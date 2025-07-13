/**
 * \file	SDSA_payWave.h
 * \brief	Manages the interface with the payWave contactless kernel.
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

#ifndef __SDSA_PAYWAVE_H__INCLUDED__
#define __SDSA_PAYWAVE_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Manage the debug mode for PayPass kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void SDSA_payWave_DebugActivation (int bActivate);



//! \brief Perform the payWave kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int SDSA_payWave_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep);



//! \brief Calls the payWave kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for payWave transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing th etransaction result.
//!	\return
//!		- payWave kernel result.

int SDSA_payWave_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree);


//! \brief Calls the payWave kernel to perform the post transaction processing.
//! \param[in] pDataStruct Data buffer to be filled and used for payWave transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- payWave kernel result.

int SDSA_payWave_PerformPostProcessing (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree);


//! \brief Modify several parameters before to use it.
//! \param[in] pShareStruct Share buffer given and modified by EntryPoint.
//! \param[in/out] pAidParameters parameters found to manage AID.
//!	\return
//!		- payWave kernel result.

void SDSA_payWave_AidRelatedData(T_SHARED_DATA_STRUCT * pSharedStruct, T_SHARED_DATA_STRUCT * pAidParameters);

//! \brief Allows to known if error is due to amount greater than TAG_EP_CLESS_TRANSACTION_LIMIT
//!	\return
//!		- TRUE if error is due to amount greater than TAG_EP_CLESS_TRANSACTION_LIMIT.
//!     - FALSE else.

int SDSA_payWave_IsQVSDCNotAllowedForAmount(void);


//! \brief Memorise if amount is greater than TAG_EP_CLESS_TRANSACTION_LIMIT.
//! \param[in] TRUE/FALSE error due to amount greater than TAG_EP_CLESS_TRANSACTION_LIMIT.

void SDSA_payWave_SetQVSDCNotAllowedForAmount(int nAmountGreaterThanTransactionLimit);




#endif // __SDSA_PAYWAVE_H__INCLUDED__
