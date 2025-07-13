//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  POWERFAILURE.C                      (Copyright INGENICO 2011)
//============================================================================
//  Created :       17-June-2011     Kassovic
//  Last modified : 17-June-2011     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  How to manage the RegisterPowerFailure.
//  On EFT30/SMART, there is a capacitor which is able to back up the RAM
//  for 50ms. So the RAM area declared by the RegisterPowerFailure function
//  is copied from RAM to FLASH only when a power failure (i.e. main power cut)
//  is detected.
//  On all other terminals, because of design, there is no such capacitor.
//  Consequence is that copy from RAM to FLASH can't be done when a power failure
//  (i.e. battery removal) is detected. So there is a special mechanism where
//  the hardware detection is replaced by a 100ms timer. To prevent useless
//  writing in FLASH, data are saved only if they changed since last timer tick.
//  This means that developer must handle power failure the same way on all
//  Telium terminals. In all cases, its task is just to register the RAM area
//  which has to be saved/restored. Telium system will do all the job! The only
//  goal of the explanations are maybe to prevent the developer to register data
//  which change very often. In that case, the life time of the Flash could be
//  affected and garbage collection will occur frequently.
//                                                                            
//  List of routines in file :  
//      WriteInRam : Write in RAM protected by RegisterPowerFailure().
//      ReadFromRam : Read from RAM protected by RegisterPowerFailure().
//                            
//  File history :
//  020109-BK : File created 
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
extern FILE *pxKbd;  // Peripheral file Keyboard

// Buffer saved automatically from RAM to FLASH in case of power failure
extern char tcPowerFailure[5*1024];

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
//                       void WriteInRam (char *pcMsg)
//  This function writes a message inside a buffer in RAM protected by the
//  function RegisterPowerFailure().
//       RegisterPowerFailure() : save a RAM data area into FLASH
//                                in case of power failure.
//  This function has parameters.
//		ucMsgNbr (I-) : Message number to write (Msg1 or Msg2).
//  This function has no return value.                                      
//****************************************************************************

void WriteInRam (byte ucMsgNbr)
{
	// Local variables 
    // ***************
		// Empty

    // Buzzer management
	// *****************
    _clrscr();                                                // Clear screen
    memset (tcPowerFailure, 0, sizeof(tcPowerFailure));

    if (ucMsgNbr == 1)
    	strcpy(tcPowerFailure, "Hello, do you hear me?\n"     // Write message1 in RAM
							   "Hello, do you hear me?\n"
							   "Hello, do you hear me?\n"
							   "Hello, do you hear me?");
    else
    	strcpy(tcPowerFailure, "Hi, how are you doing?\n"     // Write message2 in RAM
							   "Hi, how are you doing?\n"
							   "Hi, how are you doing?\n"
							   "Hi, how are you doing?");

    DisplaySmall(0, 0, "Msg in RAM:");                        // Display message written
	Display25(1, tcPowerFailure, strlen(tcPowerFailure));
    DisplaySmall(7, 0, "Unplug/Reboot terminal!");            // Unplug terminal then read RAM to see that
                                                              // the message has been restored properly

	ttestall(0, 0);                                           // Wait until terminal unplug
}

//****************************************************************************
//                       void ReadFromRam(void)
//  This function reads a message from a buffer in RAM protected by the
//  function RegisterPowerFailure().
//       RegisterPowerFailure() : Restore a RAM data area from FLASH
//                                in case of power failure.
//  This function has no parameters.
//  This function has no return value.
//****************************************************************************

void ReadFromRam(void)
{
	// Local variables
    // ***************
		// Empty

    // Buzzer management
	// *****************
    _clrscr();                                                // Clear screen
    
    DisplaySmall(0, 0, "Msg in RAM:");                        // Display message written
	Display25(1, tcPowerFailure, strlen(tcPowerFailure));
	DisplaySmall(7, 6, "Press a key");

	reset_buf(pxKbd, _receive_id);                            // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                               // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                            // Reset keyboard FIFO to clear key pressed
}
