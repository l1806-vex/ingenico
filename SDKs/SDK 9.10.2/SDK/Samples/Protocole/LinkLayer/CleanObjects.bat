@ECHO OFF

DEL VC6\*.ncb > NUL 2>NUL
DEL VC6\*.opt > NUL 2>NUL
DEL VC6\*.plg > NUL 2>NUL
DEL VC6\*.positions > NUL 2>NUL
RMDIR /S /Q VC6\Debug > NUL 2>NUL
RMDIR /S /Q VC6\Release > NUL 2>NUL

CD GNU
CALL GNU_Clean.bat
CD..
