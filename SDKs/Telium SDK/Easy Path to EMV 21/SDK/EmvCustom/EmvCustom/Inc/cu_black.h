/**
* \file cu_black.h
* \brief This module contains the functions that manages the black list.
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


#ifndef CU_BLACKL_H
#define CU_BLACKL_H

//! \defgroup Group_cu_black Black list management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

//! \brief This structure defines the data used for black list management.
typedef struct
{
	unsigned char PAN[12];						//!< Application Primary Account Number.
} T_CUBLACKL_data ;

//! \brief This structure defines the date used for black list management.
typedef struct
{
	unsigned char date [3];						//!< Date with the following format : YY MM DD.
} T_CUBLACKL_date ;

#define CUBLACKL_DEF_FILE_SIZE        100		//!< Maximum number of elements in black list definition file.

//! \brief This structure defines the data used for black list management.
typedef struct
{
	unsigned long black_list_max_size;			//!< Maximum size for black list.
	unsigned long nb_record;					//!< Number of records in black list.
	T_CUBLACKL_date activation_date;			//!< black list activation date.
	T_CUBLACKL_date expiration_date;			//!< black list expiration date.
} T_CUBLACKL_management_data ;


/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function creates the black list file according with the size
//! given as parameter. If the file already exists, nothing is done.
//! \param[in] black_list_size : maximum number of records in the file.
//! \return 
//! - TRUE if file successfuly created.
//! - FALSE if file already exists.
//===========================================================================
extern T_Bool CUBLACKL_CreateFile(unsigned long black_list_size);

//===========================================================================
//! \brief This function erases the black list file.
//===========================================================================
extern void CUBLACKL_DeleteBlackList(void);

//===========================================================================
//! \brief This function seeks a Primary account number in black list.
//! \param[in] PAN : Primary account number seeked.
//! \param[in] lg : Primary account number length.
//! \param[in] is_presentPAN_seq_number : boolean to indicate the test of primary 
//! account number sequence.
//! \param[in] PAN_seq_number : primary account number sequence to test.
//! \return 
//! - TRUE if primary account number is present in black-list.
//! - FALSE otherwise.
//===========================================================================
T_Bool CUBLACKL_IsInBlackList  ( unsigned char PAN[10], unsigned short lg,
								T_Bool is_presentPAN_seq_number,unsigned char PAN_seq_number);

//===========================================================================
//! \brief This function replaces the current black list by the one given as 
//! parameter.
//! \param[in] BlackListFile : file containing the new black list.
//! \param[in] BlackListSize : number of records of the new black list.
//! \param[in] ExpirationDate : expiration date of the new black list.
//! \return 
//! - TRUE if black list successfully replaced.
//! - FALSE otherwise.
//===========================================================================
T_Bool CUBLACKL_ReplaceBlackList (unsigned char *BlackListFile,
								  unsigned long BlackListSize,
								  T_CUBLACKL_date ExpirationDate);


//===========================================================================
//! \brief This function tests if the current black-list is valid.
//! \return 
//! - non zero if the current black list valid.
//! - zero otherwise.
//===========================================================================
unsigned short CUBLACKL_IsValid (void);

//! @}

#endif
