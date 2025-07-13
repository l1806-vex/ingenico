/**
 * \file
 * \brief Header file of the users interface for the Sample of Easy Path to Contactless.
 *
 * \author  Ingenico
 *
 * \author  Ingenico has intellectual property rights relating to the technology embodied \n
 *       in this software. In particular, and without limitation, these intellectual property rights may\n
 *       include one or more patents.\n
 *       This software is distributed under licenses restricting its use, copying, distribution, and\n
 *       and decompilation. No part of this software may be reproduced in any form by any means\n
 *       without prior written authorization of Ingenico.
 */

#ifndef APCLESS_GUI_H_INCLUDED
#define APCLESS_GUI_H_INCLUDED

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

// Screen definitions
//#define APCLESS_SCREEN_IDLE                              (1)         ///<
//#define APCLESS_SCREEN_PRESENT_CARD                      (2)         ///<
#define APCLESS_SCREEN_RETRY                             (3)         ///<
#define APCLESS_SCREEN_USE_CONTACT                       (4)         ///<
#define APCLESS_SCREEN_REMOVE_CARD                       (5)         ///<
#define APCLESS_SCREEN_WAIT_CARD_REMOVAL                 (6)         ///<
#define APCLESS_SCREEN_TIMEOUT_ELAPSED                   (7)         ///<
#define APCLESS_SCREEN_CANCELLED                         (8)         ///<
#define APCLESS_SCREEN_PROCESSING                        (9)         ///<
#define APCLESS_SCREEN_COLLISION                         (10)        ///<
#define APCLESS_SCREEN_ONLINE_APPROVED                   (11)        ///<
#define APCLESS_SCREEN_ONLINE_PIN_REQUIRED               (12)        ///<
#define APCLESS_SCREEN_SIGNATURE_REQUIRED                (13)        ///<
#define APCLESS_SCREEN_ERROR                             (14)        ///<
#define APCLESS_SCREEN_CARD_BLOCKED                      (15)        ///<
#define APCLESS_SCREEN_APPLICATION_BLOCKED               (16)        ///<
#define APCLESS_SCREEN_OFFLINE_APPROVED                  (17)        ///<
#define APCLESS_SCREEN_OFFLINE_DECLINED                  (18)        ///<
#define APCLESS_SCREEN_ONLINE_PROCESSING                 (19)        ///<
#define APCLESS_SCREEN_ONLINE_DECLINED                   (20)        ///<
#define APCLESS_SCREEN_PIN_CANCEL                        (21)        ///<
#define APCLESS_SCREEN_PIN_ERROR                         (22)        ///<
//#define APCLESS_SCREEN_ERASE_CUSTOMER                    (23)        ///<
//#define APCLESS_SCREEN_USER                              (24)        ///<
//#define APCLESS_SCREEN_KEYBOARD                          (25)        ///<
#define APCLESS_SCREEN_ERROR_STATUS                      (26)        ///<
//#define APCLESS_SCREEN_BATCH_ERROR                       (27)        ///<
#define APCLESS_SCREEN_REPRESENT_CARD                    (28)        ///<
#define APCLESS_SCREEN_ONLINE_UNABLE                     (29)        ///<
#define APCLESS_SCREEN_TRY_ANOTHER_CARD                  (31)        ///<
#define APCLESS_SCREEN_PHONE_INSTRUCTIONS                (32)        ///<
#define APCLESS_SCREEN_PHONE_INSTRUCTIONS_RETRY          (33)        ///<

#define APCLESS_PAYPASS_SCREEN_SIGNATURE_REQUIRED         (63)        ///<
#define APCLESS_PAYPASS_SCREEN_OFFLINE_APPROVED_REFUND    (66)        ///<
#define APCLESS_PAYPASS_SCREEN_ERROR_REFUND               (67)        ///<
#define APCLESS_PAYPASS_SCREEN_APPROVED                   (68)        ///<
#define APCLESS_PAYPASS_SCREEN_SIGNATURE_OK               (69)        ///<
#define APCLESS_PAYPASS_SCREEN_SIGNATURE_KO               (70)        ///<
#define APCLESS_PAYPASS_SCREEN_AUTHORISING                (71)        ///<
#define APCLESS_PAYPASS_SCREEN_DECLINED                   (72)        ///<
#define APCLESS_PAYPASS_SCREEN_PHONE_INSTRUCTIONS         (73)        ///<
#define APCLESS_PAYPASS_SCREEN_WAIT_CARD_REMOVAL          (75)        ///<

#define APCLESS_SCREEN_CARD_NOT_SUPPORTED                 (131)       ///<
#define APCLESS_SCREEN_EMPTY                              (133)       ///<
#define APCLESS_SCREEN_WAIT_END_DISPLAY                   (134)       ///<  Wait the end of the display hold time (only useful for the last display before returning to the manager)

/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

void APCLESS_Gui_Init(void);

int APCLESS_Gui_Menu( const char *title, int defaultItem, const char* Items[]);
void APCLESS_Gui_Display_Error_No_TPass(void);

void APCLESS_Gui_PresentCard(const char* currencyLabel, unsigned int currencyExp, const unsigned char* amountBcd, unsigned int amountLength);
void APCLESS_Gui_IndicatorIdle(void);
void APCLESS_Gui_IndicatorWait(void);
void APCLESS_Gui_IndicatorAlert(void);
void APCLESS_Gui_IndicatorNotReady(void);
void APCLESS_Gui_DisplayScreen(unsigned long screenIdentifier);
void APCLESS_Gui_DisplayScreenWithBalance(unsigned long screenId, const char* currencyLabel, unsigned int currencyExp, const unsigned char* amountBcd, unsigned int amountLength);

#endif //SPEC_GUI_H_INCLUDED
