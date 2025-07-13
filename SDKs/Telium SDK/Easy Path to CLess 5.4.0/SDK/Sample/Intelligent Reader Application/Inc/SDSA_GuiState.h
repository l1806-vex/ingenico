/**
 * \file	SDSA_GuiState.h
 * \brief 	Gui state management functions.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2010 Ingenico, rue claude Chappe,\n
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


//! \brief Check in the parameter file if the quick GUI mode is activated or not (if yes the GUI time will be minimized).

void SDSA_GuiState_SetQuickGUIMode (void);



//! \brief Check if the quick GUI mode is activated or not (if yes the GUI time will be minimized).
//!	\return
//!		- TRUE if quick GUI mode is used.
//!		- FALSE else.

int SDSA_GuiState_IsQuickGUIModeActivated (void);



//! \brief Function called to display a defined screen.
//! \param[in] hInputTlvTree Contains the identifier of the screen to be displayed.
//! \return
//!	- \ref SDI_STATUS_OK if the screen correctly displayed.
//!	- \ref SDI_STATUS_INVALID_DATA if provided parameters are not valid.
//!	- \ref SDI_STATUS_MISSING_DATA if there is a missing mandatory parameter (identifier of the screen to be displayed).

int SDSA_GuiState_SetGuiState (const TLV_TREE_NODE hInputTlvTree);



//! \brief Set the application language with the manager language.

void SDSA_UserInterface_SetMerchantLanguage (void);



//! \brief Set the application language with the cardholder language if present, else with the merchant language.
//! \param[in] nKernelIdentifier Kernel identifier that will be called to get the cardholder language.

void SDSA_UserInterface_SetCardholderLanguage (const int nKernelIdentifier);



//! \brief This function set the GUI state of the intelligent reader (displays a screen, sets leds...).
//! \param[in] ulScreenIdentifier Screen identifier.
//! \return
//!	- \ref SDI_STATUS_OK if correctly performed.
//!	- \ref SDI_STATUS_INVALID_PARAMETER if \a ulScreenIdentifier is unknown.

int SDSA_GuiState_DisplayScreen (unsigned long ulScreenIdentifier);
