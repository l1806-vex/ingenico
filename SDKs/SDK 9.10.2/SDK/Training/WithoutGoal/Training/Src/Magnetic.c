//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  MAGNETIC.C                        (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Magnetic stripe management:
//              Print Iso1/Iso2/Iso3 tracks 
//                                                                            
//  List of routines in file :  
//      IsoError : Iso error analysis.
//      Magnetic : Magnetic stripe demo.                                            
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
//                 void IsoError (int iSta, char *pcTrk)                            
//  This function analyzes the Iso error.
//  This function has parameters:
//     iSta (I-) : Iso error
//     pcTrk (I-) : Track buffer error    
//  This function has no return value.                                      
//****************************************************************************

void IsoError(int iSta, char *pcTrk)
{
	switch (iSta)
	{
		case DEF_SEP: strcpy(pcTrk, "Separator fault");  break;
		case DEF_PAR: strcpy(pcTrk, "Parity fault");     break;
		case DEF_LRC: strcpy(pcTrk, "LRC fault");        break;
		case DEF_LUH: strcpy(pcTrk, "Luhn fault");       break;
		case DEF_NUM: strcpy(pcTrk, "Numerical fault");  break;
		case NO_DATA: strcpy(pcTrk, "No readable data"); break;
		default:      strcpy(pcTrk, "Unknown error");    break;
	}
}

//****************************************************************************
//                          void Magnetic (void)                            
//  This function returns the contain of the magnetic stripe ISO1-ISO2-ISO3.      
//       fopen() : open Iso13, Iso2, Iso3 channels
//       ttestall() : Wait for card swiped from mag peripheral
//       is_iso1-2-3() : Retrieve Iso track in ascii format
//       fclose : close Iso13, Iso2, Iso3 channels 
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Magnetic(void) 
{
	// Local variables 
    // ***************
    FILE *pxMag13=NULL, *pxMag2=NULL, *pxMag3=NULL;
	byte ucLen=0;
    int iSta, iNum=0;
    char tcTmp[128];
    char *pcSrc, *pcDst, cKey;	
    char tcTrk1[128], tcTrk2[128], tcTrk3[128];
    char tcDisplay[25+1];
	int iRet;

	// Swipe card in progress
	// **********************
	strcpy(tcTrk1, "No readable data");                               // By default
	strcpy(tcTrk2, "No readable data");
	strcpy(tcTrk3, "No readable data");

	// Open peripherals
	// ================
    pxMag2 = fopen("SWIPE2", "r*"); CHECK(pxMag2!=NULL, lblKO);        // Open "mag2" channel (must be supported, check return code)
	pxMag13 = fopen("SWIPE31", "r*");                                  // Open "mag13" channel (Could not be supported)
    pxMag3 = fopen("SWIPE3", "r*");                                    // Open "mag3" channel (Could not be supported)

    _clrscr();                                                         // Clear screen
	DisplayMedium(0, 0, "Swipe a card...");                            // Display message

	// Wait for events
	// ===============
	reset_buf(pxKbd, _receive_id);                                     // Reset keyboard FIFO
	while(1)
	{
		iSta = ttestall(KEYBOARD | SWIPE31 | SWIPE2 | SWIPE3, 30*100); // Wait for the first event ISO1
		iSta |= ttestall(iSta ^ (SWIPE31 | SWIPE2 | SWIPE3), 10);      // Wait for the second event ISO2
		iSta |= ttestall(iSta ^ (SWIPE31 | SWIPE2 | SWIPE3), 10);      // Wait for the third event ISO3
		
        CHECK(iSta!=0, lblEnd);                                        // Exit if nothing swiped after 30s

        if(iSta & KEYBOARD)                                            // Key event
		{
			cKey = getchar();
		    CHECK(cKey!=T_ANN, lblEnd);                                // Exit on red key 
			continue;
		}
		else
			break;                                                     // Swipe event
	}

	// Retrieve and analyze ISO1
	// =========================
	if(iSta & SWIPE31) 
	{
		memset(tcTmp, 0, sizeof(tcTmp));
	    memset(tcTrk1, 0, sizeof(tcTrk1));
		iRet = is_iso1(pxMag13, &ucLen, (byte*)tcTmp);                 // *** Read ISO1 to ascii format ***
		if (iRet != ISO_OK)
			IsoError (iRet, tcTrk1);
		else
		{
			CHECK(strlen(tcTmp)<128, lblKO); 
			iNum++;
			pcSrc = tcTmp;
			pcDst = tcTrk1;
			while(*pcSrc) {                                            // Find start sentinel
				if(*pcSrc++ == '%')
					break;
			}
			while(*pcSrc) {                                            // Copy all data between start and end sentinels
				if(*pcSrc == '?')
					break;
				*pcDst++ = *pcSrc++;
			}
		}
	}
		
	// Retrieve and analyze ISO2
	// =========================
	if(iSta & SWIPE2)  
	{
		memset(tcTmp, 0, sizeof(tcTmp));
	    memset(tcTrk2, 0, sizeof(tcTrk2));                            
		iRet = is_iso2(pxMag2, &ucLen, (byte*)tcTmp);                  // *** Read ISO2 to ascii format ***
		if (iRet != ISO_OK)   
			IsoError (iRet, tcTrk2);
		else
		{
			CHECK(strlen(tcTmp)<128, lblKO);
			iNum++;
			pcSrc = tcTmp;
			pcDst = tcTrk2;
			while(*pcSrc) {                                            // Find start sentinel
				if(*pcSrc++ == 'B')
					break;
			}
			while(*pcSrc) {                                            // Copy all data between start and end sentinels
				if(*pcSrc == 'F') 
					break;
				if(*pcSrc == 'D')
					*pcSrc = '=';
				*pcDst++ = *pcSrc++;
			}
		}
	}

	// Retrieve and analyze ISO3
	// =========================
	if(iSta & SWIPE3) 
	{
		memset(tcTmp, 0, sizeof(tcTmp));
	    memset(tcTrk3, 0, sizeof(tcTrk3)); 
		iRet = is_iso3(pxMag3, &ucLen, (byte*)tcTmp);                  // *** Read ISO3 to ascci format ***
		if (iRet != ISO_OK)
			IsoError (iRet, tcTrk3);
		else
		{
			CHECK(strlen(tcTmp)<128, lblKO);
			iNum++;
			pcSrc = tcTmp;
			pcDst = tcTrk3;
			while(*pcSrc) {                                            // Find start sentinel
				if(*pcSrc++ == 'B')
					break;
			}
			while(*pcSrc) {                                            // Copy all data between start and end sentinels
				if(*pcSrc == 'F')
					break;
				if(*pcSrc == 'D')
					*pcSrc = '=';
				*pcDst++ = *pcSrc++;
			}
		}
	}

	if (tcTrk1[0]==0) strcpy(tcTrk1, "Empty");
	if (tcTrk2[0]==0) strcpy(tcTrk2, "Empty");
	if (tcTrk3[0]==0) strcpy(tcTrk3, "Empty");

	// Display tracks 
	// ==============
	_clrscr();                                                         // Clr Screen
	DisplaySmall(0, 0, "Track1:");
	sprintf(tcDisplay, "%.25s", tcTrk1);                               // Display part of track1
	DisplaySmall(1, 0, tcDisplay);
    DisplaySmall(2, 0, "Track2:");
    sprintf(tcDisplay, "%.25s", tcTrk2);                               // Display part of track2
    DisplaySmall(3, 0, tcDisplay);
    DisplaySmall(4, 0, "Track3:");
    sprintf(tcDisplay, "%.25s", tcTrk3);                               // Display part of track3
    DisplaySmall(5, 0, tcDisplay);
    DisplaySmall(7, 6, "Press a key");

	// Print tracks 
	// ============
	iRet = pprintf("\x1b""E""       Magnetic Demo\n\n"                 // Print demo in progress
		           "\x1b""F"); CHECK(iRet>=0, lblKO);
	iRet = pprintf("Track1:\n%s\n", tcTrk1); CHECK(iRet>=0, lblKO);    // Print track1
    iRet = pprintf("Track2:\n%s\n", tcTrk2); CHECK(iRet>=0, lblKO);    // Print track2
    iRet = pprintf("Track3:\n%s\n", tcTrk3); CHECK(iRet>=0, lblKO);    // Print track3
	iRet = pprintf("\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);
	
	reset_buf(pxKbd, _receive_id);                                     // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                        // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                                     // Reset keyboard FIFO to clear key pressed

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                                 // None-classified low level error
	_clrscr();                                                         // Clear screen
	DisplayMedium(0, 0, "Processing Error");                           // Oops! error
    ttestall(0,5*100);                                                 // Delay 5s 
lblEnd:
    if(pxMag2)
		fclose(pxMag2);                                                // Close "mag2" channel 
	if(pxMag3)
		fclose(pxMag3);                                                // Close "mag3" channel
	if(pxMag13)
		fclose(pxMag13);                                               // Close "mag13" channel
}
