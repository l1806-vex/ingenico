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
            
 @date      13/03/2013

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
    _UI_MENU_ID_DLL_SEC,
    _UI_MENU_ID_DLL_SEC_TEST,
    _UI_MENU_ID_DLL_SEC_PIN_ENTRY,
    _UI_MENU_ID_DLL_SEC_DATA_CIPHERING,
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
    _UI_Menu_Item_t items[10];
}_UI_Menu_t;

static void _UI_MenuDisplay(_UI_MenuID_t ID);
static void _UI_MenuCB_TraceConfig(void);
static void _UI_MenuCB_SetConfig(void);
static void _UI_MenuCB_ListSecretAreaPinEntry(void);
static void _UI_MenuCB_ListSecretAreaCiphering(void);
static void _UI_MenuCB_CreateSecretAreaPinEntry(void);
static void _UI_MenuCB_CreateSecretAreaCiphering(void);
static void _UI_MenuCB_FreeSecretAreaPinEntry(void);
static void _UI_MenuCB_FreeSecretAreaCiphering(void);
static void _UI_MenuCB_LoadRootKeyPinEntry(void);
static void _UI_MenuCB_LoadRootKeyCiphering(void);
static void _UI_MenuCB_LoadPinKey(void);
static void _UI_MenuCB_LoadMacKey(void);
static void _UI_MenuCB_PinEntry(void);
static void _UI_MenuCB_EnciperPin(void);
static void _UI_MenuCB_MacCalculation(void);

_UI_Menu_t menuList[] = 
{
    {
        _UI_MENU_ID_DLL_SEC,
        "Dll Security Sample",
        {
            {
                _UI_MENU_ID_END,
                "Trace Config",
                _UI_MenuCB_TraceConfig
            },
            {
                _UI_MENU_ID_DLL_SEC_TEST,
                "Dll Security Tests",
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
        _UI_MENU_ID_DLL_SEC_TEST,
        "Dll Security Tests",
        {
            {
                _UI_MENU_ID_END,
                "Configuration",
                _UI_MenuCB_SetConfig
            },
            {
                _UI_MENU_ID_DLL_SEC_PIN_ENTRY,
                "Pin Entry",
                0
            },
            {
                _UI_MENU_ID_DLL_SEC_DATA_CIPHERING,
                "Data Ciphering",
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
        _UI_MENU_ID_DLL_SEC_PIN_ENTRY,
        "Pin Entry",
        {
            {
                _UI_MENU_ID_END,
                "Create Secret Area",
                _UI_MenuCB_CreateSecretAreaPinEntry
            },
            {
                _UI_MENU_ID_END,
                "List Secret Area",
                _UI_MenuCB_ListSecretAreaPinEntry
            },
            {
                _UI_MENU_ID_END,
                "Load Root Key",
                _UI_MenuCB_LoadRootKeyPinEntry
            },
            {
                _UI_MENU_ID_END,
                "Load PIN Key",
                _UI_MenuCB_LoadPinKey
            },
            {
                _UI_MENU_ID_END,
                "PIN Entry",
                _UI_MenuCB_PinEntry
            },
            {
                _UI_MENU_ID_END,
                "Encipher Pin",
                _UI_MenuCB_EnciperPin
            },
            {
                _UI_MENU_ID_END,
                "Delete PIN Key",
                _UI_MenuCB_FreeSecretAreaPinEntry
            },
            {
                _UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        _UI_MENU_ID_DLL_SEC_DATA_CIPHERING,
        "Data Ciphering",
        {
            {
                _UI_MENU_ID_END,
                "Create Secret Area",
                _UI_MenuCB_CreateSecretAreaCiphering
            },
            {
                _UI_MENU_ID_END,
                "List Secret Area",
                _UI_MenuCB_ListSecretAreaCiphering
            },
            {
                _UI_MENU_ID_END,
                "Load Root Key",
                _UI_MenuCB_LoadRootKeyCiphering
            },
            {
                _UI_MENU_ID_END,
                "Load MAC Key",
                _UI_MenuCB_LoadMacKey
            },
            {
                _UI_MENU_ID_END,
                "MAC Calculation",
                _UI_MenuCB_MacCalculation
            },
            {
                _UI_MENU_ID_END,
                "Delete MAC Key",
                _UI_MenuCB_FreeSecretAreaCiphering
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

static void _UI_DisplayTestResult(int ret)
{
    if (ret==OK)
    {
        UI_PromptMsgDisplay(UI_PROMPT_MSG_TEST_OK);
    }
    else
    {
        UI_PromptMsgDisplay(UI_PROMPT_MSG_TEST_FAILED);
    }
}

static void _UI_MenuCB_TraceConfig(void)
{
    FLOW_ParamConfigTraceProcess();
    return;
}

static void _UI_MenuCB_SetConfig(void)
{
    int ret;

    ret = FUN_SetConfig();
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_ListSecretAreaPinEntry(void)
{
    int ret;

    ret = FUN_ListSecretArea(0);
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_ListSecretAreaCiphering(void)
{
    int ret;

    ret = FUN_ListSecretArea(2);
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_CreateSecretAreaPinEntry(void)
{
    int ret;

    ret = FUN_CreateSecretArea(0);
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_CreateSecretAreaCiphering(void)
{
    int ret;

    ret = FUN_CreateSecretArea(2);
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_FreeSecretAreaPinEntry(void)
{
    int ret;

    ret = FUN_FreeSecretArea(0);
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_FreeSecretAreaCiphering(void)
{
    int ret;

    ret = FUN_FreeSecretArea(2);
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_LoadRootKeyPinEntry(void)
{
    int ret;

    ret = FUN_LoadRootKey(0);
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_LoadRootKeyCiphering(void)
{
    int ret;

    ret = FUN_LoadRootKey(2);
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_LoadPinKey(void)
{
    int ret;

    ret = FUN_LoadPinKey();
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_LoadMacKey(void)
{
    int ret;

    ret = FUN_LoadMacKey();
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_PinEntry(void)
{
    int ret;

    ret = FUN_PinEntry();
    _UI_DisplayTestResult(ret);
    return;
}

static void _UI_MenuCB_EnciperPin(void)
{
    int ret;

    ret = FUN_EncipherPin();
    _UI_DisplayTestResult(ret);
    return;
}
static void _UI_MenuCB_MacCalculation(void)
{
    int ret;

    ret = FUN_MacCalculation();
    _UI_DisplayTestResult(ret);
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
    char *tmpList[10];
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

    _UI_MenuDisplay(_UI_MENU_ID_DLL_SEC);

    UI_IdleDispHdrFtrToggle();// Restore the initial state of manager's header and footer
    
    UI_PeriphStop();// Close handles to peripherals.
}

#ifdef __cplusplus
}
#endif


