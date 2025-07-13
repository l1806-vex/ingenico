/**
 * \file	CST_Discover.c
 * \brief 	Module that manages the Discover transaction.
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




/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static void __CST_Discover_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////






//! \brief Add the transaction record in the batch file.
//! \param[in] pSharedData Shared buffer to be used to get all the record data.

static void __CST_Discover_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData)
{	
	if (!CST_Batch_AddTransactionToBatch (pSharedData))
	{
		GTL_Traces_TraceDebug ("__CST_Discover_AddRecordToBatch : Save transaction in batch failed");
		Helper_DisplayMessage(STD_MESS_BATCH_ERROR, ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_RefreshScreen(WAIT);
	}
}


//! \brief Specific management for Discover end of transaction according to transaction result.
//! Displays specific messages, manages batch, manages online authorization, manages CVM ...
//! \param[in] pDataStruct Transaction output data. 
//! \param[in] nTransactionOutcome Transaction result.
//! \return The transaction outcome value.

int CST_Discover_Transaction(T_SHARED_DATA_STRUCT * pDataStruct, int nTransactionOutcome)
{
	unsigned char bLoopMode;
	MSGinfos tMsg;
	int nFound;
	int bSaveInBatch = FALSE;
	int nPosition;
	int nCurrencyCode;
	unsigned long ulAmount = 0;
	unsigned long ulLgAmount;
	unsigned char * pInfo;
	unsigned char * pCurrencyCode;
	unsigned char ucOnLineDeclined = FALSE;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	int nTransactionResult;


	nTransactionResult = nTransactionOutcome;

	// Debug purpose : if you need to dump the data provided by the kernel
	if (CST_Menu_IsTransactionDataDumpingOn())
		CST_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATA RECORD");

	// Loop mode information
	bLoopMode = CST_Menu_IsTransactionLoopOn();

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
		{
			Helper_Visa_ApprovedIHM(OFFLINE);
			CST_DisplayScreen(SDSA_SCREEN_OFFLINE_APPROVED);

			// Transaction shall be added to the batch
			bSaveInBatch = TRUE;
			
			if (!bLoopMode)
			{
				// Print a receipt only if signature requested or merchant need to print a receipt	
				GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);
			
				if (HelperQuestionYesNo (&tMsg, 30))
					CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_DISCOVER, APPROVED_TICKED, FALSE, WITH_AOSA);
			}
		}
		break;

		case (SDI_STATUS_ONLINE_REQUEST):				
			{
				Helper_Visa_OnlineProcessingIHM();
				CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ONLINE_PROCESSING);

				///////////////////////////////////////////////
				//////////// ON-LINE AUTHORISATION //////////// 
				///////////////////////////////////////////////
				if (CST_FinancialCommunication_ManageAuthorisation (pDataStruct, SDSA_KERNEL_IDENTIFIER_DISCOVER))
				{
					nPosition = SHARED_EXCHANGE_POSITION_NULL;

					// Try to get the host response
					if (GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EMV_AUTHORISATION_RESPONSE_CODE, &ulReadLength, &pReadValue) == STATUS_SHARED_EXCHANGE_OK)
					{
						if ((pReadValue[0] == 0x30) && (pReadValue[1] == 0x30))
						{
							{
								Helper_Visa_ApprovedIHM(ONLINE);
								CST_DisplayScreen(SDSA_PAYPASS_SCREEN_ONLINE_APPROVED);
								
								// Transaction shall be added to the batch
								bSaveInBatch = TRUE;
							}

							if (!bLoopMode)
							{
								// Print a receipt only if signature requested or merchant need to print a receipt
								GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);
							
								if (HelperQuestionYesNo (&tMsg, 30))
									CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_DISCOVER, APPROVED_TICKED, FALSE, WITH_AOSA);
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
		__CST_Discover_AddRecordToBatch (pDataStruct);

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

