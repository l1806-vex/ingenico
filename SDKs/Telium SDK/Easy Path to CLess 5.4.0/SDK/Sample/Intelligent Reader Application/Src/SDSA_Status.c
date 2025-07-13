/**
 * \file	SDSA_Status.h
 * \brief	SDSA status management functions.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2010 Ingenico, rue claude Chappe,\n
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

#include "SDSA_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define SEMAPHORE_TIMEOUT						500						//!< State semaphore timeout
#define SEMAPHORE_DEFAULT_VALUE					0xFFFF					//!< State semaphore default value

#define SEMAPHORE_ALLOCATION_ERROR				0xFF					//! System semaphore allocation error


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

static int gs_nCurrentState;										//!< Current state

static word g_wSemaphore_state = SEMAPHORE_DEFAULT_VALUE;			//!< Semaphore for state management.

static word g_wGetStatusTask; // Task that indicates the caller when the transaction status has changed.


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Initialise the state manager.

void SDSA_State_Initialisation (void)
{
	g_wSemaphore_state = SEMAPHORE_DEFAULT_VALUE;

	// Get a semaphore from the system
	g_wSemaphore_state = GetSemaphoreUser ();

	if (g_wSemaphore_state == SEMAPHORE_ALLOCATION_ERROR)
	{
		// Unable to allocate a semaphore
		GTL_Traces_TraceDebug ("SDSA_State_Initialisation: Unable to allocate a semaphore");
	}
	else
	{
		// Init the state semaphore (as a MUTEX)
		if (InitSemaphore (g_wSemaphore_state, 1) != cOK)
			GTL_Traces_TraceDebug ("SDSA_State_Initialisation: Unable to initialize semaphore g_wSemaphore_state");
		else
			V(g_wSemaphore_state); // Free the semaphore
	}
}



//! \brief Get the current state.
//!	\return The reader state.

int SDSA_State_GetCurrentState (void)
{
	int nTempState;

	// Take the semaphore
	P(g_wSemaphore_state, SEMAPHORE_TIMEOUT);

	// Copy the value
	nTempState = gs_nCurrentState;

	// Release the semaphore
	V(g_wSemaphore_state);

	return (nTempState);
}



//! \brief Set the current state.
//! \param[in] nState State to be set.

void SDSA_State_SetCurrentState (const int nState)
{
	// Take the semaphore
	P(g_wSemaphore_state, SEMAPHORE_TIMEOUT);

	// Set the value
	gs_nCurrentState = nState;

	// Release the semaphore
	V(g_wSemaphore_state);

	// Send event to indicate that the transaction status has changed
	if (SignalEvent (g_wGetStatusTask, (tEvent)E_USER_EVENT_STATUS) != cOK)
		GTL_Traces_TraceDebug ("SDSA_State_SetCurrentState: STATUS EVENT error");
	else
		GTL_Traces_TraceDebug ("SDSA_State_SetCurrentState: STATUS EVENT sent");
}



//! \brief Get the status of the transaction.
//! \param[in] hInputTlvTree Contains the current status and the status on which the caller wish to be notified.
//! \param[out] pOutputTlvTree Contains the status application current status.
//! \return
//!	- \ref SDI_STATUS_OK if correctly performed.
//!	- \ref SDI_STATUS_MISSING_DATA if a mandatory input data is missing.
//!	- \ref SDI_STATUS_CANCELLED if the process has been cancelled.

int SDSA_Status_GetStatus (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
{
	TLV_TREE_NODE hCurrentNode;
	int nEvent;
	unsigned long ulCurrentStatus, ulNewStatus;
	unsigned long ulStatusToNotify;
	unsigned char ucBuffer[4];
	int bSendNotification = FALSE;

	g_wGetStatusTask = CurrentTask();

	// Get the status on which the caller wish to be notified
	hCurrentNode = TlvTree_Find(hInputTlvTree, TAG_SDSA_STATUS_TO_NOTIFY, 0);
	if (hCurrentNode != NULL)
		GTL_Convert_BinNumberToUl(TlvTree_GetData(hCurrentNode), &ulStatusToNotify, TlvTree_GetLength(hCurrentNode));
	else
	{
		GTL_Traces_TraceDebug ("SDSA_Status_GetStatus missing TAG_SDSA_STATUS_TO_NOTIFY tag");
		return (SDI_STATUS_MISSING_DATA);
	}
	// Get the current transaction status (given by the caller)
	hCurrentNode = TlvTree_Find(hInputTlvTree, TAG_SDSA_CURRENT_TXN_STATUS, 0);
	if (hCurrentNode != NULL)
		GTL_Convert_BinNumberToUl(TlvTree_GetData(hCurrentNode), &ulCurrentStatus, TlvTree_GetLength(hCurrentNode));
	else
	{
		GTL_Traces_TraceDebug ("SDSA_Status_GetStatus missing TAG_SDSA_CURRENT_TXN_STATUS tag");
		return (SDI_STATUS_MISSING_DATA);
	}

	// Get the status of the transaction
	ulNewStatus = SDSA_State_GetCurrentState();
	// Compare transaction status to the status known by the caller
	if(ulNewStatus != ulCurrentStatus)
	{
		// Status are different, send notification immediately
		GTL_Traces_TraceDebug ("SDSA_Status_GetStatus, status different: current %lx new %lx", ulCurrentStatus, ulNewStatus);
		bSendNotification = TRUE;
		goto End;
	}

	do
	{
		nEvent = ttestall (USER_EVENT_STATUS | USER_EVENT_CANCEL_STATUS, 0);
		if (nEvent & USER_EVENT_STATUS)
		{
			GTL_Traces_TraceDebug ("SDSA_Status_GetStatus, USER_EVENT_STATUS received");

			// Get the new transaction status
			ulNewStatus = SDSA_State_GetCurrentState();
			
			// Check if the caller asked be notified.
			if(ulStatusToNotify & ulNewStatus)
			{
				GTL_Traces_TraceDebug ("Send notification");
				bSendNotification = TRUE;
			}
			else
				GTL_Traces_TraceDebug ("Do not Send notification");
		}
	}while((!bSendNotification) && (nEvent != USER_EVENT_CANCEL_STATUS));

	if(nEvent & USER_EVENT_CANCEL_STATUS)
	{
		GTL_Traces_TraceDebug ("Cancel get status received");
		return (SDI_STATUS_CANCELLED);
	}

End:
	if(bSendNotification)
	{
		// Add the new transaction status
		GTL_Convert_UlToBinNumber(ulNewStatus, ucBuffer, sizeof(ucBuffer));
		TlvTree_AddChild (hOutputTlvTree, TAG_SDSA_CURRENT_TXN_STATUS, ucBuffer, sizeof(ucBuffer));
	}

	return (SDI_STATUS_OK);
}

//! \brief Stop the status checking in progress.
//! \return
//!	- \ref SDI_STATUS_OK if correctly performed.

int SDSA_Status_GetStatusCancel (void)
{
	// Send an event to stop the task that scan the transaction status
	if (SignalEvent (g_wGetStatusTask, (tEvent)E_USER_EVENT_CANCEL_STATUS) != cOK)
		GTL_Traces_TraceDebug ("SDSA_Status_GetStatusCancel: CANCEL_STATUS EVENT error");
	else
		GTL_Traces_TraceDebug ("SDSA_Status_GetStatusCancel: CANCEL_STATUS EVENT sent");

	return (SDI_STATUS_OK);
}
