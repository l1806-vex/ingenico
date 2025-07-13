/**
 * \file	SDSA_Discover.c
 * \brief	Manages the interface with the Discover contactless kernel.
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

//static int __SDSA_Discover_RetreiveTransactionOutcome (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pTransactionOutcome);
static int __SDSA_Discover_AddDiscoverSpecificData (T_SHARED_DATA_STRUCT * pDataStruct);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Get the Discover transaction outcome.
//! \param[out] pTransactionOutcome Retreived transaction outcome :
//!		- \a DISCOVER_OUTCOME_APPROVED if transaction is approved.
//!		- \a DISCOVER_OUTCOME_ONLINE_REQUEST if an online authorisation is requested.
//!		- \a DISCOVER_OUTCOME_DECLINED if the transaction is declined.
//!		- \a DISCOVER_OUTCOME_TRY_ANOTHER_INTERFACE if another interface shall be used.
//!		- \a DISCOVER_OUTCOME_END_APPLICATION if the transaction is terminated.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

/* static int __SDSA_Discover_RetreiveTransactionOutcome (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pTransactionOutcome)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	* pTransactionOutcome = DISCOVER_OUTCOME_END_APPLICATION; // Default result
	
	// Get the transaction outcome tag from the shared buffer returned by the Discover kernel
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_DISCOVER_TRANSACTION_OUTCOME, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_Discover_RetreiveTransactionOutcome : Unable to get transaction outcome from the Discover kernel response (cr = %02x)", cr);
		nResult = FALSE;
		goto End;
	}
	
	// Get the transaction outcome value
	* pTransactionOutcome = pReadValue[0];
	
End:	
	return (nResult);
} */



//! \brief Fill buffer with specific Discover data for transaction customisation/interpretation.
//! \param[out] pDataStruct Shared exchange structure filled with the specific Discover data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

static int __SDSA_Discover_AddDiscoverSpecificData (T_SHARED_DATA_STRUCT * pDataStruct)
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
		GTL_Traces_TraceDebug("__SDSA_Discover_AddDiscoverSpecificData : Invalid Input data");
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
		GTL_Traces_TraceDebug("__SDSA_Discover_AddDiscoverSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_STOP in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}
		
	
	// Indicate the steps on which the kernel shall call the custom application for step customisation
    ADD_STEP_CUSTOM(STEP_DISCOVER_REMOVE_CARD,StepCustom);	 // To do GUI when MStripe card has been read
	
	memcpy ((void*)&sTransactionFlowCustom, (void*)StepCustom, KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH);
	sTransactionFlowCustom.usApplicationType = ObjectInfo.application_type; // Kernel will call this application for customisation 
	sTransactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL;				// Kernel will call SERVICE_CUSTOM_KERNEL service id for customisation 

    cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_KERNEL_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_Discover_AddDiscoverSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_CUSTOM in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}
	
End:
	return (nResult);
}


//! \brief Manage the debug mode for Discover kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void SDSA_Discover_DebugActivation (int bActivate)
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
			GTL_Traces_TraceDebug("SDSA_Discover_DebugActivation : Unable to add TAG_KERNEL_DEBUG_ACTIVATION (nResult = %02x)", nResult);
		}
		else
		{
			nResult = Discover_DebugManagement(pSharedStructure);
			
			if (nResult != KERNEL_STATUS_OK)
			{
				GTL_Traces_TraceDebug("SDSA_Discover_DebugActivation : Error occured during Discover Debug activation (nResult = %02x)", nResult);
			}
		}
		
		// Destroy the shared buffer
		GTL_SharedExchange_DestroyShare(pSharedStructure);
	}
}


//! \brief Perform the Discover kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int SDSA_Discover_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep)
{
	int nResult = KERNEL_STATUS_CONTINUE;
    
    switch (ucCustomisationStep) // Steps to customise
    {
    case (STEP_DISCOVER_REMOVE_CARD):
		// Display remove card message, manage leds and buzzer
		HelperRemoveCardSequence(pSharedData);
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	// Other customisation steps could be defined if necessary
		
    default:
    	GTL_Traces_TraceDebug ("SDSA_Discover_CustomiseStep : Step to customise (unknown) = %02x\n", ucCustomisationStep);
    	break;
    }
    
    return (nResult);
}



//! \brief Calls the Discover kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for Discover transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- Discover kernel result.

int SDSA_Discover_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult = CLESS_CR_MANAGER_END;
	int cr;
	unsigned long ulReceiptTags[] = {TAG_EMV_APPLI_PAN, TAG_EMV_APPLI_EXPIRATION_DATE, TAG_EMV_TRANSACTION_TIME, TAG_EMV_TRANSACTION_DATE,
									 TAG_EMV_APPLICATION_LABEL, TAG_EMV_APPLI_PREFERED_NAME, TAG_EMV_AID_CARD, TAG_EMV_AMOUNT_AUTH_BIN,
									 TAG_EMV_TVR, TAG_EMV_DF_NAME, TAG_EMV_TRANSACTION_TYPE};
	
	// Indicate Discover kernel is going to be used (for customisation purposes)
	SDSA_Customisation_SetUsedPaymentScheme (SDSA_KERNEL_IDENTIFIER_DISCOVER);
	
	// Fill buffer with specific Discover data for transaction customisation/interruption
	if (!__SDSA_Discover_AddDiscoverSpecificData(pDataStruct))
	{
	    GTL_Traces_TraceDebug("SDSA_Discover_PerformTransaction : __SDSA_Discover_AddDiscoverSpecificData failed\n");
	}
	else
	{		
		// Call the Discover kernel that will perform the transaction
		cr = Discover_DoTransaction(pDataStruct);
		
		// Set language with preferred card language (a request shall be done to the Discover kernel as the TAG_KERNEL_SELECTED_PREFERED_LANGUAGE tag is not defaulty returned by the Discover kernel).
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_DISCOVER);

		if (SDSA_Fill_GiveTransactionType() == SDSA_TRANSACTION_TYPE_REFUND)
		{
			// Refund transaction
			switch (cr)
			{
			case (KERNEL_STATUS_OFFLINE_APPROVED):
				// Refund is approved
				Discover_GetAllData(pDataStruct); // Get all the kernel data to print the receipt
				nResult = SDI_STATUS_APPROVED;
				break;

			case (KERNEL_STATUS_COMMUNICATION_ERROR):
				nResult = CLESS_CR_MANAGER_RESTART;
				Discover_Clear(); // If restart is required, kernel database shall be cleared
				break;

			default:
				break;

			}
		}
		else // Purshase transaction
		{

			// Get the transaction result and perform specific actions (display message...)
			switch (cr)
			{
			case (KERNEL_STATUS_OFFLINE_APPROVED):

				// Get all the kernel data to print the receipt
				Discover_GetAllData(pDataStruct);

				nResult = SDI_STATUS_APPROVED;
				break;

			case (KERNEL_STATUS_OFFLINE_DECLINED):
				nResult = SDI_STATUS_DECLINED;
				break;

			case (KERNEL_STATUS_ONLINE_AUTHORISATION):
				nResult = SDI_STATUS_ONLINE_REQUEST;
				break;

			case (KERNEL_STATUS_USE_CONTACT_INTERFACE):
				nResult = SDI_STATUS_USE_OTHER_INTERFACE;
				break;

			case (KERNEL_STATUS_COMMUNICATION_ERROR):
				nResult = CLESS_CR_MANAGER_RESTART;
				Discover_Clear(); // If restart is required, kernel database shall be cleared
				break;

			case (KERNEL_STATUS_CARD_BLOCKED):
				nResult = SDI_STATUS_CARD_BLOCKED;
				break;

			case (KERNEL_STATUS_APPLICATION_BLOCKED):
				nResult = SDI_STATUS_APPLICATION_BLOCKED;
				break;

			case (KERNEL_STATUS_REMOVE_AID):
				nResult = CLESS_CR_MANAGER_REMOVE_AID;
				Discover_Clear(); // If restart is required, kernel database shall be cleared
				GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction : REMOVE_AID");
				break;

			default: // Error case

				break;
			}
		}

		// Cless field must be stopped only if we don't try to work with an another AID
		if (nResult != CLESS_CR_MANAGER_REMOVE_AID)
		{
			ClessEmv_CloseDriver();
			GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction: Driver Closed");
		}

		GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction: Get data for CST");

		
		// add extra tags to retrieve from kernel
		SDSA_Common_SetListOfOutputTags((unsigned char *)ulReceiptTags, sizeof(ulReceiptTags));

		// Send data to the CST application. If TAG_SDSA_LIST_OF_OUTPUT_TAGS is not provided, default tag list is returned.
        if ((nResult != CLESS_CR_MANAGER_REMOVE_AID) && (nResult != CLESS_CR_MANAGER_RESTART) && (nResult != CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY) && (nResult != CLESS_CR_MANAGER_RESTART_DOUBLE_TAP))		
        {
		    if(!SDSA_Common_GetListOfOutputTags(hOutputTlvTree))
			    SDSA_Common_CopyDataStructInTLVTree(pDataStruct,hOutputTlvTree);
		}
	}
		
	return (nResult);
}
