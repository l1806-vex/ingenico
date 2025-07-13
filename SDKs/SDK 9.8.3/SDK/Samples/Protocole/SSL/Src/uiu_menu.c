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
   
 Project : SSL Sample
 Module  : UIU - User Interface Unit

 @file      uiu_menu.c
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
#include "uiu_userinterface.h"
#include "phu_processhdl.h"
#include "dfu_demofeatures.h"

typedef enum
{
    _UIU_MENU_ID_START,
    _UIU_MENU_ID_SSL_SAMPLE,
    _UIU_MENU_ID_SSL_SAMPLE_SUB_GPRS,
    _UIU_MENU_ID_SSL_SAMPLE_SUB_SSL,
    _UIU_MENU_ID_SSL_SAMPLE_SUB_SSL_SUB_PROFILES,
    _UIU_MENU_ID_END
}_UIU_MenuID_t;

typedef struct
{
    _UIU_MenuID_t id;
    char *caption;
    void (*callback)( void );
}_UIU_Menu_Item_t;

typedef struct
{
    _UIU_MenuID_t id;
    char *title;
    _UIU_Menu_Item_t items[10];
}_UIU_Menu_t;

static void _UIU_MenuDisplay(_UIU_MenuID_t ID);
static void _UIU_MenuCB_ProfileAdd( void );
static void _UIU_MenuCB_ProfileList( void );
static void _UIU_MenuCB_SSLConnect( void );
static void _UIU_MenuCB_SSLConfig( void );
static void _UIU_MenuCB_ProfileDelete( void );


_UIU_Menu_t menuList[] = 
{
    {
        _UIU_MENU_ID_SSL_SAMPLE,
        "SSL Sample",
        {
            {
                _UIU_MENU_ID_SSL_SAMPLE_SUB_SSL_SUB_PROFILES,
                "Profiles",
                0
            },
            {
                _UIU_MENU_ID_END,
                "Connection",
                _UIU_MenuCB_SSLConnect
            },
            {
                _UIU_MENU_ID_END,
                "Config",
                _UIU_MenuCB_SSLConfig
            },
            {
                _UIU_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        _UIU_MENU_ID_SSL_SAMPLE_SUB_SSL_SUB_PROFILES,
        "Profiles",
        {
            {
                _UIU_MENU_ID_END,
                "Add",
                _UIU_MenuCB_ProfileAdd
            },
            {
                _UIU_MENU_ID_END,
                "Delete",
                _UIU_MenuCB_ProfileDelete
            },
            {
                _UIU_MENU_ID_END,
                "List",
                _UIU_MenuCB_ProfileList
            },
            {
                _UIU_MENU_ID_END,
                0,
                0
            }
        }
    },
    {
        _UIU_MENU_ID_END,
        0,
        {
            {
                _UIU_MENU_ID_END,
                0,
                0
            }
        }
    }
};

static void _UIU_MenuCB_ProfileAdd( void )
{
    DFU_SslProfileAdd();
}

static void _UIU_MenuCB_ProfileDelete ( void )
{
    PHU_SSLProfileDeleteProcess();
}

static void _UIU_MenuCB_ProfileList( void )
{
    DFU_SslProfileListPrint();
}

static void _UIU_MenuCB_SSLConnect( void )
{
    PHU_SslConnectionProcess();
}

static void _UIU_MenuCB_SSLConfig( void )
{
    PHU_ParamConfigSSLProcess();
}


static _UIU_Menu_t *_UIU_Menu_Get(_UIU_MenuID_t ID)
{
    int ctr;
    _UIU_Menu_t menu;
    
    memset(&menu, 0, sizeof(_UIU_Menu_t));
    for(ctr = 0; ctr < sizeof(menuList)/sizeof(_UIU_Menu_t) ; ctr++)
    {
        if(ID == menuList[ctr].id)
        {
            return &menuList[ctr];
        }
    }

    return NULL;
}

void _UIU_MenuDisplay(_UIU_MenuID_t ID)
{
    static int sta=0; // Holds current menu item selected in the menu list.
    int ret;
    int ctr;
    _UIU_Menu_t *menu = NULL;
    char *tmpList[10];
    char *title;
    
    menu = _UIU_Menu_Get(ID);

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
            if(menu->items[ret].id < _UIU_MENU_ID_END && menu->items[ret].id > _UIU_MENU_ID_START)
            {
                _UIU_MenuDisplay(menu->items[ret].id);
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


void UIU_MenuMainDisplay( void )
{

    UIU_PeriphStart();// Open handles to peripherals.

    UIU_IdleDispHdrFtrToggle();// Turn off the manager's header and footer.

    _UIU_MenuDisplay(_UIU_MENU_ID_SSL_SAMPLE);
    
    UIU_IdleDispHdrFtrToggle();// Restore the initial state of manager's header and footer
    
    UIU_PeriphStop();// Close handles to peripherals.
}

#ifdef __cplusplus
}
#endif


