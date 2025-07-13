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
 Module  : EPU - Error Processing Unit

 @file      epu_errprompt.c
 @brief     Contains definitions of error list with corresponding prompt in UIU.
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "sdk30.h"
#include "epu_errprocess.h"
#include "uiu_userinterface.h"

struct EPU__error
{
    int errID;
    UIU_PromptIdx_t promptID;
};

const EPU_Error_t errorList[] = 
{
    { EPU_ERR_PHU_PROCESS_INVALID_PORT_NUM, UIU_PROMPT_MSG_ERR_INVALID_PORT_NUM},
    { EPU_ERR_DFU_SSL_RES_TEMP_UNAVAILABLE, UIU_PROMPT_MSG_ERR_SSL_RES_TEMP_UNAVAILABLE},
    { EPU_ERR_DFU_SSL_INVALID_ARGUMENT, UIU_PROMPT_MSG_ERR_SSL_INVALID_ARGUMENT},
    { EPU_ERR_DFU_SSL_OUT_OF_RESOURCES, UIU_PROMPT_MSG_ERR_SSL_OUT_OF_RES},
    { EPU_ERR_DFU_SSL_NO_SUCH_FILE_DIR, UIU_PROMPT_MSG_ERR_SSL_NO_SUCH_FILE_DIR},
    { EPU_ERR_DFU_SSL_INSUFFICIENT_MEMORY, UIU_PROMPT_MSG_ERR_SSL_INSUFFICIENT_MEM},
    { EPU_ERR_DFU_SSL_SOCKET_NOT_CONNECTED, UIU_PROMPT_MSG_ERR_SSL_SOCKET_NOT_CONNECTED},
    { EPU_ERR_DFU_SSL_GENERAL_ERROR, UIU_PROMPT_MSG_ERR_SSL_GENERAL_ERROR},
    { EPU_ERR_DFU_SSL_BAD_CERT_FORMAT, UIU_PROMPT_MSG_ERR_SSL_BAD_CERT_FORMAT},
    { EPU_ERR_DFU_SSL_CONNECTION_CLOSED, UIU_PROMPT_MSG_ERR_SSL_CONNECTION_CLOSED},
    { EPU_ERR_DFU_SSL_CONNECTION_FAILED, UIU_PROMPT_MSG_ERR_CONNECTION_FAILED},
    { EPU_ERR_DFU_SSL_PROFILE_DELETION_FAILED, UIU_PROMPT_MSG_ERR_PROFILE_DELETION_FAILED},
    { EPU_ERR_DFU_SSL_PROFILE_CREATION_FAILED, UIU_PROMPT_MSG_ERR_PROFILE_CREATION_FAILED},
    { EPU_ERR_DFU_SSL_NO_PROFILE_FOUND, UIU_PROMPT_MSG_ERR_SSL_NO_PROFILES_FOUND},
    { EPU_ERR_DFU_SSL_PROFILE_NOT_FOUND, UIU_PROMPT_MSG_ERR_SSL_PROFILE_NOT_FOUND},
    { EPU_ERR_DFU_SSL_CERTS_KEYS_NOT_LOADED, UIU_PROMPT_MSG_ERR_SSL_CERTS_KEYS_NOT_LOADED}
};

EPU_Error_t *EPU_ErrPromptElemGet(int errID)
{
    int ctr;
    static EPU_Error_t error;
    
    memset(&error, 0, sizeof(EPU_Error_t));
    for(ctr = 0; ctr < sizeof(errorList)/sizeof(EPU_Error_t) ; ctr++)
    {
        if(errID == errorList[ctr].errID)// Error message found
        {
            error.errID = errorList[ctr].errID;
            error.promptID = errorList[ctr].promptID;
            return &error;
        }
    }

    // Undefined error
    error.errID = EPU_ERR_UNDEFINED;
    error.promptID = UIU_PROMPT_MSG_ERR_UNDEFINED_ERROR;

    return &error;
}

UIU_PromptIdx_t EPU_ErrPromptIDGet(EPU_Error_t *error)
{
    return error->promptID;
}


#ifdef __cplusplus
}
#endif


