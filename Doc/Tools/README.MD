# Tools

## XpaRunner

XpaRunner is a "startup utility" for Magic applications which can be used as an alternative to start Studio (MgxpaStudio.exe) or Runtime (MgxpaRuntime.exe).  

Reason for this is to get a possibility to prepare application startup, monitor a running Magic application (perform HEALTHCHECK), cleanup when the application did terminate (gracefully or not) and attach the Magic application to a console (STDOUT, STDERR) - 
when running the application from a command line processor (shell).  

Currently there is two versions of XpaRunner:
- [XpaRunner.exe](/external/Dotnet/XpaRunner2) (a .NET Frameweork command line process implemented in C#)
- XpaRunner.dll (a .NET Core command line application implemented in C#)  


