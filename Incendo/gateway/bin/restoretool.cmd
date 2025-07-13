@ECHO OFF

call "%~dp0/launcher" -cp "%~dp0/../config;%~dp0/../lib/oegw.jar" -Doegw.log.dir="%~dp0/../log" com.ingenico.oegw.server.clear.RestoreTool %*
set exitcode=%errorlevel%

exit /b %exitcode%
