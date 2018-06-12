# Magic XPA tools infrastructure
There's some samples which utilize the Magic XPA tools infrastructure. Thats the "Magic XPA plugin interface" which allows you to integrate your own tools (or from 3#rd party) into the Studio (IDE). It's documented here: http://kb.magicsoftware.com/articles/bl_Reference/Tools-Infrastructure-xpa  

A sample component in XPATest project which has an optional "Xpa TOOLS interface" is the xpa_project_scan XPA component from XpaTest.XpaTPomo project.  

This component is loaded as a TOOL in the Studio by specifying it in the Magic.ini in [MAGIC_TOOLS] section. In XpaTest project we do this by adding it to the [@INI XpaTest.ini](/XPATests.ini).  

```Magic.ini
[TOOLS_MENU]
Compile=A,xpa_project_scan,,+
C:\magic\samples\xpaxmltest\XPATests\xpa_project_scan.ecf,,+
C:\magic\samples\xpaxmltest\XPATests\Templates\scripts\xpaps\compile_before.xpts,+
C:\magic\samples\xpaxmltest\XPATests\Templates\scripts\xpaps\compile_after.xpts,
```

Above will add a Manu named "Tools" to your Studio. First entry in that menu will be an item named "xpa_project_scan". When you select that menu entry it will load the component C:\magic\samples\xpaxmltest\XPATests\xpa_project_scan.ecf and thereby execute program main in that component.  

Before the component is actually loaded Magic tools infrastructure will execute the operations in C:\magic\samples\xpaxmltest\XPATests\Templates\scripts\xpaps\compile_before.xpts and when you close the tool application it will execute the operations in C:\magic\samples\xpaxmltest\XPATests\Templates\scripts\xpaps\compile_after.xpts.   

When you close the tool application (which might have a UI) Magic Studio re-opens the host application, that's the one which was closed when you selected "xpa_project_scan" from Tools menu.  

More information regarding the xpa_project_scan component, its TOOL features and the rest of it's functionality you can find [here](/Doc/XpaTPomo/xpa_project_scan.md).


