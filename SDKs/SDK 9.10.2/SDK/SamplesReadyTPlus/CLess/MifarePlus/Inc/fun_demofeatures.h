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
 Module  : FUN - Demo Features Unit

 @file      fun_demofeatures.h
 @brief     Contains all exported prototypes of FUN.
 @date      21/03/2013

 ------------------------------------------------------------------------------
 */

#ifndef __FUN_H__
#define __FUN_H__

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup dfugroup FUN Demo Functions Unit
 *
 * Contains all functions that demonstrates the use of certain features specific
 * to the sample application, the main attraction on the source code of the application.
 *
 * @{
 */

/** Personalize a mifare plus card
 * Change the security level of the mifare plus card from SL0 to SL1
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
int FUN_MfpPersonalizeSL0toSL1(void);

/** Personalize a mifare plus card
 * Change the security level of the mifare plus card from SL1 to SL2
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
int FUN_MfpPersonalizeSL1toSL2(void);

/** Personalize a mifare plus card
 * Change the security level of the mifare plus card from SL2 to SL3
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
int FUN_MfpPersonalizeSL2toSL3(void);

/** Perform the following mifare plus functionalities in Security Level 3 without SAM
 * - ClessMFP_SL3ProximityCheck
 * - ClessMFP_SL3Authenticate
 * - ClessMFP_SL3Write
 * - ClessMFP_SL3Read
 * - ClessMFP_SL3ValueOperation
 * - ClessMFP_SL3ValueOperation
 *
 * \param[in] test test to be performed
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
int FUN_MifareSL3(void);

/** Perform the following mifare plus functionalities in Security Level 3 with SAM
 * - ClessMFP_SL3ProximityCheckWithSAM
 * - ClessMFP_SL3AuthenticateWithSAM
 * - ClessMFP_SL3Write	
 * - ClessMFP_SL3Read
 * - ClessMFP_SL3ValueOperation
 *
 * \param[in] test test to be performed
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
int FUN_MifareSL3WithSAM(void);

/** Perform the following mifare plus functionalities in Security Level 2 with SAM
 * - ClessMFP_SL2AuthenticateAESWithSAM
 * - ClessMFP_SL12AuthenticateClassicWithSAM
 * - ClessMFP_SL2WriteMultiBlock
 * - ClessMFP_SL2ReadMultiBlock
 * - ClessMFP_SL12ValueOperation
 *
 * \param[in] test test to be performed
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
int FUN_MifareSL2WithSAM(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // __FUN_H__





