/**
 * \file	SDSA_Common.h
 * \brief	Contains several common functions.
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
 */

#ifndef __SDSA_COMMON_H__INCLUDED__
#define __SDSA_COMMON_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


//! \brief Retreive the number of items of an array.
//!	\param[in] Array Concerned array.
#define NUMBER_OF_ITEMS(Array)					(sizeof(Array)/sizeof((Array)[0]))

#define SDSA_COMMON_MODE_NONE				(0)
#define SDSA_COMMON_MODE_EXPLICIT			(1)
#define SDSA_COMMON_MODE_IMPLICIT			(2)


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Get a specific information in a shared buffer.
//! \param[in] pResultDataStruct Shared exchange buffer from which the tag shall be extracted.
//! \param[in] ulTag Tag that shall be extracted.
//! \param[out] pInfo pointer to the requested value
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

int SDSA_Common_RetreiveInfo (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned long ulTag, unsigned char ** pInfo);


//! \brief Format the message that contains the amount, the currency according to ucFormat, ucPosition...  
//! \param[in] ucFormat : format of the displayed amount 
//!                         0 ==> 1.000,00                                   
//!                         1 ==> 1,000.00                                   
//!                         2 ==> 1 000,00                                   
//!                         3 ==> 1.000                                      
//!                         4 ==> 1,000                                      
//!                         5 ==> 1 000                                      
//!                         6 ==> 1.000,000                                  
//!                         7 ==> 1,000.000                                  
//!                         8 ==> 1 000,000    
//! \param[in] ucCurrency : transaction currency
//! \param[in] ucPosition : position of the currency
//!                         0 ==> after the amount                        
//!                         1 ==> before the amount 
//! \param[in] ulAmount : the transaction amount
//! \param[out] pFormattedAmountMessage : the formatted message to display
//! \return : none

void SDSA_Common_FormatAmount(unsigned char ucFormat,unsigned char *ucCurrency,unsigned char ucPosition,unsigned long ulAmount,char *pFormattedAmountMessage);


//! \brief Indicates in which mode the transaction is (None, Implicit or Explicit).
//! \return The transaction mode :
//!	- \ref SDSA_COMMON_MODE_NONE if no transaction is in progress.
//!	- \ref SDSA_COMMON_MODE_EXPLICIT if transaction is in explicit mode.
//!	- \ref SDSA_COMMON_MODE_IMPLICIT if transaction is in implicit mode.

int SDSA_Common_GetTransactionMode (void);


//! \brief Set the transaction mode (None, Implicit or Explicit).
//! \param[in] bTransactionMode The transaction mode to be set :
//!	- \ref SDSA_COMMON_MODE_NONE if no transaction is in progress.
//!	- \ref SDSA_COMMON_MODE_EXPLICIT if transaction is in explicit mode.
//!	- \ref SDSA_COMMON_MODE_IMPLICIT if transaction is in implicit mode.

void SDSA_Common_SetTransactionMode (const int bTransactionMode);


//! \brief Check that all mandatory data to perform a transaction are available.
//! \param[in] hInputTlvTree Contains the input data to perform the transaction.
//! \param[in] pListOfTags contains the list of mandatory tags.
//! \param[in] nNumberOfTags number of tags contained in pListOfTags
//! \return
//!	- \a TRUE if all the mandatory tags are present.
//!	- \a FALSE if a mandatory tag is not present.

int SDSA_Common_CheckMandatoryTagsPresenceTlvTree (const TLV_TREE_NODE hInputTlvTree, const unsigned long * pListOfTags, const int nNumberOfTags);


//! \brief Copy the data in a TLV Tree.
//! \param[in] pDataStruct Data buffer that contains data to add in the TLV Tree.
//! \param[out] hOutputTlvTree Output TLV Tree containing the data.

void SDSA_Common_CopyDataStructInTLVTree (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree);


//! \brief Copy a TLV Tree in a data structure.
//! \param[in] hTlvTree TLV Tree that contains data to had to the data structure.
//! \param[out] pDataStruct Data buffer that will contain the copied data.

void SDSA_Common_CopyTlvTreeInDataStruct (TLV_TREE_NODE hTlvTree, T_SHARED_DATA_STRUCT * pDataStruct);


//! \brief Check if a card is present in the field.
//! \return TRUE if there is a card in the field, FALSE else.

int SDSA_Common_IsCardInFieldDeselection (void);


//! \brief Release the given TlvTree and then set the pointer to NULL

void TlvTree_ReleaseEx(TLV_TREE_NODE* pTlvTree);


//! \brief Save the list of output tags to be returned at the end of the transaction.
//! \param[in] pListOfTags Contains the list of tags
//! \param[in] nListOfTagsLength Length of the list of tags

void SDSA_Common_SetListOfOutputTags(const unsigned char *pListOfTags, const int nListOfTagsLength);


//! \brief Get the requested tags if \ref TAG_SDSA_LIST_OF_OUTPUT_TAGS has been provided.
//! \param[out] hOutputTlvTree Output TLV Tree that will contain the requeted data.
//! \return TRUE if data had been get, FALSE else

int SDSA_Common_GetListOfOutputTags (TLV_TREE_NODE hOutputTlvTree);

#endif // __SDSA_COMMON_H__INCLUDED__
