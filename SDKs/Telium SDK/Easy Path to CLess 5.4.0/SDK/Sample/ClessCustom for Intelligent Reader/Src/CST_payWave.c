/**
 * \file	CST_payWave.c
 * \brief 	Module that manages the payWave transaction.
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

static int __CST_payWave_RetreiveSignature (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pSignature);
static void __CST_payWave_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData);
static int __CST_payWave_ManageTransactionLog(void);
static int __CST_payWave_ManageAfterTxn(T_SHARED_DATA_STRUCT * pDataStruct, int * pnStepExecuted);
static int __CST_payWave_CheckISPConditions(T_SHARED_DATA_STRUCT * pDataStruct);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Get the payWave signature state.
//! \param[out] pSignature :
//!		- \a 0 No signature to made.
//!		- \a 1 Signature to made.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

static int __CST_payWave_RetreiveSignature (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pSignature)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	* pSignature = 0; // Default result : no signature
	
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_KERNEL_SIGNATURE_REQUESTED, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__CST_payWave_RetreiveSignature : Unable to get SigantureRequested from the payWave kernel response (cr = %02x)", cr);
		nResult = FALSE;
		goto End;
	}
	
	// Get the "signature requested" value
	* pSignature = pReadValue[0];
	
End:	
	return (nResult);
}


//! \brief Get the payWave PinOnLineRequired state.
//! \param[out] pPinOnLineRequiredState :
//!		- \a 0 No Pin OnLine Requested to made.
//!		- \a 1 Pin OnLine Requested to made.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

static int __CST_payWave_PinOnLineRequiredState (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pPinOnLineRequiredState)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	* pPinOnLineRequiredState = 0; // Default result : no PinOnLineRequired
	
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_KERNEL_ONLINE_PIN_REQUESTED, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__CST_payWave_RetreiveSignature : Unable to get OnLinePinRequested from the payWave kernel response (cr = %02x)", cr);
		nResult = FALSE;
		goto End;
	}
	
	// Get the "Pin Online requested" value
	* pPinOnLineRequiredState = pReadValue[0];
	
End:	
	return (nResult);
}



//! \brief If transaction Log has been configured and was managed by card, this function ask if Log must be printed and print it if necessary.

static int __CST_payWave_ManageTransactionLog(void)
{
	int cr = SDI_STATUS_UNKNOWN;
	int nResult = TRUE;
	MSGinfos tDisplayMsg;
	T_SHARED_DATA_STRUCT * pDataStruct = NULL;

	TLV_TREE_NODE hTlvTreeIn;
	TLV_TREE_NODE hTlvTreeOut = NULL;


	hTlvTreeIn = TlvTree_New(0);

	pDataStruct = GTL_SharedExchange_InitLocal(8192);	
	if ((hTlvTreeIn == NULL) || (pDataStruct == NULL))
	{
		GTL_Traces_TraceDebug("__CST_payWave_ManageTransactionLog : Init failed");
		nResult = FALSE;
		goto End;
	}

    // Add a tag to read in kernel
	TlvTree_AddChild(hTlvTreeIn, TAG_EMV_LOG_FORMAT, NULL, 0);
	TlvTree_AddChild(hTlvTreeIn, TAG_PAYWAVE_TRANSACTION_LOG_RECORD, NULL, 0);

	cr = SDI_Payment_GetData(nSDSAAppliId, hTlvTreeIn, &hTlvTreeOut);

	if ((cr == SDI_STATUS_OK) && (hTlvTreeOut != NULL)) // If a data has been obtained
	{
		// Copy data in the buffer
		CopyTlvTreeToDataStruct(hTlvTreeOut, pDataStruct);

		if(pDataStruct->ulDataLength)
		{
			// Print a receipt only if merchant need to print the transaction log
			GetMessageInfos(STD_MESS_PRINT_TRANSACTION_LOG, &tDisplayMsg);

			if (HelperQuestionYesNo (&tDisplayMsg, 30))
				CST_DumpData_DumpSharedBufferWithTitle (pDataStruct, "Transaction Log :");
		}

		TlvTree_ReleaseEx (&hTlvTreeOut);
	}

End:
	// Destroy the buffer
	if (pDataStruct)
		GTL_SharedExchange_DestroyLocal(pDataStruct);

	TlvTree_ReleaseEx (&hTlvTreeIn);

	if(cr == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();

	return (nResult);
}


//! \brief Add the transaction record in the batch file.
//! \param[in] pSharedData Shared buffer that contains the data to add in the batch file.
//! \note For payWave, pSharedData is the one returned by the payWave kernel on the DoTransaction function.

static void __CST_payWave_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData)
{
	
	if (!CST_Batch_AddTransactionToBatch (pSharedData))
	{
		GTL_Traces_TraceDebug ("__CST_payWave_AddRecordToBatch : Save transaction in batch failed");
		Helper_DisplayMessage(STD_MESS_BATCH_ERROR, ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_RefreshScreen(WAIT);
	}
}


//! \brief Check if Issuer Script could be executed.
//! \param[in] pSharedStructure Shared buffer that contains the transaction data.
//! \return
//!		- \a TRUE if ISP could be executed.
//!		- \a FALSE else.

static int __CST_payWave_CheckISPConditions(T_SHARED_DATA_STRUCT * pSharedStructure)
{
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;

	// Get TTQ
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext(pSharedStructure, &nPosition, TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS, &ulReadLength, &pReadValue);
	if (cr == STATUS_SHARED_EXCHANGE_OK)
	{
		if ((pReadValue[2] & 0x80) == 0)
		{	// Sorry, TTQ not configurated for ISP management => end
			GTL_Traces_TraceDebug("__CST_payWave_CheckISPConditions : TTQ not configurated for ISP management");
			return(FALSE);
		}
	}

	// Get CTQ
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext(pSharedStructure, &nPosition, TAG_PAYWAVE_CARD_TRANSACTION_QUALIFIERS, &ulReadLength, &pReadValue);
	if (cr == STATUS_SHARED_EXCHANGE_OK)
	{
		if ((pReadValue[1] & 0x40) == 0)
		{	// Sorry, CTQ not configurated for ISP management => end
			GTL_Traces_TraceDebug("__CST_payWave_CheckISPConditions : CTQ not configurated for ISP management");
			return(FALSE);
		}
	}

	return(TRUE);
}


//! \brief Perform the step after the transaction.
//! \param[in,out] pDataStruct Shared buffer that contains the transaction data (Issuer Script Result will be added if needed).
//! \param[out] nStepExecuted Boolean set to TRUE if post transcation processing is performed.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

static int __CST_payWave_ManageAfterTxn(T_SHARED_DATA_STRUCT * pDataStruct, int * pnStepExecuted)
{
	int nResult, nSdiResult = SDI_STATUS_UNKNOWN, cr, cr2;
	int nPosition;
	int nIssuerScriptPresent = FALSE;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	T_SHARED_DATA_STRUCT * pLocalStructure;
	T_SHARED_DATA_STRUCT * pTmpStructure;
	FILE * hKeyboard;
	int nEvent;
	TLV_TREE_NODE hTlvTreeIn;
	TLV_TREE_NODE hTlvTreeOut = NULL;


	// Local variable initialisation
	*pnStepExecuted = FALSE; // Default value : afterTxn hasn't been executed;

	pLocalStructure = GTL_SharedExchange_InitLocal(1024);
	pTmpStructure = GTL_SharedExchange_InitLocal(32768);

	// Default Result
	cr = OK;

	if ((pLocalStructure != NULL) && (pTmpStructure != NULL))
	{
		// Add TAG_EMV_ISSUER_AUTHENTICATION_DATA tag, this tag must be treated first !
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		cr = GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EMV_ISSUER_AUTHENTICATION_DATA, &ulReadLength, &pReadValue);
		if (cr == STATUS_SHARED_EXCHANGE_OK)
		{
			nResult = GTL_SharedExchange_AddTag(pLocalStructure, TAG_EMV_ISSUER_AUTHENTICATION_DATA, ulReadLength, pReadValue);

			if (nResult == STATUS_SHARED_EXCHANGE_OK)
				nIssuerScriptPresent = TRUE;
			else
				GTL_Traces_TraceDebug("__CST_payWave_ManageAfterTxn : Unable to add TAG_ISSUER_AUTH_DATA (nResult = %02x)", nResult);
		}

		{
			T_BER_TLV_DECODE_STRUCT BerTlvStruct;

		    GTL_BerTlvDecode_Init (&BerTlvStruct, pDataStruct->nPtrData, pDataStruct->ulDataLength);


		    /* ----------------------------------------------------------------*/
		    // Parse Script  T1:71 or 72 L1 V1 ... Tn:71 or 72 Ln Vn
		    for (;;)
		    {
		        /* Problem of script overwriting */
		        int BytesRead;
		        BER_TLV_TAG ReadTag;
		        T_TI_LENGTH ReadLength;
		        T_TI_VALUE  ReadValue;


		        //! \brief Parse the next tag in the BER-TLV structure.
		        cr = GTL_BerTlvDecode_ParseTlv (&BerTlvStruct, &ReadTag, &ReadLength, (BER_TLV_VALUE*)&ReadValue, (unsigned char)FALSE, &BytesRead);

		        if (cr == STATUS_BER_TLV_END)
		            break ;

                if (cr == STATUS_BER_TLV_OK)
                {
                    if ((ReadTag == TAG_EMV_ISSUER_SCRIPT_TEMPLATE_1) || (ReadTag == TAG_EMV_ISSUER_SCRIPT_TEMPLATE_2))
                    {
        				nResult = GTL_SharedExchange_AddTag(pTmpStructure, ReadTag, ReadLength, ReadValue);

        				if (nResult != STATUS_SHARED_EXCHANGE_OK)
        					GTL_Traces_TraceDebug("__CST_payWave_ManageAfterTxn : Unable to add TAG_EMV_ISSUER_SCRIPT_TEMPLATE_1 (nResult = %02x)", nResult);
                    }
                }
                else
                    break; // An error occurs
		    } // end of loop about Script parsing
		}

		// Check if TAG_PAYWAVE_ISSUER_SCRIPT_LIST tag must be updated
		if (pTmpStructure->ulDataLength)
		{
			nResult = GTL_SharedExchange_AddTag(pLocalStructure, TAG_PAYWAVE_ISSUER_SCRIPT_LIST, pTmpStructure->ulDataLength, pTmpStructure->nPtrData);
			if (nResult == STATUS_SHARED_EXCHANGE_OK)
				nIssuerScriptPresent = TRUE;
			else
				GTL_Traces_TraceDebug("__CST_payWave_ManageAfterTxn : Unable to add TAG_PAYWAVE_ISSUER_SCRIPT_LIST (nResult = %02x)", nResult);
		}

		// Default Result
		cr = OK;

		// If Issuer authorization and/or script must be executed
		if (nIssuerScriptPresent)
		{
			// Get all the kernel data
			CST_Term_GetAllData(pTmpStructure);
			
			if (__CST_payWave_CheckISPConditions(pTmpStructure) == TRUE)
			{
				hTlvTreeIn = TlvTree_New(0);
				if (hTlvTreeIn != NULL)
				{
					CopyDataStructInTLVTree(pLocalStructure, hTlvTreeIn);

					// Open the keyboard driver
					hKeyboard = fopen("KEYBOARD", "r");

					Helper_DisplayMessage(PAYWAVE_MESS_REPRESENT_CARD, ERASE, HELPERS_MERCHANT_LINE_2);
					Helper_RefreshScreen(NOWAIT);

					// Perform the post transaction processing
					nSdiResult = SDI_Payment_TxnPostProcessing (nSDSAAppliId, hTlvTreeIn, E_USER_EVENT);
					if(nSdiResult == SDI_STATUS_OK)
					{
						// Scan the keyboard, check for cancel
						nSdiResult = SDI_STATUS_ANSWER_NOT_YET_RECEIVED;
						do
						{
							nEvent = ttestall(USER_EVENT | KEYBOARD, 1);

							if(nEvent & USER_EVENT)
							{
								nSdiResult = SDI_Payment_GetPostProcessingResult(&hTlvTreeOut);
							}
							if((nEvent & KEYBOARD))
							{
								if (getchar() == T_ANN) // Cancel only if red key pressed
								{
									SDI_Payment_CancelTransaction(nSDSAAppliId);
								}
							}
						}while( nSdiResult == SDI_STATUS_ANSWER_NOT_YET_RECEIVED );
					}

					// Close the keyboard driver
					fclose (hKeyboard);

					*pnStepExecuted = TRUE; // afterTxn has been executed;

					// Clear buffer
					GTL_SharedExchange_ClearEx (pLocalStructure, FALSE);

					if(hTlvTreeOut != NULL)
						CopyTlvTreeToDataStruct(hTlvTreeOut, pLocalStructure);

					// Get Issuer Script Result
					nPosition = SHARED_EXCHANGE_POSITION_NULL;

					cr2 = GTL_SharedExchange_FindNext(pLocalStructure, &nPosition, TAG_PAYWAVE_ISSUER_SCRIPT_RESULT, &ulReadLength, &pReadValue);
					if (cr2 == STATUS_SHARED_EXCHANGE_OK)
					{
						// Put Issuer Script Result in exchange struct given in parameter
						nResult = GTL_SharedExchange_AddTag(pDataStruct, TAG_PAYWAVE_ISSUER_SCRIPT_RESULT, ulReadLength, pReadValue);

						if (nResult != STATUS_SHARED_EXCHANGE_OK)
							GTL_Traces_TraceDebug("__CST_payWave_ManageAfterTxn : Unable to add TAG_PAYWAVE_ISSUER_SCRIPT_RESULT (nResult = %02x)", nResult);
					}
					TlvTree_ReleaseEx (&hTlvTreeOut);
					TlvTree_ReleaseEx (&hTlvTreeIn);
				}
			}
		}
	}
	else
		GTL_Traces_TraceDebug("__CST_payWave_ManageAfterTxn : GTL_SharedExchange_InitShared error");

	// Destroy the shared buffers
	if (pTmpStructure)
		GTL_SharedExchange_DestroyLocal(pTmpStructure);
	if (pLocalStructure)
		GTL_SharedExchange_DestroyLocal(pLocalStructure);

	if(nSdiResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();

	return (cr);
}


//! \brief Specific management for payWave end of transaction according to transaction result.
//! Displays specific messages, manages batch, manages online authorization, manages CVM ...
//! \param[in] pDataStruct Transaction output data. 
//! \param[in] nTransactionOutcome Transaction result.
//! \return The transaction outcome value.

int CST_payWave_Transaction(T_SHARED_DATA_STRUCT * pDataStruct, int nTransactionOutcome)
{
	unsigned char bLoopMode;
	unsigned char ucSignature, ucOnLinePinRequested;
	unsigned char bOnlinePinError = FALSE;
	MSGinfos tDisplayMsg;	
	int cr, nFound;
	int bSaveInBatch = FALSE;
	int nPosition;
	int nCurrencyCode;
	const unsigned char * pPan;
	unsigned long ulLgPan;
	unsigned long ulAmount = 0;
	unsigned long ulLgAmount;
	const unsigned char * pAmount;
	unsigned char * pInfo;
	unsigned char * pCurrencyCode;
	BUFFER_SAISIE buffer_saisie;
	unsigned char cr_pin_online = 0;
	unsigned char ucOnLineDeclined;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	int nAfterTxnExecuted = FALSE;
	int nTransactionResult;
	
	nTransactionResult = nTransactionOutcome;

	// Debug purpose : if you need to dump the data provided by the kernel
	if (CST_Menu_IsTransactionDataDumpingOn())
		CST_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATA RECORD");

	// Loop mode information
	bLoopMode = CST_Menu_IsTransactionLoopOn();

	ucSignature = 0;
	ucOnLinePinRequested = 0;

	// Check if signature is requested or not
	__CST_payWave_RetreiveSignature(pDataStruct, &ucSignature);

	// Check if pin online is requested or not
	__CST_payWave_PinOnLineRequiredState (pDataStruct, &ucOnLinePinRequested);

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
	
	// nTransactionOutcome analyse

	if(nTransactionOutcome == SDI_STATUS_CANCELLED)
	{
		nTransactionResult = SDI_STATUS_CANCELLED;
	}
	else
	{
		// payWave 2.1 chapter 5.19
		// Note: An AAC returned by the card application for refunds and credits simply indicates completion of card action analysis, 
		// and should not be treated as a "decline" of the refund.
		if (nTransactionOutcome == SDI_STATUS_DECLINED)
		{
			if (CST_Term_RetreiveInfo (pDataStruct, TAG_EMV_TRANSACTION_TYPE, &pInfo))
			{
				if (pInfo[0] == SDSA_TRANSACTION_TYPE_REFUND)
				{
					if (CST_Term_RetreiveInfo (pDataStruct, TAG_PAYWAVE_DECLINED_BY_CARD, &pInfo))
					{
						// => transaction must be accepted
						nTransactionOutcome = SDI_STATUS_APPROVED;

						// Get all the kernel data to print the receipt
						CST_Term_GetAllData(pDataStruct);
					}
				}
			}
		}

		switch (nTransactionOutcome)
		{
		case (SDI_STATUS_OK):
			Helper_DisplayMessage(STD_MESS_ERROR_STATUS, ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_RefreshScreen(NOWAIT);

			CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_STATUS_ERROR);		
			break;

		case (SDI_STATUS_APPROVED):
			if(ucSignature)
			{
				Helper_Visa_SignatureCVMIHM();
				CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_SIGNATURE_REQUIRED);
			}
			else
			{
				Helper_Visa_ApprovedIHM(OFFLINE);
				CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_OFFLINE_APPROVED);

				// Transaction shall be added to the batch
				bSaveInBatch = TRUE;
			}

			if (!bLoopMode)
			{
				// Print a receipt only if signature requested or merchant need to print a receipt	
				GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tDisplayMsg);

				if ((CST_DumpData_GetOutputId() != CST_OUTPUT_NONE) &&  ((ucSignature) || (HelperQuestionYesNo (&tDisplayMsg, 30))))
					CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_VISA, APPROVED_TICKED, ucSignature, WITH_AOSA);
			}

			if (ucSignature)
			{
				GetMessageInfos(STD_MESS_SIGNATURE_OK, &tDisplayMsg);
				if ((bLoopMode) || (HelperQuestionYesNo (&tDisplayMsg, 30)))
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

			__CST_payWave_ManageTransactionLog();

			break;

		case (SDI_STATUS_DECLINED):
			Helper_Visa_DeclinedIHM(OFFLINE);
			CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_OFFLINE_DECLINED);

			if (!bLoopMode)
			{
				// Print a receipt only if merchant need to print a receipt
				GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tDisplayMsg);

				if ((CST_DumpData_GetOutputId() != CST_OUTPUT_NONE) &&  (HelperQuestionYesNo (&tDisplayMsg, 30)))
					CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_VISA, DECLINED_TICKED, WITHOUT_SIGNATURE, WITH_AOSA);
			}

			__CST_payWave_ManageTransactionLog();

			break;

		case (SDI_STATUS_ONLINE_REQUEST):				
			// Is Online Pin asked and possible ?
			if (ucOnLinePinRequested) // If OnLine Pin Requested
			{
				ucSignature = 0;

				nPosition = SHARED_EXCHANGE_POSITION_NULL;
				if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_APPLI_PAN, &ulLgPan, &pPan) != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug ("CST_payWave_PerformTransaction : Missing PAN for Online PIN");
					bOnlinePinError = TRUE; // On-line Pin cannot be made
				}

				ulAmount = 0;
				nPosition = SHARED_EXCHANGE_POSITION_NULL;
				if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_AMOUNT_AUTH_NUM, &ulLgAmount, &pAmount) != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug ("CST_payWave_PerformTransaction : Missing Amount auth for Online PIN");
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
						tDisplayMsg.message = aucDummyMsg;
						tDisplayMsg.coding = _ISO8859_;
						tDisplayMsg.file = GetCurrentFont();
						Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tDisplayMsg, HELPERS_ALIGN_CENTER);
					}

					cr_pin_online = CST_PinManagement_OnLinePinManagement ((unsigned char*)pPan, 1, ulAmount, 30000, 10000, &buffer_saisie);

					if (CST_IsPinpadPresent())
						Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tDisplayMsg, HELPERS_ALIGN_CENTER);

					if (cr_pin_online == INPUT_PIN_ON)
					{
						// Add a tag for on-line authorisation
						cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_CST_ENCIPHERED_PIN_CODE, buffer_saisie.nombre , (const unsigned char *)buffer_saisie.donnees);
						if (cr != STATUS_SHARED_EXCHANGE_OK)
						{
							GTL_Traces_TraceDebug("CST_payWave_PerformTransaction : Unable to add TAG_CST_ENCIPHERED_PIN_CODE in shared buffer (cr=%02x)", cr);
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
				CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_ONLINE_PROCESSING);

				///////////////////////////////////////////////
				//////////// ON-LINE AUTHORISATION //////////// 
				///////////////////////////////////////////////
				if (CST_FinancialCommunication_ManageAuthorisation (pDataStruct, SDSA_KERNEL_IDENTIFIER_PAYWAVE))
				{
					nPosition = SHARED_EXCHANGE_POSITION_NULL;

					// Try to get the host response
					if (GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EMV_AUTHORISATION_RESPONSE_CODE, &ulReadLength, &pReadValue) == STATUS_SHARED_EXCHANGE_OK)
					{
						if ((pReadValue[0] == 0x30) && (pReadValue[1] == 0x30))
						{
							__CST_payWave_ManageAfterTxn(pDataStruct, &nAfterTxnExecuted); // Result not used to known if transaction is  accepted or not

							if (ucSignature)
							{
								Helper_Visa_SignatureCVMIHM();
								CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_SIGNATURE_REQUIRED);
							}
							else
							{
								Helper_Visa_ApprovedIHM(ONLINE);

								if (nAfterTxnExecuted)
									CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_ONLINE_APPROVED_WITHOUT_AOSA);
								else
									CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_ONLINE_APPROVED_WITH_AOSA);

								// Transaction shall be added to the batch
								bSaveInBatch = TRUE;
							}

							if (!bLoopMode)
							{
								// Print a receipt only if signature requested or merchant need to print a receipt
								GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tDisplayMsg);

								if ((CST_DumpData_GetOutputId() != CST_OUTPUT_NONE) && ((ucSignature) || (HelperQuestionYesNo (&tDisplayMsg, 30))))
								{
									if (nAfterTxnExecuted)
										CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_VISA, APPROVED_TICKED, ucSignature, WITHOUT_AOSA);
									else
										CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_VISA, APPROVED_TICKED, ucSignature, WITH_AOSA);
								}
							}

							if (ucSignature)
							{
								GetMessageInfos(STD_MESS_SIGNATURE_OK, &tDisplayMsg);
								if ((bLoopMode) || (HelperQuestionYesNo (&tDisplayMsg, 30)))
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
					// Unable to go online
					ucOnLineDeclined = TRUE;
				}
			}
			else
			{
				if(!CST_VisaWave_IsVisaAsiaGuiMode())
				{
					Helper_Visa_PinEntryKOIHM(cr_pin_online == CANCEL_INPUT);

					if (cr_pin_online == CANCEL_INPUT) 
						CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_PIN_CANCELED);
					else
						CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_PIN_KO);
				}
				else
				{
					Helper_Visa_PinEntryKOIHM(FALSE);
					CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_PIN_KO);
				}

				GTL_Traces_TraceDebug ("CST_payWave_PerformTransaction : An error occured for PIN Entry");
			}

			if (ucOnLineDeclined) // Problem with communicatigon or transaction rejected
			{
				Helper_Visa_DeclinedIHM(ONLINE);
				CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_ONLINE_DECLINED);
			}

			__CST_payWave_ManageTransactionLog();

			break;

		case (SDI_STATUS_USE_OTHER_INTERFACE):
			nTransactionResult = SDI_STATUS_USE_OTHER_INTERFACE;
			break;

		default: // Error case
			// For Visa Europe, no error should be displayed.
			// If the CST application is configured in Visa Europe mode, transaction shall be conducted over another interface
			if(!CST_Menu_IsVisaEuropeModeOn())
			{
				Helper_Visa_ErrorIHM();
				CST_DisplayScreen(SDSA_PAYWAVE_SCREEN_ERROR);
			}
			else
			{
				nTransactionResult = SDI_STATUS_USE_OTHER_INTERFACE;
			}
			break;
		}
	}

	if(bSaveInBatch)
		__CST_payWave_AddRecordToBatch (pDataStruct);

	// Increment 
	CST_Batch_IncrementTransactionSeqCounter();

	// If activated, dump all the kernel database
	if (CST_Menu_IsTransactionDatabaseDumpingOn())
	{
		// Get all the kernel data
		if(CST_Term_GetAllData(pDataStruct))
			CST_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATABASE DUMP");
	}

	return(nTransactionResult);
}
