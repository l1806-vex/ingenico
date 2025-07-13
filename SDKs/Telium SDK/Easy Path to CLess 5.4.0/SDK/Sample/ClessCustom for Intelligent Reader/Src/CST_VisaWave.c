/**
 * \file	CST_VisaWave.c
 * \brief 	Module that manages the VisaWave transaction.
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

static int gs_bIsVisaAsiaGuiMode = FALSE;			// Set to TRUE if the VisaWave Asia GUI must be used

// Data concerning the last transaction (for Double Dip process)
static unsigned char gs_ucLastAmount[6];			// Last transaction amount
static DATE gs_LastDate;							// Last transaction date
static unsigned char gs_ucLastPAN[10];				// Last transaction PAN
static unsigned int gs_nLastPANLength;				// Last transaction PAN length


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static void __CST_VisaWave_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData);
static int __CST_VisaWave_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm);;
static void __CST_VisaWave_SaveLastTransactionData (TLV_TREE_NODE TlvTreeNode, TLV_TREE_NODE TlvTransactionData);
static void __CST_VisaWave_CheckLastTransaction (TLV_TREE_NODE TlvTransactionData);
static int __CST_VisaWave_GetDoubleDipTimeOut (unsigned long *pDoubleDipTimeOut);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Check if the Visa Asia GUI mode is activated.
//!	\return
//!		- TRUE if Visa Asia GUI mode is used.
//!		- FALSE else.

int CST_VisaWave_IsVisaAsiaGuiMode (void)
{
	return (gs_bIsVisaAsiaGuiMode);
}


//! \brief Get the VisaWave CVM to perform.
//! \param[out] pCvm Retreived transaction CVM :
//!		- \a VISAWAVE_CVM_NO_CVM No CVM to be performed.
//!		- \a VISAWAVE_CVM_SIGNATURE if signature shall be performed.
//!		- \a VISAWAVE_CVM_ONLINE_PIN if online PIN shall be performed.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

static int __CST_VisaWave_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	* pCvm = VISAWAVE_CVM_NO_CVM; // Default result
	
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_VISAWAVE_TRANSACTION_CVM, &ulReadLength, &pReadValue);
	
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

static void __CST_VisaWave_AddRecordToBatch (T_SHARED_DATA_STRUCT * pSharedData)
{	
	if (!CST_Batch_AddTransactionToBatch (pSharedData))
	{
		GTL_Traces_TraceDebug ("__CST_VisaWave_AddRecordToBatch : Save transaction in batch failed");
		Helper_DisplayMessage(STD_MESS_BATCH_ERROR, ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_RefreshScreen(WAIT);
	}
}


//! \brief Specific management for VisaWave end of transaction according to transaction result.
//! Displays specific messages, manages batch, manages online authorization, manages CVM ...
//! \param[in] pDataStruct Transaction output data. 
//! \param[in] nTransactionOutcome Transaction result.
//! \return The transaction outcome value.

int CST_VisaWave_Transaction(T_SHARED_DATA_STRUCT * pDataStruct, int nTransactionOutcome)
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

	if (!__CST_VisaWave_RetreiveCvmToApply (pDataStruct, &ucCvm))
	{
		ucCvm = VISAWAVE_CVM_NO_CVM;
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

		CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_STATUS_ERROR);		
		break;

	case (SDI_STATUS_APPROVED):

		if(ucCvm == VISAWAVE_CVM_SIGNATURE)
		{
			Helper_Visa_SignatureCVMIHM();
			CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_SIGNATURE_REQUIRED);
			if(CST_VisaWave_IsVisaAsiaGuiMode())
				ulStartSignatureTime = GTL_StdTimer_GetCurrent();
		}
		else
		{
			Helper_Visa_ApprovedIHM(OFFLINE);
			CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_OFFLINE_APPROVED);

			// Transaction shall be added to the batch
			bSaveInBatch = TRUE;
		}

		if (!bLoopMode)
        {
			// Print a receipt only if signature requested or merchant need to print a receipt	
			GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);
		
			if ((ucCvm == VISAWAVE_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30)))
				CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_VISAWAVE, APPROVED_TICKED, (ucCvm == VISAWAVE_CVM_SIGNATURE), WITH_AOSA);
		}

		if (ucCvm == VISAWAVE_CVM_SIGNATURE)
		{
			if(CST_VisaWave_IsVisaAsiaGuiMode())
			{
				nTimeout = GTL_StdTimer_GetRemaining(ulStartSignatureTime, C_SIGNATURE_TIMEOUT/10); 
				if (nTimeout > 0)
					ttestall(0,nTimeout);
			}

			GetMessageInfos(STD_MESS_SIGNATURE_OK, &tMsg);
			if ((bLoopMode) || (HelperQuestionYesNo (&tMsg, 5)))
			{
				Helper_Visa_SignatureOKIHM();
				CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_SIGNATURE_OK);
				bSaveInBatch = TRUE;
			}
			else
			{
				Helper_Visa_SignatureKOIHM();
				CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_SIGNATURE_KO);
			}
		}

		break;

	case (SDI_STATUS_ONLINE_REQUEST):				
		if (ucCvm == VISAWAVE_CVM_ONLINE_PIN) // If OnLine Pin Requested
		{    
			nPosition = SHARED_EXCHANGE_POSITION_NULL;
			if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_APPLI_PAN, &ulLgPan, &pPan) != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_Traces_TraceDebug ("CST_VisaWave_PerformTransaction : Missing PAN for Online PIN");
				bOnlinePinError = TRUE; // On-line Pin cannot be made
			}

			ulAmount = 0;
			nPosition = SHARED_EXCHANGE_POSITION_NULL;
			if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_AMOUNT_AUTH_NUM, &ulLgAmount, &pAmount) != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_Traces_TraceDebug ("CST_VisaWave_PerformTransaction : Missing Amount auth for Online PIN");
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
						GTL_Traces_TraceDebug("CST_VisaWave_PerformTransaction : Unable to add TAG_CST_ENCIPHERED_PIN_CODE in shared buffer (cr=%02x)", cr);
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
			CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_ONLINE_PROCESSING);

			///////////////////////////////////////////////
			//////////// ON-LINE AUTHORISATION //////////// 
			///////////////////////////////////////////////
			if (CST_FinancialCommunication_ManageAuthorisation (pDataStruct, SDSA_KERNEL_IDENTIFIER_VISAWAVE))
			{
				nPosition = SHARED_EXCHANGE_POSITION_NULL;

				// Try to get the host response
				if (GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EMV_AUTHORISATION_RESPONSE_CODE, &ulReadLength, &pReadValue) == STATUS_SHARED_EXCHANGE_OK)
				{
					if ((pReadValue[0] == 0x30) && (pReadValue[1] == 0x30))
					{
						if (ucCvm == VISAWAVE_CVM_SIGNATURE)
						{
							Helper_Visa_SignatureCVMIHM();
							CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_SIGNATURE_REQUIRED);
							if(CST_VisaWave_IsVisaAsiaGuiMode())
									ulStartSignatureTime = GTL_StdTimer_GetCurrent();
						}
						else
						{
							Helper_Visa_ApprovedIHM(ONLINE);
							CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_ONLINE_APPROVED);
							
							// Transaction shall be added to the batch
							bSaveInBatch = TRUE;
						}

						if (!bLoopMode)
				        {
							// Print a receipt only if signature requested or merchant need to print a receipt
							GetMessageInfos(STD_MESS_PRINT_RECEIPT, &tMsg);
						
							if ((ucCvm == VISAWAVE_CVM_SIGNATURE) || (HelperQuestionYesNo (&tMsg, 30)))
								CST_Receipt_PrintTransaction(pDataStruct, BATCH_TICKET_VISAWAVE, APPROVED_TICKED, (ucCvm == VISAWAVE_CVM_SIGNATURE), WITH_AOSA);
						}

						if(ucCvm == VISAWAVE_CVM_SIGNATURE)
						{
							if(CST_VisaWave_IsVisaAsiaGuiMode())
							{
								nTimeout = GTL_StdTimer_GetRemaining(ulStartSignatureTime, 500); 
								if (nTimeout == 0)
									ttestall(0,nTimeout);
							}

							GetMessageInfos(STD_MESS_SIGNATURE_OK, &tMsg);
							if ((bLoopMode) || (HelperQuestionYesNo (&tMsg, 5)))
							{
								Helper_Visa_SignatureOKIHM();
								CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_SIGNATURE_OK);
								bSaveInBatch = TRUE;
							}
							else
							{
								Helper_Visa_SignatureKOIHM();
								CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_SIGNATURE_KO);
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
			CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_PIN_KO);
		}

		if (ucOnLineDeclined) // Problem with communication or transaction rejected
		{
			Helper_Visa_DeclinedIHM(ONLINE);
			CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_ONLINE_DECLINED);
		}
		break;

	case (SDI_STATUS_USE_OTHER_INTERFACE):
			nTransactionResult = SDI_STATUS_USE_OTHER_INTERFACE;
			break;

	case (SDI_STATUS_DECLINED):	
		Helper_Visa_DeclinedIHM(OFFLINE);
		CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_OFFLINE_DECLINED);
		break;

	default: // Error case
		Helper_Visa_ErrorIHM();
		CST_DisplayScreen(SDSA_VISAWAVE_SCREEN_ERROR);
		break;
	}

	// Check if transaction shall be saved in the batch
	if (bSaveInBatch)
		__CST_VisaWave_AddRecordToBatch (pDataStruct);

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


//! \brief Init the global data related to the last transaction performed

static void __CST_VisaWave_InitLastTransactionData (void)
{
	// Init global data
	gs_nLastPANLength = 0;
	memset(gs_ucLastPAN,0,sizeof(gs_ucLastPAN));
	memset(gs_ucLastAmount,0,sizeof(gs_ucLastAmount));
	memset(&gs_LastDate,0,sizeof(DATE));
}


//! \brief Get the last transaction data in the batch file
//! \param[in] TlvTransactionData contains the current transaction data

void CST_VisaWave_GetLastTransactionData (TLV_TREE_NODE TlvTransactionData)
{			
	int ret;
	unsigned int nPosition;
	TLV_TREE_NODE hTree, hTreeBackup;
	int bFound;
	
	// Init global data
	__CST_VisaWave_InitLastTransactionData();

	// Init local data
	bFound = FALSE;
	hTreeBackup = NULL;
	hTree = NULL;
	
	// Get the last transaction data
	ret = CST_Disk_Mount (FILE_DISK_LABEL);

	if (ret == FS_OK)
	{
		nPosition = 0;

		do
		{
			ret = CST_TransactionFile_GetNextTransaction (&Transac_File, &hTree, &nPosition);

			if (ret == TRANS_FILE_OK)
			{
				if (hTreeBackup != NULL)
					TlvTree_Release(hTreeBackup);

				bFound = TRUE;
				hTreeBackup = hTree;
			}
		} while (ret == TRANS_FILE_OK);

		if (bFound)
			__CST_VisaWave_SaveLastTransactionData (hTreeBackup, TlvTransactionData);
		else
			GTL_Traces_TraceDebug ("CST_VisaWave_GetLastTransactionData : Batch empty");

		if (hTree != NULL)
			TlvTree_Release(hTree);
		if (hTreeBackup != NULL)
			TlvTree_Release(hTreeBackup);

		// Unmount the volume
		CST_Disk_Unmount (FILE_DISK_LABEL);
	}
	else
	{
		GTL_Traces_TraceDebug ("CST_VisaWave_GetLastTransactionData : Cannot mount disk");
	}
}


//! \brief Save last transaction data contained in a TLV Tree node
//! \param[in] TlvTreeNode TLV : contains the last transaction data to be saved.
//! \param[in] TlvTransactionData contains the current transaction data

static void __CST_VisaWave_SaveLastTransactionData (TLV_TREE_NODE TlvTreeNode, TLV_TREE_NODE TlvTransactionData)
{
	TLV_TREE_NODE pResearch;	// Working Node
	unsigned long ulTag;
	unsigned int nDataLength;					
	unsigned char *pValue;				
	unsigned int bAmountFound, bDateFound, bTimeFound, bPANFound;

	// Init local data
	bAmountFound = FALSE;
	bDateFound = FALSE;
	bTimeFound = FALSE;
	bPANFound = FALSE;

	// Parse the last transaction data
	if (TlvTreeNode != NULL)
	{
		pResearch = TlvTree_GetFirstChild (TlvTreeNode);

		while (pResearch != NULL)
		{
			// Get tag length
			nDataLength = TlvTree_GetLength(pResearch);
			// Get tag
			ulTag = TlvTree_GetTag (pResearch);
			
			if(ulTag == TAG_EMV_AMOUNT_AUTH_NUM)
			{
				memcpy(gs_ucLastAmount,(unsigned char *)TlvTree_GetData(pResearch),nDataLength);
				bAmountFound = TRUE;
			}
			if(ulTag == TAG_EMV_TRANSACTION_DATE)
			{
				pValue = TlvTree_GetData(pResearch);

				// Copy the last transaction Date in a DATE structure
				gs_LastDate.year[0]=(pValue[0]/16) + '0';
				gs_LastDate.year[1]=(pValue[0]%16) + '0';
				gs_LastDate.month[0]=(pValue[1]/16) + '0';
				gs_LastDate.month[1]=(pValue[1]%16) + '0';
				gs_LastDate.day[0]=(pValue[2]/16) + '0';
				gs_LastDate.day[1]=(pValue[2]%16) + '0';
	
				bDateFound = TRUE;
			}
			if(ulTag == TAG_EMV_TRANSACTION_TIME)
			{
				pValue = TlvTree_GetData(pResearch);

				// Copy the last transaction Time in a DATE structure
				gs_LastDate.hour[0]=(pValue[0]/16) + '0';
				gs_LastDate.hour[1]=(pValue[0]%16) + '0';
				gs_LastDate.minute[0]=(pValue[1]/16) + '0';
				gs_LastDate.minute[1]=(pValue[1]%16) + '0';
				gs_LastDate.second[0]=(pValue[2]/16) + '0';
				gs_LastDate.second[1]=(pValue[2]%16) + '0';

				bTimeFound = TRUE;
			}
			if(ulTag == TAG_EMV_APPLI_PAN)
			{
				// Save value to send it to the VisaWave kernel
				if((nDataLength > 0) && (nDataLength <= 10))
				{
					gs_nLastPANLength = nDataLength;
					memcpy(gs_ucLastPAN,(unsigned char *)TlvTree_GetData(pResearch),nDataLength);
			
					bPANFound = TRUE;
				}
			}
			
			pResearch = TlvTree_GetNext (pResearch);
		}
	}

	// Double Dip processing
	// The reader cannot accept the same card to perform the same transaction twice
	if(bAmountFound && bDateFound && bTimeFound && bPANFound)
		__CST_VisaWave_CheckLastTransaction(TlvTransactionData);
}


//! \brief Check last transaction data contained in a TLV Tree node
//! \param[in] TlvTransactionData contains the current transaction data

static void __CST_VisaWave_CheckLastTransaction (TLV_TREE_NODE TlvTransactionData)
{
	unsigned char *pDate, *pTime, *pAmount;						// Current transaction data
	unsigned int nDateLength, nTimeLength, nAmountLength;		// Current transaction data
	DATE Date;													// Current transaction dates
	int iTimeGap, iDayGap;										// Number of days/seconds between the 2 transactions
	unsigned long ulDoubleDipTimeOut;							// Double Dip timeout (in milliseconds)
	int bSameAmount;
	
	TLV_TREE_NODE pTlvTmp;		// Node for Double Dip Timeout.
	
	// First, get the Double Dip timeout value
	if(!__CST_VisaWave_GetDoubleDipTimeOut (&ulDoubleDipTimeOut))
		return;

	// Init local data
	iDayGap = 0;
	iTimeGap = 0;
	bSameAmount = FALSE;

	// First get the data of the current transaction (Date, Time and Amount) from EP buffer
	pTlvTmp = TlvTree_Find(TlvTransactionData, TAG_EMV_AMOUNT_AUTH_NUM, 0);
	if (pTlvTmp != 0)
	{
		pAmount = TlvTree_GetData(pTlvTmp);
		nAmountLength = TlvTree_GetLength(pTlvTmp);
	}
	else
	{
		GTL_Traces_TraceDebug ("__CST_VisaWave_CheckLastTransaction : an error occured when getting the TAG_EMV_AMOUNT_AUTH_NUM tag");
		return;
	}

	pTlvTmp = TlvTree_Find(TlvTransactionData, TAG_EMV_TRANSACTION_DATE, 0);
	if (pTlvTmp != 0)
	{
		pDate = TlvTree_GetData(pTlvTmp);
		nDateLength = TlvTree_GetLength(pTlvTmp);
	}
	else
	{
		GTL_Traces_TraceDebug ("__CST_VisaWave_CheckLastTransaction : an error occured when getting the TAG_EMV_TRANSACTION_DATE tag");
		return;
	}

	pTlvTmp = TlvTree_Find(TlvTransactionData, TAG_EMV_TRANSACTION_TIME, 0);
	if (pTlvTmp != 0)
	{
		pTime = TlvTree_GetData(pTlvTmp);
		nTimeLength = TlvTree_GetLength(pTlvTmp);
	}
	else
	{
		GTL_Traces_TraceDebug ("__CST_VisaWave_CheckLastTransaction : an error occured when getting the TAG_EMV_TRANSACTION_TIME tag");
		return;
	}
	
	// Copy the current transaction Date/Time in a DATE structure
	Date.year[0]=(pDate[0]/16) + '0';
	Date.year[1]=(pDate[0]%16) + '0';
	Date.month[0]=(pDate[1]/16) + '0';
	Date.month[1]=(pDate[1]%16) + '0';
	Date.day[0]=(pDate[2]/16) + '0';
	Date.day[1]=(pDate[2]%16) + '0';
	Date.hour[0]=(pTime[0]/16) + '0';
	Date.hour[1]=(pTime[0]%16) + '0';
	Date.minute[0]=(pTime[1]/16) + '0';
	Date.minute[1]=(pTime[1]%16) + '0';
	Date.second[0]=(pTime[2]/16) + '0';
	Date.second[1]=(pTime[2]%16) + '0';

	// Check if the transaction amount is the same amount used for the last transaction
	if (memcmp(gs_ucLastAmount, pAmount, nAmountLength) == 0)
		bSameAmount = TRUE;
	
	iDayGap = CST_Common_NumberOfDaysBetweenTwoDates(&gs_LastDate,&Date);
	iTimeGap = SLSQ_Ecart_heure_minute_seconde(&gs_LastDate,&Date);	

	// Double dip check: the same card cannot perform the same transaction within the timeout.
	if(iDayGap == 1)
		iTimeGap += 24*3600; // Add one day in seconds (86400)

	
	if((iTimeGap > 0) && ((unsigned int) iTimeGap < (ulDoubleDipTimeOut/1000)) && (iDayGap == 0 || iDayGap == 1) && bSameAmount)
	{
		// Add the tag to the data sent to the VisaWave kernel
		TlvTree_AddChild(TlvTransactionData, TAG_VISAWAVE_LAST_TRANSACTION_PAN, gs_ucLastPAN, gs_nLastPANLength);
	}
}



//! \brief Get the double dip timeout value from the parameter file.
//! \param[out] pDoubleDipTimeOut the timeout value (in milliseconds).
//! \return
//!		- TRUE if tag is present.
//!		- FALSE else.

static int __CST_VisaWave_GetDoubleDipTimeOut (unsigned long *pDoubleDipTimeOut)
{
	TLV_TREE_NODE pTimeOut;		// Node for Double Dip Timeout.
	unsigned char * pValue;
	unsigned int nDataLength;
	
	pValue = NULL;
	nDataLength = 0;

	pTimeOut = TlvTree_Find(pTreeCurrentParam, TAG_SDSA_DOUBLE_DIP_TIMEOUT, 0);

	if (pTimeOut != NULL)
	{
		pValue = TlvTree_GetData(pTimeOut);
		nDataLength = TlvTree_GetLength(pTimeOut);
	}

	if ((pValue != NULL) && (nDataLength != 0))
	{
		GTL_Convert_BinNumberToUl(pValue, pDoubleDipTimeOut, nDataLength);
		return (TRUE);
	}

	return (FALSE);
}


//! \brief Check in the parameter file if the GUI mode to use is Visa Asia.

void CST_VisaWave_SetVisaAsiaGuiMode (void)
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
		if (pValue[0] == CLESS_GUI_MODE_VISA_ASIA)
		{
			gs_bIsVisaAsiaGuiMode = TRUE;
			return;
		}
	}

	gs_bIsVisaAsiaGuiMode = FALSE;
}
