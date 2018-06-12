# xpa-project-scan

xpa-project-scan is a Magic XPA component which is part of the Magic XPA POMO SDK. It has some functionality which deals with XPA project- and source-files. Besides it exposes some of this functionality as a ["Magic XPA Tool"](/Doc/Samples/Misc/xpa_tools_infrastructure.md).  

## BPOML001_ScanXpaProject
Scans the sources of a given Magic XPA project file and fills database table XPATest_POMO.xpa_projectfiles with that information.  

## OPOML002_ShowXpaProject
Online (line mode) browse program which displays the content of database table XPATest_POMO.xpa_projectfiles and allows to perform some actions on entities there.  

## OPOML003_ShowXpaProjectComps
Online (line mode) browse program which displays the content of database table XPATest_POMO.xpa_tools_components and allows to perform some actions on entities there.  

## OPOML004_ValidateXml
Online (screen mode) demo program which allows to perform some actions around "XML Validation with Schema definition files"  

## BPOML050_CreateAutoprocSeqF
Batch Testprogram which generates a "autoprocess sequence file" for Magic Tools infrastructure in order to perform batch operations

## BPOML002_ScanXpaProject_Comp_C
Recursively scans a Magic component source file (Source\Comps.xml) for components. Information about the components found during travelling the project structure arew written to database table xpa_tools_components.  

## BPOML003_ScanXpaProject_Comp_P
Recursively scans a Magic project file for components. Information about the components found during travelling the project structure arew written to database table xpa_tools_components.  

