/**
* \file def_tag.h
* \brief This module contains the definition of used tags in EMV package.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/


#ifndef _DEFTAG_H
#define _DEFTAG_H

//! \addtogroup Group_Tag_list
//! @{
//!
//**************************************************************************
//**	Elements given by ENGINE
//**************************************************************************

//! \addtogroup IntTags
//! @{
//!
//! \defgroup Entags Tags Emitted by Engine Component
//! @{

//! \def TAG_EG_IDENTIFICATION
//! \brief Engine identification on 11 bytes :
//! - CRC on 2 bytes.
//! - Component type on 1 byte.
//! - Component name on 8 bytes.
#define TAG_EG_IDENTIFICATION			0x9F8701
#define TAG_EG_VERSION					0x9F8702		//!< Engine Version. Length = 2 bytes.
#define TAG_EG_MESSAGE_CODE_NUM			0x9F8703		//!< Message code number. This is the ID of a standard message, to display. Length = 2 bytes.
#define TAG_EG_CARDHOLDER_LANGUAGE		0x9F8704		//!< Language to use. On 2 bytes represented by 2 alphabetical characters according to ISO 639.
#define TAG_EG_NUM_APPLI				0x9F8705		//!< Engine Application type, on 1 byte (given by M2OS).

//! \def TAG_EG_IS_AMOUNT_NEEDED
//! \brief When beginning a transaction, indicates to Custom if it is necessary to enter the amount.
//! Length = 1 byte.
//! - TRUE	: Engine asks Custom for an amount entry.
//! - FALSE	: Amount is already available. No amount entry needed.
#define TAG_EG_IS_AMOUNT_NEEDED			0x9F8706

//! \def TAG_EG_REFERRAL_CARD
//! \brief Referral origin
//! Length = 1 byte.
//! - TRUE	: Referral asked by the card
//! - FALSE	: Referral asked by the issuer (host)
#define TAG_EG_REFERRAL_CARD			0x9F8707

#define TAG_EG_IS_PIN_ONLINE_ACCEPTED	0x9f8720
#define TAG_EG_TYPE_KEY_PRESSED			0x9f8721		//!< Key value, given by M20S in the entry-point keyboard_event.

//! \def TAG_EG_DISPLAY_DESTINATION
//! \brief When a message is displayed, it indicates the destination.
//! Length = 1 byte.
//! - \ref DISPLAY_CARDHOLDER
//! - \ref DISPLAY_MERCHANT
//! - \ref DISPLAY_MERCHANT_CARDHOLDER
#define TAG_EG_DISPLAY_DESTINATION		0x9F8722

#define DISPLAY_MERCHANT				0				//!< Display on the merchant device.
#define DISPLAY_CARDHOLDER				1				//!< Display on the cardholder device.
#define DISPLAY_MERCHANT_CARDHOLDER		2				//!< Display on both devices.

//! @}	// end of Tags Emitted by Engine


//**************************************************************************
//**	Elements given by CUSTOM
//**************************************************************************


//! \defgroup Cutags Tags Emitted by EMV Custom Component
//! @{
//! \defgroup CuStat Custom Service Status Codes
//! @{
#define TAG_CUST_STATUS_CODE				0x9F8401		//!< EMV Custom service status code. Coded on 2 bytes.

//! @}	// end of CuStat

#define TAG_CUST_APPLI_NAME					0x9F8402		//!< Name of EMV application, displayed by M2OS. Name on 8 alphanumeric bytes.

#define TAG_CUST_IDLE_MESSAGE				0x9F8403		//!< Idle message to be displayed, if no other application is present. Name on 16 alphanumeric bytes.

#define TAG_CUST_IDENTIFICATION				0x9F8404
#define LEN_CUST_IDENTIFICATION				11
#define TAG_CUST_VERSION					0x9F8405
#define LEN_CUST_VERSION					2

#define TAG_NB_AID_TERMINAL					0x9F8407		//!< Number of AID managed by the application. Length = 1 byte.
#define TAG_CUST_IS_KSU						0x9F8408		//!< Boolean, TRUE if the pin code should be managed by KSU (if present). Length = 2 bytes.
#define TAG_CUST_IS_BLACK_LIST				0x9F8409		//!< Boolean, TRUE if the custom component manages the black list. Length = 2 bytes.
#define TAG_CUST_IS_PIN_BYPASS				0x9F840A		//!< Boolean, TRUE if the merchant is allowed to bypass the pin code entry. Length = 2 bytes.
#define TAG_CUST_IS_ONLINE_ADVICE			0x9F840B		//!< Boolean, TRUE if advices are supported and generate an online message. Length = 2 bytes.
#define TAG_CUST_IS_OFFLINE_ADVICE			0x9F840C		//!< Boolean, TRUE if advices are supported and generate an offline message. Length = 2 bytes.
#define TAG_CUST_IS_VOICE_REFERRAL			0x9F840D		//!< Boolean, TRUE if voice referral is supported. Length = 2 bytes.
#define TAG_CUST_IS_FORCED_ONLINE			0x9F840E		//!< Boolean, TRUE if the merchant is allowed to force the transaction to go online. Length = 2 bytes.
#define TAG_CUST_IS_FORCED_ACCEPTANCE		0x9F840F		//!< Boolean, TRUE if the merchant is allowed to force acceptance of the transaction. Length = 2 bytes.
#define TAG_CUST_IS_ONLINE_ADVICE_IF_FORCED_ACCEPTANCE	0x9F8410	//!< Boolean, TRUE if the terminal generate an online advice when the merchant forces the acceptance of the transaction. Length = 2 bytes.
#define TAG_CUST_COMM_TYPE_APPLI			0x9F8411		//!< Application type associated to COMM component. Length = 2 bytes.
#define TAG_CUST_NEW_BLACK_LIST_NEEDED		0x9F8412		//!< Boolean, TRUE if CUSTOM wishes to receive a new black-list. Length = 2 bytes.
#define TAG_CUST_PIN_BYPASS_REQUEST			0x9F8413
#define TAG_CUST_FORCED_ONLINE_REQUEST		0x9F8414		//!< Boolean, TRUE if the merchant asked to force the transaction to go online. Length = 2 bytes.
#define TAG_CUST_FORCED_ACCEPTANCE_REQUEST	0x9F8415		//!< Boolean, TRUE if the merchant asked to force the acceptance of the transaction. Length = 2 bytes.
#define TAG_LAST_TR_AMOUNT_BIN				0x9F8416		//!< Amount of the last transaction. Binary value on 4 bytes. (most significant byte is byte 0).
#define TAG_LAST_TR_CURRENCY_CODE			0x9F8417		//!< Currency code of the last transaction. Length = 2 bytes.
#define TAG_LAST_TR_DATE					0x9F8418
#define TAG_LAST_TR_TIME					0x9F8419
#define TAG_LAST_TR_TYPE					0x9F841A
#define TAG_CUST_PAN_IN_BLACK_LIST			0x9F841B		//!< Boolean, TRUE if CUSTOM found the PAN in the exception file. Length = 2 bytes.
#define TAG_CUST_NB_RECORD_IN_BATCH			0x9F841C		//!< Number of records present in the batch file. Binary value on 4 bytes.

//! \def TAG_CUST_APPLICATION_SELECTION_ID
//! \brief Application Selection Indicator. See EMV 2000, Book 1, 8.3
//! Length = 1 byte.
//! - 0 : Multiple occurences of the application are not allowed in the card : Partial name not supported.
//! - 1 : Multiple occurences of the application are allowed in the card : Partial supported.
#define TAG_CUST_APPLICATION_SELECTION_ID	0x9F841D


//! \def TAG_CUST_TRM_OVERPASS_AIP
//! \brief Indicates if function TRM has to be done even if AIP value does not indicate TRM to do.
//! See book 3 chapter 10.6
//! By default ( if this parameter does not exist ) behaviour is the same as FALSE.
//! Length : 1 byte
//! - TRUE :  perform TRM even if AIP not set
//! - FALSE : else
#define TAG_CUST_TRM_OVERPASS_AIP			0x9F841E		//!< Boolean, TRUE if TRM has to be done without testing AIP.
#define TAG_CUST_SERVICE_AUTHO_NUM			0x9F8420		//!< Number of the service to be called for online authorization request.

#define TAG_CUST_DEBIT_IS_ASKED				0x9F8421

//! \def TAG_CUST_TRLOG_IS_ASKED
//! \brief Boolean given in response to a function called by menu.
//! Length = 2 bytes. TRUE if Engine must start a transaction log.
#define TAG_CUST_TRLOG_IS_ASKED				0x9F842C

#define TAG_CUST_FORCE_OTHER_TT				0x9F842D

#define TAG_CUST_IS_COMMUNICATION_OK		0x9F8422		//!< Boolean, in case of on-line authorisation, indicates if the communication succeeded. Length = 2 bytes.
#define TAG_CUST_KEY_VALIDITY_DATE			0x9F8423

//! \def TAG_CUST_CERTIF_SERIAL_NO
//! \brief Serial Number of a certificate.
//! Binary number unique to a certificate assigned by the certification authority. See EMV 2000, Book 2, 6.1
//! Length : 3 bytes. binary
#define TAG_CUST_CERTIF_SERIAL_NO			0x9F8424

//! \defgroup Curevok List of revoked certificates
//! List of revoked Issuer Public Key Certificates.
//! See EMV 2000, Book2, 5.4, bulletin 10.
//! The five following tags contain a concatened list of revoked certificate.
//! Up to 255 bytes are available for each tag.
//! 9 bytes are used per certificate :
//! - RID of certification authority : 5
//! - Certification Authority Key Index : 1
//! - Serial Number of the certificate :3
//! @{
#define TAG_CUST_CA_REVOK_1					0x9F8425		//!< First tag to use to fill in the list.
#define TAG_CUST_CA_REVOK_2					0x9F8426		//!< Second tag use only if previous one it full.
#define TAG_CUST_CA_REVOK_3					0x9F8427		//!< Third tag use only if previous ones are full.
#define TAG_CUST_CA_REVOK_4					0x9F8428		//!< Fourth tag use only if previous ones are full.
#define TAG_CUST_CA_REVOK_5					0x9F8429		//!< Fifth tag use only if previous ones are full.

//! @}	// end of Curevok

#define TAG_TRANSACTION_FORCED_ACCEPTANCE	0x9F842A		//!< Boolean, TRUE if the merchant wants to force the transaction acceptance. Length = 1 byte.

//! \def TAG_CUST_POS_ISO8583_93
//! \brief Point of Service Code of Data (ISO 8583 - 1993).
//! 12 characters, as defined in ISO 8583 - 1993.
#define TAG_CUST_POS_ISO8583_93				0x9F842B
#define LEN_CUST_POS_ISO8583_93				12

//! \def TAG_CUST_IS_COMM_MANAGED_BY_CUSTOM
//! \brief Indicates if Custom manages all the interface with the host acquirer.
//! For historical reasons, EMV Engine manages authorisation requests during the transaction.
//! It calls standard COMM entry points to achieve these authorisation requests.
//! It may be useful in some cases to let Custom manage fully the interface with the acquirer host.
//! In this case, set this tag on, and send it to Engine in global parameters.
//! EMV ENGINE will then call the service EMVCUST_Authorization instead of the corresponding COMM service.
//! Length = 1 byte.
#define TAG_CUST_IS_COMM_MANAGED_BY_CUSTOM	0x9F8430
#define LEN_CUST_IS_COMM_MANAGED_BY_CUSTOM	1

//! \def TAG_CUST_SUPPORTED_LANGUAGE_LIST
//! \brief Gives the list of the languages supported by the terminal.
//! This tag contains the list of supported languages. Each language is represented
//! by 2 alphabetical characters, according to ISO 639.
//! This tag shall be given to EMV Engine in the service EMVCUST_Get_Global_Param.
//! Length = N * 2 bytes (N is the number of supported languages).
#define TAG_CUST_SUPPORTED_LANGUAGE_LIST	0x9F8431


// Set of tag created to manage configuration file
#define TAG_CUST_IS_PREFERRED_DISPLAY_ORDER		0x9F8440

//! \def TAG_CUST_IS_MULTILANG_SUPPORTED
//! \brief Indicates if terminal manages multi language selection
//! See Book 4 - Section 11.1 - Language Selection
//! Length : 1 byte
//! - TRUE :  performs multi language selection
//! - FALSE : else
#define TAG_CUST_IS_MULTILANG_SUPPORTED			0x9F8441
#define TAG_CUST_IS_REVOK_SUPPORTED				0x9F8442
#define TAG_CUST_IS_AMOUNT_BEFORE_CVM			0x9F8443
#define TAG_CUST_IS_TRANSACTION_LOG				0x9F8444
#define TAG_CUST_IS_ISSUER_REFERRAL				0x9F8445
#define TAG_CUST_IS_CARD_REFERRAL				0x9F8446

//! \def TAG_CUST_IS_BATCH_CAPTURE
//! \brief Indicates if terminal supports Batch Data Capture
//! See Book 4 - chapter 12 Acquirer Interface
//! Length : 1 byte
//! - TRUE :  supports Batch Data Capture
//! - FALSE : else
#define TAG_CUST_IS_BATCH_CAPTURE				0x9F8447

//! \def TAG_CUST_IS_ONLINE_CAPTURE
//! \brief Indicates if terminal supports Online Data Capture
//! See Book 4 - chapter 12 Acquirer Interface
//! Length : 1 byte
//! - TRUE :  supports Online Data Capture
//! - FALSE : else
#define TAG_CUST_IS_ONLINE_CAPTURE				0x9F8448
#define TAG_CUST_IS_PINPAD						0x9F8449
#define TAG_CUST_IS_AMOUNT_PIN_SAME				0x9F844A


//! \def TAG_CUST_IS_CARDHOLDER_CONFIRMATION
//! \brief Indicates if terminal supports Cardholder Confirmation during Application Selection
//! See Book 1 - Section 12.4 - Final Selection
//! Length : 1 byte
//! - TRUE :  supports Cardholder Confirmation
//! - FALSE : else
#define TAG_CUST_IS_CARDHOLDER_CONFIRMATION		0x9F844B
#define TAG_CUST_IS_EXCEPTION_FILE				0x9F844C
#define TAG_CUST_IS_GETDATA_PIN_TRY_COUNTER		0x9F844D
#define TAG_CUST_IS_POS_ENTRY_MODE				0x9F844E
#define TAG_CUST_POS_ENTRY_VALUE				0x9F844F
#define TAG_CUST_IS_CONFIG_FILE					0x9f8450
#define TAG_CUST_CRC_CONFIG_FILE				0x9f8451

#define TAG_CUST_IS_DEFAULT_DDOL				0x9F8452

//! \def TAG_CUST_IS_FLOOR_LIMIT_CHECKING
//! \brief Indicate if function Floor Limit Checking in TRM has to be done according
//! particular terminal type.
//! See Book 4 6.4 Conditions for Support of Functions.
//! By default ( if this parameter does not exist ) behaviour is the same as TRUE.
//! Length : 1 byte
//! - TRUE :  processing Floor Limit Checking
//! - FALSE : do not process Floor Limit Checking (if conditions are gathered)
#define TAG_CUST_IS_FLOOR_LIMIT_CHECKING		0x9F8453

//! \def TAG_CUST_IS_RANDOM_TRANSACTION_SELECT
//! \brief Indicate if function Velocity Checking in TRM has to be done according
//! particular terminal type.
//! See Book 4 6.4 Conditions for Support of Functions.
//! By default ( if this parameter does not exist ) behaviour is the same as TRUE.
//! Length : 1 byte
//! - TRUE :  processing Random Selection
//! - FALSE : do not process Random Selection Checking (if conditions are gathered)

#define TAG_CUST_IS_RANDOM_TRANSACTION_SELECT	0x9F8454
//! \def TAG_CUST_IS_VELOCITY_CHECKING
//! \brief Indicate if function Velocity Checking in TRM has to be done according
//! particular terminal type.
//! See Book 4 6.4 Conditions for Support of Functions.
//! By default ( if this parameter does not exist ) behaviour is the same as TRUE.
//! Length : 1 byte
//! - TRUE :  processing Velocity Checking
//! - FALSE : do not process velocity Checking (if conditions are gathered)

#define TAG_CUST_IS_VELOCITY_CHECKING			0x9F8455
#define TAG_CUST_IS_DEFAULT_TDOL				0x9f8456
#define TAG_CUST_FULL_CRC_CONFIG_FILE			0x9f8457

//! \def TAG_CUST_IS_ODA_PROCESSING
//! \brief Indicate if function Offline Data Authentication has to be done according
//! particular terminal type.
//! See Book 4 6.4 Conditions for Support of Functions.
//! By default ( if this parameter does not exist ) behaviour is the same as TRUE.
//! Length : 1 byte
//! - TRUE :  processing ODA
//! - FALSE : do not process ODA ( if conditions are gathered)
#define TAG_CUST_IS_ODA_PROCESSING				0x9F8458


//! \def TAG_CUST_IS_ACCOUNT_TYPE
//! \brief Indicates if the ICCs type of account has to be selected on the terminal
//! By default (if this parameter does not exist)
//! behaviour is the same as FALSE.
//! See Book 1 6.1 overview of application slection
//! Length : 1 byte
//! - TRUE :  type account has to be selected
//! - FALSE : do not ask for type account to be selected
//! \def 
#define TAG_CUST_IS_ACCOUNT_TYPE				0x9F8459

//! \def TAG_CUST_IS_SKIP_DEFAULT
//! \brief Indicate if TAC/IAC Default processing has to be skipped for an Online only terminal
//! when terminal is unable to succesfully go online. By default (if this parameter does not exist)
//! behaviour is the same as FALSE.
//! Length : 1 byte
//! - TRUE :  skip TAC/IAC Default processing if conditions are gathered.
//! - FALSE : process TAC/IAC Default processing.
#define TAG_CUST_IS_SKIP_DEFAULT				0x9F845A

//! \def TAG_CUST_IS_SKIP_ONLINE
//! \brief Indicate if TAC/IAC Online processing has to be skipped for an Offline only terminal
//! during Terminal Action analysis. By default (if this parameter does not exist)
//! behaviour is the same as TRUE.
//! Length : 1 byte
//! - TRUE :  skip TAC/IAC Online processing if conditions are gathered.
//! - FALSE : process TAC/IAC Online processing.
#define TAG_CUST_IS_SKIP_ONLINE					0x9F845B


/*& BEGIN FT/2006/07/MA :  CDA Modified Terminal Behaviour			   */

/*  test value of ICS Parameter "device capable of detecting CDA failure before termal Action Acnalysis */
/*  NO if parameter is FALSE  */
/*  YES all other cases or if parameter is not set */

//! \def TAG_CUST_DETECT_FAIL_PRIOR_TAA
//! \brief Indicate if detection of CDA failure has to be done before 
//! before Terminal Action analysis. By default (if this parameter does not exist)
//! behaviour is the same as TRUE.
//! Length : 1 byte
//! - TRUE :  detects CDA failure before TAA
//! - FALSE : do not detect errors
#define TAG_CUST_DETECT_FAIL_PRIOR_TAA				0x9F845C

//! \def TAG_CUST_CDA_NEVER_REQUEST_ARQC_1GENAC
//! \brief Indicate if CDA is not requested in a 1rst generate AC with ARQC
//! By default (if this parameter does not exist)
//! behaviour is the same as FALSE.
//! Length : 1 byte
//! - TRUE :  do not ask CDA on first GENERATE AC 
//! - FALSE : ask CDA on first GENERATE AC
#define TAG_CUST_CDA_NEVER_REQUEST_ARQC_1GENAC		0x9F845D


//! \def TAG_CUST_CDA_NEVER_REQUEST_ONLINE_2GENAC
//! \brief Indicate if CDA is not requested in a 2nd generate AC with TC
//! By default (if this parameter does not exist)
//! behaviour is the same as FALSE.
//! Length : 1 byte
//! - TRUE :  do not ask CDA on second GENERATE AC 
//! - FALSE : ask CDA on second GENERATE AC
#define TAG_CUST_CDA_NEVER_REQUEST_ONLINE_2GENAC	0x9F845E


/*& BEGIN FT/2006/07/MA :  CDA Modified Terminal Behaviour			   */

#define TAG_CUST_ODA_PR_CV_TRM_SEQUENCE_ORDER	0x9F845F
#define TAG_CUST_STEP_ODA						(0)
#define TAG_CUST_STEP_PR						(1)
#define TAG_CUST_STEP_CV						(2)
#define TAG_CUST_STEP_TRM						(3)

//! \def TAG_CUST_SUBSEQUENT_BYPASS_PIN
//! \brief When PIN entry has been bypassed for one PIN-related CVM, it may be considered bypassed for 
//! any subsequent PIN-related CVM during the current transaction.
//! By default (if this parameter does not exist)
//! behaviour is the same as TRUE.
//! See Book 4 6.3.4.3 Pin Entry Bypass
//! Length : 1 byte
//! - TRUE :  bypass subsequent pin entry method
//! - FALSE : do not bypass subsequent pin entry method ( ask for pin entry )
#define TAG_CUST_SUBSEQUENT_BYPASS_PIN			0x9F8460

#define TAG_CUST_BATCH_RECORD_TYPE				0x9F8461						//!< Tag indicating the type of record in the batch file : 0 financial record, 1 advice record. Length = 1 byte.

#define TAG_CUST_FINAL_SELECT_CALL				0x9F8462						//!< Tag indicating if CUSTOM manages the step EMVDC_FINAL_SELECTION or not : FASLE do not manager EMVDC_FINAL_SELECTION, TRUE manages EMVDC_FINAL_SELECTION. Length = 1 byte.

#define TAG_CUST_SUPPORTED_CHIP_READERS			0x9F8463						//!< Tag indicating the supported chip readers (ttestall format). Length = 4 byte. Example: (CAM0 | CAM2).

#define TAG_CUST_IS_AMOUNT_UNKNOWN_BEFORE_CVM	0x9F8464			            //!< Tag indicating that amount is unknown before CVM). Length = 1 byte. TRUE unknown FALSE ( or default ) amount exist

#define TAG_CUST_IS_SELECTABLE_KERNEL           0x9F8465						//!< Tag indicating that kernel is selectable. Length = 1 byte. TRUE selectable FALSE ( or default ) not selectable

#define TAG_CUST_IS_DELETABLE_TAC           0x9F8466						//!< Tag indicating that kernel supports TAC to be disabled. Length = 1 byte. TRUE  FALSE ( or default )


//! \def TAG_CUST_LOG_DURING_TR
//! \brief Indicate if Transaction has to be read during transaction
//! By default (if this parameter does not exist)
//! behaviour is the same as FALSE.
//! Length : 1 byte
//! - TRUE :  read log during transaction
//! - FALSE : do not read log during transaction
#define TAG_CUST_LOG_DURING_TR					0x9F8467	
//***************************
//     Service Status Code
//***************************
//! \addtogroup CuStat
//! @{
//!
// Service Completed Successfully
#define	TAG_CUST_PROCESS_COMPLETED				TAG_PROCESS_COMPLETED			//!< \ref TAG_PROCESS_COMPLETED
#define	TAG_CUST_TRANSACTION_ACCEPTED			TAG_TRANSACTION_ACCEPTED		//!< \ref TAG_TRANSACTION_ACCEPTED
#define TAG_CUST_TRANSACTION_DECLINED			TAG_TRANSACTION_DECLINED		//!< \ref TAG_TRANSACTION_DECLINED
#define	TAG_CUST_AUTHORISATION_REQUEST			TAG_AUTHORISATION_REQUEST		//!< \ref TAG_AUTHORISATION_REQUEST
#define	TAG_CUST_REFERRAL_REQUEST				TAG_REFERRAL_REQUEST			//!< \ref TAG_AUTHORISATION_REQUEST
#define	TAG_CUST_VISA_EASY_ENTRY_CARD			TAG_VISA_EASY_ENTRY_CARD		//!< \ref TAG_VISA_EASY_ENTRY_CARD
#define TAG_CUST_CDA_FAILED						TAG_CDA_FAILED					//!< \ref TAG_CDA_FAILED
#define TAG_CUST_SUSPEND_ENGINE					TAG_SUSPEND_ENGINE				//!< \ref TAG_SUSPEND_ENGINE
#define TAG_CUST_RETRY_COMMUNICATION			0x0008
#define TAG_CUST_CAA_REQUEST					0x0009


// Transaction Terminated
#define TAG_CUST_TRANSACTION_CANCELLED			TAG_TRANSACTION_CANCELLED		//!< \ref TAG_TRANSACTION_CANCELLED
#define TAG_CUST_PROCESSING_ERROR				TAG_PROCESSING_ERROR			//!< \ref TAG_PROCESSING_ERROR
#define TAG_CUST_CARD_ERROR						TAG_CARD_ERROR					//!< \ref TAG_CARD_ERROR
#define	TAG_CUST_NOT_ACCEPTED					TAG_NOT_ACCEPTED				//!< \ref TAG_NOT_ACCEPTED
#define TAG_CUST_ICC_DATA_FORMAT_ERROR			TAG_ICC_DATA_FORMAT_ERROR		//!< \ref TAG_ICC_DATA_FORMAT_ERROR
#define TAG_CUST_MISSING_MANDATORY_ICC_DATA		TAG_MISSING_MANDATORY_ICC_DATA	//!< \ref TAG_MISSING_MANDATORY_ICC_DATA
#define TAG_CUST_ICC_REDUNDANT_DATA				TAG_ICC_REDUNDANT_DATA			//!< \ref TAG_ICC_REDUNDANT_DATA
#define TAG_CUST_CARD_BLOCKED					TAG_CARD_BLOCKED				//!< \ref TAG_CARD_BLOCKED
#define TAG_CUST_COND_OF_USE_NOT_SATISFIED		TAG_COND_OF_USE_NOT_SATISFIED	//!< \ref TAG_COND_OF_USE_NOT_SATISFIED
#define TAG_CUST_MISSING_MANDATORY_TERM_DATA	TAG_MISSING_MANDATORY_TERM_DATA	//!< \ref TAG_MISSING_MANDATORY_TERM_DATA
#define TAG_CUST_INTERNAL_ERROR					TAG_INTERNAL_ERROR				//!< \ref TAG_INTERNAL_ERROR
#define TAG_CUST_REMOVED_CARD					TAG_REMOVED_CARD				//!< \ref TAG_REMOVED_CARD
#define TAG_CUST_SERVICE_NOT_ALLOWED			TAG_SERVICE_NOT_ALLOWED			//!< \ref TAG_SERVICE_NOT_ALLOWED


// Service execution error
#define	TAG_CUST_NOT_ENOUGH_MEMORY				TAG_NOT_ENOUGH_MEMORY			//!< \ref TAG_NOT_ENOUGH_MEMORY
#define	TAG_CUST_WRONG_TLV_TREE_INPUT_PARAMETER	TAG_WRONG_DEL_INPUT_PARAMETER	//!< The input TLV tree received from engine doesn't contain awaited tag.
#define	TAG_CUST_SERVICE_NOT_AVAILABLE  		0x0103							//!< The AID parameter selection failed.
#define	TAG_CUST_PAN_NOT_FOUND          		0x0104							//!< The primary account number was not found in the database.
#define	TAG_CUST_NEW_PARAMETERS					0x0105							//!< New manager parameters are present in the terminal.
#define	TAG_CUST_REFERRAL_DECLINED				0x0106							//!< The referral is declined.
#define	TAG_CUST_REFERRAL_ON_LINE				0x0107							//!< An online referral is requested.
#define	TAG_CUST_REFERRAL_NOT_ACCEPTED			0x0108							//!< The referral is not accepted.

//! @}	// end of CuStat

//! @}	// end of Tags Emitted by Custom



//*******************************
//     Comm Service Status Code
//*******************************

// Service Completed Successfully
#define	TAG_COMM_PROCESS_COMPLETED				0x0000		//!< Service completed successfully.
#define	TAG_COMM_ERASE_BATCH_DATE				0x0001		//!< Erase batch data until following date.
#define	TAG_COMM_ERASE_BATCH_COUNTER			0x0002		//!< Erase batch data until following record number.

// Service execution error
#define	TAG_COMM_SERVICE_NOT_AVAILABLE			0x0103		//!< Service not available at this time.
#define	TAG_COMM_HOST_UNREACHABLE				0x0104		//!< Acquirer host unreachable.
#define	TAG_COMM_COMM_PROBLEM					0x0105		//!< Communication problem.
#define	TAG_COMM_COMM_TIME_OUT					0x0106		//!< Communication timeout.
#define	TAG_COMM_MESSAGE_REJECTED				0x0107		//!< Message rejected.
#define	TAG_COMM_INVALID_RESPONSE				0x0108
#define TAG_COMM_MERCHANT_CANCEL                0x0109

/*& BEGIN DE TE/Z2/03/46/JMV : REVERSAL */

// Valid values for reversal messages
#define	TAG_COMM_CUSTOMER_CANCELLATION			0x01		//!< The customer canceled the transaction
#define	TAG_COMM_SUSPECTED_MALFUNCTION			0x02
#define	TAG_COMM_RESPONSE_RECEIVED_TOO_LATE		0x03
#define	TAG_COMM_TIMED_OUT_AT_TAKING_MONEY		0x04
#define	TAG_COMM_TIME_OUT_WAITING_FOR_RESPONSE	0x05
#define	TAG_COMM_ICC_GENERATED_ACC				0x06

/*& END DE TE/Z2/03/46/JMV : REVERSAL */


#define TAG_APPLICATION_LIST	0x9F8200
#define TAG_EMV_SELECTED_AID	0x9F8201

//! @}	// end of IntTags

//! @}	// end of Group_Tag_list

#endif
