//! \file
//! Module that manages all the application menus

/////////////////////////////////////////////////////////////////

//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "TlvTree.h"

#include "servcomm.h"
#include "Params.h"
#include "Comm.h"

#include "YesProtocol.h"

#ifndef _YES_PROTOCOL_ONLY_
#include "Hyperterminal.h"
#endif

//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Static function definitions ////////////////////////////////

static int __CommAddStatusCode(TLV_TREE_NODE hOutputTlvTree, int nStatusCode);

//// Functions //////////////////////////////////////////////////

static int __CommAddStatusCode(TLV_TREE_NODE hOutputTlvTree, int nStatusCode)
{
	unsigned char Buffer[2];

	// Status code
	Buffer[0] = (unsigned char)((nStatusCode >> 8) & 0xff);
	Buffer[1] = (unsigned char)(nStatusCode & 0xff);

	return (TlvTree_AddChild(hOutputTlvTree, TAG_COMM_STATUS_CODE, Buffer, 2) != NULL);
}

int CommGetProtocolInfo(NO_SEGMENT AppliNum, TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	unsigned char Buffer[4];
	const char* szComponentVersion;
	int nLength;

	(void)hInputTlvTree;

	// Protocol type
#ifdef _YES_PROTOCOL_ONLY_
	Buffer[0] = COMM_PROTOCOL_TYPE_YES;
#else
	if (Params_GetComPort() < 0)
		Buffer[0] = COMM_PROTOCOL_TYPE_YES;
	else Buffer[0] = COMM_PROTOCOL_TYPE_HYPERTERMINAL;
#endif
	Buffer[1] = 0;
	Buffer[2] = 0;
	Buffer[3] = 0;
	TlvTree_AddChild(hOutputTlvTree, TAG_COMM_PROTOCOL_TYPE, Buffer, 4);

	// Protocol information
	Buffer[0] = 0;
	Buffer[1] = 0;
	Buffer[2] = 0;
	Buffer[3] = 0;
	TlvTree_AddChild(hOutputTlvTree, TAG_COMM_PROTOCOL_INFO, Buffer, 4);

	// Component version
	Buffer[0] = 0x99;
	Buffer[1] = 0x99;

	szComponentVersion = Get_AppliName(AppliNum);
	nLength = strlen(szComponentVersion);
	if (nLength > 4)
	{
		szComponentVersion += nLength - 4;
		if ((szComponentVersion[0] >= '0') && (szComponentVersion[0] <= '9')
			&& (szComponentVersion[1] >= '0') && (szComponentVersion[1] <= '9')
			&& (szComponentVersion[2] >= '0') && (szComponentVersion[2] <= '9')
			&& (szComponentVersion[3] >= '0') && (szComponentVersion[3] <= '9'))
		{
			Buffer[0] = (((unsigned char)(szComponentVersion[0] - '0')) << 4) | ((unsigned char)(szComponentVersion[1] - '0'));
			Buffer[1] = (((unsigned char)(szComponentVersion[2] - '0')) << 4) | ((unsigned char)(szComponentVersion[3] - '0'));
		}
	}
	TlvTree_AddChild(hOutputTlvTree, TAG_COMM_COMPONENT_VERSION, Buffer, 2);

	// Status code
	__CommAddStatusCode(hOutputTlvTree, COMM_ERR_SUCCESS);
	return OK;
}

int CommConfigure(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	(void)hInputTlvTree;

	// Status code
	__CommAddStatusCode(hOutputTlvTree, COMM_ERR_SUCCESS);
	return OK;
}

int CommConnect(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	(void)hInputTlvTree;

	// Status code
	__CommAddStatusCode(hOutputTlvTree, COMM_ERR_SUCCESS);
	return OK;
}

int CommDisconnect(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	(void)hInputTlvTree;

	// Status code
	__CommAddStatusCode(hOutputTlvTree, COMM_ERR_SUCCESS);
	return OK;
}

int CommGetStatus(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	unsigned char nConnectionStatus;

	(void)hInputTlvTree;

	// Connection code
	nConnectionStatus = 0x00;
	TlvTree_AddChild(hOutputTlvTree, TAG_COMM_CONNECTION_STATUS, &nConnectionStatus, 1);

	// Status code
	__CommAddStatusCode(hOutputTlvTree, COMM_ERR_SUCCESS);

	return OK;
}

int CommSendAndReceiveMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
#ifdef _YES_PROTOCOL_ONLY_
	return YesProtocolSendAndReceiveMessage(hInputTlvTree, hOutputTlvTree);
#else
	if (Params_GetComPort() < 0)
		return YesProtocolSendAndReceiveMessage(hInputTlvTree, hOutputTlvTree);
	else return HyperterminalSendAndReceiveMessage(hInputTlvTree, hOutputTlvTree);
#endif
}

int CommSendMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
#ifdef _YES_PROTOCOL_ONLY_
	return YesProtocolSendMessage(hInputTlvTree, hOutputTlvTree);
#else
	if (Params_GetComPort() < 0)
		return YesProtocolSendMessage(hInputTlvTree, hOutputTlvTree);
	else return HyperterminalSendMessage(hInputTlvTree, hOutputTlvTree);
#endif
}

int CommReadMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
#ifdef _YES_PROTOCOL_ONLY_
	return YesProtocolReadMessage(hInputTlvTree, hOutputTlvTree);
#else
	if (Params_GetComPort() < 0)
		return YesProtocolReadMessage(hInputTlvTree, hOutputTlvTree);
	else return HyperterminalReadMessage(hInputTlvTree, hOutputTlvTree);
#endif
}

int CommReceiveMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
#ifdef _YES_PROTOCOL_ONLY_
	return YesProtocolReceiveMessage(hInputTlvTree, hOutputTlvTree);
#else
	if (Params_GetComPort() < 0)
		return YesProtocolReceiveMessage(hInputTlvTree, hOutputTlvTree);
	else return HyperterminalReceiveMessage(hInputTlvTree, hOutputTlvTree);
#endif
}

int CommUnknownService(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	(void)hInputTlvTree;

	// Status code
	__CommAddStatusCode(hOutputTlvTree, COMM_ERR_SERVICE_NOT_SUPPORTED);
	return OK;
}
