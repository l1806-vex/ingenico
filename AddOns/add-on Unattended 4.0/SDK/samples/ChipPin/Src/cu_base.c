/**
* \file cu_base.c
* \brief This module contains the functions needed for data base management.
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
#include "TlvTree.h"
#include "del_lib.h"
#include "convert.h"
#include "cu_base.h"
#include "def_tag.h"
#include "cu_mess.h"
#include "cu_entry.h"
#include "gestion_param.h"
#include "cu_term.h"
#include "cu_param.h"

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

/* ======================================================================== */
/* Extern function declarations                                             */
/* ======================================================================== */

extern unsigned long PAR_SelectFatherAID(DataElementExt data);

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
unsigned short CUDB_Select_AID_Parameters(unsigned char lg_aid, unsigned char *Aid_value)
{
	unsigned short Result = DB_OK;
	unsigned long  ul_l_AIDMark, ul_l_ICSMark;
	unsigned short res;
	unsigned char lg_aidint;
	unsigned char Aid_valueint[20];

	DataElementExt data;
	lg_aidint =lg_aid;
	memcpy(Aid_valueint,Aid_value,lg_aidint);
	do
	{
		data.elt.tag = TAG_AID_TERMINAL;
		data.elt.length = lg_aidint;
		data.elt.ptValue = Aid_valueint;

		ul_l_AIDMark = PAR_SelectFatherAID(data);
		
		if (ul_l_AIDMark == 0)
	    {
		   lg_aidint =lg_aidint-1;
		   Aid_valueint[0] =Aid_valueint[0]-1;
		}
	}while ((lg_aidint>=6)&&(ul_l_AIDMark==0));
	if (ul_l_AIDMark == 0)
	{
		Result = (unsigned short)DB_KO;
	}
	else
	{
		// Process ICS mark in relation with AID marq
		CUPAR_MemorizeAdditionnalAID(ul_l_AIDMark);

		ul_l_ICSMark = ul_l_AIDMark - C_TAG_AID + C_TAG_ICS + 1;

		// This marq is not mandatory so the tag selection may be bad
		res = PAR_SelectMark(ul_l_ICSMark, C_TREE_ALL); 

		if (res == 0)
			CUPAR_MemorizeAdditionnalICS(ul_l_ICSMark);
	}

	return (Result);
}

//===========================================================================
int CUDB_StoreTLVTree (TLV_TREE_NODE *phTLVTree)
{
	TLV_TREE_NODE hNode;
	DataElementExt ext_elt;
	int Result,cr_put;

	// Check input parameter
	if (*phTLVTree == NULL)
	{
		return DB_KO;
	}

	// For each tag in the TlvTree
	Result = DB_OK;
	hNode = TlvTree_GetFirstChild(*phTLVTree);

	while(hNode != NULL)
	{
		// Get the tag 
		ext_elt.elt.tag = TlvTree_GetTag(hNode);

		// Get the length 
		ext_elt.elt.length = TlvTree_GetLength(hNode);

		// Get the value 
		ext_elt.elt.ptValue = TlvTree_GetData(hNode);

		// Add the node in the database.
		cr_put = PAR_SetParameter(ext_elt.elt.tag, ext_elt);

		if (cr_put != 1)
		{
			Result = DB_KO;
		}

		// Get the next node
		hNode = TlvTree_GetNext(hNode);
	}

	return Result;
}

//===========================================================================
void CUDB_GetParamPINCode (short *TO_inter_car, short *TO_first_car, unsigned long * fct_ksu)
{
	DataElement elt;
	unsigned short found;

	*TO_inter_car = 0;
	*TO_first_car = 0;
	*fct_ksu = SCH_NO_FCT;

	// Get data from TLVTree 
	found = PAR_ReadParameter(TAG_TIME_OUT_PIN_CODE, (DataElementExt *)&elt);
	if (found)
	{
		*TO_first_car = CharToShort(elt.ptValue);
	}
	else *TO_first_car = 6000;

	// Get data from TLVTree
	found = PAR_ReadParameter(TAG_TIME_OUT_INTER_CAR, (DataElementExt *)&elt);
	if (found)
	{
		*TO_inter_car = CharToShort(elt.ptValue);
	}
	else *TO_inter_car = 2000;

	// Get data from TLVTree
	found = PAR_ReadParameter(TAG_SCHEMAS_KSU, (DataElementExt *)&elt);
	if (found)
	{
		memcpy((unsigned char *)fct_ksu, elt.ptValue, elt.length);
	}
	else *fct_ksu = TRUE;
}

//===========================================================================
void CUDB_Get_cardholder_language (unsigned short *lg_code)
{
	int cr;
	DataElementExt data;

	// Default value for lg_code if card holder language isn't found.
	*lg_code = PSQ_Give_Language();

	// Get data from pTreeAppli
	cr = PAR_ReadParameter(TAG_EG_CARDHOLDER_LANGUAGE, &data);

	if ((cr) && ( *lg_code < C_NBLANGMERCH ))
	{
		CUMESS_GiveIso639Code(data.elt.ptValue, lg_code);
	}
}

