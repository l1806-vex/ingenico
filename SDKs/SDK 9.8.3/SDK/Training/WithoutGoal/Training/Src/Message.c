//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  MESSAGE.C                         (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Allow to customize application's messages and languages.
//                                                                            
//  List of routines in file :
//      DefaultSettings : Load the SAMPLEMSG.SGN messages file in the memory.
//      GetMsg : Display and print messages in the current language. 
//      SelectLanguage : select the current language. 
//      Testing : Language testing.
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
#include "MessagesDefinitions.h"	// Messages' name definitions

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern const byte English[];                   // Default messages in English
extern FILE *pxKbd;                            // Peripheral file Keyboard

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
static int iDefItem;                            // Default item selected

//****************************************************************************
//                          void DefaultSettings (void)                            
//  This function loads the SAMPLEMSG.SGN messages file in the memory to
//  use the new language selected. 
//  if this file cannot be loaded, english default messages are used.
//  The file SAMPLEMSG.SGN allows to customize application's messages and 
//  languages.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void DefaultSettings (void)
{
	// Local variables 
    // ***************
	char *pcNewMsg; 	                                     // Address of the loaded message file

	// Loading new messages
	// ********************
	_clrscr();                                               // Clear screen
	iDefItem=0;                                              // Language selection to English by default

	pcNewMsg = LoadMSG("/SYSTEM/SAMPLEMSG.SGN");             // Load the SGN file in memory	 
	if (pcNewMsg == NULL )
	{
	    DisplayMedium(0, 0, "FILE NOT FOUND:");
	    DisplayMedium(1, 0, "/SYSTEM/SAMPLEMS");
	    DisplayMedium(2, 0, "G.SGN");
		ttestall(0,300);
		DefCurrentMSG((char *)English);                      // Local messages are used
	}
	else
		DefCurrentMSG(pcNewMsg);                             // New messages are used 

	DefDefaultMSG((char *)English);                          // Messages used by default (if not present in current MSG file)
	DefCurrentLang(EN);                                      // Define current and default languages (English)
	DefDefaultLang(EN);
}

//****************************************************************************
//                          void GetMsg (void)                            
//  This function displays and prints messages in the application's current 
//  language.  .
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void GetMsg(void)
{
	// Local variables 
    // ***************
	int iRet;

	// Display hello in the language selected 
	// **************************************
	_clrscr();                                               
	iRet = DisplayMSG(40, 0, DISPLAY_LANGUAGE, _ON_, _dLARGE_, _PROP_WIDTH_);
	CHECK(iRet==0, lblKO);	
	iRet = DisplayMSG(0, 21, DISPLAY_HELLO, _OFF_, _dMEDIUM_, _FIXED_WIDTH_);
    CHECK(iRet==0, lblKO);

	// Print hello in the language selected
	// ************************************
    iRet = pprintf("\x1b""E"); CHECK(iRet>=0, lblKO);        // Force Bold if Local Font (Manager)
    iRet = PrintMSG(PRINTER_LANGUAGE, _OFF_, _pBOLD_, _FIXED_WIDTH_);
    CHECK(iRet==0, lblKO);
    iRet = pprintf("\x1b""F"); CHECK(iRet>=0, lblKO);        // Return to normal font
    iRet = PrintMSG(PRINTER_HELLO, _OFF_, _pNORMAL_, _FIXED_WIDTH_);
    CHECK(iRet==0, lblKO);
    iRet = pprintf("\n\n\n\n\n");
    CHECK(iRet>=0, lblKO);

	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                           // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                              // Wait for a key pressed or a timeout
	reset_buf(pxKbd, _receive_id);                           // Reset keyboard FIFO to clear key pressed

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO :
	_clrscr();                                               // Clear screen
    DisplayMedium(0, 0, "Processing Error");                 // Oops Error
    DisplayMedium(1, 0, "Font not found");
    ttestall(0,5*100);                                       // Delay 5s 
lblEnd:	
    return;
}

//****************************************************************************
//                          void LanguageSelect (void)                            
//  This function shows a menu to select the application language.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void SelectLang (void)
{
	// Local variables 
    // ***************
	char tcLang[2*MAX_LANG], ttcLang[MAX_LANG][3], *tpcLang[MAX_LANG+1];
	int iLoadLang;		                                        // Number of languages in the loaded MSG file
	int iNbrLang=0;                                             // Number of languages in the terminal 
	int i; 
	
	// Language selection
	// ******************

	// Get the languages supported by the application (local:English or loaded MSG file:Russian...)
    // ============================================================================================
    strcpy(ttcLang[iNbrLang++], EN);                            // English messages are always defined (local messages)
    
    iLoadLang = GetSupportedLanguages(tcLang, GetCurrentMSG()); // Number of loaded language
	for(i=0; i<iLoadLang; i++)
	{
		if ((memcmp(&tcLang[i*2], EN, 2))!=0)                   // EN already exist (local replaced by loaded messages)
		{
			memset (ttcLang[iNbrLang], 0, sizeof(ttcLang[iNbrLang]));
			memcpy(ttcLang[iNbrLang++], &tcLang[i*2], 2);       // Copy the ISO639-1 language code
		}
		tpcLang[i] = ttcLang[i];                                // Initialize table of pointers
	}
	tpcLang[i] = NULL;                                          // End of table of pointers
	
	// Select the language to use
	// ==========================
	iDefItem = ShowMenu("LANGUAGE", 2, iDefItem, iNbrLang, (const char**) tpcLang);
	if (iDefItem >= 0)
		DefCurrentLang(ttcLang[iDefItem]);                      // Set the language selected        	
}

//****************************************************************************
//                          void Testing (void)                            
//  This function returns informations regarding application language.
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Testing (void)
{
	// Local variables 
    // ***************
	MSGinfos xMSGtest;
	byte ucLine, ucColumn;
	int iRet;

    // Displaying in progress
	// **********************
	_clrscr();                                                        // Clear screen
	// Display hard coded message
	// ==========================
	InitMSGinfos(&xMSGtest);                                          // Print hard coded MSG
	xMSGtest.message = "Message current font:";
    ucLine=0; ucColumn=0;                                             // Display it
	DisplayMSGinfos((ucColumn*5)+2, ucLine*8, &xMSGtest, _OFF_, _dPOLICE4x7_, _FIXED_WIDTH_);
	// Display selected language message
	// ===========================================
	iRet = GetMessageInfos(DISPLAY_HELLO, &xMSGtest);                 // Get selected language MSG (DISPLAY_HELLO)
	CHECK(iRet==0, lblKO);
	ucLine=1; ucColumn=0;                                             // Display it
	DisplayMSGinfos((ucColumn*5)+2, ucLine*8, &xMSGtest, _OFF_, _dSMALL_, _PROP_WIDTH_);
	// Display local language message
	// ==============================
	InitMSGinfos(&xMSGtest);                                          // Print hard coded MSG
	xMSGtest.message = "Message local font:";
    ucLine=3; ucColumn=0;                                             // Display it
	DisplayMSGinfos((ucColumn*5)+2, ucLine*8, &xMSGtest, _OFF_, _dPOLICE4x7_, _FIXED_WIDTH_);
	iRet = GetSpecificMessage((char *)English, (byte*)EN, OBJECT_TYPE_APPLI, ApplicationGetCurrentAppliType(), DISPLAY_HELLO, &xMSGtest);
	CHECK(iRet==0, lblKO);
	ucLine=4; ucColumn=0;                                             // Display it
	DisplayMSGinfos((ucColumn*5)+2, ucLine*8, &xMSGtest, _OFF_, _dSMALL_, _PROP_WIDTH_);
	DisplaySmall(7, 6, "Press a key");

    // Printing in progress
	// ********************
    iRet = pprintf("\x1b""E""       Message Demo\n\n"                 // Print demo in progress
		           "\x1b""F"); CHECK(iRet>=0, lblKO);      
	// Print Manager stuff
    // ===================
	pprintf("Manager language : %s\n\n", GetManagerLanguage());       // Get Manager language
	pprintf("File Type : %X\nApplication Type : %X\n\n",              // Get file type and application type
			OBJECT_TYPE_APPLI, ApplicationGetCurrentAppliType());
	// Print hard coded message
	// ========================
	InitMSGinfos(&xMSGtest);                                          // Print hard coded MSG
	xMSGtest.message = "Message current font:\n";
	PrintMSGInfos(&xMSGtest, _OFF_, _pNORMAL_, _FIXED_WIDTH_);
	// Print selected language message
	// ===============================
	iRet = GetMessageInfos(PRINTER_HELLO, &xMSGtest);                 // Get selected language MSG (PRINTER_HELLO)
	CHECK(iRet==0, lblKO);
	PrintMSGInfos(&xMSGtest, _OFF_, _pNORMAL_, _FIXED_WIDTH_);        // Print it
	// Print Russian language message
	// ==============================
	InitMSGinfos(&xMSGtest);                                          // Print hard coded MSG
	xMSGtest.message = "Russian font exists?:\n";
	PrintMSGInfos(&xMSGtest, _OFF_, _pNORMAL_, _FIXED_WIDTH_);
	if(LanguageExist("RU", GetCurrentMSG()) == 0)                     // Check if Russian language MSG exists
	{
		iRet = GetMessageInfosInLang("RU", PRINTER_HELLO, &xMSGtest); // Get Russian language MSG (PRINTER_HELLO)
	    if (iRet != 0)
	    	InitMSGinfos_message(&xMSGtest, "Russian font not loaded\n");
	}
	else
		InitMSGinfos_message(&xMSGtest, "Russian is not supported\n");
	PrintMSGInfos(&xMSGtest, _OFF_, _pNORMAL_, _FIXED_WIDTH_);        // Print it
	// Print local language message
	// ============================
	InitMSGinfos(&xMSGtest);                                          // Print hard coded MSG
	xMSGtest.message = "Message local font:\n";
	PrintMSGInfos(&xMSGtest, _OFF_, _pNORMAL_, _FIXED_WIDTH_);
	iRet = GetSpecificMessage((char *)English, (byte*)EN, OBJECT_TYPE_APPLI, ApplicationGetCurrentAppliType(), PRINTER_HELLO, &xMSGtest);
	CHECK(iRet==0, lblKO);
	PrintMSGInfos(&xMSGtest, _OFF_, _pNORMAL_, _FIXED_WIDTH_);        // Print local language MSG
	// Print line feed
	// ===============
	iRet = pprintf("\n\n\n\n\n");
	CHECK(iRet>=0, lblKO);

	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                       // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO to clear key pressed

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                                        // Clear screen
    DisplayMedium(0, 0, "Processing Error");                          // Oops Error
    ttestall(0, 5*100);                                               // Delay 5s 
lblEnd:	
	return;
}




