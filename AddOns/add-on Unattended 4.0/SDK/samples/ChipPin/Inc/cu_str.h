/**
* \file cu_str.h
* \brief This module contains the functions needed for magnetic stripe management.
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

#ifndef CU_STR_H
#define CU_STR_H

//! \defgroup Group_cu_str Magnetic stripe management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */

// extern int isFallbackAllowed;

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function treats the magnetic stripe transaction.
//! \param[in] bValidAmount : TRUE if the amount is already available
//! \param[in] amount : the amount if bValidAmount is TRUE
//! \param[in] isFallbackAllowed : boolean indicating the magnetic stripe 
//! fall back authorization.
//! \param[in] track2_buffer : ISO2 track data given by M2OS.
//! \return 
//! - TRUE if card read with IC, and fall back accepted.
//! - FALSE otherwise.
//===========================================================================
int CUSTR_Mag_Stripe_Debit (int bValidAmount, unsigned long amount, int isFallbackAllowed,
							char *track2_buffer);

//===========================================================================
//! \brief This function checks the case of fall-back occuring during the 
//! application selection phase.
//! \return 
//! - TRUE if the fall-back is allowed.
//! - FALSE otherwise.
//! \note This implementation is just given as a sample.
//! You must modify it to fit the local requirements regarding fall-back.
//! This implementation is based on the MasterCard algorithm.
//! \todo fall-back implementation :
//! Modify the implementation of a fall-back during application selection 
//! to your local rules.
//===========================================================================
extern int CUSTR_CheckFallback (void);

//! @}

#endif

