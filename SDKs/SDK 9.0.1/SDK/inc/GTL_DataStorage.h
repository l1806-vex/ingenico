/**
* \file GTL_DataStorage.h
* \brief This module manages the data storage features.
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

#ifndef __GTL_DATA_STORAGE_H__INCLUDED__
#define __GTL_DATA_STORAGE_H__INCLUDED__

//! \addtogroup DataStorageManagement
//! @{

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

/*! \brief Indicate a non initialised data storage position. */
#define DS_POSITION_NULL			((T_DS_POSITION)-1)


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

/*! \brief Type of a data storage status. */
typedef enum
{
	DsSuccess				=  0,			/*!< The operation is successful.				*/
	DsNotFound				=  1,			/*!< The tag is not found.						*/
	DsNotEnoughSpace		=  2,			/*!< There is not enough space in the database.	*/
	DsProcessingError		=  3,			/*!< A processing error occured.				*/
	DsInvalidParameter		=  4,			/*!< A parameter is not valid.					*/
	DsInvalidPosition		=  5,			/*!< The position is not valid.					*/
	DsUnknownTag			=  6,			/*!< The tag is unkown.							*/
	DsBadLength				=  7,			/*!< The length is out of range.				*/
	DsBadEncoding			=  8,			/*!< The value is not correctly formatted.		*/
	DsBadTag				=  9,			/*!< The tag is not correct.					*/
	DsBadMask				= 10,			/*!< The mask is not correct.					*/
	DsInternalError			= 11,			/*!< An internal error occured.					*/
	DsBadIndex				= 12,			/*!< The index is not correct.					*/
	DsRedundantTag			= 13			/*!< The tag is redundant.						*/
} T_DS_STATUS;


/*! \brief Status of a data storage. */
typedef enum
{
	DsNotInitialised		=  0,			/*!< The data storage is not initialised.	*/
	DsInitialised			=  1,			/*!< The data storage is initialised.		*/
	DsEmpty					=  2			/*!< The data storage is empty.			*/
} T_DS_STORAGE_STATE;


#define DS_CONTROL_MASK_NONE			0x00000000		/*!< No control.													*/
#define DS_CONTROL_MASK_SOURCE			0x00000001		/*!< Control that the tag comes from the correct source.			*/
#define DS_CONTROL_MASK_LENGTH_ONLY		0x00000002		/*!< Control the length of the tag only.							*/
#define DS_CONTROL_MASK_LENGTH_VALUE	0x00000004		/*!< Control the format of the value of the tag and its length too.	*/
#define DS_CONTROL_MASK_REDUNDANCE		0x00000008		/*!< Control if the tag is already present in the database			*/
#define DS_CONTROL_MASK_ALL				0xFFFFFFFF		/*!< All controls.													*/
		

/*! \brief Position inside a data storage. */
typedef int T_DS_POSITION;

/*! \brief Type of position in a data storage buffer. */
typedef unsigned char * T_DS_INDEXED_BUFFER_ADDRESS;

/*! \brief Type of a structure containing all data of an <b>indexed</b> tag. */
typedef struct
{
	T_TI_TAG m_Tag;							/*!< Tag.															*/
	T_TI_LENGTH m_Length;					/*!< Length of the value \a m_PtrData. If 0, the tag is not stored.	*/
	T_TI_VALUE m_PtrData;					/*!< Pointer on the value. If \a NULL, the tag is not stored.		*/
	T_TI_INDEXED_OFFSET m_nBufferOffset;	/*!< Offset of the value in the buffer of indexed tags.				*/
} T_DS_TAG_DATA_INDEXED;


/*! \brief Type of a structure containing all data of a <b>non indexed</b> tag. */
typedef struct
{
	T_TI_TAG m_Tag;							/*!< Tag.												*/
	T_TI_LENGTH m_Length;					/*!< Length of the value \a m_PtrData. If 0, the tag is not stored.	*/
	T_TI_VALUE m_PtrData;					/*!< Pointer on the value. If \a NULL, the tag is not stored.		*/
} T_DS_TAG_DATA_UNINDEXED;


/*! \brief Type of a data storage (database descriptor). */
typedef struct
{
	int	m_DbNbElemTagInfo;								/*!< Number of tags in the tags definition array \a m_DbTagInfo.		*/
	const T_TI_TAG_INFO * m_DbTagInfo;					/*!< Tags definition array information.									*/

	T_DS_STORAGE_STATE m_nIndexedArrayState;			/*!< Status of the indexed tags array \a m_DbStorageIndexed.			*/
	int	m_DbNbElemIndexed;								/*!< Number of entries in the indexed tags array \a m_DbStorageIndexed.	*/
	T_DS_INDEXED_BUFFER_ADDRESS m_IndexedBufferAddress;	/*!< Address of the buffer storing the values of the indexed tags.		*/
	T_DS_TAG_DATA_INDEXED * m_DbStorageIndexed;			/*!< Indexed tags array.												*/

	T_DS_STORAGE_STATE m_nUnIndexedArrayState;			/*!< Status of the non indexed tags array \a m_DbStorageUnIndexed.		*/
	int m_DbNbElemUnIndexed;							/*!< Number of entries in the indexed tags array \a m_DbStorageUnIndexed.	*/
	T_DS_TAG_DATA_UNINDEXED * m_DbStorageUnIndexed;		/*!< Non indexed tags array.												*/
} T_DS_DB_DESC;



/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Initialise and allocate m_DbStorageIndexed and m_DbStorageUnIndexed.
//! \param DbDesc : Database descriptor.
//! \param pTagInfoStruct : Tag information description.
//! \param iNbElemTagInfo : number of elements in \a pDbTagInfo.
//! \param iNbMultipleElems : maximum number of occurences for multiple unindexed elements.
//! \return DsSuccess if allocation correctly performed.
//! \return DsNotEnoughSpace if there is not enough memory to allocate the data.
//! \return DsInvalidParameter if \a DbDesc is NULL or if \a pTagInfoStruct is NULL or \a iNbElemTagInfo is <= 0.
//! \return DsBadLength if tag length information is incorrect in \a pTagInfoStruct.
//! \return DsBadMask if tag options are not correct in \a pTagInfoStruct.
//! \return DsBadTag if tag are not correctly ordered in \a pTagInfoStruct.

T_DS_STATUS GTL_DataStorage_StorageInit (T_DS_DB_DESC * DbDesc, const T_TI_TAG_INFO * pTagInfoStruct, const int iNbElemTagInfo, const int iNbMultipleElems);



//! \brief Destroy a data storage (deallocate memory).
//! \param DbDesc : Database descriptor.
//! \return DsSuccess Always returned.

T_DS_STATUS GTL_DataStorage_StorageDestroy (T_DS_DB_DESC * DbDesc);


//! \brief Erase data from a storage.
//! \param DbDesc : Database descriptor.
//! \return DsSuccess if tags have been erased.
//! \return DsProcessingError if the specified storage has not been previously initialised.

T_DS_STATUS GTL_DataStorage_Clear (T_DS_DB_DESC * DbDesc);


//! \brief Find tag index in the storage TagInfo.
//! \param DbDesc : Database descriptor.
//! \param Tag : Tag to get information.
//! \return -1 if tag is not found in the \a DbDesc TagInfo.
//! \return the index in the \a DbDesc TagInfo else.

T_TI_STRUCT_INDEX GTL_DataStorage_GetTagInfoIndex (const T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag);



//! \brief Return tag informations according at the provided index in TagInfo.
//! \param DbDesc : Database descriptor.
//! \param nIndex : tag position to access.
//! \return NULL if \a DbDesc is NULL or if \a nIndex is out of range.
//! \return A pointer on tag descriptor.

const T_TI_TAG_INFO * GTL_DataStorage_GetTagInfoFromIndex (const T_DS_DB_DESC * DbDesc, const T_TI_STRUCT_INDEX nIndex);



//! \brief Return tag information from a data storage.
//! \param DbDesc : Database descriptor.
//! \param Tag : tag value to access.
//! \return NULL if \a DbDesc is NULL.
//! \return A pointer on tag descriptor.

const T_TI_TAG_INFO * GTL_DataStorage_GetTagInfo (const T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag);



//! \brief Add a tag (tag + length + value) in a data storage with index direct access.
//! \param DbDesc : Database descriptor.
//! \param Tag : tag to add.
//! \param length : data length.
//! \param pValue: tag data.
//! \param nIndex : tag index to access.
//! \return DsSuccess if the tag has been correctly added.
//! \return DsInvalidParameter if DbDesc=NULL, pValue=NULL.
//! \return DsBadTag if provided tag is not correct (0 or different from th eone described at \a nIndex).
//! \return DsBadIndex if provided index is not correct.
//! \return DsProcessingError if data structures for storage have not been created.

T_DS_STATUS GTL_DataStorage_AddTagWithIndex (T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag, const T_TI_LENGTH length, T_TI_VALUE_C pValue, const T_TI_INDEX nIndex);



//! \brief Add a tag (in data storage) that is not included in array descriptor.
//! \param DbDesc : Database descriptor.
//! \param Tag : tag value to add.
//! \param length : data length.
//! \param pValue : tag data.
//! \param pTagInfo : information about the tag to be added. If NULL, this function will automatically try to get info.
//! \return DsSuccess if the tag has been correctly added.
//! \return DsNotEnoughSpace if there is not enough space to add the tag.
//! \return DsInvalidParameter if \a DbDesc=NULL or \a pValue=NULL.
//! \return DsProcessingError if data structures for storage have not been created.

T_DS_STATUS GTL_DataStorage_AddTagUnIndexed (T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag, const T_TI_LENGTH length, T_TI_VALUE_C pValue, const T_TI_TAG_INFO * pTagInfo);



//! \brief Add a tag in a data storage with no check.
//! \param DbDesc : Database descriptor.
//! \param Tag : tag to add.
//! \param length : data length.
//! \param pValue : tag data.
//! \return DsSuccess if the tag has been correctly added.
//! \return DsNotEnoughSpace if there is not enough space to add the tag.
//! \return DsInvalidParameter if \a DbDesc=NULL or \a pValue=NULL.
//! \return DsBadLength if provided length is not correct.
//! \return DsBadTag if provided tag is not correct (set to 0 for example).
//! \return DsBadMask if provided mask is not correct.

#define GTL_DataStorage_AddTag(DbDesc,Tag,length,pValue)		GTL_DataStorage_AddTagCtrl(DbDesc,Tag,length,pValue,DS_CONTROL_MASK_NONE,0)



//! \brief Add a tag in a data storage and check it.
//! \param DbDesc : Database descriptor.
//! \param Tag : tag value to add.
//! \param length : data length.
//! \param pValue : tag data.
//! \return DsSuccess if the tag has been correctly added.
//! \return DsNotEnoughSpace if there is not enough space to add the tag.
//! \return DsInvalidParameter if \a DbDesc=NULL or \a pValue=NULL.
//! \return DsBadLength if provided length is not correct.
//! \return DsBadTag if provided tag is not correct (set to 0 for example).
//! \return DsBadMask if the provided mask is not correct.

#define GTL_DataStorage_AddTagEx(DbDesc,Tag,length,pValue)	GTL_DataStorage_AddTagCtrl(DbDesc,Tag,length,pValue,DS_CONTROL_MASK_LENGTH_VALUE,0xff)



//! \brief Add a tag in database and has capability check tag value and mask information.
//! \param DbDesc : Database descriptor.
//! \param Tag : tag to add.
//! \param length : data length.
//! \param pValue : tag data.
//! \param ulControlMask : control to make (mask built using DS_CONTROL_MASK_XXXX).
//! \param nSource : source to check.
//! \return DsSuccess if the tag has been correctly added.
//! \return DsNotEnoughSpace if there is not enough space to add the tag.
//! \return DsInvalidParameter if \a DbDesc=NULL or \a pValue=NULL.
//! \return DsBadLength if provided length is not correct.
//! \return DsBadTag if provided tag is not correct (set to 0 for example).
//! \return DsBadMask if the provided mask is not correct.
//! \return DsProcessingError if data structure to store data are not initialised.
//! \return DsUnknowTag if tag is not described in the data storage.
//! \return DsRedundantTag if the tag is redundant (and redundance checking has been requested).

T_DS_STATUS GTL_DataStorage_AddTagCtrl (T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag, const T_TI_LENGTH length, T_TI_VALUE_C pValue, const unsigned long ulControlMask, const unsigned int nSource);



//! \brief Remove a tag from a data storage with index access.
//! \param DbDesc : Database descriptor.
//! \param Tag : tag to remove.
//! \param nIndex : tag index for direct access.
//! \return DsSuccess if the tag has been correctly removed.
//! \return DsInvalidParameter if \a DbDesc=NULL or \a nIndex out of range.
//! \return DsProcessingError if data storage is not correctly initialised.
//! \return DsBadTag if provided tag is not correct (0 or different from th eone described at \a nIndex).
//! \return DsNotFound if tag to be removed is not found.
//! \return DsBadIndex if provided index is not correct.

T_DS_STATUS GTL_DataStorage_RemoveTagWithIndex (T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag, const T_TI_INDEX nIndex);



//! \brief Remove all tags with mask value from data storage.
//! \param DbDesc : Database descriptor.
//! \param l_Mask : tag's mask to remove.
//! \return DsSuccess if tags matching the mask have been correctly removed.
//! \return DsInvalidParameter if \a DbDesc=NULL or \a nIndex out of range.
//! \return DsBadMask if the provided mask is not correct.

T_DS_STATUS GTL_DataStorage_RemoveTagSubset (T_DS_DB_DESC * DbDesc, const T_TI_TAG_INFO_OPTIONS l_Mask);



//! \brief Remove a tag from data storage (tag not included in array descriptor).
//! \param DbDesc : Database descriptor.
//! \param Tag : tag to remove.
//! \param pTagInfo : information about the tag to be removed. If NULL, this function will automatically try to get info.
//! \return DsSuccess if the tag has been correctly removed.
//! \return DsInvalidParameter if \a DbDesc=NULL.
//! \return DsBadTag if provided tag is not correct (0).
//! \return DsProcessingError if data storage is not correctly initialised.
//! \return DsNotFound if tag to be removed is not found.

T_DS_STATUS GTL_DataStorage_RemoveTagUnIndexed (T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag, const T_TI_TAG_INFO * pTagInfo);



//! \brief Remove a tag from data storage (general function).
//! \param DbDesc : Database descriptor.
//! \param Tag : tag to remove.
//! \return DsSuccess if the tag has been correctly removed.
//! \return DbNotFound if the tag is described in this storage but is not present.
//! \return DsInvalidParameter if \a DbDesc=NULL.
//! \return DsBadTag if provided tag is not correct (0).
//! \return DsProcessingError if another error occurs.
//! \return DsUnknownTag if tag is not described in this storage.

T_DS_STATUS GTL_DataStorage_RemoveTag (T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag);



//! \brief Read a tag from a data storage with direct index access.
//! \param DbDesc : Database descriptor.
//! \param Tag : tag value to read.
//! \param pLength : tag length.
//! \param pValue : pointer on data buffer.
//! \param nIndex : tag index to read.
//! \return DsSuccess if the tag has been correctly removed.
//! \return DsNotFound if the requested tag is not in the data storage.
//! \return DsInvalidParameter if \a DbDesc=NULL.
//! \return DsBadTag if provided tag is not correct (0) or is different from the one described at \a nIndex.
//! \return DsProcessingError if another error occurs.

T_DS_STATUS GTL_DataStorage_GetTagWithIndex (const T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag, T_TI_LENGTH * pLength, T_TI_VALUE * pValue, const T_TI_INDEX nIndex);



//! \brief Read a tag from database (Tag not included in array descriptor).
//! \param DbDesc : Database descriptor.
//! \param Tag : tag to read.
//! \param pLength: tag length.
//! \param pValue : pointer on data buffer.
//! \return DsSuccess if the tag has been correctly removed.
//! \return DsNotFound if the requested tag is not in the data storage.
//! \return DsInvalidParameter if \a DbDesc=NULL.
//! \return DsBadTag if provided tag is not correct (0) or is different from the one described at \a nIndex.
//! \return DsUnknownTag if the requested tag is unknown in the data storage.
//! \return DsProcessingError if another error occurs.

T_DS_STATUS GTL_DataStorage_GetTagUnIndexed (const T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag, T_TI_LENGTH * pLength, T_TI_VALUE * pValue);



//! \brief Read a tag from a data storage.
//! \param DbDesc : Database descriptor.
//! \param Tag : tag value to read.
//! \param pLength: tag length.
//! \param pValue : pointer on buffer to update with tag datas.
//! \return DsSuccess if the tag has been correctly removed.
//! \return DsNotFound if the requested tag is not in the data storage.
//! \return DsInvalidParameter if \a DbDesc=NULL.
//! \return DsBadTag if provided tag is not correct (0) or is different from the one described at \a nIndex.
//! \return DsUnknownTag if the requested tag is unknown in the data storage.
//! \return DsProcessingError if another error occurs.

T_DS_STATUS GTL_DataStorage_GetTag (const T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag, T_TI_LENGTH * pLength, T_TI_VALUE * pValue);



//! \brief Check if a tag is present in the data storage.
//! \param DbDesc : Database descriptor.
//! \param Tag : tag to check presence.
//! \return DsSuccess if the tag is present.
//! \return DsNotFound if the tag is described in this data storage but is not present.
//! \return DsInvalidParameter if \a DbDesc=NULL.
//! \return DsBadTag if provided tag is not correct (0).
//! \return DsUnknownTag if the requested tag is unknown in the data storage (not described).

T_DS_STATUS GTL_DataStorage_IsTagPresent (const T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag);



//! \brief Get the next tag in a data storage according to a given position.
//! \param DbDesc : Database descriptor.
//! \param pPosition : current index of tag.
//! \param pTag : tag value.
//! \param pLength : tag length.
//! \param pValue : tag data.
//! \return DsSuccess if the next tag in the data storage is provided.
//! \return DsNotFound if there is no more tags in the storage.
//! \return DsInvalidParameter if \a DbDesc=NULL.

T_DS_STATUS GTL_DataStorage_GetNext (const T_DS_DB_DESC * DbDesc, T_DS_POSITION * pPosition, T_TI_TAG * pTag, T_TI_LENGTH * pLength, T_TI_VALUE * pValue);



//! \brief Get next tag occurence in a data storage.
//! \param DbDesc : Database descriptor.
//! \param pPosition : Current index of tag.
//! \param Tag : tag value.
//! \param pLength : tag length.
//! \param pValue : tag data.
//! \return DsSuccess if the next tag in the data storage is provided.
//! \return DsNotFound if there is no more tags in the storage.
//! \return DsInvalidParameter if \a DbDesc=NULL.

T_DS_STATUS GTL_DataStorage_FindNext (const T_DS_DB_DESC * DbDesc, T_DS_POSITION * pPosition, const T_TI_TAG Tag, T_TI_LENGTH * pLength, T_TI_VALUE * pValue);



//! \brief Check tag coherence (length, value encoding, etc).
//! \param DbDesc : database descriptor.
//! \param Tag : tag to check.
//! \param Length : tag length to check.
//! \param pValue : tag data to check.
//! \return DsSuccess if tag is correct.
//! \return DsInvalidParameter if \a Tag is different from provided tag information or if \a pTagInfo is NULL.
//! \return DsBadTag if the tag is incorrect (set to 0).
//! \return DsBadLength if \a Length is out of range (according to tag information).
//! \return DsBadEncoding if \a pValue is not correctly formatted.
//! \return DsUnknownTag if the requested tag is unknown in the data storage (not described).

T_DS_STATUS GTL_DataStorage_CheckTag (const T_DS_DB_DESC * DbDesc, const T_TI_TAG Tag, const T_TI_LENGTH Length, T_TI_VALUE_C pValue);



//! \brief  Dump the data storage structure content using the trace tool
//! \param txt Presentation text (dump customisation).
//! \param DbDesc Data storage structure to be dumped.

void GTL_DataStorage_DumpStructure (const char * txt, const T_DS_DB_DESC * DbDesc);

//! @}

#endif // __GTL_DATA_STORAGE_H__INCLUDED__
