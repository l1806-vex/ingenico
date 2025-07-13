/**
 * \file	CST_Receipt.h
 * \brief	Manages the receipt printing.
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

#ifndef __CST_RECEIPT_H__INCLUDED__
#define __CST_RECEIPT_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \brief Ticket type
#define BATCH_TICKET_VISA					0		/*!< Visa payWave receipt. */
#define BATCH_TICKET_MASTERCARD				1		/*!< MasterCard PayPass receipt. */
#define BATCH_TICKET_AMEX					2		/*!< American Express ExpressPay receipt. */
#define BATCH_TICKET_VISAWAVE				3		/*!< VisaWave receipt. */
#define BATCH_TICKET_INTERAC				4		/*!< Interac receipt. */
#define BATCH_TICKET_DISCOVER				5		/*!< Discover receipt. */




/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Format the spending amount for printer or display.
//! \param[in] pAvailableOfflineSpendingAmount in DCB format.
//! \param[in] nLengthSpendingAmount data length.
//! \param[in/out] buffer updated with amount formated.
//! \return
//! 	nothing.

void CST_FormatSpendingAmount(const unsigned char * pAvailableOfflineSpendingAmount, unsigned int nLengthSpendingAmount, char * szSpendingAmount);



//! \brief Print a transaction ticket (for cardholder or merchant) at the end of a transaction or print transaction batch data, according to input parameter (nTicketType).
//! \param[in] pTransaction Shared exchange buffer containing all the transaction data.
//! \param[in] nTicketType Ticket type.
//! \param[in] nTransactionResult APPROVED_TICKED or DECLINED_TICKED
//! \param[in] bSignatureRequested Indicates if signature is requested or not (\a TRUE if requested, \a FALSE else).
//! \param[in] nAOSA : with Available Offline Spending Amount : WITH_AOSA or WITHOUT_AOSA
//! \note Make sure the output driver is already opened before calling this function.

void CST_Receipt_PrintTransaction (T_SHARED_DATA_STRUCT * pTransaction, int nTicketType, int nTransactionResult, const int bSignatureRequested, int nAOSA);



#endif // __CST_RECEIPT_H__INCLUDED__
