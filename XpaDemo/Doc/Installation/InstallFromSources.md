# Installing and running XpaDemo project from sources
 
Github offers to download the sources as PKZIP archive or by cloning the repository. In order to clone a repository you need to have a git client installed and if that's the case you can simply open a command prompt, change to the directory where you usually put your sample/test Magic XPA projects and type following command:
```
git clone https://github.com/asedl/xpaxmltest.git
```

Above will create a new (sub-) directory named "xpaxmltest". If a sub-directory with that name already exist the command will fail. 

Besides some readmes license and build files that directory does not contain anything really important. The projects and their sources do reside in a (sub-) directory named xpaxmltest\\*XPATests*, that's the "home directory" of the XpaDemo project / application. 

The first thing which you should do when you did download the sources (project) is: Run XpaTests.ecf in configuration mode, as it's described in [Installing and running XpaDemo project from a release](https://github.com/asedl/xpaxmltest/blob/master/XPATests/Doc/Installation/InstallationFromRelease.md) . You can do this with a source distribution too, because XpaTests.ecf is part of the sources. 

By running XpaTests.ecf in configuration mode you get a valid initialization file for usage in XPA Studio and Runtime and you get two shortcuts in the home directory of the application to start Studio and Runtime with that configurtion file (XpaTests.ini) on commandline. 

To open the sample project you do simply start your XPA 3.3 Studio and open the project file [XPATests.edp](/XPATests/XPATests.edp). Basically that's it, there's however a few adjustments to your .INI required which you can either do directly and manually in your Magic.INI (better a copy of it) or by adjusting the accompanying @ini [XPATests.ini](/XPATests/XPATests.ini) and put that on the command line properties of the shortcut you do use to start your Studio / Runtime. In Help Menu there's also an entry which does this for you. It generates the required .INI file and creates shortcuts to start Studio and Runtime - in your installation folder.  
  
One goal of this project is to get a framework / container application for demo programs which allows you to download and start an application developed with Magic without much need for an installation or a complicated configuration. Thanks to the %WorkingDir% variable which Magic injects during startup that's trivial for simple applications but when you start to add components to your application (may be Magic components or 3'rd party) things might get complicated - you either need a setup / deploy script or try to configure the application automatically during startup. There's separate documents for these issues, be sure to check the folder for those too if you run into issues: https://github.com/asedl/xpaxmltest/tree/master/XPATests/Doc/Installation


## Binaries
In order to be able to run all sample programs you first have to create all required "binaries", which are Magic XPA components (*.ecf), some Java libraries (*.jar) and some .NET assemblies (*.exe / *.dll). 

Since the project is not yet configured completely for build tools like Maven or Gradle, this is a lot of work. You do find these binaries however in the binary releases (see link above) and you can copy from there what's missing to your project directory with the sources. If you dont do this or you don't built the required components, some samples which do require those, will simply not work.  

## 3'rd party software
For some specific samples you will have to download and install some additional software. The full list of these (mostly) tools you get by staring (demo) program [OUTIL002_Components](/XPATests/Doc/Samples/XpaTUtils/OUTIL002_Components.md) . There all this software is listed with type=X and a brief description regarding usage in XpaDemo project and some information about the "component" 


 