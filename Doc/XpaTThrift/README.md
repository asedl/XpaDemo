# XpaTThrift

XpaTThrift is a component in XpaDemo framework which helps to utilize the [Apache Thrift](https://thrift.apache.org/) software framework in 
order to do scalable cross-language service development where one of the implementation languages could be Magic Xpa. Currently this project is in a 
very early stage, no code committed yet. We'll start with the client side, and later on check if we can have Magic Xpa acting as a server as well 
(which will be kind of a challenge due to the multi-threaded nature of these).

The idea for this projects originates from a requirement to integrate some Python and GO code into a Magic Xpa application which is way 
harder to use in Magic Xpa than f.i. Java and C# (for which an integration with Apache Thrift into existing Magic applications would 
however make sense to some extend as well, because it would free you from writing all the boilerplate / interface code and would allow you to 
work with a interface definition language, ...).  

There's another popular open-source cross-language RPC framework based on Google's Protocol buffers: [gRPC](https://grpc.io/). Apache Thrift 
originally was developed at Facebook. 
