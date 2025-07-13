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
   
 Project : Dll Security Sample
 Module  : FUN - Demo Features Unit

 @file      fun_demofeatures.h
 @brief     Contains all exported prototypes of FUN.
 @date      13/03/2013

 ------------------------------------------------------------------------------
 */

#ifndef __FUN_H__
#define __FUN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "par.h"

/** \addtogroup dfugroup FUN Demo Functions Unit
 *
 * Contains all functions that demonstrates the use of certain features specific
 * to the sample application, the main attraction on the source code of the application.
 *
 * @{
 */

/** Modify the configuration of secure parts according to the secure functionalities
 * and available peripherals
 *
 * \return
 *      - \ref None
 */
int FUN_SetConfig(void);

/** List the Id's of the secret areas used
 *
 * \param[in] idx secure part to be used
 *
 * \return
 *      - \ref None
 */
int FUN_ListSecretArea(int idx);

/** Create a secret area in the terminal
 *
 * \param[in] idx secure part to be used
 *
 * \return
 *      - \ref None
 */
int FUN_CreateSecretArea(int idx);

/** Free the secret area in the terminal
 * If the area is in C_SEC_PINCODE, Loaded PIN key and PIN Master Key will be removed
 * If the area is in C_SEC_CIPHERING, Loaded MAC Key and MAC Master Key will be removed
 *
 * \param[in] idx secure part to be used
 *
 * \return
 *      - \ref None
 */
int FUN_FreeSecretArea(int idx);

/** Load the root key
 * If loading is successful, it will be used in loading the PIN/MAC Keys
 *
 * \param[in] idx secure part to be used
 *
 * \return
 *      - \ref None
 */
int FUN_LoadRootKey	(int idx);

/** Load the PIN Key and the PIN Master Key
 * If loading is successful, these keys will be used for PIN Entry
 *
 * \return
 *      - \ref None
 */
int FUN_LoadPinKey(void);

/** Load the MAC Key and the MAC Master Key
 * If loading is successful, these keys will be used for MAC Calculation
 *
 * \return
 *      - \ref None
 */
int FUN_LoadMacKey(void);

/** PIN Enrtry using GOAL
 * If PIN entry is successful, PIN Block will be obtained
 *
 * \return
 *      - \ref None
 */
int FUN_PinEntry(void);

/** Encipher the PIN according to ISO9564 (ANSI X9.8)
 *
 * \return
 *      - \ref None
 */
int FUN_EncipherPin(void);

/** Compute MAC with DES/TDES ciphering algorithm in CBC mode
 *
 * \return
 *      - \ref None
 */
int FUN_MacCalculation(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // __FUN_H__





