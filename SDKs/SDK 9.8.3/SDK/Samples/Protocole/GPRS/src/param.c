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

 @file      param.c
 @brief     Contains definitions of APIs specific to sample parameters to be 
            stored in file.
            
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "sdk30.h"
#include "utilities.h"
#include "param.h"

#define PARAM_HOST_NAME_LEN_MAX 40 ///< Maximum lenght of host name.
#define PARAM_HOST_PORT_NUM_LEN_MAX 5 ///< Maximum length  of port number.

#define PARAM_DEFAULT_VALUE_APN "internet"
#define PARAM_DEFAULT_VALUE_LOGIN ""
#define PARAM_DEFAULT_VALUE_PWD ""
#define PARAM_DEFAULT_VALUE_HOST_NAME "122.3.123.49\0"
#define PARAM_DEFAULT_VALUE_HOST_PORT "8000"
#define PARAM_DEFAULT_VALUE_PHONE_NUMBER "025190183"
#define PARAM_DEFAULT_VALUE_BAUD_RATE "7"
#define PARAM_DEFAULT_VALUE_RLP "1"

/** Filename of the SSL Sample parameter file.
 */
#define PARAM_FILENAME_GPRS                "GPRS"

PARAM_Param_t paramList[] =
    {
        {
            .paramID = PARAM_ID_APN,
            .dataType = PARAM_DATA_TYPE_STR,
            .defData = PARAM_DEFAULT_VALUE_APN,
            .dataLen = 0, // This element will be initialized properly dynamically.
            .maxDataLen = 20
        },
        {
            .paramID = PARAM_ID_LOGIN,
            .dataType = PARAM_DATA_TYPE_STR,
            .defData = PARAM_DEFAULT_VALUE_LOGIN,
            .dataLen = 0, // This element will be initialized properly dynamically.
            .maxDataLen = 50
        },
        {
            .paramID = PARAM_ID_PASSWORD,
            .dataType = PARAM_DATA_TYPE_STR,
            .defData = PARAM_DEFAULT_VALUE_PWD,
            .dataLen = 0, // This element will be initialized properly dynamically.
            .maxDataLen = 50
        },
        {
            .paramID = PARAM_ID_HOST_NAME,
            .dataType = PARAM_DATA_TYPE_STR,
            .defData = PARAM_DEFAULT_VALUE_HOST_NAME,
            .dataLen = 0, // This element will be initialized properly dynamically.
            .maxDataLen = PARAM_HOST_NAME_LEN_MAX
        },
        {
            .paramID = PARAM_ID_PORT,
            .dataType = PARAM_DATA_TYPE_INT16,
            .defData = PARAM_DEFAULT_VALUE_HOST_PORT,
            .dataLen = 0, // This element will be initialized properly dynamically.
            .maxDataLen = PARAM_HOST_PORT_NUM_LEN_MAX,
        },
        {
            .paramID = PARAM_ID_PHONE_NUMBER,
            .dataType = PARAM_DATA_TYPE_STR,
            .defData = PARAM_DEFAULT_VALUE_PHONE_NUMBER,
            .dataLen = 0, // This element will be initialized properly dynamically.
            .maxDataLen = 20
        },
        {
            .paramID = PARAM_ID_BAUD_RATE,
            .dataType = PARAM_DATA_TYPE_INT16,
            .defData = PARAM_DEFAULT_VALUE_BAUD_RATE,
            .dataLen = 0, // This element will be initialized properly dynamically.
            .maxDataLen = 6
        },
        {
            .paramID = PARAM_ID_RLP,
            .dataType = PARAM_DATA_TYPE_INT16,
            .defData = PARAM_DEFAULT_VALUE_RLP,
            .dataLen = 0, // This element will be initialized properly dynamically.
            .maxDataLen = 1
        },
    };

static int _PARAM_ParamFromFileRetrieve( void )
{
    int ret;
    int ctr;
    char *data = NULL;
    int errCtr = 0;

    for(ctr = 0; ctr < sizeof(paramList)/sizeof(PARAM_Param_t); ctr++)
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

static int _PARAM_ParamFileSave( void )
{
    int ret;
    int ctr;
    int errCtr = 0;

    for(ctr = 0; ctr < sizeof(paramList)/sizeof(PARAM_Param_t); ctr++)
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


int PARAM_ParamFileInit( void )
{
    int ret = 0;

    dpmInit(PARAM_FILENAME_GPRS);
    _PARAM_ParamFromFileRetrieve();
    _PARAM_ParamFileSave();
    return ret;

}

PARAM_Param_t* PARAM_ParamGet( PARAM_ParamID_t paramID )
{
    int ctr;

    for(ctr = 0; ctr < sizeof(paramList)/sizeof(PARAM_Param_t); ctr++)
    {
        if(paramList[ctr].paramID == paramID)
        {
            return &paramList[ctr];
        }
    }
    
    return NULL;
}

int PARAM_ParamSet(PARAM_ParamID_t paramID, char *data, int dataLen)
{
    int ret = 0;
    int ctr;

    for(ctr = 0; ctr < sizeof(paramList)/sizeof(PARAM_Param_t); ctr++)
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
