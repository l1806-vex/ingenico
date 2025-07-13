/**
 * \file
 * \brief Header file for the parameters of the current transaction.
 *
 * \author  Ingenico
 *
 * \author  Ingenico has intellectual property rights relating to the technology embodied \n
 *       in this software. In particular, and without limitation, these intellectual property rights may\n
 *       include one or more patents.\n
 *       This software is distributed under licenses restricting its use, copying, distribution, and\n
 *       and decompilation. No part of this software may be reproduced in any form by any means\n
 *       without prior written authorization of Ingenico.
 */

#ifndef APCLESS_PARAMTRN_H_INCLUDED
#define APCLESS_PARAMTRN_H_INCLUDED

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define C_SHARED_KERNEL_BUFFER_SIZE          16384    ///< Maximum size of the shared buffer exchanged between this application and the kernels.

#define APCLESS_SCHEME_UNKNOWN         0x00     ///< Indicates current transaction is unknown.
#define APCLESS_SCHEME_PAYPASS         0x01     ///< Indicates current transaction is a PayPass transaction.
#define APCLESS_SCHEME_PAYWAVE         0x02     ///< Indicates current transaction is a payWave transaction.
#define APCLESS_SCHEME_VISAWAVE        0x03     ///< Indicates current transaction is a VisaWave transaction.
#define APCLESS_SCHEME_EXPRESSPAY      0x04     ///< Indicates current transaction is a ExpressPay transaction.
#define APCLESS_SCHEME_DISCOVER        0x05     ///< Indicates current transaction is a Discover transaction.
#define APCLESS_SCHEME_INTERAC         0x06     ///< Indicates current transaction is a Interac transaction.

// Transaction type
#define APCLESS_TRANSACTION_TYPE_DEBIT       0x00     ///< Definition of debit transaction type.
#define APCLESS_TRANSACTION_TYPE_CASH        0x01     ///< Definition of cash transaction type.
#define APCLESS_TRANSACTION_TYPE_REFUND      0x20     ///< Definition of refund transaction type.


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


void APCLESS_ParamTrn_Clear(void);

void APCLESS_ParamTrn_SetTransactionType(unsigned char type);

unsigned char APCLESS_ParamTrn_GetTransactionType(void);

void APCLESS_ParamTrn_SetAmountBcd(unsigned char* amountBcd);

const unsigned char* APCLESS_ParamTrn_GetAmountBcd(void);

const unsigned char* APCLESS_ParamTrn_GetAmountBin(void);

void APCLESS_ParamTrn_SetCurrencyCode(unsigned char* currencyCode);

const unsigned char* APCLESS_ParamTrn_GetCurrencyCode(void);

void APCLESS_ParamTrn_SetCurrencyExponent(unsigned char currencyExponent);

const unsigned char* APCLESS_ParamTrn_GetCurrencyExponent(void);

void APCLESS_ParamTrn_SetDateTime(void);

const unsigned char* APCLESS_ParamTrn_GetDate(void);

const unsigned char* APCLESS_ParamTrn_GetTime(void);

void APCLESS_ParamTrn_SetDoubleTapInProgress(int doubleTapInProgress);

int APCLESS_ParamTrn_GetDoubleTapInProgress(void);

void APCLESS_ParamTrn_SetCurrentPaymentScheme(int scheme);

int APCLESS_ParamTrn_GetCurrentPaymentScheme(void);

void APCLESS_ParamTrn_IncrementTsc(void);

int APCLESS_ParamTrn_AddTscToSharedBuffer(T_SHARED_DATA_STRUCT* dataBuffer);

void APCLESS_ParamTrn_SetDebugTrace(int trace);

int APCLESS_ParamTrn_GetDebugTrace(void);


#endif //APCLESS_PARAMTRN_H_INCLUDED
