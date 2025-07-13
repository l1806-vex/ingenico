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

 @file      uiu_message.h
 @brief     Contains enum list to reference the strings defined in uiu_message.c.
            It also contains the prototype to the function used to access data in
            uiu_message.c.
            
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifndef __UIU_MESSAGE_H__
#define __UIU_MESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif


/** \addtogroup uiugroup
 * @{
 */

/** \weakgroup uiumessage UIU Message
 * @{
 */

/** Indices to the predefined string messages list of the application.
 * This indices must be used when calling _UIU_MsgStrGet(). Note that whatever
 * is defined here, must be defined in the message list.
 */
typedef enum
{
    UIU_MSG_START,
    UIU_MSG_UNDEFINED_ERROR,
    UIU_MSG_UNDEFINED_PROMPT,
    UIU_MSG_INVALID_INPUT,
    UIU_MSG_PORT_NUM_ENTRY,
    UIU_MSG_SSL_SAMPLE,
    UIU_MSG_LOADING_SSL_PROFILE,
    UIU_MSG_CONNECTING_TO_SERVER,
    UIU_MSG_CONNECTION_OK,
    UIU_MSG_DISCONNECTING_FROM_SERVER,
    UIU_MSG_CREATING_PROFILE,
    UIU_MSG_OK,
    UIU_MSG_PROFILE_CREATION_SUCCESSFUL,
    UIU_MSG_PROFILE_CREATION_FAILED,
    UIU_MSG_PROFILE_DELETION_FAILED,
    UIU_MSG_NO_PROFILE_FOUND,
    UIU_MSG_PRINTING_PROFILES,
    UIU_MSG_DISCONNECTED,
    UIU_MSG_PROFILE_DELETION_OK,
    UIU_MSG_DELETING_PROFILE,
    UIU_MSG_CONNECTION_CLOSED,
    UIU_MSG_BAD_CERTIFICATE_FORMAT,
    UIU_MSG_GENERAL_ERROR,
    UIU_MSG_SOCKET_NOT_CONNECTED,
    UIU_MSG_INSUFFICIENT_MEMORY,
    UIU_MSG_NO_SUCH_FILE_OR_DIR,
    UIU_MSG_OUT_OF_RESOURCES,
    UIU_MSG_INVALID_ARGUMENT,
    UIU_MSG_CONNECTION_FAILED,
    UIU_MSG_PROFILE_NOT_FOUND,
    UIU_MSG_SSL_CERT_KEYS_NOT_LOADED,
    UIU_MSG_END //< Undefined Message
}UIU_MsgID_t;


/** Returns the string specified using the enum UIU_MsgID_t.
 *
 * \param[in] id    The identifier of the string to be retrieved.
 *
 * \return
 *      - NULL when the specified identifier is not found in the list.
 *      - Pointer to the string corresponding to the message identifier.
 */
char *_UIU_MsgStrGet(UIU_MsgID_t id);

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif // __UIU_MESSAGE_H__


