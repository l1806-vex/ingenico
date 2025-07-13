/**
 * \file	SDSA_Interac.c
 * \brief	Manages the interface with the Interac contactless kernel.
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


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

const char gsInteracTerminalSupportedLanguage[] =
{
	"en"
	"fr"
};

static int gs_bIsInteracGuiMode = FALSE;				// Set to TRUE if the Interac GUI must be used


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static int __SDSA_Interac_AddInteracSpecificData (T_SHARED_DATA_STRUCT * pDataStruct);
static int __SDSA_Interac_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Get the Interac CVM to perform.
//! \param[out] pCvm Retreived transaction CVM :
//!		- \a VISAWAVE_CVM_NO_CVM No CVM to be performed.
//!		- \a VISAWAVE_CVM_SIGNATURE if signature shall be performed.
//!		- \a VISAWAVE_CVM_ONLINE_PIN if online PIN shall be performed.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

static int __SDSA_Interac_RetreiveCvmToApply (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned char * pCvm)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	* pCvm = INTERAC_CVM_NO_CVM; // Default result
	
	// Get the transaction CVM tag from the shared buffer returned by the Interac kernel
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, TAG_INTERAC_TRANSACTION_CVM, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		nResult = FALSE;
		goto End;
	}
	
	// Get the CVM to apply
	* pCvm = pReadValue[0];
	
End:	
	return (nResult);
}

//! \brief Fill buffer with specific Interac data for transaction customisation/interruption.
//! \param[out] pDataStruct Shared exchange structure filled with the specific Interac data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

static int __SDSA_Interac_AddInteracSpecificData (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int cr, nResult;
	char ucSupportedLang[32+1];
	unsigned long ulNbLang;
	unsigned char ucTempBuffer;
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
		GTL_Traces_TraceDebug("__SDSA_Interac_AddInteracSpecificData : Invalid Input data");
		nResult = FALSE;
		goto End;
	}
	
	// Init parameteters
	memset(StepInterruption, 0, sizeof(StepInterruption));	// Default Value : not stop on process
	memset(StepCustom, 0, sizeof(StepCustom));				// Default Value : not stop on process
	nResult = TRUE;
	
	// Indicate the steps on which the kernel shall call the custom application for step customisation
    ADD_STEP_CUSTOM(STEP_INTERAC_REMOVE_CARD,StepCustom); 		// To do GUI when card has been read
	ADD_STEP_CUSTOM(STEP_INTERAC_GET_CERTIFICATE,StepCustom); 	// To get the certifiacte for ODA step

	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
	
	// Add a tag for Do_Txn management that indicates the steps on which the kernel shall stop the processing and give hand back to the custom application
	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_STOP, KERNEL_PAYMENT_FLOW_STOP_LENGTH, (const unsigned char *)StepInterruption);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_Interac_AddInteracSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_STOP in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}

	memcpy ((void*)&sTransactionFlowCustom, (void*)StepCustom, KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH);
	sTransactionFlowCustom.usApplicationType = ObjectInfo.application_type; // Kernel will call this application for customisation 
	sTransactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL; // Kernel will call SERVICE_CUSTOM_KERNEL service id for customisation
	
    cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_KERNEL_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__SDSA_Interac_AddInteracSpecificData : Unable to add TAG_KERNEL_PAYMENT_FLOW_CUSTOM in shared buffer (cr=%02x)", cr);
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
			GTL_Traces_TraceDebug("__SDSA_Interac_AddInteracSpecificData : Unable to add TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES in shared buffer (cr=%02x)", cr);
			nResult = FALSE;
			goto End; 
		}
	}

	if (SDSA_Fill_GiveTransactionType() == SDSA_TRANSACTION_TYPE_REFUND)
	{
		ucTempBuffer=0x01;		// Interac v1.2, Section 4.7.2: set tag 9F5A to 0x01 for REFUND
	}
	else
	{
		ucTempBuffer=0x00;		// Interac v1.2, Section 4.7.2: set tag 9F5A to 0x00 for all other transactions
	}

	cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_INTERAC_TERMINAL_TRANSACTION_TYPE, 1, &ucTempBuffer);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("__ClessSample_Interac_AddInteracSpecificData : Unable to add TAG_INTERAC_TERMINAL_TRANSACTION_TYPE in shared buffer (cr=%02x)", cr);
		nResult = FALSE;
		goto End;
	}
End:
	return (nResult);
}


//! \brief Manage the debug mode for Interac kernel
//! \param[in] bActivate \a TRUE to activate the debug features. \a FALSE to deactivate features.

void SDSA_Interac_DebugActivation (int bActivate)
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
			GTL_Traces_TraceDebug("SDSA_Interac_DebugActivation : Unable to add TAG_KERNEL_DEBUG_ACTIVATION (nResult = %02x)", nResult);
		}
		else
		{
			nResult = Interac_DebugManagement(pSharedStructure);
			
			if (nResult != KERNEL_STATUS_OK)
			{
				GTL_Traces_TraceDebug("SDSA_Interac_DebugActivation : Error occured during Interac Debug activation (nResult = %02x)", nResult);
			}
		}
		
		// Destroy the shared buffer
		GTL_SharedExchange_DestroyShare(pSharedStructure);
	}
}



//! \brief Perform the Interac kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \param[in] ucCustomisationStep Step to be customised.
//! \return
//!		- \a KERNEL_STATUS_CONTINUE always.

int SDSA_Interac_CustomiseStep (T_SHARED_DATA_STRUCT * pSharedData, const unsigned char ucCustomisationStep)
{
	int nResult = KERNEL_STATUS_CONTINUE;
	int nPosition;
	unsigned char ucCapkIndex;
	unsigned char ucRid[5];
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
    switch (ucCustomisationStep) // Steps to customise
    {
    case STEP_INTERAC_REMOVE_CARD:
    	// Display remove card message, manage leds and buzzer
		HelperRemoveCardSequence(pSharedData);
		GTL_SharedExchange_ClearEx (pSharedData, FALSE);
		nResult = KERNEL_STATUS_CONTINUE;
		break;
	
	case (STEP_INTERAC_GET_CERTIFICATE):
		// The Interac kernel calls the custom application to request the transaction certificate.
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
			GTL_Traces_TraceDebug ("SDSA_Interac_CustomiseStep : SDSA_Parameters_GetCaKeyData failed");
		}
		
		nResult = KERNEL_STATUS_CONTINUE;
		break;

	// Other customisation steps could be defined if necessary
	
    default:
		GTL_Traces_TraceDebug ("SDSA_Interac_CustomiseStep : Step to customise (unknown) = %02x", ucCustomisationStep);
    	break;
    }
    
    return (nResult);
}


//! \brief Calls the Interac kernel to perform the transaction.
//! \param[in] pDataStruct Data buffer to be filled and used for Interac transaction.
//! \param[out] hOutputTlvTree Output TLV Tree containing the transaction result.
//!	\return
//!		- Interac kernel result.

int SDSA_Interac_PerformTransaction (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree)
{
	int cr;
	int nResult = C_CLESS_CR_END;
	unsigned char ucCvm;
	int nPosition;
	unsigned char bOnlinePinError = FALSE;
	const unsigned char * pValue;
	unsigned long ulLg;
	int nEvent;
	unsigned long ulReceiptTags[] = {TAG_EMV_APPLI_PAN, TAG_EMV_APPLI_EXPIRATION_DATE, TAG_EMV_TRANSACTION_TIME, 
		                             TAG_EMV_TRANSACTION_DATE, TAG_EMV_APPLICATION_LABEL, TAG_EMV_APPLI_PREFERED_NAME,
									 TAG_EMV_AID_CARD, TAG_EMV_AMOUNT_AUTH_BIN, TAG_EMV_TVR, TAG_EMV_DF_NAME,
									 TAG_EMV_TRANSACTION_TYPE, TAG_INTERAC_RECEIPT_STATUS};

	GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction");

	// Indicate Interac kernel is going to be used (for customisation purposes)
	SDSA_Customisation_SetUsedPaymentScheme (SDSA_KERNEL_IDENTIFIER_INTERAC);
    
    // Fill buffer with specific Interac data for transaction customisation/interruption
	if (!__SDSA_Interac_AddInteracSpecificData(pDataStruct))
	{
	    GTL_Traces_TraceDebug("SDSA_Interac_PerformTransaction : __SDSA_Interac_AddInteracSpecificData error\n");
	}
	else
	{
		GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction: Specific data added");

		nEvent = ttestall (USER_EVENT_CANCEL, 1);				
		if (nEvent == USER_EVENT_CANCEL)
		{
			GTL_Traces_TraceDebug ("Interac : CANCEL KEYBOARD, goto end");
			nResult = SDI_STATUS_CANCELLED;
			goto Cancel;
		}				
	
		if(SDSA_Interac_IsInteracGuiMode())
		{
			// Display the "Processing" message
			Helper_DisplayMessage(INTERAC_MESS_PROCESSING, ERASE, HELPERS_CUSTOMER_LINE_2, HELPERS_ALIGN_CENTER, LEDSOFF);
			
			// Turn on the 2nd LED
			TPass_LedsOnColored(TPASS_LED_YELLOW);
		}

		// Call the Interac kernel that will perform the transaction
		cr = Interac_DoTransaction(pDataStruct);
		
		// Set language with preferred card language (if present in the kernel database)
		SDSA_UserInterface_SetCardholderLanguage(SDSA_KERNEL_IDENTIFIER_INTERAC);
		
		// Get the TAG_VISAWAVE_TRANSACTION_CVM to identify the CVM to be performed :
		// 	- INTERAC_CVM_NO_CVM (0x01) : "No CVM" method has been applied.
		// 	- INTERAC_CVM_SIGNATURE (0x02) : "Signature" method has been applied.
		// 	- INTERAC_CVM_ONLINE_PIN (0x04) : "Online PIN" method has been applied.
		if (!__SDSA_Interac_RetreiveCvmToApply (pDataStruct, &ucCvm))
		{
			ucCvm = INTERAC_CVM_NO_CVM;
		}

		if ((ucCvm == INTERAC_CVM_ONLINE_PIN) && (cr == KERNEL_STATUS_OFFLINE_APPROVED))
			cr = KERNEL_STATUS_ONLINE_AUTHORISATION;
	
		// CR analyse

		if (cr & KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK) // If mask has been set
		{
			GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction : CANCEL KEYBOARD");
			nResult = SDI_STATUS_CANCELLED;
		}
		else switch (cr)
		{
		case KERNEL_STATUS_OK:
			// A good transaction state must be finished by approved, declined, ... 
			nResult = SDI_STATUS_OK;
			GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction: KERNEL_STATUS_OK");
			break;

		case (KERNEL_STATUS_OFFLINE_APPROVED):
			nResult = SDI_STATUS_APPROVED;
			GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction: KERNEL_STATUS_OFFLINE_APPROVED");
			break;
			
		case (KERNEL_STATUS_ONLINE_AUTHORISATION):
			if (ucCvm == INTERAC_CVM_ONLINE_PIN) // If OnLine Pin Requested
			{    
				nPosition = SHARED_EXCHANGE_POSITION_NULL;
				if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_APPLI_PAN, &ulLg, &pValue) != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction : Missing PAN for Online PIN");
					bOnlinePinError = TRUE; // On-line Pin cannot be made
				}

				nPosition = SHARED_EXCHANGE_POSITION_NULL;
				if (GTL_SharedExchange_FindNext (pDataStruct, &nPosition, TAG_EMV_AMOUNT_AUTH_NUM, &ulLg, &pValue) != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction : Missing Amount auth for Online PIN");
					bOnlinePinError = TRUE; // On-line Pin cannot be made : amount to display not available
				}
				
				if (!bOnlinePinError)
				{
					if(SDSA_Interac_IsInteracGuiMode())
						Helper_PerformCVMSequence();
					else
						HelperLedsOff();
				}
			}

			GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction: KERNEL_STATUS_ONLINE_AUTH");
		
			nResult = SDI_STATUS_ONLINE_REQUEST;
			break;

		case (KERNEL_STATUS_USE_CONTACT_INTERFACE):
			nResult = SDI_STATUS_USE_OTHER_INTERFACE;
			GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction : USE_ANOTHER_INTERFACE");
			break;

		case (KERNEL_STATUS_COMMUNICATION_ERROR):
			nResult = CLESS_CR_MANAGER_RESTART;
			Interac_Clear(); // If restart is required, kernel database shall be cleared
			GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction : COMMS_ERROR");
			break;

		case (KERNEL_STATUS_REMOVE_AID):
			nResult = CLESS_CR_MANAGER_REMOVE_AID;
			Interac_Clear(); // If restart is required, kernel database shall be cleared
			GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction : REMOVE_AID");
			break;
			
		case (KERNEL_STATUS_OFFLINE_DECLINED):
			nResult = SDI_STATUS_DECLINED;
			GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction : kERNEL_STATUS_OFFLINE_DECLINED");
			break;
		
		default:
			GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction result = %02x", cr);
			break;
		}
Cancel:
		// Cless field must be stopped only if we don't try to work with an another AID
		if (nResult != CLESS_CR_MANAGER_REMOVE_AID)
		{
			ClessEmv_CloseDriver();
			GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction: Driver Closed");
		}

		GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction: Get data for CST");

		// add extra tags to retrieve from kernel
		SDSA_Common_SetListOfOutputTags((unsigned char *)ulReceiptTags, sizeof(ulReceiptTags));


		// Send data to the CST application. If TAG_SDSA_LIST_OF_OUTPUT_TAGS is not provided, default tag list is returned. 
        if ((nResult != CLESS_CR_MANAGER_REMOVE_AID) && (nResult != CLESS_CR_MANAGER_RESTART) && (nResult != CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY) && (nResult != CLESS_CR_MANAGER_RESTART_DOUBLE_TAP))		
        {
		    if(!SDSA_Common_GetListOfOutputTags(hOutputTlvTree))
		    {
			    GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction: common call for output tags failed");
			    SDSA_Common_CopyDataStructInTLVTree(pDataStruct,hOutputTlvTree);
		    }
		    else
		    {
			    GTL_Traces_TraceDebug ("SDSA_Interac_PerformTransaction : Common call for tags good");
		    }
		}
	}

	return (nResult);
}


//! \brief Modify several parameters before to use it.
//! \param[in] pShareStruct Share buffer given and modified by EntryPoint.
//! \param[in/out] pAidParameters parameters found to manage AID.
//!	\return
//!		- Interac kernel result.

void SDSA_Interac_AidRelatedData(T_SHARED_DATA_STRUCT * pSharedStruct, T_SHARED_DATA_STRUCT * pAidParameters)
{
	// Local variables
	int cr;
	int nPositionElement;
	unsigned long ulReadLengthElement, ulAidReadLengthElement, ulTerminalTypeLength;
	unsigned char *pReadValueElement;
	unsigned char *pAidReadValueElement;
	unsigned char *pTerminalType;
	
	// Protection against bad parameters
	if ((pSharedStruct == NULL) || (pAidParameters == NULL))
		return;

	//////////////////////////////////////////////////////////
	// TAG_VISAWAVE_TERMINAL_TRANSACTION_QUALIFIERS management
	//////////////////////////////////////////////////////////
	
	// Warning, Entry Point modify the TAG_VISAWAVE_TERMINAL_TRANSACTION_QUALIFIERS parameters
	// First bit managed by EntryPoint : byte 2, bit 8 : Online cryptogram required / not required
	// Second bit managed by EntryPoint : byte 2, bit 7 : CVM required / not required

	// Find the TTQ from EP buffer
	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pSharedStruct, &nPositionElement, TAG_VISAWAVE_TERMINAL_TRANSACTION_QUALIFIERS, &ulReadLengthElement, (const unsigned char **)&pReadValueElement);
    if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
		return;	// No TTQ found, what can we made ?
	
	// Find the TTQ in pAidParameters structure
	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_VISAWAVE_TERMINAL_TRANSACTION_QUALIFIERS, &ulAidReadLengthElement, (const unsigned char **)&pAidReadValueElement);
    if (cr != STATUS_SHARED_EXCHANGE_OK)  // If tag with AID informations found
		return;	// No TTQ found, what can we made ?

    // If parameters taken == Cless qVSDC
    if (pAidReadValueElement[0] & 0x20)
    // 		=> CVM required and Online Cryptogram required bits taken from Cless_debit_Aid parameters
    {
        pAidReadValueElement[1] &= 0x3F; 						// 00XX XXXX erase Online cryptogram required & CVM required bit
        pAidReadValueElement[1] |= pReadValueElement[1] & 0xC0; // Take Online cryptogram required & EntryPoint CVM bit value
    }
    // else
    else
    {
    //	if parameters taken == MSD (only)
        if (pAidReadValueElement[0] & 0x80)
        {
        	//	=> CVM required and Online Cryptogram required bits taken from parameters (CLESSCUST.PAR)
        	// pAidReadValueElement[1] allready ok !!!
        }
    }
	
	//////////////////////////////////////////////////////////
	// TAG_EMV_TERMINAL_TYPE management
	//////////////////////////////////////////////////////////

	// 0x01 supports domestic contactless transactions only
	// 0x00 supports international contactless transactions

	// Find the Terminal Type(0x9F35) in pAidParameters structure
	nPositionElement = SHARED_EXCHANGE_POSITION_NULL;
	cr = GTL_SharedExchange_FindNext (pAidParameters, &nPositionElement, TAG_EMV_TERMINAL_TYPE, &ulTerminalTypeLength, (const unsigned char **)&pTerminalType);
	if (cr != STATUS_SHARED_EXCHANGE_OK)
		return;	// Not found

	pTerminalType[0] = 0x00;	// international contactless transactions
}



//! \brief Get the timeout value for card detection process from the parameter file.
//! \param[out] pNoCardTimeOut the timeout value (in milliseconds).
//! \return
//!		- TRUE if tag is present.
//!		- FALSE else.

int SDSA_Interac_GetNoCardTimeOut (unsigned long *pNoCardTimeOut)
{
	TLV_TREE_NODE pTimeOut;		// Node for No Card Timeout.
	unsigned char * pValue;
	unsigned int nDataLength;

	pValue = NULL;
	nDataLength = 0;

	pTimeOut = TlvTree_Find(pTreeCurrentParam, TAG_SDSA_NO_CARD_TIMEOUT, 0);

	if (pTimeOut != NULL)
	{
		pValue = TlvTree_GetData(pTimeOut);
		nDataLength = TlvTree_GetLength(pTimeOut);
	}

	if ((pValue != NULL) && (nDataLength != 0))
	{
		GTL_Convert_BinNumberToUl(pValue, pNoCardTimeOut, nDataLength);
		return (TRUE);
	}

	return (FALSE);
}


//! \brief Check in the parameter file if the GUI mode to use is Interac GUI.

void SDSA_Interac_SetInteracGuiMode (void)
{
	TLV_TREE_NODE pGuiMode;
	unsigned char * pValue;
	unsigned int nDataLength;
	
	pValue = NULL;
	nDataLength = 0;

	pGuiMode = TlvTree_Find(pTreeCurrentParam, TAG_GENERIC_GUI_MODE, 0);

	if (pGuiMode != NULL)
	{
		pValue = TlvTree_GetData(pGuiMode);
		nDataLength = TlvTree_GetLength(pGuiMode);
	}

	if ((pValue != NULL) && (nDataLength != 0))
	{
		if (pValue[0] == CLESS_GUI_MODE_INTERAC)
		{
			gs_bIsInteracGuiMode = TRUE;
			return;
		}
	}

	gs_bIsInteracGuiMode = FALSE;
}

//! \brief Check if the Interac GUI mode is activated.
//!	\return
//!		- TRUE if Interac GUI mode is used.
//!		- FALSE else.

int SDSA_Interac_IsInteracGuiMode (void)
{
	return (gs_bIsInteracGuiMode);
}
