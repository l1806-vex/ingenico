/**
 * \file
 * This module implements the explicit transaction flow.
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

#define __APCLESS_EXPLICIT_STEP_DETECTION                 1        ///< Explicit execution step to detect the card
#define __APCLESS_EXPLICIT_STEP_SELECTION                 2        ///< Explicit execution step to select a card application
#define __APCLESS_EXPLICIT_STEP_KERNEL_EXECUTION          3        ///< Explicit execution step to run a kernel
#define __APCLESS_EXPLICIT_STEP_KERNEL_EXECUTION_BIS      4        ///< Explicit execution step to run again the kernel (used by Visa card for payWave kernel)
#define __APCLESS_EXPLICIT_STEP_CHECK_RESULT              5        ///< Explicit execution step to check kernel result ( to manage restart)
#define __APCLESS_EXPLICIT_STEP_END                       99       ///< Explicit execution step to stop processing


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

/**
 * This function performs all a contactless transaction using the explicit selection method.
 * The main steps are:
 *  - parameters initialization
 *  - card detection and application selection
 *  - contactless kernel execution
 */
void APCLESS_Explicit_DoTransaction(void)
{
   int result;
   TLV_TREE_NODE selectionTlvTree = NULL;
   T_SHARED_DATA_STRUCT* selectionSharedData = NULL;
   T_SHARED_DATA_STRUCT* kernelSharedBuffer = NULL;
   FILE* keyboard;
   unsigned char end, cancel = FALSE;
   int event;
   int kernelToUse;
   int step;

   // ********** Initialize application parameters **************


   // ********** Initialize transaction parameters **************
   // Set the transaction parameters
   APCLESS_ParamTrn_SetTransactionType(APCLESS_TRANSACTION_TYPE_DEBIT);
   APCLESS_ParamTrn_SetAmountBcd((unsigned char*) "\x00\x00\x00\x00\x01\x23");  //set the transaction amount 1.23 EUR
   APCLESS_ParamTrn_SetCurrencyCode((unsigned char*) "\x09\x78"); // Euro currency code
   APCLESS_ParamTrn_SetCurrencyExponent(2);
   APCLESS_ParamTrn_SetDateTime();  // use terminal current date

   // Indicate the selection is explicit
   APCLESS_Selection_SetMethod(APCLESS_SELECTION_EXPLICIT);

   // Set the transaction kernel to "unknown"
   APCLESS_ParamTrn_SetCurrentPaymentScheme(APCLESS_SCHEME_UNKNOWN);

   // Indicate no tap is in progress
   APCLESS_ParamTrn_SetDoubleTapInProgress(FALSE);


   // ********** Initialize card detection & selection parameters **************
   // create selection TLV tree (for selection input parameters)
   selectionTlvTree = TlvTree_New(0);
   if (selectionTlvTree == NULL)
   {
      goto End;
   }

   // Create the selection shared buffer (for selection result)
   selectionSharedData = GTL_SharedExchange_InitShared(10240);
   if (selectionSharedData == NULL)
   {
      goto End;
   }

   // Create the kernel shared buffer
   kernelSharedBuffer = GTL_SharedExchange_InitShared(C_SHARED_KERNEL_BUFFER_SIZE);
   if (kernelSharedBuffer == NULL)
   {
      goto End;
   }


   // Set and load data for application explicit selection
   result = APCLESS_Selection_GiveInfo(&selectionTlvTree, TRUE);
   if (result != TRUE)
   {
      goto End;
   }

   result = Cless_ExplicitSelection_LoadData(selectionTlvTree);
   if (result != CLESS_STATUS_OK)
   {
      goto End;
   }

   // Set the customisation function to be called for GUI customisation
   Cless_ExplicitSelection_Custom_RegistrationForGui(&APCLESS_Selection_GuiCustomisation);

   // Perform the selection pre-processing
   result = Cless_ExplicitSelection_EntryPoint_TransactionPreProcessing();
   if (result != CLESS_STATUS_OK)
   {
      goto End;
   }


   // ********** Execute transaction steps (detection, selection, kernel execution) **************

   step = __APCLESS_EXPLICIT_STEP_DETECTION;
   while(step < __APCLESS_EXPLICIT_STEP_END)
   {
      switch(step)
      {
         // ********** Execute card detection **************
         case __APCLESS_EXPLICIT_STEP_DETECTION:

            // Clear the selection Shared buffer (for selection result)
            GTL_SharedExchange_ClearEx(selectionSharedData, FALSE);

            // Launch the card detection
            result = Cless_ExplicitSelection_GlobalCardDetection();
            if (result != CLESS_STATUS_OK)
            {
               step = __APCLESS_EXPLICIT_STEP_END;
               break;
            }

            // Wait contactless event (or cancel if red key is pressed)
            end = FALSE;
            cancel = FALSE;

            keyboard = fopen("KEYBOARD", "r");

            do
            {
               event = ttestall(KEYBOARD | CLESS, 0);

               if (event & CLESS)
               {
                  end = TRUE;
               }
               else   // event  KEYBOARD
               {
                  if (getc(keyboard) == T_ANN)
                  {
                     Cless_ExplicitSelection_GlobalCardDetectionCancel();
                     cancel = TRUE;
                     end = TRUE;
                  }
               }
            } while(!end);

            if (keyboard != NULL)
               fclose (keyboard);

            // Check if card detection has been canceled
            if(cancel == TRUE)
            {
               step = __APCLESS_EXPLICIT_STEP_END;
               break;
            }

            // Get the card detection result
            result = Cless_Generic_CardDetectionGetResults(selectionSharedData, TRUE);
            if (result != CLESS_STATUS_OK)
            {
               step = __APCLESS_EXPLICIT_STEP_END;
               break;
            }

            step = __APCLESS_EXPLICIT_STEP_SELECTION;
            break;

         // ********** Execute card selection **************
         case __APCLESS_EXPLICIT_STEP_SELECTION:

            // Launch application selection
            result = Cless_ExplicitSelection_Selection_ApplicationSelectionProcess(selectionSharedData);
            if (result != CLESS_STATUS_OK)
            {
               if(result == CLESS_STATUS_COMMUNICATION_ERROR)
               {  // communication error -> retry card detection & selection
                  result = CLESS_CR_MANAGER_RESTART;
                  step = __APCLESS_EXPLICIT_STEP_CHECK_RESULT;
               }
               else
               {
                  step = __APCLESS_EXPLICIT_STEP_END;
               }
               break;
            }

            step = __APCLESS_EXPLICIT_STEP_KERNEL_EXECUTION;
            break;

         // ********** Execute a kernel **************
         case __APCLESS_EXPLICIT_STEP_KERNEL_EXECUTION:

            // First clear the buffer to be used with the contactless kernel
            GTL_SharedExchange_ClearEx (kernelSharedBuffer, FALSE);

            // Add the generic transaction data (previously saved) in the shared buffer (date, time, amount, etc).
            if (!APCLESS_Kernel_AddTransactionGenericData(kernelSharedBuffer))
            {
               step = __APCLESS_EXPLICIT_STEP_END;
               break;
            }

            // Add AID related data to the shared buffer used with kernels
            if (!APCLESS_Kernel_AddAidRelatedData (selectionSharedData, kernelSharedBuffer, &kernelToUse))
            {
               step = __APCLESS_EXPLICIT_STEP_END;
               break;
            }

            // Call kernel in relationship with AID
            switch (kernelToUse)
            {
               case DEFAULT_EP_KERNEL_PAYPASS :
                  result = APCLESS_PayPass_PerformTransaction(kernelSharedBuffer);
                  break;

               case DEFAULT_EP_KERNEL_VISA :
                  result = APCLESS_payWave_PerformTransaction(kernelSharedBuffer);
                  break;

               case DEFAULT_EP_KERNEL_AMEX :
                  //result = APCLESS_ExpressPay_PerformTransaction(kernelSharedBuffer);
                  break;

               case DEFAULT_EP_KERNEL_DISCOVER :
                  //result = APCLESS_Discover_PerformTransaction(kernelSharedBuffer);
                  break;

               case DEFAULT_EP_KERNEL_INTERAC :
                  // result = APCLESS_Interac_PerformTransaction(kernelSharedBuffer);
                  break;

               // ******* Default case **********
               default:
                  // Unknown kernel... problem in parameters ?
                  // Display or log an error ?
                  break;
            }

            step = __APCLESS_EXPLICIT_STEP_CHECK_RESULT;
            break;

         // ********** Check (kernel) result (restart needed ?) **************
         case __APCLESS_EXPLICIT_STEP_CHECK_RESULT:

            switch(result)
            {
               case CLESS_CR_MANAGER_REMOVE_AID:
                  // Restart with application selection
                  APCLESS_ParamTrn_SetCurrentPaymentScheme(APCLESS_SCHEME_UNKNOWN);
                  step = __APCLESS_EXPLICIT_STEP_SELECTION;
                  break;

               case CLESS_CR_MANAGER_RESTART_DOUBLE_TAP:
                  // Restart with card detection
                  Cless_ExplicitSelection_DetectionPrepareForRestart(TRUE);
                  APCLESS_ParamTrn_SetCurrentPaymentScheme(APCLESS_SCHEME_UNKNOWN);
                  step = __APCLESS_EXPLICIT_STEP_DETECTION;
                  break;

               case CLESS_CR_MANAGER_RESTART:
               case CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY:
                  // Restart with card detection
                  Cless_ExplicitSelection_DetectionPrepareForRestart(FALSE);
                  APCLESS_ParamTrn_SetCurrentPaymentScheme(APCLESS_SCHEME_UNKNOWN);
                  step = __APCLESS_EXPLICIT_STEP_DETECTION;
                  break;

               default:
                  // Other result value -> end processing
                  step = __APCLESS_EXPLICIT_STEP_END;
                  break;
            }

            break;

         // ******* Default case **********
         default:    // iStep value unknown -> end processing
            step = __APCLESS_EXPLICIT_STEP_END;
            break;
      }
   }


End :   // End processing (cleaning)

   // Wait end of message display
   APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_WAIT_END_DISPLAY);

   // Release the TLV Tree if allocated
   if (selectionTlvTree != NULL)
   {
      TlvTree_Release(selectionTlvTree);
      selectionTlvTree = NULL;
   }

   // Release shared buffer if allocated
   if (selectionSharedData != NULL)
      GTL_SharedExchange_DestroyShare(selectionSharedData);

   if (kernelSharedBuffer != NULL)
      GTL_SharedExchange_DestroyShare(kernelSharedBuffer);

   // Clear the detection/selection resources
   Cless_ExplicitSelection_ClearGlobalData();

   // Reset APCLESS transaction parameters
   APCLESS_Selection_SetMethod(APCLESS_SELECTION_UNKNOWN);
   APCLESS_ParamTrn_SetCurrentPaymentScheme(APCLESS_SCHEME_UNKNOWN);
   APCLESS_ParamTrn_SetDoubleTapInProgress(FALSE);

   // Set the LEDs into the idle state
   APCLESS_Gui_IndicatorIdle();
}


