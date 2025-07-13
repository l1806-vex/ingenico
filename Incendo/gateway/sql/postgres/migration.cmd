@ECHO OFF

set LOGDIR="%~dp0/../../log"
if not exist %LOGDIR% mkdir %LOGDIR%

pushd "%~dp0" || goto error

echo %date% %time% Postgres DB migration script starting >> %LOGDIR%/oegw.log

set uname=-U postgres
set dbhost=-h localhost

IF "%1"=="--help" (
    goto USAGE
)
IF "%1"=="" (
    goto USAGE
)

set dbscript=%1

IF not "%2"=="" (
    set dbhost=-h %2
)
IF not "%3"=="" (
    set uname=-U %3
)

rem -----------------------------------------------------------------

psql %dbhost% %uname% -f %dbscript% || goto error

rem -----------------------------------------------------------------
echo %date% %time% Postgres DB migration script finished successfully >> %LOGDIR%/oegw.log
goto FIN

:error
echo %date% %time% Postgres DB migration script finished with error >> %LOGDIR%/oegw.log
pause
goto FIN

:USAGE
echo usage: migration.cmd [host] [login] [sql file]

:FIN
set exitcode=%errorlevel%
popd
exit /b %exitcode%