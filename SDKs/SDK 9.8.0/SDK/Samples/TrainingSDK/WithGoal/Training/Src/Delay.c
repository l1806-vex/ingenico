//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  DELAY.C                            (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-July-2008     Kassovic
//  Last modified : 13-July-2008     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                        *** Delay management ***
//  How to handle a cyclic delay.
//                                                                            
//  List of routines in file :  
//      Periodic : Periodic function call.
//      Delay : Delay demo.                                            
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
#define PRTW  24

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the Delay screen (Goal)
// =====================================
static const ST_DSP_LINE txDelay[] =
{
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE,  100, FALSE, {1, 0, 0, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line1
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, TRUE,  100, FALSE, {2, 2, 0, 2}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_RED,   GL_COLOR_BLACK,   0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line3
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,   0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

static char tcBuf[50+1];
static short sTo;

// Periodic function
// *****************
static word Periodic (void)
{
	strcat(tcBuf, "* ");
	sTo--;
	return 0;
}

//****************************************************************************
//                          void Delay (void)                            
//  This function calls cyclically a routine with a periodic delay.      
//   - GetDelayUser() : Retrieve a delay number
//   - StartLDelay() : Start a cyclic delay
//   - StopDelay() : Stop a cyclic delay
//   - FreeDelayUser() : Release the delay number
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Delay(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	word usDlyNbr=0;
	doubleword uiTime, uiPeriod;
    int iRet;            

	// Demo Delay in progress
	// **********************
    usDlyNbr = GetDelayUser();                            // Get a delay number
	xScreen = GoalCreateScreen(xGoal, txDelay, NUMBER_OF_LINES(txDelay), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                          // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "Delay Running...", &txDelay[0], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 1, "Waiting for 10s", &txDelay[1], 0, false);
	CHECK(iRet>=0, lblKO);

	// Repeat cyclically 10 times the function Periodic every 1s delay
	// ===============================================================
	memset(tcBuf, 0, sizeof(tcBuf));                      // Reset printing buffer
	sTo=10;                                               // TimeOut
	iRet = StartLDelay(usDlyNbr, 1*100, 1*100, Periodic); // Start periodic delay of 1 second
	CHECK(iRet==0, lblKO);
	while(sTo > 0)                                        // Wait until TimeOut expired
	{                                                     // Show stars
		iRet = GoalDspLine(xScreen, 2, tcBuf, &txDelay[2], 200, true);
		CHECK(iRet>=0, lblKO);
		CHECK(iRet!=GL_KEY_CANCEL, lblEnd);               // Exit on cancel key
	}
	iRet = StopDelay(usDlyNbr, &uiTime, &uiPeriod);       // Stop periodic delay
	CHECK(iRet==0, lblKO);
                                                          // Show stars
	iRet = GoalDspLine(xScreen, 2, tcBuf, &txDelay[2], 1*1000, true);
	CHECK(iRet>=0, lblKO);
	buzzer(10);
    iRet = GoalDspLine(xScreen, 3, "Delay stopped !!!", &txDelay[3], 5*1000, true);
	CHECK(iRet>=0, lblKO);

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                     // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	StopDelay(usDlyNbr, &uiTime, &uiPeriod);               // Stop periodic delay if not already done
    FreeDelayUser(usDlyNbr);                               // Release the delay number

	if (xScreen)
		GoalDestroyScreen(&xScreen);                       // Destroy screen
}
