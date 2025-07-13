//! \file
//! Module that manages all the application menus

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define DISK_NAME_SIZE			33			/*!< Size of disk name. */


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static int g_TransactionLoop = FALSE;			/*!< Global data indicating if transaction loop is enabled or not (currently not used). */
static int g_DumpTransactionData = FALSE;		/*!< Global data indicating if transaction data dumping is enabled or not. */
static int g_DumpTransactionDatabase = FALSE;	/*!< Global data indicating if transaction database dumping is enabled or not. */
static int g_TracesActivated = FALSE;			/*!< Global data indicating if transaction traces (using trace tool) is enabled or not. */
static int g_VisaEuropeModeEnabled = FALSE;		/*!< Global data indicating if Visa Europe Mode is enabled or not. */
static int g_EnableInputTransactionType = FALSE;/*!< Global data indicating if TransactionType information must be inputed before each transaction. */
static int g_MerchantForcedOnline = FALSE;		/*!< Global data indicating if merchant forced transaction online (PayPass only). */


//! \brief Main menu.
static const T_CLESS_SAMPLE_HELPER_MENU_ITEM MainMenu[] = {
	//{STD_MESS_MENU_MAIN_DEBIT, "CU_DEBIT.WGU"},
	//{STD_MESS_MENU_MAIN_REFUND, "CU_CREDIT.WGU"},
	{STD_MESS_MENU_MAIN_TEST, "CU_TOOLWARE.WGU"},
	{STD_MESS_MENU_MAIN_PARAMETERS, "CL_PARAMS.WGU"},
	{STD_MESS_MENU_MAIN_MERCHANT, "CU_MERCHANT.WGU"},
	{STD_MESS_MENU_MAIN_BATCH, "CL_BATCH.WGU"}
};
//! \brief Transaction Type menu.
static const T_CLESS_SAMPLE_HELPER_MENU_ITEM TransactionTypeMenu[] = {
	{STD_MESS_MENU_MAIN_DEBIT, "CU_DEBIT.WGU"},
	{STD_MESS_MENU_MAIN_CASH, "CU_CREDIT.WGU"},
	{STD_MESS_MENU_MAIN_REFUND, "CU_CREDIT.WGU"},
	{STD_MESS_MENU_MAIN_CASHBACK, "CU_CREDIT.WGU"},
};

//! \brief Batch menu.
static const T_CLESS_SAMPLE_HELPER_MENU_ITEM BatchMenu[] = {
	{STD_MESS_MENU_PARAMS_BATCH_TOTALS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_BATCH_PRINT_LOG, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_BATCH_PRINT_DETAILED_LOG, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_BATCH_CLEAR, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_BATCH_LAST_TR, "CU_DEFAULT.WGU"}
};

//! \brief Test menu.
static const T_CLESS_SAMPLE_HELPER_MENU_ITEM TestMenu[] = {
	{STD_MESS_MENU_TEST_DUMP_TR, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_DUMP_DB, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_LOOP, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_IMPLICIT_SEL_LOOP, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_CHANGE_OUTPUT, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_TRACES, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_VISA_EUROPE, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_INPUT_TRANSACTION_TYPE, "CU_DEFAULT.WGU"}
};

//! \brief Menu for output data change (with printer).
static const T_CLESS_SAMPLE_HELPER_MENU_ITEM TestMenuWithPrinter[] = {
	{STD_MESS_MENU_OUTPUT_COM0, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_OUTPUT_USB, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_OUTPUT_NONE, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_OUTPUT_PRINTER, "CU_DEFAULT.WGU"}
};

//! \brief Menu for output data change (without printer).
static const T_CLESS_SAMPLE_HELPER_MENU_ITEM TestMenuWithoutPrinter[] = {
	{STD_MESS_MENU_OUTPUT_COM0, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_OUTPUT_USB, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_OUTPUT_NONE, "CU_DEFAULT.WGU"}
};

//! \brief Parameters menu.
static const T_CLESS_SAMPLE_HELPER_MENU_ITEM ParametersMenu[] = {
	{STD_MESS_MENU_PARAMS_DUMP, "CU_DUMP.WGU"},
	{STD_MESS_MENU_PARAMS_DEFAULT, "CU_DEF_CNF.WGU"},
	{STD_MESS_MENU_PARAMS_ERASE_ALL, "CL_PARAMDEL.WGU"}
};

//! \brief Parameters dump menu.
static const T_CLESS_SAMPLE_HELPER_MENU_ITEM ParametersMenuDump[] = {
	{STD_MESS_MENU_PARAMS_DUMP_ID, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_DUMP_AIDS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_DUMP_CA, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_DUMP_GLOBALS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_DUMP_KERNEL_SPECIFIC, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_DUMP_ALL, "CU_DEFAULT.WGU"}
};

//! \brief Merchant menu.
static const T_CLESS_SAMPLE_HELPER_MENU_ITEM MerchantMenu[] = {
	{STD_MESS_MENU_PARAMS_MERCHANT_FORCE_ONLINE, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_MERCHANT_RESET_TSC, "CU_DEFAULT.WGU"}
};
static StructDebitEmv         s_debit;


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static void __InitDebit(unsigned long *amount,S_MONEY *currency);

# if 0
static int __ClessSample_Menu_Debit(void);
static int __ClessSample_Menu_Cash(void);
static int __ClessSample_Menu_Refund(void);
static int __ClessSample_Menu_CashBack(void);
#endif // 00
static int __ClessSample_Menu_BatchTotals(void);
static int __ClessSample_Menu_BatchPrintLog(void);
static int __ClessSample_Menu_BatchPrintDetailedLog(void);
static int __ClessSample_Menu_BatchClear(void);
static int __ClessSample_Menu_BatchPrintLastTransaction(void);
static int __ClessSample_Menu_Batch(void);
static int __ClessSample_Menu_Test (void);
static int __ClessSample_Menu_Parameters (void);
static int __ClessSample_Menu_TestTransactionData(void);
static int __ClessSample_Menu_TestTransactionDumpDatabase(void);
static int __ClessSample_Menu_TestTransactionLoop(void);
static int __ClessSample_Menu_DebitImplicitSelectionLoop(void);
static int __ClessSample_Menu_TestTraces(void);
static int __ClessSample_Menu_TestVisaEuropeMode(void);
static int __ClessSample_Menu_TestInputTransactionType(void);
static int __ClessSample_Menu_DefaultParameters(void);
static int __ClessSample_Menu_EraseParameters (void);
static int __ClessSample_Menu_ParametersDump (void);
static int __ClessSample_Menu_TestChooseOutput (void);
static int __ClessSample_Menu_MerchantForcedOnline(void);
static int __ClessSample_Menu_Merchant (void);

extern int IsPrinter(void);

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//##################################################################
//################### DEBIT MENU ###################################
//##################################################################


static void __InitDebit(unsigned long *amount,S_MONEY *currency)
{
	
    s_debit.param_out.noappli     = 0xFF;
    s_debit.param_out.rc_payment  = PAY_KO;
    memclr(s_debit.param_out.card_holder_nb,sizeof(s_debit.param_out.card_holder_nb));
	
	s_debit.param_in.support              = UNKNOWN_SUPPORT;
	s_debit.param_in.payment              = UNKNOWN_PAYMENT;
	
	s_debit.param_in.entry                = MANUAL_ENTRY;	
	
	s_debit.param_in.transaction          = DEBIT_TR;
	s_debit.param_in.amount               = *amount;

	memcpy((char *)&s_debit.param_in.currency,(char *)currency,sizeof(S_MONEY));
}


//##################################################################
//################### BATCH MENU ###################################
//##################################################################


//! \brief Action to do if TOTALS is selected in the Batch menu
//! \return Always -1.

static int __ClessSample_Menu_BatchTotals(void)
{
	// TODO: Print a receipt with the total of the transactions in the batch
	ClessSample_Batch_PrintTotals();
	return -1;
}



//! \brief Action to do if PRINT LOG is selected in the Batch menu
//! \return Always -1.

static int __ClessSample_Menu_BatchPrintLog(void)
{
	// TODO: Print the batch content
	ClessSample_Batch_PrintBatchOverview();
	return -1;
}

//! \brief Action to do if PRINT DETAILED LOG is selected in the Batch menu
//! \return Always -1.

static int __ClessSample_Menu_BatchPrintDetailedLog(void)
{
	// TODO: Print the batch content
	ClessSample_Batch_PrintBatchDetailedOverview();
	return -1;
}


//! \brief Action to do if PRINT LOG is selected in the Batch menu
//! \return Always -1.

static int __ClessSample_Menu_BatchPrintLastTransaction(void)
{
	// TODO: Print the last transaction saved in the batch
	ClessSample_Batch_PrintLastTransaction();
	return -1;
}



//! \brief  Action to do if UPLOAD is selected in the Batch menu
//! \return Always -1.

static int __ClessSample_Menu_BatchClear(void)
{
	// TODO: Updload the batch content and empty it
	ClessSample_Batch_Destroy();
	return -1;
}



//! \brief Batch menu management
//! \return Always -1.

static int __ClessSample_Menu_Batch(void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu("BATCH", nChoice, NUMBER_OF_ITEMS(BatchMenu), BatchMenu);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:
				nResult = __ClessSample_Menu_BatchTotals();
				break;
			case 1:
				nResult = __ClessSample_Menu_BatchPrintLog();
				break;
			case 2:
				nResult = __ClessSample_Menu_BatchPrintDetailedLog();
				break;
			case 3:
				nResult = __ClessSample_Menu_BatchClear();
				break;
			case 4:
				nResult = __ClessSample_Menu_BatchPrintLastTransaction();
				break;
			default:
				nResult = 0;
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}



//##################################################################
//################### TEST MENU ####################################
//##################################################################

//! \brief Action to do if DUMP TR DATA is selected in the TEST menu
//! \return Always -1.

static int __ClessSample_Menu_TestTransactionData(void)
{
	MSGinfos tMsg;
	int lg_code;

	// Get the manager language (merchant language)
	lg_code = PSQ_Give_Language();

	ClessSample_Term_Read_Message(STD_MESS_MENU_TEST_DUMP_TR, lg_code, &tMsg);
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, LEDSOFF);
		
	if (g_DumpTransactionData == FALSE)
	{
		g_DumpTransactionData = TRUE;
		ClessSample_Term_Read_Message(STD_MESS_ENABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	else
	{
		g_DumpTransactionData = FALSE;
		ClessSample_Term_Read_Message(STD_MESS_DISABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	
	Helper_RefreshScreen(WAIT, HELPERS_MERCHANT_SCREEN);

	return -1;
}


//! \brief Action to do if "DUMP DATA DB" is selected in the TEST menu (it enables/diables the dabase dumping).
//! \return Always -1.

static int __ClessSample_Menu_TestTransactionDumpDatabase(void)
{
	MSGinfos tMsg;
	int lg_code;

	// Get the manager language (merchant language)
	lg_code = PSQ_Give_Language();

	ClessSample_Term_Read_Message(STD_MESS_MENU_TEST_DUMP_DB, lg_code, &tMsg);
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, LEDSOFF);
		
	if (g_DumpTransactionDatabase == FALSE)
	{
		g_DumpTransactionDatabase = TRUE;
		ClessSample_Term_Read_Message(STD_MESS_ENABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	else
	{
		g_DumpTransactionDatabase = FALSE;
		ClessSample_Term_Read_Message(STD_MESS_DISABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	
	Helper_RefreshScreen(WAIT, HELPERS_MERCHANT_SCREEN);

	return -1;
}



//! \brief Choose the output peripheral to get the dumps (parameters or transaction data).
//! \return Always -1.

static int __ClessSample_Menu_TestChooseOutput (void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	nResult = 0;

	do
	{
		if (!IsPrinter()) // IsPrinter() is not yet provided by the simulator
			nChoice = HelperDisplayMenu("OUTPUT", nChoice, NUMBER_OF_ITEMS(TestMenuWithoutPrinter), TestMenuWithoutPrinter);
		else
			nChoice = HelperDisplayMenu("OUTPUT", nChoice, NUMBER_OF_ITEMS(TestMenuWithPrinter), TestMenuWithPrinter);

		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0: // COM0
				ClessSample_DumpData_DumpSetOutputId (CUSTOM_OUTPUT_COM0);
				nResult = -1;
				break;

			case 1: // USB
				ClessSample_DumpData_DumpSetOutputId (CUSTOM_OUTPUT_USB);
				nResult = -1;
				break;

			case 2: // NONE
				ClessSample_DumpData_DumpSetOutputId (CUSTOM_OUTPUT_NONE);
				nResult = -1;
				break;

			case 3: //Printer (if present)
				if (IsPrinter())
				{
					ClessSample_DumpData_DumpSetOutputId (CUSTOM_OUTPUT_PRINTER);
					nResult = -1;
				}
				else
				{
					nResult = 0;
				}
				break;

			default:
				nResult = 0;
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}



//! \brief Action to do if TRANSAC LOOP is selected in the TEST menu
//! \return Always -1.

static int __ClessSample_Menu_TestTransactionLoop(void)
{
	MSGinfos tMsg;
	int lg_code;

	// Get the manager language (merchant language)
	lg_code = PSQ_Give_Language();

	ClessSample_Term_Read_Message(STD_MESS_MENU_TEST_LOOP, lg_code, &tMsg);
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, LEDSOFF);
		
	if (g_TransactionLoop == FALSE)
	{
		g_TransactionLoop = TRUE;
		ClessSample_Term_Read_Message(STD_MESS_ENABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	else
	{
		g_TransactionLoop = FALSE;
		ClessSample_Term_Read_Message(STD_MESS_DISABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}

	Helper_RefreshScreen(WAIT, HELPERS_MERCHANT_SCREEN);

	return -1;
}

//===============================================================
//! \brief Begin several payment cycles
//! \return Always -1.

static int __ClessSample_Menu_DebitImplicitSelectionLoop(void)
{
	unsigned char    priority;
	unsigned char    cr;
	int              retour;
	int nEvent;
	unsigned long    ulAmount;
	ENTRY_BUFFER     buf;
	S_MONEY          currency;
	TAB_ENTRY_AMOUNT tab_montant = {0x6FC0,MINUTE};
	FILE            *hcam0;
 
	TAB_ENTRY_STRING Options = {0x0000, 2*MINUTE, 1, 0, ECHO_NORMAL, 6, 1}; 
	BUFFER_SAISIE buffer ;
	int nbLoop;
	int nTrLoopState; // To memorise an information
	FILE * hKeyboard;

	fopen("DISPLAY","w");
	printf ("Number of loops?\n");
	fclose(stdout());
	Saisie_Numerique ((TAB_ENTRY_STRING *)&Options);
	ttestall (SAISIE,0);
	cr = Read_Saisie (&buffer);
	if (cr == CR_SAISIE_OK)
	{
		buffer.donnees[buffer.nombre] = '\0';
		nbLoop = atoi((char*)(buffer.donnees));
	}
	else
	{
		nbLoop = 1;
	}

	// Get the amount 
	G_Saisie_montant (&currency,		// Contain the currency selected in return   
		&buf,							// Contain the amount in return
		&cr,							// Contain the result of entry in return     
		"AMOUNT",						// The message above the amount              
		(TAB_ENTRY_AMOUNT *)&tab_montant, // Parameters of entry 
		NULL,							// Currency table                            
		0,								// Number of currency                        
		0,								// mask of periph to wait                    
		_AFF_FRANCE_);					// type of displaying    

	if (cr == CR_ENTRY_OK)
	{
		buf.d_entry[buf.d_len] = '\0';
		ulAmount=atoi((char*)(buf.d_entry));

		// Check if the Service is available 
		if (ServiceGet(TYPE_GESTIONNAIRE,100,&priority)==0)
		{
			do
			{
				/* Open if CAM0 if not */
				hcam0 = stdcam0();
				if (hcam0==NULL)
				{
					hcam0 = fopen("CAM0","rw");
				}

				__InitDebit(&ulAmount,&currency);
				
				// To forbid ticket
				nTrLoopState = g_TransactionLoop; // Memorise state 
				g_TransactionLoop = TRUE;

				ServiceCall(TYPE_GESTIONNAIRE,100,sizeof(StructDebitEmv),&s_debit,&retour);
				
				g_TransactionLoop = nTrLoopState; // Restore state

				/* Close CAM0 if opened */
				if (hcam0==NULL)
				{
					power_down(stdcam0());fclose(stdcam0());
				}

				nbLoop--;

				// Keyboard test to check if ANNulation key has been pressed
				hKeyboard = fopen("KEYBOARD", "r");

				if (hKeyboard != NULL)
				{
					// Wait some seconds to check if no interruption is asked (RED button)
					nEvent = ttestall (KEYBOARD, 40);
					if (nEvent == KEYBOARD)
					{
						if (getc(hKeyboard) == T_ANN)
						{
							nbLoop = 0; // End loop
						}
					}
					fclose (hKeyboard);
				}
				
			} while(nbLoop > 0);
		}
	}

	return -1;
}

//! \brief Action to do if TRACES is selected in the TEST menu
//! \return Always -1.

static int __ClessSample_Menu_TestTraces(void)
{
	MSGinfos tMsg;
	int lg_code;

	// Get the manager language (merchant language)
	lg_code = PSQ_Give_Language();

	ClessSample_Term_Read_Message(STD_MESS_MENU_TEST_TRACES, lg_code, &tMsg);
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, LEDSOFF);

	if (g_TracesActivated == FALSE)
	{
		g_TracesActivated = TRUE;
		ClessSample_Term_Read_Message(STD_MESS_ENABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	else
	{
		g_TracesActivated = FALSE;
		ClessSample_Term_Read_Message(STD_MESS_DISABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	
	Helper_RefreshScreen(WAIT, HELPERS_MERCHANT_SCREEN);
	
	// Debug features management
	ClessSample_PayPass_DebugActivation (g_TracesActivated);
	ClessSample_payWave_DebugActivation (g_TracesActivated);
	ClessSample_VisaWave_DebugActivation (g_TracesActivated);
	ClessSample_ExpressPay_DebugActivation (g_TracesActivated);
	ClessSample_Discover_DebugActivation (g_TracesActivated);
	ClessSample_Interac_DebugActivation (g_TracesActivated);

	return -1;
}



//! \brief Action to do if "VISA EUROPE" is selected in the TEST menu (activate/deactivate the "Visa Europe Mode")
//! \return Always -1.

static int __ClessSample_Menu_TestVisaEuropeMode(void)
{
	MSGinfos tMsg;
	int lg_code;

	// Get the manager language (merchant language)
	lg_code = PSQ_Give_Language();

	ClessSample_Term_Read_Message(STD_MESS_MENU_TEST_VISA_EUROPE, lg_code, &tMsg);
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, LEDSOFF);

	if (g_VisaEuropeModeEnabled == FALSE)
	{
		g_VisaEuropeModeEnabled = TRUE;
		ClessSample_Term_Read_Message(STD_MESS_ENABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	else
	{
		g_VisaEuropeModeEnabled = FALSE;
		ClessSample_Term_Read_Message(STD_MESS_DISABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	
	Helper_RefreshScreen(WAIT, HELPERS_MERCHANT_SCREEN);

	return -1;
}

//! \brief Action enable/disable "TransactionType" information to input.
//! \return Always -1.

static int __ClessSample_Menu_TestInputTransactionType(void)
{
	MSGinfos tMsg;
	int lg_code;

	// Get the manager language (merchant language)
	lg_code = PSQ_Give_Language();

	ClessSample_Term_Read_Message(STD_MESS_MENU_TEST_INPUT_TRANSACTION_TYPE, lg_code, &tMsg);
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, LEDSOFF);


	if (g_EnableInputTransactionType == FALSE)
	{
		g_EnableInputTransactionType = TRUE;
		ClessSample_Term_Read_Message(STD_MESS_ENABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	else
	{
		g_EnableInputTransactionType = FALSE;
		ClessSample_Term_Read_Message(STD_MESS_DISABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}

	Helper_RefreshScreen(WAIT, HELPERS_MERCHANT_SCREEN);

	return -1;
}

//! \brief Test if EnableTransactionType is on.
//! \return
//!		- \ref TRUE if loop is activated.
//!		- \ref FALSE if not.
unsigned char ClessSample_Menu_IsEnableInputTransactionType (void)
{
	return (unsigned char)g_EnableInputTransactionType;
}



//! \brief Test if transaction loop mode has been activated.
//! \return
//!		- \ref TRUE if loop is activated.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsTransactionLoopOn (void)
{
	return (unsigned char)g_TransactionLoop;
}



//! \brief Test if transaction data dumping is TRUE or FALSE.
//! \return
//!		- \ref TRUE if dump mode is activated.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsTransactionDataDumpingOn (void)
{
	return (unsigned char)g_DumpTransactionData;
}



//! \brief Test if transaction database dumping is TRUE or FALSE.
//! \return
//!		- \ref TRUE if database dumping is activated.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsTransactionDatabaseDumpingOn (void)
{
	return (unsigned char)g_DumpTransactionDatabase;
}



//! \brief Test if Visa Europe Mode is activated or not.
//! \return
//!		- \ref TRUE if database dumping is activated.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsVisaEuropeModeOn (void)
{
	return (unsigned char)g_VisaEuropeModeEnabled;
}



//! \brief Test menu management
//! \return Always -1.

static int __ClessSample_Menu_Test(void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu("TEST MENU", nChoice, NUMBER_OF_ITEMS(TestMenu), TestMenu);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:
				nResult = __ClessSample_Menu_TestTransactionData();
				break;

			case 1:
				nResult = __ClessSample_Menu_TestTransactionDumpDatabase();
				break;

			case 2:
				nResult = __ClessSample_Menu_TestTransactionLoop();
				break;
				
			case 3:
				nResult = __ClessSample_Menu_DebitImplicitSelectionLoop();
				break;

			case 4:
				nResult = __ClessSample_Menu_TestChooseOutput();
				break;

			case 5:
				nResult = __ClessSample_Menu_TestTraces();
				break;
				
			case 6:
				nResult = __ClessSample_Menu_TestVisaEuropeMode();
				break;

			case 7:
				nResult = __ClessSample_Menu_TestInputTransactionType();
				break;
				
			default:
				nResult = 0;
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}



//##################################################################
//################### PARAMETERS MENU ##############################
//##################################################################

//! \brief Action read default parameters and update .SAV file with it
//! \return Always -1.

static int __ClessSample_Menu_DefaultParameters(void)
{

	MSGinfos tMsg, tGlobalMsg;
	int lg_code;

	// Get the manager language (merchant language)
	lg_code = PSQ_Give_Language();

	ClessSample_Term_Read_Message(STD_MESS_UPDATING_PARAMS, lg_code, &tGlobalMsg);
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tGlobalMsg, LEDSOFF);
	ClessSample_Term_Read_Message(STD_MESS_IN_PROGRESS, lg_code, &tMsg);
	Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);

	// Read default parameters
	ClessSample_Parameters_ReadDefaultParameters(&pTreeCurrentParam);

	if (ClessSample_Parameters_SaveParam (pTreeCurrentParam) != 0) // Save dummy TLVTree parameters in file
	{
		Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tGlobalMsg, LEDSOFF);
		ClessSample_Term_Read_Message(STD_MESS_ERROR, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	else
	{
		Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tGlobalMsg, LEDSOFF);
		ClessSample_Term_Read_Message(STD_MESS_COMPLETE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}

	Helper_RefreshScreen(WAIT, HELPERS_MERCHANT_SCREEN);
	
	// Check parameters CA keys
	ClessSample_Parameters_CheckCaKeysCrc(pTreeCurrentParam);

	return -1;
}


//! \brief Action to do if ERASE ALL is selected in the PARAMETERS menu. It erase all the application parameters.
//! \return Always -1.

static int __ClessSample_Menu_EraseParameters (void)
{
	MSGinfos tMsg, tGlobalMsg;
	int lg_code;

	// Get the manager language (merchant language)
	lg_code = PSQ_Give_Language();

	ClessSample_Term_Read_Message(STD_MESS_ERASING_PARAMS, lg_code, &tGlobalMsg);
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tGlobalMsg, LEDSOFF);
	ClessSample_Term_Read_Message(STD_MESS_IN_PROGRESS, lg_code, &tMsg);
	Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	Helper_RefreshScreen(NOWAIT, HELPERS_MERCHANT_SCREEN);

	ClessSample_Parameters_InitParameters(&pTreeCurrentParam); // Reset TLVTree parameters
	if (ClessSample_Parameters_SaveParam (pTreeCurrentParam) != 0) // Save dummy TLVTree parameters in file
	{
		Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tGlobalMsg, LEDSOFF);
		ClessSample_Term_Read_Message(STD_MESS_ERROR, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	else
	{
		Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tGlobalMsg, LEDSOFF);
		ClessSample_Term_Read_Message(STD_MESS_COMPLETE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}

	Helper_RefreshScreen(WAIT, HELPERS_MERCHANT_SCREEN);

	return -1;
}



//! \brief Parameters menu management
//! \return Always -1.

static int __ClessSample_Menu_Parameters (void)
{
	int nChoice;
	int nResult;


	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu("PARAMETERS", nChoice, NUMBER_OF_ITEMS(ParametersMenu), ParametersMenu);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:			// Trace parameters on printer
				nResult = __ClessSample_Menu_ParametersDump();
				break;
			case 1:			// Read default parameters and save it in file (for next start)
				nResult = __ClessSample_Menu_DefaultParameters();
				break;
			case 2:			// Scratch parameters 
				nResult = __ClessSample_Menu_EraseParameters();
				break;
			default:		// ?
				nResult = 0;
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}



//! \brief Parameters menu management for data dumping
//! \return Always -1.

static int __ClessSample_Menu_ParametersDump (void)
{
	int nChoice;
	int nResult;


	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu("PARAMETERS DUMP", nChoice, NUMBER_OF_ITEMS(ParametersMenuDump), ParametersMenuDump);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:			// Identifier
				ClessSample_Parameters_DumpIdentificationLabel(pTreeCurrentParam);
				nResult = 0;
				break;
			case 1:			// AIDs
				ClessSample_Parameters_DumpAids (pTreeCurrentParam);
				nResult = 0;
				break;
			case 2:			// CA Keys
				ClessSample_Parameters_DumpCaKeys (pTreeCurrentParam);
				nResult = 0;
				break;
			case 3:			// Globals
				ClessSample_Parameters_DumpGlobals (pTreeCurrentParam);
				nResult = 0;
				break;
			case 4:			// Kernel specific
				ClessSample_Parameters_DumpKernelSpecific (pTreeCurrentParam);
				nResult = 0;
				break;
			case 5:			// All
				ClessSample_Parameters_DumpIdentificationLabel(pTreeCurrentParam);
				ClessSample_Parameters_DumpAids (pTreeCurrentParam);
				ClessSample_Parameters_DumpCaKeys (pTreeCurrentParam);
				ClessSample_Parameters_DumpGlobals (pTreeCurrentParam);
				ClessSample_Parameters_DumpKernelSpecific (pTreeCurrentParam);
				nResult = 0;
				break;
			default:		// ?
				nResult = 0;
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}



//##################################################################
//################### GLOBAL MENU ##################################
//##################################################################

//! \brief Action to do if "Forced Online" is selected in the MERCHANT menu
//! \return Always -1.

static int __ClessSample_Menu_MerchantForcedOnline(void)
{
	MSGinfos tMsg;
	int lg_code;

	// Get the manager language (merchant language)
	lg_code = PSQ_Give_Language();

	ClessSample_Term_Read_Message(STD_MESS_MENU_PARAMS_MERCHANT_FORCE_ONLINE, lg_code, &tMsg);
	Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tMsg, LEDSOFF);

	if (g_MerchantForcedOnline == FALSE)
	{
		g_MerchantForcedOnline = TRUE;
		ClessSample_Term_Read_Message(STD_MESS_ENABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	else
	{
		g_MerchantForcedOnline = FALSE;
		ClessSample_Term_Read_Message(STD_MESS_DISABLE, lg_code, &tMsg);
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_3, &tMsg, LEDSOFF);
	}
	
	Helper_RefreshScreen(WAIT, HELPERS_MERCHANT_SCREEN);
	
	return -1;
}


//! \brief Merchant menu management for data dumping
//! \return Always -1.

static int __ClessSample_Menu_Merchant (void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu("MERCHANT", nChoice, NUMBER_OF_ITEMS(MerchantMenu), MerchantMenu);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:			// Force online
				nResult = __ClessSample_Menu_MerchantForcedOnline();
				break;
			case 1:			// Reset TSC
				ClessSample_Batch_InitTransactionSeqCounter (TRUE);
				nResult = -1;
				break;
			default:		// ?
				nResult = 0;
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);

	return nChoice;
}



//! \brief Test if merchant forced transaction online or not.
//! \return
//!		- \ref TRUE if merchant forced transaction online.
//!		- \ref FALSE if not.

unsigned char ClessSample_Menu_IsMerchantForcedOnline (void)
{
	return (unsigned char)g_MerchantForcedOnline;
}


//===========================================================================
//! \brief // Format the message that contains the amount, the currency according to ucFormat, ucPosition...
//! \param[in] ucFormat : the display format
//! \param[in] ucCurrency : transaction currency
//! \param[in] ucPosition : the position of the currency
//! \param[in] ulAmount : the transaction amount
//! \param[out] pFormattedAmountMessage : the formatted message to display
//! \return
//! 	lang code.
//===========================================================================
static void __ClessSample_Menu_FormatAmount(unsigned char ucFormat, unsigned char *ucCurrency, unsigned char ucPosition, unsigned long ulAmount, char * pFormattedAmountMessage)
{
	char            currency[4];
	char            separator1[2];
	char            separator2[2];
	char            position;
	int             exponent;
	unsigned long   divider;
	unsigned long   i;
	char            amount_format[51];

	position=ucPosition;
	strcpy((char *)currency,(char *)ucCurrency);
	switch (ucFormat)
	{
		case 1 :
			strcpy(separator1,".");
			strcpy(separator2,",");
			exponent=2;
			break;
		case 2 :
			strcpy(separator1,",");
			strcpy(separator2," ");
			exponent=2;
			break;
		case 3 :
			strcpy(separator1," ");
			strcpy(separator2,".");
			exponent=0;
			break;
		case 4 :
			strcpy(separator1," ");
			strcpy(separator2,",");
			exponent=0;
			break;
		case 5 :
			strcpy(separator1," ");
			strcpy(separator2," ");
			exponent=0;
			break;
		case 6 :
			strcpy(separator1,",");
			strcpy(separator2,".");
			exponent=3;
			break;
		case 7 :
			strcpy(separator1,".");
			strcpy(separator2,",");
			exponent=3;
			break;
		case 8 :
			strcpy(separator1,",");
			strcpy(separator2," ");
			exponent=3;
			break;
		case 0 :
	default :
			strcpy(separator1,",");
			strcpy(separator2,".");
			exponent=2;
			break;
	}
	switch(exponent)
	{
		case 1 :
			for (divider=1L,i=0L;i<(unsigned)exponent;divider*=10L,i++);
			if ((ulAmount/divider)<1000L)
			{
				sprintf(amount_format,"%lu%s%0*lu",
							(ulAmount/divider),
							separator2,
							exponent,
							(ulAmount%divider));
			}
			else
			{
				if ((ulAmount/divider)<1000000L)
				{
					sprintf(amount_format,"%lu%s%03lu%s%0*lu",
							((ulAmount/divider)/1000L),
							separator1,
							((ulAmount/divider)%1000L),
							separator2,
							exponent,
							(ulAmount%divider));
				}
				else
				{
					sprintf(amount_format,"%lu%s%03lu%s%03lu%s%0*lu",
							((ulAmount/divider)/1000000L),
							separator1,
							(((ulAmount/divider)/1000L)%1000L),
							separator1,
							((ulAmount/divider)%1000L),
							separator2,
							exponent,
							(ulAmount%divider));
				}
			}
			break;
		case 2 :
		case 3 :
		case 4 :
		case 5 :
		case 6 :
		case 7 :
			for (divider=1L,i=0L;i<(unsigned)exponent;divider*=10L,i++);
			if ((ulAmount/divider)<1000L)
			{
				sprintf(amount_format,"%lu%s%0*lu",
						(ulAmount/divider),
						separator2,
						exponent,
						(ulAmount%divider));
			}
			else
			{
				sprintf(amount_format,"%lu%s%03lu%s%0*lu",
						((ulAmount/divider)/1000L),
						separator1,
						((ulAmount/divider)%1000L),
						separator2,
						exponent,
						(ulAmount%divider));
			}
			break;
		case 0 :
		default :
			if ((ulAmount)<1000L)
			{
				sprintf(amount_format,"%lu",(ulAmount));
			}
			else
			{
				if ((ulAmount)<1000000L)
				{
					sprintf(amount_format,"%lu%s%03lu",((ulAmount)/1000L),separator1,((ulAmount)%1000L));
				}
				else
				{
					sprintf(amount_format,"%lu%s%03lu%s%03lu",((ulAmount)/1000000L),separator1,(((ulAmount)/1000L)%1000L),separator1,((ulAmount)%1000L));
				}
			}
			break;
	}

	if (position == 0)
	{
		sprintf(pFormattedAmountMessage,"%s %s",
					amount_format,
					currency);
	}
	else
	{
		sprintf(pFormattedAmountMessage,"%s %s",
					currency,
					amount_format);
	}
}


//! \brief Requests amount entry, prepare frame for Entry Point (fill shared memory)
//! \param[in] pCurrencyLabel : the currency label
//! \param[out] pAmountBin : the entered transaction amount
//! \param[out] pFormattedAmountMessage : the formatted message to display
//! \return
//!		- TRUE if amount has been entered.
//!		- FALSE if amount entry has been cancelled.
int ClessSample_Menu_AmountEntry (const unsigned char *pCurrencyLabel, unsigned long * pAmountBin, char * pFormattedAmountMessage)
{
	TAB_ENTRY_FCT TabEntry;
	unsigned long ulAmount;
	int nResult;
	unsigned char ucFormat, ucPosition;
	unsigned char CurrencyLabel[4];

	// Amount entry
	TabEntry.mask = 0;
	TabEntry.time_out = 60;
	*pAmountBin = 0;
	memset (CurrencyLabel, 0, sizeof(CurrencyLabel));

	///////////////////////////////////////////////////
	//unsigned char  ucFormat: format of the displayed amount
	//                         0 ==> 1.000,00
	//                         1 ==> 1,000.00
	//                         2 ==> 1 000,00
	//                         3 ==> 1.000
	//                         4 ==> 1,000
	//                         5 ==> 1 000
	//                         6 ==> 1.000,000
	//                         7 ==> 1,000.000
	//                         8 ==> 1 000,000
	//unsigned char ucPosition: position of the currency
	//                         0 ==> after the amount
	//                         1 ==> before the amount
	////////////////////////////////////////////////////

	ucFormat = 0;
	ucPosition = 0;
	memcpy (CurrencyLabel, pCurrencyLabel, 3);


	nResult = GetAmount(ucFormat, CurrencyLabel, ucPosition, &ulAmount, (unsigned char*)"Enter amount", &TabEntry);

	if (nResult == T_VAL)
	{
		// Format the message that contains the amount, the currency according to ucFormat, ucPosition...
		__ClessSample_Menu_FormatAmount(ucFormat,CurrencyLabel,ucPosition,ulAmount,pFormattedAmountMessage);

		*pAmountBin = ulAmount;
	}

	return (nResult == T_VAL);
}



//##################################################################
//################### GLOBAL MENU ##################################
//##################################################################

//! \brief Global menu management
void ClessSample_Menu_MainMenuDisplay(void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu("CONTACTLESS", nChoice, NUMBER_OF_ITEMS(MainMenu), MainMenu);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
//			case 0:
//				nResult = __ClessSample_Menu_Debit();
//				break;
//			case 1:
//				nResult = __ClessSample_Menu_Cash();
//				break;
//			case 2:
//				nResult = __ClessSample_Menu_Refund();
//				break;
//			case 3:
//				nResult = __ClessSample_Menu_CashBack();
//				break;
//			case 4:
			case 0:
				nResult = __ClessSample_Menu_Test();
				break;
			case 1:
				nResult = __ClessSample_Menu_Parameters();
				break;
			case 2:
				nResult = __ClessSample_Menu_Merchant();
				break;
			case 3:
				nResult = __ClessSample_Menu_Batch();
				break;
			default:
				nResult = 0;
				break;
			}

			if (nResult == -1)
				nChoice = -1;
		}
	} while(nChoice >= 0);
}

//! \brief Transaction Type menu management
void ClessSample_Menu_TransactionTypeMenuDisplay(const unsigned char *pCurrencyLabel, unsigned long * pulAmount, unsigned long * pulAmountOther, int * pnTransactionType)
{
	int nChoice;
	int nInputAmountOther = 0;

	*pnTransactionType = -1;

	nChoice = 0;

	do {
		nChoice = HelperDisplayMenu("CONTACTLESS", nChoice, NUMBER_OF_ITEMS(TransactionTypeMenu), TransactionTypeMenu);

		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:
				*pnTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_DEBIT;
				break;
			case 1:
				*pnTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_CASH;
				break;
			case 2:
				*pnTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_REFUND;
				break;
			case 3:
				*pnTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_PURSH_WITH_CASHBACK;
				nInputAmountOther = TRUE;
				break;
			default:
				*pnTransactionType = -1;
				break;
			}
		}
	} while (*pnTransactionType == -1);

	if (nInputAmountOther)
	{
		// If Amount = 0
		if (*pulAmount == 0)
		{
			*pulAmountOther = 0; // No Amount other entry possible or must be set to 0 (Initial amount inputed must be egal to amount + amount other)
		}
		else
		{
			char acFormattedAmountMessage[32];

			// => amount other must inputed
			if (!ClessSample_Menu_AmountEntry(pCurrencyLabel, pulAmountOther, acFormattedAmountMessage))
			{
				*pnTransactionType = -1;
			}
		}
	}
}

//! \brief Allows to known trace state
int ClessSample_Menu_IsTraceActivated(void)
{
	return (g_TracesActivated);
}
