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

 @file      epu_errprocess.h
 @brief     Contains all exported prototypes of DFU.
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifndef __EPU_H__
#define __EPU_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "uiu_userinterface.h"

/** \addtogroup epugroup EPU Error Processing Unit
 *
 * Contains all functions and type definitions that handle errors specific 
 * to the sample application.
 *
 * @{
 */

/** \weakgroup epuerrorid Error Identifiers
 * 
 * List of error identifiers to be specified when calling UIU_ErrMsgDisplay().
 *
 * @{
 */

#define EPU_RET_OK                                   0///< Operation successful

/** \weakgroup epuerrorid_PHU PHU Error Codes
 * 
 * Error codes set by PHU.
 *
 * @{
 */

#define EPU_ERR_PHU_PROCESS_INVALID_PORT_NUM                    -(1)///< Invalid port number was entered on port number input dialog.


/** @} epuerrorid_PHU */

/** \weakgroup epuerrorid_DFU DFU Error Codes
 * 
 * Error codes set by DFU
 *
 * @{
 */

#define EPU_ERR_DFU_SSL_RES_TEMP_UNAVAILABLE            -(100) /**< SSL resources are temporarily unavailable */
#define EPU_ERR_DFU_SSL_INVALID_ARGUMENT                -(102) /**< Invalid argument to a function call to SSL library */
#define EPU_ERR_DFU_SSL_OUT_OF_RESOURCES                -(103) /**< SSL resources are insufficient for the current operation */
#define EPU_ERR_DFU_SSL_NO_SUCH_FILE_DIR                -(104) /**< The files linked to the created SSL profile cannot be located. */
#define EPU_ERR_DFU_SSL_INSUFFICIENT_MEMORY             -(105) /**< Memory is not enough for the current SSL operation. */
#define EPU_ERR_DFU_SSL_SOCKET_NOT_CONNECTED            -(106) /**< SSL operation not possible due to an unconnected socket. */
#define EPU_ERR_DFU_SSL_GENERAL_ERROR                   -(107) /**< Unknown error occured during an SSL operation */
#define EPU_ERR_DFU_SSL_BAD_CERT_FORMAT                 -(108) /**< The certificates linked to the SSL profile is badly formatted. */
#define EPU_ERR_DFU_SSL_CONNECTION_CLOSED               -(109) /**< SSL connection suddenly terminated by the server */
#define EPU_ERR_DFU_SSL_CONNECTION_FAILED               -(110) /**< SSL connection attempt failed. */
#define EPU_ERR_DFU_SSL_PROFILE_DELETION_FAILED         -(111) /**< SSL profile delete operation failed. */
#define EPU_ERR_DFU_SSL_PROFILE_CREATION_FAILED         -(112) /**< SSL profile creation operation failed. */
#define EPU_ERR_DFU_SSL_NO_PROFILE_FOUND                -(113) /**< There are no SSL profiles available in the terminal. */
#define EPU_ERR_DFU_SSL_PROFILE_NOT_FOUND               -(114) /**< SSL profile specified is missing */
#define EPU_ERR_DFU_SSL_CERTS_KEYS_NOT_LOADED           -(115) /**< SSL certificates and keys not loaded in the terminal. */
#define EPU_ERR_DFU_SSL_PROFILE_NOT_LOADED              -(116) /**< SSL profile have not been successfully loaded */
#define EPU_ERR_DFU_SSL_HANDLE_INIT_FAILED              -(117) /**< Call to SSL_New() failed */
#define EPU_ERR_DFU_SSL_HANDLE_CONNECT_FAILED           -(118) /**< Call to SSL_Connect() failed */


/** @} epuerrorid_DFU */

/** \weakgroup epuerrorid_PMU PMU Error Codes
 * 
 * Error codes set by PMU
 *
 * @{
 */


/** @} epuerrorid_PMU */


/** \weakgroup epuerrorid_UIU UIU Error Codes
 * 
 * Error codes set by UIU
 *
 * @{
 */

#define EPU_ERR_UIU_DISPLAY_PERIPH_DISPLAY_NOT_OPEN     -(200) /**< Opening of the display peripheral is not successful. */
#define EPU_ERR_UIU_DISPLAY_PERIPH_KEYBOARD_NOT_OPEN    -(201) /**< Opening of the keyboard peripheral is not successful. */
#define EPU_ERR_UIU_DISPLAY_PERIPH_TFT_NOT_OPEN         -(203) /**< Opening of the touch screen peripheral is not successful. */
#define EPU_ERR_UIU_DISPLAY_PERIPH_DISPLAY_NOT_CLOSE    -(204) /**< Closing of the display peripheral is not successful. */
#define EPU_ERR_UIU_DISPLAY_PERIPH_KEYBOARD_NOT_CLOSE   -(205) /**< Closing of the keyboard peripheral is not successful. */
#define EPU_ERR_UIU_DISPLAY_PERIPH_TFT_NOT_CLOSE        -(206) /**< Closing of the touch screen peripheral is not successful. */

/** @} epuerrorid_UIU */


/** \weakgroup epuerrorid_EPU EPU Error Codes
 * 
 * Error codes set by EPU.
 *
 * @{
 */

#define EPU_ERR_UNDEFINED                           -(500)/**< Error returned by EPU when error identifier specified is not in the list. */
/** @} epuerrorid_EPU*/

/** @} epuerrorid*/

/** \weakgroup epuexportedstruct Exported Type Definitions
 * 
 * List of exported structures by EPU to other modules.
 *
 * @{
 */

/** Error structure used only by UIU_ErrMsgDisplay().
 */
typedef struct EPU__error EPU_Error_t;

/** @} */

/** \weakgroup epuexportedfunc Exported Functions
 * 
 * List of functions exported by EPU
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
EPU_Error_t *EPU_ErrPromptElemGet(int errID);

/** Returns the error message description specified by error. This function
 * requires calling the function EPU_ErrPromptElemGet().
 *
 * \param[in] error Pointer to the variable obtained using EPU_ErrPromptElemGet().
 *
 * \return Prompt index as defined in \ref UIU_PromptIdx_t;
 */
UIU_PromptIdx_t EPU_ErrPromptIDGet(EPU_Error_t *error);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif


#endif // __EPU_H__


