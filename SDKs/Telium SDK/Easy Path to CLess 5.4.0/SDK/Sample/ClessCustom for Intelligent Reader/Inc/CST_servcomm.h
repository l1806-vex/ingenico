/**
 * \file	CST_servcomm.h
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

#ifndef _COMM_H_
#define _COMM_H_

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

// Message types
//! \defgroup CommMsgType Generic Communication Message Type
//! \{

#define COMM_MSG_AUTHORISATION_REQUEST						1			//!< Authorisation message type.
#define COMM_MSG_REVERSAL_REQUEST							2			//!< Reversal message type.
#define COMM_MSG_REFUND_REQUEST								3			//!< Refund message type.
#define COMM_MSG_FINANCIAL_TRANSAC_REQUEST					4			//!< Financial transaction request message type.
#define COMM_MSG_FINANCIAL_TRANSAC_CONFIRM					5			//!< Financial transaction confirmation message type.
#define COMM_MSG_ONLINE_ADVICE								6			//!< Advice message type.
#define COMM_MSG_RECONCILIATION_REQUEST						7			//!< Reconciliation message type.
#define COMM_MSG_COLLECTION_INITIALISATION					20			//!< Collection initialisation message type.
#define COMM_MSG_COLLECTION_TERMINATION						21			//!< Collection termination message type.
#define COMM_MSG_COLLECTION_ITEM							22			//!< Collection item message type.
#define COMM_MSG_FILE_UPLOAD_REQUEST						30			//!< File upload request message type.
#define COMM_MSG_FILE_DOWNLOAD_REQUEST						40			//!< File download request message type.

//! \}

// Tags
//! \defgroup IntTags Internal Tags Definition
//! \{

//! \defgroup CommTags Tags used by the Communication Components
//! \{

#define TAG_COMM_STATUS_CODE								0x9F8801	//!< Component status code.
#define TAG_COMM_ERASE_DATE									0x9F8802	//!< All records before this date may be erased.
#define TAG_COMM_ERASE_TSC									0x9F8803	//!< All records with a transaction sequence counter less or equal may be erased.
#define TAG_COMM_BLACK_LIST_SIZE							0x9F8804	//!< Number of card numbers in the blacklist.
#define TAG_COMM_BLACK_LIST_FILE							0x9F8805	//!< File containing the blacklist. No assumption is made whether the list is sorted or not.
#define TAG_COMM_VALIDITY_DATE_LIMIT						0x9F8806	//!< Validity limit of the blacklist.
#define TAG_COMM_NEW_BLACK_LIST_PRESENT						0x9F8807	//!< Indicator that is set when a new blacklist was received.
#define TAG_COMM_MESSAGE_RETRANSMISSION						0x9F8809
#define TAG_COMM_PHYSICAL_LAYER_PARAMETERS					0x9F8810	//!< See SMO/SPE-0068.
#define TAG_COMM_TRANSPORT_LAYER_PARAMETERS					0x9F8811	//!< See SMO/SPE-0068.
#define TAG_COMM_APPLICATION_LAYER_PARAMETERS				0x9F8812	//!< See the documentation of the component.
#define TAG_COMM_MESSAGE_TYPE								0x9F8813	//!< The message type.
#define TAG_COMM_PROTOCOL_TYPE								0x9F8814	//!< The protocol supported by the component.
#define TAG_COMM_COMPONENT_VERSION							0x9F8815	//!< The component version.
#define TAG_COMM_PROTOCOL_INFO								0x9F8816	//!< Information about the component.
#define TAG_COMM_CONNECTION_STATUS							0x9F881B	//!< Status of the connection.
#define TAG_COMM_CALLING_MODE								0x9F881C	//!< Calling (synchronous or asynchronous).
#define TAG_COMM_DATA_LINK_LAYER_PARAMETERS					0x9F881D	//!< See SMO/SPE-0068.
#define TAG_COMM_CONFIG_ID									0x9F881E	//!< Identify the communication configuration. If not specified, the last used configuration is used.
#define TAG_COMM_LINK_LAYER_STATUS							0x9F881F	//!< The Link Layer status. See SMO/SPE-0068.

//! \}
//! \}

// Tags lengths

#define	TAG_COMM_MESSAGE_TYPE_LENGTH						2				//!< Length of the tag \ref TAG_COMM_MESSAGE_TYPE.


/** @defgroup CoServ Service definition of the Generic communication components              
 *  @{											*/
//// Communication component interfaces /////////////////////////

// Default communication component application type
#define I_COMM_DEFAULT_TYPE_APPLI						0x52			//!< Default application type for the communication component.

// Communication services
#define I_COMM_CONFIGURE								121				//!< Identifier of the service COMM_Configure.
#define I_COMM_CONNECT									122				//!< Identifier of the service COMM_Connect.
#define I_COMM_DISCONNECT								123				//!< Identifier of the service COMM_Disconnect.
#define I_COMM_SEND_AND_RECEIVE_MESSAGE					124				//!< Identifier of the service COMM_Send_And_Receive_Message.
/** @} */


//// Types //////////////////////////////////////////////////////


//// Global variables ///////////////////////////////////////////


//// Functions //////////////////////////////////////////////////


#ifdef _COM_IAC_
//! \brief Initialises the IAC tracking. This function erases the log of the IAC events.
void InitTrackIAC(void);

//! \brief Adds an entry in the IAC events log.
//! \param[in] usAppType the application type of the called component.
//! \param[in] usService the called service.
//! \param[in] nFunction the called function.
//! \param[in] pInputDel the \ref DEL given to the called component.
//! \param[in] pOutputDel the \ref DEL returned by the called component.
void TrackIAC(unsigned short usAppType, unsigned short usService,
			int nFunction, const DEL* pInputDel, const DEL* pOutputDel);
#endif


//! \brief Configures the communication component.
//! \param[in] pInputDel a \ref DEL containing the configuration of the component.
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The communication identifier \ref TAG_COMM_CONFIG_ID (optional).
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - The documentation of the component.
DEL* COMM_Configure(const DEL* pInputDel);

//! \brief Connects to the host.
//! \param[in] pInputDel a \ref DEL containing:
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.
DEL* COMM_Connect(const DEL* pInputDel);

//! \brief Disconnects from the host.
//! \param[in] pInputDel a \ref DEL containing:
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.
DEL* COMM_Disconnect(const DEL* pInputDel);

//! \brief Sends a message and waits for an answer.
//! \param[in] pInputDel a \ref DEL containing:
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! - The message type \ref TAG_COMM_MESSAGE_TYPE.
//! - The message data (see SMO/SPE-0026).
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! - The received message type \ref TAG_COMM_MESSAGE_TYPE.
//! - The received message data (see SMO/SPE-0026).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.
DEL* COMM_Send_And_Receive_Message(const DEL* pInputDel);

/** @} */

#endif // _COMM_H_
