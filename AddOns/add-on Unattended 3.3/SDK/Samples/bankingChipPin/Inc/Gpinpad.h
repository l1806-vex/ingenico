/**
* \file Gpinpad.h
* \brief This module contains functions used for pinpad management.
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

#ifndef GPINPAD_H
#define GPINPAD_H

//! \defgroup Group_Gpinpad Pinpad display functions.
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

// Display Aids on Pinpads during Application Selection

//===========================================================================
//! \brief This function displays an AID list on pinpad reader. Then it waits for 
//! selection, or continue key on pinpad reader, or cancel key on terminal keyboard.
//! \param[in] Tab : Array of array containing a list of applications to be 
//! displayed on pinpad.
//! \param[in] number : number of applications to be displayed.
//! \return 
//! - the number of selected application if an application was chosen.
//! - the number of applications to be displayed + 1 if the cancel key was pressed
//! on keyboard.
//===========================================================================
unsigned char Select_on_PPR_pinpad(T_LABEL *Tab, unsigned char number);

//===========================================================================
//! \brief This function displays AIDs on pinpad. Then it waits for 
//! selection, continue or cancel key on pinpad, or cancel key on terminal keyboard.
//! \param[in] Tab_param_appli_name : Array of array containing a list of applications 
//! to be displayed on pinpad.
//! \param[in] nb_appli : number of applications to be displayed.
//! \return 
//! - the number of selected application if an application was chosen.
//! - the number of applications to be displayed + 1 if the cancel key was pressed
//! on the pinpad or on the keyboard.
//===========================================================================
unsigned char Select_on_pinpad (T_LABEL *Tab_param_appli_name , unsigned char nb_appli);

//===========================================================================
//! \brief This function displays the application identifier given as input 
//! parameter and then waits for user confirmation.
//! \param[in] aid : aid to display.
//! \return 
//! - TRUE if the application identifier was confirmed.
//! - FALSE if if the cancel key was pressed on the pinpad or on the keyboard,
//! or if inactivity timeout occured.
//===========================================================================
unsigned char Confirm_on_pinpad(unsigned char *aid);

//! @}

#endif

