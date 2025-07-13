@ECHO OFF

pushd "%~dp0/.." || exit /b 2
rem  use -Djava.security.auth.login.config=config/jaas.conf in parameter to enable LDAP authentication
call bin/launcher -cp "lib/cfgmsrv.jar;lib/oegw.jar" -Doegw.log.dir="log" -Djava.net.preferIPv4Stack=true com.ingenico.cfgsrv.oegwmm.lsb.Lsb %*
set exitcode=%errorlevel%

exit /b %exitcode%