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
 * -  cless_give_info : contactless parameters for each contactless application.  
 * -  cless_debit_aid : contactless debit with AID allready selected.  
 * -  give_interface : Services registration and priority.
 * -  entry : Call by OS for recording services and opening DLL(s). 
 */


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDSA_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define SERVICES_LOW_PRIORITY			30
#define SERVICES_HIGH_PRIORITY			10
#define SERVICES_DEFAULT_PRIORITY		20


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

void entry(void);
static int Main_(unsigned int nSize, StructPt* pData);
static int give_your_domain_ (NO_SEGMENT no, S_INITPARAMOUT *param_out);
static int give_money_extended_ (NO_SEGMENT no , void * p1, S_MONEYOUT_EXTENDED * moneyout);
static int after_reset_ (NO_SEGMENT no, S_TRANSOUT *param_out);
static int is_name_(NO_SEGMENT no, S_ETATOUT *param_out);
static int is_state_(NO_SEGMENT no, S_ETATOUT *param_out);
static int give_interface_ (unsigned short AppliNum, void* pParamIn, void* pParamOut);
static int custom_kernel_ (unsigned int nSize, void * pData);

static int g_nTheServiceResult = SDI_STATUS_OK;
static TLV_TREE_NODE g_nTheServiceOuputTlvTree = NULL;

static int __SDSAServicesTlvTree (unsigned int nSize, SDM_SERVICE_HEADER* pData);
static int __SDSAServices_CancelTransaction (unsigned int nSize, SDM_SERVICE_HEADER* pData);
static int __SDSAServices_ReaderDisconnected (unsigned int nSize, SDM_SERVICE_HEADER* pData);
static int __SDSAServices_ReaderConnected (unsigned int nSize, SDM_SERVICE_HEADER* pData);
static void __SDSA_SetResult (int nResult);
static int __SDSA_GetResult (void);
static void __SDSA_SetOutputTlvTree (TLV_TREE_NODE hOutputTlvTree);
static TLV_TREE_NODE __SDSA_GetOutputTlvTree(void);


/////////////////////////////////////////////////////////////////

static service_desc_t Services[] = {
	{ 0, AFTER_RESET, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, IS_STATE, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, GIVE_YOUR_DOMAIN, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, GIVE_MONEY_EXTENDED, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_CUSTOM_KERNEL, (SAP)custom_kernel_, SERVICES_DEFAULT_PRIORITY },
	{ 0, SELECT_FUNCTION_EMV, (SAP)Main_, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_STATE_READER_CONNECTED, (SAP)__SDSAServices_ReaderConnected, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_STATE_READER_DISCONNECTED, (SAP)__SDSAServices_ReaderDisconnected, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_DO_TXN, (SAP)__SDSAServicesTlvTree, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_TXN_POST_PROCESSING, (SAP)__SDSAServicesTlvTree, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_CANCEL_TXN, (SAP)__SDSAServices_CancelTransaction, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_LOAD_PARAMS, (SAP)__SDSAServicesTlvTree, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_GET_PARAMS, (SAP)__SDSAServicesTlvTree, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_ERASE_PARAMS, (SAP)__SDSAServicesTlvTree, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_GET_DATA, (SAP)__SDSAServicesTlvTree, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_CLEAR_DATA, (SAP)__SDSAServicesTlvTree, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_SET_GUI_STATE, (SAP)__SDSAServicesTlvTree, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_GET_STATUS, (SAP)__SDSAServicesTlvTree, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_GET_STATUS_CANCEL, (SAP)SDSA_Status_GetStatusCancel, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_PAYMENT_CARD_REMOVAL, (SAP)__SDSAServicesTlvTree, SERVICES_DEFAULT_PRIORITY },
	{ 0, SERVICE_GENERIC_USER_CMD_01, (SAP)__SDSAServicesTlvTree, SERVICES_DEFAULT_PRIORITY }
};

static const char appName[] = "SDSA";

static int gs_bParamInitDone = FALSE;
static int gs_nHeaderEventMask;


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
  strcpy (money_out.etat_retour[money_out.nb_reponse].libelle , (char*)appName ) ;
  
  SDSA_Parameters_GetMoneyExtended(&n_NbMoney, &ps_x_Money);
  memcpy(&money_out.etat_retour[money_out.nb_reponse].money[0], ps_x_Money, n_NbMoney * sizeof(S_MONEY_EXTENDED));

  money_out.etat_retour[money_out.nb_reponse].nb_money = n_NbMoney;
  money_out.nb_reponse++;
  memcpy ( moneyout , &money_out , sizeof(S_MONEYOUT_EXTENDED));
  return (FCT_OK) ;
}


//! \brief Report application name to Manager.
//! \param[out] param_out that contains:
//!   - appname : Application name 
//!   - no : Application number
//!   - response_number : should be incremented
//! \return FCT_OK

static int is_name_(NO_SEGMENT no, S_ETATOUT *param_out)
{
	strcpy(param_out->returned_state[param_out->response_number].appname, appName);
	param_out->returned_state[param_out->response_number].no_appli = no;
	param_out->response_number++;

	return (FCT_OK);
}


static int is_state_(NO_SEGMENT no, S_ETATOUT *param_out)
{
	int retour; 
	
	/// Return application state
	param_out->returned_state[param_out->response_number].state.response = REP_OK;
	retour = is_name_ (no, param_out);
	
	// Parameters control checking
	if (!gs_bParamInitDone)
	{
		SDSA_Parameters_CreateSupportedCertificateListForKernel (pTreeCurrentParam, DEFAULT_EP_KERNEL_PAYPASS);
		SDSA_Parameters_CreateSupportedCertificateListForKernel (pTreeCurrentParam, DEFAULT_EP_KERNEL_AMEX);
		SDSA_Parameters_BuildAIDNodes(pTreeCurrentParam);
		
		// Here to be done just one time
		// Test if the VisaWave kernel is present
		if(VisaWave_Clear() != KERNEL_STATUS_SERVICE_NOT_AVAILABLE)
			SDSA_VisaWave_SetVisaWaveKernelPresence();
		
		SDSA_VisaWave_SetVisaAsiaGuiMode();

		// Check in the parameter file if the quick GUI mode is activated or not (if yes the GUI time will be minimized)
		SDSA_GuiState_SetQuickGUIMode();
		
		gs_bParamInitDone = TRUE;
	}

	// Remove Application name on the header
	EventHeader (gs_nHeaderEventMask ^ _APPLI_STATE_);

	return (retour);
}


static int give_your_domain_ (NO_SEGMENT no, S_INITPARAMOUT *param_out)
{
	(void) no;

    /// Return application domain to Manager
	/// Setting parameters initialisation
	param_out->returned_state[param_out->response_number].mask = MSK_MDP|MSK_SWIPE|MSK_TYPE_PPAD|MSK_PINPAD|MSK_STANDARD|MSK_LANGUE|MSK_FRMT_DATE|MSK_DATE;
    /// International domain
	param_out->returned_state[param_out->response_number].application_type = TYP_EXPORT;
	param_out->response_number++;

	return (FCT_OK);
}


//! \brief Function called when the device reset. Initialise data and create disks

static int after_reset_ (NO_SEGMENT no, S_TRANSOUT *param_out)
{
    unsigned char chgt;
	TYPE_CHGT  type;

	(void)param_out;

	TPasslib_open();	///< TPass DLL Library
	
	/// Reset management
	first_init(no, &chgt, (unsigned char *)&type);	///< New software loaded ?
	if (chgt==0xFF)									///< Yes, just loaded with first execution
	{ 
        raz_init(no);								///< Reset indicator downloading
	}
	
	// Try to restore parameters from a saved file
	if (SDSA_Parameters_RestoreParam (&pTreeCurrentParam) != 0)
	{
		GTL_Traces_TraceDebug("after_reset_ : SDSA_Parameters_RestoreParam KO");
	}
	
	SDSA_Disk_Open(FILE_DISK_LABEL, FILE_DISK_MODE, FILE_DISK_ACCESS_MODE, FILE_DISK_MAX_NUM_OF_FILES, FILE_DISK_SIZE);

	// Try to load black list parameters if existing
	SDSA_BlackListLoad();

	// Indicate parameters initialisation has to be done (organize AID structure for selection, check VisaWave kernel presence, IHM Mode to use...)
	gs_bParamInitDone = FALSE;

	// Initialise the message management
	SDSA_Term_Initialise();

	// Set the LEDs into the idle state
	HelperLedsIdleState();

	SDSA_Common_SetTransactionMode (SDSA_COMMON_MODE_NONE);

	// Initialise the transaction status
	SDSA_State_Initialisation();
	SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_NOT_STARTED);

	return FCT_OK;
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



//! \brief This service is called by the contactless kernels for customisation processing.
//! This is the application that provide kernel the service and the application type to call for customisation. 
//! \param[in] nSize Size of \a pData (not used as \a pData is a shared service call struct).
//! \param[in,out] pData Data buffer to be used to get and provide data to the kernel.  

static int custom_kernel_ (unsigned int nSize, void * pData)
{
	int nResult;
	T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT * pSharedStruct;

	(void) nSize;
	
	pSharedStruct = (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT *)pData;

	// Call the customisation depending on the kernel used
    nResult = SDSA_Customisation_Process (pSharedStruct->pDataStruct);
    
	return (nResult);
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
	case IS_STATE:
		nResult = is_state_(AppliNum, &pData->Param.IsState.param_out);
		break;
	case GIVE_YOUR_DOMAIN:
		nResult = give_your_domain_(AppliNum, &pData->Param.GiveYourType.param_out);
		break;
	case GIVE_MONEY_EXTENDED:
		nResult = give_money_extended_(AppliNum, NULL, &pData->Param.GiveMoneyExtended.param_out);
		break;
	default:
		nResult = FCT_OK;
		break;
	}

	return nResult;
}



#ifdef __cplusplus
extern "C" {
#endif

//! \brief entry() is called by the OS for recording services and opening DLL(s).                   
//! The RegisteryPowerFailure() can also be moved to entry().

void entry(void)
{
	object_info_t info;
	
	gs_nHeaderEventMask = EventHeader (0); // To get the initial Header Event Mask and to set the current to 0
	EventHeader (gs_nHeaderEventMask); // Restore the Header Event mask

	// Recording services
	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&info);
	give_interface_(info.application_type, NULL, NULL);
}

#ifdef __cplusplus
}
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// Intelligent Reader new services ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

static void __SDSA_SetResult (int nResult)
{
	g_nTheServiceResult = nResult;
}

static int __SDSA_GetResult (void)
{
	return (g_nTheServiceResult);
}

static void __SDSA_SetOutputTlvTree (TLV_TREE_NODE hOutputTlvTree)
{
	// Delete the previous output TlvTree
	TlvTree_ReleaseEx(&g_nTheServiceOuputTlvTree);
	g_nTheServiceOuputTlvTree = hOutputTlvTree;
}

static TLV_TREE_NODE __SDSA_GetOutputTlvTree(void)
{
	return (g_nTheServiceOuputTlvTree);
}


//! \brief Get the serialised response.
//! \param[in] nSize Size of the buffer in which the data shall be serialized.
//! \param[in] pData Data to be serialized.

static int __SDSAServices_GetResponse_ (unsigned int nSize, SDM_SERVICE_HEADER* pData)
{
	TLV_TREE_NODE hOutputTlvTree;
	int nResult;
	int nOutputSize;

	// Retrieve the result of the service
	hOutputTlvTree = __SDSA_GetOutputTlvTree();
	nResult = __SDSA_GetResult();

	if (hOutputTlvTree != NULL)
	{
		// Serialise the output TlvTree
		nOutputSize = TlvTree_Serialize(hOutputTlvTree, TLV_TREE_SERIALIZER_DEFAULT, (void*)(pData + 1), nSize - sizeof(SDM_SERVICE_HEADER));
		if (nOutputSize < 0)
		{
			nOutputSize = 0;
			nResult = SDI_STATUS_OUTPUT_BUFFER_TOO_SMALL;
		}
	}
	else
	{
		nOutputSize = 0;
	}

	// Clear unused space in output buffer
	memset(((unsigned char*)(pData + 1)) + nOutputSize, 0, nSize - sizeof(SDM_SERVICE_HEADER) - nOutputSize);

	if (nResult != SDI_STATUS_OUTPUT_BUFFER_TOO_SMALL)
	{
		// We can give the output TlvTree => delete the output TlvTree and result
		__SDSA_SetResult(SDI_STATUS_UNKNOWN);
		__SDSA_SetOutputTlvTree(NULL);
	}

	return nResult;
}

//! \brief This function is called when a Payment service of the new Intelligent Reader is called (Perform a ContactLess transaction, load parameters...)

static int __SDSAServicesTlvTree (unsigned int nSize, SDM_SERVICE_HEADER* pData)
{
	FILE *hDisplay = NULL;
	int nResult;
	TLV_TREE_NODE hInputTlvTree;
	TLV_TREE_NODE hOutputTlvTree = NULL;
	int bNoTlvTreeIn = FALSE;


	// Erase the output TlvTree
	__SDSA_SetResult(SDI_STATUS_UNKNOWN);
	__SDSA_SetOutputTlvTree(NULL);

	// Check that the input buffer contains at least the header
	if ((nSize <= sizeof(SDM_SERVICE_HEADER)) || (pData == NULL))
	{
		return (SDI_STATUS_INVALID_DATA);
	}

	// Build the input TlvTree
	if ((TlvTree_Unserialize(&hInputTlvTree, TLV_TREE_SERIALIZER_DEFAULT, (void*)(pData + 1), nSize - sizeof(SDM_SERVICE_HEADER)) != 0))
	{
		///return (SDI_STATUS_INVALID_DATA);
		bNoTlvTreeIn = TRUE;
	}
	
	// Call the service
	switch(pData->m_usService)
	{
	///////////////////////////////////////////////////////////////////////////
	case (SERVICE_PAYMENT_DO_TXN):
		if (bNoTlvTreeIn)
			return (SDI_STATUS_INVALID_DATA);

		// Create the output TLV Tree (for output data)
		hOutputTlvTree = TlvTree_New(0);
		if (hOutputTlvTree == NULL)
		{
			nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
			goto End;
		}
		hDisplay = fopen("DISPLAY","a");
		nResult = SDSA_DoTransaction (hInputTlvTree, hOutputTlvTree);
		break;

	///////////////////////////////////////////////////////////////////////////
	case (SERVICE_PAYMENT_TXN_POST_PROCESSING):
		if (bNoTlvTreeIn)
			return (SDI_STATUS_INVALID_DATA);

		// Create the output TLV Tree (for output data)
		hOutputTlvTree = TlvTree_New(0);
		if (hOutputTlvTree == NULL)
		{
			nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
			goto End;
		}
		hDisplay = fopen("DISPLAY","a");
		nResult = SDSA_PostProcessing (hInputTlvTree, hOutputTlvTree);
		break;

	///////////////////////////////////////////////////////////////////////////
	case (SERVICE_PAYMENT_LOAD_PARAMS):
		if (bNoTlvTreeIn)
			return (SDI_STATUS_INVALID_DATA);
		// Create the output TLV Tree (for output data)
		hOutputTlvTree = TlvTree_New(0);
		if (hOutputTlvTree == NULL)
		{
			nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
			goto End;
		}
	
		nResult = SDSA_Parameters_LoadParameters (hInputTlvTree, hOutputTlvTree);
		break;

	///////////////////////////////////////////////////////////////////////////
	case (SERVICE_PAYMENT_GET_PARAMS):
		if (bNoTlvTreeIn)
			return (SDI_STATUS_INVALID_DATA);
		hOutputTlvTree = TlvTree_New(0);
		if (hOutputTlvTree == NULL)
		{
			nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
			goto End;
		}

		nResult = SDSA_Parameters_GetParameters (hInputTlvTree, hOutputTlvTree);
		break;

	///////////////////////////////////////////////////////////////////////////
	case (SERVICE_PAYMENT_ERASE_PARAMS):
		nResult = SDSA_Parameters_EraseParameters ();
		break;

	///////////////////////////////////////////////////////////////////////////
	case (SERVICE_PAYMENT_GET_DATA):
		if (bNoTlvTreeIn)
			return (SDI_STATUS_INVALID_DATA);
		// Create the output TLV Tree (for output data)
		hOutputTlvTree = TlvTree_New(0);
		if (hOutputTlvTree == NULL)
		{
			nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
			goto End;
		}

		nResult = SDSA_GetPaymentData (hInputTlvTree, hOutputTlvTree);
		break;

	///////////////////////////////////////////////////////////////////////////
	case (SERVICE_PAYMENT_CLEAR_DATA):
		nResult = SDSA_ClearPaymentData ();
		break;

	///////////////////////////////////////////////////////////////////////////
	case (SERVICE_PAYMENT_SET_GUI_STATE):
		if (bNoTlvTreeIn)
			return (SDI_STATUS_INVALID_DATA);
		hDisplay = fopen("DISPLAY","a");
		nResult = SDSA_GuiState_SetGuiState (hInputTlvTree);
		break;

	///////////////////////////////////////////////////////////////////////////
	case (SERVICE_PAYMENT_GET_STATUS):
		if (bNoTlvTreeIn)
			return (SDI_STATUS_INVALID_DATA);
		// Create the output TLV Tree (for output data)
		hOutputTlvTree = TlvTree_New(0);
		if (hOutputTlvTree == NULL)
		{
			nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
			goto End;
		}

		nResult = SDSA_Status_GetStatus (hInputTlvTree, hOutputTlvTree);
		break;

	///////////////////////////////////////////////////////////////////////////
	case (SERVICE_PAYMENT_CARD_REMOVAL):
		if (bNoTlvTreeIn)
			return (SDI_STATUS_INVALID_DATA);
		hDisplay = fopen("DISPLAY","a");
		nResult = SDSA_WaitCardRemoval (hInputTlvTree);

		break;

	///////////////////////////////////////////////////////////////////////////
	case (SERVICE_GENERIC_USER_CMD_01):
		if (bNoTlvTreeIn)
			return (SDI_STATUS_INVALID_DATA);

		// Create the output TLV Tree (for output data)
		hOutputTlvTree = TlvTree_New(0);
		if (hOutputTlvTree == NULL)
		{
			nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
			goto End;
		}
		hDisplay = fopen("DISPLAY","a");
		nResult = SDSA_Generic_UserCommand_01 (hInputTlvTree, hOutputTlvTree);
		break;
		
	///////////////////////////////////////////////////////////////////////////
	default:
		nResult = SDI_STATUS_UNKNOWN;
		break;
	}

End:
	// Close the display
	if(hDisplay != NULL)
		fclose(hDisplay);

	// Delete the input TlvTree
	TlvTree_ReleaseEx(&hInputTlvTree);

	// Store the output response
	__SDSA_SetResult(nResult);
	__SDSA_SetOutputTlvTree(hOutputTlvTree);

	// Build the output response
	return (__SDSAServices_GetResponse_(nSize, pData));
}



//! \brief This function is called when the terminal ask to cancel the transaction (red key pressed, card was inserted...).

static int __SDSAServices_CancelTransaction (unsigned int nSize, SDM_SERVICE_HEADER* pData)
{
	(void) nSize;
	(void) pData;

	return (SDSA_CancelTransaction());
}


//! \brief This function is called to perform GUI when the reader is disconnected.

static int __SDSAServices_ReaderDisconnected (unsigned int nSize, SDM_SERVICE_HEADER* pData)
{
	FILE *hDisplay;

	(void) nSize;
	(void) pData;

	hDisplay = fopen("DISPLAY","a");
	if (hDisplay == NULL)
		return (SDI_STATUS_KO);

	SDSA_GuiState_DisplayScreen (SDSA_SCREEN_DISCONNECTED);

	// Close the display
	fclose(hDisplay);

	return (SDI_STATUS_OK);
}


//! \brief This function is called to perform GUI when the reader is connected.

static int __SDSAServices_ReaderConnected (unsigned int nSize, SDM_SERVICE_HEADER* pData)
{
	FILE *hDisplay;

	(void) nSize;
	(void) pData;

	hDisplay = fopen("DISPLAY","a");
	if (hDisplay == NULL)
		return (SDI_STATUS_KO);

	SDSA_GuiState_DisplayScreen (SDSA_SCREEN_CONNECTED);

	// Close the display
	fclose(hDisplay);

	return (SDI_STATUS_OK);
}
