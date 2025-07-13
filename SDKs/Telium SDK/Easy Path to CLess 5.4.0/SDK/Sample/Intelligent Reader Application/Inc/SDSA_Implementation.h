/**
 * \file	SDSA_Implementation.h
 * \brief 	This file contains all the includes that are needed.

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
 **/

#ifndef __SDSA_IMPLEMENTATION_H__INCLUDED__
#define __SDSA_IMPLEMENTATION_H__INCLUDED__


// TDS includes
#include "SDK30.h"
#include "TlvTree.h"
#include "del_lib.h"
#include "bitmap.h"
#include "MSGlib.h"

// Cless includes
#include "oem_cless.h"
#include "oem_clmf1.h"

// Generic Tool Library includes
#include "GTL_Assert.h"
#include "GTL_StdTimer.h"
#include "GTL_Traces.h"
#include "GTL_BerTlv.h"
#include "GTL_BerTlvDecode.h"
#include "GTL_Convert.h"
#include "GTL_TagsInfo.h"
#include "GTL_SharedExchange.h"
#include "GTL_SHA.h"

#include "TPass.h"

// Security includes
#include "SEC_interface.h"

// EMV tags definition
#include "EmvLib_Tags.h"

// Entry Point includes
#include "EntryPoint_Tags.h"

// Common cless kernel includes
#include "Common_Kernels_Tags.h"
#include "Common_Kernels_API.h"

// PayPass kernel includes
#include "PayPass_Tags.h"
#include "PayPass_API.h"

// payWave kernel includes
#include "payWave_API.h"
#include "payWave_Tags.h"

// VisaWave kernel includes
#include "VisaWave_API.h"
#include "VisaWave_Tags.h"

// ExpressPay kernel includes
#include "ExpressPay_Tags.h"
#include "ExpressPay3_API.h"

// Interac kernel includes
#include "Interac_Tags.h"
#include "Interac_API.h"

// Discover kernel includes
#include "Discover_Tags.h"
#include "Discover_API.h"

// SDI global includes
#include "SDI_Defines.h"
#include "SDI_Status.h"
#include "SDI_Tags.h"

// SDM global includes
#include "SDM_Services.h"

// SDSA global includes
#include "SDSA_Defines.h"
#include "SDSA_Tags.h"

// SDSA local includes
#include "SDSA_BlackList.h"
#include "SDSA_Common.h"
#include "SDSA_Customisation.h"
#include "SDSA_Disk.h"
#include "SDSA_ExpressPay.h"
#include "SDSA_Fill.h"
#include "SDSA_GuiState.h"
#include "SDSA_Parameters.h"
#include "SDSA_ParametersManagement.h"
#include "SDSA_PayPass.h"
#include "SDSA_payWave.h"
#include "SDSA_Status.h"
#include "SDSA_Term.h"
#include "SDSA_Transaction.h"
#include "SDSA_UserInterfaceHelpers.h"
#include "SDSA_VisaWave.h"
#include "SDSA_MessagesDefinitions.h"
#include "SDSA_Interac.h"
#include "SDSA_Discover.h"


#include "tlvVar_def.h"
#include "schVar_def.h"



/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define NUMBER_OF_ITEMS(Array)					(sizeof(Array)/sizeof((Array)[0]))

#define C_INDEX_TEST_BASE						0x0999 // See global range
#define SERVICE_CUSTOM_KERNEL					C_INDEX_TEST_BASE + 0x0000


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


#endif // __SDSA_IMPLEMENTATION_H__INCLUDED__
