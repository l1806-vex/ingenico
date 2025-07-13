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
 Module  : UI - User Interface Unit

 @file      ui_menu.c
 @brief     Contains the definition of the menu of the application. It contains
            the callback functions called when menu items are selected in the
            menu.
            
 @date      08/03/2013

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "sdk30.h"
#include "utilities.h"

#include "ui_userinterface.h"
#include "fun_demofeatures.h"
#include "flow.h"

typedef enum
{
    _UI_MENU_ID_START,
    _UI_MENU_ID_TPASS,
    _UI_MENU_ID_TPASS_TEST,
    _UI_MENU_ID_TPASS_BACKLIGHT,
    _UI_MENU_ID_TPASS_LEDS,
    _UI_MENU_ID_TPASS_BUZZER,
    _UI_MENU_ID_TPASS_DISPLAY,
    _UI_MENU_ID_TPASS_CLESS_ISO,
    _UI_MENU_ID_TPASS_CLESS_MIFARE,
    _UI_MENU_ID_END
}_UI_MenuID_t;

typedef struct
{
    _UI_MenuID_t id;
    char *caption;
    void (*callback)( void );
}_UI_Menu_Item_t;

typedef struct
{
    _UI_MenuID_t id;
    char *title;
    _UI_Menu_Item_t items[11];
}_UI_Menu_t;

static void _UI_MenuDisplay(_UI_MenuID_t ID);
static void _UI_MenuCB_TraceConfig(void);
static void _UI_MenuCB_CheckConnection(void);
static void _UI_MenuCB_Reset(void);
static void _UI_MenuCB_ReaderInfo(void);
static void _UI_MenuCB_BacklightSwitch(void);
static void _UI_MenuCB_BacklightFade(void);
static void _UI_MenuCB_LedsOn(void);
static void _UI_MenuCB_LedsOff(void);
static void _UI_MenuCB_LedsBlink(void);
static void _UI_MenuCB_BuzzerFrequency(void);
static void _UI_MenuCB_BuzzerVolume(void);
static void _UI_MenuCB_BuzzerBeep(void);
static void _UI_MenuCB_DisplayTest(void);
static void _UI_MenuCB_DisplayXY(void);
static void _UI_MenuCB_ClessIsoDetectTO(void);
static void _UI_MenuCB_ClessIsoSyncSync(void);
static void _UI_MenuCB_ClessIsoSyncAsync(void);
static void _UI_MenuCB_ClessIsoAsyncSync(void);
static void _UI_MenuCB_ClessIsoAsyncAsync(void);
static void _UI_MenuCB_ClessMifareDetectTO(void);
static void _UI_MenuCB_ClessMifareCredit(void);
static void _UI_MenuCB_ClessMifareDebit(void);
static void _UI_MenuCB_ClessMifareBalance(void);
static void _UI_MenuCB_ClessMifareResetPurse(void);

_UI_Menu_t menuList[] = 
{
    {
        _UI_MENU_ID_TPASS,
        "Telium Pass Sample",
        {
            {
                _UI_MENU_ID_END,
                "Trace Config",
                _UI_MenuCB_TraceConfig
            },
            {
                _UI_MENU_ID_TPASS_TEST,
                "Telium Pass Tests",
                0
            },
            {
                _UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        _UI_MENU_ID_TPASS_TEST,
        "Telium Pass Tests",
        {
            {
                _UI_MENU_ID_END,
                "Check Connection",
                _UI_MenuCB_CheckConnection
            },
            {
                _UI_MENU_ID_END,
                "Reset",
                _UI_MenuCB_Reset
            },
            {
                _UI_MENU_ID_END,
                "Reader Info",
                _UI_MenuCB_ReaderInfo
            },
            {
                _UI_MENU_ID_TPASS_BACKLIGHT,
                "Backlight",
                0
            },
            {
                _UI_MENU_ID_TPASS_LEDS,
                "Leds",
                0
            },
            {
                _UI_MENU_ID_TPASS_BUZZER,
                "Buzzer",
                0
            },
            {
                _UI_MENU_ID_TPASS_DISPLAY,
                "Display",
                0
            },
            {
                _UI_MENU_ID_TPASS_CLESS_ISO,
                "Cless Iso",
                0
            },
            {
                _UI_MENU_ID_TPASS_CLESS_MIFARE,
                "Cless Mifare",
                0
            },
            {
                _UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        _UI_MENU_ID_TPASS_BACKLIGHT,
        "Backlight",
        {
            {
                _UI_MENU_ID_END,
                "On/Off",
                _UI_MenuCB_BacklightSwitch
            },
            {
                _UI_MENU_ID_END,
                "Fading",
                _UI_MenuCB_BacklightFade
            },
            {
                _UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        _UI_MENU_ID_TPASS_LEDS,
        "Leds",
        {
            {
                _UI_MENU_ID_END,
                "On",
                _UI_MenuCB_LedsOn
            },
            {
                _UI_MENU_ID_END,
                "Off",
                _UI_MenuCB_LedsOff
            },
            {
                _UI_MENU_ID_END,
                "Blink",
                _UI_MenuCB_LedsBlink
            },
            {
                _UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        _UI_MENU_ID_TPASS_BUZZER,
        "Buzzer",
        {
            {
                _UI_MENU_ID_END,
                "Frequency",
                _UI_MenuCB_BuzzerFrequency
            },
            {
                _UI_MENU_ID_END,
                "Volume",
                _UI_MenuCB_BuzzerVolume
            },
            {
                _UI_MENU_ID_END,
                "Beep",
                _UI_MenuCB_BuzzerBeep
            },
            {
                _UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        _UI_MENU_ID_TPASS_DISPLAY,
        "Display",
        {
            {
                _UI_MENU_ID_END,
                "Display Test",
                _UI_MenuCB_DisplayTest
            },
            {
                _UI_MENU_ID_END,
                "Display XY",
                _UI_MenuCB_DisplayXY
            },
            {
                _UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        _UI_MENU_ID_TPASS_CLESS_ISO,
        "Cless Iso",
        {
            {
                _UI_MENU_ID_END,
                "Detect TO",
                _UI_MenuCB_ClessIsoDetectTO
            },
            {
                _UI_MENU_ID_END,
                "Sync/Sync",
                _UI_MenuCB_ClessIsoSyncSync
            },
            {
                _UI_MENU_ID_END,
                "Sync/Async",
                _UI_MenuCB_ClessIsoSyncAsync
            },
            {
                _UI_MENU_ID_END,
                "Async/Sync",
                _UI_MenuCB_ClessIsoAsyncSync
            },
            {
                _UI_MENU_ID_END,
                "Async/Async",
                _UI_MenuCB_ClessIsoAsyncAsync
            },
            {
                _UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        _UI_MENU_ID_TPASS_CLESS_MIFARE,
        "Cless Mifare",
        {
            {
                _UI_MENU_ID_END,
                "Detect TO",
                _UI_MenuCB_ClessMifareDetectTO
            },
            {
                _UI_MENU_ID_END,
                "Credit",
                _UI_MenuCB_ClessMifareCredit
            },
            {
                _UI_MENU_ID_END,
                "Debit",
                _UI_MenuCB_ClessMifareDebit
            },
            {
                _UI_MENU_ID_END,
                "Balance",
                _UI_MenuCB_ClessMifareBalance
            },
            {
                _UI_MENU_ID_END,
                "Reset Purse",
                _UI_MenuCB_ClessMifareResetPurse
            },
            {
                _UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        _UI_MENU_ID_END,
        0,
        {
            {
                _UI_MENU_ID_END,
                0,
                0
            }
        }
    }
};

static void _UI_MenuCB_TraceConfig(void)
{
    FLOW_ParamConfigTraceProcess();
    return;
}

static void _UI_MenuCB_CheckConnection(void)
{
    FUN_CheckPresence();
    return;
}

static void _UI_MenuCB_Reset(void)
{
    FUN_ResetTest();
    return;
}

static void _UI_MenuCB_ReaderInfo(void)
{
    FUN_InfoTest();
    return;
}

static void _UI_MenuCB_BacklightSwitch(void)
{
    FUN_BacklightTest(0);
    return;
}

static void _UI_MenuCB_BacklightFade(void)
{
    FUN_BacklightTest(1);
    return;
}

static void _UI_MenuCB_LedsOn(void)
{
    FUN_LedsTest(0);
    return;
}

static void _UI_MenuCB_LedsOff(void)
{
    FUN_LedsTest(1);
    return;
}

static void _UI_MenuCB_LedsBlink(void)
{
    FUN_LedsTest(2);
    return;
}

static void _UI_MenuCB_BuzzerFrequency(void)
{
    FUN_BuzzerTest(0);
    return;
}

static void _UI_MenuCB_BuzzerVolume(void)
{
    FUN_BuzzerTest(1);
    return;
}

static void _UI_MenuCB_BuzzerBeep(void)
{
    FUN_BuzzerTest(2);
    return;
}

static void _UI_MenuCB_DisplayTest(void)
{
    FUN_DisplayTest(0);
    return;
}

static void _UI_MenuCB_DisplayXY(void)
{
    FUN_DisplayTest(1);
    return;
}

static void _UI_MenuCB_ClessIsoDetectTO(void)
{
    FUN_IsoTest(0);
    return;
}

static void _UI_MenuCB_ClessIsoSyncSync(void)
{
    FUN_IsoTest(1);
    return;
}

static void _UI_MenuCB_ClessIsoSyncAsync(void)
{
    FUN_IsoTest(2);
    return;
}

static void _UI_MenuCB_ClessIsoAsyncSync(void)
{
    FUN_IsoTest(3);
    return;
}

static void _UI_MenuCB_ClessIsoAsyncAsync(void)
{
    FUN_IsoTest(4);
    return;
}

static void _UI_MenuCB_ClessMifareDetectTO(void)
{
    FUN_MifareTest(0);
    return;
}

static void _UI_MenuCB_ClessMifareCredit(void)
{
    FUN_MifareTest(1);
    return;
}

static void _UI_MenuCB_ClessMifareDebit(void)
{
    FUN_MifareTest(2);
    return;
}

static void _UI_MenuCB_ClessMifareBalance(void)
{
    FUN_MifareTest(3);
    return;
}

static void _UI_MenuCB_ClessMifareResetPurse(void)
{
    FUN_MifareTest(4);
    return;
}

static _UI_Menu_t *_UI_Menu_Get(_UI_MenuID_t ID)
{
    int ctr;
    _UI_Menu_t menu;
    
    memset(&menu, 0, sizeof(_UI_Menu_t));
    for(ctr = 0; ctr < sizeof(menuList)/sizeof(_UI_Menu_t) ; ctr++)
    {
        if(ID == menuList[ctr].id)
        {
            return &menuList[ctr];
        }
    }

    return NULL;
}

void _UI_MenuDisplay(_UI_MenuID_t ID)
{
    static int sta=0; // Holds current menu item selected in the menu list.
    int ret;
    int ctr;
    _UI_Menu_t *menu = NULL;
    char *tmpList[11];
    char *title;
    
    menu = _UI_Menu_Get(ID);

    if(menu == NULL)// TODO: Display undefined menu
        return;

    title = menu->title;
    memset(tmpList, 0, sizeof(tmpList));
    ctr = 0;
    while(1)
    {
        if(menu->items[ctr].caption == NULL)
        {
            break;
        }
        tmpList[ctr] = menu->items[ctr].caption;
        ctr++;
    }

    if(ctr == 0)
        return;

    while(1)
    {
        ret = guiMenu( mnuTypeDialog, sta, title, (const char**)tmpList );
        if(ret >= 0 && ret < ctr)
        {
            if(menu->items[ret].id < _UI_MENU_ID_END && menu->items[ret].id > _UI_MENU_ID_START)
            {
                _UI_MenuDisplay(menu->items[ret].id);
            }
            else
            if(menu->items[ret].callback != NULL)
            {
                menu->items[ret].callback();
            }
        }
        else
        {
            break;
        }
    }

}


void UI_MenuMainDisplay( void )
{

    UI_PeriphStart();// Open handles to peripherals.

    UI_IdleDispHdrFtrToggle();// Turn off the manager's header and footer.

    _UI_MenuDisplay(_UI_MENU_ID_TPASS);

    UI_IdleDispHdrFtrToggle();// Restore the initial state of manager's header and footer
    
    UI_PeriphStop();// Close handles to peripherals.
}

#ifdef __cplusplus
}
#endif


