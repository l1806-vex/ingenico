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
   
 Project : Card Entry Sample
 Module  : UI - User Interface Unit

 @file      uiPrompt.h
 @brief     Contains all prototypes for user interfaces related to prompt
            messages.
            
 @date      02/14/2013

 ------------------------------------------------------------------------------
 */

#ifndef __UI_PROMPT_H__
#define __UI_PROMPT_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "ui_userinterface.h"

/** \addtogroup uigroup
 * @{
 */

/** \weakgroup uiprompt UI Prompt
 * @{
 */

/** Displays a prompt.
 *
 * \param[in] id The identifier of the prompt to be displayed.
 */
void UI_PromptDisplay(UI_PromptIdx_t id);

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif // __UI_PROMPT_H__

