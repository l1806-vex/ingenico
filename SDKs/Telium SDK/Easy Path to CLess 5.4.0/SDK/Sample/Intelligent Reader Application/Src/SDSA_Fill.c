/**
 * \file	SDSA_Fill.c
 * \brief	This module is used to fill the structure with data necessary for transaction.
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
 **/

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDSA_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define ADD_STEP_INTERRUPTION(step,buffer)	buffer[sizeof(buffer)-1-step/8]+=1<<(step%8)	/*!< Macro to set information on buffer to stop transaction flow on a specific step */
#define ADD_STEP_CUSTOM(step,buffer) 		buffer[sizeof(buffer)-1-step/8]+=1<<(step%8)	/*!< Macro to set information on buffer to custom transaction flow on a specific step. */


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global data definitions ////////////////////////////////////

T_SHARED_DATA_STRUCT * g_pKernelSharedBuffer;			/*!< Share exchange buffer used with the payment kernels. */
T_PAYMENT_DATA_STRUCT gs_tTransactionDataStructure;     /*!< Structure that contains the transaction data */

static unsigned char gs_ucTransactionCashBack;			/*!< Generic transaction data : Transaction cashback. */
static unsigned long gs_ulTransactionSeqCounter;		/*!< Transaction sequence counter */		
static unsigned char gs_ucLastTransactionPAN[10];		/*!< PAN of the card used for the last transaction */
static unsigned int gs_nLastTransactionPANLength;		/*!< Length of the PAN for the last transaction */


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static unsigned int __SDSA_Fill_FoundApplicationProgramId(T_SHARED_DATA_STRUCT * pSharedStruct, unsigned char **pReadValueAPI, unsigned long * pulReadLengthAPI);
static unsigned int __SDSA_Fill_SelectCandidateElement (T_SHARED_DATA_STRUCT * pSharedStruct, unsigned char ** pReadValueSelected, unsigned long * pulReadLengthSelected);


/////////////////////////////////////////////////////////////////
//// Function ///////////////////////////////////////////////////

//! \brief Gives the transaction data structure.
//! \return The transaction data structure.

const T_PAYMENT_DATA_STRUCT * SDSA_Fill_GetTransactionDataStructure (void)
{
	return (&gs_tTransactionDataStructure);
}



//! \brief Gives transaction amount.
//! \return
//!		- \a transaction amount.

unsigned long SDSA_Fill_GiveAmount(void)
{
	return (gs_tTransactionDataStructure.ulTransactionAmountBin);
}


//! \brief Gives the money label.
//! \return
//!		- \a money label.
//! \note This function shall be called after having loaded the parameters.

unsigned char *SDSA_Fill_GiveMoneyLabel(void)
{
	return (gs_tTransactionDataStructure.ucTransactionCurrencyLabel);
}


//! \brief Gives transaction type.
//! \return
//!		- \a transaction type.

unsigned char SDSA_Fill_GiveTransactionType(void)
{
	return (gs_tTransactionDataStructure.ucTransactionType);
}


//! \brief Indicates if there is at least one Visa AID in the parametres.
//! \return
//!		- \a TRUE if at least one Visa AID is present.
//!		- \a FALSE if not.
//! \note This function shall be called after having loaded the parameters.

int SDSA_Fill_IsThereVisaAid (void)
{
	int nResult = FALSE;
	TLV_TREE_NODE pTlvTmp; 		// Temporary Node
	TLV_TREE_NODE pTlvAidParam; // Temporary Node
	unsigned short usTempKernelToUse;
	int nNbAid, nIndex;
	
	// For each supported AID, 
	nNbAid = SDSA_Parameters_GiveAIDNumber();
	
	for (nIndex=0; nIndex<nNbAid; nIndex++)
	{
		pTlvAidParam = SDSA_Parameters_GiveAIDTLVTtree(nIndex);
		
		// TAG_EP_KERNEL_TO_USE : 0x9F928101
		pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_KERNEL_TO_USE, 0);
		if (pTlvTmp != 0)
		{
			usTempKernelToUse = (((unsigned char *)TlvTree_GetData(pTlvTmp))[0] << 8) + ((unsigned char *)TlvTree_GetData(pTlvTmp))[1];
			if (usTempKernelToUse == DEFAULT_EP_KERNEL_VISA)
			{
				nResult = TRUE;
				goto End;
			}
		}
	}

End:
	return (nResult);
}


//! \brief Indicates if there is only Amex AIDs in the parameters.
//! \return
//!		- \a TRUE if only Amex AIDs are present.
//!		- \a FALSE if not.
//! \note This function shall be called after having loaded the parameters.

int SDSA_Fill_IsThereAmexAidOnly (void)
{
	int nResult = FALSE;
	TLV_TREE_NODE pTlvTmp; 		// Temporary Node
	TLV_TREE_NODE pTlvAidParam; // Temporary Node
	unsigned short usTempKernelToUse;
	int nNbAid, nIndex;
	
	// For each supported AID, 
	nNbAid = SDSA_Parameters_GiveAIDNumber();
	
	for (nIndex=0; nIndex<nNbAid; nIndex++)
	{
		pTlvAidParam = SDSA_Parameters_GiveAIDTLVTtree(nIndex);
		
		// TAG_EP_KERNEL_TO_USE : 0x9F928101
		pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_KERNEL_TO_USE, 0);
		if (pTlvTmp != 0)
		{
			usTempKernelToUse = (((unsigned char *)TlvTree_GetData(pTlvTmp))[0] << 8) + ((unsigned char *)TlvTree_GetData(pTlvTmp))[1];
			if (usTempKernelToUse != DEFAULT_EP_KERNEL_AMEX)
			{
				nResult = FALSE;
				goto End;
			}
			else
			{
				nResult = TRUE;
			}
		}
	}

End:
	return (nResult);
}


//! \brief Save some transaction data.
//! \param[in] bAmountPresent Indicates if the transaction amount is present or not.
//! \param[in] pTransactionType Indicates the transaction type to save.
//! \param[in] ucTransactionCashBack Indicates the specific transaction cashback type.
//! \param[in] pCurrencyCode Indicates the transaction currency code to save (shall be coded on 2 bytes).
//! \param[in] ucCurrencyExponent Indicates the transaction type to save.
//! \param[in] pCurrencylabel Indicates the currency label to save.
//! \param[in] pAmountAuthNum Indicates the transaction amount (numeric format) to save.
//! \param[in] pAmountOtherNum Indicates the transaction amount other (numeric format) to save.
//! \param[in] pIfdSerialNumber IFD serial number. If not provided, the Intelligent Reader one is used.
//! \param[in] pTransactionTime Transaction time.
//! \param[in] pTransactionDate Transaction date.
//! \param[in] pTransactionSeqCounter Transaction sequence counter.
//! \param[in] nLastPANLength Length of the PAN used for the last transaction (VisaWave need).
//! \param[in] pLastPAN PAN used for the last transaction (VisaWave need).

void SDSA_Fill_PrepareAndSaveClessGiveInfoTransactionData (const unsigned char bAmountPresent, const unsigned char * pTransactionType,  
																  const unsigned char * pTransactionCashBack, const unsigned char * pCurrencyCode,
																  const unsigned char ucCurrencyExponent, const unsigned char * pCurrencyLabel,
																  const unsigned char * pAmountAuthNum, const unsigned char * pAmountOtherNum,
																  const unsigned char * pIfdSerialNumber, const unsigned char * pTransactionTime,
																  const unsigned char * pTransactionDate, const unsigned char * pTransactionSeqCounter,
																  const unsigned int nLastPANLength, const unsigned char * pLastPAN)
{
	unsigned long ulTemp;
	NO_SERIE serial;

	// Save the transaction data in the structure
	gs_tTransactionDataStructure.bIsAmountPresent = bAmountPresent;
	
	if(pTransactionType != NULL)
		gs_tTransactionDataStructure.ucTransactionType = pTransactionType[0];
	else
		gs_tTransactionDataStructure.ucTransactionType = SDSA_TRANSACTION_TYPE_DEBIT;
	
	if(pTransactionCashBack != NULL)
		gs_ucTransactionCashBack = pTransactionCashBack[0];
	else
		gs_ucTransactionCashBack = 0x00; // No CashBack

	memcpy (gs_tTransactionDataStructure.ucTransactionDate, pTransactionDate, sizeof(gs_tTransactionDataStructure.ucTransactionDate));
	memcpy (gs_tTransactionDataStructure.ucTransactionTime, pTransactionTime, sizeof(gs_tTransactionDataStructure.ucTransactionTime));
	memcpy (gs_tTransactionDataStructure.ucTransactionCurrencyCode, pCurrencyCode, sizeof (gs_tTransactionDataStructure.ucTransactionCurrencyCode));
	memcpy (gs_tTransactionDataStructure.ucTransactionCurrencyLabel, pCurrencyLabel, sizeof (gs_tTransactionDataStructure.ucTransactionCurrencyLabel));
	gs_tTransactionDataStructure.ucTransactionCurrencyExponent = ucCurrencyExponent;

	GTL_Convert_DcbNumberToUl (pAmountAuthNum, &ulTemp, 6);
	gs_tTransactionDataStructure.ulTransactionAmountBin = ulTemp;

	if (pAmountOtherNum != NULL)
		GTL_Convert_DcbNumberToUl (pAmountOtherNum, &ulTemp, 6);
	else
		ulTemp = 0;
	gs_tTransactionDataStructure.ulTransactionAmountOtherBin = ulTemp;

	memset(gs_tTransactionDataStructure.ucIfdSerialNumber, 0, sizeof(gs_tTransactionDataStructure.ucIfdSerialNumber));

	// Get and save the IFD serial number (for future use)
	if (pIfdSerialNumber == NULL)
	{
		PSQ_Give_Serial_Number(serial);
		memcpy (gs_tTransactionDataStructure.ucIfdSerialNumber, serial, 8);
	}
	else
	{
		memcpy (gs_tTransactionDataStructure.ucIfdSerialNumber, pIfdSerialNumber, 8);
	}

	// Save the transaction sequence number
	if (pTransactionSeqCounter != NULL)
		GTL_Convert_DcbNumberToUl (pTransactionSeqCounter, &ulTemp, 4);
	else
		ulTemp = 0;
	gs_ulTransactionSeqCounter = ulTemp;

	// Save the PAN of the last transaction (VisaWave specific)
	if ((nLastPANLength > 0) && (nLastPANLength <= 10))
	{
		memcpy (gs_ucLastTransactionPAN, pLastPAN, nLastPANLength);
		gs_nLastTransactionPANLength = nLastPANLength;
	}
	else
		gs_nLastTransactionPANLength = 0;
}


//! \brief Save the available amount returned by the card (if available).
//! \brief This value could be used when displaying transaction result for example.
//! \param[in] nVisa Indicates if it is a payWave or a VisaWave transaction.
//! \param[in] pDataStruct share buffer with tags informations.

void SDSA_Fill_SaveAvailableAmount (int nVisa, T_SHARED_DATA_STRUCT * pDataStruct)
{
	int nFound;
	unsigned char * pAvailable;
	unsigned long ulTemp;

	if(nVisa == HELPERS_VISAWAVE)
		nFound = SDSA_Common_RetreiveInfo (pDataStruct, TAG_VISAWAVE_VLP_AVAILABLE_FUNDS, &pAvailable);
	else
		nFound = SDSA_Common_RetreiveInfo (pDataStruct, TAG_PAYWAVE_AVAILABLE_OFFLINE_SPENDING_AMOUNT, &pAvailable);
	
	if (nFound)
	{
		// Save the available amount value in the structure
		gs_tTransactionDataStructure.bIsAvailableAmountPresent = TRUE;
		GTL_Convert_DcbNumberToUl (pAvailable, &ulTemp, 6);
		gs_tTransactionDataStructure.ulAvailableAmount = ulTemp;
	}
	else
		gs_tTransactionDataStructure.bIsAvailableAmountPresent = FALSE;
}


//! \brief Init the shared buffer exchanged with the contactless kernels.
//! \param[in] pKernelSharedBuffer Shared buffer to be initialised.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

int SDSA_Fill_InitSharedBufferWithKernels (T_SHARED_DATA_STRUCT ** pSharedBuffer)
{
	int nResult = TRUE;
	
	if (*pSharedBuffer == NULL)
		*pSharedBuffer = GTL_SharedExchange_InitShared(C_SHARED_KERNEL_BUFFER_SIZE);
	else
		GTL_SharedExchange_ClearEx(*pSharedBuffer, FALSE);
	
	if (*pSharedBuffer == NULL)
	{
		GTL_Traces_TraceDebug("SDSA_Fill_InitSharedBufferWithKernels : Init failed");
		nResult = FALSE;
	}
	
	return (nResult);
}



//! \brief Fill output buffer with data for _give_info use.
//! \param[out] Output TLV Tree filled with all the necessary data for Application Selection and card detection.
//! \param[in] pParamTlvTree TLV Tree containing all the parameters (supported AIDs, etc).
//! \param[in] bExplicitSelection \a TRUE if Explicit Selection is used. \a FALSE if Implicit Selection is used.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

int SDSA_Fill_GetApplicationSelectionParameters (TLV_TREE_NODE * pOuputTlvTree, TLV_TREE_NODE * pParamTlvTree, const unsigned int bExplicitSelection)
{
	int nResult = TRUE;
	TLV_TREE_NODE pTlvTmp; 		// Temporary Node
	TLV_TREE_NODE pTlvAidParam; // Temporary Node
	TLV_TREE_NODE pTlvAidInfo; 	// Temporary Node
	int nNbAid, nIndex;
	unsigned char ucTempBuffer[4];
	unsigned char * ucPtrAID;
	int nLenAID;
	unsigned short usTempKernelToUse;
	unsigned long ulNoCardTimeOut = 0; // No Card timeout (in milliseconds)

	
	if ((pOuputTlvTree == NULL) || (pParamTlvTree == NULL))
	{
		GTL_Traces_TraceDebug("SDSA_Fill_GetApplicationSelectionParameters : Invalid Input data");
		nResult = FALSE;
		goto End;
	}

	// Detection type (0x9F928210, on 4 bytes).
	pTlvTmp = TlvTree_Find(*pParamTlvTree, TAG_GENERIC_DETECTION_TYPE, 0);
	if (pTlvTmp != 0)
	{
		// Add tag in AID parameters set
		TlvTree_AddChild(*pOuputTlvTree, TAG_GENERIC_DETECTION_TYPE, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
	}

	// Number of cards to be detected (0x9F928214, on 1 byte).
	pTlvTmp = TlvTree_Find(*pParamTlvTree, TAG_GENERIC_DETECTION_NB_CARDS_TO_DETECT, 0);
	if (pTlvTmp != 0)
	{
		// Add tag in AID parameters set
		TlvTree_AddChild(*pOuputTlvTree, TAG_GENERIC_DETECTION_NB_CARDS_TO_DETECT, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
	}

	// Global detection timeout, if necessary (0x9F928212, on 4 bytes) (in explicit selection only).
	if (bExplicitSelection)
	{
		if(SDSA_VisaWave_IsVisaAsiaGuiMode() && SDSA_VisaWave_GetNoCardTimeOut(&ulNoCardTimeOut))
		{
			GTL_Convert_UlToBinNumber(ulNoCardTimeOut/10, ucTempBuffer, sizeof(ucTempBuffer));
			// Add tag in AID parameters set
			TlvTree_AddChild (*pOuputTlvTree, TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT, ucTempBuffer, sizeof(ucTempBuffer));
		}
		else if (SDSA_Interac_IsInteracGuiMode() && SDSA_Interac_GetNoCardTimeOut(&ulNoCardTimeOut))
		{
			GTL_Convert_UlToBinNumber(ulNoCardTimeOut/10, ucTempBuffer, sizeof(ucTempBuffer));
			// Add tag in AID parameters set
			TlvTree_AddChild (*pOuputTlvTree, TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT, ucTempBuffer, sizeof(ucTempBuffer));
		}
		else
		{
			pTlvTmp = TlvTree_Find(*pParamTlvTree, TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT, 0);
			if (pTlvTmp != 0)
			{
				// Add tag in AID parameters set
				TlvTree_AddChild (*pOuputTlvTree, TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
			}
		}
	}
	
	// DETECTION - GUI mode. (0x9F928230, on 1 byte).
	pTlvTmp = TlvTree_Find(*pParamTlvTree, TAG_GENERIC_GUI_MODE, 0);
	if (pTlvTmp != 0)
	{
		// Add tag in AID parameters set
		TlvTree_AddChild(*pOuputTlvTree, TAG_GENERIC_GUI_MODE, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
	}
	
	// For each supported AID, 
	nNbAid = SDSA_Parameters_GiveAIDNumber();
	
	for (nIndex=0; nIndex<nNbAid; nIndex++)
	{
		pTlvAidParam = SDSA_Parameters_GiveAIDTLVTtree(nIndex);
		
		// Pointer on AID information nodes
		pTlvAidInfo = TlvTree_AddChild(*pOuputTlvTree, TAG_EP_AID_INFORMATION, NULL, 0);

		// TAG_AID_TERMINAL : 0x9F06
		ucPtrAID = SDSA_Parameters_GiveAID(nIndex, &nLenAID);
		if (ucPtrAID != 0)
		{
			TlvTree_AddChild(pTlvAidInfo, TAG_EMV_AID_TERMINAL, ucPtrAID, nLenAID);
		}

		// TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER : 0x9F928202 (corresponds to the index for quick search after application selection)
		GTL_Convert_UlToBinNumber((unsigned long)nIndex, ucTempBuffer, sizeof(nIndex));
		TlvTree_AddChild(pTlvAidInfo, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, ucTempBuffer, sizeof(ucTempBuffer));
		
		// TAG_EP_KERNEL_TO_USE : 0x9F928101
		usTempKernelToUse = DEFAULT_EP_KERNEL_UNKNOWN;
		pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_KERNEL_TO_USE, 0);
		if (pTlvTmp != 0)
		{
			TlvTree_AddChild(pTlvAidInfo, TAG_EP_KERNEL_TO_USE, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
			usTempKernelToUse = (((unsigned char *)TlvTree_GetData(pTlvTmp))[0] << 8) + ((unsigned char *)TlvTree_GetData(pTlvTmp))[1];
		}
		
		// TAG_EP_AID_OPTIONS : 0x9F928100
		pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_AID_OPTIONS, 0);
		if (pTlvTmp != 0)
		{
			unsigned char auc_AIDOptions[4];
			memcpy (auc_AIDOptions, TlvTree_GetData(pTlvTmp), 4);
			if (usTempKernelToUse == DEFAULT_EP_KERNEL_VISA)
			{
				// Add information  : OPTION ZERO AMOUNT ALLOWED = TRUE
				auc_AIDOptions[0] |= 0x04; 
			}
			
			TlvTree_AddChild(pTlvAidInfo, TAG_EP_AID_OPTIONS, auc_AIDOptions, TlvTree_GetLength(pTlvTmp));
		}

		if (usTempKernelToUse != DEFAULT_EP_KERNEL_VISA)
		{
			// TAG_EP_CLESS_TRANSACTION_LIMIT : 0x9F92810D
			pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_CLESS_TRANSACTION_LIMIT, 0);
			if (pTlvTmp != 0)
				TlvTree_AddChild(pTlvAidInfo, TAG_EP_CLESS_TRANSACTION_LIMIT, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
		}
		
		// TAG_EP_CLESS_CVM_REQUIRED_LIMIT : 0x9F92810E
		pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_CLESS_CVM_REQUIRED_LIMIT, 0);
		if (pTlvTmp != 0)
			TlvTree_AddChild(pTlvAidInfo, TAG_EP_CLESS_CVM_REQUIRED_LIMIT, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
		
		// TAG_EP_CLESS_FLOOR_LIMIT : 0x9F92810F
		pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_CLESS_FLOOR_LIMIT, 0);
		if (pTlvTmp != 0)
			TlvTree_AddChild(pTlvAidInfo, TAG_EP_CLESS_FLOOR_LIMIT, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
		
		// TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS : 0x9F66
		pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS, 0);
		if (pTlvTmp != 0)
			TlvTree_AddChild(pTlvAidInfo, TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
		
		// TAG_TERMINAL_FLOOR_LIMIT : 0x9F1B
		pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_TERMINAL_FLOOR_LIMIT, 0);
		if (pTlvTmp != 0)
			TlvTree_AddChild(pTlvAidInfo, TAG_TERMINAL_FLOOR_LIMIT, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
	}

End:
	return (nResult);
}
	


//! \brief Initialise the shared exchange buffer to be used with the kernel.
//! \param[out] pDataStruct Shared exchange structure filled with the generic transaction data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

int SDSA_Fill_TransactionGenericData (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int nResult, cr;
	unsigned char ucTempBuffer[6];
	
	if (pDataStruct == NULL)
	{
		GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Invalid Input data");
		nResult = FALSE;
		goto End;
	}
	
	// Init local data
	nResult = TRUE;
	
	// Add the transaction date
	cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_TRANSACTION_DATE, 3, gs_tTransactionDataStructure.ucTransactionDate);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_DATE in the shared buffer");
		nResult = FALSE;
		goto End;
	}

	// Add the transaction time
	cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_TRANSACTION_TIME, 3, gs_tTransactionDataStructure.ucTransactionTime);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_TIME in the shared buffer");
		nResult = FALSE;
		goto End;
	}
	
	// Add the amount and the currency code (if present)
	if (gs_tTransactionDataStructure.bIsAmountPresent)
	{
		memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
		GTL_Convert_UlToBinNumber(gs_tTransactionDataStructure.ulTransactionAmountBin, ucTempBuffer, 4);
		
		// Add the transaction amount binary
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_AUTH_BIN, 4, ucTempBuffer);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_AUTH_BIN in the shared buffer");
			nResult = FALSE;
			goto End;
		}

		memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
		GTL_Convert_UlToDcbNumber(gs_tTransactionDataStructure.ulTransactionAmountBin, ucTempBuffer, 6);
		
		// Add the transaction amount binary
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_AUTH_NUM, 6, ucTempBuffer);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_AUTH_NUM in the shared buffer");
			nResult = FALSE;
			goto End;
		}
		
		memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
		GTL_Convert_UlToBinNumber(gs_tTransactionDataStructure.ulTransactionAmountOtherBin, ucTempBuffer, 4);

		// Add the transaction other binary
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_OTHER_BIN, 4, ucTempBuffer);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_OTHER_BIN in the shared buffer");
			nResult = FALSE;
			goto End;
		}
		
		memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
		GTL_Convert_UlToDcbNumber(gs_tTransactionDataStructure.ulTransactionAmountOtherBin, ucTempBuffer, 6);

		// Add the transaction other binary
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_OTHER_NUM, 6, ucTempBuffer);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_OTHER_NUM in the shared buffer");
			nResult = FALSE;
			goto End;
		}
		
		// Add the currency code
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_CODE, 2, gs_tTransactionDataStructure.ucTransactionCurrencyCode);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_CURRENCY_CODE in the shared buffer");
			nResult = FALSE;
			goto End;
		}
		
		// Add the currency exponent
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_EXPONENT, 1, &gs_tTransactionDataStructure.ucTransactionCurrencyExponent);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_CURRENCY_EXPONENT in the shared buffer");
			nResult = FALSE;
			goto End;
		}
	}
	
	// Add the internal transaction type
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_INT_TRANSACTION_TYPE, 1, &(gs_tTransactionDataStructure.ucTransactionType));
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_INT_TRANSACTION_TYPE in the shared buffer");
		nResult = FALSE;
		goto End;
	}
	
	// Add the standard transaction type
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_TRANSACTION_TYPE, 1, &(gs_tTransactionDataStructure.ucTransactionType));
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_INT_TRANSACTION_TYPE in the shared buffer");
		nResult = FALSE;
		goto End;
	}

	// Add the IFD serial number
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_IFD_SERIAL_NUMBER, sizeof(gs_tTransactionDataStructure.ucIfdSerialNumber), gs_tTransactionDataStructure.ucIfdSerialNumber);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_IFD_SERIAL_NUMBER in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}

	// Add the Transaction Sequence Counter
	memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
	GTL_Convert_UlToBinNumber(gs_ulTransactionSeqCounter, ucTempBuffer, 4);
		
	cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_TRANSACTION_SEQUENCE_COUNTER, 4, ucTempBuffer);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_SEQUENCE_COUNTER in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}

	// VisaWave specific: add the PAN that performed the last transaction
	if(gs_nLastTransactionPANLength > 0)
	{
		cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_VISAWAVE_LAST_TRANSACTION_PAN, gs_nLastTransactionPANLength, gs_ucLastTransactionPAN);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("SDSA_Fill_TransactionGenericData : Unable to add TAG_VISAWAVE_LAST_TRANSACTION_PAN in shared buffer (cr=%02x)", cr);
			nResult = FALSE;
			goto End;
		}
	}

End:
	return (nResult); 
}


//! \brief Finds the Application Program Identifier in parameters given by Entry Point.
//! \param[in] pSharedStruct Shared buffer containing the application selection results.
//! \param[out] pReadValueAPI pointer of pointer on TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER data.
//! \param[out] pulReadLengthAPI pointer on TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER field length.
//! \return
//!		- \ref TRUE if TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER tag has been founded.
//!		- \ref FALSE else.

static unsigned int __SDSA_Fill_FoundApplicationProgramId(T_SHARED_DATA_STRUCT * pSharedStruct, unsigned char **pReadValueAPI, unsigned long * pulReadLengthAPI)
{
	unsigned int nResult = FALSE; // Default value : Application Program Identifier not found
	int cr;
	int nPosition;
	int nReadBytes = 0;
	unsigned long ulFinalSelectResponseLength;
	const unsigned char *pReadValue;
	BER_TLV_TAG ReadTag;
	BER_TLV_LENGTH ReadLength;
	BER_TLV_VALUE ReadValue;

	// Parameter initialisation :
	*pReadValueAPI = NULL;
	*pulReadLengthAPI = 0;

	// Look for the Final Select Response (card) coming from Entry Point tag TAG_EP_FINAL_SELECT_RESPONSE : 0x9F928108
	nPosition = SHARED_EXCHANGE_POSITION_NULL;

	// Loop on each candidate element
	cr = GTL_SharedExchange_FindNext (pSharedStruct, &nPosition, TAG_EP_FINAL_SELECT_RESPONSE, &ulFinalSelectResponseLength, &pReadValue);
	if (cr == STATUS_SHARED_EXCHANGE_OK) // If tag founded
	{
		// in the Final Select Response (card) look for the Application Program Id sent by card Tag TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER 0x9F5A 
		T_BER_TLV_DECODE_STRUCT tDecodeStruct;
		
		// Extract the FCI template from the card answer
		GTL_BerTlvDecode_Init (&tDecodeStruct, pReadValue, ulFinalSelectResponseLength);

		// Check there is only the FCI template available and there is no padding outside the template
		cr = GTL_BerTlvDecode_ParseTlv (&tDecodeStruct, &ReadTag, &ReadLength, &ReadValue, FALSE, &nReadBytes);
		if ((cr == STATUS_BER_TLV_OK) && ((unsigned int)nReadBytes == ulFinalSelectResponseLength) && (ReadTag == TAG_EMV_FCI_TEMPLATE))
		{
			// FCI template is ok
			T_BER_TLV_DECODE_STRUCT tDecodeStructFci;
			
			// Now, parse the FCI template
			GTL_BerTlvDecode_Init (&tDecodeStructFci, ReadValue, ReadLength);
			
			for (;;)
			{
				// Get the next element in the FCI template
				cr = GTL_BerTlvDecode_ParseTlv (&tDecodeStructFci, &ReadTag, &ReadLength, &ReadValue, TRUE, NULL);
				
				// If parsing is terminated (end of buffer)
				if (cr != STATUS_BER_TLV_OK)
					break;

				// !!! Warning : tag A5 can be present but with length set to 0 !!! (see table 2.24 page 15)
				if (ReadTag == TAG_EMV_FCI_PROPRIETARY_TEMPLATE)
				{
					// Now, parse the FCI template
					GTL_BerTlvDecode_Init (&tDecodeStruct, ReadValue, ReadLength);

					for (;;)
					{
						// Get the next element in the FCI template
						cr = GTL_BerTlvDecode_ParseTlv (&tDecodeStruct, &ReadTag, &ReadLength, &ReadValue, TRUE, NULL);
						
						// If parsing is terminated (end of buffer)
						if (cr != STATUS_BER_TLV_OK)
							break;

						if (ReadTag == TAG_EMV_FCI_ISSUER_DISCRET_DATA)
						{
							T_BER_TLV_DECODE_STRUCT tDecodeStructFciDiscret;

							// Now, parse the FCI discret data
							GTL_BerTlvDecode_Init (&tDecodeStructFciDiscret, ReadValue, ReadLength);

							for (;;)
							{
								// Get the next element in the FCI template
								cr = GTL_BerTlvDecode_ParseTlv (&tDecodeStructFciDiscret, &ReadTag, &ReadLength, &ReadValue, TRUE, NULL);

								// If parsing is terminated (end of buffer)
								if (cr != STATUS_BER_TLV_OK)
									break;

								if (ReadTag == TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER)
								{
									// Tag informations memorization
									// Parameter initialization :
									*pReadValueAPI = (unsigned char *)ReadValue;
									*pulReadLengthAPI = ReadLength;
									nResult = TRUE; // Application Program Identifier found
									break;
								}
							}
							break;
						}
					}
					break;
				}
			}
		}
	}
	
	return (nResult);
}


//! \brief When the ENTRY POINT process give several Element in the Candidate List (several AID which are matching with card application),
//!  this function select the Candidate Element matching witch have a Application Program Identifier in relationship with a Parameter Set.
//! \param[in] pSharedStruct Shared buffer returned by ENTRY POINT and containing the Candidate List.
//! \param[out] pKernelDataStruct Shared buffer to be filled with the correct AID parameters (depending on the Application Selection results).
//! \return
//!		- \ref TRUE if a Candidate Element has been selected.
//!		- \ref FALSE else.

static unsigned int __SDSA_Fill_SelectCandidateElement (T_SHARED_DATA_STRUCT * pSharedStruct, unsigned char ** pReadValueSelected, unsigned long * pulReadLengthSelected)
{
	unsigned char bParameterSetFounded = FALSE;			// This boolean says that the parameter set has been founded for this AID
	unsigned char bPartialParameterSetFounded = FALSE;	// This boolean says that the parameter set has been founded for the partial AID
	unsigned char bDefaultParameterSetFounded = FALSE;	// This boolean says that the default parameter set has been founded for this AID
	unsigned int nPartialParameterAIDLength = 0;
	unsigned int nResult = FALSE;
	int cr, cr2;
	int nPosition, nPositionElement, nNbNecessaryData;
	int nAidIndex = 0xff;
	unsigned long ulReadLength, ulReadLengthElement;
	const unsigned char *pReadValue, *pReadValueElement;
	unsigned char *pReadValueCardAPI;
	unsigned long ulReadLengthCardAPI;
	T_SHARED_DATA_STRUCT SubSharedExchange;
	T_SHARED_DATA_STRUCT * pAidParameters = NULL;
	int nKernelToUse;

	if (pSharedStruct == NULL)
	{
		GTL_Traces_TraceDebug("__SDSA_Fill_SelectCandidateElement : Invalid Input data");
		goto End;
	}

	*pReadValueSelected = NULL;
	*pulReadLengthSelected = 0;

	// Look for the Final Select Response (card) coming from Entry Point tag TAG_EP_FINAL_SELECT_RESPONSE : 0x9F928108
	nPosition = SHARED_EXCHANGE_POSITION_NULL;

	// If an Application Program Id has been found in data sent by card in the final select response
	if (__SDSA_Fill_FoundApplicationProgramId(pSharedStruct, &pReadValueCardAPI, &ulReadLengthCardAPI))

    {
        unsigned int index;
        char StrTmp[100];
            
        memset(StrTmp, sizeof(StrTmp), 0);
        for (index=0; index<ulReadLengthCardAPI; index++)
        {
            char ucLocalStr[5];
            
            sprintf(ucLocalStr, " %2x", pReadValueCardAPI[index]);
            strcat(StrTmp, ucLocalStr);
        }
        GTL_Traces_TraceDebug("CardPI : %s ", StrTmp);
    }
    else
        GTL_Traces_TraceDebug("No CardPI");

	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	nNbNecessaryData = 0;

	do {
		// Loop on each candidate element given by ENTRY POINT process
		cr = GTL_SharedExchange_FindNext (pSharedStruct, &nPosition, TAG_EP_CANDIDATE_LIST_ELEMENT, &ulReadLength, &pReadValue);

		// Here, only a candidate element is checked. But it could be possible to have several candidate element at the same time.
	    if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations not found
	        break; // Stop the loop

    	// Initialize buffer allowing to look for information in
		if (GTL_SharedExchange_InitEx(&SubSharedExchange, ulReadLength, ulReadLength, (unsigned char *)pReadValue) != STATUS_SHARED_EXCHANGE_OK)
	    	continue; // An error occurs, we cannot take this CandidateListElement, we try to take next

		//Extract TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER from CandidateListElement
	    nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
		cr2 = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionElement, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, &ulReadLengthElement, &pReadValueElement);
	    if (cr2 != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations not found
	        continue;

    	// Found witch parameter set we have to look for
    	nAidIndex = pReadValueElement[3] + (pReadValueElement[2] << 8) + (pReadValueElement[1] << 16) + (pReadValueElement[0] << 24);
    	
    	// Look if parameters nAidIndex have the Application cryptogram Identifier
    	pAidParameters = SDSA_Parameters_GiveAIDShareBuffer(nAidIndex);

    	// If parameter set has not been found
    	if (pAidParameters == NULL)
    	    continue;

        // Check if transactionType is the same or is absent from the DRL
    	nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
		cr2 = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_EMV_INT_TRANSACTION_TYPE, &ulReadLengthElement, &pReadValueElement);
	    if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If TAG_EMV_TRANSACTION_TYPE found in this parameter set
	    {
	        // If Transaction Type founded, it may be the same as the inputed
	        if (SDSA_Fill_GiveTransactionType() != pReadValueElement[0])
                continue;	        	        
	    }

        // Check if transactionCashBack is the same or is absent from the DRL
    	nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
		cr2 = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_SDSA_TRANSACTION_CASHBACK, &ulReadLengthElement, &pReadValueElement);
		
	    if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If TAG_SDSA_TRANSACTION_CASHBACK found in this parameter set
	    {
	        // If Transaction Type founded, it may be the same as the inputed
	        if (gs_ucTransactionCashBack != pReadValueElement[0])
                continue;	        	        
	    }
		
		// Get the kernel to use
		nKernelToUse = DEFAULT_EP_KERNEL_UNKNOWN;
		nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
		cr2 = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_EP_KERNEL_TO_USE, &ulReadLengthElement, &pReadValueElement);
		if (cr2 == STATUS_SHARED_EXCHANGE_OK)
			nKernelToUse = (pReadValueElement[0] << 8) + (pReadValueElement[1]);

		// Look for the Program Application Identifier in the Aid Parameters
		cr2 = STATUS_SHARED_EXCHANGE_END;
		if (nKernelToUse == DEFAULT_EP_KERNEL_VISA)
	    {
			nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
			cr2 = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER, &ulReadLengthElement, &pReadValueElement);
		}
		if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER found in this parameter set
        {
	    	// Check if the Application Application Program Identifier match with the card information
	    	if (ulReadLengthCardAPI == ulReadLengthElement)
	    	{
	    		if (memcmp(pReadValueCardAPI, pReadValueElement, ulReadLengthElement) == 0) // If Application Program Identifier match
	    		{
	    			// Memorise candidate element informations : address and length
    	    		*pulReadLengthSelected = ulReadLength;
    	    		*pReadValueSelected = (unsigned char *)pReadValue;
    	    		bParameterSetFounded = TRUE;	// The specific parameter set has been founded for this AID
    	    		break; // We can stop the loop
	    		}
	    	}
	    	else if ((ulReadLengthCardAPI > ulReadLengthElement) & 		// If card PID length longer than parameters PID length
	    			(ulReadLengthElement > nPartialParameterAIDLength))	// and parameters PID length greater than the previous partial length
	    	{
	    		if (memcmp(pReadValueCardAPI, pReadValueElement, ulReadLengthElement) == 0) // If a partial Application Program Identifier match
	    		{
	    			// Memorise candidate element informations : address and length
	    			nPartialParameterAIDLength = ulReadLengthElement; // Memorize parameter PID length (longest must be taken)
    	    		*pulReadLengthSelected = ulReadLength; 
    	    		*pReadValueSelected = (unsigned char *)pReadValue;
    	    		bPartialParameterSetFounded = TRUE;	// The specific parameter set has been founded for this AID
	    		}
	    	}
	    	else if (ulReadLengthCardAPI < ulReadLengthElement)
	    	{
	    		// No treatment here
	    	}
        }
	    else if (cr2 == STATUS_SHARED_EXCHANGE_END) // If TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER not found in this parameter set or 5F2A has been found outwith visa processing and no error has happened 
	    {											
	    	// we will take this parameter set as the default one
	    	
	    	// if Default parameter set has been founded => memorized it if a partial PID parameter set has not be founded
	    	if ((bDefaultParameterSetFounded == FALSE) && (bPartialParameterSetFounded == FALSE))
	    	{
	    		*pulReadLengthSelected = ulReadLength; 
	    		*pReadValueSelected = (unsigned char *)pReadValue;
    			bDefaultParameterSetFounded = TRUE;	// The default parameter set has been founded for this AID

	    		if (ulReadLengthCardAPI == 0) // If no Application Program Identifier has been given by card
	    			// We can take it and stop research
	    			break; // Jump outside the while loop
	    	}
    	}
	}while ((cr == STATUS_SHARED_EXCHANGE_OK) && (bParameterSetFounded == FALSE)); // We can stop immediately if a Parameter Set PID matches exactly

	// We have to check if TAG_EP_CANDIDATE_LIST_ELEMENT is the good one
	// Several TAG_EP_CANDIDATE_LIST_ELEMENT tags may be returned (with AID and parameters who match with transaction and card caracteristics)
	
	// If default or parameter set has been founded
	if (bDefaultParameterSetFounded || bPartialParameterSetFounded || bParameterSetFounded)
	{
		nResult = TRUE; 
	}

End:
	return (nResult);
}


//! \brief Get the correct AID parameters (to perform the transaction) according to the application selection result.
//! \param[out] pKernelDataStruct Shared buffer to be filled with the correct AID parameters (depending on the Application Selection results).
//! \param[in] pSharedStruct Shared buffer containing the application selection results.
//! \param[out] pKernelToUse Indicates the kernel to be used for the transaction.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int SDSA_Fill_AidRelatedData (T_SHARED_DATA_STRUCT * pKernelDataStruct, T_SHARED_DATA_STRUCT * pSharedStruct, int * pKernelToUse)
{
	int nResult = TRUE;
	int cr, cr2;
	int nPosition, nPositionElement, nNbNecessaryData = 0;
	int nAidIndex = 0xff;
	unsigned int nCandidateElementFound;
	unsigned long ulReadTag;
	unsigned long ulReadLength, ulReadLengthElement;
	const unsigned char *pReadValue, *pReadValueElement;
	T_SHARED_DATA_STRUCT SubSharedExchange;
	T_SHARED_DATA_STRUCT * pAidParameters = NULL;
	T_SHARED_DATA_STRUCT * pTmpAidParameters = NULL;
	unsigned char * pCardAid;
	unsigned int  nCardAidLength;

	if ((*pKernelToUse) != NULL)
		*pKernelToUse = DEFAULT_EP_KERNEL_UNKNOWN;
	
	if ((pSharedStruct == NULL) || (pKernelDataStruct == NULL))
	{
		GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : Invalid Input data");
		nResult = FALSE;
		goto End;
	}

	// Find the good Candidate Element in the Candidate List sent by EntryPoint
	nCandidateElementFound = __SDSA_Fill_SelectCandidateElement (pSharedStruct, (unsigned char **)&pReadValue, &ulReadLength);
	
	// Here, only the first candidate element is checked. But it could be possible to have several candidate element at the same time.
    if (nCandidateElementFound) // If tag with AID informations found
    {
		if (GTL_SharedExchange_InitEx(&SubSharedExchange, ulReadLength, ulReadLength, (unsigned char *)pReadValue) != STATUS_SHARED_EXCHANGE_OK)
		{
	    	GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : GTL_SharedExchange_InitEx error");
	    	nResult = FALSE;
	    	goto End;
		}
    	
		nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
		cr2 = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionElement, TAG_EP_KERNEL_TO_USE, &ulReadLengthElement, &pReadValueElement);
	    if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
        {
        	nNbNecessaryData ++; // One information has been founded on two bytes
        	*pKernelToUse = pReadValueElement[1] + (pReadValueElement[0] << 8);
        }
	    
	    nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
		cr2 = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionElement, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, &ulReadLengthElement, &pReadValueElement);
	    if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
        {
	    	nNbNecessaryData ++; // One information has been founded
        	nAidIndex = pReadValueElement[3] + (pReadValueElement[2] << 8) + (pReadValueElement[1] << 16) + (pReadValueElement[0] << 24);
        }

	    nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
		cr2 = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionElement, TAG_EMV_AID_CARD, &ulReadLengthElement, &pReadValueElement);
	    if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
        {
	    	nNbNecessaryData ++; // One information has been founded
        	pCardAid = (unsigned char*)pReadValueElement;
        	nCardAidLength = ulReadLengthElement;
        }
	    else
	    {
	    	nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
    		cr2 = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionElement, TAG_EMV_DF_NAME, &ulReadLengthElement, &pReadValueElement);
    	    if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
	        {
    	    	nNbNecessaryData ++; // One information has been founded
	        	pCardAid = (unsigned char*)pReadValueElement;
	        	nCardAidLength = ulReadLengthElement;
	        }
	    }
    }
    else // Buffer end reached
    {
    	GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : GTL_SharedExchange_FindNext End");
    	nResult = FALSE;
    	goto End;
    }
	
	// All the information to retrieve the AID have been found
	if (nNbNecessaryData != 3) // AID informations (KERNEL TO USE and AID PROPRIETARY IDENTIFIER) not found !
	{
    	GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : Missing information to retrieve the AID\n");
    	nResult = FALSE;
    	goto End;
	}
	
	// Add parameters given to the AID's parameters
	pAidParameters = SDSA_Parameters_GiveAIDShareBuffer(nAidIndex);

	// Copy TLVTree in a temporary struct
	if (pAidParameters != NULL)
	{
		pTmpAidParameters = GTL_SharedExchange_InitShared (pAidParameters->ulMaxBufferSize);
		pTmpAidParameters->ulDataLength = pAidParameters->ulDataLength;
		memcpy(pTmpAidParameters->nPtrData, pAidParameters->nPtrData, pAidParameters->ulDataLength); 
	}
	
	
	// Call kernel in relationship with AID
	switch (*pKernelToUse)
	{
	case DEFAULT_EP_KERNEL_PAYPASS :
		// No specific action to made on PayPass Parameters
		// SDSA_PayPass_AidRelatedData(pSharedStruct, pAidParameters);
		break;
		
	case DEFAULT_EP_KERNEL_VISA :
		// Warning, some parameters must be modified before to be taken for the Aid
		// Intermediate struct is needed because it can be modified
		if(SDSA_VisaWave_isVisaWaveProcessing())
			SDSA_VisaWave_AidRelatedData(&SubSharedExchange, pTmpAidParameters);
		else
			SDSA_payWave_AidRelatedData(&SubSharedExchange, pTmpAidParameters);
		break;
		
	case DEFAULT_EP_KERNEL_AMEX :
		// SDSA_ExpressPay_AidRelatedData(pTmpAidParameters);
		break;
	
	default:
		break;
	}
	
	if (pTmpAidParameters != NULL)
	{
		// Copy AIDs' parameters in final Share Buffer
		if (GTL_SharedExchange_AddSharedBufferContent (pKernelDataStruct, pTmpAidParameters) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : GTL_SharedExchange_AddSharedBufferContent failed\n");
			GTL_SharedExchange_ClearEx (pKernelDataStruct, FALSE);
			nResult = FALSE;
			goto End;
		}
		GTL_SharedExchange_DestroyShare(pTmpAidParameters);
	}
	else
	{
		GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : Unable to get the AID shared buffer");
		nResult = FALSE;
		goto End; // No treatment to realize !!
	}
	
	// Add some of the candidate element tags in the output kernel shared buffer
	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
	cr2 = STATUS_SHARED_EXCHANGE_OK;
	
	while (cr2 == STATUS_SHARED_EXCHANGE_OK)
	{
		cr2 = GTL_SharedExchange_GetNext(&SubSharedExchange, &nPositionElement, &ulReadTag, &ulReadLengthElement, &pReadValueElement);
		
		if (cr2 == STATUS_SHARED_EXCHANGE_OK)
		{
			switch (ulReadTag)
			{
			case (TAG_EP_AID_ADDITIONAL_RESULTS):
			case (TAG_EMV_AID_TERMINAL):
			case (TAG_EP_CLESS_APPLI_CAPABILITY_TYPE):
//			case (TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS):
			case (TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER):
				cr2 = GTL_SharedExchange_AddTag(pKernelDataStruct, ulReadTag, ulReadLengthElement, pReadValueElement);
				if (cr2 != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : An error occurred when adding the AID element (provided by application selection) in the shared buffer (ulTag = %02lx, cr = %02x)", ulReadTag, cr2);
			    	GTL_SharedExchange_ClearEx (pKernelDataStruct, FALSE);
			    	nResult = FALSE;
			    	goto End;
				}
				break;
			
			default:
				break;
			}
		}
	}
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pSharedStruct, &nPosition, TAG_EP_FINAL_SELECT_STATUS_WORD, &ulReadLength, &pReadValue);
	if (cr == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
    {
    	// Parameters add in final struct
    	cr2 = GTL_SharedExchange_AddTag (pKernelDataStruct, TAG_EP_FINAL_SELECT_STATUS_WORD, ulReadLength, pReadValue);
    	if (cr2 != STATUS_SHARED_EXCHANGE_OK)
    	{
        	GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : GTL_SharedExchange_AddTag error (cr=%02x)", cr2);
        	GTL_SharedExchange_ClearEx (pKernelDataStruct, FALSE);
        	nResult = FALSE;
        	goto End;
    	}
    }
    else
    {
    	GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : TAG_EP_FINAL_SELECT_STATUS_WORD not found in cless_debit_aid()");
    	GTL_SharedExchange_ClearEx (pKernelDataStruct, FALSE);
    	nResult = FALSE;
    	goto End;
    }

	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pSharedStruct, &nPosition, TAG_EP_FINAL_SELECT_RESPONSE, &ulReadLength, &pReadValue);
	if (cr == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
    {
    	// Parameters add in final struct
    	cr2 = GTL_SharedExchange_AddTag (pKernelDataStruct, TAG_EP_FINAL_SELECT_RESPONSE, ulReadLength, pReadValue);
    	if (cr2 != STATUS_SHARED_EXCHANGE_OK)
    	{
        	GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : GTL_SharedExchange_AddTag error (cr=%02x)", cr2);
        	GTL_SharedExchange_ClearEx (pKernelDataStruct, FALSE);
        	nResult = FALSE;
        	goto End;
    	}
    }
    else
    {
    	// No error management, a card error on final select give a cless_debit_aid_() shared buffer without TAG_EP_FINAL_SELECT_RESPONSE tag
    }

	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pSharedStruct, &nPosition, TAG_EP_FINAL_SELECT_COMMAND_SENT, &ulReadLength, &pReadValue);
	if (cr == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
    {
    	// Parameters add in final struct
    	cr2 = GTL_SharedExchange_AddTag (pKernelDataStruct, TAG_EP_FINAL_SELECT_COMMAND_SENT, ulReadLength, pReadValue);
    	if (cr2 != STATUS_SHARED_EXCHANGE_OK)
    	{
        	GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : GTL_SharedExchange_AddTag error (cr=%02x)", cr2);
        	GTL_SharedExchange_ClearEx (pKernelDataStruct, FALSE);
        	nResult = FALSE;
        	goto End;
    	}
    }
    else
    {
    	GTL_Traces_TraceDebug("SDSA_Fill_AidRelatedData : TAG_EP_FINAL_SELECT_COMMAND_SENT not found in cless_debit_aid()");
    }

End:
	return (nResult);
}
