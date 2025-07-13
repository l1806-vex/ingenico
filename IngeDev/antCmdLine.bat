@echo off
rem ****************************************************************************
rem * antCmdLine.bat
rem ****************************************************************************

if %1.==. goto Help
if %2.==. goto Help

set WORKSPACE_DIR=%1
set BUILD_FILE_PATH=%2
set ANT_TARGET=%3

rem ----------------------------------------------------------------------------
rem  Check Ant target file exists
rem ----------------------------------------------------------------------------
if exist %BUILD_FILE_PATH% goto LaunchCommand

set BUILD_FILE_PATH=%WORKSPACE_DIR%%BUILD_FILE_PATH%

if exist %BUILD_FILE_PATH% goto LaunchCommand

echo Cannot find "%2" Ant script!
goto End

rem ----------------------------------------------------------------------------
rem  Launch command
rem ----------------------------------------------------------------------------
:LaunchCommand
echo Workspace=%WORKSPACE_DIR%
echo Build Script Location=%BUILD_FILE_PATH%

if %ANT_TARGET%.==. (
echo Calling the default Ant Target...
) else (
echo Calling the "%ANT_TARGET%" Ant Target...
)

"IngeDevc" -data %WORKSPACE_DIR% --launcher.suppressErrors -nosplash -application org.eclipse.ant.core.antRunner -buildfile %BUILD_FILE_PATH% %ANT_TARGET%

goto End

:Help
echo. 
echo usage:
echo  antCmdLine {workspace_location} {ant_script_location}  [{ant_target}]
echo.
echo  workspace_location   : the workspace location
echo                         (example: "D:\Eclipse Dev\myWorkspace") 
echo  ant_script_location  : the Ant script absolute path
echo                         (example: "D:\Projects\myProject\Ant\build.xml")
echo                         or the Ant script relative path to the specified
echo                         workspace location (example: "\myProject\Ant\build.xml"
echo                         for file located in
echo                         "D:\Eclipse Dev\myWorkspace\myProject\Ant\build.xml")
echo  ant_target (optional): the Ant target to execute.
echo                         If not present the default target will be executed.
echo.

:End
echo on
