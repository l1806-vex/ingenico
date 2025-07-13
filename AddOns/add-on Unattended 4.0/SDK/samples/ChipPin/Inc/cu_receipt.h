/**
* \file cu_receipt.h
* \brief This module contains the functions needed to print a receipt.
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

#ifndef CU_RECEIPT_H
#define CU_RECEIPT_H

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "cu_mess.h"	// to use S_TAB_CONFIG
#include "cu_batch.h"	// to use T_CUBATCH

//! \defgroup Group_cu_receipt Receipt printing management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function prints the transaction ticket.
//! \param[in] hInputTLVTree : input TLV tree containing the transaction informations : 
//! - currency,
//! - date,
//! - time,
//! - amount.
//! \param[in] status_tr : transaction status.
//===========================================================================
void CURECEIPT_Print_Ticket_POS_Demo(TLV_TREE_NODE hInputTLVTree, unsigned char status_tr);

#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function prints the advance demo ticket which contains the all
//! timings (terminal, card, MMI, Host) of the last transaction. This function is 
//! active only if flag _TOOLWARE_ is defined and if the Kernel (EMV DC)
//! supports the TOOLWARE option.
//===========================================================================
void CURECEIPT_Print_Ticket_Advance_Demo(void);
#endif

//===========================================================================
//! \brief This function prints the current EMV Configuration loaded in terminal.
//===========================================================================
void CURECEIPT_Print_EMV_Config(void);

//! @}

#endif
