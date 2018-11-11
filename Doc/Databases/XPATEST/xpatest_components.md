# xpatest_components

Table xpatest_components contains a list of required components, system properties and optional or mandarory packages / 3'rd party software. It's used for checking the installation / configuration.  

## Fields
### id
unique id of the component (numeric)  

### name
(unique) name of the component, used as identifier as well in certain contexts

### type
component type with one of the following values:  
+ DB := database file
+ L  := Magic logical name
+ X  := Executable / Binary. 

### location relative
### location absolute
In case its a file-type component like one with a type=X for executables the location will get stored here. There's functionality in XPATEST which will try to find required components if the absolute path here is invalid or empty. Check [](../Samples/XpaTUtils/ OUTIL003_Components.md) for more information regarding that feature  

### description
brief description of the component entry

### existing
Used in the configuration program's. Will be set to Y there if the component exists and is configured properly so that it actually can be used in the application.

