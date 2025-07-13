//! \file
//! Module that gives developers an helping interface for menu creation
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define C_DEFAULT_BEEP_VOLUME			(255)
#define C_DEFAULT_BEEP_DELAY			(50)

#define C_DEFAULT_BEEP_OK_FREQUENCY		(1500)
#define C_DEFAULT_BEEP_ERROR_FREQUENCY	(750)
#define C_DEFAULT_BEEP_OK_DELAY			(50)
#define C_DEFAULT_BEEP_ERROR_DELAY		(20)

#define C_DEFAULT_BEEP_PAYPASS_MOBIL_ERROR_DELAY	(20) // For same time as others (Demo CARTE 2010)
#define C_TIME_1S						100
#define C_TIME_100MS					10


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static unsigned long gs_ulAllLedsOnRemoveCardTime;

t_topstack * g_tsRemoveCard_task_handle;						// Handle of the Remove Card task.
static int g_RemoveCardTaskRunning = FALSE;						// Indicates if the Remove Card task is still running or if it is waiting to be killed.


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static int __HelperDisplayMenuInternal(const char* szTitle, int bRadioButtons, int nDefaultChoice, int nItems, const T_CLESS_SAMPLE_HELPER_MENU_ITEM Items[], int bUseCguiIconList);
static void __HelperDisplayTag(unsigned char * pStr, unsigned long ulTag, unsigned long ulReadLength, const unsigned char * pReadValue);
static void __HelperErrorSequenceEx (const int bWithBeep, const int bWithLeds);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Create a menu according options.
//! \param[in] szTitle : Menu name
//! \param[in] bRadioButton : is radio buttons or not
//! \param[in] nDefaultChoice : default choice
//! \param[in] nItems : number of items in the menu
//! \param[in] Items : arrays containing all the menu items
//! \param[in] bUseCguiIconList Indicates if the CGUI icon list shall be used (if available) or not. If not, CGUI list is used instead.
//! \return 0 if ok, error code else.

static int __HelperDisplayMenuInternal(const char* szTitle, int bRadioButtons, int nDefaultChoice, int nItems, const T_CLESS_SAMPLE_HELPER_MENU_ITEM Items[], int bUseCguiIconList)
{
	int lg_code;
	MSGinfos tMsg;
	int nSizeX;
	int nSizeY;
	StructList Menu;
	int i;
	int nResult;
	ENTRY_BUFFER Entry;
	int nBannerHeight;

	(void) bUseCguiIconList;

	// Get the manager configured language
	lg_code = PSQ_Give_Language();

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
	{
		ClessSample_Term_Read_Message(Items[i].nMessageId, lg_code, &tMsg);
		Menu.tab[i] = (unsigned char*)tMsg.message;
	}

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



//! \brief Trace tags information on trace tool.
//! \param[in] pStr string to trace.
//! \param[in] ulTag tag number.
//! \param[in] ulReadLength tag length.
//! \param[in] pReadValue tag value.
//! \return nothing.

static void __HelperDisplayTag(unsigned char * pStr, unsigned long ulTag, unsigned long ulReadLength, const unsigned char * pReadValue)
{
    // It's a timing tag
    unsigned int nIndex;
    char ucTmpStr[1000];
    char ucLittleStr[40];

    if (pStr)
    	GTL_Traces_TraceDebug("%s Tag :%lx len:%lx", pStr, ulTag, ulReadLength);
    else
    	GTL_Traces_TraceDebug("Tag :%lx len:%lx", ulTag, ulReadLength);

    strcpy(ucTmpStr, " ");
    for (nIndex=0; nIndex<ulReadLength; nIndex++)
    {
        sprintf(ucLittleStr, " %02x",   pReadValue[nIndex]);
        strcat(ucTmpStr, ucLittleStr);
        if (nIndex > 300)
        	break;
    }
    GTL_Traces_TraceDebug(ucTmpStr);
}



//! \brief Create a menu.
//! \param[in] szTitle .
//! \param[in] nDefaultChoice .
//! \param[in] nItems .
//! \param[in] Items .
//! \param[in] bUseCguiIconList Indicates if the CGUI icon list shall be used (if available) or not. If not, CGUI list is used instead.
//! \return 0 if input ok, error code else.

int HelperDisplayMenu(const char* szTitle, int nDefaultChoice, int nItems, const T_CLESS_SAMPLE_HELPER_MENU_ITEM Items[], int bUseCguiIconList)
{
	return __HelperDisplayMenuInternal(szTitle, FALSE, nDefaultChoice, nItems, Items, bUseCguiIconList);
}



//! \brief Create a choice menu (with radio buttons).
//! \param[in] szTitle .
//! \param[in] nDefaultChoice .
//! \param[in] nItems .
//! \param[in] Items .
//! \return 0 if input ok, error code else.

int HelperDisplayChoices(const char* szTitle, int nDefaultChoice, int nItems, const T_CLESS_SAMPLE_HELPER_MENU_ITEM Items[])
{
	return __HelperDisplayMenuInternal(szTitle, TRUE, nDefaultChoice, nItems, Items, FALSE);
}



//! \brief Graphical interface allowing to input a numerical entry.
//! \param[in] szTitle .
//! \param[in] szLabel .
//! \param[in] nMinLength .
//! \param[in] nMaxLength .
//! \param[in] szDefault.
//! \param[in] szInput.
//! \return 0 if input ok, error code else.

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



//! \brief Graphical interface allowing to input a alpha_numerical entry.
//! \param[in] szTitle .
//! \param[in] szLabel .
//! \param[in] nMinLength .
//! \param[in] nMaxLength .
//! \param[in] szDefault.
//! \param[in] szAllowedChars.
//! \param[in] szInput.
//! \return 0 if input ok, error code else.

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



//! \brief This function displays a text on the cless reader
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
//! \param[in] ucLongLine LONGLINE for long line to display.
//! \param[in] nFontSize Possibility to indicate the font size to use.

void _Helper_DisplayTextCustomer(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char bLedsOff, unsigned char ucLongLine, int nFontSize)
{
	int nPeriph;
	T_Bool bUsePinPad;
	FILE* hDisplay = NULL;

	if (bLedsOff && (!g_RemoveCardTaskRunning)) // If the Remove Card task is running, the leds will be turned off by the task itself
		HelperLedsOff();
	
    bUsePinPad = ClessSample_IsPinpadPresent();

	if (bUsePinPad)
	{
		// Warning, on graphical pinpad, library function must be used for long text
		
		// Tests if graphical function can be used on pinpad
		if (ClessSample_UseGraphicalFunctionOnPPAD())
		{
			InitContexteGraphique(PERIPH_PPR);
			ClessSample_Term_DisplayGraphicLine(nLineNumber, ptrMSG, nAlignment, nEraseDisplay, ucLongLine, nFontSize); 
			
			// Restore previous configuration
			InitContexteGraphique(PERIPH_DISPLAY);
		}
		else
		{
			if (!ucLongLine)
			{
				if (nEraseDisplay)
					PPS_firstline ();
				else
					PPS_newline ();
				// graphical function and long line can't be used on pinpad
				PPS_Display (ptrMSG->message);
			}
		}
	}
	else
	{
		nPeriph = TPass_GetCustomerDisplay(0, 0);

		if (nPeriph != PERIPH_DISPLAY)
			InitContexteGraphique(nPeriph);
		else
			hDisplay = fopen ("DISPLAY", "a");

		switch (nAlignment)
		{
		case CLESSSAMPLE_ALIGN_LEFT:
		case CLESSSAMPLE_ALIGN_RIGHT:
		case CLESSSAMPLE_ALIGN_CENTER:
			break;

		default :
			nAlignment = CLESSSAMPLE_ALIGN_CENTER;
			break;
		}
		
		if ((nPeriph != PERIPH_DISPLAY) || (hDisplay != NULL))
			ClessSample_Term_DisplayGraphicLine(nLineNumber, ptrMSG, nAlignment, (nEraseDisplay ? YESCLEAR : NOCLEAR), ucLongLine, nFontSize); 

		// Restore previous configuration
		if (nPeriph != PERIPH_DISPLAY)
			InitContexteGraphique(PERIPH_DISPLAY);
		else
			if (hDisplay != NULL)
				fclose (hDisplay);
	}
}



//! \brief This function displays a text on the PinPad or terminal used to input Pin.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
//! \param[in] bLongLine LONG if long line must be displayed.

void _Helper_DisplayPinText(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char bLedsOff, unsigned char bLongLine)
{
	int nDeviceType;
	int nPinDisplay = FALSE;
	T_Bool bIsPinPadPresent;

	// Device type ? for Cless device
	nDeviceType = TPass_GetDeviceType();
	switch(nDeviceType)
	{
	    case TPASS_CLESS_TYPE_P30C :
		case TPASS_CLESS_TYPE_IPP2XX :
		    nPinDisplay = TRUE;
		    break;
	    default: // No code
    		break;
    }

	// Device type ? for external PinPad
	bIsPinPadPresent = (ClessSample_IsPinpadPresent()) || ((ClessSample_Unattended_IsUnattendedMechanism()) && (ClessSample_Unattended_IsPinPadUPPwithUCMC()));

	// If a pinpad is declared
	if (bIsPinPadPresent)
	{
		// pinpad is here and can be used
		nPinDisplay = TRUE;
	}

    if (nPinDisplay) // If a specific display (different from merchant) is available for PIN information
    {
		if ((ClessSample_Unattended_IsUnattendedMechanism()) && (ClessSample_Unattended_IsPinPadUPPwithUCMC()))
		{
			iLIBUCM_Display_Graphic_Start(UCMC_DISPLAY_PPAD);
			ClessSample_Term_DisplayGraphicLine(nLineNumber, ptrMSG, nAlignment, (nEraseDisplay ? YESCLEAR : NOCLEAR), bLongLine, HELPERS_FONT_SIZE_DEFAULT); 
	        iLIBUCM_Display_Graphic_Stop(UCMC_DISPLAY_PPAD);
		}
		else
		{
			if (bLongLine)
				Helper_DisplayTextCustomerLong(nEraseDisplay, nLineNumber, ptrMSG, nAlignment, bLedsOff);
			else
				Helper_DisplayTextCustomer(nEraseDisplay, nLineNumber, ptrMSG, nAlignment, bLedsOff);
		}
    }
    else // No specific display for PN information => make it on merchant display
    {
        if (bLongLine)
            Helper_DisplayTextMerchantLong(nEraseDisplay, nLineNumber, ptrMSG, bLedsOff);
        else
            Helper_DisplayTextMerchant(nEraseDisplay, nLineNumber, ptrMSG, bLedsOff);
    }
}



//! \brief This function refresh the screen (for WGUI only) and waits for message reading if required.
//! \param[in] bWait \a TRUE if need to wait to read message, \a FALSE if not.
//! \param[in] bMerchantDisplay Indicates if this is the merchant display that should be refreshed or not. If \a TRUE, it means it is always refresh, if \a FALSE, the screen is refreshed using CGUI only if the customer screen is the internal terminal screen.

void Helper_RefreshScreen (const unsigned int bWait, const int bMerchantDisplay)
{
	(void) bMerchantDisplay;

	// Check if wait is needed to see message correctly before continuing.
	if (bWait)
		Helper_WaitUserDisplay();
}



//! \brief This function specify if a specific Display is available for the customer.
//! \return 
//!	- \ref TRUE if a specific display is available for customer.
//!	- \ref FALSE else.

int Helper_IsClessCustomerDisplayAvailable(void)
{
	int nDeviceType;
	int nCustomerDisplay = FALSE;
		
	// Device type ?
	nDeviceType = TPass_GetDeviceType();
	switch(nDeviceType)
	{
	case TPASS_CLESS_TYPE_TELIUM_PASS :
	case TPASS_CLESS_TYPE_VENDING_PASS :
	case TPASS_CLESS_TYPE_P30C :
	case TPASS_CLESS_TYPE_IPP2XX :
		nCustomerDisplay = TRUE;
		break;
		
	case TPASS_CLESS_TYPE_EMBEDDED :
	case TPASS_CLESS_TYPE_UNKNOWN :	// No action possible
	case TPASS_CLESS_TYPE_NONE :
	default:
		break;
	}
	return (nCustomerDisplay);
}



//! \brief Trace tags from a Share Buffer.
//! \param[in] share buffer with tags to trace.
//! \param[in] information type as C_INFORMATION_RESULT=>only results are traces, C_INFORMATION_ALL=> all tags are traced.
//! \return STATUS_SHARED_EXCHANGE_END if no problem, other else.

int HelperDisplayOutputTags(T_SHARED_DATA_STRUCT * pStruct, int nInformationType)
{
	int nResult, nPosition;
    unsigned long ulTag, ulReadLength;
	const unsigned char * pReadValue;
	int nTagToTrace;
	unsigned char ucStatusCode[] = "Status Code:"; 
	unsigned char ucCardType[] = "CardType :"; 
	unsigned char ucOnLinePinRequested[] = "On Line PIN Requested :"; 
	unsigned char ucSignatureRequested[] = "Signature Requested :";
	unsigned char * pStr;

    GTL_Traces_TraceDebug("__Menu_DisplayOutputTags lg:%lx\n", pStruct->ulDataLength);

	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	do{
    	// Try to following tag.
    	nResult = GTL_SharedExchange_GetNext (pStruct, &nPosition, &ulTag, &ulReadLength, &pReadValue);

        if (nResult == STATUS_SHARED_EXCHANGE_OK)  // If tag found
        {
        	nTagToTrace = 0; // Default value : tag musn't ne traced
        	pStr = 0; // String to display
        	switch (nInformationType)
        	{
        	case C_INFORMATION_RESULT: // Only
        		switch (ulTag)
        		{
	    			case TAG_KERNEL_STATUS_CODE:
	    				pStr = ucStatusCode;
	    			break;
	    			case TAG_KERNEL_CARD_TYPE:
	    				pStr = ucCardType;
	    			break;
	    			case TAG_KERNEL_ONLINE_PIN_REQUESTED:
	    				pStr = ucOnLinePinRequested;
	    			break;
	    			case TAG_KERNEL_SIGNATURE_REQUESTED:
	    				pStr = ucSignatureRequested;
	    			break;
	    			default:
	    				// No action on other tags
	    				break;
        		}        			
        			nTagToTrace = 1; // Tag recognized : trace it !
        		break;
        		
        	case C_INFORMATION_ALL:
    			nTagToTrace = 1; // All Tag to trace.
        		break;
        		
        	default : // No trace
        		break;
        	}

        	if (nTagToTrace)
        	{
        		__HelperDisplayTag(pStr, ulTag, ulReadLength, pReadValue);
        	}
        }
        else if (nResult == STATUS_SHARED_EXCHANGE_END)  // Buffer end reached
        {
        	GTL_Traces_TraceDebug("ShareGetNext end");
          // No action
        }
        else // error or end or ...
        {
        	GTL_Traces_TraceDebug("Display tags error:%x\n", nResult);
        }
    }while (nResult == STATUS_SHARED_EXCHANGE_OK);

	return (nResult);
}



//! \brief Process the deactivation sequence (buzzer 1500Hz, Leds in order) and displays the correct message.
//! \param[in] pSharedData Data structure containing the customisation data (step ID, and prefered selected language if present).
//! \return nothing.

void HelperRemoveCardSequence (T_SHARED_DATA_STRUCT * pSharedData)
{
	int merchLang, nCardHolderLang;
	unsigned char * pInfo;

	merchLang = PSQ_Give_Language();

    if (ClessSample_Common_RetrieveInfo (pSharedData, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, &pInfo))
		nCardHolderLang = ClessSample_Term_GiveLangNumber(pInfo);
	else
		nCardHolderLang = merchLang;

	ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_PAYPASS_SCREEN_REMOVE, merchLang, nCardHolderLang);
    
	// Save current timer in order to wait 750ms before turning off all the LEDs
	gs_ulAllLedsOnRemoveCardTime = GTL_StdTimer_GetCurrent();
}



//! \brief Process the deactivation sequence (buzzer 1500Hz, Leds in order) and displays the correct message.
//! \param[in] pSharedData Data structure containing the customisation data (step ID, and prefered selected language if present).
//! \return nothing.

void HelperRemoveCardSequenceTwoLines (T_SHARED_DATA_STRUCT * pSharedData)
{
	int merchLang, nCardHolderLang;
	unsigned char * pInfo;

	merchLang = PSQ_Give_Language();

    if (ClessSample_Common_RetrieveInfo (pSharedData, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, &pInfo))
		nCardHolderLang = ClessSample_Term_GiveLangNumber(pInfo);
	else
		nCardHolderLang = merchLang;

    ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_REMOVE_CARD_TWO_LINES, merchLang, nCardHolderLang);

	// Save current timer in order to wait 750ms before turning off all the LEDs
	gs_ulAllLedsOnRemoveCardTime = GTL_StdTimer_GetCurrent();
}



//! \brief Process the represent card sequence.
//! \param[in] pSharedData Data structure containing the customisation data (prefered selected language if present).
//! \return nothing.

void HelperRepresentCardSequence (T_SHARED_DATA_STRUCT * pSharedData)
{
	int merchLang;
	int nCardHolderLang;
	unsigned char * pInfo;
	// MSGinfos tCardHolderMsg;

	merchLang = PSQ_Give_Language();
    if (ClessSample_Common_RetrieveInfo (pSharedData, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, &pInfo))
		nCardHolderLang = ClessSample_Term_GiveLangNumber(pInfo);
	else
		nCardHolderLang = merchLang;
	
    ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_REPRESENT_CARD, merchLang, nCardHolderLang);
}



//! \brief Process the deactivation sequence (buzzer 1500Hz, Leds in order).
//! \param[in] nWithBeep = TRUE if Beep and delay must be made,
//! \return nothing.

void HelperErrorSequence(int nWithBeep)
{
	__HelperErrorSequenceEx (nWithBeep, FALSE);
}



//! \brief Process the deactivation sequence (buzzer 1500Hz, Leds in order).
//! \param[in] bWithBeep TRUE if Beep and delay must be made.
//! \param[in] bWithBeep TRUE if LEDs sequence shall be done.

static void __HelperErrorSequenceEx (const int bWithBeep, const int bWithLeds)
{
	gs_ulAllLedsOnRemoveCardTime = 0;

	if (bWithLeds)
	{
		TPass_LedsOnColored (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
	}

	if (bWithBeep)
		TPass_BuzzerBeep(C_DEFAULT_BEEP_ERROR_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME, C_DEFAULT_BEEP_ERROR_DELAY);
	else if (bWithLeds)
		ttestall (0, C_DEFAULT_BEEP_ERROR_DELAY);

	if (bWithLeds)
	{
		TPass_LedsOffColored (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
		ttestall (0, C_DEFAULT_BEEP_ERROR_DELAY);
		TPass_LedsOnColored (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
	}
	else
	{
		ttestall (0, C_DEFAULT_BEEP_ERROR_DELAY);
	}

	if (bWithBeep)
		TPass_BuzzerBeep(C_DEFAULT_BEEP_ERROR_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME, C_DEFAULT_BEEP_ERROR_DELAY);
	else if (bWithLeds)
		ttestall (0, C_DEFAULT_BEEP_ERROR_DELAY);

	TPass_LedsOffColored (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4 | 
				   TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_GREEN | TPASS_LED_RED);
}



//! \brief Display a message on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nFontSize Possibility to indicate the desired font size.
//! \return nothing.

void _HelperDisplayMessageOnTerminal(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, unsigned char bLongLine, int nFontSize)
{
	FILE* hDisplay;

	if (ClessSample_Unattended_IsUnattendedMechanism())
		ClessSample_Unattended_PrintDump(ptrMSG->message);

	hDisplay = fopen ("DISPLAY", "a");

	if (hDisplay != NULL)
	{
		InitContexteGraphique(PERIPH_DISPLAY);
		ClessSample_Term_DisplayGraphicLine(nLineNumber, ptrMSG, CLESSSAMPLE_ALIGN_CENTER, (nEraseDisplay ? YESCLEAR : NOCLEAR), bLongLine, nFontSize); 
		fclose (hDisplay);
	}
}



//! \brief Display transaction result on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
//! \param[in] bLongLine LONG if long line must be displayed.
//! \param[in] nFontSize Possibility to indicate the font size.
//! \return nothing.

void _Helper_DisplayTextMerchant (int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, unsigned char bLedsOff, unsigned char bLongLine, int nFontSize)
{
	if (bLedsOff)
		HelperLedsOff();

	_HelperDisplayMessageOnTerminal(nEraseDisplay, nLineNumber, ptrMSG, bLongLine, nFontSize);	
}



//! \brief Wait allowing user to see srceen message.
//! \return nothing.

void Helper_WaitUserDisplay(void)
{
	// To see message before the iddle message
	ttestall(0, 2* C_TIME_1S);
}



//! \brief Wait just 600ms allowing user to see screen message.
//! \return nothing.

void Helper_QuickWaitUserDisplay(void)
{
	// To see message before the iddle message
	ttestall(0, 6 * C_TIME_100MS);
}



//! \brief This function wait 750ms to see LEDS.
//! \return nothing.

void HelperWaitLedsTime (void)
{
	int nTimeout;

	// If common IHM is not used, blinks the first LED at idle
	// Wait 1000ms as the timer is started at the same moment the second LED and the buzzer are turned on
	nTimeout = GTL_StdTimer_GetRemaining(gs_ulAllLedsOnRemoveCardTime, 100);
	if (nTimeout > 0)
		ttestall (0, nTimeout);

	gs_ulAllLedsOnRemoveCardTime = 0;
}



//! \brief Wait 750ms and set LEDS off.
//! \return nothing.

void HelperLedsOff (void)
{
	HelperWaitLedsTime();
	TPass_LedsOffColored (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4 | 
				   TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_GREEN | TPASS_LED_RED);
}



//! \brief This function set the LEDs into the idle state (first LED blinking 250ms every 5 seconds).
//! \return nothing.

void HelperLedsIdleState (void)
{
	HelperWaitLedsTime();
	
	// Turn off Leds 2, 3 and 4 
	TPass_LedsOff(TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
	// Make the first Led blinking 200ms every 5 seconds
	TPass_LedsBlink(TPASS_LED_1, 10, 240);

	gs_ulAllLedsOnRemoveCardTime = 0;
}



//! \brief This function set the LEDs into the idle state (first LED blinking 250ms every 5 seconds).
//! \param[in] pMsg User question informations ("Signature OK ?" for example).
//! \param[in] nTimeout Tiemout (in seconds) for user answer (if no answer, default return if \a FALSE).
//! \param[in] nMerchantLanguage Indicates the merchant language to be used.
//! \return
//!		- \a TRUE if user selected "YES".
//!		- \a FALSE if not.

int HelperQuestionYesNo (MSGinfos * pMsg, int nTimeout, int nMerchantLanguage)
{
	int nResult;
	TAB_ENTRY_FCT TabEntryFct;
	ENTRY_BUFFER Entry;
	int nResultTmp;
	MSGinfos tMsgInfo;

	if (ClessSample_Unattended_IsUnattendedMechanism())
		return TRUE;

		
	// Display the question with "YES" and "NO" for choices
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, pMsg, FALSE);

	ClessSample_Term_Read_Message(STD_MESS_CHOICE_YES_NO, nMerchantLanguage, &tMsgInfo);
	Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_4, &tMsgInfo, FALSE);
	Helper_RefreshScreen (NOWAIT, HELPERS_MERCHANT_SCREEN);

	nResult = FALSE;

	TabEntryFct.mask = MASK_ANNULATION | MASK_SKVAL | MASK_SKCORR | MASK_VALIDATION
							| MASK_SK1 | MASK_SK2 | MASK_SK3 | MASK_SK4;
	TabEntryFct.time_out = nTimeout;
	Fct_Entry(&TabEntryFct);
	ttestall(ENTRY, 0);

	// Get the entry
	nResultTmp = Get_Entry(&Entry);

	if (nResultTmp == CR_ENTRY_OK)
	{
		if (Entry.d_len > 0)
		{
			if ((Entry.d_entry[0] == TC_SKVAL) || (Entry.d_entry[0] == TC_SK1) || (Entry.d_entry[0] == TC_SK2))
				nResult = TRUE;
		}
	}

	if (nResultTmp == CR_ENTRY_VALIDATED)
		nResult = TRUE;

	return nResult;
}



//! \brief This function displays a text on the cless reader
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display.
//! \return Nothing.

void Helper_DisplayBlankLineCustomer(int nEraseDisplay, int nLineNumber)
{
	int nPeriph;
	MSGinfos tMsgInfo;
	char ucBlankLine[] = " ";

	tMsgInfo.message = ucBlankLine;
	tMsgInfo.file = NULL; // Unused fields
	tMsgInfo.coding = 0;

    if (ClessSample_IsPinpadPresent())
    {
		// Warning, on graphical pinpad, library function must be used for long text

		// Tests if graphical function can be used on pinpad
		if (ClessSample_UseGraphicalFunctionOnPPAD())
		{
			InitContexteGraphique(PERIPH_PPR);
			ClessSample_Term_DisplayGraphicLine(nLineNumber, &tMsgInfo, CLESSSAMPLE_ALIGN_CENTER, CLEAR, SHORTLINE, HELPERS_FONT_SIZE_DEFAULT);

			// Restore previous configuration
			InitContexteGraphique(PERIPH_DISPLAY);
		}
		else
		{
			if (nEraseDisplay)
				PPS_firstline ();
			// graphical function and long line can't be used on pinpad
			PPS_Display (tMsgInfo.message);
		}
	}
	else
	{
		nPeriph = TPass_GetCustomerDisplay(0, 0);
		InitContexteGraphique(nPeriph);
		ClessSample_Term_DisplayGraphicLine(nLineNumber, &tMsgInfo, CLESSSAMPLE_ALIGN_CENTER, (nEraseDisplay ? YESCLEAR : NOCLEAR), SHORTLINE, HELPERS_FONT_SIZE_DEFAULT);
	}
}



//! \brief Turn on the first LED and turn off the three others.

void HelperCardWait(void)
{
	TPass_LedsOff(TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
	TPass_LedsOn (TPASS_LED_1);
}



//! \brief Initialise global variables

static void __UIH_RemoveCardTask_InitVariables (void)
{
	g_tsRemoveCard_task_handle = NULL;		// Init the task handle
}


//! \brief This task start the remove card sequence (leds, buzzer).

static word __RemoveCardTask_StartTask (void)
{
	unsigned long ulBeforeDeselectDisplayTime = 0;
	int nTimeout;


	ulBeforeDeselectDisplayTime = GTL_StdTimer_GetCurrent();

	// Save current timer in order to wait 750ms before turning off all the LEDs
	gs_ulAllLedsOnRemoveCardTime = GTL_StdTimer_GetCurrent();

	// Turn on the buzzer
	TPass_Buzzer(C_DEFAULT_BEEP_OK_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME);

	// Turn on the 2nd LED
	TPass_LedsOn(TPASS_LED_1 | TPASS_LED_2);
	
	// Wait before turning on third LED
	nTimeout = GTL_StdTimer_GetRemaining(ulBeforeDeselectDisplayTime, 13);
	if (nTimeout > 0)
		ttestall(0, nTimeout);

	// Turn on third LED
	TPass_LedsOn (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3);

	// Wait before turning on fourth LED
	nTimeout = GTL_StdTimer_GetRemaining(ulBeforeDeselectDisplayTime, 25);
	if (nTimeout > 0)
		ttestall(0, nTimeout);

	// Turn on fourth LED
	TPass_LedsOn (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);

	// Wait display time
	nTimeout = GTL_StdTimer_GetRemaining(ulBeforeDeselectDisplayTime, C_DEFAULT_BEEP_OK_DELAY);
	if (nTimeout > 0)
	{
		ttestall(0, nTimeout);
		nTimeout = 0;
	}

	// Turn off buzzer
	TPass_Buzzer (0, 0);

	HelperLedsOff();

	g_RemoveCardTaskRunning = FALSE;		// Task is not running

	return (TRUE);
}

//! \brief Clear the screen.

void UIH_ClearScreen(void)
{
	int nPeriph;

	if ((TPass_GetDeviceType() == TPASS_CLESS_TYPE_IPP2XX) && (!ClessSample_UseGraphicalFunctionOnPPAD()))
	{
		PPS_firstline ();
	}
	else
	{
		nPeriph = TPass_GetCustomerDisplay(0, 0);

		InitContexteGraphique(nPeriph);

		// Clear the screen
		_clrscr();
		_DrawString(" ",1,20,_OFF_);
		PaintGraphics();

		// Restore previous configuration
		InitContexteGraphique(PERIPH_DISPLAY);
	}
}

//! \brief Launch the task that manages the remove card sequence (PayPass specific needs).
//! \return OK if task correctly launched, KO else.

int UIH_RemoveCardTask_Launch (void)
{
	g_RemoveCardTaskRunning = TRUE;		// Task is running

	// Init global variables
	__UIH_RemoveCardTask_InitVariables();

	// Launch the status task
	g_tsRemoveCard_task_handle = fork (&__RemoveCardTask_StartTask, NULL, -1);

	// The task cannot be created
	if (g_tsRemoveCard_task_handle == NULL)
	{
		g_RemoveCardTaskRunning = FALSE;	
		return KO;
	}

	return OK;
}



//! \brief Indicates if the remove card task is running or not.
//! \return
//!	- \a TRUE if the task is running.
//!	- \a FALSE if not.

int UIH_IsRemoveCardTaskRunning (void)
{
	return (g_RemoveCardTaskRunning);
}



//! \brief Wait the end of the Remove Card task.

void UIH_RemoveCardTask_WaitEnd (void)
{
	if (g_tsRemoveCard_task_handle != NULL) // If the task is launched
	{
		while (g_RemoveCardTaskRunning) // While the task has not terminated processing
		{
			// Waits a little
			ttestall (0, 1);
		}		
		g_tsRemoveCard_task_handle = NULL;
	}
}
