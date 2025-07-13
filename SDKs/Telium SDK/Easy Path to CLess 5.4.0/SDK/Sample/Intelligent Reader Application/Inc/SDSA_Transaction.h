/**
 * \file	SDSA_Transaction.h
 * \brief 	Perform a transaction in explicit selection (without interaction with the Manager).
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


/////////////////////////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////////////////////////

#define E_USER_EVENT_CANCEL					31									//!< User event bit for cancel.
#define USER_EVENT_CANCEL					(1 << E_USER_EVENT_CANCEL)			//!< Cancel event.

#define E_USER_EVENT_STATUS					30									//!< User event bit for status change.
#define USER_EVENT_STATUS					(1 << E_USER_EVENT_STATUS)			//!< Status change event.

#define E_USER_EVENT_CANCEL_STATUS			29									//!< User event bit to stop the status checking in progress.
#define USER_EVENT_CANCEL_STATUS			(1 << E_USER_EVENT_CANCEL_STATUS)	//!< Stop status checking event.


/////////////////////////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Global data definitions ////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////////////////////////

//! \brief Function called to perform explicit transaction (card detection and application selection).
//! \param[in] hInputTlvTree Contains the input data to perform the transaction.
//! \param[out] pOutputTlvTree Output TLV Tree containing the transaction result.
//! \return
//!	- \ref 
//!	- \ref SDI_STATUS_NO_PARAMETER if there is no loaded parameter, so transaction cannot be performed.
//!	- \ref SDI_STATUS_MISSING_DATA if there is a missing mandatory parameter.
//!	- \ref SDI_STATUS_INVALID_DATA if the provided data in the input parameter is not correct.
//! - Any other kernel specific return

int SDSA_DoTransaction (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);



//! \brief Function called to perform the transaction post processing.
//! \param[in] hInputTlvTree Contains the input data to perform the transaction.
//! \param[out] pOutputTlvTree Output TLV Tree containing the transaction result.
//! \return
//!	- \ref SDI_STATUS_UNKNOWN if the kernel identifier is not known.
//! - Any other application status.

int SDSA_PostProcessing (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);



//! \brief Cancels the transaction "in progress".
//! \return
//!	- \ref SDI_STATUS_OK.

int SDSA_CancelTransaction (void);



//! \brief Get the application data.
//! \param[in] hInputTlvTree Indicates the list of tag to be requested.
//! \param[out] pOutputTlvTree Contains the requested tags.
//! \return
//!	- \ref SDI_STATUS_OK if correctly managed. All the requested and present data are provided in the output structure.
//!	- \ref SDI_STATUS_KO if an error occured.
//!	- \ref SDI_STATUS_INVALID_DATA if provided data is not correct or pOutputTlvTree is null.

int SDSA_GetPaymentData (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);



//! \brief Clear the transaction data.
//! \return
//!	- \ref SDI_STATUS_OK if correctly cancelled.

int SDSA_ClearPaymentData (void);



//! \brief Perform the card removal.
//! \param[in] hInputTlvTree Contains the \ref TAG_SDSA_WAIT_CARD_REMOVAL tag indicating if the reader shall wait card removal or not.
//! \return
//!	- \ref SDI_STATUS_OK if processing correctly performed.
//!	- \ref SDI_STATUS_CANCELLED if processing has been cancelled.
//!	- \ref SDI_STATUS_KO if an error occured.

int SDSA_WaitCardRemoval (const TLV_TREE_NODE hInputTlvTree);



//! \brief Function that allows adding proprietary commands for specific needs.
//! \param[in] hInputTlvTree Contains the input data.
//! \param[out] pOutputTlvTree Contains output data.
//! \return
//!	- \ref SDI_STATUS_OK if correctly performed.
//!	- \ref SDI_STATUS_MISSING_DATA if a mandatory input data is missing.

int SDSA_Generic_UserCommand_01 (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);

