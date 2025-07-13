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

const unsigned char ARC_00[]={0x30, 0x30};
const unsigned char ARC_08[]={0x30, 0x38};
const unsigned char ARC_10[]={0x31, 0x30};
const unsigned char ARC_11[]={0x31, 0x31};

// Period of time the contactless reader field is deactivated between the two taps of the Mobile CVM (Time in milliseconds)
#define	EXPRESSPAY_DOUBLE_TAP_TIME_DEFAULT		0x5DC		// Default value: : 1,5 seconds
#define	EXPRESSPAY_DOUBLE_TAP_TIME_MIN			0x3E8		// Min value: : 1 second
#define	EXPRESSPAY_DOUBLE_TAP_TIME_MAX			0xBB8		// Max value: : 3 seconds

#define C_TIME_100MS					10


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

word g_TimerTask;										// To store the different tasks ID.
t_topstack * g_tsTimer_task_handle;						// Handle of the timer task.

static word g_wCurrentTask;
static unsigned char g_bTimer_task_to_be_killed = FALSE;	// Global variable used to stop the timer task.
static int g_bTimerTaskRunning = FALSE;						// Indicates if the timer task is still running or if it is waiting to be killed.
static int g_bTimerExpired = FALSE;							// Global variable used to indicate that removal timer expired.
	
static unsigned long gs_ulStartRemovalTimerTime = 0;		// Removal Timer

static unsigned char gs_bTxnWentOnline = FALSE;				// Global variable that indicates if the transaction was able to go online during the first part of an EMV Full Online transaction.

static unsigned char gs_bMobileCVMperformed = FALSE;		// Global variable that indicates if Mobile CVM has been performed and if transaction must be restarted.


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __ClessSample_ExpressPay_AddExpressPaySpecificData (T_SHARED_DATA_STRUCT * pDataStruct);
static void __ClessSample_ExpressPay_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData);
static int __ClessSample_ExpressPay_RetrieveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm);
static T_Bool __ClessSample_ExpressPay_OnlinePinManagement (T_SHARED_DATA_STRUCT * pStructureForOnlineData, int nCardHolderLang);
static int __ClessSample_ExpressPay_ActionCodeDefaultCheck (void);
static int __ClessSample_ExpressPay_IsOnlineOnly (T_SHARED_DATA_STRUCT * pDataStruct);

static void __ClessSample_ExpressPay_KillTimerTask (void);
static int __ClessSample_ExpressPay_LaunchRemovalTimerTask (void);
static void __ClessSample_ExpressPay_InitTimerVariables (void);
static word __ClessSample_ExpressPay_StartTimerTask (void);
static void __ClessSample_ExpressPay_GetDoubleTapTime (unsigned long *pDoubleTapTime);
static void __ClessSample_ExpressPay_CloseFieldBefore2ndTap (void);
static void __ClessSample_ExpressPay_SetTxnRestartedIndicator (T_SHARED_DATA_STRUCT *pTransactionData);
static void __ClessSample_ExpressPay_AddIssuerScripts (T_SHARED_DATA_STRUCT *pTransactionData);



/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Unset the Mobile CVM global variable.

void ClessSample_ExpressPay_UnsetMobileCVM (void)
{
	gs_bMobileCVMperformed = FALSE;
}


//! \brief Get the ExpressPay CVM to perform.
//! \param[out] pCvm Retrieved transaction CVM :
//!		- \a EXPRESSPAY_CVM_NO_CVM No CVM to be performed.
//!		- \a EXPRESSPAY_CVM_SIGNATURE if signature shall be performed.
//!		- \a EXPRESSPAY_CVM_ONLINE_PIN if online PIN shall be performed.
//! \return
//!		- \ref TRUE if correctly retrieved.
//!		- \ref FALSE if an error occurred.

static int __ClessSample_ExpressPay_RetrieveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	* pCvm = EXPRESSPAY_CVM_NO_CVM; // Default result
	
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_EXPRESSPAY_TRANSACTION_CVM, &ulReadLength, &pReadValue);
	
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


//! \brief Fill buffer with specific ExpressPay for transaction.
//! \param[out] pDataStruct Shared exchange structure filled with the specific ExpressPay data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

static int __ClessSample_ExpressPay_AddExpressPaySpecificData (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int cr, nResult;
	object_info_t ObjectInfo;
	T_KERNEL_TRANSACTION_FLOW_CUSTOM sTransactionFlowCustom;
	unsigned char StepInterruption[KERNEL_PAYMENT_FLOW_STOP_LENGTH];// Bit field to stop payment flow,
																	// if all bit set to 0 => no stop during payment process
									                                // if right bit set to 1 : stop after payment step number 1
	unsigned char StepCustom[KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH]; 	// Bit field to custom payment flow,
																	// if all bit set to 0 => no stop during payment process
									                                // if right bit set to 1 : stop after payment step number 1
	
	if (pDataStruct == NULL)
	{
		GTL_Traces_TraceDebug("__ClessSample_ExpressPay_AddExpressPaySpecificData : Invalid Input data");
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
		GTL_Traces_TraceDebug("__ClessSample_ExpressPay_AddExpressPaySpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_STOP in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}
		
	
	// Customize steps
	ADD_STEP_CUSTOM(STEP_EXPRESSPAY_REMOVE_CARD,StepCustom); // To do GUI when ExpressPay card has been read
	ADD_STEP_CUSTOM(STEP_EXPRESSPAY_GET_CERTIFICATE, StepCustom); // To provide the CA key data for ODA
	
	if (ClessSample_IsBlackListPresent())	
		ADD_STEP_CUSTOM(STEP_EXPRESSPAY_EXCEPTION_FILE_GET_DATA, StepCustom); // To check if PAN is in the blacklist
	
	memcpy ((void*)&sTransactionFlowCustom, (void*)StepCustom, KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH);
	sTransactionFlowCustom.usApplicationType = ObjectInfo.application_type; // Kernel will call this application for customisation 
	sTransactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL; // Kernel will call SERVICE_CUSTOM_KERNEL service id for customisation 

	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_KERNEL_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__ClessSample_ExpressPay_AddExpressPaySpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_CUSTOM in shared buffer (cr=%02x)", cr);
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

static T_Bool __ClessSample_ExpressPay_OnlinePinManagement (T_SHARED_DATA_STRUCT * pStructureForOnlineData, int nCardHolderLang)
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

		cr = ExpressPay3_GetData (pDataRequest);

		if (cr != KERNEL_STATUS_OK)
		{
			GTL_Traces_TraceDebug("__ClessSample_ExpressPay_OnlinePinManagement : An error occurred when getting tags from the ExpressPay kernel (cr=%02x)", cr);
			nResult = B_FALSE;
			goto End;
		}

		// Tags have been got (if present), get the PAN
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pDataRequest, &nPosition, TAG_EMV_APPLI_PAN, &ulPanLength, &pPan) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug ("__ClessSample_ExpressPay_OnlinePinManagement : Missing PAN for Online PIN");
			nResult = B_FALSE;
			goto End;
		}

		// Get the transaction amount (numeric)
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pDataRequest, &nPosition, TAG_EMV_AMOUNT_AUTH_NUM, &ulAmountLength, &pAmount) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug ("__ClessSample_ExpressPay_OnlinePinManagement : Missing Amount for Online PIN");
			nResult = B_FALSE;
			goto End;
		}
		
		// Convert amount
		GTL_Convert_DcbNumberToUl(pAmount, &ulAmount, ulAmountLength);
		
		// Warning, erase display must be made only if Pin input will be made on customer screen
		if (ClessSample_IsPinpadPresent())
		{
			char acDummyMsg[] = "";

			// Display dummy message to erase display
			tMsg.message = acDummyMsg;
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
				GTL_Traces_TraceDebug ("__ClessSample_ExpressPay_OnlinePinManagement : Unable to add TAG_SAMPLE_ENCIPHERED_PIN_CODE in the shared buffer (cr = %02x)", cr);
				nResult = B_FALSE;
				goto End;
			}
		}
		else if (cr == CANCEL_INPUT)
		{
				GTL_Traces_TraceDebug ("__ClessSample_ExpressPay_OnlinePinManagement : input pin Cancelled");
				nResult = B_NON_INIT;
				goto End;
		}
	}

End:
	// Destroy the shared buffer if created
	if (pDataRequest != NULL)
		GTL_SharedExchange_DestroyShare (pDataRequest);

	return (nResult);
}


//! \brief Manage the debug mode for ExpressPay kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void ClessSample_ExpressPay_DebugActivation (int bActivate)
{
	T_SHARED_DATA_STRUCT * pSharedStructure;
	int nResult;
	unsigned char ucDebugMode = 0x00;
	
	if (bActivate)
		ucDebugMode = KERNEL_DEBUG_MASK_TRACES;
	
	pSharedStructure = GTL_SharedExchange_InitShared(256);
	
	if (pSharedStructure != NULL)
	{
		nResult = GTL_SharedExchange_AddTag(pSharedStructure, TAG_KERNEL_DEBUG_ACTIVATION, 1, &ucDebugMode);
		
		if (nResult != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_ExpressPay_DebugActivation : Unable to add TAG_KERNEL_DEBUG_ACTIVATION (nResult = %02x)", nResult);
		}
		else
		{
			nResult = ExpressPay3_DebugManagement(pSharedStructure);
			
			if (nResult != KERNEL_STATUS_OK)
			{
				GTL_Traces_TraceDebug("ClessSample_ExpressPay_DebugActivation : Error occurred during ExpressPay Debug activation (nResult = %02x)", nResult);
			}
		}
		
		// Destroy the shared buffer
		GTL_SharedExchange_DestroyShare(pSharedStructure);
	}
}



//! \brief Perform the ExpressPay kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int ClessSample_ExpressPay_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep)
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
	case (STEP_EXPRESSPAY_REMOVE_CARD):
		HelperRemoveCardSequence(pSharedData);
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_EXPRESSPAY_GET_CERTIFICATE):
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
			GTL_Traces_TraceDebug ("ClessSample_ExpressPay_CustomiseStep : CUPAR_GetCaKeyData failed");
		}
		
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_EXPRESSPAY_EXCEPTION_FILE_GET_DATA):
		// Get the PAN
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_EMV_APPLI_PAN, &ulPanLength, &pPan) != STATUS_SHARED_EXCHANGE_OK)
		{
			// Pan parameters is missing, we cannot check BlackList
			GTL_Traces_TraceDebug ("ClessSample_ExpressPay_CustomiseStep : PAN is missing for exception file checking");
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
			// Add TAG_KERNEL_PAN_IN_BLACK_LIST tag in the exchange buffer to indicate ExpressPay kernel the PAN is in the black list
			if (GTL_SharedExchange_AddTag (pSharedData, TAG_KERNEL_PAN_IN_BLACK_LIST, 1, &bPanInExceptionFile) != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_SharedExchange_ClearEx (pSharedData, FALSE);
				GTL_Traces_TraceDebug ("ClessSample_ExpressPay_CustomiseStep : Unable to add TAG_KERNEL_PAN_IN_BLACK_LIST in the shared buffer");
			}
		}

		nResult = KERNEL_STATUS_CONTINUE;
		break;

	// Other customisation steps could be defined if necessary
		
	default:
		GTL_Traces_TraceDebug ("ClessSample_ExpressPay_CustomiseStep : Step to customise (unknown) = %02x\n", ucCustomisationStep);
		break;
	}
	
	return (nResult);
}



//! \brief Calls the ExpressPay kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for ExpressPay transaction.
//!	\return
//!		- ExpressPay kernel result.

int ClessSample_ExpressPay_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct)
{
	unsigned char bLoopMode;
	int nResult = CLESS_CR_MANAGER_END;
	int cr, ret, nPosition;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	unsigned char ucCvm;
	unsigned char auCustomerDisplayAvailable;
	unsigned char * pInfo;
	int merchLang, nCardHolderLang;
	T_Bool bContinueWithOnlineAuthorisation = B_TRUE;
	MSGinfos tMsg;
	unsigned char bUnableToGoOnline = FALSE;
	unsigned char bARCOnlineApproved = FALSE;
	unsigned char bCommunicationResult;
	T_SHARED_DATA_STRUCT * pDataStructSav = NULL;

	// Loop mode information
	bLoopMode = ClessSample_Menu_IsTransactionLoopOn();

	gs_bTxnWentOnline = FALSE;
	
	merchLang = PSQ_Give_Language();
	auCustomerDisplayAvailable = Helper_IsClessCustomerDisplayAvailable();
	
	// Indicate ExpressPay kernel is going to be used (for customisation purposes)
	ClessSample_Customisation_SetUsedPaymentScheme (CLESS_SAMPLE_CUST_EXPRESSPAY);
	
	if (!__ClessSample_ExpressPay_AddExpressPaySpecificData(pDataStruct))
	{
		GTL_Traces_TraceDebug("ClessSample_ExpressPay_PerformTransaction : ClessSample_Fill_ExpressPayTransaction failed\n");
	}
	else
	{
		// Debug purpose : if you need to dump the data provided to the kernel
		///ClessSample_DumpData_DumpSharedBuffer(pDataStruct, 0);
		
		// If Mobile CVM has been performed, an indicator is set to identify that a transaction has been Restarted.
		if(gs_bMobileCVMperformed)
			__ClessSample_ExpressPay_SetTxnRestartedIndicator(pDataStruct);
		
		cr = ExpressPay3_DoTransaction(pDataStruct);

		// Memorize data to store it in Batch if necessary
		pDataStructSav = GTL_SharedExchange_InitShared(pDataStruct->ulDataLength + 1);
		GTL_SharedExchange_AddSharedBufferContent (pDataStructSav, pDataStruct);
		
		// Debug purpose : if you need to dump the data provided by the kernel
		if (ClessSample_Menu_IsTransactionDataDumpingOn())
			ClessSample_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATA RECORD");
		
		// Get prefered card language (defaulty returned by the ExpressPay kernel (if present in the kernel database)
		nCardHolderLang = merchLang; // By default, cardholder language is set to default language
		if (ClessSample_Common_RetrieveInfo (pDataStruct, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, &pInfo))
			nCardHolderLang = ClessSample_Term_GiveLangNumber(pInfo);

		// Get the TAG_EXPRESSPAY_TRANSACTION_CVM to identify the CVM to be performed :
		// 	- EXPRESSPAY_CVM_NO_CVM (0x01) : "No CVM" method has been applied.
		// 	- EXPRESSPAY_CVM_SIGNATURE (0x02) : "Signature" method has been applied.
		// 	- EXPRESSPAY_CVM_ONLINE_PIN (0x04) : "Online PIN" method has been applied.
		if (!__ClessSample_ExpressPay_RetrieveCvmToApply (pDataStruct, &ucCvm))
			ucCvm = EXPRESSPAY_CVM_NO_CVM;
		
Restart:
		switch (cr)
		{
			case (KERNEL_STATUS_OFFLINE_APPROVED):
			case (EXPRESSPAY_STATUS_EMV_FULL_ONLINE_APPROVED):

				if (ucCvm == EXPRESSPAY_CVM_SIGNATURE)
				{
					ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_SIGNATURE_REQUIRED, merchLang, nCardHolderLang);
				}
				else
				{
					if((cr == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_APPROVED) && gs_bTxnWentOnline)
						ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_APPROVED, merchLang, nCardHolderLang);
					else
						ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_OFFLINE_APPROVED, merchLang, nCardHolderLang);
				}

				ExpressPay3_GetAllData(pDataStruct); // Get all the kernel data to print the receipt

				if (bLoopMode == 0)
				{
					ClessSample_Term_Read_Message(STD_MESS_PRINT_RECEIPT, merchLang, &tMsg);
					if ((ClessSample_DumpData_DumpGetOutputId() != CUSTOM_OUTPUT_NONE) && ((ucCvm == EXPRESSPAY_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30, merchLang))))
						ClessSample_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_AMEX, APPROVED_TICKED, (ucCvm == EXPRESSPAY_CVM_SIGNATURE), nCardHolderLang, WITH_AOSA);
				}

				if (ucCvm == EXPRESSPAY_CVM_SIGNATURE)
				{
					ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_OK, merchLang, &tMsg);
					if (HelperQuestionYesNo (&tMsg, 30, merchLang))
					{
						ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_SIGNATURE_OK, merchLang, nCardHolderLang);
					}
					else
					{
						ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_SIGNATURE_KO, merchLang, nCardHolderLang);
					}
				}
				break;

			case (KERNEL_STATUS_OFFLINE_DECLINED):
			case (EXPRESSPAY_STATUS_EMV_FULL_ONLINE_DECLINED):

				if((cr == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_DECLINED) && gs_bTxnWentOnline)
					ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_ONLINE_DECLINED, merchLang, nCardHolderLang);
				else
					ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_OFFLINE_DECLINED, merchLang, nCardHolderLang);
				HelperErrorSequence(WITHBEEP);
				Helper_WaitUserDisplay();
				break;

			case (EXPRESSPAY_STATUS_MAGSTRIPE_ONLINE_AUTHORISATION):
			case (EXPRESSPAY_STATUS_EMV_PARTIAL_ONLINE_AUTHORISATION):
			case (EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION):
				if (ucCvm == EXPRESSPAY_CVM_ONLINE_PIN)
				{
					bContinueWithOnlineAuthorisation = __ClessSample_ExpressPay_OnlinePinManagement (pDataStruct, nCardHolderLang);
				}

				if (bContinueWithOnlineAuthorisation == B_TRUE)
				{
					if(cr == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
					{
						ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_EXPRESSPAY_SCREEN_PROCESSING, merchLang, nCardHolderLang);
					}
					else
					{
						ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_ONLINE_PROCESSING, merchLang, nCardHolderLang);
					}

					if(cr == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
						__ClessSample_ExpressPay_LaunchRemovalTimerTask ();

					bCommunicationResult = ClessSample_FinancialCommunication_ManageAuthorisation (pDataStruct);

					if(cr == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
					{
						// Kill the timer task
						__ClessSample_ExpressPay_KillTimerTask();

						// Removal timer expired, transaction is completed as partial online transaction
						if (g_bTimerExpired)
							cr = EXPRESSPAY_STATUS_EMV_PARTIAL_ONLINE_AUTHORISATION;
					}

					if (bCommunicationResult)
					{
						if(cr == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
						{
							// Full Online Transaction is performed
							// Get some data from the response to sent to the kernel
							nPosition = SHARED_EXCHANGE_POSITION_NULL;
							if (GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EMV_AUTHORISATION_RESPONSE_CODE, &ulReadLength, &pReadValue) == STATUS_SHARED_EXCHANGE_OK)
							{
								// ARC values of “00”, “08”, “10”, or “11”  indicate Approval.
								if((memcmp(pReadValue, ARC_00, 2) == 0) ||
									(memcmp(pReadValue, ARC_08, 2) == 0) ||
									(memcmp(pReadValue, ARC_10, 2) == 0) ||
									(memcmp(pReadValue, ARC_11, 2) == 0))
								{
									bARCOnlineApproved = TRUE;
									ret = GTL_SharedExchange_AddTag(pDataStruct, TAG_EXPRESSPAY_ARC_ONLINE_APPROVED, 1, &bARCOnlineApproved);
									if (ret != STATUS_SHARED_EXCHANGE_OK)
										GTL_Traces_TraceDebug("ClessSample_ExpressPay_PerformTransaction: Unable to add TAG_EXPRESSPAY_ARC_ONLINE_APPROVED in shared buffer (ret=%02x)", ret);
								}

								// If TAG_EMV_ISSUER_AUTHENTICATION_DATA tag is returned by the Issuer, the TAG_EMV_ISSUER_AUTHENTICATION_DATA data is still present in the pDataStruct and will be used by the kernel during Issuer Authentication processing.

								gs_bTxnWentOnline = TRUE;
							}
							else
							{
								bUnableToGoOnline = TRUE;
								ret = GTL_SharedExchange_AddTag(pDataStruct, TAG_EXPRESSPAY_UNABLE_TO_GO_ONLINE, 1, &bUnableToGoOnline);
								if (ret != STATUS_SHARED_EXCHANGE_OK)
									GTL_Traces_TraceDebug("ClessSample_ExpressPay_PerformTransaction: Unable to add TAG_EXPRESSPAY_UNABLE_TO_GO_ONLINE in shared buffer (ret=%02x)", ret);
							}
						}
						else // Magstripe Online or EMV Partial Online
						{
							nPosition = SHARED_EXCHANGE_POSITION_NULL;

							if (GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EMV_AUTHORISATION_RESPONSE_CODE, &ulReadLength, &pReadValue) == STATUS_SHARED_EXCHANGE_OK)
							{
								if((memcmp(pReadValue, ARC_00, 2) == 0) ||
									(memcmp(pReadValue, ARC_08, 2) == 0) ||
									(memcmp(pReadValue, ARC_10, 2) == 0) ||
									(memcmp(pReadValue, ARC_11, 2) == 0))
								{
									if (ucCvm == EXPRESSPAY_CVM_SIGNATURE)
									{
										ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_SIGNATURE_REQUIRED, merchLang, nCardHolderLang);
									}
									else
									{
										ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_APPROVED, merchLang, nCardHolderLang);
									}

									// Get all the kernel data to print the receipt
									ExpressPay3_GetAllData(pDataStruct);

									if (bLoopMode == 0)
									{
										ClessSample_Term_Read_Message(STD_MESS_PRINT_RECEIPT, merchLang, &tMsg);
										if ((ClessSample_DumpData_DumpGetOutputId() != CUSTOM_OUTPUT_NONE) && ((ucCvm == EXPRESSPAY_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30, merchLang))))
											ClessSample_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_AMEX, APPROVED_TICKED, (ucCvm == EXPRESSPAY_CVM_SIGNATURE), nCardHolderLang, WITH_AOSA);
									}

									if (ucCvm == EXPRESSPAY_CVM_SIGNATURE)
									{
										ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_OK, merchLang, &tMsg);
										if ((bLoopMode) || (HelperQuestionYesNo (&tMsg, 30, merchLang)))
										{
											ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_EXPRESSPAY_SCREEN_SIGNATURE_OK_ONLINE_APPROVED, merchLang, nCardHolderLang);
										}
										else
										{
											ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_SIGNATURE_KO, merchLang, nCardHolderLang);
										}
									}
								}
								else
								{
									// Authorisation response code do not indicates an Approved transaction
									ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_DECLINED, merchLang, nCardHolderLang);
								}
							}
							else
							{
								bUnableToGoOnline = TRUE;
							}
						}
					}
					else
					{
						if(cr == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
						{
							bUnableToGoOnline = TRUE;
							ret = GTL_SharedExchange_AddTag(pDataStruct, TAG_EXPRESSPAY_UNABLE_TO_GO_ONLINE, 1, &bUnableToGoOnline);
							if (ret != STATUS_SHARED_EXCHANGE_OK)
								GTL_Traces_TraceDebug("ClessSample_ExpressPay_PerformTransaction: Unable to add TAG_EXPRESSPAY_UNABLE_TO_GO_ONLINE in shared buffer (ret=%02x)", ret);
						}
						else // Magstripe Online or EMV Partial Online
						{
							bUnableToGoOnline = TRUE;
						}
					}

					if(cr == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
					{
						// Add Issuer Scripts in the data sent to the kernel
						__ClessSample_ExpressPay_AddIssuerScripts(pDataStruct);

						// EMV Full Online transaction is performed
						cr = ExpressPay3_DoTransactionPostProcessing(pDataStruct);
						goto Restart;
					}
					else // Magstripe Online or EMV Partial Online
					{
						if(bUnableToGoOnline)
						{
							// If an online only terminal is unable to go online, transaction is declined.
							// If SDA was requested but not performed because it is an EMV Partial Online transaction, transaction is declined.
							 if(__ClessSample_ExpressPay_IsOnlineOnly(pDataStruct) ||
								(cr == EXPRESSPAY_STATUS_MAGSTRIPE_ONLINE_AUTHORISATION) ||
								(cr == EXPRESSPAY_STATUS_EMV_PARTIAL_ONLINE_AUTHORISATION && __ClessSample_ExpressPay_ActionCodeDefaultCheck()))
							{
								// Default Action Code match, transaction is decline
								ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_OFFLINE_DECLINED, merchLang, nCardHolderLang);
							}
							else
							{
								// Default Action Code does not match, transaction is approved offline
								if (ucCvm == EXPRESSPAY_CVM_SIGNATURE)
								{
									ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_SIGNATURE_REQUIRED, merchLang, nCardHolderLang);
								}
								else
								{
									ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_OFFLINE_APPROVED, merchLang, nCardHolderLang);
								}

								ExpressPay3_GetAllData(pDataStruct); // Get all the kernel data to print the receipt

								if (bLoopMode == 0)
								{
									ClessSample_Term_Read_Message(STD_MESS_PRINT_RECEIPT, merchLang, &tMsg);
									if ((ClessSample_DumpData_DumpGetOutputId() != CUSTOM_OUTPUT_NONE) && ((ucCvm == EXPRESSPAY_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30, merchLang))))
										ClessSample_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_AMEX, APPROVED_TICKED, (ucCvm == EXPRESSPAY_CVM_SIGNATURE), nCardHolderLang, WITH_AOSA);
								}

								if (ucCvm == EXPRESSPAY_CVM_SIGNATURE)
								{
									ClessSample_Term_Read_Message(STD_MESS_SIGNATURE_OK, merchLang, &tMsg);
									if (HelperQuestionYesNo (&tMsg, 30, merchLang))
									{
										ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_SIGNATURE_OK, merchLang, nCardHolderLang);
									}
									else
									{
										ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_SIGNATURE_KO, merchLang, nCardHolderLang);
									}
								}
							}
						}
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

			case (KERNEL_STATUS_COMMUNICATION_ERROR):
				nResult = CLESS_CR_MANAGER_RESTART;
				break;

			case (KERNEL_STATUS_MOBILE):
				// ExpressPay 3.0 Terminal Specification Section 19.2.2.1
				// The cardholder is notified to withdraw and/or consult the mobile device (Card)
				ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_PHONE_INSTRUCTIONS, merchLang, nCardHolderLang);

				// The contactless reader field must be deactivated for a period of time (configurable in the range of one to three seconds, default value to be 1.5 seconds).
				__ClessSample_ExpressPay_CloseFieldBefore2ndTap();

				// The cardholder is notified to re-present the mobile device.

				// An indicator is set to identify that a transaction has been Restarted.
				gs_bMobileCVMperformed = TRUE;

				nResult = CLESS_CR_MANAGER_RESTART_DOUBLE_TAP;

				break;

			case (KERNEL_STATUS_CARD_BLOCKED):
			case (KERNEL_STATUS_APPLICATION_BLOCKED):
			case (KERNEL_STATUS_REMOVE_AID):
				nResult = CLESS_CR_MANAGER_REMOVE_AID;
				break;

			default: // Error case
				GTL_Traces_TraceDebug ("ExpressPay3_DoTransaction result = %02x", cr);
				ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_ERROR, merchLang, nCardHolderLang);
				HelperErrorSequence(WITHBEEP);
				Helper_WaitUserDisplay();
				break;
		}

		// Cless field must be stopped only if we don't try to work with an another AID
		if ((nResult != CLESS_CR_MANAGER_REMOVE_AID) && (nResult != CLESS_CR_MANAGER_RESTART_WO_CLESS))
			ClessEmv_DeselectCard(0, TRUE, FALSE);

		// If the transaction does not restart from the begining, set the LEDs into the idle state
		if ((nResult != CLESS_CR_MANAGER_RESTART) && (nResult != CLESS_CR_MANAGER_REMOVE_AID) && (nResult != CLESS_CR_MANAGER_RESTART_DOUBLE_TAP))
		{
			// Check if transaction shall be saved in the batch
			if (pDataStructSav != NULL)
				__ClessSample_ExpressPay_AddRecordToBatch (pDataStructSav);

			// Increment 
			ClessSample_Batch_IncrementTransactionSeqCounter();

			// If activated, dump all the kernel database
			if (ClessSample_Menu_IsTransactionDatabaseDumpingOn())
			{
				ExpressPay3_GetAllData(pDataStruct); // Get all the kernel data to print the receipt
				ClessSample_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATABASE DUMP");
			}
		}

		if (pDataStructSav != NULL)
		{
			GTL_SharedExchange_DestroyShare(pDataStructSav);
			pDataStructSav = NULL;
		}
	}

	// Transaction is completed, clear ExpressPay kernel transaction data
	ExpressPay3_Clear ();

	// Return result
	return (nResult);
}


//! \brief Check if the Default Action Codes match or not (TAG_EXPRESSPAY_INT_TAC_IAC_DEFAULT_MATCHED set to 1 by the ExpressPay kernel).
//! \return
//!		- \ref TRUE if Default Action codes match (decline the transaction).
//!		- \ref FALSE else (approve the transaction).

static int __ClessSample_ExpressPay_ActionCodeDefaultCheck (void)
{
	T_SHARED_DATA_STRUCT * pDataRequest;
	int cr, nResult = FALSE;
	int nPosition;
	const unsigned char * pValue;
	unsigned long ulLength;
			
	pDataRequest = GTL_SharedExchange_InitShared (128);

	if (pDataRequest != NULL)
	{
		// Clear shared buffer
		GTL_SharedExchange_ClearEx (pDataRequest, FALSE);

		// Indicate tag to be requested
		GTL_SharedExchange_AddTag (pDataRequest, TAG_EXPRESSPAY_INT_TAC_IAC_DEFAULT_MATCHED, 0, NULL);
		
		cr = ExpressPay3_GetData (pDataRequest);

		if (cr != KERNEL_STATUS_OK)
		{
			GTL_Traces_TraceDebug("__ClessSample_ExpressPay_ActionCodeDefaultCheck : An error occurred when getting tags from the ExpressPay kernel (cr=%02x)", cr);
			nResult = FALSE;
			goto End;
		}

		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pDataRequest, &nPosition, TAG_EXPRESSPAY_INT_TAC_IAC_DEFAULT_MATCHED, &ulLength, &pValue) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug ("__ClessSample_ExpressPay_ActionCodeDefaultCheck : Missing TAG_EXPRESSPAY_INT_TAC_IAC_DEFAULT_MATCHED");
			nResult = FALSE;
			goto End;
		}

		if(pValue[0])
			nResult = TRUE; // Default Action Codes match
	}
	
End:
	// Destroy the shared buffer if created
	if (pDataRequest != NULL)
		GTL_SharedExchange_DestroyShare (pDataRequest);

	return (nResult);
}


////////////////////////////////////////////
//// TASK FOR EMV FULL ONLINE TRANSACTION //
////////////////////////////////////////////

//! \brief Get the removal timeout value from the parameter file.
//! \param[out] pRemovalTimeOut the timeout value (in milliseconds).
//! \return
//!		- TRUE if tag is present.
//!		- FALSE else.
static int __ClessSample_ExpressPay_GetRemovalTimeOut (unsigned long *pRemovalTimeOut)
{
	TLV_TREE_NODE pTimeOut;
	unsigned char * pValue;
	unsigned int nDataLength;

	pValue = NULL;
	nDataLength = 0;

	pTimeOut = TlvTree_Find(pTreeCurrentParam, TAG_EXPRESSPAY_FULL_ONLINE_EMV_REMOVAL_TIMEOUT, 0);

	if (pTimeOut != NULL)
	{
		pValue = TlvTree_GetData(pTimeOut);
		nDataLength = TlvTree_GetLength(pTimeOut);
	}

	if ((pValue != NULL) && (nDataLength != 0))
	{
		GTL_Convert_BinNumberToUl(pValue, pRemovalTimeOut, nDataLength);
		return (TRUE);
	}

	return (FALSE);
}


/**
 * function:    __ClessSample_ExpressPay_StartTimerTask
 * @brief: Waits an event from custom (Online Authorization received) during XX secondes.
 * @brief: If the event is not received, ask for card removal.
 */

static word __ClessSample_ExpressPay_StartTimerTask (void)
{
	unsigned long ulRemovalTimeOut;	// Card removal timeout (in milliseconds)
	int nTimeout;
	int nLang;
	unsigned char auCustomerDisplayAvailable;
	
	g_bTimerTaskRunning = TRUE;		// Indicates the task is running
	g_TimerTask = CurrentTask();	// Get the Timer task ID and store it in a global variable

	// Start the removal timer
	gs_ulStartRemovalTimerTime = GTL_StdTimer_GetCurrent();

	nLang = PSQ_Give_Language();
	auCustomerDisplayAvailable = Helper_IsClessCustomerDisplayAvailable();

	// First, get the removal timeout value
	if(!__ClessSample_ExpressPay_GetRemovalTimeOut (&ulRemovalTimeOut))
		ulRemovalTimeOut = 0; // Perform a Partial Online transaction
	
	while (!g_bTimer_task_to_be_killed) // While the task is not to be killed by the custom application
	{
		if (g_bTimerExpired)	// Timeout expired, task is waiting to be killed
		{
			g_bTimerTaskRunning = FALSE; // Indicate to the custom application the task is waiting to be killed
			ttestall (0,0);		// Wait to be killed
		}

		// Test if removal timer expired
		nTimeout = GTL_StdTimer_GetRemaining(gs_ulStartRemovalTimerTime, ulRemovalTimeOut/10);
		if (nTimeout == 0)
		{
			// Timer expires before a response is received from the Acquirer
			g_bTimerExpired = TRUE;
			// Prompt for the removal of the card
			HelperRemoveCardSequence(NULL);

			// Clear the screen and display "Online request" message
			ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_ONLINE_PROCESSING, nLang, nLang);
		}
		
		if(!g_bTimerExpired)
			ttestall (USER_EVENT, 1);	// User event (from main task), it indicates the task is going to be killed (because g_bTimer_task_to_be_killed has been set to TRUE by the custom application)

	} // End While

	// The task is stopped by the main application (Online Response received)
	g_bTimerTaskRunning = FALSE; // Update global variable

	// Send the event to the main task
	if (SignalEvent (g_wCurrentTask, (tEvent)E_USER_EVENT) != cOK)
		GTL_Traces_DiagnosticText ("Timer task: Error when setting the event\n");

	ttestall (0,0); // Wait to be killed
	return TRUE;
}


/**
 * function:    __ClessSample_ExpressPay_InitTimerVariables
 * @brief: Initialise removal timer global variables
 * @param	void
 * @return	void
 */

static void __ClessSample_ExpressPay_InitTimerVariables (void)
{
	g_wCurrentTask = 0xFF;				// Init the custom application task number
	g_TimerTask = 0xFF;					// Init the scanning task number
	g_tsTimer_task_handle = NULL;		// Init the scanning task handle
	g_bTimer_task_to_be_killed = FALSE; // Task has not to be killed
	g_bTimerTaskRunning = FALSE;		//Task is not running
	g_bTimerExpired = FALSE;			// Removal timer has not expired
}

/**
 * function:    __ClessSample_ExpressPay_LaunchRemovalTimerTask
 * @brief: Launch the removal timer task.
 * @param	void
 * @return	OK if task correctly launch, KO else.
 */

static int __ClessSample_ExpressPay_LaunchRemovalTimerTask (void)
{
	// Init global variables
	__ClessSample_ExpressPay_InitTimerVariables();

	// Get the main task id
	g_wCurrentTask = CurrentTask();

	// Launch the timer task
	g_tsTimer_task_handle = fork (&__ClessSample_ExpressPay_StartTimerTask, NULL, -1);

	// The task cannot be created
	if (g_tsScanning_task_handle == NULL)
		return KO;
	
	return OK;
}


/**
 * function:    __ClessSample_ExpressPay_KillTimerTask
 * @brief: Kill the removal timer task.
 * @param	void
 * @return	void
 */
static void __ClessSample_ExpressPay_KillTimerTask (void)
{
	if (g_tsTimer_task_handle != NULL) // If the task is launched
	{
		g_bTimer_task_to_be_killed = TRUE; // To Stop the task (if not already waiting to be killed because of timeout expired)

		// Send an event to make the task ready to be killed
		if (SignalEvent (g_TimerTask, (tEvent)E_USER_EVENT) != cOK)
			GTL_Traces_DiagnosticText ("Main task: Error when setting the event\n");

		while (g_bTimerTaskRunning == TRUE) // While the task has not terminated processing
		{
			// Waits a little
			ttestall (USER_EVENT,1);
		}

		// The task is ready to be killed, kill it
		kill(g_tsTimer_task_handle, "-*");
		g_tsTimer_task_handle = NULL;
	}
}


//! \brief Get the double tap time value from the parameter file.
//! \param[out] pDoubleTapTime the double tap time value (in milliseconds).

static void __ClessSample_ExpressPay_GetDoubleTapTime (unsigned long *pDoubleTapTime)
{
	TLV_TREE_NODE pTime;		// Node for Double Tap Time.
	unsigned char * pValue;
	unsigned int nDataLength;

	pValue = NULL;
	nDataLength = 0;
	
	pTime = TlvTree_Find(pTreeCurrentParam, TAG_SAMPLE_EXPRESSPAY_DOUBLE_TAP_TIME, 0);

	if (pTime != NULL)
	{
		pValue = TlvTree_GetData(pTime);
		nDataLength = TlvTree_GetLength(pTime);
	}

	if ((pValue != NULL) && (nDataLength != 0))
	{
		GTL_Convert_BinNumberToUl(pValue, pDoubleTapTime, nDataLength);

		if((*pDoubleTapTime < EXPRESSPAY_DOUBLE_TAP_TIME_MIN) || (*pDoubleTapTime > EXPRESSPAY_DOUBLE_TAP_TIME_MAX))
			*pDoubleTapTime = EXPRESSPAY_DOUBLE_TAP_TIME_DEFAULT;
	}
	else
	{
		*pDoubleTapTime = EXPRESSPAY_DOUBLE_TAP_TIME_DEFAULT;
	}
}


//! \brief Deactivate the contactless field for a period of time between the two taps of the Mobile CVM.

static void __ClessSample_ExpressPay_CloseFieldBefore2ndTap (void)
{
	unsigned long ulDoubleTapTime;		// Double Tap time (in milliseconds)

	__ClessSample_ExpressPay_GetDoubleTapTime(&ulDoubleTapTime);

	// Stop Cless Field
	ClessEmv_CloseDriver();

	// Perform a double bip (600 ms)
	HelperErrorSequence (WITHBEEP);

	// Wait the remaining time
	ttestall(0, (ulDoubleTapTime/10) - (6 * C_TIME_100MS));
}


//! \brief Add a tag in the transaction data to indicate to the Expresspay kernel that the transaction has been restarted.
//! \param[in/out] pTransactionData Transaction data.

static void __ClessSample_ExpressPay_SetTxnRestartedIndicator (T_SHARED_DATA_STRUCT *pTransactionData)
{
	int ret;
	unsigned char ucTxnRestarted;

	ucTxnRestarted = 0x01;
	
	ret = GTL_SharedExchange_AddTag(pTransactionData, TAG_EXPRESSPAY_MOBILE_TRANSACTION_RESTARTED, 1, &ucTxnRestarted);
	if (ret != STATUS_SHARED_EXCHANGE_OK)
		GTL_Traces_TraceDebug("__ClessSample_ExpressPay_SetTxnRestartedIndicator: Unable to add TAG_EXPRESSPAY_MOBILE_TRANSACTION_RESTARTED in shared buffer (ret=%02x)", ret);
}


//! \brief Add Issuer Scripts received from the authorization in the transaction data sent to the Expresspay kernel.
//! \param[in/out] pTransactionData Transaction data.

static void __ClessSample_ExpressPay_AddIssuerScripts (T_SHARED_DATA_STRUCT *pTransactionData)
{
	T_SHARED_DATA_STRUCT * pTmpScripts71, * pTmpScripts72;
	T_BER_TLV_DECODE_STRUCT BerTlvStruct;
	int nResult, cr;
	int BytesRead;
	BER_TLV_TAG ReadTag;
	T_TI_LENGTH ReadLength;
	T_TI_VALUE  ReadValue;
	

	pTmpScripts71 = GTL_SharedExchange_InitLocal(512);
	pTmpScripts72 = GTL_SharedExchange_InitLocal(512);

	if ((pTmpScripts71 != NULL) && (pTmpScripts72 != NULL))
	{
		GTL_BerTlvDecode_Init (&BerTlvStruct, pTransactionData->nPtrData, pTransactionData->ulDataLength);

		// Parse Script  T1:71 or 72 L1 V1 ... Tn:71 or 72 Ln Vn
		for (;;)
		{
			//! \brief Parse the next tag in the BER-TLV structure.
			cr = GTL_BerTlvDecode_ParseTlv (&BerTlvStruct, &ReadTag, &ReadLength, (BER_TLV_VALUE*)&ReadValue, (unsigned char)FALSE, &BytesRead);

			if (cr == STATUS_BER_TLV_END)
				break ;

			if (cr == STATUS_BER_TLV_OK)
			{
				if (ReadTag == TAG_EMV_ISSUER_SCRIPT_TEMPLATE_1)
				{
					nResult = GTL_SharedExchange_AddTag(pTmpScripts71, ReadTag, ReadLength, ReadValue);
					if (nResult != STATUS_SHARED_EXCHANGE_OK)
						GTL_Traces_TraceDebug("__ClessSample_ExpressPay_AddIssuerScripts : Unable to add TAG_EMV_ISSUER_SCRIPT_TEMPLATE_1 (nResult = %02x)", nResult);
				}
				if(ReadTag == TAG_EMV_ISSUER_SCRIPT_TEMPLATE_2)
				{
					nResult = GTL_SharedExchange_AddTag(pTmpScripts72, ReadTag, ReadLength, ReadValue);
					if (nResult != STATUS_SHARED_EXCHANGE_OK)
						GTL_Traces_TraceDebug("__ClessSample_ExpressPay_AddIssuerScripts : Unable to add TAG_EMV_ISSUER_SCRIPT_TEMPLATE_2 (nResult = %02x)", nResult);
				}
			}
			else
				break; // An error occurs
		} // end of loop about Script parsing


		// Add TAG_EXPRESSPAY_ISSUER_SCRIPT_71_LIST and TAG_EXPRESSPAY_ISSUER_SCRIPT_72_LIST tags in the data sent to the kernel
		if (pTmpScripts71->ulDataLength)
		{
			nResult = GTL_SharedExchange_AddTag(pTransactionData, TAG_EXPRESSPAY_ISSUER_SCRIPT_71_LIST, pTmpScripts71->ulDataLength, pTmpScripts71->nPtrData);
			if (nResult != STATUS_SHARED_EXCHANGE_OK)
				GTL_Traces_TraceDebug("__ClessSample_ExpressPay_AddIssuerScripts : Unable to add TAG_EXPRESSPAY_ISSUER_SCRIPT_71_LIST (nResult = %02x)", nResult);
		}

		if (pTmpScripts72->ulDataLength)
		{
			nResult = GTL_SharedExchange_AddTag(pTransactionData, TAG_EXPRESSPAY_ISSUER_SCRIPT_72_LIST, pTmpScripts72->ulDataLength, pTmpScripts72->nPtrData);
			if (nResult != STATUS_SHARED_EXCHANGE_OK)
				GTL_Traces_TraceDebug("__ClessSample_ExpressPay_AddIssuerScripts : Unable to add TAG_EXPRESSPAY_ISSUER_SCRIPT_72_LIST (nResult = %02x)", nResult);
		}
	}
	else
		GTL_Traces_TraceDebug("__ClessSample_ExpressPay_AddIssuerScripts : GTL_SharedExchange_InitLocal error");

	// Destroy the local buffers
	if (pTmpScripts71)
		GTL_SharedExchange_DestroyLocal(pTmpScripts71);
	if (pTmpScripts72)
		GTL_SharedExchange_DestroyLocal(pTmpScripts72);
}


//! \brief Check if the terminal is online only.

static int __ClessSample_ExpressPay_IsOnlineOnly (T_SHARED_DATA_STRUCT * pDataStruct)
{
	const unsigned char * pTerminalType;
	int nPosition;
	unsigned long ulLength;
	int nResult = FALSE;

	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_TERMINAL_TYPE, &ulLength, &pTerminalType) == STATUS_SHARED_EXCHANGE_OK)
	{
		if((pTerminalType[0] == CLESS_SAMPLE_TERM_TYPE_FINANCIAL_ATT_ONLINE_ONLY) ||
			(pTerminalType[0] == CLESS_SAMPLE_TERM_TYPE_FINANCIAL_UNATT_ONLINE_ONLY) ||
			(pTerminalType[0] == CLESS_SAMPLE_TERM_TYPE_MERCHANT_ATT_ONLINE_ONLY) ||
			(pTerminalType[0] == CLESS_SAMPLE_TERM_TYPE_MERCHANT_UNATT_ONLINE_ONLY) ||
			(pTerminalType[0] == CLESS_SAMPLE_TERM_TYPE_CARDHOLDER_UNATT_ONLINE_ONLY))
		{
			nResult = TRUE;
		}
	}

	return (nResult);
}

//! \brief Add the transaction record in the batch file.
//! \param[in] pSharedData Shared buffer to be used to get all the record data.
//! \note For ExpressPay, \a pSharedData is the one returned by the ExpressPay kernel on the DoTransaction function.

static void __ClessSample_ExpressPay_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData)
{
	int merchLang;

	if (!ClessSample_Batch_AddTransactionToBatch (pSharedData))
	{
		merchLang = PSQ_Give_Language();
		GTL_Traces_TraceDebug ("__ClessSample_ExpressPay_AddRecordToBatch : Save transaction in batch failed");
		ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_BATCH_ERROR, merchLang, merchLang);
	}
}
