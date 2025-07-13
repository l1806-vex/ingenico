/**
 * \file	ClessSample_XML.h
 * \brief	This module contains the functions needed for MCW XML parameters management.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2011 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __CLESS_SAMPLE_XML_H__INCLUDED__
#define __CLESS_SAMPLE_XML_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define FORMAT_NODATA		0
#define FORMAT_BINARY		1
#define FORMAT_ASCII		2


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

typedef unsigned int T_DataFormat;


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Set a node in the TLV Tree.
//!	\param[in] tParentTreeNode TLV Tree node on which the new node is added.
//!	\param[in] nDataLength Data length (0 if the node has no data, such as a template for example).
//!	\param[in] pData Data of the node to be created (NULL if the node has no data, such as a template for example).
//!	\param[in] tFormat Format of the node data (no data for templates, binary of ASCII).
//! \return
//!	- \a TRUE if correctly performed.
//!	- \a FALSE if an error occurred.

int ClessSample_XML_SetDataNode (TLV_TREE_NODE * pTreeNode, int nDataLength, unsigned char * pData, T_DataFormat tFormat);



//! \brief Create a node in the TLV Tree.
//!	\param[in] pParentTreeNode TLV Tree node on which the new node is added.
//!	\param[in] nTag Tag of the node to be created.
//!	\param[out] pCreatedTreeNode Node created.
//! \return
//!	- \a TRUE if correctly performed.
//!	- \a FALSE if an error occurred.

int ClessSample_XML_CreateNode (TLV_TREE_NODE * pParentTreeNode, int nTag, TLV_TREE_NODE* pCreatedTreeNode);



//! \brief This function parses an XML document to get the connection link.
//!	\param[in] szFilePath Path of the file to parse.
//!	\param[out] pOutputTree Output TLV Tree containing the full converted XML MCW file.
//!	\param[in] pStartFunction Function pointer to be called when a plot is opened.
//!	\param[in] pEndFunction Function pointer to be called when a plot is closed.
//!	\param[in] pDataFunction Function pointer to be called when a plot contains data.
//!	\param[out] pUseDefaultParameters Output data indicating if the default parameter shall be used or not.

void ClessSample_XML_ConvertXmlToTlvTree (const char* szFilePath, TLV_TREE_NODE *pOutputTree, XMLs_StartElementHandler pStartFunction, XMLs_EndElementHandler pEndFunction, XMLs_CharacterDataHandler pDataFunction, int * pUseDefaultParameters);


#endif //__CLESS_SAMPLE_XML_H__INCLUDED__
