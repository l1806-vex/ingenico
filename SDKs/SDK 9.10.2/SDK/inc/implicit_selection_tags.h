/**
 *! \file        implicit_selection_tags.h
 * \brief This describes all the implicit selection specific tags
 *
 *
 * \author SAGEM MONETEL
 * \author Copyright (c) 2006 Sagem Monetel SA, rue claude Chappe,\n
 *		   07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Sagem Monetel SA has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Sagem Monetel.
 **/

///////////// Detection types ////////////////////////////////////////////////////////////////////////////////
#define TAG_DETECTION_TYPE						0x9F9401		/*!< Detection type for a given application */
#define DETECT_A								0x01			/*!< Classic detection for type A cards */
#define DETECT_B								0x02			/*!< Classic detection for type B cards */
#define DETECT_AB								0x03			/*!< Classic detection for type A or type B cards */
#define DETECT_A_ONLY							0x04			/*!< Detection for cards requesting several consecutive WUPA */
#define DETECT_B_ONLY							0x05			/*!< Detection for cards requesting several consecutive WUPB */
#define DETECT_A_DETECT_B						0x06			/*!< Not an application parameter, to detect all cards types */

///////////// Activation types ///////////////////////////////////////////////////////////////////////////////
#define TAG_ACTIVATION_TYPE						0x9F9402		/*!< Activation type for a given application */
#define TAG_ACTIVATION_RESULT					0x9F9403		/*!< Activation result returned back by the ClessDC module */
#define ACTIVATE_ISO14443						0x11			/*!< Classic ISO 14443 card activation */
#define ACTIVATE_MIFARE							0x12			/*!< Classic Mifare card activation */
#define ACTIVATE_CALYPSO						0x13			/*!< Classic Innovatron Clypso B prime activation */
#define ACTIVATE_OTHER							0x1F			/*!< Other activation method than ISO14443 and Mifare */

///////////// Possible application parameters for application selection //////////////////////////////////////
#define TAG_AID_STRUCTURE						0xBF9401		/*!< Structure that contains AID data to perform the application selection. An application can provide one or several of this structres */
#define TAG_DIRECT_SELECTION_IS_ALLOWED			0x9F9404		/*!< Parameter in the structre before that informs if the direct selection is allowed or not */
#define TAG_APDU_BEFORE_SELECT_STRUCTURE		0xBF9402		/*!< Structure that contains all the parameters to perform an application using the APDU method (criteria used before AID method) */
#define TAG_APDU_AFTER_SELECT_STRUCTURE			0xBF9403		/*!< Structure that contains all the parameters to perform an application using the APDU method (criteria used after AID method) */
#define TAG_APDU_TO_SEND						0x9F9405		/*!< Parameter in a structure defined just before that consists of the APDU to send to the card */
#define TAG_EXPECTED_STATUS_WORD				0x9F9406		/*!< Parameter in a structure defined just before that consists of the expected status word from the card to the APDU sent */
#define TAG_EXPECTED_CARD_RESPONSE				0x9F9407		/*!< Parameter in a structure defined just before that consists of the expected response from the card to the APDU sent */
#define TAG_RESPONSE_MASK						0x9F9408		/*!< Parameter in a structure defined just before that consists of mask on the card response */
#define TAG_NUMBER_OF_RETRY_FOR_SELECTION		0x9F9409		/*!< Parameter that indicates the number of retry if an error occurs during detection or activation of the card */
#define TAG_RESTART_IF_COMMAND_FAILS			0x9F940A		/*!< Parameter that inform if the transaction has to restart if a communication error occurs (if activated, it overwrites the parameter before, nb of retries) */
#define TAG_CLESS_USE_ERROR_SIGNAL_TONE			0x9F9428		/*!< Parameter that inform if an error beep should be sound or not when an error occurs */
#define TAG_CLESS_USE_CHIP_IF_CARD_UNSUPPORTED	0x9F9429		/*!< Parameter that inform if the terminal must request to use chip/swipe or must generate an error if the card is not supported */
#define TAG_CLESS_USE_CHIP_INSTEAD_TERMINATE	0x9F942A		/*!< Parameter that informs if the terminal has to use swipe / chip instead of terminating the transaction if an error occurs during the implicit selection mechanism (UK needs) */
#define TAG_CLESS_OPTIMISE_DRIVERS_ACCESSES		0x9F942B		/*!< Parameter that informs if the terminal has to close or not the CAM0 and SWIPE drivers */

///////////// Implicit selection status code /////////////////////////////////////////////////////////////////
#define TAG_CARD_DETECTED						0x0008			/*!< Status code that informs that a card has been detected */
#define TAG_NEXT_AID							0x0009			/*!< Status code that informs that another AID is given from the candidate list (if remove AID from candidate list is requested) */
#define TAG_AID_TO_BE_REMOVED_FROM_CLIST		0x0021			/*!< Status code that informs that the current AID has to be removed from the candidate list (implicit selection only) */
#define TAG_USE_SWIPE_OR_CHIP					0x0022			/*!< Status code that informs that the transaction must be conducted using chip or swipe */
#define TAG_TIMEOUT_ELAPSED						0x0023			/*!< Status code that informs that the timeout for card presentation is elapsed */
#define TAG_NO_MORE_AID							0x0027			/*!< Status code that informs that no more AID is present in the candidate list (if remove AID from candidate list is requested) */
#define TAG_UNRECOGNIZED_DETECT					0x0025			/*!< Status code that informs that neither an ISO14443 nor a Mifare card had been detected */
#define TAG_TOO_MANY_CARDS_DETECTED				0x0026			/*!< Status code that informs that several cards had been detected */
#define TAG_TRY_AGAIN							0x0027			/*!< Status code that informs that "try again" must be displayed */

///////////// Returned selection type ////////////////////////////////////////////////////////////////////////
#define TAG_CLESS_SELECTION_TYPE				0x9F940B		/*!< Selection type that has been performed by the ClessDC module for application selection */
#define METHOD_SELECT_AID						0x31			/*!< AID method is selected */
#define METHOD_SELECT_APDU_BEFORE_SELECT		0x32			/*!< APDU method is selected (APDU before AID method matches) */
#define METHOD_SELECT_APDU_AFTER_SELECT			0x33			/*!< APDU method is selected (APDU after AID method matches) */
#define METHOD_SELECT_UNRECOGNIZED				0x3F			/*!< No requested method for applciation selection matches */

///////////// If AID method is used for application selection ///////////////////////////////////////////////
#define TAG_SELECTED_ICC_AID					0x9F940C		/*!< Consists of the selected AID (from the card) */
#define TAG_AID_TO_REMOVE						0x9F9412		/*!< Consists of the AID to be removed from the candidate list */
#define TAG_NB_AID_IN_CANDIDATE_LIST			0x9F940D		/*!< Consists of the number of AID that are presnet in the candidate list */
#define TAG_FINAL_SELECTION_PERFORMED			0x9F940E		/*!< Informs if the final selection had been performed or not */
#define TAG_RETURNED_CARD_DATA					0x9F940F		/*!< Card response (not parsed) if final selection is performed */

///////////// If APDU method is used (before/after) for application selection ///////////////////////////////
#define TAG_APPLIED_APDU						0x9F9410		/*!< Successfully applied APDU */
#define TAG_APDU_CARD_RESPONSE					0x9F9411		/*!< Card response to the applied APDU */
#define TAG_CARD_RESPONSE_STATUS_WORD			0x9F9413		/*!< SW of the card response to the applied APDU */


///////////// Status codes for transparents accesses via IAPP (using ClessDC module) ////////////////////////

#define TAG_TRANSPARENT_STATUS_CODE				0x9F9418		/*!< SMO USE ONLY : Status code for command sent using the IAPP for driver accesses */
#define TRANSPARENT_PROCESS_COMPLETED			0x4000			/*!< SMO USE ONLY : The operation successfully performed */
#define TRANSPARENT_PROCESS_ERROR				0x4001			/*!< SMO USE ONLY : An error occurs during the command */
#define TRANSPARENT_MISSING_PARAMS				0x4002			/*!< SMO USE ONLY : A parameter is missing for performing the operation */

#define TAG_TRANSPARENT_IS_ISO_CARD				0x9F9419		/*!< SMO USE ONLY : Informs if a card is ISO or not */
#define TAG_TRANSPARENT_CARD_INDEX				0x9F941A		/*!< SMO USE ONLY : Card index (for transparent cless accesses) */
#define TAG_TRANSPARENT_APDU_COMMAND			0x9F941B		/*!< SMO USE ONLY : Command to send to the card in transparent mode */
#define TAG_TRANSPARENT_APDU_RESPONSE			0x9F941C		/*!< SMO USE ONLY : Response sent by the card to a command APDU */
#define TAG_TRANSPARENT_TYPE_OF_CARD			0x9F941D		/*!< SMO USE ONLY : Type of card (A, B or AB) for card detection */
#define TAG_TRANSPARENT_NUMBER_OF_CARDS			0x9F941E		/*!< SMO USE ONLY : Number of detected cards */
#define TAG_TRANSPARENT_DETECTION_TIMEOUT		0x9F941F		/*!< SMO USE ONLY : Detection timeout */
#define TAG_TRANSPARENT_KIND_OF_CARD			0x9F9420		/*!< SMO USE ONLY : Kind of card for activation (Mifare or ISO) */
#define TAG_TRANSPARENT_SEND_DESELECT			0x9F9421		/*!< SMO USE ONLY : Send a deselect command to the card for deselection or not */
#define TAG_TRANSPARENT_WAIT_REMOVE				0x9F9422		/*!< SMO USE ONLY : Wait card removal for deselection */

#define TAG_TRANSPARENT_KEY_TYPE				0x9F9423		/*!< SMO USE ONLY :  */
#define TAG_TRANSPARENT_UNCODED_KEY				0x9F9424		/*!< SMO USE ONLY :  */
#define TAG_TRANSPARENT_SECTOR					0x9F9425		/*!< SMO USE ONLY :  */
#define TAG_TRANSPARENT_DATA_TYPE				0x9F9426		/*!< SMO USE ONLY :  */
#define TAG_TRANSPARENT_BLOCK					0x9F9427		/*!< SMO USE ONLY :  */
#define TAG_TRANSPARENT_DATA_BLOCK				0x9F9414		/*!< SMO USE ONLY :  */
#define TAG_TRANSPARENT_OPERATION_TYPE			0x9F9415		/*!< SMO USE ONLY :  */
#define TAG_TRANSPARENT_DEST_BLOCK				0x9F9416		/*!< SMO USE ONLY :  */
#define TAG_TRANSPARENT_UID						0x9F942C		/*!< SMO USE ONLY :  */


// Specific EMV tags
#ifndef TAG_SERVICE_STATUS_CODE
#define TAG_SERVICE_STATUS_CODE					0x9F8101
#endif

#ifndef TAG_AID_TERMINAL
#define TAG_AID_TERMINAL						0x9F06
#endif

#ifndef TAG_CUST_APPLICATION_SELECTION_ID
#define TAG_CUST_APPLICATION_SELECTION_ID		0x9F841D
#endif


