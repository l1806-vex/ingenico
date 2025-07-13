/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"

#include "UserInterfaceHelpers.h"

//// Macros & preprocessor definitions //////////////////////////


//// Types //////////////////////////////////////////////////////


//// Global variables ///////////////////////////////////////////


//// Static function definitions ////////////////////////////////

static int HelperDisplayMenuInternal(const char* szTitle, int bRadioButtons, int nDefaultChoice, int nItems, const char* Items[]);


//// Functions //////////////////////////////////////////////////

//===============================================================
// Function name	:	HelperDisplayMenuInternal
// Description		:	Create a menu according options :
//							szTitle : Menu name
//							bRadioButton : is radio buttons or not
//							nDefaultChoice : default choice
//							nItems : number of items in the menu
//							Items : arrays containing all the menu items

static int HelperDisplayMenuInternal(const char* szTitle, int bRadioButtons, int nDefaultChoice, int nItems, const char* Items[])
{
	int nSizeX;
	int nSizeY;
	StructList Menu;
	int i;
	int nResult;
	ENTRY_BUFFER Entry;
	int nBannerHeight;

	nBannerHeight = 0;

	if ((nDefaultChoice < 0) || (nDefaultChoice >= nItems))
		nDefaultChoice = 0;

	GetScreenSize(&nSizeY, &nSizeX);

	memset(&Menu, 0, sizeof(Menu));
	Menu.MyWindow.left = 0;
	Menu.MyWindow.top = nBannerHeight;
	Menu.MyWindow.rigth = nSizeX - 1;
	Menu.MyWindow.bottom = nSizeY - 1;
	if (nSizeY == 128)
		Menu.MyWindow.nblines = 10;
	else Menu.MyWindow.nblines = 4;
	Menu.MyWindow.fontsize = _MEDIUM_;
	Menu.MyWindow.type = _PROPORTIONNEL_;
	Menu.MyWindow.font = 0;
	Menu.MyWindow.correct = _ON_;
	Menu.MyWindow.offset = 1;
	Menu.MyWindow.shortcommand = _ON_;
	if (bRadioButtons)
		Menu.MyWindow.selected = _ON_;
	else Menu.MyWindow.selected = _OFF_;
	Menu.MyWindow.thickness = 2;
	Menu.MyWindow.border = _ON_;
	Menu.MyWindow.popup = _NOPOPUP_;
	Menu.MyWindow.first = nDefaultChoice;
	Menu.MyWindow.current = nDefaultChoice;
	Menu.MyWindow.time_out = 60;
	Menu.MyWindow.title = (unsigned char*)szTitle;

	for(i = 0; i < nItems; i++)
		Menu.tab[i] = (unsigned char*)Items[i];

	G_List_Entry((void*)&Menu);
	ttestall(ENTRY, 0);
	nResult = Get_Entry(&Entry);

	if (nResult == CR_ENTRY_OK)
		nResult = Entry.d_entry[0];
	else if (nResult == CR_ENTRY_NOK)
		nResult = -2;
	else nResult = -1;

	return nResult;
}


//===============================================================
// Function name	:	HelperDisplayMenu
// Description		:	Create a menu

int HelperDisplayMenu(const char* szTitle, int nDefaultChoice, int nItems, const char* Items[])
{
	return HelperDisplayMenuInternal(szTitle, FALSE, nDefaultChoice, nItems, Items);
}


//===============================================================
// Function name	:	HelperDisplayChoices
// Description		:	Create a choice menu (with radio buttons)

int HelperDisplayChoices(const char* szTitle, int nDefaultChoice, int nItems, const char* Items[])
{
	return HelperDisplayMenuInternal(szTitle, TRUE, nDefaultChoice, nItems, Items);
}


//===============================================================
// Function name	:	HelperNumericInput
// Description		:	Graphical interface allowing to input a numerical entry

int HelperNumericInput(const char* szTitle, const char* szLabel, int nMinLength, int nMaxLength, const char* szDefault, char* szInput)
{
	int nSizeX;
	int nSizeY;
	StructList Input;
	int nResult;
	TAB_ENTRY_STRING EntryNumeric;
	ENTRY_BUFFER Entry;

	if (nMaxLength >= 20)
		nMaxLength = 20;
	if (nMinLength > nMaxLength)
		nMinLength = nMaxLength;

	GetScreenSize(&nSizeY, &nSizeX);

	memset(&Input, 0, sizeof(Input));
	Input.MyWindow.left = 0;
	Input.MyWindow.top = 0;
	Input.MyWindow.rigth = nSizeX - 1;
	Input.MyWindow.bottom = nSizeY - 1;
	if (nSizeY == 128)
		Input.MyWindow.nblines = 10;
	else Input.MyWindow.nblines = 5;
	Input.MyWindow.fontsize = _MEDIUM_;
	Input.MyWindow.type = _PROPORTIONNEL_;
	Input.MyWindow.font = 0;
	Input.MyWindow.correct = _ON_;
	Input.MyWindow.offset = 0;
	Input.MyWindow.shortcommand = _ON_;
	Input.MyWindow.selected = _OFF_;
	Input.MyWindow.thickness = 2;
	Input.MyWindow.border = _ON_;
	Input.MyWindow.popup = _NOPOPUP_;
	Input.MyWindow.first = 0;
	Input.MyWindow.current = 0;
	Input.MyWindow.time_out = 120;
	Input.MyWindow.title = (unsigned char*)szTitle;

	Input.tab[0] = (unsigned char*)szLabel;
	Input.tab[1] = (unsigned char*)szDefault;

	EntryNumeric.mask = 0;
	EntryNumeric.time_out = 120;
	EntryNumeric.line = 32;
	if (nMaxLength <= 18)
		EntryNumeric.column = 10;
	else if (nMaxLength == 19)
		EntryNumeric.column = 6;
	else EntryNumeric.column = 4;
	EntryNumeric.echo = ECHO_NORMAL;
	EntryNumeric.nb_max = (unsigned char)nMaxLength;
	EntryNumeric.nb_min = (unsigned char)nMinLength;

	G_Numerical_Entry((void*)&Input, &EntryNumeric);
	ttestall(ENTRY, 0);
	nResult = Get_Entry(&Entry);

	if (nResult == CR_ENTRY_OK)
	{
		strncpy(szInput, (char*)Entry.d_entry, Entry.d_len);
		szInput[Entry.d_len] = '\0';
		nResult = 0;
	}
	else if (nResult == CR_ENTRY_VALIDATED)
	{
		strcpy(szInput, szDefault);
		nResult = 0;
	}
	else
	{
		szInput[0] = '\0';
		if (nResult == CR_ENTRY_NOK)
			nResult = -2;
		else nResult = -1;
	}

	return nResult;
}


//===============================================================
// Function name	:	HelperAlphanumericInput
// Description		:	Graphical interface allowing to input a alpha_numerical entry

int HelperAlphanumericInput(const char* szTitle, const char* szLabel, int nMinLength, int nMaxLength, const char* szDefault, const char* szAllowedChars, char* szInput)
{
	int nSizeX;
	int nSizeY;
	StructList Input;
	int nResult;
	TAB_ENTRY_ALPHA EntryAlpha;
	ENTRY_BUFFER Entry;

	if (nMaxLength >= 40)
		nMaxLength = 40;
	if (nMinLength > nMaxLength)
		nMinLength = nMaxLength;

	GetScreenSize(&nSizeY, &nSizeX);

	memset(&Input, 0, sizeof(Input));
	Input.MyWindow.left = 0;
	Input.MyWindow.top = 0;
	Input.MyWindow.rigth = nSizeX - 1;
	Input.MyWindow.bottom = nSizeY - 1;
	if (nSizeY == 128)
		Input.MyWindow.nblines = 10;
	else Input.MyWindow.nblines = 5;
	Input.MyWindow.fontsize = _MEDIUM_;
	Input.MyWindow.type = _PROPORTIONNEL_;
	Input.MyWindow.font = 0;
	Input.MyWindow.correct = _ON_;
	Input.MyWindow.offset = 0;
	Input.MyWindow.shortcommand = _ON_;
	Input.MyWindow.selected = _OFF_;
	Input.MyWindow.thickness = 2;
	Input.MyWindow.border = _ON_;
	Input.MyWindow.popup = _NOPOPUP_;
	Input.MyWindow.first = 0;
	Input.MyWindow.current = 0;
	Input.MyWindow.time_out = 255;
	Input.MyWindow.title = (unsigned char*)szTitle;

	Input.tab[0] = (unsigned char*)szLabel;
	Input.tab[1] = (unsigned char*)szDefault;

	EntryAlpha.mask = 0;
	EntryAlpha.time_out = 255;
	EntryAlpha.line = 32;
	if (nMaxLength <= 18)
		EntryAlpha.column = 10;
	else if (nMaxLength == 19)
		EntryAlpha.column = 6;
	else EntryAlpha.column = 4;
	EntryAlpha.echo = ECHO_NORMAL;
	EntryAlpha.nb_max = (unsigned char)nMaxLength;
	EntryAlpha.nb_min = (unsigned char)nMinLength;
	EntryAlpha.tab_caracteres = (unsigned char*)szAllowedChars;

	G_Alphanumerical_Entry((void*)&Input, &EntryAlpha);
	ttestall(ENTRY, 0);
	nResult = Get_Entry(&Entry);

	if (nResult == CR_ENTRY_OK)
	{
		strncpy(szInput, (char*)Entry.d_entry, Entry.d_len);
		szInput[Entry.d_len] = '\0';
		nResult = 0;
	}
	else if (nResult == CR_ENTRY_VALIDATED)
	{
		strcpy(szInput, szDefault);
		nResult = 0;
	}
	else
	{
		szInput[0] = '\0';
		if (nResult == CR_ENTRY_NOK)
			nResult = -2;
		else nResult = -1;
	}

	return nResult;
}
