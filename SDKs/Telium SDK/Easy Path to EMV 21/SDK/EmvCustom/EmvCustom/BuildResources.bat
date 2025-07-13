@echo off

set RESSOURCE_FILE=EmvCustom
set BUILD_RESSOURCE_DIR=%ProgramFiles%\TeliumSDK\SDK 9.2.2\tools\CGUI\ImageTools

echo *******************************************************************************
echo *** Generating resources file...

rd /s/q "ResourcesBuild" > nul 2> nul
md "ResourcesBuild" > nul 2> nul
xcopy /e/s/y "Resources\*.*" "ResourcesBuild" > nul

pushd "ResourcesBuild"
"%BUILD_RESSOURCE_DIR%\buildResource.exe"
popd

md "Bin" > nul 2> nul
copy "ResourcesBuild\Result.tar" "Bin\%RESSOURCE_FILE%.tar" > nul
rd /s/q "ResourcesBuild" > nul 2> nul

pause
