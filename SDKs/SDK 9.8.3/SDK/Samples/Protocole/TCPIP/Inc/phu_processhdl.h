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
   
 Project : TCP/IP Sample
 Module  : PHU - Process Handling Unit

 @file      phu_processhdl.h
 @brief     Contains all functions prototypes for PHU that executes processes 
            specific to the sample application. These processes may include but
            not limited to configuration of parameters, demo process, and so
            on.
            
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifndef __PHU_H__
#define __PHU_H__

/** \addtogroup phugroup PHU Process Handling Unit
 *
 * Contains all functions related to the handling of parameters of the sample application. 
 * This interfaces the functions that treats data in the file system of the terminal.
 * It maintains variables that holds the values the application parameters in RAM. 
 * It saves and retrieves contents of the parameter file whenever there are changes.
 *
 * @{
 */

/** Executes the parameter configuration process which will obtain the host name and
 * port number to connect to when executing the client test functionality of the sample
 * application.
 */
void phuParamConfigProcess( void );

/** Executes the client test processes.
 */
void phuTestClientProcess( void );

/** Executes the server test processes.
 */
void phuTestServerProcess( void );

/** Executes the network info display process.
 */
void phuTestNetInfoProcess( void );


/** @} */
#endif // __PMU_H__



