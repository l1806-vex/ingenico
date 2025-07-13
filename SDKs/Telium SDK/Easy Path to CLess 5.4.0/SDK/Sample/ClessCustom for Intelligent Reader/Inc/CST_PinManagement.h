/**
 * \file	CST_PinManagement.h
 * \brief	Module that manages the online PIN entry and ciphering.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2008 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __CST_PIN_H__INCLUDED__
#define __CST_PIN_H__INCLUDED__

//! \defgroup Group_cu_pin PIN code entry management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define  ERROR_INPUT								70		//<! Pin code input error.

#define TAG_CST_ENCIPHERED_PIN_CODE					0x9F918849		/*!< CST tag : Enciphered pin code for on-line verification. */

/* ======================================================================== */
/* Types declarations                                                       */
/* ======================================================================== */

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

// The common boolean type
typedef enum 
{
	B_FALSE = FALSE,
	B_TRUE  = TRUE,
	B_NON_INIT  = 0xFF
} T_Bool;


typedef enum
{
    ZERO = T_NUM0,
    ONE = T_NUM1,
    TWO = T_NUM2,
    THREE = T_NUM3,
    FOUR = T_NUM4,
    FIVE = T_NUM5,
    SIX = T_NUM6,
    SEVEN = T_NUM7,
    EIGHT = T_NUM8,
    NINE = T_NUM9,
    T_F1 = T_SK1,
    T_F2 = T_SK2,
    T_F3 = T_SK3,
    T_F4 = T_SK4,
    CU_T_POINT = T_POINT,
    T_STAR = 0x07,
    CU_VALID = T_VAL,
	CORRECT = T_CORR,
	CANCEL = T_ANN
} T_CUTERMkey;

// Exchange with Input Pin Scheme via IAPP
typedef enum
   {
   K_VALID =   0x01,
   K_CORRECT = 0x02,
   K_CANCEL =  0x03,
   K_TIMEOUT = 0x04,
   K_HID_NUM = '*'
   } T_KSUkey;
   
typedef struct {
	int iCiphMode;		/*!< CLEAR_DATA_MODE, DES_CIPHERED_MODE or TDES_CIPHERED_MODE */
	int iSecretId; // Secret Area Id of the ciphering Key
	int iIdKey;    // Id of the ciphering Key
} T_CIPHERTLV;

typedef struct
{
	unsigned int uiMessageLength;
	unsigned char ucMessage[32]; // Message can be truncated depending on the device
} PIN_MESSAGE;


typedef struct
{
	unsigned long ulTimeoutBefore;
	unsigned long ulTimeoutInter;
} PIN_TXT_STRUCT;


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief This function manage the online pin.
//! \param[in] pan card PAN.
//! \param[in] nb_try : number of PIN entry attempts.
//! \param[in] ulAmount amount to display.
//! \param[in] ulTimeoutBefore				= Timeout for first PIN key entry (in milliseconds).
//! \param[in] ulTimeoutInterCharacter		= Timeout between two PIN key entries (in milliseconds).
//! \param[out] buffer buffer containing the cyphered PIN code.
//! \return
//! TRUE if the parameters allow to enter the PIN code on the terminal 
//! when a card is inserted in the terminal, whereas a p30 is present.

unsigned char CST_PinManagement_OnLinePinManagement (unsigned char * ucPAN,
									   unsigned char nb_try,
								       unsigned long ulAmount,
									   unsigned long ulTimeoutBefore, 
									   unsigned long ulTimeoutInterCharacter,
									   BUFFER_SAISIE * buffer);



//! \brief check if a PinPad is declared in the manager.
//! return 
//! - B_TRUE if an initialised PinPad is connected
//! - B_FALSE else.

T_Bool CST_IsPinpadPresent(void);



//! \brief This function tests if graphical functions can be used on PPAD.
//! \return
//!		- \ref TRUE : graphical functions can be used on PPAD.
//!		- \ref FALSE : graphical functions cannot be used on PPAD.

char CST_UseGraphicalFunctionOnPPAD(void);


#endif // __CST_PIN_H__INCLUDED__
