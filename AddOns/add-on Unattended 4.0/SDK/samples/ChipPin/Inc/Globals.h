/**
* \file Globals.h
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
#include "TagOS.h"

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define g_TheProcessStep			g_GlobalInterfaceBuffer.m_ProcessStep
#define g_TheCustTlvTreeService		g_GlobalInterfaceBuffer.m_CustTlvTreeService

#define NOT_SUPPORTED				(0)
#define CONSTRUCTED					(1)
#define ANALYSED					(2)

#define MAX_CARD_DATA_OUT			(262)

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

typedef union
{
	StructProcessStep m_ProcessStep;
	I_CUST_TLVTREE_SERVICE m_CustTlvTreeService;
} T_GLOBAL_BUFFER;

typedef struct
{
	unsigned short Card_status;
	unsigned short Length_Data;
	unsigned char Data[MAX_CARD_DATA_OUT];
} typ_card_data;

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

extern T_GLOBAL_BUFFER g_GlobalInterfaceBuffer;

extern typ_card_data g_CardAnswer;
extern unsigned char g_OwnTag;

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

