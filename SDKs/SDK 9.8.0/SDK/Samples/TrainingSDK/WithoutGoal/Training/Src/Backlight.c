//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  BACKLIGHT.C                        (Copyright INGENICO 2009)   
//============================================================================
//  Created :       02-January-2009     Kassovic                                 
//  Last modified : 02-January-2009     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  How to manage the backlight
//                                                                            
//  List of routines in file :  
//      Backlight : Increase or decrease backlight.
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
extern FILE *pxKbd;      // Peripheral file Keyboard

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
//                         void Backlight (void)                            
//  This function shows how to decrease or increase the backlight.      
//       HWCNF_SetBacklightIntensity() : Set backlight intensity
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void Backlight(void) 
{
	// Local variables 
    // ***************
    char cKey;
    char tcDisplay[16+1];
	int iIdx, iLevel;
    int iRet;

    // Backlight management
	// ********************
    _clrscr();                                                 // Clear screen
	cKey='%';
	DisplayMedium(0, 14, "Up");
	sprintf(tcDisplay, "Backlight: 100%c", cKey);              // Display backlight percentage
	DisplayMedium(1, 0, tcDisplay);
	DisplayMedium(2, 12, "Down");

	iIdx=0;
	reset_buf(pxKbd, _receive_id);                             // Reset keyboard FIFO
	while(1)
	{
        cKey=0;	        
		iRet = ttestall(KEYBOARD, 5*100);                      // Wait for a key pressed until 5s
		if (iRet & KEYBOARD)                                   // Key detected
			cKey = getchar();                                  // Retrieve key pressed
      
        if(!cKey)
            break;                                             // Exit loop if nothing is pressed during 5s
        if((cKey == T_ANN) || (cKey == T_VAL))
            break;                                             // Exit loop if red or green key is pressed

		if ((cKey==T_SKBAS) || (cKey==T_SK3))                  // Key DOWN
		{
			if(iIdx < 10)
			{
				iIdx++;                                               
				iLevel = iIdx*6554;                            // Decrease backlight 
				if (iLevel >= 0xFFFF)
					iLevel=0xFFFF;                             // Backlight min
				iRet = HWCNF_SetBacklightIntensity(iLevel);    // Set backlight
			}
		}
        if((cKey==T_SKHAUT) || (cKey==T_SK4))                  // Key UP
		{
			if (iIdx > 0)
			{
				iIdx--;
				iLevel = iIdx*6554;                            // Increase backlight
				if (iLevel == 0)
					iLevel=0x0001;                             // Backlight max
				iRet = HWCNF_SetBacklightIntensity(iLevel);    // Set backlight
			}
		}
		
		cKey='%';                                              // Display backlight %
		sprintf (tcDisplay, "Backlight: %3d%c", 100-(10*iIdx), cKey);
		DisplayMedium(1, 0, tcDisplay);
    }
    
    HWCNF_SetBacklightIntensity(0x0001);                       // Backlight max
}
