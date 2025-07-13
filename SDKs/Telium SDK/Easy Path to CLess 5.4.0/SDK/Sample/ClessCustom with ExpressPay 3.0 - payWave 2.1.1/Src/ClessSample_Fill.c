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
T_GENERIC_TRANSACTION_DATA T_GenericTransactionData;	/*!< Global variable for transaction file. */


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////
static unsigned int __nFoundApplicationProgramId(T_SHARED_DATA_STRUCT * pSharedStruct, unsigned char **pReadValueAPI, unsigned long * pulReadLengthAPI);
static unsigned int __ClessSample_Fill_SelectCandidateElement (T_SHARED_DATA_STRUCT * pSharedStruct, unsigned char ** pReadValueSelected, unsigned long * pulReadLengthSelected);


/////////////////////////////////////////////////////////////////
//// Function ///////////////////////////////////////////////////


//! \brief Gives transaction amount.
//! \return
//!		- \a transaction amount.
//! \note This function shall be called after having loaded the parameters.
unsigned long ClessSample_Fill_GiveAmount(void)
{
	return (T_GenericTransactionData.gs_ulTransactionAmountBin);
}


//! \brief Indicates if there is only Amex AIDs in the parameters.
//! \return
//!		- \a TRUE if only Amex AIDs are present.
//!		- \a FALSE if not.
//! \note This function shall be called after having loaded the parameters.

int ClessSample_Fill_IsThereAmexAidOnly (void)
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

//! \brief Indicates if there is only Interac AIDs in the parameters.
//! \return
//!		- \a TRUE if only Interac AIDs are present.
//!		- \a FALSE if not.
//! \note This function shall be called after having loaded the parameters.

int ClessSample_Fill_IsThereInteracAidOnly (void)
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
			if (usTempKernelToUse != DEFAULT_EP_KERNEL_INTERAC)
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

//! \brief Gives the money label.
//! \return
//!		- \a money label.
//! \note This function shall be called after having loaded the parameters.
char *ClessSample_Fill_GiveMoneyLabel(void)
{
	return ((char *)(T_GenericTransactionData.gs_ucTransactionCurrencyLabel));
}

//! \brief Gives transaction type.
//! \return
//!		- \a transaction type.
//! \note This function can be called after transaction type has been populated
unsigned char ClessSample_Fill_GiveTransactionType(void)
{
	return (T_GenericTransactionData.gs_ucTransactionType);
}

//! \brief Indicates if there is at least one Visa AID in the parametres.
//! \return
//!		- \a TRUE if at least one Visa AID is present.
//!		- \a FALSE if not.
//! \note This function shall be called after having loaded the parameters.

int ClessSample_Fill_IsThereVisaAid (void)
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

//! \brief Save the some transaction only provided on CLESS_GIVE_INFO service.
//! \param[in] bAmountPresent Indicates if the transaction amount is present or not.
//! \param[in] ucTransactionType Indicates the transaction type to save.
//! \param[in] ucTransactionCashBack Indicates the specific transaction cashback type.
//! \param[in] pCurrencyCode Indicates the transaction currency code to save (shall be coded on 2 bytes).
//! \param[in] ucCurrencyExponent Indicates the transaction type to save.
//! \param[in] pCurrencylabel Indicates the currency label to save.
//! \param[in] ulAmountBin Indicates the transaction amount (binary format) to save.
//! \param[in] ulAmountOtherBin Indicates the transaction amount other (binary format) to save.

void ClessSample_Fill_PrepareAndSaveClessGiveInfoTransactionData (unsigned char bAmountPresent, unsigned char ucTransactionType, const unsigned char * pCurrencyCode, unsigned char ucCurrencyExponent, const unsigned char * pCurrencyLabel, unsigned long ulAmountBin, unsigned long ulAmountOtherBin)
{
	NO_SERIE serial;
	DATE Date;

	// Init data
	T_GenericTransactionData.gs_bIsAmountPresent = bAmountPresent;
	T_GenericTransactionData.gs_ucTransactionType = ucTransactionType;
	//T_GenericTransactionData.gs_ucTransactionCashBack = ucTransactionCashBack;
	memset (T_GenericTransactionData.gs_ucTransactionDate, 0, sizeof(T_GenericTransactionData.gs_ucTransactionDate));
	memset (T_GenericTransactionData.gs_ucTransactionTime, 0, sizeof(T_GenericTransactionData.gs_ucTransactionTime));
	memset (T_GenericTransactionData.gs_ucTransactionCurrencyCode, 0, sizeof (T_GenericTransactionData.gs_ucTransactionCurrencyCode));
	memset (T_GenericTransactionData.gs_ucTransactionCurrencyLabel, 0, sizeof (T_GenericTransactionData.gs_ucTransactionCurrencyLabel));
	T_GenericTransactionData.gs_ucTransactionCurrencyExponent = 0;
	T_GenericTransactionData.gs_ulTransactionAmountBin = 0;
	T_GenericTransactionData.gs_ulTransactionAmountOtherBin = 0;
	memset(T_GenericTransactionData.gs_ucIfdSerialNumber, 0, sizeof(T_GenericTransactionData.gs_ucIfdSerialNumber));

	// Get the current date & time
	if (read_date(&Date) == OK)
	{
		T_GenericTransactionData.gs_ucTransactionDate[0] = (unsigned char)(((Date.year[0] - '0') << 4) | (Date.year[1] - '0'));
		T_GenericTransactionData.gs_ucTransactionDate[1] = (unsigned char)(((Date.month[0] - '0') << 4) | (Date.month[1] - '0'));
		T_GenericTransactionData.gs_ucTransactionDate[2] = (unsigned char)(((Date.day[0] - '0') << 4) | (Date.day[1] - '0'));
		
		T_GenericTransactionData.gs_ucTransactionTime[0] = (unsigned char)(((Date.hour[0] - '0') << 4) | (Date.hour[1] - '0'));
		T_GenericTransactionData.gs_ucTransactionTime[1] = (unsigned char)(((Date.minute[0] - '0') << 4) | (Date.minute[1] - '0'));
		T_GenericTransactionData.gs_ucTransactionTime[2] = (unsigned char)(((Date.second[0] - '0') << 4) | (Date.second[1] - '0'));
	}
	else
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_PrepareAndSaveClessGiveInfoTransactionData : Unable to read date and time");
	}

	// Save some data only is amount is present
	if (bAmountPresent)
	{
		if (pCurrencyCode != NULL)
			memcpy (T_GenericTransactionData.gs_ucTransactionCurrencyCode, pCurrencyCode, sizeof (T_GenericTransactionData.gs_ucTransactionCurrencyCode));
		if (pCurrencyLabel != NULL)
			memcpy (T_GenericTransactionData.gs_ucTransactionCurrencyLabel, pCurrencyLabel, sizeof(T_GenericTransactionData.gs_ucTransactionCurrencyLabel) - 1);
		T_GenericTransactionData.gs_ucTransactionCurrencyExponent = ucCurrencyExponent;
		T_GenericTransactionData.gs_ulTransactionAmountBin = ulAmountBin;
		T_GenericTransactionData.gs_ulTransactionAmountOtherBin = ulAmountOtherBin;
	}

	// Get and save the IFD serial number (for future use)
	PSQ_Give_Serial_Number (serial);
	memcpy (T_GenericTransactionData.gs_ucIfdSerialNumber, serial, 8);
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


	unsigned int nJCBKernelPresent = 0;
	unsigned int nPayPassKernelPresent = 0;
	unsigned int nVisaKernelPresent = 0;
	unsigned int nAmexKernelPresent = 0;
	unsigned int nDiscoverKernelPresent = 0;
	unsigned int nInteracKernelPresent = 0;
	T_SHARED_DATA_STRUCT * pSharedStructure;


	if ((pOuputTlvTree == NULL) || (pParamTlvTree == NULL))
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_GetApplicationSelectionParameters : Invalid Input data");
		nResult = FALSE;
		goto End;
	}

	// Init the shared buffer
	pSharedStructure = GTL_SharedExchange_InitShared(256);

	// Check the structure correctly created
	if (pSharedStructure != NULL)
	{
		// Check if JCB kernel is loaded
		nJCBKernelPresent = 1; // Default value

		// Check if PayPass 3 kernel is loaded
		if (PayPass3_GetInfos (pSharedStructure) == KERNEL_STATUS_OK)
			nPayPassKernelPresent = 1;

		// Check if payWave 02.04 is loaded
		if (payWave_GetInfos (pSharedStructure) == KERNEL_STATUS_OK)
			nVisaKernelPresent = 1;

		// Check if Amex kernel is loaded
		if (ExpressPay3_GetInfos (pSharedStructure) == KERNEL_STATUS_OK)
			nAmexKernelPresent = 1;

		// Check if Discover kernel is loaded
		if (Discover_GetInfos (pSharedStructure) == KERNEL_STATUS_OK)
			nDiscoverKernelPresent = 1;

		// Check if Interac kernel is loaded
		if (Interac_GetInfos (pSharedStructure) == KERNEL_STATUS_OK)
			nInteracKernelPresent = 1;

		// Check if VisaWave kernel is loaded
		if (VisaWave_GetInfos (pSharedStructure) == KERNEL_STATUS_OK)
			nVisaKernelPresent = 1;

		// Destroy the shared buffer
		GTL_SharedExchange_DestroyShare(pSharedStructure);
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
		unsigned int nCopy = FALSE;
		TLV_TREE_NODE pResearch;			// Working Node

		pTlvAidParam = ClessSample_Parameters_GiveAIDTLVTtree(nIndex);

		// Found kernel parameters to use
		//nIndex = 0;
		pResearch = TlvTree_Find(pTlvAidParam, TAG_EP_KERNEL_TO_USE, 0);
		if (pResearch) // If kernel to use has been found
		{
			unsigned char * pucTagPtr;

			pucTagPtr = TlvTree_GetData(pResearch);

			switch ((pucTagPtr[0]<< 8) + pucTagPtr[1])
			{
			case DEFAULT_EP_KERNEL_JCB:
				if (nJCBKernelPresent)
					nCopy = TRUE;
				break;
			case DEFAULT_EP_KERNEL_PAYPASS:
				if (nPayPassKernelPresent)
					nCopy = TRUE;
				break;
			case DEFAULT_EP_KERNEL_VISA:
				if (nVisaKernelPresent)
					nCopy = TRUE;
				break;
			case DEFAULT_EP_KERNEL_AMEX:
				if (nAmexKernelPresent)
					nCopy = TRUE;
				break;
			case DEFAULT_EP_KERNEL_DISCOVER:
				if (nDiscoverKernelPresent)
					nCopy = TRUE;
				break;
			case DEFAULT_EP_KERNEL_INTERAC:
				if (nInteracKernelPresent)
					nCopy = TRUE;
				break;
			default :
				nCopy = TRUE;
				break;
			}
			if (nCopy == FALSE)
				continue;
		}

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

		if (usTempKernelToUse != DEFAULT_EP_KERNEL_PAYPASS)
		{
			// TAG_EP_CLESS_CVM_REQUIRED_LIMIT : 0x9F92810E
			pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_CLESS_CVM_REQUIRED_LIMIT, 0);
			if (pTlvTmp != 0)
				TlvTree_AddChild(pTlvAidInfo, TAG_EP_CLESS_CVM_REQUIRED_LIMIT, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));

			// TAG_EP_CLESS_FLOOR_LIMIT : 0x9F92810F
			pTlvTmp = TlvTree_Find(pTlvAidParam, TAG_EP_CLESS_FLOOR_LIMIT, 0);
			if (pTlvTmp != 0)
				TlvTree_AddChild(pTlvAidInfo, TAG_EP_CLESS_FLOOR_LIMIT, TlvTree_GetData(pTlvTmp), TlvTree_GetLength(pTlvTmp));
		}
		
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
	


//! \brief Fill the output CLESS_GIVE_INFO DEL with the serialisez TLV Tree containing all the necessary data for application selection.
//! \param[out] param_out Output structure provided on the CLESS_GIVE_INFO service.
//! \param[in] pParamTlvTree TLV Tree containing all the parameters (supported AIDs, etc).
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int ClessSample_Fill_GiveInfo (S_CLESS_GIVEINFO * param_out, TLV_TREE_NODE * pParamTlvTree)
{
	int nResult, cr;
	TLV_TREE_NODE pTlvTree = NULL; 	// Output parameters
	
	nResult = TRUE;
	cr = 0;
	
	if ((param_out == NULL) || (pParamTlvTree == NULL))
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_GiveInfo : Invalid Input data");
		nResult = FALSE;
		goto End;
	}
	
	// Output Parameters initialisation
	pTlvTree = TlvTree_New(C_TAG_MAIN);
	
	if (pTlvTree != NULL)
	{
		if (!ClessSample_Fill_GetApplicationSelectionParameters(&pTlvTree, pParamTlvTree, FALSE))
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_GiveInfo : ClessSample_Fill_GetApplicationSelectionParameters failed");
			nResult = FALSE;
			goto End;
		}
		
		// Serialize the TLV Tree in the DEL * of param_out
		cr = TlvTree_Serialize(pTlvTree, TLV_TREE_SERIALIZER_DEFAULT, (unsigned char *)(&(param_out->del)), sizeof (_DEL_));
		
		if (cr < 0)
		{
			GTL_Traces_TraceDebug ("ClessSample_Fill_GiveInfo : TlvTree_Serialize failed (error code = %02x)", cr);
			memset (&(param_out->del), 0, sizeof (_DEL_));
			nResult = FALSE;
			goto End;
		}
	}
	else
	{
		// Lack of memory
		GTL_Traces_TraceDebug("ClessSample_Fill_GiveInfo : Not enough memory to allocate the temporary TLV Tree");
		nResult = FALSE;
		goto End;
	}
	
	
End:
	if (pTlvTree != NULL)
		TlvTree_Release(pTlvTree);
	
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
	
	if (pDataStruct == NULL)
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Invalid Input data");
		nResult = FALSE;
		goto End;
	}
	
	// Init local data
	nResult = TRUE;
	
	// Add the transaction date
	cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_TRANSACTION_DATE, 3, T_GenericTransactionData.gs_ucTransactionDate);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_DATE in the shared buffer");
		nResult = FALSE;
		goto End;
	}

	// Add the transaction time
	cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_EMV_TRANSACTION_TIME, 3, T_GenericTransactionData.gs_ucTransactionTime);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_TIME in the shared buffer");
		nResult = FALSE;
		goto End;
	}
	
	// Add the amount and the currency code (if present)
	if (T_GenericTransactionData.gs_bIsAmountPresent)
	{
		memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
		GTL_Convert_UlToBinNumber(T_GenericTransactionData.gs_ulTransactionAmountBin, ucTempBuffer, 4);
		
		// Add the transaction amount binary
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_AUTH_BIN, 4, ucTempBuffer);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_AUTH_BIN in the shared buffer");
			nResult = FALSE;
			goto End;
		}

		memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
		GTL_Convert_UlToDcbNumber(T_GenericTransactionData.gs_ulTransactionAmountBin, ucTempBuffer, 6);
		
		// Add the transaction amount binary
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_AUTH_NUM, 6, ucTempBuffer);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_AUTH_NUM in the shared buffer");
			nResult = FALSE;
			goto End;
		}
		
		memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
		GTL_Convert_UlToBinNumber(T_GenericTransactionData.gs_ulTransactionAmountOtherBin, ucTempBuffer, 4);

		// Add the transaction other binary
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_OTHER_BIN, 4, ucTempBuffer);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_OTHER_BIN in the shared buffer");
			nResult = FALSE;
			goto End;
		}
		
		memset (ucTempBuffer, 0, sizeof(ucTempBuffer));
		GTL_Convert_UlToDcbNumber(T_GenericTransactionData.gs_ulTransactionAmountOtherBin, ucTempBuffer, 6);

		// Add the transaction other binary
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_AMOUNT_OTHER_NUM, 6, ucTempBuffer);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_AMOUNT_OTHER_NUM in the shared buffer");
			nResult = FALSE;
			goto End;
		}
		
		// Add the currency code
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_CODE, 2, T_GenericTransactionData.gs_ucTransactionCurrencyCode);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_CURRENCY_CODE in the shared buffer");
			nResult = FALSE;
			goto End;
		}
		
		// Add the currency exponent
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_TRANSACTION_CURRENCY_EXPONENT, 1, &(T_GenericTransactionData.gs_ucTransactionCurrencyExponent));
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_TRANSACTION_CURRENCY_EXPONENT in the shared buffer");
			nResult = FALSE;
			goto End;
		}
	}
	
	// Add the internal transaction type
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_INT_TRANSACTION_TYPE, 1, &(T_GenericTransactionData.gs_ucTransactionType));
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_INT_TRANSACTION_TYPE in the shared buffer");
		nResult = FALSE;
		goto End;
	}
	
	// Add the standard transaction type
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_TRANSACTION_TYPE, 1, &(T_GenericTransactionData.gs_ucTransactionType));
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_INT_TRANSACTION_TYPE in the shared buffer");
		nResult = FALSE;
		goto End;
	}

	// Add the IFD serial number
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_EMV_IFD_SERIAL_NUMBER, sizeof(T_GenericTransactionData.gs_ucIfdSerialNumber), T_GenericTransactionData.gs_ucIfdSerialNumber);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("ClessSample_Fill_TransactionGenericData : Unable to add TAG_EMV_IFD_SERIAL_NUMBER in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
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

//! \brief Founf the Application Program Identifier in parameters given by Entry Point.
//! \param[in] pSharedStruct Shared buffer containing the application selection results.
//! \param[out] pReadValueAPI pointer of pointer on TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER data.
//! \param[out] pulReadLengthAPI pointer on TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER field length.
//! \return
//!		- \ref TRUE if TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER tag has been found.
//!		- \ref FALSE else.

static unsigned int __nFoundApplicationProgramId(T_SHARED_DATA_STRUCT * pSharedStruct, unsigned char **pReadValueAPI, unsigned long * pulReadLengthAPI)
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
	if (cr == STATUS_SHARED_EXCHANGE_OK) // If tag found
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

static unsigned int __ClessSample_Fill_SelectCandidateElement (T_SHARED_DATA_STRUCT * pSharedStruct, unsigned char ** pReadValueSelected, unsigned long * pulReadLengthSelected)
{
	unsigned char bParameterSetFound = FALSE;			// This boolean says that the parameter set has been found for this AID
	unsigned char bPartialParameterSetFound = FALSE;	// This boolean says that the parameter set has been found for the partial AID
	unsigned char bDefaultParameterSetFound = FALSE;	// This boolean says that the default parameter set has been found for this AID
	unsigned int nPartialParameterAIDLength = 0;
	unsigned int nResult = FALSE;
	int cr, cr2;
	int nPosition, nPositionElement, nNbNecessaryData;
	int nAidIndex = 0xff;
	int nKernelToUse = 0;
	unsigned long ulReadLength, ulReadLengthElement;
	const unsigned char *pReadValue, *pReadValueElement;
	unsigned char *pReadValueCardAPI;
	unsigned long ulReadLengthCardAPI;
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

	// If an Application Program Id has been found in data sent by card in the final select response
	if (__nFoundApplicationProgramId(pSharedStruct, &pReadValueCardAPI, &ulReadLengthCardAPI))
	{
		unsigned int index;
		char acStrTmp[100];

		memset(acStrTmp, 0, sizeof(acStrTmp));
		for (index=0; index<ulReadLengthCardAPI; index++)
		{
			char acLocalStr[5];
			
			sprintf(acLocalStr, " %2x", pReadValueCardAPI[index]);
			strcat(acStrTmp, acLocalStr);
		}
		GTL_Traces_TraceDebug("CardPI : %s ", acStrTmp);
	}
	else
		GTL_Traces_TraceDebug("No CardPI");

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

		// case Tag transaction with CashBack (case payWave -> check it is a debit)
		nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
		cr2 = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_SAMPLE_TRANSACTION_CASHBACK, &ulReadLengthElement, &pReadValueElement);
		if ((cr2 == STATUS_SHARED_EXCHANGE_OK) && (pReadValueElement[0] == TRUE))
		{  // case TAG_SAMPLE_TRANSACTION_CASHBACK found and activated

			if (T_GenericTransactionData.gs_ucTransactionType != CLESS_SAMPLE_TRANSACTION_TYPE_PURSH_WITH_CASHBACK)
				continue;

			// verify TAG transactionType is DEBIT
			nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
			cr2 = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_EMV_INT_TRANSACTION_TYPE, &ulReadLengthElement, &pReadValueElement);
			if (cr2 == STATUS_SHARED_EXCHANGE_OK)
			{
				if (CLESS_SAMPLE_TRANSACTION_TYPE_DEBIT != pReadValueElement[0])
					continue;
			}
		}
		else
		{  // Verify Transaction Type
			nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
			cr2 = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_EMV_INT_TRANSACTION_TYPE, &ulReadLengthElement, &pReadValueElement);
			if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If TAG_EMV_TRANSACTION_TYPE found in this parameter set
			{
				// If Transaction Type found, it may be the same as the inputed
				if (T_GenericTransactionData.gs_ucTransactionType != pReadValueElement[0])
				continue;
			}
		}

		// Look for the Program Application Identifier in the Aid Parameters

		nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
		cr2 = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_EP_KERNEL_TO_USE, &ulReadLengthElement, &pReadValueElement);
		if (cr2 == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
		{
			nKernelToUse = pReadValueElement[1] + (pReadValueElement[0] << 8);
		}

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
					bParameterSetFound = TRUE;	// The specific parameter set has been found for this AID
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
					bPartialParameterSetFound = TRUE;	// The specific parameter set has been found for this AID
				}
			}
			else if (ulReadLengthCardAPI < ulReadLengthElement)
			{
				// No treatment here
			}
		}
		else if (cr2 == STATUS_SHARED_EXCHANGE_END) // If TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER not found in this parameter set
		{
			// Tag TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER not found, we will take this parameter set as the default one

			// if Default parameter set has been found => memorized it if a partial PID parameter set has not be found
			if ((bDefaultParameterSetFound == FALSE) && (bPartialParameterSetFound == FALSE))
			{
				*pulReadLengthSelected = ulReadLength; 
				*pReadValueSelected = (unsigned char *)pReadValue;
				bDefaultParameterSetFound = TRUE;	// The default parameter set has been found for this AID

				if (ulReadLengthCardAPI == 0) // If no Application Program Identifier has been given by card
					// We can take it and stop research
					break; // Jump outside the while loop
			}
		}
	}while ((cr == STATUS_SHARED_EXCHANGE_OK) && (bParameterSetFound == FALSE)); // We can stop immediately if a Parameter Set PID matches exactly

	// We have to check if TAG_EP_CANDIDATE_LIST_ELEMENT is the good one
	// Several TAG_EP_CANDIDATE_LIST_ELEMENT tags may be returned (with AID and parameters who match with transaction and card caracteristics)
	
	// If default or parameter set has been found
	if (bDefaultParameterSetFound || bPartialParameterSetFound || bParameterSetFound)
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


	// Call kernel in relationship with AID
	switch (*pKernelToUse)
	{
		case DEFAULT_EP_KERNEL_PAYPASS :
			// No specific action to made on PayPass Parameters
			ClessSample_PayPass_AidRelatedData(pKernelDataStruct, pAidParameters);
			break;
			
		case DEFAULT_EP_KERNEL_VISA :
			// Warning, some parameters must be modified before to be taken for the Aid
			// Intermediate struct is needed because it can be modified
			if(VisaWave_isVisaWaveProcessing())
				ClessSample_VisaWave_ModifyAidParameters(pKernelDataStruct, &SubSharedExchange, pTmpAidParameters);
			else
				ClessSample_payWave_ModifyAidParameters(&SubSharedExchange, pTmpAidParameters);
			break;
			
		case DEFAULT_EP_KERNEL_AMEX :
			// ClessSample_ExpressPay_AidRelatedData(pTmpAidParameters);
			break;
		
		case DEFAULT_EP_KERNEL_DISCOVER :
			// No specific action to made on Discover Parameters
			// ClessSample_Discover_AidRelatedData(pSharedStruct, pAidParameters);
			break;

		case DEFAULT_EP_KERNEL_INTERAC :
			// No specific action to made on Interac Parameters
			// ClessSample_Interac_AidRelatedData(pSharedStruct, pAidParameters);
			break;

		default:
			break;
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
//			case (TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS):
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


/*T_SHARED_DATA_STRUCT * cu_fill_debit_aid_buffer (T_SHARED_DATA_STRUCT * pSharedStruct, int * pKernelToUse)
{
	// Specific variables to manage share buffer 
	T_SHARED_DATA_STRUCT * pShareAIDParameters = 0; 	// Share buffer with preprocessed parameters for an AID
	static T_SHARED_DATA_STRUCT* pFinalParameters = 0;	// Final share buffer with all parameters for kernel
	
	int nAIDIndex;
	int cr;
	unsigned char * pCardAid;
	unsigned int  nCardAidLength;
	
	int nResult, nResultInTagInfo, nPosition, nPositionInTagInfo;
	unsigned long ulTag, ulReadLength, ulReadLengthInTagInfo;
	const unsigned char * pReadValue;
	const unsigned char * pReadValueInTagInfo;
	
	// Parameters informations
	unsigned char * pParameterSet;
	unsigned long ulParameterLength;
	unsigned int  nNbInformations = 0;
	T_SHARED_DATA_STRUCT SubSharedExchange;
	
	*pKernelToUse = -1;
	nAIDIndex = -1;

	// Init Share 
	if (pFinalParameters == 0)
		pFinalParameters = GTL_SharedExchange_Init(C_SHARE_BUFFER_KERNEL_SIZE, C_BUFFER_SHARED);
	else
		GTL_SharedExchange_ClearEx (pFinalParameters, FALSE);
		
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	
	do
	{ 
		// Loop on each input data
		// Try to following tag.
		ulTag = TAG_EP_CANDIDATE_LIST_ELEMENT;
		nResult = GTL_SharedExchange_FindNext (pSharedStruct, &nPosition, ulTag, &ulReadLength, &pReadValue);
	
	    if (nResult == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
	    {
	    	// Parameters information memorisation
	    	pParameterSet = (unsigned char *)pReadValue;
	    	ulParameterLength = ulReadLength;

			if (GTL_SharedExchange_InitEx(&SubSharedExchange, ulReadLength, ulReadLength, (unsigned char *)pReadValue) != STATUS_SHARED_EXCHANGE_OK)
			{
		    	GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : GTL_SharedExchange_InitEx error in cless_debit_aid()");
		    	//return (pShareAIDParameters); // No treatment to realise !!
		    	goto End;
			}
	    	
	    	nPositionInTagInfo = SHARED_EXCHANGE_POSITION_NULL; 
	    	ulTag = TAG_EP_KERNEL_TO_USE; 					// Witch kernel to use ?
    		nResultInTagInfo = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionInTagInfo, ulTag, &ulReadLengthInTagInfo, &pReadValueInTagInfo);
    	    if (nResultInTagInfo == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
	        {
	        	nNbInformations ++; // One information has been found on two bytes
	        	*pKernelToUse = pReadValueInTagInfo[1] + (pReadValueInTagInfo[0] << 8);
	        }
    	    
	    	nPositionInTagInfo = SHARED_EXCHANGE_POSITION_NULL; 
	    	ulTag = TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER;	// 0x9F928202
    		nResultInTagInfo = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionInTagInfo, ulTag, &ulReadLengthInTagInfo, &pReadValueInTagInfo);
    	    if (nResultInTagInfo == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
	        {
	        	nNbInformations ++; // One information has been found
	        	nAIDIndex = pReadValueInTagInfo[3] + (pReadValueInTagInfo[2] << 8) + (pReadValueInTagInfo[1] << 16) + (pReadValueInTagInfo[0] << 24);
	        }

	    	nPositionInTagInfo = SHARED_EXCHANGE_POSITION_NULL; 
	    	ulTag = TAG_EMV_AID_CARD;	// 0x4F
    		nResultInTagInfo = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionInTagInfo, ulTag, &ulReadLengthInTagInfo, &pReadValueInTagInfo);
    	    if (nResultInTagInfo == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
	        {
	        	nNbInformations ++; // One information has been found
	        	pCardAid = (unsigned char*)pReadValueInTagInfo;
	        	nCardAidLength = ulReadLengthInTagInfo;
	        }
    	    else
    	    {
    	    	nPositionInTagInfo = SHARED_EXCHANGE_POSITION_NULL; 
		    	ulTag = TAG_EMV_DF_NAME;	// 0x84
	    		nResultInTagInfo = GTL_SharedExchange_FindNext (&SubSharedExchange, &nPositionInTagInfo, ulTag, &ulReadLengthInTagInfo, &pReadValueInTagInfo);
	    	    if (nResultInTagInfo == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
		        {
		        	nNbInformations ++; // One information has been found
		        	pCardAid = (unsigned char*)pReadValueInTagInfo;
		        	nCardAidLength = ulReadLengthInTagInfo;
		        }
    	    }
    	    
    	    // Check if all information found => stop loop on main buffer and keept informations
    	    if (nNbInformations == 3)
    	    {
    	    	//int nLenAIDTerminal;
    	    	//unsigned char * ucPtrAID;

    	    	// Check if AID given in parameters is same than gs_Parameter_AID
    			//ucPtrAID = ClessSample_Parameters_GiveAID (nAIDIndex, &nLenAIDTerminal, pAidProprietaryId, ulAidProprietaryIdLen);
    			
    			//if (nCardAidLength > nLenAIDTerminal)
    			//	nCardAidLength = nLenAIDTerminal;
    			
    			//if (memcmp(ucPtrAID, pCardAid, nCardAidLength) == 0)
    			//{
    				// Aid checked !
    				nNbInformations ++;
    				// Stop processing
        	    	nResult = STATUS_SHARED_EXCHANGE_END;
    			//}
    	    }
	    }
	    else if (nResult == STATUS_SHARED_EXCHANGE_END)		// Buffer end reached
	    {
	    	GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : ShareGetNext end");
	    }
	    else // error or end or ...
	    {
	    	GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : Display tags error:%x\n", nResult);
	    }
	}while (nResult == STATUS_SHARED_EXCHANGE_OK);

	// Found AID index in relationship with AID
	if (nNbInformations != 4) // AID informations (KERNEL TO USE and AID PROPRIETARY IDENTIFIER) not found !
	{
		// AID index found !
    	GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : AID index not found in cless_debit_aid\n");
    	goto End; // No treatment to realise !!
	}

	// Add parameters given to the AID's parameters
	pShareAIDParameters = ClessSample_Parameters_GiveAIDShareBuffer(nAIDIndex);

	if (pShareAIDParameters != NULL)
	{
		// Copy AIDs' parameters in final Share Buffer
		if (GTL_SharedExchange_AddSharedBufferContent (pFinalParameters, pShareAIDParameters) != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : GTL_SharedExchange_AddSharedBufferContent error in cu_fill_debit_aid_buffer\n");
			GTL_SharedExchange_ClearEx (pFinalParameters, FALSE);
			goto End; // No treatment to realise !!
		}
	}
	else
	{
		GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : Unable to get the AID shared buffer");
		goto End; // No treatment to realise !!
	}
	
	// Add some of the candidate element tags in the final shared buffer
    // Get the AID Additional result (if present)
	nPositionInTagInfo = SHARED_EXCHANGE_POSITION_NULL;
	nResultInTagInfo = STATUS_SHARED_EXCHANGE_OK;
	
	while (nResultInTagInfo == STATUS_SHARED_EXCHANGE_OK)
	{
		nResultInTagInfo = GTL_SharedExchange_GetNext(&SubSharedExchange, &nPositionInTagInfo, &ulTag, &ulReadLengthInTagInfo, &pReadValueInTagInfo);
		
		if (nResultInTagInfo == STATUS_SHARED_EXCHANGE_OK)
		{
			switch (ulTag)
			{
			case (TAG_EP_AID_ADDITIONAL_RESULTS):
			case (TAG_EMV_AID_TERMINAL):
			case (TAG_EP_CLESS_APPLI_CAPABILITY_TYPE):
			case (TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS):
				nResultInTagInfo = GTL_SharedExchange_AddTag(pFinalParameters, ulTag, ulReadLengthInTagInfo, pReadValueInTagInfo);
				if (nResultInTagInfo != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : An error occurred when adding the AID element (provided by application selection) in the shared buffer (ulTag = %02lx, cr = %02x)", ulTag, cr);
			    	GTL_SharedExchange_ClearEx (pFinalParameters, FALSE);
			    	goto End;
				}
				break;
			
			default:
				break;
			}
			
		}
	}
	
	//cr = GTL_SharedExchange_AddSharedBufferContent(pFinalParameters, &SubSharedExchange);
	//if (cr != STATUS_SHARED_EXCHANGE_OK)
	//{
	//	GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : An error occurred when adding the AID element (provided by application selection) in the shared buffer (cr = %02x)", cr);
	//	GTL_SharedExchange_ClearEx (pFinalParameters, FALSE);
	//	goto End;
	//}
	//memcpy (&pFinalParameters->nPtrData[pFinalParameters->ulDataLength], pParameterSet, ulParameterLength);
	//pFinalParameters->ulDataLength += ulParameterLength;
	
	// Found parameters in relationship with AID
	// => add global parameters as TAG_EP_FINAL_SELECT_STATUS_WORD & TAG_EP_FINAL_SELECT_RESPONSE

	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	ulTag = TAG_EP_FINAL_SELECT_STATUS_WORD;
	nResult = GTL_SharedExchange_FindNext (pSharedStruct, &nPosition, ulTag, &ulReadLength, &pReadValue);
	if (nResult == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
    {
    	// Parameters add in final struct
    	cr = GTL_SharedExchange_AddTag (pFinalParameters, ulTag, ulReadLength, pReadValue);
    	if (cr != STATUS_SHARED_EXCHANGE_OK)
    	{
        	GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : GTL_SharedExchange_AddTag error in cless_debit_aid()");
        	GTL_SharedExchange_ClearEx (pFinalParameters, FALSE);
        	goto End;
    	}
    }
    else
    {
    	GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : TAG_EP_FINAL_SELECT_STATUS_WORD not found in cless_debit_aid()");
    	GTL_SharedExchange_ClearEx (pFinalParameters, FALSE);
    	goto End;
    }

	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	ulTag = TAG_EP_FINAL_SELECT_RESPONSE;
	nResult = GTL_SharedExchange_FindNext (pSharedStruct, &nPosition, ulTag, &ulReadLength, &pReadValue);
	if (nResult == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
    {
    	// Parameters add in final struct
    	cr = GTL_SharedExchange_AddTag (pFinalParameters, ulTag, ulReadLength, pReadValue);
    	if (cr != STATUS_SHARED_EXCHANGE_OK)
    	{
        	GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : GTL_SharedExchange_AddTag error in cless_debit_aid()");
        	GTL_SharedExchange_ClearEx (pFinalParameters, FALSE);
        	goto End;
    	}
    }
    else
    {
    	GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : TAG_EP_FINAL_SELECT_STATUS_WORD not found in cless_debit_aid()");
    	GTL_SharedExchange_ClearEx (pFinalParameters, FALSE);
    	goto End;
    }
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	ulTag = TAG_EMV_AMOUNT_AUTH_BIN;
	nResult = GTL_SharedExchange_FindNext (pSharedStruct, &nPosition, ulTag, &ulReadLength, &pReadValue);
	if (nResult == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
    {
    	// Parameters add in final struct
    	cr = GTL_SharedExchange_AddTag (pFinalParameters, ulTag, ulReadLength, pReadValue);
    	if (cr != STATUS_SHARED_EXCHANGE_OK)
    	{
        	GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : GTL_SharedExchange_AddTag error in cless_debit_aid()");
        	GTL_SharedExchange_ClearEx (pFinalParameters, FALSE);
        	goto End;
    	}
    }
    else
    {
    	GTL_Traces_TraceDebug("cu_fill_debit_aid_buffer : TAG_EP_FINAL_SELECT_STATUS_WORD not found in cless_debit_aid()");
    	GTL_SharedExchange_ClearEx (pFinalParameters, FALSE);
    	goto End;
    }
End:
	return (pFinalParameters);
}*/

