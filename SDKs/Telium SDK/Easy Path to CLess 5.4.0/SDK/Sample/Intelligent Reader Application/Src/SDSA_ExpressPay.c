/**
 * \file	SDSA_ExpressPay.c
 * \brief	Manages the interface with the ExpressPay contactless kernel.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2008 Ingenico, rue claude Chappe,\n
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

#include "SDSA_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

// Period of time the contactless reader field is deactivated between the two taps of the Mobile CVM (Time in milliseconds)
#define	EXPRESSPAY_DOUBLE_TAP_TIME_DEFAULT		0x5DC		// Default value: : 1,5 seconds
#define	EXPRESSPAY_DOUBLE_TAP_TIME_MIN			0x3E8		// Min value: : 1 second
#define	EXPRESSPAY_DOUBLE_TAP_TIME_MAX			0xBB8		// Max value: : 3 seconds

#define C_TIME_100MS					10


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

static unsigned char gs_bMobileCVMperformed = FALSE;		// Global variable that indicates if Mobile CVM has been performed and if transaction must be restarted.


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __SDSA_ExpressPay_AddExpressPaySpecificData (T_SHARED_DATA_STRUCT * pDataStruct);
static void __SDSA_ExpressPay_GetDoubleTapTime (unsigned long *pDoubleTapTime);
static void __SDSA_ExpressPay_CloseFieldBefore2ndTap (void);
static void __SDSA_ExpressPay_SetTxnRestartedIndicator (T_SHARED_DATA_STRUCT *pTransactionData);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Unset the Mobile CVM global variable.

void SDSA_ExpressPay_UnsetMobileCVM (void)
{
	gs_bMobileCVMperformed = FALSE;
}


//! \brief Get the ExpressPay CVM to perform.
//! \param[out] pCvm Retreived transaction CVM :
//!		- \a EXPRESSPAY_CVM_NO_CVM No CVM to be performed.
//!		- \a EXPRESSPAY_CVM_SIGNATURE if signature shall be performed.
//!		- \a EXPRESSPAY_CVM_ONLINE_PIN if online PIN shall be performed.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

static int __SDSA_ExpressPay_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm)
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
	
	// Get the CVM to perform
	* pCvm = pReadValue[0];
	
End:	
	return (nResult);
}


//! \brief Fill buffer with specific ExpressPay data for transaction customisation/interruption.
//! \param[out] pDataStruct Shared exchange structure filled with the specific ExpressPay data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

static int __SDSA_ExpressPay_AddExpressPaySpecificData (T_SHARED_DATA_STRUCT * pDataStruct)
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
		GTL_Traces_TraceDebug("__SDSA_ExpressPay_AddExpressPaySpecificData : Invalid Input data");
		nResult = FALSE;
		goto End;
	}
	
    // Init parameters
	memset(StepInterruption, 0, sizeof(StepInterruption));	// Default Value : not stop on process
	memset(StepCustom, 0, sizeof(StepCustom));				// Default Value : not stop on process
	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
	nResult = TRUE;

	
	// Add a tag for Do_Txn management that indicates the steps on which the kernel shall stop the processing and give hand back to the custom application
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_STOP, KERNEL_PAYMENT_FLOW_STOP_LENGTH, (const unsigned char *)StepInterruption);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_ExpressPay_AddExpressPaySpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_STOP in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}
		
	// Indicate the steps on which the kernel shall call the custom application for step customisation
    ADD_STEP_CUSTOM(STEP_EXPRESSPAY_REMOVE_CARD,StepCustom);		// To do GUI when ExpressPay card has been read
	ADD_STEP_CUSTOM(STEP_EXPRESSPAY_GET_CERTIFICATE, StepCustom);	// To provide the CA key data for ODA
	
	if (SDSA_IsBlackListPresent())	
		ADD_STEP_CUSTOM(STEP_EXPRESSPAY_EXCEPTION_FILE_GET_DATA, StepCustom); // To check if PAN is in the blacklist
	
	memcpy ((void*)&sTransactionFlowCustom, (void*)StepCustom, KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH);
	sTransactionFlowCustom.usApplicationType = ObjectInfo.application_type; // Kernel will call this application for customisation 
	sTransactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL;				// Kernel will call SERVICE_CUSTOM_KERNEL service id for customisation 

	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_KERNEL_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_ExpressPay_AddExpressPaySpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_CUSTOM in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}
	
End:
	return (nResult);
}



//! \brief Manage the debug mode for ExpressPay kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void SDSA_ExpressPay_DebugActivation (int bActivate)
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
			GTL_Traces_TraceDebug("SDSA_ExpressPay_DebugActivation : Unable to add TAG_KERNEL_DEBUG_ACTIVATION (nResult = %02x)", nResult);
		}
		else
		{
			nResult = ExpressPay3_DebugManagement(pSharedStructure);
			
			if (nResult != KERNEL_STATUS_OK)
			{
				GTL_Traces_TraceDebug("SDSA_ExpressPay_DebugActivation : Error occured during ExpressPay Debug activation (nResult = %02x)", nResult);
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

int SDSA_ExpressPay_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep)
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
		// Display remove card message, manage leds and buzzer
		HelperRemoveCardSequence(pSharedData);
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_EXPRESSPAY_GET_CERTIFICATE):
		// The ExpressPay kernel calls the custom application to request the transaction certificate.
		// The application shall provide the CA public key modulus and the CA public key exponent to the kernel to perform ODA.
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
		
		// Get the CA Key data according to the RID and the CA Key index.
		if (!SDSA_Parameters_GetCaKeyData (pTreeCurrentParam, ucCapkIndex, ucRid, pSharedData))
		{
			GTL_Traces_TraceDebug ("SDSA_ExpressPay_CustomiseStep : SDSA_Parameters_GetCaKeyData failed");
		}
		
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_EXPRESSPAY_EXCEPTION_FILE_GET_DATA):
		// Get the PAN
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_EMV_APPLI_PAN, &ulPanLength, &pPan) != STATUS_SHARED_EXCHANGE_OK)
		{
			// Pan parameters is missing, we cannot check BlackList
			GTL_Traces_TraceDebug ("SDSA_ExpressPay_CustomiseStep : PAN is missing for exception file checking");
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
		bPanInExceptionFile = SDSA_BlackListIsPan((int)ulPanLength, pPan, (int)(pPanSeqNumber[0]));

		GTL_SharedExchange_ClearEx (pSharedData, FALSE);

		if (bPanInExceptionFile)
		{
			// Add TAG_KERNEL_PAN_IN_BLACK_LIST tag in the exchange buffer to indicate ExpressPay kernel the PAN is in the black list
			if (GTL_SharedExchange_AddTag (pSharedData, TAG_KERNEL_PAN_IN_BLACK_LIST, 1, &bPanInExceptionFile) != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_SharedExchange_ClearEx (pSharedData, FALSE);
				GTL_Traces_TraceDebug ("SDSA_ExpressPay_CustomiseStep : Unable to add TAG_KERNEL_PAN_IN_BLACK_LIST in the shared buffer");
			}
		}

		nResult = KERNEL_STATUS_CONTINUE;
		break;

	// Other customisation steps could be defined if necessary
		
    default:
    	GTL_Traces_TraceDebug ("SDSA_ExpressPay_CustomiseStep : Step to customise (unknown) = %02x\n", ucCustomisationStep);
    	break;
    }
    
    return (nResult);
}



//! \brief Calls the ExpressPay kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for ExpressPay transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- ExpressPay kernel result.

int SDSA_ExpressPay_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult = CLESS_CR_MANAGER_END;
	int cr;
	unsigned char ucCvm;


	// Indicate ExpressPay kernel is going to be used (for customisation purposes)
	SDSA_Customisation_SetUsedPaymentScheme (SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);
	
	// Fill buffer with specific ExpressPay data for transaction customisation/interruption
	if (!__SDSA_ExpressPay_AddExpressPaySpecificData(pDataStruct))
	{
	    GTL_Traces_TraceDebug("SDSA_ExpressPay_PerformTransaction : SDSA_Fill_ExpressPayTransaction failed\n");
	}
	else
	{
		// If Mobile CVM has been performed, an indicator is set to identify that a transaction has been Restarted.
		if(gs_bMobileCVMperformed)
			__SDSA_ExpressPay_SetTxnRestartedIndicator(pDataStruct);

		// Call the ExpressPay kernel that will perform the transaction
		cr = ExpressPay3_DoTransaction(pDataStruct);
		
		// Set language with preferred card language (if present in the kernel database)
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);

		// Get the TAG_EXPRESSPAY_TRANSACTION_CVM to identify the CVM to be performed :
		// 	- EXPRESSPAY_CVM_NO_CVM (0x01) : "No CVM" method has been applied.
		// 	- EXPRESSPAY_CVM_SIGNATURE (0x02) : "Signature" method has been applied.
		// 	- EXPRESSPAY_CVM_ONLINE_PIN (0x04) : "Online PIN" method has been applied.
		if (!__SDSA_ExpressPay_RetreiveCvmToApply (pDataStruct, &ucCvm))
		{
			ucCvm = EXPRESSPAY_CVM_NO_CVM;
		}

		// Get the transaction result and perform specific actions (display message...)
		switch (cr)
		{
		case (KERNEL_STATUS_OFFLINE_APPROVED):
			ExpressPay3_GetAllData(pDataStruct); // Get all the kernel data to print the receipt
			nResult = SDI_STATUS_APPROVED;
			break;

		case (EXPRESSPAY_STATUS_EMV_FULL_ONLINE_APPROVED):
			ExpressPay3_GetAllData(pDataStruct); // Get all the kernel data to print the receipt
			nResult = EXPRESSPAY_STATUS_EMV_FULL_ONLINE_APPROVED;
			break;
		
		case (KERNEL_STATUS_OFFLINE_DECLINED):
			nResult = SDI_STATUS_DECLINED;
			break;

		case (EXPRESSPAY_STATUS_EMV_FULL_ONLINE_DECLINED):
			nResult = EXPRESSPAY_STATUS_EMV_FULL_ONLINE_DECLINED;
			break;

		case (EXPRESSPAY_STATUS_MAGSTRIPE_ONLINE_AUTHORISATION):
			if (ucCvm == EXPRESSPAY_CVM_ONLINE_PIN)
				HelperLedsOff();
			nResult = EXPRESSPAY_STATUS_MAGSTRIPE_ONLINE_AUTHORISATION;
			break;

		case (EXPRESSPAY_STATUS_EMV_PARTIAL_ONLINE_AUTHORISATION):
			if (ucCvm == EXPRESSPAY_CVM_ONLINE_PIN)
				HelperLedsOff();
			nResult = EXPRESSPAY_STATUS_EMV_PARTIAL_ONLINE_AUTHORISATION;
			break;

		case (EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION):
			nResult = EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION;
			break;
		
		case (KERNEL_STATUS_USE_CONTACT_INTERFACE):
			nResult = SDI_STATUS_USE_OTHER_INTERFACE;
			break;
		
		case (KERNEL_STATUS_COMMUNICATION_ERROR):
			nResult = CLESS_CR_MANAGER_RESTART;
			ExpressPay3_Clear(); // If restart is required, kernel database shall be cleared
			break;

		case (KERNEL_STATUS_MOBILE):
			// Update the transaction status
			SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_DOUBLE_TAP);
			
			Helper_DisplayMessage(STD_MESS_PHONE_INSTRUCTIONS_L1, ERASE, HELPERS_CUSTOMER_LINE_1, HELPERS_ALIGN_CENTER, LEDSOFF);
			Helper_DisplayMessage(STD_MESS_PHONE_INSTRUCTIONS_L2, NO_ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, NOLEDSOFF);
							
			// The contactless reader field must be deactivated for a period of time (configurable in the range of one to three seconds, default value to be 1.5 seconds).
			__SDSA_ExpressPay_CloseFieldBefore2ndTap();

			// The cardholder is notified to re-present the mobile device.
		
			// An indicator is set to identify that a transaction has been Restarted.
			gs_bMobileCVMperformed = TRUE;

			ExpressPay3_Clear(); // If restart is required, kernel database shall be cleared
			nResult = CLESS_CR_MANAGER_RESTART_DOUBLE_TAP;
			break;

		case (KERNEL_STATUS_CARD_BLOCKED):
		case (KERNEL_STATUS_APPLICATION_BLOCKED):
		case (KERNEL_STATUS_REMOVE_AID):
			nResult = CLESS_CR_MANAGER_REMOVE_AID;
			ExpressPay3_Clear(); // If restart is required, kernel database shall be cleared
			break;		
			
		default: // Error case
			GTL_Traces_TraceDebug ("ExpressPay3_DoTransaction result = %02x", cr);
			break;
		}

		// Send data to the CST application. If TAG_SDSA_LIST_OF_OUTPUT_TAGS is not provided, default tag list is returned.
        if ((nResult != CLESS_CR_MANAGER_REMOVE_AID) && (nResult != CLESS_CR_MANAGER_RESTART) && (nResult != CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY) && (nResult != CLESS_CR_MANAGER_RESTART_DOUBLE_TAP))		
        {
		    if(!SDSA_Common_GetListOfOutputTags(hOutputTlvTree))
			    SDSA_Common_CopyDataStructInTLVTree(pDataStruct,hOutputTlvTree);	
		}
	}
		
	// Return result
	return (nResult);
}



//! \brief Calls the ExpressPay kernel to perform the the post processing (Issuer Authentication, second generate AC...).
//! \param[in] pDataStruct Data buffer for ExpressPay transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- ExpressPay kernel result.

int SDSA_ExpressPay_PerformPostProcessing (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult;
	
	nResult = ExpressPay3_DoTransactionPostProcessing(pDataStruct);

	GTL_Traces_TraceDebug ("ExpressPay3_DoTransactionPostProcessing result = %02x", nResult);

	if(nResult == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_APPROVED)
		ExpressPay3_GetAllData(pDataStruct); // Get all the kernel data to print the receipt

	// Cless field must be stopped
	ClessEmv_DeselectCard(0, TRUE, FALSE);

	// Send data to the CST application. If TAG_SDSA_LIST_OF_OUTPUT_TAGS is not provided, default tag list is returned. 
    if ((nResult != CLESS_CR_MANAGER_REMOVE_AID) && (nResult != CLESS_CR_MANAGER_RESTART) && (nResult != CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY) && (nResult != CLESS_CR_MANAGER_RESTART_DOUBLE_TAP))		
    {
    	if(!SDSA_Common_GetListOfOutputTags(hOutputTlvTree))
	    	SDSA_Common_CopyDataStructInTLVTree(pDataStruct,hOutputTlvTree);	
	}
		
	return (nResult);
}



//! \brief Get the double tap time value from the parameter file.
//! \param[out] pDoubleTapTime the double tap time value (in milliseconds).

static void __SDSA_ExpressPay_GetDoubleTapTime (unsigned long *pDoubleTapTime)
{
	TLV_TREE_NODE pTime;		// Node for Double Tap Time.
	unsigned char * pValue;
	unsigned int nDataLength;

	pValue = NULL;
	nDataLength = 0;
	
	pTime = TlvTree_Find(pTreeCurrentParam, TAG_SDSA_EXPRESSPAY_DOUBLE_TAP_TIME, 0);

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

static void __SDSA_ExpressPay_CloseFieldBefore2ndTap (void)
{
	unsigned long ulDoubleTapTime;		// Double Tap time (in milliseconds)

	__SDSA_ExpressPay_GetDoubleTapTime(&ulDoubleTapTime);

	// Stop Cless Field
	ClessEmv_CloseDriver();

	// Perform a double bip (600 ms)
	HelperErrorSequence (WITHBEEP);

	// Wait the remaining time
	ttestall(0, (ulDoubleTapTime/10) - (6 * C_TIME_100MS));
}


//! \brief Add a tag in the transaction data to indicate to the Expresspay kernel that the transaction has been restarted.
//! \param[in/out] pTransactionData Transaction data.

static void __SDSA_ExpressPay_SetTxnRestartedIndicator (T_SHARED_DATA_STRUCT *pTransactionData)
{
	int ret;
	unsigned char ucTxnRestarted;

	ucTxnRestarted = 0x01;
	
	ret = GTL_SharedExchange_AddTag(pTransactionData, TAG_EXPRESSPAY_MOBILE_TRANSACTION_RESTARTED, 1, &ucTxnRestarted);
	if (ret != STATUS_SHARED_EXCHANGE_OK)
		GTL_Traces_TraceDebug("__SDSA_ExpressPay_SetTxnRestartedIndicator: Unable to add TAG_EXPRESSPAY_MOBILE_TRANSACTION_RESTARTED in shared buffer (ret=%02x)", ret);
}

