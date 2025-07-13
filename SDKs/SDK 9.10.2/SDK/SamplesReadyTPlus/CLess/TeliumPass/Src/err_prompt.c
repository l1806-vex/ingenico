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
   
 Project : Telium Pass Sample
 Module  : EPU - Error Processing Unit

 @file      epu_errprompt.c
 @brief     Contains definitions of error list with corresponding prompt in UIU.
 @date      08/03/2013
 
 ------------------------------------------------------------------------------
 */

#include "sdk30.h"
#include "err_process.h"
#include "ui_userinterface.h"

struct ERR_prompt
{
    int errID;
    UI_PromptIdx_t promptID;
};

const ERR_Prompt_t errorList[] = 
{
    { ERR_PAR_FILE_NOT_FOUND, UI_PROMPT_MSG_PAR_FILE_NOT_FOUND},
    { ERR_TPASS_NOT_CONNECTED, UI_PROMPT_MSG_TPASS_NOT_CONNECTED},
    { ERR_OPEN_DRIVER_FAILED, UI_PROMPT_MSG_OPEN_DRIVER_FAILED},
    { ERR_NO_CARD_DETECTED, UI_PROMPT_MSG_NO_CARD_DETECTED},
    { ERR_TOO_MANY_CARDS, UI_PROMPT_MSG_TOO_MANY_CARDS},
    { ERR_INVALID_CARD, UI_PROMPT_MSG_INVALID_CARD},
    { ERR_DETECTION_ERROR, UI_PROMPT_MSG_DETECTION_ERROR},
    { ERR_TIMEOUT, UI_PROMPT_MSG_TIMEOUT},
    { ERR_NOT_MIFARE_CARD, UI_PROMPT_MSG_NOT_MIFARE_CARD}
};

ERR_Prompt_t *ERR_PromptElemGet(int errID)
{
    int ctr;
    static ERR_Prompt_t error;
    
    memset(&error, 0, sizeof(ERR_Prompt_t));
    for(ctr = 0; ctr < sizeof(errorList)/sizeof(ERR_Prompt_t) ; ctr++)
    {
        if(errID == errorList[ctr].errID)// Error message found
        {
            error.errID = errorList[ctr].errID;
            error.promptID = errorList[ctr].promptID;
            return &error;
        }
    }

    // Undefined error
    error.errID = ERR_UNDEFINED;
    error.promptID = UI_PROMPT_MSG_ERR_UNDEFINED_ERROR;

    return &error;
}

UI_PromptIdx_t ERR_PromptIDGet(ERR_Prompt_t *error)
{
    return error->promptID;
}

