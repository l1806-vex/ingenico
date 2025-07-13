/**
* \file GTL_TagsInfo.h
* \brief Contains all the necessary defines on tags information.
*
*
* \author Ingenico
* \author Copyright (c) 2009 Ingenico, 1 rue claude Chappe,\n
*		   07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author	Ingenico has intellectual property rights relating to the technology embodied\n
*			in this software. In particular, and without limitation, these intellectual property rights may\n
*			include one or more patents.\n
*			This software is distributed under licenses restricting its use, copying, distribution, and\n
*			and decompilation. No part of this software may be reproduced in any form by any means\n
*			without prior written authorization of Sagem Monetel.
**/

#ifndef __TAGS_INFO_H__INCLUDED__
#define __TAGS_INFO_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup TagsInfoSources
//! @{

#define TAG_SOURCE_ALL				0xFF			/*!< The tag comes from any source.							*/
#define TAG_SOURCE_TERMINAL			0x01			/*!< The tag comes from the terminal.						*/
#define TAG_SOURCE_ICC				0x02			/*!< The tag comes from the ICC.							*/
#define TAG_SOURCE_ISSUER			0x04			/*!< The tag comes from the issuer.							*/
#define TAG_SOURCE_PROPRIETARY_1	0x80			/*!< This bit can be used to identify a propietary sources. */

//! @}

//! \addtogroup TagsInfoEncoding
//! @{

#define TAG_FORMAT_B			0x01			/*!< Binary format.						*/
#define TAG_FORMAT_CB			0x02			/*!< Compressed binary.					*/
#define TAG_FORMAT_A			0x03			/*!< Alpha format.						*/
#define TAG_FORMAT_AN			0x04			/*!< Alpha numeric format.				*/
#define TAG_FORMAT_ANS			0x05			/*!< Alpha numeric special format.		*/
#define TAG_FORMAT_ANP			0x06			/*!< Alpha numeric and space format.	*/
#define TAG_FORMAT_N			0x07			/*!< Numeric format.					*/
#define TAG_FORMAT_CN			0x08			/*!< Compressed numeric format.			*/

//! @}

//! \addtogroup TagsInfoOptions
//! @{

#define INDEX_NONE				(-1)			/*!< Indicates tag is not indexed. */

#define LENGTH_EXCLUSIVE		1				/*!< Indicates tag length is exclusive (min or max). */
#define LENGTH_RANGE			0				/*!< Indicates a length range (in [min,max]). */

#define OCCURENCE_SINGLE		1				/*!< Indicates tag has only one occurence in the data storage. */
#define OCCURENCE_MULTIPLE		0				/*!< Indicates tag can have several occurences in the data storage. */

#define EMPTY_TAG_ALLOWED		1				/*!< Indicates a tag can be empty. */
#define EMPTY_TAG_NOT_ALLOWED	0				/*!< Indicates a tag cannot be empty. */

//! @}

//! \addtogroup TagsInfoOptionsRfuMask
//! @{

#define TI_OPTIONS_RFU_MASK_EMPTY_TAG_ALLOWED	    (0x00000001)	/*!< Mask on the RFU bit field in the tag information options. */

//! @}

//! \addtogroup TagsInfoFlagMasks
//! @{

#define TI_FLAGS_EMPTY_MASK						(0x00000001)	/*!< Mask for tag presence checking. */

//! @}


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

//! \addtogroup TagsInfoTypes
//! @{

/*! \brief Type of a data element tag. */
typedef unsigned long T_TI_TAG;

/*! \brief Type of a data element length. */
typedef unsigned long T_TI_LENGTH;

/*! \brief Type of a data element template. */
typedef unsigned long T_TI_TEMPLATE;

/*! \brief Type of a value (read / write). */
typedef unsigned char * T_TI_VALUE;

/*! \brief Type of a value (read only). */
typedef const unsigned char * T_TI_VALUE_C;

/*! \brief Type of a value (read only). */
typedef unsigned long T_TI_INDEXED_OFFSET;

/*! \brief Type of a tag index (if tag is indexed). */
typedef int T_TI_INDEX;

/*! \brief Type of an index in the tags definition array structure. */
typedef int T_TI_STRUCT_INDEX;

/*! \brief Type of flags for a given tag.*/
typedef unsigned long T_TI_FLAGS;


/*! \brief Type of a tag mask (indicating tag options). */
typedef struct
{
	unsigned int m_nSource : 8;					/*!< Sourec of the tag (terminal, card or issuer).									*/
	unsigned int m_nValueEncoding : 8;			/*!< Encoding encoding of the value (B, N, CN, ANS, AN, etc).						*/
	unsigned int m_bExclusiveLengths : 1;		/*!< Indicates if min and max length define a range or unique length (min or max).	*/
	unsigned int m_bOneOccurence : 1;			/*!< Boolean that indicates if one or several tag occurences are allowed.			*/
	unsigned int m_nRfu : 14;					/*!< RFU :<br>- Bit 1 : indicates the tag can be present with a zero length (empty).*/
} T_TI_TAG_INFO_OPTIONS;


/*! \brief Type of a tag information. */
typedef struct
{
	T_TI_TAG				m_Tag;				/*!< Tag definition.							*/
	T_TI_LENGTH				m_nMinLength;		/*!< Minimum lentgh of the value.				*/
	T_TI_LENGTH				m_nMaxLength;		/*!< Maximum lentgh of the value.				*/
	T_TI_TAG_INFO_OPTIONS	m_nTagOptions;		/*!< Tag options.								*/
	T_TI_TEMPLATE			m_nTemplate;		/*!< Template in which the tag can be present.	*/
	T_TI_INDEX				m_nTagIndex;		/*!< Tag index for the array (only if tag have one occurence possible, else 0). */
} T_TI_TAG_INFO;

//! @}


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////



#endif // __TAGS_INFO_H__INCLUDED__
