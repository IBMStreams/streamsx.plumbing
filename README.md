streamsx.plumbing
================

Plumbing operators manipulate the flow of tuples in a Streams application, but are 
not part of the logic of the application. This toolkit contains:

  * **ElasticLoadBalance**: Dynamically load-balances tuples across its output 
  ports. At runtime, it will determine the number of output ports that achieve 
  the best performance.
  * **Load Shedding Operators**: Operators that use control variables to shed tuples.
  * **Control variables** : SPL support for control variables provided by the JobControlPlane operator.
