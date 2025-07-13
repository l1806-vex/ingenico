/**
* \file cu_sha.c
* \brief This module contains the functions needed for Secure Hash Algorithm (SHA).
* Heavily modified by Uwe Hollerbach uh@alumni.caltech edu
* from Peter C. Gutmann's implementation as found in Applied Cryptography by Bruce Schneier

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

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "SDK30.H"
#include "cu_sha.h"

//! \addtogroup Group_cu_sha
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

// #define UNROLL_LOOPS						// a bit faster & bigger, if defined

// by default, compile for little-endian machines (Intel, Vax)
// change for big-endian machines; for machines which are neither,
// you will need to change the definition of maybe_byte_reverse
#define LITTLE_ENDIAN						// must be commented if MOTOROLA TARGET

// NIST's proposed modification to SHA (SHA-1) of 7/11/94 may be
// activated by defining USE_MODIFIED_SHA = SHA-1
#define USE_MODIFIED_SHA					// SHA-1 specifications = DON'T TOUCH FOR GIE BANK CARDS

// #define SHA_MAIN_FOR_DEBUG				// testing only

// 32-bit rotate
#define ROT32(x,n)	((x << n) | (x >> (32 - n)))


/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

// SHA constants -   Note : CONS T_SHA[0] is never used
unsigned long CONST_SHA[5];

SHA_INFO sha_info;

unsigned long sha_temp, sha_A, sha_B, sha_C, sha_D, sha_E, sha_W[80];

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

static unsigned long sha_f(int n, unsigned long x, unsigned long y, unsigned long z);

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
//! \brief Computing function.
//! \param[in] n : see SHA-1 spec.
//! \param[in] i : see SHA-1 spec.
//===========================================================================
static void FUNC ( int n, int i)
{
	unsigned long tmp1,tmp2,tmp3;
	tmp1 = ROT32(sha_A,5);
	tmp2 = sha_f(n,sha_B,sha_C,sha_D);
	tmp3 = sha_E + sha_W[i] + CONST_SHA[n];
	sha_temp = tmp1 + tmp2 + tmp3;
	sha_E = sha_D;
	sha_D = sha_C;
	sha_C = ROT32(sha_B,30);
	sha_B = sha_A;
	sha_A = sha_temp;
}

//===========================================================================
//! \brief Computing function.
//! \param[in] n : see SHA-1 spec.
//! \param[in] x : see SHA-1 spec.
//! \param[in] y : see SHA-1 spec.
//! \param[in] z : see SHA-1 spec.
//! \return xyz combinaison.
//===========================================================================
static unsigned long sha_f(int n, unsigned long x, unsigned long y, unsigned long z)
{
	if ( n==1 )
		return ((x & y) | (~x & z));
	else if ( n==2 )
		return 	(x ^ y ^ z);
	else if ( n==4 )
		return 	(x ^ y ^ z);
	else if ( n==3 )
		return  ((x & y) | (x & z) | (y & z));
	else return (0); /* error */
}



//===========================================================================
//! \brief This function performs the SHA transform.
//! \param[in,out] sha_info : \ref SHA_INFO structure to update.
//===========================================================================
static void sha_transform(SHA_INFO *sha_info)
{
	int i;


	for (i = 0; i < 16; ++i)
	{
		sha_W[i] = sha_info->data[i];
	}

	for (i = 16; i < 80; ++i)
	{
		sha_W[i] = sha_W[i-3] ^ sha_W[i-8] ^ sha_W[i-14] ^ sha_W[i-16];

		// this below define is SHA-1 specifications
#ifdef USE_MODIFIED_SHA
		sha_W[i] = ROT32(sha_W[i], 1);
#endif	// USE_MODIFIED_SHA
	}

	sha_A = sha_info->digest[0];
	sha_B = sha_info->digest[1];
	sha_C = sha_info->digest[2];
	sha_D = sha_info->digest[3];
	sha_E = sha_info->digest[4];


#ifdef UNROLL_LOOPS
	FUNC(1, 0);  FUNC(1, 1);  FUNC(1, 2);  FUNC(1, 3);  FUNC(1, 4);
	FUNC(1, 5);  FUNC(1, 6);  FUNC(1, 7);  FUNC(1, 8);  FUNC(1, 9);
	FUNC(1,10);  FUNC(1,11);  FUNC(1,12);  FUNC(1,13);  FUNC(1,14);
	FUNC(1,15);  FUNC(1,16);  FUNC(1,17);  FUNC(1,18);  FUNC(1,19);

	FUNC(2,20);  FUNC(2,21);  FUNC(2,22);  FUNC(2,23);  FUNC(2,24);
	FUNC(2,25);  FUNC(2,26);  FUNC(2,27);  FUNC(2,28);  FUNC(2,29);
	FUNC(2,30);  FUNC(2,31);  FUNC(2,32);  FUNC(2,33);  FUNC(2,34);
	FUNC(2,35);  FUNC(2,36);  FUNC(2,37);  FUNC(2,38);  FUNC(2,39);

	FUNC(3,40);  FUNC(3,41);  FUNC(3,42);  FUNC(3,43);  FUNC(3,44);
	FUNC(3,45);  FUNC(3,46);  FUNC(3,47);  FUNC(3,48);  FUNC(3,49);
	FUNC(3,50);  FUNC(3,51);  FUNC(3,52);  FUNC(3,53);  FUNC(3,54);
	FUNC(3,55);  FUNC(3,56);  FUNC(3,57);  FUNC(3,58);  FUNC(3,59);

	FUNC(4,60);  FUNC(4,61);  FUNC(4,62);  FUNC(4,63);  FUNC(4,64);
	FUNC(4,65);  FUNC(4,66);  FUNC(4,67);  FUNC(4,68);  FUNC(4,69);
	FUNC(4,70);  FUNC(4,71);  FUNC(4,72);  FUNC(4,73);  FUNC(4,74);
	FUNC(4,75);  FUNC(4,76);  FUNC(4,77);  FUNC(4,78);  FUNC(4,79);
#else /* !UNROLL_LOOPS */
	for (i = 0 ; i < 20; ++i)
	{
		FUNC(1,i);
	}
	for (i = 20; i < 40; ++i)
	{
		FUNC(2,i);
	}
	for (i = 40; i < 60; ++i)
	{
		FUNC(3,i);
	}
	for (i = 60; i < 80; ++i)
	{
		FUNC(4,i);
	}
#endif /* !UNROLL_LOOPS */

	sha_info->digest[0] += sha_A;
	sha_info->digest[1] += sha_B;
	sha_info->digest[2] += sha_C;
	sha_info->digest[3] += sha_D;
	sha_info->digest[4] += sha_E;
}

#ifdef LITTLE_ENDIAN	// used for INTEL LSB MSB format
/***************************************************************************

used if INTEL target
please undefine this for MOTOROLA target

***************************************************************************/

//===========================================================================
//! \brief This function converts data from little endian to big endian.
//! \param[in,out] buffer : data to convert.
//! \param count : buffer size.
//===========================================================================
static void maybe_byte_reverse(unsigned long *buffer, int count)
{
	int i;
	unsigned char ct[4], *cp;

	count /= sizeof(unsigned long);
	cp     = (unsigned char *) buffer;

	for (i = 0; i < count; ++i)
	{
		ct[0] = cp[0];
		ct[1] = cp[1];
		ct[2] = cp[2];
		ct[3] = cp[3];
		cp[0] = ct[3];
		cp[1] = ct[2];
		cp[2] = ct[1];
		cp[3] = ct[0];
		cp += sizeof(unsigned long);
	}
}

#else /* !LITTLE_ENDIAN */

#define maybe_byte_reverse(a,b)	/* do nothing ( MOTOROLA ) */

#endif /* LITTLE_ENDIAN */


//===========================================================================
void sha_init(SHA_INFO *sha_info)

{

	sha_info->digest[0] = 0x67452301L;
	sha_info->digest[1] = 0xefcdab89L;
	sha_info->digest[2] = 0x98badcfeL;
	sha_info->digest[3] = 0x10325476L;
	sha_info->digest[4] = 0xc3d2e1f0L;
	sha_info->count_lo  = 0L;
	sha_info->count_hi  = 0L;
	sha_info->local     = 0;

	CONST_SHA [1] = 0x5a827999L;
	CONST_SHA [2] = 0x6ed9eba1L;
	CONST_SHA [3] = 0x8f1bbcdcL;
	CONST_SHA [4] = 0xca62c1d6L;

}


//===========================================================================
void sha_update(SHA_INFO *sha_info, unsigned char *buffer, int count)
{
	int i;

	if ( (sha_info->count_lo + ((unsigned long) count << 3))
		< sha_info->count_lo)
	{
		++sha_info->count_hi;
	}

	sha_info->count_lo += (unsigned long) count << 3;
	sha_info->count_hi += (unsigned long) count >> 29;

	if (sha_info->local)
	{
		i = SHA_BLOCKSIZE - sha_info->local;
		if (i > count)
		{
			i = count;
		}
		memcpy(((unsigned char *) sha_info->data) + sha_info->local, buffer, i);
		count -= i;
		buffer += i;
		sha_info->local += i;

		if (sha_info->local == SHA_BLOCKSIZE)
		{
			maybe_byte_reverse(sha_info->data, SHA_BLOCKSIZE);
			sha_transform(sha_info);
		}
		else
		{
			return;
		}
	}

	while (count >= SHA_BLOCKSIZE)
	{
		memcpy(sha_info->data, buffer, SHA_BLOCKSIZE);
		buffer += SHA_BLOCKSIZE;
		count -= SHA_BLOCKSIZE;
		maybe_byte_reverse(sha_info->data, SHA_BLOCKSIZE);
		sha_transform(sha_info);
	}

	memcpy(sha_info->data, buffer, count);
	sha_info->local = count;
}


//===========================================================================
void sha_final(SHA_INFO *sha_info)
{
	int count;
	unsigned long lo_bit_count, hi_bit_count;

	lo_bit_count = sha_info->count_lo;
	hi_bit_count = sha_info->count_hi;

	count = (int) ((lo_bit_count >> 3) & 0x3f);

	((unsigned char *) sha_info->data)[count++] = 0x80;

	if (count > SHA_BLOCKSIZE - 8)
	{
		memset(((unsigned char *) sha_info->data) + count, 0, SHA_BLOCKSIZE - count);
		maybe_byte_reverse(sha_info->data, SHA_BLOCKSIZE);
		sha_transform(sha_info);
		memset((unsigned char *) sha_info->data, 0, SHA_BLOCKSIZE - 8);
	}
	else
	{
		memset(((unsigned char *) sha_info->data) + count, 0,
			SHA_BLOCKSIZE - 8 - count);
	}

	maybe_byte_reverse(sha_info->data, SHA_BLOCKSIZE);
	sha_info->data[14] = hi_bit_count;
	sha_info->data[15] = lo_bit_count;
	sha_transform(sha_info);
	/*& BEGIN SMO/03/1265/LB								*/
	maybe_byte_reverse(sha_info->digest, SHA_BLOCKSIZE);
	/*& END   SMO/03/1265/LB								*/
}


//===========================================================================
unsigned long *SHA1_Compute ( unsigned char *Input_Data, int Input_Length )
{
	sha_init   ( &sha_info);
	sha_update ( &sha_info, Input_Data, Input_Length);
	sha_final  ( &sha_info);
	return ( &(sha_info.digest[0]));
}



#ifdef SHA_MAIN_FOR_DEBUG
//===========================================================================
//! \brief This is the main function. It is an example of use of SHA algorithm.
//===========================================================================
void main (void)
{
	unsigned long Digest_Result[5];

	memcpy ( Digest_Result, SHA1_Compute ( "abc", 3 ), 20 );
	/* with "abc" result must be 0xA9993E36, 0x4706816A,
	0xBA3E2571, 0x7850C26C, 0x9CD0D89D
	*/
	asm int 3; /* breakpoint */
}
#endif

//! @}
