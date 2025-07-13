/**
 * \file	DllTesting_Implementation.h
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
 **/

#ifndef __CLESS_SAMPLE_IMPLEMENTATION_H__INCLUDED__
#define __CLESS_SAMPLE_IMPLEMENTATION_H__INCLUDED__


// TDS includes
#include "SDK30.h"
#include "TlvTree.h"
#include "del_lib.h"
#include "bitmap.h"
#include "MSGlib.h"
#include "hterm.h"
#include "XMLs.h"

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

// EMV Lib includes
#include "EmvLib_Tags.h"

// Entry Point includes
#include "EntryPoint_Tags.h"

// Common cless kernel includes
#include "Common_Kernels_Tags.h"
#include "Common_Kernels_API.h"

// PayPass kernel includes
#include "PayPass_Tags.h"
#include "PayPass3_API.h"

// Cless Sample includes
#include "ClessSample_Tags.h"
#include "ClessSample_GuiState.h"
#include "ClessSample_DumpData.h"
#include "ClessSample_Receipt.h"
#include "ClessSample_Common.h"
#include "ClessSample_Scan.h"
#include "ClessSample_PayPass.h"
#include "ClessSample_Parameters.h"
#include "ClessSample_DataExchange.h"
#include "ClessSample_Fill.h"
#include "ClessSample_FinancialCommunication.h"
#include "ClessSample_Customisation.h"
#include "ClessSample_ExplicitSelection.h"
#include "ClessSample_Menu.h"
#include "ClessSample_Disk.h"
#include "ClessSample_BlackList.h"
#include "ClessSample_PinManagement.h"
#include "ClessSample_PinEnManagement.h"
#include "ClessSample_Term.h"
#include "ClessSample_Batch.h"
#include "ClessSample_Torn.h"
#include "ClessSample_TransactionFile.h"
#include "ClessSample_Comevent.h"
#include "ClessSample_Unattended.h"
#include "UserInterfaceHelpers.h"
#include "MessagesDefinitions.h"
#include "ClessSample_XML.h"
#include "servcomm.h"

#include "tlvVar_def.h"
#include "schVar_def.h"

#include "UcmTelium.h"
#include "UcmHostDLL.h"
#include "UcmcLIB.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define NUMBER_OF_ITEMS(Array)					(sizeof(Array)/sizeof((Array)[0]))

#define C_INDEX_TEST_BASE						0x0999 // See global range
#define SERVICE_CUSTOM_KERNEL					C_INDEX_TEST_BASE + 0x0000
#define SERVICE_DE_KERNEL						C_INDEX_TEST_BASE + 0x0001


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

extern long atol(const char *nptr);


#endif // __CLESS_SAMPLE_IMPLEMENTATION_H__INCLUDED__
