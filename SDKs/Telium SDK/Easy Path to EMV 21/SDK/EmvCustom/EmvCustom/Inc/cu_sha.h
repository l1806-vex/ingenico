/**
* \file cu_sha.h
* \brief This module contains the functions needed for Secure Hash Algorithm (SHA).
* Heavily modified by Uwe Hollerbach uh@alumni.caltech edu
* from Peter C. Gutmann's implementation as found in Applied Cryptography by Bruce Schneier
*
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

#ifndef SHA_H
#define SHA_H

//! \defgroup Group_cu_sha Secured Hash Algorithm (SHA) management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define SHA_BLOCKSIZE				64			//!< Size of SHA block.
#define SHA_DIGESTSIZE				20			//!< Size of digest block.

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

#ifndef __CRYPTO_DEF_H

//! \brief Definition of SHA Info structure.
typedef struct {
	unsigned long digest[5];					//!< Message digest.
	unsigned long count_lo, count_hi;			//!< 64-bit bit count.
	unsigned long data[16];						//!< SHA data buffer.
	int local;									//!< unprocessed amount in data.
} SHA_INFO;

#endif

//! \brief Definition of SHA Info pointer.
typedef SHA_INFO	*SHA;

/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function initializes the SHA digest : inits the structure 
//! given as parameter, and internal global variable.
//! \param[in] sha_info : \ref SHA_INFO structure to init.
//===========================================================================
void sha_init(SHA_INFO *sha_info);

//===========================================================================
//! \brief This function updates the SHA digest : starts the computing.
//! \param[in,out] sha_info : \ref SHA_INFO structure to update.
//! \param[in] buffer : buffer on which to calculate SHA.
//! \param[in] count : buffer size.
//===========================================================================
void sha_update(SHA_INFO *sha_info, unsigned char *buffer, int count);

//===========================================================================
//! \brief This function finishes computing the SHA digest.
//! \param[in,out] sha_info : \ref SHA_INFO structure to update.
//===========================================================================
void sha_final(SHA_INFO *sha_info);

//===========================================================================
//! \brief This function performs the three steps of SHA calculation : 
//! - sha_init
//! - sha_update
//! - sha_final.
//! \li This is the public entry point SHA-1 algorithm use.
//! \param[in] Input_Data : buffer on which to calculate SHA.
//! \param[in] Input_Length : buffer size.
//! \return The computed SHA.
//===========================================================================
unsigned long *SHA1_Compute ( unsigned char *Input_Data, int Input_Length );

//! @}

#endif /* SHA_H */
