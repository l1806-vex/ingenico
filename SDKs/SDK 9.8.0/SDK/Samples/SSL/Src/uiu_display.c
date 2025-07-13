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

 @file      uiu_display.c
 @brief     Contains definitions of APIs specific to display peripheral
            operations.
            
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "SDK30.H"
#include <GL_GraphicLib.h>

#include "Utilities.h"

#include "pmu_parammngt.h"
#include "epu_errprocess.h"
#include "uiu_userinterface.h"
#include "phu_processhdl.h"
#include "dfu_demofeatures.h"
#include "uiu_prompt.h"

int UIU_PeriphStart( void )
{
    int ret = 0;
    
    dspStart();
    kbdStart(1);
    tftStart();

    return ret;
}

int UIU_PeriphStop( void )
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

void UIU_ErrMsgDisplay(int errID)
{
    EPU_Error_t *error = NULL;
    UIU_PromptIdx_t promptID;

    error = EPU_ErrPromptElemGet(errID);
    promptID = EPU_ErrPromptIDGet(error);
    UIU_PromptDisplay(promptID);
}

void UIU_PromptMsgDisplay(UIU_PromptIdx_t promptID)
{
    UIU_PromptDisplay(promptID);
}

#ifdef __cplusplus
}
#endif


