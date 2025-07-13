/**
* \file servcomm.c
* \brief This module contains the interface with a communication component.
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
#ifdef _USE_DEL_LIB_
#include "del_lib.h"
#else
#include "del.h"
#endif

#include "MyTlvTree.h"
#include "TlvTreeDel.h"
#include "EngineInterfaceLib.h"
#include "_emvdctag_.h"
#include "TagOS.h"
#include "servcomm.h"
#include "servcomm_TlvTree.h"

#include "TrackIac.h"

//! \addtogroup Group_servcomm
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

static unsigned short g_usCommAppType = I_COMM_DEFAULT_TYPE_APPLI;
static StructProcessStep g_ProcessStep;

#ifdef _TRACK_IAC_
static StructProcessStep g_SpyProcessStep;
#endif

/* ======================================================================== */
/* Static function definitions                                              */
/* ======================================================================== */

static int __COMM_UseTlvTree(void);

static TLV_TREE_NODE __COMM_Call_Service(unsigned short usAppType, unsigned short usServiceID,
										unsigned short usInfoAppType, unsigned short usInfoService,
										int nInfoFunction, const TLV_TREE_NODE hInputTree,
										StructProcessStep* pProcessStep, TLV_TREE_NODE* pOutputTree);
static TLV_TREE_NODE __COMM_Service(unsigned short usServiceID, const TLV_TREE_NODE hInputTree);

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

static int __COMM_UseTlvTree(void)
{
	static int nCommAppType = -1;
	static int bUseTlvTree = -1;
	int nVersion;
	object_descriptor_t DcDescriptor;
	const char* pPtr;

	if ((bUseTlvTree >= 0) && (nCommAppType == g_usCommAppType))
		return bUseTlvTree;

	nCommAppType = g_usCommAppType;
	bUseTlvTree = FALSE;

	// Get the EMV DC descriptor
	if (ObjectGetDescriptor(OBJECT_TYPE_APPLI, g_usCommAppType, &DcDescriptor) == 0)
	{
		if ((DcDescriptor.file_name[8] == '.') && (strncmp((const char*)DcDescriptor.file_name, "3423", 4) == 0))
		{
			// The protocol is EMV COMM

			// Check that the last 4 characters of the file name are digits
			pPtr = &DcDescriptor.file_name[4];
			if ((pPtr[0] >= '0') && (pPtr[0] <= '9') && (pPtr[1] >= '0') && (pPtr[1] <= '9')
				&& (pPtr[2] >= '0') && (pPtr[2] <= '9') && (pPtr[3] >= '0') && (pPtr[3] <= '9'))
			{
				nVersion = (int)((((unsigned int)(pPtr[0] - '0')) << 12) | (((unsigned int)(pPtr[1] - '0')) << 8)
					| (((unsigned int)(pPtr[2] - '0')) << 4) | ((unsigned int)(pPtr[3] - '0')));

				// Versions >= 0505 can use TlvTree
				if (nVersion >= 0x0505)
					bUseTlvTree = TRUE;
			}
		}
	}

	return bUseTlvTree;
}

//===========================================================================
//! \brief This function performs a service call to communication component.
//! \param[in] usAppType : application type.
//! \param[in] usServiceID : service to reach in communication component.
//! \param[in] usInfoAppType : application type.
//! \param[in] usInfoService : service to reach in communication component.
//! \param[in] nInfoFunction : step to call in the service, in case of call to 
//! EMVDC_process_step service.
//! \param[in] hInputTree : input TLV tree containing the data to send to the 
//! communication component.
//! \param[in] pProcessStep : structure \ref StructProcessStep to exchange data.
//! \param[out] pOutputTree : output TLV tree containing : 
//! - the data sent by the communication component, if the service call is successfull.
//! - NULL if the service doesn't exist.
//! \return 
//! - result TLV tree if service call successfull.
//! - NULL if the service doesn't exist.
//===========================================================================
static TLV_TREE_NODE __COMM_Call_Service(unsigned short usAppType, unsigned short usServiceID,
										unsigned short usInfoAppType, unsigned short usInfoService,
										int nInfoFunction, const TLV_TREE_NODE hInputTree,
										StructProcessStep* pProcessStep, TLV_TREE_NODE* pOutputTree)
{
	unsigned char ucPriority;
	int nResult;
	int bResult;

	// Does the service exist ?
	if (ServiceGet(usAppType, usServiceID, &ucPriority) == 0)
	{
		// Empty the global _DEL_ object
		if (__COMM_UseTlvTree())
		{
			if (hInputTree == NULL)
			{
				TLV_TREE_NODE hTmpTree;
				hTmpTree = TlvTree_New(0);
				bResult = (TlvTree_Serialize(hTmpTree, TLV_TREE_SERIALIZER_DEFAULT, (void*)(&pProcessStep->DEL), sizeof(pProcessStep->DEL)) > 0);
				TlvTree_ReleaseEx(&hTmpTree);
			}
			else
			{
				bResult = (TlvTree_Serialize(hInputTree, TLV_TREE_SERIALIZER_DEFAULT, (void*)(&pProcessStep->DEL), sizeof(pProcessStep->DEL)) > 0);
			}
		}
		else
		{
			_DEL_init(&pProcessStep->DEL);
			if (hInputTree != NULL)
			{
				// Copy the input TLV tree to a global _DEL_ object
				bResult = AddTlvTreeToDelValue(&pProcessStep->DEL, hInputTree);
			}
			else bResult = TRUE;
		}

		if (bResult)
		{
			// Call the service
			pProcessStep->type_code = usInfoAppType;
			pProcessStep->service = usInfoService;
			pProcessStep->function = nInfoFunction;

			TrackIAC_TraceInput(pProcessStep);
			bResult = (ServiceCall(usAppType, usServiceID, sizeof(StructProcessStep), pProcessStep, &nResult) == 0);
			TrackIAC_TraceOutput(pProcessStep);

			if (pOutputTree != NULL)
			{
				if (bResult)
				{
					if (__COMM_UseTlvTree())
					{
						TlvTree_Unserialize(pOutputTree, TLV_TREE_SERIALIZER_DEFAULT,
							(void*)(&pProcessStep->DEL), sizeof(pProcessStep->DEL));
					}
					else
					{
						// Copy the filled local _DEL_ object into a global TLV Tree object
						CreateTlvTreeFromDel(pOutputTree, &pProcessStep->DEL);
					}
				}
				else
				{
					*pOutputTree = NULL;
				}
			}
		}

		return (*pOutputTree);
	}
	else
	{
		if (pOutputTree != NULL)
		{
			*pOutputTree = NULL;
		}

		// The service does not exist
		return (NULL);
	}
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//===========================================================================
//! \brief This function performs a service call to communication component.
//! \param[in] usServiceID : service to reach in communication component.
//! \param[in] hInputTree : input TLV tree.
//! \return 
//! - result TLV tree, if service call is successfull.
//! - NULL if the service doesn't exist.
//===========================================================================
static TLV_TREE_NODE __COMM_Service(unsigned short usServiceID, const TLV_TREE_NODE hInputTree)
{
	TLV_TREE_NODE hOutputTree;

	// Call the communication component
	return __COMM_Call_Service(g_usCommAppType, usServiceID, g_usCommAppType, usServiceID,
										0, hInputTree, &g_ProcessStep, &hOutputTree);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//===========================================================================
void COMM_Set_Application_Type(unsigned short usAppType)
{
	g_usCommAppType = usAppType;
}

//===========================================================================
unsigned short COMM_Get_Application_Type(void)
{
	return (g_usCommAppType);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//===========================================================================
TLV_TREE_NODE COMM_Get_Protocol_Info_TlvTree(const TLV_TREE_NODE hInputTLVTree)
{
	return __COMM_Service (I_COMM_GET_PROTOCOL_INFO, hInputTLVTree);
}

//===========================================================================
TLV_TREE_NODE COMM_Configure_TlvTree(const TLV_TREE_NODE hInputTLVTree)
{
	return __COMM_Service (I_COMM_CONFIGURE, hInputTLVTree);
}

//===========================================================================
TLV_TREE_NODE COMM_Connect_TlvTree(const TLV_TREE_NODE hInputTLVTree)
{
	return __COMM_Service(I_COMM_CONNECT, hInputTLVTree);
}

//===========================================================================
TLV_TREE_NODE COMM_Disconnect_TlvTree(const TLV_TREE_NODE hInputTLVTree)
{
	return __COMM_Service(I_COMM_DISCONNECT, hInputTLVTree);	
}

//===========================================================================
TLV_TREE_NODE COMM_Send_And_Receive_Message_TlvTree(const TLV_TREE_NODE hInputTLVTree)
{
	return __COMM_Service(I_COMM_SEND_AND_RECEIVE_MESSAGE, hInputTLVTree);
}

//===========================================================================
TLV_TREE_NODE COMM_Send_Message_TlvTree(const TLV_TREE_NODE hInputTLVTree)
{
	return __COMM_Service(I_COMM_SEND_MESSAGE, hInputTLVTree);
}

//===========================================================================
TLV_TREE_NODE COMM_Get_Status_TlvTree(const TLV_TREE_NODE hInputTLVTree)
{
	return __COMM_Service(I_COMM_GET_STATUS, hInputTLVTree);	
}

//===========================================================================
TLV_TREE_NODE COMM_Read_Message_TlvTree(const TLV_TREE_NODE hInputTLVTree)
{
	return __COMM_Service(I_COMM_READ_MESSAGE, hInputTLVTree);
}

//===========================================================================
TLV_TREE_NODE COMM_Abort_TlvTree(const TLV_TREE_NODE hInputTLVTree)
{
	return __COMM_Service(I_COMM_ABORT, hInputTLVTree);
}

//===========================================================================
TLV_TREE_NODE COMM_Receive_Message_TlvTree(const TLV_TREE_NODE hInputTLVTree)
{
	return __COMM_Service(I_COMM_RECEIVE_MESSAGE, hInputTLVTree);
}

//! @}
