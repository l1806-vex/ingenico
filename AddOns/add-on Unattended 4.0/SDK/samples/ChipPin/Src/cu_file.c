/**
* \file cu_file.c
* \brief This module contains the functions allowing the saving of global variables, in
* case of power failure. The maximum allowed size for saving is 8 Ko.
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
#include "_emvdctag_.h"
#include "cu_term.h"
#include "MyTlvTree.h"
#include "cu_batch.h"
#define FILE_H
#include "cu_file.h"

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

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================

void FILE_Save_Restore_global_RAM_data(void)
{
	int result;

	// Request save / recovery of global data 
	// RegisterPowerFailure is obsolete. You have to remove the call of it in your code 
	result = 1; //RegisterPowerFailure ((char *) LABEL_GLOBAL_DATA, (unsigned char *)&S_GlobalRamData,
				//					sizeof(STRUCT_GLOBAL_RAM_DATA));

#ifdef _SIMULPC_
	result = 0;
#endif
	if( result != 1 )
	{
		memset (&S_GlobalRamData,0,sizeof(STRUCT_GLOBAL_RAM_DATA));
	}
}


