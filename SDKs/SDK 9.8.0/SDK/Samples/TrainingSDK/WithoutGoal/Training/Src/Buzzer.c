//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  BUZZER.C                             (Copyright INGENICO 2009)   
//============================================================================
//  Created :       02-January-2009     Kassovic                                 
//  Last modified : 02-January-2009     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  How to manage the buzzer
//                                                                            
//  List of routines in file :  
//      Buzzer : Frequency 872Hz, increase or decrease volume.
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
//                         void Buzzer (void)                            
//  This function sets a buzzer to 872Hz and shows how to decrease or increase
//  the volume.
//       StartBuzzer() : start buzzer
//       StopBuzzer() : stop buzzer
//  - divisor=0 => TIC=2/57MHZ = 0.035us
//  - delay_total=0x8000 => total period = 0x8000*0.035us = 1.147ms (872Hz)
//  - delay_high=0 => Volume Min
//  - delay_high=9*500 => Volume Max
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Buzzer(void) 
{
	// Local variables 
    // ***************
    char cKey;
    char tcDisplay[16+1];
	int iIdx, iLevel;	
    int iRet;

    // Buzzer management
	// *****************
    _clrscr();                                                       // Clear screen
	cKey='%';
	DisplayMedium(0, 14, "Up");
	DisplayMedium(1, 0, "Sound: 872Hz");
	sprintf(tcDisplay, "Volume:   0%c", cKey);                       // Display sound percentage
	DisplayMedium(2, 0, tcDisplay);
	DisplayMedium(3, 12, "Down");
	
	iIdx=0;
	iLevel=0x8000;
	iRet = StartBuzzer(0, iLevel, 0x8000);                           // Set buzzer 872Hz	
	reset_buf(pxKbd, _receive_id);                                   // Reset keyboard FIFO
	while(1)
	{
        cKey=0;        
		iRet = ttestall(KEYBOARD, 5*100);                            // Wait for a key pressed until 5s
		if (iRet & KEYBOARD)                                         // Key detected
			cKey = getchar();                                        // Retrieve key pressed
      
        if(!cKey)
            break;                                                   // Exit loop if nothing is pressed during 5s
        if((cKey == T_ANN) || (cKey == T_VAL))
            break;                                                   // Exit loop if red or green key is pressed

		if ((cKey==T_SKHAUT) || (cKey==T_SK4))                       // Key UP
		{
			if(iIdx < 10)
			{
				iIdx++;                                               
				iLevel = iLevel-153;                                 // Increase volume
				iRet = StartBuzzer(0, iLevel, 0x8000);               // Set buzzer 872Hz
			}
		}
        if((cKey==T_SKBAS) || (cKey==T_SK3))                         // Key DOWN
		{
			if (iIdx > 0)
			{
				iIdx--;
				iLevel = iLevel+153;                                 // Decrease volume
				iRet = StartBuzzer(0, iLevel, 0x8000);               // Set buzzer 872Hz
			}
		}

		cKey='%';
		sprintf (tcDisplay, "Volume: %3d%c", 10*iIdx, cKey);         // Display volume %
		DisplayMedium(2, 0, tcDisplay);
    }
    
    StopBuzzer();                                                    // Stop buzzer 
}

