/**
 * \file	CST_UserInterfaceHelpers.c
 * \brief 	Module that manages the user interface.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "CST_Implementation.h"


//// Macros & preprocessor definitions //////////////////////////

#define C_TIME_1S						100


//// Types //////////////////////////////////////////////////////


//// Global variables ///////////////////////////////////////////

//// Static function definitions ////////////////////////////////


//! \brief Create a menu according options.
//! \param[in] nTitle : message number of the Menu
//! \param[in] nDefaultChoice : default choice
//! \param[in] nItems : number of items in the menu
//! \param[in] Items : arrays containing all the menu items
//! \param[in] bUseCguiIconList Indicates if the CGUI icon list shall be used (if available) or not. If not, CGUI list is used instead.
//! \return 0 if ok, error code else.

int HelperDisplayMenu(const int nTitle, int nDefaultChoice, int nItems, const T_CST_HELPER_MENU_ITEM Items[], int bUseCguiIconList)
{
	int lg_code;
	int bRadioButtons = FALSE;
	int nSizeX;
	int nSizeY;
	wStructList Menu;
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
	GetMessageInfos(nTitle, &Menu.MyWindow.title);
	
	for(i = 0; i < nItems; i++)
	{
		GetMessageInfos(Items[i].nMessageId, &Menu.tab[i]);
	}

	wG_List_Entry((void*)&Menu);
	ttestall(ENTRY, 0);
	nResult = Get_Entry(&Entry);

	if (nResult == CR_ENTRY_OK)
		nResult = Entry.d_entry[0];
	else if (nResult == CR_ENTRY_NOK)
		nResult = -2;
	else nResult = -1;

	return nResult;
}


//! \brief This function displays a text on the customer pinpad (if connected).
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] ucLongLine LONGLINE for long line to display.

void _Helper_DisplayTextCustomer(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char ucLongLine)
{
	// Customer display is available only if a pinpad is connected
	if (CST_IsPinpadPresent())
	{
		// Warning, on graphical pinpad, library function must be used for long text

		// Tests if graphical function can be used on pinpad
		if (CST_UseGraphicalFunctionOnPPAD())
		{
			InitContexteGraphique(PERIPH_PPR);
			CST_Term_DisplayGraphicLine(nLineNumber, ptrMSG, nAlignment, nEraseDisplay, ucLongLine); 

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
}


//! \brief This function displays a text on the PinPad or terminal used to input Pin.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLongLine LONG if long line must be displayed.

void _Helper_DisplayPinText(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char bLongLine)
{
    if (CST_IsPinpadPresent()) // If a specific display (different from merchant) is available for PIN information
    {
        if (bLongLine)
            Helper_DisplayTextCustomerLong(nEraseDisplay, nLineNumber, ptrMSG, nAlignment);
        else
            Helper_DisplayTextCustomer(nEraseDisplay, nLineNumber, ptrMSG, nAlignment);
    }
    else // No specific display for PIN information => make it on merchant display
    {
        if (bLongLine)
            Helper_DisplayTextMerchantLong(nEraseDisplay, nLineNumber, ptrMSG);
        else
            Helper_DisplayTextMerchant(nEraseDisplay, nLineNumber, ptrMSG);
    }
}

//! \brief This function displays a text on the terminal screen.
//! \param[in] nNum = message number.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,

void Helper_DisplayMessage(int nNum, int nEraseDisplay, int nLineNumber)
{
	MSGinfos tDisplayMsg;

	GetMessageInfos(nNum, &tDisplayMsg);
	Helper_DisplayTextMerchant(nEraseDisplay, nLineNumber, &tDisplayMsg);
}


//! \brief This function refresh the screen (for WGUI only) and waits for message reading if required.
//! \param[in] bWait \a TRUE if need to wait to read message, \a FALSE if not.

void Helper_RefreshScreen (const unsigned int bWait)
{
	// Check if wait is needed to see message correctly before continuing.
	if (bWait)
		Helper_WaitUserDisplay();
}


//! \brief Display a message on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.

void _Helper_DisplayTextMerchant(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, unsigned char bLongLine)
{
	InitContexteGraphique(PERIPH_DISPLAY);
	CST_Term_DisplayGraphicLine(nLineNumber, ptrMSG, HELPERS_ALIGN_CENTER, (nEraseDisplay ? YESCLEAR : NOCLEAR), bLongLine); 
}


//! \brief Wait allowing user to see screen message.

void Helper_WaitUserDisplay(void)
{
	// To see message before the iddle message
	ttestall(0, 2* C_TIME_1S);
}


//! \brief This function ask a question to the user.
//! \param[in] pMsg User question informations ("Signature OK ?" for example).
//! \param[in] nTimeout Tiemout (in seconds) for user answer (if no answer, default return if \a FALSE).
//! \return
//!		- \a TRUE if user selected "YES".
//!		- \a FALSE if not.

int HelperQuestionYesNo (MSGinfos * pMsg, int nTimeout)
{
	int nResult;
	TAB_ENTRY_FCT TabEntryFct;
	ENTRY_BUFFER Entry;
	int nResultTmp;
	
	// Display the question with "YES" and "NO" for choices
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, pMsg);

	Helper_DisplayMessage(STD_MESS_CHOICE_YES_NO, NO_ERASE, HELPERS_MERCHANT_LINE_4);
	Helper_RefreshScreen(NOWAIT);

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

///////////////////////
// Specific Visa IHM //
///////////////////////

//! \brief Perform the signature CVM IHM.

void Helper_Visa_SignatureCVMIHM(void)
{
	if(CST_VisaWave_IsVisaAsiaGuiMode())
	{
		Helper_DisplayMessage(VISAWAVE_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_DisplayMessage(VISAWAVE_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_MERCHANT_LINE_4);
	}
	else
	{
		Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_MERCHANT_LINE_4);
	}
	Helper_RefreshScreen(NOWAIT);
}


//! \brief Perform the IHM for an approved transaction (either offline or online).
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction

void Helper_Visa_ApprovedIHM(const int nOfflineOnline)
{
	if(CST_VisaWave_IsVisaAsiaGuiMode())
	{
		Helper_DisplayMessage(VISAWAVE_MESS_THANK_YOU, ERASE, HELPERS_MERCHANT_LINE_1);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION, NO_ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION_COMPLETED, NO_ERASE, HELPERS_MERCHANT_LINE_4);
	}
	else
	{
		if(nOfflineOnline == OFFLINE)
			Helper_DisplayMessage(STD_MESS_OFFLINE_APPROVED, ERASE, HELPERS_MERCHANT_LINE_3);
		else
			Helper_DisplayMessage(STD_MESS_ONLINE_APPROVED, ERASE, HELPERS_MERCHANT_LINE_3);					
	}
	Helper_RefreshScreen(NOWAIT);
}


//! \brief Perform the IHM when the Signature CVM is OK.

void Helper_Visa_SignatureOKIHM(void)
{
	Helper_DisplayMessage(STD_MESS_SIGNATURE_CORRECT, ERASE, HELPERS_MERCHANT_LINE_3);
	
	Helper_RefreshScreen(NOWAIT);
}


//! \brief Perform the IHM when the Signature CVM is KO.

void Helper_Visa_SignatureKOIHM(void)
{
	if(CST_VisaWave_IsVisaAsiaGuiMode())
	{
		Helper_DisplayMessage(VISAWAVE_MESS_SIGNATURE_REQUIRED, ERASE, HELPERS_MERCHANT_LINE_2);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION, NO_ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION_NOT_COMPLETED, NO_ERASE, HELPERS_MERCHANT_LINE_4);
	}
	else
	{
		Helper_DisplayMessage(STD_MESS_SIGNATURE_INCORRECT, ERASE, HELPERS_MERCHANT_LINE_3);		
	}
	Helper_RefreshScreen(NOWAIT);
}


//! \brief Perform the IHM when the PIN Entry CVM is KO.

void Helper_Visa_PinEntryKOIHM(const int bPINCanceled)
{
	if(CST_VisaWave_IsVisaAsiaGuiMode())
	{
		Helper_DisplayMessage(VISAWAVE_MESS_PIN_REQUIRED, ERASE, HELPERS_MERCHANT_LINE_2);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION, NO_ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION_NOT_COMPLETED, NO_ERASE, HELPERS_MERCHANT_LINE_4);
	}
	else
	{
		if(bPINCanceled)
			Helper_DisplayMessage(STD_MESS_PIN_CANCEL, ERASE, HELPERS_MERCHANT_LINE_3);
		else
			Helper_DisplayMessage(STD_MESS_PIN_ERROR, ERASE, HELPERS_MERCHANT_LINE_3);
	}
	Helper_RefreshScreen(NOWAIT);
}


//! \brief Perform the IHM for a declined transaction (either offline or online).
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction

void Helper_Visa_DeclinedIHM(const int nOfflineOnline)
{	
	if(CST_VisaWave_IsVisaAsiaGuiMode())
	{
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION, ERASE, HELPERS_MERCHANT_LINE_1);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION_DECLINED, NO_ERASE, HELPERS_MERCHANT_LINE_2);
		Helper_DisplayMessage(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L1, NO_ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_DisplayMessage(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L2, NO_ERASE, HELPERS_MERCHANT_LINE_4);
	}
	else
	{
		if(nOfflineOnline == OFFLINE)
			Helper_DisplayMessage(STD_MESS_OFFLINE_DECLINED, ERASE, HELPERS_MERCHANT_LINE_3);
		else
			Helper_DisplayMessage(STD_MESS_ONLINE_DECLINED, ERASE, HELPERS_MERCHANT_LINE_3);
	}
	Helper_RefreshScreen(NOWAIT);
}


//! \brief Perform the IHM for Online Processing.

void Helper_Visa_OnlineProcessingIHM(void)
{
	if(CST_VisaWave_IsVisaAsiaGuiMode())
		Helper_DisplayMessage(VISAWAVE_MESS_PLEASE_WAIT, ERASE, HELPERS_MERCHANT_LINE_2);
	else
		Helper_DisplayMessage(STD_MESS_ONLINE_REQUEST, ERASE, HELPERS_MERCHANT_LINE_3);

	Helper_RefreshScreen(NOWAIT);
}


//! \brief Perform the IHM for transaction that was terminated.

void Helper_Visa_ErrorIHM(void)
{
	if(CST_VisaWave_IsVisaAsiaGuiMode())
	{
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION, ERASE, HELPERS_MERCHANT_LINE_1);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION_TERMINATED, NO_ERASE, HELPERS_MERCHANT_LINE_2);
		Helper_DisplayMessage(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L1, NO_ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_DisplayMessage(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L2, NO_ERASE, HELPERS_MERCHANT_LINE_4);
	}
	else
	{
		Helper_DisplayMessage(STD_MESS_ERROR, ERASE, HELPERS_MERCHANT_LINE_3);
	}
	Helper_RefreshScreen(NOWAIT);
}
