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
  
Final version / deliverable of XpaHttp will most likely be a .NET library.
That's, at the end, the only way you can get "events" (delegates, futures, ...) work with Magic (for the "asynchronous" stuff
and better error handling).  
  
There's a plan to check if JMS / Message Queues could help and allow sufficient performance. 
That would solve the issues with the asynchronous and stateless nature of this stuff and would add "guaranteed delivery" and such fetures at minimal costs.




