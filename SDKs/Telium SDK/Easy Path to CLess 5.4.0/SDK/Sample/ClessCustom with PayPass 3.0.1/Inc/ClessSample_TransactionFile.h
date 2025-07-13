/**
* \file cu_trfile.h
* \brief This module contains the functions that manages the new transaction file.
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
#ifndef __CLESS_SAMPLE_TRANSACTION_FILE_H__
#define __CLESS_SAMPLE_TRANSACTION_FILE_H__

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \defgroup Group_cu_trfile Transaction file management. Low level functions.
//! @{

#define TRANS_FILE_NAME							"TR_FILE"				//!< Transaction file name
#define TRANS_FILE_BACKUP						"BACKUP"				//!< Transaction file name extension for backup file

#define TRANS_FILE_HEADER_SIZE					32						//!< Transaction file header size.
#define TRANS_FILE_VERSION						1						//!< Transaction file version.

#define TRANS_FILE_OK							0						//!< Return code for a successfull function execution.
#define TRANS_FILE_NOT_EXISTING					1						//!< Return code if the transaction file doesn't exist.
#define TRANS_FILE_CORRUPTED					2						//!< Return code for a corrupted transaction file.
#define TRANS_FILE_OPEN_ERROR					3						//!< Return code if an error occurred at transaction file open.
#define TRANS_FILE_READ_ERROR					4						//!< Return code if an error occurred at transaction file read.
#define TRANS_FILE_ADD_ERROR					5						//!< Return code if an error occurred at transaction file write.
#define TRANS_FILE_GET_ERROR					6						//!< Return code if an error occurred at transaction get in the file
#define TRANS_FILE_DEL_ERROR					7						//!< Return code if an error occurred at transaction file suppression

#define CRC_LEN									sizeof(short)			//!< Length of CRC in transaction file
#define INT_LEN									sizeof(int)				//!< Length of transaction length in transaction file


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

//! \brief This structure defines the header of the transaction file.
typedef struct
{
	unsigned int FileVersion;											//!< Transaction file version.
	unsigned int RFU1;													//!< RFU1.
	unsigned int RFU2;													//!< RFU2.
	unsigned int RFU3;													//!< RFU3.
	unsigned int RFU4;													//!< RFU4.
	unsigned int RFU5;													//!< RFU5.
	unsigned int RFU6;													//!< RFU6.
	unsigned int RFU7;													//!< RFU7.
}T_Transaction_File_Header;


//! \brief This structure defines the ram data of the transaction file. These data 
//! are updated at each transaction adding, or at terminal restart.
typedef struct
{
	T_Transaction_File_Header FileHeader;								//!< Transaction file header.
	char TFilePath[50];													//!< Transaction file path.
	S_FS_FILE *hFile;													//!< Transaction file handle.
	unsigned int FileSize;												//!< Transaction file size.
	unsigned int TransactionNumber;										//!< Transaction number in the file.
	// unsigned int FileMaxSize;
}T_Transaction_File;


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

extern T_Transaction_File Transac_File;									//!< Global variable for transaction file.
extern T_Transaction_File Transac_File_Backup;							//!< Global variable for transaction file backup.


/////////////////////////////////////////////////////////////////
//// Constant declarations //////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief This function initializes the \ref T_Transaction_File structure 
//! given as parameter. All the fields are set to 0, excepted the field FileHeader,
//! and TFilePath set to input parameter FilePath.
//! \param[out] pt_Tr_File : pointer \ref T_Transaction_File structure to be 
//! initialized.
//! \param[in] FilePath : File path of transaction file.

void ClessSample_TransactionFile_Init (T_Transaction_File *pt_Tr_File, char * FilePath);



//! \brief This function checks the CRC16 of the transactions stored in the transaction
//! file. The fields FileSize and TransactionNumber of the \ref T_Transaction_File 
//! structure are also initialized.
//! \param[in,out] pt_Tr_File : pointer to \ref T_Transaction_File structure 
//! containing the path of the file to check.
//! \return 
//! - \ref TRANS_FILE_OK if the CRC16 of all the transactions stored in the file 
//! are valid.
//! - \ref TRANS_FILE_CORRUPTED if the CRC16 of one transaction stored in the file 
//! is not valid.
//! - \ref TRANS_FILE_READ_ERROR if an error occurred at file reading.
//! - \ref TRANS_FILE_OPEN_ERROR if the file open was not successfull.
//! - \ref TRANS_FILE_NOT_EXISTING if the file doesn't exist.

int ClessSample_TransactionFile_Check(T_Transaction_File *pt_Tr_File);



//! \brief This function adds one transaction in the transaction file. 
//! The size and the CRC16 of the transaction to add are also calculated. 
//! The fields FileSize, and TransactionNumber are updated by the function.
//! \param[in,out] pt_Tr_File : pointer to \ref T_Transaction_File structure 
//! containing the path of the file.
//! \param[in] hInputTlvTree : input TLV tree containing the transaction to be
//! stored.
//! \return 
//! - \ref TRANS_FILE_OK if the transaction is successfully stored in the file.
//! - \ref TRANS_FILE_ADD_ERROR if the transaction was not stored in the file.
//! - \ref TRANS_FILE_OPEN_ERROR if the file open was not successfull and the 
//! transaction storage was not performed.
//! \note If the file doesn't exist the file is created. If the file exist the 
//! transaction is added at the end of the file.

int ClessSample_TransactionFile_AddTransaction (T_Transaction_File *pt_Tr_File, TLV_TREE_NODE hInputTlvTree);



//! \brief This function reads one transaction in the transaction file, at the 
//! position given in the parameter Trans_pos. The function checks the CRC16
//! of the transaction read. The content of the transaction is returned in a TLV tree.
//! \param[in] pt_Tr_File : pointer to \ref T_Transaction_File structure 
//! containing the path of the file.
//! \param[out] phOutputTlvTree : output TLV tree containing the transaction read.
//! \param[in] Trans_pos : transaction position in the file (in bytes).
//! \param[out] Trans_len : length of the transaction read.
//! \return 
//! - \ref TRANS_FILE_OK if the transaction is successfully read in the file.
//! - \ref TRANS_FILE_CORRUPTED if the CRC16 of one transaction read in the file 
//! is not valid.
//! - \ref TRANS_FILE_READ_ERROR if an error occurred at file reading.
//! - \ref TRANS_FILE_OPEN_ERROR if the file open was not successfull.
//! - \ref TRANS_FILE_NOT_EXISTING if the file doesn't exist.

int ClessSample_TransactionFile_GetTransaction (T_Transaction_File *pt_Tr_File, TLV_TREE_NODE *phOutputTlvTree, unsigned int Trans_pos, int * Trans_len);



//! \brief This function reads one transaction in the transaction file, at the 
//! position given in parameter. The function checks the CRC16
//! of the transaction read. The content of the transaction is returned in a TLV tree.
//! The function gives also the position of the next transaction in the file.
//! \param[in] pt_Tr_File : pointer to \ref T_Transaction_File structure 
//! containing the path of the file.
//! \param[out] phOutputTlvTree : output TLV tree containing the transaction read.
//! \param[in,out] pt_trans_pos : 
//! - as input parameter : transaction position in the file (in bytes).
//! - as output parameter : position of the next transaction in the file (in bytes).
//! \return 
//! - \ref TRANS_FILE_OK if the transaction is successfully read in the file.
//! - \ref TRANS_FILE_CORRUPTED if the CRC16 of one transaction read in the file 
//! is not valid.
//! - \ref TRANS_FILE_READ_ERROR if an error occurred at file reading.
//! - \ref TRANS_FILE_OPEN_ERROR if the file open was not successfull.
//! - \ref TRANS_FILE_NOT_EXISTING if the file doesn't exist.

int ClessSample_TransactionFile_GetNextTransaction (T_Transaction_File *pt_Tr_File, TLV_TREE_NODE *phOutputTlvTree, unsigned int *pt_trans_pos);



//! \brief This function erases the transaction file.
//! \param[in] pt_Tr_File : pointer to \ref T_Transaction_File structure 
//! containing the path of the file.
//! \return 
//! - \ref TRANS_FILE_OK if the transaction file is successfully erased.
//! - \ref TRANS_FILE_NOT_EXISTING if the file doesn't exist.
//! - \ref TRANS_FILE_DEL_ERROR if an error occurred during file erase.

int ClessSample_TransactionFile_Destroy (T_Transaction_File *pt_Tr_File);



//! \brief This function copies each valid transaction from the input transaction 
//! file to the output transaction file. This function is used to restore a corrupted 
//! transaction file at terminal startup.
//! \param[in] pt_In_Tr_File : pointer to \ref T_Transaction_File structure 
//! containing the input transaction file.
//! \param[out] pt_Out_Tr_File : pointer to \ref T_Transaction_File structure 
//! containing the output transaction file.
//! \return 
//! - \ref TRANS_FILE_OK if the output transaction file is successfully created.
//! - \ref TRANS_FILE_ADD_ERROR if an error occurred at file writing.
//! - \ref TRANS_FILE_READ_ERROR if an error occurred at file reading.
//! - \ref TRANS_FILE_OPEN_ERROR if the file open was not successfull.

int ClessSample_TransactionFile_CopyValidTrans (T_Transaction_File *pt_In_Tr_File, T_Transaction_File *pt_Out_Tr_File);



//! \brief This function renames the input transaction file into the output 
//! transaction file. 
//! \param[in] pt_In_Tr_File : pointer to \ref T_Transaction_File structure 
//! containing the input transaction file.
//! \param[out] pt_Out_Tr_File : pointer to \ref T_Transaction_File structure 
//! containing the output transaction file.
//! \return 
//! - FS_OK if successful.
//! - FS_KO in case of error.
//! - FS_NOACCESS if the application does not have the access rights.

int ClessSample_TransactionFile_Rename (T_Transaction_File *pt_In_Tr_File, T_Transaction_File *pt_Out_Tr_File);

//! @}

#endif // __CLESS_SAMPLE_TRANSACTION_FILE_H__
