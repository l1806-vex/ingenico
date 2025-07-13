/**
 * \file	SDSA_Interac.h
 * \brief	Manages the interface with the Interac contactless kernel.
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

#ifndef __SDSA_INTERAC_H__INCLUDED__
#define __SDSA_INTERAC_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Manage the debug mode for Interac kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void SDSA_Interac_DebugActivation (int bActivate);



//! \brief Perform the Interac kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int SDSA_Interac_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep);



//! \brief Calls the Interac kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for Interac transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- Interac kernel result.

int SDSA_Interac_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree);


//! \brief Modify several parameters before to use it.
//! \param[in] pShareStruct Share buffer given and modified by EntryPoint.
//! \param[in/out] pAidParameters parameters found to manage AID.
//!	\return
//!		- Interac kernel result.

void SDSA_Interac_AidRelatedData(T_SHARED_DATA_STRUCT * pSharedStruct, T_SHARED_DATA_STRUCT * pAidParameters);


//! \brief Check if the current transaction is a Interac transaction.
//! \return
//!		- TRUE if the Interac kernel is present and gs_nTransactionRestartedWithpayWave is not set.
//!		- FALSE else.

unsigned char SDSA_Interac_isInteracProcessing (void);


//! \brief Set the variable to indicate that the Interac kernel is present in the terminal.

void SDSA_Interac_SetInteracKernelPresence (void);


//! \brief Set the variable to indicate that the transaction must use or not the payWave kernel.
//! \param[in] bValue : TRUE if transaction must be performed by the payWave kernel

void SDSA_Interac_SetpayWaveFallBack (int bValue);


//! \brief Check in the parameter file if the GUI mode to use is Visa Asia.

void SDSA_Interac_SetInteracGuiMode (void);


//! \brief Check if the Interac GUI mode is activated.
//!	\return
//!		- TRUE if Interac GUI mode is used.
//!		- FALSE else.

int SDSA_Interac_IsInteracGuiMode (void);


//! \brief Get the timeout value for card detection process from the parameter file.
//! \param[out] pNoCardTimeOut the timeout value (in milliseconds).
//! \return
//!		- TRUE if tag is present.
//!		- FALSE else.

int SDSA_Interac_GetNoCardTimeOut (unsigned long *pNoCardTimeOut);


#endif // __SDSA_INTERAC_H__INCLUDED__
