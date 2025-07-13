/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "del_lib.h"
#include "TlvTree.h"

#include "TlvTreeDel.h"

//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

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
