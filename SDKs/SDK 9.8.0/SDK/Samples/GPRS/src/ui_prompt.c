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

 @file      ui_prompt.c
 @brief     Contains definitions of APIs specific to prompt messages.
            
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "sdk30.h"
#include <GL_GraphicLib.h>

#include "Utilities.h"
#include "ui.h"
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

#define UI_PROMPT_OPTION_CANCEL_BUTTON_ENABLED 1
#define UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED 0
#define UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED 1
#define UI_PROMPT_OPTION_ENTER_BUTTON_DISABLED 0
#define UI_PROMPT_OPTION_ICON_ERROR   GL_ICON_ERROR
#define UI_PROMPT_OPTION_ICON_WARNING   GL_ICON_WARNING
#define UI_PROMPT_OPTION_ICON_INFORMATION   GL_ICON_INFORMATION
#define UI_PROMPT_OPTION_ICON_QUESTION   GL_ICON_QUESTION
#define UI_PROMPT_OPTION_ICON_NONE   GL_ICON_NONE

const _UI_Prompt_t uiuPromptList[] = 
    {
        {//< Undefined Error prompt
            UI_PROMPT_MSG_ERR_UNDEFINED_ERROR,
            UI_MSG_GPRS_SAMPLE,
            UI_MSG_ERROR_UNKNOWN,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Invalid Port Number Error Message
            UI_PROMPT_MSG_ERR_INVALID_PORT_NUM,
            UI_MSG_PORT_NUM_ENTRY,
            UI_MSG_INVALID_INPUT,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Invalid Port Number Error Message
            UI_PROMPT_MSG_ERR_INVALID_PORT_NUM,
            UI_MSG_PORT_NUM_ENTRY,
            UI_MSG_INVALID_INPUT,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< PPP Error Message
            UI_PROMPT_MSG_ERR_PPP,
            UI_MSG_ERROR,
            UI_MSG_PPP,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Already Connected Error Message
            UI_PROMPT_MSG_ERR_ALREADY_CONNECTED,
            UI_MSG_ERROR,
            UI_MSG_ALREADY_CONNECTED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< No GPRS Error Message
            UI_PROMPT_MSG_ERR_NO_GPRS,
            UI_MSG_ERROR,
            UI_MSG_NO_GPRS,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< No Sim Error Message
            UI_PROMPT_MSG_ERR_NO_SIM,
            UI_MSG_ERROR,
            UI_MSG_NO_SIM,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Sim Lock Error Message
            UI_PROMPT_MSG_ERR_SIM_LOCK,
            UI_MSG_ERROR,
            UI_MSG_SIM_LOCK,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< No PIN Error Message
            UI_PROMPT_MSG_ERR_NO_PIN,
            UI_MSG_ERROR,
            UI_MSG_NO_PIN,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Bad PIN Error Message
            UI_PROMPT_MSG_ERR_BAD_PIN,
            UI_MSG_ERROR,
            UI_MSG_BAD_PIN,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Fatal Error Message
            UI_PROMPT_MSG_ERR_FATAL,
            UI_MSG_ERROR,
            UI_MSG_FATAL,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Unknown Error Message
            UI_PROMPT_MSG_ERR_UNKNOWN,
            UI_MSG_ERROR,
            UI_MSG_UNKNOWN,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< GPRS Network Not Available Error Message
            UI_PROMPT_MSG_ERR_GPRS_NETWORK,
            UI_MSG_ERROR,
            UI_MSG_GPRS_NETWORK_NOT_AVAILABLE,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Enable GSM Error Message
            UI_PROMPT_MSG_ERR_GSM_ENABLE,
            UI_MSG_ERROR,
            UI_MSG_GSM_ENABLE,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< GSM Network Not Available Error Message
            UI_PROMPT_MSG_ERR_GSM_NETWORK,
            UI_MSG_ERROR,
            UI_MSG_GSM_NETWORK_NOT_AVAILABLE,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< IP Error Message
            UI_PROMPT_MSG_ERR_IP,
            UI_MSG_ERROR,
            UI_MSG_IP_ERR,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Send Error Message
            UI_PROMPT_MSG_ERR_SEND,
            UI_MSG_ERROR,
            UI_MSG_SEND_ERROR,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Receive Error Message
            UI_PROMPT_MSG_ERR_RECEIVE,
            UI_MSG_ERROR,
            UI_MSG_RECEIVE_ERROR,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Connecting Failed Error Message
            UI_PROMPT_MSG_ERR_CONNECTION_FAILED,
            UI_MSG_ERROR,
            UI_MSG_CONNECTION_FAILED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Timeout Error Message
            UI_PROMPT_MSG_ERR_NULL_POINTER,
            UI_MSG_ERROR,
            UI_MSG_NULL_POINTER,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Timeout Error Message
            UI_PROMPT_MSG_ERR_CONNECT_TIMEOUT,
            UI_MSG_ERROR,
            UI_MSG_TIMEOUT,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Timeout Error Message
            UI_PROMPT_MSG_ERR_AUTH_FAILED,
            UI_MSG_ERROR,
            UI_MSG_AUTH_FAILED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< Activated Status Prompt
            UI_PROMPT_MSG_STAT_GPRS_ACTIVATING,
            UI_MSG_GPRS_SAMPLE,
            UI_MSG_ACTIVATING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Activated Status Prompt
            UI_PROMPT_MSG_STAT_GPRS_ACTIVATED,
            UI_MSG_GPRS_SAMPLE,
            UI_MSG_ACTIVATED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Deactivated Status Prompt
            UI_PROMPT_MSG_STAT_GPRS_DEACTIVATING,
            UI_MSG_GPRS_SAMPLE,
            UI_MSG_DEACTIVATING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Deactivated Status Prompt
            UI_PROMPT_MSG_STAT_GPRS_DEACTIVATED,
            UI_MSG_GPRS_SAMPLE,
            UI_MSG_DEACTIVATED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Activated Status Prompt
            UI_PROMPT_MSG_STAT_GSM_ACTIVATING,
            UI_MSG_GSM_TEST,
            UI_MSG_ACTIVATING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Activated Status Prompt
            UI_PROMPT_MSG_STAT_GSM_ACTIVATED,
            UI_MSG_GSM_TEST,
            UI_MSG_ACTIVATED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Deactivated Status Prompt
            UI_PROMPT_MSG_STAT_GSM_DEACTIVATING,
            UI_MSG_GSM_TEST,
            UI_MSG_DEACTIVATING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Deactivated Status Prompt
            UI_PROMPT_MSG_STAT_GSM_DEACTIVATED,
            UI_MSG_GSM_TEST,
            UI_MSG_DEACTIVATED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Enable GPRS Status Prompt
            UI_PROMPT_MSG_STAT_ENABLED,
            UI_MSG_GPRS_SAMPLE,
            UI_MSG_ENABLED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Disable GPRS Status Prompt
            UI_PROMPT_MSG_STAT_DISABLED,
            UI_MSG_GPRS_SAMPLE,
            UI_MSG_DISABLED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Sending Status Prompt
            UI_PROMPT_MSG_STAT_GSM_SENDING,
            UI_MSG_GSM_TEST,
            UI_MSG_SENDING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Receiving Status Prompt
            UI_PROMPT_MSG_STAT_GSM_RECEIVING,
            UI_MSG_GSM_TEST,
            UI_MSG_RECEIVING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Sending Status Prompt
            UI_PROMPT_MSG_STAT_TCP_SENDING,
            UI_MSG_TCP_TEST,
            UI_MSG_SENDING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Receiving Status Prompt
            UI_PROMPT_MSG_STAT_TCP_RECEIVING,
            UI_MSG_TCP_TEST,
            UI_MSG_SENDING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Connecting Status Prompt
            UI_PROMPT_MSG_STAT_GSM_CONNECTING,
            UI_MSG_GSM_TEST,
            UI_MSG_CONNECTING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Connecting Status Prompt
            UI_PROMPT_MSG_STAT_GSM_CONNECTED,
            UI_MSG_GSM_TEST,
            UI_MSG_CONNECTION_OK,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Disconnecting Status Prompt
            UI_PROMPT_MSG_STAT_GSM_DISCONNECTING,
            UI_MSG_GSM_TEST,
            UI_MSG_DISCONNECTING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Disconnected Status Prompt
            UI_PROMPT_MSG_STAT_GSM_DISCONNECTED,
            UI_MSG_GSM_TEST,
            UI_MSG_DISCONNECTED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Connecting Status Prompt
            UI_PROMPT_MSG_STAT_PPP_CONNECTING,
            UI_MSG_PPP_TEST,
            UI_MSG_CONNECTING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Connecting Status Prompt
            UI_PROMPT_MSG_STAT_PPP_CONNECTED,
            UI_MSG_PPP_TEST,
            UI_MSG_CONNECTION_OK,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Disconnecting Status Prompt
            UI_PROMPT_MSG_STAT_PPP_DISCONNECTING,
            UI_MSG_PPP_TEST,
            UI_MSG_DISCONNECTING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Disconnected Status Prompt
            UI_PROMPT_MSG_STAT_PPP_DISCONNECTED,
            UI_MSG_PPP_TEST,
            UI_MSG_DISCONNECTED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Connecting Status Prompt
            UI_PROMPT_MSG_STAT_TCP_CONNECTING,
            UI_MSG_TCP_TEST,
            UI_MSG_CONNECTING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Connecting Status Prompt
            UI_PROMPT_MSG_STAT_TCP_CONNECTED,
            UI_MSG_TCP_TEST,
            UI_MSG_CONNECTION_OK,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Disconnecting Status Prompt
            UI_PROMPT_MSG_STAT_TCP_DISCONNECTING,
            UI_MSG_TCP_TEST,
            UI_MSG_DISCONNECTING,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Disconnected Status Prompt
            UI_PROMPT_MSG_STAT_TCP_DISCONNECTED,
            UI_MSG_TCP_TEST,
            UI_MSG_DISCONNECTED,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< Undefined prompt message
            UI_PROMPT_MSG_END,
            UI_MSG_GPRS_SAMPLE,
            UI_MSG_UNDEFINED_PROMPT,
            UI_TIMEOUT_3_SECONDS,
            {
                UI_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UI_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UI_PROMPT_OPTION_ICON_ERROR
            }
        }
    };

static _UI_Prompt_t *_UI_PromptGet(int promptID)
{
    int ctr;
    static _UI_Prompt_t prompt;
    
    memset(&prompt, 0, sizeof(_UI_Prompt_t));
    for(ctr = 0; ctr < sizeof(uiuPromptList)/sizeof(_UI_Prompt_t) ; ctr++)
    {
        if(promptID == uiuPromptList[ctr].promptID)// Error message found
        {
            memcpy(&prompt,&uiuPromptList[ctr], sizeof(_UI_Prompt_t));
            return &prompt;
        }
    }

    // Undefined Prompt
    memcpy(&prompt,&uiuPromptList[ctr-1], sizeof(_UI_Prompt_t));

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

