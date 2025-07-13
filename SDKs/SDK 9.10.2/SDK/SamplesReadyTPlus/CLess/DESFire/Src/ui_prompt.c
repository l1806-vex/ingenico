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
   
 Project : Desfire Sample
 Module  : UI - User Interface Unit

 @file      ui_prompt.c
 @brief     Contains definitions of APIs specific to prompt messages.
            
 @date      21/03/2013

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "sdk30.h"
#include <GL_GraphicLib.h>

#include "Utilities.h"
#include "ui_userinterface.h"
#include "ui_prompt.h"
#include "ui_message.h"

/** Prompt message structure
 */
typedef struct
{
    UI_PromptIdx_t promptID; ///< Prompt ID as defined in UI_PromptIdx_t.
    UI_MsgID_t title; ///< Index of the string in the message list to appear as title of the message dialog.
    UI_MsgID_t promptMsg; ///< Index of the string in the message list to appear as prompt message of the message dialog.
    int timeout; ///< Duration in milliseccnds for the prompt message to be displayed
    struct options_s 
    {
        unsigned long buttonOptions:1; ///< Flag if CANCEL button/key to be used. 1 is ENABLED, 0 is DISABLED
        unsigned long buttonEnter:1; ///< Flag if ENTER button/key to be used.  1 is ENABLED, 0 is DISABLED
        unsigned long RFU:30;
        T_GL_DIALOG_ICON icon; ///< Type of GOAL icon to display. See T_GL_DIALOG_ICON of GOAL documentation.
    }options;
}_UI_Prompt_t;

static _UI_Prompt_t *_UI_PromptGet(int promptID);


#define _UI_PROMPT_OPTION_CANCEL_BUTTON_ENABLED 1
#define _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED 0
#define _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED 1
#define _UI_PROMPT_OPTION_ENTER_BUTTON_DISABLED 0
#define _UI_PROMPT_OPTION_ICON_ERROR   GL_ICON_ERROR
#define _UI_PROMPT_OPTION_ICON_WARNING   GL_ICON_WARNING
#define _UI_PROMPT_OPTION_ICON_INFORMATION   GL_ICON_INFORMATION
#define _UI_PROMPT_OPTION_ICON_QUESTION   GL_ICON_QUESTION
#define _UI_PROMPT_OPTION_ICON_NONE   GL_ICON_NONE


const _UI_Prompt_t uiPromptList[] = 
    {
        {//< Undefined Error prompt
            UI_PROMPT_MSG_ERR_UNDEFINED_ERROR,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_UNDEFINED_ERROR,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Invalid Port Number Error Message
            UI_PROMPT_MSG_PAR_FILE_NOT_FOUND,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_PAR_FILE_NOT_FOUND,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Telim Pass not connected
            UI_PROMPT_MSG_TPASS_NOT_CONNECTED,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_TPASS_NOT_CONNECTED,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Opening of cless driver failed
            UI_PROMPT_MSG_OPEN_DRIVER_FAILED,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_OPEN_DRIVER_FAILED,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< No card detected
            UI_PROMPT_MSG_NO_CARD_DETECTED,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_NO_CARD_DETECTED,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Too many cards detected
            UI_PROMPT_MSG_TOO_MANY_CARDS,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_TOO_MANY_CARDS,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Invalid card detected
            UI_PROMPT_MSG_INVALID_CARD,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_INVALID_CARD,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Detection error
            UI_PROMPT_MSG_DETECTION_ERROR,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_DETECTION_ERROR,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Timeout
            UI_PROMPT_MSG_TIMEOUT,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_TIMEOUT,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Detected card is not mifare
            UI_PROMPT_MSG_NOT_MIFARE_CARD,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_NOT_MIFARE_CARD,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< A desfire error occured
            UI_PROMPT_MSG_DESFIRE_ERROR,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_DESFIRE_ERROR,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Access Denied
            UI_PROMPT_MSG_ACCESS_DENIED,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_ACCESS_DENIED,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Invalid Data
            UI_PROMPT_MSG_INVALID_DATA,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_INVALID_DATA,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Invalid Data Length
            UI_PROMPT_MSG_INVALID_DATA_LEN,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_INVALID_DATA_LEN,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Processing
            UI_PROMPT_MSG_PROCESSING,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_PROCESSING,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_INFORMATION
            }
        },
        {//< Tap Card
            UI_PROMPT_MSG_TAP_CARD,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_TAP_CARD,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_INFORMATION
            }
        },
        {//< Test OK
            UI_PROMPT_MSG_TEST_OK,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_TEST_OK,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_INFORMATION
            }
        },
        {//< Test Failed
            UI_PROMPT_MSG_TEST_FAILED,
            UI_MSG_DESFIRE_SAMPLE,
            UI_MSG_TEST_FAILED,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UI_PROMPT_MSG_END,
            UI_MSG_UNDEFINED_PROMPT,
            UI_MSG_UNDEFINED_PROMPT,
            UI_TIMEOUT_3_SECONDS,
            {
                _UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UI_PROMPT_OPTION_ICON_ERROR
            }
        },
    };

static _UI_Prompt_t *_UI_PromptGet(int promptID)
{
    int ctr;
    static _UI_Prompt_t prompt;
    
    memset(&prompt, 0, sizeof(_UI_Prompt_t));
    for(ctr = 0; ctr < sizeof(uiPromptList)/sizeof(_UI_Prompt_t) ; ctr++)
    {
        if(promptID == uiPromptList[ctr].promptID)// Error message found
        {
            memcpy(&prompt,&uiPromptList[ctr], sizeof(_UI_Prompt_t));
            return &prompt;
        }
    }

    // Undefined Prompt
    memcpy(&prompt,&uiPromptList[ctr-1], sizeof(_UI_Prompt_t));

    return &prompt;
}

void UI_PromptDisplay(UI_PromptIdx_t id)
{
    _UI_Prompt_t *prompt = NULL;
    char* title = NULL;
    char* promptMsg = NULL;

    prompt = _UI_PromptGet(id);
    title = _UI_MsgStrGet(prompt->title);
    promptMsg = _UI_MsgStrGet(prompt->promptMsg);

    guiScreen(title, promptMsg, prompt->options.icon, prompt->timeout);
}


#ifdef __cplusplus
}
#endif


