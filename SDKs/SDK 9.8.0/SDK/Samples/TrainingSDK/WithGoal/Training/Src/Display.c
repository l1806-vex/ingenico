//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  DISPLAY.C                          (Copyright INGENICO 2012)
//============================================================================
//  Created :       10-July-2012     Kassovic
//  Last modified : 10-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :
//                       *** Display management ***
//  This file DOES NOT use the following API(s) for displaying:
//    # System function level (printf, ...)
//      - Native method (obsolete)
//      - Does not support font
//      - No access to color function, only monochrome mode
//      - Does not support touch screen
//    # Graphic library level (DrawString, ...)
//      - Graphic functionalities
//      - Support fonts
//      - No access to color functions, only colorized mode
//      - Does not support touch screen
//    # Color library level (DrawText, ...)
//      - Full color functionalities
//      - Support fonts
//      - Only for color terminals
//      - Does not support touch screen
//  This file uses the Graphic Object Advanced Library (GOAL) for displaying:
//    # Manager goal must be loaded
//    # For all type of terminals (B&W, Color, touch) and display ration supported
//    # 2 modes available
//      - Predefined mode (used inside this file)
//        Message dialog box, Input dialog box, List dialog box, File dialog box etc...
//      - Customized mode
//        . By API(s) (used inside this file)
//          Build your screen using API(s) widgets
//        . Resource file (not used inside this file)
//          Build your screen using WYSIWYG editor
//
//  List of routines in file :  
//      Display : To show the capabilities of the display when using GOAL.
//                            
//  File history :
//  071012-BK : File created
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
// Properties of the XXsmall screen (Goal)
// =======================================
static const ST_DSP_LINE txXXsmall[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_DARK_VIOLET, 0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   GL_COLOR_WHITE, GL_COLOR_RED,         0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {4, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   TRUE,  0, FALSE, {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {2, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_BLACK, GL_COLOR_DARK_ORANGE, 0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 4, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  FALSE, 0, FALSE, {2, 0, 2, 0}, {1, 1, 1, 1, GL_COLOR_BLACK}, {0, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_DARK_GREEN,  0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}}, // Line3
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   GL_COLOR_WHITE, GL_COLOR_DARK_BLUE,   0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {4, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}}, // Line4
	  {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   TRUE, 0, FALSE,  {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {2, 0, 0, 0},  {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_WHITE, GL_COLOR_DARK_RED,    0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 4, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}}, // Line5
      {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  FALSE, 0, FALSE, {2, 0, 2, 0}, {1, 1, 1, 1, GL_COLOR_BLACK}, {0, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}} },
  	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_BLACK, GL_COLOR_DARK_GRAY,   0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}}, // Line6
      {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}} }
};

// Properties of the Xsmall screen (Goal)
// ======================================
static const ST_DSP_LINE txXsmall[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_DARK_VIOLET, 0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   GL_COLOR_WHITE, GL_COLOR_RED,         0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {4, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   TRUE,  0, FALSE, {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {2, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_BLACK, GL_COLOR_DARK_ORANGE, 0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 4, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  FALSE, 0, FALSE, {2, 0, 2, 0}, {1, 1, 1, 1, GL_COLOR_BLACK}, {0, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_DARK_GREEN,  0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line3
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   GL_COLOR_WHITE, GL_COLOR_DARK_BLUE,   0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {4, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line4
	  {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   TRUE, 0, FALSE,  {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {2, 0, 0, 0},  {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_WHITE, GL_COLOR_DARK_RED,    0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 4, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}}, // Line5
      {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  FALSE, 0, FALSE, {2, 0, 2, 0}, {1, 1, 1, 1, GL_COLOR_BLACK}, {0, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XSMALL}} }
};

// Properties of the Small screen (Goal)
// =====================================
static const ST_DSP_LINE txSmall[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_DARK_VIOLET, 0, FALSE, {4, 0, 4, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {4, 3, 4, 3}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   GL_COLOR_WHITE, GL_COLOR_RED,         0, FALSE, {4, 0, 4, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {4, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   TRUE,  0, FALSE, {4, 3, 4, 3}, {0, 0, 0, 0, GL_COLOR_BLACK}, {2, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_BLACK, GL_COLOR_DARK_ORANGE, 0, FALSE, {4, 0, 4, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 4, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  FALSE, 0, FALSE, {4, 3, 4, 3}, {1, 1, 1, 1, GL_COLOR_BLACK}, {0, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_DARK_GREEN,  0, FALSE, {4, 0, 4, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}}, // Line3
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {4, 3, 4, 3}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   GL_COLOR_WHITE, GL_COLOR_DARK_BLUE,   0, FALSE, {4, 0, 4, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {4, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}}, // Line4
	  {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   TRUE,  0, FALSE, {4, 3, 4, 3}, {0, 0, 0, 0, GL_COLOR_BLACK}, {2, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_SMALL}} }
};

// Properties of the Medium screen (Goal)
// ======================================
static const ST_DSP_LINE txMedium[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_DARK_VIOLET, 0, FALSE, {4, 0, 4, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {4, 4, 4, 4}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   GL_COLOR_WHITE, GL_COLOR_RED,         0, FALSE, {4, 0, 4, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {4, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   TRUE,  0, FALSE, {4, 4, 4, 4}, {0, 0, 0, 0, GL_COLOR_BLACK}, {2, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_BLACK, GL_COLOR_DARK_ORANGE, 0, FALSE, {4, 0, 4, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 4, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  FALSE, 0, FALSE, {4, 4, 4, 4}, {1, 1, 1, 1, GL_COLOR_BLACK}, {0, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_DARK_GREEN,  0, FALSE, {4, 0, 4, 0}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line3
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {4, 4, 4, 4}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

// Properties of the Large screen (Goal)
// =====================================
static const ST_DSP_LINE txLarge[] =
{                                        // BUG font Large !!!
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_DARK_VIOLET, 0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   GL_COLOR_WHITE, GL_COLOR_RED,         0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {4, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   TRUE,  0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {2, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  GL_COLOR_BLACK, GL_COLOR_DARK_ORANGE, 0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 4, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line2
	  {GL_ALIGN_CENTER, GL_ALIGN_RIGHT,  FALSE, 0, FALSE, {0, 0, 0, 0}, {1, 1, 1, 1, GL_COLOR_BLACK}, {0, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}} }
};

// Properties of Xlarge screen (Goal)
// ==================================
static const ST_DSP_LINE txXlarge[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_DARK_VIOLET, 0, FALSE, {4, 5, 4, 5}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {4, 8, 4, 8}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   GL_COLOR_WHITE, GL_COLOR_RED,         0, FALSE, {4, 5, 4, 5}, {1, 1, 1, 1, GL_COLOR_WHITE}, {4, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   TRUE,  0, FALSE, {4, 8, 4, 8}, {0, 0, 0, 0, GL_COLOR_BLACK}, {2, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} }
};

// Properties of XXlarge screen (Goal)
// ===================================
static const ST_DSP_LINE txXXlarge[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_DARK_VIOLET, 0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, FALSE, {4, 1, 4, 1}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   GL_COLOR_WHITE, GL_COLOR_RED,         0, FALSE, {4, 2, 4, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {4, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXLARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_LEFT,   TRUE,  0, FALSE, {4, 1, 4, 1}, {0, 0, 0, 0, GL_COLOR_BLACK}, {2, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXLARGE}} }
};

// Properties of Style screen1 (Goal)
// ==================================
static const ST_DSP_LINE txStyle1[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_RED,    GL_COLOR_BLACK, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL,    GL_SCALE_XXLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_YELLOW, GL_COLOR_BLACK, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_BOLD,      GL_SCALE_XXLARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_BOLD, GL_SCALE_XLARGE}} }
};

// Properties of Style screen2 (Goal)
// ==================================
static const ST_DSP_LINE txStyle2[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_GREEN,  GL_COLOR_BLACK, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_ITALIC,      GL_SCALE_XXLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_ITALIC, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_BLUE,   GL_COLOR_BLACK, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_BOLD_ITALIC, GL_SCALE_XXLARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_BOLD_ITALIC, GL_SCALE_XLARGE}} }
};

//****************************************************************************
//                          void Display (void)                            
//  This function shows the capabilities of the display when using GOAL.
//  The following functions has been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateScreen() : To build widgets (Label, Button, ...) on screen.
//   - GoalClrScreen() : To clear a screen.
//   - GoalDspLine() : To display a line on screen.
//   - GoalDestroyScreen() : To destroy all widgets on screen.
//   Support B&W, color and touch terminals.
//   GOAL LATIN italic, bold, bold italic fonts may be loaded to get the full
//   options.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Display(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	bool bFontOk;
    int iRet;

	// Scale XXSMALL
	// *************
	xScreen = GoalCreateScreen(xGoal, txXXsmall, NUMBER_OF_LINES(txXXsmall), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO); // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xxsmall' size on line 1 (see properties)
	iRet = GoalDspLine(xScreen, 0, "XXsmall 0", &txXXsmall[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xxsmall' size on line 2 (see properties)
	iRet = GoalDspLine(xScreen, 1, "XXsmall 1", &txXXsmall[1], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xxsmall' size on line 3 (see properties)
	iRet = GoalDspLine(xScreen, 2, "XXsmall 2", &txXXsmall[2], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xxsmall' size on line 4 (see properties)
	iRet = GoalDspLine(xScreen, 3, "XXsmall 3", &txXXsmall[3], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xxsmall' size on line 5 (see properties)
	iRet = GoalDspLine(xScreen, 4, "XXsmall 4", &txXXsmall[4], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xxsmall' size on line 6 (see properties)
	iRet = GoalDspLine(xScreen, 5, "XXsmall 5", &txXXsmall[5], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xxsmall' size on line 7 (see properties)
	iRet = GoalDspLine(xScreen, 6, "XXsmall 6", &txXXsmall[6], 2*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet!=GL_KEY_CANCEL, lblEnd);  // Exit on cancel key

	GoalDestroyScreen(&xScreen); // Destroy screen

	// Scale XSMALL
	// ************
	xScreen = GoalCreateScreen(xGoal, txXsmall, NUMBER_OF_LINES(txXsmall), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO); // Create new screen and clear it
	iRet = GoalClrScreen(xScreen, 0xFF3B3131, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xsmall' size on line 1 (see properties)
	iRet = GoalDspLine(xScreen, 0, "Xsmall 0", &txXsmall[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xsmall' size on line 2 (see properties)
	iRet = GoalDspLine(xScreen, 1, "Xsmall 1", &txXsmall[1], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xsmall' size on line 3 (see properties)
	iRet = GoalDspLine(xScreen, 2, "Xsmall 2", &txXsmall[2], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xsmall' size on line 4 (see properties)
	iRet = GoalDspLine(xScreen, 3, "Xsmall 3", &txXsmall[3], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xsmall' size on line 5 (see properties)
	iRet = GoalDspLine(xScreen, 4, "Xsmall 4", &txXsmall[4], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xsmall' size on line 6 (see properties)
	iRet = GoalDspLine(xScreen, 5, "Xsmall 5", &txXsmall[5], 2*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet!=GL_KEY_CANCEL, lblEnd);  // Exit on cancel key

	GoalDestroyScreen(&xScreen); // Destroy screen

	// Scale SMALL
	// ***********
	xScreen = GoalCreateScreen(xGoal, txSmall, NUMBER_OF_LINES(txSmall), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO); // Create new screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);
	                             // 'small' size on line 1 (see properties)
	iRet = GoalDspLine(xScreen, 0, "Small 0", &txSmall[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'small' size on line 2 (see properties)
	iRet = GoalDspLine(xScreen, 1, "Small 1", &txSmall[1], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'small' size on line 3 (see properties)
	iRet = GoalDspLine(xScreen, 2, "Small 2", &txSmall[2], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'small' size on line 4 (see properties)
	iRet = GoalDspLine(xScreen, 3, "Small 3", &txSmall[3], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'small' size on line 5 (see properties)
	iRet = GoalDspLine(xScreen, 4, "Small 4", &txSmall[4], 2*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet!=GL_KEY_CANCEL, lblEnd);  // Exit on cancel key

	GoalDestroyScreen(&xScreen); // Destroy screen

	// Scale MEDIUM
	// ************
	xScreen = GoalCreateScreen(xGoal, txMedium, NUMBER_OF_LINES(txMedium), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO); // Create screen and clear it
	iRet = GoalClrScreen(xScreen, 0xFF3B3131, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);
	                             // 'medium' size on line 1 (see properties)
	iRet = GoalDspLine(xScreen, 0, "Medium 0", &txMedium[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'medium' size on line 2 (see properties)
	iRet = GoalDspLine(xScreen, 1, "Medium 1", &txMedium[1], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'medium' size on line 3 (see properties)
	iRet = GoalDspLine(xScreen, 2, "Medium 2", &txMedium[2], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'medium' size on line 4 (see properties)
	iRet = GoalDspLine(xScreen, 3, "Medium 3", &txMedium[3], 2*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet!=GL_KEY_CANCEL, lblEnd);  // Exit on cancel key

	GoalDestroyScreen(&xScreen); // Destroy screen

	// Scale LARGE
	// ***********
	xScreen = GoalCreateScreen(xGoal, txLarge, NUMBER_OF_LINES(txLarge), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO); // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);
	                             // 'large' size on line 1 (see properties)
	iRet = GoalDspLine(xScreen, 0, "Large 0", &txLarge[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'large' size on line 2 (see properties)
	iRet = GoalDspLine(xScreen, 1, "Large 1", &txLarge[1], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'large' size on line 3 (see properties)
	iRet = GoalDspLine(xScreen, 2, "Large 2", &txLarge[2], 2*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet!=GL_KEY_CANCEL, lblEnd);  // Exit on cancel key

	GoalDestroyScreen(&xScreen); // Destroy screen

	// Scale XLARGE
	// ************
	xScreen = GoalCreateScreen(xGoal, txXlarge, NUMBER_OF_LINES(txXlarge), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO); // Create screen and clear it
	iRet = GoalClrScreen(xScreen, 0xFF3B3131, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xlarge' size on line 1 (see properties)
	iRet = GoalDspLine(xScreen, 0, "Xlarge 0", &txXlarge[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xlarge' size on line 2 (see properties)
	iRet = GoalDspLine(xScreen, 1, "Xlarge 1", &txXlarge[1], 2*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet!=GL_KEY_CANCEL, lblEnd);  // Exit on cancel key

	GoalDestroyScreen(&xScreen); // Destroy screen

	// Scale XXLARGE
	// *************
	xScreen = GoalCreateScreen(xGoal, txXXlarge, NUMBER_OF_LINES(txXXlarge), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO); // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xxlarge' size on line 1 (see properties)
	iRet = GoalDspLine(xScreen, 0, "XXlarge 0", &txXXlarge[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'xxlarge' size on line 1 (see properties)
	iRet = GoalDspLine(xScreen, 1, "XXlarge 1", &txXXlarge[1], 2*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet!=GL_KEY_CANCEL, lblEnd);  // Exit on cancel key

	GoalDestroyScreen(&xScreen); // Destroy screen

	// Font Style1
	// ***********
	xScreen = GoalCreateScreen(xGoal, txStyle1, NUMBER_OF_LINES(txStyle1), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO); // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);
	                             // 'normal' style on line 1 (see properties)
	iRet = GoalDspLine(xScreen, 0, "NORMAL", &txStyle1[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'bold' style on line 2 (see properties)
	bFontOk = ParamExist(0xACD6, "GOAL_LATIN_BO");
	if (bFontOk)                 // Check if Latin bold font loaded?
		iRet = GoalDspLine(xScreen, 1, "BOLD", &txStyle1[1], 2*1000, true);
	else
		iRet = GoalDspLine(xScreen, 1, "BOLD (x)", &txStyle1[1], 2*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet!=GL_KEY_CANCEL, lblEnd);  // Exit on cancel key

	GoalDestroyScreen(&xScreen); // Destroy screen

	// Font Style2
	// ***********
	xScreen = GoalCreateScreen(xGoal, txStyle2, NUMBER_OF_LINES(txStyle2), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO); // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);
	                             // 'italic' style on line 1 (see properties)
	bFontOk = ParamExist(0xACD5, "GOAL_LATIN_IT");
	if (bFontOk)                 // Check if Latin italic font loaded?
		iRet = GoalDspLine(xScreen, 0, "ITALIC", &txStyle2[0], 0, false);
	else
		iRet = GoalDspLine(xScreen, 0, "ITALIC (x)", &txStyle2[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                             // 'italic bold' style on line 2 (see properties)
	bFontOk = ParamExist(0xACD7, "GOAL_LATIN_BI");
	if(bFontOk)                  // Check if Latin bold italic font loaded?
		iRet = GoalDspLine(xScreen, 1, "BOLD ITALIC", &txStyle2[1], 30*1000, true);
	else
		iRet = GoalDspLine(xScreen, 1, "BOLD ITALIC (x)", &txStyle2[1], 30*1000, true);
	CHECK(iRet>=0, lblKO);

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                               // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen); // Destroy screen
}
