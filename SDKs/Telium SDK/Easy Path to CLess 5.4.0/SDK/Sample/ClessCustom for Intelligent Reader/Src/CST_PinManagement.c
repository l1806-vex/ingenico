/**
* \file CST_PinManagement.c
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

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "CST_Implementation.h"

//! \addtogroup Group_cu_pin
//! @{

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

typedef enum PIN_RESULT
{
    C_PIN_INPUTED = 0,
    C_PIN_NO_INPUTED,
    C_PIN_NO_INPUTED_RECALL,
    C_PIN_CANCELED,
} PIN_RESULT;



#define CU_INPUT_PIN_OK               0

/* Type of PinPad witch must be tested to display text */
#define CU_PPTEST_NOTEST              0
#define CU_PPTEST_CARDONPPAD          1
#define CU_PPTEST_ISPINPAD            2

// Constant used for the DISPLAY peripheral

#define PINPAD						1<< 14

#define C_DEFAULT_TIMEOUT_BEFORE_PIN_INPUT				30000  // 30 seconds
#define C_DEFAULT_TIMEOUT_BETWEEN_PIN_DIGIT_INPUT		10000  // 10 seconds

/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static unsigned short * ptr_Bypass_Required;
static PIN_TXT_STRUCT PIN_UserInterfaceStructure;
static T_Bool isPinpad = B_NON_INIT;

int PinpadValue;
unsigned long ul_InputAmount = 0;


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

// Service to manage Display
static int __CST_DisplayEnterPinMsg(int nb_try, int *PtrUsePinpad);
// Services to manage Schemes
static int  __CST_SetPinEntry ( short TO_inter_car, short TO_first_car,unsigned int * ihid_key);
static unsigned char __CST_EnterPin(int nb_try,BUFFER_SAISIE *buffer);
static PIN_RESULT __CST_SchGetKey(  T_CUTERMkey *xp_key,unsigned int ihid_key);
static unsigned char __CST_ManageKeys(BUFFER_SAISIE *buffer,int isPinpad);
static PIN_RESULT __CST_StopSchGetKey(void);
static void __CST_SetConfPinpad (int * PinpadValue);
static unsigned char __CST_EnterPinOnLine(unsigned char nb_try,
							                     BUFFER_SAISIE *buffer,
							                     unsigned char * ptrPrimaryAccountNumber,
							                     unsigned short * ptrBypass);
static void __CST_SetPinUserInterfaceParameters (unsigned long ulTimeoutBefore, unsigned long ulTimeoutInterCharacter);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Enter pin on-line.
//! \param[in] nb_try : number of PIN entry attempts.
//! \param[out] buffer : buffer containing the cyphered PIN code.
//! \param[in] pan card PAN.
//! \param[out] bypass to make, pin code has been finished by a VALID key press.
//! \return
//!		- \ref entre pin state.

static unsigned char __CST_EnterPinOnLine(unsigned char nb_try,
							                     BUFFER_SAISIE *buffer,
							                     unsigned char * ptrPrimaryAccountNumber,
							                     unsigned short * ptrBypass)
{
	unsigned char cr_enter_pin;
	int           iRes, iLenEnc, cr;
	
	// Header management / display on X07
	StateHeader (0);

	// Global variable affectation for later use
	ptr_Bypass_Required = ptrBypass;
	*ptr_Bypass_Required = FALSE; // Delault value, no bypass needed

	// Inject a dummy secret key in the booster
	__CST_SetConfPinpad (&PinpadValue); 
	
	cr = CST_InjectKey ();
	if (cr != OK)
	{
		// Secret area not created or pb to load key used to encypher PIN
		
		// Header management / display on X07
		StateHeader (1);
		return(NO_INPUT); // 
	}

    cr_enter_pin = __CST_EnterPin(nb_try, buffer);

	if ( cr_enter_pin == CU_INPUT_PIN_OK )
	{
		// Encipher the entered PIN
	
		iRes = CST_OnlineEncipher (ptrPrimaryAccountNumber, buffer->donnees,&iLenEnc);
		if (iRes)
		{
			cr_enter_pin = INPUT_PIN_ON;
			buffer->nombre = (char) iLenEnc;
		}
		else
		{
			cr_enter_pin = PP_HS;
		}
	}
	
	// Header management / display on X07
	StateHeader (1);

	return(cr_enter_pin);
}

//! \brief This function tests if graphical functions can be used on PPAD.
//! \return
//!		- \ref TRUE : graphical functions can be used on PPAD.
//!		- \ref FALSE : graphical functions cannot be used on PPAD.

char CST_UseGraphicalFunctionOnPPAD(void)
{
	// On terminal, we can use graphical function with long text
	unsigned int cr;
	// Default value : no use of pinpad
	char ret = FALSE;

	cr = PSQ_Pinpad_Type();

	switch (cr)
	{
	case PP30_PPAD:
	case pinpad_pp30s:
		ret = FALSE;
		break;
	default :
		ret = TRUE;
		break;
	}
	return (ret);
}


//! \brief This function displays the enter pin message to the user.
//! \param[in] nb_try : number of PIN entry attempts.
//! if the pinpad is here but out of service.
//! \param[out] PtrUsePinpad : boolean indicating if the pinpad can be used.
//! \return
//! - TRUE if a problem exists with the user interface (pinpad access ko).
//! - FALSE otherwise.

static int __CST_DisplayEnterPinMsg(int nb_try, int *PtrUsePinpad)
{
	int           interfaceok;
	char buffer[40];
	char * pc_l_line1 = NULL;
	char * pc_l_line2 = NULL;
	char * pc_l_line3 = NULL;
	char * pc_l_line4 = NULL;
	MSGinfos tMSG;
	MSGinfos tMSGAmount;
	MSGinfos tMSGPin;
	MSGinfos tMSGSafe1;
	MSGinfos tMSGSafe2;
	
	// Local variables initialisation
	*PtrUsePinpad = FALSE;
	interfaceok = FALSE;


    // Check If PinPad is present

	// If a pinpad is declared
	*PtrUsePinpad = (int)CST_IsPinpadPresent();

	/////////////////////////////////////////////////////////
	// Set the amount message
	GetMessageInfos(STD_MESS_AMOUNT, &tMSG);
	
	if ((ul_InputAmount % 100) != 0)
		sprintf(buffer, "%s%lu.%02lu %s\n", tMSG.message, ul_InputAmount/100, ul_InputAmount%100, CST_Term_GiveMoneyLabel());
	else
		sprintf(buffer, "%s%lu %s\n", tMSG.message, ul_InputAmount/100, CST_Term_GiveMoneyLabel());

	tMSGAmount.coding = tMSG.coding;
	tMSGAmount.file = tMSG.file;
	tMSGAmount.message = buffer;
    pc_l_line1 = tMSGAmount.message;

	Helper_DisplayPinText(ERASE, 0, &tMSGAmount, HELPERS_ALIGN_CENTER);

	if (nb_try == 1)
	{
		/////////////////////////////////////////////////////////
		// Set the Pin entry message
		// message = ENTER PIN
		if(!CST_VisaWave_IsVisaAsiaGuiMode())
			GetMessageInfos(STD_MESS_ENTER_PIN, &tMSGPin);
		else
			GetMessageInfos(VISAWAVE_MESS_ENTER_PIN, &tMSGPin);
	}
	else
	{
		/////////////////////////////////////////////////////////
		// Set the retry message
		// message = TRY AGAIN
		GetMessageInfos(STD_MESS_TRY_AGAIN, &tMSGPin);
	}
    Helper_DisplayPinText(NO_ERASE, 1, &tMSGPin, HELPERS_ALIGN_CENTER);
    pc_l_line2 = tMSGPin.message;
                  

	/////////////////////////////////////////////////////////
	// Set the protect message
	GetMessageInfos(STD_MESS_ENTER_PIN, &tMSGSafe1);
    Helper_DisplayPinTextLong(NO_ERASE, 2, &tMSGSafe1, HELPERS_ALIGN_CENTER);
    pc_l_line3 = tMSGSafe1.message;
	
	GetMessageInfos(STD_MESS_SAFE, &tMSGSafe2);
    Helper_DisplayPinTextLong(NO_ERASE, 3, &tMSGSafe2, HELPERS_ALIGN_CENTER);
    pc_l_line4 = tMSGSafe2.message;

	return (TRUE);
}


//! \brief This function performs the PIN code entry.
//! This function must select cases where each key may be managed or
//! only final result with OK, CANCEL, CORRECT, TIME_OUT.
//! \param[in] nb_try : number of PIN entry attempts.
//! \param[out] buffer : buffer containing the cyphered PIN code.
//! if the pinpad is here but out of service.
//! \return The encipherement result : 
//! - PP_HS : Problem with PINPAD, or with the booster.
//! - CU_INPUT_PIN_OK : PIN entry and encipherement was successfull.
//! - CANCEL_INPUT : PIN entry was canceled.
//! - TO_INPUT : Time-out during PIN entry.

static unsigned char __CST_EnterPin(int nb_try, BUFFER_SAISIE *buffer)
{
	unsigned char cr_enter_pin;
	int           PinPadUsed, pinpadok;

	pinpadok = __CST_DisplayEnterPinMsg(nb_try, &PinPadUsed);

	if (pinpadok != TRUE)
		// Error management
		return (PP_HS);


	cr_enter_pin = __CST_ManageKeys(buffer, PinPadUsed);	// pinpad must be used if present
	
	return(cr_enter_pin);
}


//! \brief This function manages each key input.
//! \param[out] buffer : buffer to store keys.
//! \param[in] isPinpad : boolean indicating if pinpad can be used.
//! \return The encipherement result : 
//! - PP_HS : Problem with the pinpad, or with the booster.
//! - CU_INPUT_PIN_OK : PIN entry and encipherement was successfull.
//! - CANCEL_INPUT : PIN entry was canceled.
//! - TO_INPUT : Time-out during PIN entry.

static unsigned char __CST_ManageKeys(BUFFER_SAISIE *buffer, int isPinpad)
{
	char  text[40];
	unsigned char  end_enter_pin;
	unsigned char  cr_enter_pin;
	int            indice;
	int            firstCar, column;
	unsigned int   ihid_key;
	MSGinfos       MSGTmp;
	T_CUTERMkey    key = 0;
	PIN_RESULT     cr;
	
	// Local variables initialisation
	end_enter_pin = FALSE;
	indice        = 0;
	buffer->nombre= 0;
	firstCar      = 0;
	cr_enter_pin  = CANCEL_INPUT;
	column        = 4;

    // SEC_PinEntryInit ...	
	if (__CST_SetPinEntry(PIN_UserInterfaceStructure.ulTimeoutInter, PIN_UserInterfaceStructure.ulTimeoutBefore, &ihid_key) != OK)
	    return (CANCEL_INPUT); // A problem occurs

	MSGTmp.coding = _ISO8859_;
	MSGTmp.file = GetCurrentFont();

	while(!end_enter_pin)
	{
		cr = __CST_SchGetKey( &key, ihid_key);
		if ( cr == C_PIN_NO_INPUTED)
		{
			cr_enter_pin  = TO_INPUT;
			end_enter_pin = TRUE;
		}
		else if ( cr == C_PIN_CANCELED)
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
			}

			switch (key)
			{
			case CU_VALID : 
				// end of the enter pin
				if (indice == 0)
				{
					*ptr_Bypass_Required = TRUE;
				}
				buffer->nombre=indice;
				cr_enter_pin  = CU_INPUT_PIN_OK;
				end_enter_pin = TRUE;
				break;

			case CANCEL   : 
				// cancel the enter pin
				buffer->nombre=0;
				cr_enter_pin  = CANCEL_INPUT;
				end_enter_pin = TRUE;
				break;

			case CORRECT:
				// correction
				if (indice!=0)
				{
					column = column-1;
					if (isPinpad == B_TRUE)
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
						int index;
						
						strcpy((char *)text, " ");
						strcpy(text, "   ");
						for (index = 4; index<column; index++)
							strcat(text, "*");
						strcat(text, " ");
						MSGTmp.message = text;
						
                        Helper_DisplayPinText(NO_ERASE, 1, &MSGTmp, HELPERS_ALIGN_LEFT);
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
						if (isPinpad == B_TRUE)
						{
							PPS_clearline ();
						}
						else
						{
							MSGTmp.message = text;
                            Helper_DisplayPinText(NO_ERASE, 1, &MSGTmp, HELPERS_ALIGN_LEFT);
						}
						column = 4;
					}
					strcpy((char *)text, "*");

					if (isPinpad == B_TRUE)
					{
						PPS_Display ( (char *)text);
					}
					else
					{
						int index;
						
						strcpy(text, "   *");
						for (index = 4; index<column; index++)
							strcat(text, "*");
						strcat(text, " ");
						
						MSGTmp.message = text;
                        Helper_DisplayPinText(NO_ERASE, 1, &MSGTmp, HELPERS_ALIGN_LEFT);
					}

					buffer->donnees[indice++] = (unsigned char) key;
					column ++;
				}
				break;
			}
		}   //End Else Key has been inputed */
		else if (cr == C_PIN_NO_INPUTED_RECALL)
		{
    		
        }
	} // end while(!end_enter_pin)

	return (cr_enter_pin);
}


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
//! - B_NON_INIT key not inputed but fonction release allows to manage html browser : this function must be called back later.
//! - TRUE a key has been read.
//! - FALSE timeout expired or K_TIMEOUT has been read.

static PIN_RESULT __CST_SchGetKey(  T_CUTERMkey *xp_key,unsigned int ihid_key)
{
	int iret;
	int s_ibPinpadBoost;
	unsigned int Key; 
	unsigned char ucdataout;
	unsigned int uiEventToWait = 0;
    int ibToContinue;
	PIN_RESULT res_key;


    // Initialisation
	res_key = C_PIN_INPUTED; // Default value
	s_ibPinpadBoost = FALSE;
	ibToContinue = TRUE;

    // Warning, if a pinPad is present, KEYBOARD event is allowed to stop the SEC_PinEntry execution by a key pressed on the terminal keyboard
    if (CST_IsPinpadPresent())
        uiEventToWait = KEYBOARD;
    
    // USER_EVENT_PIN is given by periodic task. This event allows to suspend the SEC_PinEntry scheme execution.
	uiEventToWait |= USER_EVENT_PIN; // USER_EVENT_PIN is given by periodic task
	

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
						GTL_Traces_TraceDebug("__CST_SchGetKey : Time out\n");
						break;
					case 0x01: 
						GTL_Traces_TraceDebug("__CST_SchGetKey : PIN CANCEL\n");	// 
						res_key = C_PIN_NO_INPUTED;
						break;
					case T_VAL : // Nominal case : no trace
						*xp_key = CU_VALID; 
						GTL_Traces_TraceDebug("__CST_SchGetKey : PIN valid)\n"); 
						break;
					case T_ANN:
						*xp_key = CANCEL; 
						GTL_Traces_TraceDebug("__CST_SchGetKey : PIN Annulation\n"); 
						break;
					case T_CORR:
						*xp_key = CORRECT; 
						GTL_Traces_TraceDebug("__CST_SchGetKey : PIN Correction\n"); 
						break;
		}
	}
	else if (iret == ERR_TIMEOUT)
	{
	    if (uiEventToWait == USER_EVENT_PIN) // No information inputed and no time-out, it's an event used to suspend SEC_PinEntry temporary
	    {
		    GTL_Traces_TraceDebug("__CST_SchGetKey : release");
			res_key = C_PIN_NO_INPUTED_RECALL; // Please, call back this function later
		}
		else if (uiEventToWait == KEYBOARD) // Keyboard event (comming from terminal when ppinpad is used)
		{
		    Key = getchar(); // Which key ?
		
		    GTL_Traces_TraceDebug("__CST_SchGetKey : keyboard evt %x", Key);
		    if (Key == T_ANN) // If key is cancel => stop PinPad Pin input
		    {
			    res_key = C_PIN_CANCELED; // Pin input stopped by Cancel key pressed on terminal
			    __CST_StopSchGetKey(); // To stop SEC_PinEntry scheme
    		}
		    else
		    {
		          // Key not managed
    			res_key = C_PIN_NO_INPUTED_RECALL; // Please, call back this function later
            }
		}
		else
		{
		    GTL_Traces_TraceDebug("__CST_SchGetKey : Time out %x\n", uiEventToWait);
		    res_key = C_PIN_NO_INPUTED;
		}
	}
	else
	{
		GTL_Traces_TraceDebug("__CST_SchGetKey : Errors detected\n"); 
	    res_key = C_PIN_NO_INPUTED;
	}

	return(res_key);
}


//! \brief This function stop SEC_PinEntry scheme.
//! \return
//! - B_NON_INIT key not inputed but fonction release allows to manage html browser : this function must be called back later.
//! - TRUE a key has been read.
//! - FALSE timeout expired or K_TIMEOUT has been read.

static PIN_RESULT __CST_StopSchGetKey(void)
{
	int iret;
	unsigned char ucdataout;
	unsigned int uiEventToWait = 0;
    int ibToContinue = FALSE;


	iret = SEC_PinEntry (&uiEventToWait,&ucdataout, &ibToContinue);

	return(iret);
}


//! \brief This function sets the value of the the parameter PinpadValue, according 
//! to the pinpad type.
//! \param[out] PinpadValue : type of the pinpad

static void __CST_SetConfPinpad (int * PinpadValue)
{
	*PinpadValue=0xff;
	*PinpadValue = PSQ_Pinpad_Value();
}


//! \brief Set the PIN UI parameters.
//! \param[in] ulTimeoutBefore         = Timeout for first PIN key entry (in milliseconds).
//! \param[in] ulTimeoutInterCharacter = Timeout between two PIN key entries (in milliseconds).
//! \return
//! - void.

static void __CST_SetPinUserInterfaceParameters (unsigned long ulTimeoutBefore, unsigned long ulTimeoutInterCharacter)
{
	/////////////////////////////////////////////////////////
	// Set the Timeout before any key for PIN entry is pressed
	if (ulTimeoutBefore != 0)
		PIN_UserInterfaceStructure.ulTimeoutBefore = ulTimeoutBefore;
	else
		PIN_UserInterfaceStructure.ulTimeoutBefore = C_DEFAULT_TIMEOUT_BEFORE_PIN_INPUT;

	/////////////////////////////////////////////////////////
	// Set the Timeout between two digits entry for PIN
	if (ulTimeoutInterCharacter != 0)
		PIN_UserInterfaceStructure.ulTimeoutInter = ulTimeoutInterCharacter;
	else
		PIN_UserInterfaceStructure.ulTimeoutInter = C_DEFAULT_TIMEOUT_BETWEEN_PIN_DIGIT_INPUT;
}


//! \brief This function initialises the structure for the following secured PIN code entry.
//! \param[in] TO_inter_car : inter character timeout.
//! \param[in] TO_first_car : first character timeout.
//! \param[out] ihid_key : character displayed to hide real character entered.
//! \return
//! TRUE if the parameters allow to enter the PIN code on the terminal 
//! when a card is inserted in the terminal, whereas a p30 is present.

static int __CST_SetPinEntry ( short TO_inter_car, short TO_first_car,unsigned int * ihid_key)
{
	T_SEC_ENTRYCONF stEntryConfig;
	int iret,pinplace;

	*ihid_key= 0x2A;
	stEntryConfig.ucEchoChar = *ihid_key;
	stEntryConfig.ucMinDigits = 4;
	stEntryConfig.ucMaxDigits = 12;
	stEntryConfig.iFirstCharTimeOut = TO_first_car;
	stEntryConfig.iInterCharTimeOut = TO_inter_car;

	pinplace = C_SEC_PINCODE;

	iret = SEC_PinEntryInit (&stEntryConfig,pinplace);
    if (iret != OK)
	    GTL_Traces_TraceDebug("SEC_PinEntryInit error %d", iret);

	return iret;
}


//! \brief This function manage the online pin.
//! \param[in] pan card PAN.
//! \param[in] nb_try : number of PIN entry attempts.
//! \param[in] ulAmount amount to display.
//! \param[in] ulTimeoutBefore         = Timeout for first PIN key entry (in milliseconds).
//! \param[in] ulTimeoutInterCharacter = Timeout between two PIN key entries (in milliseconds).
//! \param[out] buffer buffer containing the cyphered PIN code.
//! \return
//! TRUE if the parameters allow to enter the PIN code on the terminal 
//! when a card is inserted in the terminal, whereas a p30 is present.

unsigned char CST_PinManagement_OnLinePinManagement (unsigned char * ucPAN,
														     unsigned char nb_try,
														     unsigned long ulAmount,
														     unsigned long ulTimeoutBefore, 
														     unsigned long ulTimeoutInterCharacter,
														     BUFFER_SAISIE * buffer)
{
	unsigned char  cr_enter_pin;
	unsigned short Bypass_Required;
	
	__CST_SetPinUserInterfaceParameters (ulTimeoutBefore, ulTimeoutInterCharacter);

    // To update : ul_InputAmount
    ul_InputAmount = ulAmount;
	
	// Online PIN management
    cr_enter_pin = __CST_EnterPinOnLine(nb_try, buffer, ucPAN, &Bypass_Required);
    return(cr_enter_pin);
}



//! @}


//! \brief check if a PinPad is declared in the manager.
//! return 
//! - B_TRUE if an initialised PinPad is connected
//! - B_FALSE else.

T_Bool CST_IsPinpadPresent(void)
{
	int cr;

	if ( isPinpad == B_NON_INIT)
	{
		cr = PSQ_Is_pinpad();
		if (cr == 1)
		{
			if(IsPPSConnected() == 0)
    			isPinpad = B_TRUE;
	   		else
	    		isPinpad = B_FALSE;
		}
		else
		{
			isPinpad = B_FALSE;
		}
	}

	return(isPinpad);

}	// end of CST_IsPinpadPresent

