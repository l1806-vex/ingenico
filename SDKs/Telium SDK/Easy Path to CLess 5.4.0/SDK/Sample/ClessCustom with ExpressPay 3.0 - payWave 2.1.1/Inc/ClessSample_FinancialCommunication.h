/**
 * \file	ClessSample_FinancialCommunication.h
 * \brief	Manages the online authorisation.
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


#ifndef __CLESS_SAMPLE_FINANCIAL_COMMUNICATION_H__INCLUDED__
#define __CLESS_SAMPLE_FINANCIAL_COMMUNICATION_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define	COMM_PROCESS_COMPLETED				0x0000


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Manage the online authorisation with the communication component.
//! \param[in,out] pSharedData Data to be sent to the host for onoline authorisation (input) and response tags are added to it (output).
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int ClessSample_FinancialCommunication_ManageAuthorisation (T_SHARED_DATA_STRUCT * pSharedData);



#endif // __CLESS_SAMPLE_FINANCIAL_COMMUNICATION_H__INCLUDED__
