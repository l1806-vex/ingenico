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
*	Launch an application download with the help of CALLHOST.
*
*	Although the classical way is to use the "remote_downloading" function, 
*   the CallHost facility allows you to custom the calling sequence, 
*   especially displayed messages.
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

//
//
#define __DWND_ACTION_NONE		0
#define __DWND_ACTION_OPEN		1
#define __DWND_ACTION_CLOSE		2
#define __DWND_ACTION_WRITING	3
#define __DWND_ACTION_READING	4

#define __DWND_LIST_NOT_PRESENT 0
#define __DWND_LIST_NOT_TREATED 1
#define __DWND_LIST_TREATED		2

typedef struct
{
	int m_bConnected;
	int m_nAction;

	int m_nCounter;		// Increased for each event of the handler. Use as a "bad" semaphore.
	int m_nProgress;

	int m_nDowloadListStatus;

	char m_szCurrentFile[40];
	int m_nRead;
	int m_nWritten;

	int m_nTotalLength;

} tINFO_DOWNLOAD;

typedef struct 
{
	char m_szFilename[40];
	int m_nSize;
}
tINFO_FILE_TO_DOWNLOAD;


//
static const char STORAGE_DISK[]	= "SYSTEM";
static const char COMPOFILE[]		= "COMPOFILE";


// Task variables.
static short g_MainTask;		// Main task ( the calling one ).
volatile int g_bThreadTerminated = __FALSE__;

//
tINFO_DOWNLOAD g_InfoDownloadProgress;


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void InitProgressInfo( tINFO_DOWNLOAD *pInfo )
{
	pInfo->m_bConnected	= __FALSE__;
	pInfo->m_nAction	= __DWND_ACTION_NONE;
	pInfo->m_nCounter	= 0;
	pInfo->m_nProgress	= 0;
	pInfo->m_nDowloadListStatus = __DWND_LIST_NOT_PRESENT;

	pInfo->m_szCurrentFile[0]	= '\0';
	pInfo->m_nRead		= 0;
	pInfo->m_nWritten	= 0;

	pInfo->m_nTotalLength = 0;
}

//------------------------------------------------------------------------------------------------------
// Add a new software to download in the list file.
// - szDowloadListFilename : the full name of the file containing the list of the filenames to download.
// - szSoftwareName : software to add in the list of files to download.
//
//------------------------------------------------------------------------------------------------------
int AddSoftwareInListFile( const char *szDowloadListFilename, const char *szSoftwareName  )
{
	int ret;
	unsigned int nMode = FS_WRITEONCE;
	
	S_FS_FILE *fp = NULL;

	char szTemp[40];

	// Mount disk.
	sprintf( szTemp, "/%s", VOLUME_MANAGER_RECEPT );

	ret = FS_mount( szTemp ,&nMode );
	if( ret == FS_OK )
	{
		sprintf( szTemp, "/%s/%s", VOLUME_MANAGER_RECEPT, szDowloadListFilename );
		FS_unlink( szTemp );

		// Open download list file. 
		fp = FS_open( szTemp, "a" );
		if( fp != NULL )
		{
			// And a line for the software to download.
			ret = FS_write((char*) szSoftwareName, 1, strlen( szSoftwareName ), fp );
			ret = FS_write( "\r\n", 1, 2, fp );

			FS_close( fp );
		}
	}

	return ret;
}

//------------------------------------------------------------------------------------------------------
// When the TMS is connected, the first it does is to send the file : /SWAP/DOWNLOAD.LST.
// This file contains all the download files and their size.
// The format of this file is for example.
//  xxx
//  31212.ADF;125
//  31212.SGN;125523
//  ...
//------------------------------------------------------------------------------------------------------
tINFO_FILE_TO_DOWNLOAD *ReadDownloadList( int *o_pnNbFiles )
{
	tINFO_FILE_TO_DOWNLOAD *pRet = NULL;
	int nNbFiles = 0;

	unsigned int nMode = FS_WRITEMANY;
	S_FS_FILE *hFile;

	char *szBuffer;
	char *szPtr1;
	char *szPtr2;

	char szTemp[40];
	char Label_P[33];

	
	strcpy(Label_P,"/SWAP");
	if( FS_mount (Label_P, &nMode) == FS_OK )
	{
		// Open download list file.
		hFile = FS_open( "/SWAP/DOWNLOAD.LST", "r" );
		if( hFile != NULL )
		{
			int nFileSize = FS_length( hFile );
			if( nFileSize > 0 )
			{
				szBuffer = umalloc( nFileSize + 1);
				if( FS_read( szBuffer, nFileSize, 1, hFile ) == 1 )
				{
					szBuffer[nFileSize] = '\0';

					// All the file is read in the buffer 'pucBuffer';
					nNbFiles = atoi( szBuffer );

					if( nNbFiles != 0 )
					{
						int i = 0;

						// Allocate return buffer.
						pRet = umalloc( sizeof( tINFO_FILE_TO_DOWNLOAD ) * nNbFiles );
						*o_pnNbFiles = nNbFiles;

						sprintf( szTemp, "%d files to load\n", nNbFiles );
						PrintText( szTemp, 1 );

						// Treat each line.
						szPtr1 = strstr( szBuffer, "\n" );
						while( szPtr1 != NULL )
						{
							szPtr1++;

							szPtr2 = strstr( szPtr1, ";" );
							if( szPtr2 != NULL )
							{
								*szPtr2 = '\0';
								strcpy( pRet[i].m_szFilename, szPtr1 );

								szPtr1 = szPtr2 + 1;
								pRet[i].m_nSize = atoi( szPtr1 );

								//
								sprintf( szTemp, "%s : %d\n", pRet[i].m_szFilename, pRet[i].m_nSize );
								PrintText( szTemp, 1 );

								i++;
							}

							szPtr1 = strstr( szPtr1, "\n" );							
						}
					}
				}
				ufree( szBuffer );
			}
			FS_close (hFile);
		}
		FS_unmount (Label_P);
	}

	return pRet;
}

tINFO_FILE_TO_DOWNLOAD *GetInfoFile( const char *szFilename, tINFO_FILE_TO_DOWNLOAD *aDownloadList, int nNbFiles )
{
	int i;
	for( i=0; i < nNbFiles; i++ )
	{
		if( strcmp( aDownloadList[i].m_szFilename, szFilename ) == 0 )
		{
			return &aDownloadList[i];
		}
	}

	return NULL;
}


//------------------------------------------------------------------------------------------------------
// Monitor the display task.
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
// Main function of the display task in charge of displaing the download progress.
//------------------------------------------------------------------------------------------------------
void DisplayTask (void)
{
	int nCounter;
	char szTemp[40];

	FILE *hDisplay = NULL;

	tINFO_FILE_TO_DOWNLOAD *aInfoFiles = NULL;
	int nNbFiles;

	tINFO_FILE_TO_DOWNLOAD *pInfoFile = NULL;

	// Get he display driver.
	hDisplay = fopen( "DISPLAY", "w" );

	//
	CreateGraphics( _MEDIUM_ );

	DisplayText( "Download in progress...", 2, 20, -1, 0 );

	nCounter = 0;

	//
	g_bThreadTerminated = __FALSE__;
	while( g_bThreadTerminated == __FALSE__ )
	{
		if( g_InfoDownloadProgress.m_nDowloadListStatus == __DWND_LIST_NOT_TREATED )
		{
			// The download list has been downloaded.
			// Read it in order to get all the sizes of files to download.
			aInfoFiles = ReadDownloadList( &nNbFiles );
			g_InfoDownloadProgress.m_nDowloadListStatus = __DWND_LIST_TREATED;
		}

		if( nCounter != g_InfoDownloadProgress.m_nCounter )
		{
			nCounter = g_InfoDownloadProgress.m_nCounter;

			switch( g_InfoDownloadProgress.m_nAction )
			{
				case __DWND_ACTION_OPEN:
					sprintf( szTemp, "Opening : %s", g_InfoDownloadProgress.m_szCurrentFile );
					DisplayText( szTemp, 2, 30, -1, __TRUE__ );

					// Retrieve the size of this file.
					g_InfoDownloadProgress.m_nTotalLength = -1;
					if( aInfoFiles != NULL )
					{
						pInfoFile = GetInfoFile( g_InfoDownloadProgress.m_szCurrentFile, aInfoFiles, nNbFiles );
						if( pInfoFile != NULL )
						{
							g_InfoDownloadProgress.m_nTotalLength = pInfoFile->m_nSize;

							sprintf( szTemp, "0/%d : 0", g_InfoDownloadProgress.m_nTotalLength );
							DisplayText( szTemp, 2, 40, -1, __TRUE__ );
						}
					}
					break;

				case __DWND_ACTION_CLOSE:
					sprintf( szTemp, "Closing : %s", g_InfoDownloadProgress.m_szCurrentFile );
					DisplayText( szTemp, 2, 30, -1, __TRUE__ );
					break;

				case __DWND_ACTION_WRITING:
					sprintf( szTemp, "Writing : %s", g_InfoDownloadProgress.m_szCurrentFile );
					DisplayText( szTemp, 2, 30, -1, __TRUE__ );

					if( g_InfoDownloadProgress.m_nTotalLength != -1 )
					{
						sprintf( szTemp, "%d/%d : %d",  g_InfoDownloadProgress.m_nWritten, g_InfoDownloadProgress.m_nTotalLength,
								 ( g_InfoDownloadProgress.m_nWritten * 100 ) / g_InfoDownloadProgress.m_nTotalLength );
						DisplayText( szTemp, 2, 40, -1, __TRUE__ );
					}
					break;

				case __DWND_ACTION_READING:
					sprintf( szTemp, "Reading : %s", g_InfoDownloadProgress.m_szCurrentFile );
					DisplayText( szTemp, 2, 30, -1, __TRUE__ );
					break;

				case __DWND_ACTION_NONE:
				default:
					if( g_InfoDownloadProgress.m_bConnected == __TRUE__ )
					{
						DisplayText( "Connected", 2, 30, -1, __TRUE__ );
					}
					else
					{
						DisplayText( "...", 2, 30, -1, __TRUE__ );
					}
					break;
			}
		}

		ttestall( 0, 1 ); // Wait 100 ms.
	}

	// Release the DISPLAY handle. 
	fclose( hDisplay );

	// Send a special event to the main task
	// to indicate that the child task is finished,
	// and it can be killed.
	SignalEvent( g_MainTask, 30 );
	ttestall(0,0);
}


t_topstack *CreateDisplayTask()
{
	return fork( (void*)DisplayTask, 0, 0 );
}

//------------------------------------------------------------------------------------------------------
// CallHost handler. Receieves the events of the download progress.
// Be careful this task is called by the system. The use of this task is limited.
// Just set shared parameters.
//------------------------------------------------------------------------------------------------------
int CallHostHandler( unsigned lg, U_CALLBACK *pData )
{	
	switch( pData->id )
	{
	case CALLBACK_DISCONNECT:
		// Disconnected
		g_InfoDownloadProgress.m_bConnected = __FALSE__;
		g_InfoDownloadProgress.m_nCounter++;
		break;

	case CALLBACK_CONNECT:
		// Connected.
		g_InfoDownloadProgress.m_bConnected = __TRUE__;
		g_InfoDownloadProgress.m_nCounter++;
		break; 

	case CALLBACK_WRITE:
		g_InfoDownloadProgress.m_nAction = __DWND_ACTION_WRITING;
		g_InfoDownloadProgress.m_nProgress++;

		g_InfoDownloadProgress.m_nWritten	+= pData->write.len;

		g_InfoDownloadProgress.m_nCounter++;
     	break;

	case CALLBACK_READ:
		g_InfoDownloadProgress.m_nAction = __DWND_ACTION_READING;
		g_InfoDownloadProgress.m_nProgress++;
		g_InfoDownloadProgress.m_nRead	+= pData->read.len;
		g_InfoDownloadProgress.m_nCounter++;
     	break;

	case CALLBACK_OPEN:
		g_InfoDownloadProgress.m_nAction = __DWND_ACTION_OPEN;
		g_InfoDownloadProgress.m_nProgress = 0;

		// New file, reset bytes counter.
		strcpy( g_InfoDownloadProgress.m_szCurrentFile, pData->open.file );
		g_InfoDownloadProgress.m_nRead		= 0;
		g_InfoDownloadProgress.m_nWritten	= 0;

		g_InfoDownloadProgress.m_nCounter++;
     	break;

	case CALLBACK_CLOSE:
		g_InfoDownloadProgress.m_nAction = __DWND_ACTION_CLOSE;
		g_InfoDownloadProgress.m_nProgress = 0;
		g_InfoDownloadProgress.m_nCounter++;

		if( strcmp( g_InfoDownloadProgress.m_szCurrentFile, "DOWNLOAD.LST" ) == 0 )
		{
			g_InfoDownloadProgress.m_nDowloadListStatus = __DWND_LIST_NOT_TREATED;
		}
     	break;
				
	}
	return __TRUE__;
}



//------------------------------------------------------------------------------------------------------
// Request the call host.
// nRemoteType  : the type of download : REMOTE_CALL (PSTN download) or REMOTE_IP (IP download).
// szCallNumber : the server number. In case of a TCP/IP server
//                the number is formatted as follow : "xxx.xxx.xxx.xxx:yyy"
//				  where "xxx.xxx.xxx.xxx" is the IP address and
//				  "yyy" the port.
// szCallingAppliName : the name of the application requesting the download.
// szContractNumber	  : the contract number.
// szDowloadListFilename : the full name of the file containing the list of the filenames to download.
// nMaxRetries	: Number of retries.
// nRetryDelay	: Delay in seconds between 2 retries.
// pCallBack	: Callback function, receives the progress event of the download.
//
//------------------------------------------------------------------------------------------------------
int ExecuteCallHost( int nRemoteType,
					 const char *szCallNumber,
					 const char *szCallingAppliName,
					 const char *szContractNumber,
					 const char *szDowloadListFilename,
					 int nMaxRetries,
					 int nRetryDelay,
					 int (*pCallBack)(unsigned, U_CALLBACK *))
{
	S_PARAM_SYSTEM_CALL ParamCall;
	long nPerformedActivity;

	char szTemp[40];

	// Structure init
	memset( &ParamCall, ' ', sizeof( S_PARAM_SYSTEM_CALL ));

	strcpy( ParamCall.CallNumber, szCallNumber ); 

	// ParamCall.Contract : 1st byte must be set to '1' to indicate that contract exist
	//			Other bytes are contract number.
	//			Length must be 10 digits (if needed, this field must be padded with blank)
	strcpy( ParamCall.Contract, "1" );		//'1' to indicate that contract exist.
	memcpy( &ParamCall.Contract[1], szContractNumber, strlen( szContractNumber ));

	// Application number that requests the download.
	strcpy( ParamCall.AppliName,  szCallingAppliName ); 

	ParamCall.AuthorizedActivity = DOWNLOADING_ACTIVITY ;
	strcpy( ParamCall.DiskActivity[IDX_DOWNLOADING_ACTIVITY], STORAGE_DISK );

	//
	sprintf( szTemp, "/%s/%s", VOLUME_MANAGER_RECEPT, szDowloadListFilename );
	strcpy( ParamCall.UpdateComponentList, szTemp );

	//
	ParamCall.CallReason = MANUAL_CALL;
	ParamCall.Nb1 = nMaxRetries;
	ParamCall.T1  = nRetryDelay;
	ParamCall.CallBack = pCallBack; 

    // Fork the task to display in charge of the display. 
	return CallHost( nRemoteType, &ParamCall, &nPerformedActivity );
}



////////////////////////////////////////////////////////////////////////////////////////

int PerformCallHost( int nRemoteType,
					 const char *szCallNumber,
					 const char *szCallingAppliName,
					 const char *szContractNumber,
					 const char *szSoftwareName )
{
	int nRet = 0;

	t_topstack	*pDisplayTask	= NULL;
	int nEvent;

	// Add the software to download in the list file.
	AddSoftwareInListFile( COMPOFILE, szSoftwareName  );

	// Create the display task.
	g_MainTask = CurrentTask();
	pDisplayTask = CreateDisplayTask();

	// Be careful on EFT30.
	// At this moment the DISPLAY driver belongs to the display task only.
	// It is forbidden to access it in the main Task.

	if( pDisplayTask != NULL )
	{
		// Reset the progress info.
		InitProgressInfo( &g_InfoDownloadProgress );

		// Perform CallHost.
		nRet = ExecuteCallHost(	nRemoteType,
								szCallNumber,
								"SAMPLE",
								szContractNumber,
								COMPOFILE,
								5,		// Maximum 5 retries.
								30,		// 30 seconds between 2 retries.
								CallHostHandler );

		// Terminate the child task.
		g_bThreadTerminated = TRUE;

		// Wait for its end and kill it.
		nEvent = ttestall((1 << 30), 0 );
		kill( pDisplayTask, "" );
	}

	// It is mandatory to reset after CallHost function
	if( nRet == 0 )
	{
		exit(0);
	}

	return nRet;
}
