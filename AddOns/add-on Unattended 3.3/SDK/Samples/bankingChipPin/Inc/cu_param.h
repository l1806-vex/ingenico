/**
* \file cu_param.h
* \brief This module contains the functions needed for parameters management.
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

#ifndef CU_PARAM_H
#define CU_PARAM_H

//! \addtogroup Group_param
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

//! \defgroup ParamType Definitions for parameters management.
//! @{

#define C_PARAM_INIT					0		//!< Default & parameter files values.
#define C_PARAM_DEFAULT					1		//!< Default values.
#define C_PARAM_DEFAULT_ICS				2		//!< Default values only for ICS parameters.
#define C_PARAM_ONLY_DEFAULT_AID		3		//!< Load default AID values in pTreeParam TLVStruct and save parameters in param.par file.
#define C_PARAM_ONLY_DEFAULT_AID_EVAL	4		//!< Load default EVAL AID values in pTreeParam TLVStruct and save parameters in param.par file.
#define C_PARAM_ONLY_DEFAULT_AID_VISA	5		//!< Load default VISA AID values in pTreeParam TLVStruct and save parameters in param.par file.
#define C_PARAM_ONLY_DEFAULT_ICS		6		//!< Load default ICS values in pTreeParam TLVStruct and save parameters in param.par file.
#define C_PARAM_FILE_TLVTSERIAL			7		//!< Parameter file(s) TLVTree serial format.
#define C_PARAM_FILE_XML				8		//!< Parameter file(s) XML format.
#define C_PARAM_INIT_APLI				9		//!< Reset application structure used to store specific application tags.
#define C_PARAM_INIT_DEFAULT			10		//!< Reset application structure used to store specific default application tags.

//! @}

/* Init Type for files access : */

#define C_SHA_BUFF_LENGTH				512

//! \addtogroup ParamType
//! @{

#define C_AID1_PARAM					"AID1.PAR"		//!< Name of the AID1 parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_AID2_PARAM					"AID2.PAR"		//!< Name of the AID2 parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_AID3_PARAM					"AID3.PAR"		//!< Name of the AID3 parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_AID4_PARAM					"AID4.PAR"		//!< Name of the AID4 parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_AID5_PARAM					"AID5.PAR"		//!< Name of the AID5 parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_ICS0_PARAM					"ICS.PAR"		//!< Name of the ICS parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_ICS1_PARAM					"ICS1.PAR"		//!< Name of the ICS1 parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_ICS2_PARAM					"ICS2.PAR"		//!< Name of the ICS2 parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_ICS3_PARAM					"ICS3.PAR"		//!< Name of the ICS3 parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_ICS4_PARAM					"ICS4.PAR"		//!< Name of the ICS4 parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_ICS5_PARAM					"ICS5.PAR"		//!< Name of the ICS5 parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_CAKEYS_PARAM					"CAKEYS.PAR"	//!< Name of the CAKEYS parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_KREVOK_PARAM					"KREVOK.PAR"	//!< Name of the KREVOK parameter file. This file can be loaded individually after global parameter file EMVCUST.PAR (xml format) to keep the compatibility with previous management.
#define C_BLACKL_PARAM					"BLACKL.PAR"	//!< Name of the BLACKL parameter file. This file is only managed individually.
#define C_FILE_PARAM					"PARAM.PAR"		//!< Name of the PARAM parameter file. This file is used to save the current parameter configuration in case of power failure.
#define C_FILE_PARAM_XML				"EMVCUST.PAR"	//!< Name of the EMVCUST parameter file. This file contains a parameter list to configure the terminal (AID1, AID2, ICS1, ICS2, ...). When this file is loaded, the PARAM.PAR file is initialized with its content.

#define C_AID_NAME						"AID"			//!< Root of AIDx file name.
#define C_ICS_NAME						"ICS"			//!< Root of ICSx file name.
#define C_CAKEYS_NAME					"CAKEYS"		//!< Root of CAKEYS.PAR file name.
#define C_KREVOK_NAME					"KREVOK"		//!< Root of KREVOK.PAR file name.
#define C_BLACKL_NAME					"BLACKL"		//!< Root of BLACKL.PAR file name.
#define C_FILE_NAME_XML					"EMVCUST"		//!< Root of EMVCUST.PAR file name.

//! @}


//! \defgroup AidMgt Definitions for application identifier management.
//! @{

#define NB_AID_MAX						5		//!< Maximum number of AID.
#define NB_KEY_PER_AID					16		//!< Maximum number of keys per RID (EMV 2000).
#define LG_RID							5		//!< Root length of AID.
#define MAX_NB_TAG_FOR_REVOKED_CA		5		//!< Maximum number of tags for a revoked CA.

//! @} // end of AidMgt


//! \defgroup WorkType Parameter text file format
//! @{

#define C_WORK_FILE_TO_BIN				0		//!< Input file will be only one file.
#define C_WORK_BIN_TO_FILE				1		//!< Not used.
#define C_WORK_FILES_TO_BIN				2		//!< Input files may be AIDX.PAR, CAKEYS.PAR, KREVOK.PAR, ICSX.PAR.
#define C_WORK_BIN_TO_FILES				3		//!< Not used.

//! @} // end of WorkType

//! \defgroup TagType Definitions of tag types.
//! @{

#define C_TAG_TYPE_HEXA_BYTE			0		//!< The data of the tag is one hexadecimal byte.
#define C_TAG_TYPE_BUF_BYTE				1		//!< The data of the tag is a byte buffer.
#define C_TAG_TYPE_BUF_BYTE_WITH_MASQ	2		//!< The data of the tag is a byte buffer to be masked.
#define C_TAG_TYPE_BOOLEAN				3		//!< The data of the tag is a boolean value.
#define C_TAG_TYPE_TXT					4		//!< The data of the tag is a text value.

//! @} // end of TagType


//! \defgroup KeyMgt Definitions for keys management.
//! @{

#define MAX_FILE_REVOK_LG				60				//!< Buffer maximum length for a revoked CA in CAREVOK file.
#define NB_MAX_REVOKED_PER_TAG			30				//!< Maximum number of revoked CA per TAG.
#define NB_CAKEY_REVOKED_PER_RID		(NB_MAX_REVOKED_PER_TAG * MAX_NB_TAG_FOR_REVOKED_CA)	//!< Maximum number of revoked CA per RID.
#define NB_MAX_ALL_REVOKED_CA			(NB_CAKEY_REVOKED_PER_RID * NB_AID_MAX)					//!< Maximum number of revoked CA. 

//! @} // end of KeyMgt

//! \defgroup FileOrder Definitions for parameter file management.
//! @{

#define C_MGT_PARAM_PAR_FILE			1				//!< Manage only PARAM.PAR parameter file.
#define C_MGT_PARAM_PAR_FILE_FIRST		2				//!< Manage PARAM.PAR parameter file first and if file not present, manage AIDx, CAREVOK...PAR files.
#define C_MGT_TXT_PAR_FILES				3				//!< Manage AIDx, CAREVOK, ICSx...PAR files.

//! @} // end of FileOrder

#define C_NB_MAX_TXT_FILE				8				//!< Maximum number of txt files used for parameters.


//! \defgroup TagMgt Definitions for tag management.
//! @{

#define C_TAG_AID						0x1000				//!< AID node number used when updating parameter TLV tree.
#define C_TAG_AID1						C_TAG_AID + 1		//!< AID1 node number of parameter TLV tree. The TLV tree is updated at loading of AID1.PAR file.
#define C_TAG_AID2						C_TAG_AID + 2		//!< AID2 node number of parameter TLV tree. The TLV tree is updated at loading of AID2.PAR file.
#define C_TAG_AID3						C_TAG_AID + 3		//!< AID3 node number of parameter TLV tree. The TLV tree is updated at loading of AID3.PAR file.
#define C_TAG_AID4						C_TAG_AID + 4		//!< AID4 node number of parameter TLV tree. The TLV tree is updated at loading of AID4.PAR file.
#define C_TAG_AID5						C_TAG_AID + 5		//!< AID5 node number of parameter TLV tree. The TLV tree is updated at loading of AID5.PAR file.

#define C_TAG_CAKEYS					0x1100				//!< CAKEYS node number of parameter TLV tree. The TLV tree is updated at loading of CAKEYS.PAR file.

#define C_TAG_CAREVOK					0x1200				//!< CAREVOK node number of parameter TLV tree. The TLV tree is updated at loading of CAREVOK.PAR file.

#define C_TAG_ICS						0x1300				//!< ICS node number used when updating parameter TLV tree.
#define C_TAG_ICS0						C_TAG_ICS + 1		//!< ICS0 node number of parameter TLV tree. The TLV tree is updated at loading of ICS.PAR file.
#define C_TAG_ICS1						C_TAG_ICS + 2		//!< ICS1 node number of parameter TLV tree. The TLV tree is updated at loading of ICS1.PAR file.
#define C_TAG_ICS2						C_TAG_ICS + 3		//!< ICS2 node number of parameter TLV tree. The TLV tree is updated at loading of ICS2.PAR file.
#define C_TAG_ICS3						C_TAG_ICS + 4		//!< ICS3 node number of parameter TLV tree. The TLV tree is updated at loading of ICS3.PAR file.
#define C_TAG_ICS4						C_TAG_ICS + 5		//!< ICS4 node number of parameter TLV tree. The TLV tree is updated at loading of ICS4.PAR file.
#define C_TAG_ICS5						C_TAG_ICS + 6		//!< ICS5 node number of parameter TLV tree. The TLV tree is updated at loading of ICS5.PAR file.

#define C_TAG_XXXX						0x9F8BA0			// Dummy tag

#define	C_MARK_XXXX						"MARQ_XXXX"
#define	C_MARK_AID						"MARQ_AID"			//!< Label for AID node in parameter TLV tree.
#define	C_MARK_AID1						"MARQ_AID1"			//!< Label for AID1 node in parameter TLV tree.
#define	C_MARK_AID2						"MARQ_AID2"			//!< Label for AID2 node in parameter TLV tree.
#define	C_MARK_AID3						"MARQ_AID3"			//!< Label for AID3 node in parameter TLV tree.
#define	C_MARK_AID4						"MARQ_AID4"			//!< Label for AID4 node in parameter TLV tree.
#define	C_MARK_AID5						"MARQ_AID5"			//!< Label for AID5 node in parameter TLV tree.
#define	C_MARK_CAKEYS					"MARQ_CAKEYS"		//!< Label for CAKEYS node in parameter TLV tree.
#define	C_MARK_CAREVOK					"MARQ_CAREVOK"		//!< Label for CAREVOK node in parameter TLV tree.
#define	C_MARK_ICS						"MARQ_ICS"			//!< Label for ICS node in parameter TLV tree.
#define	C_MARK_ICS0						"MARQ_ICS0"			//!< Label for ICS0 node in parameter TLV tree.
#define	C_MARK_ICS1						"MARQ_ICS1"			//!< Label for ICS1 node in parameter TLV tree.
#define	C_MARK_ICS2						"MARQ_ICS2"			//!< Label for ICS2 node in parameter TLV tree.
#define	C_MARK_ICS3						"MARQ_ICS3"			//!< Label for ICS3 node in parameter TLV tree.
#define	C_MARK_ICS4						"MARQ_ICS4"			//!< Label for ICS4 node in parameter TLV tree.
#define	C_MARK_ICS5						"MARQ_ICS5"			//!< Label for ICS5 node in parameter TLV tree.

//! @} // end of TagMgt


/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

typedef unsigned char lst_Tag_RevokCA[255];					

typedef struct 
{
	lst_Tag_RevokCA revoked_CA[MAX_NB_TAG_FOR_REVOKED_CA];
	unsigned short  Taglength[MAX_NB_TAG_FOR_REVOKED_CA];

} T_CUSERV_lst_tagCArevok;

typedef struct
{
	unsigned char  rid[LG_RID];
	unsigned char  index[1];
	unsigned int   length;
	unsigned char  modulus[255];
	unsigned char  exponent[3];
	unsigned short exponentlength;
	unsigned char  expir_date[3];
} CA_PUB_KEY;

typedef struct
{
	unsigned char rid[LG_RID];
	unsigned char index[1];
	unsigned char serial_number[3];
}CA_REVOK;


#ifdef FILE_H

const unsigned char ay_Mask_Tc[]  = {0x00, 0xF8, 0xC8};
const unsigned char ay_Mask_Atc[] = {0xF0, 0x00, 0x00, 0x00, 0x00};

//const struct Struct_TagList FirstTagList[] =
const Struct_TagList FirstTagList[] = {
	{TAG_TERMINAL_TYPE,                      C_TAG_TYPE_HEXA_BYTE,   NULL},    // Terminal Type
	{TAG_TERMINAL_CAPABILITIES,              C_TAG_TYPE_BUF_BYTE,    NULL},    // Terminal Capabilities
	{TAG_TERMINAL_COUNTRY_CODE,              C_TAG_TYPE_BUF_BYTE,    NULL},    // Terminal country code
	{TAG_TRANSACTION_CURRENCY_CODE,          C_TAG_TYPE_BUF_BYTE,    NULL},    // Terminal currency
	{TAG_ADD_TERMINAL_CAPABILITIES,          C_TAG_TYPE_BUF_BYTE,    NULL},    // Additionnal Terminal Capabilities

	// Other
	{TAG_USE_PSE,                             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARDHOLDER_CONFIRMATION,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PREFERRED_DISPLAY_ORDER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_MULTILANG_SUPPORTED,         C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_REVOK_SUPPORTED,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PIN_BYPASS,                  C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_GETDATA_PIN_TRY_COUNTER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_TRANSACTION_LOG,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_EXCEPTION_FILE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ONLINE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ACCEPTANCE,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_ADVICE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ISSUER_REFERRAL,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARD_REFERRAL,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_BATCH_CAPTURE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_CAPTURE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_POS_ENTRY_MODE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_POS_ENTRY_MODE_CODE,                 C_TAG_TYPE_HEXA_BYTE,  NULL},
	{TAG_CUST_IS_PINPAD,                      C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_AMOUNT_PIN_SAME,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_DDOL,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FLOOR_LIMIT_CHECKING,        C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_RANDOM_TRANSACTION_SELECT,   C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_VELOCITY_CHECKING,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_TDOL,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_TRM_OVERPASS_AIP,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_SKIP_DEFAULT,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_SKIP_ONLINE,                 C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ODA_PROCESSING,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ACCOUNT_TYPE,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_PSE_ALGO,                            C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_DETECT_FAIL_PRIOR_TAA,          C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_CDA_NEVER_REQUEST_ARQC_1GENAC,  C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_CDA_NEVER_REQUEST_ONLINE_2GENAC,C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_SUBSEQUENT_BYPASS_PIN,          C_TAG_TYPE_BOOLEAN,    NULL}
};


//const struct Struct_TagList MajorTagList[] =
const Struct_TagList MajorTagList[] =
{
	{TAG_TERMINAL_TYPE,                       C_TAG_TYPE_HEXA_BYTE,  NULL},                        // Terminal Type
	{TAG_TERMINAL_CAPABILITIES,               C_TAG_TYPE_BUF_BYTE,   (unsigned char*)ay_Mask_Tc},  // Terminal Capabilities
	{TAG_ADD_TERMINAL_CAPABILITIES,           C_TAG_TYPE_BUF_BYTE,   (unsigned char*)ay_Mask_Atc}, // Additionnal Terminal Capabilities
	// Other
	{TAG_USE_PSE,                             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARDHOLDER_CONFIRMATION,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PREFERRED_DISPLAY_ORDER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_REVOK_SUPPORTED,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PIN_BYPASS,                  C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_GETDATA_PIN_TRY_COUNTER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_TRANSACTION_LOG,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_EXCEPTION_FILE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ONLINE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ACCEPTANCE,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_ADVICE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ISSUER_REFERRAL,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARD_REFERRAL,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_BATCH_CAPTURE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_CAPTURE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PINPAD,                      C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_AMOUNT_PIN_SAME,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_DDOL,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FLOOR_LIMIT_CHECKING,        C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_RANDOM_TRANSACTION_SELECT,   C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_VELOCITY_CHECKING,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_TDOL,                C_TAG_TYPE_BOOLEAN,    NULL}
};
const Struct_TagList FirstTagListEntire[] = {
	{TAG_TERMINAL_TYPE,                      C_TAG_TYPE_HEXA_BYTE,   NULL},    // Terminal Type
	{TAG_TERMINAL_CAPABILITIES,              C_TAG_TYPE_BUF_BYTE,    NULL},    // Terminal Capabilities
	{TAG_TERMINAL_COUNTRY_CODE,              C_TAG_TYPE_BUF_BYTE,    NULL},    // Terminal country code
	{TAG_TRANSACTION_CURRENCY_CODE,          C_TAG_TYPE_BUF_BYTE,    NULL},    // Terminal currency
	{TAG_ADD_TERMINAL_CAPABILITIES,          C_TAG_TYPE_BUF_BYTE,    NULL},    // Additionnal Terminal Capabilities

	// Other
	{TAG_USE_PSE,                             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARDHOLDER_CONFIRMATION,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PREFERRED_DISPLAY_ORDER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_MULTILANG_SUPPORTED,         C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_REVOK_SUPPORTED,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PIN_BYPASS,                  C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_GETDATA_PIN_TRY_COUNTER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_TRANSACTION_LOG,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_EXCEPTION_FILE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ONLINE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ACCEPTANCE,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_ADVICE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ISSUER_REFERRAL,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARD_REFERRAL,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_BATCH_CAPTURE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_CAPTURE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_POS_ENTRY_MODE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_POS_ENTRY_MODE_CODE,                 C_TAG_TYPE_HEXA_BYTE,  NULL},
	{TAG_CUST_IS_PINPAD,                      C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_AMOUNT_PIN_SAME,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_DDOL,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FLOOR_LIMIT_CHECKING,        C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_RANDOM_TRANSACTION_SELECT,   C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_VELOCITY_CHECKING,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_TDOL,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_TRM_OVERPASS_AIP,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_SKIP_DEFAULT,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_SKIP_ONLINE,                 C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ODA_PROCESSING,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ACCOUNT_TYPE,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_PSE_ALGO,                            C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_DETECT_FAIL_PRIOR_TAA,          C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_CDA_NEVER_REQUEST_ARQC_1GENAC,  C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_CDA_NEVER_REQUEST_ONLINE_2GENAC,C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_SUBSEQUENT_BYPASS_PIN,          C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_AMOUNT_UNKNOWN_BEFORE_CVM,   C_TAG_TYPE_BOOLEAN,    NULL}
};
const Struct_TagList FirstTagListEntireFull[] = {
	{TAG_TERMINAL_TYPE,                      C_TAG_TYPE_HEXA_BYTE,   NULL},    // Terminal Type
	{TAG_TERMINAL_CAPABILITIES,              C_TAG_TYPE_BUF_BYTE,    NULL},    // Terminal Capabilities
	{TAG_TERMINAL_COUNTRY_CODE,              C_TAG_TYPE_BUF_BYTE,    NULL},    // Terminal country code
	{TAG_TRANSACTION_CURRENCY_CODE,          C_TAG_TYPE_BUF_BYTE,    NULL},    // Terminal currency
	{TAG_ADD_TERMINAL_CAPABILITIES,          C_TAG_TYPE_BUF_BYTE,    NULL},    // Additionnal Terminal Capabilities

	// Other
	{TAG_USE_PSE,                             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARDHOLDER_CONFIRMATION,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PREFERRED_DISPLAY_ORDER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_MULTILANG_SUPPORTED,         C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_REVOK_SUPPORTED,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PIN_BYPASS,                  C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_GETDATA_PIN_TRY_COUNTER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_TRANSACTION_LOG,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_EXCEPTION_FILE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ONLINE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ACCEPTANCE,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_ADVICE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ISSUER_REFERRAL,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARD_REFERRAL,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_BATCH_CAPTURE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_CAPTURE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_POS_ENTRY_MODE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_POS_ENTRY_MODE_CODE,                 C_TAG_TYPE_HEXA_BYTE,  NULL},
	{TAG_CUST_IS_PINPAD,                      C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_AMOUNT_PIN_SAME,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_DDOL,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FLOOR_LIMIT_CHECKING,        C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_RANDOM_TRANSACTION_SELECT,   C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_VELOCITY_CHECKING,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_TDOL,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_TRM_OVERPASS_AIP,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_SKIP_DEFAULT,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_SKIP_ONLINE,                 C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ODA_PROCESSING,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ACCOUNT_TYPE,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_PSE_ALGO,                            C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_DETECT_FAIL_PRIOR_TAA,          C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_CDA_NEVER_REQUEST_ARQC_1GENAC,  C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_CDA_NEVER_REQUEST_ONLINE_2GENAC,C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_SUBSEQUENT_BYPASS_PIN,          C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_AMOUNT_UNKNOWN_BEFORE_CVM,   C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_SELECTABLE_KERNEL,			  C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DELETABLE_TAC,				  C_TAG_TYPE_BOOLEAN,    NULL}
};


//const struct Struct_TagList MajorTagList[] =
const Struct_TagList MajorTagListEntire[] =
{
	{TAG_TERMINAL_TYPE,                       C_TAG_TYPE_HEXA_BYTE,  NULL},                        // Terminal Type
	{TAG_TERMINAL_CAPABILITIES,               C_TAG_TYPE_BUF_BYTE,   (unsigned char*)ay_Mask_Tc},  // Terminal Capabilities
	{TAG_ADD_TERMINAL_CAPABILITIES,           C_TAG_TYPE_BUF_BYTE,   (unsigned char*)ay_Mask_Atc}, // Additionnal Terminal Capabilities
	// Other
	{TAG_USE_PSE,                             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARDHOLDER_CONFIRMATION,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PREFERRED_DISPLAY_ORDER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_REVOK_SUPPORTED,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PIN_BYPASS,                  C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_GETDATA_PIN_TRY_COUNTER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_TRANSACTION_LOG,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_EXCEPTION_FILE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ONLINE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ACCEPTANCE,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_ADVICE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ISSUER_REFERRAL,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARD_REFERRAL,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_BATCH_CAPTURE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_CAPTURE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PINPAD,                      C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_AMOUNT_PIN_SAME,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_DDOL,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FLOOR_LIMIT_CHECKING,        C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_RANDOM_TRANSACTION_SELECT,   C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_VELOCITY_CHECKING,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_TDOL,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_AMOUNT_UNKNOWN_BEFORE_CVM,   C_TAG_TYPE_BOOLEAN,    NULL}

};
//const struct Struct_TagList MajorTagList[] =
const Struct_TagList MajorTagListEntireFull[] =
{
	{TAG_TERMINAL_TYPE,                       C_TAG_TYPE_HEXA_BYTE,  NULL},                        // Terminal Type
	{TAG_TERMINAL_CAPABILITIES,               C_TAG_TYPE_BUF_BYTE,   (unsigned char*)ay_Mask_Tc},  // Terminal Capabilities
	{TAG_ADD_TERMINAL_CAPABILITIES,           C_TAG_TYPE_BUF_BYTE,   (unsigned char*)ay_Mask_Atc}, // Additionnal Terminal Capabilities
	// Other
	{TAG_USE_PSE,                             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARDHOLDER_CONFIRMATION,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PREFERRED_DISPLAY_ORDER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_REVOK_SUPPORTED,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PIN_BYPASS,                  C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_GETDATA_PIN_TRY_COUNTER,     C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_TRANSACTION_LOG,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_EXCEPTION_FILE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ONLINE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FORCED_ACCEPTANCE,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_ADVICE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ISSUER_REFERRAL,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_CARD_REFERRAL,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_BATCH_CAPTURE,               C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_ONLINE_CAPTURE,              C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_PINPAD,                      C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_AMOUNT_PIN_SAME,             C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_DDOL,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_FLOOR_LIMIT_CHECKING,        C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_RANDOM_TRANSACTION_SELECT,   C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_VELOCITY_CHECKING,           C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DEFAULT_TDOL,                C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_AMOUNT_UNKNOWN_BEFORE_CVM,   C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_SELECTABLE_KERNEL,			  C_TAG_TYPE_BOOLEAN,    NULL},
	{TAG_CUST_IS_DELETABLE_TAC,				  C_TAG_TYPE_BOOLEAN,    NULL}

};
/* Default parameters */
const char DefaultParam[] =
{
	"	<?xml version=\"1.0\" standalone=\"yes\" ?>"
	"	<!-- Fichier de parametres base -->"
	""
	"	<tlvtree ver=\"1.0\">"
	""
	"	<node tag=\"0x0\">"
	"		<node tag=\"0x1000\">                                <!-- C_TAG_AID -->"
	""
	"			<node tag=\"0x1001\">"
	"				<!-- AID1.0 file content -->"
	"				<node tag=\"0x9FFF00\"> 41 49 44 31 </node>            <!-- AID1 Parameters -->"
	"				<node tag=\"0x9F06\"> 07 B0 12 34 56 78 12 34 </node>"
	"				<node tag=\"0x9F1A\"> 02 50 </node>                    <!-- Country code -->"
	"				<node tag=\"0x5F2A\"> 09 78 </node>                    <!-- Currency Codef -->"
	"				<node tag=\"0x5F36\"> 02 </node>                       <!-- Currency Exponent -->"
	"				<node tag=\"0x9F812B\"> 00 00 00 05 </node>            <!-- Threshold Value -->"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>               <!-- Default DDOL -->"
	"				<node tag=\"0x9F8125\"> 9F 02 06 5F 2A 02 9A 03 9C 01 95 05 9F 37 04 </node>   <!-- Default TDOL -->"
	"				<node tag=\"0x9F8126\"> 00 </node>                     <!-- Max percentage for biased random selection -->"
	"				<node tag=\"0x9F8127\"> 00 </node>                     <!-- Target percentage for biased random selection -->"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>         <!-- TAC Default -->"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>         <!-- TAC Denial -->"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>         <!-- TAC Online -->"
	"				<node tag=\"0x9F09\"> 00 02 </node>                    <!-- Version Number -->"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>              <!-- Floor Limit -->"
	"				<node tag=\"0x9F841D\"> 00 </node>                     <!-- ASI -->"
	"			</node>"
#if 0
	"		    <node tag=\"0x1002\">"
	"				<!--  AID1_EVAL file content -->"
	"				<node tag=\"0x9FFF00\"> 41 49 44 31 </node>        <!-- AID1_EVAL Parameters -->"
	"				<node tag=\"0x9F06\"> 07 B0 12 34 56 78 12 34 </node>"
	"				<node tag=\"0x9F1A\"> 00 56 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 01 F4 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 08 02 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 00 02 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F841D\"> 00 </node>"
	"		   </node>"
#endif /* 0 */
	""
	"			<node tag=\"0x1002\">"
	"				<!-- AID2.0 file content -->"
	"				<node tag=\"0x9FFF00\"> 4D 61 73 74 65 72 43 61 72 64 </node> <!-- Master Card -->"
	"				<node tag=\"0x9F06\"> 07 A0 00 00 00 04 10 10 </node>"
	"				<node tag=\"0x9F1A\"> 09 78 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 00 05 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 08 02 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 00 02 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F8145\"> 31 38 </node>"
	"				<node tag=\"0x9F841D\"> 00 </node>"
	"			</node>"
#if 0
	"			<node tag=\"0x1004\">"
	"				<!-- AID2_EVAL.0 file content -->"
	"				<node tag=\"0x9FFF00\"> 4D 61 73 74 65 72 43 61 72 64 </node>"
	"				<node tag=\"0x9F06\"> 07 A0 00 00 00 04 10 10 </node>"
	"				<node tag=\"0x9F1A\"> 00 56 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 01 F4 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 08 02 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 00 02 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F841D\"> 00 </node>"
	"			</node>"
#endif /* 0 */
	""
	"			<node tag=\"0x1003\">"
	"				<!-- AID3.0 VISA file content -->"
	"				<node tag=\"0xx9FFF00\"> 56 53 44 43 </node>               <!-- VSDC -->"
	"				<node tag=\"0x9F06\"> 07 A0 00 00 00 03 10 10 </node>"
	"				<node tag=\"0x9F1A\"> 09 78 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 00 40 </node>"
	"				<node tag=\"0x9F8125\"> 9F 02 06 5F 2A 02 9A 03 9C 01 95 05 9F 37 04 </node>"
	"				<node tag=\"0x9F8126\"> 50 </node>"
	"				<node tag=\"0x9F8127\"> 20 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F01\"> 45 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 00 8C </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F16\"> 01 20 00 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F15\"> 61 11 </node>"
	"				<node tag=\"0x9F7A\"> 01 </node>"
	"				<node tag=\"0x9F841D\"> 01 </node>"
	"			</node>"
	""
#if 0
	"			<node tag=\"0x1006\">"
	"				<!-- AID3.0 EVAL file content. Settings done according to Visa 1.4.0 -->"
	"				<node tag=\"0x9FFF00\"> 41 49 44 33 </node>"
	"				<node tag=\"0x9F06\"> 05 A0 00 00 00 10 </node>"
	"				<node tag=\"0x9F1A\"> 00 56 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 01 F4 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 08 02 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 00 02 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F841D\"> 01 </node>"
	"			</node>"
#endif /* 0 */
	""
	"			<node tag=\"0x1004\">"
	"				<!-- AID4.0 file content -->"
	"				<node tag=\"0xx9FFF00\"> 4D 61 65 73 74 72 6F </node>    <!-- MaestroParameters -->"
	"				<node tag=\"0x9F06\"> 07 A0 00 00 00 99 90 90 </node>"
	"				<node tag=\"0x9F1A\"> 09 78 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 00 05 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 08 02 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 00 02 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F841D\"> 01 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1005\">"
	"				<!-- AID5.0 file content -->"
	"				<node tag=\"0x9FFF00\"> 41 49 44 33 </node>    <!-- VisaElectronParameters -->"
	"				<node tag=\"0x9F06\"> 07 A0 00 00 00 03 20 10 </node>"
	"				<node tag=\"0x9F1A\"> 09 78 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 00 05 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 02 06 5F 2A 02 9A 03 9C 01 95 05 9F 37 04 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 01 40 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F841D\"> 01 </node>"
	"			</node> <!-- End node 1008 -->"
	"		</node> <!-- End node 1000 -->"
	""
	""
	"		<node tag=\"0x1100\">                  <!-- C_TAG_CAKEYS -->"
	""
	"			<node tag=\"0x1101\">"
	"				<!-- CAKEYS file content -->"
	"				<node tag=\"0x9F06\"> A0 00 00 00 42 </node>"
	"				<node tag=\"0x9F22\"> 03 </node>"
	"				<node tag=\"0x9F8123\"> E5 5D E6 E6 78 72 F2 50 F9 F9 EE 57 75 E5 1A"
	"				                        02 B8 41 A9 AA 78 20 29 67 54 ED D7 1F 02 C2"
	"				                        E4 FD 31 1B 39 D2 9E 8A 3A E9 34 9B BB DF D5"
	"				                        F4 37 BA 73 4F 1A F1 0C CA 21 1E E2 D5 46 F4"
	"				                        1B 7B 09 04 36 D2 81 47 4E 08 F6 4D CA D8 12"
	"				                        11 FA 8B 66 2B 2D C2 AF 5F 55 AA BE D8 91 3A"
	"				                        7F C1 2D F7 1B B4 65 70 AA 42 83 6E A5 50 C9"
	"				                        7D 2A 05 5E 23 CD FA 04 EE 17 73 4A E6 D9 E9"
	"				                        74 38 56 3D 5F BB 5F 3F </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> 90 F4 CD 28 fd 06 86 07 06 40 CC 7A 60 28 77 29 45 7C 8B 10 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1102\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> 00 </node>"
	"				<node tag=\"0x9F8123\"> 9E 15 21 42 12 F6 30 8A CA 78 B8 0B D9 86 AC"
	"				                        28 75 16 84 6C 8D 54 8A 9E D0 A4 2E 7D 99 7C"
	"				                        90 2C 3E 12 2D 1B 9D C3 09 95 F4 E2 5C 75 DD"
	"				                        7E E0 A0 CE 29 3B 8C C0 2B 97 72 78 EF 25 6D"
	"				                        76 11 94 92 47 64 94 2F E7 14 FA 02 E4 D5 7F"
	"				                        28 2B A3 B2 B6 2C 9E 38 EF 65 17 82 3F 2C A8"
	"				                        31 BD DF 6D 36 3D </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> 8B B9 9A DD F7 B5 60 11 09 55 01 45 05 FB 6B 5F 83 08 CE 27 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1103\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> FB </node>"
	"				<node tag=\"0x9F8123\"> A9 54 8D FB 39 8B 48 12 3F AF 41 E6 CF A4 AE"
	"				                        1E 23 52 B5 18 AB 4B CE FE CD B0 B3 ED EC 09"
	"				                        02 87 D8 8B 12 25 9F 36 1C 1C C0 88 E5 F0 66"
	"				                        49 44 17 E8 EE 8B BF 89 91 E2 B3 2F F1 6F 99"
	"				                        46 97 84 2B 3D 6C B3 7A 2B B5 74 2A 44 0B 63"
	"				                        56 C6 2A A3 3D B3 C4 55 E5 9E DD F7 86 47 01"
	"				                        D0 3A 5B 83 EE 9E 9B D8 3A B9 33 02 AC 2D FE"
	"				                        63 E6 61 20 B0 51 CF 08 1F 56 32 6A 71 30 3D"
	"				                        95 2B B3 36 FF 12 61 0D </node>"
	"				<node tag=\"0x9F8122\"> 02 </node>"
	"				<node tag=\"0x9F8121\"> A5 4C B4 AE C9 BD 9D 4F 57 97 56 A2 B9 E0 9C DB 49 E4 77 E8 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1104\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> FC </node>"
	"				<node tag=\"0x9F8123\"> B3 7B FD 2A 96 74 AD 62 21 C1 A0 01 08 1C 62"
	"				                        65 3D C2 80 B0 A9 BD 05 2C 67 7C 91 3C E7 A0"
	"				                        D9 02 E7 7B 12 F4 D4 D7 90 37 B1 E9 B9 23 A8"
	"				                        BB 3F AC 3C 61 20 45 BB 39 14 F8 DF 41 E9 A1"
	"				                        B6 1B FA 5B 41 70 5A 69 1D 09 CE 6F 53 0F E4"
	"				                        8B 30 24 0D 98 F4 E6 92 FF D6 AA DB 87 24 3B"
	"				                        A8 59 7A B2 37 58 6E CF 25 8F 41 48 75 1B E5"
	"				                        DA 5A 3B E6 CC 34 BD </node>"
	"				<node tag=\"0x9F8122\"> 02 </node>"
	"				<node tag=\"0x9F8121\"> 74 75 55 21 F6 0C AC F9 D2 0E 75 99 57 D2 41 E1 2B E0 C9 57 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1105\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 97 </node>"
	"				<node tag=\"0x9F8123\"> AF 07 54 EA ED 97 70 43 AB 6F 41 D6 31 2A B1"
	"				                        E2 2A 68 09 17 5B EB 28 E7 0D 5F 99 B2 DF 18"
	"				                        CA E7 35 19 34 1B BB D3 27 D0 B8 BE 9D 4D 0E"
	"				                        15 F0 7D 36 EA 3E 3A 05 C8 92 F5 B1 9A 3E 9D"
	"				                        34 13 B0 D9 7E 7A D1 0A 5F 5D E8 E3 88 60 C0"
	"				                        AD 00 4B 1E 06 F4 04 0C 29 5A CB 45 7A 78 85"
	"				                        51 B6 12 7C 0B 29 </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> 80 01 CA 76 C1 20 39 55 E2 C6 28 41 CD 6F 20 10 87 E5 64 BF </node>"
	"			</node>"
	""
	"			<node tag=\"0x1106\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> FD </node>"
	"				<node tag=\"0x9F8123\"> B3 57 2B A4 9A E4 C7 B7 A0 01 9E 51 89 E1 42"
	"				                        CF CD ED 94 98 DD B5 F0 47 05 67 AB 0B A7 13"
	"				                        B8 DA 22 64 24 62 29 55 B5 4B 93 7A BF EF AA"
	"				                        D9 79 19 E3 77 62 1E 22 19 6A BC 14 19 D5 AD"
	"				                        C1 23 48 42 09 EA 7C B7 02 9E 66 A0 D5 4C 5B"
	"				                        45 C8 AD 61 5A ED B6 AE 9E 0A 2F 75 31 0E A8"
	"				                        96 12 87 24 12 45 </node>"
	"				<node tag=\"0x9F8122\"> 02 </node>"
	"				<node tag=\"0x9F8121\"> 62 31 89 46 5E 31 48 DD 2A C2 8E 19 34 91 58 03 AD 9A 60 E4 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1107\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> FE </node>"
	"				<node tag=\"0x9F8123\"> A6 53 EA C1 C0 F7 86 C8 72 4F 73 7F 17 29 97"
	"				                        D6 3D 1C 32 51 C4 44 02 04 9B 86 5B AE 87 7D"
	"				                        0F 39 8C BF BE 8A 60 35 E2 4A FA 08 6B EF DE"
	"				                        93 51 E5 4B 95 70 8E E6 72 F0 96 8B CD 50 DC"
	"				                        E4 0F 78 33 22 B2 AB A0 4E F1 37 EF 18 AB F0"
	"				                        3C 7D BC 58 13 AE AE F3 AA 77 97 BA 15 DF 7D"
	"				                        5B A1 CB AF 7F D5 20 B5 A4 82 D8 D3 FE E1 05"
	"				                        07 78 71 11 3E 23 A4 9A F3 92 65 54 A7 0F E1"
	"				                        0E D7 28 CF 79 3B 62 A1 </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> 9A 29 5B 05 FB 39 0E F7 92 3F 57 61 8A 9F DA 29 41 FC 34 E0 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1108\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> FF </node>"
	"				<node tag=\"0x9F8123\"> B8 55 CC 64 31 3A F9 9C 45 3D 18 16 42 EE 7D"
	"				                        D2 1A 67 D0 FF 50 C6 1F E2 13 BC DC 18 AF BC"
	"				                        D0 77 22 EF DD 25 94 EF DC 22 7D A3 DA 23 AD"
	"				                        CC 90 E3 FA 90 74 53 AC C9 54 C4 73 23 BE DC"
	"				                        F8 D4 86 2C 45 7D 25 F4 7B 16 D7 C3 50 2B E0"
	"				                        81 91 3E 5B 04 82 D8 38 48 40 65 DA 5F 66 59"
	"				                        E0 0A 9E 5D 57 0A DA 1E C6 AF 8C 57 96 00 75"
	"				                        11 95 81 FC 81 46 8D </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> B4 E7 69 CE CF 7A AC 47 83 F3 05 E0 B1 10 60 2A 07 A6 35 5B </node>"
	"			</node>"
	""
	"			<node tag=\"0x1109\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> FA </node>"
	"				<node tag=\"0x9F8123\"> 9C 6B E5 AD B1 0B 4B E3 DC E2 09 9B 4B 21 06 72 B8 96 56 EB A0 91 20"
	"				                        4F 61 3E CC 62 3B ED C9 C6 D7 7B 66 0E 8B AE EA 7F 7C E3 0F 1B 15 38"
	"				                        79 A4 E3 64 59 34 3D 1F E4 7A CD BD 41 FC D7 10 03 0C 2B A1 D9 46 15"
	"				                        97 98 2C 6E 1B DD 08 55 4B 72 6F 5E FF 79 13 CE 59 E7 9E 35 72 95 C3"
	"				                        21 E2 6D 0B 8B E2 70 A9 44 23 45 C7 53 E2 AA 2A CF C9 D3 08 50 60 2F"
	"				                        E6 CA C0 0C 6D DF 6B 8D 9D 9B 48 79 B2 82 6B 04 2A 07 F0 E5 AE 52 6A"
	"				                        3D 3C 4D 22 C7 2B 9E AA 52 EE D8 89 38 66 F8 66 38 7A C0 5A 13 99 </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> 0A BC AD AD 2C 75 58 CA 9C 70 81 AE 55 DD DC 71 4F 8D 45 F8 </node>"
	"			</node>"
	""
	"			<node tag=\"0x110A\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F9 </node>"
	"				<node tag=\"0x9F8123\"> A9 9A 6D 3E 07 18 89 ED 9E 3A 0C 39 1C 69 B0 B8 04 FC 16 0B 2B 4B DD"
	"				                        57 0C 92 DD 5A 0F 45 F5 3E 86 21 F7 C9 6C 40 22 42 66 73 5E 1E E1 B3"
	"				                        C0 62 38 AE 35 04 63 20 FD 8E 81 F8 CE B3 F8 B4 C9 7B 94 09 30 A3 AC"
	"				                        5E 79 00 86 DA D4 1A 6A 4F 51 17 BA 1C E2 43 8A 51 AC 05 3E B0 02 AE"
	"				                        D8 66 D2 C4 58 FD 73 35 90 21 A1 20 29 A0 C0 43 04 5C 11 66 4F E0 21"
	"				                        9E C6 3C 10 BF 21 55 BB 27 84 60 9A 10 64 21 D4 51 63 79 97 38 C1 C3"
	"				                        09 09 BB 6C 6F E5 2B BB 76 39 7B 97 40 CE 06 4A 61 3F F8 41 11 85 F0"
	"				                        88 42 A4 23 EA D2 0E DF FB FF 1C D6 C3 FE 0C 98 21 47 91 99 C2 6D 85"
	"				                        72 CC 8A FF F0 87 A9 C3 </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> 33 67 12 DC C2 85 54 80 9C 6A A9 B0 23 58 DE 6F 75 51 64 DB </node>"
	"			</node>"
	""
	"			<node tag=\"0x110B\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F8 </node>"
	"				<node tag=\"0x9F8123\"> A1 F5 E1 C9 BD 86 50 BD 43 AB 6E E5 6B 89 1E F7 45 9C 0A 24 FA 84 F9"
	"				                        12 7D 1A 6C 79 D4 93 0F 6D B1 85 2E 25 10 F1 8B 61 CD 35 4D B8 3A 35"
	"				                        6B D1 90 B8 8A B8 DF 04 28 4D 02 A4 20 4A 7B 6C B7 C5 55 19 77 A9 B3"
	"				                        63 79 CA 3D E1 A0 8E 69 F3 01 C9 5C C1 C2 05 06 95 92 75 F4 17 23 DD"
	"				                        5D 29 25 29 05 79 E5 A9 5B 0D F6 32 3F C8 E9 27 3D 6F 84 91 98 C4 99"
	"				                        62 09 16 6D 9B FC 97 3C 36 1C C8 26 E1 </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> F0 6E CC 6D 2A AE BF 25 9B 7E 75 5A 38 D9 A9 B2 4E 2F F3 DD </node>"
	"			</node>"
	""
	"			<node tag=\"0x110C\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F7 </node>"
	"				<node tag=\"0x9F8123\"> 94 EA 62 F6 D5 83 20 E3 54 C0 22 AD DC F0 55 9D 8C F2 06 CD 92 E8 69"
	"				                        56 49 05 CE 21 D7 20 F9 71 B7 AE A3 74 83 0E BE 17 57 11 5A 85 E0 88"
	"				                        D4 1C 6B 77 CF 5E C8 21 F3 0B 1D 89 04 17 BF 2F A3 1E 59 08 DE D5 FA"
	"				                        67 7F 8C 7B 18 4A D0 90 28 FD DE 96 B6 A6 10 98 50 AA 80 01 75 EA BC"
	"				                        DB BB 68 4A 96 C2 EB 63 79 DF EA 08 D3 2F E2 33 1F E1 03 23 3A D5 8D"
	"				                        CD B1 E6 E0 77 CB 9F 24 EA EC 5C 25 AF </node>"
	"				<node tag=\"0x9F8122\"> 01 00 01 </node>"
	"				<node tag=\"0x9F8121\"> EE B0 DD 9B 24 77 BE E3 20 9A 91 4C DB A9 4C 1C 4A 9B DE D9 </node>"
	"			</node>"
	""
	"			<node tag=\"0x110D\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F6 </node>"
	"				<node tag=\"0x9F8123\"> A2 5A 6B D7 83 A5 EF 6B 8F B6 F8 30 55 C2 60 F5 F9 9E A1 66 78 F3 B9"
	"				                        05 3E 0F 64 98 E8 2C 3F 5D 1E 8C 38 F1 35 88 01 7E 2B 12 B3 D8 FF 6F"
	"				                        50 16 7F 46 44 29 10 72 9E 9E 4D 1B 37 39 E5 06 7C 0A C7 A1 F4 48 7E"
	"				                        35 F6 75 BC 16 E2 33 31 51 65 CB 14 2B FD B2 5E 30 1A 63 2A 54 A3 37"
	"				                        1E BA B6 57 2D EE BA F3 70 F3 37 F0 57 EE 73 B4 AE 46 D1 A8 BC 4D A8"
	"				                        53 EC 3C C1 2C 8C BC 2D A1 83 22 D6 85 30 C7 0B 22 BD AC 35 1D D3 60"
	"				                        68 AE 32 1E 11 AB F2 64 F4 D3 56 9B B7 12 14 54 50 05 55 8D E2 60 83"
	"				                        C7 35 DB 77 63 68 17 2F E8 C2 F5 C8 5E 8B 5B 89 0C C6 82 91 1D 2D E7"
	"				                        1F A6 26 B8 81 7F CC C0 89 22 B7 03 86 9F 3B AE AC 14 59 D7 7C D8 53"
	"				                        76 BC 36 18 2F 42 38 31 4D 6C 42 12 FB DD 7F 23 D3 </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> 50 29 09 ED 54 5E 3C 8D BD 00 EA 58 2D 06 17 FE E9 F6 F6 84 </node>"
	"			</node>"
	""
	"			<node tag=\"0x110E\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F5 </node>"
	"				<node tag=\"0x9F8123\"> A6 E6 FB 72 17 95 06 F8 60 CC CA 8C 27 F9 9C EC D9 4C 7D 4F 31 91 D3"
	"				                        03 BB EE 37 48 1C 7A A1 5F 23 3B A7 55 E9 E4 37 63 45 A9 A6 7E 79 94"
	"				                        BD C1 C6 80 BB 35 22 D8 C9 3E B0 CC C9 1A D3 1A D4 50 DA 30 D3 37 66"
	"				                        2D 19 AC 03 E2 B4 EF 5F 6E C1 82 82 D4 91 E1 97 67 D7 B2 45 42 DF DE"
	"				                        FF 6F 62 18 55 03 53 20 69 BB B3 69 E3 BB 9F B1 9A C6 F1 C3 0B 97 D2"
	"				                        49 EE E7 64 E0 BA C9 7F 25 C8 73 D9 73 95 3E 51 53 A4 20 64 BB FA BF"
	"				                        D0 6A 4B B4 86 86 0B F6 63 74 06 C9 FC 36 81 3A 4A 75 F7 5C 31 CC A9"
	"				                        F6 9F 8D E5 9A DE CE F6 BD E7 E0 78 00 FC BE 03 5D 31 76 AF 84 73 E2"
	"				                        3E 9A A3 DF EE 22 11 96 D1 14 83 02 67 7C 72 0C FE 25 44 A0 3D B5 53"
	"				                        E7 F1 B8 42 7B A1 CC 72 B0 F2 9B 12 DF EF 4C 08 1D 07 6D 35 3E 71 88"
	"				                        0A AD FF 38 63 52 AF 0A B7 B2 8E D4 9E 1E 67 2D 11 F9 </node>"
	"				<node tag=\"0x9F8122\"> 01 00 01 </node>"
	"				<node tag=\"0x9F8121\"> C2 23 98 04 C8 09 81 70 BE 52 D6 D5 D4 15 9E 81 CE 84 66 BF </node>"
	"			</node>"
	""
	"			<node tag=\"0x110F\">"
	"				<node tag=\"0x9F06\"> B0 12 34 56 78 </node>"
	"				<node tag=\"0x9F22\"> F9 </node>"
	"				<node tag=\"0x9F8123\"> A6 E6 FB 72 17 95 06 F8 60 CC CA 8C 27 F9 9C EC D9 4C 7D 4F 31 91 D3"
	"				                        03 BB EE 37 48 1C 7A A1 5F 23 3B A7 55 E9 E4 37 63 45 A9 A6 7E 79 94"
	"				                        BD C1 C6 80 BB 35 22 D8 C9 3E B0 CC C9 1A D3 1A D4 50 DA 30 D3 37 66"
	"				                        2D 19 AC 03 E2 B4 EF 5F 6E C1 82 82 D4 91 E1 97 67 D7 B2 45 42 DF DE"
	"				                        FF 6F 62 18 55 03 53 20 69 BB B3 69 E3 BB 9F B1 9A C6 F1 C3 0B 97 D2"
	"				                        49 EE E7 64 E0 BA C9 7F 25 C8 73 D9 73 95 3E 51 53 A4 20 64 BB FA BF"
	"				                        D0 6A 4B B4 86 86 0B F6 63 74 06 C9 FC 36 81 3A 4A 75 F7 5C 31 CC A9"
	"				                        F6 9F 8D E5 9A DE CE F6 BD E7 E0 78 00 FC BE 03 5D 31 76 AF 84 73 E2"
	"				                        3E 9A A3 DF EE 22 11 96 D1 14 83 02 67 7C 72 0C FE 25 44 A0 3D B5 53"
	"				                        E7 F1 B8 42 7B A1 CC 72 B0 F2 9B 12 DF EF 4C 08 1D 07 6D 35 3E 71 88"
	"				                        0A AD FF 38 63 52 AF 0A B7 B2 8E D4 9E 1E 67 2D 11 F9 </node>"
	"				<node tag=\"0x9F8122\"> 01 00 01 </node>"
	"				<node tag=\"0x9F8121\"> AE AC A4 54 80 C8 83 4C B0 BE BD CC 57 0B 7B 2B 74 BB 4B 79 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1110\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F3 </node>"
	"				<node tag=\"0x9F8123\"> 98 F0 C7 70 F2 38 64 C2 E7 66 DF 02 D1 E8 33 DF F4 FF E9 2D 69 6E 16 42"
	"				                        F0 A8 8C 56 94 C6 47 9D 16 DB 15 37 BF E2 9E 4F DC 6E 6E 8A FD 1B 0E B7"
	"				                        EA 01 24 72 3C 33 31 79 BF 19 E9 3F 10 65 8B 2F 77 6E 82 9E 87 DA ED A9"
	"				                        C9 4A 8B 33 82 19 9A 35 0C 07 79 77 C9 7A FF 08 FD 11 31 0A C9 50 A7 2C"
	"				                        3C A5 00 2E F5 13 FC CC 28 6E 64 6E 3C 53 87 53 5D 50 95 14 B3 B3 26 E1"
	"				                        23 4F 9C B4 8C 36 DD D4 4B 41 6D 23 65 40 34 A6 6F 40 3B A5 11 C5 EF A3 </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> A6 9A C7 60 3D AF 56 6E 97 2D ED C2 CB 43 3E 07 E8 B0 1A 9A </node>"
	"				<!-- VISA Test Keys -->"
	"			</node>"
	""
	"			<node tag=\"0x1111\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 95 </node>"
	"				<node tag=\"0x9F8123\"> BE 9E 1F A5 E9 A8 03 85 29 99 C4 AB 43 2D B2 86"
	"				                        00 DC D9 DA B7 6D FA AA 47 35 5A 0F E3 7B 15 08"
	"				                        AC 6B F3 88 60 D3 C6 C2 E5 B1 2A 3C AA F2 A7 00"
	"				                        5A 72 41 EB AA 77 71 11 2C 74 CF 9A 06 34 65 2F"
	"				                        BC A0 E5 98 0C 54 A6 47 61 EA 10 1A 11 4E 0F 0B"
	"				                        55 72 AD D5 7D 01 0B 7C 9C 88 7E 10 4C A4 EE 12"
	"				                        72 DA 66 D9 97 B9 A9 0B 5A 6D 62 4A B6 C5 7E 73"
	"				                        C8 F9 19 00 0E B5 F6 84 89 8E F8 C3 DB EF B3 30"
	"				                        C6 26 60 BE D8 8E A7 8E 90 9A FF 05 F6 DA 62 7B </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> EE 15 11 CE C7 10 20 A9 B9 04 43 B3 7B 1D 5F 6E 70 30 30 F6 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1112\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 96 </node>"
	"				<node tag=\"0x9F8123\"> B7 45 86 D1 9A 20 7B E6 62 7C 5B 0A AF BC 44 A2 EC F5 A2 94"
	"				                        2D 3A 26 CE 19 C4 FF AE EE 92 05 21 86 89 22 E8 93 E7 83 82"
	"				                        25 A3 94 7A 26 14 79 6F B2 C0 62 8C E8 C1 1E 38 25 A5 6D 3B"
	"				                        1B BA EF 78 3A 5C 6A 81 F3 6F 86 25 39 51 26 FA 98 3C 52 16"
	"				                        D3 16 6D 48 AC DE 8A 43 12 12 FF 76 3A 7F 79 D9 ED B7 FE D7"
	"				                        6B 48 5D E4 5B EB 82 9A 3D 47 30 84 8A 36 6D 33 24 C3 02 70"
	"				                        32 FF 8D 16 A1 E4 4D 8D </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> 76 16 E9 AC 8B E0 14 AF 88 CA 11 A8 FB 17 96 7B 73 94 03 0E </node>"
	"			</node>"
	""
	"			<node tag=\"0x1113\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 98 </node>"
	"				<node tag=\"0x9F8123\"> CA 02 6E 52 A6 95 E7 2B D3 0A F9 28 19 6E ED C9 FA F4 A6 19"
	"				                        F2 49 2E 3F B3 11 69 78 9C 27 6F FB B7 D4 31 16 64 7B A9 E0"
	"				                        D1 06 A3 54 2E 39 65 29 2C F7 78 23 DD 34 CA 8E EC 7D E3 67"
	"				                        E0 80 70 89 50 77 C7 EF AD 93 99 24 CB 18 70 67 DB F9 2C B1"
	"				                        E7 85 91 7B D3 8B AC E0 C1 94 CA 12 DF 0C E5 B7 A5 02 75 AC"
	"				                        61 BE 7C 3B 43 68 87 CA 98 C9 FD 39 </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> E7 AC 9A A8 EE D1 B5 FF 1B D5 32 CF 14 89 A3 E5 55 75 72 C1 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1114\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 99 </node>"
	"				<node tag=\"0x9F8123\"> AB 79 FC C9 52 08 96 96 7E 77 6E 64 44 4E 5D CD D6 E1 36 11 87 4F 39"
	"				                        85 72 25 20 42 52 95 EE A4 BD 0C 27 81 DE 7F 31 CD 3D 04 1F 56 5F 74"
	"				                        73 06 EE D6 29 54 B1 7E DA BA 3A 6C 5B 85 A1 DE 1B EB 9A 34 14 1A F3"
	"				                        8F CF 82 79 C9 DE A0 D5 A6 71 0D 08 DB 41 24 F0 41 94 55 87 E2 03 59"
	"				                        BA B4 7B 75 75 AD 94 26 2D 4B 25 F2 64 AF 33 DE DC F2 8E 09 61 5E 93"
	"				                        7D E3 2E DC 03 C5 44 45 FE 7E 38 27 77 </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> 4ABFFD6B1C51212D05552E431C5B17007D2F5E6D </node>"
	"				<!-- VISA Production Keys -->"
	"			</node>"
	""
	"			<node tag=\"0x1115\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 01 </node>"
	"				<node tag=\"0x9F8123\"> C6 96 03 42 13 D7 D8 54 69 84 57 9D 1D 0F 0E A5 19 CF F8 DE FF C4 29"
	"				                        35 4C F3 A8 71 A6 F7 18 3F 12 28 DA 5C 74 70 C0 55 38 71 00 CB 93 5A"
	"				                        71 2C 4E 28 64 DF 5D 64 BA 93 FE 7E 63 E7 1F 25 B1 E5 F5 29 85 75 EB"
	"				                        E1 C6 3A A6 17 70 69 17 91 1D C2 A7 5A C2 8B 25 1C 7E F4 0F 23 65 91"
	"				                        24 90 B9 39 BC A2 12 4A 30 A2 8F 54 40 2C 34 AE CA 33 1A B6 7E 1E 79"
	"				                        B2 85 DD 57 71 B5 D9 FF 79 EA 63 0B 75 </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> D3 4A 6A 77 60 11 C7 E7 CE 3A EC 5F 03 AD 2F 8C FC 55 03 CC </node>"
	"			</node>"
	""
	"			<node tag=\"0x1116\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 03 </node>"
	"				<node tag=\"0x9F8123\"> B3 E5 E6 67 50 6C 47 CA AF B1 2A 26 33 81 93 50 84 66 97 DD"
	"				                        65 A7 96 E5 CE 77 C5 7C 62 6A 66 F7 0B B6 30 91 16 12 AD 28"
	"				                        32 90 9B 80 62 29 1B EC A4 6C D3 3B 66 A6 F9 C9 D4 8C ED 8B"
	"				                        4F C8 56 1C 8A 1D 8F B1 58 62 C9 EB 60 17 8D EA 2B E1 F8 22"
	"				                        36 FF CF F4 F3 84 3C 27 21 79 DC DD 38 4D 54 10 53 DA 6A 6A"
	"				                        0D 3C E4 8F DC 2D C4 E3 E0 EE E1 5F </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> FE 70 AB 3B 4D 5A 1B 99 24 22 8A DF 80 27 C7 58 48 3A 8B 7E </node>"
	"			</node>"
	""
	"			<node tag=\"0x1117\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 07 </node>"
	"				<node tag=\"0x9F8123\"> A8 9F 25 A5 6F A6 DA 25 8C 8C A8 B4 04 27 D9 27 B4 A1 EB 4D"
	"									    7E A3 26 BB B1 2F 97 DE D7 0A E5 E4 48 0F C9 C5 E8 A9 72 17"
	"									    71 10 A1 CC 31 8D 06 D2 F8 F5 C4 84 4A C5 FA 79 A4 DC 47 0B"
	"									    B1 1E D6 35 69 9C 17 08 1B 90 F1 B9 84 F1 2E 92 C1 C5 29 27"
	"									    6D 8A F8 EC 7F 28 49 20 97 D8 CD 5B EC EA 16 FE 40 88 F6 CF"
	"				                        AB 4A 1B 42 32 8A 1B 99 6F 92 78 B0 B7 E3 31 1C A5 EF 85 6C"
	"				                        2F 88 84 74 B8 36 12 A8 2E 4E 00 D0 CD 40 69 A6 78 31 40 43"
	"				                        3D 50 72 5F </node>"
	"				<node tag=\"0x9F8122\"> 03 </node>"
	"				<node tag=\"0x9F8121\"> B4 BC 56 CC 4E 88 32 49 32 CB C6 43 D6 89 8F 6F E5 93 B1 72 </node>"
	"			</node> <!-- End node -->"
	"		</node> <!-- End node 1100 -->"
	""
	""
	"		<node tag=\"0x1200\">                   <!-- C_TAG_CAREVOK -->"
	"			<!-- KREVOK default values -->"
	""
	"			<node tag=\"0x1201\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F8 </node>"
	"				<node tag=\"0x9F8424\"> 00 10 00 </node>"
	"			</node> <!-- End -->"
	""
	"			<node tag=\"0x1202\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F7 </node>"
	"				<node tag=\"0x9F8424\"> 00 10 01 </node>"
	"			</node> <!-- End node -->"
	""
	"			<node tag=\"0x1203\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 05 </node>"
	"				<node tag=\"0x9F22\"> F6 </node>"
	"				<node tag=\"0x9F8424\"> 00 10 02 </node>"
	"			</node> <!-- End node -->"
	""
	"			<node tag=\"0x1204\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F5 </node>"
	"				<node tag=\"0x9F8424\"> 00 10 03 </node>"
	"			</node> <!-- End node -->"
	"		</node> <!-- End node -->"
	""
	""
	"		<node tag=\"0x1300\">                                <!-- C_TAG_ICS -->"
	""
	"			<node tag=\"0x1301\">"
	"				<!-- ICS0 values -->"
	"				<node tag=\"0x9f8450\"> 44 45 46 41 55 4c 54 20 43 4f 4e 46 49 47 </node> <!-- DEFAULT CONFIG -->"
	"				<node tag=\"0x9F35\"> 22 </node>"
	"				<node tag=\"0x9F33\"> 60 F8 C8 </node>"
	"				<node tag=\"0x9F1A\"> 00 56 </node>    <!-- Default country : France, currency : Euro -->"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x9F40\"> E0 00 F0 F0 01 </node>"
	"				<node tag=\"0x9F8142\"> 01 </node>"
	"				<node tag=\"0x9F8195\"> 00 </node>"
	"				<node tag=\"0x9F844B\"> 01 </node>"
	"				<node tag=\"0x9F8440\"> 00 </node>"
	"				<node tag=\"0x9F8441\"> 01 </node>"
	"				<node tag=\"0x9F8442\"> 01 </node>"
	"				<node tag=\"0x9F840A\"> 01 </node>"
	"				<node tag=\"0x9F844D\"> 01 </node>"
	"				<node tag=\"0x9F8443\"> 01 </node>"
	"				<node tag=\"0x9F8444\"> 01 </node>"
	"				<node tag=\"0x9F844C\"> 01 </node>"
	"				<node tag=\"0x9F840E\"> 01 </node>"
	"				<node tag=\"0x9F840F\"> 01 </node>"
	"				<node tag=\"0x9F840B\"> 00 </node>"
	"				<node tag=\"0x9F8445\"> 01 </node>"
	"				<node tag=\"0x9F8446\"> 00 </node>"
	"				<node tag=\"0x9F8447\"> 00 </node>"
	"				<node tag=\"0x9F8448\"> 00 </node>"
	"				<node tag=\"0x9F844E\"> 01 </node>"
	"				<node tag=\"0x9F39\"> 81 </node>"
	"				<node tag=\"0x9F8449\"> 00 </node>"
	"				<node tag=\"0x9F844A\"> 01 </node>"
	"				<node tag=\"0x9F8452\"> 01 </node>"
	"				<node tag=\"0x9F8453\"> 01 </node>"
	"				<node tag=\"0x9F8454\"> 01 </node>"
	"				<node tag=\"0x9F8455\"> 01 </node>"
	"				<node tag=\"0x9f8456\"> 01 </node>"
	"				<node tag=\"0x9F841E\"> 00 </node>"
	"				<node tag=\"0x9F845A\"> 01 </node>"
	"				<node tag=\"0x9F845B\"> 01 </node>"
	"				<node tag=\"0x9F8458\"> 01 </node>"
	"				<node tag=\"0x9F8459\"> 00 </node>"
	"				<node tag=\"0x9F845C\"> 01 </node>"
	"				<node tag=\"0x9F845D\"> 00 </node>"
	"				<node tag=\"0x9F845E\"> 00 </node>"
	"				<node tag=\"0x9F8431\"> 65 6e 66 72 </node> <!-- enfr -->"
	"				<node tag=\"0x9F8460\"> 01 </node>"
	"				<node tag=\"0x9F8464\"> 00 </node>"
	"				<node tag=\"0x9F8465\"> 00 </node>"
	"				<node tag=\"0x9F8466\"> 00 </node>"
	"			</node> <!-- End node 9F8B91 -->"
	""
#if 0
	"			<node tag=\"0x1302\">"
	"				<!-- ICS1 values -->"
	"				<node tag=\"0x9f8450\"> 44 45 46 41 55 4c 54 20 34 4f 4e 46 49 47 </node> <!-- DEFAULT CONFIG -->"
	"				<node tag=\"0x9F35\"> 22 </node>"
	"				<node tag=\"0x9F33\"> 60 F8 C8 </node>"
	"				<node tag=\"0x9F1A\"> 00 56 </node>    <!-- Default country : France, currency : Euro -->"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x9F40\"> E0 00 F0 F0 01 </node>"
	"				<node tag=\"0x9F8142\"> 01 </node>"
	"				<node tag=\"0x9F8195\"> 00 </node>"
	"			</node> <!-- End node -->"
	""
	"			<node tag=\"0x1303\">"
	"				<!-- ICS2 values -->"
	"				<node tag=\"0x9f8450\"> 44 45 46 41 55 4c 54 20 34 4f 4e 46 49 47 </node> <!-- DEFAULT CONFIG -->"
	"				<node tag=\"0x9F35\"> 22 </node>"
	"				<node tag=\"0x9F33\"> 60 F8 C8 </node>"
	"				<node tag=\"0x9F1A\"> 00 56 </node>    <!-- Default country : France, currency : Euro -->"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x9F40\"> E0 00 F0 F0 01 </node>"
	"				<node tag=\"0x9F8142\"> 01 </node>"
	"				<node tag=\"0x9F8195\"> 00 </node>"
	"				<node tag=\"0x9F844B\"> 01 </node>"
	"				<node tag=\"0x9F8440\"> 00 </node>"
	"			</node> <!-- End node -->"
	""
	"			<node tag=\"0x1304\">"
	"				<!-- ICS3 values -->"
	"				<node tag=\"0x9f8450\"> 44 45 46 41 55 4c 54 20 34 4f 4e 46 49 47 </node> <!-- DEFAULT CONFIG -->"
	"				<node tag=\"0x9F35\"> 22 </node>"
	"				<node tag=\"0x9F33\"> 60 F8 C8 </node>"
	"				<node tag=\"0x9F1A\"> 00 56 </node>    <!-- Default country : France, currency : Euro -->"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x9F40\"> E0 00 F0 F0 01 </node>"
	"				<node tag=\"0x9F8142\"> 00 </node>"
	"				<node tag=\"0x9F8195\"> 00 </node>"
	"				<node tag=\"0x9F844B\"> 01 </node>"
	"				<node tag=\"0x9F8440\"> 00 </node>"
	"				<node tag=\"0x9F8459\"> 00 </node>"
	"			</node> <!-- End node -->"
	""
	"			<node tag=\"0x1305\">"
	"				<!-- ICS4 values -->"
	"				<node tag=\"0x9f8450\"> 44 45 46 41 55 4c 54 20 34 4f 4e 46 49 47 </node> <!-- DEFAULT CONFIG -->"
	"				<node tag=\"0x9F35\"> 22 </node>"
	"				<node tag=\"0x9F33\"> 60 F8 C8 </node>"
	"				<node tag=\"0x9F1A\"> 00 56 </node>    <!-- Default country : France, currency : Euro -->"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x9F40\"> E0 00 F0 F0 01 </node>"
	"				<node tag=\"0x9F8142\"> 01 </node>"
	"				<node tag=\"0x9F8195\"> 00 </node>"
	"				<node tag=\"0x9F844B\"> 01 </node>"
	"				<node tag=\"0x9F8440\"> 00 </node>"
	"				<node tag=\"0x9F8441\"> 01 </node>"
	"			</node> <!-- End node -->"
#endif /* 0 */
	"		</node> <!-- End node -->"
	"	</node>																													    "
	"</tlvtree>"
};

const char DefaultParamEval[] =
{
	"	<?xml version=\"1.0\" standalone=\"yes\" ?>"
	"	<!-- Fichier de parametres base -->"
	""
	"	<tlvtree ver=\"1.0\">"
	""
	"	<node tag=\"0x0\">"
	"		<node tag=\"0x1000\">                                <!-- C_TAG_AID -->"
	"			<node tag=\"0x1001\">"
	"				<!-- AID1_EVAL file content -->"
	"				<node tag=\"0x9FFF00\"> 41 49 44 31 </node>    <!--     AID1_EVAL Parameters -->"
	"				<node tag=\"0x9F06\"> 07 B0 12 34 56 78 12 34 </node>"
	"				<node tag=\"0x9F1A\"> 00 56 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 01 F4 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 08 02 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 00 02 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F841D\"> 00 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1002\">"
	"				<!-- AID2_EVAL.0 file content -->"
	"				<node tag=\"0x9FFF00\"> 4D 61 73 74 65 72 43 61 72 64 </node>"
	"				<node tag=\"0x9F06\"> 07 A0 00 00 00 04 10 10 </node>"
	"				<node tag=\"0x9F1A\"> 00 56 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 01 F4 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 08 02 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 00 02 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F841D\"> 00 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1003\">"
	"				<!-- AID3.0 EVAL file content. Settings done according to Visa 1.4.0 -->"
	"				<node tag=\"0x9FFF00\"> 41 49 44 33 </node>"
	"				<node tag=\"0x9F06\"> 05 A0 00 00 00 10 </node>"
	"				<node tag=\"0x9F1A\"> 00 56 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 01 F4 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 08 02 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 00 02 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F841D\"> 01 </node>"
	"			</node> <!-- End node 9F8B03 -->"
	"		</node>"
	"	</node>"
	"</tlvtree>		<!-- End -->"
};

const char DefaultParamVisa[] =
{
	"	<?xml version=\"1.0\" standalone=\"yes\" ?>"
	"	<!-- Fichier de parametres base -->"
	""
	"	<tlvtree ver=\"1.0\">"
	""
	"	<node tag=\"0x0\">"
	"		<node tag=\"0x1000\">                                <!-- C_TAG_AID -->"
	""
	"			<node tag=\"0x1001\">"
	"				<!-- AID1 VISA file content -->"
	"				<node tag=\"0x9FFF00\"> 56 53 44 43 </node>               <!-- VSDC -->"
	"				<node tag=\"0x9F06\"> 07 A0 00 00 00 03 10 10 </node>"
	"				<node tag=\"0x9F1A\"> 09 78 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 00 40 </node>"
	"				<node tag=\"0x9F8125\"> 9F 02 06 5F 2A 02 9A 03 9C 01 95 05 9F 37 04 </node>"
	"				<node tag=\"0x9F8126\"> 50 </node>"
	"				<node tag=\"0x9F8127\"> 20 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F01\"> 45 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 00 8C </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F16\"> 01 20 00 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F15\"> 61 11 </node>"
	"				<node tag=\"0x9F7A\"> 01 </node>"
	"				<node tag=\"0x9F841D\"> 01 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1002\">"
	"				<!-- AID2 file content -->"
	"				<node tag=\"0x9FFF00\"> 4D 61 65 73 74 72 6F </node>    <!-- MaestroParameters -->"
	"				<node tag=\"0x9F06\"> 07 A0 00 00 00 99 90 90 </node>"
	"				<node tag=\"0x9F1A\"> 09 78 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 00 05 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 08 02 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 00 02 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F841D\"> 01 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1003\">"
	"				<!-- AID3 file content -->"
	"				<node tag=\"0x9FFF00\"> 41 49 44 33 </node>    <!-- VisaElectronParameters -->"
	"				<node tag=\"0x9F06\"> 07 A0 00 00 00 03 20 10 </node>"
	"				<node tag=\"0x9F1A\"> 09 78 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 00 05 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 02 06 5F 2A 02 9A 03 9C 01 95 05 9F 37 04 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 01 40 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F841D\"> 01 </node>"
	"			</node>"
	""
	"			<node tag=\"0x1004\">"
	"				<!-- AID4 file content -->"
	"				<node tag=\"0x9FFF00\"> 41 49 44 33 </node>"
	"				<node tag=\"0x9F06\"> 07 A0 00 00 00 03 20 10 </node>"
	"				<node tag=\"0x9F1A\"> 09 78 </node>"
	"				<node tag=\"0x5F2A\"> 09 78 </node>"
	"				<node tag=\"0x5F36\"> 02 </node>"
	"				<node tag=\"0x9F812B\"> 00 00 00 05 </node>"
	"				<node tag=\"0x9F8124\"> 9F 37 04 9F 47 01 8F 01 9F 32 01 </node>"
	"				<node tag=\"0x9F8125\"> 9F 02 06 5F 2A 02 9A 03 9C 01 95 05 9F 37 04 </node>"
	"				<node tag=\"0x9F8126\"> 00 </node>"
	"				<node tag=\"0x9F8127\"> 00 </node>"
	"				<node tag=\"0x9F8128\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F8129\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F812A\"> 00 00 00 00 00 </node>"
	"				<node tag=\"0x9F09\"> 01 40 </node>"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>"
	"				<node tag=\"0x9F841D\"> 01 </node>"
	"			</node> <!-- End node -->"
	"		</node> <!-- End node -->"
	"	</node>"
	"</tlvtree>	<!-- End -->"
};


/* ========================================================================	*/
/* Global function declarations                                             */
/* ========================================================================	*/

//===========================================================================
//! \brief This function performs a service call to EMV tool to get the tags.
//! and to get the trace of the last transaction.
//! \return Always OK.
//===========================================================================
extern int  DumpTags(void);

//===========================================================================
//! \brief This function performs the mark activation.
//! \param[in] data : DalaElementExt to find in TLVTree structure.
//! \return
//! - father mark if tag found, and father mark found and activated.
//! - 0 otherwise.
//===========================================================================
unsigned long PAR_SelectFatherAID(DataElementExt data);

#endif /* FILE_H */
/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function initializes aidX.par cakeys.par krevok.par or param.par
//! files with default values.
//! \param[in] y_x_PrintAID : TRUE if supported AIDs may be printed.
//! \return TRUE if successfull.
//! \note pTreeDefault must have been updated.
//===========================================================================
int CUPAR_InitDefFiles (unsigned char y_x_PrintAID);

//===========================================================================
//! \brief This function performs the initialisation of the parameters.
//! \param[in] uc_x_InitType : initialisation type. It can take the following values : 
//! - C_PARAM_APPLI : reset TLV tree used to store specific application tags.
//! - C_PARAM_INIT : read default parameters values and param.par file 
//! and build two TLV trees. Reset the marks array used to manage the activation.
//! - C_PARAM_DEFAULT : read default parameters values and update one TLV tree.
//! Don't touch the marks array used to manage the activation.
//! - C_PARAM_FILE_TLVTSERIAL : read the param.par file and update one TLV tree.
//! Don't touch the marks array used to manage the activation.
//! - C_PARAM_FILE_XML : read the param.par (xml format) file and update one TLV tree.
//! Don't touch the marks array used to manage the activation.
//! \param[in] pc_x_DirFile : file path and name used for param.par file.
//! \return 
//! - 0 if successfull.
//! - Error code, otherwise.
//! \note This function allows to select a main branch of the tree.
//! It corresponds to choose one configuration.
//! The next mark selects will be performed in the part of the tree choosen.
//===========================================================================
int PAR_InitParam(unsigned char uc_x_InitType, char *pc_x_DirFile);

//===========================================================================
//! \brief This function reads the parameters from aidX.par, cakeys.par,
//! krevok.par, ics.par, or param.par file and stores data in a TLV tree.
//! \param[in] pc_x_DirFile : file path and file name.
//! \param[in] pc_x_fileName : name of the parameter file.
//! \return TLVTree node.
//===========================================================================
TLV_TREE_NODE CUPAR_FileRead(char *pc_x_DirFile, char *pc_x_fileName);

//===========================================================================
//! \brief This function updates the output file(s) (serial TLVTree binary format)
//! with pTreeParam TLVTree informations.
//! \param[out] ptr_OutBuf : binary file (serial TVLTree binary format).
//! \return
//! - 0 if successfull.
//! - 1 otherwise.
//===========================================================================
int CUPAR_Update_Param_File(char * ptr_OutBuf);

//===========================================================================
//! \brief This function inits the ICS structure.
//! \return 
//! - TRUE if all ICS parameters are stored.
//! - FALSE otherwise.
//===========================================================================
int CUPAR_InitICS (void);

//===========================================================================
//! \brief This function gives the key module and index.
//! \param[out] AidValue : card AID.
//! \param[in] Index : certification Authority Public Key Index.
//! \param[out] Modulus : key module.
//! \param[out] ModulusLength : module length.
//! \param[out] Exponent : key exponent.
//! \param[out] ExponentLength : exponent length.
//! \return
//! - TRUE if successfull.
//! - FALSE otherwise.
//===========================================================================
int CUPAR_GiveKey (unsigned char  *AidValue,unsigned char  Index,unsigned char  *Modulus,unsigned short *ModulusLength,unsigned char  *Exponent,unsigned short *ExponentLength);

//===========================================================================
//! \brief This function restores the parameter file. If param.par file doesn't 
//! exist, the function tries to build it with other files : AIDx.par, KREVOK.PAR, ...
//! \param[in] uc_x_FileMgtType : PARAM.PAR or other parameters files indicator 
//! management.
//===========================================================================
void CUPAR_RestoreParam (unsigned char uc_x_FileMgtType);

//===========================================================================
//! \brief This function gives the AID list from the parameter structure.
//! \param[out] nb_aid : number of AID found.
//! \param[out] tab_AID : array updated with AID informations.
//! \return
//! - TRUE if successfull.
//! - FALSE otherwise.
//===========================================================================
int CUPAR_GiveAIDList(unsigned char *nb_aid, T_CUDB_AID_Elt *tab_AID);

//===========================================================================
//! \brief This function gives the AID list from the parameter structure.
//! \param[out] nb_aid : number of AID found.
//! \param[out] phOutputTLVTree : output TLV tree containing AID informations.
//! \return
//! - TRUE if successfull.
//! - FALSE otherwise.
//===========================================================================
int CUPAR_GiveAIDListTlvTree(unsigned char *nb_aid, TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function copies a file in a specific area.
//! \param[in] DirFile : file directory.
//! \param[in] fileName : file name.
//===========================================================================
void CUPAR_FileCopy(char *DirFile, char *fileName);

//===========================================================================
//! \brief This function gives all revoked Certificates matching the AID given 
//! in input parameter.
//! \param[in] AidValue : card AID.
//! \param[out] CA_revok : structure with all revoked CA.
//! \return
//! - TRUE if successfull.
//! - FALSE otherwise.
//===========================================================================
int CUPAR_GiveRevokedCA (unsigned char *AidValue, T_CUSERV_lst_tagCArevok *CA_revok);

//===========================================================================
//! \brief This function inits the blacklist file with the one given as parameter.
//! \param[in] fileName : new black list file name.
//! \return
//! - TRUE if init successfull.
//! - FALSE otherwise.
//===========================================================================
T_Bool CUPAR_BlackListInit (char *fileName);

//===========================================================================
//! \brief This function prints the current ICS.
//! \return
//! - TRUE if successfull.
//! - FALSE otherwise.
//===========================================================================
int CUPAR_Print_ICS_Config(void);

//===========================================================================
//! \brief This function gets the value of the tag, given as input parameter,
//! in the EMV configuration.
//! \param[in] tag : parameter tag to get.
//! \param[out] value : it can take the following values : 
//! - value of the tag in text format.
//! - "YES" or "NO" if the tag is binary compatible.
//! - "NONE" if the tag isn't reachable
//! \return Always TRUE.
//===========================================================================
int CUPAR_Get_Param(unsigned long tag, unsigned char *value);

//===========================================================================
//! \brief This function retreives informations (Version and CRC) about kernel 
//! and system.
//! \return Always TRUE.
//===========================================================================
int CUPAR_Update_Kernel_and_System_Infos (void);

//===========================================================================
//! \brief This function saves a list of parameters in the global database.
//===========================================================================
void CUPAR_UpdateGlobalParam(void);

//===========================================================================
//! \brief This function control the key parameters (sha...).
//! \return
//! - TRUE if all the keys are OK.
//! - FALSE otherwise.
//===========================================================================
int CUPAR_ControlCAKEYS (void);


#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function checks if the system and the kernel support ToolWare
//! \return Always TRUE.
//===========================================================================
int CUPAR_Init_ToolWare(void);
#endif

#ifdef _USE_UCM_

//===========================================================================
//! \brief This function sets the com 0 for the EMV tool.
//===========================================================================
void SetOutputCom0(void);


//===========================================================================
//! \brief This function performs a service call to EMV tool to get the tags,
//! and to get the trace of the last transaction.
//! \return Always OK.
//===========================================================================
int DumpTags(void);

#endif /* _USE_UCM_ */
//===========================================================================
//! \brief This function resets ICS mark parameter in relation with selected AID.
//===========================================================================
void CUPAR_ResetAdditionnalICS(void);

//===========================================================================
//! \brief This function memorizes ICS mark parameter in relation with selected AID.
//! \param[in] ul_x_ICSMark : ICS mark parameter in relation with AID.
//===========================================================================
void CUPAR_MemorizeAdditionnalICS(unsigned long  ul_x_ICSMark);

//===========================================================================
//! \brief This function selects ICS mark parameter in relation with selected AID.
//! \return 
//! - TRUE if mark has been found and selected.
//! - FALSE otherwise.
//===========================================================================
int  CUPAR_SelectAdditionnalICS(void);

//===========================================================================
//! \brief This function resets mark parameter in relation with selected AID.
//===========================================================================
void CUPAR_ResetAdditionnalAID(void);

//===========================================================================
//! \brief This function memorizes mark parameter in relation with selected AID.
//! \param[in] ul_x_ICSMark : mark parameter.
//===========================================================================
void CUPAR_MemorizeAdditionnalAID(unsigned long  ul_x_ICSMark);

//===========================================================================
//! \brief This function selects parameter in relation with selected AID.
//! \return
//! - TRUE if mark was found and selected.
//! - FALSE otherwise.
//===========================================================================
int CUPAR_SelectAdditionnalAID(void);

//===========================================================================
//! \brief This function resets mark parameter in relation with selected KRevok.
//===========================================================================
void CUPAR_ResetAdditionnalKRevok(void);

//===========================================================================
//! \brief This function memorizes mark parameter in relation with selected KRevok.
//! \param[in] ul_x_KRevokMark : mark parameter.
//===========================================================================
void CUPAR_MemorizeAdditionnalKRevok(unsigned long  ul_x_KRevokMark);

//===========================================================================
//! \brief This function selects parameter in relation with selected KRevok.
//! \return
//! - TRUE if mark has been found and selected.
//! - FALSE otherwise.
//===========================================================================
int CUPAR_SelectAdditionnalKRevok(void);

//! @}

#endif /* CU_PARAM_H */
