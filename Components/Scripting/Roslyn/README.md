# Roslyn.ecf / .edp
Magic XPA component which encapsulates some of the functionality of "Roslyn", the .NET Compiler platform.

Plan is to encapsulate some of the features of "Roslyn" resp. the .NET Compiler platform (shipping with the SDKs) as well as features of the .NET framework to allow code analysis and compilation inb order to use C# for scripting in Magic XPA applications without the requirement to install additional products (provided that you need a .NET Framework on a client machine anyways for a Magic XPA application).

## Motivation
Basically you can have .NET C#/VB snippets in your Magic XPA application ("Invoke .NET" operation) and Magic itself uses the .NET code providers in order to compile and execute these snippets, for more compex scripts resp. larger amounts of code this approach seems however not exactly pleasant. Besides, if you have some .NET code from somewhere, you cannot simply paste it in the Magic "Snipplet box", you will have to adjust it and it seems as if there's plenty of limitations of what you can use in that box and what you can't. Until today I was for instance not able to get "await" working, resp. did experience plenty of problems with Magic XPA snippets and asynchronous methods. That however might just be because I am neither a .NET expert nor did check very accurate which version of .NET actually gets used in my installations by Magic and/or what exactly is allowed inside that box, and what not. Namespaces f.i. are not.   
  
Another usecase is "Magic Merge Technology" which is used in a lot of existing applications in order to create script code "on the fly" based on templates (with or without Magic Merge Tags) and execute the result with (f.i.) the Windows command line processor (cmd) or Windows scripting hosts (wscript/csript). With C# code that's not that easy, it requires compilation.  
  
The Magic XPA Roslyn component also allows you to compile your C# (VB currently not planned to be supported) code to compile and link to a assembly (.exe) which can run in a seperate process.
