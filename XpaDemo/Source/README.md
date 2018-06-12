# Source \/

This is a Magic XPA "Source" directory. Magic XPA creates such a source directory (collection of XML files) whenever you create a XPA project
(XPA application). Location of this source directory is specified in the application's .edp (eDeveloper project file), which typically resides 
in the parent folder. [XpaDemo.edp](/XpaDemo/XpaDemo.edp) - in our case (see value "SourceDirectory" there).  

The format of the sources is proprietary and may change with every version of Magic XPA. Magic XPA ships with XML schema files for the sources 
which do describe their content.  

Since a while, when you create a Magic application, you will always also find Visual Studio solution / project files in your application directory. These are (probably) required for the Magic XPA Forms editor, which is (since XPA 3.x) actually from an (embedded) Visual Studio. Maybe these files serve different purposes too, like for the build process, maybe XPA is meanwhile completely Visual Studio based and we can rely on the existence of these project definition files, that's not yet clear. Besides there's also the "Magic Builders" which you do need when you deploy your Magic application / component as a webservice or as a mobile application,  ... . Those will generate a project for the target plattform too and then use the build tools of that platform in order to get the application up and running resp. integrated with a Magic backend. We will shed some light into this, esp. if its about deployment of RIA applicatuions / components to Android (mobiles).

## Team development / Version control

Magic XPA SingleUser has the "team development" feature disabled and even if it would be enabled, or you have a full version, team developmen is an issue, due to the usage of "indexes" in these source files, where entiities (models, programs, tables, ...) are not referenced by a unique name (guid) but an index - which is only unique inside a specific repository.  

Concurrent development where developers do their changes in parallel (offline) and resolve merge conflicts when they check-in / commit their changes is therefore not possible with Magic. Magic XPA also only supports those MVCS systems which do provide a MS SCC Api (and allow to disable multiple checlouts of objects).  

For this demo-project we do version the complete project with git on github. Push requests and forges will result in Merge conflicts which are very hard to resolve with Magic XPA due to the thing with the "indexes" explained above. Meanwhile there is some third party products  which do help a lttle with these issues a bit (Magic Optimizer / Magic Compare).  

Also in this project it's planned to add some tools which do work on "Magic sources" in order to be able to refactor them. Check the [XpaTPomo](https://github.com/asedl/XpaDemo/tree/master/XpaDemo/external/XpaTPomo) project.

# Magic XPA (source) Repositories and -files
## \<your project\>.edp
Sample: [XpaDemo.edp](/XpaDemo/XpaDemo.edp)

## \<your project\>.opt
Sample: [XpaDemo.opt](/XpaDemo/XpaDemo.opt)

## [Components](Comps.xml)
Sample: [XpaDemo.Comps.xml](/XpaDemo/Comps.xml)

## [Data Sources](DataSources.xml)
Sample: [XpaDemo.DataSources.xml](/XpaDemo/DataSources.xml)

## [Data Sources Indexes](DataSourcesIndex.xml)
Sample: [XpaDemo.DataSourcesIndex.xml](/XpaDemo/DataSourcesIndex.xml)

## [Helps](Helps.xml)
Sample: [XpaDemo.Helps.xml](/XpaDemo/Helps.xml)

## [Menues](Menues.xml)
Sample: [XpaDemo.Menus.xml](/XpaDemo/Menus.xml)

## [Models](Models.xml)
Sample: [XpaDemo.Models.xml](/XpaDemo/Models.xml)

## [Program Headers](ProgramHeaders.xml)
Sample: [XpaDemo.ProgramHeaders.xml](/XpaDemo/ProgramHeaders.xml)

## [Programs](Progs.xml)
Sample: [XpaDemo.Progs.xml](/XpaDemo/Progs.xml)

## [Project properties](ProjProps.xml)
Sample: [XpaDemo.ProjProps.xml](/XpaDemo/ProjProps.xml)

## [Rights](Rights.xml)
Sample: [XpaDemo.Rights.xml](/XpaDemo/Rights.xml)
  
  
# Visual Studio solution / project files
## \<your project\>.sln
[XpaDemo.sln](/XpaDemo/XpaDemo.sln)

## \<your project\>.xpaproj
[XpaDemo.xpaproj](/XpaDemo/XpaDemo.xpaproj)

