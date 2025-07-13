@ECHO OFF

pushd "%~dp0" || goto error

rem By default run scripts for root without password
set instance=

set login=-U btmlpa
set pswd=-P ingenico

IF ""%1""==""--help"" (
    goto USAGE
)

IF not ""%1""=="""" (
    set instance=-S "%1"
)
rem -----------------------------------------------------------------
osql -n -I -r -E %instance%		-i crebas.ddl.sql 	|| goto error
osql -n -I -r %instance% %login% %pswd%	-i crebas.dml.sql 	|| goto error
rem -----------------------------------------------------------------

:error
set exitcode=%errorlevel%
pause
popd
exit /b %exitcode%

:USAGE
echo usage: recreate.cmd [instance]
echo instance - name of MS SQL Server instance (SQL Server name)
