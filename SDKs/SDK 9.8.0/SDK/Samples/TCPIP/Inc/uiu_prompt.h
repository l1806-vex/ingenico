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

 @file      uiuPrompt.h
 @brief     Contains all prototypes for user interfaces related to prompt
            messages.
            
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifndef __UIU_PROMPT_H__
#define __UIU_PROMPT_H__

/** \addtogroup uiugroup
 * @{
 */

/** \weakgroup uiuprompt UIU Prompt
 * @{
 */

/** Indices to the predefined string messages list of the application.
 * This indices must be used when calling UIU_MsgStrGet(). Note that whatever
 * is defined here, must be defined in the message list.
 */
typedef enum
{
    UIU_MSG_START,
    UIU_MSG_INVALID_INPUT,
    UIU_MSG_UNDEFINED_ERROR,
    UIU_MSG_CONNECTION_STATUS,
    UIU_MSG_CONNECTING_TO_SERVER,
    UIU_MSG_PORT_NUM_ENTRY,
    UIU_MSG_UNDEFINED_PROMPT,
    UIU_MSG_UNDEFINED_ERROR,
    UIU_MSG_CONNECTION_TO_SERVER_FAILED,
    UIU_MSG_SOCKET_FAILED,
    UIU_MSG_CREATING_SOCKET,
    UIU_MSG_RESOLVING_DNS_NAME,
    UIU_MSG_CLIENT_TEST,
    UIU_MSG_SENDING,
    UIU_MSG_SENDING_FAILED,
    UIU_MSG_SHUTTING_DOWN_CONNECTION,
    UIU_MSG_TEST_RESULT,
    UIU_MSG_OK,
    UIU_MSG_SERVER_TEST,
    UIU_MSG_LAUNCHING_CLIENT_TEST,
    UIU_MSG_LAUNCHING_SERVER_TEST,
    UIU_MSG_BINDING_FAILED,
    UIU_MSG_LISTEN_FAILED,
    UIU_MSG_LISTENING,
    UIU_MSG_CONNECTION_ACCEPTED,
    UIU_MSG_RECEIVING,
    UIU_MSG_ACCEPT_FAILED,
    UIU_MSG_END //< Undefined Message
}UIU_MsgIdx_t;

/** Indices to the predefined screen prompt list of the application.
 * This indices must be used when calling UIU_PromptMsgDisplay(). Note that
 * whatever is defined here should also be defined in the prompt list.
 */
typedef enum
{
    UIU_PROMPT_MSG_START,
    UIU_PROMPT_MSG_CON_STATUS_CONNECTING,
    UIU_PROMPT_MSG_CLIENT_TEST_CON_STATUS_FAILED,
    UIU_PROMPT_MSG_CLIENT_TEST_SOCKET_FAILED,
    UIU_PROMPT_MSG_SERVER_TEST_SOCKET_FAILED,
    UIU_PROMPT_MSG_INVALID_PORT_NUM,
    UIU_PROMPT_MSG_UNDEFINED_ERROR,
    UIU_PROMPT_MSG_CLIENT_TEST_CREATING_SOCKET,
    UIU_PROMPT_MSG_CON_STATUS_RESOLVING_DNS,
    UIU_PROMPT_MSG_CLIENT_TEST_SENDING,
    UIU_PROMPT_MSG_CLIENT_TEST_SEND_FAILED,
    UIU_PROMPT_MSG_CLIENT_TEST_RECEIVING,
    UIU_PROMPT_MSG_SHUTTING_CONNECTION,
    UIU_PROMPT_MSG_TEST_OK,
    UIU_PROMPT_MSG_CLIENT_TEST_LAUNCH,
    UIU_PROMPT_MSG_SERVER_TEST_LAUNCH,
    UIU_PROMPT_MSG_SERVER_TEST_CREATING_SOCKET,
    UIU_PROMPT_MSG_SERVER_TEST_BINDING_FAILED,
    UIU_PROMPT_MSG_SERVER_TEST_LISTENING_FAILED,
    UIU_PROMPT_MSG_SERVER_TEST_LISTENING,
    UIU_PROMPT_MSG_SERVER_TEST_CONNECTION_ACCEPTED,
    UIU_PROMPT_MSG_SERVER_TEST_RECEIVING,
    UIU_PROMPT_MSG_SERVER_TEST_SENDING,
    UIU_PROMPT_MSG_SERVER_TEST_ACCEPT_FAILED,
    UIU_PROMPT_MSG_END
}UIU_PromptIdx_t;

/** Returns the string specified using the enum UIU_MsgIdx_t.
 */
char *UIU_MsgStrGet(UIU_MsgIdx_t idx);

/** Displays a prompt.
 */
void UIU_PromptDisplay(UIU_PromptIdx_t id);

/** @} */
/** @} */
#endif // __UIU_PROMPT_H__

