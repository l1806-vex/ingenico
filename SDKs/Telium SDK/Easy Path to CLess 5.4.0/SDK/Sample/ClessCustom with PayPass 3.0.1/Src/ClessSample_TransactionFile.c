/**
* \file ClessSample_TransactionFile.c
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

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


//! \addtogroup Group_cu_trfile
//! @{

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Constant declarations //////////////////////////////////////

// CRC16 implementation acording to CCITT standards
static const unsigned short crc16tab[256]= {
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

T_Transaction_File Transac_File;				//!< Global variable for transaction file.
T_Transaction_File Transac_File_Backup;			//!< Global variable for transaction file backup.


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static unsigned short __ClessSample_TransactionFile_crc16_ccitt(const void *buff, int len);
static int __ClessSample_TransactionFile_FillTlvTree(unsigned char * tr_buf, int tr_len, TLV_TREE_NODE *phOutputTlvTree);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief This function calculates CRC16 on the given buffer.
//! \param[in] buff : buffer on which to calculate the CRC16.
//! \param[in] len : buffer length on which to calculate CRC16.
//! \return CRC16 calculated.

static unsigned short __ClessSample_TransactionFile_crc16_ccitt(const void *buff, int len)
{
	register int counter;
	register unsigned short crc = 0;
	union {
		void *ptv;
		char *ptc;
	} mybuff;
	

	mybuff.ptv=(void*)buff;
	for( counter = 0; counter < len; counter++)
		crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *mybuff.ptc++)&0x00FF];
	return crc;
}



//===========================================================================
static int __ClessSample_TransactionFile_FillTlvTree(unsigned char * tr_buf, int tr_len, TLV_TREE_NODE *phOutputTlvTree)
{
	int len_read=0;
	DataElement elt;
	int ret = 1;

	// *phOutputTlvTree = TlvTree_New(0);

	if (*phOutputTlvTree != NULL)
	{
		while (len_read < tr_len)
		{
			// Get the tag in the buffer
			memcpy(&elt.tag, tr_buf, sizeof(elt.tag));
			tr_buf = tr_buf + sizeof(elt.tag);
			
			// Get the length in the buffer
			memcpy(&elt.length, tr_buf, sizeof(elt.length));
			tr_buf = tr_buf + sizeof(elt.length);

			// Get the value in the buffer
			// memcpy(elt.ptValue, tr_buf, elt.length);
			elt.ptValue = tr_buf;
			TlvTree_AddChild(*phOutputTlvTree, elt.tag, elt.ptValue, elt.length);
			tr_buf = tr_buf + elt.length;

			// Update length read in the buffer
			len_read = len_read + sizeof(elt.tag) + sizeof(elt.length) + elt.length;

		}
	}
	else
	{
		ret = 0;
	}
	return (ret);
}






//! \brief This function initializes the \ref T_Transaction_File structure 
//! given as parameter. All the fields are set to 0, excepted the field FileHeader,
//! and TFilePath set to input parameter FilePath.
//! \param[out] pt_Tr_File : pointer \ref T_Transaction_File structure to be 
//! initialized.
//! \param[in] FilePath : File path of transaction file.

void ClessSample_TransactionFile_Init (T_Transaction_File *pt_Tr_File, char * FilePath)
{
	memclr(&(pt_Tr_File->FileHeader),sizeof(pt_Tr_File->FileHeader));
	pt_Tr_File->FileHeader.FileVersion = TRANS_FILE_VERSION;
	memclr(pt_Tr_File->TFilePath, sizeof(pt_Tr_File->TFilePath));
	memcpy(pt_Tr_File->TFilePath, FilePath, strlen(FilePath));
	pt_Tr_File->hFile = NULL;
	pt_Tr_File->FileSize = 0;
	pt_Tr_File->TransactionNumber = 0;
}



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

int ClessSample_TransactionFile_Check (T_Transaction_File *pt_Tr_File)
{
	int ret, ret_exist;
	int T_length, nb_elt_read;
	unsigned char * puc_buffer = NULL;
	unsigned short crc16_read, crc16_calculated;

	pt_Tr_File->FileSize = 0;
	pt_Tr_File->TransactionNumber = 0;
	ret = TRANS_FILE_OK;

	// Tests if given file exists
	ret_exist = FS_exist(pt_Tr_File->TFilePath);

	if (ret_exist == FS_OK)
	{
		// Check transaction file consistency
		pt_Tr_File->hFile = FS_open(pt_Tr_File->TFilePath, "r");

		if (pt_Tr_File->hFile != NULL)
		{
			// Read file header
			nb_elt_read = FS_read (&(pt_Tr_File->FileHeader), TRANS_FILE_HEADER_SIZE, 1, pt_Tr_File->hFile);
			if (nb_elt_read == 1)
			{
				// Set the pointer on transaction ko to first transaction position in file
				// *p_Pos_Trans_ko = TRANS_FILE_HEADER_SIZE;

				do
				{
					// Read data length
					nb_elt_read = FS_read (&T_length, INT_LEN, 1, pt_Tr_File->hFile);
				
					if (nb_elt_read == 1)
					{
						if (T_length > 0)
						{
							puc_buffer = (unsigned char *) umalloc(T_length);
							
							// read transaction data
							nb_elt_read = FS_read (puc_buffer, T_length, 1, pt_Tr_File->hFile);

							if (nb_elt_read == 1)
							{
								// calculate CRC16 on data read
								crc16_calculated = __ClessSample_TransactionFile_crc16_ccitt(puc_buffer, T_length);

								// Read data CRC16
								nb_elt_read = FS_read (&crc16_read, CRC_LEN, 1, pt_Tr_File->hFile);
								if (nb_elt_read == 1)
								{
									if (crc16_calculated == crc16_read)
									{
										// Update field FileSize
										pt_Tr_File->FileSize = pt_Tr_File->FileSize + INT_LEN + T_length + CRC_LEN;

										// Update field TransactionNumber
										pt_Tr_File->TransactionNumber++;

										/* if (ret != TRANS_FILE_CORRUPTED)
										{
											// Set the pointer on transaction ko to next transaction position in the file
											*p_Pos_Trans_ko = *p_Pos_Trans_ko + INT_LEN + T_length + CRC_LEN;
										}*/
									}
									else
									{
										ret = TRANS_FILE_CORRUPTED;
									}
								}
								else 
								{
									ret = TRANS_FILE_READ_ERROR;
								}
							}
							else
							{
								ret = TRANS_FILE_READ_ERROR;
							}

							if (puc_buffer != 0)
							{
								ufree(puc_buffer);
							}

						}
						else
						{
							ret = TRANS_FILE_READ_ERROR;
						}
					}
					else
					{
						ret = TRANS_FILE_READ_ERROR;
					}
				}
				while (FS_eof(pt_Tr_File->hFile) ==  FS_KO);
			}
			else
			{
				ret = TRANS_FILE_READ_ERROR;
			}

			FS_close(pt_Tr_File->hFile);
		}
		else
		{
			ret = TRANS_FILE_OPEN_ERROR;
		}
	}
	else
	{
		// The file doesn't exist.
		ret = TRANS_FILE_NOT_EXISTING;
	}
	return (ret);
}



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

int ClessSample_TransactionFile_AddTransaction (T_Transaction_File *pt_Tr_File, TLV_TREE_NODE hInputTlvTree)
{
	int ret_exist, ret;
	int Trans_len, nb_elt_written, First_trans, buffer_size;
	unsigned short crc16_trans;
	unsigned char * puc_buffer = NULL, *puc_begin_buf;
	TLV_TREE_NODE hTree;
	DataElement elt;

	// Init transaction length
	Trans_len = 0;
	
	ret = TRANS_FILE_ADD_ERROR;

	if(hInputTlvTree != NULL)
	{
		// Tests if given file exists
		ret_exist = FS_exist(pt_Tr_File->TFilePath);

		if (ret_exist == FS_OK)
		{
			// Open existing file
			pt_Tr_File->hFile = FS_open(pt_Tr_File->TFilePath, "r+");
			First_trans = 0;
		}
		else
		{
			// Create the file
			pt_Tr_File->hFile = FS_open (pt_Tr_File->TFilePath, "a");
			First_trans = 1;
		}

		if (pt_Tr_File->hFile != NULL)
		{
			// position the file pointer to the end of the file.
			FS_seek(pt_Tr_File->hFile, 0, FS_SEEKEND);

			// Get the first child of the input TLV tree
			hTree = TlvTree_GetFirstChild(hInputTlvTree);
			
			// Calculate the length of the input TLV tree
			while(hTree != NULL)
			{
				// Get the tag 
				elt.tag = TlvTree_GetTag(hTree);

				// Get the length 
				elt.length = TlvTree_GetLength(hTree);

				// Get the value 
				elt.ptValue = TlvTree_GetData(hTree);

				// Update the length
				Trans_len = Trans_len + sizeof(elt.tag) + sizeof(elt.length) + elt.length;

				// Get the next node
				hTree = TlvTree_GetNext(hTree);
			}

			if(First_trans)
			{
				// Calculate buffer size
				buffer_size = TRANS_FILE_HEADER_SIZE + INT_LEN + Trans_len + CRC_LEN;

				// This is the first transaction. The allocated size is the header size + the transaction size
				puc_buffer = (unsigned char *) umalloc(buffer_size);

				// Memorize buffer beginning
				puc_begin_buf = puc_buffer;

				// Reset header
				memclr(puc_buffer,TRANS_FILE_HEADER_SIZE);

				// Set header file version
				puc_buffer[0] = TRANS_FILE_VERSION;
				puc_buffer = puc_buffer + TRANS_FILE_HEADER_SIZE;

			}
			else
			{
				// Calculate buffer size
				buffer_size = INT_LEN + Trans_len + CRC_LEN;

				// The allocated size is the transaction size
				puc_buffer = (unsigned char *) umalloc(buffer_size);

				// Memorize buffer beginning
				puc_begin_buf = puc_buffer;

			}

			// Store transaction length
			memcpy(puc_buffer, &Trans_len, INT_LEN);
			puc_buffer = puc_buffer + INT_LEN;

			// Get the first child of the input TLV tree
			hTree = TlvTree_GetFirstChild(hInputTlvTree);

			// Copy the content of the input TLV tree in puc_buffer
			while(hTree != NULL)
			{
				// Get the tag and store it into buffer
				elt.tag = TlvTree_GetTag(hTree);
				memcpy(puc_buffer, &elt.tag, sizeof(elt.tag));
				puc_buffer = puc_buffer + sizeof(elt.tag);

				// Get the length and store it into buffer
				elt.length = TlvTree_GetLength(hTree);
				memcpy(puc_buffer, &elt.length, sizeof(elt.length));
				puc_buffer = puc_buffer + sizeof(elt.length);

				// Get the value and stores it into buffer
				elt.ptValue = TlvTree_GetData(hTree);
				memcpy(puc_buffer, elt.ptValue, elt.length);
				puc_buffer = puc_buffer + elt.length;

				// Get the next node
				hTree = TlvTree_GetNext(hTree);
			}
			
			// calculates CRC16 on transaction data and store it into buffer
			if(First_trans)
			{
				crc16_trans = __ClessSample_TransactionFile_crc16_ccitt(&puc_begin_buf[TRANS_FILE_HEADER_SIZE + INT_LEN], Trans_len);
			}
			else
			{
				crc16_trans = __ClessSample_TransactionFile_crc16_ccitt(&puc_begin_buf[INT_LEN], Trans_len);

				// Corrupt transaction for tests
				/* if (pt_Tr_File->TransactionNumber == 2)
				{
					// corrupt 3rd transaction for tests
					crc16_trans++;
				}*/
				// Corrupt transaction for tests
			}
			memcpy(puc_buffer, &crc16_trans, CRC_LEN);

			// Add transaction length, data, and CRC16 in transaction file
			nb_elt_written = FS_write(puc_begin_buf, buffer_size, 1, pt_Tr_File->hFile);

			if (nb_elt_written == 1)
			{ 
				// Update field FileSize
				pt_Tr_File->FileSize = pt_Tr_File->FileSize + INT_LEN + Trans_len + CRC_LEN;

				// Update field TransactionNumber
				pt_Tr_File->TransactionNumber++;

				ret = TRANS_FILE_OK;
			}

			// Free allocated buffer
			if (puc_begin_buf != 0)
			{
				ufree(puc_begin_buf);
			}
			
			FS_close(pt_Tr_File->hFile);
		}
		else
		{
			ret = TRANS_FILE_OPEN_ERROR;
		}
	}
	return (ret);
}



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

int ClessSample_TransactionFile_GetTransaction (T_Transaction_File *pt_Tr_File, TLV_TREE_NODE *phOutputTlvTree, unsigned int Trans_pos, int * ptr_Trans_len)
{
	int ret_exist, ret;
	int nb_elt_read;       // T_length
	unsigned short crc16_trans, crc16_calculated;
	unsigned char * puc_buffer = NULL;

	ret = TRANS_FILE_GET_ERROR;
	*ptr_Trans_len = 0;

	*phOutputTlvTree = TlvTree_New(0);

	if (*phOutputTlvTree != NULL)
	{
		// Tests if given file exists
		ret_exist = FS_exist(pt_Tr_File->TFilePath);

		if (ret_exist == FS_OK)
		{
			// Open existing file
			pt_Tr_File->hFile = FS_open(pt_Tr_File->TFilePath, "r");

			if (pt_Tr_File->hFile != NULL)
			{	
				// Position the file pointer to the given position
				FS_seek(pt_Tr_File->hFile, TRANS_FILE_HEADER_SIZE + Trans_pos, FS_SEEKSET);

				// Read data length
				nb_elt_read = FS_read (ptr_Trans_len, INT_LEN, 1, pt_Tr_File->hFile);

				if (nb_elt_read == 1)
				{
					if (*ptr_Trans_len > 0)
					{
						puc_buffer = (unsigned char *) umalloc(*ptr_Trans_len);
						
						// read transaction data
						nb_elt_read = FS_read (puc_buffer, *ptr_Trans_len, 1, pt_Tr_File->hFile);

						if (nb_elt_read == 1)
						{
							// calculate CRC16 on data read
							crc16_calculated = __ClessSample_TransactionFile_crc16_ccitt(puc_buffer, *ptr_Trans_len);

							// Read data CRC16
							nb_elt_read = FS_read (&crc16_trans, CRC_LEN, 1, pt_Tr_File->hFile);
							if (nb_elt_read == 1)
							{
								if (crc16_calculated == crc16_trans)
								{
									if (__ClessSample_TransactionFile_FillTlvTree(puc_buffer, *ptr_Trans_len, phOutputTlvTree))
									{
										ret = TRANS_FILE_OK;
									}
								}
								else
								{
									ret = TRANS_FILE_CORRUPTED;
								}
							}
							else
							{
								ret = TRANS_FILE_READ_ERROR;
							}
						}
						else
						{
							ret = TRANS_FILE_READ_ERROR;
						}

						if (puc_buffer != 0)
						{
							ufree(puc_buffer);
						}
					}
				}
				else
				{
					ret = TRANS_FILE_READ_ERROR;
				}

				FS_close(pt_Tr_File->hFile);
			}
			else
			{
				ret = TRANS_FILE_OPEN_ERROR;
			}
		}
		else
		{
			ret = TRANS_FILE_NOT_EXISTING;
		}
	}
	return (ret);
}



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

int ClessSample_TransactionFile_GetNextTransaction (T_Transaction_File *pt_Tr_File, TLV_TREE_NODE *phOutputTlvTree, unsigned int *pt_trans_pos)
{
	int ret, T_length;
	
	ret = ClessSample_TransactionFile_GetTransaction (pt_Tr_File, phOutputTlvTree, *pt_trans_pos, &T_length);
	
	if (ret == TRANS_FILE_OK)
	{
		*pt_trans_pos = *pt_trans_pos + INT_LEN + T_length + CRC_LEN;
	}

	return (ret);

}



//! \brief This function erases the transaction file.
//! \param[in] pt_Tr_File : pointer to \ref T_Transaction_File structure 
//! containing the path of the file.
//! \return 
//! - \ref TRANS_FILE_OK if the transaction file is successfully erased.
//! - \ref TRANS_FILE_NOT_EXISTING if the file doesn't exist.
//! - \ref TRANS_FILE_DEL_ERROR if an error occurred during file erase.

int ClessSample_TransactionFile_Destroy (T_Transaction_File *pt_Tr_File)
{
	int ret_fct, ret;

	ret = TRANS_FILE_DEL_ERROR;

	// Tests if given file exists
	ret_fct = FS_exist(pt_Tr_File->TFilePath);

	if (ret_fct == FS_OK)
	{
		ret_fct = FS_unlink(pt_Tr_File->TFilePath);
		
		if (ret_fct == FS_OK)
		{
			memclr(&(pt_Tr_File->FileHeader),sizeof(pt_Tr_File->FileHeader));
			pt_Tr_File->hFile = NULL;
			pt_Tr_File->FileSize = 0;
			pt_Tr_File->TransactionNumber = 0;
			ret = TRANS_FILE_OK;
		}
	}
	else
	{
		ret = TRANS_FILE_NOT_EXISTING;
	}
	return (ret);
}



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

int ClessSample_TransactionFile_CopyValidTrans (T_Transaction_File *pt_In_Tr_File, T_Transaction_File *pt_Out_Tr_File)
{
	int ret;
	int T_length, nb_elt, buffer_size;
	unsigned char * puc_buffer = NULL;
	unsigned char * puc_begin_buffer = NULL;
	unsigned short crc16_read, crc16_calculated;

	ret = TRANS_FILE_OK;

	// Open the existing input transaction file
	pt_In_Tr_File->hFile = FS_open(pt_In_Tr_File->TFilePath, "r");

	if (pt_In_Tr_File->hFile != NULL)
	{
		// Create output transaction file
		pt_Out_Tr_File->hFile = FS_open(pt_Out_Tr_File->TFilePath, "a");

		if (pt_Out_Tr_File->hFile != NULL)
		{
			// Read file header in the input transaction file
			nb_elt = FS_read (&(pt_In_Tr_File->FileHeader), TRANS_FILE_HEADER_SIZE, 1, pt_In_Tr_File->hFile);
			if (nb_elt == 1)
			{
				// Copy file header 
				memcpy (&(pt_Out_Tr_File->FileHeader), &(pt_In_Tr_File->FileHeader), TRANS_FILE_HEADER_SIZE);
				
				// Write file header
				nb_elt = FS_write (&(pt_In_Tr_File->FileHeader), TRANS_FILE_HEADER_SIZE, 1, pt_Out_Tr_File->hFile);

				if (nb_elt == 1)
				{
					do
					{
						// Read data length
						nb_elt = FS_read (&T_length, INT_LEN, 1, pt_In_Tr_File->hFile);
					
						if (nb_elt == 1)
						{
							if (T_length > 0)
							{
								buffer_size = INT_LEN + T_length + CRC_LEN;
								puc_buffer = (unsigned char *) umalloc(buffer_size);
								puc_begin_buffer = puc_buffer;
								
								// Store transaction length
								memcpy (puc_buffer, &T_length, INT_LEN);
								puc_buffer = puc_buffer + INT_LEN;

								// read transaction data
								nb_elt = FS_read (puc_buffer, T_length, 1, pt_In_Tr_File->hFile);

								if (nb_elt == 1)
								{
									// calculate CRC16 on data read
									crc16_calculated = __ClessSample_TransactionFile_crc16_ccitt(puc_buffer, T_length);
									
									// Move buffer index 
									puc_buffer = puc_buffer + T_length;

									// Read data CRC16
									nb_elt = FS_read (&crc16_read, CRC_LEN, 1, pt_In_Tr_File->hFile);
									if (nb_elt == 1)
									{
										if (crc16_calculated == crc16_read)
										{
											// Store transaction CRC
											memcpy (puc_buffer, &crc16_calculated, CRC_LEN);
											//puc_buffer = puc_buffer + CRC_LEN;

											// Add transaction length, data, and CRC16 in the output transaction file
											nb_elt = FS_write (puc_begin_buffer, buffer_size, 1, pt_Out_Tr_File->hFile);

											if (nb_elt == 1)
											{
												// Update field FileSize
												pt_Out_Tr_File->FileSize = pt_Out_Tr_File->FileSize + INT_LEN + T_length + CRC_LEN;

												// Update field TransactionNumber
												pt_Out_Tr_File->TransactionNumber++;
											}
											else
											{
												ret = TRANS_FILE_ADD_ERROR;
											}
										}
										/* else
										{
											ret = TRANS_FILE_CORRUPTED;
										}*/
									}
									else 
									{
										ret = TRANS_FILE_READ_ERROR;
									}
								}
								else
								{
									ret = TRANS_FILE_READ_ERROR;
								}

								if (puc_begin_buffer != 0)
								{
									ufree(puc_begin_buffer);
								}

							}
							else
							{
								ret = TRANS_FILE_READ_ERROR;
							}
						}
						else
						{
							ret = TRANS_FILE_READ_ERROR;
						}
					}
					while (FS_eof(pt_In_Tr_File->hFile) ==  FS_KO);
				}
				else
				{
					ret = TRANS_FILE_ADD_ERROR;
				}
			}
			else
			{
				ret = TRANS_FILE_READ_ERROR;
			}

			FS_close(pt_Out_Tr_File->hFile);
		}
		else
		{
			ret = TRANS_FILE_OPEN_ERROR;
		}

		FS_close(pt_In_Tr_File->hFile);
	}
	else
	{
		ret = TRANS_FILE_OPEN_ERROR;
	}

	return (ret);
	
}



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

int ClessSample_TransactionFile_Rename (T_Transaction_File *pt_In_Tr_File, T_Transaction_File *pt_Out_Tr_File)
{
	int ret;
	
	// Rename the backup transaction file to transaction file
	ret = FS_rename(pt_In_Tr_File->TFilePath, pt_Out_Tr_File->TFilePath);

	if (ret == FS_OK)
	{
		// Update the T_Transaction_File structure
		// Copy file header
		memcpy (&(pt_Out_Tr_File->FileHeader), &(pt_In_Tr_File->FileHeader), TRANS_FILE_HEADER_SIZE);

		// Copy file handle
		pt_Out_Tr_File->hFile = pt_In_Tr_File->hFile;

		// Copy file size
		pt_Out_Tr_File->FileSize = pt_In_Tr_File->FileSize;

		// Copy transaction number
		pt_Out_Tr_File->TransactionNumber = pt_In_Tr_File->TransactionNumber;

	}

	return (ret);
}

//! @}
