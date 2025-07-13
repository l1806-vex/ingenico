/**
* \file MyTlvTree.h
* \brief This module contains missing function of module TlvTree.h.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "TlvTree.h"

//! \defgroup Group_MyTlvTree Customized functions for TLV tree management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#ifdef _TLVTREE_DEBUG_

#define TlvTree_New(nTag)													Dbg_TlvTree_New(nTag, __FILE__, __LINE__)
#define TlvTree_Release(hNode)												Dbg_TlvTree_Release(hNode, __FILE__, __LINE__)
#define TlvTree_Unserialize(phNode, nSerializer, pucBuffer, nBufferSize)	Dbg_TlvTree_Unserialize(phNode, nSerializer, pucBuffer, nBufferSize, __FILE__, __LINE__)
#define TlvTree_Copy(hSrcTree)												Dbg_TlvTree_Copy(hSrcTree, __FILE__, __LINE__)
#define TlvTree_AddChild(hParent, nTag, pData, nSize)						Dbg_TlvTree_AddChild(hParent, nTag, pData, nSize, __FILE__, __LINE__)
#define TlvTree_AddChildInteger(hParent, nTag, nValue, nSize)				Dbg_TlvTree_AddChildInteger(hParent, nTag, nValue, nSize, __FILE__, __LINE__)
#define TlvTree_AddChildString(hParent, nTag, szString)						Dbg_TlvTree_AddChildString(hParent, nTag, szString, __FILE__, __LINE__)

#endif

#ifdef _TLVTREE_DEBUG_TRACE_
#define TlvTree_New(nTag)													Dbg_TlvTree_New_Trace(nTag, __FILE__, __LINE__)
#define TlvTree_ReleaseEx(phNode)											Dbg_TlvTree_Release_Trace(phNode, __FILE__, __LINE__)
#define TlvTree_Copy(hSrcTree)												Dbg_TlvTree_Copy_Trace(hSrcTree, __FILE__, __LINE__)
#endif


/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

#ifndef _TLVTREE_DEBUG_TRACE_
//===========================================================================
//! \brief This function releases the TLV tree given as input parameter.
//! \param[in] pTlvTree : TLV tree to release.
//===========================================================================
void TlvTree_ReleaseEx(TLV_TREE_NODE* pTlvTree);
#endif

//===========================================================================
//! \brief This function updates data and length of the child ulTag of the 
//! tree hTlvTree if found. If the child ulTag is not found in the input tree
//! hTlvTree, the child is created.
//! \param[in] hTlvTree : TLV tree in which to update or create the child ulTag.
//! \param[in] ulTag : child to find / create in input TLV tree hTlvTree.
//! \param[in] pData : child data to set.
//! \param[in] ulLength : child length to set.
//===========================================================================
TLV_TREE_NODE TlvTree_SetChildTag(TLV_TREE_NODE hTlvTree, unsigned long ulTag, const void* pData, unsigned long ulLength);

//===========================================================================
//! \brief This function adds the children from hTlvTreeToAdd to the tree hTlvTree.
//! \param[in,out] hTlvTree : TLV tree in which to add the children of hTlvTreeToAdd.
//! \param[in] hTlvTreeToAdd : TLV tree containing the children to add.
//! \return 
//! - TRUE if successful.
//! - FALSE if one of the input trees is NULL.
//===========================================================================
int TlvTree_AddChildren(TLV_TREE_NODE hTlvTree, const TLV_TREE_NODE hTlvTreeToAdd);

//===========================================================================
//! \brief This function releases all the children of input TLV tree hTlvTree.
//! \param[in,out] hTlvTree : input TLV tree in which to release all the children.
//===========================================================================
void TlvTree_RemoveChildren(TLV_TREE_NODE hTlvTree);

//===========================================================================
//! \brief This function cleans the input TLV tree hTlvTree : it supresses all
//! tags with empty ptData and length set to 0.
//! \param[in,out] hTlvTree : input TLV tree to clean.
//===========================================================================
TLV_TREE_NODE TlvTree_Clean(TLV_TREE_NODE hTlvTree);

#ifdef _TLVTREE_DEBUG_

//===========================================================================
//! \brief This function traces the global TLV tree g_nTheTlvTrees.
//===========================================================================
void TlvTree_DumpAllocatedTrees(void);

//===========================================================================
//! \brief This function builds the global TLV tree g_nTheTlvTrees, with the
//! data nTag, szFile, nLine.
//! \param[in] nTag : data of the first child.
//! \param[in] szFile : data to add to the first child of nTag.
//! \param[in] nLine : data to add to the second child of nTag.
//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_New(unsigned int nTag, const char* szFile, int nLine);

//===========================================================================
//! \brief This function releases the child hNode of the global TLV tree 
//! g_nTheTlvTrees.
//! \param[in] hNode : child to release.
//! \param[in] szFile : not used.
//! \param[in] nLine : not used.
//===========================================================================
void Dbg_TlvTree_Release(TLV_TREE_NODE hNode, const char* szFile, int nLine);

//===========================================================================
//! \brief This function unserializes the TLV tree phNode, and builds the global
//! TLV tree g_nTheTlvTrees with the data phNode, szFile, and nLine.
//! \param[in] phNode : TLV tree to be unserialized. And first child of g_nTheTlvTrees
//! \param[in] nSerializer : serialization type : 
//! - TLV_TREE_SERIALIZER_DEFAULT.
//! - TLV_TREE_SERIALIZER_XML.
//! \param[out] pucBuffer : buffer to store unserialized data.
//! \param[in] nBufferSize : buffer size.
//! \param[in] szFile : data to add to the first child of the tree phNode.
//! \param[in] nLine : data to add to the second child of the tree phNode.
//! \return Unserialization result : 
//! - TLV_TREE_OK if deserialization is successful.
//! - error code otherwise.
//===========================================================================
int Dbg_TlvTree_Unserialize(TLV_TREE_NODE *phNode, unsigned int nSerializer, const unsigned char *pucBuffer, unsigned int nBufferSize, const char* szFile, int nLine);

//===========================================================================
//! \brief This function copies the input TLV tree int the global TLV tree 
//! g_nTheTlvTrees. The data szFile, and nLine are also added in the global
//! TLV tree g_nTheTlvTrees.
//! \param[in] hSrcTree : input TLV tree to be copied.
//! \param[in] szFile : data to add to the first child of hSrcTree.
//! \param[in] nLine : data to add to the second child of hSrcTree.
//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_Copy(const TLV_TREE_NODE hSrcTree, const char* szFile, int nLine);

//===========================================================================
//! \brief This function adds the child nTag, to the input TLV tree hParent, 
//! and builds the global TLV tree g_nTheTlvTrees with the data hParent, szFile, and nLine.
//! \param[in] hParent : TLV tree in which to add the child nTag. And data 
//! of the first child of the global TLV tree g_nTheTlvTrees.
//! \param[in] nTag : tag number to add.
//! \param[in] pData : tag data to add.
//! \param[in] nSize : tag length to add.
//! \param[in] szFile : data to add to the first child of the tree hParent.
//! \param[in] nLine : data to add to the second child of the tree hParent.
//! \return Added child.
//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_AddChild(TLV_TREE_NODE hParent, unsigned int nTag, const void *pData, unsigned int nSize, const char* szFile, int nLine);

//===========================================================================
//! \brief This function adds the child nTag containing integer data, to the 
//! input TLV tree hParent. Then it builds the global TLV tree g_nTheTlvTrees 
//! with the data hParent, szFile, and nLine.
//! \param[in] hParent : TLV tree in which to add the child nTag. And data 
//! of the first child of the global TLV tree g_nTheTlvTrees.
//! \param[in] nTag : tag number to add.
//! \param[in] nValue : tag data to add.
//! \param[in] nSize : tag length to add.
//! \param[in] szFile : data to add to the first child of the tree hParent.
//! \param[in] nLine : data to add to the second child of the tree hParent.
//! \return Added child.
//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_AddChildInteger(TLV_TREE_NODE hParent, unsigned int nTag, unsigned int nValue, unsigned int nSize, const char* szFile, int nLine);

//===========================================================================
//! \brief This function adds the child nTag containing string data, to the 
//! input TLV tree hParent. Then it builds the global TLV tree g_nTheTlvTrees 
//! with the data hParent, szFile, and nLine.
//! \param[in] hParent : TLV tree in which to add the child nTag. And data 
//! of the first child of the global TLV tree g_nTheTlvTrees.
//! \param[in] nTag : tag number to add.
//! \param[in] szString : tag data to add.
//! \param[in] nSize : tag length to add.
//! \param[in] szFile : data to add to the first child of the tree hParent.
//! \param[in] nLine : data to add to the second child of the tree hParent.
//! \return Added child.
//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_AddChildString(TLV_TREE_NODE hParent, unsigned int nTag, const char *szString, const char* szFile, int nLine);

#endif

#ifdef _TLVTREE_DEBUG_TRACE_

//===========================================================================
//! \brief This function prints the level 1 children of a TLV tree.
//! \param[in] i_x_service_number : service number.
//! \param[in] ptr_Tree : TLV tree to print. 
//===========================================================================
void TraceTLVTree(int i_x_service_number, TLV_TREE_NODE *ptr_Tree);

//===========================================================================
//! \brief This function copies the content of the TLV tree given as parameter 
//! to a global DEL for debug.
//! \param[in] hTree : TLV tree to debug.
//===========================================================================
void TraceTLVTreeToDEL(TLV_TREE_NODE hTree);

//===========================================================================
//! \brief This function prints the available ram of the terminal
//! \param[in] pos : Current step of the transaction.
//===========================================================================
void TraceFreeRam(int pos);

//===========================================================================
//! \brief This function creates a TLV tree with tag nTag as father node. 
//! It also traces the TLV tree creation.
//! \param[in] nTag : tag number.
//! \param[in] szFile : file in which the TLV tree is created.
//! \param[in] nLine : line number where the TLV tree is created.
//! \return TLV tree created.
//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_New_Trace(unsigned int nTag, const char* szFile, int nLine);

//===========================================================================
//! \brief This function releases the TLV tree given as input parameter.
//! It also traces the TLV tree release.
//! \param[in] phNode : pointer to TLV tree to release.
//! \param[in] szFile : file in which the TLV tree is released.
//! \param[in] nLine : line number where the TLV tree is released.
//===========================================================================
void Dbg_TlvTree_Release_Trace(TLV_TREE_NODE *phNode, const char* szFile, int nLine);

//===========================================================================
//! \brief This function returns the copy of the TLV tree given as input parameter.
//! It also traces the TLV tree copied.
//! \param[in] hSrcTree : TLV tree to copy.
//! \param[in] szFile : file in which the TLV tree is copied.
//! \param[in] nLine : line number where the TLV tree is copied.
//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_Copy_Trace(const TLV_TREE_NODE hSrcTree, const char* szFile, int nLine);
#endif

//! @}


