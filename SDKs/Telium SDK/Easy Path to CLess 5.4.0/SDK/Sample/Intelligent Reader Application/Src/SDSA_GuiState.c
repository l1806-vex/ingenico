/**
 * \file	SDSA_GuiState.c
 * \brief 	Gui state management functions.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2010 Ingenico, rue claude Chappe,\n
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

#define LENGTH_OF_GUI_STATE_TO_SET			4		/*!< Length of the tag that contains the GUI state to be set */


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

static int gs_bIsQuickGuiMode = FALSE;				// Set to TRUE if the quick GUI must be used.


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////



//! \brief Check in the parameter file if the quick GUI mode is activated or not (if yes the GUI time will be minimized).

void SDSA_GuiState_SetQuickGUIMode (void)
{
	TLV_TREE_NODE pGuiMode;
	unsigned char * pValue;
	unsigned int nDataLength;
	
	pValue = NULL;
	nDataLength = 0;

	pGuiMode = TlvTree_Find(pTreeCurrentParam, TAG_SDSA_QUICK_GUI_MODE, 0);

	if (pGuiMode != NULL)
	{
		pValue = TlvTree_GetData(pGuiMode);
		nDataLength = TlvTree_GetLength(pGuiMode);
	}

	if ((pValue != NULL) && (nDataLength != 0))
	{
		if (pValue[0] != 0)
		{
			gs_bIsQuickGuiMode = TRUE;
			return;
		}
	}

	gs_bIsQuickGuiMode = FALSE;
}

//! \brief Check if the quick GUI mode is activated or not (if yes the GUI time will be minimized).
//!	\return
//!		- TRUE if quick GUI mode is used.
//!		- FALSE else.

int SDSA_GuiState_IsQuickGUIModeActivated (void)
{
	return (gs_bIsQuickGuiMode);
}


//! \brief Set the application language with the manager language.

void SDSA_UserInterface_SetMerchantLanguage (void)
{
	char *pManagerLanguage;
	char ucLanguage[3];

	pManagerLanguage = GetManagerLanguage();
	
	memset(ucLanguage, 0, sizeof(ucLanguage));
	ucLanguage[0] = GTL_Convert_LowerCase(pManagerLanguage[0]);
	ucLanguage[1] = GTL_Convert_LowerCase(pManagerLanguage[1]);
	
	DefCurrentLang(ucLanguage);
}



//! \brief Set the application language with the cardholder language if present, else with the merchant language.
//! \param[in] nKernelIdentifier Kernel identifier that will be called to get the cardholder language.

void SDSA_UserInterface_SetCardholderLanguage (const int nKernelIdentifier)
{
	int ret;
	T_SHARED_DATA_STRUCT * pStruct;
	unsigned char * pInfo;
	
	// By default, application language is the same as the merchant language
	SDSA_UserInterface_SetMerchantLanguage();

	// Init a shared buffer to get the prefered selected language
	pStruct = GTL_SharedExchange_InitShared (128);

	if (pStruct == NULL)
	{
		// An error occured when creating the shared buffer
		GTL_Traces_TraceDebug ("SDSA_UserInterface_SetCardholderLanguage : An error occured when creating the shared buffer");
		goto End;
	}	

	// Add tag in the shared buffer to request it
	ret = GTL_SharedExchange_AddTag (pStruct, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, 0, NULL);

	if (ret != STATUS_SHARED_EXCHANGE_OK)
	{
		// An error occured when adding the TAG_KERNEL_SELECTED_PREFERED_LANGUAGE tag in the structure
		GTL_Traces_TraceDebug ("SDSA_UserInterface_SetCardholderLanguage : An error occured when adding the TAG_KERNEL_SELECTED_PREFERED_LANGUAGE tag in the structure (ret = %02x)", ret);
		goto End;
	}	

	// Request data to the kernel
	switch (nKernelIdentifier)
	{
	case SDSA_KERNEL_IDENTIFIER_PAYPASS :
		ret = PayPass_GetData(pStruct);
		break;

	case SDSA_KERNEL_IDENTIFIER_PAYWAVE :
		ret = payWave_GetData(pStruct);
		break;

	case SDSA_KERNEL_IDENTIFIER_VISAWAVE :
		ret = VisaWave_GetData(pStruct);
		break;

	case SDSA_KERNEL_IDENTIFIER_EXPRESSPAY :
		ret = ExpressPay3_GetData(pStruct);
		break;

	case SDSA_KERNEL_IDENTIFIER_INTERAC :
		ret = Interac_GetData(pStruct);
		break;

	case SDSA_KERNEL_IDENTIFIER_DISCOVER :
		ret = Discover_GetData(pStruct);
		break;

	default:
		ret = KERNEL_STATUS_UNKNOWN;
		GTL_Traces_TraceDebug("SDSA_UserInterface_SetCardholderLanguage : Unknown value for kernel identifier parameter : %x", nKernelIdentifier);
		goto End;
		break;
	}

	if (ret != KERNEL_STATUS_OK)
	{		
		// An error occured when getting data from the kernel
		GTL_Traces_TraceDebug ("SDSA_UserInterface_SetCardholderLanguage : An error occured when getting data from the kernel (ret = %02x)", ret);
			goto End;
	}

	// Search the tag in the kernel response structure
	if (SDSA_Common_RetreiveInfo (pStruct, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, &pInfo))
		DefCurrentLang((char*)pInfo);
	
End:
	// Destroy the shared buffer if created
	if (pStruct != NULL)
		GTL_SharedExchange_DestroyShare (pStruct);
}



//!	\brief Get the screen to be displayed.
//!	\param[in] hInputTlvTree TLV-Tree containing the data to display the screen.
//!	\return
//!	- \a TRUE if correctly performed.
//!	- \a FALSE if an error occured (invalid data has been provided).

static int __SDSA_UserInterface_GetScreenToDisplay (TLV_TREE_NODE hInputTlvTree, unsigned long * pScreenToDisplay)
{
	unsigned int nReadTag, nReadLength;
	int nResult = TRUE;
	TLV_TREE_NODE hCurrentNode;
	unsigned long ulTemp;


	// Get the first node
	hCurrentNode = TlvTree_GetFirstChild (hInputTlvTree);
	*pScreenToDisplay = 0;

	while (hCurrentNode != NULL)
	{
		// Get the node tag
		nReadTag = TlvTree_GetTag (hCurrentNode);

		switch (nReadTag)
		{
		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_SDSA_GUI_STATE_TO_SET):
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if (nReadLength == LENGTH_OF_GUI_STATE_TO_SET)
			{
				// Tag is correctly provided
				GTL_Convert_BinNumberToUl (TlvTree_GetData(hCurrentNode), &ulTemp, LENGTH_OF_GUI_STATE_TO_SET);
				* pScreenToDisplay = ulTemp;
				goto End; // End processing as the tag has been founded
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////
		default:
			GTL_Traces_TraceDebug ("Unexpected tag, ignore it (%02x)", nReadTag);
			break;
		}

		// Get the next node
		hCurrentNode = TlvTree_GetNext (hCurrentNode);
	}

End:
	return (nResult);
}



//! \brief Function called to display a defined screen.
//! \param[in] hInputTlvTree Contains the identifier of the screen to be displayed.
//! \return
//!	- \ref SDI_STATUS_OK if the screen correctly displayed.
//!	- \ref SDI_STATUS_INVALID_DATA if provided parameters are not valid.
//!	- \ref SDI_STATUS_MISSING_DATA if there is a missing mandatory parameter (identifier of the screen to be displayed).

int SDSA_GuiState_SetGuiState (const TLV_TREE_NODE hInputTlvTree)
{
	int nResult;
	unsigned long ulScreenToDisplay;

	nResult = SDI_STATUS_UNKNOWN;

	// Get the screen to be displayed
	if (!__SDSA_UserInterface_GetScreenToDisplay (hInputTlvTree, &ulScreenToDisplay))
	{
		// An error occured when getting the screen to display value
		GTL_Traces_TraceDebug ("SDSA_DisplayScreen : An error occured when extracting the screen to display");
		nResult = SDI_STATUS_MISSING_DATA;
		goto End;
	}

	// Display the screen
	nResult = SDSA_GuiState_DisplayScreen (ulScreenToDisplay);

End:
	return (nResult);
}



//! \brief This function set the GUI state of the intelligent reader (displays a screen, sets leds...).
//! \param[in] ulScreenIdentifier Screen identifier.
//! \return
//!	- \ref SDI_STATUS_OK if correctly performed.
//!	- \ref SDI_STATUS_INVALID_PARAMETER if \a ulScreenIdentifier is unknown.

int SDSA_GuiState_DisplayScreen (unsigned long ulScreenIdentifier)
{
	int nResult = SDI_STATUS_OK;
	const T_PAYMENT_DATA_STRUCT * pTransactionData;
	MSGinfos tDisplayMsg;
	char ucFormattedAmountMessage[32];
	unsigned char ucFormat, ucPosition;

	// By default, application language is the same as the merchant language
	SDSA_UserInterface_SetMerchantLanguage();

	// Get the global transaction data
	pTransactionData = SDSA_Fill_GetTransactionDataStructure();

	// Display the screen
	switch (ulScreenIdentifier)
	{
	case (SDSA_SCREEN_IDLE):
		Helper_DisplayMessage(STD_MESS_READY, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		// Set the LEDs into the idle state
		HelperLedsIdleState();
		break;

	case (SDSA_SCREEN_PRESENT_CARD):
		if (pTransactionData->bIsAmountPresent)
		{
			// Format the message that contains the amount, the currency according to ucFormat, ucPosition
			memset (ucFormattedAmountMessage, 0, sizeof(ucFormattedAmountMessage));
			Helper_GetCurrencyFormatFromParameters(SDSA_Fill_GiveMoneyLabel(),&ucFormat,&ucPosition);
			SDSA_Common_FormatAmount(ucFormat, SDSA_Fill_GiveMoneyLabel(), ucPosition, pTransactionData->ulTransactionAmountBin, ucFormattedAmountMessage);
			InitMSGinfos_message(&tDisplayMsg, (char*)ucFormattedAmountMessage);
			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tDisplayMsg, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		}

		// Get the STD_MESS_PRESENT_CARD message and display it
		Helper_DisplayMessage(STD_MESS_PRESENT_CARD, NO_ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		break;

	case (SDSA_SCREEN_RETRY):
		if (pTransactionData->bIsAmountPresent)
		{
			// Format the message that contains the amount, the currency according to ucFormat, ucPosition
			memset (ucFormattedAmountMessage, 0, sizeof(ucFormattedAmountMessage));
			Helper_GetCurrencyFormatFromParameters(SDSA_Fill_GiveMoneyLabel(), &ucFormat, &ucPosition);
			SDSA_Common_FormatAmount(ucFormat, SDSA_Fill_GiveMoneyLabel(), ucPosition, pTransactionData->ulTransactionAmountBin, ucFormattedAmountMessage);
			InitMSGinfos_message(&tDisplayMsg, (char*)ucFormattedAmountMessage);
			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tDisplayMsg, HELPERS_ALIGN_CENTER, LEDSOFF);
		}

		// Get the STD_MESS_TRY_AGAIN message and display it
		Helper_DisplayMessage(STD_MESS_TRY_AGAIN, NO_ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		break;

	case (SDSA_SCREEN_USE_CONTACT):
		Helper_DisplayMessage(STD_MESS_INSERT_OR_SWIPE, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		HelperErrorSequence (WITHBEEP);
		Helper_WaitUserDisplay();
		// Set the LEDs into the idle state
		HelperLedsIdleState();
		break;

	case (SDSA_SCREEN_REMOVE_CARD):
		Helper_DisplayMessage(STD_MESS_REMOVE_CARD, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		TPass_LedsBlink (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4, 125, 125);
		break;

	case (SDSA_SCREEN_TIMEOUT_ELAPSED):
		break;
	case (SDSA_SCREEN_CANCELLED):
		break;
	case (SDSA_SCREEN_PROCESSING):
		break;
	case (SDSA_SCREEN_COLLISION):
		_Helper_DisplayMessage(STD_MESS_COLLISION_LINE_1, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(STD_MESS_COLLISION_LINE_2, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		HelperErrorSequence (WITHBEEP);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_SCREEN_OFFLINE_APPROVED):
		Helper_DisplayMessage(STD_MESS_APPROVED, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_SCREEN_ONLINE_APPROVED):
		Helper_DisplayMessage(STD_MESS_ONLINE_APPROVED, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_SCREEN_OFFLINE_DECLINED):
		Helper_DisplayMessage(STD_MESS_OFFLINE_DECLINED, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_SCREEN_ONLINE_DECLINED):
		Helper_DisplayMessage(STD_MESS_ONLINE_DECLINED, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_SCREEN_ONLINE_PIN_REQUIRED):
		break;
	
	case (SDSA_SCREEN_SIGNATURE_REQUIRED):
		_Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_SCREEN_CARD_NOT_SUPPORTED):
		Helper_DisplayMessage(STD_MESS_CARD_NOT_SUPPORTED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		HelperErrorSequence (WITHBEEP);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_SCREEN_DISCONNECTED):
		Helper_DisplayMessage(STD_MESS_DISCONNECTED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		break;
		
	case (SDSA_SCREEN_CONNECTED):
		Helper_DisplayMessage(STD_MESS_CONNECTED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		// Set the LEDs into the idle state
		HelperLedsIdleState();
		break;

//////////////////////////////
// PAYWAVE SPECIFIC SCREENS //
//////////////////////////////

	case (SDSA_PAYWAVE_SCREEN_STATUS_ERROR):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_DisplayMessage(STD_MESS_ERROR_STATUS, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		if(!SDSA_VisaWave_IsVisaAsiaGuiMode())
		{
			HelperErrorSequence (WITHBEEP);
			Helper_WaitUserDisplay();
		}
		else
		{
			Helper_PerformKOSequence();
		}
		break;

	case (SDSA_PAYWAVE_SCREEN_OFFLINE_APPROVED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_ApprovedIHM(OFFLINE, WITH_AOSA);
		break;

	case (SDSA_PAYWAVE_SCREEN_OFFLINE_DECLINED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_DeclinedIHM(OFFLINE, WITH_AOSA);
		break;

	case (SDSA_PAYWAVE_SCREEN_SIGNATURE_REQUIRED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_SignatureCVMIHM();
		break;

	case (SDSA_PAYWAVE_SCREEN_SIGNATURE_OK):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_SignatureOKIHM();
		break;

	case (SDSA_PAYWAVE_SCREEN_SIGNATURE_KO):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_SignatureKOIHM();
		break;

	case (SDSA_PAYWAVE_SCREEN_ONLINE_APPROVED_WITH_AOSA):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_ApprovedIHM(ONLINE, WITH_AOSA);
		break;

	case (SDSA_PAYWAVE_SCREEN_ONLINE_APPROVED_WITHOUT_AOSA):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_ApprovedIHM(ONLINE, WITHOUT_AOSA);
		break;

	case (SDSA_PAYWAVE_SCREEN_ONLINE_DECLINED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_DeclinedIHM(ONLINE, WITH_AOSA);
		break;
		
	case (SDSA_PAYWAVE_SCREEN_ONLINE_PROCESSING):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_OnlineProcessingIHM(WITH_AOSA);
		break;

	case (SDSA_PAYWAVE_SCREEN_PIN_KO):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_PinEntryKOIHM(FALSE);
		break;
		
	case (SDSA_PAYWAVE_SCREEN_PIN_CANCELED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_PinEntryKOIHM(TRUE);
		break;

	case (SDSA_PAYWAVE_SCREEN_PHONE_INSTRUCTIONS):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_DisplayMessage(STD_MESS_PHONE_INSTRUCTIONS_L1, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(STD_MESS_PHONE_INSTRUCTIONS_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		if(!SDSA_VisaWave_IsVisaAsiaGuiMode())
		{
			// After a duration of between 1000ms and 1500ms, the reader shall power up the contactless interface
			HelperErrorSequence(WITHBEEP); // Duration : 600 ms
			ttestall(0, 50); // Duration : 500 ms
		}
		else
		{
			Helper_PerformKOSequence();
		}
		break;

	case (SDSA_PAYWAVE_SCREEN_ERROR):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		Helper_Visa_ErrorIHM();
		break;

///////////////////////////////
// VISAWAVE SPECIFIC SCREENS //
///////////////////////////////

	case (SDSA_VISAWAVE_SCREEN_STATUS_ERROR):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_DisplayMessage(STD_MESS_ERROR_STATUS, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
		if(!SDSA_VisaWave_IsVisaAsiaGuiMode())
		{
			HelperErrorSequence (WITHBEEP);
			Helper_WaitUserDisplay();
		}
		else
		{
			Helper_PerformKOSequence();
		}
		break;

	case (SDSA_VISAWAVE_SCREEN_OFFLINE_APPROVED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_Visa_ApprovedIHM(OFFLINE, WITH_AOSA);
		break;

	case (SDSA_VISAWAVE_SCREEN_OFFLINE_DECLINED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_Visa_DeclinedIHM(OFFLINE, WITHOUT_AOSA);
		break;
	
	case (SDSA_VISAWAVE_SCREEN_SIGNATURE_REQUIRED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_Visa_SignatureCVMIHM();
		break;
	
	case (SDSA_VISAWAVE_SCREEN_SIGNATURE_OK):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_Visa_SignatureOKIHM();
		break;

	case (SDSA_VISAWAVE_SCREEN_SIGNATURE_KO):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_Visa_SignatureKOIHM();
		break;
	
	case (SDSA_VISAWAVE_SCREEN_ONLINE_APPROVED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_Visa_ApprovedIHM(ONLINE, WITHOUT_AOSA);
		break;
	
	case (SDSA_VISAWAVE_SCREEN_ONLINE_DECLINED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_Visa_DeclinedIHM(ONLINE, WITHOUT_AOSA);
		break;

	case (SDSA_VISAWAVE_SCREEN_ONLINE_PROCESSING):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_Visa_OnlineProcessingIHM(WITHOUT_AOSA);
		break;

	case (SDSA_VISAWAVE_SCREEN_PIN_KO):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_Visa_PinEntryKOIHM(FALSE);
		break;

	case (SDSA_VISAWAVE_SCREEN_ERROR):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_Visa_ErrorIHM();
		break;

	case (SDSA_VISAWAVE_SCREEN_RETRY):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_DisplayMessage(VISAWAVE_MESS_TRY_AGAIN, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_PerformKOSequence();
		break;

	case (SDSA_VISAWAVE_SCREEN_COLLISION):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		_Helper_DisplayMessage(VISAWAVE_MESS_SELECT_ONE_CARD_L1, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_DisplayMessage(VISAWAVE_MESS_SELECT_ONE_CARD_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_PerformKOSequence();
		break;

	case (SDSA_VISAWAVE_SCREEN_USE_CONTACT):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_VISAWAVE);
		Helper_DisplayMessage(STD_MESS_INSERT_OR_SWIPE, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_PerformKOSequence();
		break;

//////////////////////////////
// PAYPASS SPECIFIC SCREENS //
//////////////////////////////

	case (SDSA_PAYPASS_SCREEN_APPROVED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		Helper_DisplayMessage(STD_MESS_APPROVED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_PAYPASS_SCREEN_OFFLINE_APPROVED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		Helper_DisplayMessage(STD_MESS_OFFLINE_APPROVED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_PAYPASS_SCREEN_OFFLINE_DECLINED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		Helper_DisplayMessage(STD_MESS_OFFLINE_DECLINED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_PAYPASS_SCREEN_ONLINE_PROCESSING):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		Helper_DisplayMessage(STD_MESS_ONLINE_REQUEST, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_PAYPASS_SCREEN_ONLINE_APPROVED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		Helper_DisplayMessage(STD_MESS_ONLINE_APPROVED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();								
		break;

	case (SDSA_PAYPASS_SCREEN_ONLINE_DECLINED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		Helper_DisplayMessage(STD_MESS_ONLINE_DECLINED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();								
		break;

	case (SDSA_PAYPASS_SCREEN_SIGNATURE_REQUIRED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		_Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_PAYPASS_SCREEN_CARD_BLOCKED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		Helper_DisplayMessage(STD_MESS_CARD_BLOCKED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		HelperErrorSequence (WITHOUTBEEP);
		Helper_WaitUserDisplay();								
		break;

	case (SDSA_PAYPASS_SCREEN_APPLICATION_BLOCKED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		Helper_DisplayMessage(STD_MESS_APPLICATION_BLOCKED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		HelperErrorSequence (WITHOUTBEEP);
		Helper_WaitUserDisplay();								
		break;

	case (SDSA_PAYPASS_SCREEN_OFFLINE_APPROVED_REFUND):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		_Helper_DisplayMessage(STD_MESS_REFUND, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(STD_MESS_APPROVED, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_PAYPASS_SCREEN_ERROR_REFUND):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		_Helper_DisplayMessage(STD_MESS_REFUND, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(STD_MESS_FAILED, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_WaitUserDisplay();								
		break;

	case (SDSA_PAYPASS_SCREEN_ERROR):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);
		Helper_DisplayMessage(STD_MESS_ERROR, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		HelperErrorSequence(WITHOUTBEEP);
		Helper_WaitUserDisplay();								
		break;

/////////////////////////////////
// EXPRESSPAY SPECIFIC SCREENS //
/////////////////////////////////

	case (SDSA_EXPRESSPAY_SCREEN_OFFLINE_APPROVED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);
		Helper_DisplayMessage(STD_MESS_OFFLINE_APPROVED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();
		break;
	
	case (SDSA_EXPRESSPAY_SCREEN_OFFLINE_DECLINED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);
		Helper_DisplayMessage(STD_MESS_OFFLINE_DECLINED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();
		break;

	case (SDSA_EXPRESSPAY_SCREEN_ONLINE_PROCESSING):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);
		Helper_DisplayMessage(STD_MESS_ONLINE_REQUEST, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		break;			

	case (SDSA_EXPRESSPAY_SCREEN_ONLINE_APPROVED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);
		Helper_DisplayMessage(STD_MESS_ONLINE_APPROVED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();								
		break;

	case (SDSA_EXPRESSPAY_SCREEN_ONLINE_DECLINED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);
		Helper_DisplayMessage(STD_MESS_ONLINE_DECLINED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();								
		break;

	case (SDSA_EXPRESSPAY_SCREEN_ERROR):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);
		Helper_DisplayMessage(STD_MESS_ERROR, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		HelperErrorSequence(WITHBEEP);
		Helper_WaitUserDisplay();								
		break;

	case (SDSA_EXPRESSPAY_SCREEN_SIGNATURE_REQUIRED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);
		_Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_WaitUserDisplay();								
		break;

	case (SDSA_EXPRESSPAY_SCREEN_APPROVED):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);
		Helper_DisplayMessage(STD_MESS_APPROVED, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_WaitUserDisplay();								
		break;
				
	case (SDSA_EXPRESSPAY_SCREEN_PROCESSING):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);
		_Helper_DisplayMessage(EXPRESSPAY_MESS_PROCESSING, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		Helper_DisplayMessage(EXPRESSPAY_MESS_PLEASE_WAIT, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		break;

	case (SDSA_EXPRESSPAY_SCREEN_REMOVE_CARD):
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);
		// Prompt for the removal of the card
		HelperRemoveCardSequence(NULL);
		break;

/////////////////////////////////
// INTERAC SPECIFIC SCREENS //
/////////////////////////////////
	case SDSA_INTERAC_SCREEN_IDLE:
	{
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_INTERAC);

		Helper_DisplayMessage(INTERAC_MESS_IDLE, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		
		// Set the LEDs into the idle state
		HelperLedsIdleState();
	}
	break;

	case SDSA_INTERAC_SCREEN_PRESENT_CARD:
	{
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_INTERAC);

		if (pTransactionData->ucTransactionType != SDSA_TRANSACTION_TYPE_REFUND)
		{
			Helper_DisplayMessage(INTERAC_MESS_DEBIT, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		}
		else
		{
			Helper_DisplayMessage(INTERAC_MESS_REFUND, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		}

		if (pTransactionData->bIsAmountPresent)
		{
			// Format the message that contains the amount, the currency according to ucFormat, ucPosition
			memset (ucFormattedAmountMessage, 0, sizeof(ucFormattedAmountMessage));
			Helper_GetCurrencyFormatFromParameters(SDSA_Fill_GiveMoneyLabel(),&ucFormat,&ucPosition);
			SDSA_Common_FormatAmount(ucFormat, SDSA_Fill_GiveMoneyLabel(), ucPosition, pTransactionData->ulTransactionAmountBin, ucFormattedAmountMessage);
			InitMSGinfos_message(&tDisplayMsg, (char*)ucFormattedAmountMessage);
			Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_2, &tDisplayMsg, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		}

		// Get the STD_MESS_PRESENT_CARD message and display it
		Helper_DisplayMessage(INTERAC_MESS_PRESENT_CARD, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
	}
	break;

	case SDSA_INTERAC_SCREEN_COLLISION:
	{
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_INTERAC);

		_Helper_DisplayMessage(INTERAC_MESS_SELECT_ONE_CARD_L1, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(INTERAC_MESS_SELECT_ONE_CARD_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, NOLEDSOFF);
		HelperErrorSequence (WITHBEEP);
		Helper_WaitUserDisplay();
	}
	break;

	case SDSA_INTERAC_SCREEN_NOT_SUPPORTED:
	{
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_INTERAC);

		Helper_DisplayMessage(INTERAC_MESS_NOT_SUPPORTED_L1, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(INTERAC_MESS_NOT_SUPPORTED_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, LEDSOFF);
		HelperErrorSequence (WITHBEEP);
		Helper_WaitUserDisplay();
	}
	break;

	case SDSA_INTERAC_SCREEN_USE_CONTACT:
	{
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_INTERAC);

		Helper_DisplayMessage(INTERAC_MESS_INSERT_CARD_L1, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
		Helper_DisplayMessage(INTERAC_MESS_INSERT_CARD_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_3, HELPERS_ALIGN_CENTER, LEDSOFF);
		HelperErrorSequence (WITHBEEP);
		Helper_WaitUserDisplay();
		// Set the LEDs into the idle state
		HelperLedsIdleState();
	}
	break;

	case SDSA_INTERAC_SCREEN_TIMEOUT_ELAPSED:
	{
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_INTERAC);
		Helper_DisplayMessage(INTERAC_MESS_NO_CARD, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
	}
	break;

	
	default:
		// Unexpected screen identifier
		GTL_Traces_TraceDebug ("SDSA_GuiState_DisplayScreen : Unexpected screen identifier (%02lx)", ulScreenIdentifier);
		nResult = SDI_STATUS_INVALID_DATA;
		break;
	}

	return (nResult);
}

