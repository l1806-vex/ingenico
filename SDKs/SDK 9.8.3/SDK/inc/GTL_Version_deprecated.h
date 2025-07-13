/**
 * \file GTL_Version_deprecated.h
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

#ifndef __GTL_VERSION_DEPRECATED_H__INCLUDED__
#define __GTL_VERSION_DEPRECATED_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

#ifndef _DEPRECATED_GTL_SDK090800_
#define GTL_SOFTWARE_ID				ERROR_Deprecation_For_GTL_SeeDocumentation_In_CHM_File;
// This error is generated to warn you about the deprecation of GTL for Telium+. You can remove this error by adding the define _DEPRECATED_GTL_SDK090800_ to your project options.
#else
//! \brief Type of common library software identifier.
typedef unsigned long GTL_SOFTWARE_ID;
#endif

#ifndef _DEPRECATED_GTL_SDK090800_
#define GTL_SOFTWARE_VERSION		ERROR_Deprecation_For_GTL_SeeDocumentation_In_CHM_File;
// This error is generated to warn you about the deprecation of GTL for Telium+. You can remove this error by adding the define _DEPRECATED_GTL_SDK090800_ to your project options.
#else
//! \brief Type of common library software version.
typedef unsigned short GTL_SOFTWARE_VERSION;
#endif

#ifndef _DEPRECATED_GTL_SDK090800_
#define GTL_SOFTWARE_CRC			ERROR_Deprecation_For_GTL_SeeDocumentation_In_CHM_File;
// This error is generated to warn you about the deprecation of GTL for Telium+. You can remove this error by adding the define _DEPRECATED_GTL_SDK090800_ to your project options.
#else
//! \brief Type of common library software CRC.
typedef unsigned short GTL_SOFTWARE_CRC;
#endif

#ifndef _DEPRECATED_GTL_SDK090800_
#define T_GTL_INFO_STRUCT			ERROR_Deprecation_For_GTL_SeeDocumentation_In_CHM_File;
// This error is generated to warn you about the deprecation of GTL for Telium+. You can remove this error by adding the define _DEPRECATED_GTL_SDK090800_ to your project options.
#else
//! \brief Type of the Common library information.
typedef struct
{
	GTL_SOFTWARE_ID m_SoftId;			/*!< Library identifier. */
	GTL_SOFTWARE_VERSION m_SoftVersion;	/*!< Library version. */
	GTL_SOFTWARE_CRC m_SoftCrc;			/*!< Library CRC. */
} T_GTL_INFO_STRUCT;
#endif

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

#ifndef _DEPRECATED_GTL_SDK090800_
#define GTL_Version_GetInfos()		ERROR_Deprecation_For_GTL_SeeDocumentation_In_CHM_File;
// This error is generated to warn you about the deprecation of GTL for Telium+. You can remove this error by adding the define _DEPRECATED_GTL_SDK090800_ to your project options.
#else
//! \brief Returns the Common library information (identifier, version and CRC).
//! \param[out] pInfoStruct Structure information to be filled.
void GTL_Version_GetInfos (const T_GTL_INFO_STRUCT ** pInfoStruct) MACRO_DEPRECATED;
#endif

#endif // __GTL_VERSION_DEPRECATED_H__INCLUDED__
