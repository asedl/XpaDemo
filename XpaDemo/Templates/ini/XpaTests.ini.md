# Templates/ini/XpaTests.ini

[XpaTests.ini](XpaTests.ini)  
  
XpaTests.ini in folder /Templates/ini is a (Magic merge) template used in program [OUTIL003_CheckConfiguration](XPATests\Doc\Samples\XpaTDemo\OUTIL003_CheckConfiguration.md) to generate a Magic @INI named XpaTests.ini which it will put in the application root directory and which then can used on command line of a Magic XPA Runtime or -Studio in order to add the settings from this file to the configuration.  

It is a "Magic Merge template" so it (can) contain Magic Merge variables (tags) which will be expanded when OUTIL003_CheckConfiguration runs. You cannot simply add aarbitrary Magic merge tags to this file but only those which actually are handled in that Magic program. If you add or rename tags you need to adjust that program.  

Currently OUTIL003_CheckConfiguration handles following Merge variables:  
# XPATEST_HOME
Will be used f.i. in following line from the template to set the value for logical name XPATEST_HOME.  
OUTIL003_CheckConfiguration puts here the value of %WorkingDir%, the project directory which the Magic runtime environment exposes as logical name and which will always be set as soon as a Magic application (.ecf) gets opened by a Runtime engine.
/[MAGIC_LOGICAL_NAMES]XPATEST_HOME=*<!$MG_XPATEST_HOME>