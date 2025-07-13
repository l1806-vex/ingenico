/**
* \file gestion_param.c
* \brief This module contains the functions needed for parameters management.
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

#include "SDK30.H"
#include "_emvdctag_.h"
#include "del_lib.h"
#include "cu_term.h"
#include "cu_disk.h"					// For CUDISK_CreateDisk() declaration

#include "MyTlvTree.h"
#include "convert.h"
#define FILE_H
#include "gestion_param.h"
#undef FILE_H


//! \addtogroup Group_param
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define MAX_FILE_LG              1024				// maximum length buf for file

//! \defgroup TagAccess Tag reading access type
//! @{

#define TAG_READING              1
#define VALUE_READING            3

//! @}		// end of TagAccess


/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

TLV_TREE_NODE pTreeAppli = 0;						// Node managed only by the application
TLV_TREE_NODE pTreeParam = 0;						// Node from param file parameters
TLV_TREE_NODE pTreeDefault = 0;						// Node from default parameters

static unsigned char IndexMarkList;
static Struct_Mark MarkList[C_NB_MAX_MARK];


/* ======================================================================== */
/* Static function definitions                                              */
/* ======================================================================== */

static int CUPAR_SetBooleanValue (unsigned char *value, unsigned char *pBool);
static unsigned char IsBuffAscii(unsigned char u_x_len, char * ptr_x_car);
static int CUPAR_ascii2digit (char car,unsigned char *digit);


/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
void CUPAR_InitTree(TLV_TREE_NODE * pTree)
{
	if (*pTree)
		TlvTree_Release(*pTree);

	// TLV tree creation for tag managed only by the application
	*pTree = TlvTree_New(C_TAG_MAIN);

}

//===========================================================================
TLV_TREE_NODE PAR_ReadArray(char *ptr_ac_x_ParamTable, int i_x_ArraySize, unsigned long ul_x_MainTag)
{
	TLV_TREE_NODE  pTree = 0;
	int s;

	s = TlvTree_Unserialize(&pTree, TLV_TREE_SERIALIZER_XML, ptr_ac_x_ParamTable, i_x_ArraySize );

	if (s != 0)
	{
		upload_diagnostic_txt((unsigned char *)"PB on xml parameters !!!\n");
		trace (0, strlen ("PB on xml parameters !!!"), "PB on xml parameters !!!");
		// Reset of this node, a problem occur
		pTree = 0;
	}
	else
	{
		// Marks to select nodes in TLV Trees
		CUPAR_AddMarqs(&pTree);
		//    TlvTree_Dump(pTree, "Read param.par xml format" );
	}


	// If main tag isn't tag asked for the read
	// We take just a part of the TLVTree struct
	{
		if (ul_x_MainTag != C_TAG_MAIN)
		{
			TLV_TREE_NODE pReadTree = 0;

			pReadTree = PAR_FoundMarkInTree(pTree, ul_x_MainTag);

			if (pReadTree != pTree)
			{
				TLV_TREE_NODE pSavTree;
				pSavTree = TlvTree_Copy(pReadTree);
				TlvTree_Release(pTree);
				pTree = pSavTree;
			}
		}
	}

	return (pTree);
}

//===========================================================================
void CUPAR_WriteBinFile(TLV_TREE_NODE p_node, char *ptr_x_fileName, unsigned int i_x_Mark)
{
	// Local variables déclaration
	TLV_TREE_NODE hnode;

	// Looking for the node
	hnode = PAR_FoundMarkInTree(p_node, i_x_Mark);

	// If main mark has been found
	if (hnode == NULL)
		return; // No action possible, Main mark not found

	CUPAR_WriteAllBinFile(hnode, ptr_x_fileName);
}

//===========================================================================
int CUPAR_WriteAllBinFile(TLV_TREE_NODE pTree, char * ptr_OutBuf)
{
	unsigned char * ac_l_pucBuffer = NULL;
	unsigned int  result = 0;
	int           i_l_Size;
	S_FS_FILE     *ptr_file;

	/* Controle des paramètres d'entrées */
	if ((strlen(ptr_OutBuf) == 0) || (pTree == 0))
	{
		return 1;
	}

	ac_l_pucBuffer = (unsigned char *) umalloc(C_PUC_BUFFER_SIZE);

	// For check
	// int m = TlvTree_GetSerializationSize( pTree, TLV_TREE_SERIALIZER_DEFAULT);
	i_l_Size = TlvTree_Serialize( pTree, TLV_TREE_SERIALIZER_DEFAULT, ac_l_pucBuffer, C_PUC_BUFFER_SIZE );

	// The buffer is saved in a file

	if ((i_l_Size < 0) || (i_l_Size > C_PUC_BUFFER_SIZE)) /* If serialization pb */
	{
		result = 1;
	}

	if (result == 0)	// If ok
	{
		unsigned int Mode,rc;
		int ret;

		ret = CUDISK_CreateDisk();
		if (ret == FS_OK)
		{
			ret = FS_exist (ptr_OutBuf);

			if (ret == FS_OK)
			{
				trace (0, strlen ("FILE EXIST"), "FILE EXIST");
				// The former file is suppressed. 
				ret = FS_unlink (ptr_OutBuf);
			}
		}

		Mode = FS_WRTMOD;
		rc = FS_mount(ptr_OutBuf, &Mode);
		if (rc != FS_OK)
		{
			upload_diagnostic_txt((unsigned char *)"PB Mount COM File param\n");
			result = 1;
		} 

		ptr_file = FS_open (ptr_OutBuf, "a");
		if (ptr_file == NULL)
		{
			result = 1;
			trace (0, strlen ("ERROR CREATE FILE"), "ERROR CREATE FILE");
		}
	}

	if (result == 0)	// If ok
	{
		FS_write (ac_l_pucBuffer, 1, i_l_Size, ptr_file);
		FS_close(ptr_file);	// Close file
	}

	if (ac_l_pucBuffer != 0)
		ufree(ac_l_pucBuffer);
	return (result);
}


//===========================================================================
int CUPAR_ReadParamFile(TLV_TREE_NODE * p_node, char *pc_x_DirFile, unsigned int i_x_ParamFileType)
{
	int  result = 0;
	unsigned char * ac_l_pucBuffer = NULL;
	unsigned int Mode,rc;
	S_FS_FILE * ptr_file;

	TlvTree_Release(*p_node);

	// Read data from parameters file
	Mode = FS_READMOD;
	rc= FS_mount (pc_x_DirFile,&Mode);
	if (rc != FS_OK)
	{
		upload_diagnostic_txt((unsigned char *)"PB Mount COM Filen\n");
	}
	ptr_file = FS_open(pc_x_DirFile, "r");

	if (ptr_file != NULL)
	{
		int s;

		ac_l_pucBuffer = (unsigned char *) umalloc(C_PUC_BUFFER_SIZE);

		FS_read (ac_l_pucBuffer, 1, C_PUC_BUFFER_SIZE, ptr_file);
		FS_close(ptr_file);

		s = TlvTree_Unserialize(p_node, i_x_ParamFileType, ac_l_pucBuffer, C_PUC_BUFFER_SIZE );

		ufree(ac_l_pucBuffer);

		if (s != 0)
		{
			// Reset of this node, a problem occured
			*p_node = 0;
			result = 4;
		}
		else
		{
			// Marks to select nodes in TLV Trees
			CUPAR_AddMarqs(&pTreeParam);
		}
	}
	else
	{
		result = 5;
	}

	return (result);
}

//===========================================================================
int CUPAR_AddMarqs(TLV_TREE_NODE * p_node)
{
	int  result = 0;
	TLV_TREE_NODE pNode;
	TLV_TREE_NODE hChildnode;

	pNode = *p_node;

	do{
		hChildnode = TlvTree_GetFirstChild(pNode);
		// It's a node ?
		if (hChildnode != NULL)
		{
			char tmpbuf[30];
			sprintf(tmpbuf, "MARQ_%x", TlvTree_GetTag(pNode));

			// Set mark
			TlvTree_SetDataString(pNode, (const char *)tmpbuf);
		}

		pNode = TlvTree_Iterate(pNode, *p_node);

	}while(pNode != NULL );

	return (result);
}

//===========================================================================
void PAR_ResetMarkList(void)
{
	IndexMarkList = 0;
	memset(MarkList, 0, sizeof(Struct_Mark) *  C_NB_MAX_MARK);
}

//===========================================================================
int PAR_IsAMark(TLV_TREE_NODE pMark)
{
	unsigned int length;
	void * ptr_data;
	int i_l_Mark = 0;

	// Get the tag data, to check if the node data starts with MARK_XXX.
	length = TlvTree_GetLength(pMark);
	if (length > 5)
	{
		ptr_data = TlvTree_GetData(pMark);
		// Is it a mark ?
		if (strncmp((char *)ptr_data, "MARQ_", 5) == 0)
		{
			// Memorization of mark tag.
			i_l_Mark = TlvTree_GetTag(pMark);
		}
	}
	return (i_l_Mark);
}

//===========================================================================
TLV_TREE_NODE PAR_FoundMarkInTree(TLV_TREE_NODE pTLVTree, unsigned int i_x_NumMark)
{
	unsigned int nindex = 0, length;
	unsigned char Result = 0;
	void * ptr_data;
	TLV_TREE_NODE pTree;

	// Looking for the mark in the parameter TLV tree
	do{
		pTree = TlvTree_Find(pTLVTree, i_x_NumMark, nindex++);
		
		// If a node has been obtained
		if (pTree != NULL)
		{
			// Get tag data to check if it starts with Mark_XXX
			length = TlvTree_GetLength(pTree);
			if (length > 5)
			{
				ptr_data = TlvTree_GetData(pTree);
				// Is It a mark ?
				if (strncmp((char *)ptr_data, "MARQ_", 5) == 0)
				{
					// Memorize mark pointer
					Result = 1;
					break;
				}
			}
		}
		else 
			// Stop the process
			Result = 1;
	}while ((pTree != NULL) && (Result == 0));

	return (pTree);
}

//===========================================================================
TLV_TREE_NODE PAR_FoundMark(unsigned int i_x_NumMark)
{
	unsigned int  nindex = 0;
	TLV_TREE_NODE pTree;

	pTree = PAR_FoundMarkInTree(pTreeParam, i_x_NumMark);

	nindex = 0;
	// Looking for the mark in the default parameter TLVTree
	if (pTree == NULL)
		pTree = PAR_FoundMarkInTree(pTreeDefault, i_x_NumMark);

	return (pTree);
}

//===========================================================================
int PAR_SelectMark(unsigned int i_x_NumMark, unsigned int i_x_TreeType)
{
	int Result = 1;
	TLV_TREE_NODE pTree  = 0;
	TLV_TREE_NODE pTree2 = 0;

	switch(i_x_TreeType)
	{
		case C_TREE_ALL:
			pTree  = PAR_FoundMarkInTree(pTreeParam, i_x_NumMark);
			pTree2 = PAR_FoundMarkInTree(pTreeDefault, i_x_NumMark);
			break;

		case C_TREE_PARAM:
			pTree  = PAR_FoundMarkInTree(pTreeParam, i_x_NumMark);
			break;

		case C_TREE_DEFAULT:
			pTree2 = PAR_FoundMarkInTree(pTreeDefault, i_x_NumMark);
			break;

		case C_TREE_PARAM_FIRST:
			pTree  = PAR_FoundMarkInTree(pTreeParam, i_x_NumMark);
			if (pTree == NULL)
				pTree2 = PAR_FoundMarkInTree(pTreeDefault, i_x_NumMark);
			break;

		default:
			break;
	}

	// If mark found
	if (pTree || pTree2)
	{
		// If Mark already selected
		if (PAR_IsMarkSelected(i_x_NumMark) == 1)
			PAR_DeSelectMark(i_x_NumMark);

		// Mark memorization : value and node
		if (pTree2)
		{
			MarkList[IndexMarkList].NumMark = i_x_NumMark;
			MarkList[IndexMarkList++].ptr_node = pTree2;
		}
		if (pTree)
		{
			MarkList[IndexMarkList].NumMark = i_x_NumMark;
			MarkList[IndexMarkList++].ptr_node = pTree;
		}
		// Ok, mark found
		Result = 0;
	}

	return (Result);
}

#if 0
//===========================================================================
unsigned long PAR_SelectFatherMark(DataElementExt data)
{
	unsigned long tag;
	int           Result = 0;
	int           i_l_TagIndex = 0;
	unsigned int  nindex = 0, length;
	unsigned char * ptr_data;
	TLV_TREE_NODE pTree;
	unsigned long ul_l_FatherMarq = 0;

	// Initialization

	// Look for the tag in the pTreeAppli TLVTree
	do{
		pTree = TlvTree_Find(pTreeParam, data.elt.tag, nindex++);
		if (pTree != NULL) /* If a node has been obtain */
		{
			// Get tag data to check if it start with Mark_XXX
			length = TlvTree_GetLength(pTree);

			ptr_data = (unsigned char *)TlvTree_GetData(pTree);
			if ((length == data.elt.length) && (memcmp(ptr_data, data.elt.ptValue, length) == 0))
			{
				Result = 1;
			}
		}
	}while ((pTree != NULL) && (Result == 0));

	nindex = 0;
	
	// Looking for the mark in the default parameter TLV tree
	if (pTree == NULL)
	{
		do{
			pTree = TlvTree_Find(pTreeDefault, data.elt.tag, nindex++);
			if (pTree != NULL) /* If a node has been obtain */
			{
				// Get tag data to check if it start with Mark_XXX
				length = TlvTree_GetLength(pTree);
				// If check may be shorter than normal tag length
				if (uc_x_AllowShorterTag)
					if (length > data.elt.length)
						length = data.elt.length;
					else
						data.elt.length = length;

				ptr_data = (unsigned char *)TlvTree_GetData(pTree);
				if ((length == data.elt.length) && (memcmp(ptr_data, data.elt.ptValue, length) == 0))
				{
					Result = 1;
				}
			}
		}while ((pTree != NULL) && (Result == 0));
	}

	// If tag found
	if (Result == 1)
	{
		TLV_TREE_NODE pFatherNode;

		pFatherNode = pTree;
		// Up to find father mark
		do{
			pFatherNode = TlvTree_GetParent(pFatherNode);
			if (PAR_IsAMark(pFatherNode))
			{
				tag = TlvTree_GetTag(pFatherNode);
				// If ok
				if (PAR_SelectMark(tag, C_TREE_PARAM_FIRST) == 0)
				{
					ul_l_FatherMarq = tag;
				}
			}
		}while ((pFatherNode != NULL) && (ul_l_FatherMarq == 0));
	}
	return (ul_l_FatherMarq);
}
#endif /* 0 */

//===========================================================================
int PAR_DeSelectMark(unsigned int i_x_NumMark)
{
	int Result = 1;
	unsigned int nindex = 0;

	for (nindex = IndexMarkList; nindex > 0; nindex--)
	{
		if (MarkList[nindex-1].NumMark == i_x_NumMark)
		{
			MarkList[nindex-1].NumMark = 0;
			MarkList[nindex-1].ptr_node = 0;

			// Mark found
			Result = 0;
			break;
		}
	}

	// shift the mark list
	// If mark found
	if (Result == 0)
	{
		for (; nindex < IndexMarkList; nindex++)
		{
			// Shift of each mark in list
			MarkList[nindex-1].NumMark = MarkList[nindex].NumMark;
			MarkList[nindex-1].ptr_node= MarkList[nindex].ptr_node;
		}

		// Reset of last mark
		MarkList[nindex-1].NumMark   = 0;
		MarkList[nindex-1].ptr_node  = 0;
		IndexMarkList--;
	}

	return (Result);
}

//===========================================================================
int PAR_IsMarkSelected(unsigned int i_x_NumMark)
{
	// Init result to mark not found
	int Result = 0;
	unsigned int nindex = 0;

	for (nindex=0; nindex<C_NB_MAX_MARK; nindex++)
	{
		if (MarkList[nindex].NumMark == i_x_NumMark)
		{
			// Mark found
			Result = 1;
			break;
		}
	}

	return (Result);
}

//===========================================================================
int PAR_SelectNextMark(unsigned int i_x_NumMark, unsigned char uc_x_FirstAccess)
{
	int           Index;
	unsigned char IndexMarkChild = 0;
	int           Result = 0;
	int           i_l_Mark = 0;
	TLV_TREE_NODE pTree;

	Struct_Mark ChildMark[C_NB_MAX_MARK];
	TLV_TREE_NODE pBrother;


	pTree = PAR_FoundMark(i_x_NumMark);

	if (pTree != NULL)
	{
		pBrother = TlvTree_GetFirstChild(pTree);

		do {
			if (pBrother != NULL)
			{
				if (PAR_IsAMark(pBrother))
				{
					i_l_Mark = TlvTree_GetTag(pBrother);

					ChildMark[IndexMarkChild].NumMark = i_l_Mark;
					ChildMark[IndexMarkChild++].ptr_node = pBrother;
				}
				pBrother = TlvTree_GetNext(pBrother);
			}
		}while ((pBrother != NULL) && (IndexMarkChild < C_NB_MAX_MARK));


		// If a child was found
		if (IndexMarkChild)
		{
			// First access
			if (uc_x_FirstAccess)
			{
				i_l_Mark = ChildMark[0].NumMark;
				// Select first Mark child
				PAR_SelectMark(i_l_Mark, C_TREE_PARAM_FIRST);
				Result = i_l_Mark;
			}
			// If only 1 child is available
			else if (IndexMarkChild == 1)
			{
				// If DeSelect() ok
				if (PAR_DeSelectMark(i_l_Mark) == 0)
					Result = 1;
			}
			else for (Index = IndexMarkChild-1; Index>=0; Index--)
			{
				i_l_Mark = ChildMark[Index].NumMark;
				// If a child is selected
				if (PAR_IsMarkSelected(i_l_Mark))
				{
					// We can take the next mark
					// If DeSelect() ok
					if (PAR_DeSelectMark(i_l_Mark) == 0)
					{
						// Check if it wasn't the last child
						if ((Index+1) < IndexMarkChild)
						{
							i_l_Mark = ChildMark[Index+1].NumMark;
							if (PAR_SelectMark(i_l_Mark, C_TREE_PARAM_FIRST) == 0)
								Result = i_l_Mark;
						}
						break;	// Exit the loop
					}
				}
			}
		}
	}

	return (Result);
}

//===========================================================================
int PAR_DeleteMark(unsigned int i_x_NumMark)
{
	int           Result = 0;
	int           i_l_Mark = 0;
	TLV_TREE_NODE pTree, pChild;

	pTree = PAR_FoundMark(i_x_NumMark);

	if (pTree != NULL)
	{
		pChild = TlvTree_GetFirstChild(pTree);

		do {
			// Loop on each child
			if (pChild != NULL)
			{
				if (PAR_IsAMark(pChild))
				{
					i_l_Mark = TlvTree_GetTag(pChild);
					PAR_DeSelectMark(i_l_Mark);
				}
				pChild = TlvTree_GetNext(pChild);
			}
		}while (pChild != NULL);

		PAR_DeSelectMark(i_x_NumMark);

		// All is ok, we can delete the mark and all its children (if existing)
		TlvTree_Release(pTree);
	}

	return (Result);
}

//===========================================================================
int PAR_MarkAction(unsigned int i_x_NumMark, unsigned char y_x_ActionType)
{
	int result = 0;
	static unsigned int i_NumMark = 0;

	switch (y_x_ActionType)
	{
		case C_SELECT:
			result = PAR_SelectMark(i_x_NumMark, C_TREE_PARAM_FIRST);
			i_NumMark = 0;
			break;

		case C_UNSELECT:
			result = PAR_DeSelectMark(i_x_NumMark);
			i_NumMark = 0;
			break;

		case C_SELECT_NEXT_CHILD:
			{
				unsigned char uc_l_FistAccess = 0;

				if (i_NumMark != i_x_NumMark)
				{
					// Memorization for next call
					i_NumMark = i_x_NumMark;
					uc_l_FistAccess = 1;
				}

				if (PAR_SelectNextMark(i_x_NumMark, uc_l_FistAccess) == 0)
					result = 1;	// A problem occured
			}
			break;

		case C_UNSELECT_CHILD:
			{
				int  i_l_Mark;
				TLV_TREE_NODE pTree, pBrother;

				i_NumMark = 0;


				pTree = PAR_FoundMark(i_x_NumMark);

				if (pTree != NULL)
				{
					pBrother = TlvTree_GetFirstChild(pTree);

					do {
						if (pBrother != NULL)
						{
							if (PAR_IsAMark(pBrother))
							{
								i_l_Mark = TlvTree_GetTag(pBrother);
								PAR_DeSelectMark(i_l_Mark);
							}
							pBrother = TlvTree_GetNext(pBrother);
						}
					}while(pBrother != NULL);
				}
			}
			break;

		default:
			break;
	}

	return (result);
}

//===========================================================================
int PAR_MarkInfos(unsigned int i_x_NumMark)
{
	int result = 0;

	if (PAR_IsMarkSelected(i_x_NumMark))
	{
		result = C_MARK_ACTIVATED;
	}
	else
	{
		TLV_TREE_NODE pTree;

		pTree = PAR_FoundMark(i_x_NumMark);

		// If Mark found
		if (pTree)
			result = C_MARK_NO_ACTIVATED;
		else
			result = C_MARK_NOT_DEFINE;
	}

	return (result);
}

//===========================================================================
int PAR_ReadParameter(unsigned long tag, DataElementExt *data)
{
	int           Result = 0;
	int           i_l_TagIndex = 0;
	unsigned int  nindex = 0, length;
	unsigned char * ptr_data;
	TLV_TREE_NODE pTree;
	static unsigned char BoolValue;

	// Initialization
	data->elt.tag=0;
	data->elt.length=0;
	data->elt.ptValue = NULL;

	// Look for the tag in the pTreeAppli TLVTree
	do{
		pTree = TlvTree_Find(pTreeAppli, tag, nindex++);
		// If a node has been obtained
		if (pTree != NULL)
		{
			// Get tag data to check if it start with Mark_XXX
			length = TlvTree_GetLength(pTree);
			ptr_data = (unsigned char *)TlvTree_GetData(pTree);

			if (length < 5)
				Result = 1;
			else
			{
				// It isn't a mark
				if (strncmp((char *)ptr_data, "MARQ_", 5) != 0)
				{
					// memorize mark pointer
					Result = 1;
					break;
				}
			}
		}
	}while ((pTree != NULL) && (Result == 0));


	// If a tag was found
	if (pTree != NULL)
	{
		data->elt.tag=tag;
		data->elt.length=length;
		data->elt.ptValue=ptr_data;
	}
	else
		for (nindex = IndexMarkList; nindex > 0; nindex--)
		{
			/* MarkList[IndexMarkList].NumMark;  */
			/* MarkList[IndexMarkList].ptr_node;     */

			i_l_TagIndex = 0;
			do{
				pTree = TlvTree_Find(MarkList[nindex-1].ptr_node, tag, i_l_TagIndex++);
				if (pTree != NULL) /* If a node has been obtain */
				{
					// Read tag data to check if the node is a Mark (datas begining by Mark_XXX)
					length   = TlvTree_GetLength(pTree);
					if (length)
					{
						ptr_data = (unsigned char*)TlvTree_GetData(pTree);
						// It isn't a Mark
						if (strncmp((char *)ptr_data, "MARQ_", 5) != 0)
						{
							// Set tag informations
							data->elt.tag=tag;
							data->elt.length = length;
							data->elt.ptValue = ptr_data;
							// Ok
							Result = 1;
							// Stop the main loop
							nindex = 1;
							break;
						}
					}
				}
			}while ((pTree != NULL) && (Result == 0));
		}

		if (Result == 1)
			// If the parameter has the "YES" or "NO" value
			if (CUPAR_SetBooleanValue(data->elt.ptValue, &BoolValue) == TRUE)
			{
				/*data->elt.tag=tag; no modification */
				data->elt.length = 1;
				data->elt.ptValue = &BoolValue;
			}

			return (Result);
}

//===========================================================================
void PAR_ReadParameterListTLVTree(const unsigned long cst_tag_list[], unsigned int i_x_NbTag, TLV_TREE_NODE *p_TLV_Tree)
{
	DataElement elt;
	int found;
	unsigned int TagIndex;

	for (TagIndex=0; TagIndex<i_x_NbTag; TagIndex++)
	{
		found = PAR_ReadParameter(cst_tag_list[TagIndex], (DataElementExt *)&elt);
		if (found)
			TlvTree_AddChild(*p_TLV_Tree, elt.tag, elt.ptValue, elt.length);
	}
}

//===========================================================================
int PAR_SetParameter(unsigned long tag, DataElementExt data)
{
	int Result = 0;
	unsigned int nindex = 0, length;

	TLV_TREE_NODE pTree;
	unsigned char * ptr_data;

	// Look for the tag in the pTreeAppli TLVTree
	do{
		pTree = TlvTree_Find(pTreeAppli, data.elt.tag, nindex++);
		// If a node has been obtained
		if (pTree != NULL)
		{
			// Get tag data to check if it start with Mark_XXX
			length = TlvTree_GetLength(pTree);
			if (length < 5)
				Result = 1;
			else
			{
				ptr_data = (unsigned char *)TlvTree_GetData(pTree);
				// It isn't a Mark
				if (strncmp((char *)ptr_data, "MARQ_", 5) != 0)
				{
					// Memorize mark pointer
					Result = 1;
					break;
				}
			}
		}
	}while ((pTree != NULL) && (Result == 0));


	// If tag found
	if (pTree != NULL)
	{
		// Update tag
		TlvTree_SetData(pTree, data.elt.ptValue, data.elt.length);
		Result = 1;
	}
	else	// Tag to create
	{
		// Create tag
		pTree = TlvTree_AddChild(pTreeAppli, data.elt.tag, data.elt.ptValue, data.elt.length);
		if (pTree != NULL)
			Result = 1;	// No problem
		else
			Result = 0; // a problem occured during update of pTree

	}

	return (Result);
}

//===========================================================================
void CUPAR_Print_Param_Supported(TLV_TREE_NODE pnode, char *ptr_x_DataName, unsigned int i_x_Mark, unsigned char c_x_tracetype, unsigned long ul_x_tag)
{
    char text[300];
	unsigned char * ptr_data;
	TLV_TREE_NODE hnode;
	TLV_TREE_NODE pNode;

	// If the whole TLV tree must be traced
	if (i_x_Mark == 0)
		hnode = pnode;
	else
		hnode = PAR_FoundMarkInTree(pnode, i_x_Mark);

	sprintf ((char *) text, "%s", ptr_x_DataName);
	CUTERMprintLine((char *)text);


	// If main Mark has been found
	if (hnode != NULL)
	{
		// Display all the nodes and children under the mark given
		pNode = hnode;

		pNode = TlvTree_Iterate(pNode, hnode);

		while( pNode != NULL )
		{   
			ptr_data = (unsigned char *)TlvTree_GetData(pNode);

			switch (c_x_tracetype)
			{
				case C_TRACE_ONE_TAG :
					if (TlvTree_GetTag(pNode) != ul_x_tag)
						break;
					/* else
					break; */ /* Pas de break volontaire */

				case C_TRACE_WITHOUT_MARK:
					if (c_x_tracetype == C_TRACE_WITHOUT_MARK)
					{
						if (TlvTree_GetLength(pNode) > 5) 
							if (strncmp((char*)TlvTree_GetData(pNode), "MARQ_", 5) == 0)
							{
								break;
							}
					}

				case C_TRACE_ALL_CHILD:
                sprintf(text, "T:%04X L:%02X V:", TlvTree_GetTag(pNode), TlvTree_GetLength(pNode)); 
					CUTERMprintLine((char *)text);
					HexToAscii ((char*)TlvTree_GetData(pNode), TlvTree_GetLength(pNode), (unsigned char*)text);
					CUTERMprintLine((char *)text);
					break;

				case C_TRACE_MARK:
					if (TlvTree_GetLength(pNode) > 5) 
					{
						if (strncmp((char*)TlvTree_GetData(pNode), "MARQ_", 5) == 0)
						{
							sprintf(text, "tag %08x", TlvTree_GetTag(pNode));
							CUTERMprintLine((char *)text);
						}
					}
					break;

				default: /* No treatment */
					break;

			}
			pNode = TlvTree_Iterate(pNode, hnode);
		} /* End while on Node */
	}

	CUTERMpaperFeed();
}

//===========================================================================
int PAR_ascii2bytes(unsigned char *str, unsigned char *dest)
{
	int len;				// string length
	int StrIndex;
	unsigned char value;

	len = strlen((char*)str);

	for (StrIndex=0; StrIndex<len; StrIndex++)
	{
		if (CUPAR_ascii2digit (str[StrIndex],&value) != 0)
			return FALSE;

		if ((StrIndex % 2) == 0)
		{
			value <<= 4;
			dest[StrIndex/2] = value;
		}
		else
		{
			dest[StrIndex/2] += value;
		}
	}

	return TRUE;
}

//===========================================================================
//! \brief This function sets the boolean given as output parameter according 
//! to the value of input parameter 'value': 
//! - if value equals NO pBool is set to 0.
//! - if value equals YES pBool is set to 1.
//! - for other values of value pBool is set to 0.
//! \param[in] value : string to test.
//! \param[out] pBool : boolean to set.
//! \return
//! - TRUE if value equals YES or NO.
//! - FALSE otherwise.
//===========================================================================
static int CUPAR_SetBooleanValue (unsigned char *value, unsigned char *pBool)
{
	int iRet;

	iRet = TRUE;
	if (strcmp((char*)value, NO) == 0)
	{
		*pBool = 0;
	}
	else
	{
		// YES
		if (strcmp((char*)value, YES) == 0)
		{
			*pBool = 1;
		}
		// ERROR
		else
		{
			*pBool = 0;
			iRet = FALSE;
		}
	}
	return (iRet);
}

//===========================================================================
int CUPAR_ReadTextParamFile (TLV_TREE_NODE * ptr_pTree,
							 unsigned int i_x_tag,
							 char * ptr_x_tagMark,
							 char *fileName)
{
	unsigned char  IndexpNode; /* Index on array */
	char           value[600];
	char           buf[MAX_FILE_LG];
	char           *pValue;
	int            lg, index;
	int            len;
	int            result = 0;
	int            i_l_IndexTagArray;
	unsigned long  tag;
	unsigned long  size_max;
	unsigned long  i_l_TagArray[50];
	S_FS_FILE      *file1;
	TLV_TREE_NODE  pNode, pNodeResult;
	unsigned int   Mode,rc;
	unsigned char  uc_l_trace[60];

	memset (buf, 0, MAX_FILE_LG);
	index=0;

	tag=0; len=0;
	i_l_IndexTagArray = 0;


	memset(i_l_TagArray, 0, sizeof(i_l_TagArray));

	// Open input file
	Mode = FS_READMOD;
	rc= FS_mount (fileName,&Mode);
	if (rc != FS_OK)
	{
		upload_diagnostic_txt((unsigned char *)"PB Mount COM Filen\n");
	}

	file1 = FS_open (fileName, "r");
	if (file1 == NULL)
	{
		sprintf(uc_l_trace, "FS_open(%s) ko\n", fileName);
		upload_diagnostic_txt((unsigned char *)uc_l_trace);
		// Problem with file
		result = 1;
	}
	else
	{
		// Offset = 0
		FS_seek (file1, 0, FS_SEEKSET);

		pValue = value;
		size_max = sizeof(value);

		// Set tag Mark as node in the TLVTree
		pNodeResult = TlvTree_AddChildString( *ptr_pTree, i_x_tag++, ptr_x_tagMark);
		pNode = pNodeResult;

		// Init index on array
		IndexpNode = 0;

		// Loop on each line of input file
		while (((lg = FS_read (&buf, 1, MAX_FILE_LG, file1)) != 0) && (pNodeResult != 0))
		{
			//            lg++;
			// Loop on each element on the file line
			while (CUPAR_read_next_element_text (buf, lg, &index, size_max, &tag, &len, pValue) == TRUE)
			{
				if (len != 0)
				{
					// Check, if the same tag has been inputed
					int index;
					for (index=0; index<i_l_IndexTagArray; index++)
					{
						if (i_l_TagArray[index] == tag)
							break;
					}
					// If tag has been allready inputed
					if (index != i_l_IndexTagArray)
					{
						// Create a new set of parameters
						// Set tag Mark as node in the TLVTree
						pNodeResult = TlvTree_AddChildString( *ptr_pTree, i_x_tag++, ptr_x_tagMark);
						pNode = pNodeResult;
						i_l_IndexTagArray = 0;
					}

					i_l_TagArray[i_l_IndexTagArray++] = tag;

					// Store an element as a child in the TLVTree
					{

						// if data is in hexa
						if (IsBuffAscii((unsigned char)strlen(pValue), pValue) == TRUE)
						{
							unsigned char ac_l_HexaValue[300];

							// Ascii -> hexa process
							PAR_ascii2bytes((unsigned char*)pValue, ac_l_HexaValue); // Return allways TRUE
							TlvTree_AddChild(pNode, tag, ac_l_HexaValue, strlen(pValue)/2);
						}
						else
						{
							TlvTree_AddChildString( pNode, tag, (const char *)pValue);
						}
					}
				}
			}
		}
		// Close input file
		FS_close(file1);

		if (pNodeResult == NULL)
			result = 1;		// Problem in TLVTree

	}

	return (result);
}

//===========================================================================
//! \brief This function tests if the character given as input parameter is 
//! an ascii character. ( '0' <= car <= '9' or 'a' <= car <= 'z' or 'A'<= car <= 'Z'.
//! \param[in] car : byte to test.
//! \return
//! - TRUE if car is an ascii character.
//! - FALSE otherwise.
//===========================================================================
static unsigned char IsAscii(char car)
{
	if ( ((car >= '0') && (car <= '9')) ||
		((car >= 'A') && (car <= 'F')) ||
		((car >= 'a') && (car <= 'f')) )
		return (TRUE);

	return(FALSE);
}

//===========================================================================
//! \brief This function tests if all characters of the buffer given as input 
//! parameter are ascii characters. ('0' <= ptr_x_car[i] <= '9' or 
//! 'a' <= ptr_x_car[i] <= 'z' or 'A'<= ptr_x_car[i] <= 'Z').
//! \param[in] u_x_len : buffer length.
//! \param[in] ptr_x_car : buffer to test.
//! \return
//! - TRUE if all characters of the input buffer are ascii characters.
//! - FALSE otherwise.
//===========================================================================
static unsigned char IsBuffAscii(unsigned char u_x_len, char * ptr_x_car)
{
	unsigned char uc_l_Indexchar;

	for (uc_l_Indexchar=0; uc_l_Indexchar<u_x_len; uc_l_Indexchar++)
		if(!IsAscii(ptr_x_car[uc_l_Indexchar]))
			return (FALSE);

	return (TRUE);
}

//===========================================================================
int CUPAR_read_next_element_text (char *buf,
								  int lg,
								  int *i_x_index,
								  int max_len,
								  unsigned long *tag,
								  int *length,
								  char *value)
{
	char car;
	unsigned char digit;
	int successfull;
	static int idxValue;
	static int state;
	static int finish = FALSE;
	static int tag_type = 0;			// Tag is an hexa type


	// Initialise element values
	// if First call
	if (*i_x_index == 0)
	{
		finish = FALSE;
	}

	// No stop during previous value access
	if (finish == FALSE)
	{
		*tag = 0;
		*length = 0;
		memset (value, 0, max_len);
		idxValue=0;
		state = TAG_READING;
		// Tag is an Ascii type
		tag_type = 0;
	}
	else
	{
		*i_x_index = 0;
	}

	car = 0;
	finish = FALSE;
	successfull = FALSE;


	// Reading characters loop
	while ((buf[*i_x_index] != ';') && (*i_x_index < lg) && !finish)
	{
		// Read one character
		car = buf[*i_x_index];
		if (car == '=')
		{   
			//  Tag / Value separator
			if (state == TAG_READING)
			{
				int index;
				state = VALUE_READING;
				for (index=1+*i_x_index; (index<lg) && (buf[index] != ';'); index++)
					if (!IsAscii(buf[index]) && (buf[index] != ' '))
					{
						tag_type = 1;
						break;
					}
			}
		}
		else if ( car == '#' )
		{
			// it's a comment
			while (buf[*i_x_index] != '\n')
			{
				(*i_x_index)++;
			}
			(*i_x_index)--;
		}
		else  // if (tag_type == 0)		// If tag_type is hexa
		{
			if (state == TAG_READING)
			{   
				// Append value to tag
				if (CUPAR_ascii2digit(car,&digit) == 0)
				{
					// Hexadecimal value
					(*tag) <<= 4;
					(*tag) += digit;
				}
			}
			else if (((tag_type == 0) && (car != ' ')) || (tag_type == 1))
			{
				// Add one nibble to the value
				value[idxValue++] = car;
				(*length)++;

				if (idxValue >= max_len)
				{
					finish = TRUE;
				}
			}
		}
		(*i_x_index)++;
	}	// End of the loop


	// If something was read
	if ((*i_x_index < lg) && (finish == FALSE))
	{
		successfull = TRUE;
		// Stop the text
		value[idxValue] = 0;
	}

	// To memorise information
	if (*i_x_index == lg)
	{
		finish = TRUE;
	}

	(*i_x_index)++;
	return (successfull);
}

//===========================================================================
//! \brief This function converts an ascii character given as input parameter 
//! to its binary value.
//! \param[in] car : byte to to convert.
//! \param[out] digit : binary value (0..F).
//! \return
//! - 0 if successfull.
//! - -1 otherwise.
//===========================================================================
static int CUPAR_ascii2digit (char car,unsigned char *digit)
{
	int cr;

	cr=0;
	(*digit)=0;
	if (( car >= '0' ) && (car <= '9'))
	{
		(*digit)=car-'0';
	}
	else if ((car>='A') && (car<='F'))
	{
		(*digit)=car-'A'+0xA;
	}
	else if ((car>='a') && (car<='f'))
	{
		(*digit)=car-'a'+0xa;
	}
	else
		cr=-1;
	return cr;
}

//===========================================================================
int CUPAR_Tag_Dump(unsigned int  i_x_NumMark)
{
	int result = 1;
	TLV_TREE_NODE pTree;
	unsigned long dummy = 0;

	pTree = PAR_FoundMark(i_x_NumMark);

	if (pTree)
	{
		result = 0;
		CUPAR_Print_Param_Supported(pTree, "Tag dump :", i_x_NumMark, C_TRACE_WITHOUT_MARK, dummy);
	}

	return (result);
}

//===========================================================================
int CUPAR_TLVTree_Dump(unsigned int i_x_TreeType)
{
	TLV_TREE_NODE pTree=0;
	int result = 1;
	unsigned long dummy = 0;
	unsigned int  i_l_NumMark = 0;			// Unused

	switch(i_x_TreeType)
	{
		case C_TREE_APPLI:
			pTree = pTreeAppli;
			break;
		case C_TREE_DEFAULT:
			pTree = pTreeDefault;
			break;
		case C_TREE_PARAM:
			pTree = pTreeParam;
			break;
		default:
			break;
	}

	if (pTree)
	{
		result = 0;
		CUPAR_Print_Param_Supported(pTree, "Tag dump :", i_l_NumMark, C_TRACE_WITHOUT_MARK, dummy);
	}

	return (result);
}

//! @}

