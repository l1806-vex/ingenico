/**
 * \file SDI_Maintenance.h
 * \brief Defines the interface of the maintenance services.
 *
 *
 * \author	Ingenico France
 * \author	Copyright (c) 2010 Ingenico France, 1 rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico France has intellectual property rights relating to the technology embodied\n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico France.
 **/

#ifndef __SDI_MAINTENANCE_H__INCLUDED__
#define __SDI_MAINTENANCE_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup SDI_Maintenance_InterfaceFunctions
//! @{

//! \brief Turn the intelligent reader in LLT mode for local loading.
//! The connection with the intelligent reader will be closed on reader side and then the reader will be put in LLT mode. The intelligent reader will reset after LLT process.
//! Note this function is synchronous, blocking.
//! \return
//! - \ref SDI_STATUS_OK : if the Local Loading command has been sent.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a Maintenance process is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_Maintenance_LocalLoading (void);


 
//! \brief Turn the intelligent reader in maintenance mode (call the component in charge of the maintenance). The intelligent reader will reset after maintenance process.
//! Note this function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application in charge of the maintenance mode (optionnal). If not specified (0), the intelligent reader will try to call the default application to perform the maintenance.
//! \param[in] nServiceId Identifies the service in charge of the maintenance mode (optionnal). If not specified (0), the intelligent reader will try to call the default application to perform the maintenance.
//! \param[in] hTlvTreeIn Contains data needed by the application that will manage the maintenance in the intelligent reader (optionnal).
//! \return
//! - \ref SDI_STATUS_OK : if the Start maintenance command has been sent (the given application or the default application is loaded in the reader and will be called).
//! - \ref SDI_STATUS_KO : if there is no application able to manage the maintenance mode:
//!			- if nAppliId and nServiceId are given: the given application is not loaded in the reader or the given application does not define the given service.
//!			- if nAppliId and nServiceId are set to 0: the default application in charge of the maintenance is not loaded in the reader.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a Maintenance process is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_Maintenance_Start (const int nAppliId, const int nServiceId, const TLV_TREE_NODE hTlvTreeIn);

//! @}

#endif // __SDI_MAINTENANCE_H__INCLUDED__
