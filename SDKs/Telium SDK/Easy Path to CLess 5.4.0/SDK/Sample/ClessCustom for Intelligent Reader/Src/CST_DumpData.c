/**
 * \file	CST_DumpData.c
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

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "CST_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static FILE * gs_hOuputHandle;
static unsigned char gs_ucOutputId = CST_OUTPUT_PRINTER;


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static FILE * __CST_DumpData_DumpGetOutputHandle (void);

extern int IsPrinter(void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Initialise the default output mode (printer if a printer is present, none else).

void CST_DumpData_InitOutput (void)
{
	gs_ucOutputId = ((IsPrinter()) ? CST_OUTPUT_PRINTER : CST_OUTPUT_NONE);
}



//! \brief Get the output driver handle.
//! \return	The handle of the output driver (\a NULL if not opened).

static FILE * __CST_DumpData_DumpGetOutputHandle (void)
{
	return (gs_hOuputHandle);
}



//!	\brief Get the output driver identifier.
//!	\return	the selected output driver id :
//!	- \ref CST_OUTPUT_NONE if no output is used.
//!	- \ref CST_OUTPUT_PRINTER if Printer is used.
//!	- \ref CST_OUTPUT_COM0 if COM0 is used.
//!	- \ref CST_OUTPUT_USB if USB is used.
//!	- \ref CST_OUTPUT_TRACE if Trace is used.

unsigned char CST_DumpData_GetOutputId (void)
{
	return (gs_ucOutputId);
}



//! \brief Set the output driver identifier.
//! \param[in] ucOutputId identifier of the output
//!		- \ref CST_OUTPUT_NONE if no output is used.
//!		- \ref CST_OUTPUT_PRINTER if Printer is used.
//!		- \ref CST_OUTPUT_COM0 if COM0 is used.
//!		- \ref CST_OUTPUT_USB if USB is used.
//!		- \ref CST_OUTPUT_TRACE if Trace is used.

void CST_DumpData_SetOutputId (unsigned char ucOutputId)
{
	gs_ucOutputId = ucOutputId;
}



//! \brief Print a "\n" or a "\r" according the output driver idenifier.

void CST_DumpData_NewLine(void)
{
	switch (CST_DumpData_GetOutputId())
	{
		// =========================================
		case (CST_OUTPUT_COM0):
		case (CST_OUTPUT_USB):
			CST_DumpData ("\r");
			break;

		// =========================================
		case (CST_OUTPUT_PRINTER):
			CST_DumpData ("\n");
			ttestall(PRINTER, 0);
			break;

		// =========================================
		default: // Nothing
			break;
	}
}



//! \brief Open the output driver.
//! \return
//!	- \ref TRUE if correctly opened, 
//!	- \ref FALSE else.
//! \remark	If the driver is not correctly opened, the dumping is not performed even if requested.

int CST_DumpData_OpenOutputDriver (void)
{
	if (gs_hOuputHandle != NULL)
	{
		fclose (gs_hOuputHandle);
		gs_hOuputHandle = NULL;
	}

	switch (CST_DumpData_GetOutputId())
	{
	case (CST_OUTPUT_PRINTER):
		gs_hOuputHandle = fopen("PRINTER", "w");
		break;

	case (CST_OUTPUT_COM0):
		gs_hOuputHandle = fopen("COM0", "rw*");
		format("COM0", 9600, 8, 1, NO_PARITY, EVEN, FALSE);
		break;

	case (CST_OUTPUT_USB):
		gs_hOuputHandle = fopen("COM5", "rw*");
		format("COM5", 115200, 8, 1, NO_PARITY, EVEN, FALSE);
		break;

	default:
		break;
	}

	return (__CST_DumpData_DumpGetOutputHandle() != NULL);
}



//! \brief Close the output driver.

void CST_DumpData_CloseOutputDriver (void)
{
	unsigned long ulEvent;
	unsigned char Status;
	
	if (gs_hOuputHandle != NULL)
	{
		switch (CST_DumpData_GetOutputId())
		{
		case (CST_OUTPUT_PRINTER):	ulEvent = PRINTER;	break;
		case (CST_OUTPUT_COM0): 	ulEvent = COM0;		break;
		case (CST_OUTPUT_USB):		ulEvent = COM5;		break;
		default:					ulEvent = 0;		break;
		}

		// Wait until all data are sent
		mask_event(gs_hOuputHandle, COM_SEND_EMPTY);
		status(gs_hOuputHandle, &Status);
		while((Status & COM_SEND_EMPTY) == 0)
		{
			if (ulEvent != 0)
				ttestall(ulEvent, 500);
			else ttestall(0, 10);
			status(gs_hOuputHandle, &Status);
		}
		mask_event(gs_hOuputHandle, COM_REC_NOT_EMPTY);
	
		fclose(gs_hOuputHandle);
		gs_hOuputHandle = NULL;
	}
}



//! \brief Dump data (string formated) on the correct output.
//! \param[in] pString Data to be dumped

void CST_DumpData (const char* pString, ...)
{
	char String[256];
	int nLength;
	va_list Params;

	va_start(Params, pString);
#if (defined(__GNUC__) && !defined(_SIMULPC_))
	nLength = vsprintf(String, pString, &Params);
#else
	nLength = vsprintf(String, pString, Params);
#endif
	
	va_end(Params);

	switch (CST_DumpData_GetOutputId())
	{
		// ================================================================================
		case (CST_OUTPUT_COM0):
		case (CST_OUTPUT_USB):
		case (CST_OUTPUT_PRINTER):
		{
			if (__CST_DumpData_DumpGetOutputHandle() != NULL)
			{
				int i;
				int len;
				i = 0;
				len = strlen(String);
				do
				{
					i += fwrite(String + i, 1, len - i, __CST_DumpData_DumpGetOutputHandle());
					if (i < len)
						ttestall(0,1);
				} while(i < len);
			}
			break;
		}

		// ================================================================================
		default: // Nothing
			break;
	}
}



//! \brief Dump a shared buffer content.
//! \param[in] pDataStruct Shared buffer to be dumped.
//! \param[in] nIndent Indentation for recursive calls. Shall be set to 0.

void CST_DumpData_DumpSharedBuffer (T_SHARED_DATA_STRUCT * pDataStruct, const int nIndent)
{
	int nIndex, nIndex2;
	int nPosition;
	int nResult;
	unsigned long ulReadTag;
	unsigned long ulReadLength;
	unsigned char * pValue;
	unsigned char bDriverOpened, bDriverAlreadyOpened;
	T_SHARED_DATA_STRUCT tTempStruct;
	int bFirstLinePrinted;
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	nResult = STATUS_SHARED_EXCHANGE_OK;
	
	if (__CST_DumpData_DumpGetOutputHandle() == NULL)
	{
		bDriverOpened = CST_DumpData_OpenOutputDriver();
		bDriverAlreadyOpened = FALSE;
	}
	else
	{
		bDriverOpened = TRUE;
		bDriverAlreadyOpened = TRUE;
	}
	
	if (bDriverOpened)
	{
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x0f");
		
		while (nResult == STATUS_SHARED_EXCHANGE_OK)
		{
			nResult = GTL_SharedExchange_GetNext(pDataStruct, &nPosition, &ulReadTag, &ulReadLength, (const unsigned char **)&pValue);
			
			if (nResult == STATUS_SHARED_EXCHANGE_OK)
			{
				for (nIndex=0;nIndex<nIndent;nIndex++)
					CST_DumpData ("  ");
				
				CST_DumpData ("T:%-8lx L:%04lx ", ulReadTag, ulReadLength);
				
				if (GTL_BerTlv_IsTagConstructedObject(ulReadTag))
				{
					CST_DumpData_NewLine();
					GTL_SharedExchange_InitEx(&tTempStruct, ulReadLength, ulReadLength, pValue);
					CST_DumpData_DumpSharedBuffer (&tTempStruct, nIndent+1);
					CST_DumpData_NewLine();
				}
				else
				{
					CST_DumpData ("V:");
					nIndex = 0;
					bFirstLinePrinted = FALSE;
					
					while (nIndex < (int)ulReadLength)
					{
						nIndex2 = 0;
							
						while ((nIndex+nIndex2 < (int)ulReadLength) && (nIndex2 < (14 - nIndent + ((10 + nIndent)  * (bFirstLinePrinted != FALSE)))))
						{
							CST_DumpData("%02x", pValue[nIndex+nIndex2]);
							nIndex2++;
						}
						nIndex += nIndex2;
						CST_DumpData_NewLine();
						bFirstLinePrinted = TRUE;
					}
				}
			}
		}
		
		if (!bDriverAlreadyOpened)
		{
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			
			if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
				CST_DumpData ("\x1b" "@");
			CST_DumpData_CloseOutputDriver();
		}
	}
}



//! \brief Dump a shared exchange buffer content with a title.
//!	\param[in] pDataStruct Shared exchange buffer to be dumped.
//!	\param[in] pTitle Title of the dump.

void CST_DumpData_DumpSharedBufferWithTitle (T_SHARED_DATA_STRUCT * pDataStruct, const char * pTitle)
{
	if (!CST_DumpData_OpenOutputDriver())
		return;

	if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
		CST_DumpData("\x1b" "@\x1b" "E");

	CST_DumpData ("%s", pTitle);
	CST_DumpData_NewLine();
	CST_DumpData_NewLine();

	if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
		CST_DumpData("\x1b" "@");

	CST_DumpData_CloseOutputDriver();

	CST_DumpData_DumpSharedBuffer (pDataStruct, 0);
}


//! \brief Dump data ocntained in a TLV Tree node
//! \param[in] pLabel Label to be printed before the node data.
//! \param[in] TlvTreeNodeToDump TLV Tree node to be dump.
//! \note Label is printed in bold (if printer is used).
//! \note Data are printed in smal character using the following format T:00009F06 L:07 V:A00000000991010

void CST_DumpData_DumpTlvTreeNodeWithTitle (const char* pLabel, TLV_TREE_NODE TlvTreeNodeToDump)
{
	TLV_TREE_NODE hCurrent = TlvTreeNodeToDump;
	TLV_TREE_NODE hParent;

	unsigned char* pucData;
	unsigned int   nLength;
	unsigned int   nTag;

	int nIndent;
	int nIndex;
	int nIndex2;
	int bFirstLinePrinted;

	if (CST_DumpData_OpenOutputDriver())
	{
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
		CST_DumpData("\x1b" "@\x1b" "E");

		CST_DumpData ("%s", pLabel);
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "@" "\x0F");

		while (hCurrent != NULL)
		{
			hParent = hCurrent;
			while ((hParent = TlvTree_GetParent(hParent)) != NULL)
				CST_DumpData (" ");

			nTag    = TlvTree_GetTag(hCurrent);
			nLength = TlvTree_GetLength(hCurrent);
			pucData = (unsigned char*)TlvTree_GetData(hCurrent);
			nIndent = 0;
			nIndex = 0;
			nIndex2 = 0;
			bFirstLinePrinted = FALSE;

			CST_DumpData ("T:%04X L:%04X ", nTag, nLength);

			if (nLength > 0)
			{
				CST_DumpData ("V:");
				while (nIndex < (int)nLength)
				{
					nIndex2 = 0;
				
					while ((nIndex+nIndex2 < (int)nLength) && (nIndex2 < (14 - nIndent + ((10 + nIndent) * (bFirstLinePrinted != FALSE)))))
					{
						CST_DumpData("%02x", pucData[nIndex+nIndex2]);
						nIndex2++;
					}
					nIndex += nIndex2;
					CST_DumpData_NewLine();
					bFirstLinePrinted = TRUE;
				}
			}
			else
			{
				CST_DumpData_NewLine();
			}

			hCurrent = TlvTree_Iterate (hCurrent, TlvTreeNodeToDump);
		}

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
					CST_DumpData ("\x1b" "@");
	
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();


		// Close the output driver
		CST_DumpData_CloseOutputDriver();
	}
}



//! \brief Dump data contained in a TLV Tree node
//! \param[in] pLabel Label to be printed (bold printed).

void CST_DumpData_Title (const char * pLabel)
{
	if (CST_DumpData_OpenOutputDriver())
	{
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "E");

		if (pLabel != NULL)
			CST_DumpData ("%s", pLabel);
			
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "@");

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		// Close the output driver
		CST_DumpData_CloseOutputDriver();
	}
}
