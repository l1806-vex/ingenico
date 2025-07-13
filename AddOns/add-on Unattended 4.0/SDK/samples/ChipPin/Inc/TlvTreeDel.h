/**
* \file TlvTreeDel.h
* \brief This module contains the functions to perform conversions 
* from DEL to TLV tree or from TLV tree to DEL.
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

#ifndef TLV_TREE_DEL_H
#define TLV_TREE_DEL_H

//! \defgroup Group_TlvTreeDel Conversion functions from TLV tree to DEL or from DEL to TLV tree.
//! @{

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

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
//! \brief This function copies the data elements contained in pDel to the 
//! TLV tree hTlvTree.
//! \param[out] hTlvTree : TLV tree updated with data elements of pDel.
//! \param[in] pDel : input _DEL_ containing a list of data elements to copy
//! in hTlvTree.
//! \return 
//! - TRUE if all the data elements are successfully copied to hTlvTree.
//! - FALSE otherwise.
//===========================================================================
int AddDelValueToTlvTree(TLV_TREE_NODE hTlvTree, const _DEL_* pDel);

//===========================================================================
//! \brief This function copies the data elements contained in the TLV tree 
//! hTlvTree to the _DEL_ pDel.
//! \param[out] pDel : _DEL_ updated with data elements of hTlvTree.
//! \param[in] hTlvTree : input TLV tree containing a list of data elements 
//! to be copied in pDel.
//! \return 
//! - TRUE if all the data elements are successfully copied to pDel.
//! - FALSE otherwise.
//===========================================================================
int AddTlvTreeToDelValue(_DEL_* pDel, const TLV_TREE_NODE hTlvTree);

//===========================================================================
//! \brief This function copies the data elements contained in the TLV tree 
//! hTlvTree to the _DEL_ pDel. All the children of hTlvTree are released
//! after the copy in pDel.
//! \param[out] pDel : _DEL_ updated with data elements of hTlvTree.
//! \param[in] hTlvTree : input TLV tree containing a list of data elements 
//! to be copied in pDel.
//! \return 
//! - TRUE if all the data elements are successfully copied to pDel.
//! - FALSE otherwise.
//===========================================================================
int AddTlvTreeToDelValueEx(_DEL_* pDel, TLV_TREE_NODE hTlvTree);

//===========================================================================
//! \brief This function copies the data elements contained in the TLV tree 
//! hTlvTree to the _DEL_ pDel. This function is used for complex TLV trees.
//! \param[out] pDel : _DEL_ updated with data elements of hTlvTree.
//! \param[in] hTlvTree : input TLV tree containing a list of data elements 
//! to be copied in pDel.
//! \return 
//! - TRUE if all the data elements are successfully copied to pDel.
//! - FALSE otherwise.
//===========================================================================
int AddFullTlvTreeToDelValue(_DEL_* pDel, const TLV_TREE_NODE hTlvTree);

//===========================================================================
//! \brief This function copies the data elements contained in pDel to the 
//! TLV tree pTlvTree.
//! \param[out] pTlvTree : TLV tree updated with data elements of pDel.
//! \param[in] pDel : input _DEL_ containing a list of data elements to copy
//! in pTlvTree.
//! \return 
//! - TRUE if all the data elements are successfully copied to pTlvTree or 
//! if pDel is empty.
//! - FALSE if the TLV tree can't be created or if an error occured during
//! the copy.
//===========================================================================
int CreateTlvTreeFromDel(TLV_TREE_NODE* pTlvTree, const _DEL_* pDel);

//===========================================================================
//! \brief This function builds a candidate list TLV tree from an input _DEL_.
//! The conversion from _DEL_ to TLV tree is not a simple copy because the
//! format of the TLV tree containing a candiddate list is specific.
//! \param[in] pDel : input _DEL_ containing the candidate list
//! \param[out] pOutputTLVTree : TLV tree updated with the candidate list of pDel.
//! \return 
//! - TRUE if all the tags concerning the candidate list are copied.
//! - FALSE if an error occured during the copy.
//===========================================================================
int CreateCandidateListTlvTreefromDel(const _DEL_* pDel, TLV_TREE_NODE* pOutputTLVTree);

//! @}

#endif

