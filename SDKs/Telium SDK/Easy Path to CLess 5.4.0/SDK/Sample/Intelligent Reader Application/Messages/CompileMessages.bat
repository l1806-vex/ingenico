@echo off

set SDK_DIR=%ProgramFiles%\TeliumSDK\SDK 9.8.1\tools\MSG tool

rem ===========================================================
rem
rem  generate English Messages
rem
rem ===========================================================

rem 1- convert h file to MSG file

"%SDK_DIR%\BuildMSG" -c -tSDSA_msgEnglish.h -hSDSA_MessagesDefinitions.h LANG.MSG


rem ===========================================================
rem
rem  generate French Messages (same command as previous without -C)
rem
rem ===========================================================

"%SDK_DIR%\BuildMSG" -tSDSA_msgEnglish.h -hSDSA_MessagesDefinitions.h LANG.MSG

rem ===========================================================
rem
rem  sign LANG.MSG before loadind it in the terminal
rem
rem ===========================================================


rem 2- create LANG.c file to include in the sample
"%SDK_DIR%\MSG2C" LANG.MSG SDSA_Messages.c

move /y SDSA_MessagesDefinitions.h ..\Inc
move /y SDSA_Messages.c ..\Src

pause
