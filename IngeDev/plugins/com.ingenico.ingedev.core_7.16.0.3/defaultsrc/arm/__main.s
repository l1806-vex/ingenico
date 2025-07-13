; __main function to perform the R/W and ZI data initialization and stack initialization

  AREA    MyMain, CODE, READONLY

  ENTRY

  CODE32

  EXPORT  __main

__main
  ; Start application (entry point)
  LDR r0, Entry_Point
  BX  r0

  IMPORT  ApplicationMain

Entry_Point
  DCD     ApplicationMain

  END
