# Change hosts file on emulator
If you deploy a RC component to Android, the client will run on the device, the (Magic XPA) RIA server will run on your server which is, in case of development, your local PC which hosts the Android emulator. If you want to access the host from the application running on the emulator you can use 10.0.2.2 Network address, which is a special alias to the loopback interface (127.0.0.1) of the host. 127.0.0.1 to access the host you cannot use, that would be the loopback interface of the emulator. Check [Android Emulator Networking](https://developer.android.com/studio/run/emulator-networking) for more information.

If you do not want to use Network address 10.0.2.2 to access the host you can also work with hostnames resp. with a hosts file where you map your hostnames into IP addresses. Before trying DNS Android will look there if it can resolve a hostname.  

For me Magic Xpa f.i. constantly wrote "Andreas-Lenovo" to configuration files. Result was that the RC client app running on Android was not able to find the server "Andreas-Lenovo". Solution was: Add a hostname -> IP addess to /system/etc/hosts for "Andreas-Lenovo"  

The minimal hosts file which has that mapping then looks like following:

```/system/etc/hosts
# Name for loopback interface of host computer (name: Andreas-Lenovo)
10.0.2.2 Andreas-Lenovo
```

## 1. Edit the hosts file
Create or edit a hosts file on Windows and save it to disk. In this sample we will use *C:\TEMP\hosts*. Be sure that you *do save the text file with Unix line endings (LF)*. If you do save it with Windows line endings (CRLF) it probably won't work on Android 

See Step#5 below if you do want to copy an existing hosts file on Android to Windows first in order to edit that and thereby avoiding that you loose existing host definitions.

## 2. Start the emulator 
If its not already running start the emulator from Android Studio or from command line and ensure its an writable image 

```cmd
emulator -avd Nexus_5X_API_27_x86 -writable-system 
```

## 3. push the hosts file from your local PC to Android

```cmd
adb root
adb remount
adb push c://temp/hosts /system/etc/hosts
```

Basically that's it. IP addresses for all hosts defined in /system/etc/hosts should get resolved now ... 

## Check if its working ...

```cmd
adb shell
cat /system/etc/hosts
ping Andreas-Lenovo
```

## Pull the hosts file from Android
If you already have a hosts file on Android you can pull it from there first. Then you can edit that file, instead of creating a new file and replacing what you have on Android. 

```cmd
adb root
adb remount
adb pull /system/etc/hosts c://temp/hosts.android
```
