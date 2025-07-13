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

 @file      ui_message.h
 @brief     Contains enum list to reference the strings defined in ui_msg.c.
            It also contains the prototype to the function used to access data in
            ui_msg.c.
            
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifndef __UI_MESSAGE_H__
#define __UI_MESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup uiugroup
 * @{
 */

/** \weakgroup uiumessage UI Message List
 * @{
 */

/** Indices to the predefined string messages list of the application.
 * This indices must be used when calling UI_MsgStrGet(). Note that whatever
 * is defined here, must be defined in the message list.
 */
typedef enum
{
    UI_MSG_START,
    UI_MSG_ERROR_UNKNOWN,
    UI_MSG_INVALID_INPUT,
    UI_MSG_PORT_NUM_ENTRY,
    UI_MSG_UNDEFINED_PROMPT,
    UI_MSG_GPRS_SAMPLE,
    UI_MSG_TCP_TEST,
    UI_MSG_GSM_TEST,
    UI_MSG_PPP_TEST,
    UI_MSG_OK,
    UI_MSG_INSUFFICIENT_MEMORY,
    UI_MSG_NO_SUCH_FILE_OR_DIR,
    UI_MSG_OUT_OF_RESOURCES,
    UI_MSG_INVALID_ARGUMENT,
    UI_MSG_NULL_POINTER,
    UI_MSG_ERROR,
    UI_MSG_ACTIVATING,
    UI_MSG_ACTIVATED,
    UI_MSG_DEACTIVATING,
    UI_MSG_DEACTIVATED,
    UI_MSG_ENABLED,
    UI_MSG_DISABLED,
    UI_MSG_SENDING,
    UI_MSG_RECEIVING,
    UI_MSG_CONNECTING,
    UI_MSG_CONNECTION_OK,
    UI_MSG_CONNECTION_FAILED,
    UI_MSG_DISCONNECTING,
    UI_MSG_DISCONNECTED,
    UI_MSG_RECEIVED,
    UI_MSG_SEND_ERROR,
    UI_MSG_RECEIVE_ERROR,
    UI_MSG_TIMEOUT,
    UI_MSG_AUTH_FAILED,
    UI_MSG_PPP,
    UI_MSG_ALREADY_CONNECTED,
    UI_MSG_NO_GPRS,
    UI_MSG_NO_SIM,
    UI_MSG_SIM_LOCK,
    UI_MSG_NO_PIN,
    UI_MSG_BAD_PIN,
    UI_MSG_FATAL,
    UI_MSG_UNKNOWN,
    UI_MSG_GPRS_NETWORK_NOT_AVAILABLE,
    UI_MSG_GSM_ENABLE,
    UI_MSG_GSM_NETWORK_NOT_AVAILABLE,
    UI_MSG_IP_ERR,
    UI_MSG_END
}UI_MsgID_t;

/** Returns the string specified using the enum UI_MsgID_t.
 *
 * \param[in] id    The identifier of the string to be retrieved.
 *
 * \return
 *      - NULL when the specified identifier is not found in the list.
 *      - Pointer to the string corresponding to the message identifier.
 */
char *_UI_MsgStrGet(UI_MsgID_t id);

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif // __UI_MESSAGE_H__


