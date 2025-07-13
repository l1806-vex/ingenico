/**
 * \file
 * This module manages the detection and selection process.
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

/// Macro to set a bit in the customize steps array for TAG_GENERIC_CUST_STEPS_TO_CUSTOMISE
#define __APCLESS_SELECTION_ADD_CUST_STEP(step, buffer)      buffer[(step-1)/8] += (1<<((step-1)%8))


/////////////////////////////////////////////////////////////////
//// Global data definitions ////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Static data definitions ////////////////////////////////////

static int __APCLESS_Selection_selectionMethod = APCLESS_SELECTION_UNKNOWN;


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


/**
 * Fill output TlvTree with data for \a CLESS_GIVE_INFO service or \a Cless_ExplicitSelection_LoadData().
 * @param[out] tlvTree output TlvTree filled with all the necessary data for card detection and application selection.
 * @param[in] explicitSelection \a TRUE if Explicit Selection is used. \a FALSE if Implicit Selection is used.
 * @return
 *    - \a TRUE if correctly performed.
 *    - \a FALSE if an error occurred.
 */
int APCLESS_Selection_GiveInfo (TLV_TREE_NODE * tlvTree, const int explicitSelection)
{
   int result;
   TLV_TREE_NODE tmpAidInfo; // Temporary Node for AID methods

   // Detection parameters
   unsigned char detectionType[] = {DETECTION_MASK_ISO_A | DETECTION_MASK_ISO_B ,0x00,0x00,0x00}; // ISO Type A and Type B cards
   unsigned char explicitDetectionTimeout[] = {0x00,0x00,0x17,0x70}; // 1 minute
   unsigned char numberOfCardsToDetect = 1;

   // PayPass AID parameters
   unsigned char aidPaypass[] = {0xA0, 0x00, 0x00, 0x00, 0x04, 0x10, 0x10};
   unsigned char aidPaypassId[] = {0x00, 0x00, 0x00, 0x00};          // SEPC PayPass AID internal identifier = 0
   unsigned char aidPaypassKernelToUse[] = {0x00, 0x02};             // PayPass kernel number = 2
   unsigned char aidPaypassOptions[] = {0x45, 0x01, 0x00, 0x00};     // Partial AID, Zero Amount, PPSE method

   // payWave AID parameters
   unsigned char aidpayWave[] = {0xA0, 0x00, 0x00, 0x00, 0x03, 0x10, 0x10};
   unsigned char aidpayWaveId[] = {0x00, 0x00, 0x00, 0x01};          // SEPC payWave AID internal identifier = 1
   unsigned char aidpayWaveKernelToUse[] = {0x00, 0x03};             // Visa payWave kernel number = 3
   unsigned char aidpayWaveOptions[] = {0x01, 0x01, 0x00, 0x00};     // Partial AID, PPSE method
   unsigned char aidpayWaveTTQ[] = {0xB6, 0x00, 0xC0, 0x00};

   result = FALSE;

   // tlvTree is the output TLV Tree, filled with the cless data
   if (tlvTree != NULL)
   {
      // Add card detection parameters

      // Detection type (0x9F928210, on 4 bytes).
      VERIFY(TlvTree_AddChild(*tlvTree, TAG_GENERIC_DETECTION_TYPE, detectionType, sizeof(detectionType))!= NULL);

      // Number of cards to detect
      VERIFY(TlvTree_AddChild(*tlvTree, TAG_GENERIC_DETECTION_NB_CARDS_TO_DETECT, &numberOfCardsToDetect, sizeof(numberOfCardsToDetect))!= NULL);

      if (explicitSelection)
      {
         // Global detection timeout, if necessary (0x9F928212, on 4 bytes) (in explicit selection only).
         VERIFY(TlvTree_AddChild (*tlvTree, TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT, explicitDetectionTimeout, sizeof(explicitDetectionTimeout))!= NULL);

         // Add the transaction amount
         VERIFY(TlvTree_AddChild (*tlvTree, TAG_EMV_AMOUNT_AUTH_BIN, APCLESS_ParamTrn_GetAmountBin(), 4)!= NULL);

         // Add the currency exponent
         VERIFY(TlvTree_AddChild (*tlvTree, TAG_EMV_TRANSACTION_CURRENCY_EXPONENT, APCLESS_ParamTrn_GetCurrencyExponent(), 1)!= NULL);
      }

      // TODO: For each supported AID supported, add the aid parameters (from the application configuration parameters)
      // for this sample, the AID parameters are directly coded in this source file

      // -----------  Add PayPass AID --------------------
      // Pointer on AID information nodes
      tmpAidInfo = TlvTree_AddChild(*tlvTree, TAG_EP_AID_INFORMATION, NULL, 0);

      // TAG_AID_TERMINAL : 0x9F06  -> MasterCard PayPass AID
      VERIFY(TlvTree_AddChild(tmpAidInfo, TAG_AID_TERMINAL, aidPaypass, sizeof(aidPaypass)) != NULL);

      // TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER : 0x9F928202 (corresponds to the index for quick search after application selection)
      VERIFY(TlvTree_AddChild(tmpAidInfo, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, aidPaypassId, sizeof(aidPaypassId)) != NULL);

      // TAG_EP_KERNEL_TO_USE : 0x9F928101
      VERIFY(TlvTree_AddChild(tmpAidInfo, TAG_EP_KERNEL_TO_USE, aidPaypassKernelToUse, sizeof(aidPaypassKernelToUse)));

      // TAG_EP_AID_OPTIONS : 0x9F928100
      VERIFY(TlvTree_AddChild(tmpAidInfo, TAG_EP_AID_OPTIONS, aidPaypassOptions, sizeof(aidPaypassOptions)));

      // optional add floor limits
      // ...

      //  --------- Add payWave AID ---------------
      // Pointer on AID information nodes
      tmpAidInfo = TlvTree_AddChild(*tlvTree, TAG_EP_AID_INFORMATION, NULL, 0);

      // TAG_AID_TERMINAL : 0x9F06  -> Visa payWave AID
      VERIFY(TlvTree_AddChild(tmpAidInfo, TAG_AID_TERMINAL, aidpayWave, sizeof(aidpayWave)) != NULL);

      // TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER : 0x9F928202 (corresponds to the index for quick search after application selection)
      VERIFY(TlvTree_AddChild(tmpAidInfo, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, aidpayWaveId, sizeof(aidpayWaveId)) != NULL);

      // TAG_EP_KERNEL_TO_USE : 0x9F928101
      VERIFY(TlvTree_AddChild(tmpAidInfo, TAG_EP_KERNEL_TO_USE, aidpayWaveKernelToUse, sizeof(aidpayWaveKernelToUse)));

      // TAG_EP_AID_OPTIONS : 0x9F928100
      VERIFY(TlvTree_AddChild(tmpAidInfo, TAG_EP_AID_OPTIONS, aidpayWaveOptions, sizeof(aidpayWaveOptions)));

      // TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS : 0x9F66
      VERIFY(TlvTree_AddChild(tmpAidInfo, TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS, aidpayWaveTTQ, sizeof(aidpayWaveTTQ)));

      // optional : add floor limits
      // ...


      // TODO: Add next Aid parameters
      // ...

      result = TRUE;
   }

   return result;
}


/**
 * Set the current selection method
 * @param[in] mode \a APCLESS_SELECTION_EXPLICIT, \a APCLESS_SELECTION_IMPLICIT or \a APCLESS_SELECTION_UNKNOWN
 */
void APCLESS_Selection_SetMethod(int mode)
{
   __APCLESS_Selection_selectionMethod = mode;
}


/**
 * Get the current selection method
 * @return \a APCLESS_SELECTION_EXPLICIT, \a APCLESS_SELECTION_IMPLICIT or \a APCLESS_SELECTION_UNKNOWN
 */
int APCLESS_Selection_GetMethod(void)
{
   return __APCLESS_Selection_selectionMethod;
}


/**
 * This function is called by the Entry Point to customise the Grapical User Interface during Selection.
 * @param[in,out] dataStruct shared buffer with the entry point application.
 * @return \a CLESS_CUST_DEFAULT or \a CLESS_CUST_CONTINUE
 */
int APCLESS_Selection_GuiCustomisation(T_SHARED_DATA_STRUCT* dataStruct)
{
   int result = CLESS_CUST_DEFAULT;
   int ret;
   int position;
   unsigned long readLength;
   unsigned char* readValue = NULL;
   unsigned short customStep;
   unsigned char stepsToCustomise[8];

   position = SHARED_EXCHANGE_POSITION_NULL;

   // Initialize the buffer
   memset(stepsToCustomise, 0, sizeof(stepsToCustomise));

   // Get the GUI step identifier
   ret = GTL_SharedExchange_FindNext(dataStruct, &position, TAG_GENERIC_CUST_STEP_ID, &readLength, (const unsigned char **) &readValue);
   if (ret == STATUS_SHARED_EXCHANGE_OK) // If tag found
   {
      // Save the step Identifier
      customStep = readValue[0];

      switch (customStep)
      // Steps to customize
      {
         case CLESS_CUST_GUI_REGISTRATION_STEP_ID: // Registration step
            GTL_SharedExchange_ClearEx(dataStruct, FALSE);
            __APCLESS_SELECTION_ADD_CUST_STEP(CLESS_CUST_GUI_PRESENT_CARD_AMOUNT_STEP_ID, stepsToCustomise);
            __APCLESS_SELECTION_ADD_CUST_STEP(CLESS_CUST_GUI_PRESENT_CARD_NO_AMOUNT_STEP_ID, stepsToCustomise);
            __APCLESS_SELECTION_ADD_CUST_STEP(CLESS_CUST_GUI_DOUBLE_TAP_STEP_ID, stepsToCustomise);
            __APCLESS_SELECTION_ADD_CUST_STEP(CLESS_CUST_GUI_RETRY_AMOUNT_STEP_ID, stepsToCustomise);
            __APCLESS_SELECTION_ADD_CUST_STEP(CLESS_CUST_GUI_RETRY_NO_AMOUNT_STEP_ID, stepsToCustomise);
            __APCLESS_SELECTION_ADD_CUST_STEP(CLESS_CUST_GUI_COLLISION_STEP_ID, stepsToCustomise);
            __APCLESS_SELECTION_ADD_CUST_STEP(CLESS_CUST_GUI_CARD_NOT_SUPPORTED_STEP_ID, stepsToCustomise);
            __APCLESS_SELECTION_ADD_CUST_STEP(CLESS_CUST_GUI_USE_CONTACT_STEP_ID, stepsToCustomise);
            GTL_SharedExchange_AddTag(dataStruct, TAG_GENERIC_CUST_STEPS_TO_CUSTOMISE, 8, stepsToCustomise);
            result = CLESS_CUST_CONTINUE;
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case CLESS_CUST_GUI_PRESENT_CARD_AMOUNT_STEP_ID:
         case CLESS_CUST_GUI_PRESENT_CARD_NO_AMOUNT_STEP_ID:
            // Check if a double tap is in progress ("see phone for instructions" is displayed)
            if (APCLESS_ParamTrn_GetDoubleTapInProgress())
            {
               APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_PHONE_INSTRUCTIONS);

               // Turn on the first LED only
               APCLESS_Gui_IndicatorWait();

               result = CLESS_CUST_CONTINUE;
            }
            else
            {
               if (APCLESS_Selection_GetMethod() == APCLESS_SELECTION_EXPLICIT)
               {
                  APCLESS_Gui_PresentCard("EUR", 2, APCLESS_ParamTrn_GetAmountBcd(), 6);
                  //continue to default processing to manage the leds
               }
               result = CLESS_CUST_DEFAULT;
            }
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case CLESS_CUST_GUI_DOUBLE_TAP_STEP_ID:

            // Display the message
            APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_PHONE_INSTRUCTIONS);

            // Turn on the first LED only
            APCLESS_Gui_IndicatorWait();

            result = CLESS_CUST_CONTINUE;

            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case CLESS_CUST_GUI_RETRY_AMOUNT_STEP_ID:
         case CLESS_CUST_GUI_RETRY_NO_AMOUNT_STEP_ID:

            if (APCLESS_Selection_GetMethod() == APCLESS_SELECTION_EXPLICIT)
            {
               // Turn on the first LED only
               APCLESS_Gui_IndicatorWait();

               // Customized to avoid that the TPass DLL performs a beep
               result = CLESS_CUST_CONTINUE;
            }
            else
            {
               result = CLESS_CUST_DEFAULT;
            }
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case CLESS_CUST_GUI_COLLISION_STEP_ID:
            // Display the message
            if (APCLESS_Selection_GetMethod() == APCLESS_SELECTION_EXPLICIT)
            {
               APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_COLLISION);
               result = CLESS_CUST_CONTINUE;
            }
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case CLESS_CUST_GUI_CARD_NOT_SUPPORTED_STEP_ID:
            if (APCLESS_Selection_GetMethod() == APCLESS_SELECTION_EXPLICIT)
            {
               APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_ERROR);
               result = CLESS_CUST_CONTINUE;
            }
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         case CLESS_CUST_GUI_USE_CONTACT_STEP_ID:
            if (APCLESS_Selection_GetMethod() == APCLESS_SELECTION_EXPLICIT)
            {
               APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_USE_CONTACT);
               result = CLESS_CUST_CONTINUE;
            }
            break;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         default:
            // Unknown or not managed step
            result = CLESS_CUST_DEFAULT;
            break;
      }
   }
   else
   {
      // Custom step tag not found
      result = CLESS_CUST_DEFAULT;
   }

   return result;
}


