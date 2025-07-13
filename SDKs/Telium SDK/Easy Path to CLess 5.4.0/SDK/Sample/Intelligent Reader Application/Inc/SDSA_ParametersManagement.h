/**
 * \file	SDSA_ParametersManagement.h
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

#ifndef __SDSA_PARAMETERSMANAGEMENT_H__INCLUDED__
#define __SDSA_PARAMETERSMANAGEMENT_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \brief Init Type for files access
#define DISK_SIZE						0x19000				/*!< Disk size definition. 100kb. */
#define LABEL_DISK						"E_CUST"			/*!< Const part of Label_Disk_Name. */
#define LABEL_EXCH_DISK					"HOST"				/*!< Const part of Label_Disk_Name. */


//! \brief Parameter files names
#define C_FILE_PARAM_SAV				"CLESSPARAM.PAR"	/*!< Name of the CLESSPARAM parameter file. This file is used to save the current parameter configuration in case of power failure. */
#define C_FILE_NAME_XML					"CLESSCUST"			/*!< Root of CLESSCUST.PAR file name. */


// \brief Definitions of tag types.
#define C_TAG_TYPE_HEXA_BYTE			0					/*!< The data of the tag is one hexadecimal byte. */
#define C_TAG_TYPE_BUF_BYTE				1					/*!< The data of the tag is a byte buffer. */
#define C_TAG_TYPE_BUF_BYTE_WITH_MASQ	2					/*!< The data of the tag is a byte buffer to be masked. */
#define C_TAG_TYPE_BOOLEAN				3					/*!< The data of the tag is a boolean value. */
#define C_TAG_TYPE_TXT					4					/*!< The data of the tag is a text value. */


//! \brief Mark selection for static array or file access
#define C_TRACE_ALL_CHILD				0					/*!< All tags in all children will be set in file. */
#define C_TRACE_MARK					1					/*!< All tags with the marks will be set in file. */
#define C_TRACE_WITHOUT_MARK			2					/*!< All tags without the marks (used by parameters management) will be set in file. */
#define C_TRACE_ONE_TAG             	3					/*!< One type of tag will be concerned by the command. */


//! \brief Array for parameters serialisation
//#define C_PUC_BUFFER_SIZE				0x8000				/*!< (32k) Array size to store data read (or to write) from (in) a file (32Ko). */
#define C_PUC_MAX_BUFFER_SIZE			0x18000				/*!< (100k) Max array size to store data read (or to write) from (in) a file (32Ko). */


//! \brief Tag management (boolean types)
#define NONE							"NONE"				/*!< Value used in global parameter file EMVCUST.PAR. */
#define NO								"NO"				/*!< NO value for a parameter of file EMVCUST.PAR. 0 is also used. */
#define YES								"YES"				/*!< YES value for a parameter of file EMVCUST.PAR. 1 is also used. */


#define C_TAG_MAIN						0x0000				/*!< Origin of each TLVTree. */
#define C_PARAM_SEPARATOR_TAG			0x1000				/*!< Separator field. */


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


// AID parameters set
#define C_NUMBER_AID_MAX				16
#define C_LG_MAX_AID					16
#define C_SHARE_BUFFER_SIZE				1024
#define C_SHARE_BUFFER_KERNEL_SIZE		10240

// Parameter set type : multiple tag could be stored or just last or previous is kept
#define C_MULTI_PARAMS					0
#define C_PRIORITY_PARAMS				1
#define C_UNPRIORITY_PARAMS				2


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

//! \brief 
typedef struct
{
	unsigned long tag;				/*!<  */
	unsigned int length;			/*!<  */
	unsigned char* ptValue;			/*!<  */
} T_PARAMETER_ELEMENT_STR;

//! \brief
typedef T_PARAMETER_ELEMENT_STR ParameterElement;


//! \brief
typedef struct
{
	unsigned long tag;				/*!<  */
	unsigned char tagtype;			/*!<  */
	unsigned char * Masq;			/*!<  */
}Struct_TagList;


// For each AID : AID informations
typedef struct
{
	unsigned char ucAID[C_LG_MAX_AID];		// AID in relationship with node
	unsigned int nAIDLength;				// Length of AID
	unsigned char ucAIDIndex;				// AID Index
	unsigned char bAidProprietaryIdPresent;	// Indicates if AID proprietary identifier is present or not
	unsigned char ucAidProprietaryId[4];	// AID Proprietary Identifier
	TLV_TREE_NODE pTreeAID;					// AID Node (set of parameters)
	T_SHARED_DATA_STRUCT * pSharedAIDParam;	// AID buffer Shared (set of parameters)
} T_PARAMETER_AID;


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

extern TLV_TREE_NODE pTreeCurrentParam;				/*!< Node from param file parameters. */


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief This function clear TLVTree used to store parameters. 
//! \param[in] TLVTree to clear.

void SDSA_Parameters_InitParameters(TLV_TREE_NODE * pTree);



//! \brief This function set TLVTree parameters in a save file. 
//! \param[in] TLVTree to save.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int SDSA_Parameters_SaveParam (TLV_TREE_NODE pTree);



//! \brief This function update TLVTree with parameters read in a save file. 
//! \param[in] TLVTree to save.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int SDSA_Parameters_RestoreParam (TLV_TREE_NODE * pTree);



//! \brief This function compute a CRC allowing to check parameters loaded.
//! The CRC is computed on a list of a fix list of tags.
//! \note This function return the configuration CRC.
//! \param[in] TLVTree to go througth to process CRC.
//! \param[out] nCRCLength length of CRC computed.
//! \param[in] ucCRC pointer on computed CRC.
//! \return Always \a TRUE.

int SDSA_Parameters_Compute_Config_CRC(TLV_TREE_NODE * pTree, int * nCRCLength, unsigned char ** pSha);



//! \brief This function send number of AID parameters set stored.
//! \return number of AID store.

int SDSA_Parameters_GiveAIDNumber(void);



//! \brief This function Send AID of parameters store.
//! \param[in] n_x_AIDIndex index on AID chosen by select application.
//! \param[out] pAIDLength length of AID.
//! \return pointer on AID.

unsigned char * SDSA_Parameters_GiveAID(unsigned int n_x_AIDIndex, int * pAIDLength);



//! \brief This function select TLVTree of parameters in relationchip with Index AID.
//! \param[in] n_x_AIDIndex index on AID chosen by select application.
//! \param[in] nAIDLength AID length used by select application process.
//! \return TLV Tree in relationship with AID used or void pointer if no TLVTree found.

TLV_TREE_NODE SDSA_Parameters_GiveAIDTLVTtree(unsigned int n_x_AIDIndex);



//! \brief This function select shared buffer of parameters to use with Index AID.
//! \param[in] n_x_AIDIndex index on AID chosen by select application.
//! \return SharedBuffer in relationship with AID used or void pointer if no SharedBuffer found.

T_SHARED_DATA_STRUCT * SDSA_Parameters_GiveAIDShareBuffer(unsigned int n_x_AIDIndex);



//! \brief This function select shared buffer of parameters to use with Index AID.
//! \param[in] ul_x_AIDIndex index on AID chosen by select application.
//! \param[in] ucAID AID used by select application process.
//! \param[in] nAIDLength AID length used by select application process.
//! \return SharedBuffer in relationship with AID used or void pointer if no SharedBuffer found.

TLV_TREE_NODE SDSA_Parameters_GiveAIDNode(unsigned long ul_x_AIDIndex, unsigned char * ucAID, int nAIDLength);



//! \brief This function found subset parameters and select parameters to store in MainNode.
//! \param[in] pMainNode main parameters set.
//! \param[in] pParameter parameters node.
//! \param[in] ulSubsetTag tag.
//! \param[in] ulTag tag to found allowing to choose parameter set in ulSubsetTag.
//! \param[in] nAIDLength AID length used by select application process.
//! \param[in] nParametersType allows to specify if parameters to add are prioritary, exclusive or not. 
//! \return SharedBuffer in relationship with AID used or void pointer if no SharedBuffer found.

int SDSA_Parameters_AddParametersInNode(TLV_TREE_NODE pMainNode, TLV_TREE_NODE pParameterNode, unsigned long ulSubsetTag, unsigned long ulTag, int nTagLength, unsigned char * ucTagValue, int nParametersType);



//! \brief This function organise TLVTree nodes for a parameters use with AID selection.
//! \param[in] pnode parameters node for the kernel.

void SDSA_Parameters_BuildAIDNodes(TLV_TREE_NODE pnode);




//! \brief Get the CA Key data according to the RID and the CA Key index.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[in] ucCaKeyIndex CA Public Key index to find.
//! \param[in] pRid RID to be used to find the CA Public Key.
//! \param[out] pOutputDataStruct Shared buffer filled with the CA Public Key data.
//! \return
//!		- \ref TRUE if correctly performed (data found and \a pOutputDataStruct filled).
//!		- \ref FALSE if an error occured.

int SDSA_Parameters_GetCaKeyData (TLV_TREE_NODE ParameterTlvTree, const unsigned char ucCaKeyIndex, const unsigned char * pRid, T_SHARED_DATA_STRUCT * pOutputDataStruct);



//! \brief Create the certificate supported list for each PayPass AID.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[in] usKernelId Kernel identifier to determine which AID structure shall be updated with the supported certificate list.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

int SDSA_Parameters_CreateSupportedCertificateListForKernel (TLV_TREE_NODE ParameterTlvTree, unsigned short usKernelId);



//! \brief Get the CA Key data according to the RID and the CA Key index.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[out] pCertificateList List of supported certificate indexes.
//! \param[in,out] Input : The length of \a pCertificate. Output : length of the certificate list.
//! \param[in] pRid RID to be used to find the CA Public Key.
//! \param[out] pOutputDataStruct Shared buffer filled with the CA Public Key data.

void SDSA_Parameters_GetSupportedCertificateList (TLV_TREE_NODE ParameterTlvTree, unsigned char * pCertificateList, unsigned long * pCertificateListLength, const unsigned char * pRid);


//! \brief This function give Extended money structure initialized with parameters.
//! \param[in/out] n_x_NbMoney Number of money managed.
//! \param[in/out] ps_x_Money pnode parameters node for the kernel.

void SDSA_Parameters_GetMoneyExtended(int * n_x_NbMoney, S_MONEY_EXTENDED ** ps_x_Money);


#endif // __SDSA_PARAMETERSMANAGEMENT_H__INCLUDED__
