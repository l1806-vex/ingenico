/**
 * \file GTL_BerTlvDecode.h
 * \brief Functions used to decode BER-TLV buffers.
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

#ifndef __GTL_BER_TLV_DECODE_H__INCLUDED__
#define __GTL_BER_TLV_DECODE_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

//! \addtogroup BerTlvDecodeStructures
//! @{

//! \brief Type of a BER TLV structure for decoding.
typedef struct {
	unsigned int nIndex;				/*!< Index in the BerTlv buffer. */
	unsigned long nLength;				/*!< Length of \a pBerTlvData buffer. */
	const unsigned char * pBerTlvData;	/*!< Ber Tlv buffer. */
} T_BER_TLV_DECODE_STRUCT;

//! @}

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup BerTlvDecodeFunctions
//! @{

//! \brief Initialise the structure with the provided data
//! \param[out] pBerTlvStruct Structure to be initialised.
//! \param[in] pBerTlvData Data to be used for initialisation.
//! \param[in] nLength length of \a pBerTlvData.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>Always.</td></tr>
//! </table>

int GTL_BerTlvDecode_Init (T_BER_TLV_DECODE_STRUCT * pBerTlvStruct, const unsigned char * pBerTlvData, const unsigned int nLength);



//! \brief Parse the next tag in the BER-TLV structure.
//! \param[in,out] pBerTlvStruct Structure to be parsed. Structure is updated (parsing index).
//! \param[out] pReadTag Read tag.
//! \param[in] bPaddingAllowed Indicate if padding is allowed (padding is 0x00 or 0xFF).
//! \param[out] pBytesRead Number of bytes read (correspond to number of bytes coding the tag).
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>Next tag in the structure is correctly read.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_BAD_ENCODING</td><td>Buffer is not correctly BER-TLV formatted.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_END</td><td>There is no more tag to parse in the structure.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_PADDING_NOT_ALLOWED</td><td>Unexpected padding is found.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_TAG_TOO_LONG</td><td>Tag is coded using more than 4 bytes.</td></tr>
//! </table>

int GTL_BerTlvDecode_ParseTag (T_BER_TLV_DECODE_STRUCT * pBerTlvStruct, unsigned long * pReadTag, const unsigned int bPaddingAllowed, int * pBytesRead);



//! \brief Parse the next length in the BER-TLV structure.
//! \param[in,out] pBerTlvStruct Structure to be parsed. Structure is updated (parsing index)
//! \param[out] pReadLength Read length.
//! \param[out] pBytesRead Number of bytes read (correspond to number of bytes coding the length).
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>Next length in the structure is correctly read.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_BAD_ENCODING</td><td>Buffer is not correctly BER-TLV formatted.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_END</td><td>There is no more tag to parse in the structure.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_LENGTH_TOO_LONG</td><td>Length is coded using more than 4 bytes.</td></tr>
//! </table>

int GTL_BerTlvDecode_ParseLength (T_BER_TLV_DECODE_STRUCT * pBerTlvStruct, BER_TLV_LENGTH * pReadLength, int * pBytesRead);



//! \brief Parse the next tag and length from the BER-TLV structure.
//! \param[in,out] pBerTlvStruct Structure to be parsed. Structure is updated (parsing index)
//! \param[in] nValueLength Length of the value to get.
//! \param[out] pReadValue Read value.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>Value in the structure are correctly read.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_BAD_ENCODING</td><td>Buffer is not correctly BER-TLV formatted (available bytes in the BER-TLV buffer can contains requested value).</td></tr>
//! </table>

int GTL_BerTlvDecode_ParseValue (T_BER_TLV_DECODE_STRUCT * pBerTlvStruct, const BER_TLV_LENGTH nValueLength, BER_TLV_VALUE * pReadValue);



//! \brief Parse the next tag and length from the BER-TLV structure.
//! \param[in,out] pBerTlvStruct Structure to be parsed. Structure is updated (parsing index)
//! \param[out] pReadTag Read tag.
//! \param[out] pReadLength Read length.
//! \param[out] pReadValue pointer on the tag value.
//! \param[in] bPaddingAllowed Indicate if padding is allowed (padding is 0x00 or 0xFF).
//! \param[out] pBytesRead Number of bytes read (correspond to number of bytes coding the tag + number of bytes coding the length).
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>Next tag and length in the structure are correctly read.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_BAD_ENCODING</td><td>Buffer is not correctly BER-TLV formatted.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_END</td><td>There is no more tag to parse in the structure.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_PADDING_NOT_ALLOWED</td><td>Unexpected padding is found.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_TAG_TOO_LONG</td><td>The tag is coded using more than 4 bytes.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_LENGTH_TOO_LONG</td><td>The length is coded using more than 4 bytes.</td></tr>
//! </table>

int GTL_BerTlvDecode_ParseTlv (T_BER_TLV_DECODE_STRUCT * pBerTlvStruct, BER_TLV_TAG * pReadTag, BER_TLV_LENGTH * pReadLength, BER_TLV_VALUE * pReadValue, const unsigned char bPaddingAllowed, int * pBytesRead);



//! \brief Parse the next tag and length from the BER-TLV structure (used for parsing DOLs for example).
//! \param[in,out] pBerTlvStruct Structure to be parsed. Structure is updated (parsing index)
//! \param[out] pReadTag Read tag.
//! \param[out] pReadLength Read length.
//! \param[in] bPaddingAllowed Indicate if padding is allowed (padding is 0x00 or 0xFF).
//! \param[out] pBytesRead Number of bytes read (correspond to number of bytes coding the tag + number of bytes coding the length).
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>Next tag and length in the structure are correctly read.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_BAD_ENCODING</td><td>Buffer is not correctly BER-TLV formatted.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_END</td><td>There is no more tag to parse in the structure.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_PADDING_NOT_ALLOWED</td><td>Unexpected padding is found.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_TAG_TOO_LONG</td><td>Tag is coded using more than 4 bytes.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_LENGTH_TOO_LONG</td><td>Length is coded using more than 4 bytes.</td></tr>
//! </table>

int GTL_BerTlvDecode_ParseTagLength (T_BER_TLV_DECODE_STRUCT * pBerTlvStruct, BER_TLV_TAG * pReadTag, BER_TLV_LENGTH * pReadLength, const unsigned char bPaddingAllowed, int * pBytesRead);



//! \brief Skip the padding in a BER-TLV structure.
//! \param[in,out] pBerTlvStruct BER-TLV structure on which padding has to be skipped. Structure is updated (parsing index)
//! \param[out] pBytesRead number of read bytes (for padding).
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_BER_TLV_OK</td><td>Padding correctly skipped.</td></tr>
//! <tr><td>\ref STATUS_BER_TLV_END</td><td>End of structure buffer is reached.</td></tr>
//! </table>

int GTL_BerTlvDecode_SkipPadding (T_BER_TLV_DECODE_STRUCT * pBerTlvStruct, int * pBytesRead);

//! @}


#endif // __GTL_BER_TLV_DECODE_H__INCLUDED__
