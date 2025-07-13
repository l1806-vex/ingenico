//! Module that manages the terminal flash file management.
//
/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"

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

static int _ClessSample_BlackListLoad(const char* szPath, const char* szFile);
static int _ClessSample_BlackListSave(const char* szPath, const char* szFile);

//// Functions //////////////////////////////////////////////////

//! \brief Black list initialisation with global variables reset.
//! \return
//!		- Nothing.
void ClessSample_BlackListInit(void)
{
	g_nBlackListSize = 0;
	memset(g_BlackList, 0, sizeof(g_BlackList));
}

//! \brief Delete the black list.
//! \return
//!		- Nothing.
void ClessSample_BlackListDelete(void)
{
	unlink("/" FILE_DISK_LABEL "/" BLACK_LIST_FILE_NAME);
	ClessSample_BlackListInit();
}

//! \brief Load a black list file in memory.
//! \param[in] szPath file path for the black list file.
//! \param[in] szfile file name for the black list file.
//! \return
//!		- TRUE if a black list file has been loaded, FALSE else.
static int _ClessSample_BlackListLoad(const char* szPath, const char* szFile)
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

	ClessSample_BlackListInit();
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
		ClessSample_BlackListInit();

#ifdef __TRACE_DEBUG__
	if (bResult)
		TraceDebug("Blacklist loaded");
	else TraceDebug("Blacklist not loaded");
#endif

	if (rc == FS_OK)
		FS_unmount(szFullFileName);
	
	return bResult;
}

//! \brief Load a black list file in memory with the default .
//! \return
//!		- TRUE if a black list file has been loaded, FALSE else.
int ClessSample_BlackListLoad(void)
{
	return _ClessSample_BlackListLoad(FILE_DISK_LABEL, BLACK_LIST_FILE_NAME);
}

//! \brief Load a black list file in memory.
//! \param[in] szPath file path for the black list file.
//! \param[in] szfile file name for the black list file.
//! \return
//!		- TRUE if a black list file has been loaded, FALSE else.
int ClessSample_BlackListGetNewFile(const char* szPath, const char* szFile)
{
	int bResult;

	if (strcmp(szFile, "CLESSBLACK.PAR") == 0)
	{
		// File has been received
		bResult = FALSE;
		if (ClessSample_Disk_Mount(szPath) == FS_OK)
		{
			if (_ClessSample_BlackListLoad(szPath, szFile))
			{
				if (ClessSample_BlackListSave())
				{
					bResult = ClessSample_BlackListLoad();
				}
				else ClessSample_BlackListLoad();
			}
			else ClessSample_BlackListLoad();
	
			ClessSample_Disk_Unmount(szPath);
		}
		
		if (bResult)
			GTL_Traces_DiagnosticText ("BlackList updated\n");
		else
			GTL_Traces_DiagnosticText ("Error in BlackList\n");

		return (STOP);
	}
	else
		return (FCT_OK);
}

//! \brief Save a black list in a file.
//! \param[in] szPath file path for the black list file.
//! \param[in] szfile file name for the black list file.
//! \return
//!		- TRUE if the black list file has been correctly updated, FALSE else.
static int _ClessSample_BlackListSave(const char* szPath, const char* szFile)
{
	int bResult;
	S_FS_FILE* hFile;
	char szFullFileName[1 + FS_DISKNAMESIZE + 1 + FS_FILENAMESIZE + 1];
	int i;
	char* pBuffer;
	char* pPtr;
	unsigned int Mode, rc;

	sprintf(szFullFileName, "/%s/%s", szPath, szFile);

	bResult = FALSE;

#ifdef __TRACE_DEBUG__
	TraceDebug("Delete blacklist \"%s\"", szFullFileName);
#endif

	Mode = FS_WRTMOD;
	rc = FS_mount(szFullFileName, &Mode);
	if (rc != FS_OK)
	{
		GTL_Traces_DiagnosticText("PB Mount BlackList File\n");
	}

	FS_unlink(szFullFileName);
	
	hFile = FS_open(szFullFileName, "a");
	if (hFile != NULL)
	{
		pBuffer = umalloc(g_nBlackListSize * 30 + 1);
		if (pBuffer != NULL)
		{
			memset(pBuffer, 0, g_nBlackListSize * 30 + 1);

			pPtr = pBuffer;
			for(i = 0; i < g_nBlackListSize; i++)
			{
				if (g_BlackList[i].m_nPanSeqNumber >= 0)
					pPtr += sprintf(pPtr, "%s,%d\n", g_BlackList[i].m_Pan, g_BlackList[i].m_nPanSeqNumber);
				else pPtr += sprintf(pPtr, "%s\n", g_BlackList[i].m_Pan);
			}

			if (pPtr != pBuffer)
			{
				if (FS_write(pBuffer, 1, pPtr - pBuffer, hFile) == pPtr - pBuffer)
					bResult = TRUE;
			}

			ufree(pBuffer);
		}

		// Close the file
		FS_close(hFile);
	}

	if (rc == FS_OK)
		FS_unmount(szFullFileName);
	
	if (!bResult)
		ClessSample_BlackListInit();

	return bResult;
}

//! \brief Save a black list in a default file.
//! \return
//!		- TRUE if the black list file has been correctly updated, FALSE else.
int ClessSample_BlackListSave(void)
{
	return _ClessSample_BlackListSave(FILE_DISK_LABEL, BLACK_LIST_FILE_NAME);
}

//! \brief Check if a Pan + PanSeqNumber is in the black list.
//! This function must be used with an ASCII PAN number and PAN Sequence Number.
//! \param[in] szPan card Pan number.
//! \param[in] nPanSeqNumber card Pan Sequence Number.
//! \return
//!		- TRUE if the Pan + PanSeqNumber is in the Black List, FALSE else.
int ClessSample_BlackListIsPanAscii(const char* szPan, int nPanSeqNumber)
{
	int bFound;
	int i;

	if (strlen(szPan) > 19)
		return FALSE;

	bFound = FALSE;
	i = 0;
	while((!bFound) && (i < g_nBlackListSize))
	{
		if (strcmp(g_BlackList[i].m_Pan, szPan) == 0)		// If Pan found
		{
			// If PanSeqNumber card isn't present 
			if (nPanSeqNumber == C_CLESS_VOID_PAN_SEQ_NUMBER)
			{
				if (g_BlackList[i].m_nPanSeqNumber == -1) // => PanSeqNumber from Blacklist mustn't be present (-1)
					bFound = TRUE;
			}
			// PanSeqNumber card is present : PanSeqNumber from BlackList must be dummy or must match
			else if ((g_BlackList[i].m_nPanSeqNumber == -1) || (g_BlackList[i].m_nPanSeqNumber == nPanSeqNumber))
				bFound = TRUE;
		}
		i++;
	}

#ifdef __TRACE_DEBUG__
	if (bFound)
		TraceDebug("PAN %s / %d is found", szPan, nPanSeqNumber);
	else TraceDebug("PAN %s / %d is not found", szPan, nPanSeqNumber);
#endif

	return bFound;
}

//! \brief Check if a Pan + PanSeqNumber is in the black list.
//! \param[in] szPan card Pan number.
//! \param[in] nPanSeqNumber card Pan Sequence Number.
//! \return
//!		- TRUE if the Pan + PanSeqNumber is in the Black List, FALSE else.
int ClessSample_BlackListIsPan(int nLength, const unsigned char* pPan, int nPanSeqNumber)
{
	char szPan[19 + 1];
	int i;
	int bEnd;

	if (nLength > 10)
		return FALSE;

#ifdef __TRACE_DEBUG__
	TraceDebugBuffer(nLength, pPan, "Searching for PAN");
#endif

	memset(szPan, 0, sizeof(szPan));

	for(i = 0; i < nLength; i++)
	{
		szPan[i * 2] = (((*(pPan + i)) & 0xf0) >> 4) + '0';
		szPan[(i * 2) + 1] = (((*(pPan + i)) & 0x0f)) + '0';
	}

	i = nLength * 2;
	bEnd = FALSE;
	while((!bEnd) && (i > 0))
	{
		if (szPan[i - 1] == '0' + 0xf)
		{
			szPan[i - 1] = '\0';
			i--;
		}
		else bEnd = TRUE;
	}

#ifdef __TRACE_DEBUG__
	TraceDebug("  PAN=%s", szPan);
#endif

	return ClessSample_BlackListIsPanAscii(szPan, nPanSeqNumber);
}


//! \brief Check if a Black list has been loaded.
//! \return
//!		- TRUE if a black list with at least one element is loaded.
int ClessSample_IsBlackListPresent(void)
{
	int nResult = FALSE;

	if (g_nBlackListSize > 1)   					// If something in black list
		nResult = TRUE;
	
	if (g_nBlackListSize == 1)
	{
		int nIndex;
		
		for (nIndex=0; nIndex<20; nIndex++)
		{
			if ((g_BlackList[0].m_Pan[nIndex] != 0) 	// If something in first array
			 && (g_BlackList[0].m_Pan[nIndex] != '0')) 	// If something in first array
			{
				nResult = TRUE;
				break;
			}
		}
	}
	
	return (nResult);
}

