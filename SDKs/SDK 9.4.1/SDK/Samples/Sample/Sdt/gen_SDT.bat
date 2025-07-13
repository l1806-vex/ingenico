@echo OFF

rem ===============================================
rem === init

if NOT EXIST obj_sdt md obj_sdt
if NOT EXIST obj_sdt\SAMPLE.ADF copy SAMPLE.ADF obj_sdt
if NOT EXIST obj_sdt\SAMPLE.M30 copy SAMPLE.M30 obj_sdt
if NOT EXIST obj_sdt\SAMPLE.M31 copy SAMPLE.M30 obj_sdt\SAMPLE.M31

rem ===============================================
rem === Build

nmake Makefile.sdt