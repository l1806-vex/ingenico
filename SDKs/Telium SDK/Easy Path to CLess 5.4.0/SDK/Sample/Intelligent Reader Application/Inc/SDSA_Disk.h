/**
 * \file	SDSA_Disk.h
 * \brief 	Manages the application Disk access.
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

#ifndef __SDSA_DISK_H__INCLUDED__
#define __SDSA_DISK_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define FILE_DISK_LABEL						"CLESSM"
#define FILE_MODE_LABEL                     "CLESS_M"

#define FILE_DISK_MODE						FS_WRITEONCE
#define FILE_DISK_ACCESS_MODE				FS_WRTMOD
#define FILE_DISK_MAX_NUM_OF_FILES			20
#define FILE_DISK_SIZE						102400	// 100 Kb


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Mount a disk from the flash.

int SDSA_Disk_Mount(const char* szDisk);



//! \brief Unmount a disk.

int SDSA_Disk_Unmount(const char* szDisk);



//! \brief Create a disk in the flash (with given parameters).

int SDSA_Disk_Create(const char* szDisk, int nMode, int nAccessMode, int nMaxNumOfFiles, int nDiskSize);



//! \brief Delete a disk in the flash.

int SDSA_Disk_Kill(const char* szDisk);



//! \brief Try to mount the disk. If not successful, it create a disk and mount it.

int SDSA_Disk_Open(const char* szDisk, int nMode, int nAccessMode, int nMaxNumOfFiles, int nDiskSize);

#endif // __SDSA_DISK_H__INCLUDED__
