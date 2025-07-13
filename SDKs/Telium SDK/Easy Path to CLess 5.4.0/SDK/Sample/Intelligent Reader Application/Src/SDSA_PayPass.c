/**
 * \file	SDSA_PayPass.c
 * \brief	Manages the interface with the PayPass contactless kernel.
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


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __SDSA_PayPass_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm);
static int __SDSA_PayPass_AddPayPassSpecificData (T_SHARED_DATA_STRUCT * pDataStruct);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Get the PayPass transaction outcome.
//! \param[out] pTransactionOutcome Retrieved transaction outcome :
//!		- \a PAYPASS_OUTCOME_APPROVED if transaction is approved.
//!		- \a PAYPASS_OUTCOME_ONLINE_REQUEST if an online authorization is requested.
//!		- \a PAYPASS_OUTCOME_DECLINED if the transaction is declined.
//!		- \a PAYPASS_OUTCOME_TRY_ANOTHER_INTERFACE if another interface shall be used.
//!		- \a PAYPASS_OUTCOME_END_APPLICATION if the transaction is terminated.
//! \return
//!		- \ref TRUE if correctly retrieved.
//!		- \ref FALSE if an error occurred.
#if 0
static int __SDSA_PayPass_RetreiveTransactionOutcome (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pTransactionOutcome)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	* pTransactionOutcome = PAYPASS_OUTCOME_END_APPLICATION; // Default result
	
	// Get the transaction outcome tag from the shared buffer returned by the PayPass kernel
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_PAYPASS_TRANSACTION_OUTCOME, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_PayPass_RetreiveTransactionOutcome : Unable to get transaction outcome from the PayPass kernel response (cr = %02x)", cr);
		nResult = FALSE;
		goto End;
	}
	
	// Get the transaction outcome value
	* pTransactionOutcome = pReadValue[0];
	
End:	
	return (nResult);
}
#endif


//! \brief Get the PayPass CVM to apply.
//! \param[out] pCvm CVM to apply :
//!		- \a PAYPASS_CVM_NO_CVM No CVM to be performed.
//!		- \a PAYPASS_CVM_SIGNATURE if signature shall be performed.
//!		- \a PAYPASS_CVM_ONLINE_PIN if online PIN shall be performed.
//! \return
//!		- \ref TRUE if correctly retrieved.
//!		- \ref FALSE if an error occurred.

static int __SDSA_PayPass_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	* pCvm = PAYPASS_CVM_NO_CVM; // Default result
	
	// Get the transaction CVM tag from the shared buffer returned by the PayPass kernel
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_PAYPASS_TRANSACTION_CVM, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		nResult = FALSE;
		goto End;
	}
	
	// Get the CVM to apply
	* pCvm = pReadValue[0];
	
End:	
	return (nResult);
}


//! \brief Fill buffer with specific PayPass data for transaction customization/interpretation.
//! \param[out] pDataStruct Shared exchange structure filled with the specific PayPass data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

static int __SDSA_PayPass_AddPayPassSpecificData (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int cr, nResult;
	object_info_t ObjectInfo;
	unsigned char bUseRefundTransactionFlow = 0x01;
	T_KERNEL_TRANSACTION_FLOW_CUSTOM sTransactionFlowCustom;
	unsigned char StepInterruption[KERNEL_PAYMENT_FLOW_STOP_LENGTH];// Bit field to stop payment flow,
																	// if all bit set to 0 => no stop during payment process
									                                // if right bit set to 1 : stop after payment step number 1
	unsigned char StepCustom[KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH]; 	// Bit field to custom payment flow,
																	// if all bit set to 0 => no stop during payment process
									                                // if right bit set to 1 : stop after payment step number 1
	
	if (pDataStruct == NULL)
	{
		GTL_Traces_TraceDebug("__SDSA_PayPass_AddPayPassSpecificData : Invalid Input data");
		nResult = FALSE;
		goto End;
	}
	
    // Init parameteters
	memset(StepInterruption, 0, sizeof(StepInterruption));	// Default Value : not stop on process
	memset(StepCustom, 0, sizeof(StepCustom));				// Default Value : not stop on process
	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
	nResult = TRUE;

	
	// Add a tag for Do_Txn management that indicates the steps on which the kernel shall stop the processing and give hand back to the custom application
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_STOP, KERNEL_PAYMENT_FLOW_STOP_LENGTH, (const unsigned char *)StepInterruption);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_PayPass_AddPayPassSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_STOP in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}
		
	
	// Indicate the steps on which the kernel shall call the custom application for step customisation
    ADD_STEP_CUSTOM(STEP_PAYPASS_MSTRIPE_REMOVE_CARD,StepCustom);	 // To do GUI when MStripe card has been read
	ADD_STEP_CUSTOM(STEP_PAYPASS_MCHIP_REMOVE_CARD,StepCustom);		 // To do GUI when MChip card has been read
	ADD_STEP_CUSTOM(STEP_PAYPASS_MCHIP_GET_CERTIFICATE, StepCustom); // To provide the CA key data for ODA

	if (SDSA_IsBlackListPresent())	
		ADD_STEP_CUSTOM(STEP_PAYPASS_MCHIP_EXCEPTION_FILE_GET_DATA, StepCustom); // To check if PAN is in the blacklist
	
	memcpy ((void*)&sTransactionFlowCustom, (void*)StepCustom, KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH);
	sTransactionFlowCustom.usApplicationType = ObjectInfo.application_type; // Kernel will call this application for customisation 
	sTransactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL;				// Kernel will call SERVICE_CUSTOM_KERNEL service id for customisation 

    cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_KERNEL_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_PayPass_AddPayPassSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_CUSTOM in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}
	
	if (SDSA_Fill_GiveTransactionType() == SDSA_TRANSACTION_TYPE_REFUND)
	{
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_PAYPASS_INT_USE_REFUND_FLOW, 1, &bUseRefundTransactionFlow);

		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("__SDSA_PayPass_AddPayPassSpecificData : Unable to add TAG_PAYPASS_INT_USE_REFUND_FLOW in shared buffer (cr=%02x)", cr);
			nResult = FALSE;
			goto End;
		}
	}
End:
	return (nResult);
}


//! \brief Manage the debug mode for PayPass kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to de-activate features.

void SDSA_PayPass_DebugActivation (int bActivate)
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
			GTL_Traces_TraceDebug("SDSA_PayPass_DebugActivation : Unable to add TAG_KERNEL_DEBUG_ACTIVATION (nResult = %02x)", nResult);
		}
		else
		{
			nResult = PayPass_DebugManagement(pSharedStructure);
			
			if (nResult != KERNEL_STATUS_OK)
			{
				GTL_Traces_TraceDebug("SDSA_PayPass_DebugActivation : Error occurred during PayPass Debug activation (nResult = %02x)", nResult);
			}
		}
		
		// Destroy the shared buffer
		GTL_SharedExchange_DestroyShare(pSharedStructure);
	}
}


//! \brief Perform the PayPass kernel customization.
//! \param[in,out] pSharedData Shared buffer used for customization.
//! \param[in] ucCustomisationStep Step to be customized.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int SDSA_PayPass_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep)
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

    
    switch (ucCustomisationStep) // Steps to customize
    {
    case (STEP_PAYPASS_MSTRIPE_REMOVE_CARD):
	case (STEP_PAYPASS_MCHIP_REMOVE_CARD):
		// Display remove card message, manage leds and buzzer
		HelperRemoveCardSequence(pSharedData);
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_PAYPASS_MCHIP_GET_CERTIFICATE):
		// The PayPass kernel calls the custom application to request the transaction certificate.
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
			GTL_Traces_TraceDebug ("SDSA_PayPass_CustomiseStep : SDSA_Parameters_GetCaKeyData failed");
		}
		
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_PAYPASS_MCHIP_EXCEPTION_FILE_GET_DATA):
		// Get the PAN
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_EMV_APPLI_PAN, &ulPanLength, &pPan) != STATUS_SHARED_EXCHANGE_OK)
		{
			// Pan parameters is missing, we cannot check BlackList
			GTL_Traces_TraceDebug ("SDSA_PayPass_CustomiseStep : PAN is missing for exception file checking");
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
			// Add TAG_KERNEL_PAN_IN_BLACK_LIST tag in the exchange buffer to indicate PayPass kernel the PAN is in the black list
			if (GTL_SharedExchange_AddTag (pSharedData, TAG_KERNEL_PAN_IN_BLACK_LIST, 1, &bPanInExceptionFile) != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_SharedExchange_ClearEx (pSharedData, FALSE);
				GTL_Traces_TraceDebug ("SDSA_PayPass_CustomiseStep : Unable to add TAG_KERNEL_PAN_IN_BLACK_LIST in the shared buffer");
			}
		}

		nResult = KERNEL_STATUS_CONTINUE;
		break;

	// Other customisation steps could be defined if necessary
		
    default:
    	GTL_Traces_TraceDebug ("SDSA_PayPass_CustomiseStep : Step to customize (unknown) = %02x\n", ucCustomisationStep);
    	break;
    }
    
    return (nResult);
}



//! \brief Calls the PayPass kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for PayPass transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- PayPass kernel result.

int SDSA_PayPass_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult = CLESS_CR_MANAGER_END;
	int cr;
	unsigned char ucCvm;
	
	// Indicate PayPass kernel is going to be used (for customisation purposes)
	SDSA_Customisation_SetUsedPaymentScheme (SDSA_KERNEL_IDENTIFIER_PAYPASS);
	
	// Fill buffer with specific PayPass data for transaction customisation/interruption
	if (!__SDSA_PayPass_AddPayPassSpecificData(pDataStruct))
	{
	    GTL_Traces_TraceDebug("SDSA_PayPass_PerformTransaction : __SDSA_PayPass_AddPayPassSpecificData failed\n");
	}
	else
	{		
		// Call the PayPass kernel that will perform the transaction
		cr = PayPass_DoTransaction(pDataStruct);
		
		// Set language with preferred card language (a request shall be done to the PayPass kernel as the TAG_KERNEL_SELECTED_PREFERED_LANGUAGE tag is not default returned by the PayPass kernel).
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYPASS);

		if (SDSA_Fill_GiveTransactionType() == SDSA_TRANSACTION_TYPE_REFUND)
		{
			// Refund transaction
			switch (cr)
			{
			case (KERNEL_STATUS_OFFLINE_APPROVED):
				// Refund is approved
				PayPass_GetAllData(pDataStruct); // Get all the kernel data to print the receipt
				nResult = SDI_STATUS_APPROVED;
				break;

			case (KERNEL_STATUS_COMMUNICATION_ERROR):
				nResult = CLESS_CR_MANAGER_RESTART;
				PayPass_Clear(); // If restart is required, kernel database shall be cleared
				break;

			default:
				break;

			}
		}
		else // Purchase transaction
		{
			// Get the TAG_PAYPASS_TRANSACTION_CVM to identify the CVM to be performed :
			// 	- PAYPASS_CVM_NO_CVM     (0x01) : "No CVM" method has been applied.
			// 	- PAYPASS_CVM_SIGNATURE  (0x02) : "Signature" method has been applied.
			// 	- PAYPASS_CVM_ONLINE_PIN (0x04) : "Online PIN" method has been applied.
			if (!__SDSA_PayPass_RetreiveCvmToApply (pDataStruct, &ucCvm))
			{
				ucCvm = PAYPASS_CVM_NO_CVM;
			}

			if ((ucCvm == PAYPASS_CVM_ONLINE_PIN) && (cr == KERNEL_STATUS_OFFLINE_APPROVED))
				cr = KERNEL_STATUS_ONLINE_AUTHORISATION;

			// Get the transaction result and perform specific actions (display message...)
			switch (cr)
			{
			case (KERNEL_STATUS_OFFLINE_APPROVED):

				// Get all the kernel data to print the receipt
				PayPass_GetAllData(pDataStruct);

				nResult = SDI_STATUS_APPROVED;
				break;

			case (KERNEL_STATUS_OFFLINE_DECLINED):
				nResult = SDI_STATUS_DECLINED;
				break;

			case (KERNEL_STATUS_ONLINE_AUTHORISATION):
				if(ucCvm == PAYPASS_CVM_ONLINE_PIN)
					HelperLedsOff();
				
				nResult = SDI_STATUS_ONLINE_REQUEST;
				break;

			case (KERNEL_STATUS_USE_CONTACT_INTERFACE):
				nResult = SDI_STATUS_USE_OTHER_INTERFACE;
				break;

			case (KERNEL_STATUS_COMMUNICATION_ERROR):
				nResult = CLESS_CR_MANAGER_RESTART;
				PayPass_Clear(); // If restart is required, kernel database shall be cleared
				break;

			case (KERNEL_STATUS_CARD_BLOCKED):
				nResult = SDI_STATUS_CARD_BLOCKED;
				break;

			case (KERNEL_STATUS_APPLICATION_BLOCKED):
				nResult = SDI_STATUS_APPLICATION_BLOCKED;
				break;

			default: // Error case

				break;
			}
		}

		// Close the contact less driver
		ClessEmv_CloseDriver();

		// Send data to the CST application. If TAG_SDSA_LIST_OF_OUTPUT_TAGS is not provided, default tag list is returned.
        if ((nResult != CLESS_CR_MANAGER_REMOVE_AID) && (nResult != CLESS_CR_MANAGER_RESTART) && (nResult != CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY) && (nResult != CLESS_CR_MANAGER_RESTART_DOUBLE_TAP))		
        {
		    if(!SDSA_Common_GetListOfOutputTags(hOutputTlvTree))
			    SDSA_Common_CopyDataStructInTLVTree(pDataStruct,hOutputTlvTree);
		}
	}
		
	return (nResult);
}
