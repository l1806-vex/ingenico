/**
 * \file
 * \brief Define all the DLL status codes.
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

#ifndef __CLESS_STATUS_CODES_H__INCLUDED__
#define __CLESS_STATUS_CODES_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup ClessGenericStatusCodes
//! @{

#define CLESS_STATUS_OK										0x0A00		/*!< STATUS CODE - Processing is correctly completed. */
#define CLESS_STATUS_KO										0x0A01		/*!< STATUS CODE - An internal error occurred. */
#define CLESS_STATUS_MISSING_PARAM							0x0A02		/*!< STATUS CODE - An input parameter for this service is missing. */
#define CLESS_STATUS_NO_MATCHING_AID						0x0A03		/*!< STATUS CODE - There is no matching AID (no AID in the candidate list). */
#define CLESS_STATUS_CARD_BLOCKED							0x0A04		/*!< STATUS CODE - The processing is terminated because the card is blocked (0x6A81). */
#define CLESS_STATUS_APPLICATION_BLOCKED					0x0A05		/*!< STATUS CODE - The processing is terminated because the application is blocked (0x6283). */
#define CLESS_STATUS_LACK_OF_MEMORY							0x0A06		/*!< STATUS CODE - There is not enough memory to complete the processing. */
#define CLESS_STATUS_INVALID_PARAM							0x0A07		/*!< STATUS CODE - An input parameter is not valid. */
#define CLESS_STATUS_DATABASE_ERROR							0x0A08		/*!< STATUS CODE - An error occurred during the service processing. */
#define CLESS_STATUS_COMMUNICATION_ERROR					0x0A09		/*!< STATUS CODE - A communication error occurred between the reader and the card. */
#define CLESS_STATUS_NOT_FOUND								0x0A0A		/*!< STATUS CODE - If data requested (Candidate list or card responses) cannot be found. */
#define CLESS_STATUS_MISSING_ICC_DATA						0x0A0B		/*!< STATUS CODE - An ICC mandatory card is missing. */
#define CLESS_STATUS_MISSING_TERM_DATA						0x0A0C		/*!< STATUS CODE - A mandatory terminal data is missing. */
#define CLESS_STATUS_ICC_FORMAT_ERROR						0x0A0D		/*!< STATUS CODE - The card data is not correctly formatted. */
#define CLESS_STATUS_ICC_REDUNDANT_DATA						0x0A0E		/*!< STATUS CODE - The card has a redundant data. */
#define CLESS_STATUS_UNKNOWN_TAG							0x0A0F		/*!< STATUS CODE - The requested tag is not known by the PPSE Application Selection module. */
#define CLESS_STATUS_UN_GENERATION_FAILED					0x0A10		/*!< STATUS CODE - The random number generation to be performed during pre conditions step failed. */
#define CLESS_STATUS_INTERNAL_ERROR							0x0A11		/*!< STATUS CODE - Indicates an internal error. */
#define CLESS_STATUS_BAD_PPSE_SW							0x0A12		/*!< STATUS CODE - Indicates the status word returned on the PPSE response is neither 0x9000 nor 0x6A81 nor 0x6A82 nor 0x6283. */
#define CLESS_STATUS_PPSE_NOT_FOUND							0x0A13		/*!< STATUS CODE - Indicates the card does not support the PPSE (file not found, status word is 0x6A82). */
#define CLESS_STATUS_CLESS_NOT_OPENED						0x0A14		/*!< STATUS CODE - Indicates the contactless driver is not opened. */
#define CLESS_STATUS_NO_MATCHING_APDU						0x0A15		/*!< STATUS CODE - Indicates there is no matching APDU for the APDU method. */
#define CLESS_STATUS_NO_APPLI								0x0A16		/*!< STATUS CODE - Indicates there is no contactless application. */
#define CLESS_STATUS_EP_NOT_LOADED							0x0A17		/*!< STATUS CODE - Indicates that PPSE Application Selection module is not loaded into the terminal. */
#define CLESS_STATUS_CANCELLED								0x0A18		/*!< STATUS CODE - Indicates that the operation has been cancelled. */
#define CLESS_STATUS_USE_ANOTHER_INTERFACE					0x0A20		/*!< STATUS CODE - Indicates that a contact interface shall be used. */
#define CLESS_STATUS_STOP									0x0A21		/*!< STATUS CODE - Indicates that the transaction shall be stopped. */
#define CLESS_STATUS_RETRY_DETECT							0x0A22		/*!< STATUS CODE - Indicates that the card shall be detected again. */
#define CLESS_STATUS_RETRY_DETECT_NO_DISPLAY				0x0A23		/*!< STATUS CODE - Indicates that the card shall be detected again, but no message shall be displayed by the manager. */
#define CLESS_STATUS_NO_CLESS								0x0A24		/*!< STATUS CODE - Indicates that no contactless interface is available. */
#define CLESS_STATUS_CONTINUE_SELECTION						0x0A25		/*!< STATUS CODE - Indicates that the selection shall be continued. */
#define CLESS_STATUS_EP_CLESS_SELECTION_NOT_ALLOWED			0x0A26		/*!< STATUS CODE - Indicates the contactless application selection is not allowed as the is no available AID for PPSE Application Selection method and for List Of AID method (if it shares the EP preprocessing results). */
#define CLESS_STATUS_NO_MATCHING_IS_FOR_YOU					0x0A27		/*!< STATUS CODE - Indicates there is no matching application for the CLESS_IS_FOR_YOU method. */
#define CLESS_STATUS_RESTART_DOUBLE_TAP						0x0A28		/*!< STATUS CODE - Indicates that th etransaction shall be restarted for double tap (NFC for example). */
#define CLESS_STATUS_NO_SELECTION_METHOD_ALLOWED			0x0A29		/*!< STATUS CODE - Indicates that there is no applicable selection method for the current transaction and that it is not necessary to open the cless field if a selection method is expected. */
#define CLESS_STATUS_USE_SWIPE_ONLY_INTERFACE				0x0A2A		/*!< STATUS CODE - Indicates that only swipe interface shall be used. */
#define CLESS_STATUS_USE_CHIP_ONLY_INTERFACE				0x0A2B		/*!< STATUS CODE - Indicates that only chip interface shall be used. */
#define CLESS_STATUS_NOT_IMPLEMENTED						0x0AFB		/*!< STATUS CODE - The requested function is not implemented in this version of the DLL. */
#define CLESS_STATUS_DLL_NOT_LOADED							0x0AFC		/*!< STATUS CODE - Returned by the DLL library. It indicates the DLL is not correctly loaded or mounted. */
#define CLESS_STATUS_NOT_ALLOWED							0x0AFD		/*!< STATUS CODE - Indicates this is not possible to call a function because of the current context. */
#define CLESS_STATUS_BAD_COMPONENT_INIT						0x0AFE		/*!< STATUS CODE - Indicates PPSE Application Selection module has not been initialised correctly (global value init failed). */
#define CLESS_STATUS_UNKNOWN								0x0AFF		/*!< STATUS CODE - This status would never be returned. */

//! @}


//! \addtogroup ClessGenericCustomisationStatusCodes
//! @{

#define CLESS_CUST_CONTINUE									(0)			/*!< Cless generic customisation return : Continue. */
#define CLESS_CUST_RETRY_WITH_CLESS							(1)			/*!< Cless generic customisation return : Retry with Cless. */
#define CLESS_CUST_RETRY_WITHOUT_CLESS						(2)			/*!< Cless generic customisation return : Retry Without Cless. */
#define CLESS_CUST_STOP										(3)			/*!< Cless generic customisation return : Stop. */
#define CLESS_CUST_DEFAULT									(4)			/*!< Cless generic customisation return : Default processing. */
#define CLESS_CUST_CONTINUE_METHOD							(6)			/*!< DO NOT USE - Cless generic customisation return : Continue method. */
#define CLESS_CUST_RETRY_WITH_CLESS_NO_MESSAGE_BEFORE_RETRY	(8)			/*!< Cless Generic - customisation return : Retry with cless. In implicit selection, the only difference with \ref CLESS_CUST_RETRY_WITH_CLESS is that the display is not refreshed with a message before the retry "state". In explicit selection, it has the same behaviour as \ref CLESS_CUST_RETRY_WITH_CLESS. */
#define CLESS_CUST_RETRY_CHIP_ONLY                     	    (9)			/*!< Cless Generic - customisation return : Retry with chip only. */
#define CLESS_CUST_RETRY_SWIPE_ONLY                    	    (10)		/*!< Cless Generic - customisation return : Retry with swipe only. */




//! \cond NOT_DOCUMENTED
#define CLESS_CUST_NEXT_METHOD								(5)			/*!< DO NOT USE - Cless generic customisation return : Next method. */
//! \endcond

//! @}


//! \addtogroup ClessImplicitReturnCode
//! @{

#define CLESS_CR_MANAGER_END								(0)			/*!< Implicit selection for result on following services : give info, debit, debit aid, is for you, end. */
#define CLESS_CR_MANAGER_RESTART							(1)			/*!< Implicit selection result : indicates the transaction shall be restarted. */
#define CLESS_CR_MANAGER_RESTART_WO_CLESS					(2)			/*!< Implicit selection result : indicates the transaction shall be conducted over another interface. */
#define CLESS_CR_MANAGER_REMOVE_AID							(3)			/*!< Implicit selection result : indicates the next AID having the highest priority shall be used. */
#define CLESS_CR_MANAGER_CONTINUE_METHOD					(5)			/*!< Implicit selection result : indicates the next criteria in the current applied method shall be used (similar to \ref CLESS_CR_MANAGER_REMOVE_AID for AID methods). */
#define CLESS_CR_MANAGER_OK									(6)			/*!< Implicit selection result : internal status, shall not be used. */
#define CLESS_CR_MANAGER_RESTART_DOUBLE_TAP					(7)			/*!< Implicit selection result : indicates transaction shall restart, but message for double tap shall be displayed. */
#define CLESS_CR_MANAGER_RESTART_NO_MESSAGE_BEFORE_RETRY	(8)			/*!< Implicit selection result : indicates the transaction shall be restarted, but no message should be displayed before the retry "state". Regarding the processing itself, it is the same as the \ref CLESS_CR_MANAGER_RESTART return. */
#define CLESS_CR_MANAGER_RESTART_CHIP_ONLY					(9)			/*!< Implicit selection result : indicates the transaction shall be conducted only in chip mode. */
#define CLESS_CR_MANAGER_RESTART_SWIPE_ONLY				    (10)		/*!< Implicit selection result : indicates the transaction shall be conducted only in swipe mode. */

//! \cond NOT_DOCUMENTED
#define CLESS_CR_MANAGER_NEXT_METHOD						(4)			/*!< DO NOT USE - Implicit selection result : indicates the application selection process shall continue with the next method (shall not be used). */
//! \endcond

//! @}


//! \addtogroup ClessImplicitCustomisationServices
//! @{

#define CLESS_SERVICE_CUST_IMPSEL_GUI						0x1E02		/*!< Implicit selection : GUI Customisation service. */
#define CLESS_SERVICE_CUST_IMPSEL_AS_PROC					0x1E03		/*!< Implicit selection : Application selection customisation (application selection result processing). */

//! \cond NOT_DOCUMENTED
#define CLESS_SERVICE_CUST_IMPSEL_DETECTION_PROCESSING		0x1E00		/*!< DO NOT USE - Implicit selection : Detection customisation (detection result processing). */
#define CLESS_SERVICE_CUST_IMPSEL_PERFORM_DETECTION			0x1E01		/*!< DO NOT USE - Implicit selection : Detection customisation (perform detection instead of DLL). */
#define CLESS_SERVICE_CUST_IMPSEL_AS_PERF					0x1E04		/*!< DO NOT USE - Implicit selection : Application selection customisation (perform application selection instead of DLL). */
#define CLESS_SERVICE_CUST_DEBIT_SAME_AID                   0x1E05		/*!< DO NOT USE - Cless debit with AID detected in several kernel, this entry point give kernel priority for this AID. */
//! \endcond

//! @}


#endif //__CLESS_STATUS_CODES_H__INCLUDED__
