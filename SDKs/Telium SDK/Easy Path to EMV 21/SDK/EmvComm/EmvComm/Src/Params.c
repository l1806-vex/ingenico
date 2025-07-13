/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "TlvTree.h"

#include "Disk.h"
#include "Params.h"

//// Macros & preprocessor definitions //////////////////////////

#define PARAMS_DEFAULT_COM_PORT								(0)
#define PARAMS_DEFAULT_COM_BAUDRATE							(9600)

#define PARAMS_DEFAULT_FIRST_CHARACTER_RECEIVE_TIMEOUT		(6000)		// 60 seconds
#define PARAMS_DEFAULT_NEXT_CHARACTERS_RECEIVE_TIMEOUT		(2000)		// 20 seconds

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

//// Global variables ///////////////////////////////////////////

static const char g_szParamsFileName[] = "EMVCOMM.PAR";

static int g_nParamsComPort;
static int g_nParamsComBaudrate;
static unsigned long g_nFirstCharTimeout;
static unsigned long g_nNextCharTimeout;

//// Functions //////////////////////////////////////////////////

void Params_FirstInit(void)
{
	g_nParamsComPort = PARAMS_DEFAULT_COM_PORT;
	g_nParamsComBaudrate = PARAMS_DEFAULT_COM_BAUDRATE;
	g_nFirstCharTimeout = PARAMS_DEFAULT_FIRST_CHARACTER_RECEIVE_TIMEOUT;
	g_nNextCharTimeout = PARAMS_DEFAULT_NEXT_CHARACTERS_RECEIVE_TIMEOUT;
}

void Params_Load(void)
{
	int bError;
	TLV_TREE_NODE hParamsTlvTree;
	TLV_TREE_NODE hNode;
	char szFileName[FS_PATHSIZE + 1];
	S_FS_FILE* hFile;
	unsigned long ulFileSize;
	unsigned char* pFileContent;
	const unsigned char* pValue;

	g_nParamsComPort = PARAMS_DEFAULT_COM_PORT;
	g_nParamsComBaudrate = PARAMS_DEFAULT_COM_BAUDRATE;
	g_nFirstCharTimeout = PARAMS_DEFAULT_FIRST_CHARACTER_RECEIVE_TIMEOUT;
	g_nNextCharTimeout = PARAMS_DEFAULT_NEXT_CHARACTERS_RECEIVE_TIMEOUT;

	if (Disk_OpenEmvCommDisk())
	{
		bError = TRUE;

		sprintf(szFileName, "/%s/%s", EMVCOMM_DISK_LABEL, g_szParamsFileName);
		hFile = FS_open(szFileName, "r");
		if (hFile != NULL)
		{
			ulFileSize = FS_length(hFile);
			if (ulFileSize != (unsigned long)FS_ERROR)
			{
				pFileContent = umalloc(ulFileSize);
				if (pFileContent != NULL)
				{
					if (FS_read(pFileContent, ulFileSize, 1, hFile) == 1)
					{
						hParamsTlvTree = NULL;
						if (TlvTree_Unserialize(&hParamsTlvTree, TLV_TREE_SERIALIZER_DEFAULT, pFileContent, ulFileSize) == TLV_TREE_OK)
						{
							if (hParamsTlvTree != NULL)
							{
								if (TlvTree_GetTag(hParamsTlvTree) == TAG_EMV_COMM_PARAMS)
								{
									bError = FALSE;
									
									hNode = TlvTree_GetFirstChild(hParamsTlvTree);
									while(hNode != NULL)
									{
										switch(TlvTree_GetTag(hNode))
										{
										case TAG_EMV_COMM_PORT:
											if ((TlvTree_GetLength(hNode) == 1) && (TlvTree_GetData(hNode) != NULL))
												g_nParamsComPort = *(signed char*)TlvTree_GetData(hNode);
											break;
										case TAG_EMV_COMM_BAUDRATE:
											if ((TlvTree_GetLength(hNode) == 4) && (TlvTree_GetData(hNode) != NULL))
											{
												pValue = TlvTree_GetData(hNode);
												g_nParamsComBaudrate = (((unsigned long)pValue[0]) << 24)
													| (((unsigned long)pValue[1]) << 16)
													| (((unsigned long)pValue[2]) << 8)
													| ((unsigned long)pValue[3]);
											}
											break;
										case TAG_EMV_COMM_FIRST_CHAR_TIMEOUT:
											if ((TlvTree_GetLength(hNode) == 4) && (TlvTree_GetData(hNode) != NULL))
											{
												pValue = TlvTree_GetData(hNode);
												g_nFirstCharTimeout = (((unsigned long)pValue[0]) << 24)
													| (((unsigned long)pValue[1]) << 16)
													| (((unsigned long)pValue[2]) << 8)
													| ((unsigned long)pValue[3]);
											}
											break;
										case TAG_EMV_COMM_NEXT_CHAR_TIMEOUT:
											if ((TlvTree_GetLength(hNode) == 4) && (TlvTree_GetData(hNode) != NULL))
											{
												pValue = TlvTree_GetData(hNode);
												g_nNextCharTimeout = (((unsigned long)pValue[0]) << 24)
													| (((unsigned long)pValue[1]) << 16)
													| (((unsigned long)pValue[2]) << 8)
													| ((unsigned long)pValue[3]);
											}
											break;
										default:
											break;
										}
										
										hNode = TlvTree_GetNext(hNode);
									}
								}
							}
						}
						
						if (hParamsTlvTree != NULL)
							TlvTree_Release(hParamsTlvTree);
					}
					
					ufree(pFileContent);
				}
			}
			
			FS_close(hFile);
		}

		if (bError)
			FS_unlink(szFileName);
		
		Disk_CloseEmvCommDisk();
	}
}

int Params_Save(void)
{
	int bResult;
	char szFileName[FS_PATHSIZE + 1];
	S_FS_FILE* hFile;
	TLV_TREE_NODE hParamsTlvTree;
	unsigned char Buffer[4];
	int nSerialisationSize;
	unsigned char* pFileContent;

	bResult = FALSE;
	pFileContent = NULL;
	nSerialisationSize = 0;

	hParamsTlvTree = TlvTree_New(TAG_EMV_COMM_PARAMS);
	if (hParamsTlvTree != NULL)
	{
		Buffer[0] = (unsigned char)(signed char)g_nParamsComPort;
		if (TlvTree_AddChild(hParamsTlvTree, TAG_EMV_COMM_PORT, Buffer, 1) != NULL)
		{
			Buffer[0] = (unsigned char)(g_nParamsComBaudrate >> 24);
			Buffer[1] = (unsigned char)(g_nParamsComBaudrate >> 16);
			Buffer[2] = (unsigned char)(g_nParamsComBaudrate >> 8);
			Buffer[3] = (unsigned char)(g_nParamsComBaudrate);
			if (TlvTree_AddChild(hParamsTlvTree, TAG_EMV_COMM_BAUDRATE, Buffer, 4) != NULL)
			{
				Buffer[0] = (unsigned char)(g_nFirstCharTimeout >> 24);
				Buffer[1] = (unsigned char)(g_nFirstCharTimeout >> 16);
				Buffer[2] = (unsigned char)(g_nFirstCharTimeout >> 8);
				Buffer[3] = (unsigned char)(g_nFirstCharTimeout);
				if (TlvTree_AddChild(hParamsTlvTree, TAG_EMV_COMM_FIRST_CHAR_TIMEOUT, Buffer, 4) != NULL)
				{
					Buffer[0] = (unsigned char)(g_nNextCharTimeout >> 24);
					Buffer[1] = (unsigned char)(g_nNextCharTimeout >> 16);
					Buffer[2] = (unsigned char)(g_nNextCharTimeout >> 8);
					Buffer[3] = (unsigned char)(g_nNextCharTimeout);
					if (TlvTree_AddChild(hParamsTlvTree, TAG_EMV_COMM_NEXT_CHAR_TIMEOUT, Buffer, 4) != NULL)
					{
						nSerialisationSize = TlvTree_GetSerializationSize(hParamsTlvTree, TLV_TREE_SERIALIZER_DEFAULT);
						if (nSerialisationSize > 0)
						{
							pFileContent = umalloc(nSerialisationSize);
							if (pFileContent != NULL)
							{
								nSerialisationSize = TlvTree_Serialize(hParamsTlvTree, TLV_TREE_SERIALIZER_DEFAULT, pFileContent, nSerialisationSize);
								if (nSerialisationSize > 0)
									bResult = TRUE;
							}
						}
					}
				}
			}
		}
		
		TlvTree_Release(hParamsTlvTree);
		hParamsTlvTree = NULL;
	}

	if (bResult)
	{
		bResult = FALSE;
	
		if (Disk_OpenEmvCommDisk())
		{
			sprintf(szFileName, "/%s/%s", EMVCOMM_DISK_LABEL, g_szParamsFileName);
			
			FS_unlink(szFileName);
			hFile = FS_open(szFileName, "a");
			if (hFile != NULL)
			{
				if (FS_write(pFileContent, nSerialisationSize, 1, hFile) == 1)
					bResult = TRUE;

				FS_close(hFile);
			}
	
			if (!bResult)
				FS_unlink(szFileName);
			
			Disk_CloseEmvCommDisk();
		}
	}
	
	if (pFileContent != NULL)
	{
		ufree(pFileContent);
		pFileContent = NULL;
	}
	
	return bResult;
}

int Params_Set(TLV_TREE_NODE hParamsTlvTree)
{
	TLV_TREE_NODE hNode;
	const unsigned char* pValue;

	if (hParamsTlvTree == NULL)
	{
		g_nParamsComPort = PARAMS_DEFAULT_COM_PORT;
		g_nParamsComBaudrate = PARAMS_DEFAULT_COM_BAUDRATE;
		g_nFirstCharTimeout = PARAMS_DEFAULT_FIRST_CHARACTER_RECEIVE_TIMEOUT;
		g_nNextCharTimeout = PARAMS_DEFAULT_NEXT_CHARACTERS_RECEIVE_TIMEOUT;
		return TRUE;
	}
	
	if (TlvTree_GetTag(hParamsTlvTree) != TAG_EMV_COMM_PARAMS)
		return FALSE;
	
	g_nParamsComPort = PARAMS_DEFAULT_COM_PORT;
	g_nParamsComBaudrate = PARAMS_DEFAULT_COM_BAUDRATE;
	g_nFirstCharTimeout = PARAMS_DEFAULT_FIRST_CHARACTER_RECEIVE_TIMEOUT;
	g_nNextCharTimeout = PARAMS_DEFAULT_NEXT_CHARACTERS_RECEIVE_TIMEOUT;
	
	hNode = TlvTree_GetFirstChild(hParamsTlvTree);
	while(hNode != NULL)
	{
		switch(TlvTree_GetTag(hNode))
		{
		case TAG_EMV_COMM_PORT:
			if ((TlvTree_GetLength(hNode) == 1) && (TlvTree_GetData(hNode) != NULL))
				g_nParamsComPort = *(signed char*)TlvTree_GetData(hNode);
			break;
		case TAG_EMV_COMM_BAUDRATE:
			if ((TlvTree_GetLength(hNode) == 4) && (TlvTree_GetData(hNode) != NULL))
			{
				pValue = TlvTree_GetData(hNode);
				g_nParamsComBaudrate = (((unsigned long)pValue[0]) << 24)
					| (((unsigned long)pValue[1]) << 16)
					| (((unsigned long)pValue[2]) << 8)
					| ((unsigned long)pValue[3]);
			}
			break;
		case TAG_EMV_COMM_FIRST_CHAR_TIMEOUT:
			if ((TlvTree_GetLength(hNode) == 4) && (TlvTree_GetData(hNode) != NULL))
			{
				pValue = TlvTree_GetData(hNode);
				g_nFirstCharTimeout = (((unsigned long)pValue[0]) << 24)
					| (((unsigned long)pValue[1]) << 16)
					| (((unsigned long)pValue[2]) << 8)
					| ((unsigned long)pValue[3]);
			}
			break;
		case TAG_EMV_COMM_NEXT_CHAR_TIMEOUT:
			if ((TlvTree_GetLength(hNode) == 4) && (TlvTree_GetData(hNode) != NULL))
			{
				pValue = TlvTree_GetData(hNode);
				g_nNextCharTimeout = (((unsigned long)pValue[0]) << 24)
					| (((unsigned long)pValue[1]) << 16)
					| (((unsigned long)pValue[2]) << 8)
					| ((unsigned long)pValue[3]);
			}
			break;
		default:
			break;
		}
		
		hNode = TlvTree_GetNext(hNode);
	}
	
	return TRUE;
}

int Params_GetComPort(void)
{
	return g_nParamsComPort;
}

int Params_GetComBaudrate(void)
{
	return g_nParamsComBaudrate;
}

unsigned long Params_GetFirstCharTimeout(void)
{
	return g_nFirstCharTimeout;
}

unsigned long Params_GetNextCharTimeout(void)
{
	return g_nNextCharTimeout;
}
