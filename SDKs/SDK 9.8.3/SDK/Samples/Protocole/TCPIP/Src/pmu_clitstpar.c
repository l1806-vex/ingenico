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

 @file      pmu_param.c
 @brief     Contains definitions of APIs specific to sample parameters to be 
            stored in file.
            
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#include "sdk30.h"
#include "utilities.h"
#include "pmu_parammngt.h"


#define PMU_HOST_NAME_DEFAULT_VALUE "www.free.fr\0"
#define PMU_HOST_PORT_DEFAULT_VALUE 80

/** Filename of the TCP/IP Sample parameter file.
 */
#define PMU_PARAM_FILENAME_TCPIP                "TCPIP"

/** Identifiers for the parameters to be stored in the 
 * parameter file.
 */
#define PMU_PARAM_ID_HOST_NAME                  1
#define PMU_PARAM_ID_PORT                       2

PMU_Param_t tcpipParam;

static int _PMU_ParamFromFileRetrieve( void )
{
    int ret = 0;
    PMU_Param_t param;
    char name[PMU_HOST_NAME_LEN_MAX+1];
    char port[PMU_HOST_PORT_NUM_LEN_MAX+1];

    memset(&param, 0, sizeof(PMU_Param_t));

    ret = dpmGet(PMU_PARAM_ID_HOST_NAME, name, sizeof(name));
    if (ret > 0)
    {
        memcpy(param.host, name, ret);
    }
    else
    if (ret == 0)// Parameter file exists but the desired parameter wasn't found.
    {
        memcpy(param.host, PMU_HOST_NAME_DEFAULT_VALUE, strlen(PMU_HOST_NAME_DEFAULT_VALUE));
    }
    else
    {
        return -1;// File does not exist. Return immediately for initialization of default values for all fields.
    }
    
    ret = dpmGet(PMU_PARAM_ID_PORT, port, sizeof(port));
    if (ret > 0)
    {
        param.port = atoi(port);
    }
    else
    if (ret == 0)// Parameter file exists but the desired parameter wasn't found.
    {
        param.port = PMU_HOST_PORT_DEFAULT_VALUE;
    }

    memcpy(&tcpipParam, &param, sizeof(PMU_Param_t));

    return 0;
}

static int _PMU_ParamFileSave( void )
{
    int ret = 0;
    char buf[PMU_HOST_PORT_NUM_LEN_MAX+1];

    dpmPut(PMU_PARAM_ID_HOST_NAME, tcpipParam.host, strlen(tcpipParam.host));

    sprintf(buf, "%i", tcpipParam.port);
    dpmPut(PMU_PARAM_ID_PORT, buf, strlen(buf));
    
    return ret;
}


int PMU_ParamFileInit( void )
{
#if 0
    int ret = 0;

    dpmInit(PMU_PARAM_FILENAME_TCPIP);
    ret = _PMU_ParamFromFileRetrieve();
    if(ret != 0)// If parameter file does not exist yet, initialize to default values from source code
    {
        memset(&tcpipParam, 0, sizeof(PMU_Param_t));
        memcpy(&tcpipParam.host, PMU_HOST_NAME_DEFAULT_VALUE, strlen(PMU_HOST_NAME_DEFAULT_VALUE));
        tcpipParam.port = PMU_HOST_PORT_DEFAULT_VALUE;
    }
    _PMU_ParamFileSave();
    return ret;
#else
    int ret = 0;

    memset(&tcpipParam, 0, sizeof(PMU_Param_t));
    memcpy(&tcpipParam.host, PMU_HOST_NAME_DEFAULT_VALUE, strlen(PMU_HOST_NAME_DEFAULT_VALUE));
    tcpipParam.port = PMU_HOST_PORT_DEFAULT_VALUE;
    dpmInit(PMU_PARAM_FILENAME_TCPIP);
    _PMU_ParamFromFileRetrieve();
    _PMU_ParamFileSave();
    return ret;

#endif
}

PMU_Param_t* PMU_ParamGet( void )
{
    return &tcpipParam;
}

int PMU_ParamSet( PMU_Param_t *param)
{
    int ret = 0;

    if(param != NULL)
    {
        memcpy(&tcpipParam, param, sizeof(PMU_Param_t));
        ret = _PMU_ParamFileSave();
    }

    return ret;
}
