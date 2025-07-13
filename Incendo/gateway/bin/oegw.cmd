@ECHO off

pushd "%~dp0/.." || exit /b 2
rem  use  in parameter to enable LDAP authentication
call bin/launcher -Djava.net.preferIPv4Stack=true -Doegw.log.dir="log" -jar lib/oegw.jar %*
set exitcode=%errorlevel%
popd
exit /b %exitcode%
