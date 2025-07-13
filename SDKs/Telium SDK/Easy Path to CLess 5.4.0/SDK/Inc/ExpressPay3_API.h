/**
 * \file     ExpressPay3_API.h
 * \brief    This describes the ExpressPay 3 kernel API.
 *
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

#include "ExpressPay_API_Common.h"

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global definition //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Glodal Data ///////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup ExpressPay3InterfaceFunctions
//! @{

//! \brief This function performs the ExpressPay transaction with the presented card/mobile.
//!	All the necessary data to perform the transaction shall be provided.
//! This function shall be called after the application selection (PPSE performed and Final SELECT response and status word provided).
//!	It begins by analysing the provided Final SELECT response and Status Word and perform the transaction until completion.
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel. 
//!	This shared buffer shall be initialised using the \ref GTL_SharedExchange_InitShared() function 
//! (please refer to GTL documentation for more information).
//!	- Input data list (bold ones are mandatory or highly recommended)
//!		- \ref TAG_EXPRESSPAY_UNPREDICTABLE_NUMBER_RANGE : Unpredictable number range.
//!		- \ref TAG_EXPRESSPAY_INT_TERMINAL_AVN_LIST : Terminal Application version number supported for ExpressPay cards for this AID.
//!		- <dfn>\ref TAG_EXPRESSPAY_TERMINAL_CAPABILITIES : Specific ExpressPay terminal capabilities.
//!		- \ref TAG_EXPRESSPAY_TERMINAL_TRANSACTION_CAPABILITIES : Data for managing ExpressPay transactions.
//!		- \ref TAG_EXPRESSPAY_MOBILE_TRANSACTION_RESTARTED : set to 1 to indicates that the transaction is restarted after Mobile CVM has been performed (second tap).
//!		- \ref TAG_EXPRESSPAY_INT_SUPPORTED_CAPK_INDEX_LIST : List of CA keys supported for the chosen AID.
//!		- \ref TAG_EMV_TRANSACTION_DATE : Transaction date.
//!		- \ref TAG_EMV_TRANSACTION_TIME : Transaction time.
//!		- \ref TAG_EMV_AMOUNT_AUTH_BIN : Amount Authorised, Binary format. Take care to be coherent with the provided value in \ref TAG_EMV_AMOUNT_AUTH_NUM. No verification will be performed by the kernel itself.
//!		- \ref TAG_EMV_AMOUNT_AUTH_NUM : Amount Authorised, Numeric format. Take care to be coherent with the provided value in \ref TAG_EMV_AMOUNT_AUTH_BIN. No verification will be performed by the kernel itself.
//!		- <dfn>\ref TAG_EMV_AMOUNT_OTHER_NUM</dfn> : Amount Other, Numeric format.
//!		- <dfn>\ref TAG_EMV_AMOUNT_OTHER_BIN</dfn> : Amount Other, Binary format.
//!		- \ref TAG_EMV_TRANSACTION_CURRENCY_CODE : Transaction currency code.
//!		- <dfn>\ref TAG_EMV_TRANSACTION_CURRENCY_EXPONENT</dfn> : Transaction currency exponent.
//!		- \ref TAG_EMV_TRANSACTION_TYPE : Transaction type.
//!		- \ref TAG_EMV_IFD_SERIAL_NUMBER : Payment interface serial number.
//!		- \ref TAG_EMV_TERMINAL_FLOOR_LIMIT : Terminal floor limit for the chosen AID.
//!		- \ref TAG_EMV_TERMINAL_COUNTRY_CODE : Terminal country code.
//!		- \ref TAG_EMV_ADD_TERMINAL_CAPABILITIES : Terminal Additional Capabilities.
//!		- \ref TAG_EMV_TERMINAL_TYPE : Terminal Type.
//!		- <dfn>\ref TAG_EMV_ACQUIRER_IDENTIFIER</dfn> : Acquirer identifier.
//!		- <dfn>\ref TAG_EMV_MERCHANT_CATEGORY_CODE</dfn> : Merchant category code.
//!		- <dfn>\ref TAG_EMV_MERCHANT_IDENTIFIER</dfn> : Merchant identifier.
//!		- \ref TAG_EMV_TERMINAL_IDENTIFICATION : Terminal identification.
//!		- \ref TAG_EMV_AID_TERMINAL : AID as configured in the terminal.
//!		- \ref TAG_EMV_INT_TRANSACTION_TYPE : Internal transaction type (managed by the application, and used by the kernel).
//!		- <dfn>\ref TAG_EP_KERNEL_TO_USE</dfn> : Kernel to be used (for ExpressPay, it shall be set to \a DEFAULT_EP_KERNEL_AMEX).
//!		- <dfn>\ref TAG_EP_AID_OPTIONS</dfn> : AID application selection options (please refer to \a EntryPoint_Tags.h for more information).
//!		- \ref TAG_EP_CLESS_TRANSACTION_LIMIT : Contactless Transaction Limit for the chosen AID.
//!		- \ref TAG_EP_CLESS_CVM_REQUIRED_LIMIT : Contactless CVM required limit for the chosen AID.
//!		- \ref TAG_EP_CLESS_FLOOR_LIMIT : Contactless Floor limit for the chosen AID.
//!		- \ref TAG_EP_AID_ADDITIONAL_RESULTS : Application selection additional results for the chosen AID (indicates the Entry Point results, such as floor limits exceeded, etc).
//!			Please refer to \a EntryPoint_Tags.h documentation for more information about this tag.
//!		- \ref TAG_EP_FINAL_SELECT_COMMAND_SENT : Final SELECT command.
//!		- \ref TAG_EP_FINAL_SELECT_RESPONSE : Final SELECT response provided by the application selection. It will be analysed by the ExpressPay kernel itself.
//!		- \ref TAG_EP_FINAL_SELECT_STATUS_WORD : Final SELECT response status word provided by the application selection. It will be analysed by the ExpressPay kernel itself.
//!		- \ref TAG_EMV_INT_TAC_DEFAULT : Terminal Action Code Default.
//!		- \ref TAG_EMV_INT_TAC_DENIAL : Terminal Action Code Denial.
//!		- \ref TAG_EMV_INT_TAC_ONLINE : Terminal Action Code Online.
//!		- \ref TAG_EMV_INT_DEFAULT_TDOL : Default TDOL for use in case the TDOL is not present in the ICC.
//!		- <dfn>\ref TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES</dfn> : Supported language for the chosen AID.
//!		- <dfn>\ref TAG_KERNEL_PAYMENT_FLOW_STOP</dfn> : Data field indicating steps where the transaction flow has to be stopped. It is strongly recommended, for transaction performances purposes, to not interrupt the transaction flow using this way (recommended value is all set to 0).
//!		- <dfn>\ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM</dfn> : Data field indicating steps where customisation is necessary.
//!		- <dfn>\ref TAG_KERNEL_PROPRIETARY_TAGS</dfn> : Description of the proprietary tags that shall be considered as known by the kernel.
//!	- Output data returned by the ExpressPay kernel
//!		- \ref TAG_EMV_AMOUNT_AUTH_NUM : Amount Authorized, numeric format.
//!		- \ref TAG_EMV_AMOUNT_OTHER_NUM : Amount Other, Numeric format.
//!		- \ref TAG_EMV_TERMINAL_COUNTRY_CODE : Terminal Country Code.
//!		- \ref TAG_EMV_TERMINAL_TYPE : Terminal Type.
//!		- \ref TAG_EMV_TVR : Terminal Verification Results.
//!		- \ref TAG_EMV_TRANSACTION_TYPE : Transaction Type.
//!		- \ref TAG_EMV_UNPREDICTABLE_NUMBER : Transaction Unpredictable Number.
//!		- \ref TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER : Application PAN Sequence Number.
//!		- \ref TAG_EMV_AIP : Application Interchange Profile.
//!		- \ref TAG_EMV_ATC : Application Transaction Counter.
//!		- \ref TAG_EMV_APPLICATION_CRYPTOGRAM : Application Cryptogram.
//!		- \ref TAG_EMV_CRYPTOGRAM_INFO_DATA : Cryptogram Information Data.
//!		- \ref TAG_EMV_ISSUER_APPLI_DATA : Issuer Application Data (if present).
//!		- \ref TAG_EMV_TRANSACTION_DATE : Transaction Date.
//!		- \ref TAG_EMV_TRANSACTION_TIME : Transaction Time.
//!		- \ref TAG_EMV_APPLI_EXPIRATION_DATE : Application Expiration Date.
//!		- \ref TAG_EMV_APPLICATION_LABEL : Application Label (if present).
//!		- \ref TAG_EMV_TRANSACTION_CURRENCY_CODE : Transaction Currency Code.
//!		- \ref TAG_EMV_TRANSACTION_CURRENCY_EXPONENT : Transaction Currency Exponent.
//!		- \ref TAG_EMV_DF_NAME : DF Name.
//!		- \ref TAG_EMV_APPLI_PAN : Application Pan.
//!		- \ref TAG_KERNEL_SELECTED_PREFERED_LANGUAGE : selected language.
//!		- \ref TAG_EXPRESSPAY_TRANSACTION_CVM : Transaction CVM (Signature or Online PIN).
//!		- Additional data for Magstripe Mode transactions :
//!			- \ref TAG_EXPRESSPAY_PSEUDO_MS_TRACK1 : Pseudo Magnetic Stripe Track 1.
//!			- \ref TAG_EXPRESSPAY_PSEUDO_MS_TRACK2 : Pseudo Magnetic Stripe Track 2.
//! \return Kernel processing status code.
//! - \ref EXPRESSPAY_STATUS_MAGSTRIPE_ONLINE_AUTHORISATION : Transaction succeeded and has to be sent online for authorisation (Magstripe Online transaction).
//! - \ref EXPRESSPAY_STATUS_EMV_PARTIAL_ONLINE_AUTHORISATION : Transaction succeeded and has to be sent online for authorisation (EMV Partial Online transaction).
//! - \ref EXPRESSPAY_STATUS_EMV_FULL_ONLINE_AUTHORISATION : Transaction succeeded and has to be sent online for authorisation (EMV Full Online transaction).
//! - \ref KERNEL_STATUS_OFFLINE_APPROVED : Transaction succeeded and is offline approved.
//!	- \ref KERNEL_STATUS_OFFLINE_DECLINED : Transaction is offline declined.
//!	- \ref KERNEL_STATUS_MOBILE : Cardholder Verification processing determines that Mobile CVM is required. Mobile CVM must be performed by the cardholder and then the transaction is restarted
//!	using \ref ExpressPay_DoTransaction() function (the context of the current transaction persists unchanged: Transaction Amount, Transaction Currency Code...)
//!	- \ref KERNEL_STATUS_CANCELLED : if transaction has been cancelled by the custom application (using \a ExpressPay3_Cancel() function).
//!	Take care that when transaction is cancelled by the user, status code returned is (\ref KERNEL_STATUS_CANCELLED | \ref KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK).
//!	- \ref KERNEL_STATUS_COMMUNICATION_ERROR : if a communication error occurred with the card (no response to a command because card has been to early removed for example).
//!	- \ref KERNEL_STATUS_USE_CONTACT_INTERFACE : if transaction shall be conducted over another interface.
//!	- \ref KERNEL_STATUS_INVALID_INPUT_DATA : if provided data in \a pDataStruct are not correct.
//!	- \ref KERNEL_STATUS_ICC_MISSING_DATA : if mandatory ICC data is missing.
//!	- \ref KERNEL_STATUS_ICC_INVALID_DATA : if ICC returned an invalid data.
//!	- \ref KERNEL_STATUS_ICC_REDUNDANT_DATA : if ICC returned a redundant data.
//!	- \ref KERNEL_STATUS_ICC_DATA_FORMAT_ERROR : if ICC returned data with bad format.
//!	- \ref KERNEL_STATUS_TERM_MISSING_DATA : A mandatory terminal is missing to perform the transaction.
//!	- \ref KERNEL_STATUS_CARD_BLOCKED : If the ICC is blocked (Final SELECT status word is 0x6A81).
//!	- \ref KERNEL_STATUS_APPLICATION_BLOCKED : If the ICC application is blocked (Final SELECT status word is 0x6283).
//!	- \ref KERNEL_STATUS_DATABASE_ERROR : A database error occurred.
//!	- \ref KERNEL_STATUS_UNKNOWN_SW : ICC responded to a command with an unexpected status word.
//!	- \ref KERNEL_STATUS_COND_OF_USE_NOT_SATISFIED : Card responded to GPO with 0x6985 status word.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY : there is not enough memory to perform the transaction.
//!	- \ref KERNEL_STATUS_INTERNAL_ERROR : An internal kernel error occurred (would never occur).
//!	- \ref KERNEL_STATUS_REVOKED_CERTIFICATE : The certificate is revoked.
//!	- \ref KERNEL_STATUS_EXPIRED_CERTIFICATE : The certificate is expired.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The ExpressPay kernel is not loaded in the terminal (or an interface error occurred).
//! \note If the transaction is cancelled or suspended by the application, the returned status code is (\a status \a code | \ref KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK).
//!	If transaction is cancelled or interrupted by the user, the kernel database is not altered to allow continuing the transaction 
//!	anyway if requested (using \ref ExpressPay3_ResumeTransaction() function).

int ExpressPay3_DoTransaction (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to resume the transaction when an interruption occurred (requested interruption or cancellation).
//! The transaction will continue where it has been interrupted.
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//!	- Input data can be provided. It will replace each existing data within the kernel database.
//!	- Output data are the same as \ref ExpressPay3_DoTransaction() function (as it continues the transaction).
//! \return Kernel processing status code (identical than the \ref ExpressPay3_DoTransaction() function).
//! The returned value depends on the step where the transaction is resumed.

int ExpressPay3_ResumeTransaction (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to perform the second part of an ExpressPay Full Online EMV Mode transaction.
//! This function shall be called after the \ref ExpressPay3_DoTransaction() function and after the online authorization.
//!	It begins by analysing the provided Issuer Authorization response and perform the transaction until completion.<br>
//! The ExpressPay kernel performs the following steps:
//! - Issuer authentication (if Issuer Authentication Data received).
//! - Issuer Script Processing (if Issuer Scripts received).
//! - Second Terminal Action Analysis (2nd GENERATE AC command is sent to the card).
//! - Transaction Completion.
//!
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//!	Input data can be provided. It will replace each existing data within the kernel database.
//!	- Input data list
//!		- \ref TAG_EMV_ISSUER_AUTHENTICATION_DATA : Issuer Authentication Data (if received).
//!		- \ref TAG_EMV_AUTHORISATION_RESPONSE_CODE : Authorization Response Code
//!		- \ref TAG_EXPRESSPAY_UNABLE_TO_GO_ONLINE : set to 1 if terminal is unable to connect.
//!		- \ref TAG_EXPRESSPAY_ARC_ONLINE_APPROVED : set to 1 if transaction is approved by the Acquirer.
//!		- \ref TAG_EXPRESSPAY_ISSUER_SCRIPT_71_LIST : List of Scripts with tag '71' received from the Issuer during the Online Authorization.
//!		- \ref TAG_EXPRESSPAY_ISSUER_SCRIPT_72_LIST : List of Scripts with tag '72' received from the Issuer during the Online Authorization.
//!	- Output data are the same as \ref ExpressPay3_DoTransaction() function (as it continues the transaction) and:
//!			- \ref TAG_EMV_INT_ISSUER_SCRIPT_RESULTS : Issuer Script Results (if Issuer Script Processing has been performed).
//! \return Kernel processing status code (identical than the \ref ExpressPay3_DoTransaction() function) and:
//!	- \ref EXPRESSPAY_STATUS_EMV_FULL_ONLINE_APPROVED : the ExpressPay EMV Full Online transaction is approved.
//!	- \ref EXPRESSPAY_STATUS_EMV_FULL_ONLINE_DECLINED : the ExpressPay EMV Full Online transaction is declined.

int ExpressPay3_DoTransactionPostProcessing (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to retrieve the entire kernel database.
//! All the tags present in the database are retrieved.
//! \param[out] pDataStruct Shared buffer filled with all the kernel data. 
//! Make sure the buffer size you provide is bigger enough to store all the tags.
//! Note the shared buffer is automatically cleared by the ExpressPay kernel.
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if all the data are provided and no error occurred.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The ExpressPay kernel is not loaded in the terminal (or an interface error occurred).
//! \note It is strongly recommended to not call this function during the transaction flow, as it should impact the transaction performance.

int ExpressPay3_GetAllData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to request kernel some tags (if present in its database).
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//! Make sure the buffer size you provide is bigger enough to store all the tags.
//! Note the shared buffer is automatically cleared by the ExpressPay kernel.
//!	- Input data : Tag to be requested to the kernel. It is a concatenation of tags and length set to 0.
//! - Output data : list of retrieved data (coded in BER-TLV) that have been requested and that are present in the kernel database.
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if all the data are provided and no error occurred.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The ExpressPay kernel is not loaded in the terminal (or an interface error occurred).
//! \note It is strongly recommended to not call this function during the transaction flow, as it should impact the transaction performance.
//! \remarks Example to get the transaction date and the transaction time from the ExpressPay kernel :
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
//!	// Call the ExpressPay kernel to retrieve the requested tags.
//!	nResult = ExpressPay3_GetData (pSharedDataStruct);
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

int ExpressPay3_GetData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Function to be used to load some data within the kernel.
//! \param[in] pDataStruct Shared buffer filled with the data to be loaded into the kernel.
//!	- \a pDataStruct is filled using the \a GTL_SharedExchange_AddTag() function.
//!	- All the tags that are unknown by the kernel are ignored.
//!	- If a tag is added with a zero length, it removes this tag from the kernel database.
//!	- If a provided tag is already present in the database, this one will be replaced by the new value.
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if tags correctly added in the kernel database and no error occurred.
//!	- \ref KERNEL_STATUS_INVALID_INPUT_DATA : if provided data in \a pDataStruct are not correct.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in the kernel database to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The ExpressPay kernel is not loaded in the terminal (or an interface error occurred).
//! \note It is strongly recommended to not call this function during the transaction flow, as it should impact the transaction performance.
//! \remarks Example to load the transaction date and the transaction time into the ExpressPay kernel :
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
//!	// Add transaction time tag in pSharedDataStruct with a zero length (to indicate you want to remove it).
//!	ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_EMV_TRANSACTION_TIME, 0, NULL);
//!	// Check returned value ...
//!	
//!	// Call the ExpressPay kernel to load the tags.
//!	nResult = ExpressPay3_LoadData (pSharedDataStruct);
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

int ExpressPay3_LoadData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function can be used to cancel the ExpressPay transaction.
//! We could imagine using it to cancel the transaction when the red key is pressed during the ExpressPay transaction for example.
//! \return Always \ref KERNEL_STATUS_OK.
//! \note This is the responsibility of the custom application to correctly use this function. 
//! The ExpressPay transaction can be cancelled at any step.
//! If called, the kernel will return \ref KERNEL_STATUS_CANCELLED on the following functions :
//!	- \ref ExpressPay3_DoTransaction().
//!	- \ref ExpressPay3_ResumeTransaction().

int ExpressPay3_Cancel (void);



//! \brief This function allows to manage the ExpressPay kernel debug features.
//! This allows activating / deactivating the following debug features :
//!	- Trace : it provides debug information in the \a Trace.exe tool provided in the TDS.
//!	- Time measurements : it manages in the database the \ref TAG_KERNEL_DEBUG_TIME tag that can be retrieved using \ref ExpressPay3_GetData() function).
//!	Note if Time debug feature is not activated, \ref TAG_KERNEL_DEBUG_TIME tag is not stored in the kernel database.
//!	- APDU storage : it stores all the APDU sent to the ICC and responses sent by the ICC in the database, using specific tags. 
//!	Each command is stored in a \ref TAG_EXPRESSPAY_INT_SENT_APDU tag, each received ICC response is stored in a \ref TAG_EXPRESSPAY_INT_CARD_RESPONSE tag.
//!
//! \param[in] pDataStruct Shared buffer filled with the \ref TAG_KERNEL_DEBUG_ACTIVATION tag indicating the debug mode.
//!	If the tag is not present or set to 0, then all the debug features are deactivated.
//! \return \ref KERNEL_STATUS_OK is always returned.
//!	\note If debug features shall be activated, it is strongly recommended to call this function before the transaction has started.
//!	It allows to not waste time during the transaction (performances purposes).
//! \remarks Example to set the debug mode of the ExpressPay kernel :
//! \code
//!	T_SHARED_DATA_STRUCT * pSharedDataStruct;
//!	unsigned char ucTraceOnly = KERNEL_DEBUG_MASK_TRACES;	// Trace only is activated
//!	unsigned char ucApduOnly = KERNEL_DEBUG_MASK_APDU; // APDU is activated
//!	unsigned char ucTracesAndApdu = (KERNEL_DEBUG_MASK_TRACES | KERNEL_DEBUG_MASK_APDU); // Traces and APDU debug features are activated.
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
//!	// Call the ExpressPay kernel to set the debug mode.
//!	nResult = ExpressPay3_DebugManagement (pSharedDataStruct);
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
//!	// Call the ExpressPay kernel to load the tags.
//!	nResult = ExpressPay3_DebugManagement (pSharedDataStruct);
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

int ExpressPay3_DebugManagement (T_SHARED_DATA_STRUCT * pDataStruct);



//!	\brief This function clears and initialise the ExpressPay kernel.
//! It fully clear the database and restores the global data (reset cancel, deactivate debug features, etc). 
//! <b>It is mandatory to call this function after each ExpressPay transaction has been completed (and the terminal 
//! is returning on idle state).</b>
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if ExpressPay kernel correctly cleared and initialised.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.

int ExpressPay3_Clear (void);



//! \brief This function gets the kernel information.
//! \param[out] pDataStruct Shared buffer filled with the following tags (note this buffer is automatically cleared by the function) :
//!	- \ref TAG_KERNEL_APPLICATION_NAME that indicates the application name (ASCII format).
//!	- \ref TAG_KERNEL_APPLICATION_IDENT that indicates the kernel identifier (in ASCII format, \a 3351 followed by the ExpressPay kernel version on 4 digits).
//!	- \ref TAG_KERNEL_APPLICATION_CRC that indicates the ExpressPay kernel CRC.
//! \return
//!	- \ref KERNEL_STATUS_OK if kernel information correctly retrieved.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_INTERNAL_ERROR if an internal error occurred.

int ExpressPay3_GetInfos (T_SHARED_DATA_STRUCT * pDataStruct);


//! @}
