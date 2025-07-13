/**
 * \file	SDI_Defines.h
 * \brief	Describes the SDI defines.
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

#ifndef __SDI_DEFINES_H__INCLUDED__
#define __SDI_DEFINES_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


//! \addtogroup SDI_ComponentMask
//! @{
#define SDI_SOFT_APPLICATIONS						0x00000001		/*!< Mask indicating the Applications information shall be retrieved. */
#define SDI_SOFT_DRIVERS							0x00000002		/*!< Mask indicating the Drivers information shall be retrieved. */
#define SDI_SOFT_DLL								0x00000004		/*!< Mask indicating the DLLs information shall be retrieved. */
#define SDI_SOFT_MANAGER							0x00000008		/*!< Mask indicating the Manager information shall be retrieved. */
#define SDI_SOFT_SYSTEM								0x00000010		/*!< Mask indicating the System information shall be retrieved. */
//! @}


//! \addtogroup SDI_ReaderState
//! @{
#define SDI_STATE_IDLE								(1)				/*!< Reader is in idle state. */
#define SDI_STATE_APPLICATION_MODE					(2)				/*!< Application processing is currently in progress. */
#define SDI_STATE_SYSTEM							(3)				/*!< System function is currently in progress (SetDate, SetLanguage...). */
//! @}

/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


#endif // __SDI_DEFINES_H__INCLUDED__
