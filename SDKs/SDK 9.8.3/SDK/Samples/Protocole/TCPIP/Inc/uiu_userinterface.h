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
   
 Project : TCP/IP Sample
 Module  : UIU - User Interface Unit

 @file      uiu_userinterface.h
 @brief     Contains all prototypes that handle user interfaces such as display
            of menus, display of error messages,display of user input dialogs, 
            and so on. This unit interfaces functions that are interfacing low 
            level functions to get data from different peripherals of the 
            terminal such as display, keyboard, and other related peripherals.
            
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifndef __UIU_H__
#define __UIU_H__

#include "uiu_prompt.h"

/** \addtogroup uiugroup UIU User Interface Unit
 *
 * Contains all functions that handle user interfaces such as display of menus, 
 * display of error messages, display of user input dialogs, and so on. 
 * This unit interfaces functions that are interfacing low level functions to get
 * data from different peripherals of the terminal such as display, keyboard, and 
 * other related peripherals.
 *
 * @{
 */

/** \weakgroup uiumain UIU Main
 * 
 * Functions in charge of peripheral management in the terminal.
 *
 * @{
 */

#define UIU_TIMEOUT_100_MILLISECONDS         100 ///< 100 milliseconds timeout delay used for GUI dialogs
#define UIU_TIMEOUT_3_SECONDS               3000 ///< 3-second timeout delay used for GUI dialogs
#define UIU_TIMEOUT_5_SECONDS               5000 ///< 5-second timeout delay used for GUI dialogs


/** Displays the menu of the sample application.
 */
void UIU_MenuDisplay( void );

/** Toggles the idle display's header/footer.
 * It makes sure that the header and footer are turned off. It will restore the
 * original state of the header/footer display when called the second time.
 */
void UIU_IdleDispHdrFtrToggle( void );

/** Displays an error message.
 *
 * \pre The given error code should have been defined first. Only those defined in epu_errprocess.h.
 *
 * \param   errID   The error code defined in epu_errprocess.h. See \ref epuerrorid "Error Identifiers"
 *
 * \return None
 *  
 */
void UIU_ErrMsgDisplay(int errID);

/** Displays a prompt message.
 */
void UIU_PromptMsgDisplay(UIU_PromptIdx_t promptID);
/** @} */
/** @} */
#endif // __UIU_H__

