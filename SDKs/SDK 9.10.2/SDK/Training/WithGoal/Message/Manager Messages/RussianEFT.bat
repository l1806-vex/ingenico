del Telium2\EFT.MSG

rem ===========================================================
rem
rem  generate EFT.MSG 
rem
rem ===========================================================

..\BuildMSG -c -tMANAGERRussian.h -hRuManagerMessages.h EFT.MSG
..\BuildMSG -tHWCNFRussian.h -hRuHwcnfMessages.h EFT.MSG

rem ===========================================================
rem
rem  sign EFT.MSG before loadind it in the terminal
rem
rem ===========================================================

xcopy EFT.MSG Telium2

pause


