//-------------------------------------------------------------------
//
// Copyright (c) 2005 Sagem Monetel SA, rue claude Chappe,
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

#define ERROR_UNKNOWN_HOST		-1
#define ERROR_SOCKET_FAILED		-2
#define ERROR_CONNECT_FAILED	-3
#define ERROR_SEND_FAILED		-4


// Functions
//-------------------------------------------------------------------

void PrintNetworkInfos(void);

int LaunchServerHTTP(void);

// Return the number of bytes read.
// Or a negative error code.
//
int PerformConnectionHTTP( const char *szHostName, unsigned int nPort, const char *szWebPage );

//-------------------------------------------------------------------
//-------------------------------------------------------------------
#endif // __COMMUNICATION_H__
