# Installation from sources
Clone the git repository or download the zipfile and extract it to a new, empty, directory.  In your Installationpath you have a subdirectory XpaDemo\XpaDemo, this is the root directory of the Demo application and this is where all the sources reside. Its a Magic XPA project so you have a project file (XpaDemo.edp) and a cabinet file (XpaDemo.ecf).  

You can either start your XPA Studio and open the project file or you can open your Xpa Runtime and open the applications control file XpaDemo.ecf (by putting its pathname with /StartApplication= parameter on command line / target property of shortcut. The "Open application in Magic Xpa runtime is gone since a while).  

Now, since this is a "fresh" installation, some settings which XpaDemo application does store in the .INI will be missing, they are not yet in your .INI (unless you added them manually before stating Studio/Runtime). In particular the settings which have to be added are database definitions. Without many programs in XpaDemo will fail with errors like "Cannot access database, ..." in the status bar (and mgerror.log)  

You can add the required settings either manually to your Magic.Ini (or any other you intend to use) or simply start the application (In Studio by pressing F7 on main program or by clicking the "Execute project" icon in toolbar. A Runtime engine XpaRuntime.exe will execute main program automatically). If, during startup, the application finds out that required settings / configuration properties are missing, it will start program OUTIL003_CheckConfiguration. This program generates a initialization
file XpaDemo.ini from a template and puts information fetched from your runtime environment into there. If you tell the program to do so, it will write this .INI to disk and besides creates shortcuts in your installation path to start Studio with @XpaDemo.ini on command line, and another one for runtime. The application will exit then and when you know restart it from these
shortcuts the required settings do exist and are valid - the application will start.  

# Installation from a released version
Not much different from above, only that you do always install from a zipfile and that now all binaries, which are not part of the source repository are included.

