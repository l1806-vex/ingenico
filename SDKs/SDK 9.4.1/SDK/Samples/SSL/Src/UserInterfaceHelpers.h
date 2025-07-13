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
// Description: User Interface function set. Miscellaneous.
//      
// Author:      V.GOMES
// Version:     1.0
// Date:        2005/07/22 
//
//-------------------------------------------------------------------
#ifndef __USER_INTERFACE_HELPERS_H__
#define __USER_INTERFACE_HELPERS_H__

// Macros & preprocessor definitions.
//-------------------------------------------------------------------
#define __FALSE__		0
#define __TRUE__		1

#define __ENTER_KEY		-1
#define __BACK_KEY		-2
#define __EXIT_KEY		-3

#define __NO_BANNER		1
#define __ONE_BANNER	2
#define __ALL_BANNERS	3

#define __MODE_NOCASE		0
#define __MODE_LOWERCASE	1
#define __MODE_UPPERCASE	2

// Functions.
//-------------------------------------------------------------------
void DisplayText( const char *szInput, int x, int y, int index, int bErase, int bInvert  );

void DisplayScreen( const char *szLine1, const char *szLine2 );

int HelperManageInput( char *szLabel, int xLabel, int yLabel,
					   char *szInput, int xInput, int yInput, 
					   int nMaxLen, int bNumerical, int nMode, int nTimeout );


int HelperDisplayMenu( const char* szTitle, int nDefaultChoice,
					   int nItems, const char**Items,
					   int nBanners );

int HelperDisplayChoices( const char* szTitle, int nDefaultChoice,
						  int nItems, const char* Items[],
					      int nBanners );

int HelperDisplaySelection( char *szLabel, int xLabel, int yLabel, 
							int xInput, int yInput,
							int nItems, const char **Items,
							int nBanners, int nTimeout, int *pnSelected );


int PrintText( char *szText, int bClose );


//-------------------------------------------------------------------
//-------------------------------------------------------------------
#endif // __USER_INTERFACE_HELPERS_H__
