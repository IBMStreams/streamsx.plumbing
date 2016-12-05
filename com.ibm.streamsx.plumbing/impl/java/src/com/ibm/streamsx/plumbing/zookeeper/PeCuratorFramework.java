/*
# Licensed Materials - Property of IBM
# Copyright IBM Corp. 2013, 2016
*/
package com.ibm.streamsx.plumbing.zookeeper;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.logging.Logger;

import org.apache.curator.framework.CuratorFramework;
import org.apache.curator.framework.CuratorFrameworkFactory;
import org.apache.curator.retry.ExponentialBackoffRetry;

import com.ibm.streams.operator.model.InputPortSet;
import com.ibm.streams.operator.model.Libraries;
import com.ibm.streams.operator.model.OutputPortSet;
import com.ibm.streams.operator.model.PrimitiveOperator;
import com.ibm.streams.operator.model.SharedLoader;

/**
 * Maintains a single CuratorFramework client for the PE, for operators 
 * in this toolkit that use SharedLoader.
 * 
 * CuratorFramework is thread-safe, a single instance is recommended.
 * http://curator.apache.org/curator-framework/index.html
 *
 */

public class PeCuratorFramework {
    
    private static final Logger trace = Logger.getLogger("com.ibm.streamsx.plumbing");
    
    private static final AtomicInteger refCount = new AtomicInteger();
    private static CuratorFramework client;
    
    /**
     * Create a single CuratorFramework for the PE.
     * @return CuratorFramework
     * @throws InterruptedException
     */
    public static CuratorFramework initializeZkClient() throws InterruptedException {
        synchronized (refCount) {
            if (client == null) {                
                String connString = System.getenv("STREAMS_ZKCONNECT");
                trace.info("Connecting to Zookeeper: " + connString);

                client = CuratorFrameworkFactory.newClient(connString,
                        new ExponentialBackoffRetry(1000, Integer.MAX_VALUE, 5000));

                client.start();
            }
        }
        
        client.getZookeeperClient().blockUntilConnectedOrTimedOut();

        int operatorCount = refCount.incrementAndGet();

        trace.info("Connected to Zookeeper using Curator:operator count:" + operatorCount);
        return client;
    }
    
   /**
    * Get the single curator framwork.
    */
    public static CuratorFramework getZkClient() {
        
        synchronized (refCount) {
            assert refCount.get() > 0;
            return client;
        }
    }

   /**
    * Close.
    */
    public static void closeZkClient(CuratorFramework opClient) {
        // Ensure the operator did successfully connect
        if (opClient == null)
             return;

        synchronized (refCount) {
            assert opClient == client;
            assert refCount.get() > 0;

            if (refCount.decrementAndGet() == 0)
                if (client != null) {
                    client.close();
                    client = null;
                }        
        }
    }
}
