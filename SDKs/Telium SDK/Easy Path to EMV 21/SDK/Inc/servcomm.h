/**
* \file servcomm.h
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

#ifndef _COMM_H_
#define _COMM_H_

//! \defgroup Group_servcomm Interface with communication component.
//! @{

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

// Message types
//! \defgroup CommMsgType Generic Communication Message Type
//! @{

#define COMM_MSG_AUTHORISATION_REQUEST						1	//!< Authorisation message type.
#define COMM_MSG_REVERSAL_REQUEST							2	//!< Reversal message type.
#define COMM_MSG_REFUND_REQUEST								3	//!< Refund message type.
#define COMM_MSG_FINANCIAL_TRANSAC_REQUEST					4	//!< Financial transaction request message type.
#define COMM_MSG_FINANCIAL_TRANSAC_CONFIRM					5	//!< Financial transaction confirmation message type.
#define COMM_MSG_ONLINE_ADVICE								6	//!< Advice message type.
#define COMM_MSG_RECONCILIATION_REQUEST						7	//!< Reconciliation message type.
#define COMM_MSG_COLLECTION_INITIALISATION					20	//!< Collection initialisation message type.
#define COMM_MSG_COLLECTION_TERMINATION						21	//!< Collection termination message type.
#define COMM_MSG_COLLECTION_ITEM							22	//!< Collection item message type.
#define COMM_MSG_FILE_UPLOAD_REQUEST						30	//!< File upload request message type.
#define COMM_MSG_FILE_DOWNLOAD_REQUEST						40	//!< File download request message type.
#define COMM_MSG_ADVICE_COLLECTION_ITEM						50	//!< Collection Advice message type.

//! @}

// Tags
//! \defgroup CommIntTags Internal Tags Definition
//! @{

//! \defgroup CommTags Tags used by the Communication Components
//! @{

#define TAG_COMM_STATUS_CODE								0x9F8801	//!< Component status code.
#define TAG_COMM_ERASE_DATE									0x9F8802	//!< All records before this date may be erased.
#define TAG_COMM_ERASE_TSC									0x9F8803	//!< All records with a transaction sequence counter less or equal may be erased.
#define TAG_COMM_BLACK_LIST_SIZE							0x9F8804	//!< Number of card numbers in the blacklist.
#define TAG_COMM_BLACK_LIST_FILE							0x9F8805	//!< File containing the blacklist. No assumption is made whether the list is sorted or not.
#define TAG_COMM_VALIDITY_DATE_LIMIT						0x9F8806	//!< Validity limit of the blacklist.
#define TAG_COMM_NEW_BLACK_LIST_PRESENT						0x9F8807	//!< Indicator that is set when a new blacklist was received.
#define TAG_COMM_MESSAGE_REASON_CODE						0x9F8808
#define TAG_COMM_MESSAGE_RETRANSMISSION						0x9F8809
#define TAG_COMM_MESSAGE_MISSING_FIELD                      0x9F880A	//!< Index of the first mandatory field that was not set.
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

//! \defgroup CommStatus Generic Communication Components status codes
//! @{

// Status codes
#define	COMM_ERR_SUCCESS									0x0000	//!< The service is completed successfully
#define	COMM_ERR_REQUEST_ACCEPTED							0x0010	//!< Asynchronous request accepted. Operation in progress.
#define	COMM_ERR_SERVICE_NOT_SUPPORTED						0x0103	//!< Service not supported.
#define	COMM_ERR_BAD_PARAMETER								0x0104	//!< Bad parameter.
#define	COMM_ERR_COMMUNICATION_PROBLEM						0x0105	//!< Communication problem.
#define	COMM_ERR_TIME_OUT									0x0106	//!< Communication time-out.
#define	COMM_ERR_COMMAND_NOT_ALLOWED						0x0107	//!< Command not allowed (ex: trying to send while not connected).
#define	COMM_ERR_BUSY										0x0108	//!< Command refused because an asynchronous operation is in progress.
#define	COMM_ERR_INVALID_RESPONSE							0x0109	//!< Invalid response from the host.
#define COMM_ERR_INVALID_CONFIG_FILE						0x010A	//!< Invalid configuration file.

//! @}

//! @}

//! @}

// Tags lengths
#define TAG_COMM_STATUS_CODE_LENGTH							2		//!< Length of the tag \ref TAG_COMM_STATUS_CODE.
#define TAG_COMM_ERASE_DATE_LENGTH							3		//!< Length of the tag \ref TAG_COMM_ERASE_DATE.
#define TAG_COMM_ERASE_TRANSAC_SEQ_COUNTER_MAX_LENGTH		4		//!< Maximum length of the tag \ref TAG_COMM_ERASE_TSC.
#define TAG_COMM_BLACK_LIST_SIZE_LENGTH						4		//!< Length of the tag \ref TAG_COMM_BLACK_LIST_SIZE.
#define TAG_COMM_BLACK_LIST_FILE_MAX_LENGTH					255		//!< Maximum length of the tag \ref TAG_COMM_BLACK_LIST_FILE.
#define TAG_COMM_VALIDITY_DATE_LIMIT_LENGTH					3		//!< Length of the tag \ref TAG_COMM_VALIDITY_DATE_LIMIT.
#define TAG_COMM_NEW_BLACK_LIST_PRESENT_LENGTH				2		//!< Length of the tag \ref TAG_COMM_NEW_BLACK_LIST_PRESENT.

#define TAG_COMM_PHYSICAL_LAYER_PARAMETERS_MAX_LENGTH		255		//!< Maximum length of the tag \ref TAG_COMM_PHYSICAL_LAYER_PARAMETERS.
#define TAG_COMM_TRANSPORT_LAYER_PARAMETERS_MAX_LENGTH		255		//!< Maximum length of the tag \ref TAG_COMM_TRANSPORT_LAYER_PARAMETERS.
#define TAG_COMM_APPLICATION_LAYER_PARAMETERS_MAX_LENGTH	255		//!< Maximum length of the tag \ref TAG_COMM_APPLICATION_LAYER_PARAMETERS.
#define	TAG_COMM_MESSAGE_TYPE_LENGTH						2		//!< Length of the tag \ref TAG_COMM_MESSAGE_TYPE.
#define TAG_COMM_PROTOCOL_TYPE_LENGTH						4		//!< Length of the tag \ref TAG_COMM_PROTOCOL_TYPE.
#define TAG_COMM_COMPONENT_VERSION_LENGTH					2		//!< Length of the tag \ref TAG_COMM_COMPONENT_VERSION.
#define TAG_COMM_PROTOCOL_INFO_LENGTH						4		//!< Length of the tag \ref TAG_COMM_PROTOCOL_INFO.
#define TAG_COMM_CONNECTION_STATUS_LENGTH					1		//!< Length of the tag \ref TAG_COMM_CONNECTION_STATUS.
#define TAG_COMM_CALLING_MODE_LENGTH						1		//!< Length of the tag \ref TAG_COMM_CALLING_MODE.
#define TAG_COMM_DATA_LINK_LAYER_PARAMETERS_MAX_LENGTH		255		//!< Maximum length of the tag \ref TAG_COMM_DATA_LINK_LAYER_PARAMETERS.
#define TAG_COMM_CONFIG_ID_LENGTH							4		//!< Length of the tag \ref TAG_COMM_CONFIG_ID.
#define	TAG_COMM_LINK_LAYER_STATUS_LENGTH					4		//!< Length of the tag \ref TAG_COMM_LINK_LAYER_STATUS.
#define TAG_COMM_MESSAGE_MISSING_FIELD_LENGTH               4		//!< Length of the tag \ref TAG_COMM_MESSAGE_MISSING_FIELD.

//! \addtogroup CommIntTags
//! @{

//! \addtogroup CommTags
//! @{

//! \defgroup CallMode Calling modes
//! @{
// Calling modes
#define COMM_CALLING_MODE_SYNCHRONOUS						0		//!< Requests for a synchronous operation.
#define COMM_CALLING_MODE_ASYNCHRONOUS						1		//!< Requests for an asynchronous operation.

//! @}

//! \defgroup ProtType Protocol types
//! @{
// Protocol types (tag TAG_COMM_PROTOCOL_TYPE, byte 0)
#define COMM_PROTOCOL_TYPE_YES								0		//!< Identifies the YES protocol component.
#define COMM_PROTOCOL_TYPE_HYPERTERMINAL					1		//!< Identifies the HyperTerminal protocol component.
#define COMM_PROTOCOL_TYPE_ISO8583_1987						10		//!< Identifies the ISO8583:1987 protocol component.
#define COMM_PROTOCOL_TYPE_ISO8583_1993						11		//!< Identifies the ISO8583:1993 protocol component.
#define COMM_PROTOCOL_TYPE_SPDH								20		//!< Identifies the SPDH protocol component.

//! @}

// Asynchronous event
#define COMM_ASYNCHRONOUS_EVENT_NUMBER						30		//!< Defines the event number that is signaled at the end of an asynchronous operation.
#define COMM_ASYNCHRONOUS_EVENT								(1 << COMM_ASYNCHRONOUS_EVENT_NUMBER)		//!< Defines the event mask to be used with ttestall to wait for the end of an asynchronous operation.

//! @}

//! @}



//! \defgroup CoServ Service definition of the Generic communication components
//! @{

//// Communication component interfaces /////////////////////////

// Default communication component application type
#define I_COMM_DEFAULT_TYPE_APPLI						0x52	//!< Default application type for the communication component.

// EMV historical services
#define I_COMM_INITIATE_ONLINE_TRANSACTION				100		//!< Identifier of the service COMM_Initiate_Online_Transaction.
#define I_COMM_AUTHORISATION_REQUEST					101		//!< Identifier of the service COMM_Authorisation_Request.
#define I_COMM_SEND_ONLINE_ADVICE						102		//!< Identifier of the service COMM_Send_Online_Advice.
#define I_COMM_REVERSAL									103		//!< Identifier of the service COMM_Reversal.
#define I_COMM_SEND_FINANCIAL_TRANSACTION_REQUEST		104		//!< Identifier of the service COMM_Send_Financial_Transaction_Request.
#define I_COMM_FINANCIAL_TRANSACTION_CONFIRMATION		105		//!< Identifier of the service COMM_Financial_Transaction_Confirmation.
#define I_COMM_TERMINATE_ONLINE_TRANSACTION				106		//!< Identifier of the service COMM_Terminate_Online_Transaction.
#define I_COMM_INITIATE_BATCH_DATA_CAPTURE				107		//!< Identifier of the service COMM_Initiate_Batch_Data_Capture.
#define I_COMM_SEND_BATCH_DATA							108		//!< Identifier of the service COMM_Send_Batch_Data.
#define I_COMM_TERMINATE_BATCH_DATA_CAPTURE				109		//!< Identifier of the service COMM_Terminate_Batch_Data_Capture.
#define I_COMM_PERFORM_RECONCILIATION					110		//!< Identifier of the service COMM_Perform_Reconciliation.
#define I_COMM_GET_BLACK_LIST							111		//!< Identifier of the service COMM_Get_Black_List.
#define I_COMM_PIN_ONLINE_REQUEST						112		//!< Identifier of the service COMM_PIN_Online_Request.

// Communication services
#define I_COMM_GET_PROTOCOL_INFO						120		//!< Identifier of the service COMM_Get_Protocol_Info.
#define I_COMM_CONFIGURE								121		//!< Identifier of the service COMM_Configure.
#define I_COMM_CONNECT									122		//!< Identifier of the service COMM_Connect.
#define I_COMM_DISCONNECT								123		//!< Identifier of the service COMM_Disconnect.
#define I_COMM_SEND_AND_RECEIVE_MESSAGE					124		//!< Identifier of the service COMM_Send_And_Receive_Message.
#define I_COMM_SEND_MESSAGE								125		//!< Identifier of the service COMM_Send_Message.
#define I_COMM_GET_STATUS								126		//!< Identifier of the service COMM_Get_Status.
#define I_COMM_READ_MESSAGE								127		//!< Identifier of the service COMM_Read_Message.
#define I_COMM_ABORT									129		//!< Identifier of the service COMM_Abort.
#define I_COMM_RECEIVE_MESSAGE							130		//!< Identifier of the service COMM_Receive_Message.
#define I_COMM_MAKE_RAW_MESSAGE                         131     //!< Identifier of the service COMM_Make_Raw_Message.
#define I_COMM_SEND_RAW_MESSAGE                         132     //!< Identifier of the service COMM_Send_Raw_Message.
#define I_COMM_RECEIVE_RAW_MESSAGE                      133     //!< Identifier of the service COMM_Receive_Raw_Message.
#define I_COMM_PARSE_RAW_MESSAGE                        134     //!< Identifier of the service COMM_Parse_Raw_Message.

//! @}

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

//! \addtogroup CoServ
//! @{

//===========================================================================
//! \brief Sets the application type of the communication component.
//! \param[in] usAppType the application type.
//===========================================================================
void COMM_Set_Application_Type(unsigned short usAppType);

//===========================================================================
//! \brief Retreives the application type of the communication component.
//! \return The application type.
//===========================================================================
unsigned short COMM_Get_Application_Type(void);

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


#ifdef _TRACK_IAC_
/*//! \brief Initialises the IAC tracking. This function erases the log of the IAC events.*/
void InitTrackIAC(void);

/*//! \brief Adds an entry in the IAC events log.
//! \param[in] usAppType the application type of the called component.
//! \param[in] usService the called service.
//! \param[in] nFunction the called function.
//! \param[in] pInputDel the \ref DEL given to the called component.
//! \param[in] pOutputDel the \ref DEL returned by the called component.*/
void TrackIAC(unsigned short usAppType, unsigned short usService,
			int nFunction, const DEL* pInputDel, const DEL* pOutputDel);
#endif


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Initiate_Online_Transaction(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Authorisation_Request(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Send_Online_Advice(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Reversal(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Send_Financial_Transaction_Request(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Financial_Transaction_Confirmation(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Terminate_Online_Transaction(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Initiate_Batch_Data_Capture(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Send_Batch_Data(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Terminate_Batch_Data_Capture(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Perform_Reconciliation(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_Get_Black_List(const DEL* pInputDel);

/*//! \brief Obsolete function. Do not use it anymore.*/
DEL* COMM_PIN_Online_Request(const DEL* pInputDel);


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


/*//! \brief Retreives information about the communication protocol.
//! \param[in] pInputDel a \ref DEL containing the configuration identifier \ref TAG_COMM_CONFIG_ID (optional).
//! \return A \ref DEL containing information about the communication protocol.
//! \see
//! - SMO/SPE-0026.
//! - The documentation of the component.*/
DEL* COMM_Get_Protocol_Info(const DEL* pInputDel);

/*//! \brief Configures the communication component.
//! \param[in] pInputDel a \ref DEL containing the configuration of the component.
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The communication identifier \ref TAG_COMM_CONFIG_ID (optional).
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - The documentation of the component.*/
DEL* COMM_Configure(const DEL* pInputDel);

/*//! \brief Connects to the host.
//! \param[in] pInputDel a \ref DEL containing:
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.*/
DEL* COMM_Connect(const DEL* pInputDel);

/*//! \brief Disconnects from the host.
//! \param[in] pInputDel a \ref DEL containing:
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.*/
DEL* COMM_Disconnect(const DEL* pInputDel);

/*//! \brief Sends a message and waits for an answer.
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
//! - SMO/SPE-0068.*/
DEL* COMM_Send_And_Receive_Message(const DEL* pInputDel);

/*//! \brief Sends a message.
//! \param[in] pInputDel a \ref DEL containing:
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! - The message type \ref TAG_COMM_MESSAGE_TYPE.
//! - The message data (see SMO/SPE-0026).
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.*/
DEL* COMM_Send_Message(const DEL* pInputDel);

/*//! \brief Retreives the status of the component.
//! \param[in] pInputDel a \ref DEL containing:
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The communication status \ref TAG_COMM_CONNECTION_STATUS.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.*/
DEL* COMM_Get_Status(const DEL* pInputDel);

/*//! \brief Retreives the data of an asynchronously received message.
//! \param[in] pInputDel a \ref DEL containing:
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! - The received message type \ref TAG_COMM_MESSAGE_TYPE.
//! - The received message data (see SMO/SPE-0026).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.*/
DEL* COMM_Read_Message(const DEL* pInputDel);

/*//! \brief Aborts a running asynchronous operation.
//! \param[in] pInputDel a \ref DEL containing:
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.*/
DEL* COMM_Abort(const DEL* pInputDel);

/*//! \brief Waits for an incoming message.
//! \param[in] pInputDel a \ref DEL containing:
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! \return A \ref DEL containing:
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! - The received message type \ref TAG_COMM_MESSAGE_TYPE.
//! - The received message data (see SMO/SPE-0026).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.*/
DEL* COMM_Receive_Message(const DEL* pInputDel);

//! @}

//! @}

#endif // _COMM_H_
