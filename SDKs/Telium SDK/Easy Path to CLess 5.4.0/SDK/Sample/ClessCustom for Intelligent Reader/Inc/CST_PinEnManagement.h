/**
 * \file	CST_PinEnManagement.h
 * \brief	Module that manages the PIN encipher functions.
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
 **/



//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __CST_PINEN_H__INCLUDED__
#define __CST_PINEN_H__INCLUDED__

//! \defgroup Group_cu_pin PIN code entry management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */


/* ======================================================================== */
/* Types declarations                                                       */
/* ======================================================================== */

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//! \brief Inject Key : Check if secret area exist and Load a key.
//! \return
//!		- \ref OK (0) is successful, otherwise error.

int CST_InjectKey (void);



//! \brief Encypher a key previously inputed with Scheme method.
//! \param[in] card pan.
//! \param[in] Enciphered Pin.
//! \param[in] Enciphered Pin length.
//! \return
//!		- \ref TRUE Pin has been corectly encyphered.
//!		- \ref FALSE else.

int CST_OnlineEncipher(unsigned char pucPAN [], unsigned char pucEncipheredPin [], int *iLenEnc);

/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

#endif // __CST_PINEN_H__INCLUDED__


