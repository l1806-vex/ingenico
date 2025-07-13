/**
 * \file GTL_SharedExchange.h
 * \brief Functions used to manage buffer containing data (for exchanging data between two entities for example). It uses dllmalloc buffer (shared memory).
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

#ifndef __GTL_SHARED_EXCHANGE_H__INCLUDED__
#define __GTL_SHARED_EXCHANGE_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup SharedExchangeStatus
//! @{

#define STATUS_SHARED_EXCHANGE_OK					0		/*!< Indicates processing is correct. */
#define STATUS_SHARED_EXCHANGE_END					1		/*!< Indicates there is no more tag to parse in the TLV buffer. */
#define STATUS_SHARED_EXCHANGE_ERROR				2		/*!< Indicates an internal error occurred. */
#define STATUS_SHARED_EXCHANGE_NOT_ENOUGH_SPACE		3		/*!< Indicates there is not enough space in the buffer to add data (BER-TLV encoding). */

//! @}


//! \addtogroup SharedExchangeDefines
//! @{

#define SHARED_EXCHANGE_POSITION_NULL				(-1)	/*!< NULL position. */

#define C_BUFFER_SHARED								1		/*!< Indicates a shared Buffer. */
#define C_BUFFER_LOCAL								2		/*!< Indicates a local Buffer. */

//! @}


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

//! \addtogroup SharedExchangeStructures
//! @{

//! \brief Type of a shared data structure.
typedef struct
{
	unsigned long ulMaxBufferSize;		/*!< Structure identifier (if necessary). */
	unsigned long ulDataLength;			/*!< Buffer length. */
	unsigned char * nPtrData;			/*!< Data buffer. */
} T_SHARED_DATA_STRUCT;


//! \brief Type of a standard data structure (sent on ServiceCall).
typedef struct
{
	unsigned short usApplicationId;		/*!< Structure identifier (if necessary). */
	unsigned short usServiceId;			/*!< Buffer length. */
	T_SHARED_DATA_STRUCT * pDataStruct;	/*!< Structure containig all the data information. */
} T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT;

//! @}


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup SharedExchangeFunctions
//! @{

//! \brief Initialise the exchange structure with a buffer previously reserved.
//! \param[in,out] pStruct Structure to be used.
//! \param[in] ulMaxBufferSize Maximum size to allocate.
//! \param[in] ulDataSize Size of data in buffer.
//! \param[in] nPtrData Buffer to used as store area.
//! \return 
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_OK</td><td>Structure correctly initialised.</td></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_ERROR</td><td>An internal error occurred.</td></tr>
//! </table>

int GTL_SharedExchange_InitEx(T_SHARED_DATA_STRUCT * pStruct, unsigned long ulMaxBufferSize, unsigned long ulDataSize, unsigned char * nPtrData);



//! \brief Initialise the exchange structure. It allocates memory in the shared memory area.
//! \param[in] nBufferSize Buffer size to allocate.
//! \return 
//!		- Structure address if correctly initialised and allocated.
//!		- NULL if an error occurred (not enough memory).

#define GTL_SharedExchange_InitShared(nBufferSize) GTL_SharedExchange_Init (nBufferSize,C_BUFFER_SHARED)



//! \brief Initialise the exchange structure. It allocates memory in the local memory area.
//! \param[in] nBufferSize Buffer size to allocate.
//! \return 
//!		- Structure address if correctly initialised and allocated.
//!		- NULL if an error occurred (not enough memory).

#define GTL_SharedExchange_InitLocal(nBufferSize) GTL_SharedExchange_Init (nBufferSize,C_BUFFER_LOCAL)



//! \brief Initialise the exchange structure. Allows to allocate SHARED or LOCAL memory area type.
//! \param[in] ulBufferSize Maximum size to allocate.
//! \param[in] nBufferType to precise local or share buffer type.
//! \return 
//!		- Structure address if correctly initialised and allocated.
//!		- NULL if an error occurred (not enough memory).

T_SHARED_DATA_STRUCT * GTL_SharedExchange_Init (unsigned long ulBufferSize, int nBufferType);



//! \brief Deallocate shared memory.
//! \param[in,out] pStruct Structure to be destroyed.

#define GTL_SharedExchange_DestroyShare(pStruct) GTL_SharedExchange_Destroy(pStruct,C_BUFFER_SHARED)



//! \brief Deallocate local memory.
//! \param[in,out] pStruct Structure to be destroyed.

#define GTL_SharedExchange_DestroyLocal(pStruct) GTL_SharedExchange_Destroy(pStruct,C_BUFFER_LOCAL)



//! \brief Deallocate the memory.
//! \param[in,out] pStruct Structure to be destroyed.
//! \param[in] nBufferType to precise local or share buffer type.

void GTL_SharedExchange_Destroy(T_SHARED_DATA_STRUCT * pStruct, int nBufferType);



//! \brief Clear the data structure and set all the buffer to 0.
//! \param[in,out] pStruct Structure to be cleared.

void GTL_SharedExchange_Clear (T_SHARED_DATA_STRUCT * pStruct);



//! \brief Clear the data structure with / without setting the buffer to 0.
//! \param[in,out] pStruct Structure to be cleared.
//! \param[in] bClearBuffer \a TRUE if all the buffer shall be set to 0, \a FALSE if only length needs to be set to 0.

void GTL_SharedExchange_ClearEx (T_SHARED_DATA_STRUCT * pStruct, const unsigned char bClearBuffer);



//! \brief Add a tag in the exchange structure.
//! \param[in,out] pStruct Structure to be used.
//! \param[in] ulTag Tag to be added in the structure.
//! \param[in] ulLength Length of tag to be added.
//! \param[in] pValue Value of the tag to be added.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_OK</td><td>tag correctly added.</td></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_NOT_ENOUGH_SPACE</td><td>There is not enough space in the buffer to add the tag.</td></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_ERROR</td><td>An internal error occurred.</td></tr>
//! </table>

int GTL_SharedExchange_AddTag (T_SHARED_DATA_STRUCT * pStruct, const unsigned long ulTag, const unsigned long ulLength, const unsigned char * pValue);



//! \brief Add a shared exchange buffer content in another shared exchange buffer.
//! \param[out] pDestStruct Destination shared exchange buffer.
//! \param[in] pSourceStruct Source shared exchange buffer.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_OK</td><td>Tag correctly added.</td></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_NOT_ENOUGH_SPACE</td><td>There is not enough space in \a pDestStruct to store \a pSourceStruct content.</td></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_ERROR</td><td>\a pDestStruct or \a pSourceStruct is NULL.</td></tr>
//! </table>

int GTL_SharedExchange_AddSharedBufferContent (T_SHARED_DATA_STRUCT * pDestStruct, T_SHARED_DATA_STRUCT * pSourceStruct);



//! \brief Get next tag in the exchange structure.
//! \param[in,out] pStruct Structure to be used.
//! \param[in,out] pPosition Indicates the position \a pStruct buffer from which next tag is to be founded.
//! \param[out] pReadTag Read tag.
//! \param[out] pReadLength Read length.
//! \param[out] pReadValue Read value.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_OK</td><td>Next tag correctly got.</td></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_END</td><td>There is no more tag to read.</td></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_ERROR</td><td>An internal error occurred.</td></tr>
//! </table>

int GTL_SharedExchange_GetNext (T_SHARED_DATA_STRUCT * pStruct, int * pPosition, unsigned long * pReadTag, unsigned long * pReadLength, const unsigned char ** pReadValue);



//! \brief Get next length and value from a tag in the exchange structure.
//! \param[in,out] pStruct Structure to be used.
//! \param[in,out] pPosition Indicates the position \a pStruct buffer from which next tag is to be founded.
//! \param[in] ulTag Tag to be found.
//! \param[out] pReadLength Read length in relation with tag asked.
//! \param[out] pReadValue Read value in relation with tag asked.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_OK</td><td>Tag is present and correctly got.</td></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_END</td><td>There is no more tag to read.</td></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_ERROR</td><td>An internal error occurred.</td></tr>
//! </table>

int GTL_SharedExchange_FindNext (T_SHARED_DATA_STRUCT * pStruct, int * pPosition, unsigned long ulTag, unsigned long * pReadLength, const unsigned char ** pReadValue);



//! \brief Remove all tag "ulTag" in the The TLV buffer.
//! \param[in,out] pStruct Structure to be used.
//! \param[in] ulTag Tag to remove from buffer (tag may be removed several times) .
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_OK</td><td>Tag was present and has been correctly removed.</td></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_END</td><td>No tag to remove have been found.</td></tr>
//! <tr><td>\ref STATUS_SHARED_EXCHANGE_ERROR</td><td>An internal error occurred.</td></tr>
//! </table>

int GTL_SharedExchange_RemoveTag (T_SHARED_DATA_STRUCT * pStruct, unsigned long ulTag);

//! @}


#endif // __GTL_SHARED_EXCHANGE_H__INCLUDED__
