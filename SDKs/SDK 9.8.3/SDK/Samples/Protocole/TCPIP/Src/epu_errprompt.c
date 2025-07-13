/*+
 *  PROJECT         :   TCP/IP Sample
 *  MODULE          :   Error Processing Unit
 *  FILEMANE        :   epu.c
 *  PURPOSE         :   Definitions for EPU
 *
 *  DESCRIPTION     :   Contains all prototypes that handle user interfaces
 *                      such as display of menus, display of error messages,
 *                      display of user input dialogs, and so on. This unit 
 *                      interfaces functions that are interfacing low level 
 *                      functions to get data from different peripherals of 
 *                      the terminal such as display, keyboard, and other 
 *                      related peripherals.
 *
 *  Copyright (c) 2012 Ingenico. All Rights Reserved.
 *
 *  Ingenico has intellectual property rights relating to the technology 
 *  embodied in this software.  In particular, and without limitation, 
 *  these intellectual property rights may include one or more patents.
 *
 *  This software is distributed under licenses restricting its use, 
 *  copying, distribution, and decompilation. No part of this software may be 
 *  reproduced in any form by any means without prior written authorization of 
 *  Ingenico.
 *
 * 
 *  HISTORY         :
 *
 *  Author:          Ingenico R&D Philippines Team
 *  Modification:    Creation
 *  Date:            2012/09/17
-*/

#include "sdk30.h"
#include "epu_errprocess.h"
#include "uiu_prompt.h"

struct EPU__error
{
    int errID;
    UIU_PromptIdx_t promptID;
};

const EPU_Error_t errorList[] = 
{
    { EPU_ERR_INVALID_PORT_NUM, UIU_PROMPT_MSG_INVALID_PORT_NUM},
    { EPU_ERR_CLIENT_TEST_CONNECTION_FAILED, UIU_PROMPT_MSG_CLIENT_TEST_CON_STATUS_FAILED},
    { EPU_ERR_CLIENT_TEST_SOCKET_FAILED, UIU_PROMPT_MSG_CLIENT_TEST_SOCKET_FAILED},
    { EPU_ERR_CLIENT_TEST_SEND_FAILED, UIU_PROMPT_MSG_CLIENT_TEST_SEND_FAILED},
    { EPU_ERR_SERVER_TEST_SOCKET_FAILED, UIU_PROMPT_MSG_SERVER_TEST_SOCKET_FAILED},
    { EPU_ERR_SERVER_TEST_BINDING_FAILED, UIU_PROMPT_MSG_SERVER_TEST_BINDING_FAILED},
    { EPU_ERR_SERVER_TEST_LISTEN_FAILED, UIU_PROMPT_MSG_SERVER_TEST_LISTENING_FAILED},
    { EPU_ERR_SERVER_TEST_ACCEPT_FAILED, UIU_PROMPT_MSG_SERVER_TEST_ACCEPT_FAILED}
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
    error.promptID = UIU_PROMPT_MSG_UNDEFINED_ERROR;

    return &error;
}

UIU_PromptIdx_t EPU_ErrPromptIDGet(EPU_Error_t *error)
{
    return error->promptID;
}
