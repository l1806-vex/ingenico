//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  DISPLAY.C                        (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Mode "OS font" display:
//              Change font (Small, Normal, Big)
//              Clear Screen
//              Cursor management
//              Blinking effect 
//                                                                            
//  List of routines in file :  
//      Display : OS font display demo.                                           
//                            
//  File history :
//  120508-BK : File created 
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
// !!! Warning : Functions ONLY supported for Telium 1&2 and will be replaced
// or removed for Telium+ to clean the platform.
// Add _DEPRECATED_TRAP_SDK091000_ inside Properties\Build Configurations\Users Symbols
// if needed and not yet replaced.
// font_size or startupcv20 => This routine configures the character font.
// gotoxy => This function is used to position the cursor.
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
//                          void Display (void)                            
//  This function shows the display in OS font mode.      
//       font_size() : change font (Small 8x21 Normal 4x16   Big 2x8)
//       putchar() : clear screen
//       printf() : write screen
//       blink() : blink effect 
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Display(void) 
{
	// Local variables 
    // ***************
	byte ucLig1=1, ucLig2=2;
    int iRet;

    _clrscr();
    PaintGraphics();                                                     // For ISC 350

	// Character display in progress
	// *****************************
	font_size (6,8);                                                     // **** Small font 8x21 ****  
    putchar('\x1B');                                                     // Clear screen 
    gotoxy(0,0);  iRet = printf("Small-1"); CHECK(iRet>=0, lblKO);       // Display
	gotoxy(1,2);  iRet = printf("Small-2"); CHECK(iRet>=0, lblKO);
	gotoxy(2,4);  iRet = printf("Small-3"); CHECK(iRet>=0, lblKO);
    gotoxy(3,6);  iRet = printf("Small-4"); CHECK(iRet>=0, lblKO);       //          with
	gotoxy(4,8);  iRet = printf("Small-5"); CHECK(iRet>=0, lblKO);
	gotoxy(5,10); iRet = printf("Small-6"); CHECK(iRet>=0, lblKO);
    gotoxy(6,12); iRet = printf("Small-7"); CHECK(iRet>=0, lblKO);
	gotoxy(7,14); iRet = printf("Small-8"); CHECK(iRet>=0, lblKO);       //                 gotoxy 
    ttestall(0, 3*100);                                                  // Delay 3s

	font_size (8,16);                                                    // **** Normal font 4x16 **** 
    putchar('\x1B');                                                     // Clear screen
    iRet = printf("Normal-1        \n"                                   // Display
		          "  Normal-2      \n"                                   //         with
			      "     Normal-3   \n"
			      "        Normal-4\n"); CHECK(iRet>=0, lblKO);          //               crlf
	ttestall(0, 3*100);                                                  // Delay 3s  

	font_size (13,32);                                                   // **** Big font 2x8 ****
    putchar('\x1B');                                                     // Clear screen 
	blink(ON);                                                           // Blinking effect start
    iRet = printf("Big-%d   \n"                                          // Display
		          "   Big-%d\n", ucLig1, ucLig2); CHECK(iRet>=0, lblKO); //          with  format      
    ttestall(0, 5*100);                                                  // Delay 5s
	blink(OFF); fopen("DISPLAY", "w*");                                  // Blinking effect stop
	
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	font_size(8,16);                                                     // Normal font
	putchar('\x1B');                                                     // Clear screen
	printf("Processing Error");                                          // Oops! error
    ttestall(0, 5*100);                                                  // Delay 5s 
lblEnd:
    CreateGraphics(_MEDIUM_);                                            // Graphic context
}
