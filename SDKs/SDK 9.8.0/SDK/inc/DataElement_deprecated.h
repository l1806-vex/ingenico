/**
 *! \file        DataElement.h
 * \brief This module manages a data element.
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


#ifndef __DATABASE_ELEMENT_DEPRECATED_H__INCLUDED__
#define __DATABASE_ELEMENT_DEPRECATED_H__INCLUDED__


#ifdef __cplusplus
extern "C" {
#endif


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

/*! \brief Data element NULL position*/
#define ET_POSITION_NULL		(-1)

#define MAX_DATA_ELEMENT	50
#define MAX_ELT_LENGTH		264

//// Types //////////////////////////////////////////////////////
/*typedef struct
{
	unsigned long	tag ;
	unsigned int	length ;
	unsigned char  *ptValue ;
} DataElement;

typedef struct {
	int			current;
	int			count ;
	DataElement list[MAX_DATA_ELEMENT] ;
} DEL ;
*/
/*! \brief Type of a data element tag. */
typedef unsigned long T_ET_TAG;

/*! \brief Type of a data element length. */
typedef unsigned long T_ET_LENGTH;

/*! \brief Type of position in a data element buffer. */
typedef int T_ET_POSITION;

/*! \brief Type of a data element status. */
typedef enum
{
	EtSuccess			= 0,		/*!< Success							*/
	EtNotFound			= 1,		/*!< Tag not found						*/
	EtNotEnoughSpace	= 2,		/*!< Not enough space in the database	*/
	EtProcessingError	= 3,		/*!< Error occurs						*/
	EtInvalidParameter	= 4			/*!< Invalid parameter					*/
} T_ET_STATUS;


/*! \brief Data element structure. */
/* @GSIM_T:T_DATA_ELEMENT:SUPPLIED(SER_DataElt;DSR_DataElt) */
typedef struct
{
	void* m_pBuffer;					/*!< Pointer to the data element buffer. */
	unsigned long m_ulBufferSize;		/*!< Size of the data element buffer. */

//	T_ET_TAG m_Tag;						//!< Tag of the data element.
//	T_ET_LENGTH m_Length;				//!< Length of the data element.
} T_DATA_ELEMENT;

/*! \cond not appears in the doc */
#define T_DATA_ELEMENT_DEFINED
/*! \endcond */

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief Initialise a data element.
 * \brief This function is no more supported. Please use Et_Initialise
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_Init ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_Init(T_DATA_ELEMENT* pDataElement, void* pBuffer, unsigned long ulBufferSize, T_ET_TAG Tag, T_ET_LENGTH Length) MACRO_DEPRECATED ;
#endif

/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Initialise a data element.
 *	@param[in,out]	pDataElement		Data element descriptor.
 *	@param[in,out]	pBuffer				Buffer to store the data element.
 *	@param[in]		ulBufferSize		Size of the buffer \a pBuffer.
 *	@param[in]		Tag					Tag to set.
 *	@param[in]		Length				Length to set.
 *	@return
 *	- \a EtSuccess if the data element is initialized, 
 *	- \a EtInvalidParameter/EtNotEnoughSpace if not.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_Initialise ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_Initialise(T_DATA_ELEMENT* pDataElement, void* pBuffer, unsigned long ulBufferSize, T_ET_TAG Tag, T_ET_LENGTH Length) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Initialise a data element.
 *	@param[in,out]	pDataElement		Data element descriptor.
 *	@param[in,out]	pBuffer				Buffer to store the data element.
 *	@param[in]		ulBufferSize		Size of the buffer \a pBuffer.
 *	@param[in]		Tag					Tag to set.
 *	@param[in]		Length				Length to set.
 *	@param[in]		pValue				Value to set.
 *	@return 
 *	- \a EtSuccess if the data element is initialized, 
 *	- \a EtInvalidParameter/EtNotEnoughSpace if not.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_InitEx ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_InitEx(T_DATA_ELEMENT* pDataElement, void* pBuffer, unsigned long ulBufferSize, T_ET_TAG Tag, T_ET_LENGTH Length, const void* pValue) MACRO_DEPRECATED ;
#endif



/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Retrieve the tag of a data element.
 *	@param[in]		pDataElement		Data element descriptor.
 *	@param[out]		pTag				Tag of the data element \a pDataElement.
 *	@return 
 *	- \a EtSuccess if tag correctly retreived,
 *	- \a EtInvalidParameter/EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_Tag ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_Tag(const T_DATA_ELEMENT* pDataElement, T_ET_TAG* pTag) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Retrieve the length of a data element.
 *	@param[in]		pDataElement		Data element descriptor.
 *	@param[out]		pLength				Length of the data element \a pDataElement.
 *	@return 
 *	- \a EtSuccess if length correctly retreived
 *	- \a EtInvalidParameter/EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_Length ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_Length(const T_DATA_ELEMENT* pDataElement, T_ET_LENGTH* pLength) MACRO_DEPRECATED ;
#endif



/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Retrieve the tag of a data element.
 *	@param[in]		pDataElement		Data element descriptor.
 *	@param[out]		pValue				Value of the data element \a pDataElement.
 *	@return
 *	- \a EtSuccess if value correctly retreived
 *	- \a EtInvalidParameter/EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_Value ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_Value(const T_DATA_ELEMENT* pDataElement, const void** pValue) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Retrieve the buffer where the data element is stored.
 *	@param[in]		pDataElement		Data element descriptor.
 *	@param[out]		pBuffer				Buffer where the data element is stored.
 *	@param[out]		pLength				Length of the buffer \a pBuffer.
 *	@return
 *	- \a EtSuccess buffer correctly got
 *	- \a EtInvalidParameter/EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_GetDataElementBuffer ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_GetDataElementBuffer(const T_DATA_ELEMENT* pDataElement, const void** pBuffer, unsigned long* pLength) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Retrieve the pointer in the buffer for a specified position.
 *	@param[in]		pDataElement		Data element descriptor.
 *	@param[out]		Position			Position of the pointer to get.
 *	@param[out]		pBuffer				Pointer in the buffer for the requested position.
 *	@return
 *	- \a EtSuccess if pointer correctly retrieved
 *	- \a EtInvalidParameter/EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_GetBuffer ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_GetBuffer(const T_DATA_ELEMENT* pDataElement, T_ET_POSITION Position, const void** pBuffer) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Add a tag to a data element.
 *	@param[in,out]	pDataElement		Data element descriptor.
 *	@param[in]		Tag					Tag to add.
 *	@param[in]		Length				Length to add.
 *	@param[in]		pValue				Value to add.
 *	@return 
 *	- \a EtSuccess if the data element is added, 
 *	- \a EtInvalidParameter/EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_Add ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_Add(T_DATA_ELEMENT* pDataElement, T_ET_TAG Tag, T_ET_LENGTH Length, const void* pValue) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Add a data element to another one.
 *	@param[in,out]	pDataElement		Data element descriptor.
 *	@param[in]		pSource				Data element to add.
 *	@return
 *	- \a EtSuccess if the data element is added, 
 *	- \a EtInvalidParameter/EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_AddElement ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_AddElement(T_DATA_ELEMENT* pDataElement, const T_DATA_ELEMENT* pSource) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Modify a tag in a data element.
 *	@param[in,out]	pDataElement		Data element descriptor.
 *	@param[in]		Position			Position of the data element to modify.
 *	@param[in]		Tag					New tag.
 *	@param[in]		Length				New length.
 *	@param[in]		pValue				New value.
 *	@return 
 *	- \a EtSuccess if the data element is modified, 
 *	- \a EtInvalidParameter/EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_ModifyTag ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_ModifyTag(T_DATA_ELEMENT* pDataElement, T_ET_POSITION Position, T_ET_TAG Tag, T_ET_LENGTH Length, const void* pValue) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Retrieve the position of the first tag in a data element.
 *	@param[in]		pDataElement		Data element descriptor.
 *	@param[out]		pPosition			Position of the first tag.
 *	@return 
 *	- \a EtSuccess if the position is retrieved.
 *	- Other value (according to the error).
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_GetFirstPosition ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_GetFirstPosition(const T_DATA_ELEMENT* pDataElement, T_ET_POSITION* pPosition) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Get the next tag in a data element.
 *	@param[in]		pDataElement		Data element descriptor.
 *	@param[in,out]	pPosition			Position of the next tag.
 *	@param[out]		pTag				Tag.
 *	@param[out]		pLength				Length.
 *	@param[out]		pValue				Value.
 *	@return
 *	- \a EtSuccess if an element is found, 
 *	- \a EtNotFound if there is no more element
 *	- \a EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_GetNext ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_GetNext(const T_DATA_ELEMENT* pDataElement, T_ET_POSITION* pPosition, T_ET_TAG* pTag, T_ET_LENGTH* pLength, const void** pValue) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Get the current tag in a data element.
 *	@param[in]		pDataElement		Data element descriptor.
 *	@param[in]		Position			Position of the tag.
 *	@param[out]		pTag				Tag.
 *	@param[out]		pLength				Length.
 *	@param[out]		pValue				Value.
 *	@return 
 *	- \a EtSuccess if an element is found, 
 *	- \a EtNotFound if there is no more element 
 *	- \a EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_GetCurrent ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_GetCurrent(const T_DATA_ELEMENT* pDataElement, T_ET_POSITION Position, T_ET_TAG* pTag, T_ET_LENGTH* pLength, const void** pValue) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Find a tag in a data element.
 *	@param[in]		pDataElement		Data element descriptor.
 *	@param[in,out]	pPosition			Search position.
 *	@param[in]		Tag					Tag to search for.
 *	@param[out]		pLength				Found length.
 *	@param[out]		pValue				Found value.
 *	@param[out]		pTagPosition		Position of the tag if found (may be NULL if no use).
 *	@return 
 *	- \a EtSuccess if an element is found, 
 *	- \a EtNotFound if there is no more element
 *	- \a EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_FindNext ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_FindNext(const T_DATA_ELEMENT* pDataElement, T_ET_POSITION* pPosition, T_ET_TAG Tag, T_ET_LENGTH* pLength, const void** pValue, T_ET_POSITION* pTagPosition) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Search a tag by using a key in a data element.
 *	@param[in]		pDataElement		Data element descriptor.
 *	@param[in,out]	pPosition			Search position.
 *	@param[in]		Tag					Tag to search for.
 *	@param[in]		IndexTag			Tag of the key to match for.
 *	@param[in]		IndexLength			Length of the key to match for.
 *	@param[in]		pIndexValue			Value of the key to match for.
 *	@param[out]		pLength				Found length.
 *	@param[out]		pValue				Found value.
 *	@param[out]		pTagPosition		Position of the tag if found (may be NULL if no use).
 *	@return 
 *	- \a EtSuccess if an element is found, 
 *	- \a EtNotFound if there is no more element
 *	- \a EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_SearchNext ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_SearchNext(const T_DATA_ELEMENT* pDataElement, T_ET_POSITION* pPosition, T_ET_TAG Tag, T_ET_TAG IndexTag, T_ET_LENGTH IndexLength, const void* pIndexValue, T_ET_LENGTH* pLength, const void** pValue, T_ET_POSITION* pTagPosition) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Remove the current tag in a data element.
 *	@param[in,out]	pDataElement		Data element descriptor.
 *	@param[in,out]	pPosition			Position of the data element to remove.
 *	@return 
 *	- \a EtSuccess if the element is removed, 
 *	- \a EtNotFound if there is no more element
 *	- \a EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_RemoveCurrent ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_RemoveCurrent(T_DATA_ELEMENT* pDataElement, T_ET_POSITION* pPosition) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Remove a tag in a data element.
 *	@param[in,out]	pDataElement		Data element descriptor.
 *	@param[in]		Tag					Tag to remove.
 *	@return 
 *	- \a EtSuccess if the element is removed, 
 *	- \a EtNotFound if there is no more element 
 *	- \a EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_RemoveTag ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_RemoveTag(T_DATA_ELEMENT* pDataElement, T_ET_TAG Tag) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Remove all the tags in a data element.
 *	@param[in,out]	pDataElement		Data element descriptor.
 *	@return 
 *	- \a EtSuccess if all the elements are removed
 *	- \a EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_RemoveAll ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_RemoveAll(T_DATA_ELEMENT* pDataElement) MACRO_DEPRECATED ;
#endif


/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Check the consistency of a data element.
 *	@param[in]		pDataElement		Data element descriptor.
 *	@return 
 *	- \a EtSuccess if the data element is correctly formatted
 *	- \a EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_CheckConsistency ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_CheckConsistency(const T_DATA_ELEMENT* pDataElement) MACRO_DEPRECATED ;
#endif


#ifndef _C30_
#ifndef DATA_SET_NO_DEL_CONVERSIONS
// This function allows to add the content of a dataelement in a (standard or secure) DEL (for application intercommuncation)
/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Adds the content of a data element into a DEL structure
 *	@param[in]		pDataElement		Data element containing the data to copy in the DEL.
 *	@param[out]		pDel				DEL with the data.
 *	@param[in]		bSecDel				If Secure DEL are used or not.
 *	@return
 *	- \a EtSuccess if correctly added,
 *	- \a EtNotEnoughSpace if there is not enough space in the DEL,
 *	- \a EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_AddToDel ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_AddToDel(const T_DATA_ELEMENT* pDataElement, DEL* pDel, int bSecDel) MACRO_DEPRECATED ;
#endif

/*! \brief AVL TMS will not be supported in Telium+ framework. This function has been reported as unused in the survey sent to regions.
 * To continue to use this function add _DEPRECATED_AVL_SDK090200_ in you compilation defines.
 * \brief  Adds the content of a DEL structure into a data element.
 *	@param[in,out]	pDataElement		Data element contains data copied from the DEL structure.
 *	@param[in]		pDel				DEL containing the data.
 *	@return
 *	- \a EtSuccess if correctly added,
 *	- \a EtNotEnoughSpace if there is not enough space in the data element \a pDataElement,
 *	- \a EtProcessingError if an error occurs.
 **/
#ifndef _DEPRECATED_AVL_SDK090200_
#define Et_AddDel ERROR_Deprecation_For_Module_AVL_SeeDocumentation_In_CHM_File;
#else
T_ET_STATUS Et_AddDel(T_DATA_ELEMENT * pDataElement, const DEL* pDel) MACRO_DEPRECATED ;
#endif
#endif
#endif


#ifdef __cplusplus
}
#endif

#endif // __DATABASE_ELEMENT_DEPRECATED_H__INCLUDED__
