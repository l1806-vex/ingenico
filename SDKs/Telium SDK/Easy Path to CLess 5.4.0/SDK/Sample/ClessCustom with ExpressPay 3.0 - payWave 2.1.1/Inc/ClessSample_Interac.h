/**
 * \file	ClessSample_Interac.h
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

#ifndef __CLESS_SAMPLE_INTERAC_H__INCLUDED__
#define __CLESS_SAMPLE_INTERAC_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////
#define CLESS_SAMPLE_MODE_INTERAC			1		/*!< Interac Sample GUI mode. */

/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Manage the debug mode for Interac kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void ClessSample_Interac_DebugActivation (int bActivate);



//! \brief Perform the Interac kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int ClessSample_Interac_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep);



//! \brief Calls the Interac kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for Interac transaction.
//!	\return
//!		- Interac kernel result.

int ClessSample_Interac_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct);

//! \brief Check in the parameter file if the GUI mode to use is Interac.
void ClessSample_Interac_SetInteracGuiMode (void);

//! \brief Check if the Interac GUI mode is activated.
//!	\return
//!		- TRUE if Interac GUI mode is used.
//!		- FALSE else.
int ClessSample_Interac_IsInteracGuiMode (void);

//! \brief Get the timeout value for card detection process from the parameter file.
//! \param[out] pNoCardTimeOut the timeout value (in milliseconds).
//! \return
//!		- TRUE if tag is present.
//!		- FALSE else.
int ClessSample_Interac_GetNoCardTimeOut (unsigned long *pNoCardTimeOut);


//! \brief Initialize the timer when card detection starts.
void Interac_StartDetectionTimer (void);


//! \brief Get the timer value.
//!	\return The tick value.
unsigned long Interac_GetDetectionTimer (void);


//! \brief Set the variable to display or not the "NO CARD" message when timeout elapsed.
//! \param[in] bValue : TRUE -> message will be displayed, FALSE -> message will not be displayed
void Interac_SetDisplayNoCard (int bValue);


//! \brief Get the variable to display or not the "NO CARD" message when timeout elapsed.
//!	\return
//!		- TRUE message will be displayed.
//!		- FALSE message will not be displayed.
int Interac_GetDisplayNoCard (void);


#endif // __CLESS_SAMPLE_INTERAC_H__INCLUDED__
