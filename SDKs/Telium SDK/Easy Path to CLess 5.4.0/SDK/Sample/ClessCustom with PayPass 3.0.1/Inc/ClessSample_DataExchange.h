/**
 * \file	ClessSample_DataExchange.h
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

#ifndef __CLESS_SAMPLE_DATAEXCHANGE_H__INCLUDED__
#define __CLESS_SAMPLE_DATAEXCHANGE_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \brief Init Type for files access
#define C_EVAL_DISK_SIZE				0x19000					/*!< Disk size definition. 100kb. */
#define C_EVAL_LABEL_DISK				"E_CUST_EVAL"			/*!< Const part of Label_Disk_Name. */

//! \brief Data Exchange files names
#define C_FILE_EVAL_SAV					"DEKDET_SAV.PAR"		/*!< Name of the file used to save the current DEK/DET data in case of power failure. */
#define C_FILE_EVAL_XML					"DEKDET.PAR"			/*!< Name of the EVAL Data Exchange XML file as supplied by MCW. This file contains expected DEK Signals and the corresponding DET Signal(s). */
#define C_FILE_EVAL_NAME_XML			"DEKDET"				/*!< Root of DEKDET.XML file name. */

//! \brief Array for data exchange data serialisation
#define C_EVAL_DATA_MAX_BUFFER_SIZE		0x18000					/*!< (100k) Max array size to store data read (or to write) from (in) a file (32Ko). */

// MCW XML plots
#define MCW_XML_PLOT_MESSAGE			"MESSAGE"
#define MCW_XML_PLOT_HEADER				"HEADER"
#define MCW_XML_PLOT_BODY				"BODY"
#define MCW_XML_PLOT_EVT				"EVT"
#define MCW_XML_PLOT_DEK				"DEK"
#define MCW_XML_PLOT_DET				"DET"
#define MCW_XML_PLOT_DEKPROPERTIES		"DEKPROPERTIES"
#define MCW_XML_PLOT_DETPROPERTIES		"DETPROPERTIES"
#define MCW_XML_PLOT_TRAILER			"TRAILER"

// MCW XML Event attributes
#define MCW_XML_EVT_ATTRIBUTE_TYPE		"type"

// MCW XML Event types
#define MCW_XML_EVT_TYPE_DEKRECEIVED	"DEKRECEIVED"

// MCW XML fields
#define MCW_XML_FIELD_FILE_NAME			"FILE_NAME"
#define MCW_XML_FIELD_FILE_DATE			"FILE_DATE"
#define MCW_XML_FIELD_TEMPLATE_VERSION	"TEMPLATE_VERSION"
#define MCW_XML_FIELD_GENERATED_BY		"GENERATED_BY"
#define MCW_XML_FIELD_COMPANY_NAME		"COMPANY_NAME"
#define MCW_XML_FIELD_PRODUCT_NAME		"PRODUCT_NAME"
#define MCW_XML_FIELD_PRODUCT_VERSION	"PRODUCT_VERSION"
#define MCW_XML_FIELD_OPERATOR_NAME		"OPERATOR_NAME"
#define MCW_XML_FIELD_DEKVALUE			"DEKVALUE"
#define MCW_XML_FIELD_DETVALUE			"DETVALUE"
#define MCW_XML_FIELD_STATE				"STATE"
#define MCW_XML_FIELD_SIGNATURE			"SIGNATURE"

// MCW XML Tags
#define MCW_XML_TAG_MESSAGE				0x1000
#define MCW_XML_TAG_HEADER				0x1001
#define MCW_XML_TAG_BODY				0x1002
#define MCW_XML_TAG_EVT					0x1003
#define MCW_XML_TAG_DEK					0x1004
#define MCW_XML_TAG_DET					0x1005
#define MCW_XML_TAG_DEKPROPERTIES		0x1006
#define MCW_XML_TAG_DETPROPERTIES		0x1007
#define MCW_XML_TAG_TRAILER				0x1008
#define MCW_XML_TAG_FILE_DATE			0x1009
#define MCW_XML_TAG_TEMPLATE_VERSION	0x100A
#define MCW_XML_TAG_GENERATED_BY		0x100B
#define MCW_XML_TAG_COMPANY_NAME		0x100C
#define MCW_XML_TAG_PRODUCT_NAME		0x100D
#define MCW_XML_TAG_PRODUCT_VERSION		0x100E
#define MCW_XML_TAG_OPERATOR_NAME		0x100F
#define MCW_XML_TAG_DEKVALUE			0x1010
#define MCW_XML_TAG_STATE				0x1011
#define MCW_XML_TAG_SIGNATURE			0x1012
#define MCW_XML_TAG_EVT_DEKRECEIVED		0x1013
#define MCW_XML_TAG_DETVALUE			0x1014
#define MCW_XML_TAG_FILE_NAME			0x1015

// MCW internal tag definition
#define TAG_MCW_PAYPASS_DD_CARD_TRACK1							0xDF812A
#define TAG_MCW_PAYPASS_DD_CARD_TRACK2							0xDF812B
#define TAG_MCW_PAYPASS_DEFAULT_UDOL							0xDF811A
#define TAG_MCW_PAYPASS_INT_MCHIP_GENAC_REF_CTRL_PARAMETER		0xDF8114
#define TAG_MCW_PAYPASS_CLESS_TRANSACTION_LIMIT_NO_DCV			0xDF8124
#define TAG_MCW_PAYPASS_CLESS_TRANSACTION_LIMIT_DCV				0xDF8125
#define TAG_MCW_PAYPASS_OUTCOME_PARAMETER_SET					0xDF8129
#define TAG_MCW_PAYPASS_USER_INTERFACE_REQUEST_DATA				0xDF8116
#define TAG_MCW_PAYPASS_ERROR_INDICATION						0xDF8115
#define TAG_MCW_PAYPASS_KERNEL_CONFIGURATION					0xDF811B
#define TAG_MCW_PAYPASS_CARD_DATA_INPUT_CAPABILITY				0xDF8117
#define TAG_MCW_PAYPASS_SECURITY_CAPABILITY						0xDF811F
#define TAG_MCW_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_REQUIRED		0xDF8118
#define TAG_MCW_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_NOT_REQUIRED	0xDF8119
#define TAG_MCW_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_REQUIRED		0xDF811E
#define TAG_MCW_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_NOT_REQUIRED 0xDF812C
#define TAG_MCW_PAYPASS_DEFAULT_HOLD_TIME						0xDF812D
#define TAG_MCW_PAYPASS_BALANCE_READ_BEFORE_GENAC				0xDF8105
#define TAG_MCW_PAYPASS_BALANCE_READ_AFTER_GENAC				0xDF8104
#define TAG_MCW_PAYPASS_INT_DS_INPUT_TERM						0xDF8109
#define TAG_MCW_PAYPASS_INT_DS_ODS_INFO_FOR_KERNEL				0xDF810A
#define TAG_MCW_PAYPASS_INT_DS_SUMMARY_2						0xDF8101
#define TAG_MCW_PAYPASS_INT_DS_SUMMARY_3						0xDF8102
#define TAG_MCW_PAYPASS_INT_DS_SUMMARY_STATUS					0xDF810B
#define TAG_MCW_PAYPASS_INT_DSVN_TERM							0xDF810D
#define TAG_MCW_PAYPASS_POST_GENAC_PUT_DATA_STATUS				0xDF810E
#define TAG_MCW_PAYPASS_PRE_GENAC_PUT_DATA_STATUS				0xDF810F
#define TAG_MCW_PAYPASS_INT_DS_AC_TYPE							0xDF8108
#define TAG_MCW_PAYPASS_INT_DS_IDS_STATUS						0xDF8128
#define TAG_MCW_PAYPASS_DS_PROCEED_TO_FIRST_WRITE				0xDF8110
#define TAG_MCW_PAYPASS_TIME_OUT_VALUE							0xDF8127
#define TAG_MCW_PAYPASS_CONSTRUCTED_DRDOL_VALUE					0xDF8113
#define TAG_MCW_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS		0xDF811D
#define TAG_MCW_PAYPASS_MAX_LIFETIME_OF_TORN_TXN_LOG_RECORD		0xDF811C
#define TAG_MCW_PAYPASS_DATA_RECORD								0xFF8105
#define TAG_MCW_PAYPASS_DISCRETIONARY_DATA						0xFF8106
#define TAG_MCW_PAYPASS_TORN_RECORD								0xFF8101
#define TAG_MCW_PAYPASS_DS_TAGS_TO_READ							0xDF8112
#define TAG_MCW_PAYPASS_DS_TAGS_TO_WRITE_AFTER_GENAC			0xFF8103
#define TAG_MCW_PAYPASS_DS_TAGS_TO_WRITE_BEFORE_GENAC			0xFF8102
#define TAG_MCW_PAYPASS_DS_DATA_TO_SEND							0xFF8104
#define TAG_MCW_PAYPASS_INT_DS_DATA_NEEDED						0xDF8106

// MCW tag to include in the DEK signal for matching purposes during testing
#define TAG_MCW_PAYPASS_TESTING_DEK_MATCH						0x5F53

/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

extern TLV_TREE_NODE pTreeCurrentDataExchange;		/*!< Node from data exchange file. */


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief This function clear TLVTree used to store parameters. 
//! \param[in] pTree Tree containing the Data Exchange parameters.

void ClessSample_DataExchange_InitTlvTree (TLV_TREE_NODE * pTree);



//! \brief Dump the EVAL parameter file.

void ClessSample_DataExchange_DumpFile (TLV_TREE_NODE hTree);



//! \brief Dump the EVAL file HEADER information.
//! \param[in] hTree TLV Tree containing the EVAL parameter file.

void ClessSample_DataExchange_DumpEvalHeaderInformation (TLV_TREE_NODE hTree);



//! \brief This function update TLVTree with parameters read in a save file. 
//! \param[in] TLVTree to save.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int ClessSample_DataExchange_RestoreFile (TLV_TREE_NODE * pTree);



//! \brief This function set EVAL XML TLVTree parameters in a save file.
//!	\param[in] hTree TLV Tree to be saved in a file.

int ClessSample_DataExchange_SaveFile (TLV_TREE_NODE hTree);



//! \brief Get the DET Signal data according to the kernel returned DEK signal.
//! \param[in,out] pSharedStruct Shared buffer filled with the DEK Signal as input and DET signal as output.
//! \return
//!		- \ref TRUE if correctly performed (data found and \a pOutputDataStruct filled).
//!		- \ref FALSE if an error occurred or no data found.

int ClessSample_DataExchange_GetDETData (T_SHARED_DATA_STRUCT * pSharedStruct);



//! \brief Read the XML file and store it in \a pTreeParam.
//! \param[in] VolumeName Valoume name where the file is located.
//! \param[in] FileName File Name.
//! \param[out] pTree Store the XML file content in this TLV Tree.
//! \return
//!		- \a FCT_OK if file is not for the application.
//!		- \a STOP if the file is for the application.

int ClessSample_DataExchange_ReadXMLFile (char * VolumeName, char * FileName, TLV_TREE_NODE * pTree);



//! \brief Convert the Ingenico internal tags to the MCW defined tags.
//!	\param[in] nTagToConvert Tag to be converted.
//!	\return The converted tag if recognized, \a nTagToConvert else.

int ClessSample_DataExchange_McwTagConversion (const int nTagToConvert);


int ClessSample_DataExchange_ParseTlv (T_BER_TLV_DECODE_STRUCT * pBerTlvStruct, BER_TLV_TAG * pReadTag, BER_TLV_LENGTH * pReadLength, BER_TLV_VALUE * pReadValue, int * pBytesRead);


//! \brief Set to indicate if a matching DEK Signal was returned.
//! \param[in] bDEKMatching returned DEK Signal is matching or not.

void ClessSample_DataExchange_SetDEKSignalStatus (const int bDEKMatching);


//! \brief Check if DEK Signal matched.
//! \return TRUE DEK Signal matched, FALSE DEK Signal did not match.

int ClessSample_DataExchange_GetDEKSignalStatus (void);


#endif // __CLESS_SAMPLE_DATAEXCHANGE_H__INCLUDED__
