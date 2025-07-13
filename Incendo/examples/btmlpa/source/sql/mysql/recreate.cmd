@ECHO OFF

pushd "%~dp0" || goto error

rem By default run scripts for root without password
set uname=-uroot
set passwd=

IF ""%1""==""--help"" (
    goto USAGE
)

IF not ""%1""=="""" (
    set uname=-u%1
)
IF not ""%2""=="""" (
    set passwd=-p%2
)
rem -----------------------------------------------------------------
mysql %uname% %passwd%           < crebas.ddl.sql 	|| goto error
mysql %uname% %passwd% -D btmlpa < crebas.dml.sql 	|| goto error
rem -----------------------------------------------------------------

:error
set exitcode=%errorlevel%
pause
popd
exit /b %exitcode%

:USAGE
echo usage: recreate.cmd [login [password]]
