/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

#ifndef _DEL_H_
#define _DEL_H_

/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This routine gives M2OS the list of AID managed by application .
 *  @param aDEL : Address of the DEL to be initialised. 
 *	@return None
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
**/
int EMV_GiveAid( DEL *aDEL ) ;


/*! @brief This routine initialises a DEL.
 *  @param aDEL : Address of the DEL to be initialised. 
 *	@return Always responds 0.
 *  @warning Always call this function before using a DEL.
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
**/
//-------------------------------------------------------------------------
#ifdef _SECDEL_
#define DEL_init	SecDEL_init
int SecDEL_init( DEL *aDEL ) ;
#else
int DEL_init( DEL *aDEL ) ;
#endif
void _DEL_init ( _DEL_ *vDEL );



/*! @brief This routine adds an element to a DEL.
 *  @param aDEL : Address of the DEL where the element shall be added
 *  @param anElement : Pointer on the element to be added.
 *	@return 
 *	-  0  if successful
 *	- -1 if Data Element List is full
 *
 *  @warning
 *	- The element length shall always be set. If the function is used before getting elements initialise length to 0.
 *	- With the first version of the DEL mechanism, this function does not copy the value of the element, but just sets a pointer on the value.  Take care that the value is not corrupted before the DEL is used
 *	- With the second version of the mechanism, there is no risk with this routine.
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
**/
//-------------------------------------------------------------------------
#ifdef _SECDEL_
#define DEL_AddDataElement	SecDEL_AddDataElement
int SecDEL_AddDataElement(DEL *aDEL, const DataElement *anElement ) ;
#else
int DEL_AddDataElement(DEL *aDEL, const DataElement *anElement ) ;
#endif


/*! @brief This routine remove elements in a DEL at index
 *  @param aDEL : Address of the DEL
 *  @param index : 
 *	@return Number of elements in the DEL
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
**/
#ifdef _SECDEL_
#define DEL_RemoveDataElement	SecDEL_RemoveDataElement
int SecDEL_RemoveDataElement(DEL *aDEL,int index) ;
#else
int DEL_RemoveDataElement(DEL *aDEL,int index) ;
#endif


/*! @brief This routine returns a pointer to the first Data Element of a DEL or NULL if DEL is empty
 *  @param aDEL : Address of the DEL consulted
 *	@return 
 *	- NULL in case of a void DEL
 *	- Pointer on the first Data Element of the DEL if successful
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
**/
#ifdef _SECDEL_
#define DEL_GetFirstDataElement	SecDEL_GetFirstDataElement
DataElement * SecDEL_GetFirstDataElement(DEL *aDEL) ;
#else
DataElement * DEL_GetFirstDataElement(DEL *aDEL) ;
#endif



/*! @brief This routine returns a pointer to the next Data Element of a DEL or NULL if the end of the DEL is reached
 *  @param aDEL : Address of the DEL consulted
 *	@return 
 *	- NULL in case the end of the DEL is reached
 *	- Pointer on the Data Element of the DEL if successful
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
**/
#ifdef _SECDEL_
#define DEL_GetNextDataElement	SecDEL_GetNextDataElement
DataElement * SecDEL_GetNextDataElement(DEL *aDEL) ;
#else
DataElement * DEL_GetNextDataElement(DEL *aDEL) ;
#endif



/*! @brief This routine copy the content of one DEL to an other.
 *  @param Source : Address of the input DEL
 *  @param Destination : Address of the output DEL
 *	@return always OK
 *  @warning 
 *  - With the first version of the DEL mechanism, thi function does not copy the value of the element, but just set a pointer on the value.  Take care that the values are not corrupted before the destination DEL is used
 *  - With the second version of the mechanism, there is no risk with this routine.
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
**/
#ifdef _SECDEL_
#define DEL_CopyDEL	SecDEL_CopyDEL
#define DEL_ConcatDEL	SecDEL_ConcatDEL
int SecDEL_CopyDEL(DEL* Source, DEL* Destination);
int SecDEL_ConcatDEL(DEL* Source, DEL* Destination);
void SecDEL_CleanTags(DEL* aDEL);
#else
int DEL_CopyDEL(DEL* Source, DEL* Destination);
int DEL_ConcatDEL(DEL* Source, DEL* Destination);
void DEL_CleanTags(DEL* aDEL);
#endif



/*! @brief This routine returns the number of elements contained in a DEL
 *  @param aDEL : Address of the DEL consulted
 *	@return Number of elements in the DEL
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
**/
#ifdef _SECDEL_
#define DEL_GetCount	SecDEL_GetCount
int SecDEL_GetCount(DEL *aDEL) ;
#else
int DEL_GetCount(DEL *aDEL) ;
#endif
/**
 * function:    DEL_GetDataElement
 * @brief This routine returns a pointer to the Data Element of a DEL or NULL if the end of the DEL is reached
 * @param aDEL : Address of the DEL consulted
 * @param index : number of data element
 * @return NULL in case the end of the DEL is reached
 * @return Pointer on the  Data Element of the DEL if successfull
 */
DataElement * DEL_GetDataElement(DEL *aDEL,int index) ;
#ifdef _SECDEL_
#define DEL_AddToVal	SecDEL_AddToVal
#define DEL_ValToAdd	SecDEL_ValToAdd
void             SecDEL_AddToVal                      (DEL *aDEL, _DEL_ *_vDEL);
void             SecDEL_ValToAdd                      (_DEL_ *_vDEL, DEL *aDEL);
#else
void             DEL_AddToVal                      (DEL *aDEL, _DEL_ *_vDEL);
void             DEL_ValToAdd                      (_DEL_ *_vDEL, DEL *aDEL);
#endif

void            _DEL_init                         (_DEL_ *aDEL);
int             _DEL_AddDataElement               (_DEL_ *aDEL,const DataElement *AnElement);
int             _DEL_GetCount                     (_DEL_ *aDEL);
_DataElement_  *_DEL_GetDataElement               (_DEL_ *aDEL, int index);


#endif
/*! @} **/
