//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  LIB.C                             (Copyright INGENICO 2008)
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Delay management:
//      Show how to call a LIB.
//      The static library BeepLib is generated during the training.
//                                                                            
//  List of routines in file :  
//      BeepLib : Beep LIB demo.                                            
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
#include "MyLibExport.h"


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
//                          void BeepLib (void)                            
//  This function runs the LIB called Beep.      
//  This function has no parameters.    
//  This function has no return value.
//****************************************************************************

void BeepLib(void) 
{
	// Local variables 
    // ***************
    int iRet=0;

	// Change font size
	// ================
    _clrscr();                                         // Clear screen

	// Call the functions from the LIB
	// ===============================
	DisplayMedium(0, 0, "Press a key");
	DisplayMedium(1, 0, "to hear 1 beep");
	getchar();
	//OneBeep();                                         // Call function OneBeep()

	DisplayMedium(0, 0, "Press a key");
	DisplayMedium(1, 0, "to hear 3 beeps");
	getchar();
	//iRet = ManyBeep(3);                                // Call function ManyBeep()
	CHECK(iRet==2*3, lblKO);

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                         // Clear screen
	DisplayMedium(0, 0, "Processing Error");           // Oops! error
    ttestall(0,5*100);                                 // Delay 5s 
    goto lblEnd;
lblEnd:
    return;
}



