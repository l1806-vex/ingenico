/* ========================================================================	*/
/* Project       : -                                                        */
/* Module        : ISO8583                                                  */
/* Creation Date : 08/12/2004                                               */
/* Author        : M. GATESOUPE                                             */
/* Description   : This module contains the interface with                  */
/*                 the ISO8583 communication component                      */
/* ========================================================================	*/
/* SAGEM Monetel                                                            */
/* 1 rue Claude Chappe - BP 346                                             */
/* 07503 Guilherand-Granges                                                 */
/* ========================================================================	*/
/* REVISION HISTORY                                                         */
/* ========================================================================	*/
/* Date          :                                                          */
/* Author        :                                                          */
/* Description   :                                                          */
/* ========================================================================	*/

#ifndef _ISO8583_H_
#define _ISO8583_H_

#ifndef __LL_HANDLE__
#define __LL_HANDLE__

typedef void* LL_HANDLE;

#endif

#ifndef __TLV_TREE_NODE__
#define __TLV_TREE_NODE__

typedef int * TLV_TREE_NODE;

#endif

#define TAG_ISO8583_CONFIG		                0xBF9501
#define TAG_ISO8583_MESSAGE                     0xBF9502
#define TAG_ISO8583_MTI                         0x9F8813  // Used to be TAG_COMM_MESSAGE_TYPE in servcomm.h

// ISO8583 fields default tags
#define	TAG_ISO8583_FIELDS						0x9F8A00
#define	TAG_ISO8583_DEFAULT_FIELD(nField)		(0x9F8A00 + nField)

// ISO8583 specific tags
#define	TAG_ISO8583_MESSAGE_HEADER				0x9F8A81
#define	TAG_ISO8583_MESSAGE_TRAILER				0x9F8A82

#define	TAG_ISO8583_93_MSG_REASON_CODE			0x9F8A83
#define	TAG_ISO8583_93_ACTION_CODE				0x9F8A84

#define	TAG_ISO8583_APPLI_STATUS_CODE			0x9F8A85

// Configuration tags
#define TAG_ISO8583_T_TIMEOUT					1
#define TAG_ISO8583_L_TIMEOUT					4
#define ISO8583_DEFAULT_TIMEOUT					3000

#define TAG_ISO8583_T_RESEND					2
#define TAG_ISO8583_L_RESEND					1
#define ISO8583_DEFAULT_MAX_RESEND				3

#define TAG_ISO8583_T_DESCRIPTOR_ID				3
#define TAG_ISO8583_L_DESCRIPTOR_ID				1

#define TAG_ISO8583_T_FILENAME					4
#define TAG_ISO8583_L_MAX_FILENAME				16

#define TAG_ISO8583_T_PATH						5
#define TAG_ISO8583_L_MAX_PATH					16

#define TAG_ISO8583_T_FRAME_SIZE_TYPE				6
#define TAG_ISO8583_L_FRAME_SIZE_TYPE				1
#define TAG_ISO8583_V_FRAME_SIZE_TYPE_NONE			0
#define TAG_ISO8583_V_FRAME_SIZE_TYPE_LSBF			1
#define TAG_ISO8583_V_FRAME_SIZE_TYPE_MSBF			2
#define TAG_ISO8583_V_FRAME_SIZE_TYPE_LSBF_HEADER	3
#define TAG_ISO8583_V_FRAME_SIZE_TYPE_MSBF_HEADER	4

#define TAG_ISO8583_T_FRAME_SIZE_LENGTH			7
#define TAG_ISO8583_L_FRAME_SIZE_LENGTH			1
#define TAG_ISO8583_V_FRAME_SIZE_LENGTH_DEFAULT	4

#define TAG_ISO8583_T_TIMEOUT_2					8
#define TAG_ISO8583_L_TIMEOUT_2					4
#define ISO8583_DEFAULT_TIMEOUT_2				200

#define TAG_ISO8583_T_HOOK_APPLI_TYPE			12
#define TAG_ISO8583_L_HOOK_APPLI_TYPE			2

#define TAG_ISO8583_T_HOOK_SEND_SERVICE_ID		13
#define TAG_ISO8583_L_HOOK_SEND_SERVICE_ID		2

#define TAG_ISO8583_T_HOOK_RECEIVE_SERVICE_ID	14
#define TAG_ISO8583_L_HOOK_RECEIVE_SERVICE_ID	2

// Protocol types
#define COMM_PROTOCOL_TYPE_ISO8583_87			10
#define COMM_PROTOCOL_TYPE_ISO8583_93			11

// Maximum frame size allowed in hook functions
#define ISO8583_HOOK_MAX_FRAME_SIZE				(4096)

// Kept for compatibility
#define TAG_ISO8583_T_RAW_MODE                  20
#define TAG_ISO8583_L_RAW_MODE                  1
#define TAG_ISO8583_V_RAW_MODE_NOT_USED         0
#define TAG_ISO8583_V_RAW_MODE_USED             1

#define TAG_ISO8583_T_GMS_MODE                  21
#define TAG_ISO8583_L_GMS_MODE                  1
#define TAG_ISO8583_V_GMS_MODE_NOT_USED         0
#define TAG_ISO8583_V_GMS_MODE_USED             1


// Errors
//
#define ISO_ERROR_OK                     ( 0 )
#define ISO_ERRORS                       ( -20000 )
#define ISO_ERROR_INVALID_PARAMETER      ( ISO_ERRORS - 1 )
#define ISO_ERROR_MEMORY                 ( ISO_ERRORS - 2 )
#define ISO_ERROR_CONFIGURATION          ( ISO_ERRORS - 3 )
#define ISO_ERROR_CONFIGURATION_FILE     ( ISO_ERRORS - 4 )
#define ISO_ERROR_INVALID_HANDLE         ( ISO_ERRORS - 5 )
#define ISO_ERROR_BAD_PARAMETER          ( ISO_ERRORS - 6 )
#define ISO_ERROR_TIMEOUT                ( ISO_ERRORS - 7 )
#define ISO_ERROR_INVALID_RESPONSE       ( ISO_ERRORS - 8 )
#define ISO_ERROR_COMMUNICATION_PROBLEM  ( ISO_ERRORS - 9 )
#define ISO_ERROR_SERVICE_CALL           ( ISO_ERRORS - 10 )
#define ISO_ERROR_STILL_CONNECTED        ( ISO_ERRORS - 11 )
#define ISO_ERROR_UNKNOWN                ( ISO_ERRORS - 12 )
#define ISO_ERROR_NO_LINKLAYER_HANDLE    ( ISO_ERRORS - 13 )
#define ISO_ERROR_LINKLAYER_NOT_LOADED   ( ISO_ERRORS - 14 )
#define ISO_ERROR_LINKLAYER_TOO_OLD      ( ISO_ERRORS - 15 )
#define ISO_ERROR_MISSING_FIELD          ( ISO_ERRORS - 1000 )

#define ISO_GET_MISSING_FIELD(ERROR_NB)  ( ERROR_NB - ISO_ERROR_MISSING_FIELD )

//
// API functions
//
typedef void* ISO8583_HANDLE;

int Iso8583_Configure         ( ISO8583_HANDLE* pSession, const TLV_TREE_NODE hIso8583Parameters, const TLV_TREE_NODE hLinkLayerParameters );
int Iso8583_Connect           ( ISO8583_HANDLE hIsoSession );
int Iso8583_Disconnect        ( ISO8583_HANDLE hIsoSession );
int Iso8583_SendAndReceive    ( ISO8583_HANDLE hIsoSession, const TLV_TREE_NODE hMessageToSend, TLV_TREE_NODE* phReceivedMessage );
int Iso8583_Send              ( ISO8583_HANDLE hIsoSession, const TLV_TREE_NODE hMessageToSend );
int Iso8583_EncodeMessage     ( ISO8583_HANDLE hIsoSession, const TLV_TREE_NODE hMessageToEncode, unsigned char* pucBuffer, unsigned int nBufferSize, unsigned int *pnFrameSize );
int Iso8583_DecodeMessage     ( ISO8583_HANDLE hIsoSession, const unsigned char* pucBuffer, unsigned int nBufferSize, unsigned int nHeaderLength, TLV_TREE_NODE* phDecodedMessage );
int Iso8583_GetLinkLayerHandle( ISO8583_HANDLE hIsoSession, LL_HANDLE* phLinkLayer );
int Iso8583_SetLinkLayerHandle( ISO8583_HANDLE hIsoSession, LL_HANDLE hLinkLayer, int bDestroy );

// New services - Version 0303 and above
int Iso8583_AbortConnect( ISO8583_HANDLE hIsoSession );
int Iso8583_GetNameAndVersion( char* szName, unsigned int nNameLength, char* szVersion, unsigned int nVersionLength );

//
// API MAC management
//
typedef void* ISO8583_MAC_HANDLE;

#define ISO8583_MAC_OK            (0)
#define ISO8583_MAC_KO            (-1)

#define ISO8583_FRAME_STATUS_OK   (1)
#define ISO8583_FRAME_STATUS_KO   (0)

void* Iso8583_MacGetFrame    ( ISO8583_MAC_HANDLE hIso8583Mac );
int   Iso8583_MacGetFrameSize( ISO8583_MAC_HANDLE hIso8583Mac );
int   Iso8583_MacSetFrameSize( ISO8583_MAC_HANDLE hIso8583Mac, int nNewFrameSize );
int   Iso8583_MacSetStatus   ( ISO8583_MAC_HANDLE hIso8583Mac, int nStatus );

#endif // _ISO8583_H_

