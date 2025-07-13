/**
 * \file
 * This module manages a Visa payWave transaction.
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

#define __APCLESS_PAYWAVE_CARD_REPRESENT_TO           20    ///< Time out in seconds for representing the card

/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

static unsigned char __APCLESS_payWave_caKey51Modulus[] =
     {0xDB, 0x5F, 0xA2, 0x9D, 0x1F, 0xDA, 0x8C, 0x16, 0x34, 0xB0, 0x4D, 0xCC, 0xFF, 0x14, 0x8A, 0xBE,
      0xE6, 0x3C, 0x77, 0x20, 0x35, 0xC7, 0x98, 0x51, 0xD3, 0x51, 0x21, 0x07, 0x58, 0x6E, 0x02, 0xA9,
      0x17, 0xF7, 0xC7, 0xE8, 0x85, 0xE7, 0xC4, 0xA7, 0xD5, 0x29, 0x71, 0x0A, 0x14, 0x53, 0x34, 0xCE,
      0x67, 0xDC, 0x41, 0x2C, 0xB1, 0x59, 0x7B, 0x77, 0xAA, 0x25, 0x43, 0xB9, 0x8D, 0x19, 0xCF, 0x2C,
      0xB8, 0x0C, 0x52, 0x2B, 0xDB, 0xEA, 0x0F, 0x1B, 0x11, 0x3F, 0xA2, 0xC8, 0x62, 0x16, 0xC8, 0xC6,
      0x10, 0xA2, 0xD5, 0x8F, 0x29, 0xCF, 0x33, 0x55, 0xCE, 0xB1, 0xBD, 0x3E, 0xF4, 0x10, 0xD1, 0xED,
      0xD1, 0xF7, 0xAE, 0x0F, 0x16, 0x89, 0x79, 0x79, 0xDE, 0x28, 0xC6, 0xEF, 0x29, 0x3E, 0x0A, 0x19,
      0x28, 0x2B, 0xD1, 0xD7, 0x93, 0xF1, 0x33, 0x15, 0x23, 0xFC, 0x71, 0xA2, 0x28, 0x80, 0x04, 0x68,
      0xC0, 0x1A, 0x36, 0x53, 0xD1, 0x4C, 0x6B, 0x48, 0x51, 0xA5, 0xC0, 0x29, 0x47, 0x8E, 0x75, 0x7F};

static unsigned char __APCLESS_payWave_caKey51Exponent[] = {0x03};

/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __APCLESS_payWave_AddpayWaveSpecificData(T_SHARED_DATA_STRUCT* dataStruct);
static int __APCLESS_payWave_IsPinOnLineRequested(T_SHARED_DATA_STRUCT* resultDataStruct);
static int __APCLESS_payWave_IsSignatureRequested (T_SHARED_DATA_STRUCT* resultDataStruct);
static void __APCLESS_payWave_DebugActivation(int activate);
static int __APCLESS_payWave_DisplaySreenWithBalance(unsigned long screenId, T_SHARED_DATA_STRUCT* dataStruct);
static int __APCLESS_payWave_CheckISPConditions(T_SHARED_DATA_STRUCT* sharedStructure);
static int __APCLESS_payWave_WaitClessCard(T_SHARED_DATA_STRUCT* dataStruct);
static void __APCLESS_payWave_StopClessCard(void);
static int __APCLESS_payWave_ManageAfterTrn(T_SHARED_DATA_STRUCT* dataStruct, int* stepExecuted);
static int __APCLESS_payWave_CallAuthorisationHost(T_SHARED_DATA_STRUCT* dataStruct);
static int __APCLESS_payWave_ManageOnLineAuthorisation(T_SHARED_DATA_STRUCT* dataStruct);
static void __APCLESS_payWave_CopyCAKey51(T_SHARED_DATA_STRUCT* outputDataStruct);

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


/**
 * Fill buffer with specific payWave for transaction.
 * @param[out] dataStruct Shared exchange structure filled with the specific payWave data.
 * @return
 *     - \a TRUE if correctly performed.
 *     - \a FALSE if an error occurred.
 */
static int __APCLESS_payWave_AddpayWaveSpecificData(T_SHARED_DATA_STRUCT* dataStruct)
{
   int cr;
   int result = FALSE;
   T_KERNEL_TRANSACTION_FLOW_CUSTOM transactionFlowCustom;
   object_info_t objectInfo;
   unsigned char stepInterruption[KERNEL_PAYMENT_FLOW_STOP_LENGTH];// Bit field to stop payment flow,
                                                   // if all bit set to 0 => no stop during payment process
                                                           // if right bit set to 1 : stop after payment step number 1
   unsigned char stepCustom[KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH];   // Bit field to custom payment flow,
                                                   // if all bit set to 0 => no stop during payment process
                                                           // if right bit set to 1 : stop after payment step number 1
   if (dataStruct == NULL)
   {
      goto End;
   }

   // Init parameteters
   memset(stepInterruption, 0, sizeof(stepInterruption)); // Default Value : not stop on process
   memset(stepCustom, 0, sizeof(stepCustom)); // Default Value : not stop on process

   // Customize steps :
   ADD_STEP_CUSTOM(STEP_PAYWAVE_MSD_REMOVE_CARD, stepCustom);         // To do GUI when MStripe card has been read
   ADD_STEP_CUSTOM(STEP_PAYWAVE_QVSDC_REMOVE_CARD, stepCustom);       // To do GUI when MChip card has been read
   ADD_STEP_CUSTOM(STEP_PAYWAVE_QVSDC_GET_CERTIFICATE, stepCustom);   // To get the certificate for ODA step

   // TODO: If BlackList present  ADD_STEP_CUSTOM(STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL, StepCustom);   // To check Pan in Black list

   ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &objectInfo);


   // Add a tag for Do_Txn management
   cr = GTL_SharedExchange_AddTag(dataStruct, TAG_KERNEL_PAYMENT_FLOW_STOP, KERNEL_PAYMENT_FLOW_STOP_LENGTH, (const unsigned char *)stepInterruption);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // Add a tag for Do_Txn management
   memcpy(transactionFlowCustom.pucStepCustom, (void*)stepCustom, KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH);
   transactionFlowCustom.usApplicationType = objectInfo.application_type; // Kernel will call this application for customisation
   transactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL; // Kernel will call SERVICE_CUSTOM_KERNEL service id for customisation

   cr = GTL_SharedExchange_AddTag(dataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_KERNEL_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&transactionFlowCustom);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      goto End;
   }

   // TODO: Add Tag TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES

   result = TRUE;

End:
   return result;
}


/**
 * Get the payWave PinOnLineRequested state.
 * @param[in] resultDataStruct kernel shared buffer
 * @return
 *    - \a TRUE if required.
 *    - \a FALSE if not required or an error occurred.
 */
static int __APCLESS_payWave_IsPinOnLineRequested(T_SHARED_DATA_STRUCT* resultDataStruct)
{
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;

   position = SHARED_EXCHANGE_POSITION_NULL;
   cr = GTL_SharedExchange_FindNext(resultDataStruct, &position, TAG_KERNEL_ONLINE_PIN_REQUESTED, &readLength, &readValue);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      return FALSE;
   }

   // Get the transaction outcome
   return readValue[0];
}


/**
 * Get the payWave signature state.
 * @param[in] resultDataStruct Structure containing the kernel output.
 * @return
 *     - \a TRUE if signature is requested
 *     - \a FALSE if signature is not requested or an error occurred.
 */
static int __APCLESS_payWave_IsSignatureRequested(T_SHARED_DATA_STRUCT* resultDataStruct)
{
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;

   position = SHARED_EXCHANGE_POSITION_NULL;
   cr = GTL_SharedExchange_FindNext(resultDataStruct, &position, TAG_KERNEL_SIGNATURE_REQUESTED, &readLength, &readValue);

   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      return FALSE;
   }

   // Get the transaction outcome
   return readValue[0];
}


/**
 * If a balance amount is available, it displays the message with the balance. Otherwise nothing is displayed.
 * @param[in] screenId screen identifier of the message to display
 * @param[in] dataStruct shared buffer containing the balance amount (\a TAG_PAYWAVE_AVAILABLE_OFFLINE_SPENDING_AMOUNT)
 * @return
 *    - \a TRUE if no problem occurred (display done).
 *    - \a FALSE if not displayed (balance not available or an error occurred).
 */
static int __APCLESS_payWave_DisplaySreenWithBalance(unsigned long screenId, T_SHARED_DATA_STRUCT* dataStruct)
{
   int isFound;
   unsigned char* info;

   isFound = APCLESS_Tools_SharedBufferRetrieveInfo(dataStruct, TAG_PAYWAVE_AVAILABLE_OFFLINE_SPENDING_AMOUNT, &info);
   if (isFound)
   {
      APCLESS_Gui_DisplayScreenWithBalance(screenId, "EUR", 2, info, 6);

      return TRUE;
   }

   return FALSE;
}


/**
 * Activate or not the payWave kernel debug features.
 * @param[in] activate
 *    - TRUE : activate the PayPass kernel traces
 *    - FASLE : deactivate the PayPass kernel traces
 */
static void __APCLESS_payWave_DebugActivation(int activate)
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
         result = payWave_DebugManagement(sharedStructure);
      }

      // Destroy the shared buffer
      GTL_SharedExchange_DestroyShare(sharedStructure);
   }
}


/**
 * Check if Issuer Script could be executed.
 * @param[in] sharedStructure Shared buffer of the current transaction tags.
 * @return
 *  - \a TRUE if ISP could be executed.
 *  - \a FALSE else.
 */
static int __APCLESS_payWave_CheckISPConditions(T_SHARED_DATA_STRUCT* sharedStructure)
{
   int position, cr;
   unsigned long readLength;
   const unsigned char* readValue;

   // Verify Terminal can manage ISP
   position = SHARED_EXCHANGE_POSITION_NULL;
   cr = GTL_SharedExchange_FindNext(sharedStructure, &position, TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS, &readLength, &readValue);
   if (cr == STATUS_SHARED_EXCHANGE_OK)
   {
      if ((readValue[2] & 0x80) == 0)
      {  // Sorry, TTQ not configured for ISP management => end
         return FALSE;
      }
   }

   // Verify Card can manage ISP
   position = SHARED_EXCHANGE_POSITION_NULL;
   cr = GTL_SharedExchange_FindNext(sharedStructure, &position, TAG_PAYWAVE_CARD_TRANSACTION_QUALIFIERS, &readLength, &readValue);
   if (cr == STATUS_SHARED_EXCHANGE_OK)
   {
      if ((readValue[1] & 0x40) == 0)
      {  // Sorry, CTQ not configured for ISP management => end
         return FALSE;
      }
   }

   return TRUE;
}


/**
 * Wait for the card to be represented.
 * @param[in] dataStruct Shared buffer of the current transaction tags.
 * @return
 *    - \a TRUE if appropriate card has been put in field.
 *    - \a FALSE else.
 */
static int __APCLESS_payWave_WaitClessCard(T_SHARED_DATA_STRUCT* dataStruct)
{
   unsigned char sw1, sw2;
   unsigned char response[257];
   unsigned int responseLength;
   unsigned int timeout, event;
   unsigned int key, numOfCards;
   int isAppropriateCardFound;
   int result;
   int position;
   unsigned long readLength;
   const unsigned char* readValue;
   int loop = TRUE;
   unsigned long startTime;
   FILE* keyboard = NULL;


   // Local variables initialization
   isAppropriateCardFound = FALSE; // Default result : card hasn't been found

   // get the Final Select command already sent to the card
   position = SHARED_EXCHANGE_POSITION_NULL;
   if(STATUS_SHARED_EXCHANGE_OK != GTL_SharedExchange_FindNext(dataStruct, &position, TAG_EP_FINAL_SELECT_COMMAND_SENT, &readLength, &readValue))
   {
      // We can't find the last select command
      goto EndCardTreatment;
   }

   // Ask user to represent the card
   APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_REPRESENT_CARD);

   // Loop to wait the appropriate card (with good AID ....)
   startTime = GTL_StdTimer_GetCurrent();
   timeout =  __APCLESS_PAYWAVE_CARD_REPRESENT_TO *100;
   while(loop == TRUE)
   {
      // Close driver ( and cless field)
      ClessEmv_CloseDriver();

      // Open driver (and cless field)
      result = ClessEmv_OpenDriver ();
      if (result != CL_OK)              // can't open driver / cless field
         goto EndCardTreatment;

      // Start the asynchronous ISO14443-4 contactless detection
      result = ClessEmv_DetectCardsStart(1, CL_TYPE_AB);
      if (result != CL_OK)
         goto EndCardTreatment;

      // Open keyboard
      keyboard = fopen("KEYBOARD", "r*");

      // Loop to wait a contactless card detection or cancel key
      timeout =  GTL_StdTimer_GetRemaining(startTime, __APCLESS_PAYWAVE_CARD_REPRESENT_TO *100);
      while(timeout)
      {
         event = ttestall (CLESS | KEYBOARD, timeout);

         if(event & CLESS)
         {  // cless driver has detected something, get the result
            numOfCards = 1;
            result = ClessEmv_DetectCards(CL_TYPE_AB, &numOfCards, 0);
            break; // exit timeout loop
         }

         if(event & KEYBOARD)
         {
            key = getchar();
            if (key == T_ANN)
            {  // cancel key has been pressed -> end
               timeout = 0;
               break; //  exit timeout loop
            }
         }

         //case time out or key pressed -> try to continue the loop
         timeout =  GTL_StdTimer_GetRemaining(startTime, __APCLESS_PAYWAVE_CARD_REPRESENT_TO *100);
      }

      // Close keyboard (if we manage to open it)
      if(NULL != keyboard)
         fclose(keyboard);

      // Check card detection loop result
      if(timeout == 0)
      {  // case timeout or cancel -> stop cless detection and end
         ClessEmv_DetectCardsStop();
         goto EndCardTreatment;
      }

      if (result != CL_OK)
      {  //  case cless detection error  -> retry
         continue;
      }

      // Next step : Activate the card
      if (ClessEmv_ActiveCard(0, CL_ISO14443_4) != CL_OK)
      {  // case activation error -> retry
         continue;
      }

      // Send Final Select command to the contactless card.
      responseLength = sizeof(response);
      result = ClessEmv_Apdu(0, (void*)readValue, readLength, response, &responseLength);
      if ((result != CL_OK) || (responseLength < 2))
         goto EndCardTreatment; // A problem occurs

      // Check card response
      sw1 = ((unsigned char*)response)[responseLength-2];
      sw2 = ((unsigned char*)response)[responseLength-1];
      if ((sw1 == 0x90) && (sw2 == 0x00))
      {  // The appropriate card is found
         isAppropriateCardFound = TRUE;
         loop = FALSE;
      }
      else // wrong card response (not the good card)
      {
         APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_REMOVE_CARD);

         result = ClessEmv_DeselectCard(0, TRUE, TRUE); // Deselect card with wait a card removal
         if (result == CL_OK)
         {  // card correctly removed -> retry
            APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_REPRESENT_CARD);
         }
         else
         {  // A problem occurs -> end
            loop = FALSE;
         }
      }
   }

EndCardTreatment:

   return isAppropriateCardFound;
}


/**
 * Stop Cless field without waiting card removal.
 */
static void __APCLESS_payWave_StopClessCard(void)
{
   int result;

   // Card deselection
   result = ClessEmv_DeselectCard(0, TRUE, FALSE); // Deselect card without wait a card removal
   if (result != CL_OK)
   {
      // A problem occurs !
      // ..
   }

   // close cless field
   ClessEmv_CloseDriver();
}


/**
 * Perform the step after the transaction (Issuer Script Processing)
 * @param[in,out] dataStruct shared buffer containing the host response.
 * @param[out] stepExecuted
 *    - TRUE if \a payWave_AfterTransaction has been called
 *    - FALSE otherwise
 * @return
 *    - \a KERNEL_STATUS_OK or status of \a payWave_AfterTransaction() if it has been called.
 */
static int __APCLESS_payWave_ManageAfterTrn(T_SHARED_DATA_STRUCT* dataStruct, int* stepExecuted)
{
   int result, cr, cr2;
   int position;
   int nIssuerScriptPresent = FALSE;
   unsigned long readLength;
   const unsigned char* readValue;
   T_SHARED_DATA_STRUCT* issuerData;
   T_SHARED_DATA_STRUCT* tmpShared;


   // Local variable initialisation
   *stepExecuted = FALSE; // Default value : afterTxn hasn't been executed;

   issuerData = GTL_SharedExchange_InitShared(1024);
   tmpShared = GTL_SharedExchange_InitShared(2048);

   // Default Result
   cr = KERNEL_STATUS_OK;

   if ((issuerData != NULL) && (tmpShared != NULL))
   {
      // Add TAG_EMV_ISSUER_AUTHENTICATION_DATA tag, this tag must be treated first !
      position = SHARED_EXCHANGE_POSITION_NULL;
      cr = GTL_SharedExchange_FindNext(dataStruct, &position, TAG_EMV_ISSUER_AUTHENTICATION_DATA, &readLength, &readValue);
      if (cr == STATUS_SHARED_EXCHANGE_OK)
      {
         result = GTL_SharedExchange_AddTag(issuerData, TAG_EMV_ISSUER_AUTHENTICATION_DATA, readLength, readValue);

         if (result == STATUS_SHARED_EXCHANGE_OK)
            nIssuerScriptPresent = TRUE;
      }

      // Look for Issuer Script data
      {
          T_BER_TLV_DECODE_STRUCT BerTlvStruct;

          GTL_BerTlvDecode_Init (&BerTlvStruct, dataStruct->nPtrData, dataStruct->ulDataLength);

          // Parse Script  T1:71 or 72 L1 V1 ... Tn:71 or 72 Ln Vn
          for (;;)
          {
              /* Problem of script overwriting */
              int BytesRead;
              BER_TLV_TAG ReadTag;
              T_TI_LENGTH ReadLength;
              T_TI_VALUE  ReadValue;


              // Parse the next tag in the BER-TLV structure.
              cr = GTL_BerTlvDecode_ParseTlv (&BerTlvStruct, &ReadTag, &ReadLength, (BER_TLV_VALUE*)&ReadValue, (unsigned char)FALSE, &BytesRead);

              if (cr == STATUS_BER_TLV_END)
                  break ;

              if (cr == STATUS_BER_TLV_OK)
              {
                 if ((ReadTag == TAG_EMV_ISSUER_SCRIPT_TEMPLATE_1) || (ReadTag == TAG_EMV_ISSUER_SCRIPT_TEMPLATE_2))
                 {
                    result = GTL_SharedExchange_AddTag(tmpShared, ReadTag, ReadLength, ReadValue);
                    if (result != STATUS_SHARED_EXCHANGE_OK)
                    {
                       // continue processing ? see application requirements
                    }
                 }
              }
              else
                 break; // An error occurs
          } // end of loop about Script parsing
      }

      // If Issuer Script data are present, add them under TAG_PAYWAVE_ISSUER_SCRIPT_LIST
      if(tmpShared->ulDataLength)
      {
         result = GTL_SharedExchange_AddTag(issuerData, TAG_PAYWAVE_ISSUER_SCRIPT_LIST, tmpShared->ulDataLength, tmpShared->nPtrData);
         if (result == STATUS_SHARED_EXCHANGE_OK)
            nIssuerScriptPresent = TRUE;
      }

      // Default Result
      cr = KERNEL_STATUS_OK;

      // If Issuer authorization and/or script must be executed
      if (nIssuerScriptPresent)
      {
         payWave_GetAllData(tmpShared); // Get all the kernel data

         if (__APCLESS_payWave_CheckISPConditions(tmpShared) == TRUE)
         {
            if (__APCLESS_payWave_WaitClessCard(tmpShared) == TRUE)
            {
               // Perform the payWave transaction
               cr = payWave_AfterTransaction(issuerData);

               *stepExecuted = TRUE; // afterTxn has been executed;

               // Get Issuer Script Result
               position = SHARED_EXCHANGE_POSITION_NULL;
               cr2 = GTL_SharedExchange_FindNext(issuerData, &position, TAG_PAYWAVE_ISSUER_SCRIPT_RESULT, &readLength, &readValue);
               if (cr2 == STATUS_SHARED_EXCHANGE_OK)
               {
                  // Put Issuer Script Result in exchange struct given in parameter
                  GTL_SharedExchange_AddTag(dataStruct, TAG_PAYWAVE_ISSUER_SCRIPT_RESULT, readLength, readValue);
               }
            }
            __APCLESS_payWave_StopClessCard();
         }
      }
   }

   // Destroy the shared buffers
   if (tmpShared != NULL)
      GTL_SharedExchange_DestroyShare(tmpShared);
   if (issuerData != NULL)
      GTL_SharedExchange_DestroyShare(issuerData);

   return cr;
}


/**
 * Call the authorisation host.
 * @param[in,out] dataStruct Data to be sent to the host for online authorisation (input) and response tags are added to it (output).
 * @return
 *    - \a TRUE if correctly performed.
 *    - \a FALSE if an error occurred.
 */
static int __APCLESS_payWave_CallAuthorisationHost(T_SHARED_DATA_STRUCT* dataStruct)
{
   APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_ONLINE_PROCESSING);

   // Here we simulate an accepted authorisation with Issuer Script Processing
   GTL_SharedExchange_AddTag(dataStruct,TAG_EMV_ISSUER_AUTHENTICATION_DATA, 10,
                             (unsigned char*) "\x11\x22\x33\x44\x55\x66\x77\x88\x30\x30");
   GTL_SharedExchange_AddTag(dataStruct,TAG_EMV_ISSUER_SCRIPT_TEMPLATE_2, 33,
                             (unsigned char*) "\x9F\x18\x04\x11\x22\x33\x44\x86\x0D\x84\x24\x00\x00\x08\xAA\xBB\xCC\xDD\x11\x22\x33\x44\x86\x09\x84\x24\x00\x00\x04\x55\x66\x77\x88");
   GTL_SharedExchange_AddTag(dataStruct, TAG_EMV_AUTHORISATION_RESPONSE_CODE, 2,
                             (unsigned char*) "\x30\x30");

   return TRUE;
}


/**
 * Manage the online authorisation call and response.
 * @param[in,out] dataStruct shared buffer of the transaction data
 * @return
 *    - \a TRUE if transaction has to be saved
 *    - \a FALSE otherwise
 */
static int __APCLESS_payWave_ManageOnLineAuthorisation(T_SHARED_DATA_STRUCT* dataStruct)
{
   int position;
   unsigned long readLength;
   const unsigned char* readValue;
   int isAfterTrnExecuted = FALSE;

   // In fact, in this sample we are not managing the authorization, but just simulate
   // a response with Issuer Script Processing.

   // Manage case PIN online
   if(__APCLESS_payWave_IsPinOnLineRequested(dataStruct))
   {
      // TODO: Ask/get the user PIN
   }

   // Online authorisation
   if(TRUE == __APCLESS_payWave_CallAuthorisationHost(dataStruct))
   {
      position = SHARED_EXCHANGE_POSITION_NULL;
      if (GTL_SharedExchange_FindNext(dataStruct, &position, TAG_EMV_AUTHORISATION_RESPONSE_CODE, &readLength, &readValue) == STATUS_SHARED_EXCHANGE_OK)
      {
         if ((readValue[0] == 0x30) && (readValue[1] == 0x30))
         {
            // Do card post processing (issuer script)
            __APCLESS_payWave_ManageAfterTrn(dataStruct, &isAfterTrnExecuted); // Result not used to known if transaction is accepted or not

            // TODO: Print a receipt if requested
            // TODO: Manage signature if requested

            APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_ONLINE_APPROVED);

            // transaction has to be saved in the batch
            return TRUE;
         }
      }
   }

   APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_ONLINE_DECLINED);

   return FALSE;
}


/**
 * Get the Visa payWave CA Key 51 parameters.
 * @param[out] outputDataStruct Shared buffer filled with the CA Public Key data.
 */
static void __APCLESS_payWave_CopyCAKey51(T_SHARED_DATA_STRUCT* outputDataStruct)
{
   int cr;

   // Copy Modulus
   cr = GTL_SharedExchange_AddTag(outputDataStruct, TAG_EMV_INT_CAPK_MODULUS, sizeof(__APCLESS_payWave_caKey51Modulus), __APCLESS_payWave_caKey51Modulus);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      GTL_SharedExchange_ClearEx(outputDataStruct, FALSE);
      return;
   }

   // Copy Exponent
   cr = GTL_SharedExchange_AddTag(outputDataStruct, TAG_EMV_INT_CAPK_EXPONENT, sizeof(__APCLESS_payWave_caKey51Exponent), __APCLESS_payWave_caKey51Exponent);
   if (cr != STATUS_SHARED_EXCHANGE_OK)
   {
      GTL_SharedExchange_ClearEx(outputDataStruct, FALSE);
      return;
   }
}


/**
 * Calls the payWave kernel to perform the transaction.
 * @param[in] dataStruct Data buffer to be filled and used for payWave transaction.
 * @return payWave kernel result.
 *
 * @note gui with colored LEDs is not implemented
 */
int APCLESS_payWave_PerformTransaction(T_SHARED_DATA_STRUCT* dataStruct)
{
   int cr;
   int result = C_CLESS_CR_END;
   unsigned char signature;
   unsigned char* info;
   int saveInBatch = FALSE;


   // Indicate payWave kernel is going to be used (for customisation purposes)
   APCLESS_ParamTrn_SetCurrentPaymentScheme(APCLESS_SCHEME_PAYWAVE);

   // Init payWave kernel debug traces
   __APCLESS_payWave_DebugActivation(APCLESS_ParamTrn_GetDebugTrace());


   if (__APCLESS_payWave_AddpayWaveSpecificData(dataStruct))
   {

      // TODO: Launch task that scans the peripheral to be checks for cancel (keyboard, chip, swipe)

      // Perform the payWave transaction
      cr = payWave_DoTransaction(dataStruct);

      // TODO: stop the scanning task

      // Specific treatment for Pin management
      if (cr == KERNEL_STATUS_OFFLINE_APPROVED)
      {
         if (__APCLESS_payWave_IsPinOnLineRequested(dataStruct)) // If pin asked
            cr = KERNEL_STATUS_ONLINE_AUTHORISATION; // => mandatory to go on-line
      }

      // Check if signature is requested or not
      signature = __APCLESS_payWave_IsSignatureRequested (dataStruct);

      // CR analyse
      if (cr & KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK) // If mask has been set
      {
         // TODO: if a task has been launch to scan peripherals,
         //      analyse which event stops the kernel (chip, swipe, keyboard, ...)
      }
      else
      {

         switch (cr)
         {
            case KERNEL_STATUS_OK:
               // A good transaction state must be finished by a approved, declined, ...
               APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_ERROR_STATUS);
               break;

            case KERNEL_STATUS_OFFLINE_APPROVED:
               if (signature)
               {
                  APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_SIGNATURE_REQUIRED);
               }
               else
               {
                  if(__APCLESS_payWave_DisplaySreenWithBalance(APCLESS_SCREEN_OFFLINE_APPROVED, dataStruct) == FALSE)
                     APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_OFFLINE_APPROVED);

                  // Transaction shall be added to the batch
                  saveInBatch = TRUE;
               }

               // Print a receipt only if signature requested or merchant need to print a receipt
               // TODO: print ticket

               if (signature)
               {
                  // TODO: Ask merchant if signature is OK
                  // if yes  saveInBatch = TRUE;
               }

               break;

            case KERNEL_STATUS_OFFLINE_DECLINED:
                // TODO: if credit or refund are supported, look VisaWave 2.1 chapter 5.19 to manage
                // the case of a card AAC
               if(__APCLESS_payWave_DisplaySreenWithBalance(APCLESS_SCREEN_OFFLINE_DECLINED, dataStruct) == FALSE)
                  APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_OFFLINE_DECLINED);
               break;

            case KERNEL_STATUS_ONLINE_AUTHORISATION:
               if(__APCLESS_payWave_ManageOnLineAuthorisation(dataStruct) == TRUE)
                  saveInBatch = TRUE;
               break;

            case KERNEL_STATUS_USE_CONTACT_INTERFACE:
               result = CLESS_CR_MANAGER_RESTART_WO_CLESS;
               break;

            case KERNEL_STATUS_COMMUNICATION_ERROR:
               result = CLESS_CR_MANAGER_RESTART;
               break;

            case KERNEL_STATUS_REMOVE_AID:
               result = CLESS_CR_MANAGER_REMOVE_AID;
               break;

            case KERNEL_STATUS_MOBILE:
               if (APCLESS_Tools_SharedBufferRetrieveInfo(dataStruct, TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS, &info))
               {
                  if (info[0] & 0x20) // If qVSDC supported
                  {
                     ClessEmv_CloseDriver(); // Stop Cless Field
                     result = CLESS_CR_MANAGER_RESTART_DOUBLE_TAP;
                  }
                  else
                  {
                     // display error
                     APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_ERROR_STATUS);
                     result = CLESS_CR_MANAGER_END;
                  }
               }
               else
               {
                  result = CLESS_CR_MANAGER_RESTART_DOUBLE_TAP;
               }
               break;

            default:
               // For Visa Europe, no error should be displayed.
               // transaction shall be conducted over another interface
               result = CLESS_CR_MANAGER_RESTART_WO_CLESS;
               break;
         }
      }

      // Cless field must be stopped only if we don't try to work with an another AID
      if ((result != CLESS_CR_MANAGER_REMOVE_AID) && (result != CLESS_CR_MANAGER_RESTART_WO_CLESS) && (result != CLESS_CR_MANAGER_RESTART_DOUBLE_TAP))
      {
         // Deselect the card
         ClessEmv_DeselectCard(0, TRUE, FALSE);
      }

      // If the transaction does not restart from the beginning, set the LEDs into the idle state
      if ((result != CLESS_CR_MANAGER_RESTART) && (result != CLESS_CR_MANAGER_REMOVE_AID))
      {
         // Check if transaction shall be saved in the batch
         if (saveInBatch)
         {
            // TODO: Add record to the batch
         }

         // Increment the transaction sequence counter
         APCLESS_ParamTrn_IncrementTsc();
      }
   }

   // Additional possible processing :
   // - Perform an online authorisation if necessary
   // - Save the transaction in the batch if transaction is accepted
   // - Perform CVM processing if necessary

   // Transaction is completed, clear payWave kernel transaction data
   payWave_Clear();

   return result;
}


/**
 * Perform the payWave kernel customisation.
 * @param[in,out] sharedData Shared buffer used for customisation.
 * @param[in] ucCustomisationStep Step to be customised.
 * @return \a KERNEL_STATUS_CONTINUE always.
 */
int APCLESS_payWave_KernelCustomiseStep(T_SHARED_DATA_STRUCT* sharedData, const unsigned char ucCustomisationStep)
{
   int result = KERNEL_STATUS_CONTINUE;
   int position;
   unsigned char keyIndex;
   unsigned char rid[5];
   unsigned long readLength;
   const unsigned char* readValue;

    switch (ucCustomisationStep) // Steps to customise
    {
       case STEP_PAYWAVE_MSD_REMOVE_CARD:
       case STEP_PAYWAVE_QVSDC_REMOVE_CARD:
         APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_REMOVE_CARD);
         GTL_SharedExchange_ClearEx (sharedData, FALSE);
         result = KERNEL_STATUS_CONTINUE;
         break;

      case STEP_PAYWAVE_QVSDC_GET_CERTIFICATE:
         // Get the CA public key index (card)
         position = SHARED_EXCHANGE_POSITION_NULL;
         if (GTL_SharedExchange_FindNext (sharedData, &position, TAG_EMV_CA_PUBLIC_KEY_INDEX_CARD, &readLength, (const unsigned char **)&readValue) == STATUS_SHARED_EXCHANGE_OK)
            keyIndex = readValue[0];
         else
            keyIndex = 0;

         // Get RID value
         position = SHARED_EXCHANGE_POSITION_NULL;
         if (GTL_SharedExchange_FindNext (sharedData, &position, TAG_EMV_DF_NAME, &readLength, (const unsigned char **)&readValue) == STATUS_SHARED_EXCHANGE_OK)
            memcpy (rid, readValue, 5);
         else
            memset (rid, 0, sizeof(rid));

         // Clear the output structure
         GTL_SharedExchange_ClearEx (sharedData, FALSE);

         // TODO: With rid & keyIndex look for the CA public key data (Modulus, exponent, etc) in the application parameters
         // for this sample we are just using index 51
         if (keyIndex == 0x51)
         {
            __APCLESS_payWave_CopyCAKey51(sharedData);
         }

         result = KERNEL_STATUS_CONTINUE;
         break;

      case STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL:
         // TODO: Check if PAN is in the exception file
         result = KERNEL_STATUS_CONTINUE;
         break;

      // Other customisation steps could be defined if necessary

      default:
         break;
    }

    return result;
}

