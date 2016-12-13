/*
# Licensed Materials - Property of IBM
# Copyright IBM Corp. 2013, 2016
*/
package com.ibm.streamsx.plumbing.leader;

import static com.ibm.streamsx.plumbing.zookeeper.PeCuratorFramework.closeZkClient;
import static com.ibm.streamsx.plumbing.zookeeper.PeCuratorFramework.getZkClient;
import static com.ibm.streamsx.plumbing.zookeeper.PeCuratorFramework.initializeZkClient;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.logging.Logger;

import javax.management.InstanceNotFoundException;
import javax.management.MBeanServerConnection;

import org.apache.curator.framework.CuratorFramework;
import org.apache.curator.framework.recipes.leader.LeaderLatch;
import org.apache.curator.framework.recipes.leader.LeaderLatch.CloseMode;
import org.apache.curator.framework.recipes.leader.LeaderLatchListener;

import com.ibm.streams.operator.AbstractOperator;
import com.ibm.streams.operator.OperatorContext;
import com.ibm.streams.operator.OutputTuple;
import com.ibm.streams.operator.StreamingOutput;
import com.ibm.streams.operator.control.ControlPlaneManagement;
import com.ibm.streams.operator.control.Controllable;
import com.ibm.streams.operator.logging.TraceLevel;
import com.ibm.streams.operator.metrics.Metric;
import com.ibm.streams.operator.metrics.Metric.Kind;
import com.ibm.streams.operator.model.CustomMetric;
import com.ibm.streams.operator.model.Libraries;
import com.ibm.streams.operator.model.OutputPortSet;
import com.ibm.streams.operator.model.Parameter;
import com.ibm.streams.operator.model.PrimitiveOperator;
import com.ibm.streams.operator.model.SharedLoader;
import com.ibm.streams.operator.types.RString;
import com.ibm.streams.operator.types.Timestamp;

/**
 * Java primitive operator that uses ZooKeeper to implement a leadership
 * election between itself and other instances of {@code LeadershipElection}
 * with the same group identifier.
 */
@PrimitiveOperator(description = LeadershipElection.OP_DESC)
@OutputPortSet(cardinality=1, description="Contains tuples representing leadership status changes. The stream schema"
        + " can be [LeaderStatus] or any arbitrary schema. Any attribute matching an attribute in [LeaderStatus] will"
        + "be set to a valid value otherwise it will be set to its default value.")
@Libraries({"opt/apache-curator-2.7.1/*", "opt/slf4j-1.7.5/*", "opt/zookeeper-3.4.8.jar", "opt/guava-14.0.1.jar"})
@SharedLoader
public class LeadershipElection extends AbstractOperator implements Controllable {

    public static final String OP_DESC = "Performs a leadership election between other operator invocations with the same `group`. "
            + "At any time only one invocation is the leader, should a leader have a failure a new leader will be elected. "
            + "Leadership election uses Apache Curator's leadership latch recipe against the Streams instance Zookeeper service."
            + "\\n"
            + "When the `path` parameter is not set the leadersip election is between operator invocations with the same `group`"
            + " in a single job. In this case:\\n"
            + " * the application requires an invocation of the `JobControlPlane` operator.\\n"
            + " * Invocations of `LeadershipElection` within the same `group` must be exlocated into different PEs.\\n"
            + "The Zookeeper root znode for the recipe is a sub-node `group` within job's storage node "
            + "(`com.ibm.streams.management.job.JobMXBean.retrieveZooKeeperStorageNode()`).\\n"
            + "\\n"            
            + "When the `path` parameter is set the leadersip election is between operator invocations with the same `path`"
            + " and `group` in a single domain, typically between operator invocations in different jobs in an instance."
            + " In this case:\\n"
            + " * Any invocations of `LeadershipElection` within the same `path` and `group` and job must be exlocated into different PEs.\\n"
            + "The Zookeeper root znode for the recipe is a `path`/`group`.\\n"
            + "\\n"
            + "When the leadership state of the operator changes a tuple is submitted to the output port.";


    /**
     * Group name for leadership election.
     */
    private String group;
    
    /**
     * Optional path within Zookeeper. 
     */
    private String path;

    /**
     * Metric indicating if this operator is the leader.
     */
    private Metric isLeader;

    private CuratorFramework client;
    private LeaderLatch leaderLatch;

    private String id;

    private static final Logger trace = Logger.getLogger("com.ibm.streamsx.plumbing");
    
    private final Map<String,Object> groupId = new HashMap<>();
    
    private ExecutorService singleThreadExecutor;
    private boolean portsReady;

    @Override
    public void initialize(OperatorContext context) throws Exception {
        super.initialize(context);
        
        id = "PE_" + context.getPE().getPEId().toString();
        
        groupId.put("group", new RString(getGroup()));
        groupId.put("id", new RString(getId()));
        
        // Use a single thread executor for submitting tuples from
        // the leadership latch on leadership changes.
        //
        // A task that blocks is added to stop any tuples being
        // submitted before all ports ready. The leadership election
        // is started as soon as possible to avoid any delays once
        // all ports ready occurs. Once allPortsReady is called
        // the blocking task will complete, allowing any pending
        // leadership tuples to be sent. Note on startup a tuple
        // is only sent if the operator becomes the leader.
        singleThreadExecutor = Executors.newFixedThreadPool(1, context.getThreadFactory());
        singleThreadExecutor.submit(new Callable<Object>() {

            @Override
            public Object call() throws Exception {
                synchronized (LeadershipElection.this) {
                    while (!portsReady)
                        LeadershipElection.this.wait();
                }
                trace.fine("Released portReady block: " + id);
                return null;
            }});

        client = initializeZkClient();
        
        if (getPath() == null) {
            // Leadership is within the job.
            // Attach as soon as possible, to avoid any delays during allPortsReady.
            getControlPlaneContext().connect(this);
        } else {
            // Leadership is across jobs.
            createLatch(getPath());
        }
        
        createAvoidCompletionThread();
    }
    
    private boolean relinquishLeadership(CloseMode mode) throws Exception {
        boolean wasLeader = false;
        if (leaderLatch != null) {
            wasLeader = leaderLatch.hasLeadership();
            leaderLatch.close(mode);
            leaderLatch = null;
        }
        return wasLeader;
    }

    @Override
    public void shutdown() throws Exception {
        boolean wasLeader = relinquishLeadership(CloseMode.NOTIFY_LEADER);
        if (wasLeader)
            submitTuple(false);
        
        closeZkClient(client);

        singleThreadExecutor.shutdown();
        if (wasLeader)
            Thread.sleep(200);
        singleThreadExecutor.awaitTermination(1, TimeUnit.SECONDS);
                       
        super.shutdown();
    }

    @Override
    public synchronized void allPortsReady() {
        portsReady = true;
        notifyAll();
    }

    @Parameter(description = "Leadership group name. All instances of this operator within the same `group`"
            + " are participants in a single leadership election. Group name must not start with a slash (`/`).")
    public void setGroup(String group) {
        if (group.startsWith("/"))
            throw new IllegalArgumentException(group);
        this.group = group;
    }

    private String getGroup() {
        return group;
    }
    
    private String getId() {
        return id;
    }
    
    @Parameter(optional=true, description = "Znode path for leaderhip election across multiple jobs, must start with a `/` to be used across jobs "
            + "(or an empty string to default to within a job). Optional, when not set (or set to the empty string) the path "
            + "used is specific to the job and leadership election is across operator invocations within a single jobs.")
    public void setPath(String path) {
        if (!path.isEmpty() && !path.startsWith("/"))
            throw new IllegalArgumentException(path);
        this.path = path;
    }
    private String getPath() {
        if (path.isEmpty())
            return null;
        return path;
    }

    protected Metric getIsLeader() {
        return isLeader;
    }

    @CustomMetric(kind = Kind.GAUGE, description = "Is this invocation the leader. 1 this operator invocation is the leader for the group, 0 is it not the leader.")
    public void setIsLeader(Metric isLeader) {
        this.isLeader = isLeader;
    }
    
    /**
     * Submit a tuple when the leadership changes.
     * 
     * The schema can include any or all of these attributes:
     * rstring group
     * rstring id
     * boolean leader
     * timestamp ts
     * 
     * @param leader True if this operator is the leader, false otherwise.
     */
    private void submitTuple(boolean leader) {
        
        StreamingOutput<OutputTuple> out = getOutput(0);
        Map<String,Object> attributes = new HashMap<>(groupId);
        attributes.put("leader", leader);
        attributes.put("ts", Timestamp.currentTime());

        try {
            out.submitMapAsTuple(attributes);
        } catch (Exception e) {
            try {
                relinquishLeadership(CloseMode.SILENT);
            } catch (Exception e1) {
                throw new RuntimeException(e);
            }
            throw new RuntimeException(e);
        }
    }

    @Override
    public void event(MBeanServerConnection jcp, OperatorContext context, EventType eventType) {
    }

    @Override
    public boolean isApplicable(OperatorContext context) {
        return true;
    }

    /**
     * Determine the job specific zookeeper storage node to
     * use and then create and start a leadership latch.
     */
    @Override
    public void setup(MBeanServerConnection jcp, OperatorContext context) throws InstanceNotFoundException, Exception {

        synchronized (this) {
            if (leaderLatch != null)
                return;
        }

        String path = (String) jcp.invoke(ControlPlaneManagement.JOB_NAME, "retrieveZooKeeperStorageNode", null, null);
        
        trace.fine("Zookeeper path for this job:" + path);
        
        createLatch(path);
    }
    
    private void createLatch(String path) throws Exception {
       
        synchronized (this) {
            leaderLatch = new LeaderLatch(getZkClient(), path + "/" + getGroup(), id);

            leaderLatch.addListener(new LeaderLatchListener() {

                @Override
                public void notLeader() {
                    submitTuple(false);
                    
                    // Set the metric
                    getIsLeader().setValue(0);
                    
                    if (trace.isLoggable(TraceLevel.INFO))
                        trace.info("Group:" + getGroup() + " id:" + id + " lost the leader");
                }

                @Override
                public void isLeader() {
                    submitTuple(true);
                    // Set the metric
                    getIsLeader().setValue(1);
                    if (trace.isLoggable(TraceLevel.INFO))
                        trace.info("Group:" + getGroup() + " id:" + id + " became the leader");

                }
            }, singleThreadExecutor);
        }

        trace.fine("Starting leadership latch for id: " + id);
        leaderLatch.start();
        trace.fine("Started leadership latch for id: " + id);

    }

}
