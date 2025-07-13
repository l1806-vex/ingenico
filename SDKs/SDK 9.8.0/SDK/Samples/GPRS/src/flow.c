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
 Module  : FLOW - Process Handling Unit

 @file      flow.c
 @brief     Contains all functions definitions for FLOW that executes 
            processes specific to the sample application. These 
            processes may include but not limited to configuration of
            parameters, demo process, and so on.
            
 @date      16/10/2012

 ------------------------------------------------------------------------------
 */


#ifdef __cplusplus
extern "C" {
#endif

#include "sdk30.h"
#include "utilities.h"
#include "param.h"
#include "err.h"
#include "ui.h"
#include "fun.h"

#define FLOW_GSM_2400_V22	"4"
#define FLOW_GSM_4800_V32	"6"
#define FLOW_GSM_9600_V32	"7"
#define FLOW_GSM_2400_V110	"68"
#define FLOW_GSM_4800_V110	"70"
#define FLOW_GSM_9600_V110	"71"

static void _FLOW_StateUpdateGprs(unsigned long key);
static void _FLOW_ConfigStateGprsApnGet( void );
static void _FLOW_StateUpdatePpp(unsigned long key);
static void _FLOW_ConfigStatePppLoginGet( void );
static void _FLOW_ConfigStatePppPasswordGet( void );
static void _FLOW_StateUpdateTcp(unsigned long key);
static void _FLOW_ConfigStateTcpServerAddressGet( void );
static void _FLOW_ConfigStateTcpServerPortGet( void );
static void _FLOW_StateUpdateGsm(unsigned long key);
static void _FLOW_ConfigStateGsmPhoneNumberGet( void );
static void _FLOW_ConfigStateGsmBaudRateGet( void );
static void _FLOW_ConfigStateGsmRlpGet( void );

/** List of states for the parameter configuration.
 */
enum {
    CFG_GPRS_STATE_START,
    CFG_GPRS_STATE_APN_GET,
    CFG_GPRS_STATE_END
};

enum {
    CFG_PPP_STATE_START,
    CFG_PPP_STATE_LOGIN_GET,
    CFG_PPP_STATE_PASSWORD_GET,
    CFG_PPP_STATE_END
};

enum {
    CFG_TCP_STATE_START,
    CFG_TCP_STATE_ADDRESS_GET,
    CFG_TCP_STATE_PORT_GET,
    CFG_TCP_STATE_END
};

enum {
    CFG_GSM_STATE_START,
    CFG_GSM_STATE_NUMBER_GET,
    CFG_GSM_STATE_BAUD_RATE_GET,
    CFG_GSM_STATE_RLP_GET,
    CFG_GSM_STATE_END
};

/** Set the next GPRS State based from the result of the previous state
 */
static void _FLOW_StateUpdateGprs(unsigned long key)
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
            stateSet(CFG_GPRS_STATE_END);
            break;
    }
}

/** Configure the APN to be used for the GPRS connection
 * The initial value will be obtained from the database.
 * If the user enters a valid APN, it will be stored to the database
 */
static void _FLOW_ConfigStateGprsApnGet( void )
{
    unsigned long key;
    PARAM_Param_t *currentParam = NULL;
    int ret = 0;
    char *data = NULL;

    currentParam = PARAM_ParamGet(PARAM_ID_APN);
    data = umalloc(currentParam->maxDataLen+1);

    if(data != NULL)
    {
        /* There is no checking of login since it is not necessary
         */
        memset(data, 0, currentParam->maxDataLen+1);
        memcpy(data, currentParam->data, currentParam->dataLen);
        key = enterTxt("Input APN", "APN :", data, currentParam->maxDataLen);
        if (key==GL_KEY_VALID)
        {
            ret = PARAM_ParamSet(PARAM_ID_APN, data, strlen(data));
            trcS("Login: ");
            trcS(data);
            trcS("\n");
        }

        ufree(data);
    }

    _FLOW_StateUpdateGprs(key);
}

void FLOW_ParamConfigGprsProcess( void )
{
    int currentState;

    stateSet(CFG_GPRS_STATE_START);
    stateNext();
    do
    {
        currentState = stateGet();
        switch(currentState)
        {
            case CFG_GPRS_STATE_APN_GET:
                _FLOW_ConfigStateGprsApnGet();
                break;

            default:
                stateSet(CFG_GPRS_STATE_END);
                break;
        }
    } while(currentState != CFG_GPRS_STATE_END);
}

void FLOW_GprsActivationProcess( void )
{
    PARAM_Param_t *apn;

    apn = PARAM_ParamGet(PARAM_ID_APN);

    FUN_GprsActivate(apn->data);
}

void FLOW_GprsDeactivationProcess( void )
{
    FUN_GprsDeactivate();
}

/** Set the next PPP State based from the result of the previous state
 */
static void _FLOW_StateUpdatePpp(unsigned long key)
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
            stateSet(CFG_PPP_STATE_END);
            break;
    }
}

/** Configure the login name to be used for the PPP connection
 * The initial value will be obtained from the database.
 * If the user enters a valid login name, it will be stored to the database
 */
static void _FLOW_ConfigStatePppLoginGet( void )
{
    unsigned long key;
    PARAM_Param_t *currentParam = NULL;
    int ret = 0;
    char *data = NULL;

    currentParam = PARAM_ParamGet(PARAM_ID_LOGIN);
    data = umalloc(currentParam->maxDataLen+1);

    if(data != NULL)
    {
        /* There is no checking of login since it is not necessary
         */
        memset(data, 0, currentParam->maxDataLen+1);
        memcpy(data, currentParam->data, currentParam->dataLen);
        key = enterTxt("Input Username", "Login :", data, currentParam->maxDataLen);
        if (key==GL_KEY_VALID)
        {
            ret = PARAM_ParamSet(PARAM_ID_LOGIN, data, strlen(data));
            trcS("Login: ");
            trcS(data);
            trcS("\n");
        }

        ufree(data);
    }

    _FLOW_StateUpdatePpp(key);
}

/** Configure the password to be used for the PPP connection
 * The initial value will be obtained from the database.
 * If the user enters a valid password, it will be stored to the database
 */
static void _FLOW_ConfigStatePppPasswordGet( void )
{
    unsigned long key;
    PARAM_Param_t *currentParam = NULL;
    int ret = 0;
    char *data = NULL;

    currentParam = PARAM_ParamGet(PARAM_ID_PASSWORD);
    data = umalloc(currentParam->maxDataLen+1);

    if(data != NULL)
    {
        /* There is no checking of password since it is not necessary
         */
        memset(data, 0, currentParam->maxDataLen+1);
        memcpy(data, currentParam->data, currentParam->dataLen);
        key = enterPwdTxt("Input Password", "Password :", data, currentParam->maxDataLen);
        if (key==GL_KEY_VALID)
        {
            ret = PARAM_ParamSet(PARAM_ID_PASSWORD, data, strlen(data));
            trcS("Password: ");
            trcS(data);
            trcS("\n");
        }

        ufree(data);
    }

    _FLOW_StateUpdatePpp(key);
}

void FLOW_ParamConfigPppProcess( void )
{
    int currentState;

    stateSet(CFG_PPP_STATE_START);
    stateNext();
    do
    {
        currentState = stateGet();
        switch(currentState)
        {
            case CFG_PPP_STATE_LOGIN_GET:
                _FLOW_ConfigStatePppLoginGet();
                break;

            case CFG_PPP_STATE_PASSWORD_GET:
                _FLOW_ConfigStatePppPasswordGet();
                break;

            default:
                stateSet(CFG_PPP_STATE_END);
                break;
        }
    } while(currentState != CFG_PPP_STATE_END);
}

void FLOW_PppConnectionProcess( void )
{
    PARAM_Param_t *login;
    PARAM_Param_t *password;

    login = PARAM_ParamGet(CFG_PPP_STATE_LOGIN_GET);
    password = PARAM_ParamGet(CFG_PPP_STATE_PASSWORD_GET);

    FUN_PppConnect(login->data, password->data);
}

void FLOW_PppDisconnectionProcess( void )
{
    FUN_PppDisconnect();
}

/** Set the next TCP State based from the result of the previous state
 */
static void _FLOW_StateUpdateTcp(unsigned long key)
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
            stateSet(CFG_TCP_STATE_END);
            break;
    }
}

/** Configure the host name  or address to be used for the TCP connection
 * The initial value will be obtained from the database.
 * If the user enters a valid host name or address, it will be stored to the database
 */
static void _FLOW_ConfigStateTcpServerAddressGet( void )
{
    unsigned long key;
    PARAM_Param_t *currentParam = NULL;
    int ret = 0;
    char *data = NULL;

    currentParam = PARAM_ParamGet(PARAM_ID_HOST_NAME);
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
            ret = PARAM_ParamSet(PARAM_ID_HOST_NAME, data, strlen(data));
            trcS("Address: ");
            trcS(data);
            trcS("\n");
        }

        ufree(data);
    }

    _FLOW_StateUpdateTcp(key);
}

/** Configure the port number to be used for the TCP connection
 * The initial value will be obtained from the database.
 * If the user enters a valid port number, it will be stored to the database
 */
static void _FLOW_ConfigStateTcpServerPortGet( void )
{
    unsigned long key;
    //PARAM_Param_t param;
    int port;
    PARAM_Param_t *currentParam = NULL;
    int ret = 0;
    char *data = NULL;

    currentParam = PARAM_ParamGet(PARAM_ID_PORT);
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
        key = enterStr("Input Port", "Port :", data, currentParam->maxDataLen);
        if (key==GL_KEY_VALID)
        {
            port = atoi( data );
            /* Port number is a 16-bit value. Therefore the maximum
             * value is 65536. In the dialog, the user can enter a
             * 5-digit value which is in the range 0 ~ 99999.
             */
            if(port > PARAM_HOST_PORT_VALUE_MAX)// If port is invalid, user will re-enter again the desired port number
            {
                UI_ErrMsgDisplay(ERR_FLOW_PROCESS_INVALID_PORT_NUM);
                return;
            }
            ret = PARAM_ParamSet(PARAM_ID_PORT, data, strlen(data));
            trcS("Port: ");
            trcS(data);
            trcS("\n");
        }

        ufree(data);
    }


    _FLOW_StateUpdateTcp(key);
}


void FLOW_ParamConfigTcpProcess( void )
{
    int currentState;

    stateSet(CFG_TCP_STATE_START);
    stateNext();
    do
    {
        currentState = stateGet();
        switch(currentState)
        {
            case CFG_TCP_STATE_ADDRESS_GET:
                _FLOW_ConfigStateTcpServerAddressGet();
                break;

            case CFG_TCP_STATE_PORT_GET:
                _FLOW_ConfigStateTcpServerPortGet();
                break;

            default:
                stateSet(CFG_TCP_STATE_END);
                break;
        }
    } while(currentState != CFG_TCP_STATE_END);
}

void FLOW_TcpTransceive( void )
{
    PARAM_Param_t *host;
    PARAM_Param_t *port;

    int portNum;

    host = PARAM_ParamGet(PARAM_ID_HOST_NAME);
    port = PARAM_ParamGet(PARAM_ID_PORT);

    portNum = atoi(port->data);

    FUN_TcpIpTransceive(host->data, portNum);
}

/** Set the next GSM State based from the result of the previous state
 */
static void _FLOW_StateUpdateGsm(unsigned long key)
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
            stateSet(CFG_GSM_STATE_END);
            break;
    }
}

/** Configure the phone number to be used for the GSM connection
 * The initial value will be obtained from the database.
 * If the user enters a valid phone number, it will be stored to the database
 */
static void _FLOW_ConfigStateGsmPhoneNumberGet( void )
{
    unsigned long key;
    PARAM_Param_t *currentParam = NULL;
    int ret = 0;
    char *data = NULL;

    currentParam = PARAM_ParamGet(PARAM_ID_PHONE_NUMBER);
    data = umalloc(currentParam->maxDataLen+1);

    if(data != NULL)
    {
        /* There is no checking of phone number since it is not necessary.
         */
        memset(data, 0, currentParam->maxDataLen+1);
        memcpy(data, currentParam->data, currentParam->dataLen);
        key = enterTxt("Input Number", "Phone :", data, currentParam->maxDataLen);
        if (key==GL_KEY_VALID)
        {
            ret = PARAM_ParamSet(PARAM_ID_PHONE_NUMBER, data, strlen(data));
            trcS("Phone Number: ");
            trcS(data);
            trcS("\n");
        }

        ufree(data);
    }

    _FLOW_StateUpdateGsm(key);
}

/** Configure the baud rate to be used for the GSM connection
 * The initial value will be obtained from the database and the item will be
 * highlighted on the menu. 
 * If the user selects a valid baud rate, it will be stored to the database
 */
static void _FLOW_ConfigStateGsmBaudRateGet( void )
{
    int ret;
    int len;
    int sel;
    PARAM_Param_t *currentParam = NULL;
    unsigned long key;
    unsigned char data[2+1];
    const char *menu[]=
    {
        "V22 bis at 2400 bauds",
        "V32 at 4800 bauds",
        "V32 at 9600 bauds",
        "V110 at 2400 bauds",
        "V110 at 4800 bauds",
        "V110 at 9600 bauds",
        0
    };

    sel=0;
    currentParam = PARAM_ParamGet(PARAM_ID_BAUD_RATE);
    if (strcmp(currentParam->data, (char*)FLOW_GSM_2400_V22)==0)
    {
        sel=0;
    }
    else if (strcmp(currentParam->data, (char*)FLOW_GSM_4800_V32)==0)
    {
        sel=1;
    }
    else if (strcmp(currentParam->data, (char*)FLOW_GSM_9600_V32)==0)
    {
        sel=2;
    }
    else if (strcmp(currentParam->data, (char*)FLOW_GSM_2400_V110)==0)
    {
        sel=3;
    }
    else if (strcmp(currentParam->data, (char*)FLOW_GSM_4800_V110)==0)
    {
        sel=4;
    }
    else if (strcmp(currentParam->data, (char*)FLOW_GSM_9600_V110)==0)
    {
        sel=5;
    }

    len=0;
    memset(data, 0, sizeof(data));
    key = guiMenu( mnuTypeDialog, sel, "Baud Rate", (const char **)menu);
    switch (key)
    {
        case 0: /*!< V22 bis at 2400 bauds */
            len = 1;
            strcpy(data, (char*)FLOW_GSM_2400_V22);
            break;
        case 1: /*!< V32 at 4800 bauds */
            len = 1;
            strcpy(data, (char*)FLOW_GSM_4800_V32);
            break;
        case 2: /*!< V32 at 9600 bauds */
            len = 1;
            strcpy(data, (char*)FLOW_GSM_9600_V32);
            break;
        case 3: /*!< V110 at 2400 bauds */
            len = 2;
            strcpy(data, (char*)FLOW_GSM_2400_V110);
            break;
        case 4: /*!< V110 at 4800 bauds */
            len = 2;
            strcpy(data, (char*)FLOW_GSM_4800_V110);
            break;
        case 5: /*!< V110 at 9600 bauds */
            len = 2;
            strcpy(data, (char*)FLOW_GSM_9600_V110);
            break;
        default:
            break;
    }

    if (len>0)
    {
        ret = PARAM_ParamSet(PARAM_ID_BAUD_RATE, data, len);
        trcS("Baud Rate: ");
        trcS(menu[key]);
        trcS("\n");
        key = GL_KEY_VALID;
    }

    _FLOW_StateUpdateGsm(key);
}

/** Configure the RLP mode to be used for the GSM connection
 * The initial value (Activated or Deactivated) will be obtained from the database 
 * and the item will be highlighted on the menu. 
 * If the user selects a valid RLP mode, it will be stored to the database
 */
static void _FLOW_ConfigStateGsmRlpGet( void )
{
    int ret;
    int len;
    int sel;
    PARAM_Param_t *currentParam = NULL;
    unsigned long key;
    unsigned char data[1+1];
    const char *menu[]=
    {
        "RLP",
        "Transparent",
        0
    };

    sel=0;
    currentParam = PARAM_ParamGet(PARAM_ID_RLP);
    if (strcmp(currentParam->data, "0")==0)
    {
        sel=1;
    }

    len=0;
    memset(data, 0, sizeof(data));
    key = guiMenu(mnuTypeDialog, sel, "Data Mode", (const char **)menu);
    switch (key)
    {
        case 0: 
            len = 1;
            memcpy(data, "1", len);
            break;
        case 1: 
            len = 1;
            memcpy(data, "0", len);
            break;
        default:
            break;
    }

    if (len>0)
    {
        ret = PARAM_ParamSet(PARAM_ID_RLP, data, len);
        trcS("RLP Mode: ");
        trcS(menu[key]);
        trcS("\n");
        key = GL_KEY_VALID;
    }
    _FLOW_StateUpdateGsm(key);
}

void FLOW_ParamConfigGsmProcess( void )
{
    int currentState;

    stateSet(CFG_GSM_STATE_START);
    stateNext();
    do
    {
        currentState = stateGet();
        switch(currentState)
        {
            case CFG_GSM_STATE_NUMBER_GET:
                _FLOW_ConfigStateGsmPhoneNumberGet();
                break;

            case CFG_GSM_STATE_BAUD_RATE_GET:
                _FLOW_ConfigStateGsmBaudRateGet();
                break;

            case CFG_GSM_STATE_RLP_GET:
                _FLOW_ConfigStateGsmRlpGet();
                break;

            default:
                stateSet(CFG_GSM_STATE_END);
                break;
        }
    } while(currentState != CFG_GSM_STATE_END);
}

void FLOW_GsmConnectionProcess( void )
{
    PARAM_Param_t *phoneNum;
    PARAM_Param_t *baud;
    PARAM_Param_t *rlp;

    int baudRateNum;
    int rlpNum;

    phoneNum = PARAM_ParamGet(PARAM_ID_PHONE_NUMBER);
    baud = PARAM_ParamGet(PARAM_ID_BAUD_RATE);
    rlp = PARAM_ParamGet(PARAM_ID_RLP);

    baudRateNum = atoi(baud->data);
    rlpNum = atoi(rlp->data);

    FUN_GsmConnectionTest(phoneNum->data, baudRateNum, rlpNum);
}

#ifdef __cplusplus
}
#endif

