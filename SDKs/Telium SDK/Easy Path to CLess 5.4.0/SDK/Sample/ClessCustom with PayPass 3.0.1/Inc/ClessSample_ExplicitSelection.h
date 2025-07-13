/**
 * \file	ClessSAmple_ExplicitSelection.h
 * \brief 	Perform a transaction in explicit selection (without interaction with the Manager).
 *
 * \author	Ingenico
 * \author	Copyright (c) 2008 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/


/////////////////////////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Global data definitions ////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////////////////////////

//! \brief Function called for to perform explicit transaction (card detection and application selection).
//! \param[in] bUseParameterFileForTransactionData \a TRUE if transaction is started using the parameter file, \a FALSE if transaction is started with operator assistance (transaction type choice, amount entry, etc).

void ClessSample_ExplicitSelection_Process (const int bUseParameterFileForTransactionData);
