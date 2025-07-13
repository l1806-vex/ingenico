/**
* \file convert.h
* \brief This module contains utility functions.
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

#ifndef _DATAELTS_H_
#define _DATAELTS_H_

//! \defgroup Group_db_util Utility functions management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define DB_OK		0						//!< definition of successful database access.
#define DB_KO		-4						//!< definition of failed database access.

#define AAR			0xC0					//!< definition of AAR.

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

//! \brief Definition of DataElement extended structure.
typedef struct {
	DataElement		elt;					//!< Data Element containing tag, length, and ptValue fields.
} DataElementExt;

/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */


/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function converts a string of two characters into a short integer.
//! \param[in] data : string to be converted.
//! \return Converted short.
//===========================================================================
unsigned short CharToShort(unsigned char *data);

//===========================================================================
//! \brief This function converts a string of four characters into a long integer.
//! \param[in] data : string to be converted.
//! \return Converted long.
//===========================================================================
unsigned long CharToLong(unsigned char *data);

//===========================================================================
//! \brief This function converts a short integer into a string of two characters.
//! \param[in] value : short to be converted.
//! \param[out] data : converted string.
//===========================================================================
void ShortToChar(unsigned short value,unsigned char *data);

//===========================================================================
//! \brief This function converts a long integer into a string of four characters.
//! \param[in] value : long to be converted.
//! \param[out] data : converted string.
//===========================================================================
void LongToChar(unsigned long value,unsigned char *data);

//===========================================================================
//! \brief This function converts an hexadecimal buffer to an ascii buffer.
//! \param[in] ac_x_hexbuf : hexadecimal buffer.
//! \param[in] i_x_hexbuflg : length of hexadecimal buffer.
//! \param[out] ac_x_asciibuf : output ascii buffer.
//! \return Always 1.
//===========================================================================
int HexToAscii (char * ac_x_hexbuf, int i_x_hexbuflg, unsigned char * ac_x_asciibuf);

//===========================================================================
//! \brief This function converts an DCB buffer to an ascii buffer.
//! \param[out] dest : output ascii buffer.
//! \param[in] src : hexadecimal buffer.
//! \param[in] size : length of hexadecimal buffer.
//! \return 
//! - 0 if conversion successfull.
//! - 1 if the given length is < 0.
//===========================================================================
int Hexascii( unsigned char *dest , unsigned char *src , int size);

//! @}

#endif

