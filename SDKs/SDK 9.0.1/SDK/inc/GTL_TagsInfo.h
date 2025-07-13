/**
* \file GTL_TagsInfo.h
* \brief This module manages all the tags formats and information.
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

#define TAG_SOURCE_ALL			0xFF			/*!< The tag comes from any source.		*/
#define TAG_SOURCE_TERMINAL		0x01			/*!< The tag comes from the terminal.	*/
#define TAG_SOURCE_ICC			0x02			/*!< The tag comes from the ICC.		*/
#define TAG_SOURCE_ISSUER		0x04			/*!< The tag comes from the issuer.		*/

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

//! @}


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

//! \addtogroup TagsInfoErrors
//! @{

/*! \brief Type of a tag information status. */
typedef enum
{
	TiSuccess					=  0,			/*!< The operation is successful.				*/
	TiNotFound					=  1,			/*!< The tag is not found.						*/
	TiNotEnoughSpace			=  2,			/*!< There is not enough space in the database.	*/
	TiProcessingError			=  3,			/*!< A processing error occured.				*/
	TiInvalidParameter			=  4,			/*!< A parameter is not valid.					*/
	TiInvalidPosition			=  5,			/*!< The position is not valid.					*/
	TiUnknownTag				=  6,			/*!< The tag is unkown.							*/
	TiBadLength					=  7,			/*!< The length is out of range.				*/
	TiBadEncoding				=  8,			/*!< The value is not correctly formatted.		*/
	TiBadTag					=  9,			/*!< The tag is not correct.					*/
	TiBadMask					= 10,			/*!< The mask is not correct.					*/
	TiInternalError				= 11,			/*!< An internal error occured.					*/
	TiBadIndex					= 12,			/*!< The index is not correct.					*/
	TiRedundantTag				= 13			/*!< The tag is redundant.						*/
} T_TI_STATUS;

//! @}

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

/*! \brief Type of a tag mask (indicating tag options). */
typedef struct
{
	unsigned int m_nSource : 8;					/*!< Sourec of the tag (terminal, card or issuer).									*/
	unsigned int m_nValueEncoding : 8;			/*!< Encoding encoding of the value (B, N, CN, ANS, AN, etc).						*/
	unsigned int m_bExclusiveLengths : 1;		/*!< Indicates if min and max length define a range or unique length (min or max).	*/
	unsigned int m_bOneOccurence : 1;			/*!< Boolean that indicates if one or several tag occurences are allowed.			*/
	unsigned int m_nRfu : 14;					/*!< RFU.																			*/
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

//! \addtogroup TagsInfoArrayManagement
//! @{

//! \brief Get the greater index to be managed in a tags definition array.
//! \details This function is used by the \a Data \a Storage module.
//! \param[in] pTagInfoStruct The tags definition array.
//! \param[in] iNbElemTagInfo Number of tags in \a pTagInfoStruct.
//! \return The function returns the <b>greater index</b> to be managed or <b>-1</b> if there is no indexed tag, or if \a pTagInfoStruct is \a NULL and / or \a iNbElemTagInfo is lower than 0.

T_TI_INDEX GTL_TagsInfo_GetMaxIndex (const T_TI_TAG_INFO* pTagInfoStruct, const int iNbElemTagInfo);



//! \brief Get the number of unindexed tags in a tags definition array.
//! \details This function is used by the \a Data \a Storage module.
//! \param[in] pTagInfoStruct The tags definition array.
//! \param[in] iNbElemTagInfo Number of tags in \a pTagInfoStruct.
//! \return The function returns the <b>number of unindexed tags</b> to be managed.

int GTL_TagsInfo_GetNbUnIndexed (const T_TI_TAG_INFO* pTagInfoStruct, const int iNbElemTagInfo);



//! \brief Check that a tags definition array is valid.
//! \details The following checks are performed:
//! - Tags are correctly ordered (for dichotomy),
//! - Min and Max length are coherent,
//! - Indexed tags have one occurence flag set.
//!
//! \param[in] pDbTagInfoStruct The tags definition array.
//! \param[in] iNbElemTagInfo The number of tags in \a pDbTagInfoStruct.
//! \param[out] pErroneousTag The erroneous tag if an error occured during the structure checking. If structure is correct, it is set to 0.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref TiSuccess</td><td>The tags definition array is correct.</td></tr>
//! <tr><td>\ref TiInvalidParameter</td><td>\a pDbTagInfoStruct is \a NULL or \a iNbElemTagInfo is lower or equal to 0.</td></tr>
//! <tr><td>\ref TiBadTag</td><td>The \a pErroneousTag is not correctly ordered.</td></tr>
//! <tr><td>\ref TiBadLength</td><td>The \a pErroneousTag has incoherent lengths.</td></tr>
//! <tr><td>\ref TiBadMask</td><td>The mask of the tag \a pErroneousTag is not valid: indexed tags shall authorise only one occurence.</td></tr>
//! </table>

T_TI_STATUS GTL_TagsInfo_CheckStructure (const T_TI_TAG_INFO * pDbTagInfoStruct, const int iNbElemTagInfo, T_TI_TAG * pErroneousTag);



//! \brief Get the maximum data length for all the indexed tags of a tags definition array.
//! \details This function calculates the size of the buffer neeeded to store the values of all the indexed tags.
//! \details This function is used by the \a Data \a Storage module.
//! \param[in] pTagInfoStruct The tags definition array.
//! \param[in] iNbElemTagInfo Number of tags in \a pTagInfoStruct.
//! \return The function returns the <b>sum of the maximum lengths of the indexed tags</b> or <b>0</b> if \a pTagInfoStruct is \a NULL and / or \a iNbElemTagInfo is lower than 0.

T_TI_LENGTH GTL_TagsInfo_GetAllIndexedDataLength (const T_TI_TAG_INFO * pTagInfoStruct, const int iNbElemTagInfo);

//! @}



//! \addtogroup TagsInfoTagQuery
//! @{

//! \brief Check tag data according to its information.
//! \details This function check checks the \a Tag, the \a Length and the data format of \a pValue according to the information \a pTagInfo.
//! \param[in] pTagInfo Information about the tag.
//! \param[in] Tag Tag to check.
//! \param[in] Length Length of the tag  to check.
//! \param[in] pValue Value of the tag to check (if \a NULL, only \a Tag and \a Length are checked).
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref TiSuccess</td><td>The tag is correct.</td></tr>
//! <tr><td>\ref TiInvalidParameter</td><td>\a pTagInfo is \a NULL.</td></tr>
//! <tr><td>\ref TiBadTag</td><td>The \a Tag is not valid.</td></tr>
//! <tr><td>\ref TiBadLength</td><td>The \a Length is not valid.</td></tr>
//! <tr><td>\ref TiBadEncoding</td><td>\a pValue is not correctly encoded.</td></tr>
//! </table>

T_TI_STATUS GTL_TagsInfo_CheckTag (const T_TI_TAG_INFO * pTagInfo, const T_TI_TAG Tag, const T_TI_LENGTH Length, T_TI_VALUE_C pValue);

//! @}



//! \addtogroup TagsInfoArrayQuery TagsInfo array query
//! @{

//! \brief Retrieve the index of a tag in a tags definition array.
//! \param[in] pTagInfoStruct The tags definition array.
//! \param[in] iNbElemTagInfo Number of tags in \a pTagInfoStruct.
//! \param[in] sRequestedTag The tag to search for.
//! \return The <b>index of the tag</b> within the tags definition array or <b>-1</b> if \a pTagInfoStruct is \a NULL and / or \a iNbElemTagInfo is lower than 0.

T_TI_STRUCT_INDEX GTL_TagsInfo_GetTagInfoIndex (const T_TI_TAG_INFO * pTagInfoStruct, const int iNbElemTagInfo, const T_TI_TAG sRequestedTag);



//! \brief Retrieve the tag information from a tags definition array according to an index.
//! \param[in] pTagInfoStruct The tags definition array.
//! \param[in] iNbElemTagInfo Number of tags in \a pTagInfoStruct.
//! \param[in] sIndex Index of the tag to be retrieved in the tags definition array \a pTagInfoStruct.
//! \param[out] pTagInfo The pointer to tag information. It is set to \a NULL if the tag is not found.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref TiSuccess</td><td>The tag information is found.</td></tr>
//! <tr><td>\ref TiInvalidParameter</td><td>\a pTagInfoStruct is \a NULL, or \a iNbElemTagInfo is lower or equal to 0 or \a pTagInfo is \a NULL.</td></tr>
//! <tr><td>\ref TiBadIndex</td><td>The \a sIndex is out of range.</td></tr>
//! </table>

T_TI_STATUS GTL_TagsInfo_GetTagInfoFromIndex (const T_TI_TAG_INFO * pTagInfoStruct, const int iNbElemTagInfo, const T_TI_STRUCT_INDEX sIndex, const T_TI_TAG_INFO ** pTagInfo);



//! \brief Retrieve the information about a tag from a tags definition array.
//! \param[in] pTagInfoStruct The tags definition array.
//! \param[in] iNbElemTagInfo Number of tags in \a pTagInfoStruct.
//! \param[in] sRequestedTag The tag to search for.
//! \param[out] pTagInfo The pointer to tag information. It is set to \a NULL if the tag is not found.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref TiSuccess</td><td>The tag information is found.</td></tr>
//! <tr><td>\ref TiInvalidParameter</td><td>\a pTagInfoStruct is \a NULL, or \a iNbElemTagInfo is lower or equal to 0 or \a pTagInfo is \a NULL.</td></tr>
//! <tr><td>\ref TiUnknownTag</td><td>The \a sRequestedTag is not found in \a pTagInfoStruct.</td></tr>
//! </table>

T_TI_STATUS GTL_TagsInfo_GetTagInfo (const T_TI_TAG_INFO * pTagInfoStruct, const int iNbElemTagInfo, const T_TI_TAG sRequestedTag, const T_TI_TAG_INFO ** pTagInfo);

//! @}



//! \addtogroup TagsInfoDebug
//! @{

//! \brief Dump the tags definition array using the trace tool.
//! \param[in] txt Presentation text (dump customisation).
//! \param[in] pTagInfoStruct The tags definition array.
//! \param[in] iNbElemTagInfo Number of tags in \a pTagInfoStruct.

void GTL_TagsInfo_DumpStructure (const char * txt, const T_TI_TAG_INFO * pTagInfoStruct, const int iNbElemTagInfo);

//! @}

#endif // __TAGS_INFO_H__INCLUDED__
