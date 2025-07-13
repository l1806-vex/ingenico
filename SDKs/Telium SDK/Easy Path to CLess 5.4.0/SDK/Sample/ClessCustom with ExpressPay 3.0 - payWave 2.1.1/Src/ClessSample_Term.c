//! \file
//! Module that gives developers an helping interface for menu creation
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define C_FIRSTCOL						0						//!< Definition of the first comlumn.
#define BACKGROUNDPIXELS				1						//!< Number of pixels added on the top and under the message to form the background.


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

// Multilanguage management
const t_lang_code lang_table[C_NBLANGHOLDER]=
{
	{"en"    ,"ENGLISH"    ,0       },
	{"fr"    ,"FRANCAIS"   ,1       },
	{"en"    ,"ENGLISH"    ,0xFF    }    // Not supported : english messages
};

static int FontHeight;										//!< variable for font height.

extern const unsigned char ClessSample_lang[];				// Default messages in LANG

/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


#ifdef _SIMULPC_
// This function is used ONLY IN SIMULATION
// TransfertData copies the local messages from the PC.
// to the terminal (char *LocalMessages variable) to avoid MMU errors.
extern char * TransfertData(char * msg);
#endif



/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//===========================================================================
//! \brief This function display a text line in graphic mode. 
//! \param[in] nline : line index.
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment : center, left, rigth, ....
//! \param[in] bmode : TRUE to erase before display something, else nothing
//! \param[in] bLongLine : TRUE for long line to display (little police will be used), FALSE else.
//! \param[in] nFontSize : Possibility to force the font size.
//===========================================================================
void ClessSample_Term_DisplayGraphicLine(int nline, MSGinfos * ptrMSG, int nAlignment, unsigned char bmode, unsigned char bLongLine, const int nFontSize)
{
	int lg, x, y;
	int nScreenHeight, nScreenWidth;
	char * police;
	int nType; // _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_
	int nNbLineInScreen = 5;

	if (nFontSize == HELPERS_FONT_SIZE_LARGE)
	{
		police = _dLARGE_;
	}
	else if (nFontSize == HELPERS_FONT_SIZE_MEDIUM)
	{
		police = _dMEDIUM_;
	}
	else if (nFontSize == HELPERS_FONT_SIZE_SMALL)
	{
		police = _dSMALL_;
	}
	else
	{
		if (bLongLine)
			police = _dMEDIUM_;
		else
			police = _dLARGE_;
	}
	
	nType = _PROP_WIDTH_;

	// In order to get back the width/heigth of the screen
	GetScreenSize(&nScreenHeight, &nScreenWidth);
	
	if(ptrMSG->file ==NULL)
		ptrMSG->file = GetDefaultFONaddress();  // Use the default manager font

	DefCurrentFont(ptrMSG->file);

	FontHeight = GetExtendedPoliceSize(police); // Get the height of the police 
	if (FontHeight < 0)
		GTL_Traces_TraceDebug("Police not found : %s", police);
	else
		nNbLineInScreen = nScreenHeight / FontHeight;
	
	// Get the length of the input text
	if(ptrMSG->coding == _UNICODE_)
		lg = SizeOfUnicodeString((unsigned char *)(ptrMSG->message), police, nType);
	else
		lg = SizeOfISO8859String((unsigned char *)(ptrMSG->message), police, nType);

	// Calculate the position of the text to be displayed
	y = FontHeight * nline;
	x = C_FIRSTCOL;
			
	switch (nAlignment)
	{
		case (CLESSSAMPLE_ALIGN_CENTER):
			x = (nScreenWidth - lg) / 2;
			break;
		case (CLESSSAMPLE_ALIGN_LEFT):
			x = C_FIRSTCOL;
			break;
		case (CLESSSAMPLE_ALIGN_RIGHT):
			x = nScreenWidth - lg;
			break;
		default:
			x = C_FIRSTCOL;
			break;
	} // End of switch on xt_justify

	// If the text lenght is superior to column it will be automatically truncated
	if (x < 0)
		x = C_FIRSTCOL;

	if (bmode == YESCLEAR)
	{
		// Clear the screen
		_clrscr();
	}
	else
	{	
		// Clear only the used line
		if(!bLongLine)
			DrawRect(0, y, nScreenWidth, y + FontHeight, 0, _OFF_, _OFF_);
	}

	if (bLongLine)
	{
		int nRectPosition;
		nRectPosition = nScreenHeight - (nNbLineInScreen - nline - 1) * FontHeight;

		DrawRect(0, nRectPosition - 2*BACKGROUNDPIXELS, nScreenWidth, nRectPosition + FontHeight + BACKGROUNDPIXELS, 0, _OFF_, _ON_);
		DisplayMSGinfos(x, nRectPosition - BACKGROUNDPIXELS, ptrMSG, _ON_, police, nType);
	}
	else
	{
		DisplayMSGinfos(x, y, ptrMSG, _OFF_, police, nType);
	}
}


//===========================================================================
//! \brief This function initialise Messages menagement. 
//===========================================================================
void ClessSample_Term_Initialise(void)
{
	static int bInitialised = FALSE;
	char *NewMessages;     // Address of the loaded message file
	const unsigned char* pLocalMessages;

	if (bInitialised)
		return;

	bInitialised = TRUE;

#ifdef _SIMULPC_
	pLocalMessages = TransfertData((char *)ClessSample_lang);
#else
	pLocalMessages = ClessSample_lang;
#endif // _SIMULPC_

	trace(0, strlen("ClessSample_Term_Initialise()\n"), "ClessSample_Term_Initialise()\n");

	// Load the message file in memory
	NewMessages=LoadMSG("/SYSTEM/LANG.SGN");    
	if(NewMessages == NULL )
	{
		GTL_Traces_TraceDebug("ClessSample_Term_Initialise : MSG file not found :\n /SYSTEM/LANG.SGN"); 
		// Local messages are used
		DefCurrentMSG((char *)pLocalMessages); // Higher priority table
	}
	else
	{
		GTL_Traces_TraceDebug("ClessSample_Term_Initialise : MSG file loaded :\n /SYSTEM/LANG.SGN"); 
		// New messages are used
		DefCurrentMSG(NewMessages);     // Higher priority table
	}

	DefDefaultMSG((char *)pLocalMessages); // If msg not found in higher priority table, this one will be used
	// Define current and default languages (English)
	DefCurrentLang("en");
	DefDefaultLang("en");
}


//===========================================================================
//! \brief This function gives message referenced by number in appropriate language. 
//! If the specific message in not found, a default text is pointed.
//! \param[in] num message number.
//! \param[in] language language number (0:English, 1:french ...)
//! \return
//===========================================================================
void ClessSample_Term_Read_Message(int nNum, int nLanguage, MSGinfos * pMsgInfo)
{
	int index;
	char ac_l_iso[] = "xx";		// Unused value
	
	// if language code is not valid: DefDefaultLang("en") = English will be used
	for(index=0; index<C_NBLANGHOLDER; index++)
	{
		if (lang_table[index].table_id == (unsigned char)nLanguage)
		{
			strcpy(ac_l_iso, (char *)(lang_table[index].iso639_code));
			break;
		}
	}

	DefCurrentLang(ac_l_iso);
	
	// Test GetMessageInfos function
	GetMessageInfos(nNum, pMsgInfo);
}

//===========================================================================
//! \brief This function return lang identifier. 
//! \param[in] puc_Lang iso639 text code.
//! \return
//! 	lang code.
//===========================================================================
int ClessSample_Term_GiveLangNumber(unsigned char * puc_Lang)
{
	int nIndex, nResult;

	nResult = -1;  	// Default = Bad result
	
	// Bad input parameter protection
	if (puc_Lang == NULL)
		return (nResult);
	
	// if language code is not valid: DefDefaultLang("en") = English will be used
	for(nIndex=0; nIndex<C_NBLANGHOLDER; nIndex++)
	{
		if (memcmp(lang_table[nIndex].iso639_code, puc_Lang, 2) == 0)
		{
			nResult = lang_table[nIndex].table_id;
			break;
		}
	}

	return (nResult);
}
