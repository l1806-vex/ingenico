//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  FONTUTF8.C                         (Copyright INGENICO 2012)
//============================================================================
//  Created :       16-July-2012     Kassovic
//  Last modified : 16-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                         *** UTF8 fonts coding ***
//  This file DOES NOT use the following API(s) for unicode font:
//    # Graphic library level (DrawExtendedStringUnicode, pprintfUnicode, ...)
//  This file uses the Graphic Object Advanced Library (GOAL) for UTF font:
//    # Customized mode
//      . By API(s) (used inside this file)
//        Build your screen with font using API(s) widgets
//                                                                            
//  List of routines in file :
//      FontUtf8 : Demo UTF8 character set.
//                            
//  File history :
//  071612-BK : File created
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
// Properties of the Font screen (Goal)
// ====================================
static const ST_DSP_LINE txFont[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK,  0,  TRUE,  {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL,  GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0,  TRUE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL,  GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 1, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line1
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line2
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
};

// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXLARGE}
};

//****************************************************************************
//                          void FontUtf8(void)
//  This function uses the UTF8 character set to show multi-fonts on screen:
//   German, Polish, Turkish, Russian, Arabic and Greek.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void FontUtf8(void)
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	ST_DSP_LINE xDspLine;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xPrnLine;
	byte p; // Printer line index
	bool bFontOk;
	int iRet;
	
	                           // *********************
	                           //         UTF-8       *
	                           // *********************

	xScreen = GoalCreateScreen(xGoal, txFont, NUMBER_OF_LINES(txFont), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                      // Create screen to UTF8

	// Display "Welcome" UTF8 coded (Latin)
	// ************************************
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_VALID | KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);                            // Clear screen

	iRet = GoalDspLine(xScreen, 0, "FONT UTF-8", &txFont[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                                                  // *** German utf-8 ***
 	iRet = GoalDspLine(xScreen, 1, "Mit freundlichen grüßen", &txFont[1], 0, false);
	CHECK(iRet>=0, lblKO);
	                                                  // *** Polish utf-8 ***
	iRet = GoalDspLine(xScreen, 2, "Pożądany", &txFont[2], 0, false);
	CHECK(iRet>=0, lblKO);
	                                                  // *** Turkish utf-8 ***
	iRet = GoalDspLine(xScreen, 3, "Günaydin", &txFont[3], 0, true);
	CHECK(iRet>=0, lblKO);

	// Print "Welcome" UTF8 coded (Latin)
	// **********************************
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);                    // Create document to UTF8

	p=0;                                              // Build document (Demo, Multi-fonts msg)
	xPrnLine = xPrinter;
	xPrnLine.bReverse = TRUE;
	xPrnLine.usSizeWidth = 100;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "UTF-8 Demo", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;
	xPrnLine.eBackAlign = GL_ALIGN_LEFT;
	xPrnLine.xFont.eScale = GL_SCALE_LARGE;           // *** German utf-8 ***
	iRet = GoalPrnLine(xDocument, p++, "Mit freundlichen grüßen\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);
	                                                  // *** Polish utf-8 ***
	iRet = GoalPrnLine(xDocument, p++, "Pożądany\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);
	                                                  // *** Turkish utf-8 ***
	iRet = GoalPrnLine(xDocument, p++, "Günaydin\n\n\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                // Print document
	CHECK(iRet>=0, lblKO);

    if (xDocument)
    {
    	GoalDestroyDocument(&xDocument);              // Destroy document
    	xDocument=NULL;
    }

	iRet = GoalGetKey(xScreen, xGoal, true, 30*1000, true); // Wait for key pressed/touched (shortcut)
	CHECK(iRet>=0, lblKO);
	CHECK(iRet!=GL_KEY_CANCEL, lblEnd);               // Exit on cancel key

	// Display "Welcome" UTF8 coded (Cyrillic/Arabic)
	// **********************************************
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "FONT UTF-8", &txFont[0], 0, false);
	CHECK(iRet>=0, lblKO);

	bFontOk = ParamExist(0xACD8, "GOAL_CYRGRE_NO");   // Check if Cyrillic/Greek (Iso8859-5/7 No) font loaded?
	if (bFontOk)
	{                                                 // *** Russian utf-8 ***
		iRet = GoalDspLine(xScreen, 1, "ДОБР ПОЖАЛОВАТЬ", &txFont[1], 0, true);
		CHECK(iRet>=0, lblKO);
	}
	else
	{                                                 // Font Russian missing
		iRet = GoalDspLine(xScreen, 1, "Font Russian missing", &txFont[1], 0, true);
		CHECK(iRet>=0, lblKO);
	}

	bFontOk = ParamExist(0xACDC, "GOAL_ORIENTA_NO");  // Check if Arabic/Hebrew (ISO 8859-6/8 No) font loaded?
	if (bFontOk)
	{
		xDspLine = txFont[2];
		xDspLine.xColor.eTextAlign=GL_ALIGN_RIGHT;
		xDspLine.xBW.eTextAlign=GL_ALIGN_RIGHT;       // *** Arabic utf-8 ***
		iRet = GoalDspLine(xScreen, 2,"السلام عليكم", &xDspLine, 0, true);
		CHECK(iRet>=0, lblKO);
	}
	else
	{                                                 // Font Arabic missing
		iRet = GoalDspLine(xScreen, 2, "Font Arabic missing", &txFont[2], 0, true);
		CHECK(iRet>=0, lblKO);
	}

	bFontOk = ParamExist(0xACD8, "GOAL_CYRGRE_NO");   // Check if Cyrillic/Greek (Iso8859-5/7 No) font loaded?
	if (bFontOk)
	{                                                 // *** Greek utf-8 ***
		iRet = GoalDspLine(xScreen, 3, "δαλμέρα", &txFont[3], 0, true);
		CHECK(iRet>=0, lblKO);
	}
	else
	{                                                 // Font Greek missing
		iRet = GoalDspLine(xScreen, 3, "Font Greek missing", &txFont[3], 0, true);
		CHECK(iRet>=0, lblKO);
	}

	// Print "Welcome" UTF8 coded (Cyrillic/Arabic)
	// ********************************************
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);                    // Create document to UTF8

	p=0;                                              // Build document (Demo, Multi-fonts msg)
	xPrnLine = xPrinter;
	xPrnLine.bReverse = TRUE;
	xPrnLine.usSizeWidth = 100;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "UTF-8 Demo", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;
	xPrnLine.eBackAlign = GL_ALIGN_LEFT;
	xPrnLine.xFont.eScale = GL_SCALE_LARGE;

	bFontOk = ParamExist(0xACD8, "GOAL_CYRGRE_NO");   // Check if Cyrillic/Greek (Iso8859-5/7 No) font loaded?
	if (bFontOk)
	{                                                 // *** Russian utf-8 ***
		iRet = GoalPrnLine(xDocument, p++, "ДОБР ПОЖАЛОВАТЬ\n", &xPrnLine);
		CHECK(iRet>=0, lblKO);
	}
	else
	{                                                 // Font Russian missing
		iRet = GoalPrnLine(xDocument, p++, "Font GOAL_CYRGRE_NO missing\n\n", &xPrnLine);
		CHECK(iRet>=0, lblKO);
	}

	bFontOk = ParamExist(0xACDC, "GOAL_ORIENTA_NO");  // Check if Arabic/Hebrew (ISO 8859-6/8 No) font loaded?
	if (bFontOk)
	{                                                 // *** Arabic utf-8 ***
		xPrnLine.eBackAlign = GL_ALIGN_RIGHT;
		iRet = GoalPrnLine(xDocument, p++, "السلام عليكم""\n", &xPrnLine);
		CHECK(iRet>=0, lblKO);
	}
	else
	{                                                 // Font Arabic missing
		iRet = GoalPrnLine(xDocument, p++, "Font GOAL_ORIENTAL_NO missing\n\n", &xPrnLine);
		CHECK(iRet>=0, lblKO);
	}

	xPrnLine.eBackAlign = GL_ALIGN_LEFT;
	bFontOk = ParamExist(0xACD8, "GOAL_CYRGRE_NO");   // Check if Cyrillic/Greek (Iso8859-5/7 No) font loaded?
	if (bFontOk)
	{                                                 // *** Greek utf-8 ***
		iRet = GoalPrnLine(xDocument, p++, "δαλμέρα\n\n\n\n", &xPrnLine);
		CHECK(iRet>=0, lblKO);
	}
	else
	{                                                 // Font Greek missing
		iRet = GoalPrnLine(xDocument, p++, "Font GOAL_CYRGRE_NO missing\n\n\n\n\n", &xPrnLine);
		CHECK(iRet>=0, lblKO);
	}

	iRet = GoalPrnDocument(xDocument);                // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);  // Wait for key pressed/touched (shortcut)

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);                  // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);              // Destroy document
}





