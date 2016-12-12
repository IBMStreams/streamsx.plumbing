/*
# Licensed Materials - Property of IBM
# Copyright IBM Corp. 2016
*/
package com.ibm.streamsx.plumbing.zookeeper;

import static com.ibm.streamsx.plumbing.zookeeper.PeCuratorFramework.getZkClient;
import static com.ibm.streamsx.plumbing.zookeeper.PeCuratorFramework.initializeZkClient;

import org.apache.curator.framework.CuratorFramework;

import com.ibm.streams.operator.AbstractOperator;
import com.ibm.streams.operator.OperatorContext;
import com.ibm.streams.operator.OutputTuple;
import com.ibm.streams.operator.StreamSchema;
import com.ibm.streams.operator.StreamingInput;
import com.ibm.streams.operator.Tuple;
import com.ibm.streams.operator.model.InputPortSet;
import com.ibm.streams.operator.model.Libraries;
import com.ibm.streams.operator.model.OutputPortSet;
import com.ibm.streams.operator.model.OutputPortSet.WindowPunctuationOutputMode;
import com.ibm.streams.operator.model.Parameter;
import com.ibm.streams.operator.model.PrimitiveOperator;
import com.ibm.streams.operator.model.SharedLoader;
import com.ibm.streams.operator.types.RString;

/**
 * Take an action against a Znode for each input tuple.
 *
 */
@PrimitiveOperator(description=ZnodeAction.DESC)
@InputPortSet(cardinality = 1)
@OutputPortSet(cardinality = 1, optional = true, windowPunctuationOutputMode = WindowPunctuationOutputMode.Preserving)
@Libraries({ "opt/apache-curator-2.7.1/*", "opt/slf4j-1.7.5/*", "opt/zookeeper-3.4.8.jar", "opt/guava-14.0.1.jar" })
@SharedLoader
public class ZnodeAction extends AbstractOperator {
    
    protected static final String DESC = "Take an action against a znode path for each tuple."
            + " Each input tuple results in an action against a znode defined by the parameters"
            + " `path` and `action`. The actions are:\\n"
            + "* `Create` - The znode path will be created with the contents of the data attribute from the input tuple."
            + " If the znode already exists than an exception is thrown.\\n"
            + "* `Get` - The znode path will be read and its contents set to the data attribute of the output tuple."
            + " At operator initialization time the znode is created if it does not exist.\\n"
            + "* `Set` - The znode path will be set to the contents of the data attribute from the input tuple."
            + " At operator initialization time the znode is created if it does not exist.\\n"
            + "* `Delete` - The znode path will be deleted.\\n"
            + "The data attribute is set to `data` if it exists, otherwise `jsonString`. The data attribute"
            + " must be of type `rstring`."
            + "\\n\n"
            + "If an output port exists an output tuple is submitted for each input tuple after the"
            + "successful znode action has occurred."
            + " Matching input atttributes are copied to output attributes, if the action is `Get`"
            + " then the data attribute contains the contents of the znode."
            + "\\n"
            + "The ZooKeeper instance is the one that the IBM Streams instance is configured"
            + " to use through its domain.";

    public enum Type {
        Create, Get, Set, Delete;
    }

    private String path;
    private Type action;
    private String dataName;

    public Type getAction() {
        return action;
    }

    @Parameter(description="Znode action to be applied for each input tuple.")
    public void setAction(Type action) {
        this.action = action;
    }

    public String getPath() {
        return path;
    }

    @Parameter(description="Znode path to be actioned. The path must start with a `/`, for example `/app1/p_1`.")
    public void setPath(String path) {
        if (!path.startsWith("/"))
            throw new IllegalArgumentException();
        this.path = path;
    }

    @Override
    public synchronized void initialize(OperatorContext context) throws Exception {
        super.initialize(context);

        initializeZkClient();

        byte[] defData = new byte[0];
        StreamSchema inSchema = getInput(0).getStreamSchema();
        if (inSchema.getAttribute("data") != null) {
            dataName = "data";
        } else if (inSchema.getAttribute("jsonString") != null) {
            dataName = "jsonString";
            defData = "{}".getBytes("UTF-8"); // empty JSON object
        }

        if (getAction() == Type.Set || getAction() == Type.Get) {
            if (getZkClient().checkExists().forPath(path) == null)
                getZkClient().create().creatingParentsIfNeeded().forPath(path, defData);
        }
    }

    private Type getAction(Tuple tuple) {
        Type action = getAction();
        if (action != null)
            return action;
        return tuple.getEnum(Type.class, "action");
    }

    private String getPath(Tuple tuple) {
        String path = getPath();
        if (path != null)
            return path;
        return tuple.getString("path");
    }

    @Override
    public void process(StreamingInput<Tuple> stream, Tuple tuple) throws Exception {

        String path = getPath(tuple);
        final Type action = getAction(tuple);
        switch (action) {
        case Create:
        case Delete:
        case Set:
            update(action, path, tuple);
            break;
        case Get:
            read(path, tuple);
        default:
            break;
        }
    }

    private byte[] getData(Tuple tuple) {
        RString data = (RString) tuple.getObject(dataName);
        return data.getData();
    }

    private void update(Type action, String path, Tuple tuple) throws Exception {

        byte[] data = getData(tuple);

        final CuratorFramework client = getZkClient();
        switch (action) {
        case Create:
            client.create().creatingParentsIfNeeded().forPath(path, data);
            break;
        case Set:
            client.setData().forPath(path, data);
            break;
        case Delete:
            client.delete().deletingChildrenIfNeeded().forPath(path);
            break;
        default:
            assert (false);
        }
        if (getOperatorContext().getNumberOfStreamingOutputs() == 1) {
            OutputTuple out = getOutput(0).newTuple();
            out.assign(tuple);
            getOutput(0).submit(out);
        }
    }

    private void read(String path, Tuple tuple) throws Exception {
        final CuratorFramework client = getZkClient();
        byte[] data = client.getData().forPath(path);
        OutputTuple out = getOutput(0).newTuple();
        out.assign(tuple);
        out.setObject(dataName, new RString(data));
        getOutput(0).submit(out);
    }
}
