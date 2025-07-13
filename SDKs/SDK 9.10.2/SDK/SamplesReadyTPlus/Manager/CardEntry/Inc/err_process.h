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
   
 Project : Card Entry Sample
 Module  : ERR - Error Processing Unit

 @file      errprocess.h
 @brief     Contains all exported prototypes of FUN.
 @date      02/14/2013

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


