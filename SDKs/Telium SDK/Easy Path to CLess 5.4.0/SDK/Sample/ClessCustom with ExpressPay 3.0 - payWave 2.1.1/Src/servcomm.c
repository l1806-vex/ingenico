// ========================================================================	/
// Project       : -                                                        /
// Module        : COMM                                                     /
// Creation Date : 08/12/2004                                               /
// Author        : M. GATESOUPE                                             /
// Description   : This module contains the interface with                  /
//                 a communication component.                               /
// ========================================================================	/
// SAGEM Monetel                                                            /
// 1 rue Claude Chappe - BP 346                                             /
// 07503 Guilherand-Granges                                                 /
// ========================================================================	/
// REVISION HISTORY                                                         /
// ========================================================================	/
// Date          :                                                          /
// Author        :                                                          /
// Description   :                                                          /
// ========================================================================	/

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static unsigned short g_usCommAppType = I_COMM_DEFAULT_TYPE_APPLI;
static StructProcessStep g_ProcessStep;
static DEL g_Del;


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static void COMM_CopyInput(const DEL* aDEL, _DEL_* _vDEL);
static void COMM_CopyOutput(_DEL_* _vDEL, DEL* aDEL);
static DEL* COMM_Call_Service(unsigned short usAppType, unsigned short usServiceID,
					unsigned short usInfoAppType, unsigned short usInfoService,
					int nInfoFunction, const DEL* pInputDel,
					StructProcessStep* pProcessStep, DEL* pOutputDel);
static DEL* COMM_Service(unsigned short usServiceID, const DEL* pInputDel);


//// Functions //////////////////////////////////////////////////

/*void _DEL_init(_DEL_ *aDEL)
{
	int i;

    aDEL->current = 0;
	aDEL->count   = 0;
	for (i=0; i<MAX_DATA_ELEMENT; i++)
	{
      aDEL->list[i].tag = 0;
      aDEL->list[i].length = 0;
      memclr(aDEL->list[i].ptValue,sizeof(aDEL->list[i].ptValue));
	}
}*/


/*void CopyEntree(DEL *aDEL, _DEL_ *_vDEL)
{
	int i;

    _DEL_init(_vDEL);
	if (aDEL!=NULL)
	{
      _vDEL->current = aDEL->current;
	  _vDEL->count   = aDEL->count;
	  for (i=0; i<aDEL->count; i++)
	  {
        _vDEL->list[i].tag    = aDEL->list[i].tag;
        _vDEL->list[i].length = aDEL->list[i].length;
	    if (aDEL->list[i].ptValue!=NULL)
		{
          memcpy(_vDEL->list[i].ptValue,aDEL->list[i].ptValue,aDEL->list[i].length);
		}
	  }
	}
}*/


/*void CopySortie(_DEL_ *_vDEL,DEL *aDEL)
{
	int i;

    DEL_init(aDEL);
    aDEL->current = _vDEL->current;
	aDEL->count   = _vDEL->count;
	for (i=0; i<_vDEL->count; i++)
	{
      aDEL->list[i].tag     = _vDEL->list[i].tag;
      aDEL->list[i].length  = _vDEL->list[i].length;
      aDEL->list[i].ptValue = _vDEL->list[i].ptValue;
	}
}*/


void COMM_CopyInput(const DEL* aDEL, _DEL_* _vDEL)
{
	CopyEntree((DEL*)aDEL, _vDEL);
}

void COMM_CopyOutput(_DEL_* _vDEL, DEL* aDEL)
{
	CopySortie(_vDEL, aDEL);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

static DEL* COMM_Call_Service(unsigned short usAppType, unsigned short usServiceID,
					unsigned short usInfoAppType, unsigned short usInfoService,
					int nInfoFunction, const DEL* pInputDel,
					StructProcessStep* pProcessStep, DEL* pOutputDel)
{
	unsigned char ucPriority;
	int nResult;

	// Does the service exist ?
	if (ServiceGet(usAppType, usServiceID, &ucPriority) == 0)
	{
		if (pInputDel != NULL)
		{
			// Copy the input DEL to a global _DEL_ object
			COMM_CopyInput(pInputDel, &pProcessStep->DEL);
		}
		else
		{
			// Empty the global _DEL_ object
			_DEL_init(&pProcessStep->DEL);
		}

		// Call the service
		pProcessStep->type_code = usInfoAppType;
		pProcessStep->service = usInfoService;
		pProcessStep->function = nInfoFunction;
		ServiceCall(usAppType, usServiceID, sizeof(StructProcessStep), pProcessStep, &nResult);

		if (pOutputDel != NULL)
		{
			// Copy the filled local _DEL_ object into a global DEL object
			COMM_CopyOutput(&pProcessStep->DEL, pOutputDel);
		}

		return (pOutputDel);
	}
	else
	{
		// The service does not exist
		return (NULL);
	}
}

static DEL* COMM_Service(unsigned short usServiceID, const DEL* pInputDel)
{
	DEL* pOutputDel;

	// Call the communication component
	pOutputDel = COMM_Call_Service(g_usCommAppType, usServiceID, g_usCommAppType, usServiceID,
									0, pInputDel, &g_ProcessStep, &g_Del);

#ifdef _TRACK_IAC_
	// Send the input and output DEL to the SPY tool
	TrackIAC(g_usCommAppType, usServiceID, 0, pInputDel, pOutputDel);
#endif

	return (pOutputDel);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

void COMM_Set_Application_Type(unsigned short usAppType)
{
	g_usCommAppType = usAppType;
}

unsigned short COMM_Get_Application_Type(void)
{
	return (g_usCommAppType);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

DEL* COMM_Initiate_Online_Transaction(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_INITIATE_ONLINE_TRANSACTION, pInputDel);
}

DEL* COMM_Authorisation_Request(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_AUTHORISATION_REQUEST, pInputDel);
}

DEL* COMM_Send_Online_Advice(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_SEND_ONLINE_ADVICE, pInputDel);
}

DEL* COMM_Reversal(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_REVERSAL, pInputDel);
}

DEL* COMM_Send_Financial_Transaction_Request(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_SEND_FINANCIAL_TRANSACTION_REQUEST, pInputDel);
}

DEL* COMM_Financial_Transaction_Confirmation(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_FINANCIAL_TRANSACTION_CONFIRMATION, pInputDel);
}

DEL* COMM_Terminate_Online_Transaction(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_TERMINATE_ONLINE_TRANSACTION, pInputDel);
}

DEL* COMM_Initiate_Batch_Data_Capture(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_INITIATE_BATCH_DATA_CAPTURE, pInputDel);
}

DEL* COMM_Send_Batch_Data(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_SEND_BATCH_DATA, pInputDel);
}

DEL* COMM_Terminate_Batch_Data_Capture(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_TERMINATE_BATCH_DATA_CAPTURE, pInputDel);
}

DEL* COMM_Perform_Reconciliation(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_PERFORM_RECONCILIATION, pInputDel);
}

DEL* COMM_Get_Black_List(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_GET_BLACK_LIST, pInputDel);
}

DEL* COMM_PIN_Online_Request(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_PIN_ONLINE_REQUEST, pInputDel);
}

/////////////////////////////////////////////////////////////////

DEL* COMM_Get_Protocol_Info(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_GET_PROTOCOL_INFO, pInputDel);
}

DEL* COMM_Configure(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_CONFIGURE, pInputDel);
}

DEL* COMM_Connect(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_CONNECT, pInputDel);
}

DEL* COMM_Disconnect(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_DISCONNECT, pInputDel);
}

DEL* COMM_Send_And_Receive_Message(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_SEND_AND_RECEIVE_MESSAGE, pInputDel);
}

DEL* COMM_Send_Message(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_SEND_MESSAGE, pInputDel);
}

DEL* COMM_Get_Status(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_GET_STATUS, pInputDel);
}

DEL* COMM_Read_Message(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_READ_MESSAGE, pInputDel);
}

DEL* COMM_Abort(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_ABORT, pInputDel);
}

DEL* COMM_Receive_Message(const DEL* pInputDel)
{
	return COMM_Service(I_COMM_RECEIVE_MESSAGE, pInputDel);
}
