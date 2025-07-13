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
   
 Project : Card Entry Sample
 Module  : UI - User Interface Unit

 @file      ui_menu.c
 @brief     Contains the definition of the menu of the application. It contains
            the callback functions called when menu items are selected in the
            menu.
            
 @date      30/04/2013

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
    _UI_MENU_ID_CARD_ENTRY,
    _UI_MENU_ID_END
}_UI_MenuID_t;

typedef struct
{
    _UI_MenuID_t id;
    char *caption;
    void (*callback)(void);
}_UI_Menu_Item_t;

typedef struct
{
    _UI_MenuID_t id;
    char *title;
    _UI_Menu_Item_t items[10];
}_UI_Menu_t;

static void _UI_MenuDisplay(_UI_MenuID_t ID);
static void _UI_MenuCB_TraceConfig(void);


_UI_Menu_t menuList[] = 
{
    {
        _UI_MENU_ID_CARD_ENTRY,
        "Card Entry Sample",
        {
            {
                _UI_MENU_ID_END,
                "Trace Output Stream",
                _UI_MenuCB_TraceConfig
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

static _UI_Menu_t *_UI_Menu_Get(_UI_MenuID_t ID)
{
    int ctr;
    _UI_Menu_t menu;
    
    memset(&menu, 0, sizeof(_UI_Menu_t));
    for(ctr = 0; ctr < sizeof(menuList)/sizeof(_UI_Menu_t) ; ctr++)
    {
        if (ID == menuList[ctr].id)
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

    if (menu == NULL)// TODO: Display undefined menu
        return;

    title = menu->title;
    memset(tmpList, 0, sizeof(tmpList));
    ctr = 0;
    while(1)
    {
        if (menu->items[ctr].caption == NULL)
        {
            break;
        }
        tmpList[ctr] = menu->items[ctr].caption;
        ctr++;
    }

    if (ctr == 0)
        return;

    while(1)
    {
        ret = guiMenu(mnuTypeDialog, sta, title, (const char**)tmpList);
        if (ret >= 0 && ret < ctr)
        {
            if (menu->items[ret].id < _UI_MENU_ID_END && menu->items[ret].id > _UI_MENU_ID_START)
            {
                _UI_MenuDisplay(menu->items[ret].id);
            }
            else
            if (menu->items[ret].callback != NULL)
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


void UI_MenuMainDisplay(void)
{

    UI_PeriphStart();// Open handles to peripherals.

    UI_IdleDispHdrFtrToggle();// Turn off the manager's header and footer.

    _UI_MenuDisplay(_UI_MENU_ID_CARD_ENTRY);

    UI_IdleDispHdrFtrToggle();// Restore the initial state of manager's header and footer
    
    UI_PeriphStop();// Close handles to peripherals.
}

#ifdef __cplusplus
}
#endif


