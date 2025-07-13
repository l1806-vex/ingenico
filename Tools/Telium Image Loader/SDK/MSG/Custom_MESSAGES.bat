@echo off
rem ===========================================================
rem
rem  Generate and Sign Message file
rem
rem ===========================================================

rem =========================
rem  Set Application  Name 
rem  Set File Message Name
rem =========================
set APP_NAME=IMAGELOADER
set APP_MESSAGE=8228810101

rem =========================
rem  generate Message file
rem =========================
rem 1- convert h file to MSG file
del MessagesDefinitions.h MESSAGES.c

BuildMSG -c -tSampleCustFrench.h -hMessagesDefinitions.h %APP_MESSAGE%.MSG
BuildMSG -tSampleCustEnglish.h -hMessagesDefinitions.h %APP_MESSAGE%.MSG
BuildMSG -tSampleCustSpanish.h -hMessagesDefinitions.h %APP_MESSAGE%.MSG

rem =========================
rem  create prm file for SST
rem =========================
set RESOURCE_NAME=resources
set CATALOG_FILE=31
set SST_CONFIG_FILE=%CD%\%APP_NAME%.prm1
rem set SST_DIR=D:\Programs\TELIUM Tools\SST30
set SST_DIR=C:\Program Files\TELIUM Tools\SST30
set PARAM_FILE_T1=0,%APP_MESSAGE%.SGN,B3BC,%APP_MESSAGE%,0,0,0000,00000000,00000000,00000000,00000000,00000000,

echo %PARAM_FILE_T1%>> "%APP_MESSAGE%_T1.TXT"

del "%SST_CONFIG_FILE%"
echo [SST]>> "%SST_CONFIG_FILE%"
echo ReaderName=>> "%SST_CONFIG_FILE%"
echo CertificateSchemaDir=%SST_DIR%\certificate>> "%SST_CONFIG_FILE%"
echo CertificateAppliDir=%SST_DIR%\certificate>> "%SST_CONFIG_FILE%"
echo ParametersDir=%CD%>> "%SST_CONFIG_FILE%"
echo DestinationDir=%CD%\Signed\SST>> "%SST_CONFIG_FILE%"
echo ApplicationDir=%CD%>> "%SST_CONFIG_FILE%"
echo TempDir=%CD%\Temp>> "%SST_CONFIG_FILE%"
echo.>> "%SST_CONFIG_FILE%"

echo [Application]>> "%SST_CONFIG_FILE%"
echo ParameterFile=%APP_MESSAGE%_T1.TXT>> "%SST_CONFIG_FILE%"
echo CertificateFile=Mockup.V03>> "%SST_CONFIG_FILE%"
echo ApplicationFile=%APP_MESSAGE%.MSG>> "%SST_CONFIG_FILE%"
echo CatalogFileExtension=%CATALOG_FILE%>> "%SST_CONFIG_FILE%"

mkdir "%CD%"\Temp

rem ===================
rem  SST: sign message file
rem ===================
@echo on
"%SST_DIR%\SST30.exe" 2,%SST_CONFIG_FILE%,00000000

@echo off

rmdir "%CD%"\Temp


rem =========================
rem  create prm file for SAT
rem =========================
set APP_NAME=IMAGELOADER
set CATALOG_FILE=40
set SAT_CONFIG_FILE=%CD%\%APP_NAME%.prm2
rem set SAT_DIR=D:\Programs\TELIUM Tools\SAT1.5.1
set SAT_DIR=C:\Program Files\TELIUM Tools\SAT1.5.1
set PARAM_FILE_T2=0,%APP_MESSAGE%.PGN,B3BC,%APP_MESSAGE%,0,0,0000,00000000,00000000,00000000,00000000,00000000,

echo %PARAM_FILE_T2%>> "%APP_MESSAGE%_T2.TXT"

del "%SAT_CONFIG_FILE%"
echo [SAT]>> "%SAT_CONFIG_FILE%"
echo ReaderName=>> "%SAT_CONFIG_FILE%"
echo CertificateSchemaDir=%SAT_DIR%\certificate>> "%SAT_CONFIG_FILE%"
echo CertificateAppliDir=%SAT_DIR%\certificate>> "%SAT_CONFIG_FILE%"
echo ParametersDir=%CD%>> "%SAT_CONFIG_FILE%"
echo DestinationDir=%CD%\Signed\SAT>> "%SAT_CONFIG_FILE%"
echo ApplicationDir=%CD%>> "%SAT_CONFIG_FILE%"
echo TempDir=%CD%\Temp>> "%SAT_CONFIG_FILE%"
echo.>> "%SAT_CONFIG_FILE%"

echo [Application]>> "%SAT_CONFIG_FILE%"
echo ParameterFile=%APP_MESSAGE%_T2.TXT>> "%SAT_CONFIG_FILE%"
echo CertificateFile=Mockup.V03>> "%SAT_CONFIG_FILE%"
echo ApplicationFile=%APP_MESSAGE%.MSG>> "%SAT_CONFIG_FILE%"
echo CatalogFileExtension=%CATALOG_FILE%>> "%SAT_CONFIG_FILE%"

mkdir "%CD%"\Temp

rem ===================
rem  SAT: sign message file
rem ===================
@echo on
"%SAT_DIR%\SAT.exe" 4,%SAT_CONFIG_FILE%,00000000
@echo off

rmdir "%CD%"\Temp

rem erase %APP_MESSAGE%_T1.TXT
rem erase %APP_MESSAGE%_T2.TXT

pause