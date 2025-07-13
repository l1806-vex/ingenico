@ECHO OFF

IF "%OS%" == "Windows_NT" setLocal
IF "%OS%" == "WINNT" setLocal

call launcher -cp "%~dp0/../config;%~dp0/../lib/iutil.jar;%~dp0/../lib/common/commons-codec-1.3.jar;%~dp0/../lib/common/log4j-1.2.16.jar" -Doegw.log.dir="%~dp0/../log" com.ingenico.util.byte_utils.DigestUtilityLancher %*
set exitcode=%errorlevel%

IF "%OS%" == "Windows_NT" endLocal
IF "%OS%" == "WINNT" endLocal
exit /b %exitcode%