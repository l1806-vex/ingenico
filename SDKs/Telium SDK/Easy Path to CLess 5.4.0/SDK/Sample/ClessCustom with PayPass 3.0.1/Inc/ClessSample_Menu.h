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

//! \brief Global menu management

void ClessSample_Menu_MainMenuDisplay(void);


//! \brief Transaction Type menu management

///void ClessSample_Menu_TransactionTypeMenuDisplay(const unsigned char *pCurrencyLabel, unsigned long * ulAmount, unsigned long * ulAmountOther, int * pnTransactionType, int * pnTransactionCashBack);
void ClessSample_Menu_TransactionTypeMenuDisplay (int * pnTransactionType);


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



//! \brief Action to do if DUMP TR DATA is selected in the TEST menu
//! \return Always -1.

int ClessSample_Menu_TestTransactionData(void);



//! \brief Test if transaction database dumping is TRUE or FALSE.
//! \return
//!		- \ref TRUE if database dumping is activated.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsTransactionDatabaseDumpingOn (void);



//! \brief Action to do if "DUMP DATA DB" is selected in the TEST menu (it enables/diables the dabase dumping).
//! \return Always -1.

int ClessSample_Menu_TestTransactionDumpDatabase(void);



//! \brief Test if transaction APDU and Data Exchange dumping is TRUE or FALSE.
//! \return
//!		- \ref TRUE if dumping is activated.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsApduDataExchangeDumpingOn (void);



//! \brief Test if merchant forced transaction online or not.
//! \return
//!		- \ref TRUE if merchant forced transaction online.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsMerchantForcedOnline (void);



//! \brief Allows to known trace state

int ClessSample_Menu_IsTraceActivated(void);



//! \brief Action to do if TRACES is selected in the TEST menu
//! \return Always -1.

int ClessSample_Menu_TestTraces(void);



//! \brief Action to do if TRANSAC LOOP is selected in the TEST menu
//! \return Always -1.

int ClessSample_Menu_TestTransactionLoop(void);



//! \brief Action enable/disable "TransactionType" information to input.
//! \return Always -1.

int ClessSample_Menu_TestInputTransactionType(void);



//! \brief Action to do if "DUMP APDU DE" is selected in the TEST menu (it enables/diables the APDU and DE dumping).
//! \return Always -1.

int ClessSample_Menu_TestTransactionDumpApduDataExchange(void);



//! \brief  Action to do if AUTO CLEAN is selected in the Torn Log menu
//! \return Always -1.

int ClessSample_Menu_TornAutoCleanLog(void);


//! \brief Test if automatic CLEAN of torn log has been activated.
//! \return
//!		- \ref TRUE if automatic CLEAN of torn log  is activated.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsAutomaticCleanTornOn (void);



#endif // __CLESS_SAMPLE_MENU_H__INCLUDED__
