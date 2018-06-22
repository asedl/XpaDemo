# XpaHttp library / extension (s)

There were quite some issues recently with Magic's built in Http client functionality due to the lack of support for TLS 1.2, that's however not the motivation behind this project.
What Magic has to offer in that respect (HttpCall, ..) is insufficient anyways. The error handling is a catastrophe and asynchronous features are missing completely. 

Goal of this "subproject" is a production-ready replacement / alternative for HttpCall, tailored for Magic applications.
  
  
Current status:  
Only a few samples for alternative solutions implemented with
* Java (Apache HttpCLient/HttpCore) 
* .NET (inline Magic snipptest and C# script), 
* cURL (command line requests)
* other scripting technology bawsed on templates (csscript, wsh, csript/wscript)
* ...
See sample [OWCLN001_xpatest_uris](Samples/XpaTHttp/OWCLN001_xpatest_uris.md)
  
  
You can have a look into these and decide yourself regarding future direction.
Migration to XPA 3.3 is an option of course too ... if its only about the TLS 1.2 issues.  

>* As a Magic user in magicu-l found out, Magic Xpa 3.3 (Java http framework) or Magic Xpa 3.3a (.NET http framework) is **not always**
a solution because MSE admitted to him that these new modules for Http support in Magic do not yet support client certificates but only Xpa 4 does (which is said to be released end of July 2018). Deadline for many regarding TLS 1.2 support is however 30.06.2018 because then compliance requires companies dealing with payment data to deactivate support for SSL and early TLS on their servers (-> https://blog.pcisecuritystandards.org/are-you-ready-for-30-june-2018-sayin-goodbye-to-ssl-early-tls ). The chance that these companies also do require you to identify yourself with a client certificate is high and that cannot be achieved with Magic versions before Xpa 4. This is relevant for all communication over https, also if you implement SOAP clients with Magic SOAP Lite gateway * 
  
There's a plan to check if JMS / Message Queues could help and allow sufficient performance. 
That would solve the issues with the asynchronous and stateless nature of this stuff and would add "guaranteed delivery" and such fetures at minimal costs.




