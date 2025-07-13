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

#ifdef _USE_UCM_
#include "ucmtelium.h"
#include "ucmhostdll.h"
#include "ucmclib.h"
#endif

#include "sec_interface.h"
#include "schvar_def.h"


//! \addtogroup Group_cu_pin
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

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
static unsigned short * ptr_Bypass_Required;

int PinpadValue;

unsigned char sim;

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/
int  CU_SetPinEntry ( short TO_inter_car, short TO_first_car,unsigned int * ihid_key,int type_pin);
static int DisplayEnterPinMsg(int nb_try, unsigned char PPTestType, unsigned char AllowTermIfPPadHS, int *PtrUsePinpad);
// Services to manage Schemes
static unsigned char EnterPin(int nb_try,ENTRY_BUFFER *buffer,int type_pin,unsigned char PPTestType,unsigned char ForceKsu,unsigned char AllowTermIfPPadHS);
static T_Bool CU_SchGetKey(  T_CUTERMkey *xp_key,unsigned int ihid_key);
static unsigned char ManageKeys(ENTRY_BUFFER *buffer,unsigned char ForceKsu,unsigned char KeyFunction,int isPinpad, int PinpadValue,int type_pin);
static unsigned char SelectInputKeyMethod (int nb_try, ENTRY_BUFFER *buffer, unsigned char type_pin, unsigned char AllowTermIfPPadHS);

extern int TransactionLoopMode;
extern unsigned long loop_amount;



static void CU_SetConfPinpad (int * PinpadValue);


/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
unsigned char CUPIN_EnterPinOnLine(unsigned char nb_try,
								   unsigned char AllowTermIfPPadHS,
								   ENTRY_BUFFER *buffer,
								   unsigned char * ptrPrimaryAccountNumber,
								   unsigned short * ptrBypass)
{
	unsigned char  cr_enter_pin;
	int            iRes, iLenEnc,iResInject;

	// Header management / display on X07
	//StateHeader (0);

	// Global variable affectation for later use
	ptr_Bypass_Required = ptrBypass;

	iResInject = KO;

	cr_enter_pin = CU_INPUT_PIN_OK;
	// Inject a dummy secret key in the booster
	{
#ifdef _USE_DEMO_
		PIN_InjectKeyDemo();
/*&BEGIN FT/09/5296/MA    SEC_ISO9563 has to be called only if Injection successfull */
		iResInject = OK;
#else
		CU_SetConfPinpad (&PinpadValue); 

		iResInject = PIN_InjectKey ();
#endif	    
	}

	if (iResInject == OK )
	{
/*&END FT/09/5296/MA    SEC_ISO9563 has to be called only if Injection successfull */
	cr_enter_pin = SelectInputKeyMethod (nb_try, buffer, CUP_PIN_ONLINE, AllowTermIfPPadHS);


		if ( cr_enter_pin == CU_INPUT_PIN_OK )
		{
			{
#ifdef _USE_DEMO_
			iRes = PIN_OnlineEncipherDemo (ptrPrimaryAccountNumber, buffer->d_entry,&iLenEnc);
#else
				// Encipher the entered PIN
				iRes = PIN_OnlineEncipher (ptrPrimaryAccountNumber, buffer->d_entry,&iLenEnc);
#endif
				if (iRes)
				{
					cr_enter_pin = INPUT_PIN_ON;
					buffer->d_len = (char) iLenEnc;
				}
				else
				{
					cr_enter_pin = PP_HS;
				}
			}
		}
	}
	
	// Header management / display on X07
	//StateHeader (1);

	return(cr_enter_pin);
}

//===========================================================================
unsigned char CUPIN_EnterPinOffLine(unsigned char nb_try,
									unsigned char AllowTermIfPPadHS,
									ENTRY_BUFFER *buffer,
									unsigned char * ptrPrimaryAccountNumber,
									unsigned short * ptrBypass)
{
	unsigned char cr_enter_pin;

	// Header management / display on X07
	//StateHeader (0);

	sim =1;

	// Global variable affectation for later use
	ptr_Bypass_Required = ptrBypass;

	// Time out on pincode input
	cr_enter_pin = ERROR_INPUT;

	CU_SetConfPinpad (&PinpadValue); 

	while  (cr_enter_pin == ERROR_INPUT)
	{
		cr_enter_pin = SelectInputKeyMethod (nb_try, buffer, CUP_PIN_ONLINE, AllowTermIfPPadHS);

		if ( cr_enter_pin == CU_INPUT_PIN_OK)
			cr_enter_pin = INPUT_PIN_OFF;
		nb_try=nb_try+1;
	}

	// Header management / display on X07
	//StateHeader (1);

	return(cr_enter_pin);
}

//===========================================================================
//! \brief This function displays the enter pin message to the user.
//! \param[in] nb_try : number of PIN entry attempts.
//! \param[in] PPTestType : indicates the access to be tested.
//! \param[in] AllowTermIfPPadHS : boolean allowing the terminal management,
//! if the pinpad is here but out of service.
//! \param[out] PtrUsePinpad : boolean indicating if the pinpad can be used.
//! \return
//! - TRUE if a problem exists with the user interface (pinpad access ko).
//! - FALSE otherwise.
//===========================================================================
static int DisplayEnterPinMsg(int nb_try, unsigned char PPTestType, unsigned char AllowTermIfPPadHS, int *PtrUsePinpad)
{
	unsigned short lg_code;
	// This warning text may be displayed only in graphical mode
	unsigned char  uc_l_DisplayWarningText = 0; 
	int            interfaceok;
	char *         pc_l_DisplayTxt;
	char *         pc_l_DisplayAmt;
	unsigned short found;
	DataElement elt;
	char buffer[40];

	// Local variables initialisation
	*PtrUsePinpad = FALSE;
	interfaceok = FALSE;

	CUDB_Get_cardholder_language (&lg_code);

	if (nb_try == 1)
	{
		// message = ENTER PIN
		pc_l_DisplayTxt = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_ENTER_PIN, lg_code);
	}
	else
	{
		// message = TRY AGAIN
		pc_l_DisplayTxt = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_TRY_AGAIN, lg_code);
	}


	pc_l_DisplayAmt = CUMESS_Read_Message(DEFAULT_TABLE, STD_MESS_AMOUNT, lg_code);

#ifdef _USE_UCM_
	if (UCM_Present)
	{
		sprintf(buffer, "%6lu.%02lu ", ul_InputAmount/100, ul_InputAmount%100);
	}
	else
#endif
	{	
		/*&BEGIN FT/08/4015/MA    bad format or forgotten amount */
		if ((ul_InputAmount % 100) != 0)
			sprintf(buffer, "%s:%6lu.%02lu ", pc_l_DisplayAmt, ul_InputAmount/100, ul_InputAmount%100);
		else
			sprintf(buffer, "%s:%8lu ", pc_l_DisplayAmt, ul_InputAmount/100);
		/*&END FT/08/4015/MA    bad format or forgotten amount */
	}
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

#ifdef _USE_UCM_
	if (UCM_Present)
	{
		iLIBUCM_Display_Option( UCMC_DISPLAY, buffer, UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_APPEND, 0 ) ;
		iLIBUCM_Display_Option( UCMC_DISPLAY, "\n", UCMDISPLAY_APPEND , 0 ) ; 
		iLIBUCM_Display_Option( UCMC_DISPLAY, pc_l_DisplayTxt, UCMDISPLAY_APPEND|UCMDISPLAY_CLOSE_AT_END , 0 ) ;

		interfaceok = TRUE;
	}
	else
#endif
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
					*PtrUsePinpad = TRUE;
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
				CUTERMdisplayGraphicLine(2, pc_l_DisplayTxt, CENTER, (char*)"w", FALSE); 
				
				// Restore previous configuration
				InitContexteGraphique(PERIPH_DISPLAY);

				// No pinpad to use, user interface is ok
				interfaceok = TRUE;
			}
			else
			{
				// graphical function can't be used on pinpad
				ret = PPS_Display (pc_l_DisplayTxt);
				interfaceok = (ret != 1);
			}
		}

		else
		{
			// pinpad isn't present or cannot be used
			// No pinpad to use, user interface is ok
			interfaceok = TRUE;
			CUTERMclearDisplay();

			CUTERMdisplayGraphicLine(2, pc_l_DisplayTxt, CENTER, (char*)"w", FALSE); 

			uc_l_DisplayWarningText = 1;
		}

		// Tests if graphical function can be used
		if (uc_l_DisplayWarningText)
		{
			char buffer[40];

			if (*PtrUsePinpad)
				InitContexteGraphique(PERIPH_PPR);
			/*&BEGIN FT/08/4015/MA    bad format or forgotten amount */

			pc_l_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, STD_MESS_AMOUNT, lg_code);

			/*&BEGIN FT/08/4015/MA    bad format or forgotten amount */
			sprintf(buffer, "%s: %lu.%02lu ", pc_l_DisplayTxt, ul_InputAmount/100, ul_InputAmount%100);
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
			/*&END FT/08/4015/MA    bad format or forgotten amount */

			CUTERMdisplayGraphicLine(0, buffer, CENTER, (char*)" ", FALSE);

			CUTERM_DefineNewChar();
			pc_l_DisplayTxt = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_PROTECT_ENTER_PIN, lg_code);
			CUTERMdisplayGraphicLine(3, pc_l_DisplayTxt, CENTER, (char*)" ", TRUE);
			pc_l_DisplayTxt = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_PROTECT_ENTER_PIN_L2, lg_code);
			CUTERMdisplayGraphicLine(4, pc_l_DisplayTxt, CENTER, (char*)" ", TRUE);
			CUTERM_RestoreChar();
			if (*PtrUsePinpad)
				// Restore previous configuration
				InitContexteGraphique(PERIPH_DISPLAY);
		}
	}

	return (interfaceok);
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
//! \return The encipherement result : 
//! - PP_HS : Problem with PINPAD, or with the booster.
//! - CU_INPUT_PIN_OK : PIN entry and encipherement was successfull.
//! - CANCEL_INPUT : PIN entry was canceled.
//! - TO_INPUT : Time-out during PIN entry.
//===========================================================================
static unsigned char EnterPin(int nb_try,
							  ENTRY_BUFFER *buffer,
							  int type_pin,
							  unsigned char PPTestType,
							  unsigned char ForceKsu,
							  unsigned char AllowTermIfPPadHS)
{
	unsigned char cr_enter_pin;
	unsigned char KeyFunction;
	int           PinPadUsed, pinpadok;

	// Local variables initialisation
	cr_enter_pin = CANCEL_INPUT;

	pinpadok = DisplayEnterPinMsg(nb_try, PPTestType, AllowTermIfPPadHS, &PinPadUsed);

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

	cr_enter_pin = ManageKeys(buffer,
		ForceKsu,		// Manage ksu
		KeyFunction,	// Allow functions to obtain keys
		PinPadUsed,PinpadValue, type_pin);	// pinpad must be used if present
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
static unsigned char SelectInputKeyMethod (int nb_try, ENTRY_BUFFER *buffer, unsigned char type_pin, unsigned char AllowTermIfPPadHS)
{
	char          Method_selector;
	unsigned char ForceKsu;
	unsigned char cr_enter_pin;
	unsigned char PPTestType;


	// Default values initialisation
	Method_selector = CU_NO_METHOD_FIXED;
	ForceKsu        = FALSE;
	cr_enter_pin    = PP_HS;
	PPTestType      = CU_PPTEST_NOTEST;


	/******************************/
	/* Witch method may be used ? */
	/******************************/

#ifdef _USE_UCM_
	if (UCM_Present)
	{
		if (type_pin == CUP_PIN_OFFLINE)
			Method_selector = CU_METHOD_UCM_WITH_CLOSE;
		else if (type_pin == CUP_PIN_ONLINE)
			Method_selector = CU_METHOD_UCM;
	}
	else
#endif

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
					cr_enter_pin = EnterPin(nb_try, buffer, type_pin, PPTestType, ForceKsu, AllowTermIfPPadHS);
					break;

				case CU_METHOD_EXT_WITH_SCHEMES:
					break;

				default:
					cr_enter_pin = PP_HS;
					break;
				}

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
//! \return The encipherement result : 
//! - PP_HS : Problem with the pinpad, or with the booster.
//! - CU_INPUT_PIN_OK : PIN entry and encipherement was successfull.
//! - CANCEL_INPUT : PIN entry was canceled.
//! - TO_INPUT : Time-out during PIN entry.
//===========================================================================
static unsigned char ManageKeys(ENTRY_BUFFER *buffer,
								unsigned char ForceKsu,
								unsigned char KeyFunction,
								int isPinpad, int PinpadValue,int type_pin)
{
	short          wait_input, TO_inter_car, TO_first_car;
	T_Bool         cr;
	T_CUTERMkey    key;
	unsigned char  text[40];
	unsigned char  end_enter_pin;
	unsigned char  cr_enter_pin;
	int            cr_initsch, cr_endsch;
	int            ksu_sch;
	int            range;
	int            firstCar, column;
	unsigned long  fct_ksu;
	FILE           *iapp;
	unsigned int   ihid_key;
	unsigned char ucdataout;
	unsigned int uiEventToWait;
	int ibToContinue;
	unsigned  char index;

	// Local variables initialisation
	TO_inter_car  = 0;
	TO_first_car  = 0;
	ksu_sch       = FALSE;
	cr            = B_TRUE;
	iapp          = NULL;

	end_enter_pin = FALSE;
	range        = 0;
	buffer->d_len= 0;
	firstCar      = 0;
	cr_enter_pin  = CANCEL_INPUT;
	column        = 4;

	CUDB_GetParamPINCode (&TO_inter_car, &TO_first_car, &fct_ksu);

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

	while(!end_enter_pin)
	{
		if ((ksu_sch) && (KeyFunction & CU_SCH_GETKEY))
		{
			cr = CU_SchGetKey( &key, ihid_key);
			if ( cr == B_FALSE)
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

		if ( cr == B_TRUE)
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
				if (range == 0)
				{
					*ptr_Bypass_Required = TRUE;
				}
				buffer->d_len=range;
				cr_enter_pin  = CU_INPUT_PIN_OK;
				end_enter_pin = TRUE;
				break;

			case CANCEL   : 
				// cancel the enter pin
				buffer->d_len=0;
				cr_enter_pin  = CANCEL_INPUT;
				end_enter_pin = TRUE;
				break;

			case CORRECT:
				// correction
				if (range!=0)
				{
					column = column-1;
					if ((isPinpad == B_TRUE) && (!CUTERMIsGraphicPP()) && (!ForceKsu))
					{
						int index;

						memset( (char *)text, 0, 20 );
						PPS_clearline ();

						for (index = 0; index < range - 1; index++)
						{
							strcat ((char *)text, "*");
						}
						PPS_Display ( (char *)text);
					}
					else
					{
						strcpy((char *)text, " ");
						strcpy((char*)text, "   ");
						for (index = 4; index<column; index++)
							strcat((char*)text, "*");
#ifdef _USE_UCM_			                      
						if (UCM_Present)
						{
							iLIBUCM_Display_Option( UCMC_DISPLAY, (char*)text, UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_APPEND, 0 ) ;
						}
						else
#endif
						{
							strcat((char*)text, " ");
							if (isPinpad)
								InitContexteGraphique(PERIPH_PPR);
							CUTERMdisplayGraphicLine(2, (char *)text, LEFT, (char*)" ", FALSE);
							if (isPinpad)
								InitContexteGraphique(PERIPH_DISPLAY);
						}
					}
					range = range-1;
				}
				break;

			default:
				// correction
				// Note : Numeric key sent by shemes is always 0x30 for input key 0 to 9
				if ( (key<=0x39) && (key>=0x30) && (range < 13) )
				{
					if (range ==0)
					{
						strcpy((char *)text, "                   ");
						if ((isPinpad == B_TRUE) && (!CUTERMIsGraphicPP()) && (!ForceKsu))
						{
							PPS_clearline ();
						}
						else
						{
#ifdef _USE_UCM_
							if (UCM_Present)
							{
								strcpy((char *)text, "   ");
								iLIBUCM_Display_Option( UCMC_DISPLAY, (char*)text, UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_APPEND, 0 ) ;
							}
							else
#endif 
							{
								if (isPinpad)
									InitContexteGraphique(PERIPH_PPR);
								CUTERMdisplayGraphicLine(2, (char *)text, LEFT, (char*)" ", FALSE);
								if (isPinpad)
									InitContexteGraphique(PERIPH_DISPLAY);
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
						strcpy((char*)text, "   *");
						for (index = 4; index<column; index++)
							strcat((char*)text, "*");
						strcat((char*)text, " ");
#ifdef _USE_UCM_
						if (UCM_Present)
						{
							iLIBUCM_Display_Option( UCMC_DISPLAY, "*", UCMDISPLAY_APPEND , 0 ) ;
						}
						else
#endif
						{
							if (isPinpad)
								InitContexteGraphique(PERIPH_PPR);
							CUTERMdisplayGraphicLine(2, (char *)text, LEFT, (char*)" ", FALSE);
							if (isPinpad)
								InitContexteGraphique(PERIPH_DISPLAY);
						}
					}

					buffer->d_entry[range++] = (unsigned char) key;
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

			if ((TransactionLoopMode != TRUE)||(loop_amount == 0))
			{
				cr_endsch = SEC_PinEntry (&uiEventToWait,&ucdataout, &ibToContinue);
			}
			// use TRACE  Id 0xA000 : my application
			trace(0x0F02,strlen("fin pin entry"),"fin pin entry");
		}

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
static T_Bool CU_SchGetKey(  T_CUTERMkey *xp_key,unsigned int ihid_key)
{
	int s_ibPinpadBoost;
	T_Bool       res_key;
	int iret;
	unsigned int Key; 
	unsigned char ucdataout;
	unsigned int uiEventToWait;
	int ibToContinue;
	char str[50];


	res_key = TRUE;
	s_ibPinpadBoost = FALSE;

	ibToContinue = TRUE;

	if (!s_ibPinpadBoost)
		uiEventToWait = 0;
	else
		// waiting event EFT keyboard
		uiEventToWait = KEYBOARD;
	
	// use TRACE  Id 0xA000 : my application
	trace(0x0F02,strlen("begin pin entry"),"begin pin entry");

	if ((TransactionLoopMode == TRUE)&&(loop_amount != 0))
	{
		iret = ERR_ENTRY_CANCELED;
	}
	else
	{
		iret = SEC_PinEntry (&uiEventToWait,&ucdataout, &ibToContinue);
	}
	//sprintf(str, "SEC_PinEntry %d\n",iret);
	
	// use TRACE  Id 0xA000 : my application
	trace(0x0F02,strlen(str),str);



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
					res_key = FALSE;
					upload_diagnostic_txt((unsigned char*)"Time out \n");
					break;
				case 0x01: 
					upload_diagnostic_txt((unsigned char*)"PIN CANCEL\n");	// 
					res_key = FALSE;
					break;
				case T_VAL :
					*xp_key = CU_VALID; 
					break;
				case T_ANN:
					*xp_key = CANCEL; 
					upload_diagnostic_txt((unsigned char*)"PIN Annulation\n"); 
					break;
				case T_CORR:
					*xp_key = CORRECT; 
					upload_diagnostic_txt((unsigned char*)"PIN Correction\n"); 
					break;
		}
	}
	else if (iret == ERR_TIMEOUT)
	{
		upload_diagnostic_txt((unsigned char*)"Time out \n");
		res_key = FALSE;
	}
	else
	{
		upload_diagnostic_txt((unsigned char*)" Errors detected\n"); 
		res_key = FALSE;
	}


	return(res_key);
}

//===========================================================================
//! \brief This function sets the value of the the parameter PinpadValue, according 
//! to the pinpad type.
//! \param[out] PinpadValue : type of the pinpad
//===========================================================================
static void CU_SetConfPinpad (int * PinpadValue)
{


#ifdef _USE_UCM_
	if (!UCM_Present)
	{
#endif
			*PinpadValue=0xff;
			*PinpadValue = PSQ_Pinpad_Value();
#ifdef _USE_UCM_
	}
#endif

}

//===========================================================================
//! \brief This function initialises the structure for the following secured PIN code entry.
//! \param[in] TO_inter_car : inter character timeout.
//! \param[in] TO_first_car : first character timeout.
//! \param[out] ihid_key : character displayed to hide real character entered.
//! \param[in] type_pin : indicates the PIN code type : 
//! - CUP_PIN_OFFLINE.
//! - CUP_PIN_ONLINE.
//! \return
//! TRUE if the parameters allow to enter the PIN code on the terminal 
//! when a card is inserted in the terminal, whereas a p30 is present.
//===========================================================================
int  CU_SetPinEntry ( short TO_inter_car, short TO_first_car,unsigned int * ihid_key, int type_pin)
{
	T_SEC_ENTRYCONF stEntryConfig;
	int iret,pinplace;
	char str[50];

	*ihid_key= 0x2A;
	stEntryConfig.ucEchoChar = *ihid_key;
	stEntryConfig.ucMinDigits = 4;
	stEntryConfig.ucMaxDigits = 12;
	stEntryConfig.iFirstCharTimeOut = ((int)TO_first_car) * 10;
	stEntryConfig.iInterCharTimeOut = ((int)TO_inter_car) * 10;

#ifdef _USE_UCM_
	if (UCM_Present)
	{
		// hypothesis : with Custom security DLL use EMVDC using security DLL.
		pinplace = C_SEC_PINCODE;
	}
	else
#endif
	{
		if ( type_pin == CUP_PIN_OFFLINE)  
			pinplace = C_SEC_CARD;
		else
			pinplace = C_SEC_PINCODE;
	}

	// use TRACE  Id 0xA000 : my application
	trace(0x0F02,strlen("SEC_PinEntryInit"),"SEC_PinEntryInit");

	iret = SEC_PinEntryInit (&stEntryConfig,pinplace);
	
	// use TRACE  Id 0xA000 : my application
	trace(0x0F02,strlen("end SEC_PinEntryInit"),"end SEC_PinEntryInit");

	sprintf(str, "SEC_PinEntryInit %d\n",iret);
	upload_diagnostic_txt((unsigned char*)str);

	return iret;
}

//! @}

