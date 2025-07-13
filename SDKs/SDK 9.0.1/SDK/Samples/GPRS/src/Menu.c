/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////
#include "SDK30.H"

#include "UserInterfaceHelpers.h"
#include "Communication.h"


//// Macros & preprocessor definitions //////////////////////////
#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))


// Input automaton state
#define __STATE_INPUT_EXIT			-2
#define __STATE_INPUT_BACK			-1
#define __STATE_INPUT_END			0

#define __STATE_INPUT_ADDRESS		1
#define __STATE_INPUT_PORT			2
#define __STATE_INPUT_LOGIN			3
#define __STATE_INPUT_PASSWORD		4

#define __STATE_INPUT_GSM_NUMBER	5
#define __STATE_INPUT_GSM_MODE		6
#define __STATE_INPUT_GSM_RLP		7


//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

//// Global variables ///////////////////////////////////////////
static const char* MainMenu[] =
{
	"PPP", 
	"TCP/IP", 
	"GSM"
};


static const char* MenuTestPPP[] =
{
	"Connection",
	"Disconnection"
};


static const char* MenuTestTCP[] =
{
	"WEB Iteration",
	"Echo Test",
	"Receive 100K",
};

static char g_szAPN[40];
static char g_szLogin[40];
static char g_szPassword[40];

static char g_szHostName[40];
static int  g_nPort;

// GSM parameters.
static char g_szPhoneNumber[20];
int g_nMode;
int g_bRLP;


//// Functions //////////////////////////////////////////////////
static int __atoi( const char *szInput, int *pnValue )
{
	const char *pPtr;

	*pnValue = 0;
	pPtr = szInput;
	while((*pPtr >= '0') && (*pPtr <= '9'))
	{
		*pnValue = *pnValue * 10 + (*pPtr - '0');
		pPtr++;
	}

	if( *pPtr != '\0' )
	{
		return 0;
	}

	return 1;
}

void GetManagerParameter( char *szAPN, char *szLogin, char *szPassword )
{
	S_INFOS_RESEAU_SUP sParameters;

	// Get parameters entered from the manager menu.
	PSQ_Donner_infos_reseau_sup ( &sParameters );

	strcpy( szAPN,      (const char*)sParameters.infos_sup.apn );
	strcpy( szLogin,    (const char*)sParameters.infos_sup.login );
	strcpy( szPassword, (const char*)sParameters.infos_sup.password );
}

static int ConfigurePPP( char *szLogin, int nLoginLen,
						 char *szPassword, int nPasswordLen )
{
	int nState;

	nState = __STATE_INPUT_LOGIN;
	do
	{
		switch(nState)
		{
		case __STATE_INPUT_LOGIN:
			// Input the login
			switch(HelperManageInput( "Login :", 2, 20, 
									  szLogin, 10, 30, nLoginLen, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_PASSWORD;
				break;

			case __BACK_KEY: // Back
				nState = __STATE_INPUT_BACK;
				break;

			default: // Cancel
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;

		case __STATE_INPUT_PASSWORD:
			// Input the password
			switch(HelperManageInput( "Password :", 2, 20, 
									  szPassword, 20, 30, nPasswordLen, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_END;
				break;

			case __BACK_KEY:
				nState = __STATE_INPUT_LOGIN;
				break;

			default:
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;
		}
	} while(( nState != __STATE_INPUT_END )   &&
		    ( nState != __STATE_INPUT_BACK )  && 
			( nState != __STATE_INPUT_EXIT ));

	return nState;
}

static int ConfigureTCP( char *szHostName, int nHostNameLen, int *pnPort )
{
	int nState;
	char szDefault[20];
	int nValue;

	nState = __STATE_INPUT_ADDRESS;
	do
	{
		switch(nState)
		{
		case __STATE_INPUT_ADDRESS:
			// Input the host name
			switch(HelperManageInput( "Hostname :", 2, 20, 
									  szHostName, 10, 30, nHostNameLen, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_PORT;
				break;

			case __BACK_KEY: // Back
				nState = __STATE_INPUT_BACK;
				break;

			default: // Cancel
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;

		case __STATE_INPUT_PORT:
			// Input the port
			sprintf( szDefault, "%i", *pnPort );
			switch( HelperManageInput( "Port :", 2, 20, szDefault, 20, 30, 40, 1, 0 ))
			{
			case __ENTER_KEY:
				nValue = 0;

				if( __atoi( szDefault, &nValue ) == 1 )
				{
					*pnPort = nValue;
					nState = __STATE_INPUT_END;
				}
				break;

			case __BACK_KEY:
				nState = __STATE_INPUT_ADDRESS;
				break;

			default:
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;
		}
	} while(( nState != __STATE_INPUT_END )   &&
		    ( nState != __STATE_INPUT_BACK )  && 
			( nState != __STATE_INPUT_EXIT ));

	return nState;
}



static int ConfigureGSM( char *szPhoneNumber, int nPhoneNumberLen,
						 int *pnMode, int *pbRLP )
{
	char szTemp[20];
	int nState;

	nState = __STATE_INPUT_GSM_NUMBER;
	do
	{
		switch(nState)
		{
		case __STATE_INPUT_GSM_NUMBER:
			// Input the phone number
			switch(HelperManageInput( "Phone Number :", 2, 20, 
									  szPhoneNumber, 10, 30, nPhoneNumberLen, 
									  1, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_GSM_MODE;
				break;

			case __BACK_KEY: // Back
				nState = __STATE_INPUT_BACK;
				break;

			default: // Cancel
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;

		case __STATE_INPUT_GSM_MODE:
			// Input the baudrate
			sprintf( szTemp, "%i", *pnMode );
			switch(HelperManageInput( "Mode :", 2, 20, 
									  szTemp, 20, 30, 4, 
									  1, 0 ))
			{
			case __ENTER_KEY:
				*pnMode = 0;
				if( __atoi( szTemp, pnMode ) == 1 )
				{
					nState = __STATE_INPUT_GSM_RLP;
				}
				break;

			case __BACK_KEY:
				nState = __STATE_INPUT_GSM_NUMBER;
				break;

			default:
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;

		case __STATE_INPUT_GSM_RLP:
			if( *pbRLP == 0 )
			{
				szTemp[0] = '0';
			}
			else
			{
				szTemp[0] = '1';
			}

			// Input the GSM mode (RLP or transparent).
			switch(HelperManageInput( "RLP (0/1) ?:", 2, 20, 
									  szTemp, 20, 30, 2, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				*pbRLP = 0;

				if(( szTemp[0] == '0' ) ||
				   ( szTemp[0] == '1' ))
				{
					*pbRLP = szTemp[0] - '0';
					nState = __STATE_INPUT_END;
				}
				break;

			case __BACK_KEY:
				nState = __STATE_INPUT_GSM_MODE;
				break;

			default:
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;
		}
	} while(( nState != __STATE_INPUT_END )   &&
		    ( nState != __STATE_INPUT_BACK )  && 
			( nState != __STATE_INPUT_EXIT ));

	return nState;
}



void ManageMenuTestPPP(void)
{
	int bContinue;


	bContinue = 1;
	do
	{
		switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(MenuTestPPP), MenuTestPPP,
								   __ALL_BANNERS ))
		{
		case 0:
			// PPP connection.
			PerformConnectionPPP( g_szLogin, g_szPassword );
			break;

		case 1:
			// PPP disconnection
			PerformDisconnectionPPP();
			break;

		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );
}



void ManageMenuTestTCP(void)
{
	int bContinue;


	bContinue = 1;
	do
	{
		switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(MenuTestTCP), MenuTestTCP,
								   __ALL_BANNERS ))
		{
		case 0:
			PerformConnectionTCP( g_szHostName, g_nPort, __TCP_TEST_LOOP_HTTP );
			break;

		case 1:
			PerformConnectionTCP( g_szHostName, g_nPort, __TCP_TEST_ECHO );
			break;

		case 2:
			PerformConnectionTCP( g_szHostName, g_nPort, __TCP_TEST_RECEIVE_100K );
			break;


		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );
}


void ManageMenuMain(void)
{
	int bContinue;

	GetManagerParameter( g_szAPN, g_szLogin, g_szPassword );

	if( WaitNetworkScreen( g_szAPN, 1 ) == 1 )
	{
		bContinue = 1;
		do
		{
			switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(MainMenu), MainMenu,
									   __ALL_BANNERS ))
			{
			case 0:
				// PPP Tests.
				if( ConfigurePPP( g_szLogin, 40, g_szPassword, 40 ) == __STATE_INPUT_END )
				{
					ManageMenuTestPPP();
				}
				break;

			case 1:
				if( ConfigureTCP( g_szHostName, 60, &g_nPort ) == __STATE_INPUT_END )
				{
					// TCP/IP Tests.
					ManageMenuTestTCP();
				}
				break;


			case 2:
				// GSM Tests.
				if( ConfigureGSM( g_szPhoneNumber, 20, &g_nMode, &g_bRLP ) 
									== __STATE_INPUT_END )
				{
					PerformConnectionGSM( g_szPhoneNumber, g_nMode, g_bRLP );
				}
				break;

			default:
				bContinue = 0;
				break;
			}

		} while( bContinue == 1 );
	}
}
