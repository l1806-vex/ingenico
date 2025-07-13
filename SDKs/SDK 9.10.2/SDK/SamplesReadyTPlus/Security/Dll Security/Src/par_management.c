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
 Module  : PAR - Parameter Management Unit

 @file      par_management.c
 @brief     This file contains the parameters  that is implemented
            by this sample.
            
 @date      13/03/2013

 ------------------------------------------------------------------------------
 */

#include "SDK30.H"

#include "trace.h"
#include "par.h"
#include "Utilities.h"
#include "par_management.h"

static TRC_Trace_t trc_fun;

/** Convert hexadecimal character to nibble
 * \return nibble if OK; 0x10 on error
 */
static unsigned char _PAR_chr2nib(char chr) {
    switch (chr) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
          return (unsigned char) (chr - '0');
      case 'A':
      case 'B':
      case 'C':
      case 'D':
      case 'E':
      case 'F':
          return (unsigned char) (chr - 'A' + 10);
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
          return (unsigned char) (chr - 'a' + 10);
      default:
          break;
    }
    return 0x10;                //KO
}

/** Convert a hexadecimal string hex into a binary buffer bin of length len. 
 * The zero value of len means that the length is to be calculated as the strlen(hex).
 * The spaces and tabs at the beginning of hex are not allowed.
 * If operation is performed successfully, the number of bytes converted is returned.
 * In case of invalid input (invalid character) zero value is returned.
 * \param bin (O) Pointer to the buffer to be filled.
 * \param hex (I) Source string containing hexadecimal digits only.
 * \param len (I) Number of characters in the destination.
 * \return
 *    - number of bytes written into bin if OK.
 *    - 0 otherwise.
 */
static int _PAR_hex2bin(unsigned char * bin, const char *hex, int len) {
    int ret;                    //to be returned: number of characters processed
    unsigned char tmp;

    //if non-zero, len is the length of acceptor buffer bin
    if(!len)
    {                  //calcualte length if missing
        len = strlen(hex);
    }

    ret = 0;
    while(len--)
    {
        tmp = _PAR_chr2nib(*hex++);  //get first nibble
        if(tmp >= 0x10)
            break;
        *bin = (unsigned char) (tmp << 4);

        tmp = _PAR_chr2nib(*hex++);  //get second nibble
        if (tmp >= 0x10)
        {
            ret = 0;
            break;
        }
        *bin |= tmp;

        bin++;
        ret++;
    }
    return ret;
}

int PAR_Pin_KeyGet(unsigned char * buf)
{
    int ret;
    int len;
    char * data;
    int i;
    char tmp[32];
    char str[32];

    trc_fun = TRC_HandleGet();

    ret = PAR_PinKeyGet(&data);
    if (ret==PAR_OK)
    {
        memset(buf, 0, sizeof(buf));
        len = _PAR_hex2bin(buf, data, 0);
        if (len > 0)
        {
            memset(str, 0, sizeof(str));
            for (i=0; i<len; i++)
            {
                memset(tmp, 0, sizeof(tmp));
                sprintf(tmp, "%02x ", buf[i]);
                strcat(str, tmp);
            }
            TRC_TRACE_INFO(trc_fun, str);
            
        }
    }

    return ret;
}

int PAR_Mac_KeyGet(unsigned char * buf)
{
    int ret;
    int len;
    char * data;
    int i;
    char tmp[32];
    char str[32];

    trc_fun = TRC_HandleGet();

    ret = PAR_MacKeyGet(&data);
    if (ret==PAR_OK)
    {
        memset(buf, 0, sizeof(buf));
        len = _PAR_hex2bin(buf, data, 0);
        if (len > 0)
        {
            memset(str, 0, sizeof(str));
            for (i=0; i<len; i++)
            {
                memset(tmp, 0, sizeof(tmp));
                sprintf(tmp, "%02x ", buf[i]);
                strcat(str, tmp);
            }
            TRC_TRACE_INFO(trc_fun, str);
        }
    }

    return ret;
}

int PAR_PinMaster_KeyGet(unsigned char * buf)
{
    int ret;
    int len;
    char * data;
    int i;
    char tmp[32];
    char str[32];

    trc_fun = TRC_HandleGet();

    ret = PAR_PinMasterKeyGet(&data);
    if (ret==PAR_OK)
    {
        memset(buf, 0, sizeof(buf));
        len = _PAR_hex2bin(buf, data, 0);
        if (len > 0)
        {
            memset(str, 0, sizeof(str));
            for (i=0; i<len; i++)
            {
                memset(tmp, 0, sizeof(tmp));
                sprintf(tmp, "%02x ", buf[i]);
                strcat(str, tmp);
            }
            TRC_TRACE_INFO(trc_fun, str);
        }
    }

    return ret;
}

int PAR_MacMaster_KeyGet(unsigned char * buf)
{
    int ret;
    int len;
    char * data;
    int i;
    char tmp[32];
    char str[32];

    trc_fun = TRC_HandleGet();

    ret = PAR_MacMasterKeyGet(&data);
    if (ret==PAR_OK)
    {
        memset(buf, 0, sizeof(buf));
        len = _PAR_hex2bin(buf, data, 0);
        if (len > 0)
        {
            memset(str, 0, sizeof(str));
            for (i=0; i<len; i++)
            {
                memset(tmp, 0, sizeof(tmp));
                sprintf(tmp, "%02x ", buf[i]);
                strcat(str, tmp);
            }
            TRC_TRACE_INFO(trc_fun, str);
        }
    }

    return ret;
}

int PAR_Root_KeyGet(unsigned char * buf)
{
    int ret;
    int len;
    char * data;
    int i;
    char tmp[32];
    char str[32];

    trc_fun = TRC_HandleGet();

    ret = PAR_RootKeyGet(&data);
    if (ret==PAR_OK)
    {
        memset(buf, 0, sizeof(buf));
        len = _PAR_hex2bin(buf, data, 0);
        if (len > 0)
        {
            memset(str, 0, sizeof(str));
            for (i=0; i<len; i++)
            {
                memset(tmp, 0, sizeof(tmp));
                sprintf(tmp, "%02x ", buf[i]);
                strcat(str, tmp);
            }
            TRC_TRACE_INFO(trc_fun, str);
        }
    }

    return ret;
}

int PAR_SecurePartGet(int idx, T_SEC_PARTTYPE * secPart)
{
    int ret;
    enum esecurePart data;

    *secPart = C_SEC_CIPHERING;
    ret = PAR_SecConfig_SecurePartGet(idx, &data);
    if (ret == PAR_OK)
    {
        switch (data)
        {
            case securePart_Pincode:
                *secPart = C_SEC_PINCODE;
                break;
            case securePart_Card:
                *secPart = C_SEC_CARD;
                break;
            case securePart_Ciphering:
            default:
                *secPart = C_SEC_CIPHERING;
                break;
        }
    }

    return ret;
}

int _PAR_TrmBoosterGet(int idx, char * booster)
{
    int ret;
    enum eterminalBooster data;

    *booster = C_SEC_BL2;
    ret = PAR_SecConfig_TerminalBoosterGet(idx, &data);
    if (ret == PAR_OK)
    {
        switch (data)
        {
            case terminalBooster_Booster1:
                *booster = C_SEC_BL1;
                break;
            case terminalBooster_Booster2:
            default:
                *booster = C_SEC_BL2;
                break;
        }
    }

    return (ret);
}

int _PAR_PpBoosterGet(int idx, char * booster)
{
    int ret;
    enum epinpadBooster data;

    *booster = C_SEC_BL2;
    ret = PAR_SecConfig_PinpadBoosterGet(idx, &data);
    if (ret == PAR_OK)
    {
        switch (data)
        {
            case pinpadBooster_Booster1:
                *booster = C_SEC_BL1;
                break;
            case pinpadBooster_Booster2:
            default:
                *booster = C_SEC_BL2;
                break;
        }
    }

    return (ret);
}

int PAR_BoosterGet(int idx, char * booster)
{
    int ret;
    enum eperipheralBooster data;

    ret = PAR_SecConfig_PeripheralBoosterGet(idx, &data);
    if (ret == PAR_OK)
    {
        switch (data)
        {
            case peripheralBooster_iappUsbUsrName:
                _PAR_PpBoosterGet(idx, booster);
                break;
            case peripheralBooster_iappUsbName:
            default:
                _PAR_TrmBoosterGet(idx, booster);
                break;
        }
    }

    return (ret);
}

int PAR_PeriphBoosterGet(int idx, char ** periph)
{
    int ret;
    enum eperipheralBooster data;

    ret = PAR_SecConfig_PeripheralBoosterGet(idx, &data);
    if (ret == PAR_OK)
    {
        switch (data)
        {
            case peripheralBooster_iappUsbName:
                *periph = IAPP_USB_NAME;
                break;
            case peripheralBooster_iappUsbUsrName:
                *periph =IAPP_USB_USR_NAME;
                break;

            case peripheralBooster_iappDefName:
            default:
                *periph = IAPP_DEF_NAME;
                break;
        }
    }

    return (ret);
}

