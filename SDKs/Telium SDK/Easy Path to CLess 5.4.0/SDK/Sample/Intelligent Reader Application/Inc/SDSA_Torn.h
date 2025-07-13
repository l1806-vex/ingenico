/**
 * \file	SDSA_Torn.h
 * \brief	This manages the torn transactions.
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
 */

#ifndef __SDSA_TORN_H__INCLUDED__
#define __SDSA_TORN_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Determine if the terminal supports the recovery processing.
//! \return
//!		- \a TRUE if it is supported.
//!		- \a FALSE if not.

int SDSA_Torn_IsRecoverySupported (void);



//! \brief Get the maximum number of records that could be stored in the torn transaction log.
//! \return
//!		- \a The maximum number of torn transaction log records.
//!		- \a 0 if the terminal does not support the recovery processing.

unsigned int SDSA_Torn_GetMaxNumberOfTornTxnLogRecords (void);



//! \brief Get the number of torn transaction log records.

unsigned int SDSA_Torn_GetNumberOfTornTxnLogRecords (void);



//! \brief Check if the current transaction is a torn transaction (if it appears in the torn transaction log).
//! \param[in/out] pSharedDataStruct Shared buffer filled with the transaction information (PAN, PAN sequence number...).
//!									 Output buffer is filled with the torn record in the case of a torn transaction.
//! \return
//!		- TRUE if the transaction is in the torn transaction log, FALSE else.

int SDSA_Torn_IsTornTxn(T_SHARED_DATA_STRUCT * pSharedDataStruct);



//! \brief Add the current transaction in a new record in the torn transaction log. Remove the oldest record if maximum number is exceeded.
//! \param[in/out] pSharedDataStruct Shared buffer filled with the transaction record to add in the log (PAN, PAN sequence number....).
//!									 Output buffer is filled with the removed record if maximum number of record is exceeded.
//! \return
//!		- TRUE if the record has been correctly added in the torn transaction log, FALSE else.

int SDSA_Torn_AddRecord(T_SHARED_DATA_STRUCT * pSharedDataStruct);



//! \brief Remove the current transaction record from the torn transaction log.
//! \return
//!		- TRUE if the record has been correctly removed from the torn transaction log, FALSE else.

int SDSA_Torn_RemoveRecord(void);



//! \brief Function that allows to clean or to get the Torn Transaction Log.
//! \param[in] hInputTlvTree Contains the input data.
//! \param[out] pOutputTlvTree Contains output data.
//! \return
//!	- \ref SDI_STATUS_OK if correctly performed.
//!	- \ref SDI_STATUS_KO if an error occured.

int SDSA_Torn_Generic_UserCommand_02 (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);


#endif // __SDSA_TORN_H__INCLUDED__
