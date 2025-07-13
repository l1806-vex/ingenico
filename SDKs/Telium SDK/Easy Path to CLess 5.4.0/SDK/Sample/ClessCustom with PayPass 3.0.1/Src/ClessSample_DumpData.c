/**
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
 */


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static FILE * gs_hOuputHandle;											/*!< File handle of the output driver. */
static unsigned char gs_ucCustomOutputId = CUSTOM_OUTPUT_PRINTER;		/*!< Default output driver. */


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

extern int IsPrinter(void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Initialise the default output mode (printer if a printer is present, none else).

void ClessSample_DumpData_InitOutput (void)
{
	gs_ucCustomOutputId = ((IsPrinter()) ? CUSTOM_OUTPUT_PRINTER : CUSTOM_OUTPUT_NONE);
}



//! \brief Get the output driver handle.
//! \return	The handle of the output driver

FILE * ClessSample_DumpData_DumpGetOutputHandle (void)
{
	return (gs_hOuputHandle);
}



//! \brief Set the current driver type id.
//! \param[in] ucOutputId output driver id to select (\a CUSTOM_OUTPUT_COM0, \a CUSTOM_OUTPUT_PRINTER, \a CUSTOM_OUTPUT_NONE, \a CUSTOM_OUTPUT_USB, \a CUSTOM_OUTPUT_TRACE).

void ClessSample_DumpData_DumpSetOutputId (unsigned char ucOutputId)
{
	gs_ucCustomOutputId = ucOutputId;
}



//! \brief return output driver id.
//! \return The output driver type
//! 	- \a CUSTOM_OUTPUT_NONE No selected devide (dump functions have no effect).
//! 	- \a CUSTOM_OUTPUT_PRINTER Printer output device.
//! 	- \a CUSTOM_OUTPUT_COM0 COM0 output device.
//! 	- \a CUSTOM_OUTPUT_USB USB output device.
//! 	- \a CUSTOM_OUTPUT_TRACE Trace output device.

unsigned char ClessSample_DumpData_DumpGetOutputId (void)
{
	return (gs_ucCustomOutputId);
}



//! \brief Output line feed : "\n" or a "\r" according the output driver idenifier.

void ClessSample_DumpData_DumpNewLine(void)
{
	switch (ClessSample_DumpData_DumpGetOutputId())
	{
		// =========================================
		case (CUSTOM_OUTPUT_COM0):
		case (CUSTOM_OUTPUT_USB):
			ClessSample_DumpData ("\r");
			break;

		// =========================================
		case (CUSTOM_OUTPUT_PRINTER):
			ClessSample_DumpData ("\n");
			ttestall (PRINTER, 0);
			break;

		// =========================================
		case (CUSTOM_OUTPUT_TRACE):
		default: // Nothing
			break;
	}
}



//! \brief Open current Output driver.
//! \return	
//!		- \ref TRUE if correctly opened.
//!		- \ref FALSE else.
//! \note If the driver is not correctly opened, the dumping is not performed even if requested.

int ClessSample_DumpData_DumpOpenOutputDriver (void)
{
	if (gs_hOuputHandle != NULL)
	{
		fclose (gs_hOuputHandle);
		gs_hOuputHandle = NULL;
	}

	switch (ClessSample_DumpData_DumpGetOutputId())
	{
	case (CUSTOM_OUTPUT_PRINTER):
		gs_hOuputHandle = fopen("PRINTER", "w");
		break;

	case (CUSTOM_OUTPUT_COM0):
		gs_hOuputHandle = fopen("COM0", "rw*");
		format("COM0", 9600, 8, 1, NO_PARITY, EVEN, FALSE);
		break;

	case (CUSTOM_OUTPUT_USB):
		gs_hOuputHandle = fopen("COM5", "rw*");
		format("COM5", 115200, 8, 1, NO_PARITY, EVEN, FALSE);
		break;

	case (CUSTOM_OUTPUT_TRACE): // No driver to open. Trace is allready managed
		gs_hOuputHandle = 0;
		return TRUE;
		break;
		
	default:
		break;
	}

	if (ClessSample_DumpData_DumpGetOutputHandle() != NULL)
		return TRUE;
	else
		return FALSE;
}



//! \brief Close current Output driver.

void ClessSample_DumpData_DumpCloseOutputDriver (void)
{
	if (gs_hOuputHandle)
		fclose (gs_hOuputHandle);
	gs_hOuputHandle = NULL;
}



//! \brief Dump data on current output.
//!	\param[in] pString String to be dumped.
//! \param[in] ... parameters to trace

void ClessSample_DumpData (const char* pString, ...)
{
	char String[300];
	int nLength;
	va_list Params;

	va_start(Params, pString);
#if (defined(__GNUC__) && !defined(_SIMULPC_))
	nLength = vsprintf(String, pString, &Params);
#else
	nLength = vsprintf(String, pString, Params);
#endif
	
	va_end(Params);

	switch (ClessSample_DumpData_DumpGetOutputId())
	{
		// ================================================================================
		case (CUSTOM_OUTPUT_COM0):
		{
			if (ClessSample_DumpData_DumpGetOutputHandle() != NULL)
			{
				int i;
				int len;
				i = 0;
				len = strlen(String);
				do
				{
					i += fwrite(String + i, 1, len - i, ClessSample_DumpData_DumpGetOutputHandle());
					if (i < len)
						ttestall(0,1);
				} while(i < len);
				ttestall (0,1);
			}
			break;
		}

		// ================================================================================
		case (CUSTOM_OUTPUT_USB):
		{
			if (ClessSample_DumpData_DumpGetOutputHandle() != NULL)
			{
				int i;
				int len;
				i = 0;
				len = strlen(String);
				do
				{
					i += fwrite(String + i, 1, len - i, ClessSample_DumpData_DumpGetOutputHandle());
					if (i < len)
						ttestall(0,1);
				} while(i < len);
			}
			break;
		}
		
		// ================================================================================
		case (CUSTOM_OUTPUT_PRINTER):
		{
			if (ClessSample_DumpData_DumpGetOutputHandle() != NULL)
				pprintf (String);
			break;
		}

		// ================================================================================
		case (CUSTOM_OUTPUT_TRACE):
		{
		    GTL_Traces_TraceDebug("%s", String);
			break;
		}
		
		// ================================================================================
		default: // Nothing
			break;
	}
}


//! \brief Dump a shared exchange buffer content (each constructed tag is dumped with a indentation).
//!	\param[in] pDataStruct Shared exchange buffer to be dumped.
//!	\param[in] nIndent Shall be set to 0 at the first call (for indentation purpose).

void ClessSample_DumpData_DumpSharedBuffer (T_SHARED_DATA_STRUCT * pDataStruct, const int nIndent)

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

	if (ClessSample_DumpData_DumpGetOutputHandle() == NULL)
	{
		bDriverOpened = ClessSample_DumpData_DumpOpenOutputDriver();
		bDriverAlreadyOpened = FALSE;
	}
	else
	{
		bDriverOpened = TRUE;
		bDriverAlreadyOpened = TRUE;
	}

	if (bDriverOpened)
	{
		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
			ClessSample_DumpData ("\x0f");
		
		while (nResult == STATUS_SHARED_EXCHANGE_OK)
		{
			nResult = GTL_SharedExchange_GetNext(pDataStruct, &nPosition, &ulReadTag, &ulReadLength, (const unsigned char **)&pValue);

			if (nResult == STATUS_SHARED_EXCHANGE_OK)
			{
				for (nIndex=0;nIndex<nIndent;nIndex++)
					ClessSample_DumpData (" ");
				
				ClessSample_DumpData ("T:%08lx L:%04lx ", ulReadTag, ulReadLength);
				
				if (GTL_BerTlv_IsTagConstructedObject(ulReadTag))
				{
					ClessSample_DumpData_DumpNewLine();
					GTL_SharedExchange_InitEx(&tTempStruct, ulReadLength, ulReadLength, pValue);
					ClessSample_DumpData_DumpSharedBuffer (&tTempStruct, nIndent+1);
					ClessSample_DumpData_DumpNewLine();
				}
				else
				{
					nIndex = 0;
					bFirstLinePrinted = FALSE;

					if (ulReadLength > 0)
					{
						ClessSample_DumpData ("V:");
						while (nIndex < (int)ulReadLength)
						{
							if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
							{
								nIndex2 = 0;

								while ((nIndex+nIndex2 < (int)ulReadLength) && (nIndex2 < (14 - nIndent + ((10 + nIndent) * (bFirstLinePrinted != FALSE)))))
								{
									ClessSample_DumpData("%02x", pValue[nIndex+nIndex2]);
									nIndex2++;
								}
								nIndex += nIndex2;
								ClessSample_DumpData_DumpNewLine();
								bFirstLinePrinted = TRUE;
							}
							else
							{
								ClessSample_DumpData("%02x", pValue[nIndex]);
								nIndex++;
							}
						}
						
						if (ClessSample_DumpData_DumpGetOutputId() != CUSTOM_OUTPUT_PRINTER)
							ClessSample_DumpData_DumpNewLine();

						if ((ulReadTag == TAG_PAYPASS_TRACK1_DATA) || (ulReadTag == TAG_PAYPASS_DD_CARD_TRACK1))
						{
							nIndex = 0;
							bFirstLinePrinted = FALSE;

							ClessSample_DumpData ("ASCII:");

							while (nIndex < (int)ulReadLength)
							{
								if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
								{
									nIndex2 = 0;

									while ((nIndex+nIndex2 < (int)ulReadLength) && (nIndex2 < (42 - nIndent + ((6 + nIndent) * (bFirstLinePrinted != FALSE)))))
									{
										ClessSample_DumpData("%c", pValue[nIndex+nIndex2]);
										nIndex2++;
									}
									nIndex += nIndex2;
									ClessSample_DumpData_DumpNewLine();
									bFirstLinePrinted = TRUE;
								}
								else
								{
									ClessSample_DumpData("%c", pValue[nIndex]);
									nIndex++;
								}
							}

							if (ClessSample_DumpData_DumpGetOutputId() != CUSTOM_OUTPUT_PRINTER)
								ClessSample_DumpData_DumpNewLine();
						}
					}
					else
					{
						ClessSample_DumpData_DumpNewLine();
					}
				}
			}
		}
		
		if (!bDriverAlreadyOpened)
		{
			ClessSample_DumpData_DumpNewLine();
			ClessSample_DumpData_DumpNewLine();
			ClessSample_DumpData_DumpNewLine();

			if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
				ClessSample_DumpData("\x1b" "@");
			ClessSample_DumpData_DumpCloseOutputDriver();
		}
	}
}



//! \brief Dump a shared exchange buffer content with a title.
//!	\param[in] pDataStruct Shared exchange buffer to be dumped.
//!	\param[in] pTitle Title of the dump.

void ClessSample_DumpData_DumpSharedBufferWithTitle (T_SHARED_DATA_STRUCT * pDataStruct, const char * pTitle)
{
	if (!ClessSample_DumpData_DumpOpenOutputDriver())
		return;

	if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
		ClessSample_DumpData("\x1b" "@\x1b" "E");

	ClessSample_DumpData ("%s", pTitle);
	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();

	if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
		ClessSample_DumpData("\x1b" "@");

	ClessSample_DumpData_DumpCloseOutputDriver();

	ClessSample_DumpData_DumpSharedBuffer (pDataStruct, 0);
}



//! \brief Dump data ocntained in a TLV Tree node
//! \param[in] pLabel Label to be printed before the node data.
//! \param[in] TlvTreeNodeToDump TLV Tree node to be dump.
//! \note Label is printed in bold (if printer is used).
//! \note Data are printed in smal character using the following format T:00009F06 L:07 V:A00000000991010

void ClessSample_DumpData_DumpTlvTreeNodeWithTitle (const char* pLabel, TLV_TREE_NODE TlvTreeNodeToDump)
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

	if (ClessSample_DumpData_DumpOpenOutputDriver())
	{
		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
		ClessSample_DumpData("\x1b" "@\x1b" "E");

		ClessSample_DumpData ("%s", pLabel);
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();

		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
			ClessSample_DumpData ("\x1b" "@" "\x0F");

		while (hCurrent != NULL)
		{
			hParent = hCurrent;
			while ((hParent = TlvTree_GetParent(hParent)) != NULL)
				ClessSample_DumpData (" ");

			nTag    = TlvTree_GetTag(hCurrent);
			nLength = TlvTree_GetLength(hCurrent);
			pucData = (unsigned char*)TlvTree_GetData(hCurrent);
			nIndent = 0;
			nIndex = 0;
			nIndex2 = 0;
			bFirstLinePrinted = FALSE;

			ClessSample_DumpData ("T:%04X L:%04X ", nTag, nLength);

			if (nLength > 0)
			{
				ClessSample_DumpData ("V:");
				while (nIndex < (int)nLength)
				{
					nIndex2 = 0;
				
					while ((nIndex+nIndex2 < (int)nLength) && (nIndex2 < (14 - nIndent + ((10 + nIndent) * (bFirstLinePrinted != FALSE)))))
					{
						ClessSample_DumpData("%02x", pucData[nIndex+nIndex2]);
						nIndex2++;
					}
					nIndex += nIndex2;
					ClessSample_DumpData_DumpNewLine();
					bFirstLinePrinted = TRUE;
				}
			}
			else
			{
				ClessSample_DumpData_DumpNewLine();
			}

			hCurrent = TlvTree_Iterate (hCurrent, TlvTreeNodeToDump);
		}

		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
					ClessSample_DumpData ("\x1b" "@");
	
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();


		// Close the output driver
		ClessSample_DumpData_DumpCloseOutputDriver();
	}
}



//! \brief Dump data ocntained in a TLV Tree node
//! \param[in] pLabel Label to be printed (bold printed).

void ClessSample_DumpData_DumpTitle (const char * pLabel)
{
	if (ClessSample_DumpData_DumpOpenOutputDriver())
	{
		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
			ClessSample_DumpData ("\x1b" "E");

		if (pLabel != NULL)
			ClessSample_DumpData ("%s", pLabel);
			
		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
			ClessSample_DumpData ("\x1b" "@");

		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();


		// Close the output driver
		ClessSample_DumpData_DumpCloseOutputDriver();
	}
}
