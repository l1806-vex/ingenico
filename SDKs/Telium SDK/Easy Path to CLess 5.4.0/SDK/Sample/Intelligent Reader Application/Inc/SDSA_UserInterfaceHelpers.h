/**
 * \file	CST_UserInterfaceHelpers.h
 * \brief 	Module that manages the user interface.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __SDSA_UIHELPERS_H__INCLUDED__
#define __SDSA_UIHELPERS_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define ERASE						TRUE
#define NO_ERASE					FALSE

#define LEDSOFF						TRUE
#define NOLEDSOFF					FALSE

#define WITHBEEP					TRUE
#define WITHOUTBEEP					FALSE

// Output display alignment
#define HELPERS_ALIGN_LEFT				(1)
#define HELPERS_ALIGN_CENTER			(2)
#define HELPERS_ALIGN_RIGHT				(3)

// Customer display lines
#define HELPERS_CUSTOMER_LINE_1				(0)
#define HELPERS_CUSTOMER_LINE_2				(1)
#define HELPERS_CUSTOMER_LINE_3				(2)
#define HELPERS_CUSTOMER_LINE_4				(3)
#define HELPERS_CUSTOMER_LINE_5				(4)
#define HELPERS_CUSTOMER_LINE_6				(5)

// Time on and time off for blinking leds
#define VISA_ASIA_LED_BLINK_ON					(17)			/*!< 340 ms. */
#define VISA_ASIA_LED_BLINK_OFF					(17)			/*!< 340 ms. */

// Indicates if it is a payWave or a VisaWave transaction
#define HELPERS_PAYWAVE						1
#define HELPERS_VISAWAVE					2

// Indicates if it is an offline or an online transaction
#define OFFLINE								1
#define ONLINE								2

// Indicates if Available Offline Spending Amount is displayed or not
#define WITH_AOSA							1
#define WITHOUT_AOSA						0


//// Types //////////////////////////////////////////////////////


//// Global variables ///////////////////////////////////////////


//// Functions //////////////////////////////////////////////////

//! \brief This function displays a text on the cless reader (screen is not refreshed)
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.

void _Helper_DisplayTextCustomer(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char bLedsOff);


//! \brief This function displays a text on the cless reader (screen is refreshed)
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.

void Helper_DisplayTextCustomer(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char bLedsOff);

//! \brief This function gets a message and displays it on the cless reader (screen is refreshed)
//! \param[in] nNum : message number.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.

void _Helper_DisplayMessage(int nNum, int nEraseDisplay, int nLineNumber, int nAlignment, unsigned char bLedsOff);


//! \brief This function gets a message and displays it on the cless reader (screen is refreshed)
//! \param[in] nNum : message number.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.

void Helper_DisplayMessage(int nNum, int nEraseDisplay, int nLineNumber, int nAlignment, unsigned char bLedsOff);


//! \brief Process the remove card sequence (buzzer, Leds) and displays the correct message.
//! \param[in] pSharedData Data structure containing the customisation data (step ID, and prefered selected language if present).

void HelperRemoveCardSequence (T_SHARED_DATA_STRUCT * pSharedData);


//! \brief Process the represent card sequence.
//! \param[in] pSharedData Data structure containing the customisation data (prefered selected language if present).

void HelperRepresentCardSequence (T_SHARED_DATA_STRUCT * pSharedData);


//! \brief Process the error sequence (double beep, leds off).
//! \param[in] nWithBeep = TRUE if beep must be made,

void HelperErrorSequence(int nWithBeep);


//! \brief Wait allowing user to see srceen message.

void Helper_WaitUserDisplay(void);


//! \brief This function wait 750ms to see LEDS.

void HelperWaitLedsTime(void);


//! \brief Wait 750ms and set LEDS off.

void HelperLedsOff(void);


//! \brief This function set the LEDs into the idle state.

void HelperLedsIdleState(void);


//! \brief Third light is on and beep beep sound.

void Helper_PerformOKSequence (void);


//! \brief Fourth light blinking and beep beep sound.

void Helper_PerformKOSequence (void);


//! \brief Third light blinking and beep sound.

void Helper_PerformOfflineSequence (void);


//! \brief Third light blinking.

void Helper_PerformOnlineSequence (void);


//! \brief Third light blinking and beep sound.

void Helper_PerformCVMSequence (void);


//! \brief Perform the signature CVM IHM.

void Helper_Visa_SignatureCVMIHM(void);


//! \brief Perform the IHM for an approved transaction (either offline or online).
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction
//! \param[in] nAOSA : with Available Offline Spending Amount : WITH_AOSA or WITHOUT_AOSA

void Helper_Visa_ApprovedIHM(const int nOfflineOnline,const int nAOSA);


//! \brief Perform the IHM when the Signature CVM is OK.

void Helper_Visa_SignatureOKIHM(void);


//! \brief Perform the IHM when the Signature CVM is KO.

void Helper_Visa_SignatureKOIHM(void);


//! \brief Perform the IHM when the PIN Entry CVM is KO.

void Helper_Visa_PinEntryKOIHM(const int bPINCanceled);


//! \brief Perform the IHM for a declined transaction (either offline or online).
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction
//! \param[in] nAOSA : with Available Offline Spending Amount : WITH_AOSA or WITHOUT_AOSA

void Helper_Visa_DeclinedIHM(const int nOfflineOnline,const int nAOSA);


//! \brief Perform the IHM for Online Processing.
//! \param[in] nAOSA : with Available Offline Spending Amount : WITH_AOSA or WITHOUT_AOSA

void Helper_Visa_OnlineProcessingIHM(const int nAOSA);


//! \brief Perform the IHM for Transaction that was Terminated.

void Helper_Visa_ErrorIHM(void);


//! \brief Display Available amount (if available) on customer display.

void Helper_Visa_DisplayAvailableAmount(void);


//! \brief This function get the format and the currency position from the parameters to display the amount.
//! \param[in] pCurrencyLabel Currency label to find in the parameter file.
//! \param[out] pFormat Format of the displayed amount.
//! \param[out] pPosition Position of the currency (before or after the amount).
//!	\return
//!	- \a TRUE if format to display is found.
//!	- \a FALSE indicate an invalid parameter as the currency label provided is unknown from the application.

int Helper_GetCurrencyFormatFromParameters(unsigned char *pCurrencyLabel, unsigned char *pFormat,unsigned char *pPosition);

#endif //__SDSA_UIHELPERS_H__INCLUDED__
