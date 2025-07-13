/**
 * \file	CST_TlvTreeDel.h
 * \brief 	Module that manages Tlv Tree and DEL.
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

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

int AddDelValueToTlvTree(TLV_TREE_NODE hTlvTree, const _DEL_* pDel);


int AddTlvTreeToDelValue(_DEL_* pDel, const TLV_TREE_NODE hTlvTree);


int AddTlvTreeToDelValueEx(_DEL_* pDel, TLV_TREE_NODE hTlvTree);


int AddFullTlvTreeToDelValue(_DEL_* pDel, const TLV_TREE_NODE hTlvTree);


int CreateTlvTreeFromDel(TLV_TREE_NODE* pTlvTree, const _DEL_* pDel);


//! \brief Release the given TlvTree and then set the pointer to NULL

void TlvTree_ReleaseEx(TLV_TREE_NODE* pTlvTree);
