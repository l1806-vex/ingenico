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

 @file      fun_gsm.c
 @brief     Contains all definitions of functions utilized for GSM.
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#include "sdk30.h"
#include "gprs_lib.h"

#include "utilities.h"
#include "fun.h"
#include "ui.h"
#include "err.h"
#include "fun_gprs.h"


#ifdef __cplusplus
extern "C" {
#endif

#define FUN_BOOL_FALSE       0
#define FUN_BOOL_TRUE        1

#define FUN_DELAY_100MSECONDS    10
#define FUN_DELAY_10SECONDS    1000

#define FUN_FRAME_RECEIVE_100K    "RUN_FLOW"

typedef struct sGsmComsChannel {
    unsigned char apn[40];
    char phone[20];
    int rlp;
    int baud;
    unsigned short firstTimeout;
    unsigned short interTimeout;
} tGsmComsChannel;

tGsmComsChannel com;

/** Determines the status of the GSM network within a specified timeout.
 * 
 * \param[in] stepTimeout   The timeout in units of 10 milliseconds to wait in interval before
 *                          checking again the status of GPRS network.
 * \param[in] timeout       The total timeout to wait before the function returns in units of 10 milliseconds.
 * \return
 *      - ERR_RET_OK = GSM network ready.
 *      - ERR_FUN_GSM_NETWORK_NOT_AVAILABLE = GSM network not available
 *      - ERR_FUN_GSM_TIMEOUT = GSM network not available upon waiting its status with the specified timeout.
 */
static int _FUN_GsmNetworkWait( unsigned int stepTimeout, unsigned int timeout)
{
    unsigned int timeElapsed = 0;
    int bContinue = FUN_BOOL_TRUE;

    int gsmStat = FUN_BOOL_FALSE;
    int pppStat = FUN_BOOL_FALSE;
    int err;
    int ret;

    trcS("Checking Network Availability...\n");
    do 
    { 
        bContinue = gprs_IsNetworkAvailable( FUN_BOOL_FALSE, &gsmStat, &err, &pppStat );
        if( bContinue == FUN_BOOL_TRUE  )
        {
                ttestall( 0, stepTimeout );
                timeElapsed += stepTimeout;
        }

    } while(( bContinue == FUN_BOOL_TRUE ) && ( timeElapsed < timeout ));

    if(timeElapsed >= timeout)
    {
        trcS("Timeout\n");
        ret = ERR_FUN_GSM_TIMEOUT;
    }
    else
    {
        if(gsmStat == FUN_BOOL_TRUE)
        {
            trcS("Network Available\n");
            ret = ERR_RET_OK;
        }
        else
        {
            trcS("No Network Available\n");
            ret = ERR_FUN_GSM_NETWORK_NOT_AVAILABLE;
        }
    }
    
    return ret;

}

/** Activate the GSM communication mode
 * 
 * \return
 *      - ERR_RET_OK = GSM enabled
 *      - ERR_FUN_GSM_ENABLE = GSM activation failed
 *      - ERR_FUN_GSM_NETWORK_NOT_AVAILABLE = GSM network not available
 *      - ERR_FUN_GSM_TIMEOUT = GSM network not available upon waiting its status with the specified timeout.
 */
static int _FUN_GsmStart( void )
{
    int ret;

    trcS("Enabling GSM...\n");
    UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GSM_ACTIVATING);

    ret = gsm_enable(0); // GSM does not require APN!

    ret = _FUN_GprsErrorMap(ret);
    if(ret == ERR_RET_OK)
    {
        trcS("GSM Enabled\n");
        UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GSM_ACTIVATED);

        ret = _FUN_GsmNetworkWait(50, 6000);
        if (ret != ERR_RET_OK)
        {
            UI_ErrMsgDisplay(ret);
        }
    }
    else
    {
        UI_ErrMsgDisplay(ERR_FUN_GSM_ENABLE);
        trcS("Enabling GSM KO!\n");
    }
    return ret;
}

/** Disconnect the current connection to the GPRS Network
 * 
 * \return
 *      - ERR_RET_OK = disconnection successful.
 *      - ERR_FUN_GPRS_NETWORK_UNAVAILABLE = GPRS network not available
 */
static int _FUN_GsmStop(void)
{
    int ret;

    trcS("Disconnecting GSM...\n");
    ret = gsm_disconnect();
    ret = _FUN_GprsErrorMap(ret);
    if (ret == ERR_RET_OK)
    {
        UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GSM_DISCONNECTED);
        trcS("GSM Disconnected\n");
    }
    else
    {
        trcS("GSM Disconnection KO!\n");
    }

    return ret;
}


/** Save the GSM parameters to the communications channel variable.
 * 
 * \param[in] szPhoneNumber   Phone number to conect to.
 * \param[in] baud       Baud rate t be used.
 * \param[in] bRLP       Data mode to be used.
 * \return
 *      - 1 = GSM parameters set.
 */
static int _FUN_GsmSet(char *szPhoneNumber, int baud, int bRLP)
{
    int ret=1;

    memset(&com, 0, sizeof(com));
    strcpy(com.phone, szPhoneNumber);
    com.baud = baud;
    com.rlp = bRLP;
    com.firstTimeout = FUN_DELAY_10SECONDS;
    com.interTimeout = FUN_DELAY_100MSECONDS;

    return ret;
}

/** Perform a GSM connection.
 * 
 * \return
 *      - ERR_RET_OK = connection successful.
 *      - ERR_FUN_GPRS_NO_SIM = Error no SIM Inserted
 *      - ERR_FUN_GPRS_NO_PIN = PIN required
 *      - ERR_FUN_GPRS_SIM_LOCK = SIM locked
 *      - ERR_FUN_GPRS_FATAL = Fatal error encountered
 *      - ERR_FUN_GPRS_NETWORK_UNAVAILABLE = GPRS network not available
 */
static int _FUN_GsmConnect(void)
{
    int ret;

    trcS("Connecting GSM...\n");
    ret = gsm_connect(com.phone, T_ANN, com.baud, com.rlp, 80);
    ret = _FUN_GprsErrorMap(ret);
    if (ret == ERR_RET_OK)
    {
        trcS("Gsm Connection OK\n");
    }
    else
    {
        trcS("Gsm Connection KO!\n");
    }

    return ret;
}

/** Sends data to the current GSM connection.
 * 
 * \return
 *      - ERR_RET_OK = sending successful.
 *      - ERR_FUN_GPRS_NETWORK_UNAVAILABLE = GPRS network not available
 */
static int _FUN_GsmSend(unsigned char *buf, int len)
{
    int ret;

    trcS("GSM Sending...");
    UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GSM_SENDING);

    ret = gsm_write(buf, len);
    trcS("Send buf=");
    trcBAN(buf, len);
    trcS("\n");

    ret = _FUN_GprsErrorMap(ret);
    if (ret == ERR_RET_OK)
    {
        trcS("GSM Sending OK\n");
    }
    else
    {
        trcS("GSM Sending KO!\n");
    }

    return ret;
}

/** Receives data from the current GSM connection.
 * 
 * \return
 *      - ERR_RET_OK = sending successful.
 *      - ERR_FUN_GPRS_NETWORK_UNAVAILABLE = GPRS network not available
 */
static int _FUN_GsmReceive(unsigned char *buf, int *len)
{
    int ret;

    trcS("GSM Receiving...");
    UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GSM_RECEIVING);
    ret = gsm_read(buf, len, com.firstTimeout, com.interTimeout);

    trcS("Receive buf=");
    trcBAN(buf, *len);
    trcS("\n");

    ret = _FUN_GprsErrorMap(ret);
    if (ret == ERR_RET_OK)
    {
        trcS("GSM Receiving OK\n");
    }
    else
    {
        trcS("GSM Receiving KO!\n");
    }

    return ret;
}


int FUN_GsmConnectionTest(char *szPhoneNumber, int baud, int bRLP)
{
    int ret;
    int err;
    int nReceived = 0;
     unsigned char buf[1024];

    ret = ERR_FUN_GSM_CON_TEST_START; // Return code is assumed to be a failure until analysis.
    err = _FUN_GsmStart();
    if(err == ERR_RET_OK)
    {
        UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GSM_CONNECTING);
        _FUN_GsmSet(szPhoneNumber, baud, bRLP);

        ret = ERR_FUN_GSM_CON_TEST_CONNECT;// Return code is assumed to be a failure until analysis.
        err = _FUN_GsmConnect();
        if( err == ERR_RET_OK )
        {
            
            UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GSM_CONNECTED);

            ret = ERR_FUN_GSM_CON_TEST_SEND;// Return code is assumed to be a failure until analysis.
            err = _FUN_GsmSend((unsigned char*)FUN_FRAME_RECEIVE_100K, strlen(FUN_FRAME_RECEIVE_100K));
            if(err == ERR_RET_OK)
            {
                nReceived = sizeof(buf);

                /** In receiving data in a MODEM connection, it can be done by a streaming
                 * manner, until there is no more available data to take - that is, a timeout
                 * occurs. The implementation could be to loop until a timeout occurs. The
                 * error code can be obtained via the gprs_errno() function and loop until
                 * GPRS_ERRNO_GSM_RECEIVE_TIMEOUT is encountered. 
                 * 
                 * However, depending on the host, there can be some high level
                 * protocols implemented which is outside the scope of this test. In this test,
                 * it is assumed that the host only sends a data enough to be contained on the
                 * provided buffer, thus only one instance of receiving.
                 */
                ret = ERR_FUN_GSM_CON_TEST_RECV;// Return code is assumed to be a failure until analysis.
                err = _FUN_GsmReceive(buf, &nReceived);
                if (err == ERR_RET_OK)
                {
                    ret = ERR_RET_OK; // At this point all tests are already OK.
                    UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GSM_RECEIVED);
                }
            }
        }

        // Disconnection.
        UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_GSM_DISCONNECTING);
        _FUN_GsmStop();
    }

    return ret;
}


#ifdef __cplusplus
}
#endif

