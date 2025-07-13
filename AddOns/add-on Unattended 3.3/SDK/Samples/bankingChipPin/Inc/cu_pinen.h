/**
* \file cu_pinen.h
* \brief This module contains the functions that perform the encipherment of the PIN code,
* for online presentation.
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

#ifndef  _PIN_H_
#define  _PIN_H_

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "saisie.h"					// to include BUFFER_SAISIE's definition

//! \defgroup Group_cu_pinen PIN code encipherment.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ========================================================================	*/
/* Global functions declaration                                             */
/* ========================================================================	*/

//===========================================================================
//! \brief This function injects a secret key into the Booster.
//! This is a dummy key injection function, called at the terminal initialisation.
//! This secret key will be used for PIN encipherment for online verification.
//! \return
//! - OK if the key is successfully loaded in the booster.
//! - Error code otherwise.
//===========================================================================
int PIN_InjectKey (void);

//===========================================================================
//! \brief This function enciphers the PIN code for online presentation, 
//! and gets the result.
//! The algorithm used for this sample is simple DES, ISO 9564, with block 0.
//! \param[in] pucPAN : Primary Account Number of the ICC.
//! \param[out] pucEncipheredPin : Encipherement result.
//! \param[out] iLenEnc : length of enciphered PIN.
//! \return
//! - 1 if the PIN code was correctly enciphered.
//! - 0 if errors occured during encipherement.
//===========================================================================
int PIN_OnlineEncipher (unsigned char pucPAN [],
						unsigned char pucEncipheredPin [],
						int *iLenEnc);

#ifdef _USE_DEMO_
//===========================================================================
//! \brief This function enciphers the PIN code for online presentation, 
//! and gets the result. In the demo mode no encipherement is performed.
//! \param[in] pucPAN : Primary Account Number of the ICC.
//! \param[out] pucEncipheredPin : Encipherement result.
//! \param[out] iLenEnc : length of enciphered PIN.
//! \return
//! - 1 if the PIN code was correctly enciphered.
//! - 0 if errors occured during encipherement.
//===========================================================================
int PIN_OnlineEncipherDemo (unsigned char pucPAN [], unsigned char pucEncipheredPin [],int *iLenEnc);

//===========================================================================
//! \brief This function injects a secret key into the Booster. In the demo
//! mode nothing is performed by this function.
//===========================================================================
void PIN_InjectKeyDemo (void);
#endif

//! @}

#endif
