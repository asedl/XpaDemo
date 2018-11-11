# OXMLT001_ExportCustomers
  
  OXMLT001_ExportCustomers is an onile (line mode) browse program for table Customers in sampledatabase RIADEMO . It displays the content of that table and has some buton(s) to perform some actions.

  It's a demo for following components of XPATEST project:
  * XSLT transformations with class XMLProcessor from package com.magic.examples.xml

## Buttons
### Export to XML
Saves the list of Customers to XML by means of Magic function DataViewXML() and then calls program BXMLT001_Transform (XSLT) to perform a XSLT transformation on that file. The result of this transformation is displayed in an embedded browser

See documentation of com.magic.examples.xml.XMLProcessor for further details regarding XSL/XSLT features and their implementation.