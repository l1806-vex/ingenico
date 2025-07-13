//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  MESSAGE.C                         (Copyright INGENICO 2012)
//============================================================================
//  Created :       16-July-2012     Kassovic
//  Last modified : 16-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//        *** Allow to customize application's messages and languages ***
//  The file SAMPLEMSG.SGN is built with the tool BuildMSG.exe.
//  This tool can generate a local language (English) and custom languages
//  (English, Russian, German and Arabic).
//  The following files corresponding to the message language are saved in
//  UTF8 encoding:
//  - SampleLocalEnglish.h  => Local language to generate English.c file
//                             and compile with the application
//  - SampleCustEnglish.h   => First custom language  -
//  - SampleCustGerman.h    => Second custom language  |_ generate SAMPLEMSG.SGN
//  - SampleCustRussian.h   => Third custom language   |
//  - SampleCustArabic.h    => Fourth custom language -
//  If the SAMPLEMSG.SGN is not loaded inside the terminal, only the local language
//  is available (English). When loading SAMPLEMSG.SGN, new custom languages are
//  now available (English, German, Russian and Arabic).
//                                                                            
//  List of routines in file :
//      DefaultSettings : Load the SAMPLEMSG.SGN messages file in the memory.
//      GetMsg : Display and print messages in the current language. 
//      SelectLanguage : Select the current language.
//      Testing : Language testing.
//                            
//  File history :
//  071612-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "MessagesDefinitions.h" // Messages' name definitions
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern T_GL_HGRAPHIC_LIB xGoal; // New instance of the graphics object library
extern const byte English[];    // Default messages in English
extern FILE *pxKbd;             // Peripheral file Keyboard

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define MAX_LANG 8

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the Msg screen (Goal)
// ===================================
static const ST_DSP_LINE txMsg[] =
{
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE, 100, FALSE, {1, 3, 1, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line1
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, TRUE, 100, FALSE, {2, 2, 2, 2}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE, 100, FALSE, {1, 3, 1, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}}, // Line2
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, TRUE, 100, FALSE, {2, 2, 2, 2}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

// Properties of the Test screen (Goal)
// ====================================
static const ST_DSP_LINE txTest[] =
{
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE, 100, FALSE, {1, 3, 1, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line1
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, TRUE, 100, FALSE, {2, 2, 2, 2}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLUE, 100, FALSE, {1, 3, 1, 3}, {1, 1, 1, 1, GL_COLOR_WHITE}, {3, 0, 3, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line2
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, TRUE, 100, FALSE, {2, 2, 2, 2}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}
};

static int iDefItem; // Default item selected

//****************************************************************************
//                          void DefaultSettings (void)                            
//  This function loads the SAMPLEMSG.SGN messages file in the memory to
//   use the new language selected.
//   - LoadMSG() : Load message file
//   - DefCurrentMSG() : Register the message file used by the application
//   - DefCurrentLang(): Register the language used by the application
//   - DefDefaultMSG() : Register the default message used by the application
//   - DefDefaultLang(): Register the default language used by the application
//   if this file cannot be loaded, english default messages are used.
//   The file SAMPLEMSG.SGN allows to customize application's messages and
//   languages.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void DefaultSettings (void)
{
	// Local variables 
    // ***************
	char *pcNewMsg; 	                         // Address of the loaded message file

	// Loading new messages
	// ********************
	iDefItem=0;                                  // Language selection to English by default

	pcNewMsg = LoadMSG("/SYSTEM/SAMPLEMSG.SGN"); // Load the SGN file in memory
	if (pcNewMsg == NULL )
	{
		GL_Dialog_Message(xGoal, NULL, "File SAMPLEMSG.SGN\nMissing from System", GL_ICON_WARNING, GL_BUTTON_NONE, 3*1000);
		DefCurrentMSG((char *)English);          // Local messages are used
	}
	else
		DefCurrentMSG(pcNewMsg);                 // New messages are used

	DefDefaultMSG((char *)English);              // Messages used by default (if not present in current MSG file)
	DefCurrentLang(EN);                          // Define current and default languages (English)
	DefDefaultLang(EN);
}

//****************************************************************************
//                          void GetMsg (void)                            
//  This function displays and prints messages in the application's current 
//   language.
//   - GetCurrentLang() : Get the language used by the application
//   - GetMessageInfos() : Return the message with the given message number
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void GetMsg(void)
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	ST_DSP_LINE xDspLine;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xPrnLine;
	MSGinfos xMSGSelect;
	byte p; // Printer line index
	char *pcLang;
	bool bFontOk;
	int iRet;

	// Get the language selected
	// *************************
	pcLang = GetCurrentLang();
	if (strcmp(pcLang, "RU") == 0)             // Check if cyrillic/greek font loaded?
	{
		bFontOk = ParamExist(0xACD8, "GOAL_CYRGRE_NO");
		CHECK(bFontOk==true, lblCyrgreMissing);
	}
	if (strcmp(pcLang, "AR") == 0)             // Check if arabic/hebrew font loaded?
	{
		bFontOk = ParamExist(0xACDC, "GOAL_ORIENTA_NO");
		CHECK(bFontOk==true, lblOrientaMissing);
	}

	// Display hello in the language selected
	// **************************************
	xScreen = GoalCreateScreen(xGoal, txMsg, NUMBER_OF_LINES(txMsg), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);               // Create screen to UTF8 and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	xDspLine = txMsg[0];                       // txMsg[0] and txMsg[1] same properties
	if(strcmp(pcLang, "AR") == 0)              // Change some properties if Arabic language
	{
		xDspLine.xColor.eTextAlign=GL_ALIGN_RIGHT;
		xDspLine.xBW.eTextAlign=GL_ALIGN_RIGHT;
	}

    iRet = GetMessageInfos(DISPLAY_LANGUAGE, &xMSGSelect);
    CHECK(iRet==0, lblKO);                     // Retrieve and show language name
    iRet = GoalDspLine(xScreen, 0, xMSGSelect.message, &xDspLine, 0, false);
    CHECK(iRet>=0, lblKO);

	iRet = GetMessageInfos(DISPLAY_HELLO, &xMSGSelect);
	CHECK(iRet==0, lblKO);                     // Retrieve and show the welcome message
    iRet = GoalDspLine(xScreen, 1, xMSGSelect.message, &xDspLine, 0, true);
    CHECK(iRet>=0, lblKO);

	// Print hello in the language selected
	// ************************************
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);             // Create document to UTF8

	p=0;                                       // Build document (Demo, Language name, Welcome msg)
	xPrnLine = xPrinter;
	xPrnLine.eTextAlign = GL_ALIGN_CENTER;
	xPrnLine.bReverse = TRUE;
	xPrnLine.xFont.eScale = GL_SCALE_XXLARGE;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "Message Demo", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	xPrnLine = xPrinter;
	if(strcmp(pcLang, "AR") == 0)              // Change some properties if Arabic language
		xPrnLine.eTextAlign=GL_ALIGN_RIGHT;

    iRet = GetMessageInfos(PRINTER_LANGUAGE, &xMSGSelect);
    CHECK(iRet==0, lblKO);                     // Retrieve language name to print
	xPrnLine.xFont.eScale = GL_SCALE_XLARGE;
	iRet = GoalPrnLine(xDocument, p++, xMSGSelect.message, &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GetMessageInfos(PRINTER_HELLO, &xMSGSelect);
	CHECK(iRet==0, lblKO);                     // Retrieve welcome message to print
	iRet = GoalPrnLine(xDocument, p++, xMSGSelect.message, &xPrnLine);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);         // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true); // Wait for key pressed/touched (shortcut)

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                         // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblCyrgreMissing:                                    // File unloaded
	GL_Dialog_Message(xGoal, NULL, "Font GOAL_CYRGRE_NO\nMissing from System", GL_ICON_WARNING, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblOrientaMissing:                                    // File unloaded
	GL_Dialog_Message(xGoal, NULL, "Font GOAL_ORIENTA_NO\nMissing from System", GL_ICON_WARNING, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);           // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);       // Destroy document
}

//****************************************************************************
//                          void LanguageSelect (void)                            
//  This function shows a menu to select the application language.
//   - GetCurrentMSG() : Get message file used by the application
//   - GetSupportedLanguages() : How many languages supported by message file
//   - DefCurrentLang() : Register the language used by the application
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void SelectLang (void)
{
	// Local variables 
    // ***************
	char tcLang[2*MAX_LANG], ttcLang[MAX_LANG][3], *tpcLang[MAX_LANG+1];
	int iLoadLang;	  // Number of languages in the loaded MSG file
	int iNbrLang=0;   // Number of languages in the terminal
	int i, iItem;
	
	// Language selection
	// ******************

	// Get the languages supported by the application (local:English or loaded MSG file:Russian...)
    // ============================================================================================
	memset(ttcLang, 0, 3*MAX_LANG);
    strcpy(ttcLang[iNbrLang++], EN);                            // English messages are always defined (local messages)
    
    iLoadLang = GetSupportedLanguages(tcLang, GetCurrentMSG()); // Number of loaded language
	for(i=0; i<iLoadLang; i++)
	{
		if ((memcmp(&tcLang[i*2], EN, 2))!=0)                   // EN already exist (local replaced by loaded messages)
			memcpy(ttcLang[iNbrLang++], &tcLang[i*2], 2);       // Copy the language code
		tpcLang[i] = ttcLang[i];                                // Initialize table of pointers
	}
	tpcLang[i] = NULL;                                          // End of table of pointers
	
	// Select the language to use
	// ==========================
	iItem = GL_Dialog_Choice(xGoal, "Language", (const char**) tpcLang, iDefItem, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);
	if ((iItem!=GL_KEY_CANCEL) && (iItem!=GL_RESULT_INACTIVITY))
	{
		DefCurrentLang(ttcLang[iItem]);                         // Set the language selected
		iDefItem=iItem;
	}
}

//****************************************************************************
//                          void Testing (void)                            
//  This function returns informations regarding application language.
//   - GetMessageInfos() : Return the message with the given message number
//   - GetSpecificMessage() : Return the specific message with the given message number
//   - GetCurrentMSG(): Get message file used by the application
//   - LanguageExist() : Check if the language exists inside the language file
//   - GetMessageInfosInLang() : Return the message with the given language/message number
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Testing (void)
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	ST_DSP_LINE xDspLine;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xPrnLine;
	char *pcLang;
	MSGinfos xMSGTest;
	byte p;     // Printer line index
	char tcPrinter[100+1];
	bool bFontOk;
	int iRet;

	// Get the language selected
	// *************************
	pcLang = GetCurrentLang();
	if (strcmp(pcLang, "RU") == 0)                       // Check if cyrillic/greek font loaded?
	{
		bFontOk = ParamExist(0xACD8, "GOAL_CYRGRE_NO");
		CHECK(bFontOk==true, lblCyrgreMissing);
	}
	if (strcmp(pcLang, "AR") == 0)                       // Check if arabic/hebrew font loaded?
	{
		bFontOk = ParamExist(0xACDC, "GOAL_ORIENTA_NO");
		CHECK(bFontOk==true, lblOrientaMissing);
	}

	// Displaying in progress
	// **********************
	xScreen = GoalCreateScreen(xGoal, txTest, NUMBER_OF_LINES(txTest), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                         // Create screen to UTF8 and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	// Display selected language message
	// =================================
    iRet = GoalDspLine(xScreen, 0, "Message current font:", &txTest[0], 0, false);
    CHECK(iRet>=0, lblKO);

	xDspLine = txTest[1];
	if(strcmp(pcLang, "AR") == 0)                        // Change some properties if Arabic language
	{
		xDspLine.xColor.eTextAlign=GL_ALIGN_RIGHT;
		xDspLine.xBW.eTextAlign=GL_ALIGN_RIGHT;
	}

	iRet = GetMessageInfos(DISPLAY_HELLO, &xMSGTest);
	CHECK(iRet==0, lblKO);                               // Retrieve and show the welcome message already selected
    iRet = GoalDspLine(xScreen, 1, xMSGTest.message, &xDspLine, 0, false);
    CHECK(iRet>=0, lblKO);

	// Display local language message
	// ==============================
    iRet = GoalDspLine(xScreen, 2, "Message local font:", &txTest[2], 0, false);
    CHECK(iRet>=0, lblKO);
                                                         // Retrieve and show the default welcome message
    iRet = GetSpecificMessage((char *)English, (byte*)EN, OBJECT_TYPE_APPLI, ApplicationGetCurrentAppliType(), DISPLAY_HELLO, &xMSGTest);
	CHECK(iRet==0, lblKO);
    iRet = GoalDspLine(xScreen, 3, xMSGTest.message, &txTest[3], 0, true);
    CHECK(iRet>=0, lblKO);

    // Printing in progress
	// ********************
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);                       // Create document to UTF8

	p=0;                                                 // Build document (Test, Manager language, App type, Selected and default language)
	xPrnLine = xPrinter;
	xPrnLine.eTextAlign=GL_ALIGN_CENTER;
	xPrnLine.bReverse = TRUE;
	xPrnLine.xFont.eScale = GL_SCALE_XXLARGE;
	xPrnLine.xMargin.usBottom = PIXEL_BOTTOM;
	iRet = GoalPrnLine(xDocument, p++, "Message Test", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	// Print Manager stuff
    // ===================                               // Get Manager language
	sprintf(tcPrinter, "Manager language: %s\n\n", GetManagerLanguage());
	iRet = GoalPrnLine(xDocument, p++, tcPrinter, &xPrinter);
	CHECK(iRet>=0, lblKO);
	                                                     // Get file type and application type
	sprintf(tcPrinter, "File Type: %X\nApplication Type: %X\n\n",
			           OBJECT_TYPE_APPLI, ApplicationGetCurrentAppliType());
	iRet = GoalPrnLine(xDocument, p++, tcPrinter, &xPrinter);
	CHECK(iRet>=0, lblKO);

	// Print selected language message
	// ===============================
	xPrnLine = xPrinter;
	if(strcmp(pcLang, "AR") == 0)                        // Change some properties if Arabic language
		xPrnLine.eTextAlign=GL_ALIGN_RIGHT;

	iRet = GetMessageInfos(PRINTER_HELLO, &xMSGTest);    // Retrieve the welcome message already selected
	CHECK(iRet==0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "Message current font:", &xPrinter);
	CHECK(iRet>=0, lblKO);                               // Selected welcome message to print
	iRet = GoalPrnLine(xDocument, p++, xMSGTest.message, &xPrnLine);
	CHECK(iRet>=0, lblKO);
	//iRet = GoalPrnLine(xDocument, p++, "\n", &xPrinter);
	//CHECK(iRet>=0, lblKO);

	// Print local language message
	// ============================                      // Retrieve the default welcome message
	iRet = GetSpecificMessage((char *)English, (byte*)EN, OBJECT_TYPE_APPLI, ApplicationGetCurrentAppliType(), PRINTER_HELLO, &xMSGTest);
	CHECK(iRet==0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "Message local font:", &xPrinter);
	CHECK(iRet>=0, lblKO);                               // Default welcome message to print
	iRet = GoalPrnLine(xDocument, p++, xMSGTest.message, &xPrinter);
	CHECK(iRet>=0, lblKO);
	//iRet = GoalPrnLine(xDocument, p++, "\n", &xPrinter);
	//CHECK(iRet>=0, lblKO);

	// Print Russian language message if present
	// =========================================
	xPrnLine = xPrinter;                                 // Check if Russian welcome message exist
	iRet = GoalPrnLine(xDocument, p++, "Russian font exists?:", &xPrinter);
	CHECK(iRet>=0, lblKO);
	if(LanguageExist("RU", GetCurrentMSG()) == 0)
	{                                                    // Retrieve Russian welcome message to print
		bFontOk = ParamExist(0xACD8, "GOAL_CYRGRE_NO");
		if (bFontOk)
		{
			iRet = GetMessageInfosInLang("RU", PRINTER_HELLO, &xMSGTest);
			CHECK(iRet==0, lblKO);
			iRet = GoalPrnLine(xDocument, p++, xMSGTest.message, &xPrnLine);
			CHECK(iRet>=0, lblKO);
		}
		else
		{                                                // Font GOAL_CYRGRE_NO missing from System
			iRet = GoalPrnLine(xDocument, p++, "Russian font missing\n\n", &xPrinter);
			CHECK(iRet>=0, lblKO);
		}
	}
	else
	{                                                    // Russian message not supported
		iRet = GoalPrnLine(xDocument, p++, "Russian is not supported\n\n", &xPrinter);
		CHECK(iRet>=0, lblKO);
	}

	iRet = GoalPrnLine(xDocument, p++, "\n\n\n", &xPrinter);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                   // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);     // Wait for key pressed/touched (shortcut)

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                   // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblCyrgreMissing:                                        // File unloaded
	GL_Dialog_Message(xGoal, NULL, "Font GOAL_CYRGRE_NO\nMissing from System", GL_ICON_WARNING, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblOrientaMissing:                                       // File unloaded
	GL_Dialog_Message(xGoal, NULL, "Font GOAL_ORIENTA_NO\nMissing from System", GL_ICON_WARNING, GL_BUTTON_VALID, 5*1000);
lblEnd:	
	if (xScreen)
		GoalDestroyScreen(&xScreen);                     // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);                 // Destroy document
}




