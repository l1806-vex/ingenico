/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////
#include "SDK30.h"
#include "TlvTree.h"
#include "LinkLayer.h"

#include "Assert.h"

#include "Communication.h"

//// Macros & preprocessor definitions //////////////////////////
#ifndef _SIMULPC_
#define _USE_THREAD_
#endif

#define __500_MSECONDS__	50
#define __5_SECONDS__		500
#define __60_SECONDS__		6000

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////
T__LL_CONFIGURATION CurrentConfig;
static LL_HANDLE hSession;
#ifdef _USE_THREAD_
static int nConnectError;
static short MainTask;
int bThreadTerminated;
#endif

//// Static function definitions ////////////////////////////////
#ifdef _USE_THREAD_
static Word ConnectThread(void);
#endif
static void DisplayError(char* szName, int nError);
static int Connect(void);
static void Disconnect(void);
static void ModeNone(void);
static void ModeSend(void);
static void ModeEcho(void);
static void ModeHttp(void);
static void ModeGreekHost(void);
static void ModeMalaysianHost(void);
static void ManageComm(void);

//// Functions //////////////////////////////////////////////////
void TraceDebug(const char* pString, ...)
{
#ifdef __TRACE_DEBUG__
	char String[512];
	int nLength;
	va_list Params;

	va_start(Params, pString);

#ifdef __GNUC__
	nLength = vsprintf(String, pString, &Params);
#else
	nLength = vsprintf(String, pString, Params);
#endif
	va_end(Params);

	trace(0, nLength, String);
#endif // __TRACE_DEBUG__
}


void InitCommunication(void)
{
	hSession = NULL;
	InitDefaultConfig();
}

void InitDefaultConfig(void)
{
	memset(&CurrentConfig, 0, sizeof(CurrentConfig));

//	CurrentConfig.m_nLink = LL_PHYSICAL_V_COM0;
	CurrentConfig.m_nLink = LL_PHYSICAL_V_MODEM;
//	CurrentConfig.m_nLink = LL_PHYSICAL_V_ETHERNET;

	CurrentConfig.m_nBaudrate = LL_PHYSICAL_V_BAUDRATE_115200;
	CurrentConfig.m_nBitsPerByte = LL_PHYSICAL_V_8_BITS;
	CurrentConfig.m_nStopBits = LL_PHYSICAL_V_1_STOP;
	CurrentConfig.m_nParity = LL_PHYSICAL_V_NO_PARITY;
	CurrentConfig.m_nFlowCtrl = LL_PHYSICAL_V_NO_FLOW_CTRL;

//	CurrentConfig.m_bUseModem = FALSE;
	CurrentConfig.m_bUseModem = TRUE;
	CurrentConfig.m_nModemCmdTerminator = LL_MODEM_V_CMD_TERMINATOR_CR;

	strcpy(CurrentConfig.m_szInitString, DEFAULT_INIT_STRING_ASYNC);
	strcpy(CurrentConfig.m_szPhoneNumber, DEFAULT_PHONE_NUMBER_ASYNC);
//	strcpy(CurrentConfig.m_szInitString, DEFAULT_INIT_STRING_SYNC);
//	strcpy(CurrentConfig.m_szPhoneNumber, DEFAULT_PHONE_NUMBER_SYNC);
//	strcpy(CurrentConfig.m_szInitString, DEFAULT_INIT_STRING_GREECE);
//	strcpy(CurrentConfig.m_szPhoneNumber, DEFAULT_PHONE_NUMBER_GREECE);
//	strcpy(CurrentConfig.m_szInitString, DEFAULT_INIT_STRING_MALAYSIA);
//	strcpy(CurrentConfig.m_szPhoneNumber, DEFAULT_PHONE_NUMBER_MALAYSIA);

	CurrentConfig.m_bUseGsm			= FALSE;
	CurrentConfig.m_nGsmMode		= LL_GSM_V_MODE_TRANSPARENT;
	CurrentConfig.m_nGsmModulation	= LL_GSM_V_MODULATION_V32_9600;
	CurrentConfig.m_nConnectionTimeout	= 6000;

	CurrentConfig.m_bUseHdlc = FALSE;
//	CurrentConfig.m_bUseHdlc = TRUE;

	CurrentConfig.m_bUsePpp = FALSE;
//	CurrentConfig.m_bUsePpp = TRUE;
	strcpy(CurrentConfig.m_szLogin, DEFAULT_LOGIN);
	strcpy(CurrentConfig.m_szPassword, DEFAULT_PASSWORD);

	CurrentConfig.m_bUseTcpIp = FALSE;
//	CurrentConfig.m_bUseTcpIp = TRUE;
	strcpy(CurrentConfig.m_szHostName, DEFAULT_HOST_NAME_PPP);
	CurrentConfig.m_nPort = DEFAULT_PORT_PPP;
//	strcpy(CurrentConfig.m_szHostName, DEFAULT_HOST_NAME_ETHERNET);
//	CurrentConfig.m_nPort = DEFAULT_PORT_ETHERNET;

	CurrentConfig.m_nTestMode = MODE_NONE;
//	CurrentConfig.m_nTestMode = MODE_SEND;
//	CurrentConfig.m_nTestMode = MODE_ECHO;
//	CurrentConfig.m_nTestMode = MODE_DOWNLOAD_HTTP;
//	CurrentConfig.m_nTestMode = MODE_GREEK_HOST;
//	CurrentConfig.m_nTestMode = MODE_MALAYSIAN_HOST;

	CurrentConfig.m_bUseGprs = FALSE;
	strcpy(CurrentConfig.m_szAPN, DEFAULT_APN);

	strcpy(CurrentConfig.m_szPinCode, DEFAULT_PIN_CODE);
}

static void DisplayError(char* szName, int nError)
{
	FILE* hDisplay;
	char szString[1024];

	sprintf(szString, "\x1b" "%s =\n %i", szName, nError);

	hDisplay = fopen("DISPLAY", "w");
	printf(szString);
	fclose(hDisplay);

	ttestall(0, 200);
}


int ConnectNetworkGPRS( unsigned int nWaitTimeout, unsigned int nWaitMaxTimeout )
{
	unsigned int nWaitTotal = 0;

	int nError;
	int nStatus;

	FILE *hDisplay = NULL;
//	char szString[100];

	//
	hDisplay = fopen("DISPLAY", "w");
	startupcv20(0, 0);
	printf( "\x1b" "CONNECTING NETWORK...");
	fclose(hDisplay);

	LL_GPRS_Start( CurrentConfig.m_szPinCode, CurrentConfig.m_szAPN );

	while((( nError = LL_Network_GetStatus( LL_PHYSICAL_V_GPRS, &nStatus )) == LL_ERROR_NETWORK_NOT_READY ) && 
		  ( nWaitTotal < nWaitMaxTimeout ))
	{
		if( nStatus == LL_STATUS_GPRS_AVAILABLE )
		{
			LL_GPRS_Connect( CurrentConfig.m_szAPN, "", "", 
							 nWaitMaxTimeout - nWaitTotal );
		}
		else
		{
			ttestall( 0, nWaitTimeout );
			nWaitTotal += nWaitTimeout;
		}
	}

	// Display the status.
	hDisplay = fopen("DISPLAY", "w");
	startupcv20(0, 0);
	printf( "\x1b");

	switch( nError )
	{
	case LL_ERROR_OK:
		printf( "CONNECTED !!" );
		break;

	case LL_ERROR_NETWORK_NOT_SUPPORTED:
		printf( "NOT SUPPORTED!!" );
		break;

	default:
		{
			switch( nStatus )
			{
			case LL_STATUS_GPRS_DISCONNECTED:
				printf( "\x1b" "DISCONNECTED" );
				break;

			case LL_STATUS_GPRS_ERROR_NO_SIM:
				printf( "NO SIM" );
				break;

			case LL_STATUS_GPRS_ERROR_SIM_LOCK:
				printf( "SIM LOCK" );
				break;

			case LL_STATUS_GPRS_ERROR_BAD_PIN:
				printf( "BAD PIN" );
				break;

			case LL_STATUS_GPRS_ERROR_NO_PIN:
				printf( "NO PIN" );
				break;

			case LL_STATUS_GPRS_ERROR_PPP:
				printf( "ERROR PPP" );
				break;

			case LL_STATUS_GPRS_ERROR_UNKNOWN:
				printf( "ERROR PPP" );
				break;

			case LL_STATUS_GPRS_CONNECTING:
				printf( "CONNECTION IN PROGRESS" );
				break;
			case LL_STATUS_GPRS_AVAILABLE:
				printf( "GPRS READY" );
				break;

			case LL_STATUS_GPRS_CONNECTING_PPP:
				printf( "PPP..." );
				break;

			case LL_STATUS_GPRS_CONNECTED:
				printf( "CONNECTED !!" );
				break;

			default:
				printf( "???" );
				break;
			}
		}
		break;
	}

	fclose(hDisplay);
	ttestall( 0, __5_SECONDS__ );

	return nError;
}

int ConnectNetworkGSM(  unsigned int nWaitTimeout, unsigned int nWaitMaxTimeout )
{
	unsigned int nWaitTotal = 0;

	int nError;
	int nStatus;


	FILE *hDisplay = NULL;
//	char szString[100];

	//
	TraceDebug( "***ConnectNetworkGSM !" );

	hDisplay = fopen("DISPLAY", "w");
	startupcv20(0, 0);
	printf( "\x1b" "CONNECTING NETWORK...");
	fclose(hDisplay);

	LL_GSM_Start( CurrentConfig.m_szPinCode );

	while((( nError = LL_Network_GetStatus( LL_PHYSICAL_V_GSM, &nStatus )) == LL_ERROR_NETWORK_NOT_READY ) && 
		  ( nWaitTotal < nWaitMaxTimeout ))
	{
		ttestall( 0, nWaitTimeout );
		nWaitTotal += nWaitTimeout;
	}

	// Display the status.
	hDisplay = fopen("DISPLAY", "w");
	startupcv20(0, 0);
	printf( "\x1b");

	switch( nError )
	{
	case LL_ERROR_OK:
		printf( "GSM CONNECTED !!" );
		break;

	case LL_ERROR_NETWORK_NOT_SUPPORTED:
		printf( "NOT SUPPORTED!!" );
		break;

	default:
		{
			switch( nStatus )
			{
			case LL_STATUS_GSM_DISCONNECTED:
				printf( "\x1b" "DISCONNECTED" );
				break;

			case LL_STATUS_GSM_ERROR_NO_SIM:
				printf( "NO SIM" );
				break;

			case LL_STATUS_GSM_ERROR_SIM_LOCK:
				printf( "SIM LOCK" );
				break;

			case LL_STATUS_GSM_ERROR_BAD_PIN:
				printf( "BAD PIN" );
				break;

			case LL_STATUS_GSM_ERROR_NO_PIN:
				printf( "NO PIN" );
				break;

			case LL_STATUS_GSM_CONNECTED:
				printf( "CONNECTED !!" );
				break;

			case LL_STATUS_GSM_BUSY:
				printf( "BUSY !!" );
				break;

			case LL_STATUS_GSM_CALL_IN_PROGRESS:
				printf( "IN CALL !!" );
				break;

			default:
				printf( "???" );
				break;
			}
		}
	}

	fclose(hDisplay);
	ttestall( 0, __5_SECONDS__ );

	return nError;
}


#ifdef _USE_THREAD_
static Word ConnectThread(void)
{
	TraceDebug( "***ConnectThread !" );

	nConnectError = LL_Connect(hSession);
	//nConnectError = LL_Disconnect(hSession);

	TraceDebug( "***Res LL_Connect %d !", nConnectError );

/*	if (hSession != NULL)
	{
		LL_Configure(&hSession, NULL);
		hSession = NULL;
	}
*/
	SignalEvent(MainTask, 30);
	bThreadTerminated = TRUE;
	ttestall(0, 0);
	return 0;
}
#endif

static int Connect(void)
{
	FILE* hDisplay;
	TLV_TREE_NODE hConfig			= NULL;
	TLV_TREE_NODE hPhysicalConfig	= NULL;
	TLV_TREE_NODE hDataLinkConfig	= NULL;
	TLV_TREE_NODE hTransportConfig	= NULL;
	int nError;
	int nKey;
#ifdef _USE_THREAD_
	FILE* hKeyboard;
	unsigned int nEvent;
	t_topstack* pThread;
	int bEnd;
#else
	int nConnectError;
#endif

	TraceDebug( "***Connect !" );

	// Needed to call the link layer
	hConfig = TlvTree_New( LL_TAG_LINK_LAYER_CONFIG );	

	// Physical layer parameters
	hPhysicalConfig = TlvTree_AddChild( hConfig, LL_TAG_PHYSICAL_LAYER_CONFIG, NULL, 0 );

	//
	TlvTree_AddChildInteger( hPhysicalConfig, LL_PHYSICAL_T_LINK, 
							 (unsigned char)CurrentConfig.m_nLink, LL_PHYSICAL_L_LINK );

	TlvTree_AddChildInteger( hPhysicalConfig, LL_PHYSICAL_T_BAUDRATE,
							 CurrentConfig.m_nBaudrate, LL_PHYSICAL_L_BAUDRATE );

	if (CurrentConfig.m_bUseGsm)
	{
		// Modulation.
		TlvTree_AddChildInteger( hPhysicalConfig, LL_GSM_T_MODULATION,
								 CurrentConfig.m_nGsmModulation, LL_GSM_L_MODULATION );

		// Mode (RLP/Transparent).
		TlvTree_AddChildInteger( hPhysicalConfig, LL_GSM_T_MODE,
								 (unsigned char) CurrentConfig.m_nGsmMode, LL_GSM_L_MODE );

	
		// Connection timeout.
		TlvTree_AddChildInteger( hPhysicalConfig, LL_GSM_T_CONNECTION_TIMEOUT,
								 CurrentConfig.m_nConnectionTimeout, LL_GSM_L_CONNECTION_TIMEOUT );

		// Phone number.
		TlvTree_AddChildString( hPhysicalConfig, LL_GSM_T_PHONE_NUMBER, CurrentConfig.m_szPhoneNumber );
		
	}

	if (CurrentConfig.m_bUseModem)
	{
		// Connection timeout.
		TlvTree_AddChildInteger( hPhysicalConfig, LL_MODEM_T_CMD_TERMINATOR,
								 (unsigned char) CurrentConfig.m_nModemCmdTerminator, LL_MODEM_L_CMD_TERMINATOR );

		// Initialization String.
		TlvTree_AddChildString( hPhysicalConfig, LL_MODEM_T_INIT_STRING, CurrentConfig.m_szInitString );

		// Phone number.
		TlvTree_AddChildString( hPhysicalConfig, LL_MODEM_T_PHONE_NUMBER, CurrentConfig.m_szPhoneNumber );
	}

	// Data link layer parameters


	// HDLC
	if (CurrentConfig.m_bUseHdlc != USE_HDLC_NO)
	{
	    hDataLinkConfig = TlvTree_AddChild( hConfig, LL_TAG_DATA_LINK_LAYER_CONFIG, NULL, 0 );
		
        TlvTree_AddChildInteger( hDataLinkConfig, LL_DATA_LINK_T_PROTOCOL,
								 LL_DATA_LINK_V_HDLC, LL_DATA_LINK_L_PROTOCOL );


		TlvTree_AddChildInteger( hDataLinkConfig, LL_HDLC_T_MIN_RESEND_REQUESTS,
								 2, LL_HDLC_L_MIN_RESEND_REQUESTS );
	}

	// PPP
	if (CurrentConfig.m_bUsePpp)
	{
	    hDataLinkConfig = TlvTree_AddChild( hConfig, LL_TAG_DATA_LINK_LAYER_CONFIG, NULL, 0 );
	    
		TlvTree_AddChildInteger( hDataLinkConfig, LL_DATA_LINK_T_PROTOCOL,
								 LL_DATA_LINK_V_PPP, LL_DATA_LINK_L_PROTOCOL );


		TlvTree_AddChildString( hDataLinkConfig, LL_PPP_T_LOGIN,	CurrentConfig.m_szLogin );
		TlvTree_AddChildString( hDataLinkConfig, LL_PPP_T_PASSWORD, CurrentConfig.m_szPassword );
	}

	
	// Transport layer parameters
	
    // TCP/IP
	if (CurrentConfig.m_bUseTcpIp)
	{
	    hTransportConfig = TlvTree_AddChild( hConfig, LL_TAG_TRANSPORT_LAYER_CONFIG, NULL, 0 );
	    
		TlvTree_AddChildInteger( hTransportConfig, LL_TRANSPORT_T_PROTOCOL,
								 LL_TRANSPORT_V_TCPIP, LL_TRANSPORT_L_PROTOCOL );

		TlvTree_AddChildString( hTransportConfig, LL_TCPIP_T_HOST_NAME,	CurrentConfig.m_szHostName );

		TlvTree_AddChildInteger( hTransportConfig, LL_TCPIP_T_PORT,
								 CurrentConfig.m_nPort, LL_TCPIP_L_PORT );
	}

	hDisplay = fopen("DISPLAY", "w");
	startupcv20(0, 0);
	printf("\x1b" "\nINITIALISING...");
	fclose(hDisplay);

	// Configure the Link Layer
	nError = LL_Configure(&hSession, hConfig );

	TlvTree_Release( hConfig );

	if (nError != LL_ERROR_OK)
	{
		DisplayError("LL_Configure", nError);
		return FALSE;
	}


	TraceDebug( "***Result LL_Configure %d !", nError );

	hDisplay = fopen("DISPLAY", "w");
	startupcv20(0, 0);
	printf("\x1b" "\n CONNECTING...");
	fclose(hDisplay);

	nKey = T_VAL;
#ifdef _USE_THREAD_
	ttestall(1 << 30, 1);

	bThreadTerminated = FALSE;
	nConnectError = LL_ERROR_OK;
	MainTask = CurrentTask();
	pThread = fork(ConnectThread, NULL, 0);
	if (pThread == NULL)
	{
		DisplayError("fork", 0);
		return FALSE;
	}

	bEnd = FALSE;
	hKeyboard = fopen("KEYBOARD", "r");
	do
	{
		nEvent = ttestall((1 << 30) | KEYBOARD, 0);
		if ((nEvent & KEYBOARD) != 0)
		{
			nKey = getchar();
			if (nKey == T_ANN)
				bEnd = TRUE;
		}
		else bEnd = TRUE;
	} while(!bEnd);
	fclose(hKeyboard);

	if (nKey == T_ANN)
	{
		Disconnect();
		//nConnectError = LL_ERROR_UNKNOWN;
	}

	if (pThread != NULL)
	{
		while(!bThreadTerminated)
			ttestall(0, 1);

		kill(pThread, "");
	}
#else
	nConnectError = LL_Connect(hSession);
#endif

	if (nConnectError != LL_ERROR_OK)
	{
		DisplayError("LL_Connect", nConnectError);
		return FALSE;
	}

	hDisplay = fopen("DISPLAY", "w");
	startupcv20(0, 0);
	if (nKey != T_ANN)
		printf("\x1b" "\n   CONNECTED!");
	else printf("\x1b" "\n   CANCELLED!");
	fclose(hDisplay);

	return (nKey != T_ANN);
}

static void Disconnect(void)
{
	FILE* hDisplay;

	TraceDebug("***Disconnect !" );

	if (hSession != NULL)
	{
		hDisplay = fopen("DISPLAY", "w");
		startupcv20(0, 0);
		printf("\x1b" "\nDISCONNECTING...");
		fclose(hDisplay);

		LL_Disconnect(hSession);
		trace(0, 19, "After LL_Disconnect");
		if (LL_Configure(&hSession, NULL) == LL_ERROR_OK)
			hSession = NULL;
		trace(0, 18, "After LL_Configure");

		hDisplay = fopen("DISPLAY", "w");
		startupcv20(0, 0);
		printf("\x1b" "\n DISCONNECTED!");
		fclose(hDisplay);

		ttestall(0, 50);
	}
}

static void ModeNone(void)
{
	FILE* hKeyboard;
	FILE* hDisplay;
	unsigned char Buffer[2048];
	int nBytesRead;
	int nTotalBytes;
	int nError;
	int bEnd;
	char szString[128];
	int n;
	int nKey;

	bEnd = FALSE;
	nTotalBytes = 0;
	do
	{
		nBytesRead = LL_Receive(hSession, sizeof(Buffer), Buffer, 10);
		nError = LL_GetLastError(hSession);

		if (nBytesRead > 0)
		{
			nTotalBytes += nBytesRead;
			hDisplay = fopen("DISPLAY", "w");
			startupcv20(0, 0);

			sprintf(szString, "\x1b" " DATA RECEIVED!\n");
			printf(szString);

			n = sprintf(szString, "%i / %i", nBytesRead, nTotalBytes);
			n = (16 - n) / 2;
			while(n > 0)
			{
				printf(" ");
				n--;
			}
			printf(szString);

			fclose(hDisplay);
		}

		if (nError == LL_ERROR_DISCONNECTED)
		{
			TraceDebug("Remote disconnection !" );

			bEnd = TRUE;
		}
		else
		{
			hKeyboard = fopen("KEYBOARD", "r");
			if (ttestall(KEYBOARD, 10) == KEYBOARD)
			{
				nKey = getchar();
				if (nKey == T_ANN)
					bEnd = TRUE;
			}
			fclose(hKeyboard);
		}
	} while(!bEnd);
}

static void ModeSend(void)
{
	FILE* hKeyboard;
	FILE* hDisplay;
	unsigned char SendBuffer[256];
	unsigned char Buffer[2048];
	int nBytesRead;
	int nTotalBytes;
	int nError;
	int bEnd;
	char szString[128];
	int n;
	int bSend;
	int nKey;

	for(n = 0; n < (int)sizeof(SendBuffer); n++)
	{
		// !! VG		SendBuffer[n] = (unsigned char)n;
		SendBuffer[n] = (unsigned char)'A';
	}

	bEnd = FALSE;
	nTotalBytes = 0;
	bSend = TRUE;
	do
	{
		if (bSend)
		{
			// !! VG.
			for(n = 0; n < (int)sizeof(SendBuffer); n++)
			{
				SendBuffer[n] = SendBuffer[n] + 1;
			}

			TraceDebug( "***LL_Send !");
			n =  LL_Send(hSession, sizeof(SendBuffer), SendBuffer, 100);

			if( n >= 0 )
			{
				TraceDebug( "*** %d sent bytes", n );
			}
			else
			{
				nError = LL_GetLastError(hSession);
				TraceDebug( "***LL_Send LastError %d!", nError );
			}

			//bSend = FALSE;
		}

		TraceDebug( "***LL_Receive !");
		nBytesRead = LL_Receive(hSession, sizeof(Buffer), Buffer, 10);

		nError = LL_GetLastError(hSession);

		if (nBytesRead > 0)
		{
			nTotalBytes += nBytesRead;
			hDisplay = fopen("DISPLAY", "w");
			startupcv20(0, 0);

			sprintf(szString, "\x1b" " DATA RECEIVED!\n");
			printf(szString);

			n = sprintf(szString, "%i / %i", nBytesRead, nTotalBytes);
			n = (16 - n) / 2;
			while(n > 0)
			{
				printf(" ");
				n--;
			}
			printf(szString);

			fclose(hDisplay);
		}

		if (nError == LL_ERROR_DISCONNECTED)
		{
			bEnd = TRUE;
		}
		else
		{
			hKeyboard = fopen("KEYBOARD", "r");
			if (ttestall(KEYBOARD, 5) == KEYBOARD)
			{
				nKey = getchar();

				if (nKey == T_VAL)
					bSend = TRUE;
				else if (nKey == T_ANN)
					bEnd = TRUE;
			}
			fclose(hKeyboard);
		}
	} while(!bEnd);
}

static void ModeEcho(void)
{
	FILE* hKeyboard;
	FILE* hDisplay;
	unsigned char Buffer[2048];
	int nBytesRead;
	int nTotalBytes;
	int nError;
	int bEnd;
	char szString[128];
	int n;
	int bSend;
	int nKey;

	bEnd = FALSE;
	nTotalBytes = 0;
	do
	{
		nBytesRead = LL_Receive(hSession, sizeof(Buffer), Buffer, 10);
		nError = LL_GetLastError(hSession);

		if (nBytesRead > 0)
		{
			nTotalBytes += nBytesRead;
			hDisplay = fopen("DISPLAY", "w");
			startupcv20(0, 0);

			sprintf(szString, "\x1b" " DATA RECEIVED!\n");
			printf(szString);

			n = sprintf(szString, "%i / %i", nBytesRead, nTotalBytes);
			n = (16 - n) / 2;
			while(n > 0)
			{
				printf(" ");
				n--;
			}
			printf(szString);

			fclose(hDisplay);

			LL_Send(hSession, nBytesRead, Buffer, 100);
		}

		if (nError == LL_ERROR_DISCONNECTED)
		{
			bEnd = TRUE;
		}
		else
		{
			hKeyboard = fopen("KEYBOARD", "r");
			if (ttestall(KEYBOARD, 5) == KEYBOARD)
			{
				nKey = getchar();
				if (nKey == T_VAL)
					bSend = TRUE;
				else if (nKey == T_ANN)
					bEnd = TRUE;
			}
			fclose(hKeyboard);
		}
	} while(!bEnd);
}

static void ModeHttp(void)
{
	FILE* hKeyboard;
	FILE* hDisplay;
	unsigned char Buffer[2048];
	int nBytesRead;
	int nTotalBytes;
	int nError;
	int bEnd;
	char szString[128];
	int n;
	int nKey;

	LL_Send(hSession, 18, "GET / HTTP/1.0\r\n\r\n", 100);

	bEnd = FALSE;
	nTotalBytes = 0;
	do
	{
		nBytesRead = LL_Receive(hSession, sizeof(Buffer), Buffer, 10);
		nError = LL_GetLastError(hSession);

		if (nBytesRead > 0)
		{
			nTotalBytes += nBytesRead;
			hDisplay = fopen("DISPLAY", "w");
			startupcv20(0, 0);

			sprintf(szString, "\x1b" " DATA RECEIVED!\n");
			printf(szString);

			n = sprintf(szString, "%i / %i", nBytesRead, nTotalBytes);
			n = (16 - n) / 2;
			while(n > 0)
			{
				printf(" ");
				n--;
			}
			printf(szString);

			fclose(hDisplay);
		}

		if (nError == LL_ERROR_DISCONNECTED)
		{
			bEnd = TRUE;
		}
		else
		{
			hKeyboard = fopen("KEYBOARD", "r");
			if (ttestall(KEYBOARD, 5) == KEYBOARD)
			{
				nKey = getchar();
				if (nKey == T_ANN)
					bEnd = TRUE;
			}
			fclose(hKeyboard);
		}
	} while(!bEnd);
}

static void ModeGreekHost(void)
{
	FILE* hKeyboard;
	FILE* hDisplay;
	unsigned char Buffer[2048];
	int nBytesRead;
	int nTotalBytes;
	int nError;
	int bEnd;
	int bSend;
	char szString[128];
	int n;
	int nKey;
	unsigned char HostCommand[] = {
		0x00, 0x00, 0x00, 0x00, 0x00,
		'P', 'O', 'S', 'V', '1', '0',
		'0', '8', '0', '0',
		'2', '0', '0', '0', '0', '1', '0', '0', '0', '0', 'C', '0', '0', '0', '0', '0',
		'9', '9', '0', '0', '0', '0',
		'0', '0', '2',
		'0', '0', '0', '0', '0', '0', '5', '0',
		'0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '5', '6', '1', '1' };

	bEnd = FALSE;
	nTotalBytes = 0;
	bSend = TRUE;
	do
	{
		if (bSend)
		{
			LL_Send(hSession, sizeof(HostCommand), HostCommand, 100);
			bSend = FALSE;
		}

		nBytesRead = LL_Receive(hSession, sizeof(Buffer), Buffer, 10);
		nError = LL_GetLastError(hSession);

		if (nBytesRead > 0)
		{
			nTotalBytes += nBytesRead;
			hDisplay = fopen("DISPLAY", "w");
			startupcv20(0, 0);

			sprintf(szString, "\x1b" " DATA RECEIVED!\n");
			printf(szString);

			n = sprintf(szString, "%i / %i", nBytesRead, nTotalBytes);
			n = (16 - n) / 2;
			while(n > 0)
			{
				printf(" ");
				n--;
			}
			printf(szString);

			fclose(hDisplay);

			bEnd = TRUE;
		}

		if (nError == LL_ERROR_DISCONNECTED)
		{
			bEnd = TRUE;
		}
		else
		{
			hKeyboard = fopen("KEYBOARD", "r");
			if (ttestall(KEYBOARD, 5) == KEYBOARD)
			{
				nKey = getchar();
				if (nKey == T_VAL)
					bSend = TRUE;
				else if (nKey == T_ANN)
					bEnd = TRUE;
			}
			fclose(hKeyboard);
		}
	} while(!bEnd);
}

static void ModeMalaysianHost(void)
{
	FILE* hKeyboard;
	FILE* hDisplay;
	unsigned char Buffer[2048];
	int nBytesRead;
	int nTotalBytes;
	int nError;
	int bEnd;
	int bSend;
	char szString[128];
	int n;
	int nKey;
	unsigned char HostCommand[] = {
		0x60, 0x05, 0x58, 0x00, 0x00, 0x02, 0x00, 0x30, 0x20, 0x07, 0x80, 0x20, 0xC1, 0x02, 0x04, 0x00,
		0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x01, 0x00, 0x51, 0x00, 0x01, 0x05,
		0x58, 0x00, 0x38, 0x54, 0x36, 0x23, 0x22, 0x00, 0x00, 0x01, 0x33, 0xD0, 0x70, 0x22, 0x01, 0x15,
		0x06, 0x80, 0x44, 0x00, 0x00, 0x0F, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x31, 0x32,
		0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x00, 0x06, 0x30,
		0x30, 0x30, 0x30, 0x30, 0x31, 0x01, 0x13, 0x82, 0x02, 0x7C, 0x00, 0x95, 0x05, 0x00, 0x00, 0x00,
		0x80, 0x00, 0x9A, 0x03, 0x04, 0x09, 0x27, 0x9C, 0x01, 0x00, 0x5F, 0x2A, 0x02, 0x09, 0x78, 0x5F,
		0x34, 0x01, 0x01, 0x9F, 0x02, 0x06, 0x00, 0x00, 0x00, 0x00, 0x98, 0x00, 0x9F, 0x09, 0x02, 0x00,
		0x02, 0x9F, 0x10, 0x09, 0x08, 0x02, 0x01, 0x03, 0xA0, 0xA0, 0x06, 0xFB, 0xD7, 0x9F, 0x1A, 0x02,
		0x00, 0x56, 0x9F, 0x26, 0x08, 0xC5, 0x35, 0xE8, 0x07, 0x18, 0x24, 0x3A, 0x04, 0x9F, 0x27, 0x01,
		0x80, 0x9F, 0x33, 0x03, 0x60, 0xF8, 0xC8, 0x9F, 0x34, 0x03, 0x5E, 0x03, 0x00, 0x9F, 0x35, 0x01,
		0x22, 0x9F, 0x36, 0x02, 0x02, 0xB3, 0x9F, 0x37, 0x04, 0x33, 0x4D, 0x34, 0x23, 0x9F, 0x41, 0x04,
		0x00, 0x00, 0x00, 0x06, 0x9F, 0x53, 0x01, 0x52, 0x00, 0x06, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31 };

	bEnd = FALSE;
	nTotalBytes = 0;
	bSend = TRUE;
	do
	{
		if (bSend)
		{
			LL_Send(hSession, sizeof(HostCommand), HostCommand, 100);
			bSend = FALSE;
		}

		nBytesRead = LL_Receive(hSession, sizeof(Buffer), Buffer, 10);
		nError = LL_GetLastError(hSession);

		if (nBytesRead > 0)
		{
			nTotalBytes += nBytesRead;
			hDisplay = fopen("DISPLAY", "w");
			startupcv20(0, 0);

			sprintf(szString, "\x1b" " DATA RECEIVED!\n");
			printf(szString);

			n = sprintf(szString, "%i / %i", nBytesRead, nTotalBytes);
			n = (16 - n) / 2;
			while(n > 0)
			{
				printf(" ");
				n--;
			}
			printf(szString);

			fclose(hDisplay);

			bEnd = TRUE;
		}

		if (nError == LL_ERROR_DISCONNECTED)
		{
			bEnd = TRUE;
		}
		else
		{
			hKeyboard = fopen("KEYBOARD", "r");
			if (ttestall(KEYBOARD, 5) == KEYBOARD)
			{
				nKey = getchar();
				if (nKey == T_VAL)
					bSend = TRUE;
				else if (nKey == T_ANN)
					bEnd = TRUE;
			}
			fclose(hKeyboard);
		}
	} while(!bEnd);
}

static void ModeMastercardMit(void)
{
	FILE* hKeyboard;
	FILE* hDisplay;
	unsigned char SendBuffer[256];
	unsigned char Buffer[2048];
	int nBytesRead;
	int nTotalBytes;
	int nError;
	int bEnd;
	char szString[128];
	int n;
	int bSend;
	int nKey;

	for(n = 0; n < (int)sizeof(SendBuffer); n++)
		SendBuffer[n] = (unsigned char)n;

	bEnd = FALSE;
	nTotalBytes = 0;
	bSend = TRUE;
	do
	{
		if (bSend)
		{
			LL_Send(hSession, sizeof(SendBuffer), SendBuffer, 100);
			bSend = FALSE;
		}
		nBytesRead = LL_Receive(hSession, sizeof(Buffer), Buffer, 10);
		nError = LL_GetLastError(hSession);

		if (nBytesRead > 0)
		{
			nTotalBytes += nBytesRead;
			hDisplay = fopen("DISPLAY", "w");
			startupcv20(0, 0);

			sprintf(szString, "\x1b" " DATA RECEIVED!\n");
			printf(szString);

			n = sprintf(szString, "%i / %i", nBytesRead, nTotalBytes);
			n = (16 - n) / 2;
			while(n > 0)
			{
				printf(" ");
				n--;
			}
			printf(szString);

			fclose(hDisplay);
		}

		if (nError == LL_ERROR_DISCONNECTED)
		{
			bEnd = TRUE;
		}
		else
		{
			hKeyboard = fopen("KEYBOARD", "r");
			if (ttestall(KEYBOARD, 5) == KEYBOARD)
			{
				nKey = getchar();
				if (nKey == T_VAL)
					bSend = TRUE;
				else if (nKey == T_ANN)
					bEnd = TRUE;
			}
			fclose(hKeyboard);
		}
	} while(!bEnd);
}

static void ManageComm(void)
{
	TraceDebug( "***ManageComm %d !", CurrentConfig.m_nTestMode );
	switch(CurrentConfig.m_nTestMode)
	{
	case MODE_NONE:
		ModeNone();
		break;
	case MODE_SEND:
		ModeSend();
		break;
	case MODE_ECHO:
		ModeEcho();
		break;
	case MODE_DOWNLOAD_HTTP:
		ModeHttp();
		break;
	case MODE_GREEK_HOST:
		ModeGreekHost();
		break;
	case MODE_MALAYSIAN_HOST:
		ModeMalaysianHost();
		break;
	case MODE_MASTERCARD_MIT:
		ModeMastercardMit();
		break;
	}
}

void DoCommunication(void)
{
	if( CurrentConfig.m_bUseGsm == TRUE )
	{
		TraceDebug( "***Start GSM !" );
		ConnectNetworkGSM( __500_MSECONDS__, __60_SECONDS__ );
	}

	if( CurrentConfig.m_bUseGprs == TRUE )
	{
		TraceDebug( "***Start GPRS !" );
		ConnectNetworkGPRS( __500_MSECONDS__, __60_SECONDS__ );
	}

	if (Connect())
	{
		ttestall(0, 5);
		ManageComm();
		Disconnect();
		ttestall(0, 100);
	}
	else ttestall(0, 200);

	if( CurrentConfig.m_bUseGprs == TRUE )
	{
		TraceDebug( "***Stop GPRS !" );
		LL_GPRS_Stop();
	}

	if( CurrentConfig.m_bUseGsm == TRUE )
	{
		TraceDebug( "***Stop GSM !" );
		LL_GSM_Stop();
	}
}
