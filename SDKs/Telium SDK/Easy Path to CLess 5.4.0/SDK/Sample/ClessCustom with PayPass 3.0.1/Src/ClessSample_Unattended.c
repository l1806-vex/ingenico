/**
 * \author	Ingenico
 * \author	Copyright (c) 2012 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 */

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define TXN_START_AMOUNT_AUTH_ENTRY				0
#define TXN_START_TTYPE_ENTRY					1
#define TXN_START_AMOUNT_OTHER_ENTRY			2

#define C_TRANSACTION_TYPE_VOID					0xFF


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

typedef struct
{
	unsigned long ulAmountAuth;			//! Amount, Authorized.
	unsigned long ulAmountOther;		//! Amount, Other.
	int nTransactionStartStep;			//!	Transaction Start Step.
	int nTransactionType;				//! Transaction Type.
	int bExplicitSelection;				//!	Indicates if explicit selection is used or not.
} T_UNATTENDED_START_TRANSACTION_DATA;


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

T_UNATTENDED_START_TRANSACTION_DATA	gs_tUnattendedTransactionData;


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static word __ClessSample_Unattended_IamTask(void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//!	\brief Identify if the Unattended mechanism has to be used.
//!	\return
//!	- \a TRUE if unattended mechanism shall be used.
//!	- \a FALSE if normal processing has to be used.

int ClessSample_Unattended_IsUnattendedMechanism (void)
{
	int nInternalDeviceType;
	int nResult = FALSE;

	// Determine the condition that match the undatteded devices (CAD30, iUP, etc)
	nInternalDeviceType = ClessSample_Common_GetTerminalType();

	nResult =  ((nInternalDeviceType == TERM_MR40) ||
				(nInternalDeviceType == TERM_IUN180) ||
				(nInternalDeviceType == TERM_IUN150) ||
				(nInternalDeviceType == TERM_IUN230) ||
				(nInternalDeviceType == TERM_IST150));

	return (nResult);
}



//! \brief Processing for Unattended environment on the AFTER RESET entry point.
//! \param[in] Application Number.

void ClessSample_Unattended_AfterReset (NO_SEGMENT no)
{
/*	int iError_p;
	int nInternelDeviceType;*/

	// Start ComEvent Task
	ClessSample_Comevent_Start(no);

	ClessSample_Unattended_StartIamTask();
    
	// If the device is an iUP, then, we have to open the iUP library
/*	if (SystemFioctl (SYS_FIOCTL_GET_TERMINAL_TYPE, &nInternelDeviceType) == 0)
	{
		if (nInternelDeviceType == TERM_IUN230)
		{
			iError_p = ExtReaderlib_open();
			
			if (iError_p == ERR_READER_OK)
			{
				iError_p = ExtReader_SysInit(_IUN350_READER);
				
				if (iError_p != ERR_READER_OK)
					GTL_Traces_TraceDebug ("ExtReader_SysInit error %d", iError_p);
			}
			else
			{
				GTL_Traces_TraceDebug("ExtReaderlib_open error = %d", iError_p);
			}
		}
	}*/

	// Set the output to USB
	ClessSample_DumpData_DumpSetOutputId (CUSTOM_OUTPUT_USB);
}



//! \brief Specific messages displayed for unattended environments.

void ClessSample_Unattended_IdleMessage (void)
{
	// Check if UCM component is loaded before
	if (ClessSample_Unattended_IsPinPadUPPwithUCMC())
	{
		iLIBUCM_Display_Clear(UCMC_PPAD);
		iLIBUCM_Display_Message (UCMC_PPAD, "    WELCOME", 1);
	}
}



//! \brief Indicates if UCMC is loaded and an UPP is connected.
//! \return \a TRUE if UCMC is loaded and UPP is connetced, \a FALSE else.

int ClessSample_Unattended_IsPinPadUPPwithUCMC (void)
{
	int nResult = FALSE;

	if (PSQ_Is_Ucm_Behaviour())
		nResult = (iLIBUCM_Display_Exist(UCMC_PPAD) == PARAM_TYPE_UPP);

	return (nResult);
}



//! \brief Indicates if it is an unattended terminal with a display (only the iUP250 for the moment) with the UCM component.
//! \return \a TRUE if UCMC is present is loaded and the terminal is unattended with a screen, \a FALSE else.

int ClessSample_Unattended_IsUnattendedTerminalWithDisplayWithUCMC (void)
{
	int nResult = FALSE;

	if (PSQ_Is_Ucm_Behaviour())
	{
		// If the device is an iUP, then, we have to open the iUP library
		nResult = (ClessSample_Common_GetTerminalType() == TERM_IUN230);
	}

	return (nResult);
}



//! \brief Indicates if UCMC is present or not.
//! \return \a TRUE if UCMC is present, \a FALSE else.

int ClessSample_Unattended_IsUCMCpresent (void)
{
	return (PSQ_Is_Ucm_Behaviour());
}



//!	\brief Output data .
//!	\param[in] pc_x_String String to be output.

void ClessSample_Unattended_PrintDump (const char* pc_x_String)
{
	if (ClessSample_DumpData_DumpOpenOutputDriver())		/* Send on link */
	{
		ClessSample_DumpData ("%s", pc_x_String);
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpCloseOutputDriver();
	}
}



//! \brief Initialise the Unattended transaction data.

void ClessSample_Unattended_InitTransactionStartData (void)
{
	gs_tUnattendedTransactionData.ulAmountAuth = 0; //! Amount, Authorized.
	gs_tUnattendedTransactionData.ulAmountOther = 0; //! Amount, Other.
	gs_tUnattendedTransactionData.nTransactionStartStep = TXN_START_AMOUNT_AUTH_ENTRY; //!	Transaction Start Step.
	gs_tUnattendedTransactionData.nTransactionType = C_TRANSACTION_TYPE_VOID; //! Transaction Type.
	gs_tUnattendedTransactionData.bExplicitSelection = TRUE; //!	Indicates if explicit selection is used or not.
}


//! \brief Get unattended mode transaction type.
//! \return The transaction type in unattended mode.

int ClessSample_Unattended_GetTransactionType (void)
{
	return (gs_tUnattendedTransactionData.nTransactionType);
}



//! \brief Get unattended mode Amount, Authorized.
//! \return The Amount, Authorized in unattended mode.

unsigned long ClessSample_Unattended_GetAmountAuth (void)
{
	return (gs_tUnattendedTransactionData.ulAmountAuth);
}



//! \brief Get unattended mode Amount, Other.
//! \return The Amount, Other in unattended mode.

unsigned long ClessSample_Unattended_GetAmountOther (void)
{
	return (gs_tUnattendedTransactionData.ulAmountOther);
}


//! \brief Analyse the command provided by the user on COM0 port, and execute it.
//! \param[in] nCommandLength Length of \a pCommand.
//!	\param[in] pCommand Command itself.

void ClessSample_Unattended_ExecuteCommand (int nCommandLength, char * pCommand)
{
	int bStartTransaction = FALSE;
	int nChoice;
	MSGinfos tDisplayMsg;

	if (nCommandLength > 0)
	{
		///////////////////////////////////////////////////////////////////////////////////////////
		if (pCommand[0] == '?') // Command line management
		{
			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();

			ClessSample_Unattended_PrintDump("'?'        : help");
			ClessSample_Unattended_PrintDump("'spe'      : start a transction in specific mode");
			ClessSample_Unattended_PrintDump("'debug'    : (on/off) Activates the kernel traces (dev purpose only)");
			ClessSample_Unattended_PrintDump("'loop'     : (on/off) Activates the loop mode");
			ClessSample_Unattended_PrintDump("'dumptr'   : (on/off) Dump transaction data");
			ClessSample_Unattended_PrintDump("'dumpdb'   : (on/off) Dump db data");
			ClessSample_Unattended_PrintDump("'trtype'   : (on/off) Input the transaction type");
			ClessSample_Unattended_PrintDump("'apdude'   : (on/off) Dump the DE exchanges and APDU");
			ClessSample_Unattended_PrintDump("'clean'    : send CLEAN (only available on idle)");
			ClessSample_Unattended_PrintDump("'paraminfo': get the parameters information (CLESSCUST and DEKDET)");
			ClessSample_Unattended_PrintDump("Note: when a transaction is in progress, press any key to send a STOP");
			///ttestall(0,500);
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		else if ((nCommandLength >= 5) && (memcmp(pCommand, "debug", 5) == 0))
		{
			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();

			ClessSample_Menu_TestTraces();

			if (ClessSample_Menu_IsTraceActivated())
				ClessSample_Unattended_PrintDump("trace:on");
			else
				ClessSample_Unattended_PrintDump("trace:off");
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		else if ((nCommandLength >= 4) && (memcmp(pCommand, "loop", 4) == 0))
		{
			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();

			ClessSample_Menu_TestTransactionLoop();

			if (ClessSample_Menu_IsTransactionLoopOn())
				ClessSample_Unattended_PrintDump("loop:on");
			else
				ClessSample_Unattended_PrintDump("loop:off");
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		else if ((nCommandLength >= 6) && (memcmp(pCommand, "dumptr", 6) == 0))
		{
			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();

			ClessSample_Menu_TestTransactionData();

			if (ClessSample_Menu_IsTransactionDataDumpingOn())
				ClessSample_Unattended_PrintDump("dumptr:on");
			else
				ClessSample_Unattended_PrintDump("dumptr:off");
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		else if ((nCommandLength >= 6) && (memcmp(pCommand, "dumpdb", 6) == 0))
		{
			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();

			ClessSample_Menu_TestTransactionDumpDatabase();

			if (ClessSample_Menu_IsTransactionDatabaseDumpingOn())
				ClessSample_Unattended_PrintDump("dumpdb:on");
			else
				ClessSample_Unattended_PrintDump("dumpdb:off");
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		else if ((nCommandLength >= 5) && (memcmp(pCommand, "clean", 5) == 0))
		{
			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();

			ClessSample_Unattended_PrintDump("CLEAN");

			///if(ClessSample_Torn_IsRecoverySupported())
				ClessSample_Torn_CleanLog();
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		else if ((nCommandLength >= 9) && (memcmp(pCommand, "autoclean", 9) == 0))
		{
			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();

			// Change the "auto clean" status
			ClessSample_Menu_TornAutoCleanLog();

			if (ClessSample_Menu_IsAutomaticCleanTornOn())
				ClessSample_Unattended_PrintDump("AUTO CLEAN: ON");
			else
				ClessSample_Unattended_PrintDump("AUTO CLEAN: OFF");
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		else if ((nCommandLength >= 6) && (memcmp(pCommand, "trtype", 6) == 0))
		{
			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();
			
			ClessSample_Menu_TestInputTransactionType();

			if (ClessSample_Menu_IsEnableInputTransactionType())
				ClessSample_Unattended_PrintDump("trtype:on");
			else
				ClessSample_Unattended_PrintDump("trtype:off");
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		else if ((nCommandLength >= 3) && (memcmp(pCommand, "spe", 3) == 0))
		{
			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();
			
			ClessSample_Unattended_PrintDump("Specific mode txn");

			// Start the transaction in specific mode
			ClessSample_Comevent_Manage (DO_CLOSE);
			// Start the transaction
			ClessSample_ExplicitSelection_Process (TRUE);
			ClessSample_Comevent_Manage (DO_OPEN);

			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		else if ((nCommandLength >= 6) && (memcmp(pCommand, "apdude", 6) == 0))
		{
			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();
			
			// Activates the APDU DE dump
			ClessSample_Menu_TestTransactionDumpApduDataExchange();
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		else if ((nCommandLength >= 9) && (memcmp(pCommand, "paraminfo", 9) == 0))
		{
			// Init transaction start conditions
			ClessSample_Unattended_InitTransactionStartData();

			// Dump payment related parameter identifier (CLESSCUST.PAR)
			ClessSample_Parameters_DumpIdentificationLabel(pTreeCurrentParam);

			// Dump DE related parameter infos (DEKDET.PAR)
			ClessSample_DataExchange_DumpEvalHeaderInformation (pTreeCurrentDataExchange);

		}
		///////////////////////////////////////////////////////////////////////////////////////////
		else // Keep value
		{
			switch (gs_tUnattendedTransactionData.nTransactionStartStep)
			{
			////////////////////////////////////////////////////////////////////////
			case (TXN_START_AMOUNT_AUTH_ENTRY):
				gs_tUnattendedTransactionData.ulAmountAuth = atol(pCommand); // \0 of the end has been set by caller

				if ((gs_tUnattendedTransactionData.ulAmountAuth) ||
					((gs_tUnattendedTransactionData.ulAmountAuth == 0) && (pCommand[0] == '0') && (pCommand[1] == 0)))
				{
					if (ClessSample_Menu_IsEnableInputTransactionType())
					{
						gs_tUnattendedTransactionData.nTransactionStartStep = TXN_START_TTYPE_ENTRY;
						ClessSample_Unattended_PrintDump("Enter the Transaction Type : Debit:0 / Cash:1 / Refund:2 / CashBack:3 / Manual Cash:4 / Cash Deposit:5");
					}
					else
					{
						gs_tUnattendedTransactionData.nTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_DEBIT;
						bStartTransaction = TRUE;
					}
				}
				else
				{
					// Raz the static data
					ClessSample_Unattended_InitTransactionStartData();

					///GTL_Traces_TraceDebug(pCommand);
					ClessSample_Unattended_PrintDump("!!! Invalid Command !!!");
					ttestall(0,300);
					break;
				}

				break;

			////////////////////////////////////////////////////////////////////////
			case (TXN_START_TTYPE_ENTRY):
				nChoice = atoi(pCommand); // \0 of the end has been set by caller
				switch(nChoice)
				{
				case 0:
					gs_tUnattendedTransactionData.nTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_DEBIT;
					ClessSample_Term_Read_Message(STD_MESS_DEBIT, PSQ_Give_Language(), &tDisplayMsg);
					ClessSample_Unattended_PrintDump(tDisplayMsg.message);
					bStartTransaction = TRUE;
					gs_tUnattendedTransactionData.ulAmountOther = 0;
					break;
				case 1:
					gs_tUnattendedTransactionData.nTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_CASH;
					ClessSample_Term_Read_Message(STD_MESS_CASH, PSQ_Give_Language(), &tDisplayMsg);
					ClessSample_Unattended_PrintDump(tDisplayMsg.message);
					bStartTransaction = TRUE;
					gs_tUnattendedTransactionData.ulAmountOther = 0;
					break;
				case 2:
					gs_tUnattendedTransactionData.nTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_REFUND;
					ClessSample_Term_Read_Message(STD_MESS_REFUND, PSQ_Give_Language(), &tDisplayMsg);
					ClessSample_Unattended_PrintDump(tDisplayMsg.message);
					bStartTransaction = TRUE;
					gs_tUnattendedTransactionData.ulAmountOther = 0;
					break;
				case 3: // Cashback
					gs_tUnattendedTransactionData.nTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_PURSH_WITH_CASHBACK;
					ClessSample_Term_Read_Message(STD_MESS_CASHBACK, PSQ_Give_Language(), &tDisplayMsg);
					ClessSample_Unattended_PrintDump(tDisplayMsg.message);
					gs_tUnattendedTransactionData.nTransactionStartStep = TXN_START_AMOUNT_OTHER_ENTRY;
					ClessSample_Unattended_PrintDump("Enter the Amount Other (shall be <= Amount Auth)");
					gs_tUnattendedTransactionData.ulAmountOther = 0;
					break;
				case 4:
					gs_tUnattendedTransactionData.nTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_MANUAL_CASH;
					ClessSample_Term_Read_Message(STD_MESS_MENU_MAIN_MANUAL_CASH, PSQ_Give_Language(), &tDisplayMsg);
					ClessSample_Unattended_PrintDump(tDisplayMsg.message);
					bStartTransaction = TRUE;
					gs_tUnattendedTransactionData.ulAmountOther = 0;
					break;
				case 5:
					gs_tUnattendedTransactionData.nTransactionType = CLESS_SAMPLE_TRANSACTION_TYPE_CASH_DEPOSIT;
					ClessSample_Term_Read_Message(STD_MESS_MENU_MAIN_CASH_DEPOSIT, PSQ_Give_Language(), &tDisplayMsg);
					ClessSample_Unattended_PrintDump(tDisplayMsg.message);
					bStartTransaction = TRUE;
					gs_tUnattendedTransactionData.ulAmountOther = 0;
					break;
				default:
					// Raz the static data
					ClessSample_Unattended_InitTransactionStartData();

					///GTL_Traces_TraceDebug(pCommand);
					ClessSample_Unattended_PrintDump("!!! Invalid transaction type !!!");
					break;
				}
				break;
			
			////////////////////////////////////////////////////////////////////////
			case (TXN_START_AMOUNT_OTHER_ENTRY):
				gs_tUnattendedTransactionData.ulAmountOther = atol(pCommand); // \0 of the end has been set by caller

				if ((gs_tUnattendedTransactionData.ulAmountOther) ||
					((gs_tUnattendedTransactionData.ulAmountOther == 0) && (pCommand[0] == '0') && (pCommand[1] == 0)))
				{
					bStartTransaction = TRUE;
				}
				else
				{
					// Raz the static data
					ClessSample_Unattended_InitTransactionStartData();

					///GTL_Traces_TraceDebug(pCommand);
					ClessSample_Unattended_PrintDump("!!! Invalid Amount Other !!!");
					ttestall(0,300);
					break;
				}
				break;

			////////////////////////////////////////////////////////////////////////
			default:
				// Raz the static data
				ClessSample_Unattended_InitTransactionStartData();

				ClessSample_Unattended_PrintDump("!!! Unknown automate state !!!");
				break;
			}
		    
			if (bStartTransaction)
			{
				if (gs_tUnattendedTransactionData.bExplicitSelection)
				{
					ClessSample_Comevent_Manage (DO_CLOSE);
					// Start the transaction
					ClessSample_ExplicitSelection_Process (FALSE);
					ClessSample_Comevent_Manage (DO_OPEN);
					
					// Init transaction start conditions
					ClessSample_Unattended_InitTransactionStartData();
				}
				else // Implicit selection
				{
					// Raz the static data
					ClessSample_Unattended_InitTransactionStartData();

					ClessSample_Unattended_PrintDump("!!! Implicit selection not available !!!");
				}
			}
		} // End keep value
	}
}






/////////////////////////////////////////////////////////////////
//          #  ###  ##  #     #####  ###   #### #   #          //
//          # #   # ## ##       #   #   # #     #  #           //
//          # ##### # # #       #   #####  ###  ###            //
//          # #   # #   #       #   #   #     # #  #           //
//          # #   # #   #       #   #   # ####  #   #          //
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static   S_MESSAGE_IAM   message;
static   t_topstack     *TaskHdl1;


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static word __ClessSample_Unattended_IamTask(void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief IAM task processing.

static word __ClessSample_Unattended_IamTask(void)
{
	//char strmsg[128];
	int cr;
  
	if (Register_Mailbox_User(TaskIam1)== FALSE)
		exit(E_SQ_REGISTER_MAILBOX);

	while (1)
	{
		cr = ttestall( MSG, 50 );
		if (cr & MSG)
		{
			while ( Read_Message( &message,0 )== TRUE )
			{
				unsigned char TmpStr[60];
				memcpy(TmpStr, message.value, message.length);
				message.value[message.length] = 0; // String terminated
				//GTL_Traces_TraceDebug("InterTask1 message : S:%02X T:%02X L:%02X\nV:%s\n", message.sender, message.type, message.length, message.value);
				ClessSample_DumpData_DumpSetOutputId(CUSTOM_OUTPUT_COM0);
				ClessSample_Unattended_PrintDump((char*)message.value);		
			} 
		}
	} 
	return 0;
}



//! \brief Start the IAM task
//! \return The task number.

int ClessSample_Unattended_StartIamTask(void)
{
	int num_task;

	// Launch the task
	TaskHdl1 = fork(__ClessSample_Unattended_IamTask,NULL,0);

	// Get the task number
	num_task = GiveNoTask (TaskHdl1);

	GTL_Traces_TraceDebug("start_iam_task %x",GiveNoTask(TaskHdl1));

	return (num_task);
}



/////////////////////////////////////////////////////////////////
//  ####  ###  #   #  #### ##### #      ##### ###   #### #   # //
// #     #   # ##  # #     #     #        #  #   # #     #  #  //
// #     ##### # # # #     ####  #        #  #####  ###  ###   //
// #     #   # #  ## #     #     #        #  #   #     # #  #  //
//  #### #   # #   #  #### ##### #####    #  #   # ####  #   # //
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static word g_wCurrentCancelTask = 0xFF; // Init the custom application task number
static int g_ScanningCancelTaskRunning = FALSE; //Task is not running
word g_ScanningCancelTask;
t_topstack * g_tsScanningCancel_task_handle;
static unsigned char  g_bScanningCancel_task_to_be_killed = FALSE; // Task has not to be killed


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static void __ClessSample_Unattended_InitCancelVariables (void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Waits an event on keyboard, swipe or chip.

static word __ClessSample_Unatteded_StartCancelTask (void)
{
	int nEvent, bSendCancel, bWaitToBeKilled, bStartIndication;
	FILE * hCOM0;
	unsigned char ucBuffer[1];
	
	bStartIndication = TRUE;
	bWaitToBeKilled = FALSE;
	bSendCancel = FALSE;
	g_ScanningCancelTaskRunning = TRUE; // Indicates the task is running
	g_ScanningCancelTask = CurrentTask(); // get the Scanning task ID and store it in a global variable

	// Open the keyboard driver
	hCOM0 = fopen("COM0","rw");
	format("COM0",9600,8,1,NO_PARITY,EVEN,0);

	while (!g_bScanningCancel_task_to_be_killed) // While the task is not to be killed by the custom application
	{
		if (bWaitToBeKilled) // A cancel has been sent to the Engine, task is waiting to be killed
		{
			if (hCOM0)
			{
				fclose (hCOM0); // Close the keyboard driver
				hCOM0 = NULL;
			}
			g_ScanningCancelTaskRunning = FALSE; // Indicate to the custom application the task is waiting to be killed
			ttestall (0,0); // Wait to be killed
		}

		if (bStartIndication)
		{
			bStartIndication = FALSE;

			// Allows to 
			if (SignalEvent (g_wCurrentCancelTask, (tEvent)E_USER_EVENT_START) != cOK)
				GTL_Traces_DiagnosticText("Cancel task 2: Error when setting the event\n");
		}
		
		nEvent = ttestall (COM0 | USER_EVENT, 1); // g_ListOfEvent contains the list of other cancel events (here it is CAM0 and SWIPE)

		// According to the event that may have occurred
		switch(nEvent)
		{
		case (0): // Timeout, no event, continue scanning
		case USER_EVENT: // User event (from main task), it indicates the task is going to be killed (because g_bScanning_task_to_be_killed has been set to TRUE by the custom application
			break;

		case COM0: // Keyboard event
		default: // Other event (swipe, chip, etc).
			bSendCancel = TRUE;
			break;
		}

		// If cless transaction shall be cancelled
		if (bSendCancel)
		{
			ucBuffer[0] = 0x17; // Code of RED button
			input_sim ("KEYBOARD", 1, ucBuffer); // Simulate the RED key is pressed
			bWaitToBeKilled = TRUE; // Task is going to wait to be killed

			// If unattended with UCMC, send an event to the scanning task
			if (ClessSample_Unattended_IsUnattendedMechanism())
				if (ClessSample_Unattended_IsUCMCpresent())
					if (SignalEvent (g_ScanningTask, (tEvent)E_USER_EVENT_CANCEL_UNATTENDED_UCMC) != cOK)
						GTL_Traces_DiagnosticText ("COM0 Cancel Task: Error when setting the event to the scanning task");
		}
	} // End While

	// The task is stopped by the main application, so no event occurred
	///g_ListOfEvent = 0; // Clear the list of event (because of timeout)
	if (hCOM0)
		fclose (hCOM0); // Close the keyboard
	g_ScanningCancelTaskRunning = FALSE; // Update global variable

	// Send the event to the main task (application that calls the TPass DLL)
	if (SignalEvent (g_wCurrentCancelTask, (tEvent)E_USER_EVENT) != cOK)
		GTL_Traces_DiagnosticText ("Scanning task: Error when setting the event\n");

	ttestall (0,0); // Wait to be killed
	return TRUE;
}



//! \brief Launch the scanning task.
//! \return	OK if task correctly launch, KO else.

int ClessSample_Unattended_LaunchCancelTask (void)
{
	// Init global variables
	__ClessSample_Unattended_InitCancelVariables();

	// Get the main task id
	g_wCurrentCancelTask = CurrentTask();

	// Launch the scanning task
	g_tsScanningCancel_task_handle = fork (&__ClessSample_Unatteded_StartCancelTask, NULL, -1);

	// The task cannot be created
	if (g_tsScanningCancel_task_handle == NULL)
		return KO;
	
	g_ScanningCancelTask = GiveNoTask (g_tsScanningCancel_task_handle);

	// Waiting task start before to call do_transaction
	ttestall (USER_EVENT_START, 2); // Wait scan task start

	return OK;
}



//! \brief Kill the cancel task.

void ClessSample_Unattended_KillCancelTask (void)
{
	if (g_tsScanningCancel_task_handle != NULL) // If the task is lunched
	{
		g_bScanningCancel_task_to_be_killed = TRUE; // To Stop the task (if not already waiting to be killed because of an event)

		// Send an event to make the task ready to be killed
		if (SignalEvent (g_ScanningCancelTask, (tEvent)E_USER_EVENT) != cOK)
			GTL_Traces_DiagnosticText ("Main task: Error when setting the event\n");

		while (g_ScanningCancelTaskRunning == TRUE) // While the task has not terminated processing
		{
			// Waits a little
			ttestall (USER_EVENT,1);
		}

		// The task is ready to be killed, kill it
		kill(g_tsScanningCancel_task_handle, "-*");
		g_tsScanningCancel_task_handle = NULL;
	}
}



//! \brief Initialise scanning global variables

static void __ClessSample_Unattended_InitCancelVariables (void)
{
	g_wCurrentCancelTask = 0xFF; // Init the custom application task number
	g_ScanningCancelTaskRunning = FALSE; //Task is not running
	g_ScanningCancelTask = CurrentTask(); // Init the scanning task number
	g_tsScanningCancel_task_handle = NULL; // init the scanning task handle
	g_bScanningCancel_task_to_be_killed = FALSE; // Task has not to be killed
}
