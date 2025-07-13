/**
* \file TrackIac.c
* \brief This module contains the functions needed to perform service 
* call to Emv Tool application.
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

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "SDK30.h"
#include "del_lib.h"
#include "MyTlvTree.h"
#include "EngineInterfaceLib.h"
#include "_emvdctag_.h"
#include "EmvEngineInterface.h"
#include "Globals.h"
#include "TrackIac.h"

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define EMV_TOOL_APPLI_TYPE						(0x61)

#define EMV_TOOL_SERVICE_IAC_INPUT				(103)
#define EMV_TOOL_SERVICE_IAC_OUTPUT				(104)

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

#ifdef _TRACK_IAC_
static int __TrackIAC_ServiceCall(unsigned short usServiceID, StructProcessStep* pProcessStep);
#endif

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

#ifdef _TRACK_IAC_
static int __TrackIAC_ServiceCall(unsigned short usServiceID, StructProcessStep* pProcessStep)
{
	unsigned char ucPriority;
	int nResult;

	// Does the service exist ?
	if (ServiceGet(EMV_TOOL_APPLI_TYPE, usServiceID, &ucPriority) == 0)
	{
		// Call the service
		if (ServiceCall(EMV_TOOL_APPLI_TYPE, usServiceID, sizeof(StructProcessStep), pProcessStep, &nResult) == 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		// The service does not exist
		return FALSE;
	}
}
#endif

#ifdef _TRACK_IAC_
void TrackIAC_Init(void)
{
	// Call the SPY tool with service = 0 to reset the trace file
	memset(&g_TheProcessStep, 0, sizeof(g_TheProcessStep));
	_DEL_Init(&g_TheProcessStep.DEL);
	__TrackIAC_ServiceCall(EMV_TOOL_SERVICE_IAC_INPUT, &g_TheProcessStep);
}
#endif

#ifdef _TRACK_IAC_
void TrackIAC_TraceInput(StructProcessStep* pProcessStep)
{
	// Trace the input DEL
	__TrackIAC_ServiceCall(EMV_TOOL_SERVICE_IAC_INPUT, pProcessStep);
}
#endif

#ifdef _TRACK_IAC_
void TrackIAC_TraceOutput(StructProcessStep* pProcessStep)
{
	// Trace the output DEL
	__TrackIAC_ServiceCall(EMV_TOOL_SERVICE_IAC_OUTPUT, pProcessStep);
}
#endif
