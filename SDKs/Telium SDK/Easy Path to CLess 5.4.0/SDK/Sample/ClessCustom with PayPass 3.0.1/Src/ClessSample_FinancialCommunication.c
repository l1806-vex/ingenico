//! \file
//! This module contains the functions needed for exchanges
//  with the acquirer host  
//

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Constant declarations //////////////////////////////////////

#define COMM_AUTHOR_MSG						1
#define COMM_ADVICE_MSG						2
#define COMM_REVERSAL_MSG					3
#define COMM_START_TRANSAC_DOWNLOAD			4
#define COMM_TRANSAC_DOWNLOAD				5
#define COMM_TERMINATE_TRANSAC_DOWNLOAD		6


/////////////////////////////////////////////////////////////////
//// Global Data Definition /////////////////////////////////////

static int isConnected;
static DEL outDEL, ConfigDEL;
static DEL * pDelResult;
static DEL pt_AuthoDEL;


/////////////////////////////////////////////////////////////////
//// Static function declarations ///////////////////////////////

static void __ClessSample_FinancialCommunication_BuildCommDel (DEL * pDelIn, const int nMsgType);
static int __ClessSample_FinancialCommunication_HostConfigConnect(void);
static int __ClessSample_FinancialCommunication_HostCommConnect (void);
static int __ClessSample_FinancialCommunication_HostCommConfigure (DEL * inDEL);
static int __ClessSample_FinancialCommunication_IsCommComponentLoaded (const unsigned char ucAppliType);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//===============================================================
// Function name	:	EMVCUST_Build_comm_del
// Description		:	

static void __ClessSample_FinancialCommunication_BuildCommDel (DEL * pDelIn, const int nMsgType)
{
	DataElement elt_DEL;
	static unsigned char MessageType[2];

	// Set the message type
	switch(nMsgType)
	{
	case COMM_AUTHOR_MSG:
		MessageType[0] = (unsigned char)(COMM_MSG_AUTHORISATION_REQUEST >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_AUTHORISATION_REQUEST);
		break;
	case COMM_ADVICE_MSG:
		MessageType[0] = (unsigned char)(COMM_MSG_ONLINE_ADVICE >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_ONLINE_ADVICE);
		break;
	case COMM_REVERSAL_MSG:
		MessageType[0] = (unsigned char)(COMM_MSG_REVERSAL_REQUEST >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_REVERSAL_REQUEST);
		break;
	case COMM_START_TRANSAC_DOWNLOAD:
		MessageType[0] = (unsigned char)(COMM_MSG_COLLECTION_INITIALISATION >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_COLLECTION_INITIALISATION);
		break;
	case COMM_TRANSAC_DOWNLOAD:
		MessageType[0] = (unsigned char)(COMM_MSG_COLLECTION_ITEM >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_COLLECTION_ITEM);
		break;
	case COMM_TERMINATE_TRANSAC_DOWNLOAD:
		MessageType[0] = (unsigned char)(COMM_MSG_COLLECTION_TERMINATION >> 8);
		MessageType[1] = (unsigned char)(COMM_MSG_COLLECTION_TERMINATION);
		break;
	default:
		MessageType[0] = 0;
		MessageType[1] = 0;
		break;
	}
	elt_DEL.tag = TAG_COMM_MESSAGE_TYPE;
	elt_DEL.length = TAG_COMM_MESSAGE_TYPE_LENGTH;
	elt_DEL.ptValue = MessageType;
	
	DEL_AddDataElement(pDelIn, &elt_DEL);
}



//! \brief Check the presence of an application.
//! \param[in] ucAppliType Application type to check presence.
//! \return
//!		- \ref TRUE if application is present.
//!		- \ref FALSE if not.

static int __ClessSample_FinancialCommunication_IsCommComponentLoaded (const unsigned char ucAppliType)
{
	int nCommExist;
	NO_SEGMENT seg_number;
	NO_SEGMENT i;
	object_info_t info;

	nCommExist = FALSE;

	// Get the segment number of the research application
	seg_number = (NO_SEGMENT)num_seg();
	
	// Try to find the application
	for (i = 0; i < seg_number; i++)
	{
		if (ObjectGetInfo  (OBJECT_TYPE_APPLI, i, &info) == 0)
		{
			if ((info.application_type) == ucAppliType)
			{
				// Component found
				nCommExist= TRUE;
			}
		}
	}

	return (nCommExist);
}



//! \brief This function calls the service that initialise the communication parameters
//! \param[in] inDEL DEL containing the configuration parameters for communication component.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

static int __ClessSample_FinancialCommunication_HostCommConfigure (DEL * inDEL)
{
	int nResult;
	DataElement * pElt;
	unsigned short usStatusCode;

	nResult = FALSE;
	
	// Configure Communication Component
	pDelResult = COMM_Configure (inDEL);

	// Search the TAG_COMM_STATUS_CODE tag
	pElt = DEL_GetFirstDataElement(pDelResult);
	
	while (pElt != NULL)
	{
		if (pElt->tag == TAG_COMM_STATUS_CODE)
		{
			usStatusCode = (unsigned short)((pElt->ptValue[0] << 8) + pElt->ptValue[1]);
			if (usStatusCode == COMM_PROCESS_COMPLETED)
			{
				nResult = TRUE;
			}
			else
			{
				GTL_Traces_TraceDebug("__ClessSample_FinancialCommunication_HostCommConfigure : Error occurred (status = %02x)", usStatusCode);
			}
			
			goto End;
		}
		else
		{
			pElt = DEL_GetNextDataElement(pDelResult);
		}
	}
	
End:
	return (nResult);
}



//! \brief This function establishes the connection with the host.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

static int __ClessSample_FinancialCommunication_HostCommConnect (void)
{
	int nResult;
	DataElement * pElt;
	unsigned short usStatusCode;

	nResult = FALSE;
	
	// Establish connection with the Communication Component
	pDelResult = COMM_Connect (&outDEL);

	// Search the TAG_COMM_STATUS_CODE tag
	pElt = DEL_GetFirstDataElement(pDelResult);
	
	while (pElt != NULL)
	{
		if (pElt->tag == TAG_COMM_STATUS_CODE)
		{
			usStatusCode = (unsigned short)((pElt->ptValue[0] << 8) + pElt->ptValue[1]);
			if (usStatusCode == COMM_PROCESS_COMPLETED)
			{
				nResult = TRUE;
			}
			else
			{
				GTL_Traces_TraceDebug("__ClessSample_FinancialCommunication_HostCommConnect : Error occurred (status = %02x)", usStatusCode);
			}
			
			goto End;
		}
		else
		{
			pElt = DEL_GetNextDataElement(pDelResult);
		}
	}
	
End:
	return (nResult);
}



//! \brief Configuration and connection to the communication component.
//! \return
//!		- \ref TRUE if configuration and connection correctly performed.
//!		- \ref FALSE if not.

static int __ClessSample_FinancialCommunication_HostConfigConnect(void)
{
	int bIsConnected = FALSE;

	// Init Configuration DEL
	DEL_init(&ConfigDEL);

	// Check communication component is loaded
	if (__ClessSample_FinancialCommunication_IsCommComponentLoaded(I_COMM_DEFAULT_TYPE_APPLI))
	{
		// Configure communication component
		if (__ClessSample_FinancialCommunication_HostCommConfigure (&ConfigDEL) == TRUE)
		{
			// Establish the connection with the communication component
			if (__ClessSample_FinancialCommunication_HostCommConnect() == TRUE)
			{
				bIsConnected = TRUE;
			}
			else
			{
				GTL_Traces_TraceDebug ("__ClessSample_FinancialCommunication_HostConfigConnect : __ClessSample_FinancialCommunication_HostCommConnect fails\n");
			}
		}
		else
		{
			GTL_Traces_TraceDebug ("__ClessSample_FinancialCommunication_HostConfigConnect : __ClessSample_FinancialCommunication_HostCommConfigure failed\n");
		}
	}
	else
	{
		GTL_Traces_TraceDebug ("__ClessSample_FinancialCommunication_HostConfigConnect : __ClessSample_FinancialCommunication_IsCommComponentLoaded failed\n");
	}

  	return (bIsConnected);
}



//! \brief Manage the online authorisation with the communication component.
//! \param[in,out] pSharedData Data to be sent to the host for onoline authorisation (input) and response tags are added to it (output).
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int ClessSample_FinancialCommunication_ManageAuthorisation (T_SHARED_DATA_STRUCT * pSharedData)
{
	DEL *pt_OutputDEL;
	DataElement Elt;
	DataElement * pElt;
	int cr;
	int nPosition;
	unsigned long ulReadTag, ulReadLength;
	unsigned char * pReadValue;
	unsigned short usStatusCode;
	int nResult = FALSE;

	// Init data
	isConnected = FALSE;
	DEL_init(&outDEL);
	
	// Connect with the acquirer host                                      
	if (!isConnected)
	{
		isConnected = __ClessSample_FinancialCommunication_HostConfigConnect();
	}
	
	if (isConnected)
	{
		DEL_init(&pt_AuthoDEL);

		__ClessSample_FinancialCommunication_BuildCommDel (&pt_AuthoDEL, COMM_AUTHOR_MSG);
		
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		
		do
		{
			cr = GTL_SharedExchange_GetNext(pSharedData, &nPosition, &ulReadTag, &ulReadLength, (const unsigned char **)&pReadValue);
			
			if (cr == STATUS_SHARED_EXCHANGE_OK)
			{
				Elt.tag = ulReadTag;
				Elt.length = (int)ulReadLength;
				Elt.ptValue = pReadValue;
				
				DEL_AddDataElement(&pt_AuthoDEL, &Elt);
			}
		} while (cr == STATUS_SHARED_EXCHANGE_OK);
		
		// Send the message and wait for response
		pt_OutputDEL = COMM_Send_And_Receive_Message (&pt_AuthoDEL);

		// Add the content of pt_OutputDEL in pSharedData
		pElt = DEL_GetFirstDataElement(pt_OutputDEL);
		
		while (pElt != NULL)
		{
			GTL_SharedExchange_AddTag(pSharedData, pElt->tag, pElt->length, pElt->ptValue);
			
			if (pElt->tag == TAG_COMM_STATUS_CODE)
			{
				usStatusCode = (unsigned short)((pElt->ptValue[0] << 8) + pElt->ptValue[1]);
				if (usStatusCode == COMM_PROCESS_COMPLETED)
				{
					nResult = TRUE;
				}
				else
				{
					GTL_Traces_TraceDebug("ClessSample_FinancialCommunication_ManageAuthorisation : COMM_Send_And_Receive_Message error occurred (status = %02x)", usStatusCode);
				}
			}
			pElt = DEL_GetNextDataElement(pt_OutputDEL);
		}
		
		if (isConnected)
		{
			COMM_Disconnect (NULL);
			isConnected = FALSE;
		}  
		
	}
	else
	{
		GTL_Traces_TraceDebug("ClessSample_FinancialCommunication_ManageAuthorisation : Not connected");
	}
	
	return (nResult);
}
