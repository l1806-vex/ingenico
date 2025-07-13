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

#include "oem_dgprs.h"

#include "UserInterfaceHelpers.h"
#include "Communication.h"

// Macros & preprocessor definitions.
//-------------------------------------------------------------------

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
#define __STATE_INPUT_DIRECTORY		5
#define __STATE_INPUT_APN			6

//
#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))


// Types
//-------------------------------------------------------------------

// Global variables.
//-------------------------------------------------------------------
static const char* MainMenu[] =
{
	"GPRS",
	"FTP"
};

static char g_szAPN[40];
static char g_szLogin[40];
static char g_szPassword[40];

static char g_szHostName[40];
static int  g_nPort;

static char g_szLoginFTP[40];
static char g_szPasswordFTP[40];
static char g_szDirectory[40];


// Static function definitions.
//-------------------------------------------------------------------
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


static int ConfigureFTP( char *szHostName, int nHostNameLen, int *pnPort,
						 char *szLogin, int nLoginLen,
						 char *szPassword, int nPasswordLen,
						 char *szDirName, int nDirNameLen)
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
					nState = __STATE_INPUT_LOGIN;
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

		case __STATE_INPUT_LOGIN:
			// Input the login
			switch(HelperManageInput( "Login :", 2, 20, 
									  szLogin, 10, 30, nLoginLen, 
									  0, __MODE_LOWERCASE, 0 ))
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
									  0, __MODE_NOCASE, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_DIRECTORY;
				break;

			case __BACK_KEY:
				nState = __STATE_INPUT_LOGIN;
				break;

			default:
				nState = __STATE_INPUT_EXIT;
				break;
			}
			break;

		case __STATE_INPUT_DIRECTORY:
			// Input the directory
			switch(HelperManageInput( "Directory :", 2, 20, 
									  szDirName, 20, 30, nDirNameLen, 
									  0, __MODE_NOCASE, 0 ))
			{
			case __ENTER_KEY:
				nState = __STATE_INPUT_END;
				break;

			case __BACK_KEY:
				nState = __STATE_INPUT_PASSWORD;
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


void ManageMenuMain(void)
{
	static int bFirst = __TRUE__;

	FILE *hDisplay = NULL;
	int bContinue;

	memset (g_szAPN, 0, sizeof(g_szAPN));
	memset (g_szLogin, 0, sizeof(g_szLogin));
	memset (g_szPassword, 0, sizeof(g_szPassword));
	memset (g_szHostName, 0, sizeof(g_szHostName));
	memset (g_szLoginFTP, 0, sizeof(g_szLoginFTP));
	memset (g_szPasswordFTP, 0, sizeof(g_szPasswordFTP));
	memset (g_szDirectory, 0, sizeof(g_szDirectory));

	hDisplay = fopen( "DISPLAY", "w" );

	// Init parameters.
	

	if( bFirst == __TRUE__ )
	{
		GetManagerParameter( g_szAPN, g_szLogin, g_szPassword );

		strcpy( g_szHostName, "0.0.0.0" ); 
		g_nPort = 21;

		strcpy( g_szLoginFTP,		"ftp"				);
		strcpy( g_szPasswordFTP,	"sample_ftp"		);
		strcpy( g_szDirectory,		"."					);

		bFirst = __FALSE__;
	}

	
	bContinue = 1;
	do
	{
		switch( HelperDisplayMenu( NULL, 0, NUMBER_OF_ITEMS(MainMenu), MainMenu, __ALL_BANNERS ))
		{
		case 0:
			if( ConfigureGPRS( g_szAPN, 40, g_szLogin, 40, g_szPassword, 40 ) == __STATE_INPUT_END )
			{
				PerformConnectionGPRS( g_szAPN, g_szLogin, g_szPassword );
			}
			break;

		case 1: // FTP.
			if( ConfigureFTP( g_szHostName, 40, &g_nPort,
								g_szLoginFTP, 40, g_szPasswordFTP, 40,
								g_szDirectory, 40 ) == __STATE_INPUT_END )
			{
				if( PerformConnectionFTP( g_szHostName, g_nPort, 
											g_szLoginFTP, g_szPasswordFTP,
											g_szDirectory, 
											"TEMP",  4096 * 1024 ) == 0 )
				{
					// Download success. Activation success.
				}
			}
			break;


		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );

	fclose( hDisplay );
}
