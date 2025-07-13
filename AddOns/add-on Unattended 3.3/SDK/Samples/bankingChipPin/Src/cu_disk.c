/**
* \file cu_disk.c
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

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "SDK30.H"
#include "cu_term.h"
#include "cu_entry.h"
#include "cu_disk.h"

//! \addtogroup Group_cu_disk
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

char Label_Disk_Name[DISK_NAME_SIZE];

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
void CUDISK_Get_Disk_Name(char* ptDiskName)
{
	memcpy(ptDiskName, Label_Disk_Name, sizeof(Label_Disk_Name));
}

//===========================================================================
int CUDISK_CreateDisk (void)
{
	int               Retour;
	unsigned long     DiskSize;
	S_FS_PARAM_CREATE ParamCreat;
	char              FilePath_L[33];

	ParamCreat.Mode         = FS_WRITEONCE;
	ParamCreat.IdentZone    = FS_WO_ZONE_DATA;

	memclr(Label_Disk_Name,sizeof(Label_Disk_Name));
	sprintf(Label_Disk_Name,"%s%02x",LABEL_DISK,CustApplicationNumber);

	strcpy(ParamCreat.Label, Label_Disk_Name);
	ParamCreat.AccessMode   = FS_WRTMOD;
	ParamCreat.NbFichierMax = 20;
	DiskSize              = DISK_SIZE;

	sprintf(FilePath_L,"/%s",Label_Disk_Name);
	Retour = FS_mount (FilePath_L,&ParamCreat.Mode);
	if (Retour != FS_OK)
	{
		Retour=FS_dskcreate(&ParamCreat,&DiskSize);
	}
	return (Retour);
}

//===========================================================================
int CUDISK_UnmountDisk (void)
{
	char FilePath_L[33];
	int ret;

	// Unmount volume
	memclr(FilePath_L,sizeof(FilePath_L));
	sprintf(FilePath_L, "/%s",Label_Disk_Name);

	// Unmount volume
	ret = FS_unmount(FilePath_L);

	return (ret);
}

//! @}

