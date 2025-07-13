/**
 * \file	ClessSample_Torn.c
 * \brief	This manages the torn transactions.
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
 */


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS				16			/*!< Max number of Torn Transaction Log Records. */
#define PAYPASS_TORN_RECORD_MAX_SIZE					2048		/*!< Max size of a Torn Record. */
#define MAX_LIFETIME_OF_TORN_TXN_LOG_RECORD_DEFAULT		0x12C		/*!< Maximum time, in seconds, that a record can remain in the Torn Transaction Log (300 seconds). */



/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

TLV_TREE_NODE pTreeTornTransactionLog = NULL;			/*!< Global TLV Tree used for Torn Transaction Log management. */
TLV_TREE_NODE gs_pTreeTornRecord = NULL;				/*!< Global TLV Tree used to identify the torn record used for the current transaction. */


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static unsigned long ClessSample_Torn_DateYYMMDDConvertToUl (const unsigned char * pDate);
static TLV_TREE_NODE __ClessSample_Torn_GetRecord (unsigned int nRecordPosition);
static int __ClessSample_Torn_CopyRecordInSharedBuffer (const unsigned long ulRecordTag, const TLV_TREE_NODE hRecord, T_SHARED_DATA_STRUCT * pOutputDataStruct);
static int __ClessSample_Torn_RemoveRecordFromLog(TLV_TREE_NODE *pTreeRecord);
static int __ClessSample_Torn_CleanOldRecord (DATE *pCurrentDate, int nlLifeTime);
static int __ClessSample_Torn_CopyRecordInTornLog (T_SHARED_DATA_STRUCT * pRecordDataStruct, TLV_TREE_NODE pTreeTornLog);
static int __ClessSample_Torn_AddRecordByDate (T_SHARED_DATA_STRUCT * pRecordDataStruct);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Convert a DCB coded date (YYMMDD) into an unsigned long.

static unsigned long ClessSample_Torn_DateYYMMDDConvertToUl (const unsigned char * pDate)
{
	unsigned char ucYear, ucMonth, ucDay;
	unsigned long ulConvertedDate;

	ucYear = pDate[0];
	ucMonth = pDate[1];
	ucDay = pDate[2];
	
	if (ucYear >= 0x50)
		ulConvertedDate = (0x19 << 24) + (ucYear << 16) + (ucMonth << 8) + ucDay;
	else
		ulConvertedDate = (0x20 << 24) + (ucYear << 16) + (ucMonth << 8) + ucDay;

	return (ulConvertedDate);
}


//! \brief Determine if the terminal supports the recovery processing.
//! \return
//!		- \a TRUE if it is supported.
//!		- \a FALSE if not.

int ClessSample_Torn_IsRecoverySupported (void)
{
	unsigned char *pMaxNumber;
	unsigned int nLength;

	if(ClessSample_Common_GetTagInTlvTree(pTreeCurrentParam, TAG_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS, &nLength, &pMaxNumber))
	{
		if(nLength == 1)
		{
			if(pMaxNumber[0] != 0)
				return (TRUE);
		}
	}

	return (FALSE);
}


//! \brief Get the maximum number of records that could be stored in the torn transaction log.
//! \return
//!		- \a The maximum number of torn transaction log records.
//!		- \a 0 if the terminal does not support the recovery processing.

unsigned int ClessSample_Torn_GetMaxNumberOfTornTxnLogRecords (void)
{
	unsigned int nMaxNumber = 0;
	unsigned char *pMaxNumber;
	unsigned int nLength;

	if(ClessSample_Common_GetTagInTlvTree(pTreeCurrentParam, TAG_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS, &nLength, &pMaxNumber))
	{
		if(nLength == 1)
		{
			nMaxNumber = pMaxNumber[0];
		}
	}

	if(nMaxNumber > MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS)
		nMaxNumber = MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS;

	return nMaxNumber;
}



//! \brief Get the number of torn transaction log records.

unsigned int ClessSample_Torn_GetNumberOfTornTxnLogRecords (void)
{
	TLV_TREE_NODE pRecord;
	unsigned int nRecordNumber = 0;

	if(pTreeTornTransactionLog != NULL)
	{
		pRecord = TlvTree_GetFirstChild(pTreeTornTransactionLog);
		
		while (pRecord != NULL)
		{
			nRecordNumber++;

			// Get the next record
			pRecord = TlvTree_GetNext(pRecord);
		}
	}

	return nRecordNumber;
}


//! \brief Get a record from the torn transaction log.
//! \param[in] nRecordPosition Position of the record in the torn transaction log (ie: if nRecordPosition is 1, the oldest record is returned).
//! \return
//!		- A pointer on the requested record node
//!		- NULL if a problem occurred

static TLV_TREE_NODE __ClessSample_Torn_GetRecord (unsigned int nRecordPosition)
{
	unsigned int i;
	TLV_TREE_NODE pRecord = NULL;
	
	if((pTreeTornTransactionLog != NULL) && (nRecordPosition > 0))
	{
		// Get the first record of the log
		pRecord = TlvTree_GetFirstChild(pTreeTornTransactionLog);
		
		// Get the requested record
		for(i = 1; (i < nRecordPosition) && (pRecord != NULL); i++)
			pRecord = TlvTree_GetNext(pRecord);
	}

	return (pRecord);
}



//! \brief Copy the given record in the shared buffer.
//! \param[in] ulRecordTag Tag to be added in the shared buffer. This tag will contain the record data.
//! \param[in] hRecord TLV Tree containing all the record data.
//! \param[out] pOutputDataStruct Shared buffer filled with the given record.
//! \return
//!		- \ref TRUE if correctly performed (data found and \a pOutputDataStruct filled).
//!		- \ref FALSE if an error occurred.

static int __ClessSample_Torn_CopyRecordInSharedBuffer (const unsigned long ulRecordTag, const TLV_TREE_NODE hRecord, T_SHARED_DATA_STRUCT * pOutputDataStruct)
{
	T_SHARED_DATA_STRUCT * pInternalDataStruct;
	TLV_TREE_NODE pCurrentTag;
	unsigned long ulTag, ulLength;
	int nResult = FALSE;
	int cr = STATUS_SHARED_EXCHANGE_ERROR;

	ulTag = 0;
	ulLength = 0;

	// Create an internal data structure to create the torn transaction record
	pInternalDataStruct = GTL_SharedExchange_InitLocal (PAYPASS_TORN_RECORD_MAX_SIZE);

	if((pInternalDataStruct != NULL) && (hRecord != NULL))
	{
		// Add each tag of the stored record in the data structure

		pCurrentTag = TlvTree_GetFirstChild(hRecord);
		
		if (pCurrentTag != NULL)
		{
			ulTag = TlvTree_GetTag(pCurrentTag);
			ulLength = TlvTree_GetLength(pCurrentTag);
		}

		while ((pCurrentTag != NULL) && (ulLength != 0))
		{
			// Add the tag in the internal structure to create the record.
			cr = GTL_SharedExchange_AddTag (pInternalDataStruct, ulTag, ulLength, TlvTree_GetData(pCurrentTag));
			if (cr != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_Traces_TraceDebug ("__ClessSample_Torn_CopyRecordInSharedBuffer : An error occurred when adding the tag from torn transaction log to the exchange data structure (tag is provided) (Tag = %02lx) (GTL status = %02x)\n", ulTag, cr);
				nResult = FALSE;
				break;
			}

			// Get the next tag in the record
			pCurrentTag = TlvTree_GetNext(pCurrentTag);

			if (pCurrentTag != NULL)
			{
				ulTag = TlvTree_GetTag(pCurrentTag);
				ulLength = TlvTree_GetLength(pCurrentTag);
			}
		}

		if(cr == STATUS_SHARED_EXCHANGE_OK) // At least one tag has been added to the internal data structure (record is not empty)
		{
			// Torn transaction record is constructed, add it to the output buffer
			if (GTL_SharedExchange_AddTag (pOutputDataStruct, ulRecordTag, pInternalDataStruct->ulDataLength, pInternalDataStruct->nPtrData) == STATUS_SHARED_EXCHANGE_OK)
			{
				nResult = TRUE;
			}
			else
			{
				GTL_Traces_TraceDebug ("__ClessSample_Torn_CopyRecordInSharedBuffer : Not enough memory in the structure to add the record (Tag = %02lx)\n", ulRecordTag);
				nResult = FALSE;
			}
		}

		// Free the allocated buffer
		GTL_SharedExchange_DestroyLocal (pInternalDataStruct);
	}

	return (nResult);
}


//! \brief Remove the given record from the torn transaction log.
//! \param[in] pTreeRecord Record to remove.
//!		- TRUE if the record has been correctly removed, FALSE else.

static int __ClessSample_Torn_RemoveRecordFromLog(TLV_TREE_NODE *pTreeRecord)
{
	if (pTreeRecord != NULL)
	{
		if (*pTreeRecord != NULL)
		{
			TlvTree_Release(*pTreeRecord);
			*pTreeRecord = NULL;
			return (TRUE);
		}
	}
	
	return (FALSE);
}


//! \brief Check if the current transaction is a torn transaction (if it appears in the torn transaction log).
//! \param[in/out] pSharedDataStruct Shared buffer filled with the transaction information (PAN, PAN sequence number...).
//!									 Output buffer is filled with the torn record in the case of a torn transaction.
//! \return
//!		- TRUE if the transaction is in the torn transaction log, FALSE else.


int ClessSample_Torn_IsTornTxn(T_SHARED_DATA_STRUCT * pSharedDataStruct)
{
	int nPosition;
	const unsigned char * pPan = NULL;
	const unsigned char * pPanSeqNumber = NULL;
	unsigned long ulPanLength = 0;
	unsigned long ulPanSeqNbLength = 0;
	unsigned char * pValue = NULL;
	unsigned int nDataLength;
	int nRecordNumber;
	int nCurrentRecord;
	int bIsTornTransaction;
	TLV_TREE_NODE pRecord;
	TLV_TREE_NODE pNode;


	bIsTornTransaction = FALSE;

	// Init the variable that identify a torn record during a transaction
	if (gs_pTreeTornRecord != NULL)
		gs_pTreeTornRecord = NULL;

	// Get the PAN
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	if (GTL_SharedExchange_FindNext (pSharedDataStruct, &nPosition, TAG_EMV_APPLI_PAN, &ulPanLength, &pPan) != STATUS_SHARED_EXCHANGE_OK)
	{
		// Pan is missing, we cannot check the Torn Transaction List
		GTL_Traces_TraceDebug ("ClessSample_Torn_IsTornTxn : PAN is missing for Torn Transaction List checking");
		return (FALSE);
	}

	// Get the PAN Sequence Number
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	if (GTL_SharedExchange_FindNext (pSharedDataStruct, &nPosition, TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER, &ulPanSeqNbLength, &pPanSeqNumber) != STATUS_SHARED_EXCHANGE_OK)
	{
		// Pan Sequence Number is not present
		GTL_Traces_TraceDebug ("ClessSample_Torn_IsTornTxn : PAN Sequence Number is not present for Torn Transaction List checking");
		pPanSeqNumber = NULL;
	}

	// Clear the output structure and fill it with the torn transaction record in the case of a torn transaction.
	GTL_SharedExchange_ClearEx (pSharedDataStruct, FALSE);
	
	// Check torn transaction log presence
	if(pTreeTornTransactionLog != NULL)
	{
		// Get the number of torn records stored in the log.
		nRecordNumber = ClessSample_Torn_GetNumberOfTornTxnLogRecords();
		
		// For every record in torn transaction log, check for a matching entry (i.e. entry with the same PAN and same PAN Sequence Number)
		for(nCurrentRecord = nRecordNumber; nCurrentRecord > 0; nCurrentRecord--) // Search starts from the most recent record
		{
			pRecord = __ClessSample_Torn_GetRecord(nCurrentRecord);

			if (pRecord != NULL)
			{
				// Get the PAN in the record
				pNode = TlvTree_Find(pRecord, TAG_EMV_APPLI_PAN, 0);

				if (pNode != NULL)
				{
					pValue = TlvTree_GetData(pNode);
					nDataLength = TlvTree_GetLength(pNode);
					if((nDataLength == ulPanLength) && (memcmp(pValue, pPan, ulPanLength) == 0))
					{
						// Same PAN
						// Check if PAN Sequence Number is the same (if available)
						pNode = TlvTree_Find(pRecord, TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER, 0);

						if ((pNode != NULL) && (pPanSeqNumber != NULL))
						{
							pValue = TlvTree_GetData(pNode);
							nDataLength = TlvTree_GetLength(pNode);
							if((nDataLength == ulPanSeqNbLength) && (memcmp (pValue, pPanSeqNumber, ulPanSeqNbLength) == 0))
							{
								// Record with the same PAN and same PAN Sequence Number.
								bIsTornTransaction = TRUE;
							}
						}
						if ((pNode == NULL) && (pPanSeqNumber == NULL))
						{
							// Record with the same PAN (PAN Sequence Number not present)..
							bIsTornTransaction = TRUE;
						}

						if(bIsTornTransaction)
						{
							// Copy the record in the exchange buffer to indicate PayPass kernel it is a torn transaction.
							gs_pTreeTornRecord = pRecord;
							return(__ClessSample_Torn_CopyRecordInSharedBuffer(TAG_PAYPASS_TORN_RECORD, pRecord, pSharedDataStruct));
						}
					}
				}
			}
		}
	}

	return (FALSE);
}


//! \brief Update the torn transaction log by adding a new record according to its date and time.
//! \param[in/out] pRecordDataStruct Shared buffer filled with the transaction data that must be added in a new record.
//! \return
//!		- TRUE if the record has been correctly added in the torn transaction log, FALSE else.

static int __ClessSample_Torn_AddRecordByDate (T_SHARED_DATA_STRUCT * pRecordDataStruct)
{
	int nPosition;
	const unsigned char *pDate, *pTime;		
	unsigned char *pRecordDate, *pRecordTime;
	unsigned long ulDateLength, ulTimeLength;
	TLV_TREE_NODE pTempTornLog, pRecord, pTlvTmp;
	unsigned long ulDate, ulRecordDate, ulTime, ulRecordTime;
	int bAddRecord;


	// Get the date of the record to add
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	if (GTL_SharedExchange_FindNext (pRecordDataStruct, &nPosition, TAG_EMV_TRANSACTION_DATE, &ulDateLength, &pDate) != STATUS_SHARED_EXCHANGE_OK)
	{
		// Date is missing in the record to add
		GTL_Traces_TraceDebug ("__ClessSample_Torn_AddRecordByDate : Date is missing in the record to add");
		return (FALSE);
	}

	// Get the time of the record to add
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	if (GTL_SharedExchange_FindNext (pRecordDataStruct, &nPosition, TAG_EMV_TRANSACTION_TIME, &ulTimeLength, &pTime) != STATUS_SHARED_EXCHANGE_OK)
	{
		// Time is missing in the record to add
		GTL_Traces_TraceDebug ("__ClessSample_Torn_AddRecordByDate : Time is missing in the record to add");
		return (FALSE);
	}

	// Create a temp torn log
	pTempTornLog = TlvTree_New(0);
	if (pTempTornLog == NULL)
	{
		GTL_Traces_TraceDebug ("__ClessSample_Torn_AddRecordByDate : Cannot create the temp TlvTree");
		return (FALSE);
	}

	// New record has not been added yet
	bAddRecord = FALSE;

	// Check were the new record must be inserted by comparing its date/time with each record in the torn transaction log
	pRecord = TlvTree_GetFirstChild(pTreeTornTransactionLog);

	while (pRecord != NULL)
	{
		// If the new record has not been added yet, check its date and time
		if(!bAddRecord)
		{
			// Get the Date in the record
			pTlvTmp = TlvTree_Find(pRecord, TAG_EMV_TRANSACTION_DATE, 0);
			if (pTlvTmp != NULL)
			{
				pRecordDate = TlvTree_GetData(pTlvTmp);
			}
			else
			{
				GTL_Traces_TraceDebug ("__ClessSample_Torn_AddRecordByDate : an error occurred when getting the TAG_EMV_TRANSACTION_DATE tag in the record");
				return (FALSE);
			}

			// Get the Time in the record
			pTlvTmp = TlvTree_Find(pRecord, TAG_EMV_TRANSACTION_TIME, 0);
			if (pTlvTmp != NULL)
			{
				pRecordTime = TlvTree_GetData(pTlvTmp);
			}
			else
			{
				GTL_Traces_TraceDebug ("__ClessSample_Torn_AddRecordByDate : an error occurred when getting the TAG_EMV_TRANSACTION_TIME tag in the record");
				return (FALSE);
			}

			// Convert the dates
			ulDate = ClessSample_Torn_DateYYMMDDConvertToUl (pDate);
			ulRecordDate = ClessSample_Torn_DateYYMMDDConvertToUl (pRecordDate);
		
			// Compare the dates
			if(ulDate == ulRecordDate)
			{
				// Convert the times
				ulTime = (pTime[0] << 16) + (pTime[1] << 8) + pTime[2];
				ulRecordTime = (pRecordTime[0] << 16) + (pRecordTime[1] << 8) + pRecordTime[2];

				if(ulTime < ulRecordTime)
				{
					// The record to add is older than the current record from the torn log. The new record must be inserted here in the torn log.
					bAddRecord = TRUE;
				}
			}
			else if(ulDate < ulRecordDate)
			{
				// The record to add is older than the current record from the torn log.  The new record must be inserted here in the torn log
				bAddRecord = TRUE;
			}

			if(bAddRecord)
			{
				// The new record is inserted in the torn log
				__ClessSample_Torn_CopyRecordInTornLog(pRecordDataStruct, pTempTornLog);
			}
		}
		
		// Copy the record
		pTlvTmp = TlvTree_Copy(pRecord);
		if(pTlvTmp == NULL)
		{
			GTL_Traces_TraceDebug ("__ClessSample_Torn_AddRecordByDate : TlvTree_Copy failed");
			return (FALSE);
		}
		if(TlvTree_Graft(pTempTornLog, pTlvTmp) != TLV_TREE_OK)
		{
			GTL_Traces_TraceDebug ("__ClessSample_Torn_AddRecordByDate : TlvTree_Graft failed");
			return (FALSE);
		}

		// Get the next record of the torn log
		pRecord = TlvTree_GetNext(pRecord);
	}

	// If the new record has not been added yet, it is added at the end of the tree
	if(!bAddRecord)
		__ClessSample_Torn_CopyRecordInTornLog(pRecordDataStruct, pTempTornLog);

	// Update the torn transaction log
	TlvTree_Release(pTreeTornTransactionLog);
	pTreeTornTransactionLog = pTempTornLog;

	return (TRUE);
}  


//! \brief Add a new record in the torn transaction log.
//! \param[in] pRecordDataStruct Shared buffer filled with the transaction data that must be added in a new record.
//! \param[in] pTreeTornLog Torn transaction log to be updated.
//! \return
//!		- TRUE if the record has been correctly added in the torn transaction log, FALSE else.

static int __ClessSample_Torn_CopyRecordInTornLog (T_SHARED_DATA_STRUCT * pRecordDataStruct, TLV_TREE_NODE pTreeTornLog)
{
	int nPosition, nResult;
	TLV_TREE_NODE pTreeNewRecord;
	unsigned long ulReadTag;
	unsigned long ulReadLength;
	unsigned char *pReadValue;

	// Init position
	nPosition = SHARED_EXCHANGE_POSITION_NULL;

	// Create a new record (add a child in the torn transaction log tree)
	pTreeNewRecord = TlvTree_AddChild (pTreeTornLog, TAG_PAYPASS_TORN_RECORD, NULL, 0);
	if (pTreeNewRecord == NULL)
	{
		GTL_Traces_TraceDebug ("__ClessSample_Torn_CopyRecordInTornLog : Cannot create a new record in the torn transaction log");
		return (FALSE);
	}

	// Parse the structure that contains the record to add and store every tag in the new record
	do
	{
		// Try to get following tag.
		nResult = GTL_SharedExchange_GetNext (pRecordDataStruct, &nPosition, &ulReadTag, &ulReadLength, (const unsigned char **)&pReadValue);

		if (nResult == STATUS_SHARED_EXCHANGE_OK) // If tag found
		{
			TlvTree_AddChild (pTreeNewRecord, ulReadTag, pReadValue, ulReadLength);
		}
	} while (nResult == STATUS_SHARED_EXCHANGE_OK);

	return(TRUE);
}



//! \brief Add the current transaction in a new record in the torn transaction log. Remove the oldest record if maximum number is exceeded.
//! \param[in/out] pSharedDataStruct Shared buffer filled with the transaction record to add in the log (PAN, PAN sequence number....).
//!									 Output buffer is filled with the removed record if maximum number of record is exceeded.
//! \return
//!		- TRUE if the record has been correctly added in the torn transaction log, FALSE else.

int ClessSample_Torn_AddRecord(T_SHARED_DATA_STRUCT * pSharedDataStruct)
{
	int nPosition;
	const unsigned char * pRecord = NULL;
	unsigned long ulRecordLength = 0;
	const unsigned char * pDoNotRemoveLog = NULL;
	int bKeepRecord = FALSE;
	unsigned long ulDoNotRemoveLogLength = 0;
	T_SHARED_DATA_STRUCT tDataStructure;
	TLV_TREE_NODE pTreeOldRecord;


	// Kernel C2, S11.E12 (v2)
	// In the case of a recovered transaction that is torned for a second time, the old record must be removed before adding the new torn transaction record in the log.
	// This record shall not be removed if tag TAG_PAYPASS_INT_DO_NOT_REMOVE_TORN_RECORD is present and set to '01'
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	if (GTL_SharedExchange_FindNext (pSharedDataStruct, &nPosition, TAG_PAYPASS_INT_DO_NOT_REMOVE_TORN_RECORD, &ulDoNotRemoveLogLength, &pDoNotRemoveLog) == STATUS_SHARED_EXCHANGE_OK)
	{
		// TAG_PAYPASS_INT_DO_NOT_REMOVE_TORN_RECORD is present, check if value is '01'
		bKeepRecord = (ulDoNotRemoveLogLength == 1) && (pDoNotRemoveLog[0] == 0x01);
	}

	if (!bKeepRecord)
	{
		ClessSample_Torn_RemoveRecord();
	}
	
	// Check torn transaction log presence
	if(pTreeTornTransactionLog == NULL)
	{
		// Create the Torn Transaction Log
		pTreeTornTransactionLog = TlvTree_New(0);
		if (pTreeTornTransactionLog == NULL)
		{
			GTL_Traces_TraceDebug ("ClessSample_Torn_AddRecord : Cannot create the torn transaction log TlvTree");
			return (FALSE);
		}
	}

	// Get the Record to add in the torn transaction log
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	if (GTL_SharedExchange_FindNext (pSharedDataStruct, &nPosition, TAG_PAYPASS_TORN_RECORD, &ulRecordLength, &pRecord) != STATUS_SHARED_EXCHANGE_OK)
	{
		// Torn record is missing for adding a new record in the torn transaction log
		GTL_Traces_TraceDebug ("ClessSample_Torn_IsTornTxn : TAG_PAYPASS_TORN_RECORD is missing for adding a new record in the torn transaction log");
		return (FALSE);
	}

	// Init a parsing structure to parse the torn transaction record
	GTL_SharedExchange_InitEx (&tDataStructure, ulRecordLength, ulRecordLength, (unsigned char *)pRecord);

	// Add the record in the torn transaction log according to its date and time
	__ClessSample_Torn_AddRecordByDate (&tDataStructure);

	
	// The new record has been correctly added to the torn transaction log.
	// If adding this new record to the log means that an old record is removed (maximum number of torn transaction log records exceeded), then the old record is sent to the kernel (in the output structure).

	// Clear the output structure.
	GTL_SharedExchange_ClearEx (pSharedDataStruct, FALSE);
		
	// Check if maximum number of torn transaction log records exceeded
	if(ClessSample_Torn_GetNumberOfTornTxnLogRecords() > ClessSample_Torn_GetMaxNumberOfTornTxnLogRecords())
	{
		GTL_Traces_TraceDebug ("ClessSample_Torn_AddRecord : Maximum number of torn transaction log records exceeded, oldest record is removed");
		
		// Add the oldest record in the output structure
		pTreeOldRecord = __ClessSample_Torn_GetRecord(1);
		if (pTreeOldRecord != NULL)
			__ClessSample_Torn_CopyRecordInSharedBuffer(TAG_PAYPASS_OLD_TORN_RECORD, pTreeOldRecord, pSharedDataStruct);
		
		// Remove the oldest record from the torn transaction log
		__ClessSample_Torn_RemoveRecordFromLog(&pTreeOldRecord);
	}

	return (TRUE);
}



//! \brief Remove the current transaction record from the torn transaction log.
//! \return
//!		- TRUE if the record has been correctly removed from the torn transaction log, FALSE else.

int ClessSample_Torn_RemoveRecord(void)
{
	return(__ClessSample_Torn_RemoveRecordFromLog(&gs_pTreeTornRecord));
}



//! \brief Dump the torn transaction log (each record content).

void ClessSample_Torn_PrintLog (void)
{
	TLV_TREE_NODE pRecord = NULL;
	int bIsEmpty = TRUE;
	

	if(pTreeTornTransactionLog != NULL)
	{
		ClessSample_DumpData_DumpTitle ("Torn Transaction Log :");

		// Get the first record of the log
		pRecord = TlvTree_GetFirstChild(pTreeTornTransactionLog);
		
		while (pRecord != NULL)
		{
			if(bIsEmpty)
				bIsEmpty = FALSE;

			// Dump the record
			ClessSample_DumpData_DumpTlvTreeNodeWithTitle ("RECORD", pRecord);

			// Get the next record
			pRecord = TlvTree_GetNext(pRecord);
		}
	}

	if(bIsEmpty)
		ClessSample_DumpData_DumpTitle ("Log is empty");
}



//! \brief Clean up the Torn Transaction log by removing torn transaction that were not recovered and that have been aged off the log.
//! \param[in] pCurrentDate Date to be compared with the date in a record.
//! \param[in] nlLifeTime Maximum time, in seconds, that a record can remain in the Torn Transaction Log.
//! \return
//!		- TRUE a aged off record has been removed from the torn transaction log, FALSE else.

static int __ClessSample_Torn_CleanOldRecord (DATE *pCurrentDate, int nlLifeTime)
{
	TLV_TREE_NODE pRecord, pTlvTmp;
	unsigned char *pDate, *pTime;			
	unsigned int nDateLength, nTimeLength;
    DATE RecordDate;
	int iTimeGap, iDayGap, iGapInSeconds;
	T_SHARED_DATA_STRUCT *pOutputTransactionDataStruct, *pOldRecordDataStruct;
	int cr, bOldRecordRemoved;
	unsigned char pPayPassOutcomeParameterSet[]={PAYPASS_OPS_STATUS_END_APPLICATION,
												 PAYPASS_OPS_START_NA,
												 PAYPASS_OPS_ONLINE_RESPONSE_DATA_NA,
												 PAYPASS_OPS_CVM_NA,
												 PAYPASS_OPS_DATA_PRESENCE_MASK_DISCRET_DATA,
												 PAYPASS_OPS_ALTERNATIVE_INTERFACE_PREF_NA,
												 PAYPASS_OPS_FIELD_OFF_REQUEST_NA,
												 0};

	bOldRecordRemoved = FALSE;

	// Create internal data structures that will contain the OUT signals (OPS and discretionary data)
	pOutputTransactionDataStruct = GTL_SharedExchange_InitLocal (PAYPASS_TORN_RECORD_MAX_SIZE + PAYPASS_OPS_LENGTH);
	pOldRecordDataStruct = GTL_SharedExchange_InitLocal (PAYPASS_TORN_RECORD_MAX_SIZE);
	if((pOutputTransactionDataStruct == NULL) || (pOldRecordDataStruct == NULL)) 
	{
		GTL_Traces_TraceDebug ("__ClessSample_Torn_CleanOldRecord : Unable to create buffers");
		return (FALSE);
	}

	if(pTreeTornTransactionLog != NULL)
	{
		// Get the first record of the log
		pRecord = TlvTree_GetFirstChild(pTreeTornTransactionLog);
		
		if (pRecord != NULL)
		{
			// Get the Date in the record
			pTlvTmp = TlvTree_Find(pRecord, TAG_EMV_TRANSACTION_DATE, 0);
			if (pTlvTmp != NULL)
			{
				pDate = TlvTree_GetData(pTlvTmp);
				nDateLength = TlvTree_GetLength(pTlvTmp);
			}
			else
			{
				GTL_Traces_TraceDebug ("__ClessSample_Torn_CleanOldRecord : an error occurred when getting the TAG_EMV_TRANSACTION_DATE tag in the record");
				return (FALSE);
			}

			// Get the Time in the record
			pTlvTmp = TlvTree_Find(pRecord, TAG_EMV_TRANSACTION_TIME, 0);
			if (pTlvTmp != NULL)
			{
				pTime = TlvTree_GetData(pTlvTmp);
				nTimeLength = TlvTree_GetLength(pTlvTmp);
			}
			else
			{
				GTL_Traces_TraceDebug ("__ClessSample_Torn_CleanOldRecord : an error occurred when getting the TAG_EMV_TRANSACTION_TIME tag in the record");
				return (FALSE);
			}

			// Copy the current transaction Date/Time in a DATE structure
			RecordDate.year[0]=(pDate[0]/16) + '0';
			RecordDate.year[1]=(pDate[0]%16) + '0';
			RecordDate.month[0]=(pDate[1]/16) + '0';
			RecordDate.month[1]=(pDate[1]%16) + '0';
			RecordDate.day[0]=(pDate[2]/16) + '0';
			RecordDate.day[1]=(pDate[2]%16) + '0';
			RecordDate.hour[0]=(pTime[0]/16) + '0';
			RecordDate.hour[1]=(pTime[0]%16) + '0';
			RecordDate.minute[0]=(pTime[1]/16) + '0';
			RecordDate.minute[1]=(pTime[1]%16) + '0';
			RecordDate.second[0]=(pTime[2]/16) + '0';
			RecordDate.second[1]=(pTime[2]%16) + '0';


			// Get the number of days between the two dates.
			iDayGap = ClessSample_Common_NumberOfDaysBetweenTwoDates (&RecordDate, pCurrentDate);

			// Get the number of seconds between the two dates.
			iTimeGap = SLSQ_Ecart_heure_minute_seconde(&RecordDate,pCurrentDate);

			if(iDayGap >= 0)
			{
				iGapInSeconds = (iDayGap*24*3600) + iTimeGap ;

				if(iGapInSeconds > nlLifeTime)
				{
					// The record must be removed from the torn transaction log.
					
					// Copy the content of the old record in the TAG_PAYPASS_TORN_RECORD_IN_DISCRETIONARY_DATA tag 
					__ClessSample_Torn_CopyRecordInSharedBuffer(TAG_PAYPASS_TORN_RECORD_IN_DISCRETIONARY_DATA, pRecord, pOldRecordDataStruct);
					
					// Remove the old record from the torn transaction log
					__ClessSample_Torn_RemoveRecordFromLog(&pRecord);
					
					bOldRecordRemoved = TRUE;
				}
			}
		}
	}

	// Set the outcome parameter set
	cr = GTL_SharedExchange_AddTag (pOutputTransactionDataStruct, TAG_PAYPASS_OUTCOME_PARAMETER_SET, PAYPASS_OPS_LENGTH, pPayPassOutcomeParameterSet);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug ("__ClessSample_Torn_CleanOldRecord : An error occurred when adding the tag TAG_PAYPASS_OUTCOME_PARAMETER_SET in the structure (GTL status = %02x)\n", cr);
		return (FALSE);
	}

	// Add the old record in the discretionary data
	cr = GTL_SharedExchange_AddTag (pOutputTransactionDataStruct, TAG_PAYPASS_DISCRETIONARY_DATA, pOldRecordDataStruct->ulDataLength, pOldRecordDataStruct->nPtrData);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug ("__ClessSample_Torn_CleanOldRecord : An error occurred when adding the tag TAG_PAYPASS_DISCRETIONARY_DATA in the structure (GTL status = %02x)\n", cr);
		return (FALSE);
	}

	// Add the outcome parameter set and the discretionary data to the transaction log
	if(ClessSample_Menu_IsTransactionDataDumpingOn()) 
	{
		ClessSample_PayPass_DumpSpecificStructure (pOutputTransactionDataStruct, TAG_PAYPASS_OUTCOME_PARAMETER_SET, FALSE);
		ClessSample_PayPass_DumpSpecificStructure (pOutputTransactionDataStruct, TAG_PAYPASS_DISCRETIONARY_DATA, FALSE);
	}
						
	// Dump the transaction log
	ClessSample_PayPass_DumpTransationDataLog ();

	// Free the allocated buffers
	GTL_SharedExchange_DestroyLocal (pOutputTransactionDataStruct);
	GTL_SharedExchange_DestroyLocal (pOldRecordDataStruct);

	if(bOldRecordRemoved)
		return (TRUE);
	else
		return (FALSE);
}



//! \brief Management if Torn Log Lifetime is empty.

static void __ClessSample_Torn_ManageEmptyTornLogLifetimeOrMessageHoldTime (void)
{
	T_SHARED_DATA_STRUCT *pOutputTransactionDataStruct, *pDiscretionaryDataStruct;
	int cr;
	unsigned int nMessageHoldTimeLength;
	unsigned char *pMessageHoldTimeValue;
	unsigned char pPayPassOutcomeParameterSet[]={PAYPASS_OPS_STATUS_END_APPLICATION,
												 PAYPASS_OPS_START_NA,
												 PAYPASS_OPS_ONLINE_RESPONSE_DATA_NA,
												 PAYPASS_OPS_CVM_NA,
												 PAYPASS_OPS_DATA_PRESENCE_MASK_DISCRET_DATA,
												 PAYPASS_OPS_ALTERNATIVE_INTERFACE_PREF_NA,
												 PAYPASS_OPS_FIELD_OFF_REQUEST_NA,
												 0};

	unsigned char pPayPassErrorIndication[] = {	PAYPASS_EI_L1_OK,
												PAYPASS_EI_L2_TERMINAL_DATA_ERROR,
												PAYPASS_EI_L3_OK,
												0, 0,
												PAYPASS_UIRD_MESSAGE_ID_ERROR_OTHER_CARD};

	unsigned char pPayPassUird[] = {	PAYPASS_UIRD_MESSAGE_ID_ERROR_OTHER_CARD,
										PAYPASS_UIRD_STATUS_NOT_READY,
										0, 0, 0, // Message Hold Time
										0, 0, 0, 0, 0, 0, 0, 0, // Language preference
										PAYPASS_UIRD_VALUE_QUALIFIER_NONE,
										0, 0, 0, 0, 0, 0, // Value
										0, 0}; // Currency code



	// Create internal data structures that will contain the OUT signals (OPS and discretionary data)
	pOutputTransactionDataStruct = GTL_SharedExchange_InitLocal (1024);
	pDiscretionaryDataStruct = GTL_SharedExchange_InitLocal (512);
	if((pOutputTransactionDataStruct == NULL) || (pDiscretionaryDataStruct == NULL)) 
	{
		GTL_Traces_TraceDebug ("__ClessSample_Torn_ManageEmptyTornLogLifetime : Unable to create buffers");
		return;
	}


	// Get the Message Hold Time from the parameter files, if present
	if (ClessSample_Common_GetTagInTlvTree(pTreeCurrentParam, TAG_PAYPASS_DEFAULT_HOLD_TIME, &nMessageHoldTimeLength, &pMessageHoldTimeValue))
	{
		if (nMessageHoldTimeLength == PAYPASS_UIRD_HOLD_TIME_LENGTH)
		{
			pPayPassUird[PAYPASS_UIRD_HOLD_TIME_OFFSET] = pMessageHoldTimeValue[0];
			pPayPassUird[PAYPASS_UIRD_HOLD_TIME_OFFSET+1] = pMessageHoldTimeValue[1];
			pPayPassUird[PAYPASS_UIRD_HOLD_TIME_OFFSET+2] = pMessageHoldTimeValue[2];
		}
	}
	else
	{
		// Set the Message Hold Time to the default value : 00 00 13
		pPayPassUird[PAYPASS_UIRD_HOLD_TIME_OFFSET] = 0x00;
		pPayPassUird[PAYPASS_UIRD_HOLD_TIME_OFFSET+1] = 0x00;
		pPayPassUird[PAYPASS_UIRD_HOLD_TIME_OFFSET+2] = 0x13;
	}


	// Add the UIRD
	cr = GTL_SharedExchange_AddTag (pOutputTransactionDataStruct, TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA, PAYPASS_UIRD_LENGTH, pPayPassUird);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug ("__ClessSample_Torn_CleanOldRecord : An error occurred when adding the tag TAG_PAYPASS_OUTCOME_PARAMETER_SET in the structure (GTL status = %02x)\n", cr);
		return;
	}

	// Set the outcome parameter set
	cr = GTL_SharedExchange_AddTag (pOutputTransactionDataStruct, TAG_PAYPASS_OUTCOME_PARAMETER_SET, PAYPASS_OPS_LENGTH, pPayPassOutcomeParameterSet);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug ("__ClessSample_Torn_CleanOldRecord : An error occurred when adding the tag TAG_PAYPASS_OUTCOME_PARAMETER_SET in the structure (GTL status = %02x)\n", cr);
		return;
	}

	// Add the Error Indication in the Discretionary Data
	cr = GTL_SharedExchange_AddTag (pOutputTransactionDataStruct, TAG_PAYPASS_ERROR_INDICATION, PAYPASS_EI_LENGTH, pPayPassErrorIndication);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug ("__ClessSample_Torn_ManageEmptyTornLogLifetime : An error occurred when adding the tag TAG_PAYPASS_ERROR_INDICATION in the structure (GTL status = %02x)\n", cr);
		return;
	}

	// Add the Error Indication in the Discretionary Data
	cr = GTL_SharedExchange_AddTag (pDiscretionaryDataStruct, TAG_PAYPASS_ERROR_INDICATION, PAYPASS_EI_LENGTH, pPayPassErrorIndication);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug ("__ClessSample_Torn_ManageEmptyTornLogLifetime : An error occurred when adding the tag TAG_PAYPASS_ERROR_INDICATION in the structure (GTL status = %02x)\n", cr);
		return;
	}

	// Add the old record in the discretionary data
	cr = GTL_SharedExchange_AddTag (pOutputTransactionDataStruct, TAG_PAYPASS_DISCRETIONARY_DATA, pDiscretionaryDataStruct->ulDataLength, pDiscretionaryDataStruct->nPtrData);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug ("__ClessSample_Torn_CleanOldRecord : An error occurred when adding the tag TAG_PAYPASS_DISCRETIONARY_DATA in the structure (GTL status = %02x)\n", cr);
		return;
	}

	// Display the message
	ClessSample_GuiState_DisplayScreenText (CLESS_SAMPLE_SCREEN_ERROR, PSQ_Give_Language(), PSQ_Give_Language());

	// Add the outcome parameter set and the discretionary data to the transaction log
	if(ClessSample_Menu_IsTransactionDataDumpingOn()) 
	{
		ClessSample_PayPass_DumpSpecificStructure (pOutputTransactionDataStruct, TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA, FALSE);
		ClessSample_PayPass_DumpSpecificStructure (pOutputTransactionDataStruct, TAG_PAYPASS_OUTCOME_PARAMETER_SET, FALSE);
		ClessSample_PayPass_DumpSpecificStructure (pOutputTransactionDataStruct, TAG_PAYPASS_ERROR_INDICATION, FALSE);
		ClessSample_PayPass_DumpSpecificStructure (pOutputTransactionDataStruct, TAG_PAYPASS_DISCRETIONARY_DATA, FALSE);
	}
						
	// Dump the transaction log
	ClessSample_PayPass_DumpTransationDataLog ();

	// Free the allocated buffers
	GTL_SharedExchange_DestroyLocal (pOutputTransactionDataStruct);
	GTL_SharedExchange_DestroyLocal (pDiscretionaryDataStruct);
}



//! \brief Clean up the Torn Transaction log by removing torn records that were not recovered and that have been aged off the log.

void ClessSample_Torn_CleanLog (void)
{
	DATE CurrentDate;
	unsigned int nLifeTimeLength;
	unsigned char *pLifeTimeValue;
	unsigned int nMessageHoldTimeLength;
	unsigned char *pMessageHoldTimeValue;
	unsigned long ulLifeTime;
	int nResult;
	int bEmptyLifeTime = FALSE;
	int bEmptyMessageHoldTime = FALSE;

	// Read the current date and time
	if (read_date(&CurrentDate) != OK) 
		return;

	// Get the maximum time, in seconds, that a record can remain in the Torn Transaction Log
	if(ClessSample_Common_GetTagInTlvTree(pTreeCurrentParam, TAG_PAYPASS_MAX_LIFETIME_OF_TORN_TXN_LOG_RECORD, &nLifeTimeLength, &pLifeTimeValue))
	{
		if (nLifeTimeLength != 0)
			GTL_Convert_BinNumberToUl(pLifeTimeValue, &ulLifeTime, nLifeTimeLength);
		else // Present with zero length
			bEmptyLifeTime = TRUE;
	}
	else
	{
		// Tag is not available, the default value will be used
		ulLifeTime = MAX_LIFETIME_OF_TORN_TXN_LOG_RECORD_DEFAULT;	// 300 seconds
	}

	// Get the message hold time, and check it is not empty
	if (ClessSample_Common_GetTagInTlvTree(pTreeCurrentParam, TAG_PAYPASS_DEFAULT_HOLD_TIME, &nMessageHoldTimeLength, &pMessageHoldTimeValue))
	{
		if (nMessageHoldTimeLength != PAYPASS_UIRD_HOLD_TIME_LENGTH)
			bEmptyMessageHoldTime = TRUE;
	}

	// Remove each record that has been aged off
	if ((!bEmptyLifeTime) && (!bEmptyMessageHoldTime))
	{
		do
		{
			nResult = __ClessSample_Torn_CleanOldRecord(&CurrentDate, (int) ulLifeTime);
		}while(nResult);
	}
	else
	{
		// Torn Log Lifetime is empty
		__ClessSample_Torn_ManageEmptyTornLogLifetimeOrMessageHoldTime ();
	}
}
