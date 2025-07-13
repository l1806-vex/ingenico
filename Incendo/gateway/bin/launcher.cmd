@ECHO off
set JAVA_LAUNCHER=java

if exist jre\bin\java.exe set JAVA_LAUNCHER=jre\bin\java.exe
if exist jre\bin\server set JAVA_LAUNCHER=jre\bin\java.exe -server

%JAVA_LAUNCHER% %*