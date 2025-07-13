/**
 * \file
 * This module manages the parameters of a transaction.
 *
 * \author  Ingenico
 * \author  Copyright (c) 2012 Ingenico
 *
 * \author  Ingenico has intellectual property rights relating to the technology embodied \n
 *       in this software. In particular, and without limitation, these intellectual property rights may\n
 *       include one or more patents.\n
 *       This software is distributed under licenses restricting its use, copying, distribution, and\n
 *       and decompilation. No part of this software may be reproduced in any form by any means\n
 *       without prior written authorization of Ingenico.
 */

#include "SDK30.h"
#include "APCLESS.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define APCLESS_TSC_MAX_VALUE           (99999999)       ///< Defines the maximum value of the transaction sequence counter.


/////////////////////////////////////////////////////////////////
//// Global data definitions ////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Static data definitions ////////////////////////////////////

static int __APCLESS_ParamTrn_schemeUsed = APCLESS_SCHEME_UNKNOWN;
static int __APCLESS_ParamTrn_doubleTapInProgress = FALSE;

static int __APCLESS_ParamTrn_debugTrace = FALSE;         // Boolean to activate or not kernel debug traces

// Transaction parameters
static unsigned char __APCLESS_ParamTrn_transactionDate[3] = {0}; // YYMMDD
static unsigned char __APCLESS_ParamTrn_transactionTime[3] = {0}; // HHMMSS
static unsigned char __APCLESS_ParamTrn_isAmountPresent = TRUE;
static unsigned char __APCLESS_ParamTrn_transactionAmountBin[4] = {0};
static unsigned char __APCLESS_ParamTrn_transactionAmountBcd[6] = {0};
static unsigned char __APCLESS_ParamTrn_transactionCurrencyExponent = 2; // Currency exponent is 2
static unsigned char __APCLESS_ParamTrn_transactionCurrencyCode[2] = {0x09,0x78};  // euro
static unsigned char __APCLESS_ParamTrn_transactionType = APCLESS_TRANSACTION_TYPE_DEBIT; //purchase
static unsigned long __APCLESS_ParamTrn_transactionSequenceCounter = 1;   // Application Transaction Sequence Counter

/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


/**
 * Clear the transaction data.
 */
void APCLESS_ParamTrn_Clear(void)
{
   APCLESS_ParamTrn_SetTransactionType(APCLESS_TRANSACTION_TYPE_DEBIT);  // by default the transaction is a debit
   APCLESS_ParamTrn_SetAmountBcd(NULL);     // it also resets AmountBin & AmountPresent
   APCLESS_ParamTrn_SetCurrencyCode(NULL);
   __APCLESS_ParamTrn_transactionCurrencyExponent = 0;
   memset(__APCLESS_ParamTrn_transactionDate, 0 , sizeof(__APCLESS_ParamTrn_transactionDate));
   memset(__APCLESS_ParamTrn_transactionTime, 0 , sizeof(__APCLESS_ParamTrn_transactionTime));
}


/**
 * Set the current transaction type.
 * @param type \ref APCLESS_TRANSACTION_TYPE_DEBIT, \ref APCLESS_TRANSACTION_TYPE_CASH or \ref APCLESS_TRANSACTION_TYPE_REFUND.
 */
void APCLESS_ParamTrn_SetTransactionType(unsigned char type)
{
   __APCLESS_ParamTrn_transactionType = type;
}


/**
 * Get the current transaction type.
 * @return \ref APCLESS_TRANSACTION_TYPE_DEBIT, \ref APCLESS_TRANSACTION_TYPE_CASH or \ref APCLESS_TRANSACTION_TYPE_REFUND.
 */
unsigned char APCLESS_ParamTrn_GetTransactionType(void)
{
   return __APCLESS_ParamTrn_transactionType;
}


/**
 * Set the transaction amount.
 * @param[in] amountBcd pointer to a six bytes array containing the amount value in Bcd
 *             or NULL to reset amount.
 */
void APCLESS_ParamTrn_SetAmountBcd(unsigned char* amountBcd)
{
   unsigned long ulTemp;

   if(amountBcd != NULL)
   {
      memcpy(__APCLESS_ParamTrn_transactionAmountBcd, amountBcd, sizeof(__APCLESS_ParamTrn_transactionAmountBcd));
      GTL_Convert_DcbNumberToUl(__APCLESS_ParamTrn_transactionAmountBcd, &ulTemp, sizeof(__APCLESS_ParamTrn_transactionAmountBcd));
      GTL_Convert_UlToBinNumber(ulTemp, __APCLESS_ParamTrn_transactionAmountBin, sizeof(__APCLESS_ParamTrn_transactionAmountBin));
      __APCLESS_ParamTrn_isAmountPresent = TRUE;
   }
   else
   {
      memset(__APCLESS_ParamTrn_transactionAmountBcd, 0, sizeof(__APCLESS_ParamTrn_transactionAmountBcd));
      memset(__APCLESS_ParamTrn_transactionAmountBin, 0, sizeof(__APCLESS_ParamTrn_transactionAmountBin));
      __APCLESS_ParamTrn_isAmountPresent = FALSE;
   }
}


/**
 * Get the transaction amount in Bcd.
 * @return
 *    - pointer to a six bytes array of the amount in Bcd
 *    - or NULL if amount not present.
 */
const unsigned char* APCLESS_ParamTrn_GetAmountBcd(void)
{
   if(__APCLESS_ParamTrn_isAmountPresent == TRUE)
      return __APCLESS_ParamTrn_transactionAmountBcd;
   else
      return NULL;
}


/**
 * Get the transaction amount in binary.
 * @return
 *    - pointer to a 4 bytes array of the binary amount (MSB)
 *    - or NULL if amount not present.
 */
const unsigned char* APCLESS_ParamTrn_GetAmountBin(void)
{
   if(__APCLESS_ParamTrn_isAmountPresent == TRUE)
      return __APCLESS_ParamTrn_transactionAmountBin;
   else
      return NULL;
}


/**
 * Set the transaction currency code.
 * @param[in] currencyCode pointer to a 2 bytes array containing the currency code in Bcd.
 */
void APCLESS_ParamTrn_SetCurrencyCode(unsigned char* currencyCode)
{
   if(currencyCode != NULL)
   {
      memcpy(__APCLESS_ParamTrn_transactionCurrencyCode, currencyCode, sizeof(__APCLESS_ParamTrn_transactionCurrencyCode));
   }
   else
   {
      memset(__APCLESS_ParamTrn_transactionCurrencyCode, 0, sizeof(__APCLESS_ParamTrn_transactionCurrencyCode));
   }
}


/**
 * Get the transaction currency code in Bcd.
 * @return pointer to a 2 bytes array of the currency code in Bcd.
 */
const unsigned char* APCLESS_ParamTrn_GetCurrencyCode(void)
{
   return __APCLESS_ParamTrn_transactionCurrencyCode;
}


/**
 * Set the transaction currency exponent.
 * @param[in] currencyExponent the currency exponent.
 */
void APCLESS_ParamTrn_SetCurrencyExponent(unsigned char currencyExponent)
{
   __APCLESS_ParamTrn_transactionCurrencyExponent = currencyExponent;
}


/**
 * Get the transaction currency exponent.
 * @return pointer to a byte of the currency exponent.
 */
const unsigned char* APCLESS_ParamTrn_GetCurrencyExponent(void)
{
   return &__APCLESS_ParamTrn_transactionCurrencyExponent;
}


/**
 * Set the transaction date and time with the current terminal date and time.
 */
void APCLESS_ParamTrn_SetDateTime(void)
{
   DATE date;

   if(0 == read_date(&date))
   {
      __APCLESS_ParamTrn_transactionDate[0] = (unsigned char)(((date.year[0] - '0') << 4) | (date.year[1] - '0'));
      __APCLESS_ParamTrn_transactionDate[1] = (unsigned char)(((date.month[0] - '0') << 4) | (date.month[1] - '0'));
      __APCLESS_ParamTrn_transactionDate[2] = (unsigned char)(((date.day[0] - '0') << 4) | (date.day[1] - '0'));

      __APCLESS_ParamTrn_transactionTime[0] = (unsigned char)(((date.hour[0] - '0') << 4) | (date.hour[1] - '0'));
      __APCLESS_ParamTrn_transactionTime[1] = (unsigned char)(((date.minute[0] - '0') << 4) | (date.minute[1] - '0'));
      __APCLESS_ParamTrn_transactionTime[2] = (unsigned char)(((date.second[0] - '0') << 4) | (date.second[1] - '0'));
   }
   else
   {
      memset(__APCLESS_ParamTrn_transactionDate, 0 , sizeof(__APCLESS_ParamTrn_transactionDate));
      memset(__APCLESS_ParamTrn_transactionTime, 0 , sizeof(__APCLESS_ParamTrn_transactionTime));
   }
}


/**
 * Get the transaction date.
 * @return pointer to a 3 bytes array of the date.
 */
const unsigned char* APCLESS_ParamTrn_GetDate(void)
{
   return __APCLESS_ParamTrn_transactionDate;
}


/**
 * Get the transaction time.
 * @return pointer to a 3 bytes array of the time.
 */
const unsigned char* APCLESS_ParamTrn_GetTime(void)
{
   return __APCLESS_ParamTrn_transactionTime;
}


/**
 * Set the global data indicating double tap is in progress.
 * @param[in] iDoubleTapInProgress  \a TRUE if double tap is in progress, \a FALSE else.
 */
void APCLESS_ParamTrn_SetDoubleTapInProgress(int iDoubleTapInProgress)
{
   __APCLESS_ParamTrn_doubleTapInProgress = iDoubleTapInProgress;
}


/**
 * Indicates if double tap is in progress or not.
 * @return
 *    - \a TRUE if double tap is in progress.
 *    - \a FALSE else.
 */
int APCLESS_ParamTrn_GetDoubleTapInProgress(void)
{
   return __APCLESS_ParamTrn_doubleTapInProgress;
}


/**
 * Set the used payment scheme.
 * @param[in] scheme Indicates the used scheme.
 */
void APCLESS_ParamTrn_SetCurrentPaymentScheme(int scheme)
{
   __APCLESS_ParamTrn_schemeUsed = scheme;
}


/**
 * Get the used payment scheme.
 * @return The used scheme:
 *    - \a APCLESS_SCHEME_UNKNOWN Scheme is not yet known.
 *    - \a APCLESS_SCHEME_PAYPASS Scheme is PayPass.
 *    - \a APCLESS_SCHEME_PAYWAVE Scheme is payWave.
 *    - \a APCLESS_SCHEME_VISAWAVE Scheme is VisaWave.
 *    - \a APCLESS_SCHEME_EXPRESSPAY Scheme is ExpressPay.
 *    - \a APCLESS_SCHEME_DISCOVER Scheme is Discover.
 */
int APCLESS_ParamTrn_GetCurrentPaymentScheme(void)
{
   return __APCLESS_ParamTrn_schemeUsed;
}


/**
 * Increment the Transaction sequence counter by 1.
 * @note use flash to store the Transaction counter
 */
void APCLESS_ParamTrn_IncrementTsc(void)
{
   // TODO: Manage Tsc in a persistent way
   if (__APCLESS_ParamTrn_transactionSequenceCounter >= APCLESS_TSC_MAX_VALUE)
      __APCLESS_ParamTrn_transactionSequenceCounter = 1;
   else
      __APCLESS_ParamTrn_transactionSequenceCounter++;
}


/**
 * Add the transaction sequence counter into a shared buffer structure (with tag TAG_EMV_TRANSACTION_SEQUENCE_COUNTER).
 * @param[out] dataBuffer Shared buffer in which the transaction sequence counter is added.
 * @return
 *     - \a TRUE if correctly added.
 *     - \a FALSE if an error occurred.
 */
int APCLESS_ParamTrn_AddTscToSharedBuffer (T_SHARED_DATA_STRUCT* dataBuffer)
{
   unsigned char tsc[4];

   // Convert the TSC
   GTL_Convert_UlToDcbNumber(__APCLESS_ParamTrn_transactionSequenceCounter, tsc, 4);

   if(STATUS_SHARED_EXCHANGE_OK != GTL_SharedExchange_AddTag (dataBuffer, TAG_EMV_TRANSACTION_SEQUENCE_COUNTER, 4, tsc))
   {
      // An error occurred when adding the Transaction Sequence Counter into the shared buffer.
      return FALSE;
   }

   return TRUE;
}


/**
 * Set the debug trace value.
 * @param trace
 *    - TRUE to enable the kernel debug traces,
 *    - FALSE to disable the kernel debug traces.
 */
void APCLESS_ParamTrn_SetDebugTrace(int trace)
{
   __APCLESS_ParamTrn_debugTrace = (trace == FALSE)? FALSE : TRUE;
}


/**
 * Get the debug trace value.
 * @return
 *    - \a TRUE if kernel debug traces should be activated,
 *    - \a FALSE (default) otherwise.
 */
int APCLESS_ParamTrn_GetDebugTrace(void)
{
   return __APCLESS_ParamTrn_debugTrace;
}



