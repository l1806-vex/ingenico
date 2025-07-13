/**
 * \file
 * This module manages a Mastercard PayPass 3 transaction.
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


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////
#include "SDK30.h"
#include "APCLESS.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

static unsigned char __APCLESS_PayPass_caKeyF3Modulus[] =
     {0x98, 0xF0, 0xC7, 0x70, 0xF2, 0x38, 0x64, 0xC2, 0xE7, 0x66, 0xDF, 0x02, 0xD1, 0xE8, 0x33, 0xDF,
      0xF4, 0xFF, 0xE9, 0x2D, 0x69, 0x6E, 0x16, 0x42, 0xF0, 0xA8, 0x8C, 0x56, 0x94, 0xC6, 0x47, 0x9D,
      0x16, 0xDB, 0x15, 0x37, 0xBF, 0xE2, 0x9E, 0x4F, 0xDC, 0x6E, 0x6E, 0x8A, 0xFD, 0x1B, 0x0E, 0xB7,
      0xEA, 0x01, 0x24, 0x72, 0x3C, 0x33, 0x31, 0x79, 0xBF, 0x19, 0xE9, 0x3F, 0x10, 0x65, 0x8B, 0x2F,
      0x77, 0x6E, 0x82, 0x9E, 0x87, 0xDA, 0xED, 0xA9, 0xC9, 0x4A, 0x8B, 0x33, 0x82, 0x19, 0x9A, 0x35,
      0x0C, 0x07, 0x79, 0x77, 0xC9, 0x7A, 0xFF, 0x08, 0xFD, 0x11, 0x31, 0x0A, 0xC9, 0x50, 0xA7, 0x2C,
      0x3C, 0xA5, 0x00, 0x2E, 0xF5, 0x13, 0xFC, 0xCC, 0x28, 0x6E, 0x64, 0x6E, 0x3C, 0x53, 0x87, 0x53,
      0x5D, 0x50, 0x95, 0x14, 0xB3, 0xB3, 0x26, 0xE1, 0x23, 0x4F, 0x9C, 0xB4, 0x8C, 0x36, 0xDD, 0xD4,
      0x4B, 0x41, 0x6D, 0x23, 0x65, 0x40, 0x34, 0xA6, 0x6F, 0x40, 0x3B, 0xA5, 0x11, 0xC5, 0xEF, 0xA3};

static unsigned char __APCLESS_PayPass_caKeyF3Exponent[] = {0x03};

/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __APCLESS_PayPass_AddPayPassSpecificData(T_SHARED_DATA_STRUCT* dataStruct);
static int __APCLESS_PayPass_RetrieveTransactionOutcome(T_SHARED_DATA_STRUCT* resultDataStruct, int* pTransactionOutcome);
static int __APCLESS_PayPass_RetrieveStart(T_SHARED_DATA_STRUCT* resultDataStruct, int* pStart);
static int __APCLESS_PayPass_RetrieveErrorIndicationByte(T_SHARED_DATA_STRUCT* resultDataStruct, const unsigned int nByteNumber, unsigned char* pErrorIndicationByte);
static int __APCLESS_PayPass_RetrieveUirdMessage(T_SHARED_DATA_STRUCT* resultDataStruct, int* pUirdMessage);
static int __APCLESS_PayPass_RetrieveCvmToApply(T_SHARED_DATA_STRUCT* resultDataStruct, unsigned char* pCvm);
static int __APCLESS_PayPass_RetrieveFieldOffValue(T_SHARED_DATA_STRUCT* resultDataStruct, unsigned char* pFieldOff);
static int __APCLESS_PayPass_RetrieveCardType(T_SHARED_DATA_STRUCT* resultDataStruct, unsigned short* cardType);
static int __APCLESS_PayPass_IsReceiptRequired(T_SHARED_DATA_STRUCT* resultDataStruct, int* isReceiptRequired);
static int __APCLESS_PayPass_DisplayApprovedWithBalance(T_SHARED_DATA_STRUCT* resultDataStruct);
static void __APCLESS_PayPass_DisplayUirdMsg(T_SHARED_DATA_STRUCT* dataStruct, const int isPhoneMessage);
static void __APCLESS_PayPass_DebugActivation(int activate);
static void __APCLESS_PayPass_AddRecordToBatch(T_SHARED_DATA_STRUCT * sharedData);
static void __APCLESS_PayPass_CopyCAKeyF3(T_SHARED_DATA_STRUCT* outputDataStruct);

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


/**
 * Fill buffer with specific PayPass for transaction (custom steps, stop steps ...).
 * @param[out] dataStruct Shared exchange structure filled with the specific PayPass data.
 * @return
 *    - \a TRUE if correctly retrieved.
 *    - \a FALSE if an error occurred.
 */
static int __APCLESS_PayPass_AddPayPassSpecificData(T_SHARED_DATA_STRUCT* dataStruct)
{
   int cr;
   int result = FALSE;
   object_info_t ObjectInfo;
   T_KERNEL_TRANSACTION_FLOW_CUSTOM sTransactionFlowCustom;
   unsigned char StepInterruption[KERNEL_PAYMENT_FLOW_STOP_LENGTH];// Bit field to stop payment flow,
                                                   // if all bit set to 0 => no stop during payment process
                                                           // if right bit set to 1 : stop after payment step number 1
   unsigned char StepCustom[KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH];   // Bit field to custom payment flow,
                                                   // if all bit set to 0 => no stop during payment process
                                                           // if right bit set to 1 : stop after payment step number 1
#ifdef PAYPASS_TORN
   unsigned char ucTornRecordNumber;
   unsigned char ucTornMaxRecordNumber;
#endif


   // Check the input data are correctly provided
   if (dataStruct == NULL)
   {
      goto End;
   }

   // Init parameteters
   memset(StepInterruption, 0, sizeof(StepInterruption)); // Default Value : not stop on process
   memset(StepCustom, 0, sizeof(StepCustom)); // Default Value : not stop on process
   ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);

   // Add a tag indicating where the transaction has to be stopped (default value, i.e. all bytes set to 0, is strongly recommended)
   cr = GTL_SharedExchange_AddTag(dataStruct, TAG_KERNEL_PAYMENT_FLOW_STOP, KERNEL_PAYMENT_FLOW_STOP_LENGTH, (const unsigned char *)StepInterruption);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }


   // Customize steps
   ADD_STEP_CUSTOM(STEP_PAYPASS_MSTRIPE_REMOVE_CARD, StepCustom); // To do GUI when MStripe card has been read
   ADD_STEP_CUSTOM(STEP_PAYPASS_MCHIP_REMOVE_CARD, StepCustom); // To do GUI when MChip card has been read
   ADD_STEP_CUSTOM(STEP_PAYPASS_MCHIP_GET_CERTIFICATE, StepCustom); // To provide the CA key data for ODA
   ADD_STEP_CUSTOM(STEP_PAYPASS_MCHIP_SEND_PHONE_MSG, StepCustom);      // To do GUI when MChip phone has been read
   ADD_STEP_CUSTOM(STEP_PAYPASS_MSTRIPE_SEND_PHONE_MSG, StepCustom); // To do GUI when MStripe phone has been read

   // TODO: If BlackList Present  ADD_STEP_CUSTOM(STEP_PAYPASS_MCHIP_EXCEPTION_FILE_GET_DATA, StepCustom);

#ifdef PAYPASS_TORN
   {
      ADD_STEP_CUSTOM(STEP_PAYPASS_MCHIP_IS_TORN_RECORD, StepCustom);      // To check if transaction is in the torn transaction log
      ADD_STEP_CUSTOM(STEP_PAYPASS_MCHIP_ADD_TORN_RECORD, StepCustom);  // To add a transaction in the torn transaction log
      ADD_STEP_CUSTOM(STEP_PAYPASS_MCHIP_REMOVE_TORN_RECORD, StepCustom);  // To remove a transaction from the torn transaction log

      // Add TAG_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS
      ucTornMaxRecordNumber = APCLESS_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS;
      cr = GTL_SharedExchange_AddTag(dataStruct, TAG_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS, 1, &ucTornMaxRecordNumber);
      if (cr != STATUS_SHARED_EXCHANGE_OK)
      {
         goto End;
      }

      // Add data indicating the number of records in the torn transaction log.
      ucTornRecordNumber = APCLESS_PayPassTorn_GetNumberOfTornTxnLogRecords();
      if (ucTornRecordNumber > 0)
      {
         cr = GTL_SharedExchange_AddTag(dataStruct, TAG_PAYPASS_NUMBER_OF_TORN_TXN_LOG_RECORDS, 1, &ucTornRecordNumber);
         if (cr != STATUS_SHARED_EXCHANGE_OK)
         {
            goto End;
         }
      }
   }
#endif

   memcpy(sTransactionFlowCustom.pucStepCustom, (void*)StepCustom, KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH);
   sTransactionFlowCustom.usApplicationType = ObjectInfo.application_type; // Kernel will call this application for customisation
   sTransactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL; // Kernel will call SERVICE_CUSTOM_KERNEL service id for customisation

   cr = GTL_SharedExchange_AddTag(dataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_KERNEL_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }


   result = TRUE;

End:
   return result;
}


/**
 * Activate or not the PayPass kernel debug features.
 * @param[in] activate
 *    - TRUE : activate the PayPass kernel traces
 *    - FASLE : deactivate the PayPass kernel traces
 */
static void __APCLESS_PayPass_DebugActivation(int activate)
{
   T_SHARED_DATA_STRUCT* sharedStructure;
   int result;
   unsigned char debugMode = 0x00;

   if (activate)
      debugMode = KERNEL_DEBUG_MASK_TRACES;   // Provide debug information in the Trace.exe tool

   sharedStructure = GTL_SharedExchange_InitShared(256);

   if (sharedStructure != NULL)
   {
      result = GTL_SharedExchange_AddTag(sharedStructure, TAG_KERNEL_DEBUG_ACTIVATION, 1, &debugMode);

      if (result == STATUS_SHARED_EXCHANGE_OK)
      {
         result = PayPass3_DebugManagement(sharedStructure);
      }

      // Destroy the shared buffer
      GTL_SharedExchange_DestroyShare(sharedStructure);
   }
}


/**
 * Get the PayPass transaction outcome from the Outcome Parameter Set.
 * @param[in] resultDataStruct Structure containing the PayPass 3 kernel output.
 * @param[out] pTransactionOutcome Retrieved transaction outcome :
 *    - \a PAYPASS_OPS_STATUS_APPROVED if transaction is approved.
 *    - \a PAYPASS_OPS_STATUS_ONLINE_REQUEST if an online authorisation is requested.
 *    - \a PAYPASS_OPS_STATUS_DECLINED if the transaction is declined.
 *    - \a PAYPASS_OPS_STATUS_SELECT_NEXT if next AID shall be selected.
 *    - \a PAYPASS_OPS_STATUS_TRY_AGAIN transaction shall be restarted from the beginning..
 *    - \a PAYPASS_OPS_STATUS_END_APPLICATION if the transaction is terminated.
 * @return
 *    - \a TRUE if correctly retrieved.
 *    - \a FALSE if an error occurred.
 */
static int __APCLESS_PayPass_RetrieveTransactionOutcome(T_SHARED_DATA_STRUCT* resultDataStruct, int* pTransactionOutcome)
{
   int result = TRUE;
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;

   // Init position
   position = SHARED_EXCHANGE_POSITION_NULL;

   // Init output data
   if (pTransactionOutcome != NULL)
      *pTransactionOutcome = PAYPASS_OPS_STATUS_END_APPLICATION;

   // Get the Outcome Parameter Set
   cr = GTL_SharedExchange_FindNext(resultDataStruct, &position, TAG_PAYPASS_OUTCOME_PARAMETER_SET, &readLength, &readValue);

   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      result = FALSE;
      goto End;
   }

   // Get the transaction outcome
   if (pTransactionOutcome != NULL)
      *pTransactionOutcome = readValue[PAYPASS_OPS_STATUS_BYTE];

End:
   return result;
}


/**
 * Get the start byte from the Outcome Parameter Set.
 * @param[in] resultDataStruct Structure containing the PayPass 3 kernel output.
 * @param[out] pStart Retrieved start value :
 *    - \a PAYPASS_OPS_START_A if transaction needs to start at A.
 *    - \a PAYPASS_OPS_START_B if transaction needs to start at B.
 *    - \a PAYPASS_OPS_START_C if transaction needs to start at C.
 *    - \a PAYPASS_OPS_START_D if transaction needs to start at D.
 * @return
 *    - \a TRUE if correctly retrieved.
 *    - \a FALSE if an error occurred.
 */
static int __APCLESS_PayPass_RetrieveStart(T_SHARED_DATA_STRUCT* resultDataStruct, int* pStart)
{
   int result = TRUE;
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;

   // Init position
   position = SHARED_EXCHANGE_POSITION_NULL;

   // Init output data
   if (pStart != NULL)
      *pStart = PAYPASS_OPS_START_NA;

   // Get the Outcome Parameter Set
   cr = GTL_SharedExchange_FindNext(resultDataStruct, &position, TAG_PAYPASS_OUTCOME_PARAMETER_SET, &readLength, &readValue);

   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      result = FALSE;
      goto End;
   }

   // Get the start value
   if (pStart != NULL)
      *pStart = readValue[PAYPASS_OPS_START_BYTE];

End:
   return result;
}


/**
 * Get the PayPass Error Indication required byte (extracted from the Discretionary Data).
 * @param[in] resultDataStruct Structure containing the PayPass 3 kernel output.
 * @param[in] nByteNumber byte number to be returned (shall be in [0;5]).
 * @param[out] pErrorIndicationByte Retrieved byte.Retrieved transaction outcome :
 *      - Value if correctly retrieved.
 *      - \a 0xFF if not.
 * @return
 *    - \a TRUE if correctly retrieved.
 *    - \a FALSE if an error occurred.
 */
static int __APCLESS_PayPass_RetrieveErrorIndicationByte(T_SHARED_DATA_STRUCT* resultDataStruct, const unsigned int nByteNumber, unsigned char* pErrorIndicationByte)
{
   int result = FALSE;
   int position, cr;
   unsigned long readLength;
   unsigned char* readValue;

   unsigned long ulEiReadLength;
   const unsigned char* pEiReadValue;
   T_SHARED_DATA_STRUCT tDiscretionaryData;

   // Init output data
   if (pErrorIndicationByte != NULL)
      *pErrorIndicationByte = 0xFF;

   if (nByteNumber > PAYPASS_EI_MSG_ON_ERROR_BYTE)
   {
      goto End;
   }

   // Get the Outcome Parameter Set
   position = SHARED_EXCHANGE_POSITION_NULL;
   cr = GTL_SharedExchange_FindNext(resultDataStruct, &position, TAG_PAYPASS_DISCRETIONARY_DATA, &readLength, (const unsigned char **)&readValue);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Init the shared buffer with the discretionary data buffer
   cr = GTL_SharedExchange_InitEx (&tDiscretionaryData, readLength, readLength, readValue);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Get the Error array
   position = SHARED_EXCHANGE_POSITION_NULL;
   cr = GTL_SharedExchange_FindNext (&tDiscretionaryData, &position, TAG_PAYPASS_ERROR_INDICATION, &ulEiReadLength, &pEiReadValue);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Get the byte number from the EI
   if (pErrorIndicationByte != NULL)
      *pErrorIndicationByte = pEiReadValue[nByteNumber];

   result = TRUE;

End:
   return result;
}


/**
 * Get the PayPass message to be displayed from the UIRD.
 * @param[in] resultDataStruct Structure containing the PayPass 3 kernel output.
 * @param[out] pUirdMessage Retrieved transaction outcome :
 *    - \a PAYPASS_UIRD_MESSAGE_ID_CARD_READ_OK Indicates the card has been read.
 *    - \a PAYPASS_UIRD_MESSAGE_ID_TRY_AGAIN Indicates the card has to be presented again.
 *    - \a PAYPASS_UIRD_MESSAGE_ID_APPROVED Indicates the transaction is approved.
 *    - \a PAYPASS_UIRD_MESSAGE_ID_APPROVED_SIGN Indicates the transaction is approved but signature required.
 *    - \a PAYPASS_UIRD_MESSAGE_ID_DECLINED Indicates the transaction is declined.
 *    - \a PAYPASS_UIRD_MESSAGE_ID_ERROR_OTHER_CARD Indicates the an error occurred and the cardholder shall use another card.
 *    - \a PAYPASS_UIRD_MESSAGE_ID_SEE_PHONE Indicates the cardholder shall see his phone for instructions.
 *    - \a PAYPASS_UIRD_MESSAGE_ID_CLEAR_DISPLAY Indicates the display shall be cleared.
 *    - \a PAYPASS_UIRD_MESSAGE_ID_NA Message identifier is not applicable.
 * @return
 *    - \a TRUE if correctly retrieved.
 *    - \a FALSE if an error occurred.
 */
static int __APCLESS_PayPass_RetrieveUirdMessage(T_SHARED_DATA_STRUCT* resultDataStruct, int* pUirdMessage)
{
   int result = TRUE;
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;

   // Init position
   position = SHARED_EXCHANGE_POSITION_NULL;

   // Init output data
   if (pUirdMessage != NULL)
      *pUirdMessage = PAYPASS_UIRD_MESSAGE_ID_NA;

   // Get the Outcome Parameter Set
   cr = GTL_SharedExchange_FindNext(resultDataStruct, &position, TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA, &readLength, &readValue);

   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      result = FALSE;
      goto End;
   }

   // Get the UIRD message
   if (pUirdMessage != NULL)
      *pUirdMessage = readValue[PAYPASS_UIRD_MESSAGE_ID_BYTE];

End:
   return result;
}


/**
 * Get the CVM to apply (read from the Outcome Parameter Set).
 * @param[in] resultDataStruct Structure containing the PayPass 3 kernel output.
 * @param[out] pCvm Retrieved transaction outcome :
 *    - \a PAYPASS_OPS_CVM_NO_CVM No CVM to be performed.
 *    - \a PAYPASS_OPS_CVM_SIGNATURE if signature shall be performed.
 *    - \a PAYPASS_OPS_CVM_ONLINE_PIN if online PIN shall be performed.
 *    - \a PAYPASS_OPS_CVM_CONFIRMATION_CODE_VERIFIED if if confirmation code has been verified.
 *    - \a PAYPASS_OPS_CVM_NA if CVM is not applicable to the case.
 * @return
 *    - \a TRUE if correctly retrieved.
 *    - \a FALSE if an error occurred.
 */
static int __APCLESS_PayPass_RetrieveCvmToApply(T_SHARED_DATA_STRUCT* resultDataStruct, unsigned char* pCvm)
{
   int result = TRUE;
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;

   // Init position
   position = SHARED_EXCHANGE_POSITION_NULL;

   // Init output data
   if (pCvm != NULL)
      *pCvm = PAYPASS_OPS_CVM_NA;

   // Get the Outcome Parameter Set
   cr = GTL_SharedExchange_FindNext(resultDataStruct, &position, TAG_PAYPASS_OUTCOME_PARAMETER_SET, &readLength, &readValue);

   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      result = FALSE;
      goto End;
   }

   // Get the CVM to apply
   if (pCvm != NULL)
      *pCvm = readValue[PAYPASS_OPS_CVM_BYTE];

End:
   return result;
}


/**
 * Get the Field Off value (read from the Outcome Parameter Set).
 * @param[in] resultDataStruct Structure containing the PayPass 3 kernel output.
 * @param[out] pFieldOff Retrieved field off value (in units of 100 ms).
 *    - \a PAYPASS_OPS_FIELD_OFF_REQUEST_NA if Field Off is not applicable to the case.
 * @return
 *    - \a TRUE if correctly retrieved.
 *    - \a FALSE if an error occurred.
 */
static int __APCLESS_PayPass_RetrieveFieldOffValue(T_SHARED_DATA_STRUCT* resultDataStruct, unsigned char* pFieldOff)
{
   int result = TRUE;
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;

   // Init position
   position = SHARED_EXCHANGE_POSITION_NULL;

   // Init output data
   if (pFieldOff != NULL)
      *pFieldOff = PAYPASS_OPS_FIELD_OFF_REQUEST_NA;

   // Get the Outcome Parameter Set
   cr = GTL_SharedExchange_FindNext(resultDataStruct, &position, TAG_PAYPASS_OUTCOME_PARAMETER_SET, &readLength, &readValue);

   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      result = FALSE;
      goto End;
   }

   // Get the Field Off value
   if (pFieldOff != NULL)
      *pFieldOff = readValue[PAYPASS_OPS_FIELD_OFF_REQUEST_BYTE];

End:
   return result;
}


/**
 * Get the card type.
 * @param[in] resultDataStruct Structure containing the PayPass 3 kernel output.
 * @param[out] cardType Retrieved card type
 *    - \a 0 If card type not found.
 *    - \a 0x8501 for MStripe card.
 *    - \a 0x8502 for MChip card.
 * @return
 *    - \a TRUE if correctly retrieved.
 *    - \a FALSE if an error occurred.
 */
static int __APCLESS_PayPass_RetrieveCardType(T_SHARED_DATA_STRUCT* resultDataStruct, unsigned short* cardType)
{
   int result = TRUE;
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;

   position = SHARED_EXCHANGE_POSITION_NULL;

   if (cardType != NULL)
      *cardType = 0; // Default result

   cr = GTL_SharedExchange_FindNext(resultDataStruct, &position, TAG_KERNEL_CARD_TYPE, &readLength, &readValue);

   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      result = FALSE;
      goto End;
   }

   // Get the transaction outcome
   if (cardType != NULL)
      *cardType = (readValue[0] << 8) + readValue[1];

End:
   return result;
}


/**
 * Check if a receipt is required or not (read from the Outcome Parameter Set).
 * @param[in] resultDataStruct Structure containing the PayPass 3 kernel output.
 * @param[out] isReceiptRequired \a TRUE if the receipt is required, \a FALSE else.
 * @return
 *    - \a TRUE if correctly retrieved.
 *    - \a FALSE if an error occurred.
 */
static int __APCLESS_PayPass_IsReceiptRequired(T_SHARED_DATA_STRUCT* resultDataStruct, int* isReceiptRequired)
{
   int result = TRUE;
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;

   // Init position
   position = SHARED_EXCHANGE_POSITION_NULL;

   // Init output data
   if (isReceiptRequired != NULL)
      *isReceiptRequired = FALSE;

   // Get the Outcome Parameter Set
   cr = GTL_SharedExchange_FindNext(resultDataStruct, &position, TAG_PAYPASS_OUTCOME_PARAMETER_SET, &readLength, &readValue);

   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      result = FALSE;
      goto End;
   }

   // Get the transaction outcome
   if (isReceiptRequired != NULL)
      *isReceiptRequired = ((readValue[PAYPASS_OPS_DATA_PRESENCE_BYTE] & PAYPASS_OPS_DATA_PRESENCE_MASK_RECEIPT) == PAYPASS_OPS_DATA_PRESENCE_MASK_RECEIPT);

End:
   return result;
}


/**
 * Display the Approved message with the Balance amount (if available from UIRD).
 * @param[in] resultDataStruct Structure containing the PayPass 3 kernel output.
 * @return
 *    - \a TRUE if no problem occurred.
 *    - \a FALSE if not displayed (balance not available, an error occurred).
 */
static int __APCLESS_PayPass_DisplayApprovedWithBalance(T_SHARED_DATA_STRUCT* resultDataStruct)
{
   int result = FALSE;
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;
   unsigned char* pCurrencyCode = NULL;

   // Get the Outcome Parameter Set
   position = SHARED_EXCHANGE_POSITION_NULL;
   cr = GTL_SharedExchange_FindNext(resultDataStruct, &position, TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA, &readLength, &readValue);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Get the Balance value and format the message to display
   if(readValue[PAYPASS_UIRD_VALUE_QUALIFIER_BYTE] == PAYPASS_UIRD_VALUE_QUALIFIER_BALANCE)
   {
      pCurrencyCode = (unsigned char *) (&readValue[PAYPASS_UIRD_CURRENCY_CODE_OFFSET]);

      // TODO: Get the currency label and exponent from the parameters. If not found, indicate an invalid parameter as the currency code provided is unknown from the application.

      // TODO: Retrieve the format of the money (currency position, separator, ...)

      // Display the message with the balance amount
      APCLESS_Gui_DisplayScreenWithBalance(APCLESS_PAYPASS_SCREEN_APPROVED, "EUR", 2, &(readValue[PAYPASS_UIRD_VALUE_OFFSET]), PAYPASS_UIRD_VALUE_LENGTH);

      result = TRUE;
   }

End:
   return result;
}


/**
 * Add the transaction data record to the batch.
 * @param[in,out] sharedData Shared buffer to be used to retrieve the data record.
 */
static void __APCLESS_PayPass_AddRecordToBatch(T_SHARED_DATA_STRUCT * sharedData)
{
   int result;

   // TODO: Get transaction data and add them to the batch

   // Note : here we are using PayPass3_GetData() but it is also possible to use PayPass3_GetAllData()

   // Clear the shared exchange buffer
   GTL_SharedExchange_ClearEx (sharedData, FALSE);

   // Add the needed tags : Data Record and Discretionary Data
   result = GTL_SharedExchange_AddTag(sharedData, TAG_PAYPASS_DATA_RECORD, 0, NULL);
   if (result != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }
   result = GTL_SharedExchange_AddTag(sharedData, TAG_PAYPASS_DISCRETIONARY_DATA, 0, NULL);
   if (result != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Get the tags from the kernel
   result = PayPass3_GetData(sharedData);
   if (result == KERNEL_STATUS_OK)
   {
      // TODO: Now we have the needed transaction data, add them in the batch
      // ...

   }

End:

   if (result != KERNEL_STATUS_OK)
   {
      // TODO: Manage error case
   }
}


/**
 * Display a specific message according to the UIRD.
 * @param[in] dataStruct Shared buffer contianing the UIRD, containing itself the message to be displayed.
 * @param[in] isPhoneMessage \a TRUE if function called when displaying phone message, \a FALSE else.
 */
static void __APCLESS_PayPass_DisplayUirdMsg(T_SHARED_DATA_STRUCT* dataStruct, const int isPhoneMessage)
{
   int uirdMessage;

   // Get the UIRD message to be displayed
   if (!__APCLESS_PayPass_RetrieveUirdMessage (dataStruct, &uirdMessage))
      uirdMessage = PAYPASS_UIRD_MESSAGE_ID_NA;

   switch (uirdMessage)
   {
      case PAYPASS_UIRD_MESSAGE_ID_CARD_READ_OK:
         APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_REMOVE_CARD);
         break;
      case PAYPASS_UIRD_MESSAGE_ID_TRY_AGAIN:
         APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_RETRY);
         break;
      case PAYPASS_UIRD_MESSAGE_ID_APPROVED:
         APCLESS_Gui_DisplayScreen(APCLESS_PAYPASS_SCREEN_APPROVED);
         break;
      case PAYPASS_UIRD_MESSAGE_ID_APPROVED_SIGN:
         APCLESS_Gui_DisplayScreen(APCLESS_PAYPASS_SCREEN_SIGNATURE_OK);
         break;
      case PAYPASS_UIRD_MESSAGE_ID_DECLINED:
         APCLESS_Gui_DisplayScreen(APCLESS_PAYPASS_SCREEN_DECLINED);
         break;
      case PAYPASS_UIRD_MESSAGE_ID_ERROR_OTHER_CARD:
         APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_ERROR);
         break;
      case PAYPASS_UIRD_MESSAGE_ID_SEE_PHONE:
         // Request cardholder to follow his phone for instructions
         APCLESS_Gui_DisplayScreen(APCLESS_PAYPASS_SCREEN_PHONE_INSTRUCTIONS);

         if (isPhoneMessage)
         {
            // Indicate double tap is in progress
            APCLESS_ParamTrn_SetDoubleTapInProgress(TRUE);
         }
         break;
      case PAYPASS_UIRD_MESSAGE_ID_AUTHORISING_PLEASE_WAIT:
         APCLESS_Gui_DisplayScreen(APCLESS_PAYPASS_SCREEN_AUTHORISING);
         break;
      case PAYPASS_UIRD_MESSAGE_ID_INSERT_CARD:
         APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_USE_CONTACT);
         break;
      case PAYPASS_UIRD_MESSAGE_ID_CLEAR_DISPLAY:
         APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_EMPTY);
         break;
      default:
         break;
   }
}


/**
 * Get the PayPass CA Key F3 parameters.
 * @param[out] outputDataStruct Shared buffer filled with the CA Public Key data.
 */
static void __APCLESS_PayPass_CopyCAKeyF3(T_SHARED_DATA_STRUCT* outputDataStruct)
{
   int cr;

   // Copy Modulus
   cr = GTL_SharedExchange_AddTag(outputDataStruct, TAG_EMV_INT_CAPK_MODULUS, sizeof(__APCLESS_PayPass_caKeyF3Modulus), __APCLESS_PayPass_caKeyF3Modulus);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      GTL_SharedExchange_ClearEx(outputDataStruct, FALSE);
      return;
   }

   // Copy Exponent
   cr = GTL_SharedExchange_AddTag(outputDataStruct, TAG_EMV_INT_CAPK_EXPONENT, sizeof(__APCLESS_PayPass_caKeyF3Exponent), __APCLESS_PayPass_caKeyF3Exponent);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      GTL_SharedExchange_ClearEx(outputDataStruct, FALSE);
      return;
   }
}


/**
 * Calls the PayPass kernel to perform the transaction.
 * @param[in] dataStruct Data buffer to be filled and used for PayPass transaction.
 * @return status of the PayPass kernel execution (\a CLESS_CR_MANAGER_xxx status).
 */
int APCLESS_PayPass_PerformTransaction(T_SHARED_DATA_STRUCT* dataStruct)
{
   int result = CLESS_CR_MANAGER_END;
   int cr, transactionOutcome, transactionStart;
   int receiptRequired;
   unsigned char cvm, fieldOff;
   unsigned char saveInBatch = FALSE;
   unsigned short cardType = 0;
   int mobileTransaction;
   int uirdMessage;
   unsigned char errorIndicationByte;
   int performDeselect = TRUE;


   // Indicate PayPass kernel is going to be used (for customisation purposes)
   APCLESS_ParamTrn_SetCurrentPaymentScheme(APCLESS_SCHEME_PAYPASS);

   // Init PayPass kernel debug traces
   __APCLESS_PayPass_DebugActivation(APCLESS_ParamTrn_GetDebugTrace());

   // Get the PayPass
   if(__APCLESS_PayPass_AddPayPassSpecificData(dataStruct))
   {
      // Call the PayPass kernel to perform the transaction
      cr = PayPass3_DoTransaction(dataStruct);

      // Get the transaction outcome
      // - PAYPASS_OPS_STATUS_APPROVED if transaction is approved.
      // - PAYPASS_OPS_STATUS_ONLINE_REQUEST if an online authorisation is requested.
      // - PAYPASS_OPS_STATUS_DECLINED if the transaction is declined.
      // - PAYPASS_OPS_STATUS_SELECT_NEXT if next AID shall be selected.
      // - PAYPASS_OPS_STATUS_TRY_AGAIN transaction shall be restarted from the beginning..
      // - PAYPASS_OPS_STATUS_END_APPLICATION if the transaction is terminated.
      if (!__APCLESS_PayPass_RetrieveTransactionOutcome(dataStruct, &transactionOutcome))
         transactionOutcome = PAYPASS_OPS_STATUS_END_APPLICATION;


      // Get the TAG_PAYPASS_OUTCOME_PARAMETER_SET to identify the CVM to be performed
      // - PAYPASS_OPS_CVM_NO_CVM : "No CVM" method has been applied.
      // - PAYPASS_OPS_CVM_SIGNATURE : "Signature" method has been applied.
      // - PAYPASS_OPS_CVM_ONLINE_PIN : "Online PIN" method has been applied.
      // - PAYPASS_OPS_CVM_CONFIRMATION_CODE_VERIFIED : confirmation code has been verified.
      // - PAYPASS_OPS_CVM_NA : if CVM is not applicable.
      if (!__APCLESS_PayPass_RetrieveCvmToApply (dataStruct, &cvm))
         cvm = PAYPASS_OPS_CVM_NA;

      if (!__APCLESS_PayPass_RetrieveFieldOffValue(dataStruct, &fieldOff))
         fieldOff = PAYPASS_OPS_FIELD_OFF_REQUEST_NA;

      // Retrieve the card type
      if (!__APCLESS_PayPass_RetrieveCardType(dataStruct, &cardType))
         cardType = 0;

      // Check if the receipt has to be printed or not
      if (!__APCLESS_PayPass_IsReceiptRequired(dataStruct, &receiptRequired))
         receiptRequired = FALSE;

      // Get the UIRD message to be displayed
      if (!__APCLESS_PayPass_RetrieveUirdMessage(dataStruct, &uirdMessage))
         uirdMessage = PAYPASS_UIRD_MESSAGE_ID_NA;

      // Retrieve the start value in the OPS
      if (!__APCLESS_PayPass_RetrieveStart(dataStruct, &transactionStart))
         transactionStart = PAYPASS_OPS_START_NA;


      // Additional possible processing :
      // - Perform an online authorisation if necessary
      // - Save the transaction in the batch if transaction is accepted
      // - Perform CVM processing if necessary

      // Check if a mobile transaction has been performed
      mobileTransaction = ((cardType & PAYPASS_B2_MASK_ON_DEVICE_CVM_SUPPORTED) == PAYPASS_B2_MASK_ON_DEVICE_CVM_SUPPORTED);

      switch (transactionOutcome)
      {
         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case PAYPASS_OPS_STATUS_APPROVED:

            if (cvm == PAYPASS_OPS_CVM_SIGNATURE)
            {
               APCLESS_Gui_DisplayScreen(APCLESS_PAYPASS_SCREEN_SIGNATURE_REQUIRED);
            }
            else
            {
               // Display Approved message and, if available, the balance amount
               if(FALSE == __APCLESS_PayPass_DisplayApprovedWithBalance(dataStruct))
                  APCLESS_Gui_DisplayScreen(APCLESS_PAYPASS_SCREEN_APPROVED);


               // Indicate the transaction shall be stored in the batch
               saveInBatch = TRUE;
            }

            // Get all data
            PayPass3_GetAllData(dataStruct); // Get all the kernel data to print the receipt

            // TODO: Print the receipt...

            // If the selected CVM is signature
            if (cvm == PAYPASS_OPS_CVM_SIGNATURE)
            {
                  // TODO: Ask merchant if signature is OK
                  // if yes  bSaveInBatch = TRUE;
            }
            break;

         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case PAYPASS_OPS_STATUS_DECLINED:
            // Display the message located in the UIRD (DECLINED, INSERT CARD or CLEAR DISPLAY)
            __APCLESS_PayPass_DisplayUirdMsg (dataStruct, FALSE);
            break;

         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case PAYPASS_OPS_STATUS_TRY_ANOTHER_INTERFACE:
            // Display the message located in the UIRD
            __APCLESS_PayPass_DisplayUirdMsg (dataStruct, FALSE);
            break;

         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case PAYPASS_OPS_STATUS_ONLINE_REQUEST:
            // TODO: Check if PIN online is required and manage it.
            // TODO: Make online authorisation
            APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_ONLINE_PROCESSING);
            // if ok bSaveInBatch
            break;


         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case PAYPASS_OPS_STATUS_TRY_AGAIN:
            // Transaction shall be silently restarted from the beginning
            result = CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY;

            // Do not perform deselect when a silent restart needs to be performed
            performDeselect = FALSE;
            break;


         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case PAYPASS_OPS_STATUS_SELECT_NEXT:
            // The next AID shall be selected in the candidate list
            result = CLESS_CR_MANAGER_REMOVE_AID;
            break;


         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         default: // Error case
            // Check if the transaction must be restarted
            if ((transactionOutcome == PAYPASS_OPS_STATUS_END_APPLICATION) && (transactionStart == PAYPASS_OPS_START_B))
            {
               // Do not perform deselect in the generic case, as all is managed here
               performDeselect = FALSE;

               __APCLESS_PayPass_RetrieveErrorIndicationByte(dataStruct, PAYPASS_EI_L1_BYTE, &errorIndicationByte);

               // Check if the restart is due to a communication error with the card
               if((uirdMessage == PAYPASS_UIRD_MESSAGE_ID_TRY_AGAIN) && (errorIndicationByte != PAYPASS_EI_L1_OK))
               {
                  // Display a message and wait card removal
                  if(fieldOff == PAYPASS_OPS_FIELD_OFF_REQUEST_NA)
                  {
                     APCLESS_Gui_DisplayScreen(APCLESS_PAYPASS_SCREEN_WAIT_CARD_REMOVAL);
                     ClessEmv_DeselectCard(0, TRUE, TRUE);
                  }

                  if (APCLESS_ParamTrn_GetDoubleTapInProgress())
                     APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_PHONE_INSTRUCTIONS_RETRY);
                  else
                  {
                     if (APCLESS_Selection_GetMethod() == APCLESS_SELECTION_EXPLICIT)
                        APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_RETRY);
                  }

                  // Transaction shall be restarted from the beginning
                  result = CLESS_CR_MANAGER_RESTART;
               }
               else
               {
                  // Message has already been displayed in the customisation of steps STEP_PAYPASS_MCHIP_SEND_PHONE_MSG and STEP_PAYPASS_MSTRIPE_SEND_PHONE_MSG

                  // Wait card removal
                  if(fieldOff == PAYPASS_OPS_FIELD_OFF_REQUEST_NA)
                     ClessEmv_DeselectCard(0, TRUE, TRUE);

                  if (APCLESS_ParamTrn_GetDoubleTapInProgress())
                     result = CLESS_CR_MANAGER_RESTART_DOUBLE_TAP;
                  else
                     result = CLESS_CR_MANAGER_RESTART;
               }
            }
            else // Standard error case
            {
               __APCLESS_PayPass_RetrieveErrorIndicationByte(dataStruct, PAYPASS_EI_L3_BYTE, &errorIndicationByte);

               if (!((transactionOutcome == PAYPASS_OPS_STATUS_END_APPLICATION) && ((errorIndicationByte == PAYPASS_EI_L3_STOP) || (uirdMessage == PAYPASS_UIRD_MESSAGE_ID_CLEAR_DISPLAY))))
               {
                  // Indicate an error occurred (transaction is terminated)
                  APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_ERROR);
               }

               // Indicate double tap is not in progress
               APCLESS_ParamTrn_SetDoubleTapInProgress(FALSE);
            }
            break;
      }

      if(result != CLESS_CR_MANAGER_REMOVE_AID)
      {
         // After the transaction, turn off the field during the time requested in the OPS
         if(fieldOff != PAYPASS_OPS_FIELD_OFF_REQUEST_NA)
         {
            ClessEmv_CloseDriver();
            if(fieldOff != 0)
               ttestall(0, fieldOff * 10);
         }
         else
         {
            if (transactionStart == PAYPASS_OPS_START_NA)
            {
               if (performDeselect)
                  ClessEmv_DeselectCard(0, TRUE, FALSE);
               ClessEmv_CloseDriver();
            }
         }

         // Turn on the 1st LED only
         if ((result == CLESS_CR_MANAGER_RESTART) || (result == CLESS_CR_MANAGER_RESTART_DOUBLE_TAP))
         {
            APCLESS_Gui_IndicatorWait();
         }
      }

      // If transaction shall be save in the batch, save it
      if (saveInBatch)
      {
         __APCLESS_PayPass_AddRecordToBatch(dataStruct);
      }

      // If the transaction does not restart from the beginning, set the LEDs into the idle state
      if ((result != CLESS_CR_MANAGER_RESTART) && (result != CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY) && (result != CLESS_CR_MANAGER_REMOVE_AID) && (result != CLESS_CR_MANAGER_RESTART_DOUBLE_TAP))
      {
         // Increment the transaction sequence counter
         APCLESS_ParamTrn_IncrementTsc();

      }
   }

   // Transaction is completed, clear PayPass kernel transaction data
   PayPass3_Clear ();

   // Return result
   return result;
}


/**
 * Perform the PayPass 3 kernel customisation.
 * @param[in,out] sharedData Shared buffer used for customisation.
 * @param[in] ucCustomisationStep Step to be customised.
 * @return \a KERNEL_STATUS_CONTINUE always.
 */
int APCLESS_PayPass_KernelCustomiseStep(T_SHARED_DATA_STRUCT* sharedData, const unsigned char ucCustomisationStep)
{
   int result = KERNEL_STATUS_CONTINUE;
   unsigned char keyIndex;
   unsigned char rid[5];
   unsigned long readLength;
   int position;
   const unsigned char* readValue;

   switch (ucCustomisationStep) // Steps to customise
   {
      case STEP_PAYPASS_MSTRIPE_REMOVE_CARD:
      case STEP_PAYPASS_MCHIP_REMOVE_CARD:
         APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_REMOVE_CARD);
         GTL_SharedExchange_ClearEx (sharedData, FALSE);
         result = KERNEL_STATUS_CONTINUE;
         break;

      case STEP_PAYPASS_MCHIP_GET_CERTIFICATE:
         // Get the CA public key index (card)
         position = SHARED_EXCHANGE_POSITION_NULL;
         if (GTL_SharedExchange_FindNext(sharedData, &position, TAG_EMV_CA_PUBLIC_KEY_INDEX_CARD, &readLength, (const unsigned char **)&readValue) == STATUS_SHARED_EXCHANGE_OK)
            keyIndex = readValue[0];
         else
            keyIndex = 0;

         // Get RID value
         position = SHARED_EXCHANGE_POSITION_NULL;
         if (GTL_SharedExchange_FindNext(sharedData, &position, TAG_PAYPASS_INT_RID, &readLength, (const unsigned char **)&readValue) == STATUS_SHARED_EXCHANGE_OK)
            memcpy (rid, readValue, 5);
         else
            memset (rid, 0, sizeof(rid));

         // Clear the output structure
         GTL_SharedExchange_ClearEx (sharedData, FALSE);

         // TODO: With rid & keyIndex look for the corresponding CA public key data (Modulus, exponent, etc) in the application parameters
         // for this sample we are just using index F3
         if (keyIndex == 0xF3)
         {
            __APCLESS_PayPass_CopyCAKeyF3(sharedData);
         }

         result = KERNEL_STATUS_CONTINUE;
         break;

      case STEP_PAYPASS_MCHIP_EXCEPTION_FILE_GET_DATA:
         // TODO:  Check if PAN is in the exception file
         result = KERNEL_STATUS_CONTINUE;
         break;

      case STEP_PAYPASS_MCHIP_SEND_PHONE_MSG:
      case STEP_PAYPASS_MSTRIPE_SEND_PHONE_MSG:

         __APCLESS_PayPass_DisplayUirdMsg(sharedData, TRUE);

         GTL_SharedExchange_ClearEx(sharedData, FALSE);

         result = KERNEL_STATUS_CONTINUE;
         break;

#ifdef PAYPASS_TORN
      case STEP_PAYPASS_MCHIP_IS_TORN_RECORD:
         if(!APCLESS_PayPassTorn_IsTornTxn(sharedData))
            GTL_SharedExchange_ClearEx (sharedData, FALSE);

         result = KERNEL_STATUS_CONTINUE;
         break;

      case STEP_PAYPASS_MCHIP_ADD_TORN_RECORD:
         if(!APCLESS_PayPassTorn_AddRecord(sharedData))
            GTL_SharedExchange_ClearEx (sharedData, FALSE);

         result = KERNEL_STATUS_CONTINUE;
         break;

      case STEP_PAYPASS_MCHIP_REMOVE_TORN_RECORD:
         APCLESS_PayPassTorn_RemoveRecord();

         GTL_SharedExchange_ClearEx (sharedData, FALSE);

         result = KERNEL_STATUS_CONTINUE;
         break;
#endif

      default:
         break;
    }

    return result;
}


