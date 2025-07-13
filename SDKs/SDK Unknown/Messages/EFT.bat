rem ===========================================================
rem generate EFT.MSG that contains:
rem english and russian messages for Manager and HWCNF DLL
rem ===========================================================

BuildMSG -c -tenglish.h -hEnRuManagerMessages.h EFT.MSG
BuildMSG -tHWCNFEnglish.h -hEnRuHwcnfMessages.h EFT.MSG
BuildMSG -tMANAGERRussian.h -hEnRuManagerMessages.h EFT.MSG
BuildMSG -tHWCNFRussian.h -hEnRuHwcnfMessages.h EFT.MSG

rem ===========================================================
rem
rem  sign EFT.MSG before loadind it in the terminal
rem
rem ===========================================================


