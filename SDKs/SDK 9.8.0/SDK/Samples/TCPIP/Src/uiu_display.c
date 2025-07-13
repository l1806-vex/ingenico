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
   
 Project : TCP/IP Sample
 Module  : UIU - User Interface Unit

 @file      uiu_display.c
 @brief     Contains definitions of APIs specific to display peripheral
            operations.
            
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#include "SDK30.H"
#include <GL_GraphicLib.h>

#include "Utilities.h"

#include "pmu_parammngt.h"
#include "epu_errprocess.h"
#include "uiu_userinterface.h"
#include "phu_processhdl.h"
#include "dfu_demofeatures.h"
#include "uiu_prompt.h"

static int _UIU_PeriphStart( void )
{
    int ret = 0;
    
    dspStart();
    kbdStart(1);
    tftStart();

    return ret;
}

static int _UIU_PeriphStop( void )
{
    int ret = 0;
    
    tftStop();
    kbdStop();
    dspStop();

    return ret;
}


void UIU_IdleDispHdrFtrToggle( void )
{
    static int hdr = 0; // Holds initial manager's header state.
    static int ftr = 0; // Holds initial manager's footer state.

    static int callInstance = 0;

    if(callInstance == 0)
    {
        hdr = DisplayHeader(0);
        ftr = DisplayFooter(0);
        callInstance = 1;// Remembers that this function should be called again to restore the original state of header/footer display.
    }
    else
    {
        DisplayHeader(hdr);
        DisplayFooter(ftr);
        callInstance = 0;// Restart for the next call of this function to toggle the header and footer.
    }

}

void UIU_MenuDisplay(void)
{
    static int sta=0; // Holds current menu item selected in the menu list.
    int bContinue; 
    int ret;

    const char* menuList[] =
    {
        "Client Test Config",
        "Network Info",
        "HTTP Server",
        "HTTP Client",
        0
    };

    _UIU_PeriphStart();// Open handles to peripherals.

    UIU_IdleDispHdrFtrToggle();// Turn off the manager's header and footer.

    bContinue = 1;
    do
    {
        ret = guiMenu( mnuTypeDialog, sta, "SAMPLE TCP/IP", menuList );
        switch( ret )
        {
            case 0: // Setup parameters for client test.
                phuParamConfigProcess();
                break;
            case 1: // Display Ethernet Infos.
                phuTestNetInfoProcess();
                break;
            
            case 2: // Runs HTTP Server test.
                phuTestServerProcess();
                break;
            
            case 3: // Runs HTTP Client test.
                phuTestClientProcess();
                break;
            
            default:
                bContinue = 0;
                break;
        }
    } while( bContinue == 1 );

    
    UIU_IdleDispHdrFtrToggle();// Restore the initial state of manager's header and footer
    
    _UIU_PeriphStop();// Close handles to peripherals.
}

void UIU_ErrMsgDisplay(int errID)
{
    EPU_Error_t *error = NULL;
    UIU_PromptIdx_t promptID;

    error = EPU_ErrPromptElemGet(errID);
    promptID = EPU_ErrPromptIDGet(error);
    UIU_PromptDisplay(promptID);
}

