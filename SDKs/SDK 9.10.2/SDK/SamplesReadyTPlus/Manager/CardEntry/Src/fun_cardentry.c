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
 Module  : FUN - Demo Features Unit

 @file      fun_cardentry.c
 @brief     Contains all definitions of functions utilized for Card Entry.
 @date      02/14/2013

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "sdk30.h"
#include "bitmap.h"
#include "hterm.h"
#include "TPass.h"
#include "Cless_HighLevel.h"

#include "par.h"
#include "utilities.h"
#include "trace.h"
#include "err_process.h"
#include "fun_demofeatures.h"

static int _FUN_BWHeader(S_CUST_CARD_Entry *infoscust);
static int _FUN_CustCardEntryDisplay(S_CUST_CARD_Entry *infoscust);
static int _FUN_CustAmountDisplay(S_CUST_CARD_Entry *infoscust);
static int _FUN_CheckBitmap(S_CUST_CARD_Entry *infoscust);
static int _FUN_TpassBitmap(S_CUST_CARD_Entry *infoscust);
static int _FUN_CheckCless(S_CUST_CARD_Entry *infoscust);
static void _FUN_PeriphDisplay(S_CUST_CARD_Entry *infoscust);
static int _FUN_Pinpad2Lines(S_CUST_CARD_Entry *infoscust);
static int _FUN_PinpadGraphic(S_CUST_CARD_Entry *infoscust);
static void _FUN_PeriphPinpad(S_CUST_CARD_Entry *infoscust);
static int _FUN_PeriphC30(S_CUST_CARD_Entry *infoscust);
static unsigned short _FUN_DisplayScreen(void);

static unsigned char *amount;
static unsigned char buf_amount[51];
static unsigned char buf_currency[51];
static unsigned char buf_final[102];
static TRC_Trace_t trc_fun;

/** Checks if header display will be enabled for black and white terminals during custom card entry display
 *
 * \param[in] infoscust customized card entry data
 * 
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref Negative in case of error
 */
static int _FUN_BWHeader(S_CUST_CARD_Entry *infoscust)
{
    int ret;
    enum ebwHeader mode=0;

    ret = PAR_BwHeaderGet(&mode);
    if(mode==bwHeader_On)
    {
        TRC_TRACE_INFO(trc_fun, "BW Header Display Enabled");
        infoscust->fct_header((IsHeader()?1:(IsIWL220()?1:0)),infoscust->periph,infoscust->flag_cless,0);
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "BW Header Display Disabled");
    }

    return ret;
}

/** Modify card entry display message
 *
 * \param[in] infoscust customized card entry data
 * 
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref Negative in case of error
 */
static int _FUN_CustCardEntryDisplay(S_CUST_CARD_Entry *infoscust)
{
    int ret;
    enum ecardEntry mode=0;
    MSGinfos msg;

    ret = PAR_CardEntryGet(&mode);
    if(mode==cardEntry_On)
    {
        TRC_TRACE_INFO(trc_fun, "Custom Card Entry Display Enabled");
        if (GetGraphicMode()==PERIPH_DISPLAY_EXTENDED)
        {
            guiDrawText(37, 90, 10, 10, "MY MESSAGE");
        }
        else
        {
            guiDrawText(37, 86, 10, 10, "MY MESSAGE");
        }
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Custom Card Entry Display Disabled");
        GetMessageInfos(infoscust->MessWaitCard, &msg);
        if (GetGraphicMode()==PERIPH_DISPLAY_EXTENDED)
        {
            guiDrawText(37, 90, 10, 10, "MY MESSAGE");
        }
        else
        {
            guiDrawText(37, 86, 10, 10, "MY MESSAGE");
        }
        //removed manager display with custom GOAL display
        //infoscust->fct_mess(infoscust->MessWaitCard,infoscust->flag_cless,1);
    }

    return ret;
}

/** Checks if amount will be displayed on the custom card entry screen
 *
 * \param[in] infoscust customized card entry data
 * 
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref Negative in case of error
 */
static int _FUN_CustAmountDisplay(S_CUST_CARD_Entry *infoscust)
{
    int ret;
    enum eamountEntry mode=0;

    ret = PAR_AmountEntryGet(&mode);
    if(mode==amountEntry_On)
    {
        TRC_TRACE_INFO(trc_fun, "Custom Amount Entry Display Enabled");
        amount=(unsigned char *)&infoscust->amount;
        Amount_Format(amount,&infoscust->currency_infos.currency,SYMBOL_EURO,buf_final,buf_amount,buf_currency);
        if (GetGraphicMode()==PERIPH_DISPLAY_EXTENDED)
        {
            guiDrawText(40,5, 10, 10, (char *)buf_final);
        }
        else
        {
            guiDrawText(40,5, 15, 15, (char *)buf_final);
        }
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Custom Amount Entry Display Disabled");
        amount=(unsigned char *)&infoscust->amount;
        if (GetGraphicMode()==PERIPH_DISPLAY_EXTENDED)
        {
            infoscust->fct_amount(amount,&infoscust->currency_infos,infoscust->MessWaitCard,PERIPH_DISPLAY_EXTENDED,infoscust->flag_cless,0);
        }
        else
        {
           _FUN_BWHeader(infoscust);
            infoscust->fct_amount(amount,&infoscust->currency_infos,infoscust->MessWaitCard,PERIPH_DISPLAY,infoscust->flag_cless,0);
        }
    }

    return ret;
}

/** Checks if the check bitmap will be displayed on the custom card entry screen
 *
 * \param[in] infoscust customized card entry data
 * 
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref Negative in case of error
 */
static int _FUN_CheckBitmap(S_CUST_CARD_Entry *infoscust)
{
    int ret;
    enum echeckBmp mode=0;

    ret = PAR_CheckBmpGet(&mode);
    if(mode==checkBmp_On)
    {
        TRC_TRACE_INFO(trc_fun, "Check Bitmap Display Enabled");
        if(infoscust->flag_check)
        {
            infoscust->fct_check();
        }
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Check Bitmap Display Disabled");
    }

    return ret;
}

/** Checks if the tpass bitmap will be displayed on the custom card entry screen
 *
 * \param[in] infoscust customized card entry data
 * 
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref Negative in case of error
 */
static int _FUN_TpassBitmap(S_CUST_CARD_Entry *infoscust)
{
    int ret;
    enum etpassBmp mode=0;

    ret = PAR_TpassBmpGet(&mode);
    if(mode==tpassBmp_On)
    {
        TRC_TRACE_INFO(trc_fun, "Tpass Bitmap Display Enabled");
        if(infoscust->flag_tpass)
        {
            infoscust->fct_tpass();
        }
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Tpass Bitmap Display Disabled");
    }

    return ret;
}

/** Checks if terminal supports cless transactions.
 * If it supports cless transactions it will be displayed on the custom card entry screen
 *
 * \param[in] infoscust customized card entry data
 * 
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref Negative in case of error
 */
static int _FUN_CheckCless(S_CUST_CARD_Entry *infoscust)
{
    int ret;
    int x=0, y=0;
    enum eclessSupport mode=0;

    ret = PAR_ClessSupportGet(&mode);
    if(mode==clessSupport_On)
    {
        TRC_TRACE_INFO(trc_fun, "Custom Cless Logo Enabled");
        TPass_GetFieldCenterCoords(&x, &y);
        if ((x<0) && (y<0))
        {
            guiScreenSize(&x, &y);
            x = x/2; //obtain center coords from width
            y = y/2; //obtain center coords from height
        }

        //image is 160x180 pixels
        x = x-80; //subtract half of the width of the image
        y = y-90; //subtract half of the height of the image

        guiDrawImage(x, y, "file://flash/HOST/logocless.wgu");
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Custom Cless Logo Disabled");
        if(infoscust->flag_cless)
        {
            infoscust->fct_cless();
        }
    }

    return ret;
}

/** Custom card entry display for terminals
 *
 * \param[in] infoscust customized card entry data
 */
static void _FUN_PeriphDisplay(S_CUST_CARD_Entry *infoscust)
{
     _FUN_CustCardEntryDisplay(infoscust);
    _FUN_CustAmountDisplay(infoscust);
    _FUN_CheckBitmap(infoscust);
    _FUN_TpassBitmap(infoscust);
    _FUN_CheckCless(infoscust);
}

/** Custom card entry display for pinpads with 2 lines
 *
 * \param[in] infoscust customized card entry data
 * 
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref Negative in case of error
 */
static int _FUN_Pinpad2Lines(S_CUST_CARD_Entry *infoscust)
{
    int ret;
    enum epp2Lines mode=0;

    ret = PAR_Pp2LinesGet(&mode);
    if(mode==pp2Lines_On)
    {
        TRC_TRACE_INFO(trc_fun, "Pinpad 2 Lines Support Enabled");
        memset(buf_final, 0, sizeof(buf_final));
        amount=(unsigned char *)&infoscust->amount;
        Amount_Format(amount,&infoscust->currency_infos.currency,SYMBOL_EURO,buf_final,buf_amount,buf_currency);
        
        PPS_firstline();
        send_message_pinpad ((char *)buf_final );
        
        PPS_newline();
        send_message_pinpad ( "MY MESSAGE" );
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Pinpad 2 Lines Support Disabled");
        amount=(unsigned char *)&infoscust->amount;
        infoscust->fct_pinpad2lines(amount,&infoscust->currency_infos.currency,infoscust->MessWaitCard);
    }

    return ret;
}

/** Custom card entry display for pinpads that supports graphics
 *
 * \param[in] infoscust customized card entry data
 * 
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref Negative in case of error
 */
static int _FUN_PinpadGraphic(S_CUST_CARD_Entry *infoscust)
{
    int ret;
    enum eppGraphic mode=0;

    ret = PAR_PpGraphicGet(&mode);
    if(mode==ppGraphic_On)
    {
        TRC_TRACE_INFO(trc_fun, "Pinpad Graphic Support Enabled");
        infoscust->fct_header(0,infoscust->periph,infoscust->flag_cless,0);
        amount=(unsigned char *)&infoscust->amount;
        
        _DrawExtendedString(30,25,"MY MESSAGE",OFF,_MEDIUM_,_PROP_WIDTH_);
        
        Amount_Format(amount,&infoscust->currency_infos.currency,SYMBOL_EURO,buf_final,buf_amount,buf_currency);
        DrawExtendedString(30,15,(char *)buf_final,OFF,_SMALL_,_PROP_WIDTH_);
        
        // TODO: GOAL graphic display if cless is supported
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Pinpad Graphic Support Disabled");
        infoscust->fct_header(0,infoscust->periph,infoscust->flag_cless,0);
        amount=(unsigned char *)&infoscust->amount;
        infoscust->fct_amount(amount,&infoscust->currency_infos,infoscust->MessWaitCard,infoscust->periph,infoscust->flag_cless,0);
        infoscust->fct_mess(infoscust->MessWaitCard,infoscust->flag_cless,1);
        if(infoscust->flag_cless)
        infoscust->fct_cless();
    }

    return ret;
}

/** Custom card entry display for pinpad
 *
 * \param[in] infoscust customized card entry data
 */
static void _FUN_PeriphPinpad(S_CUST_CARD_Entry *infoscust)
{
     if (PSQ_Est_pinpad() && !PSQ_est_pinpad_graphique())
     {
        _FUN_Pinpad2Lines(infoscust);
     }
     else
     {
        _clrscr();
        _FUN_PinpadGraphic(infoscust);
     }
}

/** Custom card entry display for telium pass and vending pass
 *
 * \param[in] infoscust customized card entry data
 * 
 * \return
 *      -   \ref 1 if ok.
 *      -   \ref Negative in case of error
 */
static int _FUN_PeriphC30(S_CUST_CARD_Entry *infoscust)
{
    int ret;
    enum ec30 mode=0;

    ret = PAR_C30Get(&mode);
    if(mode==c30_On)
    {
        TRC_TRACE_INFO(trc_fun, "Vending Pass/Telium Pass Support Enabled");
         amount=(unsigned char *)&infoscust->amount;
         _DrawExtendedString(30,25,"MY MESSAGE",OFF,_MEDIUM_,_PROP_WIDTH_);
         Amount_Format(amount,&infoscust->currency_infos.currency,SYMBOL_EURO,buf_final,buf_amount,buf_currency);
         DrawExtendedString(30,15,(char *)buf_final,OFF,_SMALL_,_PROP_WIDTH_);
    }
    else
    {
        TRC_TRACE_INFO(trc_fun, "Vending Pass/Telium Pass Support Disabled");
        infoscust->fct_header(0,infoscust->periph,infoscust->flag_cless,0);
        amount=(unsigned char *)&infoscust->amount;
        infoscust->fct_amount(amount,&infoscust->currency_infos,infoscust->MessWaitCard,infoscust->periph,infoscust->flag_cless,0);
        infoscust->fct_mess(infoscust->MessWaitCard,infoscust->flag_cless,1);
    }
    

    return ret;
}

static unsigned short _FUN_DisplayScreen(void)
{
    trc_fun = TRC_HandleGet();

    guiDrawDisplay();
    return 0;
}

void FUN_ServiceCardEntry(int size, S_CUST_CARD_Entry *infoscust)
{
    int ret;
    enum eperiph periph=0;
    FILE *handle;

    handle = fopen("DISPLAY","w");

    trc_fun = TRC_HandleGet();

    TRC_TRACE_INFO(trc_fun, "SVC CALL: CUSTOMIZE_CARD_ENTRY");
    ret = PAR_PeriphGet(&periph);
    if (ret==PAR_OK)
    {
        switch (periph)
        {
            case PERIPH_DISPLAY:
                TRC_TRACE_INFO(trc_fun, "OUTPUT DISPLAY: PERIPH_DISPLAY");
                guiDrawCreate();
                _FUN_PeriphDisplay(infoscust);
                /*
                _FUN_DisplayScreen uses GOAL display GL_Window_Dispatch instead of GL_Window_MainLoop
                because GL_Window_MainLoop waits for a GOAL event and thus the handle will not be returned to the manager
                until the GOAL window is destroyed so card detection/keyboard events will not be performed. 
                On the other hand GL_Window_Dispatch just refreshes the window displayed 
                so manager card detection/keyboard events are performed in parallel.
                */
                _FUN_DisplayScreen();
                break;

            case PERIPH_PPR:
                TRC_TRACE_INFO(trc_fun, "OUTPUT DISPLAY: PERIPH_PPR");
                InitContexteGraphique(PERIPH_PPR);
                _FUN_PeriphPinpad(infoscust);
                InitContexteGraphique(PERIPH_DISPLAY);
                break;

            case PERIPH_C30:
                TRC_TRACE_INFO(trc_fun, "OUTPUT DISPLAY: PERIPH_C30");
                InitContexteGraphique(PERIPH_C30);
                _clrscr();
                _FUN_PeriphC30(infoscust);
                InitContexteGraphique(PERIPH_DISPLAY);
                break;

            default:
                TRC_TRACE_INFO(trc_fun, "OUTPUT DISPLAY: UNKNOWN PERIPHERAL");
                break;
        }
    }
    else
    {
        UI_ErrMsgDisplay(ERR_PAR_FILE_NOT_FOUND);
    }

    fclose(handle); 
}

#ifdef __cplusplus
}
#endif

