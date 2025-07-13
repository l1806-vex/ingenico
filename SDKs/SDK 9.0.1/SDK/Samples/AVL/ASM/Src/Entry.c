/////////////////////////////////////////////////////////////////
/////////				Includes				/////////////////
/////////////////////////////////////////////////////////////////

#include "SDK30.h"
#include "VGE_ASM.h"
#include "VGE_UIM.h"

//////////////	 Macros & preprocessor definitions		///////////////

#define SERVICES_DEFAULT_PRIORITY		32

#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))


/////////////////	 Static function definitions	///////////////////

void entry(void);

static int after_reset_(NO_SEGMENT AppliNum, S_TRANSOUT* pParamOut);
static int is_delete_(NO_SEGMENT AppliNum, S_DELETE* pParamOut);
static int is_name_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_state_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int is_time_function_(NO_SEGMENT AppliNum, S_ETATOUT* pParamOut);
static int give_your_domain_(NO_SEGMENT AppliNum, S_INITPARAMOUT* pParamOut);
static int more_function_(NO_SEGMENT AppliNum);
static int state_(NO_SEGMENT AppliNum);
static int idle_message_(NO_SEGMENT AppliNum);
static int Main_(unsigned int nSize, StructPt* pData);
static int Main_App_(unsigned int nSize, ASM_t_ExecuteTaskPt* pData);
static int PrintAppliVersion(NO_SEGMENT AppliNum, int bFormFeed);

/////////////////	 Extern function definitions	///////////////////

extern void L_CalculateDeltaDate (void);
extern void L_CreateCalandar( void );
extern void L_DeleteCalandar( void );
extern void L_ActivateCalendar( void );
extern void L_AddTask( void );
extern void L_ModifyTask( void );
extern void L_DeleteTask( void );
extern void L_IsTaskExist( void );
extern void L_GetNextTaskInfo( void );
extern void L_GetTaskInfo( void );

extern int execute_task(unsigned short i_usTaskId);

////////////////		Global variables			///////////////////

NO_SEGMENT AppliNum;
object_info_t ObjectInfo;

static const char APP_NAME[] = "ASM SAMPLE";

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
	{ 0, TIME_FUNCTION, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, I_EXECUTE_TASK, (SAP)Main_App_, SERVICES_DEFAULT_PRIORITY }
};

/////////////////////////////////////////////////////////////////////////
///////////////			 Local Functions			/////////////////////
/////////////////////////////////////////////////////////////////////////


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


///////////////////////////////////////////////////////////
/////  			  ENTRY POINT FUNCTIONS		    	  /////
///////////////////////////////////////////////////////////


/**
 * @function:    after_reset_ 
 * @description: This module performs the initialisation of the application
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       - AppliNum : application number 
 *               - param_in : not used
 * @param out:   See doc M²OS Multi Application Manager 
 * @return:      Always FCT_OK   
 * @execption: 
 *-----------------------------------------------------------------------------
 */
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


/**
 * @function:    is_delete_ 
 * @description: actions before deleting application 
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       - AppliNum : application number 
 *               - pParamOut : not used
 * @param out:   See doc M²OS Multi Application Manager 
 * @return:      Always FCT_OK   
 * @execption: 
 *-----------------------------------------------------------------------------
 */
static int is_delete_(NO_SEGMENT AppliNum, S_DELETE* pParamOut)
{
	(void)AppliNum;

	// Initialise the output parameter
	memset(pParamOut, 0, sizeof(*pParamOut));

	/////////////////////////////////////////////////////////////////////////////
	// !!!!				Delete the application calendar                    !!!!//
	// !!!! This service must be called here to avoid calendar duplication !!!!//
	/////////////////////////////////////////////////////////////////////////////
	ASM_DeleteCalendar(ObjectInfo.application_type);

	pParamOut->deleting = DEL_YES;

	return FCT_OK;
}


/**
 * @function:    is_name_ 
 * @description: This service returns the name of the application.
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       - AppliNum : application number 
 *               - pParamOut : not used
 * @param out:   See doc M²OS Multi Application Manager 
 * @return:      Always FCT_OK   
 * @execption: 
 *-----------------------------------------------------------------------------
 */
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


/**
 * @function:    is_state_ 
 * @description: gives application state   
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       - AppliNum : application number 
 *               - pParamOut : not used
 * @param out:   See doc M²OS Multi Application Manager 
 * @return:      Always FCT_OK   
 * @execption: 
 *-----------------------------------------------------------------------------
 */
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


/**
 * @function:    is_time_function_ 
 * @description: This service informs the manager that the application 
 *               has a periodic function to be executed. 
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       - AppliNum : application number 
 *               - param_out : not used
 * @param out:   See doc M²OS Multi Application Manager 
 * @return:      Always FCT_OK   
 * @execption: 
 *-----------------------------------------------------------------------------
 */
static int is_time_function_(NO_SEGMENT noappli, S_ETATOUT* param_out)
{
	S_ETATOUT etatout;
	int       retour;
	memcpy(&etatout, param_out, sizeof(etatout));
	etatout.returned_state[etatout.response_number].state.response=REP_OK;
	memcpy(param_out,&etatout,sizeof(etatout));
	retour = is_name_ (noappli, param_out);
	return(FCT_OK);		 
}


/**
 * @function:    time_function_ 
 * @description: This service start périodic call (used here for debug).
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       application number 
 * @param out:   See doc M²OS Multi Application Manager
 * @return:      Always FCT_OK   
 * @execption: 
 *-----------------------------------------------------------------------------
 */
int time_function_ (NO_SEGMENT noappli)
{	
	return FCT_OK;
}


/**
 * @function:    give_your_domain_ 
 * @description: This service gives the application domain
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       - AppliNum : application number 
 *               - param_out : not used
 * @param out:   See doc M²OS Multi Application Manager
 * @return:      Always FCT_OK   
 * @execption: 
 *-----------------------------------------------------------------------------
 */
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

/**
 * @function:    more_function_ 
 * @description: This service manages the application menu 
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       application number 
 * @param out:   See doc M²OS Multi Application Manager
 * @return:      Always FCT_OK   
 * @execption: 
 *-----------------------------------------------------------------------------
 */
static int more_function_(NO_SEGMENT AppliNum)
{
	int l_nRet;

	UIM_t_navigate_menu l_x_NavigateMenu[] =
	{
		{"ASM SAMPLE",			"0",		0,	PT_NULL},
		{"Calcul. delta date",	"1",		1,	(PFONCNAVI)L_CalculateDeltaDate},
		{"Create calendar",		"2",		1,	(PFONCNAVI)L_CreateCalandar},
		{"Delete calendar",		"3",		1,	(PFONCNAVI)L_DeleteCalandar},
		{"Activate calendar",	"4",		1,	(PFONCNAVI)L_ActivateCalendar},
		{"Add task",			"5",		1,	(PFONCNAVI)L_AddTask},
		{"Modify task",			"6",		1,	(PFONCNAVI)L_ModifyTask},
		{"Delete task",			"7",		1,	(PFONCNAVI)L_DeleteTask},
		{"Task exist",			"8",		1,	(PFONCNAVI)L_IsTaskExist},
		{"Get next task info",	"9",		1,	(PFONCNAVI)L_GetNextTaskInfo},
		{"Get task info",		"10",		1,	(PFONCNAVI)L_GetTaskInfo},
	};
	
	UIM_t_navigate_option l_x_NavigateOption = {
		30,						/*time out in second*/
		1,						/*offset*/
		0,						/*radio button*/
		UIM_DISPLAY_MESSAGE,	/*action to do after time out*/
		0,						/*default choice*/
		"Time Out",				/*message to display after time out*/
		UIM_CONTINUE_AFTER_FCT	/*Action to do after the execution of the function*/
	};

	l_nRet = UIM_NavigateService(l_x_NavigateMenu,NUMBER_OF_ITEMS(l_x_NavigateMenu),&l_x_NavigateOption);

	return FCT_OK;
}

/**
 * @function:    state_ 
 * @description: prints the application info and status 
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       - AppliNum : application number 
 * @param out:   See doc M²OS Multi Application Manager 
 * @return:      Always FCT_OK   
 * @execption: 
 *-----------------------------------------------------------------------------
 */
static int state_(NO_SEGMENT AppliNum)
{
	// Print the version
	PrintAppliVersion(AppliNum, FALSE);

	return FCT_OK;
}


/**
 * @function:    idle_message_ 
 * @description: This service define the application idle message
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       application number 
 * @param out:   See doc M²OS Multi Application Manager  
 * @return:      Always FCT_OK   
 * @execption: 
 *-----------------------------------------------------------------------------
 */
static int idle_message_(NO_SEGMENT AppliNum)
{
	FILE *hdisp;
	
	hdisp=fopen("DISPLAY","w");
	printf("   ASM SAMPLE   \n   use F key \n");
	fclose(hdisp);
	
	return FCT_OK;
}

/**
 * @function:    Main_App_ 
 * @description: call the execute task entry point.
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       Paremeters exchanged bewtween calendar and application
 * @param out:    
 * @return:      Exction Result =   ASM_SUCCESS or ASM_CALL_FAILURE
 * @execption: 
 *-----------------------------------------------------------------------------
 */
static int Main_App_(unsigned int nSize, ASM_t_ExecuteTaskPt * pData)
{
	int nResult = 0;

	nResult = execute_task(pData->i_usTaskToExecute);
	pData->o_nAppliStatus = nResult;

	return FCT_OK;
}


/**
 * @function:    Main_ 
 * @description: Call entry points
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       Paremeters exchanged bewtween manager and application
 * @param out:    
 * @return:      
 * @execption: 
 *-----------------------------------------------------------------------------
 */
static int Main_(unsigned int nSize, StructPt* pData)
{
	int nResult;

	(void)nSize;

	AppliNum = (NO_SEGMENT)ApplicationGetCurrent();
	switch(pData->service)
	{
	case AFTER_RESET:
		nResult = after_reset_(AppliNum, &pData->Param.AfterReset.param_out);
		break;
	case IS_DELETE:
		nResult = is_delete_(AppliNum, &pData->Param.IsDelete.param_out);
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
	case TIME_FUNCTION:
		nResult =time_function_(AppliNum);
		break;

	default:
		nResult = FCT_OK;
		break;
	}

	return nResult;
}

/**
 * @function:    give_interface_ 
 * @description: call service proposed by application
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       application number ,...
 * @param out:   See doc M²OS Multi Application Manager  
 * @return:      Always FCT_OK   
 * @execption: 
 *-----------------------------------------------------------------------------
 */
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


/**
 * @function:    entry 
 * @description: Apllication entry
 * @see: 
 * @author: 
 *-----------------------------------------------------------------------------
 * @param:       
 * @param out:   See doc M²OS Multi Application Manager   
 * @return:      void 
 * @execption: 
 *-----------------------------------------------------------------------------
 */
void entry(void)
{
	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
	give_interface_(ObjectInfo.application_type, NULL, NULL);
}



