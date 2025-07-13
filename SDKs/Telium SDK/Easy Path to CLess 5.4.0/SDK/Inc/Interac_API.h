/**
 * \file     Interac_API.h
 * \brief    This describes the Interac kernel API.
 * \details It consists of the following defines :
 *	- Transaction steps identifiers.
 *	- Specific Interac status codes.
 *	- Interac timers definition.
 *	- Error codes definitions.
 *	- Interac kernel API functions.
 *
 * \author    Ingenico
 * \author    Copyright (c) 2009 Ingenico, rue claude Chappe,\n
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


/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global definition //////////////////////////////////////////

//! \addtogroup InteracTransactionFlowSteps
//! @{
#define STEP_INTERAC_INITIAL							0x00								/*!< Interac Step : Initial process management. It consists of the starting Interac transaction step. */
#define STEP_INTERAC_FINAL_SELECTION					0x01								/*!< Interac Step : Performs the final card application selection process. The Interac reader performs certain checks on the data received in reply to the SELECT AID command as described in <i>Interac 1.2 specification Section 4.7.1.4</i>.<br>The Final SELECT card response and status word are provided by the custom application (application selection result performed by Entry Point). */
#define STEP_INTERAC_INITIATE_APPLI_PROCESSING			0x02								/*!< Interac Step : Performs the "Initiate Application Processing" step. The Interac reader initiates the transaction by issuing the <i>GET PROCESSING OPTIONS</i> command as described in <i>Interac 1.2 specification Section 4.7.2.2</i>.<br>The Interac card returns the AIP and the AFL. */
#define STEP_INTERAC_ODA_METHOD_SELECTION	    		0x10								/*!< Interac Step () : The Interac reader selects the offline data authentication method to be used in the transaction. As described in Section 2.3.2.7, it compares the functionality available on the card, as indicated in the AIP, with its own capabilities. The result of this process is a decision to perform CDA or not to perform any offline data authentication. */
#define STEP_INTERAC_READ_APPLI_DATA			    	0x11								/*!< Interac Step () : The Interac reader reads the necessary data using <i>READ RECORD</i> commands as specified in <i>Interac 1.2 specification, Section 2.2.3.4</i>. */
#define STEP_INTERAC_PROCESSING_RESTRICTIONS	    	0x12								/*!< Interac Step () : The Interac reader performs the Processing Restrictions function as specified in <i>Interac 1.2 specification, Section 4.7.4</i>. This includes application version number checking, application usage control checking and application effective/expiry dates checking. */
#define STEP_INTERAC_TERMINAL_RISK_MANAGEMENT	    	0x13								/*!< Interac Step () : The Interac reader performs Terminal Risk Management as specified in <i>Interac 1.2 specification, Section 4.7.2.1</i>. */
#define STEP_INTERAC_CVM_SELECTION			        	0x14								/*!< Interac Step () : The Interac reader selects a cardholder verification method as specified in <i>Interac 1.2 specification, Section 4.7.5</i>. The result of this function is stored as the Transaction CVM (\ref TAG_INTERAC_TRANSACTION_CVM). */
#define STEP_INTERAC_TERMINAL_ACTION_ANALYSIS   		0x15								/*!< Interac Step () : The Interac reader performs Terminal Action Analysis in order to decide whether the transaction should be approved offline, declined offline, or transmitted online. The Interac reader makes this decision based on the content of the TVR, the Issuer Action Codes and Terminal Action Codes as specified in <i>Interac 1.2 specification, Section 4.7.8</i>. */
#define STEP_INTERAC_GENERATE_AC	   		    		0x16								/*!< Interac Step () : The Interac reader issues a <i>GENERATE AC</i> command, as described in <i>Interac 1.2 specification, Section 2.2.3.2.5</i>, requesting a TC, ARQC or an AAC based on the results of Terminal Action Analysis. The Interac card performs its card risk management when it receives the <i>GENERATE AC</i> command, and may decide to complete the transaction online (ARQC), offline (TC) or decline the transaction (AAC). */
#define STEP_INTERAC_REMOVE_CARD	    				0x17								/*!< Interac Step () : This step is just there to indicate card read is complete and cardholder can remove the card from the field. It would be used for GUI customisation only. */
#define STEP_INTERAC_GET_CERTIFICATE	    			0x18								/*!< Interac Step () : This is a step where the kernel is looking for the transaction certificates for Offline Data Authentication. Usually, the kernel calls the application to request the transaction certificate.<br><br>The application shall provide the following data to the kernel to perform ODA :<br>	- \ref TAG_EMV_INT_CAPK_MODULUS containing the CA public key modulus.<br>	- \ref TAG_EMV_INT_CAPK_EXPONENT containing the CA public key exponent. */
#define STEP_INTERAC_ODA_ROUTER				        	0x19								/*!< Interac Step () : This choose the correct ODA step to execute (just reads a value and return the appropriate status code). */
#define STEP_INTERAC_CDA_PROCESSING	    	    		0x1A								/*!< Interac Step () : The Interac reader retrieves the ICC Public Key and verifies the SDAD generated by the Interac card as specified in <i>Interac 1.2 specification, Section 2.2.3.2.7</i>. */
#define STEP_INTERAC_EXCEPTION_FILE_GET_DATA		    0x1B								/*!< Interac Step () : This step is part of \ref STEP_INTERAC_TERMINAL_RISK_MANAGEMENT step. It prepares the necessary data to be check for exception file. The kernel does not manage the blacklist itself. This is the role of the custom application to manage it.<br><br>This step is only necessary to provide the following data to custom to check if PAN is present in the black list :<br>	- \ref TAG_EMV_APPLI_PAN to indicate the card PAN.<br>	- \ref TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER to indicate the PAN Sequence number (if present).<br><br>As output, custom provide the \ref TAG_KERNEL_PAN_IN_BLACK_LIST tag to indicate if PAN has been found in the exception file or not. */
#define STEP_INTERAC_EXCEPTION_FILE_CHECKING    		0x1C								/*!< Interac Step () : Based on the data returned by the custom on the \ref STEP_INTERAC_EXCEPTION_FILE_GET_DATA step, it sets the TVR if the PAN has been found in the exception file. */
#define STEP_INTERAC_COMPLETION							0x40								/*!< Interac Step : The Interac reader executes the Completion function. The exchange structure is filled with the transaction tags. Please refer to \ref Interac_DoTransaction() function for more information about the returned data. */
#define STEP_INTERAC_STOP								0x50								/*!< Interac Step : Last step of the transaction flow. It indicates transaction results shall be provided to the custom application. */
//! @}


//! \addtogroup InteracStatusCodes
//! @{
#define INTERAC_STATUS_OK   							0x0801								/*!< Specific result to manage Interac cards. */
#define INTERAC_STATUS_CDA								0x0802								/*!< Specific result to indicate CDA step is to be performed.  */
#define INTERAC_STATUS_APPLICATION_BLOCKED				0x0803								/*!< Specific result to indicate card returned 6285 to the FINAL Select. */
//! @}


//! \addtogroup InteracTimeMeasure
//! @{
#define INTERAC_TIME_TYPE_CARD							0x80000000  						/*!< Time measure is relative to card access. */
#define INTERAC_TIME_TYPE_FCT							0x40000000  						/*!< Time measure is relative to code execution. */
#define INTERAC_TIME_TYPE_SYSTEM						0x20000000  						/*!< Time measure is relative to system + manager + ... code execution. */

#define INTERAC_TIME_FCT_PRELIMINARY					INTERAC_TIME_TYPE_FCT+1				/*!< Time measure for Preliminary function execution. */
#define INTERAC_TIME_FCT_PRELIMINARY_END				INTERAC_TIME_TYPE_FCT+2 			/*!< Time measure end for Preliminary function execution. */
#define INTERAC_TIME_FCT_TXN							INTERAC_TIME_TYPE_FCT+3				/*!< Time measure for transaction function execution. */
#define INTERAC_TIME_FCT_TXN_END						INTERAC_TIME_TYPE_FCT+4				/*!< Time measure end for Transaction function execution. */
#define INTERAC_TIME_FCT_LOAD_DATA						INTERAC_TIME_TYPE_FCT+5				/*!< Time measure for Data function execution. */
#define INTERAC_TIME_FCT_LOAD_DATA_END					INTERAC_TIME_TYPE_FCT+6				/*!< Time measure end for Data function execution. */
#define INTERAC_TIME_FCT_GET_DATA						INTERAC_TIME_TYPE_FCT+7				/*!< Time measure for data retrieval function execution. */
#define INTERAC_TIME_FCT_GET_DATA_END					INTERAC_TIME_TYPE_FCT+8				/*!< Time measure end for data retrieval function execution. */
#define INTERAC_TIME_FCT_GET_ALL_DATA					INTERAC_TIME_TYPE_FCT+9				/*!< Time measure for obtain all data function execution. */
#define INTERAC_TIME_FCT_GET_ALL_DATA_END				INTERAC_TIME_TYPE_FCT+10			/*!< Time measure end for obtain all data function execution. */
//! @}


//! \addtogroup InteracErrorDefinition
//! @{
#define ERR_INTERAC_BASE                         		0x1A000000							/*!< Error Code Prefix identifying a Interac error. */

#define ERR_INTERAC_NO_TAG								0xFFFFFFFF							/*!< Indicates there is no concerned tag for the provided error. */
#define ERR_INTERAC_000001                       		ERR_INTERAC_BASE+0x000001			/*!< Interac error 01  : An error occurred when removing tag from the database (case where provided tag has length set to 0).<br>(Interac_Entry.c, __Interac_Entry_LoadTags).<br>() */
#define ERR_INTERAC_000002                       		ERR_INTERAC_BASE+0x000002			/*!< Interac error 02  : The list of provided tag has an incorrect format (parsing error).<br>(Interac_Entry.c, __Interac_Entry_LoadTags) */
#define ERR_INTERAC_000003                       		ERR_INTERAC_BASE+0x000003			/*!< Interac error 03  : An error occurred when adding the provided tag in the database.<br>(Interac_Entry.c, __Interac_Entry_Store_One_Tag) */
#define ERR_INTERAC_000004                       		ERR_INTERAC_BASE+0x000004			/*!< Interac error 04  : Unable to get the \ref TAG_KERNEL_DEBUG_TIME tag from the database (not present or error).<br>(Interac_Debug.c, Interac_Debug_TimeInit) */
#define ERR_INTERAC_000005                       		ERR_INTERAC_BASE+0x000005			/*!< Interac error 05  : An error occurred when adding the TAG_KERNEL_DEBUG_TIME tag in database for time initialisation.<br>(Interac_Debug.c, Interac_Debug_TimeInit) */
#define ERR_INTERAC_000006                       		ERR_INTERAC_BASE+0x000006			/*!< Interac error 06  : An error occurred when adding the provided tag in the database.<br>(Interac_Entry.c, __Interac_Entry_LoadTags) */
#define ERR_INTERAC_000007                       		ERR_INTERAC_BASE+0x000007			/*!< Interac error 07  : Unable to add \ref TAG_KERNEL_APPLICATION_NAME tag in the exchange buffer.<br>(Interac_Entry.c, __Interac_Entry_Get_Kernel_Infos) */
#define ERR_INTERAC_000008                       		ERR_INTERAC_BASE+0x000008			/*!< Interac error 08  : Unable to add \ref TAG_KERNEL_APPLICATION_IDENT tag in the exchange buffer.<br>(Interac_Entry.c, __Interac_Entry_Get_Kernel_Infos) */
#define ERR_INTERAC_000009                       		ERR_INTERAC_BASE+0x000009			/*!< Interac error 09  : Unable to add \ref TAG_KERNEL_APPLICATION_CRC tag in the exchange buffer.<br>(Interac_Entry.c, __Interac_Entry_Get_Kernel_Infos) */
#define ERR_INTERAC_00000A                       		ERR_INTERAC_BASE+0x00000A			/*!< Interac error 0A  : There is not enough space in the exchange buffer to store all the kernel information.<br>(Interac_Entry.c, __Interac_Entry_Get_Kernel_Infos) */
#define ERR_INTERAC_00000B                       		ERR_INTERAC_BASE+0x00000B			/*!< Interac error 0B  : An internal error occurred when getting the kernel information.<br>(Interac_Entry.c, __Interac_Entry_Get_Kernel_Infos) */
#define ERR_INTERAC_00000C                       		ERR_INTERAC_BASE+0x00000C			/*!< Interac error 0C  : Unable to add the retrieved tag in the exchange buffer.<br>(Interac_Entry.c, __Interac_Entry_Get_Data) */
#define ERR_INTERAC_00000D                       		ERR_INTERAC_BASE+0x00000D			/*!< Interac error 0D  : An error occurred when getting the provided tag from the database.<br>(Interac_Entry.c, __Interac_Entry_Get_Data) */
#define ERR_INTERAC_00000E                       		ERR_INTERAC_BASE+0x00000E			/*!< Interac error 0E  : Unable to add the retrieved tag in the exchange buffer.<br>(Interac_Entry.c, __Interac_Entry_Get_All_Data) */
#define ERR_INTERAC_00000F                       		ERR_INTERAC_BASE+0x00000F			/*!< Interac error 0F  : An error occurred when creating the proprietary data storage in the database.<br>(Interac_Common.c, Interac_Common_LoadTagsFromExchangeStructToDatabase) */
#define ERR_INTERAC_000010                       		ERR_INTERAC_BASE+0x000010			/*!< Interac error 10  : SELECT response is not correctly formatted (padding outside the template, or incorrect length).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ExtractAndParseFciTemplate) */
#define ERR_INTERAC_000011                       		ERR_INTERAC_BASE+0x000011			/*!< Interac error 11  : A mandatory card data is missing : \ref TAG_EMV_FCI_TEMPLATE. Tag found is not the expected one.<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ExtractAndParseFciTemplate) */
#define ERR_INTERAC_000012                       		ERR_INTERAC_BASE+0x000012			/*!< Interac error 12  : FCI Template has bad format.<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ExtractAndParseFciTemplate) */
#define ERR_INTERAC_000013                       		ERR_INTERAC_BASE+0x000013			/*!< Interac error 13  : The terminal shall discard tags that are not expected in the FCI Proprietary Template (concerned tag is provided).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ParseFciProprietaryTemplate) */
#define ERR_INTERAC_000014                       		ERR_INTERAC_BASE+0x000014			/*!< Interac error 14  : A parsing error occurred on the card response (extracting data from FCI Proprietary Template).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ParseFciProprietaryTemplate) */
#define ERR_INTERAC_000015                       		ERR_INTERAC_BASE+0x000015			/*!< Interac error 15  : The terminal shall ignore tags that are not expected in the FCI (concerned tag is provided).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ExtractAndParseFciTemplate) */
#define ERR_INTERAC_000016                       		ERR_INTERAC_BASE+0x000016			/*!< Interac error 16  : A parsing error occurred on the card response (extracting data from FCI template).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ExtractAndParseFciTemplate) */
#define ERR_INTERAC_000017                       		ERR_INTERAC_BASE+0x000017			/*!< Interac error 17  : Missing mandatory data in the SELECT response (in the 6F template) : \ref TAG_EMV_DF_NAME.<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ExtractAndParseFciTemplate) */
#define ERR_INTERAC_000018                       		ERR_INTERAC_BASE+0x000018			/*!< Interac error 18  : Missing mandatory data in the SELECT response (in the 6F template) : \ref TAG_EMV_FCI_PROPRIETARY_TEMPLATE.<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ExtractAndParseFciTemplate) */
#define ERR_INTERAC_000019                       		ERR_INTERAC_BASE+0x000019			/*!< Interac error 19  : Tag \ref TAG_EMV_FCI_PROPRIETARY_TEMPLATE is present but its length is 0.<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ExtractAndParseFciTemplate) */
#define ERR_INTERAC_00001A                       		ERR_INTERAC_BASE+0x00001A			/*!< Interac error 1A  : A critical tag is redundant within the card (concerned tag is provided).<br>(Interac_Txn_FinalSelect.c, __Interac_Common_CheckAndStore) */
#define ERR_INTERAC_00001B                       		ERR_INTERAC_BASE+0x00001B			/*!< Interac error 1B  : A critical tag has a bad format (bad length or incorrect format)(concerned tag is provided).<br>(Interac_Txn_FinalSelect.c, __Interac_Common_CheckAndStore) */
#define ERR_INTERAC_00001C                       		ERR_INTERAC_BASE+0x00001C			/*!< Interac error 1C  : There is not enough memory to add the tag in the database (concerned tag is provided).<br>(Interac_Txn_FinalSelect.c, __Interac_Common_CheckAndStore) */
#define ERR_INTERAC_00001D                       		ERR_INTERAC_BASE+0x00001D			/*!< Interac error 1D  : An internal error occurred when adding the tag in the database (concerned tag is provided).<br>(Interac_Txn_FinalSelect.c, __Interac_Common_CheckAndStore) */
#define ERR_INTERAC_00001E                       		ERR_INTERAC_BASE+0x00001E			/*!< Interac error 1E  : An error occurred as FCI Proprietary Template is not correctly stored in the database (it shall be present, i.e. length != 0 and value != NULL).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ParseFciProprietaryTemplate) */
#define ERR_INTERAC_00001F                       		ERR_INTERAC_BASE+0x00001F			/*!< Interac error 1F  : FCI Issuer Discretionary Data parsing error.<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ParseFciIssuerDiscretionaryData) */
#define ERR_INTERAC_000020                       		ERR_INTERAC_BASE+0x000020			/*!< Interac error 20  : This function cannot be called if FCI Issuer Discretionary Data Template is not in database (shall be checked before calling this function).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ParseFciIssuerDiscretionaryData) */
#define ERR_INTERAC_000021                       		ERR_INTERAC_BASE+0x000021			/*!< Interac error 21  : Unable to get the Final SELECT Response (that shall be provided by the custom application).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse) */
#define ERR_INTERAC_000022                       		ERR_INTERAC_BASE+0x000022			/*!< Interac error 22  : Final SELECT status word indicates card is blocked (0x6A81).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse) */
#define ERR_INTERAC_000023                       		ERR_INTERAC_BASE+0x000023			/*!< Interac error 23  : Final SELECT status word indicates application is blocked (0x6283).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse) */
#define ERR_INTERAC_000024                       		ERR_INTERAC_BASE+0x000024			/*!< Interac error 24  : Final SELECT status word indicates an unexpected status word.<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse) */
#define ERR_INTERAC_000025                       		ERR_INTERAC_BASE+0x000025			/*!< Interac error 25  : Unable to get the Final SELECT status word (that shall be provided by the custom application).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse) */
#define ERR_INTERAC_000026                       		ERR_INTERAC_BASE+0x000026			/*!< Interac error 26  : An error occurred when adding tag \ref TAG_KERNEL_SELECTED_PREFERED_LANGUAGE in the database (Data Storage status is provided).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_LanguageSelection) */
#define ERR_INTERAC_000027                       		ERR_INTERAC_BASE+0x000027			/*!< Interac error 27  : An error occurred when initialising the TVR in the database.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_InitTvrCvmResults) */
#define ERR_INTERAC_000028                       		ERR_INTERAC_BASE+0x000028			/*!< Interac error 28  : An error occurred when initialising the CVM Results in the database.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_InitTvrCvmResults) */
#define ERR_INTERAC_000029                       		ERR_INTERAC_BASE+0x000029			/*!< Interac error 29  : A mandatory data is missing : \ref TAG_INTERAC_TERMINAL_CAPABILITIES_CVM_REQ.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_SetTerminalCapabilities) */
#define ERR_INTERAC_00002A                       		ERR_INTERAC_BASE+0x00002A			/*!< Interac error 2A  : A mandatory data is missing : \ref TAG_INTERAC_TERMINAL_CAPABILITIES_NO_CVM_REQ.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_SetTerminalCapabilities) */
#define ERR_INTERAC_00002B                       		ERR_INTERAC_BASE+0x00002B			/*!< Interac error 2B  : A mandatory data is missing : \ref TAG_INTERAC_TERMINAL_CAPABILITIES_NO_CVM_REQ.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_SetTerminalCapabilities) */
#define ERR_INTERAC_00002C                       		ERR_INTERAC_BASE+0x00002C			/*!< Interac error 2C  : An error occurred when adding \ref TAG_EMV_TERMINAL_CAPABILITIES tag in the database.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_SetTerminalCapabilities) */

#define ERR_INTERAC_000032                       		ERR_INTERAC_BASE+0x000032			/*!< Interac error 32  : An error occurred when adding \ref TAG_EMV_AIP or \ref TAG_EMV_AFL in the database.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_ResponseAnalysisFormat2) */
#define ERR_INTERAC_000033                       		ERR_INTERAC_BASE+0x000033			/*!< Interac error 33  : Card returned a redundant tag (\ref TAG_EMV_AIP or \ref TAG_EMV_AFL).<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_ResponseAnalysisFormat2) */
#define ERR_INTERAC_000034                       		ERR_INTERAC_BASE+0x000034			/*!< Interac error 34  : Parsing error in the format 2 response template.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_ResponseAnalysisFormat2) */
#define ERR_INTERAC_000035                       		ERR_INTERAC_BASE+0x000035			/*!< Interac error 35  : Missing mandatory data within the card (\ref TAG_EMV_AFL).<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_ResponseAnalysisFormat2) */
#define ERR_INTERAC_000036                       		ERR_INTERAC_BASE+0x000036			/*!< Interac error 36  : Missing mandatory data within the card (\ref TAG_EMV_AIP).<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_ResponseAnalysisFormat2) */
#define ERR_INTERAC_000037                       		ERR_INTERAC_BASE+0x000037			/*!< Interac error 37  : Card GPO response has not a correct format (bad TLV coding).<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_CardResponseAnalysis) */
#define ERR_INTERAC_000038                       		ERR_INTERAC_BASE+0x000038			/*!< Interac error 38  : Card GPO response has no data.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_CardResponseAnalysis) */
#define ERR_INTERAC_000039                       		ERR_INTERAC_BASE+0x000039			/*!< Interac error 39  : Card GPO response has not a correct format (data outside the template).<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_CardResponseAnalysis) */
#define ERR_INTERAC_00003A                      		ERR_INTERAC_BASE+0x00003A			/*!< Interac error 3A  : Card responds with "Format 1" but not defined in Interac Specification and no way to extract CTI.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_CardResponseAnalysis) */
#define ERR_INTERAC_00003B                       		ERR_INTERAC_BASE+0x00003B			/*!< Interac error 3B  : An error occurred when analyses the format 2 GPO response data.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_CardResponseAnalysis) */
#define ERR_INTERAC_00003C                       		ERR_INTERAC_BASE+0x00003C			/*!< Interac error 3C  : Card responds with an unknown format, transaction is to be terminated.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_CardResponseAnalysis) */
#define ERR_INTERAC_00003D                       		ERR_INTERAC_BASE+0x00003D			/*!< Interac error 3D  : Status word for GPO is not x9000.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_CardResponseAnalysis) */
#define ERR_INTERAC_00003E                       		ERR_INTERAC_BASE+0x00003E			/*!< Interac error 3E  : An error occurred when building the PDOL.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_BuildAndSendGpoCommand) */
#define ERR_INTERAC_00003F                       		ERR_INTERAC_BASE+0x00003F			/*!< Interac error 3F  : An error occurred when adding constructed PDOL value in the database.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_BuildAndSendGpoCommand) */
#define ERR_INTERAC_000040                       		ERR_INTERAC_BASE+0x000040			/*!< Interac error 40  : Unable to build the Get Processing Options command.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_BuildAndSendGpoCommand) */
#define ERR_INTERAC_000041                       		ERR_INTERAC_BASE+0x000041			/*!< Interac error 41  : Communication error with the card (GPO command).<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_BuildAndSendGpoCommand) */
#define ERR_INTERAC_000042                       		ERR_INTERAC_BASE+0x000042			/*!< Interac error 42  : GPO Card response analysis failed.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_BuildAndSendGpoCommand) */

#define ERR_INTERAC_000044                       		ERR_INTERAC_BASE+0x000044			/*!< Interac error 44  : Specific result to indicate card returned 6285 to the FINAL Select.<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse) */


#define ERR_INTERAC_000096                       		ERR_INTERAC_BASE+0x000096			/*!< Interac error 96  : An error occurred when adding the tag in exchange data structure (tag is provided).<br>(Interac_Txn_Completion.c, __Interac_Txn_Completion_AddTagToStructure) */
#define ERR_INTERAC_000097                       		ERR_INTERAC_BASE+0x000097			/*!< Interac error 97  : An error occurred when adding common tags in the exchange data structure.<br>(Interac_Txn_Completion.c, __Interac_Txn_Completion_FillExchangeStructure) */
#define ERR_INTERAC_000098                       		ERR_INTERAC_BASE+0x000098			/*!< Interac error 98  : An error occurred when adding tags in the exchange data structure.<br>(Interac_Txn_Completion.c, __Interac_Txn_Completion_FillExchangeStructure) */
#define ERR_INTERAC_000099                       		ERR_INTERAC_BASE+0x000099			/*!< Interac error 99  : An error occurred when adding tags in the exchange data structure.<br>(Interac_Txn_Completion.c, __Interac_Txn_Completion_FillExchangeStructure) */
#define ERR_INTERAC_00009A                       		ERR_INTERAC_BASE+0x00009A			/*!< Interac error 9A  : Unknown Interac card type.<br>(Interac_Txn_Completion.c, __Interac_Txn_Completion_SetTransactionOutcome) */
#define ERR_INTERAC_00009B                       		ERR_INTERAC_BASE+0x00009B			/*!< Interac error 9B  : Incorrect Interac card type.<br>(Interac_Txn_Completion.c, __Interac_Txn_Completion_GetInteracCardType) */
#define ERR_INTERAC_00009C                       		ERR_INTERAC_BASE+0x00009C			/*!< Interac error 9C  : Invalid input data (pointer on data exchange is NULL).<br>(Interac_Txn_Completion.c, __Interac_Txn_Completion_FillExchangeStructure) */
#define ERR_INTERAC_00009D                       		ERR_INTERAC_BASE+0x00009D			/*!< Interac error 9D  : Unable to add \ref TAG_INTERAC_TRANSACTION_OUTCOME tag in the database.<br>(Interac_Common.c, Interac_Common_SetTransactionOutcome) */
#define ERR_INTERAC_00009E                       		ERR_INTERAC_BASE+0x00009E			/*!< Interac error 9E  : An error occurred, there is not enough memory in the database to add ODA data.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_AddDataPartOfOda) */
#define ERR_INTERAC_00009F                       		ERR_INTERAC_BASE+0x00009F			/*!< Interac error 9F  : An error occurred when adding TAG_INTERAC_INT_IS_SFI_ERROR tag in the database.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_SetIsSfiCorrect) */
#define ERR_INTERAC_0000A0								ERR_INTERAC_BASE+0x0000A0			/*!< Interac error A0  : An error occurred when building the Read Record command.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_ReadApplicationData) */
#define ERR_INTERAC_0000A1                       		ERR_INTERAC_BASE+0x0000A1			/*!< Interac error A1  : Communication error with the card (Read Application Data).<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_ReadApplicationData) */
#define ERR_INTERAC_0000A2                       		ERR_INTERAC_BASE+0x0000A2			/*!< Interac error A2  : Read Record Card response analysis failed.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_ReadApplicationData) */
#define ERR_INTERAC_0000A3                       		ERR_INTERAC_BASE+0x0000A3			/*!< Interac error A3  : Missing mandatory tag : \ref TAG_EMV_APPLI_EXPIRATION_DATE.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CheckMandatoryDataPresence) */
#define ERR_INTERAC_0000A4                       		ERR_INTERAC_BASE+0x0000A4			/*!< Interac error A4  : Missing mandatory tag : \ref TAG_EMV_APPLI_PAN.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CheckMandatoryDataPresence) */
#define ERR_INTERAC_0000A5                       		ERR_INTERAC_BASE+0x0000A5			/*!< Interac error A5  : Missing mandatory tag : \ref TAG_EMV_CDOL_1.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CheckMandatoryDataPresence) */


#define ERR_INTERAC_0000A7                       		ERR_INTERAC_BASE+0x0000A7			/*!< Interac error A7  : Missing mandatory data : \ref TAG_EMV_AFL.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CheckAflAndReadApplicationData) */
#define ERR_INTERAC_0000A8                       		ERR_INTERAC_BASE+0x0000A8			/*!< Interac error A8  : An error occurred when reading the application data within the card.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CheckAflAndReadApplicationData) */
#define ERR_INTERAC_0000A9                       		ERR_INTERAC_BASE+0x0000A9			/*!< Interac error A9  : Card response to Read Record has not a correct format (bad TLV coding).<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000AA                       		ERR_INTERAC_BASE+0x0000AA			/*!< Interac error AA  : Card response to Read Record has no data.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000AB                       		ERR_INTERAC_BASE+0x0000AB			/*!< Interac error AB  : Card response to Read Record has not a correct format (data outside the template).<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000AC                       		ERR_INTERAC_BASE+0x0000AC			/*!< Interac error AC  : Card responds to Read Record with template different from 0x70, terminate the transaction.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000AD                       		ERR_INTERAC_BASE+0x0000AD			/*!< Interac error AD  : An error occurred when adding data that are part of ODA in the database.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000AE                       		ERR_INTERAC_BASE+0x0000AE			/*!< Interac error AE  : Card returned a redundant tag in a Read Record (tag is provided).<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000AF                       		ERR_INTERAC_BASE+0x0000AF			/*!< Interac error AF  : Card returned a tag with a bad format in a Read Record (tag is provided).<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000B0                       		ERR_INTERAC_BASE+0x0000B0			/*!< Interac error B0  : A database error occurred when storing data provided in Read Record.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000B1                       		ERR_INTERAC_BASE+0x0000B1			/*!< Interac error B1  : Card response to Read Record is not correctly formatted (BER-TLV parsing error).<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000B2                       		ERR_INTERAC_BASE+0x0000B2			/*!< Interac error B2  : An error occurred when setting data indicating a SFI format error.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000B3                       		ERR_INTERAC_BASE+0x0000B3			/*!< Interac error B3  : Card responds to Read Record with template different from 0x70, SFI is between 10 and 30.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000B4                       		ERR_INTERAC_BASE+0x0000B4			/*!< Interac error B4  : Card responds to Read Record with data that is NOT part of ODA, but template different from 0x70 or there is data outside the template, or response is not BER-TLV coded (SFI is between 11 and 30).<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000B5                       		ERR_INTERAC_BASE+0x0000B5			/*!< Interac error B5  : An error occurred when adding data that are part of ODA in the database.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000B6                       		ERR_INTERAC_BASE+0x0000B6			/*!< Interac error B6  : Bad SFI (SFI > 30).<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000B7                       		ERR_INTERAC_BASE+0x0000B7			/*!< Interac error B7  : Status Word is not x9000 to the READ RECORD response.<br>(Interac_Txn_rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_0000B8                       		ERR_INTERAC_BASE+0x0000B8			/*!< Interac error B8  : A database error occurred when getting the card AVN.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_VersionNumberChecking) */
#define ERR_INTERAC_0000B9                       		ERR_INTERAC_BASE+0x0000B9			/*!< Interac error B9  : Missing mandatory terminal data : \ref TAG_INTERAC_INT_TERMINAL_AVN_LIST.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_VersionNumberChecking) */
#define ERR_INTERAC_0000BA                       		ERR_INTERAC_BASE+0x0000BA			/*!< Interac error BA  : Database error when adding \ref TAG_EMV_APPLI_VERSION_NUMBER_TERM in database.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_VersionNumberChecking) */
#define ERR_INTERAC_0000BB                       		ERR_INTERAC_BASE+0x0000BB			/*!< Interac error BB  : An error occurred when setting the TVR in the database.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_VersionNumberChecking) */
#define ERR_INTERAC_0000BC                       		ERR_INTERAC_BASE+0x0000BC			/*!< Interac error BC  : Missing mandatory terminal data : \ref TAG_EMV_INT_TRANSACTION_TYPE.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_ApplicationUsageControl) */
#define ERR_INTERAC_0000BD                       		ERR_INTERAC_BASE+0x0000BD			/*!< Interac error BD  : Missing mandatory terminal data : \ref TAG_EMV_TERMINAL_COUNTRY_CODE.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_ApplicationUsageControl) */
#define ERR_INTERAC_0000BE                       		ERR_INTERAC_BASE+0x0000BE			/*!< Interac error BE  : Application Usage Control is not correct.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_ApplicationUsageControl) */
#define ERR_INTERAC_0000BF                       		ERR_INTERAC_BASE+0x0000BF			/*!< Interac error BF  : An error occurred when setting the \ref TAG_EMV_TVR in the database.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_ApplicationUsageControl) */
#define ERR_INTERAC_0000C0                       		ERR_INTERAC_BASE+0x0000C0			/*!< Interac error C0  : A mandatory data is missing : \ref TAG_EMV_TRANSACTION_DATE.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_ApplicationDatesCheckings) */
#define ERR_INTERAC_0000C1                       		ERR_INTERAC_BASE+0x0000C1			/*!< Interac error C1  : Application is not yet effective, set "Application not yet effective" bit in the TVR (B2b6).<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_ApplicationDatesCheckings) */
#define ERR_INTERAC_0000C2                       		ERR_INTERAC_BASE+0x0000C2			/*!< Interac error C2  : An error occurred when setting the TVR in the database.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_ApplicationDatesCheckings) */
#define ERR_INTERAC_0000C3                       		ERR_INTERAC_BASE+0x0000C3			/*!< Interac error C3  : Application is expired, set "Expired Application" bit in the TVR (B2b7).<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_ApplicationDatesCheckings) */
#define ERR_INTERAC_0000C4                       		ERR_INTERAC_BASE+0x0000C4			/*!< Interac error C4  : An error occurred when setting the TVR in the database.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_ApplicationDatesCheckings) */
#define ERR_INTERAC_0000C5                       		ERR_INTERAC_BASE+0x0000C5			/*!< Interac error C5  : A mandatory terminal data is missing : \ref TAG_EP_AID_ADDITIONAL_RESULTS.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_Pre_Initiation) */
#define ERR_INTERAC_0000C6                       		ERR_INTERAC_BASE+0x0000C6			/*!< Interac error C6  : Contactless Floor Limit Exceeded, an error occurred when setting the TVR in the database.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_Pre_Initiation) */
#define ERR_INTERAC_0000C7                       		ERR_INTERAC_BASE+0x0000C7			/*!< Interac error C7  : PAN is in the Black list, an error occurred when setting the TVR in the database.<br>(Interac_Txn_Trm.c, __Interac_Txn_Trm_CheckPanPresenceInBlackList) */
#define ERR_INTERAC_0000C8                       		ERR_INTERAC_BASE+0x0000C8			/*!< Interac error C8  : A database error occurred when getting the \ref TAG_KERNEL_PAN_IN_BLACK_LIST tag.<br>(Interac_Txn_Trm.c, __Interac_Txn_Trm_CheckPanPresenceInBlackList) */
#define ERR_INTERAC_0000C9                       		ERR_INTERAC_BASE+0x0000C9			/*!< Interac error C9  : An error occurred when setting the CVR Result in the database (Rule).<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_SetCvrInDatabase) */
#define ERR_INTERAC_0000CA                       		ERR_INTERAC_BASE+0x0000CA			/*!< Interac error CA  : An error occurred when setting the CVR Result in the database (Condition).<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_SetCvrInDatabase) */
#define ERR_INTERAC_0000CB                       		ERR_INTERAC_BASE+0x0000CB			/*!< Interac error CB  : An error occurred when setting the CVR Result in the database (Result).<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_SetCvrInDatabase) */
#define ERR_INTERAC_0000CC                       		ERR_INTERAC_BASE+0x0000CC			/*!< Interac error CC  : An unexpected CVM method has been provided.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_SetTransactionCvm) */
#define ERR_INTERAC_0000CD                       		ERR_INTERAC_BASE+0x0000CD			/*!< Interac error CD  : A database error occurred when getting the \ref TAG_EMV_CVM_LIST_CARD tag from the database.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_CheckCvmListPresence) */
#define ERR_INTERAC_0000CE                       		ERR_INTERAC_BASE+0x0000CE			/*!< Interac error CE  : The is no CVR in the CVM List.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_CheckCvmListPresence) */
#define ERR_INTERAC_0000CF                       		ERR_INTERAC_BASE+0x0000CF			/*!< Interac error CF  : CVM List is empty or does not have CVR, an error occurred when setting the TVR in the database.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_CheckCvmListPresence) */
#define ERR_INTERAC_0000D0                       		ERR_INTERAC_BASE+0x0000D0			/*!< Interac error D0  : There is not an even number of bytes for couple of CVM Method / CVM Condition.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000D1                       		ERR_INTERAC_BASE+0x0000D1			/*!< Interac error D1  : A mandatory terminal data is missing : \ref TAG_EMV_TERMINAL_CAPABILITIES.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000D2                       		ERR_INTERAC_BASE+0x0000D2			/*!< Interac error D2  : A mandatory terminal data is missing : \ref TAG_EMV_TERMINAL_TYPE.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000D3                       		ERR_INTERAC_BASE+0x0000D3			/*!< Interac error D3  : A mandatory terminal data is missing : \ref TAG_EMV_INT_TRANSACTION_TYPE.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000D4                       		ERR_INTERAC_BASE+0x0000D4			/*!< Interac error D4  : A mandatory terminal data is missing : \ref TAG_EMV_TRANSACTION_CURRENCY_CODE.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000D5                       		ERR_INTERAC_BASE+0x0000D5			/*!< Interac error D5  : A mandatory terminal data is missing : \ref TAG_EMV_AMOUNT_AUTH_BIN.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000D6                       		ERR_INTERAC_BASE+0x0000D6			/*!< Interac error D6  : An error occurred when getting the \ref TAG_EMV_APPLI_CURRENCY_CODE tag from the database.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000D7                       		ERR_INTERAC_BASE+0x0000D7			/*!< Interac error D7  : An error occurred when setting the Interac Transaction CVM.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000D8                       		ERR_INTERAC_BASE+0x0000D8			/*!< Interac error D8  : Online PIN method, an error occurred when setting the TVR in the database.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000D9                       		ERR_INTERAC_BASE+0x0000D9			/*!< Interac error D9  : Unrecognised method, an error occurred when setting the TVR in the database.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000DA                       		ERR_INTERAC_BASE+0x0000DA			/*!< Interac error DA  : An error occurred when setting the Transaction CVM in the database.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000DB                       		ERR_INTERAC_BASE+0x0000DB			/*!< Interac error DB  : CVM processing required and no CVM performed, terminate in favour of another interface.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_0000DC                       		ERR_INTERAC_BASE+0x0000DC			/*!< Interac error DC  : A database error occurred when getting the TAC from the database.<br>(Interac_Txn_Taa.c, __Interac_Txn_Taa_ActionCodeMatchChecking) */
#define ERR_INTERAC_0000DD                       		ERR_INTERAC_BASE+0x0000DD			/*!< Interac error DD  : A database error occurred when getting the IAC from the database.<br>(Interac_Txn_Taa.c, __Interac_Txn_Taa_ActionCodeMatchChecking) */
#define ERR_INTERAC_0000DE                       		ERR_INTERAC_BASE+0x0000DE			/*!< Interac error DE  : Missing mandatory data : \ref TAG_EMV_TVR.<br>(Interac_Txn_Taa.c, __Interac_Txn_Taa_Process) */
#define ERR_INTERAC_0000DF                       		ERR_INTERAC_BASE+0x0000DF			/*!< Interac error DF  : Missing mandatory data : \ref TAG_EMV_TERMINAL_TYPE.<br>(Interac_Txn_Taa.c, __Interac_Txn_Taa_Process) */
#define ERR_INTERAC_0000E0                       		ERR_INTERAC_BASE+0x0000E0			/*!< Interac error E0  : An error occurred during the Action Code Denial processing.<br>(Interac_Txn_Taa.c, __Interac_Txn_Taa_Process) */
#define ERR_INTERAC_0000E1                       		ERR_INTERAC_BASE+0x0000E1			/*!< Interac error E1  : An error occurred during the Action Code Online processing.<br>(Interac_Txn_Taa.c, __Interac_Txn_Taa_Process) */
#define ERR_INTERAC_0000E2                       		ERR_INTERAC_BASE+0x0000E2			/*!< Interac error E2  : An error occurred when adding the \ref TAG_INTERAC_INT_GENAC_REF_CTRL_PARAMETER tag in the database.<br>(Interac_Txn_Taa.c, __Interac_Txn_Taa_Process) */
#define ERR_INTERAC_0000E3                       		ERR_INTERAC_BASE+0x0000E3			/*!< Interac error E3  : An error occurred during the Action Code Default processing.<br>(Interac_Txn_Taa.c, __Interac_Txn_Taa_Process) */
#define ERR_INTERAC_0000E4                       		ERR_INTERAC_BASE+0x0000E4			/*!< Interac error E4  : An error occurred when adding the \ref TAG_INTERAC_INT_TAC_IAC_DEFAULT_MATCHED tag in the database.<br>(Interac_Txn_Taa.c, __Interac_Txn_Taa_Process) */
#define ERR_INTERAC_0000E5                       		ERR_INTERAC_BASE+0x0000E5			/*!< Interac error E5  : An error occurred when adding \ref TAG_EMV_CRYPTOGRAM_INFO_DATA in the database.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat1) */
#define ERR_INTERAC_0000E6                       		ERR_INTERAC_BASE+0x0000E6			/*!< Interac error E6  : An error occurred when adding \ref TAG_EMV_ATC in the database.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat1) */
#define ERR_INTERAC_0000E7                       		ERR_INTERAC_BASE+0x0000E7			/*!< Interac error E7  : An error occurred when adding \ref TAG_EMV_APPLICATION_CRYPTOGRAM in the database.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat1) */
#define ERR_INTERAC_0000E8                       		ERR_INTERAC_BASE+0x0000E8			/*!< Interac error E8  : An error occurred when adding \ref TAG_EMV_ISSUER_APPLI_DATA in the database.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat1) */
#define ERR_INTERAC_0000E9                       		ERR_INTERAC_BASE+0x0000E9			/*!< Interac error E9  : Template format 1 is too small.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat1) */
#define ERR_INTERAC_0000EA                       		ERR_INTERAC_BASE+0x0000EA			/*!< Interac error EA  : Template format 1 is too long.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat1) */
#define ERR_INTERAC_0000EB                       		ERR_INTERAC_BASE+0x0000EB			/*!< Interac error EB  : An error occurred when adding the \ref TAG_INTERAC_INT_GENAC_RESPONSE_DATA tag in the database.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat2) */
#define ERR_INTERAC_0000EC                       		ERR_INTERAC_BASE+0x0000EC			/*!< Interac error EC  : Card returned a redundant tag (redundant tag is provided).<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat2) */
#define ERR_INTERAC_0000ED                       		ERR_INTERAC_BASE+0x0000ED			/*!< Interac error ED  : Card returned a tag with a bad format (tag is provided).<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat2) */
#define ERR_INTERAC_0000EE                       		ERR_INTERAC_BASE+0x0000EE			/*!< Interac error EE  : A database error occured (Database status is provided).<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat2) */
#define ERR_INTERAC_0000EF                       		ERR_INTERAC_BASE+0x0000EF			/*!< Interac error EF  : An error occured when setting the Transaction CVM in the database.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_CheckAipSupportCvm) */
#define ERR_INTERAC_0000F0                       		ERR_INTERAC_BASE+0x0000F0			/*!< Interac error F0  : An error occured when setting the Transaction CVM in the database.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_CheckCvmListPresence) */
#define ERR_INTERAC_0000F1                       		ERR_INTERAC_BASE+0x0000F1			/*!< Interac error F1  : Parsing error in the format 2 response template.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat2) */
#define ERR_INTERAC_0000F2                       		ERR_INTERAC_BASE+0x0000F2			/*!< Interac error F2  : Missing ICC mandatory data : \ref TAG_EMV_CRYPTOGRAM_INFO_DATA.<br>(Interac_Txn_OdaRouter.c, __Interac_Txn_OdaRouter_CheckMandatoryDataPresence) */
#define ERR_INTERAC_0000F3                       		ERR_INTERAC_BASE+0x0000F3			/*!< Interac error F3  : Missing ICC mandatory data : \ref TAG_EMV_ATC.<br>(Interac_Txn_OdaRouter.c, __Interac_Txn_OdaRouter_CheckMandatoryDataPresence) */
#define ERR_INTERAC_0000F4                       		ERR_INTERAC_BASE+0x0000F4			/*!< Interac error F4  : Missing ICC mandatory data : \ref TAG_EMV_APPLICATION_CRYPTOGRAM.<br>(Interac_Txn_OdaRouter.c, __Interac_Txn_OdaRouter_CheckMandatoryDataPresence) */
#define ERR_INTERAC_0000F5                       		ERR_INTERAC_BASE+0x0000F5			/*!< Interac error F5  : Missing ICC mandatory data : \ref TAG_EMV_SIGNED_DYNAMIC_APPLI_DATA.<br>(Interac_Txn_OdaRouter.c, __Interac_Txn_OdaRouter_CheckMandatoryDataPresence) */
#define ERR_INTERAC_0000F6                       		ERR_INTERAC_BASE+0x0000F6			/*!< Interac error F6  : Card response has not a correct format (bad TLV coding).<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_CardResponseAnalysis) */
#define ERR_INTERAC_0000F7                       		ERR_INTERAC_BASE+0x0000F7			/*!< Interac error F7  : Card response has no data.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_CardResponseAnalysis) */
#define ERR_INTERAC_0000F8                       		ERR_INTERAC_BASE+0x0000F8			/*!< Interac error F8  : Card response has not a correct format (data outside the template).<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_CardResponseAnalysis) */
#define ERR_INTERAC_0000F9                       		ERR_INTERAC_BASE+0x0000F9			/*!< Interac error F9  : An error occurred when analyses the format 1 Generate AC response data.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_CardResponseAnalysis) */
#define ERR_INTERAC_0000FA                       		ERR_INTERAC_BASE+0x0000FA			/*!< Interac error FA  : An error occurred when analyses the format 2 Generate AC response data.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_CardResponseAnalysis) */
#define ERR_INTERAC_0000FB                       		ERR_INTERAC_BASE+0x0000FB			/*!< Interac error FB  : Merchant forced transaction online, an error occurred when setting the TVR in the database.<br>(Interac_Txn_Taa.c, __Interac_Txn_Taa_CheckMerchantForcedOnline) */
#define ERR_INTERAC_0000FC                       		ERR_INTERAC_BASE+0x0000FC			/*!< Interac error FC  : Card responds with an unknown format, transaction is to be terminated.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_CardResponseAnalysis) */
#define ERR_INTERAC_0000FD                       		ERR_INTERAC_BASE+0x0000FD			/*!< Interac error FD  : Status word for Generate AC is not x9000.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_CardResponseAnalysis) */
#define ERR_INTERAC_0000FE                       		ERR_INTERAC_BASE+0x0000FE			/*!< Interac error FE  : Mandatory data checking failed.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_CardResponseAnalysis) */
#define ERR_INTERAC_0000FF                       		ERR_INTERAC_BASE+0x0000FF			/*!< Interac error FF  : Missing mandatory data : \ref TAG_EMV_CDOL_1.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_BuildAndSendGenerateAcCommand) */
#define ERR_INTERAC_000100                       		ERR_INTERAC_BASE+0x000100			/*!< Interac error 100 : An error occurred when building the CDOL1.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_BuildAndSendGenerateAcCommand) */
#define ERR_INTERAC_000101                       		ERR_INTERAC_BASE+0x000101			/*!< Interac error 101 : An error occurred when adding constructed CDOL1 value in the database.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_BuildAndSendGenerateAcCommand) */
#define ERR_INTERAC_000102                       		ERR_INTERAC_BASE+0x000102			/*!< Interac error 102 : Unable to build the Generate AC command.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_BuildAndSendGenerateAcCommand) */
#define ERR_INTERAC_000103                       		ERR_INTERAC_BASE+0x000103			/*!< Interac error 103 : Communication error with the card.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_BuildAndSendGenerateAcCommand) */
#define ERR_INTERAC_000104                       		ERR_INTERAC_BASE+0x000104			/*!< Interac error 104 : Generate AC Card response analysis failed.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_BuildAndSendGenerateAcCommand) */
#define ERR_INTERAC_000105                       		ERR_INTERAC_BASE+0x000105			/*!< Interac error 105 : There is not enough memory in the shared exchange structure to add the TAG_EMV_DF_NAME.<br>(Interac_Txn_GetCertificate.c, __Interac_Txn_GetCertificate_FillOutputStructure) */
#define ERR_INTERAC_000106                       		ERR_INTERAC_BASE+0x000106			/*!< Interac error 106 : There is not enough memory in the shared exchange structure to add the TAG_EMV_CA_PUBLIC_KEY_INDEX_CARD.<br>(Interac_Txn_GetCertificate.c, __Interac_Txn_GetCertificate_FillOutputStructure) */
#define ERR_INTERAC_000107                       		ERR_INTERAC_BASE+0x000107			/*!< Interac error 107 : Missing terminal data : \ref TAG_EMV_INT_CAPK_MODULUS.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_GetCommonData) */
#define ERR_INTERAC_000108                       		ERR_INTERAC_BASE+0x000108			/*!< Interac error 108 : Missing terminal data : \ref TAG_EMV_INT_CAPK_EXPONENT.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_GetCommonData) */
#define ERR_INTERAC_000109                       		ERR_INTERAC_BASE+0x000109			/*!< Interac error 109 : Missing ICC data : \ref TAG_EMV_ISSUER_PUBLIC_KEY_CERTIFICATE.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_GetCommonData) */
#define ERR_INTERAC_00010A                       		ERR_INTERAC_BASE+0x00010A			/*!< Interac error 10A : Missing ICC data : \ref TAG_EMV_ISSUER_PK_EXPONENT.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_GetCommonData) */
#define ERR_INTERAC_00010B                       		ERR_INTERAC_BASE+0x00010B			/*!< Interac error 10B : Missing ICC data : \ref TAG_EMV_CA_PUBLIC_KEY_INDEX_CARD.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_GetCommonData) */
#define ERR_INTERAC_00010C                       		ERR_INTERAC_BASE+0x00010C			/*!< Interac error 10C : Missing ICC data : \ref TAG_EMV_APPLI_PAN.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_GetCommonData) */
#define ERR_INTERAC_00010D                       		ERR_INTERAC_BASE+0x00010D			/*!< Interac error 10D : Missing ICC data : \ref TAG_EMV_DF_NAME.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_GetCommonData) */
#define ERR_INTERAC_00010E                       		ERR_INTERAC_BASE+0x00010E			/*!< Interac error 10E : Missing ICC data : \ref TAG_EMV_TRANSACTION_DATE.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_GetCommonData) */
#define ERR_INTERAC_00010F                       		ERR_INTERAC_BASE+0x00010F			/*!< Interac error 10F : Missing mandatory data to retrieve the Issuer Public Key.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_GetCommonData) */

#define ERR_INTERAC_000112                       		ERR_INTERAC_BASE+0x000112			/*!< Interac error 112 : Missing ICC data : \ref TAG_EMV_ICC_PK_CERTIFICATE.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GetAdditionalData) */
#define ERR_INTERAC_000113                       		ERR_INTERAC_BASE+0x000113			/*!< Interac error 113 : Missing ICC data : \ref TAG_EMV_ICC_PK_EXPONENT.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GetAdditionalData) */
#define ERR_INTERAC_000114                       		ERR_INTERAC_BASE+0x000114			/*!< Interac error 114 : Missing ICC data : \ref TAG_INTERAC_INT_GENAC_RESPONSE_DATA.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GetAdditionalData) */
#define ERR_INTERAC_000115                       		ERR_INTERAC_BASE+0x000115			/*!< Interac error 115 : Missing ICC data for SDA : \ref TAG_EMV_SIGNED_DYNAMIC_APPLI_DATA.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GetAdditionalData) */
#define ERR_INTERAC_000116                       		ERR_INTERAC_BASE+0x000116			/*!< Interac error 116 : Missing ICC data for SDA : \ref TAG_EMV_CRYPTOGRAM_INFO_DATA.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GetAdditionalData) */
#define ERR_INTERAC_000117                       		ERR_INTERAC_BASE+0x000117			/*!< Interac error 117 : Missing ICC data for SDA : \ref TAG_EMV_UNPREDICTABLE_NUMBER.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GetAdditionalData) */
#define ERR_INTERAC_000118                       		ERR_INTERAC_BASE+0x000118			/*!< Interac error 118 : Missing mandatory CDA data.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GetAdditionalData) */
#define ERR_INTERAC_000119                       		ERR_INTERAC_BASE+0x000119			/*!< Interac error 119 : An error occurred when adding \ref TAG_KERNEL_IPK_RECOVERED_DATA tag in the database.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_RetrieveIssuerPublicKey) */
#define ERR_INTERAC_00011A                       		ERR_INTERAC_BASE+0x00011A			/*!< Interac error 11A : The certificate is revoked.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_RetrieveIssuerPublicKey) */
#define ERR_INTERAC_00011B                       		ERR_INTERAC_BASE+0x00011B			/*!< Interac error 11B : The certificate used is expired.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_RetrieveIssuerPublicKey) */
#define ERR_INTERAC_00011C                       		ERR_INTERAC_BASE+0x00011C			/*!< Interac error 11C : An ICC mandatory data is missing : \ref TAG_EMV_ISSUER_PUBLIC_KEY_REMAINDER.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_RetrieveIssuerPublicKey) */
#define ERR_INTERAC_00011D                       		ERR_INTERAC_BASE+0x00011D			/*!< Interac error 11D : Unable to retrieve the Issuer Public Key.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_RetrieveIssuerPublicKey) */
#define ERR_INTERAC_00011E                       		ERR_INTERAC_BASE+0x00011E			/*!< Interac error 11E : An error occurred when adding \ref TAG_KERNEL_ICC_RECOVERED_DATA tag in the database.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_RetrieveIccPublicKey) */
#define ERR_INTERAC_00011F                       		ERR_INTERAC_BASE+0x00011F			/*!< Interac error 11F : The certificate used is expired.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_RetrieveIccPublicKey) */
#define ERR_INTERAC_000120                       		ERR_INTERAC_BASE+0x000120			/*!< Interac error 120 : An ICC mandatory data is missing : \ref TAG_EMV_ISSUER_PUBLIC_KEY_REMAINDER.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_RetrieveIccPublicKey) */
#define ERR_INTERAC_000121                       		ERR_INTERAC_BASE+0x000121			/*!< Interac error 121 : Unable to retrieve the ICC Public Key.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_RetrieveIccPublicKey) */


#define ERR_INTERAC_000124                       		ERR_INTERAC_BASE+0x000124			/*!< Interac error 124 : An error occurred when adding \ref TAG_KERNEL_DDA_RECOVERED_DATA tag in the database.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GenerateAndVerifySignature) */
#define ERR_INTERAC_000125                       		ERR_INTERAC_BASE+0x000125			/*!< Interac error 125 : CDA signature verification failed.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GenerateAndVerifySignature) */
#define ERR_INTERAC_000126                       		ERR_INTERAC_BASE+0x000126			/*!< Interac error 126 : Missing ICC mandatory data : \ref TAG_EMV_APPLI_PAN.<br>(Interac_Txn_ExceptionFile.c, __Interac_Txn_ExceptionFile_FillOutputStructure) */
#define ERR_INTERAC_000127                       		ERR_INTERAC_BASE+0x000127			/*!< Interac error 127 : There is not enough memory in the shared exchange structure to add the PAN.<br>(Interac_Txn_ExceptionFile.c, __Interac_Txn_ExceptionFile_FillOutputStructure) */
#define ERR_INTERAC_000128                       		ERR_INTERAC_BASE+0x000128			/*!< Interac error 128 : There is not enough memory in the shared exchange structure to add the PAN sequence number.<br>(Interac_Txn_ExceptionFile.c, __Interac_Txn_ExceptionFile_FillOutputStructure) */
#define ERR_INTERAC_000129                       		ERR_INTERAC_BASE+0x000129			/*!< Interac error 129 : Card is in the exception file, an error occurred when setting the TVR in the database.<br>(Interac_Txn_ExceptionFile.c, Interac_Txn_ExceptionFile_Check) */
#define ERR_INTERAC_00012A                       		ERR_INTERAC_BASE+0x00012A			/*!< Interac error 12A : An error occurred when getting the \ref TAG_KERNEL_PAN_IN_BLACK_LIST tag from the database.<br>(Interac_Txn_ExceptionFile.c, Interac_Txn_ExceptionFile_Check) */
#define ERR_INTERAC_00012B                       		ERR_INTERAC_BASE+0x00012B			/*!< Interac error 12B : A database error occurred when adding the \ref TAG_INTERAC_INT_ODA_METHOD tag in the database.<br>(Interac_Txn_SelectOdaMethod.c, __Interac_Txn_SelectOdaMethod_SetOdaMethod) */
#define ERR_INTERAC_00012C                       		ERR_INTERAC_BASE+0x00012C			/*!< Interac error 12C : An error occurred when setting the TVR in the EMV DataStorage.<br>(Interac_Txn_SelectOdaMethod.c, Interac_Txn_SelectOdaMethod) */
#define ERR_INTERAC_00012D                       		ERR_INTERAC_BASE+0x00012D			/*!< Interac error 12D : An error occurred when adding the command to be sent in the database.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_BuildAndSendGpoCommand) */
#define ERR_INTERAC_00012E                       		ERR_INTERAC_BASE+0x00012E			/*!< Interac error 12E : An error occurred when adding the card response to be sent in the database.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_BuildAndSendGpoCommand) */
#define ERR_INTERAC_00012F                       		ERR_INTERAC_BASE+0x00012F			/*!< Interac error 12F : An error occurred when adding the command to be sent in the database.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_BuildAndSendGenerateAcCommand) */	
#define ERR_INTERAC_000130                      		ERR_INTERAC_BASE+0x000130			/*!< Interac error 130 : An error occurred when adding the card response to be sent in the database.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_BuildAndSendGenerateAcCommand) */
#define ERR_INTERAC_000131                       		ERR_INTERAC_BASE+0x000131			/*!< Interac error 131 : An error occurred when adding the command to be sent in the database.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_ReadApplicationData) */	
#define ERR_INTERAC_000132                       		ERR_INTERAC_BASE+0x000132			/*!< Interac error 132 : An error occurred when adding the card response to be sent in the database.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_ReadApplicationData) */
#define ERR_INTERAC_000133                       		ERR_INTERAC_BASE+0x000133			/*!< Interac error 133  : Status word for Generate AC is 9001, 6700, 6A80, 6A88 or 6985.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_CardResponseAnalysis) */
#define ERR_INTERAC_000134                       		ERR_INTERAC_BASE+0x000134			/*!< Interac error 134 : An error occurred when setting the TVR in the database.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_GetCommonData) */
#define ERR_INTERAC_000135                       		ERR_INTERAC_BASE+0x000135			/*!< Interac error 135 : An error occurred when setting the TVR in the database.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_RetrieveIssuerPublicKey) */
#define ERR_INTERAC_000136                       		ERR_INTERAC_BASE+0x000136			/*!< Interac error 136 : An error occurred when setting the TVR in the database.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_RetrieveIccPublicKey) */
#define ERR_INTERAC_000137                       		ERR_INTERAC_BASE+0x000137			/*!< Interac error 137 : Unable to add \ref TAG_INTERAC_INT_SENT_APDU tag in the database.<br>(Interac_Debug.c, Interac_Debug_StoreCommandToBeSent) */
#define ERR_INTERAC_000138                       		ERR_INTERAC_BASE+0x000138			/*!< Interac error 138 : Unable to add \ref TAG_INTERAC_INT_CARD_RESPONSE tag in the database.<br>(Interac_Debug.c, Interac_Debug_StoreCardResponse) */
#define ERR_INTERAC_000139                       		ERR_INTERAC_BASE+0x000139			/*!< Interac error 139 : Missing ICC data : \ref TAG_EMV_ISSUER_PUBLIC_KEY_CERTIFICATE.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckOdaMandatoryDataPresence) */
#define ERR_INTERAC_00013A                       		ERR_INTERAC_BASE+0x00013A			/*!< Interac error 13A : Missing ICC data : \ref TAG_EMV_ISSUER_PK_EXPONENT.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckOdaMandatoryDataPresence) */
#define ERR_INTERAC_00013B                       		ERR_INTERAC_BASE+0x00013B			/*!< Interac error 13B : Missing ICC data : \ref TAG_EMV_CA_PUBLIC_KEY_INDEX_CARD.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckOdaMandatoryDataPresence) */
#define ERR_INTERAC_00013C                       		ERR_INTERAC_BASE+0x00013C			/*!< Interac error 13C : Missing ICC data for SDA : \ref TAG_EMV_SIGNED_STATIC_APPLI_DATA.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckOdaMandatoryDataPresence) */
#define ERR_INTERAC_00013D                       		ERR_INTERAC_BASE+0x00013D			/*!< Interac error 13D : Missing ICC data : \ref TAG_EMV_ICC_PK_CERTIFICATE.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckOdaMandatoryDataPresence) */
#define ERR_INTERAC_00013E                       		ERR_INTERAC_BASE+0x00013E			/*!< Interac error 13E : Missing ICC data : \ref TAG_EMV_ICC_PK_EXPONENT.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckOdaMandatoryDataPresence) */
#define ERR_INTERAC_00013F                       		ERR_INTERAC_BASE+0x00013F			/*!< Interac error 13F : An error occurred when setting the TVR in the database.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckOdaMandatoryDataPresence) */
#define ERR_INTERAC_000140                       		ERR_INTERAC_BASE+0x000140			/*!< Interac error 140 : An error occurred when checking if CAPK Index is supported by the terminal.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckOdaMandatoryDataPresence) */
#define ERR_INTERAC_000141                       		ERR_INTERAC_BASE+0x000141			/*!< Interac error 141 : CA Index not supported by the terminal.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckCapkIndexSupported) */
#define ERR_INTERAC_000142                       		ERR_INTERAC_BASE+0x000142			/*!< Interac error 142 : An error occurred when setting the TVR in the database.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckCapkIndexSupported) */
#define ERR_INTERAC_000143                       		ERR_INTERAC_BASE+0x000143			/*!< Interac error 143 : An error occurred when getting a random number (DLL).<br>(Interac_Common.c, Interac_Common_GetAndStoreUnpredictableNumber) */
#define ERR_INTERAC_000144                       		ERR_INTERAC_BASE+0x000144			/*!< Interac error 144 : Unable to add \ref TAG_EMV_UNPREDICTABLE_NUMBER tag in the database.<br>(Interac_Common.c, Interac_Common_GetAndStoreUnpredictableNumber) */
#define ERR_INTERAC_000145                       		ERR_INTERAC_BASE+0x000145			/*!< Interac error 145 : Terminal requested TC but ICC responds with CID different from TC, ARQC or AAC.<br>(Interac_Txn_OdaRouter.c, __Interac_Txn_OdaRouter_AreCidAndRcpCoherents) */
#define ERR_INTERAC_000146                       		ERR_INTERAC_BASE+0x000146			/*!< Interac error 146 : Terminal requested ARQC but ICC responds with CID different from ARQC or AAC.<br>(Interac_Txn_OdaRouter.c, __Interac_Txn_OdaRouter_AreCidAndRcpCoherents) */
#define ERR_INTERAC_000147                       		ERR_INTERAC_BASE+0x000147			/*!< Interac error 147 : Terminal requested AAC but ICC responds with CID different from AAC.<br>(Interac_Txn_OdaRouter.c, __Interac_Txn_OdaRouter_AreCidAndRcpCoherents) */
#define ERR_INTERAC_000148                       		ERR_INTERAC_BASE+0x000148			/*!< Interac error 148 : Incorrect terminal RCP.<br>(Interac_Txn_OdaRouter.c, __Interac_Txn_OdaRouter_AreCidAndRcpCoherents) */
#define ERR_INTERAC_000149                       		ERR_INTERAC_BASE+0x000149			/*!< Interac error 149 : Missing data in the CVM List or number of bytes is even.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_CheckCvmListPresence) */
#define ERR_INTERAC_00014A                       		ERR_INTERAC_BASE+0x00014A			/*!< Interac error 14A : AFL is not correctly formatted.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_ResponseAnalysisFormat2) */
#define ERR_INTERAC_00014B                       		ERR_INTERAC_BASE+0x00014B			/*!< Interac error 14B : Card expiration date is not correctly formatted, so transaction shall be terminated.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckSomeDataFormat) */
#define ERR_INTERAC_00014C                       		ERR_INTERAC_BASE+0x00014C			/*!< Interac error 14C : Card effective date is not correctly formatted, so transaction shall be terminated.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckSomeDataFormat) */
#define ERR_INTERAC_00014D                       		ERR_INTERAC_BASE+0x00014D			/*!< Interac error 14D : An error occurred when adding \ref TAG_EMV_CA_PUBLIC_KEY_INDEX_TERM tag in the database.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CheckCapkIndexSupported) */
#define ERR_INTERAC_00014E                       		ERR_INTERAC_BASE+0x00014E			/*!< Interac error 14E : An error occurred when setting the TVR in the database.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_SetIsSfiCorrect) */
#define ERR_INTERAC_00014F                       		ERR_INTERAC_BASE+0x00014F			/*!< Interac error 14F : Card returned a tag having terminal as source, transaction shall be terminated.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_000150                       		ERR_INTERAC_BASE+0x000150			/*!< Interac error 150 : An error occurred when setting the TVR in the database.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GenerateAndVerifySignature) */
#define ERR_INTERAC_000151                       		ERR_INTERAC_BASE+0x000151			/*!< Interac error 151 : Card returned a redundant proprietary tag (tag is provided) in a SFI in [11;30], this one is ignored and transaction continue.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_000152                       		ERR_INTERAC_BASE+0x000152			/*!< Interac error 152 : Card returned a proprietary tag with a bad format in a Read Record with SFI in [11;30], this one is ignored and transaction continue.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_000153                       		ERR_INTERAC_BASE+0x000153			/*!< Interac error 153 : A database error occurred when storing proprietary data provided in Read Record with SFI in [11;30].<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_CardResponseAnalysis) */
#define ERR_INTERAC_000154                       		ERR_INTERAC_BASE+0x000154			/*!< Interac error 154 : Card returned a redundant tag (\ref TAG_EMV_AIP or \ref TAG_EMV_AFL).<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_ResponseAnalysisFormat2) */
#define ERR_INTERAC_000155                       		ERR_INTERAC_BASE+0x000155			/*!< Interac error 155 : An error occurred when setting the TVR in the database.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GenerateAndVerifySignature) */
#define ERR_INTERAC_000156                       		ERR_INTERAC_BASE+0x000156			/*!< Interac error 156 : A database error occured when adding FCI template in the database (DsStatus is provided).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_ExtractAndParseFciTemplate) */
#define ERR_INTERAC_000157                       		ERR_INTERAC_BASE+0x000157			/*!< Interac error 157 : Card returned \ref TAG_EMV_ISSUER_APPLI_DATA tag with a bad format (Generate AC format 1).<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_ResponseAnalysisFormat1) */
#define ERR_INTERAC_000158								ERR_INTERAC_BASE+0x000158			/*!< Interac error 158 : Missing Terminal mandatory data : \ref TAG_EP_FINAL_SELECT_COMMAND_SENT.<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_CheckAdfCoherence) */
#define ERR_INTERAC_000159								ERR_INTERAC_BASE+0x000159			/*!< Interac error 159 : The sent ADF and the DF Name have the same length but are different.<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_CheckAdfCoherence) */
#define ERR_INTERAC_00015A								ERR_INTERAC_BASE+0x00015A			/*!< Interac error 15A : The sent ADF and the DF Name returned by the card has not the same length (lengths are provided).<br>(Interac_Txn_FinalSelect.c, __Interac_Txn_FinalSelect_CheckAdfCoherence) */
#define ERR_INTERAC_00015B								ERR_INTERAC_BASE+0x00015B			/*!< Interac error 15B : An error occured when adding TAG_EMV_APPLICATION_CRYPTOGRAM tag in the database.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GenerateAndVerifySignature) */
#define ERR_INTERAC_00015C								ERR_INTERAC_BASE+0x00015C			/*!< Interac error 15C : An error occured when adding TAG_EMV_ICC_DYNAMIC_NUMBER tag in the database.<br>(Interac_Txn_Oda.c, __Interac_Txn_Oda_CDA_GenerateAndVerifySignature) */

#define ERR_INTERAC_00015E								ERR_INTERAC_BASE+0x00015E			/*!< Interac error 15E : An error occured when adding last command and SW in the database.<br>(Interac_Common.c, Interac_Common_StoreLastCommandAndSw) */
#define ERR_INTERAC_00015F								ERR_INTERAC_BASE+0x00015F			/*!< Interac error 15F : An error occured when adding the last command/answer for GPO in the database.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_BuildAndSendGpoCommand) */
#define ERR_INTERAC_000160								ERR_INTERAC_BASE+0x000160			/*!< Interac error 160 : An error occured when adding the last command/answer for Generate AC in the database.<br>(Interac_Txn_GenAc.c, __Interac_Txn_GenAc_BuildAndSendGenerateAcCommand) */
#define ERR_INTERAC_000161								ERR_INTERAC_BASE+0x000161			/*!< Interac error 161 : An error occured when adding the last command/answer for RAD in the database.<br>(Interac_Txn_Rad.c, __Interac_Txn_Rad_ReadApplicationData) */

#define ERR_INTERAC_000162								ERR_INTERAC_BASE+0x000162			/*!< Interac error 162 : A mandatory data is missing : TAG_INTERAC_TERMINAL_TRANSACTION_INFORMATION (tag 9F59).<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_ResponseAnalysisFormat2) */
#define ERR_INTERAC_000163								ERR_INTERAC_BASE+0x000163			/*!< Interac error 163 : Card CTI requires revert but terminal TTI does not support Interac contactl so decline.<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_ResponseAnalysisFormat2) */
#define ERR_INTERAC_000164                       		ERR_INTERAC_BASE+0x000164			/*!< Interac error 164 : Missing mandatory data within the card (\ref TAG_INTERAC_CARD_TRANSACTION_INFORMATION).<br>(Interac_Txn_Iap.c, __Interac_Txn_Iap_ResponseAnalysisFormat2) */

#define ERR_INTERAC_000165                       		ERR_INTERAC_BASE+0x000165			/*!< Interac error 165 : Missing mandatory terminal data (\ref TAG_INTERAC_TERMINAL_OPTION_STATUS).<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_CheckTOS) */
#define ERR_INTERAC_000166                       		ERR_INTERAC_BASE+0x000166			/*!< Interac error 166 : Missing mandatory terminal data (\ref TAG_EMV_TERMINAL_COUNTRY_CODE).<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_CheckTOS) */
#define ERR_INTERAC_000167                       		ERR_INTERAC_BASE+0x000167			/*!< Interac error 167 : Missing mandatory terminal data (\ref TAG_EMV_TRANSACTION_CURRENCY_CODE).<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_CheckTOS) */
#define ERR_INTERAC_000168                       		ERR_INTERAC_BASE+0x000168			/*!< Interac error 168 : Issuer and Terminal country codes differ and TOS B1b7 is set to '1' so revert.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_CheckTOS) */
#define ERR_INTERAC_000169                       		ERR_INTERAC_BASE+0x000169			/*!< Interac error 169 : Issuer currency and Transaction currency codes differ and TOS B1b8 is set to '1' so revert.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_CheckTOS) */

#define ERR_INTERAC_00016A                       		ERR_INTERAC_BASE+0x00016A			/*!< Interac error 16A : A mandatory tag in the terminal data is missing (\ref TAG_EMV_AMOUNT_AUTH_BIN).<br>(Interac_Txn_Completion.c, __Interac_Txn_Completion_SetReceiptRequired) */
#define ERR_INTERAC_00016B                       		ERR_INTERAC_BASE+0x00016B			/*!< Interac error 16B : A mandatory tag in the terminal data is missing (\ref TAG_INTERAC_RECEIPT_LIMIT).<br>(Interac_Txn_Completion.c, __Interac_Txn_Completion_SetReceiptRequired) */
#define ERR_INTERAC_00016C                       		ERR_INTERAC_BASE+0x00016C			/*!< Interac error 16C : Failed to store the receipt status in .<br>(Interac_Txn_Completion.c, __Interac_Txn_Completion_SetReceiptRequired) */

#define ERR_INTERAC_00016D								ERR_INTERAC_BASE+0x00016D			/*!< Interac error 16D : A mandatory data is missing : TAG_INTERAC_TERMINAL_TRANSACTION_INFORMATION (tag 9F59).<br>(Interac_Txn_Completion.c, __Interac_Txn_Completion_SetTransactionOutcome) */
#define ERR_INTERAC_00016E                       		ERR_INTERAC_BASE+0x00016E			/*!< Interac error 16E : CVM List \ref TAG_EMV_CVM_LIST_CARD tag has not been returned by the card, either not prsent or empty.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_CheckCvmListPresence) */
#define ERR_INTERAC_00016F                       		ERR_INTERAC_BASE+0x00016F			/*!< Interac error 16F : CVM List \ref TAG_EMV_CVM_LIST_CARD tag returned but there are no CVMs.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_CheckCvmListPresence) */

#define ERR_INTERAC_000170                       		ERR_INTERAC_BASE+0x000170			/*!< Interac error 170 : Missing mandatory data within the card (\ref TAG_EMV_ISSUER_COUNTRY_CODE).<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_CheckTOS) */
#define ERR_INTERAC_000171                       		ERR_INTERAC_BASE+0x000171			/*!< Interac error 171 : Missing mandatory data within the card (\ref TAG_EMV_APPLI_CURRENCY_CODE).<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_CheckTOS) */
#define ERR_INTERAC_000172                       		ERR_INTERAC_BASE+0x000172			/*!< Interac error 172 : Missing mandatory data within the card (\ref TAG_INTERAC_CARD_TRANSACTION_INFORMATION).<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_CheckTOS) */
#define ERR_INTERAC_000173                       		ERR_INTERAC_BASE+0x000173			/*!< Interac error 173 : Missing mandatory terminal data (\ref TAG_INTERAC_TERMINAL_TRANSACTION_INFORMATION).<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_CheckTOS) */
#define ERR_INTERAC_000174                       		ERR_INTERAC_BASE+0x000174			/*!< Interac error 174 : Issuer and Terminal country codes match and TOS B1b6 is set to '1' so revert.<br>(Interac_Txn_Pr.c, __Interac_Txn_Pr_CheckTOS) */
#define ERR_INTERAC_000175                       		ERR_INTERAC_BASE+0x000175			/*!< Interac error 175 : Missing mandatory terminal data (\ref TAG_EMV_TERMINAL_CAPABILITIES).<br>(Interac_Txn_SelectOdaMethod.c, __Interac_Txn_SelectOdaMethod_IsCdaMethod) */
#define ERR_INTERAC_000176                       		ERR_INTERAC_BASE+0x000176			/*!< Interac error 176 : Missing mandatory card data (\ref TAG_EMV_AIP).<br>(Interac_Txn_SelectOdaMethod.c, __Interac_Txn_SelectOdaMethod_IsCdaMethod) */
#define ERR_INTERAC_000177                       		ERR_INTERAC_BASE+0x000177			/*!< Interac error 177 : Missing mandatory terminal data (\ref TAG_INTERAC_TERMINAL_TRANSACTION_INFORMATION).<br>(Interac_Txn_SelectOdaMethod.c, __Interac_Txn_SelectOdaMethod_SetTTIValue) */
#define ERR_INTERAC_000178                       		ERR_INTERAC_BASE+0x000178			/*!< Interac error 178 : Error occurred adding terminal data (\ref TAG_INTERAC_TERMINAL_TRANSACTION_INFORMATION) to the database.<br>(Interac_Txn_SelectOdaMethod.c, __Interac_Txn_SelectOdaMethod_SetTTIValue) */
#define ERR_INTERAC_000179                       		ERR_INTERAC_BASE+0x000179			/*!< Interac error 179 : Error occurred adding terminal data (\ref TAG_INTERAC_TERMINAL_TRANSACTION_INFORMATION) to the database.<br>(Interac_Txn_Trm.c, Interac_Txn_Trm) */
#define ERR_INTERAC_00017A                       		ERR_INTERAC_BASE+0x00017A			/*!< Interac error 17A : Missing mandatory card data (\ref TAG_EMV_AIP).<br>(Interac_Txn_Trm.c, __Interac_Txn_Trm_ToBePerformed) */
#define ERR_INTERAC_00017B                       		ERR_INTERAC_BASE+0x00017B			/*!< Interac error 17B : An error occured when setting the Transaction CVM in the database.<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
#define ERR_INTERAC_00017C                       		ERR_INTERAC_BASE+0x00017C			/*!< Interac error 17C : An error occured when setting the TVR ('Cardholder verification was not successful').<br>(Interac_Txn_CvmSelection.c, __Interac_Txn_CvmSelection_ProcessCvmSelection) */
//! @}


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global Data ///////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup InteracInterfaceFunctions
//! @{

//! \brief This function performs the Interac transaction with the presented card.
//!	All the necessary data to perform the transaction shall be provided.
//! This function shall be called after the application selection (PPSE performed and Final SELECT response and status word provided).
//!	It begins by analysing the provided Final SELECT response and Status cord and perform the transaction until completion.
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel. 
//!	This shared buffer shall be initialised using the \ref GTL_SharedExchange_InitShared() function 
//! (please refer to GTL documentation for more information).
//!	- Input data list (bold ones are mandatory or highly recommended)
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
//!		- <dfn>\ref TAG_EMV_MERCHANT_CATEGORY_CODE</dfn>	: Merchant category code.
//!		- <dfn>\ref TAG_EMV_MERCHANT_IDENTIFIER</dfn> : Merchant identifier.
//!		- \ref TAG_EMV_TERMINAL_IDENTIFICATION : Terminal identification.
//!		- \ref TAG_EMV_AID_TERMINAL : AID as configured in the terminal.
//!		- \ref TAG_EMV_INT_TRANSACTION_TYPE : Internal transaction type (managed by the application, and used by the kernel).
//!		- <dfn>\ref TAG_EP_KERNEL_TO_USE</dfn> : Kernel to be used (for Interac, it shall be set to \a DEFAULT_EP_KERNEL_INTERAC).
//!		- <dfn>\ref TAG_EP_AID_OPTIONS</dfn> : AID application selection options (please refer to \a EntryPoint_Tags.h for more information).
//!		- \ref TAG_EP_CLESS_TRANSACTION_LIMIT : Contactless Transaction Limit for the chosen AID.
//!		- \ref TAG_EP_CLESS_CVM_REQUIRED_LIMIT : Contactless CVM required limit for the chosen AID.
//!		- \ref TAG_EP_CLESS_FLOOR_LIMIT : Contactless Floor limit for the chosen AID.
//!		- \ref TAG_EP_AID_ADDITIONAL_RESULTS : Application selection additional results for the chosen AID (indicates the Entry Point results, such as floor limits exceeded, etc).
//!			Please refer to \a EntryPoint_Tags.h documentation for more information about this tag.
//!		- \ref TAG_EP_FINAL_SELECT_COMMAND_SENT : Final SELECT command (for internal Interac mandatory checkings).
//!		- \ref TAG_EP_FINAL_SELECT_RESPONSE : Final SELECT response provided by the application selection. It will be analysed by the Interac kernel itself.
//!		- \ref TAG_EP_FINAL_SELECT_STATUS_WORD : Final SELECT response status word provided by the application selection. It will be analysed by the Interac kernel itself.
//!		- \ref TAG_INTERAC_INT_TERMINAL_AVN_LIST : Terminal Application version number supported for this AID.
//!		- \ref TAG_INTERAC_TERMINAL_CAPABILITIES_CVM_REQ : Terminal capabilities to be used if CVM is required (amount greater than \a TAG_EP_CLESS_CVM_REQUIRED_LIMIT). Terminal capabilities is automatically set by the kernel depending on the application selection results.
//!		- \ref TAG_INTERAC_TERMINAL_CAPABILITIES_NO_CVM_REQ : Terminal capabilities to be used if CVM is not required (amount lower than \a TAG_EP_CLESS_CVM_REQUIRED_LIMIT). Terminal capabilities is automatically set by the kernel depending on the application selection results.
//!		- \ref TAG_EMV_INT_TAC_DEFAULT : Terminal Action Code Default.
//!		- \ref TAG_EMV_INT_TAC_DENIAL : Terminal Action Code Denial.
//!		- \ref TAG_EMV_INT_TAC_ONLINE : Terminal Action Code Online.
//!		- \ref TAG_INTERAC_INT_SUPPORTED_CAPK_INDEX_LIST : List of CA keys supported for the chosen AID.
//!		- <dfn>\ref TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES</dfn> : Supported language for the chosen AID.
//!		- <dfn>\ref TAG_KERNEL_PAYMENT_FLOW_STOP</dfn> : Data field indicating steps where the transaction flow has to be stopped. It is strongly recommended, for transaction performances purposes, to not interrupt the transaction flow using this way (recommended value is all set to 0).
//!		- <dfn>\ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM</dfn> : Data field indicating steps where customisation is necessary.
//!		- <dfn>\ref TAG_KERNEL_PROPRIETARY_TAGS</dfn> : Description of the proprietary tags that shall be considered as known by the kernel.
//!	- Output data returned by the Interac kernel
//!		- Whatever the transaction result (except if transaction is cancelled or interrupted) :
//!			- \ref TAG_INTERAC_TRANSACTION_OUTCOME : Indicates the transaction outcome (offline approved, online request, offline declined, use another interface or terminated).
//!		- Additional data for "Offline Approve" or "Online" :
//!			- \ref TAG_INTERAC_TRANSACTION_CVM : Transaction CVM (No CVM, Signature or Online PIN).
//!			- \ref TAG_EMV_TRACK_2_EQU_DATA : Track 2 Equivalent Data (if present).
//!			- \ref TAG_EMV_DF_NAME : DF Name.
//!			- \ref TAG_EMV_APPLICATION_LABEL : Application Label (if present).
//!			- \ref TAG_EMV_APPLI_PREFERED_NAME : Application Preferred Name (if present).
//!			- \ref TAG_EMV_ISSUER_CODE_TABLE_INDEX : Issuer Code Table Index (if present).
//!			- \ref TAG_EMV_APPLICATION_CRYPTOGRAM : Application Cryptogram.
//!			- \ref TAG_EMV_CRYPTOGRAM_INFO_DATA : Cryptogram Information Data.
//!			- \ref TAG_EMV_ISSUER_APPLI_DATA : Issuer Application Data (if present).
//!			- \ref TAG_EMV_ATC : Application Transaction Counter.
//!			- \ref TAG_EMV_TVR : Terminal Verification Results.
//!			- \ref TAG_EMV_UNPREDICTABLE_NUMBER : Transaction Unpredictable Number.
//!			- \ref TAG_EMV_TRANSACTION_CURRENCY_CODE : Transaction Currency Code.
//!			- \ref TAG_EMV_TRANSACTION_TYPE : Transaction Type.
//!			- \ref TAG_EMV_TRANSACTION_DATE : Transaction Date.
//!			- \ref TAG_EMV_AMOUNT_AUTH_NUM : Amount Authorized, numeric format.
//!			- \ref TAG_EMV_TERMINAL_COUNTRY_CODE : Terminal Country Code.
//!			- \ref TAG_EMV_CVM_RESULTS : Cardholder Verification Results.
//!			- \ref TAG_EMV_AIP : Application Interchange Profile.
//!		- Additional data for "Online"  :
//!			- \ref TAG_EMV_TRACK_2_EQU_DATA : Track 2 Data
//!			- \ref TAG_EMV_DF_NAME : DF Name.
//!			- \ref TAG_EMV_APPLICATION_LABEL : Application Label (if present).
//!			- \ref TAG_EMV_APPLI_PREFERED_NAME : Application Preferred Name (if present).
//!			- \ref TAG_EMV_ISSUER_CODE_TABLE_INDEX : Issuer Code Table Index (if present).
//!		- If transaction is cancelled or interrupted, the \ref TAG_KERNEL_LAST_EXECUTED_STEP_INTERRUPTION is returned to indicate the last executed step when the interruption / cancellation occurred.
//!		Please refer to \ref InteracTransactionFlowSteps for more information about the existing transaction steps.
//! \return Kernel processing status code.
//! - \ref KERNEL_STATUS_OFFLINE_APPROVED : Transaction succeeded and is offline approved.
//!	- \ref KERNEL_STATUS_OFFLINE_DECLINED : Transaction is offline declined.
//!	- \ref KERNEL_STATUS_ONLINE_AUTHORISATION : Transaction succeeded and has to be sent online for authorisation.
//!	- \ref KERNEL_STATUS_CANCELLED : if transaction has been cancelled by the custom application (using \a Interac_Cancel() function).
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
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the Interac kernel is not loaded in the terminal or if the requested service does not exists.
//! \note If the transaction is cancelled or suspended by the application, the returned status code is (\a status \a code | \ref KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK).
//!	If transaction is cancelled or interrupted by the user, the kernel database is not altered to allow continuing the transaction 
//!	anyway if requested (using \ref Interac_ResumeTransaction() function).

int Interac_DoTransaction (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to resume the transaction when an interruption occurred (requested interruption or cancellation).
//! The transaction will continue where it has been interrupted.
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//!	- Input data can be provided. It will replace each existing data within the kernel database.
//!	- Output data are the same as \ref Interac_DoTransaction() function (as it continues the transaction).
//! \return Kernel processing status code (identical than the \ref Interac_DoTransaction() function).
//! The returned value depends on the step where the transaction is resumed.
//!	For example, \ref KERNEL_STATUS_COND_OF_USE_NOT_SATISFIED cannot be returned if you resume the transaction after the \ref STEP_INTERAC_INITIATE_APPLI_PROCESSING step.

int Interac_ResumeTransaction (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to retrieve the entire kernel database.
//! All the tags present in the database are retrieved.
//! \param[out] pDataStruct Shared buffer filled with all the kernel data. 
//! Make sure the buffer size you provide is bigger enough to store all the tags.
//! Note the shared buffer is automatically cleared by the Interac kernel.
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if all the data are provided and no error occurred.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the Interac kernel is not loaded in the terminal or if the requested service does not exists.
//! \note It is strongly recommended to not call this function during the transaction flow, as it should impact the transaction performance.

int Interac_GetAllData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to request kernel some tags (if present in its database).
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//! Make sure the buffer size you provide is bigger enough to store all the tags.
//! Note the shared buffer is automatically cleared by the Interac kernel.
//!	- Input data : Tag to be requested to the kernel. It is a concatenation of tags and length set to 0.
//! - Output data : list of retrieved data (coded in BER-TLV) that have been requested and that are present in the kernel database.
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if all the data are provided and no error occurred.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the Interac kernel is not loaded in the terminal or if the requested service does not exists.
//! \note It is strongly recommended to not call this function during the transaction flow, as it should impact the transaction performance.
//! \remarks Example to get the transaction date and the transaction time from the Interac kernel :
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
//!	// Call the Interac kernel to retrieve the requested tags.
//!	nResult = Interac_GetData (pSharedDataStruct);
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

int Interac_GetData (T_SHARED_DATA_STRUCT * pDataStruct);



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
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the Interac kernel is not loaded in the terminal or if the requested service does not exists.
//! \note It is strongly recommended to not call this function during the transaction flow, as it should impact the transaction performance.
//! \remarks Example to load the transaction date and the transaction time from the Interac kernel :
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
//!	// Call the Interac kernel to load the tags.
//!	nResult = Interac_LoadData (pSharedDataStruct);
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

int Interac_LoadData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function can be used to cancel the Interac transaction.
//! We could imagine using it to cancel the transaction when the red key is pressed during the Interac transaction for example.
//! \return Always \ref KERNEL_STATUS_OK.
//! \note This is the responsibility of the custom application to correctly use this function. 
//! The Interac transaction can be cancelled at any step.
//! If called, the kernel will return \ref KERNEL_STATUS_CANCELLED on the following functions :
//!	- \ref Interac_DoTransaction().
//!	- \ref Interac_ResumeTransaction().

int Interac_Cancel (void);



//! \brief This function allows to manage the Interac kernel debug features.
//! This allows activating / deactivating the following debug features :
//!	- Trace : it provides debug information in the \a Trace.exe tool provided in the TDS.
//!	- Time measurements : it manages in the database the \ref TAG_KERNEL_DEBUG_TIME tag that can be retrieved using \ref Interac_GetData() function).
//!	Note if Time debug feature is not activated, \ref TAG_KERNEL_DEBUG_TIME tag is not stored in the kernel database.
//!	- APDU storage : it stores all the APDU sent to the ICC and responses sent by the ICC in the database, using specific tags. 
//!	This concerns commands from GPO command to the Generate AC command .
//!	Each command is stored in a \ref TAG_INTERAC_INT_SENT_APDU tag, each received ICC response is stored in a \ref TAG_INTERAC_INT_CARD_RESPONSE tag.
//! \param[in] pDataStruct Shared buffer filled with the \ref TAG_KERNEL_DEBUG_ACTIVATION tag indicating the debug mode.
//!	If the tag is not present or set to 0, then all the debug features are deactivated.
//! \return
//!	- \ref KERNEL_STATUS_OK if debug mode correctly activated / deactivated.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the Interac kernel is not loaded in the terminal or if the requested service does not exists.
//!	\note If debug features shall be activated, it is strongly recommended to call this function before the transaction has started.
//!	It allows to not waste time during the transaction (performances purposes).
//! \remarks Example to set the debug mode :
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
//!	// Call the Interac kernel to set the debug mode.
//!	nResult = Interac_DebugManagement (pSharedDataStruct);
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
//!	// Call the Interac kernel to load the tags.
//!	nResult = Interac_DebugManagement (pSharedDataStruct);
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

int Interac_DebugManagement (T_SHARED_DATA_STRUCT * pDataStruct);



//!	\brief This function clears and initialise the Interac kernel.
//! It fully clear the database and restores the global data (reset cancel, deactivate debug features, etc). 
//! <b>It is mandatory to call this function after each Interac transaction has been completed (and the terminal 
//! is returning on idle state).</b>
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if Interac kernel correctly cleared and initialised.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : A library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if the Interac kernel is not loaded in the terminal or if the requested service does not exists.

int Interac_Clear (void);



//! \brief This function gets the kernel information.
//! \param[out] pDataStruct Shared buffer filled with the following tags (note this buffer is automatically cleared by the function) :
//!	- \ref TAG_KERNEL_APPLICATION_NAME that indicates the application name (ASCII format).
//!	- \ref TAG_KERNEL_APPLICATION_IDENT that indicates the kernel identifier (in ASCII format, \a 3349 followed by the Interac kernel version on 4 digits).
//!	- \ref TAG_KERNEL_APPLICATION_CRC that indicates the Interac kernel CRC.
//! \return
//!	- \ref KERNEL_STATUS_OK if kernel information correctly retrieved.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_INTERNAL_ERROR if an internal error occurred.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR if a library interface error occurred.
//!	- \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE if the Interac kernel is not loaded in the terminal or if the requested service does not exists.

int Interac_GetInfos (T_SHARED_DATA_STRUCT * pDataStruct);



//! @}



//! \addtogroup InteracTransactionFlow
//! @{
//! Here is described the transaction flow as it is implemented in the Interac kernel. Each transaction step in the following graph corresponds to a transaction step described in \ref InteracTransactionFlowSteps.
//! 
//! 
//! \dot
//! digraph G {
//!		bgcolor="transparent";
//!		ranksep="0.2 equally"
//! 
//!		graph [fontname="FreeSans",fontsize=10];
//!		node [shape="box",fontname="FreeSans",fontsize=10,height=0.4,width=2];
//!		edge [fontname="FreeSans",fontsize=10,labelfontname="FreeSans",labelfontsize=10];
//! 
//!		nodeStart [label="Interac_DoTransaction",shape="ellipse",style=filled];
//!		node_STEP_INTERAC_INITIAL [label="Initial",size="50,2",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_INITIAL"];
//!		node_STEP_INTERAC_FINAL_SELECTION [label="Final Application Selection",size="5,2",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_FINAL_SELECTION"];
//!		node_STEP_INTERAC_INITIATE_APPLI_PROCESSING	[label="Initiate Application Processing",size="5,2",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_INITIATE_APPLI_PROCESSING"];
//!		node_STEP_INTERAC_ODA_METHOD_SELECTION [label="ODA Method selection",size="5,2",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_ODA_METHOD_SELECTION"];
//!		node_STEP_INTERAC_READ_APPLI_DATA [label="Read Application Data",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_READ_APPLI_DATA"];
//!		node_STEP_INTERAC_PROCESSING_RESTRICTIONS [label="Processing Restrictions",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_PROCESSING_RESTRICTIONS"];
//!		node_STEP_INTERAC_TERMINAL_RISK_MANAGEMENT [label="Terminal Risk Management",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_TERMINAL_RISK_MANAGEMENT"];
//!		node_STEP_INTERAC_CVM_SELECTION [label="CVM Selection",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_CVM_SELECTION"];
//!		node_STEP_INTERAC_TERMINAL_ACTION_ANALYSIS [label="Terminal Action Analysis",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_TERMINAL_ACTION_ANALYSIS"];
//!		node_STEP_INTERAC_GENERATE_AC [label="Generate AC",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_GENERATE_AC"];
//!		node_STEP_INTERAC_REMOVE_CARD [label="Remove Card",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_REMOVE_CARD"];
//!		node_STEP_INTERAC_GET_CERTIFICATE [label="Get Certificate",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_GET_CERTIFICATE"];
//!		node_STEP_INTERAC_ODA_ROUTER [label="ODA Router",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_ODA_ROUTER"];
//!		node_STEP_INTERAC_CDA_PROCESSING [label="CDA Processing",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_CDA_PROCESSING"];
//!		node_STEP_INTERAC_EXCEPTION_FILE_GET_DATA [label="Get Exception File Data",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_EXCEPTION_FILE_GET_DATA"];
//!		node_STEP_INTERAC_EXCEPTION_FILE_CHECKING [label="Exception File Checking",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_EXCEPTION_FILE_CHECKING"];

//!		node_STEP_INTERAC_COMPLETION [label="Completion",style=filled,fillcolor=plum,URL="\ref STEP_INTERAC_COMPLETION"];
//!		nodeStop [label="Return transaction result",shape="ellipse",style=filled];
//! 
//!		nodeStart -> node_STEP_INTERAC_INITIAL [weight=100];
//!		node_STEP_INTERAC_INITIAL -> node_STEP_INTERAC_FINAL_SELECTION [weight=100];
//!		node_STEP_INTERAC_FINAL_SELECTION -> node_STEP_INTERAC_INITIATE_APPLI_PROCESSING [weight=100];
//!		node_STEP_INTERAC_INITIATE_APPLI_PROCESSING -> node_STEP_INTERAC_ODA_METHOD_SELECTION [weight=100];
//!		node_STEP_INTERAC_ODA_METHOD_SELECTION -> node_STEP_INTERAC_READ_APPLI_DATA [weight=100];
//!		node_STEP_INTERAC_READ_APPLI_DATA -> node_STEP_INTERAC_PROCESSING_RESTRICTIONS [weight=100];
//!		node_STEP_INTERAC_PROCESSING_RESTRICTIONS -> node_STEP_INTERAC_TERMINAL_RISK_MANAGEMENT [weight=100];
//!		node_STEP_INTERAC_TERMINAL_RISK_MANAGEMENT -> node_STEP_INTERAC_CVM_SELECTION [weight=100];
//!		node_STEP_INTERAC_CVM_SELECTION -> node_STEP_INTERAC_EXCEPTION_FILE_GET_DATA [weight=100];
//!		node_STEP_INTERAC_EXCEPTION_FILE_GET_DATA -> node_STEP_INTERAC_EXCEPTION_FILE_CHECKING [weight=100];
//!		node_STEP_INTERAC_EXCEPTION_FILE_CHECKING -> node_STEP_INTERAC_TERMINAL_ACTION_ANALYSIS [weight=100];
//!		node_STEP_INTERAC_TERMINAL_ACTION_ANALYSIS -> node_STEP_INTERAC_GENERATE_AC [weight=100];
//!		node_STEP_INTERAC_GENERATE_AC -> node_STEP_INTERAC_REMOVE_CARD [weight=100];
//!		node_STEP_INTERAC_REMOVE_CARD -> node_STEP_INTERAC_ODA_ROUTER [weight=100];
//!		node_STEP_INTERAC_ODA_ROUTER -> node_STEP_INTERAC_GET_CERTIFICATE [label="CDA",weight=100];
//!		node_STEP_INTERAC_GET_CERTIFICATE -> node_STEP_INTERAC_CDA_PROCESSING [label="CDA",weight=100];
//!		node_STEP_INTERAC_CDA_PROCESSING -> node_STEP_INTERAC_COMPLETION [weight=100];
//!		node_STEP_INTERAC_COMPLETION -> nodeStop [weight=100];
//!	}
//! \enddot
//! @}



//! \addtogroup InteracOverview
//! @{
//! <h2>Presentation</h2><br>
//! The Interac kernel allows you to easily perform transactions using the Interac contactless technology. It is fully compliant 
//! with the <i>Interac 1.4 Terminal Specification (December 2011)</i>.<br>
//! The kernel supports the following features :
//!	- Full supports of Interac contactless cards.
//!	- Following CVM are supported : No CVM (a future configuration will support Signature and Online PIN)
//!	- Language selection management (multi language supported).
//!	- Offline Data Authentication supported methods : CDA.
//!	- Exception file and CA Revocation management.
//!	- Offline and online capabilities (online only will be certified initially).
//! 
//! <table cellspacing="5" bgcolor="#FFCCCC" bordercolordark="green" bordercolorlight="yellow">
//! <tr><td>
//! <h2>Performances requirements</h2><br>
//! Interac requires the terminal processing time during a transaction to not exceed :
//!	- 100 ms for a Interac transaction.
//!
//! To achieve these transaction times the terminal processing time must be kept to a minimum. It is essential that the payment 
//! application performs as few processes as possible during the contactless session (i.e. when the interaction between the ICC 
//! and the terminal is in progress).<br>
//! Please note the following :
//!	- Ensure that all data is passed to the Interac kernel before the card is presented.
//!	- Ensure any application customisation is kept to a minimum during the transaction.
//! </td></tr>
//! </table>
//! 
//! <h2>Additional information</h2><br>
//! The Interac kernel performs the transaction but it does not manage :
//!	- The graphical user interface : This is the role of your application to perform the GUI. It will allow a better customisation.
//!	- The Interac parameters : all the parameters (supported AID, supported CA Keys, etc) are exclusively managed by the custom application itself.
//!	When a transaction is to be performed, this is the role of your application to provide the correct data to the kernel to perform the transaction.
//!	There is no persistent data within the Interac kernel itself. After each transaction, the Interac kernel shall be completely cleared.
//!	- The exception file itself : in fact, the exception file checking is performed by the custom application (it allows you to have your own exception file format).
//!	If the card PAN is found within the exception file, the custom application indicates it to the Interac kernel (using customisation).
//!	The kernel will continue transaction accordingly.
//! 
//!	<br><br>
//! <table cellspacing="5" bgcolor="#FFCCCC" bordercolordark="green" bordercolorlight="yellow">
//! <tr><td>
//! It is <b>mandatory</b> to call the \ref Interac_Clear() function after each transaction has been completed. Else, next transaction will not work correctly.
//! </td></tr>
//! </table>
//! 
//! @}



//! \addtogroup InteracCustomisationProcess
//! @{
//! \details 
//! It is possible for an application to be called back during the transaction process to make some customisation and interact with the transaction flow.
//! For example, it would be necessary during the Interac transaction to indicate card has been correctly read (GUI), or to check if the card PAN is present or not
//! in the exception file, etc. The Interac customisation will allow you to perform any processing you need that is not specified by the Interac specification.
//! <br><br>
//! <table cellspacing="5" bgcolor="#FFCCCC" bordercolordark="green" bordercolorlight="yellow">
//! <tr><td>
//! <b>Warning</b> : The terminal processing time during the transaction (i.e. until the card and the reader interact together) shall not exceed 100ms. That is why it 
//! is strongly recommended to avoid at the maximum the number of customisation calls during this period.
//! </td></tr>
//! </table>
//! 
//! <h2>How to be called to perform customisation on a transaction step</h2><br>
//! To call back an application for customisation, the Interac kernel shall have the following information :
//!	- The application identifier to call.
//!	- The application service to use.
//!	- A bit field indicating which step the application wishes to customise.
//!
//! All of this information is provided to the Interac kernel using the \ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM tag. 
//! This tag contains a \ref T_KERNEL_TRANSACTION_FLOW_CUSTOM structure.
//! The Interac kernel will call the application for customisation after the step to customise has been executed.
//!
//! Here is an example to correctly format the \ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM tag for customisation :
//! \code
//! #define SERVICE_CUSTOM_KERNEL		0x0999      // Indicates the service to call for customisation
//!                                                 // This service shall be declared by the application to be called for customisation.
//! 
//! T_KERNEL_TRANSACTION_FLOW_CUSTOM sTransactionFlowCustom; // Structure containing the customisation information
//! object_info_t ObjectInfo; // To get my application identifier
//! int cr;
//! 
//! // Get my application identifier
//! ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &ObjectInfo);
//! 
//! // Fill the structure with my application type and my service id to call for customisation
//! sTransactionFlowCustom.usApplicationType = ObjectInfo.application_type;
//! sTransactionFlowCustom.usServiceId = SERVICE_CUSTOM_KERNEL;
//! 
//! // Indicates the transaction steps to be customised
//! ADD_STEP_CUSTOM(STEP_INTERAC_REMOVE_CARD, sTransactionFlowCustom.pucStepCustom); // To do GUI when card has been read
//! ADD_STEP_CUSTOM(STEP_INTERAC_GET_CERTIFICATE, sTransactionFlowCustom.pucStepCustom); // To provide the CA key data for ODA
//! 
//! // For optimisation, request blacklist checking only if a black list has been loaded
//! if (ClessSample_IsBlackListPresent())	
//! 	ADD_STEP_CUSTOM(STEP_INTERAC_EXCEPTION_FILE_GET_DATA, sTransactionFlowCustom.pucStepCustom); // To check if PAN is in the blacklist
//! 
//! // Add the structure into the shared buffer to be sent to the Interac kernel to perform the transaction
//! cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
//! if (cr != STATUS_SHARED_EXCHANGE_OK)
//! {
//! 	// An error occurred when adding the tag in the shared buffer
//! 	// ...
//! }
//! 
//! // Other processing to prepare data for Interac transaction
//! // ...
//! 
//! // Call the Interac kernel to perform the transaction (Interac_DoTransaction() function) with the shared buffer containing all the necessary data 
//! // To perform the transaction, including TAG_KERNEL_PAYMENT_FLOW_CUSTOM tag.
//! // ...
//! \endcode
//! 
//! \note As described in the example before, it is strongly recommended to customise the following Interac transaction steps :
//!	- \ref STEP_INTERAC_REMOVE_CARD to indicate the card has been read and can be removed for a Interac transaction.
//! - \ref STEP_INTERAC_GET_CERTIFICATE is mandatory for a Interac transaction as it allows the custom application to provide to 
//!	the Interac kernel all the certificate data to perform Offline Data Authentication.
//! 
//! 
//! <b>How to perform the customisation ?</b><br>
//! When the \ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM tag is provided (with all the correct information and if the application type and service identifier are correct),
//! the Interac kernel will call you back for customisation.
//! 
//! \note For every customised step :
//!	- It is mandatory to clear data provided by the kernel from the shared buffer (after having read the necessary data provided by the kernel of course).
//! - It is mandatory to return \ref KERNEL_STATUS_CONTINUE to the customisation service.
//!
//! The function to be called when the customisation service is called by the Interac kernel shall have the following format :
//! \code
//! static int custom_kernel_ (unsigned int nSize, void * pData);
//! \endcode
//!
//! Declare the customisation service in the application :
//! \code
//! static service_desc_t Services[] = {
//! 	// ...
//! 	{ 0, SERVICE_CUSTOM_KERNEL, (SAP)custom_kernel_, SERVICES_DEFAULT_PRIORITY },
//! 	// ...
//! };
//! \endcode
//!
//! Here is an example about how to manage the customisation itself :
//! \code
//! // Function called when customisation service is called
//! static int custom_kernel_ (unsigned int nSize, void * pData)
//! {
//! 	int nResult, cr;
//! 	int nPosition;
//! 	unsigned char ucStepId;
//! 	unsigned long ulReadLength;
//! 	unsigned char * pReadValue = NULL;
//! 	T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT * pSharedStruct;
//! 	T_SHARED_DATA_STRUCT * pDataStuct;
//! 
//! 	(void) nSize;
//! 	
//! 	// It is mandatory to always return KERNEL_STATUS_CONTINUE for every customisation steps
//! 	nResult = KERNEL_STATUS_CONTINUE;
//! 
//! 	// The "pData" variable contain the shared buffer address
//! 	pSharedStruct = (T_SERVICE_CALL_SHARED_EXCHANGE_STRUCT *)pData;
//! 	pDataStuct = pSharedStruct->pDataStruct;
//! 
//! 	// Retrieve the step to be customised
//! 	nPosition = SHARED_EXCHANGE_POSITION_NULL;
//! 	cr = GTL_SharedExchange_FindNext (pDataStuct, &nPosition, TAG_KERNEL_CUSTOM_STEP, &ulReadLength, (const unsigned char **)&pReadValue);
//!		
//! 	if (cr != STATUS_SHARED_EXCHANGE_OK)
//! 	{
//! 		// No provided kernel step, so continue the transaction
//! 		nResult = KERNEL_STATUS_CONTINUE;
//! 	}
//! 	else
//! 	{
//! 		// Get the customisation step identifier
//!			ucStepId = pReadValue[0];
//!			
//! 		switch(ucStepId)
//! 		{
//! 		case (STEP_INTERAC_REMOVE_CARD):
//! 			// Card can be remove, do GUI
//! 			// ...
//! 			// Clear the shared buffer before returning to the kernel
//! 			GTL_SharedExchange_ClearEx (pDataStuct, FALSE);
//! 			break;
//! 		case (STEP_INTERAC_GET_CERTIFICATE):
//! 			// Get the certificate depending on the other provided data
//! 			// Clear the shared buffer before returning to the kernel
//! 			GTL_SharedExchange_ClearEx (pDataStuct, FALSE);
//! 			// ... and add output data if necessary
//! 			break;
//! 		case (STEP_INTERAC_EXCEPTION_FILE_GET_DATA):
//! 			// Check if the card is present in the exception file or not
//! 			// Clear the shared buffer before returning to the kernel
//! 			GTL_SharedExchange_ClearEx (pDataStuct, FALSE);
//! 			// ... and add output data if necessary
//! 			break;
//! 		default:
//! 			break;
//! 		}
//! 	}
//! 
//! 	return (nResult);
//! }
//! \endcode
//! 
//! 
//! <b>Which data are provided to custom for customisation ?</b><br>
//! By default, some data are provided to the custom on each step to be customised. By default, the following data are provided :
//!	- \ref TAG_KERNEL_CUSTOM_STEP indicating the step identifier.
//!	- \ref TAG_EMV_LANGUAGE_PREFERENCE indicating the list of supported language by the card (if present). It may help to correctly do GUI if necessary, with the correct language.
//!	- \ref TAG_KERNEL_SELECTED_PREFERED_LANGUAGE indicating the selected language during the language selection (if not present, default language shall be used). It may help to correctly do GUI if necessary, with the correct language.
//! 
//! Some specific additional data are sent depending on the customisation step :
//!	- \ref STEP_INTERAC_EXCEPTION_FILE_GET_DATA step :
//!		- Additional data provided by the Interac kernel :
//!			- \ref TAG_EMV_APPLI_PAN to indicate the card PAN.
//!			- \ref TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER to indicate the PAN Sequence number (if present).
//!		- Data that can be provided to the kernel (output) :
//!			- \ref TAG_KERNEL_PAN_IN_BLACK_LIST to indicate if PAN has been found in the exception file or not.
//!
//!	- \ref STEP_INTERAC_GET_CERTIFICATE step :
//!		- Additional data provided by the Interac kernel :
//!			- \ref TAG_EMV_DF_NAME to identify the RID to get the certificate.
//!			- \ref TAG_EMV_CA_PUBLIC_KEY_INDEX_CARD indicating the CA index (provided by the card).
//!		- Data to be provided to the kernel (output) :
//!			- \ref TAG_EMV_INT_CAPK_MODULUS containing the CA public key modulus.
//!			- \ref TAG_EMV_INT_CAPK_EXPONENT containing the CA public key exponent.
//! @}



//! \addtogroup InteracProprietaryTags
//! @{
//! The Interac kernel allows you to define a certain number of proprietary tags. It allows answering some specific field needs.
//! This section describes how to define these tags to make them known by the Interac kernel.
//! 
//! The proprietary tags are defined using the \ref TAG_KERNEL_PROPRIETARY_TAGS tag. When this tag is sent to the Interac kernel, 
//! this one create a proprietary database in which will be stored all the defined tags.
//! The \ref TAG_KERNEL_PROPRIETARY_TAGS tag is a list of \ref T_TI_TAG_INFO structures (see GTL documentation for more information). 
//! All the T_TI_TAG_INFO structures shall be stored using a tag ascendant order (if not, proprietary database will not correctly work).
//!
//! Here is an example of how to format the \ref TAG_KERNEL_PROPRIETARY_TAGS tag :
//! \code
//! int cr;
//! T_TI_TAG_INFO * pProprietaryTags[] = 
//! {
//! //  Tag,        Min    Max     Source               Format            Length type       Single or multiple    RFU
//! 	{0xDF01,     2,     2,     {TAG_SOURCE_ICC,      TAG_FORMAT_B,     LENGTH_RANGE,     OCCURENCE_SINGLE,     OPTIONS_RFU},  // Information for tag DF01 (length is 2 bytes, card data with binary format).
//! 	{0xDF02,     1,     255,   {TAG_SOURCE_TERMINAL, TAG_FORMAT_N,     LENGTH_RANGE,     OCCURENCE_SINGLE,     OPTIONS_RFU},  // Information for tag DF02 (length is in [1;255], terminal data with numeric format.
//! 	{0xDF03,     1,     5,     {TAG_SOURCE_ICC,      TAG_FORMAT_B,     LENGTH_EXCLUSIVE, OCCURENCE_SINGLE,     OPTIONS_RFU}   // Information for tag DF03 (length is either 1 or 5, card data with binary format.
//! };
//! 
//! // We consider that pDataStruct is the shared buffer used to send data to the Interac kernel
//! cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_KERNEL_PROPRIETARY_TAGS, sizeof(pProprietaryTags), pProprietaryTags);
//! if (cr != STATUS_SHARED_EXCHANGE_OK)
//! {
//! 	// An error occurred
//! 	// ...
//! }
//!
//! // When performing the transaction, tags DF01, DF02 and DF03 will be known by the Interac kernel, and they will be stored ...
//! // ...
//! 
//! \endcode
//! 
//! \note This tag (if necessary) shall be sent to the Interac kernel on the \ref Interac_DoTransaction() function. As all other tags, this 
//! one is not persistent. It means it shall be sent on every transaction where the proprietary tags are necessary.
//! @}

