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
   
 Project : Mifare Sample
 Module  : UI - User Interface Unit

 @file      ui_message.h
 @brief     Contains enum list to reference the strings defined in ui_message.c.
            It also contains the prototype to the function used to access data in
            ui_message.c.
            
 @date      21/03/2013

 ------------------------------------------------------------------------------
 */

#ifndef __UI_MESSAGE_H__
#define __UI_MESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif


/** \addtogroup uigroup
 * @{
 */

/** \weakgroup uimessage UI Message
 * @{
 */

/** Indices to the predefined string messages list of the application.
 * This indices must be used when calling _UI_MsgStrGet(). Note that whatever
 * is defined here, must be defined in the message list.
 */
typedef enum
{
    UI_MSG_START,
    UI_MSG_UNDEFINED_ERROR,
    UI_MSG_UNDEFINED_PROMPT,
    UI_MSG_MIFARE_SAMPLE,
    UI_MSG_PAR_FILE_NOT_FOUND,
    UI_MSG_TPASS_NOT_CONNECTED,
    UI_MSG_OPEN_DRIVER_FAILED,
    UI_MSG_NO_CARD_DETECTED,
    UI_MSG_TOO_MANY_CARDS,
    UI_MSG_INVALID_CARD,
    UI_MSG_DETECTION_ERROR,
    UI_MSG_TIMEOUT,
    UI_MSG_NOT_MIFARE_CARD,
    UI_MSG_PAR_ERROR,
    UI_MSG_MAC_VERIFICATION_ERROR,
    UI_MSG_AUTHENTICATION_ERROR,
    UI_MSG_PICC_COMMS_ERROR,
    UI_MSG_COMMS_TIMEOUT,
    UI_MSG_INVALID_VALUE,
    UI_MSG_VALUE_ADD_WARNING,
    UI_MSG_PROCESSING_ERROR,
    UI_MSG_CRYPTO_ERROR,
    UI_MSG_SAM_ERROR,
    UI_MSG_PC_TIME_ERROR,
    UI_MSG_STATE_ERROR,
    UI_MSG_RESPONSE_ERROR,
    UI_MSG_DLL_NOT_LOADED,
    UI_MSG_ACCESS_DENIED,
    UI_MSG_INVALID_DATA,
    UI_MSG_INVALID_DATA_LEN,
    UI_MSG_TEST_OK,
    UI_MSG_TEST_FAILED,
    UI_MSG_END //< Undefined Message
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


