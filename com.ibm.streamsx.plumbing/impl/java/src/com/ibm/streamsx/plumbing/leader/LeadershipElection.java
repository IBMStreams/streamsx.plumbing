/*
# Licensed Materials - Property of IBM
# Copyright IBM Corp. 2013, 2013
# US Government Users Restricted Rights - Use, duplication or
# disclosure restricted by GSA ADP Schedule Contract with
# IBM Corp.
*/
package com.ibm.streamsx.plumbing.leader;

import java.util.concurrent.Executors;
import java.util.logging.Logger;

import javax.management.InstanceNotFoundException;
import javax.management.MBeanServerConnection;

import org.apache.curator.framework.CuratorFramework;
import org.apache.curator.framework.CuratorFrameworkFactory;
import org.apache.curator.framework.recipes.leader.LeaderLatch;
import org.apache.curator.framework.recipes.leader.LeaderLatchListener;
import org.apache.curator.retry.ExponentialBackoffRetry;

import com.ibm.streams.operator.AbstractOperator;
import com.ibm.streams.operator.OperatorContext;
import com.ibm.streams.operator.control.ControlPlaneManagement;
import com.ibm.streams.operator.control.Controllable;
import com.ibm.streams.operator.logging.TraceLevel;
import com.ibm.streams.operator.metrics.Metric;
import com.ibm.streams.operator.metrics.Metric.Kind;
import com.ibm.streams.operator.model.CustomMetric;
import com.ibm.streams.operator.model.Libraries;
import com.ibm.streams.operator.model.Parameter;
import com.ibm.streams.operator.model.PrimitiveOperator;

/**
 * Java primitive operator that uses ZooKeeper to implement a leadership
 * election between itself and other instances of {@code LeadershipElection}
 * with the same group identifier.
 */
@PrimitiveOperator(description = LeadershipElection.OP_DESC)
@Libraries("opt/apache-curator-2.7.1/*")
public class LeadershipElection extends AbstractOperator implements Controllable {

    public static final String OP_DESC = "Performs a leadership election between other operator invocations with the same `group`. "
            + "At any time only one invocation is the leader, should a leader have a failure a new leader will be elected. "
            + "Invocations must be exlocated into different PEs." + "\\n\\n"
            + "The operator requires the application include an invocation of the `JobControlPlane` operator."
            + "\\n\\n"
            + "Leadership election uses Apache Curator's leadership latch recipe against the Streams instance Zookeeper service."
            + "The Zookeeper root node for the recipe is a sub-node `group` within job's storage node "
            + "(`com.ibm.streams.management.job.JobMXBean.retrieveZooKeeperStorageNode()`).";

    /**
     * Group name for leadership election.
     */
    private String group;

    /**
     * Metric indicating if this operator is the leader.
     */
    private Metric isLeader;

    private CuratorFramework client;
    private LeaderLatch leaderLatch;

    private String id;

    private static final Logger trace = Logger.getLogger("com.ibm.streamsx.plumbing");

    @Override
    public void initialize(OperatorContext context) throws Exception {
        super.initialize(context);

        id = "PE_" + context.getPE().getPEId().toString();

        String connString = System.getenv("STREAMS_ZKCONNECT");
        client = CuratorFrameworkFactory.newClient(connString,
                new ExponentialBackoffRetry(1000, Integer.MAX_VALUE, 5000));

        client.start();
        client.getZookeeperClient().blockUntilConnectedOrTimedOut();

        trace.fine("Connected to Zookeeper using Curator");

        // Attach as soon as possible, to avoid any delays during allPortsReady.
        getControlPlaneContext().connect(this);
    }

    @Override
    public void shutdown() throws Exception {
        if (leaderLatch != null) {
            leaderLatch.close();
            leaderLatch = null;
        }

        if (client != null) {
            client.close();
            client = null;
        }
        super.shutdown();
    }

    @Override
    public void allPortsReady() {
    }

    @Parameter(description = "Leadership group name. All instances of this operator within the same job and having the same `group`"
            + " are participants in a single leadership election. Group name must not start with a slash (`/`).")
    public void setGroup(String group) {
        this.group = group;
    }

    public String getGroup() {
        return group;
    }

    protected Metric getIsLeader() {
        return isLeader;
    }

    @CustomMetric(kind = Kind.GAUGE, description = "Is this invocation the leader. 1 this operator invocation is the leader for the group, 0 is it not the leader.")
    public void setIsLeader(Metric isLeader) {
        this.isLeader = isLeader;
    }

    @Override
    public void event(MBeanServerConnection jcp, OperatorContext context, EventType eventType) {
    }

    @Override
    public boolean isApplicable(OperatorContext context) {
        return true;
    }

    @Override
    public void setup(MBeanServerConnection jcp, OperatorContext context) throws InstanceNotFoundException, Exception {

        synchronized (this) {
            if (leaderLatch != null)
                return;
        }

        String path = (String) jcp.invoke(ControlPlaneManagement.JOB_NAME, "retrieveZooKeeperStorageNode", null, null);

        trace.fine("Zookeeper path for this job:" + path);

        synchronized (this) {
            leaderLatch = new LeaderLatch(client, path + "/" + getGroup(), id);

            leaderLatch.addListener(new LeaderLatchListener() {

                @Override
                public void notLeader() {
                    // Set the metric
                    getIsLeader().setValue(0);
                    if (trace.isLoggable(TraceLevel.INFO))
                        trace.info("Group:" + getGroup() + " id:" + id + " lost the leader");
                }

                @Override
                public void isLeader() {
                    // Set the metric
                    getIsLeader().setValue(1);
                    if (trace.isLoggable(TraceLevel.INFO))
                        trace.info("Group:" + getGroup() + " id:" + id + " became the leader");

                }
            }, Executors.newFixedThreadPool(1, context.getThreadFactory()));
        }

        trace.fine("Starting leadership latch for id: " + id);
        leaderLatch.start();
        trace.fine("Started leadership latch for id: " + id);

    }

}
