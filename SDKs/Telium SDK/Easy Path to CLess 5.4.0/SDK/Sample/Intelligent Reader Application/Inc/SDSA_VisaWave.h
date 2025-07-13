/**
 * \file	SDSA_VisaWave.h
 * \brief	Manages the interface with the VisaWave contactless kernel.
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

#ifndef __SDSA_VISAWAVE_H__INCLUDED__
#define __SDSA_VISAWAVE_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Manage the debug mode for VisaWave kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void SDSA_VisaWave_DebugActivation (int bActivate);



//! \brief Perform the VisaWave kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int SDSA_VisaWave_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep);



//! \brief Calls the VisaWave kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for VisaWave transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- VisaWave kernel result.

int SDSA_VisaWave_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree);


//! \brief Modify several parameters before to use it.
//! \param[in] pShareStruct Share buffer given and modified by EntryPoint.
//! \param[in/out] pAidParameters parameters found to manage AID.
//!	\return
//!		- VisaWave kernel result.

void SDSA_VisaWave_AidRelatedData(T_SHARED_DATA_STRUCT * pSharedStruct, T_SHARED_DATA_STRUCT * pAidParameters);


//! \brief Check if the current transaction is a VisaWave transaction.
//! \return
//!		- TRUE if the VisaWave kernel is present and gs_nTransactionRestartedWithpayWave is not set.
//!		- FALSE else.

unsigned char SDSA_VisaWave_isVisaWaveProcessing (void);


//! \brief Set the variable to indicate that the VisaWave kernel is present in the terminal.

void SDSA_VisaWave_SetVisaWaveKernelPresence (void);


//! \brief Set the variable to indicate that the transaction must use or not the payWave kernel.
//! \param[in] bValue : TRUE if transaction must be performed by the payWave kernel

void SDSA_VisaWave_SetpayWaveFallBack (int bValue);


//! \brief Check in the parameter file if the GUI mode to use is Visa Asia.

void SDSA_VisaWave_SetVisaAsiaGuiMode (void);


//! \brief Check if the Visa Asia GUI mode is activated.
//!	\return
//!		- TRUE if Visa Asia GUI mode is used.
//!		- FALSE else.

int SDSA_VisaWave_IsVisaAsiaGuiMode (void);


//! \brief Get the timeout value for card detection process from the parameter file.
//! \param[out] pNoCardTimeOut the timeout value (in milliseconds).
//! \return
//!		- TRUE if tag is present.
//!		- FALSE else.

int SDSA_VisaWave_GetNoCardTimeOut (unsigned long *pNoCardTimeOut);


#endif // __SDSA_VISAWAVE_H__INCLUDED__
