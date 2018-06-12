# OUTIL002_Components

OUTIL002_Components is an online (line mode) browse program for XPATEST database table xpatest_components
where we store some configuration information. The information is not only displayed here,
it also gets validated. The program can be used to configure XPATEST and helps with fixing
a broken installation.  

  Status: TODO (most of it)   

## Screen
![OUTIL001_About](../../Screens/OUTIL002_Components.png)

## Description

Basically all components listed in that screen have to be considered different and require special handling when it's about their installation or configuration.  

If it's a component with type=X (executable) and the location_absolute of it is either missing or invalid, the program will check if it can find the program in the system PATH by checking all directories where PATH points to.  
For that search the component's name will be used. So if you f.i. installed CURL on your system and modified the PATH curl.exe will be found and it's location will be stored here. 


