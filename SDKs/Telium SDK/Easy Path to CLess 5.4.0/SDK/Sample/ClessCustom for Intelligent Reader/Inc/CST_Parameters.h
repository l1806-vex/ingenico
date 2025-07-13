/**
 * \file	CST_Parameters.h
 * \brief	This module contains the functions needed for parameters management.
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

#ifndef __CST_PARAMETERS_H__INCLUDED__
#define __CST_PARAMETERS_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \brief Init Type for files access
#define DISK_SIZE						0x19000				/*!< Disk size definition. 100kb. */
#define LABEL_DISK						"E_CUST"			/*!< Const part of Label_Disk_Name. */
#define LABEL_EXCH_DISK					"HOST"				/*!< Const part of Label_Disk_Name. */

//! \brief Parameter files names
#define C_FILE_PARAM_SAV				"CLESSPARAM.PAR"	/*!< Name of the CLESSPARAM parameter file. This file is used to save the current parameter configuration in case of power failure. */
#define C_FILE_PARAM_XML				"CLESSCUST.PAR"		/*!< Name of the CLESSCUST parameter file. This file contains a parameter list to configure the terminal (AID1, AID2, ICS1, ICS2, ...). When this file is loaded, the CLESSPARAM.PAR file is initialized with its content. */
#define C_FILE_NAME_XML					"CLESSCUST"			/*!< Root of CLESSCUST.PAR file name. */
#define C_FILE_SHAPARAM_SAV				"SHAPARAM.PAR"		/*!< Name of the SHAPARAM file. This file is used to save the current parameter sha in case of power failure. */


//! \brief Array for parameters serialisation
//#define C_PUC_BUFFER_SIZE				0x8000				/*!< (32k) Array size to store data read (or to write) from (in) a file (32Ko). */
#define C_PUC_MAX_BUFFER_SIZE			0x18000				/*!< (100k) Max array size to store data read (or to write) from (in) a file (32Ko). */
#define C_PUC_MAX_SHABUFFER_SIZE		0x400				/*!< (1k) Max array size to store sha read (or to write) from (in) a file. */



// AID parameters tag
#define C_PARAM_AID_TAG					TAG_SDSA_AID_PARAMETERS

// key parameters tag
#define C_PARAM_CAKEY_TAG				TAG_SDSA_CAKEYS_PARAMETERS

// Revokation key parameters tag
#define C_PARAM_KREVOK_TAG				TAG_SDSA_CAREVOK_PARAMETERS

// Global parameters Tag
#define C_PARAM_GLOBAL_TAG				TAG_SDSA_ICS_PARAMETERS

// Kernel parameters tag
#define C_PARAM_KERNEL_TAG				TAG_SDSA_SPECIFIC_PARAMETERS


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

extern TLV_TREE_NODE pTreeCurrentParam;				/*!< Node from param file parameters. */
extern TLV_TREE_NODE pTreeDefaultParam;				/*!< Node from default parameters. */


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief This function clear TLVTree used to store parameters. 
//! \param[in] TLVTree to clear.

void CST_Parameters_InitParameters(TLV_TREE_NODE * pTree);



//! \brief This function update TLVTree with defaut parameters (read in an array). 
//! \param[in] TLVTree to update with default parameters.

void CST_Parameters_ReadDefaultParameters(TLV_TREE_NODE * pTree);



//! \brief This function update TLVTree with parameters read in a XML text file. 
//! \param[in] p_node to update with parameters read.
//! \param[in] i_x_tag main node to set in TLVRee.
//! \param[in] filePath file path of xml text file to read.
//! \param[in] fileName file name of xml text file to read.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int CST_Parameters_ReadXMLParamFile (TLV_TREE_NODE * ptr_pTree, unsigned int i_x_tag, char *filePath, char *fileName);



//! \brief This function set TLVTree parameters in a save file, and save the sha calculated in a second file. 
//! \param[in] pTree to save.
//! \param[in] pucSha Sha to save (calculated with given parameters).
//! \param[in] nShaLength Length of the sha.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int CST_Parameters_SaveParam (TLV_TREE_NODE pTree, unsigned char *pucSha, int nShaLength);



//! \brief This function update TLVTree with parameters read in a save file. 
//! \param[in] pTree TLVTree to get.
//! \param[in] pucSha sha to get.
//! \param[in] nSize size of the pucSha buffer.
//! \param[in] pulShaLength length of the sha.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int CST_Parameters_RestoreParam (TLV_TREE_NODE * pTree, unsigned char *pucSha, int nSize, unsigned long *pulShaLength);



//! \brief Read the XML file and store it in a TLV Tree.
//! \param[in] VolumeName Volume name where the file is located.
//! \param[in] FileName File Name.
//! \param[out] pTree Store the XML file content in this TLV Tree.
//! \return
//!		- \a FCT_OK if file is not for the application.
//!		- \a STOP if the file is for the application.

int CST_Parameters_ReadXMLFile (char * VolumeName, char * FileName, TLV_TREE_NODE * pTree);



//! \brief Check the CA keys coherence and verify the checksum.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "CST_DumpData.h" functions).

void CST_Parameters_CheckCaKeysCrc (TLV_TREE_NODE ParameterTlvTree);



//! \brief Dump the CA keys configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.

void CST_Parameters_DumpCaKeys (TLV_TREE_NODE ParameterTlvTree);



//! \brief Dumps the parameters identifier label.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.

void CST_Parameters_DumpIdentificationLabel (TLV_TREE_NODE ParameterTlvTree);



//! \brief Dump the AIDs configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.

void CST_Parameters_DumpAids (TLV_TREE_NODE ParameterTlvTree);



//! \brief Dump the global parameters configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.

void CST_Parameters_DumpGlobals (TLV_TREE_NODE ParameterTlvTree);



//! \brief Dump the kernel specific parameters configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.

void CST_Parameters_DumpKernelSpecific (TLV_TREE_NODE ParameterTlvTree);



//! \brief This function returns the Sha of the current parameters.
//! \return Sha calculated on the current parameters.

unsigned char *CST_Parameters_GetSha(void);



//! \brief This function returns the size of the variable that contained the Sha of the current parameters.
//! \return The size of the variable that contained the Sha.

int CST_Parameters_GetShaSize(void);



//! \brief This function returns the length of the Sha of the current parameters.
//! \return The sha length.

unsigned long *CST_Parameters_GetShaLength(void);



//! \brief This function set the length of the Sha of the current parameters.
//! \param[in] ulLen Length of the Sha.

void CST_Parameters_SetShaLength(unsigned long ulLen);



//! \brief This function checks the consistency between the terminal parameters and the intelligent reader parameters.
//! \brief If parameters are not consistent, parameters are loaded in the intelligent reader.

void CST_Parameters_CheckConsistency(void);



//! \brief This function get the moneys defined in the parameter file.

void CST_Parameters_GetMoneyExtendedFromParameters(void);



//! \brief This function give Extended money structure initialized with parameters.
//! \param[in/out] n_x_NbMoney Number of money managed.
//! \param[in/out] ps_x_Money pnode parameters node for the kernel.

void CST_Parameters_GetMoneyExtended(int * n_x_NbMoney, S_MONEY_EXTENDED ** ps_x_Money);


#endif // __CST_PARAMETERS_H__INCLUDED__
