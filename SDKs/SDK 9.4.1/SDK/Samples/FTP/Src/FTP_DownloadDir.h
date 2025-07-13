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

#ifndef __FTP_DOWNLOAD_DIR_H__
#define __FTP_DOWNLOAD_DIR_H__

//--------------------------------------------------------------------------
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
//
// Return :
//		Handle on the local RAM disk.
//		NULL in case of failure.
// 
//--------------------------------------------------------------------------
RAMDISK_HANDLE iFtp_download_dir( const char *szAddress, 
								  unsigned int nPort, 
								  const char *szLogin, 
								  const char *szPassword, 
								  const char *szDirectory,
								  const char *szLocalDiskName,
								  unsigned int nLocalDiskSize );

//-------------------------------------------------------------------
//-------------------------------------------------------------------
#endif // __FTP_DOWNLOAD_DIR_H__

