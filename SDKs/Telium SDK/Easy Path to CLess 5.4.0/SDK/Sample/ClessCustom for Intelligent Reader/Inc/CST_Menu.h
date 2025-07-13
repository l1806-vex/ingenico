/**
 * \file	CST_Menu.h
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

#ifndef __CST_MENU_H__INCLUDED__
#define __CST_MENU_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Global menu management

void CST_Menu_MainMenuDisplay(void);



//! \brief Test if transaction loop mode has been activated.
//! \return
//!		- \ref TRUE if loop is activated.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsTransactionLoopOn (void);



//! \brief Test if transaction data dumping is TRUE or FALSE.
//! \return
//!		- \ref TRUE if data dumping is activated.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsTransactionDataDumpingOn (void);



//! \brief Test if transaction database dumping is TRUE or FALSE.
//! \return
//!		- \ref TRUE if database dumping is activated.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsTransactionDatabaseDumpingOn (void);



//! \brief Test if Visa Europe Mode is activated or not.
//! \return
//!		- \ref TRUE if Visa Europe Mode is activated.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsVisaEuropeModeOn (void);



//! \brief Test if cashback transaction type must be as defined by Visa payWave (idem DEBIT transaction type: 0x00).
//! \return
//!		- \ref TRUE if it is a Visa payWave cashback.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsVisaCashback(void);



//! \brief Test if Transaction Type entry is possible or not.
//! \return
//!		- \ref TRUE if Transaction Type entry is activated.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsEnableInputTransactionType (void);


#endif // __CST_MENU_H__INCLUDED__
