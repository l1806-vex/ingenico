/***
* Copyright (c) 2004 Sagem Monetel SA, rue claude Chappe,
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* Sagem Monetel SA has intellectual property rights relating
* to the technology embodied in this software.  In particular, 
* and without limitation, these intellectual property rights 
* may include one or more patents.
*
* This software is distributed under licenses restricting 
* its use, copying, distribution, and decompilation.  
* No part of this software may be reproduced in any form 
* by any means without prior written authorization of 
* Sagem Monetel.
*
* @Title:        
* @Description:  
*
*	Launch an application download with the help of REMOTE download..
*
*
*	Here is an example which shows you how to use the CallHost function to
*	download an application by RTC and GPRS/IP way.
*
*
* @Reference:    
* @Comment:      
*
* @author        
* @version       
* @Comment:      
* @date:         
*/
#include <SDK30.H>
#include <Malloc.h>

#include "UserInterfaceHelpers.h"

#define __FALSE__		0
#define __TRUE__		1

static const char g_pcExtendedStructTag[3]     = { 0x01, 0x02, 0x03 };

//
int GetAddressIP( const char *szAddress, unsigned int *o_pnAddress, unsigned int *o_pnPort )
{
	unsigned int nIP;
	unsigned int i,j;
	unsigned char c;

	char szTemp[4];

	//
	nIP = 0;

	j = 0;
	i = 0;

	while ((( c = szAddress[i++] ) != 0 ) && 
	       ( c != ':' ))
	{
		if( c == '.' )
		{
			nIP = ( nIP << 8) + atoi( szTemp );
			j = 0;
		}
		else
		{
			szTemp[j++] = c;
			szTemp[j] = '\0';
		}
	}

	if( c == ':' )
	{
		*o_pnAddress = ( nIP << 8 ) + atoi( szTemp );
		*o_pnPort	 = atoi( &szAddress[i] );

		return __TRUE__;
	}

	return __FALSE__;
}

////////////////////////////////////////////////////////////////////////////////////////

int PerformRemoteIP( int nRemoteType,
					 const char *szCallNumber,			// PSTN Phone Number. 
				     const char *szAddress,				// TMS IP address : xxx.xxx.xxx.xxx:yyy
				     const char *szContractNumber,
				     const char *szSoftwareName,
					 const char *szLogin,
					 const char *szPassword,
					 const char *szAPN )
{
	int nRet = 0;

	S_PARAM_TLCHGT Params;

	// Decomposed IP¨address.
	unsigned int nIP;
	unsigned int nPort;

	//
	if( GetAddressIP( szAddress, &nIP, &nPort ) == __TRUE__ )
	{
		memset( &Params, 0, sizeof( S_PARAM_TLCHGT ));
		Params.type_modem	= VIP;

		Params.ip	= nIP;		// TMS IP address
		Params.port = nPort;	// TMS IP port

		// Contract number. Pad with blank.
		memset( Params.t_nocontrat, ' ', sizeof( Params.t_nocontrat ));
		memcpy( Params.t_nocontrat, szContractNumber, strlen( szContractNumber ));

		// Tag for extended structure.
		memcpy( Params.t_nologiciel, g_pcExtendedStructTag, 3 );

		Params.reseau = nRemoteType;

		// Set the other parameters according to the remote type.
		switch( Params.reseau )
		{
		case TMSGPRS:
			// Download through GPRS.
			strcpy( Params.t_noappel, szAddress );

			strcpy( (char*)Params.apn,   szAPN );			// GPRS APN.
			strcpy( (char*)Params.login, szLogin );		// GPRS Login.
			strcpy( (char*)Params.password, szPassword );	// GPRS Password.
			break;

		case TMSIP:
			strcpy( Params.t_noappel, szAddress );
			break;

		case TMSIPRTC:
			sprintf( Params.t_noappel, "T%s", szCallNumber );	// ISP PhoneNumber.
			strcpy( (char*)Params.login,  szLogin );		// ISP Login.
			strcpy( (char*)Params.password, szPassword );	// ISP Password.
			break;
		}

		nRet = remote_downloading( &Params );
	}

	return nRet;
}
