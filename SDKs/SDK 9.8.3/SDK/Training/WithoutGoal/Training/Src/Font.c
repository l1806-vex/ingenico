//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  FONT.C                            (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  ISO 8859 fonts coding and Unicode fonts coding.
//                                                                            
//  List of routines in file :
//      Candara : Demo User font ISO 8859-1 character set.
//      German : Demo ISO 8859-1 character set.
//      Polish : Demo ISO 8859-2 character set.
//      Turkish : Demo ISO 8859-3 character set. 
//      Russian : Demo ISO 8859-5 character set.  
//      Arabic : Demo ISO 8859-6 character set.
//      Greek : Demo ISO 8859-7 character set.
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

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern FILE *pxKbd;      // Peripheral file Keyboard

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
    /* */

//****************************************************************************
//                          void Candara (void)
//  This function shows the display in Candara (Iso1) font mode.
//       DrawExtendedString() : draw an ASCII formatted text with font and type
//       _clrscr() : clear the whole graphic context
//       PaintGraphics() : display the graphic context 
//  This function also prints in Candara (Iso1) font mode.
//       pprintf8859() : print an ASCII formatted text with font and type
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Candara(void)
{
	// Local variables
    // ***************
	char *pcDefFont, *pcCandara;
    int iX, iY;
    int iRet;

	// Candara display in progress
	// ***************************
	pcDefFont = GetCurrentFont();                                                         // Save access to default font

	pcCandara = LoadFont("/SYSTEM/CANDARA.xxx");	                                      // Load font CANDARA in RAM memory (extension not checked)
    CHECK(pcCandara!=NULL, lblKO);
	DefCurrentFont(pcCandara);                                                            // Register the font CANDARA used by the application
	_clrscr();

	// Medium
	// ======
	iY=0; iX=0;                                     // Draw with font=CandaraNo10 (Normal 10pt size) and type=NONE REVERSE
	DrawExtendedString8859(iX, iY, (byte*)"MEDIUM", _OFF_, "CandaraNo10", _PROP_WIDTH_);
    ttestall(0, 1*100);                             // Delay 1s

	iX=89;                                          // Draw with font=CandaraNo10 (Normal 10pt size) and type=REVERSE
    DrawExtendedString8859(iX, iY, (byte*)"  MEDIUM  ", _ON_, "CandaraNo10", _PROP_WIDTH_);
    ttestall(0, 1*100);                             // Delay 1s
	_clrscr();

	// Large
	// =====
	iY=2; iX=0;                                     // Draw with font=CandaraNo16 (Normal 16pt size) and type=NONE REVERSE
	DrawExtendedString8859(iX, iY, (byte*)"LARGE", _OFF_, "CandaraNo16", _PROP_WIDTH_);
	ttestall(0, 1*100);                             // Delay 1s

	iX=76;                                          // Draw with font=CandaraNo16 (Normal 16pt size) and type=REVERSE
	DrawExtendedString8859(iX, iY, (byte*)"  LARGE  ", _ON_, "CandaraNo16", _PROP_WIDTH_);
    ttestall(0, 1*100);                             // Delay 1s
	_clrscr();

	// XLarge
	// ======
	iY=4; iX=0;                                     // Draw with font=CandaraNo20 (Normal 20pt size) and type=NONE REVERSE
	DrawExtendedString8859(iX, iY, (byte*)"XLARGE", _OFF_, "CandaraNo20", _PROP_WIDTH_);
    ttestall(0, 1*100);                             // Delay 1s

	iY=23; iX=55;                                   // Draw with font=CandaraNo20 (Normal 20pt size) and type=REVERSE
	DrawExtendedString8859(iX, iY, (byte*)"  XLARGE  ", _ON_, "CandaraNo20", _PROP_WIDTH_);
    ttestall(0, 1*100);                             // Delay 1s
	_clrscr();

	// XXLarge
	// =======
	iY=6; iX=0;                                     // Draw with font=CandaraNo26 (Normal 26pt size) and type=NONE REVERSE
	DrawExtendedString8859(iX, iY, (byte*)"XXLARGE", _OFF_, "CandaraNo26", _PROP_WIDTH_);
    ttestall(0, 1*100);                             // Delay 1s

	iY=30; iX=21;                                   // Draw with font=CandaraNo26 (Normal 26pt size)and type=REVERSE
	DrawExtendedString8859(iX, iY, (byte*)"  XXLARGE  ", _ON_, "CandaraNo26", _PROP_WIDTH_);
    ttestall(0, 1*100);                             // Delay 1s
	_clrscr();

	// Normal + Bold
	// =============
	iY=5; iX=30;                                    // Draw with font=CandaraNo20 (Normal 20pt size) and type=NONE REVERSE
	DrawExtendedString8859(iX, iY, (byte*)"NORMAL", _OFF_, "CandaraNo20", _PROP_WIDTH_);

	iY=35; iX=40;                                   // Draw with font=CandaraBo20 (Bold 20pt size) and type=REVERSE
	DrawExtendedString8859(iX, iY, (byte*)"BOLD", _OFF_, "CandaraBo20", _PROP_WIDTH_);
    ttestall(0, 2*100);                             // Delay 1s
	_clrscr();

	// Italic + Bold Italic
	// ====================
	iY=5; iX=37;                                    // Draw with font=CandaraIt20 (Italic 20pt size) and type=NONE REVERSE
	DrawExtendedString8859(iX, iY, (byte*)"ITALIC", _OFF_, "CandaraIt20", _PROP_WIDTH_);

	iY=35; iX=12;                                   // Draw with font=CandaraBI20 (Bold Italic 20pt size) and type=REVERSE
	DrawExtendedString8859(iX, iY, (byte*)"BOLD ITALIC", _OFF_, "CandaraBI20", _PROP_WIDTH_);
    ttestall(0, 2*100);                            // Delay 1s

    // Candara printing in progress
    // ****************************
	if (IsPrinter() == 1)
	{
		pprintf("\x1b""E""        Candara Demo\n\n" "\x1b""F");                       // Print demo in progress
		iRet = pprintf8859((byte*)"XXsmall\n", _OFF_,   "CandaraNo10", _PROP_WIDTH_); // Print with font=CandaraNo10 and type=NONE REVERSE
		iRet = pprintf8859((byte*)"Xsmall\n",  _OFF_,   "CandaraNo16", _PROP_WIDTH_); // Print with font=CandaraNo16 and type=NONE REVERSE
		iRet = pprintf8859((byte*)"Small\n",   _OFF_,   "CandaraNo20", _PROP_WIDTH_); // Print with font=CandaraNo20 and type=NONE REVERSE
		iRet = pprintf8859((byte*)"Medium\n",  _OFF_,   "CandaraNo26", _PROP_WIDTH_); // Print with font=CandaraNo26 and type=NONE REVERSE
		iRet = pprintf8859((byte*)"Large\n",   _OFF_,   "CandaraNo33", _PROP_WIDTH_); // Print with font=CandaraNo33 and type=NONE REVERSE
		iRet = pprintf8859((byte*)"Xlarge\n",  _OFF_,   "CandaraNo42", _PROP_WIDTH_); // Print with font=CandaraNo42 and type=NONE REVERSE
		iRet = pprintf8859((byte*)"XXlarge\n", _OFF_,   "CandaraNo53", _PROP_WIDTH_); // Print with font=CandaraNo53 and type=NONE REVERSE
		iRet = pprintf8859((byte*)" XXlarge \n", _ON_,  "CandaraNo53", _PROP_WIDTH_); // Print with font=CandaraNo53 and type=REVERSE
		pprintf("\n\n\n\n\n");

		ttestall(PRINTER, 1*100);                    // Wait until everything printed
	}

    goto lblEnd;

	// Errors treatment
    // ****************
lblKO:
	_clrscr();                                       // Clear screen
    DisplayMedium(0, 0, "FONT NOT FOUND:");          // Oops! font CANDARA not loaded
    DisplayMedium(1, 0, "/SYSTEM/CANDARA.");
    DisplayMedium(2, 0, "SGN");
    ttestall(0, 5*100);                              // Delay 5s
lblEnd:
	if(pcCandara)
	{
		UnloadFont(pcCandara);                       // Unload font CAND from RAM memory
		DefCurrentFont(pcDefFont);                   // Restore default font
	}
}

//****************************************************************************
//                          void German(void)                            
//  This function uses the ISO 8859-1 character set.
//  It represents most Western European languages including:
//  Albanian, Catalan, Danish, Dutch, English, French, Faroese, Finnish,
//  Galician, German, Irish, Icelandic, Italian, Norwegian, Portuguese,
//  Spanish and Swedish.
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void German(void)
{
	// Local variables 
    // ***************
	char *pcDefFont, *pcGerman;

	                           // *********************
	                           //      ISO8859-1      *
	                           // *********************
	pcDefFont = GetCurrentFont();                                      // Save access to default font

	pcGerman = LoadFont("/SYSTEM/ISO1.SGN");                           // Load font ISO1 in RAM memory
    CHECK(pcGerman!=NULL, lblKO);
    DefCurrentFont(pcGerman);                                          // Register the font ISO1
    _clrscr();

	// Display the demo in MEDIUM mode
	// *******************************
	// Display German welcome ISO8859 coded
	// ====================================
	DrawExtendedString8859(0, 0, (byte*)"\x4D\x69\x74\x20\x66\x72\x65\x75\x6E\x64\x6C\x69\x63\x68\x65\x6E\x20\n\x67\x72\xFC\xDF\x65\x6E", _OFF_, _dMEDIUM_, _FIXED_WIDTH_);
	// Display German welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
	// ======================================================================================
	DrawExtendedStringUnicode(0, 21, (byte*)"\x00\x4D\x00\x69\x00\x74\x00\x20\x00\x66\x00\x72\x00\x65\x00\x75\x00\x6E\x00\x64\x00\x6C\x00\x69\x00\x63\x00\x68\x00\x65\x00\x6E\x00\n\x00\x67\x00\x72\x00\xFC\x00\xDF\x00\x65\x00\x6E\x00", _OFF_, _dMEDIUM_, _FIXED_WIDTH_);

	// Print the demo in BOLD mode
	// ***************************
	if (IsPrinter() == 1)
	{
		pprintf8859((byte*)"ISO 8859-1 DEMO\nGerman message\n\n", _ON_, _pBOLD_, _PROP_WIDTH_);
		// Print German welcome ISO8859 coded
		// ==================================
		pprintf8859((byte*)"\x4D\x69\x74\x20\x66\x72\x65\x75\x6E\x64\x6C\x69\x63\x68\x65\x6E\x20\x67\x72\xFC\xDF\x65\x6E\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
		// Print German welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
		// ====================================================================================
		pprintfUnicode((byte*)"\x00\x4D\x00\x69\x00\x74\x00\x20\x00\x66\x00\x72\x00\x65\x00\x75\x00\x6E\x00\x64\x00\x6C\x00\x69\x00\x63\x00\x68\x00\x65\x00\x6E\x00\x20\x00\x67\x00\x72\x00\xFC\x00\xDF\x00\x65\x00\x6E\x00\n\x00\n\x00", _OFF_, _pBOLD_, _PROP_WIDTH_);

		// Print all the characters of the ISO1.SGN file in BOLD mode
		// ==========================================================
		pprintf8859((byte*)"        FONT DUMP\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
		PrintPolice(_pBOLD_, _PROP_WIDTH_);
		pprintf8859((byte*)"\n\n\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
	}

	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                                     // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                        // Wait for a key pressed or a timeout
	reset_buf(pxKbd, _receive_id);                                     // Reset keyboard FIFO to clear key pressed

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO :
	_clrscr();                                                         // Clear screen
	DisplayMedium(0, 0, "FONT NOT FOUND:");                            // Oops! font German not loaded
	DisplayMedium(1, 0, "/SYSTEM/ISO1.SGN");
    ttestall(0, 5*100);                                                // Delay 5s
lblEnd:
	if(pcGerman)
	{
		UnloadFont(pcGerman);                                          // Unload font ISO1 from RAM memory
		DefCurrentFont(pcDefFont);                                     // Restore default font
	}
	return;
}


//****************************************************************************
//                          void Polish(void)                            
//  This function uses the ISO 8859-2 character set.
//  It represents the Slavic languages of Central Europe which use the Latin
//  alphabet. It supports te following languages : Czech, Croat, German, 
//  Hungarian, Polish, Romanian, Slovak and Slovenian.      
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Polish(void)
{
	// Local variables 
    // ***************
	char *pcDefFont, *pcPolish;
	
		                       // *********************
	                           //      ISO8859-2      *
	                           // *********************
	pcDefFont = GetCurrentFont();                                      // Save access to default font

	pcPolish = LoadFont("/SYSTEM/ISO2.SGN");                           // Load font ISO2 in RAM memory
    CHECK(pcPolish!=NULL, lblKO);
	DefCurrentFont(pcPolish);                                          // Register the font ISO2
	_clrscr();

	// Display the demo in MEDIUM mode
	// *******************************
	// Display Polish welcome ISO8859 coded
	// ====================================
	DrawExtendedString8859(0, 0, (byte*)"\x50\x6F\xBF\xB1\x64\x61\x6E\x79", _OFF_, _dMEDIUM_, _FIXED_WIDTH_);
	// Display Polish welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
	// ======================================================================================
	DrawExtendedStringUnicode(0, 10, (byte*)"\x00\x50\x00\x6F\x01\x7C\x01\x05\x00\x64\x00\x61\x00\x6E\x00\x79\x00", _OFF_, _dMEDIUM_, _FIXED_WIDTH_);

	// Print the demo in BOLD mode
	// ***************************
	if (IsPrinter() == 1)
	{
		pprintf8859((byte*)"ISO 8859-2 DEMO\nPolish message\n\n", _ON_, _pBOLD_, _PROP_WIDTH_);
		// Print Polish welcome ISO8859 coded
		// ==================================
		pprintf8859((byte*)"\x50\x6F\xBF\xB1\x64\x61\x6E\x79\n", _OFF_, _pBOLD_, _PROP_WIDTH_);

		// Print Polish welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
		// ====================================================================================
		pprintfUnicode((byte*)"\x00\x50\x00\x6F\x01\x7C\x01\x05\x00\x64\x00\x61\x00\x6E\x00\x79\x00\n\x00\n\x00", _OFF_, _pBOLD_, _PROP_WIDTH_);

		// Print all the characters of the ISO2.SGN file in BOLD mode
		// ==========================================================
		pprintf8859((byte*)"        FONT DUMP\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
		PrintPolice(_pBOLD_, _PROP_WIDTH_);
		pprintf8859((byte*)"\n\n\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
	}

	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                       // Wait for a key pressed or a timeout
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO to clear key pressed

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                                        // Clear screen
	DisplayMedium(0, 0, "FONT NOT FOUND:");                           // Oops! font Polish not loaded
	DisplayMedium(1, 0, "/SYSTEM/ISO2.SGN");
    ttestall(0, 5*100);                                               // Delay 5s
lblEnd:
	if(pcPolish)
	{
		UnloadFont(pcPolish);                                         // Unload font ISO2 from RAM memory
		DefCurrentFont(pcDefFont);                                    // Restore default font
	}
}

//****************************************************************************
//                          void Turkish(void)                            
//  This function uses the ISO 8859-3 character set. It represents the following 
//  languages:
//  Esperanto, Galician, Maltese and Turkish.      
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Turkish(void)
{
	// Local variables 
    // ***************
	char *pcDefFont, *pcTurkish;
	
		                       // *********************
	                           //      ISO8859-3      *
	                           // *********************
	pcDefFont = GetCurrentFont();                                      // Save access to default font

	pcTurkish = LoadFont("/SYSTEM/ISO3.SGN");                          // Load font ISO3 in RAM memory
    CHECK(pcTurkish!=NULL, lblKO);
	DefCurrentFont(pcTurkish);                                         // Register the font ISO3
	_clrscr();

	// Display the demo in MEDIUM mode
	// *******************************
	// Display Turkish welcome ISO8859 coded
	// =====================================
	DrawExtendedString8859(0, 0, (byte*)"\x47\xFC\x6E\x61\x79\x64\x69\x6E", _OFF_, _dMEDIUM_, _FIXED_WIDTH_);
	// Display Turkish welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
	// =======================================================================================
	DrawExtendedStringUnicode(0, 10, (byte*)"\x00\x47\x00\xFC\x00\x6E\x00\x61\x00\x79\x00\x64\x00\x69\x00\x6E\x00", _OFF_, _dMEDIUM_, _FIXED_WIDTH_);

	// Print the demo in BOLD mode
	// ***************************
	if (IsPrinter() == 1)
	{
		pprintf8859((byte*)"ISO 8859-3 DEMO\nTurkish message\n\n", _ON_, _pBOLD_, _PROP_WIDTH_);
		// Print Turkish welcome ISO8859 coded
		// ===================================
		pprintf8859((byte*)"\x47\xFC\x6E\x61\x79\x64\x69\x6E\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
		// Print Turkish welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
		// =====================================================================================
		pprintfUnicode((byte*)"\x00\x47\x00\xFC\x00\x6E\x00\x61\x00\x79\x00\x64\x00\x69\x00\x6E\x00\n\x00\n\x00", _OFF_, _pBOLD_, _PROP_WIDTH_);

		// Print all the characters of the ISO2.SGN file in BOLD mode
		// ==========================================================
		pprintf8859((byte*)"        FONT DUMP\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
		PrintPolice(_pBOLD_, _PROP_WIDTH_);
		pprintf8859((byte*)"\n\n\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
	}

	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                       // Wait for a key pressed or a timeout
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO to clear key pressed

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                                        // Clear screen
	DisplayMedium(0, 0, "FONT NOT FOUND:");                           // Oops! font Turkish not loaded
	DisplayMedium(1, 0, "/SYSTEM/ISO3.SGN");
    ttestall(0, 5*100);                                               // Delay 5s
lblEnd:
	if(pcTurkish)
	{
		UnloadFont(pcTurkish);                                        // Unload font ISO3 from RAM memory
		DefCurrentFont(pcDefFont);                                    // Restore default font
	}
}

//****************************************************************************
//                          void Russian(void)                            
//  This function uses the ISO 8859-5 character set. It represents various 
//  forms of the Cyrillic alphabet. It supports Bulgarian, Byelorussian,
//  Macedonian, Serbian and Ukrainian.      
//  This function has no parameters.    
//  This function has no return value.                                      
//****************************************************************************

void Russian(void)
{
	// Local variables 
    // ***************
	char *pcDefFont, *pcRussian;

		                       // *********************
	                           //      ISO8859-5      *
	                           // *********************
	pcDefFont = GetCurrentFont();                                      // Save access to default font

	pcRussian = LoadFont("/SYSTEM/ISO5.SGN");                          // Load font ISO5 in RAM memory
    CHECK(pcRussian!=NULL, lblKO);
	DefCurrentFont(pcRussian);                                         // Register the font ISO5
	_clrscr();

	// Display the demo in MEDIUM mode
	// *******************************
	// Display Russian welcome ISO8859 coded
	// =====================================
	DrawExtendedString8859(0, 0, (byte*)"\xB4\xBE\xB1\xC0\xBE\x20\xBF\xBE\xB6\xB0\xBB\xBE\xB2\xB0\xC2\xCC", _OFF_, _dMEDIUM_, _FIXED_WIDTH_);
	// Display Russian welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
	// =======================================================================================
	DrawExtendedStringUnicode(0, 10, (byte*)"\x04\x14\x04\x1E\x04\x11\x04\x20\x04\x1E\x00\x20\x04\x1F\x04\x1E\x04\x16\x04\x10\x04\x1B\x04\x1E\x04\x12\x04\x10\x04\x22\x04\x2C\x00", _OFF_, _dMEDIUM_, _FIXED_WIDTH_);

	// Print the demo in BOLD mode
	// ***************************
	if (IsPrinter() == 1)
	{
		pprintf8859((byte*)"ISO 8859-5 DEMO\nRussian message\n\n", _ON_, _pBOLD_, _PROP_WIDTH_);
		// Print Russian welcome ISO8859 coded
		// ===================================
		pprintf8859((byte*)"\xB4\xBE\xB1\xC0\xBE\x20\xBF\xBE\xB6\xB0\xBB\xBE\xB2\xB0\xC2\xCC\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
		// Print Russian welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
		// =====================================================================================
		pprintfUnicode((byte*)"\x04\x14\x04\x1E\x04\x11\x04\x20\x04\x1E\x00\x20\x04\x1F\x04\x1E\x04\x16\x04\x10\x04\x1B\x04\x1E\x04\x12\x04\x10\x04\x22\x04\x2C\x00\n\x00\n\x00", _OFF_, _pBOLD_, _PROP_WIDTH_);

		// Print all the characters of the ISO5.SGN file in BOLD mode
		// ==========================================================
		pprintf8859((byte*)"        FONT DUMP\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
		PrintPolice(_pBOLD_, _PROP_WIDTH_);
		pprintf8859((byte*)"\n\n\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
	}

	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                       // Wait for a key pressed or a timeout
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO to clear key pressed

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                                        // Clear screen
	DisplayMedium(0, 0, "FONT NOT FOUND:");                           // Oops! font Russian not loaded
	DisplayMedium(1, 0, "/SYSTEM/ISO5.SGN");
    ttestall(0, 5*100);                                               // Delay 5s
lblEnd:
	if(pcRussian)
	{
		UnloadFont(pcRussian);                                        // Unload font ISO5 from RAM memory
		DefCurrentFont(pcDefFont);                                    // Restore default font
	}
}

//****************************************************************************
//                          void Arabic(void)                            
//  This function uses the ISO 8859-6 character set. It supports the Arabic letter.
//  Each Arabic letter can be represented in 4 positional forms: initial, median,
//  fianal and isolated. Arabic documents coded in ISO 8859-6 are only viewable
//  after a type of processing called contextual analysis, whereby the character's
// positions are analyzed so that they can be presented in the proper form.      
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void Arabic(void)
{
	// Local variables 
    // ***************
	char *pcDefFont, *pcArabic;
	
		                       // *********************
	                           //      ISO8859-6      *
	                           // *********************
	pcDefFont = GetCurrentFont();                                      // Save access to default font

	pcArabic = LoadFont("/SYSTEM/ISO6.SGN");                           // Load the SGN file in RAM memory
    CHECK(pcArabic!=NULL, lblKO);
	DefCurrentFont(pcArabic);                                          // Register the font
	_clrscr();

	// Display the demo in MEDIUM mode
	// *******************************
	// Display Arabic welcome ISO8859 coded
	// ====================================
	DrawExtendedString8859(0, 0, (byte*)"\xC7\xE4\xD3\xE4\xC7\xE5\x20\xD9\xE4\xEA\xE3\xE5", _OFF_, _dMEDIUM_, _PROP_WIDTH_);
	// Display Arabic welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
	// ======================================================================================
	DrawExtendedStringUnicode(0, 14, (byte*)"\xFE\x8D\xFE\xDF\xFE\xB4\xFE\xFC\xFE\xE1\x00\x20\xFE\xCB\xFE\xE0\xFE\xF4\xFE\xDC\xFE\xE2\x00", _OFF_, _dMEDIUM_, _PROP_WIDTH_);

	// Print the demo in BOLD mode
	// ***************************
	if (IsPrinter() == 1)
	{
		pprintf8859((byte*)"ISO 8859-6 DEMO\nArabic message\n\n", _ON_, _pBOLD_, _PROP_WIDTH_);
		// Print Arabic welcome ISO8859 coded
		// ==================================
		pprintf8859((byte*)"\xC7\xE4\xD3\xE4\xC7\xE5\x20\xD9\xE4\xEA\xE3\xE5\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
		// Print Arabic welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
		// ====================================================================================
		pprintfUnicode((byte*)"\xFE\x8D\xFE\xDF\xFE\xB4\xFE\xFC\xFE\xE1\x00\x20\xFE\xCB\xFE\xE0\xFE\xF4\xFE\xDC\xFE\xE2\x00\n\x00\n\x00", _OFF_, _pBOLD_, _PROP_WIDTH_);

		// Print all the characters of the ISO6.SGN file in BOLD mode
		// ==========================================================
		pprintf8859((byte*)"        FONT DUMP\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
		PrintPolice(_pBOLD_, _PROP_WIDTH_);
		pprintf8859((byte*)"\n\n\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
	}

	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                       // Wait for a key pressed or a timeout
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO to clear key pressed

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                                        // Clear screen
	DisplayMedium(0, 0, "FONT NOT FOUND:");                           // Oops! font Arabic not loaded
	DisplayMedium(1, 0, "/SYSTEM/ISO6.SGN");
    ttestall(0, 5*100);                                               // Delay 5s
lblEnd:
	if(pcArabic)
	{
		UnloadFont(pcArabic);                                         // Unload font from RAM memory
		DefCurrentFont(pcDefFont);                                    // Restore default font
	}
}

//****************************************************************************
//                          void Greek(void)                            
//  This function uses the ISO 8859-7 character set. It support the modern Greek.
//  There are no emphases, or subscripted iotas, or any of the accents of ancient
//  Greek.     
//  This function has no parameters.
//  This function has no return value.                                      
//****************************************************************************

void Greek(void)
{
	// Local variables 
    // ***************
	char *pcDefFont, *pcGreek;
	
	                           // *********************
	                           //      ISO8859-7      *
	                           // *********************
	pcDefFont = GetCurrentFont();                                     // Save access to default font

	pcGreek = LoadFont("/SYSTEM/ISO7.SGN");                           // Load font ISO7 in RAM memory
    CHECK(pcGreek!=NULL, lblKO);
	DefCurrentFont(pcGreek);                                          // Register the font ISO7
	_clrscr();

	// Display the demo in MEDIUM mode
	// *******************************
	// Display Greek welcome ISO8859 coded
	// ===================================
	DrawExtendedString8859(0, 0, (byte*)"\xEA\xE1\xEB\xE7\xEC\xDD\xF1\xE1", _OFF_, _dMEDIUM_, _FIXED_WIDTH_);
	// Display Greek welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
	// =====================================================================================
	DrawExtendedStringUnicode(0, 14, (byte*)"\x03\xBA\x03\xB1\x03\xBB\x03\xB7\x03\xBC\x03\xAD\x03\xC1\x03\xB1\x00", _OFF_, _dMEDIUM_, _FIXED_WIDTH_);

	// Print the demo in BOLD mode
	// ***************************
	if (IsPrinter() == 1)
	{
		pprintf8859((byte*)"ISO 8859-7 DEMO\nGreek message\n\n", _ON_, _pBOLD_, _PROP_WIDTH_);
		// Print Greek welcome ISO8859 coded
		// =================================
		pprintf8859((byte*)"\xEA\xE1\xEB\xE7\xEC\xDD\xF1\xE1\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
		// Print Greek welcome UNICODE coded (String in big endian MUST be finished by a 0x00)
		// ===================================================================================
		pprintfUnicode((byte*)"\x03\xBA\x03\xB1\x03\xBB\x03\xB7\x03\xBC\x03\xAD\x03\xC1\x03\xB1\x00\n\x00\n\x00", _OFF_, _pBOLD_, _PROP_WIDTH_);

		// Print all the characters of the ISO7.SGN file in BOLD mode
		// ==========================================================
		pprintf8859((byte*)"        FONT DUMP\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
		PrintPolice(_pBOLD_, _PROP_WIDTH_);
		pprintf8859((byte*)"\n\n\n\n", _OFF_, _pBOLD_, _PROP_WIDTH_);
	}

	DisplaySmall(7, 6, "Press a key");
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                       // Wait for a key pressed or a timeout
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO to clear key pressed

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:
	_clrscr();                                                        // Clear screen
	DisplayMedium(0, 0, "FONT NOT FOUND:");                           // Oops! font Greek not loaded
	DisplayMedium(1, 0, "/SYSTEM/ISO7.SGN");
    ttestall(0, 5*100);                                               // Delay 5s
lblEnd:
	if(pcGreek)
	{
		UnloadFont(pcGreek);                                          // Unload font ISO7 from RAM memory
		DefCurrentFont(pcDefFont);                                    // Restore default font
	}
}





