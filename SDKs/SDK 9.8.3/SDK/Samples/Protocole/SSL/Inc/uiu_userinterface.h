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

 @file      uiu_userinterface.h
 @brief     Contains all prototypes that handle user interfaces such as display
            of menus, display of error messages,display of user input dialogs, 
            and so on. This unit interfaces functions that are interfacing low 
            level functions to get data from different peripherals of the 
            terminal such as display, keyboard, and other related peripherals.
            
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifndef __UIU_H__
#define __UIU_H__

#ifdef __cplusplus
extern "C" {
#endif


/** \addtogroup uiugroup UIU User Interface Unit
 *
 * Contains all functions that handle user interfaces such as display of menus, 
 * display of error messages, display of user input dialogs, and so on. 
 * This unit interfaces functions that are interfacing low level functions to get
 * data from different peripherals of the terminal such as display, keyboard, and 
 * other related peripherals.
 *
 * @{
 */

/** \weakgroup uiumain UIU Main
 * 
 * Functions in charge of peripheral management in the terminal.
 *
 * @{
 */

#define UIU_TIMEOUT_100_MILLISECONDS         100 ///< 100 milliseconds timeout delay used for GUI dialogs
#define UIU_TIMEOUT_3_SECONDS               3000 ///< 3-second timeout delay used for GUI dialogs
#define UIU_TIMEOUT_5_SECONDS               5000 ///< 5-second timeout delay used for GUI dialogs


/** Indices to the predefined screen prompt list of the application.
 * This indices must be used when calling UIU_PromptMsgDisplay(). Note that
 * whatever is defined here should also be defined in the prompt list.
 */
typedef enum
{
    UIU_PROMPT_MSG_START,
    UIU_PROMPT_MSG_ERR_UNDEFINED_ERROR,
    UIU_PROMPT_MSG_ERR_INVALID_PORT_NUM,
    UIU_PROMPT_MSG_ERR_SSL_RES_TEMP_UNAVAILABLE,
    UIU_PROMPT_MSG_ERR_SSL_INVALID_ARGUMENT,
    UIU_PROMPT_MSG_ERR_SSL_OUT_OF_RES,
    UIU_PROMPT_MSG_ERR_SSL_NO_SUCH_FILE_DIR,
    UIU_PROMPT_MSG_ERR_SSL_INSUFFICIENT_MEM,
    UIU_PROMPT_MSG_ERR_SSL_SOCKET_NOT_CONNECTED,
    UIU_PROMPT_MSG_ERR_SSL_GENERAL_ERROR,
    UIU_PROMPT_MSG_ERR_SSL_BAD_CERT_FORMAT,
    UIU_PROMPT_MSG_ERR_SSL_CONNECTION_CLOSED,
    UIU_PROMPT_MSG_ERR_CONNECTION_FAILED,
    UIU_PROMPT_MSG_ERR_PROFILE_CREATION_FAILED,
    UIU_PROMPT_MSG_ERR_PROFILE_DELETION_FAILED,
    UIU_PROMPT_MSG_ERR_SSL_NO_PROFILES_FOUND,
    UIU_PROMPT_MSG_ERR_SSL_PROFILE_NOT_FOUND,
    UIU_PROMPT_MSG_STAT_DELETING_PROFILE,
    UIU_PROMPT_MSG_STAT_PROFILE_DELETION_OK,
    UIU_PROMPT_MSG_STAT_PRINTING_PROFILE,
    UIU_PROMPT_MSG_STAT_CREATING_PROFILE,
    UIU_PROMPT_MSG_STAT_PROFILE_CREATION_OK,
    UIU_PROMPT_MSG_STAT_LOADING_SSL_PROFILE,
    UIU_PROMPT_MSG_STAT_CONNECTING_TO_SERVER,
    UIU_PROMPT_MSG_STAT_CONNECTION_OK,
    UIU_PROMPT_MSG_STAT_DISCONNECTING_FROM_SERVER,
    UIU_PROMPT_MSG_STAT_DISCONNECTED,
    UIU_PROMPT_MSG_ERR_SSL_CERTS_KEYS_NOT_LOADED,
    UIU_PROMPT_MSG_END
}UIU_PromptIdx_t;

/** Starts all user interface peripherals in the terminal ready for used by the application. This includes
 * the keyboard, the display and the touch screen peripherals.
 *
 * \return
 *      - \ref EPU_ERR_UIU_DISPLAY_PERIPH_DISPLAY_NOT_OPEN = The display peripheral cannot be openned.
 *      - \ref EPU_ERR_UIU_DISPLAY_PERIPH_KEYBOARD_NOT_OPEN = The keyboard peripheral cannot be openned.
 *      - \ref EPU_ERR_UIU_DISPLAY_PERIPH_TFT_NOT_OPEN = The touch screen peripheral cannot be openned.
 */
int UIU_PeriphStart( void );

/** Stops all user interface peripherals in the terminal. It gives up all handles acquired by the terminal
 * with the display and touch screen and the keyboard.
 *
 * \return
 *      - \ref EPU_ERR_UIU_DISPLAY_PERIPH_DISPLAY_NOT_CLOSE = The display peripheral cannot be closed.
 *      - \ref EPU_ERR_UIU_DISPLAY_PERIPH_KEYBOARD_NOT_CLOSE = The keyboard peripheral cannot be closed.
 *      - \ref EPU_ERR_UIU_DISPLAY_PERIPH_TFT_NOT_CLOSE = The touch screen peripheral cannot be closed.
 */
int UIU_PeriphStop( void );


/** Displays the menu of the sample application.
 *
 */
void UIU_MenuMainDisplay( void );

/** Toggles the idle display's header/footer.
 * It makes sure that the header and footer are turned off. It will restore the
 * original state of the header/footer display when called the second time.
 */
void UIU_IdleDispHdrFtrToggle( void );

/** Displays an error message.
 *
 * \pre The given error code should have been defined first. Only those defined in epu_errprocess.h.
 *
 * \param   errID   The error code defined in epu_errprocess.h. See \ref epuerrorid "Error Identifiers"
 *
 * \return
 *      None
 *  
 */
void UIU_ErrMsgDisplay(int errID);

/** Displays a prompt message.
 * 
 * \param[in] promptID      The identifier of the prompt to be displayed.
 *
 * \note
 *      When the specified prompt ID does not exist, the function will display a default prompt
 *      message indicating an undefined prompt.
 */
void UIU_PromptMsgDisplay(UIU_PromptIdx_t promptID);
/** @} */

#ifdef __cplusplus
}
#endif

#endif // __UIU_H__

