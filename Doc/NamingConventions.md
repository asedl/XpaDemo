# naming conventions

## program names
The naming of the programs is a bit cryptic but that eases at the end referencing and usage in URIs or filenames. Only names of "important" programs will follow these naming conventions ... that's those fow which documentation exists (which requires then this naming)  

A (documented) program name has to adhere following syntax:  
  
   \<program type\>\<module\>\<running number\>_\<descriptive name\>  
  
**program type** :=  
   "O" (Online, program has a GUI and can be started without preconditions)  
   "B" (Batch, batch program without a GUI. Typically cannot be started "as is" because it requires parameters, ...)  
  
**module** :=  
   "functional area". Currently there is:  
      "XMLT" := XML / XSL / XSLT / XQuery stuff  
      "UTIL" := Utility programs used all over (like programs for display of information in an embedded browser, ..)   
      "WCLN" := "Web Client", here is the http stuff  
      "OFFI" := (Microsoft) Office stuff like Excel->CSV with program BOFFI001_ConvertExcelDir  
  
There's also interface programs in components which will have the components (short) identifier as the module specifier:  
+ "ROSL" := Roslyn component with stuff around code analysis / compilation
+ "OFFI" := Office component  
  
**running number** :=  
   running number unique inside the model. Sometimes there's big gaps between the numbers. That's an indication that there will be more between so that a "family" of programs (of which not all are implemented yet) can get running numbers close to each other forming a number cycle.  
  
**descriptve name** :=  
   free text which allows a brief description of the functionality (its hard to memorize the program codes). Unfortunately not much space left for that - a Magic program name can have 40 characters max.  
  
Note that the program name needs to be URL-safe because its used in URLs (and filenames). Do not use special characters which require to be escaped on a URL or which are invalid for a filename. Exception is programs which do not start with above pattern <program type><module><running number>_  at all. Those you can name like you want.  
    
If a program name starts with a hyphen character the program implements parts of a program above resp. depends on that. If you move a program in the program repository be sure to move these dependencies then too.
