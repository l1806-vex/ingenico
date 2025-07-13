#ifndef __HTTP_H__
#define __HTTP_H__

#ifdef __cplusplus
extern "C"
{
#endif

//! \file        HTTP_.h
//! \brief This module contains all the HTTP definitions.
//!
//
// Copyright (c) 2005 Ingenico France, rue claude Chappe,
// 07503 Guilherand-Granges, France, All Rights Reserved.
//
// Ingenico France has intellectual property rights relating
// to the technology embodied in this software.  In particular,
// and without limitation, these intellectual property rights
// may include one or more patents.
//
// This software is distributed under licenses restricting
// its use, copying, distribution, and decompilation.
// No part of this software may be reproduced in any form
// by any means without prior written authorization of
// Ingenico France.
//

//! \defgroup TCPIP_HTTP HTTP/HTTPS functions
//! \ingroup TCPIP
//! \brief This module contains all the HTTP definitions.
//! @{

//
// Error codes
//
//! \defgroup HTTP_ERROR_CODES Error codes
//! \brief Error codes returned by HTTP API functions.
//! @{

#define HTTP_SERVER_OK							(  0)   //!< Function succeeds.
#define HTTP_SERVER_ERROR_MEMORY				(- 1)   //!< Memory error for handle allocation.
#define HTTP_SERVER_ERROR_SOCKET				(- 2)   //!< Cannot create or activate the listening socket.
#define HTTP_SERVER_ERROR_HANDLE				(- 3)   //!< Invalid handle parameter.
#define HTTP_SERVER_ERROR_TIMEOUT				(- 4)   //!< Timeout, no request received.
#define HTTP_SERVER_ERROR_NO_REQUEST			(- 5)   //!< No request is currently in progress.
#define HTTP_SERVER_ERROR_INVALID_ARG			(- 6)   //!< *hHandle cannot be NULL.
#define HTTP_SERVER_ERROR_DISK					(- 7)   //!< Cannot mount the destination disk.
#define HTTP_SERVER_ERROR_MALFORMED_REQUEST		(- 8)   //!< Unable to parse the request.
#define HTTP_SERVER_ERROR_SERVER_CLOSED			(- 9)   //!< The server is not running.
#define HTTP_SERVER_ERROR_CLIENT_SOCKET			(-10)   //!< Client socket error.
#define HTTP_SERVER_ERROR_CLIENT_TIMEOUT		(-11)   //!< Client did not respond in the last 10 seconds.
#define HTTP_SERVER_ERROR_INVALID_PROFILE		(-12)   //!< Cannot load the SSL profile.
#define HTTP_SERVER_ERROR_SSL_DLL_NOT_FOUND		(-13)   //!< Cannot open the SSL DLL.

//! @}

//
// HTTP Commands
//
#define HTTP_SERVER_NOCOMMAND			0	//!< No command received.
#define HTTP_SERVER_GET					1	//!< HTTP GET request.
#define HTTP_SERVER_POST				2	//!< HTTP POST request.
#define HTTP_SERVER_PUT					3	//!< HTTP PUT request.
#define HTTP_SERVER_UNKNOWN_COMMAND		4	//!< Command not yet supported.

//
// Default response messages
//
#define HTTP_SERVER_PAGE_404 "HTTP/1.1 404" " KO" "\r\n" "\r\n" "The requested URL could not be retreived !\r\n"   //!< Default HTML page for HTTP error 404.
#define HTTP_SERVER_HTTP_200 "HTTP/1.1 200" " OK" "\r\n" "\r\n"                                                    //!< Default HTML page for HTTP error 200.
#define HTTP_SERVER_PAGE_501 "HTTP/1.1 501" " KO" "\r\n" "\r\n" "Unsupported command\r\n"                          //!< Default HTML page for HTTP error 501.

//
// HTTP Internal value
//
#define HTTP_SERVER_MAX_HEADER_PARAM		 32
#define HTTP_SERVER_MAX_HEADER_PARAMNAME	 32
#define HTTP_SERVER_MAX_HEADER_PARAMVALUE	 64
#define HTTP_SERVER_MAX_URI					128
#define HTTP_SERVER_MAX_DATA				 32
#define HTTP_SERVER_MAX_DATA_NAME			 32
#define HTTP_SERVER_MAX_DATA_VALUE			 64
#define HTTP_SERVER_MAX_FILE_NUMBER			  6
#define HTTP_SERVER_MAX_FILE_NAME			 32
#define HTTP_SERVER_MAX_FILE_TYPE			 32
#define HTTP_SERVER_MAX_DISK_NAME			 16
#define HTTP_SERVER_MAX_BOUNDARY			 80

//
// Definition of a server handle
//
//! \brief Definition of HTTP_SERVER_HANDLE.
typedef void * HTTP_SERVER_HANDLE;

//
// SSL and X509 handle definition if needed
//
#ifndef __SSL_HANDLES__

//! \brief Definition of SSL_HANDLE.
typedef void * SSL_HANDLE;
//! \brief Definition of SSL_SERVER_HANDLE.
typedef void * SSL_SERVER_HANDLE;
//! \brief Definition of SSL_PROFILE_HANDLE.
typedef void * SSL_PROFILE_HANDLE;
//! \brief Definition of X509_HANDLE.
typedef void * X509_HANDLE;

#define __SSL_HANDLES__

#endif


//
//! \brief Handle on a HTTP Request
//
typedef struct {

	// Request
	char	m_nCommand;						//!< HTTP Command.
	char	m_szHttpVersion[4];				//!< HTTP Version (0.9, 1.0 or 1.1)
	char	m_szURI[HTTP_SERVER_MAX_URI];	//!< Address of the requested page (This string is always internally set to upper case to be compliant with Telium File System syntax).
	
	// Header parameters
	short	m_nHeaderParamNb;																		//!< Number of elements in the header
	char	m_szHeaderParamName [HTTP_SERVER_MAX_HEADER_PARAM][HTTP_SERVER_MAX_HEADER_PARAMNAME];	//!< Name of the parameter
	char	m_szHeaderParamValue[HTTP_SERVER_MAX_HEADER_PARAM][HTTP_SERVER_MAX_HEADER_PARAMVALUE];	//!< Value of the parameter
	short	m_nBoundaryPos;																			//!< Internal use only
	
	// Data
	short	m_nDataNumber;														//!< Number of data
	char	m_szDataName [HTTP_SERVER_MAX_DATA][HTTP_SERVER_MAX_DATA_NAME];		//!< Name of the current data
	short	m_nFileIndex [HTTP_SERVER_MAX_DATA];								//!< Internal use 
	char	m_szDataValue[HTTP_SERVER_MAX_DATA][HTTP_SERVER_MAX_DATA_VALUE];	//!< Value of the current data
	
	// Files
	short	m_nFileNumber;															//<! Number of files in the data
	char	m_szFilename  [HTTP_SERVER_MAX_FILE_NUMBER][HTTP_SERVER_MAX_FILE_NAME];	//<! Name of the received file
	char	m_szFileType  [HTTP_SERVER_MAX_FILE_NUMBER][HTTP_SERVER_MAX_FILE_TYPE];	//<! Type of the received file
	char    m_szFsFileName[HTTP_SERVER_MAX_FILE_NUMBER][16];						//<! Name of the file saved in the file system
	int     m_nFileLength [HTTP_SERVER_MAX_FILE_NUMBER];							//<! Length of the file (in bytes)

	// Added
	int  m_nContentLength;							//!< Value of the Content-Length parameter (if any).
	char m_szBoundary[HTTP_SERVER_MAX_BOUNDARY];	//!< HTTP Boundary (if any).

	// Client information
	char        m_szClientAddress[16];			//!< Address of the connected client.
	int         m_nClientPort;					//!< Port of the connected client.
} HTTP_SERVER_DATA;

//
// Start the HTTP/HTTPS Server
//

//! \brief This function starts the HTTP server on the given port. A handle is
//! allocated and returned.
//! \param pHandle : Handle on the HTTP(S) server.
//! \param nPort : Listening port (usually 80 for HTTP and 443 for HTTPS).
//! \param szDestDisk : Disk name where the server stores the downloaded files. This parameter can be set to NULL: in that case, the server won't store any files.
//! \return 
//! - \ref HTTP_SERVER_OK or a negative error code.
//! - \ref HTTP_SERVER_OK : the server is launched.
//! - \ref HTTP_SERVER_ERROR_MEMORY
//! - \ref HTTP_SERVER_ERROR_SOCKET
//! - \ref HTTP_SERVER_ERROR_DISK
//! - \ref HTTP_SERVER_ERROR_INVALID_PROFILE
//! - \ref HTTP_SERVER_ERROR_SSL_DLL_NOT_FOUND
//! \note 
//! The function mounts the destination disk. This disk is unmounted when the server is stopped (see function HTTP_Server_Close() described below).
int HTTP_Server_Open ( HTTP_SERVER_HANDLE *pHandle,
					   unsigned int nPort,
					   const char *szDestDisk );


//! \brief Start the HTTPS Server
//! \param pHandle : Handle onto the Http server (output).
//! \param nPort : HTTPS input port
//! \param szDestDisk : Name of the disk that will receive the files (may be NULL if no file expected)
//! \param szSslProfileName : Name of the profile 
//! \param bUseCache : Use HTTPS server cache or not
//! \param bCheckPeer : Authenticate the client (mutual authentication) 
//! \return 
//! - \ref HTTP_SERVER_OK
//! - \ref HTTP_SERVER_ERROR_MEMORY
//! - \ref HTTP_SERVER_ERROR_SOCKET
//! - \ref HTTP_SERVER_ERROR_DISK
//! - \ref HTTP_SERVER_ERROR_INVALID_PROFILE
//! - \ref HTTP_SERVER_ERROR_SSL_DLL_NOT_FOUND
//! - \ref HTTP_SERVER_ERROR_INVALID_ARG 
int HTTPS_Server_Open( HTTP_SERVER_HANDLE *pHandle,
					   unsigned int nPort,
					   const char *szDestDisk,
                       const char* szSslProfileName,
					   int bUseCache,
					   int bCheckPeer );

//
// Wait for a request
//
//! \brief This function waits for the reception of an HTTP request. The request is
//! decoded and returned in the parameter of type HTTP_SERVER_DATA (described below).
//! \param hHandle : Handle on the HTTP server.
//! \param nTimeout : Duration to wait for a request.
//! \param pRequest : A pointer on the decoded HTTP request.
//! \return 
//! - \ref HTTP_SERVER_OK 
//! - \ref HTTP_SERVER_ERROR_TIMEOUT
//! - \ref HTTP_SERVER_ERROR_HANDLE
//! - \ref HTTP_SERVER_ERROR_SOCKET
//! - \ref HTTP_SERVER_ERROR_CLIENT_TIMEOUT
//! - \ref HTTP_SERVER_ERROR_CLIENT_SOCKET
//! - \ref HTTP_SERVER_ERROR_MALFORMED_REQUEST
//! \note 
//! The function creates a connection dedicated to the treatment of the request. The pointer on the request is internally allocated, it must not be released by the application. If the call to HTTP_Server-WaitRequest() function is successful (return code equal to HTTP_SERVER_OK), a call to HTTP_SendResponse() is mandatory to terminate the dedicated connection properly. For any other return codes, the connection with the client, if established, is automatically closed.
int HTTP_Server_WaitRequest ( HTTP_SERVER_HANDLE hHandle,
							  unsigned int nTimeout,
							  HTTP_SERVER_DATA **pRequest );

//! \brief Waits for a request.
//! \param hHandle : Handle on the HTTPS server;
//! \param nTimeout : Duration to wait a request.
//! \param pRequest : The decoded request (output). 
//! \return 
//! - \ref HTTP_SERVER_OK
//! - \ref HTTP_SERVER_ERROR_TIMEOUT
//! - \ref HTTP_SERVER_ERROR_SOCKET
//! - \ref HTTP_SERVER_ERROR_CLIENT_TIMEOUT
//! - \ref HTTP_SERVER_ERROR_CLIENT_SOCKET
//! - \ref HTTP_SERVER_ERROR_MALFORMED_REQUEST
//! - \ref HTTP_SERVER_ERROR_HANDLE
int HTTPS_Server_WaitRequest( HTTP_SERVER_HANDLE hHandle,
							  unsigned int nTimeout,
							  HTTP_SERVER_DATA **pRequest );

//
// Send the response
//

//! \brief This function responds to an HTTP request.
//! \param hHandle : Handle on the HTTP server.
//! \param pcDataBuffer : Buffer containing the response to send.
//! \param nDataSize : Size of the buffer response.
//! \return 
//! - \ref HTTP_SERVER_OK or a negative error code.
//! - \ref HTTP_SERVER_ERROR_HANDLE
//! - \ref HTTP_SERVER_ERROR_NO_REQUEST
//! - \ref HTTP_SERVER_ERROR_SERVER_CLOSED
//! - \ref HTTP_SERVER_ERROR_SOCKET
//! \note 
//! This function sends an HTTP response and then close the dedicated
//! connection. It must be called after the success of the call to the function
//! HTTP_Server_WaitRequest().
int HTTP_Server_SendResponse ( HTTP_SERVER_HANDLE hHandle,
							   const char *pcDataBuffer,
							   unsigned int nDataSize );

//! \brief Send the response
//! \param hHandle : Handle on the HTTP server
//! \param pcDataBuffer : The response buffer
//! \param nDataSize : Size of the response buffer
//! \return 
//! - \ref HTTP_SERVER_OK
//! - \ref HTTP_SERVER_ERROR_SOCKET
//! - \ref HTTP_SERVER_ERROR_HANDLE
//! - \ref HTTP_SERVER_ERROR_NO_REQUEST
//! - \ref HTTP_SERVER_ERROR_SERVER_CLOSED
int HTTPS_Server_SendResponse( HTTP_SERVER_HANDLE hHandle,
							   const char *pcDataBuffer,
							   unsigned int nDataSize );

//
// Stop the server
//

//! \brief This function stops the HTTP server and releases the handle and all the
//! resources used by the server.
//! \param hHandle : Handle on the HTTP server.
//! \return 
//! - \ref HTTP_SERVER_OK or a negative error code.
//! - \ref HTTP_SERVER_ERROR_HANDLE
//! \note 
//! The destination folder is unmounted.
int HTTP_Server_Close ( HTTP_SERVER_HANDLE hHandle );

//! \brief Stop the server
//! \param hHandle : Handle onto the Http server. 
//! \param hHandle : NULL Handle (output).
//! \return 
//! - \ref HTTP_SERVER_OK
//! - \ref HTTP_SERVER_ERROR_HANDLE
int HTTPS_Server_Close( HTTP_SERVER_HANDLE hHandle );

//
// Get SSL handles on a HTTPS server
//

//! \brief Get SSL handles on a HTTPS server.
//! \param hHandle : Handle onto the Https server
//! \param hSession : Handle on the current connection (if any)
//! \param hProfile : Handle on the server SSL profile
//! \return 
//! - \ref HTTP_SERVER_OK
//! - \ref HTTP_SERVER_ERROR_HANDLE
int HTTPS_Server_GetHandles( HTTP_SERVER_HANDLE hHandle, SSL_HANDLE *hSession, SSL_PROFILE_HANDLE *hProfile );

//! @}


//! \defgroup HTTP_SAMPLE	HTTP server sample
//! \ingroup TCPIP_SAMPLES
//!
//! The following code shows how to launch an HTTP server and how to process the GET requests.
//!
//! \include HTTP__Sample_01.c
//! \example HTTP__Sample_01.c

#ifdef __cplusplus
}
#endif


#endif // __HTTP_H__
