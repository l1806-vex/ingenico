/**
* \file cu_wgui.c
* \brief This module contains the functions needed for color management.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "MessagesDefinitions.h"
#include "sdk30.h"
#include "cu_mess.h"
#include "WGUI.h"
#include "Wgui_Services.h"
#include "cu_wgui.h"


/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */
// Constant to manage periodic fct call

#define C_USER_DELAY                  1


/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/
static word g_wCurrentCguiTask;
extern WGUI_CANVAS_HANDLE canvas;					/*!< Application CGUI canevas. */

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

char ilist_html[64] = "";
char list_html[64] = "";
char input_html[64] = "";

const char pin_html[] = "@tar:///param/844042----.tar/pin/PIN.HTML";
const char file_dir[] = "@tar:///param/844042----.tar/Icons/";
const char tag_pinask[] = "PINASK";
const char tag_pin[] = "PIN";
const char tag_pindesc[] = "PINDESC";

const char icon_debit[] = "CU_DEBIT.WGU";
const char icon_refund[] = "CU_REFUND.WGU";
const char icon_cash[] = "CU_CASH.WGU";
const char icon_cashback[] = "CU_CASHBACK.WGU";
const char icon_merchant[] = "CU_MERCHANT.WGU";
#ifdef _TOOLWARE_
const char icon_toolware[] = "CU_TOOLWARE.WGU";
#endif
const char icon_credit[] = "CU_CREDIT.WGU";

const char icon_batch_stat[] = "CU_BAT_STAT.WGU";
const char icon_run_batch[] = "CU_RUN_BAT.WGU";
const char icon_parameters[] = "CU_PARAM.WGU";
const char icon_force_online[] = "CU_ONLINE.WGU";
const char icon_tr_log[] = "CU_DUMP.WGU";

const char icon_run_batch_reset[] = "CU_RUN_BATR.WGU";
const char icon_batch_reset[] = "CU_RES_BAT.WGU";

const char icon_reset_all[] = "CU_RES_PAR.WGU";
const char icon_load_param[] = "CU_DEF_CNF.WGU";
const char icon_terminal_id[] = "CU_TERM_ID.WGU";
const char icon_dump_ICS[] = "CU_DUMP.WGU";
const char icon_dump_AID[] = "CU_DUMP.WGU";
const char icon_dump_Param[] = "CU_DUMP.WGU";
const char icon_default[] = "CU_DEFAULT.WGU";

const char icon_flag_fr[] = "CU_FLAG_FR.WGU";
const char icon_flag_en[] = "CU_FLAG_EN.WGU";

const char icon_valid[] = "CU_VALID.WGU";
const char icon_cancel[] = "CU_CANCEL.WGU";

/* ======================================================================== */
/* function declarations                                                    */
/* ======================================================================== */

//===========================================================================
void CUWGUI_load_icon(int num_icon, char **icon_name)
{
	switch(num_icon)
	{
		case CMN_MESS_DEBIT :
			(*icon_name)=(char*)icon_debit;
		break;
    
		case CMN_MESS_REFUND :
			(*icon_name)=(char*)icon_refund;
		break;

		case CMN_MESS_EMV_CASH :
			(*icon_name)=(char*)icon_cash;
		break;

		case CMN_MESS_EMV_CASHBACK :
			(*icon_name)=(char*)icon_cashback;
		break;

		case CMN_MESS_MERCHANT :
			(*icon_name)=(char*)icon_merchant;
		break;

#ifdef _TOOLWARE_
		case CMN_MESS_MERCHANT_TOOLWARE :
			(*icon_name)=(char*)icon_toolware;
		break;
#endif

//		case CMN_MESS_MERCHANT_PIN_BYPASS :
//			(*icon_name)=(char*)icon_pin_bypass;
//		break;

		case CMN_MESS_MERCHANT_BATCH_STAT :
			(*icon_name)=(char*)icon_batch_stat;
		break;

		case CMN_MESS_MERCHANT_RUN_BATCH :
			(*icon_name)=(char*)icon_run_batch;
		break;

		case CMN_MESS_MERCHANT_PARAM_MNGT :
			(*icon_name)=(char*)icon_parameters;
		break;

		case CMN_MESS_MERCHANT_FORCE_ONLINE :
			(*icon_name)=(char*)icon_force_online;
		break;

		case CMN_MESS_MERCHANT_TRANSACTIONLOG :
			(*icon_name)=(char*)icon_tr_log;
		break;

		case CMN_MESS_MERCHANT_RUN_BATCH_RAZ :
			(*icon_name)=(char*)icon_run_batch_reset;
		break;

		case CMN_MESS_MERCHANT_BATCH_RAZ :
			(*icon_name)=(char*)icon_batch_reset;
		break;

		case CMN_MESS_MERCHANT_RESET_ALL :
			(*icon_name)=(char*)icon_reset_all;
		break;

		case CMN_MESS_MERCHANT_DEFAUT_CONF :
			(*icon_name)=(char*)icon_load_param;
		break;

		case CMN_MESS_MERCHANT_TERMINAL_ID :
			(*icon_name)=(char*)icon_terminal_id;
		break;

		case CMN_MESS_MERCHANT_DUMP_ICS :
			(*icon_name)=(char*)icon_dump_ICS;
		break;

		case CMN_MESS_MERCHANT_DUMP_AID :
			(*icon_name)=(char*)icon_dump_AID;
		break;

		case CMN_MESS_MERCHANT_GLOBAL_PARAM :
			(*icon_name)=(char*)icon_dump_Param;
		break;

		case STD_MESS_UNDEFINED : 
		default:
			(*icon_name)=(char*)icon_default;
		break;
	}
}

//===========================================================================
void CUWGUI_load_flag_icon(char num_lang, char **icon_name)
{
	switch(num_lang)
	{
		case 0 :
			(*icon_name)=(char*)icon_flag_en;
		break;
    
		case 1 :
			(*icon_name)=(char*)icon_flag_fr;
		break;

		default:
			(*icon_name)=(char*)icon_default;
		break;

	}
}

//===========================================================================
void CUWGUI_load_yesno_icon(int index, char **icon_name)
{
	switch(index)
	{
		case 0 :
			(*icon_name)=(char*)icon_valid;
		break;
    
		case 1 :
			(*icon_name)=(char*)icon_cancel;
		break;

		default:
			(*icon_name)=(char*)icon_default;
		break;

	}
}

//===========================================================================
void CUWGUI_load_trans_icon(int index, char **icon_name)
{
	switch(index)
	{
		case 0 :
			(*icon_name)=(char*)icon_refund;
		break;
    
		case 1 :
			(*icon_name)=(char*)icon_debit;
		break;

		case 2 :
			(*icon_name)=(char*)icon_credit;
		break;

		default:
			(*icon_name)=(char*)icon_default;
		break;

	}
}

//===========================================================================
void CUWGUI_InitIconList(wIconList *pIconList)
{
	int lg_code;
	char FileName[32];

	// Get the manager language
	lg_code = PSQ_Give_Language();

	// Init html page
	sprintf(ilist_html,"@tar:///param/%s.tar/IList/ILIST.HTML", GetCguiFileName(FileName));
	pIconList->page_html = (char *)ilist_html;
	
	// Init title structure
	InitMSGinfos(&(pIconList->title));

	// Init left footer structure
	InitMSGinfos(&(pIconList->footer_left));
	pIconList->footer_left.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_VALIDATE, lg_code);

	// Init center footer structure
	InitMSGinfos(&(pIconList->footer_center));
	pIconList->footer_center.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_UNTIL_NEXT, lg_code);

	// Init right footer structure
	InitMSGinfos(&(pIconList->footer_right));
	pIconList->footer_right.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_CANCEL, lg_code);

	// Init timeout to 120 sec = 12000 ticks
	pIconList->time_out = 12000;

	pIconList->key_dot = _OFF_;

	pIconList->key_correction = _OFF_;

}

//===========================================================================
void CUWGUI_InitStructList(cGuiStructList *pWguiList)
{
	int lg_code;
	char FileName[32];

	// Get the manager language
	lg_code = PSQ_Give_Language();

	// Init html page
	sprintf(list_html,"@tar:///param/%s.tar/List/LIST.HTML", GetCguiFileName(FileName));
	pWguiList->page_html = (char *)list_html;
	
	// Init title structure
	InitMSGinfos(&(pWguiList->title));

	// Init default selected item to 0
	pWguiList->current = 0;

	// Init left footer structure
	InitMSGinfos(&(pWguiList->footer_left));
	pWguiList->footer_left.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_VALIDATE, lg_code);

	// Init center footer structure
	InitMSGinfos(&(pWguiList->footer_center));
	pWguiList->footer_center.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_UNTIL_NEXT, lg_code);

	// Init right footer structure
	InitMSGinfos(&(pWguiList->footer_right));
	pWguiList->footer_right.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_CANCEL, lg_code);

	// Init timeout to 120 sec = 12000 ticks
	pWguiList->time_out = 12000;

	// Init timeout to 120 sec = 12000 ticks
	pWguiList->key_correction = _OFF_;
	
}

//===========================================================================
void CUWGUI_InitStructEntry(cGuiStructEntry *pWguiEntry)
{
	int lg_code;
	char FileName[32];

	// Get the manager language
	lg_code = PSQ_Give_Language();

	// Init html page
	sprintf(input_html,"@tar:///param/%s.tar/Input/INPUT.HTML", GetCguiFileName(FileName));
	pWguiEntry->page_html = (char *)input_html;
	
	// Init title structure
	InitMSGinfos(&(pWguiEntry->title));

	// Init left footer structure
	InitMSGinfos(&(pWguiEntry->footer_left));
	pWguiEntry->footer_left.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_VALIDATE, lg_code);

	// Init right footer structure
	InitMSGinfos(&(pWguiEntry->footer_right));
	pWguiEntry->footer_right.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_CANCEL, lg_code);

	// Init current value structure
	InitMSGinfos(&(pWguiEntry->current_value));

	pWguiEntry->echo = 1;
	pWguiEntry->mask = 0x0000;

	// Init timeout to 120 sec = 12000 ticks
	pWguiEntry->time_out = 12000;
}

//===========================================================================
void CUWGUI_DisplayEnterPin(char *pcline1, char *pcline2, char *pcline3, char *pcline4, WGUI_BROWSER_HANDLE WGUI_Browser)
{
	WGUI_ERROR cr_wgui;
	char ac_line3[60];

	// Set template 1 of pin code html page
	cr_wgui = WGUI_Template_AddTagAscii(WGUI_Browser, tag_pinask, (const char *)pcline1, 1);

	// Set template 2 of pin code html page
	cr_wgui = WGUI_Template_AddTagAscii(WGUI_Browser, tag_pin, (const char *)pcline2, 1);

	// Set template 3 of pin code html page
	memset(ac_line3, 0, sizeof(ac_line3));
	sprintf(ac_line3, "%s\n%s", pcline3, pcline4);
	cr_wgui = WGUI_Template_AddTagAscii(WGUI_Browser, tag_pindesc, (const char *)ac_line3, 1);

	// Load pin code html page
	cr_wgui = WGUI_Browser_LoadUrl(WGUI_Browser, pin_html, 1);

	// Remove template 1 to recover memory
	cr_wgui = WGUI_Template_RemoveTagAscii(WGUI_Browser, tag_pinask);

	// Remove template 2 to recover memory
	cr_wgui = WGUI_Template_RemoveTagAscii(WGUI_Browser, tag_pin);

	// Remove template 3 to recover memory
	cr_wgui = WGUI_Template_RemoveTagAscii(WGUI_Browser, tag_pindesc);

}

//===========================================================================
void CUWGUI_DisplayPinLine(char inputkey, WGUI_CANVAS_HANDLE WGUI_Canvas)
{
	ttestall (KEYBOARD, 10);
	do
	{
		// Several DispatchEvent to get keyboard event and send it to the browser
		WGUI_Canvas_DispatchEvent(WGUI_Canvas);
	} while(ttestall(KEYBOARD, 1) != 0);
	WGUI_Canvas_DispatchEvent(WGUI_Canvas);
	WGUI_Canvas_DispatchEvent(WGUI_Canvas);
	WGUI_Canvas_DispatchEvent(WGUI_Canvas);
	WGUI_Canvas_DispatchEvent(WGUI_Canvas);
	WGUI_Canvas_DispatchEvent(WGUI_Canvas);
}

//===========================================================================
void CUWGUI_InitBrowser(void)
{
	CGUI_CONTEXT_STRUCT   CGUIContext;

	CGUIContext.CGUIStatus   = CGUI_NEEDED;
	CGUIContext.HeaderStatus = _PERIPH_OFF;
	CGUIContext.FooterStatus = _PERIPH_OFF;
	CGUIContext.LedsStatus   = _PERIPH_OFF;
	CGUIContext.CanvasStatus = CANVAS_MAXIMIZE;
	PushCGUIContext(&CGUIContext);
}

//===========================================================================
void CUWGUI_RestoreBrowser(void)
{
	PopCGUIContext();
}

//! \brief This function allows to sent an event to this task.
//! This event allows to suspend periodicaly SEC_PinEntry execution scheme.

static void CUWGUI_PeriodicBrowserCall(void)
{
   SignalEvent (g_wCurrentCguiTask, (tEvent)E_USER_EVENT_PIN);
}



//! \brief Start a periodical Delay and call the __ClessSample_Cgui_PeriodicBrowserCall() static function on each delay.
//! This event allows to suspend periodicaly SEC_PinEntry execution scheme.

void CUWGUI_BrowserStart(void)
{
    g_wCurrentCguiTask = CurrentTask();
    StartLDelay(C_USER_DELAY,50,50, (void*)CUWGUI_PeriodicBrowserCall); // unit = 10ms, Delay number = 1, FirstDelay = 100 (1000ms), Period = 100 (1000ms)
}



//! \brief Stop periodical Delay.

void CCUWGUI_BrowserStop(void)
{
    DoubleWord DWRestOfDelay;
    DoubleWord DWPeriod;
    StopDelay(C_USER_DELAY, &DWRestOfDelay, &DWPeriod);
}

//===========================================================================
//! \brief This function allows cgui to manage browser.
void CGUI_DisplayPinLine(void)
{
	// Several DispatchEvent to get keyboard event and send it to the browser
	WGUI_Canvas_DispatchEvent(canvas);
	WGUI_Canvas_DispatchEvent(canvas);
	WGUI_Canvas_DispatchEvent(canvas);
	WGUI_Canvas_DispatchEvent(canvas);
	WGUI_Canvas_DispatchEvent(canvas);
}
