@echo off

set SDK_DIR=%ProgramFiles%\TeliumSDK\SDK 9.6.1\tools\MSG tool

rem ===========================================================
rem
rem  generate English Messages
rem
rem ===========================================================

rem 1- convert h file to MSG file

"%SDK_DIR%\BuildMSG" -c -tcu_msgEnglish.h -hMessagesDefinitions.h LANG.MSG


rem ===========================================================
rem
rem  generate French Messages (same command as previous without -C)
rem
rem ===========================================================

"%SDK_DIR%\BuildMSG" -tcu_msgFrench.h -hMessagesDefinitions.h LANG.MSG

rem ===========================================================
rem
rem  sign LANG.MSG before loadind it in the terminal
rem
rem ===========================================================


rem 2- create LANG.c file to include in the sample
"%SDK_DIR%\MSG2C" LANG.MSG cu_lang.c

move /y MessagesDefinitions.h ..\Inc
move /y cu_lang.c ..\Src

pause
