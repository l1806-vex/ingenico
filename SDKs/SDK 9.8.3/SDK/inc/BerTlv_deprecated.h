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

/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief Retreive the class of a BER-TLV tag								
 *	@param[in] Tag Tag to analyse.										
 *	@return The class of the tag.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvGetTagClass ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvGetTagClass(BER_TLV_TAG Tag) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Check if the tag belongs to the universal class.								
 *	@param[in] Tag Tag to analyse.										
 *	@return	TRUE if the tag belongs to the universal class, FALSE if not.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvIsTagUniversalClass ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvIsTagUniversalClass(BER_TLV_TAG Tag) MACRO_DEPRECATED ;
#endif



/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief 	Check if the tag belongs to the application class.						
 *	@param[in] Tag Tag to analyse.									
 *	@return TRUE if the tag belongs to the application class, FALSE if not.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvIsTagApplicationClass ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvIsTagApplicationClass(BER_TLV_TAG Tag) MACRO_DEPRECATED ;
#endif


/*!  @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Check if the tag belongs to the context specific class.							
 *	@param[in] Tag Tag to analyse.	
 *	@return	TRUE if the tag belongs to the context specific class, FALSE if not.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvIsTagContextSpecificClass ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvIsTagContextSpecificClass(BER_TLV_TAG Tag) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Check if the tag belongs to the private class.							
 *	@param[in] Tag Tag to analyse.									
 *	@return	TRUE if the tag belongs to the private class, FALSE if not.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvIsTagPrivateClass ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvIsTagPrivateClass(BER_TLV_TAG Tag) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Check if the tag is a primitive object.							
 *	@param[in] Tag Tag to analyse.									
 *	@return	TRUE if the tag is a primitive object, FALSE if not.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvIsTagPrimitiveObject ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvIsTagPrimitiveObject(BER_TLV_TAG Tag) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Check if the tag is a constructed object.							
 *	@param[in] Tag Tag to analyse.								
 *	@return	TRUE if the tag is a constructed object, FALSE if not.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvIsTagConstructedObject ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvIsTagConstructedObject(BER_TLV_TAG Tag) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Check that a tag is a valid one.								
 *	@param[in] Tag Tag to analyse.									
 *	@return	TRUE if the tag is valid, FALSE if not.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvIsTagValid ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvIsTagValid(BER_TLV_TAG Tag) MACRO_DEPRECATED ;
#endif


////

/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Calculate the number of bytes needed to encode a BER-TLV tag.							
 *	@param[in] Tag Tag to encode.									
 *	@return	The number of bytes needed.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvGetTagSize ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvGetTagSize(BER_TLV_TAG Tag) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Calculate the number of bytes needed to encode a BER-TLV length.							
 *	@param[in] Length Length to encode.										
 *	@return	The number of bytes needed.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvGetLengthSize ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvGetLengthSize(BER_TLV_LENGTH Length) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Skip the padding bytes if present.							
 *	@param[in] pBuffer Buffer that contains the encoded tags.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return	The number of bytes skipped.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvSkipPadding ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvSkipPadding(const void* pBuffer, int nBufferSize) MACRO_DEPRECATED ;
#endif

//// Tag encoding/decoding

/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Encode a BER-TLV tag into a buffer.							
 *	@param[in] Tag Tag to encode.
 *	@param[in,out] pBuffer Buffer to fill with the encoded tag.	
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return	The number of bytes written or -1 if the buffer is too small.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvEncodeTag ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvEncodeTag(BER_TLV_TAG Tag, void* pBuffer, int nBufferSize) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Decode a BER-TLV tag from a buffer.							
 *	@param[out] pTag Decoded tag.
 *	@param[in] pBuffer Buffer that contains the encoded tag.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return	
 *	- > 0 : The number of bytes read. The tag is correctly read.
 *	- < 0 : The number of bytes read. The tag is incorrectly read (more than 4 bytes, ...).
 *	- = 0 : There is no tag or the tag is not correctly formatted.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvDecodeTag ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvDecodeTag(BER_TLV_TAG* pTag, const void* pBuffer, int nBufferSize) MACRO_DEPRECATED ;
#endif


//// Length encoding/decoding

/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief Encode a BER-TLV length into a buffer.							
 *	@param[in] Length Length to encode.
 *	@param[in,out] pBuffer Buffer to fill with the encoded length.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return	The number of bytes written or -1 if the buffer is too small.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvEncodeLength ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvEncodeLength(BER_TLV_LENGTH Length, void* pBuffer, int nBufferSize) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief Decode a BER-TLV length from a buffer.							
 *	@param[out] pLength Decoded length.
 *	@param[in] pBuffer Buffer that contains the encoded length.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return
 *	- > 0 : The number of bytes read. The length is correctly read.
 *	- < 0 : The number of bytes read. The length is incorrectly read (more than 5 bytes, ...).
 *	- = 0 : There is no length or the length is not correctly formatted.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvDecodeLength ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvDecodeLength(BER_TLV_LENGTH* pLength, const void* pBuffer, int nBufferSize) MACRO_DEPRECATED ;
#endif


//// Tag and length encoding/decoding

/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief	Encode a BER-TLV tag and length into a buffer.							
 *	@param[in] Tag Tag to encode.
 *	@param[in] Length Length to encode.	
 *	@param[in,out] pBuffer Buffer to fill with the encoded tag and length.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return	The number of bytes written or -1 if the buffer is too small.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvEncode ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvEncode(BER_TLV_TAG Tag, BER_TLV_LENGTH Length, void* pBuffer, int nBufferSize) MACRO_DEPRECATED ;
#endif


/*! @brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * @brief Decode a BER-TLV length from a buffer.
 *	@param[out] pTag Decoded tag.	
 *	@param[out] pLength Decoded length.
 *	@param[in] pBuffer Buffer that contains the encoded tag and length.
 *	@param[in] nBufferSize size of the buffer \a pBuffer.
 *	@return
 *	- > 0 : The number of bytes read. The tag and length are correctly read.
 *	- < 0 : The number of bytes read. The tag and length are incorrectly read.
 *	- = 0 : There is no tag or the length, or one of them is not correctly formatted.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define BerTlvDecode ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
int BerTlvDecode(BER_TLV_TAG* pTag, BER_TLV_LENGTH* pLength, const void* pBuffer, int nBufferSize) MACRO_DEPRECATED ;
#endif



#ifdef __cplusplus
}
#endif

#endif // __BERTLV_H__INCLUDED__
