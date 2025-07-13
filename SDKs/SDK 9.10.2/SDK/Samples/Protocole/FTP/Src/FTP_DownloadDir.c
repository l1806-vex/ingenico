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
// Description: FTP downloading (sample to use the static FTP_ library).
//      
// Author:      V.GOMES
// Version:     1.0
// Date:        2005/07/22 
//
//-------------------------------------------------------------------

// Includes.
//-------------------------------------------------------------------
#include <SDK30.h>
//#include <malloc.h>

#include <FTP_.h>

#include "loader_util.h"
#include "UserInterfaceHelpers.h"

#include "FTP_DownloadDir.h"

// Macros & preprocessor definitions.
//-------------------------------------------------------------------
#define __DATA_SIZE			4096

#define __5_SECONDS__		500


#define __ERR_CONNECTION			20
#define	__ERR_NULL_ADDRESS			21
#define __ERR_GET_LIST_FILES		22
#define __ERR_BAD_DIRECTORY			24
#define __ERR_FILENAME_TO_LONG		25
#define __ERR_TO_MANY_FILES			26
#define __ERR_RAMDISK_CREATION		30
#define __ERR_RAMDISK_FULL			42
#define __ERR_GET_FILE				43
#define __ERR_DISCONNECTION_PPP		60
#define __ERR_SOFTWARE_ACTIVATE		70

#define __ANY_ARG(a)	((void*)(a))

// Functions
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// Name  : iFtp_Error
// Param :
//	I  : nError		: Error identifier. The list of errors is listed above.
//	I  : p1			: Parameter 1. 
//	I  : p2			: Parameter 2.
//	I  : nTimeout	: Timeout
//
// Description :
//		This functions displays an error screen.
//
// Return :
//		None.
// 
//-------------------------------------------------------------------
void iFtp_Error( int nError, void *p1, void *p2, int nTimeout )
{
	char cBuf1[60];

	switch( nError )
	{
	case __ERR_FILENAME_TO_LONG:
		DisplayScreen( "Error 25:", "File name length" );
		break;

	case __ERR_TO_MANY_FILES:
		DisplayScreen( "Error 26:", "Too many files" );
		break;

	case __ERR_CONNECTION:
		// Connection Error.
		sprintf( cBuf1, "%s", (char*) p1 );
		DisplayScreen( "Error 20: Connection", cBuf1 );
		break;

	case __ERR_GET_LIST_FILES:
		DisplayScreen( "Error 22:", "Can't list files" );
		break;

	case __ERR_BAD_DIRECTORY:
		sprintf( cBuf1, "Bad Directory %s", (char*) p1 );
		DisplayScreen( "Error 24", cBuf1 );
		break;

	case __ERR_RAMDISK_CREATION:
		DisplayScreen( "Error 30:", "Disk creation" );
		break;

	case __ERR_RAMDISK_FULL:
		DisplayScreen( "Error 42:", "Disk full" );
		break;

	case __ERR_GET_FILE:
		sprintf( cBuf1, "FTP Get file %s", (char*) p1 ); 

		DisplayScreen( "Error 43:", cBuf1 );
		break;

	case __ERR_SOFTWARE_ACTIVATE:
		DisplayScreen( "Error 70: Software", "Activation failed" );
		break;

	case __ERR_DISCONNECTION_PPP:
		DisplayScreen( "Error 60: ", "Disconnection PPP" );
		break;

	case __ERR_NULL_ADDRESS:
		DisplayScreen( "Error 21: server", "No Address " );
		break;

	default:
		break;
	}

	if( nTimeout != 0 )
	{
		ttestall( 0, nTimeout );
	}
}


//-------------------------------------------------------------------
//
// Name  : iFtp_init_file_list
// Param :
//	O  : aFilenames	: File name list.
//	I  : nMaxFile	: List size. 
//
// Description :
//		This functions initializes the file name list.
//
// Return :
//		None.
// 
//-------------------------------------------------------------------
void iFtp_init_file_list( char **aFilenames, int nMaxFile )
{
	memset( aFilenames, 0, nMaxFile * sizeof( char *));
}

//-------------------------------------------------------------------
//
// Name  : iFtp_reset_file_list
// Param :
//	O  : aFilenames	: File name list.
//	I  : nMaxFile	: List size. 
//
// Description :
//		This functions clears the file name list.
//		The allocated memory for the file names is freed.
//
// Return :
//		None.
// 
//-------------------------------------------------------------------
void iFtp_reset_file_list( char **aFilenames, int nMaxFile )
{
	int i;
	for( i = 0; i < nMaxFile; i++ )
	{
		if( aFilenames[i] != NULL )
		{
			ufree( aFilenames[i] );
		}
	}
}

//-------------------------------------------------------------------
//
// Name  : iFtp_get_file_list
// Param :
//	I  : hFTP		: FTP connection handle.
//	O  : aFilenames	: File name list.
//	I  : nMaxFile	: List size. 
//
// Description :
//		This functions retrieves the content of the current remote directory,
//		and stores the name of all of its contained files in the file name list.
//
// Return :
//		The number of files.
// 
//-------------------------------------------------------------------
int iFtp_get_file_list(	FTP_HANDLE hFTP, 
						char **aFilenames, 
						int nMaxFile )
{
	int bContinue	= 1;
	int nNbFiles	= 0;

	if( FTP_GetList( hFTP, "." ) == 0 )
	{
		DisplayScreen( "Files list received !", "");

		while( bContinue == 1 )
		{
			const char *szFilename = FTP_GetListItem( hFTP );

			if( szFilename != NULL)
			{
				if( nNbFiles < nMaxFile )
				{
					// Avoid to try to download '.' and '..' objects returned as file names...
					if( ( strcmp( szFilename, "." )  != 0 ) && ( strcmp( szFilename, ".." ) != 0 ) )
					{
						// Duplicate Name. And store it in the filename array.
						aFilenames[nNbFiles] = (char *) umalloc( strlen ( szFilename ) + 1 );
						strcpy( aFilenames[nNbFiles], szFilename );
						nNbFiles++;
					}
				}
				else
				{
					iFtp_Error( __ERR_TO_MANY_FILES, NULL, NULL, __5_SECONDS__ );
				}
			}
			else
			{
				bContinue = 0;
			}
		}

		FTP_CloseData( hFTP );
	}

	return nNbFiles;
}

//-------------------------------------------------------------------
//
// Name  : iFtp_download_file
// Param :
//	I  : hFTP		: FTP connection handle.
//	IO : hDisk		: Local RAM disk handle.
//	I  : szFilename	: Name of the file to download.
//
// Description :
//		This functions downloads a remote file into a local RAM disk.
//
// Return :
//		0	: Success
//		<0	: Error.
// 
//-------------------------------------------------------------------
int iFtp_download_file( FTP_HANDLE hFTP, RAMDISK_HANDLE hDisk, char *szFilename )
{
	unsigned char pucBuffer[__DATA_SIZE];

	int nRet = -1;

	int nReadBytes  = 0;

	if( FTP_Get( hFTP, szFilename ) == 0 )
	{
		// Create file.
		RAMDISK_FILE hFile = RAMDISK_OpenFile( hDisk, szFilename, "a");

		if( hFile != 0 )
		{
			nRet = 0;
			do
			{
				nReadBytes =  FTP_GetData( hFTP, (char*) pucBuffer, __DATA_SIZE );
				if( nReadBytes >= 0 )
				{
					if( RAMDISK_WriteInFile( hDisk, hFile, pucBuffer, nReadBytes ) != 0 )
					{
						nRet = -1;
					}
				}
			} while(( nReadBytes > 0 ) && ( nRet == 0 ));

			//
			RAMDISK_CloseFile( hDisk, hFile );
		}

		// Close FTP data channel.
		FTP_CloseData( hFTP );
	}
	else
	{
		iFtp_Error( __ERR_GET_FILE, (void*) szFilename, NULL, __5_SECONDS__ );
	}

	return nRet;
}

//-------------------------------------------------------------------
//
// Name  : iFtp_download_files
// Param :
//	I  : hFTP		: FTP connection handle.
//	IO : hDisk		: Local RAM disk handle.
//	I  : aFilenames	: List of file names to download.
//	I  : nMaxFile	: List size. 
//
// Description :
//		This functions downloads a list of files into a local RAM disk.
//
// Return :
//		0	: Success
//		<0	: Error.
// 
//-------------------------------------------------------------------
int iFtp_download_files( FTP_HANDLE hFTP, RAMDISK_HANDLE hDisk, 
						 char **aFilenames, int nNbFiles )
{
	char cBuf1[60];
	char cBuf2[60];

	int i = 0;
	int bContinue = 1;

	FTP_SetType( hFTP, __TYPE_IMAGE );

	while(( bContinue == 1 ) && ( i < nNbFiles ))
	{
		sprintf( cBuf1, "Download file %d/%d",  i+1, nNbFiles );
		sprintf( cBuf2, "%s",  aFilenames[i] );
		DisplayScreen( cBuf1, cBuf2 );

		if( iFtp_download_file( hFTP, hDisk, aFilenames[i] ) == 0 )
		{
			// Next File.
			i++;
		}
		else
		{
			bContinue = 0;
		}
	}

	if( bContinue == 1 )
	{
		// Success !
		return 0;
	}

	return -1;
}


//-------------------------------------------------------------------
//
// Name : iFtp_download_dir
// Param :
//	I  : szAddress	: FTP server address (resolved name www.xxx.yyy.zzz)
//	I  : nPort		: FTP server port (normally 21)
//	I  : szLogin	: User for FTP authentication
//	I  : szPassword	: Password for FTP authentication
//	I  : szDirectory: Remote directory to be downloaded.
//	I  : szLocalDiskName : Local RAM disk name.
//  I  : nLocalDiskSize  : Local disk size (in bytes).
//
// Description :
//		This functions performs a FTP connection and download all the content of a remote
//		directory. It creates and returns a local RAM disk which contains 
//		the downloaded files 
//
// Return :
//		Handle on the local RAM disk.
//		NULL in case of failure.
// 
//-------------------------------------------------------------------
RAMDISK_HANDLE iFtp_download_dir( const char *szAddress, 
								  unsigned int nPort, 
								  const char *szLogin, 
								  const char *szPassword, 
								  const char *szDirectory,
								  const char *szLocalDiskName,
								  unsigned int nLocalDiskSize )
{
	RAMDISK_HANDLE hDisk = NULL;

	int nNbFiles = 0;

	char *aFilenames[MAX_FILE];


	FTP_HANDLE hFTP = 0; // FTP connection Handle.

	DisplayScreen( "Initializing data...", "" );

	iFtp_init_file_list( aFilenames, MAX_FILE );

	//
	DisplayScreen( "Connecting FTP server...", szAddress );

	hFTP = FTP_Connect( szLogin, szPassword, 
						szAddress, (unsigned short) nPort, TRUE );

	if( hFTP != NULL )
	{
		DisplayScreen( "Searching directory", szDirectory  );
		  
		if( FTP_ChangeDir( hFTP, (char*) szDirectory ) == 0 )
		{
			DisplayScreen( "Looking for file(s) list", "" );

			nNbFiles = iFtp_get_file_list( hFTP, aFilenames, MAX_FILE );
			if( nNbFiles > 0 )
			{			
				// RAM disk creation.
				hDisk = RAMDISK_Create( szLocalDiskName, nLocalDiskSize, 
								        nNbFiles + 1 );
					
				if( hDisk != 0 )
				{
					if( iFtp_download_files( hFTP, hDisk, aFilenames, nNbFiles ) == 0 )
					{
						// Download OK.
					}
					else
					{
						// Download Error.
						// Delete RAMDISK and return NULL.
						RAMDISK_Delete( hDisk );
						hDisk = NULL;
					}
				}
				else
				{
					iFtp_Error( __ERR_RAMDISK_CREATION, 
								__ANY_ARG(szLocalDiskName), __ANY_ARG(nLocalDiskSize),
								__5_SECONDS__ );
				}
			}
			else
			{
				iFtp_Error( __ERR_GET_LIST_FILES, NULL, NULL, __5_SECONDS__ );
			}
		}
		else
		{
			iFtp_Error( __ERR_BAD_DIRECTORY, __ANY_ARG(szDirectory), NULL, __5_SECONDS__ );
		}

		DisplayScreen( "Disconnecting FTP...", "" );
		FTP_Disconnect( hFTP );
	}
	else
	{
		iFtp_Error( __ERR_CONNECTION, __ANY_ARG(szAddress), __ANY_ARG(nPort), __5_SECONDS__ );
	}

	// Destroy filename list.
	iFtp_reset_file_list( aFilenames, MAX_FILE );

    
	return hDisk;
}


