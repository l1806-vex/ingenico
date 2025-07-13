#ifndef __SMTP__H__
#define __SMTP__H__

#ifdef __cplusplus
extern "C"
{
#endif

//! \file        SMTP_.h
//! \brief This module contains all the SMTP definitions.
//
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
//

//! \addtogroup TCPIP_SMTP
//! \par Introduction
//!
//! The TELIUM SDK TCP/IP package provides services for email management. 
//! It supports the SMTP protocol to send emails to a server. 
//!
//! The SMTP protocol is described in the RFC 2821.
//!
//! <TABLE border="3" cellspacing="0" bordercolor="black">
//! <TR><TD></TD></TR>
//! <TR><TD><b>Developers shall read the document [ICO-PE-045-GU-EN_PackIP_SecurityGuidance_UserGuide.pdf]
//! which describes best practises for implementing IP enabled applications, according to
//! the requirements of the POS Terminal Security Program (PTS) and of the PCI PTS v3 "Open Protocols" module.</b></TD></TR>
//! <TR><TD></TD></TR>
//! </TABLE>
//!
//! Please refer \ref MAIL_SAMPLE (a sample showing how to send emails to a SMTP server). 
//!
//! @{

//! \brief Definition of SMTP handle.
typedef int SMTP_HANDLE;

//! \cond __EXCLUDE__
#define __SMTP_RELEASE1			1
//! \endcond

////// Errors definition //////////////////////////////////////////////////

//! \defgroup SMTP_ERROR_CODES Error codes
//! \brief Error codes returned by SMTP API functions.
//! @{

#define SMTP_ERROR_ADDRESS				-5000    //!< Invalid address.
#define SMTP_ERROR_SOCKET				-5001    //!< Socket creation error.
#define SMTP_ERROR_CONNECT				-5002    //!< Connection error (host not found).
#define SMTP_ERROR_EHLO					-5003    //!< Error when exchanging EHLO message.
#define SMTP_ERROR_AUTHORIZATION		-5004    //!< Authentication error.
#define SMTP_ERROR_MAILSOURCE			-5010    //!< Mail source error.
#define SMTP_ERROR_MAILDESTINATION		-5011    //!< Mail destination error.
#define SMTP_ERROR_MAILDATA				-5012    //!< Mail data error.
#define SMTP_ERROR_MSGBUFFER_OVERFLOW	-5013    //!< Message buffer overflow.

//! @}

// Connection management


//! \brief This function connects the terminal to the SMTP server. This
//! connection can request an identification, or be anonymous (no user, nor password).
//! \param szSMTPServer : TCP/IP address of the SMTP server.
//! \param szPassword : Password associated to the user name. Is NULL when the user name is NULL.
//! \param nPort : SMTP port (usually 25).
//! \param szLogin : User name. May be set to NULL (or ''), if no authentication required by the remote SMTP server.
//! \param szSMTPClient : Network name of the terminal.
//! \return
//! - The connection handle (>=0) if OK.
//! - A negative error code otherwise.
SMTP_HANDLE SMTP_Connect(	const char *szSMTPServer,
							int			nPort,
							const char *szLogin,
							const char *szPassword,
							const char *szSMTPClient );

// Disconnection management 


//! \brief This function disconnects the terminal from the SMTP server.
//! \param handle : Handle on the connection to close.
//! \return None.
void SMTP_Disconnect( SMTP_HANDLE handle );

// Message sending management

//! \brief Send an US-ASCII text message to the lists of specified recipients. This 
//! message has an header formatted according to the standard RFC 822, as long as this header is not greater than 1024 bytes. Otherwise no header is added.
//! \param handle : Handle on an existing connection.
//! \param szMessage : Message to send. Please note that the global raw message's 
//! size (header and content) is limited to 8 kilobytes.
//! \param nMessageSize : Size, in bytes, of the message to send.
//! \param szSubject : Subject of the message. May be NULL.
//! \param szFrom : E-mail address of the sender. This address cannot be NULL. Use a valid address to be able to be informed about distribution failures.
//! \param szTo : List of recipients. This list can be NULL. In case of multiple 
//! recipients, put a comma (,) between each address.
//! \param szCC : List of recipients put in copy. This list can be NULL. In case of 
//! multiple recipients, put a comma (,) between each address.
//! \param szBCC : List of recipients put in blind copy. This list can be NULL. In
//!  case of multiple recipients, put a comma (,) between each address.
//! \param pAttachedFilesList : Array of attachement files' names. These files must be stored 
//! in the FFMS before being sent. The complete path to these files (directory and file name) must be put in this array. This list can be 
//! NULL (no attached files). In any case, the last item of this list must be NULL.
//! \return 
//! - Number of attachement files sent (0 if none) if OK.
//! - A negative error code otherwise.
//! \note 
//! At least of one list of recipients (To, CC, or BCC) must not be NULL.
int SMTP_Send(				SMTP_HANDLE handle,
							const char *szMessage,
							int			nMessageSize,
							const char *szSubject,
							const char *szFrom,
							const char *szTo,
							const char *szCC,
							const char *szBCC,
							const char *pAttachedFilesList[] );

//! \brief This function can be used to send an unique message. It automatically
//! performs the sequence:
//! - SMTP_Connect(...),
//! - SMTP_Send(...)
//! - SMTP_Disconnect(...)
//! \param szSMTPServer : TCP/IP address of the SMTP server.
//! \param nPort : SMTP server port (usually 25).
//! \param szLogin : User name. May be set to NULL (or ''), if no authentication required by the remote SMTP server.
//! \param szPassword : Password associated to the user name. Is NULL when the user name is NULL.
//! \param szSMTPClient : Network name of the terminal.
//! \param szMessage : Message to send. Please note that the global raw message's 
//! size (header and content) is limited to 8 kilobytes.
//! \param nMessageSize : Size, in bytes, of the message to send.
//! \param szSubject : Subject of the message. May be NULL.
//! \param szFrom : E-mail address of the sender. This address cannot be NULL. Use a valid address to be able to be informed about distribution failures,
//! \param szTo : List of recipients. This list can be NULL. In case of multiple recipients, put a comma (,) between each address.
//! \param szCC : List of recipients put in copy. This list can be NULL. In case of multiple recipients, put a comma (,) between each address.
//! \param szBCC : List of recipients put in blind copy. This list can be NULL. In 
//! case of multiple recipients, put a comma (,) between each address.
//! \param pAttachedFilesList : Array of attachement files' names. These files must be stored 
//! in the FFMS before being sent. The complete path to these files (directory and file name) must be put in this array. This list can be NULL (no attached files). In any case, the last item of this list must be NULL.
//! \return 
//! - Number of attachement files sent (0 if none)
//! - or an negative error code.
//! \note 
//! At least of one list of recipients (To, CC, or BCC) must not be NULL.
int SMTP_SendUniqueMessage(	const char *szSMTPServer,
							int			nPort,
							const char *szLogin,
							const char *szPassword,
							const char *szSMTPClient,
							const char *szMessage,
							int			nMessageSize,
							const char *szSubject,
							const char *szFrom,
							const char *szTo,
							const char *szCC,
							const char *szBCC,
							const char *pAttachedFilesList[] );

//! @}

#ifdef __cplusplus
}
#endif


#endif // __SMTP__H__
