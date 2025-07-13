@ECHO OFF

pushd "%~dp0" || goto error

set login=btmlpa
set pswd=ingenico

IF ""%1""==""--help"" (
    goto USAGE
)
IF not ""%1""=="""" (
    set uname=%1
)
IF not ""%2""=="""" (
    set passwd=%2
)

rem -----------------------------------------------------------------
sqlplus %uname%/%passwd% < crebas.ddl.sql   || goto error
sqlplus %login%/%pswd%   < crebas.dml.sql   || goto error
rem -----------------------------------------------------------------

:error
set exitcode=%errorlevel%
pause
popd
exit /b %exitcode%

:USAGE
echo usage: recreate.cmd login password