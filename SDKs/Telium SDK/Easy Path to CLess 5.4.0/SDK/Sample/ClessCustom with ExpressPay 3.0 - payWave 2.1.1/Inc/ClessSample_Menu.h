/**
 * \file	ClessSample_Customisation.h
 * \brief 	Manages the application menus.
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

#ifndef __CLESS_SAMPLE_MENU_H__INCLUDED__
#define __CLESS_SAMPLE_MENU_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Global Amount entry management

int ClessSample_Menu_AmountEntry (const unsigned char *pCurrencyLabel, unsigned long * pAmountBin, char * pFormattedAmountMessage);


//! \brief Global menu management

void ClessSample_Menu_MainMenuDisplay(void);


//! \brief Transaction Type menu management

void ClessSample_Menu_TransactionTypeMenuDisplay(const unsigned char *pCurrencyLabel, unsigned long * ulAmount, unsigned long * ulAmountOther, int * pnTransactionType);


//! \brief Test if transaction loop mode has been activated.
//! \return
//!		- \ref TRUE if loop is activated.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsTransactionLoopOn (void);

//! \brief Test if EnableTransactionType is on.
//! \return
//!		- \ref TRUE if loop is activated.
//!		- \ref FALSE if not.
unsigned char ClessSample_Menu_IsEnableInputTransactionType (void);

//! \brief Test if transaction data dumping is TRUE or FALSE.
//! \return
//!		- \ref TRUE if data dumping is activated.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsTransactionDataDumpingOn (void);



//! \brief Test if transaction database dumping is TRUE or FALSE.
//! \return
//!		- \ref TRUE if database dumping is activated.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsTransactionDatabaseDumpingOn (void);



//! \brief Test if Visa Europe Mode is activated or not.
//! \return
//!		- \ref TRUE if database dumping is activated.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsVisaEuropeModeOn (void);



//! \brief Test if merchant forced transaction online or not.
//! \return
//!		- \ref TRUE if merchant forced transaction online.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsMerchantForcedOnline (void);



//! \brief Allows to known trace state
int ClessSample_Menu_IsTraceActivated(void);



#endif // __CLESS_SAMPLE_MENU_H__INCLUDED__
