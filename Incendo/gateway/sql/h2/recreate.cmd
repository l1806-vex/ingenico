@ECHO OFF

set LOGDIR="%~dp0/../../log"
if not exist %LOGDIR% mkdir %LOGDIR%

echo %date% %time% H2 DB recreation script starting >> %LOGDIR%/oegw.log

pushd "%~dp0" || goto error

set CLASSPATH=h2.jar
set CLASS=org.h2.tools.RunScript
set JDBC_URL=jdbc:h2:~/oegw
set uname=-user oe
set passwd=-password ingenico

IF "%1"=="--help" (
    goto USAGE
)

IF not "%1"=="" (
    set uname=-user %1
)
IF not "%2"=="" (
    set passwd=-password %2
)
rem -----------------------------------------------------------------
java -cp %CLASSPATH% %CLASS% -url %JDBC_URL% %uname% %passwd% -script oegw/cred.ddl.sql || goto error
java -cp %CLASSPATH% %CLASS% -url %JDBC_URL% %uname% %passwd% -script oegw/crebas.ddl.sql || goto error
java -cp %CLASSPATH% %CLASS% -url %JDBC_URL% %uname% %passwd% -script oegw/crebas.dml.sql || goto error
if exist oegw/testdata.sql java -cp %CLASSPATH% %CLASS% -url %JDBC_URL% %uname% %passwd% -script oegw/testdata.sql || goto error
java -cp %CLASSPATH% %CLASS% -url %JDBC_URL% %uname% %passwd% -script cfgsrv/crebas.ddl.sql || goto error

rem -----------------------------------------------------------------
echo %date% %time% H2 DB recreation script finished successfully >> %LOGDIR%/oegw.log
goto FIN

:error
pause
echo %date% %time% H2 DB recreation script finished with error >> %LOGDIR%/oegw.log
goto FIN

:USAGE
echo usage: recreate.cmd [login [password]]

:FIN
set exitcode=%errorlevel%
popd
exit /b %exitcode%
