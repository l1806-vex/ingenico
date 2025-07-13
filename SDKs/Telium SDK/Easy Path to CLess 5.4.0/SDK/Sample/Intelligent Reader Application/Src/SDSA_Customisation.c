/**
 * \file	SDSA_Customisation.c
 * \brief 	Manages the kernel customisation.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2008 Ingenico, rue claude Chappe,\n
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


/////////////////////////////////////////////////////////////////
//// Static function definition /////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

static unsigned char gs_ucSchemeToUse = SDSA_KERNEL_IDENTIFIER_UNKNOWN;


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Set the used payment scheme.
//! \param[in] ucUsedScheme Indicates the used scheme.

void SDSA_Customisation_SetUsedPaymentScheme (const unsigned char ucUsedScheme)
{
	gs_ucSchemeToUse = ucUsedScheme;
}



//! \brief Get the used payment scheme.
//! \return The used scheme.
//!		\a SDSA_KERNEL_IDENTIFIER_UNKNOWN Scheme is not yet known.
//!		\a SDSA_KERNEL_IDENTIFIER_PAYPASS Scheme is PayPass.
//!		\a SDSA_KERNEL_IDENTIFIER_PAYWAVE Scheme is payWave.
//!		\a SDSA_KERNEL_IDENTIFIER_VISAWAVE Scheme is VisaWave.
//!		\a SDSA_KERNEL_IDENTIFIER_EXPRESSPAY Scheme is ExpressPay.
//!		\a SDSA_KERNEL_IDENTIFIER_INTERAC Scheme is Interac.
//!		\a SDSA_KERNEL_IDENTIFIER_DISCOVER Scheme is Discover.

unsigned char SDSA_Customisation_GetUsedPaymentScheme (void)
{
	return (gs_ucSchemeToUse);
}



//! \brief Perform the kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int SDSA_Customisation_Process (T_SHARED_DATA_STRUCT * pSharedData)
{
	int cr;
	int nResult = KERNEL_STATUS_CONTINUE;
	int nPosition;
	unsigned long ulReadLength;
	unsigned char * pReadValue = NULL;
	unsigned char ucCustomStep;


	// Get the step to be customised
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_KERNEL_CUSTOM_STEP, &ulReadLength, (const unsigned char **)&pReadValue);
	
	if (cr == STATUS_SHARED_EXCHANGE_OK) // If tag found
	{
		ucCustomStep = pReadValue[0];
        
		// Customisation depends on the kernel that performs the transaction
    	switch (SDSA_Customisation_GetUsedPaymentScheme())
    	{
    	case (SDSA_KERNEL_IDENTIFIER_PAYPASS):
    		nResult = SDSA_PayPass_CustomiseStep (pSharedData, ucCustomStep);
    		break;
    	case (SDSA_KERNEL_IDENTIFIER_PAYWAVE):
    		nResult = SDSA_payWave_CustomiseStep (pSharedData, ucCustomStep);
    		break;
    	case (SDSA_KERNEL_IDENTIFIER_VISAWAVE):
    		nResult = SDSA_VisaWave_CustomiseStep (pSharedData, ucCustomStep);
    		break;
		case (SDSA_KERNEL_IDENTIFIER_EXPRESSPAY):
    		nResult = SDSA_ExpressPay_CustomiseStep (pSharedData, ucCustomStep);
    		break;
		case (SDSA_KERNEL_IDENTIFIER_INTERAC):
    		nResult = SDSA_Interac_CustomiseStep (pSharedData, ucCustomStep);
    		break;
		case (SDSA_KERNEL_IDENTIFIER_DISCOVER):
    		nResult = SDSA_Discover_CustomiseStep (pSharedData, ucCustomStep);
    		break;
    	default:
    		break;
    	}
	}
    else
    {
		GTL_Traces_DiagnosticText ("SDSA_Customisation_Process : Custom step tag not found");
    }
	
	return (nResult);
}



//! \brief This function is called to customise the GUI during the DLL processing.
//! \brief Customisation is different according to the GUI mode used (specific GUI for Visa Asia)
//! \brief Customisation is different according to the selection mode (implicit or explicit)
//! \param[in] pDataStruct Shared buffer containing data necessary to customise the step.
//! \return
//!	- \ref CLESS_CUST_DEFAULT if default DLL GUI shall be executed.
//!	- \ref CLESS_CUST_CONTINUE if application made customisation and default DLL GUI shall not be executed.

int SDSA_Customisation_SelectionGui (T_SHARED_DATA_STRUCT * pDataStruct)
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
	unsigned char ucStepsToCustomise[] = {0x2C,0x58,0x00,0x00,0x00,0x00,0x00,0x00};
	const T_PAYMENT_DATA_STRUCT * pTransactionData;
		
	// Get the step to be customised
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	nGtlResult = GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_GENERIC_CUST_STEP_ID, &LengthTag, (const unsigned char **)&pReadValue);
	
	usCustomStep = pReadValue[0];

	pTransactionData = SDSA_Fill_GetTransactionDataStructure();

	if (nGtlResult == STATUS_SHARED_EXCHANGE_OK) // If tag found
	{
        switch (usCustomStep) // Steps to customise
        {
		case (CLESS_CUST_GUI_REGISTRATION_STEP_ID):
			GTL_SharedExchange_ClearEx (pDataStruct, FALSE);
			GTL_SharedExchange_AddTag (pDataStruct, TAG_GENERIC_CUST_STEPS_TO_CUSTOMISE, 8, ucStepsToCustomise);
			nResult = CLESS_CUST_CONTINUE;
			break;

		case (CLESS_CUST_GUI_IDLE_STEP_ID):
		{
			if (SDSA_Interac_IsInteracGuiMode())
			{
				SDSA_GuiState_DisplayScreen (SDSA_INTERAC_SCREEN_IDLE);
				nResult = CLESS_CUST_CONTINUE;
			}
			else
			{
				nResult = CLESS_CUST_DEFAULT;
			}
		}
		break;
		
		case (CLESS_CUST_GUI_PRESENT_CARD_AMOUNT_STEP_ID):
			// Update the transaction status
			SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_DETECT_CARD);
			
			if (!SDSA_Interac_IsInteracGuiMode())
			{
				SDSA_GuiState_DisplayScreen (SDSA_SCREEN_PRESENT_CARD);
				nResult = CLESS_CUST_DEFAULT;
			}
			else // Interac Specific GUI
			{
				SDSA_GuiState_DisplayScreen (SDSA_INTERAC_SCREEN_PRESENT_CARD);
				nResult = CLESS_CUST_CONTINUE;
			}
			break;

		case (CLESS_CUST_GUI_RETRY_AMOUNT_STEP_ID):
			// Update the transaction status
			SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_RETRY);
			
			if(!SDSA_VisaWave_IsVisaAsiaGuiMode() && !SDSA_Interac_IsInteracGuiMode())
			{
				SDSA_GuiState_DisplayScreen (SDSA_SCREEN_RETRY);
				nResult = CLESS_CUST_DEFAULT;
			}
			else if (SDSA_Interac_IsInteracGuiMode()) // Interac Specific GUI
			{
				SDSA_GuiState_DisplayScreen (SDSA_INTERAC_SCREEN_PRESENT_CARD);
				nResult = CLESS_CUST_CONTINUE;
			}
			else // Visa Asia specific GUI
			{
				SDSA_GuiState_DisplayScreen (SDSA_VISAWAVE_SCREEN_RETRY);

				TPass_LedsOffColored(TPASS_LED_RED);
				TPass_LedsBlinkColored(TPASS_LED_BLUE, VISA_ASIA_LED_BLINK_ON, VISA_ASIA_LED_BLINK_OFF);

				// Display the 'PRESENT CARD' message
				SDSA_GuiState_DisplayScreen (SDSA_SCREEN_PRESENT_CARD);
			
				nResult = CLESS_CUST_CONTINUE;
			}
			break;

		case (CLESS_CUST_GUI_COLLISION_STEP_ID):

			// Update the transaction status
			SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_COLLISION);
			
			if(!SDSA_VisaWave_IsVisaAsiaGuiMode() && !SDSA_Interac_IsInteracGuiMode())
				SDSA_GuiState_DisplayScreen(SDSA_SCREEN_COLLISION);
			else if (SDSA_Interac_IsInteracGuiMode()) // Interac Specific GUI
				SDSA_GuiState_DisplayScreen (SDSA_INTERAC_SCREEN_COLLISION);
			else // Visa Asia specific GUI
				SDSA_GuiState_DisplayScreen(SDSA_VISAWAVE_SCREEN_COLLISION);

			nResult = CLESS_CUST_CONTINUE;
			
			break;

		case (CLESS_CUST_GUI_CARD_NOT_SUPPORTED_STEP_ID):

			if(!SDSA_Interac_IsInteracGuiMode())
			{
				// GUI will be managed by the CST application: here to avoid the DLL to perform a beep.
				nResult = CLESS_CUST_CONTINUE;
			}
			else // Interac Specific GUI
			{
				// Display the 'Not Supported' message
				SDSA_GuiState_DisplayScreen (SDSA_INTERAC_SCREEN_NOT_SUPPORTED);
				nResult = CLESS_CUST_CONTINUE;

			}
			break;
		
		case (CLESS_CUST_GUI_USE_CONTACT_STEP_ID):
			
			if(SDSA_VisaWave_IsVisaAsiaGuiMode()) // Visa Asia specific GUI
			{	
				SDSA_GuiState_DisplayScreen(SDSA_VISAWAVE_SCREEN_USE_CONTACT);
				nResult = CLESS_CUST_CONTINUE;
			}
			if(SDSA_Interac_IsInteracGuiMode())
			{
				SDSA_GuiState_DisplayScreen(SDSA_INTERAC_SCREEN_USE_CONTACT);
				nResult = CLESS_CUST_CONTINUE;
			}
			else
			{
				// GUI will be managed by the CST application: here to avoid the DLL to perform a beep.
				nResult = CLESS_CUST_CONTINUE;
			}
			break;
		
		default:
			GTL_Traces_TraceDebug ("SDSA_Customisation_SelectionGui : Unknown step (id = %02x)\n", usCustomStep);
			nResult = CLESS_CUST_DEFAULT;
			break;
        }
    }
    else
    {
		nResult = CLESS_CUST_DEFAULT;
		GTL_Traces_TraceDebug ("SDSA_Customisation_SelectionGui : Custom step tag not found\n");
    }
    
	return (nResult);
}



//! \brief Function called for explicit application selection processing customisation.
//! \param[in] pDataStruct Shared exchange structure provided with customisation information.
//! \return
//! 	- CLESS_CUST_DEFAULT to use the default processing. 
//! 	- CLESS_CUST_RETRY_WITH_CLESS if the transaction shall be restarted.
//! 	- CLESS_CUST_RETRY_WITHOUT_CLESS if transaction shall be restarted without cless.
//! 	- CLESS_CUST_STOP if the transaction shall be stopped.
//! 	- CLESS_CUST_NEXT_METHOD if next application selection method shall be used (if present). 
//! 	- CLESS_CUST_CONTINUE_METHOD if next application selection criteria shall be used. 

int SDSA_Customisation_CustAsProc (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int nResult;
	int nGtlResult;
    int nPosition;
	unsigned long LengthTag;
	unsigned char * pReadValue = NULL;
	unsigned short usCustomStep;
	// Steps to customise are identified by a sequence of bits
	// Example 0x44 : the steps to customised are CLESS_CUST_AS_PROC_STEP_PPSE_STEP_ID (bit 3)
	// and CLESS_CUST_AS_PROC_STEP_END_STEP_ID (bit 7)
	unsigned char ucStepsToCustomise[] = {0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	
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
			if (SDSA_Fill_IsThereAmexAidOnly())
			{
				nGtlResult = GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_GENERIC_APPLICATION_SELECTION_RESULT, &LengthTag, (const unsigned char **)&pReadValue);
				if (nGtlResult == STATUS_SHARED_EXCHANGE_OK) // If tag found
				{
					if((pReadValue[0] == 0x0A) && (pReadValue[1] == 0x26))
					{	// CLESS_STATUS_EP_CLESS_SELECTION_NOT_ALLOWED
						nResult = CLESS_CUST_RETRY_WITHOUT_CLESS;
						break;
					}
				}
			}

			nResult = CLESS_CUST_DEFAULT;
			break;
		
		case (CLESS_CUST_AS_PROC_STEP_END_STEP_ID): // Step called when application selection is completed and no method has matched (card is not supported)
			nResult = CLESS_CUST_DEFAULT;
			if (SDSA_Fill_IsThereVisaAid())
			{
				if ((gs_ucSchemeToUse == SDSA_KERNEL_IDENTIFIER_PAYWAVE) || (gs_ucSchemeToUse == SDSA_KERNEL_IDENTIFIER_UNKNOWN))
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
    	GTL_Traces_TraceDebug ("SDSA_Customisation_CustAsProc : Custom step tag not found\n");
		nResult = CLESS_CUST_DEFAULT;
    }
	
	return (nResult);
}


//! \brief Analyse the application selection result and set the transaction result.
//! \param[in] nApplicationSelectionResult Application selection result.
//! \return The transaction result.

int SDSA_Customisation_AnalyseApplicationSelectionResult(int nApplicationSelectionResult)
{
	int nResult = SDI_STATUS_KO;

	 switch (nApplicationSelectionResult) // Steps to customise
    {
    case (CLESS_STATUS_COMMUNICATION_ERROR):
		nResult = CLESS_CR_MANAGER_RESTART;
		 // Update the transaction status
		 SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_RETRY);
    	break;

	case (CLESS_STATUS_NO_MATCHING_APDU):
		nResult = SDI_STATUS_CARD_NOT_SUPPORTED;
		
		// Visa specific requirement: use contact interface
		if (SDSA_Fill_IsThereVisaAid())
		{
			if ((gs_ucSchemeToUse == SDSA_KERNEL_IDENTIFIER_PAYWAVE) || (gs_ucSchemeToUse == SDSA_KERNEL_IDENTIFIER_UNKNOWN))
				nResult = SDI_STATUS_USE_OTHER_INTERFACE;
		}
		break;

	case (CLESS_STATUS_EP_CLESS_SELECTION_NOT_ALLOWED):
		if (SDSA_Fill_IsThereAmexAidOnly())
			nResult = SDI_STATUS_USE_OTHER_INTERFACE;
		break;

	default:
    	GTL_Traces_TraceDebug("SDSA_Customisation_AnalyseApplicationSelectionResult : Unknown application selection result (nApplicationSelectionResult=%02x)", nApplicationSelectionResult);
		nResult = SDI_STATUS_KO;
		break;
    }

	 return (nResult);
}
