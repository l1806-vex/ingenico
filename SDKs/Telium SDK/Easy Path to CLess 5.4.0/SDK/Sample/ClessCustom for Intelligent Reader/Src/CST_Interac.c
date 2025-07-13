/**
 * \file	CST_Interac.c
 * \brief 	Module that manages the Interac transaction.
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

// Defines the timeout to perform the requested CVM
#define C_SIGNATURE_TIMEOUT					(5000)  // 5 Seconds
#define C_PINENTRY_TIMEOUT					(10000) // 10 Seconds


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static int gs_bIsInteracGuiMode = FALSE;			// Set to TRUE if the Interac GUI must be used

/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static void __CST_Interac_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData);
static int __CST_Interac_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm);;


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Check if the Interac GUI mode is activated.
//!	\return
//!		- TRUE if Visa Asia GUI mode is used.
//!		- FALSE else.

int CST_Interac_IsInteracGuiMode (void)
{
	return (gs_bIsInteracGuiMode);
}


//! \brief Get the Interac CVM to perform.
//! \param[out] pCvm Retreived transaction CVM :
//!		- \a INTERAC_CVM_NO_CVM No CVM to be performed.
//!		- \a INTERAC_CVM_SIGNATURE if signature shall be performed.
//!		- \a INTERAC_CVM_ONLINE_PIN if online PIN shall be performed.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

static int __CST_Interac_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm)
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
	
	// Get the CVM value
	* pCvm = pReadValue[0];
	
End:	
	return (nResult);
}

//! \brief Add the transaction record in the batch file.
//! \param[in] pSharedData Shared buffer to be used to get all the record data.

static void __CST_Interac_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData)
{	
	if (!CST_Batch_AddTransactionToBatch (pSharedData))
	{
		GTL_Traces_TraceDebug ("__CST_Interac_AddRecordToBatch : Save transaction in batch failed");
		Helper_DisplayMessage(STD_MESS_BATCH_ERROR, ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_RefreshScreen(WAIT);
	}
}


//! \brief Specific management for Interac end of transaction according to transaction result.
//! Displays specific messages, manages batch, manages online authorization, manages CVM ...
//! \param[in] pDataStruct Transaction output data. 
//! \param[in] nTransactionOutcome Transaction result.
//! \return The transaction outcome value.

int CST_Interac_Transaction(T_SHARED_DATA_STRUCT * pDataStruct, int nTransactionOutcome)
{
	unsigned char bLoopMode;
	unsigned char bOnlinePinError = FALSE;
	MSGinfos tMsg;
	int cr, nFound;
	int bSaveInBatch = FALSE;
	int nPosition;
	int nCurrencyCode;
	const unsigned char * pPan;
	unsigned long ulLgPan;
	unsigned long ulAmount = 0;
	unsigned long ulLgAmount;
	unsigned long ulLgReceiptStatus;
	const unsigned char * pReceiptStatus;
	const unsigned char * pAmount;
	unsigned char * pInfo;
	unsigned char * pCurrencyCode;
	BUFFER_SAISIE buffer_saisie;
	unsigned char cr_pin_online = 0;
	unsigned char ucOnLineDeclined;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	unsigned char ucCvm;
	unsigned long ulStartSignatureTime = 0;
    int nTimeout;
	int nTransactionResult;


	nTransactionResult = nTransactionOutcome;

	// Debug purpose : if you need to dump the data provided by the kernel
	if (CST_Menu_IsTransactionDataDumpingOn())
		CST_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATA RECORD");

	// Loop mode information
	bLoopMode = CST_Menu_IsTransactionLoopOn();

	if (!__CST_Interac_RetreiveCvmToApply (pDataStruct, &ucCvm))
	{
		ucCvm = INTERAC_CVM_NO_CVM;
	}

	ulAmount = 0;
	nCurrencyCode = 0;

	nFound = CST_Term_RetreiveInfo (pDataStruct, TAG_EMV_AMOUNT_AUTH_BIN, &pInfo);
	if (nFound)
	{
		ulLgAmount = 4;
		GTL_Convert_BinNumberToUl(pInfo, &ulAmount, ulLgAmount);
	}				

	nFound = CST_Term_RetreiveInfo (pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_CODE, &pCurrencyCode);
	if (nFound)
	{
		nCurrencyCode = ((*pCurrencyCode)<< 8) + *(pCurrencyCode+1);
	}				

	switch (nTransactionOutcome)
	{
	case (SDI_STATUS_OK):
		Helper_DisplayMessage(STD_MESS_ERROR_STATUS, ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_RefreshScreen(NOWAIT);

		CST_DisplayScreen(STD_MESS_ERROR);		
		break;

	case (SDI_STATUS_APPROVED):

		if(ucCvm == INTERAC_CVM_SIGNATURE)
		{
			Helper_Visa_SignatureCVMIHM();
			CST_DisplayScreen(SDSA_SCREEN_SIGNATURE_REQUIRED);
			if(CST_Interac_IsInteracGuiMode())
				ulStartSignatureTime = GTL_StdTimer_GetCurrent();
		}
		else
		{
			Helper_Visa_ApprovedIHM(OFFLINE);
			CST_DisplayScreen(SDSA_SCREEN_OFFLINE_APPROVED);

			// Transaction shall be added to the batch
			bSaveInBatch = TRUE;
		}

		if (!bLoopMode)
        {
			nPosition = SHARED_EXCHANGE_POSITION_NULL;

			if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_INTERAC_RECEIPT_STATUS, &ulLgReceiptStatus, &pReceiptStatus) == STATUS_SHARED_EXCHANGE_OK)
			{
				if (*pReceiptStatus == INTERAC_RECEIPT_REQUIRED)
				{
					CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_INTERAC, APPROVED_TICKED, (ucCvm == INTERAC_CVM_SIGNATURE), WITH_AOSA);
				}

			}
			else
			{
				// Print a receipt only if signature requested or merchant need to print a receipt
				GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);

				if ((ucCvm == INTERAC_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30)))
					CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_INTERAC, APPROVED_TICKED, (ucCvm == INTERAC_CVM_SIGNATURE), WITH_AOSA);
			}

			
		}

		if (ucCvm == INTERAC_CVM_SIGNATURE)
		{
			if(CST_Interac_IsInteracGuiMode())
			{
				nTimeout = GTL_StdTimer_GetRemaining(ulStartSignatureTime, C_SIGNATURE_TIMEOUT/10); 
				if (nTimeout > 0)
					ttestall(0,nTimeout);
			}

			GetMessageInfos(STD_MESS_SIGNATURE_OK, &tMsg);
			if ((bLoopMode) || (HelperQuestionYesNo (&tMsg, 5)))
			{
				Helper_Visa_SignatureOKIHM();
				CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_SIGNATURE_OK);
				bSaveInBatch = TRUE;
			}
			else
			{
				Helper_Visa_SignatureKOIHM();
				CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_SIGNATURE_KO);
			}
		}

		break;

	case (SDI_STATUS_ONLINE_REQUEST):				
		if (ucCvm == INTERAC_CVM_ONLINE_PIN) // If OnLine Pin Requested
		{    
			nPosition = SHARED_EXCHANGE_POSITION_NULL;
			if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_APPLI_PAN, &ulLgPan, &pPan) != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_Traces_TraceDebug ("CST_Interac_PerformTransaction : Missing PAN for Online PIN");
				bOnlinePinError = TRUE; // On-line Pin cannot be made
			}

			ulAmount = 0;
			nPosition = SHARED_EXCHANGE_POSITION_NULL;
			if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_AMOUNT_AUTH_NUM, &ulLgAmount, &pAmount) != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_Traces_TraceDebug ("CST_Interac_PerformTransaction : Missing Amount auth for Online PIN");
				bOnlinePinError = TRUE; // On-line Pin cannot be made : amount to display not available
			}
			else
			{
				GTL_Convert_DcbNumberToUl(pAmount, &ulAmount, ulLgAmount);
			}

			if (!bOnlinePinError)
			{
				char aucDummyMsg[] = "";

				// Warning, erase display must be made only if Pin input will be made on customer screen

				if (CST_IsPinpadPresent())
				{
					// Display dummy message to erase display
					tMsg.message = aucDummyMsg;
					tMsg.coding = _ISO8859_;
					tMsg.file = GetCurrentFont();
					
					Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, HELPERS_ALIGN_CENTER);
				}

				cr_pin_online = CST_PinManagement_OnLinePinManagement ((unsigned char*)pPan, 1, ulAmount, C_PINENTRY_TIMEOUT, 10000, &buffer_saisie);

				if (CST_IsPinpadPresent())
					Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, HELPERS_ALIGN_CENTER);

				if (cr_pin_online == INPUT_PIN_ON)
				{
					// Add a tag for on-line authorisation
					cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_CST_ENCIPHERED_PIN_CODE, buffer_saisie.nombre , (const unsigned char *)buffer_saisie.donnees);
					if (cr != STATUS_SHARED_EXCHANGE_OK)
					{
						GTL_Traces_TraceDebug("CST_Interac_PerformTransaction : Unable to add TAG_CST_ENCIPHERED_PIN_CODE in shared buffer (cr=%02x)", cr);
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
			Helper_Visa_OnlineProcessingIHM();
			CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ONLINE_PROCESSING);

			///////////////////////////////////////////////
			//////////// ON-LINE AUTHORISATION //////////// 
			///////////////////////////////////////////////
			if (CST_FinancialCommunication_ManageAuthorisation (pDataStruct, SDSA_KERNEL_IDENTIFIER_INTERAC))
			{
				nPosition = SHARED_EXCHANGE_POSITION_NULL;

				// Try to get the host response
				if (GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EMV_AUTHORISATION_RESPONSE_CODE, &ulReadLength, &pReadValue) == STATUS_SHARED_EXCHANGE_OK)
				{
					if ((pReadValue[0] == 0x30) && (pReadValue[1] == 0x30))
					{
						if (ucCvm == INTERAC_CVM_SIGNATURE)
						{
							Helper_Visa_SignatureCVMIHM();
							CST_DisplayScreen(SDSA_PAYPASS_SCREEN_SIGNATURE_REQUIRED);
							if(CST_Interac_IsInteracGuiMode())
									ulStartSignatureTime = GTL_StdTimer_GetCurrent();
						}
						else
						{
							Helper_Visa_ApprovedIHM(ONLINE);
							CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ONLINE_APPROVED);
							
							// Transaction shall be added to the batch
							bSaveInBatch = TRUE;
						}

						if (!bLoopMode)
				        {
							// print a receipt if kernel dictates

							nPosition = SHARED_EXCHANGE_POSITION_NULL;

							if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_INTERAC_RECEIPT_STATUS, &ulLgReceiptStatus, &pReceiptStatus) == STATUS_SHARED_EXCHANGE_OK)
							{
								if (*pReceiptStatus == INTERAC_RECEIPT_REQUIRED)
								{
									CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_INTERAC, APPROVED_TICKED, (ucCvm == INTERAC_CVM_SIGNATURE), WITH_AOSA);
								}

							}
							else
							{
								// Print a receipt only if signature requested or merchant need to print a receipt
								GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);

								if ((ucCvm == INTERAC_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30)))
									CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_INTERAC, APPROVED_TICKED, (ucCvm == INTERAC_CVM_SIGNATURE), WITH_AOSA);
							}
						}

						if(ucCvm == INTERAC_CVM_SIGNATURE)
						{
							if(CST_Interac_IsInteracGuiMode())
							{
								nTimeout = GTL_StdTimer_GetRemaining(ulStartSignatureTime, 500); 
								if (nTimeout == 0)
									ttestall(0,nTimeout);
							}

							GetMessageInfos(STD_MESS_SIGNATURE_OK, &tMsg);
							if ((bLoopMode) || (HelperQuestionYesNo (&tMsg, 5)))
							{
								Helper_Visa_SignatureOKIHM();
								CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_SIGNATURE_OK);
								bSaveInBatch = TRUE;
							}
							else
							{
								Helper_Visa_SignatureKOIHM();
								CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_SIGNATURE_KO);
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
			Helper_Visa_PinEntryKOIHM(FALSE);
			CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_PIN_KO);
		}

		if (ucOnLineDeclined) // Problem with communication or transaction rejected
		{
			Helper_Visa_DeclinedIHM(ONLINE);
			CST_DisplayScreen(SDSA_SCREEN_ONLINE_DECLINED);
		}
		break;

	case (SDI_STATUS_USE_OTHER_INTERFACE):
			nTransactionResult = SDI_STATUS_USE_OTHER_INTERFACE;
			break;

	case (SDI_STATUS_DECLINED):	
		Helper_Visa_DeclinedIHM(OFFLINE);
		CST_DisplayScreen(SDSA_SCREEN_OFFLINE_DECLINED);
		break;

	default: // Error case
		Helper_Visa_ErrorIHM();
		CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_STATUS_ERROR);
		break;
	}

	// Check if transaction shall be saved in the batch
	if (bSaveInBatch)
		__CST_Interac_AddRecordToBatch (pDataStruct);

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










//! \brief Check in the parameter file if the GUI mode to use is Visa Asia.

void CST_Interac_SetInteracGuiMode (void)
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
		if (pValue[0] == CLESS_GUI_MODE_INTERAC)
		{
			gs_bIsInteracGuiMode = TRUE;
			return;
		}
	}

	gs_bIsInteracGuiMode = FALSE;
}
