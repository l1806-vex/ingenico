/**
 * \file	CST_Implementation.h
 * \brief 	This file contains all the includes that are needed.
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


#include "SDK30.h"
#include "del_lib.h"

#include "TlvTree.h"

// Generic Tool Library includes
#include "GTL_Assert.h"
#include "GTL_StdTimer.h"
#include "GTL_Traces.h"
#include "GTL_TagsInfo.h"
#include "GTL_BerTlv.h"
#include "GTL_BerTlvDecode.h"
#include "GTL_Convert.h"
#include "GTL_SHA.h"
#include "GTL_SharedExchange.h"

// Security includes
#include "SEC_interface.h"

// Common cless kernel includes
#include "EmvLib_Tags.h"

// Generic cless tags
#include "Cless_Generic_Tags.h"

// Common kernel tags
#include "Common_Kernels_Tags.h"
#include "Common_Kernels_API.h"

// payWave kernel includes
#include "payWave_Tags.h"

// PayPass kernel includes
#include "PayPass_Tags.h"

// ExpressPay kernel includes
#include "ExpressPay_Tags.h"
#include "ExpressPay_API.h"

// VisaWave kernel includes
#include "VisaWave_Tags.h"

// Interac kernel includes
#include "Interac_Tags.h"

// SD common includes
#include "SDI_Defines.h"
#include "SDI_Status.h"
#include "SDI_Tags.h"

// SDI global includes
#include "SDI_Interface.h"
#include "SDI_Maintenance.h"
#include "SDI_Payment.h"
#include "SDI_System.h"

// SDSA global includes
#include "SDSA_Defines.h"
#include "SDSA_Tags.h"

#include "tlvVar_def.h"
#include "schVar_def.h"

// CST includes
#include "CST_Common.h"
#include "CST_Batch.h"
#include "CST_BlackList.h"
#include "CST_Disk.h"
#include "CST_DumpData.h"
#include "CST_ExpressPay.h"
#include "CST_FinancialCommunication.h"
#include "CST_Menu.h"
#include "CST_Parameters.h"
#include "CST_PayPass.h"
#include "CST_payWave.h"
#include "CST_PinEnManagement.h"
#include "CST_PinManagement.h"
#include "CST_Receipt.h"
#include "CST_Scan.h"
#include "CST_servcomm.h"
#include "CST_TaskStatus.h"
#include "CST_Term.h"
#include "CST_Tests.h"
#include "CST_TlvTreeDel.h"
#include "CST_TransactionFile.h"
#include "CST_UserInterfaceHelpers.h"
#include "CST_VisaWave.h"
#include "CST_MessagesDefinitions.h"
#include "CST_Interac.h"
#include "CST_Discover.h"


/////////////////////////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////////////////////////

#define NUMBER_OF_ITEMS(Array)					(sizeof(Array)/sizeof((Array)[0]))

// SDSA application type
#define nSDSAAppliId				0x0123

/////////////////////////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Global data definitions ////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////////////////////////
