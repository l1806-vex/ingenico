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

 @file      fun_ppp.c
 @brief     Contains all definitions of functions utilized for PPP.
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#include "sdk30.h"
#include "gprs_lib.h"

#include "utilities.h"
#include "err.h"
#include "fun_gprs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FUN_BOOL_FALSE       0
#define FUN_BOOL_TRUE        1


/** Determines the status of the PPP authentication within a specified timeout.
 * 
 * \param[in] stepTimeout   The timeout in units of 10 milliseconds to wait in interval before
 *                          checking again the status of GPRS network.
 * \param[in] timeout       The total timeout to wait before the function returns in units of 10 milliseconds.
 * \return
 *      - ERR_RET_OK = GPRS network ready.
 *      - ERR_FUN_GPRS_NETWORK_NOT_AVAILABLE = GPRS network not available
 *      - ERR_FUN_GPRS_TIMEOUT = GPRS network not available upon waiting its status with the specified timeout.
 */
static int _FUN_PppAuthWait( unsigned int stepTimeout, unsigned int timeout)
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
        ret = ERR_FUN_PPP_AUTH_TIMEOUT;
    }
    else
    {
        if(pppStat == FUN_BOOL_TRUE)
        {
            trcS("Network Available\n");
            ret = ERR_RET_OK;
        }
        else
        {
            trcS("No Network Available\n");
            ret = ERR_FUN_PPP_AUTH_FAILED;
        }
    }
    
    return ret;
}


int FUN_PppConnect( char *login, char *password )
{
    int ret;
    char *apn = NULL;

    apn = _FUN_GprsApnGet();
    ret = _FUN_GprsStatusGet();

    if(ret == ERR_RET_OK)
    {
        /** The function called here is gprs_connect(). There is no separate function
         * used to established a PPP link with that of the GPRS link. The GPRS link can 
         * either be established here or can be established at an early stage.
         */
        trcS("Connecting PPP...\n");
        UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_PPP_CONNECTING);

        ret = gprs_connect( T_ANN, apn, login, password, 30 );// Cancel key is used to terminate the connection. Timeout is 30 seconds.

        ret = _FUN_GprsErrorMap(ret);

        if(ret == ERR_RET_OK)
        {
            trcS("PPP Connected\n");
            UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_PPP_CONNECTED);
            ret = _FUN_PppAuthWait(50, 300);
        }
        else
        {
            trcS("PPP Connection KO!\n");
        }
    }

    return ret;
}

int FUN_PppDisconnect( void )
{
    int ret;

    trcS("Disconnecting PPP...\n");
    UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_PPP_DISCONNECTING);

    ret = gprs_ppp_disconnect();
    ret = _FUN_GprsErrorMap(ret);
    if (ret == ERR_RET_OK)
    {
        trcS("PPP Disconnected\n");
        UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_PPP_DISCONNECTED);
    }
    else
    {
        trcS("PPP Disconnection KO!\n");
    }

    return ret;
}


#ifdef __cplusplus
}
#endif


