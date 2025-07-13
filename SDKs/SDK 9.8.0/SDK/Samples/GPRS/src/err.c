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
 Module  : ERR - Error Processing Unit

 @file      err.h
 @brief     Contains all prototypes that handle user interfaces
            such as display of menus, display of error messages,
            display of user input dialogs, and so on. This unit 
            interfaces functions that are interfacing low level 
            functions to get data from different peripherals of 
            the terminal such as display, keyboard, and other 
            related peripherals.
 @date      19/10/2012

 ------------------------------------------------------------------------------
 */


#include "sdk30.h"
#include "err.h"
#include "ui.h"

struct ERR__error
{
    int errID;
    UI_PromptIdx_t promptID;
};

const ERR_Error_t errorList[] = 
{
    { ERR_UNDEFINED, UI_PROMPT_MSG_ERR_UNDEFINED_ERROR},
    { ERR_FLOW_PROCESS_INVALID_PORT_NUM, UI_PROMPT_MSG_ERR_INVALID_PORT_NUM},
    { ERR_FUN_GPRS_NO_SIM, UI_PROMPT_MSG_ERR_NO_SIM},
    { ERR_FUN_GPRS_SIM_LOCK, UI_PROMPT_MSG_ERR_SIM_LOCK},
    { ERR_FUN_GPRS_NO_PIN, UI_PROMPT_MSG_ERR_NO_PIN},
    { ERR_FUN_GPRS_BAD_PIN, UI_PROMPT_MSG_ERR_BAD_PIN},
    { ERR_FUN_GPRS_FATAL, UI_PROMPT_MSG_ERR_FATAL},
    { ERR_FUN_GPRS_UNKNOWN, UI_PROMPT_MSG_ERR_UNKNOWN},
    { ERR_FUN_GPRS_NETWORK_NOT_AVAILABLE, UI_PROMPT_MSG_ERR_GPRS_NETWORK},
    { ERR_FUN_GPRS_NULL_POINTER, UI_PROMPT_MSG_ERR_NULL_POINTER},
    { ERR_FUN_CONNECT_TIMEOUT, UI_PROMPT_MSG_ERR_CONNECT_TIMEOUT},
    { ERR_FUN_PPP_CONNECT_FAILED, UI_PROMPT_MSG_ERR_PPP},
    { ERR_FUN_GPRS_NETWORK_UNAVAILABLE, UI_PROMPT_MSG_ERR_NO_GPRS},
    { ERR_FUN_GSM_ENABLE, UI_PROMPT_MSG_ERR_GSM_ENABLE},
    { ERR_FUN_GSM_NETWORK_NOT_AVAILABLE, UI_PROMPT_MSG_ERR_GSM_NETWORK},
    { ERR_FUN_TCP_SEND_FAILED, UI_PROMPT_MSG_ERR_SEND},
    { ERR_FUN_TCP_RECEIVE_FAILED, UI_PROMPT_MSG_ERR_RECEIVE},
    { ERR_FUN_TCP_CONNECTION_FAILED, UI_PROMPT_MSG_ERR_CONNECTION_FAILED},
    { ERR_FUN_GSM_TIMEOUT, UI_PROMPT_MSG_ERR_CONNECT_TIMEOUT},
    { ERR_FUN_PPP_AUTH_TIMEOUT, UI_PROMPT_MSG_ERR_CONNECT_TIMEOUT},
    { ERR_FUN_PPP_AUTH_FAILED, UI_PROMPT_MSG_ERR_AUTH_FAILED},
};

ERR_Error_t *ERR_PromptElemGet(int errID)
{
    int ctr;
    static ERR_Error_t error;
    
    memset(&error, 0, sizeof(ERR_Error_t));
    for(ctr = 0; ctr < sizeof(errorList)/sizeof(ERR_Error_t) ; ctr++)
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

UI_PromptIdx_t ERR_PromptIDGet(ERR_Error_t *error)
{
    return error->promptID;
}
