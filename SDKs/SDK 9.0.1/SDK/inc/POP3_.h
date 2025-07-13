#ifndef __POP3__H__
#define __POP3__H__

#ifdef __cplusplus
extern "C"
{
#endif

//! \file        POP3_.h
//! \brief This module contains all the POP3 definitions.
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

//! \addtogroup TCPIP_POP3
//! \par Introduction
//!
//! The TELIUM SDK TCP/IP package provides services for email management. 
//! It supports the POP3 protocol (Post Office Protocol Version 3) to get and 
//! to manage messages from a email server. 
//!
//! The POP3 protocol is described in the RFC 1939.
//!
//! <TABLE border="3" cellspacing="0" bordercolor="black">
//! <TR><TD></TD></TR>
//! <TR><TD><b>Developers shall read the document [ICO-PE-045-GU-EN_PackIP_SecurityGuidance_UserGuide.pdf]
//! which describes best practises for implementing IP enabled applications, according to
//! the requirements of the POS Terminal Security Program (PTS) and of the PCI PTS v3 "Open Protocols" module.</b></TD></TR>
//! <TR><TD></TD></TR>
//! </TABLE>
//!
//! Please refer \ref MAIL_SAMPLE (a sample showing how to get emails from a POP3 server). 
//!
//! @{

//! \brief Definition of POP3 handle.
typedef int POP3_HANDLE;

//! \cond __EXCLUDE__
#define __POP3_RELEASE1			1
//! \endcond

#define _POP3_HEADER_LINE_SIZE 128

//! \brief Define a structure wich gives informations about a POP3 message.
typedef struct
{
	char szSubject	[_POP3_HEADER_LINE_SIZE];			//!< Subject of the message
	char szFrom		[_POP3_HEADER_LINE_SIZE];			//!< Sender of the message
	char szDate		[_POP3_HEADER_LINE_SIZE];			//!< Date of the message
	char szTo       [_POP3_HEADER_LINE_SIZE];			//!< Recipicient(s)
	char szCC		[_POP3_HEADER_LINE_SIZE];			//!< Recipicient(s) in copy
	char szUIDL		[_POP3_HEADER_LINE_SIZE];			//!< Unique identifier for the message
	int	 nSize;											//!< Size of the message (in bytes)
} POP3_INFO;

////// Errors definition //////////////////////////////////////////////////

//! \defgroup POP3_ERROR_CODES Error codes
//! \brief Error codes returned by POP3 API functions.
//! @{

#define POP3_ERROR_ADDRESS				-6000    //!< Invalid address.
#define POP3_ERROR_SOCKET				-6001    //!< Socket creation error.
#define POP3_ERROR_CONNECT				-6002    //!< Connection error (host not found).
#define POP3_ERROR_AUTHORIZATION		-6003    //!< Authentication error.
#define POP3_ERROR_PARAMETER			-6010    //!< Invalid parameter.
#define POP3_ERROR_DATA_OVERFLOW		-6011    //!< Data overflow.
#define POP3_ERROR_DATA					-6012    //!< Data error.
#define POP3_ERROR_MESSAGE				-6013    //!< Message error.
#define POP3_ERROR_RESET				-6014    //!< Reset.
#define POP3_ERROR_GET_MESSAGE_NB		-6015    //!< Error when getting message count.

//! @}


//// Connect management

//! \brief This function connects the terminal to the POP3 server. This connection
//! requires an authentication.
//! \param szPop3Server : TCP/IP address of the POP3 server.
//! \param nPort : POP3 server port (usually 110).
//! \param szUsername : User name.
//! \param szPassword : Password associated to the user name.
//! \param bSecuredConnection : Reserved for future use.
//! \return 
//! The connection handle (>=0) if OK.
//! Anegative error code otherwise.
POP3_HANDLE POP3_Connect(	const char *szPop3Server,
							int			nPort,
							const char *szUsername,
							const char *szPassword,
							char		bSecuredConnection);

//// Disconnect

//! \brief This function disconnects the terminal from the SMTP server.
//! \param handle : Handle on the connection to close.
//! \return None.
void POP3_Disconnect(		POP3_HANDLE handle );

//// Number of messages present onto the server

//! \brief This function returns the number of message present on the mail
//! account, and, if required, the total size occupied by the messages.
//! \param handle : Handle on the connection,
//! \param nTotalSize : Pointer to an integer to fill with the global size of the messages 
//! currently into the open mail account. This pointer may be NULL if this value is not needed.
//! \return 
//! The number of messages currently into the mail account. This number
//! includes all the messages (new messages and those already read).
int POP3_GetNbMessages(		POP3_HANDLE	handle,
							int	*		nTotalSize
							);

//// Whole content of the message

//! \brief This function returns the given message, with, the header on the "info"
//! structure, and the body in a separate buffer.
//! \param handle : Handle on the connection,
//! \param nMessageIndex : Number of the message to retrieve from the POP3 server. The index of the first message (oldest one) is 1.
//! \param pPop3Info : A pointer to the structure that will be filled with data extracted from the header, and important message characteristics. 
//! Please note that the buffers (see POP3_INFO description below) containing these data are 128 bytes long. If the content in the message's header is longer than 128 bytes, the data will be truncated to fit with buffer size.
//! \param psBufferBody : Buffer to fill with the body of the message. This parameter can 
//! be NULL, whether only the 'info' structure is requested.
//! \param nBufferSize : Maximum size of the buffer allocated to receive the body of the message.
//! \return 
//! - 0, if OK.
//! - A negative error code otherwise.
//! \note
//! The content of the body is US-ASCII text only. Thus, any mail containing other 
//! elements, like MIME encoding parts, has to be processed by the user.
int POP3_GetMessage(		POP3_HANDLE	handle,
							int			nMessageIndex,
							POP3_INFO *	pPop3Info,
							char *		psBufferBody,
							int			nBufferSize);


//// Delete the message

//! \brief This function deletes a given message.
//! \param handle : Handle on the connection.
//! \param nMessageIndex : Index of the message to delete from the POP3 server. The index of the first message (oldest one) is 1.
//! \return 
//! - 0 if OK.
//! - A negative error code otherwise.
int POP3_DeleteMessage(		POP3_HANDLE handle,
							int			nMessageIndex);

//// Reset the session

//! \brief This function reset the session. It cancels the deletion of the messages
//! performed during the current session.
//! \param handle : Handle on the connection.
//! \return 
//! - 0 if OK.
//! - A negative error code otherwise.
int POP3_Reset(	POP3_HANDLE handle);

//! @}


//! \defgroup MAIL_SAMPLE	Email management.
//! \ingroup TCPIP_SAMPLES
//! The sample code below shows how to send and receive an email using the dedicated interface.
//! Mails are sent using the SMTP protocol and read from a server using the POP3 protocol.
//! \include POP3__Sample_01.c
//! \example POP3__Sample_01.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

#ifdef __cplusplus
}
#endif


#endif
