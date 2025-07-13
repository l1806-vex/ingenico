/**
* \file cu_entry.h
* \brief This module contains the entry point functions called by the Manager.
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

#ifndef CU_ENTRY_H
#define CU_ENTRY_H

//! \defgroup Group_cu_entry Manager entry points.
//! @{

/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */

extern unsigned short CustApplicationNumber;				//!< Custom application type.

#ifdef _USE_UCM_
extern int UCM_Present;										//!< Boolean indicating if an UCM is present.
#endif

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */
/*==========================================================================*/
//! \brief This function displays the message "USE MAG STRIPE".
//! This entry point replaces the default behaviour of the Telium Manager.
//! \param[in] noappli :  application number.
//! \param[in] AmountEntry : TRUE if the amount is already available
//! \param[in] amount : the amount if bAmount is TRUE
//! \return Always FCT_OK.
/*==========================================================================*/
int cu_fall_back    (NO_SEGMENT noappli, ENTRY_TYPE AmountEntry, unsigned long amount);


//! @}

#endif /* CU_ENTRY_H */
