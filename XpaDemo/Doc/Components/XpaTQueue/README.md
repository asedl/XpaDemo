# XpatQueue

XpatQueue is a component which deals with message queue handling. There's some interface programs, sample- and demo programs.  

This first version is mostly about Magic Xpa + Apache ActiveMQ. Apache ActiveMQ is probably the most popular open source messaging and Integration Patterns server. Plan is to add support for some other Message Queues as well. Some more information you can find in document [ActiveMQ installation/configuration](./ActiveMQ.md).  

Basically Magic Xpa (and preceeding versions) do ship with a Message Queue component, usage of that however requires a enterprise server license. Besides its not clear if it actually really supports anything else than (Microsoft) MSMQ  

XpatQueue demo (currently) consists of following components / libraries:

- XpatQueue Magic Xpa application/component
- [XpatQueue .NET assemby](/XpaDemo/tree/master/XpaDemo/external/Dotnet)
