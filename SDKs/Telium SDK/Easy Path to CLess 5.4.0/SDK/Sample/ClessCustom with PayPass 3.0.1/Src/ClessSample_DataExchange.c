/**
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 */


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define DISK_NAME_SIZE					33			/*!< Size of disk name. */


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

TLV_TREE_NODE pTreeCurrentDataExchange = NULL;							/*!< Node from data exchange parameters. */
static char gs_DataExchange_Label_Disk_Name[DISK_NAME_SIZE];			/*!< To store the disk name. */
static int gDETSignalStatus;											// Indication that DEK Signal matched during DE testing


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __ClessSample_DataExchange_WriteBinFile (TLV_TREE_NODE hTree, char * ptr_OutBuf);
static void __ClessSample_DataExchange_Get_Disk_Name (char* ptDiskName);
static int __ClessSample_DataExchange_CreateDisk (void);
static int __ClessSample_DataExchange_FileRead(TLV_TREE_NODE * pTree, char *pc_x_DirFile, char *pc_x_fileName);
static int __ClessSample_DataExchange_ReadEvalTreeFile (TLV_TREE_NODE * p_node, char *pc_x_DirFile, unsigned int i_x_ParamFileType);
static int __ClessSample_DataExchange_Alignment (const unsigned char * pDEKValue, const unsigned char * pParamValue, unsigned long ulLengthDEK, unsigned long ulLengthParam);
static void __Xmls_Start (XMLs_PARSER hParser, const char* szName, XMLs_ATTRIBUTE* pAttributes, unsigned int nAttributesNumber);
static void __Xmls_Stop (XMLs_PARSER hXmlParser, const char* szName);
static void __Xmls_GetData (XMLs_PARSER hXmlParser, const char*  pcDataBuffer, unsigned int nLength);
static int __ClessSample_DataExchange_GetNext (T_SHARED_DATA_STRUCT * pStruct, int * pPosition, unsigned long * pReadTag, unsigned long * pReadLength, const unsigned char ** pReadValue);
static int __ClessSample_DataExchange_ParseTag (T_BER_TLV_DECODE_STRUCT * pBerTlvStruct, BER_TLV_TAG * pReadTag, int * pBytesRead);
static int __ClessSample_DataExchange_DecodeTag (BER_TLV_TAG* pTag, const void* pBuffer, int nBufferSize);
static int __ClessSample_DataExchange_SkipPadding (const void* pBuffer, int nBufferSize);
static int __ClessSample_DataExchange_CheckMCWDOL (unsigned long ulLength, const unsigned char * pValue, unsigned long * ulLengthModified, unsigned char * pValueModified, unsigned long ulModifiedSize);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief This function clear TLVTree used to store parameters. 
//! \param[in] pTree Tree containing the Data Exchange parameters.

void ClessSample_DataExchange_InitTlvTree (TLV_TREE_NODE * pTree)
{
	if (pTree)
	{
		TlvTree_Release(*pTree);
		*pTree = NULL;
	}
}



//! \brief Dump the EVAL parameter file.

void ClessSample_DataExchange_DumpFile (TLV_TREE_NODE hTree)
{
	if (hTree != NULL)
		ClessSample_DumpData_DumpTlvTreeNodeWithTitle ("EVAL MCW FILE", hTree);
	else
		ClessSample_DumpData_DumpTitle ("NO EVAL FILE");
}



//! \brief Dump the EVAL file HEADER information.
//! \param[in] hTree TLV Tree containing the EVAL parameter file.

void ClessSample_DataExchange_DumpEvalHeaderInformation (TLV_TREE_NODE hTree)
{
	TLV_TREE_NODE hHeaderNode;
	TLV_TREE_NODE hTempNode;
	TLV_TREE_NODE hTempNodeGenBy;
	TLV_TREE_NODE hSignatureNode;
	unsigned int nLength;
	unsigned int nIndex;
	unsigned char * pValue;


	if (!ClessSample_DumpData_DumpOpenOutputDriver())
		return;

	if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
		ClessSample_DumpData("\x1b" "@\x1b" "E");

	if (hTree != NULL)
	{
		ClessSample_DumpData ("EVAL HEADER INFO");
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();

		// Change the character size
		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
				ClessSample_DumpData ("\x1b" "@" "\x0F");

		hHeaderNode = TlvTree_Find (hTree, MCW_XML_TAG_HEADER, 0);

		if (hHeaderNode != NULL)
		{
			hTempNode = TlvTree_GetFirstChild (hHeaderNode);

			do
			{
				if (hTempNode != NULL)
				{
					// Get the node data
					pValue = NULL;
					nLength = TlvTree_GetLength (hTempNode);
					if (nLength > 0)
						pValue = TlvTree_GetData (hTempNode);

					switch (TlvTree_GetTag (hTempNode))
					{
					case (MCW_XML_TAG_FILE_NAME):
						ClessSample_DumpData ("FILE NAME : ");
						for (nIndex=0; nIndex<nLength; nIndex++)
							ClessSample_DumpData ("%c", pValue[nIndex]);
						ClessSample_DumpData_DumpNewLine();
						break;
					case (MCW_XML_TAG_FILE_DATE):
						ClessSample_DumpData ("FILE DATE : ");
						for (nIndex=0; nIndex<nLength; nIndex++)
							ClessSample_DumpData ("%c", pValue[nIndex]);
						ClessSample_DumpData_DumpNewLine();
						break;
					case (MCW_XML_TAG_TEMPLATE_VERSION):
						ClessSample_DumpData ("TEMPLATE VERSION : ");
						for (nIndex=0; nIndex<nLength; nIndex++)
							ClessSample_DumpData ("%c", pValue[nIndex]);
						ClessSample_DumpData_DumpNewLine();
						break;
					case (MCW_XML_TAG_GENERATED_BY):
						ClessSample_DumpData ("GENERATED BY : ");
						ClessSample_DumpData_DumpNewLine();

						hTempNodeGenBy = TlvTree_GetFirstChild (hTempNode);

						do
						{
							if (hTempNodeGenBy != NULL)
							{
								// Get the node data
								pValue = NULL;
								nLength = TlvTree_GetLength (hTempNodeGenBy);
								if (nLength > 0)
									pValue = TlvTree_GetData (hTempNodeGenBy);

								switch (TlvTree_GetTag (hTempNodeGenBy))
								{
								case (MCW_XML_TAG_COMPANY_NAME):
									ClessSample_DumpData ("  COMPANY NAME : ");
									for (nIndex=0; nIndex<nLength; nIndex++)
										ClessSample_DumpData ("%c", pValue[nIndex]);
									ClessSample_DumpData_DumpNewLine();
									break;
								case (MCW_XML_TAG_PRODUCT_NAME):
									ClessSample_DumpData ("  PRODUCT NAME : ");
									for (nIndex=0; nIndex<nLength; nIndex++)
										ClessSample_DumpData ("%c", pValue[nIndex]);
									ClessSample_DumpData_DumpNewLine();
									break;
								case (MCW_XML_TAG_PRODUCT_VERSION):
									ClessSample_DumpData ("  PRODUCT VERSION : ");
									for (nIndex=0; nIndex<nLength; nIndex++)
										ClessSample_DumpData ("%c", pValue[nIndex]);
									ClessSample_DumpData_DumpNewLine();
									break;
								case (MCW_XML_TAG_OPERATOR_NAME):
									ClessSample_DumpData ("  OPERATOR NAME : ");
									for (nIndex=0; nIndex<nLength; nIndex++)
										ClessSample_DumpData ("%c", pValue[nIndex]);
									ClessSample_DumpData_DumpNewLine();
									break;
								default:
									break;
								}

								hTempNodeGenBy = TlvTree_GetNext (hTempNodeGenBy);
							}
						} while (hTempNodeGenBy != NULL);
						ClessSample_DumpData_DumpNewLine();
						break;
					default:
						ClessSample_DumpData ("UNKNOWN : %02X", TlvTree_GetTag (hTempNode));
						ClessSample_DumpData_DumpNewLine();
						break;
					}

					// Get every node in order to print the information
					hTempNode = TlvTree_GetNext (hTempNode);
				}
			} while (hTempNode != NULL);

			ClessSample_DumpData_DumpNewLine();
			ClessSample_DumpData_DumpNewLine();
		}

		// Restore character size
		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
			ClessSample_DumpData ("\x1b" "@");

		// Dump the signature
		hSignatureNode = TlvTree_Find (hTree, MCW_XML_TAG_SIGNATURE, 0);

		if (hSignatureNode != NULL)
		{
			// Get the node data
			pValue = NULL;
			nLength = TlvTree_GetLength (hSignatureNode);
			if (nLength > 0)
				pValue = TlvTree_GetData (hSignatureNode);

			ClessSample_DumpData ("SIGNATURE : ");
			for (nIndex=0; nIndex<nLength; nIndex++)
				ClessSample_DumpData ("%02X", pValue[nIndex]);
			ClessSample_DumpData_DumpNewLine();
		}

		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
	}
	else
	{
		ClessSample_DumpData ("NO EVAL FILE");
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();

		// Restore character size
		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
			ClessSample_DumpData ("\x1b" "@");
	}

	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();	

	// Close the output driver
	ClessSample_DumpData_DumpCloseOutputDriver();
}



//! \brief Load the Data Exchange tags file in memory.
//! \param[in] Volume path for the data exchange file.
//! \param[in] FileName file name for the data exchange file.
//! \param[out] pTree resultant TLV Tree.
//! \return
//!	- \a TRUE if a data exchange file has been loaded, 
//!	- \a FALSE else.

int ClessSample_DataExchange_ReadXMLFile(char * VolumeName, char * FileName, TLV_TREE_NODE * pTree)
{
	char FileName_L[DISK_NAME_SIZE];
	int bUseDefaultParameters = TRUE;

	if (strcmp(FileName, C_FILE_EVAL_XML) == 0)
	{
		// File has been received
		sprintf(FileName_L, "/%s/%s", VolumeName, FileName);

		// Read the Data Exchange File - try the param file read!
		ClessSample_XML_ConvertXmlToTlvTree (FileName_L, pTree, &__Xmls_Start, &__Xmls_Stop, &__Xmls_GetData, &bUseDefaultParameters);

		//Trace parameters on printer
		if (!bUseDefaultParameters) // A file has been read, and the default XML EVAL shall not be used
		{			
			// Save the parameters into a file (DEKDET_SAV.PAR)
			if (ClessSample_DataExchange_SaveFile (*pTree) != 0) // If a problem occurs
			{
				GTL_Traces_TraceDebug("ClessSample_DataExchange_ReadXMLFile : ClessSample_DataExchange_SaveFile() error");				
			}
		}
		else
		{
			GTL_Traces_DiagnosticText ("ClessSample_DataExchange_ReadXMLFile : DEKDET.PAR incorrect file received\n");
		}

		return (STOP);
	}

	// Default case
	return (FCT_OK);
}



//! \brief This function update TLVTree with EVAL XML read in a save file. 
//! \param[in] TLVTree to save.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int ClessSample_DataExchange_RestoreFile (TLV_TREE_NODE * pTree)
{
	// restore the stored data exchange file data
	char FilePath_L[80];
	int ret = FS_OK;
	char LabelDiskName[DISK_NAME_SIZE];
	int nResult;
	unsigned int Mode,rc;

	memclr(FilePath_L,sizeof(FilePath_L));

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__ClessSample_DataExchange_Get_Disk_Name(LabelDiskName);

	Mode = FS_WRTMOD;
	sprintf(FilePath_L, "/%s", LabelDiskName);

	rc = FS_mount(FilePath_L, &Mode);
	if (rc != FS_OK)
	{
		GTL_Traces_TraceDebug("ClessSample_DataExchange_RestoreFile : An error occurred when mounting the saved EVAL XML file");
		nResult = 1;
	}
	else
	{
		
		sprintf(FilePath_L, "/%s/%s", LabelDiskName, C_FILE_EVAL_SAV);
		// Set path in input buffer for BuildParameters() call
		ret = FS_exist (FilePath_L);
		
		if (ret == FS_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Parameters_RestoreParam : Load %s file", C_FILE_EVAL_SAV);
			// Load parameter file in the terminal
			nResult = __ClessSample_DataExchange_FileRead (pTree, FilePath_L, C_FILE_EVAL_SAV);
		}
		else
		{
			GTL_Traces_TraceDebug("ClessSample_Parameters_RestoreParam : %s file not existing", C_FILE_EVAL_SAV);
			nResult = 1;
		}
	}
	
	return (nResult);
}



//! \brief This function reads a file of parameters (XML format) and extract tags and value to build a TLVTree. 
//! \param[in] pTree to go throw to found tag informations.
//! \param[in] pc_x_DirFile file path of xml text file to read.
//! \param[in] pc_x_fileName file name of xml text file to read.
//! \return
//! - 0 if file read ok, 1 else.

static int __ClessSample_DataExchange_FileRead(TLV_TREE_NODE * pTree, char *pc_x_DirFile, char *pc_x_fileName)
{
	char ac_l_OutBuf[80];
	char LabelDiskName[DISK_NAME_SIZE];
	int nResult = 0;

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__ClessSample_DataExchange_Get_Disk_Name(LabelDiskName);

	sprintf(ac_l_OutBuf, "/%s/%s", LabelDiskName, C_FILE_EVAL_SAV);

	if ((strncmp(pc_x_fileName, C_FILE_EVAL_NAME_XML, sizeof(C_FILE_EVAL_NAME_XML)-1) == 0)	||
		(strncmp(pc_x_fileName, C_FILE_EVAL_SAV, sizeof(C_FILE_EVAL_SAV)-1) == 0) )
	{
		unsigned int FileTypeAccess = TLV_TREE_SERIALIZER_DEFAULT;

		if (__ClessSample_DataExchange_ReadEvalTreeFile (pTree, pc_x_DirFile, FileTypeAccess) != 0)
		{
			GTL_Traces_TraceDebug ("__ClessSample_Parameters_ReadParamFile() error");
			nResult = 1;
		}
		//ClessSample_Parameters_TlvTree_Display(pTree, "Read param.par");
	}
	return (nResult);
}



//! \brief This function reads a file of parameters (XML format) and extract tags and value to build a TLVTree. 
//! \param[in] pnode to store tags informations.
//! \param[in] pc_x_DirFile file path of xml text file to read.
//! \param[in] pc_x_fileName file name of xml text file to read.
//! \return
//! 0 if ok 1 else.

static int __ClessSample_DataExchange_ReadEvalTreeFile (TLV_TREE_NODE * p_node, char *pc_x_DirFile, unsigned int i_x_ParamFileType)
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
		GTL_Traces_TraceDebug ("PB Mount COM File");
	}
	ptr_file = FS_open(pc_x_DirFile, "r");

	if (ptr_file != NULL)
	{
		int s;
		unsigned long ulFileLength;

		ulFileLength = FS_length (ptr_file);
		
		if (ulFileLength>C_EVAL_DATA_MAX_BUFFER_SIZE) // If file size greater than max size
		{
			GTL_Traces_TraceDebug ("__ClessSample_Parameters_ReadParamFile : Parameter file size too important !!!");
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
				// Reset of this node, a problem occurred
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



//! \brief This function update a file with EVAL XML given in a TLVTree.
//! File is updated in TLVTree serial binary format.
//! \param[in] pTree to go save in file.
//! \param[in] ptr_OutBuf file path and name to update.
//! \return
//! - 0 if ok, 1 else.

static int __ClessSample_DataExchange_WriteBinFile (TLV_TREE_NODE hTree, char * ptr_OutBuf)
{
	unsigned char * ac_l_pucBuffer = NULL;
	unsigned int  result = 0;
	int           i_l_Size = 0;
	S_FS_FILE     *ptr_file;

	if (hTree == NULL)
		goto SuppressFile;

	// Input parameters checking
	if (strlen(ptr_OutBuf) == 0)
	{
		return (1);
	}

	// Check size
	i_l_Size = TlvTree_GetSerializationSize(hTree, TLV_TREE_SERIALIZER_DEFAULT);

	if (i_l_Size > C_EVAL_DATA_MAX_BUFFER_SIZE) // If file size greater than max size
	{
		GTL_Traces_TraceDebug ("__ClessSample_DataExchange_WriteBinFile : Parameter node size too important");
		result = (1);
	}
	else
	{
		ac_l_pucBuffer = (unsigned char *) umalloc(i_l_Size + 10);
		i_l_Size = TlvTree_Serialize (hTree, TLV_TREE_SERIALIZER_DEFAULT, ac_l_pucBuffer, i_l_Size + 10);

		// The buffer is saved in a file
		if ((i_l_Size < 0) || (i_l_Size > C_PUC_MAX_BUFFER_SIZE)) // If serialization pb
		{
			GTL_Traces_TraceDebug ("__ClessSample_DataExchange_WriteBinFile : Parameter node serialisation pb");
			result = (1);
		}
	}

SuppressFile:
	if (result == 0)	// If ok
	{
		unsigned int Mode,rc;
		int ret;

		// Create the disk
		ret = __ClessSample_DataExchange_CreateDisk();

		if (ret == FS_OK)
		{
			ret = FS_exist (ptr_OutBuf);

			if (ret == FS_OK)
			{
				GTL_Traces_TraceDebug ("__ClessSample_DataExchange_WriteBinFile : FILE EXIST");
				// The former file is suppressed. 
				ret = FS_unlink (ptr_OutBuf);

				if (hTree == 0)
					return (result);
			}
			else
			{
				// File does not exist, terminate
				if (hTree == 0)
					return (result);
			}
		}

		Mode = FS_WRTMOD;
		rc = FS_mount(ptr_OutBuf, &Mode);
		if (rc != FS_OK)
		{
			GTL_Traces_TraceDebug("PB Mount COM File param");
			result = 1;
		} 

		ptr_file = FS_open (ptr_OutBuf, "a");
		if (ptr_file == NULL)
		{
			result = 1;
			GTL_Traces_TraceDebug ("Error create file");
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



//! \brief This function give disk label used to store parameters. 
//! \param[in/out] Disk name to update.

static void __ClessSample_DataExchange_Get_Disk_Name (char* ptDiskName)
{
	sprintf (gs_DataExchange_Label_Disk_Name,"%s%02x", C_EVAL_LABEL_DISK, 0);
	memcpy (ptDiskName, gs_DataExchange_Label_Disk_Name, sizeof(gs_DataExchange_Label_Disk_Name));
}



//! \brief This function create give disk to store parameters. 
//! \return
//! FS_OK if disk created, other else.

static int __ClessSample_DataExchange_CreateDisk (void)
{
	int               nResult;
	unsigned long     DiskSize;
	S_FS_PARAM_CREATE EvalXmlCreat;
	char              FilePath_L[33];

	EvalXmlCreat.Mode         = FS_WRITEONCE;
	EvalXmlCreat.IdentZone    = FS_WO_ZONE_DATA;
	EvalXmlCreat.AccessMode   = FS_WRTMOD;
	EvalXmlCreat.NbFichierMax = 20;
	DiskSize				  = C_EVAL_DISK_SIZE;

	memclr (gs_DataExchange_Label_Disk_Name,sizeof(gs_DataExchange_Label_Disk_Name));
	sprintf (gs_DataExchange_Label_Disk_Name,"%s%02x", C_EVAL_LABEL_DISK, 0);
	strcpy (EvalXmlCreat.Label, gs_DataExchange_Label_Disk_Name);

	sprintf(FilePath_L, "/%s", gs_DataExchange_Label_Disk_Name);

	nResult = FS_mount (FilePath_L, &EvalXmlCreat.Mode);
	if (nResult != FS_OK)
	{
		nResult = FS_dskcreate(&EvalXmlCreat, &DiskSize);
	}

	return (nResult);
}



//! \brief This function set EVAL XML TLVTree parameters in a save file.
//!	\param[in] hTree TLV Tree to be saved in a file.

int ClessSample_DataExchange_SaveFile (TLV_TREE_NODE hTree)
{
	int nResult;
	char ac_l_FilePath_L[80];
	char LabelDiskName[DISK_NAME_SIZE];

	memclr (LabelDiskName, sizeof(LabelDiskName));
	__ClessSample_DataExchange_Get_Disk_Name (LabelDiskName);

	// Update PARAM.PAR serial binary TLVTree format file
	sprintf(ac_l_FilePath_L, "/%s/%s", LabelDiskName, C_FILE_EVAL_SAV);
	nResult = __ClessSample_DataExchange_WriteBinFile(hTree, ac_l_FilePath_L);

	return (nResult);
}



//! \brief Get the DET Signal data according to the kernel returned DEK signal.
//!
//! \param[in,out] pSharedStruct Shared buffer filled with the DEK Signal as input and DET signal as output.
//! \return
//!		- \ref TRUE if correctly performed (data found and \a pOutputDataStruct filled).
//!		- \ref FALSE if an error occurred or no data found.

int ClessSample_DataExchange_GetDETData (T_SHARED_DATA_STRUCT * pSharedStruct)
{
	TLV_TREE_NODE pDeParams;			// Node for DE expected exchanges
	TLV_TREE_NODE pChild;				// DEK Data content
	TLV_TREE_NODE pResearch;			// DET Data content
	TLV_TREE_NODE pDET;					// Working Node
	unsigned char * pKernelDEK=NULL;	// Kernel returned DEK signal data
	unsigned char * pKernelDET=NULL;	// Kernel returned DET signal data
	unsigned char * pParam=NULL;		// Param DEK data
	int nResult = FALSE;
	int nResultParam  = FALSE;
	int bProcessNextDEK = FALSE;
	int cr=0,nDEPosition, nParamPosition;
	unsigned long ulKernelDEKLength, ulKernelDETLength;
	unsigned long ulDEKLength, ulDETLength;
	unsigned long ulDEKTag, ulDETTag, ulDETTagMCW;
	const unsigned char *pDEKValue, *pDETValue;
	T_SHARED_DATA_STRUCT tDEKStruct, tDETStruct;
	unsigned long ulParamTag, ulParamTagMCW;
	unsigned long ulParamLength;
	const unsigned char *pParamValue;
	T_SHARED_DATA_STRUCT tParamStruct;
	unsigned char DEKData[2048];
	unsigned long LengthDEKData = 0;
	int DETCounter=0;
	unsigned long ulLengthModified=0;
	unsigned char ValueModified[256];		// Contains zero padded DOL data 
	
	// Initialised global to indicate DEK mismatch 
	ClessSample_DataExchange_SetDEKSignalStatus(FALSE);

	// processing DEK and DET Signals
	ClessSample_PayPass_SetDataExchangeInProgress(TRUE);

	if (pSharedStruct == NULL) // Input parameter control
	{
		GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData : pSharedStruct null");
		goto End;
	}

	// Get the DEK Signal data from the kernel Data Needed
	nDEPosition = SHARED_EXCHANGE_POSITION_NULL;
	if (GTL_SharedExchange_FindNext (pSharedStruct, &nDEPosition, TAG_PAYPASS_INT_DS_DATA_NEEDED, &ulKernelDEKLength, (const unsigned char **)&pKernelDEK) == STATUS_SHARED_EXCHANGE_OK)
	{
		// 'Data Needed' returned store the TLV for comparison with the param file
		if (LengthDEKData+nDEPosition > sizeof(DEKData))
		{
			// Not enough space to store the data
			GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData : Not enough space to store the 'Data Needed' data");
		}
		else
		{
			// copy the data to a local buffer to compare with the param file data
			memcpy (&DEKData[LengthDEKData], pSharedStruct->nPtrData, nDEPosition);
			LengthDEKData+=nDEPosition;
		}
	}
	else
	{
		// Check if Data To Send returned
		nDEPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pSharedStruct, &nDEPosition, TAG_PAYPASS_DS_DATA_TO_SEND, &ulKernelDEKLength, (const unsigned char **)&pKernelDEK) == STATUS_SHARED_EXCHANGE_OK)
		{
			// 'Data To Send' returned store the TLV for comparison with the param file
			if (LengthDEKData+nDEPosition > sizeof(DEKData))
			{
				// Not enough space to store the data
				GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData : Not enough space to store the 'Data To Send' data");
			}
			else
			{
				// copy the data to a local buffer to compare with the param file data
				memcpy (&DEKData[LengthDEKData], pSharedStruct->nPtrData, nDEPosition);
				LengthDEKData+=nDEPosition;
			}
		}
	}

	if (LengthDEKData == 0)
	{
		GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData : An error occurred as no DEK Signal");
		GTL_SharedExchange_ClearEx(pSharedStruct, FALSE);
		goto End;
	}
	else
	{
		// Check if MCW XML tree has DE parameters defined
		pDeParams = TlvTree_Find(pTreeCurrentDataExchange, MCW_XML_TAG_EVT_DEKRECEIVED, 0);
		
		if (pDeParams != NULL)
		{
			// DE Parameters present, get the DEK Signal
			pChild = TlvTree_GetFirstChild(pDeParams);

			while (pChild != NULL)
			{
				// Default to indicate no DEK match
				ClessSample_DataExchange_SetDEKSignalStatus(FALSE);

				// See if need to cancel DE processing
				if (!ClessSample_PayPass_GetDataExchangeInProgress())
					break;

				// Check if the DEK tag value is in the MCW XML tree
				pResearch = TlvTree_Find(pChild, MCW_XML_TAG_DEKVALUE, 0); 
				
				if (pResearch != NULL)
				{
					// Get the MCW XML tree DEK data
					pParam = TlvTree_GetData(pResearch);

					// Loop through each tag in the Kernel returned DEK Data "DEKData" and MCW defined Parameter file data "pParam" 
					if ((GTL_SharedExchange_InitEx (&tDEKStruct, LengthDEKData, LengthDEKData, DEKData) == STATUS_SHARED_EXCHANGE_OK) &&
						(GTL_SharedExchange_InitEx (&tParamStruct, TlvTree_GetLength(pResearch), TlvTree_GetLength(pResearch), pParam) == STATUS_SHARED_EXCHANGE_OK))
					{
						// Does the tag exist in the List
						bProcessNextDEK = FALSE;
						nDEPosition = SHARED_EXCHANGE_POSITION_NULL;
						nParamPosition = SHARED_EXCHANGE_POSITION_NULL;

						do
						{
							// Get the next tag in the kernel DEK
							nResult = GTL_SharedExchange_GetNext (&tDEKStruct, &nDEPosition, &ulDEKTag, &ulDEKLength, &pDEKValue);

							// Check for overrun
							if (nResult == STATUS_SHARED_EXCHANGE_END)
							{
								// Get the next tag in the Param file
								nResultParam = __ClessSample_DataExchange_GetNext (&tParamStruct, &nParamPosition, &ulParamTagMCW, &ulParamLength, &pParamValue);

								if (nResultParam == STATUS_SHARED_EXCHANGE_OK)
								{
									// DEK Value does not match, move onto the next DEK in the param file
									GTL_Traces_TraceDebug("ClessSample_DataExchange_GetDETData: DEK mismatch, overrun on MCW Param DEK");
									bProcessNextDEK = TRUE; 
								}
							}
							else if (nResult == STATUS_SHARED_EXCHANGE_OK)
							{
								// not the end of the kernel DEK buffer, check the Param file 
								nResultParam = __ClessSample_DataExchange_GetNext (&tParamStruct, &nParamPosition, &ulParamTagMCW, &ulParamLength, &pParamValue);

								if (nResultParam == STATUS_SHARED_EXCHANGE_END)
								{
									// DEK Value does not match, move onto the next DEK in the param file
									GTL_Traces_TraceDebug("ClessSample_DataExchange_GetDETData: DEK mismatch, overrun on kernel DEK");
									bProcessNextDEK = TRUE; 
								}
							}

							// Continue if a tag found in both kernel DEK and Param DEK
							if ((nResult == STATUS_SHARED_EXCHANGE_OK) && (nResultParam == STATUS_SHARED_EXCHANGE_OK))
							{
								// check if the equivalent MCW tag is present
								ulParamTag = ClessSample_DataExchange_McwTagConversion (ulParamTagMCW);

								// check the kernel DEK and MCW tag match (ignore constructed tags that could contain Ingenico tags)
								if ((ulDEKTag != ulParamTag) || 
									((ulDEKLength != ulParamLength) && ((ulDEKTag!=TAG_PAYPASS_INT_DS_DATA_NEEDED) &&
																  		(ulDEKTag!=TAG_PAYPASS_DS_DATA_TO_SEND))))
								{
									// DEK Length does not match, move onto the next DEK in the param file
									GTL_Traces_TraceDebug("ClessSample_DataExchange_GetDETData: DEK mismatch on tag %lx", ulDEKTag);
									bProcessNextDEK = TRUE; 
								}
								else
								{
									// specific processing for the DEK data in the MCW Param file as there is no zero padding
									if (ulDEKTag==TAG_PAYPASS_INT_DS_DATA_NEEDED)
									{
										if (__ClessSample_DataExchange_CheckMCWDOL(ulParamLength, pParamValue, &ulLengthModified, ValueModified, sizeof(ValueModified)))
										{
											// Check the modified value
											if (!__ClessSample_DataExchange_Alignment (pDEKValue, ValueModified, ulDEKLength, ulLengthModified))
											{
												// DEK Value does not match, move onto the next DEK in the param file
												GTL_Traces_TraceDebug("ClessSample_DataExchange_GetDETData: DEK alignment mismatch in Data needed, move to next DEK in PAR file");
												bProcessNextDEK = TRUE; 
											}
										}
									}
									else
									{
										// Check the value
										if (!__ClessSample_DataExchange_Alignment (pDEKValue, pParamValue, ulDEKLength, ulParamLength))
										{
											// DEK Value does not match, move onto the next DEK in the param file
											GTL_Traces_TraceDebug("ClessSample_DataExchange_GetDETData: DEK alignment mismatch, move to next DEK in PAR file");
											bProcessNextDEK = TRUE; 
										}
									}
								}
							}

						} while ((nResult == STATUS_SHARED_EXCHANGE_OK) && (!bProcessNextDEK));

						// Check both DEK and Param file parsing completed
						if (!bProcessNextDEK)
						{
							// Indicate match found
							ClessSample_DataExchange_SetDEKSignalStatus(TRUE);
						}
					}
					else
					{
						GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData : GTL_SharedExchange_InitEx error");
						goto End;
					}

					// reset the DET counter
					DETCounter=0;

					// Check if the DEK returned matched a DEK in the DEKDET.PAR file
					if (ClessSample_DataExchange_GetDEKSignalStatus())
					{
						GTL_Traces_TraceDebug("ClessSample_DataExchange_GetDETData: DEK Match");

						// Clear the shared structure to store the DET signal
						GTL_SharedExchange_ClearEx(pSharedStruct, FALSE);

						// Get the DET Signal which should be next after the DEK in the parameter file
						pDET = TlvTree_Find(pChild, MCW_XML_TAG_DETVALUE, 0); // Get the DET for that child from the param file

						// Get all the following DET signals in the output structure
						while ((pDET != NULL) && (TlvTree_GetTag(pDET) == MCW_XML_TAG_DETVALUE))
						{
							if (!ClessSample_PayPass_GetDataExchangeInProgress())
								break;

							// Get the DET tag data and add to the exchange
							ulKernelDETLength = TlvTree_GetLength(pDET);
							pKernelDET = TlvTree_GetData(pDET);

							if (GTL_SharedExchange_InitEx (&tDETStruct, ulKernelDETLength, ulKernelDETLength, pKernelDET) == STATUS_SHARED_EXCHANGE_OK)
							{
								// Does the tag exist in the List
								nDEPosition = SHARED_EXCHANGE_POSITION_NULL;

								do
								{
									// Loop on each tag in each Share exchange buffer
									nResult = __ClessSample_DataExchange_GetNext (&tDETStruct, &nDEPosition, &ulDETTagMCW, &ulDETLength, &pDETValue);

									if (nResult == STATUS_SHARED_EXCHANGE_OK) // If DET tag found
									{
										// convert MCW DET tag to our tag 
										ulDETTag = ClessSample_DataExchange_McwTagConversion (ulDETTagMCW);

										// The Tag to Read MCW DOL can contain other MCW tags
										if (ulDETTag == TAG_PAYPASS_DS_TAGS_TO_READ)
										{
											if (__ClessSample_DataExchange_CheckMCWDOL(ulDETLength, pDETValue, &ulLengthModified, ValueModified, sizeof(ValueModified)))
											{
												// Add DET Signal data to the output
												cr = GTL_SharedExchange_AddTag(pSharedStruct, ulDETTag, ulLengthModified, ValueModified);
												if (cr != STATUS_SHARED_EXCHANGE_OK)
												{
													GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData : An error occurred when adding modified tag data in the shared structure (cr = %02x)", cr);
													GTL_SharedExchange_ClearEx(pSharedStruct, FALSE);
													goto End;
												}
											}
											else
											{
												GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData : __ClessSample_DataExchange_CheckMCWDOL DET parsing NOK");
											}
										}
										else
										{
											// Add DET Signal data to the output
											cr = GTL_SharedExchange_AddTag(pSharedStruct, ulDETTag, ulDETLength, pDETValue);
											if (cr != STATUS_SHARED_EXCHANGE_OK)
											{
												GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData An error occurred when adding tag in the shared structure (cr = %02x)", cr);
												GTL_SharedExchange_ClearEx(pSharedStruct, FALSE);
												goto End;
											}
										}
									}
									else if (nResult != STATUS_SHARED_EXCHANGE_END)
									{
										// A parsing error occurred
										GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData : GTL_SharedExchange_GetNext DET error:%x", nResult);
										goto End;
									}

								} while (nResult == STATUS_SHARED_EXCHANGE_OK);							
							}
							
							// Check if there is another DET signal
							DETCounter++;					// Increment the DET counter

							// Get the next DET 
							pDET = TlvTree_Find(pChild, MCW_XML_TAG_DETVALUE, DETCounter); // Get the next DET 

							// If there is another DET Signal to be sent, send the ServiceCall to process the current DET
							if ((pDET != NULL) && (pSharedStruct != NULL))
							{
								// ServiceCall to process this DET
								cr = PayPass3_DETSignal (pSharedStruct);

								if (cr != KERNEL_STATUS_OK)
								{
									// An error occurred
									GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData : An error occurred when sending the DET Signal to the PayPass kernel (cr=%02x)", cr);
									goto End;
								}
							}
						}
					
						nResult = TRUE;
						goto End;
					}
				}

				// Check the next DEK Signal in Parameter file
				pChild = TlvTree_GetNext(pChild);

			} // end of while
		}
		else
		{
			GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData : No DE Parameters defined in the loaded param file");
		}
	}
End:
	if (!ClessSample_DataExchange_GetDEKSignalStatus())
	{
		// no match found, clear the shared structure
		GTL_SharedExchange_ClearEx(pSharedStruct, FALSE);

		// No matching DEK Signal, send CANCEL (as requested by testing, Ludovic 11.01.2012)
		GTL_Traces_TraceDebug("ClessSample_Parameters_GetDETData : No Matching DEK Signal, send PayPass3_Cancel");
		PayPass3_Cancel ();
	}

	// Indicate that current Data Exchange processing is complete
	ClessSample_PayPass_SetDataExchangeInProgress(FALSE);

	return (nResult);
}



//! \brief Check if the Value portion of the DEK signal matches - aligning tags that can be variable in the signal
//! \param[in] pDEKValue buffer filled with the DEK Signal.
//! \param[in] pParamValue buffer filled with the Parameter file data.
//! \param[in] ulLength length of the buffer.
//! \return
//!		- \ref TRUE if correctly performed and data matched.
//!		- \ref FALSE if an error occurred or no data found.

static int __ClessSample_DataExchange_Alignment (const unsigned char * pDEKValue, const unsigned char * pParamValue, unsigned long ulLengthDEK, unsigned long ulLengthParam)
{
	int nResult = FALSE;
	unsigned long ulDEKTag, ulParamTag, ulParamTagMCW;
	unsigned long ulDEKLength,ulParamLength;
	const unsigned char *pDEKData, *pParamData;
	T_SHARED_DATA_STRUCT tDEKStruct, tParamStruct;
	int nDEPosition, nParamPosition;
	int nDEKFound = FALSE;
	int nDEKParamFound = FALSE;

	// Check if the modified Value matches
	if ((ulLengthDEK == ulLengthParam) && (memcmp (pDEKValue, pParamValue, ulLengthDEK) == 0))
	{
		return (TRUE);
	}
	else
	{
		// check for partial match
		if ((GTL_SharedExchange_InitEx (&tDEKStruct, ulLengthDEK, ulLengthDEK, (unsigned char *)pDEKValue) == STATUS_SHARED_EXCHANGE_OK) &&
			(GTL_SharedExchange_InitEx (&tParamStruct, ulLengthParam, ulLengthParam, (unsigned char *)pParamValue) == STATUS_SHARED_EXCHANGE_OK))
		{
			nDEPosition = SHARED_EXCHANGE_POSITION_NULL;
			nParamPosition = SHARED_EXCHANGE_POSITION_NULL;

			do
			{
				// Initialise to ensure both DEK and DEK Param found
				nDEKFound = FALSE;
				nDEKParamFound = FALSE;

				// Loop on each tag in each Share exchange buffer
				nResult = GTL_SharedExchange_GetNext (&tDEKStruct, &nDEPosition, &ulDEKTag, &ulDEKLength, &pDEKData);

				if (nResult == STATUS_SHARED_EXCHANGE_OK) 
				{
					// DEK tag found
					nDEKFound = TRUE;

					// since the MCW param file can contain zero length tags without 0x00 then this need handled locally
					nResult = __ClessSample_DataExchange_GetNext (&tParamStruct, &nParamPosition, &ulParamTagMCW, &ulParamLength, &pParamData);
			
					if (nResult == STATUS_SHARED_EXCHANGE_OK) // If Param tag found
					{
						// DEK Param tag found
						nDEKParamFound = TRUE;

						// Check if DEK Param needs converted from MCW format to Ingenico format before comparison
						ulParamTag = ClessSample_DataExchange_McwTagConversion (ulParamTagMCW);

						// check the kernel DEK and MCW tag match
						if ((ulDEKTag != ulParamTag) || (ulDEKLength != ulParamLength))
						{
							// DEK does not match
							return(FALSE);
						}
						else
						{
							switch (ulParamTag)
							{
								case TAG_EMV_IFD_SERIAL_NUMBER:
								case TAG_EMV_TERMINAL_CAPABILITIES:
								case TAG_EMV_TERMINAL_TYPE:
								case TAG_EMV_UNPREDICTABLE_NUMBER:
								case TAG_EMV_ADD_TERMINAL_CAPABILITIES:
								case TAG_EMV_TRANSACTION_SEQUENCE_COUNTER:
								case TAG_EMV_TRANSACTION_TIME:
								case TAG_EMV_TRANSACTION_DATE:
								case TAG_PAYPASS_DS_SUMMARY_1:
								case TAG_PAYPASS_DS_UNPREDICTABLE_NUMBER:
								{
									// ignore the matching of these variable tag values
									break;
								}
								break;

								default:
								{
									// check the value matches
									if (memcmp (pDEKData, pParamData, ulParamLength) != 0)
									{
										// DEK does not match
										return(FALSE);
									}
								}
								break;
							}

							if ((ulLengthDEK == (unsigned)nDEPosition) && (ulLengthParam == (unsigned)nParamPosition))
							{
								// End DEK matching as reached the end of the DEK and DEK Param data
								return (TRUE);
							}
						}
					}
					else if (nResult != STATUS_SHARED_EXCHANGE_END)
					{
						GTL_Traces_TraceDebug("__ClessSample_DataExchange_Alignment : GTL_SharedExchange_GetNext Param error:%x", nResult);
						break;
					}
				}
				else if (nResult != STATUS_SHARED_EXCHANGE_END)
				{
					// A parsing error occurred
					GTL_Traces_TraceDebug("__ClessSample_DataExchange_Alignment : GTL_SharedExchange_GetNext DEK error:%x", nResult);
					break;
				}

			} while (nResult != STATUS_SHARED_EXCHANGE_END);
		}
	}

	if ((nResult == STATUS_SHARED_EXCHANGE_END) && (nDEKFound) && (nDEKParamFound))
	{
		return(TRUE);
	}
	else
	{
		return(FALSE);
	}
}



//! \brief This function is called on each start tag encountered by the XML parser.
//! \param[in] hParser Handle on the parser object
//! \param[in] szName Name of the start tag
//! \param[in] pAttributes Pointer on an array of attributes
//! \param[in] nAttributesNumber Number of attributes

static void __Xmls_Start (XMLs_PARSER hParser, const char* szName, XMLs_ATTRIBUTE* pAttributes, unsigned int nAttributesNumber)
{
	char* szAttributeName;
	char* szAttributeValue;
	int nIndex;
	TLV_TREE_NODE tCreatedNode = NULL;
	int nResult = FALSE;
	TLV_TREE_NODE hTempNode = (TLV_TREE_NODE) XMLs_GetUserData (hParser);

	/////////////////////////////////////////////////////////////////////////
	// "MESSAGE" plot
	if (strcmp(szName, MCW_XML_PLOT_MESSAGE) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_MESSAGE, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "HEADER" plot
	if (strcmp(szName, MCW_XML_PLOT_HEADER) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_HEADER, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "BODY" plot
	if (strcmp(szName, MCW_XML_PLOT_BODY) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_BODY, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "EVT" plot
	if (strcmp(szName, MCW_XML_PLOT_EVT) == 0)
	{
		// Check attributes and value
		for (nIndex = 0; nIndex < (int)nAttributesNumber; nIndex++)
		{
			szAttributeName = (char *) pAttributes[nIndex].m_szName;
			szAttributeValue = (char *) pAttributes[nIndex].m_szValue;

			if (strcmp(szAttributeName, MCW_XML_EVT_ATTRIBUTE_TYPE) == 0)
			{
				// The "type" attribute has been found for the "EVT" plot
				if (strcmp(szAttributeValue, MCW_XML_EVT_TYPE_DEKRECEIVED) == 0)
				{
					// "DEKRECEIVED" attribute value
					nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_EVT_DEKRECEIVED, &tCreatedNode);
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////
	// "DEK" plot
	if (strcmp(szName, MCW_XML_PLOT_DEK) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_DEK, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "DET" plot
	if (strcmp(szName, MCW_XML_PLOT_DET) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_DET, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "DEKPROPERTIES" plot
	if (strcmp(szName, MCW_XML_PLOT_DEKPROPERTIES) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_DEKPROPERTIES, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "DETPROPERTIES" plot
	if (strcmp(szName, MCW_XML_PLOT_DETPROPERTIES) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_DETPROPERTIES, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "TRAILER" plot
	if (strcmp(szName, MCW_XML_PLOT_TRAILER) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_TRAILER, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "FILE_NAME" plot
	if (strcmp(szName, MCW_XML_FIELD_FILE_NAME) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_FILE_NAME, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "FILE_DATE" plot
	if (strcmp(szName, MCW_XML_FIELD_FILE_DATE) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_FILE_DATE, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "TEMPLATE_VERSION" plot
	if (strcmp(szName, MCW_XML_FIELD_TEMPLATE_VERSION) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_TEMPLATE_VERSION, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "GENERATED_BY" plot
	if (strcmp(szName, MCW_XML_FIELD_GENERATED_BY) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_GENERATED_BY, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "COMPANY_NAME" plot
	if (strcmp(szName, MCW_XML_FIELD_COMPANY_NAME) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_COMPANY_NAME, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "PRODUCT_NAME" plot
	if (strcmp(szName, MCW_XML_FIELD_PRODUCT_NAME) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_PRODUCT_NAME, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "PRODUCT_VERSION" plot
	if (strcmp(szName, MCW_XML_FIELD_PRODUCT_VERSION) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_PRODUCT_VERSION, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "OPERATOR_NAME" plot
	if (strcmp(szName, MCW_XML_FIELD_OPERATOR_NAME) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_OPERATOR_NAME, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "DEKVALUE" plot
	if (strcmp(szName, MCW_XML_FIELD_DEKVALUE) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_DEKVALUE, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "DETVALUE" plot
	if (strcmp(szName, MCW_XML_FIELD_DETVALUE) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_DETVALUE, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "STATE" plot
	if (strcmp(szName, MCW_XML_FIELD_STATE) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_STATE, &tCreatedNode);

	/////////////////////////////////////////////////////////////////////////
	// "SIGNATURE" plot
	if (strcmp(szName, MCW_XML_FIELD_SIGNATURE) == 0)
		nResult = ClessSample_XML_CreateNode (&hTempNode, MCW_XML_TAG_SIGNATURE, &tCreatedNode);

	if (nResult)
		XMLs_SetUserData (hParser, tCreatedNode);
}



//! \brief Prototype of the call-back function called on an end tag.
//!	\param[in] hXmlParser Handle on the parser object
//!	\param[in] szName Name of the end tag

static void __Xmls_Stop (XMLs_PARSER hXmlParser, const char* szName)
{
	TLV_TREE_NODE hTempNode = (TLV_TREE_NODE) XMLs_GetUserData (hXmlParser);
	TLV_TREE_NODE hNode = NULL;
	(void) szName;

	if (hTempNode)
		hNode = TlvTree_GetParent (hTempNode);
	XMLs_SetUserData(hXmlParser, hNode);
}



//!	\brief Prototype of the call-back function called on data.
//!	\param[in] hXmlParser Handle on the parser object.
//!	\param[in] pcDataBuffer Pointer on the beginning of the data.
//!	\param[in] nLength Data length.

static void __Xmls_GetData (XMLs_PARSER hXmlParser, const char*  pcDataBuffer, unsigned int nLength)
{
	TLV_TREE_NODE hTempNode = (TLV_TREE_NODE) XMLs_GetUserData (hXmlParser);

	if (hTempNode == NULL) // Protection against error
	{
		ClessSample_XML_SetDataNode (&hTempNode, nLength, (unsigned char*)pcDataBuffer, FORMAT_NODATA);
		return;
	}

	switch (TlvTree_GetTag(hTempNode))
	{
	case (MCW_XML_TAG_FILE_NAME): // "FILE_NAME" plot
	case (MCW_XML_TAG_FILE_DATE): // "FILE_DATE" plot
	case (MCW_XML_TAG_TEMPLATE_VERSION): // "TEMPLATE_VERSION" plot
	case (MCW_XML_TAG_GENERATED_BY): // "GENERATED_BY" plot
	case (MCW_XML_TAG_COMPANY_NAME): // "COMPANY_NAME" plot
	case (MCW_XML_TAG_PRODUCT_NAME): // "PRODUCT_NAME" plot
	case (MCW_XML_TAG_PRODUCT_VERSION): // "PRODUCT_VERSION" plot
	case (MCW_XML_TAG_OPERATOR_NAME): // "OPERATOR_NAME" plot
	case (MCW_XML_TAG_STATE): // "STATE" plot
		ClessSample_XML_SetDataNode (&hTempNode, nLength, (unsigned char*)pcDataBuffer, FORMAT_ASCII);
		break;

	case (MCW_XML_TAG_DEKVALUE): // "DEKVALUE" plot
	case (MCW_XML_TAG_DETVALUE): // "DETVALUE" plot
	case (MCW_XML_TAG_SIGNATURE): // "SIGNATURE" plot
		ClessSample_XML_SetDataNode (&hTempNode, nLength, (unsigned char*)pcDataBuffer, FORMAT_BINARY);
		break;
	
	case (MCW_XML_TAG_MESSAGE): // "MESSAGE" plot
	case (MCW_XML_TAG_HEADER): // "HEADER" plot
	case (MCW_XML_TAG_BODY): // "BODY" plot
	case (MCW_XML_TAG_EVT_DEKRECEIVED): // "EVT" plot with "type = DEKRECEIVED"
	case (MCW_XML_TAG_DEK): // "DEK" plot
	case (MCW_XML_TAG_DET): // "DET" plot
	case (MCW_XML_TAG_DEKPROPERTIES): // "DEKPROPERTIES" plot
	case (MCW_XML_TAG_DETPROPERTIES): // "DETPROPERTIES" plot
	case (MCW_XML_TAG_TRAILER): // "TRAILER" plot
	default:
		ClessSample_XML_SetDataNode (&hTempNode, nLength, (unsigned char*)pcDataBuffer, FORMAT_NODATA);
		break;
	}
}



//! \brief Convert the Ingenico internal tags to the MCW defined tags.
//!	\param[in] nTagToConvert Tag to be converted.
//!	\return The converted tag if recognized, \a nTagToConvert else.

int ClessSample_DataExchange_McwTagConversion (const int nTagToConvert)
{
	int nConvertedTag;

	switch (nTagToConvert)
	{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Ingenico > MCW
	case (TAG_PAYPASS_DD_CARD_TRACK1):								nConvertedTag = TAG_MCW_PAYPASS_DD_CARD_TRACK1;								break;
	case (TAG_PAYPASS_DD_CARD_TRACK2):								nConvertedTag = TAG_MCW_PAYPASS_DD_CARD_TRACK2;								break;
	case (TAG_PAYPASS_DEFAULT_UDOL):								nConvertedTag = TAG_MCW_PAYPASS_DEFAULT_UDOL;								break;
	case (TAG_PAYPASS_INT_MCHIP_GENAC_REF_CTRL_PARAMETER):			nConvertedTag = TAG_MCW_PAYPASS_INT_MCHIP_GENAC_REF_CTRL_PARAMETER;			break;
	case (TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_NO_DCV):				nConvertedTag = TAG_MCW_PAYPASS_CLESS_TRANSACTION_LIMIT_NO_DCV;				break;
	case (TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_DCV):					nConvertedTag = TAG_MCW_PAYPASS_CLESS_TRANSACTION_LIMIT_DCV;				break;
	case (TAG_PAYPASS_OUTCOME_PARAMETER_SET):						nConvertedTag = TAG_MCW_PAYPASS_OUTCOME_PARAMETER_SET;						break;
	case (TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA):					nConvertedTag = TAG_MCW_PAYPASS_USER_INTERFACE_REQUEST_DATA;				break;
	case (TAG_PAYPASS_ERROR_INDICATION):							nConvertedTag = TAG_MCW_PAYPASS_ERROR_INDICATION;							break;
	case (TAG_PAYPASS_KERNEL_CONFIGURATION):						nConvertedTag = TAG_MCW_PAYPASS_KERNEL_CONFIGURATION;						break;
	case (TAG_PAYPASS_CARD_DATA_INPUT_CAPABILITY):					nConvertedTag = TAG_MCW_PAYPASS_CARD_DATA_INPUT_CAPABILITY;					break;
	case (TAG_PAYPASS_SECURITY_CAPABILITY):							nConvertedTag = TAG_MCW_PAYPASS_SECURITY_CAPABILITY;						break;
	case (TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_REQUIRED):			nConvertedTag = TAG_MCW_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_REQUIRED;			break;
	case (TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_NOT_REQUIRED):		nConvertedTag = TAG_MCW_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_NOT_REQUIRED;		break;
	case (TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_REQUIRED):			nConvertedTag = TAG_MCW_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_REQUIRED;		break;
	case (TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_NOT_REQUIRED): 	nConvertedTag = TAG_MCW_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_NOT_REQUIRED;	break;
	case (TAG_PAYPASS_DEFAULT_HOLD_TIME):							nConvertedTag = TAG_MCW_PAYPASS_DEFAULT_HOLD_TIME;							break;
	case (TAG_PAYPASS_BALANCE_READ_BEFORE_GENAC):					nConvertedTag = TAG_MCW_PAYPASS_BALANCE_READ_BEFORE_GENAC;					break;
	case (TAG_PAYPASS_BALANCE_READ_AFTER_GENAC):					nConvertedTag = TAG_MCW_PAYPASS_BALANCE_READ_AFTER_GENAC;					break;
	case (TAG_PAYPASS_INT_DS_INPUT_TERM):							nConvertedTag = TAG_MCW_PAYPASS_INT_DS_INPUT_TERM;							break;
	case (TAG_PAYPASS_INT_DS_ODS_INFO_FOR_KERNEL):					nConvertedTag = TAG_MCW_PAYPASS_INT_DS_ODS_INFO_FOR_KERNEL;					break;
	case (TAG_PAYPASS_INT_DS_SUMMARY_2):							nConvertedTag = TAG_MCW_PAYPASS_INT_DS_SUMMARY_2;							break;
	case (TAG_PAYPASS_INT_DS_SUMMARY_3):							nConvertedTag = TAG_MCW_PAYPASS_INT_DS_SUMMARY_3;							break;
	case (TAG_PAYPASS_INT_DS_SUMMARY_STATUS):						nConvertedTag = TAG_MCW_PAYPASS_INT_DS_SUMMARY_STATUS;						break;
	case (TAG_PAYPASS_INT_DSVN_TERM):								nConvertedTag = TAG_MCW_PAYPASS_INT_DSVN_TERM;								break;
	case (TAG_PAYPASS_POST_GENAC_PUT_DATA_STATUS):					nConvertedTag = TAG_MCW_PAYPASS_POST_GENAC_PUT_DATA_STATUS;					break;
	case (TAG_PAYPASS_PRE_GENAC_PUT_DATA_STATUS):					nConvertedTag = TAG_MCW_PAYPASS_PRE_GENAC_PUT_DATA_STATUS;					break;
	case (TAG_PAYPASS_INT_DS_AC_TYPE):								nConvertedTag = TAG_MCW_PAYPASS_INT_DS_AC_TYPE;								break;
	case (TAG_PAYPASS_INT_DS_IDS_STATUS):							nConvertedTag = TAG_MCW_PAYPASS_INT_DS_IDS_STATUS;							break;
	case (TAG_PAYPASS_DS_PROCEED_TO_FIRST_WRITE):					nConvertedTag = TAG_MCW_PAYPASS_DS_PROCEED_TO_FIRST_WRITE;					break;
	case (TAG_PAYPASS_TIME_OUT_VALUE):								nConvertedTag = TAG_MCW_PAYPASS_TIME_OUT_VALUE;								break;
	case (TAG_PAYPASS_CONSTRUCTED_DRDOL_VALUE):						nConvertedTag = TAG_MCW_PAYPASS_CONSTRUCTED_DRDOL_VALUE;					break;
	case (TAG_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS):			nConvertedTag = TAG_MCW_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS;			break;
	case (TAG_PAYPASS_MAX_LIFETIME_OF_TORN_TXN_LOG_RECORD):			nConvertedTag = TAG_MCW_PAYPASS_MAX_LIFETIME_OF_TORN_TXN_LOG_RECORD;		break;
	case (TAG_PAYPASS_DATA_RECORD):									nConvertedTag = TAG_MCW_PAYPASS_DATA_RECORD;								break;
	case (TAG_PAYPASS_DISCRETIONARY_DATA):							nConvertedTag = TAG_MCW_PAYPASS_DISCRETIONARY_DATA;							break;
	case (TAG_PAYPASS_TORN_RECORD):									nConvertedTag = TAG_MCW_PAYPASS_TORN_RECORD;								break;
	case (TAG_PAYPASS_DS_TAGS_TO_READ):								nConvertedTag = TAG_MCW_PAYPASS_DS_TAGS_TO_READ;							break;
	case (TAG_PAYPASS_DS_TAGS_TO_WRITE_AFTER_GENAC):				nConvertedTag = TAG_MCW_PAYPASS_DS_TAGS_TO_WRITE_AFTER_GENAC;				break;
	case (TAG_PAYPASS_DS_TAGS_TO_WRITE_BEFORE_GENAC):				nConvertedTag = TAG_MCW_PAYPASS_DS_TAGS_TO_WRITE_BEFORE_GENAC;				break;
	case (TAG_PAYPASS_DS_DATA_TO_SEND):								nConvertedTag = TAG_MCW_PAYPASS_DS_DATA_TO_SEND;							break;
	case (TAG_PAYPASS_INT_DS_DATA_NEEDED):							nConvertedTag = TAG_MCW_PAYPASS_INT_DS_DATA_NEEDED;							break;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// MCW > Ingenico
	case (TAG_MCW_PAYPASS_DD_CARD_TRACK1):							nConvertedTag = TAG_PAYPASS_DD_CARD_TRACK1;									break;
	case (TAG_MCW_PAYPASS_DD_CARD_TRACK2):							nConvertedTag = TAG_PAYPASS_DD_CARD_TRACK2;									break;
	case (TAG_MCW_PAYPASS_DEFAULT_UDOL):							nConvertedTag = TAG_PAYPASS_DEFAULT_UDOL;									break;
	case (TAG_MCW_PAYPASS_INT_MCHIP_GENAC_REF_CTRL_PARAMETER):		nConvertedTag = TAG_PAYPASS_INT_MCHIP_GENAC_REF_CTRL_PARAMETER;				break;
	case (TAG_MCW_PAYPASS_CLESS_TRANSACTION_LIMIT_NO_DCV):			nConvertedTag = TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_NO_DCV;					break;
	case (TAG_MCW_PAYPASS_CLESS_TRANSACTION_LIMIT_DCV):				nConvertedTag = TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_DCV;					break;
	case (TAG_MCW_PAYPASS_OUTCOME_PARAMETER_SET):					nConvertedTag = TAG_PAYPASS_OUTCOME_PARAMETER_SET;							break;
	case (TAG_MCW_PAYPASS_USER_INTERFACE_REQUEST_DATA):				nConvertedTag = TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA;					break;
	case (TAG_MCW_PAYPASS_ERROR_INDICATION):						nConvertedTag = TAG_PAYPASS_ERROR_INDICATION;								break;
	case (TAG_MCW_PAYPASS_KERNEL_CONFIGURATION):					nConvertedTag = TAG_PAYPASS_KERNEL_CONFIGURATION;							break;
	case (TAG_MCW_PAYPASS_CARD_DATA_INPUT_CAPABILITY):				nConvertedTag = TAG_PAYPASS_CARD_DATA_INPUT_CAPABILITY;						break;
	case (TAG_MCW_PAYPASS_SECURITY_CAPABILITY):						nConvertedTag = TAG_PAYPASS_SECURITY_CAPABILITY;							break;
	case (TAG_MCW_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_REQUIRED):		nConvertedTag = TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_REQUIRED;				break;
	case (TAG_MCW_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_NOT_REQUIRED):	nConvertedTag = TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_NOT_REQUIRED;			break;
	case (TAG_MCW_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_REQUIRED):		nConvertedTag = TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_REQUIRED;			break;
	case (TAG_MCW_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_NOT_REQUIRED): nConvertedTag = TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_NOT_REQUIRED;		break;
	case (TAG_MCW_PAYPASS_DEFAULT_HOLD_TIME):						nConvertedTag = TAG_PAYPASS_DEFAULT_HOLD_TIME;								break;
	case (TAG_MCW_PAYPASS_BALANCE_READ_BEFORE_GENAC):				nConvertedTag = TAG_PAYPASS_BALANCE_READ_BEFORE_GENAC;						break;
	case (TAG_MCW_PAYPASS_BALANCE_READ_AFTER_GENAC):				nConvertedTag = TAG_PAYPASS_BALANCE_READ_AFTER_GENAC;						break;
	case (TAG_MCW_PAYPASS_INT_DS_INPUT_TERM):						nConvertedTag = TAG_PAYPASS_INT_DS_INPUT_TERM;								break;
	case (TAG_MCW_PAYPASS_INT_DS_ODS_INFO_FOR_KERNEL):				nConvertedTag = TAG_PAYPASS_INT_DS_ODS_INFO_FOR_KERNEL;						break;
	case (TAG_MCW_PAYPASS_INT_DS_SUMMARY_2):						nConvertedTag = TAG_PAYPASS_INT_DS_SUMMARY_2;								break;
	case (TAG_MCW_PAYPASS_INT_DS_SUMMARY_3):						nConvertedTag = TAG_PAYPASS_INT_DS_SUMMARY_3;								break;
	case (TAG_MCW_PAYPASS_INT_DS_SUMMARY_STATUS):					nConvertedTag = TAG_PAYPASS_INT_DS_SUMMARY_STATUS;							break;
	case (TAG_MCW_PAYPASS_INT_DSVN_TERM):							nConvertedTag = TAG_PAYPASS_INT_DSVN_TERM;									break;
	case (TAG_MCW_PAYPASS_POST_GENAC_PUT_DATA_STATUS):				nConvertedTag = TAG_PAYPASS_POST_GENAC_PUT_DATA_STATUS;						break;
	case (TAG_MCW_PAYPASS_PRE_GENAC_PUT_DATA_STATUS):				nConvertedTag = TAG_PAYPASS_PRE_GENAC_PUT_DATA_STATUS;						break;
	case (TAG_MCW_PAYPASS_INT_DS_AC_TYPE):							nConvertedTag = TAG_PAYPASS_INT_DS_AC_TYPE;									break;
	case (TAG_MCW_PAYPASS_INT_DS_IDS_STATUS):						nConvertedTag = TAG_PAYPASS_INT_DS_IDS_STATUS;								break;
	case (TAG_MCW_PAYPASS_DS_PROCEED_TO_FIRST_WRITE):				nConvertedTag = TAG_PAYPASS_DS_PROCEED_TO_FIRST_WRITE;						break;
	case (TAG_MCW_PAYPASS_TIME_OUT_VALUE):							nConvertedTag = TAG_PAYPASS_TIME_OUT_VALUE;									break;
	case (TAG_MCW_PAYPASS_CONSTRUCTED_DRDOL_VALUE):					nConvertedTag = TAG_PAYPASS_CONSTRUCTED_DRDOL_VALUE;						break;
	case (TAG_MCW_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS):		nConvertedTag = TAG_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS;				break;
	case (TAG_MCW_PAYPASS_MAX_LIFETIME_OF_TORN_TXN_LOG_RECORD):		nConvertedTag = TAG_PAYPASS_MAX_LIFETIME_OF_TORN_TXN_LOG_RECORD;			break;
	case (TAG_MCW_PAYPASS_DATA_RECORD):								nConvertedTag = TAG_PAYPASS_DATA_RECORD;									break;
	case (TAG_MCW_PAYPASS_DISCRETIONARY_DATA):						nConvertedTag = TAG_PAYPASS_DISCRETIONARY_DATA;								break;
	case (TAG_MCW_PAYPASS_TORN_RECORD):								nConvertedTag = TAG_PAYPASS_TORN_RECORD;									break;
	case (TAG_MCW_PAYPASS_DS_TAGS_TO_READ):							nConvertedTag = TAG_PAYPASS_DS_TAGS_TO_READ;								break;
	case (TAG_MCW_PAYPASS_DS_TAGS_TO_WRITE_AFTER_GENAC):			nConvertedTag = TAG_PAYPASS_DS_TAGS_TO_WRITE_AFTER_GENAC;					break;
	case (TAG_MCW_PAYPASS_DS_TAGS_TO_WRITE_BEFORE_GENAC):			nConvertedTag = TAG_PAYPASS_DS_TAGS_TO_WRITE_BEFORE_GENAC;					break;
	case (TAG_MCW_PAYPASS_DS_DATA_TO_SEND):							nConvertedTag = TAG_PAYPASS_DS_DATA_TO_SEND;								break;
	case (TAG_MCW_PAYPASS_INT_DS_DATA_NEEDED):						nConvertedTag = TAG_PAYPASS_INT_DS_DATA_NEEDED;								break;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// No correspondance
	default:
		nConvertedTag = nTagToConvert;
		break;
	}

	return (nConvertedTag);
}



//! \brief Get next tag in the exchange structure.
//! \param[in,out] pStruct Structure to be used.
//! \param[in,out] pPosition Indicates the position \a pStruct buffer from which next tag is to be found.
//! \param[out] pReadTag Read tag.
//! \param[out] pReadLength Read length.
//! \param[out] pReadValue Read value.
//! \return
//! <table><tr><th>Value</th><th>Description</th></tr>
//! <tr><td>\ref ??STATUS_SHARED_EXCHANGE_OK</td><td>Tag correctly found.</td></tr>
//! <tr><td>\ref ??STATUS_SHARED_EXCHANGE_END</td><td>There is no more tag to read.</td></tr>
//! <tr><td>\ref ??STATUS_SHARED_EXCHANGE_ERROR</td><td>An internal error occurred.</td></tr>
//! </table>
static int __ClessSample_DataExchange_GetNext (T_SHARED_DATA_STRUCT * pStruct, int * pPosition, unsigned long * pReadTag, unsigned long * pReadLength, const unsigned char ** pReadValue)
{
	T_BER_TLV_DECODE_STRUCT tBerTlvStruct;
	int nResult;
	int nPosition;
	int nReadBytes;

	if (*pPosition == SHARED_EXCHANGE_POSITION_NULL)
		nPosition = 0;
	else
		nPosition = *pPosition;
												  
	GTL_BerTlvDecode_Init (&tBerTlvStruct, (((unsigned char *) (pStruct->nPtrData )) + nPosition), (pStruct->ulDataLength - nPosition));

	nResult = ClessSample_DataExchange_ParseTlv (&tBerTlvStruct, pReadTag, pReadLength, pReadValue, &nReadBytes);

	switch (nResult)
	{
	case (STATUS_BER_TLV_OK) : 
		nResult = STATUS_SHARED_EXCHANGE_OK; 
		nPosition += nReadBytes;
		*pPosition = nPosition;
		break;
	case (STATUS_BER_TLV_END):
		nResult = STATUS_SHARED_EXCHANGE_END;
		break;
	default:
		nResult = STATUS_SHARED_EXCHANGE_ERROR;
		break;
	}

	return (nResult);
}

//! \brief Parse the next TLV from the BER-TLV structure.
int ClessSample_DataExchange_ParseTlv (T_BER_TLV_DECODE_STRUCT * pBerTlvStruct, BER_TLV_TAG * pReadTag, BER_TLV_LENGTH * pReadLength, BER_TLV_VALUE * pReadValue, int * pBytesRead)
{
	int nResult;
	int nTagLength = 0;
	int nLengthLength = 0;

	*pReadTag = 0;
	*pReadLength = 0;

	// Decode the tag
	nResult = __ClessSample_DataExchange_ParseTag (pBerTlvStruct, pReadTag, &nTagLength);

	if (nResult == STATUS_BER_TLV_OK)
	{
		nResult = GTL_BerTlvDecode_ParseLength (pBerTlvStruct, pReadLength, &nLengthLength);

		if (nResult == STATUS_BER_TLV_OK)
		{
			nResult = GTL_BerTlvDecode_ParseValue (pBerTlvStruct, *pReadLength, pReadValue);
		}
		else
		{
			// if the TLV structure is only a tag (no length) - ignore the remaining checks as GTL functions fail on zero length tag checks
			if (((unsigned int)nTagLength == pBerTlvStruct->nLength) && ((unsigned int)nTagLength == pBerTlvStruct->nIndex))
			{
				nResult = STATUS_BER_TLV_OK;
			}
			else
			{
				if (nResult == STATUS_BER_TLV_END)
					nResult = STATUS_BER_TLV_BAD_ENCODING; // Length cannot be read => BerTlv encoding error
			}
		}
	}

	if (nResult != STATUS_BER_TLV_OK)
	{
		*pReadTag = 0;
		*pReadLength = 0;
	}

	if (pBytesRead != NULL)
		*pBytesRead = nTagLength + nLengthLength + *pReadLength;

	return (nResult);
}

//! \brief Parse the next tag in the BER-TLV structure.
static int __ClessSample_DataExchange_ParseTag (T_BER_TLV_DECODE_STRUCT * pBerTlvStruct, BER_TLV_TAG * pReadTag, int * pBytesRead)
{
	int nResult;
	int nConsumed;

	*pReadTag = 0;
	
	if (pBytesRead != NULL)
		*pBytesRead = 0;

	// pading bytes automaticly managed by GTL_BerTlvDecodeLow_DecodeTag()
	nConsumed = __ClessSample_DataExchange_DecodeTag (pReadTag, &(pBerTlvStruct->pBerTlvData[pBerTlvStruct->nIndex]), (pBerTlvStruct->nLength - pBerTlvStruct->nIndex));

	switch (nConsumed)
	{
	  case 0:
		nResult = STATUS_BER_TLV_END;
		break;
	  case -1:
		nResult = STATUS_BER_TLV_BAD_ENCODING;
		break;
	  case -2:
		nResult = STATUS_BER_TLV_TAG_TOO_LONG;
		break;
	  default:
		nResult = STATUS_BER_TLV_OK;
		if (pBytesRead != NULL)
			*pBytesRead = nConsumed;

		// Update structure index
		pBerTlvStruct->nIndex += nConsumed;
		break;
	}

	return (nResult);
}

//! \brief	Decode a BER-TLV tag from a buffer.							
//! \param[out] pTag Decoded tag.
//! \param[in] pBuffer Buffer that contains the encoded tag.
//! \param[in] nBufferSize size of the buffer \a pBuffer.
//! \return	
//!	- > 0 : The number of bytes read. The tag is correctly read.
//!	- = 0 : There is no tag (no more tag).
//!	- = -1 : The tag is not correctly encoded (missing bytes). 
//!	- = -2 : The tag is incorrectly read (more than 4 bytes, ...).

static int __ClessSample_DataExchange_DecodeTag (BER_TLV_TAG* pTag, const void* pBuffer, int nBufferSize)
{
	int nConsumed;
	const unsigned char* pBuf;
	unsigned char Byte;
	int nNumBytes;

	*pTag = 0;
	nConsumed = 0;
	pBuf = pBuffer;

	// Skip the pading bytes
	nConsumed = __ClessSample_DataExchange_SkipPadding (pBuffer, nBufferSize);

	if (nConsumed < nBufferSize)
	{
		// Read the first byte
		Byte = pBuf[nConsumed];
		nConsumed++;

		*pTag = (BER_TLV_TAG)Byte;

		if ((Byte & BER_TLV_TAG_SEE_NEXT_BYTES) == BER_TLV_TAG_SEE_NEXT_BYTES)
		{
			if (nConsumed < nBufferSize)
			{
				// Read the next bytes
				nNumBytes = 1;

				do
				{
					Byte = pBuf[nConsumed];
					nConsumed++;
					*pTag = (*pTag << 8) | Byte;
					nNumBytes++;
				} while((nConsumed < nBufferSize) && ((Byte & BER_TLV_TAG_ANOTHER_BYTE) == BER_TLV_TAG_ANOTHER_BYTE));

				if ((Byte & BER_TLV_TAG_ANOTHER_BYTE) == BER_TLV_TAG_ANOTHER_BYTE)
				{
					// Some bytes are missing
					nConsumed = -1;
					*pTag = 0;
				}
				else if (nNumBytes > 4)
				{
					// The tag is coded on more than 4 bytes
					nConsumed = -2;
					*pTag = 0;
				}
			}
			else
			{
				// Some bytes are missing
				nConsumed = -1;
			}
		}
	}
	else
	{
		// No more tag in the buffer
		nConsumed = 0;
	}

	return nConsumed;
}

//! \brief	Skip the padding bytes if present.
//! \brief	According to SU69, 0x00 is the only valid padding byte.
//! \param[in] pBuffer Buffer that contains the encoded tags.
//! \param[in] nBufferSize size of the buffer \a pBuffer.
//! \return	The number of bytes skipped.

static int __ClessSample_DataExchange_SkipPadding (const void* pBuffer, int nBufferSize)
{
	int nConsumed;
	unsigned char Byte;
	const unsigned char* pBuf;

	nConsumed = 0;
	pBuf = pBuffer;
	if (nBufferSize > 0)
	{
		// Skip the padding bytes (00)
		Byte = pBuf[nConsumed];
		while((Byte == 0x00) && (nConsumed < nBufferSize))
		{
			nConsumed++;
			Byte = pBuf[nConsumed];
		}
	}
	// Else the buffer is empty

	return nConsumed;
}


//! \brief Set to indicate if a matching DEK Signal was returned.
//! \param[in] bDEKMatching returned DEK Signal is matching or not.

void ClessSample_DataExchange_SetDEKSignalStatus (const int bDEKMatching)
{
	gDETSignalStatus = bDEKMatching;
}


//! \brief Check if Data Exchange is in progress.
//! \return TRUE DEK Signal matched, FALSE DEK Signal did not match.

int ClessSample_DataExchange_GetDEKSignalStatus (void)
{
	return (gDETSignalStatus);
}


//! \brief Check if the MCW DOL contains any MCW tags, if so translate then to
//! \brief Ingenico tags and adjust the length. Ensure DOL tags are zero padded.
//! \param[in] pValue data of the DOL tag in the DET Signal.
//! \param[in] ulLength Length of \a pDETValue.
//! \param[out] pValueModified data of the DOL tag in the DET Signal modified to Ingenico format.
//! \param[out] ulLength Length of \a pDETValueModified.
//! \return TRUE DOL parse correctly, FALSE DOL did not parse correctly.

static int __ClessSample_DataExchange_CheckMCWDOL (unsigned long ulLength, const unsigned char * pValue, unsigned long * ulLengthModified, unsigned char * pValueModified, unsigned long ulModifiedSize)
{
	int nResult;
	int nTagLength = 0;
	BER_TLV_TAG ulReadTag, ulTag;
	T_BER_TLV_DECODE_STRUCT TlvStruct;
	BER_TLV_LENGTH ReadLength=0;

	*ulLengthModified = 0;

	if ((pValue == NULL) || (pValueModified == NULL)) //Input parameters control
		return (FALSE);

	memset (pValueModified, 0x00, ulModifiedSize);

	// initialise the local structure
	GTL_BerTlvDecode_Init (&TlvStruct, pValue, ulLength);

	do
	{
		// Get the next tag in the DOL
		nResult = __ClessSample_DataExchange_ParseTag (&TlvStruct, &ulReadTag, &nTagLength);

		// Check there is enough space to continue
		if ((ReadLength+5) > ulModifiedSize)
		{
			GTL_Traces_TraceDebug("__ClessSample_DataExchange_CheckMCWDOL : Not enough space in output buffer pValueModified");
			return (FALSE);
		}

		if (nResult == STATUS_BER_TLV_OK)
		{
			// Initialise the destination tag
			ulTag = ulReadTag;

			// check if the equivilant MCW tag is present 
			ulTag = ClessSample_DataExchange_McwTagConversion (ulReadTag);

			// check if tag was converted MCW to Ingenico, if so, increment the overall length
			if (ulTag != ulReadTag)
			{
				// Tag was converted from 3 byte MCW tag to 4 byte Ingenico tag
				GTL_Convert_UlToBinNumber (ulTag, &pValueModified[ReadLength], 4);
				ReadLength++;							// MCW tag converted to Ingenico Tag
			}
			else
			{
				// Tag was not converted from 3 byte MCW tag to 4 byte Ingenico tag
				GTL_Convert_UlToBinNumber (ulTag, &pValueModified[ReadLength], nTagLength);
			}

			//Update the overall length of the modified buffer
			ReadLength+=nTagLength;

			// Add a 0x00 between DOL tags
			pValueModified[ReadLength]=0x00;
			ReadLength++;
		}

	} while (nResult == STATUS_BER_TLV_OK);

	if ((nResult != STATUS_BER_TLV_OK) && (nResult != STATUS_BER_TLV_END))
	{
		return (FALSE);
	}
	else
	{
		*ulLengthModified = ReadLength;
		return (TRUE);
	}
}

