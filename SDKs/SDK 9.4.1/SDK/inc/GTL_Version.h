/**
 * \file GTL_Version.h
 * \brief Functions used to get the common library information.
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

#ifndef __GTL_VERSION_H__INCLUDED__
#define __GTL_VERSION_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

//! \brief Type of common library software identifier.
typedef unsigned long GTL_SOFTWARE_ID;

//! \brief Type of common library software version.
typedef unsigned short GTL_SOFTWARE_VERSION;

//! \brief Type of common library software CRC.
typedef unsigned short GTL_SOFTWARE_CRC;

//! \brief Type of the Common library information.
typedef struct
{
	GTL_SOFTWARE_ID m_SoftId;			/*!< Library identifier. */
	GTL_SOFTWARE_VERSION m_SoftVersion;	/*!< Library version. */
	GTL_SOFTWARE_CRC m_SoftCrc;			/*!< Library CRC. */
} T_GTL_INFO_STRUCT;


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Returns the Common library information (identifier, version and CRC).
//! \param[out] pInfoStruct Structure information to be filled.

void GTL_Version_GetInfos (const T_GTL_INFO_STRUCT ** pInfoStruct);



#endif // __GTL_VERSION_H__INCLUDED__
