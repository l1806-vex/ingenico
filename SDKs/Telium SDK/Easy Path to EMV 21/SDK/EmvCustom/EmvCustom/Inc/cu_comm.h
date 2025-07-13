/**
* \file cu_comm.h
* \brief This module contains the functions needed for exchanges with the acquirer host.
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

#ifndef CU_COMM_H
#define CU_COMM_H

//! \defgroup Group_cu_comm Host communication management.
//! @{

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function configures the link layer and the ISO8583.
//! \param[in] nTimeout : timeout value.
//! \param[in] nRepetitions : number of repetitions.
//! \param[out] pOutputTLVTree : TLV tree containing the configuration.
//===========================================================================
void EMVCUST_BuildCommConfig_ISO8583(unsigned int nTimeout, unsigned int nRepetitions, TLV_TREE_NODE *pOutputTLVTree);

//===========================================================================
//! \brief This function prepares data for a reversal message.
//! \param[out] pOutputTLVTree : output TLV tree containing reversal data.
//===========================================================================
void EMVCUST_Build_reversal_TLVTree_Iso8583(TLV_TREE_NODE *pOutputTLVTree);

//===========================================================================
//! \brief This function builds a TLV tree with data used for an autorisation.
//! The Data are those described in EMV 4.0, Book 4, 8.1.3.
//! \param[out] pOutputTLVTree : output TLV tree containing the communication 
//! tags.
//===========================================================================
void EMVCUST_BuildISO8583_autho_TLVTree (TLV_TREE_NODE *pOutputTLVTree);

//===========================================================================
//! \brief This function build an output TLV tree containing tags for batch 
//! transfer initialisation and communication tags.
//! \param[in] pInputTLVTree : TLV tree containing tags for batch transfer
//! initialisation.
//! \return TLV tree containing tags  for batch transfer initialisation
//! and communication tags.
//===========================================================================
TLV_TREE_NODE EMVCUST_Build_start_transac_download_TLVTree(TLV_TREE_NODE *pInputTLVTree);

//===========================================================================
//! \brief This function build an output TLV tree containing the financial 
//! tags record and the communication tags.
//! \param[in] pInputTLVTree : TLV tree containing the financial record.
//! \return TLV tree containing the financial tags record and 
//! communication tags.
//===========================================================================
TLV_TREE_NODE EMVCUST_Build_transac_download_TLVTree(TLV_TREE_NODE *pInputTLVTree);

//===========================================================================
//! \brief This function build an output TLV tree containing tags for batch 
//! transfer termination and communication tags.
//! \param[in] pInputTLVTree : TLV tree containing tags for batch transfer
//! termination.
//! \return TLV tree containing tags for batch transfer termination and
//! communication tags.
//===========================================================================
TLV_TREE_NODE EMVCUST_Build_terminate_transac_download_TLVTree(TLV_TREE_NODE *pInputTLVTree);

//===========================================================================
//! \brief This function returns a TLV tree containing the advice tags 
//! record and the communication tags.
//! \param[in] pInputTLVTree : TLV tree containing the advice tags record.
//! \return TLV tree containing the advice tags record and the 
//! communication tags.
//===========================================================================
TLV_TREE_NODE EMVCUST_Build_transac_advice_TLVTree(TLV_TREE_NODE *pInputTLVTree);

//===========================================================================
//! \brief This function builds a TLV tree with data used for an advice.
//! \param[out] pOutputTLVTree : output TLV tree containing the advice message.
//===========================================================================
void EMVCUST_Build_advice_TLVTree_Iso8583(TLV_TREE_NODE *pOutputTLVTree);

//! @}

#endif
