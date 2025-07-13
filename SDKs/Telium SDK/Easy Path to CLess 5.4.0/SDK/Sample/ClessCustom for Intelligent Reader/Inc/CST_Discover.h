/**
 * \file	CST_Discover.h
 * \brief 	Module that manages the Discover transaction.
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

#ifndef __CST_DISCOVER_H__INCLUDED__
#define __CST_DISCOVER_H__INCLUDED__



/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Specific management for Discover end of transaction according to transaction result.
//! Displays specific messages, manages batch, manages online authorization, manages CVM ...
//! \param[in] pDataStruct Transaction output data. 
//! \param[in] nTransactionOutcome Transaction result.
//! \return The transaction outcome value.

int CST_Discover_Transaction(T_SHARED_DATA_STRUCT * pDataStruct, int nTransactionOutcome);

//! \brief Get the last transaction data in the batch file
//! \param[in] TlvTransactionData contains the current transaction data

void CST_Discover_GetLastTransactionData (TLV_TREE_NODE TlvTransactionData);


#endif // __CST_DISCOVER_H__INCLUDED__
