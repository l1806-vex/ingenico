/**
 * \file	SDSA_Parameters.c
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

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDSA_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definition /////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Function called to load a parameter or a blacklist file.
//! \param[in] hInputTlvTree Contains the parameter or the blacklist file (identified by the value of the tag of the root node).
//! \param[out] hOutputTlvTree Contains the parameters SHA (in the case of a parameter file).
//! \return
//!	- \ref SDI_STATUS_OK if parameters/blacklist correctly loaded.
//!	- \ref SDI_STATUS_INVALID_DATA if provided data are not valid (is not a parameters/blacklist file).

int SDSA_Parameters_LoadParameters (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	unsigned int nNodeTag;
	int nCRCLength;
	unsigned char * pSha;

	GTL_Traces_TraceDebug ("SDSA_Parameters_LoadParameters");
	
	// Get the tag of the root node
	nNodeTag = TlvTree_GetTag(hInputTlvTree);

	if(nNodeTag == TAG_SDSA_PARAMETER_FILE_NODE)
	{
		// The input TLVTree contains a parameter file

		// Copy the given parameters in the current parameters
		SDSA_Parameters_InitParameters(&pTreeCurrentParam);

		pTreeCurrentParam = TlvTree_Copy(hInputTlvTree);

		// Set TLVTree parameters in a save file
		if (SDSA_Parameters_SaveParam (pTreeCurrentParam) != 0)
			GTL_Traces_TraceDebug ("SDSA_Parameters_LoadParameters : SDSA_Parameters_SaveParam Error");

		SDSA_Parameters_CreateSupportedCertificateListForKernel (pTreeCurrentParam, DEFAULT_EP_KERNEL_PAYPASS);
		SDSA_Parameters_CreateSupportedCertificateListForKernel (pTreeCurrentParam, DEFAULT_EP_KERNEL_AMEX);
		SDSA_Parameters_BuildAIDNodes(pTreeCurrentParam);

		SDSA_VisaWave_SetVisaAsiaGuiMode();
		SDSA_Interac_SetInteracGuiMode();

		// Check in the parameter file if the quick GUI mode is activated or not (if yes the GUI time will be minimized)
		SDSA_GuiState_SetQuickGUIMode();

		// Generate a SHA calculated on the loaded parameters.
		// This SHA allows the terminal to be able to check if the parameters loaded in the Intelligent Reader are coherent with his ones.
		SDSA_Parameters_Compute_Config_CRC(&pTreeCurrentParam, &nCRCLength, &pSha);

		if (hOutputTlvTree != NULL)
		{
			TlvTree_AddChild (hOutputTlvTree, TAG_SDSA_LOADED_PARAMETERS_SHA, pSha, nCRCLength);
		}
	}
	else if (nNodeTag == TAG_SDSA_BLACKLIST_FILE_NODE)
	{
		// The input TLVTree contains a blacklist file
		
		// Copy the given blacklist in a structure
		if(SDSA_BlackList_LoadNewBlackList(hInputTlvTree))
		{
			// Save the blacklist structure in a file
			SDSA_BlackListSave();
			// Load the blacklist file in memory
			SDSA_BlackListLoad();
		}
		else
		{
			// An error occured with the received blacklist, load the default blacklist file in memory
			SDSA_BlackListLoad();
		}
	}
	else
	{
		GTL_Traces_TraceDebug ("SDSA_Parameters_LoadParameters : bad input TlvTree");
		return (SDI_STATUS_INVALID_DATA);
	}

	return (SDI_STATUS_OK);
}



//! \brief Function called to get the application parameters or only get the parameter calculated checksum.
//! \param[in] hInputTlvTree Not used.
//! \param[out] hOutputTlvTree Filled with the application parameters.
//! \return
//!	- \ref SDI_STATUS_OK if parameters correctly loaded.
//!	- \ref SDI_STATUS_KO if an error occured.
//!	- \ref SDI_STATUS_NO_PARAMETER if there is no parameter to get.

int SDSA_Parameters_GetParameters (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	TLV_TREE_NODE pGetShaOnly;
	unsigned char * pValue;
	unsigned int nDataLength;
	int nCRCLength;
	unsigned char * pSha;
	unsigned char bGetShaOnly = FALSE;


	GTL_Traces_TraceDebug ("SDSA_Parameters_GetParameters");

	// Generate a SHA calculated on the loaded parameters.
	// This SHA allows the terminal to be able to check if the parameters loaded in the Intelligent Reader are coherent with his ones.
	if(pTreeCurrentParam != NULL)
	{
		SDSA_Parameters_Compute_Config_CRC(&pTreeCurrentParam, &nCRCLength, &pSha);
	}
	else
	{
		GTL_Traces_TraceDebug ("SDSA_Parameters_GetParameters, No param loaded");
		return(SDI_STATUS_NO_PARAMETER);
	}

	// Check if only the parameter SHA is requested
	pGetShaOnly = TlvTree_Find(hInputTlvTree, TAG_SDSA_GET_PARAMETERS_SHA_ONLY, 0);
	if (pGetShaOnly != NULL)
	{
		pValue = TlvTree_GetData(pGetShaOnly);
		nDataLength = TlvTree_GetLength(pGetShaOnly);
		if ((pValue != NULL) && (nDataLength != 0) && (pValue[0] != 0))
		{
			GTL_Traces_TraceDebug ("Get Sha Only");
			bGetShaOnly = TRUE;			
		}
	}

	if(!bGetShaOnly)
	{
		// All the parameters are requested, copy it in the output buffer
		if(TlvTree_Graft(hOutputTlvTree, TlvTree_Copy(pTreeCurrentParam)) != TLV_TREE_OK)
		{
			GTL_Traces_TraceDebug ("GetParameters error");
			return (SDI_STATUS_KO);
		}
	}

	// Add the calculated SHA in the output buffer
	TlvTree_AddChild (hOutputTlvTree, TAG_SDSA_LOADED_PARAMETERS_SHA, pSha, nCRCLength);
	
	return (SDI_STATUS_OK);
}



//! \brief Function called to erase the parameters.
//! \return
//!	- \ref SDI_STATUS_OK if parameters correctly loaded.
//!	- \ref SDI_STATUS_KO if an error occured.

int SDSA_Parameters_EraseParameters (void)
{
	GTL_Traces_TraceDebug ("SDSA_Parameters_EraseParameters");
	
	// Reset TLVTree parameters
	SDSA_Parameters_InitParameters(&pTreeCurrentParam);

	// Save empty parameters file (allow to delete the saved file if existing)
	if (SDSA_Parameters_SaveParam (pTreeCurrentParam) != 0)
	{
		GTL_Traces_TraceDebug ("SDSA_Parameters_EraseParameters save error");
		return (SDI_STATUS_KO);
	}

//	SDSA_Parameters_CreateSupportedCertificateListForKernel (pTreeCurrentParam, DEFAULT_EP_KERNEL_PAYPASS);
//	SDSA_Parameters_CreateSupportedCertificateListForKernel (pTreeCurrentParam, DEFAULT_EP_KERNEL_AMEX);
//	SDSA_Parameters_BuildAIDNodes(pTreeCurrentParam);

	SDSA_VisaWave_SetVisaAsiaGuiMode();
	SDSA_Interac_SetInteracGuiMode();

	// Check in the parameter file if the quick GUI mode is activated or not (if yes the GUI time will be minimized)
	SDSA_GuiState_SetQuickGUIMode();

	return (SDI_STATUS_OK);
}
