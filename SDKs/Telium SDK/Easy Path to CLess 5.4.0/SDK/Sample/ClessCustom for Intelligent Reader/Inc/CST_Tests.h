/**
 * \file	CST_Test.h
 * \brief 	This file allows to test each functions available in the SDI DLL Interface (System functions and Payment functions).
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

#ifndef __CST_TESTS_H__INCLUDED__
#define __CST_TESTS_H__INCLUDED__


//// Functions //////////////////////////////////////////////////

//! \brief Gives transaction type.
//! \return The transaction type.
//! \note This function can be called after transaction type has been populated.

unsigned char CST_Tests_GiveTransactionType(void);



//! \brief Gives the message to display the amount value.

char *CST_Tests_GiveAmountMessage(void);



//! \brief Main menu that allows to test each System and Payment functions of the intelligent reader.

int CST_Tests_ManageMenu(void);



//! \brief Allows to test SDI_Payment_DoTransaction() function.

void CST_Tests_DoTransaction (void);



//! \brief Allows to test SDI_Payment_EraseParams() function.

int CST_Tests_EraseParameters (void);



//! \brief Copy a TLV Tree in a data structure.
//! \param[in] hTlvTree TLV Tree that contains data to had to the data structure.
//! \param[out] pDataStruct Data buffer that will contain the copied data.

void CopyTlvTreeToDataStruct (TLV_TREE_NODE hTlvTree, T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Copy the data in a TLV Tree.
//! \param[in] pDataStruct Data buffer that contains data to add in the TLV Tree.
//! \param[out] hOutputTlvTree Output TLV Tree containing the data.

void CopyDataStructInTLVTree (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree);



//! \brief Display the screen given in parameter.
//! \param[in] ulScreenToDisplay Screen identifier.

int CST_DisplayScreen (const unsigned long ulScreenToDisplay);



//! \brief Try to reconnect when a connection error occurs.

void CST_ReconnectionProcess (void);


#endif // __CST_TESTS_H__INCLUDED__
