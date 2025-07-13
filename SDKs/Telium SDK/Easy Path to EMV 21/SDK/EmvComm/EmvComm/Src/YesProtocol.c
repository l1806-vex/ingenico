//! \file
//! Module that manages all the application menus

/////////////////////////////////////////////////////////////////

//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "_emvdctag_.h"

#include "TlvTree.h"
#include "servcomm.h"
#include "WGUI.h"
#include "WGUI_Deprecated.h"
#include "YesProtocol.h"

//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

extern int g_bCGuiMode;

static int g_nYesProtocolLastMessageType;

static const char g_HtmlFileNameWarning[] = "Warning/Warning.html";
static const char g_HtmlFileNameMessage[] = "Message/Message.html";

static const char g_HtmlWarning[] =
	"<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\n"
	"<html>\n"
	"<head>\n"
	"<meta http-equiv=\"refresh\" content=\"<?tpl TIMEOUT?>;url=app://end\">\n"
	"<title>Message</title>\n"
	"<style>\n"
	"body { font-family:sans-serif; margin:0px; padding:0px; background-color:black; }\n"
	"#ContentCell { width:100%; vertical-align:middle; }\n"
	".ContentLine { background-color:red; color:black; margin:0px; padding:0px; font-size:14pt; width:100%; text-align:center; }\n"
	"</style>\n"
	"</head>\n"
	"\n"
	"<body>\n"
	"<table width=\"100%\" cellpadding=\"0\" cellspacing=\"0\">\n"
	"<tr><td id=\"ContentCell\" height=\"<?tpl HEIGHT?>px\"><p class=\"ContentLine\" id=\"Message\"><?tpl MESSAGE?></p></td></tr></table>\n"
	"</body>\n"
	"</html>\n";

static const char g_HtmlMessage[] =
	"<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\n"
	"<html>\n"
	"<head>\n"
	"<meta http-equiv=\"refresh\" content=\"<?tpl TIMEOUT?>;url=app://end\">\n"
	"<title>Message</title>\n"
	"<style>\n"
	"body { font-family:sans-serif; margin:0px; padding:0px; background-color:black; }\n"
	"#ContentCell { width:100%; vertical-align:middle; }\n"
	".ContentLine { color:white; margin:0px; padding:0px; font-size:14pt; width:100%; text-align:center; }\n"
	"</style>\n"
	"</head>\n"
	"\n"
	"<body>\n"
	"<table width=\"100%\" cellpadding=\"0\" cellspacing=\"0\">\n"
	"<tr><td id=\"ContentCell\" height=\"<?tpl HEIGHT?>px\"><p class=\"ContentLine\" id=\"Message\"><?tpl MESSAGE?></p></td></tr></table>\n"
	"</body>\n"
	"</html>\n";

//// Static function definitions ////////////////////////////////

static int __YesProtocolAddStatusCode(TLV_TREE_NODE hOutputTlvTree, int nStatusCode);

static int __YesProtocolSendMessage(TLV_TREE_NODE hInputTlvTree);
static int __YesProtocolGetResponse(TLV_TREE_NODE hOutputTlvTree);

//// Functions //////////////////////////////////////////////////

static int __YesProtocolAddStatusCode(TLV_TREE_NODE hOutputTlvTree, int nStatusCode)
{
	unsigned char Buffer[2];

	// Status code
	Buffer[0] = (unsigned char)((nStatusCode >> 8) & 0xff);
	Buffer[1] = (unsigned char)(nStatusCode & 0xff);

	return (TlvTree_AddChild(hOutputTlvTree, TAG_COMM_STATUS_CODE, Buffer, 2) != NULL);
}

static int __YesProtocolSendMessage(TLV_TREE_NODE hInputTlvTree)
{
	TLV_TREE_NODE hNode;
	const unsigned char* pValue;

	// Get the Message Type
	g_nYesProtocolLastMessageType = -1;
	hNode = TlvTree_Find(hInputTlvTree, TAG_COMM_MESSAGE_TYPE, 0);
	if (hNode != NULL)
	{
		pValue = TlvTree_GetData(hNode);
		if ((TlvTree_GetLength(hNode) == 2) && (pValue != NULL))
		{
			g_nYesProtocolLastMessageType = ((unsigned short)(pValue[0] << 8)) | (pValue[1]);
		}
	}

	return COMM_ERR_SUCCESS;
}

static int __YesProtocolGetResponse(TLV_TREE_NODE hOutputTlvTree)
{
	int nResult;
	const char* pTestMessage;
	const char* pGraphicMessage;
	int nResponseCode;
	unsigned char Buffer[2];
	FILE* hDisplay;
	int nDisplayDelay;
	int nLeft;
	int nTop;
	int nRight;
	int nBottom;
	WGUI_CANVAS_HANDLE hCanvas;
	WGUI_BROWSER_HANDLE hBrowser;
	int bDisplayText;
	WGUI_ERROR nWGuiError;
	WGUI_HTML_EVENT_HANDLE hEvent;
	char szTimeout[16];
	char szHeight[16];
	const char* pHtmlMessage;
	const char* pHtmlFileName;
	char HtmlRscFileName[128 + 1];
	object_info_t ObjectInfo;
	object_descriptor_t ObjectDescriptor;
	char* pPtr;

	pTestMessage = NULL;
	pGraphicMessage = NULL;
	nResult = COMM_ERR_SUCCESS;
	nResponseCode = -1;
	nDisplayDelay = -1;
	pHtmlMessage = g_HtmlMessage;
	pHtmlFileName = g_HtmlFileNameMessage;
	HtmlRscFileName[0] = '\0';

	// Check the Message Type
	switch(g_nYesProtocolLastMessageType)
	{
	case COMM_MSG_AUTHORISATION_REQUEST:
		pTestMessage = "  APPROVAL  BY\n  YES PROTOCOL";
		pGraphicMessage = "APPROVAL<br>BY YES PROTOCOL";
		pHtmlMessage = g_HtmlWarning;
		pHtmlFileName = g_HtmlFileNameWarning;
		nDisplayDelay = 200;
		nResponseCode = 0x00;
		nResult = COMM_ERR_SUCCESS;
		break;

	case COMM_MSG_COLLECTION_INITIALISATION:
		pTestMessage = "  BATCH UPLOAD\n  IN  PROGRESS";
		pGraphicMessage = "BATCH UPLOAD<br>IN PROGRESS";
		nDisplayDelay = 100;
		nResponseCode = 0x00;
		nResult = COMM_ERR_SUCCESS;
		break;

	case COMM_MSG_REVERSAL_REQUEST:
	case COMM_MSG_REFUND_REQUEST:
	case COMM_MSG_FINANCIAL_TRANSAC_REQUEST:
	case COMM_MSG_FINANCIAL_TRANSAC_CONFIRM:
	case COMM_MSG_ONLINE_ADVICE:
	case COMM_MSG_COLLECTION_TERMINATION:
	case COMM_MSG_COLLECTION_ITEM:
	case COMM_MSG_ADVICE_COLLECTION_ITEM:
		pTestMessage = NULL;
		pGraphicMessage = NULL;
		nResponseCode = 0x00;
		nResult = COMM_ERR_SUCCESS;
		break;

	case COMM_MSG_RECONCILIATION_REQUEST:
	case COMM_MSG_FILE_UPLOAD_REQUEST:
	case COMM_MSG_FILE_DOWNLOAD_REQUEST:
	default:
		// Message Type is not valid or not supported
		g_nYesProtocolLastMessageType = -1;
		pTestMessage = NULL;
		pGraphicMessage = NULL;
		nResponseCode = -1;
		nResult = COMM_ERR_BAD_PARAMETER;
		break;
	}

	bDisplayText = TRUE;
	if (g_bCGuiMode)
	{
		if ((pGraphicMessage != NULL) && (pHtmlMessage != NULL))
		{
			GetScreenArea(&nLeft, &nTop, &nRight, &nBottom);
			nWGuiError = WGUI_Display_Create(nLeft, nTop, nRight - nLeft + 1, nBottom - nTop + 1, WGUI_DISPLAY_COLORS);
			if ((nWGuiError == WGUI_OK) || (nWGuiError == WGUI_DISPLAY_ALREADY_CREATE_ERR))
			{
				if (nWGuiError == WGUI_DISPLAY_ALREADY_CREATE_ERR)
					WGUI_Display_Resize(nLeft, nTop, nRight - nLeft + 1, nBottom - nTop + 1);

			hCanvas = WGUI_Canvas_Create(WGUI_CANVAS_SCREEN, nLeft, nTop, nRight - nLeft + 1, nBottom - nTop + 1);
			if (hCanvas != NULL)
			{
				hBrowser = WGUI_Browser_Create(hCanvas);
				if (hBrowser != NULL)
				{
					if (nDisplayDelay > 0)
						sprintf(szTimeout, "%d", (nDisplayDelay + 50) / 100);
					else sprintf(szTimeout, "1");

					sprintf(szHeight, "%d", nBottom - nTop + 1);

					// Activate the tag replacement
					if ((WGUI_Browser_SetOption(hBrowser, WGUI_BROWSER_TEMPLATE_MODE, WGUI_TEMPLATE_ACTIVATE) == WGUI_OK)
						&& (WGUI_Browser_SetOption(hBrowser, WGUI_BROWSER_LOADING_BAR_DELAY, WGUI_INFINITE) == WGUI_OK)
						&& (WGUI_Template_AddTagAscii(hBrowser, "MESSAGE", pGraphicMessage, WGUI_TRUE) == WGUI_OK)
						&& (WGUI_Template_AddTagAscii(hBrowser, "TIMEOUT", szTimeout, WGUI_TRUE) == WGUI_OK)
						&& (WGUI_Template_AddTagAscii(hBrowser, "HEIGHT", szHeight, WGUI_TRUE) == WGUI_OK))
					{
						if (pHtmlFileName != NULL)
						{
							// Is there a ressource file ?
							HtmlRscFileName[0] = '\0';
							// Get the current application type
							if (ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo) == 0)
							{
								// Get the parameter file name with the same application type of the application
								if (ObjectGetDescriptor(OBJECT_TYPE_PARAM, ObjectInfo.application_type, &ObjectDescriptor) == 0)
								{
									// Yes, there is a ressource file

									// Remove the file extention of the ressource file name
									pPtr = strrchr((char*)ObjectDescriptor.file_name, '.');
									if (pPtr != NULL)
										*pPtr = '\0';
									// Format the path to the HTML file
									sprintf(HtmlRscFileName, "@tar:///param/%s.tar/%s", ObjectDescriptor.file_name, pHtmlFileName);
								}
							}
						}

						// Load the HTML page
						if (HtmlRscFileName[0] != '\0')
							nWGuiError = WGUI_Browser_LoadUrl(hBrowser, HtmlRscFileName, FALSE);
						else nWGuiError = WGUI_Browser_WriteHtmlAscii(hBrowser, pHtmlMessage, FALSE);
						if (nWGuiError == WGUI_OK)
						{
							// Wait for the end the HTML page
							do
							{
								WGUI_Canvas_DispatchEvent(hCanvas);
								WGUI_Browser_GetHtmlEvent(hBrowser, &hEvent);
							}
							while(hEvent == NULL);

							bDisplayText = FALSE;
						}
					}

					WGUI_Browser_Destroy(hBrowser);
				}
				WGUI_Canvas_Destroy(hCanvas);
				}

				if (nWGuiError == WGUI_OK)
					WGUI_Display_Destroy();
			}
		}
	}

	if ((pTestMessage != NULL) && (bDisplayText))
	{
		hDisplay = fopen("DISPLAY", "w");
		printf("%s", pTestMessage);
		fclose(hDisplay);

		if (nDisplayDelay > 0)
		{
			ttestall(0, nDisplayDelay);
		}
	}

	if (nResponseCode >= 0)
	{
		Buffer[0] = ((nResponseCode >> 4) & 0x0f);
		if (Buffer[0] >= 0x0a)
		{
			Buffer[0] += 'A';
		}
		else
		{
			Buffer[0] += '0';
		}

		Buffer[1] = (nResponseCode & 0x0f);
		if (Buffer[1] >= 0x0a)
		{
			Buffer[1] += 'A';
		}
		else
		{
			Buffer[1] += '0';
		}

		TlvTree_AddChild(hOutputTlvTree, TAG_AUTHORISATION_RESPONSE_CODE, Buffer, 2);
	}

	return nResult;
}

int YesProtocolSendAndReceiveMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult;

	// Send the message
	nResult = __YesProtocolSendMessage(hInputTlvTree);
	if (nResult == COMM_ERR_SUCCESS)
	{
		// Wait for an answer
		nResult = __YesProtocolGetResponse(hOutputTlvTree);
	}

	// Add the status code
	__YesProtocolAddStatusCode(hOutputTlvTree, nResult);

	return OK;
}

int YesProtocolSendMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult;

	// Send the message
	nResult = __YesProtocolSendMessage(hInputTlvTree);

	// Add the status code
	__YesProtocolAddStatusCode(hOutputTlvTree, nResult);

	return OK;
}

int YesProtocolReadMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	(void)hInputTlvTree;

	// Status code
	__YesProtocolAddStatusCode(hOutputTlvTree, COMM_ERR_SERVICE_NOT_SUPPORTED);
	return OK;
}

int YesProtocolReceiveMessage(TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult;

	(void)hInputTlvTree;

	// Wait for an answer
	nResult = __YesProtocolGetResponse(hOutputTlvTree);

	// Add the status code
	__YesProtocolAddStatusCode(hOutputTlvTree, nResult);

	return OK;
}
