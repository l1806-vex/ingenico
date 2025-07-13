/**
 * \file GTL_BerTlvDecodeLow.h
 * \brief Functions used to decode BER-TLV buffers. It is a lower level as the one provided within GTL_BerTlvDecode.h file.
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

#ifndef __GTL_BER_TLV_DECODE_LOW_H__INCLUDED__
#define __GTL_BER_TLV_DECODE_LOW_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief	Skip the padding bytes if present.							
//! \param[in] pBuffer Buffer that contains the encoded tags.
//! \param[in] nBufferSize size of the buffer \a pBuffer.
//! \return	The number of bytes skipped.

int GTL_BerTlvDecodeLow_SkipPadding (const void* pBuffer, int nBufferSize);



//! \brief	Decode a BER-TLV tag from a buffer.							
//! \param[out] pTag Decoded tag.
//! \param[in] pBuffer Buffer that contains the encoded tag.
//! \param[in] nBufferSize size of the buffer \a pBuffer.
//! \param[out] pPaddingPresent Indicates if padding is present or not.
//! \return	
//!	- > 0 : The number of bytes read. The tag is correctly read.
//!	- = 0 : There is no tag (no more tag).
//!	- = -1 : The tag is not correctly encoded (missing bytes). 
//!	- = -2 : The tag is incorrectly read (more than 4 bytes, ...).

int GTL_BerTlvDecodeLow_DecodeTag (BER_TLV_TAG* pTag, const void* pBuffer, int nBufferSize, int * pPaddingPresent);



//! \brief Decode a BER-TLV length from a buffer.							
//! \param[out] pLength Decoded length.
//! \param[in] pBuffer Buffer that contains the encoded length.
//! \param[in] nBufferSize size of the buffer \a pBuffer.
//! \return
//!	- > 0 : The number of bytes read. The length is correctly read.
//!	- > 0 : The number of bytes read. The tag is correctly read.
//!	- = 0 : There is no length.
//!	- = -1 : The length is not correctly encoded (missing bytes). 
//!	- = -3 : The length is incorrectly read (more than 4 bytes, ...).

int GTL_BerTlvDecodeLow_DecodeLength (BER_TLV_LENGTH* pLength, const void* pBuffer, int nBufferSize);



//! \brief Decode a BER-TLV length from a buffer.
//! \param[out] pTag Decoded tag.	
//! \param[out] pLength Decoded length.
//! \param[in] pBuffer Buffer that contains the encoded tag and length.
//! \param[in] nBufferSize size of the buffer \a pBuffer.
//!	\return
//!	- > 0 : The number of bytes read. The tag and length are correctly read.
//!	- = 0 : There is no tag or the length.
//!	- = -1 : The tag or length is not correctly encoded (missing bytes).
//!	- = -2 : The tag is incorrectly read (more than 4 bytes, ...).
//!	- = -3 : The length is incorrectly read (more than 4 bytes, ...).

int GTL_BerTlvDecodeLow_Decode (BER_TLV_TAG * pTag, BER_TLV_LENGTH * pLength, const void * pBuffer, int nBufferSize);



#endif // __GTL_BER_TLV_DECODE_LOW_H__INCLUDED__
