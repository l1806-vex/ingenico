/**
 * \file     Common_Kernels_TagInfos.h
 * \brief    This file describes all the tags information used by all Contacless kernels.
 *
 *
 * \author    Ingenico
 * \author    Copyright (c) 2008 Ingenico, rue claude Chappe,\n
 *            07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author    Ingenico has intellectual property rights relating to the technology embodied \n
 *            in this software. In particular, and without limitation, these intellectual property rights may\n
 *            include one or more patents.\n
 *            This software is distributed under licenses restricting its use, copying, distribution, and\n
 *            and decompilation. No part of this software may be reproduced in any form by any means\n
 *            without prior written authorization of Ingenico.
 **/

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#ifndef OPTIONS_RFU
#define OPTIONS_RFU						(0)				/*!< Default RFU options. */
#endif


/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////

//! \addtogroup Tags_Definition
//! @{

//#define TagName					TAG				MinL	MaxL	Option:Source			Encoding		Exclusive			One					RFU					// Description
#define TAG_KERNEL_INFO_9F918400	0x9F918400,		32,		32,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_EXCLUSIVE,	OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_PAYMENT_FLOW_STOP - TAG steps to stop on transaction flow. */
#define TAG_KERNEL_INFO_9F918401	0x9F918401,		36,		36,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_EXCLUSIVE,	OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_PAYMENT_FLOW_CUSTOM - TAG steps to custom on transaction flow. */
#define TAG_KERNEL_INFO_9F918402	0x9F918402,		1,		1,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_EXCLUSIVE,	OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_DEBUG_ACTIVATION - TAG debug activation (active verbose mode with traces). */
#define TAG_KERNEL_INFO_9F918403	0x9F918403,		1,		300,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_DEBUG_TIME - TAG debug time (active measures of steps, cards access, ...). */
#define TAG_KERNEL_INFO_9F918404	0x9F918404,		1,		1,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_EXCLUSIVE,	OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_AUTOMAT_STATE - TAG current automat state for transaction flow. */
#define TAG_KERNEL_INFO_9F918405	0x9F918405,		1,		768,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_PROPRIETARY_TAGS - TAG proprietary tags allowing a ponctual DataBase. */
#define TAG_KERNEL_INFO_9F918406	0x9F918406,		1,		128,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_TRACE_ERROR - TAG trace error (memorise error and associated tags). */
#define TAG_KERNEL_INFO_9F918407	0x9F918407,		2,		2,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_EXCLUSIVE,	OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_STATUS_CODE - TAG status code (Status code value. See Status Code values definition for more information). */
#define TAG_KERNEL_INFO_9F918408	0x9F918408,		1,		1,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_EXCLUSIVE,	OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_CUSTOM_STEP - TAG current transaction flow step to customise. */
#define TAG_KERNEL_INFO_9F918409	0x9F918409,		1,		32,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_ANP,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_APPLICATION_NAME - TAG Application name used in identification of each kernel. */
#define TAG_KERNEL_INFO_9F91840A	0x9F91840A,		2,		5,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_EXCLUSIVE,	OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_APPLICATION_IDENT - TAG Application identifier used in identification of each kernel. */
#define TAG_KERNEL_INFO_9F91840B	0x9F91840B,		2,		2,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_EXCLUSIVE,	OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_APPLICATION_CRC - TAG Application checksum used in identification of each kernel. */
#define TAG_KERNEL_INFO_9F91840C	0x9F91840C,		1,		248,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_IPK_RECOVERED_DATA - Data Recovered from the Issuer Public Key Certificate, as defined in EMV Specification 4.2, Book 2, Table 6.		 */
#define TAG_KERNEL_INFO_9F91840D	0x9F91840D,		1,		248,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_SDA_RECOVERED_DATA - Data Recovered from the SDA, as defined in EMV Specifcation 4.2, Book 2, Table 7.		 */
#define TAG_KERNEL_INFO_9F91840E	0x9F91840E,		1,		248,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_ICC_RECOVERED_DATA - Data Recovered from the ICC Public Key Certificate, as defined in EMV Specification 4.2, Book 2, Table 14.		 */
#define TAG_KERNEL_INFO_9F91840F	0x9F91840F,		1,		248,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_DDA_RECOVERED_DATA - Data Recovered from the DDA, as defined in EMV specification, Book 2, Table 17.		 */
#define TAG_KERNEL_INFO_9F918410	0x9F918410,		1,		1,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_IS_CA_REVOKED - Indicates if the Certificate Authority public key is revoked or not (TRUE if CA is revoked).	 */
#define TAG_KERNEL_INFO_9F918411	0x9F918411,		6,		6,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_LAST_APDU_AND_SW - Last Instruction code, and response (on 1 byte) */
#define TAG_KERNEL_INFO_9F918412	0x9F918412,		4,		4,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_CUMULATED_AMOUNT - cumulated amount = current transaction amount + last transaction amount */
#define TAG_KERNEL_INFO_9F918413	0x9F918413,		1,		1,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_SIGNATURE_REQUESTED - Indicates whether a signature is required or not (TRUE if signature is required) */
#define TAG_KERNEL_INFO_9F918414	0x9F918414,		1,		1,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_IS_PINPAD_FUNCTIONING - Indicates if the PinPad is functioning or not. */
#define TAG_KERNEL_INFO_9F918415	0x9F918415,		1,		1,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_PAN_IN_BLACK_LIST - Indicates if the Card PAN is in the black list or not. */
#define TAG_KERNEL_INFO_9F918416	0x9F918416,		2,		2,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_CARD_TYPE - Indicates the card type (value depends on the kernel defines). */
#define TAG_KERNEL_INFO_9F918417	0x9F918417,		1,		1,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,	OPTIONS_RFU}		/*!< TAG_KERNEL_ONLINE_PIN_REQUESTED - Indicates if online PIN is requested by the kernel or not (TRUE if Online PIN is requested).	 */
#define TAG_KERNEL_INFO_9F918418	0x9F918418,		1,		256,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_CONSTRUCTED_TDOL_VALUE - Value of the constructed TDOL (using terminal data). */
#define TAG_KERNEL_INFO_9F918419	0x9F918419,		1,		256,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_CONSTRUCTED_PDOL_VALUE - Value of the constructed PDOL (using terminal data). */
#define TAG_KERNEL_INFO_9F91841A	0x9F91841A,		1,		256,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_CONSTRUCTED_CDOL1_VALUE - Value of the constructed CDOL1 (using terminal data). */
#define TAG_KERNEL_INFO_9F91841B	0x9F91841B,		1,		256,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_CONSTRUCTED_CDOL2_VALUE - Value of the constructed CDOL2 (using terminal data). */
#define TAG_KERNEL_INFO_9F91841C	0x9F91841C,		1,		256,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_CONSTRUCTED_DDOL_VALUE - Value of the constructed DDOL (using terminal data). */
#define TAG_KERNEL_INFO_9F91841D	0x9F91841D,		2,		64,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_A,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES - List of languages supported by the terminal (concatenation of languages identifiers : for example "enfrde"). Can store until 32 languages identifiers. */
#define TAG_KERNEL_INFO_9F91841E	0x9F91841E,		2,		2,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_A,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_SELECTED_PREFERED_LANGUAGE - Language identifier matching between the card and the terminal (as determined by the language selection). */
#define TAG_KERNEL_INFO_9F91841F	0x9F91841F,		9,		288,	{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_RANGE,		OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_REVOKED_CERTIFICATE_LIST - List of revoked certificates. Each revoked certificate is a concatenation of RID (on 5 bytes), Exponent (on 1 byte) and the serial number (on 3 bytes). 32 revoked keys can be stored in this tag. */
#define TAG_KERNEL_INFO_9F918420	0x9F918420,		1,		1,		{TAG_SOURCE_TERMINAL,	TAG_FORMAT_B,	LENGTH_EXCLUSIVE,	OCCURENCE_SINGLE,   OPTIONS_RFU}		/*!< TAG_KERNEL_LAST_EXECUTED_STEP_INTERRUPTION - Indicates the last executed step  when interruption or cancellation occurs. */
//! @}


/////////////////////////////////////////////////////////////////
//// Glodal Data ////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////
