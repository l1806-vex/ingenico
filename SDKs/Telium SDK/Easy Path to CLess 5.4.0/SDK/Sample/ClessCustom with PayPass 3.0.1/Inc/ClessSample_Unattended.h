/**
 * \file	ClessSample_Unattended.h
 * \brief	To manage the specific unattended devices testing.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2012 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __CLESS_SAMPLE_UNATTENDED_H__INCLUDED__
#define __CLESS_SAMPLE_UNATTENDED_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//!	\brief Identify if the Unattended mechanism has to be used.
//!	\return
//!	- \a TRUE if unattended mechanism shall be used.
//!	- \a FALSE if normal processing has to be used.

int ClessSample_Unattended_IsUnattendedMechanism (void);



//! \brief Indicates if UCMC is present or not.
//! \return \a TRUE if UCMC is present, \a FALSE else.

int ClessSample_Unattended_IsUCMCpresent (void);



//! \brief Processing for Unattended environment on the AFTER RESET entry point.
//! \param[in] Application Number.

void ClessSample_Unattended_AfterReset (NO_SEGMENT no);



//! \brief Specific messages displayed for unattended environments.

void ClessSample_Unattended_IdleMessage (void);



//! \brief Indicates if UCMC is loaded and an UPP is connected.
//! \return \a TRUE if UCMC is loaded and UPP is connetced, \a FALSE else.

int ClessSample_Unattended_IsPinPadUPPwithUCMC (void);



//! \brief Indicates if it is an unattended terminal with a display (only the iUP250 for the moment) with the UCM component.
//! \return \a TRUE if UCMC is present is loaded and the terminal is unattended with a screen, \a FALSE.

int ClessSample_Unattended_IsUnattendedTerminalWithDisplayWithUCMC (void);



//! \brief Initialise the Unattended transaction data.

void ClessSample_Unattended_InitTransactionStartData (void);



//! \brief Get unattended mode transaction type.
//! \return The transaction type in unattended mode.

int ClessSample_Unattended_GetTransactionType (void);



//! \brief Get unattended mode Amount, Authorized.
//! \return The Amount, Authorized in unattended mode.

unsigned long ClessSample_Unattended_GetAmountAuth (void);



//! \brief Get unattended mode Amount, Other.
//! \return The Amount, Other in unattended mode.

unsigned long ClessSample_Unattended_GetAmountOther (void);



//!	\brief Output data .
//!	\param[in] pc_x_String String to be output.

void ClessSample_Unattended_PrintDump (const char* pc_x_String);



//! \brief Analyse the command provided by the user on COM0 port, and execute it.
//! \param[in] nCommandLength Length of \a pCommand.
//!	\param[in] pCommand Command itself.

void ClessSample_Unattended_ExecuteCommand (int nCommandLength, char * pCommand);



//! \brief Start the IAM task
//! \return The task number.

int ClessSample_Unattended_StartIamTask(void);




//! \brief Launch the scanning task.
//! \return	OK if task correctly launch, KO else.

int ClessSample_Unattended_LaunchCancelTask (void);



//! \brief Kill the cancel task.

void ClessSample_Unattended_KillCancelTask (void);


#endif // __CLESS_SAMPLE_UNATTENDED_H__INCLUDED__
