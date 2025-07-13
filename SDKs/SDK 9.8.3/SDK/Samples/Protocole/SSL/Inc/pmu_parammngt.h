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
   
 Project : SSL Sample
 Module  : PMU - Parameter Management Unit

 @file      pmu_parammngt.h
 @brief     Contains all definitions of functions related to the handling of 
            parameters of the sample application. This interfaces the functions
            that treats data in the file system of the terminal. It maintains 
            variables that holds the values the application parameters in RAM.
            It saves and retrieves contents of the parameter file whenever 
            there are changes.
            
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifndef __PMU_H__
#define __PMU_H__

#ifdef __cplusplus
extern "C" {
#endif


/** \addtogroup pmugroup PMU Parameter Management Unit
 *
 * Contains all functions related to the handling of parameters of the sample application. 
 * This interfaces the functions that treats data in the file system of the terminal.
 * It maintains variables that holds the values the application parameters in RAM. 
 * It saves and retrieves contents of the parameter file whenever there are changes.
 *
 * @{
 */

/** Parameter ID's used to reference the parameters managed by PMU.
 * The parameter ID's listed here must be defined in pmu_param.c.
 */
typedef enum
{
    PMU_PARAM_ID_START,
    PMU_PARAM_ID_HOST_NAME,///< Host name of the SSL server to connect to which is of type PMU_PARAM_DATA_TYPE_STR.
    PMU_PARAM_ID_PORT,///< Port number where the SSL server to connect to is listening. It is of type PMU_PARAM_DATA_TYPE_INT16
    PMU_PARAM_ID_SSL_PROFILE,///< The SSL profile used to connect to the SSL server. It is of type PMU_PARAM_DATA_TYPE_STR.
    PMU_PARAM_ID_END
}PMU_ParamID_t;

/** Data types indicating the data type of a certain parameter.
 */
typedef enum
{
    PMU_PARAM_DATA_TYPE_START,
    PMU_PARAM_DATA_TYPE_INT16,///< 16-bit signed integer value 
    PMU_PARAM_DATA_TYPE_INT32,///< 32-bit signed integer value
    PMU_PARAM_DATA_TYPE_INT64,///< 64-bit signed integer value
    PMU_PARAM_DATA_TYPE_BIN,///< binary value of any length
    PMU_PARAM_DATA_TYPE_STR,///< string value of any length
    PMU_PARAM_DATA_TYPE_END
}PMU_ParamDataType_t;

/**
 * This is the declaration of parameter structure
 */
typedef struct 
{
    PMU_ParamID_t paramID;
    PMU_ParamDataType_t dataType;
    char *defData;
    char *data;
    int dataLen;
    int maxDataLen;
}PMU_Param_t;

#define PMU_HOST_PORT_VALUE_MAX 65536 ///< Maximum value of port number.

/** Initializes the parameter file of the sample application.
 */
int PMU_ParamFileInit( void );

/** Obtains a parameter from database.
 *
 * \param[in] paramID The desired parameter ID to retrieve. See PMU_ParamID_t.
 *
 * \return 
 *      - NULL when the parameter is not defined in the PMU database.
 *      - Pointer to the parameter in the database.
 *
 */
PMU_Param_t* PMU_ParamGet( PMU_ParamID_t paramID );

/** Stores the values pointed to by the input param to the internal variable
 * for parameters and then updates the parameter file.
 * 
 * \param[in] param     Pointer to PMU_Param_t values. It should be initialized and filled
 *                      before calling the function.
 * \return
 *      - 0 when parameter update was successul.
 *      - -1 when parameter update was not successful.
 */
int PMU_ParamSet(PMU_ParamID_t paramID, char *data, int dataLen);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // __PMU_H__


