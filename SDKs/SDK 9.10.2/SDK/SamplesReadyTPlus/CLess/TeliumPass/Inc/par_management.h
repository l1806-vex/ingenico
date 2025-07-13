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
   
 Project : Telium Pass Sample
 Module  : PAR - Parameter Management Unit

 @file      par_management.h
 @brief     Contains all prototypes for user interfaces related to trace management
 @date      08/03/2013

 ------------------------------------------------------------------------------
 */

#ifndef __PAR_MANAGEMENT_H__
#define __PAR_MANAGEMENT_H__

#ifdef __cplusplus
extern "C" {
#endif

/** Convert a hexadecimal string hex into a binary buffer bin of length len. 
 * 
 * \param tlvTree (O) tl
 * \return
 *    - none
 */
void PAR_GetClessParameters(TLV_TREE_NODE tlvTree);

#ifdef __cplusplus
}
#endif

#endif // __PAR_MANAGEMENT_H__
