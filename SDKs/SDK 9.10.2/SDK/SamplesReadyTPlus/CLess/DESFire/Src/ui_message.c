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

 @file      ui_message.c
 @brief     Contains definitions of all strings needed in prompt messages.
            
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
            UI_MSG_DESFIRE_SAMPLE, 
            "DESFIRE SAMPLE\0",
        },
        {
            UI_MSG_PAR_FILE_NOT_FOUND,
            "PAR File Not Found\0"
        },
        {
            UI_MSG_TPASS_NOT_CONNECTED,
            "TPASS NOT\nCONNECTED\0"
        },
        {
            UI_MSG_OPEN_DRIVER_FAILED,
            "OPEN DRIVER\nFAILED\0"
        },
        {
            UI_MSG_NO_CARD_DETECTED,
            "NO CARD DETECTED\0"
        },
        {
            UI_MSG_TOO_MANY_CARDS,
            "TOO MANY CARDS\nDETECTED\0"
        },
        {
            UI_MSG_INVALID_CARD,
            "INVALID CARD\0"
        },
        {
            UI_MSG_DETECTION_ERROR,
            "DETECTION ERROR\0"
        },
        {
            UI_MSG_TIMEOUT,
            "TIMEOUT\0"
        },
        {
            UI_MSG_NOT_MIFARE_CARD,
            "CARD IS NOT MIFARE\0"
        },
        {
            UI_MSG_DESFIRE_ERROR,
            "DESFIRE ERROR\nOCCURED\0"
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
            UI_MSG_PROCESSING,
            "Processing...\0"
        },
        {
            UI_MSG_TAP_CARD,
            "TAP\nCARD\0"
        },
        {
            UI_MSG_TEST_OK,
            "TEST OK\0"
        },
        {
            UI_MSG_TEST_FAILED,
            "TEST FAILED\0"
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


