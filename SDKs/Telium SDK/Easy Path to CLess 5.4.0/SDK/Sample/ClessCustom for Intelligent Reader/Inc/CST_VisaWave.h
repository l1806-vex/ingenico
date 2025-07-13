/**
 * \file	CST_VisaWave.h
 * \brief 	Module that manages the VisaWave transaction.
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

#ifndef __CST_VISAWAVE_H__INCLUDED__
#define __CST_VISAWAVE_H__INCLUDED__



/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Specific management for VisaWave end of transaction according to transaction result.
//! Displays specific messages, manages batch, manages online authorization, manages CVM ...
//! \param[in] pDataStruct Transaction output data. 
//! \param[in] nTransactionOutcome Transaction result.
//! \return The transaction outcome value.

int CST_VisaWave_Transaction(T_SHARED_DATA_STRUCT * pDataStruct, int nTransactionOutcome);



//! \brief Check in the parameter file if the GUI mode to use is Visa Asia.

void CST_VisaWave_SetVisaAsiaGuiMode (void);



//! \brief Check if the Visa Asia GUI mode is activated.
//!	\return
//!		- TRUE if Visa Asia GUI mode is used.
//!		- FALSE else.

int CST_VisaWave_IsVisaAsiaGuiMode (void);



//! \brief Get the last transaction data in the batch file
//! \param[in] TlvTransactionData contains the current transaction data

void CST_VisaWave_GetLastTransactionData (TLV_TREE_NODE TlvTransactionData);


#endif // __CST_VISAWAVE_H__INCLUDED__
