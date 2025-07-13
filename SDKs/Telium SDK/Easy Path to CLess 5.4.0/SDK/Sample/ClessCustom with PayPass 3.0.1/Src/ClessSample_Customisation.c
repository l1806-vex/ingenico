/**
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
 */


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

// Macro to add customisation steps
#define ADD_CUST_STEP(step,buffer)	buffer[(step-1)/8] += (1<<((step-1)%8))

/////////////////////////////////////////////////////////////////
//// Static function definition /////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

static unsigned char gs_ucSchemeToUse = CLESS_SAMPLE_CUST_UNKNOWN;
static unsigned char gs_bDoubleTapInProgress = FALSE;


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Set the used payment scheme.
//! \param[in] ucUsedScheme Indicates the used scheme.

void ClessSample_Customisation_SetUsedPaymentScheme (const unsigned char ucUsedScheme)
{
	gs_ucSchemeToUse = ucUsedScheme;
}



//! \brief Set the used payment scheme.
//! \return The used scheme.
//!		\a CLESS_SAMPLE_CUST_UNKNOWN Scheme is not yet known.
//!		\a CLESS_SAMPLE_CUST_PAYPASS Scheme is PayPass.
//!		\a CLESS_SAMPLE_CUST_PAYWAVE Scheme is payWave.
//!		\a CLESS_SAMPLE_CUST_VISAWAVE Scheme is VisaWave.
//!		\a CLESS_SAMPLE_CUST_EXPRESSPAY Scheme is ExpressPay.
//!		\a CLESS_SAMPLE_CUST_DISCOVER Scheme is Discover.

unsigned char ClessSample_Customisation_GetUsedPaymentScheme (void)
{
	return (gs_ucSchemeToUse);
}



//! \brief Perform the kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int ClessSample_Customisation_Process (T_SHARED_DATA_STRUCT * pSharedData)
{
	int cr;
	int nResult = KERNEL_STATUS_CONTINUE;
	int nPosition;
	unsigned long ulReadLength;
	unsigned char * pReadValue = NULL;
	unsigned char ucCustomStep;
    
	// Dump provided parameters
	///ClessSample_DumpData_DumpSharedBuffer(pSharedData, 0);
	
	// Get the step to be customised
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_KERNEL_CUSTOM_STEP, &ulReadLength, (const unsigned char **)&pReadValue);
	
	if (cr == STATUS_SHARED_EXCHANGE_OK) // If tag found
	{
		ucCustomStep = pReadValue[0];
        
    	switch (ClessSample_Customisation_GetUsedPaymentScheme())
    	{
    	case (CLESS_SAMPLE_CUST_PAYPASS):
    		nResult = ClessSample_PayPass_CustomiseStep (pSharedData, ucCustomStep);
    		break;
    	default:
    		break;
    	}
	}
    else
    {
		GTL_Traces_DiagnosticText ("ClessSample_Customisation_Process : Custom step tag not found");
    }
	
	return (nResult);
}



//! \brief Perform the kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int ClessSample_Customisation_Data_Exchange (T_SHARED_DATA_STRUCT * pSharedData)
{
	int nResult = KERNEL_STATUS_CONTINUE;
    
	if (ClessSample_Customisation_GetUsedPaymentScheme() == CLESS_SAMPLE_CUST_PAYPASS)
	{
		if (pSharedData != NULL)
		{
			// For Type Approval testing: Check the DEK Signal with the loaded MCW XML file
			if (!ClessSample_DataExchange_GetDETData (pSharedData))
			{
				// An error occurred when retreiving the DET Signal data in the parameters
				GTL_Traces_TraceDebug ("ClessSample_PayPass_CustomiseStep : ClessSample_Parameters_GetDETData not present");
			}
		}

		nResult = KERNEL_STATUS_CONTINUE;
	}
    else
    {
		GTL_Traces_DiagnosticText ("ClessSample_DE_Process : Other scheme that does not support Data Exchange");
    }
	
	return (nResult);
}



//! \brief Function called for application selection processing customisation.
//! \param[in] pDataStruct Shared exchange structure provided with customisation information.
//! \return
//! 	- CLESS_CUST_DEFAULT to use the default processing. 
//! 	- CLESS_CUST_RETRY_WITH_CLESS if the transaction shall be restarted.
//! 	- CLESS_CUST_RETRY_WITHOUT_CLESS if transaction shall be restarted without cless.
//! 	- CLESS_CUST_STOP if the transaction shall be stopped.
//! 	- CLESS_CUST_NEXT_METHOD if next application selection method shall be used (if present). 
//! 	- CLESS_CUST_CONTINUE_METHOD if next application selection criteria shall be used. 

int ClessSample_Customisation_CustAsProc (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int nResult = CLESS_CUST_DEFAULT;
	int nGtlResult;
    int nPosition;
	unsigned long LengthTag;
	unsigned char * pReadValue = NULL;
	unsigned short usCustomStep;
	unsigned char ucStepsToCustomise[] = {0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	
	///ClessSample_DumpData_DumpSharedBufferWithTitle (pDataStruct, "AS CUST PROC");
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
    
	nGtlResult = GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_GENERIC_CUST_STEP_ID, &LengthTag, (const unsigned char **)&pReadValue);
	
	usCustomStep = pReadValue[0];
	
	if (nGtlResult == STATUS_SHARED_EXCHANGE_OK) // If tag found
	{
        switch (usCustomStep) // Steps to customise
        {
		case (CLESS_CUST_AS_PROC_REGISTRATION_STEP_ID):
			GTL_SharedExchange_ClearEx (pDataStruct, FALSE);
			GTL_SharedExchange_AddTag (pDataStruct, TAG_GENERIC_CUST_STEPS_TO_CUSTOMISE, 8, ucStepsToCustomise);
			nResult = CLESS_CUST_CONTINUE;
			break;

		case (CLESS_CUST_AS_PROC_STEP_PPSE_STEP_ID): // Step called when PPSE method is completed
			break;
		
		case (CLESS_CUST_AS_PROC_STEP_END_STEP_ID): // Step called when application selection is completed and no method has matched (card is not supported)
			ClessSample_Customisation_SetDoubleTapInProgress(FALSE);
			break;

		default: // Use default behaviour on other steps
			break;
        }
    }
    else
    {
    	GTL_Traces_TraceDebug ("ClessSample_Customisation_CustAsProc : Custom step tag not found\n");
    }
	
	return (nResult);
}



//! \brief Set the global data indicating double tap is in progress.
//! \param[in] bDoubleTapInProgress \ref TRUE if double tap is in progress, \ref FALSE else.

void ClessSample_Customisation_SetDoubleTapInProgress (const unsigned char bDoubleTapInProgress)
{
	gs_bDoubleTapInProgress = bDoubleTapInProgress;
}



//! \brief Indicates if double tap is in progress or not.
//! \return
//!	- \ref TRUE if double tap is in progress.
//!	- \ref FALSE else.

unsigned char ClessSample_Customisation_GetDoubleTapInProgress (void)
{
	return (gs_bDoubleTapInProgress);
}



//! \brief This function is called to customise the GUI during the DLL processing.
//! \brief Customisation is different according to the GUI mode used (specific GUI for Visa Asia)
//! \brief Customisation is different according to the selection mode (implicit or explicit)
//! \param[in] pDataStruct Shared buffer containing data necessary to customise the step.
//! \return
//!	- \ref CLESS_CUST_DEFAULT if default DLL GUI shall be executed.
//!	- \ref CLESS_CUST_CONTINUE if application made customisation and default DLL GUI shall not be executed.

int ClessSample_Customisation_Generic_SelectionGui (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int nResult = CLESS_CUST_DEFAULT;
	int nGtlResult;
    int nPosition;
	unsigned long LengthTag;
	unsigned char * pReadValue = NULL;
	unsigned short usCustomStep;
	// Steps to customise are identified by a sequence of bits
	// Example 0x28 : the steps to customised are CLESS_CUST_GUI_PRESENT_CARD_AMOUNT_STEP_ID (bit 4)
	// and CLESS_CUST_GUI_RETRY_AMOUNT_STEP_ID (bit 6)
	///unsigned char ucStepsToCustomise[] = {0x28,0x58,0x00,0x00,0x00,0x00,0x00,0x00};
	unsigned char ucStepsToCustomise[] = {0x78,0x58,0x04,0x00,0x00,0x00,0x00,0x00};
	const T_PAYMENT_DATA_STRUCT * pTransactionData;
		


	// Init position
	nPosition = SHARED_EXCHANGE_POSITION_NULL;

	// Get the step identiifer to be customised
	nGtlResult = GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_GENERIC_CUST_STEP_ID, &LengthTag, (const unsigned char **)&pReadValue);
	
	pTransactionData = ClessSample_Fill_GetTransactionDataStructure();

	if (nGtlResult == STATUS_SHARED_EXCHANGE_OK) // If tag found
	{
		// Save the step identifier
		usCustomStep = pReadValue[0];

		// Steps to customise
		switch (usCustomStep)
		{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case (CLESS_CUST_GUI_REGISTRATION_STEP_ID):
			// Clear the output structure
			GTL_SharedExchange_ClearEx (pDataStruct, FALSE);

			// Indicate the steps to be customised
			GTL_SharedExchange_AddTag (pDataStruct, TAG_GENERIC_CUST_STEPS_TO_CUSTOMISE, 8, ucStepsToCustomise);

			nResult = CLESS_CUST_CONTINUE;
			break;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case (CLESS_CUST_GUI_PRESENT_CARD_AMOUNT_STEP_ID):
		case (CLESS_CUST_GUI_PRESENT_CARD_NO_AMOUNT_STEP_ID):
			// Note the folowing specific processing is only there to display "see phone for instructions" when the card collision is detected, to avoid displaying "present card" again after collision is solved
			// Check if a double tap is in progress ("see phone for instructions" is displayed)
			if (ClessSample_Customisation_GetDoubleTapInProgress())
			{
				ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_PHONE_INSTRUCTIONS, -1, -1);

				// Turn on the first LED only
				HelperCardWait();
				nResult = CLESS_CUST_CONTINUE;
			}
			else
			{
				// Use the default behavior (standard message "CLIENT CARD" with the cless logo if applicable)
				if (ClessSample_Common_GetTransactionMode() == CLESS_SAMPLE_TRANSACTION_MODE_EXPLICIT)
					ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_PRESENT_CARD, -1, -1);
				nResult = CLESS_CUST_DEFAULT;
			}
			break;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case (CLESS_CUST_GUI_DOUBLE_TAP_STEP_ID):

			if (ClessSample_Common_GetTransactionMode() != CLESS_SAMPLE_TRANSACTION_MODE_EXPLICIT)
			{
				// Display the message
				ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_PHONE_INSTRUCTIONS, -1, -1);
	
				// Turn on the fist LED only
				HelperCardWait();
	
				nResult = CLESS_CUST_CONTINUE;
			}
			else
			{
				nResult = CLESS_CUST_DEFAULT;
			}
			break;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case (CLESS_CUST_GUI_RETRY_AMOUNT_STEP_ID):
		case (CLESS_CUST_GUI_RETRY_NO_AMOUNT_STEP_ID):

			// Turn on the fist LED only
			HelperCardWait();

			// Customized to avoid that the TPass DLL performs a beep
			nResult = CLESS_CUST_CONTINUE;
			break;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case (CLESS_CUST_GUI_COLLISION_STEP_ID):
			// Display the message
			if (ClessSample_Common_GetTransactionMode() == CLESS_SAMPLE_TRANSACTION_MODE_EXPLICIT)
			{
				ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_COLLISION, -1, -1);

				nResult = CLESS_CUST_CONTINUE;
			}
			
			break;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case (CLESS_CUST_GUI_CARD_NOT_SUPPORTED_STEP_ID):
			if (ClessSample_Common_GetTransactionMode() == CLESS_SAMPLE_TRANSACTION_MODE_EXPLICIT)
			{
				ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_ERROR, -1, -1);
				HelperErrorSequence(WITHBEEP);

				nResult = CLESS_CUST_CONTINUE;
			}
			break;
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case (CLESS_CUST_GUI_USE_CONTACT_STEP_ID):
			if (ClessSample_Common_GetTransactionMode() == CLESS_SAMPLE_TRANSACTION_MODE_EXPLICIT)
			{
				ClessSample_GuiState_DisplayScreen (CLESS_SAMPLE_SCREEN_USE_CONTACT, -1, -1);
				HelperErrorSequence(WITHBEEP);

				nResult = CLESS_CUST_CONTINUE;
			}
			break;
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		default:
			GTL_Traces_TraceDebug ("ClessSample_Customisation_Generic_SelectionGui : Unknown step (id = %02x)\n", usCustomStep);
			nResult = CLESS_CUST_DEFAULT;
			break;
        }
    }
    else
    {
		nResult = CLESS_CUST_DEFAULT;
		GTL_Traces_TraceDebug ("ClessSample_Customisation_Generic_SelectionGui : Custom step tag not found\n");
    }
    
	return (nResult);
}



//! \brief Analyse the application selection result and set the transaction result.
//! \param[in] nApplicationSelectionResult Application selection result.
//! \return The transaction result.

int ClessSample_Customisation_AnalyseApplicationSelectionResult (int nApplicationSelectionResult)
{
	int nResult = CLESS_CR_MANAGER_END;

	switch (nApplicationSelectionResult) // Steps to customise
    {
    case (CLESS_STATUS_COMMUNICATION_ERROR):
		nResult = CLESS_CR_MANAGER_RESTART;
    	break;

	case (CLESS_STATUS_NO_MATCHING_APDU):
		nResult = CLESS_CR_MANAGER_END;
		ClessSample_Customisation_SetDoubleTapInProgress(FALSE);
		break;

	case (CLESS_STATUS_EP_CLESS_SELECTION_NOT_ALLOWED):
		break;

	default:
    	GTL_Traces_TraceDebug("ClessSample_Customisation_AnalyseApplicationSelectionResult : Unknown application selection result (nApplicationSelectionResult=%02x)", nApplicationSelectionResult);
		nResult = CLESS_CR_MANAGER_END;
		break;
    }

	 return (nResult);
}
