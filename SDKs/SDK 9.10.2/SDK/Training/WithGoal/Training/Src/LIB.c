//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  LIB.C                             (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-July-2012     Kassovic
//  Last modified : 13-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                         *** Static LIB management ***
//      Show how to call a LIB.
//      The static library BeepLib is generated during the training.
//                                                                            
//  List of routines in file :  
//      BeepLib : Beep LIB demo.                                            
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
#include "MyLibExport.h"

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
// Properties of the Lib screen (Goal)
// ===================================
static const ST_DSP_LINE txLib[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} }
};


//****************************************************************************
//                          void BeepLib (void)                            
//  This function runs the LIB called Beep.      
//  This function has no parameters.    
//  This function has no return value.
//****************************************************************************

void BeepLib(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
    int iRet;

	// Call the functions from the LIB
	// ===============================
	xScreen = GoalCreateScreen(xGoal, txLib, NUMBER_OF_LINES(txLib), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);      // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "Press Valid", &txLib[0], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 1, "To hear 1 Beep", &txLib[1], 30*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet==GL_KEY_VALID, lblEnd); // Exit on cancel key or timeout

	OneBeepLIB();                      // Call function OneBeepLIB()

	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 0, "Press Valid", &txLib[0], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 1, "To hear 3 Beeps", &txLib[1], 30*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet==GL_KEY_VALID, lblEnd); // Exit on cancel key or timeout

	iRet = ManyBeepLIB(3);             // Call function ManyBeepLIB()
	CHECK(iRet==2*3, lblKO);

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);
}



