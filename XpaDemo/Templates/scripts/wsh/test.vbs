Set Shell = CreateObject("WScript.Shell")
strFolder = "C:\xpa\samples\XpaDemo\XpaDemo\"
Set link = Shell.CreateShortcut(strFolder+"Start XPA Studio (XpaDemo).lnk")
link.WindowStyle = 4 
link.TargetPath = "C:\magic\Magic XPA 3.3\MgxpaStudio.exe"
link.Arguments = "\@""C:\xpa\samples\XpaDemo\XpaDemo\XpaDemo.ini"""
link.WorkingDirectory = "C:\magic\Magic XPA 3.3"
link.Save
