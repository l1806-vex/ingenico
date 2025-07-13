//! \file
//! Module that manages the data dump on a ticket

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"

#include "GTL_BerTlv.h"
#include "GTL_SharedExchange.h"

#include "DllTesting_DumpData.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static FILE * gs_hOuputHandle;
static unsigned char gs_ucCustomOutputId = CUSTOM_OUTPUT_PRINTER;


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static FILE * __DumpGetOutputHandle (void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

/**
 * function:    __DumpGetOutputHandle
 * @brief: Get the output driver handle.

 * @param	void
 * @return	The handle of the output driver
 */
static FILE * __DumpGetOutputHandle (void)
{
	return gs_hOuputHandle;
}



/**
 * function:    DumpGetOutputId
 * @brief: Get the output driver identifier.

 * @param	void
 * @return	the selected output driver id :
 *     - CUSTOM_OUTPUT_COM0		if COM0 is used.
 *     - CUSTOM_OUTPUT_PRINTER	if PRINTER is used.
 *     - CUSTOM_OUTPUT_NONE		if no output is used (or cannot be used).
 */
unsigned char DumpGetOutputId (void)
{
	return gs_ucCustomOutputId;
}



/**
 * function:    DumpSetOutputId
 * @brief: Set the output driver identifier.

 * @param	ucOutputId		identifier of the output
 *     - CUSTOM_OUTPUT_COM0		if COM0 is used.
 *     - CUSTOM_OUTPUT_USB		if USB is used.
 *     - CUSTOM_OUTPUT_PRINTER	if PRINTER is used.
 *     - CUSTOM_OUTPUT_NONE		if no output is used (or cannot be used).
 * @return	void
 */
void DumpSetOutputId (unsigned char ucOutputId)
{
	gs_ucCustomOutputId = ucOutputId;
}



/**
 * function:    DumpNewLine
 * @brief: Print a "\n" or a "\r" according the output driver idenifier.

 * @param	void
 * @return	void
 */
void DumpNewLine(void)
{
	switch (DumpGetOutputId())
	{
		// =========================================
		case (CUSTOM_OUTPUT_COM0):
		case (CUSTOM_OUTPUT_USB):
			DumpData ("\r");
			ttestall (0,1);
			break;

		// =========================================
		case (CUSTOM_OUTPUT_PRINTER):
			DumpData ("\n");
			ttestall (PRINTER,10);
			break;

		// =========================================
		default: // Nothing
			break;
	}
}



/**
 * function:    DumpOpenOutputDriver
 * @brief: Open the output driver (printer or COM0).

 * @param	void
 * @return	TRUE if correctly opened, FALSE else.
 * @remark	If the driver is not correctly opened, the dumping is not performed even if requested.
 */
int DumpOpenOutputDriver (void)
{
	if (gs_hOuputHandle != NULL)
	{
		fclose (gs_hOuputHandle);
		gs_hOuputHandle = NULL;
	}

	switch (DumpGetOutputId())
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

	default:
		break;
	}

	if (__DumpGetOutputHandle() != NULL)
		return TRUE;
	else
		return FALSE;
}



/**
 * function:    DumpCloseOutputDriver
 * @brief: Close the output driver (printer or COM0).

 * @param	void
 * @return	void
 */
void DumpCloseOutputDriver (void)
{
	fclose (gs_hOuputHandle);
	gs_hOuputHandle = NULL;
}



/**
 * function:    DumpData
 * @brief: Dump data (string formated) on the correct output.

 * @param	pString			Data to be dumped
 * @return	void
 */
void DumpData (const char* pString, ...)
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

	switch (DumpGetOutputId())
	{
		// ================================================================================
		case (CUSTOM_OUTPUT_COM0):
		{
			if (__DumpGetOutputHandle() != NULL)
			{
				int i;
				int len;
				i = 0;
				len = strlen(String);
				do
				{
					i += fwrite(String + i, 1, len - i, __DumpGetOutputHandle());
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
			if (__DumpGetOutputHandle() != NULL)
			{
				int i;
				int len;
				i = 0;
				len = strlen(String);
				do
				{
					i += fwrite(String + i, 1, len - i, __DumpGetOutputHandle());
					if (i < len)
						ttestall(0,1);
				} while(i < len);
			}
			break;
		}

		// ================================================================================
		case (CUSTOM_OUTPUT_PRINTER):
			pprintf (String);
			break;

		// ================================================================================
		default: // Nothing
			break;
	}
}



void DllTesting_DumpData_DumpSharedBuffer (T_SHARED_DATA_STRUCT * pDataStruct, const int nIndent)
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
	
	if (__DumpGetOutputHandle() == NULL)
	{
		bDriverOpened = DumpOpenOutputDriver();
		bDriverAlreadyOpened = FALSE;
	}
	else
	{
		bDriverOpened = TRUE;
		bDriverAlreadyOpened = TRUE;
	}
	
	if (bDriverOpened)
	{
		if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
			DumpData ("\x0f");
		
		while (nResult == STATUS_SHARED_EXCHANGE_OK)
		{
			nResult = GTL_SharedExchange_GetNext(pDataStruct, &nPosition, &ulReadTag, &ulReadLength, (const unsigned char **)&pValue);
			
			if (nResult == STATUS_SHARED_EXCHANGE_OK)
			{
				for (nIndex=0;nIndex<nIndent;nIndex++)
					DumpData ("  ");
				
				DumpData ("T:%08lx L:%04lx ", ulReadTag, ulReadLength);
				
				if (GTL_BerTlv_IsTagConstructedObject(ulReadTag))
				{
					DumpNewLine();
					GTL_SharedExchange_InitEx(&tTempStruct, ulReadLength, ulReadLength, pValue);
					DllTesting_DumpData_DumpSharedBuffer (&tTempStruct, nIndent+1);
					DumpNewLine();
				}
				else
				{
					DumpData ("V:");
					nIndex = 0;
					bFirstLinePrinted = FALSE;
					
					while (nIndex < (unsigned int)ulReadLength)
					{
						nIndex2 = 0;
							
						while ((nIndex+nIndex2 < (unsigned int)ulReadLength) && (nIndex2 < (14 - nIndent + ((10 + nIndent)  * (bFirstLinePrinted != FALSE)))))
						{
							DumpData("%02x", pValue[nIndex+nIndex2]);
							nIndex2++;
						}
						nIndex += nIndex2;
						DumpNewLine();
						bFirstLinePrinted = TRUE;
					}
				}
			}
		}
		
		if (!bDriverAlreadyOpened)
		{
			DumpNewLine();
			DumpNewLine();
			DumpNewLine();
			
			if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
				DumpData("\x1b" "@");
			DumpCloseOutputDriver();
		}
	}
}



/*int TlvTree_Dump( const TLV_TREE_NODE hTree, const char* szTitle )
{
	unsigned char *pucBuffer;

	int nTraceSize      = 0;
	int nSerializedSize = 0;
	int nTitleSize      = 0;
	int nCurrentIndex   = 0;
	int nStatus;

	if( hTree != NULL )
	{
		nTraceSize  = sizeof(int); // For magic       (4 bytes)
		nTraceSize += sizeof(int); // For version     (4 bytes)
		nTraceSize += sizeof(int); // For title size  (4 bytes)
		nTraceSize += sizeof(int); // For buffer size (4 bytes)
	
		if( szTitle != NULL )
		{
			nTitleSize  = strlen(szTitle) + 1; // To copy the \0
			nTraceSize += nTitleSize;
		}
		
		nSerializedSize = TlvTree_GetSerializationSize( hTree, TLV_TREE_SERIALIZER_DEFAULT );
		if( nSerializedSize > 0 )
		{
			nTraceSize += nSerializedSize;
		
			pucBuffer = (unsigned char*)umalloc( nTraceSize );
			if( pucBuffer != NULL )
			{
				nCurrentIndex = 0;
		
				// Add the header...
		
				// Magic
				pucBuffer[nCurrentIndex++] = 'T';
				pucBuffer[nCurrentIndex++] = 'R';
				pucBuffer[nCurrentIndex++] = 'E';
				pucBuffer[nCurrentIndex++] = 'E';
		
				// Version
				pucBuffer[nCurrentIndex++] = 0x00;
				pucBuffer[nCurrentIndex++] = 0x00;
				pucBuffer[nCurrentIndex++] = 0x01;
				pucBuffer[nCurrentIndex++] = 0x00;
			
				// Title Size
				memcpy( &pucBuffer[nCurrentIndex], &nTitleSize, sizeof(nTitleSize) );
				nCurrentIndex += sizeof(nTitleSize);
				
				// Serialized size
				memcpy( &pucBuffer[nCurrentIndex], &nSerializedSize, sizeof(nSerializedSize) );
				nCurrentIndex += sizeof(nSerializedSize);
				
				// Add the title...
				if( nTitleSize != 0 )
				{
					memcpy( &pucBuffer[nCurrentIndex], szTitle, nTitleSize );
					nCurrentIndex += nTitleSize;
				}
			
				// Add the serialized tree...
				nStatus = TlvTree_Serialize( hTree, TLV_TREE_SERIALIZER_DEFAULT, &pucBuffer[nCurrentIndex], nSerializedSize );
			
				if( nStatus > 0 )
				{
					// Trace the buffer...
					trace( TLVTREE_TRACE_ID, nTraceSize, pucBuffer );
					nStatus = TLV_TREE_OK;
				}
		
				ufree( pucBuffer );
			}
			else
			{
				nStatus = TLV_TREE_ERROR_MEMORY;
			}
		}
		else
		{
			// Retrieve the error from TlvTree_GetSerializationSize()
			nStatus = nSerializedSize;
		}
	}
	else
	{
		nStatus = TLV_TREE_ERROR_INVALID_TREE;
	}
	
	return nStatus;
}*/
