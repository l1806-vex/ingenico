//! \file
//! Module that manages all the application menus

/////////////////////////////////////////////////////////////////

//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "TlvTree.h"

#include "ConfigurationTest.h"
#include "UserInterfaceHelpers.h"
#include "oem_sys.h"
#include "oem_cless.h"
#include "oem_clmf1.h"
#include "uiram.h"
#include "DataElement.h"
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"


#define DRIVER_C30_DISPLAY				"DISPLAY_C30"

//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

static void __CUC30_DisplayText (const char* szText, int nLength, int nAlignment);
static void __TeliumPass_PrintModules (void);
static void __PrintDiagnostics (void);
static void __HardwareCapabilities (void);
static void __SoftwareCapabilities (void);
static void __ListComponents (void);

//// Global variables ///////////////////////////////////////////


//// Local functions ////////////////////////////////////////////

static void __CUC30_DisplayText(const char* szText, int nLength, int nAlignment)
{
	FILE* hDisplay;
	int nScreenWidth;
	int nX;
	int nY;
	int nIndex;
	const char* pLinePtr;
	const char* pPtr;
	int nLineLength;
	int bEnd;

	hDisplay = fopen(DRIVER_C30_DISPLAY, "a*");
	if (hDisplay != NULL)
	{
		if (nAlignment == CUC30_ALIGN_LEFT)
		{
			if (nLength >= 0)
				fprintf(hDisplay, "%.*s", nLength, szText);
			else fprintf(hDisplay, "%s", szText);
		}
		else
		{
			// Get the current cursor position
			nX = whereydsp(hDisplay);
			nY = wherexdsp(hDisplay);

			// Get the screen width
			gotoxydsp(hDisplay, nY, 255);
			nScreenWidth = whereydsp(hDisplay);

			nIndex = 0;
			pLinePtr = szText;
			pPtr = szText;
			nLineLength = 0;
			bEnd = FALSE;
			while(!bEnd)
			{
				if (((nIndex >= nLength) && (nLength >= 0)) || (*pPtr == '\0'))
					bEnd = TRUE;

				if ((bEnd) || (*pPtr == '\n'))
				{
					if (nLineLength < nScreenWidth)
					{
						if (nAlignment == CUC30_ALIGN_CENTER)
							nX = (nScreenWidth - nLineLength) / 2;
						else nX = nScreenWidth - nLineLength;
					}
					else
					{
						nLineLength = nScreenWidth;
						nX = 0;
					}

					// Set the correct cursor position
					gotoxydsp(hDisplay, nY, nX);

					// Display the string
					fprintf(hDisplay, "%.*s", nLineLength, pLinePtr);

					if (!bEnd)
					{
						// It is a carriage return => go to next line
						nX = 0;
						nY++;

						pLinePtr = pPtr + 1;
						nLineLength = 0;
					}
					else
					{
						nX += nLineLength;
					}
				}
				else
				{
					nLineLength++;
				}

				nIndex++;
				pPtr++;
			}

			// Set the correct cursor position
			gotoxydsp(hDisplay, nY, nX);
		}

		fclose(hDisplay);
	}
}


static void __TeliumPass_PrintModules(void)
{
	unsigned char Buffer[512];
	unsigned long i;
	int iWrittenBytes;
	FILE* hPrinter;

	hPrinter = NULL;

	if (TPass_GetApplicationVersions(Buffer, sizeof(Buffer)) == ERR_TPASS_KO)
	{
		upload_diagnostic_txt ((unsigned char*)"TPass_GetApplicationVersions error\n");
		return;
	}

	if (hPrinter == NULL)
	{
		hPrinter = fopen("PRINTER", "w");
		fprintf(hPrinter, "\x1b" "@\x1b" "ETeliumPass Application\nModules\n\x1b" "@\n\n");
		upload_diagnostic_txt ((unsigned char*)"ON PASS LA\n");
		ttestall(PRINTER, 0);
	}

	i=0;

	while ((Buffer[i] != '\0') && (i<sizeof(Buffer)))
	{
		iWrittenBytes = fwrite (&Buffer[i], 1, 1, hPrinter);
		i += iWrittenBytes;
	}

	if (hPrinter != NULL)
	{
		fprintf(hPrinter, "\n\n\n\n");
		ttestall(PRINTER, 0);

		fclose(hPrinter);
	}
}


/////////////////////////////////////////////////////////////////
// Function name	:	__ListComponents
// Description		:	Lists the components loaded in the cless reader
//						(TeliumPass or Vending Pass).

static void __ListComponents (void)
{
	int nIndex;
	int nResult;
	T_TPASS_COMPONENT_INFO Info;
	FILE* hPrinter;

	hPrinter = NULL;
	nIndex = 0;
	do
	{
		nResult = TPass_GetComponentInfoByIndex(nIndex, &Info);
		if (nResult == ERR_TPASS_OK)
		{
			if (hPrinter == NULL)
			{
				hPrinter = fopen("PRINTER", "w");
				fprintf(hPrinter, "\x1b" "@\x1b" "ETeliumPass Components\n\x1b" "@\n\n");
			}

			fprintf(hPrinter, "%s\n"
				"Number      : %s\n"
				"Size          : %u\n"
				"CRC           : %04X\n"
				"Type          : %u\n"
				"Key           : %08X\n"
				"Load adr      : %08X\n"
				"Start data adr: %08X\n"
				"End data adr  : %08X\n"
				"Entry point   : %08X\n"
				"RUF adr 1     : %08X\n"
				"RUF adr 2     : %08X\n"
				"RUF adr 3     : %08X\n"
				"\n\n"
				,
				Info.Label,
				Info.Identification,
				Info.Size,
				Info.Crc,
				Info.Type,
				Info.Key,
				Info.LoadingAddress,
				Info.DataAddressStart,
				Info.DataAddressEnd,
				Info.EntryPointAddress,
				Info.RufAddress1,
				Info.RufAddress2,
				Info.RufAddress3);

			ttestall(PRINTER, 0);

			nIndex++;
		}
	} while(nResult == ERR_TPASS_OK);

	if (hPrinter != NULL)
	{
		fprintf(hPrinter, "\n\n\n\n\x0c");
		ttestall(PRINTER, 0);

		fclose(hPrinter);
	}
}



/////////////////////////////////////////////////////////////////
// Function name	:	__SoftwareCapabilities
// Description		:	Gets the cless reader software capabilities.
//						(TeliumPass or Vending Pass).

static void __SoftwareCapabilities (void)
{
	int nResult;
	T_TPASS_SOFTWARE_CAPABILITIES SoftCapabilities;
	FILE* hPrinter;

	nResult = TPass_GetSoftwareCapabilities(&SoftCapabilities);
	if (nResult == ERR_TPASS_OK)
	{
		hPrinter = fopen("PRINTER", "w");
		fprintf(hPrinter, "\x1b" "@\x1b" "ETeliumPass Software\nCapabilities\n\x1b" "@\n\n");

		fprintf(hPrinter,
			"RUF 1       : %02X\n"
			"Security    : %X\n"
			"ISO14443 C  : %X\n"
			"Mifare      : %X\n"
			"ISO14443 AB : %X\n"
			"Appli       : %X\n"
			"RUF 2       : %X\n"
			"\n\n"
			,
			SoftCapabilities.Ruf1,
			SoftCapabilities.Security,
			SoftCapabilities.Iso14443_C,
			SoftCapabilities.Mifare,
			SoftCapabilities.Iso14443_AB,
			SoftCapabilities.Appli,
			SoftCapabilities.Ruf2);

		fprintf(hPrinter, "\n\n\n\n\x0c");
		ttestall(PRINTER, 0);
		fclose(hPrinter);
	}
}



/////////////////////////////////////////////////////////////////
// Function name	:	__HardwareCapabilities
// Description		:	Gets the cless reader hardware capabilities.
//						(TeliumPass or Vending Pass).

static void __HardwareCapabilities (void)
{
	int nResult;
	T_TPASS_HARDWARE_CAPABILITIES HardCapabilities;
	FILE* hPrinter;

	nResult = TPass_GetHardwareCapabilities(&HardCapabilities);
	if (nResult == ERR_TPASS_OK)
	{
		hPrinter = fopen("PRINTER", "w");
		fprintf(hPrinter, "\x1b" "@\x1b" "ETeliumPass Hardware\nCapabilities\n\x1b" "@\n\n");

		fprintf(hPrinter,
			"Product id   :  %8s\n"
			"Serial number:  %8s\n"
			"Product code :  %8s\n"
			"Constructor  :  %8s\n"
			"Manufacturing:%c%c/%c%c/%c%c%c%c\n"
			"Booster ver. :  %8s\n"
			"\n"
			"Options :\n"
			,
			HardCapabilities.szProductIdentification,
			HardCapabilities.szSerialNumber,
			HardCapabilities.szProductCode,
			HardCapabilities.szConstructorCode,
			HardCapabilities.szManufacturingDate[0],
			HardCapabilities.szManufacturingDate[1],
			HardCapabilities.szManufacturingDate[2],
			HardCapabilities.szManufacturingDate[3],
			HardCapabilities.szManufacturingDate[4],
			HardCapabilities.szManufacturingDate[5],
			HardCapabilities.szManufacturingDate[6],
			HardCapabilities.szManufacturingDate[7],
			HardCapabilities.szBoosterVersion);

		ttestall(PRINTER, 0);

		if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_BUZZER) != 0)
		{
			fprintf(hPrinter, "  BUZZER\n");
			ttestall(PRINTER, 0);
		}
		if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_USB_SLAVE) != 0)
		{
			fprintf(hPrinter, "  USB SLAVE\n");
			ttestall(PRINTER, 0);
		}
		if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_COM0) != 0)
		{
			if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_INTER_UC_ON_COM0) != 0)
				fprintf(hPrinter, " *COM0\n");
			else fprintf(hPrinter, "  COM0\n");
			ttestall(PRINTER, 0);
		}
		if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_COM1) != 0)
		{
			if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_COM0_COM1_SEPARATED) != 0)
				fprintf(hPrinter, " !COM1\n");
			else fprintf(hPrinter, "  COM1\n");
			ttestall(PRINTER, 0);
		}
		if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_SAM_1) != 0)
		{
			fprintf(hPrinter, "  SAM 1\n");
			ttestall(PRINTER, 0);
		}
		if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_SAM_2) != 0)
		{
			fprintf(hPrinter, "  SAM 2\n");
			ttestall(PRINTER, 0);
		}
		if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_SAM_3) != 0)
		{
			fprintf(hPrinter, "  SAM 3\n");
			ttestall(PRINTER, 0);
		}
		if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_SAM_4) != 0)
		{
			fprintf(hPrinter, "  SAM 4\n");
			ttestall(PRINTER, 0);
		}
		if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_DISPLAY_NONE) != 0)
		{
			fprintf(hPrinter, "  NO DISPLAY\n");
			ttestall(PRINTER, 0);
		}
		if ((HardCapabilities.Options & TPASS_HARDWARE_OPTION_DISPLAY_128_64) != 0)
		{
			fprintf(hPrinter, "  DISPLAY 128x64\n");
			ttestall(PRINTER, 0);
		}

		fprintf(hPrinter, "\n\n\n\n\x0c");
		ttestall(PRINTER, 0);
		fclose(hPrinter);
	}
}



/////////////////////////////////////////////////////////////////
// Function name	:	__PrintDiagnostics
// Description		:	Prints the cless reader system diagnostics.
//						(TeliumPass or Vending Pass).

static void __PrintDiagnostics (void)
{
	int nResult;
	spy_data_t SpyData;
	char Diagnostics[TPASS_DIAGNOSTICS_SIZE + 1];
	FILE* hPrinter;
	int nIndex;
	int nIndex2;

#ifndef _SIMULPC_
	nResult = TPass_GetDeviceType();
#else
	nResult = TPASS_CLESS_TYPE_TELIUM_PASS;
#endif

	if ((nResult != TPASS_CLESS_TYPE_TELIUM_PASS) && (nResult != TPASS_CLESS_TYPE_CAD30VT))
		return;

	nResult = TPass_GetDiagnostics(&SpyData, Diagnostics);
	if (nResult == ERR_TPASS_OK)
	{
		Diagnostics[TPASS_DIAGNOSTICS_SIZE] = '\0';

		hPrinter = fopen("PRINTER", "w");
		fprintf(hPrinter, "\x1b" "@\x1b" "ETeliumPass Diagnostics\n\x1b" "@\n\n");

		fprintf(hPrinter,
			"Hard reset nb : %8u\n"
			"Soft reset nb : %8u\n"
			"Num of excep. : %8u\n"
			"Type of excep.: %8u\n"
			"r0            : %08X\n"
			"r1            : %08X\n"
			"r2            : %08X\n"
			"r3            : %08X\n"
			"r4            : %08X\n"
			"r5            : %08X\n"
			"r6            : %08X\n"
			"r7            : %08X\n"
			"r14           : %08X\n"
			,
			SpyData.hard_reset_nbr,
			SpyData.soft_reset_nbr,
			SpyData.exceptions_nbr,
			SpyData.exception_type,
			SpyData.exception_r0,
			SpyData.exception_r1,
			SpyData.exception_r2,
			SpyData.exception_r3,
			SpyData.exception_r4,
			SpyData.exception_r5,
			SpyData.exception_r6,
			SpyData.exception_r7,
			SpyData.exception_r14
			);
		ttestall(PRINTER, 0);

		fprintf(hPrinter, "\nException infos:\n");
		ttestall(PRINTER, 0);

		nIndex = 0;
		fprintf(hPrinter, "\x0f");
		while(nIndex < EXCEPTION_INFO_LEN)
		{
			nIndex2 = 0;
			do
			{
				if (nIndex2 > 0)
					fprintf(hPrinter, " ");
				fprintf(hPrinter, "0x%08X", SpyData.exception_info[nIndex]);
				nIndex++;
				nIndex2++;
			} while((nIndex < EXCEPTION_INFO_LEN) && (nIndex2 < 4));

			fprintf(hPrinter, "\n");
			ttestall(PRINTER, 0);
		}

		fprintf(hPrinter, "\x1b" "@\nTrap reset (ptr = 0x%02X):\n", SpyData.trap_reset_ptr);
		ttestall(PRINTER, 0);

		nIndex = 0;
		nIndex2 = 0;
		fprintf(hPrinter, "\x0f");
		while(nIndex < TRAP_RESET_DATA_LEN)
		{
			if ((SpyData.trap_reset_data[nIndex] == '\n')
				|| (SpyData.trap_reset_data[nIndex] == '\r'))
			{
				nIndex2 = 0;
				fprintf(hPrinter, "\n");
				ttestall(PRINTER, 0);
			}
			else if (SpyData.trap_reset_data[nIndex] > 0)
			{
				if (SpyData.trap_reset_data[nIndex] >= ' ')
					fprintf(hPrinter, "%c", SpyData.trap_reset_data[nIndex]);
				else fprintf(hPrinter, ".");

				nIndex2++;

				if (nIndex2 >= 48)
				{
					nIndex2 = 0;
					fprintf(hPrinter, "\n");
					ttestall(PRINTER, 0);
				}
			}

			nIndex++;
		}
		fprintf(hPrinter, "\x1b" "@\n\n");
		ttestall(PRINTER, 0);

		nIndex = 0;
		fprintf(hPrinter, "\x0f");
		while(nIndex < TRAP_RESET_DATA_LEN)
		{
			nIndex2 = 0;
			do
			{
				if (nIndex2 > 0)
					fprintf(hPrinter, " ");
				fprintf(hPrinter, "%02X", SpyData.trap_reset_data[nIndex]);
				nIndex++;
				nIndex2++;
			} while((nIndex < TRAP_RESET_DATA_LEN) && (nIndex2 < 16));

			fprintf(hPrinter, "\n");
			ttestall(PRINTER, 0);
		}

		fprintf(hPrinter, "\x1b" "@\n------------------------\n");
		ttestall(PRINTER, 0);
		fprintf(hPrinter, "%s\n", Diagnostics);
		ttestall(PRINTER, 0);
		fprintf(hPrinter, "------------------------\n");
		ttestall(PRINTER, 0);

		fprintf(hPrinter, "\n\n\n\n\x0c");
		ttestall(PRINTER, 0);
		fclose(hPrinter);
	}
}


//// Main functions ////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
// Function name	:	CUC30_DisplayText
// Description		:	To display a messages (left, rigth or center aligned) on
//						the TeliumPass or Vending Pass device.

void CUC30_DisplayText (const char* szText, int nAlignment)
{
	__CUC30_DisplayText(szText, -1, nAlignment);
}


/////////////////////////////////////////////////////////////////
// Function name	:	CheckPresence
// Description		:	Checks the cless reader presence.
//						(TeliumPass or Vending Pass).

void CheckPresence (void)
{
	FILE* hDisplay;
	FILE* hKeyboard;
	int bEnd;
	int bOldPresent;
	int bPresent;
	unsigned char nKeyboardState;
	int nKey;

	hDisplay = fopen("DISPLAY", "w");
	hKeyboard = fopen("KEYBOARD", "r");

	bPresent = -1;
	bEnd = FALSE;
	do
	{
		bOldPresent = bPresent;
		if (TPass_CheckPresence() == ERR_TPASS_OK)
			bPresent = TRUE;
		else bPresent = FALSE;

		if (bOldPresent != bPresent)
		{
			if (bPresent)
			{
				printf("\x1b" "   CONNECTED");
				TPass_FirstLine();
				CUC30_DisplayText("\n\nCHECKING PRESENCE", CUC30_ALIGN_CENTER);
				TPass_BacklightLevel(TPASS_BACKLIGHT_ON);
			}
			else printf("\x1b" " NOT CONNECTED");
		}

		status(hKeyboard, &nKeyboardState);
		if (nKeyboardState == 0)
		{
			ttestall(KEYBOARD, 10);
			status(hKeyboard, &nKeyboardState);
		}

		if (nKeyboardState != 0)
		{
			nKey = getchar();
			if (nKey == T_ANN)
				bEnd = TRUE;
		}
	} while(!bEnd);

	fclose(hKeyboard);
	fclose(hDisplay);
}


/////////////////////////////////////////////////////////////////
// Function name	:	ResetTest
// Description		:	Resets (Hard and soft) the cless reader.
//						(TeliumPass or Vending Pass).

void ResetTest (void)
{
	FILE* hDisplay;
	unsigned long ulStartTime;
	unsigned long ulResetTime;
	char String[40 + 1];

	hDisplay = fopen("DISPLAY", "w");

	printf("\x1b" "   SOFT RESET");
	ulStartTime = get_tick_counter();
	TPass_Reset(FALSE, TRUE);
	ulResetTime = get_tick_counter() - ulStartTime;
	sprintf(String, "\n\nSOFT RESET\n\n%lu.%02lu s", ulResetTime / 100, ulResetTime % 100);
	TPass_FirstLine();
	CUC30_DisplayText(String, CUC30_ALIGN_CENTER);
	TPass_BacklightLevel(TPASS_BACKLIGHT_ON);
	printf("\x1b" "   SOFT RESET\n     %lu.%02lu s", ulResetTime / 100, ulResetTime % 100);

	ttestall(0, 200);

	printf("\x1b" "   HARD RESET");
	ulStartTime = get_tick_counter();
	TPass_Reset(TRUE, TRUE);
	ulResetTime = get_tick_counter() - ulStartTime;
	sprintf(String, "\n\nHARD RESET\n\n%lu.%02lu s", ulResetTime / 100, ulResetTime % 100);
	TPass_FirstLine();
	CUC30_DisplayText(String, CUC30_ALIGN_CENTER);
	TPass_BacklightLevel(TPASS_BACKLIGHT_ON);
	printf("\x1b" "   HARD RESET\n     %lu.%02lu s", ulResetTime / 100, ulResetTime % 100);

	ttestall(0, 200);

	fclose(hDisplay);
}


/////////////////////////////////////////////////////////////////
// Function name	:	InfoTest
// Description		:	Gets all the cless reader information.
//						(TeliumPass or Vending Pass).

void InfoTest (void)
{
	__HardwareCapabilities();
	__SoftwareCapabilities();
	__ListComponents();
	__TeliumPass_PrintModules();

	__PrintDiagnostics();
}

void BacklightTest(int nTest)
{
	FILE* hDisplay;
	FILE* hKeyboard;
	int bEnd;
	int bBacklight;
	unsigned char nKeyboardState;
	int nKey;
	int bChangeBacklight;

	hDisplay = fopen("DISPLAY", "w");
	hKeyboard = fopen("KEYBOARD", "r");

	bEnd = FALSE;
	bBacklight = FALSE;
	bChangeBacklight = FALSE;
	do
	{
		if (bBacklight)
		{
			TPass_FirstLine();
			CUC30_DisplayText("\n\nBACKLIGHT\nON", CUC30_ALIGN_CENTER);
			printf("\x1b" "   BACKLIGHT\n       ON");

			if (nTest == 0)
				TPass_BacklightLevel(TPASS_BACKLIGHT_ON);
			else TPass_BacklightFadeToLevel(TPASS_BACKLIGHT_ON, TPASS_BACKLIGHT_DEFAULT_FADE_RAMP / 2);
		}
		else
		{
			TPass_FirstLine();
			CUC30_DisplayText("\n\nBACKLIGHT\nOFF", CUC30_ALIGN_CENTER);
			printf("\x1b" "   BACKLIGHT\n      OFF");

			if (nTest == 0)
				TPass_BacklightLevel(TPASS_BACKLIGHT_OFF);
			else TPass_BacklightFadeToLevel(TPASS_BACKLIGHT_OFF, TPASS_BACKLIGHT_DEFAULT_FADE_RAMP / 2);
		}

		status(hKeyboard, &nKeyboardState);
		if ((nTest == 0) && (nKeyboardState == 0))
		{
			ttestall(KEYBOARD, 50);
			status(hKeyboard, &nKeyboardState);
		}
		if (nKeyboardState != 0)
		{
			nKey = getchar();
			if (nKey == T_ANN)
				bEnd = TRUE;
		}

		// Change backlight every 2 loops
		if (bChangeBacklight)
			bBacklight = !bBacklight;

		bChangeBacklight = !bChangeBacklight;
	} while(!bEnd);

	fclose(hKeyboard);
	fclose(hDisplay);
}

void LedsTest(int nTest)
{
	FILE* hDisplay;
	FILE* hKeyboard;
	int bEnd;
	int nIndex;
	unsigned char nKeyboardState;
	int nKey;
	int bChangeLeds;

	hDisplay = fopen("DISPLAY", "w");
	hKeyboard = fopen("KEYBOARD", "r");

	if (nTest == 1)
		TPass_LedsOn(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
	else TPass_LedsOff(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);

	bEnd = FALSE;
	nIndex = FALSE;
	bChangeLeds = FALSE;
	do
	{
		if (nTest == 0)
		{
			TPass_FirstLine();
			switch(nIndex)
			{
			case 0:
				CUC30_DisplayText("\n\nLEDS TEST\n\nX - - -", CUC30_ALIGN_CENTER);
				printf("\x1b" "   LEDS TEST\n    X - - -");
				TPass_LedsOn(TPASS_LED_1);
				TPass_LedsOff(TPASS_LED_4);
				break;
			case 1:
				CUC30_DisplayText("\n\nLEDS TEST\n\n- X - -", CUC30_ALIGN_CENTER);
				printf("\x1b" "   LEDS TEST\n    - X - -");
				TPass_LedsOn(TPASS_LED_2);
				TPass_LedsOff(TPASS_LED_1);
				break;
			case 2:
				CUC30_DisplayText("\n\nLEDS TEST\n\n- - X -", CUC30_ALIGN_CENTER);
				printf("\x1b" "   LEDS TEST\n    - - X -");
				TPass_LedsOn(TPASS_LED_3);
				TPass_LedsOff(TPASS_LED_2);
				break;
			case 3:
				CUC30_DisplayText("\n\nLEDS TEST\n\n- - - X", CUC30_ALIGN_CENTER);
				printf("\x1b" "   LEDS TEST\n    - - - X");
				TPass_LedsOn(TPASS_LED_4);
				TPass_LedsOff(TPASS_LED_3);
				break;
			}
		}
		else if (nTest == 1)
		{
			TPass_FirstLine();
			switch(nIndex)
			{
			case 0:
				CUC30_DisplayText("\n\nLEDS TEST\n\n- X X X", CUC30_ALIGN_CENTER);
				printf("\x1b" "   LEDS TEST\n    - X X X");
				TPass_LedsOff(TPASS_LED_1);
				TPass_LedsOn(TPASS_LED_4);
				break;
			case 1:
				CUC30_DisplayText("\n\nLEDS TEST\n\nX - X X", CUC30_ALIGN_CENTER);
				printf("\x1b" "   LEDS TEST\n    X - X X");
				TPass_LedsOff(TPASS_LED_2);
				TPass_LedsOn(TPASS_LED_1);
				break;
			case 2:
				CUC30_DisplayText("\n\nLEDS TEST\n\nX X - X", CUC30_ALIGN_CENTER);
				printf("\x1b" "   LEDS TEST\n    X X - X");
				TPass_LedsOff(TPASS_LED_3);
				TPass_LedsOn(TPASS_LED_2);
				break;
			case 3:
				CUC30_DisplayText("\n\nLEDS TEST\n\nX X X -", CUC30_ALIGN_CENTER);
				printf("\x1b" "   LEDS TEST\n    X X X -");
				TPass_LedsOff(TPASS_LED_4);
				TPass_LedsOn(TPASS_LED_3);
				break;
			}
		}
		else
		{
			TPass_FirstLine();
			if ((nIndex % 2) == 0)
			{
				CUC30_DisplayText("\n\nLEDS TEST\n\nCHENILLARD", CUC30_ALIGN_CENTER);
				printf("\x1b" "   LEDS TEST\n   CHENILLARD");

				TPass_LedsBlink(TPASS_LED_1, 1 * C30_CHENILLARD_TIME, 4 * C30_CHENILLARD_TIME);
				TPass_LedsBlink(TPASS_LED_2, 2 * C30_CHENILLARD_TIME, 3 * C30_CHENILLARD_TIME);
				TPass_LedsBlink(TPASS_LED_3, 3 * C30_CHENILLARD_TIME, 2 * C30_CHENILLARD_TIME);
				TPass_LedsBlink(TPASS_LED_4, 4 * C30_CHENILLARD_TIME, 1 * C30_CHENILLARD_TIME);
			}
			else
			{
				CUC30_DisplayText("\n\nLEDS TEST\n\nBLINK", CUC30_ALIGN_CENTER);
				printf("\x1b" "   LEDS TEST\n     BLINK");

				TPass_LedsBlink(TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4, 25, 25);
			}

			bChangeLeds = TRUE;
		}

		status(hKeyboard, &nKeyboardState);
		if (nKeyboardState == 0)
		{
			if (nTest == 2)
				ttestall(KEYBOARD, 500);
			else ttestall(KEYBOARD, 50);
			status(hKeyboard, &nKeyboardState);
		}
		if (nKeyboardState != 0)
		{
			nKey = getchar();
			if (nKey == T_ANN)
				bEnd = TRUE;
		}

		// Change LEDs every 2 loops
		if (bChangeLeds)
			nIndex = (nIndex + 1) % 4;

		bChangeLeds = !bChangeLeds;
	} while(!bEnd);

	TPass_LedsBlink(TPASS_LED_1, 1 * C30_CHENILLARD_TIME, 4 * C30_CHENILLARD_TIME);
	TPass_LedsBlink(TPASS_LED_2, 2 * C30_CHENILLARD_TIME, 3 * C30_CHENILLARD_TIME);
	TPass_LedsBlink(TPASS_LED_3, 3 * C30_CHENILLARD_TIME, 2 * C30_CHENILLARD_TIME);
	TPass_LedsBlink(TPASS_LED_4, 4 * C30_CHENILLARD_TIME, 1 * C30_CHENILLARD_TIME);

	fclose(hKeyboard);
	fclose(hDisplay);
}

void BuzzerTest(int nTest)
{
	FILE* hDisplay;
	FILE* hKeyboard;
	int bEnd;
	int nIndex;
	unsigned char nKeyboardState;
	int nKey;
	char String[40 + 1];
	int nFrequency;
	int nVolume;
	int nDelay;

	hDisplay = fopen("DISPLAY", "w");
	hKeyboard = fopen("KEYBOARD", "r");

	if (nTest == 0)
	{
		nFrequency = 20;
		nVolume = 32;
		nDelay = 2;
	}
	else if (nTest == 1)
	{
		nFrequency = 3000;
		nVolume = 0;
		nDelay = 2;
	}
	else
	{
		nFrequency = 3000;
		nVolume = 32;
		nDelay = 2;
	}

	bEnd = FALSE;
	nIndex = FALSE;
	do
	{
		if (nTest == 0)
		{
			TPass_FirstLine();
			sprintf(String, "\n\nBUZZER TEST\n\nFreq = %i Hz", nFrequency);
			CUC30_DisplayText(String, CUC30_ALIGN_CENTER);
			printf("\x1b" "  BUZZER TEST\n Freq = %i Hz", nFrequency);

			TPass_Buzzer(0, 0);
			ttestall(0, 10);
			TPass_Buzzer(nFrequency, (unsigned char)nVolume);

			if (nFrequency < 100)
				nFrequency += 10;
			else if (nFrequency < 1000)
				nFrequency += 100;
			else if (nFrequency < 10000)
				nFrequency += 1000;
			else nFrequency = 20;
		}
		else if (nTest == 1)
		{
			TPass_FirstLine();
			sprintf(String, "\n\nBUZZER TEST\n\nVol = %d", nVolume);
			CUC30_DisplayText(String, CUC30_ALIGN_CENTER);
			printf("\x1b" "  BUZZER TEST\n   Vol = %d", nVolume);

			TPass_Buzzer(0, 0);
			ttestall(0, 10);
			TPass_Buzzer(nFrequency, (unsigned char)nVolume);

			nVolume += 16;
			if (nVolume > 255)
				nVolume = 0;
		}
		else
		{
			TPass_FirstLine();
			sprintf(String, "\n\nBUZZER TEST\n\nDelay = %d ms", nDelay * 10);
			CUC30_DisplayText(String, CUC30_ALIGN_CENTER);
			printf("\x1b" "  BUZZER TEST\n Delay = %d ms", nDelay * 10);

			ttestall(0, 10);
			TPass_BuzzerBeep(nFrequency, (unsigned char)nVolume, nDelay);

			if (nDelay < 10)
				nDelay += 2;
			else if (nDelay < 50)
				nDelay += 10;
			else if (nDelay < 100)
				nDelay += 50;
			else nDelay = 2;
		}

		status(hKeyboard, &nKeyboardState);
		if (nKeyboardState == 0)
		{
			ttestall(KEYBOARD, 50);
			status(hKeyboard, &nKeyboardState);
		}
		if (nKeyboardState != 0)
		{
			nKey = getchar();
			if (nKey == T_ANN)
				bEnd = TRUE;
		}
	} while(!bEnd);

	TPass_Buzzer(0, 0);

	fclose(hKeyboard);
	fclose(hDisplay);
}

void DisplayTest(int nTest)
{
	FILE* hDisplay;
	FILE* hKeyboard;
	int bEnd;
	int nIndex;
	unsigned char nKeyboardState;
	int nKey;

	hDisplay = fopen("DISPLAY", "w");
	hKeyboard = fopen("KEYBOARD", "r");

	bEnd = FALSE;
	nIndex = FALSE;
	do
	{
		if (nTest == 0)
		{
			switch(nIndex)
			{
			case 0:
				printf("\x1b" "  DISPLAY TEST\n      INIT");
				TPass_FirstLine();
				TPass_Display("##################\n##################\n"
							  "##################\n##################\n"
							  "##################\n##################\n"
							  "##################\n##################\n");
				break;
			case 1:
				printf("\x1b" "  DISPLAY TEST\n  FirstLine()");
				TPass_FirstLine();
				break;
			case 2:
				printf("\x1b" "  DISPLAY TEST\nDisplay(\"Line1\")");
				TPass_Display("Line1\n");
				break;
			case 3:
				printf("\x1b" "  DISPLAY TEST\nDisplay(\"Line2\")");
				TPass_Display("Line2");
				break;
			case 4:
				printf("\x1b" "  DISPLAY TEST\n  ClearLine()");
				TPass_ClearLine();
				break;
			case 5:
				printf("\x1b" "  DISPLAY TEST\nDisplay(\"Line2\")");
				TPass_Display("Line2\n");
				break;
			case 6:
				printf("\x1b" "  DISPLAY TEST\nDisplay(\"Line3\")");
				TPass_Display("Line3\n");
				break;
			}

			nIndex++;
			if (nIndex > 6)
				nIndex = 0;
		}
		else if (nTest == 1)
		{
			TPass_FirstLine();
			printf("\x1b" "  DISPLAY TEST\n  Display_XY()");

			TPass_DisplayXY(0, 0, "TL");
			TPass_DisplayXY(16, 0, "TR");
			TPass_DisplayXY(0, 7, "BL");
			TPass_DisplayXY(16, 7, "BR");
			TPass_DisplayXY(6, 3, "CENTER");
		}

		status(hKeyboard, &nKeyboardState);
		if (nKeyboardState == 0)
		{
			if (nTest == 1)
				ttestall(KEYBOARD, 0);
			else ttestall(KEYBOARD, 200);
			status(hKeyboard, &nKeyboardState);
		}
		if (nKeyboardState != 0)
		{
			nKey = getchar();
			if (nKey == T_ANN)
				bEnd = TRUE;
		}
	} while(!bEnd);

	fclose(hKeyboard);
	fclose(hDisplay);
}

