/**
 * \file	CST_Scan.h
 * \brief	This module manages contact transactions.
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
 */

#ifndef __CST_SCAN_H__INCLUDED__
#define __CST_SCAN_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define E_USER_EVENT			31							// User event bit for notification
#define USER_EVENT				1 << E_USER_EVENT			// User event, necessary to be notified when the response has been received

#define E_USER_EVENT_PIN		30							// User event bit for PIN management
#define USER_EVENT_PIN     		1 << E_USER_EVENT_PIN  		// PIN management event	

#define E_USER_EVENT_STATUS		29							// User event bit for status task management
#define USER_EVENT_STATUS		1 << E_USER_EVENT_STATUS	// Status task event



/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////
extern int g_ListOfEvent;						// Global variable used by the scanning task to provide the event.


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Perform a contact transaction on Cam0.
//! \param[in] ulAmount Transaction amount. 
//! \param[in] nCurrencyCode Transaction currency code.
//! \return :
//!		- TRUE if the contact transaction is performed
//!		- FALSE else

int CST_Scan_TransacCam0(unsigned long ulAmount, int nCurrencyCode);



//! \brief Perform a swipe transaction.
//! \param[in] ulAmount Transaction amount. 
//! \return :
//!		- TRUE if the swipe transaction is performed
//!		- FALSE else

int CST_Scan_TransacSwipe2(unsigned long ulAmount);



//! \brief Opens the drivers for contact transactions.

void CST_Scan_TransacOpenDrivers(void);



//! \brief Close the Cam0 contact driver.

void CST_Scan_TransacCloseDriversExceptSwipe(void);



//! \brief Close the contact drivers.

void CST_Scan_TransacCloseDrivers(void);



//! \brief Perform a contact transaction.
//! If a contact card has already been detected, the transaction is directly performed, else a message is displayed and contact interfaces are scanned to detect the card.
//! \param[in] ulAmount Transaction amount. 
//! \param[in] nCurrencyCode Transaction currency code.
//! \param[in] pFormattedAmountMessage Message to display that contains the transaction amount. 
//! \param[in] bScanInterfaces Boolean (TRUE if contact interfaces must be scanned). 

void CST_Scan_PerformContactTransaction (unsigned long ulAmount, int nCurrencyCode, char *pFormattedAmountMessage, int bScanInterfaces);



//! \brief Memorise ISO2 track.
//! \param[in] lgParamIso2 : lg track Iso 2.
//! \param[in] pParambufIso2 pointer on ISO2 track data. 
void CST_Scan_MemoriseISO2Track(LG_REF_CLI lgParamIso2, TRACK2_BUFFER ParambufIso2);


#endif // __CST_SCAN_H__INCLUDED__
