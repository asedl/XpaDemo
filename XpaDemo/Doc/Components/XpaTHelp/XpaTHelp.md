# XpaTHelp
XpaTHelp is a "Help System system interface component" which is partly based on annotations and in XpaDemo project(s) it is f.i. used for the some help features (Online Help). It's not hard coupled to XpaDemo project, you should be able to use this component in your own projects as well - with no or only minor changes/configuration required.  

# Annotations

## @XpaTHelp (RetentionPolicy.RUNTIME, RetentionPolicy.COMPILE)
## @XpaTHelp.URL (XpatHelp.hid)
Allows you to specify a URL which gets invokes when you press F1. You can either get the value of that URL automatically fetched from the helpsystem by specifying a "help id" as a compile time attribute or by explicitely setting XpaTHelp.URL to a URI. If the user presses F1 in a program XpaTHelp component will find this variable (annotation) and jump to the online help for this program. 

# Models
## XpatHelp.hid (object-id, numeric)
Unique id of a XpaTHelp "help object". XpatHelp.hid is f.i. used in table XpaTHelp.xhlp_object where all "help objects" used in a project have to be stored, in order to be used in the help system provided by XpaTHelp. 

# Examples
## 


