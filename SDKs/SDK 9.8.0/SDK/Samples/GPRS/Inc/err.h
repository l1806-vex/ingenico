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
 @brief     Contains all exported prototypes of ERR module.
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifndef __ERR_H__
#define __ERR_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "ui.h"

/** \addtogroup epugroup ERR Error Processing Unit
 *
 * Contains all functions and type definitions that handle errors specific 
 * to the sample application.
 *
 * @{
 */

/** \weakgroup epuerrorid Error Identifiers
 * 
 * List of error identifiers to be specified when calling UI_ErrMsgDisplay().
 *
 * @{
 */

#define ERR_RET_OK                                   0///< Operation successful

/** \weakgroup epuerrorid_FLOW FLOW Error Codes
 * 
 * Error codes set by FLOW.
 *
 * @{
 */

#define ERR_FLOW_PROCESS_INVALID_PORT_NUM                    -(1)///< Invalid port number was entered on port number input dialog.


/** @} epuerrorid_FLOW */

/** \weakgroup epuerrorid_FUN FUN Error Codes
 * 
 * Error codes set by FUN
 *
 * @{
 */

/** \weakgroup epuerrorid_FUN_GPRS GPRS Error Codes
 * 
 * Error codes set by GPRS.
 *
 * @{
 */

#define ERR_FUN_GPRS_NO_SIM                 -(100) /**< No SIM card inserted on the slot */
#define ERR_FUN_GPRS_NO_PIN                 -(102) /**< No PIN set */
#define ERR_FUN_GPRS_BAD_PIN                -(103) /**< Invalid PIN code */
#define ERR_FUN_GPRS_SIM_LOCK               -(104) /**< The SIM card has been locked */
#define ERR_FUN_GPRS_FATAL                  -(105) /**< GPRS encountered a fatal error and could not continue. */
#define ERR_FUN_GPRS_UNKNOWN                -(106) /**< GPRS module encountered an unknown error */
#define ERR_FUN_GPRS_TIMEOUT                -(107) /**< Waiting for the GPRS network status timed out. */
#define ERR_FUN_GPRS_NETWORK_NOT_AVAILABLE  -(108) /**< GPRS network is not available*/
#define ERR_FUN_GPRS_NULL_POINTER           -(109) /**< Function received a NULL pointer parameter*/
#define ERR_FUN_CONNECT_TIMEOUT             -(110) /**< Connection timeout*/
#define ERR_FUN_GPRS_NETWORK_UNAVAILABLE                     -(112) /**< GPRS network is not enabled*/

/** @} epuerrorid_FUN_GPRS */

/** \weakgroup epuerrorid_FUN_GSM GSM Error Codes
 * 
 * Error codes set by GSM.
 *
 * @{
 */

#define ERR_FUN_GSM_ENABLE  -                   -(120) /**< GSM network is not enabled*/
#define ERR_FUN_GSM_NETWORK_NOT_AVAILABLE       -(121) /**< GSM network is not available */
#define ERR_FUN_GSM_TIMEOUT                     -(122) /**< Waiting for the GSM network status timed out */
#define ERR_FUN_GSM_CON_TEST_START              -(123) /**< GSM connectivity test GSM start failed*/
#define ERR_FUN_GSM_CON_TEST_SEND               -(124) /**< GSM connectivity test sending failed*/
#define ERR_FUN_GSM_CON_TEST_RECV               -(125) /**< GSM connectivity test receiving failed*/
#define ERR_FUN_GSM_CON_TEST_CONNECT            -(126) /**< GSM connectivity test modem connection failed */


/** @} epuerrorid_FUN_GSM */

/** \weakgroup epuerrorid_FUN_PPP PPP Error Codes
 * 
 * Error codes set by PPP.
 *
 * @{
 */

#define ERR_FUN_PPP_AUTH_TIMEOUT            -(140) /**< PPP authentication timed out */
#define ERR_FUN_PPP_AUTH_FAILED             -(141) /**< PPP authentication failed */
#define ERR_FUN_PPP_CONNECT_FAILED          -(142) /**< PPP connection error*/


/** @} epuerrorid_FUN_PPP */

/** \weakgroup epuerrorid_FUN_TCP TCP Error Codes
 * 
 * Error codes set by TCP.
 *
 * @{
 */

#define ERR_FUN_TCP_RECEIVE_FAILED          -(160) /**< TCP data reception failed */
#define ERR_FUN_TCP_SEND_FAILED             -(161) /**< TCP data transmission failed */
#define ERR_FUN_TCP_CONNECTION_FAILED       -(162) /**< TCP connection to server failed*/

/** @} epuerrorid_FUN_TCP */

/** @} epuerrorid_FUN */

/** \weakgroup epuerrorid_PARAM PARAM Error Codes
 * 
 * Error codes set by PARAM
 *
 * @{
 */


/** @} epuerrorid_PARAM */


/** \weakgroup epuerrorid_UI UI Error Codes
 * 
 * Error codes set by UI
 *
 * @{
 */

#define ERR_UI_DISPLAY_PERIPH_DISPLAY_NOT_OPEN     -(200) /**< Opening of the display peripheral is not successful. */
#define ERR_UI_DISPLAY_PERIPH_KEYBOARD_NOT_OPEN    -(201) /**< Opening of the keyboard peripheral is not successful. */
#define ERR_UI_DISPLAY_PERIPH_TFT_NOT_OPEN         -(203) /**< Opening of the touch screen peripheral is not successful. */
#define ERR_UI_DISPLAY_PERIPH_DISPLAY_NOT_CLOSE    -(204) /**< Closing of the display peripheral is not successful. */
#define ERR_UI_DISPLAY_PERIPH_KEYBOARD_NOT_CLOSE   -(205) /**< Closing of the keyboard peripheral is not successful. */
#define ERR_UI_DISPLAY_PERIPH_TFT_NOT_CLOSE        -(206) /**< Closing of the touch screen peripheral is not successful. */

/** @} epuerrorid_UI */


/** \weakgroup epuerrorid_ERR ERR Error Codes
 * 
 * Error codes set by ERR.
 *
 * @{
 */

#define ERR_UNDEFINED                           -(500)/**< Error returned by ERR when error identifier specified is not in the list. */
/** @} epuerrorid_ERR*/

/** @} epuerrorid*/

/** \weakgroup epuexportedstruct Exported Type Definitions
 * 
 * List of exported structures by ERR to other modules.
 *
 * @{
 */

/** Error structure used only by UI_ErrMsgDisplay().
 */
typedef struct ERR__error ERR_Error_t;

/** @} */

/** \weakgroup epuexportedfunc Exported Functions
 * 
 * List of functions exported by ERR
 *
 * @{
 */

/** Retrieves the specific error details. If the specified
 * error identifier is not found in the error list it will
 * return a pointer that says undefined error.
 *
 * \param[in] errID The identifier of the error. See error identifiers.
 *
 * \return
 *  - Pointer to an error definition in the list.
 */
ERR_Error_t *ERR_PromptElemGet(int errID);

/** Returns the error message description specified by error. This function
 * requires calling the function ERR_PromptElemGet().
 *
 * \param[in] error Pointer to the variable obtained using ERR_PromptElemGet().
 *
 * \return Prompt index as defined in \ref UI_PromptIdx_t;
 */
UI_PromptIdx_t ERR_PromptIDGet(ERR_Error_t *error);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif


#endif // __ERR_H__


