/**
 * \file	CST_BlackList.h
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

#ifndef __CST_BLACKLIST_H__INCLUDED__
#define __CST_BLACKLIST_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define C_CLESS_VOID_PAN_SEQ_NUMBER 	0xff


//// Types //////////////////////////////////////////////////////


//// Global variables ///////////////////////////////////////////


//// Functions //////////////////////////////////////////////////

//! \brief Black list initialisation with global variables reset.
//! \return
//!		- Nothing.
void CST_BlackListInit(void);



//! \brief Read a black list file and store it into an internal TLV tree structure.
//! \param[in] szPath file path for the black list file.
//! \param[in] szfile file name for the black list file.
//! \param[out] pTree TLV tree structure.
//! \return
//!		- TRUE if a black list file has been loaded, FALSE else.
int CST_BlackListGetNewFile(const char* szPath, const char* szFile, TLV_TREE_NODE * pTree);


#endif // __CST_BLACKLIST_H__INCLUDED__
