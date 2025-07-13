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
 Module  : FUN - Functional Demo Unit

 @file      fun_gprs.c
 @brief     Contains all definitions of functions utilized for SSL.
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#include "sdk30.h"
#include "gprs_lib.h"

#include "utilities.h"
#include "err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FUN_BOOL_FALSE       0
#define FUN_BOOL_TRUE       1

char *_FUN_Gprs_Apn = NULL;// Holds the currently in-used APN in this module. This is separate

int _FUN_GprsErrorMap(int err)
{
    int ret;

    switch(err)
    {
        case GPRS_OK:
            trcS("GPRS OK\n");
            ret = ERR_RET_OK;
            break;
        case GPRS_ERR_NO_SIM:
            trcS("GPRS Error = No Sim\n");
            ret = ERR_FUN_GPRS_NO_SIM;
            break;
        case GPRS_ERR_NO_PIN:
            trcS("GPRS Error = No Pin\n");
            ret = ERR_FUN_GPRS_NO_PIN;
            break;
        case GPRS_ERR_BAD_PIN:
            trcS("GPRS Error = Bad Pin\n");
            ret = ERR_FUN_GPRS_BAD_PIN;
            break;
        case GPRS_ERR_SIM_LOCK:
            trcS("GPRS Error = Sim Lock\n");
            ret = ERR_FUN_GPRS_SIM_LOCK;
            break;
        case GPRS_ERR_FATAL:
            trcS("GPRS Error = Fatal\n");
            ret = ERR_FUN_GPRS_FATAL;
            break;
        case GPRS_ERR_CONNECT_TIMEOUT:
            trcS("GPRS Error = Connection Timeout\n");
            ret = ERR_FUN_CONNECT_TIMEOUT;
            break;
        case GPRS_ERR_PPP:
            trcS("GPRS Error = PPP Connection Failed\n");
            ret = ERR_FUN_PPP_CONNECT_FAILED;
            break;
        case GPRS_ERR_NO_GPRS:
            trcS("GPRS Error = No GPRS\n");
            ret = ERR_FUN_GPRS_NETWORK_UNAVAILABLE;
            break;
        case GPRS_ERR_UNKNOWN:
        default:
            trcS("GPRS Error = Unknown\n");
            ret = ERR_FUN_GPRS_UNKNOWN;
            break;
    }

    if (ret!=ERR_RET_OK)
    {
        UI_ErrMsgDisplay(ret);
    }
    return ret;
}

/** Opens the GPRS communication channel.
 *
 * \param[in] apn   The APN provided by the GPRS network.
 * \return
 *      - ERR_RET_OK = GPRS communication channel successfully openned.
 */
static int _FUN_GprsEnable(char *apn)
{
    int ret;

    if(apn == NULL)
    {
        return ERR_FUN_GPRS_NULL_POINTER;
    }

    if(_FUN_Gprs_Apn != NULL)
    {
        ufree(_FUN_Gprs_Apn);
    }

    {
        int size = strlen(apn)+1;
        _FUN_Gprs_Apn = (char*)umalloc(size);
        memset(_FUN_Gprs_Apn, 0, size);
        memcpy(_FUN_Gprs_Apn, apn, size - 1);
    }

    ret = gprs_enable(apn);

    ret = _FUN_GprsErrorMap(ret);

    return ret;
}

/** Disables GPRS. It disconnects all current
 * PPP connections too.
 *
 * \return
 *      - \ref ERR_RET_OK = GPRS successfully disabled.
 */
static int _FUN_GprsDisable(void)
{
    int ret;

    ret = gprs_stop();
    ret = _FUN_GprsErrorMap(ret);

    return ret;
}

/** Determines the status of the GPRS network within a specified timeout.
 * 
 * \param[in] stepTimeout   The timeout in units of 10 milliseconds to wait in interval before
 *                          checking again the status of GPRS network.
 * \param[in] timeout       The total timeout to wait before the function returns in units of 10 milliseconds.
 * \return
 *      - ERR_RET_OK = GPRS network ready.
 *      - ERR_FUN_GPRS_NETWORK_NOT_AVAILABLE = GPRS network not available
 *      - ERR_FUN_GPRS_TIMEOUT = GPRS network not available upon waiting its status with the specified timeout.
 */
static int _FUN_GprsNetworkWait( unsigned int stepTimeout, unsigned int timeout)
{
    unsigned int timeElapsed = 0;
    int bContinue = FUN_BOOL_TRUE;

    int gprsStat = FUN_BOOL_FALSE;
    int pppStat = FUN_BOOL_FALSE;
    int err;
    int ret;

    trcS("Checking Network Availability...\n");
    do 
    { 
        bContinue = gprs_IsNetworkAvailable( FUN_BOOL_TRUE, &gprsStat, &err, &pppStat );
        if( bContinue == FUN_BOOL_TRUE  )
        {
                ttestall( 0, stepTimeout );
                timeElapsed += stepTimeout;
        }

    } while(( bContinue == FUN_BOOL_TRUE ) && ( timeElapsed < timeout ));

    if(timeElapsed >= timeout)
    {
        trcS("Timeout\n");
        ret = GPRS_ERR_CONNECT_TIMEOUT;
        ret = _FUN_GprsErrorMap(ret);
    }
    else
    {
        if(gprsStat == FUN_BOOL_TRUE)
        {
            trcS("Network Available\n");
            trcS("GPRS Activated\n");
            UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GPRS_ACTIVATED);
            ret = ERR_RET_OK;
        }
        else
        {
            trcS("No Network Available\n");
            ret = _FUN_GprsErrorMap(err);
        }
    }
    
    return ret;
}

int FUN_GprsActivate( char *apn )
{
    int ret;

    trcS("Activating GPRS...\n");
    UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GPRS_ACTIVATING);

    ret = _FUN_GprsEnable(apn);
    if(ret == ERR_RET_OK)
    {
        trcS("GPRS Enabled\n");
        ret = _FUN_GprsNetworkWait(50, 6000);// Wait for 60 seconds with an interval of 50 milliseconds.
    }
    else
    {
        trcS("GPRS Activation KO!\n");
    }

    if((ret == ERR_FUN_GPRS_NO_PIN) || (ret == ERR_FUN_GPRS_BAD_PIN))
    {
        gprs_setpincode();
        ret = _FUN_GprsNetworkWait(50, 6000);// Wait for 60 seconds with an interval of 50 milliseconds.
    }

    return ret;
}


int FUN_GprsDeactivate( void )
{
    int ret;

    trcS("Deactivating GPRS...\n");
    UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GPRS_DEACTIVATING);

    ret = _FUN_GprsDisable();
    if (ret == ERR_RET_OK)
    {
        trcS("GPRS Deactivated\n");
        UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GPRS_DEACTIVATED);
    }
    else
    {
        trcS("GPRS Deactivation KO!\n");
    }

    return ret;
}

int _FUN_GprsStatusGet( void )
{
    int ret;

    ret = _FUN_GprsNetworkWait(50, 6000);

    return ret;
}

char* _FUN_GprsApnGet( void )
{
    return _FUN_Gprs_Apn;
}

#ifdef __cplusplus
}
#endif

