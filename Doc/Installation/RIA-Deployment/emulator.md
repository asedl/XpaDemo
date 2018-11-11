# Android Emulator(s)
If you don't have an Android phone or a cloud based solution which allows you to run your APK, you can choose to install and use an Android emulator. MSE seems to be a bit focused on Genymotion Desktop edition, which is nice - just not available as a free dwonload. If you are happy with what ships with Android SDK - that you can use too. Be sure to check following helpfile from Magic Xpa too, which is about execution of Magic RC / RIA on Android and which has that hard link to Genymotion: [Execution on Android (Magic xpa 2.x)](http://kb.magicsoftware.com/articles/bl_Reference/Execution-on-Android-xpa) 

## Nerworking issues
When you deploy a RIA application to a device (emulator) you do actually only deploy the EIA client. That client application requires network connectivity to your Magic XPA RIA server. If you have a device with network connectivity, that's not a big issue. When it is an emulator it is actually a virtual machine hosted on your development machine and in order to be able to access the Magic XPA RIA development server which runs on your machine you may need to setup/configure network connectivity between that virtual machine and your desktop first. 

A "Magic XPA RIA Server" is a http server (Apache or IIS) + A Magic XPA Internet requester + Magic Xpa (enterprise) server. For test/development Magic XPA Studio can act as a Magic XPA server too. 

## Starting an emulator
Open a command prompt and change directory to the "emulator" directory in your Android SDK directory (should be c:\users\<your username>\Local\Android\Sdk\emulator) 
You can start an emulator with: 
emulator -avd <emulator name> -partition-size 128

If you forgot the emulator name(s) you can get a reminder with: 
emulator -list-avds 


 
