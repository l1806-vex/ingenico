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
   
 Project : Telium Pass Sample
 Module  : FUN - Demo Features Unit

 @file      fun_iso.c
 @brief     This file contains the definition of processes that is implemented
            by this sample.
            
 @date      08/03/2013

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "SDK30.H"
#include "TlvTree.h"
#include "TPass.h"
#include "Cless_HighLevel.h"
#include "oem_cless.h"
#include <oem_clmf1.h>
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"		// Telium Pass include DLL

#include "utilities.h"
#include "err_process.h"
#include "ui_userinterface.h"
#include "fun_demofeatures.h"
#include "trace.h"

static void _FUN_StateUpdateIso(int res);
static int _FUN_IsoGetError(int err);
static int _FUN_IsoStart(void);
static void _FUN_IsoStop(void);
static int _FUN_IsoDetect (int async, int dly);
static int _FUN_IsoDetectCard(int test);
static int _FUN_IsoActivate(void);
static int _FUN_IsoSend(void);
static int _FUN_IsoDeselect(void);

static TRC_Trace_t trc_fun;

/** List of states for the differen mifare transaction stages.
 */
enum {
    FUN_ISO_STATE_START,
    FUN_ISO_STATE_DETECT,
    FUN_ISO_STATE_ACTIVATE,
    FUN_ISO_STATE_SEND,
    FUN_ISO_STATE_DESELECT,
    FUN_ISO_STATE_END
};

/** Update the next state based from the execution result of the previous state
 *
 * \param[in] res result of previous state
 *
 * \return
 *      - \ref None
 */
static void _FUN_StateUpdateIso(int res)
{
    switch(res)
    {
        case 1:
            stateNext();
            break;

        default: // Cancel
            stateSet(FUN_ISO_STATE_END);
            break;
    }
}

/** Process the result of the ISO processing
 *
 * \param[in] err result of previous excecution
 *
 * \return
 *      - \ref None
 */
static int _FUN_IsoGetError(int err)
{
    switch(err)
    {
        case CL_OK:
            TRC_TRACE_INFO(trc_fun, "Cless OK");
            return 1;

        case CL_NOCARD:
            TRC_TRACE_ERR(trc_fun, "No card detected");
            UI_ErrMsgDisplay(ERR_NO_CARD_DETECTED);
            break;

        case CL_TOOMANYCARDS:
            TRC_TRACE_ERR(trc_fun, "Too many cards on the reader");
            UI_ErrMsgDisplay(ERR_TOO_MANY_CARDS);
            break;

        case CL_INVALIDCARD:
            TRC_TRACE_ERR(trc_fun, "The presented card is not valid");
            UI_ErrMsgDisplay(ERR_INVALID_CARD);
            break;

        default:
            TRC_TRACE_ERR(trc_fun, "An error occurs during the card detection err=%d", err);
            UI_ErrMsgDisplay(ERR_UNDEFINED);
            break;
    }
    return 0;
}

/** Open the cless card reader, but not wait for card detection
 * \return CL_OK if OK; CL_KO if an error occured
 */
static int _FUN_IsoStart(void)
{
    int ret=FALSE;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_IsoStart");
    err = ClessEmv_OpenDriver();

    ret = _FUN_IsoGetError(err);
    return ret;
}

/** Stop the cless card reader and
 * Close the associated channel.
 */
static void _FUN_IsoStop(void)
{
    TRC_TRACE_INFO(trc_fun, "_FUN_IsoStop");
    ClessEmv_CloseDriver();
}

/** Detect ISO14443-4 contactless card
 * \return 1 if OK; 0 on error
 */
static int _FUN_IsoDetect (int async, int dly)
{
    int ret=0;
    int err;
    unsigned int maxCards;

    maxCards = 1;

    TRC_TRACE_INFO(trc_fun, "_FUN_IsoDetect");

    TPass_FirstLine();
    TPass_Display("\n\nTAP\nCARD");
    TRC_TRACE_INFO(trc_fun, "TAP CARD");

    if (async==1)
    {
        err = ClessEmv_DetectCardsStart(maxCards, CL_TYPE_AB);
        ret = _FUN_IsoGetError(err);
        if (ret==0)
        {
            return ret;
        }

        while (1)
        {
            ret = ttestall(KEYBOARD | CLESS, dly * 100);
            if(ret == KEYBOARD)
            {
                if(getchar() == T_ANN)
                {
                    TRC_TRACE_INFO(trc_fun, "Card Detection Cancelled");
                    ret = 0;
                    break;
                }
            }
            else
            {
                if(ret == 0) //timeout
                {
                    TRC_TRACE_INFO(trc_fun, "Timeout");
                    break;
                }

                TRC_TRACE_INFO(trc_fun, "Card Detected");
                err = ClessEmv_DetectCards(CL_TYPE_AB, &maxCards, 1);
                ret = _FUN_IsoGetError(err);
                break;
            }
        }
    }
    else // Synchronous mode
    {
        // Deselect the card (synchronous mode)
        err = ClessEmv_DetectCards(CL_TYPE_AB, &maxCards, dly);
        ret = _FUN_IsoGetError(err);
    }

    ClessEmv_DetectCardsStop();
    return ret;
}

/** Perform an operations on a mifare card based on the test Id
 * \return 1 if OK; 0 on error
 */
static int _FUN_IsoDetectCard(int test)
{
    int ret=0;

    TPass_FirstLine();
    TPass_Display("\n\nPRESENT\nCARD");
    TRC_TRACE_INFO(trc_fun, "PRESENT CARD");

    switch (test)
    {
        case 0:
            ret = _FUN_IsoDetect(0, 3);
            break;

        case 1:
            ret = _FUN_IsoDetect(1, 3);
            break;

        case 2:
        case 3:
            ret = _FUN_IsoDetect(0, 30);
            break;

        default:
            ret = _FUN_IsoDetect(1, 30);
            break;
    }

    return ret;
}


/** Activate mifare card
 * \return 1 if OK; 0 on error
 */
static int _FUN_IsoActivate(void)
{
    int ret=0;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_IsoActivate");

    TPass_FirstLine();
    TPass_Display("\n\nCARD\nACTIVATION");
    TRC_TRACE_INFO(trc_fun, "CARD ACTIVATION");

    err = ClessEmv_ActiveCard(0, CL_ISO14443_4);

    ret = _FUN_IsoGetError(err);
    return ret;
}

static int _FUN_IsoSend(void)
{
    int ret=0;
    int err;
    int idx;
    char tmp[8];
    char buf[256];
    static const unsigned char selectPPSE[] =
        { 0x00, 0xa4, 0x04, 0x00, 0x0e, 0x32, 0x50, 0x41, 0x59, 0x2e, 0x53, 0x59, 0x53, 0x2e, 0x44, 0x44, 0x46, 0x30, 0x31, 0x00};
    unsigned char rsp[256];
    unsigned int len;

    TRC_TRACE_INFO(trc_fun, "_FUN_IsoSend");

    TPass_FirstLine();
    TPass_Display("\n\nSEND \nAPDU");
    TRC_TRACE_INFO(trc_fun, "SEND APDU");

    len = 256;

    memset(buf, 0, sizeof(buf));
    for (idx=0; idx<sizeof(selectPPSE);idx++)
    {
        memset(tmp, 0, sizeof(tmp));
        sprintf(tmp, "%02X ", (unsigned short)selectPPSE[idx]);
        strcat(buf, tmp);
    }

    TRC_TRACE_INFO(trc_fun, "Command = ");
    TRC_TRACE_INFO(trc_fun, buf);


    // Send the APDU to the card
    err = ClessEmv_Apdu(0, selectPPSE, sizeof(selectPPSE), rsp, &len);

    memset(buf, 0, sizeof(buf));
    for (idx=0; idx<len;idx++)
    {
        memset(tmp, 0, sizeof(tmp));
        sprintf(tmp, "%02X ", (unsigned short)rsp[idx]);
        strcat(buf, tmp);
    }

    TRC_TRACE_INFO(trc_fun, "Response = ");
    TRC_TRACE_INFO(trc_fun, buf);
    TRC_TRACE_INFO(trc_fun, "Length = %d", len);

    ret = _FUN_IsoGetError(err);
    return ret;
}

static int _FUN_IsoDeselect(void)
{
    int ret=0;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_IsoDeselectCard");

    TPass_FirstLine();
    TPass_Display("\n\nDESELECT\nCARD");
    TRC_TRACE_INFO(trc_fun, "DESELECT CARD");

    err = ClessEmv_DeselectCard(0, 1, 1);

    ret = _FUN_IsoGetError(err);
    return ret;
}

void FUN_IsoTest(int test)
{
    int ret=0;
    int currentState;

    _FUN_IsoStart();

    trc_fun = TRC_HandleGet();

    stateSet(FUN_ISO_STATE_START);
    stateNext();
    do
    {
        currentState = stateGet();
        switch(currentState)
        {
            case FUN_ISO_STATE_DETECT:
                ret = _FUN_IsoDetectCard(test);
                _FUN_StateUpdateIso(ret);
                break;

            case FUN_ISO_STATE_ACTIVATE:
                ret = _FUN_IsoActivate();
                _FUN_StateUpdateIso(ret);
                break;

            case FUN_ISO_STATE_SEND:
                ret = _FUN_IsoSend();
                _FUN_StateUpdateIso(ret);
                break;

            case FUN_ISO_STATE_DESELECT:
                ret = _FUN_IsoDeselect();
                _FUN_StateUpdateIso(ret);
                break;

            default:
                stateSet(FUN_ISO_STATE_END);
                break;
        }
    } while(currentState != FUN_ISO_STATE_END);

    if (ret==1)
    {
        UI_PromptMsgDisplay(UI_PROMPT_MSG_TEST_OK);
    }
    else
    {
        UI_PromptMsgDisplay(UI_PROMPT_MSG_TEST_FAILED);
    }

    _FUN_IsoStop();
}

#ifdef __cplusplus
}
#endif
