/**
* \file MyTlvTree.c
* \brief This module contains missing function of module TlvTree.c.
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

extern void CUPRINT_Open_Printer(void);
extern  void CUPRINT_PrintString(unsigned char *pucString_p, int iWait_p );
extern void CUPRINT_Close_Printer(void );
//! \addtogroup Group_MyTlvTree
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define DBG_TLVTREE_BUFFER_INCREMENT	128

#ifdef _TLVTREE_DEBUG_TRACE_

#undef TlvTree_New
#undef TlvTree_ReleaseEx
#undef TlvTree_Copy

#endif

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

#ifdef _TLVTREE_DEBUG_
static TLV_TREE_NODE g_nTheTlvTrees = NULL;
#endif

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
void TlvTree_ReleaseEx(TLV_TREE_NODE* pTlvTree)
{
	if (pTlvTree != NULL)
	{
		if (*pTlvTree != NULL)
		{
			TlvTree_Release(*pTlvTree);
			*pTlvTree = NULL;
		}
	}
}

//===========================================================================
TLV_TREE_NODE TlvTree_SetChildTag(TLV_TREE_NODE hTlvTree, unsigned long ulTag, const void* pData, unsigned long ulLength)
{
	TLV_TREE_NODE hNode;
	int bFound;

	if (hTlvTree == NULL)
	{
		return FALSE;
	}

	bFound = FALSE;
	hNode = TlvTree_GetFirstChild(hTlvTree);
	while((!bFound) && (hNode != NULL))
	{
		if (TlvTree_GetTag(hNode) == ulTag)
		{
			bFound = TRUE;
		}
		else
		{
			hNode = TlvTree_GetNext(hNode);
		}
	}

	if (bFound)
	{
		// The tag is already present, set the new value
//		{
//			char str[40];
//			sprintf(str,"01 %lX %lu\n", (unsigned long)hNode, (unsigned long)ulLength);
//			upload_diagnostic_txt(str);
//		}
		TlvTree_SetData(hNode, pData, ulLength);
	}
	else
	{
		// The tag is not present, add it
		hNode = TlvTree_AddChild(hTlvTree, ulTag, pData, ulLength);
	}

	return hNode;
}

//===========================================================================
int TlvTree_AddChildren(TLV_TREE_NODE hTlvTree, const TLV_TREE_NODE hTlvTreeToAdd)
{
	TLV_TREE_NODE hStartNode;
	TLV_TREE_NODE hNode;
	TLV_TREE_NODE hNodeToAdd;
	TLV_TREE_NODE hNextNode;
	int bResult;
	int bEnd;

	if ((hTlvTree == NULL) || (hTlvTreeToAdd == NULL))
	{
		return FALSE;
	}

	hStartNode = hTlvTreeToAdd;
	bResult = TRUE;

	hNode = hTlvTree;
	hNodeToAdd = hTlvTreeToAdd;
	// For each child in hTlvTreeToAdd
	do
	{
		// Go down in the tree
		hNextNode = TlvTree_GetFirstChild(hNodeToAdd);
		if (hNextNode == NULL)
		{
			if (hNodeToAdd != hStartNode)
			{
				// Go right in the tree
				hNextNode = TlvTree_GetNext(hNodeToAdd);
				if (hNextNode == NULL)
				{
					bEnd = FALSE;
					do
					{
						// Go up in the tree
						hNextNode = TlvTree_GetParent(hNodeToAdd);
						hNode = TlvTree_GetParent(hNode);
						if ((hNextNode != NULL) && (hNextNode != hStartNode))
						{
							// Go right in the tree
							hNextNode = TlvTree_GetNext(hNextNode);
							if (hNextNode != NULL)
							{
								// Found a new node => stop
								hNode = TlvTree_GetParent(hNode);
								bEnd = TRUE;
							}
							else
							{
								// Go up in the tree
								hNodeToAdd = TlvTree_GetParent(hNodeToAdd);
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
				else
				{
					hNode = TlvTree_GetParent(hNode);
				}
			}
		}

		hNodeToAdd = hNextNode;
		if (hNodeToAdd != NULL)
		{
			// Add the tag to hNode 
			hNode = TlvTree_AddChild(hNode, TlvTree_GetTag(hNodeToAdd), TlvTree_GetData(hNodeToAdd), TlvTree_GetLength(hNodeToAdd));
		}
	} while(hNodeToAdd != NULL);

	return bResult;
}

//===========================================================================
void TlvTree_RemoveChildren(TLV_TREE_NODE hTlvTree)
{
	TLV_TREE_NODE hNode;
	TLV_TREE_NODE hNodeNext;

	if (hTlvTree != NULL)
	{
		hNode = TlvTree_GetFirstChild(hTlvTree);
		while(hNode != NULL)
		{
			hNodeNext = TlvTree_GetNext(hNode);
			TlvTree_Release(hNode);
			hNode = hNodeNext;
		}
	}
}

//===========================================================================
TLV_TREE_NODE TlvTree_Clean(TLV_TREE_NODE hTlvTree)
{
	unsigned int length;
	char *ptData;
	TLV_TREE_NODE hNode; 
	TLV_TREE_NODE hNode2; 

	if (hTlvTree != NULL)
	{
		hNode = TlvTree_GetFirstChild(hTlvTree);
		while(hNode != NULL)
		{
			// Get the length
			length = TlvTree_GetLength(hNode);

			// Get the data
			ptData = TlvTree_GetData(hNode);

			if ((length == 0) || (ptData == NULL))
			{
				// Get next node
				hNode2 = TlvTree_GetNext(hNode);

				// remove empty tag
				TlvTree_Release(hNode);

				// Go to next node
				hNode = hNode2;
			}
			else
			{
				// Get the next node
				hNode = TlvTree_GetNext(hNode);
			}
		}
	}
	return hTlvTree;
}

#ifdef _TLVTREE_DEBUG_

#undef TlvTree_New
#undef TlvTree_Release
#undef TlvTree_Unserialize
#undef TlvTree_Copy
#undef TlvTree_AddChild
#undef TlvTree_AddChildInteger
#undef TlvTree_AddChildString

//===========================================================================
void TlvTree_DumpAllocatedTrees(void)
{
	static char String[1024 + 1];
	TLV_TREE_NODE hNode;
	TLV_TREE_NODE hNode2;
	const TLV_TREE_NODE* pTlvTree;
	const char* pFile;
	const int* pLine;
	char* pPtr;

	trace(SAP_KERNEL_TRAP_RESET, 15, "ALLOCATED TREES");

	hNode = TlvTree_GetFirstChild(g_nTheTlvTrees);
	while(hNode != NULL)
	{
		pTlvTree = TlvTree_GetData(hNode);

		hNode2 = TlvTree_Find(hNode, 2, 0);
		if (hNode2 != NULL)
		{
			pFile = TlvTree_GetData(hNode2);
		}
		else
		{
			pFile = NULL;
		}

		hNode2 = TlvTree_Find(hNode, 3, 0);
		if (hNode2 != NULL)
		{
			pLine = TlvTree_GetData(hNode2);
		}
		else
		{
			pLine = NULL;
		}

		pPtr = String;
		*pPtr = '0';

		if (pTlvTree != NULL)
		{
			pPtr += sprintf(pPtr, "TlvTree %08lX", (unsigned long)*pTlvTree);
		}
		if (pLine != NULL)
		{
			pPtr += sprintf(pPtr, "Line %-11d", *pLine);

		}
		if (pFile != NULL)
		{
			pPtr += sprintf(pPtr, "File %s", pFile);
		}

		trace(SAP_KERNEL_TRAP_RESET, strlen(String), String);

		hNode = TlvTree_GetNext(hNode);
	}

	trace(SAP_KERNEL_TRAP_RESET, 15, "===============");
}

//===========================================================================
//! \brief This function builds the global TLV tree g_nTheTlvTrees, with the
//! data hTlvTree, szFile, nLine.
//! \param[in] hTlvTree : data of the first child.
//! \param[in] szFile : data of the first child of hTlvTree.
//! \param[in] nLine : data of the second child of hTlvTree.
//===========================================================================
static void __Dbg_TlvTree_New(TLV_TREE_NODE hTlvTree, const char* szFile, int nLine)
{
	TLV_TREE_NODE hNode;

	if (g_nTheTlvTrees == NULL)
	{
		g_nTheTlvTrees = TlvTree_New(0);
	}

	if (g_nTheTlvTrees != NULL)
	{
		hNode = TlvTree_AddChild(g_nTheTlvTrees, 1, &hTlvTree, sizeof(hTlvTree));
		if (szFile != NULL)
		{
			TlvTree_AddChild(hNode, 2, szFile, strlen(szFile) + 1);
		}
		if (nLine > 0)
		{
			TlvTree_AddChild(hNode, 3, &nLine, sizeof(nLine));
		}
	}
}

//===========================================================================
//! \brief This function releases the TLV tree hTlvTree if found in the global 
//! TLV tree g_nTheTlvTrees.
//! \param[in] hTlvTree : TLV tree to release.
//! \param[in] szFile : not used.
//! \param[in] nLine : not used.
//===========================================================================
static void __Dbg_TlvTree_Release(TLV_TREE_NODE hTlvTree, const char* szFile, int nLine)
{
	TLV_TREE_NODE hNode;

	(void)szFile;
	(void)nLine;

	if (g_nTheTlvTrees != NULL)
	{
		hNode = TlvTree_GetFirstChild(g_nTheTlvTrees);
		while(hNode != NULL)
		{
			if (memcmp(&hTlvTree, TlvTree_GetData(hNode), sizeof(hTlvTree)) == 0)
			{
				TlvTree_Release(hNode);
				hNode = NULL;
			}
			else
			{
				hNode = TlvTree_GetNext(hNode);
			}
		}
	}
}

//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_New(unsigned int nTag, const char* szFile, int nLine)
{
	TLV_TREE_NODE hTlvTree;

	hTlvTree = TlvTree_New(nTag);
	if (hTlvTree != NULL)
	{
		__Dbg_TlvTree_New(hTlvTree, szFile, nLine);
	}

	return hTlvTree;
}

//===========================================================================
int Dbg_TlvTree_Unserialize(TLV_TREE_NODE *phNode, unsigned int nSerializer, const unsigned char *pucBuffer, unsigned int nBufferSize, const char* szFile, int nLine)
{
	int nResult;

	nResult = TlvTree_Unserialize(phNode, nSerializer, pucBuffer, nBufferSize);
	if (phNode != NULL)
	{
		if ((nResult == 0) && (*phNode != NULL))
		{
			__Dbg_TlvTree_New(*phNode, szFile, nLine);
		}
	}

	return nResult;
}

//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_Copy(const TLV_TREE_NODE hSrcTree, const char* szFile, int nLine)
{
	TLV_TREE_NODE hTlvTree;

	hTlvTree = TlvTree_Copy(hSrcTree);
	if (hTlvTree != NULL)
	{
		__Dbg_TlvTree_New(hTlvTree, szFile, nLine);
	}

	return hTlvTree;
}

//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_AddChild(TLV_TREE_NODE hParent, unsigned int nTag, const void *pData, unsigned int nSize, const char* szFile, int nLine)
{
	TLV_TREE_NODE hTlvTree;

	hTlvTree = TlvTree_AddChild(hParent, nTag, pData, nSize);
	if ((hParent == NULL) && (hTlvTree != NULL))
	{
		__Dbg_TlvTree_New(hTlvTree, szFile, nLine);
	}

	return hTlvTree;
}

//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_AddChildInteger(TLV_TREE_NODE hParent, unsigned int nTag, unsigned int nValue, unsigned int nSize, const char* szFile, int nLine)
{
	TLV_TREE_NODE hTlvTree;

	hTlvTree = TlvTree_AddChildInteger(hParent, nTag, nValue, nSize);
	if ((hParent == NULL) && (hTlvTree != NULL))
	{
		__Dbg_TlvTree_New(hTlvTree, szFile, nLine);
	}

	return hTlvTree;
}

//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_AddChildString(TLV_TREE_NODE hParent, unsigned int nTag, const char *szString, const char* szFile, int nLine)
{
	TLV_TREE_NODE hTlvTree;

	hTlvTree = TlvTree_AddChildString(hParent, nTag, szString);
	if ((hParent == NULL) && (hTlvTree != NULL))
	{
		__Dbg_TlvTree_New(hTlvTree, szFile, nLine);
	}

	return hTlvTree;
}

//===========================================================================
void Dbg_TlvTree_Release(TLV_TREE_NODE hNode, const char* szFile, int nLine)
{
	TlvTree_Release(hNode);
	__Dbg_TlvTree_Release(hNode, szFile, nLine);
}

#endif

#ifdef _TLVTREE_DEBUG_TRACE_

//===========================================================================
void TraceTLVTree(int i_x_service_number, TLV_TREE_NODE *ptr_Tree)
{
	unsigned int TagValueIndex;
	char Buffer[200];
	char Buffer_bis[200];
	TLV_TREE_NODE pTree;
	DataElement Elt;

   CUPRINT_Open_Printer();

	strcpy(Buffer, "\nTLV_T ");
	// strcat(Buffer, ptr_txt);

	// itoa(i_x_service_number, Buffer_bis, 10);
	Buffer_bis[0] = (i_x_service_number / 100) + 0x30;
	Buffer_bis[1] = (i_x_service_number % 100)/10 + 0x30;
	Buffer_bis[2] = (i_x_service_number % 10) + 0x30;
	Buffer_bis[3] = 0;
	strcat(Buffer, "Service:");
	strcat(Buffer, Buffer_bis);
	// printer trace 
   CUPRINT_PrintString( (unsigned char *)Buffer, 0);

	// trace(0x6E02, sizeof(Buffer), Buffer);

	pTree = TlvTree_GetFirstChild(*ptr_Tree);
	while (pTree!=NULL)
	{
		// get the tag
		Elt.tag = TlvTree_GetTag(pTree);
		// get the length
		Elt.length = TlvTree_GetLength(pTree);
		// get the value
		Elt.ptValue = TlvTree_GetData(pTree);

		sprintf(Buffer, "\nT=%lx", Elt.tag);
		sprintf(Buffer_bis, " L=%x", Elt.length);
		strcat(Buffer, Buffer_bis);
		sprintf(Buffer_bis, " V=");
		for (TagValueIndex=0; (TagValueIndex < Elt.length) && (TagValueIndex < 20); TagValueIndex++)
		{
			sprintf(&Buffer_bis[3+TagValueIndex*2], "%2x", Elt.ptValue[TagValueIndex]);
		}
		strcat(Buffer, Buffer_bis);
		// printer trace 
		CUPRINT_PrintString( (unsigned char *)Buffer, 0);
		// trace(0x6E02, sizeof(Buffer), Buffer);

		pTree = TlvTree_GetNext(pTree);
	} 
	// trace(0x6E02, sizeof("\n\n"), "\n\n");
	// printer trace 
   CUPRINT_PrintString((unsigned char *)"\n", 50);

   CUPRINT_Close_Printer();

}

DEL g_DEL;

//===========================================================================
void TraceTLVTreeToDEL(TLV_TREE_NODE hTree)
{
	_DEL_ _local_DEL_;

	if (hTree != NULL)
	{
		// Init local _DEL_
		_DEL_init(&_local_DEL_);

		// Init global DEL
		DEL_init(&g_DEL);

		// Convert input TLV tree into _DEL_
		AddTlvTreeToDelValue(&_local_DEL_, hTree);

		// Copy local _DEL_ to global DEL
		CopySortie(&_local_DEL_, &g_DEL);
	}
}

//===========================================================================
void TraceFreeRam(int pos)
{
	unsigned long free_ram;
	char buf[50];
	
	free_ram = FreeSpace();
	sprintf(buf, "Pos:%d  Free ram:%ld heapFree:%d", pos, (free_ram/1024), HeapFree() );
	trace(0x0A00, strlen(buf), buf);
}

//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_New_Trace(unsigned int nTag, const char* szFile, int nLine)
{
	TLV_TREE_NODE hTlvTree;
	char buf[80];

	hTlvTree = TlvTree_New(nTag);
	if (hTlvTree != NULL)
	{
		sprintf(buf, "TlvTree_New:%x File:%s Line:%d", (int)hTlvTree, szFile, nLine);
		trace(0x0A00, strlen(buf), buf);

	}

	return hTlvTree;
}

//===========================================================================
void Dbg_TlvTree_Release_Trace(TLV_TREE_NODE *phNode, const char* szFile, int nLine)
{
	char buf[80];

	sprintf(buf, "TlvTree_ReleaseEx:%x File:%s Line:%d", (int)*phNode, szFile, nLine);
	trace(0x0A00, strlen(buf), buf);
	TlvTree_ReleaseEx(phNode);

}

//===========================================================================
TLV_TREE_NODE Dbg_TlvTree_Copy_Trace(const TLV_TREE_NODE hSrcTree, const char* szFile, int nLine)
{
	TLV_TREE_NODE hTlvTree;
	char buf[80];

	hTlvTree = TlvTree_Copy(hSrcTree);
	if (hTlvTree != NULL)
	{
		sprintf(buf, "TlvTree_Copy:%x File:%s Line:%d", (int)hTlvTree, szFile, nLine);
		trace(0x0A00, strlen(buf), buf);
	}

	return hTlvTree;
}

#endif
//! @}

