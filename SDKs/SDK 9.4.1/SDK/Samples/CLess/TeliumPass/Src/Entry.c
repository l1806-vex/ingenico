/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "TlvTree.h"
#include "oem_cless.h"

#include "UserInterfaceHelpers.h"
#include "GTL_SharedExchange.h"
#include "ClessInterface.h"
#include "ConfigurationTest.h"
#include "TPassMenu.h"
#include "ImplicitSelection.h"
#include "DllTesting_DumpData.h"

//// Macros & preprocessor definitions //////////////////////////

#define SERVICES_LOW_PRIORITY			30
#define SERVICES_HIGH_PRIORITY			10
#define SERVICES_DEFAULT_PRIORITY		20


//// Static function definitions ////////////////////////////////

void entry(void);

static int PrintAppliVersion(NO_SEGMENT AppliNum, int bFormFeed);
static int after_reset_(NO_SEGMENT AppliNum, S_TRANSOUT* pParamOut);
static int idle_message_(NO_SEGMENT AppliNum);
static int is_card_emv_for_you_(NO_SEGMENT AppliNum, const S_AID* pParamIn, S_CARDOUT* pParamOut);
static int is_card_specific_(NO_SEGMENT AppliNum, const S_TRANSIN* pParamIn, S_ETATOUT* pParamOut);
static int is_change_init_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_delete_(NO_SEGMENT AppliNum, S_DELETE* pParamOut);
static int is_evol_pg_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_for_you_after_(NO_SEGMENT AppliNum, const S_TRANSIN* pParamIn, S_CARDOUT* pParamOut);
static int is_for_you_before_(NO_SEGMENT AppliNum, const S_TRANSIN* pParamIn, S_ETATOUT* pParamOut);
static int is_licenced_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_name_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_state_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_time_function_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int give_your_domain_(NO_SEGMENT AppliNum, S_INITPARAMOUT* pParamOut);
static int more_function_(NO_SEGMENT AppliNum);
static int state_(NO_SEGMENT AppliNum);
static int give_info_(NO_SEGMENT AppliNum, S_TRANSIN * pParamIn, S_CLESS_GIVEINFO* pParamOut);
static int cless_is_for_you_ (NO_SEGMENT AppliNum, unsigned int nSize, void * pData);
static int cless_debit_aid_ (NO_SEGMENT AppliNum, unsigned int nSize, void * pData);
static int cless_debit_ (NO_SEGMENT AppliNum, unsigned int nSize, void * pData);
static int cless_end_ (NO_SEGMENT AppliNum);

static int Main_(unsigned int nSize, StructPt* pData);


//// Global variables ///////////////////////////////////////////
static const char APP_NAME[] = "Main Test TPass";

static service_desc_t Services[] = {
	{ 0, AFTER_RESET, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IDLE_MESSAGE, (SAP)Main_, 60},
	{ 0, IS_CARD_EMV_FOR_YOU, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_CARD_SPECIFIC, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_CHANGE_INIT, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_DELETE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_EVOL_PG, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_FOR_YOU_AFTER, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_FOR_YOU_BEFORE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_LICENCED, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_NAME, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_STATE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_TIME_FUNCTION, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, GIVE_YOUR_DOMAIN, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, MORE_FUNCTION, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, STATE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, CLESS_GIVE_INFO, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, CLESS_IS_FOR_YOU, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, CLESS_DEBIT, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, CLESS_DEBIT_AID, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, CLESS_END, (SAP)Main_, SERVICES_DEFAULT_PRIORITY }
};

//// Functions //////////////////////////////////////////////////

static int PrintAppliVersion(NO_SEGMENT AppliNum, int bFormFeed)
{
	int nResult;
	FILE* hPrinter;
	SEGMENT Infos;
	unsigned char Status;

	// Get information on the application
	info_seg(AppliNum, &Infos);

	// Open the printer
	hPrinter = fopen("PRINTER", "w-*");
	if (hPrinter != NULL)
	{
		// Print
		pprintf("\x1b" "@\n\x1b" "E%s\n\x1b" "@", APP_NAME);
		pprintf("Version : %s\n", Get_AppliName(AppliNum));
		pprintf("CRC     : %04X\n\n", Infos.crc);

		if (bFormFeed)
			pprintf("\n\n\n\n");

		ttestall(PRINTER, 0);

		status(hPrinter, &Status);
		if ((Status & (PRINT_ERROR | PAPER_OUT)) != 0)
			nResult = STOP;
		else nResult = FCT_OK;

		fclose(hPrinter);
	}
	else nResult = FCT_OK;

	return nResult;
}



static int after_reset_(NO_SEGMENT AppliNum, S_TRANSOUT* pParamOut)
{
	unsigned char ChangeFlag;
	unsigned char ChangeType;
	unsigned int nResult;

	// Clear the output parameter
	memset(pParamOut, 0, sizeof(*pParamOut));

	// Check for first run
	if (first_init(AppliNum, &ChangeFlag, &ChangeType) != FSE_FAILED)
	{
		if (ChangeFlag == (unsigned char)-1)
		{
			// Print the version
			PrintAppliVersion(AppliNum, TRUE);

			// Cold reset
			raz_init(AppliNum);
		}
	}

	{
		TPasslib_open();

		nResult = TPass_IsConnected();
		if (nResult == ERR_TPASS_OK)
		{
			TPass_BacklightLevel(0);
			TPass_FirstLine();
			CUC30_DisplayText("\n\nTeliumPass Test", CUC30_ALIGN_CENTER);
			return FCT_OK;
		}
		else
		{
			printf("\x1b" "CHECK TeliumPass\nPRESENCE ");
			ttestall(0, 300);
			return STOP;
		}

	}

}

static int idle_message_(NO_SEGMENT AppliNum)
{
	FILE* hDisplay;
	int nDefaultFont;
	int nScreenWidth;
	int nScreenHeight;
	int nFontHeight;
	int terminalType;
	int nResult;

	(void) AppliNum;

	// Get the type of contactless reader
#ifndef _SIMULPC_
	nResult = TPass_GetDeviceType();
#else
	nResult = TPASS_CLESS_TYPE_TELIUM_PASS;
#endif

	// If there is no contactless reader
	if (nResult == TPASS_CLESS_TYPE_NONE)
	{
		return (FCT_OK);
	}
	else if ((nResult == TPASS_CLESS_TYPE_TELIUM_PASS) || (nResult == TPASS_CLESS_TYPE_CAD30VT)) // TeliumPass or Vending Pass
	{
		// Terminal idle message
		hDisplay = fopen("DISPLAY", "w");
		nDefaultFont = GetDefaultFont();

		CreateGraphics(_XLARGE_);
		GetScreenSize(&nScreenHeight, &nScreenWidth);
		nFontHeight = GetPoliceSize();

		SystemFioctl (SYS_FIOCTL_GET_TERMINAL_TYPE, &terminalType);

		// Display the idle message according to terminal type
		if (!IsHeader())
		{
			_DrawRect(0, 0, nScreenWidth-1, nScreenHeight-1, 1, _ON_, _OFF_);
			_DrawRect(1, 1, nScreenWidth-2, nScreenHeight-2, 1, _ON_, _OFF_);
			_DrawRect(3, 3, nScreenWidth-4, nScreenHeight-4, 1, _ON_, _OFF_);
			
			SetFont(_LARGE_);
			_DrawString("Addon Cless", 25, 7+10, _OFF_);
			SetFont(_MEDIUM_);
			_DrawString("Sample Application", 15, 7+30, _OFF_);

		}
		else
		{
			_DrawRect(0, 22, nScreenWidth-1, nScreenHeight-1-7, 1, _ON_, _OFF_);
			_DrawRect(1, 23, nScreenWidth-2, nScreenHeight-2-7, 1, _ON_, _OFF_);
			_DrawRect(3, 25, nScreenWidth-4, nScreenHeight-4-7, 1, _ON_, _OFF_);
			
			SetFont(_LARGE_);
			_DrawString("Addon Cless", 25, 7+10, _OFF_);
			SetFont(_MEDIUM_);
			_DrawString("Sample Application", 15, 7+30, _OFF_);
		}

		PaintGraphics();

		SetDefaultFont(nDefaultFont);
		fclose(hDisplay);

		// Clear the cless reader screen
		TPass_FirstLine ();

		// Turn on the reader screen backligth
		TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

		// Turn off all the LEDs
		TPass_LedsOff (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);

		// Display the idle screen
		CUC30_DisplayText ("\n\nAddon Cless\n\nSample Application\n", CUC30_ALIGN_CENTER);
	}
	else // Internal contactless reader
	{
		// Terminal idle message
		hDisplay = fopen("DISPLAY", "w");
		nDefaultFont = GetDefaultFont();

		CreateGraphics(_XLARGE_);
		GetScreenSize(&nScreenHeight, &nScreenWidth);
		nFontHeight = GetPoliceSize();

		// Display the idle message according to terminal type
		if (!IsHeader())
		{
			_DrawRect(0, 0, nScreenWidth-1, nScreenHeight-1, 1, _ON_, _OFF_);
			_DrawRect(1, 1, nScreenWidth-2, nScreenHeight-2, 1, _ON_, _OFF_);
			_DrawRect(3, 3, nScreenWidth-4, nScreenHeight-4, 1, _ON_, _OFF_);
			
			SetFont(_LARGE_);
			_DrawString("Addon Cless", 25, 7+10, _OFF_);
			SetFont(_MEDIUM_);
			_DrawString("Sample Application", 15, 7+30, _OFF_);

		}
		else
		{
			_DrawRect(0, 22, nScreenWidth-1, nScreenHeight-1-7, 1, _ON_, _OFF_);
			_DrawRect(1, 23, nScreenWidth-2, nScreenHeight-2-7, 1, _ON_, _OFF_);
			_DrawRect(3, 25, nScreenWidth-4, nScreenHeight-4-7, 1, _ON_, _OFF_);
			
			SetFont(_LARGE_);
			_DrawString("Addon Cless", 25, 7+10, _OFF_);
			SetFont(_MEDIUM_);
			_DrawString("Sample Application", 25, 7+30, _OFF_);
		}

		PaintGraphics();

		SetDefaultFont(nDefaultFont);
		fclose(hDisplay);

		// Turn on the terminal screen backligth
		TPass_BacklightLevel(TPASS_BACKLIGHT_ON);

		// Turn off all the LEDs
		TPass_LedsOff (TPASS_LED_1 | TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
	}

	return (FCT_OK);
}


static int is_card_emv_for_you_(NO_SEGMENT AppliNum, const S_AID* pParamIn, S_CARDOUT* pParamOut)
{
	(void)pParamIn;

	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].cardappnumber = 0;
	//pParamOut->returned_state[pParamOut->response_number].cardapp;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_card_specific_(NO_SEGMENT AppliNum, const S_TRANSIN* pParamIn, S_ETATOUT* pParamOut)
{
	(void)pParamIn;

	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_KO;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_change_init_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.mask = MSK_NULL;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_delete_(NO_SEGMENT AppliNum, S_DELETE* pParamOut)
{
	(void)AppliNum;

	// Initialise the output parameter
	memset(pParamOut, 0, sizeof(*pParamOut));

	pParamOut->deleting = DEL_YES;

	return FCT_OK;
}

static int is_evol_pg_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_OK;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_for_you_after_(NO_SEGMENT AppliNum, const S_TRANSIN* pParamIn, S_CARDOUT* pParamOut)
{
	(void)pParamIn;

	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].cardappnumber = 0;
	//pParamOut->returned_state[pParamOut->response_number].cardapp;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_for_you_before_(NO_SEGMENT AppliNum, const S_TRANSIN* pParamIn, S_ETATOUT* pParamOut)
{
	(void)pParamIn;

	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = 0;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_licenced_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_KO;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_name_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_OK;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_state_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_OK;
	pParamOut->response_number++;

	return FCT_OK;
}

static int is_time_function_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut)
{
	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname) - 1);
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_KO;
	pParamOut->response_number++;

	return FCT_OK;
}

static int give_your_domain_(NO_SEGMENT AppliNum, S_INITPARAMOUT* pParamOut)
{
	(void)AppliNum;

	// Initialise the output parameter
	memset(&pParamOut->returned_state[pParamOut->response_number], 0,
		sizeof(pParamOut->returned_state[pParamOut->response_number]));

	pParamOut->returned_state[pParamOut->response_number].mask = MSK_ALL_PARAM;
	pParamOut->returned_state[pParamOut->response_number].application_type = TYP_EXPORT;
	pParamOut->response_number++;

	return FCT_OK;
}


static int more_function_(NO_SEGMENT AppliNum)
{
	(void)AppliNum;
	
	TPassMenu_MainMenu ();
			
	return FCT_OK;
}

static int state_(NO_SEGMENT AppliNum)
{
	// Print the version
	PrintAppliVersion(AppliNum, FALSE);

	return FCT_OK;

}


static int give_info_(NO_SEGMENT AppliNum, S_TRANSIN * pParamIn, S_CLESS_GIVEINFO* pParamOut)
{
	TLV_TREE_NODE hOutputTlvTree;
	int nResult;
	
	if (DumpOpenOutputDriver())
	{
		// Print
		DumpData ("CLESS_GIVE_INFO");
		DumpNewLine ();
		DumpNewLine ();

		if (pParamIn->entry != NO_ENTRY)
		{
			// Print
			if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
				DumpData ("\x0f");
			
			DumpData ("S_TRANSIN content :");
			DumpNewLine ();
			DumpData ("Transaction amount = %02lx", pParamIn->amount);
			DumpNewLine ();
			DumpData ("Currency Code = %c%c%c", pParamIn->currency.code[0], pParamIn->currency.code[1], pParamIn->currency.code[2]);
			DumpNewLine ();
			DumpData ("Currency Label = %c%c%c", pParamIn->currency.nom[0], pParamIn->currency.nom[1], pParamIn->currency.nom[2]);
			DumpNewLine ();
			DumpNewLine ();

			if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
				DumpData("\x1b" "@");
		}
	}

	memset (pParamOut, 0, sizeof(*pParamOut));

	// Create the TLV Tree
	hOutputTlvTree = TlvTree_New(0);
	
	// Fill the hOutputTlvTree with the correct parameters (depending on the choosen configuration identifier)
	DllTesting_ParametersManagement_GetParameters(hOutputTlvTree);
	
	if (hOutputTlvTree != NULL)
	{
		// Serialize the TLV Tree in the DEL * of pParamOut
		nResult = TlvTree_Serialize(hOutputTlvTree, TLV_TREE_SERIALIZER_DEFAULT, (unsigned char *)(&(pParamOut->del)), sizeof (_DEL_));
		
		if (nResult < 0)
		{
			memset (&(pParamOut->del), 0, sizeof (_DEL_));
		}

		// Release the TLV Tree
		TlvTree_Release(hOutputTlvTree);
	}
	
	if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
	{
		DumpData("\x1b" "@");
		DumpNewLine ();
		DumpNewLine ();
		DumpNewLine ();
	}
	DumpCloseOutputDriver ();

	return (FCT_OK);
}


static int cless_debit_aid_ (NO_SEGMENT AppliNum, unsigned int nSize, void * pData)
{
	T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT * pSharedStruct;

	(void)AppliNum;
	(void)nSize;
	
	pSharedStruct = (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT *)pData;
		
	if (DumpOpenOutputDriver())
	{
		// Print
		DumpData ("CLESS_DEBIT_AID");
		DumpNewLine ();
		DumpNewLine ();
	}
	
	if (nSize != sizeof (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT))
	{
		DumpData ("Error : nSize not a shared structure");
		DumpNewLine ();
		DumpData ("(nSize = %02x", nSize);
		DumpNewLine ();
		DumpNewLine ();
		
		return CLESS_CR_MANAGER_END;
	}

	DllTesting_DumpData_DumpSharedBuffer (pSharedStruct->pDataStruct, 0);

	if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
	{
		DumpData("\x1b" "@");
		DumpNewLine ();
		DumpNewLine ();
		DumpNewLine ();
	}
	DumpCloseOutputDriver ();

	return (CLESS_CR_MANAGER_END);
}


static int cless_end_ (NO_SEGMENT AppliNum)
{
	if (DumpOpenOutputDriver())
	{
		// Print
		DumpData ("CLESS_END");
		DumpNewLine ();
		DumpNewLine ();
		
		if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
		{
			DumpData("\x1b" "@");
			DumpNewLine ();
			DumpNewLine ();
			DumpNewLine ();
		}
		DumpCloseOutputDriver ();
	}

	return FCT_OK;
}

static int cless_is_for_you_ (NO_SEGMENT AppliNum, unsigned int nSize, void * pData)
{
	T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT * pSharedStruct;
    unsigned char ucPriority;

	(void)AppliNum;
	(void)nSize;

	pSharedStruct = (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT *)pData;

	if (DumpOpenOutputDriver())
	{
		// Print
		DumpData ("CLESS_IS_FOR_YOU ");
		DumpNewLine ();
	}

	if (nSize != sizeof (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT))
	{
		DumpData ("Error : nSize not a shared structure");
		DumpNewLine ();
		DumpData ("(nSize = %02x", nSize);
		DumpNewLine ();
		DumpNewLine ();

		return FCT_OK;
	}

	DllTesting_DumpData_DumpSharedBuffer (pSharedStruct->pDataStruct, 0);

	if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
	{
		DumpData("\x1b" "@");
		DumpNewLine ();
		DumpNewLine ();
	}
	DumpCloseOutputDriver ();

	// Clear the buffer
    GTL_SharedExchange_ClearEx (pSharedStruct->pDataStruct, FALSE);

    /*  The TAG_GENERIC_PRIORITY tag is mandatory for new architecture if
		the application wants to manage the card on CLESS_DEBIT. If the tag
		is not provided, the application will not be called on CLESS_DEBIT,
		even if it returns STOP. */
    // Set the interest level (=priority)
    ucPriority = 30;
    GTL_SharedExchange_AddTag (pSharedStruct->pDataStruct, TAG_GENERIC_PRIORITY, 1, &ucPriority);

	return FCT_OK;
}

static int cless_debit_ (NO_SEGMENT AppliNum, unsigned int nSize, void * pData)
{
	T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT * pSharedStruct;

	(void)AppliNum;
	(void)nSize;
	
	pSharedStruct = (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT *)pData;
		
	if (DumpOpenOutputDriver())
	{
		// Print
		DumpData ("CLESS_DEBIT");
		DumpNewLine ();
		DumpNewLine ();
	}
	
	if (nSize != sizeof (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT))
	{
		DumpData ("Error : nSize not a shared structure");
		DumpNewLine ();
		DumpData ("(nSize = %02x", nSize);
		DumpNewLine ();
		DumpNewLine ();
		
		return CLESS_CR_MANAGER_END;
	}

	DllTesting_DumpData_DumpSharedBuffer (pSharedStruct->pDataStruct, 0);

	if (DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
	{
		DumpData("\x1b" "@");
		DumpNewLine ();
		DumpNewLine ();
		DumpNewLine ();
	}
	DumpCloseOutputDriver ();

	return (CLESS_CR_MANAGER_END);
}





static int Main_(unsigned int nSize, StructPt* pData)
{
	NO_SEGMENT AppliNum;
	int nResult;

	(void)nSize;

	AppliNum = (NO_SEGMENT)ApplicationGetCurrent();
	switch(pData->service)
	{
	case AFTER_RESET:
		nResult = after_reset_(AppliNum, &pData->Param.AfterReset.param_out);
		break;
	case IS_CARD_EMV_FOR_YOU:
		nResult = is_card_emv_for_you_(AppliNum, &pData->Param.IsCardEmvForYou.param_in, &pData->Param.IsCardEmvForYou.param_out);
		break;
	case IS_CARD_SPECIFIC:
		nResult = is_card_specific_(AppliNum, &pData->Param.IsCardSpecific.param_in, &pData->Param.IsCardSpecific.param_out);
		break;
	case IS_CHANGE_INIT:
		nResult = is_change_init_(AppliNum, &pData->Param.IsChangeInit.param_out);
		break;
	case IS_DELETE:
		nResult = is_delete_(AppliNum, &pData->Param.IsDelete.param_out);
		break;
	case IS_EVOL_PG:
		nResult = is_evol_pg_(AppliNum, &pData->Param.IsEvolPg.param_out);
		break;
	case IS_FOR_YOU_AFTER:
		nResult = is_for_you_after_(AppliNum, &pData->Param.IsForYouAfter.param_in, &pData->Param.IsForYouAfter.param_out);
		break;
	case IS_FOR_YOU_BEFORE:
		nResult = is_for_you_before_(AppliNum, &pData->Param.IsForYouBefore.param_in, &pData->Param.IsForYouBefore.param_out);
		break;
	case IS_LICENCED:
		nResult = is_licenced_(AppliNum, &pData->Param.IsLicenced.param_out);
		break;
	case IS_NAME:
		nResult = is_name_(AppliNum, &pData->Param.IsName.param_out);
		break;
	case IS_STATE:
		nResult = is_state_(AppliNum, &pData->Param.IsState.param_out);
		break;
	case IS_TIME_FUNCTION:
		nResult = is_time_function_(AppliNum, &pData->Param.IsTimeFunction.param_out);
		break;
	case GIVE_YOUR_DOMAIN:
		nResult = give_your_domain_(AppliNum, &pData->Param.GiveYourType.param_out);
		break;
	case MORE_FUNCTION:
		nResult = more_function_(AppliNum);
		break;
	case STATE:
		nResult = state_(AppliNum);
		break;
	case IDLE_MESSAGE:
		nResult = idle_message_(AppliNum);
		break;

/*	case AUTO_OVER:
		nResult = auto_over_(AppliNum);
		break;*/
/*	case CARD_INSIDE:
		nResult = card_inside_(AppliNum);
		break;*/
/*	case COM_EVENT:
		nResult = com_event_(AppliNum, &pData->Param.ComEvent.param_in, &pData->Param.ComEvent.param_out);
		break;*/
/*	case CONSULT:
		nResult = consult_(AppliNum);
		break;*/
/*	case DEBIT_EMV:
		nResult = debit_emv_(AppliNum, &pData->Param.DebitEmv.param_in, &pData->Param.DebitEmv.param_out);
		break;*/
/*	case DEBIT_NON_EMV:
		nResult = debit_non_emv_(AppliNum, &pData->Param.DebitNonEmv.param_in, &pData->Param.DebitNonEmv.param_out);
		break;*/
/*	case DEBIT_OVER:
		nResult = debit_over_(AppliNum);
		break;*/
/*	case FALL_BACK:
		nResult = fall_back_(AppliNum, &pData->Param.FallBack.param_in);
		break;*/
/*	case FILE_RECEIVED:
		nResult = file_received_(AppliNum, &pData->Param.FileReceived.param_in);
		break;*/
/*	case GIVE_AID:
		nResult = give_aid_(AppliNum, &pData->Param.GiveAid.param_in, &pData->Param.GiveAid.param_out);
		break;*/
/*	case KEYBOARD_EVENT:
		nResult = keyboard_event_(AppliNum, &pData->Param.KeyboardEvent.param_in, &pData->Param.KeyboardEvent.param_out);
		break;*/
/*	case MCALL:
		nResult = mcall_(AppliNum);
		break;*/
/*	case MESSAGE_RECEIVED:
		nResult = message_received_(AppliNum, &pData->Param.MessageReceived.param_in);
		break;*/
/*	case MODEM_EVENT:
		nResult = modem_event_(AppliNum, &pData->Param.ModemEvent.param_in, &pData->Param.ModemEvent.param_out);
		break;*/
/*	case MODIF_PARAM:
		nResult = modif_param_(AppliNum, &pData->Param.ModifParam.param_in);
		break;*/
/*	case TIME_FUNCTION:
		nResult = time_function_(AppliNum);
		break;*/
/*	case SELECT_AID:
		nResult = select_aid_(AppliNum, &pData->Param.SelectAid.param_in, &pData->Param.SelectAid.param_out);
		break;*/
/*	case TRACK_STREAM:
		nResult = track_stream_(AppliNum, &pData->Param.TrackStream.param_in);
		break;*/
	case CLESS_GIVE_INFO:
		nResult = give_info_ (AppliNum, &pData->Param.ClessGiveInfo.param_in, &pData->Param.ClessGiveInfo.param_out);
		break;
	case CLESS_IS_FOR_YOU:
		nResult = cless_is_for_you_ (AppliNum, nSize, pData);
		break;
	case CLESS_DEBIT:
		nResult = cless_debit_ (AppliNum, nSize, pData); 
		break;
	case CLESS_DEBIT_AID:
		nResult = cless_debit_aid_ (AppliNum, nSize, pData);
		break;
	case CLESS_END:
		nResult = cless_end_ (AppliNum);
		break;
	default:
		nResult = FCT_OK;
		break;
	}

	return nResult;
}

static int give_interface_(unsigned short AppliNum, void* pParamIn, void* pParamOut)
{
	int i;

	(void)pParamIn;
	(void)pParamOut;

	for(i = 0; i < (int)(sizeof(Services) / sizeof(Services[0])); i++)
		Services[i].appli_id = AppliNum;

	ServiceRegister((sizeof(Services) / sizeof(Services[0])), Services);

	return FCT_OK;
}


void entry(void)
{
	object_info_t ObjectInfo;

	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
	give_interface_(ObjectInfo.application_type, NULL, NULL);
}
