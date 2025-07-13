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

 @file      pmu_param.c
 @brief     Contains definitions of APIs specific to sample parameters to be 
            stored in file.
            
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "sdk30.h"
#include "utilities.h"
#include "pmu_parammngt.h"


#define _PMU_HOST_NAME_LEN_MAX           40 ///< Maximum lenght of host name.
#define _PMU_HOST_PORT_NUM_LEN_MAX       5 ///< Maximum length  of port number.


#define _PMU_DEFAULT_VALUE_HOST_NAME     "192.168.2.224"
#define _PMU_DEFAULT_VALUE_HOST_PORT     "8000"
#define _PMU_DEFAULT_VALUE_SSL_PROFILE   "PROFILE_00"


/** Filename of the SSL Sample parameter file.
 */
#define _PMU_PARAM_FILENAME_SSL                "SSL"

/** This is the variable that contains the list of parameters to be stored in
 * a parameter file. Some data members are initialized dynamically and others
 * are fixed and cannot be changed.
 */
PMU_Param_t paramList[] =
    {
        {
            .paramID = PMU_PARAM_ID_HOST_NAME,
            .dataType = PMU_PARAM_DATA_TYPE_STR,
            .defData = _PMU_DEFAULT_VALUE_HOST_NAME,
            .dataLen = 0, // This element will be initialized properly dynamically.
            .maxDataLen = _PMU_HOST_NAME_LEN_MAX
        },
        {
            .paramID = PMU_PARAM_ID_PORT,
            .dataType = PMU_PARAM_DATA_TYPE_INT16,
            .defData = _PMU_DEFAULT_VALUE_HOST_PORT,
            .dataLen = 0, // This element will be initialized properly dynamically.
            .maxDataLen = _PMU_HOST_PORT_NUM_LEN_MAX,
        },
        {
            .paramID = PMU_PARAM_ID_SSL_PROFILE,
            .dataType = PMU_PARAM_DATA_TYPE_INT16,
            .defData = _PMU_DEFAULT_VALUE_SSL_PROFILE,
            .dataLen = 0, // This element will be initialized properly dynamically.
            .maxDataLen = 10
        },

    };

/** Retrieves all the parameter values from file and loads it to memory.
 *
 *  \return
 *      - Number of parameters successfully obtained from the parameter file.
 *
 * \note
 *      -   The number of parameters to be retrieved is dependent on the number
 *          of parameters listed in \ref paramList variable at compile time.
 */
static int _PMU_ParamFromFileRetrieve( void )
{
    int ret;
    int ctr;
    char *data = NULL;
    int errCtr = 0;

    for(ctr = 0; ctr < sizeof(paramList)/sizeof(PMU_Param_t); ctr++)
    {
        data = umalloc(paramList[ctr].maxDataLen + 1);
        if(data != NULL)
        {
            memset(data, 0, paramList[ctr].maxDataLen + 1);
            ret = dpmGet(paramList[ctr].paramID, data, paramList[ctr].maxDataLen);
            if (ret > 0 && ret < paramList[ctr].maxDataLen)
            {
                paramList[ctr].data = (char*)umalloc(ret + 1);
                memset(paramList[ctr].data, 0, ret + 1);
                memcpy(paramList[ctr].data, data, ret);
                paramList[ctr].dataLen = ret;
            }// TODO: Design error logging for parameter initialization?
            else
            {
                paramList[ctr].dataLen = strlen(paramList[ctr].defData);
                paramList[ctr].data = (char*)umalloc(paramList[ctr].dataLen + 1);
                if(paramList[ctr].data != NULL)
                {
                    memset(paramList[ctr].data, 0, paramList[ctr].dataLen + 1);
                    memcpy(paramList[ctr].data, paramList[ctr].defData, paramList[ctr].dataLen);
                }
                
                errCtr++;
            }
            ufree(data);
        }
    }
    
    return errCtr;
}

/** Saves all the parameter values from memory to the parameter file.
 *
 *  \return
 *      - Number of parameters successfully save to the parameter file.
 *
 * \note
 *      -   The number of parameters to be saved is dependent on the number
 *          of parameters listed in \ref paramList variable at compile time.
 */
static int _PMU_ParamFileSave( void )
{
    int ret;
    int ctr;
    int errCtr = 0;

    for(ctr = 0; ctr < sizeof(paramList)/sizeof(PMU_Param_t); ctr++)
    {
        if(paramList[ctr].data != NULL)
        {
            ret = dpmPut(paramList[ctr].paramID, paramList[ctr].data, paramList[ctr].dataLen);
            if (ret != paramList[ctr].dataLen)
            {
                // TODO: Design error logging for parameter saving?
                errCtr++;
            }
        }
    }
    
    return errCtr;

}


/** Initializes the \ref paramList variable.
 *
 * \return
 * 
 * \note
 *      -   This function must be called only during power-on.
 */
int PMU_ParamFileInit( void )
{
    int ret = 0;

    dpmInit(_PMU_PARAM_FILENAME_SSL);
    _PMU_ParamFromFileRetrieve();
    _PMU_ParamFileSave();
    return ret;

}

PMU_Param_t* PMU_ParamGet( PMU_ParamID_t paramID )
{
    int ctr;

    for(ctr = 0; ctr < sizeof(paramList)/sizeof(PMU_Param_t); ctr++)
    {
        if(paramList[ctr].paramID == paramID)
        {
            return &paramList[ctr];
        }
    }
    
    return NULL;
}

int PMU_ParamSet(PMU_ParamID_t paramID, char *data, int dataLen)
{
    int ret = 0;
    int ctr;

    for(ctr = 0; ctr < sizeof(paramList)/sizeof(PMU_Param_t); ctr++)
    {
        if(paramList[ctr].paramID == paramID && dataLen <= paramList[ctr].maxDataLen)
        {
            if(dataLen != paramList[ctr].dataLen)
            {
                ufree(paramList[ctr].data);
                paramList[ctr].dataLen = dataLen;
                paramList[ctr].data = (char*)umalloc(paramList[ctr].dataLen + 1);
            }

            if(paramList[ctr].data != NULL)
            {
                memset(paramList[ctr].data, 0, paramList[ctr].dataLen + 1);
                memcpy(paramList[ctr].data, data, dataLen);
                ret = dpmPut(paramList[ctr].paramID, paramList[ctr].data, paramList[ctr].dataLen);
                if (ret != paramList[ctr].dataLen)
                {
                    // TODO: Design error logging for parameter saving?
                }
            }
            break;
        }
    }

    return ret;
}

#ifdef __cplusplus
}
#endif


