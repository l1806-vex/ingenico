/**
* \file cu_more.h
* \brief This module contains the functions activated by the navigation menus.
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

#ifndef CU_MORE_H
#define CU_MORE_H

//! \defgroup Group_cu_more Navigation menus management.
//! @{

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

extern TLV_TREE_NODE CUMORE_Tree;					//!< Global TLV tree used by functions called in the application menus.
extern unsigned short Bypass_Required;				//!< Boolean indicating if PIN code entry has to be bypassed on the next transaction.
extern unsigned short TransactionForcedOnline;		//!< Boolean indicating if the next transaction has to be forced online. 
extern unsigned char RetransmitIndicator;			//!< Boolean indicating if the current record has been transmitted to the host.

/* ========================================================================	*/
/* Global functions declaration                                             */
/* ========================================================================	*/

//===========================================================================
//! \brief This function manages a debit/credit transaction.
//===========================================================================
extern void CUMORE_Debit(void);

//===========================================================================
//! \brief This function starts an EMV transaction.
//! \param ulAmount : amount entered.
//! \param nCurrencyCode : ISO currency code.
//===========================================================================
extern void CUMORE_DebitEx(unsigned long ulAmount, int nCurrencyCode);

//===========================================================================
//! \brief This function begins a refund transaction, with amount entered first.
//===========================================================================
extern void CUMORE_Refund(void);

//===========================================================================
//! \brief This function sends the batch data file to the host.
//===========================================================================
extern void CUMORE_BatchCapt(void);

/* ========================================================================	*/
/* Constant declaration                                                     */
/* ========================================================================	*/
#ifndef _TOOLWARE_
extern const NavigationListe NavigationEmvdc[7];	//!< Array for navigation menus.
#else
extern const NavigationListe NavigationEmvdc[8];	//!< Array for navigation menus.
#endif

#ifdef _USE_UCM_
extern int cu_more_function_UCM(NO_SEGMENT no,void *p1,void *p2);
#endif
//! @}

#endif
