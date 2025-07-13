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
   
 Project : Dll Security Sample
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
#include "SEC_interface.h"

#include "flow.h"
#include "utilities.h"
#include "err_process.h"
#include "ui_userinterface.h"
#include "fun_demofeatures.h"
#include "par.h"
#include "trace.h"

static int _FLOW_ParGetError(int err);
static void _FLOW_StateUpdateTraceOutput(unsigned long key);
static void _FLOW_ConfigStateTraceOutputGet(void);
static void _FLOW_StateUpdate(unsigned long key);
static void _FLOW_ConfigStateSecurePartGet(void);
static void _FLOW_ConfigStateBoosterProductGet(void);

/** List of states for the Trace configuration.
 */
enum {
    CFG_TRACE_OUTPUT_START,
    CFG_TRACE_OUTPUT_GET,
    CFG_TRACE_OUTPUT_END
};

/** List of states for the parameter configuration.
 */
enum {
    CFG_SEC_STATE_START,
    CFG_SEC_STATE_SECURE_PART_GET,
    CFG_SEC_STATE_BOOSTER_PRODUCT_GET,
    CFG_SEC_STATE_END
};

static int idx;
static TRC_Trace_t trc_flow;

/** Process the result of the PAR processing
 * \param[in] err result of previous excecution
 * \return 1 if OK; 0 on error
 */
static int _FLOW_ParGetError(int err)
{
    switch(err)
    {
        case PAR_OK:
            TRC_TRACE_INFO(trc_flow, "PAR OK");
            return 1;

        case PAR_ACCESS_DENIED:
            TRC_TRACE_ERR(trc_flow, "Access Denied");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_ACCESS_DENIED);
            break;

        case PAR_INVALID_DATA:
            TRC_TRACE_ERR(trc_flow, "Invalid Data");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_INVALID_DATA);
            break;

        case PAR_INVALID_DATA_LEN:
            TRC_TRACE_ERR(trc_flow, "Invalid Data Length");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_INVALID_DATA_LEN);
            break;

        default:
            TRC_TRACE_ERR(trc_flow, "An error occurs during the Parameter processing err=%d", err);
            UI_ErrMsgDisplay(ERR_UNDEFINED);
            break;
    }
    return 0;
}


/** Set the next TMS-IP State based from the result of the previous state
 */
static void _FLOW_StateUpdateTraceOutput(unsigned long key)
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
            stateSet(CFG_TRACE_OUTPUT_END);
            break;
    }
}

/** Configure the Host to be used for the TMS-IP connection
 * The initial value will be obtained from the database.
 * If the user enters a valid data, it will be stored to the database
 */
static void _FLOW_ConfigStateTraceOutputGet(void)
{
    int ret;
    enum etrcOutput data;
    unsigned long key;
    const char *menu[]=
    {
        "Telium Trace",
        "Remote Debug",
        "Internal File",
        //"External File - USB",
        //"External File - MMC",
        "Printer",
        //"UDP-IP",
        0
    };

    ret = PAR_TrcOutputGet(&data);
    if (ret!=PAR_OK)
    {
        _FLOW_ParGetError(ret); 
        _FLOW_StateUpdateTraceOutput(GL_KEY_CANCEL);
        return;
    }

    //move selected  item since other trace output streams are not supported
    if (data == trcOutput_printer)
    {
        data = trcOutput_externalFileUsb;
    }

    key = guiMenu( mnuTypeDialog, data, "Trace Output Stream", (const char **)menu);
    switch (key)
    {
        case 0:
        case 1:
        case 2:
            PAR_TrcOutputSet(key);
            TRC_TRACE_INFO(trc_flow, "Trace Output: %s", menu[key]);
            TRC_Init();
            key = GL_KEY_VALID;
            break;
        case 3:
            PAR_TrcOutputSet(trcOutput_printer);
            TRC_TRACE_INFO(trc_flow, "Trace Output: %s", menu[key]);
            TRC_Init();
            key = GL_KEY_VALID;
            break;

        default:
            break;
    }

    _FLOW_StateUpdateTraceOutput(key);
}

void FLOW_ParamConfigTraceProcess(void)
{
    int currentState;

    trc_flow = TRC_HandleGet();

    stateSet(CFG_TRACE_OUTPUT_START);
    stateNext();
    do
    {
        currentState = stateGet();
        switch(currentState)
        {
            case CFG_TRACE_OUTPUT_GET:
                _FLOW_ConfigStateTraceOutputGet();
                break;

            default:
                stateSet(CFG_TRACE_OUTPUT_END);
                break;
        }
    } while(currentState != CFG_TRACE_OUTPUT_END);
}

/** Set the next Config State based from the result of the previous state
 */
static void _FLOW_StateUpdate(unsigned long key)
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
            stateSet(CFG_SEC_STATE_END);
            break;
    }
}


/** Configure the baud rate to be used for the GSM connection
 * The initial value will be obtained from the database and the item will be
 * highlighted on the menu. 
 * If the user selects a valid baud rate, it will be stored to the database
 */
static void _FLOW_ConfigStateSecurePartGet(void)
{
    int ret;
    int len;
    int sel;
    unsigned long key;
    unsigned char data[2+1];
    const char *menu[]=
    {
        "PIN ENTRY KEYBOARD",
        "CARD READER LOCATION",
        "KEY FOR DATA CIPHERING",
        0
    };

    ret = 0;
    len = 0;
    sel=0;
    memset(data, 0, sizeof(data));
    key = guiMenu( mnuTypeDialog, sel, "Config", (const char **)menu);
    switch (key)
    {
        case securePart_Pincode:
        case securePart_Card:
        case securePart_Ciphering:
            idx = key;
            len = 1;
            break;
        default:
            break;
    }

    if (len>0)
    {
        key = GL_KEY_VALID;
    }

    _FLOW_StateUpdate(key);
}

static int _FLOW_ConfigPinpadTypeGet(int * boost)
{
    int ret;

    *boost = 0;
    ret = PSQ_Is_pinpad();
    if (ret != 0)
    {
        ret = PSQ_Pinpad_Value();
        switch (ret)
        {
            case PP30_PPAD:
                *boost = 1;
                return C_SEC_BL2;

            case PPC30_PPAD:
            case PPR30_PPAD:
            case P30_PPAD:
                *boost = 1;
                return C_SEC_BL1;

            default :
                break;
        }
    }

    return C_SEC_BL1;
}

/** Configure the RLP mode to be used for the GSM connection
 * The initial value (Activated or Deactivated) will be obtained from the database 
 * and the item will be highlighted on the menu. 
 * If the user selects a valid RLP mode, it will be stored to the database
 */
static void _FLOW_ConfigStateBoosterProductGet(void)
{
    int ret;
    int sel;
    int pinpad;
    enum eperipheralBooster booster;
    char ppBoosterType;
    unsigned long key;
    unsigned char data[1+1];
    const char *menu[]=
    {
        "Terminal",
        "Pinpad",
        0
    };

    ret = PAR_SecConfig_PeripheralBoosterGet(idx, &booster);
    if (ret == PAR_OK)
    {
        switch (booster)
        {
            case peripheralBooster_iappUsbName:
                sel =1;
                break;
            case peripheralBooster_iappDefName:
            default:
                sel=0;
                break;
        }
    }

    ppBoosterType = _FLOW_ConfigPinpadTypeGet(&pinpad);

    memset(data, 0, sizeof(data));
    key = guiMenu(mnuTypeDialog, sel, "Booster", (const char **)menu);
    switch (key)
    {
        case 0:
            PAR_SecConfig_PeripheralBoosterSet(idx, peripheralBooster_iappDefName);
            PAR_SecConfig_TerminalBoosterSet(idx, terminalBooster_Booster2);
            break;
        case 1: 
            if (pinpad==1)
            {
                PAR_SecConfig_PeripheralBoosterSet(idx, peripheralBooster_iappUsbName);
                PAR_SecConfig_PinpadBoosterSet(idx, ppBoosterType);
            }
            break;
        default:
            break;
    }

    _FLOW_StateUpdate(key);
}

void FLOW_ConfigParamProcess(void)
{
    int currentState;

    idx=0;
    stateSet(CFG_SEC_STATE_START);
    stateNext();
    do
    {
        currentState = stateGet();
        switch(currentState)
        {
            case CFG_SEC_STATE_SECURE_PART_GET:
                _FLOW_ConfigStateSecurePartGet();
                break;

            case CFG_SEC_STATE_BOOSTER_PRODUCT_GET:
                _FLOW_ConfigStateBoosterProductGet();
                break;

            default:
                stateSet(CFG_SEC_STATE_END);
                break;
        }
    } while(currentState != CFG_SEC_STATE_END);
}

#ifdef __cplusplus
}
#endif

