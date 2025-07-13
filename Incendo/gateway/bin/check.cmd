@ECHO OFF

pushd "%~dp0/.." || exit /b 2
call bin/launcher -cp "lib/cfgmsrv.jar;lib/oegw.jar" -Doegw.log.dir="log" -Djava.net.preferIPv4Stack=true com.ingenico.oegw.connector.RemoteControl %*
set exitcode=%errorlevel%

exit /b %exitcode%