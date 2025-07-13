/**
 * \file     PayPass3_API.h
 * \brief    This describes the PayPass 3 / C2 kernel API.
 *
 * \author    Ingenico
 * \author    Copyright (c) 2012 Ingenico, rue claude Chappe,\n
 *            07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author    Ingenico has intellectual property rights relating to the technology embodied \n
 *            in this software. In particular, and without limitation, these intellectual property rights may\n
 *            include one or more patents.\n
 *            This software is distributed under licenses restricting its use, copying, distribution, and\n
 *            and decompilation. No part of this software may be reproduced in any form by any means\n
 *            without prior written authorization of Ingenico.
 **/

#include "PayPass_API_Common.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global definition //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

//! \brief This structure defines parameters used to customise steps of data exchange processing (if required). 
typedef struct
{
	unsigned short usApplicationType;	            					/*!< Application type to call to perform customisation. */
	unsigned short usServiceId; 		            					/*!< Service Id to call to perform customisation. */
} T_PAYPASS_DATA_EXCHANGE_CUSTOM;


/////////////////////////////////////////////////////////////////
//// Global Data ///////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup PayPass3InterfaceFunctions
//! @{

//! \brief This function performs the PayPass transaction with the presented card (MChip or MStripe).
//!	All the necessary data to perform the transaction shall be provided.
//! This function shall be called after the application selection (PPSE performed and Final SELECT response and status word provided).
//!	It begins by analysing the provided Final SELECT response and Status cord and perform the transaction until completion.
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel. 
//!	This shared buffer shall be initialised using the \ref GTL_SharedExchange_InitShared() function 
//! (please refer to GTL documentation for more information).
//!	- Input data list (bold ones are mandatory or highly recommended)
//!		- \ref TAG_EP_FINAL_SELECT_COMMAND_SENT : Final SELECT command (for internal PayPass mandatory checkings).
//!		- \ref TAG_EP_FINAL_SELECT_RESPONSE : Final SELECT response provided by the application selection. It will be analysed by the PayPass kernel itself. Note if this data is not provided to the kernel, the the kernel will request to select the next available AID.
//!		- \ref TAG_EP_FINAL_SELECT_STATUS_WORD : Final SELECT response status word provided by the application selection. Note that this is the role of the application to indicate the AID removal if final SELECT SW is not x9000.
//!		- \ref TAG_EMV_TRANSACTION_DATE : Transaction date.
//!		- \ref TAG_EMV_TRANSACTION_TIME : Transaction time.
//!		- \ref TAG_EMV_AMOUNT_AUTH_NUM : Amount Authorised, Numeric format. Note this is possible to provide it during the transaction processing (for specific needs), but we recommand to provide it on this function call.
//!		- \ref TAG_EMV_TRANSACTION_CURRENCY_CODE : Transaction currency code.
//!		- \ref TAG_EMV_TRANSACTION_TYPE : Transaction type.
//!		- \ref TAG_EMV_INT_TRANSACTION_TYPE : Internal transaction type (managed by the application, and used by the kernel).
//!		- \ref TAG_EMV_IFD_SERIAL_NUMBER : Payment interface serial number.
//!		- \ref TAG_EMV_TERMINAL_COUNTRY_CODE : Terminal country code. If it is not provided, the kernel will set the default value to '0000'.
//!		- \ref TAG_EMV_ADD_TERMINAL_CAPABILITIES : Terminal Additional Capabilities. If it is not provided, the kernel will set the default value to '0000000000'.
//!		- \ref TAG_EP_CLESS_FLOOR_LIMIT : Reader Contactless Floor limit for the chosen AID (used for M/Chip only). If it is not provided, the kernel will set the default value to '000000000000'.
//!		- \ref TAG_EP_CLESS_CVM_REQUIRED_LIMIT : Contactless CVM required limit for the chosen AID. If it is not provided, the kernel will set the default value to '000000000000'.
//!		- \ref TAG_PAYPASS_MSTRIPE_APPLI_VERSION_NUMBER_TERM : Terminal Application version number supported for MStripe cards for this AID. If it is not provided, the kernel will set the default value to '0001'.
//!		- \ref TAG_EMV_APPLI_VERSION_NUMBER_TERM : Terminal Application version number supported for MChip cards for this AID. If it is not provided, the kernel will set the default value to '0002'.
//!		- \ref TAG_EMV_TERMINAL_TYPE : Terminal Type (M/Chip only). If it is not provided, the kernel will set the default value to '00'.
//!		- \ref TAG_EMV_INT_TAC_DEFAULT : Terminal Action Code Default (used for M/Chip only). If it is not provided, the kernel will set the default value to 'CC00000000'.
//!		- \ref TAG_EMV_INT_TAC_DENIAL : Terminal Action Code Denial (used for M/Chip only). If it is not provided, the kernel will set the default value to '0000000000'.
//!		- \ref TAG_EMV_INT_TAC_ONLINE : Terminal Action Code Online (used for M/Chip only). If it is not provided, the kernel will set the default value to 'CC00000000'.
//!		- \ref TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_NO_DCV : Reader Cless Transaction Limit (if card is presented, i.e. No On-Device CVM). If it is not provided, the kernel will set the default value to '000000000000'.
//!		- \ref TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_DCV : Reader Cless Transaction Limit (if device capable of processing CVM is presented, i.e. On-Device CVM). If it is not provided, the kernel will set the default value to '000000000000'.
//!		- \ref TAG_PAYPASS_DEFAULT_UDOL : Default UDOL (only necessary for M/Stripe transactions).
//!		- \ref TAG_PAYPASS_INT_SUPPORTED_CAPK_INDEX_LIST : List of CA keys supported for the chosen AID (used only for M/Chip only).
//!		- \ref TAG_PAYPASS_KERNEL_CONFIGURATION : Indicates the kernel configuration. If it is not provided, the kernel will set the default value to '00'.
//!		- \ref TAG_PAYPASS_CARD_DATA_INPUT_CAPABILITY :Card Data Input Capabilities. If it is not provided, the kernel will set the default value to '00'.
//!		- \ref TAG_PAYPASS_SECURITY_CAPABILITY : Security Capabilities. If it is not provided, the kernel will set the default value to '00'.
//!		- \ref TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_REQUIRED : M/Chip CVM capabilities if CVM is required. If it is not provided, the kernel will set the default value to '00'.
//!		- \ref TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_NOT_REQUIRED : M/Chip CVM Capabilities if CVM is not required. If it is not provided, the kernel will set the default value to '00'.
//!		- \ref TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_REQUIRED : M/Stripe CVM capabilities if CVM is required. If it is not provided, the kernel will set the default value to 'F0'.
//!		- \ref TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_NOT_REQUIRED : M/Stripe CVM capabilities if CVM is not required. If it is not provided, the kernel will set the default value to 'F0'.
//!		- \ref TAG_PAYPASS_DEFAULT_HOLD_TIME : Message Hold Time. If it is not provided, the kernel will set the default value to '000013'.
//!		- \ref TAG_PAYPASS_TIME_OUT_VALUE : Tmiout Value (used with DE/DS only). If it is not provided, the kernel will set the default value to '01F4'.
//!		- \ref TAG_PAYPASS_MAX_LIFETIME_OF_TORN_TXN_LOG_RECORD : Max Lifetime of Torn Transaction Log Record (only used with Torn feature). If it is not provided, the kernel will set the default value to '012C'.
//!		- \ref TAG_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS : Max number of Torn Transaction Log Records (only used with Torn feature). If it is not provided, the kernel will set the default value to '00'.
//!		- <dfn>\ref TAG_EMV_AMOUNT_OTHER_NUM</dfn> : Amount Other, Numeric format. This tag is optional but shall be provided for transactions with cashback.
//!		- <dfn>\ref TAG_PAYPASS_INT_MERCHANT_FORCE_ONLINE</dfn> : Indicate the merchant would like to force the transaction online (set TVR B4b4).
//!		- <dfn>\ref TAG_EP_KERNEL_TO_USE</dfn> : Kernel to be used (for PayPass, it shall be set to \a DEFAULT_EP_KERNEL_PAYPASS).
//!		- <dfn>\ref TAG_EMV_ACQUIRER_IDENTIFIER</dfn> : Acquirer identifier.
//!		- <dfn>\ref TAG_EMV_MERCHANT_CATEGORY_CODE</dfn>	: Merchant category code.
//!		- <dfn>\ref TAG_EMV_MERCHANT_IDENTIFIER</dfn> : Merchant identifier.
//!		- <dfn>\ref TAG_EMV_TERMINAL_IDENTIFICATION</dfn> : Terminal identification.
//!		- <dfn>\ref TAG_PAYPASS_TRANSACTION_CATEGORY_CODE</dfn> : PayPass merchant category code.
//!		- <dfn>\ref TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES</dfn> : Supported language for the chosen AID.
//!		- <dfn>\ref TAG_KERNEL_PAYMENT_FLOW_STOP</dfn> : Data field indicating steps where the transaction flow has to be stopped. It is strongly recommended, for transaction performances purposes, to not interrupt the transaction flow using this way (recommended value is all set to 0).
//!		- <dfn>\ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM</dfn> : Data field indicating steps where customisation is necessary.
//!		- <dfn>\ref TAG_KERNEL_PROPRIETARY_TAGS</dfn> : Description of the proprietary tags that shall be considered as known by the kernel. Note that every proprietary tag declared will be initialised as "empty" in the kernel database (i.e. present with zero length, no value), except if the tag is present in the input data (i.e. it will be stored in the database).
//!		- <dfn>\ref TAG_PAYPASS_BALANCE_READ_BEFORE_GENAC</dfn> : If you would like to read the card balance before GenAC, you have to provide this tag to the kernel with zero length (i.e. no value)(used for M/Chip only).
//!		- <dfn>\ref TAG_PAYPASS_BALANCE_READ_AFTER_GENAC</dfn> : If you would like to read the card balance after GenAC, you have to provide this tag to the kernel with zero length (i.e. no value)(used for M/Chip only).
//!		- <dfn>\ref TAG_PAYPASS_INT_PHONE_MESSAGE_TABLE</dfn> : If the application needs to redefine its own Phone Message Table.
//!		- <dfn>\ref TAG_PAYPASS_DATA_EXCHANGE_CUSTOM</dfn> : Indicates the service call for DEK management.
//!	- Output data returned by the PayPass kernel
//!		- \ref TAG_PAYPASS_OUTCOME_PARAMETER_SET : Outcome Parameter Set indicating the status of the transaction.
//!		- \ref TAG_PAYPASS_DISCRETIONARY_DATA : Tag containing some data, depending on the transaction performed. It consists of :
//!			- For a M/Chip transaction running to completion :
//!				- \ref TAG_PAYPASS_ERROR_INDICATION : Error Indication (always).
//!				- \ref TAG_EMV_APPLI_CURRENCY_CODE : Application Currency Code (if present).
//!				- \ref TAG_PAYPASS_THIRD_PARTY_DATA : PayPass Third Party Data (if present).
//!				- \ref TAG_PAYPASS_BALANCE_READ_BEFORE_GENAC : Balance Read Before Generate AC (if balance reading feature supported, i.e. this tag has been provided with zero length and card supports balance).
//!				- \ref TAG_PAYPASS_BALANCE_READ_AFTER_GENAC : Balance Read After Generate AC (if balance reading feature supported, i.e. this tag has been provided with zero length and card supports balance).
//!				- \ref TAG_PAYPASS_TORN_RECORD : Torn Record of the current torn transaction with DS processing that has failed (only returned in the DE/DS specific cases).
//!				- \ref TAG_PAYPASS_OLD_TORN_RECORD : If the torn was full and a new record has been added. It corresponds to the torn record removed from the torn log.
//!				- \ref TAG_PAYPASS_POST_GENAC_PUT_DATA_STATUS : Post GenAC PUT DATA Status (if DE/DS used only, and PUT DATA after GenAC are performed).
//!				- \ref TAG_PAYPASS_PRE_GENAC_PUT_DATA_STATUS : Post GenAC PUT DATA Status (if DE/DS used only, and PUT DATA before GenAC are performed).
//!				- \ref TAG_PAYPASS_INT_DS_SUMMARY_3 : DS Summary 3 (only if DS is used).
//!				- \ref TAG_PAYPASS_INT_DS_SUMMARY_STATUS : DS Summary Status (only if DS is used).
//!			- For a M/Stripe transaction running to completion :
//!				- \ref TAG_PAYPASS_ERROR_INDICATION : Error Indication (always).
//!				- \ref TAG_PAYPASS_THIRD_PARTY_DATA : PayPass Third Party Data (if present).
//!				- \ref TAG_PAYPASS_DD_CARD_TRACK1 : Track 1 Discretionnary Data (if present).
//!				- \ref TAG_PAYPASS_DD_CARD_TRACK2 : Track 2 Discretionnary Data.
//!			- Else (error occurred, other cases) :
//!				- \ref TAG_PAYPASS_ERROR_INDICATION : Error Indication (always).
//!		- \ref TAG_KERNEL_CARD_TYPE : Card type (refer to \ref PayPassPossibleCardTypes for more information about the possible values).
//!		- \ref TAG_PAYPASS_DATA_RECORD : Data record containing th etransaction (only returned if the transaction runs to completion) :
//!			- For M/Chip transaction :
//!				- \ref TAG_EMV_AMOUNT_AUTH_NUM : Amount, Authorised (Numeric).
//!				- \ref TAG_EMV_AMOUNT_OTHER_NUM : Amount, Other (Numeric).
//!				- \ref TAG_EMV_APPLICATION_CRYPTOGRAM : Application Cryptogram.
//!				- \ref TAG_EMV_APPLI_EXPIRATION_DATE : Application Expiration Date.
//!				- \ref TAG_EMV_AIP : Application Interchange Profile.
//!				- \ref TAG_EMV_APPLICATION_LABEL : Application Label (if present).
//!				- \ref TAG_EMV_APPLI_PAN : Application PAN.
//!				- \ref TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER : Application PAN Sequence Number (if present).
//!				- \ref TAG_EMV_APPLI_PREFERED_NAME : Application Preferred Name (if present).
//!				- \ref TAG_EMV_ATC : Application Transaction Counter.
//!				- \ref TAG_EMV_APPLI_VERSION_NUMBER_TERM : Application Version Number (Reader).
//!				- \ref TAG_EMV_CRYPTOGRAM_INFO_DATA : Cryptogram Information Data.
//!				- \ref TAG_EMV_CVM_RESULTS : CVM Results.
//!				- \ref TAG_EMV_DF_NAME : DF Name.
//!				- \ref TAG_EMV_IFD_SERIAL_NUMBER : Device Serial Number.
//!				- \ref TAG_EMV_ISSUER_APPLI_DATA : Issuer Application Data.
//!				- \ref TAG_EMV_ISSUER_CODE_TABLE_INDEX : Issuer Code Table Index (if present).
//!				- \ref TAG_EMV_TERMINAL_CAPABILITIES : Terminal Capabilities.
//!				- \ref TAG_EMV_TERMINAL_COUNTRY_CODE : Terminal Country Code.
//!				- \ref TAG_EMV_TERMINAL_TYPE : Terminal Type.
//!				- \ref TAG_EMV_TVR : Terminal Verification Results.
//!				- \ref TAG_EMV_TRACK_2_EQU_DATA : Track 2 Equivalent Data.
//!				- \ref TAG_PAYPASS_TRANSACTION_CATEGORY_CODE : Transaction Category Code (if present).
//!				- \ref TAG_EMV_TRANSACTION_CURRENCY_CODE : Transaction Currency Code.
//!				- \ref TAG_EMV_TRANSACTION_DATE : Transaction Date.
//!				- \ref TAG_EMV_TRANSACTION_TYPE : Transaction Type.
//!				- \ref TAG_EMV_UNPREDICTABLE_NUMBER : Unpredictable Number.
//!			- For M/Stripe transaction :
//!				- \ref TAG_EMV_APPLICATION_LABEL : Application Label (if present).
//!				- \ref TAG_EMV_APPLI_PREFERED_NAME : Application Preferred Name (if present).
//!				- \ref TAG_EMV_DF_NAME : DF Name.
//!				- \ref TAG_EMV_IFD_SERIAL_NUMBER : Device Serial Number.
//!				- \ref TAG_EMV_ISSUER_CODE_TABLE_INDEX : Issuer Code Table Index (if present).
//!				- \ref TAG_PAYPASS_MSTRIPE_APPLI_VERSION_NUMBER_TERM : M/Stripe Application Version Number (Reader).
//!				- \ref TAG_PAYPASS_TRACK1_DATA : Track 1 Data (if present).
//!				- \ref TAG_PAYPASS_TRACK2_DATA : Track 2 Data.
//!		- \ref TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA : Optional Data returned to indicate GUI to be displayed at the end of the transaction.
//! \return Kernel processing status code (<b>shall only be used for debug purpose</b>). The \ref TAG_PAYPASS_OUTCOME_PARAMETER_SET tag content shall be used to determine the transaction outcome.
//! - \ref KERNEL_STATUS_OFFLINE_APPROVED : Transaction succeeded and is offline approved. This status is also returned when a refund transaction is performed and has succeeded, whatever the card type (M/Chip or M/Stripe cards).
//!	- \ref KERNEL_STATUS_OFFLINE_DECLINED : Transaction is offline declined.
//!	- \ref KERNEL_STATUS_ONLINE_AUTHORISATION : Transaction succeeded and has to be sent online for authorisation.
//!	- \ref KERNEL_STATUS_CANCELLED : if transaction has been cancelled by the custom application (using \a PayPass3_Cancel() function).
//!	Take care that when transaction is cancelled by the user, status code returned is (\ref KERNEL_STATUS_CANCELLED | \ref KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK).
//!	- \ref KERNEL_STATUS_COMMUNICATION_ERROR : if a communication error occurred with the card (no response to a command because card has been to early removed for example).
//!	- \ref KERNEL_STATUS_INVALID_INPUT_DATA : if provided data in \a pDataStruct are not correct.
//!	- \ref KERNEL_STATUS_ICC_MISSING_DATA : if mandatory ICC data is missing.
//!	- \ref KERNEL_STATUS_ICC_INVALID_DATA : if ICC returned an invalid data.
//!	- \ref KERNEL_STATUS_ICC_REDUNDANT_DATA : if ICC returned a redundant data.
//!	- \ref KERNEL_STATUS_ICC_DATA_FORMAT_ERROR : if ICC returned data with bad format.
//!	- \ref KERNEL_STATUS_TERM_MISSING_DATA : A mandatory terminal is missing to perform the transaction.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR : A database error occurred.
//!	- \ref KERNEL_STATUS_UNKNOWN_SW : ICC responded to a command with an unexpected status word and transaction is terminated.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY : there is not enough memory to perform the transaction.
//!	- \ref KERNEL_STATUS_INTERNAL_ERROR : An internal kernel error occurred (would never occur).
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the PayPass kernel is not loaded in the terminal or if the requested service does not exists.
//!	- \ref PAYPASS_STATUS_MSTRIPE_NOT_ALLOWED : Indicates that the M/Stripe profile is not allowed and the transaction is terminated.
//!	- \ref PAYPASS_STATUS_NO_TRANSACTION_AMOUNT : Indicates that the transaction amount is missing, and the transaction cannot continue.
//!	- \ref PAYPASS_STATUS_TIMEOUT_OCCURRED : Only when Data Exchange mechanism is used. Indicates that the kernel was waiting for some data from the application that does not arrived. So transaction is terminated.
//!	- \ref PAYPASS_STATUS_IDS_ERROR : Indicates an IDS error occurred.
//! \note If the transaction is suspended by the application, the returned status code is (\a status \a code | \ref KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK).
//!	If transaction is interrupted by the user, the kernel database is not altered to allow continuing the transaction 
//!	anyway if requested (using \ref PayPass3_ResumeTransaction() function).

int PayPass3_DoTransaction (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to resume the transaction when an interruption occurred (requested interruption).
//! The transaction will continue where it has been interrupted.
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//!	- Input data can be provided. It will replace each existing data within the kernel database.
//!	- Output data are the same as \ref PayPass3_DoTransaction() function (as it continues the transaction).
//! \return Kernel processing status code (identical than the \ref PayPass3_DoTransaction() function).

int PayPass3_ResumeTransaction (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to retrieve the entire kernel database.
//! All the tags present in the database are retrieved.
//! \param[out] pDataStruct Shared buffer filled with all the kernel data. Note that the notion of "empty tag" exists with Kernel C2. In this case, the tag is returned with a zero length (i.e. no value).
//! Make sure the buffer size you provide is bigger enough to store all the tags.
//! Note the shared buffer is automatically cleared by the PayPass kernel.
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if all the data are provided and no error occurred.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the PayPass kernel is not loaded in the terminal or if the requested service does not exists.
//! \note Warning : It is strongly recommended to not call this function during the transaction flow, as it should impact the transaction performance.

int PayPass3_GetAllData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to request kernel some tags (if present in its database).
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel. 
//! Make sure the buffer size you provide is bigger enough to store all the tags.
//! Note the shared buffer is automatically cleared by the PayPass kernel.
//!	- Input data : Tag to be requested to the kernel. It is a concatenation of tags and length set to 0.
//! - Output data : list of retrieved data (coded in BER-TLV) that have been requested and that are present in the kernel database. Note that the notion of "empty tag" exists with Kernel C2. In this case, the tag is returned with a zero length (i.e. no value).
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if all the data are provided and no error occurred.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the PayPass kernel is not loaded in the terminal or if the requested service does not exists.
//! \note It is strongly recommended to not call this function during the transaction flow, as it should impact the transaction performance.
//! \remarks Example to get the transaction date and the transaction time from the PayPass kernel :
//! \code
//!	T_SHARED_DATA_STRUCT * pSharedDataStruct;
//!	
//!	// Initialise the shared buffer to be used (if not already done).
//!	// Make sure size is bigger enough.
//!	pSharedDataStruct = GTL_SharedExchange_InitShared (256);
//!
//!	if (pSharedDataStruct == NULL)
//!	{
//!		// An error occurred when creating the shared data structure.
//!		...
//!	}
//!	
//!	// Add TAG_EMV_TRANSACTION_DATE tag in pSharedDataStruct with a zero length.
//!	ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_EMV_TRANSACTION_DATE, 0, NULL);
//!	// Check returned value ...
//!	
//!	// Add TAG_EMV_TRANSACTION_TIME tag in pSharedDataStruct with a zero length.
//!	ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_EMV_TRANSACTION_TIME, 0, NULL);
//!	// Check returned value ...
//!	
//!	// Call the PayPass kernel to retrieve the requested tags.
//!	nResult = PayPass3_GetData (pSharedDataStruct);
//!	if (nResult != KERNEL_STATUS_OK)
//!	{
//!		// An error occurred when requesting tags to the kernel.
//!		// ...
//!	}
//!	
//!	// Now, pSharedDataStruct contains the requested tags (only the ones that are present within the kernel database)
//!	// You can use GTL_SharedExchange_GetNext and GTL_SharedExchange_FindNext functions to retrieve the desired tags.
//!	// ...
//!	
//!	// If created, destroy the shared buffer if not used anymore
//!	if (pSharedDataStruct != NULL)
//!		GTL_SharedExchange_DestroyShare (pSharedDataStruct);
//! \endcode

int PayPass3_GetData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Function to be used to load some data within the kernel.
//! \param[in] pDataStruct Shared buffer filled with the data to be loaded into the kernel.
//!	- \a pDataStruct is filled using the \a GTL_SharedExchange_AddTag() function.
//!	- All the tags that are unknown by the kernel are ignored.
//!	- If a tag is added with a zero length, it will be added as empty.
//!	- If a provided tag is already present in the database, this one will be replaced by the new value.
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if tags correctly added in the kernel database and no error occurred.
//!	- \ref KERNEL_STATUS_INVALID_INPUT_DATA : if provided data in \a pDataStruct are not correct.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in the kernel database to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the PayPass kernel is not loaded in the terminal or if the requested service does not exists.
//! \note It is strongly recommended to not call this function during the transaction flow, as it should impact the transaction performance.
//! \remarks Example to load the transaction date and the transaction time from the PayPass kernel :
//! \code
//!	T_SHARED_DATA_STRUCT * pSharedDataStruct;
//!	unsigned char ucTransactionDate[] = {0x09,0x09,0x09}; // September 9th of 2009
//!	
//!	// Initialise the shared buffer to be used (if not already done).
//!	// Make sure size is bigger enough.
//!	pSharedDataStruct = GTL_SharedExchange_InitShared (256);
//!
//!	if (pSharedDataStruct == NULL)
//!	{
//!		// An error occurred when creating the shared data structure.
//!		...
//!	}
//!	
//!	// Add transaction date in pSharedDataStruct (if tag already present in the database, this one will be replaced by the one sent here).
//!	ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_EMV_TRANSACTION_DATE, 3, ucTransactionDate);
//!	// Check returned value ...
//!	
//!	// Add transaction time tag in pSharedDataStruct with a zero length (to indicate you want to add it as empty).
//!	ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_EMV_TRANSACTION_TIME, 0, NULL);
//!	// Check returned value ...
//!	
//!	// Call the PayPass kernel to load the tags.
//!	nResult = PayPass3_LoadData (pSharedDataStruct);
//!	if (nResult != KERNEL_STATUS_OK)
//!	{
//!		// An error occurred when requesting tags to the kernel.
//!		// ...
//!	}
//!	
//!	// Tags has been correctly loaded in the kernel database
//!	// ...
//!	
//!	// If created, destroy the shared buffer if not used anymore
//!	if (pSharedDataStruct != NULL)
//!		GTL_SharedExchange_DestroyShare (pSharedDataStruct);
//! \endcode

int PayPass3_LoadData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function can be used to cancel the PayPass transaction.
//! We could imagine using it to cancel the transaction when the red key is pressed during the PayPass transaction for example.
//! \return Always \ref KERNEL_STATUS_OK.
//! \note This is the responsibility of the custom application to correctly use this function. 
//! The PayPass transaction can be cancelled at any step.
//! If called, the kernel will return \ref KERNEL_STATUS_CANCELLED on the following functions :
//!	- \ref PayPass3_DoTransaction().
//!	- \ref PayPass3_ResumeTransaction().
//! \note The PayPass transaction can be aborted by the application until the last command before the GenAC or CCC has been sent. After that, transaction abort is no more possible and transaction will run to completion.

int PayPass3_Cancel (void);



//! \brief This function allows to manage the PayPass kernel debug features.
//! This allows activating / deactivating the following debug features :
//!	- Trace : it provides debug information in the \a Trace.exe tool provided in the TDS.
//!	- Time measurements : it manages in the database the \ref TAG_KERNEL_DEBUG_TIME tag that can be retrieved using \ref PayPass3_GetData() function).
//!	Note if Time debug feature is not activated, \ref TAG_KERNEL_DEBUG_TIME tag is not stored in the kernel database.
//!	- APDU storage : it stores all the APDU sent to the ICC and responses sent by the ICC in the database, using specific tags. 
//!	This concerns commands from GPO command to the CCC command (for MStripe) or Generate AC command (for MChip cards).
//!	Each command is stored in a \ref TAG_PAYPASS_INT_SENT_APDU tag, each received ICC response is stored in a \ref TAG_PAYPASS_INT_CARD_RESPONSE tag.
//!	- Data Exchange storage : it stores all the DE signals in the database. Each DEK is stored into a \ref TAG_PAYPASS_INT_DEK_SIGNAL and the DET into 
//!	a \ref TAG_PAYPASS_INT_DET_SIGNAL.
//! \param[in] pDataStruct Shared buffer filled with the \ref TAG_KERNEL_DEBUG_ACTIVATION tag indicating the debug mode.
//!	If the tag is not present or set to 0, then all the debug features are deactivated.
//!	Else, the following masks can be used :
//!	- \ref KERNEL_DEBUG_MASK_TRACES : to activate the traces.
//!	- \ref KERNEL_DEBUG_MASK_APDU : to activate the APDU logging.
//!	- \ref PAYPASS_DEBUG_MASK_DE_LOG : to activate the DE logging.
//! \return
//!	- \ref KERNEL_STATUS_OK if debug mode correctly activated / deactivated.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the PayPass kernel is not loaded in the terminal or if the requested service does not exists.
//!	
//!	\note If debug features shall be activated, it is strongly recommended to call this function before the transaction has started.
//!	It allows to not waste time during the transaction (performances purposes).
//! \note The \ref KERNEL_DEBUG_KERNEL_SPECIFIC_2 mask is used for PayPass to log the DE exchanges into the kernel (please use the \ref PAYPASS_DEBUG_MASK_DE_LOG define)
//! \remarks Example to set the debug mode :
//! \code
//!	T_SHARED_DATA_STRUCT * pSharedDataStruct;
//!	unsigned char ucTraceOnly = KERNEL_DEBUG_MASK_TRACES;	// Trace only is activated
//!	unsigned char ucApduOnly = KERNEL_DEBUG_MASK_APDU; // APDU is activated
//!	unsigned char ucTracesAndApdu = (KERNEL_DEBUG_MASK_TRACES | KERNEL_DEBUG_MASK_APDU); // Traces and APDU debug features are activated.
//!	unsigned char ucApduAndDeLog = (KERNEL_DEBUG_MASK_APDU | PAYPASS_DEBUG_MASK_DE_LOG); // APDU and DE log features are activated.
//!	
//!	// Initialise the shared buffer to be used (if not already done).
//!	// Make sure size is bigger enough.
//!	pSharedDataStruct = GTL_SharedExchange_InitShared (128);
//!
//!	if (pSharedDataStruct == NULL)
//!	{
//!		// An error occurred when creating the shared data structure.
//!		...
//!	}
//!	
//!	// Indicate Traces Only has to be activated.
//!	ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_KERNEL_DEBUG_ACTIVATION, 1, &ucTraceOnly);
//!	// Check returned value ...
//!	
//!	// Call the PayPass kernel to set the debug mode.
//!	nResult = PayPass3_DebugManagement (pSharedDataStruct);
//!	if (nResult != KERNEL_STATUS_OK)
//!	{
//!		// An error occurred when requesting tags to the kernel.
//!		// ...
//!	}
//!	
//!	// Indicate Traces Only has to be activated.
//!	ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_KERNEL_DEBUG_ACTIVATION, 1, &ucApduOnly);
//!	// Check returned value ...
//!	
//!	// Call the PayPass kernel to load the tags.
//!	nResult = PayPass3_DebugManagement (pSharedDataStruct);
//!	if (nResult != KERNEL_STATUS_OK)
//!	{
//!		// An error occurred when requesting tags to the kernel.
//!		// ...
//!	}
//!	
//!	// At this step, only APDU is activated (trace has been deactivated).
//!	// If you want to activate both Traces and APDU, send TAG_KERNEL_DEBUG_ACTIVATION = ucTracesAndApdu.
//!	// ...
//!	
//!	// If created, destroy the shared buffer if not used anymore
//!	if (pSharedDataStruct != NULL)
//!		GTL_SharedExchange_DestroyShare (pSharedDataStruct);
//! \endcode

int PayPass3_DebugManagement (T_SHARED_DATA_STRUCT * pDataStruct);



//!	\brief This function clears and initialise the PayPass kernel.
//! It fully clear the database and restores the global data (reset cancel, deactivate debug features, etc). 
//! <b>It is mandatory to call this function after each PayPass transaction has been completed (and the terminal 
//! is returning on idle state).</b>
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if PayPass kernel correctly cleared and initialised.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the PayPass kernel is not loaded in the terminal or if the requested service does not exists.

int PayPass3_Clear (void);



//! \brief This function gets the kernel information.
//! \param[out] pDataStruct Shared buffer filled with the following tags (note this buffer is automatically cleared by the function) :
//!	- \ref TAG_KERNEL_APPLICATION_NAME that indicates the application name (ASCII format).
//!	- \ref TAG_KERNEL_APPLICATION_IDENT that indicates the kernel identifier (in ASCII format, \a 4241XXXX where XXXX is the PayPass kernel version on 4 digits).
//!	- \ref TAG_KERNEL_APPLICATION_CRC that indicates the PayPass kernel CRC.
//! \return
//!	- \ref KERNEL_STATUS_OK if kernel information correctly retrieved.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_INTERNAL_ERROR if an internal error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR if a library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE if the PayPass kernel is not loaded in the terminal or if the requested service does not exists.

int PayPass3_GetInfos (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Function to be used to send a single Data Exchange (DET) Signal to the kernel.
//! \param[in] pDataStruct Shared buffer filled with the data to be loaded into the kernel.
//!	- \a pDataStruct is filled with the DET Signal data.
//!	- The kernel will update the \ref TAG_PAYPASS_INT_DS_TAGS_TO_READ_YET with the data in the \ref TAG_PAYPASS_DS_TAGS_TO_READ buffer.
//!	- The kernel will update the \ref TAG_PAYPASS_DS_TAGS_TO_WRITE_YET_BEFORE_GENAC with the data in the \ref TAG_PAYPASS_DS_TAGS_TO_WRITE_BEFORE_GENAC buffer.
//!	- The kernel will update the \ref TAG_PAYPASS_DS_TAGS_TO_WRITE_YET_AFTER_GENAC with the data in the \ref TAG_PAYPASS_DS_TAGS_TO_WRITE_AFTER_GENAC buffer.
//!	- If a provided tag is already present in the database, this one will be replaced by the new value.
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if tags correctly added in the kernel database and no error occurred.
//!	- \ref KERNEL_STATUS_INVALID_INPUT_DATA : if provided data in \a pDataStruct are not correct.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in the kernel database to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the PayPass kernel is not loaded in the terminal or if the requested service does not exists.
//! \note It is strongly recommended that this function is only used when a more than one DET signal is required as it will impact transaction performance.
//! If only one DET Signal is required to the kernel DEK Signal then the application does not need to use this function and can simply return the data to the original kernel ServiceCall.

int PayPass3_DETSignal (T_SHARED_DATA_STRUCT * pDataStruct);



//! @}
