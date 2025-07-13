/**
 * \file	CST_servcomm.c
 * \brief 	This module contains the interface with a communication component.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "CST_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static unsigned short g_usCommAppType = I_COMM_DEFAULT_TYPE_APPLI;
static StructProcessStep g_ProcessStep;
static DEL g_Del;


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static void COMM_CopyInput(const DEL* aDEL, _DEL_* _vDEL);
static void COMM_CopyOutput(_DEL_* _vDEL, DEL* aDEL);
static DEL* COMM_Call_Service(unsigned short usAppType, unsigned short usServiceID,
					unsigned short usInfoAppType, unsigned short usInfoService,
					int nInfoFunction, const DEL* pInputDel,
					StructProcessStep* pProcessStep, DEL* pOutputDel);
static DEL* COMM_Service(unsigned short usServiceID, const DEL* pInputDel);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


void COMM_CopyInput(const DEL* aDEL, _DEL_* _vDEL)
{
	CopyEntree((DEL*)aDEL, _vDEL);
}

void COMM_CopyOutput(_DEL_* _vDEL, DEL* aDEL)
{
	CopySortie(_vDEL, aDEL);
}

static DEL* COMM_Call_Service(unsigned short usAppType, unsigned short usServiceID,
					unsigned short usInfoAppType, unsigned short usInfoService,
					int nInfoFunction, const DEL* pInputDel,
					StructProcessStep* pProcessStep, DEL* pOutputDel)
{
	unsigned char ucPriority;
	int nResult;

	// Does the service exist ?
	if (ServiceGet(usAppType, usServiceID, &ucPriority) == 0)
	{
		if (pInputDel != NULL)
		{
			// Copy the input DEL to a global _DEL_ object
			COMM_CopyInput(pInputDel, &pProcessStep->DEL);
		}
		else
		{
			// Empty the global _DEL_ object
			_DEL_init(&pProcessStep->DEL);
		}

		// Call the service
		pProcessStep->type_code = usInfoAppType;
		pProcessStep->service = usInfoService;
		pProcessStep->function = nInfoFunction;
		ServiceCall(usAppType, usServiceID, sizeof(StructProcessStep), pProcessStep, &nResult);

		if (pOutputDel != NULL)
		{
			// Copy the filled local _DEL_ object into a global DEL object
			COMM_CopyOutput(&pProcessStep->DEL, pOutputDel);
		}

		return (pOutputDel);
	}
	else
	{
		// The service does not exist
		return (NULL);
	}
}

static DEL* COMM_Service(unsigned short usServiceID, const DEL* pInputDel)
{
	DEL* pOutputDel;

	// Call the communication component
	pOutputDel = COMM_Call_Service(g_usCommAppType, usServiceID, g_usCommAppType, usServiceID,
									0, pInputDel, &g_ProcessStep, &g_Del);

#ifdef _TRACK_IAC_
	// Send the input and output DEL to the SPY tool
	TrackIAC(g_usCommAppType, usServiceID, 0, pInputDel, pOutputDel);
#endif

	return (pOutputDel);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


DEL* COMM_Configure(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_CONFIGURE, pInputDel);
}

DEL* COMM_Connect(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_CONNECT, pInputDel);
}

DEL* COMM_Disconnect(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_DISCONNECT, pInputDel);
}

DEL* COMM_Send_And_Receive_Message(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_SEND_AND_RECEIVE_MESSAGE, pInputDel);
}
