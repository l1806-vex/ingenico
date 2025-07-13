/**
* \file servcomm_TlvTree.h
* \brief This module contains the TlvTree interface with a communication component.
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

#ifndef _SERVCOMM_TLVTREE_H_
#define _SERVCOMM_TLVTREE_H_

//! \defgroup Group_servcomm Interface with communication component.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//! \addtogroup CoServ
//! @{

//===========================================================================
//! \brief Sets the application type of the communication component.
//! \param[in] usAppType the application type.
//===========================================================================
void COMM_Set_Application_Type(unsigned short usAppType);

//===========================================================================
//! \brief Retreives the application type of the communication component.
//! \return The application type.
//===========================================================================
unsigned short COMM_Get_Application_Type(void);


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


//===========================================================================
//! \brief Retreives information about the communication protocol.
//! \param[in] hInputTLVTree a TLV tree containing the configuration identifier 
//! \ref TAG_COMM_CONFIG_ID (optional).
//! \return A TLV tree containing information about the communication protocol.
//! \see
//! - SMO/SPE-0026.
//! - The documentation of the component.
//===========================================================================
TLV_TREE_NODE COMM_Get_Protocol_Info_TlvTree(const TLV_TREE_NODE hInputTLVTree);

//===========================================================================
//! \brief Configures the communication component.
//! \param[in] hInputTLVTree a TLV tree containing the configuration of the component.
//! \return A TLV tree containing :
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The communication identifier \ref TAG_COMM_CONFIG_ID (optional).
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - The documentation of the component.
//===========================================================================
TLV_TREE_NODE COMM_Configure_TlvTree(const TLV_TREE_NODE hInputTLVTree);

//===========================================================================
//! \brief Connects to the host.
//! \param[in] hInputTLVTree a TLV tree containing :
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! \return A TLV tree containing :
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.
//===========================================================================
TLV_TREE_NODE COMM_Connect_TlvTree(const TLV_TREE_NODE hInputTLVTree);

//===========================================================================
//! \brief Disconnects from the host.
//! \param[in] hInputTLVTree a TLV tree containing :
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! \return A TLV tree containing :
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.
//===========================================================================
TLV_TREE_NODE COMM_Disconnect_TlvTree(const TLV_TREE_NODE hInputTLVTree);

//===========================================================================
//! \brief Sends a message and waits for an answer.
//! \param[in] hInputTLVTree a TLV tree containing :
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! - The message type \ref TAG_COMM_MESSAGE_TYPE.
//! - The message data (see SMO/SPE-0026).
//! \return A TLV tree containing :
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! - The received message type \ref TAG_COMM_MESSAGE_TYPE.
//! - The received message data (see SMO/SPE-0026).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.
//===========================================================================
TLV_TREE_NODE COMM_Send_And_Receive_Message_TlvTree(const TLV_TREE_NODE hInputTLVTree);

//===========================================================================
//! \brief Sends a message.
//! \param[in] hInputTLVTree a TLV tree containing :
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! - The message type \ref TAG_COMM_MESSAGE_TYPE.
//! - The message data (see SMO/SPE-0026).
//! \return A TLV tree containing :
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.
//===========================================================================
TLV_TREE_NODE COMM_Send_Message_TlvTree(const TLV_TREE_NODE hInputTLVTree);

//===========================================================================
//! \brief Retreives the status of the component.
//! \param[in] hInputTLVTree a TLV tree containing :
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! \return A TLV tree containing :
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The communication status \ref TAG_COMM_CONNECTION_STATUS.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.
//===========================================================================
TLV_TREE_NODE COMM_Get_Status_TlvTree(const TLV_TREE_NODE hInputTLVTree);

//===========================================================================
//! \brief Retreives the data of an asynchronously received message.
//! \param[in] hInputTLVTree a TLV tree containing :
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! \return A TLV tree containing :
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! - The received message type \ref TAG_COMM_MESSAGE_TYPE.
//! - The received message data (see SMO/SPE-0026).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.
//===========================================================================
TLV_TREE_NODE COMM_Read_Message_TlvTree(const TLV_TREE_NODE hInputTLVTree);

//===========================================================================
//! \brief Aborts a running asynchronous operation.
//! \param[in] hInputTLVTree a TLV tree containing :
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! \return A TLV tree containing :
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.
//===========================================================================
TLV_TREE_NODE COMM_Abort_TlvTree(const TLV_TREE_NODE hInputTLVTree);

//===========================================================================
//! \brief Waits for an incoming message.
//! \param[in] hInputTLVTree a TLV tree containing :
//! - The configuration of the component \ref TAG_COMM_CONFIG_ID (optional).
//! - The calling mode \ref TAG_COMM_CALLING_MODE (optional).
//! \return A TLV tree containing :
//! - The status code \ref TAG_COMM_STATUS_CODE.
//! - The link layer status code \ref TAG_COMM_LINK_LAYER_STATUS (optional).
//! - The received message type \ref TAG_COMM_MESSAGE_TYPE.
//! - The received message data (see SMO/SPE-0026).
//! \see
//! - SMO/SPE-0026.
//! - SMO/SPE-0068.
//===========================================================================
TLV_TREE_NODE COMM_Receive_Message_TlvTree(const TLV_TREE_NODE hInputTLVTree);

//! @}

//! @}

#endif // _COMM_H_
