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
   
 Project : Desfire Sample
 Module  : FUN - Demo Features Unit

 @file      fun_desfire.c
 @brief     This file contains the definition of processes that is implemented
            by this sample.
            
 @date      30/03/2013

 ------------------------------------------------------------------------------
 */


#include "SDK30.H"
#include "Desfire.h"
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
#include "par_management.h"
#include "trace.h"

static int _FUN_ClessGetError(int err);
static int _FUN_DesfireGetError(int err);
static int _FUN_DetectCard(int async, int dly);
static int _FUN_DesfireThunder(void);
static int _FUN_FormatPICC(void);
static int _FUN_FreeContext(void);
static int _FUN_AuthenticateHost(void);
static int _FUN_ChangeKeyEntry(void);
static int _FUN_ResetKeyEntry(void);

// Local variables
static TRC_Trace_t trc_fun;
FILE* hSAM = NULL;
T_MIFARE_SAM_CONTEXT *pSamContext = NULL;

/** Process the result of the cless processing
 *
 * \param[in] err result of previous excecution
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
static int _FUN_ClessGetError(int err)
{
    switch(err)
    {
        case CL_OK: // The Desfire card is correctly detected
            TRC_TRACE_INFO(trc_fun, "Cless OK");
            return 1;

        case CL_TOOMANYCARDS:
            TRC_TRACE_ERR(trc_fun, "Too many cards are presented");
            UI_ErrMsgDisplay(ERR_TOO_MANY_CARDS);
            break;

        case CL_NOCARD:
            TRC_TRACE_ERR(trc_fun, "There is no card (timeout)");
            UI_ErrMsgDisplay(ERR_NO_CARD_DETECTED);
            break;

        case CL_INVALIDCARD:
            TRC_TRACE_ERR(trc_fun, "The detected card is not a MIFARE one");
            UI_ErrMsgDisplay(ERR_INVALID_CARD);
            break;

        case CLESS_NOT_IMPLEMENTED:
            TRC_TRACE_ERR(trc_fun, "Cless not Implemented");
            UI_ErrMsgDisplay(ERR_CLESS_NOT_IMPLEMENTED);
            break;

        case CL_KO:
        default:
            TRC_TRACE_ERR(trc_fun, "An error occurred err=%d", err);
            UI_ErrMsgDisplay(ERR_UNDEFINED);
            break;
    }

    return 0;
}

/** Process the result of the desfire processing
 *
 * \param[in] err result of previous excecution
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
static int _FUN_DesfireGetError(int err)
{
    switch(err)
    {
        case DESFIRE_OPERATION_OK:
           TRC_TRACE_ERR(trc_fun, "DESFIRE OPERATION OK");
            return 1;

        case DESFIRE_NO_CHANGES:
           TRC_TRACE_ERR(trc_fun, "DESFIRE NO CHANGES");
            break;

        case DESFIRE_OUT_OF_EEPROM_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE OUT OF EEPROM");
            break;

        case DESFIRE_ILLEGAL_COMMAND:
           TRC_TRACE_ERR(trc_fun, "DESFIRE ILLEGAL COMMAND");
            break;

        case DESFIRE_INTEGRITY_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE INTEGRITY ERROR");
            break;

        case DESFIRE_NO_SUCH_KEY:
           TRC_TRACE_ERR(trc_fun, "DESFIRE NO SUCH KEY");
            break;

        case DESFIRE_LENGTH_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE LENGTH ERROR");
            break;

        case DESFIRE_PERMISSION_DENIED:
           TRC_TRACE_ERR(trc_fun, "DESFIRE PERMISSION DENIED");
            break;

        case DESFIRE_PARAMETER_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE PARAMETER ERROR");
            break;

        case DESFIRE_APPLICATION_NOT_FOUND:
           TRC_TRACE_ERR(trc_fun, "DESFIRE APPLICATION NOT FOUND");
            break;

        case DESFIRE_APPL_INTEGRITY_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE APPLICATION INTEGRITY ERROR");
            break;

        case DESFIRE_AUTHENTICATION_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE AUTHENTICATION ERROR");
            break;

        case DESFIRE_ADDITIONAL_FRAME:
           TRC_TRACE_ERR(trc_fun, "DESFIRE ADDITIONAL FRAME");
            break;

        case DESFIRE_BOUNDARY_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE BOUNDARY ERROR");
            break;

        case DESFIRE_PICC_INTEGRITY_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE PICC INTEGRITY ERROR");
            break;

        case DESFIRE_COMMAND_ABORTED:
           TRC_TRACE_ERR(trc_fun, "DESFIRE COMMAND ABORTED");
            break;

        case DESFIRE_PICC_DISABLED:
           TRC_TRACE_ERR(trc_fun, "DESFIRE PICC DISABLED");
            break;

        case DESFIRE_COUNT_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE COUNT ERROR");
            break;

        case DESFIRE_DUPLICATE_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE DUPLICATE ERROR");
            break;

        case DESFIRE_EEPROM_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE EEPROM ERROR");
            break;

        case DESFIRE_FILE_NOT_FOUND:
           TRC_TRACE_ERR(trc_fun, "DESFIRE FILE NOT FOUND");
            break;

        case DESFIRE_FILE_INTEGRITY_ERROR:
           TRC_TRACE_ERR(trc_fun, "DESFIRE FILE INTEGRITY ERROR");
            break;

        case DESFIRE_DLL_NOT_LOADED:
           TRC_TRACE_ERR(trc_fun, "DESFIRE DLL NOT LOADED");
            break;

        default:
            TRC_TRACE_ERR(trc_fun, "An error occurred err=%d", err);
            break;
    }

    UI_ErrMsgDisplay(ERR_DESFIRE_ERROR);
    return 0;
}

/** Wait for Card detection
 *
 * \param[in] async flag that indicates if asynchronous or synchronous
 * \param[in] dly detection delay
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
static int _FUN_DetectCard(int async, int dly)
{
    int ret;
    int end;
    int key;
    int res;
    int stop;
    unsigned int event;
    unsigned int numCards;

    numCards = 1;
    stop = FALSE;

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


    if (async) // Asynchronous mode
    {
        // Start the asynchronous card detection
        res = ClessEmv_DetectCardsStart(3, CL_TYPE_AB);//number max is 3 here for ex.

        if (res == CL_OK)
        {
            // The card is correctly detected
            end = FALSE;

            kbdStart(1);
            do
            {
                // Wait for an event : keyboard, cless or timeout
                event = ttestall(KEYBOARD | CLESS, dly * 100);
                if (event == KEYBOARD)
                {
                    // Keyboard event
                    key = getchar(); // get the pressed key
                    
                    if (key == T_ANN) // The detection is cancelled only if the red key is pressed
                    {
                        TRC_TRACE_ERR(trc_fun, "Detection Cancelled");
                        res = CL_OK;
                        end = TRUE;
                    }
                }
                else // Cless or timeout
                {
                    if (event == 0)
                    {
                        // Timeout event
                        res = CL_NOCARD;
                        TRC_TRACE_ERR(trc_fun, "Detection Timeout");
                    }
                    end = TRUE;
                }
            } while (!end);
            kbdStop();

            // If the cless event is received
            if (event == CLESS)
            {
                res = ClessEmv_DetectCards(CL_TYPE_AB, &numCards, 1);
            }
            else
            {
                stop = TRUE;
            }
        }
        else
        {
            TRC_TRACE_INFO(trc_fun, "CLESS_DetectCardsStart=%i", res);
            return FALSE;
        }
    }
    else // Synchronous mode
    {
        // Deselect the card (synchronous mode)
        res = ClessEmv_DetectCards(CL_TYPE_AB, &numCards, dly);
    }

    if (stop==TRUE)
    {
        ClessEmv_DetectCardsStop();
    }

    TPass_FirstLine();
    ret = _FUN_ClessGetError(res);
    return ret;
}

/** Perform the following desfire operations:
 * - context initialization
 * - create a simple des key
 * - authenticate
 * - get card UID
 * - get application id's
 * - create application
 * - select an application
 * - backup a data file
 * - get file id's
 * - read and write data
 * - commit transaction
 * - free key and context
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
static int _FUN_DesfireThunder(void)
{
    int ret;
    int res;
    int i;
    int arrayLen = 0;
    int count = 0;
    unsigned char array[32];
    T_DESFIRE_CONTEXT *context;
    T_MIFARE_KEY *key;
    T_DESFIRE_AID aid[MAX_APPLICATION_COUNT];
    struct S_DESFIRE_VERSION_INFO info;
    char tmp[32];
    char buf[64];

    /* Context initialization */
    context = desfire_NewContext(APDU_NATIVE); //could have been APDU_WRAPPED

    /* Create a simple DES key (here master key default value */
    key = mifare_NewDesKeyWithVersion((unsigned char*) "\0\0\0\0\0\0\0\0",
    MF_CHAINING_DESFIRE_NATIVE); // MF_CHAINING_DESFIRE_NATIVE because we want this key to be DESFire EV0 compliant

    res = desfire_GetVersion(context, &info);
    TRC_TRACE_INFO(trc_fun, "desfire_GetVersion=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    memset(buf, 0, sizeof(buf));
    for (i = 0; i < sizeof(struct S_DESFIRE_VERSION_INFO); i++)
    {
        memset(tmp,0, sizeof(tmp));
        if (i == 0)
        {
            strcat(buf, "HW info :");
        }
        else if (i == 7)
        {
            TRC_TRACE_INFO(trc_fun, buf);
            memset(buf, 0, sizeof(buf));
            strcat(buf, "SW info :");
        }
        else if (i == 14)
        {
            TRC_TRACE_INFO(trc_fun, buf);
            memset(buf, 0, sizeof(buf));
            strcat(buf, "Other info :");
        }
        sprintf(tmp, " %02X", ((unsigned char*) &info)[i]);
        strcat(buf, tmp);
    }
    TRC_TRACE_INFO(trc_fun, buf);

    res = desfire_Authenticate(context, 0, key);
    TRC_TRACE_INFO(trc_fun, "desfire_Authenticate=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    /* Get card UID with DESFire command */
    res = desfire_GetCardUID(context, array, &arrayLen);
    TRC_TRACE_INFO(trc_fun, "desfire_GetCardUID=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    memset(buf, 0, sizeof(buf));
    strcat(buf, "UID :");
    for (i = 0; i < arrayLen; i++)
    {
        memset(tmp, 0, sizeof(tmp));
        sprintf(tmp, " %02X", array[i]);
        strcat(buf, tmp);
    }
    TRC_TRACE_INFO(trc_fun, buf);

    /* Get the list of existing applications */
    res = desfire_GetApplicationIds(context, aid, &count);
    TRC_TRACE_INFO(trc_fun, "desfire_GetApplicationIds=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    memset(buf, 0, sizeof(buf));
    if (count != 0)
    {
        for (i = 0; i < count; i++)
        {
            memset(tmp, 0, sizeof(tmp));
            sprintf(tmp, "%02X %02X %02X\n", aid[i][0], aid[i][1], aid[i][2]);
            strcat(buf, tmp);
        }
    }
    TRC_TRACE_INFO(trc_fun, buf);

    /* Creation of 3 applications with different settings */
    desfire_DeleteApplication(context, aid); //delete application first if already created

    res = desfire_CreateApplication(context, 0x11, 0xFF, 0x00, 0, 0, 0);
    TRC_TRACE_INFO(trc_fun, "desfire_CreateApplication=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    ret = desfire_CreateApplication(context, 0x22, 0xEF, 0x06, 0, 0, 0);
    TRC_TRACE_INFO(trc_fun, "desfire_CreateApplication=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    ret = desfire_CreateApplication(context, 0x33, 0xC2, 0x0E, 0, 0, 0);
    TRC_TRACE_INFO(trc_fun, "desfire_CreateApplication=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }
    
    /* Get the list of existing applications */
    ret = desfire_GetApplicationIds(context, aid, &count);
    TRC_TRACE_INFO(trc_fun, "desfire_GetApplicationIds=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    memset(buf, 0, sizeof(buf));
    if (count != 0)
    {
        for (i = 0; i < count; i++)
        {
            memset(tmp, 0, sizeof(tmp));
            sprintf(tmp, "%02X %02X %02X\n", aid[i][0], aid[i][1], aid[i][2]);
            strcat(buf, tmp);
        }
    }
    TRC_TRACE_INFO(trc_fun, buf);

    /* Selection of the 2nd application */
    res = desfire_SelectApplication(context, 0x22);
    TRC_TRACE_INFO(trc_fun, "desfire_SelectApplication=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }
    
    /* Authentication with application master key (use the same default key)*/
    res = desfire_Authenticate(context, 0, key);
    TRC_TRACE_INFO(trc_fun, "desfire_Authenticate=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    /* Creation of a file backup data file within the selected application */
    desfire_DeleteFile(context, (T_DESFIRE_FID) 0x09);
    res = desfire_CreateBackupDataFile(context, (T_DESFIRE_FID) 0x09, NULL, DCM_ENCIPHERED, 0x0000, 20);
    TRC_TRACE_INFO(trc_fun, "desfire_CreateBackupDataFile=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }
    
    /* Get the list of existing files */
    res = desfire_GetFileIds(context, array, &count);
    TRC_TRACE_INFO(trc_fun, "desfire_GetFileIds=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    memset(buf, 0, sizeof(buf));
    if (count != 0)
    {
        for (i = 0; i < count; i++)
        {
            memset(tmp, 0, sizeof(tmp));
            sprintf(tmp, "%02X\n", array[i]);
            strcat(buf, tmp);
        }
    }
    TRC_TRACE_INFO(trc_fun, buf);

    /* Write data into the file */
    res = desfire_WriteData(context, (T_DESFIRE_FID) 0x09, 0, 11, "Hello World");
    TRC_TRACE_INFO(trc_fun, "desfire_WriteData=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    /* Read the file without having commited the data */
    res = desfire_ReadData(context, (T_DESFIRE_FID) 0x09, 0, 0, (unsigned long*) &count, array);
    TRC_TRACE_INFO(trc_fun, "desfire_ReadData=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    if (count != 0)
    {
        memset(buf, 0, sizeof(buf));
        for (i = 0; i < count; i++)
        {
            memset(tmp, 0, sizeof(tmp));
            sprintf(tmp, "%c", array[i]);
            strcat(buf, tmp);
        }
        TRC_TRACE_INFO(trc_fun, buf);
    }

    /* Commit transaction (mandatory, except for standard data files, to validate files changes) */
    res = desfire_CommitTransaction(context);
    TRC_TRACE_INFO(trc_fun, "desfire_CommitTransaction=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    /* Read the file after having commited the data */
    res = desfire_ReadData(context, (T_DESFIRE_FID) 0x09, 0, 0, (unsigned long*) &count, array);
    TRC_TRACE_INFO(trc_fun, "desfire_ReadData=%i", res);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    if (count != 0)
    {
        memset(buf, 0, sizeof(buf));
        for (i = 0; i < count; i++)
        {
            memset(tmp, 0, sizeof(tmp));
            sprintf(tmp, "%c", array[i]);
            strcat(buf, tmp);
        }
        TRC_TRACE_INFO(trc_fun, buf);
    }

    mifare_FreeKey(key);
    desfire_FreeContext(context);
    return ret;
}

/** Releases the PICC user memory
 * This command releases all allocated user memory on the PICC. All
 * applications are deleted and all files within those applications are deleted.
 * The memory is deleted.
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
static int _FUN_FormatPICC(void)
{
    int ret;
    int res;
    T_DESFIRE_CONTEXT *context;
    T_MIFARE_KEY *key;

    TRC_TRACE_INFO(trc_fun, "Context initialization...");
    context = desfire_NewContext(APDU_NATIVE); //could have been APDU_WRAPPED

    TRC_TRACE_INFO(trc_fun, "Creating new DES key...");
    key = mifare_NewDesKeyWithVersion((unsigned char*) "\0\0\0\0\0\0\0\0", MF_CHAINING_DESFIRE_NATIVE);

    TRC_TRACE_INFO(trc_fun, "Desfire Authenticate...");
    res= desfire_Authenticate(context, 0, key);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    TRC_TRACE_INFO(trc_fun, "Desfire Format Picc...");
    res = desfire_FormatPicc(context);
    ret = _FUN_DesfireGetError(res);
    if (ret!=1)
    {
        mifare_FreeKey(key);
        desfire_FreeContext(context);
        return ret;
    }

    mifare_FreeKey(key);
    desfire_FreeContext(context);
    return ret;
}

/** Clear a SAM context
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
static int _FUN_FreeContext(void)
{
    /* Context destruction */
    if (pSamContext != NULL)
        mifareSAM_FreeContext(pSamContext);
    pSamContext = NULL;
    return 1;
}

/** Authenticate a SAM host
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
static int _FUN_AuthenticateHost(void)
{
    int ret = 0;
    T_MIFARE_KEY *key;
    unsigned char ucAuthMode;
    unsigned char ucKeyNo;
    unsigned char ucKeyVersion;
    unsigned char ucDivInp[2];

    _FUN_FreeContext();
    TRC_TRACE_INFO(trc_fun, "SAM Initialization...");
    hSAM = mifareSAM_AutoDetectSAM();
    if (hSAM == NULL)
    {
        TRC_TRACE_ERR(trc_fun, "SAM initialization...KO");
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "Creating SAM Context...");
    pSamContext = mifareSAM_NewContext(hSAM, MF_SAM_AV1); //could have been APDU_WRAPPED
    if (pSamContext == NULL)
    {
        TRC_TRACE_ERR(trc_fun, "SAM not found or power on failed");
        TRC_TRACE_ERR(trc_fun, "Creating SAM Context...KO");
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "Creating new DES key...");
    key = mifare_NewDesKeyWithVersion((unsigned char*) "\0\0\0\0\0\0\0\0", MF_CHAINING_CBC);
    
    ucAuthMode   = 0;    // ok
    ucKeyNo      = 0x02; // ok
    ucKeyVersion = 0;    // ok
    memset(ucDivInp, 0x00, sizeof(ucDivInp));

    TRC_TRACE_INFO(trc_fun, "Authenticating Host...");
    ret = mifareSAM_AuthenticateHost(pSamContext, key, ucAuthMode, ucKeyNo, ucKeyVersion, ucDivInp, sizeof(ucDivInp));
    ret = _FUN_DesfireGetError(ret);
    
    if (key != NULL)
    {
        TRC_TRACE_INFO(trc_fun, "Destroying Keys...");
        mifare_FreeKey(key);
    }
    key = NULL;

    return ret;
}

/** Change a SAM key entry
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
static int _FUN_ChangeKeyEntry(void)
{
    int ret;
    int res;
    unsigned char ucNewPosAkey[16];
    unsigned char ucNewPosBkey[16];
    unsigned char ucNewPosCkey[16];
    const unsigned char ucDfAid[3] = {0x00, 0x00, 0x00};
    const unsigned char ucSet[2] = {0x20, 0x00};
    unsigned char ucKeyNo;
    unsigned char ucProgMask;
    T_MIFARE_KEY_ENTRY KeyEntry;
    

    // Check input parameters
    if ((hSAM == NULL) || (pSamContext == NULL))
    {
        TRC_TRACE_ERR(trc_fun, "SAM not initialized");
        return 0;
    }

    res = PAR_KeyAGet(ucNewPosAkey);
    if (res!=PAR_OK)
    {
        TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
        return ERR_PAR_FILE_NOT_FOUND;
    }

    PAR_KeyBGet(ucNewPosBkey);
    if (res!=PAR_OK)
    {
        TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
        return ERR_PAR_FILE_NOT_FOUND;
    }

    PAR_KeyCGet(ucNewPosCkey);
    if (res!=PAR_OK)
    {
        TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
        return ERR_PAR_FILE_NOT_FOUND;
    }

    memcpy(KeyEntry.tKeyA, ucNewPosAkey, sizeof(ucNewPosAkey));
    memcpy(KeyEntry.tKeyB, ucNewPosBkey, sizeof(ucNewPosBkey));
    memcpy(KeyEntry.tKeyC, ucNewPosCkey, sizeof(ucNewPosCkey));
    memcpy(KeyEntry.dfAid, ucDfAid, sizeof(ucDfAid));
    KeyEntry.dfKeyNr = 0;
    KeyEntry.CEK_No = 0;
    KeyEntry.CEK_V = 0;
    KeyEntry.KUC = 0xff;
    memcpy(KeyEntry.SET, ucSet, sizeof(ucSet));
    KeyEntry.VerA = 0x00;
    KeyEntry.VerB = 0x01;
    KeyEntry.VerC = 0x02;
    
    ucKeyNo = 0;       // Key entry number
    ucProgMask = 0xFF; // Versions are sent separately and all items are updated.

    TRC_TRACE_INFO(trc_fun, "Changing Key Entry...");
    ret = mifareSAM_ChangeKeyEntryEx(pSamContext, ucKeyNo, ucProgMask, sizeof(T_MIFARE_KEY_ENTRY), &KeyEntry);
    ret = _FUN_DesfireGetError(ret);

    return ret;
}

/** Reset a SAM key entry
 *
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref 0 in case of error
 */
static int _FUN_ResetKeyEntry(void)
{
    int ret;
    int res;
    unsigned char ucNewPosAkey[16];
    unsigned char ucNewPosBkey[16];
    unsigned char ucNewPosCkey[16];
    const unsigned char ucDfAid[3] = {0x00, 0x00, 0x00};
    const unsigned char ucSet[2] = {0x20, 0x80}; // AES-192
    unsigned char ucKeyNo;
    unsigned char ucProgMask;
    T_MIFARE_KEY_ENTRY KeyEntry;

    // Check input parameters
    if ((hSAM == NULL) || (pSamContext == NULL))
    {
        TRC_TRACE_ERR(trc_fun, "SAM not initialized");
        return 0;
    }

    res = PAR_KeyAGet(ucNewPosAkey);
    if (res!=PAR_OK)
    {
        TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
        return ERR_PAR_FILE_NOT_FOUND;
    }

    PAR_KeyBGet(ucNewPosBkey);
    if (res!=PAR_OK)
    {
        TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
        return ERR_PAR_FILE_NOT_FOUND;
    }

    PAR_KeyCGet(ucNewPosCkey);
    if (res!=PAR_OK)
    {
        TRC_TRACE_INFO(trc_fun, "PAR Not Initialized");
        return ERR_PAR_FILE_NOT_FOUND;
    }

    memcpy(KeyEntry.tKeyA, ucNewPosAkey, sizeof(ucNewPosAkey));
    memcpy(KeyEntry.tKeyB, ucNewPosBkey, sizeof(ucNewPosBkey));
    memcpy(KeyEntry.tKeyC, ucNewPosCkey, sizeof(ucNewPosCkey));
    memcpy(KeyEntry.dfAid, ucDfAid, sizeof(ucDfAid));
    KeyEntry.dfKeyNr = 0;
    KeyEntry.CEK_No = 0;
    KeyEntry.CEK_V = 0;
    KeyEntry.KUC = 0xff;
    memcpy(KeyEntry.SET, ucSet, sizeof(ucSet));
    KeyEntry.VerA = 0x00;
    KeyEntry.VerB = 0x01;
    KeyEntry.VerC = 0x02;

    ucKeyNo = 0;       // Key entry number
    ucProgMask = 0xFF; // Versions are sent separately and all items are updated.

    TRC_TRACE_INFO(trc_fun, "Reseting Key Entry...");
    ret = mifareSAM_ChangeKeyEntryEx(pSamContext, ucKeyNo, ucProgMask, sizeof(T_MIFARE_KEY_ENTRY), &KeyEntry);
    ret = _FUN_DesfireGetError(ret);

    return ret;
}

int FUN_Desfire(int test)
{
    int ret;
    int res;
    char tmp[32];
    unsigned char cardUid[12]; // unique IDentifier of the card detected

    trc_fun = TRC_HandleGet();

    ret = ClessEmv_OpenDriver();
    if (ret == CL_KO)
    {
    pprintf("ClessEmv_OpenDriver() KO");
        return 0;
    }

    TRC_TRACE_INFO(trc_fun, "MIFARE DESfire sample");
    TRC_TRACE_INFO(trc_fun, "Card detection...");
    ret = _FUN_DetectCard(TRUE, 30);
    if (!ret)
    {
        ClessEmv_CloseDriver();
        return 0;
    }

    // Retrieve the UID of an ISO14443-4 card.
    // unique IDentifier of the card
    // buffer must be 12 bytes long. The UID can be on 4, 7 or 10 bytes.
    memset(cardUid, 0, sizeof(cardUid));
    TRC_TRACE_INFO(trc_fun, "ClessEmv_GetUid() =");
    res = ClessEmv_GetUid(cardUid);
    ret = _FUN_ClessGetError(res);
    if (ret!=1)
    {
        ClessEmv_CloseDriver();
        return 0;
    }
    sprintf(tmp, "UID = %02X %02X %02X %02X %02X %02X %02X\n", cardUid[0], cardUid[1], cardUid[2], cardUid[3], cardUid[4], cardUid[5], cardUid[6]);
    TRC_TRACE_INFO(trc_fun, tmp);

    // Activate an ISO14443-4 contactless card
    res = ClessEmv_ActiveCard(0, CL_ISO14443_4);
    ret = _FUN_ClessGetError(res);
    if (ret != 1)
    {
        ClessEmv_CloseDriver();
        return 0;
    }
    
    switch (test)
    {
        case 0:
            ret = _FUN_DesfireThunder();
            break;
        case 1:
            ret = _FUN_FormatPICC();
            break;
        case 2:
            ret = _FUN_AuthenticateHost();
            break;
        case 3:
            ret = _FUN_ChangeKeyEntry();
            break;
        case 4:
            ret = _FUN_ResetKeyEntry();
            break;
        case 5:
            ret = _FUN_FreeContext();
            break;
        default:
            break;
   }

   ClessEmv_CloseDriver();// Close the contactless driver
   return ret;
}

