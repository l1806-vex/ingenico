/*+
 *  PROJECT         :   TCP/IP Sample
 *  MODULE          :   Process Handling Unit
 *  FILEMANE        :   phu.c
 *  PURPOSE         :   Definitions for PHU
 *
 *  DESCRIPTION     :   Contains all functions definitions for PHU that executes 
 *                      processes specific to the sample application. These 
 *                      processes may include but not limited to configuration of
 *                      parameters, demo process, and so on.
 *
 *  Copyright (c) 2012 Ingenico. All Rights Reserved.
 *
 *  Ingenico has intellectual property rights relating to the technology 
 *  embodied in this software.  In particular, and without limitation, 
 *  these intellectual property rights may include one or more patents.
 *
 *  This software is distributed under licenses restricting its use, 
 *  copying, distribution, and decompilation. No part of this software may be 
 *  reproduced in any form by any means without prior written authorization of 
 *  Ingenico.
 *
 * 
 *  HISTORY         :
 *
 *  Author:          Ingenico R&D Philippines Team
 *  Modification:    Creation
 *  Date:            2012/09/17
-*/

#include "sdk30.h"
#include "utilities.h"
#include "pmu_parammngt.h"
#include "epu_errprocess.h"
#include "uiu_userinterface.h"
#include "dfu_demofeatures.h"

static void _phuStateUpdate(unsigned long key);
static void _phuConfigStateServerAddressGet( void );
static void _phuConfigStateServerPortGet( void );

/** List of states for the parameter configuration.
 */
enum {
    CFG_STATE_START,
    CFG_STATE_ADDRESS_GET,
    CFG_STATE_PORT_GET,
    CFG_STATE_END
};


static void _phuStateUpdate(unsigned long key)
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
            stateSet(CFG_STATE_END);
            break;
    }
}

static void _phuConfigStateServerAddressGet( void )
{
    unsigned long key;
    PMU_Param_t param;
    PMU_Param_t *currentParam = NULL;
    int ret = 0;

    currentParam = PMU_ParamGet();

    memcpy(&param, currentParam, sizeof(PMU_Param_t));

    /* There is no checking of host name since it is not necessary.
     * Any value can be entered as host name. The DNS server will
     * still resolve it. If such host name can't be resolved,
     * then it doesn't exist.
     */
    key = enterTxt("Input Address", "Hostname :", param.host, PMU_HOST_NAME_LEN_MAX);
    if (key==GL_KEY_VALID)
    {
        ret = PMU_ParamSet(&param);
        trcS("Address: ");
        trcS(param.host);
        trcS("\n");
    }
    _phuStateUpdate(key);
}

static void _phuConfigStateServerPortGet( void )
{
    char buf[PMU_HOST_PORT_NUM_LEN_MAX+ 1];
    unsigned long key;
    PMU_Param_t param;
    PMU_Param_t *currentParam = NULL;
    int ret = 0;

    currentParam = PMU_ParamGet();
    memcpy(&param, currentParam, sizeof(PMU_Param_t));

    sprintf( buf, "%i", currentParam->port);

    key = enterTxt("Input Port", "Port :", buf, sizeof(buf));
    if (key == GL_KEY_VALID)
    {
        param.port = atoi( buf );
        /* Port number is a 16-bit value. Therefore the maximum
         * value is 65536. In the dialog, the user can enter a
         * 5-digit value which is in the range 0 ~ 99999.
         */
        if(param.port > PMU_HOST_PORT_VALUE_MAX)// If port is invalid, user will re-enter again the desired port number
        {
            UIU_ErrMsgDisplay(EPU_ERR_INVALID_PORT_NUM);
            return;
        }
        ret = PMU_ParamSet(&param);
        trcS("Port: ");
        trcS(buf);
        trcS("\n");
    }
    _phuStateUpdate(key);
}

void phuParamConfigProcess( void )
{
    int currentState;

    stateSet(CFG_STATE_START);
    stateNext();
    do
    {
        currentState = stateGet();
        switch(currentState)
        {
            case CFG_STATE_ADDRESS_GET:
                _phuConfigStateServerAddressGet();
                break;

            case CFG_STATE_PORT_GET:
                _phuConfigStateServerPortGet();
                break;

            default:
                stateSet(CFG_STATE_END);
                break;
        }
    } while(currentState != CFG_STATE_END);
}


void phuTestClientProcess( void )
{
    DFU_ComClientConnect((PMU_ParamGet())->host, (PMU_ParamGet())->port, "/");
}

void phuTestServerProcess( void )
{
    DFU_ComServerStart();
}

void phuTestNetInfoProcess( void )
{
    DFU_ComNetInfoDisplay();
}


