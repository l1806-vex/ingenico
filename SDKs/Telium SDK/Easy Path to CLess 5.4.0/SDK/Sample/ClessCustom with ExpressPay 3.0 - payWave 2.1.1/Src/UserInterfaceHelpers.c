//! \file
//! Module that gives developers an helping interface for menu creation
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static unsigned long gs_ulAllLedsOnRemoveCardTime;

t_topstack * g_tsRemoveCard_task_handle;						// Handle of the Remove Card task.
static int g_RemoveCardTaskRunning = FALSE;						// Indicates if the Remove Card task is still running or if it is waiting to be killed.

/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static int __HelperDisplayMenuInternal(const char* szTitle, int bRadioButtons, int nDefaultChoice, int nItems, const T_CLESS_SAMPLE_HELPER_MENU_ITEM Items[]);
static void __HelperDisplayTag(unsigned char * pStr, unsigned long ulTag, unsigned long ulReadLength, const unsigned char * pReadValue);
static void __Helper_Beep (void);
static void __Helper_BeepBeep (void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Create a menu according options.
//! \param[in] szTitle : Menu name
//! \param[in] bRadioButton : is radio buttons or not
//! \param[in] nDefaultChoice : default choice
//! \param[in] nItems : number of items in the menu
//! \param[in] Items : arrays containing all the menu items
//! \return 0 if ok, error code else.
static int __HelperDisplayMenuInternal(const char* szTitle, int bRadioButtons, int nDefaultChoice, int nItems, const T_CLESS_SAMPLE_HELPER_MENU_ITEM Items[])
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
    char acTmpStr[1000];
    char acLittleStr[40];

    if (pStr)
    	GTL_Traces_TraceDebug("%s Tag :%lx len:%lx", pStr, ulTag, ulReadLength);
    else
    	GTL_Traces_TraceDebug("Tag :%lx len:%lx", ulTag, ulReadLength);

    strcpy(acTmpStr, " ");
    for (nIndex=0; nIndex<ulReadLength; nIndex++)
    {
        sprintf(acLittleStr, " %02x",   pReadValue[nIndex]);
        strcat(acTmpStr, acLittleStr);
        if (nIndex > 300)
        	break;
    }
    GTL_Traces_TraceDebug(acTmpStr);
}


//! \brief Create a menu.
//! \param[in] szTitle .
//! \param[in] nDefaultChoice .
//! \param[in] nItems .
//! \param[in] Items .
//! \return 0 if input ok, error code else.
int HelperDisplayMenu(const char* szTitle, int nDefaultChoice, int nItems, const T_CLESS_SAMPLE_HELPER_MENU_ITEM Items[])
{
	return __HelperDisplayMenuInternal(szTitle, FALSE, nDefaultChoice, nItems, Items);
}


//! \brief Create a choice menu (with radio buttons).
//! \param[in] szTitle .
//! \param[in] nDefaultChoice .
//! \param[in] nItems .
//! \param[in] Items .
//! \return 0 if input ok, error code else.
int HelperDisplayChoices(const char* szTitle, int nDefaultChoice, int nItems, const T_CLESS_SAMPLE_HELPER_MENU_ITEM Items[])
{
	return __HelperDisplayMenuInternal(szTitle, TRUE, nDefaultChoice, nItems, Items);
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
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
//! \param[in] ucLongLine LONGLINE for long line to display.

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
	bIsPinPadPresent = ClessSample_IsPinpadPresent();

	// If a pinpad is declared
	if (bIsPinPadPresent)
	{
		// pinpad is here and can be used
		nPinDisplay = TRUE;
	}

    if (nPinDisplay) // If a specific display (different from merchant) is available for PIN information
    {
        if (bLongLine)
            Helper_DisplayTextCustomerLong(nEraseDisplay, nLineNumber, ptrMSG, nAlignment, bLedsOff);
        else
            Helper_DisplayTextCustomer(nEraseDisplay, nLineNumber, ptrMSG, nAlignment, bLedsOff);
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
	unsigned long ulBeforeDeselectDisplayTime = 0;
	int nTimeout;
	int merchLang, nCardHolderLang;
	unsigned char auCustomerDisplayAvailable;
	unsigned char bIsPinPadPresent = FALSE;
	unsigned char * pInfo;
	MSGinfos tMerchantMsg;
	MSGinfos tCardHolderMsg;

	ulBeforeDeselectDisplayTime = GTL_StdTimer_GetCurrent();
	
	// Turn on the buzzer
	TPass_Buzzer(C_DEFAULT_BEEP_OK_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME);

	// Turn on the 2nd LED
	if(!ClessSample_VisaWave_IsVisaAsiaGuiMode())
		TPass_LedsOn(TPASS_LED_1 | TPASS_LED_2);

	merchLang = PSQ_Give_Language();
    if (ClessSample_Common_RetrieveInfo (pSharedData, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, &pInfo))
		nCardHolderLang = ClessSample_Term_GiveLangNumber(pInfo);
	else
		nCardHolderLang = merchLang;
	
	auCustomerDisplayAvailable = Helper_IsClessCustomerDisplayAvailable();
	
    // If a pinpad is declared
    if (ClessSample_IsPinpadPresent())
    {
	    // Tests if pinpad is ok, and connected
	    if(IsPPSConnected() == 0)
	    {
		    // pinpad is here and can be used
		    bIsPinPadPresent = TRUE;
	    }
    }		
	// Display the "Remove card" message
	if(!ClessSample_VisaWave_IsVisaAsiaGuiMode())
	{
		if (auCustomerDisplayAvailable || bIsPinPadPresent) // If a customer display is available
		{
			ClessSample_Term_Read_Message(STD_MESS_REMOVE_CARD, merchLang, &tMerchantMsg);
			Helper_DisplayTextMerchant(TRUE, HELPERS_MERCHANT_LINE_3, &tMerchantMsg, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		// Display the customer message
		ClessSample_Term_Read_Message(STD_MESS_REMOVE_CARD, nCardHolderLang, &tCardHolderMsg);
		Helper_DisplayTextCustomer (ERASE, HELPERS_CUSTOMER_LINE_2, &tCardHolderMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);

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

		TPass_Buzzer (0, 0);

		// Save current timer in order to wait 750ms before turning off all the LEDs
		gs_ulAllLedsOnRemoveCardTime = GTL_StdTimer_GetCurrent();
	}
	else
	{
		if (auCustomerDisplayAvailable || bIsPinPadPresent) // If a customer display is available
		{
			ClessSample_Term_Read_Message(VISAWAVE_MESS_REMOVE_CARD, merchLang, &tMerchantMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tMerchantMsg, LEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_PLEASE_WAIT, merchLang, &tMerchantMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMerchantMsg, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		// Display the customer message
		ClessSample_Term_Read_Message(VISAWAVE_MESS_REMOVE_CARD, nCardHolderLang, &tCardHolderMsg);
		Helper_DisplayTextCustomer (ERASE, HELPERS_CUSTOMER_LINE_2, &tCardHolderMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_PLEASE_WAIT, nCardHolderLang, &tCardHolderMsg);
		Helper_DisplayTextCustomer (NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tCardHolderMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);

		TPass_LedsOn(TPASS_LED_GREEN);

		// Wait display time
		nTimeout = GTL_StdTimer_GetRemaining(ulBeforeDeselectDisplayTime, C_DEFAULT_BEEP_OK_DELAY);
		if (nTimeout > 0)
		{
			ttestall(0, nTimeout);
			nTimeout = 0;
		}

		TPass_Buzzer (0, 0);

		// Wait display time
		nTimeout = GTL_StdTimer_GetRemaining(ulBeforeDeselectDisplayTime, 200);
		if (nTimeout > 0)
		{
			ttestall(0, nTimeout);
			nTimeout = 0;
		}

		// Save current timer in order to wait 750ms before turning off all the LEDs
		gs_ulAllLedsOnRemoveCardTime = GTL_StdTimer_GetCurrent();
	}
}

//! \brief Process the represent card sequence.
//! \param[in] pSharedData Data structure containing the customisation data (prefered selected language if present).
//! \return nothing.
void HelperRepresentCardSequence (T_SHARED_DATA_STRUCT * pSharedData)
{
	int merchLang;
	int nCardHolderLang;
	unsigned char * pInfo;

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
	gs_ulAllLedsOnRemoveCardTime = 0;

	if (nWithBeep)
	{
		TPass_BuzzerBeep(C_DEFAULT_BEEP_ERROR_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME, C_DEFAULT_BEEP_ERROR_DELAY);
		ttestall (0, C_DEFAULT_BEEP_ERROR_DELAY);
		TPass_BuzzerBeep(C_DEFAULT_BEEP_ERROR_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME, C_DEFAULT_BEEP_ERROR_DELAY);
	}

	TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4 | 
				TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_GREEN | TPASS_LED_RED);

}


//! \brief Display a message on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \return nothing.
void _HelperDisplayMessageOnTerminal(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, unsigned char bLongLine, int nFontSize)
{
	FILE* hDisplay;

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
	TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4 | 
				TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_GREEN | TPASS_LED_RED);
}


//! \brief This function set the LEDs into the idle state (first LED blinking 250ms every 5 seconds).
//! \return nothing.
void HelperLedsIdleState (void)
{
	HelperWaitLedsTime();
	
	if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
	{	
		TPass_LedsOff(TPASS_LED_YELLOW | TPASS_LED_GREEN | TPASS_LED_RED);
		TPass_LedsOn(TPASS_LED_BLUE);
	}
	else
	{
		// Turn off Leds 2, 3 and 4 
		TPass_LedsOff(TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
		// Make the first Led blinking 200ms every 5 seconds
		TPass_LedsBlink(TPASS_LED_1, 10, 240);
	}
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
	
	// Display the question with "YES" and "NO" for choices
	if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
		Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, pMsg, TRUE);
	else
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


//! \brief This function set the LEDs into the idle state (first LED blinking 250ms every 5 seconds).
//! \param[in] pMsg User question informations ("Signature OK ?" for example).
//! \param[in] nTimeout Tiemout (in seconds) for user answer (if no answer, default return if \a FALSE).
//! \param[in] nMerchantLanguage Indicates the merchant language to be used.
//! \return
//!		- \a TRUE if user selected "YES".
//!		- \a FALSE if not.

int HelperSignatureCapture (MSGinfos * pMsg, int nMerchantLanguage)
{
	int nResult;
	/*TAB_ENTRY_FCT TabEntryFct;
	ENTRY_BUFFER Entry;
	int nResultTmp;
	MSGinfos tMsgInfo;
	
	// Display the question with "YES" and "NO" for choices
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_1, pMsg, FALSE);

	ClessSample_Term_Read_Message(STD_MESS_CHOICE_YES_NO, nMerchantLanguage, &tMsgInfo);
	Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_2, &tMsgInfo, FALSE);
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

	if (nResultTmp == CR_ENTRY_VALIDATED)*/
		nResult = TRUE;

	return nResult;
}

////////////////////////////////////////////////////////////////
// SPECIFIC ASIA USER INTERFACE FOR VISA PAYWAVE AND VISAWAVE //
////////////////////////////////////////////////////////////////


//! \brief Perform a beep sound.

static void __Helper_Beep (void)
{
	TPass_Buzzer(C_DEFAULT_BEEP_OK_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME);
	ttestall(0,10);
	TPass_Buzzer (0,0);
}


//! \brief Perform a beep beep sound.

static void __Helper_BeepBeep (void)
{
	TPass_Buzzer(C_DEFAULT_BEEP_OK_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME);
	ttestall(0,10);
	TPass_Buzzer (0,0);
	ttestall(0,10);
	TPass_Buzzer(C_DEFAULT_BEEP_OK_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME);
	ttestall(0,10);
	TPass_Buzzer (0,0);
}


//! \brief Third ligth is on and beep beep sound.

void Helper_PerformOKSequence (void)
{
	TPass_LedsOff(TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_RED);
	TPass_LedsOn(TPASS_LED_GREEN);
	__Helper_BeepBeep();
	ttestall(0,500);
}


//! \brief Fourth ligth blinking and beep beep sound.

void Helper_PerformKOSequence (void)
{
	TPass_LedsOff(TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_GREEN);
	TPass_LedsBlink(TPASS_LED_RED, VISA_ASIA_LED_BLINK_ON, VISA_ASIA_LED_BLINK_OFF);
	__Helper_BeepBeep();
	ttestall(0,300);
}


//! \brief Third ligth blinking and beep sound.

void Helper_PerformOfflineSequence (void)
{
	TPass_LedsOff(TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_RED);
	TPass_LedsBlink(TPASS_LED_GREEN, VISA_ASIA_LED_BLINK_ON, VISA_ASIA_LED_BLINK_OFF);
	__Helper_Beep();
	ttestall(0,500);
}


//! \brief Third ligth blinking.

void Helper_PerformOnlineSequence (void)
{
	TPass_LedsOff(TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_RED);
	TPass_LedsBlink(TPASS_LED_GREEN, VISA_ASIA_LED_BLINK_ON, VISA_ASIA_LED_BLINK_OFF);
}


//! \brief Third ligth blinking and beep sound.

void Helper_PerformCVMSequence (void)
{
	TPass_LedsOff(TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_RED);
	TPass_LedsBlink(TPASS_LED_GREEN, VISA_ASIA_LED_BLINK_ON, VISA_ASIA_LED_BLINK_OFF);
	__Helper_Beep();
}


//! \brief Perform the signature CVM IHM.

void Helper_Visa_SignatureCVMIHM(const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang)
{
	MSGinfos tMsg;

	if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
	{
		Helper_PerformCVMSequence();

		// Warning, this message in on 2 lines
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(VISAWAVE_MESS_SIGNATURE_CHECK_L1, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, NOLEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_SIGNATURE_CHECK_L2, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_4, &tMsg, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(VISAWAVE_MESS_SIGNATURE_CHECK_L1, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_SIGNATURE_CHECK_L2, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
	}
	else
	{
		// Warning, this message in on 2 lines
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_CHECK_L1, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
			ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_CHECK_L2, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_4, &tMsg, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_CHECK_L1, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
		ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_CHECK_L2, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);
	}
}

//! \brief Perform the IHM for an approved transaction (either offline or online).
//! \param[in] nVisa : Indicates if it is a payWave or a VisaWave transaction.
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction
//! \param[in] nAOSA : with Available Offline Spending Amount : WITH_AOSA or WITHOUT_AOSA

void Helper_Visa_ApprovedIHM(const int nVisa, const int nOfflineOnline, T_SHARED_DATA_STRUCT * pDataStruct, const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang, const int nAOSA)
{
	MSGinfos tMsg;
	int nMsgNum;

	if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(VISAWAVE_MESS_THANK_YOU, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_1, &tMsg, NOLEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, NOLEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION_COMPLETED, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_4, &tMsg, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(VISAWAVE_MESS_THANK_YOU, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION_COMPLETED, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_4, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);

		Helper_RefreshScreen(NO_WAIT, HELPERS_CUSTOMER_SCREEN);

		Helper_PerformOKSequence();
	}
	else
	{
		if(nOfflineOnline == OFFLINE)
			nMsgNum =STD_MESS_OFFLINE_APPROVED;
		else
			nMsgNum =STD_MESS_ONLINE_APPROVED;
		
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(nMsgNum, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(nMsgNum, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);

		if ((TPass_GetDeviceType() == TPASS_CLESS_TYPE_IPP2XX) && (!ClessSample_UseGraphicalFunctionOnPPAD())) // Two lines display
			Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);

		if (nAOSA == WITH_AOSA)
		{
			if(nVisa == HELPERS_VISAWAVE)
			{
				if(nOfflineOnline == OFFLINE)
					Helper_Visa_DisplayAvailableAmount(HELPERS_VISAWAVE, pDataStruct, nCardHolderLang);
			}
			else
			{
				Helper_Visa_DisplayAvailableAmount(HELPERS_PAYWAVE, pDataStruct, nCardHolderLang);
			}
		} // else (nAOSA == WITHOUT_AOSA) => no action
		Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);
	}
}

//! \brief Perform the IHM when the Signature CVM is OK.
//! \param[in] nVisa Indicates if it is a payWave or a VisaWave transaction.

void Helper_Visa_SignatureOKIHM(const int nVisa, T_SHARED_DATA_STRUCT * pDataStruct, const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang)
{
	MSGinfos tMsg;

	if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_CORRECT, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}

		ClessSample_Term_Read_Message(VISAWAVE_MESS_THANK_YOU, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION_COMPLETED, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_4, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);

		Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
		Helper_PerformOKSequence();
	}
	else
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_CORRECT, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}

		ClessSample_Term_Read_Message(STD_MESS_APPROVED, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);

		if ((TPass_GetDeviceType() == TPASS_CLESS_TYPE_IPP2XX) && (!ClessSample_UseGraphicalFunctionOnPPAD())) // Two lines display
			Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);

		// Display Available amount
		Helper_Visa_DisplayAvailableAmount(nVisa, pDataStruct, nCardHolderLang);

		Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);
	}
}

//! \brief Perform the IHM when the Signature CVM is KO.
//! \param[in] nVisa : Indicates if it is a payWave or a VisaWave transaction.

void Helper_Visa_SignatureKOIHM(const int nVisa, T_SHARED_DATA_STRUCT * pDataStruct, const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang)
{
	MSGinfos tMsg;

	if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(VISAWAVE_MESS_SIGNATURE_REQUIRED, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, LEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, NOLEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION_NOT_COMPLETED, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_4, &tMsg, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(VISAWAVE_MESS_SIGNATURE_REQUIRED, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION_NOT_COMPLETED, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);

		Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
		Helper_PerformKOSequence();
	}
	else
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_INCORRECT, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(STD_MESS_OFFLINE_DECLINED, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer (ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);

		if ((TPass_GetDeviceType() == TPASS_CLESS_TYPE_IPP2XX) && (!ClessSample_UseGraphicalFunctionOnPPAD())) // Two lines display
			Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);

		// Display Available amount
		Helper_Visa_DisplayAvailableAmount(nVisa, pDataStruct, nCardHolderLang);
		Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);
	}
}

//! \brief Perform the IHM when the PIN Entry CVM is KO.

void Helper_Visa_PinEntryKOIHM(const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang)
{
	MSGinfos tMsg;

	if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(VISAWAVE_MESS_PIN_REQUIRED, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, LEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, NOLEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION_NOT_COMPLETED, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_4, &tMsg, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(VISAWAVE_MESS_PIN_REQUIRED, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION_NOT_COMPLETED, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);

		Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
		Helper_PerformKOSequence();
	}
	else
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(STD_MESS_PIN_ERROR, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}

		ClessSample_Term_Read_Message(STD_MESS_PIN_ERROR, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
		Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);
	}
}

//! \brief Perform the IHM for a declined transaction (either offline or online).
//! \param[in] nVisa : Indicates if it is a payWave or a VisaWave transaction.
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction

void Helper_Visa_DeclinedIHM(const int nVisa, const int nOfflineOnline, T_SHARED_DATA_STRUCT * pDataStruct, const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang)
{
	MSGinfos tMsg;
	int nMsgNum;
	
	if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_1, &tMsg, LEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION_DECLINED, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, NOLEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L1, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, NOLEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L2, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_4, &tMsg, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION_DECLINED, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L1, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L2, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_4, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);

		Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
		Helper_PerformKOSequence();
	}
	else
	{
		if(nOfflineOnline == OFFLINE)
			nMsgNum = STD_MESS_OFFLINE_DECLINED;
		else
			nMsgNum = STD_MESS_ONLINE_DECLINED;

		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(nMsgNum, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}

		ClessSample_Term_Read_Message(nMsgNum, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);

		if ((TPass_GetDeviceType() == TPASS_CLESS_TYPE_IPP2XX) && (!ClessSample_UseGraphicalFunctionOnPPAD())) // Two lines display
			Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);

		if(nVisa == HELPERS_PAYWAVE)
			Helper_Visa_DisplayAvailableAmount(nVisa, pDataStruct, nCardHolderLang);
		
		Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);
	}
}

//! \brief Perform the IHM for Online Processing.
//! \param[in] nVisa : Indicates if it is a payWave or a VisaWave transaction.

void Helper_Visa_OnlineProcessingIHM(const int nVisa, T_SHARED_DATA_STRUCT * pDataStruct, const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang)
{
	MSGinfos tMsg;

	if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(VISAWAVE_MESS_PLEASE_WAIT, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(VISAWAVE_MESS_PLEASE_WAIT, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);

		Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);

		Helper_PerformOnlineSequence();
	}
	else
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(STD_MESS_ONLINE_REQUEST, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(STD_MESS_ONLINE_REQUEST, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);

		if ((TPass_GetDeviceType() == TPASS_CLESS_TYPE_IPP2XX) && (!ClessSample_UseGraphicalFunctionOnPPAD())) // Two lines display
			Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);

		if(nVisa == HELPERS_PAYWAVE)
			Helper_Visa_DisplayAvailableAmount(nVisa, pDataStruct, nCardHolderLang);
		
		Helper_RefreshScreen(WAIT, HELPERS_CUSTOMER_SCREEN);
	}
}

//! \brief Perform the IHM for Transaction that was Terminated.

void Helper_Visa_ErrorIHM(const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang)
{
	MSGinfos tMsg;

	if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_1, &tMsg, LEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION_TERMINATED, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, NOLEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L1, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, NOLEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L2, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_4, &tMsg, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_TRANSACTION_TERMINATED, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L1, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
		ClessSample_Term_Read_Message(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L2, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_4, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);

		Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
		Helper_PerformKOSequence();
	}
	else
	{
		if (ucCustomerDisplayAvailable) // If a customer display is available
		{
			ClessSample_Term_Read_Message(STD_MESS_ERROR, nMerchantLang, &tMsg);
			Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
		}
		ClessSample_Term_Read_Message(STD_MESS_ERROR, nCardHolderLang, &tMsg);
		Helper_DisplayTextCustomer (ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
		Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
		HelperErrorSequence (WITHBEEP);
		Helper_WaitUserDisplay();
	}
}


//! \brief Display Available amount (if available) on customer display if available or on Merchant display else.
//! \param[in] nVisa Indicates if it is a payWave or a VisaWave transaction.
//! \param[in] pDataStruct share buffer with tags informations.
//! \param[in] nCardHolderLang lang to use for the customer. 

void Helper_Visa_DisplayAvailableAmount(int nVisa, T_SHARED_DATA_STRUCT * pDataStruct, int nCardHolderLang)
{
	int nFound;
	unsigned char * pInfo;
	MSGinfos MsgTmp;
	static char ac_SpendingAmount[30];
	unsigned char auCustomerDisplayAvailable;
	MSGinfos tDisplayMsgL1, tDisplayMsgL2;

	if(nVisa == HELPERS_VISAWAVE)
		nFound = ClessSample_Common_RetrieveInfo (pDataStruct, TAG_VISAWAVE_VLP_AVAILABLE_FUNDS, &pInfo);
	else
		nFound = ClessSample_Common_RetrieveInfo (pDataStruct, TAG_PAYWAVE_AVAILABLE_OFFLINE_SPENDING_AMOUNT, &pInfo);
	
	if (nFound)
	{
		memset (ac_SpendingAmount, 0, sizeof(ac_SpendingAmount));

		if(!ClessSample_VisaWave_IsVisaAsiaGuiMode())
			ClessSample_Term_Read_Message(STD_MESS_AVAILABLE, nCardHolderLang, &tDisplayMsgL1);
		else
		{
			ClessSample_Term_Read_Message(VISAWAVE_MESS_OFFLINE_AVAILABLE_FUNDS_L1, nCardHolderLang, &tDisplayMsgL1);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_OFFLINE_AVAILABLE_FUNDS_L2, nCardHolderLang, &tDisplayMsgL2);
		}

		ClessSampleFormatSpendingAmount(pInfo, 6, ac_SpendingAmount);
		MsgTmp.coding  = tDisplayMsgL1.coding;
		MsgTmp.file    = tDisplayMsgL1.file;
		MsgTmp.message = ac_SpendingAmount;
		
		auCustomerDisplayAvailable = Helper_IsClessCustomerDisplayAvailable();
		if(!ClessSample_VisaWave_IsVisaAsiaGuiMode())
		{
			if (auCustomerDisplayAvailable) // If a customer display is available
			{	// Display on customer display
				if ((TPass_GetDeviceType() == TPASS_CLESS_TYPE_IPP2XX) && (!ClessSample_UseGraphicalFunctionOnPPAD())) // Two lines display
				{
					Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_2, &tDisplayMsgL1, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
					Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &MsgTmp, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
				}
				else
				{
					Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_2, &tDisplayMsgL1, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
					Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &MsgTmp, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
				}
			}
			else
			{	// Display on merchant display
				Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tDisplayMsgL1, LEDSOFF);
				Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_4, &MsgTmp, NOLEDSOFF);
			}
		}
		else
		{
			if (auCustomerDisplayAvailable) // If a customer display is available
			{	// Display on customer display
				if ((TPass_GetDeviceType() == TPASS_CLESS_TYPE_IPP2XX) && (!ClessSample_UseGraphicalFunctionOnPPAD())) // Two lines display
				{
					Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_2, &tDisplayMsgL2, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
					Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_4, &MsgTmp, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
				}
				else
				{
					Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tDisplayMsgL1, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
					Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_2, &tDisplayMsgL2, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
					Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_4, &MsgTmp, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
				}
				Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
			}
			else
			{	// Display on merchant display
				Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_1, &tDisplayMsgL1, NOLEDSOFF);
				Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_2, &tDisplayMsgL2, NOLEDSOFF);
				Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_4, &MsgTmp, NOLEDSOFF);
				Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
			}
			Helper_PerformOfflineSequence();
		}
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
   g_tsRemoveCard_task_handle = NULL;     // Init the task handle
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

   g_RemoveCardTaskRunning = FALSE;    // Task is not running

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

