---
title: "Toolkit technical background overview"
permalink: /docs/knowledge/overview/
excerpt: "Basic knowledge of the toolkits technical domain."
last_modified_at: 2020-08-21T11:37:48-04:00
redirect_from:
   - /theme-setup/
sidebar:
   nav: "knowledgedocs"
---
{% include toc %}
{% include editme %}

# The ElasticLoadBalance Operator

The `ElasticLoadBalance` operator, available on github under the streamsx.plumbing toolkit, is a drop-in replacement for the `ThreadedSplit` operator from the SPL Standard Library.

The new functionality is that it allows for runtime elasticity; in our context, runtime elasticity means that it will continually monitor its own tuple throughput, and adjust the active number of threads to seek out maximum performance.

To achieve this elasticity, I adapted our prior research work. Our papers [Elastic Scaling of Data Parallel Operators in Stream Processing (IPDPS 2009)](http://www.scott-a-s.com/files/ipdps09.pdf) and [Elastic Scaling for Data Stream Processing (TPDS 2014)](http://www.scott-a-s.com/files/tpds2014_elastic.pdf) present elasticity algorithms in the context of threads and processes distributed across hosts, respectively. The work in the paper from 2009 dynamically adapts the number of threads inside of a data-parallel operator, but it does not respond to workload changes. The paper from 2014 responds to workload changes, but it is designed to work across hosts, so it assumes larger communication costs. The `ElasticLoadBalance` operator incorporates lessons from both approaches to dynamically respond to workload changes in a threaded environment.

A note on the name: the `ThreadedSplit` operator that is currently part of the SPL Standard Toolkit already performs load balancing. As tuples arrive, it prefers to place tuples in the "next" buffer according to round-robin order. However, if that buffer is full, it will move on to the next available buffer, effectively load balancing the tuples across the output ports. **LoadBalance** is a more descriptive name for this operation, making this operator `ElasticLoadBlance`.

## Why Use It?

The primary use-case for ElasticLoadBalance (and ThreadedSplit) is to enable taking advantage of [data parallelism](http://en.wikipedia.org/wiki/Data_parallelism). In our context, data parallelism means invoking the same operator multiple times, and sending different tuples of the same stream to different invocations of that operator. Performance improves because we are processing tuples in parallel that previously were processed sequentially.

However, it is difficult to determine how much parallelism will yield the best performance. That is, is it best to invoke three parallel copies, or four? Currently, application developers must determine this by running their own experiments and manually varying the degree of parallelism. Developers must perform these experiments for every system they want to deploy their application to. Aside from the burden of taking extra time and effort, a major difficulty is that running such experiments on production systems is sometimes not an option. Further, such experiments may not answer how much parallelism is best under varying work loads.

Elasticity solves these problems by figuring out, at runtime, how much parallelism yields the best performance. Elastic solutions are robust to changes in both the hardware itself and the workload.
