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
#define CLESS_SAMPLE_TRANSACTION_TYPE_DEBIT                    0x00     /*!< Definition of debit transaction type. */
#define CLESS_SAMPLE_TRANSACTION_TYPE_CASH                     0x01     /*!< Definition of cash transaction type. */
#define CLESS_SAMPLE_TRANSACTION_TYPE_PURSH_WITH_CASHBACK      0x09     /*!< Definition of purshase with cashback transaction type. */
#define CLESS_SAMPLE_TRANSACTION_TYPE_REFUND                   0x20     /*!< Definition of refund transaction type. */

// Amount type
#define CLESS_SAMPLE_AMOUNT_TYPE_BIN				0x00		/*!< Definition of debit amount to manage. */
#define CLESS_SAMPLE_AMOUNT_TYPE_OTHER_BIN			0x01		/*!< Definition of debit amount other to manage. */


//! \brief Retrieve the number of items of an array.
//!	\param[in] Array Concerned array.
#define NUMBER_OF_ITEMS(Array)					(sizeof(Array)/sizeof((Array)[0]))


#define CLESS_SAMPLE_DEVICE_UNDETERMINED			-1
#define CLESS_SAMPLE_DEVICE_UNKNOWN					0

// Terminal types (according to EMV)
#define CLESS_SAMPLE_TERM_TYPE_FINANCIAL_ATT_ONLINE_ONLY		0x11	/*!< Terminal Type - Financial, Attended, Online only. */
#define CLESS_SAMPLE_TERM_TYPE_FINANCIAL_UNATT_ONLINE_ONLY		0x14	/*!< Terminal Type - Financial, Unattended, Online only. */
#define CLESS_SAMPLE_TERM_TYPE_MERCHANT_ATT_ONLINE_ONLY			0x21	/*!< Terminal Type - Merchant, Attended, Online only. */
#define CLESS_SAMPLE_TERM_TYPE_MERCHANT_UNATT_ONLINE_ONLY		0x24	/*!< Terminal Type - Merchant, Unattended, Online only. */
#define CLESS_SAMPLE_TERM_TYPE_CARDHOLDER_UNATT_ONLINE_ONLY		0x34	/*!< Terminal Type - Cardholder, Unattended, Online only. */


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

//! \brief Allows to set transaction state : successfulled or not.
//! \param[in] : TRUE if transaction has been successfulled, FALSE else.
//! \return nothing
void ClessSample_Common_SetTransactionState (int n_Succesful);

//! \brief Allows to known is transaction has been successfulled.
//! \return
//!		- \ref TRUE if transaction has been successfulled.
//!		- \ref FALSE.
int ClessSample_Common_IsTransactionSuccesful (void);

//! \brief Allows to manage transaction state and update output share buffer with data.
//! \param[in] pSharedStruct : share buffer to update
//! \return
//!		- \ref TRUE if transaction has been successfulled.
//!		- \ref FALSE.
void ClessSample_Common_ManageTransactionState (T_SHARED_DATA_STRUCT * pSharedStruct);

//! \brief Allows to initialise output buffer with data used for cashbox.
//! \param[in] pIn : Share buffer to exchange.
//! \param[in] cr_cxce : result for cash register.
//! \param[in] no_appli : application number.
//! \param[in] no_porteur : cardholder number.
//! \return nothing
void ClessSample_Common_cr_caisse(T_SHARED_DATA_STRUCT *pIn, unsigned char cr_cxce, NO_SEGMENT no_appli, NO_PORTEUR no_porteur);

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
