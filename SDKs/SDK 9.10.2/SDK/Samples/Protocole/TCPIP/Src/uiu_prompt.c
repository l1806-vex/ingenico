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

 @file      uiu_prompt.c
 @brief     Contains definitions of APIs specific to prompt messages.
            
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#include "sdk30.h"
#include <GL_GraphicLib.h>

#include "Utilities.h"
#include "uiu_userinterface.h"
#include "uiu_prompt.h"

#define UIU_PROMPT_OPTION_CANCEL_BUTTON_ENABLED 1
#define UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED 0
#define UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED 1
#define UIU_PROMPT_OPTION_ENTER_BUTTON_DISABLED 0
#define UIU_PROMPT_OPTION_ICON_ERROR   GL_ICON_ERROR
#define UIU_PROMPT_OPTION_ICON_WARNING   GL_ICON_WARNING
#define UIU_PROMPT_OPTION_ICON_INFORMATION   GL_ICON_INFORMATION
#define UIU_PROMPT_OPTION_ICON_QUESTION   GL_ICON_QUESTION
#define UIU_PROMPT_OPTION_ICON_NONE   GL_ICON_NONE

/** Message Database Structure
 */
typedef struct
{
    UIU_MsgIdx_t msgID;
    char *strMsg;
}UIU_StrMsg_t;

/** Prompt message structure
 */
typedef struct
{
    UIU_PromptIdx_t promptID; ///< Prompt ID as defined in UIU_PromptIdx_t.
    UIU_MsgIdx_t title; ///< Index of the string in the message list to appear as title of the message dialog.
    UIU_MsgIdx_t promptMsg; ///< Index of the string in the message list to appear as prompt message of the message dialog.
    int timeout; ///< Duration in milliseccnds for the prompt message to be displayed
    struct options_s 
    {
        unsigned long buttonOptions:1; ///< Flag if CANCEL button/key to be used. 1 is ENABLED, 0 is DISABLED
        unsigned long buttonEnter:1; ///< Flag if ENTER button/key to be used.  1 is ENABLED, 0 is DISABLED
        unsigned long RFU:30;
        T_GL_DIALOG_ICON icon; ///< Type of GOAL icon to display. See T_GL_DIALOG_ICON of GOAL documentation.
    }options;
}UIU_Prompt_t;


/** Define first the appropriate index in UIU_MsgIdx_t enumeration
 * before inserting a message here. It is located in UIU_Prompt.h
 */
const UIU_StrMsg_t uiuStrMsgList[] = 
    {
        {
            UIU_MSG_INVALID_INPUT,
            "Invalid Input\0"
        },
        {
            UIU_MSG_UNDEFINED_ERROR,
            "Undefined Error\0"
        },
        {
            UIU_MSG_CONNECTION_STATUS,
            "Connection Status\0",
        },
        {
            UIU_MSG_CONNECTING_TO_SERVER,
            "Connecting to server...\0"
        },
        {
            UIU_MSG_PORT_NUM_ENTRY,
            "Port Num Entry"
        },
        {
            UIU_MSG_UNDEFINED_PROMPT,
            "UNDEFINED PROMPT"
        },
        {
            UIU_MSG_UNDEFINED_ERROR,
            "UNDEFINED ERROR"
        },
        {
            UIU_MSG_CONNECTION_TO_SERVER_FAILED,
            "Connection to server failed..."
        },
        {
            UIU_MSG_SOCKET_FAILED,
            "Socket Creation Failed"
        },
        {
            UIU_MSG_CREATING_SOCKET,
            "Creating socket..."
        },
        {
            UIU_MSG_RESOLVING_DNS_NAME,
            "Resolving DNS Name..."
        },
        {
            UIU_MSG_CLIENT_TEST,
            "CLIENT TEST"
        },
        {
            UIU_MSG_SERVER_TEST,
            "SERVER TEST"
        },
        {
            UIU_MSG_SENDING,
            "Sending..."
        },
        {
            UIU_MSG_SENDING_FAILED,
            "Sending Failed."
        },
        {
            UIU_MSG_SHUTTING_DOWN_CONNECTION,
            "Shutting down connection..."
        },
        {
            UIU_MSG_TEST_RESULT,
            "TEST RESULT"
        },
        {
            UIU_MSG_OK,
            "OK"
        },
        {
            UIU_MSG_LAUNCHING_CLIENT_TEST,
            "Launching Client Test..."
        },
        {
            UIU_MSG_LAUNCHING_SERVER_TEST,
            "Launching Server Test..."
        },
        {
            UIU_MSG_BINDING_FAILED,
            "Binding failed!"
        },
        {
            UIU_MSG_LISTEN_FAILED,
            "Listen Failed!"
        },
        {
            UIU_MSG_LISTENING,
            "Listening..."
        },
        {
            UIU_MSG_CONNECTION_ACCEPTED,
            "Accepted connection!"
        },
        {
            UIU_MSG_RECEIVING,
            "Receiving..."
        },
        {
            UIU_MSG_ACCEPT_FAILED,
            "Accept Failed!"
        },
        {
            UIU_MSG_END, //< Undefined Message
            "Undefined Message ID\0",
        },
        
    };

const UIU_Prompt_t uiuPromptList[] = 
    {
        {//< Connection Status Prompt Message: Connecting to server...
            UIU_PROMPT_MSG_CON_STATUS_CONNECTING,
            UIU_MSG_CONNECTION_STATUS,
            UIU_MSG_CONNECTING_TO_SERVER,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },

        {//< Connection Status Prompt Message: Creating socket...
            UIU_PROMPT_MSG_CLIENT_TEST_CREATING_SOCKET,
            UIU_MSG_CONNECTION_STATUS,
            UIU_MSG_CREATING_SOCKET,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },

        {//< Connection Status Prompt Message: Resolving DNS Name...
            UIU_PROMPT_MSG_CON_STATUS_RESOLVING_DNS,
            UIU_MSG_CONNECTION_STATUS,
            UIU_MSG_RESOLVING_DNS_NAME,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },

        {//< Connection Status Error Prompt Message: Connection to Server Failed
            UIU_PROMPT_MSG_CLIENT_TEST_CON_STATUS_FAILED,
            UIU_MSG_CONNECTION_STATUS,
            UIU_MSG_CONNECTION_TO_SERVER_FAILED,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_ERROR
            }
        },

        {//< Client Test Sending Failed Error Prompt Message
            UIU_PROMPT_MSG_CLIENT_TEST_SEND_FAILED,
            UIU_MSG_CLIENT_TEST,
            UIU_MSG_SENDING_FAILED,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_ERROR
            }
        },

        {//< Client Test socket creation failed Prompt Message
            UIU_PROMPT_MSG_CLIENT_TEST_SOCKET_FAILED,
            UIU_MSG_CLIENT_TEST,
            UIU_MSG_SOCKET_FAILED,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_ERROR
            }
        },

        {//< Server test scoket creation failed Prompt Message
            UIU_PROMPT_MSG_SERVER_TEST_SOCKET_FAILED,
            UIU_MSG_SERVER_TEST,
            UIU_MSG_SOCKET_FAILED,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_ERROR
            }
        },

        {//< Server test scoket binding Prompt Message
            UIU_PROMPT_MSG_SERVER_TEST_BINDING_FAILED,
            UIU_MSG_SERVER_TEST,
            UIU_MSG_BINDING_FAILED,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_ERROR
            }
        },

        {//< Sending Status Prompt Message
            UIU_PROMPT_MSG_CLIENT_TEST_SENDING,
            UIU_MSG_CLIENT_TEST,
            UIU_MSG_SENDING,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },

        {//< REceiving Status Prompt Message
            UIU_PROMPT_MSG_CLIENT_TEST_RECEIVING,
            UIU_MSG_CLIENT_TEST,
            UIU_MSG_RECEIVING,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },

        {//< Server Test Sending Status Prompt Message
            UIU_PROMPT_MSG_SERVER_TEST_SENDING,
            UIU_MSG_CLIENT_TEST,
            UIU_MSG_SENDING,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },

        {//< Listening Status Prompt Message
            UIU_PROMPT_MSG_SERVER_TEST_LISTENING,
            UIU_MSG_SERVER_TEST,
            UIU_MSG_LISTENING,
            UIU_TIMEOUT_100_MILLISECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_NONE
            }
        },

        {//< Connection Accepted Status Prompt Message
            UIU_PROMPT_MSG_SERVER_TEST_CONNECTION_ACCEPTED,
            UIU_MSG_SERVER_TEST,
            UIU_MSG_CONNECTION_ACCEPTED,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },

        {//< Server test connection accepted status Prompt Message
            UIU_PROMPT_MSG_SERVER_TEST_RECEIVING,
            UIU_MSG_SERVER_TEST,
            UIU_MSG_RECEIVING,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_NONE
            }
        },

        {//< Server Test Listening failed error message Prompt Message
            UIU_PROMPT_MSG_SERVER_TEST_LISTENING_FAILED,
            UIU_MSG_SERVER_TEST,
            UIU_MSG_LISTEN_FAILED,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_ERROR
            }
        },
        
        {//< Server Test Accept failed error message Prompt Message
            UIU_PROMPT_MSG_SERVER_TEST_ACCEPT_FAILED,
            UIU_MSG_SERVER_TEST,
            UIU_MSG_ACCEPT_FAILED,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_ERROR
            }
        },

        {//< Shutting down connection Prompt Message
            UIU_PROMPT_MSG_SHUTTING_CONNECTION,
            UIU_MSG_CLIENT_TEST,
            UIU_MSG_SHUTTING_DOWN_CONNECTION,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },

        {//< Launching Server Test Prompt Message
            UIU_PROMPT_MSG_SERVER_TEST_LAUNCH,
            UIU_MSG_SERVER_TEST,
            UIU_MSG_LAUNCHING_SERVER_TEST,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },
        
        {//< Launching Server Test Prompt Message
            UIU_PROMPT_MSG_CLIENT_TEST_LAUNCH,
            UIU_MSG_CLIENT_TEST,
            UIU_MSG_LAUNCHING_CLIENT_TEST,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },

        {//< Invalid Port Number Error Message
            UIU_PROMPT_MSG_INVALID_PORT_NUM,
            UIU_MSG_PORT_NUM_ENTRY,
            UIU_MSG_INVALID_INPUT,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_ERROR
            }
        },

        {//< Undefined Error prompt
            UIU_PROMPT_MSG_UNDEFINED_ERROR,
            UIU_MSG_UNDEFINED_ERROR,
            UIU_MSG_UNDEFINED_ERROR,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_ERROR
            }
        },

        {//< Test OK Prompt Message
            UIU_PROMPT_MSG_TEST_OK,
            UIU_MSG_TEST_RESULT,
            UIU_MSG_OK,
            UIU_TIMEOUT_5_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },

        {//< Connection Status Prompt Message: Creating socket...
            UIU_PROMPT_MSG_SERVER_TEST_CREATING_SOCKET,
            UIU_MSG_SERVER_TEST,
            UIU_MSG_CREATING_SOCKET,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_INFORMATION
            }
        },

        {//< Undefined prompt message
            UIU_PROMPT_MSG_END,
            UIU_MSG_UNDEFINED_PROMPT,
            UIU_MSG_UNDEFINED_PROMPT,
            UIU_TIMEOUT_3_SECONDS,
            {
                UIU_PROMPT_OPTION_CANCEL_BUTTON_DISABLED,
                UIU_PROMPT_OPTION_ENTER_BUTTON_ENABLED,
                0,
                UIU_PROMPT_OPTION_ICON_ERROR
            }
        }
    };

char *UIU_MsgStrGet(UIU_MsgIdx_t idx)
{
    int ctr;
    
    for(ctr = 0; uiuStrMsgList[ctr].msgID != UIU_MSG_END ; ctr++)
    {
        if(idx == uiuStrMsgList[ctr].msgID)// Message ID string found
        {
            return uiuStrMsgList[ctr].strMsg;
        }
    }

    // Undefined Message ID
    return uiuStrMsgList[ctr].strMsg;
}

UIU_Prompt_t *UIU_PromptGet(int promptID)
{
    int ctr;
    static UIU_Prompt_t prompt;
    
    memset(&prompt, 0, sizeof(UIU_Prompt_t));
    for(ctr = 0; ctr < sizeof(uiuPromptList)/sizeof(UIU_Prompt_t) ; ctr++)
    {
        if(promptID == uiuPromptList[ctr].promptID)// Error message found
        {
            memcpy(&prompt,&uiuPromptList[ctr], sizeof(UIU_Prompt_t));
            return &prompt;
        }
    }

    // Undefined Prompt
    memcpy(&prompt,&uiuPromptList[ctr-1], sizeof(UIU_Prompt_t));

    return &prompt;
}

void UIU_PromptDisplay(UIU_PromptIdx_t id)
{
    UIU_Prompt_t *prompt = NULL;
    char* title = NULL;
    char* promptMsg = NULL;

    prompt = UIU_PromptGet(id);
    title = UIU_MsgStrGet(prompt->title);
    promptMsg = UIU_MsgStrGet(prompt->promptMsg);

    guiScreen(title, promptMsg, prompt->options.icon, prompt->timeout);
}

