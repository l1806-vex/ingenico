/*! @addtogroup KSFAM_CRYPTO
	* @{
**/

/***
 * Copyright (c) 2001 Ascom Monetel SA, rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * Ascom Monetel SA has intellectual property rights relating
 * to the technology embodied in this software.  In particular, 
 * and without limitation, these intellectual property rights 
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting 
 * its use, copying, distribution, and decompilation.  
 * No part of this software may be reproduced in any form 
 * by any means without prior written authorization of 
 * Ascom Monetel.
 *
 * @Title:        TELIUM_CRYPTO.H
 * @Description:  Definitions for security Algorithms 
 * @Company:      
 * @Reference:    ANSI C Code
 * @Comment:
 *       
 * @author        L. PION
 * @version       1.0
 * @date          2002/02/14 
 */ 

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __CRYPTO_H
#define __CRYPTO_H

#define DLL_OK                  0
#define DLL_KO                  (-1)
#define DLL_NOT_LOAD            (-2)
#define DLL_BAD_ID              (-3)
#define DLL_FUNCTION_KO         (-4)
#define DLL_BAD_PROC_ADR        (-5)

/*! @brief This function is used to get current version of DLL crypto
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 * @return Returns :
 * - Version [ID][MAJOR][MINOR][PATCH]
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
int  Crypto_Dll_Version (void);

/*! @brief This function NOT a string
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 * @param Buf1 : String.
 * @param Len : Len of Buf1.
 * @return none
 * @par exit None
 * @section Sample CRYPTO

 * @include Telium_crypto_Sample_01.c
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
void NotB (unsigned char *Buf1,int Len);

/*! @brief XOR between two string
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 * @param Buf1 : String1 and result string.
 * @param Buf2 : String2.
 * @param Len : Len of Buf1 and buf2.
 * @return none
 * @par exit None
 * @section Sample CRYPTO

 * @include Telium_crypto_Sample_02.c
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
void XorB (unsigned char *Buf1,unsigned char *Buf2,int Len);

/*! @brief OR between two string
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 * @param Buf1 : String1 and result string.
 * @param Buf2 : String2.
 * @param Len : Len of Buf1 and buf2.
 * @return none
 * @par exit None
 * @section Sample CRYPTO

 * @include Telium_crypto_Sample_03.c
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
void OrB (unsigned char *Buf1,unsigned char *Buf2,int Len);

/*! @brief AND between two string
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 * @param Buf1 : String1 and result string.
 * @param Buf2 : String2.
 * @param Len : Len of Buf1 and buf2.
 * @return none
 * @par exit None
 * @section Sample CRYPTO

 * @include Telium_crypto_Sample_04.c
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
void AndB (unsigned char *Buf1,unsigned char *Buf2,int Len);

/*! @brief Calculate a CRC16 on a buffer
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 * @param buffer : buffer.
 * @param size   : size of buffer.
 * @return Returns : CRC16 result
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
CRC16 CalculateCrc (void *buffer, unsigned int size);

/*! @brief Calculate a LRC on a buffer starting
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 *	Initial value is ZERO
 * @param Buffer : buffer.
 * @param Len   : size of buffer.
 * @return Returns : LRC result
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
unsigned short CalculateLrc    (unsigned char* Buffer ,int Len);

/*! @brief initialize the SHA digest
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 * @param sha_info : structure containing SHA info.
 * @return none
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
void ShaInit   (SHA_INFO *sha_info);

/*! @brief update the SHA digest
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 * @param sha_info : structure containing SHA info.
 * @param Input_Data : input block
 * @param Input_Length : input len
 * @return none
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
void ShaUpdate (SHA_INFO *sha_info,unsigned char *Input_Data,unsigned int Input_Length);

/*! @brief finish computing the SHA digest
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 * @param sha_info : structure containing SHA info.
 * @return none
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
void ShaFinal  (SHA_INFO *sha_info);

/*! @brief Entry point SHA-1 Algorithm to be used
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 * @param Input_Data : input block  
 * @param Input_Length : input len
 * @param Digest : Digest (160 bits)
 * @return none
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
void ShaCompute (unsigned char *Input_Data,unsigned int Input_Length,unsigned char *Digest);

/*! @brief Begins an MD5 operation, writing a new context
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 * @param context : MD5 context
 * @return none
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
void MD5Init   (MD5_CTX *context);

/*! @brief MD5 block update operation
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 *  Continues an MD5 message-digest operation, processing another 
 *  message block, and updating the context.
 *
 * @param context : MD5 context
 * @param input : input block,
 * @param inputLen : input length 
 * @return none
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
void MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen);

/*! @brief MD5 finalization
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 *  Ends an MD5 message-digest operation, writing the the message 
 *  digest and zeroizing the context.
 *
 * @param digest : result pointer
 * @param context : MD5 context
 * @return none
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
void MD5Final  (unsigned char digest[DIGEST_SIZE], MD5_CTX *context);

#define SHA256_DIGEST_SIZE  32
#define SHA256_BLOCK_SIZE  ( 512 / 8)

#define SHA_SUCCESS 0
#define SHA_FAIL    1

typedef struct
{
  unsigned int	count[2];
  int			bufsz;
  unsigned char buf[SHA256_BLOCK_SIZE];
  unsigned int	h[8];
}T_SHA256_CTX;


/*! @brief initialize the SHA256 digest
 *
 * @param p_ctx : structure containing SHA256 info.
 * @return SHA_SUCCESS
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
int sha256_init(T_SHA256_CTX *p_ctx);

/*! @brief update the SHA256 digest
 *
 * @param p_ctx : structure containing SHA256 info.
 * @param message : input block
 * @param len : input len
 * @return SHA_SUCCESS
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
int sha256_update (T_SHA256_CTX *p_ctx, unsigned char *message, int len);

/*! @brief finish computing the SHA256 digest
 *
 * @param p_ctx : structure containing SHA256 info.
 * @param digest : Digest (256 bits)
 * @return SHA_SUCCESS
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
int sha256_finish (T_SHA256_CTX *p_ctx, unsigned char *digest);

/*! @brief Entry point SHA256 Algorithm to be used
 *
 * @param message : input block  
 * @param Length : input len
 * @param digest : Digest (256 bits)
 * @return SHA_SUCCESS
 * @par exit None
 *
 * @link KSFAM_CRYPTO Back to top @endlink
*/
int sha256 (unsigned char * message, unsigned int Length, unsigned char * digest );

#endif

/*! @} **/

#ifdef __cplusplus
}
#endif
