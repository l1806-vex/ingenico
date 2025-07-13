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
   
 Project : GPRS Sample
 Module  : PARAM - Parameter Management Unit

 @file      param.h
 @brief     Contains all definitions of functions related to the handling of 
            parameters of the sample application. This interfaces the functions
            that treats data in the file system of the terminal. It maintains 
            variables that holds the values the application parameters in RAM.
            It saves and retrieves contents of the parameter file whenever 
            there are changes.
            
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifndef __PARAM_H__
#define __PARAM_H__

/** \addtogroup pmugroup PARAM Parameter Management Unit
 *
 * Contains all functions related to the handling of parameters of the sample application. 
 * This interfaces the functions that treats data in the file system of the terminal.
 * It maintains variables that holds the values the application parameters in RAM. 
 * It saves and retrieves contents of the parameter file whenever there are changes.
 *
 * @{
 */

/** Parameter ID's used to reference the parameters managed by PARAM.
 * The parameter ID's listed here must be defined in pmu_param.c.
 */
typedef enum
{
    PARAM_ID_START,
    PARAM_ID_APN,///< Apn to use for the GPRS to connect to which is of type PARAM_DATA_TYPE_STR.
    PARAM_ID_LOGIN,///< Login to use for the PPP server to connect to which is of type PARAM_DATA_TYPE_STR.
    PARAM_ID_PASSWORD,///< Passsword to use for the PPP server to connect to which is of type PARAM_DATA_TYPE_STR.
    PARAM_ID_HOST_NAME,///< Host name of the TCP/IP server to connect to which is of type PARAM_DATA_TYPE_STR.
    PARAM_ID_PORT,///< Port number where the TCP/IP server to connect to is listening. It is of type PARAM_DATA_TYPE_INT16
    PARAM_ID_PHONE_NUMBER,///< Phone number of the GSM server to connect to which is of type PARAM_DATA_TYPE_STR.
    PARAM_ID_BAUD_RATE,///< Baud rate modulation to be used for GSM which is of type PARAM_DATA_TYPE_INT16.
    PARAM_ID_RLP,///< The RLP Mode is the native GSM protocol for error detection and correction for GSM It is of type PARAM_DATA_TYPE_INT16.
    PARAM_ID_END
}PARAM_ParamID_t;

/** Data types indicating the data type of a certain parameter.
 */
typedef enum
{
    PARAM_DATA_TYPE_START,
    PARAM_DATA_TYPE_INT16,///< 16-bit signed integer value 
    PARAM_DATA_TYPE_INT32,///< 32-bit signed integer value
    PARAM_DATA_TYPE_INT64,///< 64-bit signed integer value
    PARAM_DATA_TYPE_BIN,///< binary value of any length
    PARAM_DATA_TYPE_STR,///< string value of any length
    PARAM_DATA_TYPE_END
}PARAM_ParamDataType_t;

/**
 * This is the declaration of parameter structure
 */
typedef struct 
{
    PARAM_ParamID_t paramID;
    PARAM_ParamDataType_t dataType;
    char *defData;
    char *data;
    int dataLen;
    int maxDataLen;
}PARAM_Param_t;

#define PARAM_HOST_PORT_VALUE_MAX 65536 ///< Maximum value of port number.

/** Initializes the parameter file of the sample application.
 */
int PARAM_ParamFileInit( void );

/** Obtains a parameter from database.
 *
 * \param (I) paramID The desired parameter ID to retrieve. See PARAM_ParamID_t.
 *
 * \return 
 *      - NULL when the parameter is not defined in the PARAM database.
 *      - Pointer to the parameter in the database.
 *
 */
PARAM_Param_t* PARAM_ParamGet( PARAM_ParamID_t paramID );

/** Stores the values pointed to by the input param to the internal variable
 * for parameters and then updates the parameter file.
 * 
 * \param (I) param     Pointer to PARAM_Param_t values. It should be initialized and filled
 *                      before calling the function.
 * \return
 *      - 0 when parameter update was successul.
 *      - -1 when parameter update was not successful.
 */
int PARAM_ParamSet(PARAM_ParamID_t paramID, char *data, int dataLen);

/** @} */
#endif // __PARAM_H__


