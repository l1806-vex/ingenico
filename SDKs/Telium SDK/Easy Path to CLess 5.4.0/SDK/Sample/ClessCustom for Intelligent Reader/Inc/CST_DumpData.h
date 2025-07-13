/**
 * \file	CST_DumpData.h
 * \brief 	Module that manages the data dump on a ticket.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __CST_DUMPDATA_H__INCLUDED__
#define __CST_DUMPDATA_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define CST_OUTPUT_NONE						0		/*!< No output. */
#define CST_OUTPUT_PRINTER					1		/*!< Printer output device. */
#define CST_OUTPUT_COM0						2		/*!< COM0 output device. */
#define CST_OUTPUT_USB						3		/*!< USB output device. */
#define CST_OUTPUT_TRACE			 		4		/*!< Trace output device. */


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Initialise the default output mode (printer if a printer is present, none else).

void CST_DumpData_InitOutput (void);



//! \brief Set the output driver identifier.
//! \param[in] ucOutputId identifier of the output
//!		- \ref CST_OUTPUT_NONE if no output is used.
//!		- \ref CST_OUTPUT_PRINTER if Printer is used.
//!		- \ref CST_OUTPUT_COM0 if COM0 is used.
//!		- \ref CST_OUTPUT_USB if USB is used.
//!		- \ref CST_OUTPUT_TRACE if Trace is used.

void CST_DumpData_SetOutputId (unsigned char ucOutputId);



//!	\brief Get the output driver identifier.
//!	\return	the selected output driver id :
//!	- \ref CST_OUTPUT_NONE if no output is used.
//!	- \ref CST_OUTPUT_PRINTER if Printer is used.
//!	- \ref CST_OUTPUT_COM0 if COM0 is used.
//!	- \ref CST_OUTPUT_USB if USB is used.
//!	- \ref CST_OUTPUT_TRACE if Trace is used.

unsigned char CST_DumpData_GetOutputId (void);



//! \brief Print a "\n" or a "\r" according the output driver idenifier.

void CST_DumpData_NewLine(void);



//! \brief Open the output driver.
//! \return
//!	- \ref TRUE if correctly opened, 
//!	- \ref FALSE else.
//! \remark	If the driver is not correctly opened, the dumping is not performed even if requested.

int CST_DumpData_OpenOutputDriver (void);



//! \brief Close the output driver.

void CST_DumpData_CloseOutputDriver (void);



//! \brief Dump data (string formated) on the correct output.
//! \param[in] pString Data to be dumped

void CST_DumpData (const char* pString, ...)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
	__attribute__((format(printf, 1, 2)));
#else
	;
#endif



//! \brief Dump a shared buffer content.
//! \param[in] pDataStruct Shared buffer to be dumped.
//! \param[in] nIndent Indentation for recursive calls. Shall be set to 0.

void CST_DumpData_DumpSharedBuffer (T_SHARED_DATA_STRUCT * pDataStruct, const int nIndent);



//! \brief Dump a shared exchange buffer content with a title.
//!	\param[in] pDataStruct Shared exchange buffer to be dumped.
//!	\param[in] pTitle Title of the dump.

void CST_DumpData_DumpSharedBufferWithTitle (T_SHARED_DATA_STRUCT * pDataStruct, const char * pTitle);



//! \brief Dump data ocntained in a TLV Tree node
//! \param[in] pLabel Label to be printed before the node data.
//! \param[in] TlvTreeNodeToDump TLV Tree node to be dump.
//! \note Label is printed in bold (if printer is used).
//! \note Data are printed in smal character using the following format T:00009F06 L:07 V:A00000000991010
//! \note Indentation is not perfromed on constructed tags.

void CST_DumpData_DumpTlvTreeNodeWithTitle (const char * pLabel, TLV_TREE_NODE TlvTreeNodeToDump);



//! \brief Dump data ocntained in a TLV Tree node
//! \param[in] pLabel Label to be printed (bold printed).

void CST_DumpData_Title (const char * pLabel);

#endif // __CST_DUMPDATA_H__INCLUDED__
