#ifndef __SEC_AESHMAC_INTERF_H__
#define __SEC_AESHMAC_INTERF_H__

// Copyright (c) 2009 INGENICO France , rue claude Chappe,
// 07503 Guilherand-Granges, France, All Rights Reserved.
// 
// INGENICO France has intellectual property rights relating
// to the technology embodied in this software.  In particular,
// and without limitation, these intellectual property rights
// may include one or more patents.
// 
// This software is distributed under licenses restricting
// its use, copying, distribution, and decompilation.
// No part of this software may be reproduced in any form
// by any means without prior written authorization of
// INGENICO France.
// 
//! \file  SEC_AESHMacinterface.h
//! \brief This header file contains complementary functions interface, to use AES and HMAC schemes  

//! \addtogroup DLLsecu_EXTEND
//! @{
//! \defgroup DLLsecu_EXTEND_AES_HMAC Library AES and HMAC schemes 
//! \ingroup DLLsecu_EXTEND
//! @{
//! \brief This library contains complementary functions to use AES and HMAC schemes
//!


//! \brief SEC_RandomMACAESKeyExpRSA() generates a Random MAC/AES key in a secret area and exports it with a RSA public key encryption.
//!
//! It only works on a BL2 booster, if the secret area has the format C_SEC_TLV (the scheme to call is "TlvMAKeyGen").\n
//! A MAC key has 2 parts \n
//!  Scheme to sign with your application: #NAM_TLV_MACKEYGEN "TlvMAKeyGen"
//!
//! \param[in] secureType Secure part used to store the random key
//! \param[in] ptRandomKeyId Random Key Id (cAlgoType has to be set to TLV_TYPE_MAC for HMAC key or TLV_TYPE_AES for AES key)
//! \param[in] iRandomKeySize Random Key size in bytes; multiple of 4, max is 128 (if this parameter is 32 for MAC key, the 2 parts of the MAC key have 16 bytes)
//! \param[in] *pt_stRSAPubKey RSA public Key in the form Exponent, Modulus; values are LSB first(max 2048 bits)
//! \param[out] pt_OutputRSABlock Output RSA ciphered key block (LSB first) 
//! \param[out] pt_uiOutputRSABlockLength Length in bytes of the Output RSA ciphered key block 
//! \return OK (0) is successful, otherwise error
int SEC_RandomMACAESKeyExpRSA (T_SEC_PARTTYPE secureType, T_SEC_DATAKEY_ID * ptRandomKeyId,
						 int iRandomKeySize, 
						 R_RSA_PUBLIC_KEY * pt_stRSAPubKey, 
						 unsigned char * pt_OutputRSABlock, unsigned int * pt_uiOutputRSABlockLength);


//! \brief SEC_ComputeHMAC() Computing signature HMAC-SHA256  
//!
//! To compute HMAC-SHA256.\n
//! HMAC = H (K + opad // H (K + ipad // M)\n
//! With :\n
//! K is the key (16 bytes)\n
//! H is SHA256 computation\n
//! opad are the 64 padding bytes 0X5C\n
//! ipad are the 64 padding bytes 0X36\n
//! M is the message (data input)\n
//! + is the XOR operation\n
//! // is the concatenation operation\n
//! It only works on a BL2 booster, if the secret area has the for-mat C_SEC_TLV (the scheme to call is "TlvHMac").\n
//!  Scheme to sign with your application: #NAM_TLV_HMAC "TlvHMac"
//!
//! Secure part used for scheme running : Ciphering functions (C_SEC_CIPHERING)\n
//! \param[in] ptCipherKeyId Key Id of the key to use (cAlgoType has to be set to TLV_TYPE_MAC)
//! \param[in] pt_inputData Data buffer to cipher
//! \param[in] uiInputDataLength Length in bytes of the Input Data buffer
//! \param[in] iKeyMACIndex MAC key value index : part of the MAC key to use (0 for the 1rst part or 1 for the 2nd part of the MAC key value)
//! \param[in] uiHMACLength Length in bytes of the HMAC to compute
//! \param[out] pt_OutputHMAC Computed HMAC buffer (length is uiHMACLength) 
//! \return OK (0) is successful, otherwise error
//! \par TEST CASE #1 :
//!	\verbatim  
//!   Input buffer : 200 bytes to 0
//!   Key : 16 bytes to 0xAA
//!   HMAC-SHA256 (32 bytes) : (hexa form) 0x74, 0x6C,0xBF,0x65,0xCA,0x96,0x91,0x83,
//!                                        0x95,0xAB,0x58,0xF7,0x20,0x0C,0xE6,0xCE,
//!                                        0x6E,0xCA,0xB4,0x26,0x15,0x3D,0x70,0x1F,
//!                                        0x7C,0xD3,0xA9,0x82,0x19,0xB5,0x77,0x1E
//!	\endverbatim 
int SEC_ComputeHMAC (T_SEC_DATAKEY_ID * ptCipherKeyId,  
				 unsigned char * pt_inputData, unsigned int uiInputDataLength,
				 int iKeyMACIndex, unsigned int uiHMACLength,
				 unsigned char * pt_OutputHMAC);


//! \brief SEC_AESCipher() AES CBC ciphering/deciphering data (Cipher Block Chaining mode).
//! 
//! It only works on a BL2 booster, if the secret area has the format C_SEC_TLV (the scheme to call is "TlvAESCiph").\n
//!  Scheme to sign with your application: #NAM_TLV_AESCIPH "TlvAESCiph"
//!
//! Secure part used for scheme running : Ciphering functions (C_SEC_CIPHERING)\n
//! \param[in] ptCipherKeyId Key Id of the key to use (cAlgoType has to be set to TLV_TYPE_AES)
//! \param[in] iOper : Ciphering (C_SEC_CIPHER_FUNC) or deciphering (C_SEC_DECIPHER_FUNC) function 
//! \param[in] ucModeCBC TRUE for CBC mode or FALSE for ECB mode 
//! \param[in] pt_inputData Data buffer to cipher/decipher
//! \param[in] uiInputDataLength Length (in bytes) of the input data buffer
//! \param[in] pt_IV  pointer to 16 bytes ICV value (or NULL pointer if 16 bytes zero value)
//! \param[out] pt_OutputData output ciphered/deciphered data 
//! \param[out] pt_uiOutputDataLength length (in bytes) of output ciphered/deciphered data 
//! \return OK (0) is successful, otherwise error
//! \par TEST CASE #1 :
//!	\verbatim  
//!	  Key (16 bytes) : 0x06,0xA9,0x21,0x40,0x36,0xB8,0xA1,0x5B,
//!	                   0x51,0x2E,0x03,0xD5,0x34,0x12,0x00,0x06
//!	  Initial Vector (16 bytes) : 0x3D,0xAF,0xBA,0x42,0x9D,0x9E,0xB4,0x30,
//!	                              0xB4,0x22,0xDA,0x80,0x2C,0x9F, 0xAC,0x41
//!	  Input data (32 bytes) : 0x53,0x69,0x6E,0x67,0x6C,0x65,0x20,0x62,
//!	                          0x6C,0x6F,0x63,0x6B,0x20,0x6D,0x73,0x67
//!	                          0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10
//!	                          0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10
//!	  AES-CBC (32 bytes) : 0xE3,0x53,0x77,0x9C,0x10,0x79,0xAE,0xB8,
//!	                       0x27,0x08,0x94,0x2D,0xBE,0x77,0x18,0x1A,
//!	                       0xB9,0x7C,0x82,0x5E,0x1C,0x78,0x51,0x46,
//!	                       0x54,0x2D,0x39,0x69,0x41,0xBC,0xE5,0x5D
//!	\endverbatim 
int SEC_AESCipher (T_SEC_DATAKEY_ID * ptCipherKeyId, T_SEC_OPER_FUNCT iOper, unsigned char ucModeCBC, 
				 unsigned char * pt_inputData, unsigned int uiInputDataLength,
				 unsigned char * pt_IV,
				 unsigned char * pt_OutputData, unsigned int * pt_uiOutputDataLength);
//! @}
//! @}

#endif /* __SEC_AESHMAC_INTERF__ */
