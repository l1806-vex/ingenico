/**
 * \file	SDI_Tags.h
 * \brief	Describes the SDI tags.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2010 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __SDI_TAGS_H__INCLUDED__
#define __SDI_TAGS_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup SDI_Tags
//! @{

// In range 9F918E00 to 9F918E7F for simple tags.
#define TAG_SDI_COMPONENT_NAME							0x9F918E00		/*!< Tag indicating the name of a component (ASCII up to 20 bytes). */
#define TAG_SDI_COMPONENT_IDENTIFIER					0x9F918E01		/*!< Tag indicating the identifier of a component (ASCII up to 20 bytes). */
#define TAG_SDI_COMPONENT_CRC							0x9F918E02		/*!< Tag indicating the CRC of a component (ASCII up to 4 bytes). */

// In range BF918E00 to BF918E7F for constructed tags.
#define TAG_SDI_CONFIGURATION_APPLICATION_STRUCTURE		0xBF918E00		/*!< Constructed tag containing information of an application. */
#define TAG_SDI_CONFIGURATION_DRIVER_STRUCTURE			0xBF918E01		/*!< Constructed tag containing information of a driver. */
#define TAG_SDI_CONFIGURATION_DLL_STRUCTURE				0xBF918E02		/*!< Constructed tag containing information of a DLL. */
#define TAG_SDI_CONFIGURATION_MANAGER_STRUCTURE			0xBF918E03		/*!< Constructed tag containing information of the Manager. */
#define TAG_SDI_CONFIGURATION_SYSTEM_STRUCTURE			0xBF918E04		/*!< Constructed tag containing information of the system. */

//! @}

/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


#endif // __SDI_TAGS_H__INCLUDED__
