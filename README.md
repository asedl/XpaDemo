# Magic XPA (SingleUser) demo project XpaDemo

This is a repository with a growing collection of Magic XPA demos / samples with a strong focus on the exotic stuff. If you do want demos / samples in order to actually learn "Magic" you should download and install (latest version) of Magic XPA and first have a look into the samples and demo applications which do ship with that (also exotic) development tool.

It's rather pricey and requires you to pay for runtime licenses later on, when you want to deploy your applications, too, there is however - since a while at least - a free "Single User" edition. That version lacks support of all the "enterprise features" and does support SQLite with a database gateway only. You can download that edition from following link (requires registration):  
<http://info.magicsoftware.com/Magic-xpa-Free-Single-User-Edition> . There's also a website from Magic Software which is exclusively about this special, free, version of their development tool. Its a bit old and seems not maintained anymore, many links do not work there and the "Magic DevNet" has basically been discontinued as it looks: <http://homeedition.magicsoftware.com/> . 

The IDE (aka: "Magic XPA Studio") is only available for Microsoft Windows. The applications you do build with Magic XPA do then run on some different systems / platforms too and if you keep it "Single User" you can also deploy your applications for free and do not have to purchase runtime licenses from the vendor. Its interesting technology, esp. the RIA things and quite different from everything else in that area but maybe worth a look. It's rather "B2B" though.

## User Group / Community
The (international) "Magic User Group" basically is organized around a Mailing list named "magicu-l" which currently resides here: <https://magicu-l.groups.io> . That's definitely the best place when you do look for help with Magic Xpa (or any other Magic version or product). 

# Installation / Configuration
  
In order to be able to start the demo application(s) included in this package you do need to have Magic XPA 3.3 installed. If you do not have this version you can download and install the free Magic XPA SingleUser edition of that development tool from the link above. Next to this, there's basically no mandatory installations required, for specific samples / functionality you will however need to have some additional software installed or binary components which are not part of the source distribution, which you get if you clone the repository from github or download the sources from there as PKZIP archive. If you can build these components yourself you are fine with the source distribution, if not (or to get started fast), you should download a released version, which does only contain the binaries and support files, but not the sources. A step-by-step description for an installation from a released version you can find here: [Installing and running XpaDemo project from a release](https://github.com/asedl/XpaDemo/blob/master/Doc/Installation/InstallationFromRelease.md)

Once you have that running you can download the sources or clone the git repository in order to look into the implementation of this stuff. Regarding the installation from source distribution you will find some more information here: [Installing and running XpaDemo project(s) from a source distribution](https://github.com/asedl/XpaDemo/blob/master/Doc/Installation/InstallFromSources.md)


# Content

Currently this project contains following top-level samples / demos / modules, maybe only stubs with not much implemented yet: 

| Demo / Subproject    | Brief description
| -------------------- | ----------------- |
| [XpaDemo](XpaDemo/) | Goal is basically a small Framework for more complex Magic applications which does autoconfigure itself |
| XpaTHttp | https://github.com/asedl/XpaDemo/tree/master/XpaDemo/Doc |
| XpaTOffice | There's some samples which do use functionality from Apache POI for MS Office stuff like converting Excel -> CSV for an easy import into Magic without the requirement to have MS Office actally be installed |
| XpaTXML | There's some samples which do demo "advanced" XML technics, like XSL/XSLT/XQuery for reformatting of existing XML to whatever or extracting information from there with standard query languages |  
XpaTPomo | "POMO" is a new term invented for this project in analogy to Java POJOs, a "plain old Magic object". Goal is to get a (compile time) framework for Magic XPA applications in order to enable dependency injection and aspect oriented programming |
| XpaTHelp | Component which can be added to Magic programs to integrate/implement an online help system |
  
some more stuff is in the pipeline. Initial versions not yet commited to this repository.

| Demo / Subproject    | Brief description
| -------------------- | ----------------- |
| XpaTBuild | Maven multi-module project + required stuff to get a Magic application (or parts of it) deployed with standard build systems / continouus delivery piplines / Jenkins / .... |

