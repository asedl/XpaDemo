# XpatQueue

XpatQueue is a component which deals with "message queue handling". There's some interface programs (.NET), samples and demo programs.  

This first version is mostly about Magic Xpa + Apache ActiveMQ. Apache ActiveMQ is probably the most popular open source messaging and Integration Patterns server whih supports a wide range of protocols and has plenty of additional features (like f.i. a message scheduler).  Some more information about ApacheMQ and links to additional information you can find in document [ActiveMQ installation/configuration](./ActiveMQ.md).  

Plan is to add support for some other Message Queues as well, that does however not have priority at the moment. Samples and code have "demo" quality, a version which would be "ready for production" might get released 1Q/2019.  

Basically Magic Xpa (and preceeding versions) do ship with a ["Message Queue component"](http://kb.magicsoftware.com/articles/bl_Reference/MESSAGEMessaging-Connectivity-xpa-3x), usage of that however requires a enterprise server license so I actually never saw it working besides some simple things with MSMQ.  

XpatQueue demo (currently) consists of following components / libraries:

- XpatQueue Magic Xpa application/component
- [XpatQueue .NET assemby](/XpaDemo/tree/master/XpaDemo/external/Dotnet/XpaTQueue)  

# Publish/Subscribe examples
| Name | Type/Pattern | Descrition |
| ---- | ---- | ---- |
|  [TSTO112_Subscriber](Samples/TSTO112_Subscriber.md) | Publish/Subscribe  |  |
|  [#TSTO112A_Publish]() | Publish/Subscribe  |  Publishes (produces) messages and sends them to the queue (resp. topic) where TSTO112_Subscriber subscibes to |

