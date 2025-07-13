/**
 * \file	SDSA_BlackList.h
 * \brief	Module that manages the black list.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __SDSA_BLACKLIST_H__INCLUDED__
#define __SDSA_BLACKLIST_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define C_CLESS_VOID_PAN_SEQ_NUMBER 	0xff


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Black list initialisation with global variables reset.

void SDSA_BlackListInit(void);



//! \brief Delete the black list.

void SDSA_BlackListDelete(void);



//! \brief Load a black list file in memory.
//! \return
//!		- TRUE if a black list file has been loaded, FALSE else.

int SDSA_BlackListLoad(void);



//! \brief Save a black list in a default file.
//! \return
//!		- TRUE if the black list file has been correctly updated, FALSE else.

int SDSA_BlackListSave(void);



//! \brief Check if a Pan + PanSeqNumber is in the black list.
//! This function must be used with an ASCII PAN number and PAN Sequence Number.
//! \param[in] szPan card Pan number.
//! \param[in] nPanSeqNumber card Pan Sequence Number.
//! \return
//!		- TRUE if the Pan + PanSeqNumber is in the Black List, FALSE else.

int SDSA_BlackListIsPanAscii(const char* szPan, int nPanSeqNumber);



//! \brief Check if a Pan + PanSeqNumber is in the black list.
//! \param[in] szPan card Pan number.
//! \param[in] nPanSeqNumber card Pan Sequence Number.
//! \return
//!		- TRUE if the Pan + PanSeqNumber is in the Black List, FALSE else.

int SDSA_BlackListIsPan(int nLength, const unsigned char* pPan, int nPanSeqNumber);



//! \brief Check if a Black list has been loaded.
//! \return
//!		- TRUE if a black list with at least one element is loaded.

int SDSA_IsBlackListPresent(void);



//! \brief Load a black list received from TLVTree in memory.
//! \param[in] hInputTlvTree TLVTree that contains the blacklist.
//! \return
//!		- TRUE if a black list has been loaded, FALSE else.

int SDSA_BlackList_LoadNewBlackList(const TLV_TREE_NODE hInputTlvTree);

#endif // __SDSA_BLACKLIST_H__INCLUDED__
