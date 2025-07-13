/**
 * \file	CST_PayPass.c
 * \brief 	Module that manages the PayPass transaction.
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


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static int __CST_PayPass_RetreiveCardType (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned short * pCardType);
static void __CST_PayPass_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData, unsigned short usCardType);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Get the PayPass CVM to apply.
//! \param[out] pCvm CVM to apply :
//!		- \a PAYPASS_CVM_NO_CVM No CVM to be performed.
//!		- \a PAYPASS_CVM_SIGNATURE if signature shall be performed.
//!		- \a PAYPASS_CVM_ONLINE_PIN if online PIN shall be performed.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

static int __CST_PayPass_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	* pCvm = PAYPASS_CVM_NO_CVM; // Default result
	
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_PAYPASS_TRANSACTION_CVM, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		nResult = FALSE;
		goto End;
	}
	
	// Get the CVM to be performed
	* pCvm = pReadValue[0];
	
End:	
	return (nResult);
}



//! \brief Get the PayPass card type.
//! \param[out] pCardType Retreived card type :
//!		- \a 0 If card type not found.
//!		- \a 0x8501 for MStripe card.
//!		- \a 0x8502 for MChip card.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

static int __CST_PayPass_RetreiveCardType (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned short * pCardType)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	* pCardType = 0; // Default result
	
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_KERNEL_CARD_TYPE, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		nResult = FALSE;
		goto End;
	}
	
	// Get the card type value
	* pCardType = (pReadValue[0] << 8) + pReadValue[1];
	
End:	
	return (nResult);
}


//! \brief Perform the Online PIN input and encipher PIN.
//! \param[out] pStructureForOnlineData Data returned by the kernel in which the enciphered online PIN would be added.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

static T_Bool __CST_PayPass_OnlinePinManagement (T_SHARED_DATA_STRUCT * pStructureForOnlineData)
{
	T_SHARED_DATA_STRUCT * pDataRequest;
	T_Bool nResult = B_TRUE;
	int cr;
	int nPosition;
	const unsigned char * pPan;
	unsigned long ulPanLength;
	const unsigned char * pAmount;
	char aucDymmyMsg[] = "";
	unsigned long ulAmountLength;
	unsigned long ulAmount = 0;
	BUFFER_SAISIE buffer_saisie;
	MSGinfos tMsg;
	TLV_TREE_NODE hTlvTreeIn;
	TLV_TREE_NODE hTlvTreeOut = NULL;
	
	hTlvTreeIn = TlvTree_New(0);
	
	pDataRequest = GTL_SharedExchange_InitLocal (128);

	if ((hTlvTreeIn != NULL) && (pDataRequest != NULL))
	{
		// Indicate tag to be requested
		TlvTree_AddChild(hTlvTreeIn, TAG_EMV_APPLI_PAN, NULL, 0);
		TlvTree_AddChild(hTlvTreeIn, TAG_EMV_AMOUNT_AUTH_NUM, NULL, 0);
		
		cr = SDI_Payment_GetData(nSDSAAppliId, hTlvTreeIn, &hTlvTreeOut);

		if (cr != SDI_STATUS_OK)
		{
			GTL_Traces_TraceDebug("__CST_PayPass_OnlinePinManagement : An error occured when getting tags from the PayPass kernel (cr=%02x)", cr);
			
			if(cr == SDI_STATUS_DISCONNECTED)
				CST_ReconnectionProcess();

			nResult = B_FALSE;
			goto End;
		}

		if (hTlvTreeOut == NULL)
		{
			nResult = B_FALSE;
			goto End;
		}

		// Copy data in the buffer
		CopyTlvTreeToDataStruct(hTlvTreeOut, pDataRequest);

		// Tags have been got (if present), get the PAN
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pDataRequest, &nPosition, TAG_EMV_APPLI_PAN, &ulPanLength, &pPan) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug ("__CST_PayPass_OnlinePinManagement : Missing PAN for Online PIN");
			nResult = B_FALSE;
			goto End;
		}

		// Get the transaction amount (numeric)
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pDataRequest, &nPosition, TAG_EMV_AMOUNT_AUTH_NUM, &ulAmountLength, &pAmount) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug ("__CST_PayPass_OnlinePinManagement : Missing Amount for Online PIN");
			nResult = B_FALSE;
			goto End;
		}

		// Convert amount
		GTL_Convert_DcbNumberToUl(pAmount, &ulAmount, ulAmountLength);
		
		// Warning, erase display must be made only if Pin input will be made on customer screen
		if (CST_IsPinpadPresent())
		{
			// Display dummy message to erase display
			tMsg.message = aucDymmyMsg;
			tMsg.coding = _ISO8859_;
			tMsg.file = GetCurrentFont();

			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, HELPERS_ALIGN_CENTER);
		}
		
		// Request online PIN entry
		cr = CST_PinManagement_OnLinePinManagement ((unsigned char*)pPan, 1, ulAmount, 30000, 10000, &buffer_saisie);

		if (CST_IsPinpadPresent())
			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, HELPERS_ALIGN_CENTER);

		if (cr == INPUT_PIN_ON)
		{
			cr = GTL_SharedExchange_AddTag(pStructureForOnlineData, TAG_CST_ENCIPHERED_PIN_CODE, buffer_saisie.nombre , (const unsigned char *)buffer_saisie.donnees);

			if (cr != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_Traces_TraceDebug ("__CST_PayPass_OnlinePinManagement : Unable to add TAG_CST_ENCIPHERED_PIN_CODE in the shared buffer (cr = %02x)", cr);
				nResult = B_FALSE;
				goto End;
			}
		}
		else if (cr == CANCEL_INPUT)
		{
				GTL_Traces_TraceDebug ("__CST_PayPass_OnlinePinManagement : input pin Cancelled");
				nResult = B_NON_INIT;
				goto End;
		}
	}

End:

	TlvTree_ReleaseEx (&hTlvTreeOut);
	TlvTree_ReleaseEx (&hTlvTreeIn);

	// Destroy the shared buffer if created
	if (pDataRequest != NULL)
		GTL_SharedExchange_DestroyLocal (pDataRequest);	

	return (nResult);
}


//! \brief Add the tranasction record in the batch file.
//! \param[in] pSharedData Shared buffer to be used to get all the record data.

static void __CST_PayPass_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData, unsigned short usCardType)
{
	// Tags required for Offline and Online approved transactions
	T_TI_TAG tRequestedTagsMChip[] = {TAG_EMV_TRACK_2_EQU_DATA, TAG_PAYPASS_THIRD_PARTY_DATA, TAG_EMV_DF_NAME,
								TAG_EMV_APPLICATION_LABEL, TAG_EMV_APPLI_PREFERED_NAME, TAG_EMV_ISSUER_CODE_TABLE_INDEX,
								TAG_EMV_APPLICATION_CRYPTOGRAM, TAG_EMV_CRYPTOGRAM_INFO_DATA, TAG_EMV_ISSUER_APPLI_DATA,
								TAG_EMV_ATC, TAG_EMV_TVR, TAG_EMV_UNPREDICTABLE_NUMBER, TAG_EMV_TRANSACTION_CURRENCY_CODE,
								TAG_EMV_TRANSACTION_TYPE, TAG_EMV_TERMINAL_CAPABILITIES, TAG_EMV_TRANSACTION_DATE, TAG_EMV_AMOUNT_AUTH_NUM,
								TAG_EMV_TERMINAL_COUNTRY_CODE, TAG_EMV_CVM_RESULTS, TAG_EMV_AIP, TAG_EMV_APPLI_PAN, 
								TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER, TAG_EMV_APPLI_EXPIRATION_DATE,
								TAG_PAYPASS_TRANSACTION_OUTCOME, TAG_PAYPASS_TRANSACTION_CVM, TAG_KERNEL_CARD_TYPE};

	T_TI_TAG tRequestedTagsMStripe[] = {TAG_PAYPASS_TRACK2_DATA, TAG_PAYPASS_TRACK1_DATA, TAG_PAYPASS_DD_CARD_TRACK1, 
										TAG_PAYPASS_DD_CARD_TRACK2, TAG_PAYPASS_THIRD_PARTY_DATA, TAG_EMV_DF_NAME,
										TAG_EMV_APPLICATION_LABEL, TAG_EMV_APPLI_PREFERED_NAME, 
										TAG_EMV_ISSUER_CODE_TABLE_INDEX, TAG_EMV_TRANSACTION_DATE,
										TAG_PAYPASS_TRANSACTION_OUTCOME, TAG_PAYPASS_TRANSACTION_CVM, TAG_KERNEL_CARD_TYPE,
										TAG_EMV_AMOUNT_AUTH_NUM, TAG_EMV_TRANSACTION_TYPE};
	unsigned int nIndex;
	int nResult;
	TLV_TREE_NODE hTlvTreeIn;
	TLV_TREE_NODE hTlvTreeOut = NULL;
	
	hTlvTreeIn = TlvTree_New(0);

	if (hTlvTreeIn != NULL)
	{
		nIndex = 0;

		switch (usCardType)
		{
		case ((PAYPASS_B1_CARD_ID << 8) + (PAYPASS_B2_CARD_TYPE_MCHIP)): // MChip card
			while (nIndex < NUMBER_OF_ITEMS(tRequestedTagsMChip))
			{
				TlvTree_AddChild(hTlvTreeIn, tRequestedTagsMChip[nIndex], NULL, 0);
				nIndex ++;
			}
			break;
		case ((PAYPASS_B1_CARD_ID << 8) + (PAYPASS_B2_CARD_TYPE_MSTRIPE)): // MStripe card
			while (nIndex < NUMBER_OF_ITEMS(tRequestedTagsMStripe))
			{
				TlvTree_AddChild(hTlvTreeIn, tRequestedTagsMStripe[nIndex], NULL, 0);
				nIndex ++;
			}
			break;
		default:
			GTL_Traces_TraceDebug ("__CST_PayPass_AddRecordToBatch : Unknown card type (%02x)\n", usCardType);
			return;
			break;
		}

		// Get the common tags
		nResult = SDI_Payment_GetData(nSDSAAppliId, hTlvTreeIn, &hTlvTreeOut);

		if (nResult == SDI_STATUS_OK)
		{
			if (hTlvTreeOut != NULL)
			{
				// Clear the buffer and copy data
				GTL_SharedExchange_ClearEx (pSharedData, FALSE);
				CopyTlvTreeToDataStruct(hTlvTreeOut, pSharedData);

				if (!CST_Batch_AddTransactionToBatch (pSharedData))
				{
					GTL_Traces_TraceDebug ("__CST_PayPass_AddRecordToBatch : Save transaction in batch failed");
					Helper_DisplayMessage(STD_MESS_BATCH_ERROR, ERASE, HELPERS_MERCHANT_LINE_3);
					Helper_RefreshScreen (WAIT);
				}
			}
		}
		else
		{
			GTL_Traces_TraceDebug ("__CST_PayPass_AddRecordToBatch : Unable to get PayPass data (nResult = %02x)\n", nResult);
		}
		
		TlvTree_ReleaseEx (&hTlvTreeIn);
		TlvTree_ReleaseEx (&hTlvTreeOut);

		if(nResult == SDI_STATUS_DISCONNECTED)
			CST_ReconnectionProcess();
	}
	else
	{
		GTL_Traces_TraceDebug ("__CST_PayPass_AddRecordToBatch : error when creating the TLV-Tree");
	}
}


//! \brief Specific management for PayPass end of transaction according to transaction result.
//! Displays specific messages, manages batch, manages online authorization, manages CVM ...
//! \param[in] pDataStruct Transaction output data. 
//! \param[in] nTransactionOutcome Transaction result.
//! \return The transaction outcome value.

int CST_PayPass_Transaction(T_SHARED_DATA_STRUCT * pDataStruct, int nTransactionOutcome)
{
	unsigned char bLoopMode;
	unsigned char ucCvm;
	MSGinfos tMsg;
	int bSaveInBatch = FALSE;
	int nPosition;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	T_Bool bContinueWithOnlineAuthorisation = B_TRUE;
	unsigned short usCardType = 0;
	int nTransactionResult;

	nTransactionResult = nTransactionOutcome;

	// Debug purpose : if you need to dump the data provided by the kernel
	if (CST_Menu_IsTransactionDataDumpingOn())
		CST_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATA RECORD");

	// Loop mode information
	bLoopMode = CST_Menu_IsTransactionLoopOn();

	if (CST_Tests_GiveTransactionType() == SDSA_TRANSACTION_TYPE_REFUND)
	{
		// Retreive the card type
		if (!__CST_PayPass_RetreiveCardType (pDataStruct, &usCardType))
		{
			usCardType = 0;
		}

		// Refund transaction
		switch (nTransactionOutcome)
		{
		case (SDI_STATUS_APPROVED):
			// Refund is approved
			Helper_DisplayMessage(STD_MESS_MENU_MAIN_REFUND, ERASE, HELPERS_MERCHANT_LINE_2);
			Helper_DisplayMessage(STD_MESS_APPROVED, NO_ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_RefreshScreen(NOWAIT);
			CST_DisplayScreen(SDSA_PAYPASS_SCREEN_OFFLINE_APPROVED_REFUND);

			if (!bLoopMode)
			{
				// Print a receipt only merchant need to print a receipt	
				GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);

				if ((CST_DumpData_GetOutputId() != CST_OUTPUT_NONE) &&  (HelperQuestionYesNo (&tMsg, 30)))
					CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_MASTERCARD, APPROVED_TICKED, WITHOUT_SIGNATURE, WITH_AOSA);
			}

			bSaveInBatch = TRUE;
			break;

		default:
			// Refund has failed
			GTL_Traces_TraceDebug ("Refund failed (nTransactionOutcome=%02x)", nTransactionOutcome);

			Helper_DisplayMessage(STD_MESS_MENU_MAIN_REFUND, ERASE, HELPERS_MERCHANT_LINE_2);
			Helper_DisplayMessage(STD_MESS_FAILED, NO_ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_RefreshScreen(NOWAIT);
			CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ERROR_REFUND);
			
			break;
		}
	}
	else // Purshase transaction
	{

		if (!__CST_PayPass_RetreiveCvmToApply (pDataStruct, &ucCvm))
		{
			ucCvm = PAYPASS_CVM_NO_CVM;
		}

		// Retreive the card type
		if (!__CST_PayPass_RetreiveCardType (pDataStruct, &usCardType))
		{
			usCardType = 0;
		}

		switch (nTransactionOutcome)
		{
		case (SDI_STATUS_APPROVED):
			if (ucCvm == PAYPASS_CVM_SIGNATURE)
			{
				Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_MERCHANT_LINE_3);
				Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_MERCHANT_LINE_4);
				Helper_RefreshScreen(NOWAIT);
				CST_DisplayScreen(SDSA_PAYPASS_SCREEN_SIGNATURE_REQUIRED);
			}
			else
			{
				Helper_DisplayMessage(STD_MESS_OFFLINE_APPROVED, ERASE, HELPERS_MERCHANT_LINE_3);
				Helper_RefreshScreen(NOWAIT);
				CST_DisplayScreen(SDSA_PAYPASS_SCREEN_OFFLINE_APPROVED);
				bSaveInBatch = TRUE;
			}

			if (!bLoopMode)
			{
				// Print a receipt only if signature requested or merchant need to print a receipt	
				GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);

				if ((CST_DumpData_GetOutputId() != CST_OUTPUT_NONE) &&  ((ucCvm == PAYPASS_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30))))
					CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_MASTERCARD, APPROVED_TICKED, (ucCvm == PAYPASS_CVM_SIGNATURE), WITH_AOSA);
			}

			if (ucCvm == PAYPASS_CVM_SIGNATURE)
			{
				GetMessageInfos(STD_MESS_SIGNATURE_OK, &tMsg);
				if (HelperQuestionYesNo (&tMsg, 30))
				{
					Helper_DisplayMessage(STD_MESS_SIGNATURE_CORRECT, ERASE, HELPERS_MERCHANT_LINE_3);
					Helper_RefreshScreen(NOWAIT);

					CST_DisplayScreen(SDSA_PAYPASS_SCREEN_APPROVED);
					bSaveInBatch = TRUE;
				}
				else
				{
					Helper_DisplayMessage(STD_MESS_SIGNATURE_INCORRECT, ERASE, HELPERS_MERCHANT_LINE_3);
					Helper_RefreshScreen(NOWAIT);

					CST_DisplayScreen(SDSA_PAYPASS_SCREEN_OFFLINE_DECLINED);
				}
			}
			break;

		case (SDI_STATUS_DECLINED):
			Helper_DisplayMessage(STD_MESS_OFFLINE_DECLINED, ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_RefreshScreen(NOWAIT);
			CST_DisplayScreen(SDSA_PAYPASS_SCREEN_OFFLINE_DECLINED);
			break;

		case (SDI_STATUS_ONLINE_REQUEST):				
			if (ucCvm == PAYPASS_CVM_ONLINE_PIN)
			{
				bContinueWithOnlineAuthorisation = __CST_PayPass_OnlinePinManagement (pDataStruct);
			}

			if (bContinueWithOnlineAuthorisation == B_TRUE)
			{
				Helper_DisplayMessage(STD_MESS_ONLINE_REQUEST, ERASE, HELPERS_MERCHANT_LINE_3);
				Helper_RefreshScreen(NOWAIT);

				CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ONLINE_PROCESSING);

				// Manage online authorisation
				if (CST_FinancialCommunication_ManageAuthorisation (pDataStruct, SDSA_KERNEL_IDENTIFIER_PAYPASS))
				{
					nPosition = SHARED_EXCHANGE_POSITION_NULL;

					// Try to get the host response
					if (GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EMV_AUTHORISATION_RESPONSE_CODE, &ulReadLength, &pReadValue) == STATUS_SHARED_EXCHANGE_OK)
					{
						if ((pReadValue[0] == 0x30) && (pReadValue[1] == 0x30))
						{
							if (ucCvm == PAYPASS_CVM_SIGNATURE)
							{
								Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_MERCHANT_LINE_3);
								Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_MERCHANT_LINE_4);
								Helper_RefreshScreen(NOWAIT);

								CST_DisplayScreen(SDSA_PAYPASS_SCREEN_SIGNATURE_REQUIRED);
							}
							else
							{
								Helper_DisplayMessage(STD_MESS_ONLINE_APPROVED, ERASE, HELPERS_MERCHANT_LINE_3);
								Helper_RefreshScreen(NOWAIT);

								CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ONLINE_APPROVED);
								bSaveInBatch = TRUE;
							}

							// Get all the kernel data
							CST_Term_GetAllData(pDataStruct);
							
							if (!bLoopMode)
							{
								GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);
							
								if ((CST_DumpData_GetOutputId() != CST_OUTPUT_NONE) && ((ucCvm == PAYPASS_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30))))
									CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_MASTERCARD, APPROVED_TICKED, (ucCvm == PAYPASS_CVM_SIGNATURE), WITH_AOSA);
							}

							if (ucCvm == PAYPASS_CVM_SIGNATURE)
							{
								GetMessageInfos(STD_MESS_SIGNATURE_OK, &tMsg);
								if ((bLoopMode) || (HelperQuestionYesNo (&tMsg, 30)))
								{
									Helper_DisplayMessage(STD_MESS_SIGNATURE_CORRECT, ERASE, HELPERS_MERCHANT_LINE_3);
									Helper_RefreshScreen(NOWAIT);

									CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ONLINE_APPROVED);
									bSaveInBatch = TRUE;
								}
								else
								{
									Helper_DisplayMessage(STD_MESS_SIGNATURE_INCORRECT, ERASE, HELPERS_MERCHANT_LINE_3);
									Helper_RefreshScreen(NOWAIT);

									CST_DisplayScreen(SDSA_PAYPASS_SCREEN_OFFLINE_DECLINED);
									bSaveInBatch = FALSE;
								}
							}
						}
						else
						{
							// Authorisation response code do not indicates an Approved transaction
							Helper_DisplayMessage(STD_MESS_ONLINE_DECLINED, ERASE, HELPERS_MERCHANT_LINE_3);
							Helper_RefreshScreen(NOWAIT);

							CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ONLINE_DECLINED);
						}
					}
					else
					{
						// No Authorisation response code
						Helper_DisplayMessage(STD_MESS_ONLINE_DECLINED, ERASE, HELPERS_MERCHANT_LINE_3);
						Helper_RefreshScreen(NOWAIT);

						CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ONLINE_DECLINED);
					}
				}
				else
				{
					Helper_DisplayMessage(STD_MESS_UNABLE_ON_LINE, ERASE, HELPERS_MERCHANT_LINE_3);
					Helper_RefreshScreen(NOWAIT);

					CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ONLINE_DECLINED);
				}
			}
			else
			{
				if (bContinueWithOnlineAuthorisation == B_NON_INIT)
					Helper_DisplayMessage(STD_MESS_PIN_CANCEL, ERASE, HELPERS_MERCHANT_LINE_3);
				else
					Helper_DisplayMessage(STD_MESS_ONLINE_PIN_ERROR, ERASE, HELPERS_MERCHANT_LINE_3);
				Helper_RefreshScreen(NOWAIT);

				CST_DisplayScreen(SDSA_PAYPASS_SCREEN_OFFLINE_DECLINED);
			}
			break;

		case (SDI_STATUS_USE_OTHER_INTERFACE):
			nTransactionResult = SDI_STATUS_USE_OTHER_INTERFACE;
			break;

		case (SDI_STATUS_CARD_BLOCKED):
			Helper_DisplayMessage(STD_MESS_CARD_BLOCKED, ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_RefreshScreen(NOWAIT);
			CST_DisplayScreen(SDSA_PAYPASS_SCREEN_CARD_BLOCKED);
			break;

		case (SDI_STATUS_APPLICATION_BLOCKED):
			Helper_DisplayMessage(STD_MESS_APPLICATION_BLOCKED, ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_RefreshScreen(NOWAIT);
			CST_DisplayScreen(SDSA_PAYPASS_SCREEN_APPLICATION_BLOCKED);
			break;

		default: // Error case
			Helper_DisplayMessage(STD_MESS_ERROR, ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_RefreshScreen(NOWAIT);
			CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ERROR);
			break;
		}
	}

	if (bSaveInBatch)
		__CST_PayPass_AddRecordToBatch (pDataStruct, usCardType);

	// Increment 
	CST_Batch_IncrementTransactionSeqCounter();

	// If activated, dump all the kernel database
	if (CST_Menu_IsTransactionDatabaseDumpingOn())
	{
		// Get all the kernel data
		if(CST_Term_GetAllData(pDataStruct))
			CST_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATABASE DUMP");
	}

	return (nTransactionResult);
}
