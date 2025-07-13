/**
 * \file	ClessSample_ExpressPay.h
 * \brief	Manages the interface with the ExpressPay contactless kernel.
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

#ifndef __CLESS_SAMPLE_EXPRESSPAY_H__INCLUDED__
#define __CLESS_SAMPLE_EXPRESSPAY_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Unset the Mobile CVM global variable.

void ClessSample_ExpressPay_UnsetMobileCVM (void);



//! \brief Manage the debug mode for ExpressPay kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void ClessSample_ExpressPay_DebugActivation (int bActivate);



//! \brief Perform the ExpressPay kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int ClessSample_ExpressPay_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep);



//! \brief Calls the ExpressPay kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for ExpressPay transaction.
//!	\return
//!		- ExpressPay kernel result.

int ClessSample_ExpressPay_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct);


#endif // __CLESS_SAMPLE_EXPRESSPAY_H__INCLUDED__
