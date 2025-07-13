@ECHO OFF

pushd "%~dp0" || goto error

rem By default run scripts for postgres with password prompted
set uname=-U postgres
rem Do not force password prompt (which is default):
rem set passwd=-W
rem keep is empty instead:
set passwd=

IF ""%1""==""--help"" (
    goto USAGE
)
IF not ""%1""=="""" (
    set uname=-U %1
)
rem -----------------------------------------------------------------

psql %uname% %passwd% -f all.sql || goto error

rem -----------------------------------------------------------------

:error
set exitcode=%errorlevel%
pause
popd
exit /b %exitcode%

:USAGE
echo usage: recreate.cmd [login]
