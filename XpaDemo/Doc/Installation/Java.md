# Getting the Java samples working ...

Java raises some installation / configuration issues when you decide to leverage the "Magic & Java" functionality of Magic XPA. Magic requires a 32-Bit Java VM and typically is a bit behind when it comes to supported Java versions. Magic XPA 3.3 requires 32-Bit-Java 8 for Windows, support for Java 7 has been added (asfaik) to uniPaaS 1.9. Versions before do require Java 6 and cannot work with a later Java version.

On a development system a JRE is not sufficient too, you will need a JDK. A JDK you will also need in order to get some of the "enterprise functionality" of XPA running but that we do not cover in a demo project for the SingleUser edition anyways.

Note: During Startup the Magic Runtime scans all directories in System PATH environment variable for existing Java (client) installations, respectively for jvm.dll (the Java Invocation API) and checks it. If it's a version it can work with, it will use that and set JAVA_HOME (system) environment variable and [MAGIC_JAVA]JAVA_HOME accordingly. If you have a Java version installed Magic can work with you do not have to care about these settings.

  
[MAGIC_JAVA]  
JAVA_HOME=*C:\Java\jdk1.8.x86  
CLASSPATH=*.;Support\*;Libraries\*;C:\xpa\samples\XpaDemo\XpaDemo\ext+  
ernal\Java\XPATest\target\XPATest-0.0.1-SNAPSHOT-jar-with-dependencies.jar

If you don't have a Java 8 32-Bit on your machine you need to download and install it from Oracle and put the installtion path into [MAGIC_JAVA]JAVA_HOME (without an trailling backslash!). You should rather not modify the system environment variable JAVA_HOME, that may have an impact on other applications which require a Java VM too. You should also not modify the PATH variable, for the same reason.  
  
Note: XpaDemo project has an embedded project which is only uniPaaS 1.9. Wehn you want to get Java stuff working inside there you will need a Java 7 32-Bit. The .INI you would then alter like above, just with the path to Java 7.  
  
The Java library which is part of this project (and which is referenced in the .INI above in CLASSPATH setting as XPATest-0.0.1-SNAPSHOT-jar-with-dependencies.jar is however compiled for Java 8 and later. If you want to get it work with uniPaaS and Java 7 you will need to recompile and that will raise issues for those parts there which use Java 8 stuff. So: Basically this project requires Java 8 or later, No support for previous Java versions.  
  
Also note: There is / or there will be some Java stuff in the Magic applications which will require a JDK. So if you install Java 8 better install a JDK on your development machine - from the Oracle Java SE Development Kit 8 Downloads page. For staring and running the "Desktop application samples" only a JRE will be required, the JDK contains one anyways.


