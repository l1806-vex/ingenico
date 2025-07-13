del Telium1\SAMPLEMSG.MSG
del Telium2\SAMPLEMSG.MSG

rem ===========================================================
rem
rem  generate English.c for Message sample
rem
rem ===========================================================

rem 1- convert h file to MSG file

..\BuildMSG -c -tSampleLocalEnglish.h -hMessagesDefinitions.h English.MSG

rem 2- create English.c file to include in the sample

..\MSG2C English.MSG English.c




rem ===========================================================
rem
rem  generate SAMPLEMSG.MSG for Message sample
rem
rem ===========================================================


..\BuildMSG -c -tSampleCustEnglish.h -hMessagesDefinitions.h SAMPLEMSG.MSG
..\BuildMSG -tSampleCustRussian.h -hMessagesDefinitions.h SAMPLEMSG.MSG
..\BuildMSG -tSampleCustGerman.h -hMessagesDefinitions.h SAMPLEMSG.MSG
..\BuildMSG -tSampleCustArabic.h -hMessagesDefinitions.h SAMPLEMSG.MSG

rem ===========================================================
rem
rem  sign SAMPLEMSG.MSG before loadind it in the terminal
rem
rem ===========================================================

xcopy  SAMPLEMSG.MSG Telium1
xcopy  SAMPLEMSG.MSG Telium2

pause