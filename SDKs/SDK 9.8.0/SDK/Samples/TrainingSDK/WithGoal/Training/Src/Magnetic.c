//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  MAGNETIC.C                         (Copyright INGENICO 2012)
//============================================================================
//  Created :       11-July-2012     Kassovic
//  Last modified : 11-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                     *** Magnetic stripe management ***
//  How to get track 1/2/3 from magnetic card.
//                                                                            
//  List of routines in file :  
//      IsoError : Iso status analysis.
//      Magnetic : Magnetic stripe demo.                                            
//                            
//  File history :
//  071112-BK : File created
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
extern T_GL_HGRAPHIC_LIB xGoal; // New instance of the graphics object library

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
// Properties of the Magnetic screen (Goal)
// ========================================
static const ST_DSP_LINE txMagnetic[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} }
};

// Properties of the Track screen (Goal)
// =====================================
static const ST_DSP_LINE txTrack[] =
{
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line0
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_RED,   100, FALSE, {1, 3, 0, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line1
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, TRUE,  100, FALSE, {2, 4, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line2
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE,  100, FALSE, {1, 3, 0, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line3
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, TRUE,  100, FALSE, {2, 4, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line4
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_GREEN, 100, FALSE, {1, 3, 0, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line5
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, TRUE,  100, FALSE, {2, 4, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} }
};

// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}
};

//****************************************************************************
//                 void IsoError (int iSta, char *pcTrk)                            
//  This function translates the Iso status to an ascii string.
//  This function has parameters:
//     iSta (I-) : Iso status
//     pcTrk (-O) : Ascii string
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
//  This function shows partially the contain of the magnetic stripe ISO123.
//  Then prints the full contain of the magnetic stripe ISO123.
//   - IsISO1-2-3() : Check if ISO1-2-3 devices available
//   - fopen() : Open Iso13, Iso2, Iso3 peripherals
//   - ttestall() : Wait for a card swiped from mag peripheral
//   - is_iso1-2-3() : Retrieve Iso track in ascii format
//   - fclose : Close Iso13, Iso2, Iso3 peripherals
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Magnetic(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xLine;
    FILE *pxMag31=NULL, *pxMag2=NULL, *pxMag3=NULL;
	byte ucLen=0;
    int iSta;
    char tcTmp[128];
    char *pcSrc, *pcDst;
    char tcTrk1[128], tcTrk2[128], tcTrk3[128];
    byte p; // Printer line index
	int iKey, iTimeout=0, iRet;

	// Swipe card in progress
	// **********************
	strcpy(tcTrk1, "No readable data"); // By default
	strcpy(tcTrk2, "No readable data");
	strcpy(tcTrk3, "No readable data");

	// Open peripherals
	// ================
	if (IsISO1() == 1)
	{
		pxMag31 = fopen("SWIPE31", "r*"); // Open mag1 peripheral
		CHECK(pxMag31, lblKO);
	}
    if (IsISO2() == 1)
    {
    	pxMag2 = fopen("SWIPE2", "r*");   // Open mag2 peripheral
    	CHECK(pxMag2, lblKO);
    }
    if (IsISO3() == 1)
    {
    	pxMag3 = fopen("SWIPE3", "r*");   // Open mag3 peripheral
    	CHECK(pxMag3, lblKO);
    }

    // Prompt Swipe a card
    // ===================
	xScreen = GoalCreateScreen(xGoal, txMagnetic, NUMBER_OF_LINES(txMagnetic), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);          // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "Please Swipe", &txMagnetic[0], 0, false);
	CHECK(iRet>=0, lblKO);                // Prompt for a swiping card
	iRet = GoalDspLine(xScreen, 1, "Magnetic Card", &txMagnetic[1], 0, true);
	CHECK(iRet>=0, lblKO);

	// Wait for magnetic card
	// ======================
    iRet = TimerStart(0, 30*100);         // Timer0 starts to 30s
    CHECK(iRet>=0, lblKO);
	do
	{
		iSta = ttestall(SWIPE31 | SWIPE2 | SWIPE3, 10);           // Wait for the first event SWIPE31
		if (iSta != 0)
			break;                                                // Swipe detected
		iKey = GoalGetKey(xScreen, xGoal, true, 100, false);      // Get key pressed/touched (shortcut)
		CHECK(iKey!=GL_KEY_CANCEL, lblEnd);                       // Exit on cancel key
		iTimeout = TimerGet(0);                                   // Retrieve timer value
	}while(iTimeout>0);

	CHECK(iTimeout!=0, lblEnd);                                   // Exit on timeout

	iSta |= ttestall(iSta ^ (SWIPE31 | SWIPE2 | SWIPE3), 10);     // Wait for the second event SWIPE2
	iSta |= ttestall(iSta ^ (SWIPE31 | SWIPE2 | SWIPE3), 10);     // Wait for the third event SWIPE3

	// Retrieve and analyze ISO1
	// =========================
	if(iSta & SWIPE31) 
	{
		memset(tcTmp, 0, sizeof(tcTmp));
	    memset(tcTrk1, 0, sizeof(tcTrk1));
		iRet = is_iso1(pxMag31, &ucLen, (byte*)tcTmp); // *** Read ISO1 to ascii format ***
		if (iRet != ISO_OK)
			IsoError (iRet, tcTrk1);
		else
		{
			CHECK(strlen(tcTmp)<128, lblKO);
			pcSrc = tcTmp;
			pcDst = tcTrk1;
			while(*pcSrc) {                            // Find start sentinel
				if(*pcSrc++ == '%')
					break;
			}
			while(*pcSrc) {                            // Copy all data between start and end sentinels
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
		iRet = is_iso2(pxMag2, &ucLen, (byte*)tcTmp);  // *** Read ISO2 to ascii format ***
		if (iRet != ISO_OK)   
			IsoError (iRet, tcTrk2);
		else
		{
			CHECK(strlen(tcTmp)<128, lblKO);
			pcSrc = tcTmp;
			pcDst = tcTrk2;
			while(*pcSrc) {                            // Find start sentinel
				if(*pcSrc++ == 'B')
					break;
			}
			while(*pcSrc) {                            // Copy all data between start and end sentinels
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
		iRet = is_iso3(pxMag3, &ucLen, (byte*)tcTmp);  // *** Read ISO3 to ascii format ***
		if (iRet != ISO_OK)
			IsoError (iRet, tcTrk3);
		else
		{
			CHECK(strlen(tcTmp)<128, lblKO);
			pcSrc = tcTmp;
			pcDst = tcTrk3;
			while(*pcSrc) {                            // Find start sentinel
				if(*pcSrc++ == 'B')
					break;
			}
			while(*pcSrc) {                            // Copy all data between start and end sentinels
				if(*pcSrc == 'F')
					break;
				if(*pcSrc == 'D')
					*pcSrc = '=';
				*pcDst++ = *pcSrc++;
			}
		}
	}

	if (tcTrk1[0]==0) strcpy(tcTrk1, "Empty");         // Check if track empty
	if (tcTrk2[0]==0) strcpy(tcTrk2, "Empty");
	if (tcTrk3[0]==0) strcpy(tcTrk3, "Empty");

	GoalDestroyScreen(&xScreen); // Destroy screen

	// Display tracks 
	// ==============
	xScreen = GoalCreateScreen(xGoal, txTrack, NUMBER_OF_LINES(txTrack), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);       // Create new screen and clear it

	iRet = GoalDspLine(xScreen, 0, "Track 1 :", &txTrack[0], 0, false); // Show part of track1
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 1, tcTrk1, &txTrack[1], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 2, "Track 2 :", &txTrack[2], 0, false); // Show part of track2
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 3, tcTrk2, &txTrack[3], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 4, "Track 3 :", &txTrack[4], 0, false); // Show part of track3
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 5, tcTrk3, &txTrack[5], 0, true);
	CHECK(iRet>=0, lblKO);

	// Print tracks
	// ============
	p=0;
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);              // Create document

	xLine = xPrinter;                           // Build document (Demo, Track1/2/3 info)
	xLine.eTextAlign = GL_ALIGN_CENTER;
	xLine.bReverse = TRUE;
	xLine.xMargin.usBottom = PIXEL_BOTTOM;
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Magnetic Demo", &xLine);
	CHECK(iRet>=0, lblKO);
/*
	iRet = GoalPrnLine(xDocument, p++, "Track1:", &xPrinter);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, tcTrk1, &xPrinter);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "Track2:", &xPrinter);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, tcTrk2, &xPrinter);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "Track3:", &xPrinter);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, tcTrk3, &xPrinter);
	CHECK(iRet>=0, lblKO);
*/
	iRet = GoalPrnDocument(xDocument);          // Print document
	CHECK(iRet>=0, lblKO);

	iRet = pprintf("Track1:\n%s\n", tcTrk1);    // Print track1
	CHECK(iRet>=0, lblKO);
    iRet = pprintf("Track2:\n%s\n", tcTrk2);    // Print track2
    CHECK(iRet>=0, lblKO);
    iRet = pprintf("Track3:\n%s\n", tcTrk3);    // Print track3
    CHECK(iRet>=0, lblKO);
	iRet = pprintf("\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);  // Wait for key pressed/touched (shortcut)

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                   // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	TimerStop(0);                        // Stop Timer0
    if(pxMag2)
		fclose(pxMag2);                  // Close mag2 peripheral
	if(pxMag3)
		fclose(pxMag3);                  // Close mag3 peripheral
	if(pxMag31)
		fclose(pxMag31);                 // Close mag31 peripheral
	if (xScreen)
		GoalDestroyScreen(&xScreen);     // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument); // Destroy document
}
