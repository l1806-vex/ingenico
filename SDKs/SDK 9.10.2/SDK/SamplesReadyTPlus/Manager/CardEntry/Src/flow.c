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
   
 Project : Card Entry Sample
 Module  : FLOW - Process Handling Unit

 @file      flow.c
 @brief     Contains all functions definitions for FLOW that executes 
            processes specific to the sample application. These 
            processes may include but not limited to configuration of
            parameters, demo process, and so on.
            
 @date      30/04/2013

 ------------------------------------------------------------------------------
 */


#ifdef __cplusplus
extern "C" {
#endif

#include "sdk30.h"
#include "GL_GraphicLib.h"

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

/** List of states for the Trace configuration.
 */
enum {
    CFG_TRACE_OUTPUT_START,
    CFG_TRACE_OUTPUT_GET,
    CFG_TRACE_OUTPUT_END
};

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

#ifdef __cplusplus
}
#endif

