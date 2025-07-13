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
// Description: Communication utilities module.
//      
// Author:      V.GOMES
// Version:     1.0
// Date:        2005/07/22 
//
//-------------------------------------------------------------------


// Includes
//-------------------------------------------------------------------
#include <SDK30.H>

#include <gprs_lib.h>
#include <oem_dgprs.h>

#include "UserInterfaceHelpers.h"
#include "Communication.h"

#include "loader_util.h"
#include "Ftp_DownloadDir.h"

// Macros & preprocessor definitions.
//-------------------------------------------------------------------

// Delays.
#define __500_MSECONDS__		50
#define __3_SECONDS__			300
#define __20_SECONDS__			2000
#define __60_SECONDS__			6000

//
#define __COM_STATE_ERROR				1
#define __COM_STATE_ERROR_ENABLE_GPRS	2



// Types.
//-------------------------------------------------------------------


// Global variables
//-------------------------------------------------------------------

// Static function definitions.
//-------------------------------------------------------------------
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


static int DisplayConnectionScreen( int nStatus, int nError, int nTimeout, int bKey )
{
	int nKey = -1;
	char szTemp[32];

	CreateGraphics( _MEDIUM_ );

	switch( nStatus )
	{
	case __COM_STATE_ERROR:
		DisplayText( "Error :", 2, 20, -1, __FALSE__, __FALSE__ );

		switch( nError )
		{
		case GPRS_ERR_CONNECT_TIMEOUT:
			DisplayText( "- Timeout", 5, 30, -1, __FALSE__, __FALSE__ );
			break;

		case GPRS_ERR_PPP:
			DisplayText( "- PPP", 5, 30, -1, __FALSE__, __FALSE__ );
			break;

		case GPRS_ERR_ALREADY_CONNECTED:
			DisplayText( "- Already", 5, 30, -1, __FALSE__, __FALSE__ );
			break;

		case GPRS_ERR_NO_GPRS:
			DisplayText( "- GPRS disabled", 5, 30, -1, __FALSE__, __FALSE__ );
			break;

		case GPRS_ERR_NO_SIM:
			DisplayText( "- No SIM", 5, 30, -1, __FALSE__, __FALSE__ );
			break;

		case GPRS_ERR_SIM_LOCK:
			DisplayText( "- SIM locked", 5, 30, -1, __FALSE__, __FALSE__ );
			break;

		case GPRS_ERR_NO_PIN:
			DisplayText( "- No PIN", 5, 30, -1, __FALSE__, __FALSE__ );
			break;

		case GPRS_ERR_BAD_PIN:
			DisplayText( "- Bad PIN", 5, 30, -1, __FALSE__, __FALSE__ );
			break;

		case GPRS_ERR_FATAL:
			DisplayText( "- Fatal", 5, 30, -1, __FALSE__, __FALSE__ );
			break;

		case GPRS_ERR_UNKNOWN:
		default:
			DisplayText( "- Unknown", 5, 30, -1, __FALSE__, __FALSE__ );
			break;
		}
		break;

	case __COM_STATE_ERROR_ENABLE_GPRS:
		DisplayText( "GPRS enable Error :", 2, 20, -1, __FALSE__, __FALSE__ );
		sprintf( szTemp, "-  %d", nError );
		DisplayText( szTemp, 5, 30, -1, __FALSE__, __FALSE__ );
		break;

	}

	if( bKey == __TRUE__ )
	{
		DisplayText( ">", 0, 50, -1, __FALSE__, __FALSE__ );
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

// Functions
//-------------------------------------------------------------------

int CheckSIM( T_DGPRS_GET_INFORMATION *pInfo, int *pbResult, int *pError )
{
	switch( pInfo->start_report )
	{
		case DGPRS_REPORT_NOT_RECEIVED_YET:	
			return __FALSE__;
			break;

		case DGPRS_REPORT_SIM_NOT_PRESENT:
			*pError   = GPRS_ERR_NO_SIM;
			*pbResult = __FALSE__;
			return __TRUE__;
			break;

		case DGPRS_REPORT_FATAL_ERROR:
		case DGPRS_REPORT_UNKNOWN_ERROR:
		case DGPRS_REPORT_SIMLOCK_STATE:
			*pError   = GPRS_ERR_SIM_LOCK;
			*pbResult = __FALSE__;
			return __TRUE__;
			break;

		case DGPRS_REPORT_WAITING_CODE:
		default:
			break;
	}

	switch( pInfo->sim_status )
	{
	case DGPRS_SIM_NOT_RECEIVED_YET:
	case DGPRS_SIM_PIN_PRESENTED:
		return __FALSE__;
		break;

	case DGPRS_SIM_OK:
		*pError   = GPRS_OK;
		*pbResult = __TRUE__;
		return __TRUE__;
		break;

	case DGPRS_SIM_PIN_ERRONEOUS:
		*pError   = GPRS_ERR_BAD_PIN;
		*pbResult = __FALSE__;
		return __TRUE__;
		break;

	case DGPRS_SIM_PIN_REQUIRED:
		*pError   = GPRS_ERR_NO_PIN;
		*pbResult = __FALSE__;
		return __TRUE__;
		break;

	case DGPRS_SIM_NOT_INSERTED:
		*pError   = GPRS_ERR_NO_SIM;
		*pbResult = __FALSE__;
		return __TRUE__;
		break;

	case DGPRS_SIM_KO:
	case DGPRS_SIM_PIN2_REQUIRED:
	case DGPRS_SIM_PUK_REQUIRED:
	case DGPRS_SIM_PUK2_REQUIRED:
	default:
		*pError   = GPRS_ERR_SIM_LOCK;
		*pbResult = __FALSE__;
		return __TRUE__;
		break;
	}

	return __FALSE__;
}


int IsNetworkAvailable( int bGPRS, int *pbResult, int *pError, int *pbLinkPPP )
{
	static int nRadioLevel = -1;

	T_DGPRS_GET_INFORMATION info;
	FILE *gprs = NULL;

	char szTemp[100];

	int bReadySIM;

	gprs = stdperif(( char *)"DGPRS", NULL );

	if( gprs != NULL )
	{
		fioctl( DGPRS_FIOCTL_GET_INFORMATION, &info, gprs );

		sprintf( szTemp, "func=%08X netw=%d gprs=%d sreport=%d sstatus=%d rd=%d", 
						  info.func_enable, info.network_connection, info.status_gprs,
						  info.start_report, info.sim_status, info.radio_level );

		if( CheckSIM( &info, &bReadySIM, pError ) == __TRUE__ )
		{
			if( bReadySIM == __FALSE__ )
			{
				DisplayConnectionScreen( __COM_STATE_ERROR, *pError, 500, 1 );

				*pbResult = __FALSE__;
				return __FALSE__; // Stop Waiting.
			}
			else
			{
				// The SIM module is ready.
				if( info.radio_level > 0 )
				{
					nRadioLevel = info.radio_level;

					if( bGPRS == __TRUE__ )
					{
						// GPRS network.
						if(( info.func_enable & DGPRS_MASK_FUNC_GPRS ) &&
						   ( info.status_gprs != DGPRS_GPRS_DISCONNECTED ))
						{
							*pbResult = __TRUE__;

							
							if( info.status_gprs == DGPRS_GPRS_PDP_CONNECTED )
							{
								*pbLinkPPP = __TRUE__;
							}
							else
							{
								*pbLinkPPP = __FALSE__;
							}

							return __FALSE__; // Stop Waiting.
						}
					}
					else
					{
						// GSM network
						if(( info.func_enable & DGPRS_MASK_FUNC_GSM ) &&
						   ( info.network_connection == DGPRS_GSM_NETWORK_NORMAL_CONNECT ))
						{
							*pbResult = __TRUE__;
							return __FALSE__; // Stop Waiting.
						}
					}
				}
				else
				{
					if( nRadioLevel != -1 )
					{
						// No radio signal.
						*pError = GPRS_ERR_UNKNOWN;

						nRadioLevel = info.radio_level;
						*pbResult = __FALSE__;
						return __FALSE__; // Stop Waiting.
					}
				}
			}
		}
	}

	return __TRUE__;
}


int WaitNetworkAvailable( int bGPRS, unsigned int nWaitTimeout, unsigned int nWaitMaxTimeout, int *pError )
{
	unsigned int nWaitTotal = 0;
	int bContinue = __TRUE__;

	int bReady	= __FALSE__;
	int bPPP	= __FALSE__;

	do 
	{ 
		bContinue = IsNetworkAvailable( bGPRS, &bReady, pError, &bPPP );
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
		bContinue = IsNetworkAvailable( __TRUE__, &bReady, &nError, &bPPP );

		if(( bContinue == __TRUE__  ) && ( bPPP == __FALSE__ ))
		{
			ttestall( 0, nWaitTimeout );
			nWaitTotal += nWaitTimeout;
		}

	} while(( bContinue == __TRUE__ ) && ( bPPP == __FALSE__ ) && ( nWaitTotal < nWaitMaxTimeout ));

	return bPPP;
}

int WaitNetworkScreen( char *szAPN, int bGPRS )
{
	int nError;

	DisplayScreen( "Connecting GPRS...", "" );

	if( bGPRS )
	{
		nError = gprs_enable( szAPN );
	}
	else
	{
		nError = gsm_enable( szAPN );
	}

	
	if( nError == GPRS_OK )
	{
		if( WaitNetworkAvailable( bGPRS, __500_MSECONDS__, __60_SECONDS__, &nError ) == __TRUE__ )
		{
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


int PerformConnectionGPRS( char *szAPN, char *szLogin, char *szPassword )
{
	int nError = 0;

	FILE *hKeyboard = NULL;

	if( WaitNetworkScreen( szAPN, __TRUE__ ))
	{
		DisplayScreen( "Connecting PPP...", "" );

		hKeyboard = fopen("KEYBOARD", "r");
		nError = gprs_connect( T_ANN, szAPN , szLogin, szPassword, 30 );
		fclose(hKeyboard);

		if(( nError == GPRS_OK ) &&
		   ( WaitNetworkPPP( __500_MSECONDS__, __20_SECONDS__ ) == __TRUE__ ))
		{
			DisplayScreen( "Connecting PPP...", "OK !" );
			ttestall( 0, __3_SECONDS__ );
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


int PerformConnectionFTP( const char *szHostName, unsigned int nPort, 
						  const char *szLogin, const char *szPassword,
						  const char *szDirectory, 
						  const char *szDiskName, unsigned int nDiskSize )
{
	RAMDISK_HANDLE hDisk = NULL;

	int nReturn = -1;

	hDisk = iFtp_download_dir( szHostName, nPort, szLogin, szPassword,
							   szDirectory,
							   szDiskName, nDiskSize );

	if( hDisk != NULL )
	{
		DisplayScreen( "Download success !", "Activate software..." );	

		if( RAMDISK_Activate( hDisk ) == 0 )
		{
			ttestall( 0, 200 );
			nReturn = 0;
		}

		RAMDISK_Delete( hDisk );
	}

	return nReturn;
}


