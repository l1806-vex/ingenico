/**
 * \file	CST_Interac.h
 * \brief 	Module that manages the Interac transaction.
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

#ifndef __CST_INTERAC_H__INCLUDED__
#define __CST_INTERAC_H__INCLUDED__



/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Specific management for Interac end of transaction according to transaction result.
//! Displays specific messages, manages batch, manages online authorization, manages CVM ...
//! \param[in] pDataStruct Transaction output data. 
//! \param[in] nTransactionOutcome Transaction result.
//! \return The transaction outcome value.

int CST_Interac_Transaction(T_SHARED_DATA_STRUCT * pDataStruct, int nTransactionOutcome);



//! \brief Check in the parameter file if the GUI mode to use is Interac.

void CST_Interac_SetInteracGuiMode (void);



//! \brief Check if the Interac GUI mode is activated.
//!	\return
//!		- TRUE if Interac GUI mode is used.
//!		- FALSE else.

int CST_Interac_IsInteracGuiMode (void);

#endif // __CST_INTERAC_H__INCLUDED__
