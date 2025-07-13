/**
 * \file	CST_Batch.c
 * \brief	To manage the transaction batch as well as the transaction sequence counter.
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

#define SAMPLE_TSC_MAX_VALUE				(99999999)			/*!< Defines the maximum value of transaction sequence counter. */
#define FILE_TSC_LABEL						"CLESS_TSC"			/*!< Defines the file name that stores the cless transaction sequence counter. */



/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////



/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static void __CST_Batch_SetTransactionSeqCounter (const unsigned long ulValue);
static unsigned long __CST_Batch_GetTransactionSeqCounter (void);
static int __CST_Batch_WriteTransactionSeqCounter (unsigned long ulValue);
static int __CST_Batch_ReadTransactionSeqCounter (unsigned long * ulValue);
static int __CST_Batch_IsTscFilePresent (void);
static int __CST_Batch_AddRecord (TLV_TREE_NODE hInputTLVTree);



/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Set the value of the transaction sequence counter
//! \param[in] ulValue Value to be used to set the transaction sequence counter value.

static void __CST_Batch_SetTransactionSeqCounter (const unsigned long ulValue)
{
	if (!__CST_Batch_WriteTransactionSeqCounter (ulValue))
	{
		GTL_Traces_TraceDebug ("__CST_Batch_SetTransactionSeqCounter : __CST_Batch_WriteTransactionSeqCounter failed");
	}
}



//! \brief Get the transaction sequence counter.
//! \return The transaction sequence counter.

static unsigned long __CST_Batch_GetTransactionSeqCounter (void)
{
	unsigned long ulReadTsc;

	if (!__CST_Batch_ReadTransactionSeqCounter (&ulReadTsc))
	{
		ulReadTsc = 0;
		GTL_Traces_TraceDebug ("__CST_Batch_GetTransactionSeqCounter : __CST_Batch_ReadTransactionSeqCounter failed");
	}

	return (ulReadTsc);
}



//! \brief Writes the transaction sequence counter in a file.
//! \param[in] ulValue Value of the transaction sequence counter to be saved.
//! \return
//!		- \a TRUE if correctly saved.
//!		- \a FALSE if an error occured.

static int __CST_Batch_WriteTransactionSeqCounter (unsigned long ulValue)
{
	char PathName[1 + FS_PATHSIZE + 1];
	S_FS_FILE* hFile;

	if (CST_Disk_Mount (FILE_DISK_LABEL) == FS_OK)
	{
		memset (PathName, '\0', sizeof (PathName));
		sprintf(PathName, "/%s/%s", FILE_DISK_LABEL, FILE_TSC_LABEL);

		// Delete the saved file
		FS_unlink(PathName);

		// Open or create a file
		hFile = FS_open (PathName, "a");

		if (hFile != NULL)
		{
			FS_seek (hFile, 0, FS_SEEKEND);

			if (FS_write (&ulValue, 4, 1, hFile) != 1)
			{
				// An error occurs
				GTL_Traces_TraceDebug ("__CST_Batch_WriteTransactionSeqCounter : Error when writing the TSC in the file");
				FS_close(hFile);
				CST_Disk_Unmount (FILE_DISK_LABEL);
				return (FALSE);
			}

			FS_close(hFile);
		}
		else
		{
			GTL_Traces_TraceDebug ("__CST_Batch_WriteTransactionSeqCounter : hFile is NULL");
			CST_Disk_Unmount (FILE_DISK_LABEL);
			return (FALSE);
		}

		CST_Disk_Unmount (FILE_DISK_LABEL);
	}
	else
	{
		GTL_Traces_TraceDebug ("__CST_Batch_WriteTransactionSeqCounter : Unable to mount the disk");
		return (FALSE);
	}
		
	return (TRUE);
}



//! \brief Reads the transaction sequence counter in a file.
//! \param[out] ulValue Value of the transaction sequence counter read.
//! \return
//!		- \a TRUE if correctly saved.
//!		- \a FALSE if an error occured.

static int __CST_Batch_ReadTransactionSeqCounter (unsigned long * ulValue)
{
	char PathName[1 + FS_PATHSIZE + 1];
	S_FS_FILE* hFile;

	if (CST_Disk_Mount (FILE_DISK_LABEL) == FS_OK)
	{
		sprintf(PathName, "/%s/%s", FILE_DISK_LABEL, FILE_TSC_LABEL);

		// Open or create a file
		hFile = FS_open (PathName, "r");

		if (hFile != NULL)
		{
			FS_seek (hFile, -4, FS_SEEKEND);

			if (FS_read (ulValue, 4, 1, hFile) != 1)
			{
				// An error occurs
				GTL_Traces_TraceDebug ("__CST_Batch_ReadTransactionSeqCounter : An error occured when trying to read the TSC from the file");
				FS_close(hFile);
				CST_Disk_Unmount (FILE_DISK_LABEL);
				return (FALSE);
			}

			FS_close(hFile);
		}
		else
		{
			GTL_Traces_TraceDebug ("__CST_Batch_ReadTransactionSeqCounter : hFile is NULL");
			CST_Disk_Unmount (FILE_DISK_LABEL);
			return (FALSE);
		}

		CST_Disk_Unmount (FILE_DISK_LABEL);
	}
	else
	{
		GTL_Traces_TraceDebug ("__CST_Batch_ReadTransactionSeqCounter : Unable to mount the disk");
	}
	
	return (TRUE);
}



//! \brief Checks if the file that stores the TSC is present or not.
//! \return
//!		- \a TRUE if the file is present.
//!		- \a FALSE if not.

static int __CST_Batch_IsTscFilePresent (void)
{
	char PathName[1 + FS_PATHSIZE + 1];
	int nResult = FALSE;

	if (CST_Disk_Mount (FILE_DISK_LABEL) == FS_OK)
	{
		memset (PathName, '\0', sizeof (PathName));
		sprintf(PathName, "/%s/%s", FILE_DISK_LABEL, FILE_TSC_LABEL);

		nResult = (FS_exist (PathName) == FS_OK);

		CST_Disk_Unmount (FILE_DISK_LABEL);
	}
	else
	{
		GTL_Traces_TraceDebug ("__CST_Batch_IsTscFilePresent : Unable to mount the disk");
		nResult = FALSE;
	}

	return (nResult);
}



//! \brief Initialise the transaction sequence counter to 1.
//! \param[in] bForceInit Indicates if TSC shall be forced to be initialised or not.

void CST_Batch_InitTransactionSeqCounter (const unsigned char bForceInit)
{
	if ((bForceInit) || (!__CST_Batch_IsTscFilePresent ()))
	{
		// File does not yet exists, create it
		GTL_Traces_TraceDebug ("File does not yet exists, create it\n");
		__CST_Batch_SetTransactionSeqCounter(1);
	}
}



//! \brief Increment the Transaction sequence counter by 1.
//! \note If the TSC reached its max value, this one is initialised to 1.

void CST_Batch_IncrementTransactionSeqCounter (void)
{
	unsigned long ulTsc;
	
	// Get the transaction sequence counter
	ulTsc = __CST_Batch_GetTransactionSeqCounter();

	if (ulTsc >= SAMPLE_TSC_MAX_VALUE)
		ulTsc = 1;
	else
		ulTsc++;

	__CST_Batch_SetTransactionSeqCounter (ulTsc);
}



//! \brief Add the transaction sequence counter into a TLV Tree.
//! \param[in] pDataStruct Shared buffer in which the transaction sequence counter is stored.
//! \return
//!		- \a TRUE if correctly added.
//!		- \a FALSE if an error occured.

int CST_Batch_AddTscToTlvTree (TLV_TREE_NODE hTlvTree)
{
	unsigned char ucTsc[4];
	
	// Convert the TSC
	GTL_Convert_UlToDcbNumber (__CST_Batch_GetTransactionSeqCounter(), ucTsc, 4);

	TlvTree_AddChild(hTlvTree, TAG_EMV_TRANSACTION_SEQUENCE_COUNTER, ucTsc, 4);
		
	return (TRUE);
}



//! \brief This function checks the consistency of the transaction file. 
//! If the file data are valid the ram data are updated with the file content.
//! If the file is found corrupted, the function tries to restore it.

void CST_Batch_Restore (void)
{
	char FilePath_L[40];
	int ret;

	if (CST_Disk_Mount (FILE_DISK_LABEL) == FS_OK)
	{
		// Build path for transaction file
		memclr(FilePath_L, sizeof(FilePath_L));
		sprintf(FilePath_L, "/%s/%s",FILE_DISK_LABEL, TRANS_FILE_NAME);

		// Init transaction file
		CST_TransactionFile_Init (&Transac_File, FilePath_L);

		// Build path for backup transaction file
		memclr(FilePath_L, sizeof(FilePath_L));
		sprintf(FilePath_L, "/%s/%s%s",FILE_DISK_LABEL, TRANS_FILE_NAME, TRANS_FILE_BACKUP);

		// Init backup transaction file
		CST_TransactionFile_Init (&Transac_File_Backup, FilePath_L);

		// Tests if transaction file exists
		ret = FS_exist(Transac_File.TFilePath);

		if (ret == FS_OK)
		{
			// Delete backup transaction file
			CST_TransactionFile_Destroy (&Transac_File_Backup);

			// Check transaction file
			ret = CST_TransactionFile_Check (&Transac_File);

			if (ret == TRANS_FILE_CORRUPTED)
			{
				// Transaction file corrupted, then valid transactions are copied in backup transaction file
				ret = CST_TransactionFile_CopyValidTrans (&Transac_File, &Transac_File_Backup);

				if (ret == TRANS_FILE_OK)
				{
					// Delete corrupted transaction file
					ret = CST_TransactionFile_Destroy (&Transac_File);
					
					if (ret == TRANS_FILE_OK)
					{
						// The backup transaction file is valid, then rename the backup transaction file to transaction file
						ret = CST_TransactionFile_Rename (&Transac_File_Backup, &Transac_File);
					}
				}
			}
			else
			{
				// The transaction file is valid
			}
		}
		else
		{
			// Tests if backup transaction file exists
			ret = FS_exist(Transac_File_Backup.TFilePath);

			if (ret == FS_OK)
			{
				// The backup transaction file is valid, then rename the backup transaction file to transaction file
				ret = CST_TransactionFile_Rename (&Transac_File_Backup, &Transac_File);
			}
		}
		CST_Disk_Unmount (FILE_DISK_LABEL);
	}
}



//! \brief This function adds an entry in the transaction log file.
//! \param[in] hInputTLVTree : TLV tree containing the record to add. (Financial record or advice record).
//! \return 
//! - TRUE if record successfully written in the log file.
//! - FALSE otherwise.

static int __CST_Batch_AddRecord (TLV_TREE_NODE hInputTLVTree)
{
	int b_ret = FALSE;
	int i_ret;

	i_ret = CST_Disk_Mount (FILE_DISK_LABEL);
	if (i_ret == FS_OK)
	{
		i_ret = CST_TransactionFile_AddTransaction (&Transac_File, hInputTLVTree);
		
		if (i_ret == TRANS_FILE_OK)
		{
			b_ret = TRUE;
		}

		// Unmount the volume
		CST_Disk_Unmount (FILE_DISK_LABEL);
	}
	else
	{
		GTL_Traces_TraceDebug ("__CST_Batch_AddRecord : Cannot mount disk");
	}
	
	return (b_ret);
}



//! \brief Get the number of transaction stored in the batch file.
//! \param[out] nb_record Number of records stored in the Batch file.

void CST_Batch_InitialiseBatchTransfer (unsigned long *nb_record)
{
	*nb_record = Transac_File.TransactionNumber;
}


//! \brief Add a transaction record in the batch file.
//! \param[in] pDataStruct Shared buffer containing the transaction data.
//! \return
//!		- \a TRUE if correctly performed.
//!		- \a FALSE if an error occured.

int CST_Batch_AddTransactionToBatch (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int cr, nResult;
	int nPosition;
	unsigned long ulReadTag, ulReadLength;
	const unsigned char * pValue;
	TLV_TREE_NODE hTlvTree;


	cr = STATUS_SHARED_EXCHANGE_OK;
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	nResult = FALSE;

	// Create the TLV Tree
	hTlvTree = TlvTree_New(0);

	if (hTlvTree != NULL)
	{
		// pDataStruct contains all the necessary data to be stored in the batch
		// Create a TLV Tree that contains all the pStructData

		do
		{
			cr = GTL_SharedExchange_GetNext (pDataStruct, &nPosition, &ulReadTag, &ulReadLength, &pValue);

			if (cr == STATUS_SHARED_EXCHANGE_OK)
			{
				TlvTree_AddChild (hTlvTree, ulReadTag, pValue, ulReadLength);
			}
		} while (cr == STATUS_SHARED_EXCHANGE_OK);

		// If end of data has been reached
		if (cr == STATUS_SHARED_EXCHANGE_END)
		{
			// Add record to the batch file
			nResult = __CST_Batch_AddRecord (hTlvTree);

		}
		else
		{
			GTL_Traces_TraceDebug ("CST_Batch_AddTransactionToBatch : Error occured when parsing the shared buffer for batch");
		}

		// Release the TLV Tree
		TlvTree_Release(hTlvTree);
	}
	else
	{
		GTL_Traces_TraceDebug ("CST_Batch_AddTransactionToBatch : Cannot create TlvTree");
	}

	return (nResult);
}



//! \brief Destroy the batch database.

void CST_Batch_Destroy (void)
{
	if (CST_Disk_Mount (FILE_DISK_LABEL) == FS_OK)
	{
		CST_TransactionFile_Destroy (&Transac_File);
		CST_DumpData_Title ("Batch cleared");

		// Unmount the volume
		CST_Disk_Unmount (FILE_DISK_LABEL);
	}
}



//! \brief Dump the last transaction data saved in the batch.

void CST_Batch_PrintLastTransaction (void)
{
	int ret;
	unsigned int nPosition;
	TLV_TREE_NODE hTree, hTreeBackup;
	int bFound;

	// Init local data
	bFound = FALSE;
	hTreeBackup = NULL;
	hTree = NULL;

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
			CST_DumpData_DumpTlvTreeNodeWithTitle ("Last Transaction", hTreeBackup);
		else
			CST_DumpData_Title ("Batch is empty");

		// Release the TLV Tree if allocated
		if (hTree != NULL)
			TlvTree_Release(hTree);
		if (hTreeBackup != NULL)
			TlvTree_Release(hTreeBackup);

		// Unmount the volume
		CST_Disk_Unmount (FILE_DISK_LABEL);
	}
	else
	{
		GTL_Traces_TraceDebug ("CST_Batch_PrintLastTransaction : Cannot mount disk");
	}
}



//! \brief Dump the batch totals.

void CST_Batch_PrintTotals (void)
{
	int ret;
	unsigned int nPosition;
	TLV_TREE_NODE hTree, hTreeAmount;
	int bFound;
	unsigned long ulCurrentAmount, ulTotalAmount;
	unsigned char ucTotalsNum[6];
	char ucAsciiTotals[40];

	// Init local data
	bFound = FALSE;
	hTree = NULL;
	ulCurrentAmount = 0;
	ulTotalAmount = 0;
	memset (ucTotalsNum, 0x00, sizeof(ucTotalsNum));
	memset (ucAsciiTotals, 0x00, sizeof(ucAsciiTotals));

	ret = CST_Disk_Mount (FILE_DISK_LABEL);

	if (ret == FS_OK)
	{
		nPosition = 0;

		do
		{
			ret = CST_TransactionFile_GetNextTransaction (&Transac_File, &hTree, &nPosition);

			if (ret == TRANS_FILE_OK)
			{
				// Get the transaction amount
				hTreeAmount = TlvTree_Find (hTree, TAG_EMV_AMOUNT_AUTH_NUM, 0);

				if (hTreeAmount != NULL)
				{
					// Amount has been found, convert it into an unsigned long
					GTL_Convert_DcbNumberToUl ((unsigned char*)TlvTree_GetData (hTreeAmount), &ulCurrentAmount, TlvTree_GetLength(hTreeAmount));
					ulTotalAmount += ulCurrentAmount;
				}
				if (hTree != NULL)
					TlvTree_Release(hTree);
			}
		} while (ret == TRANS_FILE_OK);

		if (CST_DumpData_OpenOutputDriver())
		{
			if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
				CST_DumpData ("\x1b" "E");

			CST_DumpData ("Batch Totals");
				
			if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
				CST_DumpData ("\x1b" "@");

			CST_DumpData_NewLine();
			CST_DumpData_NewLine();

			CST_DumpData ("Nb Transactions = %d", Transac_File.TransactionNumber);
			CST_DumpData_NewLine();

			GTL_Convert_UlToDcbNumber (ulTotalAmount, ucTotalsNum, sizeof(ucTotalsNum));
			CST_FormatSpendingAmount(ucTotalsNum, 6, ucAsciiTotals);
			CST_DumpData ("Total = %s", ucAsciiTotals);
			
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();

			CST_DumpData_CloseOutputDriver();
		}

		if (hTree != NULL)
				TlvTree_Release(hTree);
	
		// Unmount the volume
		CST_Disk_Unmount (FILE_DISK_LABEL);
	}
	else
	{
		GTL_Traces_TraceDebug ("CST_Batch_PrintLastTransaction : Cannot mount disk");
	}
}


//! \brief Dump the a batch transaction overview.

static void __CST_Batch_PrintBatchTransactionOverview (TLV_TREE_NODE hTransaction, unsigned int nTransactionIndex)
{
	TLV_TREE_NODE hData;
	unsigned int nDataLength;
	unsigned char * pValue;
	char ucAsciiAmount[40];
	unsigned int nIndex;

	if (CST_DumpData_OpenOutputDriver())
	{
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "@");

		CST_DumpData ("Transaction (%d)", nTransactionIndex);
			
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "@" "\x0F");

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		// Dump the transaction type
		hData = TlvTree_Find (hTransaction, TAG_EMV_TRANSACTION_TYPE, 0);

		if (hData != NULL)
		{
			pValue = TlvTree_GetData(hData);
			if (pValue[0] == SDSA_TRANSACTION_TYPE_DEBIT)
				CST_DumpData ("Type : DEBIT");
			else if (pValue[0] == SDSA_TRANSACTION_TYPE_REFUND)
				CST_DumpData ("Type : REFUND");
			else
				CST_DumpData ("Type : UNKNOWN");
			CST_DumpData_NewLine();
		}
		else
		{
			CST_DumpData ("Type : NOT FOUND");
			CST_DumpData_NewLine();
		}

		// Dump the transaction date
		hData = TlvTree_Find (hTransaction, TAG_EMV_TRANSACTION_DATE, 0);

		if (hData != NULL)
		{
			pValue = TlvTree_GetData(hData);
			CST_DumpData ("Date : %02x/%02x/%02x", pValue[2], pValue[1], pValue[0]);
			CST_DumpData_NewLine();
		}
		else
		{
			CST_DumpData ("Date : Unknown");
			CST_DumpData_NewLine();
		}

		// Dump the AID
		hData = TlvTree_Find (hTransaction, TAG_EMV_DF_NAME, 0);

		if (hData != NULL)
		{
			pValue = TlvTree_GetData(hData);
			nDataLength = TlvTree_GetLength (hData);
			CST_DumpData ("AID : ");
			for (nIndex=0 ; nIndex<nDataLength; nIndex++)
				CST_DumpData ("%02x", pValue[nIndex]);
			CST_DumpData_NewLine();
		}
		else
		{
			CST_DumpData ("AID : Unknown");
			CST_DumpData_NewLine();
		}

		// Dump the application label
		hData = TlvTree_Find (hTransaction, TAG_EMV_APPLICATION_LABEL, 0);

		if (hData != NULL)
		{
			pValue = TlvTree_GetData(hData);
			nDataLength = TlvTree_GetLength (hData);
			CST_DumpData ("Label : ");
			for (nIndex=0 ; nIndex<nDataLength; nIndex++)
				CST_DumpData ("%c", pValue[nIndex]);
			CST_DumpData_NewLine();
		}

		// Dump the application prefered name
		hData = TlvTree_Find (hTransaction, TAG_EMV_APPLI_PREFERED_NAME, 0);

		if (hData != NULL)
		{
			pValue = TlvTree_GetData(hData);
			nDataLength = TlvTree_GetLength (hData);
			CST_DumpData ("Prefered Name : ");
			for (nIndex=0 ; nIndex<nDataLength; nIndex++)
				CST_DumpData ("%c", pValue[nIndex]);
			CST_DumpData_NewLine();
		}

		// Dump the application prefered name
		hData = TlvTree_Find (hTransaction, TAG_KERNEL_CARD_TYPE, 0);

		if (hData != NULL)
		{
			pValue = TlvTree_GetData(hData);
			nDataLength = TlvTree_GetLength (hData);
			CST_DumpData ("Card Type : ");
			for (nIndex=0 ; nIndex<nDataLength; nIndex++)
				CST_DumpData ("%02x", pValue[nIndex]);
			CST_DumpData_NewLine();
		}

		// Display the transaction amount
		memset (ucAsciiAmount, 0x00, sizeof(ucAsciiAmount));
		hData = TlvTree_Find (hTransaction, TAG_EMV_AMOUNT_AUTH_NUM, 0);

		if (hData != NULL)
		{
			pValue = TlvTree_GetData(hData);
			nDataLength = TlvTree_GetLength (hData);

			CST_FormatSpendingAmount (pValue, nDataLength, ucAsciiAmount);
			CST_DumpData ("Amount : %s", ucAsciiAmount);
			CST_DumpData_NewLine();
		}
		else
		{
			CST_DumpData ("Amount : Unknown");
			CST_DumpData_NewLine();
		}

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "@");
		
		CST_DumpData_CloseOutputDriver();
	}
}



//! \brief Dump the batch overview (each transaction overview).

void CST_Batch_PrintBatchOverview (void)
{
	int ret;
	unsigned int nPosition;
	int nIndex;
	int bFound;
	TLV_TREE_NODE hTree;

	// Init local data
	hTree = NULL;
	bFound = FALSE;

	ret = CST_Disk_Mount (FILE_DISK_LABEL);

	if (ret == FS_OK)
	{
		nPosition = 0;
		nIndex = 1;
		do
		{
			ret = CST_TransactionFile_GetNextTransaction (&Transac_File, &hTree, &nPosition);

			if (ret == TRANS_FILE_OK)
			{
				bFound = TRUE;
				__CST_Batch_PrintBatchTransactionOverview (hTree, nIndex);
			}
			nIndex++;

			if (hTree != NULL)
				TlvTree_Release(hTree);
		} while (ret == TRANS_FILE_OK);

		if (CST_DumpData_OpenOutputDriver())
		{
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
		
			CST_DumpData_CloseOutputDriver();
		}

		if (!bFound)
			CST_DumpData_Title ("No Record");

		// Unmount the volume
		CST_Disk_Unmount (FILE_DISK_LABEL);
	}
	else
	{
		GTL_Traces_TraceDebug ("CST_Batch_PrintLastTransaction : Cannot mount disk");
	}
}
