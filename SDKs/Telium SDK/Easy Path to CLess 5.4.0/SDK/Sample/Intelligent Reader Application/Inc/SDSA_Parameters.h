/**
 * \file	SDSA_Parameters.h
 * \brief 	Parameters functions (load, get, erase).
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

//! \brief Function called to load a parameter or a blacklist file.
//! \param[in] hInputTlvTree Contains the parameter or the blacklist file (identified by the value of the tag of the root node).
//! \param[out] hOutputTlvTree Contains the parameters SHA (in the case of a parameter file).
//! \return
//!	- \ref SDI_STATUS_OK if parameters/blacklist correctly loaded.
//!	- \ref SDI_STATUS_INVALID_DATA if provided data are not valid (is not a parameters/blacklist file).

int SDSA_Parameters_LoadParameters (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);



//! \brief Function called to get the application parameters or only get the parameter calculated checksum.
//! \param[in] hInputTlvTree Not used.
//! \param[out] hOutputTlvTree Filled with the application parameters.
//! \return
//!	- \ref SDI_STATUS_OK if parameters correctly loaded.
//!	- \ref SDI_STATUS_KO if an error occured.
//!	- \ref SDI_STATUS_NO_PARAMETER if there is no parameter to get.

int SDSA_Parameters_GetParameters (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree);



//! \brief Function called to erase the parameters.
//! \return
//!	- \ref SDI_STATUS_OK if parameters correctly loaded.
//!	- \ref SDI_STATUS_KO if an error occured.

int SDSA_Parameters_EraseParameters (void);
