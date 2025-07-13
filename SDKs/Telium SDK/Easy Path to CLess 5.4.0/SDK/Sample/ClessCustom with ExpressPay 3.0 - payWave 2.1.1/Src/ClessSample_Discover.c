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


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __ClessSample_Discover_AddDiscoverSpecificData (T_SHARED_DATA_STRUCT * pDataStruct);
static void __ClessSample_Discover_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData);

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Fill buffer with specific Discover for transaction.
//! \param[out] pDataStruct Shared exchange structure filled with the specific Discover data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

static int __ClessSample_Discover_AddDiscoverSpecificData (T_SHARED_DATA_STRUCT * pDataStruct)
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
		GTL_Traces_TraceDebug("__ClessSample_Discover_AddDiscoverSpecificData : Invalid Input data");
		nResult = FALSE;
	}
	else
	{
		// Init parameteters
		memset(StepInterruption, 0, sizeof(StepInterruption)); // Default Value : not stop on process
		memset(StepCustom, 0, sizeof(StepCustom)); // Default Value : not stop on process
		ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
		nResult = TRUE;

		
		// Add a tag for Do_Txn management
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_STOP, KERNEL_PAYMENT_FLOW_STOP_LENGTH, (const unsigned char *)StepInterruption);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("__ClessSample_Discover_AddDiscoverSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_STOP in shared buffer (cr=%02x)", cr);
			nResult = FALSE;
		}
		else
		{
			ADD_STEP_CUSTOM(STEP_DISCOVER_REMOVE_CARD,StepCustom); // To do GUI when Discover card has been read

			memcpy ((void*)&sTransactionFlowCustom, (void*)StepCustom, KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH);
			sTransactionFlowCustom.usApplicationType = ObjectInfo.application_type; // Kernel will call this application for customisation 
			sTransactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL; // Kernel will call SERVICE_CUSTOM_KERNEL service id for customisation 

			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_KERNEL_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
			if (cr != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_Traces_TraceDebug("__ClessSample_Discover_AddDiscoverSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_CUSTOM in shared buffer (cr=%02x)", cr);
				nResult = FALSE;
			}
		}
	}

	return (nResult);
}

//! \brief Manage the debug mode for Discover kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void ClessSample_Discover_DebugActivation (int bActivate)
{
	T_SHARED_DATA_STRUCT * pSharedStructure;
	int nResult;
	unsigned char ucDebugMode = 0x00;

	if (bActivate)
		ucDebugMode = 0x03;

	pSharedStructure = GTL_SharedExchange_InitShared(256);
	
	if (pSharedStructure != NULL)
	{
		nResult = GTL_SharedExchange_AddTag(pSharedStructure, TAG_KERNEL_DEBUG_ACTIVATION, 1, &ucDebugMode);
		
		if (nResult != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Discover_DebugActivation : Unable to add TAG_KERNEL_DEBUG_ACTIVATION (nResult = %02x)", nResult);
		}
		else
		{
			nResult = Discover_DebugManagement(pSharedStructure);
			
			if (nResult != KERNEL_STATUS_OK)
			{
				GTL_Traces_TraceDebug("ClessSample_Discover_DebugActivation : Error occurred during Discover Debug activation (nResult = %02x)", nResult);
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

int ClessSample_Discover_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep)
{
	int nResult = KERNEL_STATUS_CONTINUE;

	switch (ucCustomisationStep) // Steps to customise
	{
	case (STEP_DISCOVER_REMOVE_CARD):
		HelperRemoveCardSequence(pSharedData);
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	// Other customisation steps could be defined if necessary
		
	default:
		GTL_Traces_TraceDebug ("ClessSample_Discover_CustomiseStep : Step to customise (unknown) = %02x\n", ucCustomisationStep);
		break;
	}
	
	return (nResult);
}



//! \brief Calls the Discover kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for Discover transaction.
//!	\return
//!		- Discover kernel result.

int ClessSample_Discover_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int nResult = CLESS_CR_MANAGER_END;
	int cr, nPosition;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	unsigned char auCustomerDisplayAvailable;
	unsigned char bSaveInBatch = FALSE;
	unsigned char bLoopMode;
	int merchLang;
	T_Bool bContinueWithOnlineAuthorisation = TRUE;
	MSGinfos tMsg;

	// Loop mode information
	bLoopMode = ClessSample_Menu_IsTransactionLoopOn();

	merchLang = PSQ_Give_Language();
	auCustomerDisplayAvailable = Helper_IsClessCustomerDisplayAvailable();

	// Indicate Discover kernel is going to be used (for customisation purposes)
	ClessSample_Customisation_SetUsedPaymentScheme (CLESS_SAMPLE_CUST_DISCOVER);
	
	// Get the Discover
	if (!__ClessSample_Discover_AddDiscoverSpecificData(pDataStruct))
	{
		GTL_Traces_TraceDebug("ClessSample_Discover_PerformTransaction : ClessSample_Fill_DiscoverTransaction failed\n");
	}
	else
	{		
		// Debug purpose : if you need to dump the data provided to the kernel
		///ClessSample_DumpData_DumpSharedBuffer(pDataStruct, 0);
		cr = Discover_DoTransaction(pDataStruct);
		
		// Debug purpose : if you need to dump the data provided by the kernel
		if (ClessSample_Menu_IsTransactionDataDumpingOn())
			ClessSample_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATA RECORD");
		
		switch (cr)
		{
		case (KERNEL_STATUS_OFFLINE_APPROVED):
			ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_OFFLINE_APPROVED, merchLang, merchLang);
			bSaveInBatch = TRUE;
			
			Discover_GetAllData(pDataStruct); // Get all the kernel data to print the receipt
			ClessSample_Term_Read_Message(STD_MESS_PRINT_RECEIPT, merchLang, &tMsg);

			if (bLoopMode == 0)
			{
				if (HelperQuestionYesNo (&tMsg, 30, merchLang))
					ClessSample_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_DISCOVER, APPROVED_TICKED, FALSE, merchLang, WITHOUT_AOSA);
			}
			break;
		
		case (KERNEL_STATUS_OFFLINE_DECLINED):
			ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_OFFLINE_DECLINED, merchLang, merchLang);
			break;
		
		case (KERNEL_STATUS_ONLINE_AUTHORISATION):

			if (bContinueWithOnlineAuthorisation == B_TRUE)
			{
				// if the terminal is not in a transaction loop go online
				if (bLoopMode == 0)
				{
					ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_PROCESSING, merchLang, merchLang);

					if (ClessSample_FinancialCommunication_ManageAuthorisation (pDataStruct))
					{
						nPosition = SHARED_EXCHANGE_POSITION_NULL;

						if (GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EMV_AUTHORISATION_RESPONSE_CODE, &ulReadLength, &pReadValue) == STATUS_SHARED_EXCHANGE_OK)
						{
							if ((pReadValue[0] == 0x30) && (pReadValue[1] == 0x30))
							{
							   ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_APPROVED, merchLang, merchLang);
								bSaveInBatch = TRUE;

								// Get all the kernel data to print the receipt
								Discover_GetAllData(pDataStruct);

								ClessSample_Term_Read_Message(STD_MESS_PRINT_RECEIPT, merchLang, &tMsg);

								if (bLoopMode == 0)
								{
									if (HelperQuestionYesNo (&tMsg, 30, merchLang))
										ClessSample_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_DISCOVER, APPROVED_TICKED, FALSE, merchLang, WITHOUT_AOSA);
								}
							}
							else
							{
								// Authorisation response code do not indicates an Approved transaction
							   ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_DECLINED, merchLang, merchLang);
							}
						}
						else
						{
							// No Authorisation response code
						   ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_DECLINED, merchLang, merchLang);
						}
					}
					else
					{
					   ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_ONLINE_UNABLE, merchLang, merchLang);
					}
				}
			}
			else
			{
				ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_OFFLINE_DECLINED, merchLang, merchLang);
			}
			break;
		
		case (KERNEL_STATUS_USE_CONTACT_INTERFACE):
			nResult = CLESS_CR_MANAGER_RESTART_WO_CLESS;
			break;
		
		case (KERNEL_STATUS_COMMUNICATION_ERROR):
			nResult = CLESS_CR_MANAGER_RESTART;
			break;

		case (KERNEL_STATUS_REMOVE_AID):
			nResult = CLESS_CR_MANAGER_REMOVE_AID;
			break;
			
		case (KERNEL_STATUS_CARD_BLOCKED):
			ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_CARD_BLOCKED, merchLang, merchLang);
			HelperErrorSequence (WITHOUTBEEP);
			Helper_WaitUserDisplay();
			break;
			
		case (KERNEL_STATUS_APPLICATION_BLOCKED):
			ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_APPLICATION_BLOCKED, merchLang, merchLang);
			HelperErrorSequence (WITHOUTBEEP);
			Helper_WaitUserDisplay();
			break;
			
		default: // Error case
			GTL_Traces_TraceDebug ("Discover_DoTransaction result = %02x", cr);
			ClessSample_GuiState_DisplayScreenText(CLESS_SAMPLE_SCREEN_ERROR, merchLang, merchLang);
			HelperErrorSequence(WITHOUTBEEP);
			Helper_WaitUserDisplay();
			break;
		}

		// Cless field must be stopped only if we don't try to work with an another AID
		if (nResult != CLESS_CR_MANAGER_REMOVE_AID)
			// Deselect the card
			ClessEmv_DeselectCard(0, TRUE, FALSE);

		// If the transaction does not restart from the begining, set the LEDs into the idle state
		if ((nResult != CLESS_CR_MANAGER_RESTART) && (nResult != CLESS_CR_MANAGER_REMOVE_AID))
		{
			if (bSaveInBatch)
				__ClessSample_Discover_AddRecordToBatch (pDataStruct);

			// Increment 
			ClessSample_Batch_IncrementTransactionSeqCounter();

			// If activated, dump all the kernel database
			if (ClessSample_Menu_IsTransactionDatabaseDumpingOn())
			{
				Discover_GetAllData(pDataStruct); // Get all the kernel data to print the receipt
				ClessSample_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATABASE DUMP");
			}
		}
	}
	
	// Transaction is completed, clear Discover kernel transaction data
	Discover_Clear ();
	
	// Return result
	return (nResult);
}

//! \brief Add the tranasction record in the batch file.
//! \param[in] pSharedData Shared buffer to be used to get all the record data.

static void __ClessSample_Discover_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData)
{
	// Tags required for Online approved transactions
	T_TI_TAG tRequestedTagsDiscover[] = {TAG_EMV_TRACK_2_EQU_DATA, TAG_DISCOVER_TRACK1_DATA, TAG_EMV_DF_NAME,
								TAG_EMV_APPLICATION_LABEL, TAG_EMV_APPLI_PREFERED_NAME, TAG_EMV_UNPREDICTABLE_NUMBER,
								TAG_DISCOVER_APPLI_VERSION_NUMBER_ICC, TAG_DISCOVER_DCVV,
								TAG_EMV_AMOUNT_AUTH_NUM, TAG_EMV_AIP, TAG_DISCOVER_TRANSACTION_OUTCOME};

	unsigned int nIndex;
	int nResult;

	// Clear the shared exchange buffer
	GTL_SharedExchange_ClearEx (pSharedData, FALSE);
	nIndex = 0;

	while (nIndex < NUMBER_OF_ITEMS(tRequestedTagsDiscover))
	{
		GTL_SharedExchange_AddTag (pSharedData, tRequestedTagsDiscover[nIndex], 0, NULL);
		nIndex ++;
	}

	// Get the common tags
	nResult = Discover_GetData (pSharedData);

	if (nResult == KERNEL_STATUS_OK)
	{
		if (!ClessSample_Batch_AddTransactionToBatch (pSharedData))
		{
			int merchLang;

			merchLang = PSQ_Give_Language();
			GTL_Traces_TraceDebug ("__ClessSample_Discover_AddRecordToBatch : Save transaction in batch failed");
			ClessSample_GuiState_DisplayScreen(CLESS_SAMPLE_SCREEN_BATCH_ERROR, merchLang, merchLang);
		}
	}
	else
	{
		GTL_Traces_TraceDebug ("__ClessSample_Discover_AddRecordToBatch : Unable to get Discover data (nResult = %02x)\n", nResult);
	}
}
