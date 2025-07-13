/**
 * \file	SDSA_Discover.h
 * \brief	Manages the interface with the Discover contactless kernel.
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

#ifndef __SDSA_DISCOVER_H__INCLUDED__
#define __SDSA_DISCOVER_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Manage the debug mode for Discover kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void SDSA_Discover_DebugActivation (int bActivate);



//! \brief Perform the Discover kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int SDSA_Discover_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep);



//! \brief Calls the Discover kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for Discover transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- Discover kernel result.

int SDSA_Discover_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree);



//! \brief Calls the Discover kernel to perform the the post processing (Issuer Authentication, second generate AC...).
//! \param[in] pDataStruct Data buffer for Discover transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- Discover kernel result.

int SDSA_Discover_PerformPostProcessing (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree);



//! \brief Modify several parameters before to use it.
//! \param[in/out] pAidParameters parameters found to manage AID.

void SDSA_Discover_AidRelatedData(T_SHARED_DATA_STRUCT * pAidParameters);


#endif // __SDSA_DISCOVER_H__INCLUDED__
