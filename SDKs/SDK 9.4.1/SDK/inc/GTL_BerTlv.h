/**
 * \file GTL_BerTlv.h
 * \brief Standard BER-TLV functions.
 *
 *
 * \author Ingenico
 * \author Copyright (c) 2009 Ingenico, 1 rue claude Chappe,\n
 *		   07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __GTL_BER_TLV_H__INCLUDED__
#define __GTL_BER_TLV_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup BerTlvStatus
//! @{

#define STATUS_BER_TLV_OK						0		/*!< Indicates processing is correct. */
#define STATUS_BER_TLV_END						1		/*!< Indicates there is no more tag to parse in the TLV buffer. */
#define STATUS_BER_TLV_ERROR					2		/*!< Indicates an internal error occured. */
#define STATUS_BER_TLV_NOT_ENOUGH_SPACE			3		/*!< Indicates there is not enough space in the buffer to add data (BER-TLV encoding). */

#define STATUS_BER_TLV_BAD_ENCODING				20		/*!< Indicates a BER TLV coding error. */
#define STATUS_BER_TLV_TAG_TOO_LONG				21		/*!< Indicates read tag is too long (coded on more than 4 bytes). */
#define STATUS_BER_TLV_LENGTH_TOO_LONG			22		/*!< Indicates read length is too long (coded on more than 4 bytes). */
#define STATUS_BER_TLV_BAD_TAG					23		/*!< Indicates the provided tag for BER-TLV encoding is not valid. */
#define STATUS_BER_TLV_PADDING_NOT_ALLOWED		24		/*!< Indicates there is padding in the buffer but this one is not allowed. */

//! @}


//! \addtogroup BerTlvDefines
//! @{

#define BER_TLV_TAG_CLASS_MASK					0xc0	/*!< Mask to retreive the tag class. */
#define BER_TLV_TAG_UNIVERSAL_CLASS				0x00	/*!< Universal tag class. */
#define BER_TLV_TAG_APPLICATION_CLASS			0x40	/*!< Application tag class. */
#define BER_TLV_TAG_CONTEXT_SPECIFIC_CLASS		0x80	/*!< Context specific tag class. */
#define BER_TLV_TAG_PRIVATE_CLASS				0xc0	/*!< Private tag class. */
#define BER_TLV_TAG_CONSTRUCTED					0x20	/*!< Constructed or primitive tag flag. */
#define BER_TLV_TAG_SEE_NEXT_BYTES				0x1f	/*!< "See subsequent bytes" tag flag. */

#define BER_TLV_LENGTH_OTHERS_BYTES				0x80	/*!< Flag that indicates that several bytes are used for the length. */
#define BER_TLV_LENGTH_NUMBER_OF_BYTES_MASK		0x7f	/*!< Mask to retreive the number of bytes used to encode the length. */

#define BER_TLV_TAG_ANOTHER_BYTE				0x80	/*!< "Another byte follows" tag flag. */

//! @}


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

//! \addtogroup BerTlvTypes
//! @{

//! \brief Type of a BER-TLV tag.
typedef unsigned long BER_TLV_TAG;

//! \brief Type of a BER-TLV length.
typedef unsigned long BER_TLV_LENGTH;

//! \brief Type of a BER-TLV value.
typedef const unsigned char * BER_TLV_VALUE;

//! @}


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup BerTlvTagFunctions
//! @{

//! \brief Retreive the class of a BER-TLV tag								
//! \param[in] Tag Tag to analyse.										
//! \return The class of the tag.

int GTL_BerTlv_GetTagClass (const BER_TLV_TAG Tag);



//! \brief Check if the tag belongs to the universal class.								
//! \param[in] Tag Tag to analyse.										
//! \return	TRUE if the tag belongs to the universal class.
//! \return FALSE if not.

int GTL_BerTlv_IsTagUniversalClass (const BER_TLV_TAG Tag);



//! \brief Check if the tag belongs to the application class.						
//! \param[in] Tag Tag to analyse.									
//! \return TRUE if the tag belongs to the application class.
//! \return FALSE if not.

int GTL_BerTlv_IsTagApplicationClass (const BER_TLV_TAG Tag);



//! \brief Check if the tag belongs to the context specific class.							
//! \param[in] Tag Tag to analyse.	
//! \return	TRUE if the tag belongs to the context specific class.
//! \return FALSE if not.

int GTL_BerTlv_IsTagContextSpecificClass (const BER_TLV_TAG Tag);



//! \brief Check if the tag belongs to the private class.							
//! \param[in] Tag Tag to analyse.									
//! \return	TRUE if the tag belongs to the private class.
//! \return FALSE if not.

int GTL_BerTlv_IsTagPrivateClass (const BER_TLV_TAG Tag);



//! \brief Check if the tag is a primitive object.							
//! \param[in] Tag Tag to analyse.									
//! \return	TRUE if the tag is a primitive object.
//! \return FALSE if not.

int GTL_BerTlv_IsTagPrimitiveObject (const BER_TLV_TAG Tag);



//! \brief Check if the tag is a constructed object.							
//! \param[in] Tag Tag to analyse.								
//! \return	TRUE if the tag is a constructed object.
//! \return FALSE if not.

int GTL_BerTlv_IsTagConstructedObject (const BER_TLV_TAG Tag);



//! \brief Check that a tag is a valid one.								
//! \param[in] Tag Tag to analyse.									
//! \return	TRUE if the tag is valid.
//! \return FALSE if not.

int GTL_BerTlv_IsTagValid (BER_TLV_TAG Tag);

//! @}



#endif // __GTL_BER_TLV_H__INCLUDED__
