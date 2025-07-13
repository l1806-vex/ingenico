/**
 * \file	CST_Disk.c
 * \brief 	Module that manages the terminal flash file management.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "CST_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Mount a disk from the flash.

int CST_Disk_Mount(const char* szDisk)
{
	unsigned int nMountMode;
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);

	// Mount the disk
	nMountMode = 0;
	return FS_mount(DirName, &nMountMode);
}



//! \brief Unmount a disk.

int CST_Disk_Unmount(const char* szDisk)
{
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);
	return FS_unmount(DirName);
}



//! \brief Create a disk in the flash (with given parameters).

int CST_Disk_Create(const char* szDisk, int nMode, int nAccessMode, int nMaxNumOfFiles, int nDiskSize)
{
	S_FS_PARAM_CREATE Params;
	unsigned long ulSize;
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);

	// Set the disk parameters
	memset(&Params, 0, sizeof(Params));

	strncpy(Params.Label, szDisk, sizeof(Params.Label));
	Params.Mode = nMode;
	Params.AccessMode = nAccessMode;
	Params.NbFichierMax = nMaxNumOfFiles;
	Params.IdentZone = FS_WO_ZONE_DATA;
	ulSize = (unsigned long)nDiskSize;

	// Create the disk
	return FS_dskcreate(&Params, &ulSize);
}



//! \brief Delete a disk in the flash.

int CST_Disk_Kill(const char* szDisk)
{
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);
	return FS_dskkill(DirName);
}



//! \brief Try to mount the disk. If not successful, it create a disk and mount it.

int CST_Disk_Open(const char* szDisk, int nMode, int nAccessMode, int nMaxNumOfFiles, int nDiskSize)
{
	int nResult;
	unsigned int nMountMode;
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);

	// Mount the disk, in case of...
	nMountMode = 0;
	nResult = FS_mount(DirName, &nMountMode);
	if (nResult != FS_OK)
	{
		GTL_Traces_TraceDebug("Cannot mount \"%s\"\n  => create disk\n", DirName);
		// Remove the disk in case of it already exists but in a bad state
		nResult= FS_dskkill(DirName);

		// Create the disk
		nResult = CST_Disk_Create(szDisk, nMode, nAccessMode, nMaxNumOfFiles, nDiskSize);
		if (nResult == FS_OK)
		{
			// Mount the disk
			nResult = FS_mount(DirName, &nMountMode);
			if (nResult != FS_OK)
			{
				GTL_Traces_TraceDebug("Cannot create disk \"%s\"\n", DirName);

				// Delete the created disk
				nResult= FS_dskkill(DirName);
			}
		}
	}

	return nResult;
}

