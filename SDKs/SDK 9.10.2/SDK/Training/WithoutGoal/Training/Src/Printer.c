//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  PRINTER.C                        (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Mode "OS font" printer:
//          Printer mode (Bold, Reverse, Double Width/Height, 48 columns)
//                                                                            
//  List of routines in file :  
//      Printer : OS font Printer demo.
//      PrnGraphic : Graphic font Printer demo                                            
//                            
//  File history :
//  120508-BK : File created 
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
    /* */

//****************************************************************************
//                          void Printer (void)                            
//  This function shows the printer in OS font mode.      
//       pprintf() : print printer capabilities
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Printer(void) 
{
	// Local variables 
    // ***************
    int iRet;

    // Printing in progress
	// ********************
	_clrscr();                                                                    // Clear screen
	DisplayMedium(0, 0, "Printing...");                                           // Display printing in progress
	iRet = pprintf("\x1b""E""         Printer Demo\n\n" "\x1b""F");               // Print demo in progress
    CHECK(iRet>=0, lblKO);      
	
	// Print strings
	// =============
	iRet = pprintf("Short string\n\n"); CHECK(iRet>=0, lblKO);                    // Short
    iRet = pprintf("Now try a long string:\n"); CHECK(iRet>=0, lblKO);            // Long
    iRet = pprintf("012345678901234567890123456789\n\n"); CHECK(iRet>=0, lblKO);
	
    // Print different modes
	// =====================
    iRet = pprintf("\x1b""E""Bold\n\n""\x1b""F"); CHECK(iRet>=0, lblKO);          // Bold  
    iRet = pprintf("\x1b""B1""Reverse\n\n""\x1b""B0"); CHECK(iRet>=0, lblKO);     // Reverse
    iRet = pprintf("\x0E""Double Width\n\n""\x14"); CHECK(iRet>=0, lblKO);        // Double Width
    iRet = pprintf("\x1b""H""Double Height\n\n""\x1b""F"); CHECK(iRet>=0, lblKO); // Double Height
    iRet = pprintf("\x0F""48 columns\n\n""\x12"); CHECK(iRet>=0, lblKO);          // 48 columns
    iRet = pprintf("Normal again\n\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);          // Normal
	
    ttestall(PRINTER, 1*100);                                                     // Wait until everything printed

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                                            // None-classified low level error
	_clrscr();                                                                    // Clear screen
	DisplayMedium(0, 0, "Processing Error");                                      // Oops! error
    ttestall(0, 5*100);                                                           // Delay 5s 
lblEnd: 
    return;
}

