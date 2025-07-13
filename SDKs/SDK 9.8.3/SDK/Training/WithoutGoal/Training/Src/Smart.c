//****************************************************************************
//       INGENICO                                INGEDEV 7               
//============================================================================
//       FILE  SMART.C                           (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Smart card management:
//      Print Application Selection command sent to the card 
//                                                                            
//  List of routines in file :  
//      Smart : Smart card demo.                                            
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
//                          void Smart (void)                            
//  This function sends the application selection command to the card.      
//       fopen() : open Cam0 channel
//       ttestall() : Wait for card insertion from cam peripheral
//       EMV_power_on() : Retrieve ATR
//       EMV_apdu() : Send command for Application Selection 
//       ttestall() : Wait for card removal from cam peripheral
//       fclose : close cam0 channel 
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Smart(void) 
{
	// Local variables 
    // ***************
	FILE *pxSmc=NULL;
    HISTORIC xAtr;
	T_APDU xApduC;                                              // Command APDU
    T_APDU xApduR;                                              // Response APDU
    char tcDisplay[25+1];
    byte tucSnd[262];
    byte tucRsp[262];
	char *pcMsg;
	byte ucSta, ucKey;
    int iRet, iCt, iLen;

    pcMsg = "Processing Error";                                 // Error message by default

	// Open peripherals
	// ================
	pxSmc = fopen("CAM0", "rw*"); CHECK(pxSmc!=NULL, lblKO);    // Open the main Cam channel

    _clrscr();                                                  // Clear screen
	DisplayMedium(0, 0, "Insert a card...");                    // Display insert message

    // Wait for smart card
	// ===================
	reset_buf(pxKbd, _receive_id);                              // Reset keyboard FIFO
	while(1)
	{
		ucSta = ttestall(KEYBOARD | CAM0, 30*100);

		CHECK(ucSta!=0, lblEnd);                                // Exit if nothing inserted after 30s

		if(ucSta & KEYBOARD)                                    // Key event
		{
			ucKey = getchar();
		    CHECK(ucKey!=T_ANN, lblEnd);                        // Exit on red key
			continue;
		}
		else
			break;                                              // Smart event
	}

    // Power on smart card
	// ===================
    iLen=0;
	iRet = EMV_power_on(pxSmc, &xAtr);                          // EMV power on and reset                 
	if(iRet == 5)                                               // Power once more time  on VPP problem detected 
		iRet = EMV_power_on(pxSmc, &xAtr);
    switch (iRet)                                               // Card errors
	{                                            
    case 0:                                           break;
	case 1: case 7:         pcMsg = "Card removed";   break;
	case 2: case 4: case 5: pcMsg = "Card Problem";   break;
	case 3:                 pcMsg = "Card mute";      break;
	case 6: default:        pcMsg = "Driver Problem"; break;
    }
	CHECK(iRet==0, lblKO);
	memcpy(tucRsp, xAtr.historic, xAtr.length);                 // Retrieve ATR and length
	iLen=xAtr.length;

	// Display ATR
	// ===========
	_clrscr();                                                  // Clr Screen
	DisplaySmall(0, 0, "ATR:");                                 // Display ATR message
	for (iCt=0; iCt<iLen; iCt++)
	{
		sprintf (tcDisplay, "%02X", tucRsp[iCt]);
		DisplaySmall(1, 2*iCt, tcDisplay);
	}  
	
	// Print ATR
	// =========
	iRet = pprintf("\x1b""E""         Smart Demo\n\n"           // Print demo in progress
		           "\x1b""F"); CHECK(iRet>=0, lblKO);      
	iRet = pprintf("ATR:\n"); CHECK(iRet>=0, lblKO);            // Print ATR
	for (iCt=0; iCt<iLen; iCt++)
	{
		iRet = pprintf("%02X ", tucRsp[iCt]); CHECK(iRet>=0, lblKO);
	}
	iRet = pprintf("\n"); CHECK(iRet>=0, lblKO);

    // Send command to card for application selection
	// ==============================================
	xApduC.length = 5+14;                                       // APDU length
	memcpy (tucSnd,                                             // APDU request data cla/ins/P1/P2/Le/data
		    "\x00\xA4\x04\x00\x0E"
			"1PAY.SYS.DDF01", 
			xApduC.length); 
    xApduC.data = tucSnd;                                       // Sending buffer
    xApduR.data = tucRsp;                                       // Receiving buffer

    iRet = EMV_apdu(pxSmc, &xApduC, &xApduR);                   // Call APDU communication routine
    if(iRet == 0) 
	{
		if(tucRsp[0] == 0x61)                                   // Retrieve APDU response data (PSE found) 
		{                                                          
			memcpy(tucSnd, "\x00\xC0\x00\x00", 4);              // APDU request data cla/ins/P1/P2/Le      
            tucSnd[4] = tucRsp[1];
            xApduC.length = 5;                                  // APDU length
            iRet = EMV_apdu(pxSmc, &xApduC, &xApduR);           // Call APDU communication routine 
            if(iRet == 0)
                iLen = xApduR.length;
            else
                iRet = -iRet;
		}
    } 
    else
    	iRet = -iRet;

	// Print and display card response
	// ===============================
	iLen = xApduR.length;
    if(iRet < 0) 
    {
		switch (-iRet)                                          // Card errors
		{                                            
		case 1: case 7:         pcMsg = "Card removed";   break;
        case 2: case 4: case 5: pcMsg = "Card Problem";   break;
        case 3:                 pcMsg = "Card mute";      break;
        case 6: default:        pcMsg = "Driver Problem"; break;
        }
		CHECK(iRet==0, lblKO);
    }
	else
	{
        iRet = pprintf("APPLICATION SELECT:\n"); 
		CHECK(iRet>=0, lblKO);           
        if ((tucRsp[iLen-2]==0x6A) && (tucRsp[iLen-1]==0x82))   // PSE not found, List of AIDs Method
        {
        	iRet = pprintf("No PSE, List AIDs Method\n");
		    CHECK(iRet>=0, lblKO);  
		    DisplaySmall(2, 0, "No PSE");
		    DisplaySmall(3, 0, "List AIDs Method");
        }
		if ((tucRsp[iLen-2]==0x90) && (tucRsp[iLen-1]==0x00))   // PSE found, Directory selection Method
		{
			iRet = pprintf("PSE, Directory Selection\n"); 
		    CHECK(iRet>=0, lblKO);
            DisplaySmall(2, 0, "PSE found");
            DisplaySmall(3, 0, "Directory Selection");
		}
	    for (iCt=0; iCt<iLen; iCt++)                            // Print response 
	    {
			iRet = pprintf("%02X ", tucRsp[iCt]); CHECK(iRet>=0, lblKO);                
		}
	    iRet = pprintf("\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);  
    }

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                          // None-classified low level error
	_clrscr();                                                  // Clear screen
	DisplayMedium(0, 0, pcMsg);                                 // Oops! error
    ttestall(0,5*100);                                          // Delay 5s 
lblEnd:
	// Remove smart card
	// =================
    if (pxSmc)
	{
		status (pxSmc, &ucSta);
		switch (ucSta)
		{
		case CAM_PRESENT:                                       // Card present
			DisplaySmall(7, 0, "Remove card...");               // Display remove card
		    power_down(pxSmc);                                  // Card power off
			ttestall(CAM0, 0);                                  // Wait for removal
			break;	
		default:                                                // Card absent
			break;
		}
		fclose(pxSmc);                                          // Close "cam" channel
	}
}
