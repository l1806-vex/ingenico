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

// Defines the timeout to perform the requested CVM
#define C_SIGNATURE_TIMEOUT					(5000)  // 5 Secondes
#define C_PINENTRY_TIMEOUT					(10000) // 10 Secondes

// Defines the color of the leds for Visa AP user interface
#define LIGHTRED							0xFFFF0000
#define LIGHTGREEN							0xFF00FF00
#define LIGHTBLUE							0xFF0000FF
#define LIGHTYELLOW							0xFFFFFF00


/////////////////////////////////////////////////////////////////
//// Define the transaction card provider type //////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

const char gsVisaWaveTerminalSupportedLanguage[] =
{
	"en"
	"fr"
};

static int gs_nVisaWaveKernelPresent = FALSE;			// Set to TRUE if the VisaWave kernel is present in the terminal
static int gs_nTransactionRestartedWithpayWave = FALSE;	// Set to TRUE if the VisaWave kernel detects it is a payWave card  (the transaction restarts using the payWave kernel)
static int gs_bIsVisaAsiaGuiMode = FALSE;				// Set to TRUE if the VisaWave Asia GUI must be used
static unsigned long gs_ulStartDetectionTime = 0;		// Timer for "NO CARD"
static int gs_bDisplayNoCard = TRUE;					// Display or not the "NO CARD" message when timeout elapsed

// Data concerning the last transaction (for Double Dip process)
static unsigned char gs_ucLastAmount[6];			// Last transaction amount
static DATE gs_LastDate;							// Last transaction date
static unsigned char gs_ucLastPAN[10];				// Last transaction PAN
static unsigned int gs_nLastPANLength;				// Last transaction PAN length
static int gs_bLastTransactionDataFound = FALSE;	// TRUE if all the last transaction data was get


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __ClessSample_VisaWave_AddVisaWaveSpecificData (T_SHARED_DATA_STRUCT * pDataStruct);
static void __ClessSample_VisaWave_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData);
static int __ClessSample_VisaWave_RetrieveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm);
static void __ClessSample_VisaWave_InitLastTransactionData (void);
static void __ClessSample_VisaWave_SaveLastTransactionData (TLV_TREE_NODE TlvTreeNode);
static void __ClessSample_VisaWave_CheckLastTransaction (T_SHARED_DATA_STRUCT *pCurrentTransactionStruct);
static int __ClessSample_VisaWave_GetDoubleDipTimeOut (unsigned long *pDoubleDipTimeOut);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


		
//! \brief Initialize the timer when card detection starts.
void VisaWave_StartDetectionTimer (void)
{
	gs_ulStartDetectionTime = GTL_StdTimer_GetCurrent();
	gs_bDisplayNoCard = TRUE;
	return;
}

//! \brief Get the timer value.
//!	\return The tick value.
unsigned long VisaWave_GetDetectionTimer (void)
{
	return (gs_ulStartDetectionTime);
}

//! \brief Set the variable to display or not the "NO CARD" message when timeout elapsed.
//! \param[in] bValue : TRUE -> message will be displayed, FALSE -> message will not be displayed
void VisaWave_SetDisplayNoCard (int bValue)
{
	gs_bDisplayNoCard = bValue;
	return;
}

//! \brief Get the variable to display or not the "NO CARD" message when timeout elapsed.
//!	\return
//!		- TRUE message will be displayed.
//!		- FALSE message will not be displayed.
int VisaWave_GetDisplayNoCard (void)
{
	return(gs_bDisplayNoCard);
}


//! \brief Check if the current transaction is a VisaWave transaction.
//! \return
//!		- TRUE if the VisaWave kernel is present and gs_nTransactionRestartedWithpayWave is not set.
//!		- FALSE else.
unsigned char VisaWave_isVisaWaveProcessing (void)
{
	if(gs_nVisaWaveKernelPresent && (!gs_nTransactionRestartedWithpayWave))
		return (TRUE);
	else
		return (FALSE);
}

//! \brief Set the variable to indicate that the VisaWave kernel is present in the terminal.
void VisaWave_SetVisaWaveKernelPresence (void)
{
	gs_nVisaWaveKernelPresent = TRUE;
	return;
}

//! \brief Set the variable to indicate that the transaction must use the payWave kernel.
void VisaWave_SetpayWaveFallBack (void)
{
	gs_nTransactionRestartedWithpayWave = TRUE;
	return;
}

//! \brief Unset the payWave fallback variable.
void VisaWave_UnsetpayWaveFallBack (void)
{
	gs_nTransactionRestartedWithpayWave = FALSE;
	return;
}

//! \brief Get the VisaWave CVM to perform.
//! \param[out] pCvm Retrieved transaction CVM :
//!		- \a VISAWAVE_CVM_NO_CVM No CVM to be performed.
//!		- \a VISAWAVE_CVM_SIGNATURE if signature shall be performed.
//!		- \a VISAWAVE_CVM_ONLINE_PIN if online PIN shall be performed.
//! \return
//!		- \ref TRUE if correctly retrieved.
//!		- \ref FALSE if an error occurred.

static int __ClessSample_VisaWave_RetrieveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	* pCvm = VISAWAVE_CVM_NO_CVM; // Default result
	
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_VISAWAVE_TRANSACTION_CVM, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		nResult = FALSE;
		goto End;
	}
	
	// Get the transaction outcome
	* pCvm = pReadValue[0];
	
End:	
	return (nResult);
}

//! \brief Fill buffer with specific VisaWave for transaction.
//! \param[out] pDataStruct Shared exchange structure filled with the specific VisaWave data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

static int __ClessSample_VisaWave_AddVisaWaveSpecificData (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int cr, nResult;
	int nPosition;
	unsigned long ulReadLength;
	unsigned char * pReadValue;

	T_KERNEL_TRANSACTION_FLOW_CUSTOM sTransactionFlowCustom;
	object_info_t ObjectInfo;
	unsigned char StepInterruption[KERNEL_PAYMENT_FLOW_STOP_LENGTH];// Bit field to stop payment flow,
																	// if all bit set to 0 => no stop during payment process
									                                // if right bit set to 1 : stop after payment step number 1
	unsigned char StepCustom[KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH]; 	// Bit field to custom payment flow,
																	// if all bit set to 0 => no stop during payment process
									                                // if right bit set to 1 : stop after payment step number 1
	if (pDataStruct == NULL)
	{
		GTL_Traces_TraceDebug("__ClessSample_VisaWave_AddVisaWaveSpecificData : Invalid Input data");
		nResult = FALSE;
		goto End;
	}
	
	// Init parameteters
	memset(StepInterruption, 0, sizeof(StepInterruption)); // Default Value : not stop on process
	memset(StepCustom, 0, sizeof(StepCustom)); // Default Value : not stop on process
	nResult = TRUE;
	
	// Customize steps :
	ADD_STEP_CUSTOM(STEP_VISAWAVE_REMOVE_CARD,StepCustom); 		// To do GUI when card has been read
	ADD_STEP_CUSTOM(STEP_VISAWAVE_GET_CERTIFICATE,StepCustom); 	// To get the certifiacte for ODA step


	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);

	
	// Add a tag for Do_Txn management
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_STOP, KERNEL_PAYMENT_FLOW_STOP_LENGTH, (const unsigned char *)StepInterruption);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__ClessSample_VisaWave_AddVisaWaveSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_STOP in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}

	// Add a tag for Do_Txn management
	memcpy ((void*)&sTransactionFlowCustom, (void*)StepCustom, KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH);
	sTransactionFlowCustom.usApplicationType = ObjectInfo.application_type; // Kernel will call this application for customisation 
	sTransactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL; // Kernel will call SERVICE_CUSTOM_KERNEL service id for customisation
	
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_KERNEL_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__ClessSample_VisaWave_AddVisaWaveSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_CUSTOM in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}

	// Add Tag TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES, sizeof(gsVisaWaveTerminalSupportedLanguage), (const unsigned char *)&gsVisaWaveTerminalSupportedLanguage);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__ClessSample_VisaWave_AddVisaWaveSpecificData : Unable to add TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}

    // Search and replace internal transaction type in the shared buffer
    nPosition = SHARED_EXCHANGE_POSITION_NULL;

    if(GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_TERMINAL_TYPE, &ulReadLength, (const unsigned char **)&pReadValue) == STATUS_SHARED_EXCHANGE_OK)
    {
    	pReadValue[0] = 0x00; // Domestic
    }

End:
	return (nResult);
}


//! \brief Manage the debug mode for VisaWave kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void ClessSample_VisaWave_DebugActivation (int bActivate)
{
	T_SHARED_DATA_STRUCT * pSharedStructure;
	int nResult;
	unsigned char ucDebugMode = 0x00;
	
	if (bActivate)
		ucDebugMode = 0x01;
	
	pSharedStructure = GTL_SharedExchange_InitShared(256);
	
	if (pSharedStructure != NULL)
	{
		nResult = GTL_SharedExchange_AddTag(pSharedStructure, TAG_KERNEL_DEBUG_ACTIVATION, 1, &ucDebugMode);
		
		if (nResult != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_VisaWave_DebugActivation : Unable to add TAG_KERNEL_DEBUG_ACTIVATION (nResult = %02x)", nResult);
		}
		else
		{
			nResult = VisaWave_DebugManagement(pSharedStructure);
			
			if (nResult != KERNEL_STATUS_OK)
			{
				GTL_Traces_TraceDebug("ClessSample_VisaWave_DebugActivation : Error occurred during VisaWave Debug activation (nResult = %02x)", nResult);
			}
		}
		
		// Destroy the shared buffer
		GTL_SharedExchange_DestroyShare(pSharedStructure);
	}
}



//! \brief Perform the VisaWave kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int ClessSample_VisaWave_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep)
{
	int nResult = KERNEL_STATUS_CONTINUE;
	int nPosition;
	unsigned char ucCapkIndex;
	unsigned char ucRid[5];
	unsigned long ulReadLength;
	const unsigned char * pReadValue;

	switch (ucCustomisationStep) // Steps to customise
	{
	case STEP_VISAWAVE_REMOVE_CARD:
		HelperRemoveCardSequence(pSharedData);
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_VISAWAVE_GET_CERTIFICATE):
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
			GTL_Traces_TraceDebug ("ClessSample_VisaWave_CustomiseStep : ClessSample_Parameters_GetCaKeyData failed");
		}
		
		nResult = KERNEL_STATUS_CONTINUE;
		break;

	// Other customisation steps could be defined if necessary
	
	default:
		GTL_Traces_TraceDebug ("ClessSample_VisaWave_CustomiseStep : Step to customise (unknown) = %02x", ucCustomisationStep);
		break;
	}

	return (nResult);
}


//! \brief Calls the VisaWave kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for VisaWave transaction.
//!	\return
//!		- VisaWave kernel result.

int ClessSample_VisaWave_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct)
{
	unsigned char bLoopMode;
	int cr, nFound;
	int nResult = C_CLESS_CR_END;
	int nPosition;
	int nCurrencyCode;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	unsigned char bOnlinePinError = FALSE;
	BUFFER_SAISIE buffer_saisie;
	unsigned char ucCvm;
	
	unsigned char cr_pin_online, ucOnLineDeclined;
	const unsigned char * pPan;
	unsigned long ulLgPan;
	unsigned char auCustomerDisplayAvailable;
	unsigned long ulAmount = 0;
	unsigned long ulLgAmount;
	const unsigned char * pAmount;
	unsigned char * pInfo;
	unsigned char * pCurrencyCode;
	int bSaveInBatch = FALSE;
    int merchLang, nCardHolderLang;
	MSGinfos tMsg;	
	unsigned long ulStartSignatureTime = 0;
	int nTimeout;

	// Loop mode information
	bLoopMode = ClessSample_Menu_IsTransactionLoopOn();

	// The contactless transaction can be stopped by a contact card (swipe or chip)
	auCustomerDisplayAvailable = Helper_IsClessCustomerDisplayAvailable();
	merchLang = PSQ_Give_Language();
	
	// Indicate VisaWave kernel is going to be used (for customisation purposes)
	ClessSample_Customisation_SetUsedPaymentScheme (CLESS_SAMPLE_CUST_VISAWAVE);

	if (!__ClessSample_VisaWave_AddVisaWaveSpecificData(pDataStruct))
	{
		GTL_Traces_TraceDebug("ClessSample_VisaWave_PerformTransaction : __ClessSample_VisaWave_AddVisaWaveSpecificData error\n");
	}
	else
	{
		// Dump all the data sent to the VisaWave kernel
		////ClessSample_DumpData_DumpSharedBuffer(pDataStruct, 0);

		// For later use
		ulAmount = 0;
		nCurrencyCode = 0;
		
		nFound = ClessSample_Common_RetrieveInfo (pDataStruct, TAG_EMV_AMOUNT_AUTH_BIN, &pInfo);
		if (nFound)
		{
			ulLgAmount = 4;
			GTL_Convert_BinNumberToUl(pInfo, &ulAmount, ulLgAmount);
		}

		nFound = ClessSample_Common_RetrieveInfo (pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_CODE, &pCurrencyCode);
		if (nFound)
		{
			nCurrencyCode = ((*pCurrencyCode)<< 8) + *(pCurrencyCode+1);
		}
		// End for later use
		
		ClessSample_Scan_TransacOpenDrivers();
		
		// Launch task that scans the peripheral to be checks for cancel (keyboard, chip, swipe)
		ClessSample_Scan_LaunchScanningTask(SCAN_CANCEL_ALL_INTERFACES);
		g_ScanningTask = GiveNoTask (g_tsScanning_task_handle);

		// Waiting task start before to call do_transaction
		// It allows to detect chip card / swipe card / user interruption

		ttestall (USER_EVENT_START, 2); // Wait scan task start		

		if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
		{
			// Display the "Processing" message
			if (auCustomerDisplayAvailable) // If a customer display is available
			{
				ClessSample_Term_Read_Message(VISAWAVE_MESS_PROCESSING, merchLang, &tMsg);
				Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
				Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);
			}
			// Display the customer message
			ClessSample_Term_Read_Message(VISAWAVE_MESS_PROCESSING, merchLang, &tMsg);
			Helper_DisplayTextCustomer (ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);

			// Turn on the 2nd LED
			TPass_LedsOn(TPASS_LED_YELLOW);
		}

		// Perform the VisaWave transaction
		cr = VisaWave_DoTransaction(pDataStruct);

		// Kill the scanning task
		ClessSample_Scan_KillScanningTask();
		ClessSample_Scan_TransacCloseDrivers();

		// Debug purpose : if you need to dump the data provided by the kernel
		if (ClessSample_Menu_IsTransactionDataDumpingOn())
			ClessSample_DumpData_DumpSharedBufferWithTitle (pDataStruct, "VISAWAVE DATA");

		// Get prefered card language (defaulty returned by the VisaWave kernel (if present in the kernel database)
		nCardHolderLang = merchLang; // By default, cardholder language is set to default language
		if (ClessSample_Common_RetrieveInfo (pDataStruct, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, &pInfo))
			nCardHolderLang = ClessSample_Term_GiveLangNumber(pInfo);
		
		// Get the TAG_VISAWAVE_TRANSACTION_CVM to identify the CVM to be performed :
		// 	- VISAWAVE_CVM_NO_CVM (0x01) : "No CVM" method has been applied.
		// 	- VISAWAVE_CVM_SIGNATURE (0x02) : "Signature" method has been applied.
		// 	- VISAWAVE_CVM_ONLINE_PIN (0x04) : "Online PIN" method has been applied.
		if (!__ClessSample_VisaWave_RetrieveCvmToApply (pDataStruct, &ucCvm))
		{
			ucCvm = VISAWAVE_CVM_NO_CVM;
		}

		if ((ucCvm == VISAWAVE_CVM_ONLINE_PIN) && (cr == KERNEL_STATUS_OFFLINE_APPROVED))
			cr = KERNEL_STATUS_ONLINE_AUTHORISATION;
		
		// CR analyse
		if (cr & KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK) // If mask has been set
		{
			switch (g_ListOfEvent)
			{
			case CAM0:			// Chip card
				if (ClessSample_Scan_TransacCam0(ulAmount, nCurrencyCode) == FALSE)
					GTL_Traces_TraceDebug ("ClessSample_VisaWave_PerformTransaction Pb Transac Cam 0");
				
				break;

			case SWIPE2:		// Swipe
				if (ClessSample_Scan_TransacSwipe2(ulAmount, nCurrencyCode) == FALSE)
					GTL_Traces_TraceDebug ("ClessSample_VisaWave_PerformTransaction Pb Transac Swipe 2");

				break;

			case USER_EVENT:	// User event (from main task), it indicates the task is going to be killed (because g_bScanning_task_to_be_killed has been set to TRUE by the custom application
				ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_USER, merchLang, nCardHolderLang);
				break;

			case KEYBOARD:		// Keyboard event
				ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_KEYBOARD, merchLang, nCardHolderLang);
				break;
				
			default:
				ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_STOPPED, merchLang, nCardHolderLang);
				HelperErrorSequence (WITHBEEP);
				Helper_WaitUserDisplay();
				break;
			}
		}
		else switch (cr)
		{
		case KERNEL_STATUS_OK:
			// A good transaction state must be finished by a approved, declined, ... 
			ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_ERROR_STATUS, merchLang, nCardHolderLang);
			if(!ClessSample_VisaWave_IsVisaAsiaGuiMode())
			{
				HelperErrorSequence (WITHBEEP);
				Helper_WaitUserDisplay();
			}
			else
			{
				Helper_PerformKOSequence();
			}
			break;

		case (KERNEL_STATUS_OFFLINE_APPROVED):

			if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
				Helper_Visa_DisplayAvailableAmount(HELPERS_VISAWAVE, pDataStruct, nCardHolderLang);

			if (ucCvm == VISAWAVE_CVM_SIGNATURE)
			{
				Helper_Visa_SignatureCVMIHM(auCustomerDisplayAvailable,merchLang,nCardHolderLang);
				if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
					ulStartSignatureTime = GTL_StdTimer_GetCurrent();
			}
			else
			{
				Helper_Visa_ApprovedIHM(HELPERS_VISAWAVE, OFFLINE,pDataStruct,auCustomerDisplayAvailable,merchLang,nCardHolderLang, WITH_AOSA);
				
				// Transaction shall be added to the batch
				bSaveInBatch = TRUE;
			}
			
			// Print a receipt only if signature requested or merchant need to print a receipt	
			ClessSample_Term_Read_Message(STD_MESS_PRINT_RECEIPT, merchLang, &tMsg);
			
			if (bLoopMode == 0)
			{
				if ((ucCvm == VISAWAVE_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30, merchLang)))
					ClessSample_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_VISA, APPROVED_TICKED, (ucCvm == VISAWAVE_CVM_SIGNATURE), nCardHolderLang, WITH_AOSA);
			}

			if (ucCvm == VISAWAVE_CVM_SIGNATURE)
			{
				if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
				{
					nTimeout = GTL_StdTimer_GetRemaining(ulStartSignatureTime, C_SIGNATURE_TIMEOUT/10); 
					if (nTimeout > 0)
						ttestall(0,nTimeout);
				}

				ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_OK, merchLang, &tMsg);
				if ((bLoopMode) || (HelperQuestionYesNo (&tMsg, 5, merchLang)))
				{
					Helper_Visa_SignatureOKIHM(HELPERS_VISAWAVE, pDataStruct,auCustomerDisplayAvailable,merchLang,nCardHolderLang);
					bSaveInBatch = TRUE;
				}
				else
				{
					Helper_Visa_SignatureKOIHM(HELPERS_VISAWAVE, pDataStruct,auCustomerDisplayAvailable,merchLang,nCardHolderLang);
				}
			}
			break;
			
		case (KERNEL_STATUS_ONLINE_AUTHORISATION):
			// Is Online Pin asked and possible ?
			if (ucCvm == VISAWAVE_CVM_ONLINE_PIN) // If OnLine Pin Requested
			{
				nPosition = SHARED_EXCHANGE_POSITION_NULL;
				if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_APPLI_PAN, &ulLgPan, &pPan) != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug ("ClessSample_VisaWave_PerformTransaction : Missing PAN for Online PIN");
					bOnlinePinError = TRUE; // On-line Pin cannot be made
				}

				ulAmount = 0;
				nPosition = SHARED_EXCHANGE_POSITION_NULL;
				if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_AMOUNT_AUTH_NUM, &ulLgAmount, &pAmount) != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug ("ClessSample_VisaWave_PerformTransaction : Missing Amount auth for Online PIN");
					bOnlinePinError = TRUE; // On-line Pin cannot be made : amount to display not available
				}
				else
				{
					GTL_Convert_DcbNumberToUl(pAmount, &ulAmount, ulLgAmount);
				}

				if (!bOnlinePinError)
				{
					// Warning, erase display must be made only if Pin input will be made on customer screen
					if (ClessSample_IsPinpadPresent())
					{
						char acDummyMsg[] = "";

						// Display dummy message to erase display
						tMsg.message = acDummyMsg;
						tMsg.coding = _ISO8859_;
						tMsg.file = GetCurrentFont();
						if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
							Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
						else
							Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
						Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
					}

					if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
						Helper_PerformCVMSequence();
					
					cr_pin_online = ClessSample_PinManagement_OnLinePinManagement ((unsigned char*)pPan, 1, ulAmount, C_PINENTRY_TIMEOUT, 10000, nCardHolderLang, &buffer_saisie);
					
					if (cr_pin_online == INPUT_PIN_ON)
					{
						// Add a tag for on-line authorisation
						cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_SAMPLE_ENCIPHERED_PIN_CODE, buffer_saisie.nombre , (const unsigned char *)buffer_saisie.donnees);
						if (cr != STATUS_SHARED_EXCHANGE_OK)
						{
							GTL_Traces_TraceDebug("ClessSample_VisaWave_PerformTransaction : Unable to add TAG_SAMPLE_ENCIPHERED_PIN_CODE in shared buffer (cr=%02x)", cr);
							bOnlinePinError = TRUE;
						}
					}
					else
					{
						bOnlinePinError = TRUE;
					}
				}
			}

			ucOnLineDeclined = FALSE;

			if (!bOnlinePinError)
			{
				Helper_Visa_OnlineProcessingIHM(HELPERS_VISAWAVE, pDataStruct, auCustomerDisplayAvailable,merchLang,nCardHolderLang);
		    		
				///////////////////////////////////////////////
				//////////// ON-LINE AUTHORISATION //////////// 
				///////////////////////////////////////////////
				if (ClessSample_FinancialCommunication_ManageAuthorisation (pDataStruct))
				{
					nPosition = SHARED_EXCHANGE_POSITION_NULL;
					
					if (GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EMV_AUTHORISATION_RESPONSE_CODE, &ulReadLength, &pReadValue) == STATUS_SHARED_EXCHANGE_OK)
					{
						if ((pReadValue[0] == 0x30) && (pReadValue[1] == 0x30))
						{
							if (ucCvm == VISAWAVE_CVM_SIGNATURE)
							{
								Helper_Visa_SignatureCVMIHM(auCustomerDisplayAvailable,merchLang,nCardHolderLang);
								if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
									ulStartSignatureTime = GTL_StdTimer_GetCurrent();
							}
							else
							{
								Helper_Visa_ApprovedIHM(HELPERS_VISAWAVE, ONLINE,pDataStruct,auCustomerDisplayAvailable,merchLang,nCardHolderLang, WITH_AOSA);

								// Transaction shall be added to the batch
								bSaveInBatch = TRUE;
							}
				
							// Print a receipt only if signature requested or merchant need to print a receipt
							ClessSample_Term_Read_Message(STD_MESS_PRINT_RECEIPT, merchLang, &tMsg);
							
							if (bLoopMode == 0)
							{
								if ((ucCvm == VISAWAVE_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30, merchLang)))
									ClessSample_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_VISA, APPROVED_TICKED, (ucCvm == VISAWAVE_CVM_SIGNATURE), nCardHolderLang, WITH_AOSA);
							}

							if(ucCvm == VISAWAVE_CVM_SIGNATURE)
							{
								if(ClessSample_VisaWave_IsVisaAsiaGuiMode())
								{
									nTimeout = GTL_StdTimer_GetRemaining(ulStartSignatureTime, 500); 
									if (nTimeout == 0)
										ttestall(0,nTimeout);
								}

								ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_OK, merchLang, &tMsg);
								if ((bLoopMode) || (HelperQuestionYesNo (&tMsg, 5, merchLang)))
								{
									Helper_Visa_SignatureOKIHM(HELPERS_VISAWAVE, pDataStruct,auCustomerDisplayAvailable,merchLang,nCardHolderLang);

									bSaveInBatch = TRUE;
								}
								else
								{
									Helper_Visa_SignatureKOIHM(HELPERS_VISAWAVE, pDataStruct,auCustomerDisplayAvailable,merchLang,nCardHolderLang);
								}
							}
						}
						else
						{
							// No Authorisation response code
							ucOnLineDeclined = TRUE;
						}
					}
					else
					{
						// No Authorisation response code
						ucOnLineDeclined = TRUE;
					}
				}
				else
				{
					// Unable to go online, offline decline
					ucOnLineDeclined = TRUE;
				}
			}
			else
			{
				Helper_Visa_PinEntryKOIHM(auCustomerDisplayAvailable,merchLang,nCardHolderLang);
			}
			
			if (ucOnLineDeclined) // Problem with communication or transaction rejected
			{
				Helper_Visa_DeclinedIHM(HELPERS_VISAWAVE, ONLINE, pDataStruct, auCustomerDisplayAvailable,merchLang,nCardHolderLang);
			}
			break;

		case (KERNEL_STATUS_USE_CONTACT_INTERFACE):
		case (VISAWAVE_STATUS_OVERSEA_CARD):
			nResult = CLESS_CR_MANAGER_RESTART_WO_CLESS;
			break;

		case (KERNEL_STATUS_COMMUNICATION_ERROR):
			nResult = CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY;
			break;
	
		case (KERNEL_STATUS_REMOVE_AID):
			nResult = CLESS_CR_MANAGER_REMOVE_AID;
			break;
		
		case (VISAWAVE_STATUS_PAYWAVE_CARD):
			nResult = VISAWAVE_STATUS_PAYWAVE_CARD;
			goto End;
			break;

		case (KERNEL_STATUS_OFFLINE_DECLINED):
		case (VISAWAVE_STATUS_DDA_FAILED):
			Helper_Visa_DeclinedIHM(HELPERS_VISAWAVE, OFFLINE, pDataStruct, auCustomerDisplayAvailable,merchLang,nCardHolderLang);
			break;
		
		default:
			GTL_Traces_TraceDebug ("ClessSample_VisaWave_PerformTransaction result = %02x", cr);
			Helper_Visa_ErrorIHM(auCustomerDisplayAvailable,merchLang,nCardHolderLang);
			break;
		}

		// Cless field must be stopped only if we don't try to work with an another AID
		if (nResult != CLESS_CR_MANAGER_REMOVE_AID)
			// Deselect the card
			ClessEmv_DeselectCard(0, TRUE, FALSE);

		// If the transaction does not restart from the begining, set the LEDs into the idle state
		if ((nResult != CLESS_CR_MANAGER_RESTART) && (nResult != CLESS_CR_MANAGER_REMOVE_AID))
		{
			// Check if transaction shall be saved in the batch
			if (bSaveInBatch)
				__ClessSample_VisaWave_AddRecordToBatch (pDataStruct);

			// Increment 
			ClessSample_Batch_IncrementTransactionSeqCounter();

			// If activated, dump all the kernel database
			if (ClessSample_Menu_IsTransactionDatabaseDumpingOn())
			{
				VisaWave_GetAllData(pDataStruct); // Get all the kernel data to print the receipt
				ClessSample_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATABASE DUMP");
			}
		}
	}
	
	// Additional possible processing :
	//	- Perform an online authorisation if necessary
	//	- Save the transaction in the batch if transaction is accepted
	//	- Perform CVM processing if necessary
	
End:

	// Transaction is completed, clear VisaWave kernel transaction data
	VisaWave_Clear ();

	return (nResult);
}


//! \brief Modify several parameters in relationship to AID before to use it.
//! \param[in] pShareStruct Share buffer given and modified by EntryPoint.
//! \param[in/out] pAidParameters parameters found to manage AID.
//!	\return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.
int ClessSample_VisaWave_ModifyAidParameters(T_SHARED_DATA_STRUCT *pKernelDataStruct, T_SHARED_DATA_STRUCT * pSharedStruct, T_SHARED_DATA_STRUCT * pAidParameters)
{
	// Local variables
	int cr;
	int nPositionElement;
	unsigned long ulReadLengthElement, ulAidReadLengthElement;
	unsigned char *pReadValueElement;
	unsigned char *pAidReadValueElement;

	// Protection against bad parameters
	if ((pSharedStruct == NULL) || (pAidParameters == NULL))
		return(FALSE);

	//////////////////////////////////////////////////////////
	// TAG_VISAWAVE_TERMINAL_TRANSACTION_QUALIFIERS management
	//////////////////////////////////////////////////////////
	
	// Warning, Entry Point modify the TAG_VISAWAVE_TERMINAL_TRANSACTION_QUALIFIERS parameters
	// First bit managed by EntryPoint : byte 2, bit 8 : Online cryptogram required / not required
	// Second bit managed by EntryPoint : byte 2, bit 7 : CVM required / not required

	// Find the TTQ from EP buffer
	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pSharedStruct, &nPositionElement, TAG_VISAWAVE_TERMINAL_TRANSACTION_QUALIFIERS, &ulReadLengthElement, (const unsigned char **)&pReadValueElement);
	if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
		return(FALSE);	// No TTQ found, what can we made ?
	
	// Find the TTQ in pAidParameters structure
	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_VISAWAVE_TERMINAL_TRANSACTION_QUALIFIERS, &ulAidReadLengthElement, (const unsigned char **)&pAidReadValueElement);
	if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
		return(FALSE);	// No TTQ found, what can we made ?

	// If parameters taken == Cless qVSDC
	if (pAidReadValueElement[0] & 0x20)
	// 		=> CVM required and Online Cryptogram required bits taken from Cless_debit_Aid parameters
	{
		pAidReadValueElement[1] &= 0x3F; 						// 00XX XXXX erase Online cryptogram required & CVM required bit
		pAidReadValueElement[1] |= pReadValueElement[1] & 0xC0; // Take Online cryptogram required & EntryPoint CVM bit value
	}
	// else
	else
	{
	//	if parameters taken == MSD (only)
		if (pAidReadValueElement[0] & 0x80)
		{
			//	=> CVM required and Online Cryptogram required bits taken from parameters (CLESSCUST.PAR)
			// pAidReadValueElement[1] allready ok !!!
		}
	}

	// Double Dip processing
	// The reader cannot accept the same card to perform the same transaction twice
	if(ClessSample_VisaWave_IsVisaAsiaGuiMode() && gs_bLastTransactionDataFound)
		__ClessSample_VisaWave_CheckLastTransaction(pKernelDataStruct);

	return (TRUE); // All parameters have been managed

}


//! \brief Add the transaction record in the batch file.
//! \param[in] pSharedData Shared buffer to be used to get all the record data.
//! \note For VisaWave, \a pSharedData is the one returned by the VisaWave kernel on the DoTransaction function.

static void __ClessSample_VisaWave_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData)
{
	int merchLang;

	if (!ClessSample_Batch_AddTransactionToBatch (pSharedData))
	{
		merchLang = PSQ_Give_Language();
		GTL_Traces_TraceDebug ("__ClessSample_VisaWave_AddRecordToBatch : Save transaction in batch failed");
		ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_BATCH_ERROR, merchLang, merchLang);
	}
}


//! \brief Get the double dip timeout value from the parameter file.
//! \param[out] pDoubleDipTimeOut the timeout value (in milliseconds).
//! \return
//!		- TRUE if tag is present.
//!		- FALSE else.
static int __ClessSample_VisaWave_GetDoubleDipTimeOut (unsigned long *pDoubleDipTimeOut)
{
	TLV_TREE_NODE pTimeOut;		// Node for Double Dip Timeout.
	unsigned char * pValue;
	unsigned int nDataLength;

	pValue = NULL;
	nDataLength = 0;

	pTimeOut = TlvTree_Find(pTreeCurrentParam, TAG_SAMPLE_DOUBLE_DIP_TIMEOUT, 0);

	if (pTimeOut != NULL)
	{
		pValue = TlvTree_GetData(pTimeOut);
		nDataLength = TlvTree_GetLength(pTimeOut);
	}

	if ((pValue != NULL) && (nDataLength != 0))
	{
		GTL_Convert_BinNumberToUl(pValue, pDoubleDipTimeOut, nDataLength);
		return (TRUE);
	}

	return (FALSE);
}

//! \brief Get the timeout value for card detection process from the parameter file.
//! \param[out] pNoCardTimeOut the timeout value (in milliseconds).
//! \return
//!		- TRUE if tag is present.
//!		- FALSE else.
int ClessSample_VisaWave_GetNoCardTimeOut (unsigned long *pNoCardTimeOut)
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

// Init the global data related to the last transaction performed
static void __ClessSample_VisaWave_InitLastTransactionData (void)
{
	// Init global data
	gs_nLastPANLength = 0;
	memset(gs_ucLastPAN,0,sizeof(gs_ucLastPAN));
	memset(gs_ucLastAmount,0,sizeof(gs_ucLastAmount));
	memset(&gs_LastDate,0,sizeof(DATE));
	gs_bLastTransactionDataFound = FALSE;
}

//! \brief Get the last transaction data saved in the batch.

void ClessSample_VisaWave_GetLastTransactionData (void)
{
	int ret;
	unsigned int nPosition;
	TLV_TREE_NODE hTree, hTreeBackup;
	int bFound;
	
	// Init global data
	__ClessSample_VisaWave_InitLastTransactionData();

	// Init local data
	bFound = FALSE;
	hTreeBackup = NULL;
	hTree = NULL;
	
	// Get the last transaction data
	ret = ClessSample_Disk_Open_MyDisk ();

	if (ret == FS_OK)
	{
		nPosition = 0;

		do
		{
			ret = ClessSample_TransactionFile_GetNextTransaction (&Transac_File, &hTree, &nPosition);

			if (ret == TRANS_FILE_OK)
			{
				if (hTreeBackup != NULL)
					TlvTree_Release(hTreeBackup);

				bFound = TRUE;
				hTreeBackup = hTree;
			}
		} while (ret == TRANS_FILE_OK);

		if (bFound)
			__ClessSample_VisaWave_SaveLastTransactionData (hTreeBackup);
		else
			GTL_Traces_TraceDebug ("ClessSample_VisaWave_GetLastTransactionData : Batch empty");

		if (hTree != NULL)
			TlvTree_Release(hTree);
		if (hTreeBackup != NULL)
			TlvTree_Release(hTreeBackup);

		// Unmount the volume
		ClessSample_Disk_Unmount (FILE_DISK_LABEL);
	}
	else
	{
		GTL_Traces_TraceDebug ("ClessSample_VisaWave_GetLastTransactionData : Cannot mount disk");
	}
}

//! \brief Save last transaction data contained in a TLV Tree node
//! \param[in] TlvTreeNode TLV : contains the last transaction data to be saved.

static void __ClessSample_VisaWave_SaveLastTransactionData (TLV_TREE_NODE TlvTreeNode)
{
	TLV_TREE_NODE pResearch;	// Working Node
	unsigned long ulTag;
	unsigned int nDataLength;					
	unsigned char *pValue;				
	unsigned int bAmountFound, bDateFound, bTimeFound, bPANFound;

	// Init local data
	bAmountFound = FALSE;
	bDateFound = FALSE;
	bTimeFound = FALSE;
	bPANFound = FALSE;

	// Parse the last transaction data
	if (TlvTreeNode != NULL)
	{
		pResearch = TlvTree_GetFirstChild (TlvTreeNode);

		while (pResearch != NULL)
		{
			// Get tag length
			nDataLength = TlvTree_GetLength(pResearch);
			// Get tag
			ulTag = TlvTree_GetTag (pResearch);
			
			if(ulTag == TAG_EMV_AMOUNT_AUTH_NUM)
			{
				memcpy(gs_ucLastAmount,(unsigned char *)TlvTree_GetData(pResearch),nDataLength);
				bAmountFound = TRUE;
			}
			if(ulTag == TAG_EMV_TRANSACTION_DATE)
			{
				pValue = TlvTree_GetData(pResearch);

				// Copy the last transaction Date in a DATE structure
				gs_LastDate.year[0]=(pValue[0]/16) + '0';
				gs_LastDate.year[1]=(pValue[0]%16) + '0';
				gs_LastDate.month[0]=(pValue[1]/16) + '0';
				gs_LastDate.month[1]=(pValue[1]%16) + '0';
				gs_LastDate.day[0]=(pValue[2]/16) + '0';
				gs_LastDate.day[1]=(pValue[2]%16) + '0';

				bDateFound = TRUE;
			}
			if(ulTag == TAG_EMV_TRANSACTION_TIME)
			{
				pValue = TlvTree_GetData(pResearch);

				// Copy the last transaction Time in a DATE structure
				gs_LastDate.hour[0]=(pValue[0]/16) + '0';
				gs_LastDate.hour[1]=(pValue[0]%16) + '0';
				gs_LastDate.minute[0]=(pValue[1]/16) + '0';
				gs_LastDate.minute[1]=(pValue[1]%16) + '0';
				gs_LastDate.second[0]=(pValue[2]/16) + '0';
				gs_LastDate.second[1]=(pValue[2]%16) + '0';

				bTimeFound = TRUE;
			}
			if(ulTag == TAG_EMV_APPLI_PAN)
			{
				// Save value to send it to the VisaWave kernel
				gs_nLastPANLength = nDataLength;
				memcpy(gs_ucLastPAN,(unsigned char *)TlvTree_GetData(pResearch),nDataLength);
			
				bPANFound = TRUE;
			}
			
			pResearch = TlvTree_GetNext (pResearch);
		}
	}

	if(bAmountFound && bDateFound && bTimeFound && bPANFound)
		gs_bLastTransactionDataFound = TRUE;
}



//! \brief Check last transaction data contained in a TLV Tree node
//! \param[in] pCurrentTransactionStruct : contains the current transaction data.

static void __ClessSample_VisaWave_CheckLastTransaction (T_SHARED_DATA_STRUCT *pCurrentTransactionStruct)
{
	unsigned char *pDate, *pTime, *pAmount;						// Current transaction data
	unsigned long ulDateLength, ulTimeLength, ulAmountLength;	// Current transaction data
	DATE Date;													// Current transaction dates
	int iTimeGap, iDayGap;										// Number of days/seconds between the 2 transactions
	unsigned long ulDoubleDipTimeOut;							// Double Dip timeout (in milliseconds)
	int cr, nPositionElement, bSameAmount;
	
	// First, get the Double Dip timeout value
	if(!__ClessSample_VisaWave_GetDoubleDipTimeOut (&ulDoubleDipTimeOut))
		return;

	// Init local data
	iDayGap = 0;
	iTimeGap = 0;
	bSameAmount = FALSE;

	// First get the data of the current transaction (Date, Time and Amount) from EP buffer
	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pCurrentTransactionStruct, &nPositionElement, TAG_EMV_AMOUNT_AUTH_NUM, &ulAmountLength, (const unsigned char **)&pAmount);
    if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug ("__ClessSample_VisaWave_CheckLastTransaction : an error occurred when getting the TAG_EMV_AMOUNT_AUTH_NUM tag");
		return;
	}
	
	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pCurrentTransactionStruct, &nPositionElement, TAG_EMV_TRANSACTION_DATE, &ulDateLength, (const unsigned char **)&pDate);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug ("__ClessSample_VisaWave_CheckLastTransaction : an error occurred when getting the TAG_EMV_TRANSACTION_DATE tag");
		return;	
	}
	
	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pCurrentTransactionStruct, &nPositionElement, TAG_EMV_TRANSACTION_TIME, &ulTimeLength, (const unsigned char **)&pTime);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug ("__ClessSample_VisaWave_CheckLastTransaction : an error occurred when getting the TAG_EMV_TRANSACTION_TIME tag");
		return;
	}
	
	// Copy the current transaction Date/Time in a DATE structure
	Date.year[0]=(pDate[0]/16) + '0';
	Date.year[1]=(pDate[0]%16) + '0';
	Date.month[0]=(pDate[1]/16) + '0';
	Date.month[1]=(pDate[1]%16) + '0';
	Date.day[0]=(pDate[2]/16) + '0';
	Date.day[1]=(pDate[2]%16) + '0';
	Date.hour[0]=(pTime[0]/16) + '0';
	Date.hour[1]=(pTime[0]%16) + '0';
	Date.minute[0]=(pTime[1]/16) + '0';
	Date.minute[1]=(pTime[1]%16) + '0';
	Date.second[0]=(pTime[2]/16) + '0';
	Date.second[1]=(pTime[2]%16) + '0';

	// Check if the transaction amount is the same amount used for the last transaction
	if (memcmp(gs_ucLastAmount, pAmount, ulAmountLength) == 0)
		bSameAmount = TRUE;
	
	iDayGap = ClessSample_Common_NumberOfDaysBetweenTwoDates (&gs_LastDate, &Date);
	iTimeGap = SLSQ_Ecart_heure_minute_seconde(&gs_LastDate,&Date);	

	// Double dip check: the same card cannot perform the same transaction within the timeout.
	if(iDayGap == 1)
		iTimeGap += 24*3600; // Add one day in seconds (86400)

	if((iTimeGap > 0) && ((unsigned int) iTimeGap < (ulDoubleDipTimeOut/1000)) && (iDayGap == 0 || iDayGap == 1) && bSameAmount)
	{
		// Add the tag to the data sent to the VisaWave kernel
		cr = GTL_SharedExchange_AddTag (pCurrentTransactionStruct, TAG_VISAWAVE_LAST_TRANSACTION_PAN, gs_nLastPANLength, gs_ucLastPAN);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug ("__ClessSample_VisaWave_CheckLastTransaction : an error occurred when adding the TAG_VISAWAVE_LAST_TRANSACTION_PAN tag");
			return;
		}
	}
}

//! \brief Check in the parameter file if the GUI mode to use is Visa Asia.

void ClessSample_VisaWave_SetVisaAsiaGuiMode (void)
{
	TLV_TREE_NODE pGuiMode;		// Node for Double Dip Timeout.
	unsigned char * pValue;
	unsigned int nDataLength;

	pValue = NULL;
	nDataLength = 0;

	pGuiMode = TlvTree_Find(pTreeCurrentParam, TAG_GENERIC_GUI_MODE, 0);

	if (pGuiMode != NULL)
	{
		pValue = TlvTree_GetData(pGuiMode);
		nDataLength = TlvTree_GetLength(pGuiMode);
	}

	if ((pValue != NULL) && (nDataLength != 0))
	{
		if (pValue[0] == CLESS_GUI_MODE_VISA_ASIA)
		{
			TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4 | 
						TPASS_LED_BLUE | TPASS_LED_YELLOW | TPASS_LED_GREEN | TPASS_LED_RED);

			gs_bIsVisaAsiaGuiMode = TRUE;
			return;
		}
	}

	gs_bIsVisaAsiaGuiMode = FALSE;
}

//! \brief Check if the Visa Asia GUI mode is activated.
//!	\return
//!		- TRUE if Visa Asia GUI mode is used.
//!		- FALSE else.
int ClessSample_VisaWave_IsVisaAsiaGuiMode (void)
{
	return (gs_bIsVisaAsiaGuiMode);
}
