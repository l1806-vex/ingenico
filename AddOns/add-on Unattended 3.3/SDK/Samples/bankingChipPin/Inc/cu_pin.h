/**
* \file cu_pin.h
* \brief This module contains the functions that perform the entry of the PIN code.
* The PIN code can be entered directly on the terminal, or on a pinpad.
* It is kept in the booster.
* In case of enciphered PIN for online presentation, this module also
* encipher the PIN code, and returns the result.
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

#ifndef CU_PIN_H
#define CU_PIN_H

//! \defgroup Group_cu_pin PIN code entry management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define  ERROR_INPUT								70		//<! Pin code input error.

/* ======================================================================== */
/* Types declarations                                                       */
/* ======================================================================== */

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function performs the PIN code entry and encipherment, for online
//! verification.
//! \param[in] nb_try : number of PIN entry attempts.
//! \param[in] AllowTermIfPPadHS : boolean allowing the terminal management,
//! if the pinpad is here but out of service.
//! \param[out] buffer : buffer containing the entered pin code.
//! \param[out] ptrPrimaryAccountNumber : pointer on the data given by the tag.
//! \param[out] ptrBypass_Required : boolean set to TRUE if bypass is asked.
//! Else not modified.
//! \return 
//! - PP_HS : Problem with PINPAD, or with the booster.
//! - INPUT_PIN_ON : PIN entry and encipherement was successfull.
//! - CANCEL_INPUT : PIN entry was canceled.
//! - TO_INPUT : Time-out during PIN entry.
//! \todo Online PIN management :
//! \li A dummy key is used for online PIN management.
//! \li Replace it by your own secret key management.
//! \li Replace the default encipherment algorithm by the one you need.
//===========================================================================
unsigned char CUPIN_EnterPinOnLine(unsigned char nb_try,
								   unsigned char AllowTermIfPPadHS,
								   ENTRY_BUFFER *buffer,
								   unsigned char * ptrPrimaryAccountNumber,
								   unsigned short *ptrBypass_Required);


//===========================================================================
//! \brief This function performs the PIN code verification. The PIN code 
//! is verified offline by the ICC. The PIN code is not available in the 
//! Thunder processor. It is kept inside the Booster processor.
//! \param[in] nb_try : number of PIN entry attempts.
//! \param[in] AllowTermIfPPadHS : boolean allowing the terminal management,
//! if the pinpad is here but out of service.
//! \param[out] buffer : dummy PIN code.
//! \param[out] ptrPrimaryAccountNumber : pointer on the data given by the tag.
//! Unused, kept for compatibility with online function.
//! \param[out] ptrBypass_Required : boolean set to TRUE if bypass is asked.
//! Else not modified.
//! \return 
//! - PP_HS : Problem with PINPAD, or with the booster.
//! - INPUT_PIN_ON : PIN entry was successfull.
//! - CANCEL_INPUT : PIN entry was canceled.
//! - TO_INPUT : Time-out during PIN entry.
//===========================================================================
unsigned char CUPIN_EnterPinOffLine(unsigned char nb_try,
									unsigned char AllowTermIfPPadHS,
									ENTRY_BUFFER *buffer,
									unsigned char * ptrPrimaryAccountNumber,
									unsigned short * ptrBypass_Required);


//! @}

#endif

