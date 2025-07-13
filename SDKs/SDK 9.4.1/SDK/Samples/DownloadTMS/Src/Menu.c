/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////
#include "SDK30.H"

#include "UserInterfaceHelpers.h"
#include "Communication.h"
#include "DoCallHost.h"
#include "DoRemote.h"

#include "DefaultParams.h"


//// Macros & preprocessor definitions //////////////////////////
#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))


// Input automaton state
#define __STATE_INPUT_EXIT			-2
#define __STATE_INPUT_BACK			-1
#define __STATE_INPUT_END			0

#define __STATE_INPUT_SOFTWARE_NUMBER	1
#define __STATE_INPUT_CONTRACT_NUMBER	2

#define __STATE_INPUT_ADDRESS		3
#define __STATE_INPUT_PORT			4
#define __STATE_INPUT_LOGIN			5
#define __STATE_INPUT_PASSWORD		6
#define __STATE_INPUT_APN			7

#define __STATE_INPUT_PSTN_NUMBER	8

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

//// Global variables ///////////////////////////////////////////
static const char* MainMenu[] =
{
	"REMOTE IP",
	"CALLHOST"
};

static const char* MenuCallHost[] =
{
	"PSTN",		// TMS PSTN
	"IP"		// TMS IP
};

static const char* MenuCallHostIP[] =
{
	"Parameters",		// Download parameters.
	"Connect GPRS",		// Connect the GPRS network.
	"Run..."			// Call Host
};

static const char* MenuCallHostPSTN[] =
{
	"Parameters",
	"Run..."			// Call Host
};

static const char* MenuRemoteIP[] =
{
	"Parameters",			// Download parameters
	"GPRS Parameters",		// GPRS parameters
	"ISP Parameters",		// ISP parameters
	"Run -- IP   -->",		// Run in IP directly
	"Run -- GPRS -->",		// Run through GPRS network.
	"Run -- ISP  -->"		// Run through an PSTN ISP.
};



// GPRS parameters.
static char g_szGPRS_APN[40];
static char g_szGPRS_Login[40];
static char g_szGPRS_Password[40];

// ISP Parameters
static char g_szISP_PhoneNumber[40];
static char g_szISP_Login[40];
static char g_szISP_Password[40];

// Download parameters.
static char g_szPSTN_Software[40];
static char g_szPSTN_ContractNumber[40];

static char g_szIP_Software[40];
static char g_szIP_ContractNumber[40];

// PSTN parameters.
static char g_szPSTN_PhoneNumber[40];

// IP parameters.
static char g_szIP_Address[40];
static int  g_nIP_Port;

//
FILE *g_hDisplay = NULL;

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


//
void OpenDisplay()
{
	if( g_hDisplay == NULL )
	{
		g_hDisplay = fopen( "DISPLAY", "w" );
	}
}

void CloseDisplay()
{
	if( g_hDisplay != NULL )
	{
		fclose( g_hDisplay );
		g_hDisplay = NULL;
	}
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


static int ConfigureGPRS( char *szAPN, int nAPNLen, char *szLogin, int nLoginLen,
						  char *szPassword, int nPasswordLen )
{
	int nState;

	nState = __STATE_INPUT_APN;
	do
	{
		switch(nState)
		{
		case __STATE_INPUT_APN:
			// Input the login
			switch(HelperManageInput( "APN :", 2, 20, 
									  szAPN, 10, 30, nAPNLen, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_LOGIN;
				break;

			case __BACK_KEY: // Back
				nState = __STATE_INPUT_BACK;
				break;

			default: // Cancel
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;

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
				nState = __STATE_INPUT_APN;
				break;

			default: // Cancel
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;

		case __STATE_INPUT_PASSWORD:
			// Input the password
			switch(HelperManageInput( "Password :", 2, 20, 
									  szPassword, 10, 30, nPasswordLen, 
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

static int ConfigureISP( char *szPhoneNumber, int nPhoneNumberLen, 
						  char *szLogin, int nLoginLen,
						  char *szPassword, int nPasswordLen )
{
	int nState;

	nState = __STATE_INPUT_PSTN_NUMBER;
	do
	{
		switch(nState)
		{
		case __STATE_INPUT_PSTN_NUMBER:
			// Input the login
			switch(HelperManageInput( "ISP Phone Number :", 2, 20, 
									  szPhoneNumber, 10, 30, nPhoneNumberLen, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_LOGIN;
				break;

			case __BACK_KEY: // Back
				nState = __STATE_INPUT_BACK;
				break;

			default: // Cancel
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;

		case __STATE_INPUT_LOGIN:
			// Input the login
			switch(HelperManageInput( "ISP Login :", 2, 20, 
									  szLogin, 10, 30, nLoginLen, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_PASSWORD;
				break;

			case __BACK_KEY: // Back
				nState = __STATE_INPUT_PSTN_NUMBER;
				break;

			default: // Cancel
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;

		case __STATE_INPUT_PASSWORD:
			// Input the password
			switch(HelperManageInput( "ISP Password :", 2, 20, 
									  szPassword, 10, 30, nPasswordLen, 
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


static int ConfigurePSTN( char *szSoftwareNumber, int nSoftwareNumberLen,
						  char *szContractNumber, int nContractNumberLen,
						  char *szPhoneNumber, int nPhoneNumberLen )
{
	int nState;

	nState = __STATE_INPUT_SOFTWARE_NUMBER;
	do
	{
		switch(nState)
		{
		case __STATE_INPUT_SOFTWARE_NUMBER:
			// Input the host name
			switch(HelperManageInput( "Software Number :", 2, 20, 
									  szSoftwareNumber, 10, 30, nSoftwareNumberLen, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_CONTRACT_NUMBER;
				break;

			case __BACK_KEY: // Back
				nState = __STATE_INPUT_BACK;
				break;

			default: // Cancel
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;

		case __STATE_INPUT_CONTRACT_NUMBER:
			// Input the host name
			switch(HelperManageInput( "Contract Number :", 2, 20, 
									  szContractNumber, 10, 30, nContractNumberLen, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_PSTN_NUMBER;
				break;

			case __BACK_KEY: // Back
				nState = __STATE_INPUT_SOFTWARE_NUMBER;
				break;

			default: // Cancel
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;


		case __STATE_INPUT_PSTN_NUMBER:
			// Input the host name
			switch(HelperManageInput( "TMS Phone Number :", 2, 20, 
									  szPhoneNumber, 10, 30, nPhoneNumberLen, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_END;
				break;

			case __BACK_KEY: // Back
				nState = __STATE_INPUT_CONTRACT_NUMBER;
				break;

			default: // Cancel
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

static int ConfigureIP( char *szSoftwareNumber, int nSoftwareNumberLen,
						char *szContractNumber, int nContractNumberLen,
						char *szHostName, int nHostNameLen, int *pnPort )
{
	int nState;
	char szDefault[20];
	int nValue;

	nState = __STATE_INPUT_SOFTWARE_NUMBER;
	do
	{
		switch(nState)
		{
		case __STATE_INPUT_SOFTWARE_NUMBER:
			// Input the host name
			switch(HelperManageInput( "Software Number :", 2, 20, 
									  szSoftwareNumber, 10, 30, nSoftwareNumberLen, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_CONTRACT_NUMBER;
				break;

			case __BACK_KEY: // Back
				nState = __STATE_INPUT_BACK;
				break;

			default: // Cancel
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;

		case __STATE_INPUT_CONTRACT_NUMBER:
			// Input the host name
			switch(HelperManageInput( "Contract Number :", 2, 20, 
									  szContractNumber, 10, 30, nContractNumberLen, 
									  0, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_ADDRESS;
				break;

			case __BACK_KEY: // Back
				nState = __STATE_INPUT_SOFTWARE_NUMBER;
				break;

			default: // Cancel
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;


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
				nState = __STATE_INPUT_CONTRACT_NUMBER;
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



void ManageMenuCallHostPSTN(void)
{
	int bContinue = 1;

	do
	{
		switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(MenuCallHostPSTN),MenuCallHostPSTN, __ALL_BANNERS ))
		{
		case 0:
			// Parameters.
			ConfigurePSTN( g_szPSTN_Software, 40,
						   g_szPSTN_ContractNumber, 40, 
						   g_szPSTN_PhoneNumber, 40 );
			break;

		case 1:
			// Execute Call Host.
			CloseDisplay();
			PerformCallHost( REMOTE_CALL, g_szPSTN_PhoneNumber, "SAMPLE", 
							 g_szPSTN_ContractNumber, g_szPSTN_Software );
			break;

		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );

}


void ManageMenuCallHostIP(void)
{
	int bContinue = 1;

	char szTemp[40];

	do
	{
		switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(MenuCallHostIP), MenuCallHostIP, __ALL_BANNERS ))
		{
		case 0:
			// Parameters.
			ConfigureIP( g_szIP_Software, 40, 
						 g_szIP_ContractNumber, 40, 
						 g_szIP_Address, 60, &g_nIP_Port );
			break;

		case 1:
			// Connect GPRS.
			if( ConfigureGPRS( g_szGPRS_APN, 40, g_szGPRS_Login, 40, g_szGPRS_Password, 40 )
					== __STATE_INPUT_END )
			{
				PerformConnectionGPRS( g_szGPRS_APN, g_szGPRS_Login, g_szGPRS_Password );
			}
			break;

		case 2:
			// Execute Call Host.
			sprintf( szTemp, "%s:%d", g_szIP_Address, g_nIP_Port );
			CloseDisplay();
			PerformCallHost( REMOTE_IP, szTemp, "SAMPLE", g_szIP_ContractNumber, g_szIP_Software );
			break;

		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );

}



void ManageMenuRemoteIP(void)
{
	int bContinue = 1;

	char szTemp[40];

	do
	{
		switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(MenuRemoteIP), MenuRemoteIP, __ALL_BANNERS ))
		{
		case 0:
			// Parameters.
			ConfigureIP( g_szIP_Software, 40, 
						 g_szIP_ContractNumber, 40, 
						 g_szIP_Address, 60, &g_nIP_Port );
			break;

		case 1:
			// GPRS Parameters.
			ConfigureGPRS( g_szGPRS_APN, 40, g_szGPRS_Login, 40, g_szGPRS_Password, 40 );
			break;

		case 2:
			// ISP Parameters.
			ConfigureISP( g_szISP_PhoneNumber, 40, g_szISP_Login, 40, g_szISP_Password, 40 );
			break;

		case 3:
			// Execute Remote directly through IP.
			sprintf( szTemp, "%s:%d", g_szIP_Address, g_nIP_Port );

			CloseDisplay();
			PerformRemoteIP( TMSIP, "", szTemp, g_szIP_ContractNumber, g_szIP_Software,
							 "", "", "" );
			break;

		case 4:
			// Execute Remote through GPRS.
			sprintf( szTemp, "%s:%d", g_szIP_Address, g_nIP_Port );

			CloseDisplay();
			PerformRemoteIP( TMSGPRS, "", szTemp, g_szIP_ContractNumber, g_szIP_Software,
							 g_szGPRS_Login, g_szGPRS_Password, g_szGPRS_APN );
			break;

		case 5:
			// Execute Remote through an external PSTN ISP.
			sprintf( szTemp, "%s:%d", g_szIP_Address, g_nIP_Port );

			CloseDisplay();
			PerformRemoteIP( TMSIPRTC, g_szISP_PhoneNumber, szTemp, g_szIP_ContractNumber, g_szIP_Software,
							 g_szISP_Login, g_szISP_Password, "" );
			break;

		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );
}

void ManageMenuCallHost(void)
{
	int bContinue = 1;

	do
	{
		switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(MenuCallHost), MenuCallHost, __ALL_BANNERS ))
		{
		case 0:
			// CallHost PSTN.
			ManageMenuCallHostPSTN();
			break;

		case 1:
			// CallHost IP.
			ManageMenuCallHostIP();
			break;

		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );
}

void ManageMenuMain(void)
{
	static int bFirst = 1;

	int bContinue = 1;

	// The fist time, initialize all the parameters with default values?
	if( bFirst == 1 )
	{
		// Get the GPRS parameters from the manager.
		GetManagerParameter( g_szGPRS_APN, g_szGPRS_Login, g_szGPRS_Password );

		//
		strcpy( g_szPSTN_ContractNumber, __DEFAULT_PSTN_CONTRACT_NUMBER );
		strcpy( g_szPSTN_Software,		 __DEFAULT_PSTN_SOFTWARE );

		//
		strcpy( g_szIP_ContractNumber,	__DEFAULT_IP_CONTRACT_NUMBER );
		strcpy( g_szIP_Software,		__DEFAULT_IP_SOFTWARE );

		//
		strcpy( g_szISP_PhoneNumber,	__DEFAULT_ISP_PHONE_NUMBER );
		strcpy( g_szISP_Login,			__DEFAULT_ISP_LOGIN );
		strcpy( g_szISP_Password,		__DEFAULT_ISP_PASSWORD );

		// PSTN parameters.
		strcpy( g_szPSTN_PhoneNumber, __DEFAULT_PSTN_PHONE_NUMBER );

		// IP parameters.
		strcpy( g_szIP_Address, __DEFAULT_IP_ADDRESS );
		g_nIP_Port = __DEFAULT_IP_PORT;
	}

	do
	{
		OpenDisplay();

		switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(MainMenu), MainMenu, __ALL_BANNERS ))
		{
		case 0:
			// Remote IP.
			ManageMenuRemoteIP();
			break;

		case 1:
			// CallHost.
			ManageMenuCallHost();
			break;

		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );

	CloseDisplay();
}
