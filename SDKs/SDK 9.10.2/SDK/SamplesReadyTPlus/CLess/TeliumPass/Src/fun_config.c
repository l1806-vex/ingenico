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

 @file      fun_config.c
 @brief     This file contains the definition of processes that is implemented
            by this sample.
            
 @date      08/03/2013

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "sdk30.h"
#include "TlvTree.h"
#include "oem_sys.h"
#include "oem_cless.h"
#include "oem_clmf1.h"
#include "uiram.h"
#include "DataElement.h"
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"

#include "utilities.h"
#include "err_process.h"
#include "ui_userinterface.h"
#include "fun_demofeatures.h"
#include "trace.h"

#define C30_CHENILLARD_TIME 15

static void _FUN_ListModules(void);
static void _FUN_ListComponents(void);
static void _FUN_SoftwareCapabilities (void);
static void _FUN_HardwareCapabilities (void);
/*static void _FUN_Diagnostics (void);*/

static TRC_Trace_t trc_fun;

static void _FUN_ListModules(void)
{
    int ret;
    unsigned char buf[512];

    ret = TPass_GetApplicationVersions(buf, sizeof(buf));
    if (ret == ERR_TPASS_OK)
    {
        TRC_TRACE_INFO(trc_fun, "Telium Pass Application Modules");
        TRC_TRACE_INFO(trc_fun, (char *)buf);
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "TPass_GetApplicationVersions error");
    }

}

static void _FUN_ListComponents(void)
{
    int idx;
    int ret=ERR_TPASS_OK;
    T_TPASS_COMPONENT_INFO Info;

    idx = 0;
    TRC_TRACE_INFO(trc_fun, "TeliumPass Components");
    while (ret==ERR_TPASS_OK)
    {
        ret = TPass_GetComponentInfoByIndex(idx, &Info);
        if (ret == ERR_TPASS_OK)
        {
            TRC_TRACE_INFO(trc_fun, "Label     : %s", Info.Label);
            TRC_TRACE_INFO(trc_fun, "Number      : %s", Info.Identification);
            TRC_TRACE_INFO(trc_fun, "Size          : %d", Info.Size);
            TRC_TRACE_INFO(trc_fun, "CRC           : %04X", Info.Crc);
            TRC_TRACE_INFO(trc_fun, "Type          : %d", Info.Type);
            TRC_TRACE_INFO(trc_fun, "Key           : %08X", Info.Key);
            TRC_TRACE_INFO(trc_fun, "Load adr      : %08X", Info.LoadingAddress);
            TRC_TRACE_INFO(trc_fun, "Start data adr: %08X", Info.DataAddressStart);
            TRC_TRACE_INFO(trc_fun, "End data adr  : %08X", Info.DataAddressEnd);
            TRC_TRACE_INFO(trc_fun, "Entry point   : %08X", Info.EntryPointAddress);
            TRC_TRACE_INFO(trc_fun, "RUF adr 1     : %08X", Info.RufAddress1);
            TRC_TRACE_INFO(trc_fun, "RUF adr 2     : %08X", Info.RufAddress2);
            TRC_TRACE_INFO(trc_fun, "RUF adr 3     : %08X", Info.RufAddress3);
            idx++;
        }
    }
}

static void _FUN_SoftwareCapabilities (void)
{
    int ret;
    T_TPASS_SOFTWARE_CAPABILITIES SoftCapabilities;

    TRC_TRACE_INFO(trc_fun, "TeliumPass Software Capabilities");
    ret = TPass_GetSoftwareCapabilities(&SoftCapabilities);
    if (ret == ERR_TPASS_OK)
    {
        TRC_TRACE_INFO(trc_fun, "RUF 1       : %02X\n", SoftCapabilities.Ruf1);
        TRC_TRACE_INFO(trc_fun, "Security    : %X\n", SoftCapabilities.Security);
        TRC_TRACE_INFO(trc_fun, "ISO14443 C  : %X\n", SoftCapabilities.Iso14443_C);
        TRC_TRACE_INFO(trc_fun, "Mifare      : %X\n", SoftCapabilities.Mifare);
        TRC_TRACE_INFO(trc_fun, "ISO14443 AB : %X\n", SoftCapabilities.Iso14443_AB);
        TRC_TRACE_INFO(trc_fun, "Appli       : %X\n", SoftCapabilities.Appli);
        TRC_TRACE_INFO(trc_fun, "RUF 2       : %X\n", SoftCapabilities.Ruf2);
    }
}

static void _FUN_HardwareCapabilities (void)
{
    int ret;
    T_TPASS_HARDWARE_CAPABILITIES HardCapabilities;

    TRC_TRACE_INFO(trc_fun, "TeliumPass Software Capabilities");
    ret = TPass_GetHardwareCapabilities(&HardCapabilities);
    if (ret == ERR_TPASS_OK)
    {
        TRC_TRACE_INFO(trc_fun, "Product id   :  %8s", HardCapabilities.szProductIdentification);
        TRC_TRACE_INFO(trc_fun, "Serial number:  %8s", HardCapabilities.szSerialNumber);
        TRC_TRACE_INFO(trc_fun, "Product code :  %8s", HardCapabilities.szProductCode);
        TRC_TRACE_INFO(trc_fun, "Constructor  :  %8s", HardCapabilities.szConstructorCode);
        TRC_TRACE_INFO(trc_fun, "Manufacturing:%c%c/%c%c/%c%c%c%c\n", HardCapabilities.szManufacturingDate[0], 
            HardCapabilities.szManufacturingDate[1], HardCapabilities.szManufacturingDate[2], HardCapabilities.szManufacturingDate[3],
            HardCapabilities.szManufacturingDate[4], HardCapabilities.szManufacturingDate[5], HardCapabilities.szManufacturingDate[6],
            HardCapabilities.szManufacturingDate[7]);
        TRC_TRACE_INFO(trc_fun, "Booster ver. :  %8s", HardCapabilities.szBoosterVersion);
    }

     TRC_TRACE_INFO(trc_fun, "Options");
    if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_BUZZER) != 0)
    {
        TRC_TRACE_INFO(trc_fun, "  Buzzer");
    }
    if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_USB_SLAVE) != 0)
    {
        TRC_TRACE_INFO(trc_fun, "  USB Slave");
    }
    if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_COM0) != 0)
    {
        if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_INTER_UC_ON_COM0) != 0)
        {
            TRC_TRACE_INFO(trc_fun, " *COM0");
        }
        else
        {
            TRC_TRACE_INFO(trc_fun, "  COM0");
        }
    }
    if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_COM1) != 0)
    {
        if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_COM0_COM1_SEPARATED) != 0)
        {
            TRC_TRACE_INFO(trc_fun, " !COM 1");
        }
        else
        {
            TRC_TRACE_INFO(trc_fun, "  COM 1");
        }
    }
    if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_SAM_1) != 0)
    {
        TRC_TRACE_INFO(trc_fun, "  SAM 1");
    }
    if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_SAM_2) != 0)
    {
        TRC_TRACE_INFO(trc_fun, "  SAM 2");
    }
    if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_SAM_3) != 0)
    {
        TRC_TRACE_INFO(trc_fun, "  SAM 3");
    }
    if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_SAM_4) != 0)
    {
        TRC_TRACE_INFO(trc_fun, "  SAM 4");
    }
    if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_DISPLAY_NONE) != 0)
    {
        TRC_TRACE_INFO(trc_fun, "  NO DISPLAY");
    }
    if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_DISPLAY_128_64) != 0)
    {
        TRC_TRACE_INFO(trc_fun, "  DISPLAY 128x64");
    }
}

/*
static void _FUN_Diagnostics (void)
{
    int ret;
    spy_data_t SpyData;
    char Diagnostics[TPASS_DIAGNOSTICS_SIZE + 1];
    int idx;
    int pos;
    char tmp[64];
    char buf[64];

    TRC_TRACE_INFO(trc_fun, "TeliumPass Diagnostics");
    ret = TPass_GetDiagnostics(&SpyData, Diagnostics);
    if (ret == ERR_TPASS_OK)
    {
        Diagnostics[TPASS_DIAGNOSTICS_SIZE] = '\0';
        TRC_TRACE_INFO(trc_fun, "Hard reset nb : %8d", SpyData.hard_reset_nbr);
        TRC_TRACE_INFO(trc_fun, "Soft reset nb : %8d", SpyData.soft_reset_nbr);
        TRC_TRACE_INFO(trc_fun, "Num of excep. : %8d", SpyData.exceptions_nbr);
        TRC_TRACE_INFO(trc_fun, "Type of excep.: %8d", SpyData.exception_type);
        TRC_TRACE_INFO(trc_fun, "r0            : %08X", SpyData.exception_r0);
        TRC_TRACE_INFO(trc_fun, "r1            : %08X", SpyData.exception_r1);
        TRC_TRACE_INFO(trc_fun, "r2            : %08X", SpyData.exception_r2);
        TRC_TRACE_INFO(trc_fun, "r3            : %08X", SpyData.exception_r3);
        TRC_TRACE_INFO(trc_fun, "r4            : %08X", SpyData.exception_r4);
        TRC_TRACE_INFO(trc_fun, "r5            : %08X", SpyData.exception_r5);
        TRC_TRACE_INFO(trc_fun, "r6            : %08X", SpyData.exception_r6);
        TRC_TRACE_INFO(trc_fun, "r7            : %08X", SpyData.exception_r7);
        TRC_TRACE_INFO(trc_fun, "r14            : %08X", SpyData.exception_r14);
    }

    TRC_TRACE_INFO(trc_fun, "Exception infos:");

    idx = 0;
    while(idx < EXCEPTION_INFO_LEN)
    {
        pos = 0;
        memset(buf, 0, sizeof(buf));
        do
        {
            memset(tmp, 0, sizeof(tmp));
            if (pos > 0)
            {
                strcat(buf, ".");
            }
            sprintf(tmp, "0x%08X", SpyData.exception_info[idx]);
            strcat(buf, tmp);
            idx++;
            pos++;
        } while((idx < EXCEPTION_INFO_LEN) && (pos < 4));
        
        TRC_TRACE_INFO(trc_fun, buf);
    }

    memset(tmp, 0, sizeof(tmp));
    sprintf(tmp, "Trap reset (ptr = 0x%02X):", SpyData.trap_reset_ptr);
    TRC_TRACE_INFO(trc_fun, tmp);

    idx = 0;
    pos = 0;
    memset(buf, 0, sizeof(buf));
    while(idx < TRAP_RESET_DATA_LEN)
    {
        if ((SpyData.trap_reset_data[idx] == '\n') || (SpyData.trap_reset_data[idx] == '\r'))
        {
            TRC_TRACE_INFO(trc_fun, buf);
            memset(buf, 0, sizeof(buf));
        }
        else if (SpyData.trap_reset_data[idx] > 0)
        {
            if (SpyData.trap_reset_data[idx] >= ' ')
            {
                memset(tmp, 0, sizeof(tmp));
                sprintf(tmp, "%c", SpyData.trap_reset_data[idx]);
                strcat(buf, tmp);
            }
            else
            {
                strcat(buf, ".");
            }
            
            pos++;
            if (pos >= 48)
            {
                pos = 0;
                TRC_TRACE_INFO(trc_fun, buf);
                memset(buf, 0, sizeof(buf));
            }
        }
        
        idx++;
    }

    if (buf[0]!=0)
    {
        TRC_TRACE_INFO(trc_fun, buf);
    }

    idx = 0;
    while (idx < TRAP_RESET_DATA_LEN)
    {
        pos = 0;
        memset(buf, 0, sizeof(buf));
        do
        {
            if (pos > 0)
            {
                strcat(buf, ".");
            }
            memset(tmp, 0, sizeof(tmp));
            sprintf(tmp, "%02X", SpyData.trap_reset_data[idx]);
            strcat(buf, tmp);
            idx++;
            pos++;
        } while((idx < TRAP_RESET_DATA_LEN) && (pos < 16));
        TRC_TRACE_INFO(trc_fun, buf);
    }
}
*/

void FUN_InfoTest(void)
{
    trc_fun = TRC_HandleGet();

    TRC_TRACE_INFO(trc_fun, "INFO TEST");

    _FUN_HardwareCapabilities();
    _FUN_SoftwareCapabilities();
    _FUN_ListComponents();
    _FUN_ListModules();
/*    _FUN_Diagnostics();*/

}

void FUN_CheckPresence (void)
{
    int status;
    int present;
    int key;

    dspStart();
    kbdStart(1);

    trc_fun = TRC_HandleGet();
    
    TRC_TRACE_INFO(trc_fun, "CHECK PRESENCE TEST");
    present = -1;
    while (1)
    {
        status = present;
        if (TPass_CheckPresence() == ERR_TPASS_OK)
        {
            present = 1;
        }
        else 
        {
            present = 0;
        }
        
        if (status != present)
        {
            if (present)
            {
                TPass_FirstLine();
                TPass_Display("CHECKING PRESENCE\n");
                TRC_TRACE_INFO(trc_fun, "CHECKING PRESENCE");
                ttestall(0, 2*100);
                TPass_Display("CONNECTED");
                TRC_TRACE_INFO(trc_fun, "CONNECTED");
                TPass_BacklightLevel(TPASS_BACKLIGHT_ON);
                break;
            }
            else
            {
                TRC_TRACE_ERR(trc_fun, "NOT CONNECTED");
                UI_ErrMsgDisplay(ERR_TPASS_NOT_CONNECTED);
                break;
            }
        }
        
        key = kbdKey();
        if (key == T_ANN)
        {
            break;
        }
    }

    kbdStop();
    dspStop();
}

void FUN_ResetTest (void)
{
    char String[40 + 1];

    dspStart();

    trc_fun = TRC_HandleGet();

    TRC_TRACE_INFO(trc_fun, "RESET TEST");

    TRC_TRACE_INFO(trc_fun, "SOFT RESET");
    tmrStart(1, 500);
    TPass_Reset(FALSE, TRUE);
    sprintf(String, "SOFT RESET %d ms", tmrGet(1));
    TRC_TRACE_INFO(trc_fun, String);
    TPass_FirstLine();
    TPass_Display(String);
    TPass_BacklightLevel(TPASS_BACKLIGHT_ON);
    tmrStop(1);
    ttestall(0, 3*100);

    TRC_TRACE_INFO(trc_fun, "HARD RESET");
    tmrStart(1, 500);
    TPass_Reset(TRUE, TRUE);
    sprintf(String, "HARD RESET %d ms", tmrGet(1));
    TRC_TRACE_INFO(trc_fun, String);
    TPass_FirstLine();
    TPass_Display(String);
    TPass_BacklightLevel(TPASS_BACKLIGHT_ON);
    tmrStop(1);

    dspStop();
}

void FUN_BacklightTest(int test)
{
    int key;
    int backlight;
    int changeBacklight;

    dspStart();
    kbdStart(1);

   trc_fun = TRC_HandleGet();

    TRC_TRACE_INFO(trc_fun, "BACKLIGHT TEST %d", test);
    backlight = 0;
    changeBacklight = 0;
    while (1)
    {
        if (backlight)
        {
            TPass_FirstLine();
            TPass_Display("\n\nBACKLIGHT\nON");
            TRC_TRACE_INFO(trc_fun, "BACKLIGHT ON");
            
            if (test == 0)
            {
                TPass_BacklightLevel(TPASS_BACKLIGHT_ON);
            }
            else
            {
                TPass_BacklightFadeToLevel(TPASS_BACKLIGHT_ON, TPASS_BACKLIGHT_DEFAULT_FADE_RAMP / 2);
            }
        }
        else
        {
            TPass_FirstLine();
            TPass_Display("\n\nBACKLIGHT\nOFF");
            TRC_TRACE_INFO(trc_fun, "BACKLIGHT OFF");
            
            if (test == 0)
            {
                TPass_BacklightLevel(TPASS_BACKLIGHT_OFF);
            }
            else
            {
                TPass_BacklightFadeToLevel(TPASS_BACKLIGHT_OFF, TPASS_BACKLIGHT_DEFAULT_FADE_RAMP / 2);
            }
        }
        
        key = kbdKey();
        if (key == T_ANN)
        {
            break;
        }
        ttestall(0, 2*100);
        
        // Change backlight every 2 loops
        if (changeBacklight)
            backlight = !backlight;
        
        changeBacklight = !changeBacklight;
    }

    kbdStop();
    dspStop();
}

void FUN_LedsTest(int test)
{
    int idx;
    int key;

    dspStart();
    kbdStart(1);

    trc_fun = TRC_HandleGet();

    TRC_TRACE_INFO(trc_fun, "LEDS TEST %d", test);
    if (test == 1)
    {
        TPass_LedsOn(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
    }
    else
    {
        TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
    }

    idx = 0;
    while (1)
    {
        switch (test)
        {
            case 0:
                TPass_FirstLine();
                switch(idx)
                {
                    case 0:
                        TRC_TRACE_INFO(trc_fun, "X - - -");
                        TPass_Display("\n\nLEDS TEST\n\nX - - -");
                        TPass_LedsOn(TPASS_LED_1);
                        TPass_LedsOff(TPASS_LED_4);
                        break;
                    case 1:
                        TRC_TRACE_INFO(trc_fun, "- X - - -");
                        TPass_Display("\n\nLEDS TEST\n\n- X - -");
                        TPass_LedsOn(TPASS_LED_2);
                        TPass_LedsOff(TPASS_LED_1);
                        break;
                    case 2:
                        TRC_TRACE_INFO(trc_fun, "- - X -");
                        TPass_Display("\n\nLEDS TEST\n\n- - X -");
                        TPass_LedsOn(TPASS_LED_3);
                        TPass_LedsOff(TPASS_LED_2);
                        break;
                    case 3:
                        TRC_TRACE_INFO(trc_fun, "- - - X");
                        TPass_Display("\n\nLEDS TEST\n\n- - - X");
                        TPass_LedsOn(TPASS_LED_4);
                        TPass_LedsOff(TPASS_LED_3);
                        break;
                    default:
                        break;
                }
                break;

            case 1:
                TPass_FirstLine();
                switch(idx)
                {
                    case 0:
                        TRC_TRACE_INFO(trc_fun, "- X X X");
                        TPass_Display("\n\nLEDS TEST\n\n- X X X");
                        TPass_LedsOff(TPASS_LED_1);
                        TPass_LedsOn(TPASS_LED_4);
                        break;
                    case 1:
                        TRC_TRACE_INFO(trc_fun, "X - X X");
                        TPass_Display("\n\nLEDS TEST\n\nX - X X");
                        TPass_LedsOff(TPASS_LED_2);
                        TPass_LedsOn(TPASS_LED_1);
                        break;
                    case 2:
                        TRC_TRACE_INFO(trc_fun, "X X - X");
                        TPass_Display("\n\nLEDS TEST\n\nX X - X");
                        TPass_LedsOff(TPASS_LED_3);
                        TPass_LedsOn(TPASS_LED_2);
                        break;
                    case 3:
                        TRC_TRACE_INFO(trc_fun, "X X X -");
                        TPass_Display("\n\nLEDS TEST\n\nX X X -");
                        TPass_LedsOff(TPASS_LED_4);
                        TPass_LedsOn(TPASS_LED_3);
                        break;
                    default:
                        break;
                }
                break;

            default:
                TPass_FirstLine();
                if ((idx % 2) == 0)
                {
                    TPass_Display("\n\nLEDS TEST\n\nCHENILLARD");
                    TRC_TRACE_INFO(trc_fun, "LEDS TEST - CHENILLARD");
                    TPass_LedsBlink(TPASS_LED_1, 1 * C30_CHENILLARD_TIME, 4 * C30_CHENILLARD_TIME);
                    TPass_LedsBlink(TPASS_LED_2, 2 * C30_CHENILLARD_TIME, 3 * C30_CHENILLARD_TIME);
                    TPass_LedsBlink(TPASS_LED_3, 3 * C30_CHENILLARD_TIME, 2 * C30_CHENILLARD_TIME);
                    TPass_LedsBlink(TPASS_LED_4, 4 * C30_CHENILLARD_TIME, 1 * C30_CHENILLARD_TIME);
                }
                else
                {
                    TPass_Display("\n\nLEDS TEST\n\nBLINK");
                    TRC_TRACE_INFO(trc_fun, "LEDS TEST - BLINK");
                    TPass_LedsBlink(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4, 25, 25);
                }
                break;
        }

        key = kbdKey();
        if (key == T_ANN)
        {
            break;
        }
        idx++;
        if (idx > 3)
            idx = 0;
        ttestall(0, 3*100);
    }

    kbdStop();
    dspStop();
}

void FUN_BuzzerTest(int test)
{
    int key;
    char String[40 + 1];
    int frequency;
    int vol;
    int dly;
    
    dspStart();
    kbdStart(1);

    trc_fun = TRC_HandleGet();

    TRC_TRACE_INFO(trc_fun, "BUZZER TEST %d", test);
    switch (test)
    {
        case 0:
            frequency = 20;
            vol = 32;
            dly = 2;
            break;

        case 1:
            frequency = 3000;
            vol = 0;
            dly = 2;
            break;

        default:
            frequency = 3000;
            vol = 32;
            dly = 2;
            break;
    }

    TRC_TRACE_INFO(trc_fun, "frequency = %d", frequency);
    TRC_TRACE_INFO(trc_fun, "volume = %d", vol);
    TRC_TRACE_INFO(trc_fun, "delay = %d", dly);

    while (1)
    {
        if (test == 0)
        {
            TPass_FirstLine();
            sprintf(String, "\n\nBUZZER TEST\n\nFreq = %d Hz", frequency);
            TPass_Display(String);
            TPass_Buzzer(0, 0);
            ttestall(0, 10);
            TPass_Buzzer(frequency, (unsigned char)vol);
            
            if (frequency < 100)
            frequency += 10;
            else if (frequency < 1000)
            frequency += 100;
            else if (frequency < 10000)
            frequency += 1000;
            else frequency = 20;
        }
        else if (test == 1)
        {
            TPass_FirstLine();
            sprintf(String, "\n\nBUZZER TEST\n\nVol = %d", vol);
            TPass_Display(String);
            TPass_Buzzer(0, 0);
            TPass_Buzzer(frequency, (unsigned char)vol);
            
            vol += 16;
            if (vol > 255)
            {
                vol = 0;
            }
        }
        else
        {
            TPass_FirstLine();
            sprintf(String, "\n\nBUZZER TEST\n\nDelay = %d ms", dly * 10);
            TPass_Display(String);
            TPass_BuzzerBeep(frequency, (unsigned char)vol, dly);

            if (dly < 10)
            {
                dly += 2;
            }
            else if (dly < 50)
            {
                dly += 10;
            }
            else if (dly < 100)
            {
                dly += 50;
            }
            else
            {
                dly = 2;
            }
        }
        
        key = kbdKey();
        if (key == T_ANN)
        {
            break;
        }
        ttestall(0, 1*100);
    }
    
    TPass_Buzzer(0, 0);

    kbdStop();
    dspStop();
}

void FUN_DisplayTest(int test)
{
    int idx;
    int key;

    dspStart();
    kbdStart(1);

    trc_fun = TRC_HandleGet();

    TRC_TRACE_INFO(trc_fun, "DISPLAY TEST %d", test);
    idx = 0;
    while (1)
    {
        if (test == 0)
        {
            switch(idx)
            {
                case 0:
                    TRC_TRACE_INFO(trc_fun, "DISPLAY TEST Init");
                    TPass_FirstLine();
                    TPass_Display("##################\n##################\n"
                        "##################\n##################\n"
                        "##################\n##################\n"
                        "##################\n##################\n");
                   break;

                case 1:
                    TRC_TRACE_INFO(trc_fun, "DISPLAY TEST First Line");
                    TPass_FirstLine();
                    break;
                case 2:
                    TRC_TRACE_INFO(trc_fun, "DISPLAY TEST Display Line 1");
                    TPass_Display("Line1\n");
                    break;
                case 3:
                    TRC_TRACE_INFO(trc_fun, "DISPLAY TEST Display Line 2");
                    TPass_Display("Line2");
                    break;
                case 4:
                    TRC_TRACE_INFO(trc_fun, "DISPLAY TEST Clear Line");
                    TPass_ClearLine();
                    break;
                case 5:
                    TRC_TRACE_INFO(trc_fun, "DISPLAY TEST Display Line 2");
                    TPass_Display("Line2\n");
                    break;
                case 6:
                    TRC_TRACE_INFO(trc_fun, "DISPLAY TEST Display Line 3");
                    TPass_Display("Line3\n");
                    break;
            }
            
            idx++;
            if (idx > 6)
            {
                idx = 0;
            }
        }
        else if (test == 1)
        {
            TRC_TRACE_INFO(trc_fun, "DISPLAY TEST Display XY");
            TPass_FirstLine();
            TPass_DisplayXY(0, 0, "TL");
            TPass_DisplayXY(16, 0, "TR");
            TPass_DisplayXY(0, 7, "BL");
            TPass_DisplayXY(16, 7, "BR");
            TPass_DisplayXY(6, 3, "CENTER");
        }
        
        key = kbdKey();
        if (key == T_ANN)
        {
            break;
        }
        ttestall(0, 3*100);
    }

    kbdStop();
    dspStop();
}

#ifdef __cplusplus
}
#endif
