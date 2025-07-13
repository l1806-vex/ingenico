/**
 * \author	Ingenico
 * \author	Copyright (c) 2012 Ingenico, rue claude Chappe,\n
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
//// Static function definition /////////////////////////////////

static int __ClessSample_PerformClessTransaction (void);


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Prepare the static data to be used for the transaction (amount auth, amount other, currency code, currency exponent, currency label, Interface serial number).
//! \param[in] bUseParameterFileForTransactionData \a TRUE if the parameter file data shall be used to perform the transaction, \a ALSE if standard transaction has to be performed.
//! \return
//!	- \a TRUE if correctly performed.
//!	- \a FALSE if an error occurred.

static int __ClessSample_ExplicitSelection_PrepareStaticTransactionData (const int bUseParameterFileForTransactionData)
{
	int nResult = TRUE;
	S_MONEY money;
	unsigned long ulAmountAuth = 0;
	unsigned long ulAmountOther = 0;
	unsigned char ucTransactionCurrencyCode[2];
	unsigned char ucTransactionCurrencyExponent;
	char * pCurrencyLabel;
	char ucCurrencyLabel[4];
	int nTransactionType;
	unsigned char ucTransactionType;
	unsigned char ucTxnCategoryCode;
	unsigned char bIsAmountOtherPresent = SAMPLE_TAG_ABSENT;
	unsigned char bIsCurrencyCodePresent = SAMPLE_TAG_ABSENT;
	unsigned char bIsCurrencyExpPresent = SAMPLE_TAG_ABSENT;
	unsigned char bIsTransacTypePresent = SAMPLE_TAG_ABSENT;
	unsigned char bIsSerialNumberPresent = SAMPLE_TAG_ABSENT;
	unsigned char bIsAmountAuthPresent = SAMPLE_TAG_ABSENT;
	unsigned char bIsTxnCategoryCodePresent = SAMPLE_TAG_ABSENT;
	unsigned char bUseCurrentSerialNumber;
	unsigned char * pReadInfo = NULL;
	

	// Determine the transaction data either from file or from operator
	if (bUseParameterFileForTransactionData)
	{
		// Transaction is done using the data provided in the parameter file only (no amount entry, etc).
		if(ClessSample_Parameters_GetTagInParameterFile(TAG_EMV_AMOUNT_AUTH_NUM, &bIsAmountAuthPresent, &pReadInfo))
		{
			if(bIsAmountAuthPresent == SAMPLE_TAG_PRESENT)
				GTL_Convert_DcbNumberToUl (pReadInfo, &ulAmountAuth, 6);
		}
		else
		{
			nResult = FALSE;
			goto End;
		}
		if(ClessSample_Parameters_GetTagInParameterFile(TAG_EMV_AMOUNT_OTHER_NUM, &bIsAmountOtherPresent, &pReadInfo))
		{
			if(bIsAmountOtherPresent == SAMPLE_TAG_PRESENT)
				GTL_Convert_DcbNumberToUl (pReadInfo, &ulAmountOther, 6);
		}
		else
		{
			nResult = FALSE;
			goto End;
		}
		if(ClessSample_Parameters_GetTagInParameterFile(TAG_EMV_TRANSACTION_CURRENCY_CODE, &bIsCurrencyCodePresent, &pReadInfo))
		{
			if(bIsCurrencyCodePresent == SAMPLE_TAG_PRESENT)
			{
				memcpy (ucTransactionCurrencyCode, pReadInfo, 2);

				// Get the currency label from the parameters. If not found, indicate an invalid parameter as the currency code provided is unknown from the application
				if(!ClessSample_Parameters_GetCurrencyFromParameters(ucTransactionCurrencyCode, &pCurrencyLabel))
				{
					GTL_Traces_TraceDebug ("Currency code provided is unknown from the application (%02x %02x)", ucTransactionCurrencyCode[0], ucTransactionCurrencyCode[1]);
					nResult = FALSE;
					goto End;
				}

				memset(ucCurrencyLabel,0,sizeof(ucCurrencyLabel));
				memcpy(ucCurrencyLabel, pCurrencyLabel, 3);
				pCurrencyLabel = ucCurrencyLabel;
			}
		}
		else
		{
			nResult = FALSE;
			goto End;
		}
		if(ClessSample_Parameters_GetTagInParameterFile(TAG_EMV_TRANSACTION_CURRENCY_EXPONENT, &bIsCurrencyExpPresent, &pReadInfo))
		{
			if(bIsCurrencyExpPresent == SAMPLE_TAG_PRESENT)
				ucTransactionCurrencyExponent = pReadInfo[0];
		}
		else
		{
			nResult = FALSE;
			goto End;
		}
		if(ClessSample_Parameters_GetTagInParameterFile(TAG_EMV_TRANSACTION_TYPE, &bIsTransacTypePresent, &pReadInfo))
		{
			if(bIsTransacTypePresent == SAMPLE_TAG_PRESENT)	
				ucTransactionType = pReadInfo[0];
		}
		else
		{
			nResult = FALSE;
			goto End;
		}
		if(ClessSample_Parameters_GetTagInParameterFile(TAG_EMV_IFD_SERIAL_NUMBER, &bIsSerialNumberPresent, &pReadInfo))
		{
			// If the TAG_EMV_IFD_SERIAL_NUMBER tag is present in the parameter file, serial number of the device must be used for the transaction
			if(bIsSerialNumberPresent == SAMPLE_TAG_PRESENT)
				bUseCurrentSerialNumber = TRUE;
			else
				bUseCurrentSerialNumber = FALSE;		
		}
		else
		{
			nResult = FALSE;
			goto End;
		}
		if(ClessSample_Parameters_GetTagInParameterFile(TAG_PAYPASS_TRANSACTION_CATEGORY_CODE, &bIsTxnCategoryCodePresent, &pReadInfo))
		{
			// If the TAG_PAYPASS_TRANSACTION_CATEGORY_CODE tag is present in the parameter file, use the provided value
			if(bIsTxnCategoryCodePresent == SAMPLE_TAG_PRESENT)
				ucTxnCategoryCode = pReadInfo[0];
		}
		else
		{
			nResult = FALSE;
			goto End;
		}
	}
	else
	{
		// Check if unattended mode is enabled
		if (ClessSample_Unattended_IsUnattendedMechanism())
		{
			// If unatteded, the transaction amount is already available, and no entry is necessary
			nTransactionType = ClessSample_Unattended_GetTransactionType();
			ucTransactionType = (unsigned char)nTransactionType;
		}
		else
		{
			// Transaction is started using the normal way (amount entry, etc).
			if (ClessSample_Menu_IsEnableInputTransactionType()) // Is transactionType must be inputed
			{
				// Input nTransactionType
				ClessSample_Menu_TransactionTypeMenuDisplay (&nTransactionType);
				ucTransactionType = (unsigned char)nTransactionType;
			}
			else
			{
				ucTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_DEBIT;
			}
		}

		// Check the provided transaction type is correct
		if ((ucTransactionType != CLESS_SAMPLE_TRANSACTION_TYPE_DEBIT) && (ucTransactionType != CLESS_SAMPLE_TRANSACTION_TYPE_REFUND) && (ucTransactionType != CLESS_SAMPLE_TRANSACTION_TYPE_CASH) &&
			(ucTransactionType != CLESS_SAMPLE_TRANSACTION_TYPE_PURSH_WITH_CASHBACK) && (ucTransactionType != CLESS_SAMPLE_TRANSACTION_TYPE_MANUAL_CASH) && (ucTransactionType != CLESS_SAMPLE_TRANSACTION_TYPE_CASH_DEPOSIT))
		{
			GTL_Traces_TraceDebug("__ClessSample_ExplicitSelection_PrepareStaticTransactionData : Transaction type is unknown (value = %02X)", ucTransactionType);
			nResult = FALSE;
			goto End;
		}

		// Init the transaction type
		bIsTransacTypePresent = SAMPLE_TAG_PRESENT;

		// Get the currency configured in the manager
		memset (&money, 0x00, sizeof(S_MONEY));
		PSQ_Est_money (&money);

		// Convert the transaction currency code from the manager to 2 byte numeric
		bIsCurrencyCodePresent = SAMPLE_TAG_PRESENT;
		memset (ucTransactionCurrencyCode, 0x00, sizeof(ucTransactionCurrencyCode));
		ucTransactionCurrencyCode[0] = (unsigned char)(money.code[0] - '0');
		ucTransactionCurrencyCode[1] = (unsigned char)(((money.code[1] - '0') << 4) | (money.code[2] - '0'));

		// Get the transaction currency exponent
		bIsCurrencyExpPresent = SAMPLE_TAG_PRESENT;
		ucTransactionCurrencyExponent = money.posdec;

		// Get the currency label
		pCurrencyLabel = (char*)money.nom;

		// Check if unattended mode is enabled
		if (ClessSample_Unattended_IsUnattendedMechanism())
		{
			// If unatteded, the transaction amount authorized is already available, and no entry is necessary
			ulAmountAuth = ClessSample_Unattended_GetAmountAuth();
		}
		else
		{
			// Whatever the transaction, amount is entered
			if (!ClessSample_Common_AmountEntry (FALSE, money.nom, &ulAmountAuth))
			{
				GTL_Traces_TraceDebug("__ClessSample_ExplicitSelection_PrepareStaticTransactionData : Transaction amount entry cancelled");
				nResult = FALSE;
				goto End;
			}
		}

		bIsAmountAuthPresent = SAMPLE_TAG_PRESENT;


		// If transaction is cashback, enter amount other
		if (ucTransactionType == CLESS_SAMPLE_TRANSACTION_TYPE_PURSH_WITH_CASHBACK)
		{
			// Check if unattended mode is enabled
			if (ClessSample_Unattended_IsUnattendedMechanism())
			{
				// If unatteded, the transaction amount other is already available, and no entry is necessary
				ulAmountOther = ClessSample_Unattended_GetAmountOther();

				if (ClessSample_DumpData_DumpOpenOutputDriver())
				{
					ClessSample_DumpData ("Amount Auth = %lu", ulAmountAuth);
					ClessSample_DumpData_DumpNewLine();
					ClessSample_DumpData ("Amount Other = %lu", ulAmountOther);
					ClessSample_DumpData_DumpNewLine();
					ClessSample_DumpData_DumpCloseOutputDriver();
				}
			}
			else
			{
				if (!ClessSample_Common_AmountEntry (TRUE, money.nom, &ulAmountOther))
				{
					// Display an error message
					ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_ERROR, -1, -1);

					GTL_Traces_TraceDebug("__ClessSample_ExplicitSelection_PrepareStaticTransactionData : Transaction amount other entry cancelled");
					nResult = FALSE;
					goto End;
				}
			}

			// Indicate the amount other is present
			bIsAmountOtherPresent = SAMPLE_TAG_PRESENT;

			// Anti-bug:
			if (ulAmountOther > ulAmountAuth)
			{
				// Display an error message
				ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_ERROR, -1, -1);

				// An error occurred when preparing the static transaction data
				GTL_Traces_TraceDebug ("__ClessSample_ExplicitSelection_PrepareStaticTransactionData : An error occurred when preparing the static transaction data");
				nResult = FALSE;
				goto End;
			}
		}
		else
		{
			// Indicate the amount other is present
			ulAmountOther = 0;
			bIsAmountOtherPresent = SAMPLE_TAG_PRESENT;
		}

		// Use the current SN
		bUseCurrentSerialNumber = TRUE;

		bIsTxnCategoryCodePresent = SAMPLE_TAG_PRESENT;
		ucTxnCategoryCode = 0x52; // "R"

	}

	// Save the transaction related data for future use
	ClessSample_Fill_PrepareAndSaveClessGiveInfoTransactionStaticData (bIsAmountAuthPresent, ulAmountAuth,
																bIsAmountOtherPresent, ulAmountOther,
																bIsCurrencyCodePresent, ucTransactionCurrencyCode,
																bIsCurrencyExpPresent, &ucTransactionCurrencyExponent,
																bIsTransacTypePresent, &ucTransactionType,
																bUseCurrentSerialNumber, bIsSerialNumberPresent,
																pCurrencyLabel,
																bIsTxnCategoryCodePresent, &ucTxnCategoryCode);

End:
	return (nResult);
}



//! \brief Prepare the dynamic data to be used for the transaction (date and time).
//! \param[in] bUseParameterFileForTransactionData \a TRUE if the parameter file data shall be used to perform the transaction, \a ALSE if standard transaction has to be performed.
//! \return
//!	- \a TRUE if correctly performed.
//!	- \a FALSE if an error occurred.

static int __ClessSample_ExplicitSelection_PrepareDynamicTransactionData (const int bUseParameterFileForTransactionData)
{
	int nResult = TRUE;
	unsigned char bIsDatePresent = SAMPLE_TAG_ABSENT;
	unsigned char bIsTimePresent = SAMPLE_TAG_ABSENT;
	unsigned char bUseCurrentDate = FALSE;
	unsigned char bUseCurrentTime = FALSE;
	unsigned char * pReadInfo = NULL;


	// Determine the transaction data either from file or from operator
	if (bUseParameterFileForTransactionData)
	{
		// Transaction is done using the data provided in the parameter file only (no amount entry, etc).	
		if(ClessSample_Parameters_GetTagInParameterFile(TAG_EMV_TRANSACTION_DATE, &bIsDatePresent, &pReadInfo))
		{
			// If the TAG_EMV_TRANSACTION_DATE tag is present in the parameter file, the date of the device must be used for the transaction
			if(bIsDatePresent == SAMPLE_TAG_PRESENT)
				bUseCurrentDate = TRUE;
		}
		else
		{
			nResult = FALSE;
			goto End;
		}

		if(ClessSample_Parameters_GetTagInParameterFile(TAG_EMV_TRANSACTION_TIME, &bIsTimePresent, &pReadInfo))
		{
			// If the TAG_EMV_TRANSACTION_TIME tag is present in the parameter file, the time of the device must be used for the transaction
			if(bIsTimePresent == SAMPLE_TAG_PRESENT)
				bUseCurrentTime = TRUE;
		}
		else
		{
			nResult = FALSE;
			goto End;
		}
	}
	else
	{
		// Transaction is started using the normal way (get date and time dynamically, etc).
		bUseCurrentDate = TRUE;
		bUseCurrentTime = TRUE;
	}

	ClessSample_Fill_PrepareAndSaveClessGiveInfoTransactionDynamicData (bUseCurrentDate, bIsDatePresent, bUseCurrentTime, bIsTimePresent);

End:
	return (nResult);
}



//! \brief Function called for to perform explicit transaction (card detection and application selection).
//! \param[in] bUseParameterFileForTransactionData \a TRUE if transaction is started using the parameter file, \a FALSE if transaction is started with operator assistance (transaction type choice, amount entry, etc).

void ClessSample_ExplicitSelection_Process (const int bUseParameterFileForTransactionData)
{
	// If iUP250, start graphic mode
	if (ClessSample_Unattended_IsUnattendedMechanism())
		if (ClessSample_Unattended_IsUnattendedTerminalWithDisplayWithUCMC ())
			iLIBUCM_Display_Graphic_Start(UCMC_DISPLAY);

	// Set the transaction mode to "explicit"
	ClessSample_Common_SetTransactionMode (CLESS_SAMPLE_TRANSACTION_MODE_EXPLICIT);

	// First, prepare the transaction data
	if (!__ClessSample_ExplicitSelection_PrepareStaticTransactionData (bUseParameterFileForTransactionData))
	{
		// An error occurred when preparing the static transaction data
		GTL_Traces_TraceDebug ("ClessSample_ExplicitSelection_Process : An error occurred when preparing the static transaction data");
		goto End;
	}

	// First, prepare the dynamic transaction data
	if (!__ClessSample_ExplicitSelection_PrepareDynamicTransactionData (bUseParameterFileForTransactionData))
	{
		// An error occurred when preparing the transaction data
		GTL_Traces_TraceDebug ("ClessSample_ExplicitSelection_Process : An error occurred when preparing the dynamic transaction data");
		goto End;
	}

	// Perform the transaction
	if (!__ClessSample_PerformClessTransaction ())
	{
		// An error occurred during the transaction
		GTL_Traces_TraceDebug ("ClessSample_ExplicitSelection_Process : An error occurred during the transaction");
		goto End;
	}

End:

	// If iUP250, stop graphic mode
	if (ClessSample_Unattended_IsUnattendedMechanism())
		if (ClessSample_Unattended_IsUnattendedTerminalWithDisplayWithUCMC ())
			iLIBUCM_Display_Graphic_Stop(UCMC_DISPLAY);

	ClessSample_Common_SetTransactionMode (CLESS_SAMPLE_TRANSACTION_MODE_UNKNOWN);
	return;
}



//! \brief Perform a contactless transaction in explicit mode, with transaction amount provided.
//! \return
//!	- \a TRUE if correctly performed.
//!	- \a FALSE if an error occurred.

static int __ClessSample_PerformClessTransaction (void)
{
	int nResult = TRUE;
	TLV_TREE_NODE hTransactionTlvTree = NULL;
	const T_PAYMENT_DATA_STRUCT * pTransactionData;
	T_SHARED_DATA_STRUCT * pSharedData = NULL;
	unsigned char ucBuffer[4];
	int bEnd, bCancel, nEvent;
	int nKernelToUse;
	///unsigned char ucKernelUsed[2];
	int cr_temp;
	int nPosition;
	unsigned long ulReadLength;
	const unsigned char * pValue;
	unsigned char bLoopMode = FALSE;


	// Loop mode information
	bLoopMode = ClessSample_Menu_IsTransactionLoopOn();

	do{ // bLoopMode

		bCancel = FALSE;

		// Set the transaction kernel to "unknown"
		ClessSample_Customisation_SetUsedPaymentScheme (CLESS_SAMPLE_CUST_UNKNOWN);

		// Indicate no tap is in progress
		ClessSample_Customisation_SetDoubleTapInProgress(FALSE);

		// Set the current application language with the manager language
		///ClessSample_UserInterface_SetMerchantLanguage();

		//// Prepare data for card detection and application selection

		// Create the shared buffer (for transaction result)
		pSharedData = GTL_SharedExchange_InitShared(10240);

		if (pSharedData == NULL)
		{
			GTL_Traces_TraceDebug ("__ClessSample_PerformClessTransaction : pSharedData is NULL");
			nResult = FALSE;
			goto End;
		}

		//// Prepare data and structure for kernel processing after application selection
		// Input parameters
		if (!ClessSample_Fill_InitSharedBufferWithKernels (&g_pKernelSharedBuffer))
		{
			GTL_Traces_TraceDebug("__ClessSample_PerformClessTransaction : ClessSample_Fill_InitSharedBufferWithKernels failed");
			nResult = FALSE;
			goto End;
		}


		// Create the TLV Tree to provide all the application selection parameters (including transaction amount)
		hTransactionTlvTree = TlvTree_New(0);

		if (hTransactionTlvTree != NULL)
		{
			// Fill the hTransactionTlvTree with the correct parameters
			if (!ClessSample_Fill_GetApplicationSelectionParameters (&hTransactionTlvTree, &pTreeCurrentParam, TRUE))
			{
				GTL_Traces_TraceDebug ("__ClessSample_PerformClessTransaction : ClessSample_Fill_GetApplicationSelectionParameters failed");
				nResult = FALSE;
				goto End;
			}

			// Get the transaction data
			pTransactionData = ClessSample_Fill_GetTransactionDataStructure();

			if(pTransactionData->bIsAmountAuthPresent == SAMPLE_TAG_PRESENT)
			{	
				// Add the transaction amount
				GTL_Convert_UlToBinNumber(pTransactionData->ulTransactionAmount, ucBuffer, 4);
				TlvTree_AddChild(hTransactionTlvTree, TAG_EMV_AMOUNT_AUTH_BIN, ucBuffer, 4);
			}

			// Call DLL to load data
			nResult = Cless_ExplicitSelection_LoadData (hTransactionTlvTree);

			if (nResult != CLESS_STATUS_OK)
			{
				GTL_Traces_TraceDebug("__ClessSample_PerformClessTransaction : Cless_ExplicitSelection_LoadData failed (nResult=%02x)", nResult);
				nResult = FALSE;
				goto End;
			}


			// Set the customisation function to be called for GUI customisation
			Cless_ExplicitSelection_Custom_RegistrationForGui (&ClessSample_Customisation_Generic_SelectionGui);

			// Set the customisation function to be called for application selection customisation
			Cless_ExplicitSelection_Custom_RegistrationForApplicationSelection(&ClessSample_Customisation_CustAsProc, NULL);

			// Perform the transaction pre processing
			nResult = Cless_ExplicitSelection_EntryPoint_TransactionPreProcessing ();
			if (nResult != CLESS_STATUS_OK)
			{
				GTL_Traces_TraceDebug("__ClessSample_PerformClessTransaction : Cless_ExplicitSelection_EntryPoint_TransactionPreProcessing failed (nResult=%02x)", nResult);
				nResult = FALSE;
				goto End;
			}

			if (ClessSample_Unattended_IsUnattendedMechanism())
				ClessSample_Unattended_LaunchCancelTask();

			// Launch task that scans the peripheral to be checks for cancel (keyboard, chip, swipe)
			ClessSample_Scan_LaunchScanningTask (SCAN_CANCEL_KEYBOARD);
			g_ScanningTask = GiveNoTask (g_tsScanning_task_handle);

			// Waiting task start before to call do_transaction
			ttestall (USER_EVENT_START, 2); // Wait scan task start

			do // While transaction not completed
			{
				// Set the transaction kernel to "unknown"
				ClessSample_Customisation_SetUsedPaymentScheme (CLESS_SAMPLE_CUST_UNKNOWN);

				// Clear the pSharedData structure
				GTL_SharedExchange_ClearEx (pSharedData, FALSE);

				// Launch the card detection
				nResult = Cless_ExplicitSelection_GlobalCardDetection();

				if (nResult != CLESS_STATUS_OK)
				{
					GTL_Traces_TraceDebug("__ClessSample_PerformClessTransaction : Cless_ExplicitSelection_GlobalCardDetection failed (nResult=%02x)", nResult);
					nResult = FALSE;
					goto End;
				}

				// Wait contactless event (or cancel from terminal application)
				bEnd = FALSE;
				bCancel = FALSE;

				do
				{
					// Wait the event
					nEvent = ttestall (USER_EVENT_CANCEL | CLESS, 0);

					if (nEvent == USER_EVENT_CANCEL)
					{
						if (Cless_ExplicitSelection_GlobalCardDetectionCancel() == CLESS_STATUS_OK)
						{
							bCancel = TRUE;
						}
					}
					else
					{
						bEnd = TRUE;
					}
				} while(!bEnd);

				// Check if card detection has been cancelled
				if (bCancel)
				{
					///ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_CANCELLED, -1, -1);

					GTL_Traces_TraceDebug ("__ClessSample_PerformClessTransaction : Card detection has been cancelled");
					nResult = FALSE;
					goto End;
				}

				if (nEvent != CLESS)
				{
					GTL_Traces_TraceDebug ("__ClessSample_PerformClessTransaction : Unknown event (nEvent=%02x)", nEvent);
					nResult = FALSE;
					goto End;
				}

				// Get the card detection result
				nResult = Cless_Generic_CardDetectionGetResults (pSharedData, TRUE);

				nPosition = SHARED_EXCHANGE_POSITION_NULL;

				cr_temp = GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_GENERIC_DETECTION_RESULT, &ulReadLength, &pValue);

				if (cr_temp != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug ("__ClessSample_PerformClessTransaction : TAG_GENERIC_DETECTION_RESULT not found (cr_temp = %02x)\n", cr_temp);
					nResult = FALSE;
					goto End;
				}

				if (pValue[0] == DETECT_RESULT_GLOBAL_TO)
				{
					nResult = FALSE;
					goto End;
				}

				if (pValue[0] != DETECT_RESULT_OK)
				{
					GTL_Traces_TraceDebug ("__ClessSample_PerformClessTransaction : TAG_GENERIC_DETECTION_RESULT = %02x\n", pValue[0]);
					nResult = FALSE;
					goto End;
				}

				if (nResult != CLESS_STATUS_OK)
				{
					GTL_Traces_TraceDebug("__ClessSample_PerformClessTransaction : Cless_Generic_CardDetectionGetResults failed (nResult=%02x)", nResult);
					nResult = FALSE;
					goto End;
				}

				do
				{
					// Set the transaction kernel to "unknown"
					ClessSample_Customisation_SetUsedPaymentScheme (CLESS_SAMPLE_CUST_UNKNOWN);

					// A card has been detected, perform the application selection
					nResult = Cless_ExplicitSelection_Selection_ApplicationSelectionProcess (pSharedData);

					if (nResult != CLESS_STATUS_OK)
					{
						nResult = ClessSample_Customisation_AnalyseApplicationSelectionResult(nResult);
						goto End_While;
					}

					// First clear the buffer to be used with the contactless kernel
					GTL_SharedExchange_ClearEx (g_pKernelSharedBuffer, FALSE);

					//Add AID related data in the shared buffer
					if (!ClessSample_Fill_AidRelatedData (g_pKernelSharedBuffer, pSharedData, &nKernelToUse))
					{
						GTL_Traces_TraceDebug("__ClessSample_PerformClessTransaction : ClessSample_Fill_AidRelatedData failed");
						nResult = FALSE;
						goto End;
					}

					// Add the generic transaction data (previously saved) in the shared buffer (date, time, amount, etc).
					if (!ClessSample_Fill_TransactionGenericData(g_pKernelSharedBuffer))
					{
						GTL_Traces_TraceDebug("__ClessSample_PerformClessTransaction : ClessSample_Fill_TransactionGenericData failed");
						nResult = FALSE;
						goto End;
					}

					if (OS_rtc_EventsOccurred (USER_EVENT_CANCEL))
					{
						// Cancel occurred
						///ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_CANCELLED, -1, -1);

						// Remove event
						ttestall (USER_EVENT_CANCEL, 1);
						GTL_Traces_TraceDebug ("__ClessSample_PerformClessTransaction : Card detection has been cancelled");
						nResult = FALSE;
						bCancel = TRUE;
						goto End;
					}

					// Call the kernel in relationship with AID
					switch (nKernelToUse)
					{
					case DEFAULT_EP_KERNEL_PAYPASS :
						nResult = ClessSample_PayPass_PerformTransaction(g_pKernelSharedBuffer);
						break;
					default:
						GTL_Traces_TraceDebug("__ClessSample_PerformClessTransaction : Unknown Kernel to use in cless_debit_aid() : %x", nKernelToUse);
						break;
					}					
				}while(nResult == CLESS_CR_MANAGER_REMOVE_AID);

End_While:
				if (nResult == CLESS_CR_MANAGER_RESTART_DOUBLE_TAP)
					Cless_ExplicitSelection_DetectionPrepareForRestart (TRUE);
				if ((nResult == CLESS_CR_MANAGER_RESTART) || (nResult == CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY))
					Cless_ExplicitSelection_DetectionPrepareForRestart (FALSE);

			} while ((nResult == CLESS_CR_MANAGER_RESTART_DOUBLE_TAP) || (nResult == CLESS_CR_MANAGER_RESTART) || (nResult == CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY));


		}
		else
		{
			GTL_Traces_TraceDebug ("ClessSample_ExplicitSelection_Process : hTransactionTlvTree is NULL");
			nResult = FALSE;
			goto End;
		}

End:

		if (ClessSample_Unattended_IsUnattendedMechanism())
			ClessSample_Unattended_KillCancelTask();

		// Kill the scanning task
		ClessSample_Scan_KillScanningTask();

		// Add the transaction data log (PayPass specific)
		if (((ClessSample_Customisation_GetUsedPaymentScheme() == CLESS_SAMPLE_CUST_PAYPASS) || ((ClessSample_Customisation_GetUsedPaymentScheme() == CLESS_SAMPLE_CUST_UNKNOWN)))&& (!bLoopMode))
			ClessSample_PayPass_DumpTransationDataLog ();


		// Release the TLV Tree if allocated
		if (hTransactionTlvTree != NULL)
		{
			TlvTree_Release(hTransactionTlvTree);
			hTransactionTlvTree = NULL;
		}

		// Release shared buffer if allocated
		if (pSharedData != NULL)
			GTL_SharedExchange_DestroyShare(pSharedData);

		// Delete the event (if exist)
		ttestall (USER_EVENT_CANCEL, 1);

		if (Cless_ExplicitSelection_ClearGlobalData() != CLESS_STATUS_OK)
			GTL_Traces_TraceDebug ("ClessSample_ExplicitSelection_Process : Cless_ExplicitSelection_ClearGlobalData failed");

	}while (bLoopMode && (!bCancel));


	return (nResult);
}
