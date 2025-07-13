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
   
 Project : Mifare Sample
 Module  : UI - User Interface Unit

 @file      ui_display.c
 @brief     Contains definitions of APIs specific to display peripheral
            operations.
            
 @date      21/03/2013

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "SDK30.H"
#include <GL_GraphicLib.h>

#include "Utilities.h"

#include "err_process.h"
#include "ui_userinterface.h"
#include "fun_demofeatures.h"
#include "ui_prompt.h"

int UI_PeriphStart( void )
{
    int ret = 0;
    
    dspStart();
    kbdStart(1);
    tftStart();

    return ret;
}

int UI_PeriphStop( void )
{
    int ret = 0;
    
    tftStop();
    kbdStop();
    dspStop();

    return ret;
}


void UI_IdleDispHdrFtrToggle( void )
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

void UI_ErrMsgDisplay(int errID)
{
    ERR_Prompt_t *error = NULL;
    UI_PromptIdx_t promptID;

    error = ERR_PromptElemGet(errID);
    promptID = ERR_PromptIDGet(error);
    UI_PromptDisplay(promptID);
}

void UI_PromptMsgDisplay(UI_PromptIdx_t promptID)
{
    UI_PromptDisplay(promptID);
}

#ifdef __cplusplus
}
#endif


