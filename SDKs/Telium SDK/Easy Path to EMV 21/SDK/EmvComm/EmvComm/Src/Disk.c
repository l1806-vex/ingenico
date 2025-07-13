//! \file
//! Module that manages the terminal flash file management.
//
/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "Disk.h"

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

int Disk_Mount(const char* szDisk)
{
	unsigned int nMountMode;
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);

	// Mount the disk
	nMountMode = 0;
	return FS_mount(DirName, &nMountMode);
}

int Disk_Unmount(const char* szDisk)
{
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);
	return FS_unmount(DirName);
}

int Disk_Create(const char* szDisk, int nMode, int nAccessMode, int nMaxNumOfFiles, int nZone, unsigned long ulDiskSize)
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
	Params.IdentZone = nZone;
	ulSize = ulDiskSize;

	// Create the disk
	return FS_dskcreate(&Params, &ulSize);
}

int Disk_Kill(const char* szDisk)
{
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);
	return FS_dskkill(DirName);
}

int Disk_Open(const char* szDisk, int nMode, int nAccessMode, int nMaxNumOfFiles, int nZone, unsigned long ulDiskSize)
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
		// Remove the disk in case of it already exists but in a bad state
		nResult= FS_dskkill(DirName);

		// Create the disk
		nResult = Disk_Create(szDisk, nMode, nAccessMode, nMaxNumOfFiles, nZone, ulDiskSize);
		if (nResult == FS_OK)
		{
			// Mount the disk
			nResult = FS_mount(DirName, &nMountMode);
			if (nResult != FS_OK)
			{
				// Delete the created disk
				nResult= FS_dskkill(DirName);
			}
		}
	}

	return nResult;
}
