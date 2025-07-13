/**
* \file CustomTypes.h
* \brief This module contains the definitions of EMVDC error codes.
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

#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

//! \defgroup Group_CustomTypes EMVDC error code definitions.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define ERROR_CODE_CANCEL				(0)					//!< Returned EMVDC status code, when user canceled the transaction.
#define ERROR_CODE_PROCESSING_ERROR		(1)					//!< Returned EMVDC status code, when error occured during transaction process.
#define ERROR_CODE_CARD_BLOCKED			(2)					//!< Returned EMVDC status code, when the inserted card is blocked.
#define ERROR_CODE_REMOVE_CARD			(3)					//!< Returned EMVDC status code, when a card has to be removed.
#define ERROR_CODE_INVALID_CARD			(4)					//!< Returned EMVDC status code, when the inserted card is invalid.
#define NO_ERROR_CODE					(5)					//!< Init value of EMVDC status code, before accessing EMVDC.

#define SC_CONTINUE						(0)					//!< Action if no error occured.
#define SC_CANCEL						(1)					//!< Action if one error occured.

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//! @}

#endif
