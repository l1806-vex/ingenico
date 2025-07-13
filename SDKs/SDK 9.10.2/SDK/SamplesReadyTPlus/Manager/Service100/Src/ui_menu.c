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

 Project : GPRS Sample
 Module  : UI - User Interface Unit

 @file      ui_menu.c
 @brief     Contains the definition of the menu of the application.
 menu.

 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include "sdk30.h"
#include "utilities.h"
#include "ui_userinterface.h"
#include "fun_service100.h"

/* global array for choosing Payment mode */
static const char *gMenuUserPaymentArray[4] = { "Unknown", "Cards", "Check", 0 };
/*  global array for choosing Payment support */
static const char *gMenuUserSupportArray[5] = { "Card", "Swipe2", "Manual", "Unknown", 0 };
/*  global array for choosing transaction type */
static const char *gMenuUserTypeArray[5] = { "Debit", "Cancel", "Credit", "Extended Cancel", 0 };

/** Display choose Payment menu (UNKNOWN_PAYMENT/CARD_PAYMENT/CHEQUE_PAYMENT).
 *
 *\param[in] void
 *
 *\return
 *         -   \ref CR_ENTRY_OK if OK.
 *         -   \ref GL_RESULT_TIMEOUT if timeout has occurred.
 *         -   \ref GL_KEY_CANCEL
 */
unsigned long Ui_PaymentDisplayMenu()
{
   unsigned long choice = 0;
   UI_IdleDispHdrFtrToggle(); // Turn off the manager's header and footer.
   do
   {
      choice = guiMenu(mnuTypeDialog, choice, "Payment", gMenuUserPaymentArray);
   } while ((choice != 0) && (choice != 1) && (choice != 2) && (choice != GL_KEY_CANCEL) && (choice != GL_RESULT_TIMEOUT));

   UI_IdleDispHdrFtrToggle(); // Restore the initial state of manager's header and footer
   return choice;
}
/** Display Payment support menu (CHIP_SUPPORT/TRACK2_SUPPORT/UNKNOWN_SUPPORT).
 *
 *\param[in] void
 *
 *\return
 *         -   \ref CR_ENTRY_OK if OK.
 *         -   \ref GL_RESULT_TIMEOUT if timeout has occurred.
 *         -   \ref GL_KEY_CANCEL
 */
unsigned long Ui_SupportDisplayMenu()
{

   unsigned long choice = 0;
   UI_IdleDispHdrFtrToggle(); // Turn off the manager's header and footer.
   do
   {
      choice = guiMenu(mnuTypeDialog, choice, "SUPPORT", gMenuUserSupportArray);
   } while ((choice != 0) && (choice != 1) && (choice != 2) && (choice != 3) && (choice != GL_KEY_CANCEL) && (choice != GL_RESULT_TIMEOUT));

   UI_IdleDispHdrFtrToggle(); // Restore the initial state of manager's header and footer

   return choice;
}
/** Display transaction Status after service 100 call.
 *
 *\param[in] unsigned char payment_Status.
 *
 */
void Ui_TransctionStatusMenu(unsigned char payment_status)
{
   if (payment_status == PAY_OK)
      guiScreen("Service 100", "Transaction OK\n", GL_ICON_NONE, 3000);
   else
      guiScreen("Service 100", "Transaction KO\n", GL_ICON_NONE, 3000);
}
/** Display Transaction type menu (DEBIT_TR/CANCEL_TR/CREDIT_TR/EXT_CANCEL_TR).
 *
 *\param[in] void
 *
 *\return
 *         -   \ref CR_ENTRY_OK if OK.
 *         -   \ref GL_RESULT_TIMEOUT if timeout has occurred.
 *         -   \ref GL_KEY_CANCEL
 */
unsigned long Ui_TypeDisplayMenu()
{
   unsigned long choice = 0;
   UI_IdleDispHdrFtrToggle(); // Turn off the manager's header and footer.
   do
   {
      choice = guiMenu(mnuTypeDialog, choice, "TRANSACTION", gMenuUserTypeArray);
   } while ((choice != 0) && (choice != 1) && (choice != 2) && (choice != 3) && (choice != GL_KEY_CANCEL) && (choice != GL_RESULT_TIMEOUT));

   UI_IdleDispHdrFtrToggle(); // Restore the initial state of manager's header and footer

   return choice;
}

#ifdef __cplusplus
}
#endif

