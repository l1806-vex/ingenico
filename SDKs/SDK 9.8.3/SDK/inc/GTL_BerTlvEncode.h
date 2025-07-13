/**
 * \file GTL_BerTlvEncode.h
 * \brief Functions used to encode BER-TLV buffers.
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

#ifndef __GTL_BER_TLV_ENCODE_H__INCLUDED__
#define __GTL_BER_TLV_ENCODE_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

//! \addtogroup BerTlvEncodeStructures
//! @{

//! \brief Type of a BER TLV structure for encoding.
typedef struct {
	unsigned int nIndex;				/*!< Index in the BerTlv buffer. */
	unsigned long nLength;				/*!< Length of \a pBerTlvData buffer. */
	unsigned char * pBerTlvData;		/*!< Ber Tlv buffer. */
} T_BER_TLV_ENCODE_STRUCT;

//! @}

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup BerTlvEncodeFunctions
//! @{

//! \brief Initialise the structure with the provided data (buffer to be encoded with BER-TLV).
//! \param[out] pBerTlvStruct Structure to be initialised.
//! \param[in] pBuffer Data to be filled with BER-TLV.
//! \param[in] nLength length of \a pBerTlvData.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>Always.</td></tr>
//! </table>

int GTL_BerTlvEncode_Init (T_BER_TLV_ENCODE_STRUCT * pBerTlvStruct, unsigned char * pBuffer, unsigned int nLength);



//! \brief	Encode a BER-TLV tag into a buffer.
//! \param[in,out] pBerTlvStruct Structure in which tag has to be added.
//! \param[in] Tag Tag to encode.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>The tag is correctly encoded with the buffer.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_NOT_ENOUGH_SPACE</td><td>There is not enough space in the structure buffer to add the tag.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_BAD_TAG</td><td>The provided tag is not valid.</td></tr>
//! </table>

int GTL_BerTlvEncode_EncodeTag (T_BER_TLV_ENCODE_STRUCT * pBerTlvStruct, BER_TLV_TAG Tag);



//! \brief Encode a BER-TLV length into a buffer.	
//! \param[in,out] pBerTlvStruct Structure in which tag has to be added.
//! \param[in] Length Length to encode.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>The length is correctly encoded with the buffer.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_NOT_ENOUGH_SPACE</td><td>There is not enough space in the structure buffer to add the length.</td></tr>
//! </table>

int GTL_BerTlvEncode_EncodeLength (T_BER_TLV_ENCODE_STRUCT * pBerTlvStruct, BER_TLV_LENGTH Length);



//! \brief Encode a BER-TLV value into a buffer.	
//! \param[in,out] pBerTlvStruct Structure in which value has to be added.
//! \param[in] pValue Value to encode.
//! \param[in] ulValueLength Length of \a pValue.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>The value is correctly encoded with the buffer.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_NOT_ENOUGH_SPACE</td><td>There is not enough space in the structure buffer to add the value.</td></tr>
//! </table>

int GTL_BerTlvEncode_EncodeValue (T_BER_TLV_ENCODE_STRUCT * pBerTlvStruct, BER_TLV_VALUE pValue, const unsigned long ulValueLength);



//! \brief	Encode a BER-TLV tag, length and value into a buffer.
//! \param[in,out] pBerTlvStruct Structure in which value has to be added.
//! \param[in] Tag Tag to encode.
//! \param[in] Length Length to encode.
//! \param[in] pValue Value to encode.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>The data are correctly encoded within the buffer.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_NOT_ENOUGH_SPACE</td><td>There is not enough space in the structure buffer to add the data.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_BAD_TAG</td><td>The provided tag is not valid.</td></tr>
//! </table>

int GTL_BerTlvEncode_Encode (T_BER_TLV_ENCODE_STRUCT * pBerTlvStruct, BER_TLV_TAG Tag, BER_TLV_LENGTH Length, BER_TLV_VALUE pValue);

//! @}



#endif // __COMMON_LIB_BER_TLV_ENCODE_H__INCLUDED__
