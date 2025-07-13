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

 Project : Service 100 Sample
 Module  : FUN - Demo Features Unit

 @file      fun_Service100.h
 @brief     Contains all definitions of functions utilized for Service 100.
 @date      03/11/2013

 ------------------------------------------------------------------------------
 */

#ifndef __FUN_H__
#define __FUN_H__
#ifdef __cplusplus
extern "C"
{
#endif
   /** \addtogroup FUN Dual Sim Demo Features Unit
    *
    * @{
    */


   /** Dual SIM management:
    * Switch between SIM 1 and SIM2,GPRS configuration and TCP communication.
    *
    *
    *
    */
   void FUN_DualSim(void);
   /** @} */

#ifdef __cplusplus
}
#endif

#endif // __FUN_H__
