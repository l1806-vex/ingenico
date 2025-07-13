/**
 * \file	SDSA_Status.h
 * \brief	Describes the different SDSA status.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2010 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __SDSA_STATUS_H__INCLUDED__
#define __SDSA_STATUS_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Initialise the state manager.

void SDSA_State_Initialisation (void);



//! \brief Get the current state.
//!	\return The reader state.

int SDSA_State_GetCurrentState (void);



//! \brief Set the current state.
//! \param[in] nState State to be set.

void SDSA_State_SetCurrentState (const int nState);



//! \brief Get the status of the transaction.
//! \param[in] hInputTlvTree Contains the current status and the status on which the caller wish to be notified.
//! \param[out] pOutputTlvTree Contains the status application current status.
//! \return
//!	- \ref SDI_STATUS_OK if correctly performed.
//!	- \ref SDI_STATUS_MISSING_DATA if a mandatory input data is missing.
//!	- \ref SDI_STATUS_CANCELLED if the process has been cancelled.

int SDSA_Status_GetStatus (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);



//! \brief Stop the status checking in progress.
//! \return
//!	- \ref SDI_STATUS_OK if correctly performed.

int SDSA_Status_GetStatusCancel (void);


#endif // __SDSA_STATUS_H__INCLUDED__
