//-------------------------------------------------------------------
//
// Copyright (c) 2001 Sagem Monetel SA, rue claude Chappe,
// 07503 Guilherand-Granges, France, All Rights Reserved.
//
// Sagem Monetel SA has intellectual property rights relating
// to the technology embodied in this software.  In particular, 
// and without limitation, these intellectual property rights 
// may include one or more patents.
//
// This software is distributed under licenses restricting 
// its use, copying, distribution, and decompilation.  
// No part of this software may be reproduced in any form 
// by any means without prior written authorization of 
// Sagem Monetel.
//
// Description: Application menu management.
//      
// Author:      V.GOMES
// Version:     1.0
// Date:        2005/07/22 
//
//-------------------------------------------------------------------

// Includes.
//-------------------------------------------------------------------
#include "SDK30.H"

//#include "dgprs.h"

#include "UserInterfaceHelpers.h"
#include "Communication.h"


#include <SSL_.h>
#include <X509_.h>
#include "ssl_profile.h"



// Macros & preprocessor definitions.
//-------------------------------------------------------------------
#define __TRACE__(a)	trace(0,strlen(a),a)

// Delay
#define __30_SECONDS__			30000
#define __20_SECONDS__			20000
#define __10_SECONDS__			10000

//
#define __FALSE__		0
#define __TRUE__		1


// Input automaton state
#define __STATE_INPUT_EXIT			-2
#define __STATE_INPUT_BACK			-1
#define __STATE_INPUT_END			0

#define __STATE_INPUT_ADDRESS		1
#define __STATE_INPUT_PORT			2
#define __STATE_INPUT_LOGIN			3
#define __STATE_INPUT_PASSWORD		4
#define __STATE_INPUT_APN			5
#define __STATE_INPUT_PROFILE		6

//
#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))


// Types
//-------------------------------------------------------------------


// Global variables.
//-------------------------------------------------------------------
static const char* Menu_Main[] =
{
	"GPRS",
	"SSL"
};

static const char* Menu_SSL[] =
{
	"Profiles",
	"Connection"
};

static const char* Menu_SSL_Profile[] =
{
	"Add",
	"List"
};

static char g_szAPN[40];
static char g_szLogin[40];
static char g_szPassword[40];

static char g_szHostName[40];
static int  g_nPort;

static char g_szProfile[40];


// Static function definitions.
//-------------------------------------------------------------------


// Functions.
//-------------------------------------------------------------------
void GetManagerParameter( char *szAPN, char *szLogin, char *szPassword )
{
	S_INFOS_RESEAU_SUP sParameters;

	memset (&sParameters, 0, sizeof(S_INFOS_RESEAU_SUP));

	// Get parameters entered from the manager menu.
	PSQ_Donner_infos_reseau_sup ( &sParameters );

	memcpy( szAPN, sParameters.infos_sup.apn, sizeof(sParameters.infos_sup.apn) );
	memcpy( szLogin, sParameters.infos_sup.login, sizeof(sParameters.infos_sup.login) );
	memcpy( szPassword, sParameters.infos_sup.password, sizeof(sParameters.infos_sup.password) );

}

void PrintProfile( SSL_PROFILE_HANDLE hProfile )
{
	int iError;
	int iPort;
	int i;
	X509_HANDLE hX509;

	char szTmp[80];
	int szTmpSize = 80;
	char szBuffer[100];
	
	if( hProfile == NULL )
	{
		return;
	}

	if( SSL_ProfileGetName( hProfile, szTmp ) == 0 )
	{
		sprintf( szBuffer, "\x1B""E" "%s" "\x1B""F" "\n", szTmp );
		PrintText( szBuffer, 0 );
	}

	if( SSL_ProfileGetLastIpServer( hProfile, szTmp, &iPort ) == 0 )
	{
		if(strcmp(szTmp,"")!=0)
		{
			sprintf( szBuffer, "Last connection :\n%s:%d\n", szTmp, iPort );
			PrintText( szBuffer, 0 );
			
			if( SSL_ProfileGetLastError( hProfile, &iError ) == 0 )
			{
				switch( iError )
				{
					case SSL_PROFILE_OK:
						sprintf( szBuffer, "Connection OK\n" );
						break;
					case SSL_PROFILE_TCP_CONNECT_TIMEOUT:
						sprintf( szBuffer, "TCP connection timeout\n" );
						break;
					case SSL_PROFILE_TCP_CONNECT_FAILED:
						sprintf( szBuffer, "TCP connection failed\n"  );
						break;
					case SSL_PROFILE_TCP_ADDR_NOT_AVAILABLE:
						sprintf( szBuffer, "Address Not available\n" );
						break;
					case SSL_PROFILE_SSL_HANDSHAKE_FAILURE:
						sprintf( szBuffer, "Not SSL server\n" );
						break;
					case SSL_PROFILE_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
						sprintf( szBuffer, "Unknown server certificate\n" );
						break;
					case SSL_PROFILE_ERROR_IN_CERT_NOT_BEFORE_FIELD:
						sprintf( szBuffer, "Server certificate not yet valid\n" );
						break;
					case SSL_PROFILE_ERROR_IN_CERT_NOT_AFTER_FIELD:
						sprintf( szBuffer, "Server certificate has expired\n" );
						break;
					case SSL_PROFILE_E_SSLV3_ALERT_HANDSHAKE_FAILURE:
						sprintf( szBuffer, "Server refused connection\n" );
						break;
					default:
						sprintf( szBuffer, "Error: %d\n", iError );
				}
				PrintText( szBuffer, 0 );
				PrintText( "\n", 0 );
			}
		}
	}
	
	if( SSL_ProfileGetCertificateFile( hProfile, szTmp ) == 0 )
	{
		sprintf( szBuffer, "Client Certificate :\n");
		PrintText( szBuffer, 0 );

		if(( hX509 = X509_Load( szTmp )) != NULL )
		{
			if(X509_GetInfo(hX509,X509_NOTBEFORE,0,szTmp,szTmpSize)>0)
			{
				sprintf( szBuffer, "Not Before :\n%s\n",szTmp);
				PrintText( szBuffer, 0 );
			}
			if(X509_GetInfo(hX509,X509_NOTAFTER,0,szTmp,szTmpSize)>0)
			{
				sprintf( szBuffer, "Not After :\n%s\n",szTmp);
				PrintText( szBuffer, 0 );
			}
			X509_Unload( hX509 );
		}
		PrintText( "\n", 0 );
	}
	
	i = 0;
	while(SSL_ProfileGetCAFile( hProfile, i, szTmp ) == 0)
	{
		sprintf( szBuffer, "Certificate Authority :\n");
		PrintText( szBuffer, 0 );

		if(( hX509 = X509_Load( szTmp )) != NULL )
		{
			if(X509_GetInfo(hX509,X509_NOTBEFORE,0,szTmp,szTmpSize)>0)
			{
				sprintf( szBuffer, "Not Before :\n%s\n",szTmp);
				PrintText( szBuffer, 0 );
			}
			if(X509_GetInfo(hX509,X509_NOTAFTER,0,szTmp,szTmpSize)>0)
			{
				sprintf( szBuffer, "Not After :\n%s\n",szTmp);
				PrintText( szBuffer, 0 );
			}
			if(X509_GetInfo(hX509,X509_ISSUER,NID_commonName,szTmp,szTmpSize)>0)
			{
				sprintf( szBuffer, "Issuer %s :\n%s\n",SN_commonName,szTmp);
				PrintText( szBuffer, 0 );
			}
			X509_Unload( hX509 );
		}
		PrintText("\n",0);
		i++;
	}
	
	PrintText("\n",1);
}

void AddProfile(void)
{
	static int i=0;
	char szName[80];
	char szBuffer[100];

	SSL_PROFILE_HANDLE hProfile;

	sprintf( szName, "PROFILE_%02d", i++ );

	//
	sprintf( szBuffer, "Creation Profile: %s\n", szName );
	PrintText( szBuffer, 1 );

	hProfile = SSL_NewProfile( szName, NULL );

	if( hProfile != NULL )
	{
		SSL_ProfileSetProtocol( hProfile, SSLv3 );
		SSL_ProfileSetCipher( hProfile,
							  SSL_RSA | SSL_DES| SSL_3DES | SSL_RC4 | SSL_RC2 | SSL_MAC_MASK | SSL_SSLV3,
							  SSL_HIGH | SSL_NOT_EXP );

		//
		SSL_ProfileSetKeyFile( hProfile, "/SYSTEM/CLIENT_KEY.PEM", FALSE );
		SSL_ProfileSetCertificateFile( hProfile, "/SYSTEM/CLIENT.CRT" );
		SSL_ProfileAddCertificateCA( hProfile, "/SYSTEM/CA.CRT" );

		// Save the profile.
		SSL_SaveProfile( hProfile );
		SSL_UnloadProfile( hProfile );

		PrintText( "SUCCESS !!\n", 1);
	}
	else
	{
		PrintText( "ERROR !!\n", 1);
	}
}




void ListProfiles(void)
{
	SSL_PROFILE_HANDLE hProfile;
	int i = 0;	
	while(( hProfile = SSL_GetProfile( i++ )) != NULL )
	{
		PrintProfile( hProfile );

		SSL_UnloadProfile( hProfile );
	}
}

char **GetListProfiles( int *pnNbItems )
{
	int nNbProfiles = 0;
	char **pItems = NULL;
	char *szName = NULL;

	SSL_PROFILE_HANDLE hProfile;
	int i = 0;

	nNbProfiles = SSL_GetProfileCount();
	if( nNbProfiles != 0 )
	{
		pItems = (char **) umalloc( sizeof(const char*) * nNbProfiles );

		while(( hProfile = SSL_GetProfile( i )) != NULL )
		{
			szName = (char *) umalloc( PROFILE_NAME_SIZE );

			SSL_ProfileGetName( hProfile, szName );
			pItems[i] = szName;

			SSL_UnloadProfile( hProfile );
			i++;
		}
	}
	*pnNbItems = nNbProfiles;
	return pItems;
}

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
									  0, __MODE_NOCASE, 0 ))
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
									  0, __MODE_NOCASE, 0 ))
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
									  0, __MODE_NOCASE, 0 ))
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



static int ConfigureSSL( char *szHostName, int nHostNameLen, int *pnPort,
						 char *szProfile, int nProfileLen )
{
	int nState;
	char szDefault[20];
	int nValue;

	//
	char **ProfileNames = NULL;
	int nNbProfiles = 0;

	// Get the profile list.
	ProfileNames = GetListProfiles( &nNbProfiles );

	//
	nState = __STATE_INPUT_ADDRESS;
	do
	{
		switch(nState)
		{
		case __STATE_INPUT_ADDRESS:
			// Input the host name
			switch(HelperManageInput( "Hostname :", 2, 20, 
									  szHostName, 10, 30, nHostNameLen, 
									  0, __MODE_NOCASE, 0 ))
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
			switch( HelperManageInput( "Port :", 2, 20, szDefault, 20, 30, 40, 1, __MODE_NOCASE, 0 ))
			{
			case __ENTER_KEY:
				nValue = 0;

				if( __atoi( szDefault, &nValue ) == 1 )
				{
					*pnPort = nValue;
					nState = __STATE_INPUT_PROFILE;
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

		case __STATE_INPUT_PROFILE:
			switch( HelperDisplaySelection( "Profile :", 2, 20,
											10, 30,
											nNbProfiles, (const char**) ProfileNames,
											__ALL_BANNERS, __30_SECONDS__, &nValue ))
			{
				case __ENTER_KEY:
					strcpy( szProfile, ProfileNames[nValue] );
					nState = __STATE_INPUT_END;
					break;

				case __BACK_KEY: // Back
					nState = __STATE_INPUT_PORT;
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

	// Delete profile list.
	if( ProfileNames != NULL )
	{
		int i;
		for( i = 0; i < nNbProfiles; i++ )
		{
			ufree( ProfileNames[i] );
		}

		ufree( ProfileNames );
	}

	return nState;
}




void ManageMenuSSL_Profile(void)
{
	int bContinue;
	
	bContinue = 1;
	do
	{
		switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(Menu_SSL_Profile), Menu_SSL_Profile, __ALL_BANNERS ))
		{
		case 0:
			AddProfile();
			break;

		case 1:
			ListProfiles();
			break;

		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );
}


void ManageMenuSSL(void)
{
	static int bFirst = __TRUE__;

	int bContinue;

	if( bFirst == __TRUE__ )
	{
		strcpy( g_szHostName, "0.0.0.0" ); 
		g_nPort = 0;
		strcpy( g_szProfile, "PROFILE_00" );

		bFirst = __FALSE__;
	}
	
	bContinue = 1;
	do
	{
		switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(Menu_SSL), Menu_SSL, __ALL_BANNERS ))
		{
		case 0:
			ManageMenuSSL_Profile();
			break;

		case 1: // SSL.
			if( ConfigureSSL( g_szHostName, 40, &g_nPort,
							  g_szProfile, 40 ) == __STATE_INPUT_END )
			{
				if( PerformConnectionSSL( g_szHostName, g_nPort, g_szProfile ) == 0 )
				{
					// Connection success.
				}
			}
			break;

		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );
}



void ManageMenuMain(void)
{
	static int bFirst = __TRUE__;

	int bContinue;

	memset (g_szAPN, 0, sizeof(g_szAPN));
	memset (g_szLogin, 0, sizeof(g_szLogin));
	memset (g_szPassword, 0, sizeof(g_szPassword));
	memset (g_szHostName, 0, sizeof(g_szHostName));
	memset (g_szProfile, 0, sizeof(g_szProfile));

	// Init parameters.
	if( bFirst == __TRUE__ )
	{
		GetManagerParameter( g_szAPN, g_szLogin, g_szPassword );
		bFirst = __FALSE__;
	}


	bContinue = 1;
	do
	{
		switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(Menu_Main), Menu_Main, __ALL_BANNERS ))
		{
		case 0:
			if( ConfigureGPRS( g_szAPN, 40, g_szLogin, 40, g_szPassword, 40 ) == __STATE_INPUT_END )
			{
				PerformConnectionGPRS( g_szAPN, g_szLogin, g_szPassword );
			}
			break;

		case 1: // SSL.
			ManageMenuSSL();
			break;

		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );
}
