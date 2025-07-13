/**
 *! \file        BerTlv.h
 * \brief This module contains the definitions and functions necessary to manage the BER-TLV format
 *
 *
 * \author SAGEM MONETEL
 * \author Copyright (c) 2006 Sagem Monetel SA, rue claude Chappe,\n
 *		   07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Sagem Monetel SA has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Sagem Monetel.
 **/

#ifndef __BERTLV_H__INCLUDED__
#define __BERTLV_H__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "AVL_deprecated.h"

#if defined (__GNUC__) || defined(_DEPRECATED_SDK920_AVL_)

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

// Definition of the first byte of a tag
#define BER_TLV_TAG_CLASS_MASK					0xc0	/*!< Mask to retreive the tag class */

#define BER_TLV_TAG_UNIVERSAL_CLASS				0x00	/*!< Universal tag class */

#define BER_TLV_TAG_APPLICATION_CLASS			0x40	/*!< Application tag class */

#define BER_TLV_TAG_CONTEXT_SPECIFIC_CLASS		0x80	/*!< Context specific tag class */

#define BER_TLV_TAG_PRIVATE_CLASS				0xc0	/*!< Private tag class */

#define BER_TLV_TAG_CONSTRUCTED					0x20	/*!< Constructed or primitive tag flag */

#define BER_TLV_TAG_SEE_NEXT_BYTES				0x1f	/*!< "See subsequent bytes" tag flag */

// Definition of the others bytes of a tag
#define BER_TLV_TAG_ANOTHER_BYTE				0x80	/*!< "Another byte follows" tag flag */

// Definition of the first byte of a length
#define BER_TLV_LENGTH_OTHERS_BYTES				0x80	/*!< Flag that indicates that several bytes are used for the length */

#define BER_TLV_LENGTH_NUMBER_OF_BYTES_MASK		0x7f	/*!< Mask to retreive the number of bytes used to encode the length */

//// Types //////////////////////////////////////////////////////

/*! \brief Type of a BER-TLV tag. */
typedef unsigned long BER_TLV_TAG;

/*! \brief Type of a BER-TLV length. */
typedef unsigned long BER_TLV_LENGTH;

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

//// Tag properties

/*! \brief Retreive the class of a BER-TLV tag								
 *	@param[in] Tag Tag to analyse.										
 *	@return The class of the tag.
 **/
int BerTlvGetTagClass(BER_TLV_TAG Tag) AVL_DEPRECATED ;


/*! \brief	Check if the tag belongs to the universal class.								
 *	@param[in] Tag Tag to analyse.										
 *	@return	TRUE if the tag belongs to the universal class, FALSE if not.
 **/
int BerTlvIsTagUniversalClass(BER_TLV_TAG Tag) AVL_DEPRECATED ;


/*! \brief 	Check if the tag belongs to the application class.						
 *	@param[in] Tag Tag to analyse.									
 *	@return TRUE if the tag belongs to the application class, FALSE if not.
 **/
int BerTlvIsTagApplicationClass(BER_TLV_TAG Tag) AVL_DEPRECATED ;


/*! \brief	Check if the tag belongs to the context specific class.							
 *	@param[in] Tag Tag to analyse.	
 *	@return	TRUE if the tag belongs to the context specific class, FALSE if not.
 **/
int BerTlvIsTagContextSpecificClass(BER_TLV_TAG Tag) AVL_DEPRECATED ;


/*! \brief	Check if the tag belongs to the private class.							
 *	@param[in] Tag Tag to analyse.									
 *	@return	TRUE if the tag belongs to the private class, FALSE if not.
 **/
int BerTlvIsTagPrivateClass(BER_TLV_TAG Tag) AVL_DEPRECATED ;


/*! \brief	Check if the tag is a primitive object.							
 *	@param[in] Tag Tag to analyse.									
 *	@return	TRUE if the tag is a primitive object, FALSE if not.
 **/
int BerTlvIsTagPrimitiveObject(BER_TLV_TAG Tag) AVL_DEPRECATED ;


/*! \brief	Check if the tag is a constructed object.							
 *	@param[in] Tag Tag to analyse.								
 *	@return	TRUE if the tag is a constructed object, FALSE if not.
 **/
int BerTlvIsTagConstructedObject(BER_TLV_TAG Tag) AVL_DEPRECATED ;


/*! \brief	Check that a tag is a valid one.								
 *	@param[in] Tag Tag to analyse.									
 *	@return	TRUE if the tag is valid, FALSE if not.
 **/
int BerTlvIsTagValid(BER_TLV_TAG Tag) AVL_DEPRECATED ;


////

/*! \brief	Calculate the number of bytes needed to encode a BER-TLV tag.							
 *	@param[in] Tag Tag to encode.									
 *	@return	The number of bytes needed.
 **/
int BerTlvGetTagSize(BER_TLV_TAG Tag) AVL_DEPRECATED ;


/*! \brief	Calculate the number of bytes needed to encode a BER-TLV length.							
 *	@param[in] Length Length to encode.										
 *	@return	The number of bytes needed.
 **/
int BerTlvGetLengthSize(BER_TLV_LENGTH Length) AVL_DEPRECATED ;


/*! \brief	Skip the padding bytes if present.							
 *	@param[in] pBuffer Buffer that contains the encoded tags.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return	The number of bytes skipped.
 **/
int BerTlvSkipPadding(const void* pBuffer, int nBufferSize) AVL_DEPRECATED ;

//// Tag encoding/decoding

/*! \brief	Encode a BER-TLV tag into a buffer.							
 *	@param[in] Tag Tag to encode.
 *	@param[in,out] pBuffer Buffer to fill with the encoded tag.	
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return	The number of bytes written or -1 if the buffer is too small.
 **/
int BerTlvEncodeTag(BER_TLV_TAG Tag, void* pBuffer, int nBufferSize) AVL_DEPRECATED ;


/*! \brief	Decode a BER-TLV tag from a buffer.							
 *	@param[out] pTag Decoded tag.
 *	@param[in] pBuffer Buffer that contains the encoded tag.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return	
 *	- > 0 : The number of bytes read. The tag is correctly read.
 *	- < 0 : The number of bytes read. The tag is incorrectly read (more than 4 bytes, ...).
 *	- = 0 : There is no tag or the tag is not correctly formatted.
 **/
int BerTlvDecodeTag(BER_TLV_TAG* pTag, const void* pBuffer, int nBufferSize) AVL_DEPRECATED ;


//// Length encoding/decoding

/*! \brief Encode a BER-TLV length into a buffer.							
 *	@param[in] Length Length to encode.
 *	@param[in,out] pBuffer Buffer to fill with the encoded length.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return	The number of bytes written or -1 if the buffer is too small.
 **/
int BerTlvEncodeLength(BER_TLV_LENGTH Length, void* pBuffer, int nBufferSize) AVL_DEPRECATED ;


/*! \brief Decode a BER-TLV length from a buffer.							
 *	@param[out] pLength Decoded length.
 *	@param[in] pBuffer Buffer that contains the encoded length.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return
 *	- > 0 : The number of bytes read. The length is correctly read.
 *	- < 0 : The number of bytes read. The length is incorrectly read (more than 5 bytes, ...).
 *	- = 0 : There is no length or the length is not correctly formatted.
 **/
int BerTlvDecodeLength(BER_TLV_LENGTH* pLength, const void* pBuffer, int nBufferSize) AVL_DEPRECATED ;


//// Tag and length encoding/decoding

/*! \brief	Encode a BER-TLV tag and length into a buffer.							
 *	@param[in] Tag Tag to encode.
 *	@param[in] Length Length to encode.	
 *	@param[in,out] pBuffer Buffer to fill with the encoded tag and length.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return	The number of bytes written or -1 if the buffer is too small.
 **/
int BerTlvEncode(BER_TLV_TAG Tag, BER_TLV_LENGTH Length, void* pBuffer, int nBufferSize) AVL_DEPRECATED ;


/*! \brief Decode a BER-TLV length from a buffer.
 *	@param[out] pTag Decoded tag.	
 *	@param[out] pLength Decoded length.
 *	@param[in] pBuffer Buffer that contains the encoded tag and length.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return
 *	- > 0 : The number of bytes read. The tag and length are correctly read.
 *	- < 0 : The number of bytes read. The tag and length are incorrectly read.
 *	- = 0 : There is no tag or the length, or one of them is not correctly formatted.
 **/
int BerTlvDecode(BER_TLV_TAG* pTag, BER_TLV_LENGTH* pLength, const void* pBuffer, int nBufferSize) AVL_DEPRECATED ;

#endif //#if defined (__GNUC__) || defined(_DEPRECATED_SDK920_AVL_)

#ifdef __cplusplus
}
#endif

#endif // __BERTLV_H__INCLUDED__
