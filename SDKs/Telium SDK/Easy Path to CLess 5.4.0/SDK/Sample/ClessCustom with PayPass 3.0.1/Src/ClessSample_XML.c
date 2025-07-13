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
#include "XMLs.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define HEXCHAR2NIBBLE(ch,d) \
if (ch >= '0' && ch <= '9') d = (unsigned char)(ch - '0'); \
else if (ch >= 'a' && ch <= 'f') d = (unsigned char)((ch - 'a') + 10); \
else if (ch >= 'A' && ch <= 'F') d = (unsigned char)((ch - 'A') + 10); \
else d = 0xFF;

#define NIBBLE2HEXCHAR(d,ch) \
if (d >= 0 && d <= 9) ch = (char)(d + '0'); \
else if (d >= 0x0a && d <= 0x0f) ch = (char)((d - 10)+ 'A'); \
else ch = '?';


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static void __ClessSample_XML_str2hex (char* src, char* des, int len);
static int __ClessSample_XML_CountSpaces (const unsigned char* src, int len);
static int __ClessSample_XML_AsciiToBinary (const unsigned char* pSrc, int nSrcLength, unsigned char* pDest, int nMaxDestLength);
static int __ClessSample_XML_SplitPath (const char* szFilePath, char* pcDisk, unsigned int nSize);
static int __ClessSample_XML_ParseFile (XMLs_PARSER hXml, const char* szFilePath, XMLs_StartElementHandler pStartFunction, XMLs_EndElementHandler pEndFunction, XMLs_CharacterDataHandler pDataFunction, void* pUserData);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Count the space characters in the provided data
//!	\param[in] src Input buffer to be analysed.
//!	\param[in] len Length of \a src.
//! \return The number of space characters in \a src.

static int __ClessSample_XML_CountSpaces (const unsigned char* src, int len)
{
	int nIndex;
	int nCount = 0;

	for (nIndex=0;nIndex<len;nIndex++)
		if (src[nIndex] == ' ')
			nCount++;

	return (nCount);
}



//! \brief Convert a string into an hexadecimal format, and ignore the spce characters.
//!	\param[in] src Input string to be converted.
//!	\param[out] des Output buffer containing the converted string.
//!	\param[in] len Length of \a src.
//! \note We consider that the length of \a des shall be at least (len+1)/2 long.
//!	\note Example of convertion : src = " 12 34 56 AB " implies des = 0x12 0x34 0x56 0xAB

static void __ClessSample_XML_str2hex (char* src, char* des, int len)
{
	unsigned char b;
	unsigned char padLeft;
	int i;
	int nIndex;

	memset(des,0,(len+1)/2);
	padLeft = 1;
	nIndex = 0;

	for (i=0; i<len; i++)
	{
		if (src[i] != ' ')
		{
			HEXCHAR2NIBBLE(src[i],b);
			des [nIndex >> 1] |=  b << ((nIndex & 1) == 1 ? 0 : 4);
			nIndex++;
		}
	}
}



//! \brief Convert an ASCII buffer into a binary one.
//!	\param[in] pSrc Source ASCII buffer to be converted.
//!	\param[in] nSrcLength Length of \a pSrc.
//!	\param[out] pDest Output buffer filled with the converted buffer.
//!	\param[in] nMaxDestLength Maximum length of \a pDest.
//!	\return The size of bytes contained in pDest.

static int __ClessSample_XML_AsciiToBinary (const unsigned char* pSrc, int nSrcLength, unsigned char* pDest, int nMaxDestLength)
{
	int nLength;

	if (nSrcLength > nMaxDestLength * 2)
	{
		// Truncate
		nSrcLength = nMaxDestLength * 2;
	}

	// Convert to binary
	__ClessSample_XML_str2hex((char*)pSrc, (char*)pDest, nSrcLength);
	nLength = ((nSrcLength - __ClessSample_XML_CountSpaces (pSrc, nSrcLength) + 1)) / 2;

	return nLength;
}



//! \brief Split a file path to get the disk name.
//!	\param[in] szFilePath Full file path.
//!	\param[out] pcDisk File disk.
//! \param[in] nSize Size of \a szFilePath.
//! \return
//!	- \a (0) if correctly performed.
//!	- \a (-1) if an error occurred.

static int __ClessSample_XML_SplitPath (const char* szFilePath, char* pcDisk, unsigned int nSize)
{
	unsigned int nDiskLength = 0;
	const char*  pcCurrent   = szFilePath;

	int nReturn = -1;

	if( ( pcCurrent != NULL ) && ( pcDisk != NULL ) )
	{
		if( *pcCurrent == '/' )
		{
			do
			{
				nDiskLength++;
				pcCurrent++;
				if( *pcCurrent == '/' )
				{
					break;
				}
			}while( *pcCurrent != '\0' );

			if( *pcCurrent != '\0' )
			{
				if( nSize > nDiskLength )
				{
					memcpy( pcDisk, szFilePath, nDiskLength );
					pcDisk[nDiskLength] = '\0';

					nReturn = 0;
				}
			}
		}
	}
	return nReturn;
}



//! \brief Parse an XML file.
//!	\param[in] hXml XML parser.
//!	\param[in] szFilePath Path of the file to be parsed.
//!	\param[in] pStartFunction Function pointer to be called when a plot is opened.
//!	\param[in] pEndFunction Function pointer to be called when a plot is closed.
//!	\param[in] pDataFunction Function pointer to be called when a plot contains data.
//!	\param[in] pUserData User data.
//!	\return
//!	- \a XMLS_BAD_PARAMETER if \a szFilePath is NULL.
//!	- \a XMLS_INVALID_HANDLE if \a hXml is NULL.
//!	- \a XMLS_BAD_PARAMETER if \a szFilePath has an incorrect format. 
//!	- \a XMLS_ERROR_FILE_ACCESS if an error occurred when trying to access the desired file.
//!	- \a XMLS_OK if all succeeded.
//!	- \a XMLS_ERROR_PARSING if a parsing error occurred.
//!	- \a XMLS_ERROR_TAG_MISMATCH
//!	- \a XMLS_ERROR_SEVERAL_ROOT_TAGS

static int __ClessSample_XML_ParseFile (XMLs_PARSER hXml, const char* szFilePath, XMLs_StartElementHandler pStartFunction, XMLs_EndElementHandler pEndFunction, XMLs_CharacterDataHandler pDataFunction, void* pUserData)
{
	unsigned int nMode;
	S_FS_FILE*   hXmlFile = NULL;
	char         szDisk[32];
	char*        pcDataBuffer;
	unsigned int nDataLength;
	int          nReturn = (-6); // XMLS_ERROR_FILE_ACCESS;

	if (szFilePath == NULL)
	{
		return (XMLS_BAD_PARAMETER);
	}

	if (hXml == NULL)
	{
		return (XMLS_INVALID_HANDLE);
	}

	if (__ClessSample_XML_SplitPath (szFilePath, szDisk, sizeof(szDisk)) == -1)
	{
		return (XMLS_BAD_PARAMETER);
	}

	// Mount the disk but don't unmount it !
	// It might be already mounted by the application.
	if (FS_mount((char*)szDisk, &nMode) == FS_OK)
	{
		hXmlFile = FS_open ((char*)szFilePath, "r");

		if (hXmlFile != NULL)
		{
			// Allocate the buffer for the data.
			nDataLength  = FS_length (hXmlFile);

			pcDataBuffer = umalloc (nDataLength);

			if( pcDataBuffer != NULL )
			{
				// Read all the file.
				FS_read (pcDataBuffer, 1, nDataLength, hXmlFile);

				// At last start the XML parsing !
				nReturn = XMLs_Parse (hXml, pcDataBuffer, nDataLength,
					                  pStartFunction, pEndFunction, pDataFunction, pUserData);
				
				// Release the data buffer.
				ufree (pcDataBuffer);
			}
			else
			{
				nReturn = (-7); // XMLS_ERROR_MEMORY
			}

			FS_close (hXmlFile);
		}
	}

	return (nReturn);
}



//! \brief Set a node in the TLV Tree.
//!	\param[in] tParentTreeNode TLV Tree node on which the new node is added.
//!	\param[in] nDataLength Data length (0 if the node has no data, such as a template for example).
//!	\param[in] pData Data of the node to be created (NULL if the node has no data, such as a template for example).
//!	\param[in] tFormat Format of the node data (no data for templates, binary of ASCII).
//! \return
//!	- \a TRUE if correctly performed.
//!	- \a FALSE if an error occurred.

int ClessSample_XML_SetDataNode (TLV_TREE_NODE * pTreeNode, int nDataLength, unsigned char * pData, T_DataFormat tFormat)
{
	int nResult = TRUE;
	int nConvertedLength;
	unsigned char * pTemp = NULL;

	if (pTreeNode != NULL)
	{
		// Allocate the temporary buffer for convertion
		switch (tFormat)
		{
		case (FORMAT_NODATA):
			nConvertedLength = 0;
			break;
		case (FORMAT_ASCII):
			nConvertedLength = nDataLength;
			break;
		case (FORMAT_BINARY):
		default:
			nConvertedLength = ((nDataLength - __ClessSample_XML_CountSpaces (pData, nDataLength) + 1) / 2);
			break;
		}

		if (nConvertedLength > 0)
			pTemp = umalloc(nDataLength);

		if (pTemp != NULL)
		{
			// Initialise the buffer
			memset (pTemp, 0, nDataLength);

			switch (tFormat)
			{
			case (FORMAT_ASCII):
				memcpy (pTemp, pData, nConvertedLength);				
				break;
			case (FORMAT_BINARY):
				__ClessSample_XML_AsciiToBinary (pData, nDataLength, pTemp, nDataLength);
				break;
			case (FORMAT_NODATA):
			default:
				break;
			}
		}

		// Update the node
		if (TlvTree_SetData (*pTreeNode, pTemp, nConvertedLength) != TLV_TREE_OK)
		{
			// An error occurred when setting the node data
			GTL_Traces_TraceDebug ("__ClessSample_XML_SetDataNode : An error occurred when setting the node data");
			nResult = FALSE;
		}
	}
	else
	{
		GTL_Traces_TraceDebug ("__ClessSample_XML_SetDataNode : pTreeNode (%p) is NULL", pTreeNode);
		nResult = FALSE;
	}

	// Free the allocated buffer
	if (pTemp != NULL)
		ufree (pTemp);

	return (nResult);
}



//! \brief Create a node in the TLV Tree.
//!	\param[in] pParentTreeNode TLV Tree node on which the new node is added.
//!	\param[in] nTag Tag of the node to be created.
//!	\param[out] pCreatedTreeNode Node created.
//! \return
//!	- \a TRUE if correctly performed.
//!	- \a FALSE if an error occurred.

int ClessSample_XML_CreateNode (TLV_TREE_NODE * pParentTreeNode, int nTag, TLV_TREE_NODE* pCreatedTreeNode)
{
	int nResult = TRUE;
	TLV_TREE_NODE tCreatedNode = NULL;

	if ((pParentTreeNode != NULL) && (pCreatedTreeNode != NULL))
	{
		// Init output data
		*pCreatedTreeNode = NULL;

		// Create the new node
		tCreatedNode = TlvTree_AddChild (*pParentTreeNode, nTag, NULL, 0);

		if (tCreatedNode != NULL)
		{
			*pCreatedTreeNode = tCreatedNode;
		}
		else
		{
			GTL_Traces_TraceDebug ("__ClessSample_XML_CreateNode : an error occurred when creating the new node");
			nResult = FALSE;
		}
	}
	else
	{
		GTL_Traces_TraceDebug ("__ClessSample_XML_CreateNode : pParentTreeNode (%p) or pCreatedTreeNode (%p) is NULL", pParentTreeNode, pCreatedTreeNode);
		nResult = FALSE;
	}

	return (nResult);
}



//! \brief This function parses an XML document to get the connection link.
//!	\param[in] szFilePath Path of the file to parse.
//!	\param[out] pOutputTree Output TLV Tree containing the full converted XML MCW file.
//!	\param[in] pStartFunction Function pointer to be called when a plot is opened.
//!	\param[in] pEndFunction Function pointer to be called when a plot is closed.
//!	\param[in] pDataFunction Function pointer to be called when a plot contains data.
//!	\param[out] pUseDefaultParameters Output data indicating if the default parameter shall be used or not.

void ClessSample_XML_ConvertXmlToTlvTree (const char* szFilePath, TLV_TREE_NODE *pOutputTree, XMLs_StartElementHandler pStartFunction, XMLs_EndElementHandler pEndFunction, XMLs_CharacterDataHandler pDataFunction, int * pUseDefaultParameters)
{
	XMLs_PARSER hParser;
	XMLs_ATTRIBUTE pAttributes[10]; // Deal with a maximum of 10 attributes per starting tag
	int nStatus;
	int bUseDefaultConfiguration = TRUE;
	TLV_TREE_NODE hTempNode;

	if (pUseDefaultParameters != NULL)
		*pUseDefaultParameters = TRUE;

	if (pOutputTree != NULL)
	{
		// Init output data
		*pOutputTree = NULL;

		// Create the parser
		hParser = XMLs_ParserOpen (pAttributes, 10);

		if (hParser != NULL)
		{
			// Create the root node
			*pOutputTree = TlvTree_New(0);

			if (*pOutputTree != NULL)
			{
				// Initialise the current node (root node in this case)
				hTempNode = *pOutputTree;

				// Parse the data
				nStatus = __ClessSample_XML_ParseFile (hParser,
					szFilePath,     // File path to parse
					pStartFunction,    // Call-back on start tag
					pEndFunction,    // Call-back on end tag
					pDataFunction, // Call-back on data
					hTempNode);	// User Data

				if(nStatus == XMLS_OK)
					bUseDefaultConfiguration = FALSE;

				if (pUseDefaultParameters != NULL)
					*pUseDefaultParameters = FALSE;
			}
			else
			{
				// An error occurred when creating the root node
				GTL_Traces_TraceDebug ("ClessSample_XML_ConvertXmlToTlvTree : An error occurred when creating the root node");
			}

			// Release the parser
			XMLs_ParserClose (hParser);
		}

		if (bUseDefaultConfiguration)
		{
			// No XML File
			GTL_Traces_TraceDebug ("ClessSample_XML_ConvertXmlToTlvTree : USE DEFAULT CONF");

			TlvTree_Release (*pOutputTree);
			*pOutputTree = NULL;
		}
	}
}
