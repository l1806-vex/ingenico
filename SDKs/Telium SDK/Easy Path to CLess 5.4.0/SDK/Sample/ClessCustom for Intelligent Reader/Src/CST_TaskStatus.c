/**
 * \file	CST_TaskStatus.c
 * \brief 	Management of the task that will retrieve the transaction status.
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
//// Global data definition /////////////////////////////////////


word g_StatusTask;											// To store the Status task ID.
t_topstack * g_tsStatus_task_handle;						// Handle of the status task.

static word g_wCurrentTask;
static int g_StatusTaskRunning = FALSE;						// Indicates if the status task is still running or if it is waiting to be killed.



/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static word __CST_Status_StartTask (void);
static void __CST_TaskStatus_InitVariables (void);
static int __CST_TaskStatus_AnalyseOutput(TLV_TREE_NODE hTlvTreeStatus, unsigned long *pNewStatus);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Retrieve the transaction status and perform action according to the status
//! \param[in] hTlvTreeStatus TLV Tree containing the new transaction status
//! \param[out] pNewStatus to get the new transaction status
//! \return TRUE if OK, FALSE else
 
static int __CST_TaskStatus_AnalyseOutput(TLV_TREE_NODE hTlvTreeStatus, unsigned long *pNewStatus)
{
	TLV_TREE_NODE hCurrentNode;
	unsigned long ulTransactionStatus;
	MSGinfos tMsg;
	

	// Get the current status of the transaction
	hCurrentNode = TlvTree_Find(hTlvTreeStatus, TAG_SDSA_CURRENT_TXN_STATUS, 0);
	if (hCurrentNode != NULL)
		GTL_Convert_BinNumberToUl(TlvTree_GetData(hCurrentNode), &ulTransactionStatus, TlvTree_GetLength(hCurrentNode));
	else
	{
		GTL_Traces_TraceDebug ("__CST_TaskStatus_AnalyseOutput missing TAG_SDSA_CURRENT_TXN_STATUS tag");
		return (FALSE);
	}
	
	GTL_Traces_TraceDebug ("__CST_TaskStatus_AnalyseOutput: ulTransactionStatus, %lx",ulTransactionStatus);
	
	switch (ulTransactionStatus)
	{
	case SDSA_PAYMENT_STATUS_NOT_STARTED :
		// TODO
		break;
	case SDSA_PAYMENT_STATUS_DETECT_CARD :
		// Display present card message
		GetMessageInfos(STD_MESS_PRESENT_CARD, &tMsg);
		Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg);
		// Display the amount with the same font
		tMsg.message = CST_Tests_GiveAmountMessage();
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_2, &tMsg);
		Helper_RefreshScreen(NOWAIT);
		break;
	case SDSA_PAYMENT_STATUS_IN_PROGRESS :
		// TODO
		break;
	case SDSA_PAYMENT_STATUS_RETRY :
		// Display try again message
		GetMessageInfos(STD_MESS_TRY_AGAIN, &tMsg);
		Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg);
		// Display the amount with the same font
		tMsg.message = CST_Tests_GiveAmountMessage();
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_2, &tMsg);
		Helper_RefreshScreen(NOWAIT);
		break;
	case SDSA_PAYMENT_STATUS_COLLISION :
		Helper_DisplayMessage(STD_MESS_COLLISION_LINE_1, ERASE, HELPERS_MERCHANT_LINE_2);
		Helper_DisplayMessage(STD_MESS_COLLISION_LINE_2, NO_ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_RefreshScreen(NOWAIT);
		break;
	case SDSA_PAYMENT_STATUS_DOUBLE_TAP :
		Helper_DisplayMessage(STD_MESS_PHONE_INSTRUCTIONS_L1, ERASE, HELPERS_MERCHANT_LINE_2);
		Helper_DisplayMessage(STD_MESS_PHONE_INSTRUCTIONS_L2, NO_ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_RefreshScreen(NOWAIT);
		break;
	case SDSA_PAYMENT_STATUS_CARD_READ :
		Helper_DisplayMessage(STD_MESS_REMOVE_CARD, ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_RefreshScreen(NOWAIT);
		// Wait during the beep
		if(!CST_VisaWave_IsVisaAsiaGuiMode())
			ttestall(0,50);
		else
			ttestall(0,200);
		// Wait 750ms to see LEDS.
		ttestall(0,75);
		break;
	default:
		GTL_Traces_TraceDebug ("__CST_TaskStatus_AnalyseOutput: unknown transaction status : %lx", ulTransactionStatus);
		return (FALSE);
		break;
	}

	// Return the new transaction status
	*pNewStatus = ulTransactionStatus;

	return(TRUE);
}


//! \brief This task asks to the intelligent reader to be notified when the reader status has changed.
//! The task will then update the display accordingly (retry, collision...).

static word __CST_Status_StartTask (void)
{
	TLV_TREE_NODE hTlvTreeIn, hTlvTreeOut;
	unsigned long ulStatusToNotify, ulCurrentStatus;
	unsigned char ucStatusToNotify[4], ucCurrentStatus[4];
	unsigned char bStatus_task_to_be_killed = FALSE;	// variable used to stop the status task.
	int nEvent;
	int nResult = SDI_STATUS_KO;

	g_StatusTaskRunning = TRUE;
	g_StatusTask = CurrentTask();

	// Init the current transaction status known by the terminal
	ulCurrentStatus = SDSA_PAYMENT_STATUS_NOT_STARTED;		
	
	// Set the status on which the caller wish to be notified
	ulStatusToNotify = SDSA_PAYMENT_STATUS_DETECT_CARD | SDSA_PAYMENT_STATUS_RETRY | SDSA_PAYMENT_STATUS_COLLISION | SDSA_PAYMENT_STATUS_CARD_READ | SDSA_PAYMENT_STATUS_DOUBLE_TAP;		
	GTL_Convert_UlToBinNumber (ulStatusToNotify, ucStatusToNotify, sizeof(ucStatusToNotify));

	do{

		hTlvTreeIn = TlvTree_New(0);

		if (hTlvTreeIn != NULL)
		{
			TlvTree_AddChild(hTlvTreeIn, TAG_SDSA_STATUS_TO_NOTIFY, ucStatusToNotify, sizeof(ucStatusToNotify));

			GTL_Convert_UlToBinNumber (ulCurrentStatus, ucCurrentStatus, sizeof(ucCurrentStatus));
			TlvTree_AddChild(hTlvTreeIn, TAG_SDSA_CURRENT_TXN_STATUS, ucCurrentStatus, sizeof(ucCurrentStatus));

			// Ask the intelligent reader for notification
			nResult = SDI_Payment_GetStatusUpdateStart(nSDSAAppliId, hTlvTreeIn, E_USER_EVENT);
			if(nResult == SDI_STATUS_OK)
			{
				nResult = SDI_STATUS_ANSWER_NOT_YET_RECEIVED;
				do
				{
					// Wait for notification or for cancel
					nEvent = ttestall(USER_EVENT | USER_EVENT_STATUS, 1);
					if(nEvent & USER_EVENT)
					{
						// A notification of a status change has been received
						nResult = SDI_Payment_GetStatusUpdate(&hTlvTreeOut);

						if(nResult == SDI_STATUS_OK)
						{	
							// Analyse the output that containing the new transaction status
							if(!__CST_TaskStatus_AnalyseOutput(hTlvTreeOut, &ulCurrentStatus))
								nResult = SDI_STATUS_KO;
						}
					}
					if((nEvent & USER_EVENT_STATUS))
					{
						// Cancel the get status processing and make the task ready to be killed
						SDI_Payment_GetStatusUpdateStop(nSDSAAppliId);
						bStatus_task_to_be_killed = TRUE;
					}
				}while(nResult == SDI_STATUS_ANSWER_NOT_YET_RECEIVED);
			}

			// Release the input/output TLV Tree
			TlvTree_ReleaseEx(&hTlvTreeIn);
			TlvTree_ReleaseEx(&hTlvTreeOut);
		}
		else
			nResult = SDI_STATUS_KO;
	}while((!bStatus_task_to_be_killed) && (nResult == SDI_STATUS_OK));

	g_StatusTaskRunning = FALSE; // Update global variable

	// Send the event to the main task
	if (SignalEvent (g_wCurrentTask, (tEvent)E_USER_EVENT_STATUS) != cOK)
		GTL_Traces_TraceDebug ("GetStatus task: Error when setting the event\n");	

	ttestall (0,0); // Wait to be killed

	return (TRUE);
}



//! \brief Launch the task that manages the transaction status.
//! \return OK if task correctly launched, KO else.

int CST_TaskStatus_LaunchTask (void)
{
	// Init global variables
	__CST_TaskStatus_InitVariables();

	// Get the main task id
	g_wCurrentTask = CurrentTask();

	// Launch the status task
	g_tsStatus_task_handle = fork (&__CST_Status_StartTask, NULL, 0);

	// The task cannot be created
	if (g_tsStatus_task_handle == NULL)
		return KO;

	return OK;
}



//! \brief Kill the status task.

void CST_TaskStatus_KillTask (void)
{
	if (g_tsStatus_task_handle != NULL) // If the task is launched
	{
		// Send an event to the status task to make the task ready to be killed
		if (SignalEvent (g_StatusTask, (tEvent)E_USER_EVENT_STATUS) != cOK)
			GTL_Traces_TraceDebug ("CST_TaskStatus_KillTask: Error when setting the event\n");	
		
		while (g_StatusTaskRunning == TRUE) // While the task has not terminated processing
		{
			// Waits a little
			ttestall (USER_EVENT_STATUS,1);
		}

		// The task is ready to be killed, kill it
		kill(g_tsStatus_task_handle, "-*");
		GTL_Traces_TraceDebug ("CST_TaskStatus_KillTask, task killed\n");
		g_tsStatus_task_handle = NULL;
	}
}



//! \brief Initialise global variables

static void __CST_TaskStatus_InitVariables (void)
{
	g_wCurrentTask = 0xFF;					// Init the custom application task number
	g_StatusTask = 0xFF;					// Init the task number
	g_tsStatus_task_handle = NULL;			// Init the task handle
	g_StatusTaskRunning = FALSE;			// Task is not running
}


