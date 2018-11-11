@echo off

rem ---------------------------------------------------------------------------
rem Start XpaDemo Sample SOAP server
rem
rem Environment Variable Prequisites
rem
rem   JAVA_HOME       Must point at your Java Development Kit installation.
rem
rem   JAVA_OPTS       (Optional) Java runtime options
rem ---------------------------------------------------------------------------
set CURRENT_DIR=%cd%

rem Make sure prerequisite environment variables are set
if not "%JAVA_HOME%" == "" goto gotJavaHome
echo The JAVA_HOME environment variable is not defined
echo This environment variable is needed to run this program
goto end
:gotJavaHome
if not exist "%JAVA_HOME%\bin\java.exe" goto noJavaHome
goto okJavaHome
:noJavaHome
echo The JAVA_HOME environment variable is not defined correctly
echo This environment variable is needed to run this program
echo NB: JAVA_HOME should point to a JDK/JRE
goto end
:okJavaHome

rem check the XPADEMO_HOME environment variable
if not "%XPADEMO_HOME%" == "" goto gotHome
set XPADEMO_HOME=%CURRENT_DIR%
if exist "%XPADEMO_HOME%\wsdl_first_https-3.2.4.jar" goto okHome

:gotHome
if exist "%XPADEMO_HOME%\wsdl_first_https-3.2.4.jar" goto okHome
echo The XPADEMO_HOME environment variable is not defined correctly
echo This environment variable is needed to run this program
goto end

:okHome
rem set the classes
setlocal EnableDelayedExpansion

rem ----- Execute The Requested Command ---------------------------------------
echo Using XPADEMO_HOME:   %XPADEMO_HOME%
echo Using JAVA_HOME:    %JAVA_HOME%
set _RUNJAVA="%JAVA_HOME%\bin\java"

REM %_RUNJAVA% %JAVA_OPTS%  %*
mvn -Pserver
endlocal
:end
