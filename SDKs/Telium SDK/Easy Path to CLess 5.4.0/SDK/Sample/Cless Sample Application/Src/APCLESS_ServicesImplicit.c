/**
 * \file
 * This module implements the implicit transaction flow.
 * The following services are defined:
 *    - CLESS_GIVE_INFO: to get parameters for card detection and application selection
 *    - CLESS_DEBIT_AID: to process a transaction (call a cless kernel)
 *    - CLESS_END: to clean up if necessary.
 *    - CLESS_SERVICE_CUST_IMPSEL_GUI: for GUI customization
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
//// Global data definitions ////////////////////////////////////

static T_SHARED_DATA_STRUCT* __APCLESS_ServicesImplicit_kernelSharedBuffer;     ///< Share exchange buffer used with the payment kernels.


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __APCLESS_ServicesImplicit_FillGiveInfo(S_CLESS_GIVEINFO* paramOut);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

/**
 * Fill the output CLESS_GIVE_INFO DEL with the serialized TLV Tree containing all the necessary data for application selection.
 * @param[out] paramOut Output structure provided on the CLESS_GIVE_INFO service.
 * @return
 *    - \a TRUE if correctly performed.
 *    - \a FALSE if an error occurred.
 */
static int __APCLESS_ServicesImplicit_FillGiveInfo(S_CLESS_GIVEINFO* paramOut)
{
   int result, cr;
   TLV_TREE_NODE tlvTree;    // Output parameters

   result = TRUE;
   tlvTree = NULL;

   if(paramOut == NULL)
   {
      result = FALSE;
      goto End;
   }

   // Output Parameters initialisation
   tlvTree = TlvTree_New(0);
   if (tlvTree != NULL)
   {
      if (!APCLESS_Selection_GiveInfo(&tlvTree, FALSE))
      {
         result = FALSE;
         goto End;
      }

      // Serialize the TLV Tree in the DEL * of param_out
      cr = TlvTree_Serialize(tlvTree, TLV_TREE_SERIALIZER_DEFAULT, (unsigned char *)(&(paramOut->del)), sizeof (_DEL_));

      if (cr < 0)
      {
         memset (&(paramOut->del), 0, sizeof (_DEL_));
         result = FALSE;
         goto End;
      }
   }
   else
   {
      // Lack of memory
      result = FALSE;
      goto End;
   }


End:
   if (tlvTree != NULL)
      TlvTree_Release(tlvTree);

   return result;
}


/**
 * Implement the \a CLESS_GIVE_INFO service.
 * @param[in] appliId The application ID
 * @param[in] paramIn transaction input parameters (amount, currency ...)
 * @param[out] paramOut parameters for card detection and application selection
 * @return \a FCT_OK
 */
int APCLESS_ServicesImplicit_ClessGiveInfo(NO_SEGMENT appliId, S_TRANSIN* paramIn, S_CLESS_GIVEINFO* paramOut)
{
   unsigned char currencyCode[2];
   unsigned char amountBcd[6];

   (void) appliId;

   // Init/reset the transaction data (type, amount, date, kernel ...)
   APCLESS_ParamTrn_Clear();
   APCLESS_ParamTrn_SetCurrentPaymentScheme(APCLESS_SCHEME_UNKNOWN);
   APCLESS_Selection_SetMethod(APCLESS_SELECTION_IMPLICIT);

   // Prepare maximum transaction data before card presentation

   // Create/reset the kernel shared buffer (for selection result)
   if (__APCLESS_ServicesImplicit_kernelSharedBuffer == NULL)
   {
      __APCLESS_ServicesImplicit_kernelSharedBuffer = GTL_SharedExchange_InitShared(C_SHARED_KERNEL_BUFFER_SIZE);
   }
   else
   {  // case buffer already created -> just clear it
      GTL_SharedExchange_ClearEx(__APCLESS_ServicesImplicit_kernelSharedBuffer, FALSE);
   }

   // Verify kernel buffer has been created
   if (__APCLESS_ServicesImplicit_kernelSharedBuffer == NULL)
   {
      goto End;
   }


   // Set the transaction type
   switch(paramIn->transaction)
   {
      case DEBIT_TR:
         APCLESS_ParamTrn_SetTransactionType(APCLESS_TRANSACTION_TYPE_DEBIT);
         break;
      //case CREDIT_TR:    not supported by this sample
      //   APCLESS_ParamTrn_SetTransactionType(APCLESS_TRANSACTION_TYPE_REFUND);
      //   break;
      default: // Error management
         goto End;

   }

   if(paramIn->entry == NO_ENTRY)  // amount is not present
   {
      // Not supported by the sample
      goto End;
   }

   // Get and save transaction data (amount, date, time, etc).
   currencyCode[0] = paramIn->currency.code[0] - 0x30;
   currencyCode[1] = ((paramIn->currency.code[1] - 0x30) << 4) + (paramIn->currency.code[2] - 0x30);
   APCLESS_ParamTrn_SetCurrencyCode(currencyCode);
   APCLESS_ParamTrn_SetCurrencyExponent(paramIn->currency.posdec);
   APCLESS_Tools_ConvertAsciiToBcd(paramIn->big_amount, paramIn->big_amount_size, amountBcd, sizeof(amountBcd)*2 - paramIn->big_amount_size);
   APCLESS_ParamTrn_SetAmountBcd(amountBcd);
   APCLESS_ParamTrn_SetDateTime();  // use terminal current date

   // Fill the output structure with the data to be used for application selection
   if (!__APCLESS_ServicesImplicit_FillGiveInfo(paramOut))
   {
      goto End;
   }

End:
   return FCT_OK;
}


/**
 * Implement the \a CLESS_DEBIT_AID service.
 * It processes a contactless debit with AID already selected.
 * @param[in] appliId  The application ID
 * @param[in] size size of \a data
 * @param[in,out] data shared buffer to input transaction parameters and to output transaction result.
 * @return a \a CLESS_CR_MANAGER_xxxx status
 */
int APCLESS_ServicesImplicit_ClessDebitAid(NO_SEGMENT appliId, unsigned int size, void* data)
{
   int result = C_CLESS_CR_END;
   int kernelToUse;
   T_SHARED_DATA_STRUCT* sharedData;

   (void) appliId;
   (void) size;


   // Input parameters : a shared buffer structure
   sharedData = ((T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT *)data)->pDataStruct;

   // Indicates the cless kernel is not yet known
   APCLESS_ParamTrn_SetCurrentPaymentScheme(APCLESS_SCHEME_UNKNOWN);

   // Input parameters (__kernelSharedBuffer has been initialised in the CLESS_GIVE_INFO service, just clear it)
   GTL_SharedExchange_ClearEx (__APCLESS_ServicesImplicit_kernelSharedBuffer, FALSE);

   // Add the generic transaction data (previously saved) in the shared buffer (date, time, amount, ...).
   if (!APCLESS_Kernel_AddTransactionGenericData(__APCLESS_ServicesImplicit_kernelSharedBuffer))
   {
      goto End;
   }

   // Add AID related data to the shared buffer used with kernels
   if (!APCLESS_Kernel_AddAidRelatedData (sharedData, __APCLESS_ServicesImplicit_kernelSharedBuffer, &kernelToUse))
   {
      goto End;
   }

   // Call kernel in relationship with AID
   switch (kernelToUse)
   {
      case DEFAULT_EP_KERNEL_PAYPASS :
         result = APCLESS_PayPass_PerformTransaction(__APCLESS_ServicesImplicit_kernelSharedBuffer);
         break;

      case DEFAULT_EP_KERNEL_VISA :
         result = APCLESS_payWave_PerformTransaction(__APCLESS_ServicesImplicit_kernelSharedBuffer);
         break;

      case DEFAULT_EP_KERNEL_AMEX :
         //result = APCLESS_ExpressPay_PerformTransaction(__APCLESS_ServicesImplicit_kernelSharedBuffer);
         break;

      case DEFAULT_EP_KERNEL_DISCOVER :
         //result = APCLESS_Discover_PerformTransaction(__APCLESS_ServicesImplicit_kernelSharedBuffer);
         break;

      case DEFAULT_EP_KERNEL_INTERAC :
         // result = APCLESS_Interac_PerformTransaction(__APCLESS_ServicesImplicit_kernelSharedBuffer);
         break;

      default:
         break;
   }


End:

   // Set response data
   GTL_SharedExchange_Clear(sharedData);

   // TODO: Add transaction result to sharedData for cash register

   // Wait end of message display
   APCLESS_Gui_DisplayScreen(APCLESS_SCREEN_WAIT_END_DISPLAY);

   return result;
}


/**
 * This service is called after the contactless transaction (or when a contact transaction is initiated).
 * It can be used to close peripheral (that had been opened in the CLESS_GIVE_INFO entry point for example) or doing
 * any other treatments.
 * \param[in] appliId The application ID
 * \return \a FCT_OK always.
 */
int APCLESS_ServicesImplicit_ClessEnd(NO_SEGMENT appliId)
{
   (void) appliId;

   // Close every opened drivers
   // ...


   // Finalise processing before returning to idle state
   // ...

   APCLESS_Selection_SetMethod(APCLESS_SELECTION_UNKNOWN);
   APCLESS_ParamTrn_SetDoubleTapInProgress(FALSE);

   return FCT_OK;
}


/**
 * This function is called to customise the GUI during the implicit selection processing.
 * @param[in] size Size of \a data (not used as \a data is a shared service call struct).
 * @param[in] data Shared buffer containing data necessary to customise the step.
 * @return
 *   - \a CLESS_CUST_DEFAULT if default DLL GUI shall be executed.
 *   - \a CLESS_CUST_CONTINUE if application made customisation and default DLL GUI shall not be executed.
 */
int APCLESS_ServicesImplicit_CustomSelectionGui(unsigned int size, void* data)
{
   T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT* sharedStruct;

   (void)size;
   sharedStruct = (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT*)data;

   return APCLESS_Selection_GuiCustomisation(sharedStruct->pDataStruct);
}


