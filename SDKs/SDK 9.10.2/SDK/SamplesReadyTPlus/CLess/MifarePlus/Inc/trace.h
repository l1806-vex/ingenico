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
 Module  : TRC - Trace Management Unit

 @file      trace.h
 @brief     Contains all prototypes for user interfaces related to trace management
 @date      21/03/2013

 ------------------------------------------------------------------------------
 */

#ifndef __TRC_MANAGEMENT_H__
#define __TRC_MANAGEMENT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "trc.h"

/** \addtogroup trcgroup TRC Trace Management Unit
 * @{
 */

/** \weakgroup trcmanagement Trace Management
 * @{
 */

/** Initialize the trace management.
 *
 */
void TRC_Init(void);

/** Obtain the trace handle.
 *
 * \return  Pointer to an error definition in the list.
 */
TRC_Trace_t TRC_HandleGet(void);

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif // __TRC_MANAGEMENT_H__

