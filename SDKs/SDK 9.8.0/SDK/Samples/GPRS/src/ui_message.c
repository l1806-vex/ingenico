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

 @file      ui_msg.c
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
#include "ui_message.h"

/** Message Database Structure
 */
typedef struct
{
    UI_MsgID_t msgID;
    char *strMsg;
}UI_StrMsg_t;

/** Define first the appropriate index in UI_MsgIdx_t enumeration
 * before inserting a message here. It is located in UI_Prompt.h
 */
const UI_StrMsg_t uiuStrMsgList[] = 
    {
        {
            UI_MSG_ERROR_UNKNOWN,
            "Error Unknown\0"
        },
        {
            UI_MSG_INVALID_INPUT,
            "Invalid Input\0"
        },
        {
            UI_MSG_PORT_NUM_ENTRY,
            "Port Num Entry"
        },
        {
            UI_MSG_UNDEFINED_PROMPT,
            "UNDEFINED PROMPT"
        },
        {
            UI_MSG_GPRS_SAMPLE,
            "GPRS SAMPLE\0",
        },
        {
            UI_MSG_TCP_TEST,
            "TCP TEST\0",
        },
        {
            UI_MSG_GSM_TEST,
            "GSM TEST\0",
        },
        {
            UI_MSG_PPP_TEST,
            "PPP TEST\0",
        },
        {
            UI_MSG_OK,
            "OK\0",
        },
        {
            UI_MSG_INSUFFICIENT_MEMORY,
            "Insufficient memory!\0",
        },
        {
            UI_MSG_NO_SUCH_FILE_OR_DIR,
            "No such file or directory!\0",
        },
        {
            UI_MSG_OUT_OF_RESOURCES,
            "Out of resources!\0",
        },
        {
            UI_MSG_INVALID_ARGUMENT,
            "Invalid argument!\0",
        },
        {
            UI_MSG_ERROR,
            "Error\0",
        },
        {
            UI_MSG_ACTIVATING,
            "Activating\0",
        },
        {
            UI_MSG_ACTIVATED,
            "Activated\0",
        },
        {
            UI_MSG_DEACTIVATING,
            "Deactivating\0",
        },
        {
            UI_MSG_DEACTIVATED,
            "Deactivated\0",
        },
        {
            UI_MSG_ENABLED,
            "Enabled\0",
        },
        {
            UI_MSG_DISABLED,
            "Disabled\0",
        },
        {
            UI_MSG_SENDING,
            "Sending\0",
        },
        {
            UI_MSG_RECEIVING,
            "Receiving\0",
        },
        {
            UI_MSG_CONNECTING,
            "Connecting\0",
        },
        {
            UI_MSG_CONNECTION_OK,
            "Connection OK!\0",
        },
        {
            UI_MSG_CONNECTION_FAILED,
            "Connection Failed!\0",
        },
        {
            UI_MSG_DISCONNECTING,
            "Disconnecting\0",
        },
        {
            UI_MSG_DISCONNECTED,
            "Disconnected\0",
        },
        {
            UI_MSG_RECEIVED,
            "Received\0",
        },
        {
            UI_MSG_SEND_ERROR,
            "Send Error\0",
        },
        {
            UI_MSG_RECEIVE_ERROR,
            "Receive Error\0",
        },
        {
            UI_MSG_NULL_POINTER,
            "Invalid Data\0",
        },
        {
            UI_MSG_TIMEOUT,
            "Connection\nTimeout\0",
        },
        {
            UI_MSG_AUTH_FAILED,
            "Authentication\nFailed\0",
        },
        {
            UI_MSG_PPP,
            "PPP Connection\nFailed\0",
        },
        {
            UI_MSG_ALREADY_CONNECTED,
            "Already\nConnected\0",
        },
        {
            UI_MSG_NO_GPRS,
            "GPRS Disabled\0",
        },
        {
            UI_MSG_NO_SIM,
            "No Sim\0",
        },
        {
            UI_MSG_SIM_LOCK,
            "SIM Locked\0",
        },
        {
            UI_MSG_NO_PIN,
            "No PIN\0",
        },
        {
            UI_MSG_BAD_PIN,
            "Bad PIN\0",
        },
        {
            UI_MSG_FATAL,
            "Fatal Error\0",
        },
        {
            UI_MSG_UNKNOWN,
            "Unknown Error\0",
        },
        {
            UI_MSG_GPRS_NETWORK_NOT_AVAILABLE,
            "GPRS Network\nNot Available\0",
        },
        {
            UI_MSG_GSM_ENABLE,
            "Enable GSM KO!\0",
        },
        {
            UI_MSG_GSM_NETWORK_NOT_AVAILABLE,
            "GSM Network\nNotAvailable\0",
        },
        {
            UI_MSG_IP_ERR,
            "IP Error\0",
        },
        {
            UI_MSG_END,
            "Undefined Message ID\0",
        },
    };

char *_UI_MsgStrGet(UI_MsgID_t id)
{
    int ctr;
    
    for(ctr = 0; uiuStrMsgList[ctr].msgID != UI_MSG_END ; ctr++)
    {
        if(id == uiuStrMsgList[ctr].msgID)// Message ID string found
        {
            return uiuStrMsgList[ctr].strMsg;
        }
    }

    // Undefined Message ID
    return uiuStrMsgList[ctr].strMsg;
}

#ifdef __cplusplus
}
#endif

