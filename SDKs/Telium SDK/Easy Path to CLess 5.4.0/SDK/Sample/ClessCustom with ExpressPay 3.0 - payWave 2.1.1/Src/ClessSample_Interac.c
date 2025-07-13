/**
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
 */


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////
static int gs_bIsInteracGuiMode = FALSE;				// Set to TRUE if the Interac GUI must be used
static unsigned long gs_ulStartDetectionTime = 0;		// Timer for "NO CARD"
static int gs_bDisplayNoCard = TRUE;					// Display or not the "NO CARD" message when timeout elapsed

/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __ClessSample_Interac_RetrieveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm);
static int __ClessSample_Interac_AddInteracSpecificData (T_SHARED_DATA_STRUCT * pDataStruct);
static T_Bool __ClessSample_Interac_OnlinePinManagement (T_SHARED_DATA_STRUCT * pStructureForOnlineData, int nCardHolderLang);
static void __ClessSample_Interac_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData);
static void __ClessSample_Interac_GetSelectedPreferedLanguage (int * pCardholderLanguage, int nMerchantLanguage);

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Initialize the timer when card detection starts.
void Interac_StartDetectionTimer (void)
{
	gs_ulStartDetectionTime = GTL_StdTimer_GetCurrent();
	gs_bDisplayNoCard = TRUE;
	return;
}

//! \brief Get the timer value.
//!	\return The tick value.
unsigned long Interac_GetDetectionTimer (void)
{
	return (gs_ulStartDetectionTime);
}

//! \brief Set the variable to display or not the "NO CARD" message when timeout elapsed.
//! \param[in] bValue : TRUE -> message will be displayed, FALSE -> message will not be displayed
void Interac_SetDisplayNoCard (int bValue)
{
	gs_bDisplayNoCard = bValue;
	return;
}

//! \brief Get the variable to display or not the "NO CARD" message when timeout elapsed.
//!	\return
//!		- TRUE message will be displayed.
//!		- FALSE message will not be displayed.
int Interac_GetDisplayNoCard (void)
{
	return(gs_bDisplayNoCard);
}

//! \brief Get the timeout value for card detection process from the parameter file.
//! \param[out] pNoCardTimeOut the timeout value (in milliseconds).
//! \return
//!		- TRUE if tag is present.
//!		- FALSE else.
int ClessSample_Interac_GetNoCardTimeOut (unsigned long *pNoCardTimeOut)
{
	TLV_TREE_NODE pTimeOut;		// Node for No Card Timeout.
	unsigned char * pValue;
	unsigned int nDataLength;

	pValue = NULL;
	nDataLength = 0;

	pTimeOut = TlvTree_Find(pTreeCurrentParam, TAG_SAMPLE_NO_CARD_TIMEOUT, 0);

	if (pTimeOut != NULL)
	{
		pValue = TlvTree_GetData(pTimeOut);
		nDataLength = TlvTree_GetLength(pTimeOut);
	}

	if ((pValue != NULL) && (nDataLength != 0))
	{
		GTL_Convert_BinNumberToUl(pValue, pNoCardTimeOut, nDataLength);
		return (TRUE);
	}

	return (FALSE);
}

//! \brief Get the Interac transaction outcome.
//! \param[out] pTransactionOutcome Retrieved transaction outcome :
//!		- \a INTERAC_CVM_NO_CVM No CVM to be performed.
//!		- \a INTERAC_CVM_SIGNATURE if signature shall be performed.
//!		- \a INTERAC_CVM_ONLINE_PIN if online PIN shall be performed.
//! \return
//!		- \ref TRUE if correctly retrieved.
//!		- \ref FALSE if an error occurred.

static int __ClessSample_Interac_RetrieveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	* pCvm = INTERAC_CVM_NO_CVM; // Default result
	
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_INTERAC_TRANSACTION_CVM, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		nResult = FALSE;
		goto End;
	}
	
	// Get the resultant CVM performed
	* pCvm = pReadValue[0];
	
End:	
	return (nResult);
}


//! \brief Fill buffer with specific Interac for transaction.
//! \param[out] pDataStruct Shared exchange structure filled with the specific Interac data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

static int __ClessSample_Interac_AddInteracSpecificData (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int cr, nResult;
	object_info_t ObjectInfo;
	unsigned char bMerchantForcedTrOnline = 0x01;
	T_KERNEL_TRANSACTION_FLOW_CUSTOM sTransactionFlowCustom;
	unsigned char StepInterruption[KERNEL_PAYMENT_FLOW_STOP_LENGTH];// Bit field to stop payment flow,
																	// if all bit set to 0 => no stop during payment process
									                                // if right bit set to 1 : stop after payment step number 1
	unsigned char StepCustom[KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH]; 	// Bit field to custom payment flow,
																	// if all bit set to 0 => no stop during payment process
									                                // if right bit set to 1 : stop after payment step number 1
	unsigned char ucTempBuffer;
	int nPosition;
	const unsigned char * pTxnType;
	unsigned long ulTxnTypeLength;

	if (pDataStruct == NULL)
	{
		GTL_Traces_TraceDebug("__ClessSample_Interac_AddInteracSpecificData : Invalid Input data");
		nResult = FALSE;
		goto End;
	}
	
    // Init parameteters
	memset(StepInterruption, 0, sizeof(StepInterruption)); // Default Value : not stop on process
	memset(StepCustom, 0, sizeof(StepCustom)); // Default Value : not stop on process
	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
	nResult = TRUE;

	
	// Add a tag for Do_Txn management
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_STOP, KERNEL_PAYMENT_FLOW_STOP_LENGTH, (const unsigned char *)StepInterruption);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__ClessSample_Interac_AddInteracSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_STOP in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}
		
	
	// Customize steps
	ADD_STEP_CUSTOM(STEP_INTERAC_REMOVE_CARD,StepCustom); // To do GUI when card has been read
	ADD_STEP_CUSTOM(STEP_INTERAC_GET_CERTIFICATE, StepCustom); // To provide the CA key data for ODA

	if (ClessSample_IsBlackListPresent())	
		ADD_STEP_CUSTOM(STEP_INTERAC_EXCEPTION_FILE_GET_DATA, StepCustom); // To check if PAN is in the blacklist
	
	memcpy ((void*)&sTransactionFlowCustom, (void*)StepCustom, KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH);
	sTransactionFlowCustom.usApplicationType = ObjectInfo.application_type; // Kernel will call this application for customisation 
	sTransactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL; // Kernel will call SERVICE_CUSTOM_KERNEL service id for customisation 

    cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_KERNEL_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__ClessSample_Interac_AddInteracSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_CUSTOM in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}
	
	// Add data indicating if merchant forced transaction online or not
	if (ClessSample_Menu_IsMerchantForcedOnline())
	{
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_INTERAC_INT_MERCHANT_FORCE_ONLINE, 1, &bMerchantForcedTrOnline);

		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("__ClessSample_Interac_AddInteracSpecificData : Unable to add TAG_INTERAC_INT_MERCHANT_FORCE_ONLINE in shared buffer (cr=%02x)", cr);
			nResult = FALSE;
			goto End;
		}
	}

	// Add Tag TAG_INTERAC_TERMINAL_OPTION_STATUS - updated via PARAM file
	// Add Tag TAG_INTERAC_TERMINAL_TRANSACTION_TYPE - default in PARAM file
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_TRANSACTION_TYPE, &ulTxnTypeLength, &pTxnType);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		// Pan parameters is missing, we cannot check BlackList
		GTL_Traces_TraceDebug("__ClessSample_Interac_AddInteracSpecificData : Unable to find TAG_EMV_TRANSACTION_TYPE in buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;

	}

	if (pTxnType[0] == CLESS_SAMPLE_TRANSACTION_TYPE_REFUND)
	{
		ucTempBuffer=0x01;		// Interac v1.2, Section 4.7.2: set tag 9F5A to 0x01 for REFUND
	}
	else
	{
		ucTempBuffer=0x00;		// Interac v1.2, Section 4.7.2: set tag 9F5A to 0x00 for all other transactions
	}

	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_INTERAC_TERMINAL_TRANSACTION_TYPE, 1, &ucTempBuffer);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__ClessSample_Interac_AddInteracSpecificData : Unable to add TAG_INTERAC_TERMINAL_TRANSACTION_TYPE in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}


End:
	return (nResult);
}



//! \brief Perform the Online PIN input and encipher PIN.
//! \param[out] pStructureForOnlineData Data returned by the kernel in which the enciphered online PIN would be added.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

static T_Bool __ClessSample_Interac_OnlinePinManagement (T_SHARED_DATA_STRUCT * pStructureForOnlineData, int nCardHolderLang)
{
	T_SHARED_DATA_STRUCT * pDataRequest;
	T_Bool nResult = B_TRUE;
	int cr;
	int nPosition;
	const unsigned char * pPan;
	unsigned long ulPanLength;
	const unsigned char * pAmount;
	unsigned long ulAmountLength;
	unsigned long ulAmount = 0;
	BUFFER_SAISIE buffer_saisie;
	MSGinfos tMsg;
	
	pDataRequest = GTL_SharedExchange_InitShared (128);

	if (pDataRequest != NULL)
	{
		// Clear shared buffer
		GTL_SharedExchange_ClearEx (pDataRequest, FALSE);

		// Indicate tag to be requested
		GTL_SharedExchange_AddTag (pDataRequest, TAG_EMV_APPLI_PAN, 0, NULL);
		GTL_SharedExchange_AddTag (pDataRequest, TAG_EMV_AMOUNT_AUTH_NUM, 0, NULL);

		cr = Interac_GetData (pDataRequest);

		if (cr != KERNEL_STATUS_OK)
		{
			GTL_Traces_TraceDebug("__ClessSample_Interac_OnlinePinManagement : An error occurred when getting tags from the Interac kernel (cr=%02x)", cr);
			nResult = B_FALSE;
			goto End;
		}

		// Tags have been obtained (if present), get the PAN
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pDataRequest, &nPosition, TAG_EMV_APPLI_PAN, &ulPanLength, &pPan) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug ("__ClessSample_Interac_OnlinePinManagement : Missing PAN for Online PIN");
			nResult = B_FALSE;
			goto End;
		}

		// Get the transaction amount (numeric)
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pDataRequest, &nPosition, TAG_EMV_AMOUNT_AUTH_NUM, &ulAmountLength, &pAmount) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug ("__ClessSample_Interac_OnlinePinManagement : Missing Amount for Online PIN");
			nResult = B_FALSE;
			goto End;
		}
		
		// Convert amount
		GTL_Convert_DcbNumberToUl(pAmount, &ulAmount, ulAmountLength);
		
		// Warning, erase display must be made only if Pin input will be made on customer screen
		if (ClessSample_IsPinpadPresent())
		{
			char acDymmyMsg[] = "";

			// Display dummy message to erase display
			tMsg.message = acDymmyMsg;
			tMsg.coding = _ISO8859_;
			tMsg.file = GetCurrentFont();

			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
		}
		
		// Request online PIN entry
		cr = ClessSample_PinManagement_OnLinePinManagement ((unsigned char*)pPan, 1, ulAmount, 30000, 10000, nCardHolderLang, &buffer_saisie);

		if (cr == INPUT_PIN_ON)
		{
			cr = GTL_SharedExchange_AddTag(pStructureForOnlineData, TAG_SAMPLE_ENCIPHERED_PIN_CODE, buffer_saisie.nombre , (const unsigned char *)buffer_saisie.donnees);

			if (cr != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_Traces_TraceDebug ("__ClessSample_Interac_OnlinePinManagement : Unable to add TAG_SAMPLE_ENCIPHERED_PIN_CODE in the shared buffer (cr = %02x)", cr);
				nResult = B_FALSE;
				goto End;
			}
		}
		else if (cr == CANCEL_INPUT)
		{
				GTL_Traces_TraceDebug ("__ClessSample_Interac_OnlinePinManagement : input pin Cancelled");
				nResult = B_NON_INIT;
				goto End;
		}
		else
		{
			GTL_Traces_TraceDebug ("PIN Entry fail");
		}
	}

End:
	return (nResult);
}



//! \brief Manage the debug mode for Interac kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void ClessSample_Interac_DebugActivation (int bActivate)
{
	T_SHARED_DATA_STRUCT * pSharedStructure;
	int nResult;
	unsigned char ucDebugMode = 0x00;

	if (bActivate)
		ucDebugMode = 0x07;
	
	pSharedStructure = GTL_SharedExchange_InitShared(256);
	
	if (pSharedStructure != NULL)
	{
		nResult = GTL_SharedExchange_AddTag(pSharedStructure, TAG_KERNEL_DEBUG_ACTIVATION, 1, &ucDebugMode);

		if (nResult != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Interac_DebugActivation : Unable to add TAG_KERNEL_DEBUG_ACTIVATION (nResult = %02x)", nResult);
		}
		else
		{
			nResult = Interac_DebugManagement(pSharedStructure);
			
			if (nResult != KERNEL_STATUS_OK)
			{
				GTL_Traces_TraceDebug("ClessSample_Interac_DebugActivation : Error occurred during Interac Debug activation (nResult = %02x)", nResult);
			}
		}
		
		// Destroy the shared buffer
		GTL_SharedExchange_DestroyShare(pSharedStructure);
	}
}



//! \brief Create a shared buffer, and requests the selected language to the Interac kernel.
//! \param[out] pCardholderLanguage Selected language (equal to \a nMerchantLanguage if selected language is not found).
//! \param[in] nMerchantLanguage Merchant language as configured by the manager.

static void __ClessSample_Interac_GetSelectedPreferedLanguage (int * pCardholderLanguage, int nMerchantLanguage)
{
	int ret;
	T_SHARED_DATA_STRUCT * pStruct;
	unsigned char * pInfo;

	// By default, cardholder language is the same as the merchant language
	*pCardholderLanguage = nMerchantLanguage;

	// Init a shared buffer to get the prefered selected language
	pStruct = GTL_SharedExchange_InitShared (128);

	if (pStruct == NULL)
	{
		// An error occurred when creating the shared buffer
		GTL_Traces_TraceDebug ("__ClessSample_Interac_GetSelectedPreferedLanguage : An error occurred when creating the shared buffer");
		goto End;
	}	

	// Add tag in the shared buffer to request it
	ret = GTL_SharedExchange_AddTag (pStruct, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, 0, NULL);

	if (ret != STATUS_SHARED_EXCHANGE_OK)
	{
		// An error occurred when adding the TAG_KERNEL_SELECTED_PREFERED_LANGUAGE tag in the structure
		GTL_Traces_TraceDebug ("__ClessSample_Interac_GetSelectedPreferedLanguage : An error occurred when adding the TAG_KERNEL_SELECTED_PREFERED_LANGUAGE tag in the structure (ret = %02x)", ret);
		goto End;
	}	

	// Request data to Interac kernel
	ret = Interac_GetData (pStruct);

	if (ret != KERNEL_STATUS_OK)
	{
		// An error occurred when getting data from the Interac kernel
		GTL_Traces_TraceDebug ("__ClessSample_Interac_GetSelectedPreferedLanguage : An error occurred when getting data from the Interac kernel (ret = %02x)", ret);
		goto End;
	}

	// Search the tag in the kernel response structure
	if (ClessSample_Common_RetrieveInfo (pStruct, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, &pInfo))
		*pCardholderLanguage = ClessSample_Term_GiveLangNumber(pInfo);

End:
	// Destroy the shared buffer if created
	if (pStruct != NULL)
		GTL_SharedExchange_DestroyShare (pStruct);
}



//! \brief Perform the Interac kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int ClessSample_Interac_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep)
{
	int nResult = KERNEL_STATUS_CONTINUE;
	unsigned char ucCapkIndex;
	unsigned char ucRid[5];
	unsigned long ulReadLength;
	int nPosition;
	const unsigned char * pReadValue;
	const unsigned char * pPan;
	unsigned long ulPanLength;
	const unsigned char * pPanSeqNumber;
	unsigned char ucVoidPanSeqNumber = C_CLESS_VOID_PAN_SEQ_NUMBER; // Unused value for PanSeqNumber
	unsigned long ulPanSeqNbLength;
	unsigned char bPanInExceptionFile = FALSE;

    
    switch (ucCustomisationStep) // Steps to customise
    {
	case (STEP_INTERAC_REMOVE_CARD):
		HelperRemoveCardSequence(pSharedData);
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_INTERAC_GET_CERTIFICATE):
		memset (ucRid, 0, sizeof(ucRid));
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_EMV_CA_PUBLIC_KEY_INDEX_CARD, &ulReadLength, (const unsigned char **)&pReadValue) == STATUS_SHARED_EXCHANGE_OK)
			ucCapkIndex = pReadValue[0];
		else
			ucCapkIndex = 0;
		
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_EMV_DF_NAME, &ulReadLength, (const unsigned char **)&pReadValue) == STATUS_SHARED_EXCHANGE_OK)
			memcpy (ucRid, pReadValue, 5);
		
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		
		if (!ClessSample_Parameters_GetCaKeyData (pTreeCurrentParam, ucCapkIndex, ucRid, pSharedData))
		{
			GTL_Traces_TraceDebug ("ClessSample_Interac_CustomiseStep : ClessSample_Parameters_GetCaKeyData failed");
		}
		
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_INTERAC_EXCEPTION_FILE_GET_DATA):
		// Get the PAN
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_EMV_APPLI_PAN, &ulPanLength, &pPan) != STATUS_SHARED_EXCHANGE_OK)
		{
			// Pan parameters is missing, we cannot check BlackList
			GTL_Traces_TraceDebug ("ClessSample_Interac_CustomiseStep : PAN is missing for excpetion file checking");
			break;
		}
		
		// Get the PAN Sequence Number
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER, &ulPanSeqNbLength, &pPanSeqNumber) != STATUS_SHARED_EXCHANGE_OK)
		{
			// Pan Sequence Number is missing, we will check BlackList without PanSeqNumber
			pPanSeqNumber = &ucVoidPanSeqNumber;
		}

		// Check if PAN is in the exception file
		bPanInExceptionFile = ClessSample_BlackListIsPan((int)ulPanLength, pPan, (int)(pPanSeqNumber[0]));

		GTL_SharedExchange_ClearEx (pSharedData, FALSE);

		if (bPanInExceptionFile)
		{
			// Add TAG_KERNEL_PAN_IN_BLACK_LIST tag in the exchange buffer to indicate Interac kernel the PAN is in the black list
			if (GTL_SharedExchange_AddTag (pSharedData, TAG_KERNEL_PAN_IN_BLACK_LIST, 1, &bPanInExceptionFile) != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_SharedExchange_ClearEx (pSharedData, FALSE);
				GTL_Traces_TraceDebug ("ClessSample_Interac_CustomiseStep : Unable to add TAG_KERNEL_PAN_IN_BLACK_LIST in the shared buffer");
			}
		}

		nResult = KERNEL_STATUS_CONTINUE;
		break;

	// Other customisation steps could be defined if necessary
		
	default:
		GTL_Traces_TraceDebug ("ClessSample_Interac_CustomiseStep : Step to customise (unknown) = %02x\n", ucCustomisationStep);
		break;
	}
	
	return (nResult);
}



//! \brief Calls the Interac kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for Interac transaction.
//!	\return
//!		- Interac kernel result.

int ClessSample_Interac_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct)
{
	unsigned char bLoopMode;
	int nResult = CLESS_CR_MANAGER_END;
	int cr, nPosition;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	unsigned char ucCvm;
	unsigned char auCustomerDisplayAvailable;
	unsigned char bSaveInBatch = FALSE;
	int merchLang, nCardHolderLang;
	T_Bool bContinueWithOnlineAuthorisation = B_TRUE;
	MSGinfos tMsg;

	// Loop mode information
	bLoopMode = ClessSample_Menu_IsTransactionLoopOn();
	
	merchLang = PSQ_Give_Language();
	auCustomerDisplayAvailable = Helper_IsClessCustomerDisplayAvailable();
	
	// Indicate Interac kernel is going to be used (for customisation purposes)
	ClessSample_Customisation_SetUsedPaymentScheme (CLESS_SAMPLE_CUST_INTERAC);
	
	// Get the Interac
    if (!__ClessSample_Interac_AddInteracSpecificData(pDataStruct))
	{
	    GTL_Traces_TraceDebug("ClessSample_Interac_PerformTransaction : ClessSample_Fill_InteracTransaction failed\n");
	}
	else
	{
		// Debug purpose : if you need to dump the data provided to the kernel
		///ClessSample_DumpData_DumpSharedBufferWithTitle(pDataStruct, "INPUT DATA");
		cr = Interac_DoTransaction(pDataStruct);

		// Debug purpose : if you need to dump the data provided by the kernel
		if (ClessSample_Menu_IsTransactionDataDumpingOn())
			ClessSample_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATA RECORD");

		// Get prefered card language (a request shall be done to the Interac kernel as the TAG_KERNEL_SELECTED_PREFERED_LANGUAGE tag is not defaulty returned by the Interac kernel).
		__ClessSample_Interac_GetSelectedPreferedLanguage (&nCardHolderLang, merchLang);

		// Get the TAG_INTERAC_TRANSACTION_CVM to identify the CVM to be performed :
		// 	- INTERAC_CVM_NO_CVM (0x01) : "No CVM" method has been applied.
		// 	- INTERAC_CVM_SIGNATURE (0x02) : "Signature" method has been applied.
		// 	- INTERAC_CVM_ONLINE_PIN (0x04) : "Online PIN" method has been applied.
		if (!__ClessSample_Interac_RetrieveCvmToApply (pDataStruct, &ucCvm))
		{
			ucCvm = INTERAC_CVM_NO_CVM;
		}

		// Additional possible processing :
		//	- Perform an online authorisation if necessary
		//	- Save the transaction in the batch if transaction is accepted
		//	- Perform CVM processing if necessary
		if ((ucCvm == INTERAC_CVM_ONLINE_PIN) && (cr == KERNEL_STATUS_OFFLINE_APPROVED))
			cr = KERNEL_STATUS_ONLINE_AUTHORISATION;
		
		switch (cr)
		{
		case (KERNEL_STATUS_OFFLINE_APPROVED):
			ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_OFFLINE_APPROVED, merchLang, nCardHolderLang);
			bSaveInBatch = TRUE;
			
			Interac_GetAllData(pDataStruct); // Get all the kernel data to print the receipt
			
			// check if a receipt is required
			nPosition = SHARED_EXCHANGE_POSITION_NULL;
			cr = GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_INTERAC_RECEIPT_STATUS, &ulReadLength, &pReadValue);

			if (cr == STATUS_SHARED_EXCHANGE_OK)
			{
				if (pReadValue[0] == INTERAC_RECEIPT_REQUIRED)
				{
					if (bLoopMode == 0)
					{
						ClessSample_Term_Read_Message(STD_MESS_PRINT_RECEIPT, merchLang, &tMsg);
						if ((ClessSample_DumpData_DumpGetOutputId() != CUSTOM_OUTPUT_NONE) && ((ucCvm == VISAWAVE_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30, merchLang))))
							ClessSample_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_INTERAC, APPROVED_TICKED, (ucCvm == INTERAC_CVM_SIGNATURE), nCardHolderLang, WITH_AOSA);
					}
				}
			}
			else
			{
				GTL_Traces_TraceDebug("ClessSample_Interac_PerformTransaction : GTL_SharedExchange_FindNext failed to find TAG_INTERAC_RECEIPT_STATUS\n");
			}
			break;
		
		case (KERNEL_STATUS_OFFLINE_DECLINED):
			ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_OFFLINE_DECLINED, merchLang, nCardHolderLang);
			break;
		
		case (KERNEL_STATUS_ONLINE_AUTHORISATION):
			if (ucCvm == INTERAC_CVM_ONLINE_PIN)
			{
				bContinueWithOnlineAuthorisation = __ClessSample_Interac_OnlinePinManagement (pDataStruct, nCardHolderLang);
			}

			if (bContinueWithOnlineAuthorisation == B_TRUE)
			{
				ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_PROCESSING, merchLang, nCardHolderLang);

				if (ClessSample_FinancialCommunication_ManageAuthorisation (pDataStruct))
				{
					nPosition = SHARED_EXCHANGE_POSITION_NULL;

					if (GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EMV_AUTHORISATION_RESPONSE_CODE, &ulReadLength, &pReadValue) == STATUS_SHARED_EXCHANGE_OK)
					{
						if ((pReadValue[0] == 0x30) && (pReadValue[1] == 0x30))
						{
							ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_APPROVED, merchLang, nCardHolderLang);
							bSaveInBatch = TRUE;

							// Get all the kernel data to print the receipt
							Interac_GetAllData(pDataStruct);

							// check if a receipt is required
							nPosition = SHARED_EXCHANGE_POSITION_NULL;
							cr = GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_INTERAC_RECEIPT_STATUS, &ulReadLength, &pReadValue);

							if (cr == STATUS_SHARED_EXCHANGE_OK)
							{
								if (pReadValue[0] == INTERAC_RECEIPT_REQUIRED)
								{
									if (bLoopMode == 0)
									{
										ClessSample_Term_Read_Message(STD_MESS_PRINT_RECEIPT, merchLang, &tMsg);
										if ((ClessSample_DumpData_DumpGetOutputId() != CUSTOM_OUTPUT_NONE) && ((ucCvm == VISAWAVE_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30, merchLang))))
											ClessSample_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_INTERAC, APPROVED_TICKED, (ucCvm == INTERAC_CVM_SIGNATURE), nCardHolderLang, WITH_AOSA);
									}
								}
							}
							else
							{
								GTL_Traces_TraceDebug("ClessSample_Interac_PerformTransaction : GTL_SharedExchange_FindNext failed to find TAG_INTERAC_RECEIPT_STATUS after ONLINE processing\n");
							}
						}
						else if ((pReadValue[0] == 0x38) && (pReadValue[1] == 0x39))
						{
							// revert to insert if host returns '89' ARC
							nResult = CLESS_CR_MANAGER_RESTART_WO_CLESS;
						}
						else
						{
							ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_DECLINED, merchLang, nCardHolderLang);
						}
					}
					else
					{
						// No Authorisation response code
						ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_DECLINED, merchLang, nCardHolderLang);
					}
				}
				else
				{
					ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_UNABLE, merchLang, nCardHolderLang);
				}
			}
			else
			{
				if (bContinueWithOnlineAuthorisation == B_NON_INIT)
					ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_PIN_CANCEL, merchLang, nCardHolderLang);
				else
					ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_PIN_ERROR, merchLang, nCardHolderLang);
			}
			break;
		
		case (KERNEL_STATUS_USE_CONTACT_INTERFACE):
			nResult = CLESS_CR_MANAGER_RESTART_WO_CLESS;
			break;
		
		case (KERNEL_STATUS_CARD_BLOCKED):
			ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_CARD_BLOCKED, merchLang, nCardHolderLang);
			HelperErrorSequence (WITHBEEP);
			Helper_WaitUserDisplay();
			break;
			
		case (KERNEL_STATUS_APPLICATION_BLOCKED):
			ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_APPLICATION_BLOCKED, merchLang, nCardHolderLang);
			HelperErrorSequence (WITHBEEP);
			Helper_WaitUserDisplay();
			break;
			
		case (KERNEL_STATUS_COMMUNICATION_ERROR):
		default: // Error case
			ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_ERROR, merchLang, nCardHolderLang);
			HelperErrorSequence(WITHBEEP);
			Helper_WaitUserDisplay();
			break;
		}

		if (bSaveInBatch)
			__ClessSample_Interac_AddRecordToBatch (pDataStruct);

		// Deselect the card
		//CLESS_DeselectCard(NULL, 0, TRUE, FALSE);

		// If the transaction does not restart from the begining, set the LEDs into the idle state
		if (nResult != CLESS_CR_MANAGER_RESTART)
		{
			// Increment 
			ClessSample_Batch_IncrementTransactionSeqCounter();

			// If activated, dump all the kernel database
			if (ClessSample_Menu_IsTransactionDatabaseDumpingOn())
			{
				Interac_GetAllData(pDataStruct); // Get all the kernel data to print the receipt
				ClessSample_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATABASE DUMP");
			}
		}
	}

	// Transaction is completed, clear Interac kernel transaction data
	Interac_Clear ();

	// Return result
	return (nResult);
}

//! \brief Add the tranasction record in the batch file.
//! \param[in] pSharedData Shared buffer to be used to get all the record data.

static void __ClessSample_Interac_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData)
{
	// Tags required for Offline and Online approved transactions
	T_TI_TAG tRequestedTags[] = {TAG_EMV_TRACK_2_EQU_DATA, TAG_EMV_DF_NAME,
								TAG_EMV_APPLICATION_LABEL, TAG_EMV_APPLI_PREFERED_NAME, TAG_EMV_ISSUER_CODE_TABLE_INDEX,
								TAG_EMV_APPLICATION_CRYPTOGRAM, TAG_EMV_CRYPTOGRAM_INFO_DATA, TAG_EMV_ISSUER_APPLI_DATA,
								TAG_EMV_ATC, TAG_EMV_TVR, TAG_EMV_UNPREDICTABLE_NUMBER, TAG_EMV_TRANSACTION_CURRENCY_CODE,
								TAG_EMV_TRANSACTION_TYPE, TAG_EMV_TRANSACTION_DATE, TAG_EMV_AMOUNT_AUTH_NUM,
								TAG_EMV_TERMINAL_COUNTRY_CODE, TAG_EMV_CVM_RESULTS, TAG_EMV_AIP, 
								TAG_INTERAC_TRANSACTION_OUTCOME, TAG_INTERAC_TRANSACTION_CVM, TAG_KERNEL_CARD_TYPE,
								TAG_INTERAC_RECEIPT_STATUS};

	unsigned int nIndex;
	int nResult;

	// Clear the shared exchange buffer
	GTL_SharedExchange_ClearEx (pSharedData, FALSE);
	nIndex = 0;

	while (nIndex < NUMBER_OF_ITEMS(tRequestedTags))
	{
		GTL_SharedExchange_AddTag (pSharedData, tRequestedTags[nIndex], 0, NULL);
		nIndex ++;
	}

	// Get the common tags

	nResult = Interac_GetData (pSharedData);

	if (nResult == KERNEL_STATUS_OK)
	{
		if (!ClessSample_Batch_AddTransactionToBatch (pSharedData))
		{
			int merchLang;

			merchLang = PSQ_Give_Language();
			GTL_Traces_TraceDebug ("__ClessSample_Interac_AddRecordToBatch : Save transaction in batch failed");
			ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_BATCH_ERROR, merchLang, merchLang);
		}
	}
	else
	{
		GTL_Traces_TraceDebug ("__ClessSample_Interac_AddRecordToBatch : Unable to get Interac data (nResult = %02x)\n", nResult);
	}
}

//! \brief Check in the parameter file if the GUI mode to use is Interac.

void ClessSample_Interac_SetInteracGuiMode (void)
{
	TLV_TREE_NODE pGuiMode;
	unsigned char * pValue;
	unsigned int nDataLength;

	pValue = NULL;
	nDataLength = 0;

	pGuiMode = TlvTree_Find(pTreeCurrentParam, TAG_SAMPLE_INTERAC_MODE, 0);

	if (pGuiMode != NULL)
	{
		pValue = TlvTree_GetData(pGuiMode);
		nDataLength = TlvTree_GetLength(pGuiMode);
	}

	if ((pValue != NULL) && (nDataLength != 0))
	{
		if (pValue[0] == CLESS_SAMPLE_MODE_INTERAC)
		{
			gs_bIsInteracGuiMode = TRUE;
			return;
		}
	}

	gs_bIsInteracGuiMode = FALSE;
}
//! \brief Check if the Interac GUI mode is activated.
//!	\return
//!		- TRUE if Interac GUI mode is used.
//!		- FALSE else.
int ClessSample_Interac_IsInteracGuiMode (void)
{
	return (gs_bIsInteracGuiMode);
}
