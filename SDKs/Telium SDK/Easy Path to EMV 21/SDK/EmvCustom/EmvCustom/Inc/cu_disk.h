/**
* \file cu_disk.h
* \brief This module contains the functions needed for disk management.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

#ifndef CU_DISK_H
#define CU_DISK_H

//! \defgroup Group_cu_disk Disk management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */
#define DISK_NAME_SIZE					33			//!< Size of disk name.

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function gets the value of the global variable Label_Disk_Name.
//! \param[out] ptDiskName : value of the global variable Label_Disk_Name.
//===========================================================================
void CUDISK_Get_Disk_Name(char* ptDiskName);

//===========================================================================
//! \brief This function creates a volume.
//! \return
//! - FS_OK if successfull, volume ready to be used.
//! - FS_NAMEUSED : volume name already used.
//! - FS_NOMEM no more space available in Flash.
//! - FS_KO other errors.
//===========================================================================
int CUDISK_CreateDisk (void);

//===========================================================================
//! \brief This function unmounts a volume.
//! \return
//! - FS_OK If successful.
//! - FS_KO other errors.
//! - FS_NOACCESS if application does not have the access rights.
//! - FS_FILEUSED if files are still open.
//===========================================================================
int CUDISK_UnmountDisk (void);

//! @}

#endif
