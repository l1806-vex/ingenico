//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  KEYBOARD.C                        (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Keyboard management:
//              Wait for a key
//              Retrieve key pressed
//              Display key pressed
//                                                                            
//  List of routines in file :  
//      Keyboard : Key press demo.                                            
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
//                         void Keyboard (void)                            
//  This function displays the key pressed.      
//       fopen() : open the keyboard channel
//       ttestall() : Wait for a key from keyboard peripheral
//       getchar() : Retrieve key pressed
//       fclose : close the keyboard channel 
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void Keyboard(void) 
{
	// Local variables 
    // ***************
    char cKey;                                                           // The last key pressed
	char tcBuf[25+1];                                                    // Buffer to accumulate keys pressed
    int iIdx;                                                            // The number of key pressed
    int iRet;

	// Key press in progress
	// *********************
	_clrscr();                                                           // Clear screen
	DisplayMedium(0, 0, "Press a key...");                               // Display message
    
    iIdx=0;
    memset(tcBuf, 0, sizeof(tcBuf));
    reset_buf(pxKbd, _receive_id);                                       // Reset keyboard FIFO before starting key press process
    while(iIdx <= sizeof(tcBuf)-1) 
	{
        cKey=0;
		iRet = ttestall(KEYBOARD, 30*100);                               // Wait for a key pressed or a timeout
		if (iRet & KEYBOARD)                                             // Key detected
			cKey = getchar();                                            // Retrieve key pressed
      
        tcBuf[iIdx] = cKey;               
        if(!tcBuf[iIdx])
            break;                                                       // Exit loop if nothing is pressed during 5s
        if(tcBuf[iIdx] == T_ANN)
            break;                                                       // Exit loop if red key is pressed
		if(tcBuf[iIdx] == T_VAL)
			tcBuf[iIdx] = 'V';                                           // Assign 'V' to green key
		if(tcBuf[iIdx] == T_CORR)
			tcBuf[iIdx] = 'C';                                           // Assign 'C' to yellow key
		if(tcBuf[iIdx] == T_F)
			tcBuf[iIdx] = 'F';                                           // Assign 'F' to function key
		if(tcBuf[iIdx] == F1)
			tcBuf[iIdx] = '?';                                           // Assign '?' to F1 
		DisplaySmall(3, 0, tcBuf);                                       // Display key pressed
        iIdx++;                                                          // One more key
    }
}
