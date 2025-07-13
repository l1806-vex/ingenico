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
   
 Project : SSL Sample
 Module  : UIU - User Interface Unit

 @file      uiu_prompt.c
 @brief     Contains definitions of APIs specific to prompt messages.
            
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "sdk30.h"
#include <GL_GraphicLib.h>

#include "Utilities.h"
#include "uiu_userinterface.h"
#include "uiu_prompt.h"
#include "uiu_message.h"

/** Prompt message structure
 */
typedef struct
{
    UIU_PromptIdx_t promptID; ///< Prompt ID as defined in UIU_PromptIdx_t.
    UIU_MsgID_t title; ///< Index of the string in the message list to appear as title of the message dialog.
    UIU_MsgID_t promptMsg; ///< Index of the string in the message list to appear as prompt message of the message dialog.
    int timeout; ///< Duration in milliseccnds for the prompt message to be displayed
    struct options_s 
    {
        unsigned long buttonOptions:1; ///< Flag if CANCEL button/key to be used. 1 is ENABLED, 0 is DISABLED
        unsigned long buttonEnter:1; ///< Flag if ENTER button/key to be used.  1 is ENABLED, 0 is DISABLED
        unsigned long RFU:30;
        T_GL_DIALOG_ICON icon; ///< Type of GOAL icon to display. See T_GL_DIALOG_ICON of GOAL documentation.
    }options;
}_UIU_Prompt_t;

static _UIU_Prompt_t *_UIU_PromptGet(int promptID);


#define _UIU_PROMPT_OPTION_CANCEL_BUTTON_ENABLED 1
#define _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED 0
#define _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED 1
#define _UIU_PROMPT_OPTION_ENTER_BUTTON_DISABLED 0
#define _UIU_PROMPT_OPTION_ICON_ERROR   GL_ICON_ERROR
#define _UIU_PROMPT_OPTION_ICON_WARNING   GL_ICON_WARNING
#define _UIU_PROMPT_OPTION_ICON_INFORMATION   GL_ICON_INFORMATION
#define _UIU_PROMPT_OPTION_ICON_QUESTION   GL_ICON_QUESTION
#define _UIU_PROMPT_OPTION_ICON_NONE   GL_ICON_NONE


const _UIU_Prompt_t uiuPromptList[] = 
    {
        {//< Invalid Port Number Error Message
            UIU_PROMPT_MSG_ERR_INVALID_PORT_NUM,
            UIU_MSG_PORT_NUM_ENTRY,
            UIU_MSG_INVALID_INPUT,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },

        {//< Undefined Error prompt
            UIU_PROMPT_MSG_ERR_UNDEFINED_ERROR,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_UNDEFINED_ERROR,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_SSL_INVALID_ARGUMENT,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_INVALID_ARGUMENT,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_SSL_OUT_OF_RES,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_OUT_OF_RESOURCES,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_SSL_NO_SUCH_FILE_DIR,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_NO_SUCH_FILE_OR_DIR,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_SSL_INSUFFICIENT_MEM,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_INSUFFICIENT_MEMORY,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_SSL_SOCKET_NOT_CONNECTED,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_SOCKET_NOT_CONNECTED,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_SSL_GENERAL_ERROR,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_GENERAL_ERROR,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_SSL_BAD_CERT_FORMAT,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_BAD_CERTIFICATE_FORMAT,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_SSL_CONNECTION_CLOSED,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_CONNECTION_CLOSED,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_CONNECTION_FAILED,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_CONNECTION_FAILED,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_PROFILE_CREATION_FAILED,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_PROFILE_CREATION_FAILED,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_PROFILE_DELETION_FAILED,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_PROFILE_DELETION_FAILED,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_SSL_NO_PROFILES_FOUND,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_NO_PROFILE_FOUND,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_SSL_PROFILE_NOT_FOUND,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_PROFILE_NOT_FOUND,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_ERR_SSL_CERTS_KEYS_NOT_LOADED,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_SSL_CERT_KEYS_NOT_LOADED,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        {//< 
            UIU_PROMPT_MSG_STAT_DELETING_PROFILE,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_DELETING_PROFILE,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< 
            UIU_PROMPT_MSG_STAT_PROFILE_DELETION_OK,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_PROFILE_DELETION_OK,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< 
            UIU_PROMPT_MSG_STAT_PRINTING_PROFILE,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_PRINTING_PROFILES,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< 
            UIU_PROMPT_MSG_STAT_CREATING_PROFILE,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_CREATING_PROFILE,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< 
            UIU_PROMPT_MSG_STAT_PROFILE_CREATION_OK,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_PROFILE_CREATION_SUCCESSFUL,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< 
            UIU_PROMPT_MSG_STAT_LOADING_SSL_PROFILE,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_LOADING_SSL_PROFILE,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< 
            UIU_PROMPT_MSG_STAT_CONNECTING_TO_SERVER,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_CONNECTING_TO_SERVER,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< 
            UIU_PROMPT_MSG_STAT_CONNECTION_OK,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_CONNECTION_OK,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< 
            UIU_PROMPT_MSG_STAT_DISCONNECTING_FROM_SERVER,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_DISCONNECTING_FROM_SERVER,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_NONE
            }
        },
        {//< 
            UIU_PROMPT_MSG_STAT_DISCONNECTED,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_DISCONNECTED,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_NONE
            }
        },


        {//< Undefined prompt message
            UIU_PROMPT_MSG_END,
            UIU_MSG_SSL_SAMPLE,
            UIU_MSG_UNDEFINED_PROMPT,
            UIU_TIMEOUT_3_SECONDS,
            {
                _UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                _UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                _UIU_PROMPT_OPTION_ICON_ERROR
            }
        }


    };

static _UIU_Prompt_t *_UIU_PromptGet(int promptID)
{
    int ctr;
    static _UIU_Prompt_t prompt;
    
    memset(&prompt, 0, sizeof(_UIU_Prompt_t));
    for(ctr = 0; ctr < sizeof(uiuPromptList)/sizeof(_UIU_Prompt_t) ; ctr++)
    {
        if(promptID == uiuPromptList[ctr].promptID)// Error message found
        {
            memcpy(&prompt,&uiuPromptList[ctr], sizeof(_UIU_Prompt_t));
            return &prompt;
        }
    }

    // Undefined Prompt
    memcpy(&prompt,&uiuPromptList[ctr-1], sizeof(_UIU_Prompt_t));

    return &prompt;
}

void UIU_PromptDisplay(UIU_PromptIdx_t id)
{
    _UIU_Prompt_t *prompt = NULL;
    char* title = NULL;
    char* promptMsg = NULL;

    prompt = _UIU_PromptGet(id);
    title = _UIU_MsgStrGet(prompt->title);
    promptMsg = _UIU_MsgStrGet(prompt->promptMsg);

    guiScreen(title, promptMsg, prompt->options.icon, prompt->timeout);
}


#ifdef __cplusplus
}
#endif


