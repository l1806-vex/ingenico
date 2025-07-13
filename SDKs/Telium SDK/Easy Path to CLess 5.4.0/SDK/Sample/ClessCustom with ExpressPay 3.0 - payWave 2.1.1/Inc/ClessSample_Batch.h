/**
 * \file	ClessSample_Batch.h
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

#ifndef __CLESS_SAMPLE_BATCH_H__INCLUDED__
#define __CLESS_SAMPLE_BATCH_H__INCLUDED__


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

void ClessSample_Batch_InitTransactionSeqCounter (const unsigned char bForceInit);



//! \brief Increment the Transaction sequence counter by 1.
//! \note If the TSC reached its max value, this one is initialised to 1.

void ClessSample_Batch_IncrementTransactionSeqCounter (void);



//! \brief Add the transaction sequence counter into a shared buffer structure.
//! \param[in] pDataStruct Shared buffer in which the transaction sequence counter is stored.
//! \return
//!		- \a TRUE if correctly added.
//!		- \a FALSE if an error occurred.

int ClessSample_Batch_AddTscToSharedBuffer (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function checks the consistency of the transaction file. 
//! If the file data are valid the ram data are updated with the file content.
//! If the file is found corrupted, the function tries to restore it.

void ClessSample_Batch_Restore (void);



//! \brief Get the number of transaction stored in the batch file.
//! \param[out] nb_record Number of records stored in the Batch file.

void ClessSample_Batch_InitialiseBatchTransfer (unsigned long *nb_record);



//! \brief Add a transaction record in the batch file.
//! \param[in] pDataStruct Shared buffer containing the transaction data.
//! \return
//!		- \a TRUE if correctly performed.
//!		- \a FALSE if an error occurred.

int ClessSample_Batch_AddTransactionToBatch (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Destroy the batch database.

void ClessSample_Batch_Destroy (void);



//! \brief Dump the last transaction data saved in the batch.

void ClessSample_Batch_PrintLastTransaction (void);



//! \brief Dump the batch totals.

void ClessSample_Batch_PrintTotals (void);



//! \brief Dump the batch overview (each transaction overview).

void ClessSample_Batch_PrintBatchOverview (void);


//! \brief Dump the batch detailed overview (each transaction detailed).

void ClessSample_Batch_PrintBatchDetailedOverview (void);


#endif // __CLESS_SAMPLE_BATCH_H__INCLUDED__
