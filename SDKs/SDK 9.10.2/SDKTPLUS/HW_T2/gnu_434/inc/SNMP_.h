/**
 * \file  SNMP_.h
 * \brief This module contains the definition to use the SNMP DLL.
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


#ifndef __SNMP__H__
#define __SNMP__H__

#ifdef __cplusplus
extern "C"
{
#endif


//! \defgroup SNMP_DLL SNMP
//! \par Introduction
//! SNMP provides an architectural model to manage a collection of network elements. These elements are seen
//! as a part of a tree network. The path from the root of the tree to the element is represented as a sequence
//! of numbers (one number by node from the root to the terminal) separated by dots.
//! The terminal can manage "nodes". A node is an abstract object in charge of managing a group of data.
//!
//! The SNMP DLL provides services to handle the SNMP server embedded in Telium System:
//! - Declare applicative data nodes.
//! - Manage incoming requests from the network.
//! - Send response to these requests.
//! - Send "TRAP" messages.
//!
//! <TABLE border="3" cellspacing="0" bordercolor="black">
//! <TR><TD><b>Developers shall read the document <a href="ICO-PE-045-GU-EN_PackIP_SecurityGuidance_UserGuide.html">[Pack IP Security Guidance]</a>
//! which describes best practises for implementing SNMP enabled applications, according to
//! the requirements of the POS Terminal Security Program (PTS) and of the PCI PTS v3 "Open Protocols" module.</b>
//! <br>
//! Every SNMP client knowing the name of the community, and the IP address of the terminal is able
//! to perform accesses onto the terminal. It is not recommended to allow write accesses through the SNMP server,
//! </TD></TR>
//! nor to expose sensitive data through SNMP.
//! </TABLE>
//! @{

//! \brief Data types for SNMP elements.
typedef enum
{
	SNMP_BOOLEAN	= 0x01, //!< Equivalent to ASN.1 type BOOLEAN.
	SNMP_INTEGER	= 0x02, //!< Equivalent to ASN.1 type INTEGER.
	SNMP_UNSIGNED32 = 0x42, //!< Equivalent to ASN.1 type UNSIGNED32.
	SNMP_COUNTER64	= 0x46, //!< Equivalent to ASN.1 type COUNTER64.
	SNMP_BIT_STR	= 0x03, //!< Equivalent to ASN.1 type BIT_STR.
	SNMP_BYTE_STR	= 0x04, //!< Equivalent to ASN.1 type BYTE_STR.
	SNMP_IPADDR		= 0x40, //!< Equivalent to ASN.1 type IPADDRESS.
	SNMP_TABLE		= 0x10  //!< Equivalent to ASN.1 type SEQUENCE.
}SNMP_DATA_TYPE ;

//! \brief Supported SNMP commands.
typedef enum 
{
	SNMP_COMMAND_GET     = 0xA0, //!< Request the value of an element.
	SNMP_COMMAND_GETNEXT = 0xA1, //!< Request the value of the next element (of a table).
	SNMP_COMMAND_SET     = 0xA3, //!< Change the value of an element.
	SNMP_COMMAND_CHECK   = 0xAE  //!< Check the write access on an element.
}SNMP_COMMAND;

//! \brief Error codes to respond to a request.
typedef enum 
{
	SNMP_ERRNO_EOK    =   0, //!< No error.
	SNMP_ERRNO_EINVAL = -26, //!< Invalid argument.
	SNMP_ERRNO_ENOENT = -41, //!< No entry (file or directory).
	SNMP_ERRNO_EPERM  = -57  //!< Operation not allowed.
}SNMP_ERRNO;

//! \brief SNMP server status.
typedef enum
{
	SNMP_STATUS_STARTED = 0, //!< SNMP server started.
	SNMP_STATUS_STOPPED = 1  //!< SNMP server stopped.
}SNMP_SERVER_STATUS;

//! \brief Description of a column in an SNMP table.
typedef struct
{
	unsigned int   nId;       //!< Id of the column.
	SNMP_DATA_TYPE eDataType; //!< Type of the data (\ref SNMP_TABLE is not allowed here).
}T_SNMP_COLUMN_DESC;

//! \brief Description of the data of an SNMP element.
typedef struct
{
	unsigned int        nId;        //!< Id of the element.
	SNMP_DATA_TYPE      eDataType;  //!< Type of the data.
	unsigned int        nNbColumns; //!< Number of columns in the table (set to 0 if \ref eDataType is not \ref SNMP_TABLE).
	T_SNMP_COLUMN_DESC* pColList;   //!< List of columns descriptors (set to NULL if \ref eDataType is not \ref SNMP_TABLE).
	                                //!< The first item must be a unique ID of type \ref SNMP_INTEGER identifying the column of the table.
									//!< See the sample for more details.
}T_SNMP_DATA_DESC ;

//! \brief SNMP request handle.
typedef int SNMP_REQUEST_HANDLE;

//! \brief No key ID returned or needed.
#define SNMP_NO_KEY    (-1)

//! \defgroup SNMP_ERROR_CODES Error codes
//! \brief Error codes returned by SNMP API functions.
//! @{

#define SNMP_SUCCESS                     (   0) //!< No error during the process.
#define SNMP_ERROR_INVALID_PARAMETER     (-100) //!< Function called with an invalid argument.
#define SNMP_ERROR_INVALID_HANDLE        (-101) //!< The handle is invalid.
#define SNMP_ERROR_MEMORY                (-102) //!< No more memory.
#define SNMP_ERROR_NO_SESSION            (-103) //!< No SNMP session opened.
#define SNMP_ERROR_ADD_NODE              (-104) //!< The node cannot be added.
#define SNMP_ERROR_RESOURCE_ALLOCATION   (-105) //!< Resource allocation error.
#define SNMP_ERROR_ALREADY_CONNECTED     (-106) //!< The connection to the SNMP server is already done.
#define SNMP_ERROR_DLL                   (-110) //!< SNMP DLL not found.
#define SNMP_ERROR_SERVICE_NOT_SUPPORTED (-111) //!< Service not supported by the DLL.

//! @}

//! \brief Start the SNMP server.
//! \param[in] usListeningPort  Listening port of the SNMP server. If set to 0, the server will use the default SNMP port (161).
//! \param[in] szRootId Root    OID of the SNMP elements managed by the application.
//! \param[in] szReadCommunity  Community name for reading operations. If set to NULL, the read community name is "Telium_R".
//! \param[in] szWriteCommunity Community name for writing operations. If set to NULL, the write community name is "Telium_W".
//! \return \ref SNMP_SUCCESS or a negative error code (see \ref SNMP_ERROR_CODES).
int SNMP_Server_Start( unsigned short usListeningPort,
					   const char*    szRootId,
					   const char*    szReadCommunity,
					   const char*    szWriteCommunity );

//! \brief Stop and close the connection with the SNMP server.
//! \return \ref SNMP_SUCCESS or a negative error code (see \ref SNMP_ERROR_CODES).
int SNMP_Server_Stop( void );

//! \brief Get the current status of the SNMP service.
//! \param[out] pStatus Current status of the SNMP server.
//! \return \ref SNMP_SUCCESS or a negative error code (see \ref SNMP_ERROR_CODES).
int SNMP_Server_GetStatus( SNMP_SERVER_STATUS* pStatus );

//! \brief Add a new SNMP node.
//! \param[in] nNodeId   ID of the new node. <b>Most significant bit must not be used</b>.
//! \param[in] pDataDesc Description of the data managed by the node.
//! \param[in] nNbData   Number of data elements in the descriptor.
//! \return \ref SNMP_SUCCESS or a negative error code (see \ref SNMP_ERROR_CODES).
int SNMP_Server_AddNode( unsigned int            nNodeId,
						 const T_SNMP_DATA_DESC* pDataDesc,
						 unsigned int            nNbData );

//! \brief Wait for an incoming SNMP request.
//! \param[in] nTimeout Maximum duration to wait for a request (in 1/100s).
//! \return NULL if nothing is received, a \ref SNMP_REQUEST_HANDLE otherwise.
//! \note <b>Once a valid request is received, a call to \ref SNMP_Server_SendResponse()
//! is mandatory, otherwise the SNMP server is stuck</b>.
SNMP_REQUEST_HANDLE SNMP_Server_WaitRequest( unsigned int nTimeout );

//! \brief Decode an incoming SNMP request.
//! \param[in]  hRequest     Handle on the request.
//! \param[out] pCommand     Type of the request.
//! \param[out] pNodeId      ID of the node requested.
//! \param[out] pDataId      ID of the data requested in the node.
//! \param[out] pValue       Data contained in the node (SET command).
//! \param[out] pValueLength Length of the data (SET command).
//! \return \ref SNMP_SUCCESS or a negative error code (see \ref SNMP_ERROR_CODES).
int SNMP_Server_DecodeRequest( SNMP_REQUEST_HANDLE hRequest,
							   SNMP_COMMAND*       pCommand,
							   int*   pNodeId,
							   int*   pDataId,
							   void** pValue,
							   int*   pValueLength );

//! \brief Get information about a SNMP table element.
//! \param[in]  hRequest  Handle on the request.
//! \param[out] pKey      Key used to identify the line of the table requested or \ref SNMP_NO_KEY.
//! \param[out] pColumnId ID of the column requested.
//! \return \ref SNMP_SUCCESS or a negative error code (see \ref SNMP_ERROR_CODES).
int SNMP_Server_GetTableInfo( SNMP_REQUEST_HANDLE hRequest,
							  int* pKey,
							  int* pColumnId );

//! \brief Send a response to a request.
//! \param[in] hRequest      Handle on the request.
//! \param[in] eResponseCode Error code associated to the response.
//! \param[in] pValue        Data buffer (for \ref SNMP_COMMAND_GET and \ref SNMP_COMMAND_GETNEXT only).
//! \param[in] nValueLength  Length of the data (for \ref SNMP_COMMAND_GET and \ref SNMP_COMMAND_GETNEXT only).
//! \param[in] nKey          Key of the value (for SNMP tables only, \ref SNMP_NO_KEY otherwise).
//! \param[in] bInt32Value   TRUE if the value is a numericial (or a boolean) storable using 32-bits. FALSE otherwise (for \ref SNMP_BYTE_STR...).
//! \return \ref SNMP_SUCCESS or a negative error code (see \ref SNMP_ERROR_CODES).
int SNMP_Server_SendResponse( SNMP_REQUEST_HANDLE hRequest,
							  SNMP_ERRNO eResponseCode,
							  void*      pValue,
							  int        nValueLength,
							  int        nKey,
							  int        bInt32Value );

//! \brief Send a TRAP message.
//! \param[in] szIpAddress Address of the peer.
//! \param[in] szCommunity Community name to use in the request. Can be NULL, in that case the community will be "public".
//! \param[in] szMessage   Message to send.
int SNMP_Server_SendEvent( const char* szIpAddress,
						   const char* szCommunity,
						   const char* szMessage );

//! \defgroup SAMPLE_SNMP SNMP sample.
//! \brief Basic use of SNMP interfaces.
//!
//! \par Sample description.
//! This sample shows how to use the SNMP API functions:
//! - declare an applicative node with "simple" items and a table.
//! - manage incoming requests from an SNMP client, and send response.
//! - send TRAP messages.
//!
//! \include SNMP__Sample_01.c
//! \example SNMP__Sample_01.c

//! @}

#ifdef __cplusplus
}
#endif


#endif //__SNMP__H__
