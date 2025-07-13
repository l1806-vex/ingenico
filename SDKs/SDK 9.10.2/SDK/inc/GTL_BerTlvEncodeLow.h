/**
 * \file GTL_BerTlvEncodeLow.h
 * \brief Functions used to encode BER-TLV buffers. It is a lower level as the one provided within GTL_BerTlvEncode.h file.
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

#ifndef __GTL_BER_TLV_ENCODE_LOW_H__INCLUDED__
#define __GTL_BER_TLV_ENCODE_LOW_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Calculate the number of bytes needed to encode a BER-TLV tag.
//! \param[in] Tag Tag to encode.									
//! \return	The number of bytes needed.

int GTL_BerTlvEncodeLow_GetTagSize (BER_TLV_TAG Tag);



//! \brief	Calculate the number of bytes needed to encode a BER-TLV length.							
//! \param[in] Length Length to encode.										
//! \return	The number of bytes needed.

int GTL_BerTlvEncodeLow_GetLengthSize (BER_TLV_LENGTH Length);



//! \brief	Encode a BER-TLV tag into a buffer.
//! \param[in] Tag Tag to encode.
//! \param[in,out] pBuffer Buffer to fill with the encoded tag and length.
//! \param[in] nBufferSize size of the buffer \a pBuffer.
//! \return The number of bytes written or -1 if the buffer is too small.

int GTL_BerTlvEncodeLow_EncodeTag (BER_TLV_TAG Tag, void * pBuffer, int nBufferSize);



//! \brief Encode a BER-TLV length into a buffer.
//! \param[in] Length Length to encode.
//! \param[in,out] pBuffer Buffer to fill with the encoded tag and length.
//! \param[in] nBufferSize size of the buffer \a pBuffer.
//! \return	The number of bytes written or -1 if the buffer is too small.

int GTL_BerTlvEncodeLow_EncodeLength (BER_TLV_LENGTH Length, void * pBuffer, int nBufferSize);



//! \brief	Encode a BER-TLV tag and length into a buffer.
//! \param[in] Tag Tag to encode.
//! \param[in] Length Length to encode.
//! \param[in,out] pBuffer Buffer to fill with the encoded tag and length.
//! \param[in] nBufferSize size of the buffer \a pBuffer.
//! \return	The number of bytes written or -1 if the buffer is too small.

int GTL_BerTlvEncodeLow_Encode (BER_TLV_TAG Tag, BER_TLV_LENGTH Length, void * pBuffer, int nBufferSize);





#endif // __GTL_BER_TLV_ENCODE_H__INCLUDED__
