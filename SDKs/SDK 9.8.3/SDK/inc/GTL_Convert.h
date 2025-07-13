/**
 * \file GTL_Convert.h
 * \brief This file describes all the conversion functions.
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

#ifndef __GTL_CONVERT_H_DEFINED__
#define __GTL_CONVERT_H_DEFINED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup ConvertFunctions
//!	@{

//!	\brief Convert a DCB coded string into ASCII format.
//!	\param[in] pDcb	DCB coded string to convert.
//!	\param[out] szString Converted string in ascii format. The string is zero terminated.
//!	\param[in] nDcbFirstIndex First BCD index (begin conversion from this index).
//!	\param[in] nDcbLastIndex Last BCD index (end conversion to this index).
//! \note
//! Here is an example : 
//! pDcb = 0x12 0x34 0xAB 0xCD
//! GTL_Convert_DcbToAscii (pDcb, szString, 0, 8) : szString = 0x31 0x32 0x33 0x34 0x41 0x42 0x43 0x44 0x00
//! GTL_Convert_DcbToAscii (pDcb, szString, 1, 5) : szString = 0x32 0x33 0x34 0x41 0x42 0x00

void GTL_Convert_DcbToAscii (const unsigned char* pDcb, char* szString, int nDcbFirstIndex, int nDcbLastIndex);



//!	\brief Convert a DCB coded number into ASCII format.
//!	\param[in] pDcb DCB coded number to convert.
//!	\param[out] szString Converted number in ascii format. The string is zero terminated.
//!	\param[in] nDcbLength DCB coded number length (in bytes).
//!	\param[in] nNumberLength ASCII coded number length (in bytes).
//! Here is an example : 
//! pDcb = 0x12 0x34 0xAB 0xCD
//! unsigned char szString [10];
//! GTL_Convert_DcbNumberToAscii (pDcb, szString, 4, 10) : szString = 0x00 0x00 0x31 0x32 0x33 0x34 0x41 0x42 0x43 0x44 0x00
//! GTL_Convert_DcbNumberToAscii (pDcb, szString, 4, 3) : szString = 0x31 0x32 0x33 0x00

void GTL_Convert_DcbNumberToAscii (const unsigned char* pDcb, char* szString, int nDcbLength, int nNumberLength);



//!	\\brief Convert a DCB coded number into ASCII format with deleting the padding.
//!	\param[in] pDcb DCB coded number to convert.
//!	\param[out] szString Converted number in ascii format. The string is zero terminated.
//!	\param[in] nDcbLength DCB coded number length (in bytes).
//! Here is an example : 
//! pDcb = 0x12 0x34 0xAB 0xCD 0xEF 0xFF
//! unsigned char szString [10];
//! GTL_Convert_DcbPaddedToAscii (pDcb, szString, 6) : szString = 0x31 0x32 0x33 0x34 0x41 0x42 0x43 0x44 0x45 0x00 ("1234ABCDE")

void GTL_Convert_DcbPaddedToAscii (const unsigned char* pDcb, char* szString, int nDcbLength);



//! \brief Convert a DCB coded number to an unsigned long.
//! \param[in] pDcb DCB coded number to convert.
//! \param[out] pValue Unsigned long containing the converted value.
//! \param[in] nDcbLength DCB coded number length (in bytes).
//! Here is an example : 
//! pDcb = 0x12 0x34
//! GTL_Convert_DcbNumberToUl (pDcb, &ulNumber, 2) : ulNumber = 0x000004D2 (1234).

void GTL_Convert_DcbNumberToUl (const unsigned char* pDcb, unsigned long* pValue, int nDcbLength);



//!	\brief Convert a Binary coded number to an unsigned long.
//!	\param[in] pBin Binary coded number to convert.
//!	\param[out] pValue Unsigned long containing the converted value.
//!	\param[in] nLength DCB coded number length (in bytes).
//! Here is an example : 
//! pDcb = 0x12 0xAB
//! GTL_Convert_DcbNumberToUl (pDcb, &ulNumber, 2) : ulNumber = 0x000012AB.

void GTL_Convert_BinNumberToUl (const void* pBin, unsigned long* pValue, const int nLength);



//! \brief Convert a character into a lower case.
//! \param[in] ucCharacter Character to be converted.
//! \return The converted character.
//! \note The conversion is only performed if \a ucCharacter is between 'A' and 'Z'.

unsigned char GTL_Convert_LowerCase (unsigned char ucCharacter);



//! \brief Convert a character into a upper case.
//! \param[in] ucCharacter Character to be converted.
//! \return The converted character.
//! \note The conversion is only performed if \a ucCharacter is between 'a' and 'z'.

unsigned char GTL_Convert_UpperCase (unsigned char ucCharacter);



//! \brief Convert an unsigned long (binary) into a DCB data.
//! \param[in] ulValue Value to be converted. 
//! \param[out] pDcb Output DCB converted data.
//! \param[in] nDcbLength Max size of DCB value (in bytes).
//! Here is an example : 
//! ulValue = 0x0001E240 (123456)
//! GTL_Convert_UlToDcbNumber (ulValue, &ucDcb, 4) : ucDcb = {0x00,0x12,0x34,0x56}.
//! GTL_Convert_UlToDcbNumber (ulValue, &ucDcb, 2) : ucDcb = {0x12,0x34}.

void GTL_Convert_UlToDcbNumber (unsigned long ulValue, void* pDcb, int nDcbLength);



//! \brief Convert an unsigned long (binary) into a DCB data.
//! \param[in] ulValue Value to be converted. 
//! \param[out] pBin Output Binary converted data.
//! \param[in] nBinLength Max size of Binary value (in bytes).
//! Here is an example : 
//! ulValue = 0xABCD1234
//! GTL_Convert_UlToBinNumber (ulValue, &ucBin, 3) : ucBin = {0xAB,0xCD,0x12}.
//! GTL_Convert_UlToBinNumber (ulValue, &ucBin, 6) : ucBin = {0x00,0x00,0xAB,0xCD,0x12,0x34}.

void GTL_Convert_UlToBinNumber (unsigned long ulValue, void* pBin, int nBinLength);

//!	@}


#endif // __GTL_CONVERT_H_DEFINED__
