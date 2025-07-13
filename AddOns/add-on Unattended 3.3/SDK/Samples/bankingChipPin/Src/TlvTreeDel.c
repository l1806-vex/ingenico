/**
* \file TlvTreeDel.c
* \brief This module contains the functions to perform conversions 
* from DEL to TLV tree or from TLV tree to DEL.
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

#include "SDK30.h"
#include "del_lib.h"
#include "MyTlvTree.h"
#include "TlvTreeDel.h"
#include "_emvdctag_.h"

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

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

//===========================================================================
int AddDelValueToTlvTree(TLV_TREE_NODE hTlvTree, const _DEL_* pDel)
{
	int nNumOfTags;
	int nIndex;
	_DataElement_* pDataElement;
	int bResult;

	if ((hTlvTree == NULL) || (pDel == NULL))
	{
		return FALSE;
	}

	// Get the number of tags in the DEL
	bResult = TRUE;
	nNumOfTags = _DEL_GetCount(pDel);

	// For each tag in the DEL
	for(nIndex = 1; nIndex <= nNumOfTags; nIndex++)
	{
		// Get the tag from the DEL
		pDataElement = _DEL_GetDataElement((_DEL_*)pDel, nIndex);
		if (pDataElement != NULL)
		{
			// Add the tag to the TlvTree
			if (TlvTree_AddChild(hTlvTree, pDataElement->tag, pDataElement->ptValue, pDataElement->length) == NULL)
			{
				bResult = FALSE;
			}
		}
	}

	return bResult;
}

//===========================================================================
int AddTlvTreeToDelValue(_DEL_* pDel, const TLV_TREE_NODE hTlvTree)
{
	TLV_TREE_NODE hNode;
	int bResult;
	DataElement DataElt;

	if ((pDel == NULL) || (hTlvTree == NULL))
	{
		return FALSE;
	}

	// For each tag in the TlvTree
	bResult = TRUE;
	hNode = TlvTree_GetFirstChild(hTlvTree);
	while(hNode != NULL)
	{
		// Add the tag to the DEL
		DataElt.tag = TlvTree_GetTag(hNode);
		DataElt.length = TlvTree_GetLength(hNode);
		DataElt.ptValue = TlvTree_GetData(hNode);
		if (DelValue_AddDataElement(pDel, &DataElt) != DEL_OK)
		{
			bResult = FALSE;
		}

		hNode = TlvTree_GetNext(hNode);
	}

	return bResult;
}

//===========================================================================
int AddTlvTreeToDelValueEx(_DEL_* pDel, TLV_TREE_NODE hTlvTree)
{
	TLV_TREE_NODE hNode;
	TLV_TREE_NODE hNextNode;
	int bResult;
	DataElement DataElt;
	int nIndex;

	if ((pDel == NULL) || (hTlvTree == NULL))
	{
		return FALSE;
	}

	// For each tag in the TlvTree
	nIndex = DelValue_GetCount(pDel);
	bResult = TRUE;
	hNode = TlvTree_GetFirstChild(hTlvTree);
	while((hNode != NULL) && (bResult) && (nIndex < DEL_NUMBER_OF_DATA_ELEMENT))
	{
		// Add the tag to the DEL
		DataElt.tag = TlvTree_GetTag(hNode);
		DataElt.length = TlvTree_GetLength(hNode);
		DataElt.ptValue = TlvTree_GetData(hNode);
		if (DelValue_AddDataElement(pDel, &DataElt) == DEL_OK)
		{
			// Remove the added tag
			hNextNode = TlvTree_GetNext(hNode);
			TlvTree_Release(hNode);
			hNode = hNextNode;
		}
		else
		{
			bResult = FALSE;
		}
	}

	return bResult;
}

//===========================================================================
int AddFullTlvTreeToDelValue(_DEL_* pDel, const TLV_TREE_NODE hTlvTree)
{
	TLV_TREE_NODE hStartNode;
	TLV_TREE_NODE hNode;
	TLV_TREE_NODE hNextNode;
	int bResult;
	DataElement DataElt;
	int bEnd;

	if ((pDel == NULL) || (hTlvTree == NULL))
	{
		return FALSE;
	}

	hStartNode = hTlvTree;
	bResult = TRUE;

	hNode = hStartNode;
	// For each tag in the TlvTree
	do
	{
		// Go down in the tree
		hNextNode = TlvTree_GetFirstChild(hNode);
		if (hNextNode == NULL)
		{
			if (hNode != hStartNode)
			{
				// Go right in the tree
				hNextNode = TlvTree_GetNext(hNode);
				if (hNextNode == NULL)
				{
					bEnd = FALSE;
					do
					{
						// Go up in the tree
						hNextNode = TlvTree_GetParent(hNode);
						if ((hNextNode != NULL) && (hNextNode != hStartNode))
						{
							// Go right in the tree
							hNextNode = TlvTree_GetNext(hNextNode);
							if (hNextNode != NULL)
							{
								// Found a new node => stop
								bEnd = TRUE;
							}
						}
						else
						{
							// It is the start node => stop
							hNextNode = NULL;
							bEnd = TRUE;
						}
					} while(!bEnd);
				}
			}
		}

		hNode = hNextNode;
		if (hNode != NULL)
		{
			// Add the tag to the DEL
			DataElt.tag = TlvTree_GetTag(hNode);
			DataElt.length = TlvTree_GetLength(hNode);
			DataElt.ptValue = TlvTree_GetData(hNode);
			if (DelValue_AddDataElement(pDel, &DataElt) != DEL_OK)
			{
				bResult = FALSE;
			}
		}
	} while(hNode != NULL);

	return bResult;
}

//===========================================================================
int CreateTlvTreeFromDel(TLV_TREE_NODE* pTlvTree, const _DEL_* pDel)
{
	if (pTlvTree == NULL)
	{
		return FALSE;
	}

	*pTlvTree = TlvTree_New(0);
	if (*pTlvTree == NULL)
	{
		return FALSE;
	}

	if (pDel == NULL)
	{
		return TRUE;
	}

	return AddDelValueToTlvTree(*pTlvTree, pDel);
}

//===========================================================================
int CreateCandidateListTlvTreefromDel(const _DEL_* pDel, TLV_TREE_NODE* pOutputTLVTree)
{
	_DataElement_ *ptElt;
	int nResult, nbElt, i_index;
	TLV_TREE_NODE hChild;

	nResult = TRUE;
	*pOutputTLVTree = TlvTree_New(0);
	if (*pOutputTLVTree != NULL)
	{
		if (pDel != NULL)
		{
			hChild = NULL;
			nbElt=_DEL_GetCount(pDel);
			for (i_index = 1; i_index <= nbElt; i_index++)
			{
				ptElt = _DEL_GetDataElement((_DEL_*)pDel, i_index);
				switch(ptElt->tag)
				{
					case TAG_SERVICE_STATUS_CODE:
					case TAG_CARDHOLDER_CONFIRMATION:
						// Copy the tag
						if (TlvTree_AddChild(*pOutputTLVTree, ptElt->tag, ptElt->ptValue, ptElt->length) == NULL)
						{
							nResult = FALSE;
						}
						break;

					case TAG_AID_ICC:
						// Create a new AID node
						hChild = TlvTree_AddChild(*pOutputTLVTree, ptElt->tag, ptElt->ptValue, ptElt->length);
						if (hChild == NULL)
						{
							nResult = FALSE;
						}
						break;

					case TAG_APPLICATION_LABEL:
					case TAG_APPLICATION_PREFFERRED_NAME:
					case TAG_ISSUER_CODE_TABLE_INDEX:
					case TAG_LANGUAGE_PREFERENCE:
					case TAG_APPLI_PRIOR_IND:
						if (hChild != NULL)
						{
							// Add information about the AID
							if (TlvTree_AddChild(hChild, ptElt->tag, ptElt->ptValue, ptElt->length) == NULL)
							{
								nResult = FALSE;
							}
						}
						break;

					default:
						// Unknown tag => Skip it
						break;
				}
			}

			if( nResult == FALSE)
			{
				// Error => Delete the output TlvTree
				TlvTree_ReleaseEx(pOutputTLVTree);
			}
		}
		else
		{
			// input DEL empty
			nResult = FALSE;
		}
	}
	else
	{	
		// unable to create a TLV Tree
		nResult = FALSE;
	}
	return nResult;
}

