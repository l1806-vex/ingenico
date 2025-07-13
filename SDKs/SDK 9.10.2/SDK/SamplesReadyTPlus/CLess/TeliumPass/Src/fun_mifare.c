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

 @file      fun_mifare.c
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

#include "oem_cless.h"    // Telium Pass include driver
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"		  // Telium Pass include DLL
#include "oem_clmf1.h"    // Mifare

#include "utilities.h"
#include "err_process.h"
#include "ui_userinterface.h"
#include "fun_demofeatures.h"
#include "trace.h"

// Mifare constant
#define MONEY_SECTORS_NUMBER	1
#define ACCESS_SECTORS_NUMBER	6
#define READ_SECTORS_NUMBER		9
#define WRITE_SECTORS_NUMBER	9

//MF1
#define READ			0x30
#define INCREMENT		0xC1
#define DECREMENT		0xC0
#define WRITE			0xA0

static void _FUN_StateUpdateMifare(int res);
static int _FUN_MifareGetError(int err);
static int _FUN_MifareStart(void);
static void _FUN_MifareStop(void);
static int _FUN_MifareDetect (unsigned int dly);
static int _FUN_MifareActivate(void);
static int _FUN_MifareAuthenticate(int test);
static int _FUN_MifareLoad(void);
static int _FUN_MifareSave(void);
static int _FUN_MifareCredit(void);
static int _FUN_MifareDebit(void);
static int _FUN_MifareOperation(int test);

typedef byte t_MF_Key[6];		// define the lenght of a key for CRYPTO1
static TRC_Trace_t trc_fun;

// define the key (A) for money payment (sector=0)
static const t_MF_Key MoneyKey_A[MONEY_SECTORS_NUMBER] = {{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}};

// define the key (B) for money payment (sector=0)
static const t_MF_Key MoneyKey_B[MONEY_SECTORS_NUMBER] = {{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}};

/** List of states for the differen mifare transaction stages.
 */
enum {
    FUN_MIFARE_STATE_START,
    FUN_MIFARE_STATE_DETECT,
    FUN_MIFARE_STATE_ACTIVATE,
    FUN_MIFARE_STATE_AUTHENTICATE,
    FUN_MIFARE_STATE_OPERATION,
    FUN_MIFARE_STATE_END
};

/** Update the next state based from the execution result of the previous state
 *
 * \param[in] res result of previous state
 *
 * \return
 *      - \ref None
 */
static void _FUN_StateUpdateMifare(int res)
{
    switch(res)
    {
        case 1:
            stateNext();
            break;

        default: // Cancel
            stateSet(FUN_MIFARE_STATE_END);
            break;
    }
}

/** Process the result of the mifare processing
 *
 * \param[in] err result of previous excecution
 *
 * \return
 *      - \ref None
 */
static int _FUN_MifareGetError(int err)
{
    switch(err)
    {
        case MF_OK: // The Mifare card is correctly detected
            TRC_TRACE_INFO(trc_fun, "Mifare OK");
            return 1;

        case MF_TOOMANYCARDS:
            TRC_TRACE_ERR(trc_fun, "Too many cards are presented");
            UI_ErrMsgDisplay(ERR_TOO_MANY_CARDS);
            break;

        case MF_NO_CARD:
            TRC_TRACE_ERR(trc_fun, "There is no card (timeout)");
            UI_ErrMsgDisplay(ERR_NO_CARD_DETECTED);
            break;

        case MF_INVALIDCARD:
            TRC_TRACE_ERR(trc_fun, "The detected card is not a MIFARE one");
            UI_ErrMsgDisplay(ERR_INVALID_CARD);
            break;

        case MF_KO:
        default:
            TRC_TRACE_ERR(trc_fun, "An error occurred err=%d", err);
            UI_ErrMsgDisplay(ERR_UNDEFINED);
            break;
    }

    return 0;
}

/** Open the mifare card reader, but not wait for card detection
 * \return CL_OK if OK; CL_KO if an error occured
 */
static int _FUN_MifareStart(void)
{
    int ret=FALSE;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareStart");
    err = ClessMifare_IsDriverOpened();
    if(!err) {
        err = ClessMifare_OpenDriver();
    }

    ret = _FUN_MifareGetError(err);
    return ret;
}

/** Stop the mifare card reader and
 * Close the associated channel.
 */
static void _FUN_MifareStop(void)
{
    TRC_TRACE_INFO(trc_fun, "_FUN_MifareStop");
    ClessMifare_CloseDriver();
}

/** Detect mifare card
 * \return 1 if OK; 0 on error
 */
static int _FUN_MifareDetect (unsigned int dly)
{
    int ret=0;
    int err;
    unsigned int maxCards;

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareDetect");

    maxCards = 100;
    TPass_FirstLine();
    TPass_Display("\n\nTAP\nCARD");
    TRC_TRACE_INFO(trc_fun, "TAP CARD");

    err = ClessMifare_DetectCards(&maxCards, dly);

    ret = _FUN_MifareGetError(err);
    return ret;
}

/** Activate mifare card
 * \return 1 if OK; 0 on error
 */
static int _FUN_MifareActivate(void)
{
    int ret=0;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareActivate");

    TPass_FirstLine();
    TPass_Display("\n\nCARD\nACTIVATION");
    TRC_TRACE_INFO(trc_fun, "CARD ACTIVATION");

    err = ClessMifare_ActiveCard(0); //activate the 1st card

    ret = _FUN_MifareGetError(err);
    return ret;
}

/** Authenticate mifare card
 * \param test (I) authentication test to be performed
 * \return 1 if OK; 0 on error
 */
static int _FUN_MifareAuthenticate(int test)
{
    int ret;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareAuthenticate");

    TPass_FirstLine();
    TPass_Display("\n\nCARD\nAUTHENTICATION");
    TRC_TRACE_INFO(trc_fun, "CARD AUTHENTICATION");

        err = ClessMifare_Authentication(KEY_A, MoneyKey_B[0], 0);

    ret = _FUN_MifareGetError(err);
    return ret;
}

/** Load data from mifare card
 * \return 1 if OK; 0 on error
 */
static int _FUN_MifareLoad(void)
{
    int ret;
    int err;
    unsigned char buf[16];

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareLoad");

    TPass_FirstLine();
    TPass_Display("\n\nLOAD\nDATA");
    TRC_TRACE_INFO(trc_fun, "LOAD DATA");

    memset(buf, 0, sizeof(buf));
    err = ClessMifare_ReadBlock(VALUE, 0, 1, buf);
    if (err==MF_OK)
    {
        TRC_TRACE_INFO(trc_fun, "BLOCK = %02X %02X %02X %02X", buf[0], buf[1], buf[2], buf[3]);
    }

    ret = _FUN_MifareGetError(err);
    return ret;
}

/** Save data to mifare card
 * \return 1 if OK; 0 on error
 */
static int _FUN_MifareSave(void)
{
    int ret;
    int err;
    unsigned char buf[16];

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareSave");

    TPass_FirstLine();
    TPass_Display("\n\nSAVE\nDATA");
    TRC_TRACE_INFO(trc_fun, "SAVE DATA");

    memset(buf, 0, sizeof(buf));
    err = ClessMifare_WriteBlock(VALUE, 0, 1, buf);

    ret = _FUN_MifareGetError(err);
    return ret;
}

/** Credit mifare card
 * \return 1 if OK; 0 on error
 */
static int _FUN_MifareCredit(void)
{
    int ret=0;
    int err;
    unsigned char amt[4];

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareCredit");

    TPass_FirstLine();
    TPass_Display("\n\ncredit\noperation");
    TRC_TRACE_INFO(trc_fun, "Credit Operation");

    memset(amt, 0, sizeof(amt));
    amt[0] = 200;
    err = ClessMifare_ValueOperation(INCREMENT, 0, 1, 1, &amt);

    ret = _FUN_MifareGetError(err);
    return ret;
}

/** Debit mifare card
 * \return 1 if OK; 0 on error
 */
static int _FUN_MifareDebit(void)
{
    int ret=0;
    int err;
    unsigned char amt[4];

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareDebit");

    TPass_FirstLine();
    TPass_Display("\n\ndebit\noperation");
    TRC_TRACE_INFO(trc_fun, "Debit Operation");

    memset(amt, 0, sizeof(amt));
    amt[0] = 3;
    err = ClessMifare_ValueOperation(DECREMENT, 0, 1, 1, &amt);

    ret = _FUN_MifareGetError(err);
    return ret;
}

/** Perform an operations on a mifare card based on the test Id
 * \return 1 if OK; 0 on error
 */
static int _FUN_MifareOperation(int test)
{
    int ret=0;

    switch (test)
    {
        case 1:
            ret = _FUN_MifareCredit();
            break;
        case 2:
            ret = _FUN_MifareDebit();
            break;
        case 3:
            ret = _FUN_MifareLoad();
            break;
        case 4:
            ret = _FUN_MifareSave();
            break;
        default:
            break;
    }

    return ret;
}


void FUN_MifareTest(int test)
{
    int ret;
    int currentState;

    trc_fun = TRC_HandleGet();

    ret = _FUN_MifareStart();
    if (ret!=1)
    {
        UI_ErrMsgDisplay(ERR_OPEN_DRIVER_FAILED);
        return;
    }

    stateSet(FUN_MIFARE_STATE_START);
    stateNext();
    do
    {
        currentState = stateGet();
        switch(currentState)
        {
            case FUN_MIFARE_STATE_DETECT:
                ret = _FUN_MifareDetect(15);
                _FUN_StateUpdateMifare(ret);
                break;

            case FUN_MIFARE_STATE_ACTIVATE:
                ret = _FUN_MifareActivate();
                _FUN_StateUpdateMifare(ret);
                if (test == 0)
                {
                    stateSet(FUN_MIFARE_STATE_END);
                }
                break;

            case FUN_MIFARE_STATE_AUTHENTICATE:
                ret = _FUN_MifareAuthenticate(test);
                _FUN_StateUpdateMifare(ret);
                break;

            case FUN_MIFARE_STATE_OPERATION:
                ret = _FUN_MifareOperation(test);
                _FUN_StateUpdateMifare(ret);
                break;

            default:
                stateSet(FUN_MIFARE_STATE_END);
                break;
        }
    } while(currentState != FUN_MIFARE_STATE_END);

    if (ret==1)
    {
        UI_PromptMsgDisplay(UI_PROMPT_MSG_TEST_OK);
    }
    else
    {
        UI_PromptMsgDisplay(UI_PROMPT_MSG_TEST_FAILED);
    }

    _FUN_MifareStop();
}

#ifdef __cplusplus
}
#endif

