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
 Module  : PHU - Process Handling Unit

 @file      phu_process.c
 @brief     This file contains the definition of processes that is implemented
            by this sample.
            
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "sdk30.h"
#include "utilities.h"
#include "pmu_parammngt.h"
#include "epu_errprocess.h"
#include "uiu_userinterface.h"
#include "dfu_demofeatures.h"

static void _PHU_StateUpdateSSL(unsigned long key);
static void _PHU_ConfigStateSSLServerAddressGet( void );
static void _PHU_ConfigStateSSLServerPortGet( void );

/** List of states for the parameter configuration.
 */
enum {
    CFG_SSL_STATE_START,
    CFG_SSL_STATE_ADDRESS_GET,
    CFG_SSL_STATE_PORT_GET,
    CFG_SSL_STATE_PROFILE_GET,
    CFG_SSL_STATE_END
};

static void _PHU_StateUpdateSSL(unsigned long key)
{
    switch(key)
    {
        case GL_KEY_VALID:
            stateNext();
            break;

        case GL_KEY_CORRECTION: // Back
            statePrev();
            break;

        default: // Cancel
            stateSet(CFG_SSL_STATE_END);
            break;
    }
}

static void _PHU_ConfigStateSSLServerAddressGet( void )
{
    unsigned long key;
    PMU_Param_t *currentParam = NULL;
    int ret = 0;
    char *data = NULL;

    currentParam = PMU_ParamGet(PMU_PARAM_ID_HOST_NAME);
    data = umalloc(currentParam->maxDataLen+1);

    if(data != NULL)
    {
        /* There is no checking of host name since it is not necessary.
         * Any value can be entered as host name. The DNS server will
         * still resolve it. If such host name can't be resolved,
         * then it doesn't exist.
         */
        memset(data, 0, currentParam->maxDataLen+1);
        memcpy(data, currentParam->data, currentParam->dataLen);
        key = enterTxt("Input Address", "Hostname :", data, currentParam->maxDataLen);
        if (key==GL_KEY_VALID)
        {
            ret = PMU_ParamSet(PMU_PARAM_ID_HOST_NAME, data, strlen(data));
            trcS("Address: ");
            trcS(data);
            trcS("\n");
        }

        ufree(data);
    }

    _PHU_StateUpdateSSL(key);
}

static void _PHU_ConfigStateSSLServerPortGet( void )
{
    unsigned long key;
    //PMU_Param_t param;
    int port;
    PMU_Param_t *currentParam = NULL;
    int ret = 0;
    char *data = NULL;

    currentParam = PMU_ParamGet(PMU_PARAM_ID_PORT);
    data = umalloc(currentParam->maxDataLen+1);

    if(data != NULL)
    {
        memset(data, 0, currentParam->maxDataLen+1);
        memcpy(data, currentParam->data, currentParam->dataLen);
        key = enterStr("Input Port", "Port :", data, currentParam->maxDataLen);
        if (key==GL_KEY_VALID)
        {
            port = atoi( data );
            /* Port number is a 16-bit value. Therefore the maximum
             * value is 65536. In the dialog, the user can enter a
             * 5-digit value which is in the range 0 ~ 99999.
             */
            if(port > PMU_HOST_PORT_VALUE_MAX)// If port is invalid, user will re-enter again the desired port number
            {
                UIU_ErrMsgDisplay(EPU_ERR_PHU_PROCESS_INVALID_PORT_NUM);
                return;
            }
            ret = PMU_ParamSet(PMU_PARAM_ID_PORT, data, strlen(data));
            trcS("Port: ");
            trcS(data);
            trcS("\n");
        }

        ufree(data);
    }


    _PHU_StateUpdateSSL(key);
}

static void _PHU_ConfigStateSSLProfileGet( void )
{
    unsigned long key;
    PMU_Param_t *currentParam = NULL;
    int ret = 0;
    char *data = NULL;
    char **profileList;
    int items;
    int ctr = 0;

    currentParam = PMU_ParamGet(PMU_PARAM_ID_SSL_PROFILE);
    data = umalloc(currentParam->maxDataLen+1);

    if(data != NULL)
    {
        memset(data, 0, currentParam->maxDataLen+1);
        profileList = DFU_SslProfileListConstruct(&items);

        if (items>0)
        {
            while(profileList[ctr] != NULL)
            {
                if(strcmp(profileList[ctr], currentParam->data) == 0)
                {
                    break;
                }
                ctr++;
            }
            
            if(ctr >= items)
            {
                ctr = 0;// Automatically select item 0 when the currently stored profile is not found in the list.
            }
            
            key = guiMenu( mnuTypeDialog, ctr, "SSL Profile", (const char **)profileList);
            if (key >= 0 && key < items)
            {
                memcpy(data, profileList[key], strlen(profileList[key]));
                ret = PMU_ParamSet(PMU_PARAM_ID_SSL_PROFILE, data, strlen(data));
                trcS("SSL Profile: ");
                trcS(data);
                trcS("\n");
            }

        }
        else
        {
           UIU_ErrMsgDisplay(EPU_ERR_DFU_SSL_NO_PROFILE_FOUND);
        }

        // De-allocate memory consumed by retrieving profile names
        if( profileList != NULL )
        {
            int i;
            for( i = 0; i < items; i++ )
            {
                ufree( profileList[i] );
            }

            ufree( profileList );
        }

        ufree(data);
    }

    _PHU_StateUpdateSSL(key);
}


void PHU_ParamConfigSSLProcess( void )
{
    int currentState;

    stateSet(CFG_SSL_STATE_START);
    stateNext();
    do
    {
        currentState = stateGet();
        switch(currentState)
        {
            case CFG_SSL_STATE_ADDRESS_GET:
                _PHU_ConfigStateSSLServerAddressGet();
                break;

            case CFG_SSL_STATE_PORT_GET:
                _PHU_ConfigStateSSLServerPortGet();
                break;
            case CFG_SSL_STATE_PROFILE_GET:
                _PHU_ConfigStateSSLProfileGet();
                break;
            default:
                stateSet(CFG_SSL_STATE_END);
                break;
        }
    } while(currentState != CFG_SSL_STATE_END);
}

void PHU_SslConnectionProcess( void )
{
    PMU_Param_t *host;
    PMU_Param_t *port;
    PMU_Param_t *profile;

    int portNum;

    host = PMU_ParamGet(PMU_PARAM_ID_HOST_NAME);
    port = PMU_ParamGet(PMU_PARAM_ID_PORT);
    profile = PMU_ParamGet(PMU_PARAM_ID_SSL_PROFILE);

    portNum = atoi(port->data);

    DFU_SslConnectionTest(host->data, portNum, profile->data);
}

void PHU_SSLProfileDeleteProcess( void )
{
    unsigned long key;
    char **profileList;
    int items;

    profileList = DFU_SslProfileListConstruct(&items);

    if (items>0)
    {
        key = guiMenu( mnuTypeDialog, 0, "SSL Profile", (const char **)profileList);
        if (key >= 0 && key < items)
        {
            DFU_SslProfileDelete(profileList[key]);
        }
    }
    else
    {
       UIU_ErrMsgDisplay(EPU_ERR_DFU_SSL_NO_PROFILE_FOUND);
    }

    // De-allocate memory consumed by retrieving profile names
    if( profileList != NULL )
    {
        int i;
        for( i = 0; i < items; i++ )
        {
            ufree( profileList[i] );
        }

        ufree( profileList );
    }
}

#ifdef __cplusplus
}
#endif


