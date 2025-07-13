/**
* \file cu_batch.c
* \brief This module contains the functions that manages the transaction record file.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "SDK30.H"
#include "_emvdctag_.h"
#include "del_lib.h"
#include "cu_term.h"
#include "MyTlvTree.h"
#include "convert.h"
#include "cu_batch.h"
#include "cu_disk.h"
#include "cu_mess.h"
#include "cu_serv.h"
#include "cu_file.h"
#include "gestion_param.h"
#include "cu_base.h"
#include "cu_param.h"
#include "cu_entry.h"
#include "EngineInterfaceLib.h"

#include "cu_trfile.h"

//! \addtogroup Group_cu_batch
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

/* static T_CUBATCH_record BatchFile [CUBATCH_DEF_LOG_SIZE];
static T_CUBATCH_management_data MngData;*/

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
/* void CUBATCH_DeleteLog(void)
{
	char LabelDiskName[DISK_NAME_SIZE];
	char FilePath_L[33];

	// Get volume name
	memclr(LabelDiskName, sizeof(LabelDiskName));
	CUDISK_Get_Disk_Name(LabelDiskName);

	// Build transaction path
	memclr(FilePath_L, sizeof(FilePath_L));
	sprintf(FilePath_L, "/%s/%s",LabelDiskName, TRANS_FILE_NAME);

	// Init transaction file
	Init_Transaction_File(&Transac_File, FilePath_L);

	// Delete transaction file
	Del_Transaction_File(&Transac_File);

}
*/

//===========================================================================
void CUBATCH_RestoreLog (void)
{
	char LabelDiskName[DISK_NAME_SIZE];
	char FilePath_L[40];
	int ret;
	// int Pos_Trans_KO;

	// Get volume name
	memclr(LabelDiskName, sizeof(LabelDiskName));
	CUDISK_Get_Disk_Name(LabelDiskName);

	// Build path for transaction file
	memclr(FilePath_L, sizeof(FilePath_L));
	sprintf(FilePath_L, "/%s/%s",LabelDiskName, TRANS_FILE_NAME);
	// Init transaction file
	Init_Transaction_File(&Transac_File, FilePath_L);

	// Build path for backup transaction file
	memclr(FilePath_L, sizeof(FilePath_L));
	sprintf(FilePath_L, "/%s/%s%s",LabelDiskName, TRANS_FILE_NAME, TRANS_FILE_BACKUP);
	// Init backup transaction file
	Init_Transaction_File(&Transac_File_Backup, FilePath_L);

	// Tests if transaction file exists
	ret = FS_exist(Transac_File.TFilePath);

	if (ret == FS_OK)
	{
		// Delete backup transaction file
		Del_Transaction_File(&Transac_File_Backup);

		// Check transaction file
		ret = Check_Transac_File(&Transac_File);

		if (ret == TRANS_FILE_CORRUPTED)
		{
			// Transaction file corrupted, then valid transactions are copied in backup transaction file
			ret = Copy_Valid_Trans(&Transac_File, &Transac_File_Backup);

			if (ret == TRANS_FILE_OK)
			{
				// Delete corrupted transaction file
				ret = Del_Transaction_File(&Transac_File);
				
				if (ret == TRANS_FILE_OK)
				{
					// The backup transaction file is valid, then rename the backup transaction file to transaction file
					ret = Rename_Trans_File(&Transac_File_Backup, &Transac_File);
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
			ret = Rename_Trans_File(&Transac_File_Backup, &Transac_File);
		}
	}
}

//===========================================================================
//! \brief This function adds an entry in the transaction log file.
//! \param[in] hInputTLVTree : TLV tree containing the record to add. (Financial
//! record or advice record).
//! \return 
//! - TRUE if record successfully written in the log file.
//! - FALSE otherwise.
//===========================================================================
static T_Bool CUBATCH_AddRecord (TLV_TREE_NODE hInputTLVTree)
{
	T_Bool b_ret = FALSE;
	int i_ret;

	i_ret = CUDISK_CreateDisk();
	if (i_ret == FS_OK)
	{
		i_ret = Add_Transaction(&Transac_File, hInputTLVTree);
		
		if (i_ret == TRANS_FILE_OK)
		{
			b_ret = TRUE;
		}

		// Unmount the volume
		CUDISK_UnmountDisk();
	}
	
	return (b_ret);
}


//===========================================================================
T_Bool CUBATCHReadLastPANRecord (unsigned char PAN[10], TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned int Trans_pos = 0;
	int ret;
	TLV_TREE_NODE hTree;
	unsigned short found;
	DataElement elt;
	char Tr_PAN[10];
	T_Bool b_ret = FALSE;

	*phOutputTLVTree = NULL;

	// Mount the volume
	ret = CUDISK_CreateDisk();
	if (ret == FS_OK)
	{
		do
		{
			// Read a transaction in the batch file
			ret = Get_Next_Transaction(&Transac_File, &hTree, &Trans_pos);
			
			if (ret == TRANS_FILE_OK)
			{
				// Get TAG_CUST_BATCH_RECORD_TYPE
				found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_CUST_BATCH_RECORD_TYPE, &elt);
				if (found)
				{
					// Check if record read is a financial record
					if (elt.ptValue[0] == FINANCIAL_RECORD)
					{
						// Get TAG_APPLI_PRIM_ACCOUNT_NB
						found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APPLI_PRIM_ACCOUNT_NB, &elt);
						if (found)
						{
							memset(Tr_PAN, 0, sizeof(Tr_PAN));
							memcpy(Tr_PAN, elt.ptValue, elt.length);
							// Compare transaction PAN with given PAN
							if (memcmp(Tr_PAN, PAN, sizeof(Tr_PAN)) == 0)
							{
								// if transaction PAN equals given PAN then save transaction
								TlvTree_ReleaseEx(phOutputTLVTree );
								*phOutputTLVTree = TlvTree_Copy(hTree);
								b_ret = TRUE;
							}
						}
					}
				}
			}
			TlvTree_ReleaseEx(&hTree);
		}
		while (ret == TRANS_FILE_OK);

		// Unmount the volume
		CUDISK_UnmountDisk();

	}
	return (b_ret);
}


//===========================================================================
T_Bool CUBATCH_GiveStatistics (unsigned long *nb_record,
							   unsigned long *total_amount)
{
	unsigned int Trans_pos = 0;
	int ret;
	TLV_TREE_NODE hTree;
	unsigned short found;
	unsigned long amount;
	DataElement elt;

	*nb_record = Transac_File.TransactionNumber;

	*total_amount = 0;

	// Mount the volume
	ret = CUDISK_CreateDisk();
	if (ret == FS_OK)
	{
		do
		{
			ret = Get_Next_Transaction(&Transac_File, &hTree, &Trans_pos);
			
			if (ret == TRANS_FILE_OK)
			{
				// Get TAG_CUST_BATCH_RECORD_TYPE
				found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_CUST_BATCH_RECORD_TYPE, &elt);
				if (found)
				{
					// Check if record read is a financial record
					if (elt.ptValue[0] == FINANCIAL_RECORD)
					{
						// Get TAG_AMOUNT_AUTH_BIN
						found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_AMOUNT_AUTH_BIN, &elt);
						if (found)
						{
							amount = CharToLong (elt.ptValue);
							*total_amount = *total_amount + amount;
						}

						// Get TAG_AMOUNT_OTHER_BIN
						found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_AMOUNT_OTHER_BIN, &elt);
						if (found)
						{
							amount = CharToLong (elt.ptValue);
							*total_amount = *total_amount + amount;
						}
					}
				}
			}
			TlvTree_ReleaseEx(&hTree);
		}
		while (ret == TRANS_FILE_OK);

		// Unmount the volume
		CUDISK_UnmountDisk();

	}

	return (B_TRUE);
}


//===========================================================================
T_Bool CUBATCH_InitialiseBatchTransfer (unsigned long *nb_record)
{
	*nb_record = Transac_File.TransactionNumber;

	return (B_TRUE);
}


//===========================================================================
void CUBATCH_GetNextTransfDate (DATE *date_time)
{
	memcpy(date_time, &DateNextTransf, sizeof(DATE));
}


//===========================================================================
void CUBATCH_SetNextTransfDate (DATE *date_time)
{
	memcpy(&DateNextTransf, date_time, sizeof(DATE));
}


//===========================================================================
void CUBATCH_Create_Financial_Record (TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned short found;
	DataElement elt;
	char Auth_Code[6];
	char Record_Type;
	static const unsigned long RequiredTags[] = {TAG_AIP, TAG_ATC, TAG_APPLI_USAGE_CONTROL, 
		TAG_CRYPTOGRAM_INFORMATION_DATA, TAG_CVM_LIST, TAG_CVR_RESULT, TAG_IFD_SERIAL_NUMBER,
		TAG_ISSUER_ACTION_CODE_DEFAULT, TAG_ISSUER_ACTION_CODE_DENIAL, TAG_ISSUER_ACTION_CODE_ONLINE,
		TAG_ISSUER_APPLICATION_DATA, TAG_ISSUER_SCRIPT_RESULT_LIST, TAG_ISSUER_SCRIPT_RESULT_LIST_LEN,
		TAG_TERMINAL_CAPABILITIES, TAG_TERMINAL_TYPE, TAG_TVR, TAG_APPLI_CRYPTOGRAMME_AC,
		TAG_UNPREDICTABLE_NUMBER, TAG_ACQUIRER_IDENTIFIER, TAG_AMOUNT_AUTH_BIN, TAG_AMOUNT_OTHER_BIN,
		TAG_APPLI_EFFECTIVE_DATE, TAG_APPLI_EXPIRATION_DATE, TAG_APPLI_PRIM_ACCOUNT_NB,
		TAG_APPLI_PRIM_ACCOUNT_NB_SEQ_NB, TAG_AUTHORISATION_CODE, TAG_AUTHORISATION_RESPONSE_CODE,
		TAG_ISSUER_COUNTRY_CODE, TAG_MERCHANT_CATEGORY_CODE, TAG_MERCHANT_IDENTIFIER,
		TAG_POS_ENTRY_MODE_CODE, TAG_TERMINAL_COUNTRY_CODE, TAG_TERMINAL_IDENTIFICATION,
		TAG_TRANSACTION_CURRENCY_CODE, TAG_TRANSACTION_DATE, TAG_TRANSACTION_TIME,
		TAG_TRANSACTION_TYPE, TAG_ISSUER_APPLICATION_DATA, TAG_AMOUNT_AUTH_NUM,
		TAG_AMOUNT_OTHER_NUM, TAG_AID_ICC, TAG_SERVICE_CODE, TAG_TRANSACTION_SEQ_COUNTER,
		TAG_TRACK2_EQU_DATA, TAG_TRANSACTION_CURRENCY_EXP, TAG_VERSION_NUMBER_TERMINAL,
		TAG_TRANSACTION_FORCED_ACCEPTANCE, TAG_TSI, TAG_ICC_DYNAMIC_NUMBER };
	// TAG_TRANSACTION_CATEGORY_CODE


	PAR_ResetMarkList();             // Reset the selected mark list
	CUPAR_SelectAdditionnalICS();    // Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalAID();    // Select Main AIDx or AID0 parameters
	CUPAR_SelectAdditionnalKRevok(); // Select Main Krevok parameters

	//----------------------------------------------------------------------
	// Retrieve data needed for batch data capture record
	//----------------------------------------------------------------------

	// Retrieve all tags from EMVDC Data base
	*phOutputTLVTree = Engine_GetDataElements(sizeof(RequiredTags) / sizeof(RequiredTags[0]), RequiredTags);

	// Add the record type.
	Record_Type = FINANCIAL_RECORD;
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_BATCH_RECORD_TYPE, &Record_Type, 1);

	found = CUSERV_Extract_Element_TLV_Tree(phOutputTLVTree, TAG_AUTHORISATION_CODE, &elt);
	if (found == FALSE)
	{
		// Default value : all set with zeroes
		memset(Auth_Code, 0x30, 6);
		TlvTree_AddChild(*phOutputTLVTree, TAG_AUTHORISATION_CODE, Auth_Code, 6);
	}

	// fallback management
	found = PAR_ReadParameter(TAG_POS_ENTRY_MODE_CODE, (DataElementExt *)&elt);
	if (found)
	{
		TlvTree_AddChild(*phOutputTLVTree, elt.tag, elt.ptValue, elt.length);
	}

	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_POS_ISO8583_93, Pos_8583_93, LEN_CUST_POS_ISO8583_93);

	//----------------------------------------------------------------------
	// Add record to the batch file
	//----------------------------------------------------------------------
	CUBATCH_AddRecord(*phOutputTLVTree);

}


//===========================================================================
void CUBATCH_Create_Advice_Record (void)
{
	TLV_TREE_NODE hTree;
	char Record_Type;
	static const unsigned long RequiredTags[] = {TAG_AIP, TAG_ATC, TAG_APPLI_USAGE_CONTROL, 
		TAG_CRYPTOGRAM_INFORMATION_DATA, TAG_CVM_LIST, TAG_CVR_RESULT, TAG_IFD_SERIAL_NUMBER,
		TAG_ISSUER_ACTION_CODE_DEFAULT, TAG_ISSUER_ACTION_CODE_DENIAL, TAG_ISSUER_ACTION_CODE_ONLINE,
		TAG_ISSUER_APPLICATION_DATA, TAG_ISSUER_SCRIPT_RESULT_LIST, TAG_ISSUER_SCRIPT_RESULT_LIST_LEN,
		TAG_TERMINAL_CAPABILITIES, TAG_TERMINAL_TYPE, TAG_TVR, TAG_APPLI_CRYPTOGRAMME_AC,
		TAG_UNPREDICTABLE_NUMBER, TAG_ACQUIRER_IDENTIFIER, TAG_AMOUNT_AUTH_BIN, TAG_AMOUNT_OTHER_BIN,
		TAG_APPLI_EFFECTIVE_DATE, TAG_APPLI_EXPIRATION_DATE, TAG_APPLI_PRIM_ACCOUNT_NB,
		TAG_APPLI_PRIM_ACCOUNT_NB_SEQ_NB, TAG_AUTHORISATION_CODE, TAG_AUTHORISATION_RESPONSE_CODE,
		TAG_ISSUER_COUNTRY_CODE, TAG_MERCHANT_CATEGORY_CODE, TAG_MERCHANT_IDENTIFIER,
		TAG_POS_ENTRY_MODE_CODE, TAG_TERMINAL_COUNTRY_CODE, TAG_TERMINAL_IDENTIFICATION,
		TAG_TRANSACTION_CURRENCY_CODE, TAG_TRANSACTION_DATE, TAG_TRANSACTION_TIME,
		TAG_TRANSACTION_TYPE, TAG_ISSUER_APPLICATION_DATA, TAG_AMOUNT_AUTH_NUM, TAG_AMOUNT_OTHER_NUM,
		TAG_AID_ICC, TAG_SERVICE_CODE, TAG_TRANSACTION_SEQ_COUNTER, TAG_TRACK2_EQU_DATA,
		TAG_TRANSACTION_CURRENCY_EXP, TAG_VERSION_NUMBER_TERMINAL, TAG_TRANSACTION_FORCED_ACCEPTANCE,
		TAG_TSI };
	// TAG_TRANSACTION_CATEGORY_CODE;

	//----------------------------------------------------------------------
	// Retrieve data needed for batch data capture record
	//----------------------------------------------------------------------

	// Retrieve all RequiredTags from EMVDC Data base
	hTree = Engine_GetDataElements(sizeof(RequiredTags) / sizeof(RequiredTags[0]), RequiredTags);

	// Add the record type.
	Record_Type = ADVICE;
	TlvTree_AddChild(hTree, TAG_CUST_BATCH_RECORD_TYPE, &Record_Type, 1);

	//----------------------------------------------------------------------
	// Add record to the batch file
	//----------------------------------------------------------------------
	CUBATCH_AddRecord(hTree);

	// release local TLV tree
	TlvTree_ReleaseEx(&hTree);
}


//===========================================================================
void CUBATCH_Create_MAGFinancial_Record (TLV_TREE_NODE *pInputTLVTree, int Record_POS_EM)
{
	unsigned short found;
	DataElement Elt;
	char Auth_Code[6];
	char Record_Type;
	unsigned char value[4];
	TLV_TREE_NODE hTree;
	static const unsigned long RequiredTags[] = { TAG_IFD_SERIAL_NUMBER, TAG_TERMINAL_CAPABILITIES, 
		TAG_TERMINAL_TYPE, TAG_AUTHORISATION_CODE, TAG_TERMINAL_IDENTIFICATION, TAG_TRANSACTION_SEQ_COUNTER };

	//----------------------------------------------------------------------
	// Retrieve data needed for batch data capture record
	//----------------------------------------------------------------------

	// Retrieve all RequiredTags from EMVDC Data base
	hTree = Engine_GetDataElements(sizeof(RequiredTags) / sizeof(RequiredTags[0]), RequiredTags);

	// Add the record type.
	Record_Type = FINANCIAL_RECORD;
	TlvTree_AddChild(hTree, TAG_CUST_BATCH_RECORD_TYPE, &Record_Type, 1);

	found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_AUTHORISATION_CODE, &Elt);
	if (found == FALSE)
	{
		// Default value : all set with zeroes
		memset(Auth_Code, 0x30, 6);
		TlvTree_AddChild(hTree, TAG_AUTHORISATION_CODE, Auth_Code, 6);
	}


	//----------------------------------------------------------------------
	// Fill the batch record with data from input TLV tree
	//----------------------------------------------------------------------

	// data of input parameter
	found = CUSERV_Extract_Element_TLV_Tree(pInputTLVTree, TAG_AMOUNT_AUTH_BIN, &Elt);
	if (found)
	{
		TlvTree_AddChild(hTree, Elt.tag, Elt.ptValue, Elt.length);
	}

	found = CUSERV_Extract_Element_TLV_Tree(pInputTLVTree, TAG_AMOUNT_OTHER_BIN, &Elt);
	if (found)
	{
		TlvTree_AddChild(hTree, Elt.tag, Elt.ptValue, Elt.length);
	}

	found = CUSERV_Extract_Element_TLV_Tree(pInputTLVTree, TAG_APPLI_EXPIRATION_DATE, &Elt);
	if (found)
	{
		TlvTree_AddChild(hTree, Elt.tag, Elt.ptValue, Elt.length);
	}

	found = CUSERV_Extract_Element_TLV_Tree(pInputTLVTree, TAG_APPLI_PRIM_ACCOUNT_NB, &Elt);
	if (found)
	{
		TlvTree_AddChild(hTree, Elt.tag, Elt.ptValue, Elt.length);
	}

	found = CUSERV_Extract_Element_TLV_Tree(pInputTLVTree, TAG_TERMINAL_COUNTRY_CODE, &Elt);
	if (found)
	{
		TlvTree_AddChild(hTree, Elt.tag, Elt.ptValue, Elt.length);
	}

	found = CUSERV_Extract_Element_TLV_Tree(pInputTLVTree, TAG_TRANSACTION_CURRENCY_CODE, &Elt);
	if (found)
	{
		TlvTree_AddChild(hTree, Elt.tag, Elt.ptValue, Elt.length);
	}

	found = CUSERV_Extract_Element_TLV_Tree(pInputTLVTree, TAG_TRANSACTION_DATE, &Elt);
	if (found)
	{
		TlvTree_AddChild(hTree, Elt.tag, Elt.ptValue, Elt.length);
	}

	found = CUSERV_Extract_Element_TLV_Tree(pInputTLVTree, TAG_TRANSACTION_TIME, &Elt);
	if (found)
	{
		TlvTree_AddChild(hTree, Elt.tag, Elt.ptValue, Elt.length);
	}

	found = CUSERV_Extract_Element_TLV_Tree(pInputTLVTree, TAG_TRANSACTION_TYPE, &Elt);
	if (found)
	{
		TlvTree_AddChild(hTree, Elt.tag, Elt.ptValue, Elt.length);
	}
	
	// Amount, Authorised 0x9F02 (numeric)
	found = CUSERV_Extract_Element_TLV_Tree(pInputTLVTree, TAG_AMOUNT_AUTH_NUM, &Elt);
	if (found)
	{
		TlvTree_AddChild(hTree, Elt.tag, Elt.ptValue, Elt.length);
	}

	// Amount, Other 0x9F03 (numeric)
	found = CUSERV_Extract_Element_TLV_Tree(pInputTLVTree, TAG_AMOUNT_OTHER_NUM, &Elt);
	if (found)
	{
		TlvTree_AddChild(hTree, Elt.tag, Elt.ptValue, Elt.length);
	}


	if (Record_POS_EM )
		CUPAR_Get_Param(TAG_POS_ENTRY_MODE_CODE, value);
	else
		memcpy (value,"02",2);

	TlvTree_AddChild(hTree, TAG_POS_ENTRY_MODE_CODE, value, 2);
	// Aschex (&(pIntRecord->exist_data.POS_Ent_Mode), &value[0], 2 );

	//----------------------------------------------------------------------
	// Add record to the batch file
	//----------------------------------------------------------------------
	CUBATCH_AddRecord(hTree);

	// release local TLV tree
	TlvTree_ReleaseEx(&hTree);
}


//! @}

