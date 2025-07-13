/**
 * \file
 * \brief Define the interface of the contactless DLL.
 *
 *
 * \author	Ingenico France
 * \author	Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico France has intellectual property rights relating to the technology embodied\n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico France.
 **/

#ifndef __CLESSINTERFACE_H__INCLUDED__
#define __CLESSINTERFACE_H__INCLUDED__



//! \addtogroup Contactless 
//! @{
//! \defgroup TPassApi Contactless API
//! @{

	//! \defgroup TPassLowLevel Low level features
	//! @{

		//! \defgroup TPassApiErrors Contactless DLL errors
		//! \defgroup TPassApiGeneral Contactless general API
		//! \defgroup TPassApiBacklight Contactless backlight management
		//! \defgroup TPassApiBuzzer Contactless buzzer management
		//! \defgroup TPassApiLeds Contactless LEDs management
		//! \defgroup TPassApiDisplay Contactless display management
		//! \defgroup TPassApiSams Contactless reader SAMs
		//! \defgroup TPassContactLess Contactless card management
		//! @{

			//! \defgroup TPassContactLessStd ISO14443-4 card management
			//! @{

				//! \defgroup TPassContactLessStdDriver Driver management
				//! \defgroup TPassContactLessStdDetection Card detection
				//! \defgroup TPassContactLessStdActivation Card activation
				//! \defgroup TPassContactLessStdCommands Commands
				//! \defgroup TPassContactLessStdDeselection Card deselection
				//! \defgroup TPassContactLessStdObsolete Obsolete functions

			//! @}

			//! \defgroup TPassContactLessMifare MIFARE card management
			//! @{

				//! \defgroup TPassContactLessMifareDriver Driver management
				//! \defgroup TPassContactLessMifareDetection Card detection
				//! \defgroup TPassContactLessMifareActivation Card activation
				//! \defgroup TPassContactLessMifareBlockOperations Blocks and sectors operations
				//! \defgroup TPassContactLessMifareObsolete Obsolete functions

			//! @}

			//! \defgroup TPassContactLessStm STMicroelectronics card management
			//! @{

				//! \defgroup TPassContactLessStmDriver Driver management
				//! \defgroup TPassContactLessStmDetection Card detection
				//! \defgroup TPassContactLessStmDeactivation Card deactivation
				//! \defgroup TPassContactLessStmMemoryOperations Memory operations

			//! @}

			//! \defgroup TPassContactLessCalypso Innovatron Calypso card management
			//! @{

				//! \defgroup TPassContactLessCalypsoDriver Driver management
				//! \defgroup TPassContactLessCalypsoDetection Card detection
				//! \defgroup TPassContactLessCalypsoDisconnection Disconnect card
				//! \defgroup TPassContactLessCalypsoCommands Commands

			//! @}

			//! \defgroup TPassContactLessCts ASK CTS card management
			//! @{

				//! \defgroup TPassContactLessCtsDriver Driver management
				//! \defgroup TPassContactLessCtsCardDetection Card detection
				//! \defgroup TPassContactLessCtsMemoryOperations Memory operations

			//! @}

		//! @}

		//! \defgroup TPassTeliumPassVendingPass TeliumPass and Vending Pass specific functions
		//! @{

			//! \defgroup TPassComponents Contactless components
			//! \defgroup TPassCapabilities Contactless hardware and software capabilities

		//! @}

	//! @}

	//! \defgroup ClessHighLevel High level features
	//! @{

		//! \defgroup ClessGenericStatusCodes Status codes
		//! \defgroup ClessGenericTags Contactless generic tags
		//! @{

			//! \defgroup ClessGenericTagsCallingMode Values for TAG_GENERIC_DATA_CALLING_MODE
			//! \defgroup ClessGenericTagsSelectionMethod Values for TAG_GENERIC_APPLIED_METHOD
			//! \defgroup ClessGenericTagsDetectionType Values for TAG_GENERIC_DETECTION_TYPE
			//! \defgroup ClessGenericTagsDetectionResults Values for TAG_GENERIC_DETECTION_RESULT
			//! \defgroup ClessErrorCodes Values for TAG_GENERIC_ERROR_INFORMATION
			//! \defgroup ClessImplicitMessageCustomisation Values for TAG_GENERIC_MANAGER_MESSAGE_TO_DISPLAY
			//! \defgroup ClessGenericIdleCause Values for TAG_GENERIC_CUST_GUI_IDLE_CAUSE

		//! @}

		//! \defgroup ClessGenericSelection Common features
		//! @{

			//! \defgroup ClessGenericSelectionEntryPoint Entry Point
			// @{

				//! \defgroup EntryPointNewOption9F2AAndNewPreProcessing New features (management of 9F2A and pre processing)
				//!	\defgroup ClessGenericSelectionEntryPointFunctions Entry Point functions
				
			//! @}
			//! \defgroup ClessGenericSelectionDetect Card detection
			//! \defgroup ClessGenericSelectionAppSelection Application selection
			//! @{

				//! \defgroup ClessGenericSelectionFlow Application selection processing (flow)
				//! \defgroup ClessGenericSelectionAppSelectionFunctions Generic functions

			//! @}

			//! \defgroup GenericParametersFormat Generic Card Detection and Application Selection parameters
			//! \defgroup ClessGenericCustomisation Possible customisation
			//! @{

				//! \defgroup ClessGenericCustomisationGui GUI customisation
				//! @{
					
					//! \defgroup ClessGenericCustomisationFunction Generic Customisation Functions
					//! \defgroup ClessGenericCustomisationDefaultGui Default GUI modes
					//! \defgroup ClessGenericCustomisationGuiSteps Existing GUI steps

				//! @}

				//! \defgroup ClessGenericCustomisationAsProc Application Selection Processing customisation
				//!	@{

					//! \defgroup ClessGenericCustomisationAppliSelectionProcessingSteps Application Selection result customisation steps

				//!	@}

				//! \defgroup ClessGenericCustomisationStatusCodes Customisation possible returns

			//!	@}

		//! @}

		//! \defgroup ClessExplicitSelection Explicit selection (card detection and selection performed by the application)
		//! @{

			//! \defgroup ClessExplicitSelectionLoadData Setting card detection and selection parameters (explicit selection)
			//! \defgroup ClessExplicitCustom Customisation (explicit selection) : GUI, application selection results.
			//! \defgroup ClessExplicitSelectionPreprocessing EMVCo Entry Point pre-conditions and pre-processing (explicit selection)
			//! \defgroup ClessExplicitSelectionDetection Card detection (explicit selection)
			//! \defgroup ClessExplicitSelectionClearData Clear Global Data (explicit selection)
			//! \defgroup ClessExplicitSelectionAppSelection Application selection (explicit selection)
			//! @{

				//! \defgroup ClessExplicitSelectionAppSelectionAdvanced Advanced application selection (explicit selection)

			//! @}

		//! @}

		//! \defgroup ClessImplicitSelection Implicit Selection
		//! @{

			//! \defgroup ClessImplicitOverview Mechanism overview (implicit selection)
			//! \defgroup ClessImplicitGiveInfo CLESS_GIVE_INFO : Setting card detection and selection parameters (implicit selection)
			//! \defgroup ClessImplicitDebitAid CLESS_DEBIT_AID : Perform a transaction with an AID method (implicit selection)
			//! \defgroup ClessImplicitDebit CLESS_DEBIT : Perform a transaction with other method than AID (implicit selection)
			//! \defgroup ClessImplicitIsForYou CLESS_IS_FOR_YOU : Manage specific cards (implicit selection)
			//! \defgroup ClessImplicitEnd CLESS_END : Processing when transaction has been completed (implicit selection)
			//! \defgroup ClessImplicitCustomisation Possible customisation (implicit selection)
			//! @{

				//! \defgroup ClessImplicitCustomisationServices Customisation Services (implicit selection)
				//! \defgroup ClessImplicitCustomisationGui GUI Customisation (implicit selection)
				//! \defgroup ClessImplicitCustomisationAsProc Application Selection result processing customisation (implicit selection)

			//! @}

			//! \defgroup ClessImplicitReturnCode Implicit Selection return codes

		//! @}

	//! @}

//! @}


//! \defgroup EntryPointDefines Entry Point Defines
//! @{

	//! \defgroup TagsDefinitions Tags definition
	//! @{

		//! \defgroup EntryPointDefinedTags Entry Point defined tags (defined by EMVCo).
		//! \defgroup EntryPointInternalDefinition Entry Point Ingenico created tags.
		//! @{

			//! \defgroup EntryPointPossibleKernels Entry Point Kernel identifiers (values for tag TAG_EP_KERNEL_TO_USE).
			//! \defgroup EntryPointErrorCodes Values for TAG_EP_ERROR_INFORMATION

		//! @}

	//! @}

	//! \defgroup EntryPoint_ExternalTypes Entry Point external types

//! @}


//! \defgroup EmvDefines EMV Defines
//! @{

	//! \defgroup EmvTags Tags Definition
	//! @{

		//! \defgroup EmvDefinedTags EMV defined tags
		//! \defgroup EmvInternalDefinition EMV internal tags

	//! @}

	//! \defgroup EmvDefinitions Defines
	//! @{

		//! \defgroup AidInfiormation EMV AID information
		//! \defgroup TransactionTypes Transaction Types (internal define)
		//! \defgroup GenAcRefControlParameters EMV Generate AC Reference Control Parameter
		//! \defgroup EmvLib_Cvr CVR data management
		//! @{

			//! \defgroup CvrBytesIdentifiers CVR Bytes identifiers
			//! \defgroup CvrRulesDefinition CVM Rules definitions
			//! \defgroup CvrConditionsDefinition CVM Conditions definitions
			//! \defgroup CvrResultsDefinition CVM Results definitions
			//! \defgroup CvrMiscellaneousDefinfion Miscellaneous definitions

		//! @}

		//! \defgroup EmvLibTerminalTypes EMV Terminal Types.

	//! @}

//! @}

//! @}


/////////////////////////////////////////////////////////////////
//// Include ////////////////////////////////////////////////////

#include "Cless_Generic_StatusCodes.h"
#include "Cless_Generic_Tags.h"

#include "Cless_LowLevel.h"
#include "Cless_HighLevel.h"

#endif // __CLESSINTERFACE_H__INCLUDED__
