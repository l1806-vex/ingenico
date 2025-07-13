/**
* \file cu_comm.c
* \brief This module contains the functions needed for exchanges with the acquirer host.
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

#include "SDK30.H"
#include "_emvdctag_.h"
#include "del_lib.h"
#include "def_tag.h"
#include "cu_file.h"
#include "MyTlvTree.h"
#include "convert.h"
#include "EngineInterfaceLib.h"
#include "cu_comm.h"
#include "cu_serv.h"
#include "cu_entry.h"
/* ISO8583 includes */
#include "iso8583.h"
/* COMM includes */
#include "servcomm.h"
#include "LinkLayer.h"

//! \addtogroup Group_cu_comm
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define COMM_AUTHOR_MSG                        1
#define COMM_ADVICE_MSG                        2
#define COMM_REVERSAL_MSG                      3
#define COMM_START_TRANSAC_DOWNLOAD            4
#define COMM_TRANSAC_DOWNLOAD                  5
#define COMM_TERMINATE_TRANSAC_DOWNLOAD        6
#define COMM_ADVICE_DOWNLOAD                   7

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
//! \brief This function configures the link layer and the ISO8583 with 
//! a TCP/IP access through Ethernet.
//! \param[in] szIpAddress : IP Adress.
//! \param[in] nTcpPort : port number.
//! \param[in] nTimeout : timeout value.
//! \param[in] nRepetitions : number of repetitions.
//! \param[out] pOutputTLVTree : TLV tree containing the configuration.
//===========================================================================
static void EMVCUST_BuildCommConfig_(char* szIpAddress, unsigned int nTcpPort,
									unsigned int nTimeout, unsigned int nRepetitions, TLV_TREE_NODE *pOutputTLVTree)
{
	static unsigned char PhysicalConfig[40];
	static unsigned char TransportConfig[40];
	static unsigned char AppProtocolConfig[40];
	int nOffset;
	DataElement Element;


	// Build an output TLV Tree

	// Physical layer parameters
	nOffset = 0;
	PhysicalConfig[nOffset + 0] = LL_PHYSICAL_T_LINK;
	PhysicalConfig[nOffset + 1] = LL_PHYSICAL_L_LINK;
	PhysicalConfig[nOffset + 2] = LL_PHYSICAL_V_ETHERNET;
	nOffset += 2 + PhysicalConfig[nOffset + 1];

	Element.tag = LL_TAG_PHYSICAL_LAYER_CONFIG;
	Element.length = nOffset;
	Element.ptValue = PhysicalConfig;
	TlvTree_AddChild(*pOutputTLVTree, Element.tag, Element.ptValue, Element.length);

	// Transport layer parameters
	// TCP/IP
	nOffset = 0;
	TransportConfig[nOffset + 0] = LL_TRANSPORT_T_PROTOCOL;
	TransportConfig[nOffset + 1] = LL_TRANSPORT_L_PROTOCOL;
	TransportConfig[nOffset + 2] = LL_TRANSPORT_V_TCPIP;
	nOffset += 2 + TransportConfig[nOffset + 1];

	TransportConfig[nOffset + 0] = LL_TCPIP_T_HOST_NAME;
	TransportConfig[nOffset + 1] = strlen(szIpAddress);
	strcpy((char*)&TransportConfig[nOffset + 2], szIpAddress);
	nOffset += 2 + TransportConfig[nOffset + 1];

	TransportConfig[nOffset + 0] = LL_TCPIP_T_PORT;
	TransportConfig[nOffset + 1] = LL_TCPIP_L_PORT;
	TransportConfig[nOffset + 2] = nTcpPort & 0xff;
	TransportConfig[nOffset + 3] = (nTcpPort >> 8) & 0xff;
	TransportConfig[nOffset + 4] = (nTcpPort >> 16) & 0xff;
	TransportConfig[nOffset + 5] = (nTcpPort >> 24) & 0xff;
	nOffset += 2 + TransportConfig[nOffset + 1];

	Element.tag = LL_TAG_TRANSPORT_LAYER_CONFIG;
	Element.length = nOffset;
	Element.ptValue = TransportConfig;
	TlvTree_AddChild(*pOutputTLVTree, Element.tag, Element.ptValue, Element.length);

	// Application protocol parameters
	// ISO8583
	nOffset = 0;
	AppProtocolConfig[nOffset + 0] = TAG_ISO8583_T_TIMEOUT;
	AppProtocolConfig[nOffset + 1] = TAG_ISO8583_L_TIMEOUT;
	AppProtocolConfig[nOffset + 2] = (unsigned char)(nTimeout >> 24);
	AppProtocolConfig[nOffset + 3] = (unsigned char)(nTimeout >> 16);
	AppProtocolConfig[nOffset + 4] = (unsigned char)(nTimeout >> 8);
	AppProtocolConfig[nOffset + 5] = (unsigned char)nTimeout;
	nOffset += 2 + AppProtocolConfig[nOffset + 1];

	AppProtocolConfig[nOffset + 0] = TAG_ISO8583_T_RESEND;
	AppProtocolConfig[nOffset + 1] = TAG_ISO8583_L_RESEND;
	AppProtocolConfig[nOffset + 2] = nRepetitions;
	nOffset += 2 + AppProtocolConfig[nOffset + 1];

	AppProtocolConfig[nOffset + 0] = TAG_ISO8583_T_DESCRIPTOR_ID;
	AppProtocolConfig[nOffset + 1] = TAG_ISO8583_L_DESCRIPTOR_ID;
	AppProtocolConfig[nOffset + 2] = 1;
	nOffset += 2 + AppProtocolConfig[nOffset + 1];

	AppProtocolConfig[nOffset + 0] = TAG_ISO8583_T_FILENAME;
	strcpy(&AppProtocolConfig[nOffset + 2], "ISO8583.BIN");
	AppProtocolConfig[nOffset + 1] = strlen(&AppProtocolConfig[nOffset + 2]) + 1;
	nOffset += 2 + AppProtocolConfig[nOffset + 1];

	AppProtocolConfig[nOffset + 0] = TAG_ISO8583_T_PATH;
	strcpy(&AppProtocolConfig[nOffset + 2], "/HOST/");
	AppProtocolConfig[nOffset + 1] = strlen(&AppProtocolConfig[nOffset + 2]) + 1;
	nOffset += 2 + AppProtocolConfig[nOffset + 1];

	///////////////////////////////////////////////
	// The frame size is needed by MIT
	AppProtocolConfig[nOffset + 0] = TAG_ISO8583_T_FRAME_SIZE_TYPE;
	AppProtocolConfig[nOffset + 1] = TAG_ISO8583_L_FRAME_SIZE_TYPE;
	AppProtocolConfig[nOffset + 2] = TAG_ISO8583_V_FRAME_SIZE_TYPE_MSBF;
	nOffset += 2 + AppProtocolConfig[nOffset + 1];

	AppProtocolConfig[nOffset + 0] = TAG_ISO8583_T_FRAME_SIZE_LENGTH;
	AppProtocolConfig[nOffset + 1] = TAG_ISO8583_L_FRAME_SIZE_LENGTH;
	AppProtocolConfig[nOffset + 2] = TAG_ISO8583_V_FRAME_SIZE_LENGTH_DEFAULT;
	nOffset += 2 + AppProtocolConfig[nOffset + 1];
	///////////////////////////////////////////////

	Element.tag = TAG_COMM_APPLICATION_LAYER_PARAMETERS;
	Element.length = nOffset;
	Element.ptValue = AppProtocolConfig;
	TlvTree_AddChild(*pOutputTLVTree, Element.tag, Element.ptValue, Element.length);

}


//===========================================================================
//! \brief This function gets the transaction from the EMV D/C tags database.
//! \return TLV tree containing the tags read in database.
//===========================================================================
static TLV_TREE_NODE EMVCUST_Get_transaction_tags_from_db_TLVtree (void)
{
	TLV_TREE_NODE hTree;
	static const unsigned long RequiredTags[] = { TAG_CVR_RESULT, TAG_APPLI_CRYPTOGRAMME_AC, 
		TAG_CRYPTOGRAM_INFORMATION_DATA, TAG_ISSUER_APPLICATION_DATA, TAG_UNPREDICTABLE_NUMBER,
		TAG_ATC, TAG_TVR, TAG_AIP, TAG_TERMINAL_CAPABILITIES, TAG_TERMINAL_COUNTRY_CODE,
		TAG_TERMINAL_TYPE, TAG_IFD_SERIAL_NUMBER, TAG_AMOUNT_OTHER_NUM, TAG_TRANSACTION_DATE,
		TAG_TRANSACTION_TYPE, TAG_AMOUNT_AUTH_NUM, TAG_TRANSACTION_CURRENCY_CODE, 
		TAG_TRANSACTION_CURRENCY_EXP, TAG_AID_ICC, TAG_VERSION_NUMBER_TERMINAL, TAG_APPLI_PRIM_ACCOUNT_NB,
		TAG_APPLI_PRIM_ACCOUNT_NB_SEQ_NB, TAG_TRANSACTION_SEQ_COUNTER, TAG_AUTOMATE, TAG_PIN_CODE,
		TAG_APPLI_EXPIRATION_DATE, TAG_TRACK2_EQU_DATA, TAG_SERVICE_CODE };
	/* TAG_TRANSACTION_CATEGORY_CODE, TAG_POS_ENTRY_MODE_CODE, TAG_AMOUNT_AUTH_BIN
	TAG_APPLI_EFFECTIVE_DATE, TAG_AMOUNT_OTHER_BIN, TAG_MERCHANT_CATEGORY_CODE, 
	TAG_MERCHANT_IDENTIFIER, TAG_TERMINAL_IDENTIFICATION, TAG_TRANSACTION_TIME */


	// Retrieve all RequiredTags from EMVDC Data base
	hTree = Engine_GetDataElements(sizeof(RequiredTags) / sizeof(RequiredTags[0]), RequiredTags);

	// Remove tags with no value
	hTree = TlvTree_Clean(hTree);

	// Point of Service Entry Mode
	// Special need in case of ISO8583-1993 Protocol. Useless with other Protocols                                                            */
	// Point of Service Entry Mode
	TlvTree_AddChild(hTree, TAG_CUST_POS_ISO8583_93, Pos_8583_93, LEN_CUST_POS_ISO8583_93);

	return hTree;
}

//===========================================================================
//! \brief This function builds a communication TLV Tree.
//! \param[in,out] pInOutTLVTree : input / output TLV tree.
//! \li as input : input TLV tree.
//! \li as output : input TLV tree and communication tags.
//! \param[in] nMsgType : communication message type.
//===========================================================================
static void EMVCUST_Build_comm_TLVTree (TLV_TREE_NODE *pInOutTLVTree , int nMsgType)
{
	DataElement elt_DEL;
	unsigned short found;
	static unsigned char MessageType[2];
	static unsigned char ProcessingCode[3];
	static unsigned char ExpirationDate[2];
	static unsigned char FunctionCode[2];
	static unsigned char MsgReasonCode[2];
	//static unsigned char AmountsOriginal[12];
	static unsigned char SecurityInfo1[8] = { 0x98, 0x01, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00 };
	//static unsigned char SecurityInfo2[8] = { 0x96, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00 };

	// Processing code
	found = CUSERV_Extract_Element_TLV_Tree(pInOutTLVTree, TAG_TRANSACTION_TYPE, &elt_DEL);
	if (found)
	{
		ProcessingCode[0] = elt_DEL.ptValue[0];
		ProcessingCode[1] = 0x00;
		ProcessingCode[2] = 0x00;

		elt_DEL.tag = TAG_ISO8583_DEFAULT_FIELD(3);
		elt_DEL.length = sizeof(ProcessingCode);
		elt_DEL.ptValue = ProcessingCode;
		TlvTree_AddChild(*pInOutTLVTree, elt_DEL.tag, elt_DEL.ptValue, elt_DEL.length);
	}

	// Authorised amount
	found = CUSERV_Extract_Element_TLV_Tree(pInOutTLVTree, TAG_AMOUNT_AUTH_NUM, &elt_DEL);
	if (found)
	{
		elt_DEL.tag = TAG_ISO8583_DEFAULT_FIELD(4);
		TlvTree_AddChild(*pInOutTLVTree, elt_DEL.tag, elt_DEL.ptValue, elt_DEL.length);
	}

	// Expiration date
	found = CUSERV_Extract_Element_TLV_Tree(pInOutTLVTree, TAG_APPLI_EXPIRATION_DATE, &elt_DEL);
	if (found)
	{
		ExpirationDate[0] = elt_DEL.ptValue[0];
		ExpirationDate[1] = elt_DEL.ptValue[1];

		TlvTree_AddChild(*pInOutTLVTree, TAG_ISO8583_DEFAULT_FIELD(14), ExpirationDate, sizeof(ExpirationDate));
	}

	// Function code
	switch(nMsgType)
	{
	case COMM_REVERSAL_MSG:
		FunctionCode[0] = 0x04;
		FunctionCode[1] = 0x00;
		break;
	case COMM_TRANSAC_DOWNLOAD:
	case COMM_ADVICE_DOWNLOAD:
		// Default : off-line, same amount
		FunctionCode[0] = 0x02;
		FunctionCode[1] = 0x00;

		found = CUSERV_Extract_Element_TLV_Tree(pInOutTLVTree, TAG_AUTHORISATION_RESPONSE_CODE, &elt_DEL);
		if (found)
		{
			if (elt_DEL.length == 2)
			{
				if ((elt_DEL.ptValue[0] == '0') && (elt_DEL.ptValue[1] == '0'))
				{
					// On-line, same amount
					FunctionCode[1] = 0x01;
				}
			}
		}
		break;
	case COMM_START_TRANSAC_DOWNLOAD:
		FunctionCode[0] = 0x08;
		FunctionCode[1] = 0x01;
		break;
	case COMM_TERMINATE_TRANSAC_DOWNLOAD:
		FunctionCode[0] = 0x08;
		FunctionCode[1] = 0x02;
		break;

	case COMM_AUTHOR_MSG:
	case COMM_ADVICE_MSG:
	default:
		FunctionCode[0] = 0x01;
		FunctionCode[1] = 0x00;
		break;
	}

	TlvTree_AddChild(*pInOutTLVTree, TAG_ISO8583_DEFAULT_FIELD(24), FunctionCode, sizeof(FunctionCode));

	// Message Reason Code
	if ((nMsgType == COMM_ADVICE_MSG) || (nMsgType == COMM_REVERSAL_MSG)
		|| (nMsgType == COMM_START_TRANSAC_DOWNLOAD) || (nMsgType == COMM_TERMINATE_TRANSAC_DOWNLOAD))
	{
		if (nMsgType == COMM_ADVICE_MSG)
		{
			// TODO: Message Reason Code for advice messages
			MsgReasonCode[0] = 0x00;
			MsgReasonCode[1] = 0x00;
		}
		else if ((nMsgType == COMM_START_TRANSAC_DOWNLOAD) || (nMsgType == COMM_TERMINATE_TRANSAC_DOWNLOAD))
		{
			MsgReasonCode[0] = 0x86;
			MsgReasonCode[1] = 0x01;
		}
		else
		{
			switch(ucComm_Message_reason_code)
			{
			case TAG_COMM_CUSTOMER_CANCELLATION:
				MsgReasonCode[0] = 0x40;
				MsgReasonCode[1] = 0x00;
				break;
			case TAG_COMM_SUSPECTED_MALFUNCTION:
				MsgReasonCode[0] = 0x40;
				MsgReasonCode[1] = 0x02;
				break;
			case TAG_COMM_RESPONSE_RECEIVED_TOO_LATE:
				MsgReasonCode[0] = 0x40;
				MsgReasonCode[1] = 0x06;
				break;
			case TAG_COMM_TIMED_OUT_AT_TAKING_MONEY:
				MsgReasonCode[0] = 0x40;
				MsgReasonCode[1] = 0x18;
				break;
			case TAG_COMM_TIME_OUT_WAITING_FOR_RESPONSE:
				MsgReasonCode[0] = 0x40;
				MsgReasonCode[1] = 0x21;
				break;
			case TAG_COMM_ICC_GENERATED_ACC:
				MsgReasonCode[0] = 0x44;
				MsgReasonCode[1] = 0x99;
				break;

			default:
				MsgReasonCode[0] = 0x00;
				MsgReasonCode[1] = 0x00;
				break;
			}
		}

		TlvTree_AddChild(*pInOutTLVTree, TAG_ISO8583_93_MSG_REASON_CODE, MsgReasonCode, sizeof(MsgReasonCode));
	}

	if (nMsgType == COMM_REVERSAL_MSG)
	{
		// TODO: Amounts Original
		/*        memset(AmountsOriginal, 0, sizeof(AmountsOriginal));

		TlvTree_AddChild(*pInOutTLVTree, TAG_ISO8583_DEFAULT_FIELD(30), AmountsOriginal, sizeof(AmountsOriginal));
		*/
	}

	// Card Acceptor Terminal ID
	found = CUSERV_Extract_Element_TLV_Tree(pInOutTLVTree, 0x9F1E, &elt_DEL);
	if (found)
	{
		elt_DEL.tag = TAG_ISO8583_DEFAULT_FIELD(41);
		TlvTree_AddChild(*pInOutTLVTree, elt_DEL.tag, elt_DEL.ptValue, elt_DEL.length);
	}

	// Currency Code Transaction
	found = CUSERV_Extract_Element_TLV_Tree(pInOutTLVTree, 0x5F2A, &elt_DEL);
	if (found)
	{
		elt_DEL.tag = TAG_ISO8583_DEFAULT_FIELD(49);
		TlvTree_AddChild(*pInOutTLVTree, elt_DEL.tag, elt_DEL.ptValue, elt_DEL.length);
	}


	if (nMsgType == COMM_AUTHOR_MSG)
	{
		found = CUSERV_Extract_Element_TLV_Tree(pInOutTLVTree, TAG_AUTOMATE, &elt_DEL);
		if (found)
		{
			// Is an online PIN entered ?
			if (*elt_DEL.ptValue == INPUT_PIN_ON)
			{
				found = CUSERV_Extract_Element_TLV_Tree(pInOutTLVTree, TAG_PIN_CODE, &elt_DEL);
				if (found)
				{
					// PIN data
					elt_DEL.tag = TAG_ISO8583_DEFAULT_FIELD(52);
					TlvTree_AddChild(*pInOutTLVTree, elt_DEL.tag, elt_DEL.ptValue, elt_DEL.length);

					// Security control information
					TlvTree_AddChild(*pInOutTLVTree, TAG_ISO8583_DEFAULT_FIELD(53), SecurityInfo1, sizeof(SecurityInfo1));
				}
			}
		}
	}

	// Set the message type
	switch(nMsgType)
	{
	case COMM_AUTHOR_MSG:
		MessageType[0] = (unsigned char)(COMM_MSG_AUTHORISATION_REQUEST >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_AUTHORISATION_REQUEST);
		break;
	case COMM_ADVICE_MSG:
		MessageType[0] = (unsigned char)(COMM_MSG_ONLINE_ADVICE >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_ONLINE_ADVICE);
		break;
	case COMM_REVERSAL_MSG:
		MessageType[0] = (unsigned char)(COMM_MSG_REVERSAL_REQUEST >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_REVERSAL_REQUEST);
		break;
	case COMM_START_TRANSAC_DOWNLOAD:
		MessageType[0] = (unsigned char)(COMM_MSG_COLLECTION_INITIALISATION >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_COLLECTION_INITIALISATION);
		break;
	case COMM_TRANSAC_DOWNLOAD:
		MessageType[0] = (unsigned char)(COMM_MSG_COLLECTION_ITEM >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_COLLECTION_ITEM);
		break;
	case COMM_ADVICE_DOWNLOAD:
		MessageType[0] = (unsigned char)(COMM_MSG_ADVICE_COLLECTION_ITEM >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_ADVICE_COLLECTION_ITEM);
		break;
	case COMM_TERMINATE_TRANSAC_DOWNLOAD:
		MessageType[0] = (unsigned char)(COMM_MSG_COLLECTION_TERMINATION >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_COLLECTION_TERMINATION);
		break;
	default:
		MessageType[0] = 0;
		MessageType[1] = 0;
		break;
	}

	TlvTree_AddChild(*pInOutTLVTree, TAG_COMM_MESSAGE_TYPE, MessageType, TAG_COMM_MESSAGE_TYPE_LENGTH);

}


//===========================================================================
void EMVCUST_BuildCommConfig_ISO8583(unsigned int nTimeout, unsigned int nRepetitions, TLV_TREE_NODE *pOutputTLVTree)
{
	EMVCUST_BuildCommConfig_("10.138.2.47", 3331, nTimeout, nRepetitions, pOutputTLVTree);
}


//===========================================================================
void EMVCUST_BuildISO8583_autho_TLVTree (TLV_TREE_NODE *pOutputTLVTree)
{
	*pOutputTLVTree = EMVCUST_Get_transaction_tags_from_db_TLVtree();

	EMVCUST_Build_comm_TLVTree (pOutputTLVTree , COMM_AUTHOR_MSG);
}



//===========================================================================
void EMVCUST_Build_reversal_TLVTree_Iso8583(TLV_TREE_NODE *pOutputTLVTree)
{

	*pOutputTLVTree = EMVCUST_Get_transaction_tags_from_db_TLVtree();

	// Build output TLV tree
	EMVCUST_Build_comm_TLVTree (pOutputTLVTree , COMM_REVERSAL_MSG);
}


//===========================================================================
TLV_TREE_NODE EMVCUST_Build_start_transac_download_TLVTree(TLV_TREE_NODE *pInputTLVTree)
{

	// Build output TLV tree
	EMVCUST_Build_comm_TLVTree (pInputTLVTree , COMM_START_TRANSAC_DOWNLOAD);

	return *pInputTLVTree;

}


//===========================================================================
TLV_TREE_NODE EMVCUST_Build_transac_download_TLVTree(TLV_TREE_NODE *pInputTLVTree)
{
	// Build output TLV tree
	EMVCUST_Build_comm_TLVTree (pInputTLVTree , COMM_TRANSAC_DOWNLOAD);

	return *pInputTLVTree;
}


//===========================================================================
TLV_TREE_NODE EMVCUST_Build_transac_advice_TLVTree(TLV_TREE_NODE *pInputTLVTree)
{
	// Build output TLV tree
	EMVCUST_Build_comm_TLVTree (pInputTLVTree , COMM_ADVICE_DOWNLOAD);

	return *pInputTLVTree;
}


//===========================================================================
TLV_TREE_NODE EMVCUST_Build_terminate_transac_download_TLVTree(TLV_TREE_NODE *pInputTLVTree)
{
	// Build output TLV tree
	EMVCUST_Build_comm_TLVTree (pInputTLVTree , COMM_TERMINATE_TRANSAC_DOWNLOAD);

	return *pInputTLVTree;
}


//===========================================================================
void EMVCUST_Build_advice_TLVTree_Iso8583(TLV_TREE_NODE *pOutputTLVTree)
{
	*pOutputTLVTree = EMVCUST_Get_transaction_tags_from_db_TLVtree();

	// Build output TLV tree
	EMVCUST_Build_comm_TLVTree (pOutputTLVTree , COMM_ADVICE_MSG);
}

//! @}

