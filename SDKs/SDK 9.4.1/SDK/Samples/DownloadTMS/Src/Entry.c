/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////
#include "SDK30.H"

#include "Communication.h"
#include "Menu.h"

#include "gprs_lib.h"

//// Macros & preprocessor definitions //////////////////////////
#define NUMBER_OF_ITEMS(a)		(sizeof(a)/sizeof((a)[0]))

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////
// int after_reset(NO_SEGMENT AppliNum, void* pParamIn, S_TRANSOUT* pParamOut);
// static int give_your_domain(NO_SEGMENT AppliNum, void* pParamIn, S_INITPARAMOUT* pParamOut);
// static int is_state(NO_SEGMENT AppliNum, void* pParamIn, S_ETATOUT* pParamOut);
// static int is_name(NO_SEGMENT AppliNum, void* pParamIn, S_ETATOUT* pParamOut);
// static int state(NO_SEGMENT AppliNum, void* pParamIn, void* pParamOut);
// static int is_delete(NO_SEGMENT AppliNum, void* pParamIn, S_DELETE* pParamOut);
// static int is_evol_pg(NO_SEGMENT AppliNum, void* pParamIn, S_ETATOUT* pParamOut);
// static int more_function(NO_SEGMENT AppliNum, void* pParamIn, void* pParamOut);
// static int Main(unsigned int nSize, StructPt* pData);
// static int give_interface(NO_SEGMENT AppliNum, void* pParamIn, void* pParamOut);

//// Global variables ///////////////////////////////////////////
static const char APP_NAME[] = "DOWNLOAD TMS";

//// Functions //////////////////////////////////////////////////
int after_reset(NO_SEGMENT AppliNum, void* pParamIn, S_TRANSOUT* pParamOut)
{
	FLAG_CHGT ChangeFlag;
	TYPE_CHGT ChangeType;
	

	// Check for first run
	if (first_init(AppliNum, (unsigned char*)&ChangeFlag, (unsigned char*)&ChangeType) != FSE_FAILED)
	{
		if (ChangeFlag == (FLAG_CHGT)-1)
		{   
			// Cold reset                                                  
			raz_init(AppliNum);
		}
	}

	// !! VG
//	g_nCallingTaskNumber = CurrentTask();
//	fork( TaskWaitNetwork, 0, 0 );

	return FCT_OK;
}

int give_your_domain(NO_SEGMENT AppliNum, void* pParamIn, S_INITPARAMOUT* pParamOut)
{
	pParamOut->returned_state[pParamOut->response_number].mask = MSK_ALL_PARAM;
	pParamOut->returned_state[pParamOut->response_number].application_type = TYP_EXPORT;
	pParamOut->response_number++;
	return FCT_OK;
}

int is_state(NO_SEGMENT AppliNum, void* pParamIn, S_ETATOUT* pParamOut)
{
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_OK;
	return is_name(AppliNum, NULL, pParamOut);
}

int is_name(NO_SEGMENT AppliNum, void* pParamIn, S_ETATOUT* pParamOut)
{
	pParamOut->returned_state[pParamOut->response_number].no_appli = AppliNum;

	// Copy the name
	strncpy(pParamOut->returned_state[pParamOut->response_number].appname, APP_NAME,
		sizeof(pParamOut->returned_state[pParamOut->response_number].appname));
	// Ensure that the ending zero is present
	pParamOut->returned_state[pParamOut->response_number].appname[sizeof(pParamOut->returned_state[pParamOut->response_number].appname)-1] = '\0';

	// Increase the response number
	pParamOut->response_number++;
	return FCT_OK;
}

int state(NO_SEGMENT AppliNum, void* pParamIn, void* pParamOut)
{
	FILE* hPrinter;
	SEGMENT Infos;

	// Get information on the application
	info_seg(AppliNum, &Infos);

	// Open the printer
	hPrinter = fopen("PRINTER", "w-*");
	if (hPrinter != NULL)
	{
		// Print
		pprintf("\x1b" "@\x1b" "E       %s\n\x1b" "@", APP_NAME);
		pprintf("Version : %s\n", Infos.libelle);
		pprintf("CRC     : %04x\n\n", Infos.crc);

		ttestall(PRINTER, 0);
		fclose(hPrinter);
	}

	return FCT_OK;
}

int is_delete(NO_SEGMENT AppliNum, void* pParamIn, S_DELETE* pParamOut)
{
	pParamOut->deleting = DEL_YES;
	return FCT_OK;
}

int is_evol_pg(NO_SEGMENT AppliNum, void* pParamIn, S_ETATOUT* pParamOut)
{
	pParamOut->returned_state[pParamOut->response_number].state.response = REP_OK;
	return is_name(AppliNum, NULL, pParamOut);
}

int more_function(NO_SEGMENT AppliNum, void *p1, void* pParamOut)
{
	ManageMenuMain();
	return FCT_OK;
}

int Main(unsigned int nSize, StructPt* pData)
{
	NO_SEGMENT AppliNum;
	int nResult;

	AppliNum = ApplicationGetCurrent();
	switch(pData->service)
	{
	case AFTER_RESET:
		nResult = after_reset(AppliNum, NULL, &pData->Param.AfterReset.param_out);
		break;
	case GIVE_YOUR_DOMAIN:
		nResult = give_your_domain(AppliNum,NULL, &pData->Param.GiveYourType.param_out);
		break;
	case IS_STATE:
		nResult = is_state(AppliNum, NULL, &pData->Param.IsState.param_out);
		break;
	case IS_NAME:
		nResult = is_name(AppliNum, NULL, &pData->Param.IsName.param_out);
		break;
	case STATE:
		nResult = state(AppliNum, NULL, NULL);
		break;
	case IS_DELETE:
		nResult = is_delete(AppliNum, NULL, &pData->Param.IsDelete.param_out);
		break;
	case IS_EVOL_PG:
		nResult = is_evol_pg(AppliNum, NULL, &pData->Param.IsEvolPg.param_out);
		break;
	case MORE_FUNCTION:
		nResult = more_function(AppliNum, NULL, NULL);
		break;
	default:
		nResult = FCT_OK;
		break;
	}

	return nResult;
}

int give_interface(unsigned short AppliNum, void* pParamIn, void* pParamOut)
{
	service_desc_t Services[] = 
	{
		{ AppliNum, AFTER_RESET, (SAP)Main, 10 },
		{ AppliNum, GIVE_YOUR_DOMAIN, (SAP)Main, 10 },
		{ AppliNum, IS_STATE, (SAP)Main, 10 },
		{ AppliNum, IS_NAME, (SAP)Main, 10 },
		{ AppliNum, STATE, (SAP)Main, 10 },
		{ AppliNum, IS_DELETE, (SAP)Main, 10 },
		{ AppliNum, IS_EVOL_PG, (SAP)Main, 10 },
		{ AppliNum, MORE_FUNCTION, (SAP)Main, 10 } 
	};


	ServiceRegister( NUMBER_OF_ITEMS(Services), Services);

	return FCT_OK;
}

void entry(void)
{
	object_info_t ObjectInfo;

	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
	give_interface(ObjectInfo.application_type, NULL, NULL);

}
