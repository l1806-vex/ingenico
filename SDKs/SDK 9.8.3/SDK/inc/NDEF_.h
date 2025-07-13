/**
 * \file NDEF_.h
 * \brief Defines the interface of the NDEF component.
 *
 *
 * \author	Ingenico France
 * \author	Copyright (c) 2011 Ingenico France, 1 rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico France has intellectual property rights relating to the technology embodied\n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico France.
 **/

#ifndef __NDEF_H__
#define __NDEF_H__

#ifdef __cplusplus
extern "C"
{
#endif

//! \addtogroup NDEF_GROUP NDEF library
//! \ingroup KSFAM_LIBRARIES_GROUP
//! @{
//! NDEF (NFC Data Exchange Format) is a data format specified by the NFC Forum.
//! NDEF is a lightweight, binary message format that can be used to encapsulate one or 
//! more application-defined payloads of arbitrary type and size into a single message 
//! construct. Each payload is described by a type, a length, and an optional identifier.
//!
//! <b>The NDEF library is a DLL (reference 844378xxyy) and must be loaded in the
//! terminal to operate properly. Otherwise, any call to the DLL will fail with the exit
//! code 0xAD5ACAFE or 0xAD5AFADE, and a line will be added to the reset ticket of the
//! terminal. </b>
//!
//! @}

//! \addtogroup NDEF_ERROR NDEF Error Codes
//! The NDEF library returns the error codes described below.
//! \ingroup NDEF_GROUP
//! @{

#define NDEF_OK                             (    0) //!< Operation successful.
#define NDEF_ERROR_INTERNAL_RESOURCE        (-3000) //!< Internal allocation failed.
#define NDEF_ERROR_INVALID_PARAMETER        (-3001) //!< Incorrect input parameter.
#define NDEF_ERROR_INVALID_HANDLE           (-3002) //!< Incorrect handle.
#define NDEF_ERROR_BUFFER_TOO_SMALL         (-3003) //!< The buffer given is too small to compute the operation.
#define NDEF_ERROR_INVALID_RECORD_TYPE      (-3004) //!< The type of the record is not correct.

//! @}

//! \addtogroup NDEF_RECORD NDEF Record Interface
//! A NDEF record is contained inside a NDEF message.
//! Every NDEF record is described by a type, a length, and an optional identifier.
//! Specific records are defined by the NFC forum for common data types such as text or URI (see \ref T_NDEF_RECORD_TYPE).
//! \ingroup NDEF_GROUP
//! @{

#ifndef __NDEF_RECORD_HANDLE_DEFINED__
//! \cond
#define __NDEF_RECORD_HANDLE_DEFINED__
//! \endcond

//! \brief NDEF record handle.
typedef struct T_NDEF_RECORD_CONTEXT* NDEF_RECORD_HANDLE;

#endif //__NDEF_RECORD_HANDLE_DEFINED__

//! Types of NDEF record.
typedef enum
{
	NDEF_RAW_RECORD,       //!< Raw record.
	NDEF_TEXT_RECORD,      //!< Text record.
	NDEF_URI_RECORD,       //!< URI record.
	NDEF_MEDIA_TYPE_RECORD //!< Media type record.
}T_NDEF_RECORD_TYPE;

//! TNF values for NDEF records.
typedef enum
{
	TNF_EMPTY          = 0x00, //!< Empty.
	TNF_NFC_WELL_KNOWN = 0x01, //!< NFC Forum well-known type.
	TNF_MEDIA_TYPE     = 0x02, //!< Media-type as defined in RFC 2046.
	TNF_ABSOLUTE_URI   = 0x03, //!< Absolute URI as defined in RFC 3986.
	TNF_NFC_EXTERNAL   = 0x04, //!< NFC Forum external type.
	TNF_UNKNOWN        = 0x05, //!< Unknown.
	TNF_UNCHANGED      = 0x06, //!< Unchanged (chunked records only).
	TNF_RESERVED       = 0x07  //!< Reserved.
}T_NDEF_TNF;

//! Encoding for NDEF text records.
typedef enum
{
	TEXT_ENCODING_UTF8,  //!< NDEF text record in UTF8.
	TEXT_ENCODING_UTF16  //!< NDEF text record in UTF16.
}T_NDEF_TEXT_ENCODING;

//! URI codes for NDEF URI records.
typedef enum
{
	URI_ID_CODE_NONE                    = 0x00, //!< No abbreviation.
	URI_ID_CODE_HTTP_WWW                = 0x01, //!< Abbreviation for 'http://www.'.
	URI_ID_CODE_HTTPS_WWW               = 0x02, //!< Abbreviation for 'https://www.'.
	URI_ID_CODE_HTTP                    = 0x03, //!< Abbreviation for 'http://'.
	URI_ID_CODE_HTTPS                   = 0x04, //!< Abbreviation for 'https://'.
	URI_ID_CODE_TEL                     = 0x05, //!< Abbreviation for 'tel:'.
	URI_ID_CODE_MAILTO                  = 0x06, //!< Abbreviation for 'mailto:'.
	URI_ID_CODE_FTP_ANONYMOUS_ANONYMOUS = 0x07, //!< Abbreviation for 'ftp://anonymous:anonymous@'.
	URI_ID_CODE_FTP_FTP                 = 0x08, //!< Abbreviation for 'ftp://ftp.'.
	URI_ID_CODE_FTPS                    = 0x09, //!< Abbreviation for 'ftps://'.
	URI_ID_CODE_SFTP                    = 0x0A, //!< Abbreviation for 'sftp://'.
	URI_ID_CODE_SMB                     = 0x0B, //!< Abbreviation for 'smb://'.
	URI_ID_CODE_NFS                     = 0x0C, //!< Abbreviation for 'nfs://'.
	URI_ID_CODE_FTP                     = 0x0D, //!< Abbreviation for 'ftp://'.
	URI_ID_CODE_DAV                     = 0x0E, //!< Abbreviation for 'dav://'.
	URI_ID_CODE_NEWS                    = 0x0F, //!< Abbreviation for 'news:'.
	URI_ID_CODE_TELNET                  = 0x10, //!< Abbreviation for 'telnet://'.
	URI_ID_CODE_IMAP                    = 0x11, //!< Abbreviation for 'imap:'.
	URI_ID_CODE_RTSP                    = 0x12, //!< Abbreviation for 'rtsp://'.
	URI_ID_CODE_URN                     = 0x13, //!< Abbreviation for 'urn:'.
	URI_ID_CODE_POP                     = 0x14, //!< Abbreviation for 'pop:'.
	URI_ID_CODE_SIP                     = 0x15, //!< Abbreviation for 'sip:'.
	URI_ID_CODE_SIPS                    = 0x16, //!< Abbreviation for 'sips:'.
	URI_ID_CODE_TFTP                    = 0x17, //!< Abbreviation for 'tftp:'.
	URI_ID_CODE_BTSPP                   = 0x18, //!< Abbreviation for 'btspp://'.
	URI_ID_CODE_BTL2CAP                 = 0x19, //!< Abbreviation for 'btl2cap://'.
	URI_ID_CODE_BTGOEP                  = 0x1A, //!< Abbreviation for 'btgoep://'.
	URI_ID_CODE_TCPOBEX                 = 0x1B, //!< Abbreviation for 'tcpobex://'.
	URI_ID_CODE_IRDAOBEX                = 0x1C, //!< Abbreviation for 'irdaobex://'.
	URI_ID_CODE_FILE                    = 0x1D, //!< Abbreviation for 'file://'.
	URI_ID_CODE_URN_EPC_ID              = 0x1E, //!< Abbreviation for 'urn:epc:id:'.
	URI_ID_CODE_URN_EPC_TAG             = 0x1F, //!< Abbreviation for 'urn:epc:tag:'.
	URI_ID_CODE_URN_EPC_PAT             = 0x20, //!< Abbreviation for 'urn:epc:pat:'.
	URI_ID_CODE_URN_EPC_RAW             = 0x21, //!< Abbreviation for 'urn:epc:raw:'.
	URI_ID_CODE_URN_EPC                 = 0x22, //!< Abbreviation for 'urn:epc:'.
	URI_ID_CODE_URN_NFC                 = 0x23  //!< Abbreviation for 'urn:nfc:'.
}T_NDEF_URI_ID_CODE;

//! \brief Get a NDEF record type.
//! \param[in]  hRecord NDEF record handle.
//! \param[out] pType   Pointer to store the type of the record.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Record_GetType( NDEF_RECORD_HANDLE hRecord, T_NDEF_RECORD_TYPE* pType );

//! \brief Get the TNF (Type Name Format) of a NDEF record.
//! \param[in]  hRecord NDEF record handle.
//! \param[out] pTnf    Pointer to store the TNF value of the record.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Record_GetTnf( NDEF_RECORD_HANDLE hRecord, T_NDEF_TNF* pTnf );

//! Type of the NDEF data fields.
typedef enum
{
	NDEF_TYPE_DATA,
	NDEF_ID_DATA,
	NDEF_PAYLOAD_DATA
}T_NDEF_DATA_TYPE;

//! \brief Get data from a NDEF record.
//! \param[in]  hRecord NDEF record handle.
//! \param[in]  eType   Type of the data to get (see \ref T_NDEF_DATA_TYPE for possible values).
//! \param[out] pBuffer Data buffer of the record.
//! \param[out] pLength Length of the previous buffer.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Record_GetData( NDEF_RECORD_HANDLE hRecord, T_NDEF_DATA_TYPE eType, const unsigned char** pBuffer, unsigned int* pLength );

//! \brief Extract data from a NDEF text record.
//! \param[in]  hRecord   NDEF record handle.
//! \param[out] pText     Pointer to get the text of the record (zero-terminated string). Can be NULL.
//! \param[out] pLanguage Pointer to get the language of the record (zero-terminated string). Can be NULL.
//! \param[out] pEncoding Pointer to get the text encoding of the record. Can be NULL.
//! \note This function will successfully return only with records of type \ref NDEF_TEXT_RECORD.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Record_ParseAsText( NDEF_RECORD_HANDLE hRecord, const char** pText, const char** pLanguage, T_NDEF_TEXT_ENCODING* pEncoding );

//! \brief Extract data from a NDEF URI record.
//! \param[in]  hRecord   NDEF record handle.
//! \param[out] pUri      Pointer to get the URI of the record (zero-terminated string). Can be NULL.
//! \param[out] pFullUri  Pointer to get the full URI of the record, with the URI ID code expanded (zero-terminated string). Can be NULL.
//! \param[out] pId       Pointer to get the URI ID code of the record. Can be NULL.
//! \note This function will successfully return only with records of type \ref NDEF_URI_RECORD.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Record_ParseAsUri( NDEF_RECORD_HANDLE hRecord, const char** pUri, const char** pFullUri, T_NDEF_URI_ID_CODE* pId );

//! \brief Extract data from a NDEF media type record.
//! \param[in]  hRecord   NDEF record handle.
//! \param[out] pMimeType Pointer to get the MIME type of the record (zero-terminated string). Can be NULL.
//! \param[out] pData     Pointer to get the data of the record. Can be NULL.
//! \param[out] pDataSize Pointer to get the size of the data. Can be NULL.
//! \note This function will successfully return only with records of type \ref NDEF_MEDIA_TYPE_RECORD.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Record_ParseAsMediaType( NDEF_RECORD_HANDLE hRecord, const char** pMimeType, const unsigned char** pData, unsigned int* pDataSize );

//! @}

//! \addtogroup NDEF_MESSAGE NDEF Message Interface
//! \ingroup NDEF_GROUP
//! A NDEF message is a set of one or more NDEF records.
//! @{

#ifndef __NDEF_MESSAGE_HANDLE_DEFINED__
//! \cond
#define __NDEF_MESSAGE_HANDLE_DEFINED__
//! \endcond

//! \brief NDEF message handle.
typedef struct T_NDEF_MESSAGE_CONTEXT* NDEF_MESSAGE_HANDLE;

#endif //__NDEF_MESSAGE_HANDLE_DEFINED__

//! \brief Create a NDEF message.
//! \param[out] pMessage Contains the handle on the message.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_Create( NDEF_MESSAGE_HANDLE* pMessage );

//! \brief Destroy a NDEF message.
//! \param[in] hMessage NDEF message handle.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_Destroy( NDEF_MESSAGE_HANDLE hMessage );

//! \brief Duplicate a NDEF message.
//! \param[in]  hMessage NDEF message handle to copy.
//! \param[out] pCopy    NDEF message handle to store the copy.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_Duplicate( NDEF_MESSAGE_HANDLE hMessage, NDEF_MESSAGE_HANDLE* pCopy );

//! \brief Add a raw record to a NDEF message.
//! \param[in] hMessage       NDEF message handle.
//! \param[in] eTnf           Type Name Format of the message.
//! \param[in] pucType        NDEF type buffer.
//! \param[in] nTypeLength    Length of the type buffer.
//! \param[in] pucId          NDEF type buffer.
//! \param[in] nIdLength      Length of the type buffer.
//! \param[in] pucPayload     NDEF type buffer.
//! \param[in] nPayloadLength Length of the type buffer.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_AppendRawRecord( NDEF_MESSAGE_HANDLE  hMessage,   T_NDEF_TNF   eTnf,
                                  const unsigned char* pucType,    unsigned int nTypeLength,
                                  const unsigned char* pucId,      unsigned int nIdLength,
                                  const unsigned char* pucPayload, unsigned int nPayloadLength );

//! \brief Add a text record to a NDEF message.
//! \param[in] hMessage       NDEF message handle.
//! \param[in] szText         Content of the record. Zero-terminated string.
//! \param[in] szLanguageCode Code of the language of the record (such as "fr", "en"...). Zero-terminated string.
//! \param[in] eEncoding      Encoding type (see the T_NDEF_TEXT_ENCODING definition for the possible values).
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_AppendTextRecord( NDEF_MESSAGE_HANDLE hMessage, const char* szText, const char* szLanguageCode, T_NDEF_TEXT_ENCODING eEncoding );

//! \brief Add an URI (Uniform Resource Identifier) record to a NDEF message.
//! \param[in] hMessage NDEF message handle.
//! \param[in] szUri    Content of the record. Zero-terminated string.
//! \param[in] eId      URI ID code to use (to shorten the URI payload length, see the \ref T_NDEF_URI_ID_CODE definition for the possible values).
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_AppendUriRecord( NDEF_MESSAGE_HANDLE hMessage, const char* szUri, T_NDEF_URI_ID_CODE eId );

//! \brief Add a media type record to a NDEF message.
//! \param[in] hMessage   NDEF message handle.
//! \param[in] szMimeType MIME type of the record. Zero-terminated string.
//! \param[in] pucData    Buffer containing the data of the record.
//! \param[in] nDataSize  Length of the buffer.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_AppendMediaTypeRecord( NDEF_MESSAGE_HANDLE hMessage, const char* szMimeType, const unsigned char* pucData, unsigned int nDataSize );

//! \brief Get the size needed to serialize a NDEF message.
//! \param[in]  hMessage NDEF message handle.
//! \param[out] pSize    Pointer to store the size.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_GetSerializationSize( NDEF_MESSAGE_HANDLE hMessage, unsigned int* pSize );

//! \brief Serialize a NDEF message.
//! \param[in]  hMessage    NDEF message handle.
//! \param[out] pucBuffer   Buffer to store the serialized data.
//! \param[in]  nBufferSize Size of the previous buffer.
//! \param[out] pUsed       Pointer to store the number of bytes used in the buffer.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_Serialize( NDEF_MESSAGE_HANDLE hMessage, unsigned char* pucBuffer, unsigned int nBufferSize, unsigned int* pUsed );

//! \brief Parse a buffer containing a NDEF message.
//! \param[out] pMessage       Pointer to store the NDEF message handle.
//! \param[in]  pucMessage     Buffer containing a serialized NDEF message.
//! \param[in]  nMessageLength Size of the previous buffer.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_Parse( NDEF_MESSAGE_HANDLE* pMessage, const unsigned char* pucMessage, unsigned int nMessageLength );

//! \brief Get the number of NDEF records contained in a NDEF message.
//! \param[in]  hMessage NDEF message handle.
//! \param[out] pCount   Pointer to store the number of records.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_GetRecordCount( NDEF_MESSAGE_HANDLE hMessage, unsigned int* pCount );

//! \brief Get a NDEF record contained in a NDEF message.
//! \param[in]  hMessage NDEF message handle.
//! \param[out] pRecord  Pointer to store the NDEF record handle.
//! \param[in]  nIndex   Index of the record. Use 0 to get the first record.
//! \return \ref NDEF_OK in case of success, a negative error code otherwise (see \ref NDEF_ERROR for details).
int NDEF_Message_GetRecord( NDEF_MESSAGE_HANDLE hMessage, NDEF_RECORD_HANDLE* pRecord, unsigned int nIndex );

//! @}

//! \example NDEF_Sample_01.c
//! \example NDEF_Sample_02.c
//! \example NDEF_Sample_03.c
//! \example NDEF_Sample_04.c
//! \example NDEF_Sample_05.c

#ifdef __cplusplus
}
#endif

#endif //__NDEF_H__

