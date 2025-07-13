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
   
 Project : Mifare Sample
 Module  : FUN - Demo Features Unit

 @file      fun_mifare.c
 @brief     This file contains the definition of processes that is implemented
            by this sample.
            
 @date      08/03/2013

 ------------------------------------------------------------------------------
 */

#include "SDK30.H"
#include "ClessMFP.h"
#include "Desfire.h"
#include "Cless_LowLevel.h"     // low level interface of the contactless DLL.
#include "oem_cless.h"          // Telium Pass include driver
#include "oem_clmf1.h"          // Mifare

#include "utilities.h"
#include "err_process.h"
#include "ui_userinterface.h"
#include "fun_demofeatures.h"
#include "trace.h"

#define SL0 0
#define SL1 1
#define SL2 2
#define SL3 3

static int _FUN_IsoGetError(int err);
static int _FUN_IsoStart(void);
static int _FUN_IsoDetect (int async, int dly);
static int _FUN_IsoActivate(void);
static int _FUN_MifareGetError(int err);
static int _FUN_MifareStart(void);
static int _FUN_MifareDetect (unsigned int dly);
static int _FUN_MifareDetectSAM(void);
static int _FUN_MifareActivate(void);
static int _FUN_MfpGetError(int err);
static int _FUN_MfpCreateContext(int sam, int secLvl);
static int _FUN_MfpAuthenticate(int sam, int secLvl);
static int _FUN_MfpWrite(int secLvl, unsigned char cmd, unsigned short blk, unsigned char blkSize, void* buf);
static int _FUN_MfpWritePerso(unsigned short blk, void* data);
static int _FUN_MfpCommitPerso(void);
static int _FUN_MfpRead(int secLvl, unsigned char cmd, unsigned short blk, unsigned char blkSize, void* buf);
static int _FUN_MfpOperation(int secLvl, unsigned char cmd, unsigned short blk, unsigned char addBlk, void* buf);
static int _FUN_MifareFree(void);

static TRC_Trace_t trc_fun;
static T_MFP_CONTEXT* context = NULL;
FILE* hdlSAM = NULL;

/** Process the result of the ISO processing
 * \param[in] err result of previous excecution
 * \return 1 if OK; 0 on error
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
    err = ClessEmv_IsDriverOpened();
    if(!err) {
        err = ClessEmv_OpenDriver();
    }

    ret = _FUN_IsoGetError(err);
    return ret;
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

    guiDrawCreate();
    ret = TPass_GetDeviceType();
    if (ret == TPASS_CLESS_TYPE_TELIUM_PASS)
    {
        TRC_TRACE_INFO(trc_fun, "TAP CARD");
        TPass_FirstLine();
        TPass_Display("\n\nTAP\nCARD");
        guiDrawText(30, 30, 15, 15, "Processing...");
    }
    else
    {
        guiDrawText(30, 30, 15, 15, "TAP CARD");
    }
    guiDrawDisplay();

    if (async==1)
    {
        err = ClessEmv_DetectCardsStart(maxCards, CL_TYPE_A);
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
        err = ClessEmv_DetectCards(CL_TYPE_A, &maxCards, dly);
        ret = _FUN_IsoGetError(err);
    }

    ClessEmv_DetectCardsStop();
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

    guiDrawCreate();
    ret = TPass_GetDeviceType();
    if (ret == TPASS_CLESS_TYPE_TELIUM_PASS)
    {
        TRC_TRACE_INFO(trc_fun, "CARD ACTIVATION");
        TPass_FirstLine();
        TPass_Display("\n\nCARD\nACTIVATION");
        guiDrawText(30, 30, 15, 15, "Activating...");
    }
    else
    {
        guiDrawText(30, 30, 15, 15, "Card Activation");
    }
    guiDrawDisplay();

    err = ClessEmv_ActiveCard(0, CL_ISO14443_4);

    ret = _FUN_IsoGetError(err);
    return ret;
}

/** Process the result of the mifare processing
 * \param[in] err result of previous excecution
 * \return 1 if OK; 0 on error
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
    guiDrawCreate();
    ret = TPass_GetDeviceType();
    if (ret == TPASS_CLESS_TYPE_TELIUM_PASS)
    {
        TRC_TRACE_INFO(trc_fun, "TAP CARD");
        TPass_FirstLine();
        TPass_Display("\n\nTAP\nCARD");
        guiDrawText(30, 30, 15, 15, "Processing...");
    }
    else
    {
        guiDrawText(30, 30, 15, 15, "TAP CARD");
    }
    guiDrawDisplay();

    err = ClessMifare_DetectCards(&maxCards, dly);

    ret = _FUN_MifareGetError(err);
    return ret;
}

/** Detect and activation of SAM
 * \return 1 if OK; 0 on error
 */
static int _FUN_MifareDetectSAM(void)
{
    TRC_TRACE_INFO(trc_fun, "_FUN_MifareDetectSAM");
    hdlSAM = mifareSAM_AutoDetectSAM();
    if (hdlSAM == NULL)
    {
        TRC_TRACE_INFO(trc_fun, "SAM not found");
        return 0;
    }
    TRC_TRACE_INFO(trc_fun, "SAM found");

    return 1;
}


/** Activate mifare card
 * \return 1 if OK; 0 on error
 */
static int _FUN_MifareActivate(void)
{
    int ret=0;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareActivate");

    guiDrawCreate();
    ret = TPass_GetDeviceType();
    if (ret == TPASS_CLESS_TYPE_TELIUM_PASS)
    {
        TRC_TRACE_INFO(trc_fun, "CARD ACTIVATION");
        TPass_FirstLine();
        TPass_Display("\n\nCARD\nACTIVATION");
        guiDrawText(30, 30, 15, 15, "Activating...");
    }
    else
    {
        guiDrawText(30, 30, 15, 15, "Card Activation");
    }
    guiDrawDisplay();

    err = ClessMifare_ActiveCard(0); //activate the 1st card

    ret = _FUN_MifareGetError(err);
    return ret;
}

/** Process the result of the mifare plus processing
 * \param[in] err result of previous excecution
 * \return 1 if OK; 0 on error
 */
static int _FUN_MfpGetError(int err)
{
    switch(err)
    {
        case MFP_OK: // The Mifare plus card is correctly detected
            TRC_TRACE_INFO(trc_fun, "Mfp OK");
            return 1;

        case MFP_PARAMETER_ERROR:
            TRC_TRACE_ERR(trc_fun, "Value of the parameter(s) is invalid");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_PAR_ERROR);
            break;

        case MFP_MAC_VERIFICATION_ERROR:
            TRC_TRACE_ERR(trc_fun, "Verification of the PICC MAC failed");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_MAC_VERIFICATION_ERROR);
             break;

        case MFP_AUTHENTICATION_ERROR:
            TRC_TRACE_ERR(trc_fun, "The authentication failed");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_AUTHENTICATION_ERROR);
             break;

        case MFP_COMMUNICATION_ERROR:
            TRC_TRACE_ERR(trc_fun, "Communication error with PICC");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_PICC_COMMS_ERROR);
             break;

        case MFP_COMMUNICATION_TIMEOUT_ERROR:
            TRC_TRACE_ERR(trc_fun, "Communication timeout");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_COMMS_TIMEOUT);
             break;

        case MFP_INVALID_VALUE:
            TRC_TRACE_ERR(trc_fun, "The value block has an error");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_INVALID_VALUE);
             break;

        case MFP_VALUE_ADD_WARNING:
            TRC_TRACE_ERR(trc_fun, "The address byte of value block doesn't match the current block number");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_VALUE_ADD_WARNING);
             break;

        case MFP_INTERNAL_ERROR:
            TRC_TRACE_ERR(trc_fun, "The library has a processing error");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_PROCESSING_ERROR);
             break;

        case MFP_CRYPTO_ERROR:
            TRC_TRACE_ERR(trc_fun, "The library has a crypto processing error");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_CRYPTO_ERROR);
             break;

        case MFP_SAM_ERROR:
            TRC_TRACE_ERR(trc_fun, "SAM has an error");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_SAM_ERROR);
             break;

        case MFP_PC_TIME_ERROR:
            TRC_TRACE_ERR(trc_fun, "The Proximity Check time verification failed");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_PC_TIME_ERROR);
             break;

        case MFP_STATE_ERROR:
            TRC_TRACE_ERR(trc_fun, "The current state doesn't allow the command execution");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_STATE_ERROR);
             break;

        case MFP_RESPONSE_ERROR:
            TRC_TRACE_ERR(trc_fun, "The response has an error");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_RESPONSE_ERROR);
             break;

        case MFP_DLL_NOT_LOADED:
            TRC_TRACE_ERR(trc_fun, "The DLL is not loaded");
            UI_ErrMsgDisplay(UI_PROMPT_MSG_DLL_NOT_LOADED);
             break;

        case MFP_SC_ERROR:
        case MFP_SC_AUTHENTICATION_ERROR:
        case MFP_SC_COMMAND_OVERFLOW:
        case MFP_SC_INVALID_MAC:
        case MFP_SC_INVALID_BLOCK_NB:
        case MFP_SC_NOT_EXISTING_BLOCK_NB:
        case MFP_SC_BAD_CONDITIONS:
        case MFP_SC_LENGTH_ERROR:
        case MFP_SC_GENERAL_ERROR:
            TRC_TRACE_ERR(trc_fun, "PICC Error err=%d", err);
             break;

         default:
            TRC_TRACE_ERR(trc_fun, "An error occurred err=%d", err);
            UI_ErrMsgDisplay(ERR_UNDEFINED);
            break;
    }

    return 0;
}

/** Create new mifare plus context
 * \param[in] sam indicator if with SAM or not
 * \return 1 if OK; 0 on error
 */
static int _FUN_MfpCreateContext(int sam, int secLvl)
{
    int ret;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareCreateContext");
    if (sam == 0)
    {
        context = ClessMFP_NewContext();
        if (context == NULL)
        {
            TRC_TRACE_INFO(trc_fun, "ClessMFP_NewContext KO");
            return 0;
        }
        TRC_TRACE_INFO(trc_fun, "ClessMFP_NewContext OK");

        err = MFP_OK;
/*
        if (secLvl==SL3)
        {
            TRC_TRACE_INFO(trc_fun, "Proximity check with Proximity Check Key (PC key is 00 ... 00)");
            err = ClessMFP_SL3ProximityCheck(context, NULL);
        }
*/
    }
    else
    {
        context = ClessMFP_NewContextWithSAM(hdlSAM);
        if (context == NULL)
        {
            TRC_TRACE_INFO(trc_fun, "ClessMFP_NewContextWithSAM KO");
            return 0;
        }
        TRC_TRACE_INFO(trc_fun, "ClessMFP_NewContextWithSAM OK");

        TRC_TRACE_INFO(trc_fun, "Host-SAM Authentication with SAM Key 1 version 0 and Full protection mode");
        err = ClessMFP_SAMAuthenticate(context, (const unsigned char*)"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 1, 0, 2);
        ret = _FUN_MfpGetError(err);
        if (ret != 1)
        {
            TRC_TRACE_INFO(trc_fun, "ClessMFP_SAMAuthenticate KO");
            return 0;
        }
        TRC_TRACE_INFO(trc_fun, "ClessMFP_SAMAuthenticate OK");

/*
        if (secLvl==SL3)
        {
            TRC_TRACE_INFO(trc_fun, "Proximity check with Proximity Check Key (PC key is 00 ... 00)");
            err = ClessMFP_SL3ProximityCheckWithSAM(context, 2, 0, 0, NULL);
        }
*/
    }

    ret = _FUN_MfpGetError(err);
    return ret;
}

/** Authenticate mifare plus card
 * \param[in] sam indicator if with SAM or not
 * \param[in] secLvl Security Level
 * \return 1 if OK; 0 on error
 */
static int _FUN_MfpAuthenticate(int sam, int secLvl)
{
    int ret;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareAuthenticate");
    if (secLvl == SL3)
    {
        if (sam == 0)
        {
            TRC_TRACE_INFO(trc_fun, "Authenticate with AES key 0x4002 (Sector 1 Key A)");
            err = ClessMFP_SL3Authenticate(context, 0x4002, MFP_AUTH_F, (const unsigned char*)"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
            ret = _FUN_MfpGetError(err);
            if (ret != 1)
            {
                TRC_TRACE_INFO(trc_fun, "ClessMFP_SL3Authenticate KO");
            }
            else
            {
                TRC_TRACE_INFO(trc_fun, "ClessMFP_SL3Authenticate OK");
            }
        }
        else
        {
            TRC_TRACE_INFO(trc_fun, "Authenticate First SL3 using MFP AES key 0x4002 (Sector 1 Key A) and SAM Key 2 V0, no diversification");
            err = ClessMFP_SL3AuthenticateWithSAM(context, 0x4002, MFP_AUTH_F, 2, 0, 0, NULL);
            ret = _FUN_MfpGetError(err);
            if (ret != 1)
            {
                TRC_TRACE_INFO(trc_fun, "ClessMFP_SL3AuthenticateWithSAM KO");
            }
            else
            {
                TRC_TRACE_INFO(trc_fun, "ClessMFP_SL3AuthenticateWithSAM OK");
            }
        }
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "AES Authenticate using MFP AES key 0x4002 (Sector 1 Key A) and SAM Key 2 V0, no diversification");
        err = ClessMFP_SL2AuthenticateAESWithSAM(context, 0x4002, MFP_AUTH_N, 2, 0, 0, NULL);
        ret = _FUN_MfpGetError(err);
        if (ret != 1)
        {
          TRC_TRACE_INFO(trc_fun, "ClessMFP_SL2AuthenticateAESWithSAM KO");
          return 0;
        }
        TRC_TRACE_INFO(trc_fun, "ClessMFP_SL2AuthenticateAESWithSAM KOK");
    
        TRC_TRACE_INFO(trc_fun, "Mifare Classic Authenticate using Key A of sector 1 and SAM Key 4 V0, no diversification");
        err = ClessMFP_SL12AuthenticateClassicWithSAM(context, MFP_KEY_A, 1, 4, 0, NULL);
        ret = _FUN_MfpGetError(err);
        if (ret != 1)
        {
          TRC_TRACE_INFO(trc_fun, "ClessMFP_SL12AuthenticateClassicWithSAM KO");
          return 0;
        }
        TRC_TRACE_INFO(trc_fun, "ClessMFP_SL12AuthenticateClassicWithSAM KOK");
    }

    return ret;
}

/** Write data to one or multiple blocks
 * \param[in] secLvl Security Level
 * \param[in] cmd Read command code
 * \param[in] blk Block number of the first block to read
 * \param[in] blkSize Number of blocks to write
 * \param[in] buf Pointer to the buffer which will receive the data read
 * \return 1 if OK; 0 on error
 */
static int _FUN_MfpWrite(int secLvl, unsigned char cmd, unsigned short blk, unsigned char blkSize, void* buf)
{
    int ret;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_MfpWrite");

    if (secLvl==SL3)
    {
        err = ClessMFP_SL3Write(context, cmd, blk, blkSize, buf);
    }
    else
    {
        err = ClessMFP_SL2WriteMultiBlock(context, blk, blkSize, buf);
    }

    ret = _FUN_MfpGetError(err);
    if (ret != 1)
    {
        TRC_TRACE_INFO(trc_fun, "Cless MFP Write KO");
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Cless MFP Write OK");
    }

    return ret;
}

/** Write data or keys in plain
 * \param[in] blk Block number or key address where to write
 * \param[in] data 16 bytes of plain data to write
 * \return 1 if OK; 0 on error
 */
static int _FUN_MfpWritePerso(unsigned short blk, void* data)
{
    int ret;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_MfpWrite");

    err = ClessMFP_SL0WritePerso(context, blk, data);
    ret = _FUN_MfpGetError(err);

    return ret;
}

/** Finalize the personalization and switch the card to Security Level 1 for "L1 card"
 * or to Security Level 3 for "L3 card". Only available in Security Level 0.
 * \return 1 if OK; 0 on error
 */
static int _FUN_MfpCommitPerso(void)
{
    int ret;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_MfpWrite");

    err = ClessMFP_SL0CommitPerso(context);
    ret = _FUN_MfpGetError(err);

    return ret;
}

/** Read data from one or multiple blocks
 * \param[in] secLvl Security Level
 * \param[in] cmd Read command code
 * \param[in] blk Block number of the first block to read
 * \param[in] blkSize Number of blocks to read
 * \param[in] buf Pointer to the buffer which will receive the data read
 * \return 1 if OK; 0 on error
 */
static int _FUN_MfpRead(int secLvl, unsigned char cmd, unsigned short blk, unsigned char blkSize, void* buf)
{
    int ret;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_MfpSL3Read");

    if (secLvl==SL3)
    {
        err = ClessMFP_SL3Read(context, cmd, blk, blkSize, buf);
    }
    else
    {
        err = ClessMFP_SL2ReadMultiBlock(context, blk, blkSize, buf);
    }

    ret = _FUN_MfpGetError(err);
    if (ret != 1)
    {
        TRC_TRACE_INFO(trc_fun, "ClessMFP_SL3Read KO");
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "ClessMFP_SL3Read OK");
    }

    return ret;
}

/** Make a value operation on a block.
 * \param[in] secLvl Security Level
 * \param[in] cmd Read command code
 * \param[in] blk Block number of the first block to read
 * \param[in] addBlk Additional block number used by the commands. Increment-Transfer or Decrement-Transfer. For the other commands, put 0.
 * \param[in] buf Pointer to the buffer which will receive the data read
 * \return 1 if OK; 0 on error
 */
static int _FUN_MfpOperation(int secLvl, unsigned char cmd, unsigned short blk, unsigned char addBlk, void* buf)
{
    int ret;
    int err;

    TRC_TRACE_INFO(trc_fun, "_FUN_MfpOperation");

    if (secLvl == SL3)
    {
        err = ClessMFP_SL3ValueOperation(context, cmd, blk, addBlk, buf);
        ret = _FUN_MfpGetError(err);
        if (ret != 1)
        {
            TRC_TRACE_INFO(trc_fun, "ClessMFP_SL3ValueOperation KO");
        }
        else
        {
            TRC_TRACE_INFO(trc_fun, "ClessMFP_SL3ValueOperation OK");
        }
    }
    else
    {
        err = ClessMFP_SL12ValueOperation(context, cmd, blk, buf);
        ret = _FUN_MfpGetError(err);
        if (ret != 1)
        {
            TRC_TRACE_INFO(trc_fun, "ClessMFP_SL12ValueOperation KO");
        }
        else
        {
            TRC_TRACE_INFO(trc_fun, "ClessMFP_SL12ValueOperation OK");
        }
    }

    return ret;
}

/** Perform the following processes
 * - free mifare plus context 
 * - release SAM handle
 * - close the drivers opened
 * \return 1 if OK; 0 on error
 */
static int _FUN_MifareFree(void)
{
    int ret;

    TRC_TRACE_INFO(trc_fun, "_FUN_MifareFree");
    if(hdlSAM)
    {
        fclose(hdlSAM);
    }

    if (context !=NULL)
    {
        ClessMFP_FreeContext(context);
    }

    ret = ClessMifare_IsDriverOpened();
    if(ret)
    {
        ClessMifare_OpenDriver();
    }

    ret = ClessEmv_IsDriverOpened();
    if(ret)
    {
        ClessEmv_CloseDriver();
    }

    return 1;
}

int FUN_MfpPersonalizeSL0toSL1(void)
{
    int ret;
    int blk;
    unsigned char buf[16];

    trc_fun = TRC_HandleGet();
    TRC_TRACE_INFO(trc_fun, "FUN_MfpPersonalize");
    _FUN_IsoStart();

    ret = _FUN_IsoDetect(0, 30);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_IsoActivate();
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_MfpCreateContext(0, SL0); //SL0 without SAM
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    // initialize AES Sector keys to 00 .. 00
    TRC_TRACE_INFO(trc_fun, "Initialization of AES Sector keys to 00 ... 00 from 0x4000 to 0x403F");
    memclr(buf, sizeof(buf));// set buffer to zero
    for (blk=0x4000; blk<= 0x404F; blk++)
    {
        TRC_TRACE_INFO(trc_fun, "WritePerso AES Sector Key %04X to 00 .. 00", blk);
        ret = _FUN_MfpWritePerso(blk, buf);
        if (ret!=1)
        {
            if (blk<0x4040)
            {
                TRC_TRACE_INFO(trc_fun, "ClessMFP_WritePerso Key(x%0x4) error x%04X ", blk, ret);
            }
            else
            {
                //Error on keys > 0x403F -> normal for MFP 2K cards
                TRC_TRACE_INFO(trc_fun, "ClessMFP_WritePerso Key(x%0x4) error x%04X, can be OK if MFP 2K ", blk, ret);
                break;
            }
            _FUN_MifareFree();
            return 0;
        }
    }

    memclr(buf, sizeof(buf));
    //Write data or keys in plain. Only available in Security Level 0 (personalization)
    TRC_TRACE_INFO(trc_fun, "WritePerso Card Master Key to 00 .. 00");
    ret = _FUN_MfpWritePerso(0x9000, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "WritePerso Card Configuration Key to 00 .. 00");
    ret = _FUN_MfpWritePerso(0x9001, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "WritePerso SL2 Switch key to 00 .. 00");
    ret = _FUN_MfpWritePerso(0x9002, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "WritePerso SL3 Switch Key to 00 .. 00");
    ret = _FUN_MfpWritePerso(0x9003, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "WritePerso SL1 Card Auth Key to 00 .. 00");
    ret = _FUN_MfpWritePerso(0x9004, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "WritePerso Select VC Key to 00 .. 00");
    ret = _FUN_MfpWritePerso(0xA000, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "WritePerso Proximity Check Key to 00 .. 00");
    ret = _FUN_MfpWritePerso(0xA001, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "WritePerso VC Polling Enc Key to 00 .. 00");
    ret = _FUN_MfpWritePerso(0xA080, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "WritePerso VC Polling Mac Key to 00 .. 00");
    ret = _FUN_MfpWritePerso(0xA081, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_MfpCommitPerso();
    if (ret!=1)
    {
        ret = 0;
    }

    _FUN_MifareFree();
    return ret;
}

int FUN_MfpPersonalizeSL1toSL2(void)
{
    int ret;

    trc_fun = TRC_HandleGet();
    TRC_TRACE_INFO(trc_fun, "FUN_MfpPersonalize");
    _FUN_IsoStart();

    ret = _FUN_IsoDetect(0, 30);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_IsoActivate();
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_MfpCreateContext(0, SL1); //SL1 without SAM
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "ClessMFP_SL1AuthenticateAES");
    ret = ClessMFP_SL1AuthenticateAES(context, 0x9002, MFP_AUTH_F,  (const unsigned char*)"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
    ret = _FUN_MfpGetError(ret);
    if (ret!=1)
    {
        TRC_TRACE_INFO(trc_fun, "ClessMFP_SL1AuthenticateAES KO");
        ret = 0;
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "ClessMFP_SL1AuthenticateAES OK");
    }

    _FUN_MifareFree();
    return ret;
}

int FUN_MfpPersonalizeSL2toSL3(void)
{
    int ret;

    trc_fun = TRC_HandleGet();
    TRC_TRACE_INFO(trc_fun, "FUN_MfpPersonalize");
    _FUN_IsoStart();

    ret = _FUN_IsoDetect(0, 30);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_IsoActivate();
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_MfpCreateContext(0, SL2); //SL0 without SAM
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "ClessMFP_SL2AuthenticateAES");
    ret = ClessMFP_SL2AuthenticateAES(context, 0x9003, MFP_AUTH_F,  (const unsigned char*)"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
    ret = _FUN_MfpGetError(ret);
    if (ret!=1)
    {
        TRC_TRACE_INFO(trc_fun, "ClessMFP_SL2AuthenticateAES KO");
        ret = 0;
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "ClessMFP_SL2AuthenticateAES OK");
    }

    _FUN_MifareFree();
    return ret;
}

int FUN_MifareSL3(void)
{
    int ret;
    unsigned char buf[64];
    int val;

    trc_fun = TRC_HandleGet();
    TRC_TRACE_INFO(trc_fun, "MIFARE Plus SL3 Sample");
    _FUN_IsoStart();

    ret = _FUN_IsoDetect(0, 30);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_IsoActivate();
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_MfpCreateContext(0, SL3); //SL3 without SAM
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_MfpAuthenticate(0, SL3);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    //Write 2 blocks (4, 5)
    ret = _FUN_MfpWrite(SL3, MFP_WRITE_MAC, 4, 2, "- Hello Block 4 from MFPSample -");
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    //Read blocks 4, 5
    ret = _FUN_MfpRead(SL3, MFP_READ_MAC, 4, 2, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    if(memcmp(buf,  "- Hello Block 4 from MFPSample -", 2*16)!=0)
    {
        TRC_TRACE_INFO(trc_fun, "Read Data KO");
        _FUN_MifareFree();
        return 0;
    }
    
    //Write value 2012 in block 6
    val = 2012;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
    ret = _FUN_MfpOperation(SL3, MFP_WRITE, 6, 0, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }
    
    //Increment(+3) & Transfer Value (block 6)
    val = 3;//Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
     ret = _FUN_MfpOperation(SL3, MFP_INC_TRANSFER_MAC, 6, 6, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    //Read value in block 6
    val = 0;//Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
     ret = _FUN_MfpOperation(SL3, MFP_READ_MAC, 6, 0, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    if(val != 2012+3)
    {
        TRC_TRACE_INFO(trc_fun, "Read Value KO");
        _FUN_MifareFree();
        return 0;
    }

    _FUN_MifareFree();
    return ret;
}

int FUN_MifareSL3WithSAM(void)
{
    int ret;
    unsigned char buf[64];
    int val;

    trc_fun = TRC_HandleGet();
    TRC_TRACE_INFO(trc_fun, "MIFARE Plus SL3 sample with SAM");

    ret = _FUN_MifareDetectSAM();
    if (ret!=1)
    {
        return 0;
    }
    _FUN_IsoStart();

    ret = _FUN_IsoDetect(0, 30);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_IsoActivate();
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_MfpCreateContext(1, SL3); //SL3 with SAM
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_MfpAuthenticate(1, SL3);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    //Write 2 blocks (4, 5)
    ret = _FUN_MfpWrite(SL3, MFP_WRITE_MAC, 4, 2, "- Hello Block 4 from MFPSample -");
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    //  Read blocks 4, 5
    ret = _FUN_MfpRead(SL3, MFP_READ_MAC, 4, 2, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    if(memcmp(buf,  "- Hello Block 4 from MFPSample -", 2*16)!=0)
    {
        TRC_TRACE_INFO(trc_fun, "Read Data KO");
        _FUN_MifareFree();
        return 0;
    }

    //  Write value 2012 in block 6
    val = 2012;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
    ret = _FUN_MfpOperation(SL3, MFP_WRITE, 6, 0, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    //  Increment(+3) & Transfer Value (block 6)
    val = 3;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
    ret = _FUN_MfpOperation(SL3, MFP_INC_TRANSFER_MAC, 6, 6, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    //  Read value in block 6
    val = 0;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
    ret = _FUN_MfpOperation(SL3, MFP_READ_MAC, 6, 0, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    if(val != 2012+3)
    {
        TRC_TRACE_INFO(trc_fun, "Read Value KO");
        _FUN_MifareFree();
        return 0;
    }

    //  Decrement (-4) block 6
    val = 4;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
    ret = _FUN_MfpOperation(SL3, MFP_DECREMENT, 6, 0, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    //  Tranfert to block 6
    ret = _FUN_MfpOperation(SL3, MFP_TRANSFER_MAC, 6, 0, NULL);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    //  Read value in block 6
    val = 0;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
    ret = _FUN_MfpOperation(SL3, MFP_READ_MAC, 6, 0, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    if(val != 2015-4)
    {
        TRC_TRACE_INFO(trc_fun, "Read Value KO");
        _FUN_MifareFree();
        return 0;
    }

    _FUN_MifareFree();
    return ret;
}

int FUN_MifareSL2WithSAM(void)
{
   int ret;
   unsigned char buf[64];
   int val;

    trc_fun = TRC_HandleGet();
    TRC_TRACE_INFO(trc_fun, "MIFARE Plus SL2 sample with SAM");

    ret = _FUN_MifareDetectSAM();
    if (ret!=1)
    {
        return 0;
    }

    _FUN_MifareStart();

    ret = _FUN_MifareDetect(30);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_MifareActivate();
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_MfpCreateContext(1, SL2); //SL2 with SAM
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

    ret = _FUN_MfpAuthenticate(1, SL2);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

   //Write 2 blocks (4, 5)
   ret = _FUN_MfpWrite(SL2, NULL, 4, 2, "-Hello Blk 4 from SL2 MFPSample-");
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

   //Read blocks 4, 5
   ret = _FUN_MfpRead(SL2, NULL, 4, 2, buf);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

   if(memcmp(buf,  "-Hello Blk 4 from SL2 MFPSample-", 2*16)!=0)
    {
        TRC_TRACE_INFO(trc_fun, "Read Data KO");
        _FUN_MifareFree();
        return 0;
    }

   //Write value 7964 in block 6
   val = 7964;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   ret = _FUN_MfpOperation(SL2, MFP_SL12_WRITE, 6, NULL, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }


   //  Decrement (-4) block 6
   val = 4;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   ret = _FUN_MfpOperation(SL2, MFP_SL12_DECREMENT, 6, NULL, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

   //  Transfer to block 6
   ret = _FUN_MfpOperation(SL2, MFP_SL12_TRANSFER, 6, NULL, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

   //  Read value in block 6
   val = 0;  //Rem Thunder is LSB first like Mifare -> no conversion MSB LSB
   ret = _FUN_MfpOperation(SL2, MFP_SL12_READ, 6, NULL, &val);
    if (ret!=1)
    {
        _FUN_MifareFree();
        return 0;
    }

   if(val != 7964-4)
   {
        TRC_TRACE_INFO(trc_fun, "Read Value KO");
        _FUN_MifareFree();
        return 0;
   }

    _FUN_MifareFree();
    return ret;
}

