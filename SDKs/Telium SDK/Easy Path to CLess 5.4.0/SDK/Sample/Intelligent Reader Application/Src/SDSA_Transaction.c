/**
 * \file	SDSA_Transaction.c
 * \brief 	Perform a transaction in explicit selection (without interaction with the Manager).
 *
 * \author	Ingenico
 * \author	Copyright (c) 2010 Ingenico, rue claude Chappe,\n
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

#include "SDSA_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define LENGTH_OF_TRANSACTION_AMOUNT_AUTH_NUM			6
#define LENGTH_OF_TRANSACTION_AMOUNT_OTHER_NUM			6
#define LENGTH_OF_TRANSACTION_TYPE						1
#define LENGTH_OF_TRANSACTION_DATE						3
#define LENGTH_OF_TRANSACTION_TIME						3
#define LENGTH_OF_TRANSACTION_CURRENCY_CODE				2
#define LENGTH_OF_IFD_SERIAL_NUMBER						8
#define LENGTH_OF_TRANSACTION_SEQUENCE_COUNTER			4
#define LENGTH_OF_LAST_TRANSACTION_PAN					10
#define LENGTH_OF_CASHBACK								1
#define LENGTH_OF_LIST_OF_OUTPUT_TAGS					256


/////////////////////////////////////////////////////////////////
//// Static function definition /////////////////////////////////

static int __SDSA_Transaction_ExtractAndStoreData (TLV_TREE_NODE hInputTlvTree);
static int __SDSA_PerformClessTransaction (TLV_TREE_NODE hOutputTlvTree);
static int __SDSA_Transaction_GetCurrencyFromParameters(unsigned char *pCurrencyCode, char **pCurrencyLabel,unsigned char *pCurrencyExponent);
static int __SDSA_Transaction_CheckPreProcessingResults(void);


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

static word gs_ProcessingTask;


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Function called to perform explicit transaction (card detection and application selection).
//! \param[in] hInputTlvTree Contains the input data to perform the transaction.
//! \param[out] pOutputTlvTree Output TLV Tree containing the transaction result.
//! \return
//!	- \ref 
//!	- \ref SDI_STATUS_NO_PARAMETER if there is no loaded parameter, so transaction cannot be performed.
//!	- \ref SDI_STATUS_MISSING_DATA if there is a missing mandatory parameter.
//!	- \ref SDI_STATUS_INVALID_DATA if the provided data in the input parameter is not correct.
//! - Any other kernel specific return

int SDSA_DoTransaction (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult;
	unsigned long tMandatoryTags[] = {TAG_EMV_AMOUNT_AUTH_NUM, TAG_EMV_AMOUNT_OTHER_NUM, TAG_EMV_TRANSACTION_TYPE, TAG_EMV_TRANSACTION_CURRENCY_CODE, TAG_EMV_TRANSACTION_SEQUENCE_COUNTER};


	nResult = SDI_STATUS_UNKNOWN;

	// Save the current task identifier
	gs_ProcessingTask = CurrentTask();

	// Update the transaction status
	SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_NOT_STARTED);

	if(pTreeCurrentParam == NULL)
	{
		nResult = SDI_STATUS_NO_PARAMETER;
		goto End;
	}

	// Check mandatory data presence
	if (!SDSA_Common_CheckMandatoryTagsPresenceTlvTree (hInputTlvTree, tMandatoryTags, NUMBER_OF_ITEMS (tMandatoryTags)))
	{
		nResult = SDI_STATUS_MISSING_DATA;
		goto End;
	}


	// Initialization of the shared buffer exchanged with the contactless kernels
	if (!SDSA_Fill_InitSharedBufferWithKernels (&g_pKernelSharedBuffer))
	{
		// An error occured when preparing the data for transaction
		GTL_Traces_TraceDebug("SDSA_ExplicitSelection_Process : SDSA_Fill_InitSharedBufferWithKernels failed");
		nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
		goto End;
	}


	// Extract and store the transaction data (amount, date, ...)
	if (!__SDSA_Transaction_ExtractAndStoreData (hInputTlvTree))
	{
		// An error occured when extracting data from the input TLV-Tree
		GTL_Traces_TraceDebug ("SDSA_DoTransaction : An error occured when extracting data from the input TLV-Tree");
		nResult = SDI_STATUS_INVALID_DATA;
		goto End;
	}

	// Data extraction is OK, all is ready to perform the transaction
	nResult = __SDSA_PerformClessTransaction (hOutputTlvTree);

End:
	// Update the transaction status
	SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_NOT_STARTED);

	return (nResult);
}


//! \brief Function called to perform the transaction post processing.
//! \param[in] hInputTlvTree Contains the input data to perform the transaction.
//! \param[out] pOutputTlvTree Output TLV Tree containing the transaction result.
//! \return
//!	- \ref SDI_STATUS_UNKNOWN if the kernel identifier is not known.
//! - Any other application status.

int SDSA_PostProcessing (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult = SDI_STATUS_UNKNOWN;
	unsigned char ucUsedKernel;


	// Save the current task identifier
	gs_ProcessingTask = CurrentTask();

	// Get the idenfier of the kernel that performed the transaction
	ucUsedKernel = SDSA_Customisation_GetUsedPaymentScheme();

	// Initialization of the shared buffer exchanged with the contactless kernels
	if (!SDSA_Fill_InitSharedBufferWithKernels (&g_pKernelSharedBuffer))
	{
		// An error occured when preparing the data for transaction
		GTL_Traces_TraceDebug("SDSA_PostProcessing : SDSA_Fill_InitSharedBufferWithKernels failed");
		nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
		goto End;
	}

	// First clear the buffer to be used with the contactless kernel
	GTL_SharedExchange_ClearEx (g_pKernelSharedBuffer, FALSE);
	
	// Copy the input data in the shared buffer
	SDSA_Common_CopyTlvTreeInDataStruct(hInputTlvTree, g_pKernelSharedBuffer);

	switch (ucUsedKernel)
	{
	case SDSA_KERNEL_IDENTIFIER_PAYPASS :
		// There is no possible post processing for a PayPass transaction
		break;

	case SDSA_KERNEL_IDENTIFIER_PAYWAVE :
		nResult = SDSA_payWave_PerformPostProcessing(g_pKernelSharedBuffer, hOutputTlvTree);
		break;

	case SDSA_KERNEL_IDENTIFIER_VISAWAVE :
		// There is no possible post processing for a VisaWave transaction
		break;

	case SDSA_KERNEL_IDENTIFIER_EXPRESSPAY :
		nResult = SDSA_ExpressPay_PerformPostProcessing(g_pKernelSharedBuffer, hOutputTlvTree);
		break;

	case SDSA_KERNEL_IDENTIFIER_INTERAC :
		// There is no possible post processing for an Interac transaction
		break;

	case SDSA_KERNEL_IDENTIFIER_DISCOVER :
		// There is no possible post processing for a Discover transaction
		break;

	default:
		GTL_Traces_TraceDebug("SDSA_PostProcessing : Unknown value for kernel identifier : %c", ucUsedKernel);
		break;
	}

End:
	return (nResult);
}


//! \brief Cancels the transaction "in progress".
//! \return
//!	- \ref SDI_STATUS_OK.

int SDSA_CancelTransaction (void)
{
	int nResult;
	unsigned char ucKernelUsed;


	// Get the kernel id that performs the transaction
	ucKernelUsed = SDSA_Customisation_GetUsedPaymentScheme();
	switch (ucKernelUsed)
	{
	case (SDSA_KERNEL_IDENTIFIER_PAYPASS):
		nResult = PayPass_Cancel();
		GTL_Traces_TraceDebug ("SDSA_CancelTransaction, PayPass_Cancel result, %02x",nResult);
		break;
	case (SDSA_KERNEL_IDENTIFIER_PAYWAVE):
		nResult = payWave_Cancel();
		GTL_Traces_TraceDebug ("SDSA_CancelTransaction, payWave_Cancel result, %02x",nResult);
		break;
	case (SDSA_KERNEL_IDENTIFIER_VISAWAVE):
		nResult = VisaWave_Cancel();
		GTL_Traces_TraceDebug ("SDSA_CancelTransaction, VisaWave_Cancel result, %02x",nResult);
		break;
	case (SDSA_KERNEL_IDENTIFIER_EXPRESSPAY):
		nResult = ExpressPay3_Cancel();
		GTL_Traces_TraceDebug ("SDSA_CancelTransaction, ExpressPay3_Cancel result, %02x",nResult);
		break;
	case (SDSA_KERNEL_IDENTIFIER_INTERAC):
		nResult = Interac_Cancel();
		GTL_Traces_TraceDebug ("SDSA_CancelTransaction, Interac_Cancel result, %02x",nResult);
		break;
	case (SDSA_KERNEL_IDENTIFIER_DISCOVER):
		nResult = Interac_Cancel();
		GTL_Traces_TraceDebug ("SDSA_CancelTransaction, Discover_Cancel result, %02x",nResult);
		break;
	default:
		GTL_Traces_TraceDebug ("SDSA_CancelTransaction, unknown kernel %d",ucKernelUsed);
		break;
	}

	if (SignalEvent (gs_ProcessingTask, (tEvent)E_USER_EVENT_CANCEL) != cOK)
	{
		GTL_Traces_TraceDebug ("SDSA_Custom_CancelTransaction, SignalEvent error");
	}

	return (SDI_STATUS_OK);
}



//! \brief Get the application data.
//! \param[in] hInputTlvTree Indicates the list of tag to be requested.
//! \param[out] pOutputTlvTree Contains the requested tags.
//! \return
//!	- \ref SDI_STATUS_OK if correctly managed. All the requested and present data are provided in the output structure.
//!	- \ref SDI_STATUS_KO if an error occured.
//!	- \ref SDI_STATUS_INVALID_DATA if provided data is not correct or pOutputTlvTree is null.

int SDSA_GetPaymentData (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	T_SHARED_DATA_STRUCT * pDataRequest;
	int nResult = SDI_STATUS_OK;
	unsigned int nReadTag;
	TLV_TREE_NODE hCurrentNode;
	int cr = KERNEL_STATUS_UNKNOWN, bGetAllData = FALSE;
	unsigned char *pKernel;
	unsigned long ulKernel;


	// Initialise the kernel to use with the default value
	ulKernel = SDSA_KERNEL_IDENTIFIER_UNKNOWN;

	pDataRequest = GTL_SharedExchange_InitShared(32768);
	if (pDataRequest == NULL)
		return (SDI_STATUS_KO);

	// Get the first node
	hCurrentNode = TlvTree_GetFirstChild (hInputTlvTree);
	if(hCurrentNode == NULL)
	{
		nResult = SDI_STATUS_INVALID_DATA;
		goto End;
	}

	while (hCurrentNode != NULL)
	{
		// Get the node tag
		nReadTag = TlvTree_GetTag (hCurrentNode);
		if(nReadTag == TAG_SDSA_KERNEL_IDENTIFIER)
		{
			// Get the identifier of the kernel that will be called
			pKernel = TlvTree_GetData(hCurrentNode);
			GTL_Convert_BinNumberToUl (pKernel, &ulKernel, 2);
		}
		else if(nReadTag == TAG_SDSA_GET_ALL_DATA)
		{
			// All the tag are requested
			bGetAllData = TRUE;
		}
		else
		{
			// Add the requested tag in the list
			GTL_SharedExchange_AddTag (pDataRequest, nReadTag, 0, NULL);
		}

		// Get the next node
		hCurrentNode = TlvTree_GetNext (hCurrentNode);
	}

	// If the kernel to use is not specified, the kernel that performed the last transaction will be called
	if(ulKernel == SDSA_KERNEL_IDENTIFIER_UNKNOWN)
	{
		ulKernel = SDSA_Customisation_GetUsedPaymentScheme();
	}

	if(bGetAllData)
	{
		// Call GetAll function
		switch (ulKernel)
		{
		case SDSA_KERNEL_IDENTIFIER_PAYPASS :
			cr = PayPass_GetAllData(pDataRequest);
			break;

		case SDSA_KERNEL_IDENTIFIER_PAYWAVE :
			cr = payWave_GetAllData(pDataRequest);
			break;

		case SDSA_KERNEL_IDENTIFIER_VISAWAVE :
			cr = VisaWave_GetAllData(pDataRequest);
			break;

		case SDSA_KERNEL_IDENTIFIER_EXPRESSPAY :
			cr = ExpressPay3_GetAllData(pDataRequest);
			break;

		case SDSA_KERNEL_IDENTIFIER_INTERAC :
			cr = Interac_GetAllData(pDataRequest);
			break;

		case SDSA_KERNEL_IDENTIFIER_DISCOVER :
			cr = Discover_GetAllData(pDataRequest);
			break;

		default:
			GTL_Traces_TraceDebug("SDSA_GetPaymentData : Unknown value for SDSA_KERNEL_IDENTIFIER_UNKNOWN tag : %x", (unsigned int)ulKernel);
			nResult = SDI_STATUS_KO;
			break;
		}
	}
	else
	{
		// Get the requeted tags
		switch (ulKernel)
		{
		case SDSA_KERNEL_IDENTIFIER_PAYPASS :
			cr = PayPass_GetData (pDataRequest);
			break;

		case SDSA_KERNEL_IDENTIFIER_PAYWAVE :
			cr = payWave_GetData(pDataRequest);
			break;

		case SDSA_KERNEL_IDENTIFIER_VISAWAVE :
			cr = VisaWave_GetData(pDataRequest);
			break;

		case SDSA_KERNEL_IDENTIFIER_EXPRESSPAY :
			cr = ExpressPay3_GetData(pDataRequest);
			break;

		case SDSA_KERNEL_IDENTIFIER_INTERAC:
			cr = Interac_GetData(pDataRequest);
			break;

		case SDSA_KERNEL_IDENTIFIER_DISCOVER:
			cr = Discover_GetData(pDataRequest);
			break;

		default:
			GTL_Traces_TraceDebug("SDSA_GetPaymentData : Unknown value for SDSA_KERNEL_IDENTIFIER_UNKNOWN tag : %x", (unsigned int) ulKernel);
			nResult = SDI_STATUS_KO;
			break;
		}
	}

	if (cr != KERNEL_STATUS_OK)
	{
		GTL_Traces_TraceDebug("SDSA_GetPaymentData : An error occured when getting tags from the PayPass kernel (cr=%02x)", cr);
		nResult = SDI_STATUS_KO;
		goto End;
	}

	if(hOutputTlvTree != NULL)
		SDSA_Common_CopyDataStructInTLVTree(pDataRequest, hOutputTlvTree);
	else
		nResult = SDI_STATUS_INVALID_DATA;


End:
	GTL_SharedExchange_DestroyShare(pDataRequest);

	return (nResult);
}



//! \brief Clear the transaction data.
//! \return
//!	- \ref SDI_STATUS_OK.

int SDSA_ClearPaymentData (void)
{
	// Clear data and deactivate the contactless field
	Cless_ExplicitSelection_ClearGlobalData();

	PayPass_Clear();
	payWave_Clear();
	VisaWave_Clear();
	ExpressPay3_Clear();
	Interac_Clear();
	Discover_Clear();
	
	return (SDI_STATUS_OK);
}



//! \brief Perform the card removal.
//! \param[in] hInputTlvTree Contains the \ref TAG_SDSA_WAIT_CARD_REMOVAL tag indicating if the reader shall wait card removal or not.
//! \return
//!	- \ref SDI_STATUS_OK if processing correctly performed.
//!	- \ref SDI_STATUS_CANCELLED if processing has been cancelled.
//!	- \ref SDI_STATUS_KO if an error occured.

int SDSA_WaitCardRemoval (const TLV_TREE_NODE hInputTlvTree)
{
	int nResult = SDI_STATUS_OK;
	int bEnd = FALSE;
	unsigned int nReadTag;
	TLV_TREE_NODE hCurrentNode;
	unsigned char * pReadValue;
	int bWaitCardRemoval = TRUE;

	GTL_Traces_TraceDebug ("SDSA_WaitCardRemoval");

	// Save the current task identifier
	gs_ProcessingTask = CurrentTask();

	// Check if card removal is required or not
	hCurrentNode = TlvTree_GetFirstChild (hInputTlvTree);

	while (hCurrentNode != NULL)
	{
		// Get the node tag
		nReadTag = TlvTree_GetTag (hCurrentNode);

		if(nReadTag == TAG_SDSA_WAIT_CARD_REMOVAL)
		{
			// Get the identifier of the kernel that will be called
			pReadValue = TlvTree_GetData(hCurrentNode);
			bWaitCardRemoval = pReadValue[0];
			break;
		}

		// Get the next node
		hCurrentNode = TlvTree_GetNext (hCurrentNode);
	}

	// Perform card removal if required
	if (bWaitCardRemoval)
	{
		// If card removal is required, open the field if it is not opened
		if (!ClessEmv_IsDriverOpened())
			ClessEmv_OpenDriver();

		if (SDSA_Common_IsCardInFieldDeselection())
		{
			SDSA_GuiState_DisplayScreen (SDSA_SCREEN_REMOVE_CARD);

			while (!bEnd)
			{
				if (ttestall (USER_EVENT_CANCEL, 10) & USER_EVENT_CANCEL)
				{
					GTL_Traces_TraceDebug ("SDSA_WaitCardRemoval Cancel");
					nResult = SDI_STATUS_CANCELLED;
					bEnd = TRUE;
					continue;
				}
				
				bEnd = (!SDSA_Common_IsCardInFieldDeselection ());
			}
		}
		else
		{
			GTL_Traces_TraceDebug ("SDSA_WaitCardRemoval no card");
			nResult = SDI_STATUS_NO_CARD;
		}
	}

	if (ClessEmv_IsDriverOpened())
		ClessEmv_CloseDriver();

	return (nResult);
}


				
//! \brief This function get the currency label and exponent from the parameters.
//! \param[in] pCurrencyCode Currency code to find in the parameter file.
//! \param[out] pCurrencyLabel Currency label to get.
//! \param[out] pCurrencyExponent Currency exponent to get.
//!	\return
//!	- \a TRUE if currency is found.
//!	- \a FALSE indicate an invalid parameter as the currency code provided is unknown from the application.

static int __SDSA_Transaction_GetCurrencyFromParameters(unsigned char *pCurrencyCode, char **pCurrencyLabel,unsigned char *pCurrencyExponent)
{
	int n_NbMoney;
	S_MONEY_EXTENDED * ps_x_Money;
	int i;
	char ucCurrencyCode[3];

	GTL_Convert_DcbToAscii(pCurrencyCode, ucCurrencyCode, 1, 4);

	// Get the list of supported money
	SDSA_Parameters_GetMoneyExtended(&n_NbMoney, &ps_x_Money);

	// Try to find the requested money 
	for(i=0; i<n_NbMoney; i++)
	{
		if(memcmp(ps_x_Money[i].currency.code, ucCurrencyCode, 3) == 0)
		{
			// Currency code found in the parameter file, get the currency label and exponent
			*pCurrencyLabel = (char*)ps_x_Money[i].currency.nom;
			*pCurrencyExponent = ps_x_Money[i].currency.posdec;
			return (TRUE);
		}
	}

	// Not found, check if it is the default currency Euro
	if(memcmp(ucCurrencyCode,"978", 3) == 0)
	{
		*pCurrencyLabel = "EUR";
		*pCurrencyExponent = 2;
		return (TRUE);
	}

	return (FALSE);
}  

//!	\brief Save the transaction data in the application transaction context.
//!	\param[in] hInputTlvTree TLV-Tree containing the data to start the transaction.
//!	\return
//!	- \a TRUE if correctly performed.
//!	- \a FALSE if an error occured (invalid data has been provided).

static int __SDSA_Transaction_ExtractAndStoreData (TLV_TREE_NODE hInputTlvTree)
{
	unsigned int nReadTag, nReadLength, nLastPANLength, nListOfTagsLength;
	int nResult = TRUE;
	TLV_TREE_NODE hCurrentNode;
	unsigned char ucCurrencyLabel[4];
	int nDatePresent, nTimePresent;
	DATE date;
	unsigned char ucDate[3], ucTime[3];

	unsigned char * pTransactionType = NULL;
	unsigned char * pCurrencyCode = NULL;
	char * pCurrencyLabel = NULL;
	unsigned char * pAmountAuthNum = NULL;
	unsigned char * pAmountOtherNum = NULL;
	unsigned char * pTransactionDate = NULL;
	unsigned char * pTransactionTime = NULL;
	unsigned char * pIfdSerialNumber = NULL;
	unsigned char ucCurrencyExponent = NULL;
	unsigned char * pTsc = NULL;
	unsigned char * pLastTransactionPAN = NULL;
	unsigned char * pCashBack = NULL;
	unsigned char * pListOfTags = NULL;
	
	nLastPANLength = 0;
	nListOfTagsLength = 0;
	nDatePresent = FALSE;
	nTimePresent = FALSE;

	// Get the first node
	hCurrentNode = TlvTree_GetFirstChild (hInputTlvTree);

	while (hCurrentNode != NULL)
	{
		// Get the node tag
		nReadTag = TlvTree_GetTag (hCurrentNode);

		switch (nReadTag)
		{
		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_EMV_AMOUNT_AUTH_NUM): // Amount, Authorized numeric
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if (nReadLength == LENGTH_OF_TRANSACTION_AMOUNT_AUTH_NUM)
			{
				// Tag is correctly provided
				pAmountAuthNum = TlvTree_GetData(hCurrentNode);
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_EMV_AMOUNT_OTHER_NUM): // Amount, Other numeric (optional)
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if (nReadLength == LENGTH_OF_TRANSACTION_AMOUNT_OTHER_NUM)
			{
				// Tag is correctly provided
				pAmountOtherNum = TlvTree_GetData(hCurrentNode);
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_EMV_TRANSACTION_DATE): // Transaction date
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if (nReadLength == LENGTH_OF_TRANSACTION_DATE)
			{
				// Tag is correctly provided
				pTransactionDate = TlvTree_GetData(hCurrentNode);
				nDatePresent = TRUE;
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_EMV_TRANSACTION_TIME): // Transaction time
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if (nReadLength == LENGTH_OF_TRANSACTION_TIME)
			{
				// Tag is correctly provided
				pTransactionTime = TlvTree_GetData(hCurrentNode);
				nTimePresent = TRUE;
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_EMV_TRANSACTION_TYPE): // Transaction type
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if (nReadLength == LENGTH_OF_TRANSACTION_TYPE)
			{
				// Tag is correctly provided
				pTransactionType = TlvTree_GetData(hCurrentNode);
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_EMV_IFD_SERIAL_NUMBER): // IFD serial number (if present)
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if (nReadLength == LENGTH_OF_IFD_SERIAL_NUMBER)
			{
				// Tag is correctly provided
				pIfdSerialNumber = TlvTree_GetData(hCurrentNode);
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_EMV_TRANSACTION_CURRENCY_CODE): // Transaction currency code
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if (nReadLength == LENGTH_OF_TRANSACTION_CURRENCY_CODE)
			{
				// Tag is correctly provided
				pCurrencyCode = TlvTree_GetData(hCurrentNode);

				// Get the currency label and exponent from the parameters. If not found, indicate an invalid parameter as the currency code provided is unknown from the application
				if(!__SDSA_Transaction_GetCurrencyFromParameters(pCurrencyCode, &pCurrencyLabel, &ucCurrencyExponent))
				{
					GTL_Traces_TraceDebug ("Currency code provided is unknown from the application (%02x %02x)", pCurrencyCode[0], pCurrencyCode[1]);
					nResult = FALSE;
					goto End;
				}

				memset(ucCurrencyLabel,0,sizeof(ucCurrencyLabel));
				memcpy(ucCurrencyLabel, pCurrencyLabel, 3);
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_SDSA_TRANSACTION_CASHBACK): // Cashback
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if (nReadLength == LENGTH_OF_CASHBACK)
			{
				// Tag is correctly provided
				pCashBack = TlvTree_GetData(hCurrentNode);
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_EMV_TRANSACTION_SEQUENCE_COUNTER): // Transaction Sequence Counter (if present)
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if (nReadLength == LENGTH_OF_TRANSACTION_SEQUENCE_COUNTER)
			{
				// Tag is correctly provided
				pTsc = TlvTree_GetData(hCurrentNode);
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_SDSA_LIST_OF_OUTPUT_TAGS): // List of tags to be returned at the end of the transaction (if present)
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if (nReadLength <= LENGTH_OF_LIST_OF_OUTPUT_TAGS)
			{
				// Tag is correctly provided
				nListOfTagsLength = nReadLength;
				pListOfTags = TlvTree_GetData(hCurrentNode);
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////
		case (TAG_VISAWAVE_LAST_TRANSACTION_PAN): // Last transaction PAN (if present)
			nReadLength = TlvTree_GetLength(hCurrentNode);
			if ((nReadLength > 0) && (nReadLength <= LENGTH_OF_LAST_TRANSACTION_PAN))
			{
				// Tag is correctly provided
				nLastPANLength = nReadLength;
				pLastTransactionPAN = TlvTree_GetData(hCurrentNode);
			}
			else
			{
				GTL_Traces_TraceDebug ("Tag with bad length (T:%02x, L:%02x)", nReadTag, nReadLength);
				nResult = FALSE;
				goto End;
			}
			break;
		
		///////////////////////////////////////////////////////////////////////////////////////////////
		default:
			GTL_Traces_TraceDebug ("Unexpected tag, ignore it (%02x)", nReadTag);
			break;
		}

		// Get the next node
		hCurrentNode = TlvTree_GetNext (hCurrentNode);
	}

	// If the transaction date and time are not available in the input data, get the date and time from the IST device
	if((!nDatePresent) || (!nTimePresent))
	{	
		if(read_date(&date) == OK)
		{
			ucDate[0] = ((date.year[0] - 0x30) << 4) + (date.year[1] - 0x30);
			ucDate[1] = ((date.month[0] - 0x30) << 4) + (date.month[1] - 0x30);
			ucDate[2] = ((date.day[0] - 0x30) << 4) + (date.day[1] - 0x30);
			
			pTransactionDate = ucDate;

			ucTime[0] = ((date.hour[0] - 0x30) << 4) + (date.hour[1] - 0x30);
			ucTime[1] = ((date.minute[0] - 0x30) << 4) + (date.minute[1] - 0x30);
			ucTime[2] = ((date.second[0] - 0x30) << 4) + (date.second[1] - 0x30);

			pTransactionTime = ucTime;

			// GTL_Traces_TraceDebug ("Get IST date: %02X%02X%02X %02X%02X%02X", ucDate[0], ucDate[1], ucDate[2], ucTime[0], ucTime[1], ucTime[2]);
		}
		else
		{
			nResult = FALSE;
			goto End;
		}
	}

	// Save the list of output tags to be returned at the end of the transaction
	SDSA_Common_SetListOfOutputTags(pListOfTags, nListOfTagsLength);

	// Save the transaction data in the global context
	SDSA_Fill_PrepareAndSaveClessGiveInfoTransactionData (TRUE, pTransactionType, pCashBack, pCurrencyCode, ucCurrencyExponent, ucCurrencyLabel, pAmountAuthNum, pAmountOtherNum, pIfdSerialNumber, pTransactionTime, pTransactionDate, pTsc, nLastPANLength, pLastTransactionPAN);

End:
	return (nResult);
}


//! \brief Perform a contactless transaction in explicit mode, with transaction amount provided.
//! \param[out] hOutputTlvTree Output TLV Tree containing th etransaction result.

static int __SDSA_PerformClessTransaction (TLV_TREE_NODE hOutputTlvTree)
{
	int nResult = SDI_STATUS_OK;
	TLV_TREE_NODE hTransactionTlvTree = NULL;
	unsigned long ulAmount;
	T_SHARED_DATA_STRUCT * pSharedData = NULL;
	unsigned char ucBuffer[4];
	int bEnd, bCancel, nEvent;
	int nKernelToUse, nKernelUsed;
	unsigned char ucKernelUsed[2];
	int cr_temp;
	int nPosition;
	unsigned long ulReadLength;
	const unsigned char * pValue;


	// Set the transaction kernel to "unknown"
	SDSA_Customisation_SetUsedPaymentScheme (SDSA_KERNEL_IDENTIFIER_UNKNOWN);
	nKernelUsed = SDSA_KERNEL_IDENTIFIER_UNKNOWN;

	// Set the transaction mode (explicit)
	SDSA_Common_SetTransactionMode (SDSA_COMMON_MODE_EXPLICIT);

	// Init payWave fallback (If the VisaWave kernel detects a payWave card, the transaction will be held by the payWave kernel)
	SDSA_VisaWave_SetpayWaveFallBack(FALSE);
	SDSA_ExpressPay_UnsetMobileCVM();
	
	// Set the current application language with the manager language
	SDSA_UserInterface_SetMerchantLanguage();

	// Get the transaction amount
	ulAmount = SDSA_Fill_GiveAmount ();

	//// Prepare data for card detection and application selection
	
	// Create the shared buffer (for transaction result)
	pSharedData = GTL_SharedExchange_InitShared(10240);
	if (pSharedData == NULL)
	{
		GTL_Traces_TraceDebug ("__SDSA_PerformClessTransaction : pSharedData is NULL");
		nResult = SDI_STATUS_KO;
		goto End;
	}


	//// Prepare data and structure for kernel processing after application selection
	// Input parameters
	if (!SDSA_Fill_InitSharedBufferWithKernels (&g_pKernelSharedBuffer))
	{
		GTL_Traces_TraceDebug("__SDSA_PerformClessTransaction : SDSA_Fill_InitSharedBufferWithKernels failed");
		nResult = SDI_STATUS_KO;
		goto End;
	}

	// Create the TLV Tree to provide all the application selection parameters (including transaction amount)
	hTransactionTlvTree = TlvTree_New(0);
	
	if (hTransactionTlvTree != NULL)
	{
		// Fill the hTransactionTlvTree with the correct parameters
		if (!SDSA_Fill_GetApplicationSelectionParameters (&hTransactionTlvTree, &pTreeCurrentParam, TRUE))
		{
			GTL_Traces_TraceDebug ("__SDSA_PerformClessTransaction : SDSA_Fill_GetApplicationSelectionParameters failed");
			nResult = SDI_STATUS_KO;
			goto End;
		}

		// Add the transaction amount
		GTL_Convert_UlToBinNumber(ulAmount, ucBuffer, 4);
		TlvTree_AddChild(hTransactionTlvTree, TAG_EMV_AMOUNT_AUTH_BIN, ucBuffer, 4);
		
		// Call DLL to load data
		nResult = Cless_ExplicitSelection_LoadData (hTransactionTlvTree);
		if (nResult != CLESS_STATUS_OK)
		{
			GTL_Traces_TraceDebug("__SDSA_PerformClessTransaction : Cless_ExplicitSelection_LoadData failed (nResult=%02x)", nResult);
			nResult = SDI_STATUS_KO;
			goto End;
		}
	
		// Set the customisation function to be called for GUI customisation
		Cless_ExplicitSelection_Custom_RegistrationForGui (&SDSA_Customisation_SelectionGui);
			
		// Set the customisation function to be called for application selection customisation
		Cless_ExplicitSelection_Custom_RegistrationForApplicationSelection(&SDSA_Customisation_CustAsProc, NULL);
		
		// Perform the transaction pre processing
		nResult = Cless_ExplicitSelection_EntryPoint_TransactionPreProcessing ();
		if (nResult != CLESS_STATUS_OK)
		{
			GTL_Traces_TraceDebug("__SDSA_PerformClessTransaction : Cless_ExplicitSelection_EntryPoint_TransactionPreProcessing failed (nResult=%02x)", nResult);
			nResult = SDI_STATUS_KO;
			goto End;
		}

		if(!__SDSA_Transaction_CheckPreProcessingResults())
		{
			GTL_Traces_TraceDebug("SDSA_Transaction_CheckPreProcessingResults : failed");
			nResult = SDI_STATUS_CONTACTLESS_NOT_ALLOWED;
			goto End;
		}

		do // While transaction not completed
		{
			// Set the transaction kernel to "unknown"
			SDSA_Customisation_SetUsedPaymentScheme (SDSA_KERNEL_IDENTIFIER_UNKNOWN);
			nKernelUsed = SDSA_KERNEL_IDENTIFIER_UNKNOWN;

			// Clear the pSharedData structure
			GTL_SharedExchange_ClearEx (pSharedData, FALSE);

			// Update the transaction status
			SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_DETECT_CARD);

			// Launch the card detection
			nResult = Cless_ExplicitSelection_GlobalCardDetection();
			if (nResult != CLESS_STATUS_OK)
			{
				GTL_Traces_TraceDebug("__SDSA_PerformClessTransaction : Cless_ExplicitSelection_GlobalCardDetection failed (nResult=%02x)", nResult);
				nResult = SDI_STATUS_KO;
				goto End;
			}

			// Wait contactless event (or cancel from terminal application)
			bEnd = FALSE;
			bCancel = FALSE;
			
			do
			{
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
				GTL_Traces_TraceDebug ("__SDSA_PerformClessTransaction : Card detection has been cancelled");
				nResult = SDI_STATUS_CANCELLED;
				goto End;
			}
			
			if (nEvent != CLESS)
			{
				GTL_Traces_TraceDebug ("__SDSA_PerformClessTransaction : Unknown event (nEvent=%02x)", nEvent);
				nResult = SDI_STATUS_KO;
				goto End;
			}
			
			
			// Get the card detection result
			nResult = Cless_Generic_CardDetectionGetResults (pSharedData, TRUE);

			nPosition = SHARED_EXCHANGE_POSITION_NULL;

			cr_temp = GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_GENERIC_DETECTION_RESULT, &ulReadLength, &pValue);

			if (cr_temp != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_Traces_TraceDebug ("__SDSA_PerformClessTransaction : TAG_GENERIC_DETECTION_RESULT not found (cr_temp = %02x)\n", cr_temp);
				nResult = SDI_STATUS_KO;
				goto End;
			}

			if (pValue[0] == DETECT_RESULT_GLOBAL_TO)
			{
				// Visa AP specific: display 'NO CARD' message if the detection timeout elapsed.
				if(SDSA_VisaWave_IsVisaAsiaGuiMode())
				{
					Helper_DisplayMessage(VISAWAVE_MESS_NO_CARD, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
					Helper_WaitUserDisplay();
				}

				// Interac specific: display 'NO CARD' message if the detection timeout elapsed.
				if(SDSA_Interac_IsInteracGuiMode())
				{
					SDSA_GuiState_DisplayScreen (SDSA_INTERAC_SCREEN_TIMEOUT_ELAPSED);
					Helper_WaitUserDisplay();
				}
				nResult = SDI_STATUS_NO_CARD;
				goto End;
			}

			if (pValue[0] != DETECT_RESULT_OK)
			{
				GTL_Traces_TraceDebug ("__SDSA_PerformClessTransaction : TAG_GENERIC_DETECTION_RESULT = %02x\n", pValue[0]);
				nResult = SDI_STATUS_KO;
				goto End;
			}

			if (nResult != CLESS_STATUS_OK)
			{
				GTL_Traces_TraceDebug("__SDSA_PerformClessTransaction : Cless_Generic_CardDetectionGetResults failed (nResult=%02x)", nResult);
				nResult = SDI_STATUS_KO;
				goto End;
			}

			do{
               	SDSA_payWave_SetQVSDCNotAllowedForAmount(FALSE);
               	
				// Set the transaction kernel to "unknown"
				SDSA_Customisation_SetUsedPaymentScheme (SDSA_KERNEL_IDENTIFIER_UNKNOWN);
				nKernelUsed = SDSA_KERNEL_IDENTIFIER_UNKNOWN;

				// A card has been detected, perform the application selection
				nResult = Cless_ExplicitSelection_Selection_ApplicationSelectionProcess (pSharedData);
    	
				if (nResult != CLESS_STATUS_OK)
				{
					nResult = SDSA_Customisation_AnalyseApplicationSelectionResult(nResult);
					goto End_While;
				}

Restart_AfterVisaWave:

				// First clear the buffer to be used with the contactless kernel
				GTL_SharedExchange_ClearEx (g_pKernelSharedBuffer, FALSE);

				// Add the generic transaction data (previously saved) in the shared buffer (date, time, amount, etc).
				if (!SDSA_Fill_TransactionGenericData(g_pKernelSharedBuffer))
				{
					GTL_Traces_TraceDebug("__SDSA_PerformClessTransaction : SDSA_Fill_TransactionGenericData failed");
					nResult = SDI_STATUS_KO;
					goto End;
				}

				//Add AID related data in the shared buffer
				if (!SDSA_Fill_AidRelatedData (g_pKernelSharedBuffer, pSharedData, &nKernelToUse))
				{
					GTL_Traces_TraceDebug("__SDSA_PerformClessTransaction : SDSA_Fill_AidRelatedData failed");
					nResult = SDI_STATUS_KO;
					goto End;
				}

                if (SDSA_payWave_IsQVSDCNotAllowedForAmount())
                {
                    GTL_Traces_TraceDebug("__SDSA_PerformClessTransaction : SDSA_Fill_AidRelatedData failed Amount greater than TAG_EP_CLESS_TRANSACTION_LIMIT");
                    nResult = CLESS_CR_MANAGER_REMOVE_AID;
					goto End;
                }

				// Update the transaction status
				SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_IN_PROGRESS);

				// Call the kernel in relationship with AID
				switch (nKernelToUse)
				{
				case DEFAULT_EP_KERNEL_PAYPASS :
					nResult = SDSA_PayPass_PerformTransaction(g_pKernelSharedBuffer, hOutputTlvTree);
					nKernelUsed = SDSA_KERNEL_IDENTIFIER_PAYPASS;
					break;

				case DEFAULT_EP_KERNEL_VISA :
					// If the VisaWave kernel is present in the terminal, it will first try to perform the transaction.
					// Then if it detects that the presented card is a payWave card, the payWave kernel will perform the transaction.
					if(SDSA_VisaWave_isVisaWaveProcessing())
					{
						nResult = SDSA_VisaWave_PerformTransaction(g_pKernelSharedBuffer, hOutputTlvTree);
						nKernelUsed = SDSA_KERNEL_IDENTIFIER_VISAWAVE;
						if(nResult == VISAWAVE_STATUS_PAYWAVE_CARD)
						{
							// It is not a VisaWave card
							SDSA_VisaWave_SetpayWaveFallBack(TRUE);
							goto Restart_AfterVisaWave;
						}
					}
					else
					{
						nResult = SDSA_payWave_PerformTransaction(g_pKernelSharedBuffer, hOutputTlvTree);
						nKernelUsed = SDSA_KERNEL_IDENTIFIER_PAYWAVE;
					}
					break;

				case DEFAULT_EP_KERNEL_AMEX :
					nResult = SDSA_ExpressPay_PerformTransaction(g_pKernelSharedBuffer, hOutputTlvTree);
					nKernelUsed = SDSA_KERNEL_IDENTIFIER_EXPRESSPAY;
					break;

				case DEFAULT_EP_KERNEL_INTERAC :
					nResult = SDSA_Interac_PerformTransaction(g_pKernelSharedBuffer, hOutputTlvTree);
					nKernelUsed = SDSA_KERNEL_IDENTIFIER_INTERAC;
					break;

				case DEFAULT_EP_KERNEL_DISCOVER :
					nResult = SDSA_Discover_PerformTransaction(g_pKernelSharedBuffer, hOutputTlvTree);
					nKernelUsed = SDSA_KERNEL_IDENTIFIER_DISCOVER;
					break;

				default:
					GTL_Traces_TraceDebug("__SDSA_PerformClessTransaction : Unknown Kernel to use in cless_debit_aid() : %x", nKernelToUse);
					nKernelUsed = SDSA_KERNEL_IDENTIFIER_UNKNOWN;
					break;
				}					
			}while(nResult == CLESS_CR_MANAGER_REMOVE_AID);

End_While:
			if (nResult == CLESS_CR_MANAGER_RESTART_DOUBLE_TAP)
				Cless_ExplicitSelection_DetectionPrepareForRestart (TRUE);
			if (nResult == CLESS_CR_MANAGER_RESTART)
				Cless_ExplicitSelection_DetectionPrepareForRestart (FALSE);

		} while ((nResult == CLESS_CR_MANAGER_RESTART_DOUBLE_TAP) || (nResult == CLESS_CR_MANAGER_RESTART));
	}
	else
	{
		GTL_Traces_TraceDebug ("__SDSA_PerformClessTransaction : hTransactionTlvTree is NULL");
		nResult = SDI_STATUS_KO;
		goto End;
	}

End:

	// Indicates the kernel that performed the transaction
	GTL_Convert_UlToBinNumber(nKernelUsed, ucKernelUsed, 2);
	TlvTree_AddChild (hOutputTlvTree, TAG_SDSA_KERNEL_IDENTIFIER, ucKernelUsed, 2);

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

	return (nResult);
}

//! \brief Function that allows adding proprietary commands for specific needs.
//! \param[in] hInputTlvTree Contains the input data.
//! \param[out] pOutputTlvTree Contains output data.
//! \return
//!	- \ref SDI_STATUS_OK if correctly performed.
//!	- \ref SDI_STATUS_MISSING_DATA if a mandatory input data is missing.

int SDSA_Generic_UserCommand_01 (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	TLV_TREE_NODE hCurrentNode;
	unsigned char uc_Date[] = {0x10,0x10,0x10};
	unsigned char *pDate;

	// Get the date sent by the caller
	hCurrentNode = TlvTree_Find(hInputTlvTree, TAG_EMV_TRANSACTION_DATE, 0);
	if (hCurrentNode != NULL)
	{
		pDate = TlvTree_GetData(hCurrentNode);
		GTL_Traces_TraceDebug ("SDSA_Generic_UserCommand: received date %02X %02X %02X", pDate[0], pDate[1], pDate[2]);
		TlvTree_AddChild (hOutputTlvTree, TAG_EMV_TRANSACTION_DATE, uc_Date, sizeof(uc_Date));
		return (SDI_STATUS_OK);
	}
	else
	{
		GTL_Traces_TraceDebug ("SDSA_Generic_UserCommand: missing TAG_EMV_TRANSACTION_DATE tag");
		return (SDI_STATUS_MISSING_DATA);
	}
}


static int __SDSA_Transaction_CheckPreProcessingResults(void)
{
	TLV_TREE_NODE hPreProcessingTlvTree;
	TLV_TREE_NODE hCurrentNode;
	TLV_TREE_NODE hAidAdditionnalResults;
	unsigned int nReadTag, nReadLength;
	unsigned char * pValue;
	int nResult;
	T_PRE_PROCESSING_ADD_RESULT_AID tAddAidResult;
	int nAnAppliAllowed;

	nAnAppliAllowed = FALSE;

	hPreProcessingTlvTree = TlvTree_New(0);
	if (hPreProcessingTlvTree != NULL)
	{
		nResult = Cless_Generic_EntryPoint_GetPreProcessingResults (hPreProcessingTlvTree);
		if (nResult != CLESS_STATUS_OK)
		{
			GTL_Traces_TraceDebug("SDSA_Transaction_CheckPreProcessingResults : Cless_Generic_EntryPoint_GetPreProcessingResults failed (nResult=%02x)", nResult);
			nResult = FALSE;
			goto End;
		}

		// Get the first node
		hCurrentNode = TlvTree_GetFirstChild (hPreProcessingTlvTree);

		while (hCurrentNode != NULL)
		{
			// Get the node tag
			nReadTag = TlvTree_GetTag (hCurrentNode);

			switch (nReadTag)
			{
				///////////////////////////////////////////////////////////////////////////////////////////////
			case (TAG_EP_AID_PRE_PROCESSING_RESULT):

				hAidAdditionnalResults = TlvTree_Find(hCurrentNode, TAG_EP_AID_ADDITIONAL_RESULTS, 0);
				if (hAidAdditionnalResults != NULL)
				{
					pValue = TlvTree_GetData(hAidAdditionnalResults);
					nReadLength = TlvTree_GetLength(hAidAdditionnalResults);
					if ((pValue != NULL) && (nReadLength == sizeof(T_PRE_PROCESSING_ADD_RESULT_AID)))
					{
						memcpy(&tAddAidResult, pValue, nReadLength);
						if(!tAddAidResult.bContactlessApplicationNotAllowed)
						{
							nAnAppliAllowed = TRUE;
						}
					}
				}
				break;

				///////////////////////////////////////////////////////////////////////////////////////////////
			default:
				GTL_Traces_TraceDebug ("Unexpected tag, ignore it (%02x)", nReadTag);
				break;
			}

			// Get the next node
			hCurrentNode = TlvTree_GetNext (hCurrentNode);
		}
	}

End:

	// Release the TLV Tree if allocated
	if (hPreProcessingTlvTree != NULL)
	{
		TlvTree_Release(hPreProcessingTlvTree);
	}

	return (nAnAppliAllowed);
}
