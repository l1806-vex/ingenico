//! \file
//! Module that manages all the application menus

/////////////////////////////////////////////////////////////////

//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "TlvTree.h"

#include "servcomm.h"
#include "Params.h"
#include "Hyperterminal.h"

//// Macros & preprocessor definitions //////////////////////////

#define HYPERTERMINAL_RECEIVE_BUFFER_SIZE				4096

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

static int g_nHyperterminalLastMessageType;

static FILE* g_hHyperterminalComPort;
static unsigned char g_HyperterminalComBuffer[HYPERTERMINAL_RECEIVE_BUFFER_SIZE];

//// Static function definitions ////////////////////////////////

static int __HyperterminalAddStatusCode(TLV_TREE_NODE hOutputTlvTree, int nStatusCode);

static unsigned long __HyperterminalGetEvent(void);

static int __HyperterminalOpen(void);
static void __HyperterminalClose(void);

static void __HyperterminalSendBuffer(int nLength, const char* pBuffer);
static void __HyperterminalSendTag(unsigned long ulTag, unsigned long ulLength,
		const unsigned char* pValue, int bAllowAscii);
static int __HyperterminalSendMessage(TLV_TREE_NODE hInputTlvTree);

static int __HyperterminalAnalyseResponseLine(unsigned char* pBuffer, int nLength,
		TLV_TREE_NODE hOutputTlvTree, int* pResult);
static void __HyperterminalGetResponse(TLV_TREE_NODE hOutputTlvTree, int* pResult);

//// Functions //////////////////////////////////////////////////

static int __HyperterminalAddStatusCode(TLV_TREE_NODE hOutputTlvTree, int nStatusCode)
{
	unsigned char Buffer[2];

	// Status code
	Buffer[0] = (unsigned char)((nStatusCode >> 8) & 0xff);
	Buffer[1] = (unsigned char)(nStatusCode & 0xff);

	return (TlvTree_AddChild(hOutputTlvTree, TAG_COMM_STATUS_CODE, Buffer, 2) != NULL);
}

static unsigned long __HyperterminalGetEvent(void)
{
	unsigned long ulEvent;
	
	switch(Params_GetComPort())
	{
	case 0:		ulEvent = COM0;		break;
	case 1:		ulEvent = COM1;		break;
	case 2:		ulEvent = COM2;		break;
	case 5:		ulEvent = COM5;		break;
	case 6:		ulEvent = COM6;		break;
	default:	ulEvent = 0;		break;
	}
	
	return ulEvent;
}

static int __HyperterminalOpen(void)
{
	char szComPort[16];
	
	g_nHyperterminalLastMessageType = -1;
	
	// Open the COM port
	sprintf(szComPort, "COM%d", Params_GetComPort());
	g_hHyperterminalComPort = fopen(szComPort, "rw*");
	if (g_hHyperterminalComPort == NULL)
	{
		return COMM_ERR_COMMUNICATION_PROBLEM;
	}

	// Configure the COM port
	format(szComPort, Params_GetComBaudrate(), 8, 1, NO_PARITY, EVEN, 0);

	return COMM_ERR_SUCCESS;
}

static void __HyperterminalClose(void)
{
	unsigned char Status;

	g_nHyperterminalLastMessageType = -1;

	// Close the COM port
	if (g_hHyperterminalComPort != NULL)
	{
		// Wait until all data are sent
		mask_event(g_hHyperterminalComPort, COM_SEND_EMPTY);
		status(g_hHyperterminalComPort, &Status);
		while((Status & COM_SEND_EMPTY) == 0)
		{
			ttestall(__HyperterminalGetEvent(), 500);
			status(g_hHyperterminalComPort, &Status);
		}
		mask_event(g_hHyperterminalComPort, COM_REC_NOT_EMPTY);

		fclose(g_hHyperterminalComPort);
		g_hHyperterminalComPort = NULL;
	}
}

static void __HyperterminalSendBuffer(int nLength, const char* pBuffer)
{
	int nIndex;
	
	nIndex = 0;
	while(nIndex < nLength)
	{
		// Send some bytes
		nIndex += fwrite((unsigned char*)(pBuffer + nIndex), 1, nLength - nIndex, g_hHyperterminalComPort);
		if (nIndex < nLength)
		{
			// Not all the bytes are sent, wait a little before to continue
			ttestall(0, 1);
		}
	}
}

static void __HyperterminalSendTag(unsigned long ulTag, unsigned long ulLength,
		const unsigned char* pValue, int bAllowAscii)
{
	char String[256];
	unsigned long ulIndex;
	int nLineLength;
	int bAddSpace;
	
	// Format the tag and length
	nLineLength = sprintf(String, "T:%-6lX L:%02lX V:", ulTag, ulLength);

	bAddSpace = FALSE;
	
	// Format and send the value
	for(ulIndex = 0; ulIndex < ulLength; ulIndex++)
	{
		if (bAddSpace)
		{
			nLineLength += sprintf(String + nLineLength, " %02X", pValue[ulIndex]);
		}
		else
		{
			nLineLength += sprintf(String + nLineLength, "%02X", pValue[ulIndex]);
			bAddSpace = TRUE;
		}
		
		if (nLineLength > 76)
		{
			// Send the line
			nLineLength += sprintf(String + nLineLength, "\r\n");
			__HyperterminalSendBuffer(nLineLength, String);
			nLineLength = 0;
			bAddSpace = FALSE;
		}
	}
	
	// Send the last line
	if (nLineLength > 0)
	{
		nLineLength += sprintf(String + nLineLength, "\r\n");
		__HyperterminalSendBuffer(nLineLength, String);
		nLineLength = 0;
		bAddSpace = FALSE;
	}
	
	if ((bAllowAscii) && (ulTag == 0x56))
	{
		// Send the value in ASCII
		
		// Format the tag and length
		nLineLength = sprintf(String, "        V ASCII:");

		// Format and send the value
		for(ulIndex = 0; ulIndex < ulLength; ulIndex++)
		{
			nLineLength += sprintf(String + nLineLength, "%c", pValue[ulIndex]);
			
			if (nLineLength > 79)
			{
				// Send the line
				nLineLength += sprintf(String + nLineLength, "\r\n");
				__HyperterminalSendBuffer(nLineLength, String);
				nLineLength = 0;
			}
		}
		
		// Send the last line
		if (nLineLength > 0)
		{
			nLineLength += sprintf(String + nLineLength, "\r\n");
			__HyperterminalSendBuffer(nLineLength, String);
			nLineLength = 0;
		}
	}
}

static int __HyperterminalSendMessage(TLV_TREE_NODE hInputTlvTree)
{
	TLV_TREE_NODE hNode;
	const unsigned char* pValue;
	const char* pMessage;
	
	// Get the Message Type
	g_nHyperterminalLastMessageType = -1;
	hNode = TlvTree_Find(hInputTlvTree, TAG_COMM_MESSAGE_TYPE, 0);
	if (hNode != NULL)
	{
		pValue = TlvTree_GetData(hNode);
		if ((TlvTree_GetLength(hNode) == 2) && (pValue != NULL))
		{
			g_nHyperterminalLastMessageType = ((unsigned short)(pValue[0] << 8)) | (pValue[1]);
		}
	}

	// Check the Message Type
	switch(g_nHyperterminalLastMessageType)
	{
	case COMM_MSG_AUTHORISATION_REQUEST:
		pMessage = "AUTHORISATION REQUEST\r\n";
		break;
	case COMM_MSG_REVERSAL_REQUEST:
		pMessage = "REVERSAL REQUEST\r\n";
		break;
	case COMM_MSG_REFUND_REQUEST:
		pMessage = "REFUND REQUEST\r\n";
		break;
	case COMM_MSG_FINANCIAL_TRANSAC_REQUEST:
		pMessage = "FINANCIAL TRANSACTION REQUEST\r\n";
		break;
	case COMM_MSG_FINANCIAL_TRANSAC_CONFIRM:
		pMessage = "FINANCIAL TRANSACTION CONFIRMATION\r\n";
		break;
	case COMM_MSG_ONLINE_ADVICE:
		pMessage = "ONLINE ADVICE\r\n";
		break;
	case COMM_MSG_COLLECTION_INITIALISATION:
		pMessage = "COLLECTION INITIALISATION\r\n";
		break;
	case COMM_MSG_COLLECTION_TERMINATION:
		pMessage = "COLLECTION TERMINATION\r\n";
		break;
	case COMM_MSG_COLLECTION_ITEM:
		pMessage = "COLLECTION ITEM\r\n";
		break;
	case COMM_MSG_ADVICE_COLLECTION_ITEM:
		pMessage = "ADVICE COLLECTION ITEM\r\n";
		break;

	case COMM_MSG_RECONCILIATION_REQUEST:
	case COMM_MSG_FILE_UPLOAD_REQUEST:
	case COMM_MSG_FILE_DOWNLOAD_REQUEST:
	default:
		// Message Type is not valid or not supported
		g_nHyperterminalLastMessageType = -1;
		return COMM_ERR_BAD_PARAMETER;
		break;
	}
	
	// Send the Message Type
	__HyperterminalSendBuffer(strlen(pMessage), pMessage);
	
	// Send the input tags
	hNode = TlvTree_GetFirstChild(hInputTlvTree);
	while(hNode != NULL)
	{
		__HyperterminalSendTag(TlvTree_GetTag(hNode), TlvTree_GetLength(hNode), TlvTree_GetData(hNode), TRUE);
		hNode = TlvTree_GetNext(hNode);
	}
	
	return COMM_ERR_SUCCESS;
}

static int __HyperterminalAnalyseResponseLine(unsigned char* pBuffer, int nLength,
		TLV_TREE_NODE hOutputTlvTree, int* pResult)
{
	int bResult;
	int nIndex;
	unsigned long ulTag;
	int bTagSet;
	int nBinValueIndex;
	int bFirstNibble;
	int bError;
	unsigned char ucValue;
	
	if (nLength == 0)
	{
		return FALSE;
	}
	
	bResult = FALSE;
	nIndex = 0;
	while(nIndex < nLength)
	{
		// Remove spaces and tabs
		if ((pBuffer[nIndex] == ' ') || (pBuffer[nIndex] == '\t'))
		{
			memmove(&pBuffer[nIndex], &pBuffer[nIndex + 1], nLength - nIndex - 1);
			nLength--;
		}
		// Convert to uppercase
		else if ((pBuffer[nIndex] >= 'a') && (pBuffer[nIndex] <= 'z'))
		{
			pBuffer[nIndex] = (pBuffer[nIndex] - 'a') + 'A';
			nIndex++;
		}
		else
		{
			nIndex++;
		}
	}

	if (nLength == 2)
	{
		if (memcmp(pBuffer, "KO", 2) == 0)
		{
			*pResult = COMM_ERR_COMMUNICATION_PROBLEM;
			bResult = TRUE;
		}
	}
	else if (nLength == 3)
	{
		if (memcmp(pBuffer, "END", 3) == 0)
		{
			*pResult = COMM_ERR_SUCCESS;
			bResult = TRUE;
		}
	}
	
	if (!bResult)
	{
		// Analyse the tag
		nIndex = 0;
		nBinValueIndex = 0;
		bFirstNibble = TRUE;
		bTagSet = FALSE;
		bError = FALSE;
		ulTag = 0;
		ucValue = 0;
		while((!bError) && (nIndex < nLength))
		{
			if (pBuffer[nIndex] == '=')
			{
				if ((!bFirstNibble) || (bTagSet) || (ulTag == 0))
				{
					bError = TRUE;
				}
				else
				{
					bTagSet = TRUE;
				}
			}
			else
			{
				if (bFirstNibble)
				{
					ucValue = 0;
				}
				else
				{
					ucValue <<= 4;
				}
				
				if ((pBuffer[nIndex] >= 'A') && (pBuffer[nIndex] <= 'Z'))
				{
					ucValue |= (pBuffer[nIndex] - 'A') + 10;
				}
				else if ((pBuffer[nIndex] >= '0') && (pBuffer[nIndex] <= '9'))
				{
					ucValue |= pBuffer[nIndex] - '0';
				}
				else
				{
					bError = TRUE;
				}
				
				if (!bError)
				{
					if (!bFirstNibble)
					{
						// New byte, store the value
						if (!bTagSet)
						{
							if ((ulTag & 0xff000000) == 0)
							{
								ulTag = (ulTag << 8) | ucValue;
							}
							else
							{
								bError = TRUE;
							}
						}
						else
						{
							pBuffer[nBinValueIndex++] = ucValue;
						}
					}
					bFirstNibble = !bFirstNibble;
				}
			}

			nIndex++;
		}
		
		if (!bError)
		{
			if (bFirstNibble)
			{
				// Data is valid
				if (TlvTree_AddChild(hOutputTlvTree, ulTag, pBuffer, nBinValueIndex) != NULL)
				{
					// Confirm the tag
					__HyperterminalSendTag(ulTag, nBinValueIndex, pBuffer, FALSE);
				}
				else
				{
					bError = TRUE;
				}
			}
			else
			{
				bError = TRUE;
			}
		}

		if (bError)
		{
			// Signal an error
			__HyperterminalSendBuffer(7, "ERROR\r\n");
		}
	}
	
	return bResult;
}

static void __HyperterminalGetResponse(TLV_TREE_NODE hOutputTlvTree, int* pResult)
{
	int nBufferIndex;
	int bEnd;
	FILE* hKeyboard;
	unsigned long ulEvent;
	unsigned long ulLastReceiveTime;
	unsigned long ulCurrentTime;
	unsigned long ulTimeout;
	int nIndex;
	TLV_TREE_NODE hNode;
	unsigned long ulComEvent;

	if ((g_nHyperterminalLastMessageType == COMM_MSG_AUTHORISATION_REQUEST)
			|| (g_nHyperterminalLastMessageType == COMM_MSG_REVERSAL_REQUEST)
			|| (g_nHyperterminalLastMessageType == COMM_MSG_REFUND_REQUEST)
			|| (g_nHyperterminalLastMessageType == COMM_MSG_FINANCIAL_TRANSAC_REQUEST)
			|| (g_nHyperterminalLastMessageType == COMM_MSG_FINANCIAL_TRANSAC_CONFIRM)
			|| (g_nHyperterminalLastMessageType == COMM_MSG_ONLINE_ADVICE))
	{
		__HyperterminalSendBuffer(16, "ENTER RESPONSE\r\n");
	
		hKeyboard = fopen("KEYBOARD", "r*");
		
		ulLastReceiveTime = get_tick_counter();
		ulTimeout = Params_GetFirstCharTimeout();
		
		ulComEvent = __HyperterminalGetEvent();
		nBufferIndex = 0;
		bEnd = FALSE;
		do
		{
			ulEvent = ttestall(KEYBOARD | ulComEvent, ulTimeout);
			if ((ulEvent & KEYBOARD) != 0)
			{
				if (getc(hKeyboard) == T_ANN)
				{
					// Cancel key
					*pResult = COMM_ERR_COMMUNICATION_PROBLEM;
					bEnd = TRUE;
				}
			}
			
			if ((!bEnd) && ((ulEvent & ulComEvent) != 0))
			{
				nBufferIndex += fread(g_HyperterminalComBuffer + nBufferIndex, 1, sizeof(g_HyperterminalComBuffer) - nBufferIndex, g_hHyperterminalComPort);
				
				ulLastReceiveTime = get_tick_counter();
				
				// Remove deleted characters and analyse the lines
				nIndex = 0;
				while((!bEnd) && (nIndex < nBufferIndex))
				{
					switch(g_HyperterminalComBuffer[nIndex])
					{
					case '\n':
					case '\r':
						bEnd = __HyperterminalAnalyseResponseLine(g_HyperterminalComBuffer, nIndex, hOutputTlvTree, pResult);
						memmove(&g_HyperterminalComBuffer[0], &g_HyperterminalComBuffer[nIndex + 1], nBufferIndex - nIndex - 1);
						nBufferIndex -= nIndex + 1;
						nIndex = 0;
						break;
					case 0x08:
						if (nIndex > 0)
						{
							memmove(&g_HyperterminalComBuffer[nIndex - 1], &g_HyperterminalComBuffer[nIndex + 1], nBufferIndex - nIndex - 1);
							nBufferIndex -= 2;
							nIndex--;
						}
						else
						{
							memmove(&g_HyperterminalComBuffer[nIndex], &g_HyperterminalComBuffer[nIndex + 1], nBufferIndex - nIndex);
							nBufferIndex--;
						}
						break;
					default:
						nIndex++;
						break;
					}
				}
			}
	
			if (!bEnd)
			{
				ulCurrentTime = get_tick_counter();
				if (nBufferIndex == 0)
				{
					if (ulCurrentTime - ulLastReceiveTime >= Params_GetFirstCharTimeout())
					{
						// Timeout
						ulTimeout = 0;
						bEnd = TRUE;
						*pResult = COMM_ERR_TIME_OUT;
					}
					else
					{
						ulTimeout = Params_GetFirstCharTimeout() - (ulCurrentTime - ulLastReceiveTime);
					}
				}
				else
				{
					if (ulCurrentTime - ulLastReceiveTime >= Params_GetNextCharTimeout())
					{
						// Timeout
						ulTimeout = 0;
						bEnd = TRUE;
						*pResult = COMM_ERR_TIME_OUT;
					}
					else
					{
						ulTimeout = Params_GetNextCharTimeout() - (ulCurrentTime - ulLastReceiveTime);
					}
				}
			}
		} while(!bEnd);
		
		if (hKeyboard != NULL)
		{
			fclose(hKeyboard);
			hKeyboard = NULL;
		}
	}
	else
	{
		*pResult = COMM_ERR_SUCCESS;
	}
	
	if (*pResult != COMM_ERR_SUCCESS)
	{
		// Clear output TlvTree
		if (hOutputTlvTree != NULL)
		{
			hNode = TlvTree_GetFirstChild(hOutputTlvTree);
			while(hNode != NULL)
			{
				TlvTree_Release(hNode);
				hNode = TlvTree_GetFirstChild(hOutputTlvTree);
			}
		}
	}
}

int HyperterminalSendAndReceiveMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult;

	// Open the COM port
	nResult = __HyperterminalOpen();
	if (nResult == COMM_ERR_SUCCESS)
	{
		// Send the message
		nResult = __HyperterminalSendMessage(hInputTlvTree);
		if (nResult == COMM_ERR_SUCCESS)
		{
			// Wait for an answer
			__HyperterminalGetResponse(hOutputTlvTree, &nResult);
		}
	}
	
	// Close the COM port
	__HyperterminalClose();
	
	// Add the status code
	__HyperterminalAddStatusCode(hOutputTlvTree, nResult);
	
	return OK;
}

int HyperterminalSendMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult;

	// Open the COM port
	nResult = __HyperterminalOpen();
	if (nResult == COMM_ERR_SUCCESS)
	{
		// Send the message
		nResult = __HyperterminalSendMessage(hInputTlvTree);
	}
	
	// Close the COM port
	__HyperterminalClose();
	
	// Add the status code
	__HyperterminalAddStatusCode(hOutputTlvTree, nResult);
	
	return OK;
}

int HyperterminalReadMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	(void)hInputTlvTree;

	// Status code
	__HyperterminalAddStatusCode(hOutputTlvTree, COMM_ERR_SERVICE_NOT_SUPPORTED);
	return OK;
}

int HyperterminalReceiveMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult;

	(void)hInputTlvTree;

	// Open the COM port
	nResult = __HyperterminalOpen();
	if (nResult == COMM_ERR_SUCCESS)
	{
		// Wait for an answer
		__HyperterminalGetResponse(hOutputTlvTree, &nResult);
	}
	
	// Close the COM port
	__HyperterminalClose();
	
	// Add the status code
	__HyperterminalAddStatusCode(hOutputTlvTree, nResult);
	
	return OK;
}
