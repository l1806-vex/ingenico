@echo off

set SDK_DIR=%ProgramFiles%\TeliumSDK\SDK 9.8.1\tools\MSG tool

rem ===========================================================
rem
rem  generate English Messages
rem
rem ===========================================================

rem 1- convert h file to MSG file

"%SDK_DIR%\BuildMSG" -c -tCST_msgEnglish.h -hCST_MessagesDefinitions.h CST.MSG


rem ===========================================================
rem
rem  generate French Messages (same command as previous without -C)
rem
rem ===========================================================

"%SDK_DIR%\BuildMSG" -tCST_msgEnglish.h -hCST_MessagesDefinitions.h CST.MSG

rem ===========================================================
rem
rem  sign CST.MSG before loadind it in the terminal
rem
rem ===========================================================


rem 2- create CST.c file to include in the sample
"%SDK_DIR%\MSG2C" CST.MSG CST_Messages.c

move /y CST_MessagesDefinitions.h ..\Inc
move /y CST_Messages.c ..\Src

pause
