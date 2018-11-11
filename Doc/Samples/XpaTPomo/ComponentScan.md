# Scanning for Magic XPA Components
Some of the components in XpaTPomo require a recursive scan for (Magic XPA) components. Starting point for this component scan is the XPA project file (*.edp) of the (host) application resp. of a component. The components which are hosted by that application are listed in \<ProjectDir\>\\<Source\>\Comps.xml. \<ProjectDir\> is the directory where the project file (*.edp) resides, \<source\> is the name of the (sub-) directory with the application's sources. It's named "Source", when you create a Magic application with XPA Studio. This name can be changed and can be configured in the .edp file (-> /Application/_Project/SourceDirectory@val)  

XpaTPomo can only check a component for nested components if it knows where the sources of that component actually reside resp. when it knows, where the project file used to create the component is located. This information it gets from the MciFile@val attribute of a component object (element). Xpa sets this attribute when you add a component by selecting an .eci file. MciFile is however not a mandatory element of a Component object. If it's missing (or invalid) XpaTPomo cannot parse the .eci file in order to fine the component's sources.  

If you want that the component search in XpaTPomo finds all components used/referenced in your application (component), you need to take care that the information in the .eci files is accurate and that the .eci value PROJECTFILE has a value which points to the project folder of the component. 

Magic checks/sets the MciFile@val attribute of component objects (elements) only when you load/reload a component of type="Magic XPA" in CRR of XPA Studio. During runtime it does not need that information, it loads the .ecf file of a referenced Magic XPA component (attribute: Component\CABINET_FILE@val) and then does directly access the components interface from the .ecf file.



