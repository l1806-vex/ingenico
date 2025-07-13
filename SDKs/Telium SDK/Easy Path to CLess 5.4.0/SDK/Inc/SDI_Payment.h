/**
 * \file SDI_Payment.h
 * \brief Defines the interface of payment services.
 *
 *
 * \author	Ingenico France
 * \author	Copyright (c) 2010 Ingenico France, 1 rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico France has intellectual property rights relating to the technology embodied\n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico France.
 **/

#ifndef __SDI_PAYMENT_H__INCLUDED__
#define __SDI_PAYMENT_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \addtogroup SDI_Payment_InterfaceFunctions
//! @{

//! \brief Starts a contactless transaction. 
//! Standard transaction data are returned as function output (transaction output can be retrieved with \ref SDI_Payment_GetTransactionResult() function). 
//! Note this is one of the commands that can be interrupted using the SDI_Payment_CancelTransaction() function.
//! This function is asynchronous, non-blocking. A notification is sent to the caller to indicate the transaction processing is completed.
//! \param[in] nAppliId Identifies the application to which the call is for. 
//! \param[in] hTlvTreeIn Contains data that are necessary to perform a payment. Contains at least the following data (bold ones are mandatory or highly recommended):
//!		- \ref TAG_EMV_AMOUNT_AUTH_NUM : Amount Authorised, numeric.
//!		- \ref TAG_EMV_AMOUNT_OTHER_NUM : Amount Other, numeric.
//!		- \ref TAG_EMV_TRANSACTION_TYPE : Transaction Type.
//!		- \ref TAG_EMV_TRANSACTION_CURRENCY_CODE : Transaction Currency Code.
//!		- \ref TAG_EMV_TRANSACTION_SEQUENCE_COUNTER : Transaction Sequence Counter.
//!		- <dfn>\ref TAG_EMV_TRANSACTION_DATE</dfn> : Transaction date. If not present, intelligent reader one is used (and in this case, the terminal shall not use its own value for this tag during clearing, but shall use the intelligent reader values).
//!		- <dfn>\ref TAG_EMV_TRANSACTION_TIME</dfn> : Transaction time. If not present, intelligent reader one is used (and in this case, the terminal shall not use its own value for this tag during clearing, but shall use the intelligent reader values).
//!		- <dfn>\ref TAG_EMV_IFD_SERIAL_NUMBER</dfn> : IFD Serial Number. If not present, intelligent reader one is used (and in this case, the terminal shall not use its own value for this tag during clearing, but shall use the intelligent reader values).
//!		- <dfn>\ref TAG_SDSA_LIST_OF_OUTPUT_TAGS</dfn> : List of tags to be returned at the end of the transaction. If not provided, default tag list is returned.
//! \param[in] nEvent Event identifier, necessary to be notified the response has been received. See \ref SDI_Overview for more details about asynchronous functions.
//! \return
//! - \ref SDI_STATUS_OK : transaction has been correctly launched.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a transaction is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_Payment_DoTransaction (const int nAppliId, const TLV_TREE_NODE hTlvTreeIn, const int nEvent);



//! \brief This function is called after the notification related to the \ref SDI_Payment_DoTransaction() function has been received.
//! It allows retrieving the transaction result.
//! Note this function is synchronous, blocking.
//! \param[out] pTlvTreeOut contains the standard transaction results, including transaction status (missing mandatory card data, invalid card data, etc. depending on the kernel used)
//! and transaction related data (also depending on the kernel used to perform the transaction).
//! If \ref TAG_SDSA_LIST_OF_OUTPUT_TAGS tag has been provided on \ref SDI_Payment_DoTransaction() call, pTlvTreeOut contains the requested tags.
//! \return
//! - \ref SDI_STATUS_APPROVED : transaction is approved.
//! - \ref SDI_STATUS_DECLINED : transaction is offline declined.
//! - \ref SDI_STATUS_ONLINE_REQUEST : transaction has to be sent online for authorization.
//! - \ref SDI_STATUS_TERMINATED : transaction is terminated.
//! - \ref SDI_STATUS_USE_OTHER_INTERFACE : if transaction shall be conducted over another interface.
//! - \ref SDI_STATUS_NO_CARD : if no card has been presented and timeout is elapsed.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_NOT_ALLOWED : if no contactless transaction has been started.
//! - \ref SDI_STATUS_INVALID_DATA : if provided data in the input structure is not correct.
//! - \ref SDI_STATUS_CANCELLED : if the transaction has been cancelled.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_NO_PARAMETER : if there is no loaded parameter.
//! - \ref SDI_STATUS_MISSING_DATA : if mandatory data are missing.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier (given in SDI_Payment_DoTransaction parameters) is not valid or if the application in the intelligent reader does not implement the related service.
//! - \ref SDI_STATUS_ANSWER_NOT_YET_RECEIVED : if the transaction result is not yet received.

int SDI_Payment_GetTransactionResult (TLV_TREE_NODE * pTlvTreeOut);



//! \brief Performs the transaction post processing (specific requirement depending on the payment scheme used).
//! It can be used to perform issuer script processing or any specific post transaction processing (it will be used for payWave 2.1 and ExpressPay 2.0 for example).
//! Note this is one of the commands that can be interrupted using the \ref SDI_Payment_CancelTransaction() function.
//! This function is asynchronous, non-blocking. A notification is sent to the caller to indicate the transaction processing is completed.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \param[in] hTlvTreeIn Contains:
//!		- All the necessary data to perform the transaction post processing. The data will depend on the payment scheme used.
//!		- <dfn>\ref TAG_SDSA_LIST_OF_OUTPUT_TAGS</dfn> : List of tags to be returned at the end of the transaction. If not provided, default tag list is returned.
//! \param[in] nEvent Event identifier, necessary to be notified the response has been received. See \ref SDI_Overview for more details about asynchronous functions.
//! \return
//! - \ref SDI_STATUS_OK : transaction has been correctly launched.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a transaction is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_Payment_TxnPostProcessing (const int nAppliId, const TLV_TREE_NODE hTlvTreeIn, const int nEvent);



//! \brief This function is called after the notification related to the \ref SDI_Payment_TxnPostProcessing() function has been received.
//! It allows retrieving the transaction post processing result.
//! Note this function is synchronous, blocking.
//! \param[out] pTlvTreeOut Contains the transaction post processing results, including transaction status (missing mandatory card data, invalid card data, etc. depending on the kernel used)
//! and transaction post processing related data (also depending on the kernel used to perform the transaction).
//! If \ref TAG_SDSA_LIST_OF_OUTPUT_TAGS tag has been provided on \ref SDI_Payment_TxnPostProcessing() call, pTlvTreeOut contains the requested tags.
//! \return
//! - \ref SDI_STATUS_APPROVED : transaction is approved.
//! - \ref SDI_STATUS_DECLINED : transaction is offline declined.
//! - \ref SDI_STATUS_ONLINE_REQUEST : transaction has to be sent online for authorization.
//! - \ref SDI_STATUS_TERMINATED : transaction is terminated.
//! - \ref SDI_STATUS_USE_OTHER_INTERFACE : if transaction shall be conducted over another interface.
//! - \ref SDI_STATUS_NO_CARD : if no card has been presented and timeout is elapsed.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_NOT_ALLOWED : if no contactless post processing has been started.
//! - \ref SDI_STATUS_INVALID_DATA : if provided data in the input structure is not correct.
//! - \ref SDI_STATUS_CANCELLED : if the transaction has been cancelled.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_NO_PARAMETER : if there is no loaded parameter.
//! - \ref SDI_STATUS_MISSING_DATA : if mandatory data are missing.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier (given in SDI_Payment_TxnPostProcessing parameters) is not valid or if the application in the intelligent reader does not implement the related service.
//! - \ref SDI_STATUS_ANSWER_NOT_YET_RECEIVED : if the transaction result is not yet received.

int SDI_Payment_GetPostProcessingResult (TLV_TREE_NODE * pTlvTreeOut);



//! \brief Cancel the current process in progress into the intelligent reader.
//! For example it can cancel the operations started using the \ref SDI_Payment_DoTransaction(), \ref SDI_Payment_TxnPostProcessing() or \ref SDI_Payment_WaitCardRemoval() functions.
//! Note if the cancellation is taken into account by the application in the intelligent reader, the caller will be notified that the transaction process is completed (ie: \ref SDI_STATUS_CANCELLED will be returned by \ref SDI_Payment_GetTransactionResult() function).
//! This function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \return
//! - \ref SDI_STATUS_OK : if cancel command has been correctly sent.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a Cancel is already in progress).
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_NO_OPERATION_IN_PROGRESS : if there is no transaction in progress.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_Payment_CancelTransaction (const int nAppliId);



//! \brief Load a full set of parameters in the intelligent reader. If there is already a set of parameters in the intelligent reader, this one will be deleted and replaced by the new one.
//! This function also allows to load a BlackList file in the intelligent reader.
//! Note this function is synchronous, blocking.
//!
//! Here is an overview of the content of a parameter set.
//! @image html ParameterSet.png
//!
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \param[in] hTlvTreeIn Contains the following data (root node is \ref TAG_SDSA_PARAMETER_FILE_NODE or \ref TAG_SDSA_BLACKLIST_FILE_NODE):
//!		- \ref TAG_SDSA_PARAMETER_FILE_NODE : node that identifies that the content of the TLVTREE is a set of parameters. This node contains all the parameters needed by the reader to perform a payment:
//!			- \ref TAG_SDSA_AID_PARAMETERS : node that contains each <b>AID Parameters</b>:
//!				- \ref TAG_SDSA_PARAM_AID_STRUCTURE : AID parameters are contained in a node (AID structure). Each AID structure defines an AID supported by the intelligent reader and contains data specific for this AID (AID value, floor limits...). After the application selection, all the data (contained in the \ref TAG_SDSA_PARAM_AID_STRUCTURE) related to the selected AID will be sent to the kernel.
//!			- \ref TAG_SDSA_CAKEYS_PARAMETERS : node that contains each <b>CA Key parameters</b>:
//!				- \ref TAG_SDSA_PARAM_CA_KEY_STRUCTURE : CA Key data are in a node (CA structure). Each CA structure defines a transaction certificate that can be used for Offline Data Authentication. CA structure consists of :
//!					- \ref TAG_EMV_AID_TERMINAL : RID.
//!					- \ref TAG_EMV_CA_PUBLIC_KEY_INDEX_TERM : CA Index.
//!					- \ref TAG_EMV_INT_CAPK_MODULUS : CA modulus.
//!					- \ref TAG_EMV_INT_CAPK_EXPONENT : CA exponent.
//!					- \ref TAG_EMV_INT_CAPK_CHECKSUM : CA Checksum.
//!			- \ref TAG_SDSA_ICS_PARAMETERS : node that contains <b>ICS Parameters</b>:
//!				- \ref TAG_SDSA_PARAM_ICS_DATA_STRUCTURE : ICS related data are global data that are not specific to an AID (\ref TAG_EMV_TERMINAL_TYPE, \ref TAG_EMV_TERMINAL_COUNTRY_CODE, \ref TAG_EMV_MERCHANT_IDENTIFIER...)<br>
//!				<b>Notes</b>:
//!					- In the below example, all the tags contained in the \ref TAG_SDSA_PARAM_ICS_DATA_STRUCTURE structure (except the TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT tag) are mandatory or highly recommended.
//!					- Only one \ref TAG_SDSA_PARAM_ICS_DATA_STRUCTURE structure must be defined in the \ref TAG_SDSA_ICS_PARAMETERS node.
//!			- \ref TAG_SDSA_SPECIFIC_PARAMETERS : node that contains each <b>Kernel Specific Parameters</b>:
//!				- \ref TAG_SDSA_PARAM_KERNEL_SPECIFIC_STRUCTURE : kernel specific data are data specific to a payment scheme (PayPass, payWave...). If the selected AID is a payWave AID, all the payWave specific data will be sent to the kernel. Kernel Specific data are in a node that consists of :
//!					- \ref TAG_EP_KERNEL_TO_USE : Kernel identifier.
//!					- Any other data specific to the kernel. This data will be sent to the kernel if the kernel is selected to perform the transaction.
//!				- \ref TAG_SDSA_GENERIC_MONEY_EXTENDED : currency could be added using the following format:<br>
//!					Example 'EUR9782,.1' <br>
//!						- EUR : is the currency name on 3 bytes
//!						- 978 : is the currency code on 3 bytes
//!						- 2 : is the decimal position in the amount
//!						- , : is the cents separator
//!						- . : is the thousands separator
//!						- 1 : is the currency position (0 = after the amount; 1 = before the amount)<br>
//!					With the 'EUR9782,.1' example, an amount of 1000,01 euros will be displayed <b>EUR 1.000,01</b>
//!			- \ref TAG_SDSA_CAREVOK_PARAMETERS : node that contains the list of revoked certificates.
//!					- TAG_KERNEL_REVOKED_CERTIFICATE_LIST :  List of revoked certificates.
//!			- Other additional data, depending on the application (specific needs).<br><br>
//!			  <b>Note:</b> if one of the global data is also defined in an AID structure, the value defined in the AID struture as the highest priority.<br>
//!           For example the \ref TAG_EMV_ADD_TERMINAL_CAPABILITIES tag is defined with the following values:
//!				- '40 00 F0 B0 01' in  the \ref TAG_SDSA_PARAM_AID_STRUCTURE structure related to the AID 'A0 00 00 00 03 10 10'.
//!				- '60 00 F0 B0 01' in  the \ref TAG_SDSA_PARAM_ICS_DATA_STRUCTURE structure.<br>
//!				If the AID 'A0 00 00 00 03 10 10' is selected for the transaction, the \ref TAG_EMV_ADD_TERMINAL_CAPABILITIES tag value will be '40 00 F0 B0 01'.<br><br>
//!		- \ref TAG_SDSA_BLACKLIST_FILE_NODE : node that identifies that the content of the TLVTREE is a BlackList. This node consists of a list of \ref TAG_EMV_APPLI_PAN tags and \ref TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER tags.
//! \param[out] pTlvTreeOut Filled if a parameter set has been loaded (not filled in the case of a blacklist). Contains a SHA calculated on the loaded parameters (\ref TAG_SDSA_LOADED_PARAMETERS_SHA). This SHA allows the terminal to be able to check if the parameters loaded in the intelligent reader are coherent with its ones.
//! \return
//! - \ref SDI_STATUS_OK : if parameters are correctly loaded.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_NOT_ENOUGH_MEMORY : if there is not enough memory to store the parameters.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_INVALID_DATA : if provided data are not correct.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a transaction is in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.
//!
//! Here is an example of a parameter file (XML format) that shows the tags that could be contained in the hTlvTreeIn parameter :
//! \verbatim
//! <?xml version="1.0" standalone="yes" ?>
//! <!-- Parameter file VISA qVSDC -->
//! <!-- VISA_QVSDC_00 -->
//! 
//! <tlvtree ver="1.0">
//! 
//! <node tag="0xBF91884A">
//! 	<node tag="0x9F91884A"> 56 49 53 41 5f 51 56 53 44 43 </node>					    <!-- TAG_SDSA_PARAMETERS_LABEL : VISA_QVSDC -->
//! 	
//! 	<node tag="0xBF918845">    															<!-- TAG_SDSA_AID_PARAMETERS -->
//!         <node tag="0xBF918840">
//!             <!-- AID : VISA AID -->
//!             <node tag="0x9F06"> A0 00 00 00 03 10 10 </node>                			<!-- TAG_AID_TERMINAL -->
//!             <node tag="0x9F928101"> 00 03 </node>                           			<!-- TAG_EP_KERNEL_TO_USE : VISA -->
//!             <node tag="0x9F928100"> 05 01 00 00 </node>                     			<!-- TAG_EP_AID_OPTIONS : Partial AID & Zero amount -->
//!             <node tag="0x9F66"> 36 00 C0 00 </node>                         			<!-- TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS qVSDC + EMV Chip contact + onlinePIN + sign supported + ISP + Mobile CVM-->
//!             <node tag="0x9F92810D"> 00 00 00 00 15 00 </node>               			<!-- TAG_EP_CLESS_TRANSACTION_LIMIT : 15.00 -->
//!             <node tag="0x9F92810F"> 00 00 00 00 14 00 </node>               			<!-- TAG_EP_CLESS_FLOOR_LIMIT : 14.00 -->
//!             <node tag="0x9F92810E"> 00 00 00 00 13 00 </node>               			<!-- TAG_EP_CLESS_CVM_REQUIRED_LIMIT : 13.00 -->
//!             <node tag="0x9F1B"> 00 00 05 AA </node>                         			<!-- TAG_EMV_TERMINAL_FLOOR_LIMIT : 14.50 -->
//!         </node>
//! 
//!         <node tag="0xBF918840">
//!             <!-- AID : Test AID -->
//!             <node tag="0x9F06"> A0 00 00 99 99 01 </node>                   			<!-- TAG_AID_TERMINAL -->
//!             <node tag="0x9F928101"> 00 03 </node>                           			<!-- TAG_EP_KERNEL_TO_USE : VISA -->
//!             <node tag="0x9F928100"> 05 01 00 00 </node>                     			<!-- TAG_EP_AID_OPTIONS : Partial AID & Zero amount -->
//!             <node tag="0x9F66"> 36 00 C0 00 </node>                         			<!-- TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS qVSDC + EMV Chip contact + onlinePIN + sign supported + ISP + Mobile CVM -->
//!             <node tag="0x9F92810D"> 00 00 00 00 15 00 </node>               			<!-- TAG_EP_CLESS_TRANSACTION_LIMIT : 15.00 -->
//!             <node tag="0x9F92810F"> 00 00 00 00 14 00 </node>               			<!-- TAG_EP_CLESS_FLOOR_LIMIT : 14.00 -->
//!             <node tag="0x9F92810E"> 00 00 00 00 13 00 </node>               			<!-- TAG_EP_CLESS_CVM_REQUIRED_LIMIT : 13.00 -->
//!             <node tag="0x9F1B"> 00 00 05 AA </node>                         			<!-- TAG_EMV_TERMINAL_FLOOR_LIMIT : 14.50 -->
//!         </node>
//!     </node> <!-- End node 0xBF918845 : TAG_SDSA_AID_PARAMETERS -->
//! 
//!     <node tag="0xBF918846">    <!-- TAG_SDSA_CAKEYS_PARAMETERS -->
//! 
//!         <node tag="0xBF918841">
//!             <node tag="0x9F06"> A0 00 00 00 03 </node>
//!             <node tag="0x9F22"> 50 </node>
//!             <node tag="0x9F918704"> D1 11 97 59 00 57 B8 41 96 C2 F4 D1 1A 8F 3C 05
//!                                     40 8F 42 2A 35 D7 02 F9 01 06 EA 5B 01 9B B2 8A
//!                                     E6 07 AA 9C DE BC D0 D8 1A 38 D4 8C 7E BB 00 62
//!                                     D2 87 36 9E C0 C4 21 24 24 6A C3 0D 80 CD 60 2A
//!                                     B7 23 8D 51 08 4D ED 46 98 16 2C 59 D2 5E AC 1E
//!                                     66 25 5B 4D B2 35 25 26 EF 09 82 C3 B8 AD 3D 1C
//!                                     CE 85 B0 1D B5 78 8E 75 E0 9F 44 BE 73 61 36 6D
//!                                     EF 9D 1E 13 17 B0 5E 5D 0F F5 29 0F 88 A0 DB 47 </node>
//!             <node tag="0x9F918703"> 01 00 01 </node>
//!             <node tag="0x9F918702"> B7 69 77 56 68 CA CB 5D 22 A6 47 D1 D9 93 14 1E DA B7 23 7B </node>
//!         </node>
//! 
//!     </node> <!-- End node 0xBF918846 : TAG_SDSA_CAKEYS_PARAMETERS-->
//!
//!		<node tag="0xBF918847">	<!-- TAG_SDSA_CAREVOK_PARAMETERS -->
//!			<node tag="0x9F91841F"> A0 00 00 00 03 51 00 00 06 </node>				<!-- TAG_KERNEL_REVOKED_CERTIFICATE_LIST -->
//!		</node> <!-- End node 0xBF918847 : TAG_SDSA_CAREVOK_PARAMETERS -->
//!
//!     <node tag="0xBF918848">    <!-- TAG_SDSA_ICS_PARAMETERS -->
//! 
//!         <node tag="0xBF918842">
//!             <!-- ICS0 values -->
//!             <node tag="0x9F928210"> 03 00 00 00 </node>                     			<!-- TAG_GENERIC_DETECTION_TYPE -->
//!             <node tag="0x9F928212"> 00 00 17 70 </node>                     			<!-- TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT : 6000 -->
//!             <node tag="0x9F928214"> 01 </node>                              			<!-- TAG_GENERIC_DETECTION_NB_CARDS_TO_DETECT -->
//! 
//!             <node tag="0x9F1A"> 08 40 </node>                               			<!-- TAG_EMV_TERMINAL_COUNTRY_CODE -->
//!             <node tag="0x9F40"> 60 00 F0 B0 01 </node>                      			<!-- TAG_EMV_ADD_TERMINAL_CAPABILITIES -->
//!             <node tag="0x9F35"> 22 </node>                                  			<!-- TAG_EMV_TERMINAL_TYPE -->
//! 
//!             <node tag="0x9F01"> 01 23 45 67 89 01 </node>                   			<!-- TAG_EMV_ACQUIRER_IDENTIFIER -->
//!             <node tag="0x9F15"> 00 00 </node>                               			<!-- TAG_EMV_MERCHANT_CATEGORY_CODE -->
//!             <node tag="0x9F16"> 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 </node>  	<!-- TAG_EMV_MERCHANT_IDENTIFIER -->
//!             <node tag="0x9F1C"> 87 65 43 21 87 65 43 21 </node>             			<!-- TAG_EMV_TERMINAL_IDENTIFICATION -->
//!             <node tag="0x9F4E" format="ascii"> "MerchantNameLocation" </node>   		<!-- TAG_EMV_MERCHANT_NAME_AND_LOCATION -->
//!         </node> <!-- End node 0xBF918842 -->
//!
//!     </node> <!-- End node 0xBF918803 : TAG_SDSA_ICS_PARAMETERS-->
//! 
//!     <node tag="0xBF918849">    <!-- TAG_SDSA_SPECIFIC_PARAMETERS -->
//! 
//!         <!-- VISA Specific parameters -->
//!			<node tag="0xBF918843">
//!             <node tag="0x9F928101"> 00 03 </node>                           			<!-- TAG_EP_KERNEL_TO_USE : VISA -->
//!             <node tag="0x9f918307"> 01 </node>                              			<!-- TAG_PAYWAVE_TERM_SUPPORTED_FDDA_VERSIONS -->
//!             <node tag="0x9f918318"> 01 </node>                              			<!-- TAG_PAYWAVE_IS_TRANSACTION_LOG_SUPPORTED -->
//!             <node tag="0x9F33"> E0 68 40 </node>                            			<!-- TAG_EMV_TERMINAL_CAPABILITIES -->
//!         </node> <!-- End node 0xBF918843 -->
//! 
//! 		<node tag="0x9F91884B" format="ascii"> "EUR9782,.1" </node>  					<!-- TAG_SDSA_GENERIC_MONEY_EXTENDED EUR9782,.1 -->
//! 		<node tag="0x9F91884B" format="ascii"> "USD8402,.1" </node>  					<!-- TAG_SDSA_GENERIC_MONEY_EXTENDED USD8402,.1 -->
//! 		
//!     </node> <!-- End node 0xBF918849 : TAG_SDSA_SPECIFIC_PARAMETERS-->
//! 
//! </node>     <!-- End node 0xBF91884A -->
//! </tlvtree>
//! 
//! \endverbatim

int SDI_Payment_LoadParams (const int nAppliId, const TLV_TREE_NODE hTlvTreeIn, TLV_TREE_NODE * pTlvTreeOut);



//! \brief Get all the loaded parameters. But it is possible to only get the parameter calculated checksum.
//! It would be useful for the terminal to get this checksum in order to check parameters consistency (with the one loaded in the terminal itself).
//! Note this function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \param[in] hTlvTreeIn TLV Tree that may contain the tag \ref TAG_SDSA_GET_PARAMETERS_SHA_ONLY indicating if only the parameter SHA shall be retrieved or not (Boolean). If not present, all the parameters as well as the SHA are returned.
//! \param[out] pTlvTreeOut Contains the loaded parameters (same format as described in \ref SDI_Payment_LoadParams() function), only if the SHA only flag is not present or set to FALSE.
//! \return
//! - \ref SDI_STATUS_OK : if parameters have been correctly got.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_NO_PARAMETER : if there is no loaded parameter.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a transaction is in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_Payment_GetParams (const int nAppliId, const TLV_TREE_NODE hTlvTreeIn, TLV_TREE_NODE * pTlvTreeOut);



//! \brief Erase the application parameters.
//! Note this function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \return
//! - \ref SDI_STATUS_OK : if parameters correctly erased.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a transaction is in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_Payment_EraseParams (const int nAppliId);



//! \brief Get application data.
//! Note this function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \param[in] hTlvTreeIn Contains the following data:
//!		- List of tags to be requested (Tags with no length).
//!		- If the kernel to use is not specified (\ref TAG_SDSA_KERNEL_IDENTIFIER not present), the kernel that performed the last transaction will be called.
//!		- If all the data are required (\ref TAG_SDSA_GET_ALL_DATA is present), all the application data are requested.
//!		- Any additional data if necessary (depending on application needs).
//! \param[out] pTlvTreeOut Containing the required parameters (all the requested data that are not present in the kernel will not be returned).
//! \return
//! - \ref SDI_STATUS_OK : if command correctly managed. All the requested and present data are provided in the output structure.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_INVALID_DATA : if provided data are not correct or if pTlvTreeOut is NULL.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a transaction is in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_Payment_GetData (const int nAppliId, const TLV_TREE_NODE hTlvTreeIn, TLV_TREE_NODE * pTlvTreeOut);



//! \brief Clear the transaction data. This function does not concern the parameters.
//! Note this function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \return
//! - \ref SDI_STATUS_OK : if payment data correctly cleared.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a transaction is in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_Payment_ClearData (const int nAppliId);



//! \brief Request an application to indicate the caller when the transaction status has changed. It is useful for the terminal to inform the merchant when  something occurred (collision detected, card can be removed, double tap, etc.).
//! The user shall indicate the current transaction status and a mask indicating with transaction status he wants to be notified.
//! When called, if the status within the application is different from state defined in tag \ref TAG_SDSA_CURRENT_TXN_STATUS, then the function will send a notification indicating the status update.
//! Note this function is asynchronous, non-blocking. A notification is sent to the caller to indicate the processing is completed (transaction status changed).
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \param[in] hTlvTreeIn TLV Tree containing the following data:
//!		- \ref TAG_SDSA_STATUS_TO_NOTIFY : Bit field containing the status on which the caller wish to be notified:
//!			- \ref SDSA_PAYMENT_STATUS_NOT_STARTED : no payment is in progress.
//!			- \ref SDSA_PAYMENT_STATUS_DETECT_CARD : card detection has been started.
//!			- \ref SDSA_PAYMENT_STATUS_IN_PROGRESS : a card has been detected and transaction is in progress.
//!			- \ref SDSA_PAYMENT_STATUS_COLLISION : if too many cards have been presented.
//!			- \ref SDSA_PAYMENT_STATUS_RETRY : transaction is restarted due to communication error.
//!			- \ref SDSA_PAYMENT_STATUS_DOUBLE_TAP : if a double tap is required.
//!			- \ref SDSA_PAYMENT_STATUS_CARD_READ : if the interaction with the card is completed.
//!		- \ref TAG_SDSA_CURRENT_TXN_STATUS : Data containing the value of the current transaction status. If this is the first time this function is called, this parameter is set \ref SDSA_PAYMENT_STATUS_NOT_STARTED. Else, it has one of the values defined before.
//! \param[in] nEvent Event identifier, necessary to be notified the response has been received. See \ref SDI_Overview for more details about asynchronous functions.
//! \return
//! - \ref SDI_STATUS_OK : if status update checking correctly started.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a Get Status is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_Payment_GetStatusUpdateStart (const int nAppliId, const TLV_TREE_NODE hTlvTreeIn, const int nEvent);



//! \brief Stop the asynchronous call started with the \ref SDI_Payment_GetStatusUpdateStart() function.
//! Note this function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \return
//! - \ref SDI_STATUS_OK : if the asynchronous function correctly stopped.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a Get Status Update Stop is already in progress).
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_BUSY : if a Get Status is already launched with another application, so cancellation is not possible.
//! - \ref SDI_STATUS_NO_OPERATION_IN_PROGRESS : if there is no status checking in progress.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_Payment_GetStatusUpdateStop (const int nAppliId);



//! \brief This function is called when a notification has been received following the call of \ref SDI_Payment_GetStatusUpdateStart() function. It provides the current status.
//! Note this function is synchronous, blocking.
//! \param[out] pTlvTreeOut containing the following data:
//!		- \ref TAG_SDSA_CURRENT_TXN_STATUS : Data containing the application current status:
//!			- \ref SDSA_PAYMENT_STATUS_NOT_STARTED : no payment is in progress.
//!			- \ref SDSA_PAYMENT_STATUS_DETECT_CARD : card detection has been started.
//!			- \ref SDSA_PAYMENT_STATUS_IN_PROGRESS : a card has been detected and transaction is in progress.
//!			- \ref SDSA_PAYMENT_STATUS_COLLISION : if too many cards have been presented.
//!			- \ref SDSA_PAYMENT_STATUS_RETRY : transaction is restarted due to communication error.
//!			- \ref SDSA_PAYMENT_STATUS_DOUBLE_TAP : if a double tap is required.
//!			- \ref SDSA_PAYMENT_STATUS_CARD_READ : if the interaction with the card is completed.
//! \return
//! - \ref SDI_STATUS_OK : if the status correctly retrieved.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_NOT_ALLOWED : if there is no status checking in progress.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_MISSING_DATA : if mandatory data are missing.
//! - \ref SDI_STATUS_CANCELLED : if the process has been cancelled using the \ref SDI_Payment_GetStatusUpdateStop() function.
//! - \ref SDI_STATUS_ANSWER_NOT_YET_RECEIVED : if the transaction status is not yet received.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier (given in SDI_Payment_GetStatusUpdateStart parameters) is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_Payment_GetStatusUpdate (TLV_TREE_NODE * pTlvTreeOut);



//! \brief Request an application to display a screen on the device. This feature is necessary to display the transaction status (after an online authorization for example).
//! Note this function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \param[in] hTlvTreeIn Contains the \ref TAG_SDSA_GUI_STATE_TO_SET tag indicating the GUI state to be set. Refer to \ref PossibleScreens for more information about the possible values.
//! \return
//! - \ref SDI_STATUS_OK : if screen correctly displayed.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_MISSING_DATA : tag indicating the screen to be displayed is not present.
//! - \ref SDI_STATUS_INVALID_DATA : if provided data are not correct (screen identifier is not known).
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a transaction is in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_Payment_SetGuiState (const int nAppliId, const TLV_TREE_NODE hTlvTreeIn);



//! \brief Waits the contactless card removal (if required) if it is still in the field, and switches off the contactless field.
//! If there is no card in the field, the function immediately sends a notification. This function also manages the GUI interface according to this processing.
//! Note this is one of the commands that can be interrupted using the \ref SDI_Payment_CancelTransaction() function.
//! This function is asynchronous, non-blocking. A notification is sent to the caller to indicate the transaction processing is completed.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \param[in] hTlvTreeIn Contains the \ref TAG_SDSA_WAIT_CARD_REMOVAL tag indicating if the reader shall wait the card removal or not.
//! \param[in] nEvent Event identifier, necessary to be notified the response has been received. See \ref SDI_Overview for more details about asynchronous functions.
//! \return
//! - \ref SDI_STATUS_OK : if processing correctly started.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a transaction is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_Payment_WaitCardRemoval (const int nAppliId, const TLV_TREE_NODE hTlvTreeIn, const int nEvent);



//! \brief Gets the contactless card removal result. This function is called after the notification related to the \ref SDI_Payment_WaitCardRemoval() function has been received.
//! Note this function is synchronous, blocking.
//! \return
//! - \ref SDI_STATUS_OK : if processing correctly performed.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_NO_CARD : if card removal is required and no card is present in the field.
//! - \ref SDI_STATUS_CANCELLED : if card removal is required and \ref SDI_Payment_CancelTransaction() function is called.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_NOT_ALLOWED : if there is Card Removal in progress.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier (given in SDI_Payment_WaitCardRemoval parameters) is not valid or if the application in the intelligent reader does not implement the related service.
//! - \ref SDI_STATUS_ANSWER_NOT_YET_RECEIVED : if the contactless card removal result is not yet received.

int SDI_Payment_GetCardRemovalResult (void);



//! \brief As it is possible for an application in the intelligent reader to provide other services than the ones defined by Ingenico for payment, an additional function allows exchanging data
//! with the application through user commands. So this function allows exchanging data between the terminal and the custom application within the intelligent reader. It allows adding proprietary commands for specific needs.
//! Note this function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \param[in] nCommandId User command identifier (only between 1 and 8).
//! \param[in] hTlvTreeIn Contains the input data.
//! \param[out] pTlvTreeOut Contains the output data.
//! \return
//! - \ref SDI_STATUS_OK : if user command correctly executed.
//! - \ref SDI_STATUS_INVALID_DATA : if one of the parameters is not valid.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a transaction is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.
//! Any other status returned by the application, as this is kind of proprietary application commands.

int SDI_Generic_UserCommand (const int nAppliId, const int nCommandId, const TLV_TREE_NODE hTlvTreeIn, TLV_TREE_NODE * pTlvTreeOut);

//! @}

#endif // __SDI_PAYMENT_H__INCLUDED__
