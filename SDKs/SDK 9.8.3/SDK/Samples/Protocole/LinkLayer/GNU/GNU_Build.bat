@ECHO OFF
if NOT EXIST obj md obj
CALL Make.bat Makefile.gnu
PAUSE
