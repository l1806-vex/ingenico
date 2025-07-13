/**
 * \file	ClessSample_Parameters.h
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

#ifndef __CLESS_SAMPLE_PARAMETERS_H__INCLUDED__
#define __CLESS_SAMPLE_PARAMETERS_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \brief Init Type for files access
#define DISK_SIZE						0x19000				/*!< Disk size definition. 100kb. */
#define LABEL_DISK						"E_CUST"			/*!< Const part of Label_Disk_Name. */
#define LABEL_EXCH_DISK					"HOST"				/*!< Const part of Label_Disk_Name. */


//! \brief Parameter files names
#define C_FILE_PARAM_SAV				"CLESSPARAM.PAR"	/*!< Name of the PARAM parameter file. This file is used to save the current parameter configuration in case of power failure. */
#define C_FILE_PARAM_XML				"CLESSCUST.PAR"		/*!< Name of the CLESSCUST parameter file. This file contains a parameter list to configure the terminal (AID1, AID2, ICS1, ICS2, ...). When this file is loaded, the PARAM.PAR file is initialized with its content. */
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
#define C_PARAM_AID_TAG					TAG_SAMPLE_AID_PARAMETERS

// key parameters tag
#define C_PARAM_CAKEY_TAG				TAG_SAMPLE_CAKEYS_PARAMETERS

// Revokation key parameters tag
#define C_PARAM_KREVOK_TAG				TAG_SAMPLE_CAREVOK_PARAMETERS

// Global parameters Tag
#define C_PARAM_GLOBAL_TAG				TAG_SAMPLE_ICS_PARAMETERS

// Kernel parameters tag
#define C_PARAM_KERNEL_TAG				TAG_SAMPLE_SPECIFIC_PARAMETERS


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
	unsigned char bAidProprietaryIdPresent;	// Indicates if AID propretary identifier is present or not
	unsigned char ucAidProprietaryId[4];	// AID Proprietary Identifier
	TLV_TREE_NODE pTreeAID;					// AID Node (set of parameters)
	T_SHARED_DATA_STRUCT * pSharedAIDParam;	// AID buffer Shared (set of parameters)
} T_PARAMETER_AID;


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

extern TLV_TREE_NODE pTreeCurrentParam;				/*!< Node from param file parameters. */
extern TLV_TREE_NODE pTreeDefaultParam;				/*!< Node from default parameters. */


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief This function clear TLVTree used to store parameters. 
//! \param[in] TLVTree to clear.

void ClessSample_Parameters_InitParameters(TLV_TREE_NODE * pTree);



//! \brief This function update TLVTree with defaut parameters (read in an array). 
//! \param[in] TLVTree to update with default parameters.

void ClessSample_Parameters_ReadDefaultParameters(TLV_TREE_NODE * pTree);



//! \brief This function update TLVTree with parameters read in a XML text file. 
//! \param[in] TLVTree to update with parameters read.
//! \param[in] tag main node to set in TLVRee.
//! \param[in] filePath file path of xml text file to read.
//! \param[in] fileName file name of xml text file to read.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int ClessSample_Parameters_ReadXMLParamFile (TLV_TREE_NODE * ptr_pTree, unsigned int i_x_tag, char *filePath, char *fileName);



//! \brief This function set TLVTree parameters in a save file. 
//! \param[in] TLVTree to save.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int ClessSample_Parameters_SaveParam (TLV_TREE_NODE pTree);



//! \brief This function update TLVTree with parameters read in a save file. 
//! \param[in] TLVTree to save.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int ClessSample_Parameters_RestoreParam (TLV_TREE_NODE * pTree);



//! \brief This function compute a CRC allowing to check parameters loaded.
//! The CRC is computed on a list of a fix list of tags.
//! \note This function return the configuration CRC.
//! \param[in] TLVTree to go througth to process CRC.
//! \param[out] nCRCLength length of CRC computed.
//! \param[in] ucCRC pointer on computed CRC.
//! \return Always \a TRUE.

int ClessSample_Parameters_Compute_Config_CRC(TLV_TREE_NODE * pTree, int * nCRCLength, unsigned char ** pSha);



//! \brief This function allows to trace TLV tree given as parameter on trace tool
//! \param[in] pTree TLV tree to trace.
//! \param[in] txt text to display at begining of trace.

void ClessSample_Parameters_TlvTree_Display(TLV_TREE_NODE pTree , char * txt);



//! \brief This function trace parameters store in a TLVTree.
//! \brief Trace may be made on printer, USB, ... 
//! \param[in] pnode TLV tree to trace.
//! \param[in] ucOutputType allows to specify output driver : printer, USB ...
//! \param[in] ptr_x_DataName text to display at the begining of trace.
//! \param[in] c_x_tracetype allows to trace all tags or only value of tag given in parameter.
//! \param[in] ul_x_tag tag if only value of one tag may be printed.

void ClessSample_Parameters_Trace_Param_Supported(TLV_TREE_NODE pnode, unsigned char ucOutputType, char *ptr_x_DataName, unsigned char c_x_tracetype, unsigned long ul_x_tag);



//! \brief This function trace CRC of a predefine list of tag of a TLVTree.
//! \brief Trace may be made on printer, USB, ... 
//! \param[in] ucOutputType allows to specify output driver : printer, USB ...
//! \param[in] pnode TLV tree to compute CRC on.
//! \param[in] ptr_x_DataName text to display at the begining of trace.

void ClessSample_Parameters_Trace_CRC(TLV_TREE_NODE pnode, unsigned char ucOutputType, char *ptr_x_DataName);



//! \brief This function send number of AID parameters set stored.
//! \return number of AID store.

int ClessSample_Parameters_GiveAIDNumber(void);



//! \brief This function Send AID of parameters store.
//! \param[in] n_x_AIDIndex index on AID chosen by select application.
//! \param[out] pAIDLength length of AID.
//! \return pointer on AID.

unsigned char * ClessSample_Parameters_GiveAID(unsigned int n_x_AIDIndex, int * pAIDLength);



//! \brief This function select TLVTree of parameters in relationchip with Index AID.
//! \param[in] n_x_AIDIndex index on AID chosen by select application.
//! \param[in] nAIDLength AID length used by select application process.
//! \return TLV Tree in relationship with AID used or void pointer if no TLVTree found.

TLV_TREE_NODE ClessSample_Parameters_GiveAIDTLVTtree(unsigned int n_x_AIDIndex);



//! \brief This function select shared buffer of parameters to use with Index AID.
//! \param[in] n_x_AIDIndex index on AID chosen by select application.
//! \return SharedBuffer in relationship with AID used or void pointer if no SharedBuffer found.

T_SHARED_DATA_STRUCT * ClessSample_Parameters_GiveAIDShareBuffer(unsigned int n_x_AIDIndex);



//! \brief This function select shared buffer of parameters to use with Index AID.
//! \param[in] ul_x_AIDIndex index on AID chosen by select application.
//! \param[in] ucAID AID used by select application process.
//! \param[in] nAIDLength AID length used by select application process.
//! \return SharedBuffer in relationship with AID used or void pointer if no SharedBuffer found.

TLV_TREE_NODE ClessSample_Parameters_GiveAIDNode(unsigned long ul_x_AIDIndex, unsigned char * ucAID, int nAIDLength);



//! \brief This function found subset parameters and select parameters to store in MainNode.
//! \param[in] pMainNode main parameters set.
//! \param[in] pParameter parameters node.
//! \param[in] ulSubsetTag tag.
//! \param[in] ulTag tag to found allowing to choose parameter set in ulSubsetTag.
//! \param[in] nAIDLength AID length used by select application process.
//! \param[in] nParametersType allows to specify if parameters to add are prioritary, exclusive or not. 
//! \return SharedBuffer in relationship with AID used or void pointer if no SharedBuffer found.

int ClessSample_Parameters_AddParametersInNode(TLV_TREE_NODE pMainNode, TLV_TREE_NODE pParameterNode, unsigned long ulSubsetTag, unsigned long ulTag, int nTagLength, unsigned char * ucTagValue, int nParametersType);



//! \brief This function organise TLVTree nodes for a parameters use with AID selection.
//! \param[in] pnode parameters node for the kernel.

void ClessSample_Parameters_BuildAIDNodes(TLV_TREE_NODE pnode);



//! \brief Dump parameters set on trace link.

void ClessSample_Parameters_Trace_Parameter_AID_Structure(void);



//! \brief Read the XML file and store it in \a pTreeParam.
//! \param[in] VolumeName Valoume name where the file is located.
//! \param[in] FileName File Name.
//! \param[out] pTree Store the XML file content in this TLV Tree.
//! \return
//!		- \a FCT_OK if file is not for the application.
//!		- \a STOP if the file is for the application.

int ClessSample_Parameters_ReadXMLFile (char * VolumeName, char * FileName, TLV_TREE_NODE * pTree);



//! \brief Get the CA Key data according to the RID and the CA Key index.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[in] ucCaKeyIndex CA Public Key index to find.
//! \param[in] pRid RID to be used to find the CA Public Key.
//! \param[out] pOutputDataStruct Shared buffer filled with the CA Public Key data.
//! \return
//!		- \ref TRUE if correctly performed (data found and \a pOutputDataStruct filled).
//!		- \ref FALSE if an error occurred.

int ClessSample_Parameters_GetCaKeyData (TLV_TREE_NODE ParameterTlvTree, const unsigned char ucCaKeyIndex, const unsigned char * pRid, T_SHARED_DATA_STRUCT * pOutputDataStruct);



//! \brief Check the CA keys coherence and verify the checksum.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_CheckCaKeysCrc (TLV_TREE_NODE ParameterTlvTree);



//! \brief Dump the CA keys configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_DumpCaKeys (TLV_TREE_NODE ParameterTlvTree);



//! \brief Dumps the parameters identifier label.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_DumpIdentificationLabel (TLV_TREE_NODE ParameterTlvTree);


//! \brief Dump the AIDs configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_DumpAids (TLV_TREE_NODE ParameterTlvTree);



//! \brief Dump the global parameters configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_DumpGlobals (TLV_TREE_NODE ParameterTlvTree);


//! \brief Dump the kernel specific parameters configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_DumpKernelSpecific (TLV_TREE_NODE ParameterTlvTree);



//! \brief Create the certificate supported list for each PayPass AID.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[in] usKernelId Kernel identifier to determine which AID structure shall be updated with the supported certificate list.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int ClessSample_Parameters_CreateSupportedCertificateListForKernel (TLV_TREE_NODE ParameterTlvTree, unsigned short usKernelId);



//! \brief Get the CA Key data according to the RID and the CA Key index.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[out] pCertificateList List of supported certificate indexes.
//! \param[in,out] Input : The length of \a pCertificate. Output : length of the certificate list.
//! \param[in] pRid RID to be used to find the CA Public Key.
//! \param[out] pOutputDataStruct Shared buffer filled with the CA Public Key data.

void ClessSample_Parameters_GetSupportedCertificateList (TLV_TREE_NODE ParameterTlvTree, unsigned char * pCertificateList, unsigned long * pCertificateListLength, const unsigned char * pRid);


//! \brief This function give Extended money structure initialized with parameters.
//! \param[in/out] n_x_NbMoney Number of money managed.
//! \param[in/out] ps_x_Money pnode parameters node for the kernel.

void ClessSample_Parameters_GetMoneyExtended(int * n_x_NbMoney, S_MONEY_EXTENDED ** ps_x_Money);


//! \brief This function get the currency label and exponent from the parameters.
//! \param[in] pCurrencyCode Currency code to find in the parameter file.
//! \param[out] pCurrencyLabel Currency label to get.
//! \param[out] pCurrencyExponent Currency exponent to get.
//!   \return
//!   - \a TRUE if currency is found.
//!   - \a FALSE indicate an invalid parameter as the currency code provided is unknown from the application.

int ClessSample_Parameters_GetCurrencyFromParameters(unsigned char *pCurrencyCode, char **pCurrencyLabel);


//! \brief This function get the format and the currency position from the parameters to display the amount.
//! \param[in] pCurrencyLabel Currency label to find in the parameter file.
//! \param[out] pFormat Format of the displayed amount.
//! \param[out] pPosition Position of the currency (before or after the amount).
//!	\return
//!	- \a TRUE if format to display is found.
//!	- \a FALSE indicate an invalid parameter as the currency label provided is unknown from the application.

int ClessSample_Parameters_GetCurrencyFormatFromParameters(char *pCurrencyLabel, unsigned char *pFormat,unsigned char *pPosition);

#endif // __CLESS_SAMPLE_PARAMETERS_H__INCLUDED__
