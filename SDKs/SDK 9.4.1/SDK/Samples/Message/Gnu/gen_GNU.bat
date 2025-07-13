@echo OFF

rem ===============================================
rem === init

if NOT EXIST obj md obj
if NOT EXIST obj\SAMPLE.TXT copy ..\Src\SAMPLE.TXT obj
if NOT EXIST obj\SAMPLE.M30 copy ..\Src\SAMPLE.M30 obj
if NOT EXIST obj\SAMPLE.M31 copy ..\Src\SAMPLE.M30 obj\SAMPLE.M31

rem ===============================================
rem === Build

nmake Makefile.gnu

rem ===============================================
rem === if mockup 
rem 	sample.bin is copy as sample.sgn
rem 	SAMPLE.TXT is copy as SAMPLE.ADF

copy obj\SAMPLE.BIN obj\SAMPLE.SGN
copy obj\SAMPLE.TXT obj\SAMPLE.ADF

PAUSE