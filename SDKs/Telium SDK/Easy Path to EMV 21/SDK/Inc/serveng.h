/**
* \file serveng.h
* \brief This module contains the definitions to access to the EMV Engine Component.
* EMV Engine is a part of the EMV Generic architecture, for Telium Platform.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

#ifndef _SERVENG_H_
#define _SERVENG_H_

//! \defgroup Group_serveng Definitions to access EMV Engine component.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define I_EMVENG_Type_Appli								(0x50)		//!< ENGINE application number.

/*-------------------------------------------------------------------------*/
/* ENGINE component services identification                                */
/*-------------------------------------------------------------------------*/
//! \defgroup EMVService EMV Service
//! @{
//! \defgroup EngServ Engine Services definition              
//! @{
#define I_ENG_DO_TRANSACTION_DEL						(100)		//!< Engine service do transaction del.
#define I_ENG_RESUME_TRANSACTION_DEL					(260)		//!< Engine service resume transaction del.

#define I_EMVENG_Start_Transaction						I_ENG_DO_TRANSACTION_DEL

//! @}

//! @}

//! @}

#endif
