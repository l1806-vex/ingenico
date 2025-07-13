/**
 * \file	ClessSample_Common.h
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

#ifndef __CLESS_SAMPLE_COMMON_H__INCLUDED__
#define __CLESS_SAMPLE_COMMON_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


// Transaction type
#define CLESS_SAMPLE_TRANSACTION_TYPE_DEBIT						0x00									/*!< Definition of debit transaction type. */
#define CLESS_SAMPLE_TRANSACTION_TYPE_CASH						0x01									/*!< Definition of cash transaction type. */
#define CLESS_SAMPLE_TRANSACTION_TYPE_PURSH_WITH_CASHBACK		0x09									/*!< Definition of purshase with cashback transaction type. */
#define CLESS_SAMPLE_TRANSACTION_TYPE_MANUAL_CASH				0x12									/*!< Definition of manual cash transaction type. */
#define CLESS_SAMPLE_TRANSACTION_TYPE_REFUND					0x20									/*!< Definition of refund transaction type. */
#define CLESS_SAMPLE_TRANSACTION_TYPE_CASH_DEPOSIT				0x21									/*!< Definition of cash deposit transaction type. */
#define CLESS_SAMPLE_TRANSACTION_TYPE_DEFAULT					CLESS_SAMPLE_TRANSACTION_TYPE_DEBIT		/*!< Sample define : indicates the default transaction type to use. */

// Amount type
///#define CLESS_SAMPLE_AMOUNT_TYPE_BIN				0x00									/*!< Definition of debit amount to manage. */
///#define CLESS_SAMPLE_AMOUNT_TYPE_OTHER_BIN			0x01									/*!< Definition of debit amount other to manage. */

// Transaction modes
#define CLESS_SAMPLE_TRANSACTION_MODE_UNKNOWN		0x00
#define CLESS_SAMPLE_TRANSACTION_MODE_IMPLICIT		0x01
#define CLESS_SAMPLE_TRANSACTION_MODE_EXPLICIT		0x02


//! \brief retrieve the number of items of an array.
//!	\param[in] Array Concerned array.
#define NUMBER_OF_ITEMS(Array)						(sizeof(Array)/sizeof((Array)[0]))

#define CLESS_SAMPLE_DEVICE_UNDETERMINED			-1
#define CLESS_SAMPLE_DEVICE_UNKNOWN					0

/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Extract the status code (TAG_KERNEL_STATUS_CODE) from a shared exchange buffer.
//! \param[in] pSharedStruct Shared exchange buffer from which the status code shall be extracted.
//! \return The exctracted status code.
int ClessSample_Common_GetStatusCode (T_SHARED_DATA_STRUCT * pSharedStruct);

//! \brief Get a specific information in a shared buffer.
//! \param[out] pSpendingAmount pointer
//! \return
//!		- \ref TRUE if correctly retrieved.
//!		- \ref FALSE if an error occurred.
int ClessSample_Common_RetrieveInfo (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned long ulTag, unsigned char ** pInfo);

//! \brief Get a specific information in a TlvTree.
//! \param[in] pTlvTree Tree node.
//! \param[in] ulTag Tag to be found.
//! \param[out] pReadLength Read length in relation with tag asked.
//! \param[out] pReadValue Read value in relation with tag asked.
//! \return
//!		- \ref TRUE if correctly retrieved.
//!		- \ref FALSE if an error occurred.

int ClessSample_Common_GetTagInTlvTree (TLV_TREE_NODE pTlvTree, unsigned long ulTag, unsigned int *pReadLength, unsigned char ** pReadValue);

//! \brief Format the message that contains the amount, the currency according to ucFormat, ucPosition...  
//! \param[in] ucFormat : the display format
//! \param[in] ucCurrency : transaction currency
//! \param[in] ucPosition : the position of the currency
//! \param[in] ulAmount : the transaction amount
//! \param[out] pFormattedAmountMessage : the formatted message to display
void ClessSample_Common_FormatAmount (unsigned char ucFormat, char *ucCurrency, unsigned char ucPosition, unsigned long ulAmount, char *pFormattedAmountMessage);

//! \brief Requests amount entry, prepare frame for Entry Point (fill shared memory)
//! \param[in] bEnterAmountOther \a TRUE if amount other shall be enetered (change the label).
//! \param[in] pCurrencyLabel : the currency label
//! \param[out] pAmountBin : the entered transaction amount
//! \return 
//!		- TRUE if amount has been entered.
//!		- FALSE if amount entry has been cancelled.
int ClessSample_Common_AmountEntry (const int bEnterAmountOther, const unsigned char *pCurrencyLabel, unsigned long * pAmountBin);

//! \brief Set the transaction mode.
//! \param[in] nMode Transaction mode (implicit or explicit).
void ClessSample_Common_SetTransactionMode (const int nMode);

//! \brief Get the transaction mode.
//! \return The transaction mode.
int ClessSample_Common_GetTransactionMode (void);

//! \brief This function returns the number of days bewteen two dates.
//! \param[in] date1 First date
//! \param[in] date2 Second date
//! \returns the number of days between date1 and date2.
//! \note No date check is done, so the provided dates shall be valid !
int ClessSample_Common_NumberOfDaysBetweenTwoDates (DATE *date1, DATE *date2);

//! \brief Determine the type of terminal.
//! \return The type of terminal.
int ClessSample_Common_GetTerminalType (void);


#endif // __CLESS_SAMPLE_COMMON_H__INCLUDED__
