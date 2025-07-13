//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  BACKLIGHT.C                        (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-July-2012     Kassovic
//  Last modified : 13-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                        *** Backlight management ***
//  How to adjust the backlight.
//                                                                            
//  List of routines in file :  
//      Backlight : Increase or decrease backlight.
//                            
//  File history :
//  071312-BK : File created
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
// Properties of the Light screen (Goal)
// =====================================
static const ST_DSP_LINE txLight[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_WHITE, GL_COLOR_GREEN, 25, TRUE,  {0, 0, 0, 0},   {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 2, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  FALSE,  0, TRUE,  {0, 0, 0, 0},   {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 2, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE,  60, FALSE, {0, 15, 0, 15}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL,  GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, TRUE,  90, FALSE, {0, 15, 0, 15}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL,  GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE }} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_WHITE, GL_COLOR_GREEN, 25, TRUE,  {0, 0, 0, 0},   {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 3, 2}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  FALSE,  0, TRUE,  {0, 0, 0, 0},   {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 2, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}} },
};

//****************************************************************************
//                         void Backlight (void)                            
//  This function shows how to decrease or increase the backlight.      
//   - HWCNF_SetBacklightIntensity() : Set backlight intensity
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void Backlight(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
    char cVal='%';
    char tcDisplay[50+1];
	int iIdx, iLevel;
    int iKey, iRet;

    // Backlight management
	// ********************
	xScreen = GoalCreateScreen(xGoal, txLight, NUMBER_OF_LINES(txLight), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                                         // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_UP | KEY_DOWN, false);
	CHECK(iRet>=0, lblKO);

    iRet = GoalDspLine(xScreen, 0, "Up to inc", &txLight[0], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 2, "Down to dec", &txLight[2], 0, false);
	CHECK(iRet>=0, lblKO);

	iIdx=0;
	while(1)
	{
		sprintf (tcDisplay, "Backlight:  %d%c", 100-(10*iIdx), cVal);
		iRet = GoalDspLine(xScreen, 1, tcDisplay, &txLight[1], 0, true); // Show backligth percentage
		CHECK(iRet>=0, lblKO);

		iKey = GoalGetKey(xScreen, xGoal, true, 30*1000, true);          // Wait for a key pressed/touched (shortcut)
		CHECK(iKey>=0, lblKO);

        if(iKey==0)
            break;                                                       // Exit on timeout
        if((iKey==GL_KEY_CANCEL) || (iKey==GL_KEY_VALID))
            break;                                                       // Exit on cancel/valid key

		if (iKey==GL_KEY_DOWN)                                           // *** Key DOWN ***
		{
			if(iIdx < 10)
			{
				iIdx++;                                               
				iLevel = iIdx*6554;                                      // Decrease backlight
				if (iLevel >= 0xFFFF)
					iLevel=0xFFFF;                                       // Backlight min
				HWCNF_SetBacklightIntensity(iLevel);                     // Set backlight
			}
		}

        if (iKey==GL_KEY_UP)                                              // *** Key UP ***
		{
			if (iIdx > 0)
			{
				iIdx--;
				iLevel = iIdx*6554;                                      // Increase backlight
				if (iLevel == 0)
					iLevel=0x0001;                                       // Backlight max
				HWCNF_SetBacklightIntensity(iLevel);                     // Set backlight
			}
		}
    }
    
	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                                   // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	HWCNF_SetBacklightIntensity(0x0001);                                 // Backlight max

	if (xScreen)
		GoalDestroyScreen(&xScreen);                                     // Destroy screen
}
