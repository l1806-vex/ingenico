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

 @file      ui_message.c
 @brief     Contains definitions of all strings needed in prompt messages.
            
 @date      02/14/2013

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "sdk30.h"
#include <GL_GraphicLib.h>

#include "Utilities.h"
#include "ui_userinterface.h"
#include "ui_message.h"

/** Message Database Structure
 */
typedef struct
{
    UI_MsgID_t msgID;
    char *strMsg;
}UI_StrMsg_t;

/** Define first the appropriate index in UI_MsgID_t enumeration
 * before inserting a message here. It is located in UI_Prompt.h
 */
/** Define first the appropriate index in UI_MsgIdx_t enumeration
 * before inserting a message here. It is located in UI_Prompt.h
 */
const UI_StrMsg_t uiStrMsgList[] = 
    {
        {
            UI_MSG_UNDEFINED_ERROR,
            "UNDEFINED ERROR"
        },
        {
            UI_MSG_UNDEFINED_PROMPT,
            "UNDEFINED PROMPT"
        },
        {
            UI_MSG_CARD_ENTRY_SAMPLE, 
            "CARD ENTRY SAMPLE\0",
        },
        {
            UI_MSG_PAR_FILE_NOT_FOUND,
            "PAR File Not Found\0"
        },
        {
            UI_MSG_ACCESS_DENIED,
            "Access Denied\0"
        },
        {
            UI_MSG_INVALID_DATA,
            "Invalid Data\0"
        },
        {
            UI_MSG_INVALID_DATA_LEN,
            "Invalid Data\nLength\0"
        },
        {
            UI_MSG_END, //< Undefined Message
            "Undefined Message ID\0",
        },
        
    };

char *_UI_MsgStrGet(UI_MsgID_t id)
{
    int ctr;
    
    for(ctr = 0; uiStrMsgList[ctr].msgID != UI_MSG_END ; ctr++)
    {
        if(id == uiStrMsgList[ctr].msgID)// Message ID string found
        {
            return uiStrMsgList[ctr].strMsg;
        }
    }

    // Undefined Message ID
    return uiStrMsgList[ctr].strMsg;
}

#ifdef __cplusplus
}
#endif


