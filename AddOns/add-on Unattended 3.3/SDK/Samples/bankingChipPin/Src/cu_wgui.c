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

//===========================================================================


