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
 Module  : FUN - Demo Features Unit

 @file      fun_demofeatures.h
 @brief     Contains all exported prototypes of FUN.
 @date      02/14/2013

 ------------------------------------------------------------------------------
 */

#ifndef __FUN_H__
#define __FUN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "par.h"
#include "DisplayAmount.h"

/** \addtogroup dfugroup FUN Demo Functions Unit
 *
 * Contains all functions that demonstrates the use of certain features specific
 * to the sample application, the main attraction on the source code of the application.
 *
 * @{
 */

/** Callback function for the service call CUSTOM_CARD_ENTRY
 * It customizes the waiting card scren from idle.
 *
 * \param[in] size data size
 * \param[in] infoscust defines the input wait card service properties
 *
 * \return
 *      - \ref None
 */
void FUN_ServiceCardEntry(int size, S_CUST_CARD_Entry *infoscust);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // __FUN_H__





