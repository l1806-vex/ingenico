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
 Module  : FUN - Functional Demo Unit

 @file      fun_gprs.h
 @brief     Contains all exported prototypes of FUN.
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifndef __FUN_GPRS_H__
#define __FUN_GPRS_H__

/** \addtogroup dfugroup FUN Demo Functions Unit
 *
 * Contains all functions that demonstrates the use of certain features specific
 * to the sample application, the main attraction on the source code of the application.
 *
 * @{
 */

/** Maps the error code returned by GPRS library to ERR error codes.
 *
 * \param[in] err   Error code returned by functions exported by the GPRS library.
 *
 * \return
 *      - GPRS/GSM error codes as defined in err.h.
 */
int _FUN_GprsErrorMap(int err);

/** Obtains the status of the GPRS network whether it is available already for
 * establishing a connection.
 *
 * \return
 *      - \ref ERR_RET_OK = GPRS network ready for connection.
 *      - \ref ERR_FUN_GPRS_TIMEOUT = Checking of status of the GPRS network timed out.
 *      - \ref ERR_FUN_GPRS_NETWORK_NOT_AVAILABLE = GPRS network is not available.
 */
int _FUN_GprsStatusGet( void );

/** Obtains the currently set APN used by the FUN_GPRS submodule.
 *
 * \return
 *      - Pointer to the APN currently used.
 */
char* _FUN_GprsApnGet( void );

/** @} */
#endif // __FUN_H__




