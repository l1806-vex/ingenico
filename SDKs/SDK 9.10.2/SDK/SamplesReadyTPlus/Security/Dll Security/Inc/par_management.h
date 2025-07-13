/////////////////////////////////////////////////////////////////
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
 Module  : PAR - Parameter Management Unit

 @file      par_management.h
 @brief     Contains all prototypes for user interfaces related to trace management
 @date      13/03/2013

 ------------------------------------------------------------------------------
 */

#ifndef __PAR_MANAGEMENT_H__
#define __PAR_MANAGEMENT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "SEC_interface.h"

/** Obtain the PIN Key from the parameter database
 *
 * \param[out] buf    PIN Key buffer
 *
 * \return
 *      - PAR_OK when the parameter is obtained successfully.
 *      - Negative in case of error.
 */
int PAR_Pin_KeyGet(unsigned char * buf);

/** Obtain the MAC Key from the parameter database
 *
 * \param[out] buf    MAC Key buffer
 *
 * \return
 *      - PAR_OK when the parameter is obtained successfully.
 *      - Negative in case of error.
 */
int PAR_Mac_KeyGet(unsigned char * buf);

/** Obtain the Pin Master Key from the parameter database
 *
 * \param[out] buf    Pin Master Key buffer
 *
 * \return
 *      - PAR_OK when the parameter is obtained successfully.
 *      - Negative in case of error.
 */
int PAR_PinMaster_KeyGet(unsigned char * buf);

/** Obtain the MAC Master Key from the parameter database
 *
 * \param[out] buf    MAC Master Key buffer
 *
 * \return
 *      - PAR_OK when the parameter is obtained successfully.
 *      - Negative in case of error.
 */
int PAR_MacMaster_KeyGet(unsigned char * buf);

/** Obtain the Root Key from the parameter database
 *
 * \param[out] buf    Root Key buffer
 *
 * \return
 *      - PAR_OK when the parameter is obtained successfully.
 *      - Negative in case of error.
 */
int PAR_Root_KeyGet(unsigned char * buf);

/** Obtain the Secure Part Area from the parameter database
 *
 * \param[in] idx    Secure Part Index
 * \param[out] secPart    Secure Part Area

 *
 * \return
 *      - PAR_OK when the parameter is obtained successfully.
 *      - Negative in case of error.
 */
int PAR_SecurePartGet(int idx, T_SEC_PARTTYPE * secPart);

/** Obtain the Peripheral Booster from the parameter database
 *
 * \param[in] idx    Secure Part Index
 * \param[out] periph    Peripheral Booster to be used

 *
 * \return
 *      - PAR_OK when the parameter is obtained successfully.
 *      - Negative in case of error.
 */
int PAR_PeriphBoosterGet(int idx, char ** periph);

/** Obtain the Booster from the parameter database
 *
 * \param[in] idx    Secure Part Index
 * \param[out] booster    Booster to be used

 *
 * \return
 *      - PAR_OK when the parameter is obtained successfully.
 *      - Negative in case of error.
 */
int PAR_BoosterGet(int idx, char * booster);

#ifdef __cplusplus
}
#endif

#endif // __PAR_MANAGEMENT_H__
