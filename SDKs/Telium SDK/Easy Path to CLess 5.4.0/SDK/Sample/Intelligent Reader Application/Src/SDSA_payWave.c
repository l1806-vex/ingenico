/**
 * \file	SDSA_payWave.c
 * \brief	Manages the interface with the payWave contactless kernel.
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
 */


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDSA_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define C_CPT_TIME_20S						20


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

const char gsTerminalSupportedLanguage[] =
{
	"en"
	"fr"
};

static int nCardInBlackList = 0;
static int gs_ErrorAmountTooHigth = FALSE;			    /*!< Global data indicating if an error is due to amount graeter than TAG_EP_CLESS_TRANSACTION_LIMIT. */


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __SDSA_payWave_AddpayWaveSpecificData (T_SHARED_DATA_STRUCT * pDataStruct);
static int __SDSA_payWave_RetreiveSignature (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pSignature);
static int __SDSA_payWave_PinOnLineRequiredState (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pPinOnLineRequiredState);
static int __SDSA_payWave_WaitClessCard(T_SHARED_DATA_STRUCT * pDataStruct);
static int __SDSA_payWave_StopClessCard(void);



/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Fill buffer with specific payWave data for transaction customisation/interruption.
//! \param[out] pDataStruct Shared exchange structure filled with the specific payWave data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

static int __SDSA_payWave_AddpayWaveSpecificData (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int cr, nResult;
	char ucSupportedLang[32+1];
	unsigned long ulNbLang;
	T_KERNEL_TRANSACTION_FLOW_CUSTOM sTransactionFlowCustom;
	object_info_t ObjectInfo;
	unsigned char StepInterruption[KERNEL_PAYMENT_FLOW_STOP_LENGTH];// Bit field to stop payment flow,
																	// if all bit set to 0 => no stop during payment process
									                                // if right bit set to 1 : stop after payment step number 1
	unsigned char StepCustom[KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH]; 	// Bit field to custom payment flow,
																	// if all bit set to 0 => no stop during payment process
									                                // if right bit set to 1 : stop after payment step number 1
	if (pDataStruct == NULL)
	{
		GTL_Traces_TraceDebug("__SDSA_payWave_AddpayWaveSpecificData : Invalid Input data");
		nResult = FALSE;
		goto End;
	}
	
	// Init parameteters
	memset(StepInterruption, 0, sizeof(StepInterruption));	// Default Value : not stop on process
	memset(StepCustom, 0, sizeof(StepCustom));				// Default Value : not stop on process
	nResult = TRUE;
	
	// Indicate the steps on which the kernel shall call the custom application for step customisation
    ADD_STEP_CUSTOM(STEP_PAYWAVE_MSD_REMOVE_CARD,StepCustom); 			// To do GUI when MSD card has been read
	ADD_STEP_CUSTOM(STEP_PAYWAVE_QVSDC_REMOVE_CARD,StepCustom); 		// To do GUI when QVSDC card has been read
	ADD_STEP_CUSTOM(STEP_PAYWAVE_QVSDC_GET_CERTIFICATE,StepCustom); 	// To get the certificate for ODA step
	
	if (SDSA_IsBlackListPresent())	
		ADD_STEP_CUSTOM(STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL,StepCustom);	// To check Pan in Black list
	
	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);

	
	// Add a tag for Do_Txn management that indicates the steps on which the kernel shall stop the processing and give hand back to the custom application
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_STOP, KERNEL_PAYMENT_FLOW_STOP_LENGTH, (const unsigned char *)StepInterruption);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_payWave_AddpayWaveSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_STOP in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}

	memcpy ((void*)&sTransactionFlowCustom, (void*)StepCustom, KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH);
	sTransactionFlowCustom.usApplicationType = ObjectInfo.application_type; // Kernel will call this application for customisation 
	sTransactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL; // Kernel will call SERVICE_CUSTOM_KERNEL service id for customisation
	
    cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_KERNEL_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_payWave_AddpayWaveSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_CUSTOM in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}

	// Get the languages supported by the reader
	// Init variable
	memset(ucSupportedLang, 0, sizeof(ucSupportedLang));
	if(SDSA_Term_GetSupportedLanguages(ucSupportedLang, sizeof(ucSupportedLang)-1, &ulNbLang))
	{
		// Add the languages supported by the terminal
		cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES, (2*ulNbLang)+1, (const unsigned char *)&ucSupportedLang);
		if (cr != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("__SDSA_payWave_AddpayWaveSpecificData : Unable to add TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES in shared buffer (cr=%02x)", cr);
			nResult = FALSE;
			goto End; 
		}
	}

End:
	return (nResult);
}


//! \brief Get the payWave signature state.
//! \param[out] pSignature :
//!		- \a 0 No signature to made.
//!		- \a 1 Signature to made.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

static int __SDSA_payWave_RetreiveSignature (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pSignature)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	* pSignature = 0; // Default result : no signature
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_KERNEL_SIGNATURE_REQUESTED, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_payWave_RetreiveSignature : Unable to get SignatureRequested from the payWave kernel response (cr = %02x)", cr);
		nResult = FALSE;
		goto End;
	}
	
	* pSignature = pReadValue[0];
	
End:	
	return (nResult);
}


//! \brief Get the payWave PinOnLineRequired state.
//! \param[out] pPinOnLineRequiredState :
//!		- \a 0 No Pin OnLine Requested to made.
//!		- \a 1 Pin OnLine Requested to made.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

static int __SDSA_payWave_PinOnLineRequiredState (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pPinOnLineRequiredState)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	* pPinOnLineRequiredState = 0; // Default result : no PinOnLineRequired
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_KERNEL_ONLINE_PIN_REQUESTED, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_payWave_RetreiveSignature : Unable to get OnLinePinRequested from the payWave kernel response (cr = %02x)", cr);
		nResult = FALSE;
		goto End;
	}
	
	* pPinOnLineRequiredState = pReadValue[0];
	
End:	
	return (nResult);
}


//! \brief Manage the debug mode for payWave kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void SDSA_payWave_DebugActivation (int bActivate)
{
	T_SHARED_DATA_STRUCT * pSharedStructure;
	int nResult;
	unsigned char ucDebugMode = 0x00;
	
	if (bActivate)
		ucDebugMode = 0x01;
	
	pSharedStructure = GTL_SharedExchange_InitShared(256);
	
	if (pSharedStructure != NULL)
	{
		nResult = GTL_SharedExchange_AddTag(pSharedStructure, TAG_KERNEL_DEBUG_ACTIVATION, 1, &ucDebugMode);
		
		if (nResult != STATUS_SHARED_EXCHANGE_OK)
		{
			GTL_Traces_TraceDebug("SDSA_payWave_DebugActivation : Unable to add TAG_KERNEL_DEBUG_ACTIVATION (nResult = %02x)", nResult);
		}
		else
		{
			nResult = payWave_DebugManagement(pSharedStructure);
			
			if (nResult != KERNEL_STATUS_OK)
			{
				GTL_Traces_TraceDebug("SDSA_payWave_DebugActivation : Error occured during payWave Debug activation (nResult = %02x)", nResult);
			}
		}
		
		// Destroy the shared buffer
		GTL_SharedExchange_DestroyShare(pSharedStructure);
	}
}



//! \brief Perform the payWave kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int SDSA_payWave_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep)
{
	int nResult = KERNEL_STATUS_CONTINUE;
	int nPosition;
	unsigned char ucCapkIndex;
	unsigned char ucRid[5];
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	const unsigned char * pPan;
	unsigned long ulLgPan;
	const unsigned char * pPanSeqNumber;
	unsigned char ucVoidPanSeqNumber = C_CLESS_VOID_PAN_SEQ_NUMBER; // Unused value for PanSeqNumber
	unsigned long ulLgSeqPan;
    
    switch (ucCustomisationStep) // Steps to customise
    {
    case STEP_PAYWAVE_MSD_REMOVE_CARD:
    case STEP_PAYWAVE_QVSDC_REMOVE_CARD:
		// Display remove card message, manage leds and buzzer
		HelperRemoveCardSequence(pSharedData);
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_PAYWAVE_QVSDC_GET_CERTIFICATE):
		// The payWave kernel calls the custom application to request the transaction certificate.
		// The application shall provide the CA public key modulus and the CA public key exponent to the kernel to perform ODA.
		memset (ucRid, 0, sizeof(ucRid));
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_EMV_CA_PUBLIC_KEY_INDEX_CARD, &ulReadLength, (const unsigned char **)&pReadValue) == STATUS_SHARED_EXCHANGE_OK)
			ucCapkIndex = pReadValue[0];
		else
			ucCapkIndex = 0;
		
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_EMV_DF_NAME, &ulReadLength, (const unsigned char **)&pReadValue) == STATUS_SHARED_EXCHANGE_OK)
			memcpy (ucRid, pReadValue, 5);
		
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		
		// Get the CA Key data according to the RID and the CA Key index.
		if (!SDSA_Parameters_GetCaKeyData (pTreeCurrentParam, ucCapkIndex, ucRid, pSharedData))
		{
			GTL_Traces_TraceDebug ("SDSA_payWave_CustomiseStep : SDSA_Parameters_GetCaKeyData failed");
		}
		
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL):
		nResult = KERNEL_STATUS_CONTINUE; // default value
	
		// Take values and length of : TAG_EMV_APPLI_PAN and TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER tag.

		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		if (GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_EMV_APPLI_PAN, &ulLgPan, &pPan) != STATUS_SHARED_EXCHANGE_OK)
		{
			// Pan parameters is missing, we cannot check BlackList
			break;
		}
		
		nPosition = SHARED_EXCHANGE_POSITION_NULL;
		// Length of this tag is 1 
		if (GTL_SharedExchange_FindNext (pSharedData, &nPosition, TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER, &ulLgSeqPan, &pPanSeqNumber) != STATUS_SHARED_EXCHANGE_OK)
		{
			// Pan Sequence Number is missing, we will check BlackList without PanSeqNumber
			pPanSeqNumber = &ucVoidPanSeqNumber;
		}

		// Reset output buffer
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		
		if (SDSA_BlackListIsPan((int)ulLgPan, pPan, (int)(*pPanSeqNumber)) == TRUE)
		{
			// Card is in BlackList
			unsigned char ucPanInBlackList = 1;
			int cr;
			
			// add information in exchange buffer
			cr = GTL_SharedExchange_AddTag(pSharedData, TAG_KERNEL_PAN_IN_BLACK_LIST, 1, &ucPanInBlackList);
			if (cr != STATUS_SHARED_EXCHANGE_OK)
			{
				GTL_Traces_TraceDebug("SDSA_payWave_CustomiseStep An error occured when adding TAG_KERNEL_PAN_IN_BLACK_LIST in the shared buffer (cr = %02x)", cr);
				GTL_SharedExchange_ClearEx (pSharedData, FALSE);
				break;
			}
			nCardInBlackList = 1;
		}
		else
			nCardInBlackList = 0;

		break;
	// Other customisation steps could be defined if necessary
		
    default:
		GTL_Traces_TraceDebug ("SDSA_payWave_CustomiseStep : Step to customise (unknown) = %02x", ucCustomisationStep);
    	break;
    }
    
    return (nResult);
}


//! \brief Calls the payWave kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for payWave transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- payWave kernel result.

int SDSA_payWave_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree)
{
	int cr;
	int nResult = C_CLESS_CR_END;
	unsigned char ucOnLinePinRequested = FALSE;
	unsigned char ucSignature;
	int nPosition;
	unsigned char bOnlinePinError = FALSE;
	const unsigned char * pValue;
	unsigned long ulLg;
	unsigned char * pttq;
	int nEvent;

	
	GTL_Traces_TraceDebug ("SDSA_payWave_PerformTransaction");

	// Indicate payWave kernel is going to be used (for customisation purposes)
	SDSA_Customisation_SetUsedPaymentScheme (SDSA_KERNEL_IDENTIFIER_PAYWAVE);
    
    // Fill buffer with specific payWave data for transaction customisation/interruption
	if (!__SDSA_payWave_AddpayWaveSpecificData(pDataStruct))
	{
	    GTL_Traces_TraceDebug("SDSA_payWave_PerformTransaction : __SDSA_payWave_AddpayWaveSpecificData error\n");
	}
	else
	{	
		nEvent = ttestall (USER_EVENT_CANCEL, 1);				
		if (nEvent == USER_EVENT_CANCEL)
		{
			GTL_Traces_TraceDebug ("payWave : CANCEL KEYBOARD, goto end");
			nResult = SDI_STATUS_CANCELLED;
			goto Cancel;
		}				
	
		
		// Call the payWave kernel that will perform the transaction
		cr = payWave_DoTransaction(pDataStruct);
		
		// Save the available amount in the transaction data structure
		SDSA_Fill_SaveAvailableAmount(HELPERS_PAYWAVE, pDataStruct);		
	
		// Set language with preferred card language (if present in the kernel database)
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_PAYWAVE);
		
		// Specific treatment for on-line/Pin management
		if ((cr == KERNEL_STATUS_OFFLINE_APPROVED) || (cr == KERNEL_STATUS_ONLINE_AUTHORISATION))
		{
			__SDSA_payWave_PinOnLineRequiredState (pDataStruct, &ucOnLinePinRequested);
			if (ucOnLinePinRequested) // If pin asked
				cr = KERNEL_STATUS_ONLINE_AUTHORISATION; // => mandatory to go on-line
		}
		
		// Check if signature is requested or not
		ucSignature = 0;
		__SDSA_payWave_RetreiveSignature (pDataStruct, &ucSignature);
		
		// CR analyse
		if (cr & KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK) // If mask has been set
		{
			GTL_Traces_TraceDebug ("SDSA_payWave_PerformTransaction : CANCEL KEYBOARD");
			nResult = SDI_STATUS_CANCELLED;
		}
		else switch (cr)
		{
		case KERNEL_STATUS_OK:
			// A good transaction state must be finished by a approved, declined, ...
			nResult = SDI_STATUS_OK;
			break;

		case (KERNEL_STATUS_OFFLINE_APPROVED):
			if(SDSA_VisaWave_IsVisaAsiaGuiMode())
				Helper_Visa_DisplayAvailableAmount();

			nResult = SDI_STATUS_APPROVED;
			break;

		case (KERNEL_STATUS_OFFLINE_DECLINED):
			nResult = SDI_STATUS_DECLINED;
			break;
			
		case (KERNEL_STATUS_ONLINE_AUTHORISATION):
			// Is Online Pin asked and possible ?
			if (ucOnLinePinRequested) // If OnLine Pin Requested
			{    
				nPosition = SHARED_EXCHANGE_POSITION_NULL;
				if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_APPLI_PAN, &ulLg, &pValue) != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug ("SDSA_payWave_PerformTransaction : Missing PAN for Online PIN");
					bOnlinePinError = TRUE; // On-line Pin cannot be made
				}

				nPosition = SHARED_EXCHANGE_POSITION_NULL;
				if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_AMOUNT_AUTH_NUM, &ulLg, &pValue) != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug ("SDSA_payWave_PerformTransaction : Missing Amount auth for Online PIN");
					bOnlinePinError = TRUE; // On-line Pin cannot be made : amount to display not available
				}
				
				if (!bOnlinePinError)
				{
					if(SDSA_VisaWave_IsVisaAsiaGuiMode())
						Helper_PerformCVMSequence();
					else
						HelperLedsOff();
				}
			}

			nResult = SDI_STATUS_ONLINE_REQUEST;
			break;

		case (KERNEL_STATUS_USE_CONTACT_INTERFACE):
			nResult = SDI_STATUS_USE_OTHER_INTERFACE;
			break;
		
		case (KERNEL_STATUS_COMMUNICATION_ERROR):
			nResult = CLESS_CR_MANAGER_RESTART;
			payWave_Clear(); // If restart is required, kernel database shall be cleared
			break;
	
		case (KERNEL_STATUS_REMOVE_AID):
			nResult = CLESS_CR_MANAGER_REMOVE_AID;
			payWave_Clear(); // If restart is required, kernel database shall be cleared
			break;

		case (KERNEL_STATUS_MOBILE):
			if (SDSA_Common_RetreiveInfo (pDataStruct, TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS, &pttq))
			{
				if (pttq[0] & 0x20) // If qVSDC supported
				{
					ClessEmv_CloseDriver();

					// Update the transaction status
					SDSA_State_SetCurrentState(SDSA_PAYMENT_STATUS_DOUBLE_TAP);
					
					SDSA_GuiState_DisplayScreen(SDSA_PAYWAVE_SCREEN_PHONE_INSTRUCTIONS);		
					payWave_Clear(); // If restart is required, kernel database shall be cleared
					nResult = CLESS_CR_MANAGER_RESTART_DOUBLE_TAP;
				}
				else
				{
					nResult = SDI_STATUS_KO;
				}
			}
			else
			{
				nResult = SDI_STATUS_KO;
			}
		
			break;

		default:
			GTL_Traces_TraceDebug ("SDSA_payWave_PerformTransaction result = %02x", cr);

			nResult = SDI_STATUS_KO;
			break;
		}
Cancel:
		// Cless field must be stopped only if we don't try to work with an another AID
		if (nResult != CLESS_CR_MANAGER_REMOVE_AID)
		{
			ClessEmv_CloseDriver();
		}
        if ((nResult != CLESS_CR_MANAGER_REMOVE_AID) && (nResult != CLESS_CR_MANAGER_RESTART) && (nResult != CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY) && (nResult != CLESS_CR_MANAGER_RESTART_DOUBLE_TAP))		
        {
    		// Send data to the CST application. If TAG_SDSA_LIST_OF_OUTPUT_TAGS is not provided, default tag list is returned.
	    	if(!SDSA_Common_GetListOfOutputTags(hOutputTlvTree))
		    	SDSA_Common_CopyDataStructInTLVTree(pDataStruct, hOutputTlvTree);
		}
	}

	return (nResult);
}


//! \brief Wait Cless Card.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \return
//!		- \a SDI_STATUS_OK if appropriate card has been inputed on field.
//!		- \a SDI_STATUS_CANCELLED if the card detection has been cancelled.
//!		- \a SDI_STATUS_KO else.

static int __SDSA_payWave_WaitClessCard(T_SHARED_DATA_STRUCT * pDataStruct)
{
	unsigned char ucSW1, ucSW2;
	unsigned char aResponse[257];
	unsigned int bIsOpened, nTimeout, nEvent;
	unsigned int nNumOfCards, bStop;
	unsigned int nResponseLength;
	int nFctResult, nCpt, cr;
	int nAppropriateCardFounded;
	int nCr = KERNEL_STATUS_OK; // Default result
	int nResult = SDI_STATUS_KO;
	int nPosition;
	T_TI_LENGTH ReadLength;
	const unsigned char * pReadValue;


	// Local variables initialization
	nFctResult = FALSE;					// Default result : card isn't ok
	nCpt = 0;							// Time counter initialisation (step = 1s)
	nAppropriateCardFounded = FALSE;	// Default result : card hasn't been found
	bStop = FALSE;

	// Add TAG_EMV_ISSUER_AUTHENTICATION_DATA tag
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext(pDataStruct, &nPosition, TAG_EP_FINAL_SELECT_COMMAND_SENT, &ReadLength, &pReadValue);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		// We have'nt information, what can we made ?
		goto EndCardTreatment;
	}

	// Sends a command to an ISO14443 contact less card.
	nResponseLength = sizeof(aResponse);

	do{ // Infinite loop to wait the appropriate card (with good AID ....)

		// Cless Field Close allows to restart it later ...
		ClessEmv_CloseDriver();

		// Card Power-On
		bIsOpened = ClessEmv_OpenDriver (); // Open contactless field
		if (bIsOpened != CL_OK) 			// If contactless field not opened
			goto EndCardTreatment;

		do{ // Infinite loop to wait a Contacless Card detection
			// Synchrone Detection (bloquante)
			nTimeout = 1; // 1s
			nNumOfCards = 1;
			nCr = ClessEmv_DetectCards(CL_TYPE_AB, &nNumOfCards, nTimeout);

			if (nCr != CL_OK) // If card hasn't been detected
			{
				nTimeout = 100; // 1s
				nEvent = ttestall (USER_EVENT_CANCEL, nTimeout);

				if (nEvent & USER_EVENT_CANCEL)
				{
					nResult = SDI_STATUS_CANCELLED;
					nCpt = C_CPT_TIME_20S; // End loop
				}
				else // Timeout
				{
					// On first loop, display : represent card
					if (nCpt == 0)
						HelperRepresentCardSequence(pDataStruct);
				}	
			}
			nCpt ++;
		}while ((nCr != CL_OK) && (nCpt < C_CPT_TIME_20S)); // For 20s max

		if (nCr != CL_OK) // End if no card detected
			goto EndCardTreatment;

		// Active the Cless Card if a card has been detected
		if (ClessEmv_ActiveCard(0, CL_ISO14443_4) != CL_OK)
			continue; // End if a problem occurs on card detection, we can try to restart

		if (nCr != CL_OK)
		{
			// A problem occurs, what can we made ?
			// We try to continue ...
		}

		// Final select selection
		nFctResult = ClessEmv_Apdu(0, (void*)pReadValue, ReadLength, aResponse, &nResponseLength);
		if (nFctResult != CL_OK)
			goto EndCardTreatment; // A problem occurs

		// Control if last AID selection is ok
		ucSW1 = ((unsigned char*)aResponse)[nResponseLength-2];
		ucSW2 = ((unsigned char*)aResponse)[nResponseLength-1];

		// If card response ok
		if ((ucSW1 == 0x90) && (ucSW2 == 0x00)) // If it's the appropriate card
		{
			nAppropriateCardFounded = TRUE; // Card founded !!!!!!
			nResult = SDI_STATUS_OK;
		}
		else // If card response KO
		{
			HelperRemoveCardSequence(pDataStruct);

			nFctResult = ClessEmv_DeselectCard(0, TRUE, TRUE); // Deselect card with wait a card removal
			if (nFctResult != CL_OK)
			{
				// A problem occurs !
				nCpt = C_CPT_TIME_20S; // End !!!
			}
			else
			{
				HelperRepresentCardSequence(pDataStruct);
			}
		}
	}while ((nAppropriateCardFounded == FALSE) && (nCpt < C_CPT_TIME_20S)); // If Appropriate card hasn't been founded and for 20s max

EndCardTreatment:

	return(nResult);
}


//! \brief Stop Cless field.
//! \return
//!		- \a TRUE always.

static int __SDSA_payWave_StopClessCard(void)
{
	int nFctResult;

	// Card deselection
	nFctResult = ClessEmv_DeselectCard(0, TRUE, FALSE); // Deselect card without wait a card removal
	if (nFctResult != CL_OK)
	{
		// A problem occurs !
		// ..
	}

	ClessEmv_CloseDriver();

	return(TRUE);
}


//! \brief Calls the payWave kernel to perform the post transaction processing.
//! \param[in] pDataStruct Data buffer to be filled and used for payWave transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- payWave kernel result.

int SDSA_payWave_PerformPostProcessing (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree)
{
	int nResult = SDI_STATUS_KO;
	T_SHARED_DATA_STRUCT * pTmpStructure;

	pTmpStructure = GTL_SharedExchange_InitShared(32768);
	if(pTmpStructure == NULL)
	{
		goto End;
	}

	payWave_GetAllData(pTmpStructure); // Get all the kernel data to print the receipt

	nResult = __SDSA_payWave_WaitClessCard(pTmpStructure);
	if (nResult == SDI_STATUS_OK)
	{
		// Perform the payWave transaction
		nResult = payWave_AfterTransaction(pDataStruct);
		if(nResult == KERNEL_STATUS_OK)
			nResult = SDI_STATUS_OK;
		
		// Send data to the CST application. If TAG_SDSA_LIST_OF_OUTPUT_TAGS is not provided, default tag list is returned. 
        if ((nResult != CLESS_CR_MANAGER_REMOVE_AID) && (nResult != CLESS_CR_MANAGER_RESTART) && (nResult != CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY) && (nResult != CLESS_CR_MANAGER_RESTART_DOUBLE_TAP))		
        {
		    if(!SDSA_Common_GetListOfOutputTags(hOutputTlvTree))
			    SDSA_Common_CopyDataStructInTLVTree(pDataStruct, hOutputTlvTree);
		}
	}

	__SDSA_payWave_StopClessCard();

	// Destroy the shared buffer
	if (pTmpStructure)
		GTL_SharedExchange_DestroyShare(pTmpStructure);

End:
	return (nResult);
}

//! \brief Modify several parameters before to use it.
//! \param[in] pShareStruct Share buffer given and modified by EntryPoint.
//! \param[in/out] pAidParameters parameters found to manage AID.
//!	\return
//!		- payWave kernel result.

void SDSA_payWave_AidRelatedData(T_SHARED_DATA_STRUCT * pSharedStruct, T_SHARED_DATA_STRUCT * pAidParameters)
{
	// Local variables
	int cr;
	int nPositionElement;
	unsigned long ulReadLengthElement, ulAidReadLengthElement, ulTransactionLimitLength;
	unsigned char *pReadValueElement;
	unsigned char *pAidReadValueElement;
	unsigned char *pAidOption;
	unsigned char *pZeroCheckDeactivated;
	unsigned char *pTransactionLimit;
	unsigned long ulTransactionAmount;
	unsigned long ulTransactionLimit;

	// Protection against bad parameters
	if ((pSharedStruct == NULL) || (pAidParameters == NULL))
		return;

	//////////////////////////////////////////////////////////
	// TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS management
	//////////////////////////////////////////////////////////
	
	// Warning, Entry Point modify the TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS parameters
	// First bit managed by EntryPoint : byte 2, bit 8 : Online cryptogram required / not required
	// Second bit managed by EntryPoint : byte 2, bit 7 : CVM required / not required

	// Find the TTQ from EP buffer
	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pSharedStruct, &nPositionElement, TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS, &ulReadLengthElement, (const unsigned char **)&pReadValueElement);
    if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
		return;	// No TTQ found, what can we made ?
	
	// Find the TTQ in pAidParameters structure
	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS, &ulAidReadLengthElement, (const unsigned char **)&pAidReadValueElement);
    if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
		return;	// No TTQ found, what can we made ?

    // If parameters taken == Cless qVSDC
    if (pAidReadValueElement[0] & 0x20)
    // 		=> CVM required and Online Cryptogram required bits taken from Cless_debit_Aid parameters
    {
        pAidReadValueElement[1] &= 0x3F; 						// 00XX XXXX erase Online cryptogram required & CVM required bit
        pAidReadValueElement[1] |= pReadValueElement[1] & 0xC0; // Take Online cryptogram required & EntryPoint CVM bit value
        
        ulTransactionAmount = SDSA_Fill_GiveAmount();
        
        if (ulTransactionAmount == 0)
        {
        	// Find the TTQ in pAidParameters structure
        	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
        	cr = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_EP_AID_OPTIONS, &ulAidReadLengthElement, (const unsigned char **)&pAidOption);
            if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
        		return;	// No AID option found, what can we made ?
        	
        	// If zero amount not authorized for this AID and Cless qVSDC
            if ((pAidOption[0] & 0x04) == 0x00)
            {
            	unsigned char ucQvsdcNotAllowed = 1;
            	// Delete the Contactless magnetic stripe (MSD) supported and Contactless qVSDC supported
            	pAidReadValueElement[0] &= 0x5F;
            	// Delete Online cryptogram required
            	pAidReadValueElement[1] &= 0x7F;
            	
            	// Add tag TAG_PAYWAVE_QVSDC_NOT_ALLOWED with information true
            	cr = GTL_SharedExchange_AddTag (pAidParameters, TAG_PAYWAVE_QVSDC_NOT_ALLOWED, 1, &ucQvsdcNotAllowed);
                if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
                	return;	// pb to store information, what can we made ?
            }
			else // If zero amount authorized for this AID and Cless qVSDC
            {
        	    nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
        	    cr = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_SDSA_ZERO_CHECK_DEACTIVATED, &ulReadLengthElement, (const unsigned char **)&pZeroCheckDeactivated);
                if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
        		    return;	// No specific information added => no action
        		    
                if (pZeroCheckDeactivated[0])
				  // Delete the Online cryptogram required information
				  pAidReadValueElement[1] &= 0x7F;
            }
        }
        else if (ulTransactionAmount == 100) // Specific amount : 1 currency (status check), this specific amount is used to check a qVSDC card
        {
        	// Find the TTQ in pAidParameters structure
        	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
        	cr = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_EP_AID_OPTIONS, &ulAidReadLengthElement, (const unsigned char **)&pAidOption);
            if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
        		return;	// No AID option found, what can we made ?

        	// If Status Check allowed
            if ((pAidOption[0] & 0x02) == 0x02)
            {
				// Set Online cryptogram required
				pAidReadValueElement[1] |= 0x80;
            }
        }
        else
        {
	        // Check if amount not greater than TAG_EP_CLESS_TRANSACTION_LIMIT
        	
        	// Find the TAG_EP_CLESS_TRANSACTION_LIMIT in pAidParameters structure
        	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
        	cr = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_EP_CLESS_TRANSACTION_LIMIT, &ulTransactionLimitLength, (const unsigned char **)&pTransactionLimit);
            if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
        		return;	// No AID option found, what can we made ?

            GTL_Convert_DcbNumberToUl(pTransactionLimit, &ulTransactionLimit, ulTransactionLimitLength);

            if (ulTransactionAmount >= ulTransactionLimit)
            {
            	// Find the TTQ in pAidParameters structure
            	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
            	cr = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_EP_AID_OPTIONS, &ulAidReadLengthElement, (const unsigned char **)&pAidOption);
                if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
            		return;	// No AID option found, what can we made ?
            	
            	// Warning : here, ulTransactionAmount >= ulTransactionLimit
            	SDSA_payWave_SetQVSDCNotAllowedForAmount(TRUE);
            	
                {
                	unsigned char ucQvsdcNotAllowed = 1;
                	// Delete the Contactless magnetic stripe (MSD) supported and Contactless qVSDC supported
                	pAidReadValueElement[0] &= 0x5F;
                	
                	// Add tag TAG_PAYWAVE_QVSDC_NOT_ALLOWED with information true
                	cr = GTL_SharedExchange_AddTag (pAidParameters, TAG_PAYWAVE_QVSDC_NOT_ALLOWED, 1, &ucQvsdcNotAllowed);
                    if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
                    	return;	// pb to store information, what can we made ?
                }
            }
        }
    }
    else
    {
    //	if parameters taken == MSD (only)
        if (pAidReadValueElement[0] & 0x80)
        {
			pReadValueElement[1] &= 0x7F;								// 0XXX XXXX erase Online cryptogram required 
			pReadValueElement[1] |= pAidReadValueElement[1] & 0x80;		// Take Online cryptogram required bit value 

        }
    }
}


//! \brief Allows to known if error is due to amount greater than TAG_EP_CLESS_TRANSACTION_LIMIT
//!	\return
//!		- TRUE if error is due to amount greater than TAG_EP_CLESS_TRANSACTION_LIMIT.
//!     - FALSE else.
int SDSA_payWave_IsQVSDCNotAllowedForAmount(void)
{
    return (gs_ErrorAmountTooHigth);
}

//! \brief Memorise if amount is greater than TAG_EP_CLESS_TRANSACTION_LIMIT.
//! \param[in] TRUE/FALSE error due to amount greater than TAG_EP_CLESS_TRANSACTION_LIMIT.
void SDSA_payWave_SetQVSDCNotAllowedForAmount(int nAmountGreaterThanTransactionLimit)
{
    gs_ErrorAmountTooHigth = nAmountGreaterThanTransactionLimit;
}

