//! \file        PROXY_.h
//! \brief This module contains all the definitions for the proxy management.
//!
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
//
//! \addtogroup TCPIP_PROXY
//! @{
//! \par Introduction
//!
//! The TELIUM SDK TCP/IP package provides services for the IP proxy management. 
//! It supports the proxy protocols : SOCKS4a, SOCKS5 and the HTTP-CONNECT proxy.
//!
//! - The SOCKS4 protocol is described in the RFC 1413.
//! - The SOCKS4a is an extension of the SOCKS4 protocol enabling to perform remotely
//! the DNS address resolution.
//! - The SOCKS5 protocol is described in the RFC 1928. This protocol provides
//! authentication methods.
//! - The HTTP proxy uses the CONNECT HTTP request to operate.
//!
//! <TABLE border="3" cellspacing="0" bordercolor="black">
//! <TR><TD></TD></TR>
//! <TR><TD></TD></TR>
//! <TR><TD><b>Developers shall read the document <a href="ICO-PE-045-GU-EN_PackIP_SecurityGuidance_UserGuide.html">[Pack IP Security Guidance]</a>
//! which describes best practises for implementing IP enabled applications, according to
//! the requirements of the POS Terminal Security Program (PTS).</b></TD></TR>
//! <TR><TD></TD></TR>
//! <TR><TD></TD></TR>
//! </TABLE>
//!
//! Please refer \ref PROXY_SAMPLE (a sample showing how to connect a WEB server through a SOCKS5 proxy).
//!

#ifndef __PROYY_H__
#define __PROYY_H__

#ifdef __cplusplus
extern "C"
{
#endif


//! \defgroup PROXY_TYPE Proxy type
//! \brief Proxy type.
//! @{
#define PROXY_TYPE_NONE			-1	//!< No proxy (unknown type).
#define PROXY_TYPE_SOCKS4		1	//!< SOCKS4a proxy.
#define PROXY_TYPE_SOCKS5		2	//!< SOCKS5 proxy.
#define PROXY_TYPE_HTTP			3	//!< HTTP proxy (HTTP-CONNECT method).

//! @}

//! \defgroup SOCKS5_AUTHENTICATION SOCKS5 authentication methods
//! \brief SOCKS5 authentication methods.
//! @{
// SOCKS5 authentication methods.
#define PROXY_SOCK5_AUTHENT_NONE				(1<<0)	//!< No authentication.
#define PROXY_SOCK5_AUTHENT_GSSSAPI				(1<<1)	//!< GSSAPI (not supported).
#define PROXY_SOCK5_AUTHENT_LOGIN_PASSWORD		(1<<2)	//!< Login/Password method.

// Private authentication methods.
#define PROXY_SOCK5_AUTHENT_PRIVATE1			((unsigned int) (1<<8))		//!< Private authentication method (1).
#define PROXY_SOCK5_AUTHENT_PRIVATE2			((unsigned int) (1<<9))		//!< Private authentication method (2).
#define PROXY_SOCK5_AUTHENT_PRIVATE3			((unsigned int) (1<<10))	//!< Private authentication method (3).
#define PROXY_SOCK5_AUTHENT_PRIVATE4			((unsigned int) (1<<11))	//!< Private authentication method (4).
#define PROXY_SOCK5_AUTHENT_PRIVATE5			((unsigned int) (1<<12))	//!< Private authentication method (5).
#define PROXY_SOCK5_AUTHENT_PRIVATE6			((unsigned int) (1<<13))	//!< Private authentication method (6).
#define PROXY_SOCK5_AUTHENT_PRIVATE7			((unsigned int) (1<<14))	//!< Private authentication method (7).
#define PROXY_SOCK5_AUTHENT_PRIVATE8			((unsigned int) (1<<15))	//!< Private authentication method (8).
//! @}

//! \defgroup PROXY_ERROR Error codes 
//! \brief Error codes.
//! @{
#define PROXY_OK 								0		//!< The operation has been successfully performed.
#define PROXY_ERROR_BAD_ADDRESS 				-10		//!< Invalid address.
#define PROXY_ERROR_BAD_ADDRESS_SIZE 			-11		//!< Invalid address size.
#define PROXY_ERROR_BAD_LOGIN_SIZE 				-12		//!< Invalid login size.
#define PROXY_ERROR_BAD_PASSWORD_SIZE 			-13		//!< Invalid password size.
#define PROXY_ERROR_INVALID_HANDLE				-14		//!< Invalid handle.
#define PROXY_ERROR_INVALID_RESPONSE			-20		//!< Invalid response.
#define PROXY_ERROR_REJECTED_REQUEST			-21		//!< Authentication request is rejected by the server.
#define PROXY_ERROR_IDENTIFICATION				-22		//!< Identification error.
#define PROXY_ERROR_NO_IDENTD					-23		//!< Ident deamon is not supported by the client.
#define PROXY_ERROR_AUTHENTICATION				-25		//!< Authentication error.
#define PROXY_ERROR_AUTHENTICATION_METHOD		-26		//!< Bad authentication method.
#define PROXY_ERROR_GENERAL_FAILURE				-27		//!< General failure.
#define PROXY_ERROR_CONNECTION_NOT_ALLOWED		-28		//!< Connection is not allowed.
#define PROXY_ERROR_NETWORK_UNREACHABLE			-29		//!< Network is not reachable.
#define PROXY_ERROR_HOST_UNREACHABLE			-30		//!< Host is not reachable.
#define PROXY_ERROR_CONNECTION_REFUSED			-31		//!< Connection is refused.
#define PROXY_ERROR_TTL_EXPIRATION				-32		//!< Time To Live (TTL) counter error.
#define PROXY_ERROR_COMMAND_NOT_SUPPORTED		-33		//!< Command is not supported.
#define PROXY_ERROR_ADDRESS_TYPE_NOT_SUPPORTED	-34		//!< Address type is not supported.
#define PROXY_ERROR_INVALID_PROXY_TYPE			-40		//!< Invalid proxy type.
#define PROXY_ERROR_INVALID_PROXY_ADDRESS		-41		//!< Invalid proxy address.
#define PROXY_ERROR_SOCKET_FAILED				-42		//!< Socket creation error.
#define PROXY_ERROR_CONNECT_FAILED				-43		//!< Connection error (host not found).
#define PROXY_ERROR_INVALID_SOCKET				-44		//!< Invalid socket.
#define PROXY_ERROR_INVALID_PARAMETER			-45		//!< Invalid parameter.
#define PROXY_ERROR_UNKNOWN						-50		//!< Internal error.

#define PROXY_ERROR_HTTP						-1000	//!< Index starting the range of the HTTP proxy errors.

//! @}

//! \brief Definition of a proxy connection handle.
typedef void * PROXY_HANDLE;


//! \brief This function instantiates a proxy connection handle.
//! \return 
//! The connection handle (>0) if OK.
//! or NULL when an error occured.
//! \note 
//! - The allocated connection handle must be freed by a call to \ref PROXY_Free().
//! - By default, the new allocated connection handle uses the default proxy (refer \ref PROXY_SetProxy()).
PROXY_HANDLE PROXY_New(void);

//! \brief This function frees a proxy connection handle.
//! \param s : connection handle to release.
//! \return 
//! - The connection handle (>0) if OK,
//! - or a negative error code (refer: \ref PROXY_ERROR).
//! \note This function must be called each time a connection handle has instantiated
//! by a call to the \ref PROXY_New function.
int PROXY_Free( PROXY_HANDLE s );

//! \brief This function sets the proxy parameters of a connection handle. 
//! \param s : connection handle.
//! \param nProxyType : proxy type (cf: \ref PROXY_TYPE).
//! \param szAddress : proxy server address.
//! \param nPort : proxy server port.
//! \param bRemoteDNS : the DNS address resolution mus be remotely processed.
//! \param nAuthentMethods : authentification methods which are supproted by the client (for SOCKS5 only).
//! \param szLogin : authentification login (for SOCKS5 only).
//! \param szPassword : authentification password (for SOCKS5 only).
//! \return
//! - \ref PROXY_OK when OK,
//! - or a negative error code (refer: \ref PROXY_ERROR).
int PROXY_SetProxy( PROXY_HANDLE s, int nProxyType, const char *szAddress, int nPort, int bRemoteDNS,
					unsigned int nAuthentMethods, const char *szLogin, const char *szPassword );

//! \brief This function sets the parameters of the default proxy. 
//! \param nProxyType : proxy type (refer: \ref PROXY_TYPE).
//! \param szAddress : proxy server address.
//! \param nPort : proxy server port.
//! \param bRemoteDNS : the DNS address resolution mus be remotely processed.
//! \param nAuthentMethods : authentification methods which are supproted by the client (for SOCKS5 only).
//! \param szLogin : authentification login (for SOCKS5 only).
//! \param szPassword : authentification password (for SOCKS5 only).
//! \return
//! - \ref PROXY_OK when OK,
//! - or a negative error code (refer: \ref PROXY_ERROR).
int PROXY_SetDefaultProxy( int nProxyType, const char *szAddress, int nPort, int bRemoteDNS,
						   unsigned int nAuthentMethods, const char *szLogin, const char *szPassword );


//! \brief Callback function to define to implement a private authentication method (for SOCKS5 only).
typedef int (*PROXY_METHOD_CALLBACK)( int socket, const char *szLogin, const char *szPassword, void *userData );

//! \brief This function adds a provate authentication method (for SOCKS5 only).
//! \param nMethod : private method to defined.
//! \param callBack : callback function managing the authentication method.
//! \param userData : user data
int PROXY_AddPrivateAuthentication( unsigned int nMethod, PROXY_METHOD_CALLBACK callBack, void *userData );

//! \brief This function connects a remote server through the proxy server.
//! \param s : connection handle.
//! \param szDestAddress : remote server address.
//! \param nDestPort : remote server port.
//! \param pRFU : reserved for future use (must be set to NULL)
//! \return
//! - \ref PROXY_OK when OK,
//! - or a negative error code (refer: \ref PROXY_ERROR).
int PROXY_Connect( PROXY_HANDLE s, const char *szDestAddress, int nDestPort, void *pRFU );


//! \brief This function reads data from the remote server through the proxy server.
//! \param s : connection handle.
//! \param buf : buffer where the data are saved.
//! \param num : number of bytes to read.
//! \param timeout : timeout 1/100 second
//! \return
//! - the number of read bytes,
//! - or a negative error code (refer: \ref PROXY_ERROR).
int PROXY_Read( PROXY_HANDLE s, void * buf, int num, int timeout);

//! \brief This function send data to the remote server through the proxy server.
//! \param s : connection handle.
//! \param buf : buffer containing the data.
//! \param num : number of bytes to send.
//! \param timeout : timeout 1/100 second
//! \return
//! - the number of sent bytes,
//! - or a negative error code (refer: \ref PROXY_ERROR).
int PROXY_Write( PROXY_HANDLE s, const void * buf, int num, int timeout);

//! \brief This function disconnects the current connection to the proxy server.
//! \param s : connection handle.
//! \return
//! - \ref PROXY_OK when OK,
//! - or a negative error code (refer: \ref PROXY_ERROR).
int PROXY_Disconnect( PROXY_HANDLE s );

//! @}


//! \defgroup PROXY_SAMPLE	Proxy management.
//! \ingroup TCPIP_SAMPLES
//! The sample code below shows how to perform a connection to a WEB server through
//! a SOCKS5 proxy server.
//! It also shows how to add a private authentication method.
//! \include PROXY__Sample_01.c
//! \example PROXY__Sample_01.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

#ifdef __cplusplus
}
#endif

#endif // __PROYY_H__
