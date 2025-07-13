/** \file Entry.c
 *
 * Application entry point.
 *                   
 * Purpose :
 *
 * Each time Manager calls an application, it generates only one service
 * call that reaches your application main with the corresponding service
 * number.
 *
 * List of routines in file :
 * -  give_your_domain : Return application domain.
 * -  after_reset : Application reset processing.
 * -  is_name : Report application name to Manager.
 * -  is_state : Return application status (initialise or not).
 * -  idle_message : Dedicated to display idle message.
 * -  more_function : Dedicated to navigation menus.
 * -  keyboard_event : Return key pressed.
 * -  state : Print terminal content.
 * -  consult : Print daily totals.
 * -  mcall : Print call schedule.
 * -  is_time_function : Need pheripherals at the next call time_function()
 * -  time_function : Allow automatic execution of periodic functions.
 * -  is_change_init : Conditions for changing manager parameters?
 * -  modif_param : Manager reports parameters changing.
 * -  is_evol_pg : Conditions for application downloading?
 * -  is_delete : Conditions for application deletion?
 * -  file_received : Manager reports parameters file received from LLT.
 * -  message_received : Inter application messaging.
 * -  is_card_specific : Card needs a specific process?
 * -  card_inside : Transaction in progress for a specific card.
 * -  is_for_you_before : Is chip card as an ISO 7816-3?
 * -  is_for_you_after : recognise mag, smc or man card in order to be a candidate.     
 * -  give_interface : Services registration and priority.
 * -  entry : Call by OS for recording services and opening DLL(s). 
 */

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "CST_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define SERVICES_LOW_PRIORITY			30
#define SERVICES_HIGH_PRIORITY			10
#define SERVICES_DEFAULT_PRIORITY		20


/////////////////////////////////////////////////////////////////
//// Static function definition /////////////////////////////////

void entry(void);
static int Main_(unsigned int nSize, StructPt* pData);;
static int give_interface_ (unsigned short AppliNum, void* pParamIn, void* pParamOut);
static int keyboard_event_ (NO_SEGMENT noappli, S_KEY *key_in, S_KEY *key_out);
static int file_received_ (NO_SEGMENT no, S_FILE *param_in);
static int give_money_extended_ (NO_SEGMENT no , void * p1, S_MONEYOUT_EXTENDED * moneyout);


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

static const char APP_NAME[] = "CST";

static service_desc_t Services[] = {
	{ 0, AFTER_RESET, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IDLE_MESSAGE, (SAP)Main_, 60},
	{ 0, IS_DELETE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_NAME, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_STATE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, GIVE_YOUR_DOMAIN, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, MORE_FUNCTION, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, STATE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, FILE_RECEIVED, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, KEYBOARD_EVENT, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, GIVE_MONEY_EXTENDED, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, GIVE_YOUR_SPECIFIC_CONTEXT, (SAP)Main_, SERVICES_DEFAULT_PRIORITY }
};


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief This function get the moneys defined in the parameter file.

static int give_money_extended_ (NO_SEGMENT no , void * p1, S_MONEYOUT_EXTENDED * moneyout)
{
  S_MONEYOUT_EXTENDED money_out;
 
  // Unused parameters
  (void)no;
  (void)p1;
  
  int n_NbMoney;
  S_MONEY_EXTENDED * ps_x_Money;

  memcpy (&money_out, moneyout, sizeof(S_MONEYOUT_EXTENDED));
  strcpy (money_out.etat_retour[money_out.nb_reponse].libelle , (char*)APP_NAME ) ;
  
  CST_Parameters_GetMoneyExtended(&n_NbMoney, &ps_x_Money);
  memcpy(&money_out.etat_retour[money_out.nb_reponse].money[0], ps_x_Money, n_NbMoney * sizeof(S_MONEY_EXTENDED));

  money_out.etat_retour[money_out.nb_reponse].nb_money = n_NbMoney;
  money_out.nb_reponse++;
  memcpy ( moneyout , &money_out , sizeof(S_MONEYOUT_EXTENDED));
  return (FCT_OK) ;
}


//! \brief Manager reports parameters file received from LLT.
//! It's activated upon reception of a parameter file by the manager.
//! \param[in] param_in that contains
//!   - volume_name : SYSTEM (File loaded in CFS), HOST (File loaded in DFS).
//!   - file_name : Application file name
//! \return FCT_OK

static int file_received_ (NO_SEGMENT no, S_FILE *param_in)
{
	int nResult, nSdiResult = SDI_STATUS_UNKNOWN;
	TLV_TREE_NODE hTlvTreeIn = NULL;
	TLV_TREE_NODE hTlvTreeOut = NULL;
	TLV_TREE_NODE pTlvTreeSha;
	
	
	(void) no;

	// Try to read parameter file and store it into an internal TLV tree structure
	nResult = CST_Parameters_ReadXMLFile((char*)param_in->volume_name, (char*)param_in->file_name, &hTlvTreeIn);
	if (nResult == STOP) // Inputed file is a parameter file 
	{
		// Load the parameters into the intelligent reader
		nSdiResult = SDI_Payment_LoadParams (nSDSAAppliId, hTlvTreeIn, &hTlvTreeOut);

		if(nSdiResult == SDI_STATUS_OK)
		{
			// Parameters are correctly loaded in the intelligent reader
			// Copy the given parameters in the current parameters
			CST_Parameters_InitParameters(&pTreeCurrentParam);
			pTreeCurrentParam = TlvTree_Copy(hTlvTreeIn);

			// Get and save the calculated SHA. This SHA will allow the terminal to check if the parameters loaded in the reader are coherent with its ones.
			if (hTlvTreeOut != NULL)
			{
				// CST_DumpData_DumpTlvTreeNodeWithTitle ("LoadParams return", hTlvTreeOut);
				
				pTlvTreeSha = TlvTree_Find(hTlvTreeOut, TAG_SDSA_LOADED_PARAMETERS_SHA, 0);
				if(pTlvTreeSha != NULL)
				{
					*CST_Parameters_GetShaLength() = TlvTree_GetLength(pTlvTreeSha);
					memcpy(CST_Parameters_GetSha(), TlvTree_GetData(pTlvTreeSha), *CST_Parameters_GetShaLength());
				}

				TlvTree_ReleaseEx (&hTlvTreeOut);
			}

			// Save the parameters into a file (CLESSPARAM.PAR)
			if (CST_Parameters_SaveParam (pTreeCurrentParam, CST_Parameters_GetSha(), *CST_Parameters_GetShaLength()) != 0)
				GTL_Traces_TraceDebug("file_received_ : CST_Parameters_SaveParam() error");				
			
			CST_Parameters_CheckCaKeysCrc(pTreeCurrentParam);
		}
		
		TlvTree_ReleaseEx (&hTlvTreeIn);

		// New parameters, update some values
		CST_VisaWave_SetVisaAsiaGuiMode();
		CST_Interac_SetInteracGuiMode();
		CST_Parameters_GetMoneyExtendedFromParameters();

		goto End;
	}

	// Try to read black List parameter
	nResult = CST_BlackListGetNewFile(param_in->volume_name, param_in->file_name, &hTlvTreeIn);
	if (nResult) // Inputed file is a Black list parameter file 
	{
		// Load the blacklist into the intelligent reader
		nSdiResult = SDI_Payment_LoadParams (nSDSAAppliId, hTlvTreeIn, &hTlvTreeOut);
		
		if (hTlvTreeOut != NULL)
		{
			// CST_DumpData_DumpTlvTreeNodeWithTitle ("LoadParams return", hTlvTreeOut);
			TlvTree_ReleaseEx (&hTlvTreeOut);
		}

		TlvTree_ReleaseEx (&hTlvTreeIn);

		goto End;
	}

End:
	if(nSdiResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();

	return (nResult);
}


//! \brief Print the application version.

static int PrintAppliVersion(NO_SEGMENT AppliNum, int bFormFeed)
{
	int nResult;
	FILE* hPrinter;
	SEGMENT Infos;
	unsigned char Status;
	object_info_t info;

	// Get information on the application
	info_seg(AppliNum, &Infos);

	if (ObjectGetInfo  (OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &info) == 0)
	{
		// Open the printer
		hPrinter = fopen("PRINTER", "w-*");
		if (hPrinter != NULL)
		{
			// Print
			pprintf("\x1b" "@\n\x1b" "E%s\n\x1b" "@", APP_NAME);
			pprintf("Version : %s\n", (info.name));
			pprintf("CRC     : %04X\n\n", Infos.crc);

			if (bFormFeed)
				pprintf("\n\n\n\n\x0c");

			ttestall(PRINTER, 0);

			status(hPrinter, &Status);
			if ((Status & (PRINT_ERROR | PAPER_OUT)) != 0)
				nResult = STOP;
			else nResult = FCT_OK;

			fclose(hPrinter);
		}
		else nResult = FCT_OK;
	}
	else nResult = FCT_OK;

	return nResult;
}


//! \brief Function called when the device reset.

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

	// Open the SDI DLL (to communicate with the intelligent reader)
	SDIlib_open();

	// Try to restore parameters from saved files (parameters value and calculated sha)
	if (CST_Parameters_RestoreParam (&pTreeCurrentParam, CST_Parameters_GetSha(), CST_Parameters_GetShaSize(), CST_Parameters_GetShaLength()) != 0)
	{
		GTL_Traces_TraceDebug("after_reset_ : CST_Parameters_RestoreParam KO");
		
		// Cannot restore parameters, read default parameters
		CST_Parameters_ReadDefaultParameters(&pTreeDefaultParam);
		if (CST_Parameters_SaveParam (pTreeDefaultParam, NULL, 0) != 0)
		{
			GTL_Traces_TraceDebug("after_reset_ : CST_Parameters_SaveParam KO");
		}
		else // Parameter has been correctly loaded/saved
		{
			CST_Parameters_InitParameters(&pTreeCurrentParam);
			pTreeCurrentParam = pTreeDefaultParam; // Update pTreeCurrentParam for later use...
			pTreeDefaultParam = NULL;
		}
	}
	
	// Create or restore the batch
	CST_Batch_Restore ();

	CST_Disk_Open(FILE_DISK_LABEL, FILE_DISK_MODE, FILE_DISK_ACCESS_MODE, FILE_DISK_MAX_NUM_OF_FILES, FILE_DISK_SIZE);

	// Init the transaction sequence counter
	CST_Batch_InitTransactionSeqCounter(FALSE);

	CST_DumpData_InitOutput();

	// Wait during the intelligent reader is reseting
	ttestall(0,200);

	// Establishe the connection with the intelligent reader
	//SDI_System_Connect("USB");
	//SDI_System_Connect("COM0");
	CST_Term_ConnectAll();
	
	// Initialise Messages menagement
	CST_Term_Initialise();

	// Set some values according to current parameters
	CST_VisaWave_SetVisaAsiaGuiMode();
	CST_Interac_SetInteracGuiMode();
	CST_Parameters_GetMoneyExtendedFromParameters();

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

	// Compare parameters version between the terminal and the intelligent reader (update if needed)
	CST_Parameters_CheckConsistency();

	// If Manager language has been modified, update the terminal and reader languages too
	CST_Term_SetMerchantLanguage();

	return FCT_OK;
}


/** Enable CGUI mode of the manager for this application. 
* \param    param_out (-O) Set the CGUI flag. 
* \return                                            
*  FCT_OK 
* \header sdk30.h 
* \source entry.c  
*/ 
static int give_your_specific_context_(NO_SEGMENT No, S_SPECIFIC_CONTEXT *param_out) 
{ 
	// Initialise the output parameter 
	memset(&param_out->returned_state[param_out->response_number], 0, 
		sizeof(param_out->returned_state[param_out->response_number])); 

	// The name of the resource file 
	strcpy(param_out->returned_state[param_out->response_number].appname, "844084----"); 
	param_out->returned_state[param_out->response_number].no_appli = No; 
	param_out->returned_state[param_out->response_number].mask = 0; 
	param_out->returned_state[param_out->response_number].type = 0; 
	param_out->returned_state[param_out->response_number].support = 0; 
	param_out->returned_state[param_out->response_number].cam = 0; 

	// The application is CGUI compliant 
	param_out->returned_state[param_out->response_number].cgui = CGUI_MASK; 
	param_out->response_number++; 

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
	int nOldStateHeader;
	
	(void)AppliNum;

	nOldStateHeader = StateHeader(0);

	// Display the menu of the CST application
	CST_Menu_MainMenuDisplay();

	StateHeader(nOldStateHeader);
	
	return FCT_OK;
}


//! \brief F4 key allows to enter an amount and start a contactless transaction with the intelligent reader.

static int keyboard_event_ (NO_SEGMENT noappli, S_KEY *key_in, S_KEY *key_out)
{
	int nOldStateHeader;

	(void) noappli;

	/// Keyboard management
	switch (key_in->keycode)
	{
	case N0: case N1: case N2: case N3: case N4: 
	case N5: case N6: case N7: case N8: case N9: 
	case T_VAL : case T_POINT : 
		key_out->keycode=key_in->keycode;   ///< Inhibit these keys to Manager for International domain
		break; 
	case F4 :
		nOldStateHeader = StateHeader(0);
	
		// Start the transaction
		CST_Tests_DoTransaction();

		key_out->keycode = 0;

		StateHeader(nOldStateHeader);
		break;
	case F1 : case F2 : case F3 : 
	case T_CORR : case T_ANN : case NAVI_CLEAR : case NAVI_OK : 
	case UP : case DOWN :  
	case T_F :                              ///< do not filter F key and return the same key ! 
		key_out->keycode=key_in->keycode;   ///< Return the same key value for keys above ! 
		break; 
	default :
		key_out->keycode=key_in->keycode;
		break;
	}

	return (FCT_OK);
}


static int state_(NO_SEGMENT AppliNum)
{
	// Print the version
	PrintAppliVersion(AppliNum, FALSE);

	return FCT_OK;
}


static int idle_message_(NO_SEGMENT AppliNum)
{
	static const char* szMessage1 = "C'Less Testing";
	static const char* szMessage2 = "Press 'F4' key";
	FILE *hDisplay;
	int nOldFont;
	int nOldFontType;
	int nScreenHeight;
	int nScreenWidth;
	int nWidth;
	int nX;
	int nY;

	(void)AppliNum;

	if (SDI_System_IsConnected() == SDI_STATUS_OK)
	{
		hDisplay = fopen("DISPLAY", "w");
		
		// Create the display context
		InitContexteGraphique(PERIPH_DISPLAY);
		GetScreenSize(&nScreenHeight, &nScreenWidth);
		nOldFont = GetFont();
		nOldFontType = GetType();
		SetType(_PROPORTIONNEL_);
		
		if (IsHeader())
			nY = 27;
		else nY = 18;
		
		// Clear the screen
		_clrscr();
		
		// Display the first message
		SetFont(_LARGE_);
		nWidth = StringWidth((char*)szMessage1);
		if (nWidth <= nScreenWidth)
			nX = (nScreenWidth - nWidth) / 2;
		else nX = 0;
		_DrawString((char*)szMessage1, nX, nY, _OFF_);
		nY += GetPoliceSize();
		
		// Display the second message
		SetFont(_SMALL_);
		nY += GetPoliceSize();
		nWidth = StringWidth((char*)szMessage2);
		if (nWidth <= nScreenWidth)
			nX = (nScreenWidth - nWidth) / 2;
		else nX = 0;
		_DrawString((char*)szMessage2, nX, nY, _OFF_);
		nY += GetPoliceSize();

		// Refresh the screen
		PaintGraphics();

		// Reset the font
		SetFont(nOldFont);
		SetType(nOldFontType);
		fclose(hDisplay);

		// Set the intelligent reader in idle state (display the WELCOME message)
		if (CST_Interac_IsInteracGuiMode())
		{
			CST_DisplayScreen (SDSA_INTERAC_SCREEN_IDLE);
		}
		else
		{
			CST_DisplayScreen (SDSA_SCREEN_IDLE);
		}
	}
	else
	{
		CST_ReconnectionProcess();
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
	case IS_DELETE:
		nResult = is_delete_(AppliNum, &pData->Param.IsDelete.param_out);
		break;
	case IS_NAME:
		nResult = is_name_(AppliNum, &pData->Param.IsName.param_out);
		break;
	case IS_STATE:
		nResult = is_state_(AppliNum, &pData->Param.IsState.param_out);
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
	case FILE_RECEIVED:
		nResult = file_received_(AppliNum, &pData->Param.FileReceived.param_in);
		break;
	case KEYBOARD_EVENT:
		nResult = keyboard_event_ (AppliNum, &pData->Param.KeyboardEvent.param_in, &pData->Param.KeyboardEvent.param_out);
		break;
	case GIVE_MONEY_EXTENDED:
		nResult = give_money_extended_(AppliNum, NULL, &pData->Param.GiveMoneyExtended.param_out);
		break;
	case GIVE_YOUR_SPECIFIC_CONTEXT: 
		nResult = give_your_specific_context_(AppliNum,&pData->Param.GiveYourSpecificContext.param_out); 
        break; 

	default:
		nResult = FCT_OK;
		break;
	}

	return nResult;
}



//! \brief Services registration and priority.  
//! For all services except idle_message, priority => 0x00 highest and 0xFF lowest
//! For idle_message, priority => 0x00 lowest 0xFF highest

static int give_interface_ (unsigned short AppliNum, void* pParamIn, void* pParamOut)
{
	int i;

	(void)pParamIn;
	(void)pParamOut;

	for(i = 0; i < (int)(sizeof(Services) / sizeof(Services[0])); i++)
		Services[i].appli_id = AppliNum;

	ServiceRegister((sizeof(Services) / sizeof(Services[0])), Services);

	// Security DLL open 
	SEClib_Open();

	return FCT_OK;
}



//! \brief entry() is called by the OS for recording services and opening DLL(s).                   
//! The RegisteryPowerFailure() can also be moved to entry().

void entry(void)
{
	object_info_t ObjectInfo;

	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
	give_interface_(ObjectInfo.application_type, NULL, NULL);
}
