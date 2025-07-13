#ifndef __SEC_DATACIPHER_INTERF_H__
#define __SEC_DATACIPHER_INTERF_H__

// Copyright (c) 2009 INGENICO FRANCE , rue claude Chappe,
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
// INGENICO FRANCE.
// 
//! \file  SEC_DataCipherinterface.h
//! \brief This header file contains complementary functions interface, allowing cipher with OFB mode (DES/TDES) 

//! \addtogroup DLLsecu_EXTEND
//! @{
//! \defgroup DLLsecu_EXTEND_OFBMode Library Data ciphering with OFB mode (DES/TDES) 
//! \ingroup DLLsecu_EXTEND
//! @{
//! \brief This library contains complementary functions, allowing cipher with OFB mode (DES/TDES)  

//! @image html OFBMode.JPG ""
//!
//! \brief __SEC_OFBCipher() DES/TDES ciphering/deciphering data in OFB mode (Output Feedback).\n
//!  Scheme to sign with your application: #NAM_STLV_CIPHER_DATA "STLCipherDa"
//!
//! \param[in] ptCipherKeyId :  Key Id of the ciphering key (cAlgoType defines the algorithm to use DES (TLV_TYPE_KDES) or TDES (TLV_TYPE_KTDES)
//! \param[in] pt_InputData : Data buffer to cipher/decipher
//! \param[in] uiInputDataLength : Length in bytes of the Input Data buffer
//! \param[in] pt_IV : Initial vector (8 bytes)
//! \param[out] pt_OutputData : Output data buffer
//! \param[out] pt_uiOutputDataLength : Length in bytes of the Output Data buffer
//! \return OK (0) is successful, otherwise error
//! \note  
//! Specificity : No compatibility for the format C_SEC_NO_TLV of secret area.\n
//! Secure part used for scheme running : Ciphering functions (C_SEC_CIPHERING)\n
//! \par TEST CASE #1 :
//!	\verbatim  
//!	  Ciphering DES Key (8 bytes) : (hex form) 0123456789ABCDEF
//!	  Initial Vector (8 bytes) : 0102030405060708
//!	  Input data (deciphered data) (24 bytes) : 4E6F772069732074 68652074696D6520 666F7220616C6C20
//!	  Output data (ciphered data)  (24 bytes) : A8E00E3BC265F492 B59EB031B7EBD985 63B21F8194DFAA64
//!	\endverbatim 
//! \par TEST CASE #2 :
//!	\verbatim  
//!	  Ciphering TDES Key (16 bytes) : (hex form) 0123456789ABCDEF 1011121314151617
//!	  Initial Vector (8 bytes) : 0102030405060708
//!	  Input data (deciphered data) (24 bytes) : 4E6F772069732074 68652074696D6520 666F7220616C6C20
//!	  Output data (ciphered data)  (24 bytes) : 29E9A8CC1B47F070 1F3456F51C5769D8 F1B44D82F94B2F6D
//!	\endverbatim 
int __SEC_OFBCipher ( T_SEC_DATAKEY_ID * ptCipherKeyId,
					unsigned char * pt_InputData, unsigned int uiInputDataLength,
					unsigned char * pt_IV,
					unsigned char * pt_OutputData, unsigned int * pt_uiOutputDataLength );
//! @}
//! @}
#ifndef SEC_OFBCipher
#define SEC_OFBCipher __SEC_OFBCipher
#endif			

#endif /* __SEC_DATACIPHER_INTERF__ */
