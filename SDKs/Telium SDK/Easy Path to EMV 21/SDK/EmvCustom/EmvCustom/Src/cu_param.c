/**
* \file cu_param.c
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

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "SDK30.H"
#include "_emvdctag_.h"
#include "del_lib.h"
#include "cu_term.h"
#include "cu_disk.h"
#include "MyTlvTree.h"
#include "convert.h"
#include "cu_batch.h"
#include "cu_black.h"
#include "cu_base.h"
#include "cu_sha.h"
#include "cu_mess.h"
#include "MessagesDefinitions.h"
#include "def_tag.h"
#include "cu_file.h"
#include "cu_receipt.h"
#include "cu_entry.h"
#include "servcomm.h"
#include "gestion_param.h"
#define FILE_H
#include "cu_param.h"
#undef FILE_H

#ifdef _USE_UCM_
#include "EmvTool.h"
#endif /* _USE_UCM_ */

//! \addtogroup Group_param
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define EMVDC_TYPE					0x60
#define SYSTEM_TYPE					0x01

#define MAX_FILE_LG					1024  /* max length buf for file */

#define C_INDEX_AID					0
#define C_INDEX_REVOK				1
#define C_INDEX_CAKEYS				2
#define C_INDEX_ICS					3
#define C_INDEX_UNKNOWN				4

#define C_NB_OLD_FILES				13

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

static const unsigned char C_OLD_FILES[C_NB_OLD_FILES][11] = {C_AID1_PARAM,
C_AID2_PARAM,
C_AID3_PARAM,
C_AID4_PARAM,
C_AID5_PARAM,
C_ICS0_PARAM,
C_ICS2_PARAM,
C_ICS3_PARAM,
C_ICS4_PARAM,
C_ICS5_PARAM,
C_CAKEYS_PARAM,
C_KREVOK_PARAM};

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

static unsigned long ul_AdditionnalICS = 0;
static unsigned long ul_AdditionnalAID = 0;
static unsigned long ul_AdditionnalKRevok = 0;


/* ======================================================================== */
/* Static function definitions                                              */
/* ======================================================================== */

static int  CUPAR_Compute_ICS_Config_CRC(void);
static int  Build_Parameters(unsigned char c_x_WorkType, char * ptr_InBuf, char * ptr_OutBuf, char * ptr_rStringTmp, unsigned char option);
static int  Update_Parameters_file(TLV_TREE_NODE pTree, char * ptr_TxtBuf, char * ptr_OutBuf, char * ptr_rStringTmp, unsigned char option);

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
void CUPAR_ResetAdditionnalICS(void)
{
	ul_AdditionnalICS = 0;
}


//===========================================================================
void CUPAR_MemorizeAdditionnalICS(unsigned long  ul_x_ICSMark)
{
	/* Memorize additionnal ICS found */
	ul_AdditionnalICS = ul_x_ICSMark;
}

//===========================================================================
int CUPAR_SelectAdditionnalICS(void)
{
	int i_l_res, i_l_result = 0;

	// Select first Mark child for ICS
	i_l_res = PAR_SelectMark(C_TAG_ICS0, C_TREE_ALL);
	if (i_l_res != 0)
	{
		i_l_result = 1;
	}

	if (ul_AdditionnalICS != 0)
	{
		// Select second and highter priority Mark child for ICSx
		i_l_res = PAR_SelectMark(ul_AdditionnalICS, C_TREE_ALL);
		if (i_l_res != 0)
		{
			i_l_result = 2;
		}
	}

	return (i_l_result);
}

//===========================================================================
void CUPAR_ResetAdditionnalAID(void)
{
	ul_AdditionnalAID = 0;
}

//===========================================================================
void CUPAR_MemorizeAdditionnalAID(unsigned long  ul_x_AIDMark)
{
	// Memorize additionnal ICS found
	ul_AdditionnalAID = ul_x_AIDMark;
}

//===========================================================================
int CUPAR_SelectAdditionnalAID(void)
{
	int i_l_res, i_l_result = 0;

	if (ul_AdditionnalAID != 0)
	{
		// Select second and highter priority Mark child for ICSx
		i_l_res = PAR_SelectMark(ul_AdditionnalAID, C_TREE_PARAM_FIRST);
		if (i_l_res != 0)
			i_l_result = 1; /* Pb */
	}

	return (i_l_result);
}

//===========================================================================
void CUPAR_ResetAdditionnalKRevok(void)
{
	ul_AdditionnalKRevok = 0;
}

//===========================================================================
void CUPAR_MemorizeAdditionnalKRevok(unsigned long  ul_x_KRevokMark)
{
	// Memorize additionnal ICS found
	ul_AdditionnalKRevok = ul_x_KRevokMark;
}


//===========================================================================
int CUPAR_SelectAdditionnalKRevok(void)
{
	int i_l_res, i_l_result = 0;

	if (ul_AdditionnalKRevok != 0)
	{
		// Select second and highter priority Mark child for ICSx
		i_l_res = PAR_SelectMark(ul_AdditionnalKRevok, C_TREE_PARAM_FIRST);
		if (i_l_res != 0)
			// Pb
			i_l_result = 1;
	}

	return (i_l_result);
}


//===========================================================================
int CUPAR_InitDefFiles (unsigned char y_x_PrintAID)
{
	// Local variables déclaration
	// Function result
	int success = TRUE;
	char ac_l_FilePath_L[80];
	char LabelDiskName[DISK_NAME_SIZE];

	memclr(LabelDiskName, sizeof(LabelDiskName));
	CUDISK_Get_Disk_Name(LabelDiskName);

	// Update PARAM.PAR serial binary TLVTree format file
	sprintf(ac_l_FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM);
	CUPAR_WriteAllBinFile(pTreeDefault, ac_l_FilePath_L);
	CUPAR_InitICS();

	if (y_x_PrintAID)
		CUPAR_Print_Param_Supported(pTreeDefault, "AID", C_TAG_AID, C_TRACE_ONE_TAG, TAG_AID_TERMINAL);

	return(success);
}


//===========================================================================
//! \brief This function allows to trace TLV tree given as parameter on trace tool
//! \param[in] pTree : TLV tree to trace.
//! \param[in] txt : text to display at begining of trace.
//===========================================================================
void CUPAR_TlvTree_Display(TLV_TREE_NODE pTree , char * txt)
{
	// #define DETAIL

	// trace when simulating on target
	TLV_TREE_NODE pNode;
	char TmpBuf[100];
#ifdef DETAIL
	unsigned char * ptr_car;
	unsigned int index;
#endif // DETAIL


	pNode = pTree;

	trace(0, strlen("\nCUPAR_TlvTree_Display:\n"), "\nCUPAR_TlvTree_Display:\n");
	trace(0, strlen(txt), txt);

	while( pNode != NULL )
	{
		sprintf(TmpBuf, "- %08x [- %08x]: (%d/%d)   ", TlvTree_GetTag(pNode), (int)(TlvTree_GetParent(pNode) ? TlvTree_GetParent(pNode) : 0 ),
			(int)TlvTree_GetData(pNode), (int)TlvTree_GetLength(pNode)); 
		trace(0, strlen(TmpBuf), TmpBuf);

#ifdef DETAIL
		ptr_car = (unsigned char*)TlvTree_GetData(pNode);
		for (index=0; ((index<(TlvTree_GetLength(pNode))) && (index<30)); index++)
		{
			sprintf(&TmpBuf[index*3], "%2x ", *ptr_car++);
		}
		trace(0, strlen(TmpBuf), TmpBuf);
#endif // DETAIL

		pNode = TlvTree_Iterate( pNode,  pTree );
	} 
}


//===========================================================================
int PAR_InitParam(unsigned char uc_x_InitType, char *pc_x_DirFile)
{
	int  i_l_result = 0, i_l_Size = 0;
	char ac_l_FilePath_L[80];
	TLV_TREE_NODE pTree = 0;
	unsigned int ui_l_NumMark = 0;
	char * pc_l_ParamArray = 0;
	int i_l_ControlCaKeys = FALSE;
	char LabelDiskName[DISK_NAME_SIZE];

	switch (uc_x_InitType)
	{
		case C_PARAM_INIT_APLI :
			trace(0, strlen("PAR_InitParam() : C_PARAM_INIT_APLI"), "PAR_InitParam() : C_PARAM_INIT_APLI");
			CUPAR_InitTree(&pTreeAppli);
			break;

		case C_PARAM_INIT_DEFAULT :
			trace(0, strlen("PAR_InitParam() : C_PARAM_INIT_DEFAULT"), "PAR_InitParam() : C_PARAM_INIT_DEFAULT");
			CUPAR_InitTree(&pTreeDefault);
			break;

		case C_PARAM_INIT:
			memclr(LabelDiskName, sizeof(LabelDiskName));
			CUDISK_Get_Disk_Name(LabelDiskName);

			trace(0, strlen("PAR_InitParam() : C_PARAM_INIT"), "PAR_InitParam() : C_PARAM_INIT");
			memclr(ac_l_FilePath_L, sizeof(ac_l_FilePath_L));

			// If code executed on target
			sprintf(ac_l_FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM);

			// default parameter files, and default values are read. The global data TLV tree is initialised.
			if (CUPAR_FileRead(ac_l_FilePath_L, C_FILE_PARAM) == 0)
			{
				trace(0, strlen("Pb on PARAM.PAR file load"), "Pb on PARAM.PAR file load");
				upload_diagnostic_txt ((unsigned char*)"\n Problem on CUPAR_FileRead() Load PARAM.PAR file");
				i_l_result = 1;
			}
			else
				trace(0, strlen("PARAM.PAR file loaded"), "PARAM.PAR file loaded");

			break;

		case C_PARAM_DEFAULT:
			trace(0, strlen("PAR_InitParam() : C_PARAM_DEFAULT"), "PAR_InitParam() : C_PARAM_DEFAULT");
			TlvTree_Release(pTreeDefault);

			// Default parameters initialisation => set in TLV tree
			pTreeDefault = PAR_ReadArray((char*)DefaultParam, sizeof(DefaultParam), C_TAG_MAIN);

			if (pTreeDefault == 0)
				i_l_result = 2;
			else
			{
				i_l_ControlCaKeys = TRUE;
				CUPAR_InitICS();
			}
			break;

		case C_PARAM_DEFAULT_ICS: 
			// Load Default ICS values in pTreeDefault structure
			trace(0, strlen("PAR_InitParam() : C_PARAM_DEFAULT_ICS"), "PAR_InitParam() : C_PARAM_DEFAULT_ICS");
			TlvTree_Release(pTreeDefault);

			// Default parameters initialisation => set in TLV tree
			pTreeDefault = PAR_ReadArray((char*)DefaultParam, sizeof(DefaultParam), C_TAG_ICS);

			if (pTreeDefault == 0)
				i_l_result = 2;
			else
			{
				i_l_ControlCaKeys = TRUE;
				CUPAR_InitICS();
			}
			break;


		case C_PARAM_ONLY_DEFAULT_AID:		// Delete AID values in pTreeParam and load default AID values in pTreeParam and save new TLVTree Struct in param.par file
		case C_PARAM_ONLY_DEFAULT_AID_EVAL:	// Delete AID values in pTreeParam and load default EVAL AID values in pTreeParam and save new TLVTree Struct in param.par file
		case C_PARAM_ONLY_DEFAULT_AID_VISA:	// Delete AID values in pTreeParam and load default VISA AID values in pTreeParam and save new TLVTree Struct in param.par file
		case C_PARAM_ONLY_DEFAULT_ICS:		// Delete ICS values in pTreeParam and load default ICS values in pTreeParam and save new TLVTree Struct in param.par file

			if (uc_x_InitType == C_PARAM_ONLY_DEFAULT_ICS)
			{
				trace(0, strlen("PAR_InitParam() : C_PARAM_ONLY_DEFAULT_ICS"), "PAR_InitParam() : C_PARAM_ONLY_DEFAULT_ICS");
				ui_l_NumMark = C_TAG_ICS;
				pc_l_ParamArray = (char*)DefaultParam;
				i_l_Size = sizeof(DefaultParam);
				i_l_ControlCaKeys = TRUE;
			}
			else if (uc_x_InitType == C_PARAM_ONLY_DEFAULT_AID)
			{
				trace(0, strlen("PAR_InitParam() : C_PARAM_ONLY_DEFAULT_AID"), "PAR_InitParam() : C_PARAM_ONLY_DEFAULT_AID");
				ui_l_NumMark = C_TAG_AID;
				pc_l_ParamArray = (char*)DefaultParam;
				i_l_Size = sizeof(DefaultParam);
				i_l_ControlCaKeys = TRUE;
			}
			else if (uc_x_InitType == C_PARAM_ONLY_DEFAULT_AID_EVAL)
			{
				trace(0, strlen("PAR_InitParam() : C_PARAM_ONLY_DEFAULT_AID_EVAL"), "PAR_InitParam() : C_PARAM_ONLY_DEFAULT_AID_EVAL");
				ui_l_NumMark = C_TAG_AID;
				pc_l_ParamArray = (char*)DefaultParamEval;
				i_l_Size = sizeof(DefaultParamEval);
			}
			else if (uc_x_InitType == C_PARAM_ONLY_DEFAULT_AID_VISA)
			{
				trace(0, strlen("PAR_InitParam() : C_PARAM_ONLY_DEFAULT_AID_VISA"), "PAR_InitParam() : C_PARAM_ONLY_DEFAULT_AID_VISA");
				ui_l_NumMark = C_TAG_AID;
				pc_l_ParamArray = (char*)DefaultParamVisa;
				i_l_Size = sizeof(DefaultParamVisa);
			}
			else
				trace(0, strlen("PAR_InitParam() : C_PARAM_???"), "PAR_InitParam() : C_PARAM_???");

			if (pTreeParam == 0)
				pTreeParam = TlvTree_New(C_TAG_MAIN);

			// Look for main tag in pTreeParam
			pTree = PAR_FoundMarkInTree(pTreeParam, ui_l_NumMark);

			// if main tag present
			if (pTree != NULL)
				// Delete it
				TlvTree_Release(pTree);

			// Load default parameters => set in a TLV tree
			pTree = PAR_ReadArray((char*)pc_l_ParamArray, i_l_Size, ui_l_NumMark);

			// Add new TLVTree in pTreeParam TLVStruct
			TlvTree_Graft(pTreeParam, pTree);

			{
				// Save new TLV tree structure in param.par file for memorization
				char FilePath_L[33];

				memclr(LabelDiskName, sizeof(LabelDiskName));
				CUDISK_Get_Disk_Name(LabelDiskName);

				sprintf(FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM);
				trace(0, strlen("Update PARAM.PAR file"), "Update PARAM.PAR file");
				CUPAR_Update_Param_File(FilePath_L);
			}
			break;

		case C_PARAM_FILE_TLVTSERIAL:
			trace(0, strlen("PAR_InitParam() : C_PARAM_FILE_TLVTSERIAL"), "PAR_InitParam() : C_PARAM_FILE_TLVTSERIAL");
			if (CUPAR_ReadParamFile(&pTreeParam, pc_x_DirFile, TLV_TREE_SERIALIZER_DEFAULT) != 0)
			{
				i_l_result = 3;
			}
			else
			{
				// Mards to select nodes in TLV trees
				CUPAR_AddMarqs(&pTreeParam);
				// For debug
				//CUPAR_TlvTree_Display( pTreeParam, "C_PARAM_FILE_XML");
			}
			break;

		case C_PARAM_FILE_XML:
			trace(0, strlen("PAR_InitParam() : C_PARAM_FILE_XML"), "PAR_InitParam() : C_PARAM_FILE_XML");
			if (CUPAR_ReadParamFile(&pTreeParam, pc_x_DirFile, TLV_TREE_SERIALIZER_XML) != 0)
			{
				i_l_result = 3;
			}
			else
			{
				// Mards to select nodes in TLV Trees
				CUPAR_AddMarqs(&pTreeParam);
				// For debug
				//CUPAR_TlvTree_Display( pTreeParam, "C_PARAM_FILE_XML");
			}
			break;

		default:
			trace(0, strlen("PAR_InitParam() : ??"), "PAR_InitParam() : ??");
			break;
	}

	if (i_l_ControlCaKeys)
		if (CUPAR_ControlCAKEYS() != TRUE)
			trace(0, strlen("PAR_InitParam():CUPAR_ControlCAKEYS pb\n"), "PAR_InitParam():CUPAR_ControlCAKEYS pb\n");

	return (i_l_result);
}

/* Penser à travailler dans une partie de l'arbre (celle sélectionnée et qui correspond à une conf) */

//===========================================================================
TLV_TREE_NODE CUPAR_FileRead(char *pc_x_DirFile, char *pc_x_fileName)
{
	char ac_l_OutBuf[80];
	char ac_l_rStringTmp[250];
	char LabelDiskName[DISK_NAME_SIZE];

	memclr(LabelDiskName, sizeof(LabelDiskName));
	CUDISK_Get_Disk_Name(LabelDiskName);

	sprintf(ac_l_OutBuf, "/%s/%s", LabelDiskName, C_FILE_PARAM);

	if ((strncmp(pc_x_fileName, "AID", strlen("AID")) == 0)       || (strncmp(pc_x_fileName, "aid", strlen("aid")) == 0)       ||
		(strncmp(pc_x_fileName, "CAKEYS", strlen("CAKEYS")) == 0) || (strncmp(pc_x_fileName, "cakeys", strlen("cakeys")) == 0) ||
		(strncmp(pc_x_fileName, "KREVOK", strlen("KREVOK")) == 0) || (strncmp(pc_x_fileName, "krevok", strlen("krevok")) == 0) ||
		(strncmp(pc_x_fileName, "ICS", strlen("ICS")) == 0)       || (strncmp(pc_x_fileName, "ics", strlen("ics")) == 0)  )
	{
		if (pTreeParam == 0)
			pTreeParam = TlvTree_New(C_TAG_MAIN);

		Update_Parameters_file(pTreeParam, pc_x_DirFile, ac_l_OutBuf, ac_l_rStringTmp, 0);
		//      CUPAR_TlvTree_Display(pTreeParam, "AID, CAKEYS KREVOK ICS");

		if ((strncmp(pc_x_fileName, C_ICS0_PARAM, strlen(C_ICS0_PARAM)) == 0) || (strncmp(pc_x_fileName, "ics.par", strlen("ics.par")) == 0))
		{	// Warning : ICS values are allways used with default ICS loaded (a tag not found in ICS parameters will be taken in Default ICA parameters
			char *ptrDummy = 0;
			PAR_InitParam(C_PARAM_DEFAULT_ICS, ptrDummy);
		}
	}
	else if ((strncmp(pc_x_fileName, C_FILE_NAME_XML, sizeof(C_FILE_NAME_XML)-1) == 0)	||
			(strncmp(pc_x_fileName, "emvcust", sizeof("emvcust")) == 0)					||
			(strncmp(pc_x_fileName, C_FILE_PARAM, sizeof(C_FILE_PARAM)-1) == 0)         ||
			(strncmp(pc_x_fileName, "param.par", sizeof("param.par")) == 0))
	{
		unsigned int FileTypeAccess = TLV_TREE_SERIALIZER_DEFAULT;

		TlvTree_Release(pTreeParam);
		pTreeParam = 0;
		// Reset the selected mark list
		PAR_ResetMarkList();

		if ((strncmp(pc_x_fileName, C_FILE_NAME_XML, sizeof(C_FILE_NAME_XML)-1) == 0) ||
			(strncmp(pc_x_fileName, "emvcust", sizeof("emvcust")) == 0))
		{
			// XML format used to load parameter
			FileTypeAccess = TLV_TREE_SERIALIZER_XML;
		}
		else
		{
		}

		if (CUPAR_ReadParamFile(&pTreeParam, pc_x_DirFile, FileTypeAccess) == 0)
		{
			char *ptrDummy = 0;

			// Warning : ICS values are allways used with default ICS loaded (a tag not found in ICS parameters will be taken in Default ICA parameters
			PAR_InitParam(C_PARAM_DEFAULT_ICS, ptrDummy);

			CUPAR_InitICS();
		}
		//        CUPAR_TlvTree_Display(pTreeParam, "Read param.par");
	}
	return (pTreeParam);
}


//===========================================================================
int CUPAR_Update_Param_File(char * ptr_x_OutBuf)
{
	trace(0, strlen("CUPAR_Update_Param_File()"), "CUPAR_Update_Param_File()");
	return (CUPAR_WriteAllBinFile(pTreeParam, ptr_x_OutBuf));
}


//===========================================================================
//! \brief This function inits keys structure with keys parameters.
//! \param[out] ptr_x_key : array containing all keys in relation with given AID.
//! \param[in] ptr_x_AID : card AID.
//! \param[in] uc_x_Index : Certification Authority Public Key Index.
//! \return
//! - TRUE if all keys have been stored.
//! - FALSE otherwise.
//===========================================================================
static int CUPAR_GiveCAKEYS(CA_PUB_KEY * ptr_x_key, unsigned char * ptr_x_AID, unsigned char uc_x_Index)
{
	unsigned char uc_l_FirstAcces = 1;
	unsigned int  i_l_NumMark;
	int           i_l_Success;
	int           i_l_ResultMark;
	int           cr;
	DataElementExt data;

	//    trace(0, strlen("\nCUPAR_GiveCAKEYS()\n"), "\nCUPAR_GiveCAKEYS()\n");

	// Select mark witch must be actived
	i_l_Success = FALSE;
	// Main mark of CAKEYS
	i_l_NumMark = C_TAG_CAKEYS;

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Loop on each CAKEYS
	do{
		memclr ((unsigned char *)ptr_x_key, sizeof(CA_PUB_KEY));

		i_l_ResultMark = PAR_SelectNextMark(i_l_NumMark, uc_l_FirstAcces);
		if (i_l_ResultMark == 0)
		{
			// Loop end
			break;
		}
		uc_l_FirstAcces = 0;

		cr = PAR_ReadParameter(TAG_AID_TERMINAL, &data);
		if ((cr) && (data.elt.length == LG_RID))
		{
			// Is it the good AID ?
			if (memcmp (ptr_x_AID, data.elt.ptValue, 5) != 0)
			{
				//                trace(0, strlen("\nCUPAR_GiveCAKEYS():AID not matching\n"), "\nCUPAR_GiveCAKEYS():AID not matching\n");
				// Next NumMark, this one isn't good
				continue;
			}
			memcpy((unsigned char*)ptr_x_key->rid, data.elt.ptValue, LG_RID);
		}
		else 
		{
			if (cr == 0)
				trace(0, strlen("Bad CR PAR_ReadParameter TAG_AID_TERMINAL\n"), "Bad CR PAR_ReadParameter TAG_AID_TERMINAL\n");
			else
				trace(0, strlen("AID bad length \n"), "AID bad length \n");
			// Next NumMark, this one isn't good
			continue;
		}

		cr = PAR_ReadParameter(TAG_CERT_AUTH_PUB_KEY_INDEX_TERM, &data);
		if ((cr) && (data.elt.length == 1))
		{
			// Is it the good index ?
			if (uc_x_Index != data.elt.ptValue[0])
			{            
				//                trace(0, strlen("\nCUPAR_GiveCAKEYS():Index not matching\n"), "\nCUPAR_GiveCAKEYS():INDEX not matching\n");
				// Next NumMark, this one isn't good
				continue;
			}
			memcpy((unsigned char*)ptr_x_key->index, data.elt.ptValue ,data.elt.length);
		}
		else
		{
			if (cr == 0)
				trace(0, strlen("Bad CR PAR_ReadParameter KEY_INDEX_TERM\n"), "Bad CR PAR_ReadParameter KEY_INDEX_TERM\n");
			else
				trace(0, strlen("TAG_CERT_AUTH bad length \n"), "TAG_CERT_AUTH bad length \n");
			// Next NumMark, this one isn't good
			continue;
		}

		/****************************************************/
		/* After this line, a AID+index key have been found */
		/****************************************************/

		cr = PAR_ReadParameter(TAG_CERT_AUTH_PUB_KEY_MODULUS, &data);
		if ((cr) && (data.elt.length < 256))
		{
			memcpy((unsigned char*)ptr_x_key->modulus, data.elt.ptValue, data.elt.length);
			ptr_x_key->length = data.elt.length;
		}
		else
		{
			if (cr == 0)
				trace(0, strlen("Bad CR PAR_ReadParameter KEY_MODULUS\n"), "Bad CR PAR_ReadParameter KEY_MODULUS\n");
			else
				trace(0, strlen("256 \n"), "256 \n");
			// Next NumMark, this one isn't good
			continue;
		}

		cr = PAR_ReadParameter(TAG_CERT_AUTH_PUB_KEY_EXPONENT, &data);
		if ((cr) && (data.elt.length < 4))
		{
			memcpy((unsigned char*)ptr_x_key->exponent, data.elt.ptValue, data.elt.length);
			ptr_x_key->exponentlength = data.elt.length;
		}
		else
		{
			if (cr == 0)
				trace(0, strlen("Bad CR PAR_ReadParameter KEY_MODULUS\n"), "Bad CR PAR_ReadParameter KEY_MODULUS\n");
			else
				trace(0, strlen(" KEY_EXPO \n"), " KEY_EXPO \n");
			// Next NumMark, this one isn't good
			continue;
		}

		// No SHA check, it has allready been made

		// All is ok, we can took this key
		// To stop the loop
		i_l_ResultMark = 0;
		// Ok we found a key
		i_l_Success = TRUE;

		cr = PAR_ReadParameter(TAG_CUST_KEY_VALIDITY_DATE, &data);
		if ((cr) && (data.elt.length == 3))
		{
			memcpy((unsigned char*)ptr_x_key->expir_date, data.elt.ptValue, data.elt.length);
		}

		CUPAR_MemorizeAdditionnalKRevok(i_l_ResultMark);

	}while (i_l_ResultMark != 0); // End loop on each AID

	return (i_l_Success);
}

//===========================================================================
int CUPAR_ControlCAKEYS (void)
{
	unsigned char uc_l_FirstAcces = 1;
	unsigned int  i_l_NumMark;
	int           i_l_Success;
	int           i_l_ResultMark;
	unsigned int  i_l_MarkToSuppress;
	int           cr;
	unsigned long * pShaDigest;
	char          ac_l_szTrace [80];
	char          ac_l_szReadSha [20];
	static char   ac_l_sha_buf [C_SHA_BUFF_LENGTH];
	DataElementExt data;
	CA_PUB_KEY    key;


	// For trace
	char index = 0;

	//    trace(0, strlen("\nCUPAR_ControlCAKEYS()\n"), "\nCUPAR_ControlCAKEYS()\n");

	// Select mark which must be actived
	// Default value, all is ok
	i_l_Success = TRUE;
	// If at least, one CAKEY has been suppressed, this function will return FALSE
	// To know if the current mark must be deleted (bad sha, bad data length ...
	i_l_MarkToSuppress = 0;
	// Main mark of CAKEYS */
	i_l_NumMark = C_TAG_CAKEYS;

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Loop on each CAKEYS
	do{

		memclr ((unsigned char *)&key, sizeof(CA_PUB_KEY));


		i_l_ResultMark = PAR_SelectNextMark(i_l_NumMark, uc_l_FirstAcces);
		if (i_l_ResultMark == 0)
		{
			// Loop end
			break;
		}
		uc_l_FirstAcces = 0;

		if (i_l_MarkToSuppress != 0)
		{
			{
				char tmpBuf[50];
				sprintf(tmpBuf, "\n CUPAR_ControlCAKEYS() pb : %d", index);
				trace(0, strlen(tmpBuf), tmpBuf);
			}

			// Delete previous Mark with bad data
			PAR_DeleteMark(i_l_MarkToSuppress);

			// For work on current Mark
			i_l_MarkToSuppress = 0;
		}
		index++;

		memset (ac_l_sha_buf, 0, C_SHA_BUFF_LENGTH);

		cr = PAR_ReadParameter(TAG_AID_TERMINAL, &data);
		if ((cr) && (data.elt.length == LG_RID))
		{
			memcpy((unsigned char*)key.rid, data.elt.ptValue, LG_RID);
			memcpy(ac_l_sha_buf, data.elt.ptValue, LG_RID);
		}
		else 
		{
			if (cr == 0)
				trace(0, strlen("Bad CR PAR_ReadParameter TAG_AID_TERMINAL\n"), "Bad CR PAR_ReadParameter TAG_AID_TERMINAL\n");
			else
				trace(0, strlen("AID bad length \n"), "AID bad length \n");
			i_l_MarkToSuppress = i_l_ResultMark;
			i_l_Success = FALSE;
			continue;
		}

		cr = PAR_ReadParameter(TAG_CERT_AUTH_PUB_KEY_INDEX_TERM, &data);
		if ((cr) && (data.elt.length == 1))
		{
			memcpy((unsigned char*)key.index, data.elt.ptValue ,data.elt.length);
			memcpy (&(ac_l_sha_buf[LG_RID]), data.elt.ptValue, data.elt.length);
		}
		else
		{
			if (cr == 0)
				trace(0, strlen("Bad CR PAR_ReadParameter KEY_INDEX_TERM\n"), "Bad CR PAR_ReadParameter KEY_INDEX_TERM\n");
			else
				trace(0, strlen("TAG_CERT_AUTH bad length \n"), "TAG_CERT_AUTH bad length \n");
			i_l_MarkToSuppress = i_l_ResultMark;
			i_l_Success = FALSE;
			continue;
		}

		cr = PAR_ReadParameter(TAG_CERT_AUTH_PUB_KEY_MODULUS, &data);
		if ((cr) && (data.elt.length < 256))
		{
			memcpy((unsigned char*)key.modulus, data.elt.ptValue, data.elt.length);
			key.length = data.elt.length;
			memcpy (&(ac_l_sha_buf[LG_RID + 1 ]), data.elt.ptValue, data.elt.length);
		}
		else
		{
			if (cr == 0)
				trace(0, strlen("Bad CR PAR_ReadParameter KEY_MODULUS\n"), "Bad CR PAR_ReadParameter KEY_MODULUS\n");
			else
				trace(0, strlen("256 \n"), "256 \n");

			i_l_MarkToSuppress = i_l_ResultMark;
			i_l_Success = FALSE;
			continue;
		}

		cr = PAR_ReadParameter(TAG_CERT_AUTH_PUB_KEY_EXPONENT, &data);
		if ((cr) && (data.elt.length < 4))
		{
			memcpy((unsigned char*)key.exponent, data.elt.ptValue, data.elt.length);
			key.exponentlength = data.elt.length;
			memcpy (&(ac_l_sha_buf[LG_RID + 1 + key.length]), data.elt.ptValue, data.elt.length);
		}
		else
		{
			if (cr == 0)
				trace(0, strlen("Bad CR PAR_ReadParameter KEY_MODULUS\n"), "Bad CR PAR_ReadParameter KEY_MODULUS\n");
			else
				trace(0, strlen(" KEY_EXPO \n"), " KEY_EXPO \n");

			i_l_MarkToSuppress = i_l_ResultMark;
			i_l_Success = FALSE;
			continue;
		}

		pShaDigest = SHA1_Compute ((unsigned char*)ac_l_sha_buf, LG_RID+1+key.exponentlength + key.length);

		cr = PAR_ReadParameter(TAG_CERT_AUTH_PUB_KEY_CHECKSUM, &data);
		if ((cr) && (data.elt.length == 20) && (pShaDigest != NULL))
		{
			memcpy((unsigned char*)ac_l_szReadSha, data.elt.ptValue, data.elt.length);
			if (memcmp (ac_l_szReadSha,pShaDigest, 20) != 0 )
			{
				trace(0, strlen(" SHA KO !!\n"), " SHA KO !!\n");

				trace(0, 31, (unsigned char *)"Invalid key SHA (RID/Index/SHA)");
				trace(0, sizeof(key.rid), key.rid);
				trace(0, sizeof(key.index), key.index);
				trace(0, 20, (unsigned char *)pShaDigest);

				sprintf ((char *)ac_l_szTrace, "RID %02X%02X%02X%02X%02X I %02X, SHA:%08lX %08lX %08lX %08lX %08lX\n",
					key.rid[0], key.rid[1], key.rid[2], key.rid[3], key.rid[4],
					key.index [0],
					pShaDigest[0],
					pShaDigest[1],
					pShaDigest[2],
					pShaDigest[3],
					pShaDigest[4]);
				upload_diagnostic_txt ((unsigned char*)ac_l_szTrace);
				upload_diagnostic_txt ((unsigned char*)"Bad\n");

				i_l_MarkToSuppress = i_l_ResultMark;
				i_l_Success = FALSE;
				continue;
			}
			else
			{
				//                trace(0, strlen(" SHA OK\n"), " SHA OK\n");
				// All is ok
			}
		}        
		else
		{
			if (cr == 0)
				trace(0, strlen(" bad cr KEY_CHECKSUM \n"), " bad cr KEY_CHECKSUM \n");
			else if (pShaDigest == NULL)
				trace(0, strlen(" pSHA null \n"), " pSHA null \n");
			else 
				trace(0, strlen(" bad KEY_CHECKSUM length \n"), " bad KEY_CHECKSUM length \n");

			i_l_MarkToSuppress = i_l_ResultMark;
			i_l_Success = FALSE;
			continue;
		}
	}while (i_l_ResultMark != 0); // End loop on each AID

	return (i_l_Success);
}

//===========================================================================
int CUPAR_InitICS (void)
{
	int             found = FALSE;
	unsigned int    i_l_Mark = C_TAG_ICS;
	TLV_TREE_NODE	hnode;

	hnode = PAR_FoundMark(i_l_Mark);

	// If main mark has been found
	if (hnode != NULL)
	{   
		unsigned int  nindex = 0;
		TLV_TREE_NODE hChildnode;

		// Main mark found
		found = TRUE;

		hChildnode = TlvTree_Find(hnode,C_TAG_ICS0, nindex++);
		while (hChildnode != NULL)
		{
			if ((hChildnode != NULL) && (strncmp((char*)TlvTree_GetData(hChildnode), "MARQ_", 5) == 0))
			{
				// Compute the CRC
				CUPAR_Compute_ICS_Config_CRC();

				CUPAR_UpdateGlobalParam();
				break;
			}
			hChildnode = TlvTree_Find(hnode,C_TAG_ICS0, nindex++);
		}
	}
	return (found);
}

//===========================================================================
int CUPAR_GiveKey (unsigned char  *AidValue,
				   unsigned char  Index,
				   unsigned char  *Modulus,
				   unsigned short *ModulusLength,
				   unsigned char  *Exponent,
				   unsigned short *ExponentLength)
{
	int         i_l_found = FALSE;
	int         i_l_ResultInitCAKEYS;
	CA_PUB_KEY  key;

	i_l_ResultInitCAKEYS = CUPAR_GiveCAKEYS(&key, &AidValue[1], Index);
	if (i_l_ResultInitCAKEYS == FALSE)
		return (i_l_found);

	i_l_found = TRUE;
	/* Extract the values                                          */
	*ModulusLength  = key.length;
	memcpy(Modulus, key.modulus, key.length);
	*ExponentLength = key.exponentlength;
	memcpy(Exponent, key.exponent, key.exponentlength);

	return (i_l_found);
}

//===========================================================================
//! \brief This function inits AID structure.
//! \param[out] ptr_x_revok : 
//! \param[in] ptr_x_AID : 
//! \return
//! - Number of revoked key found.
//! - 0 otherwise.
//===========================================================================
static int CUPAR_InitKEY_REVOK(CA_REVOK * ptr_x_revok, unsigned char * ptr_x_AID)
{
	unsigned char uc_l_FirstAcces = 1;
	unsigned int  i_l_NumMark;
	int           cr;
	int           ResultMark;
	int           found = FALSE;
	int           revokIndex=0, lastIndex=0;
	DataElementExt data;


	// Select mark witch must be actived
	PAR_ResetMarkList();
	// Main mark of CAKEYS
	i_l_NumMark = C_TAG_CAREVOK;

	// input structure Reset
	memclr (ptr_x_revok, sizeof(CA_REVOK) * NB_CAKEY_REVOKED_PER_RID);

	// Loop on each CAKEYS
	do{
		memclr(&ptr_x_revok[revokIndex], sizeof(CA_REVOK));

		ResultMark = PAR_SelectNextMark(i_l_NumMark, uc_l_FirstAcces);
		if (ResultMark == 0)
			break;	// Loop end

		uc_l_FirstAcces = 0;

		cr = PAR_ReadParameter(TAG_AID_TERMINAL, &data);
		if ((cr) && (data.elt.length == LG_RID))
		{
			// Is it the good AID ?
			if (memcmp (ptr_x_AID, data.elt.ptValue, 5) != 0)
				// Next NumMark, this one isn't good
				continue;

			memcpy((unsigned char*)ptr_x_revok[revokIndex].rid, data.elt.ptValue, LG_RID);
		}
		else 
			continue;

		cr = PAR_ReadParameter(TAG_CERT_AUTH_PUB_KEY_INDEX_TERM, &data);
		if ((cr) && (data.elt.length == 1))
		{
			ptr_x_revok[revokIndex].index[0] = data.elt.ptValue[0];
		}
		else 
			continue;

		cr = PAR_ReadParameter(TAG_CUST_CERTIF_SERIAL_NO, &data);
		if ((cr) && (data.elt.length == 3))
		{
			memcpy((unsigned char*)ptr_x_revok[revokIndex].serial_number, data.elt.ptValue, 3);
			// Memorization of last index used
			lastIndex = revokIndex+1;
		}
		else 
			continue;

		found = TRUE;
		revokIndex++;
	}while ((ResultMark != 0) && (revokIndex < NB_CAKEY_REVOKED_PER_RID));	// End loop on each AID

	return (lastIndex);
}

//===========================================================================
int CUPAR_GiveAIDList(unsigned char *nb_aid, T_CUDB_AID_Elt *tab_AID)
{
	unsigned char FirstAcces = 1;

	// Reset buffer of keys
	unsigned int  i_l_NumMark;
	int           i_l_Result = FALSE;
	int           i_l_ResultMark;
	int           i_l_cr;
	DataElementExt eltExt;

	*nb_aid = 0;
	// Structure reset
	memset(tab_AID, 0, sizeof(T_CUDB_AID_Elt) * NB_AID_MAX);

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select mark witch must be actived
	// Default value, all is ok
	i_l_Result = TRUE;
	
	// Main mark of AID
	i_l_NumMark = C_TAG_AID;


	// Loop on each AID
	do{
		i_l_ResultMark = PAR_SelectNextMark(i_l_NumMark, FirstAcces);

		if (i_l_ResultMark == 0)
			break;	// End of list

		FirstAcces = 0;

		i_l_cr = PAR_ReadParameter(TAG_AID_TERMINAL, &eltExt);
		if (i_l_cr)
		{
			i_l_Result = TRUE;	// an AID has been found
			
			// Add AID in the output table
			tab_AID [*nb_aid].len_Aid = eltExt.elt.length;
			memcpy (tab_AID [*nb_aid].AID, eltExt.elt.ptValue, eltExt.elt.length);

			i_l_cr = PAR_ReadParameter(TAG_CUST_APPLICATION_SELECTION_ID, &eltExt);
			if (i_l_cr)
			{
				tab_AID [*nb_aid].ASI = (!(eltExt.elt.ptValue[0])) << 7;
			}
			else
			{
				// Default value : partial AID supported
				tab_AID [*nb_aid].ASI = 0x00;
			}

			(*nb_aid)++;
		}
	}while ((i_l_ResultMark != 0) && (i_l_Result));	// End loop on each AID

	return (i_l_Result);
}

//===========================================================================
int CUPAR_GiveAIDListTlvTree(unsigned char *nb_aid, TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned char	FirstAcces = 1;

	// Reset buffer of keys
	unsigned int	i_l_NumMark;
	int				i_l_Result = FALSE;
	int				i_l_ResultMark;
	int				i_l_cr;
	DataElement		elt;

	*nb_aid = 0;
	
	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select mark witch must be actived
	// Default value, all is ok
	i_l_Result = TRUE;
	
	// Main mark of AID
	i_l_NumMark = C_TAG_AID;

	// TLV tree creation
	*phOutputTLVTree = TlvTree_New(0);

	if(*phOutputTLVTree != NULL)
	{
		// Loop on each AID
		do{
			i_l_ResultMark = PAR_SelectNextMark(i_l_NumMark, FirstAcces);

			if (i_l_ResultMark == 0)
				break;	// End of list

			FirstAcces = 0;

			// i_l_cr = PAR_ReadParameter(TAG_AID_TERMINAL, &eltExt);
			i_l_cr = PAR_ReadParameter(TAG_AID_TERMINAL, (DataElementExt *)&elt);
			if (i_l_cr)
			{
				i_l_Result = TRUE;	// an AID has been found
				
				// Add AID in the output TLV tree
				TlvTree_AddChild(*phOutputTLVTree, elt.tag, elt.ptValue, elt.length);

				// i_l_cr = PAR_ReadParameter(TAG_CUST_APPLICATION_SELECTION_ID, &eltExt);
				i_l_cr = PAR_ReadParameter(TAG_CUST_APPLICATION_SELECTION_ID, (DataElementExt *)&elt);
				if (i_l_cr)
				{
					unsigned char val;
					val = (!(elt.ptValue[0])) << 7;
					elt.ptValue[0] = val;
				}
				else
				{
					// Default value : partial AID supported
					elt.ptValue[0] = 0x00;
				}
				
				TlvTree_AddChild(*phOutputTLVTree, elt.tag, elt.ptValue, elt.length);
				(*nb_aid)++;
			}

		}while ((i_l_ResultMark != 0) && (i_l_Result));	// End loop on each AID

	}

	return (i_l_Result);
}


//===========================================================================
void CUPAR_RestoreParam (unsigned char uc_x_FileMgtType)
{
	char FilePath_L[80];
	int rc,Mode;
	int ret = FS_OK;
	char InBuf[150];
	char OutBuf[80];
	char rStringTmp[250];
	unsigned char option = 0;
	char LabelDiskName[DISK_NAME_SIZE];

	memclr(FilePath_L,sizeof(FilePath_L));

	memclr(LabelDiskName, sizeof(LabelDiskName));
	CUDISK_Get_Disk_Name(LabelDiskName);


	if ( (uc_x_FileMgtType == C_MGT_PARAM_PAR_FILE) ||
		(uc_x_FileMgtType == C_MGT_PARAM_PAR_FILE_FIRST) )
	{
		sprintf(FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM);
		// Set path in input buffer for BuildParameters() call
		sprintf(InBuf, "/%s", LabelDiskName);
		ret = FS_exist (FilePath_L);
	}

	if  (((ret != FS_OK) && (uc_x_FileMgtType == C_MGT_PARAM_PAR_FILE_FIRST)) ||
		(uc_x_FileMgtType == C_MGT_TXT_PAR_FILES))
	{
		unsigned char FileIndex = 0;

		for (FileIndex=0; FileIndex<C_NB_OLD_FILES; FileIndex++)
		{
			sprintf(FilePath_L, "/%s/%s", LabelDiskName, C_OLD_FILES[FileIndex]);

			ret = FS_exist (FilePath_L);
			if (ret == FS_OK)
			{
				char strbuf[40];

				strcat (InBuf, " ");
				strcat (InBuf, (char *)C_OLD_FILES[FileIndex]);

				sprintf(strbuf, "CUPAR_RestoreParam(%s)",C_OLD_FILES[FileIndex]);
				trace(0, strlen(strbuf), strbuf);
			}
		}

		if (strlen(InBuf) > strlen(FilePath_L))
		{
			int i_retPB;

			sprintf(OutBuf, C_FILE_PARAM);
			// If param.par file not present, Try to manage AIDX.PAR, AID2, ... REVOK.PAR and CAKEYS.PAR
			// And try to build param.pr file
			i_retPB = Build_Parameters(C_WORK_FILES_TO_BIN, InBuf, OutBuf, rStringTmp, option);
		}
	}


	sprintf(FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM);

	ret = FS_exist (FilePath_L);
	if (ret == FS_OK)
	{
		Mode = FS_READMOD;
		rc   = FS_mount (FilePath_L, &Mode);
		if (rc != FS_OK)
		{
			trace(0, strlen("PB Mount COM Filen"), "PB Mount COM Filen");
			upload_diagnostic_txt((unsigned char *)"PB Mount COM Filen\n");
		}
		else
		{
			trace(0, strlen("Mount COM File ok"), "Mount COM File ok");
			trace(0, strlen("Load PARAM.PAR file"), "Load PARAM.PAR file");
			// Load parameter file in the terminal
			CUPAR_FileRead (FilePath_L, C_FILE_PARAM);
		}
	}


	memclr(FilePath_L,sizeof(FilePath_L));
	sprintf(FilePath_L, "/%s",LabelDiskName);
	FS_unmount(FilePath_L);
}

//===========================================================================
void CUPAR_FileCopy(char *DirFile, char *pc_x_fileName)
{
	int           ret, lg;
	unsigned int  Mode,rc;
	unsigned char uc_l_trace[60];
	char          FilePath_L[33], buff[MAX_FILE_LG];
	S_FS_FILE     *file1, *file2;
	char          LabelDiskName[DISK_NAME_SIZE];

	file2 = NULL;
	memset (buff, 0, MAX_FILE_LG);

	Mode         = FS_WRITEONCE;
	rc= FS_mount (DirFile,&Mode);
	if (rc != FS_OK)
	{
		upload_diagnostic_txt((unsigned char *)"PB Mount COM Filen\n");
	}
	else
	{
		file1 = FS_open (DirFile, "r");
		if (file1 == NULL)
		{
			sprintf(uc_l_trace, "FS_open(%s) ko\n", pc_x_fileName);
			upload_diagnostic_txt((unsigned char *)"uc_l_trace\n");
		}
		else
		{
			memclr(LabelDiskName, sizeof(LabelDiskName));
			CUDISK_Get_Disk_Name(LabelDiskName);

			FS_seek (file1, 0, FS_SEEKSET);
			/*        sprintf(FilePath_L, "/%s/%sAR",LabelDiskName,pc_x_fileName); */
			sprintf(FilePath_L, "/%s/%s",LabelDiskName,pc_x_fileName);

			Mode = FS_WRITEONCE;
			rc= FS_mount (FilePath_L,&Mode);
			if (rc != FS_OK)
			{
				upload_diagnostic_txt((unsigned char *)"PB Mount COM Filen\n");
			}
			else
			{
				ret = FS_exist (FilePath_L);
				if (ret == FS_OK)
					// suppress former file
					ret = FS_unlink (FilePath_L);

				file2 = FS_open (FilePath_L, "a");
				if (file2 == NULL)
				{
					sprintf(uc_l_trace, "FS_open(%s) ko\n", FilePath_L);
					upload_diagnostic_txt((unsigned char *)"uc_l_trace\n");
				}
				else
				{
					while ((lg = FS_read(&buff, 1, MAX_FILE_LG, file1))!= 0)
					{
						FS_write(&buff, 1, lg, file2);
					}
					FS_close(file2);
				}
			}
		}
		FS_close(file1);
	}
}

//===========================================================================
int CUPAR_GiveRevokedCA (unsigned char *AidValue, T_CUSERV_lst_tagCArevok *CA_revok)
{
	unsigned short i;
	unsigned short uc_l_nb_CA;
	unsigned short uc_l_ind_Tag_CA;
	int            found = 0, NbKeys;
	CA_REVOK       revok[NB_CAKEY_REVOKED_PER_RID];

	found = FALSE;
	i = 0;
	uc_l_nb_CA = 0;
	uc_l_ind_Tag_CA = 0;

	// Clear the storing revoked CA structure
	memset((unsigned char *)CA_revok, 0, sizeof(T_CUSERV_lst_tagCArevok));

	NbKeys = CUPAR_InitKEY_REVOK(revok, &AidValue[1]);
	if (NbKeys == 0)
		return (found);

	found = TRUE;

	// Loop on the revoked CA storing table
	for (i=0; (i<NB_CAKEY_REVOKED_PER_RID) && (uc_l_ind_Tag_CA<MAX_NB_TAG_FOR_REVOKED_CA) && (i<NbKeys); i++)
	{
		// Extract the values
		if (uc_l_nb_CA >= NB_MAX_REVOKED_PER_TAG)
		{
			uc_l_nb_CA=0;
			uc_l_ind_Tag_CA++;
		}
		CA_revok->Taglength[uc_l_ind_Tag_CA] = CA_revok->Taglength[uc_l_ind_Tag_CA]+9;
		memcpy (&CA_revok->revoked_CA [uc_l_ind_Tag_CA][uc_l_nb_CA*9], revok[i].rid, 5);
		memcpy (&CA_revok->revoked_CA [uc_l_ind_Tag_CA][(uc_l_nb_CA*9)+5], revok[i].index, 1);
		memcpy (&CA_revok->revoked_CA [uc_l_ind_Tag_CA][(uc_l_nb_CA*9) + 6], revok[i].serial_number, 3);
		uc_l_nb_CA++;
	}	// End of for loop
	return (found);
}

//===========================================================================
T_Bool CUPAR_BlackListInit (char *pc_x_fileName)
{
	char            value[512];
	char            *pValue;
	char            buf[MAX_FILE_LG];
	int             len;
	int             lg, index;
	int             Nb_elt;
	unsigned int    Mode,rc;
	// PAN sequence number shall be controlled in exception file
	unsigned char   bufPAN [12 * CUBLACKL_DEF_FILE_SIZE];
	unsigned long   tag;
	unsigned long   size_max;
	S_FS_FILE *file1;
	T_CUBLACKL_date ExpDate;
	T_Bool          success;

	// PAN sequence number shall be controlled in exception file
	memclr (bufPAN, 12 * CUBLACKL_DEF_FILE_SIZE);
	memset (buf, 0, MAX_FILE_LG);
	index=0;
	Nb_elt = 0;
	success = B_FALSE;


	Mode = FS_READMOD;
	rc= FS_mount (pc_x_fileName,&Mode);
	if (rc != FS_OK)
	{
		upload_diagnostic_txt((unsigned char *)"PB Mount COM Filen\n");
	}
	file1 = FS_open (pc_x_fileName, "r");
	if (file1 == NULL)
	{
		upload_diagnostic_txt((unsigned char *)pc_x_fileName);
		upload_diagnostic_txt((unsigned char *)"CUST\n");
	}
	else
	{
		FS_seek (file1, 0, FS_SEEKSET);
		pValue = value;
		size_max = sizeof(value);

		lg=FS_read (&buf, 1, MAX_FILE_LG, file1);
		lg++;

		while (CUPAR_read_next_element_text (buf, lg, &index, size_max, &tag, &len, pValue) == TRUE)
		{
			// PAN sequence number shall be controlled in exception file
			if ((tag == TAG_COMM_BLACK_LIST_FILE) && (len <= 20))
			{
				unsigned char ac_l_HexaValue[10];

				// Ascii -> hexa conversion
				// Return always TRUE
				PAR_ascii2bytes((unsigned char*)pValue, ac_l_HexaValue);

				memcpy (&(bufPAN [12 * Nb_elt]), ac_l_HexaValue, len/2);
				Nb_elt++;
				pValue += len;
				size_max -= len;
			}
		}
		FS_close(file1);

		ExpDate.date [0] = 39;
		ExpDate.date [1] = 12;
		ExpDate.date [2] = 31;

		// Replace black-list
		CUBLACKL_DeleteBlackList();
		CUBLACKL_CreateFile(CUBLACKL_DEF_FILE_SIZE);
		success = CUBLACKL_ReplaceBlackList ( bufPAN, Nb_elt, ExpDate);
	}
	return (success);
}

//===========================================================================
int CUPAR_Print_ICS_Config(void)
{
	CURECEIPT_Print_EMV_Config();
	return TRUE;
}


//===========================================================================
//! \brief This function builds a list of value with tags given as parameter.
//! \param[out] pc_x_buffer : buffer to update with tag value.
//! \param[in,out] pi_x_Index : index on pc_x_buffer.
//! \param[in] ps_x_ListPointer : tag list (Struct_TagList format).
//! \param[in] i_x_NbTag : number of tags in list.
//===========================================================================
static void BuildListValue(char * pc_x_buffer, int * pi_x_Index, Struct_TagList * ps_x_ListPointer, int i_x_NbTag)
{
	unsigned int    ListIndex;
	unsigned int    CarIndex;
	DataElementExt  data;

	for (ListIndex=0; (unsigned int)ListIndex<(unsigned int)i_x_NbTag; ListIndex++)
	{
		if (PAR_ReadParameter(ps_x_ListPointer[ListIndex].tag, &data))
			switch (ps_x_ListPointer[ListIndex].tagtype)
		{
			case C_TAG_TYPE_HEXA_BYTE:
				pc_x_buffer[(*pi_x_Index)++] = *(data.elt.ptValue);
				break;

			case C_TAG_TYPE_BUF_BYTE:
				memcpy(&pc_x_buffer[(*pi_x_Index)], data.elt.ptValue, data.elt.length);
				(*pi_x_Index) += data.elt.length;
				break;

			case C_TAG_TYPE_BUF_BYTE_WITH_MASQ:
				for (CarIndex = 0; CarIndex<data.elt.length; CarIndex++)
				{
					pc_x_buffer[(*pi_x_Index) + CarIndex] = data.elt.ptValue[CarIndex] & ps_x_ListPointer[ListIndex].Masq[CarIndex];
				}
				(*pi_x_Index) += data.elt.length;
				break;

			case C_TAG_TYPE_BOOLEAN:
				//                    CUPAR_SetBooleanValue (data.elt.ptValue, (unsigned char *)&pc_x_buffer[(*pi_x_Index)++]);
				pc_x_buffer[(*pi_x_Index)++] = *(data.elt.ptValue);
				break;

			case C_TAG_TYPE_TXT:
			default:
				// Not managed
				break;
		}
	}
}

static int Is_CVM_AMOUNT_KNOWN_SET(void)
{
	int           cr;
	DataElementExt data;


	cr = PAR_ReadParameter(TAG_CUST_IS_AMOUNT_UNKNOWN_BEFORE_CVM, &data);
	if ((cr) && (data.elt.length == 1))
	{
		if (data.elt.ptValue[0] == 1)
		{
	
				return(0);
		}
	}

	return(1);
}			

static int Is_SELECTABLE_KERNEL_SET(void)
{
	int           cr;
	DataElementExt data;

	cr = PAR_ReadParameter(TAG_CUST_IS_SELECTABLE_KERNEL, &data);
	if ((cr) && (data.elt.length == 1))
	{
		if (data.elt.ptValue[0] == 1)
		{
				return(1);
		}
	}

	return(0);
	
}

static int Is_DELETABLE_TAC_SET(void)
{
	int           cr;
	DataElementExt data;

	cr = PAR_ReadParameter(TAG_CUST_IS_DELETABLE_TAC, &data);
	if ((cr) && (data.elt.length == 1))
	{
		if (data.elt.ptValue[0] == 1)
		{
				return(1);
		}
	}

	return(0);;
}

//===========================================================================
//! \brief This function calculates the CRC of the current EMV configuration.
//! \return always TRUE.
//! \note This function updates the CRC tags after SHA calculation.
//===========================================================================
static int CUPAR_Compute_ICS_Config_CRC(void)
{
	unsigned char   buffer[80];
	unsigned char   value[60];
	unsigned int    i, Index;
	unsigned char * pSha;
	DataElementExt  data;

	memset (buffer, 0, sizeof (buffer));

	// ICS
	// Reset mark manager
	PAR_ResetMarkList();
	// Select first Mark child for ICS
	PAR_SelectMark(C_TAG_ICS0, C_TREE_ALL);

	// Kernel Version and Kernel CRC
	sprintf((char*)buffer, "%ld%lx", ct_KernelVersion, ct_KernelCRC);
	i = strlen((char*)buffer);


	if (Is_SELECTABLE_KERNEL_SET()||Is_DELETABLE_TAC_SET())
	{
		// Buffer build
		BuildListValue((char*)buffer, (int*)&i, (Struct_TagList *)FirstTagListEntireFull, sizeof(FirstTagListEntireFull) / sizeof(Struct_TagList));
	}
	else
	{
		if (!Is_CVM_AMOUNT_KNOWN_SET())
		{			
			// Buffer build
			BuildListValue((char*)buffer, (int*)&i, (Struct_TagList *)FirstTagListEntire, sizeof(FirstTagListEntire) / sizeof(Struct_TagList));
		}
		else
		{
			// Buffer build
			BuildListValue((char*)buffer, (int*)&i, (Struct_TagList *)FirstTagList, sizeof(FirstTagList) / sizeof(Struct_TagList));
		}
	}

	pSha = (unsigned char*)SHA1_Compute ((unsigned char*)buffer, i);

	for (Index = 0; Index < 20; Index++)
		sprintf((char*)&(value[2*Index]), "%02x", (int)pSha[Index]);

	data.elt.length = 40+1;
	data.elt.ptValue = value;
	data.elt.tag = TAG_CUST_FULL_CRC_CONFIG_FILE;
	PAR_SetParameter(TAG_CUST_FULL_CRC_CONFIG_FILE, data);

	/**********************************/
	/* CRC with only Major parameters */
	/**********************************/

	memset (buffer, 0, sizeof (buffer));
	i = 0;

	// Kernel Version and Kernel CRC
	sprintf((char*)buffer, "%ld%lx", ct_KernelVersion, ct_KernelCRC);
	i = strlen((char*)buffer);

	if (Is_SELECTABLE_KERNEL_SET()||Is_DELETABLE_TAC_SET())
	{
		// Buffer build
		BuildListValue((char*)buffer, (int*)&i, (Struct_TagList *)MajorTagListEntireFull, sizeof(MajorTagListEntireFull) / sizeof(Struct_TagList));
	}
	else
	{
		if (!Is_CVM_AMOUNT_KNOWN_SET())
		{
			// Buffer build
			BuildListValue((char*)buffer, (int*)&i, (Struct_TagList *)MajorTagListEntire, sizeof(MajorTagListEntire) / sizeof(Struct_TagList));
		}
		else
		{
			// Buffer build
			BuildListValue((char*)buffer, (int*)&i, (Struct_TagList *)MajorTagList, sizeof(MajorTagList) / sizeof(Struct_TagList));
		}
	}		

	pSha = (unsigned char*)SHA1_Compute ((unsigned char*)buffer, i);

	for (Index = 0; Index < 20; Index++)
		sprintf((char*)&(value[2*Index]), "%02x", (int)(pSha[Index]));

	data.elt.length = 40+1;
	data.elt.ptValue = value;
	data.elt.tag = TAG_CUST_CRC_CONFIG_FILE;
	PAR_SetParameter(TAG_CUST_CRC_CONFIG_FILE, data);

	return TRUE;
}

//===========================================================================
int CUPAR_Get_Param(unsigned long tag, unsigned char *value)
{
	// This function is keeped for compliant with previous version
	DataElementExt data;
	int cr;

	cr = PAR_ReadParameter(tag, &data);
	if (cr)
	{
		if ((data.elt.length == 1) && (data.elt.ptValue[0] == 0))
			sprintf(value, "NO");
		else if ((data.elt.length == 1) && (data.elt.ptValue[0] == 1))
			sprintf(value, "YES");
		else
			HexToAscii ((char*)data.elt.ptValue, data.elt.length, value);
	}
	else
		sprintf((char*)value, NONE);

	return (TRUE);
}

//===========================================================================
//! \brief This function builds the output file(s) (serial TLVTree binary format)
//! with tags read in input text file(s)
//! \param[in] c_x_WorkType : allow to select the work type. It can take the 
//! following values : 
//! - C_WORK_FILES_TO_BIN : input files may be AIDX.PAR, CAKEYS.PAR, KREVOK.PAR,
//! ICSX.PAR set in the ptr_TxtBuf.
//! - C_WORK_FILE_TO_BIN : input file will be only one file set in the ptr_TxtBuf.
//! \param[in] ptr_TxtBuf : text file (list).
//! \param[out] ptr_OutBuf : binary file (serial TVLTree binary format).
//! \param[out] ptr_rStringTmp : result of the function : text to display to the user.
//! \param[in] option : not used.
//! \return
//! - 0 if successfull.
//! - 1 otherwise.
//! \note This function allows to obtain parameters with old texts files.
//===========================================================================
static int Build_Parameters(unsigned char c_x_WorkType, char * ptr_TxtBuf, char * ptr_OutBuf, char * ptr_rStringTmp, unsigned char option)
{
	unsigned char FileIndex = 0;
	unsigned char * ac_l_pucBuffer = NULL;
	char          path[100];
	char          ac_l_Mark[50];
	char          ac_filearray[C_NB_MAX_TXT_FILE][100];
	char          * ptr_charindex;
	char          * ptr_charspace;
	unsigned int  ai_l_Mark[5];
	unsigned int  result = 0;
	unsigned int  i_l_Mark = C_TAG_XXXX, i_l_MarkDefault = C_TAG_XXXX;
	int n;
	TLV_TREE_NODE pTree = 0, pNodeResult;
	// Second level of entry point (node)
	TLV_TREE_NODE apSecondTree[5];
	S_FS_FILE     *ptr_file;

	// Input parameters control
	if (c_x_WorkType == C_WORK_FILES_TO_BIN)
	{
		if (strlen(ptr_TxtBuf) == 0) 
		{
			strcpy (ptr_rStringTmp, "Set input file(s)");
			return 1;
		}
	}
	else if (c_x_WorkType == C_WORK_FILE_TO_BIN)
	{
		if (strlen(ptr_TxtBuf) == 0) 
		{
			strcpy (ptr_rStringTmp, "Saisir le fichier d'entrée");
			return 1;
		}
	}
	else // Only two work types are allowed
	{
		strcpy (ptr_rStringTmp, "Bad work type");
		return 1;
	}

	if (strlen(ptr_OutBuf) == 0)	// If no binary file was inputed
	{
		strcpy (ptr_rStringTmp, "Set input file");
		return 1;
	}


	// Initialisation of file arrays

	memset(ac_filearray, 0, sizeof(ac_filearray));
	memset(apSecondTree, 0, sizeof(apSecondTree));
	memset(ai_l_Mark,    0, sizeof(ai_l_Mark));


	// Parameters storage
	// If AIDX, CAKEYS, KREVOK ICSX -> serial TLVTree file process
	if(c_x_WorkType == C_WORK_FILES_TO_BIN) 
	{

		// Path copy
		ptr_charspace = strstr(ptr_TxtBuf, (const char *)" ");
		if (ptr_charspace != NULL)
		{
			strncpy(path, ptr_TxtBuf, ptr_charspace-ptr_TxtBuf);
			path[ptr_charspace-ptr_TxtBuf] = 0;
		}
		else
			strcpy(path, ptr_TxtBuf);


		if (ptr_charspace != NULL)
			ptr_charindex = ptr_charspace+1;
		else 
			ptr_charindex = ptr_TxtBuf;

		do{
			ptr_charspace = strstr(ptr_charindex, " ");

			// if there is no separator, that means there is only one file.
			if ((ptr_charspace == NULL) && (FileIndex==0))
			{
				strcpy(ac_filearray[FileIndex++], ptr_TxtBuf);
			}
			else 
			{
				strcpy(ac_filearray[FileIndex], path);
				ac_filearray[FileIndex][strlen(path)] = 0;
				strcat(ac_filearray[FileIndex], "\\");
				// if there is no more separator, that means this is the last file.
				if (ptr_charspace == NULL)
				{
					strcat(ac_filearray[FileIndex++], ptr_charindex);
				}
				else
				{
					strncat(ac_filearray[FileIndex++], ptr_charindex, ptr_charspace-ptr_charindex);
				}
			}
			ptr_charindex = ptr_charspace+1;

		}while ((ptr_charspace != NULL) && (FileIndex<C_NB_MAX_TXT_FILE));	// If it's the end of the string
	}
	else // if (c_x_WorkType == C_WORK_FILE_TO_BIN)  // If text file -> serial TLVTree file process
	{

	}


	if (c_x_WorkType == C_WORK_FILES_TO_BIN)	// If AIDX, CAKEYS, KREVOK ICSX -> serial TLVTree file process
	{
		// For each text file
		for (FileIndex=0; FileIndex<C_NB_MAX_TXT_FILE; FileIndex++)
		{
			// If something => select adapted mark
			if (strlen(ac_filearray[FileIndex]))
			{
				strcpy(ac_l_Mark, C_MARK_XXXX);
				if ((strstr(ac_filearray[FileIndex], C_AID_NAME) != NULL) || (strstr(ac_filearray[FileIndex], "aid") != NULL))
				{
					i_l_Mark = C_TAG_AID;
					strcpy(ac_l_Mark, C_MARK_AID);
				}
				else if ((strstr(ac_filearray[FileIndex], C_CAKEYS_NAME) != NULL) || (strstr(ac_filearray[FileIndex], "cakeys") != NULL))
				{
					i_l_Mark = C_TAG_CAKEYS;
					strcpy(ac_l_Mark, C_MARK_CAKEYS);
				}
				else if ((strstr(ac_filearray[FileIndex], C_KREVOK_NAME) != NULL) || (strstr(ac_filearray[FileIndex], "krevok") != NULL))
				{
					i_l_Mark = C_TAG_CAREVOK;
					strcpy(ac_l_Mark, C_MARK_CAREVOK);
				}
				if ((strstr(ac_filearray[FileIndex], C_ICS_NAME) != NULL) || (strstr(ac_filearray[FileIndex], "ics") != NULL))
				{
					i_l_Mark = C_TAG_ICS;
					strcpy(ac_l_Mark, C_MARK_ICS);
				}
				else
				{
					i_l_Mark = i_l_MarkDefault;
					i_l_MarkDefault += 0x10;
				}

				// First call
				if(pTree == 0)
					pTree = TlvTree_New(C_TAG_MAIN);

				// Manage under-node entry-point
				if ((ai_l_Mark[C_INDEX_AID] == 0) && (i_l_Mark == C_TAG_AID))
				{
					pNodeResult = TlvTree_AddChildString( pTree, i_l_Mark, ac_l_Mark);
					apSecondTree[C_INDEX_AID] = pNodeResult;
					ai_l_Mark[C_INDEX_AID] = C_TAG_AID;
				}
				else if ((ai_l_Mark[C_INDEX_REVOK] == 0) && (i_l_Mark == C_TAG_CAREVOK))
				{
					pNodeResult = TlvTree_AddChildString( pTree, i_l_Mark, ac_l_Mark);
					apSecondTree[C_INDEX_REVOK] = pNodeResult;
					ai_l_Mark[C_INDEX_REVOK] = C_TAG_CAREVOK;
				}
				else if ((ai_l_Mark[C_INDEX_CAKEYS] == 0) && (i_l_Mark == C_TAG_CAKEYS))
				{
					pNodeResult = TlvTree_AddChildString( pTree, i_l_Mark, ac_l_Mark);
					apSecondTree[C_INDEX_CAKEYS] = pNodeResult;
					ai_l_Mark[C_INDEX_CAKEYS] = C_TAG_CAKEYS;
				}
				// Manage under-node entry-point
				else if ((ai_l_Mark[C_INDEX_ICS] == 0) && (i_l_Mark == C_TAG_ICS))
				{
					pNodeResult = TlvTree_AddChildString( pTree, i_l_Mark, ac_l_Mark);
					apSecondTree[C_INDEX_ICS] = pNodeResult;
					ai_l_Mark[C_INDEX_ICS] = C_TAG_ICS;
				}
				else if ((i_l_Mark != C_TAG_AID)     &&	// Unknown mark
						(i_l_Mark != C_TAG_CAREVOK) &&
						(i_l_Mark != C_TAG_CAKEYS)  &&
						(i_l_Mark != C_TAG_ICS) )
				{
					pNodeResult = TlvTree_AddChildString( pTree, i_l_Mark, ac_l_Mark);
					apSecondTree[C_INDEX_UNKNOWN] = pNodeResult;
					ai_l_Mark[C_INDEX_UNKNOWN] = C_TAG_XXXX;
				}


				if (i_l_Mark == C_TAG_AID)
					i_l_Mark = ++ai_l_Mark[C_INDEX_AID];
				else if (i_l_Mark == C_TAG_CAREVOK)
					i_l_Mark = ++ai_l_Mark[C_INDEX_REVOK];
				else if (i_l_Mark == C_TAG_CAKEYS)
					i_l_Mark = ++ai_l_Mark[C_INDEX_CAKEYS];
				else if (i_l_Mark == C_TAG_ICS)
					i_l_Mark = ++ai_l_Mark[C_INDEX_ICS];
				else // if (i_l_Mark == C_TAG_UNKNOWN)
					i_l_Mark = ++ai_l_Mark[C_INDEX_UNKNOWN];

				// Update binary files
				if (CUPAR_ReadTextParamFile(&pNodeResult, i_l_Mark, ac_l_Mark, ac_filearray[FileIndex]) != 0)
				{
					strcpy (ptr_rStringTmp, "Input file ko");
					return (1);
				}
			}
		}
	}

	ac_l_pucBuffer = (unsigned char *) umalloc(C_PUC_BUFFER_SIZE);

	// For check
	// int m = TlvTree_GetSerializationSize( pTree, TLV_TREE_SERIALIZER_DEFAULT);
	n = TlvTree_Serialize( pTree, TLV_TREE_SERIALIZER_DEFAULT, ac_l_pucBuffer, C_PUC_BUFFER_SIZE );

	TlvTree_Release( pTree );
	pTree = 0;

	// Save buffer in file

	ptr_file = FS_open (ptr_OutBuf, "a");
	if (ptr_file == NULL)
	{
		sprintf(ac_l_Mark, "FS_open(%s) ko\n", ptr_OutBuf);
		upload_diagnostic_txt((unsigned char *)ac_l_Mark);
		return 1;
	}

	FS_write (ac_l_pucBuffer, 1, n, ptr_file);

	// Close file
	FS_close(ptr_file);

	// If result may be checked
	if (option)
	{
		unsigned int Mode,rc;

		// Open serial TLVTree binary file
		memset (ac_l_pucBuffer, 0, C_PUC_BUFFER_SIZE);

		Mode = FS_READMOD;
		rc= FS_mount (ptr_OutBuf,&Mode);
		if (rc != FS_OK)
		{
			upload_diagnostic_txt((unsigned char *)"PB Mount COM Filen\n");
			return 1;
		}

		ptr_file = FS_open (ptr_OutBuf, "r");
		if (ptr_file == NULL)
		{
			sprintf(ac_l_Mark, "FS_open(%s) ko\n", ptr_OutBuf);
			upload_diagnostic_txt((unsigned char *)ac_l_Mark);
			return 1;
		}

		FS_read (ac_l_pucBuffer, 1, C_PUC_BUFFER_SIZE, ptr_file);
		// Close file
		FS_close(ptr_file);

		TlvTree_Unserialize( &pTree, TLV_TREE_SERIALIZER_DEFAULT, ac_l_pucBuffer, C_PUC_BUFFER_SIZE );
		//        CUPAR_TlvTree_Display(pTree, "Check param.par built");

		TlvTree_Release( pTree );
		pTree = 0;
	}
	ufree(ac_l_pucBuffer);

	strcpy (ptr_rStringTmp, "Ok");
	return (result);
}


//===========================================================================
//! \brief This function updates the output file(s) (serial TLVTree binary format)
//! with previous TLVTree updated with data read in text file given in parameter.
//! \param[in] pTree : input TLV tree.
//! \param[in] ptr_TxtBuf : text file.
//! \param[out] ptr_OutBuf : binary file (serial TVLTree binary format).
//! \param[out] ptr_rStringTmp : result of the function : text to display to the user.
//! \param[in] option : not used.
//! \return
//! - 0 if successfull.
//! - 1 otherwise.
//===========================================================================
static int Update_Parameters_file(TLV_TREE_NODE pTree, char * ptr_TxtBuf, char * ptr_OutBuf, char * ptr_rStringTmp, unsigned char option)
{
	char          ac_l_Mark[50];
	unsigned int  result = 0;
	unsigned int  i_l_Mark = C_TAG_XXXX;
	TLV_TREE_NODE hnode;

	// Input parameters control
	strcpy (ptr_rStringTmp, "KO");

	if ((strlen(ptr_TxtBuf) == 0) || 
		(strlen(ptr_OutBuf) == 0) /* ||
		(pTree == 0) */)
	{
		return 1;
	}

	strcpy(ac_l_Mark, C_MARK_XXXX);
	if ((strstr(ptr_TxtBuf, "AID1") != NULL) || (strstr(ptr_TxtBuf, "aid1") != NULL))
	{
		i_l_Mark = C_TAG_AID1;
		strcpy(ac_l_Mark, C_MARK_AID1);
	}
	else if ((strstr(ptr_TxtBuf, "AID2") != NULL) || (strstr(ptr_TxtBuf, "aid2") != NULL))
	{
		i_l_Mark = C_TAG_AID2;
		strcpy(ac_l_Mark, C_MARK_AID2);
	}
	else if ((strstr(ptr_TxtBuf, "AID3") != NULL) || (strstr(ptr_TxtBuf, "aid3") != NULL))
	{
		i_l_Mark = C_TAG_AID3;
		strcpy(ac_l_Mark, C_MARK_AID3);
	}
	else if ((strstr(ptr_TxtBuf, "AID4") != NULL) || (strstr(ptr_TxtBuf, "aid4") != NULL))
	{
		i_l_Mark = C_TAG_AID4;
		strcpy(ac_l_Mark, C_MARK_AID4);
	}
	else if ((strstr(ptr_TxtBuf, "AID5") != NULL) || (strstr(ptr_TxtBuf, "aid5") != NULL))
	{
		i_l_Mark = C_TAG_AID5;
		strcpy(ac_l_Mark, C_MARK_AID5);
	}
	else if ((strstr(ptr_TxtBuf, "CAKEYS") != NULL) || (strstr(ptr_TxtBuf, "cakeys") != NULL))
	{
		i_l_Mark = C_TAG_CAKEYS;
		strcpy(ac_l_Mark, C_MARK_CAKEYS);
	}
	else if ((strstr(ptr_TxtBuf, "KREVOK") != NULL) || (strstr(ptr_TxtBuf, "krevok") != NULL))
	{
		i_l_Mark = C_TAG_CAREVOK;
		strcpy(ac_l_Mark, C_MARK_CAREVOK);
	}
	else if ((strstr(ptr_TxtBuf, "ICS1") != NULL) || (strstr(ptr_TxtBuf, "ics1") != NULL))
	{
		i_l_Mark = C_TAG_ICS1;
		strcpy(ac_l_Mark, C_MARK_ICS1);
	}
	else if ((strstr(ptr_TxtBuf, "ICS2") != NULL) || (strstr(ptr_TxtBuf, "ics2") != NULL))
	{
		i_l_Mark = C_TAG_ICS2;
		strcpy(ac_l_Mark, C_MARK_ICS2);
	}
	else if ((strstr(ptr_TxtBuf, "ICS3") != NULL) || (strstr(ptr_TxtBuf, "ics3") != NULL))
	{
		i_l_Mark = C_TAG_ICS3;
		strcpy(ac_l_Mark, C_MARK_ICS3);
	}
	else if ((strstr(ptr_TxtBuf, "ICS4") != NULL) || (strstr(ptr_TxtBuf, "ics4") != NULL))
	{
		i_l_Mark = C_TAG_ICS4;
		strcpy(ac_l_Mark, C_MARK_ICS4);
	}
	else if ((strstr(ptr_TxtBuf, "ICS5") != NULL) || (strstr(ptr_TxtBuf, "ics5") != NULL))
	{
		i_l_Mark = C_TAG_ICS5;
		strcpy(ac_l_Mark, C_MARK_ICS5);
	}
    /*&BEGIN FT/09/4668/MA acceptance of ICS_0xxx.par file*/
    else if ((strstr(ptr_TxtBuf, "ICS") != NULL) || (strstr(ptr_TxtBuf, "ics") != NULL))
    {
        i_l_Mark = C_TAG_ICS0;
        strcpy(ac_l_Mark, C_MARK_ICS0);
    }
	/*&END FT/09/4668/MA acceptance of ICS_0xxx.par file*/

	if (i_l_Mark != C_TAG_XXXX)
	{
		// Looking for the node in the parameters data
		hnode = PAR_FoundMarkInTree(pTree, i_l_Mark);
		// If Mark founded
		if (hnode != NULL)
		{
			// Delete old parameters
			TlvTree_Release(hnode);
			hnode = 0;
		}

		// Looking for the main mark tag
		// For these tag, origin is C_TAG_AID
		if ((i_l_Mark == C_TAG_AID1) ||
			(i_l_Mark == C_TAG_AID2) ||
			(i_l_Mark == C_TAG_AID3) ||
			(i_l_Mark == C_TAG_AID4) ||
			(i_l_Mark == C_TAG_AID5))
		{
			// Update with C_TAG_AID as origin
			hnode = PAR_FoundMarkInTree(pTree, C_TAG_AID);
			// Warning if C_TAG_AID not present
			if (hnode == NULL)
				hnode = TlvTree_AddChildString(pTree, C_TAG_AID, C_MARK_AID);
		}
		// For these tag, origin is C_TAG_ICS
		else if ((i_l_Mark == C_TAG_ICS0) ||
			(i_l_Mark == C_TAG_ICS1) ||
			(i_l_Mark == C_TAG_ICS2) ||
			(i_l_Mark == C_TAG_ICS3) ||
			(i_l_Mark == C_TAG_ICS4) ||
			(i_l_Mark == C_TAG_ICS5))
		{	
			// Update with C_TAG_ICS as origin
			hnode = PAR_FoundMarkInTree(pTree, C_TAG_ICS);
			// Warning if C_TAG_ICS not present
			if (hnode == NULL)
				hnode = TlvTree_AddChildString(pTree, C_TAG_ICS, C_MARK_ICS);
		}
		else
		{
			// Manage sous-node entry-point
			hnode = TlvTree_AddChildString( pTree, i_l_Mark, ac_l_Mark);
			i_l_Mark++;
		}

		if (hnode == 0)
		{
			strcpy (ptr_rStringTmp, "Problème sur organisation données");
			result = 1;
		}

		// If ok
		if (result == 0)
		{
			// Update binary files
			if (CUPAR_ReadTextParamFile(&hnode, i_l_Mark, ac_l_Mark, ptr_TxtBuf) != 0)
			{
				strcpy (ptr_rStringTmp, "Problème sur fichier d'entrée");
				result = 1;
			}
		}

		// Warning : if file given was empty, marq has been created empty in TLVTree struct
		// In this case, we will destroy it
		hnode = PAR_FoundMarkInTree(pTree, i_l_Mark);
		// if marq present
		if (hnode != NULL)
		{
			TLV_TREE_NODE hChildnode;
			hChildnode = TlvTree_GetFirstChild(hnode);
			// If no child
			if (hChildnode == NULL)
			{
				// Delete empty entry point
				TlvTree_Release(hnode);
				hnode = 0;
			}
		}

		// If ok
		if (result == 0)
		{
			// If a problem occurs
			if (CUPAR_WriteAllBinFile(pTree, ptr_OutBuf) != 0)
			{
				strcpy (ptr_rStringTmp, "Problème sur le fichier binaire format TLVTree");
				result = 1;
			}
		}
	}

	if (result == 0)
		strcpy (ptr_rStringTmp, "Update_Parameters_file ok");

	return (result);
}

//===========================================================================
int CUPAR_Update_Kernel_and_System_Infos (void)
{
	int           i;
	int           iMaxAppli;
	int           iMaxDriver;
	object_info_t infos;

	ct_KernelVersion =    0;
	ct_KernelCRC =        0;
	ct_SystemVersion =    0;
	ct_SystemCRC =        0;

	// Kernel
	iMaxAppli = ObjectGetNumber(OBJECT_TYPE_APPLI);
	for (i = 0; i < iMaxAppli; i ++)
	{
		if (ObjectGetInfo(OBJECT_TYPE_APPLI, i, &infos) == 0)
		{
			// Application EMV DC
			if (infos.application_type == EMVDC_TYPE)
			{
				ct_KernelVersion = atoi(infos.name);
				ct_KernelCRC = infos.crc;
			}
		}
	}

	// System
	iMaxDriver = ObjectGetNumber(OBJECT_TYPE_APPLI);
	for (i = 0; i < iMaxAppli; i ++)
	{
		if (ObjectGetInfo(OBJECT_TYPE_DRIVER, i, &infos) == 0)
		{
			// Driver System
			if (infos.application_type == SYSTEM_TYPE)
			{
				ct_SystemVersion = atoi(infos.name);
				ct_SystemCRC = infos.crc;
			}
		}
	}

	return TRUE;
}

//===========================================================================
void CUPAR_UpdateGlobalParam (void)
{
	int merchLang;
	unsigned char ac_l_chaine [40];
	unsigned long ul_l_fct_ksu;
	unsigned char uc_l_tmp_lg_9 [ 9 ]  ;
	const unsigned char CUPAR_TRUE_BYTE [] = {0x01};
	TLV_TREE_NODE hTree;

	//----------------------------------------------------------------------
	// Fill Inquiry TLV tree                                                
	//----------------------------------------------------------------------
	// Retreive Terminal merchant language
	merchLang = PSQ_Give_Language();
	if (merchLang > C_NBLANGMERCH)
	{
		merchLang = 0;
	}


	//----------------------------------------------------------------------
	// Fill Global DataBase                                                 
	//----------------------------------------------------------------------
	hTree = TlvTree_New(0);
	if (hTree != NULL)
	{
		strcpy ((char* ) ac_l_chaine, CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_APPLI_NAME, merchLang));
		TlvTree_AddChild(hTree, TAG_CUST_APPLI_NAME, ac_l_chaine, strlen ((char *) ac_l_chaine));

		strcpy ((char *) ac_l_chaine, CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_IDLE_MESS, merchLang));
		TlvTree_AddChild(hTree, TAG_CUST_IDLE_MESSAGE, ac_l_chaine, strlen ((char *) ac_l_chaine));

		CUTERMgetTerminalId ( (char *)uc_l_tmp_lg_9) ;
		TlvTree_AddChild(hTree, TAG_TERMINAL_IDENTIFICATION, uc_l_tmp_lg_9, LEN_TERMINAL_IDENTIFICATION);

		ul_l_fct_ksu = SCH_PINCODE_OFFLINE;
		TlvTree_AddChild(hTree, TAG_SCHEMAS_KSU, (unsigned char *) &ul_l_fct_ksu, 4);

		CUTERMgetSerialNumber((char*)uc_l_tmp_lg_9);
		TlvTree_AddChild(hTree, TAG_IFD_SERIAL_NUMBER, uc_l_tmp_lg_9, 8);

		TlvTree_AddChild(hTree, TAG_COMPATIBILITY_2000, &ucMode2000, LEN_COMPATIBILITY_2000);

		TlvTree_AddChild(hTree, TAG_CUST_IS_COMM_MANAGED_BY_CUSTOM, (unsigned char*)CUPAR_TRUE_BYTE, 1);

		TlvTree_AddChild(hTree, TAG_WAIT_AFTER_ATR, &ucDelayAfterAtr, 1);

		CUDB_StoreTLVTree (&hTree);

		// release local TLV tree
		TlvTree_ReleaseEx(&hTree);

	}

}



#ifdef _TOOLWARE_
//===========================================================================
int CUPAR_Init_ToolWare(void)
{
	// Find a solution to retreive if the kernel were compiled with TOOLWARE
	ct_KernelSupportToolWare = TRUE;

	// Check if the System version support the function
	// get_tick_counter()
	// This function was implemented the first time into the version 0174
	/*    if (ct_SystemVersion < 30100174)
	{
	ct_SystemSupportToolWare = FALSE;
	}
	else*/
	{
		ct_SystemSupportToolWare = TRUE;
	}

	return TRUE;
}

#endif /* _TOOLWARE_ */


#ifdef _USE_UCM_
//===========================================================================
//! \brief This function performs a service call to EMV tool to configure
//! the output peripheral.
//! \param i_x_nLink : link to configure. (printer, USB, COM0).
//! \param i_x_nBaudrate : communication speed.
//===========================================================================
static void EmvTool_Configure(int i_x_nLink, int i_x_nBaudrate)
{
	T_STRUCT_PROCESS_CONFIGURE Struct;
	int i_l_nResult;

	memset(&Struct, 0, sizeof(Struct));

	Struct.type_code = EMV_TOOL_APPLI_TYPE;
	Struct.service = EMV_TOOL_SERVICE_CONFIGURE;
	Struct.function = 0;

	Struct.nLink = i_x_nLink;
	Struct.nBaudrate = i_x_nBaudrate;

	ServiceCall(EMV_TOOL_APPLI_TYPE, EMV_TOOL_SERVICE_CONFIGURE, sizeof(Struct), &Struct, &i_l_nResult);
}

//===========================================================================
//! \brief This function performs a service call to EMV tool to get the trace
//! of the last transaction.
//! \param bDetailed : boolean indicating if the trace should be detailed or not.
//===========================================================================
static void EmvTool_DumpTrace(int i_x_bDetailed)
{
	T_STRUCT_PROCESS_DUMP_TRACE Struct;
	int i_l_nResult;

	memset(&Struct, 0, sizeof(Struct));

	Struct.type_code = EMV_TOOL_APPLI_TYPE;
	Struct.service = EMV_TOOL_SERVICE_DUMP_TRACE;
	Struct.function = 0;

	Struct.bDetailed = i_x_bDetailed;

	ServiceCall(EMV_TOOL_APPLI_TYPE, EMV_TOOL_SERVICE_DUMP_TRACE, sizeof(Struct), &Struct, &i_l_nResult);
}

//===========================================================================
//! \brief This function performs a service call to EMV tool to get the tags.
//===========================================================================
static void EmvTool_DumpTags(void)
{
	T_STRUCT_PROCESS_DUMP_TAGS Struct;
	int i_l_nResult;

	memset(&Struct, 0, sizeof(Struct));

	Struct.type_code = EMV_TOOL_APPLI_TYPE;
	Struct.service = EMV_TOOL_SERVICE_DUMP_TAGS;
	Struct.function = 0;

	Struct.bDumpAll = TRUE;

	ServiceCall(EMV_TOOL_APPLI_TYPE, EMV_TOOL_SERVICE_DUMP_TAGS, sizeof(Struct), &Struct, &i_l_nResult);
}

//===========================================================================
int DumpTags(void)
{
	EmvTool_DumpTags();
	EmvTool_DumpTrace(TRUE);
	return OK;
}

//===========================================================================
void SetOutputCom0(void)
{
	EmvTool_Configure(EMV_TOOL_OUTPUT_COM0, 9600);
}

#endif /* _USE_UCM_ */

//===========================================================================
unsigned long PAR_SelectFatherAID(DataElementExt data)
{
	unsigned long tag;
	int           i_l_Result = 0;
	unsigned int  nindex = 0, length, data_elt_length;
	unsigned char * ptr_l_data;
	unsigned char * data_elt_ptValue;
	TLV_TREE_NODE pTree;
	unsigned long ul_l_FatherMarq = 0;

	// Initialisation

	// Look for the tag in the pTreeAppli TLVTree
	do{
		data_elt_length  = data.elt.length;
		data_elt_ptValue = data.elt.ptValue;

		pTree = TlvTree_Find(pTreeParam, data.elt.tag, nindex++);
		// If a node has been obtain
		if (pTree != NULL)
		{
			// Get tag data to check if it start with Mark_XXX
			length = TlvTree_GetLength(pTree);
			ptr_l_data = (unsigned char *)TlvTree_GetData(pTree);

			// If check may be shorter than normal tag length
			if (length != data_elt_length)
			{
				if (length > data_elt_length)
				{
					length = data_elt_length = data_elt_length - 1;
				}
				else
				{
					data_elt_length = length = length - 1;
				}
				// First byte must be ignored
				ptr_l_data ++;
				data_elt_ptValue++;
			}

			if ((length == data_elt_length) && (memcmp(ptr_l_data, data_elt_ptValue, length) == 0))
			{
				i_l_Result = 1;
			}
		}
	}while ((pTree != NULL) && (i_l_Result == 0));

	nindex = 0;
	// Looking for the mark in the default parameters TLVTree
	if (pTree == NULL)
	{
		do{
			data_elt_length  = data.elt.length;
			data_elt_ptValue = data.elt.ptValue;

			pTree = TlvTree_Find(pTreeDefault, data.elt.tag, nindex++);
			// If a node has been obtained
			if (pTree != NULL)
			{
				// Get tag data to check if it start with Mark_XXX
				length = TlvTree_GetLength(pTree);
				ptr_l_data = (unsigned char *)TlvTree_GetData(pTree);

				// If check may be shorter than normal tag length
				if (length != data_elt_length)
				{
					if (length > data_elt_length)
					{
						length = data_elt_length = data_elt_length - 1;
					}
					else
					{
						data_elt_length = length = length - 1;
					}
					// First byte must be ignored
					ptr_l_data ++;
					data_elt_ptValue++;
				}

				if ((length == data.elt.length) && (memcmp(ptr_l_data, data_elt_ptValue, length) == 0))
				{
					i_l_Result = 1;
				}
			}
		}while ((pTree != NULL) && (i_l_Result == 0));
	}

	// If tag found
	if (i_l_Result == 1)
	{
		TLV_TREE_NODE pFatherNode;

		pFatherNode = pTree;
		// Up to found father marq
		do{
			pFatherNode = TlvTree_GetParent(pFatherNode);
			if (PAR_IsAMark(pFatherNode))
			{
				tag = TlvTree_GetTag(pFatherNode);
				// If ok
				if (PAR_SelectMark(tag, C_TREE_PARAM_FIRST) == 0)
				{
					ul_l_FatherMarq = tag;
				}
			}
		}while ((pFatherNode != NULL) && (ul_l_FatherMarq == 0));
	}
	return (ul_l_FatherMarq);
}

//! @}

