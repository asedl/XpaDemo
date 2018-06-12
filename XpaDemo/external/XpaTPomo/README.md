# XpaTPomo
XpaTPomo is a (quite ambitious) subproject / module / component of XPATests with the goal to add a framework /SDK for dependency injection and aspect oriented programming to Magic XPA. The term "POMO" stands for (in analogy to Java's POJO): "**p**lain **o**ld **m**agic **o**bject".  

Reason: Magic XPA is very limited when it comes to what is required here, "Reflection", the ability to analyze and modify programs/applications during Runtime. But, at least, Sources are "XML" since a while so we actually can analyze and modify those in order to add some stuff by using "annotations". 

__Until Magic v8 there was a "Magic control file API" which is, to some extend, exactly what we do need, that was however discontinued in some Magic 8.3 version. Part of the XpaTPomo project is therefore exactly that: A "Magic XPA control file API" based on the projects XML sources.__

XpaTPomo project is in a very early stage and maintained as a Eclipse based SDK in order to use that infrastructure for installation/configuration of the single components and maybe for some plugins. Eclipse you have to download and install seperately. The Eclipse project named Pomo_SDK you can find here: https://github.com/asedl/xpaxmltest/tree/master/XPATests/external/XpaTPomo/Pomo_SDK/  

## Directory Structure
| --- | --- |
| Pomo_SDK | Eclipse based project |
| Schemas / Xpa | Magic Schema files for XPA applications which do ship with the product | 