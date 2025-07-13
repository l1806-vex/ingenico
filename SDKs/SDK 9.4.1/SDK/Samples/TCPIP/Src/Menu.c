//-------------------------------------------------------------------
//
// Copyright (c) 2005 Sagem Monetel SA, rue claude Chappe,
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
#define __STATE_INPUT_RECIPIENT		3
#define __STATE_INPUT_CC            4
#define __STATE_INPUT_BCC           5

//
#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))


// Types
//-------------------------------------------------------------------

// Global variables.
//-------------------------------------------------------------------
static const char* MainMenu[] =
{
	"Info",
	"HTTP Server",
	"HTTP Client"
};


static char g_szHostName[40];
static int  g_nPort;


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


static int ConfigureHTTP( char *szHostName, int nHostNameLen, int *pnPort )
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

		default:
			nState = __STATE_INPUT_EXIT;
			break;
		}
	} while(( nState != __STATE_INPUT_END )   &&
		    ( nState != __STATE_INPUT_BACK )  && 
			( nState != __STATE_INPUT_EXIT ));

	return nState;
}

void ManageMenuMain(void)
{
	static int bFirst = __TRUE__;

	FILE *hDisplay = NULL;

	int bContinue;

	// Init parameters.
	if( bFirst == __TRUE__ )
	{
		strcpy( g_szHostName, "www.free.fr" ); 
		g_nPort = 80;
		bFirst = __FALSE__;
	}

	hDisplay = fopen( "DISPLAY", "w" );

	bContinue = 1;
	do
	{
		switch( HelperDisplayMenu( "SAMPLE TCP/IP", 0, NUMBER_OF_ITEMS(MainMenu), MainMenu, __NO_BANNER ))
		{
		case 0:
			// Display Ethernet Infos.
			PrintNetworkInfos();
			break;

		case 1: // HTTP Server.
			LaunchServerHTTP();
			break;

		case 2: // HTTP Client.
			if( ConfigureHTTP( g_szHostName, 40, &g_nPort ) == 0 )
			{
				PerformConnectionHTTP( g_szHostName, g_nPort, "/" );
			}
			break;

		default:
			bContinue = 0;
			break;
		}

	} while( bContinue == 1 );

	fclose( hDisplay );
}
