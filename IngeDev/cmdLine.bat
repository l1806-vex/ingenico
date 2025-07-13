@echo off
rem ****************************************************************************
rem * cmdLine.bat
rem ****************************************************************************

set IMPORT_APP=importProject
set GEN_BUILD_FILES_APP=generateBuildFiles

if %1.==. goto Help
if %2.==. goto Help
if %3.==. goto Help

if "%1"=="%IMPORT_APP%" (
	set PLUGIN_COMMAND_LINE=com.ingenico.ingedev.generic.commandlinetools
	goto AppliOk
)
if "%1"=="%GEN_BUILD_FILES_APP%" (
	set PLUGIN_COMMAND_LINE=com.ingenico.ingedev.commandlineapplications
	goto AppliOk
)

echo The application '%1' does not exist! (available applications are '%IMPORT_APP%' and '%GEN_BUILD_FILES_APP%')
goto End

:AppliOk
rem ----------------------------------------------------------------------------
rem  Set Eclipse Home
rem ----------------------------------------------------------------------------
set ECLIPSEHOME=.

rem ----------------------------------------------------------------------------
rem  Get path to equinox launcher jar file
rem ----------------------------------------------------------------------------
FOR /f "delims= tokens=1" %%c IN ('dir /B /S /OD %ECLIPSEHOME%\plugins\org.eclipse.equinox.launcher_*.jar') DO SET EQUINOXJAR=%%c

rem ----------------------------------------------------------------------------
rem  Launch command
rem ----------------------------------------------------------------------------
"%JAVA_HOME%\bin\java.exe" -jar "%EQUINOXJAR%" -application %PLUGIN_COMMAND_LINE%.%1 -data %2 -projDir %3 %4

goto End

:Help
echo. 
echo usage:
echo  cmdLine {application_name} {workspace_location} {project_location} [{other_option}]
echo.
echo  application_name   : the application name to launch ("importProject" or "generateBuildFiles") 
echo  workspace_location : the workspace location ("D:\Eclipse Dev\myWorkspace" for example) 
echo  project_location   : the project location ("D:\Ingedev Projects\myProject" for example)
echo  other_option       : additional option like "-d" for debug (optional)
echo.

:End
echo on

