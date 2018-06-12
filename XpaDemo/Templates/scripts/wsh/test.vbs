Set Shell = CreateObject("WScript.Shell")
strFolder = "C:\magic\samples\xpaxmltest\XPATests\"
Set link = Shell.CreateShortcut(strFolder+"Start XPA Studio (XpaTests).lnk")
link.WindowStyle = 4 
link.TargetPath = "C:\magic\Magic XPA 3.3\MgxpaStudio.exe"
link.Arguments = "\@""C:\magic\samples\xpaxmltest\XPATests\XPATests.ini"""
link.WorkingDirectory = "C:\magic\Magic XPA 3.3"
link.Save
