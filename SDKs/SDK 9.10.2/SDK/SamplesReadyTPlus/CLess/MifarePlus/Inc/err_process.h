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
 Module  : ERR - Error Processing Unit

 @file      errprocess.h
 @brief     Contains all exported prototypes of FUN.
 @date      21/03/2013

 ------------------------------------------------------------------------------
 */

#ifndef __ERR_H__
#define __ERR_H__

#include "ui_userinterface.h"

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

/** \weakgroup epuerrorid_PAR PAR Error Codes
 * 
 * Error codes set by PAR
 *
 * @{
 */

#define ERR_PAR_FILE_NOT_FOUND      -(100)///< Parameter file not found.

/** @} */

/** \weakgroup epuerrorid_FUN FUN Error Codes
 * 
 * Error codes set by FUN
 *
 * @{
 */

#define ERR_UNDEFINED                           -(500)///< Error returned by ERR when error identifier specified is not in the list.
#define ERR_TPASS_NOT_CONNECTED      -(501)///< Error returned by ERR when TELIUM PASS is not connected.
#define ERR_OPEN_DRIVER_FAILED          -(502)///< Error returned by ERR when opening of cless driver failed.
#define ERR_NO_CARD_DETECTED            -(503)///< Error returned by ERR when no card is detected.
#define ERR_TOO_MANY_CARDS                -(504)///< Error returned by ERR when too many cards are detected.
#define ERR_INVALID_CARD                      -(505)///< Error returned by ERR when an invalid card is detected.
#define ERR_DETECTION_ERROR                -(506)///< Error returned by ERR when a detection error occured.
#define ERR_TIMEOUT                                -(507)///< Error returned by ERR when a card detection timeout occured.
#define ERR_NOT_MIFARE_CARD               -(508)///< Error returned by ERR when a card detected is not mifare.
#define ERR_PAR_ERROR                           -(509)///< Error returned by ERR when the value of the parameter(s) is invalid.
#define ERR_MAC_VERIFICATION              -(510)///< Error returned by ERR when verification of the PICC MAC failed
#define ERR_AUTHENTICATION                 -(511)///< Error returned by ERR when authentication failed
#define ERR_PICC_COMMS                         -(512)///< Error returned by ERR when there is a communication error with PICC
#define ERR_COMMS_TIMEOUT                  -(513)///< Error returned by ERR when there is a communication timeout
#define ERR_INVALID_VALUE                    -(514)///< Error returned by ERR when the value block has an error
#define ERR_VALUE_ADD_WARNING          -(515)///< Error returned by ERR when the address byte of value block doesn't match the current block number
#define ERR_PROCESSING                          -(516)///< Error returned by ERR when the library has a processing error
#define ERR_CRYPTO                                  -(517)///< Error returned by ERR when the library has a crypto processing error
#define ERR_SAM                                       -(518)///< Error returned by ERR when SAM has an error
#define ERR_PC_TIME                                -(519)///< Error returned by ERR when the Proximity Check time verification failed
#define ERR_STATE                                    -(520)///< Error returned by ERR when the current state doesn't allow the command execution
#define ERR_RESPONSE                              -(521)///< Error returned by ERR when the response has an error
#define ERR_DLL_NOT_LOADED                 -(522)///< Error returned by ERR when the Mifare Plus DLL is not loaded

/** @} */
/** @} */

/** \weakgroup epuexportedstruct Exported Type Definitions
 * 
 * List of exported structures by ERR to other modules.
 *
 * @{
 */

/** Error structure used only by UI_ErrMsgDisplay().
 */
typedef struct ERR_prompt ERR_Prompt_t;

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
 * \param (I) errID The identifier of the error. See error identifiers.
 *
 * \return  Pointer to an error definition in the list.
 */
ERR_Prompt_t *ERR_PromptElemGet(int errID);

/** Returns the error message description specified by error. This function
 * requires calling the function ERR_PromptElemGet().
 *
 * \param (I) error Pointer to the variable obtained using ERR_PromptElemGet().
 *
 * \return Prompt index as defined in \ref UI_PromptIdx_t;
 */
UI_PromptIdx_t ERR_PromptIDGet(ERR_Prompt_t *error);

/** @} */

/** @} */

#endif // __ERR_H__


