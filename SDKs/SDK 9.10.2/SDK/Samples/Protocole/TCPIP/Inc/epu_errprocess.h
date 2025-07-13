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
 Module  : EPU - Error Processing Unit

 @file      epu_errprocess.h
 @brief     Contains all exported prototypes of DFU.
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifndef __EPU_H__
#define __EPU_H__

#include "uiu_prompt.h"

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

/** \weakgroup epuerrorid_PHU PHU Error Codes
 * 
 * Error codes set by PHU.
 *
 * @{
 */

#define EPU_ERR_INVALID_PORT_NUM                    -(1)///< Invalid port number was entered on port number input dialog.
/** @} */

/** \weakgroup epuerrorid_DFU DFU Error Codes
 * 
 * Error codes set by DFU
 *
 * @{
 */
#define EPU_ERR_CLIENT_TEST_CONNECTION_FAILED       -(100)///< Error when connecting to the server during client-test.
#define EPU_ERR_CLIENT_TEST_UNKNOWN_HOST            -(101)///< Error when the DNS name cannot be resolved.
#define EPU_ERR_CLIENT_TEST_SOCKET_FAILED           -(102)///< Client Test Socket creation encountered an error.
#define EPU_ERR_CLIENT_TEST_SEND_FAILED             -(103)///< Sending failed
#define EPU_ERR_SERVER_TEST_SOCKET_FAILED           -(104)///< Server Test scoket creation failed.
#define EPU_ERR_SERVER_TEST_BINDING_FAILED          -(105)///< Server Test socket binding failed.
#define EPU_ERR_SERVER_TEST_LISTEN_FAILED           -(106)///< Server Test socket listening parameters configuration failed.
#define EPU_ERR_SERVER_TEST_ACCEPT_FAILED           -(107)///< Server Test scoket accept failed - waiting of client connection not possible.
/** @} */

/** \weakgroup epuerrorid_EPU EPU Error Codes
 * 
 * Error codes set by DFU
 *
 * @{
 */

#define EPU_ERR_UNDEFINED                           -(500)///< Error returned by EPU when error identifier specified is not in the list.
/** @} */
/** @} */

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
 * \param (I) errID The identifier of the error. See error identifiers.
 *
 * \return  Pointer to an error definition in the list.
 */
EPU_Error_t *EPU_ErrPromptElemGet(int errID);

/** Returns the error message description specified by error. This function
 * requires calling the function EPU_ErrPromptElemGet().
 *
 * \param (I) error Pointer to the variable obtained using EPU_ErrPromptElemGet().
 *
 * \return Prompt index as defined in \ref UIU_PromptIdx_t;
 */
UIU_PromptIdx_t EPU_ErrPromptIDGet(EPU_Error_t *error);

/** @} */

/** @} */

#endif // __EPU_H__


