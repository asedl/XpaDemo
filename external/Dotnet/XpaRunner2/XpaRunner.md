# XpaRunner

XpaRunner is a little utility which can be used to start a Magic XPA Runtime or Magic XPA Studio in order to be able to prepare the environment before the Magic XPA Runtime / Engine takes over control. Sometimes there is a requirement to do this - esp. then if you need system / user specific settings available in your .INI for path diversion - before the application is actually started so that you could modify the settings from inside Magic. That's an issue which gets discussed once a while in the usergroup. Check following document for some more details: [altering-the-configuration-of-a-magic-application-before-its-actually-started](/XpaDemo/Doc/Installation/Magic.md#altering-the-configuration-of-a-magic-application-before-its-actually-started)  

_XpaRunner is implemented as a (C#) .NET application. A script or Java application is not a really good option here because we need, in this specific case, an .exe or command file in order to be able to set the "Run As Administrator" flag for the executable file - because the Magic setup sets this flag for MagicXpaRuntime.exe and MagicXpaStudio.exe as well. Trying to start these executables might then simply fail with "requires escalation" system error_ .

Which application XpaRunner actually should start you can specify by commandline parameters or a .settings file. Minimum requirement is to specify the full pathname of the application (typically .EXE)  
  

## XpaRunner (renaming the application)
You can rename XpaRunner.exe to something more meaningful, like:
+ StartRuntime.exe
+ StartStudio.exe
+ MyApp.exe
+ InvoiceHandling.exe
+ ..

The only thing you have to ensure then, if you do this and work with .settings file(s):   The application will use it's own name in order to find the .settings file which needs to reside in the same directory. So if you have a XpaRunner.settings file and you rename (copy) XpaRunner.Exe to StartRuntime.exe you also need to rename/copy XpaRunner.settings -> StartRuntime.settings (or create a new file with that name).  
    
## XpaRunner.settings
In this file you can persist settings for XpaRunner if you do not want to work with commandline parameters. The .settings file is a simple text file from where XpaRunner will read information. If you do additionally specify one of the settings persisted there as a command line parameter, the command line parameter has priority resp. overwrites the setting from the file.  

## XpaRunner commandline parameters

Commandline parameters for XPaRunner (which you can use in batch programs, scripts or in target property of Windows shortcuts) follow Windows conventions and can be prefixed with / (backslash) - (single hyphen). If you need one of these characters in a parameter you can enclose the whole parameter in double quotes to exclude it from parsing or escape it.

XpaRunner scans the command line from left to right and stops if it finds the first parameter which is none of those specific for XpaRunner itself, one of those documented below. The rest of the command line is considered as command line for the apllication XpaRunner should start and is basically not evaluated anymore with one exception: XpaRunner will scan the rest of the command line for parameters prefixed with an @ sign,
if it's in ENVEXPAND mode. It will have to remove these parameters and replace by a modified version, its "Magic @INI Merge files" - where XpaRunner should look for occurences of Envoronment variables which require expansion. See parameter ENVEXPAND for more explanation.  

### command line samples
**XpaRunner.exe -ENVEXPAND -EXE=c:\magic\xpa\MgXpaRuntime.exe -PARAMETERS=@%ProgramData%\MyApp\Config\MyApp.Ini**  

_This will start a Magic XPA Runtime from your Magic XPA installation directory and set the working directory (since you did not specify resp. overwrite it) to "c:\magic\xpa" (which is required for Magic XPA anyways). There is only one command line parameter for the Magic Runtime:  @%ProgramData%\MyApp\Config\MyApp.Ini  

The Windows shell will expand %ProgramData% to what is configured for you, typically something like "C:\ProgramData". Parameter -ENVEXPAND is described further below. Its one
of the parameters specific for XpaRunner so it gets not passed forward to MgXpaRuntime.exe but is removed from command line_

### Parameter: EXE
**Mandatory** parameter which allows you to specify which application / command XpaRunner should actually start. You can leave aways the full path and only specify a filename w/o extension. Then the usual Windows rules for finding an executable apply, Windows will search your PATH environment variable, ...  

### Parameter: PARAMETERS
Commandline parameters for the application you want to start. Optional because not all applications actually read the command line parameters. Besides: All command line parameters which are not for XpaRunner itself will be removed and all others will stay, resp. will be forwarded to the target application

### Parameter: WORKINGDIR
Working directory setting for the application which gets started. If empty or missing XpaRunner will set the working directory to the path it has from the EXE parameter (where that exe resides). This it however does only if you did specify a full pathname. If its only a filename with or without extension like "java", it will be windows which sets the 
working directory.  

### Parameter: ENVEXPAND
_Only makes sense if one (or more of) the command line parameters for the target application (Magic XPA Studio or Runtime in our case typically) starts with an @ sign.  
Which is interpreted as the prefix to declare a "Magic @INI Merge file"._

If XpaRunner detects such a @INI **and ENVEXPAND is set**, it will automatically "expand" all variables in the @INI which are surrounded with % signs by the value the system environment variable with the name matching this variable name has - if a environment variable with that name exists. Efectively this means: Where you now can only use Magic logical names in your .INI you now can use environment variables too. %HOMEDRIVE%%HOMEDIR% would be expanded to C:\ f.i. .  

_An issue with this you would only get if there's Magic logical names and (system) environment variables with the same name. This case is currently not handled and there is no escape mechanism. Its about the @INIs only anyway. The Magic.INI with the rest of your settings won't be touched by XPaRunner anyways_.  
  
If a @INI is modified by XpaRunner, XpaRunner works on a copy which it will create in user's temp directory. The original @INI will stay as it is, it will however be removed from the command line parameters and will be replaced by the (changed) version from temp directory.

If XpaRunner is configured to wait for the process it started to terminate (see WAIT option), it has a chance to delete that tempfile. If it will just spawn the process and then exit immediately (default behaviour), the file will stay in temp directory and you 
have to take care that these files get deleted once a wile yourself. You can use parameter / setting INIDIR to overwrite the output directory for this temporary files to a drive / directory where you centralize these files. 
 
## Parameter: INIDIR
See remarks for option ENVEXPAND. With this setting you can overwrite the output folder for temporary @INI files, which by default go to the user's temp directory (%TEMP%). XpaRunner will ensure unique names for files it creates in this directory - even if multiple users share this INIDIR setting.  

## Parameter: WAIT
By default XpaRunner starts the target process from EXE parameter and terminates. By specifying -WAIT on the command line you can advise XpaRunner to keep running and wait for the process it started to terminate. It then can remove temporary files it created and exit too.  

Basically its possible to do some housekeeping now and check if the application XpaRunner started terminated "gracefully" or crashed. That feature is however not yet implemented. 

# Instance handling
"Instance handling" is a feature from a predecessor Version which did not make it into first version of XpaRunner. It helps when you have an application where the users tend to start multiple instances of your application and you want to identify these and need some 
(e.g.) "instance specific temp. directories". That requires some coordination of the running instances (since users can continue to to start instances and can terminate some while continue to work with others). Information about the instance you get in Magic application as command line parameter and/or .INI setting and you can f.i. add this "id" to the title bar of your application - which is a surprising nice feature when you \<alt\>\<tab\> fast between instances of your application on Windows ;).  

You can also use this feature to limit the maximum number of instances a user is allowed to create and if you set it to one, you effectively limited the number of possible  instances to 1, which helps if multiple instances cause issues, as it is often the case for applications with a lot of I/O on lacal drives.

# Further Notes

Processes which XpaRunner creates are started with Process.Start method from System.Diagnostics

Samples for XpaRunner.settings files you will find in the XPATEST root directory:  
+ StartRuntime.settings
+ StartStudio.settings
+ XpaTest.settings

## Fun fact
The initial version for XpaRunner I did clone from the Firefly github repository, an application named [AppRunner](https://github.com/FireflyMigration/AppRunner). So this is my credits. Todah Rabah!!  

Firefly migrations is the guys from Israel which constantly tell Magic Programmers to stop with it and use their technology to automatically migrate existing Magic applications to .NET resp. C#. 

Personally I had quite a complete Magic startup application but decided to build a new one from scratch. Code is almost 20 years old and MFC based C++. Not worth the migration efforts and it has issues with Unicode and portability to 64-Bit.

