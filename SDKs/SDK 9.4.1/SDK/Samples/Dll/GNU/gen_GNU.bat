@echo OFF

rem ===============================================
rem === init

if NOT EXIST obj_gnu md obj_gnu
if NOT EXIST obj_gnu\sampledll.txt copy ..\src\sampledll.txt obj_gnu
if NOT EXIST obj_gnu\sampledll.M30 copy ..\src\sampledll.M30 obj_gnu
if NOT EXIST obj_gnu\sampledll.M31 copy ..\src\sampledll.M30 obj_gnu\sampledll.M31


rem ===============================================
rem === Build

nmake  Makefile.gnu

rem ===============================================
rem === mockup
copy obj_gnu\sampledll.txt obj_gnu\sampledll.ldf
copy obj_gnu\sampledll.BIN obj_gnu\sampledll.SGN

PAUSE
