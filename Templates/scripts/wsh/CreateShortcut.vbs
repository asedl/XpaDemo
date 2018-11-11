Set Shell = CreateObject("WScript.Shell")
strFolder = "<!$MG_XPADEMO_HOME>"
Set link = Shell.CreateShortcut(strFolder+"<!$MG_LINK_FILENAME>")
link.WindowStyle = 4 
link.TargetPath = "<!$MG_ENGINEDIR><!$MG_ENGINE>"
link.Arguments = "<!$MG_TARGET_ARGUMENTS>"
link.WorkingDirectory = "<!$MG_WORKINGDIR>"
link.Save
