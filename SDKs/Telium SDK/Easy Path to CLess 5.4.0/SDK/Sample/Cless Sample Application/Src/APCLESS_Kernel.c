/**
 * \file
 * This module is used to fill/initialise the kernel data buffer.
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


/////////////////////////////////////////////////////////////////
//// Global data definitions ////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Static data definitions ////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __APCLESS_Kernel_CopyAIDParamToSharedBuffer(int aidIdentifier, T_SHARED_DATA_STRUCT* buffer);

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


/**
 * Copy all the tags of an AID to a shared buffer.
 * @param[in] aidIdentifier identifies the AID parameters set (correspond to \a TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER)
 * @param[out] buffer shared buffer where the parameters are copied to.
 * @return
 *     - \a TRUE if correctly performed (data found and \a outSharedBuffer filled).
 *     - \a FALSE if an error occurred.
 */
static int __APCLESS_Kernel_CopyAIDParamToSharedBuffer(int aidIdentifier, T_SHARED_DATA_STRUCT* buffer)
{
   int result = FALSE;
   unsigned char termCapabilities[] = {0xE0, 0x28, 0xC8};


   // In this sample, there is no AID database. We are setting the parameters directly in the source code


   if(aidIdentifier == APCLESS_AID_PAYPASS_IDENTIFIER)
   {  // Add PayPass tags
      unsigned char aidPaypassKernelToUse[] = {0x00, 0x02};             // PayPass kernel number = 2
      unsigned char aidPaypassOptions[] = {0x45, 0x01, 0x00, 0x00};     // Partial AID, Zero Amount, PPSE method
      unsigned char aidDefaultUdol[] = {0x9F, 0x6A, 0x04};
      unsigned char aidPaypassFloorLimit[]= {0x00, 0x00, 0x00, 0x01, 0x00, 0x00};
      unsigned char aidPaypassTrnLimitNoDcv[] = {0x00, 0x00, 0x00, 0x03, 0x00, 0x00};
      unsigned char aidPaypassTrnLimitDcv[] = {0x00, 0x00, 0x00, 0x05, 0x00, 0x00};
      unsigned char aidPaypassCvmRequiredLimit[] = {0x00, 0x00, 0x00, 0x00, 0x10, 0x00};
      unsigned char aidPaypassSecurityCapability[] = {0x08};
      unsigned char aidPaypassEmvIntTacDefault[] = {0x00, 0x00, 0x00, 0x00, 0x00};
      unsigned char aidPaypassEmvIntTacDenial[] = {0x00, 0x00, 0x00, 0x00, 0x00};
      unsigned char aidPaypassEmvIntTacOnline[] = {0x00, 0x00, 0x00, 0x00, 0x00};
      unsigned char aidPaypassCardDataInputCapability[] = {0x00};
      unsigned char aidPaypassMChipCvmCapabilityCvmRequired[] = {0x60};
      unsigned char aidPaypassMChipCvmCapabilityCvmNotRequired[] = {0x08};
      unsigned char aidPaypassKernelConfiguration[] = {0x20};
      unsigned char aidPaypassCAPKIndexList[] = {0xF3};


       if(GTL_SharedExchange_AddTag(buffer, TAG_EP_KERNEL_TO_USE, sizeof(aidPaypassKernelToUse), aidPaypassKernelToUse) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_EP_AID_OPTIONS, sizeof(aidPaypassOptions), aidPaypassOptions) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYPASS_DEFAULT_UDOL, sizeof(aidDefaultUdol), aidDefaultUdol) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_EP_CLESS_FLOOR_LIMIT, sizeof(aidPaypassFloorLimit), aidPaypassFloorLimit) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_NO_DCV, sizeof(aidPaypassTrnLimitNoDcv), aidPaypassTrnLimitNoDcv) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_DCV, sizeof(aidPaypassTrnLimitDcv), aidPaypassTrnLimitDcv) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_EP_CLESS_CVM_REQUIRED_LIMIT, sizeof(aidPaypassCvmRequiredLimit), aidPaypassCvmRequiredLimit) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYPASS_SECURITY_CAPABILITY, sizeof(aidPaypassSecurityCapability), aidPaypassSecurityCapability) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_EMV_TERMINAL_CAPABILITIES, sizeof(termCapabilities), termCapabilities) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_EMV_INT_TAC_DEFAULT, sizeof(aidPaypassEmvIntTacDefault), aidPaypassEmvIntTacDefault) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_EMV_INT_TAC_DENIAL, sizeof(aidPaypassEmvIntTacDenial), aidPaypassEmvIntTacDenial) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_EMV_INT_TAC_ONLINE, sizeof(aidPaypassEmvIntTacOnline), aidPaypassEmvIntTacOnline) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYPASS_CARD_DATA_INPUT_CAPABILITY, sizeof(aidPaypassCardDataInputCapability), aidPaypassCardDataInputCapability) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_REQUIRED, sizeof(aidPaypassMChipCvmCapabilityCvmRequired), aidPaypassMChipCvmCapabilityCvmRequired) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_NOT_REQUIRED, sizeof(aidPaypassMChipCvmCapabilityCvmNotRequired), aidPaypassMChipCvmCapabilityCvmNotRequired) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYPASS_KERNEL_CONFIGURATION, sizeof(aidPaypassKernelConfiguration), aidPaypassKernelConfiguration) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYPASS_INT_SUPPORTED_CAPK_INDEX_LIST, sizeof(aidPaypassCAPKIndexList), aidPaypassCAPKIndexList) != STATUS_SHARED_EXCHANGE_OK) goto End;
      // Add following empty tags to activate the card balance
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYPASS_BALANCE_READ_BEFORE_GENAC, 0, NULL) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYPASS_BALANCE_READ_AFTER_GENAC, 0, NULL) != STATUS_SHARED_EXCHANGE_OK) goto End;

      result = TRUE;

   }
   else if(aidIdentifier == APCLESS_AID_PAYWAVE_IDENTIFIER)
   {  // Add payWave tags
      unsigned char aidpayWaveKernelToUse[] = {0x00, 0x03};             // Visa payWave kernel number = 1
      unsigned char aidpayWaveOptions[] = {0x01, 0x01, 0x00, 0x00};     // Partial AID, PPSE method
      unsigned char aidpayWaveTTQ[] =     {0xB6, 0x00, 0xC0, 0x00};     // Cless MSD + qVSDC & onlinePIN + sign supported + CVN17 + ISP
      unsigned char aidpayWaveFddaVer[] = {0x00, 0x01};


      if(GTL_SharedExchange_AddTag(buffer, TAG_EP_KERNEL_TO_USE, sizeof(aidpayWaveKernelToUse), aidpayWaveKernelToUse) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_EP_AID_OPTIONS, sizeof(aidpayWaveOptions), aidpayWaveOptions) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS, sizeof(aidpayWaveTTQ), aidpayWaveTTQ) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_PAYWAVE_TERM_SUPPORTED_FDDA_VERSIONS, sizeof(aidpayWaveFddaVer), aidpayWaveFddaVer) != STATUS_SHARED_EXCHANGE_OK) goto End;
      if(GTL_SharedExchange_AddTag(buffer, TAG_EMV_TERMINAL_CAPABILITIES, sizeof(termCapabilities), termCapabilities) != STATUS_SHARED_EXCHANGE_OK) goto End;

      result = TRUE;
   }

End:
   return result;
}


/**
 * Add the generic transaction data in the kernel shared buffer (date, time, amount, etc).
 * @param[out] kernelSharedData Shared exchange structure filled with the generic transaction data.
 * @return
 *      - \a TRUE if correctly performed.
 *      - \a FALSE if an error occurred.
 */
int APCLESS_Kernel_AddTransactionGenericData(T_SHARED_DATA_STRUCT* kernelSharedData)
{
   int result, cr;
   unsigned char transactionType;
   NO_SERIE serial;

   result = FALSE;

   if(kernelSharedData == NULL)
   {
      goto End;
   }

   // Add the transaction date
   cr = GTL_SharedExchange_AddTag(kernelSharedData, TAG_EMV_TRANSACTION_DATE, 3, APCLESS_ParamTrn_GetDate());
   if(cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Add the transaction time
   cr = GTL_SharedExchange_AddTag(kernelSharedData, TAG_EMV_TRANSACTION_TIME, 3, APCLESS_ParamTrn_GetTime());
   if(cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Add the amount and the currency code (if present)
   if(APCLESS_ParamTrn_GetAmountBcd() != NULL)
   {
      // Add the transaction amount numeric (bcd)
      cr = GTL_SharedExchange_AddTag(kernelSharedData, TAG_EMV_AMOUNT_AUTH_NUM, 6, APCLESS_ParamTrn_GetAmountBcd());
      if (cr != STATUS_SHARED_EXCHANGE_OK)
      {
         goto End;
      }

      // Add the transaction amount binary
      cr = GTL_SharedExchange_AddTag(kernelSharedData, TAG_EMV_AMOUNT_AUTH_BIN, 4, APCLESS_ParamTrn_GetAmountBin());
      if (cr != STATUS_SHARED_EXCHANGE_OK)
      {
         goto End;
      }

      // Add the transaction amount other ... todo if necessary


      // Add the currency code
      cr = GTL_SharedExchange_AddTag(kernelSharedData, TAG_EMV_TRANSACTION_CURRENCY_CODE, 2, APCLESS_ParamTrn_GetCurrencyCode());
      if (cr != STATUS_SHARED_EXCHANGE_OK)
      {
         goto End;
      }

      // Add the currency exponent
      cr = GTL_SharedExchange_AddTag(kernelSharedData, TAG_EMV_TRANSACTION_CURRENCY_EXPONENT, 1, APCLESS_ParamTrn_GetCurrencyExponent());
      if (cr != STATUS_SHARED_EXCHANGE_OK)
      {
         goto End;
      }
   }

   // Add the internal transaction type
   transactionType = APCLESS_ParamTrn_GetTransactionType();
   cr = GTL_SharedExchange_AddTag(kernelSharedData, TAG_EMV_INT_TRANSACTION_TYPE, 1, &transactionType);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Add the standard transaction type
   cr = GTL_SharedExchange_AddTag(kernelSharedData, TAG_EMV_TRANSACTION_TYPE, 1, &transactionType);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Extract Serial Number and add it to the data
   PSQ_Give_Serial_Number(serial);
   cr = GTL_SharedExchange_AddTag(kernelSharedData, TAG_EMV_IFD_SERIAL_NUMBER, 8, (unsigned char *)serial);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Add the transaction sequence counter
   if (APCLESS_ParamTrn_AddTscToSharedBuffer(kernelSharedData) == FALSE)
   {
      goto End;
   }

   result = TRUE;

End:
   return result;
}


/**
 * Find the correct AID parameters (to perform the transaction) according to the application selection result and add
 * the parameters to the kernel shared buffer.
 * @param[in] selectionSharedData Shared buffer containing the application selection results.
 * @param[out] kernelSharedData Shared buffer to be filled with the correct AID parameters (depending on the Application Selection results).
 * @param[out] kernelToUse Indicates the kernel to be used for the transaction.
 * @return
 *      - \a TRUE if correctly performed.
 *      - \a FALSE if an error occurred.
 */
int APCLESS_Kernel_AddAidRelatedData(T_SHARED_DATA_STRUCT* selectionSharedData, T_SHARED_DATA_STRUCT* kernelSharedData, int* kernelToUse)
{
   int result = FALSE;
   int cr, cr2;
   int position;
   int aidIndex = 0xff;
   unsigned long readTag;
   unsigned long readLength;
   const unsigned char* readValue;
   T_SHARED_DATA_STRUCT candidateElementTags;
   unsigned char* cardAid;
   unsigned int  cardAidLength;

   if ((*kernelToUse) != NULL)
      *kernelToUse = DEFAULT_EP_KERNEL_UNKNOWN;

   if ((selectionSharedData == NULL) || (kernelSharedData == NULL))
   {
      goto End;
   }

   // TODO: Find the good Candidate Element in the Candidate List sent by EntryPoint
   // (it is possible to have several candidate element at the same time)
   // For this sample, we just use the first candidate element (no further check).
   position = SHARED_EXCHANGE_POSITION_NULL;
   if (GTL_SharedExchange_FindNext(selectionSharedData, &position, TAG_EP_CANDIDATE_LIST_ELEMENT, &readLength, &readValue)!= STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // init the candidateElementTags shared buffer with TAG_EP_CANDIDATE_LIST_ELEMENT found
   if (GTL_SharedExchange_InitEx(&candidateElementTags, readLength, readLength, (unsigned char *)readValue) != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Get the Kernel to Use
   position = SHARED_EXCHANGE_POSITION_NULL;
   if(GTL_SharedExchange_FindNext (&candidateElementTags, &position, TAG_EP_KERNEL_TO_USE, &readLength, &readValue)!= STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }
   *kernelToUse = readValue[1] + (readValue[0] << 8);

   // Get the AID proprietary identifier
   position = SHARED_EXCHANGE_POSITION_NULL;
   if(GTL_SharedExchange_FindNext (&candidateElementTags, &position, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, &readLength, &readValue)!= STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }
   aidIndex = readValue[3] + (readValue[2] << 8) + (readValue[1] << 16) + (readValue[0] << 24);


   // Get the AID from TAG_EMV_AID_CARD or from TAG_EMV_DF_NAME
   position = SHARED_EXCHANGE_POSITION_NULL;
   if(GTL_SharedExchange_FindNext (&candidateElementTags, &position, TAG_EMV_AID_CARD, &readLength, &readValue)!= STATUS_SHARED_EXCHANGE_OK)
   {
      position = SHARED_EXCHANGE_POSITION_NULL;
      if(GTL_SharedExchange_FindNext (&candidateElementTags, &position, TAG_EMV_DF_NAME, &readLength, &readValue)!= STATUS_SHARED_EXCHANGE_OK)
      {
         goto End;
      }
   }
   cardAid = (unsigned char*)readValue;
   cardAidLength = readLength;


   // Add the AID's parameters to the kernel shared buffer
   if(__APCLESS_Kernel_CopyAIDParamToSharedBuffer(aidIndex, kernelSharedData) == FALSE)
   {  // an error occurs
      goto End;
   }

   // Add some of the candidate element tags to the kernel shared buffer
   position = SHARED_EXCHANGE_POSITION_NULL;
   cr2 = STATUS_SHARED_EXCHANGE_OK;
   while (cr2 == STATUS_SHARED_EXCHANGE_OK)
   {
      cr2 = GTL_SharedExchange_GetNext(&candidateElementTags, &position, &readTag, &readLength, &readValue);

      if (cr2 == STATUS_SHARED_EXCHANGE_OK)
      {
         switch (readTag)
         {
            case TAG_EP_AID_ADDITIONAL_RESULTS:
            case TAG_EMV_AID_TERMINAL:
            case TAG_EP_CLESS_APPLI_CAPABILITY_TYPE:
            case TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER:
               cr2 = GTL_SharedExchange_AddTag(kernelSharedData, readTag, readLength, readValue);
               if (cr2 != STATUS_SHARED_EXCHANGE_OK)
               {
                  goto End;
               }
               break;

            default:
               break;
         }
      }
   }

   // Add Final Select SW
   position = SHARED_EXCHANGE_POSITION_NULL;
   cr = GTL_SharedExchange_FindNext (selectionSharedData, &position, TAG_EP_FINAL_SELECT_STATUS_WORD, &readLength, &readValue);
   if (cr == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
   {
      cr2 = GTL_SharedExchange_AddTag (kernelSharedData, TAG_EP_FINAL_SELECT_STATUS_WORD, readLength, readValue);
      if (cr2 != STATUS_SHARED_EXCHANGE_OK)
      {
         goto End;
      }
   }
   else
   {
      goto End;
   }

   // Add Final Select Response
   position = SHARED_EXCHANGE_POSITION_NULL;
   cr = GTL_SharedExchange_FindNext (selectionSharedData, &position, TAG_EP_FINAL_SELECT_RESPONSE, &readLength, &readValue);
   if (cr == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
   {
      cr2 = GTL_SharedExchange_AddTag (kernelSharedData, TAG_EP_FINAL_SELECT_RESPONSE, readLength, readValue);
      if (cr2 != STATUS_SHARED_EXCHANGE_OK)
      {
         goto End;
      }
   }
   else
   {
      // No error management, as a card could answer only a SW without data (in case of processing error)
   }

   // Add Final Select Command
   position = SHARED_EXCHANGE_POSITION_NULL;
   cr = GTL_SharedExchange_FindNext (selectionSharedData, &position, TAG_EP_FINAL_SELECT_COMMAND_SENT, &readLength, &readValue);
   if (cr == STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
   {
      cr2 = GTL_SharedExchange_AddTag (kernelSharedData, TAG_EP_FINAL_SELECT_COMMAND_SENT, readLength, readValue);
      if (cr2 != STATUS_SHARED_EXCHANGE_OK)
      {
         goto End;
      }

      result = TRUE;
   }

End:

   if(result == FALSE)  //case an error occurs
   {
      GTL_SharedExchange_ClearEx (kernelSharedData, FALSE);
   }

   return result;
}

