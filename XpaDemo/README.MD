# XpaDemo

XpaDemo is the main component of this project and it serves as demo container resp. demo Framework. Everything which belongs to this application resides in this directory or below and you need to ensure that logical name __%XPATEST_HOME%__ points to this directory

Documentation / Descriptions of the demo programs you will find in [Doc/Samples](Doc/Samples).  
  
  > Note that also all the .ecf (Magic XPA cabinet files) which basically should be consideed "binaries" do reside in the root directory
  of this application while they probably should better go to a "bin" directory which is set to read-only and where you can enforce
  different permissions, ... .  
 
  > That's however not that easy because we want that a user just has to double-click the XpaDemo.ecf in order to start the application and then we might not yet have enough information to fix the pathnames for components and other stuff (database files, ...). This issue will be addressed soon.  
  
## Directory structure
| Name | Content |
| --- | --- |
| Components | Magic XPA components |
| [Data](Data/) | Database files (SQLite, XML, ...) |
| [Doc](Doc/) | Documentation |
| Samplefiles | |
| Source | Magic XPA sources of XpaDemo project |
| Templates | Various templates for the scripting samples / framework |
| external | None-Magic-XPA subprojects/code (Java, .NET, ... |
| Temp | application's global Temp directory (git ignored). Programs might also use system TEMP directory or user's TEMP (XPA: %TempDir%) for output of temporary files |

## XpaDemo.ini
[XpaDemo.ini](XpaDemo.ini) is a "Magic @Merge .INI file". Its only a partial .INI which get's "merged" into the Magic.INI file during startup if you put it on the commandline (of your shortcuts), prefixed with an @ sign. Syntax is very similar to a regular .INI with a few caveats which you find documented in the Magic XPA helpfiles. All .INI settings required by the XpaDemo application/project (or one of it's components/modules) you will find here. Currently this is not much and we might factor it out completely by adding database settings and other stuff in there during startup.






  
