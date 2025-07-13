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
	////ClessSample_DumpData_DumpSharedBuffer(pSharedData, 0);
	
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
		case (CLESS_SAMPLE_CUST_PAYWAVE):
			nResult = ClessSample_payWave_CustomiseStep (pSharedData, ucCustomStep);
			break;
		case (CLESS_SAMPLE_CUST_VISAWAVE):
			nResult = ClessSample_VisaWave_CustomiseStep (pSharedData, ucCustomStep);
			break;
		case (CLESS_SAMPLE_CUST_EXPRESSPAY):
			nResult = ClessSample_ExpressPay_CustomiseStep (pSharedData, ucCustomStep);
			break;
		case (CLESS_SAMPLE_CUST_DISCOVER):
			nResult = ClessSample_Discover_CustomiseStep (pSharedData, ucCustomStep);
			break;
		case (CLESS_SAMPLE_CUST_INTERAC):
			nResult = ClessSample_Interac_CustomiseStep (pSharedData, ucCustomStep);
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
			if (ClessSample_Fill_IsThereAmexAidOnly())
			{
				// Get the EP status code
				nGtlResult = GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_GENERIC_APPLICATION_SELECTION_RESULT, &LengthTag, (const unsigned char **)&pReadValue);
				if (nGtlResult == STATUS_SHARED_EXCHANGE_OK) // If tag found
				{
					if((pReadValue[0] == 0x0A) && (pReadValue[1] == 0x26))
					{	// CLESS_STATUS_EP_CLESS_SELECTION_NOT_ALLOWED
						GTL_Traces_TraceDebug ("CLESS_STATUS_EP_CLESS_SELECTION_NOT_ALLOWED\n");
						nResult = CLESS_CUST_RETRY_WITHOUT_CLESS;
						break;
					}
				}
			}
			else if (ClessSample_Fill_IsThereInteracAidOnly())
			{	
				// Get the EP status code
				nGtlResult = GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_GENERIC_APPLICATION_SELECTION_RESULT, &LengthTag, (const unsigned char **)&pReadValue);
				if (nGtlResult == STATUS_SHARED_EXCHANGE_OK) // If tag found
				{
					// Interac (Section 4.9) requires abort the transaction if there 
					// is an error - the service will exit with a suitable error 
					// Do not perform AID List selection method
					if((pReadValue[0] == 0x0A) && (pReadValue[1] == 0x09))
					{	// CLESS_STATUS_COMMUNICATION_ERROR 
						nResult = CLESS_CUST_STOP;
						GTL_Traces_DiagnosticText ("ClessSample_Customisation_CustAsProc : EP Comms Error 0x%02x%02x)",pReadValue[0], pReadValue[1]);
						break;
					}
					else if((pReadValue[0] == 0x0A) && (pReadValue[1] == 0x0B))
					{	// CLESS_STATUS_MISSING_ICC_DATA
						nResult = CLESS_CUST_STOP;
						GTL_Traces_DiagnosticText ("ClessSample_Customisation_CustAsProc : EP Missing ICC Data 0x%02x%02x)",pReadValue[0], pReadValue[1]);
						break;
					}
					else if((pReadValue[0] == 0x0A) && (pReadValue[1] == 0x0D))
					{	// CLESS_STATUS_ICC_FORMAT_ERROR
						nResult = CLESS_CUST_STOP;
						GTL_Traces_DiagnosticText ("ClessSample_Customisation_CustAsProc : EP ICC Data format Error 0x%02x%02x)",pReadValue[0], pReadValue[1]);
						break;
					}
					else if((pReadValue[0] == 0x0A) && (pReadValue[1] == 0x04))
					{	// CLESS_STATUS_CARD_BLOCKED
						nResult = CLESS_CUST_STOP;
						GTL_Traces_DiagnosticText ("ClessSample_Customisation_CustAsProc : EP Card Blocked Error 0x%02x%02x)",pReadValue[0], pReadValue[1]);
						break;
					}
					else
					{
						GTL_Traces_DiagnosticText ("ClessSample_Customisation_CustAsProc : EP Response 0x%02x%02x)",pReadValue[0], pReadValue[1]);
					}
				}
			}

			nResult = CLESS_CUST_DEFAULT;
			break;
		
		case (CLESS_CUST_AS_PROC_STEP_END_STEP_ID): // Step called when application selection is completed and no method has matched (card is not supported)
			ClessSample_Customisation_SetDoubleTapInProgress(FALSE);
			nResult = CLESS_CUST_DEFAULT;
			if (ClessSample_Fill_IsThereVisaAid())
			{
				if ((gs_ucSchemeToUse == CLESS_SAMPLE_CUST_PAYWAVE) ||(gs_ucSchemeToUse == CLESS_SAMPLE_CUST_UNKNOWN))
					nResult = CLESS_CUST_RETRY_WITHOUT_CLESS;
			}
			
			break;
			
		default: // Use default behaviour on other steps
			nResult = CLESS_CUST_DEFAULT;
			break;
		}
	}
	else
	{
		GTL_Traces_TraceDebug ("ClessSample_Customisation_CustAsProc : Custom step tag not found\n");
		nResult = CLESS_CUST_DEFAULT;
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
//! \param[in] pDataStruct Shared buffer containing data necessary to customise the step.
//! \return
//!	- \ref CLESS_CUST_DEFAULT if default DLL GUI shall be executed.
//!	- \ref CLESS_CUST_CONTINUE if application made customisation and default DLL GUI shall not be executed.

int ClessSample_Customisation_SelectionGui (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int nResult = CLESS_CUST_DEFAULT;
	int nGtlResult;
	int nPosition;
	unsigned long LengthTag;
	unsigned char * pReadValue = NULL;
	unsigned short usCustomStep;
	unsigned char ucStepsToCustomise[] = {0x20,0x18,0x00,0x00,0x00,0x00,0x00,0x00};
	MSGinfos tDisplayMsg;
	int merchLang, nCardHolderLang;


	nPosition = SHARED_EXCHANGE_POSITION_NULL;

	nGtlResult = GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_GENERIC_CUST_STEP_ID, &LengthTag, (const unsigned char **)&pReadValue);
	
	usCustomStep = pReadValue[0];   // Save the step identifier

	if (nGtlResult == STATUS_SHARED_EXCHANGE_OK) // If tag found
	{
		switch (usCustomStep) // Steps to customise
		{
		case (CLESS_CUST_GUI_REGISTRATION_STEP_ID):
			///GTL_Traces_TraceDebug ("Custom GUI : CLESS_CUST_GUI_REGISTRATION_STEP_ID\n");
			// Clear the output structure
			GTL_SharedExchange_ClearEx (pDataStruct, FALSE);

			// Indicate the steps to be customised
			GTL_SharedExchange_AddTag (pDataStruct, TAG_GENERIC_CUST_STEPS_TO_CUSTOMISE, 8, ucStepsToCustomise);

			nResult = CLESS_CUST_CONTINUE;
			break;
				
		case (CLESS_CUST_GUI_RETRY_AMOUNT_STEP_ID):
			{ 
			unsigned char ucValue = CLESS_CUST_MANAGER_MESS_PRESENT_CARD;
			
			// Get the merchant language
			merchLang = PSQ_Give_Language();
			nCardHolderLang = merchLang;
			
			ClessSample_Term_Read_Message(VISAWAVE_MESS_TRY_AGAIN, nCardHolderLang, &tDisplayMsg);
			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_2, &tDisplayMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);

			Helper_PerformKOSequence();
			
			TPass_LedsOff(TPASS_LED_RED);
			TPass_LedsBlink(TPASS_LED_BLUE, VISA_ASIA_LED_BLINK_ON, VISA_ASIA_LED_BLINK_OFF);

			// Set the next screen to diplay (PRESENT CARD)
			GTL_SharedExchange_ClearEx (pDataStruct, FALSE);
			GTL_SharedExchange_AddTag (pDataStruct, TAG_GENERIC_MANAGER_MESSAGE_TO_DISPLAY, 1, &ucValue);

			// Re-Initialize the timer because card detection restarts
			VisaWave_StartDetectionTimer();

			nResult = CLESS_CUST_CONTINUE;
			//GTL_Traces_TraceDebug ("Custom GUI : CLESS_CUST_GUI_RETRY_AMOUNT_STEP_ID\n");
			break;
			}
			
		case (CLESS_CUST_GUI_COLLISION_STEP_ID):
			merchLang = PSQ_Give_Language();
			nCardHolderLang = merchLang;

			ClessSample_Term_Read_Message(VISAWAVE_MESS_SELECT_ONE_CARD_L1, nCardHolderLang, &tDisplayMsg);
			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_2, &tDisplayMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
			ClessSample_Term_Read_Message(VISAWAVE_MESS_SELECT_ONE_CARD_L2, nCardHolderLang, &tDisplayMsg);
			Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tDisplayMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
			
			Helper_PerformKOSequence();

			// Re-Initialize the timer because card detection restarts
			VisaWave_StartDetectionTimer();
			
			nResult = CLESS_CUST_CONTINUE;
			///GTL_Traces_TraceDebug ("Custom GUI : CLESS_CUST_GUI_COLLISION_STEP_ID\n");
			break;
		
		case (CLESS_CUST_GUI_USE_CONTACT_STEP_ID):
			merchLang = PSQ_Give_Language();
			nCardHolderLang = merchLang;

			ClessSample_Term_Read_Message(VISAWAVE_MESS_INSERT_OR_SWIPE, nCardHolderLang, &tDisplayMsg);
			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_2, &tDisplayMsg, CLESSSAMPLE_ALIGN_CENTER, LEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
			
			Helper_PerformKOSequence();

			nResult = CLESS_CUST_CONTINUE;
			break;
		
		default:
			GTL_Traces_TraceDebug ("Custom GUI : Unknown step (id = %02x)\n", usCustomStep);
			nResult = CLESS_CUST_DEFAULT;
			break;
		}
	}
	else
	{
		nResult = CLESS_CUST_DEFAULT;
		GTL_Traces_TraceDebug ("Custom GUI : step tag not found\n");
	}
	
	return (nResult);
}


//! \brief This function is called to customise the GUI during the DLL processing of Interac transaction.
//! \param[in] pDataStruct Shared buffer containing data necessary to customise the step.
//! \return
//!	- \ref CLESS_CUST_DEFAULT if default DLL GUI shall be executed.
//!	- \ref CLESS_CUST_CONTINUE if application made customisation and default DLL GUI shall not be executed.

int ClessSample_Customisation_Interac_SelectionGui (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int nResult = CLESS_CUST_DEFAULT;
	int nGtlResult;
	int nPosition;
	unsigned long LengthTag;
	unsigned char * pReadValue = NULL;
	unsigned short usCustomStep;
	unsigned char ucStepsToCustomise[8];
	MSGinfos tMsg;
	int merchLang, nCardHolderLang;
	unsigned char ucTransactionType;
	unsigned long ulTransactionAmount;
	MSGinfos tMsgAmount;
	char buffer[40];
	char *pLogoFont;
	int nDeviceType;

	// Init customisation mask buffer
	memset (ucStepsToCustomise, 0, sizeof(ucStepsToCustomise));

	// Add steps to be customised
	ADD_CUST_STEP (CLESS_CUST_GUI_COLLISION_STEP_ID, ucStepsToCustomise); // If you need to customise the "PRESENT 1 CARD" screen.
	ADD_CUST_STEP (CLESS_CUST_GUI_PRESENT_CARD_AMOUNT_STEP_ID, ucStepsToCustomise); // If you need to customise the "PRESENT CARD" screen.
	ADD_CUST_STEP (CLESS_CUST_GUI_CARD_NOT_SUPPORTED_STEP_ID, ucStepsToCustomise); // If you need to customise the "NOT SUPPORTED" screen.
	ADD_CUST_STEP (CLESS_CUST_GUI_USE_CONTACT_STEP_ID, ucStepsToCustomise); // If you need to customise the "INSERT CARD" screen.
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;

	// Find the customisation step
	nGtlResult = GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_GENERIC_CUST_STEP_ID, &LengthTag, (const unsigned char **)&pReadValue);
	usCustomStep = pReadValue[0];

	if (nGtlResult == STATUS_SHARED_EXCHANGE_OK) // If tag found
	{
		switch (usCustomStep) // Steps to customise
		{
		case (CLESS_CUST_GUI_REGISTRATION_STEP_ID):
			GTL_SharedExchange_ClearEx (pDataStruct, FALSE);
			GTL_SharedExchange_AddTag (pDataStruct, TAG_GENERIC_CUST_STEPS_TO_CUSTOMISE, 8, ucStepsToCustomise);
			nResult = CLESS_CUST_CONTINUE;
			break;

		case (CLESS_CUST_GUI_COLLISION_STEP_ID):
			merchLang = PSQ_Give_Language();
			nCardHolderLang = merchLang;

			ClessSample_Term_Read_Message(INTERAC_MESS_SELECT_ONE_CARD_L1, nCardHolderLang, &tMsg);
			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
			ClessSample_Term_Read_Message(INTERAC_MESS_SELECT_ONE_CARD_L2, nCardHolderLang, &tMsg);
			Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
			
			HelperErrorSequence (WITHBEEP);

			// Re-Initialize the timer because card detection restarts
			Interac_StartDetectionTimer();
			
			nResult = CLESS_CUST_CONTINUE;
			//GTL_Traces_TraceDebug ("Custom GUI : CLESS_CUST_GUI_COLLISION_STEP_ID\n");
			break;
			
		case (CLESS_CUST_GUI_PRESENT_CARD_AMOUNT_STEP_ID): // Present card customisation
			merchLang = PSQ_Give_Language();
			nCardHolderLang = merchLang;

			// Turn on the first LED
			TPass_LedsOff(TPASS_LED_2 | TPASS_LED_3 | TPASS_LED_4);
			TPass_LedsOn (TPASS_LED_1);

			// Get the INTERAC_MESS_PRESENT_CARD_L1 message and display it
			ClessSample_Term_Read_Message(INTERAC_MESS_PRESENT_CARD, nCardHolderLang, &tMsg);
			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_1, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);

			// Get the data required to display the Amount and label with the correct transaction type
			ulTransactionAmount = ClessSample_Fill_GiveAmount();
			ucTransactionType = ClessSample_Fill_GiveTransactionType();

			if (ucTransactionType == CLESS_SAMPLE_TRANSACTION_TYPE_REFUND)
				ClessSample_Term_Read_Message(INTERAC_MESS_REFUND, nCardHolderLang, &tMsg);
			else
				ClessSample_Term_Read_Message(INTERAC_MESS_DEBIT, nCardHolderLang, &tMsg);

			// prepare the message with transaction type and amount
			sprintf(buffer, "%s$%lu.%02lu\n", tMsg.message, ulTransactionAmount/100, ulTransactionAmount%100);

			// Fill the Message structure with the formatted message and display it
			tMsgAmount.coding = tMsg.coding;
			tMsgAmount.file = tMsg.file;
			tMsgAmount.message = buffer;

			// Display the buffer message
			Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_2, &tMsgAmount, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);

			// Display the Contact Less logo
			nDeviceType = TPass_GetDeviceType();
			if((nDeviceType != TPASS_CLESS_TYPE_TELIUM_PASS) && (nDeviceType != TPASS_CLESS_TYPE_VENDING_PASS))
			{
				pLogoFont = LoadFont("/SYSTEM/LOGOCLESS.SGN");
				if(pLogoFont != NULL)
				{
					DefCurrentFont(pLogoFont);
					DrawExtendedString8859(40,36,(unsigned char*)" ",_OFF_,_dLARGE_,_PROP_WIDTH_);
				}
				else
				{
					// if the loading of the M3x font file fail try the M4x font file
					pLogoFont = LoadFont("/SYSTEM/LOGOCLESS.PGN");
					if(pLogoFont != NULL)
					{
						DefCurrentFont(pLogoFont);
						DrawExtendedString8859(40,36,(unsigned char*)" ",_OFF_,_dLARGE_,_PROP_WIDTH_);
					}
					else
					{
						GTL_Traces_TraceDebug("LOGOCLESS font file not found.");		
					}
				}
			}
	
			nResult = CLESS_CUST_CONTINUE; // Mandatory return if you don't want to use the default GUI (Manager message)
			break;

		case (CLESS_CUST_GUI_CARD_NOT_SUPPORTED_STEP_ID):
			merchLang = PSQ_Give_Language();
			nCardHolderLang = merchLang;

			ClessSample_Term_Read_Message(INTERAC_MESS_NOT_SUPPORTED_L1, nCardHolderLang, &tMsg);
			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
			ClessSample_Term_Read_Message(INTERAC_MESS_NOT_SUPPORTED_L2, nCardHolderLang, &tMsg);
			Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
			
			HelperErrorSequence (WITHBEEP);

			nResult = CLESS_CUST_CONTINUE;
			break;

		case (CLESS_CUST_GUI_USE_CONTACT_STEP_ID):
			merchLang = PSQ_Give_Language();
			nCardHolderLang = merchLang;

			ClessSample_Term_Read_Message(INTERAC_MESS_INSERT_CARD_L1, nCardHolderLang, &tMsg);
			Helper_DisplayTextCustomer(ERASE, HELPERS_CUSTOMER_LINE_2, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
			ClessSample_Term_Read_Message(INTERAC_MESS_INSERT_CARD_L2, nCardHolderLang, &tMsg);
			Helper_DisplayTextCustomer(NO_ERASE, HELPERS_CUSTOMER_LINE_3, &tMsg, CLESSSAMPLE_ALIGN_CENTER, NOLEDSOFF);
			Helper_RefreshScreen(NOWAIT, HELPERS_CUSTOMER_SCREEN);
			
			HelperErrorSequence (WITHBEEP);

			nResult = CLESS_CUST_CONTINUE;
			break;

		//case (CLESS_CUST_GUI_RETRY_AMOUNT_STEP_ID):
		default:
			GTL_Traces_TraceDebug ("Custom GUI : Unknown step (id = %02x)\n", usCustomStep);
			nResult = CLESS_CUST_DEFAULT;
			break;
		}
	}
	else
	{
		nResult = CLESS_CUST_DEFAULT;
		GTL_Traces_TraceDebug ("Custom step tag not found\n");
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


