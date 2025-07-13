/**
* \file cu_base.h
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

#ifndef CU_BASE_H
#define CU_BASE_H

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "_emvdctag_.h"
#include "appel.h"

//! \defgroup Group_cu_base Data base management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define NB_AID_MAX                  5			//!< Maximun number of AID.

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

//! \brief Definition of Application Identifier structure for data base
typedef struct
{
	unsigned long len_Aid;						//!< Application identifier length.
	unsigned char AID [LEN_AID+1];				//!< Application identifier value.
	unsigned char ASI;							//!< Application selection identifier.
} T_CUDB_AID_Elt ;


/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */


/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function activates the AID parameter given as input parameter.
//! \param[in] lg_aid : Application identifier length.
//! \param[in] Aid_value : Application identifier value.
//! \return 
//! - DB_OK = 0 if AID mark has been found and activated.
//! - DB_KO = -4 otherwise.
//===========================================================================
unsigned short CUDB_Select_AID_Parameters (unsigned char lg_aid, unsigned char *Aid_value);


//===========================================================================
//! \brief This function stores a TLV tree in the parameter database.
//! \param[in] phTLVTree : Tree to store in the data base.
//! \return 
//! - DB_OK = 0 if all the elements of the tree are stored.
//! - DB_KO = -4 otherwise.
//===========================================================================
extern int CUDB_StoreTLVTree (TLV_TREE_NODE *phTLVTree);

//===========================================================================
//! \brief This function gets the cordholder language for this transaction.
//! \param[out] lg_code : language code, in iso639 format.
//===========================================================================
void CUDB_Get_cardholder_language (unsigned short *lg_code);

//===========================================================================
//! \brief This function gets two time out to the enter pin and the functions 
//! made by KSU Schemes.
//! \param[out] TO_inter_car : inter character time out.
//! \param[out] TO_first_car : first character time out.
//! \param[out] fct_ksu : functions managed by KSU (TAG_SCHEMAS_KSU).
//===========================================================================
void CUDB_GetParamPINCode (short *TO_inter_car, short *TO_first_car, unsigned long * fct_ksu);

//! @}

#endif


