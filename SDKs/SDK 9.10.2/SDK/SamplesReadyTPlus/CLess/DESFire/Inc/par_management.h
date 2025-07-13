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
   
 Project : Desfire Sample
 Module  : PAR - Parameter Management Unit

 @file      par_management.h
 @brief     Contains all prototypes for user interfaces related to trace management
 @date      21/03/2013

 ------------------------------------------------------------------------------
 */

#ifndef __PAR_MANAGEMENT_H__
#define __PAR_MANAGEMENT_H__

#ifdef __cplusplus
extern "C" {
#endif


/** Obtain the Key A from the parameter database
 *
 * \param[out] buf    Key A buffer
 *
 * \return
 *      - PAR_OK when the parameter is obtained successfully.
 *      - Negative in case of error.
 */
int PAR_KeyAGet(unsigned char * buf);

/** Obtain the Key B from the parameter database
 *
 * \param[out] buf    Key B buffer
 *
 * \return
 *      - PAR_OK when the parameter is obtained successfully.
 *      - Negative in case of error.
 */
int PAR_KeyBGet(unsigned char * buf);

/** Obtain the Key C from the parameter database
 *
 * \param[out] buf    Key C buffer
 *
 * \return
 *      - PAR_OK when the parameter is obtained successfully.
 *      - Negative in case of error.
 */
int PAR_KeyCGet(unsigned char * buf);

#ifdef __cplusplus
}
#endif

#endif // __PAR_MANAGEMENT_H__
