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
 Module  : PMU - Parameter Management Unit

 @file      pmu_parammngt.h
 @brief     Contains all definitions of functions related to the handling of 
            parameters of the sample application. This interfaces the functions
            that treats data in the file system of the terminal. It maintains 
            variables that holds the values the application parameters in RAM.
            It saves and retrieves contents of the parameter file whenever 
            there are changes.
            
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifndef __PMU_H__
#define __PMU_H__

/** \addtogroup pmugroup PMU Parameter Management Unit
 *
 * Contains all functions related to the handling of parameters of the sample application. 
 * This interfaces the functions that treats data in the file system of the terminal.
 * It maintains variables that holds the values the application parameters in RAM. 
 * It saves and retrieves contents of the parameter file whenever there are changes.
 *
 * @{
 */

#define PMU_HOST_NAME_LEN_MAX 40 ///< Maximum lenght of host name.
#define PMU_HOST_PORT_NUM_LEN_MAX 5 ///< Maximum length  of port number.
#define PMU_HOST_PORT_VALUE_MAX 65536 ///< Maximum value of port number.


/**
 * This is the declaration of PMU__param specific to the TCP/IP sample appli-
 * cation.
 */
typedef struct PMU__param 
{
    char host[PMU_HOST_NAME_LEN_MAX+1];///< Holds the host name parameter for the client test
    int port;///< Holds the port used during client test
}PMU_Param_t;


/** Initializes the parameter file of the sample application.
 */
int PMU_ParamFileInit( void );

/** Returns the pointer to the parameter structure of the sample application
 */
PMU_Param_t* PMU_ParamGet( void );

/** Stores the values pointed to by the input param to the internal variable
 * for parameters and then updates the parameter file.
 * 
 * \param (I) param     Pointer to PMU_Param_t values. It should be initialized and filled
 *                      before calling the function.
 * \return
 *      - 0 when parameter update was successul.
 *      - -1 when parameter update was not successful.
 */
int PMU_ParamSet( PMU_Param_t *param);


/** @} */
#endif // __PMU_H__


