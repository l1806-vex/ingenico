/**
 * \file	SDSA_UserInterfaceHelpers.c
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

#include "SDSA_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define C_DEFAULT_BEEP_VOLUME			(255)
#define C_DEFAULT_BEEP_DELAY			(50)

#define C_DEFAULT_BEEP_OK_FREQUENCY		(1500)
#define C_DEFAULT_BEEP_ERROR_FREQUENCY	(750)
#define C_DEFAULT_BEEP_OK_DELAY			(50)
#define C_DEFAULT_BEEP_ERROR_DELAY		(20)

#define C_TIME_1S						100
#define C_TIME_100MS					10


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static unsigned long gs_ulAllLedsOnRemoveCardTime;


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static void __Helper_Beep (void);
static void __Helper_BeepBeep (void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief This function displays a text on the cless reader (screen is not refreshed)
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.

void _Helper_DisplayTextCustomer(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char bLedsOff)
{
	int nPeriph;
	int nScreenHeight, nScreenWidth;
	int nFontHeight, nTextLength;
	int x, y;
	char *police;
	int nType; 

	// Turn the LEDs off if necessary
	if (bLedsOff)
		HelperLedsOff();

	// Initialize the graphique context (use the reader screen)
	nPeriph = TPass_GetCustomerDisplay(0, 0);
	InitContexteGraphique(nPeriph);

	// Define the font file to use (if not available, the default manager font is used)
	if(ptrMSG->file ==NULL)
		ptrMSG->file = GetDefaultFONaddress();

	DefCurrentFont(ptrMSG->file);

	// The message is displayed with the 'large' police, in 'proportionnal' mode
	police = _dLARGE_;
	nType = _PROP_WIDTH_;

	// Get the height of the police 
	nFontHeight = GetExtendedPoliceSize(police);
	if (nFontHeight < 0)
	{
        GTL_Traces_TraceDebug("Police not found : %s", police);
		return;
	}
    
	// Get the length of the input text
	if(ptrMSG->coding == _UNICODE_)
		nTextLength = SizeOfUnicodeString((unsigned char*)(ptrMSG->message), police, nType);
	else
		nTextLength = SizeOfISO8859String((unsigned char*)(ptrMSG->message), police, nType);

	// Get the heigth/width of the screen
	GetScreenSize(&nScreenHeight, &nScreenWidth);

	// Calculate the position of the text to be displayed
	y = nFontHeight * nLineNumber;
	x = 0;
			
	switch (nAlignment)
	{
		case (HELPERS_ALIGN_CENTER):
			x = (nScreenWidth - nTextLength) / 2;
			break;
		case (HELPERS_ALIGN_LEFT):
			x = 0;
			break;
		case (HELPERS_ALIGN_RIGHT):
			x = nScreenWidth - nTextLength;
			break;
		default:
			x = 0;
			break;
	}

	// If the text lenght is greater than the screen width it will be truncated
	if (x < 0)
		x = 0;

	// Clear all the screen or only the used line
	if (nEraseDisplay)
		_clrscr();
	else
		_DrawRect(0, y, nScreenWidth, y + nFontHeight, 0, _OFF_, _OFF_);

	// Display the message at the calculated position (x,y)
	_DisplayMSGinfos(x, y, ptrMSG, _OFF_, police, nType);

	// Restore previous configuration 
	InitContexteGraphique(PERIPH_DISPLAY);     
}


//! \brief This function displays a text on the cless reader (screen is refreshed)
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.

void Helper_DisplayTextCustomer(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char bLedsOff)
{

	_Helper_DisplayTextCustomer(nEraseDisplay, nLineNumber, ptrMSG, nAlignment, bLedsOff);
	PaintGraphics();
}


//! \brief This function gets a message and displays it on the cless reader (screen is not refreshed)
//! \param[in] nNum : message number.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.

void _Helper_DisplayMessage(int nNum, int nEraseDisplay, int nLineNumber, int nAlignment, unsigned char bLedsOff)
{
	MSGinfos tDisplayMsg;

	// Get the message number nNum in the messages file
	GetMessageInfos(nNum, &tDisplayMsg);
	// Display the message
	_Helper_DisplayTextCustomer(nEraseDisplay, nLineNumber, &tDisplayMsg, nAlignment, bLedsOff);
}


//! \brief This function gets a message and displays it on the cless reader (screen is refreshed)
//! \param[in] nNum : message number.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.

void Helper_DisplayMessage(int nNum, int nEraseDisplay, int nLineNumber, int nAlignment, unsigned char bLedsOff)
{
	// Add the message in a 'virtual screen'
	_Helper_DisplayMessage(nNum, nEraseDisplay, nLineNumber, nAlignment, bLedsOff);
	// Refresh the screen
	PaintGraphics();
}


//! \brief Process the remove card sequence (buzzer, Leds) and displays the correct message.
//! \param[in] pSharedData Data structure containing the customisation data (step ID, and prefered selected language if present).

void HelperRemoveCardSequence (T_SHARED_DATA_STRUCT * pSharedData)
{
	unsigned long ulBeforeDeselectDisplayTime = 0;
	int nTimeout;
	unsigned char * pLang;


	// Update the transaction status
	SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_CARD_READ);

	ulBeforeDeselectDisplayTime = GTL_StdTimer_GetCurrent();
	
	// Turn on the buzzer
	TPass_Buzzer(C_DEFAULT_BEEP_OK_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME);

	// Turn on the 2nd LED
	if(!SDSA_VisaWave_IsVisaAsiaGuiMode())
		TPass_LedsOn(TPASS_LED_1 | TPASS_LED_2);

	// Initialise the language to use
    if (SDSA_Common_RetreiveInfo (pSharedData, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, &pLang))
		DefCurrentLang((char*)pLang);
			
	// Display the "Remove card" message
	if(!SDSA_VisaWave_IsVisaAsiaGuiMode())
	{
		Helper_DisplayMessage(STD_MESS_REMOVE_CARD, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		
		// Wait before turning on third LED
		if(!SDSA_GuiState_IsQuickGUIModeActivated())
		{
			nTimeout = GTL_StdTimer_GetRemaining(ulBeforeDeselectDisplayTime, 13);
			if (nTimeout > 0)
				ttestall(0, nTimeout);
		}

		// Turn on third LED
		TPass_LedsOn (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3);

		// Wait before turning on fourth LED
		if(!SDSA_GuiState_IsQuickGUIModeActivated())
		{
			nTimeout = GTL_StdTimer_GetRemaining(ulBeforeDeselectDisplayTime, 25);
			if (nTimeout > 0)
				ttestall(0, nTimeout);
		}

		// Turn on fourth LED
		TPass_LedsOn (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);

		// Wait display time
		if(!SDSA_GuiState_IsQuickGUIModeActivated())
		{
			nTimeout = GTL_StdTimer_GetRemaining(ulBeforeDeselectDisplayTime, C_DEFAULT_BEEP_OK_DELAY);
			if (nTimeout > 0)
			{
				ttestall(0, nTimeout);
				nTimeout = 0;
			}
		}
		else
		{
			ttestall(0,5);
		}

		// Turn off buzzer
		TPass_Buzzer (0, 0);

		// Save current timer in order to wait 750ms before turning off all the LEDs
		gs_ulAllLedsOnRemoveCardTime = GTL_StdTimer_GetCurrent();
	}
	else
	{
		_Helper_DisplayMessage(VISAWAVE_MESS_REMOVE_CARD, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(VISAWAVE_MESS_PLEASE_WAIT, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		
		TPass_LedsOnColored (TPASS_LED_GREEN);

		// Wait display time
		nTimeout = GTL_StdTimer_GetRemaining(ulBeforeDeselectDisplayTime, C_DEFAULT_BEEP_OK_DELAY);
		if (nTimeout > 0)
		{
			ttestall(0, nTimeout);
			nTimeout = 0;
		}

		// Turn off buzzer
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

void HelperRepresentCardSequence (T_SHARED_DATA_STRUCT * pSharedData)
{
	unsigned char * pLang;

	// Initialise the language to use
    if (SDSA_Common_RetreiveInfo (pSharedData, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, &pLang))
		DefCurrentLang((char*)pLang);

	// Display the customer message
	Helper_DisplayMessage(STD_MESS_REPRESENT_CARD, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, NOLEDSOFF);	
}


//! \brief Process the error sequence (double beep, leds off).
//! \param[in] nWithBeep = TRUE if beep must be made,

void HelperErrorSequence(int nWithBeep)
{
	gs_ulAllLedsOnRemoveCardTime = 0;

	if (nWithBeep)
	{
		TPass_BuzzerBeep(C_DEFAULT_BEEP_ERROR_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME, C_DEFAULT_BEEP_ERROR_DELAY);
		ttestall (0, C_DEFAULT_BEEP_ERROR_DELAY);
		TPass_BuzzerBeep(C_DEFAULT_BEEP_ERROR_FREQUENCY, (unsigned char)C_DEFAULT_BEEP_VOLUME, C_DEFAULT_BEEP_ERROR_DELAY);
	}

	TPass_LedsOffColored (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4 | 
				   TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_GREEN | TPASS_LED_RED);
}



//! \brief Wait allowing user to see srceen message.

void Helper_WaitUserDisplay(void)
{
	if(SDSA_GuiState_IsQuickGUIModeActivated())
		ttestall (0, C_TIME_100MS);
	else
		// To see message before the iddle message
		ttestall(0, 2* C_TIME_1S);
}


//! \brief This function wait 750ms to see LEDS.

void HelperWaitLedsTime (void)
{
	int nTimeout;

	// If common IHM is not used, blinks the first LED at idle
	nTimeout = GTL_StdTimer_GetRemaining(gs_ulAllLedsOnRemoveCardTime, 75);
	if(!SDSA_GuiState_IsQuickGUIModeActivated())
	{
		if (nTimeout > 0)
			ttestall (0, nTimeout);
	}

	gs_ulAllLedsOnRemoveCardTime = 0;
}


//! \brief Wait 750ms and set LEDS off.

void HelperLedsOff (void)
{
	HelperWaitLedsTime();
	TPass_LedsOffColored (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4 | 
				   TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_GREEN | TPASS_LED_RED);
}


//! \brief This function set the LEDs into the idle state.

void HelperLedsIdleState (void)
{
	HelperWaitLedsTime();
	
	if(SDSA_VisaWave_IsVisaAsiaGuiMode())
	{	
		TPass_LedsOffColored(TPASS_LED_YELLOW | TPASS_LED_GREEN | TPASS_LED_RED);
		TPass_LedsOnColored(TPASS_LED_BLUE);
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


///////////////////////////////////////////////////////////
// SPECIFIC USER INTERFACE FOR VISA PAYWAVE AND VISAWAVE //
///////////////////////////////////////////////////////////


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
	__Helper_Beep();
	ttestall(0,10);
	__Helper_Beep();	
}


//! \brief Third ligth is on and beep beep sound.

void Helper_PerformOKSequence (void)
{
	TPass_LedsOffColored(TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_RED);
	TPass_LedsOnColored(TPASS_LED_GREEN);
	__Helper_BeepBeep();
	ttestall(0,500);
}


//! \brief Fourth ligth blinking and beep beep sound.

void Helper_PerformKOSequence (void)
{
	TPass_LedsOffColored(TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_GREEN);
	TPass_LedsBlinkColored(TPASS_LED_RED, VISA_ASIA_LED_BLINK_ON, VISA_ASIA_LED_BLINK_OFF);
	__Helper_BeepBeep();
	ttestall(0,300);
}


//! \brief Third ligth blinking and beep sound.

void Helper_PerformOfflineSequence (void)
{
	TPass_LedsOffColored(TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_RED);
	TPass_LedsBlinkColored(TPASS_LED_GREEN, VISA_ASIA_LED_BLINK_ON, VISA_ASIA_LED_BLINK_OFF);
	__Helper_Beep();
	ttestall(0,500);
}


//! \brief Third ligth blinking.

void Helper_PerformOnlineSequence (void)
{
	TPass_LedsOffColored(TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_RED);
	TPass_LedsBlinkColored(TPASS_LED_GREEN, VISA_ASIA_LED_BLINK_ON, VISA_ASIA_LED_BLINK_OFF);
}


//! \brief Third ligth blinking and beep sound.

void Helper_PerformCVMSequence (void)
{
	TPass_LedsOffColored(TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_RED);
	TPass_LedsBlinkColored(TPASS_LED_GREEN, VISA_ASIA_LED_BLINK_ON, VISA_ASIA_LED_BLINK_OFF);
	__Helper_Beep();
}


//! \brief Perform the signature CVM IHM.

void Helper_Visa_SignatureCVMIHM(void)
{
	if(SDSA_VisaWave_IsVisaAsiaGuiMode())
	{
		Helper_PerformCVMSequence();

		_Helper_DisplayMessage(VISAWAVE_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_DisplayMessage(VISAWAVE_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
	}
	else
	{
		_Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_WaitUserDisplay();
	}
}

//! \brief Perform the IHM for an approved transaction (either offline or online).
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction
//! \param[in] nAOSA : with Available Offline Spending Amount : WITH_AOSA or WITHOUT_AOSA

void Helper_Visa_ApprovedIHM(const int nOfflineOnline,const int nAOSA)
{
	int nMsgNum;

	if(SDSA_VisaWave_IsVisaAsiaGuiMode())
	{
		_Helper_DisplayMessage(VISAWAVE_MESS_THANK_YOU, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		_Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION_COMPLETED, NO_ERASE, HELPERS_CUSTOMER_LINE_4, HELPERS_ALIGN_CENTER, NOLEDSOFF);

		Helper_PerformOKSequence();
	}
	else
	{
		if(nOfflineOnline == OFFLINE)
			nMsgNum =STD_MESS_OFFLINE_APPROVED;
		else
			nMsgNum =STD_MESS_ONLINE_APPROVED;
		
		Helper_DisplayMessage(nMsgNum, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		
		if (nAOSA == WITH_AOSA)
			Helper_Visa_DisplayAvailableAmount();
		
		Helper_WaitUserDisplay();
	}
}


//! \brief Perform the IHM when the Signature CVM is OK.

void Helper_Visa_SignatureOKIHM(void)
{
	if(SDSA_VisaWave_IsVisaAsiaGuiMode())
	{
		_Helper_DisplayMessage(VISAWAVE_MESS_THANK_YOU, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		_Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION_COMPLETED, NO_ERASE, HELPERS_CUSTOMER_LINE_4, HELPERS_ALIGN_CENTER, NOLEDSOFF);

		Helper_PerformOKSequence();
	}
	else
	{
		Helper_DisplayMessage(STD_MESS_APPROVED, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);

		// Display Available amount
		Helper_Visa_DisplayAvailableAmount();

		Helper_WaitUserDisplay();
	}
}


//! \brief Perform the IHM when the Signature CVM is KO.

void Helper_Visa_SignatureKOIHM(void)
{
	if(SDSA_VisaWave_IsVisaAsiaGuiMode())
	{
		_Helper_DisplayMessage(VISAWAVE_MESS_SIGNATURE_REQUIRED, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		_Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION, NO_ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION_NOT_COMPLETED, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);

		Helper_PerformKOSequence();
	}
	else
	{
		Helper_DisplayMessage(STD_MESS_OFFLINE_DECLINED, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);

		// Display Available amount
		Helper_Visa_DisplayAvailableAmount();
		Helper_WaitUserDisplay();
	}
}


//! \brief Perform the IHM when the PIN Entry CVM is KO.

void Helper_Visa_PinEntryKOIHM(const int bPINCanceled)
{
	MSGinfos tMsg;

	if(SDSA_VisaWave_IsVisaAsiaGuiMode())
	{
		_Helper_DisplayMessage(VISAWAVE_MESS_PIN_REQUIRED, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		_Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION, NO_ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION_NOT_COMPLETED, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);

		Helper_PerformKOSequence();
	}
	else
	{
		if(bPINCanceled)
			GetMessageInfos(STD_MESS_PIN_CANCEL, &tMsg);
		else
			GetMessageInfos(STD_MESS_PIN_ERROR, &tMsg);

		Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();
	}
}


//! \brief Perform the IHM for a declined transaction (either offline or online).
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction
//! \param[in] nAOSA : with Available Offline Spending Amount : WITH_AOSA or WITHOUT_AOSA

void Helper_Visa_DeclinedIHM(const int nOfflineOnline,const int nAOSA)
{
	int nMsgNum;
	
	if(SDSA_VisaWave_IsVisaAsiaGuiMode())
	{
		_Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		_Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION_DECLINED, NO_ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		_Helper_DisplayMessage(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L1, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_DisplayMessage(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_4, HELPERS_ALIGN_CENTER, NOLEDSOFF);

		Helper_PerformKOSequence();
	}
	else
	{
		if(nOfflineOnline == OFFLINE)
			nMsgNum = STD_MESS_OFFLINE_DECLINED;
		else
			nMsgNum = STD_MESS_ONLINE_DECLINED;

		Helper_DisplayMessage(nMsgNum, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);

		if(nAOSA == WITH_AOSA)
			Helper_Visa_DisplayAvailableAmount();
		
		Helper_WaitUserDisplay();
	}
}


//! \brief Perform the IHM for Online Processing.
//! \param[in] nAOSA : with Available Offline Spending Amount : WITH_AOSA or WITHOUT_AOSA

void Helper_Visa_OnlineProcessingIHM(const int nAOSA)
{
	if(SDSA_VisaWave_IsVisaAsiaGuiMode())
	{
		Helper_DisplayMessage(VISAWAVE_MESS_PLEASE_WAIT, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_PerformOnlineSequence();
	}
	else
	{
		Helper_DisplayMessage(STD_MESS_ONLINE_REQUEST, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);

		if(nAOSA == WITH_AOSA)
			Helper_Visa_DisplayAvailableAmount();
		
		Helper_WaitUserDisplay();
	}
}


//! \brief Perform the IHM for Transaction that was Terminated.

void Helper_Visa_ErrorIHM(void)
{
	if(SDSA_VisaWave_IsVisaAsiaGuiMode())
	{
		_Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		_Helper_DisplayMessage(VISAWAVE_MESS_TRANSACTION_TERMINATED, NO_ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		_Helper_DisplayMessage(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L1, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_DisplayMessage(VISAWAVE_MESS_USE_OTHER_VISA_CARD_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_4, HELPERS_ALIGN_CENTER, NOLEDSOFF);

		Helper_PerformKOSequence();
	}
	else
	{
		Helper_DisplayMessage(STD_MESS_ERROR, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		HelperErrorSequence (WITHBEEP);
		Helper_WaitUserDisplay();
	}
}


//! \brief Display Available amount (if available) on customer display.

void Helper_Visa_DisplayAvailableAmount(void)
{
	const T_PAYMENT_DATA_STRUCT * pTransactionData;
	static char auc_SpendingAmount[30];
	MSGinfos tDisplayMsgL1, tDisplayMsgL2;
	MSGinfos MsgTmp;
	unsigned char ucFormat, ucPosition;
	
	// Get the global transaction data
	pTransactionData = SDSA_Fill_GetTransactionDataStructure();

	if (pTransactionData->bIsAvailableAmountPresent)
	{
		if(!SDSA_VisaWave_IsVisaAsiaGuiMode())
			GetMessageInfos(STD_MESS_AVAILABLE, &tDisplayMsgL1);
		else
		{
			GetMessageInfos(VISAWAVE_MESS_OFFLINE_AVAILABLE_FUNDS_L1, &tDisplayMsgL1);
			GetMessageInfos(VISAWAVE_MESS_OFFLINE_AVAILABLE_FUNDS_L2, &tDisplayMsgL2);
		}

		memset (auc_SpendingAmount, 0, sizeof(auc_SpendingAmount));
		// Retrieve the format of the money (currency position, separator, ...)
		Helper_GetCurrencyFormatFromParameters(SDSA_Fill_GiveMoneyLabel(),&ucFormat,&ucPosition);
		// Create a message that contains the amount, the currency ...
		SDSA_Common_FormatAmount(ucFormat, SDSA_Fill_GiveMoneyLabel(), ucPosition, pTransactionData->ulAvailableAmount, auc_SpendingAmount);
		MsgTmp.coding  = tDisplayMsgL1.coding;
		MsgTmp.file    = tDisplayMsgL1.file;
		MsgTmp.message = auc_SpendingAmount;
		
		// Display messages
		if(!SDSA_VisaWave_IsVisaAsiaGuiMode())
		{
			_Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_2, &tDisplayMsgL1, HELPERS_ALIGN_CENTER, LEDSOFF);
			Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &MsgTmp, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		}
		else
		{
			_Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tDisplayMsgL1, HELPERS_ALIGN_CENTER, NOLEDSOFF);
			_Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_2, &tDisplayMsgL2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
			Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_4, &MsgTmp, HELPERS_ALIGN_CENTER, NOLEDSOFF);
			Helper_PerformOfflineSequence();
		}
	}
}


//! \brief This function get the format and the currency position from the parameters to display the amount.
//! \param[in] pCurrencyLabel Currency label to find in the parameter file.
//! \param[out] pFormat Format of the displayed amount.
//! \param[out] pPosition Position of the currency (before or after the amount).
//!	\return
//!	- \a TRUE if format to display is found.
//!	- \a FALSE indicate an invalid parameter as the currency label provided is unknown from the application.

int Helper_GetCurrencyFormatFromParameters(unsigned char *pCurrencyLabel, unsigned char *pFormat,unsigned char *pPosition)
{
	int n_NbMoney;
	S_MONEY_EXTENDED * ps_x_Money;
	int i;
	unsigned char ucExponent;
	unsigned char ucCents;			// character used to separate the cents
    unsigned char ucThousands;		// character used to separate the thousands

	// Set the default format
	*pFormat = 0;	// 0 ==> 1.000,00 
	*pPosition = CURRENCY_AFTER_AMOUNT;	// 0 ==> currency displayed after the amount

	// Get the list of supported money
	SDSA_Parameters_GetMoneyExtended(&n_NbMoney, &ps_x_Money);

	// Try to find the requested money 
	for(i=0; i<n_NbMoney; i++)
	{
		if(memcmp(ps_x_Money[i].currency.nom, pCurrencyLabel, 3) == 0)
		{
			// Currency label found in the parameter file, get the format and the position
			
			if(ps_x_Money[i].infos.currency_position == CURRENCY_BEFORE_AMOUNT)
				*pPosition = CURRENCY_BEFORE_AMOUNT;
			else
				*pPosition = CURRENCY_AFTER_AMOUNT;
			
			ucCents = ps_x_Money[i].infos.cents_separator;
			ucThousands = ps_x_Money[i].infos.thousands_separator;
			ucExponent = ps_x_Money[i].currency.posdec;

			if ((ucCents == ',') && (ucThousands == '.') && (ucExponent == 2))
				*pFormat = 0;
			else if ((ucCents == '.') && (ucThousands == ',') && (ucExponent == 2))
				*pFormat = 1;
			else if ((ucCents == ',') && (ucThousands == ' ') && (ucExponent == 2))
				*pFormat = 2;
			else if ((ucCents == ' ') && (ucThousands == '.') && (ucExponent == 0))
				*pFormat = 3;
			else if ((ucCents == ' ') && (ucThousands == ',') && (ucExponent == 0))
				*pFormat = 4;
			else if ((ucCents == ' ') && (ucThousands == ' ') && (ucExponent == 0))
				*pFormat = 5;
			else if ((ucCents == ',') && (ucThousands == '.') && (ucExponent == 3))
				*pFormat = 6;
			else if ((ucCents == '.') && (ucThousands == ',') && (ucExponent == 3))
				*pFormat = 7;
			else if ((ucCents == ',') && (ucThousands == ' ') && (ucExponent == 3))
				*pFormat = 8;
			else
				*pFormat = 0;

			return (TRUE);
		}
	}

	return (FALSE);
}
