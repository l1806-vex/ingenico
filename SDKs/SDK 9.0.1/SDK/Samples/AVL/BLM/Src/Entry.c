/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "VGE_BLM.h"

//// Macros & preprocessor definitions //////////////////////////

#define SERVICES_DEFAULT_PRIORITY		30


//// Static function definitions ////////////////////////////////

void entry(void);

static int PrintAppliVersion(NO_SEGMENT AppliNum, int bFormFeed);

static int after_reset_(NO_SEGMENT AppliNum, S_TRANSOUT* pParamOut);
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
static int file_received_(NO_SEGMENT AppliNum, const S_FILE* pParamIn);
static int idle_message_(NO_SEGMENT AppliNum);
static int Keyboard_event_(NO_SEGMENT AppliNum,S_KEY *InputKey,S_KEY *OutputKey);
static int Main_(unsigned int nSize, StructPt* pData);


extern int Test_BLM(void);

//// Global variables ///////////////////////////////////////////

static const char APP_NAME[] = "BLM SAMPLE";

static service_desc_t Services[] = {
	{ 0, AFTER_RESET, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
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
	{ 0, FILE_RECEIVED, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, STATE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IDLE_MESSAGE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, KEYBOARD_EVENT, (SAP)Main_, SERVICES_DEFAULT_PRIORITY }
};

//// Local Functions //////////////////////////////////////////////////

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
			pprintf("\n\n\n\x0c");

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

//// Functions //////////////////////////////////////////////////

static int after_reset_(NO_SEGMENT AppliNum, S_TRANSOUT* pParamOut)
{
	unsigned char ChangeFlag;
	unsigned char ChangeType;
	
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

	return FCT_OK;
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
	int l_nRet;

	l_nRet = Test_BLM();

	return l_nRet;
}

static int state_(NO_SEGMENT AppliNum)
{
	// Print the version
	PrintAppliVersion(AppliNum, FALSE);

	return FCT_OK;
}

static int file_received_(NO_SEGMENT AppliNum, const S_FILE* pParamIn)
{
	(void)AppliNum;
	(void)pParamIn;
	
    //Parse Received File
	
	return FCT_OK;
}

static int idle_message_(NO_SEGMENT AppliNum)
{
	FILE *hdisp;
	
	hdisp=fopen("DISPLAY","w");
	printf("   BLM SAMPLE   \n   use F key \n");
	fclose(hdisp);
	
	return FCT_OK;
}

static int Keyboard_event_(NO_SEGMENT AppliNum,S_KEY *InputKey,S_KEY *OutputKey)
{
	(void)AppliNum;

	switch(InputKey->keycode)
	{
	case T_NUM0:
	case T_NUM1:
	case T_NUM2:
	case T_NUM3:
	case T_NUM4:
	case T_NUM5:
	case T_NUM6:
	case T_NUM7:
	case T_NUM8:
	case T_NUM9:
	case T_POINT:
	case T_VAL:
	case T_SK2:
	case T_SK3:
	case T_SK1:
	case T_SK4:
		OutputKey->keycode = 0;
		break;
	default:
		OutputKey->keycode = InputKey->keycode;
		break;
	}

	return FCT_OK;
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
	case FILE_RECEIVED:
		nResult = file_received_(AppliNum, &pData->Param.FileReceived.param_in);
		break;
	case IDLE_MESSAGE:
		nResult = idle_message_(AppliNum);
		break;

	case KEYBOARD_EVENT:
		nResult = Keyboard_event_(AppliNum,&pData->Param.KeyboardEvent.param_in,&pData->Param.KeyboardEvent.param_out);
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
