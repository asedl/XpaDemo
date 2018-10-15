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
|  [TSTO112A_Publish]() | Publish/Subscribe  |  Publishes (produces) messages and sends them to the queue (resp. topic) where TSTO112_Subscriber subscibes to |

> TSTO112_Subscriber and TSTO112A_Publish are parallel programs (tasks) so you can both start and run in parallel. You can however too run multiple consumers and multiple producers by running multiple instances of the demo application (Magic XPA Runtime with XpaTQueue.ecf loaded as Startapplication) and these instances can also run on multiple machines. ActiveMQ will coordinata all this and also ApacheMQ you can run in a "distributed mode" with multiple brokers.  

> The topic subscription in TSTO112_Subscriber is "durable". If TSTO112_Subscriber subscribed for messages to a specific topic and goes down for some reason or looses network connectivity, ApacheMQ will persist these messages and TSTO112_Subscriber will get them as soon as it is connected again and until the durable topic subscription gets explicitely deleted.  

> *** Note: *** At the moment there might be some issues with re-connecting a subscriber to the messaging system because we recently changed the client IDs to contain process and thread id. After a restart of these clients (in case of failure or maintenance) this client id does change.  

