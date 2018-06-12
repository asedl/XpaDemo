# XpaCompile

XpaCompile is a command line "compiler" for Magic XPA projects. It uses the [Magic XPA tools infrastructure](http://kb.magicsoftware.com/articles/bl_Reference/Tools-Infrastructure-xpa) to create a Magic XPA cabinet file (*.ecf).  

Status: **Not done**

# Usage / command line parameters
XpaCompile.exe -project=c:\magic\samples\xpaxmltest\xpatest\xpatest.edp

## Parameter: project
Allows you to specify a Magic XPA project file (.edp).

## Parameter: ecf
Allows you to specify the (full path-) name of the Magic XPA cabinet file which will be created as the result of the "compilation". This parameter is optional, if you leave it aways, name of the resulting .ecf file will be the name of the project file with extension .ecf.

#Implementation details
XpaCompile uses the [Automatic Processing features of the "Magic XPA tools infrastructure"](file:///C:/magic/Magic%20XPA%203.3/Help/index.htm#t=mergedProjects%2FMGHELPW%2FUtilities%2FAutomatic_Processing.htm) in order to be able to create / compile an .ecf for a Magic XPA project resp. Magic XPA "sources". This requires you to have a Magic XPA Studio installed (which can deal with the Magic XPA version of your project).  

XpaCompile simply creates the **"AutomaticProcessingSequenceFile"** and then starts Magic in background mode in order to process that file  

Compilation is a "deep scan" of the project file. If there's components and the component sources resp. projects can be accessed because the .edp specification is valid (not a requirement for a Magic application to run) these projects will be compiled too. XpaCompile detects recursion and stops looking deeper when a component (project) has already been processed. Components / projects are identified by their GUID (which they do get when you create the project)  

Having a command-line compiler for Magic projects does not only allow you to do batch-builds for all the components forming an application, it also allows you easier integration with build- and package managemnt systems.  

 