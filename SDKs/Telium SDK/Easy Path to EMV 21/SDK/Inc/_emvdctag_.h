/**
* \file _emvdctag_.h
* \brief This module contains the definition of used tags by EMVDC component.
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

#ifndef _EMVDCTAG_H
#define _EMVDCTAG_H

//! \defgroup Group_Tag_list List of used tags in custom application.
//! @{

// TAG OF THE EMV'96 SPECIFICATION

//! \defgroup ExtTags External Tags Definition
//! @{

#define TAG_ACQUIRER_IDENTIFIER				0x9F01				//!< Acquirer identifier. Uniquely identifies the acquirer within each payment system. Length = 6 bytes.
#define LEN_ACQUIRER_IDENTIFIER				6					//!< Acquirer identifier length.
#define TAG_ADD_TERMINAL_CAPABILITIES		0x9F40				//!< Additional Terminal Capabilities. Indicates the data input and output capabilities of the terminal. Length = 5 bytes.
#define LEN_ADD_TERMINAL_CAPABILITIES		5					//!< Additional Terminal Capabilities length.
#define TAG_AEF_DATA_TEMPLATE				0x70
#define TAG_AMOUNT_AUTH_BIN					0x81				//!< Amount, authorized (binary). Authorised amount of the transaction (excluding adjustments). Length = 4 bytes.
#define TAG_AMOUNT_AUTH_NUM					0x9F02				//!< Amount, authorized (numeric). Authorised amount of the transaction (excluding adjustments). Length = 6 bytes.
#define TAG_AMOUNT_OTHER_BIN				0x9F04				//!< Amount, other (binary). Secondary amount associated with the transaction representing a cashback amount. Length = 4 bytes.
#define TAG_AMOUNT_OTHER_NUM				0x9F03				//!< Amount, other (numeric). Secondary amount associated with the transaction representing a cashback amount. Length = 6 bytes.
#define TAG_AMOUNT_REFERENCE_CURRENCY_BIN	0x9F3A				
#define TAG_APPLI_CRYPTOGRAMME_AC			0x9F26				//!< Application cryptogram. Cryptogram returned by the ICC in response of the GENERATE AC command. Length = 8 bytes.
#define TAG_APPLI_CURRENCY_CODE				0x9F42
/*#define TAG_APPLI_CURRENCY_CODE_VISA		0x9F51 fixed 2cj012*/
#define TAG_APPLI_CURRENCY_EXPONENT			0x9F44
#define TAG_APPLI_DEFAULT_ACTION			0x9F52
#define TAG_APPLI_DISCRETIONARY_DATA		0x9F05
#define TAG_APPLI_EFFECTIVE_DATE			0x5F25				//!< Application Effective Date. Date from which the application may be used. Format = YYMMDD. Length = 3 bytes.
#define TAG_APPLI_EXPIRATION_DATE			0x5F24				//!< Application Expiration Date. Date after which application expires. Format = YYMMDD. Length = 3 bytes.
#define TAG_AFL								0x94
#define LEN_AFL								252
#define TAG_AID_ICC							0x4F				//!< Application identifier (card). Identifies the application as described in ISO/IEC 7816-5.
#define TAG_AID_TERMINAL					0x9F06				//!< Application identifier (terminal). Identifies the application as described in ISO/IEC 7816-5.

#ifndef LEN_AID
#define LEN_AID								16					//!< Application identifier length.
#endif

#define TAG_AIP								0x82				//!< Application interchange profile. Indicates the capabilities of the card to support specific functions in the application.  Length = 2 bytes.
#define LEN_AIP								2					//!< Application interchange profile length.
#define TAG_APPLICATION_LABEL				0x50				//!< Application label. Mnemonic associated with the AID according to ISO/IEC 7816-5. Length = 1 to 16 bytes.
#define TAG_APPLICATION_PREFFERRED_NAME		0x9F12				//!< Application preferred name. Preferred mnemonic associated with the AID. Length = 1 to 16 bytes.
#define TAG_APPLI_PRIM_ACCOUNT_NB			0x5A				//!< Application primary account number (PAN). Valid cardholder account number.  Length = variable up to 10 bytes.
#define TAG_APPLI_PRIM_ACCOUNT_NB_SEQ_NB	0x5F34				//!< Application primary account number (PAN) sequence number. Identifies and differentiates cards with the same PAN. Length = 1 byte.
#define TAG_APPLI_PRIOR_IND					0x87				//!< Application priority indicator. Indicates the priority of a given application or group of applications in a directory. Length = 1 byte.
#define TAG_APPLI_REF_CURRENCY				0x9F3B
#define TAG_APPLI_REF_CURRENCY_EXPONENT		0x9F43
#define TAG_APPLI_TEMPLATE					0X61
#define TAG_ATC								0x9F36				//!< Application transaction counter : a counter maintained by the card application of the number of transactions processed. Length = 2 bytes.
#define TAG_APPLI_USAGE_CONTROL				0x9F07				//!< Application Usage Control. Indicates issuer‘s specified restrictions on the geographic usage and services allowed for the application. Length = 2 bytes.
#define TAG_VERSION_NUMBER_ICC				0x9F08
#define TAG_VERSION_NUMBER_TERMINAL			0x9F09				//!< Application Version Number. Version number assigned by the payment system for the application. Length = 2 bytes.
#define TAG_AUTHORISATION_CODE				0x89				//!< Authorisation Code. Value generated by the authorisation authority for an approved transaction. Length = 6 bytes.
#define TAG_AUTHORISATION_RESPONSE_CODE		0x8A				//!< Authorisation Response Code. Code that defines the disposition of a message. Length = 2 bytes.
#define TAG_CPLC_STRING						0x9F7F
#define TAG_CDOL1							0x8C
#define TAG_CDOL2							0x8D
#define TAG_CARDHOLDER_NAME					0x5F20
#define TAG_CARDHOLDER_NAME_EXT				0x9F0B
#define TAG_CVM_LIST						0x8E				//!< Cardholder Verification Method (CVM) List. Identifies a method of verification of the cardholder supported by the application. Length = variable up to 252 bytes.
#define TAG_CVR_RESULT						0x9F34				//!< Cardholder Verification Method (CVM) Results. Indicates the results of the last CVM performed. Length = 3 bytes.
#define LEN_CVR								3					//!< Card verification results length.
#define TAG_CERT_AUTH_PUB_KEY_INDEX_ICC		0x8F				//!< Certification Authority Public Key Index (card). Identifies the certification authority‘s public key in conjunction with the RID. Length = 1 byte.
#define TAG_CERT_AUTH_PUB_KEY_INDEX_TERM	0x9F22				//!< Certification Authority Public Key Index (terminal). Identifies the certification authority‘s public key in conjunction with the RID. Length = 1 byte.
#define TAG_COMMAND_TEMPLATE				0x83
#define TAG_COMMAND_TO_PERFORM				0x52
#define TAG_CRYPTOGRAM_INFORMATION_DATA		0x9F27				//!< Cryptogram Information Data. Indicates the type of cryptogram and the actions to be performed by the terminal. Length = 1 byte.
#define TAG_CUMUL_TOTAL_TRANS_AMOUNT_LIMIT	0x9F54
#define TAG_DATA_AUTH_CODE					0x9F45
#define TAG_DF_NAME							0x84
#define TAG_DIRECTORY_DEF_FILE_NAME			0x9D
#define TAG_DIRECTORY_DISCRET_TEMPLATE		0x73
#define TAG_DDOL							0x9F49
#define TAG_FCI_ISSUER_DISCRET_DATA			0xBF0C
#define TAG_FCI_ISSUER_PROPRIET_TEMPLATE	0xA5
#define TAG_FCI_TEMPLATE					0x6F
#define TAG_GEO_INDIC						0x9F55
#define TAG_ICC_DYNAMIC_NUMBER				0x9F4C				//!< ICC Dynamic Number. Time-variant number generated by the ICC, to be captured by the terminal.  Length = 2 to 8 bytes.
#define TAG_ICC_PIN_ENCIPH_PUB_KEY_CERT		0x9F2D
#define TAG_ICC_PIN_ENCIPH_PUB_KEY_EXP		0x9F2E
#define TAG_ICC_PIN_ENCIPH_PUB_KEY_REM		0x9F2F
#define TAG_ICC_PUB_KEY_CERT				0x9F46
#define TAG_ICC_PUB_KEY_EXP					0x9F47				//!< Integrated Circuit Card (ICC) Public Key Exponent. ICC Public Key Exponent used for the verification of the Signed Dynamic Application Data. Length = 1 to 3 bytes.
#define TAG_ICC_PUB_KEY_REM					0x9F48				//!< Integrated Circuit Card (ICC) Public Key Remainder. Remaining digits of the ICC Public Key Modulus.
#define TAG_IFD_SERIAL_NUMBER				0x9F1E				//!< Interface Device (IFD) Serial Number. Unique and permanent serial number assigned to the IFD by the manufacturer. Length = 8 bytes.

//! \def TAG_ISSUER_ACTION_CODE_DEFAULT
//! \brief Issuer Action Code - Default. 
//! Specifies the issuer's conditions that cause a transaction to be rejected 
//! if it might have been approved online, but the terminal is unable to process 
//! the transaction online. Length = 5 bytes.
#define TAG_ISSUER_ACTION_CODE_DEFAULT		0x9F0D
#define TAG_ISSUER_ACTION_CODE_DENIAL		0x9F0E				//!< Issuer Action Code - Denial. Specifies the issuer's conditions that cause the denial of a transaction without attempt to go online. Length = 5 bytes.
#define TAG_ISSUER_ACTION_CODE_ONLINE		0x9F0F				//!< Issuer Action Code - Online. Specifies the issuer's conditions that cause a transaction to be transmitted online. Length = 5 bytes.
#define TAG_ISSUER_APPLICATION_DATA			0x9F10				//!< Issuer application data. Contains proprietary application data for transmission to the issuer in an online transaction. Length = variable up to 32 bytes.
#define TAG_ISSUER_AUTH_DATA				0x91
#define TAG_ISSUER_AUTH_INDIC				0x9F56
#define TAG_ISSUER_CODE_TABLE_INDEX			0x9F11				//!< Issuer Code Table Index. Indicates the code table according to ISO/IEC 8859 for displaying the Application Preferred Name. Length = 1 byte.
#define TAG_ISSUER_COUNTRY_CODE				0x5F28				//!< Issuer Country Code. Indicates the country of the issuer according to ISO 3166. Length = 2 bytes.
#define TAG_ISSUER_COUNTRY_CODE_VISA		0x9F57
#define TAG_ISSUER_PUBLIC_KEY_CERT			0x90
#define TAG_ISSUER_PUBLIC_KEY_EXP			0x9F32				//!< Issuer Public Key Exponent. Issuer public key exponent used for the verification of the Signed Static Application Data and the ICC Public Key Certificate. Length = 1 to 3 bytes.
#define TAG_ISSUER_PUBLIC_KEY_REM			0x92				//!< Issuer Public Key Remainder. Remaining digits of the Issuer Public Key Modulus.
#define TAG_ISSUER_SCRIPT_COMMAND			0x86
#define TAG_ISSUER_SCRIPT_IDENTIFIER		0x9F18
#define LEN_SCRID							0x04
#define TAG_ISSUER_SCRIPT_TEMPLATE_1		0x71
#define TAG_ISSUER_SCRIPT_TEMPLATE_2		0x72
#define TAG_LANGUAGE_PREFERENCE				0x5F2D				//!< Language Preference. 1-4 languages stored in order of preference, each represented by 2 alphabetical characters according to ISO 639. Length = 2 to 8 bytes.
#define TAG_LAST_ONLINE_ATC					0x9F13
#define TAG_LOW_CONS_OFF_LIMIT				0x9F14
#define TAG_LOW_CONS_OFF_LIMIT_VISA			0x9F58
#define TAG_MERCHANT_CATEGORY_CODE			0x9F15				//!< Merchant Category Code. Classifies the type of business being done by the merchant, represented according to ISO 8583:1993 for Card Acceptor Business Code. Length = 2 bytes.
#define TAG_MERCHANT_IDENTIFIER				0x9F16				//!< Merchant Identifier. When concatenated with the Acquirer Identifier, uniquely identifies a given merchant. Length = 15 bytes.
#define TAG_PIN_TRY_COUNTER					0x9F17
#define TAG_POS_ENTRY_MODE_CODE				0x9F39				//!< Point-of-Service (POS) Entry Mode. Indicates the method by which the PAN was entered, according to the first two digits of the ISO 8583:1987 POS Entry Mode. Length = 1 byte.
#define TAG_PDOL							0x9F38
#define TAG_RGPO_FORMAT1					0x80
#define TAG_RGPO_FORMAT2					0x77
#define TAG_RINT_FORMAT1					0x80
#define TAG_RINT_FORMAT2					0x77
#define TAG_SERVICE_CODE					0x5F30				//!< Service Code. Service code as defined in ISO/IEC 7813 for track 1 and track 2. Length = 2 bytes.
#define TAG_SFI								0x88
#define TAG_SIGNED_DYNAMIC_APPLI_DATA		0x9F4B
#define TAG_SIGNED_STATIC_APPLI_DATA		0x93
#define TAG_STATIC_DATA_AUTH_TAG_LIST		0x9F4A
#define TAG_TERMINAL_CAPABILITIES			0x9F33				//!< Terminal Capabilities. Indicates the card data input, CVM, and security capabilities of the terminal. Length = 3 bytes.
#define LEN_TERMINAL_CAPABILITIES			0x3					//!< Terminal Capabilities length.
#define TAG_TERMINAL_COUNTRY_CODE			0x9F1A				//!< Terminal Country Code. Indicates the country of the terminal, represented according to ISO 3166. Length = 2 bytes.
#define LEN_TERMINAL_COUNTRY_CODE			0x2					//!< Terminal Country Code length.
#define TAG_TERMINAL_FLOOR_LIMIT			0x9F1B				//!< Terminal Floor Limit. Indicates the floor limit in the terminal in conjunction with the AID. Length = 4 bytes.
#define TAG_TERMINAL_IDENTIFICATION			0x9F1C				//!< Terminal Identification. Designates the unique location of a terminal at a merchant. Length = 8 bytes.
#define LEN_TERMINAL_IDENTIFICATION			0x8					//!< Terminal Identification length.
#define TAG_TERMINAL_RISK_MANAGMENT_DATA	0x9F1D
#define TAG_TERMINAL_TYPE					0x9F35				//!< Terminal Type. Indicates the environment of the terminal, its communications capability, and its operational control. Length = 1 byte.
#define LEN_TERMINAL_TYPE					0x1					//!< Terminal type length.
#define TAG_TVR								0x95				//!< Terminal Verification Results. Status of the different functions as seen from the terminal. Length = 5 bytes.
#define LEN_TVR								0x5					//!< Terminal Verification Results length.
#define TAG_TRACK1_DISCRET_DATA				0x9F1F
#define TAG_TRACK2_DISCRET_DATA				0x9F20

#define TAG_MERCHANT_NAME_AND_LOCATION		0x9F4E

//! \def TAG_TRACK2_EQU_DATA
//! \brief Track 2 Equivalent Data. Contains the data elements of track 2 
//! according to ISO/IEC 7813, excluding start sentinel, end sentinel, and 
//! Longitudinal Redundancy Check (LRC), as follows :
//! - Primary Account Number.
//! - Field Separator (Hex 'D').
//! - Expiration Date (YYMM).
//! - Service Code.
//! - Discretionary Data (defined by individual payment systems).
//! - Pad with one Hex 'F' if needed to ensure whole bytes.
#define TAG_TRACK2_EQU_DATA					0x57
#define TAG_TDOL							0x97
#define TAG_TC_HASH_VALUE					0x98
#define TAG_TRANSACTION_CURRENCY_CODE		0x5F2A				//!< Transaction Currency Code. Indicates the currency code of the transaction according to ISO 4217. Length = 2 bytes.
#define TAG_TRANSACTION_CURRENCY_EXP		0x5F36				//!< Transaction Currency Exponent. Indicates the implied position of the decimal point from the right of the transaction amount represented according to ISO 4217. Length = 1 byte.
#define TAG_TRANSACTION_DATE				0x9A				//!< Transaction Date. Local date that the transaction was authorised. Format = YYMMDD. Length = 3 bytes.
#define TAG_TRANSACTION_PIN_DATA			0x99

//! \def TAG_TRANSACTION_REF_CURRENCY_CODE
//! \brief Transaction Reference Currency Code.
//! Code defining the common currency used by the terminal in case the 
//! Transaction Currency Code is different from the Application Currency Code. 
//! Length = 2 bytes.
#define TAG_TRANSACTION_REF_CURRENCY_CODE	0x9F3C

//! \def TAG_TRANSACTION_REF_CURRENCY_EXP
//! \brief Transaction Reference Currency Exponent. 
//! Indicates the implied position of the decimal point from the right of the transaction amount,
//! with the Transaction Reference Currency Code represented according to ISO 4217. 
//! Length = 1 byte.
#define TAG_TRANSACTION_REF_CURRENCY_EXP	0x9F3D
#define TAG_TRANSACTION_SEQ_COUNTER			0x9F41				//!< Transaction Sequence Counter. Counter maintained by the terminal that is incremented by one for each transaction. See \ref TAG_TSC_NOT_MANAGED to manage it manually.
#define LEN_TRANSACTION_SEQ_COUNTER			0x4					//!< Transaction Sequence Counter length.

#define TAG_TSI								0x9B				//!< Transaction Status Information. Indicates the functions performed in a transaction. Length = 2 bytes.
#define LEN_TSI								0x2
#define TAG_TRANSACTION_TIME				0x9F21				//!< Transaction time. Local time that the transaction was authorised. Format = HHMMSS. Length = 3 bytes.

//! \def TAG_TRANSACTION_TYPE
//! \brief Transaction Type. Indicates the type of financial transaction, 
//! represented by the first two digits of the ISO 8583:1987 Processing Code.
//! The actual values to be used for the Transaction Type data element are defined 
//! by the relevant payment system. Length = 1 byte.
#define TAG_TRANSACTION_TYPE				0x9C
#define TAG_UNPREDICTABLE_NUMBER			0x9F37				//!< Unpredictable Number. Value to provide variability and uniqueness to the generation of a cryptogram. Length = 4 bytes.
#define TAG_UPPER_CONS_OFFLINE_LIMIT		0x9F23

#define TAG_UPPER_CONS_OFFLINE_LIMIT_VISA	0x9F59

#define TAG_ANUFACT_DATA					0xDF50

// #define TAG_TRANSACTION_CATEGORY_CODE		0x9F53

/*& BEGIN FT/937/06/MA : Get transaction Log from ICC for PBOC			   */
#define TAG_LOG_ENTRY						0x9F4D
#define TAG_LOG_FORMAT						0x9F4F
/*& END FT/937/06/MA : Get transaction Log from ICC for PBOC			   */

/*& BEGIN FT/1126/06/MA : Account Type Selection						   */
#define TAG_ACCOUNT_TYPE					0x5F57				//!< Account Type. Indicates the type of account selected on the terminal, coded as specified in Annex G. Length = 1 byte.
#define TAG_IBAN							0x5F53
/*& END   FT/1126/06/MA : Account Type Selection						   */

//! @}	// end of External Tags Definition

//********************************
//****	Tags of the terminal  ****
//********************************
//! \defgroup IntTags Internal Tags Definition
//! @{

#define TAG_SERVICE_STATUS_CODE						0x9F8101		//!< Status of the service code. See \ref Status definitions.
// Service Status Code values definition.

//! \def TAG_LAST_APDU_CMD_RESPONSE
//! \brief Last Instruction code, and response : 
//! - Byte 1: CLA
//! - Byte 2: INS
//! - Byte 3: P1
//! - Byte 4: P2
//! - Byte 5: SW1
//! - Byte 6: SW2
#define TAG_LAST_APDU_CMD_RESPONSE					0x9F8102
#define LEN_LAST_APDU_CMD_RESPONSE					0x6				//!< Last apdu command response length.

#define TAG_LAST_APDU_RES							0x9F8103		//!< Response Code of EMV Level 1 to the last command. See SDK 30 documentation.
#define LEN_LAST_APDU_RES							0x1
#define TAG_ICC_APPLICATION_WARNING					0x9F8104		//!< Used in french application only. An application in the card has a problem (format error, ...)
#define TAG_LOCATED_ERROR							0x9F8105
#define TAG_EMV_ERROR								0x9F8106		//!< Internal use only : Do not use.
#define TAG_COMPONENT_VERSION						0x9f8107		//!< Obsolete value : Do not use.
#define TAG_UNPREDICTABLE_ICC_NUMBER				0x9F8108		//!< Unpredictable value given by the ICC in response to a GET_CHALLENGE command. 

//! \def TAG_COMPONENT_ID
//! \brief EMVDC Component identification on 11 bytes : 
//! - CRC on 2 bytes
//! - Component type on 1 byte
//! - Component name on 8 bytes
#define TAG_COMPONENT_ID							0x9f8109

//! \def TAG_AID_LIST_TERMINAL
//! \brief List of AID managed by the terminal.
//! This list is given in entry to the application selection step.
//! It is a concatened list of AID with :
//! - len : AID length on one byte. The most significant bit is dedicated to ASI : 
//!	- 0 : partial AID allowed
//!	- 1 : partial AID not allowed.
//! - AID : Application Identifier.
#define TAG_AID_LIST_TERMINAL						0x9F8110

//! \def TAG_ICC_EMV_DC_OPTION
//! \brief Special options to be applied to the transaction.
//! value on 2 bytes :
//! - Byte 1 :
//!	- bit 8 : Merchant force online choice
//! - bit 7 : Merchant force decline : AAC instead of ARQC in Gen AC
//!	- bit 6 : Merchant force Offline approved instead of Offline declined
//!	- Other bits : RFU.
//! - Byte 2: RFU.
#define TAG_ICC_EMV_DC_OPTION						0x9f8111
#define TAG_CUMUL_AMOUNT							0x9F8112		//!< Indicates the cumulative transaction amount for the current card.

//! \def TAG_EXCEPTION_FILE_RESULT
//! \brief Result of exception file control
//! value on 1 byte :
//! - 0 : ICC not found in exception fie
//! - 1 : ICC found.
#define TAG_EXCEPTION_FILE_RESULT					0x9F8113
#define TAG_AUTH_REQUEST_INTERF						0x9F8114		//!< Internal use only : Do not use.
#define TAG_AUTH_REQUEST_SERVICE					0x9F8115		//!< Internal use only : Do not use.
#define TAG_CARDHOLDER_CONFIRMATION					0x9f8116		//!< Boolean indicating if the cardholder confirmation is requested : 0 : No, 1 : Yes.
#define TAG_NUMBER_OF_MATCHING_APP					0x9f8117		//!< Number of matching application between the terminal and the card
#define TAG_APP_LABEL_DISPLAYED						0x9f8118		//!< Internal use only : Do not use.
#define TAG_TAA_RESULT								0x9f8119		//!< Result on TAA step as defined in EMV 2000, Book 3 6.7, on one byte.
#define TAG_AUTHORISATION_RESULT					0x9f811A		//!< Issuer decision on one byte : 0 declined, 1 accepted.
#define TAG_LAST_CVM_CODE							0x9f811B		//!< Last CVM method examined, on one byte.
#define TAG_TIME_OUT_PIN_CODE						0x9f811C		//!< Obsolete value : Do not use.
#define TAG_TIME_OUT_INTER_CAR						0x9f811D		//!< Obsolete value : Do not use.
#define TAG_PIN_MINIMUM								0x9f811E		//!< Used in french application only.
#define TAG_INPUT_PIN_STATE							0x9f811F		//!< Internal use only : Do not use.

#define TAG_CERT_AUTH_PUB_KEY						0x9F8120		//!< Obsolete value : Do not use.
#define TAG_CERT_AUTH_PUB_KEY_CHECKSUM				0x9F8121		//!< SHA on Certification Authority Public Key. Length = 20.
#define TAG_CERT_AUTH_PUB_KEY_EXPONENT				0x9F8122		//!< Certification Authority Exponent. Length = 1 for exp 3, Length = 3 for exp 56537.
#define TAG_CERT_AUTH_PUB_KEY_MODULUS				0x9F8123		//!< Certification Authority Modulus.
#define TAG_DEFAULT_DDOL							0x9F8124		//!< Default Dynamic Data Authentication Data Object List (DDOL). See EMV 2000 book 3 1.4.
#define TAG_DEFAULT_TDOL							0x9F8125		//!< Default Transaction Certificate Data Object List (TDOL). See EMV 2000 book 3 1.4.
#define TAG_MAX_TARG_PERC_FOR_BIASED_RAND_SEL		0x9F8126		//!< Maximum Target Percentage to be Used for Biased Random Selection. One binary byte from 0 to 99.
#define TAG_TARG_PERC_FOR_BIASED_RAND_SEL			0x9F8127		//!< Target Percentage to Be Used for Random Selection. One binary byte from 0 to 99.
#define TAG_TERMINAL_ACTION_CODE_DEFAULT			0x9F8128		//!< Terminal Action Code Default. See EMV 2000, Book3 6.7.
#define TAG_TERMINAL_ACTION_CODE_DENIAL				0x9F8129		//!< Terminal Action Code Denial. See EMV 2000, Book3 6.7.
#define TAG_TERMINAL_ACTION_CODE_ONLINE				0x9F812A		//!< Terminal Action Code Online. See EMV 2000, Book3 6.7.
#define TAG_TRESH_VALUE_FOR_BIASED_RAND_SEL			0x9F812B		//!< Threshold Value for Biased random Selection. See EMV 2000, Book3 6.6.2.
#define TAG_TRANSACTION_REF_CURRENCY_CONV			0x9F812C		//!< Transaction Reference Currency Conversion (Not used in current version of EMVDC.
#define TAG_ISSUER_SCRIPT_RESULT					0x9F812D		//!< Issuer Script Result for one script. Length on 5 bytes. See EMV 2000, Book 4, Annex A5.
#define LEN_ISR											0x05

//! \def TAG_ISSUER_SCRIPT_LIST
//! \brief Encapsulation tag for one Issuer Script.
//! Value for this tag is :
//! - First Byte	: Script Temblate (71 or 72)
//! - Second Byte	: Script length
//! - Other bytes	: script value.
#define TAG_ISSUER_SCRIPT_LIST						0x9F812E
#define TAG_ISSUER_SCRIPT_RESULT_LIST				0x9F812F		//!< Issuer Script Result List. See EMV 2000, Book 4, Annex A5.
#define TAG_HISTORICAL_BYTES						0x9f8130		//!< Historical bytes after Power on. See EMV 2000, Book 1.

//! \def TAG_RESULT_ANALISYS_TAC_DEFAULT
//! \brief Result of Terminal Action Analysis performed on TAC - Default and IAC - Default
//! 0 : Declined,
//! 1 : Approved.
#define TAG_RESULT_ANALISYS_TAC_DEFAULT				0x9F8131
#define TAG_ISSUER_SCRIPT_RESULT_LIST_LEN			0x9F8137		//!< Issuer Script Result List. Number of bytes in ISR List.

//! \def TAG_AUTOMATE
//! \brief Result of processing of CVM on the application side (i.e : result of pin entry)
//! see automate definitions for detail of the authorised values.
#define TAG_AUTOMATE								0x9F8132

//! \def TAG_STATUS_CVP
//! \brief Current Cardholder Verication Method to be processed
//! see automate definitions for detail of the authorised values
#define TAG_STATUS_CVP								0x9F8133
#define TAG_PIN_CODE								0x9F8134		//!< Pin value (Fill in with dummy bytes, as Pin value is no more accessible.
#define TAG_REMAINING_PIN							0x9F8135		//!< Number of remaining PIN tries.

//! \def TAG_SIGNATURE
//! \brief Indicates whether a signature is required or not
//! Length = 1 byte.
//!	TRUE if signature required.
#define TAG_SIGNATURE								0x9F8136
#define TAG_PIN_ERROR								0x9F8138		//!< Used in french application only.

//! \def TAG_BYPASS_PIN
//! \brief Indicates if the Pin entry bypass is required
//! Length = 1 byte.
//! TRUE (1) if bypass required.
#define TAG_BYPASS_PIN								0x9F8139

//! \def TAG_SCHEMAS_KSU
//! \brief Identify the type of schemes to be managed.
//! Only one scheme is defined up to now : Scheme for PIN presentation
//! Length = 4 bytes.
#define TAG_SCHEMAS_KSU								0x9F813A
#define TAG_PP_OK									0x9F813B		//!< Boolean on one Byte. True if Pinpad is functioning.
#define TAG_MODE 									0x9F813C		//!< Used in french application only.

//! \def TAG_PROPRIETARY_TAGS
//! \brief Enables to give the description of a proprietary tag.
//! List of proprietary tag definition, with 8 bytes for each tag :
//! - 2 first bytes : Proprietary tag value : (shall be between 9F50 and 9F7F)
//! - 2 bytes : tag length in case of fixed length, or 0 if variable length
//! - 2 bytes : minimum length. 0 in case of fixed length
//! - 2 bytes : maximum length. 0 in case of fixed length
#define TAG_PROPRIETARY_TAGS						0x9F813D

#define TAG_AID_PROPRIETARY							0x9F8140

#define TAG_COMPATIBILITY_2000						0x9F8141		//!< Boolean TRUE for a compatibility with EMV 2000 requirements.
#define LEN_COMPATIBILITY_2000						1

#define TAG_USE_PSE									0x9F8142		//!< Boolean indicating whether the PSE algorithm shall be used or not. (By default, only the list of AID method is used).
#define LEN_USE_PSE									1

#define TAG_AID_FAILURE								0x9F8150		//!< Only useful in the french application.

//! \brief It can be set set with the following values:
//! - 0x00, default value, Kernel will manage Transaction Sequence Counter (TSC) internally, incremented on each transaction and saved in FLASH.
//! - 0x01, application must manage TSC itself by sending the tag \ref TAG_TRANSACTION_SEQ_COUNTER with the others transaction parameters (no later than the FINAL SELECT step).
#define TAG_TSC_NOT_MANAGED							0x9F8151

/*&BEGIN FT/08/3207/WM      Ajout du temps de calcul RSA dans les traces TOOLWARE  */
#define TAG_ODA_TIME								0x9F815E
/*&END FT/08/3207/WM      Ajout du temps de calcul RSA dans les traces TOOLWARE  */

//! \defgroup IntMsg Internal messages  (Obsolete values : do not use)
//! @{
// tag for the message
#define TAG_MSG_APPROVED							0x9F8153
#define TAG_MSG_CALL_YOUR_BANK						0x9F8154
/*#define TAG_MSG_CARD_ERROR						0x9F8156*/
#define TAG_MSG_DECLINED							0x9F8157
#define TAG_MSG_ENTER_PIN							0x9F8159
#define TAG_MSG_INCORRECT_PIN						0x9F815a
#define TAG_MSG_NOT_ACCEPTED						0x9F815c
#define TAG_MSG_PIN_OK								0x9F815d
/*#define TAG_MSG_PLEASE_WAIT						0x9F813e*/
#define TAG_MSG_PROCESSING_ERROR					0x9F813f
/*#define TAG_MSG_REMOVE_CARD						0x9F8140*/
#define TAG_MSG_TRY_AGAIN							0x9F8163
/*#define TAG_MSG_CARD_CANNOT_BE_READ				0x9F8170*/
#define TAG_MSG_LAST_PIN_TRY						0x9F8171
#define TAG_MSG_PIN_TRY_LIMIT_EXCEEDED				0x9F8172
#define TAG_MSG_PIN_LENGTH_ERROR					0x9F8173
#define TAG_MSG_PIN_BLOCKED							0x9F8174
#define TAG_MSG_ELECTRICAL_PB						0x9F8175
#define TAG_MSG_COMMS_ERROR							0x9F8176

//! @}

//! \defgroup ExtOda Tags for externalisation of ODA
//! \warning Do not use, except in case of specific requirements
//! @{
// Externalisation ODA
#define TAG_EXTERNAL_FUNCTION						0x9F8180
#define TAG_ODA_TYPE								0x9F8181
#define TAG_ODA_RESULT								0x9F8182
#define TAG_INPUT_AUTH_DATA							0x9F8183
#define TAG_DDOL_DATA								0x9F8184

//! @}

/* BEGIN tedt/z3/02/1166  authentication records must have tag 70 */
#define TAG_ERROR_SFI_AUTH							0x9F8185

#define TAG_PIN_EXT_FLAG							0x9F8186
#define TAG_PIN_EXT_ENCIPHER						0x9F8187

#define TAG_IPK_DATA				0x9F8188		//!< Data Recovered from the Issuer Public Key Certificate, as defined in EMV2000, Book 2, Table 4.
#define TAG_SDA_DATA				0x9F8189		//!< Data Recovered from the SDA, as defined in EMV2000, Book 2, Table 5.
#define TAG_ICC_DATA				0x9F818A		//!< Data Recovered from the ICC Public Key Certificate, as defined in EMV2000, Book 2, Table 10.
#define TAG_ICC_PIN_DATA			0x9F818B		//!< Data Recovered from the ICC PIN Encipherment Public Key Certificate, as defined in EMV2000, Book 2, Table 23.
#define TAG_DDA_DATA				0x9F818C		//!< Data Recovered from the DDA, as defined in EMV2000, Book 2, Table 13.
#define TAG_WAIT_AFTER_ATR			0x9F818D		//!< Special need for EMV probe tools : Add a delay after ATR.
#define TAG_IPK_CERTIFICATE_SERIAL	0x9F818E
#define TAG_APPLI_SEL_STATE			0x9F818F
#define TAG_ICC_DYNAMIC_DATA		0x9F81B9		//!< Data Recovered from the Signature application data , as defined in EMV2000, Book 2, Table 19.

//! \def TAG_IS_FORCAGE_CDA
//! \brief Indicate if CDA has to be requested independetly of AIP
//! By default behaviour is the same as FALSE.
//! Length : 1 byte
//! - TRUE :  ask CDA to be done
//! - FALSE : do not force CDA 
#define TAG_IS_FORCAGE_CDA			0x9F81BA

/* &BEGIN tedt/z3/02/1674/ma EMV2000 specifi for Combo DDA*/
#define TAG_COMBO									0x9F8190
#define TAG_PDOL_VALUES								0x9F8191
#define TAG_CDOL1_VALUES							0x9F8192
#define TAG_CDOL2_VALUES							0x9F8193
#define TAG_GENAC_RESP								0x9F8194
#define TAG_PSE_ALGO								0x9F8195		//!< Enables to require an alternative option to the PSE algorithm.
#define PSE_NORESELECT								0x00			//!< Standard algorithm.
#define PSE_RESELECT								0x01			//!< Reselect when resume to previous directory.
#define TAG_RECOVERED_CID							0x9F8196		//!< In case of CDA, CID recovered from the cerficate.

#define TAG_APDU_CMD								0x9F8197		//!< EMV C_APDU.
#define TAG_APDU_RESPONSE							0x9F8198		//!< EMV R_APDU.
#define TAG_BEGIN_TIMER								0x9F8199		//!< Absolute tick before the command.
#define TAG_END_TIMER								0x9F819A		//!< Absolute tick after the command.
#define TAG_IS_TOOLWARE								0x9F819B		//!< Tool ware implemented.

//! \def TAG_IS_ADVICE_REQUIRED
//! \brief Indicate if an advice messages must be created, when the transaction is declined.
//! Do not create an advice when a batch log is created, or when the transaction is
//! captured online, even if the tag is set to TRIE.
//! Length : 1 byte
//! - TRUE : Create an advice if the transaction is declined.
//! - FALSE : Don't create an advice.
#define TAG_IS_ADVICE_REQUIRED						0x9F819C

/*& BEGIN FT/937/06/MA : Get transaction Log from ICC for PBOC			   */
#define TAG_TRLOG_RECORD							0x9F819D		//!< Contains a response of command Read_Record of transaction Log of the ICC.
#define TAG_TRLOG_IN_PROGRESS						0x9F81A4
/*& END FT/937/06/MA : Get transaction Log from ICC for PBOC			   */

#define TAG_FORCE_TAA_RESULT						0x9F81AB

/*& BEGIN FT/2006/07/MA :  CDA Modified Terminal Behaviour			   */
#define TAG_CDA_NEVER_REQUEST_ARQC_1GENAC			0x9F81A7
#define TAG_CDA_NEVER_REQUEST_ONLINE_2GENAC			0x9F81A8
#define TAG_DETECT_FAIL_PRIOR_TAA					0x9F81A6
#define TAG_CDA_IN_P1_GENAC1						0x9F81A5
#define TAG_CDA_IN_P1_GENAC2						0x9F81A9
#define TAG_FORCE_AAC_IN_P1_GENAC2					0x9F81AA
/*& BEGIN FT/2006/07/MA :  CDA Modified Terminal Behaviour			   */

/* management of parameter Amount known before CVM value is 01 if amount is known*/
#define TAG_AMOUNT_UNKNOWN							0x9F81B7
/* management of internal Transaction Type */
#define TAG_INT_TRANSACTION_TYPE					0x9F81B8

/*& BEGIN DE/FT/2567/MA : gestion compatibilite applications France sur donnees Discretionary */
#define TAG_MNG_AS_PROPRIETARY						0x9F81AC
/*& END DE/FT/2567/MA : gestion compatibilite applications France sur donnees Discretionary */

/*& BEGIN FT/08/3144/JJA  peripheral number on which EMV CArd is inserted */
#define TAG_CHIP_READER_ID							0x9F81AD
/*& END FT/08/3144/JJA  peripheral number on which EMV CArd is inserted */

//! \def TAG_PROPRIETARY_TAGS_EX
//! \brief Enables to give the description of a proprietary tag.
//! \brief First Send to Engine TAG_PROPRIETARY_TAGS_EX at the step EMVCUST_Get_Global_Param_TlvTree. This tag allows to define a list of tag plus their characteristics and tell to emvdc kernel what is the name and format of the tags to store. 
//! List of proprietary tag definition, with 8 bytes for each tag :
//! - 2 first bytes : Proprietary tag value : (shall be a private tag class see Annex B1, Book 3 table 35 or between 9F50 and 9F7F)
//! - 2 bytes : minimum length (cannot be set to zero) 
//! - 2 bytes : maximum length (if minLen = maxLen, it means that the tag value has a fixed length)
//! - 1 byte : mask :
//!		- 000xxxxx Alphanumeric
//!		- 001xxxxx Alphanumeric Special
//!		- 010xxxxx Binary
//!		- 011xxxxx Compressed Numeric
//!		- 100xxxxx Numeric
//!		- 101xxxxx RFU
//!		- 110xxxxx RFU
//!		- 111xxxxx RFU
//!		- xxx00xxx Source Terminal
//!		- xxx01xxx Source ICC
//!		- xxx10xxx Source Issuer
//!		- xxx11xxx Source Issuer/Terminal
//!
//! Then use EMVDC_Ex_SetPrivateDataElements() or TLV_EMVDC_Ex_SetPrivateDataElements() to setup the values of previously defined Issuer or Terminal tags.(Use EmvDcInterface.lib provided in  EP2EMV > Pack 20)
#define TAG_PROPRIETARY_TAGS_EX						0x9F815F


//! @}		// end of Internal Tags Definition

/*******************************/
/** Service Status Code State **/
/******************************/
//! \defgroup Status Service Status Codes
//! @{

// Service Completed Successfully
#define	TAG_PROCESS_COMPLETED						0x0000			//!< Service Completed Successfully - Nothing Special.
#define	TAG_TRANSACTION_ACCEPTED					0x0001			//!< Service Completed Successfully - Transaction Accepted.
#define TAG_TRANSACTION_DECLINED					0x0002			//!< Service Completed Successfully - Transaction Declined.
#define	TAG_AUTHORISATION_REQUEST					0x0003			//!< Service Completed Successfully - Online Authorisation Requested.
#define	TAG_REFERRAL_REQUEST						0x0004			//!< Service Completed Successfully - Referral Requested.
#define	TAG_VISA_EASY_ENTRY_CARD					0x0005			//!< Service Completed Successfully - Special Case of Visa Easy Entry Cards.
/* &BEGIN tedt/z3/02/1674/ma EMV2000 specifi for Combo DDA*/
#define	TAG_CDA_FAILED								0x0006			//!< Error during CDA.
#define	TAG_SUSPEND_ENGINE							0x0007			//!< Suspend transaction.
/* &END tedt/z3/02/1674/ma EMV2000 specifi for Combo DDA*/


// Transaction Terminated
#define TAG_TRANSACTION_CANCELLED					0x0010			//!< Transaction terminated - Transaction canceled.
#define TAG_PROCESSING_ERROR						0x0011			//!< Transaction terminated - ICC Protocol error.
#define TAG_CARD_ERROR								0x0012			//!< Transaction terminated - Unexpected Response Code from ICC.
#define	TAG_NOT_ACCEPTED							0x0013			//!< Transaction terminated - Bad Tag given by the card.
#define TAG_ICC_DATA_FORMAT_ERROR					0x0014			//!< Transaction terminated - Format error in a tag value.
#define TAG_MISSING_MANDATORY_ICC_DATA				0x0015			//!< Transaction terminated - Mandatory Data missing in ICC.
#define TAG_ICC_REDUNDANT_DATA						0x0016			//!< Transaction terminated - Redundant Data in ICC.
#define TAG_CARD_BLOCKED							0x0017			//!< Transaction terminated - Card Blocked.
#define TAG_COND_OF_USE_NOT_SATISFIED				0x0018			//!< Transaction terminated - ICC replies Condition of Use not Satisfied to GPO command.
#define TAG_MISSING_MANDATORY_TERM_DATA				0x0019			//!< Transaction terminated - Terminal Parameters Missing.
#define TAG_INTERNAL_ERROR							0x001A			//!< Transaction terminated - Internal Error during Step Processing.
#define TAG_REMOVED_CARD							0x001B			//!< Transaction terminated - Card Removed.
/*&BEGIN FT/06/638/MA : service not allowed in GENAC shall terminate transaction   */
#define TAG_SERVICE_NOT_ALLOWED						0x001C			//!< Transaction terminated - Service Not Allowed.
/*&END FT/06/638/MA : service not allowed in GENAC shall terminate transaction   */

/* Service execution error */
#define	TAG_NOT_ENOUGH_MEMORY						0x0101			//!< Execution Error - Missing Memory.
#define	TAG_WRONG_DEL_INPUT_PARAMETER				0x0102			//!< Execution Error - Bad entry Data.

//! @}		// end of Status.

//! \defgroup automate Cardholder Verification Automate
//! @{
#define  PROPRIETARY_METHOD							0x50			//!< Perform Proprietary method
#define  NO_REMAINING_PIN							52				//!< PIN Try limit Exceeded.
#define  INPUT_PIN_OFF								53				//!< Perform PIN Entry for offline verification.
#define  INPUT_PIN_ON								54				//!< Perform PIN Entry for online verification.
#define  INPUT_PIN_OK								55				//!< PIN entry performed.
#define  NO_INPUT									56				//!< CVM End.
#define  PP_HS										60				//!< Pinpad Out of Service.
#define  CANCEL_INPUT								61				//!< Pin entry cancelled.
#define  TO_INPUT  									62				//!< Time Out during PIN Entry.
#define  REMOVED_CARD				 				63				//!< Card Removed.
#define  ERROR_CARD									64				//!< Card Error.
#define  MORE								 		65				//!< Internal use only.
#define  ERROR_ENC_DATA								66				//!< Error during PIN Encipherment.
#define  INPUT_INCORRECT_PIN                        67              //!< Incorrect Pin Verification
//! @}		// end of automate

//! \defgroup Values of EMV Transaction Types
//! @{
#define TYPE_GOODS_SERVICES     0
#define TYPE_CASH 				1
#define TYPE_CASHBACK 			2
#define TYPE_OTHER   			3
//! @}		// EMV Transaction Types

// Values for TAG_SCHEMAS_KSU
// ----------------------------
#define SCH_NO_FCT									0x00000000		//!< Default Value : No Treatment made by KSU Scheme.
#define SCH_PINCODE_OFFLINE							0x00000001		//!< Bit 1 : Set to 1 for Pincode Offline Treatment by KSU Scheme.

/*& BEGIN Externalisation ODA 									*/
#define IS_EXTERNAL_ODA								0x8000
/*& END															*/


//! \addtogroup IntTags
//! @{

/*& BEGIN SMO/ETU/05/20560/MA   : proprietary method for CVM list   */
#define TAG_SUPPORTED_PROPRIETARY_LIST				0x9f8145		//!< List of proprietary methods supported.
// result of the CVM proprietary method applied
#define TAG_PERFORMED_METHOD						0x9f8146

//! \def TAG_RESULT_PROPRIETARY_METHOD
//! \brief Indicate if CVM proprietary method is successfull
//! Length : 1 byte
//! - TRUE :  method is sucessfull
//! - FALSE : method is erraneous
#define TAG_RESULT_PROPRIETARY_METHOD				0x9f8147



/*& BEGIN SMO/ETU/05/20560/MA   : proprietary method for CVM list   */
/*&BEGIN FT/06/812/MA : Online-only  terminal type clarification: declare SKIP TAC-IAC Default    */
//! \def TAG_SKIP_TAC_IAC_DEFAULT
//! \brief Indicate if TAC/IAC Default processing has to be skipped for an Online only terminal
//! when terminal is unable to succesfully go online. By default (if this parameter does not exist)
//! behaviour is the same as FALSE.
//! Length : 1 byte
//! - TRUE :  skip TAC/IAC Default processing if conditions are gathered.
//! - FALSE : process TAC/IAC Default processing.
#define  TAG_SKIP_TAC_IAC_DEFAULT					0x9f8148
/*&END FT/06/812/MA : Online-only  terminal type clarification: declare SKIP TAC-IAC Default    */

/*& BEGIN FT/937/06/MA : Get transaction Log from ICC for PBOC			   */
#define TAG_TRLOG_RECORD							0x9F819D		//!< Contains a response of command Read_Record of transaction Log of the ICC.
/*& END FT/937/06/MA : Get transaction Log from ICC for PBOC			   */


/*&BEGIN FT 1114/MA : release on taa + Custom parameter / terminal type */
//! \def TAG_SKIP_TAC_IAC_ONLINE
//! \brief Indicate if TAC/IAC Online processing has to be skipped for an Offline only terminal
//! during Terminal Action analysis. By default (if this parameter does not exist)
//! behaviour is the same as TRUE.
//! Length : 1 byte
//! - TRUE :  skip TAC/IAC Online processing if conditions are gathered.
//! - FALSE : process TAC/IAC Online processing.
#define  TAG_SKIP_TAC_IAC_ONLINE					0x9F819E

//! \def TAG_FLOOR_LIMIT_CHECKING
//! \brief Indicate if function Floor Limit Checking in TRM has to be done according
//! particular terminal type.
//! See Book 4 6.4 Conditions for Support of Functions.
//! By default ( if this parameter does not exist ) behaviour is the same as TRUE.
//! Length : 1 byte
//! - TRUE :  processing Floor Limit Checking
//! - FALSE : do not process Floor Limit Checking (if conditions are gathered)
#define  TAG_FLOOR_LIMIT_CHECKING					0x9F819F

//! \def TAG_RANDOM_TRANSACTION_SELECT
//! \brief Indicate if function Velocity Checking in TRM has to be done according
//! particular terminal type.
//! See Book 4 6.4 Conditions for Support of Functions.
//! By default ( if this parameter does not exist ) behaviour is the same as TRUE.
//! Length : 1 byte
//! - TRUE :  processing Random Selection
//! - FALSE : do not process Random Selection Checking (if conditions are gathered)
#define  TAG_RANDOM_TRANSACTION_SELECT				0x9F81A0

//! \def TAG_VELOCITY_CHECKING
//! \brief Indicate if function Velocity Checking in TRM has to be done according
//! particular terminal type.
//! See Book 4 6.4 Conditions for Support of Functions.
//! By default ( if this parameter does not exist ) behaviour is the same as TRUE.
//! Length : 1 byte
//! - TRUE :  processing Velocity Checking
//! - FALSE : do not process velocity Checking (if conditions are gathered)
#define  TAG_VELOCITY_CHECKING						0x9F81A1


//! \def TAG_ODA_PROCESSING
//! \brief Indicate if function Offline Data Authentication has to be done according
//! particular terminal type.
//! See Book 4 6.4 Conditions for Support of Functions.
//! By default ( if this parameter does not exist ) behaviour is the same as TRUE.
//! Length : 1 byte
//! - TRUE :  processing ODA
//! - FALSE : do not process ODA ( if conditions are gathered)
#define  TAG_ODA_PROCESSING							0x9F81A2
/*&END FT 1114/MA : release on TRM + Custom parameter / terminal type */

/*&BEGIN FT 472/MA TRM can be bypassed */
//! \def TAG_TRM_OVERPASS_AIP
//! \brief Indicates if function TRM has to be done even if AIP value does not indicate TRM to do.
//! See book 3 chapter 10.6
//! By default ( if this parameter does not exist ) behaviour is the same as FALSE.
//! Length : 1 byte
//! - TRUE :  perform TRM even if AIP not set
//! - FALSE : else
#define TAG_TRM_OVERPASS_AIP						0x9F81A3

//! \def TAG_SUBSEQUENT_BYPASS_PIN
//! \brief If the terminal supports bypass PIN entry, this tag indicates all other PIN entry methods are also considered bypassed.
//! See Book 4 - Section 6.3.4.3 - PIN Entry Bypass and Book Bulletins - Section SU 48
//! By default ( if this parameter does not exist ) behaviour is the same as FALSE.
//! Length : 1 byte
//! - TRUE :  bypass subsequent PIN entry methods
//! - FALSE : else
#define TAG_SUBSEQUENT_BYPASS_PIN					0x9F81AE

#define TAG_EXTENDED_INFO							0x9F81AF

#define TAG_GEN_AC_CTRL_PARAM						0x9F81B0

#define TAG_MANAGER_SELECT_FUNCTION_PRIORITY		0x9F81B1
#define TAG_MANAGER_TRANSACTION_TYPE				0x9F81B2
#define TAG_MANAGER_ENTRY_TYPE						0x9F81B3
#define TAG_MANAGER_CASH_REGISTER_ID				0x9F81B4
#define TAG_MANAGER_PRIVATE_DATA					0x9F81B5
#define TAG_MANAGER_RESULT_PAN						0x9F81B6

//! \def DATA STORAGE Internal TAGS
#define TAG_DS_INT_SUMMARY_2                    0x9F81C1
#define TAG_DS_INT_SUMMARY_3                    0x9F81C2
#define TAG_DS_INT_BUILDDSDOL					0x9F81C3	

#define TAG_DS_INT_CVM_REQ_LIMIT                0x9F81C6
#define TAG_DS_INT_AC_TYPE						0x9F81C8
#define TAG_DS_INT_INPUT_TERM					0x9F81C9
#define TAG_DS_INT_ODS_INFO_FOR_KERNEL			0x9F81CA
#define TAG_DS_INT_SUMMARY_STATUS				0x9F81CB
#define TAG_DS_INT_IDS_STATUS				    0x9F81CC
#define TAG_DS_INT_DSVN_TERM					0x9F81CD				


//! @}		// end of Internal Tags Definition

//*******************************
//** Service Status Code State **
//*******************************

//! \addtogroup Status
//! @{

/*& BEGIN SMO/ETU/05/20560/MA   : proprietary method for CVM list   */
/* 
// list of proprietary methods supported
#define TAG_SUPPORTED_PROPRIETARY_LIST				0x9f8145
// result of the CVM proprietary method applied
#define TAG_PERFORMED_METHOD						0x9f8146
#define TAG_RESULT_PROPRIETARY_METHOD				0x9f8147
#define PROPRIETARY_METHOD							0x50
*/

/*& END SMO/ETU/05/20560/MA   : proprietary method for CVM list   */

/* Attended Environment */
#define ONLINE_ONLY_ATTENDED_FINANCIAL				0x11
#define ONLINE_ONLY_ATTENDED_MERCHANT				0x21
#define OFFLINE_ONLINE_ATTENDED_FINANCIAL			0x12
#define OFFLINE_ONLINE_ATTENDED_MERCHANT			0x22
#define OFFLINE_ONLY_ATTENDED_FINANCIAL				0x13
#define OFFLINE_ONLY_ATTENDED_MERCHANT				0x23

/* Unattended Environment */
#define ONLINE_ONLY_UNATTENDED_FINANCIAL			0x14
#define ONLINE_ONLY_UNATTENDED_MERCHANT				0x24
#define OFFLINE_ONLINE_UNATTENDED_FINANCIAL			0x15
#define OFFLINE_ONLINE_UNATTENDED_MERCHANT			0x25
#define OFFLINE_ONLY_UNATTENDED_FINANCIAL			0x16
#define OFFLINE_ONLY_UNATTENDED_MERCHANT			0x26

/*&END FT/06/812/MA : see SU #51  Online-only terminals clarifications         */


/*& BEGIN FT/1126/06/MA : Account Type Selection						   */
#define  ACCOUNT_TYPE_DEFAULT						0x00
#define  ACCOUNT_TYPE_SAVINGS						0x10
#define  ACCOUNT_TYPE_CHEQUE_DEBIT					0x20
#define  ACCOUNT_TYPE_CREDIT						0x30
/*& END FT/1126/06/MA : Account Type Selection						   */

/*&BEGIN FT/07/2147/MA : bad comparison between CID and control parameter */
#define TAC_DEFAULT_REJECT							0
#define TAC_DEFAULT_APPROVE							1
/*&END FT/07/2147/MA : bad comparison between CID and control parameter */

//! @}		// Status 

//! @}		// Group_Tag_list

#endif
