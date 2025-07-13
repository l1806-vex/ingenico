//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  DELAY.C                          (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Delay management:
//      Show how to handle a cyclic delay  
//                                                                            
//  List of routines in file :  
//      Periodic : Periodic function call.
//      Delay : Delay demo.                                            
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
#define PRTW  24

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
static char tcBuf[PRTW+1];
static word usTo; 


// Periodic function
// *****************
static word Periodic (void)
{
	strcat(tcBuf, ".");
	DisplayMedium(2, 0, tcBuf);
	pprintf("%s\n", tcBuf);
	usTo--;
	return 0;
}

//****************************************************************************
//                          void Delay (void)                            
//  This function calls cyclically a routine with a periodic delay.      
//       GetDelayUser() : Retrieve a delay number
//       StartLDelay() : Start a cyclic delay
//       StopDelay() : Stop a cyclic delay
//       FreeDelayUser() : Release the delay number
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Delay(void) 
{
	// Local variables 
    // ***************
	word usDlyNbr=0;
	doubleword uiTime, uiPeriod;
    int iRet;            

	// Demo Delay in progress
	// **********************
    memset(tcBuf, 0, sizeof(tcBuf));                                              // Reset printing buffer
    _clrscr();                                                                    // Clear screen
	DisplayMedium(0, 0, "Delay running...");                                      // Display delay running
	DisplayMedium(1, 0, "Waiting for 10s");
	
    iRet = pprintf("\x1b""E""          Delay Demo\n\n"                            // Print demo in progress
		           "\x1b""F"); CHECK(iRet>=0, lblKO);      
	iRet = pprintf("Waiting for 10 seconds..\n"); CHECK(iRet>=0, lblKO);          // Print time delay

	// Repeat cyclically 10 times the function Periodic every 1s delay
	// ===============================================================
	usTo=10;                                                                      // TimeOut
	usDlyNbr = GetDelayUser();                                                    // Get a delay number
	iRet = StartLDelay(usDlyNbr, 1*100, 1*100, Periodic); CHECK(iRet==0, lblKO);  // Start periodic delay of 1 second
	while(usTo != 0)                                                              // Wait until TimeOut expired
		ttestall(PRINTER, 10);                                              
	StopDelay(usDlyNbr, &uiTime, &uiPeriod);                                      // Stop periodic delay
	iRet = pprintf("Finished\n\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);              // Print delay finished

	ttestall(0, 2*100);                                                           // Delay 2s
		
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                                                    // Clear screen
	DisplayMedium(0, 0, "Processing Error");                                      // Oops! error
    ttestall(0,5*100);                                                            // Delay 5s 
lblEnd:
    FreeDelayUser(usDlyNbr);                                                      // Release the delay number
}
