# OPOMO001_ScanXpaProject

OPOMO001_ScanXpaProject is a test/demo program for XpaTPomo functions which deal with XPA (project) sources. 

## Screen
![OPOMO001_ScanXpaProject](../../Screens/OPOMO001_ScanXpaProject.png)

## Fields
### Project (edp)
Allows you to specify a XPA project file. You can either type the full pathname or press F5 to zoom into a FileOpen Dialogue.
  
## Buttons
### Scan project
Runs program xpa_project_scan.BPOMO001_ScanProject with the filename specified in "Project (edp) as parameter. The project file and it's dependencies will be scanned and the result will be written to a database table 

### Scan Result
Calls program xpa_project_scan.OPOML002_ShowXpaProject to display the result of a previous project scan in an online (line mode) browse program
