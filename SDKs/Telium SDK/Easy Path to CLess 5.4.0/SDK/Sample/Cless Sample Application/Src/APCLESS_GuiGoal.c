/**
 * \file
 * This file implements the Graphical User Interface of the Easy Path to Contactless Sample using Goal library.
 *
 * Note : This sample expects an iCT250 terminal using the internal contactless reader (no pinpad, no external display ...)
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
 *
 */

#include "SDK30.h"
#include "APCLESS.h"
#include "GL_GraphicLib.h"
#include "widgetMappings.h"

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define __BEEP_VOLUME          (255)     ///< Default beep volume
#define __BEEP_OK_FREQUENCY    (1500)    ///< Beep frequency for a success tone
#define __BEEP_ERROR_FREQUENCY (750)     ///< Beep frequency for an alert tone
#define __BEEP_OK_DELAY        (50)      ///< Success tone duration
#define __BEEP_ERROR_DELAY     (20)      ///< Alert tone duration


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

T_GL_HGRAPHIC_LIB __APCLESS_GuiGoal_libInstance = NULL;  ///< handle on GOAL context
T_GL_HWIDGET __APCLESS_GuiGoal_window = NULL;            ///< handle to the current window

static unsigned int __APCLESS_GuiGoal_holdTime = 0;                ///< Minimum time to display a screen (in ticks)
static unsigned long __APCLESS_GuiGoal_startTime = 0;              ///< Start time of the hold time period (in ticks)

/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static void __APCLESS_GuiGoal_DisplayText(const char* line1, const char* line2, const char* line3, const char* line4);
static void __APCLESS_GuiGoal_RemoveCard(void);
static void __APCLESS_GuiGoal_SetHoldTime(unsigned int holdTime);
static void __APCLESS_GuiGoal_StartHoldTime(void);
static void __APCLESS_GuiGoal_WaitHoldTime(void);
static void __APCLESS_GuiGoal_BcdAmountToStr(const char* currencyLabel, unsigned int currencyExp, const unsigned char* amountBcd, unsigned int amountLength, char* amountStr);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


/**
 * Erase the screen and display 4 lines.
 * A line is an ASCII string terminated with zero.
 * @param line1 text of line 1 or NULL
 * @param line2 text of line 2 or NULL
 * @param line3 text of line 3 or NULL
 * @param line4 text of line 4 or NULL
 */
static void __APCLESS_GuiGoal_DisplayText(const char* line1, const char* line2, const char* line3, const char* line4)
{
   char szBuff[4*(16+2)+1];  // 4*(16 char + CR LF) + zero
   const char* pL1 = "";
   const char* pL2 = "";
   const char* pL3 = "";
   const char* pL4 = "";

   if(line1) pL1 = line1;
   if(line2) pL2 = line2;
   if(line3) pL3 = line3;
   if(line4) pL4 = line4;

   sprintf(szBuff, "%.16s\n%.16s\n%.16s\n%.16s\n", pL1, pL2, pL3, pL4);

   // Instantiates the goal resource screen using the resource file
   if(__APCLESS_GuiGoal_window != NULL)
   {  // Destroy the previous window
      GL_Widget_Destroy(__APCLESS_GuiGoal_window);
      __APCLESS_GuiGoal_window = NULL;
   }
   __APCLESS_GuiGoal_window = GL_GraphicLib_ReadResource(__APCLESS_GuiGoal_libInstance, "dal://APCLESSGuiText");

   if(__APCLESS_GuiGoal_window != NULL)
   {
      GL_Widget_SetTextById(__APCLESS_GuiGoal_window, ID_LABEL, szBuff);
      GL_Window_Dispatch(__APCLESS_GuiGoal_window, 1);
   }
   else
   {
      GL_Dialog_Message(__APCLESS_GuiGoal_libInstance, NULL, "Graphic resource\nnot found", GL_ICON_ERROR, GL_BUTTON_NONE, 2 * GL_TIME_SECOND);
   }

}


/**
 * Initialise the Graphical User Interface, (to be called once, in after reset).
 */
void APCLESS_Gui_Init(void)
{
   if(__APCLESS_GuiGoal_libInstance == NULL)
   {
      __APCLESS_GuiGoal_libInstance = GL_GraphicLib_Create();
   }
}


/**
 * Display a list of items and wait the user selection.
 * A timeout of 1 minute is set.
 * @param[in] title title of the message box (or null if no title).
 * @param[in] defaultItem item number that has the focus.
 * @param[in] items menu items (array of strings, WARNING : THE LAST IN THE LIST MUST ALWAYS BE A NULL POINTER).
 * @return
 *    - selected item number (starts from 0).
 *    - -1 if cancel key pressed, timeout or error.
 */
int APCLESS_Gui_Menu( const char* title, int defaultItem, const char* items[])
{
   int ret = -1;
   int oldHeader, oldFooter;

   FILE* keyboard = NULL;
   FILE* touch = NULL;

   // Open keyboard & touch driver
   keyboard = fopen("KEYBOARD", "r*");
   touch = fopen("TSCREEN", "r*");
   if(keyboard != NULL)
   {
      // Backup screen header and footer state and remove them
      oldHeader=DisplayHeader(_OFF_);
      oldFooter=DisplayFooter(_OFF_);

      ret = GL_Dialog_Menu(__APCLESS_GuiGoal_libInstance, title, items, defaultItem,
            GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);

      if (ret >= GL_KEY_CONTROL_BEGIN)  // case GL_KEY_CANCEL, GL_KEY_CORRECTION, GL_RESULT_INACTIVITY
         ret = -1;

      // close keyboard & touch
      fclose(touch);
      fclose(keyboard);

      // Restore screen header and footer
      DisplayHeader(oldHeader);
      DisplayFooter(oldFooter);
   }

   return ret;
}


/**
 * Display message "TPASS DLL NOT LOADED"
 */
void APCLESS_Gui_Display_Error_No_TPass(void)
{
   GL_Dialog_Message(__APCLESS_GuiGoal_libInstance, NULL, "TPASS DLL\n NOT LOADED", GL_ICON_ERROR, GL_BUTTON_NONE, 2* GL_TIME_SECOND);
}


/**
 * This function sets the indicators into the 'Idle' state
 * (first LED blinking 250ms every 5 seconds).
 */
void APCLESS_Gui_IndicatorIdle(void)
{
   // Turn off Leds 2, 3 and 4
   TPass_LedsOff(TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
   // Make the first Led blinking 200ms every 5 seconds
   TPass_LedsBlink(TPASS_LED_1, 10, 240);
}


/**
 * This function sets the indicators into the 'Ready to read' state
 * (first LED on, the three others off).
 */
void APCLESS_Gui_IndicatorWait(void)
{
   TPass_LedsOff(TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
   TPass_LedsOn(TPASS_LED_1);
}


/**
 * This function sets the indicators into the 'Processing error' state
 * (all the LEDs off, buzzer plays the Alert sequence).
 */
void APCLESS_Gui_IndicatorAlert(void)
{
   TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
   TPass_BuzzerBeep(__BEEP_ERROR_FREQUENCY, __BEEP_VOLUME, __BEEP_ERROR_DELAY);
   ttestall(0, __BEEP_ERROR_DELAY);
   TPass_BuzzerBeep(__BEEP_ERROR_FREQUENCY, __BEEP_VOLUME, __BEEP_ERROR_DELAY);
}


/**
 * This function sets the indicators into the 'Not ready' state
 * (all the LEDs off).
 */
void APCLESS_Gui_IndicatorNotReady(void)
{
   TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
}


/**
 * Display the "Present Card" screen with the contactless logo and the amount.
 * @param[in] currencyLabel transaction currency label (3 ASCII bytes) or NULL if no amount
 * @param[in] currencyExp transaction currency exponent
 * @param[in] amountBcd the transaction amount (in BCD and right align) or NULL if no amount
 * @param[in] amountLength length in bytes of \a amountBcd (should be <= 6)
 */
void APCLESS_Gui_PresentCard(const char* currencyLabel, unsigned int currencyExp, const unsigned char* amountBcd, unsigned int amountLength)
{
   char szAmount[32];

   // Format szAmount
   __APCLESS_GuiGoal_BcdAmountToStr(currencyLabel, currencyExp, amountBcd, amountLength, szAmount);

   // Wait end of the previous display (if not elapsed)
   // No need to the set a hold period as we are waiting the user to present the card.
   __APCLESS_GuiGoal_WaitHoldTime();


   // Instantiates the goal resource screen using the resource file
   if(__APCLESS_GuiGoal_window != NULL)
   {  // Destroy the previous window
      GL_Widget_Destroy(__APCLESS_GuiGoal_window);
      __APCLESS_GuiGoal_window = NULL;
   }
   __APCLESS_GuiGoal_window = GL_GraphicLib_ReadResource(__APCLESS_GuiGoal_libInstance, "dal://APCLESSGuiPresent");

   if(__APCLESS_GuiGoal_window != NULL)
   {
      GL_Widget_SetTextById(__APCLESS_GuiGoal_window, ID_LABEL_AMOUNT, szAmount);
      GL_Widget_SetTextById(__APCLESS_GuiGoal_window, ID_LABEL_PRESENT, "PRESENT CARD");

      // TODO: Center cless logo to the center of cless field.

      GL_Window_Dispatch(__APCLESS_GuiGoal_window, 1);

   }
   else
   {  // pb with resource, just display present card
      __APCLESS_GuiGoal_DisplayText(szAmount, 0, "PRESENT CARD", 0);
   }
}


/**
 * The screen displays "Remove Card" and the indicators are set into the
 * 'Card Read Successfully' state (LEDs and buzzer are playing the successful sequence).
 */
static void __APCLESS_GuiGoal_RemoveCard(void)
{
   int timeout;
   unsigned long startTime;

   // Turn on the buzzer for 500ms
   TPass_Buzzer(__BEEP_OK_FREQUENCY, __BEEP_VOLUME);
   startTime = GTL_StdTimer_GetCurrent();

   // Turn on the 2nd LED
   TPass_LedsOn(TPASS_LED_1 | TPASS_LED_2);
   __APCLESS_GuiGoal_DisplayText(0, "PLEASE REMOVE", "CARD OR DEVICE", 0);

   // Wait 125 ms before turning on LED 3
   timeout = GTL_StdTimer_GetRemaining(startTime, 12);
   if(timeout > 0)
   {
      ttestall(0, timeout);
   }

   // Turn on third LED
   TPass_LedsOn(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3);
   ttestall(0, 13);

   // Turn on fourth LED
   TPass_LedsOn(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);

   // Turn off beep after 500ms
   timeout = GTL_StdTimer_GetRemaining(startTime, 50);
   if(timeout > 0)
   {
      ttestall(0, timeout);
   }
   TPass_Buzzer(0, 0);

   //Turn off the leds after 750ms
   ttestall(0, 25);
   TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
}


/**
 * Wait the end of the (previous) hold time period.
 */
static void __APCLESS_GuiGoal_WaitHoldTime(void)
{
   int timeout;

   // Before Displaying a message, verify that the previous display hold time is elapsed, or wait if not.
   if(__APCLESS_GuiGoal_holdTime != 0)
   {
      timeout = GTL_StdTimer_GetRemaining(__APCLESS_GuiGoal_startTime, __APCLESS_GuiGoal_holdTime);
      if(timeout > 0)
      {
         ttestall(0, timeout);
      }
   }

   // Reset hold time
   __APCLESS_GuiGoal_holdTime = 0;
}


/**
 * Set the (minimum) hold time of the display.
 * @param[in] holdTime hold time in ticks
 */
static void __APCLESS_GuiGoal_SetHoldTime(unsigned int holdTime)
{
   __APCLESS_GuiGoal_holdTime = holdTime;
}


/**
 * Start a new hold time period.
 */
static void __APCLESS_GuiGoal_StartHoldTime(void)
{
   __APCLESS_GuiGoal_startTime = GTL_StdTimer_GetCurrent();
}


/**
 * Format a string with the transaction amount  ex: "EUR 12.34".
 * @param[in] currencyLabel transaction currency label (3 ASCII bytes) or NULL if no amount
 * @param[in] currencyExp transaction currency exponent
 * @param[in] amountBcd the transaction amount (in BCD and right align) or NULL if no amount
 * @param[in] amountLength length in bytes of \a amountBcd (should be <= 6)
 * @param[out] amountStr the amount string (zero terminated, should be large enough to receive the formatted string)
 */
static void __APCLESS_GuiGoal_BcdAmountToStr(const char* currencyLabel, unsigned int currencyExp, const unsigned char* amountBcd, unsigned int amountLength, char* amountStr)
{
    char str[16];
    char* ptr;
    int index;
    int len;

   if (amountStr == NULL)
      return;

   if ((amountBcd == NULL) || (amountLength == 0) || (amountLength > 6) || (currencyLabel == NULL))
   {
      *amountStr = 0; // String end...
      return;
   }

    ptr = str;
    len = amountLength*2;
    GTL_Convert_DcbNumberToAscii(amountBcd, str, amountLength, len);

    // remove the leading zeros
    index = 0;
    while ((str[index] == '0') && (index < len))
      index++;
    ptr = str + index;
    len-= index;

    // Put Currency
    if(currencyLabel != NULL)
    {
       strcpy(amountStr, currencyLabel);
       strcat(amountStr, " ");
    }

    // Put the integer part of the amount
    if(len > currencyExp)
       strncat(amountStr, ptr, len - currencyExp);
    else    // amount is less than 1
       strcat(amountStr, "0");

    strcat(amountStr, ".");

    // Put the remaining part
    if(len >= currencyExp)
    {
       strncat(amountStr, &ptr[len-currencyExp], currencyExp);
    }
    else    // amount is less than 1
    {
       strncat(amountStr, "000000000000", currencyExp-len );
       strncat(amountStr, ptr, len);
    }
}


/**
 * This function displays a screen and, if necessary, updates the indicators.
 * @param[in] screenId screen identifier.
 */
void APCLESS_Gui_DisplayScreen(unsigned long screenId)
{

   // Wait end of the previous display (if not elapsed)
   __APCLESS_GuiGoal_WaitHoldTime();

   // Set Default Hold Time for this new screen, and start the hold period
   __APCLESS_GuiGoal_SetHoldTime(2*100);   // 2s by default
   __APCLESS_GuiGoal_StartHoldTime();

   // Display the screen
   switch (screenId)
   {
      case APCLESS_SCREEN_RETRY:
         __APCLESS_GuiGoal_DisplayText(0, "TRY AGAIN", 0, 0);
         APCLESS_Gui_IndicatorAlert();
         break;

      case APCLESS_SCREEN_REMOVE_CARD:
         __APCLESS_GuiGoal_RemoveCard();
         break;

      case APCLESS_SCREEN_CANCELLED:
         __APCLESS_GuiGoal_DisplayText(0, "CANCEL", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_COLLISION:
         __APCLESS_GuiGoal_DisplayText(0, "PLEASE PRESENT", "ONLY ONE CARD", 0);
         APCLESS_Gui_IndicatorAlert();
         break;

      case APCLESS_SCREEN_USE_CONTACT:
         __APCLESS_GuiGoal_DisplayText(0, "INSERT CARD", 0, 0);
         APCLESS_Gui_IndicatorAlert();
         break;

      case APCLESS_SCREEN_ERROR:
         __APCLESS_GuiGoal_DisplayText(0, "ERROR", 0, 0);
         APCLESS_Gui_IndicatorAlert();
         break;

      case APCLESS_SCREEN_CARD_BLOCKED:
         __APCLESS_GuiGoal_DisplayText(0, "CARD BLOCKED", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_APPLICATION_BLOCKED:
         __APCLESS_GuiGoal_DisplayText(0, "APPLICATION", "BLOCKED", 0);
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_OFFLINE_DECLINED:
         __APCLESS_GuiGoal_DisplayText(0, "DECLINED", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_OFFLINE_APPROVED:
         __APCLESS_GuiGoal_DisplayText(0, "APPROVED", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_ONLINE_PROCESSING:
         __APCLESS_GuiGoal_DisplayText(0, "ONLINE REQUEST", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_ONLINE_APPROVED:
         __APCLESS_GuiGoal_DisplayText(0, "ONLINE APPROVED", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_ONLINE_DECLINED:
         __APCLESS_GuiGoal_DisplayText(0, "ONLINE DECLINED", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_PIN_CANCEL:
         __APCLESS_GuiGoal_DisplayText(0, "DECLINED", 0, 0); // if merchant display : "INPUT PIN CANCELED"
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_PIN_ERROR:
         __APCLESS_GuiGoal_DisplayText(0, "DECLINED", 0, 0); // if merchant display : "ONLINE PIN" "FAILED"
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_ERROR_STATUS:
         __APCLESS_GuiGoal_DisplayText(0, "ERROR STATUS", 0, 0);
         APCLESS_Gui_IndicatorAlert();
         break;

      case APCLESS_SCREEN_REPRESENT_CARD:
         __APCLESS_GuiGoal_DisplayText(0, "REPRESENT CARD", 0, 0);
         break;

      case APCLESS_SCREEN_PHONE_INSTRUCTIONS:
      case APCLESS_SCREEN_PHONE_INSTRUCTIONS_RETRY:
         __APCLESS_GuiGoal_DisplayText(0, "SEE PHONE FOR", "INSTRUCTIONS", 0);
         APCLESS_Gui_IndicatorAlert();
         break;

      case APCLESS_SCREEN_CARD_NOT_SUPPORTED:
         __APCLESS_GuiGoal_DisplayText(0, "NOT SUPPORTED", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_EMPTY:
         __APCLESS_GuiGoal_DisplayText(0, 0, 0, 0);
         APCLESS_Gui_IndicatorNotReady();
         break;

      case APCLESS_SCREEN_WAIT_END_DISPLAY:   // Special case to wait end of the display (useful just before application returns back to the manger)
         // We have already wait the end of the previous display at the beginning of the function
         // just reset Hold Time to 0.
         __APCLESS_GuiGoal_SetHoldTime(0);
         break;


         //////////////////////////////
         // PAYPASS SPECIFIC SCREENS //
         //////////////////////////////

      case APCLESS_PAYPASS_SCREEN_SIGNATURE_REQUIRED:
         __APCLESS_GuiGoal_DisplayText(0, "SIGNATURE", "CHECKING", 0);
         APCLESS_Gui_IndicatorNotReady();
      break;

      case APCLESS_PAYPASS_SCREEN_SIGNATURE_OK:
         __APCLESS_GuiGoal_DisplayText(0, "SIGNATURE OK", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
      break;

      case APCLESS_PAYPASS_SCREEN_SIGNATURE_KO:
         __APCLESS_GuiGoal_DisplayText(0, "BAD SIGNATURE", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
      break;

      case APCLESS_PAYPASS_SCREEN_DECLINED:
         __APCLESS_GuiGoal_DisplayText(0, "TRANSACTION", "NOT AUTHORISED", 0);
         APCLESS_Gui_IndicatorAlert();
      break;

      case APCLESS_PAYPASS_SCREEN_PHONE_INSTRUCTIONS:
         // Special case when called from the PayPass kernel
         __APCLESS_GuiGoal_DisplayText(0, "SEE PHONE FOR", "INSTRUCTIONS", 0);
         __APCLESS_GuiGoal_SetHoldTime(0);
         APCLESS_Gui_IndicatorNotReady();
      break;

      case APCLESS_SCREEN_ONLINE_UNABLE:
         __APCLESS_GuiGoal_DisplayText(0, "DECLINED", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
      break;

      case APCLESS_PAYPASS_SCREEN_AUTHORISING:
         __APCLESS_GuiGoal_DisplayText(0, "AUTHORISING", "PLEASE WAIT", 0);
         APCLESS_Gui_IndicatorNotReady();
      break;

      case APCLESS_PAYPASS_SCREEN_APPROVED:
         __APCLESS_GuiGoal_DisplayText(0, "APPROVED", 0, 0);
         APCLESS_Gui_IndicatorNotReady();
      break;

      case APCLESS_PAYPASS_SCREEN_WAIT_CARD_REMOVAL: //rem : Appl sould call CLESS_DeselectCard() after
         __APCLESS_GuiGoal_DisplayText(0, "PLEASE REMOVE", "CARD OR DEVICE", 0);
         APCLESS_Gui_IndicatorNotReady();
         break;

      default:
         // Unexpected screen identifier
         ASSERT(FALSE); // in debug, make a break
      break;
   }

}


/**
 * Display a message with the Balance amount.
 * @param[in] screenId screen identifier
 * @param[in] currencyLabel transaction currency label (3 ASCII bytes) or NULL if no amount
 * @param[in] currencyExp transaction currency exponent
 * @param[in] amountBcd transaction amount (in BCD and right align) or NULL if no amount
 * @param[in] amountLength length in bytes of \a amountBcd (should be <= 6)
 */
void APCLESS_Gui_DisplayScreenWithBalance(unsigned long screenId, const char* currencyLabel, unsigned int currencyExp, const unsigned char* amountBcd, unsigned int amountLength)
{
   char balanceAmount[64];

   __APCLESS_GuiGoal_BcdAmountToStr(currencyLabel, currencyExp, amountBcd, amountLength, balanceAmount);

   // Wait end of the previous display (if not elapsed)
   __APCLESS_GuiGoal_WaitHoldTime();

   // Set Default Hold Time for this new screen, and start the hold period
   __APCLESS_GuiGoal_SetHoldTime(2*100);   // 2s by default
   __APCLESS_GuiGoal_StartHoldTime();

   switch (screenId)
   {
      case APCLESS_SCREEN_OFFLINE_APPROVED:
      case APCLESS_PAYPASS_SCREEN_APPROVED:
         __APCLESS_GuiGoal_DisplayText("AVAILABLE:", balanceAmount, "APPROVED", 0);
         APCLESS_Gui_IndicatorNotReady();
      break;

      case APCLESS_SCREEN_OFFLINE_DECLINED:
         __APCLESS_GuiGoal_DisplayText("AVAILABLE:", balanceAmount, "DECLINED", 0);
         APCLESS_Gui_IndicatorNotReady();
      break;

      default:
         // Unexpected screen identifier
         ASSERT(FALSE);  // in debug,  make a break
      break;
   }
}


