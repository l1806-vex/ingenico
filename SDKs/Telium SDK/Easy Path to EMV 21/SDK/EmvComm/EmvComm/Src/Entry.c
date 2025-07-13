/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "hterm.h"
#include "_emvdc_.h"

#include "WGUI.h"

#include "del_lib.h"
#include "TlvTree.h"

#include "servcomm.h"

#include "TlvTreeDel.h"
#include "Params.h"
#include "Comm.h"

//// Macros & preprocessor definitions //////////////////////////

#define SERVICES_DEFAULT_PRIORITY		50
#define SERVICES_COMM_PRIORITY			(SERVICES_DEFAULT_PRIORITY)

//// Types //////////////////////////////////////////////////////

//// Extern function definitions ////////////////////////////////

extern int Get_StateWGUI(void);

//// Static function definitions ////////////////////////////////

void entry(void);

static int __after_reset(NO_SEGMENT AppliNum, S_TRANSOUT* pParamOut);
static int __give_your_domain(NO_SEGMENT AppliNum, S_INITPARAMOUT* pParamOut);
static int __Main(unsigned int nSize, StructPt* pData);
static int __Main_Comm(unsigned int nSize, StructProcessStep* pData);
static int __give_interface(unsigned short AppliNum, void* pParamIn, void* pParamOut);

//// Global variables ///////////////////////////////////////////

static service_desc_t Services[] = {
	{ 0, AFTER_RESET, (SAP)__Main, SERVICES_DEFAULT_PRIORITY },
	{ 0, GIVE_YOUR_DOMAIN, (SAP)__Main, SERVICES_DEFAULT_PRIORITY },
#ifndef _YES_PROTOCOL_ONLY_
	{ 0, FILE_RECEIVED, (SAP)__Main, SERVICES_DEFAULT_PRIORITY },
#endif
	
	{ 0, I_COMM_INITIATE_ONLINE_TRANSACTION, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_AUTHORISATION_REQUEST, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_SEND_ONLINE_ADVICE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_REVERSAL, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_SEND_FINANCIAL_TRANSACTION_REQUEST, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_FINANCIAL_TRANSACTION_CONFIRMATION, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_TERMINATE_ONLINE_TRANSACTION, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_INITIATE_BATCH_DATA_CAPTURE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_SEND_BATCH_DATA, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_TERMINATE_BATCH_DATA_CAPTURE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_PERFORM_RECONCILIATION, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_GET_BLACK_LIST, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_PIN_ONLINE_REQUEST, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },

	{ 0, I_COMM_GET_PROTOCOL_INFO, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_CONFIGURE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_CONNECT, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_DISCONNECT, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_SEND_AND_RECEIVE_MESSAGE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_SEND_MESSAGE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_GET_STATUS, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_READ_MESSAGE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_ABORT, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_RECEIVE_MESSAGE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_MAKE_RAW_MESSAGE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_SEND_RAW_MESSAGE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_RECEIVE_RAW_MESSAGE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY },
	{ 0, I_COMM_PARSE_RAW_MESSAGE, (SAP)__Main_Comm, SERVICES_COMM_PRIORITY }
};

//// Functions //////////////////////////////////////////////////

int g_bCGuiMode = FALSE;

static int __after_reset(NO_SEGMENT AppliNum, S_TRANSOUT* pParamOut)
{
	unsigned char ChangeFlag;
	unsigned char ChangeType;

	// Clear the output parameter
	memset(pParamOut, 0, sizeof(*pParamOut));

#ifndef _YES_PROTOCOL_ONLY_
	Params_FirstInit();
	Params_Load();
#endif

	// Check if cGUI must be used
	if (Get_StateWGUI())
	{
		WGUI_DLL_Init();
		g_bCGuiMode = TRUE;
	}
	
	// Check for first run
	if (first_init(AppliNum, &ChangeFlag, &ChangeType) != FSE_FAILED)
	{
		if (ChangeFlag == (unsigned char)-1)
		{
			// The application has been updated
			raz_init(AppliNum);
		}
	}

	return FCT_OK;
}

static int __give_your_domain(NO_SEGMENT AppliNum, S_INITPARAMOUT* pParamOut)
{
	(void)AppliNum;

	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	pParamOut->returned_state[pParamOut->response_number].mask = MSK_NULL;
	pParamOut->returned_state[pParamOut->response_number].application_type = TYP_CARTE;
	pParamOut->response_number++;

	return FCT_OK;
}

#ifndef _YES_PROTOCOL_ONLY_
static int __file_received(NO_SEGMENT AppliNum, S_FILE* pParamIn)
{
	int nResult;
	S_FS_FILE* hFile;
	unsigned int uiAccessMode;
	char szVolumeName[1 + FS_DISKNAMESIZE + 1];
	char szFileName[FS_PATHSIZE + 1];
	unsigned long ulFileSize;
	TLV_TREE_NODE hParamsTlvTree;
	unsigned char* pFileContent;
	
	(void)AppliNum;

	nResult = FCT_OK;
	if (strcmp(pParamIn->volume_name, "HOST") == 0)
	{
		if (strcmp(pParamIn->file_name, "EMVCOMM.PAR") == 0)
		{
			sprintf(szVolumeName, "/%s", pParamIn->volume_name);
			
			if (FS_mount(szVolumeName, &uiAccessMode) == FS_OK)
			{
				sprintf(szFileName, "/%s/%s", pParamIn->volume_name, pParamIn->file_name);
				hFile = FS_open(szFileName, "r");
				if (hFile != NULL)
				{
					ulFileSize = FS_length(hFile);
					if (ulFileSize != (unsigned long)FS_ERROR)
					{
						pFileContent = umalloc(ulFileSize + 1);
						if (pFileContent != NULL)
						{
							if (FS_read(pFileContent, ulFileSize, 1, hFile) == 1)
							{
								pFileContent[ulFileSize] = '\0';
								hParamsTlvTree = NULL;
								if (TlvTree_Unserialize(&hParamsTlvTree, TLV_TREE_SERIALIZER_XML, pFileContent, ulFileSize) == TLV_TREE_OK)
								{
									if (Params_Set(hParamsTlvTree))
									{
										if (Params_Save())
											nResult = STOP;
										else Params_Load();
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
				
				FS_unmount(szVolumeName);
			}
		}
	}
	
	return nResult;
}
#endif

static int __Main(unsigned int nSize, StructPt* pData)
{
	NO_SEGMENT AppliNum;
	int nResult;

	(void)nSize;

	AppliNum = (NO_SEGMENT)ApplicationGetCurrent();
	switch(pData->service)
	{
	case AFTER_RESET:
		nResult = __after_reset(AppliNum, &pData->Param.AfterReset.param_out);
		break;
	case GIVE_YOUR_DOMAIN:
		nResult = __give_your_domain(AppliNum, &pData->Param.GiveYourType.param_out);
		break;
#ifndef _YES_PROTOCOL_ONLY_
	case FILE_RECEIVED:
		nResult = __file_received(AppliNum, &pData->Param.FileReceived.param_in);
		break;
#endif
	default:
		nResult = FCT_OK;
		break;
	}

	return nResult;
}

static int __Main_Comm(unsigned int nSize, StructProcessStep* pData)
{
	int nResult;
	TLV_TREE_NODE hInputTlvTree;
	TLV_TREE_NODE hOutputTlvTree;
	unsigned char Buffer[2];
	DataElement Elt;
	int bError;
	int bUseTlvTree;

	if (nSize != sizeof(StructProcessStep))
	{
		return STOP;
	}

	hInputTlvTree = NULL;
	hOutputTlvTree = NULL;
	bError = TRUE;

	// Try to deserialise the input TlvTree
	if (TlvTree_Unserialize(&hInputTlvTree, TLV_TREE_SERIALIZER_DEFAULT, (void*)(&pData->DEL), nSize - 8) == TLV_TREE_OK)
	{
		bUseTlvTree = TRUE;
		bError = FALSE;
	}
	else
	{
		bUseTlvTree = FALSE;
		if (nSize == sizeof(StructProcessStep))
		{
			if (CreateTlvTreeFromDel(&hInputTlvTree, &pData->DEL))
				bError = FALSE;
		}
	}

	hOutputTlvTree = TlvTree_New(0);
	if (hOutputTlvTree != NULL)
	{
		if (!bError)
		{
			switch(pData->service)
			{
			// COMM services
			case I_COMM_GET_PROTOCOL_INFO:			nResult = CommGetProtocolInfo((NO_SEGMENT)ApplicationGetCurrent(), hInputTlvTree, hOutputTlvTree);	break;
			case I_COMM_CONFIGURE:					nResult = CommConfigure(hInputTlvTree, hOutputTlvTree);					break;
			case I_COMM_CONNECT:					nResult = CommConnect(hInputTlvTree, hOutputTlvTree);						break;
			case I_COMM_DISCONNECT:					nResult = CommDisconnect(hInputTlvTree, hOutputTlvTree);					break;
			case I_COMM_GET_STATUS:					nResult = CommGetStatus(hInputTlvTree, hOutputTlvTree);					break;
			case I_COMM_SEND_AND_RECEIVE_MESSAGE:	nResult = CommSendAndReceiveMessage(hInputTlvTree, hOutputTlvTree);		break;
			case I_COMM_SEND_MESSAGE:				nResult = CommSendMessage(hInputTlvTree, hOutputTlvTree);					break;
			case I_COMM_READ_MESSAGE:				nResult = CommReadMessage(hInputTlvTree, hOutputTlvTree);					break;
			case I_COMM_RECEIVE_MESSAGE:			nResult = CommReceiveMessage(hInputTlvTree, hOutputTlvTree);				break;

			// Not implemented COMM services
			case I_COMM_ABORT:

			// ISO8583 specific services
			case I_COMM_MAKE_RAW_MESSAGE:
			case I_COMM_SEND_RAW_MESSAGE:
			case I_COMM_RECEIVE_RAW_MESSAGE:
			case I_COMM_PARSE_RAW_MESSAGE:

			default:
				nResult = CommUnknownService(hInputTlvTree, hOutputTlvTree);
				break;
			}
		}
	}

	if (bUseTlvTree)
	{
		if (hOutputTlvTree != NULL)
		{
			if (bError)
			{
				// Set the error
				Buffer[0] = (unsigned char)((COMM_ERR_BAD_PARAMETER >> 8) & 0xff);
				Buffer[1] = (unsigned char)(COMM_ERR_BAD_PARAMETER & 0xff);
				TlvTree_AddChild(hOutputTlvTree, TAG_COMM_STATUS_CODE, Buffer, 2);
			}

			// Serialise the TlvTree
			if (TlvTree_Serialize(hOutputTlvTree, TLV_TREE_SERIALIZER_DEFAULT, (void*)(&pData->DEL), nSize - 8) < 0)
			{
				// Clear output buffer
				memclr(&pData->DEL, nSize - 8);
			}
		}
		else
		{
			// Clear output buffer
			memclr(&pData->DEL, nSize - 8);
		}
	}
	else
	{
		if (!bError)
		{
			// Convert the output TlvTree to the output DEL
			_DEL_Init(&pData->DEL);
			bError = !AddTlvTreeToDelValue(&pData->DEL, hOutputTlvTree);
		}

		if (bError)
		{
			// Set the error
			_DEL_Init(&pData->DEL);

			Buffer[0] = (unsigned char)((COMM_ERR_BAD_PARAMETER >> 8) & 0xff);
			Buffer[1] = (unsigned char)(COMM_ERR_BAD_PARAMETER & 0xff);

			Elt.tag = TAG_COMM_STATUS_CODE;
			Elt.length = 2;
			Elt.ptValue = Buffer;
			_DEL_AddDataElement(&pData->DEL, &Elt);
		}
	}

	if (hInputTlvTree != NULL)
	{
		TlvTree_Release(hInputTlvTree);
		hInputTlvTree = NULL;
	}
	if (hOutputTlvTree != NULL)
	{
		TlvTree_Release(hOutputTlvTree);
		hOutputTlvTree = NULL;
	}

	return FCT_OK;
}

static int __give_interface(unsigned short AppliNum, void* pParamIn, void* pParamOut)
{
	int i;

	(void)pParamIn;
	(void)pParamOut;

	for(i = 0; i < (int)(sizeof(Services) / sizeof(Services[0])); i++)
		Services[i].appli_id = AppliNum;

	ServiceRegister((sizeof(Services) / sizeof(Services[0])), Services);

	return FCT_OK;
}

void entry(void)
{
	object_info_t ObjectInfo;

	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
	__give_interface(ObjectInfo.application_type, NULL, NULL);
}
