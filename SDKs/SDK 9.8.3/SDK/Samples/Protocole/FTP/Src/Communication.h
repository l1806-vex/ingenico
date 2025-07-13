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
// Description: Communication utilities module.
//      
// Author:      V.GOMES
// Version:     1.0
// Date:        2005/07/22 
//
//-------------------------------------------------------------------
#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__


// Macros & preprocessor definitions
//-------------------------------------------------------------------
#define __FALSE__		0
#define __TRUE__		1


// Functions
//-------------------------------------------------------------------

int PerformConnectionGPRS( char *szAPN, char *szLogin, char *szPassword );

int PerformConnectionFTP( const char *szHostName, unsigned int nPort, 
						  const char *szLogin, const char *szPassword,
						  const char *szDirectory, 
						  const char *szDiskName, unsigned int nDiskSize );

//-------------------------------------------------------------------
//-------------------------------------------------------------------
#endif // __COMMUNICATION_H__
