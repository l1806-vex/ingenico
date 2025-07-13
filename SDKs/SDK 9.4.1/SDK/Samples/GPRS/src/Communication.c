/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////
#include "SDK30.H"

#include "gprs_lib.h"
#include "client_ip.h"
#include "oem_dgprs.h"

#include "UserInterfaceHelpers.h"
#include "Communication.h"

//// Macros & preprocessor definitions //////////////////////////

#define __FALSE__		0
#define __TRUE__		1

//
#define __INFINITE__			0x00FFFFFF
#define __100_MSECONDS__		10
#define __500_MSECONDS__		50
#define __3_SECONDS__			300
#define __10_SECONDS__			1000
#define __20_SECONDS__			2000
#define __60_SECONDS__			6000

#define __COM_STATE_CONNECTING			0
#define __COM_STATE_CONNECTED			1
#define __COM_STATE_ERROR				2
#define __COM_STATE_ERROR_PARAMETERS	3		

#define __COM_STATE_DISCONNECTED		4
#define __COM_STATE_DISCONNECTING		5

#define __COM_STATE_RECEIVED			6
#define __COM_STATE_CONNECTING_IP		7
#define __COM_STATE_ERROR_IP			8

#define __COM_STATE_ERROR_SEND			9
#define __COM_STATE_ERROR_ENABLE_GPRS	10
#define __COM_STATE_ERROR_ENABLE_GSM	11

#define __COM_STATE_CONNECTING_PPP		12


#define __FRAME_ECHO			"RUN_ECHO ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define __FRAME_RECEIVE_100K	"RUN_FLOW"


unsigned char __APN__[40];


#define __START_COUNTER(a)	(a) = get_tick_counter();
#define __END_COUNTER(a,b)	(b) = get_tick_counter() - (a);


#define __TRACE__(a)	trace(0,strlen(a),a)

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////
unsigned char g_pucData[1024];




////////////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////
static int GetKey( int nTimeout )
{
	int nKey = -1;

	FILE* hKeyboard;
	hKeyboard = fopen("KEYBOARD", "r");
	if( ttestall( KEYBOARD, nTimeout ) == KEYBOARD ) 
	{
		nKey = getchar();
	}

	fclose(hKeyboard);

	return nKey;
}

////////////////////////////////////////////////////////////////////

void PrintNetworkInfos()
{
	T_DGPRS_GET_INFORMATION info;
	FILE *gprs = NULL;
	char szTemp[100];

	if(( gprs = stdperif(( char *)"DGPRS", NULL )) != NULL )
	{
		fioctl( DGPRS_FIOCTL_GET_INFORMATION, &info, gprs );

		sprintf( szTemp, "ICC=%s\n", info.simIccId );
		PrintText( szTemp, 0 );

		sprintf( szTemp, "IMEI=%s\n", info.module_imei_number );
		PrintText( szTemp, 0 );

		sprintf( szTemp, "APN=%s\n", info.gprs_apn );
		PrintText( szTemp, 0 );

		sprintf( szTemp, "Version=%s\n", info.module_software_version );
		PrintText( szTemp, 0 );

		sprintf( szTemp, "Network=%s (%d)\n", info.network_name, info.network_typ );
		PrintText( szTemp, 0 );

		sprintf( szTemp, "PIN mgt=%s, %s \n",
			( info.pin_control_activ  ? "Enable" : "Disable"),
			( info.pin_mode_free  ? "Free" : "Suspicious"));

		PrintText( szTemp, 0 );

		sprintf( szTemp, "Funct=%08x\n", info.func_enable );
		PrintText( szTemp, 0 );

		sprintf( szTemp, "Radio=%d\n", info.radio_level );
		PrintText( szTemp, 0 );

		sprintf( szTemp, "Battery=%d\n", info.battery_level );
		PrintText( szTemp, 1 );
	}
}



static int DisplayConnectionScreen( int nStatus, int nError, int nTimeout, int bKey )
{
	int nKey = -1;
	char szTemp[32];

	CreateGraphics( _MEDIUM_ );

	switch( nStatus )
	{
	case __COM_STATE_CONNECTING:
		DisplayText( "Connecting...", 2, 20, -1, 0 );
		sprintf( szTemp, "Wait : %d", nError );
		DisplayText( szTemp, 2, 30, -1, 0 );
		break;

	case __COM_STATE_CONNECTING_IP:
		DisplayText( "Connecting...", 2, 20, -1, 0 );
		sprintf( szTemp, "Addr : %s", (const char *) nError );
		DisplayText( szTemp, 2, 30, -1, 0 );
		break;

	case __COM_STATE_ERROR_IP:
		DisplayText( "Error :", 2, 20, -1, 0 );
		sprintf( szTemp, "%d", nError );
		DisplayText( szTemp, 2, 30, -1, 0 );
		break;

	case __COM_STATE_CONNECTED:
		DisplayText( "Connected !", 2, 20, -1, 0 );
		break;

	case __COM_STATE_DISCONNECTING:
		DisplayText( "Disconnecting...", 2, 20, -1, 0 );
		break;

	case __COM_STATE_DISCONNECTED:
		DisplayText( "Disconnected !", 2, 20, -1, 0 );
		break;

	case __COM_STATE_RECEIVED:
		DisplayText( "Connected !", 2, 20, -1, 0 );
		sprintf( szTemp, "Received : %d", nError );
		DisplayText( szTemp, 2, 30, -1, 0 );
		break;

	case __COM_STATE_ERROR_SEND:
		DisplayText( "Send Error :", 2, 20, -1, 0 );
		sprintf( szTemp, "%d", nError );
		DisplayText( szTemp, 2, 30, -1, 0 );
		break;

	case __COM_STATE_ERROR:
		DisplayText( "Error :", 2, 20, -1, 0 );

		switch( nError )
		{
		case GPRS_ERR_CONNECT_TIMEOUT:
			DisplayText( "- Timeout", 5, 30, -1, 0 );
			break;

		case GPRS_ERR_PPP:
			DisplayText( "- PPP", 5, 30, -1, 0 );
			break;

		case GPRS_ERR_ALREADY_CONNECTED:
			DisplayText( "- Already", 5, 30, -1, 0 );
			break;

		case GPRS_ERR_NO_GPRS:
			DisplayText( "- GPRS disabled", 5, 30, -1, 0 );
			break;

		case GPRS_ERR_NO_SIM:
			DisplayText( "- No SIM", 5, 30, -1, 0 );
			break;

		case GPRS_ERR_SIM_LOCK:
			DisplayText( "- SIM locked", 5, 30, -1, 0 );
			break;

		case GPRS_ERR_NO_PIN:
			DisplayText( "- No PIN", 5, 30, -1, 0 );
			break;

		case GPRS_ERR_BAD_PIN:
			DisplayText( "- Bad PIN", 5, 30, -1, 0 );
			break;

		case GPRS_ERR_FATAL:
			DisplayText( "- Fatal", 5, 30, -1, 0 );
			break;

		case GPRS_ERR_UNKNOWN:
		default:
			DisplayText( "- Unknown", 5, 30, -1, 0 );
			break;
		}
		break;

	case __COM_STATE_ERROR_ENABLE_GPRS:
		DisplayText( "Error :", 2, 20, -1, 0 );
		DisplayText( "- GPRS enable", 5, 30, -1, 0 );
		break;

	case __COM_STATE_ERROR_ENABLE_GSM:
		DisplayText( "Error :", 2, 20, -1, 0 );
		DisplayText( "- GSM enable", 5, 30, -1, 0 );
		break;

	case __COM_STATE_CONNECTING_PPP:
		DisplayText( "Connecting PPP...", 2, 20, -1, 0 );
		break;
	}

	if( bKey == __TRUE__ )
	{
		DisplayText( ">", 0, 50, -1, 0 );
	}

	//
	PaintGraphics();

	if( nTimeout > 0 )
	{
		if( bKey == 1 )
		{
			nKey = GetKey( nTimeout );
		}
		else
		{
			// Just wait.
			ttestall( 0, nTimeout );			
		}
	}

	return nKey;
}

//// Functions //////////////////////////////////////////////////



int WaitNetworkAvailable( int bGPRS, unsigned int nWaitTimeout, unsigned int nWaitMaxTimeout, int *pError )
{
	unsigned int nWaitTotal = 0;
	int bContinue = __TRUE__;

	int bReady	= __FALSE__;
	int bPPP	= __FALSE__;

	do 
	{ 
		bContinue = gprs_IsNetworkAvailable( bGPRS, &bReady, pError, &bPPP );
		if( bContinue == __TRUE__  )
		{
			ttestall( 0, nWaitTimeout );
			nWaitTotal += nWaitTimeout;
		}

	} while(( bContinue == __TRUE__ ) && ( nWaitTotal < nWaitMaxTimeout ));

	return bReady;
}


int WaitNetworkPPP( unsigned int nWaitTimeout, unsigned int nWaitMaxTimeout )
{
	unsigned int nWaitTotal = 0;
	int bContinue = __TRUE__;

	int bReady	= __FALSE__;
	int bPPP	= __FALSE__;

	int nError  = 0;

	do 
	{ 
		bContinue = gprs_IsNetworkAvailable( __TRUE__, &bReady, &nError, &bPPP );

		if(( bContinue == __TRUE__  ) && ( bPPP == __FALSE__ ))
		{
			ttestall( 0, nWaitTimeout );
			nWaitTotal += nWaitTimeout;
		}

	} while(( bContinue == __TRUE__ ) &&
		    ( bPPP == __FALSE__ ) && 
			( nWaitTotal < nWaitMaxTimeout ));

	return bPPP;
}



int WaitNetworkScreen( char *szAPN, int bGPRS )
{
	int nError;

	CreateGraphics( _MEDIUM_ );
	DisplayText( "Wait GPRS network...", 2, 20, -1, 0 );
	PaintGraphics();

	strcpy( (char*)__APN__, szAPN );
	if( bGPRS )
	{
		nError = gprs_enable( (char*)__APN__ );
	}
	else
	{
		nError = gsm_enable( (char*)__APN__ );
	}

	
	if( nError == GPRS_OK )
	{
		if( WaitNetworkAvailable( bGPRS, __500_MSECONDS__, __60_SECONDS__, &nError ) == __TRUE__ )
		{
			PrintNetworkInfos();
			return __TRUE__;
		}
	}

	DisplayConnectionScreen( __COM_STATE_ERROR_ENABLE_GPRS, nError, 500, 1 );

	if(( nError == GPRS_ERR_NO_PIN ) || ( nError == GPRS_ERR_BAD_PIN ))
	{
		gprs_setpincode();
	}

	return __FALSE__;
}



/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
int PerformConnectionPPP( char *szLogin, char *szPassword )
{
	int nError;

	FILE *hKeyboard = NULL;

	nError = gprs_enable((char*) __APN__ );
	if(( nError == GPRS_OK ) && 
	   ( WaitNetworkAvailable( __TRUE__, __500_MSECONDS__, __20_SECONDS__, &nError ) == __TRUE__ ))
	{
		DisplayConnectionScreen( __COM_STATE_CONNECTING_PPP, 0, 0, 0 );

		hKeyboard = fopen("KEYBOARD", "r");
		nError = gprs_connect( T_ANN, (char*)__APN__, szLogin, szPassword, 30 );
		fclose(hKeyboard);

		if(( nError == GPRS_OK ) &&
		   ( WaitNetworkPPP( __500_MSECONDS__, __20_SECONDS__ ) == __TRUE__ ))
		{
			DisplayConnectionScreen( __COM_STATE_CONNECTED, 0, 500, 1 );
		}
		else
		{
			if( nError == GPRS_ERR_PPP )
			{
				gprs_stop();
			}

			DisplayConnectionScreen( __COM_STATE_ERROR, nError, 500, 1 );
		}
	}
	else
	{
		DisplayConnectionScreen( __COM_STATE_ERROR_ENABLE_GPRS, nError, 500, 1 );
	}

	return nError;
}


int PerformDisconnectionPPP()
{
	int nError;

	DisplayConnectionScreen( __COM_STATE_DISCONNECTING, 0, 0, 1 );
	
	nError = gprs_stop();

	DisplayConnectionScreen( __COM_STATE_DISCONNECTED, 0, 500, 1 );


	return nError;
}

static int PerformTestTCP_LoopHTTP( char *szHostname, int nPort )
{
	int nHandle = 0;
	int nResult = 0;
	int nReceived = 0;
	int nTotalReceived = 0;

	int bContinue = __TRUE__;

	unsigned char pucData[64];

	unsigned long int ulDelay			= 0;
	unsigned long int ulConnectDelay	= 0;
	unsigned long int ulTotalDelay		= 0;

	int nIterations	= 0;

	char szTemp[128];


	// Connect to IP Test server.
	while( bContinue == __TRUE__ )
	{
		DisplayConnectionScreen( __COM_STATE_CONNECTING_IP, (int) szHostname, 0, 0 );

		nReceived = 0;
		nTotalReceived = 0;

		//
		__START_COUNTER(ulDelay);
		nHandle = tcp_connect_to_server( szHostname, nPort, __20_SECONDS__ );
		__END_COUNTER(ulDelay,ulConnectDelay);

		if( nHandle >= 0 )
		{
			DisplayConnectionScreen( __COM_STATE_CONNECTED, 0, 0, 0 );

			while(( nResult = tcp_send_to_server( nHandle, (unsigned char*)"GET / HTTP/1.0\r\n\r\n", 18, __INFINITE__ ))
						== ERROR_TIMEOUT )
			{
				ttestall( 0, __100_MSECONDS__ );
			}

			if( nResult == 18 )
			{
				//
				// HTTP request sent.
				// Infinite wait (the HTTP disconnection will be performed
				// by the remote server.
				//
				DisplayConnectionScreen( __COM_STATE_RECEIVED, nTotalReceived, 0, 0 );

				while(( nResult = tcp_recv_from_server( nHandle, pucData, 64, __20_SECONDS__ )) > 0 )
				{
					nReceived = nResult;
					nTotalReceived += nReceived;
					if( DisplayConnectionScreen( __COM_STATE_RECEIVED, nTotalReceived, __500_MSECONDS__, 1 )
							== T_ANN )
					{
						// Cancel key pressed.
						// Request disconnection.
						bContinue = __FALSE__;
						nResult = 0;
						break;
					}
				}
			}
			else
			{
				DisplayConnectionScreen( __COM_STATE_ERROR_SEND, nResult, __3_SECONDS__, 1 );
				bContinue = __FALSE__;
			}

			// Disconnect and Release handle.
			tcp_disconnect_from_server( nHandle );

			__END_COUNTER(ulDelay,ulTotalDelay);
			sprintf( szTemp, "(%d) http %d= %d (%ld/%ld)\n", nResult, nIterations, nTotalReceived, ulConnectDelay, ulTotalDelay );
			PrintText( szTemp, 1 );

			DisplayConnectionScreen( __COM_STATE_DISCONNECTED, 0, __3_SECONDS__, 0 );
		}
		else
		{
			// Error during connection.
			DisplayConnectionScreen( __COM_STATE_ERROR_IP, nResult, __3_SECONDS__, 1 );
			bContinue = __FALSE__;
		}

		nIterations++;
	}

	return 0;
}



static int PerformTestTCP_LoopEcho( char *szHostname, int nPort )
{
	int nHandle = 0;
	int nResult = 0;
	int nReceived = 0;
	int nTotalReceived = 0;

	int nIterations = 0;


	char szTemp[100];

	int bContinue = __TRUE__;

	unsigned char pucData[64];


	int nFrameSize = strlen(( const char* ) __FRAME_ECHO );

	// Connect to IP Test server.
	DisplayConnectionScreen( __COM_STATE_CONNECTING_IP, (int) szHostname, 0, 0 );


	nHandle = tcp_connect_to_server( szHostname, nPort, __20_SECONDS__ );

	if( nHandle >= 0 )
	{
		DisplayConnectionScreen( __COM_STATE_CONNECTED, 0, 0, 0 );

		while(( bContinue == __TRUE__ ) && ( nIterations < 1000 ))
		{
			// Send Frame to be echoed.
			while(( nResult = tcp_send_to_server( nHandle, (unsigned char*)__FRAME_ECHO, nFrameSize,0 ))
						== ERROR_TIMEOUT )
			{
				ttestall( 0, __100_MSECONDS__ );
			}

			if( nResult == nFrameSize )
			{
				nReceived = 0;

				DisplayConnectionScreen( __COM_STATE_RECEIVED, nTotalReceived, 0, 0 );

				// Wait for the echo of the sent frame.
				while(( nResult = tcp_recv_from_server( nHandle, pucData, nFrameSize, 0 ))
							== ERROR_TIMEOUT )
				{
					ttestall( 0, __100_MSECONDS__ );
				}

				if( nResult > 0 )
				{
					nReceived = nResult;
					nTotalReceived += nReceived;

					if( DisplayConnectionScreen( __COM_STATE_RECEIVED, nTotalReceived, __100_MSECONDS__, 1 ) 
							== T_ANN )
					{
						// Cancel key pressed.
						// Request disconnection.
						nResult = 0;
						bContinue = __FALSE__;
					}
					else
					{
						// Continue. Next Echo.
						nIterations++;
					}
				}
				else
				{
					if( nResult < 0 )
					{
						DisplayConnectionScreen( __COM_STATE_ERROR_IP, nResult, __3_SECONDS__, 1 );
					}

					bContinue = __FALSE__;
				}
			}
			else
			{
				DisplayConnectionScreen( __COM_STATE_ERROR_SEND, nResult, __3_SECONDS__, 1 );
				bContinue = __FALSE__;
			}
		}

		// Disconnect and release handle.
		tcp_disconnect_from_server( nHandle ); // To release the internal socket.
		DisplayConnectionScreen( __COM_STATE_DISCONNECTED, 0, __3_SECONDS__, 1 );
	}
	else
	{
		// Error during connection.
		DisplayConnectionScreen( __COM_STATE_ERROR_IP, nResult, __3_SECONDS__, 1 );
	}

	sprintf( (char*)szTemp, "(%d) Echo %d= %d\n", nResult, nIterations, nTotalReceived );
	PrintText( szTemp, 1 );

	return 0;
}



static int PerformTestTCP_Receive100K( char *szHostname, int nPort )
{
	int nHandle = 0;
	int nResult = 0;

	int nReceived = 0;
	int nTotalReceived = 0;

	unsigned long int ulDelay		  = 0;
	unsigned long int ulConnectDelay = 0;
	unsigned long int ulTotalDelay	  = 0;

	int nFrameSize = strlen(( const char* ) __FRAME_RECEIVE_100K );

	char szTemp[100];

	// Connect to IP Test server.
	DisplayConnectionScreen( __COM_STATE_CONNECTING_IP, (int) szHostname, 0, 0 );

	__START_COUNTER(ulDelay);
	nHandle = tcp_connect_to_server( szHostname, nPort, __20_SECONDS__ );
	__END_COUNTER(ulDelay,ulConnectDelay);

	if( nHandle >= 0 )
	{
		DisplayConnectionScreen( __COM_STATE_CONNECTED, 0, 0, 0 );

		// Send request frame.
		while(( nResult = tcp_send_to_server( nHandle, (unsigned char*)__FRAME_RECEIVE_100K, nFrameSize,0 ))
						== ERROR_TIMEOUT )
		{
			ttestall( 0, __100_MSECONDS__ );
		}

		if( nResult == nFrameSize )
		{
			DisplayConnectionScreen( __COM_STATE_RECEIVED, nTotalReceived, 0, 0 );

			while(( nResult = tcp_recv_from_server( nHandle, g_pucData, 1024, __INFINITE__ )) > 0 )
			{
				nReceived = nResult;
				nTotalReceived += nReceived;
				if( DisplayConnectionScreen( __COM_STATE_RECEIVED, nTotalReceived, __500_MSECONDS__, 1 )
						== T_ANN )
				{
					nResult = 0;
					break;
				}
			}
		}
		else
		{
			DisplayConnectionScreen( __COM_STATE_ERROR_SEND, nResult, __3_SECONDS__, 1 );
		}

		// Disconnect and release handle.
		tcp_disconnect_from_server( nHandle );

		//
		__END_COUNTER(ulDelay,ulTotalDelay);
		sprintf( szTemp, "(%d) r100K=%d (%ld/%ld)\n", nResult, nTotalReceived, ulConnectDelay, ulTotalDelay );
		PrintText( szTemp, 1 );

		DisplayConnectionScreen( __COM_STATE_DISCONNECTED, 0, 0, 0 );
		return __TRUE__;
	}
	else
	{
		// Error during connection.
		DisplayConnectionScreen( __COM_STATE_ERROR_IP, nResult, __3_SECONDS__, 1 );
	}

	return __FALSE__;
}


int PerformConnectionTCP( char *szHostname, int nPort, int nTest )
{
//	sprintf( szHostname, "217.12.3.11" ); // www.yahoo.fr
//	nPort = 80;

//	sprintf( szHostname, "213.222.84.6" ); // Serveur de test
//	nPort = 2121;

	switch( nTest )
	{
		case __TCP_TEST_RECEIVE_100K:
			PerformTestTCP_Receive100K( szHostname, nPort );
			break;

		case __TCP_TEST_ECHO:
			PerformTestTCP_LoopEcho( szHostname, nPort );
			break;

		case __TCP_TEST_LOOP_HTTP:
			PerformTestTCP_LoopHTTP( szHostname, nPort );
			break;

		default:
			break;
	}

	return 0;
}


int PerformConnectionGSM( char *szPhoneNumber,
						  int nMode, int bRLP )
{
	int nError;

	FILE *hKeyboard = NULL;

	int nReceived = 0;
	int nTotalReceived = 0;

	unsigned short nFirstTimeout = 0;
	unsigned short nInterTimeout = 0;

	unsigned long int ulDelay		 = 0;
	unsigned long int ulConnectDelay = 0;
	unsigned long int ulTotalDelay	 = 0;

	char l_szTemp[200];

	nError = gsm_enable( (char*)__APN__ );
	if(( nError == GPRS_OK ) && 
	   ( WaitNetworkAvailable( __FALSE__, __500_MSECONDS__, __20_SECONDS__, &nError ) == __TRUE__ ))
	{
		DisplayConnectionScreen( __COM_STATE_CONNECTING, 80, 0, 0 );

		//
		hKeyboard = fopen("KEYBOARD", "r");

		__START_COUNTER(ulDelay);
		nError = gsm_connect( szPhoneNumber, T_ANN, nMode, bRLP, 80 );;
		__END_COUNTER(ulDelay,ulConnectDelay);

		__START_COUNTER(ulDelay);

		fclose(hKeyboard);

		if( nError == GPRS_OK )
		{
			
			DisplayConnectionScreen( __COM_STATE_CONNECTED, 0, 0, 0 );

			// Run FLOW tests
			gsm_write( (unsigned char*)__FRAME_RECEIVE_100K, strlen( __FRAME_RECEIVE_100K ));

			//
			do
			{
				nReceived = 1024;
				nFirstTimeout = __10_SECONDS__;
				nInterTimeout = __100_MSECONDS__;

				while( gsm_read( g_pucData, &nReceived, nFirstTimeout, nInterTimeout ) == GPRS_OK )
				{
					nTotalReceived += nReceived;
					DisplayConnectionScreen( __COM_STATE_RECEIVED, nTotalReceived, 0, 0 );

					// Adjust timeout.
					nFirstTimeout = __100_MSECONDS__ ;
					nInterTimeout = __100_MSECONDS__;

					nReceived = 1024;
				}

				nError = gprs_errno();

			} while( nError == GPRS_ERRNO_GSM_RECEIVE_TIMEOUT );
				
			__END_COUNTER(ulDelay,ulTotalDelay);

			sprintf( l_szTemp, "(%d) Receive %d bytes, %lu (%lu)!\n", nError, nTotalReceived, ulTotalDelay, ulConnectDelay );
			PrintText( l_szTemp, 1 );

			// Disconnection.
			DisplayConnectionScreen( __COM_STATE_DISCONNECTING, 0, 0, 0 );

			gsm_disconnect();
		}
	}
	else
	{
		DisplayConnectionScreen( __COM_STATE_ERROR_ENABLE_GSM, nError, 500, 1 );
	}

	return nError;
}



