#ifndef __SEC_EXTDUKPT_INTERF_H__
#define __SEC_EXTDUKPT_INTERF_H__

// Copyright (c) 2009 INGENICO FRANCE, rue claude Chappe,
// 07503 Guilherand-Granges, France, All Rights Reserved.
// 
// INGENICO FRANCE has intellectual property rights relating
// to the technology embodied in this software.  In particular,
// and without limitation, these intellectual property rights
// may include one or more patents.
// 
// This software is distributed under licenses restricting
// its use, copying, distribution, and decompilation.
// No part of this software may be reproduced in any form
// by any means without prior written authorization of
// Ingenico France.

//! \file        SEC_ExtDukptinterface.h
//! \brief This header file contains complementary functions interface, to use with SEC_Dukptxxx functions of the DLL SECURITY;



//! \addtogroup DLLsecu_EXTEND
//! @{
//! \defgroup DLLsecu_EXTEND_ExtDukpt Library EXTENT DUKPT (ANS X9.24-1:2009) 
//! \ingroup DLLsecu_EXTEND
//! @{
//! \brief This library contains complementary functions to use with SEC_Dukptxxx functions of the DLL SECURITY; \n
//! these functions are relative to cAlgoType set to TLV_TYPE_TDESDUKPT
//! \cond NOT_DOCUMENTED
//! or TLV_TYPE_TDESDUKPTLIGHT
//! \endcond

//! \par 
//! \defgroup DLLsecu_EXTEND_ExtDukpt_KEY_ADVANCE Automatic Key advance Mode
//! \brief Automatic mode for current UKPT key advance:\n
//! The current UKPT key advance is incremented before calculating the UKPT key for:
//! -	ciphering a PIN : SEC_DukptEncryptPin\n
//! -	other ciphering functions (_SEC_DukptECBCipher , _SEC_DukptCBCCipher , _SEC_DukptComputeMAC_AC_lg and _SEC_DukptVerifyMAC_AC_lg) if the previous function is _SEC_DukptVerifyMAC_AC_lg.\n
//! Note : If 10 calls of ciphering functions do not increment the current UKPT key advance, the next call will increment the current UKPT key advance.\n
//! \ingroup DLLsecu_EXTEND_ExtDukpt
//! @{
#define     C_EXTDUKPT_AUTO_MODE        0        //!< automatic mode current UKPT key advance
#define     C_EXTDUKPT_FORCED_MODE      1        //!< forced mode, to advance the current UKPT key
//! @}


//! \brief SEC_DukptECBCipher() TDES ciphering/deciphering data in ECB mode (Electronic Code Block Chaining) with a UKPT key (ANS X9.24).\n
//! If the secret area does not exist or if the secret area has the format C_SEC_NO_TLV then an error is returned\n
//! The UKPT key is a XOR with a 16 bytes constant variant (00 00 00 00 00 FF 00 00 00 00 00 00 00 FF 00 00) and the current UKPT key. And an extra OWF operation (TDES cipher in ECB mode to apply to the key with itself) is performed to the computed key.\n
//!  Schemes to sign with your application: #NAM_TLV_DUKPT_TDES "TlvDukptTDes"
//! \cond NOT_DOCUMENTED
//!										  , #NAM_TLV_DUKPT_LIGHT_TDES "SDukptLTDes"
//! \endcond
//! \param[in] secureTypeKey : Secure part used to store the DUKPT keys
//! \param[in] ptDukptId : Dukpt Id; cAlgoType has to be set to TDES DUKPT TLV_TYPE_TDESDUKPT
//! \cond NOT_DOCUMENTED
//!									or TLV_TYPE_TDESDUKPTLIGHT
//! \endcond
//! \param[in] ucOperation : Ciphering (C_SEC_CIPHER_FUNC) or deciphering (C_SEC_DECIPHER_FUNC) function
//! \param[in] ucKeyAdvance : Automatic (C_EXTDUKPT_AUTO_MODE) or forced (C_EXTDUKPT_FORCED_MODE) mode
//! \param[in] pt_InputData : Data buffer to cipher/decipher
//! \param[in] uiInputDataLength : Length in bytes of the Input Data buffer (it must be multiple of 8 and max is 512)
//! \param[out] pt_OutputData : Output Data buffer
//! \param[out] uiOutputDataLength : Length in bytes of the Output Data buffer
//! \param[out] pt_OutputSMID : Output SMID transaction (10 bytes)
//! \return OK (0) is successful, otherwise error
//! \note
//! \par TEST CASE #1 :
//!	\verbatim  
//!	  ucOperation: C_SEC_CIPHER_FUNC
//!	  pt_InputData : (24 bytes) string bytes "Hello_World_123456789012"
//!	  Initial key : (16 bytes) (hex form) 6AC292FAA1315B4D858AB3A3D7D5933A
//!	  SMID/KSN : (10 bytes) (hex form) FFFF9876543210E00002
//!	  pt_OutputData : (hex form) C197C32549E0E82A0377E7FF557572D2F5019813474BE037
//!	\endverbatim 
int SEC_DukptECBCipher (T_SEC_PARTTYPE secureTypeKey,
						T_SEC_DATAKEY_ID * ptDukptId,
						unsigned char ucOperation,
						unsigned char ucKeyAdvance,
						unsigned char * pt_InputData,
						unsigned int  uiInputDataLength,
						unsigned char * pt_OutputData,
						unsigned int  * uiOutputDataLength,
						unsigned char * pt_OutputSMID);

//! \brief SEC_DukptCBCCipher() TDES ciphering/deciphering data in CBC mode (Cipher Block Chaining) with a UKPT key (ANS X9.24).\n
//! If the secret area does not exist or if the secret area has the format C_SEC_NO_TLV then an error is returned\n
//! The UKPT key is a XOR with a 16 bytes constant variant (00 00 00 00 00 FF 00 00 00 00 00 00 00 FF 00 00) and the current UKPT key.\n 
//! And an extra OWF operation (TDES cipher in ECB mode to apply to the key with itself) is performed to the computed key.\n
//!  Schemes to sign with your application: #NAM_TLV_DUKPT_TDES "TlvDukptTDes"
//! \cond NOT_DOCUMENTED
//!										  , #NAM_TLV_DUKPT_LIGHT_TDES "SDukptLTDes"
//! \endcond
//! \param[in] secureTypeKey : Secure part used to store the DUKPT keys
//! \param[in] ptDukptId : Dukpt Id; cAlgoType has to be set to TDES DUKPT TLV_TYPE_TDESDUKPT
//! \cond NOT_DOCUMENTED
//!									or TLV_TYPE_TDESDUKPTLIGHT
//! \endcond
//! \param[in] ucOperation : Ciphering (C_SEC_CIPHER_FUNC) or deciphering (C_SEC_DECIPHER_FUNC) function
//! \param[in] ucKeyAdvance : Automatic (C_EXTDUKPT_AUTO_MODE) or forced (C_EXTDUKPT_FORCED_MODE) mode
//! \param[in] pt_InputData : Data buffer to cipher/decipher
//! \param[in] uiInputDataLength : Length in bytes of the Input Data buffer (it must be multiple of 8 and max is 512)
//! \param[in] pt_IV : Initial vector (8 bytes) (Null pointer if no Initial vector)
//! \param[out] pt_OutputData : Output Data buffer
//! \param[out] uiOutputDataLength : Length in bytes of the Output Data buffer
//! \param[out] pt_OutputSMID : Output SMID transaction (10 bytes)
//! \return OK (0) is successful, otherwise error
//! \note
//! \par TEST CASE #1 :
//!	\verbatim  
//!	  ucOperation: C_SEC_CIPHER_FUNC
//!	  pt_InputData : (24 bytes) string bytes "Hello_World_123456789012"
//!	  pt_IV : NULL pointer
//!	  Initial key : (16 bytes) (hex form) 6AC292FAA1315B4D858AB3A3D7D5933A
//!	  SMID/KSN : (10 bytes) (hex form) FFFF9876543210E00002
//!	  pt_OutputData : (hex form) C197C32549E0E82A722CBEFAC980041A6CE78666DAB6D62B
//!	\endverbatim 
int SEC_DukptCBCCipher (T_SEC_PARTTYPE secureTypeKey,
						T_SEC_DATAKEY_ID * ptDukptId,
						unsigned char ucOperation,
						unsigned char ucKeyAdvance,
						unsigned char * pt_InputData,
						unsigned int  uiInputDataLength,
						unsigned char * pt_IV,
						unsigned char * pt_OutputData,
						unsigned int  * uiOutputDataLength,
						unsigned char * pt_OutputSMID);

//! \brief SEC_DukptComputeMAC_AC_lg() To compute MAC in CBC mode (Cipher Block Chaining) according to the Annex C of X9.19-1996 with a UKPT key (ANS X9.24). The 1rst DES key value is the MSB 8 bytes of the TDES UKPT key and the 2nd DES key value is the LSB 8 bytes of the TDES UKPT key.\n
//! The computed MAC size is variable (8 bytes max).\n
//! If the secret area does not exist or if the secret area has the format C_SEC_NO_TLV then an error is returned\n
//! The UKPT key is a XOR with a 16 bytes constant variant (00 00 00 00 00 00 FF 00 00 00 00 00 00 00 FF 00) and the current UKPT key.\n 
//! See Annex "CBC MAC Annex C X9.19 algorithm" in the document "SECURITY DLL Reference guide".\n
//!  Schemes to sign with your application: #NAM_TLV_DUKPT_TDES "TlvDukptTDes"
//! \cond NOT_DOCUMENTED
//!										  , #NAM_TLV_DUKPT_LIGHT_TDES "SDukptLTDes"
//! \endcond
//! \param[in] secureTypeKey : Secure part used to store the DUKPT keys
//! \param[in] ptDukptId : Dukpt Id; cAlgoType has to be set to TDES DUKPT TLV_TYPE_TDESDUKPT
//! \cond NOT_DOCUMENTED
//!									or TLV_TYPE_TDESDUKPTLIGHT
//! \endcond
//! \param[in] ucModeKeyAdvance : Automatic (C_EXTDUKPT_AUTO_MODE) or forced (C_EXTDUKPT_FORCED_MODE) mode
//! \param[in] pt_InputData : Input Data buffer
//! \param[in] uiInputDataLength : Length in bytes of the Input Data buffer (it must be multiple of 8 and greater than 16)
//! \param[in] pt_IV : Initial vector (8 bytes) (Null pointer if no Initial vector)
//! \param[in] uiInputMACLength : Length in bytes of the MAC to compute (from 4 to 8)
//! \param[out] pt_OutputMAC : Computed MAC buffer (8 bytes max)
//! \param[out] pt_OutputSMID : Output SMID transaction (10 bytes)
//! \return OK (0) is successful, otherwise error
//! \note
//! \par TEST CASE #1 :
//!	\verbatim  
//!	  pt_InputData : (32 bytes) (hex form) 1101020305060708090A1201020305060708090B130102030100000000000000
//!	  pt_IV : NULL pointer
//!	  uiInputMACLength : 8
//!	  Initial key : (16 bytes) (hex form) 6AC292FAA1315B4D858AB3A3D7D5933A
//!	  SMID/KSN : (10 bytes) (hex form) FFFF9876543210E00002
//!	  pt_OutputMAC : (8 bytes) (hex form) 06434550C4587B4E
//!	\endverbatim 
int SEC_DukptComputeMAC_AC_lg(T_SEC_PARTTYPE secureTypeKey,
						   T_SEC_DATAKEY_ID * ptDukptId,
						   unsigned char ucModeKeyAdvance,
						   unsigned char * pt_InputData,
						   unsigned int  uiInputDataLength,
						   unsigned char * pt_IV,
						   unsigned int uiInputMACLength,
						   unsigned char * pt_OutputMAC,
						   unsigned char * pt_OutputSMID);

//! \brief SEC_DukptVerifyMAC_AC_lg() To verify MAC in CBC mode (Cipher Block Chaining) according to the Annex C of X9.19-1996 with a UKPT key (ANS X9.24).\n 
//! The 1rst DES key value is the MSB 8 bytes of the TDES UKPT key and the 2nd DES key value is the LSB 8 bytes of the TDES UKPT key.\n
//! The size of the MAC to verify is variable (8 bytes max).\n
//! If the secret area does not exist or if the secret area has the format C_SEC_NO_TLV then an error is returned\n
//! The UKPT key is a XOR with a 16 bytes constant variant (00 00 00 00 FF 00 00 00 00 00 00 00 FF 00 00 00) and the current UKPT key.\n 
//! See Annex "CBC MAC Annex C X9.19 algorithm" in the document "SECURITY DLL Reference guide"\n
//!  Schemes to sign with your application: #NAM_TLV_DUKPT_TDES "TlvDukptTDes"
//! \cond NOT_DOCUMENTED
//!										  , #NAM_TLV_DUKPT_LIGHT_TDES "SDukptLTDes"
//! \endcond
//! \param[in] secureTypeKey : Secure part used to store the DUKPT keys
//! \param[in] ptDukptId : Dukpt Id; cAlgoType has to be set to TDES DUKPT TLV_TYPE_TDESDUKPT
//! \cond NOT_DOCUMENTED
//!									or TLV_TYPE_TDESDUKPTLIGHT
//! \endcond
//! \param[in] ucModeKeyAdvance : Automatic (C_EXTDUKPT_AUTO_MODE) or forced (C_EXTDUKPT_FORCED_MODE) mode
//! \param[in] pt_InputData : Input Data buffer
//! \param[in] uiInputDataLength : Length in bytes of the Input Data buffer (it must be multiple of 8 and greater than 16)
//! \param[in] pt_IV : Initial vector (8 bytes) (Null pointer if no Initial vector)
//! \param[in] uiInputMACLength : Length in bytes of the MAC to compute (from 4 to 8)
//! \param[in] pt_MACToVerify : MAC data to verify (8 bytes max)
//! \param[out] pt_OutputSMID : Output SMID transaction (10 bytes)
//! \return OK (0) is successful, otherwise error
int SEC_DukptVerifyMAC_AC_lg(T_SEC_PARTTYPE secureTypeKey,
						  T_SEC_DATAKEY_ID * ptDukptId,
						  unsigned char ucModeKeyAdvance,
						  unsigned char * pt_InputData,
						  unsigned int  uiInputDataLength,
						  unsigned char * pt_IV,
                          unsigned int uiInputMACLength,
						  unsigned char * pt_MACToVerify,
						  unsigned char * pt_OutputSMID);

//! \brief SEC_DukptComputeMAC_AC() This deprecated function is the same as #SEC_DukptComputeMAC_AC_lg by specifying a 4 bytes MAC.\n
//! To compute MAC in CBC mode (Cipher Block Chaining) according to the Annex C of X9.19-1996 with a UKPT key (ANS X9.24). The 1rst DES key value is the MSB 8 bytes of the TDES UKPT key and the 2nd DES key value is the LSB 8 bytes of the TDES UKPT key.\n
//! This function computes a 4 bytes MAC.\n
//! If the secret area does not exist or if the secret area has the format C_SEC_NO_TLV then an error is returned\n
//! The UKPT key is a XOR with a 16 bytes constant variant (00 00 00 00 00 00 FF 00 00 00 00 00 00 00 FF 00) and the current UKPT key.\n 
//! See Annex "CBC MAC Annex C X9.19 algorithm" in the document "SECURITY DLL Reference guide".\n
//!  Schemes to sign with your application: #NAM_TLV_DUKPT_TDES "TlvDukptTDes"
//! \cond NOT_DOCUMENTED
//!										  , #NAM_TLV_DUKPT_LIGHT_TDES "SDukptLTDes"
//! \endcond
//! \param[in] secureTypeKey : Secure part used to store the DUKPT keys
//! \param[in] ptDukptId : Dukpt Id; cAlgoType has to be set to TDES DUKPT TLV_TYPE_TDESDUKPT
//! \cond NOT_DOCUMENTED
//!									or TLV_TYPE_TDESDUKPTLIGHT
//! \endcond
//! \param[in] ucModeKeyAdvance : Automatic (C_EXTDUKPT_AUTO_MODE) or forced (C_EXTDUKPT_FORCED_MODE) mode
//! \param[in] pt_InputData : Input Data buffer
//! \param[in] uiInputDataLength : Length in bytes of the Input Data buffer (it must be multiple of 8 and greater than 16)
//! \param[in] pt_IV : Initial vector (8 bytes) (Null pointer if no Initial vector)
//! \param[out] pt_OutputMAC : Computed MAC buffer (4 bytes)
//! \param[out] pt_OutputSMID : Output SMID transaction (10 bytes)
//! \return OK (0) is successful, otherwise error
//! \note
//! \par TEST CASE #1 :
//!	\verbatim  
//!	  pt_InputData : (32 bytes) (hex form) 1101020305060708090A1201020305060708090B130102030100000000000000
//!	  pt_IV : NULL pointer
//!	  Initial key : (16 bytes) (hex form) 6AC292FAA1315B4D858AB3A3D7D5933A
//!	  SMID/KSN : (10 bytes) (hex form) FFFF9876543210E00002
//!	  pt_OutputMAC : (4 bytes) (hex form) 06434550
//!	\endverbatim 
#ifdef _DEPRECATED_SDK90_
int SEC_DukptComputeMAC_AC(T_SEC_PARTTYPE secureTypeKey,
						   T_SEC_DATAKEY_ID * ptDukptId,
						   unsigned char ucModeKeyAdvance,
						   unsigned char * pt_InputData,
						   unsigned int  uiInputDataLength,
						   unsigned char * pt_IV,
						   unsigned char * pt_OutputMAC,
						   unsigned char * pt_OutputSMID);
#endif

//! \brief SEC_DukptVerifyMAC_AC() This deprecated function is the same as #SEC_DukptVerifyMAC_AC_lg by specifying a 4 bytes MAC.\n
//! To verify MAC in CBC mode (Cipher Block Chaining) according to the Annex C of X9.19-1996 with a UKPT key (ANS X9.24).\n 
//! The 1rst DES key value is the MSB 8 bytes of the TDES UKPT key and the 2nd DES key value is the LSB 8 bytes of the TDES UKPT key.\n
//! This function verifies a 4 bytes MAC.\n
//! If the secret area does not exist or if the secret area has the format C_SEC_NO_TLV then an error is returned\n
//! The UKPT key is a XOR with a 16 bytes constant variant (00 00 00 00 FF 00 00 00 00 00 00 00 FF 00 00 00) and the current UKPT key.\n 
//! See Annex "CBC MAC Annex C X9.19 algorithm" in the document "SECURITY DLL Reference guide"\n
//!  Schemes to sign with your application: #NAM_TLV_DUKPT_TDES "TlvDukptTDes"
//! \cond NOT_DOCUMENTED
//!										  , #NAM_TLV_DUKPT_LIGHT_TDES "SDukptLTDes"
//! \endcond
//! \param[in] secureTypeKey : Secure part used to store the DUKPT keys
//! \param[in] ptDukptId : Dukpt Id; cAlgoType has to be set to TDES DUKPT TLV_TYPE_TDESDUKPT
//! \cond NOT_DOCUMENTED
//!									or TLV_TYPE_TDESDUKPTLIGHT
//! \endcond
//! \param[in] ucModeKeyAdvance : Automatic (C_EXTDUKPT_AUTO_MODE) or forced (C_EXTDUKPT_FORCED_MODE) mode
//! \param[in] pt_InputData : Input Data buffer
//! \param[in] uiInputDataLength : Length in bytes of the Input Data buffer (it must be multiple of 8 and greater than 16)
//! \param[in] pt_IV : Initial vector (8 bytes) (Null pointer if no Initial vector)
//! \param[in] pt_MACToVerify : MAC data to verify (4 bytes)
//! \param[out] pt_OutputSMID : Output SMID transaction (10 bytes)
//! \return OK (0) is successful, otherwise error
#ifdef _DEPRECATED_SDK90_
int SEC_DukptVerifyMAC_AC(T_SEC_PARTTYPE secureTypeKey,
						  T_SEC_DATAKEY_ID * ptDukptId,
						  unsigned char ucModeKeyAdvance,
						  unsigned char * pt_InputData,
						  unsigned int  uiInputDataLength,
						  unsigned char * pt_IV,
						  unsigned char * pt_MACToVerify,
						  unsigned char * pt_OutputSMID);
#endif


//! @}
//! @}
#endif /* __SEC_EXTDUKPT_INTERF_H__ */
