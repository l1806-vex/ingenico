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
// Description: RAM disk management for FTP file download.
//      
// Author:      V.GOMES
// Version:     1.0
// Date:        2005/07/22 
//
//-------------------------------------------------------------------

// Includes.
//-------------------------------------------------------------------

//#include "oem.h"
//#include "fs.h"

#include <SDK30.h>

#include "loader_util.h"

// Macros & preprocessor definitions.
//-------------------------------------------------------------------


// Types.
//-------------------------------------------------------------------

typedef struct
{
	char m_szName[40];		// Disk name.
	unsigned long m_nSize;	// Disk size.
	int m_bUnload;			// Unload application.

	int m_nFreeSize;

} T__RAMDISK;


// Functions.
//-------------------------------------------------------------------
int __SoftwareActivate( const char *szName );

int RAMDISK_WriteInFile( RAMDISK_HANDLE hDisk, void *hFile,
						 const unsigned char *pucBuffer, unsigned int nSize )
{
	T__RAMDISK* pDisk = (T__RAMDISK*)hDisk;
	
	if( ( pDisk != NULL ) && ( nSize <= pDisk->m_nSize ) )
	{
		unsigned int nBytes = FS_write(	(unsigned char *) pucBuffer, 
										1, nSize, 
										(S_FS_FILE*) hFile );

		pDisk->m_nSize -= nBytes;

		if( nBytes == nSize )
		{
			return 0;
		}
	}

	return -1;
}

RAMDISK_HANDLE RAMDISK_Create( const char *szName, unsigned long nSize, 
							   unsigned int nMaxFile )
{
    unsigned long nDiskSize = 0;
    S_FS_PARAM_CREATE  DiskParam;
	T__RAMDISK* pDisk = NULL;

    // Create the disk.
    strcpy( DiskParam.Label, szName );

    DiskParam.Mode         = FS_WRITEMANY;
    DiskParam.IdentZone    = FS_WO_ZONE_APPLICATION;
    DiskParam.AccessMode   = FS_WRTMOD;
    DiskParam.NbFichierMax = nMaxFile;

    nDiskSize = FreeSpace() - (512 * 1024);

    if( nDiskSize > (4096 * 1024))
    {
        nDiskSize = 4096 * 1024;
    }

	if( nDiskSize > nSize )
	{
		nDiskSize = nSize;
	}

    if( FS_dskcreate( &DiskParam, &nDiskSize ) == FS_OK )
	{
		pDisk = (T__RAMDISK*)umalloc( sizeof(T__RAMDISK) );
		if( pDisk != NULL )
		{
			strcpy( pDisk->m_szName, szName );

			pDisk->m_nSize     = nDiskSize;
			pDisk->m_bUnload   = 0;
			pDisk->m_nFreeSize = nDiskSize - 512;	// !! VG : 512 bytes allocated 
													// for the resumption file.
		}
	}

	return (RAMDISK_HANDLE)pDisk;
}


int RAMDISK_Delete( RAMDISK_HANDLE hDisk )
{
	T__RAMDISK* pDisk = (T__RAMDISK*)hDisk;

	char szDisk[16];
	int  nError = 0;

	if( ( pDisk != NULL ) && ( pDisk->m_nSize != 0 ) )
	{
		// Add the starting '/'
		sprintf( szDisk, "/%s", pDisk->m_szName );
		
		// Unmount the disk
		nError = FS_unmount( szDisk );
		if( nError == FS_OK )
		{
			// Destroy the disk
			nError = FS_dskkill( szDisk );
			if( nError == FS_OK )
			{
				ufree( pDisk );
				return 0; // Successful !!!
			}
		}
	}

	return (-1);
}



RAMDISK_FILE RAMDISK_OpenFile( RAMDISK_HANDLE hDisk, const char *szName, const char *szMode )
{
    T__RAMDISK* pDisk = (T__RAMDISK*)hDisk;
	S_FS_FILE*  hFile = NULL;

	char szFullPath[64];

	if( memcmp( szName, "./", strlen("./") ) == 0 )
	{
		// In case of file names beginning with "./", skip it !
		szName += strlen( "./" );
	}
    
	if( pDisk != NULL )
	{
		if( strchr( pDisk->m_szName, '/') == NULL )
		{
			sprintf( szFullPath, "/%s/%s", pDisk->m_szName, szName );
		}
		else 
		{
			sprintf( szFullPath, "%s/%s", pDisk->m_szName, szName );
		}

		hFile = FS_open((char*) szFullPath, (char*) szMode );
    }

    
    return hFile;
}

void RAMDISK_CloseFile( RAMDISK_HANDLE hDisk, RAMDISK_FILE hFile )
{
    FS_close((S_FS_FILE*) hFile );
}




int RAMDISK_Activate( RAMDISK_HANDLE hDisk )
{
	T__RAMDISK* pDisk = (T__RAMDISK*)hDisk;
	
	if( pDisk != NULL )
	{
		if( __SoftwareActivate( pDisk->m_szName ) == 0 )
		{
			return 0;
		}
	}

	return -1;
}
