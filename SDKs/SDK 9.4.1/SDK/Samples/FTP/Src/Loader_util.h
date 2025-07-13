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

#ifndef __LOADER_UTIL_H__
#define __LOADER_UTIL_H__

// Macros & preprocessor definitions.
//-------------------------------------------------------------------
#define MAX_FILE (120)
#define MAX_FILE_LEN (15)

// Types
//-------------------------------------------------------------------
typedef void * RAMDISK_HANDLE; 
typedef void * RAMDISK_FILE;


// Functions.
//-------------------------------------------------------------------
						 
RAMDISK_HANDLE RAMDISK_Create( const char *szName, unsigned long nSize, 
							   unsigned int nMaxFile );

int RAMDISK_Delete( RAMDISK_HANDLE hDisk );

RAMDISK_FILE RAMDISK_OpenFile( RAMDISK_HANDLE hDisk, 
								const char *szName, const char *szMode );

void RAMDISK_CloseFile( RAMDISK_HANDLE hDisk, RAMDISK_FILE hFile );

int RAMDISK_WriteInFile( RAMDISK_HANDLE hDisk, 
						  void *hFile, const unsigned char *pucBuffer, unsigned int nSize );

int RAMDISK_Activate( RAMDISK_HANDLE hDisk );

//-------------------------------------------------------------------
//-------------------------------------------------------------------
#endif // __LOADER_UTIL_H__

