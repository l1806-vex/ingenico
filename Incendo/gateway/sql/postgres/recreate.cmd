@ECHO OFF

set LOGDIR="%~dp0/../../log"
if not exist %LOGDIR% mkdir %LOGDIR%

pushd "%~dp0" || goto error

echo %date% %time% Postgres DB recreation script starting >> %LOGDIR%/oegw.log

set uname=-U postgres
set dbhost=-h localhost

IF "%1"=="--help" (
    goto USAGE
)
IF not "%1"=="" (
    set dbhost=-h %1
)
IF not "%2"=="" (
    set uname=-U %2
)
rem -----------------------------------------------------------------

psql %dbhost% %uname% -f all.sql || goto error

rem -----------------------------------------------------------------
echo %date% %time% Postgres DB recreation script finished successfully >> %LOGDIR%/oegw.log
goto FIN

:error
echo %date% %time% Postgres DB recreation script finished with error >> %LOGDIR%/oegw.log
pause
goto FIN

:USAGE
echo usage: recreate.cmd [host] [login]

:FIN
set exitcode=%errorlevel%
popd
exit /b %exitcode%