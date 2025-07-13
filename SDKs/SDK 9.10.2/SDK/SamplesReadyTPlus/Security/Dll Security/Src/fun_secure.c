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
 Module  : FUN - Demo Features Unit
 
 @file      fun_security.c
 @brief     This file contains the definition of processes that is implemented
 by this sample.
 
 @date      13/03/2013

------------------------------------------------------------------------------
*/

#include "sdk30.h"
#include "SEC_interface.h"
#include "GL_GraphicLib.h"
#include "schVar_def.h"
#include "tlvVar_def.h"

#include "err_process.h"
#include "par.h"
#include "trace.h"
#include "flow.h"
#include "par_management.h"
#include "fun_demofeatures.h"
#include "utilities.h"

#define C_NB_PARTS 3
#define ECHO_PIN '*'

typedef struct stPin
{
    unsigned char dly;
    int state;
} ST_PIN;

/******************************************************/
/*                VAR PARAMETERS TO SET               */
/******************************************************/
/* 
FOR YOUR TESTS : INITIALIZE WITH YOUR CARD NUMBER
CARD_NUMBER_SIGN  4bytes to define   
VAR_NUMBER_SIGN   4bytes to define       
*/
#define VAR_NUMBER_SIGN 0x010D
#define CARD_NUMBER_SIGN 0x0003C00E
#define ID_SCR_XXX_BANK 0x0E012130 /* SECRET AREA ID TO USE */
#define ID_BANK_XXX BK_SAGEM /* BANK ID TO USE */
#define ROOT_KEY_NO_XXX 1008 /* ROOT KEY NUMBER */
#define PIN_MASTER_KEY_NO_XXX 72 /* PIN MASTER KEY NUMBER */
#define MAC_MASTER_KEY_NO_XXX 88 /* MAC MASTER KEY NUMBER */
#define PIN_KEY_NO_XXX 8 /* PIN KEY NUMBER */
#define MAC_KEY_NO_XXX 24 /* MAC KEY NUMBER */

static int _FUN_GetConfig(void);
static void _FUN_SetRootKeyId(T_SEC_DATAKEY_ID * ptstRootKey);
static int _FUN_PinCiphering(const unsigned char *pucAcc, unsigned char *pucBlk);
static unsigned long _FUN_RefreshScheme(T_GL_HSCHEME_INTERFACE interfac, T_GL_HWIDGET label);
static unsigned long _FUN_OpenScheme (T_GL_HSCHEME_INTERFACE interfac);
static void _FUN_CloseScheme (T_GL_HSCHEME_INTERFACE interfac);

int outputLen;
unsigned char outputData[8];
static TRC_Trace_t trc_fun;

static int _FUN_GetConfig(void)
{
    int ret;
    int parts;
    int i;
    T_SEC_CONFIG tabConfParts[C_NB_PARTS];
    char buf[100];

    trc_fun = TRC_HandleGet();

    ret = SEC_GetConfig(&parts, tabConfParts);
    sprintf (buf, "Number of Parts:%d", parts);
    TRC_TRACE_INFO(trc_fun, buf);
    for (i=0; i < parts; i++)
    {
         switch ( (int) tabConfParts[i].SecureType )
         {
             case C_SEC_PINCODE :
                 TRC_TRACE_INFO(trc_fun, "Secure Type: PIN ENTRY");
                 break;
             case C_SEC_CARD :
                 TRC_TRACE_INFO(trc_fun, "Secure Type: CARD READER");
                 break;
             case C_SEC_CIPHERING :
                 TRC_TRACE_INFO(trc_fun, "Secure Type: CIPHERING");
                 break;
             default:
                 sprintf (buf, "SecurePart:%d ", tabConfParts[i].SecureType);
                 TRC_TRACE_INFO(trc_fun, buf);
                 break;
         }

         if ( memcmp (tabConfParts [i].ptszBoosterPeripheral, IAPP_USB_NAME, strlen(IAPP_USB_NAME)) == 0)
         {
             TRC_TRACE_INFO(trc_fun, "Peripheral: PINPAD");
         }
         else
         {
             TRC_TRACE_INFO(trc_fun, "Peripheral: TERMINAL");
         }
    }

    return (ret);
}

int FUN_SetConfig(void)
{
    int ret;
    int i;
    T_SEC_CONFIG tabConfParts[C_NB_PARTS];

    trc_fun = TRC_HandleGet();

    FLOW_ConfigParamProcess();
    for (i=0; i < C_NB_PARTS; i++)
    {
        PAR_SecurePartGet(i, &tabConfParts[i].SecureType);
        PAR_BoosterGet(i,&tabConfParts[i].cBoosterType);
        PAR_PeriphBoosterGet(i, &tabConfParts[i].ptszBoosterPeripheral);
        tabConfParts[i].cbGestResid=TRUE;
    }

    ret = SEC_SetConfig(C_NB_PARTS, tabConfParts);
    if (ret == OK)
    {
        TRC_TRACE_INFO(trc_fun, "Configuration SET OK");
        ret = _FUN_GetConfig();
        if (ret==OK)
        {
            TRC_TRACE_INFO(trc_fun, "Configuration GET OK");
        }
        else
        {
            TRC_TRACE_INFO(trc_fun, "Configuration GET KO");
        }
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Configuration SET KO");
    }
    return (ret);
}

int FUN_ListSecretArea(int idx)
{
    int ret;
    int i;
    T_SEC_PARTTYPE SecPart;
    int numId, tabList[10];
    char buf[80], tmp[10];

    trc_fun = TRC_HandleGet();

    switch (idx)
    {
        case 2:
            TRC_TRACE_INFO(trc_fun, "List Data Ciphering Secret Key");
            break;

        default:
            TRC_TRACE_INFO(trc_fun, "List PIN Entry Secret Key");
            break;
    }

    ret = PAR_SecurePartGet(idx, &SecPart);
    if  (ret == PAR_OK)
    {
        ret = SEC_listSecureId(SecPart, &numId, tabList);
        if (ret == OK)
        {
            strcpy (buf, "Id:");
            for (i=0; i< numId; i++)
            {
                sprintf (tmp, " %x", tabList[i]);
                strcat (buf, tmp);
            }
            TRC_TRACE_INFO(trc_fun, buf);
        }
    }
    return (ret);
}

int FUN_CreateSecretArea(int idx)
{
    T_SEC_PARTTYPE SecPart;
    int ret;

    trc_fun = TRC_HandleGet();
    TRC_TRACE_INFO(trc_fun, "Secret Area Creation...");

    ret = PAR_SecurePartGet(idx, &SecPart);
    if  (ret == PAR_OK)
    {
        ret = SEC_CreateSecretArea(SecPart, (SEG_ID) ID_SCR_XXX_BANK, CARD_NUMBER_SIGN, VAR_NUMBER_SIGN);
        if (ret == OK)
        {
            TRC_TRACE_INFO(trc_fun, "Secret Area Creation... OK");
        }
        else
        {
            TRC_TRACE_INFO(trc_fun, "Secret Area Creation... KO");
        }
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
    }

    return (ret);
}

int FUN_FreeSecretArea(int idx)
{
    int ret;
    T_SEC_PARTTYPE SecPart;
    T_SEC_DATAKEY_ID keyId;

    trc_fun = TRC_HandleGet();

    switch (idx)
    {
        case 0: //C_SEC_PINCODE
            ret = PAR_SecurePartGet(idx, &SecPart);
            TRC_TRACE_INFO(trc_fun, "Free PIN Master Key");
            keyId.iSecretArea = ID_SCR_XXX_BANK;
            keyId.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
            keyId.usNumber = PIN_MASTER_KEY_NO_XXX;
            keyId.uiBankId = ID_BANK_XXX;
            ret = SEC_FreeSecret(SecPart, &keyId);
            if (ret == OK)
            {
                TRC_TRACE_INFO(trc_fun, "Free PIN Master Key...OK");
                TRC_TRACE_INFO(trc_fun, "Free PIN Key");
                keyId.iSecretArea = ID_SCR_XXX_BANK;
                keyId.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
                keyId.usNumber = PIN_KEY_NO_XXX;
                keyId.uiBankId = ID_BANK_XXX;
                ret = SEC_FreeSecret(SecPart, &keyId);
                if (ret == OK)
                {
                    TRC_TRACE_INFO(trc_fun, "Free PIN Key...OK");
                }
                else
                {
                    TRC_TRACE_INFO(trc_fun, "Free PIN Key...KO");
                }
            }
            else
            {
                TRC_TRACE_INFO(trc_fun, "Free PIN Master Key...KO");
            }
            break;

        case 2: //C_SEC_CIPHERING
            ret = PAR_SecurePartGet(idx, &SecPart);
            TRC_TRACE_INFO(trc_fun, "Free MAC Master Key");
            keyId.iSecretArea = ID_SCR_XXX_BANK;
            keyId.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
            keyId.usNumber = MAC_MASTER_KEY_NO_XXX;
            keyId.uiBankId = ID_BANK_XXX;
            ret = SEC_FreeSecret(SecPart, &keyId);
            if (ret == OK)
            {
                TRC_TRACE_INFO(trc_fun, "Free MAC Master Key...OK");
                TRC_TRACE_INFO(trc_fun, "Free MAC Key");
                keyId.iSecretArea = ID_SCR_XXX_BANK;
                keyId.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
                keyId.usNumber = MAC_KEY_NO_XXX;
                keyId.uiBankId = ID_BANK_XXX;
                ret = SEC_FreeSecret(SecPart, &keyId);
                if (ret == OK)
                {
                    TRC_TRACE_INFO(trc_fun, "Free MAC Key...OK");
                }
                else
                {
                    TRC_TRACE_INFO(trc_fun, "Free MAC Key...KO");
                }
            }
            else
            {
                TRC_TRACE_INFO(trc_fun, "Free MAC Master Key...KO");
            }
            break;

        default: //free whole area
            TRC_TRACE_INFO(trc_fun, "Free All Secret Area");
            ret = PAR_SecurePartGet(0, &SecPart);
            keyId.iSecretArea = ID_SCR_XXX_BANK;
            keyId.cAlgoType = 0;
            keyId.usNumber = 0;
            keyId.uiBankId = 0;
            ret = SEC_FreeSecret(SecPart, &keyId);
            if (ret == OK)
            {
                TRC_TRACE_INFO(trc_fun, "Free All Secret Area...OK");
            }
            else
            {
                TRC_TRACE_INFO(trc_fun, "Free All Secret Area...KO");
            }
            break;
    }

    return (ret);
}

static void _FUN_SetRootKeyId(T_SEC_DATAKEY_ID * ptstRootKey)
{
    ptstRootKey->iSecretArea = ID_SCR_XXX_BANK;
    ptstRootKey->cAlgoType   = TLV_TYPE_KTDES; /* This ROOT key is a TDES Key */
    ptstRootKey->usNumber    = ROOT_KEY_NO_XXX;
    ptstRootKey->uiBankId    = ID_BANK_XXX;
}

int FUN_LoadRootKey	(int idx)
{
    int ret, iUsage;
    T_SEC_PARTTYPE SecPart;
    T_SEC_DATAKEY_ID key;
    unsigned char TheRootKey[TDES_KEY_SIZE+1];

    trc_fun = TRC_HandleGet();

    ret = OK;
    ret = PAR_SecurePartGet(0, &SecPart);
    if  (ret == PAR_OK)
    {
        TRC_TRACE_INFO(trc_fun, "Loading Root Key...");
        _FUN_SetRootKeyId(&key);
        iUsage = CIPHERING_KEY; /* Key to cipher PIN keys and MAC keys */

        ret = PAR_Root_KeyGet(TheRootKey);
        if (ret!=PAR_OK)
        {
            TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
            return ERR_PAR_FILE_NOT_FOUND;
        }
        SEC_FreeSecret(SecPart, &key);
        ret = SEC_LoadKey(SecPart, NULL, &key, (unsigned char*) &TheRootKey, iUsage);
        if (ret != OK)
        {
            TRC_TRACE_INFO(trc_fun, "Loading Root Key...KO");
            TRC_TRACE_INFO(trc_fun, "Use SKMT/SKMT2 tool to load the Root Key");
        }
        else
        {
            TRC_TRACE_INFO(trc_fun, "Loading Root Key...OK");
        }
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "PAR not initialized");
    }
    return (ret);
}

int FUN_LoadPinKey(void)
{
    T_SEC_PARTTYPE SecPart;
    int ret, iUsage;
    T_SEC_DATAKEY_ID stMasterKey, key, stRootKey;
    unsigned char ThePinKey[DES_KEY_SIZE];
    unsigned char ThePinMasterKey[DES_KEY_SIZE];

    trc_fun = TRC_HandleGet();

    SecPart = C_SEC_PINCODE;
    ret = SEC_isSecretArea(SecPart, (SEG_ID) ID_SCR_XXX_BANK);
    if ( ret == OK )
    {
        /* Ciphering Key is the Root Key */
        _FUN_SetRootKeyId(&stRootKey);
        
        TRC_TRACE_INFO(trc_fun, "Loading PIN Master Key...");
        stMasterKey.iSecretArea = ID_SCR_XXX_BANK;
        stMasterKey.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
        stMasterKey.usNumber = PIN_MASTER_KEY_NO_XXX;
        stMasterKey.uiBankId = ID_BANK_XXX;
        iUsage = CIPHERING_KEY; /* Key to cipher PIN keys */

        ret = PAR_PinMaster_KeyGet(ThePinMasterKey);
        if (ret!=PAR_OK)
        {
            TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
            return ERR_PAR_FILE_NOT_FOUND;
        }
        ret = SEC_LoadKey(SecPart, &stRootKey, &stMasterKey, (unsigned char*) &ThePinMasterKey, iUsage);
        if (ret == OK)
        {
            /* PIN Key to load */
            TRC_TRACE_INFO(trc_fun, "Loading PIN Key...");
            key.iSecretArea = ID_SCR_XXX_BANK;
            key.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
            key.usNumber = PIN_KEY_NO_XXX;
            key.uiBankId = ID_BANK_XXX;
            iUsage = CIPHERING_PIN; /* Key to cipher PIN */

            ret = PAR_Pin_KeyGet(ThePinKey);
             if (ret!=PAR_OK)
            {
                TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
                return ERR_PAR_FILE_NOT_FOUND;
            }
            ret = SEC_LoadKey (SecPart, &stMasterKey, &key, (unsigned char*) &ThePinKey, iUsage);
            if (ret == OK)
            {
                        TRC_TRACE_INFO(trc_fun, "Loading PIN Key...OK");
            }
            else
            {
                        TRC_TRACE_INFO(trc_fun, "Loading PIN Key...KO");
            }
        }
        else
        {
                    TRC_TRACE_INFO(trc_fun, "Loading PIN Master Key...KO");
        }
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Use SKMT/SKMT2 tool to load the Root Key");
    }

    return (ret);
}

int FUN_LoadMacKey(void)
{
    T_SEC_PARTTYPE SecPart;
    int ret, iUsage;
    T_SEC_DATAKEY_ID stMasterKey, key, stRootKey;
    unsigned char TheMacKey[DES_KEY_SIZE];
    unsigned char TheMacMasterKey[DES_KEY_SIZE];

    trc_fun = TRC_HandleGet();

    SecPart = C_SEC_CIPHERING;
    ret = SEC_isSecretArea(SecPart, (SEG_ID) ID_SCR_XXX_BANK);
    if  (ret == OK)
    {
        /* Ciphering Key is the Root Key */
        _FUN_SetRootKeyId (&stRootKey);
        
        TRC_TRACE_INFO(trc_fun, "Loading MAC Master Key...");
        stMasterKey.iSecretArea = ID_SCR_XXX_BANK;
        stMasterKey.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
        stMasterKey.usNumber = MAC_MASTER_KEY_NO_XXX;
        stMasterKey.uiBankId = ID_BANK_XXX;
        iUsage = CIPHERING_KEY; /* Key to cipher MAC keys */

        ret = PAR_MacMaster_KeyGet(TheMacMasterKey);
        if (ret!=PAR_OK)
        {
            TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
            return ERR_PAR_FILE_NOT_FOUND;
        }
        ret = SEC_LoadKey(SecPart, &stRootKey, &stMasterKey, (unsigned char*) &TheMacMasterKey, iUsage);
        if (ret == OK)
        {
            TRC_TRACE_INFO(trc_fun, "Loading MAC Key...");
            key.iSecretArea = ID_SCR_XXX_BANK;
            key.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
            key.usNumber = MAC_KEY_NO_XXX;
            key.uiBankId = ID_BANK_XXX;
            iUsage = CIPHERING_DATA; /* Key to cipher data CBC/ECB */

            ret = PAR_Mac_KeyGet(TheMacKey);
            if (ret!=PAR_OK)
            {
                TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
                return ERR_PAR_FILE_NOT_FOUND;
            }
            ret = SEC_LoadKey (SecPart, &stMasterKey, &key, (unsigned char*) &TheMacKey, iUsage);
            if (ret == OK)
            {
                        TRC_TRACE_INFO(trc_fun, "Loading MAC Key...OK");
            }
            else
            {
                        TRC_TRACE_INFO(trc_fun, "Loading MAC Key...KO");
            }
        }
        else
        {
                    TRC_TRACE_INFO(trc_fun, "Loading MAC Master Key...KO");
        }
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Use SKMT/SKMT2 tool to load the Root Key");
    }
    
    return (ret);
}

static int _FUN_PinCiphering(const unsigned char *pucAcc, unsigned char *pucBlk)
{
    int ret;
    doubleword uiLengthOut;
    T_SEC_DATAKEY_ID xKey;

    // ISO9564 Pin ciphering
    xKey.iSecretArea = ID_SCR_XXX_BANK;                   // Secret area identification
    xKey.cAlgoType = TLV_TYPE_KDES;               // PIN key is a DES Key 
    xKey.usNumber = PIN_KEY_NO_XXX;           // PIN key location inside the secret area 
    xKey.uiBankId = ID_BANK_XXX;              // Bank id related to this PIN key 

    // C_SEC_PINCODE secure part recommended to cipher/decipher Iso9564Pin entry (PCI/PED)
    ret = SEC_Iso9564(C_SEC_PINCODE, &xKey, ISO9564_F0_DES, (unsigned char*)pucAcc, pucBlk, &uiLengthOut);

    return ret;
}

static unsigned long _FUN_RefreshScheme(T_GL_HSCHEME_INTERFACE interfac, T_GL_HWIDGET label)
{
    int ret=GL_RESULT_SUCCESS;
    unsigned int event;
    ST_PIN* pin;
    static char enteredPin[16+1];
    int cont=TRUE;
    unsigned char key;	
    
    pin = (ST_PIN*)interfac->privateData;                                             // Retrieve pointer on my private data
    
    //Pin entry code management
    if (pin->state == -1)                                                            // First step: Show screen Pin entry
    {
        memset(enteredPin, 0, sizeof(enteredPin));
        pin->state++;
        return ret;
    }
    //Next steps: Enter Pin
    event=0;                                                                        // Event time-out
    ret = SEC_PinEntry(&event, &key, &cont);
    
    if (ret == OK)
    {
        if (key == ECHO_PIN)
        {
            // Enter pin in progress
            if (pin->state < MAX_PIN_CODE_SIZE)
            {
                enteredPin[pin->state] = key;
                enteredPin[pin->state+1] = 0;
                GL_Widget_SetText(label, (char*)enteredPin);                                // Display pin code entry
                pin->state++;
            }
            event=0;                                                                // Event time-out
        }
        else
        {
            // Pin confirmation
            switch (key)
            {
                case 0x00:
                    ret=GL_RESULT_INACTIVITY; //Response to stop pin entry by receiving an event
                    break;
                case 0x01:
                    ret=GL_RESULT_INACTIVITY;
                    break;
                case T_VAL:
                    ret=GL_KEY_VALID; //Valid key from Pinpad or Terminal when enter pin => cont=FALSE if >= Min pin entry
                    break;
                case T_ANN:
                    ret=GL_KEY_CANCEL;
                    break;  //Cancel key from Pinpad or Terminal when enter pin => cont=FALSE
                case T_CORR: //Correction from Pinpad or Terminal when enter pin => cont=TRUE
                    if (pin->state != 0)
                    {
                        pin->state--;
                        enteredPin[pin->state] = ' ';
                        enteredPin[pin->state+1] = 0;
                        GL_Widget_SetText(label, (char*)enteredPin);// Pin entry code correction
                    }
                    event=0; // Event time-out
                    break;
                default:
                    break;
            }
        }
    }
    else if (ret == ERR_TIMEOUT) // Pin entry on pinpad and canceled by terminal
    {
        ret = GL_RESULT_INACTIVITY;
    }
    else // Pin entry on pinpad already in progress
    {
        ret=GL_RESULT_INACTIVITY;
    }

    return ret;
}

static unsigned long _FUN_OpenScheme (T_GL_HSCHEME_INTERFACE interfac)
{
    int ret;
    ST_PIN* pin;
    T_SEC_ENTRYCONF cfg;

    pin = (ST_PIN*)interfac->privateData;                                              // Retrieve pointer on my private data
    
    // Pin entry code initialization
    cfg.ucEchoChar = ECHO_PIN;                                                      // '*' echo character
    cfg.ucMinDigits = 4;                                                            // Min pin entry 4 digits
    cfg.ucMaxDigits = 4;                                                            // Max pin entry 4 digits
    if (pin->dly < 60)
    {
        cfg.iFirstCharTimeOut = pin->dly*1000;                              // Wait for first digit < 60s
    }
    else
    {
        cfg.iFirstCharTimeOut = 60*1000;                                            // Wait for first digit 60s (Max supported)
    }
        cfg.iInterCharTimeOut = 30*1000;                                                // Wait for next digits 10s
    
    // Secure part relative to the Pin entry function
    ret = SEC_PinEntryInit(&cfg, C_SEC_PINCODE); // C_SEC_PINCODE secure part recommended to pin entry (PCI/PED)
    
    (void)(interfac);
    return GL_RESULT_SUCCESS;
}

static void _FUN_CloseScheme (T_GL_HSCHEME_INTERFACE interfac)
{
    (void)(interfac);
}

int FUN_PinEntry(void)
{
    int ret;
    unsigned long res;
    T_GL_SCHEME_INTERFACE sch;
    T_GL_HGRAPHIC_LIB goalHdl;
    ST_PIN pin;

    trc_fun = TRC_HandleGet();
    TRC_TRACE_INFO(trc_fun, "Pin Entry");

    // Check Pinpad
    ret = DLLExist("SECURITY"); 
    if (ret!=TRUE)
    {
        TRC_TRACE_INFO(trc_fun, "No Security Dll loaded");
    }

    // Enter PIN
    // Initializes interface scheme management
    sch.open     = _FUN_OpenScheme;
    sch.close    = _FUN_CloseScheme;
    sch.refresh  = _FUN_RefreshScheme;
    
    // Pointer on my private data
    pin.dly = 60;
    pin.state = -1;
    sch.privateData = &pin;

    goalHdl = guiStart();

    // Pin entry
    res = GL_Dialog_Scheme(goalHdl, "PIN ENTRY", "1000 EUR", "Enter your code\nfrom prying eyes", &sch);
    if (res==GL_KEY_CANCEL)
    {
        TRC_TRACE_INFO(trc_fun, "Pin Entry Cancelled");
        UI_PromptMsgDisplay(UI_PROMPT_MSG_PIN_ENTRY_CANCELLED);
        return ERR_PIN_ENTRY_CANCELLED;
    }
    if (res==GL_RESULT_INACTIVITY)
    {
        TRC_TRACE_INFO(trc_fun, "Pin Entry Timeout");
        UI_PromptMsgDisplay(UI_PROMPT_MSG_PIN_ENTRY_TIMEOUT);
        return ERR_PIN_ENTRY_TIMEOUT;
    }

    return OK;
}

int FUN_EncipherPin(void)
{
    int ret;
    int i;
    unsigned char acc[8];
    unsigned char blk[8];
    char tmp[32];
    char buf[32];

    trc_fun = TRC_HandleGet();
    TRC_TRACE_INFO(trc_fun, "Pin Ciphering...");

    // PIN ciphering to get pinblock
    memcpy(acc, "\x00\x00\x78\x90\x12\x34\x56\x74", 8);
    ret = _FUN_PinCiphering(acc, blk); 
    if (ret!=OK)
    {
        TRC_TRACE_INFO(trc_fun, "Pin Ciphering...KO");
        return -1;
    }

    memset(buf, 0, sizeof(buf));
    TRC_TRACE_INFO(trc_fun, "Account Number");
    for (i=0; i<8; i++)
    {
        memset(tmp, 0, sizeof(tmp));
        sprintf(tmp, "%02x ", acc[i]);
        strcat(buf, tmp);
    }
    TRC_TRACE_INFO(trc_fun, buf);

    TRC_TRACE_INFO(trc_fun, "Pin Key");
    TRC_TRACE_INFO(trc_fun, "6B 21 8F 24 DE 7D C6 6C");

    memset(buf, 0, sizeof(buf));
    TRC_TRACE_INFO(trc_fun, "Pin Block");
    for (i=0; i<8; i++)
    {
        memset(tmp, 0, sizeof(tmp));
        sprintf(tmp, "%02x ", blk[i]);
        strcat(buf, tmp);
    }
    TRC_TRACE_INFO(trc_fun, buf);

   TRC_TRACE_INFO(trc_fun, "Pin Ciphering...OK");
    return (ret);
}

int FUN_MacCalculation(void)
{
    int ret;
    static const unsigned char tabICV[8]            = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char tabinput [8*8];
    T_SEC_DATAKEY_ID key;

    trc_fun = TRC_HandleGet();

    /* MAC DES                                   */
    /* Ciphered Result : D5 C2 92 14 61 C1 B1 39 */
    /* With Input data : 05 05 ... 05 (64 bytes) */
    /* ICV             : 00 00 00 00 00 00 00 00 */
    /*********************************************/
    key.iSecretArea = ID_SCR_XXX_BANK;
    key.cAlgoType = TLV_TYPE_KDES; /* MAC key is a DES Key */
    key.usNumber = MAC_KEY_NO_XXX;
    key.uiBankId = ID_BANK_XXX;

    memset (tabinput, 0x05, sizeof(tabinput));
    ret = SEC_ComputeMAC(&key, (unsigned char *) tabinput, sizeof(tabinput), (unsigned char *) tabICV, outputData);
    if (ret == OK)
    {
        TRC_TRACE_INFO(trc_fun, "MAC Calculation...OK");
        outputLen = 8;
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "MAC Calculation...KO");
    }

    return (ret);
}

