//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  PRINTER.C                          (Copyright INGENICO 2012)
//============================================================================
//  Created :       10-July-2012     Kassovic
//  Last modified : 10-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :
//                       *** Printer management ***
//  This file DOES NOT use the following API(s) for printing:
//    # System function level (pprintf, ...)
//      - Native method (obsolete)
//      - Does not support font
//    # Graphic library level (pprintf8859, pprintfUnicode, ...)
//      - Graphic functionalities
//      - Support fonts
//  This file uses the Graphic Object Advanced Library (GOAL) for printing:
//    # Manager goal must be loaded
//    # Customized mode
//      . By API(s) (used inside this file)
//        Build your document using API(s) widgets
//                                                                            
//  List of routines in file :  
//      Printer : To show the capabilities of the printer when using GOAL.
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
// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXSMALL}
};

static const ST_PADDING xPadding = {4, 0, 4, 0,};              // Padding properties
static const ST_BORDER xBorder = {4, 4, 4, 4, GL_COLOR_BLACK}; // Border properties
static const ST_MARGIN xMargin = {1, 10, 1, 10};               // Margin properties

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
    /* */

//****************************************************************************
//                          void Printer (void)                            
//  This function shows the capabilities of the printer when using GOAL.
//  The following functions has been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateDocument() : To build widgets on a document.
//   - GoalPrnLine() : To add a line on document.
//   - GoalPrnDocument : To print the document.
//   - GoalDestroyDocument() : To destroy all widgets on a document.
//   Support all terminals with an internal printer.
//   GOAL LATIN italic, bold, bold italic fonts may be loaded to get the full
//   options.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Printer(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xLine;
	byte p; // Printer line index
	bool bFontOk;
    int iRet;

    // Printing in progress
	// ********************
    GL_Dialog_Message(xGoal, NULL, "Please Wait""\n""Printing In Progress", GL_ICON_INFORMATION, GL_BUTTON_NONE, 0);

	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);                  // Create document

	p=0;                                            // *** Font scale capability ***
	xLine = xPrinter;
	xLine.bReverse = TRUE;
	xLine.usSizeWidth = 100;
	xLine.xMargin.usBottom = PIXEL_BOTTOM;
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Font Scale", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine = xPrinter;                               // 'xxsmall' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "XXsmall", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.xFont.eScale = GL_SCALE_XSMALL;           // 'xsmall' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "Xsmall", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.xFont.eScale = GL_SCALE_SMALL;            // 'small' size  (see properties)
	iRet = GoalPrnLine(xDocument, p++, "Small", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.xFont.eScale = GL_SCALE_MEDIUM;           // 'medium' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "Medium", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.xFont.eScale = GL_SCALE_LARGE;            // 'large' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "Large", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.xFont.eScale = GL_SCALE_XLARGE;           // 'xlarge' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "Xlarge", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.xFont.eScale = GL_SCALE_XXLARGE;          // 'xxlarge' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "XXlarge""\n\n", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine = xPrinter;                               // *** Font style capabilities ***
	xLine.bReverse = TRUE;
	xLine.usSizeWidth = 100;
	xLine.xMargin.usBottom = PIXEL_BOTTOM;
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Font Style", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine = xPrinter;                               // 'normal' style (see properties)
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "NORMAL", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.xFont.eStyle = GL_FONT_STYLE_BOLD;        // 'bold' style (see properties)
	bFontOk = ParamExist(0xACD6, "GOAL_LATIN_BO");  // Check if Latin bold font loaded?
    if (bFontOk)
    	iRet = GoalPrnLine(xDocument, p++, "BOLD", &xLine);
    else
    	iRet = GoalPrnLine(xDocument, p++, "BOLD (x)", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.xFont.eStyle = GL_FONT_STYLE_ITALIC;      // 'italic' style (see properties)
	bFontOk = ParamExist(0xACD5, "GOAL_LATIN_IT");  // Check if Latin italic font loaded?
	if (bFontOk)
		iRet = GoalPrnLine(xDocument, p++, "ITALIC", &xLine);
	else
		iRet = GoalPrnLine(xDocument, p++, "ITALIC (x)", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.xFont.eStyle = GL_FONT_STYLE_BOLD_ITALIC; // 'bold italic' style (see properties)
	bFontOk = ParamExist(0xACD7, "GOAL_LATIN_BI");  // Check if Latin bold italic font loaded?
	if (bFontOk)
		iRet = GoalPrnLine(xDocument, p++, "BOLD ITALIC""\n\n", &xLine);
	else
		iRet = GoalPrnLine(xDocument, p++, "BOLD ITALIC (x)""\n\n", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine = xPrinter;                               // *** Font format capabilities ***
	xLine.bReverse = TRUE;
	xLine.usSizeWidth = 100;
	xLine.xMargin.usBottom = PIXEL_BOTTOM;
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Font Format", &xLine);
	CHECK(iRet>=0, lblKO);

    xLine = xPrinter;                               // 'center' adjust (see properties)
    xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "CENTER", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.eBackAlign = GL_ALIGN_LEFT;               // 'left' adjust (see properties)
	iRet = GoalPrnLine(xDocument, p++, "LEFT", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.eBackAlign = GL_ALIGN_RIGHT;              // 'right' adjust (see properties)
	iRet = GoalPrnLine(xDocument, p++, "RIGHT", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.eBackAlign = GL_ALIGN_CENTER;             // 'border center' adjust (see properties)
	xLine.xPadding = xPadding;
	xLine.xBorder = xBorder;
	iRet = GoalPrnLine(xDocument, p++, "BORDER", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.bReverse = TRUE;                          // 'reverse center' adjust (see properties)
	xLine.xMargin = xMargin;
	iRet = GoalPrnLine(xDocument, p++, "REVERSE", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine.bReverse = FALSE;                         // 'normal center' adjust (see properties)
	xLine.xBorder = xPrinter.xBorder;
	iRet = GoalPrnLine(xDocument, p++, "NORMAL""\n\n", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine = xPrinter;                               // *** Print text capabilities ***
	xLine.bReverse = TRUE;
	xLine.usSizeWidth = 100;
	xLine.xMargin.usBottom = PIXEL_BOTTOM;
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Print Text", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine = xPrinter;                               // Short string
	xLine.eTextAlign = GL_ALIGN_LEFT;
	xLine.usSizeWidth = 100;
	xLine.xFont.eScale = GL_SCALE_LARGE;
	iRet = GoalPrnLine(xDocument, p++, "Short string", &xLine);
	CHECK(iRet>=0, lblKO);                          // Long string
	iRet = GoalPrnLine(xDocument, p++, "Now try a long string:\n"
			                "0123456789012345678901234567890123456789""\n\n\n\n\n", &xLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);              // Print document
	CHECK(iRet>=0, lblKO);

	iRet=1;

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                   // None-classified low level error
    GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
    if (xDocument)
    	GoalDestroyDocument(&xDocument); // Destroy document
}


