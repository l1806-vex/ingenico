/**
 * \file	CST_BlackList.c
 * \brief	Module that manages the black list.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "CST_Implementation.h"


//// Macros & preprocessor definitions //////////////////////////

#define BLACK_LIST_MAX_SIZE		128
#define BLACK_LIST_FILE_NAME	"BLACKLIST.PAR"



//// Types //////////////////////////////////////////////////////

typedef struct
{
	char m_Pan[19 + 1];
	int m_nPanSeqNumber;
} T_BLACK_LIST_ENTRY;



//// Global variables ///////////////////////////////////////////

static T_BLACK_LIST_ENTRY g_BlackList[BLACK_LIST_MAX_SIZE];
static int g_nBlackListSize;



//// Static function definitions ////////////////////////////////

static int __CST_BlackListLoad(const char* szPath, const char* szFile);
static int __CST_BlackListCopyInTLVTree(TLV_TREE_NODE * pTree);



//// Functions //////////////////////////////////////////////////

//! \brief Black list initialisation with global variables reset.
//! \return
//!		- Nothing.

void CST_BlackListInit(void)
{
	g_nBlackListSize = 0;
	memset(&g_BlackList, 0, sizeof(g_BlackList));
}


//! \brief Load a black list file in memory.
//! \param[in] szPath file path for the black list file.
//! \param[in] szfile file name for the black list file.
//! \return
//!		- TRUE if a black list file has been loaded, FALSE else.

static int __CST_BlackListLoad(const char* szPath, const char* szFile)
{
	int bResult;
	S_FS_FILE* hFile;
	char szFullFileName[1 + FS_DISKNAMESIZE + 1 + FS_FILENAMESIZE + 1];
	char* pBuffer;
	const char* pPtr;
	const char* pPtrEndLine;
	unsigned long i;
	unsigned long ulFileSize;
	unsigned int Mode, rc;

	CST_BlackListInit();
	sprintf(szFullFileName, "/%s/%s", szPath, szFile);

	bResult = FALSE;

#ifdef __TRACE_DEBUG__
	TraceDebug("Loading blacklist \"%s\"...", szFullFileName);
#endif

	
	Mode = FS_READMOD;
	rc = FS_mount(szFullFileName, &Mode);
	if (rc != FS_OK)
	{
		GTL_Traces_DiagnosticText("PB Mount BlackList File\n");
	} 
	
	hFile = FS_open(szFullFileName, "r");
	if (hFile != NULL)
	{
		// Get the size of the file
		ulFileSize = FS_length(hFile);
#ifdef __TRACE_DEBUG__
		TraceDebug("File size = %lu", ulFileSize);
#endif

		pBuffer = umalloc(ulFileSize + 1);
		if (pBuffer != NULL)
		{
			if (FS_read(pBuffer, 1, ulFileSize, hFile) == (int)ulFileSize)
			{
#ifdef __TRACE_DEBUG__
				TraceDebugBuffer(ulFileSize, pBuffer, "FS_read=>");
#endif
				pPtr = pBuffer;
				i = 0;
				bResult = TRUE;
				do
				{
					// Search start of line
					while((i < ulFileSize) && ((*pPtr == '\n') || (*pPtr == '\r') || (*pPtr == ' ') || (*pPtr == '\t')))
					{
#ifdef __TRACE_DEBUG__
						TraceDebug("Skip char 0x%02X", *pPtr);
#endif
						i++;
						pPtr++;
					}

					if (i < ulFileSize)
					{
						// Search end of the PAN
						pPtrEndLine = pPtr;
						while((i < ulFileSize) && (((*pPtrEndLine >= '0') && (*pPtrEndLine <= '9')) || (*pPtrEndLine == '?')))
						{
							i++;
							pPtrEndLine++;
						}

						if ((pPtrEndLine != pPtr) && (pPtrEndLine - pPtr <= 19))
						{
							// Add the black list entry
							memset(&g_BlackList[g_nBlackListSize], 0, sizeof(g_BlackList[g_nBlackListSize]));
							memcpy(g_BlackList[g_nBlackListSize].m_Pan, pPtr, pPtrEndLine - pPtr);

							if (*pPtrEndLine == ',')
							{
								// Search the PAN Sequence Number
								i++;
								pPtrEndLine++;

								pPtr = pPtrEndLine;
								g_BlackList[g_nBlackListSize].m_nPanSeqNumber = 0;
								while((i < ulFileSize) && ((*pPtrEndLine >= '0') && (*pPtrEndLine <= '9')))
								{
									g_BlackList[g_nBlackListSize].m_nPanSeqNumber =
										g_BlackList[g_nBlackListSize].m_nPanSeqNumber * 10 + (*pPtrEndLine - '0');

									i++;
									pPtrEndLine++;
								}
#ifdef __TRACE_DEBUG__
								TraceDebug("Add PAN %s with seq number %d", g_BlackList[g_nBlackListSize].m_Pan, g_BlackList[g_nBlackListSize].m_nPanSeqNumber);
#endif
							}
							else
							{
								g_BlackList[g_nBlackListSize].m_nPanSeqNumber = -1;
#ifdef __TRACE_DEBUG__
								TraceDebug("Add PAN %s", g_BlackList[g_nBlackListSize].m_Pan);
#endif
							}

							g_nBlackListSize++;
							pPtr = pPtrEndLine;
						}
						else
						{
							// Invalid character or PAN too long => error
#ifdef __TRACE_DEBUG__
							TraceDebug("Error:");
							if (pPtrEndLine == pPtr)
								TraceDebug("Invalid character!");
							if (pPtrEndLine - pPtr > 19)
								TraceDebug("PAN too long!");
#endif
							bResult = FALSE;
						}
					}
				} while((bResult) && (i < ulFileSize) && (g_nBlackListSize < BLACK_LIST_MAX_SIZE));

				if (i < ulFileSize)
				{
#ifdef __TRACE_DEBUG__
					TraceDebug("The file is not parsed entirely %lu / %lu", i, ulFileSize);
#endif
					bResult = FALSE;
				}
			}
#ifdef __TRACE_DEBUG__
			else TraceDebug("FS_read error");
#endif

			ufree(pBuffer);
		}
#ifdef __TRACE_DEBUG__
		else TraceDebug("umalloc error");
#endif

		// Close the file
		FS_close(hFile);
	}
#ifdef __TRACE_DEBUG__
	else TraceDebug("Cannot open blacklist");
#endif

	if (!bResult)
		CST_BlackListInit();

#ifdef __TRACE_DEBUG__
	if (bResult)
		TraceDebug("Blacklist loaded");
	else TraceDebug("Blacklist not loaded");
#endif

	if (rc == FS_OK)
		FS_unmount(szFullFileName);
	
	return bResult;
}


//! \brief Read a black list file and store it into an internal TLV tree structure.
//! \param[in] szPath file path for the black list file.
//! \param[in] szfile file name for the black list file.
//! \param[out] pTree TLV tree structure.
//! \return
//!		- TRUE if a black list file has been loaded, FALSE else.

int CST_BlackListGetNewFile(const char* szPath, const char* szFile, TLV_TREE_NODE * pTree)
{
	int bResult;

	bResult = FALSE;

	if (strcmp(szFile, "CLESSBLACK.PAR") == 0)
	{
		// File has been received
		if (CST_Disk_Mount(szPath) == FS_OK)
		{
			if (__CST_BlackListLoad(szPath, szFile))
			{
				bResult = __CST_BlackListCopyInTLVTree(pTree);
			}
			CST_Disk_Unmount(szPath);
		}		
	}

	if (bResult)
		GTL_Traces_TraceDebug ("BlackList updated\n");
	else
		GTL_Traces_TraceDebug ("Error in BlackList\n");

	return (bResult);
}


//! \brief Copy black list in a TLV Tree.
//! \return
//!		- TRUE if the black list file has been correctly copied, FALSE else.

static int __CST_BlackListCopyInTLVTree(TLV_TREE_NODE * pTree)
{
	int i;

	*pTree = TlvTree_New(TAG_SDSA_BLACKLIST_FILE_NODE);

	if(pTree != NULL)
	{
		for(i=0;i<g_nBlackListSize;i++)
		{
			TlvTree_AddChild(*pTree, TAG_EMV_APPLI_PAN, g_BlackList[i].m_Pan, sizeof(g_BlackList[i].m_Pan));
			TlvTree_AddChild(*pTree, TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER, &(g_BlackList[i].m_nPanSeqNumber), sizeof(g_BlackList[i].m_nPanSeqNumber));
		}
		return (TRUE);
	}
	return (FALSE);
}
