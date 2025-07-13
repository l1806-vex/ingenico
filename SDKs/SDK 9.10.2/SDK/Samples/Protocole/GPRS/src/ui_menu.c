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
   
 Project : GPRS Sample
 Module  : UI - User Interface Unit

 @file      ui_menu.c
 @brief     Contains the definition of the menu of the application. It contains
            the callback functions called when menu items are selected in the
            menu.
            
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "sdk30.h"
#include "utilities.h"
#include "ui.h"
#include "flow.h"
#include "fun.h"

typedef enum
{
    UI_MENU_ID_START,
    UI_MENU_ID_GPRS_SAMPLE,
    UI_MENU_ID_GPRS_SAMPLE_SUB_CONFIG,
    UI_MENU_ID_GPRS_SAMPLE_SUB_GPRS,
    UI_MENU_ID_GPRS_SAMPLE_SUB_PPP,
    UI_MENU_ID_END
}UI_MenuID_t;

typedef struct
{
    UI_MenuID_t id;
    char *caption;
    void (*callback)( void );
}UI_Menu_Item_t;

typedef struct
{
    UI_MenuID_t id;
    char *title;
    UI_Menu_Item_t items[10];
}UI_Menu_t;

static void _UI_MenuCB_GPRSConfig( void );
static void _UI_MenuCB_GPRSActivate( void );
static void _UI_MenuCB_GPRSDeactivate( void );
static void _UI_MenuCB_PPPConfig( void );
static void _UI_MenuCB_PPPConnect( void );
static void _UI_MenuCB_PPPDisconnect( void );
static void _UI_MenuCB_TCPConfig( void );
static void _UI_MenuCB_TCPTransceive( void );
static void _UI_MenuCB_GSMConfig( void );
static void _UI_MenuCB_GSMTest( void );

UI_Menu_t menuList[] = 
{
    {
        UI_MENU_ID_GPRS_SAMPLE,
        "GPRS Sample",
        {
            {
                UI_MENU_ID_GPRS_SAMPLE_SUB_GPRS,
                "GPRS",
                0
            },
            {
                UI_MENU_ID_GPRS_SAMPLE_SUB_PPP,
                "PPP",
                0
            },
            {
                UI_MENU_ID_END,
                "TCP/IP",
                _UI_MenuCB_TCPTransceive
            },
            {
                UI_MENU_ID_END,
                "GSM",
                _UI_MenuCB_GSMTest
            },
            {
                UI_MENU_ID_GPRS_SAMPLE_SUB_CONFIG,
                "Configuration",
                0
            },
            {
                UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        UI_MENU_ID_GPRS_SAMPLE_SUB_GPRS,
        "GPRS",
        {
            {
                UI_MENU_ID_END,
                "Activate",
                _UI_MenuCB_GPRSActivate
            },
            {
                UI_MENU_ID_END,
                "Deactivate",
                _UI_MenuCB_GPRSDeactivate
            },
            {
                UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        UI_MENU_ID_GPRS_SAMPLE_SUB_PPP,
        "PPP",
        {
            {
                UI_MENU_ID_END,
                "Connect",
                _UI_MenuCB_PPPConnect
            },
            {
                UI_MENU_ID_END,
                "Disconnect",
                _UI_MenuCB_PPPDisconnect
            },
            {
                UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        UI_MENU_ID_GPRS_SAMPLE_SUB_CONFIG,
        "Configuration",
        {
            {
                UI_MENU_ID_END,
                "GPRS",
                _UI_MenuCB_GPRSConfig
            },
            {
                UI_MENU_ID_END,
                "PPP",
                _UI_MenuCB_PPPConfig
            },
            {
                UI_MENU_ID_END,
                "TCP/IP",
                _UI_MenuCB_TCPConfig
            },
            {
                UI_MENU_ID_END,
                "GSM",
                _UI_MenuCB_GSMConfig
            },
            {
                UI_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        UI_MENU_ID_END,
        0,
        {
            {
                UI_MENU_ID_END,
                0,
                0
            }
        }
    }
};

static void _UI_MenuCB_GPRSConfig( void )
{
    FLOW_ParamConfigGprsProcess();
}

static void _UI_MenuCB_GPRSActivate( void )
{
    FLOW_GprsActivationProcess();
}

static void _UI_MenuCB_GPRSDeactivate( void )
{
    FLOW_GprsDeactivationProcess();
}

static void _UI_MenuCB_PPPConfig( void )
{
    FLOW_ParamConfigPppProcess();
}

static void _UI_MenuCB_PPPConnect( void )
{
    FLOW_PppConnectionProcess();
}

static void _UI_MenuCB_PPPDisconnect( void )
{
    FLOW_PppDisconnectionProcess();
}

static void _UI_MenuCB_TCPConfig( void )
{
    FLOW_ParamConfigTcpProcess();
}

static void _UI_MenuCB_TCPTransceive( void )
{
    FLOW_TcpTransceive();
}

static void _UI_MenuCB_GSMConfig( void )
{
    FLOW_ParamConfigGsmProcess();
}

static void _UI_MenuCB_GSMTest( void )
{
    FLOW_GsmConnectionProcess();
}

static UI_Menu_t *_UI_Menu_Get(UI_MenuID_t ID)
{
    int ctr;
    UI_Menu_t menu;
    
    memset(&menu, 0, sizeof(UI_Menu_t));
    for(ctr = 0; ctr < sizeof(menuList)/sizeof(UI_Menu_t) ; ctr++)
    {
        if(ID == menuList[ctr].id)
        {
            return &menuList[ctr];
        }
    }

    return NULL;
}

void _UI_MenuDisplay(UI_MenuID_t ID)
{
    static int sta=0; // Holds current menu item selected in the menu list.
    int ret;
    int ctr;
    UI_Menu_t *menu = NULL;
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
            if(menu->items[ret].id < UI_MENU_ID_END && menu->items[ret].id > UI_MENU_ID_START)
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

    _UI_MenuDisplay(UI_MENU_ID_GPRS_SAMPLE);
    
    UI_IdleDispHdrFtrToggle();// Restore the initial state of manager's header and footer
    
    UI_PeriphStop();// Close handles to peripherals.
}

#ifdef __cplusplus
}
#endif

