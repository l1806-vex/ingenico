
#ifndef __TLV_TREE_INCLUDED_H__

#define __TLV_TREE_INCLUDED_H__


#ifdef __cplusplus
extern "C"
{
#endif

/*! @addtogroup DOC_TLVTREE
 * 
 * @link DOC_TLVTREE Back to top @endlink
 * @{ **/


#ifndef __TLV_TREE_NODE__
#define __TLV_TREE_NODE__

/*! @brief Definition of TLV_TREE_NODE. */
typedef int * TLV_TREE_NODE;

#endif

/*
======================================================================
					List of Defines		 
======================================================================
*/

// Serialization method.

#define TLV_TREE_SERIALIZER_DEFAULT					0						/*!<  Default binary serialization method. **/
#define TLV_TREE_SERIALIZER_XML             1						/*!<  Serialization method converting a TLV Tree in an XML formatted buffer. **/

#define TLV_TREE_OK                         0						/*!<  Successful function return. **/
#define TLV_TREE_ERROR_INVALID_SERIALIZER   -1000				/*!<  The serialization method is not supported. **/
#define TLV_TREE_ERROR_BUFFER_TOO_SMALL			-1001      	/*!<  The allocated size of the buffer @a pucBuffer is too small to store the encoded serialization result. **/
#define TLV_TREE_ERROR_INVALID_TREE					-1002				/*!<  The tree structure is invalid to be encoded according to the serialization method. **/
#define TLV_TREE_ERROR_INVALID_BUFFER				-1003			  /*!< Unable to deserialize due to a problem in the buffer or in its size */	
#define TLV_TREE_ERROR_MEMORY								-1004				/*!<  Not enough memory. **/
#define TLV_TREE_ERROR_INVALID_SIZE					-1005				/*!<  Invalid data size. **/
#define TLV_TREE_ERROR_INVALID_OPERATION		-1006				/*!<  The node @a hChild is not a root node or the node @a hParent belongs to the same branch of the node @a hChild **/

/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @name Constructor 

 * @{ **/

// Function: TlvTree_New

/*! @brief This function creates a new TLV tree containing a root node with the tag @a nTag.
 * @param nTag Tag of the root node
 * @return 
 *  - The newly created tree; or 
 *  - @c NULL in case of error.
 *  @note The tree is allocated in the dynamic memory. It must be released at the end using the destructor function \ref TlvTree_Release.
 *  
 *  @link DOC_TLVTREE Back to top @endlink **/
 
      TLV_TREE_NODE TlvTree_New( unsigned int nTag );
      
/*! @} 

 * @name Node Creation
 * @brief The following functions allow adding new nodes into the tree:
 * @{ **/
 	
// Function: TlvTree_AddChild

/*! @brief This function adds a child node to an existing parent node @a hParent. 
 *  @brief The newly created node is inserted at the end in child list of the @a hParent node. If the @a hParent is set to @c NULL, it creates a new node.
 *  @param  hParent Parent node
 *  @param  nTag Node tag
 *  @param  pData Pointer on the buffer containing the binary data of the node
 *  @param  nSize Data size. For the integer values, this size must be 1, 2, 3 or 4 bytes
 *  @return Non-NULL value in case of success
 *  @note It is possible to create a node with no data setting the parameters @a pData to @c NULL or @a nSize to 0.
 *  
 *  @link DOC_TLVTREE Back to top @endlink **/

      TLV_TREE_NODE TlvTree_AddChild( TLV_TREE_NODE hParent, unsigned int nTag, 
								const void *pData, unsigned int nSize );

// Function: TlvTree_AddChildInteger

/*! @brief This function adds a child node to an existing parent node @a hParent. 
 *  @brief The newly created node is inserted at the end in child list of the @a hParent node. If the @a hParent is set to @c NULL, it creates a new node. The data type is an integer (1, 2 or 4 bytes).
 *  @param  hParent Parent node
 *  @param  nTag Node tag
 *  @param  nValue Integer value of the node
 *  @param  nSize Data size. For the integer values, this size must be 1, 2, 3 or 4 bytes
 *  @return Non-NULL value in case of success
 *  @note It is possible to create a node with no data setting the parameter @a nSize to 0.
 *  
 *  @link DOC_TLVTREE Back to top @endlink **/

      TLV_TREE_NODE TlvTree_AddChildInteger( TLV_TREE_NODE hParent, unsigned int nTag,
								       unsigned int nValue, unsigned int nSize );

// Function: TlvTree_AddChildString

/*! @brief This function adds a child node to an existing parent node @a hParent. @brief The newly created node is inserted at the end in child list of the @a hParent node. If the @a hParent is set to @c NULL, it creates a new  node. The data type is a @c NULL terminated string. The data length is automatically calculated.
 *  @param  hParent Parent node
 *  @param  nTag Node tag
 *  @param  szString @c NULL terminated string - value of the node
 *  @return Non-NULL value in case of success      
 *  
 *  @link DOC_TLVTREE Back to top @endlink **/
 
      TLV_TREE_NODE TlvTree_AddChildString( TLV_TREE_NODE hParent, unsigned int nTag, const char *szString );

/*! @} 

 * @name Tree Graft
 * @{ **/

// Function: TlvTree_Graft

/*! @brief This function grafts a whole tree @a hChild onto the node @a hParent. 
 *  @brief The node @a hChild is added at the end to the child list of the @a hParent node.
 *  @param  hParent Parent node
 *  @param  hChild Tree to graft on the parent node
 *  @return 
 *  - #TLV_TREE_OK; or
 *  - #TLV_TREE_ERROR_INVALID_OPERATION
 *  @note The node @a hChild must be a root node (e.g. it is not a child of an other node). The node @a hParent must not belong to the same branch as the node @a hChild.
 *  
 *  @link DOC_TLVTREE Back to top @endlink **/

     int TlvTree_Graft( TLV_TREE_NODE hParent, TLV_TREE_NODE hChild );

/*! @} 
 * @name Destructor
 * @{ **/

// Function: TlvTree_Release

/*! @brief This function deletes a TLV tree. 
 *  @brief All the dynamic memory allocated for the tree, for its nodes and for all its contained data is released. This function can also be used to delete a branch of a tree.
 *  @param hNode TLV tree to delete
 *  @return None
 *  
 *  @link DOC_TLVTREE Back to top @endlink **/
 
      void TlvTree_Release( TLV_TREE_NODE hNode );



	  /*! @} **/



/* * @name Serializers
 *  The following serialization methods (called serializers) are supported:
 *  - #TLV_TREE_SERIALIZER_DEFAULT	
 *  - #TLV_TREE_SERIALIZER_XML	
 *  @{ **/


// Function: TlvTree_Serialize


/*! @brief This function serializes a TLV tree in a buffer.
 *  @brief The serialization method is given by the parameter @a nSerializer. 
 *  @param  hNode Tree node.
 *  @param  nSerializer Serialization method.
 *  @param  pucBuffer Serialization buffer. It receives the result  encoded according to the serialization method.
 *  @param  nSize Allocated size of the serialization buffer.
 *  @return
 *  - The size of the serialized or encoded buffer in case of success; or
 *  - #TLV_TREE_ERROR_BUFFER_TOO_SMALL; or
 *  - #TLV_TREE_ERROR_INVALID_SERIALIZER; or
 *  - #TLV_TREE_ERROR_INVALID_TREE
 *  @note The result buffer must be allocated by the caller. The size of this buffer is dependent of the serialization method. To calculate this size, the caller can request the function \ref TlvTree_GetSerializationSize.
 *  
 *  @link DOC_TLVTREE Back to top @endlink   **/   

      int TlvTree_Serialize( const TLV_TREE_NODE hNode, unsigned int nSerializer, unsigned char *pucBuffer, unsigned int nSize );

// Function: TlvTree_GetSerializationSize

/*! @brief This function calculates the size of a buffer (in bytes) needed to store of the serialization buffer of the TLV tree. 
 *  @brief It is useful to know the size to allocate a buffer before the serialization.  
 *  @param  hNode Tree node.
 *  @param  nSerializer Serialization method.
 *  @return
 *  - The size of a TLV tree encoded according to the serialization method in case of success; or
 *  - #TLV_TREE_ERROR_INVALID_SERIALIZER; or
 *  - #TLV_TREE_ERROR_INVALID_TREE
 *  @par Example:

 * @include TlvTree_Sample_01.c
 * 
 * @link DOC_TLVTREE Back to top @endlink      **/

			int TlvTree_GetSerializationSize( const TLV_TREE_NODE hNode, unsigned int nSerializer );


// Function: TlvTree_Unserialize

/*! @brief This function creates a TLV tree from a serialized buffer.  
 *  @param  hNode Output parameter receiving the unserialized TLV tree.
 *  @param  nSerializer Serialization method.
 *  @param  pucBuffer Buffer containing the serialized TLV tree.
 *  @param  nBufferSize Size of the serialized buffer.
 *  @return
 *  - #TLV_TREE_OK; or
 *  - #TLV_TREE_ERROR_INVALID_SERIALIZER; or
 *  - #TLV_TREE_ERROR_INVALID_BUFFER; or
 *  - #TLV_TREE_ERROR_INVALID_TREE
 *  @note This function is a constructor creating the tree, allocated in the dynamic memory. It must be released at the end using the destructor function \ref TlvTree_Release.
 *  
 *  @link DOC_TLVTREE Back to top @endlink **/

			int TlvTree_Unserialize( TLV_TREE_NODE *hNode, unsigned int nSerializer,
						 const unsigned char *pucBuffer, unsigned int nBufferSize );

/*! @} 

 * @name Tree Browsing
 *  Browsing methods, access sequentially the nodes and  search for a given tag
 *  @{ **/

// Function: TlvTree_Find

/*! @brief This function searches nodes by their tags.
 *  @brief The search is operated only in the branch of the node @a hNode. As it is possible to have several nodes with the same tag, the @a nIndex indicates  the node to get; @a nIndex = 0 returns the first found node, @a nIndex = 1 returns the second node. 
 *  @param  hNode Tree node.
 *  @param  nTag Node tag to search.
 *  @param  nIndex Node index.
 *  @return 
 *  - A pointer on the node searched by its tag; or
 *  - @c NULL when no node has been found.
 *  @note The iteration order is not determined. The function only guarantees that all the nodes with the tag @a nTag will be returned incrementing the index @a nIndex.
 *  @par Example:

 * @include TlvTree_Sample_02.c
 *  
 *  @link DOC_TLVTREE Back to top @endlink **/
 
			TLV_TREE_NODE TlvTree_Find( const TLV_TREE_NODE hNode, unsigned int nTag, unsigned int nIndex );

/*! @} 

 * @name Node Accessors
 *  Functions to get the attributes of a nodes: tag, data size and data
 *  @{ **/


//  Function: TlvTree_Iterate

/*! @brief This function allows to iterate on all the nodes contained in a tree. 
 *  @brief The iteration is operated only in the branch of the node @a hRootNode.
 *  @param  hNode Tree node.
 *  @param  hRootNode Root node defining the branch where the iteration is processed.
 *  @return 
 *  - A pointer on the next node; or 
 *  - @c NULL when the iteration ends.
 *  @note The iteration order is not determined. The function only guarantees that all the nodes with the tag @a nTag will be returned incrementing the index @a nIndex.
 *  @par Example:

 * @include TlvTree_Sample_03.c
 * 
 * @link DOC_TLVTREE Back to top @endlink **/

TLV_TREE_NODE TlvTree_Iterate( const TLV_TREE_NODE hNode, const TLV_TREE_NODE hRootNode );

// Function: TlvTree_GetFirstChild

/*! @brief This function returns the first child of a node. 
 *  @param  hNode Tree node.
 *  @return 
 *  - A pointer on the first child of a node; or
 *  - @c NULL when the node has no child.
 *  
 *  @link DOC_TLVTREE Back to top @endlink  **/

			TLV_TREE_NODE TlvTree_GetFirstChild( const TLV_TREE_NODE hNode );

// Function: TlvTree_GetParent

/*! @brief This function returns the parent of the node @a hNode. 
 *  @param  hNode Tree node.
 *  @return 
 *  - A pointer on the parent of a node; or 
 *  - @c NULL when @a hNode is the root node of the tree.
 *  
 *  @link DOC_TLVTREE Back to top @endlink  **/

TLV_TREE_NODE TlvTree_GetParent( const TLV_TREE_NODE hNode );


// Function: TlvTree_GetNext

/*! @brief This function returns the next node (same parent and same generation).
 *  @brief It allows to iterate on all the child of a node (using \ref TlvTree_GetFirstChild) to get the first child and then \ref TlvTree_GetNext to iterate on the following childs. 
 *  @param  hNode Tree node.
 *  @return 
 *  - A pointer on the first brother of a node; or 
 *  - @c NULL at the end of the iteration. 
 *  
 *  @link DOC_TLVTREE Back to top @endlink  **/

TLV_TREE_NODE TlvTree_GetNext( const TLV_TREE_NODE hNode );


// Function: TlvTree_GetTag

/*! @brief This function allows to know the tag of the node.
 *  @param  hNode Tree node.
 *  @return The tag of the node
 *  
 *  @link DOC_TLVTREE Back to top @endlink  **/

			unsigned int TlvTree_GetTag( const TLV_TREE_NODE hNode );

// Function: TlvTree_GetLength

/*! @brief This function gets the data length of the node.
 *  @param  hNode Tree node.
 *  @return 
 *  - The data length of the node; or
 *  - 0 if the node contains no data
 *  
 *  @link DOC_TLVTREE Back to top @endlink  **/

unsigned int TlvTree_GetLength( const TLV_TREE_NODE hNode );

// Function: TlvTree_GetData

/*! @brief This function allows to know the data of the node.
 *  @param  hNode Tree node.
 *  @return 
 *  - A pointer on the data of the node; or
 *  - @c NULL pointer if the node contains no data
 *  
 *  @link DOC_TLVTREE Back to top @endlink **/
 
			void *TlvTree_GetData( const TLV_TREE_NODE hNode );

/*! @} 

 * @name Node Modifiers
 * The following functions allow modifying the data contained in a node:
 *  @{ **/

// Function: TlvTree_SetTag

/*! @brief This function modifies the tag of the node.
 *  @param  hNode Tree node.
 *  @param  nTag New tag of the node.
 *  @return None
 *  
 *  @link DOC_TLVTREE Back to top @endlink  **/

void TlvTree_SetTag( TLV_TREE_NODE hNode, unsigned int nTag );

// Function: TlvTree_SetData 

/*! @brief This modifies the data contained in a node.
 *  @brief The data currently contained in the node are freed. The new data are allocated in the dynamic RAM and set from the data given by parameter @a pData.
 *  @param  hNode Tree node.
 *  @param  pData Pointer on the buffer containing the binary data of the node.
 *  @param  nSize Data size.
 *  @return 
 *  - #TLV_TREE_OK; or
 *  - #TLV_TREE_ERROR_MEMORY; or
 *  - #TLV_TREE_ERROR_INVALID_SIZE
 *  @note It is possible to just erase the current data of the node, setting the parameters @a pData to @c NULL or @a nSize to 0.
 *  
 *  @link DOC_TLVTREE Back to top @endlink  **/

      int TlvTree_SetData( TLV_TREE_NODE hNode, const void *pData, unsigned int nSize );

// Function: TlvTree_SetDataString 

/*! @brief This function modifies the data string contained in a node.
 *  @brief The data string currently contained in the node are freed. The new data string are allocated in the dynamic RAM and set from the data given by parameter @a szString.
 *  @param  hNode Tree node.
 *  @param  szString @c NULL terminated string.
 *  @return 
 *  - #TLV_TREE_OK; or
 *  - #TLV_TREE_ERROR_MEMORY; or
 *  - #TLV_TREE_ERROR_INVALID_SIZE
 *  @note It is possible to just erase the current data of the node.
 *  
 *  @link DOC_TLVTREE Back to top @endlink  **/

      int TlvTree_SetDataString ( TLV_TREE_NODE hNode, const char *szString );

// Function: TlvTree_SetDataInteger 

/*! @brief This function modifies the data integer contained in a node.
 *  @brief The data integer currently contained in the node are freed. The new data integer are allocated in the dynamic RAM and set from the data.
 *  @param  hNode Tree node.
 *  @param  nValue Integer value.
 *  @param  nSize Data size. For the integer values, this size must be 1, 2, 3 or 4 bytes.
 *  @return 
 *  - #TLV_TREE_OK; or
 *  - #TLV_TREE_ERROR_MEMORY; or
 *  - #TLV_TREE_ERROR_INVALID_SIZE
 *  @note It is possible to just erase the current data of the node, setting the parameter @a nSize to 0.
 *  
 *  @link DOC_TLVTREE Back to top @endlink  **/

      int TlvTree_SetDataInteger( TLV_TREE_NODE hNode, unsigned int nValue, unsigned int nSize );

/*! @} 

 * @name Tree Duplication
 * @{ **/

// Function: TlvTree_Copy

/*! @brief This function creates a copy of a \b TLV_TREE object
 *  @brief This function creates a new tree which is a perfect copy of the source tree @a hSrcTree.  The two trees are totally separate; they do not share neither nodes nor data.
 *  @param  hSrcTree Tree to duplicate.
 *  @return 
 *  - A newly created tree copy of the source tree @a hSrcTree; or
 *  - @c NULL in case of error
 *  @note This function is a constructor, creating a tree allocated in the dynamic memory. It must be released at the end using the destructor function \ref TlvTree_Release.
 *  
 *  @link DOC_TLVTREE Back to top @endlink  **/
 
      TLV_TREE_NODE TlvTree_Copy( const TLV_TREE_NODE hSrcTree );
/*! @} **/

/*! @} 

 * @name Debug
 * @{ **/

// Function: TlvTree_Dump

/*! @brief This function dumps a \b TLV_TREE object on the trace link
 *  @param  hTree Tree to trace.
 *  @param  szTitle Title of the dump.
 *  @return 
 *  - #TLV_TREE_OK; or
 *  - #TLV_TREE_ERROR_MEMORY; or
 *  - #TLV_TREE_ERROR_INVALID_TREE
 *  
 *  @link DOC_TLVTREE Back to top @endlink  **/

      int TlvTree_Dump( const TLV_TREE_NODE hTree, const char* szTitle );

/*! @} **/


/*! @} **/


//int TlvTree_RemoveChild( TLV_TREE_NODE hParent, const TLV_TREE_NODE hNode );
// TlvTree_RemoveChild is deprecated, please use TlvTree_Release instead 



#ifdef __cplusplus
}
#endif


#endif // __TLV_TREE_INCLUDED_H__



