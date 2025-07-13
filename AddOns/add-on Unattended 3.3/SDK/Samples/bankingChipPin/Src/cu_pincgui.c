/**
* \file cu_pin.c
* \brief This module contains the functions that perform the entry of the PIN code.
* The PIN code can be entered directly on the terminal, or on a pinpad.
* It is kept in the booster.
* In case of enciphered PIN for online presentation, this module also
* encipher the PIN code, and returns the result.
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

#include "SDK30.H"
#include "cu_pinen.h"
#include "cu_term.h"
#include "TlvTree.h"
#include "cu_base.h"
#include "cu_mess.h"
#include "MessagesDefinitions.h"
#include "cu_pin.h"
#include "cu_pinen.h"
#include "del_lib.h"
#include "cu_serv.h"
#include "def_tag.h"
#include "cu_entry.h"
#include "convert.h"
#include "cu_param.h"
#include "gestion_param.h"
#include "cu_logos.h"
#include "WGUI.h"
#include "cu_wgui.h"

#include "sec_interface.h"
#include "schvar_def.h"


//! \addtogroup Group_cu_pin
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */
typedef enum PIN_RESULT
{
    C_PIN_INPUTED = 0,
    C_PIN_NO_INPUTED,
    C_PIN_NO_INPUTED_RECALL,
    C_PIN_CANCELED,
} PIN_RESULT;

#define CU_INPUT_PIN_OK               0

#define ICC_OK                        0
/* #define ICC_READER_ERROR              1
#define ICC_INVALID_PARAMETER         2
#define ICC_TIMEOUT                   4
#define ICC_INVALID_DATA              5
#define ICC_ABSENT                    6
#define ICC_INVALID_CARD              7
#define ICC_DRIVER_ERROR              9*/
#define ICC_PIN_ENTRY_TIMEOUT        17
#define ICC_PIN_CANCELLED            18
// #define ICC_PIN_ERROR                19

/* Type of PIN entry */
#define CUP_PIN_ONLINE                0
#define CUP_PIN_OFFLINE               1

/* Type of PinPad witch must be tested to display text */
#define CU_PPTEST_NOTEST              0
#define CU_PPTEST_CARDONPPAD          1
#define CU_PPTEST_ISPINPAD            2

/* Type of function to use to get keys */
#define CU_CUTERM_GETPPPIN            1
#define CU_CUTERM_GETKEY              2
#define CU_SCH_GETKEY                 4

/* Input key method to use */
#define CU_NO_METHOD_FIXED            0
#define CU_METHOD_UCM_WITH_CLOSE      1
#define CU_METHOD_UCM                 2
#define CU_METHOD_ENTER_PIN           3
#define CU_METHOD_EXT_WITH_SCHEMES    4


/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/
int PinpadValue;
unsigned char sim;
WGUI_CANVAS_HANDLE canvas = NULL;					/*!< Application CGUI canevas. */
WGUI_BROWSER_HANDLE browser = NULL;					/*!< Application CGUI browser. */


/* ========================================================================	*/
/* Static variable definitions                                              */
/* ========================================================================	*/

/* ========================================================================	*/
/* external  function definitions                                           */
/* ========================================================================	*/
extern  int  CU_SetPinEntry ( short TO_inter_car, short TO_first_car,unsigned int * ihid_key,int type_pin);
extern void CU_SetConfPinpad (int * PinpadValue);
extern void CUWGUI_BrowserStart(void);
extern void CCUWGUI_BrowserStop(void);
extern void CGUI_DisplayPinLine();


/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */


//===========================================================================


//! @}

