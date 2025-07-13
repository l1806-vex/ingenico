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
static unsigned short * ptr_Bypass_Required;

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
static int CGUI_DisplayEnterPinMsg(int nb_try, unsigned char PPTestType, unsigned char AllowTermIfPPadHS, int *PtrUsePinpad, WGUI_BROWSER_HANDLE WGUI_Browser);
static unsigned char CGUI_EnterPin(int nb_try,ENTRY_BUFFER *buffer,int type_pin,unsigned char PPTestType,unsigned char ForceKsu,unsigned char AllowTermIfPPadHS, WGUI_BROWSER_HANDLE Browser, WGUI_CANVAS_HANDLE WGUI_Canvas);
static unsigned char CGUI_ManageKeys(ENTRY_BUFFER *buffer,unsigned char ForceKsu,unsigned char KeyFunction,int isPinpad, int PinpadValue,int type_pin, WGUI_CANVAS_HANDLE WGUI_Canvas);
static PIN_RESULT CGUI_StopSchGetKey(void);
static PIN_RESULT CGUI_SchGetKey(  T_CUTERMkey *xp_key,unsigned int ihid_key);
static int Sample_Cgui_DisplayEnterPin (char* MessageL1, char* MessageL2, char* MessageL3, char* MessageL4);

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */
unsigned char CGUI_SelectInputKeyMethod (int nb_try, ENTRY_BUFFER *buffer, unsigned char type_pin, unsigned char AllowTermIfPPadHS);


//===========================================================================


//===========================================================================
//! \brief This function displays the enter pin message to the user.
//! \param[in] nb_try : number of PIN entry attempts.
//! \param[in] PPTestType : indicates the access to be tested.
//! \param[in] AllowTermIfPPadHS : boolean allowing the terminal management,
//! if the pinpad is here but out of service.
//! \param[out] PtrUsePinpad : boolean indicating if the pinpad can be used.
//! \param[in] WGUI_Browser : HTML browser allowing to display HTML pages.
//! \return
//! - TRUE if a problem exists with the user interface (pinpad access ko).
//! - FALSE otherwise.
//===========================================================================
static int CGUI_DisplayEnterPinMsg(int nb_try, unsigned char PPTestType, unsigned char AllowTermIfPPadHS, int *PtrUsePinpad, WGUI_BROWSER_HANDLE WGUI_Browser)
{
	unsigned short	lg_code;
	// This warning text may be displayed only in graphical mode
	unsigned char	uc_l_DisplayWarningText = 0; 
	int				interfaceok;
	char *			pc_l_DisplayTxt;
	char *			pc_l_line2;
	char *			pc_l_line3;
	char *			pc_l_line4;
	char *			pc_l_DisplayAmt;
	unsigned short	found;
	DataElement		elt;
	char			buffer[40];

	// Local variables initialisation
	*PtrUsePinpad = FALSE;
	interfaceok = FALSE;

	CUDB_Get_cardholder_language (&lg_code);

	if (nb_try == 1)
	{
		// message = ENTER PIN
		pc_l_line2 = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_ENTER_PIN, lg_code);
	}
	else
	{
		// message = TRY AGAIN
		pc_l_line2 = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_TRY_AGAIN, lg_code);
	}


	pc_l_DisplayAmt = CUMESS_Read_Message(DEFAULT_TABLE, STD_MESS_AMOUNT, lg_code);

	
	/*&BEGIN FT/08/4015/MA    bad format or forgotten amount */
	if ((ul_InputAmount % 100) != 0)
		sprintf(buffer, "%s:%6lu.%02lu ", pc_l_DisplayAmt, ul_InputAmount/100, ul_InputAmount%100);
	else
		sprintf(buffer, "%s:%8lu ", pc_l_DisplayAmt, ul_InputAmount/100);
	/*&END FT/08/4015/MA    bad format or forgotten amount */

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();
	found = PAR_ReadParameter(TAG_TRANSACTION_CURRENCY_CODE, (DataElementExt *)&elt);
	if (found)
	{
		unsigned char i;
		unsigned short currency_code;

		currency_code = (elt.ptValue[0] << 8) + elt.ptValue[1];
		for (i=0; i< L_NBCURCY; i++)
		{
			if (ct_confCurrency[i].currency == currency_code)
			{
				strcat (buffer, ct_confCurrency[i].label);
				break;
			}
		}
	}


	{

		// tests the pinpad to be addressed.
		if (PPTestType == CU_PPTEST_NOTEST)
			*PtrUsePinpad = FALSE;
		else if (PPTestType == CU_PPTEST_ISPINPAD)
		{
			// Tests if a pinpad is declared
			*PtrUsePinpad = CUTERIsPinpadPresent();

			// If a pinpad is declared
			if (*PtrUsePinpad)
			{
				// Tests if pinpad is ok, and connected
				if(IsPPSConnected() == 0)
					// pinpad is here and can be used
				{
					*PtrUsePinpad = TRUE;
			    }
				else
				{
					// Here pinpad is declared but not present
					// If the terminal can be used to keep pin
					if (AllowTermIfPPadHS)
					{
						// pinpad is here and cannot be used
						*PtrUsePinpad = FALSE;
						// Terminal access is considered as good
						interfaceok = TRUE;
					}
					else
					{
						// The terminal can't be used if pinpad is out of order
						// pinpad is here and cannot be used
						*PtrUsePinpad = FALSE;
						// Bad pinpad access cannot allow to keep pinpad
						interfaceok = FALSE;
						return (interfaceok);
					}
				}
			}
		}

		// If Pinpad is present and can be used
		if (*PtrUsePinpad)
		{
			int ret;
			PPS_firstline ();

			// Warning, on graphical pinpad, library function must be used for long text

			// Tests if graphical function can be used on pinpad
			if (CUTERMIsGraphicPP())
			{
				uc_l_DisplayWarningText = 1;
				InitContexteGraphique(PERIPH_PPR);
				CUTERMdisplayGraphicLine(2, pc_l_line2, CENTER, (char*)"w", FALSE); 
				
				// Restore previous configuration
				InitContexteGraphique(PERIPH_DISPLAY);

				// No pinpad to use, user interface is ok
				interfaceok = TRUE;
			}
			else
			{
				// graphical function can't be used on pinpad
				ret = PPS_Display (pc_l_line2);
				interfaceok = (ret != 1);
			}
		}

		else
		{
			// pinpad isn't present or cannot be used
			// No pinpad to use, user interface is ok
			interfaceok = TRUE;
			CUTERMclearDisplay();

			uc_l_DisplayWarningText = 1;
		}

		// Tests if graphical function can be used
		if (uc_l_DisplayWarningText)
		{
			char ac_l_line1[40];

			if (*PtrUsePinpad)
				InitContexteGraphique(PERIPH_PPR);
			/*&BEGIN FT/08/4015/MA    bad format or forgotten amount */

			pc_l_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, STD_MESS_AMOUNT, lg_code);

			/*&BEGIN FT/08/4015/MA    bad format or forgotten amount */
			sprintf(ac_l_line1, "%s: %lu.%02lu ", pc_l_DisplayTxt, ul_InputAmount/100, ul_InputAmount%100);
			/*&END FT/08/4015/MA    bad format or forgotten amount */

			// Reset the selected mark list
			PAR_ResetMarkList();
			// Select Main ICS + ICSx (Maybe unused)
			CUPAR_SelectAdditionnalICS();

			found = PAR_ReadParameter(TAG_TRANSACTION_CURRENCY_CODE, (DataElementExt *)&elt);
			if (found)
			{
				unsigned char i;
				unsigned short currency_code;

				currency_code = (elt.ptValue[0] << 8) + elt.ptValue[1];
				for (i=0; i< L_NBCURCY; i++)
				{
					if (ct_confCurrency[i].currency == currency_code)
					{
						strcat (ac_l_line1, ct_confCurrency[i].label);
						break;
					}
				}
			}
			/*&END FT/08/4015/MA    bad format or forgotten amount */

			if(!Get_StateWGUI() || (*PtrUsePinpad && CUTERMIsGraphicPP()))
			{
			
				CUTERMdisplayGraphicLine(0, ac_l_line1, CENTER, (char*)" ", FALSE);

				CUTERM_DefineNewChar();
				pc_l_line3 = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_PROTECT_ENTER_PIN, lg_code);
				CUTERMdisplayGraphicLine(3, pc_l_line3, CENTER, (char*)" ", TRUE);
				pc_l_line4 = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_PROTECT_ENTER_PIN_L2, lg_code);
				CUTERMdisplayGraphicLine(4, pc_l_line4, CENTER, (char*)" ", TRUE);

				CUTERM_RestoreChar();
				if (*PtrUsePinpad)
					// Restore previous configuration
					InitContexteGraphique(PERIPH_DISPLAY);
			}
			else
			{
			// Display pin code html page
			pc_l_line3 = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_PROTECT_ENTER_PIN_CGUI, lg_code);
			pc_l_line4 = NULL;//CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_PROTECT_ENTER_PIN_L2, lg_code);
			Sample_Cgui_DisplayEnterPin (ac_l_line1, pc_l_line2, pc_l_line3, pc_l_line4);
			WGUI_Canvas_DispatchEvent(canvas); 
			WGUI_Canvas_DispatchEvent(canvas);
			WGUI_Canvas_DispatchEvent(canvas);
			WGUI_Canvas_DispatchEvent(canvas);
			WGUI_Canvas_DispatchEvent(canvas);
			}
		}
	}

	return (interfaceok);
}
//! \brief Displays a message to input PIN and a choice (validate, cancel).
//! \param[in] MessageL1 Message displayed on the first line.
//! \param[in] MessageL2 Message displayed on the second line.
//! \param[in] MessageL3 Message displayed on the third line.
//! \param[in] MessageL4 Message displayed on the fourth line.
//! \return
//!		- TRUE if user selected the left choice.
//!		- FALSE if user selected the right choice.

static int Sample_Cgui_DisplayEnterPin (char* MessageL1, char* MessageL2, char* MessageL3, char* MessageL4)
{
	int ret = 0;
	WGUI_ERROR cr_wgui;
	char ac_line3[60];

	if (MessageL1 != NULL)
		cr_wgui = WGUI_Template_AddTagAscii(browser,"PINASK",MessageL1,1);
	if (MessageL2 != NULL)
		cr_wgui = WGUI_Template_AddTagAscii(browser,"PIN",MessageL2,1);

	// Set template 3 of pin code html page
	memset(ac_line3, 0, sizeof(ac_line3));
	if (MessageL3 != NULL)
    	sprintf(ac_line3, "%s\n", MessageL3);
	if (MessageL4 != NULL)
    	strcat(ac_line3, MessageL4);

    if (strlen(ac_line3)) // If something to set
    	cr_wgui = WGUI_Template_AddTagAscii(browser, "PINDESC", (const char *)ac_line3, 1);


	// Load the URL
   	cr_wgui = WGUI_Browser_LoadUrl(browser, "@tar:///param/844042----.tar/Pin/Pin.html",1);

	// Set the focus on the application canevas
	WGUI_Canvas_SetFocus(canvas);

	// Dispatch event while no html event fire
	// Dispatch keyboard, mouse and timer event to all browsers
	WGUI_Canvas_DispatchEvent(canvas);
	WGUI_Canvas_DispatchEvent(canvas);
	WGUI_Canvas_DispatchEvent(canvas);
	WGUI_Canvas_DispatchEvent(canvas);
	WGUI_Canvas_DispatchEvent(canvas);

	if (MessageL1 != NULL)
		cr_wgui = WGUI_Template_RemoveTagAscii(browser,"PINASK");

	if (MessageL2 != NULL)
		cr_wgui = WGUI_Template_RemoveTagAscii(browser,"PIN");

    if (strlen(ac_line3)) // If something to set
		cr_wgui = WGUI_Template_RemoveTagAscii(browser,"PINDESC");

	return(ret);
}

//===========================================================================
//! \brief This function performs the PIN code entry.
//! This function must select cases where each key may be managed or
//! only final result with OK, CANCEL, CORRECT, TIME_OUT.
//! \param[in] nb_try : number of PIN entry attempts.
//! \param[out] buffer : buffer containing the cyphered PIN code.
//! \param[in] type_pin : indicates the PIN code type : 
//! \li - CUP_PIN_OFFLINE.
//! \li - CUP_PIN_ONLINE.
//! \param[in] PPTestType : indicates the access to be tested.
//! \param[in] ForceKsu : Ksu is mandatory or not.
//! \param[in] AllowTermIfPPadHS : boolean allowing the terminal management,
//! if the pinpad is here but out of service.
//! \param[in] WGUI_Browser : HTML Browser allowing to display HTML pages.
//! \param[in] WGUI_Canvas : Canvas used by HTML browser.
//! \return The encipherement result : 
//! - PP_HS : Problem with PINPAD, or with the booster.
//! - CU_INPUT_PIN_OK : PIN entry and encipherement was successfull.
//! - CANCEL_INPUT : PIN entry was canceled.
//! - TO_INPUT : Time-out during PIN entry.
//===========================================================================
static unsigned char CGUI_EnterPin(int nb_try,
							  ENTRY_BUFFER *buffer,
							  int type_pin,
							  unsigned char PPTestType,
							  unsigned char ForceKsu,
							  unsigned char AllowTermIfPPadHS,
							  WGUI_BROWSER_HANDLE WGUI_Browser,
							  WGUI_CANVAS_HANDLE WGUI_Canvas)
{
	unsigned char cr_enter_pin;
	unsigned char KeyFunction;
	int           PinPadUsed, pinpadok;

	// Local variables initialisation
	cr_enter_pin = CANCEL_INPUT;

	pinpadok = CGUI_DisplayEnterPinMsg(nb_try, PPTestType, AllowTermIfPPadHS, &PinPadUsed, WGUI_Browser);

	if (pinpadok != TRUE)
		// Error management
		return (PP_HS);

	// What InputKeyFunction we can autorise ?
	if (ForceKsu)
		// Allow only CUTERMgetKey() functions to obtain keys
		KeyFunction = CU_SCH_GETKEY;
	else
		// Allow all functions to obtain keys
		KeyFunction = CU_CUTERM_GETPPPIN + CU_CUTERM_GETKEY + CU_SCH_GETKEY;

	cr_enter_pin = CGUI_ManageKeys(buffer,
		ForceKsu,							// Manage ksu
		KeyFunction,						// Allow functions to obtain keys
		PinPadUsed,PinpadValue, type_pin,	// pinpad must be used if present
		WGUI_Canvas);						// WGUI canvas
	return(cr_enter_pin);
}

//===========================================================================
//! \brief This function manages UCM, SPED or standard function selection for PIN code entry.
//! \param[in] nb_try : number of PIN entry attempts.
//! \param[out] buffer : buffer containing the cyphered PIN code.
//! \param[in] type_pin : indicates the PIN code type : 
//! \li - CUP_PIN_OFFLINE.
//! \li - CUP_PIN_ONLINE.
//! \param[in] AllowTermIfPPadHS : boolean allowing the terminal management,
//! if the pinpad is here but out of service.
//! \return The encipherement result : 
//! - PP_HS : Problem with the pinpad, or with the booster.
//! - CU_INPUT_PIN_OK : PIN entry and encipherement was successfull.
//! - CANCEL_INPUT : PIN entry was canceled.
//! - TO_INPUT : Time-out during PIN entry.
//===========================================================================
 unsigned char CGUI_SelectInputKeyMethod (int nb_try, ENTRY_BUFFER *buffer, unsigned char type_pin, unsigned char AllowTermIfPPadHS)
{
	char				Method_selector;
	unsigned char		ForceKsu;
	unsigned char		cr_enter_pin;
	unsigned char		PPTestType;
	WGUI_ERROR			cr_wgui;
	FILE				* Keybd = NULL;
	int					left, top, right, bottom;

	// Default values initialisation
	Method_selector = CU_NO_METHOD_FIXED;
	ForceKsu        = FALSE;
	cr_enter_pin    = PP_HS;
	PPTestType      = CU_PPTEST_NOTEST;


		// Open keyboard to get keys from input_sim
		Keybd = fopen("KEYBOARD","r");

		// Get screen position
		GetScreenArea(&left,&top,&right,&bottom);

		// Canvas creation
		canvas = WGUI_Canvas_Create(WGUI_CANVAS_SCREEN, left, top, right, bottom);



		// Browser creation
		browser = WGUI_Browser_Create(canvas);

		// Modify browser options to enable tag modification
		cr_wgui = WGUI_Browser_SetOption(browser, WGUI_BROWSER_TEMPLATE_MODE, WGUI_TEMPLATE_ACTIVATE);

		// Modify browser options to desactivate loading bar
		cr_wgui = WGUI_Browser_SetOption(browser, WGUI_BROWSER_LOADING_BAR_DELAY, WGUI_INFINITE);


	/******************************/
	/* Which method may be used ? */
	/******************************/

	if (type_pin == CUP_PIN_OFFLINE)
	{
		Method_selector = CU_METHOD_ENTER_PIN;

		// Display Enter Pin msg
		PPTestType = CU_PPTEST_NOTEST;
	}
	else

		if (type_pin == CUP_PIN_ONLINE)
		{
			Method_selector = CU_METHOD_ENTER_PIN;
			PPTestType = CU_PPTEST_ISPINPAD;
		}
		// In all cases : Manage Ksu will be forced for Sped (if compiled + sped connected)
		// This variable is used only for CU_METHOD_ENTER_PIN


		/**************************/
		/* Manage method selected */
		/**************************/

	switch (Method_selector)
	{
	case CU_METHOD_UCM:
	case CU_METHOD_UCM_WITH_CLOSE:
	case CU_METHOD_ENTER_PIN:
			cr_enter_pin = CGUI_EnterPin(nb_try, buffer, type_pin, PPTestType, ForceKsu, AllowTermIfPPadHS, browser, canvas);
		break;

	case CU_METHOD_EXT_WITH_SCHEMES:
		break;

	default:
		cr_enter_pin = PP_HS;
		break;
	}

	// Browser destruction
	cr_wgui = WGUI_Browser_Destroy (browser);

	// Canvas destruction
	WGUI_Canvas_Destroy(canvas);

	// Close keyboard
	fclose(Keybd);
	
	return (cr_enter_pin);

}


//===========================================================================
//! \brief This function manages each key input.
//! \param[out] buffer : buffer to store keys.
//! \param[in] ForceKsu : boolean indicating if ksu is mandatory or not.
//! \param[in] KeyFunction : key function indicator to know which function may be used to obtain keys.
//! \param[in] isPinpad : boolean indicating if pinpad can be used.
//! \param[in] PinpadValue : pinpad value.
//! \param[in] type_pin : indicates the PIN code type : 
//! - CUP_PIN_OFFLINE.
//! - CUP_PIN_ONLINE.
//! \param[in] WGUI_Canvas : Canvas used by HTML browser.
//! \return The encipherement result : 
//! - PP_HS : Problem with the pinpad, or with the booster.
//! - CU_INPUT_PIN_OK : PIN entry and encipherement was successfull.
//! - CANCEL_INPUT : PIN entry was canceled.
//! - TO_INPUT : Time-out during PIN entry.
//===========================================================================
static unsigned char CGUI_ManageKeys(ENTRY_BUFFER *buffer,
								unsigned char ForceKsu,
								unsigned char KeyFunction,
								int isPinpad, int PinpadValue,
								int type_pin,
								WGUI_CANVAS_HANDLE WGUI_Canvas)
{
	short			wait_input, TO_inter_car, TO_first_car;
	T_Bool			cr;
	T_CUTERMkey		key;
	unsigned char	text[40];
	unsigned char	end_enter_pin;
	unsigned char	cr_enter_pin;
	int				cr_initsch, cr_endsch;
	int				ksu_sch;
	int				indice;
	int				firstCar, column;
	unsigned long	fct_ksu;
	FILE			*iapp;
	unsigned int	ihid_key;
	unsigned char	ucdataout;
	unsigned int	uiEventToWait;
	unsigned int	ibToContinue;
	unsigned char	index;

	// Local variables initialisation
	TO_inter_car  = 0;
	TO_first_car  = 0;
	ksu_sch       = FALSE;
	cr            = B_TRUE;
	iapp          = NULL;

	end_enter_pin = FALSE;
	indice        = 0;
	buffer->d_len= 0;
	firstCar      = 0;
	cr_enter_pin  = CANCEL_INPUT;
	column        = 4;

	CUDB_GetParamPINCode (&TO_inter_car, &TO_first_car, &fct_ksu);

	// CUDB_Get_cardholder_language (&lg_code);

	if (ForceKsu)
		// If Ksu is Mandatory
		ksu_sch = TRUE;
	else
	{
		// If Ksu is not Mandatory => test if ksu must be used
		// Use of KSU only for PIN Offline entry, in this version
		if ( ( fct_ksu & (SCH_PINCODE_OFFLINE)) != 0 )
		{
			// PinCode Schemes to launch
			ksu_sch = (isPinpad == B_FALSE) || ( (isPinpad == B_TRUE) &&((PinpadValue!= PP30_PPAD)));
		}
	}

	if (ksu_sch)
	{
		// If ksu must be managed
		cr_initsch = CU_SetPinEntry ( TO_inter_car,TO_first_car,&ihid_key, type_pin);
	}
	else
		cr_initsch = OK;

	wait_input=TO_first_car;

    CUWGUI_BrowserStart();

	while(!end_enter_pin)
	{
		if (! (!Get_StateWGUI() || (isPinpad && CUTERMIsGraphicPP())))
			CGUI_DisplayPinLine();

		if ((ksu_sch) && (KeyFunction & CU_SCH_GETKEY))
		{
			cr = CGUI_SchGetKey( &key, ihid_key);

		    if ( cr == C_PIN_NO_INPUTED)
			{
				cr_enter_pin  = TO_INPUT;
				end_enter_pin = TRUE;
			}
		}
		else if ((isPinpad == B_TRUE) && (KeyFunction & CU_CUTERM_GETPPPIN))
		{
			// use TRACE  Id 0xA000 : my application
			trace(0x0F02,strlen("begin CUTERMgetPPpin"),"begin CUTERMgetPPpin");

			cr_enter_pin  = CUTERMgetPPpin(TO_first_car, TO_inter_car, buffer);

			end_enter_pin = TRUE;
			cr = B_FALSE;
		}
		else if (KeyFunction & CU_CUTERM_GETKEY)
		{
			// use TRACE  Id 0xA000 : my application
			trace(0x0F02,strlen("begin CUTERMgetKey"),"begin CUTERMgetKey");
			cr = CUTERMgetKey(wait_input, &key);
			if (cr == B_FALSE)
			{
				cr_enter_pin  = TO_INPUT;
				end_enter_pin = TRUE;
			}
		}

		if ( cr == C_PIN_CANCELED)
		{
			cr_enter_pin  = CANCEL_INPUT;
			end_enter_pin = TRUE;
		}
		else if ( cr == C_PIN_INPUTED)
		{
			// Key has been typed
			if ( firstCar==0 )
			{
				firstCar=1;
				wait_input=TO_inter_car;
			}

			switch (key)
			{
			case CU_VALID : 
				// end of the enter pin
				if (indice == 0)
				{
					*ptr_Bypass_Required = TRUE;
				}
				buffer->d_len=indice;
				cr_enter_pin  = CU_INPUT_PIN_OK;
				end_enter_pin = TRUE;
				break;

			case C_PIN_CANCELED :
				// cancel the enter pin
				buffer->d_len=0;
				cr_enter_pin  = CANCEL_INPUT;
				end_enter_pin = TRUE;
				break;

			case CORRECT:
				// correction
				if (indice!=0)
				{
					column = column-1;
					if ((isPinpad == B_TRUE) && (!CUTERMIsGraphicPP()) && (!ForceKsu))
					{
						int index;

						memset( (char *)text, 0, 20 );
						PPS_clearline ();

						for (index = 0; index < indice - 1; index++)
						{
							strcat ((char *)text, "*");
						}
						PPS_Display ( (char *)text);
					}
					else
					{
						strcpy((char *)text, " ");
						strcpy(text, "   ");
						for (index = 4; index<column; index++)
							strcat(text, "*");
						{
							strcat(text, " ");

							if(!Get_StateWGUI() || (isPinpad && CUTERMIsGraphicPP()))
							{
								if (isPinpad)
									InitContexteGraphique(PERIPH_PPR);
								CUTERMdisplayGraphicLine(2, (char *)text, LEFT, (char*)" ", FALSE);
								if (isPinpad)
									InitContexteGraphique(PERIPH_DISPLAY);
							}
							else
							{
							// Refresh pin code html page
							CGUI_DisplayPinLine();
							}
						}
					}
					indice = indice-1;
				}
				break;

			default:
				// correction
				// Note : Numeric key sent by shemes is always 0x30 for input key 0 to 9
				if ( (key<=0x39) && (key>=0x30) && (indice < 13) )
				{
					if (indice ==0)
					{
						strcpy((char *)text, "                   ");
						if ((isPinpad == B_TRUE) && (!CUTERMIsGraphicPP()) && (!ForceKsu))
						{
							PPS_clearline ();
						}
						else
						{
							{
								if(!Get_StateWGUI() || (isPinpad && CUTERMIsGraphicPP()))
								{
									if (isPinpad)
										InitContexteGraphique(PERIPH_PPR);
									CUTERMdisplayGraphicLine(2, (char *)text, LEFT, (char*)" ", FALSE);
									if (isPinpad)
										InitContexteGraphique(PERIPH_DISPLAY);
								}
							}
						}
						column = 4;
					}
					strcpy((char *)text, "*");

					if ((isPinpad == B_TRUE) && (!CUTERMIsGraphicPP()) && (!ForceKsu))
					{
						PPS_Display ( (char *)text);
					}
					else
					{
						strcpy(text, "   *");
						for (index = 4; index<column; index++)
							strcat(text, "*");
						{
							if(!Get_StateWGUI() || (isPinpad && CUTERMIsGraphicPP()))
							{
								if (isPinpad)
									InitContexteGraphique(PERIPH_PPR);
								CUTERMdisplayGraphicLine(2, (char *)text, LEFT, (char*)" ", FALSE);
								if (isPinpad)
									InitContexteGraphique(PERIPH_DISPLAY);
							}
							else
							{
								// Refresh pin code html page
								CUWGUI_DisplayPinLine(0x30, WGUI_Canvas);
							}
						}
					}

					buffer->d_entry[indice++] = (unsigned char) key;
					column ++;
				}
				break;
			}

		}   //End Else Key has been typed */

	}

	if (ksu_sch) 
		if (cr_initsch == 0)
		{
			uiEventToWait = 0;
			ibToContinue = FALSE; 
			// STOP pin entry

			// use TRACE  Id 0xA000 : my application
			trace(0x0F02,strlen("debut pin entry"),"debut pin entry");

			cr_endsch = SEC_PinEntry (&uiEventToWait,&ucdataout, &ibToContinue);

			// use TRACE  Id 0xA000 : my application
			trace(0x0F02,strlen("fin pin entry"),"fin pin entry");
		}

        CCUWGUI_BrowserStop();

		return (cr_enter_pin);
}


//===========================================================================
//! \brief This function reads a byte on the IAPP link coming from the input PIN scheme.
//! \li Thunder Booster
//! \li ------- -------
//! \li     <--- 'x' several    times
//! \li      ...
//! \li     <--- 'y'
//! \li 'x' is the typed key : K_HID_NUM for numeric key, K_CORRECT for CORRECT key.
//! \li 'y' is the last typed key : K_VALID for VALID key, K_CANCEL for CANCEL key, K_TIMEOUT for TimeOut.
//! \param xp_key : the read byte K_HID_NUM, K_CORRECT, K_VALID, K_CANCEL, or K_TIMEOUT.
//! \param ihid_key : character displayed to hide real character entered.
//! \return
//! - TRUE a key has been read.
//! - FALSE timeout expired or K_TIMEOUT has been read.
//===========================================================================
static PIN_RESULT CGUI_SchGetKey(  T_CUTERMkey *xp_key,unsigned int ihid_key)
{
	int iret;
	int s_ibPinpadBoost;
	unsigned int Key;
	unsigned char ucdataout;
	unsigned int uiEventToWait = 0;
    unsigned int ibToContinue;
	PIN_RESULT res_key;

    // Initialisation
	res_key = C_PIN_INPUTED; // Default value
	s_ibPinpadBoost = FALSE;
	ibToContinue = TRUE;

	if (!s_ibPinpadBoost)
		uiEventToWait = 0;
	else
		// waiting event EFT keyboard
		uiEventToWait = KEYBOARD;


	// USER_EVENT_PIN is given by periodic task. This event allows to suspend the SEC_PinEntry scheme execution.
	uiEventToWait |= USER_EVENT_PIN; // USER_EVENT_PIN is given by periodic task   a remetttre

	iret = SEC_PinEntry (&uiEventToWait,&ucdataout, &ibToContinue);

	Key = ucdataout;
	if (iret == OK)
	{
		if (Key == ihid_key)
		{
			// This is a numeric key
			*xp_key = ZERO;
		}
		else
			switch (Key) {
					case 0x00:
						res_key = C_PIN_NO_INPUTED;
						upload_diagnostic_txt("Time out \n");
						break;
					case 0x01: 
						upload_diagnostic_txt("PIN CANCEL\n");	// 
						res_key = C_PIN_NO_INPUTED;
						break;
					case T_VAL :
						*xp_key = CU_VALID; 
						break;
					case T_ANN:
						*xp_key = CANCEL; 
						upload_diagnostic_txt("PIN Annulation\n"); 
						break;
					case T_CORR:
						*xp_key = CORRECT; 
						upload_diagnostic_txt("PIN Correction\n"); 
						break;
		}
	}
	else if (iret == ERR_TIMEOUT)
	{
	    if ((uiEventToWait & USER_EVENT_PIN) != 0) // No information inputed and no time-out, it's an event used to suspend SEC_PinEntry temporary
	    {
			res_key = C_PIN_NO_INPUTED_RECALL; // Please, call back this function later
		}
		if ((uiEventToWait & KEYBOARD) != 0) // Keyboard event (comming from terminal when ppinpad is used)
		{
		    Key = getchar(); // Which key ?

		    if (Key == T_ANN) // If key is cancel => stop PinPad Pin input
		    {
			    res_key = C_PIN_CANCELED; // Pin input stopped by Cancel key pressed on terminal
			    CGUI_StopSchGetKey(); // To stop SEC_PinEntry scheme
    		}
		    else
		    {
		          // Key not managed
    			res_key = C_PIN_NO_INPUTED_RECALL; // Please, call back this function later
            }
		}

	    if (uiEventToWait == 0)
		{
		    res_key = C_PIN_NO_INPUTED;
		}
	}
	else
	{
	    res_key = C_PIN_NO_INPUTED;
	}

	return(res_key);
}

//===========================================================================
//! \brief This function stop SEC_PinEntry scheme.
//! \return
//! - B_NON_INIT key not inputed but fonction release allows to manage html browser : this function must be called back later.
//! - TRUE a key has been read.
//! - FALSE timeout expired or K_TIMEOUT has been read.
//===========================================================================
static PIN_RESULT CGUI_StopSchGetKey(void)
{
	int iret;
	unsigned char ucdataout;
	unsigned int uiEventToWait = 0;
    unsigned int ibToContinue = FALSE;


	iret = SEC_PinEntry (&uiEventToWait,&ucdataout, &ibToContinue);

	return(iret);
}

//! @}

