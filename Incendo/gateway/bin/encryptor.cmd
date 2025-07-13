@ECHO OFF

IF "%OS%" == "Windows_NT" setLocal
IF "%OS%" == "WINNT" setLocal

rem IF "%1" == "" goto usage

call "%~dp0/launcher" -cp "%~dp0/../config;%~dp0/../lib/iutil.jar;%~dp0/../lib/common/log4j-1.2.13.jar" -Doegw.log.dir="%~dp0/../log" com.ingenico.util.configuration.SecureProperties %*
IF "%OS%" == "Windows_NT" endLocal
IF "%OS%" == "WINNT" endLocal
GOTO :eof

:usage
ECHO Usage: %~nx0 filename masterphrase