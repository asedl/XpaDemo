# Gradle
Gradle is a build tool (like Make, Ant, Maven, ...). Magic XPA uses it to build the Java projects it generates, f.i. when you deploy Magic Rich Client programs (RC) to Android.  

You do not have to install Gradle. When you use the Magic XPA Builder for RC / RIA, Magic uses a Gradle wrapper which is basically just a stub and which will download install and configure Gradle - in order to be able to build a Magic Xpa RIA project and deploy it as APK to Android - on your machine. 

You can find that Gradle wrapper if you use the Magic Xpa Builder for Rich client / RIA in directory source\gradle\wrapper. Its gradle-wrapper.jar and that will read its configuration from gradle-wrapper.properties. Content of that file for a deployment to Android with Xpa 3.3 Single user:
```settings
#Thu May 25 11:33:19 IDT 2017
distributionBase=GRADLE_USER_HOME
distributionPath=wrapper/dists
zipStoreBase=GRADLE_USER_HOME
zipStorePath=wrapper/dists
distributionUrl=https\://services.gradle.org/distributions/gradle-3.5-all.zip
```

That's basically an old version which would raise some issues with latest Android SDKs, Android SDK has however it's own gradle wrapper and it can also use an existing Gradle installation - which you might have, if you download Gradle from [gradle.org](https://gradle.org/) and installed it.  

Magic XPA will not start Gradle directly in order to build the (Java) project but will actually start Windows powershell and run a powershell script it created when you deploy RIA: source\build.ps1 . There it will finally run Gradle (gradlew.bat) to build source\app\build.gradle (your "app").  

