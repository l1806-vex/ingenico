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

 @file      uiu_message.c
 @brief     Contains definitions of all strings needed in prompt messages.
            
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
#include "uiu_message.h"

/** Message Database Structure
 */
typedef struct
{
    UIU_MsgID_t msgID;
    char *strMsg;
}UIU_StrMsg_t;

/** Define first the appropriate index in UIU_MsgID_t enumeration
 * before inserting a message here. It is located in UIU_Prompt.h
 */
const UIU_StrMsg_t uiuStrMsgList[] = 
    {
        {
            UIU_MSG_INVALID_INPUT,
            "Invalid Input\0"
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
            UIU_MSG_SSL_SAMPLE, 
            "SSL SAMPLE\0",
        },
        {
            UIU_MSG_LOADING_SSL_PROFILE, 
            "Loading SSL Profile...\0",
        },
        {
            UIU_MSG_CONNECTING_TO_SERVER, 
            "Connecting to server...\0",
        },
        {
            UIU_MSG_CONNECTION_OK, 
            "Connection OK!\0",
        },
        {
            UIU_MSG_DISCONNECTING_FROM_SERVER, 
            "Disconnecting from server...\0",
        },
        {
            UIU_MSG_CREATING_PROFILE, 
            "Creating profile...\0",
        },
        {
            UIU_MSG_PROFILE_CREATION_SUCCESSFUL, 
            "Profile creation OK!\0",
        },
        {
            UIU_MSG_PROFILE_CREATION_FAILED, 
            "Profile creation FAILED!\0",
        },
        {
            UIU_MSG_PROFILE_DELETION_FAILED, 
            "Profile deletion FAILED!\0",
        },
        {
            UIU_MSG_OK, 
            "OK\0",
        },
        {
            UIU_MSG_NO_PROFILE_FOUND, 
            "No Profiles Found!\0",
        },
        {
            UIU_MSG_PRINTING_PROFILES, 
            "Printing profiles...\0",
        },
        {
            UIU_MSG_DISCONNECTED, 
            "Disconnected!\0",
        },
        {
            UIU_MSG_PROFILE_DELETION_OK, 
            "Profile deletion OK!\0",
        },
        {
            UIU_MSG_DELETING_PROFILE, 
            "Deleting profile...\0",
        },
        {
            UIU_MSG_CONNECTION_CLOSED, 
            "Connection closed!\0",
        },
        {
            UIU_MSG_BAD_CERTIFICATE_FORMAT, 
            "Bad certificate format!\0",
        },
        {
            UIU_MSG_GENERAL_ERROR, 
            "General Error!\0",
        },
        {
            UIU_MSG_SOCKET_NOT_CONNECTED, 
            "Socket not connected!\0",
        },
        {
            UIU_MSG_INSUFFICIENT_MEMORY, 
            "Insufficient memory!\0",
        },
        {
            UIU_MSG_NO_SUCH_FILE_OR_DIR, 
            "No such file or directory!\0",
        },
        {
            UIU_MSG_OUT_OF_RESOURCES, 
            "Out of resources!\0",
        },
        {
            UIU_MSG_INVALID_ARGUMENT, 
            "Invalid argument!\0",
        },
        {
            UIU_MSG_CONNECTION_FAILED, 
            "Connection Failed!\0",
        },
        {
            UIU_MSG_PROFILE_NOT_FOUND, 
            "Profile not found!\0",
        },
        {
            UIU_MSG_SSL_CERT_KEYS_NOT_LOADED, 
            "SSL certificates and keys not loaded!\0",
        },
        {
            UIU_MSG_END, 
            "Undefined Message ID\0",
        },
    };

char *_UIU_MsgStrGet(UIU_MsgID_t id)
{
    int ctr;
    
    for(ctr = 0; uiuStrMsgList[ctr].msgID != UIU_MSG_END ; ctr++)
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


