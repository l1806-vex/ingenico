/**
 * \file
 * \brief Define all the generic contactless tags. This concerns all the generic tags, available for custom applications, to perform card detection and application selection.
 * \brief It can also be used by contactless kernels themselves.
 *
 *
 * \author Ingenico
 * \author Copyright (c) 2009 Ingenico, 1 rue claude Chappe,\n
 *		   07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __CLESS_GENERIC_TAGS_H__INCLUDED__
#define __CLESS_GENERIC_TAGS_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup ClessGenericTags
//! @{

#define TAG_GENERIC_APPLICATION_TYPE				0x9F928201		/*!< Indicates the application type which provided the AID for Entry Point.<br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal. */
#define TAG_GENERIC_AID_PROPRIETARY_IDENTIFIER		0x9F928202		/*!< Indicates the proprietary identifier of a given AID (to differentiate an AID configuration according to specific parameters).<br>	- Format : b.<br>	- Length : 4 bytes.<br>	- Source : Terminal. */
#define TAG_GENERIC_DATA_CALLING_MODE				0x9F928203		/*!< Indicates the way to communicate with the application. See \ref ClessGenericTagsCallingMode.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */

//! @}


//! \addtogroup ClessGenericTagsCallingMode
//! @{

#define GENERIC_DATA_CALLING_MODE_NONE				0x00			/*!< Way to communicate is not yet determined. */
#define GENERIC_DATA_CALLING_MODE_DEL				0x01			/*!< Way to communicate is DEL. */
#define GENERIC_DATA_CALLING_MODE_SHARED_TLV		0x02			/*!< Way to communicate is a buffer in shared memory providing the buffer address only. */
#define GENERIC_DATA_CALLING_MODE_TLV				0x03			/*!< Way to communicate is a full buffer containing all the data (for simulation only). */

//! @}


//! \addtogroup ClessGenericTags
//! @{

#define TAG_GENERIC_ERROR_INFORMATION				0x9F928204		/*!< Contains the error codes information about the processing. This consists of a concatenation of error codes. Each error code is coded on 8 bytes :<br>	- The four first bytes represent the error code identifier (please refer to \ref ClessErrorCodes for more information).<br>	- The four last bytes indicate the related tag (if applicable), else, it is filled with 0xFFFFFFFF.<br><br>	- Format : b.<br>	- Length : 8 to 128 bytes.<br>	- Source : Terminal. */
#define TAG_GENERIC_APPLIED_METHOD					0x9F928205		/*!< Indicates the applied application selection method. See \ref ClessGenericTagsSelectionMethod.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */

//! @}


//! \addtogroup ClessGenericTagsSelectionMethod
//! @{

#define GENERIC_METHOD_APDU_BEFORE					0x01			/*!< Application Selection method - APDU Before method. */
#define GENERIC_METHOD_PPSE							0x02			/*!< Application Selection method - PPSE method. */
#define GENERIC_METHOD_LOA							0x03			/*!< Application Selection method - List Of AID method. */
#define GENERIC_METHOD_APDU_AFTER					0x04			/*!< Application Selection method - APDU After method. */

//! \cond NOT_DOCUMENTED
#define GENERIC_METHOD_PROPRIETARY					0x05			/*!< Application Selection method - Proprietary method (DO NOT USE). */
//! \endcond

//! @}


//! \addtogroup ClessGenericTags
//! @{

#define TAG_GENERIC_DETECTION_TYPE					0x9F928210		/*!< DETECTION - Card detection type. See \ref ClessGenericTagsDetectionType.<br>	- Format : b.<br>	- Length : 4 bytes.<br>	- Source : Terminal. */

//! @}


//! \addtogroup ClessGenericTagsDetectionType
//! @{

#define DETECTION_BYTE_ISO_A						0				/*!< DETECTION - Byte for bit indicating ISO 14443-4 Type A is supported (first byte). */
#define DETECTION_BYTE_ISO_B						0				/*!< DETECTION - Byte for bit indicating ISO 14443-4 Type B is supported (first byte). */
#define DETECTION_BYTE_ISO_BB						0				/*!< DETECTION - Byte for bit indicating ISO 14443-4 Type BB is supported (first byte). */
#define DETECTION_BYTE_MIFARE_A						0				/*!< DETECTION - Byte for bit indicating ISO 14443 Mifare Type A is supported (first byte). */
#define DETECTION_BYTE_STM							0				/*!< DETECTION - Byte for bit indicating ISO 14443 STM  is supported (first byte). */
#define DETECTION_BYTE_FELICA						0				/*!< DETECTION - Byte for bit indicating Felica is supported (first byte). */
#define DETECTION_BYTE_MIFARE_ULTRA_LIGHT_A			0				/*!< DETECTION - Byte for bit indicating ISO 14443 Mifare Ultra Light Type A is supported (first byte). */
#define DETECTION_BYTE_CALYPSO_B_PRIME				0				/*!< DETECTION - Byte for bit indicating Innovatron Clypso B prime is supported (first byte). */
#define DETECTION_BYTE_MIFARE_4K_A					1				/*!< DETECTION - Byte for bit indicating ISO 14443 Mifare 4K Type A is supported (second byte). */

#define DETECTION_BYTE_STM_B						DETECTION_BYTE_STM	/*!< DETECTION - For compatibillity. */

#define DETECTION_MASK_ISO_A						0x01			/*!< DETECTION - Mask indicating ISO 14443-4 Type A is supported (first byte). */
#define DETECTION_MASK_ISO_B						0x02			/*!< DETECTION - Mask indicating ISO 14443-4 Type B is supported (first byte). */
#define DETECTION_MASK_ISO_BB						0x04			/*!< DETECTION - Mask indicating ISO 14443-4 Type BB is supported (first byte). */
#define DETECTION_MASK_MIFARE_A						0x08			/*!< DETECTION - Mask indicating ISO 14443 Mifare Type A is supported (first byte). */
#define DETECTION_MASK_STM							0x10			/*!< DETECTION - Mask indicating ISO 14443 STM is supported (first byte). */
#define DETECTION_MASK_FELICA						0x20			/*!< DETECTION - Mask indicating Felica is supported (first byte). */
#define DETECTION_MASK_MIFARE_ULTRA_LIGHT_A			0x40			/*!< DETECTION - Mask indicating ISO 14443 Mifare Ultra Light Type A is supported (first byte). */
#define DETECTION_MASK_CALYPSO_B_PRIME				0x80			/*!< DETECTION - Mask indicating Innovatron Calypso B prime is supported (first byte). */
#define DETECTION_MASK_MIFARE_4K_A					0x01			/*!< DETECTION - Mask indicating ISO 14443 Mifare 4K Type A is supported (second byte). */

#define DETECTION_MASK_STM_B						DETECTION_MASK_STM	/*!< DETECTION - For compatibillity. */

//! @}


//! \addtogroup ClessGenericTags
//! @{

#define TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT		0x9F928212		/*!< DETECTION - Card detection global timeout.<br>	- Format : b.<br>	- Length : 4 bytes.<br>	- Source : Terminal. */
#define TAG_GENERIC_DETECTION_LOCAL_TIMEOUT			0x9F928213		/*!< DETECTION - Card detection local timeout.<br>	- Format : b.<br>	- Length : 4 bytes.<br>	- Source : Terminal. */
#define TAG_GENERIC_DETECTION_NB_CARDS_TO_DETECT	0x9F928214		/*!< DETECTION - Maximum number of card that can be detected.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_GENERIC_DETECTION_RESULT				0x9F928215		/*!< DETECTION - Card detection result. See \ref ClessGenericTagsDetectionResults.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */

//! @}


//! \addtogroup ClessGenericTagsDetectionResults
//! @{

#define DETECT_RESULT_OK							0xF1			/*!< DETECTION - Detection result indicating card correctly detected and activated. */
#define DETECT_RESULT_COLLISION						0xF2			/*!< DETECTION - Detection result indicating card collision. */
#define DETECT_RESULT_GLOBAL_TO						0xF3			/*!< DETECTION - Detection result indicating global timeout has been reached. */
#define DETECT_RESULT_LOCAL_TO						0xF4			/*!< DETECTION - Detection result indicating local timeout has been reached. */
#define DETECT_RESULT_CANCEL						0xF5			/*!< DETECTION - Detection result indicating detection has been cancelled. */
#define DETECT_RESULT_ERROR							0xF6			/*!< DETECTION - Detection result indicating an error occurred during the card detection. */
#define DETECT_RESULT_RETRY_FROM_APPLICATION		0xF7			/*!< DETECTION - Status indicating the transaction will be restarted based on the application result (depending on the transaction and not on the detection itself, i.e. after the card detection). */

//! @}


//! \addtogroup ClessGenericTags
//! @{

#define TAG_GENERIC_DETECTED_CARD_TYPE				0x9F928217		/*!< DETECTION - Indicates the type of the detected card (ISO, Mifare, Felica, STM or Unknown).<br>	- Format : b.<br>	- Length : 4 bytes.<br>	- Source : Terminal. */

//! \cond NOT_DOCUMENTED
#define TAG_GENERIC_LEVEL_1_ERROR					0x9F928219		/*!< DETECTION - Level 1 error code (DO NOT USE). */
//! \endcond

#define TAG_GENERIC_APPLICATION_SELECTION_RESULT	0x9F92821A		/*!< Application Selection - Indicates the Application selection result (used for application selection post processing).<br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal. */

#define TAG_GENERIC_APDU_COMMAND_TO_SEND			0x9F928220		/*!< APDU METHOD - Command to be sent to the contactless card.<br>	- Format : b.<br>	- Length : var. up to 261 bytes.<br>	- Source : Terminal. */
#define TAG_GENERIC_APDU_EXPECTED_STATUS_WORD		0x9F928221		/*!< APDU METHOD - Expected status word from the contactless card to the sent command.<br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal. */
#define TAG_GENERIC_APDU_EXPECTED_CARD_RESPONSE		0x9F928222		/*!< APDU METHOD - Expected response from the contactless card to the send command.<br>	- Format : b.<br>	- Length : var. up to 257 bytes.<br>	- Source : Terminal. */		
#define TAG_GENERIC_APDU_RESPONSE_MASK				0x9F928223		/*!< APDU METHOD - Mask applied on the expected response (if only partial response only matches).<br>	- Format : b.<br>	- Length : var. up to 257 bytes.<br>	- Source : Terminal. */

/*! \brief APDU METHOD - APDU options :
- Byte 1 :
	- Bit 1 : APDU Before (0) / After (1)
	- Bit 2 : Proprietary application selection allowed or not (currently not used).
	- Bits 3 to 8 : RFU.
- Byte 2 : Priority Level.
- Bytes 3 to 4 : RFU.
*/
#define TAG_GENERIC_APDU_OPTIONS					0x9F928224

#define TAG_GENERIC_APDU_CARD_RESPONSE				0x9F928225		/*!< APDU METHOD - Card response according to the sent APDU.<br>	- Format : b.<br>	- Length : var. up to 257 bytes.<br>	- Source : Terminal. */
#define TAG_GENERIC_APDU_CARD_STATUS_WORD			0x9F928226		/*!< APDU METHOD - Card response status word according to the sent command.<br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal. */

#define TAG_GENERIC_DEBUG_ACTIVATION				0x9F928227    	/*!< Indicates the debug mode to use.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define DEBUG_MASK_TRACES						    0x01		    /*!< Mask for \a TAG_EP_DEBUG_ACTIVATION tag indicating traces are activated. */
#define DEBUG_MASK_APDU	                            0x02		    /*!< Mask for \a TAG_EP_DEBUG_ACTIVATION tag indicating APDU exchanged between card and reader are stored or not in the database. */

#define TAG_GENERIC_GUI_MODE						0x9F928230		/*!< DETECTION - GUI mode.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */

//! @}


//! \addtogroup ClessGenericCustomisationDefaultGui
//! @{

#define CLESS_GUI_MODE_NONE									(0)		/*!< Contactless GUI mode : No GUI. */
#define CLESS_GUI_MODE_MASTERCARD							(1)		/*!< Contactless GUI mode : Standard MasterCard GUI mode. */
#define CLESS_GUI_MODE_VISA_EUROPE							(2)		/*!< Contactless GUI mode : Standard Visa GUI mode. */
#define CLESS_GUI_MODE_VISA_ASIA							(3)		/*!< Contactless GUI mode : Standard Visa Asia GUI mode (with coloured LEDs). */
#define CLESS_GUI_MODE_MASTERCARD_COLORED_LEDS				(4)		/*!< Contactless GUI mode : Standard MasterCard GUI mode (with coloured LEDs). */
#define CLESS_GUI_MODE_INTERAC								(5)		/*!< Contactless GUI mode : Standard Interac GUI mode. */
#define CLESS_GUI_MODE_DISCOVER								(6)		/*!< Contactless GUI mode : Standard Discover GUI mode. */

//! @}


//! \addtogroup ClessGenericTags
//! @{

#define TAG_GENERIC_CUST_STEPS_TO_CUSTOMISE			0x9F928231		/*!< CUSTOMISATION PROCESSING - Bit field (on 8 bytes) indicating which steps can be customised.<br>	- Format : b.<br>	- Length : 8 bytes.<br>	- Source : Terminal. */
#define TAG_GENERIC_CUST_STEP_ID					0x9F928232		/*!< CUSTOMISATION PROCESSING - Bit field containing the step to be customised.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_GENERIC_MANAGER_MESSAGE_TO_DISPLAY		0x9F928233		/*!< CUSTOMISATION PROCESSING - Tag that can be used to change the message displayed on the following GUI customisation steps :<br>	- \ref CLESS_CUST_GUI_PRESENT_CARD_AMOUNT_STEP_ID<br>	- \ref CLESS_CUST_GUI_RETRY_AMOUNT_STEP_ID<br>	- \ref CLESS_CUST_GUI_DOUBLE_TAP_STEP_ID<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_GENERIC_CUST_GUI_IDLE_CAUSE 			0x9F928234		/*!< CUSTOMISATION PROCESSING - Tag that specify the reason why we comes in CLESS_CUST_GUI_IDLE_STEP_ID step. See \ref ClessGenericIdleCause.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */

//! @}


//!\addtogroup ClessImplicitMessageCustomisation
//! @{

#define CLESS_CUST_MANAGER_MESS_PRESENT_CARD		(255)			/*!< Possible value for \ref TAG_GENERIC_MANAGER_MESSAGE_TO_DISPLAY tag. It indicates the "Present card" message shall be displayed. */
#define CLESS_CUST_MANAGER_MESS_TRY_AGAIN			(249)			/*!< Possible value for \ref TAG_GENERIC_MANAGER_MESSAGE_TO_DISPLAY tag. It indicates the "Try Again" message shall be displayed. */
#define CLESS_CUST_MANAGER_MESS_NONE				(248)			/*!< Possible value for \ref TAG_GENERIC_MANAGER_MESSAGE_TO_DISPLAY tag. It indicates that no message shall be displayed. */
#define CLESS_CUST_MANAGER_MESS_DOUBLE_TAP			(247)			/*!< Possible value for \ref TAG_GENERIC_MANAGER_MESSAGE_TO_DISPLAY tag. It indicates the "Present Mobile" message shall be displayed. */

//! @}


//! \addtogroup ClessGenericCustomisationGuiSteps
//! @{

#define CLESS_CUST_GUI_REGISTRATION_STEP_ID					(1)		/*!< Generic GUI step - Registration. */
#define CLESS_CUST_GUI_IDLE_STEP_ID							(3)		/*!< Generic GUI step - Idle state. */
#define CLESS_CUST_GUI_PRESENT_CARD_AMOUNT_STEP_ID			(4)		/*!< Generic GUI step - The contactless reader is waiting for a card (amount is provided). */
#define CLESS_CUST_GUI_PRESENT_CARD_NO_AMOUNT_STEP_ID		(5)		/*!< Generic GUI step - The contactless reader is waiting for a card (amount is not provided). */
#define CLESS_CUST_GUI_RETRY_AMOUNT_STEP_ID					(6)		/*!< Generic GUI step - The card shall be presented again on the reader (amount is present). */
#define CLESS_CUST_GUI_RETRY_NO_AMOUNT_STEP_ID				(7)		/*!< Generic GUI step - The card shall be presented again on the reader (amount is not present). */
#define CLESS_CUST_GUI_COLLISION_STEP_ID					(12)	/*!< Generic GUI step - Indicates to the cardholder there are too many cards within the contactless field. */
#define CLESS_CUST_GUI_USE_CONTACT_STEP_ID					(13)	/*!< Generic GUI step - Indicates transaction shall be conducted over another interface. */
#define CLESS_CUST_GUI_CARD_NOT_SUPPORTED_STEP_ID			(15)	/*!< Generic GUI step - The presented card is not supported by the system. */
#define CLESS_CUST_GUI_DOUBLE_TAP_STEP_ID					(19)	/*!< Generic GUI step - The double tap is required (card / phone shall be presented again to perform the transaction). */
#define CLESS_CUST_GUI_USE_CONTACT_CHIP_STEP_ID				(20)	/*!< Generic GUI step - Indicates transaction shall be conducted only on chip mode. */
#define CLESS_CUST_GUI_USE_CONTACT_SWIPE_STEP_ID			(21)	/*!< Generic GUI step - Indicates transaction shall be conducted only on swipe mode. */

//! @}

//! \addtogroup ClessGenericIdleCause
//! @{
#define CLESS_CUST_IDLE_STEP							    (0)		/*!< Generic GUI step - Idle state without reason..... */
#define CLESS_CUST_IDLE_INIT					            (1)     /*!< Idle state due to Initialisation. */
#define CLESS_CUST_IDLE_TIMEOUT					            (2)     /*!< Idle state due to Timeout. */
#define CLESS_CUST_IDLE_CANCEL          					(3)     /*!< Idle state due to Cancel key. */
#define CLESS_CUST_IDLE_CHIP            					(4)     /*!< Idle state due to chip card inserted. */
#define CLESS_CUST_IDLE_SWIPE               				(5)     /*!< Idle state due to magnetic card swipped. */
#define CLESS_CUST_IDLE_MANUAL_TRANSACTION          		(6)     /*!< Idle state due to a manual transaction. */
#define CLESS_CUST_IDLE_ABORT                  				(7) 	/*!< Idle state due to a transaction aborted. */
#define CLESS_CUST_TRANSACTION_ERROR           				(8) 	/*!< Idle state due to a transaction error. */
#define CLESS_CUST_IDLE_CHECK                  				(9) 	/*!< Idle state due to a user request for check. */
#define CLESS_CUST_IDLE_CASH_REGISTER                  		(10) 	/*!< Idle state due to a cash register message. */
#define CLESS_CUST_IDLE_RESTART_WITHOUT_CLESS               (11) 	/*!< Idle state due to a transaction restart without Cless. */
//! @}

//! \cond NOT_DOCUMENTED
#define CLESS_CUST_GUI_NOT_WORKING_STEP_ID					(2)		/*!< DO NOT USE */
#define CLESS_CUST_GUI_PRESENT_ONE_CARD_AMOUNT_STEP_ID		(8)		/*!< DO NOT USE */
#define CLESS_CUST_GUI_PRESENT_ONE_CARD_NO_AMOUNT_STEP_ID	(9)		/*!< DO NOT USE */
#define CLESS_CUST_GUI_CARD_DETECTED_STEP_ID				(10)	/*!< DO NOT USE */
#define CLESS_CUST_GUI_CARD_DETECTED_WITH_ERROR_STEP_ID		(11)	/*!< DO NOT USE */
#define CLESS_CUST_GUI_INVALID_CARD_STEP_ID					(14)	/*!< DO NOT USE */
#define CLESS_CUST_GUI_NO_CARD_STEP_ID						(16)	/*!< DO NOT USE */
#define CLESS_CUST_GUI_REMOVE_CARD_STEP_ID					(17)	/*!< DO NOT USE */
#define CLESS_CUST_GUI_INTERNAL_ERROR_STEP_ID				(18)	/*!< DO NOT USE */
//! \endcond

//! @}


//! \addtogroup ClessGenericCustomisationAppliSelectionProcessingSteps
//! @{

#define CLESS_CUST_AS_PROC_REGISTRATION_STEP_ID				(1)		/*!< Implicit Selection only : Registration step for Application Selection result customisation. */
#define CLESS_CUST_AS_PROC_STEP_APDU_BEFORE_STEP_ID			(2)		/*!< Implicit Selection only : Step to customise APDU Before method result. */
#define CLESS_CUST_AS_PROC_STEP_PPSE_STEP_ID				(3)		/*!< Implicit Selection only : Step to customise PPSE method result. */
#define CLESS_CUST_AS_PROC_STEP_LIST_OF_AID_STEP_ID			(4)		/*!< Implicit Selection only : Step to customise List Of AID method result. */
#define CLESS_CUST_AS_PROC_STEP_APDU_AFTER_STEP_ID			(5)		/*!< Implicit Selection only : Step to customise APDU After method result. */
#define CLESS_CUST_AS_PROC_STEP_CLESS_IS_FOR_YOU_STEP_ID	(6)		/*!< Implicit Selection only : Step to customise CLESS_IS_FOR_YOU method result. Useless as \a CLESS_IS_FOR_YOU service is not yet implemented. */
#define CLESS_CUST_AS_PROC_STEP_END_STEP_ID					(7)		/*!< Implicit Selection only : Step to customise application selection result in case an error occurred or no method matched (when all the method have been applied). */

//! @}


//! \cond NOT_DOCUMENTED

//! \addtogroup ClessGenericCustomisationDetectProcessingSteps
//! @{

#define CLESS_CUST_DETECT_PROC_REGISTRATION_STEP_ID			(1)		/*!< DO NOT USE - Registration step for card detection result customisation. */
#define CLESS_CUST_DETECT_PROC_DETECTION_BEFORE_STEP_ID		(2)		/*!< DO NOT USE - Step to customise card detection before the card detection performed by the DLL. */
#define CLESS_CUST_DETECT_PROC_DETECTION_AFTER_STEP_ID		(3)		/*!< DO NOT USE - Step to customise card detection result (after card detection has been performed). */
#define CLESS_CUST_DETECT_PROC_PREPARE_RETRY_APPLI_STEP_ID	(4)		/*!< DO NOT USE - Step to customise the local timeout if a retry is requested after the card detection. */
#define CLESS_CUST_DETECT_PROC_RESTART_DOUBLE_TAP			(5)		/*!< DO NOT USE - Step to customise the restart for double tap. */

//! @}

//! \endcond


//! \cond NOT_DOCUMENTED

//! \addtogroup ClessGenericCustomisationDetection
//! @{

#define CLESS_CUST_DETECT_PERF_REGISTRATION_STEP_ID			(1)		/*!< DO NOT USE - Implicit Selection : Registration step for card detection itself customisation. */
#define CLESS_CUST_DETECT_PERF_PERFORM_DETECTION			(2)		/*!< DO NOT USE - Implicit Selection : Step to customise the card detection itself (the called application has to perform the card detection). */
#define CLESS_CUST_DETECT_PERF_CANCEL_DETECTION				(3)		/*!< DO NOT USE - Implicit Selection : Step called when the card detection has to be cancelled. */

//! @}

//! \endcond


//! \cond NOT_DOCUMENTED

//! \addtogroup ClessGenericCustomisationAppliSelectionSteps
//! @{

#define CLESS_CUST_AS_PERF_REGISTRATION_STEP_ID				(1)		/*!< DO NOT USE - Implicit Selection : Registration step for Application Selection itself customisation. */
#define CLESS_CUST_AS_PERF_STEP_1_STEP_ID					(2)		/*!< DO NOT USE - Implicit Selection : Step to perform application selection customisation (itself) before (or instead) APDU before method. */
#define CLESS_CUST_AS_PERF_STEP_2_STEP_ID					(3)		/*!< DO NOT USE - Implicit Selection : Step to perform application selection customisation (itself) before (or instead) PPSE method. */
#define CLESS_CUST_AS_PERF_STEP_3_STEP_ID					(4)		/*!< DO NOT USE - Implicit Selection : Step to perform application selection customisation (itself) before (or instead) List Of AID method. */
#define CLESS_CUST_AS_PERF_STEP_4_STEP_ID					(5)		/*!< DO NOT USE - Implicit Selection : Step to perform application selection customisation (itself) before (or instead) APDU After method. */
#define CLESS_CUST_AS_PERF_STEP_5_STEP_ID					(6)		/*!< DO NOT USE - Implicit Selection : Step to perform application selection customisation (itself) after all the applied methods. */

//! @}

//! \endcond


//! \addtogroup ClessGenericTags
//! @{

#define TAG_GENERIC_MANAGER_AMOUNT_ENTRY			0x9F928240		/*!< MANAGER - Tag indicating if the amount has been entered or not (extracted from S_TRANSIN).<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_GENERIC_MANAGER_TRANSACTION_TYPE		0x9F928241		/*!< MANAGER - Tag indicating the transaction type (extracted from S_TRANSIN).<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_GENERIC_MANAGER_CURRENCY_LABEL			0x9F928242		/*!< MANAGER - Tag indicating the currency label (extracted from S_TRANSIN).<br>	- Format : ans.<br>	- Length : 3 bytes.<br>	- Source : Terminal. */
#define TAG_GENERIC_MANAGER_CASH_REGISTER_NUMBER	0x9F928243		/*!< MANAGER - Tag indicating the cash register number (extracted from S_TRANSIN).<br>	- Format : an.<br>	- Length : 2 bytes.<br>	- Source : Terminal. */
#define TAG_GENERIC_MANAGER_STRANSOUT_NOAPPLI		0x9F928244		/*!< MANAGER - Tag indicating the application number, as indicated in the S_TRANSOUT structure (member "noappli"). This could be returned in the CLESS_DEBIT or CLESS_DEBIT_AID structure to fill the S_TRANSOUT structure.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br> Note if the returned value has a length different from 1 byte, this one will be ignored. */
#define TAG_GENERIC_MANAGER_STRANSOUT_RC_PAYMENT	0x9F928245		/*!< MANAGER - Tag indicating the paiement result for the cash register, as indicated in the S_TRANSOUT structure (member "rc_payment"). This could be returned in the CLESS_DEBIT or CLESS_DEBIT_AID structure to fill the S_TRANSOUT structure. The possible values are :<br>	- /a PAIEM_OK (0)<br>	- \a PAIEM_KO (1)<br>	- \a PAIEM_AUTRE_AID (2)<br>	- \a PAIEM_EN_COURS (3)<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br> Note if the returned value has a length different from 1 byte, this one will be ignored. */
#define TAG_GENERIC_MANAGER_STRANSOUT_CARDHOLDER_NB	0x9F928246		/*!< MANAGER - Tag indicating the cardholder number, as indicated in the S_TRANSOUT structure (member "card_holder_nb"). This could be returned in the CLESS_DEBIT or CLESS_DEBIT_AID structure to fill the S_TRANSOUT structure.<br>	- Format : an.<br>	- Length : up to 19 byte.<br>	- Source : Terminal.<br> */

#define TAG_GENERIC_PRIORITY						0x9F928250		/*!< CLESS_IS_FOR_YOU - Priority for CLESS_IS_FOR_YOU service.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */

#define TAG_GENERIC_APDU_INFORMATION				0xBF928200		/*!< APDU METHOD - APDU structure (After or before). Refer to \ref GenericParametersFormat for more information about the structure content. */
#define TAG_GENERIC_CARD_INFORMATION				0xBF928201		/*!< DETECTION - Detected card information. */

//! @}



#endif // __CLESS_GENERIC_TAGS_H__INCLUDED__
