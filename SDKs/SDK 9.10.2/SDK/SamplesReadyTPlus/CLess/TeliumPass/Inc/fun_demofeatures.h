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
   
 Project : Telium Pass Sample
 Module  : FUN - Demo Features Unit

 @file      fun_demofeatures.h
 @brief     Contains all exported prototypes of FUN.
 @date      08/03/2013

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

/** Obtains all information regarding the Cless reader
 *
 * \return
 *      - \ref None
 */
void FUN_InfoTest(void);

/** Test the display capability of the Cless reader
 *
 * \return
 *      - \ref None
 */
void FUN_DisplayTest(int test);

/** Test the buzzer functionality of the Cless reader
 *
 * \return
 *      - \ref None
 */
void FUN_BuzzerTest(int test);

/** Test the leds functionality of the Cless reader
 *
 * \return
 *      - \ref None
 */
void FUN_LedsTest(int test);

/** Test the backlight functionality of the Cless reader
 *
 * \return
 *      - \ref None
 */
void FUN_BacklightTest(int test);

/** Perform soft or hard reset on the Cless reader
 *
 * \param[in] test test to be performed
 *
 * \return
 *      - \ref None
 */
void FUN_ResetTest(void);

/** Check the presence of a Cless reader
 *
 * \return
 *      - \ref None
 */
void FUN_CheckPresence(void);

/** Perform the following ISO14443-4 functionalities depending on the test number
 * - Detection
 * - Activation
 * - APDU Sending
 * - Deselection
 *
 * \param[in] test test to be performed
 *
 * \return
 *      - \ref None
 */
void FUN_IsoTest(int test);

/** Perform the following mifare functionalities depending on the test number
 * - Detection
 * - Activation
 * - Authentication
 * - Operations
 *
 * \param[in] test test to be performed
 *
 * \return
 *      - \ref None
 */
void FUN_MifareTest(int test);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // __FUN_H__





