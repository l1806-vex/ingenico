/*!
 ------------------------------------------------------------------------------
 INGENICO Technical Software Department
 ------------------------------------------------------------------------------
 Copyright (c) 2012, Ingenico.
 28-32 boulevard de Grenelle 75015 Paris, France.
 All rights reserved.

 This source program is the property of INGENICO Company and may not be copied
 in any form or by any means, whether in part or in whole, except under license
 expressly granted by INGENICO company

 All copies of this program, whether in part or in whole, and
 whether modified or not, must display this and all other
 embedded copyright and ownership notices in full.
 ------------------------------------------------------------------------------

 Project : Service 100  Sample
 Module  : FUN - Demo Features Unit

 @file      fun_Service100.c
 @brief     Contains all definitions of functions utilized for Service 100.
 @date      03/07/2013

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include "sdk30.h"
#include <GL_GraphicLib.h>
#include "bitmap.h"
#include "hterm.h"
#include "fun_Service100.h"
#include "Par.h"
#include "err_process.h"
#include "trace.h"
#include "Utilities.h"

/* global StructDebitEmv structure used in Servicecall*/
static StructDebitEmv s_debit;

/** initialize s_debit (StructDebitEmv)struct
 * \param[in] unsigned long *amount amount entry
 * \param[in] S_MONEY *currency currency struct
 *
 * \return
 */
void _FUN_InitDebit(unsigned long *amount, S_MONEY *currency, PAYMENT_MODE gPayment, SUPPORT_TYPE gSupport, TRANSACTION_TYPE gType)
{
   /* Structure debitout default */
   s_debit.param_out.noappli = 0xFF;
   s_debit.param_out.rc_payment = PAY_OK;
   memclr(s_debit.param_out.card_holder_nb, sizeof(s_debit.param_out.card_holder_nb));
   /* Structure debitin default */
   /* I don't know the type of support */
   s_debit.param_in.support = gSupport;
   /* The amount comes from a cash register */
   s_debit.param_in.entry = CASH_REG_ENTRY;
   /* I want a debit with a card */
   s_debit.param_in.payment = gPayment;
   /* This is a debit */
   s_debit.param_in.transaction = gType;
   /* The amount */
   s_debit.param_in.amount = *amount;
   /* The currency */
   memcpy((char*) &s_debit.param_in.currency, (char*) currency, sizeof(S_MONEY));
   /* The cash register number */
   memcpy(s_debit.param_in.cashreg, "01", 2);
}

/** Wait a ship card to be inserted or timeout occurred.
 *
 * \param[in] unsigned short to timeout value
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref Negative in case of error
 */
unsigned char _FUN_WaitCard(unsigned short to)
{
   FILE *hcam0;
   uchar ucStatus;
   unsigned char Cr;
   int ret;
   /* Open if CAM0 if not */
   hcam0 = stdcam0();
   if (hcam0 == NULL)
   {
      hcam0 = fopen("CAM0", "rw");
   }
   status(hcam0, &ucStatus);
   /* CAM is already present */
   if ((ucStatus & CAM_PRESENT) == CAM_PRESENT)
   {
      Cr = CR_ENTRY_OK;
   }
   else
   {
      guiScreen("Service 100", "INSERT CARD", GL_ICON_NONE, 0);
      do
      {
         ret = ttestall(KEYBOARD | CAM0, (to * 100));
         if (ret == KEYBOARD)
         {
            if (getchar() == T_ANN) /*cancel choice*/
            {
               Cr = CR_ENTRY_CANCEL;
               break;
            }
         }
         else
         {
            if (ret == CAM0) /*a card has been inserted*/
            {
               Cr = CR_ENTRY_OK;
               break;
            }
            else /*time out has occurred*/
            {
               Cr = CR_ENTRY_TIME_OUT;
               break;
            }
         }
      } while (1);
   }

   /* Close CAM0 if opened */
   if (hcam0 != NULL)
   {
      power_down(stdcam0());
      fclose(stdcam0());
   }

   return (Cr);
}
/** Wait a card to be swiped or timeout occurred.
 *
 *\param[in] unsigned short to timeout value
 *
 *\return
 *         -   \ref CR_ENTRY_OK if OK.
 *         -   \ref CR_ENTRY_TIME_OUT if timeout has occurred.
 *         -   \ref CR_ENTRY_CANCEL
 */
unsigned char _FUN_WaitSwipe(unsigned short to)
{
   FILE *swipe2;
   unsigned char Cr;
   int ret;
   LG_REF_CLI lg_ref;
   TRACK2_BUFFER track2; // track 2 contents
   int cr;
   swipe2 = fopen("SWIPE2", "r");
   guiScreen("Service 100", "SWIPE CARD", GL_ICON_NONE, 0);
   do
   {
      ret = ttestall(KEYBOARD | SWIPE2, (to * 100));
      if (ret == KEYBOARD)
      {
         if (getchar() == T_ANN)
         {
            Cr = CR_ENTRY_CANCEL;/*cancel choice*/
            break;
         }
      }
      else
      {
         if (ret == SWIPE2)
         {
            memclr(track2, sizeof(TRACK2_BUFFER));
            cr = is_iso2(swipe2, &lg_ref, track2);
            switch (cr)
            {
               case ISO_OK:
               case DEF_LUH:
                  /*a card has been swiped*/
                  memclr(s_debit.param_in.track2, sizeof(TRACK2_BUFFER));
                  memcpy(s_debit.param_in.track2, track2, sizeof(TRACK2_BUFFER));
                  Cr = CR_ENTRY_OK;
                  break;
               case DEF_SEP:
               case DEF_NUM:
               case DEF_LRC:
               default:
                  Cr = CR_ENTRY_CANCEL; /*not supported*/
                  break;
            }
            break;
         }
         else
         {
            Cr = CR_ENTRY_TIME_OUT;/*time out has occurred*/
            break;
         }
      }
   } while (1);
   fclose(swipe2);

   return (Cr);
}
/** Get Currency code .
 *
 *\param[out] T_COD_MONEY * currencyCode currency code.
 *
 *\return
 *         -   \ref 0 if OK.
 *         -   \ref 1 if Par file is not found or bad currency value found in Par file.
 */
int _FUN_InitCurrency(T_COD_MONEY * currencyCode)
{
   int ret;
   char* currencyName;
   TRC_Trace_t trc_fun; /* trace instance*/

   /* Array of currency code supported*/
   static const char* gCurrencyArray[] = { "978", "840", "826", "949", "643", "124", "036", "986" };

   trc_fun = TRC_HandleGet();

   /*Get currency name */
   ret = PAR_CurrencyNameGet(&currencyName);
   if (ret == PAR_OK)
   {
      if (strcmp(currencyName, "EUR") == 0)
      {
         TRC_TRACE_INFO(trc_fun, "CURRENCY NAME: EUR");
         memcpy(currencyCode, gCurrencyArray[0], 3);
      }
      else if (strcmp(currencyName, "USD") == 0)
      {
         TRC_TRACE_INFO(trc_fun, "CURRENCY NAME: USD");
         memcpy(currencyCode, gCurrencyArray[1], 3);
      }
      else if (strcmp(currencyName, "GBP") == 0)
      {
         TRC_TRACE_INFO(trc_fun, "CURRENCY NAME: GBP");
         memcpy(currencyCode, gCurrencyArray[2], 3);
      }
      else if (strcmp(currencyName, "TRY") == 0)
      {
         TRC_TRACE_INFO(trc_fun, "CURRENCY NAME: TRY");
         memcpy(currencyCode, gCurrencyArray[3], 3);
      }
      else if (strcmp(currencyName, "RUB") == 0)
      {
         TRC_TRACE_INFO(trc_fun, "CURRENCY NAME: RUB");
         memcpy(currencyCode, gCurrencyArray[4], 3);
      }
      else if (strcmp(currencyName, "CAD") == 0)
      {
         TRC_TRACE_INFO(trc_fun, "CURRENCY NAME: CAD");
         memcpy(currencyCode, gCurrencyArray[5], 3);
      }
      else if (strcmp(currencyName, "AUD") == 0)
      {
         TRC_TRACE_INFO(trc_fun, "CURRENCY NAME: ,AUD");
         memcpy(currencyCode, gCurrencyArray[6], 3);
      }
      else if (strcmp(currencyName, "RBR") == 0)
      {
         TRC_TRACE_INFO(trc_fun, "CURRENCY NAME: RBR");
         memcpy(currencyCode, gCurrencyArray[7], 3);
      }
      else
      { /* bad value for currency code found in PAr file*/
         UI_ErrMsgDisplay(ERR_BAD_PAR_CURRENCY_VALUE);
         ret = 1;
      }
   }
   else
   {
      /*No Par file found*/
      UI_ErrMsgDisplay(ERR_PAR_FILE_NOT_FOUND);
      ret = 1;
   }
   return ret;
}
/** Print Ticket to indicate status of transaction already performed.
 *
 *\param[in] unsigned char payment_Status.
 *
 *\return
 *
 */
void _FUN_Print_Ticket(unsigned char payment_Status)
{
   FILE * hprinter;
   /* Print result of transaction */
   hprinter = fopen("PRINTER", "w");

   if (payment_Status == PAY_OK)
   {
      pprintf("Transaction OK\n");
      pprintf("Appli No   : %04X\n", s_debit.param_out.noappli);
   }
   else
   {
      pprintf("Transaction NOK\n");
   }
   pprintf("\n\n\n\n\n");
   ttestall(PRINTER, 0);

   fclose(hprinter);
}
/** Check if Service is available and perform a Service call (service100).
 *
 *\param[in] void.
 *
 *\return
 *         -   \ref CR_ENTRY_OK if OK.
 *         -   \ref CR_ENTRY_TIME_OUT if timeout has occurred.
 *         -   \ref CR_ENTRY_CANCEL
 *
 */

int FUN_DoTransaction(void)
{
   unsigned char priority;
   int retour;
   int cr = 1;
   S_MONEY currency;
   char *currencyName;
   unsigned long amount;
   char strAmount[13] = "0000";
   int ret;
   SUPPORT_TYPE support;
   PAYMENT_MODE payment;
   TRANSACTION_TYPE type;
   /* Check if Service is available */
   if (ServiceGet(TYPE_GESTIONNAIRE, 100, &priority) == 0)
   {
      /* Get Currency name */
      ret = PAR_CurrencyNameGet(&currencyName);
      /* Initialize Currency code */
      ret = _FUN_InitCurrency(&currency.code);
      if (ret == 0)
      {
         /*Enter Amount*/
         do
         {
            cr = enterAmt("Service 100", "ENTER AMOUNT ", strAmount, sizeof(strAmount), 2);
            amount = atoi(strAmount);
         } while ((cr == GL_KEY_VALID) && (amount == 0));

         /* Initialize Currency structure */
         memcpy(currency.nom, currencyName, sizeof(T_NOM_MONEY));
         currency.posdec = 2;

         if (cr == GL_KEY_VALID)
         {
            /* Default value */
            support = UNKNOWN_SUPPORT;
            payment = UNKNOWN_PAYMENT;
            type = DEBIT_TR;
            /* choose payment mode menu*/
            cr = Ui_PaymentDisplayMenu();
            switch (cr)
            {
               case 0:
                  payment = UNKNOWN_PAYMENT;
                  break;
               case 1:
                  payment = CARD_PAYMENT;
                  cr = CR_ENTRY_OK;
                  break;
               case 2:
                  payment = CHEQUE_PAYMENT;
                  cr = CR_ENTRY_OK;
                  break;
               default:
                  break;
            }

            if (cr == CR_ENTRY_OK)
            {
               if (payment == CARD_PAYMENT)
               {
                  /* choose payment support menu*/
                  cr = Ui_SupportDisplayMenu();
                  switch (cr)
                  {
                     case 0:
                        support = CHIP_SUPPORT;
                        cr = _FUN_WaitCard(30);
                        break;
                     case 1:
                        support = TRACK2_SUPPORT;
                        cr = _FUN_WaitSwipe(30);
                        break;
                     case 2:
                        support = OPERATOR_SUPPORT;
                        strcpy((char*) s_debit.param_in.track2, "B4761739001010010D05110000000F");
                        cr = CR_ENTRY_OK;
                        break;
                     case 3:
                        support = UNKNOWN_SUPPORT;
                        cr = CR_ENTRY_OK;
                        break;
                     default:
                        break;
                  }
               }

            }
            if (cr == CR_ENTRY_OK)
            {
               /* choose transaction type  menu*/
               cr = Ui_TypeDisplayMenu();
               switch (cr)
               {
                  case 0:
                     type = DEBIT_TR;
                     break;
                  case 1:
                     type = CANCEL_TR;
                     break;
                  case 2:
                     type = CREDIT_TR;
                     cr = CR_ENTRY_OK;
                     break;
                  case 3:
                     type = EXT_CANCEL_TR;
                     break;
               }
            }
            if (cr == CR_ENTRY_OK)
            {
               _FUN_InitDebit(&amount, &currency, payment, support, type);
               ret = ServiceCall(TYPE_GESTIONNAIRE, 100, sizeof(StructDebitEmv), &s_debit, &retour);
               if (IsPrinter())
                  _FUN_Print_Ticket(s_debit.param_out.rc_payment);
               Ui_TransctionStatusMenu(s_debit.param_out.rc_payment);
            }
         }
      }
   }
   return (cr);
}
