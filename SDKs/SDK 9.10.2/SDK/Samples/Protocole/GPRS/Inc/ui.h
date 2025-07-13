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

 @file      ui.h
 @brief     Contains all prototypes that handle user interfaces such as display
            of menus, display of error messages,display of user input dialogs, 
            and so on. This unit interfaces functions that are interfacing low 
            level functions to get data from different peripherals of the 
            terminal such as display, keyboard, and other related peripherals.
            
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifndef __UI_H__
#define __UI_H__

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup uiugroup UI User Interface Unit
 *
 * Contains all functions that handle user interfaces such as display of menus, 
 * display of error messages, display of user input dialogs, and so on. 
 * This unit interfaces functions that are interfacing low level functions to get
 * data from different peripherals of the terminal such as display, keyboard, and 
 * other related peripherals.
 *
 * @{
 */

/** \weakgroup uiumain UI Main
 * 
 * Functions in charge of peripheral management in the terminal.
 *
 * @{
 */

#define UI_TIMEOUT_100_MILLISECONDS         100 ///< 100 milliseconds timeout delay used for GUI dialogs
#define UI_TIMEOUT_3_SECONDS               3000 ///< 3-second timeout delay used for GUI dialogs
#define UI_TIMEOUT_5_SECONDS               5000 ///< 5-second timeout delay used for GUI dialogs

/** Indices to the predefined screen prompt list of the application.
 * This indices must be used when calling UI_PromptMsgDisplay(). Note that
 * whatever is defined here should also be defined in the prompt list.
 */
typedef enum
{
    UI_PROMPT_MSG_START,
    UI_PROMPT_MSG_ERR_UNDEFINED_ERROR,
    UI_PROMPT_MSG_ERR_INVALID_PORT_NUM,
    UI_PROMPT_MSG_ERR_PPP,
    UI_PROMPT_MSG_ERR_ALREADY_CONNECTED,
    UI_PROMPT_MSG_ERR_NO_GPRS,
    UI_PROMPT_MSG_ERR_NO_SIM,
    UI_PROMPT_MSG_ERR_SIM_LOCK,
    UI_PROMPT_MSG_ERR_NO_PIN,
    UI_PROMPT_MSG_ERR_BAD_PIN,
    UI_PROMPT_MSG_ERR_FATAL,
    UI_PROMPT_MSG_ERR_UNKNOWN,
    UI_PROMPT_MSG_ERR_GPRS_NETWORK,
    UI_PROMPT_MSG_ERR_GSM_ENABLE,
    UI_PROMPT_MSG_ERR_GSM_NETWORK,
    UI_PROMPT_MSG_ERR_IP,
    UI_PROMPT_MSG_ERR_SEND,
    UI_PROMPT_MSG_ERR_RECEIVE,
    UI_PROMPT_MSG_ERR_CONNECTION_FAILED,
    UI_PROMPT_MSG_ERR_NULL_POINTER,
    UI_PROMPT_MSG_ERR_CONNECT_TIMEOUT,
    UI_PROMPT_MSG_ERR_AUTH_FAILED,

    UI_PROMPT_MSG_STAT_ENABLED,
    UI_PROMPT_MSG_STAT_DISABLED,
    UI_PROMPT_MSG_STAT_TCP_SENDING,
    UI_PROMPT_MSG_STAT_TCP_RECEIVING,
    UI_PROMPT_MSG_STAT_TCP_CONNECTING,
    UI_PROMPT_MSG_STAT_TCP_CONNECTED,
    UI_PROMPT_MSG_STAT_TCP_DISCONNECTING,
    UI_PROMPT_MSG_STAT_TCP_DISCONNECTED,
    
    UI_PROMPT_MSG_STAT_GPRS_ACTIVATING,
    UI_PROMPT_MSG_STAT_GPRS_ACTIVATED,
    UI_PROMPT_MSG_STAT_GPRS_DEACTIVATING,
    UI_PROMPT_MSG_STAT_GPRS_DEACTIVATED,
    
    UI_PROMPT_MSG_STAT_GSM_ACTIVATING,
    UI_PROMPT_MSG_STAT_GSM_ACTIVATED,
    UI_PROMPT_MSG_STAT_GSM_DEACTIVATING,
    UI_PROMPT_MSG_STAT_GSM_DEACTIVATED,
    UI_PROMPT_MSG_STAT_GSM_SENDING,
    UI_PROMPT_MSG_STAT_GSM_RECEIVING,
    UI_PROMPT_MSG_STAT_GSM_RECEIVED,
    UI_PROMPT_MSG_STAT_GSM_CONNECTING,
    UI_PROMPT_MSG_STAT_GSM_CONNECTED,
    UI_PROMPT_MSG_STAT_GSM_DISCONNECTING,
    UI_PROMPT_MSG_STAT_GSM_DISCONNECTED,

    UI_PROMPT_MSG_STAT_PPP_CONNECTING,
    UI_PROMPT_MSG_STAT_PPP_CONNECTED,
    UI_PROMPT_MSG_STAT_PPP_DISCONNECTING,
    UI_PROMPT_MSG_STAT_PPP_DISCONNECTED,
    
    UI_PROMPT_MSG_END
}UI_PromptIdx_t;

/** Starts all user interface peripherals in the terminal ready for used by the application. This includes
 * the keyboard, the display and the touch screen peripherals.
 *
 * \return
 *      - \ref ERR_UI_DISPLAY_PERIPH_DISPLAY_NOT_OPEN = The display peripheral cannot be openned.
 *      - \ref ERR_UI_DISPLAY_PERIPH_KEYBOARD_NOT_OPEN = The keyboard peripheral cannot be openned.
 *      - \ref ERR_UI_DISPLAY_PERIPH_TFT_NOT_OPEN = The touch screen peripheral cannot be openned.
 */
int UI_PeriphStart( void );

/** Stops all user interface peripherals in the terminal. It gives up all handles acquired by the terminal
 * with the display and touch screen and the keyboard.
 *
 * \return
 *      - \ref ERR_UI_DISPLAY_PERIPH_DISPLAY_NOT_CLOSE = The display peripheral cannot be closed.
 *      - \ref ERR_UI_DISPLAY_PERIPH_KEYBOARD_NOT_CLOSE = The keyboard peripheral cannot be closed.
 *      - \ref ERR_UI_DISPLAY_PERIPH_TFT_NOT_CLOSE = The touch screen peripheral cannot be closed.
 */
int UI_PeriphStop( void );


/** Displays the menu of the sample application.
 *
 */
void UI_MenuMainDisplay( void );

/** Toggles the idle display's header/footer.
 * It makes sure that the header and footer are turned off. It will restore the
 * original state of the header/footer display when called the second time.
 */
void UI_IdleDispHdrFtrToggle( void );

/** Displays an error message.
 *
 * \pre The given error code should have been defined first. Only those defined in err.h.
 *
 * \param   errID   The error code defined in err.h. See \ref epuerrorid "Error Identifiers"
 *
 * \return
 *      None
 *  
 */
void UI_ErrMsgDisplay(int errID);

/** Displays a prompt message.
 * 
 * \param[in] promptID      The identifier of the prompt to be displayed.
 *
 * \note
 *      When the specified prompt ID does not exist, the function will display a default prompt
 *      message indicating an undefined prompt.
 */
void UI_PromptMsgDisplay(UI_PromptIdx_t promptID);
/** @} */

#ifdef __cplusplus
}
#endif

#endif // __UI_H__

