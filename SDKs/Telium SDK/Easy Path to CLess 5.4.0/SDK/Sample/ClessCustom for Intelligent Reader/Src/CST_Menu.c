/**
 * \file	CST_Menu.c
 * \brief 	Manages the application menus.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "CST_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static int g_EnableInputTransactionType = FALSE;	/*!< Global data indicating if TransactionType information must be inputed before each transaction. */
static int g_TransactionLoop = FALSE;				/*!< Global data indicating if transaction loop is enabled or not. */
static int g_DumpTransactionData = FALSE;			/*!< Global data indicating if transaction data dumping is enabled or not. */
static int g_DumpTransactionDatabase = FALSE;		/*!< Global data indicating if transaction database dumping is enabled or not. */
static int g_TracesActivated = FALSE;				/*!< Global data indicating if transaction traces (using trace tool) is enabled or not. */
static int g_VisaEuropeModeEnabled = FALSE;			/*!< Global data indicating if Visa Europe Mode is enabled or not. */
static int g_VisaCashback = FALSE;					/*!< Global data indicating if cashback must be performed as defined by Visa payWave. */


//! \brief Main menu.
static const T_CST_HELPER_MENU_ITEM MainMenu[] = {
	{STD_MESS_MENU_PAYMENT_INPUT_TR_TYPE, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_MAIN_TEST, "CU_TOOLWARE.WGU"},
	{STD_MESS_MENU_MAIN_PARAMETERS, "CL_PARAMS.WGU"},
	{STD_MESS_MENU_PARAMS_MERCHANT_RESET_TSC, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_MAIN_BATCH, "CL_BATCH.WGU"},
	{STD_MESS_MENU_TEST_EACH_FCT, "CU_DEFAULT.WGU"}
};

//! \brief Batch menu.
static const T_CST_HELPER_MENU_ITEM BatchMenu[] = {
	{STD_MESS_MENU_PARAMS_BATCH_TOTALS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_BATCH_PRINT_LOG, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_BATCH_CLEAR, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_BATCH_LAST_TR, "CU_DEFAULT.WGU"}
};

//! \brief Test menu.
static const T_CST_HELPER_MENU_ITEM TestMenu[] = {
	{STD_MESS_MENU_TEST_DUMP_TR, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_DUMP_DB, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_LOOP, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_CHANGE_OUTPUT, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_TRACES, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_VISA_EUROPE, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TEST_VISA_CASHBACK, "CU_DEFAULT.WGU"}
};

//! \brief Menu for output data change (with printer).
static const T_CST_HELPER_MENU_ITEM TestMenuWithPrinter[] = {
	{STD_MESS_MENU_OUTPUT_COM0, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_OUTPUT_USB, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_OUTPUT_NONE, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_OUTPUT_PRINTER, "CU_DEFAULT.WGU"}
};

//! \brief Menu for output data change (without printer).
static const T_CST_HELPER_MENU_ITEM TestMenuWithoutPrinter[] = {
	{STD_MESS_MENU_OUTPUT_COM0, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_OUTPUT_USB, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_OUTPUT_NONE, "CU_DEFAULT.WGU"}
};

//! \brief Parameters menu.
static const T_CST_HELPER_MENU_ITEM ParametersMenu[] = {
	{STD_MESS_MENU_PARAMS_DUMP, "CU_DUMP.WGU"},
	{STD_MESS_MENU_PARAMS_DEFAULT, "CU_DEF_CNF.WGU"},
	{STD_MESS_MENU_PARAMS_ERASE_ALL, "CL_PARAMDEL.WGU"}
};

//! \brief Parameters dump menu.
static const T_CST_HELPER_MENU_ITEM ParametersMenuDump[] = {
	{STD_MESS_MENU_PARAMS_DUMP_ID, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_DUMP_AIDS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_DUMP_CA, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_DUMP_GLOBALS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_DUMP_KERNEL_SPECIFIC, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PARAMS_DUMP_ALL, "CU_DEFAULT.WGU"}
};



/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static int __CST_Menu_BatchTotals(void);
static int __CST_Menu_BatchPrintLog(void);
static int __CST_Menu_BatchClear(void);
static int __CST_Menu_BatchPrintLastTransaction(void);
static int __CST_Menu_Batch(void);
static int __CST_Menu_Test (void);
static int __CST_Menu_Parameters (void);
static int __CST_Menu_TestTransactionData(void);
static int __CST_Menu_TestTransactionDumpDatabase(void);
static int __CST_Menu_TestTransactionLoop(void);
static int __CST_Menu_TestTraces(void);
static int __CST_Menu_TestVisaEuropeMode(void);
static int __CST_Menu_DefaultParameters(void);
static int __CST_Menu_EraseParameters (void);
static int __CST_Menu_ParametersDump (void);
static int __CST_Menu_TestChooseOutput (void);

extern int IsPrinter(void);

/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////



//##################################################################
//################### BATCH MENU ###################################
//##################################################################


//! \brief Print a receipt with the total of the transactions in the batch
//! \return Always -1.

static int __CST_Menu_BatchTotals(void)
{
	CST_Batch_PrintTotals();
	return -1;
}



//! \brief Print the batch content
//! \return Always -1.

static int __CST_Menu_BatchPrintLog(void)
{
	CST_Batch_PrintBatchOverview();
	return -1;
}



//! \brief Print the last transaction saved in the batch
//! \return Always -1.

static int __CST_Menu_BatchPrintLastTransaction(void)
{
	CST_Batch_PrintLastTransaction();
	return -1;
}



//! \brief Updload the batch content and empty it
//! \return Always -1.

static int __CST_Menu_BatchClear(void)
{
	CST_Batch_Destroy();
	return -1;
}



//! \brief Batch menu management
//! \return Always -1.

static int __CST_Menu_Batch(void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu(STD_MESS_MENU_MAIN_BATCH, nChoice, NUMBER_OF_ITEMS(BatchMenu), BatchMenu, FALSE);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:
				nResult = __CST_Menu_BatchTotals();
				break;
			case 1:
				nResult = __CST_Menu_BatchPrintLog();
				break;
			case 2:
				nResult = __CST_Menu_BatchClear();
				break;
			case 3:
				nResult = __CST_Menu_BatchPrintLastTransaction();
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

//! \brief Enables/disables the transaction data dumping
//! \return Always -1.

static int __CST_Menu_TestTransactionData(void)
{
	Helper_DisplayMessage(STD_MESS_MENU_TEST_DUMP_TR, ERASE, HELPERS_MERCHANT_LINE_2);
		
	if (g_DumpTransactionData == FALSE)
	{
		g_DumpTransactionData = TRUE;
		Helper_DisplayMessage(STD_MESS_ENABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	else
	{
		g_DumpTransactionData = FALSE;
		Helper_DisplayMessage(STD_MESS_DISABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	
	Helper_RefreshScreen(WAIT);

	return -1;
}


//! \brief Enables/disables the dabase dumping.
//! \return Always -1.

static int __CST_Menu_TestTransactionDumpDatabase(void)
{
	Helper_DisplayMessage(STD_MESS_MENU_TEST_DUMP_DB, ERASE, HELPERS_MERCHANT_LINE_2);
		
	if (g_DumpTransactionDatabase == FALSE)
	{
		g_DumpTransactionDatabase = TRUE;
		Helper_DisplayMessage(STD_MESS_ENABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	else
	{
		g_DumpTransactionDatabase = FALSE;
		Helper_DisplayMessage(STD_MESS_DISABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	
	Helper_RefreshScreen(WAIT);

	return -1;
}



//! \brief Choose the output peripheral to get the dumps (parameters or transaction data).
//! \return Always -1.

static int __CST_Menu_TestChooseOutput (void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	nResult = 0;

	do
	{
		if (!IsPrinter())
			nChoice = HelperDisplayMenu(STD_MESS_MENU_OUTPUT_TITLE, nChoice, NUMBER_OF_ITEMS(TestMenuWithoutPrinter), TestMenuWithoutPrinter, FALSE);
		else
			nChoice = HelperDisplayMenu(STD_MESS_MENU_OUTPUT_TITLE, nChoice, NUMBER_OF_ITEMS(TestMenuWithPrinter), TestMenuWithPrinter, FALSE);

		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0: // COM0
				CST_DumpData_SetOutputId (CST_OUTPUT_COM0);
				nResult = -1;
				break;

			case 1: // USB
				CST_DumpData_SetOutputId (CST_OUTPUT_USB);
				nResult = -1;
				break;

			case 2: // NONE
				CST_DumpData_SetOutputId (CST_OUTPUT_NONE);
				nResult = -1;
				break;

			case 3: //Printer (if present)
				if (IsPrinter())
				{
					CST_DumpData_SetOutputId (CST_OUTPUT_PRINTER);
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



//! \brief Enables/disables the transaction loop mode
//! \return Always -1.

static int __CST_Menu_TestTransactionLoop(void)
{
	Helper_DisplayMessage(STD_MESS_MENU_TEST_LOOP, ERASE, HELPERS_MERCHANT_LINE_2);
		
	if (g_TransactionLoop == FALSE)
	{
		g_TransactionLoop = TRUE;
		Helper_DisplayMessage(STD_MESS_ENABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	else
	{
		g_TransactionLoop = FALSE;
		Helper_DisplayMessage(STD_MESS_DISABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}

	Helper_RefreshScreen(WAIT);

	return -1;
}

//! \brief  Enables/disables the traces (debug purpose)
//! \return Always -1.

static int __CST_Menu_TestTraces(void)
{
	Helper_DisplayMessage(STD_MESS_MENU_TEST_TRACES, ERASE, HELPERS_MERCHANT_LINE_2);

	if (g_TracesActivated == FALSE)
	{
		g_TracesActivated = TRUE;
		Helper_DisplayMessage(STD_MESS_ENABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	else
	{
		g_TracesActivated = FALSE;
		Helper_DisplayMessage(STD_MESS_DISABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	
	Helper_RefreshScreen(WAIT);

	return -1;
}



//! \brief Activate/deactivate the "Visa Europe Mode"
//! \return Always -1.

static int __CST_Menu_TestVisaEuropeMode(void)
{
	Helper_DisplayMessage(STD_MESS_MENU_TEST_VISA_EUROPE, ERASE, HELPERS_MERCHANT_LINE_2);

	if (g_VisaEuropeModeEnabled == FALSE)
	{
		g_VisaEuropeModeEnabled = TRUE;
		Helper_DisplayMessage(STD_MESS_ENABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	else
	{
		g_VisaEuropeModeEnabled = FALSE;
		Helper_DisplayMessage(STD_MESS_DISABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	
	Helper_RefreshScreen(WAIT);
		
	return -1;
}



//! \brief Activate/deactivate the "Visa cashback Mode"
//! \return Always -1.

static int __CST_Menu_TestVisaCashback(void)
{
	Helper_DisplayMessage(STD_MESS_MENU_TEST_VISA_CASHBACK, ERASE, HELPERS_MERCHANT_LINE_2);

	if (g_VisaCashback == FALSE)
	{
		g_VisaCashback = TRUE;
		Helper_DisplayMessage(STD_MESS_ENABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	else
	{
		g_VisaCashback = FALSE;
		Helper_DisplayMessage(STD_MESS_DISABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	
	Helper_RefreshScreen(WAIT);
		
	return -1;
}



//! \brief Test if transaction loop mode has been activated.
//! \return
//!		- \ref TRUE if loop is activated.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsTransactionLoopOn (void)
{
	return (unsigned char)g_TransactionLoop;
}	



//! \brief Test if transaction data dumping is TRUE or FALSE.
//! \return
//!		- \ref TRUE if dump mode is activated.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsTransactionDataDumpingOn (void)
{
	return (unsigned char)g_DumpTransactionData;
}	



//! \brief Test if transaction database dumping is TRUE or FALSE.
//! \return
//!		- \ref TRUE if database dumping is activated.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsTransactionDatabaseDumpingOn (void)
{
	return (unsigned char)g_DumpTransactionDatabase;
}	



//! \brief Test if Visa Europe Mode is activated or not.
//! \return
//!		- \ref TRUE if Visa Europe Mode is activated.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsVisaEuropeModeOn (void)
{
	return (unsigned char)g_VisaEuropeModeEnabled;
}	



//! \brief Test if cashback transaction type must be as defined by Visa payWave (idem DEBIT transaction type: 0x00).
//! \return
//!		- \ref TRUE if it is a Visa payWave cashback.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsVisaCashback(void)
{
	return (unsigned char)g_VisaCashback;
}	



//! \brief Test if Transaction Type entry is possible or not.
//! \return
//!		- \ref TRUE if Transaction Type entry is activated.
//!		- \ref FALSE if not.

unsigned char CST_Menu_IsEnableInputTransactionType (void)
{
	return (unsigned char)g_EnableInputTransactionType;
}	


//! \brief Action enable/disable "TransactionType" information to input.
//! \return Always -1.

static int __CST_Menu_InputTransactionType(void)
{
	Helper_DisplayMessage(STD_MESS_MENU_PAYMENT_INPUT_TR_TYPE, ERASE, HELPERS_MERCHANT_LINE_2);


    if (g_EnableInputTransactionType == FALSE)
    {
        g_EnableInputTransactionType = TRUE;
		Helper_DisplayMessage(STD_MESS_ENABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
    }
    else
    {
        g_EnableInputTransactionType = FALSE;
		Helper_DisplayMessage(STD_MESS_DISABLE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
    }
    
	Helper_RefreshScreen(WAIT);
		
	return -1;
}


//! \brief Test menu management
//! \return Always -1.

static int __CST_Menu_Test(void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu(STD_MESS_MENU_TEST_TITLE, nChoice, NUMBER_OF_ITEMS(TestMenu), TestMenu, FALSE);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:
				nResult = __CST_Menu_TestTransactionData();
				break;

			case 1:
				nResult = __CST_Menu_TestTransactionDumpDatabase();
				break;

			case 2:
				nResult = __CST_Menu_TestTransactionLoop();
				break;
				
			case 3:
				nResult = __CST_Menu_TestChooseOutput();
				break;

			case 4:
				nResult = __CST_Menu_TestTraces();
				break;
				
			case 5:
				nResult = __CST_Menu_TestVisaEuropeMode();
				break;

			case 6:
				nResult = __CST_Menu_TestVisaCashback();
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

//! \brief Read default parameters and update .SAV file with it
//! \return Always -1.

static int __CST_Menu_DefaultParameters(void)
{
	Helper_DisplayMessage(STD_MESS_UPDATING_PARAMS, ERASE, HELPERS_MERCHANT_LINE_2);
	Helper_DisplayMessage(STD_MESS_IN_PROGRESS, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	Helper_RefreshScreen(NOWAIT);
	
	// Read default parameters
	CST_Parameters_ReadDefaultParameters(&pTreeDefaultParam);
	if (CST_Parameters_SaveParam (pTreeDefaultParam, NULL, 0) != 0)
	{
		Helper_DisplayMessage(STD_MESS_UPDATING_PARAMS, ERASE, HELPERS_MERCHANT_LINE_2);
		Helper_DisplayMessage(STD_MESS_ERROR, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	else // Parameter has been correctly read/saved
	{
		CST_Parameters_InitParameters(&pTreeCurrentParam);
		pTreeCurrentParam = pTreeDefaultParam;
		pTreeDefaultParam = NULL;

		// Check the consistency between the terminal parameters and the reader parameters.
		// If parameters are not consistent, parameters are loaded in the reader.
		CST_Parameters_CheckConsistency();

		Helper_DisplayMessage(STD_MESS_UPDATING_PARAMS, ERASE, HELPERS_MERCHANT_LINE_2);
		Helper_DisplayMessage(STD_MESS_COMPLETE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}

	Helper_RefreshScreen(WAIT);

	// Check parameters CA keys
	CST_Parameters_CheckCaKeysCrc(pTreeCurrentParam);
	
	return -1;
}


//! \brief Erase all the application parameters.
//! \return Always -1.

static int __CST_Menu_EraseParameters (void)
{

	Helper_DisplayMessage(STD_MESS_ERASING_PARAMS, ERASE, HELPERS_MERCHANT_LINE_2);
	Helper_DisplayMessage(STD_MESS_IN_PROGRESS, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	Helper_RefreshScreen(NOWAIT);

	if(CST_Tests_EraseParameters() != SDI_STATUS_OK)
	{
		Helper_DisplayMessage(STD_MESS_ERASING_PARAMS, ERASE, HELPERS_MERCHANT_LINE_2);
		Helper_DisplayMessage(STD_MESS_ERROR, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}
	else
	{
		Helper_DisplayMessage(STD_MESS_ERASING_PARAMS, ERASE, HELPERS_MERCHANT_LINE_2);
		Helper_DisplayMessage(STD_MESS_COMPLETE, NO_ERASE, HELPERS_MERCHANT_LINE_3);
	}

	Helper_RefreshScreen(WAIT);
	
	return -1;
}



//! \brief Parameters menu management
//! \return Always -1.

static int __CST_Menu_Parameters (void)
{
	int nChoice;
	int nResult;


	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu(STD_MESS_MENU_MAIN_PARAMETERS, nChoice, NUMBER_OF_ITEMS(ParametersMenu), ParametersMenu, TRUE);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:			// Trace parameters on printer
				nResult = __CST_Menu_ParametersDump();
				break;
			case 1:			// Read default parameters and save it in file (for next start)
				nResult = __CST_Menu_DefaultParameters();
				break;
			case 2:			// Scratch parameters 
				nResult = __CST_Menu_EraseParameters();
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



//! \brief Parameters menu management for data dumping
//! \return Always -1.

static int __CST_Menu_ParametersDump (void)
{
	int nChoice = 0;
	int nResult;
	TLV_TREE_NODE hTlvTreeIn;
	TLV_TREE_NODE hTlvTreeOut = NULL;
			

	hTlvTreeIn = TlvTree_New(0);

	if (hTlvTreeIn != NULL)
	{
		nResult = SDI_Payment_GetParams (nSDSAAppliId, hTlvTreeIn, &hTlvTreeOut);

		if(nResult == SDI_STATUS_DISCONNECTED)
			CST_ReconnectionProcess();

		if (hTlvTreeOut != NULL)
		{
			do
			{
				nChoice = HelperDisplayMenu(STD_MESS_MENU_PARAMS_DUMP_TITLE, nChoice, NUMBER_OF_ITEMS(ParametersMenuDump), ParametersMenuDump, FALSE);
				if (nChoice >= 0)
				{
					switch(nChoice)
					{
					case 0:			// Identifier
						CST_Parameters_DumpIdentificationLabel(hTlvTreeOut);
						nResult = 0;
						break;
					case 1:			// AIDs
						CST_Parameters_DumpAids (hTlvTreeOut);
						nResult = 0;
						break;
					case 2:			// CA Keys
						CST_Parameters_DumpCaKeys (hTlvTreeOut);
						nResult = 0;
						break;
					case 3:			// Globals
						CST_Parameters_DumpGlobals (hTlvTreeOut);
						nResult = 0;
						break;
					case 4:			// Kernel specific
						CST_Parameters_DumpKernelSpecific (hTlvTreeOut);
						nResult = 0;
						break;
					case 5:			// All
						CST_Parameters_DumpIdentificationLabel(hTlvTreeOut);
						CST_Parameters_DumpAids (hTlvTreeOut);
						CST_Parameters_DumpCaKeys (hTlvTreeOut);
						CST_Parameters_DumpGlobals (hTlvTreeOut);
						CST_Parameters_DumpKernelSpecific (hTlvTreeOut);
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

			TlvTree_ReleaseEx (&hTlvTreeOut);
		}
		TlvTree_ReleaseEx (&hTlvTreeIn);
	}
	else
	{
		GTL_Traces_TraceDebug ("__CST_Menu_ParametersDump : error when creating the TLV-Tree");
	}

	return nChoice;
}



//##################################################################
//################### GLOBAL MENU ##################################
//##################################################################

//! \brief Global menu management

void CST_Menu_MainMenuDisplay(void)
{
	int nChoice;
	int nResult;

	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu(STD_MESS_MENU_MAIN_TITLE, nChoice, NUMBER_OF_ITEMS(MainMenu), MainMenu, TRUE);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:
				nResult = __CST_Menu_InputTransactionType();
				break;
			case 1:
				nResult = __CST_Menu_Test();
				break;
			case 2:
				nResult = __CST_Menu_Parameters();
				break;
			case 3:
				CST_Batch_InitTransactionSeqCounter (TRUE);
				nResult = -1;
				break;
			case 4:
				nResult = __CST_Menu_Batch();
				break;
			case 5:
				nResult = CST_Tests_ManageMenu();
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
