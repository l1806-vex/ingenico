/**
 * \file	CST_ExpressPay.c
 * \brief 	Module that manages the ExpressPay transaction.
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

const unsigned char ARC_00[]={0x30, 0x30};
const unsigned char ARC_08[]={0x30, 0x38};
const unsigned char ARC_10[]={0x31, 0x30};
const unsigned char ARC_11[]={0x31, 0x31};

/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

word g_TimerTask;											// To store the timer task ID.
t_topstack * g_tsTimer_task_handle;							// Handle of the timer task.

static word g_wCurrentTask;
static unsigned char g_bTimer_task_to_be_killed = FALSE;	// Global variable used to stop the timer task.
static int g_bTimerTaskRunning = FALSE;						// Indicates if the timer task is still running or if it is waiting to be killed.
static int g_bTimerExpired = FALSE;							// Global variable used to indicate that removal timer expired.
	
static unsigned long gs_ulStartRemovalTimerTime = 0;		// Removal Timer

static unsigned char gs_bTxnWentOnline = FALSE;				// Global variable indicated if the transaction was able to go online during the first part of an EMV Full Online transaction.


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static int __CST_ExpressPay_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm);
static T_Bool __CST_ExpressPay_OnlinePinManagement (T_SHARED_DATA_STRUCT * pStructureForOnlineData);
static int __CST_ExpressPay_TransactionPostProcessing(T_SHARED_DATA_STRUCT * pDataStruct);
static int __CST_ExpressPay_ActionCodeDefaultCheck (void);
static void __CST_ExpressPay_AddIssuerScripts (T_SHARED_DATA_STRUCT *pTransactionData);
static int __CST_ExpressPay_IsOnlineOnly (T_SHARED_DATA_STRUCT * pDataStruct);

static int __CST_ExpressPay_GetRemovalTimeOut (unsigned long *pRemovalTimeOut);
static word __CST_ExpressPay_StartTimerTask (void);
static void __CST_ExpressPay_InitTimerVariables (void);
static int __CST_ExpressPay_LaunchRemovalTimerTask (void);
static void __CST_ExpressPay_KillTimerTask (void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Get the ExpressPay CVM to perform.
//! \param[out] pCvm Retreived transaction CVM :
//!		- \a EXPRESSPAY_CVM_NO_CVM No CVM to be performed.
//!		- \a EXPRESSPAY_CVM_SIGNATURE if signature shall be performed.
//!		- \a EXPRESSPAY_CVM_ONLINE_PIN if online PIN shall be performed.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

static int __CST_ExpressPay_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm)
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
	
	// Get the CVM to be performed
	* pCvm = pReadValue[0];
	
End:	
	return (nResult);
}


//! \brief Perform the Online PIN input and encipher PIN.
//! \param[out] pStructureForOnlineData Data returned by the kernel in which the enciphered online PIN would be added.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

static T_Bool __CST_ExpressPay_OnlinePinManagement (T_SHARED_DATA_STRUCT * pStructureForOnlineData)
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
			GTL_Traces_TraceDebug("__CST_ExpressPay_OnlinePinManagement : An error occured when getting tags from the ExpressPay kernel (cr=%02x)", cr);
			
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
			GTL_Traces_TraceDebug ("__CST_ExpressPay_OnlinePinManagement : Missing PAN for Online PIN");
			nResult = B_FALSE;
			goto End;
		}

		// Get the transaction amount (numeric)
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pDataRequest, &nPosition, TAG_EMV_AMOUNT_AUTH_NUM, &ulAmountLength, &pAmount) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug ("__CST_ExpressPay_OnlinePinManagement : Missing Amount for Online PIN");
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
				GTL_Traces_TraceDebug ("__CST_ExpressPay_OnlinePinManagement : Unable to add TAG_CST_ENCIPHERED_PIN_CODE in the shared buffer (cr = %02x)", cr);
				nResult = B_FALSE;
				goto End;
			}
		}
		else if (cr == CANCEL_INPUT)
		{
				GTL_Traces_TraceDebug ("__CST_ExpressPay_OnlinePinManagement : input pin Cancelled");
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


//! \brief Specific management for ExpressPay end of transaction according to transaction result.
//! Displays specific messages, manages batch, manages online authorization, manages CVM ...
//! \param[in] pDataStruct Transaction output data. 
//! \param[in] nTransactionOutcome Transaction result.
//! \return The transaction outcome value.

int CST_ExpressPay_Transaction(T_SHARED_DATA_STRUCT * pDataStruct, int nTransactionOutcome)
{
	unsigned char bLoopMode;
	int ret;
	MSGinfos tMsg;
	int nPosition;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	int nTransactionResult;
	unsigned char ucCvm;
	T_Bool bContinueWithOnlineAuthorisation = B_TRUE;
	unsigned char bUnableToGoOnline = FALSE;
	unsigned char bARCOnlineApproved = FALSE;
	unsigned char bCommunicationResult;
	int nMsgNumber;


	nTransactionResult = nTransactionOutcome;

	// Debug purpose : if you need to dump the data provided by the kernel
	if (CST_Menu_IsTransactionDataDumpingOn())
		CST_DumpData_DumpSharedBufferWithTitle (pDataStruct, "DATA RECORD");

	// Loop mode information
	bLoopMode = CST_Menu_IsTransactionLoopOn();

	gs_bTxnWentOnline = FALSE;

	// Get the TAG_EXPRESSPAY_TRANSACTION_CVM to identify the CVM to be performed :
	// 	- EXPRESSPAY_CVM_NO_CVM (0x01) : "No CVM" method has been applied.
	// 	- EXPRESSPAY_CVM_SIGNATURE (0x02) : "Signature" method has been applied.
	// 	- EXPRESSPAY_CVM_ONLINE_PIN (0x04) : "Online PIN" method has been applied.
	if (!__CST_ExpressPay_RetreiveCvmToApply (pDataStruct, &ucCvm))
	{
		ucCvm = EXPRESSPAY_CVM_NO_CVM;
	}
	
Restart:
	switch (nTransactionOutcome)
	{
	case (SDI_STATUS_APPROVED):
	case (EXPRESSPAY_STATUS_EMV_FULL_ONLINE_APPROVED):

		if((nTransactionOutcome == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_APPROVED) && gs_bTxnWentOnline)
			nMsgNumber = STD_MESS_ONLINE_APPROVED;
		else
			nMsgNumber = STD_MESS_OFFLINE_APPROVED;

		if (ucCvm == EXPRESSPAY_CVM_SIGNATURE)
		{
			Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_MERCHANT_LINE_4);
			Helper_RefreshScreen(NOWAIT);
			CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_SIGNATURE_REQUIRED);
		}
		else
		{
			Helper_DisplayMessage(nMsgNumber, ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_RefreshScreen(NOWAIT);
			if((nTransactionOutcome == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_APPROVED) && gs_bTxnWentOnline)
				CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_ONLINE_APPROVED);
			else
				CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_OFFLINE_APPROVED);
		}
		
		if (!bLoopMode)
		{
			// Print a receipt only if merchant need to print a receipt	
			GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);

			if ((CST_DumpData_GetOutputId() != CST_OUTPUT_NONE) && ((ucCvm == EXPRESSPAY_CVM_SIGNATURE) ||  (HelperQuestionYesNo (&tMsg, 30))))
				CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_AMEX, APPROVED_TICKED, (ucCvm == EXPRESSPAY_CVM_SIGNATURE), WITH_AOSA);
		}

		if (ucCvm == EXPRESSPAY_CVM_SIGNATURE)
		{
			GetMessageInfos(STD_MESS_SIGNATURE_OK, &tMsg);
			if (HelperQuestionYesNo (&tMsg, 30))
			{
				Helper_DisplayMessage(STD_MESS_SIGNATURE_CORRECT, ERASE, HELPERS_MERCHANT_LINE_3);
				Helper_RefreshScreen(NOWAIT);
				
				CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_APPROVED);
			}
			else
			{
				Helper_DisplayMessage(STD_MESS_SIGNATURE_INCORRECT, ERASE, HELPERS_MERCHANT_LINE_3);
				Helper_RefreshScreen(NOWAIT);

				CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_OFFLINE_DECLINED);
			}
		}
		break;

	case (SDI_STATUS_DECLINED):	
	case (EXPRESSPAY_STATUS_EMV_FULL_ONLINE_DECLINED):
	
		if((nTransactionOutcome == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_DECLINED) && gs_bTxnWentOnline)
			nMsgNumber = STD_MESS_ONLINE_DECLINED;
		else
			nMsgNumber = STD_MESS_OFFLINE_DECLINED;

		Helper_DisplayMessage(nMsgNumber, ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_RefreshScreen(NOWAIT);

		if((nTransactionOutcome == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_DECLINED) && gs_bTxnWentOnline)
			CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_ONLINE_DECLINED);
		else
			CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_OFFLINE_DECLINED);
		break;

	case (EXPRESSPAY_STATUS_MAGSTRIPE_ONLINE_AUTHORISATION):
	case (EXPRESSPAY_STATUS_EMV_PARTIAL_ONLINE_AUTHORISATION):
	case (EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION):
		if (ucCvm == EXPRESSPAY_CVM_ONLINE_PIN)
		{
			bContinueWithOnlineAuthorisation = __CST_ExpressPay_OnlinePinManagement (pDataStruct);
		}
		if (bContinueWithOnlineAuthorisation == B_TRUE)
		{
			if(nTransactionOutcome == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
			{
				Helper_DisplayMessage(EXPRESSPAY_MESS_PROCESSING, ERASE, HELPERS_MERCHANT_LINE_3);
				Helper_DisplayMessage(EXPRESSPAY_MESS_PLEASE_WAIT, NO_ERASE, HELPERS_MERCHANT_LINE_4);
				Helper_RefreshScreen(NOWAIT);

				CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_PROCESSING);
			}
			else
			{
				Helper_DisplayMessage(STD_MESS_ONLINE_REQUEST, ERASE, HELPERS_MERCHANT_LINE_3);
				Helper_RefreshScreen(NOWAIT);

				CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_ONLINE_PROCESSING);
			}
		
			if(nTransactionOutcome == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
				__CST_ExpressPay_LaunchRemovalTimerTask ();

			bCommunicationResult = CST_FinancialCommunication_ManageAuthorisation (pDataStruct, SDSA_KERNEL_IDENTIFIER_EXPRESSPAY);

			if(nTransactionOutcome == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
			{
				// Kill the timer task
				__CST_ExpressPay_KillTimerTask();

				// Removal timer expired, transaction is completed as partial online transaction
				if (g_bTimerExpired)
					nTransactionOutcome = EXPRESSPAY_STATUS_EMV_PARTIAL_ONLINE_AUTHORISATION;
			}

			if (bCommunicationResult)
			{
				if(nTransactionOutcome == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
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
								GTL_Traces_TraceDebug("CST_ExpressPay_Transaction: Unable to add TAG_EXPRESSPAY_ARC_ONLINE_APPROVED in shared buffer (ret=%02x)", ret);

						}

						// If TAG_EMV_ISSUER_AUTHENTICATION_DATA are present, this tag is sent to the kernel.

						gs_bTxnWentOnline = TRUE;
					}
					else
					{
						bUnableToGoOnline = TRUE;
						ret = GTL_SharedExchange_AddTag(pDataStruct, TAG_EXPRESSPAY_UNABLE_TO_GO_ONLINE, 1, &bUnableToGoOnline);
						if (ret != STATUS_SHARED_EXCHANGE_OK)
							GTL_Traces_TraceDebug("CST_ExpressPay_Transaction: Unable to add TAG_EXPRESSPAY_UNABLE_TO_GO_ONLINE in shared buffer (ret=%02x)", ret);
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
								Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_MERCHANT_LINE_3);
								Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_MERCHANT_LINE_4);
								Helper_RefreshScreen(NOWAIT);
								CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_SIGNATURE_REQUIRED);
							}
							else
							{
								Helper_DisplayMessage(STD_MESS_ONLINE_APPROVED, ERASE, HELPERS_MERCHANT_LINE_3);
								Helper_RefreshScreen(NOWAIT);
								CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_ONLINE_APPROVED);
							}

							// Get all the kernel data to print the receipt
							CST_Term_GetAllData(pDataStruct);

							if (!bLoopMode)
							{
								GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);

								if ((CST_DumpData_GetOutputId() != CST_OUTPUT_NONE) && ((ucCvm == EXPRESSPAY_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30))))
									CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_AMEX, APPROVED_TICKED, (ucCvm == EXPRESSPAY_CVM_SIGNATURE), WITH_AOSA);
							}

							if (ucCvm == EXPRESSPAY_CVM_SIGNATURE)
							{
								GetMessageInfos(STD_MESS_SIGNATURE_OK, &tMsg);
								if ((bLoopMode) || (HelperQuestionYesNo (&tMsg, 30)))
								{
									Helper_DisplayMessage(STD_MESS_SIGNATURE_CORRECT, ERASE, HELPERS_MERCHANT_LINE_3);
									Helper_RefreshScreen(NOWAIT);
									CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_ONLINE_APPROVED);
								}
								else
								{
									Helper_DisplayMessage(STD_MESS_SIGNATURE_INCORRECT, ERASE, HELPERS_MERCHANT_LINE_3);
									Helper_RefreshScreen(NOWAIT);
									CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_OFFLINE_DECLINED);
								}
							}
						}
						else
						{
							// Authorisation response code do not indicates an Approved transaction
							Helper_DisplayMessage(STD_MESS_ONLINE_DECLINED, ERASE, HELPERS_MERCHANT_LINE_3);
							Helper_RefreshScreen(NOWAIT);
							CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_ONLINE_DECLINED);
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
				if(nTransactionOutcome == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
				{
					bUnableToGoOnline = TRUE;
					ret = GTL_SharedExchange_AddTag(pDataStruct, TAG_EXPRESSPAY_UNABLE_TO_GO_ONLINE, 1, &bUnableToGoOnline);
					if (ret != STATUS_SHARED_EXCHANGE_OK)
						GTL_Traces_TraceDebug("CST_ExpressPay_Transaction: Unable to add TAG_EXPRESSPAY_UNABLE_TO_GO_ONLINE in shared buffer (ret=%02x)", ret);
				}
				else // Magstripe Online or EMV Partial Online
				{
					bUnableToGoOnline = TRUE;
				}
			}

			if(nTransactionOutcome == EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION)
			{
				// Add Issuer Scripts in the data sent to the kernel
				__CST_ExpressPay_AddIssuerScripts(pDataStruct);

				// EMV Full Online transaction is performed
				nTransactionOutcome = __CST_ExpressPay_TransactionPostProcessing(pDataStruct);
				goto Restart;
			}
			else // Magstripe Online or EMV Partial Online
			{
				if(bUnableToGoOnline)
				{
					// If an online only terminal is unable to go online, transaction is declined.
					// If SDA was requested but not performed because it is an EMV Partial Online transaction, transaction is declined.
					if(__CST_ExpressPay_IsOnlineOnly(pDataStruct) ||
					   (nTransactionOutcome == EXPRESSPAY_STATUS_MAGSTRIPE_ONLINE_AUTHORISATION) ||
					   (nTransactionOutcome == EXPRESSPAY_STATUS_EMV_PARTIAL_ONLINE_AUTHORISATION && __CST_ExpressPay_ActionCodeDefaultCheck()))
					{
						Helper_DisplayMessage(STD_MESS_OFFLINE_DECLINED, ERASE, HELPERS_MERCHANT_LINE_3);
						Helper_RefreshScreen(NOWAIT);
						CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_OFFLINE_DECLINED);
					}
					else
					{
						// Default Action Code does not match, transaction is approved offline
						if (ucCvm == EXPRESSPAY_CVM_SIGNATURE)
						{
							Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L1, ERASE, HELPERS_MERCHANT_LINE_3);
							Helper_DisplayMessage(STD_MESS_SIGNATURE_CHECK_L2, NO_ERASE, HELPERS_MERCHANT_LINE_4);
							Helper_RefreshScreen(NOWAIT);
							CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_SIGNATURE_REQUIRED);
						}
						else
						{
							Helper_DisplayMessage(STD_MESS_OFFLINE_APPROVED, ERASE, HELPERS_MERCHANT_LINE_3);
							Helper_RefreshScreen(NOWAIT);
							CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_OFFLINE_APPROVED);
						}

						// Get all the kernel data to print the receipt
						CST_Term_GetAllData(pDataStruct);

						if (!bLoopMode)
						{
							GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);

							if ((CST_DumpData_GetOutputId() != CST_OUTPUT_NONE) && ((ucCvm == EXPRESSPAY_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30))))
								CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_AMEX, APPROVED_TICKED, (ucCvm == EXPRESSPAY_CVM_SIGNATURE), WITH_AOSA);
						}

						if (ucCvm == EXPRESSPAY_CVM_SIGNATURE)
						{
							GetMessageInfos(STD_MESS_SIGNATURE_OK, &tMsg);
							if (HelperQuestionYesNo (&tMsg, 30))
							{
								Helper_DisplayMessage(STD_MESS_SIGNATURE_CORRECT, ERASE, HELPERS_MERCHANT_LINE_3);
								Helper_RefreshScreen(NOWAIT);
								CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_APPROVED);
							}
							else
							{
								Helper_DisplayMessage(STD_MESS_SIGNATURE_INCORRECT, ERASE, HELPERS_MERCHANT_LINE_3);
								Helper_RefreshScreen(NOWAIT);
								CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_OFFLINE_DECLINED);
							}
						}
					}
				}
			}
		}
		else
		{
			if (bContinueWithOnlineAuthorisation == B_NON_INIT)
				Helper_DisplayMessage(STD_MESS_PIN_CANCEL, ERASE, HELPERS_MERCHANT_LINE_3);
			else
				Helper_DisplayMessage(STD_MESS_ONLINE_PIN_ERROR, ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_RefreshScreen(NOWAIT);
			CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_OFFLINE_DECLINED);
		}
		break;

	case (SDI_STATUS_USE_OTHER_INTERFACE):
		nTransactionResult = SDI_STATUS_USE_OTHER_INTERFACE;
		break;

	default: // Error case
		Helper_DisplayMessage(STD_MESS_ERROR, ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_RefreshScreen(NOWAIT);
		CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_ERROR);
		break;
	}

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


//! \brief Perform the full online EMV transaction post processing (Issuer Authentication, Second Terminal Action Analysis...)
//! \param[in,out] pDataStruct Shared buffer that contains the transaction data.
//! \return The transaction outcome value.

static int __CST_ExpressPay_TransactionPostProcessing(T_SHARED_DATA_STRUCT * pDataStruct)
{
	int nSdiResult = SDI_STATUS_UNKNOWN;
	int nEvent;
	TLV_TREE_NODE hTlvTreeIn;
	TLV_TREE_NODE hTlvTreeOut = NULL;

	hTlvTreeIn = TlvTree_New(0);
	if (hTlvTreeIn != NULL)
	{
		CopyDataStructInTLVTree(pDataStruct, hTlvTreeIn);

		// Perform the post transaction processing
		nSdiResult = SDI_Payment_TxnPostProcessing (nSDSAAppliId, hTlvTreeIn, E_USER_EVENT);
		if(nSdiResult == SDI_STATUS_OK)
		{
			nSdiResult = SDI_STATUS_ANSWER_NOT_YET_RECEIVED;
			do
			{
				nEvent = ttestall(USER_EVENT, 1);

				if(nEvent & USER_EVENT)
				{
					nSdiResult = SDI_Payment_GetPostProcessingResult(&hTlvTreeOut);
				}
			}while( nSdiResult == SDI_STATUS_ANSWER_NOT_YET_RECEIVED );
		}

		// Clear buffer
		GTL_SharedExchange_ClearEx (pDataStruct, FALSE);

		if(hTlvTreeOut != NULL)
			CopyTlvTreeToDataStruct(hTlvTreeOut, pDataStruct);

		TlvTree_ReleaseEx (&hTlvTreeOut);
		TlvTree_ReleaseEx (&hTlvTreeIn);
	}
	else
		GTL_Traces_TraceDebug("__CST_ExpressPay_TransactionPostProcessing : TlvTree_New error");

	if(nSdiResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();

	return (nSdiResult);
}


//! \brief Check if the Default Action Codes match or not (TAG_EXPRESSPAY_INT_TAC_IAC_DEFAULT_MATCHED set to 1 by the ExpressPay kernel).
//! \return
//!		- \ref TRUE if Default Action codes match (decline the transaction).
//!		- \ref FALSE else (approve the transaction).

static int __CST_ExpressPay_ActionCodeDefaultCheck (void)
{
	T_SHARED_DATA_STRUCT * pDataRequest;
	TLV_TREE_NODE hTlvTreeIn;
	TLV_TREE_NODE hTlvTreeOut = NULL;
	int cr, nResult = FALSE;
	int nPosition;
	const unsigned char * pValue;
	unsigned long ulLength;
			
	hTlvTreeIn = TlvTree_New(0);
	
	pDataRequest = GTL_SharedExchange_InitLocal (128);

	if ((hTlvTreeIn != NULL) && (pDataRequest != NULL))
	{
		// Indicate tag to be requested
		TlvTree_AddChild(hTlvTreeIn, TAG_EXPRESSPAY_INT_TAC_IAC_DEFAULT_MATCHED, NULL, 0);
		
		cr = SDI_Payment_GetData(nSDSAAppliId, hTlvTreeIn, &hTlvTreeOut);

		if (cr != SDI_STATUS_OK)
		{
			GTL_Traces_TraceDebug("__CST_ExpressPay_ActionCodeDefaultCheck : An error occured when getting tags from the ExpressPay kernel (cr=%02x)", cr);
			
			if(cr == SDI_STATUS_DISCONNECTED)
				CST_ReconnectionProcess();

			nResult = FALSE;
			goto End;
		}

		if (hTlvTreeOut == NULL)
		{
			nResult = FALSE;
			goto End;
		}

		// Copy data in the buffer
		CopyTlvTreeToDataStruct(hTlvTreeOut, pDataRequest);

		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pDataRequest, &nPosition, TAG_EXPRESSPAY_INT_TAC_IAC_DEFAULT_MATCHED, &ulLength, &pValue) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug ("__CST_ExpressPay_ActionCodeDefaultCheck : Missing TAG_EXPRESSPAY_INT_TAC_IAC_DEFAULT_MATCHED");
			nResult = FALSE;
			goto End;
		}

		if(pValue[0])
			nResult = TRUE; // Default Action Codes match
	}
	
End:

	TlvTree_ReleaseEx (&hTlvTreeOut);
	TlvTree_ReleaseEx (&hTlvTreeIn);

	// Destroy the shared buffer if created
	if (pDataRequest != NULL)
		GTL_SharedExchange_DestroyLocal (pDataRequest);

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

static int __CST_ExpressPay_GetRemovalTimeOut (unsigned long *pRemovalTimeOut)
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


//! \brief Waits an event from CST applicaation (Online Authorization received) during XX seconds.
//! If the event is not received, ask for card removal.

static word __CST_ExpressPay_StartTimerTask (void)
{
	unsigned long ulRemovalTimeOut;	// Card removal timeout (in milliseconds)
	int nTimeout;


	g_bTimerTaskRunning = TRUE;		// Indicates the task is running
	g_TimerTask = CurrentTask();	// Get the Timer task ID and store it in a global variable

	// Start the removal timer
	gs_ulStartRemovalTimerTime = GTL_StdTimer_GetCurrent();

	// First, get the removal timeout value
	if(!__CST_ExpressPay_GetRemovalTimeOut (&ulRemovalTimeOut))
		ulRemovalTimeOut = 0; // Perform a Partial Online transaction
	
	while (!g_bTimer_task_to_be_killed) // While the task is not to be killed by the CST application
	{
		if (g_bTimerExpired)	// Timeout expired, task is waiting to be killed
		{
			g_bTimerTaskRunning = FALSE;	// Indicate to the CST application that the task is waiting to be killed
			ttestall (0,0);					// Wait to be killed
		}

		// Test if removal timer expired
		nTimeout = GTL_StdTimer_GetRemaining(gs_ulStartRemovalTimerTime, ulRemovalTimeOut/10);
		if (nTimeout == 0)
		{
			// Timer expires before a response is received from the Acquirer
			g_bTimerExpired = TRUE;
			// Prompt for the removal of the card
			CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_REMOVE_CARD);

			Helper_DisplayMessage(STD_MESS_ONLINE_REQUEST, ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_RefreshScreen(NOWAIT);
			CST_DisplayScreen(SDSA_EXPRESSPAY_SCREEN_ONLINE_PROCESSING);
		}
		
		if(!g_bTimerExpired)
			ttestall (USER_EVENT, 1);	// User event (from main task), it indicates the task is going to be killed (because g_bTimer_task_to_be_killed has been set to TRUE by the cst application)

	} // End While

	// The task is stopped by the main application (Online Response received)
	g_bTimerTaskRunning = FALSE; // Update global variable

	// Send the event to the main task
	if (SignalEvent (g_wCurrentTask, (tEvent)E_USER_EVENT) != cOK)
		GTL_Traces_TraceDebug ("Timer task: Error when setting the event\n");

	ttestall (0,0); // Wait to be killed
	return TRUE;
}


//! \brief Initialise removal timer global variables
 
static void __CST_ExpressPay_InitTimerVariables (void)
{
	g_wCurrentTask = 0xFF;				// Init the custom application task number
	g_TimerTask = 0xFF;					// Init the scanning task number
	g_tsTimer_task_handle = NULL;		// Init the scanning task handle
	g_bTimer_task_to_be_killed = FALSE; // Task has not to be killed
	g_bTimerTaskRunning = FALSE;		// Task is not running
	g_bTimerExpired = FALSE;			// Removal timer has not expired
}


//! \brief Launch the removal timer task.
//! \return	OK if task correctly launched, KO else.

static int __CST_ExpressPay_LaunchRemovalTimerTask (void)
{
	// Init global variables
	__CST_ExpressPay_InitTimerVariables();

	// Get the main task id
	g_wCurrentTask = CurrentTask();

	// Launch the timer task
	g_tsTimer_task_handle = fork (&__CST_ExpressPay_StartTimerTask, NULL, 0);
	
	// The task cannot be created
	if (g_tsTimer_task_handle == NULL)
		return KO;

	return OK;
}


//! \brief Kill the removal timer task.

static void __CST_ExpressPay_KillTimerTask (void)
{
	if (g_tsTimer_task_handle != NULL) // If the task is launched
	{
		g_bTimer_task_to_be_killed = TRUE; // To Stop the task (if not already waiting to be killed because of timeout expired)

		// Send an event to make the task ready to be killed
		if (SignalEvent (g_TimerTask, (tEvent)E_USER_EVENT) != cOK)
			GTL_Traces_TraceDebug ("Main task: Error when setting the event\n");

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


//! \brief Add Issuer Scripts received from the authorization in the transaction data sent to the Expresspay kernel.
//! \param[in/out] pTransactionData Transaction data.

static void __CST_ExpressPay_AddIssuerScripts (T_SHARED_DATA_STRUCT *pTransactionData)
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
						GTL_Traces_TraceDebug("__CST_ExpressPay_AddIssuerScripts : Unable to add TAG_EMV_ISSUER_SCRIPT_TEMPLATE_1 (nResult = %02x)", nResult);
				}
				if(ReadTag == TAG_EMV_ISSUER_SCRIPT_TEMPLATE_2)
				{
					nResult = GTL_SharedExchange_AddTag(pTmpScripts72, ReadTag, ReadLength, ReadValue);
					if (nResult != STATUS_SHARED_EXCHANGE_OK)
						GTL_Traces_TraceDebug("__CST_ExpressPay_AddIssuerScripts : Unable to add TAG_EMV_ISSUER_SCRIPT_TEMPLATE_2 (nResult = %02x)", nResult);
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
				GTL_Traces_TraceDebug("__CST_ExpressPay_AddIssuerScripts : Unable to add TAG_EXPRESSPAY_ISSUER_SCRIPT_71_LIST (nResult = %02x)", nResult);
		}

		if (pTmpScripts72->ulDataLength)
		{
			nResult = GTL_SharedExchange_AddTag(pTransactionData, TAG_EXPRESSPAY_ISSUER_SCRIPT_72_LIST, pTmpScripts72->ulDataLength, pTmpScripts72->nPtrData);
			if (nResult != STATUS_SHARED_EXCHANGE_OK)
				GTL_Traces_TraceDebug("__CST_ExpressPay_AddIssuerScripts : Unable to add TAG_EXPRESSPAY_ISSUER_SCRIPT_72_LIST (nResult = %02x)", nResult);
		}
	}
	else
		GTL_Traces_TraceDebug("__CST_ExpressPay_AddIssuerScripts : GTL_SharedExchange_InitLocal error");

	// Destroy the local buffers
	if (pTmpScripts71)
		GTL_SharedExchange_DestroyLocal(pTmpScripts71);
	if (pTmpScripts72)
		GTL_SharedExchange_DestroyLocal(pTmpScripts72);
}


//! \brief Check if the terminal is online only.

static int __CST_ExpressPay_IsOnlineOnly (T_SHARED_DATA_STRUCT * pDataStruct)
{
	const unsigned char * pTerminalType;
	int nPosition;
	unsigned long ulLength;
	int nResult = FALSE;

	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_TERMINAL_TYPE, &ulLength, &pTerminalType) == STATUS_SHARED_EXCHANGE_OK)
	{
		if((pTerminalType[0] == CST_TERM_TYPE_FINANCIAL_ATT_ONLINE_ONLY) ||
		   (pTerminalType[0] == CST_TERM_TYPE_FINANCIAL_UNATT_ONLINE_ONLY) ||
		   (pTerminalType[0] == CST_TERM_TYPE_MERCHANT_ATT_ONLINE_ONLY) ||
		   (pTerminalType[0] == CST_TERM_TYPE_MERCHANT_UNATT_ONLINE_ONLY) ||
		   (pTerminalType[0] == CST_TERM_TYPE_CARDHOLDER_UNATT_ONLINE_ONLY))
		{
			nResult = TRUE;
		}
	}

	return (nResult);
}
