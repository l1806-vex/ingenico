//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  FONTISO8859.C                      (Copyright INGENICO 2012)
//============================================================================
//  Created :       16-July-2012     Kassovic
//  Last modified : 16-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :
//                   *** ISO 8859 fonts coding ***
//  This file DOES NOT use the following API(s) for ISO font:
//    # Graphic library level (DrawExtendedString8859, pprintf8859, ...)
//  This file uses the Graphic Object Advanced Library (GOAL) for ISO font:
//    # Customized mode
//      . By API(s) (used inside this file)
//        Build your screen with font using API(s) widgets
//                                                                            
//  List of routines in file :
//      Candara : Demo Candara font (ISO 8859-1).
//      German : Demo ISO 8859-1 character set.
//      Polish : Demo ISO 8859-2 character set.
//      Turkish : Demo ISO 8859-3 character set. 
//      Russian : Demo ISO 8859-5 character set.  
//      Arabic : Demo ISO 8859-6 character set.
//      Greek : Demo ISO 8859-7 character set.
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
// Properties of Candara Font screen1 (Goal)
// =========================================
static const ST_DSP_LINE txCandaraFont1[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_RED,    GL_COLOR_BLACK, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {"CANDARA", GL_FONT_STYLE_NORMAL,    GL_SCALE_XXLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {"CANDARA", GL_FONT_STYLE_NORMAL,      GL_SCALE_XXLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_YELLOW, GL_COLOR_BLACK, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {"CANDARA", GL_FONT_STYLE_BOLD,      GL_SCALE_XXLARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {"CANDARA", GL_FONT_STYLE_BOLD,        GL_SCALE_XXLARGE}} }
};

// Properties of Candara Font screen2 (Goal)
// =========================================
static const ST_DSP_LINE txCandaraFont2[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_GREEN,  GL_COLOR_BLACK, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {"CANDARA", GL_FONT_STYLE_ITALIC,      GL_SCALE_XXLARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {"CANDARA", GL_FONT_STYLE_ITALIC,      GL_SCALE_XXLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_BLUE,   GL_COLOR_BLACK, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {"CANDARA", GL_FONT_STYLE_BOLD_ITALIC, GL_SCALE_XXLARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {"CANDARA", GL_FONT_STYLE_BOLD_ITALIC, GL_SCALE_XXLARGE}} }
};

// Properties of the default Font screen (Goal)
// ============================================
static const ST_DSP_LINE txGoalFont[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK,  0,  TRUE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0,  TRUE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK,  0,  TRUE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line1
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE,  0,  TRUE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE, 100, FALSE, {1, 3, 1, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line2
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, TRUE, 100, FALSE, {2, 2, 2, 2}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_CENTER, GL_ALIGN_CENTER, FALSE, 0, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XXLARGE}
};

//****************************************************************************
//                          void Candara (void)
//  This function shows the display in Candara font mode.
//       DrawExtendedString() : draw an ASCII formatted text with font and type
//       _clrscr() : clear the whole graphic context
//       PaintGraphics() : display the graphic context 
//  This function also prints in CourierNew font mode.
//       pprintf8859() : print an ASCII formatted text with font and type
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Candara(void)
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xPrnLine;
	byte p; // Printer line index
	bool bFontOk;
	int iRet;

	// Candara display in progress
	// ***************************
	bFontOk = ParamExist(0x0161, "CAND_LATIN1");       // Check if Latin (ISO 8859-1 NoBoItBI) font loaded?
	CHECK(bFontOk==true, lblFontMissing);

	// Screen 1
	// ========
	xScreen = GoalCreateScreen(xGoal, txCandaraFont1, NUMBER_OF_LINES(txCandaraFont1), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                       // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);

	                                                   // 'normal' style on line 1 (see properties)
	iRet = GoalDspLine(xScreen, 0, "NORMAL", &txCandaraFont1[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                                                   // 'bold' style on line 2 (see properties)
	iRet = GoalDspLine(xScreen, 1, "BOLD", &txCandaraFont1[1], 2*1000, true);
	CHECK(iRet>=0, lblKO);
	CHECK(iRet!=GL_KEY_CANCEL, lblEnd);                // Exit on cancel key

	GoalDestroyScreen(&xScreen);                       // Destroy screen

	// Screen 2
	// ========
	xScreen = GoalCreateScreen(xGoal, txCandaraFont2, NUMBER_OF_LINES(txCandaraFont2), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                       // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);
	                                                   // 'italic' style on line 1 (see properties)
	iRet = GoalDspLine(xScreen, 0, "ITALIC", &txCandaraFont2[0], 0, false);
	CHECK(iRet>=0, lblKO);
	                                                   // 'italic bold' style on line 2 (see properties)
	iRet = GoalDspLine(xScreen, 1, "BOLD ITALIC", &txCandaraFont2[1], 0, true);
	CHECK(iRet>=0, lblKO);

	// Candara printing in progress
	// ****************************
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);                     // Create document

	p=0;                                               // *** Font scale capability ***
	xPrnLine = xPrinter;
	xPrnLine.xFont.pcName = "CANDARA";
	xPrnLine.bReverse = TRUE;
	xPrnLine.usSizeWidth = 100;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "Font Scale", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;
	xPrnLine.xFont.pcName = "CANDARA";
	xPrnLine.xFont.eScale = GL_SCALE_XXSMALL;          // 'xxsmall' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "XXsmall", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.xFont.eScale = GL_SCALE_XSMALL;           // 'xsmall' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "Xsmall", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.xFont.eScale = GL_SCALE_SMALL;            // 'small' size  (see properties)
	iRet = GoalPrnLine(xDocument, p++, "Small", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.xFont.eScale = GL_SCALE_MEDIUM;           // 'medium' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "Medium", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.xFont.eScale = GL_SCALE_LARGE;            // 'large' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "Large", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.xFont.eScale = GL_SCALE_XLARGE;           // 'xlarge' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "Xlarge", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.xFont.eScale = GL_SCALE_XXLARGE;          // 'xxlarge' size (see properties)
	iRet = GoalPrnLine(xDocument, p++, "XXlarge""\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;                               // *** Font style capabilities ***
	xPrnLine.xFont.pcName = "CANDARA";
	xPrnLine.bReverse = TRUE;
	xPrnLine.usSizeWidth = 100;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "Font Style", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;                               // 'normal' style (see properties)
	xPrnLine.xFont.pcName = "CANDARA";
	iRet = GoalPrnLine(xDocument, p++, "NORMAL", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.xFont.eStyle = GL_FONT_STYLE_BOLD;        // 'bold' style (see properties)
    iRet = GoalPrnLine(xDocument, p++, "BOLD", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.xFont.eStyle = GL_FONT_STYLE_ITALIC;      // 'italic' style (see properties)
	iRet = GoalPrnLine(xDocument, p++, "ITALIC", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.xFont.eStyle = GL_FONT_STYLE_BOLD_ITALIC; // 'bold italic' style (see properties)
	iRet = GoalPrnLine(xDocument, p++, "BOLD ITALIC""\n\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                 // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);   // Wait for key pressed/touched (shortcut)

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                 // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblFontMissing:                                        // File unloaded
	GL_Dialog_Message(xGoal, NULL, "Font CAND_LATIN1\nMissing from System", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);                   // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);               // Destroy document
}

//****************************************************************************
//                          void German(void)                            
//  This function uses the ISO 8859-1 character set.
//  The following functions has been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateScreen() : To build widgets and select ISO font on screen.
//   - GoalClrScreen() : To clear a screen.
//   - GoalDspLine() : To display a line on screen.
//   - GoalDestroyScreen() : To destroy all widgets on screen.
//   Support B&W, color and touch terminals.
//   GOAL LATIN italic, bold, bold italic fonts (All latin)
//   GOAL CYGRE normal, italic, bold, bold italic fonts (All cyrillic and greek)
//   GOAL ORIENTA normal, bold fonts (All arabic and hebrew)
//   may be loaded to get the full options.
//   It represents most Western European languages including:
//   Albanian, Catalan, Danish, Dutch, English, French, Faroese, Finnish,
//   Galician, German, Irish, Icelandic, Italian, Norwegian, Portuguese,
//   Spanish and Swedish.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void German(void)
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xPrnLine;
	byte p; // Printer line index
	int iRet;

	                           // *********************
	                           //      ISO8859-1      *
	                           // *********************

	xScreen = GoalCreateScreen(xGoal, txGoalFont, NUMBER_OF_LINES(txGoalFont), GL_ENCODING_ISO_8859_1);
	CHECK(xScreen!=NULL, lblKO);                       // Create screen to ISO_8859_1 and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "FONT ISO8859-1", &txGoalFont[0], 0, false);
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 1, "German message", &txGoalFont[1], 0, false);
	CHECK(iRet>=0, lblKO);

	// Display German "Welcome" ISO8859 coded
	// **************************************
	iRet = GoalDspLine(xScreen, 2, "\x4D\x69\x74\x20\x66\x72\x65\x75\x6E\x64\x6C\x69\x63\x68\x65\x6E\x20\x67\x72\xFC\xDF\x65\x6E", &txGoalFont[2], 0, true);
	CHECK(iRet>=0, lblKO);

	// Print German "Welcome" ISO8859 coded
	// ************************************
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_ISO_8859_1);
	CHECK(xDocument!=NULL, lblKO);                     // Create document to ISO_8859_1

	p=0;                                               // Build document (Demo, German msg, welcome msg)
	xPrnLine = xPrinter;
	xPrnLine.bReverse = TRUE;
	xPrnLine.usSizeWidth = 100;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "ISO 8859-1 Demo", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;
	xPrnLine.xFont.eScale = GL_SCALE_XLARGE;
	iRet = GoalPrnLine(xDocument, p++, "German message\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.eBackAlign = GL_ALIGN_LEFT;
	iRet = GoalPrnLine(xDocument, p++, "\x4D\x69\x74\x20\x66\x72\x65\x75\x6E\x64\x6C\x69\x63\x68\x65\x6E\x20\x67\x72\xFC\xDF\x65\x6E\n\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                 // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);   // Wait for key pressed/touched (shortcut)

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                 // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);                   // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);               // Destroy document
}


//****************************************************************************
//                          void Polish(void)                            
//  This function uses the ISO 8859-2 character set.
//  The following functions has been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateScreen() : To build widgets and select ISO font on screen.
//   - GoalClrScreen() : To clear a screen.
//   - GoalDspLine() : To display a line on screen.
//   - GoalDestroyScreen() : To destroy all widgets on screen.
//   Support B&W, color and touch terminals.
//   GOAL LATIN italic, bold, bold italic fonts (All latin)
//   GOAL CYGRE normal, italic, bold, bold italic fonts (All cyrillic and greek)
//   GOAL ORIENTA normal, bold fonts (All arabic and hebrew)
//   may be loaded to get the full options.
//   It represents the Slavic languages of Central Europe which use the Latin
//   alphabet. It supports te following languages : Czech, Croat, German,
//   Hungarian, Polish, Romanian, Slovak and Slovenian.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Polish(void)
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	ST_DSP_LINE xDspLine;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xPrnLine;
	byte p; // Printer line index
	int iRet;
	
		                       // *********************
	                           //      ISO8859-2      *
	                           // *********************

	xScreen = GoalCreateScreen(xGoal, txGoalFont, NUMBER_OF_LINES(txGoalFont), GL_ENCODING_ISO_8859_2);
	CHECK(xScreen!=NULL, lblKO);                       // Create screen to ISO_8859_2 and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "FONT ISO8859-2", &txGoalFont[0], 0, false);
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 1, "Polish message", &txGoalFont[1], 0, false);
	CHECK(iRet>=0, lblKO);

	// Display Polish "Welcome" ISO8859 coded
	// **************************************
	xDspLine = txGoalFont[2];
	xDspLine.xBW.xFont.eScale=GL_SCALE_XLARGE;
	iRet = GoalDspLine(xScreen, 2, "\x50\x6F\xBF\xB1\x64\x61\x6E\x79", &xDspLine, 0, true);
	CHECK(iRet>=0, lblKO);

	// Print Polish "Welcome" ISO8859 coded
	// ************************************
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_ISO_8859_2);
	CHECK(xDocument!=NULL, lblKO);                     // Create document to ISO_8859_2

	p=0;                                               // Build document (Demo, Polish msg, welcome msg)
	xPrnLine = xPrinter;
	xPrnLine.bReverse = TRUE;
	xPrnLine.usSizeWidth = 100;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "ISO 8859-2 Demo", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;
	xPrnLine.xFont.eScale = GL_SCALE_XLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Polish message\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.eBackAlign = GL_ALIGN_LEFT;
	iRet = GoalPrnLine(xDocument, p++, "\x50\x6F\xBF\xB1\x64\x61\x6E\x79\n\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                 // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);   // Wait for key pressed/touched (shortcut)

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                 // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);                   // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);               // Destroy document
}

//****************************************************************************
//                          void Turkish(void)                            
//  This function uses the ISO 8859-3 character set.
//  The following functions has been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateScreen() : To build widgets and select ISO font on screen.
//   - GoalClrScreen() : To clear a screen.
//   - GoalDspLine() : To display a line on screen.
//   - GoalDestroyScreen() : To destroy all widgets on screen.
//   Support B&W, color and touch terminals.
//   GOAL LATIN italic, bold, bold italic fonts
//   GOAL CYGRE normal, italic, bold, bold italic fonts
//   GOAL ORIENTA normal, bold fonts
//   may be loaded to get the full options.
//   It represents the following languages:
//   Esperanto, Galician, Maltese and Turkish.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Turkish(void)
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	ST_DSP_LINE xDspLine;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xPrnLine;
	byte p; // Printer line index
	int iRet;
	
		                       // *********************
	                           //      ISO8859-3      *
	                           // *********************

	xScreen = GoalCreateScreen(xGoal, txGoalFont, NUMBER_OF_LINES(txGoalFont), GL_ENCODING_ISO_8859_3);
	CHECK(xScreen!=NULL, lblKO);                       // Create screen to ISO_8859_3 and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "FONT ISO8859-3", &txGoalFont[0], 0, false);
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 1, "Turkish message", &txGoalFont[1], 0, false);
	CHECK(iRet>=0, lblKO);

	// Display Turkish "Welcome" ISO8859 coded
	// ***************************************
	xDspLine = txGoalFont[2];
	xDspLine.xBW.xFont.eScale=GL_SCALE_XLARGE;
	iRet = GoalDspLine(xScreen, 2, "\x47\xFC\x6E\x61\x79\x64\x69\x6E", &xDspLine, 0, true);
	CHECK(iRet>=0, lblKO);

	// Print Turkish "Welcome" ISO8859 coded
	// *************************************
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_ISO_8859_3);
	CHECK(xDocument!=NULL, lblKO);                     // Create document to ISO_8859_3

	p=0;                                               // Build document (Demo, Turkish msg, welcome msg)
	xPrnLine = xPrinter;
	xPrnLine.bReverse = TRUE;
	xPrnLine.usSizeWidth = 100;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "ISO 8859-3 Demo", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;
	xPrnLine.xFont.eScale = GL_SCALE_XLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Turkish message\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.eBackAlign = GL_ALIGN_LEFT;
	iRet = GoalPrnLine(xDocument, p++, "\x47\xFC\x6E\x61\x79\x64\x69\x6E\n\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                  // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);    // Wait for key pressed/touched (shortcut)

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                  // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);                    // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);                // Destroy document
}

//****************************************************************************
//                          void Russian(void)                            
//  This function uses the ISO 8859-5 character set.
//  The following functions has been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateScreen() : To build widgets and select ISO font on screen.
//   - GoalClrScreen() : To clear a screen.
//   - GoalDspLine() : To display a line on screen.
//   - GoalDestroyScreen() : To destroy all widgets on screen.
//   Support B&W, color and touch terminals.
//   GOAL LATIN italic, bold, bold italic fonts
//   GOAL CYGRE normal, italic, bold, bold italic fonts
//   GOAL ORIENTA normal, bold fonts
//   may be loaded to get the full options.
//   It represents various forms of the Cyrillic alphabet. It supports
//   Bulgarian, Byelorussian, Macedonian, Serbian and Ukrainian.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Russian(void)
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
	                           //      ISO8859-5      *
	                           // *********************
	bFontOk = ParamExist(0xACD8, "GOAL_CYRGRE_NO");    // Check if Cyrillic/Greek (Iso8859-5/7 No) font loaded?
	CHECK(bFontOk==true, lblFontMissing);

	xScreen = GoalCreateScreen(xGoal, txGoalFont, NUMBER_OF_LINES(txGoalFont), GL_ENCODING_ISO_8859_5);
	CHECK(xScreen!=NULL, lblKO);                       // Create screen to ISO_8859_5 and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

    iRet = GoalDspLine(xScreen, 0, "FONT ISO8859-5", &txGoalFont[0], 0, false);
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 1, "Russian message", &txGoalFont[1], 0, false);
	CHECK(iRet>=0, lblKO);

	// Display Russian "Welcome" ISO8859 coded
	// ****************************************
	xDspLine = txGoalFont[2];
	xDspLine.xColor.xFont.eScale=GL_SCALE_MEDIUM;
	iRet = GoalDspLine(xScreen, 2, "\xB4\xBE\xB1\xC0\xBE\x20\xBF\xBE\xB6\xB0\xBB\xBE\xB2\xB0\xC2\xCC", &xDspLine, 0, true);
	CHECK(iRet>=0, lblKO);

	// Print Russian "Welcome" ISO8859 coded
	// *************************************
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_ISO_8859_5);
	CHECK(xDocument!=NULL, lblKO);                     // Create document to ISO_8859_5

	p=0;                                               // Build document (Demo, Russian msg, welcome msg)
	xPrnLine = xPrinter;
	xPrnLine.bReverse = TRUE;
	xPrnLine.usSizeWidth = 100;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "ISO 8859-5 Demo", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;
	xPrnLine.xFont.eScale = GL_SCALE_XLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Russian message\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.eBackAlign = GL_ALIGN_LEFT;
	xPrnLine.xFont.eScale = GL_SCALE_LARGE;
	iRet = GoalPrnLine(xDocument, p++, "\xB4\xBE\xB1\xC0\xBE\x20\xBF\xBE\xB6\xB0\xBB\xBE\xB2\xB0\xC2\xCC\n\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                 // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);   // Wait for key pressed/touched (shortcut)

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                 // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblFontMissing:                                        // File unloaded
	GL_Dialog_Message(xGoal, NULL, "Font GOAL_CYRGRE_NO\nMissing from System", GL_ICON_WARNING, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);                   // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);               // Destroy document
}

//****************************************************************************
//                          void Arabic(void)                            
//  This function uses the ISO 8859-6 character set.
//  The following functions has been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateScreen() : To build widgets and select ISO font on screen.
//   - GoalClrScreen() : To clear a screen.
//   - GoalDspLine() : To display a line on screen.
//   - GoalDestroyScreen() : To destroy all widgets on screen.
//   Support B&W, color and touch terminals.
//   GOAL LATIN italic, bold, bold italic fonts
//   GOAL CYGRE normal, italic, bold, bold italic fonts
//   GOAL ORIENTA normal, bold fonts
//   may be loaded to get the full options.
//   It supports the Arabic letter.
//   Each Arabic letter can be represented in 4 positional forms: initial, median,
//   final and isolated. Arabic documents coded in ISO 8859-6 are only viewable
//   after a type of processing called contextual analysis, whereby the character's
//   positions are analyzed so that they can be presented in the proper form.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void Arabic(void)
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
	                           //      ISO8859-6      *
	                           // *********************
	bFontOk = ParamExist(0xACDC, "GOAL_ORIENTA_NO");   // Check if Arabic/Hebrew (ISO 8859-6/8 No) font loaded?
	CHECK(bFontOk==true, lblFontMissing);

	xScreen = GoalCreateScreen(xGoal, txGoalFont, NUMBER_OF_LINES(txGoalFont), GL_ENCODING_ISO_8859_6);
	CHECK(xScreen!=NULL, lblKO);                       // Create screen to ISO_8859_6 and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "FONT ISO8859-6", &txGoalFont[0], 0, false);
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 1, "Arabic message", &txGoalFont[1], 0, false);
	CHECK(iRet>=0, lblKO);

	// Display Arabic "Welcome" ISO8859 coded
	// **************************************
	xDspLine = txGoalFont[2];
	xDspLine.xColor.eTextAlign=GL_ALIGN_RIGHT;
	xDspLine.xBW.eTextAlign=GL_ALIGN_RIGHT; xDspLine.xBW.xFont.eScale=GL_SCALE_XLARGE;
	iRet = GoalDspLine(xScreen, 2, "\xC7\xE4\xD3\xE4\xC7\xE5\x20\xD9\xE4\xEA\xE3\xE5", &xDspLine, 0, true);
	CHECK(iRet>=0, lblKO);

	// Print Arabic "Welcome" ISO8859 coded
	// ************************************
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_ISO_8859_6);
	CHECK(xDocument!=NULL, lblKO);                     // Create document to ISO_8859_6

	p=0;                                               // Build document (Demo, Arabic msg, welcome msg)
	xPrnLine = xPrinter;
	xPrnLine.bReverse = TRUE;
	xPrnLine.usSizeWidth = 100;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "ISO 8859-6 Demo", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;
	xPrnLine.xFont.eScale = GL_SCALE_XLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Arabic message\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.eBackAlign = GL_ALIGN_RIGHT;
	iRet = GoalPrnLine(xDocument, p++, "\xC7\xE4\xD3\xE4\xC7\xE5\x20\xD9\xE4\xEA\xE3\xE5\n\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                 // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);   // Wait for key pressed/touched (shortcut)

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                 // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblFontMissing:                                        // File unloaded
	GL_Dialog_Message(xGoal, NULL, "Font GOAL_ORIENTA_NO\nMissing from System", GL_ICON_WARNING, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);                   // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);               // Destroy document
}

//****************************************************************************
//                          void Greek(void)                            
//  This function uses the ISO 8859-7 character set.
//  The following functions has been developed in customized mode using API(s)
//  widgets (See file Goal.c):
//   - GoalCreateScreen() : To build widgets and select ISO font on screen.
//   - GoalClrScreen() : To clear a screen.
//   - GoalDspLine() : To display a line on screen.
//   - GoalDestroyScreen() : To destroy all widgets on screen.
//   Support B&W, color and touch terminals.
//   GOAL LATIN italic, bold, bold italic fonts
//   GOAL CYGRE normal, italic, bold, bold italic fonts
//   GOAL ORIENTA normal, bold fonts
//   may be loaded to get the full options.
//   It support the modern Greek.
//   There are no emphases, or subscripted iotas, or any of the accents of ancient
//   Greek.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void Greek(void)
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
	                           //      ISO8859-7      *
	                           // *********************
	bFontOk = ParamExist(0xACD8, "GOAL_CYRGRE_NO");    // Check if Cyrillic/Greek (Iso8859-5/7 No) font loaded?
	CHECK(bFontOk==true, lblFontMissing);

	xScreen = GoalCreateScreen(xGoal, txGoalFont, NUMBER_OF_LINES(txGoalFont), GL_ENCODING_ISO_8859_7);
	CHECK(xScreen!=NULL, lblKO);                       // Create screen to ISO_8859_7 and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

    iRet = GoalDspLine(xScreen, 0, "FONT ISO8859-7", &txGoalFont[0], 0, false);
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 1, "Greek message", &txGoalFont[1], 0, false);
	CHECK(iRet>=0, lblKO);

	// Display Greek "Welcome" ISO8859 coded
	// *************************************
	xDspLine = txGoalFont[2];
	xDspLine.xBW.xFont.eScale=GL_SCALE_XLARGE;
	iRet = GoalDspLine(xScreen, 2, "\xEA\xE1\xEB\xE7\xEC\xDD\xF1\xE1", &xDspLine, 0, true);
	CHECK(iRet>=0, lblKO);

	// Print Greek "Welcome" ISO8859 coded
	// ***********************************
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_ISO_8859_7);
	CHECK(xDocument!=NULL, lblKO);                     // Create document to ISO_8859_7

	p=0;                                               // Build document (Demo, Greek msg, welcome msg)
	xPrnLine = xPrinter;
	xPrnLine.bReverse = TRUE;
	xPrnLine.usSizeWidth = 100;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "ISO 8859-7 Demo", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;
	xPrnLine.xFont.eScale = GL_SCALE_XLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Greek message\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine.eBackAlign = GL_ALIGN_LEFT;
	iRet = GoalPrnLine(xDocument, p++, "\xEA\xE1\xEB\xE7\xEC\xDD\xF1\xE1\n\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                 // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);   // Wait for key pressed/touched (shortcut)

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                 // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblFontMissing:                                        // File unloaded
	GL_Dialog_Message(xGoal, NULL, "Font GOAL_CYRGRE_NO\nMissing from System", GL_ICON_WARNING, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);                   // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);               // Destroy document
}





