# XpaTHttpDNET

This is sample .NET (C#) code implementing a SOAP request to a secure server which requires you to identify yourself by providing a 
client certificate. You can also use this code to HttpPost() any data to any (secure) HTTP(S) server which requires you to send a client 
certificate - just do not set the SOAPAction HTTP header then.  

Currently XpaTHttpDNet.Post requires you to provide the client certificate as a (eventually password protected) certificate file, other meanbs to 
provide the certificate might be added. Re work with Windows/.NET and X.509 certificates I found this blog article informative and helpful: 
http://paulstovell.com/blog/x509certificate2  

One Magic Xpa demo program using  XpaTHttpDNET.Post in order to perform a (SOAP) request is [OSOAP001_GreetingsClient](/XpaDemo/Doc/Samples/XpaTSoap/OSOAP001_GreetingsClient.md) 
in XpaDemo component [XpaTSoap](/XpaDemo/Components/XpaTSoap). Check the documentation of that Demo program / component to get more information 
about usage in Magic (and other components required by this Demo - like the sample https server implemented in Java).  

> Note that there is an unresolved issue with XpaTHttpDNET.Post when used with Magic where it fails to validate the server's certificate. As 
a workaround (temporary solution) the server's certificate is always considered "valid". There's an open issue for that: https://github.com/asedl/XpaDemo/issues/2#issue-364035583



