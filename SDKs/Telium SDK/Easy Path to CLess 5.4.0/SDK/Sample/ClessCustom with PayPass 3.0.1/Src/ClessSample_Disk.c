//! \file
//! Module that manages the terminal flash file management.
//
/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


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



//===============================================================
// Function name	:	ClessSample_Disk_Mount
// Description		:	mount a disk from the flash

int ClessSample_Disk_Mount(const char* szDisk)
{
	unsigned int nMountMode;
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);

	// Mount the disk
	nMountMode = 0;
	return FS_mount(DirName, &nMountMode);
}



//===============================================================
// Function name	:	ClessSample_Disk_Unmount
// Description		:	unmount a disk

int ClessSample_Disk_Unmount(const char* szDisk)
{
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);
	return FS_unmount(DirName);
}



//===============================================================
// Function name	:	ClessSample_Disk_Create
// Description		:	create a disk in the flash (with given parameters)

int ClessSample_Disk_Create(const char* szDisk, int nMode, int nAccessMode, int nMaxNumOfFiles, int nDiskSize)
{
	S_FS_PARAM_CREATE Params;
	unsigned long ulSize;
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);

	// Set the disk parameters
	memset(&Params, 0, sizeof(Params));

	if (strlen(szDisk) < FS_DISKNAMESIZE)						// FS_DISKNAMESIZE is the length of Params.Label
		strncpy(Params.Label, szDisk, sizeof(Params.Label));

	Params.Mode = nMode;
	Params.AccessMode = nAccessMode;
	Params.NbFichierMax = nMaxNumOfFiles;
	Params.IdentZone = FS_WO_ZONE_DATA;
	ulSize = (unsigned long)nDiskSize;

	// Create the disk
	return FS_dskcreate(&Params, &ulSize);
}



//===============================================================
// Function name	:	ClessSample_Disk_Kill
// Description		:	Delete a disk in the flash

int ClessSample_Disk_Kill(const char* szDisk)
{
	char DirName[1 + FS_DISKNAMESIZE + 1];

	sprintf(DirName, "/%s", szDisk);
	return FS_dskkill(DirName);
}




//===============================================================
// Function name	:	ClessSample_Disk_Open
// Description		:	Try to mount the disk. If not successful, 
//						it create a disk and mount it.

int ClessSample_Disk_Open(const char* szDisk, int nMode, int nAccessMode, int nMaxNumOfFiles, int nDiskSize)
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
		GTL_Traces_DiagnosticText("Cannot mount \"%s\"\n  => create disk\n", DirName);
		// Remove the disk in case of it already exists but in a bad state
		nResult= FS_dskkill(DirName);

		// Create the disk
		nResult = ClessSample_Disk_Create(szDisk, nMode, nAccessMode, nMaxNumOfFiles, nDiskSize);
		if (nResult == FS_OK)
		{
			// Mount the disk
			nResult = FS_mount(DirName, &nMountMode);
			if (nResult != FS_OK)
			{
				GTL_Traces_DiagnosticText("Cannot create disk \"%s\"\n", DirName);

				// Delete the created disk
				nResult= FS_dskkill(DirName);
			}
		}
	}

	return nResult;
}

//===============================================================
// Function name	:	ClessSample_Disk_Open_MyDisk
// Description		:	Try to mount the application disk. If not successful, 
//						it create the disk and mount it.

int ClessSample_Disk_Open_MyDisk(void)
{
	return ClessSample_Disk_Open(FILE_DISK_LABEL, FILE_DISK_MODE, FILE_DISK_ACCESS_MODE, FILE_DISK_MAX_NUM_OF_FILES, FILE_DISK_SIZE);
}
