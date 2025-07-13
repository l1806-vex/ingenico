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
 Module  : FLOW - Process Handling Unit

 @file      flow.h
 @brief     Contains all functions prototypes for FLOW that executes processes 
            specific to the sample application. These processes may include but
            not limited to configuration of parameters, demo process, and so
            on.
            
 @date      30/4/2013

 ------------------------------------------------------------------------------
 */

#ifndef __FLOW_H__
#define __FLOW_H__


#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup phugroup FLOW Process Handling Unit
 *
 * Contains all functions related to the handling of parameters of the sample application. 
 * This interfaces the functions that treats data in the file system of the terminal.
 * It maintains variables that holds the values the application parameters in RAM. 
 * It saves and retrieves contents of the parameter file whenever there are changes.
 *
 * @{
 */

/** Executes the parameter configuration process to change the output
 * stream of the trace
 */
void FLOW_ParamConfigTraceProcess(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // __PARAM_H__

