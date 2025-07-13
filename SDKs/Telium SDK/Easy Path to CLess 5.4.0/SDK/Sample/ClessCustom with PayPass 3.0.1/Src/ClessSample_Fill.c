/**
 * \file	ClessSample_Fill.c
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

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define ADD_STEP_INTERRUPTION(step,buffer)	buffer[sizeof(buffer)-1-step/8]+=1<<(step%8)	/*!< Macro to set information on buffer to stop transaction flow on a specific step */
#define ADD_STEP_CUSTOM(step,buffer) 		buffer[sizeof(buffer)-1-step/8]+=1<<(step%8)	/*!< \brief Macro to set information on buffer to custom transaction flow on a specific step. */


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global data definitions ////////////////////////////////////

T_SHARED_DATA_STRUCT * g_pKernelSharedBuffer;			/*!< Share exchange buffer used with the payment kernels. */

T_PAYMENT_DATA_STRUCT gs_tTransactionDataStructure;     /*!< Structure that contains the transaction data */


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static unsigned int __ClessSample_Fill_SelectCandidateElement (T_SHARED_DATA_STRUCT * pSharedStruct, unsigned char ** pReadValueSelected, unsigned long * pulReadLengthSelected);


/////////////////////////////////////////////////////////////////
//// Function ///////////////////////////////////////////////////

//! \brief Gives the transaction data structure.
//! \return The transaction data structure.

const T_PAYMENT_DATA_STRUCT * ClessSample_Fill_GetTransactionDataStructure (void)
{
	return (&gs_tTransactionDataStructure);
}



//! \brief Gives transaction amount.
//! \return
//!		- \a transaction amount.
//! \note This function shall be called after having loaded the parameters.

unsigned long ClessSample_Fill_GiveAmount(void)
{
	return (gs_tTransactionDataStructure.ulTransactionAmount);
}



//! \brief Indicates if there is at least one AID in the parametres related to the specified kernel.
//! \param[in] nKernelIdentifier Kernel identifier.
//! \return
//!		- \a TRUE if at least one AID is present.
//!		- \a FALSE if not.
//! \note This function shall be called after having loaded the parameters.

int ClessSample_Fill_IsThereAidWithKernel (const int nKernelIdentifier)
{
	int nResult = FALSE;
	TLV_TREE_NODE pTlvTmp; 		// Temporary Node
	TLV_TREE_NODE pTlvAidParam; // Temporary Node
	unsigned short usTempKernelToUse;
	int nNbAid, nIndex;
	
	// For each supported AID, 
	nNbAid = ClessSample_Parameters_GiveAIDNumber();
	
	for (nIndex=0; nIndex<nNbAid; nIndex++)
	{
		pTlvAidParam = ClessSample_Parameters_GiveAIDTLVTtree(nIndex);
		
		// TAG_EP_KERNEL_TO_USE : 0x9F928101
		pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_KERNEL_TO_USE, 0);
		if (pTlvTmp != 0)
		{
			usTempKernelToUse = (((unsigned char *)TlvTree_GetData(pTlvTmp))[0] << 8) + ((unsigned char *)TlvTree_GetData(pTlvTmp))[1];
			if (usTempKernelToUse == (unsigned short)nKernelIdentifier)
			{
				nResult = TRUE;
				goto End;
			}
		}
	}

End:
	return (nResult);
}



//! \brief Gives the money label.
//! \return
//!		- \a money label.
//! \note This function shall be called after having loaded the parameters.
char *ClessSample_Fill_GiveMoneyLabel(void)
{
	return (gs_tTransactionDataStructure.ucTransactionCurrencyLabel);
}



//! \brief Gives transaction type.
//! \return
//!		- \a transaction type.
//! \note This function can be called after transaction type has been populated. If the transaction type is not defined, the default one is provided (0x00).

unsigned char ClessSample_Fill_GiveTransactionType(void)
{
	if (gs_tTransactionDataStructure.bIsTransacTypePresent == SAMPLE_TAG_PRESENT)
		return (gs_tTransactionDataStructure.ucTransactionType);
	else
		return (CLESS_SAMPLE_TRANSACTION_TYPE_DEFAULT);
}



//! \brief Save the some transaction only provided on CLESS_GIVE_INFO service.
//! \param[in] bIsAmountAuthPresent Indicates if the transaction amount authorised is present or not.
//! \param[in] ulAmountAuthBin Indicates the transaction amount (binary format) to save.
//! \param[in] bIsAmountOtherPresent Indicates if the transaction amount other is present or not.
//! \param[in] ulAmountOtherBin Indicates the transaction amount other (binary format) to save.
//! \param[in] bIsCurrencyCodePresent Indicates if the transaction currency code is present or not.
//! \param[in] pCurrencyCode Indicates the transaction currency code to save (shall be coded on 2 bytes).
//! \param[in] bIsCurrencyExpPresent Indicates if the transaction currency exponent is present or not.
//! \param[in] pCurrencyExponent Indicates the transaction type to save.
//! \param[in] bIsTransacTypePresent Indicates if the transaction type is present or not.
//! \param[in] pTransactionType Indicates the transaction type to save.
//! \param[in] bUseCurrentSn \a TRUE if the current SN shall be used, \a FALSE if \a bIsSerialNumberPresent and \a pIfdSerialNumber have to be used.
//! \param[in] bIsSerialNumberPresent Indicates if the interface serial number is present or not.
//! \param[in] pCurrencyLabel Indicates the currency label to save.
//!	\param[in] bIsTxnCategoryCodePresent Indicates if the Transaction Category Code is present or not.
//!	\param[in] pTxnCategoryCode Indicates the Transaction Category Code to save.

void ClessSample_Fill_PrepareAndSaveClessGiveInfoTransactionStaticData (const unsigned char bIsAmountAuthPresent, const unsigned long ulAmountAuthBin,
															const unsigned char bIsAmountOtherPresent, const unsigned long ulAmountOtherBin,
															const unsigned char bIsCurrencyCodePresent, const unsigned char * pCurrencyCode,
															const unsigned char bIsCurrencyExpPresent, const unsigned char * pCurrencyExponent,
															const unsigned char bIsTransacTypePresent, const unsigned char * pTransactionType,
															const unsigned char bUseCurrentSn, const unsigned char bIsSerialNumPresent,
															const char * pCurrencyLabel,
															const unsigned char bIsTxnCategoryCodePresent, const unsigned char * pTxnCategoryCode)
{
	unsigned long ulTemp;
	NO_SERIE serial;

	
	// Save the transaction data in the structure

	// Save transaction Amount Authorized
	gs_tTransactionDataStructure.bIsAmountAuthPresent = bIsAmountAuthPresent;
	if(bIsAmountAuthPresent == SAMPLE_TAG_PRESENT)
		ulTemp = ulAmountAuthBin;
	else
		ulTemp = 0;
	gs_tTransactionDataStructure.ulTransactionAmount = ulTemp;


	// Save transaction Amount Other
	gs_tTransactionDataStructure.bIsAmountOtherPresent = bIsAmountOtherPresent;
	if(bIsAmountOtherPresent == SAMPLE_TAG_PRESENT)
		ulTemp = ulAmountOtherBin;
	else
		ulTemp = 0;
	gs_tTransactionDataStructure.ulTransactionAmountOther = ulTemp;


	// Save transaction currency code
	gs_tTransactionDataStructure.bIsCurrencyCodePresent = bIsCurrencyCodePresent;
	if(bIsCurrencyCodePresent == SAMPLE_TAG_PRESENT)
		memcpy (gs_tTransactionDataStructure.ucTransactionCurrencyCode, pCurrencyCode, sizeof (gs_tTransactionDataStructure.ucTransactionCurrencyCode));


	// Save transaction currency exponent
	gs_tTransactionDataStructure.bIsCurrencyExpPresent = bIsCurrencyExpPresent;
	if(bIsCurrencyExpPresent == SAMPLE_TAG_PRESENT)
		gs_tTransactionDataStructure.ucTransactionCurrencyExponent = pCurrencyExponent[0];


	// Save transaction type
	gs_tTransactionDataStructure.bIsTransacTypePresent = bIsTransacTypePresent;
	if(bIsTransacTypePresent == SAMPLE_TAG_PRESENT)	
		gs_tTransactionDataStructure.ucTransactionType = pTransactionType[0];


	// Save transaction currency label
	if(pCurrencyLabel != NULL)
		memcpy (gs_tTransactionDataStructure.ucTransactionCurrencyLabel, pCurrencyLabel, 3);


	// Get and save the IFD serial number (for future use)
	if (!bUseCurrentSn)
	{
		// Tag TAG_EMV_IFD_SERIAL_NUMBER is absent or empty
		gs_tTransactionDataStructure.bIsSerialNumberPresent = bIsSerialNumPresent;
	}
	else
	{
		// Extract SN and initialise the structure
		PSQ_Give_Serial_Number (serial);

		gs_tTransactionDataStructure.bIsSerialNumberPresent = SAMPLE_TAG_PRESENT;
		memcpy (gs_tTransactionDataStructure.ucIfdSerialNumber, serial, 8);
	}

	// Save Transaction Category Code
	gs_tTransactionDataStructure.bIsTxnCategoryCodePresent = bIsTxnCategoryCodePresent;
	if(bIsTxnCategoryCodePresent == SAMPLE_TAG_PRESENT)	
		gs_tTransactionDataStructure.ucTxnCategoryCode = pTxnCategoryCode[0];
}



//! \brief Save the some transaction only provided on CLESS_GIVE_INFO service.
//! \param[in] bUseCurrentDate if \a TRUE, the function reads the current date and set the structure. Else (\a FALSE), the function uses the provided parameters.
//! \param[in] bIsDatePresent Indicates if the transaction date is present or not.
//! \param[in] bUseCurrentTime if \a TRUE, the function reads the current time and set the structure. Else (\a FALSE), the function uses the provided parameters.
//! \param[in] bIsTimePresent Indicates if the transaction time is present or not.

void ClessSample_Fill_PrepareAndSaveClessGiveInfoTransactionDynamicData (const unsigned char bUseCurrentDate, const unsigned char bIsDatePresent,
																		 const unsigned char bUseCurrentTime, const unsigned char bIsTimePresent)
{
	DATE Date;
	unsigned char ucDate[3], ucTime[3];

	// If necessary, read the date and time
	if ((bUseCurrentDate) || (bUseCurrentTime))
	{
		if (read_date(&Date) == OK)
		{
			if (bUseCurrentDate)
			{	
				ucDate[0] = (unsigned char)(((Date.year[0] - '0') << 4) | (Date.year[1] - '0'));
				ucDate[1] = (unsigned char)(((Date.month[0] - '0') << 4) | (Date.month[1] - '0'));
				ucDate[2] = (unsigned char)(((Date.day[0] - '0') << 4) | (Date.day[1] - '0'));
			}
			if (bUseCurrentTime)
			{	
				ucTime[0] = (unsigned char)(((Date.hour[0] - '0') << 4) | (Date.hour[1] - '0'));
				ucTime[1] = (unsigned char)(((Date.minute[0] - '0') << 4) | (Date.minute[1] - '0'));
				ucTime[2] = (unsigned char)(((Date.second[0] - '0') << 4) | (Date.second[1] - '0'));
			}
		}
		else // error management
		{
			GTL_Traces_TraceDebug("__ClessSample_ExplicitSelection_PrepareDynamicTransactionData : Unable to read date and time");
			gs_tTransactionDataStructure.bIsDatePresent = SAMPLE_TAG_ABSENT;
			gs_tTransactionDataStructure.bIsTimePresent = SAMPLE_TAG_ABSENT;
			return;
		}
	}


	// Save transaction date
	if (!bUseCurrentDate)
	{
		// Tag TAG_EMV_TRANSACTION_DATE is absent or empty
		gs_tTransactionDataStructure.bIsDatePresent = bIsDatePresent;
	}
	else
	{
		gs_tTransactionDataStructure.bIsDatePresent = SAMPLE_TAG_PRESENT;
		memcpy (gs_tTransactionDataStructure.ucTransactionDate, ucDate, sizeof (ucDate));
	}
	

	// Save transaction time
	if (!bUseCurrentTime)
	{
		// Tag TAG_EMV_TRANSACTION_TIME is absent or empty
		gs_tTransactionDataStructure.bIsTimePresent = bIsTimePresent;
	}
	else
	{
		gs_tTransactionDataStructure.bIsTimePresent = SAMPLE_TAG_PRESENT;
		memcpy (gs_tTransactionDataStructure.ucTransactionTime, ucTime, sizeof (ucTime));
	}
}



//! \brief Init the shared buffre exchanged with the contactless kernels.
//! \param[in] pKernelSharedBuffer Shared exchange to be initialised.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int ClessSample_Fill_InitSharedBufferWithKernels (T_SHARED_DATA_STRUCT ** pSharedBuffer)
{
	int nResult = TRUE;
	
	if (*pSharedBuffer == NULL)
		*pSharedBuffer = GTL_SharedExchange_InitShared(C_SHARED_KERNEL_BUFFER_SIZE);
	else
		GTL_SharedExchange_ClearEx(*pSharedBuffer, FALSE);
	
	if (*pSharedBuffer == NULL)
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_InitSharedBufferWithKernels : Init failed");
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
//!		- \ref FALSE if an error occurred.

int ClessSample_Fill_GetApplicationSelectionParameters (TLV_TREE_NODE * pOuputTlvTree, TLV_TREE_NODE * pParamTlvTree, const unsigned int bExplicitSelection)
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
	unsigned char ucTransactionType, ucAidTransactionType;
	unsigned char bAddAidInfo, bAtLeastOneAid = FALSE;


	if ((pOuputTlvTree == NULL) || (pParamTlvTree == NULL))
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_GetApplicationSelectionParameters : Invalid Input data");
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
		pTlvTmp = TlvTree_Find(*pParamTlvTree, TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT, 0);
		if (pTlvTmp != 0)
		{
			// Add tag in AID parameters set
			TlvTree_AddChild (*pOuputTlvTree, TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
		}
	}
	
	// DETECTION - GUI mode. (0x9F928230, on 1 byte).
	pTlvTmp = TlvTree_Find(*pParamTlvTree, TAG_GENERIC_GUI_MODE, 0);
	if (pTlvTmp != 0)
	{
		// Add tag in AID parameters set
		TlvTree_AddChild(*pOuputTlvTree, TAG_GENERIC_GUI_MODE, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
	}


	// TPass and EntryPoint trace activation (if necessary).
    // Traces for TPass and EntryPoint	
    if (ClessSample_Menu_IsTraceActivated())
    {
       	unsigned char ucDebugMode = DEBUG_MASK_APDU + DEBUG_MASK_TRACES; // 2 + 1
		// Add tag in AID parameters set
		TlvTree_AddChild (*pOuputTlvTree, TAG_GENERIC_DEBUG_ACTIVATION, (const void *)&ucDebugMode, 1);
	}


	// For each supported AID, 
	nNbAid = ClessSample_Parameters_GiveAIDNumber();
	
	for (nIndex=0; nIndex<nNbAid; nIndex++)
	{
		pTlvAidParam = ClessSample_Parameters_GiveAIDTLVTtree(nIndex);

		bAddAidInfo = FALSE;

		// TAG_EP_KERNEL_TO_USE : 0x9F928101
		usTempKernelToUse = DEFAULT_EP_KERNEL_UNKNOWN;
		pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_KERNEL_TO_USE, 0);
		if (pTlvTmp != 0)
		{
			usTempKernelToUse = (((unsigned char *)TlvTree_GetData(pTlvTmp))[0] << 8) + ((unsigned char *)TlvTree_GetData(pTlvTmp))[1];
		}

		if (usTempKernelToUse == DEFAULT_EP_KERNEL_PAYPASS)
		{
			pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EMV_INT_TRANSACTION_TYPE, 0);
			if ((pTlvTmp != 0) && (TlvTree_GetLength(pTlvTmp) == LENGTH_OF_TRANSACTION_TYPE))
			{
				// Get the transaction type allowed for the current AID
				ucAidTransactionType = ((unsigned char *)TlvTree_GetData(pTlvTmp))[0];

				// Get the transaction type of the transaction in progress
				if(gs_tTransactionDataStructure.bIsTransacTypePresent == SAMPLE_TAG_PRESENT)
					ucTransactionType = gs_tTransactionDataStructure.ucTransactionType;
				else
				{
					ucTransactionType = 0x99; // If the default transaction type is not defined in the parameter file, 0x99 will be used as the default transaction type.
					// Get the default transaction type in the parameter file
					pTlvTmp = TlvTree_Find(*pParamTlvTree, TAG_SAMPLE_DEFAULT_TRANSACTION_TYPE, 0);
					if ((pTlvTmp != 0) && (TlvTree_GetLength(pTlvTmp) == LENGTH_OF_TRANSACTION_TYPE))
						ucTransactionType = ((unsigned char *)TlvTree_GetData(pTlvTmp))[0];
				}
		
				// If the transaction types match, the current AID will be added in the list for the application selection
				if(ucAidTransactionType == ucTransactionType)
					bAddAidInfo = TRUE;
			}
		}

		if(bAddAidInfo)
		{
			bAtLeastOneAid = TRUE;

			// Pointer on AID information nodes
			pTlvAidInfo = TlvTree_AddChild(*pOuputTlvTree, TAG_EP_AID_INFORMATION, NULL, 0);

			// TAG_AID_TERMINAL : 0x9F06
			ucPtrAID = ClessSample_Parameters_GiveAID(nIndex, &nLenAID);
			if (ucPtrAID != 0)
			{
				TlvTree_AddChild(pTlvAidInfo, TAG_EMV_AID_TERMINAL, ucPtrAID, nLenAID);
			}

			// TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER : 0x9F928202 (corresponds to the index for quick search after application selection)
			GTL_Convert_UlToBinNumber((unsigned long)nIndex, ucTempBuffer, sizeof(nIndex));
			TlvTree_AddChild(pTlvAidInfo, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, ucTempBuffer, sizeof(ucTempBuffer));

			// TAG_EP_KERNEL_TO_USE : 0x9F928101
			pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_KERNEL_TO_USE, 0);
			if (pTlvTmp != 0)
			{
				TlvTree_AddChild(pTlvAidInfo, TAG_EP_KERNEL_TO_USE, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
			}

			// TAG_EP_AID_OPTIONS : 0x9F928100
			pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_AID_OPTIONS, 0);
			if (pTlvTmp != 0)
			{
				unsigned char auc_AIDOptions[4];
				memcpy (auc_AIDOptions, TlvTree_GetData(pTlvTmp), 4);
				TlvTree_AddChild(pTlvAidInfo, TAG_EP_AID_OPTIONS, auc_AIDOptions, TlvTree_GetLength(pTlvTmp));
			}

			// TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS : 0x9F66
			pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS, 0);
			if (pTlvTmp != 0)
				TlvTree_AddChild(pTlvAidInfo, TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
		}
	}

	if(!bAtLeastOneAid)
		nResult = FALSE;	
End:
	return (nResult);
}
	


//! \brief Initialise the shared exchange buffer to be used with the kernel.
//! \param[out] pDataStruct Shared exchange structure filled with the generic transaction data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int ClessSample_Fill_TransactionGenericData (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int nResult, cr;
	unsigned char ucTempBuffer[6];

	// Check the structure is correct
	if (pDataStruct == NULL)
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Invalid Input data");
		nResult = FALSE;
		goto End;
	}

	// Init local data
	nResult = TRUE;

	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_EMV_TRANSACTION_DATE);
	// Add the transaction date
	if (gs_tTransactionDataStructure.bIsDatePresent != SAMPLE_TAG_ABSENT)
	{
		if ((gs_tTransactionDataStructure.bIsDatePresent) == SAMPLE_TAG_PRESENT)
			cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_TRANSACTION_DATE, 3, gs_tTransactionDataStructure.ucTransactionDate);
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_TRANSACTION_DATE, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_DATE in the shared buffer");
			nResult = FALSE;
			goto End;
		}
	}

	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_EMV_TRANSACTION_TIME);
	// Add the transaction time
	if (gs_tTransactionDataStructure.bIsTimePresent != SAMPLE_TAG_ABSENT)
	{
		if ((gs_tTransactionDataStructure.bIsTimePresent) == SAMPLE_TAG_PRESENT)
			cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_TRANSACTION_TIME, 3, gs_tTransactionDataStructure.ucTransactionTime);
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_TRANSACTION_TIME, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_TIME in the shared buffer");
			nResult = FALSE;
			goto End;
		}
	}

	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_EMV_AMOUNT_AUTH_BIN);
	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_EMV_AMOUNT_AUTH_NUM);
	// Add the amount (if present)
	if (gs_tTransactionDataStructure.bIsAmountAuthPresent != SAMPLE_TAG_ABSENT)
	{
		if ((gs_tTransactionDataStructure.bIsAmountAuthPresent) == SAMPLE_TAG_PRESENT)
		{

			memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
			GTL_Convert_UlToBinNumber(gs_tTransactionDataStructure.ulTransactionAmount, ucTempBuffer, 4);

			// Add the transaction amount binary
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_AUTH_BIN, 4, ucTempBuffer);
		}
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_AUTH_BIN, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_AUTH_BIN in the shared buffer");
			nResult = FALSE;
			goto End;
		}

		if ((gs_tTransactionDataStructure.bIsAmountAuthPresent) == SAMPLE_TAG_PRESENT)
		{
			memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
			GTL_Convert_UlToDcbNumber(gs_tTransactionDataStructure.ulTransactionAmount, ucTempBuffer, 6);

			// Add the transaction amount binary
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_AUTH_NUM, 6, ucTempBuffer);
		}
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_AUTH_NUM, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_AUTH_NUM in the shared buffer");
			nResult = FALSE;
			goto End;
		}
	}

	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_EMV_AMOUNT_OTHER_BIN);
	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_EMV_AMOUNT_OTHER_NUM);
	// Add the transaction other
	if (gs_tTransactionDataStructure.bIsAmountOtherPresent != SAMPLE_TAG_ABSENT)
	{
		if ((gs_tTransactionDataStructure.bIsAmountOtherPresent) == SAMPLE_TAG_PRESENT)
		{
			memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
			GTL_Convert_UlToBinNumber(gs_tTransactionDataStructure.ulTransactionAmountOther, ucTempBuffer, 4);

			// Add the transaction other binary
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_OTHER_BIN, 4, ucTempBuffer);
		}
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_OTHER_BIN, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_OTHER_BIN in the shared buffer");
			nResult = FALSE;
			goto End;
		}

		if ((gs_tTransactionDataStructure.bIsAmountOtherPresent) == SAMPLE_TAG_PRESENT)
		{
			memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
			GTL_Convert_UlToDcbNumber(gs_tTransactionDataStructure.ulTransactionAmountOther, ucTempBuffer, 6);

			// Add the transaction other num
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_OTHER_NUM, 6, ucTempBuffer);
		}
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_OTHER_NUM, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_OTHER_NUM in the shared buffer");
			nResult = FALSE;
			goto End;
		}
	}

	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_CODE);
	// Add the currency code
	if (gs_tTransactionDataStructure.bIsCurrencyCodePresent != SAMPLE_TAG_ABSENT)
	{
		if ((gs_tTransactionDataStructure.bIsCurrencyCodePresent) == SAMPLE_TAG_PRESENT)	
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_CODE, 2, gs_tTransactionDataStructure.ucTransactionCurrencyCode);
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_CODE, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_CURRENCY_CODE in the shared buffer");
			nResult = FALSE;
			goto End;
		}
	}

	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_EXPONENT);
	// Add the currency exponent
	if (gs_tTransactionDataStructure.bIsCurrencyExpPresent != SAMPLE_TAG_ABSENT)
	{
		if ((gs_tTransactionDataStructure.bIsCurrencyExpPresent) == SAMPLE_TAG_PRESENT)	
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_EXPONENT, 1, &(gs_tTransactionDataStructure.ucTransactionCurrencyExponent));
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_EXPONENT, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_CURRENCY_EXPONENT in the shared buffer");
			nResult = FALSE;
			goto End;
		}
	}

	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_EMV_INT_TRANSACTION_TYPE);
	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_EMV_TRANSACTION_TYPE);
	// Add the internal transaction type (if present)
	if (gs_tTransactionDataStructure.bIsTransacTypePresent != SAMPLE_TAG_ABSENT)
	{
		// Add the internal transaction type
		if ((gs_tTransactionDataStructure.bIsTransacTypePresent) == SAMPLE_TAG_PRESENT)	
			cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_INT_TRANSACTION_TYPE, 1, &(gs_tTransactionDataStructure.ucTransactionType));
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_INT_TRANSACTION_TYPE, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_INT_TRANSACTION_TYPE in the shared buffer");
			nResult = FALSE;
			goto End;
		}

		// Add the standard transaction type
		if ((gs_tTransactionDataStructure.bIsTransacTypePresent) == SAMPLE_TAG_PRESENT)	
			cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_TRANSACTION_TYPE, 1, &(gs_tTransactionDataStructure.ucTransactionType));
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_TRANSACTION_TYPE, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_INT_TRANSACTION_TYPE in the shared buffer");
			nResult = FALSE;
			goto End;
		}
	}

	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_EMV_IFD_SERIAL_NUMBER);
	// Add the IFD serial number (if present)
	if (gs_tTransactionDataStructure.bIsSerialNumberPresent != SAMPLE_TAG_ABSENT)
	{
		if ((gs_tTransactionDataStructure.bIsSerialNumberPresent) == SAMPLE_TAG_PRESENT)
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_IFD_SERIAL_NUMBER, sizeof(gs_tTransactionDataStructure.ucIfdSerialNumber), gs_tTransactionDataStructure.ucIfdSerialNumber);
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_IFD_SERIAL_NUMBER, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_IFD_SERIAL_NUMBER in shared buffer (cr=%02x)", cr);
			nResult = FALSE;
			goto End;
		}
	}

	GTL_SharedExchange_RemoveTag(pDataStruct, TAG_PAYPASS_TRANSACTION_CATEGORY_CODE);
	// Add the currency exponent
	if (gs_tTransactionDataStructure.bIsTxnCategoryCodePresent != SAMPLE_TAG_ABSENT)
	{
		if ((gs_tTransactionDataStructure.bIsTxnCategoryCodePresent) == SAMPLE_TAG_PRESENT)	
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_PAYPASS_TRANSACTION_CATEGORY_CODE, 1, &(gs_tTransactionDataStructure.ucTxnCategoryCode));
		else // The tag is empty (SAMPLE_TAG_EMPTY)
			cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_PAYPASS_TRANSACTION_CATEGORY_CODE, 0, NULL);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_PAYPASS_TRANSACTION_CATEGORY_CODE in the shared buffer");
			nResult = FALSE;
			goto End;
		}
	}

	// Add the transaction sequence counter
	if (!ClessSample_Batch_AddTscToSharedBuffer(pDataStruct))
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : ClessSample_Batch_AddTscToSharedBuffer failed");
		nResult = FALSE;
		goto End;
	}

End:
	return (nResult); 
}



//! \brief When the ENTRY POINT process give several Element in the Candidate List (several AID which are matching with card application),
//!  this function select the Candidate Element matching witch have a Application Program Identifier in relationship with a Parameter Set.
//! \param[in] pSharedStruct Shared buffer returned by ENTRY POINT and containing the Candidate List.
//! \param[out] pKernelDataStruct Shared buffer to be filled with the correct AID parameters (depending on the Application Selection results).
//! \return
//!		- \ref TRUE if a Candidate Element has been selected.
//!		- \ref FALSE else.

static unsigned int __ClessSample_Fill_SelectCandidateElement (T_SHARED_DATA_STRUCT * pSharedStruct, unsigned char ** pReadValueSelected, unsigned long * pulReadLengthSelected)
{
	unsigned char bDefaultParameterSetFound = FALSE;	// This boolean says that the default parameter set has been found for this AID
	unsigned int nResult = FALSE;
	int cr, cr2;
	int nPosition, nPositionElement, nNbNecessaryData;
	int nAidIndex = 0xff;
	int nKernelToUse = 0;
	unsigned long ulReadLength, ulReadLengthElement;
	const unsigned char *pReadValue, *pReadValueElement;
	T_SHARED_DATA_STRUCT SubSharedExchange;
	T_SHARED_DATA_STRUCT * pAidParameters = NULL;

	if (pSharedStruct == NULL)
	{
		GTL_Traces_TraceDebug("__ClessSample_Fill_SelectCandidateElement : Invalid Input data");
		goto End;
	}

	*pReadValueSelected = NULL;
	*pulReadLengthSelected = 0;

	// Look for the Final Select Response (card) coming from Entry Point tag TAG_EP_FINAL_SELECT_RESPONSE : 0x9F928108
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	nNbNecessaryData = 0;

	do {
    	nKernelToUse = 0;

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
    	pAidParameters = ClessSample_Parameters_GiveAIDShareBuffer(nAidIndex);

    	// If parameter set has not been found
    	if (pAidParameters == NULL)
    	    continue;

        // Check if transactionType is the same or is absent from the DRL
    	nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
		cr2 = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_EMV_INT_TRANSACTION_TYPE, &ulReadLengthElement, &pReadValueElement);
	    if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If TAG_EMV_TRANSACTION_TYPE found in this parameter set
	    {
	        // If Transaction Type found, it may be the same as the inputed
	        if(gs_tTransactionDataStructure.bIsTransacTypePresent == SAMPLE_TAG_PRESENT)
			{
				if (ClessSample_Fill_GiveTransactionType() != pReadValueElement[0])
				 continue;	      
			}
	    }

    	// if Default parameter set has been found => memorized it if a partial PID parameter set has not be found
   		*pulReadLengthSelected = ulReadLength; 
   		*pReadValueSelected = (unsigned char *)pReadValue;
		// The default parameter set has been found for this AID
		bDefaultParameterSetFound = TRUE;
		break; // Jump outside the while loop
	}while (cr == STATUS_SHARED_EXCHANGE_OK); // We can stop immediately if a Parameter Set PID matches exactly

	// We have to check if TAG_EP_CANDIDATE_LIST_ELEMENT is the good one
	// Several TAG_EP_CANDIDATE_LIST_ELEMENT tags may be returned (with AID and parameters who match with transaction and card caracteristics)
	
	// If default or parameter set has been found
	if (bDefaultParameterSetFound)
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

int ClessSample_Fill_AidRelatedData (T_SHARED_DATA_STRUCT * pKernelDataStruct, T_SHARED_DATA_STRUCT * pSharedStruct, int * pKernelToUse)
{
	int nResult = TRUE;
	int cr, cr2;
	int nPosition, nPositionElement, nNbNecessaryData = 0;
	int nAidIndex = 0xff;
	unsigned int nCandidateElementFound;
	unsigned long ulReadTag;
	unsigned long ulReadLength, ulReadLengthElement;
	const unsigned char * pReadValue, *pReadValueElement;
	T_SHARED_DATA_STRUCT SubSharedExchange;
	T_SHARED_DATA_STRUCT * pAidParameters = NULL;
	T_SHARED_DATA_STRUCT * pTmpAidParameters = NULL;
	unsigned char * pCardAid;
	unsigned int  nCardAidLength;

	if ((*pKernelToUse) != NULL)
		*pKernelToUse = DEFAULT_EP_KERNEL_UNKNOWN;
	
	if ((pSharedStruct == NULL) || (pKernelDataStruct == NULL))
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : Invalid Input data");
		nResult = FALSE;
		goto End;
	}
	
	// Find the good Candidate Element in the Candidate List sent by EntryPoint
	nCandidateElementFound = __ClessSample_Fill_SelectCandidateElement (pSharedStruct, (unsigned char **)&pReadValue, &ulReadLength);
	
	// Here, only the first candidate element is checked. But it could be possible to have several candidate element at the same time.
    if (nCandidateElementFound) // If tag with AID informations found
    {
		if (GTL_SharedExchange_InitEx(&SubSharedExchange, ulReadLength, ulReadLength, (unsigned char *)pReadValue) != STATUS_SHARED_EXCHANGE_OK)
		{
	    	GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : GTL_SharedExchange_InitEx error");
	    	nResult = FALSE;
	    	goto End;
		}
    	
		nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
		cr2 = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionElement, TAG_EP_KERNEL_TO_USE, &ulReadLengthElement, &pReadValueElement);
	    if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
        {
        	nNbNecessaryData ++; // One information has been found on two bytes
        	*pKernelToUse = pReadValueElement[1] + (pReadValueElement[0] << 8);
        }
	    
	    nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
		cr2 = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionElement, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, &ulReadLengthElement, &pReadValueElement);
	    if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
        {
	    	nNbNecessaryData ++; // One information has been found
        	nAidIndex = pReadValueElement[3] + (pReadValueElement[2] << 8) + (pReadValueElement[1] << 16) + (pReadValueElement[0] << 24);
        }

	    nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
		cr2 = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionElement, TAG_EMV_AID_CARD, &ulReadLengthElement, &pReadValueElement);
	    if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
        {
	    	nNbNecessaryData ++; // One information has been found
        	pCardAid = (unsigned char*)pReadValueElement;
        	nCardAidLength = ulReadLengthElement;
        }
	    else
	    {
	    	nPositionElement = SHARED_EXCHANGE_POSITION_NULL; 
    		cr2 = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionElement, TAG_EMV_DF_NAME, &ulReadLengthElement, &pReadValueElement);
    	    if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
	        {
    	    	nNbNecessaryData ++; // One information has been found
	        	pCardAid = (unsigned char*)pReadValueElement;
	        	nCardAidLength = ulReadLengthElement;
	        }
	    }
    }
    else // error or end or ...
    {
    	GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : GTL_SharedExchange_FindNext End");
    	nResult = FALSE;
    	goto End;
    }
	
	// All the information to retrieve the AID have been found
	if (nNbNecessaryData != 3) // AID informations (KERNEL TO USE and AID PROPRIETARY IDENTIFIER) not found !
	{
    	GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : Missing information to retrieve the AID\n");
    	nResult = FALSE;
    	goto End;
	}
	
	// Add parameters given to the AID's parameters
	pAidParameters = ClessSample_Parameters_GiveAIDShareBuffer(nAidIndex);

	// Copy TLVTree in a temporary struct
	if (pAidParameters != NULL)
	{
		pTmpAidParameters = GTL_SharedExchange_InitShared (pAidParameters->ulMaxBufferSize);
		pTmpAidParameters->ulDataLength = pAidParameters->ulDataLength;
		memcpy(pTmpAidParameters->nPtrData, pAidParameters->nPtrData, pAidParameters->ulDataLength); 
	}
	
	if (pTmpAidParameters != NULL)
	{
		// Copy AIDs' parameters in final Share Buffer
		if (GTL_SharedExchange_AddSharedBufferContent (pKernelDataStruct, pTmpAidParameters) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : GTL_SharedExchange_AddSharedBufferContent failed\n");
			GTL_SharedExchange_ClearEx (pKernelDataStruct, FALSE);
			nResult = FALSE;
			GTL_SharedExchange_DestroyShare(pTmpAidParameters);
			goto End;
		}
		GTL_SharedExchange_DestroyShare(pTmpAidParameters);
	}
	else
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : Unable to get the AID shared buffer");
		nResult = FALSE;
		goto End; // No treatment to realise !!
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
			case (TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER):
				cr2 = GTL_SharedExchange_AddTag(pKernelDataStruct, ulReadTag, ulReadLengthElement, pReadValueElement);
				if (cr2 != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : An error occurred when adding the AID element (provided by application selection) in the shared buffer (ulTag = %02lx, cr = %02x)", ulReadTag, cr2);
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
        	GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : GTL_SharedExchange_AddTag error (cr=%02x)", cr2);
        	GTL_SharedExchange_ClearEx (pKernelDataStruct, FALSE);
        	nResult = FALSE;
        	goto End;
    	}
    }
    else
    {
    	GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : TAG_EP_FINAL_SELECT_STATUS_WORD not found in cless_debit_aid()");
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
        	GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : GTL_SharedExchange_AddTag error (cr=%02x)", cr2);
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
        	GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : GTL_SharedExchange_AddTag error (cr=%02x)", cr2);
        	GTL_SharedExchange_ClearEx (pKernelDataStruct, FALSE);
        	nResult = FALSE;
        	goto End;
    	}
    }
    else
    {
    	GTL_Traces_TraceDebug("ClessSample_Fill_AidRelatedData : TAG_EP_FINAL_SELECT_COMMAND_SENT not found in cless_debit_aid()");
    }

End:
	return (nResult);
}
