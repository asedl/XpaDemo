# JAVA_HOME
> This is preliminary, unconfiremed information about things which are not documented anywhere in Magic (asfaik). Its just the result of
brief investigation by monitoring and debugging the behaviour of a Magic XPA 3.3 Runtime  

As mentioed in various places of this documentation the (system) environment variable JAVA_HOME plays an important role on a machine where
you do Java development resp. run Java applications. Typically you set JAVA_HOME after you did install a JDK to the installation path of that 
JDK and (if you have multiple versions installed). change that variable to the installation path of the Java version you want to use - either 
permanently or in your scripts. Besides there's another environment variable which is relevant for the JRE, the JRE_HOME system environment variable, 
that however is not widely used and not considered here now.

For Magic XPA applications JAVA_HOME typically raises issues, because Magic requires a 32-Bit Java version and until XPA 3.3 had no support for
Java 8, which is what you will find most often preinstalled on today's desktop systems: Java 8, 64-Bit.

For that (and other) reasons it's possible to specify which Java installation Magic should use, when it needs to start a JVM, in the Magic.INI: 
``` Magic.INI
[MAGIC_JAVA]
JAVA_HOME=c:\program files (x86)\Java\Jdk8u72x86
```

**Surprising fact** and result of the debug session initially mentioned: You can start a Magic application on a system where you have either
system environmentvariable JAVA_HOME set nor a setting for [MAGIC_JAVA]JAVA_HOME in the .INI and if you look into these values after Magic startup
from within your Magic application you will find them correctly set and pointing to a valid Java installation (valid in terms of compatibilty 
with the Magic version you run). You can verify that in XPATEST project by looking into the Help/About screen resp. executing program 
[OUTIL001_About](../Samples/XpaTUtils/OUTIL001_About.md) because these values get displayed there.  

What happened is: Magic "scans" the machine during startup for existing Java installations, resp. for jvm.dll, the Java Invocation API, 
until it finds one which "looks good". On my machine wher I have plenty of Java software, that would be when it finds a Java 8 JRE 32-Bit.
Thats ok basically and Magic does this quick enough. Application startup is not really instant but acceptable.

What happens too however is: Now, since Magic altered the value of system environment variable JAVA_HOME, other Java applications which you 
might use/start from within your application (like by executing a "java -jar ..." with InvokeOs) might run into trouble because they need
the latest 64-Bit Java version. Thats because cmd.exe (which you use in InvokeOS and at the end java.exe will inherit the system settings from
Magic runtime - which actually created these processes). An impact on Java software you start from outside Magic this has not, they get their
own environment settings - which has not been modified by your Magic application.

I'll add some more information and the debug logs if I find some time but basically I consider this a minor issue, just worth mentioning and maybe 
once a while cause for problems which might be hard to find. Question is also if we should always leave our JAVA_HOME setting in Magic.INI empty
and rely on this JVM scan of Magic during startup - or not.

