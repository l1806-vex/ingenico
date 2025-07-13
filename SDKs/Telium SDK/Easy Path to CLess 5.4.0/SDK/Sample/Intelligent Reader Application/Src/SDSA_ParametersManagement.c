/**
 * \file	SDSA_ParametersManagement.c
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


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDSA_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define MAX_FILE_LG						1024		/*!< max length buf for file. */
#define DISK_NAME_SIZE					33			/*!< Size of disk name. */


//! \brief TagAccess Tag reading access type
#define TAG_READING						1			/*!<  */
#define VALUE_READING					3			/*!<  */


//! \brief Action when a tag is allready found in destination TLVTree
#define C_PARAMS_NO_ACTION				0			/*!<  */
#define C_PARAMS_DELETE					1			/*!<  */


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////


//! \brief Global TLV Tree used for parameters management.
TLV_TREE_NODE pTreeCurrentParam = NULL;						/*!< Node from param file parameters. */

static char gs_Label_Disk_Name[DISK_NAME_SIZE];				/*!< To store the disk name. */

static T_PARAMETER_AID gs_Parameter_AID[C_NUMBER_AID_MAX];	/*!< Static structure containing all the AID data prepared before card presentation. */
static int gs_nNbParameterSet; 								/*!< Static data containing the number of configured AID. */

static int nNbMoneyExtended = 0;
static S_MONEY_EXTENDED * ptr_money_extended = NULL;


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static void __SDSA_Parameters_Get_Disk_Name(char* ptDiskName);
static void __SDSA_Parameters_SetKRevokParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID);
static void __SDSA_Parameters_SetKernelParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID);
static void __SDSA_Parameters_SetGlobalParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID);

static int __SDSA_Parameters_FileRead(TLV_TREE_NODE * pTree, char *pc_x_DirFile, char *pc_x_fileName);
static int __SDSA_Parameters_WriteBinFile(TLV_TREE_NODE pTree, char * ptr_OutBuf);
static int __SDSA_Parameters_ReadParamFile(TLV_TREE_NODE * p_node, char *pc_x_DirFile, unsigned int i_x_ParamFileType);
static int __SDSA_Parameters_CreateDisk (void);
static int __SDSA_Parameters_IsTagAlreadyInTLVTree(TLV_TREE_NODE pTree, unsigned long ulTag, unsigned int nAction);;
static int __SDSA_Parameters_CopyParameters( const TLV_TREE_NODE hDestTree, const TLV_TREE_NODE hSrcTree, int nParametersType);
static int __SDSA_Parameters_SetAIDParametersInFinalStruct(TLV_TREE_NODE pnode);
static int __SDSA_Parameters_EncodeTLVTreeInShareBuf(int nNbAID);
static int __SDSA_Parameters_AddTLVTreeInShareBuf (int nNumAID);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief This function reads a file of parameters (XML format) and extract tags and value to build a TLVTree. 
//! \param[in] pTree to go throw to found tag informations.
//! \param[in] pc_x_DirFile file path of xml text file to read.
//! \param[in] pc_x_fileName file name of xml text file to read.
//! \return
//! - 0 if file read ok, 1 else.

static int __SDSA_Parameters_FileRead(TLV_TREE_NODE * pTree, char *pc_x_DirFile, char *pc_x_fileName)
{
	char ac_l_OutBuf[80];
	char LabelDiskName[DISK_NAME_SIZE];
	int nResult = 0;

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__SDSA_Parameters_Get_Disk_Name(LabelDiskName);

	sprintf(ac_l_OutBuf, "/%s/%s", LabelDiskName, C_FILE_PARAM_SAV);

	if ((strncmp(pc_x_fileName, C_FILE_NAME_XML, sizeof(C_FILE_NAME_XML)-1) == 0)	||
		(strncmp(pc_x_fileName, C_FILE_PARAM_SAV, sizeof(C_FILE_PARAM_SAV)-1) == 0) )
	{
		unsigned int FileTypeAccess = TLV_TREE_SERIALIZER_DEFAULT;

		if (strncmp(pc_x_fileName, C_FILE_NAME_XML, sizeof(C_FILE_NAME_XML)-1) == 0)
		{
			// XML format used to load parameter
			FileTypeAccess = TLV_TREE_SERIALIZER_XML;
		}

		if (__SDSA_Parameters_ReadParamFile(pTree, pc_x_DirFile, FileTypeAccess) != 0)
		{
			GTL_Traces_TraceDebug ("__SDSA_Parameters_ReadParamFile() error");
			nResult = 1;
		}
	}
	return (nResult);
}



//! \brief This function update a file with parameters given in a TLVTree.
//! File is updated in TLVTree serial binary format.
//! \param[in] pTree to go save in file.
//! \param[in] ptr_OutBuf file path and name to update.
//! \return
//! - 0 if ok, 1 else.

static int __SDSA_Parameters_WriteBinFile(TLV_TREE_NODE pTree, char * ptr_OutBuf)
{
	unsigned char * ac_l_pucBuffer = NULL;
	unsigned int  result = 0;
	int           i_l_Size = 0;
	S_FS_FILE     *ptr_file;

	
	// If the TlvTree that contains the parameters to save is null, suppress the saved file
	if(pTree == 0)
		goto SuppressFile;

	// Input parameters checking
	if (strlen(ptr_OutBuf) == 0)
	{
		return 1;
	}
	
	// Check size
	i_l_Size = TlvTree_GetSerializationSize(pTree, TLV_TREE_SERIALIZER_DEFAULT);

	if (i_l_Size>C_PUC_MAX_BUFFER_SIZE) // If file size greater than max size
	{
		GTL_Traces_TraceDebug ("__SDSA_Parameters_WriteBinFile : Parameter node size too important");
		result = 1;
	}
	else
	{
		ac_l_pucBuffer = (unsigned char *) umalloc(i_l_Size + 10);
		i_l_Size = TlvTree_Serialize( pTree, TLV_TREE_SERIALIZER_DEFAULT, ac_l_pucBuffer, i_l_Size + 10);

		// The buffer is saved in a file
		if ((i_l_Size < 0) || (i_l_Size > C_PUC_MAX_BUFFER_SIZE)) // If serialization pb
		{
			GTL_Traces_TraceDebug ("__SDSA_Parameters_WriteBinFile : Parameter node serialisation pb");
			result = 1;
		}
	}

SuppressFile:
	if (result == 0)	// If ok
	{
		unsigned int Mode,rc;
		int ret;

		ret = __SDSA_Parameters_CreateDisk();
		if (ret == FS_OK)
		{
			ret = FS_exist (ptr_OutBuf);

			if (ret == FS_OK)
			{
				GTL_Traces_TraceDebug ("__SDSA_Parameters_WriteBinFile : FILE EXIST");
				// The former file is suppressed. 
				ret = FS_unlink (ptr_OutBuf);

				// File is suppressed, terminate
				if(pTree == 0)
					return(result);
			}
			else
			{
				// File does not exist, terminate
				if(pTree == 0)
					return(result);
			}
		}

		Mode = FS_WRTMOD;
		rc = FS_mount(ptr_OutBuf, &Mode);
		if (rc != FS_OK)
		{
			GTL_Traces_TraceDebug ("__SDSA_Parameters_WriteBinFile : PB Mount COM File param");
			result = 1;
		} 

		ptr_file = FS_open (ptr_OutBuf, "a");
		if (ptr_file == NULL)
		{
			result = 1;
			GTL_Traces_TraceDebug ("__SDSA_Parameters_WriteBinFile : Error create file");
		}
	}

	if (result == 0)	// If ok
	{
		FS_write (ac_l_pucBuffer, 1, i_l_Size, ptr_file);
		FS_close(ptr_file);	// Close file
	}

	if (ac_l_pucBuffer != 0)
		ufree(ac_l_pucBuffer);
	return (result);
}



//! \brief This function reads a file of parameters (XML format) and extract tags and value to build a TLVTree. 
//! \param[in] pnode to store tags informations.
//! \param[in] pc_x_DirFile file path of xml text file to read.
//! \param[in] pc_x_fileName file name of xml text file to read.
//! \return
//! 0 if ok 1 else.

static int __SDSA_Parameters_ReadParamFile(TLV_TREE_NODE * p_node, char *pc_x_DirFile, unsigned int i_x_ParamFileType)
{
	int  result = 0;
	unsigned char * ac_l_pucBuffer = NULL;
	unsigned int Mode,rc;
	S_FS_FILE * ptr_file;

	// Read data from parameters file
	Mode = FS_READMOD;
	rc= FS_mount (pc_x_DirFile,&Mode);
	if (rc != FS_OK)
	{
		GTL_Traces_TraceDebug ("__SDSA_Parameters_ReadParamFile : PB Mount COM File");
	}
	ptr_file = FS_open(pc_x_DirFile, "r");

	if (ptr_file != NULL)
	{
		int s;
		unsigned long ulFileLength;

		ulFileLength = FS_length (ptr_file);
		
		if (ulFileLength>C_PUC_MAX_BUFFER_SIZE) // If file size greater than max size
		{
			GTL_Traces_TraceDebug ("__SDSA_Parameters_ReadParamFile : Parameter file size too important !!!");
			result = 1;
		}
		else
		{
			ac_l_pucBuffer = (unsigned char *) umalloc(ulFileLength+10);
			FS_read (ac_l_pucBuffer, 1, ulFileLength+10, ptr_file);
			s = TlvTree_Unserialize(p_node, i_x_ParamFileType, ac_l_pucBuffer, ulFileLength+10);
			ufree(ac_l_pucBuffer);

			if (s != 0)
			{
				// Reset of this node, a problem occured
				p_node = 0;
				result = 1;
			}
		}
		FS_close(ptr_file);
	}
	else // Pb on FS_open()
	{
		result = 1;
	}

	return (result);
}



//! \brief This function give disk label used to store parameters. 
//! \param[in/out] Disk name to update.

static void __SDSA_Parameters_Get_Disk_Name(char* ptDiskName)
{
	sprintf(gs_Label_Disk_Name,"%s%02x", LABEL_DISK, 0);
	memcpy(ptDiskName, gs_Label_Disk_Name, sizeof(gs_Label_Disk_Name));
}



//! \brief This function create disk to store parameters. 
//! \return
//! FS_OK if disk created, other else.

static int __SDSA_Parameters_CreateDisk (void)
{
	int               Retour;
	unsigned long     DiskSize;
	S_FS_PARAM_CREATE ParamCreat;
	char              FilePath_L[33];

	ParamCreat.Mode         = FS_WRITEONCE;
	ParamCreat.IdentZone    = FS_WO_ZONE_DATA;

	memclr(gs_Label_Disk_Name,sizeof(gs_Label_Disk_Name));
	sprintf(gs_Label_Disk_Name,"%s%02x", LABEL_DISK, 0);

	strcpy(ParamCreat.Label, gs_Label_Disk_Name);
	ParamCreat.AccessMode   = FS_WRTMOD;
	ParamCreat.NbFichierMax = 20;
	DiskSize              = DISK_SIZE;

	sprintf(FilePath_L,"/%s",gs_Label_Disk_Name);
	Retour = FS_mount (FilePath_L,&ParamCreat.Mode);
	if (Retour != FS_OK)
	{
		Retour=FS_dskcreate(&ParamCreat,&DiskSize);
	}
	return (Retour);
}



//! \brief This function check if tag is already in destination TLVTree.
//! If tag is already present => no action or delete it 
//! \param[in] pTree TLVTree with parameters set 
//! \param[in] ulTag tag to check in structure
//! \param[in] nAction, C_PARAMS_NO_ACTION (no ation) or C_PARAMS_DELETE (suppress it)
//! \return 1 if Tag is already present, 0 else

static int __SDSA_Parameters_IsTagAlreadyInTLVTree(TLV_TREE_NODE pTree, unsigned long ulTag, unsigned int nAction)
{
	int	nIndex, nFound;
	TLV_TREE_NODE pNode;

	if ((pTree == NULL) || (ulTag == 0))
		return (0); // A problem occurs, input parameters are empty ! Nothing could be made

	nIndex = 0;
	nFound = 0;

	pNode = TlvTree_Find(pTree, (unsigned int) ulTag, nIndex++);
	do{
		if (pNode) // If something founded
		{
			nFound = 1;
			if (nAction == C_PARAMS_NO_ACTION)	// If no action is asked on each tag found
				break;	// We can stop treatment

			if (nAction == C_PARAMS_DELETE)		// If a delete action has been asked
				TlvTree_Release(pNode);
			
			pNode = TlvTree_Find(pTree, (unsigned int) ulTag, nIndex++);
		}
	}while (pNode != 0);

	return (nFound);
}



//! \brief This function copies all parameters under hSrcTree TLVTree in the hDestTree TLVTree 
//! \param[in] hSrcTree TLVTree node with parameters to copies.
//! \param[in] hDescTree TLVTree node with parameters to update.
//! \param[in] nParametersType allows to specify if parameters to add are prioritary, exclusive or not. 
//! return 0 if copied has been correctly executed, 1 else.

static int __SDSA_Parameters_CopyParameters (const TLV_TREE_NODE hDestTree, const TLV_TREE_NODE hSrcTree, int nParametersType)
{
	unsigned int nResult = 0;
	int nTLVResult;
	TLV_TREE_NODE pResearch;
	int nCopyCanBeMade;
	unsigned int nTag;
	TLV_TREE_NODE pTmpNode;
	
	if ((hDestTree == NULL) || (hSrcTree == NULL))
	{
		nResult = 1;
		return (nResult);
	}

	// Init local data
	pTmpNode = NULL;
	
	// For each tag found in Src TLVTree
	pResearch = TlvTree_GetFirstChild(hSrcTree);
	
	do
	{
		if (pResearch != 0)
		{
			// Node has been found
			nTag = TlvTree_GetTag(pResearch); // What tag is managed
			
			switch (nParametersType)
			{
			case C_PRIORITY_PARAMS:
				__SDSA_Parameters_IsTagAlreadyInTLVTree(hDestTree, nTag, C_PARAMS_DELETE); // If tag is already present => delete it
				nCopyCanBeMade = 1; // Copy can be made ...
				break;
				
			case C_UNPRIORITY_PARAMS:
				if (__SDSA_Parameters_IsTagAlreadyInTLVTree(hDestTree, nTag, C_PARAMS_NO_ACTION) != 0) // If tag is already present => we keep it
					nCopyCanBeMade = 0; // Copy cannot be made ...
				else
					nCopyCanBeMade = 1; // Tag isn't already present, we can copy it 
				break;
				
			case C_MULTI_PARAMS: // No action, just a copy is necessary
			default:
				nCopyCanBeMade = 1; // Copy can be made ...
				break;
			}

			if (nCopyCanBeMade) // If copy can be made (no problem of multi same tags)
			{
				// Copy it in destination pNode
				pTmpNode = TlvTree_Copy(pResearch);
				nTLVResult = TlvTree_Graft(hDestTree, pTmpNode);
			}
			else
			{
				nTLVResult = TLV_TREE_OK; // To allow to continue
			}

			if (nTLVResult == TLV_TREE_OK)
				pResearch = TlvTree_GetNext(pResearch);
			else
			{
				nResult = 1;// A problem occurs
				pResearch = NULL; // To stop process
				GTL_Traces_TraceDebug ("__SDSA_Parameters_CopyParameters : Unable to add tag in dest TLVTree");
			}
		} // End (if pResearch != 0)
	}while (pResearch != 0);
	
	return (nResult);
}



//! \brief This function add AID parameters in global gs_Parameter_AID[] structure.
//! \param[in] pnode parameters node for the kernel.
//! \return number of AID found in input parameters.

static int __SDSA_Parameters_SetAIDParametersInFinalStruct(TLV_TREE_NODE pnode)
{
	unsigned int nNbAID;
	int	nIndex;
	TLV_TREE_NODE pChild;
	TLV_TREE_NODE pAIDParams, pResearch;			// Node for AID parameters.
	

	// Found main AID nodes in TLVTree given in parameters
	nNbAID = 0;
	nIndex = 0;

	// Look for the main AID tag in the pTree TLVTree
	pAIDParams = TlvTree_Find(pnode, C_PARAM_AID_TAG, nIndex);

	if (pAIDParams == 0) // No AID information found
		return(nNbAID);
		
	// For each AID found in parameters
	pChild = TlvTree_GetFirstChild(pAIDParams);
	
	// Loop on each parameters set
	while ((pChild != 0) && (nNbAID < C_NUMBER_AID_MAX)) // Loop on each child
	{
		// Create a tree containing the AID data
		gs_Parameter_AID[nNbAID].pTreeAID = TlvTree_New(C_TAG_MAIN);
		
		pResearch = TlvTree_Find (pChild, TAG_EMV_AID_TERMINAL, 0); // If AID informations have been founded
		
		if (pResearch != 0) // If AID informations have been founded
		{
			if (__SDSA_Parameters_CopyParameters(gs_Parameter_AID[nNbAID].pTreeAID, pChild, C_MULTI_PARAMS) != 0)
			{
				GTL_Traces_TraceDebug ("__SDSA_Parameters_SetAIDParametersInFinalStruct : Unable to add tag in AID parameters");
			}
			else
			{
				// Put index reference in AID informations structure
				gs_Parameter_AID[nNbAID].nAIDLength = TlvTree_GetLength(pResearch);
				memcpy (gs_Parameter_AID[nNbAID].ucAID, TlvTree_GetData(pResearch), TlvTree_GetLength(pResearch));
				
				// Get the AID Proprietary identifier (if present)
				//pResearch = TlvTree_Find (pChild, TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER, 0); // If AID informations have been founded
				
				/*if (pResearch != NULL)
				{
					gs_Parameter_AID[nNbAID].bAidProprietaryIdPresent = TRUE;
					memcpy (gs_Parameter_AID[nNbAID].ucAidProprietaryId, TlvTree_GetData(pResearch), TlvTree_GetLength(pResearch));
				}
				else
				{
					gs_Parameter_AID[nNbAID].bAidProprietaryIdPresent = FALSE;
					memset (gs_Parameter_AID[nNbAID].ucAidProprietaryId, 0x00, sizeof(gs_Parameter_AID[nNbAID].ucAidProprietaryId));
				}*/
				
				// Store the index
				gs_Parameter_AID[nNbAID].ucAIDIndex = nNbAID;
				
				// Delete AID informations from destination TLVTree
				//nIndex = 0;
				pResearch = TlvTree_Find(gs_Parameter_AID[nNbAID].pTreeAID, TAG_EMV_AID_TERMINAL, 0);
				if (pResearch)
					TlvTree_Release(pResearch);
			}
		}
		
		nNbAID ++; // Increase the number of supported AID
		pChild = TlvTree_GetNext(pChild); // Next AID (next child)
	} // End loop on each AID parameters

	return (nNbAID);
}

//! \brief This function add Krevok parameters in global gs_Parameter_AID[] structure.
//! \param[in] nNbAID Number of available AID.
//! \param[in] pnode parameters node for the kernel.

static void __SDSA_Parameters_SetKRevokParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID)
{
	unsigned int nIndex, nIndexAID;
	TLV_TREE_NODE pKRevokParams;		// Node for KRevok parameters.
	
	nIndex = 0;
	nIndexAID = 0;

	// Found global parameters
	pKRevokParams = TlvTree_Find (pnode, C_PARAM_KREVOK_TAG, nIndex);
	
	// Set global parameters in AID TLVTree
	if (pKRevokParams != NULL) // If KRevok parameters founded
	{
		// Loop on each AID
		for (nIndexAID = 0; nIndexAID<(unsigned int)nNbAID; nIndexAID++)
		{
			if (__SDSA_Parameters_CopyParameters(gs_Parameter_AID[nIndex].pTreeAID, pKRevokParams, C_MULTI_PARAMS) != 0)
			{
				GTL_Traces_TraceDebug ("__SDSA_Parameters_SetKRevokParametersInFinalStruct: Pb copy Krevok parameters");
			}
		}
	}
}


//! \brief This function add kernel parameters in global gs_Parameter_AID[] structure.
//! \param[in] nNbAID Number of available AID.
//! \param[in] pnode parameters node for the kernel.

static void __SDSA_Parameters_SetKernelParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID)
{
	unsigned char * pucTagPtr;
	int nTagLentgth;
	unsigned int nIndex, nIndexAID;
	TLV_TREE_NODE pKernelParams;		// Node for global parameters.
	TLV_TREE_NODE pResearch;			// Node for research.
	TLV_TREE_NODE pNode;

	nIndex = 0;
	nIndexAID = 0;

	// Found global parameters
	pKernelParams = TlvTree_Find (pnode, C_PARAM_KERNEL_TAG, nIndex);
	
	// Set global parameters in AID TLVTree
	if (pKernelParams != NULL) // If Kernel parameters founded
	{
		// Loop on each AID
		for (nIndexAID = 0; nIndexAID<(unsigned int)nNbAID; nIndexAID++)
		{
			// Found kernel parameters to use
			pResearch = TlvTree_Find(gs_Parameter_AID[nIndexAID].pTreeAID, TAG_EP_KERNEL_TO_USE, 0);
			
			if (pResearch) // If kernel to use has been found
			{
				// Store kernel parameters.
				if (SDSA_Parameters_AddParametersInNode(gs_Parameter_AID[nIndexAID].pTreeAID, pnode, C_PARAM_KERNEL_TAG, TAG_EP_KERNEL_TO_USE, TlvTree_GetLength(pResearch), TlvTree_GetData(pResearch), C_UNPRIORITY_PARAMS) != 0)
				{
					GTL_Traces_TraceDebug ("__SDSA_Parameters_SetKernelParametersInFinalStruct: Pb kernel parameters copy");
				}
			}
		}

		nIndex = 0;
		pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SDSA_GENERIC_MONEY_EXTENDED, nIndex++);

		if (pNode) // If something founded
		{
			nNbMoneyExtended = 0; // Reset for update it
			if (ptr_money_extended)
				ufree(ptr_money_extended);
			ptr_money_extended = NULL;
		}
		
		do{
			if (pNode) // If something founded
			{
				// Add informations in ptr_money_extended array
				nNbMoneyExtended++;

				pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SDSA_GENERIC_MONEY_EXTENDED, nIndex++);
			}
		}while (pNode != 0);
		
		nIndex = 0;
		if (nNbMoneyExtended)
		{
			ptr_money_extended = umalloc(nNbMoneyExtended * sizeof(S_MONEY_EXTENDED));
			pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SDSA_GENERIC_MONEY_EXTENDED, nIndex++);
	
			do{
				if (pNode) // If something founded
				{
					nTagLentgth = TlvTree_GetLength(pNode);
					pucTagPtr = TlvTree_GetData(pNode);
				}
				
				if (pNode) // If something founded
				{
					memset(&ptr_money_extended[nIndex-1], 0, sizeof(S_MONEY_EXTENDED)); 		// Reset structure
					if (nTagLentgth >= 10)														// If something founded
					{
						memcpy(ptr_money_extended[nIndex-1].currency.nom, pucTagPtr, 3); 		// Name copy, 3 bytes
						memcpy(ptr_money_extended[nIndex-1].currency.code, pucTagPtr + 3, 3); 	// Code copy, 3 bytes
						ptr_money_extended[nIndex-1].currency.posdec = pucTagPtr[6] - 0x30;		// Decimal position in the amount  
		
						ptr_money_extended[nIndex-1].infos.cents_separator = pucTagPtr[7];
						ptr_money_extended[nIndex-1].infos.thousands_separator = pucTagPtr[8];
						ptr_money_extended[nIndex-1].infos.currency_position = pucTagPtr[9] - 0x30;
					}
					pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SDSA_GENERIC_MONEY_EXTENDED, nIndex++);
				}
			}while (pNode != 0);
		}
	}
}


//! \brief This function give Extended money structure initialized with parameters.
//! \param[in/out] n_x_NbMoney Number of money managed.
//! \param[in/out] ps_x_Money pnode parameters node for the kernel.

void SDSA_Parameters_GetMoneyExtended(int * n_x_NbMoney, S_MONEY_EXTENDED ** ps_x_Money)
{
	*n_x_NbMoney = nNbMoneyExtended;
	*ps_x_Money  = ptr_money_extended;
}


//! \brief This function add global parameters in global gs_Parameter_AID[] structure.
//! \param[in] pnode parameters node for the kernel.
//! \param[in] nNbAID.

static void __SDSA_Parameters_SetGlobalParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID)
{
	TLV_TREE_NODE pGlobalParams;		// Node for global parameters.
	unsigned int nIndex;
	
	nIndex = 0;
	
	// Found global parameters
	nIndex = 0;
	pGlobalParams = TlvTree_Find(pnode, C_PARAM_GLOBAL_TAG, nIndex);
	
	// Set global parameters in AID TLVTree
	if (pGlobalParams) // If global parameters founded
	{
		// Loop on each AID
		for (nIndex = 0; nIndex<(unsigned int)nNbAID; nIndex++)
		{
			// Store global parameters.
			if (SDSA_Parameters_AddParametersInNode(gs_Parameter_AID[nIndex].pTreeAID, pnode, C_PARAM_GLOBAL_TAG, 0, 0, NULL, C_UNPRIORITY_PARAMS) != 0)
			{
				GTL_Traces_TraceDebug ("__SDSA_Parameters_SetGlobalParametersInFinalStruct : SDSA_Parameters_AddParametersInNode : No global parameters found");
			}
		}
	}
}



//! \brief This function add global parameters in global gs_Parameter_AID[] structure.
//! \param[in] nNbAID Number of parametered AID.
//! \param[in] pnode parameters node for the kernel.
//! \return KERNEL_STATUS_OK if no problem, other else.

static int __SDSA_Parameters_EncodeTLVTreeInShareBuf(int nNbAID)
{
	int nResult = 0;
	int nIndex;
	T_SHARED_DATA_STRUCT* pAidInfo;

	// Loop on each AID set of parameter to manage
	for (nIndex=0; nIndex<nNbAID; nIndex++)
	{
		pAidInfo = GTL_SharedExchange_Init(C_SHARE_BUFFER_SIZE, C_BUFFER_SHARED);
		if (pAidInfo == NULL)
		{
			nResult = 1; // Error
			goto End;
		}
		
		gs_Parameter_AID[nIndex].pSharedAIDParam = pAidInfo; 

		if (__SDSA_Parameters_AddTLVTreeInShareBuf(nIndex) != 0)
			nResult = 1; // Error
	} // End Loop on each AID set of parameter to manage
	
End :
	return (nResult);
}



//! \brief This function add parameters in global g_Parameter_AID[] structure.
//! \param[in] nNumAID parameter set number.
//! \return
//!		- 0 if no problem
//!		- 1 else.

static int __SDSA_Parameters_AddTLVTreeInShareBuf (int nNumAID)
{
	int nResult = 0;
	int nResultSharedExchange;
	TLV_TREE_NODE hRootNode, hNode; 
	T_SHARED_DATA_STRUCT* pAidInfo;

	hRootNode = gs_Parameter_AID[nNumAID].pTreeAID;
	pAidInfo = gs_Parameter_AID[nNumAID].pSharedAIDParam; 
	hNode = hRootNode;
			
	// Loop on each tag to add in Share exchange buffer
	do{
		hNode = TlvTree_Iterate(hNode, hRootNode );
		
		if (hNode != 0) // Tag may be added in Shared Buffer
		{
			// Get informations from tag found					
			
			nResultSharedExchange = GTL_SharedExchange_AddTag (pAidInfo, TlvTree_GetTag(hNode), TlvTree_GetLength(hNode), TlvTree_GetData(hNode));
			switch (nResultSharedExchange)
			{
				case STATUS_SHARED_EXCHANGE_OK:
					break;
				case STATUS_SHARED_EXCHANGE_NOT_ENOUGH_SPACE: 
					GTL_Traces_TraceDebug ("__SDSA_Parameters_EncodeTLVTreeInShareBuf() not enought space");
					nResult = 1; // Error
					break;
				case STATUS_SHARED_EXCHANGE_ERROR:
				default:
					GTL_Traces_TraceDebug ("__SDSA_Parameters_EncodeTLVTreeInShareBuf() exchange error");
					nResult = 1; // Error
					break;
			}
		}
	}while((hNode != 0) && (nResultSharedExchange == STATUS_SHARED_EXCHANGE_OK)); // End loop on tag to add in Share exchange buffer

	return (nResult);
}



//! \brief This function clear TLVTree used to store parameters. 

void SDSA_Parameters_InitParameters(TLV_TREE_NODE * pTree)
{
	TlvTree_ReleaseEx(pTree);
}



//! \brief This function set TLVTree parameters in a save file. 

int SDSA_Parameters_SaveParam (TLV_TREE_NODE pTree)
{
	// Local variables déclaration
	// Function result
	int nResult;
	char ac_l_FilePath_L[80];
	char LabelDiskName[DISK_NAME_SIZE];

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__SDSA_Parameters_Get_Disk_Name(LabelDiskName);

	// Update PARAM.PAR serial binary TLVTree format file
	sprintf(ac_l_FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM_SAV);
	nResult = __SDSA_Parameters_WriteBinFile(pTree, ac_l_FilePath_L);

	return(nResult);
}



//! \brief This function update TLVTree with parameters read in a save file. 

int SDSA_Parameters_RestoreParam (TLV_TREE_NODE * pTree)
{
	char FilePath_L[80];
	int ret = FS_OK;
	char LabelDiskName[DISK_NAME_SIZE];
	int nResult;
	unsigned int Mode,rc;

	memclr(FilePath_L,sizeof(FilePath_L));

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__SDSA_Parameters_Get_Disk_Name(LabelDiskName);

	Mode = FS_WRTMOD;
	sprintf(FilePath_L, "/%s", LabelDiskName);
	rc = FS_mount(FilePath_L, &Mode);
	if (rc != FS_OK)
	{
		upload_diagnostic_txt((unsigned char *)"PB Mount COM File param\n");
		GTL_Traces_TraceDebug("SDSA_Parameters_RestoreParam : PB Mount COM File param");
		nResult = 1;
	}
	else
	{
		
		sprintf(FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM_SAV);
		// Set path in input buffer for BuildParameters() call
		ret = FS_exist (FilePath_L);
		
		if (ret == FS_OK)
		{
			GTL_Traces_TraceDebug("SDSA_Parameters_RestoreParam : Load %s file", C_FILE_PARAM_SAV);
			// Load parameter file in the terminal
			nResult = __SDSA_Parameters_FileRead (pTree, FilePath_L, C_FILE_PARAM_SAV);
		}
		else
		{
			GTL_Traces_TraceDebug("SDSA_Parameters_RestoreParam : %s file not existing", C_FILE_PARAM_SAV);
			nResult = 1;
		}
	}
	
	return (nResult);
}



//! \brief This function compute a CRC allowing to check parameters loaded.
//! The CRC is computed on a list of a fix list of tags.

int SDSA_Parameters_Compute_Config_CRC(TLV_TREE_NODE * pTree, int * nCRCLength, unsigned char ** pSha)
{
	unsigned char *pucBuffer;
	int nSerializedSize = 0;
	int nStatus, nReturn;

	// Initialisation
	nReturn = FALSE;
	*nCRCLength = 0;

	if( *pTree != NULL )
	{
		nSerializedSize = TlvTree_GetSerializationSize( *pTree, TLV_TREE_SERIALIZER_DEFAULT );
		if( nSerializedSize > 0 )
		{
			pucBuffer = (unsigned char*)umalloc( nSerializedSize );
			if( pucBuffer != NULL )
			{
				// Add the serialized tree...
				nStatus = TlvTree_Serialize( *pTree, TLV_TREE_SERIALIZER_DEFAULT, pucBuffer, nSerializedSize );

				if( nStatus > 0 )
				{

					*pSha = (unsigned char*)GTL_SHA_Sha1Compute ((unsigned char*)pucBuffer, nSerializedSize);
					*nCRCLength = 20;
					nReturn = TRUE;
				}

				ufree( pucBuffer );
			}
			else
			{
				GTL_Traces_TraceDebug ("SDSA_Parameters_Compute_Config_CRC : umalloc Error");
			}
		}
		else
		{
			GTL_Traces_TraceDebug ("SDSA_Parameters_Compute_Config_CRC : TlvTree_GetSerializationSize Error");
		}
	}
	else
	{
		GTL_Traces_TraceDebug ("SDSA_Parameters_Compute_Config_CRC : input TlvTree is null");
	}

	return nReturn;
}


//! \brief This function select TLVTree of parameters in relationchip with Index AID.

int SDSA_Parameters_GiveAIDNumber(void)
{
	return (gs_nNbParameterSet);
}



//! \brief This function Send AID of parameters store.

unsigned char * SDSA_Parameters_GiveAID(unsigned int n_x_AIDIndex, int * pAIDLength)
{
	unsigned char * pAID = NULL;
	
	*pAIDLength = 0;
	
	if (n_x_AIDIndex >= (unsigned int)gs_nNbParameterSet) // If index greater than number of parameter set
	{
		GTL_Traces_TraceDebug("SDSA_Parameters_GiveAID : Bad index");
		goto End;
	}
	
	pAID = gs_Parameter_AID[n_x_AIDIndex].ucAID;
	*pAIDLength	= gs_Parameter_AID[n_x_AIDIndex].nAIDLength;
		
End:
	return (pAID);
}



//! \brief This function select TLVTree of parameters in relationchip with Index AID.

TLV_TREE_NODE SDSA_Parameters_GiveAIDTLVTtree(unsigned int n_x_AIDIndex)
{
	if (n_x_AIDIndex >= (unsigned int)gs_nNbParameterSet) // If index greater than number of parameter set
	{
		GTL_Traces_TraceDebug("SDSA_Parameters_GiveAIDTLVTtree : Bad index");
		return (NULL);
	}
	
	return (gs_Parameter_AID[n_x_AIDIndex].pTreeAID);
}



//! \brief This function select shared buffer of parameters to use with Index AID.

T_SHARED_DATA_STRUCT * SDSA_Parameters_GiveAIDShareBuffer(unsigned int n_x_AIDIndex)
{
	if (n_x_AIDIndex >= (unsigned int)gs_nNbParameterSet) // If index greater than number of parameter set
	{
		GTL_Traces_TraceDebug("SDSA_Parameters_GiveAIDShareBuffer : Bad index");
		return (NULL);
	}
	
	return (gs_Parameter_AID[n_x_AIDIndex].pSharedAIDParam);
}



//! \brief This function found subset parameters and select parameters set to store in MainNode.

int SDSA_Parameters_AddParametersInNode(TLV_TREE_NODE pMainNode, TLV_TREE_NODE pParameterNode, unsigned long ulSubsetTag, unsigned long ulTag, int nTagLength, unsigned char * ucTagValue, int nParametersType)
{
	int nResult = 0; // No problem = Default result
	//  Find main tag in input parameters node
	int	nIndex = 0;
	int nFound = 0;
	TLV_TREE_NODE pNode, pChild, pResearch;

	if ((pMainNode == NULL) || (pParameterNode == NULL) || (ulSubsetTag == 0))
	{
		GTL_Traces_TraceDebug ("SDSA_Parameters_AddParametersInNode : Invalid input parameter");
		nResult = 1; // A problem occurs, input parameters are empty !
		goto End;
	}

	// Look for the tag in the pTree TLVTree
	pNode = TlvTree_Find(pParameterNode, ulSubsetTag, 0);

	// If a tag was found
	if (pNode != NULL)
	{
		pChild = TlvTree_GetFirstChild(pNode);
		
		// Loop on each parameters set
		while((pChild != 0) && (!nFound))
		{
			nIndex = 0;
			
			if (ulTag == 0) // If no tag is specified, first set of parameters will be taken.
			{
				nFound = TRUE;
			}
			else // A tag is specified : we have to look for the tag with appropriate value.
			{
				do{
					pResearch = TlvTree_Find(pChild, ulTag, nIndex++);
					
					if (pResearch != 0)
					{
						// Check if tag found is same as we want 					
						if (((unsigned long)TlvTree_GetTag(pResearch) == ulTag) && (TlvTree_GetLength(pResearch) == (unsigned long)nTagLength) && (memcmp(TlvTree_GetData(pResearch), ucTagValue, nTagLength) == 0))
							nFound = TRUE;					 
					}
				}while ((pResearch != NULL) && (!nFound));
			}
			
			if (!nFound)
			{
				pChild = TlvTree_GetNext(pChild); // Next Child
			}
		}
		
		if (nFound) // If specific tag has been found, all parameters in pChild set may be copied in pMainNode main Node parameter set
		{
			if (__SDSA_Parameters_CopyParameters(pMainNode, pChild, nParametersType) != 0)
			{
				GTL_Traces_TraceDebug ("SDSA_Parameters_AddParametersInNode : __SDSA_Parameters_CopyParameters error");
				nResult = 1;// A problem occurs
				goto End;
			}
		}
	}
End:
	return (nResult);
}



//! \brief This function organises TLVTree nodes with parameters used for AID selection.

void SDSA_Parameters_BuildAIDNodes(TLV_TREE_NODE pnode)
{
	int nIndex;

	// Init structures
	for (nIndex = 0; nIndex < gs_nNbParameterSet; nIndex++)
	{
		TlvTree_ReleaseEx (&(gs_Parameter_AID[nIndex].pTreeAID));

		if (gs_Parameter_AID[nIndex].pSharedAIDParam != NULL)
			GTL_SharedExchange_DestroyShare (gs_Parameter_AID[nIndex].pSharedAIDParam);
	}
	
	// Init all the structure
	memset(gs_Parameter_AID[0].ucAID, 0, sizeof(T_PARAMETER_AID) * C_NUMBER_AID_MAX);
	gs_nNbParameterSet = 0;

	// Add AID parameters in final global Structure
	gs_nNbParameterSet = __SDSA_Parameters_SetAIDParametersInFinalStruct(pnode);

	if (gs_nNbParameterSet == 0)
	{
		GTL_Traces_TraceDebug("SDSA_Parameters_BuildAIDNodes : No avaibale AID");
		return; // No AID found ...
	}

	// Here, gs_Parameter_AID[] is initialised with AID parameters, AID value (and length) and AID index    

	// Add kernel parameters in final global Structure
	__SDSA_Parameters_SetKernelParametersInFinalStruct(pnode, gs_nNbParameterSet);

	// Add global parameters in final global Structure
	__SDSA_Parameters_SetGlobalParametersInFinalStruct(pnode, gs_nNbParameterSet);

	// Add KRevok parameters in final global Structure
	__SDSA_Parameters_SetKRevokParametersInFinalStruct(pnode, gs_nNbParameterSet);

	// Put set of parameters in ShareTLV (BERTLV) format (for kernel use when AID will be used).
	if (__SDSA_Parameters_EncodeTLVTreeInShareBuf(gs_nNbParameterSet) != 0)
		GTL_Traces_TraceDebug ("SDSA_Parameters_BuildAIDNodes : __SDSA_Parameters_EncodeTLVTreeInShareBuf failed");
}



//! \brief Get the CA Key data according to the RID and the CA Key index.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[in] ucCaKeyIndex CA Public Key index to find.
//! \param[in] pRid RID to be used to find the CA Public Key.
//! \param[out] pOutputDataStruct Shared buffer filled with the CA Public Key data.
//! \return
//!		- \ref TRUE if correctly performed (data found and \a pOutputDataStruct filled).
//!		- \ref FALSE if an error occured.

int SDSA_Parameters_GetCaKeyData (TLV_TREE_NODE ParameterTlvTree, const unsigned char ucCaKeyIndex, const unsigned char * pRid, T_SHARED_DATA_STRUCT * pOutputDataStruct)
{
	TLV_TREE_NODE pCaKeysParams;		// Node for CAKeys.
	TLV_TREE_NODE pChild;				// CA Key content
	TLV_TREE_NODE pResearch;			// Working Node
	unsigned char * pValue;
	int nResult = FALSE;
	int bFound = FALSE;
	int cr;
	
	pCaKeysParams = TlvTree_Find(ParameterTlvTree, C_PARAM_CAKEY_TAG, 0);
	
	if (pCaKeysParams != NULL)
	{
		// For each CA Key found in parameters
		pChild = TlvTree_GetFirstChild(pCaKeysParams);
		
		while (pChild != NULL)
		{
			pResearch = TlvTree_Find(pChild, TAG_EMV_AID_TERMINAL, 0); // If AID informations have been founded
			
			if (pResearch != NULL)
			{
				if (memcmp(pRid, TlvTree_GetData(pResearch), 5) == 0)
				{
					// Same RID, check if CA Key index is identical
					pResearch = TlvTree_Find(pChild, TAG_EMV_CA_PUBLIC_KEY_INDEX_TERM, 0); // If AID informations have been founded
					
					if (pResearch != NULL)
					{
						pValue = TlvTree_GetData(pResearch);
						if (ucCaKeyIndex == pValue[0])
						{
							// This is the correct CA Key, copy the necessary data in pOutputDataStruct (modulus and exponent)
							bFound = TRUE;							
							
							pResearch = TlvTree_Find(pChild, TAG_EMV_INT_CAPK_MODULUS, 0); // If AID informations have been founded
							if (pResearch != NULL)
							{
								cr = GTL_SharedExchange_AddTag(pOutputDataStruct, TAG_EMV_INT_CAPK_MODULUS, TlvTree_GetLength(pResearch), TlvTree_GetData(pResearch));
								if (cr != STATUS_SHARED_EXCHANGE_OK)
								{
									GTL_Traces_TraceDebug("SDSA_Parameters_GetCaKeyData An error occured when adding TAG_EMV_INT_CAPK_MODULUS in the shared structure (cr = %02x)", cr);
									GTL_SharedExchange_ClearEx(pOutputDataStruct, FALSE);
									goto End;
								}
							}
							
							pResearch = TlvTree_Find(pChild, TAG_EMV_INT_CAPK_EXPONENT, 0); // If AID informations have been founded
							if (pResearch != NULL)
							{
								cr = GTL_SharedExchange_AddTag(pOutputDataStruct, TAG_EMV_INT_CAPK_EXPONENT, TlvTree_GetLength(pResearch), TlvTree_GetData(pResearch));
								if (cr != STATUS_SHARED_EXCHANGE_OK)
								{
									GTL_Traces_TraceDebug("SDSA_Parameters_GetCaKeyData An error occured when adding TAG_EMV_INT_CAPK_EXPONENT in the shared structure (cr = %02x)", cr);
									GTL_SharedExchange_ClearEx(pOutputDataStruct, FALSE);
									goto End;
								}
							}
							
							nResult = TRUE;
							goto End;
						}
					}
				}
			}
			
			pChild = TlvTree_GetNext(pChild);
		}
	}
	
	if (!bFound)
	{
		GTL_Traces_TraceDebug("SDSA_Parameters_GetCaKeyData : CA Public Key is not found");
	}
End:
	return (nResult);
}



//! \brief Create the certificate supported list for each PayPass AID.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[in] usKernelId Kernel identifier to determine which AID structure shall be updated with the supported certificate list.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

int SDSA_Parameters_CreateSupportedCertificateListForKernel (TLV_TREE_NODE ParameterTlvTree, unsigned short usKernelId)
{
	unsigned char ucSupportedCaList[64];
	unsigned long ulSupportedListLength;
	unsigned char * pAid;
	int nResult = TRUE;
	TLV_TREE_NODE pAidParams; // AID structure content
	TLV_TREE_NODE pChild; // CA Key content
	TLV_TREE_NODE pResearch; // Working Node
	unsigned short usCurrentKernel;
	unsigned char * pKernelToUse;

	pAidParams = TlvTree_Find(ParameterTlvTree, C_PARAM_AID_TAG, 0);

	if (pAidParams != NULL)
	{
		pChild = TlvTree_GetFirstChild(pAidParams);

		while (pChild != NULL)
		{
			// Init kernel identifier
			usCurrentKernel = DEFAULT_EP_KERNEL_UNKNOWN;

			// Search the kernel to use for this AID
			pResearch = TlvTree_Find(pChild, TAG_EP_KERNEL_TO_USE, 0); // Get the kernel to use for this AID

			if (pResearch != NULL)
			{
				// Build the kernel to use for future use
				pKernelToUse = TlvTree_GetData(pResearch);
				usCurrentKernel = pKernelToUse[1] + (pKernelToUse[0] << 8);

				// If the AID kernel is the same as the requested one
				if (usCurrentKernel == usKernelId)
				{
					// Get the AID
					pResearch = TlvTree_Find(pChild, TAG_EMV_AID_TERMINAL, 0); // If AID informations have been founded
					
					if (pResearch != NULL)
					{
						// Save the AID pointer
						pAid = TlvTree_GetData(pResearch);

						// Init output data (supported certificate list)
						ulSupportedListLength = sizeof (ucSupportedCaList);
						memset (ucSupportedCaList, 0, ulSupportedListLength);

						// Get the certificate list for this AID
						SDSA_Parameters_GetSupportedCertificateList (ParameterTlvTree, ucSupportedCaList, &ulSupportedListLength, pAid);

						if (ulSupportedListLength > 0)
						{
							// Specific treatment for PayPass
							if(usKernelId == DEFAULT_EP_KERNEL_PAYPASS)
							{
								// Add the tag in the TLV Tree (for the current AID)
								if (TlvTree_AddChild (pChild, TAG_PAYPASS_INT_SUPPORTED_CAPK_INDEX_LIST, ucSupportedCaList, ulSupportedListLength) == NULL)
								{
									GTL_Traces_TraceDebug ("SDSA_Parameters_CreateSupportedCertificateListForKernel : An error occured when adding the supported certificate list to the AID structure");
									nResult = FALSE;
								}
							}
							else if (usKernelId == DEFAULT_EP_KERNEL_AMEX)
							{
								if (TlvTree_AddChild (pChild, TAG_EXPRESSPAY_INT_SUPPORTED_CAPK_INDEX_LIST, ucSupportedCaList, ulSupportedListLength) == NULL)
								{
									GTL_Traces_TraceDebug ("SDSA_Parameters_CreateSupportedCertificateListForKernel : An error occured when adding the supported certificate list to the Expresspay AID structure");
									nResult = FALSE;
								}
							}
							// else... No treatment for other kernels
						}
					}
				}
			}

			// Get the next AID structure
			pChild = TlvTree_GetNext(pChild);
		}
	}

	return (nResult);
}



//! \brief Get the CA Key data according to the RID and the CA Key index.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[out] pCertificateList List of supported certificate indexes.
//! \param[in,out] Input : The length of \a pCertificate. Output : length of the certificate list.
//! \param[in] pRid RID to be used to find the CA Public Key.
//! \param[out] pOutputDataStruct Shared buffer filled with the CA Public Key data.

void SDSA_Parameters_GetSupportedCertificateList (TLV_TREE_NODE ParameterTlvTree, unsigned char * pCertificateList, unsigned long * pCertificateListLength, const unsigned char * pRid)
{
	TLV_TREE_NODE pCaKeysParams;		// Node for CAKeys.
	TLV_TREE_NODE pChild;				// CA Key content
	TLV_TREE_NODE pResearch;			// Working Node
	unsigned char * pValue;
	unsigned long ulTempLength = 0;
	
	pCaKeysParams = TlvTree_Find(ParameterTlvTree, C_PARAM_CAKEY_TAG, 0);
	
	if (pCaKeysParams != NULL)
	{
		// For each CA Key found in parameters
		pChild = TlvTree_GetFirstChild(pCaKeysParams);
		
		while (pChild != NULL)
		{
			pResearch = TlvTree_Find(pChild, TAG_EMV_AID_TERMINAL, 0); // If AID informations have been founded
			
			if (pResearch != NULL)
			{
				if (memcmp(pRid, TlvTree_GetData(pResearch), 5) == 0)
				{
					// Same RID, check if CA Key index is identical
					pResearch = TlvTree_Find(pChild, TAG_EMV_CA_PUBLIC_KEY_INDEX_TERM, 0); // If AID informations have been founded
					
					if (pResearch != NULL)
					{
						pValue = TlvTree_GetData(pResearch);

						if (*pCertificateListLength > ulTempLength)
						{
							pCertificateList[ulTempLength] = pValue[0];
							ulTempLength ++; // One more supported CA
						}
					}
				}
			}
			
			pChild = TlvTree_GetNext(pChild);
		}
	}
	
	if (pCertificateListLength != NULL)
		*pCertificateListLength = ulTempLength;
}
