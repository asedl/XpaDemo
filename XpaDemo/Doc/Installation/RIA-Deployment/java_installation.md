# Java installation for Magic RIA
For Magic XPA Rich Client (RIA) Builder you need a Java JDK. For Magic XPA 3.3 it should be Java 8 32-Bit. XPA 3.3 is the first XPA version which added support for Java 8, so if you have an older version you will need Java 7. Also note the documents regarding the Java installation in XpaDemo project.  

If its only about Magic RIA you basically do not need to install a JDK because you probably will have installed Android Studio (Android SDK) and that ships with a JDK. You just jave to make sure that it's a version XPA can work with too, so choose Java 8 32-Bit, when you download and install the Android SDK. 

What you have in Android Studio you can check with java -version command from command line: 
![Android JDK version](android_jdk.png) 

_You know from above that it's 32-Bit because it does not say it's 64-Bit. As you can see this is a Open JDK, and not what you get if you download Java from Oracle. If this causes any issue with Magic Xpa then, I can't tell._ 





