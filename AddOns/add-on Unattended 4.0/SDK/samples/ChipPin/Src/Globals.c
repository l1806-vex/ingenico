/**
* \file Globals.c
* \brief This module contains global variables.
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

#include "SDK30.h"
#include "del_lib.h"
#include "MyTlvTree.h"

#include "EngineInterfaceLib.h"
#include "_emvdctag_.h"

#include "EmvEngineInterface.h"
#include "Globals.h"

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

T_GLOBAL_BUFFER g_GlobalInterfaceBuffer;

typ_card_data g_CardAnswer;
unsigned char g_OwnTag = 0xDF;

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

