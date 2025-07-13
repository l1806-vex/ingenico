/**
 * \file	ClessSample_DumpData.h
 * \brief	To dump information on desired output device (display, printer, USB or serial output devices).
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

#ifndef __CLESS_SAMPLE_DUMPDATA_H__INCLUDED__
#define __CLESS_SAMPLE_DUMPDATA_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


//! \brief Output device types
#define CUSTOM_OUTPUT_NONE				 0		/*!< No selected devide (dump functions have no effect). */
#define CUSTOM_OUTPUT_PRINTER			 1		/*!< Printer output device. */
#define CUSTOM_OUTPUT_COM0				 2		/*!< COM0 output device. */
#define CUSTOM_OUTPUT_USB				 3		/*!< USB output device. */
#define CUSTOM_OUTPUT_TRACE			 	 4		/*!< Trace output device. */


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Initialise the default output mode (printer if a printer is present, none else).

void ClessSample_DumpData_InitOutput (void);



//! \brief Get the output driver handle.
//! \return	The handle of the output driver

FILE * ClessSample_DumpData_DumpGetOutputHandle (void);



//! \brief Set the current driver type id.
//! \param[in] ucOutputId output driver id to select (\a CUSTOM_OUTPUT_COM0, \a CUSTOM_OUTPUT_PRINTER, \a CUSTOM_OUTPUT_NONE, \a CUSTOM_OUTPUT_USB, \a CUSTOM_OUTPUT_TRACE).

void ClessSample_DumpData_DumpSetOutputId (unsigned char ucOutputId);



//! \brief return output driver id.
//! \return The output driver type
//! 	- \a CUSTOM_OUTPUT_NONE No selected devide (dump functions have no effect).
//! 	- \a CUSTOM_OUTPUT_PRINTER Printer output device.
//! 	- \a CUSTOM_OUTPUT_COM0 COM0 output device.
//! 	- \a CUSTOM_OUTPUT_USB USB output device.
//! 	- \a CUSTOM_OUTPUT_TRACE Trace output device.

unsigned char ClessSample_DumpData_DumpGetOutputId (void);



//! \brief Output line feed : "\n" or a "\r" according the output driver idenifier.

void ClessSample_DumpData_DumpNewLine(void);



//! \brief Open current Output driver.
//! \return	
//!		- \ref TRUE if correctly opened.
//!		- \ref FALSE else.
//! \note If the driver is not correctly opened, the dumping is not performed even if requested.

int ClessSample_DumpData_DumpOpenOutputDriver (void);



//! \brief Close current Output driver.

void ClessSample_DumpData_DumpCloseOutputDriver (void);



//! \brief Dump data on current output.
//!	\param[in] pString String to be dumped.
//! \param[in] ... parameters to trace

void ClessSample_DumpData (const char* pString, ...)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
	__attribute__((format(printf, 1, 2)));
#else
	;
#endif

	
	
//! \brief Dump a shared exchange buffer content (each constructed tag is dumped with a indentation).
//!	\param[in] pDataStruct Shared exchange buffer to be dumped.
//!	\param[in] nIndent Shall be set to 0 at the first call (for indentation purpose).

void ClessSample_DumpData_DumpSharedBuffer (T_SHARED_DATA_STRUCT * pDataStruct, const int nIndent);



//! \brief Dump a shared exchange buffer content with a title.
//!	\param[in] pDataStruct Shared exchange buffer to be dumped.
//!	\param[in] pTitle Title of the dump.

void ClessSample_DumpData_DumpSharedBufferWithTitle (T_SHARED_DATA_STRUCT * pDataStruct, const char * pTitle);



//! \brief Dump data ocntained in a TLV Tree node
//! \param[in] pLabel Label to be printed before the node data.
//! \param[in] TlvTreeNodeToDump TLV Tree node to be dump.
//! \note Label is printed in bold (if printer is used).
//! \note Data are printed in smal character using the following format T:00009F06 L:07 V:A00000000991010
//! \note Indentation is not perfromed on constructed tags.

void ClessSample_DumpData_DumpTlvTreeNodeWithTitle (const char * pLabel, TLV_TREE_NODE TlvTreeNodeToDump);



//! \brief Dump data ocntained in a TLV Tree node
//! \param[in] pLabel Label to be printed (bold printed).

void ClessSample_DumpData_DumpTitle (const char * pLabel);



#endif // __CLESS_SAMPLE_DUMPDATA_H__INCLUDED__
