/**
 * \file	CST_Batch.h
 * \brief	To manage the transaction batch as well as the transaction sequence counter.
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

#ifndef __CST_BATCH_H__INCLUDED__
#define __CST_BATCH_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Initialise the transaction sequence counter to 1.
//! \param[in] bForceInit Indicates if TSC shall be forced to be initialised or not.

void CST_Batch_InitTransactionSeqCounter (const unsigned char bForceInit);



//! \brief Increment the Transaction sequence counter by 1.
//! \note If the TSC reached its max value, this one is initialised to 1.

void CST_Batch_IncrementTransactionSeqCounter (void);



//! \brief Add the transaction sequence counter into a TLV Tree.
//! \param[in] pDataStruct Shared buffer in which the transaction sequence counter is stored.
//! \return
//!		- \a TRUE if correctly added.
//!		- \a FALSE if an error occured.

int CST_Batch_AddTscToTlvTree (TLV_TREE_NODE hTlvTree);



//! \brief This function checks the consistency of the transaction file. 
//! If the file data are valid the ram data are updated with the file content.
//! If the file is found corrupted, the function tries to restore it.

void CST_Batch_Restore (void);



//! \brief Get the number of transaction stored in the batch file.
//! \param[out] nb_record Number of records stored in the Batch file.

void CST_Batch_InitialiseBatchTransfer (unsigned long *nb_record);



//! \brief Add a transaction record in the batch file.
//! \param[in] pDataStruct Shared buffer containing the transaction data.
//! \return
//!		- \a TRUE if correctly performed.
//!		- \a FALSE if an error occured.

int CST_Batch_AddTransactionToBatch (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Destroy the batch database.

void CST_Batch_Destroy (void);



//! \brief Dump the last transaction data saved in the batch.

void CST_Batch_PrintLastTransaction (void);



//! \brief Dump the batch totals.

void CST_Batch_PrintTotals (void);



//! \brief Dump the batch overview (each transaction overview).

void CST_Batch_PrintBatchOverview (void);



#endif // __CST_BATCH_H__INCLUDED__
