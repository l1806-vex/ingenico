//! \file
//! Assertions management for debug purposes.

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#ifdef _C30_
#include "std_c.h"
#include "swirom.h"
//#include "oem_manque.h"
#else
#include "SDK30.h"
#endif

#include "Common.h"
#include "Assert.h"

#ifdef _MSC_VER
#include <CrtDbg.h>
#endif // _MSC_VER

#ifdef __USE_ASSERT__

//// Macros & preprocessor definitions //////////////////////////

#ifdef _EFT30_
#define __ASSERT_USE_KEYBOARD__
#define __ASSERT_ALLOW_PRINT__
#endif

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Static function definitions ////////////////////////////////

#ifdef __ASSERT_ALLOW_PRINT__
static void __assert_print(const char* szFileName, int nLine);
#endif

//// Functions //////////////////////////////////////////////////

#ifdef __ASSERT_ALLOW_PRINT__
//! \brief Print a ticket that describe an assertion.
//! \param[in] szFileName Source file name.
//! \param[in] nLine Line in the source file name.
static void __assert_print(const char* szFileName, int nLine)
{
	FILE* hPrinter;

	hPrinter = fopen("PRINTER", "w-*");
	if (hPrinter != NULL)
	{
		// Print
		pprintf("\x1b""H\x1b""E   ASSERTION FAILED\n\x1b""@");
		pprintf("File : %s\n", szFileName);
		pprintf("Line : %i\n\n\n\n\n", nLine);

		ttestall(PRINTER, 0);
		fclose(hPrinter);
	}
}
#endif

int __assert(int bTest, const char* szFile, int nLine)
{
#ifdef _EFT30_
	char szString[512];
#endif
	const char* szFileName;
	FILE* hDisplay;
#ifdef __ASSERT_USE_KEYBOARD__
	FILE* hKeyboard;
	int bReset;
	int bDebug;
	int nKey;
	int bEnd;
#endif // __ASSERT_USE_KEYBOARD__
#ifdef __ASSERT_ALLOW_PRINT__
	int bPrint;
#endif // __ASSERT_ALLOW_PRINT__

	if (bTest)
		return FALSE;

	// Retrieve the file name
	szFileName = strrchr(szFile, '\\');
	if (szFileName == NULL)
		szFileName = szFile;
	else szFileName++;

	// Trace the assertion
#ifdef _EFT30_
	upload_diagnostic_def(ASSERT_FAILED_DIAG, 0);
	sprintf(szString, "*** ASSERTION FAILED File: %s Line: %i\n", szFileName, nLine);
	upload_diagnostic_txt((unsigned char*)szString);
	trace(SAP_KERNEL_TRAP_RESET, strlen(szString), szString);
#endif

	// Open the display
	hDisplay = fopen("DISPLAY", "w*");
#ifdef _EFT30_
	if (hDisplay == NULL)
		hDisplay = fowner("DISPLAY", CurrentTask());
#endif

#ifdef __ASSERT_USE_KEYBOARD__
	bDebug = FALSE;
#endif
	if (hDisplay != NULL)
	{
		// Clear the screen
		printf("\x1b");

		// Display a message
		startupcv20(7, 7);
		printf(" ASSERTION FAILED\n");
		startupcv20(1, 1);
		printf("\nFile: %s\nLine: %i\n", szFileName, nLine);

		// Close the display
		startupcv20(0, 0);
		fclose(hDisplay);

#ifdef __ASSERT_USE_KEYBOARD__
		bReset = FALSE;
		bDebug = FALSE;
#ifdef __ASSERT_ALLOW_PRINT__
		bPrint = FALSE;
#endif // __ASSERT_ALLOW_PRINT__

		// Open the keyboard
		hKeyboard = fopen("KEYBOARD", "r*");
		if (hKeyboard != NULL)
		{
			bEnd = FALSE;
			do
			{
				bReset = FALSE;
				bDebug = FALSE;
#ifdef __ASSERT_ALLOW_PRINT__
				bPrint = FALSE;
#endif // __ASSERT_ALLOW_PRINT__

				if (ttestall(KEYBOARD, 6000) == KEYBOARD)
				{
					nKey = getc(hKeyboard);
					switch(nKey)
					{
					case T_ANN:
					case T_VAL:
						bReset = TRUE;
						break;
					case T_SK1:
					case T_SK2:
					case T_SK3:
					case T_SK4:
						bDebug = TRUE;
						break;
#ifdef __ASSERT_ALLOW_PRINT__
					case T_SK10:
						bPrint = TRUE;
						break;
#endif // __ASSERT_ALLOW_PRINT__
					}
				}
				else bReset = TRUE;

#ifdef __ASSERT_ALLOW_PRINT__
				if (bPrint)
				{
					__assert_print(szFileName, nLine);
				}
				else
#endif // __ASSERT_ALLOW_PRINT__
				{
					if (bReset)
					{
						fclose(hKeyboard);

						// Reset
						exit(ASSERT_FAILED_DIAG);
					}
					else if (bDebug)
					{
						// Stop execution
						bEnd = TRUE;
					}
				}
			} while(!bEnd);

			fclose(hKeyboard);
		}
		else
		{
			// Wait 10 seconds
			ttestall(0, 1000);
		}
#else // __ASSERT_USE_KEYBOARD__
		// Wait 30 seconds
		ttestall(0, 3000);
#endif // __ASSERT_USE_KEYBOARD__
	}
	else
	{
#ifdef __ASSERT_ALLOW_PRINT__
		// Print the assertion
		__assert_print(szFileName, nLine);
#endif // __ASSERT_ALLOW_PRINT__
	}

#ifdef __ASSERT_USE_KEYBOARD__
	// Reset
	if (!bDebug)
#endif
		exit(ASSERT_FAILED_DIAG);

	return TRUE;
}

#endif // __USE_ASSERT__
