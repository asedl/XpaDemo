# OOFFI001_ConvertExcelDir

This program demos part of the "Office" functionality which is impmented in Java package com.magic.examples.office . The program will scan a directory with sample Excel files and display the content of this directory in a line mode browse program. There then is buttons which allow to perform actions on the Excel files.  
  
## Buttons
### ToCsv
Calls program BOFFI001_ConvertExcelDir with two parameters:  
* the currently selected filename from the table with the dirscan result
* Pathname of an (existing) directory for the output

See doc of BOFFI001_ConvertExcelDir for further details. BOFFI001_ConvertExcelDir checks if the first parameter is actually a file - or a directory. If its a single file, only that file will be converted to CSV, if its a directory - all files in that directory will get converted to CSV.

For that reason the directory scanner implemented in BOFFI001_ConvertExcelDir injects an additional record: the name of source directory itself. By invoking "ToCSV" on that record you can test the bulk feature of BOFFI001_ConvertExcelDir.  
  
  When BOFFI001_ConvertExcelDir returns the second parameter for it (the name of output directory) is passed to OUTIL100_EmbeddedBrowser which will display the content of that directory nicely in an embedded browser.
  
## Known issues
The Excel samples which ship with the demo application in %XPATEST_HOME%Samplefiles\Excel do contain samples for XLS (old excel format), XLSX (new format) and XLSM (new format, macros enabled). Basically the Excel->CSV converter can convert all of them to CSV, just if you run it in "bulk mode" with a directory name it will only consider XLS and XSLX. XLSM it will skip, that you would have to convert separately.


