# Getting information about the Magic runtime environment from inside a Magic application (project)

## How does XPATEST find the Magic installation it will use for shortcuts and (.ini) settings

There's not often a need for a Magic application to know how it does get executed (by a Studio, by a Runtime, which version of that "Engine", ...). Autoconfiguration of a Magic application is however part of that Demo container and so it tries to get that information from inside the Magic application. There's several options.

### %EngineDir%

Thats's a logical name which Magic runtime injects during startup and which you can query from inside the application. It gives you the directory of the "Engine" used to start the application. Only problem with that: Magic renames the product quite often. How would you know what the .exe currently is named ? For XPA 3.3 it's "MgXPARuntime.Exe" and if you want tro create links/shortcuts, you could use following expression: Trim(Translate('%EngineDir%')) & 'MgXpaRuntime.exe".

### %WorkingDir%
%WorkingDir% is one of the three project directories which the Magic runtime "injects" during startup. You can work with it as if it would be a logical name named "WorkingDir", it does however not exist in the Magic.ini ([MAGIC_LOGICAL_NAMES]. %WorkingDir% will always point to your project directory, that's the directory where the application's .ecf file reside. Basically that's a nice feature, but there's two issues with %WorkingDir%:  
1. You cannot use it in the .INI for settings which do get evaluated before the application is actually started, resp. the .ecf is loaded. If you use %WorkingDir% f.i. in location property of databases in [MAGIC_DATABASES] section, the path to those DBs will be invalid when your application starts.
2. A .ecf I would consider a binary which requires to be stored in a separate directory with special permissions ("/bin" f.i). If one uses %WorkingDirectory% as root (home) directory for an application you end up with everything in your "/bin" folder.  On Windows you should put user specific program data to (system environment variable) %APPDATA% and data which is shared by all users which do use your application on that machine to %ProgramData%

### Commandline

In a Magic application you do not have access to the commandline, used to start the process so you cant read the first argument, which is by convention the name of the executable itself. MgXpaRuntime.exe in our case. There is a sample program in XPATEST which shows how to get the commandline, by using .NET Enviuronment and by using Windows API GetCommandlineW

### Registry

XPATEST will query the registry for a key named HKEY_CLASSES_ROOT\EDPFile\shell\command\open, the shell open command for .edp files, Magic XPA project files. On a machine where Magic has been installed with the Magic Setup program, this will point to the latest Magic version installed on that machine. XPATEST will extract the first command line argument (which points to the application) and found thereby the installation directory. In addition it will query the version properties of that file.

On a system where Magic was not installed from Installation media (Setup) this won't help and in the Magic world its quite common to simply copy an installation from one machine to another.

# Altering the configuration of a Magic application before it's actually started 

Sometimes there is a need to alter the configuration of a Magic application before it's actually started resp. where it would be too late to check/alter the configuration from inside the Magic application.  Examples for that are some of the .INI settings where Magic does not accept logical names or where you would rather want to use environment variables in the .INI file in order to get some user/session specific information, ... . System environment variables you cannot use in a Magic.Ini, they will be interpreted as Magic logical names.

This issue with Magic applications is once a while discussed in the Magic community, last time I was aware of such a discussion is folloing thread from the user group: [Can you dynamically set the error log path?](https://magicu-l.groups.io/g/main/topic/can_you_dynamically_set_the/18140035)

Options / Possible solutions for this dilemma are:

## Windows Setup Program

The obvious solution. Write a setup program for your application and do a proper installation of your application. There's plenty of toolkits which make this task quite easy (InstallShield, Wise, ...) and (today) there's also a lot of packet managers you can use - or even build managers like Ant / Maven / Gradle / ....

## Startup script

Instead of asking the Magic engine (Studio, Runtime) to start a project (MyApp.edp / MyApp.ecf) you ask a script to do so which will, before it actually and finally starts the Magic engine, modify the configuration (like adding some information to the .INI, putting some parameters on the command line ... ).  
  
The script (can be a compiled application as well of course), can terminate when it created the Magic process, it can however also keep running and thereby can "monitor" the process it started: The Magic runtime which started your application. Good for crash recovery and other stuff (Cleanup, ...)

The XPATEST demo application has samples for "Magic startup scripts". 

## Host / Container application

That's basically not much different from the "Startup script" approach only that you do a bit more now in the application which is initially started and which serves as the host for your Magic applications. Samples for this are "Node & Magic" applications where you then can integrate with the container, can have a Magic application which acts as a http server, ... . 







