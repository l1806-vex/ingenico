//! \file
//! Module that manages all the application menus

/////////////////////////////////////////////////////////////////

//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "TlvTree.h"

#include "ConfigurationTest.h"
#include "TestIso.h"
#include "UserInterfaceHelpers.h"
#include "oem_cless.h"    // Telium Pass include driver
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"
#include "TestMifare.h"
#include "TPassMenu.h"

//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////


// Main menu
/*static const char * MainMenu[] =
{
#ifndef _TEST_2ND_APPLICATION_
	"TeliumPass tests",
#endif
	"Implicit Select"
};*/


static const char* MainMenu[] =
{
	"Check Connection",
	"Reset",
	"Reader Infos",
	"Backlight",
	"LEDs",
	"Buzzer",
	"Display",
	"CLess ISO",
	"CLess MIFARE"
};

static const char* BacklightMenu[] =
{
	"Test 1 : ON/OFF", "Test 2 : Fading"
};

static const char* LedsMenu[] =
{
	"Test 1 : ON", "Test 2 : OFF", "Test 3 : Blink"
};

static const char* BuzzerMenu[] =
{
	"Test 1 : Frequence", "Test 2 : Volume", "Test 3 : Beep"
};

static const char* DisplayMenu[] =
{
	"Test 1 : Display", "Test 2 : Display XY"
};

static const char* CLessIso14443Menu[] =
{
	"Test 1 : Detect TO", "Test 2 : Detect TO",
	"Test 3 : Sync/Sync", "Test 4 : Sync/Async",
	"Test 5 : ASync/Sync", "Test 6 : ASync/Async"
};

static const char* CLessMifareMenu[] =
{
	"Test 1 : Detect TO",
	"CREDIT",
	"DEBIT",
	"BALANCE",
	"RESET PURSE"
};


// CLESS_IS_FOR_YOU response
static const char * CIFY_ResponseMenu[] =
{
	"FCT_OK", "STOP"
};


//// Static function definitions ////////////////////////////////

//static int __TPassMenu_Configuration (void);
static int __TPassMenu_CLessMifare (void);
static int __TPassMenu_CLessIso14443_4 (void);
static int __TPassMenu_Display (void);
static int __TPassMenu_Buzzer (void);
static int __TPassMenu_Leds (void);
static int __TPassMenu_Backlight (void);


//// Functions //////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// Name :		__TPassMenu_Backlight 
// Desciption :	Menu that allows to test the backlight functionalities.

static int __TPassMenu_Backlight (void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		TPass_FirstLine();
		CUC30_DisplayText("\n\nBACKLIGHT TESTS", CUC30_ALIGN_CENTER);
		TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

		nChoice = HelperDisplayMenu("Backlight Tests", nChoice, NUMBER_OF_ITEMS(BacklightMenu), BacklightMenu);
		if (nChoice >= 0)
		{
			nResult = 0;
			switch(nChoice)
			{
			case 0: // Backligth ON/OFF
				BacklightTest(0);
				break;

			case 1: // Backligth fading ON/OFF
				BacklightTest(1);
				break;

			default: // Default case
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}



/////////////////////////////////////////////////////////////////
// Name :		__TPassMenu_Leds 
// Desciption :	Menu that allows to test the leds functionalities.

static int __TPassMenu_Leds (void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		TPass_FirstLine();
		CUC30_DisplayText("\n\nLEDS TESTS", CUC30_ALIGN_CENTER);
		TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

		nChoice = HelperDisplayMenu("LEDs Tests", nChoice, NUMBER_OF_ITEMS(LedsMenu), LedsMenu);
		if (nChoice >= 0)
		{
			nResult = 0;
			switch(nChoice)
			{
			case 0:
				LedsTest(0);
				break;

			case 1:
				LedsTest(1);
				break;

			case 2:
				LedsTest(2);
				break;

			default:
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}



/////////////////////////////////////////////////////////////////
// Name :		__TPassMenu_Buzzer 
// Desciption :	Menu that allows to test the buzzer functionalities.

static int __TPassMenu_Buzzer (void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		TPass_FirstLine();
		CUC30_DisplayText("\n\nBUZZER TESTS", CUC30_ALIGN_CENTER);
		TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

		nChoice = HelperDisplayMenu("Buzzer Tests", nChoice, NUMBER_OF_ITEMS(BuzzerMenu), BuzzerMenu);
		if (nChoice >= 0)
		{
			nResult = 0;
			switch(nChoice)
			{
			case 0:
				BuzzerTest(0);
				break;

			case 1:
				BuzzerTest(1);
				break;

			case 2:
				BuzzerTest(2);
				break;

			default:
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}


/////////////////////////////////////////////////////////////////
// Name :		__TPassMenu_Display
// Desciption :	Menu that allows to test the display functionalities.

static int __TPassMenu_Display (void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		TPass_FirstLine();
		CUC30_DisplayText("\n\nDISPLAY TESTS", CUC30_ALIGN_CENTER);
		TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

		nChoice = HelperDisplayMenu("Display Tests", nChoice, NUMBER_OF_ITEMS(DisplayMenu), DisplayMenu);
		if (nChoice >= 0)
		{
			nResult = 0;
			switch(nChoice)
			{
			case 0:
				DisplayTest(0);
				break;

			case 1:
				DisplayTest(1);
				break;

			default:
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}



/////////////////////////////////////////////////////////////////
// Name :		__TPassMenu_CLessIso14443_4
// Desciption :	Menu that allows to test the ISO14443 functionalities.

static int __TPassMenu_CLessIso14443_4 (void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		TPass_FirstLine();
		CUC30_DisplayText("\n\nISO14443-4 TESTS", CUC30_ALIGN_CENTER);
		TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

		nChoice = HelperDisplayMenu("ISO Tests", nChoice, NUMBER_OF_ITEMS(CLessIso14443Menu), CLessIso14443Menu);

		if (nChoice >= 0)
		{
			nResult = 0;
			switch(nChoice)
			{
			case 0:
				TestIso_ISO14443Test(0);
				break;

			case 1:
				TestIso_ISO14443Test(1);
				break;

			case 2:
				TestIso_ISO14443Test(2);
				break;

			case 3:
				TestIso_ISO14443Test(3);
				break;

			case 4:
				TestIso_ISO14443Test(4);
				break;

			case 5:
				TestIso_ISO14443Test(5);
				break;

			default:
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}



/////////////////////////////////////////////////////////////////
// Name :		__TPassMenu_CLessMifare
// Desciption :	Menu that allows to test the MiFare functionalities.

static int __TPassMenu_CLessMifare (void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		TPass_FirstLine();
		CUC30_DisplayText("\n\nMIFARE TESTS", CUC30_ALIGN_CENTER);
		TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

		nChoice = HelperDisplayMenu("MIFARE Tests", nChoice, NUMBER_OF_ITEMS(CLessMifareMenu), CLessMifareMenu);

		if (nChoice >= 0)
		{
			nResult = 0;
			switch(nChoice)
			{
			case 0:
				TestMifare_Test(0);
				break;

			case 1:
				TestMifare_Test(1);
				break;

			case 2:
				TestMifare_Test(2);
				break;

			case 3:
				TestMifare_Test(3);
				break;

			case 4:
				TestMifare_Test(4);
				break;

			default:
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}


/////////////////////////////////////////////////////////////////
//
//

/*static int __TPassMenu_Configuration (void)
{
	int nChoice;
	int nResult;

	nChoice = 0;

	do
	{
		TPass_FirstLine();
		CUC30_DisplayText("\n\nTELIUM PASS\n\nTESTS", CUC30_ALIGN_CENTER);
		TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

		nChoice = HelperDisplayMenu("TeliumPass", nChoice, NUMBER_OF_ITEMS(ConfigurationMenu), ConfigurationMenu);
		if (nChoice >= 0)
		{
			nResult = 0;
			switch(nChoice)
			{
			case 0:
				TPass_FirstLine();
				CUC30_DisplayText("\n\nCHECKING PRESENCE", CUC30_ALIGN_CENTER);
				TPass_BacklightLevel(TPASS_BACKLIGHT_ON);
				CheckPresence();
				break;

			case 1:
				ResetTest();
				break;

			case 2:
				InfoTest();
				break;

			case 3:
				nResult = __TPassMenu_Backlight ();
				break;

			case 4:
				nResult = __TPassMenu_Leds ();
				break;

			case 5:
				nResult = __TPassMenu_Buzzer ();
				break;

			case 6:
				nResult = __TPassMenu_Display ();
				break;

			case 7:
				nResult = __TPassMenu_CLessIso14443_4 ();
				break;

			case 8:
				nResult = __TPassMenu_CLessMifare ();
				break;

			default:
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	TPass_BacklightFadeToLevel(TPASS_BACKLIGHT_OFF, TPASS_BACKLIGHT_DEFAULT_FADE_RAMP * 2);
	TPass_FirstLine();

	return nChoice;
}*/


/////////////////////////////////////////////////////////////////
// Function name	:	__TPassMenu_Display
// Description		:	Global menu management

void TPassMenu_MainMenu (void)
{
	int nChoice;
	int nResult;

	nChoice = 0;

	do
	{
		TPass_FirstLine();
		CUC30_DisplayText("\n\nTELIUM PASS\n\nTESTS", CUC30_ALIGN_CENTER);
		TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

		nChoice = HelperDisplayMenu("TeliumPass", nChoice, NUMBER_OF_ITEMS(MainMenu), MainMenu);
		if (nChoice >= 0)
		{
			nResult = 0;
			switch(nChoice)
			{
			case 0:
				TPass_FirstLine();
				CUC30_DisplayText("\n\nCHECKING PRESENCE", CUC30_ALIGN_CENTER);
				TPass_BacklightLevel(TPASS_BACKLIGHT_ON);
				CheckPresence();
				break;

			case 1:
				ResetTest();
				break;

			case 2:
				InfoTest();
				break;

			case 3:
				nResult = __TPassMenu_Backlight ();
				break;

			case 4:
				nResult = __TPassMenu_Leds ();
				break;

			case 5:
				nResult = __TPassMenu_Buzzer ();
				break;

			case 6:
				nResult = __TPassMenu_Display ();
				break;

			case 7:
				nResult = __TPassMenu_CLessIso14443_4 ();
				break;

			case 8:
				nResult = __TPassMenu_CLessMifare ();
				break;

			default:
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	TPass_BacklightFadeToLevel(TPASS_BACKLIGHT_OFF, TPASS_BACKLIGHT_DEFAULT_FADE_RAMP * 2);
	TPass_FirstLine();
}



// Choice for cless_is_for_you entry point call
unsigned int TPassMenu_ClessIsForYou_choice (unsigned char bUseDefaultValue)
{
	int nChoice, nResult;

	nResult = 0;
	nChoice = 0;

	if (bUseDefaultValue)
		return FCT_OK;

	do
	{
		nChoice = HelperDisplayMenu("CIFY CHOICE", nChoice, NUMBER_OF_ITEMS(CIFY_ResponseMenu), CIFY_ResponseMenu);

		if (nChoice >= 0)
		{
			nResult = 0;
			switch(nChoice)
			{
			case 0: // TeliumPass Configuration
				nResult = FCT_OK;
				nChoice = -1;
				break;

			case 1: // Implicit Select
				nResult = STOP;
				nChoice = -1;
				break;

			default:
				nResult = FCT_OK;
				nChoice = -1;
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nResult;
}
