/**
 *! \file        Common.h
 * \brief General definitions.
 *
 *
 * \author SAGEM MONETEL
 * \author Copyright (c) 2006 Sagem Monetel SA, rue claude Chappe,\n
 *		   07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Sagem Monetel SA has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Sagem Monetel.
 **/

#ifndef __COMMON_H__INCLUDED__
#define __COMMON_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

/*! \hideinitializer
 *	\brief Suppress the warning because of a not used parameter.
 *	@param[in] Param Name of the parameter.
 **/
#define UNREFERENCED_PARAMETER(Param)			((void)Param)

/*! \brief Retreive the offset, in bytes, of the field \a m_Field in the structure \a T_TYPE.
 *	@param[in] T_TYPE Type of the structure.
 *	@param[in] m_Field Name of the field.
 **/
#define STRUCT_OFFSET(T_TYPE, m_Field)			((unsigned int)(&((T_TYPE*)NULL)->m_Field))

/*! \brief Retreive the length, in bytes, of the field \a m_Field in the structure \a T_TYPE.
 *	@param[in] T_TYPE Type of the structure.
 *	@param[in] m_Field Name of the field.
 **/
#define STRUCT_FIELD_SIZE(T_TYPE, m_Field)		(sizeof(((T_TYPE*)NULL)->m_Field))

/*! \brief Retreive the number of items of an array.
 *	@param[in] Array Concerned array.
 **/
#define NUMBER_OF_ITEMS(Array)					(sizeof(Array)/sizeof((Array)[0]))

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

#endif // __COMMON_H__INCLUDED__
