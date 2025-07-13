/**
 * \file     Discover_API.h
 * \brief    This describes the Discover kernel API.
 * \details It consists of the following defines :
 *	- Transaction steps identifiers.
 *	- Specific Discover status codes.
 *	- Discover timers definition.
 *	- Error codes definitions.
 *	- Discover kernel API functions.*
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


/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global definition //////////////////////////////////////////

//! \addtogroup DiscoverTransactionFlowSteps
//! @{
#define STEP_DISCOVER_INITIAL							0x00								/*!< Discover Step : Initial process management. */
#define STEP_DISCOVER_FINAL_SELECTION					0x01								/*!< Discover Step : Final card selection process. The Final SELECT card response is provided by the custom application (application selection performed by Entry Point). */
#define STEP_DISCOVER_INITIATE_APPLI_PROCESSING			0x02								/*!< Discover Step : Initiate application processing (sends GetProcessingOptions command to the card to determine the card type). */
#define STEP_DISCOVER_APPLICATION_BLOCKED				0x03								/*!< Discover Step : Processing when application is blocked. */
#define STEP_DISCOVER_CARD_BLOCKED						0x04								/*!< Discover Step : Processing when card is blocked. */
#define STEP_DISCOVER_READ_APPLI_DATA					0x30								/*!< Discover Step (MSTRIPE) : Read M/Stripe card application data. */
#define STEP_DISCOVER_APPLI_VERSION_NB_CHECKING			0x31								/*!< Discover Step (MSTRIPE) : The Discover reader verifies the compatibility of its application with the card application. */
#define STEP_DISCOVER_REMOVE_CARD						0x33								/*!< Discover Step (MSTRIPE) : This step is just there to indicate card read is complete and cardholder can remove the card from the field. It would be used for GUI customisation only. */
#define STEP_DISCOVER_COMPLETION						0x40								/*!< Discover Step : Performs the Discover transaction completion and give back hand to the custom application. */
#define STEP_DISCOVER_STOP								0x50								/*!< Discover Step : Terminate kernel processing (end of transaction or transaction termination). */
//! @}

//! \addtogroup DiscoverTimeMeasure
//! @{
#define DISCOVER_TIME_TYPE_CARD							0x80000000  						/*!< Time measure is relative to card access. */
#define DISCOVER_TIME_TYPE_FCT							0x40000000  						/*!< Time measure is relative to code execution. */
#define DISCOVER_TIME_TYPE_SYSTEM						0x20000000  						/*!< Time measure is relative to system + manager + ... code execution. */

#define DISCOVER_TIME_FCT_PRELIMINARY					DISCOVER_TIME_TYPE_FCT+1				/*!< Time measure for Preliminary function execution */
#define DISCOVER_TIME_FCT_PRELIMINARY_END				DISCOVER_TIME_TYPE_FCT+2 			/*!< Time measure end for Preliminary function execution */
#define DISCOVER_TIME_FCT_TXN							DISCOVER_TIME_TYPE_FCT+3				/*!< Time measure for transaction function execution */
#define DISCOVER_TIME_FCT_TXN_END						DISCOVER_TIME_TYPE_FCT+4				/*!< Time measure end for Transaction function execution */
#define DISCOVER_TIME_FCT_LOAD_DATA						DISCOVER_TIME_TYPE_FCT+5				/*!< Time measure for Data function execution */
#define DISCOVER_TIME_FCT_LOAD_DATA_END					DISCOVER_TIME_TYPE_FCT+6				/*!< Time measure end for Data function execution */
#define DISCOVER_TIME_FCT_GET_DATA						DISCOVER_TIME_TYPE_FCT+7				/*!< Time measure for data obtention function execution */
#define DISCOVER_TIME_FCT_GET_DATA_END					DISCOVER_TIME_TYPE_FCT+8				/*!< Time measure end for data obtention function execution */
#define DISCOVER_TIME_FCT_GET_ALL_DATA					DISCOVER_TIME_TYPE_FCT+9				/*!< Time measure for obtain all data function execution */
#define DISCOVER_TIME_FCT_GET_ALL_DATA_END				DISCOVER_TIME_TYPE_FCT+10			/*!< Time measure end for obtain all data function execution */
//! @}


//! \addtogroup DiscoverErrorDefinition
//! @{
#define ERR_DISCOVER_BASE                         		0x16000000							/*!< Error Code : warning, the first index of error code depend on each kernel... see documentation */

#define ERR_DISCOVER_NO_TAG								0xFFFFFFFF							/*!< Indicates there is no concerned tag for the provided error. */
#define ERR_DISCOVER_000001                       		ERR_DISCOVER_BASE+0x000001			/*!< Discover error N°01, 	Discover_Entry.c, __Discover_Entry_LoadTags, An error occured when removing tag from the database */
#define ERR_DISCOVER_000002                       		ERR_DISCOVER_BASE+0x000002			/*!< Discover error N°02, 	Discover_Entry.c, __Discover_Entry_LoadTags, The list of provided tag has an incorrect format (parsing error). */
#define ERR_DISCOVER_000003                       		ERR_DISCOVER_BASE+0x000003			/*!< Discover error N°03, 	Discover_Entry.c, __Discover_Entry_Store_One_Tag, An error occured when adding the provided tag in the database. */
#define ERR_DISCOVER_000004                       		ERR_DISCOVER_BASE+0x000004			/*!< Discover error N°04, 	Discover_Debug.c, Discover_Debug_TimeInit, Unable to get the TAG_KERNEL_DEBUG_TIME tag from the database (not present or error). */
#define ERR_DISCOVER_000005                       		ERR_DISCOVER_BASE+0x000005			/*!< Discover error N°05, 	Discover_Debug.c, Discover_Debug_TimeInit, An error occured when adding the TAG_KERNEL_DEBUG_TIME tag in database for time initialisation. */
#define ERR_DISCOVER_000006                       		ERR_DISCOVER_BASE+0x000006			/*!< Discover error N°06, 	Discover_Entry.c, __Discover_Entry_LoadTags, An error occured when adding the provided tag in the database. */
#define ERR_DISCOVER_000007                       		ERR_DISCOVER_BASE+0x000007			/*!< Discover error N°07, 	Discover_Entry.c, __Discover_Entry_Get_Kernel_Infos, Unable to add \a TAG_KERNEL_APPLICATION_NAME tag in the exchange buffer. */
#define ERR_DISCOVER_000008                       		ERR_DISCOVER_BASE+0x000008			/*!< Discover error N°08, 	Discover_Entry.c, __Discover_Entry_Get_Kernel_Infos, Unable to add \a TAG_KERNEL_APPLICATION_IDENT tag in the exchange buffer. */
#define ERR_DISCOVER_000009                       		ERR_DISCOVER_BASE+0x000009			/*!< Discover error N°09, 	Discover_Entry.c, __Discover_Entry_Get_Kernel_Infos, Unable to add \a TAG_KERNEL_APPLICATION_CRC tag in the exchange buffer. */
#define ERR_DISCOVER_00000A                       		ERR_DISCOVER_BASE+0x00000A			/*!< Discover error N°0A, 	Discover_Entry.c, __Discover_Entry_Get_Kernel_Infos, There is not enough space in the exchange buffer to store all the kernel information. */
#define ERR_DISCOVER_00000B                       		ERR_DISCOVER_BASE+0x00000B			/*!< Discover error N°0B, 	Discover_Entry.c, __Discover_Entry_Get_Kernel_Infos, An internal error occured when getting the kernel information. */
#define ERR_DISCOVER_00000C                       		ERR_DISCOVER_BASE+0x00000C			/*!< Discover error N°0C, 	Discover_Entry.c, __Discover_Entry_Get_Data, Unable to add the retrieved tag in the exchange buffer. */
#define ERR_DISCOVER_00000D                       		ERR_DISCOVER_BASE+0x00000D			/*!< Discover error N°0D, 	Discover_Entry.c, __Discover_Entry_Get_Data, An error occured when getting the provided tag from the database. */
#define ERR_DISCOVER_00000E                       		ERR_DISCOVER_BASE+0x00000E			/*!< Discover error N°0E, 	Discover_Entry.c, __Discover_Entry_Get_All_Data, Unable to add the retrieved tag in the exchange buffer. */
#define ERR_DISCOVER_00000F                       		ERR_DISCOVER_BASE+0x00000F			/*!< Discover error N°0F, 	Discover_Common.c, Discover_Common_LoadTagsFromExchangeStructToDatabase, An error occured when creating the proprietary data storage in the database. */
#define ERR_DISCOVER_000010                       		ERR_DISCOVER_BASE+0x000010			/*!< Discover error N°10, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ExtractAndParseFciTemplate, SELECT response is not correctly formatted (padding outside the template, or incorrect length). */
#define ERR_DISCOVER_000011                       		ERR_DISCOVER_BASE+0x000011			/*!< Discover error N°11, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ExtractAndParseFciTemplate, A mandatory icc data is missing : TAG_FCI_TEMPLATE. Tag found is not the expected one. */
#define ERR_DISCOVER_000012                       		ERR_DISCOVER_BASE+0x000012			/*!< Discover error N°12, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ExtractAndParseFciTemplate, FCI Template has bad format */
#define ERR_DISCOVER_000013                       		ERR_DISCOVER_BASE+0x000013			/*!< Discover error N°13, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ParseFciProprietaryTemplate, The terminal shall discard tags that are not expected in the FCI Proprietary Template (concerned tag is provided). */
#define ERR_DISCOVER_000014                       		ERR_DISCOVER_BASE+0x000014			/*!< Discover error N°14, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ParseFciProprietaryTemplate, A parsing error occured on the card response (extracting data from FCI Proprietary Template). */
#define ERR_DISCOVER_000015                       		ERR_DISCOVER_BASE+0x000015			/*!< Discover error N°15, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ExtractAndParseFciTemplate, The terminal shall ignore tags that are not expected in the FCI (concerned tag is provided). */
#define ERR_DISCOVER_000016                       		ERR_DISCOVER_BASE+0x000016			/*!< Discover error N°16, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ExtractAndParseFciTemplate, A parsing error occured on the card response (extracting data from FCI template). */
#define ERR_DISCOVER_000017                       		ERR_DISCOVER_BASE+0x000017			/*!< Discover error N°17, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ExtractAndParseFciTemplate, Missing mandatory data in the SELECT response (in the 6F template) : TAG_EMV_DF_NAME. */
#define ERR_DISCOVER_000018                       		ERR_DISCOVER_BASE+0x000018			/*!< Discover error N°18, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ExtractAndParseFciTemplate, Missing mandatory data in the SELECT response (in the 6F template) : TAG_EMV_FCI_PROPRIETARY_TEMPLATE. */
#define ERR_DISCOVER_000019                       		ERR_DISCOVER_BASE+0x000019			/*!< Discover error N°19, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ExtractAndParseFciTemplate, Tag \a TAG_EMV_FCI_PROPRIETARY_TEMPLATE is present but its length is 0. */
#define ERR_DISCOVER_00001A                       		ERR_DISCOVER_BASE+0x00001A			/*!< Discover error N°1A, 	Discover_Txn_FinalSelect.c, __Discover_Common_CheckAndStore, A critical tag is redundant within the card (concerned tag is provided). */
#define ERR_DISCOVER_00001B                       		ERR_DISCOVER_BASE+0x00001B			/*!< Discover error N°1B, 	Discover_Txn_FinalSelect.c, __Discover_Common_CheckAndStore, A critical tag has a bad format (bad length or incorrect format)(concerned tag is provided). */
#define ERR_DISCOVER_00001C                       		ERR_DISCOVER_BASE+0x00001C			/*!< Discover error N°1C, 	Discover_Txn_FinalSelect.c, __Discover_Common_CheckAndStore, There is not enough memory to add the tag in the database (concerned tag is provided). */
#define ERR_DISCOVER_00001D                       		ERR_DISCOVER_BASE+0x00001D			/*!< Discover error N°1D, 	Discover_Txn_FinalSelect.c, __Discover_Common_CheckAndStore, An internal error occured when adding the tag in the database (concerned tag is provided). */
#define ERR_DISCOVER_00001E                       		ERR_DISCOVER_BASE+0x00001E			/*!< Discover error N°1E, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ParseFciProprietaryTemplate, An error occured as FCI Proprietary Template is not correctly stored in the database (it shall be present, i.e. length != 0 and value != NULL). */
#define ERR_DISCOVER_00001F                       		ERR_DISCOVER_BASE+0x00001F			/*!< Discover error N°1F, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ParseFciIssuerDiscretionaryData, FCI Issuer Discretionnary Data parsing error. */
#define ERR_DISCOVER_000020                       		ERR_DISCOVER_BASE+0x000020			/*!< Discover error N°20, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ParseFciIssuerDiscretionaryData, This function cannot be called if FCI Issuer Deiscretionary Data Template is not in database (shall be checked before calling this function). */
#define ERR_DISCOVER_000021                       		ERR_DISCOVER_BASE+0x000021			/*!< Discover error N°21, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse, Unable to get the Final SELECT Response (that shall be provided by entry point). */
#define ERR_DISCOVER_000022                       		ERR_DISCOVER_BASE+0x000022			/*!< Discover error N°22, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse, Final SELECT status word indicates card is blocked (0x6A81). */
#define ERR_DISCOVER_000023                       		ERR_DISCOVER_BASE+0x000023			/*!< Discover error N°23, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse, Final SELECT status word indicates application is blocked (0x6283). */
#define ERR_DISCOVER_000024                       		ERR_DISCOVER_BASE+0x000024			/*!< Discover error N°24, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse, Final SELECT status word indicates application locked (0x6999). */
#define ERR_DISCOVER_000025                       		ERR_DISCOVER_BASE+0x000025			/*!< Discover error N°25, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse, Final SELECT status word indicates an unexpected status word. */
#define ERR_DISCOVER_000026                       		ERR_DISCOVER_BASE+0x000025			/*!< Discover error N°25, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse, Unable to get the Final SELECT SW1, SW2 (that shall be provided by entry point). */
#define ERR_DISCOVER_000027                       		ERR_DISCOVER_BASE+0x000027			/*!< Discover error N°27, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ExtractAndParseFciTemplate, DF Name does not match selected ADF Name. */
#define ERR_DISCOVER_000028                       		ERR_DISCOVER_BASE+0x000028			/*!< Discover error N°28, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ExtractAndParseFciTemplate, Unable to get the final terminal selected AID from the database (4F). */
#define ERR_DISCOVER_000029                       		ERR_DISCOVER_BASE+0x000029			/*!< Discover error N°29, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ParseFciProprietaryTemplate, A mandatory data is missing : TAG_EMV_PDOL. */
#define ERR_DISCOVER_00002A                       		ERR_DISCOVER_BASE+0x00002A			/*!< Discover error N°2A, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ParseFciIssuerDiscretionaryData, Ignore missing tags in discretionary data field. */
#define ERR_DISCOVER_00002B                       		ERR_DISCOVER_BASE+0x00002B			/*!< Discover error N°2B, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_ExtractAndParseFciTemplate, A database error occured when adding FCI template in the database. */
#define ERR_DISCOVER_00002D                       		ERR_DISCOVER_BASE+0x00002D			/*!< Discover error N°2D, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_ResponseAnalysisFormat1, An error occured when adding AIP in the database. */
#define ERR_DISCOVER_00002E                       		ERR_DISCOVER_BASE+0x00002E			/*!< Discover error N°2E, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_ResponseAnalysisFormat1, An error occured when adding AFL in the database. */
#define ERR_DISCOVER_00002F                       		ERR_DISCOVER_BASE+0x00002F			/*!< Discover error N°2F, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_ResponseAnalysisFormat1, AFL is not correctly formatted. */
#define ERR_DISCOVER_000030                      		ERR_DISCOVER_BASE+0x000030			/*!< Discover error N°30, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_ResponseAnalysisFormat1, Missing mandatory data within the card (TAG_EMV_AFL). */
#define ERR_DISCOVER_000031                       		ERR_DISCOVER_BASE+0x000031			/*!< Discover error N°31, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_ResponseAnalysisFormat1, Template fromat 1 is too small (incorrect format). */
#define ERR_DISCOVER_000032                       		ERR_DISCOVER_BASE+0x000032			/*!< Discover error N°32, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_ResponseAnalysisFormat2, An error occured when adding AIP in the database. */
#define ERR_DISCOVER_000033                       		ERR_DISCOVER_BASE+0x000033			/*!< Discover error N°33, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_ResponseAnalysisFormat2, An error occured when adding AFL in the database. */
#define ERR_DISCOVER_000034                       		ERR_DISCOVER_BASE+0x000034			/*!< Discover error N°34, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_ResponseAnalysisFormat2, Parsing error in the format 2 response template. */
#define ERR_DISCOVER_000035                       		ERR_DISCOVER_BASE+0x000035			/*!< Discover error N°35, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_ResponseAnalysisFormat2, Missing mandatory data within the card (TAG_EMV_AFL). */
#define ERR_DISCOVER_000036                       		ERR_DISCOVER_BASE+0x000036			/*!< Discover error N°36, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_ResponseAnalysisFormat2, Missing mandatory data within the card (TAG_EMV_AIP). */
#define ERR_DISCOVER_000037                       		ERR_DISCOVER_BASE+0x000037			/*!< Discover error N°37, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_CardResponseAnalysis, Card GPO response has not a correct format (bad TLV coding). */
#define ERR_DISCOVER_000038                       		ERR_DISCOVER_BASE+0x000038			/*!< Discover error N°38, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_CardResponseAnalysis, Card GPO response has no data. */
#define ERR_DISCOVER_000039                       		ERR_DISCOVER_BASE+0x000039			/*!< Discover error N°39, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_CardResponseAnalysis, Card GPO response has not a correct format (data outside the template). */
#define ERR_DISCOVER_00003A                       		ERR_DISCOVER_BASE+0x00003A			/*!< Discover error N°3A, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_CardResponseAnalysis, An error occured when analyses the format 1 GPO response data. */
#define ERR_DISCOVER_00003B                       		ERR_DISCOVER_BASE+0x00003B			/*!< Discover error N°3B, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_CardResponseAnalysis, An error occured when analyses the format 2 GPO response data. */
#define ERR_DISCOVER_00003C                       		ERR_DISCOVER_BASE+0x00003C			/*!< Discover error N°3C, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_CardResponseAnalysis, Card responds with an unknown format, transaction is to be terminated. */
#define ERR_DISCOVER_00003D                       		ERR_DISCOVER_BASE+0x00003D			/*!< Discover error N°3D, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_CardResponseAnalysis, Status word for GPO is not x9000. */
#define ERR_DISCOVER_00003E                       		ERR_DISCOVER_BASE+0x00003E			/*!< Discover error N°3E, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand, An error occured when building the PDOL (9F37 missing). */
#define ERR_DISCOVER_00003F                       		ERR_DISCOVER_BASE+0x00003F			/*!< Discover error N°3F, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand, An error occured when adding constructed PDOL value in the database (9F37 incorrect length). */
#define ERR_DISCOVER_000040                       		ERR_DISCOVER_BASE+0x000040			/*!< Discover error N°40, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand, Unable to build the Get Processing Options command. */
#define ERR_DISCOVER_000041                       		ERR_DISCOVER_BASE+0x000041			/*!< Discover error N°41, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand, Communication error with the card (GPO command). */
#define ERR_DISCOVER_000042                       		ERR_DISCOVER_BASE+0x000042			/*!< Discover error N°42, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand, GPO Card response analysis failed. */
#define ERR_DISCOVER_000043                       		ERR_DISCOVER_BASE+0x000043			/*!< Discover error N°43, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand, Unable to get TAG_EMV_UNPREDICTABLE_NUMBER from the database. */
#define ERR_DISCOVER_000044                       		ERR_DISCOVER_BASE+0x000044			/*!< Discover error N°44, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_DetermineTransactionFlow, AIP is not 0x00, 0x00. */
#define ERR_DISCOVER_000045                       		ERR_DISCOVER_BASE+0x000045			/*!< Discover error N°45, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand, An error occured when adding TAG_EMV_UNPREDICTABLE_NUMBER to the database. */
#define ERR_DISCOVER_000046                       		ERR_DISCOVER_BASE+0x000046			/*!< Discover error N°46, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand, PDOL Length is zero, terminate transaction. */
#define ERR_DISCOVER_000047                       		ERR_DISCOVER_BASE+0x000047			/*!< Discover error N°47, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand, An error occured when building the PDOL. */
#define ERR_DISCOVER_000048                       		ERR_DISCOVER_BASE+0x000048			/*!< Discover error N°48, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand,  An error occured when adding the constructed PDOL to the database. */
#define ERR_DISCOVER_000049                       		ERR_DISCOVER_BASE+0x000049			/*!< Discover error N°49, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_Check, Unable to get the AIP from the database. */
#define ERR_DISCOVER_00004A                       		ERR_DISCOVER_BASE+0x00004A			/*!< Discover error N°4A, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_ExtractDataFromTrack2, A database error occured when adding TAG_EMV_TRACK_2_EQU_DATA in the database. */
#define ERR_DISCOVER_00004B                       		ERR_DISCOVER_BASE+0x00004B			/*!< Discover error N°4B, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_ExtractDataFromTrack2, A database error occured when adding TAG_EMV_APPLI_PAN in the database. */
#define ERR_DISCOVER_00004C                       		ERR_DISCOVER_BASE+0x00004C			/*!< Discover error N°4C, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_ExtractDataFromTrack2, PAN is out of range in the track 2 data. */
#define ERR_DISCOVER_00004D                       		ERR_DISCOVER_BASE+0x00004D			/*!< Discover error N°4D, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_ExtractDataFromTrack2, A database error occured when adding the Card Expiration Date in the database. */
#define ERR_DISCOVER_000050                       		ERR_DISCOVER_BASE+0x000050			/*!< Discover error N°50, 	Discover_Txn_VersionNbChecking.c, __Discover_Txn_TrackSeeding, Card version 02xx or more and returned 9F8003 so terminate the transaction. */
#define ERR_DISCOVER_000051                       		ERR_DISCOVER_BASE+0x000051			/*!< Discover error N°51, 	Discover_Txn_VersionNbChecking.c, __Discover_Txn_TrackSeeding, A database error occured when getting the card AVN. */
#define ERR_DISCOVER_000052                       		ERR_DISCOVER_BASE+0x000052			/*!< Discover error N°52, 	Discover_Txn_VersionNbChecking.c, __Discover_Txn_TrackSeeding, Unable to get track 2 data from the database. */
#define ERR_DISCOVER_000053                       		ERR_DISCOVER_BASE+0x000053			/*!< Discover error N°53, 	Discover_Txn_VersionNbChecking.c, __Discover_Txn_TrackSeeding, An error occured when adding the modified track 2 data to the database */
#define ERR_DISCOVER_000054                       		ERR_DISCOVER_BASE+0x000054			/*!< Discover error N°54, 	Discover_Txn_VersionNbChecking.c, __Discover_Txn_TrackSeeding, Unable to get the track 1 data (tag 56) from the database */
#define ERR_DISCOVER_000055                       		ERR_DISCOVER_BASE+0x000055			/*!< Discover error N°55, 	Discover_Txn_VersionNbChecking.c, __Discover_Txn_TrackSeeding, An error occured when adding the track 1 data to the database. */
#define ERR_DISCOVER_000063                       		ERR_DISCOVER_BASE+0x000063			/*!< Discover error N°63, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Missing mandatory tag : TAG_DISCOVER_TRACK1_DATA. */
#define ERR_DISCOVER_000064                       		ERR_DISCOVER_BASE+0x000064			/*!< Discover error N°64, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Missing mandatory tag : TAG_EMV_TRACK_2_EQU_DATA. */
#define ERR_DISCOVER_000067                       		ERR_DISCOVER_BASE+0x000067			/*!< Discover error N°67, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Card response to Read Record has not a correct format (bad TLV coding). */
#define ERR_DISCOVER_000068                       		ERR_DISCOVER_BASE+0x000068			/*!< Discover error N°68, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Card response to Read Record has no data. */
#define ERR_DISCOVER_000069                       		ERR_DISCOVER_BASE+0x000069			/*!< Discover error N°69, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Card response to Read Record has not a correct format (data outside the template). */
#define ERR_DISCOVER_00006A                       		ERR_DISCOVER_BASE+0x00006A			/*!< Discover error N°6A, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Card responds to Read Record with template different from 0x70, terminate the transaction. */
#define ERR_DISCOVER_00006B                       		ERR_DISCOVER_BASE+0x00006B			/*!< Discover error N°6B, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Card returned a redundant tag in a Read Record (tag is provided). */
#define ERR_DISCOVER_00006C                       		ERR_DISCOVER_BASE+0x00006C			/*!< Discover error N°6C, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Card returned a tag with a bad format in a Read Record (tag is provided) */
#define ERR_DISCOVER_00006D                       		ERR_DISCOVER_BASE+0x00006D			/*!< Discover error N°6D, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, A database error occured when storing data provided in Read Record. */
#define ERR_DISCOVER_00006E                       		ERR_DISCOVER_BASE+0x00006E			/*!< Discover error N°6E, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Card response to Read Record is not correctly formatted (BER-TLV parsing error). */
#define ERR_DISCOVER_00006F                       		ERR_DISCOVER_BASE+0x00006F			/*!< Discover error N°6F, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Bad SFI (SFI > 30). */
#define ERR_DISCOVER_000070                       		ERR_DISCOVER_BASE+0x000070			/*!< Discover error N°70, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Status Word is not x9000 to the READ RECORD response. */
#define ERR_DISCOVER_000071                       		ERR_DISCOVER_BASE+0x000071			/*!< Discover error N°71, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, An error occured when building the Read Record command. */
#define ERR_DISCOVER_000072                       		ERR_DISCOVER_BASE+0x000072			/*!< Discover error N°72, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Communication error with the card (Read Application Data). */
#define ERR_DISCOVER_000073                       		ERR_DISCOVER_BASE+0x000073			/*!< Discover error N°73, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckMandatoryDataPresence, Read Record Card response analysis failed. */
#define ERR_DISCOVER_000074                       		ERR_DISCOVER_BASE+0x000074			/*!< Discover error N°74, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckAflAndReadApplicationData, Missing mandatory data : TAG_EMV_AFL. */
#define ERR_DISCOVER_000075                       		ERR_DISCOVER_BASE+0x000075			/*!< Discover error N°75, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckAflAndReadApplicationData, AFL is not 08010100 so terminate the transaction. */
#define ERR_DISCOVER_000076                       		ERR_DISCOVER_BASE+0x000076			/*!< Discover error N°76, 	Discover_Txn_Rad.c, __Discover_Txn_Rad_CheckAflAndReadApplicationData, An error occured when reading the application data within the card. */
#define ERR_DISCOVER_000096                       		ERR_DISCOVER_BASE+0x000096			/*!< Discover error N°96, 	Discover_Txn_Completion.c, __Discover_Txn_Completion_AddTagToStructure, An error occured when adding the tag in exchange data structure (tag is provided). */
#define ERR_DISCOVER_000097                       		ERR_DISCOVER_BASE+0x000097			/*!< Discover error N°97, 	Discover_Txn_Completion.c, __Discover_Txn_Completion_FillExchangeStructure, An error occured when adding common tags in the exchange data structure. */
#define ERR_DISCOVER_000098                       		ERR_DISCOVER_BASE+0x000098			/*!< Discover error N°98, 	Discover_Txn_Completion.c, __Discover_Txn_Completion_FillExchangeStructure, An error occured when adding Discover tags in the exchange data structure. */
#define ERR_DISCOVER_00009C                       		ERR_DISCOVER_BASE+0x00009C			/*!< Discover error N°9C, 	Discover_Txn_Completion.c, __Discover_Txn_Completion_FillExchangeStructure, Invalid input data (pointer on data exchange is NULL). */
#define ERR_DISCOVER_00009D                       		ERR_DISCOVER_BASE+0x00009D			/*!< Discover error N°9D, 	Discover_Common.c, Discover_Common_SetTransactionOutcome, Unable to add TAG_DISCOVER_TRANSACTION_OUTCOME tag in the database. */
#define ERR_DISCOVER_00009E                       		ERR_DISCOVER_BASE+0x00009E			/*!< Discover error N°9E, 	Discover_Txn_FinalSelect.c, __Discover_Txn_FinalSelect_LanguageSelection, Unable to add TAG_DISCOVER_TRANSACTION_OUTCOME tag in the database. */
#define ERR_DISCOVER_00012D                       		ERR_DISCOVER_BASE+0x00012D			/*!< Discover error N°12D, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand, An error occured when adding the command to be sent in the database. */
#define ERR_DISCOVER_00012E                       		ERR_DISCOVER_BASE+0x00012E			/*!< Discover error N°12E,	Discover_Txn_Iap.c, __Discover_Txn_Iap_BuildAndSendGpoCommand, An error occured when adding the card response to be sent in the database. */
#define ERR_DISCOVER_000131                       		ERR_DISCOVER_BASE+0x000131			/*!< Discover error N°131,	Discover_Txn_Rad.c, __Discover_Txn_Rad_ReadApplicationData, An error occured when adding the command to be sent in the database. */	
#define ERR_DISCOVER_000132                       		ERR_DISCOVER_BASE+0x000132			/*!< Discover error N°132,	Discover_Txn_Rad.c, __Discover_Txn_Rad_ReadApplicationData, An error occured when adding the card response to be sent in the database. */
#define ERR_DISCOVER_000137                       		ERR_DISCOVER_BASE+0x000137			/*!< Discover error N°137,	Discover_Debug.c, Discover_Debug_StoreCommandToBeSent, Unable to add TAG_DISCOVER_INT_SENT_APDU tag in the database. */
#define ERR_DISCOVER_000138                       		ERR_DISCOVER_BASE+0x000138			/*!< Discover error N°138,	Discover_Debug.c, Discover_Debug_StoreCardResponse, Unable to add TAG_DISCOVER_INT_CARD_RESPONSE tag in the database. */
#define ERR_DISCOVER_000143                       		ERR_DISCOVER_BASE+0x000143			/*!< Discover error N°143,	Discover_Common.c, Discover_Common_GetAndStoreUnpredictableNumber, An error occured when getting a random number (DLL). */
#define ERR_DISCOVER_000144                       		ERR_DISCOVER_BASE+0x000144			/*!< Discover error N°144,	Discover_Common.c, Discover_Common_GetAndStoreUnpredictableNumber, Unable to add TAG_EMV_UNPREDICTABLE_NUMBER tag in the database. */
#define ERR_DISCOVER_00014A                       		ERR_DISCOVER_BASE+0x00014A			/*!< Discover error N°14A, 	Discover_Txn_Iap.c, __Discover_Txn_Iap_ResponseAnalysisFormat2, AFL is not correctly formatted. */
#define ERR_DISCOVER_00014B              (0x04000156)		/*!< Paypass error, trm.c, TRM_RandomTransSelection2, A mandatory terminal data is not present : TAG_TRESH_VALUE_FOR_BIASED_RAND_SEL or TAG_TARG_PERC_FOR_BIASED_RAND_SEL or TAG_AMOUNT_AUTH_BIN. */
//! @}


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Glodal Data ///////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup DiscoverInterfaceFunctions
//! @{

//! \brief This function performs the Discover contactless transaction flow and is called by the payment application after 
//! Entry Point has completed Application Selection (PPSE and Final SELECT processing). 
//!	All the necessary data to perform the transaction shall be provided by the payment application. This data includes the
//! Entry Point returned Final SELECT response, Final SELECT command and Final SELECT status words (SW1, SW2).
//!	This function begins by analysing the Final SELECT response and status words and performs the transaction until completion.
//! The Discover transaction is a magnetic stripe based transaction that returns modified Track 1 and Track 2 data.
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel. 
//!	This shared buffer shall be initialised using the \a GTL_SharedExchange_InitShared() function 
//! (please refer to GTL documentation for more information about the data exchange buffer).
//!	- Input data list
//!	   - The following tags are mandatory:
//!		- \ref TAG_EP_FINAL_SELECT_COMMAND_SENT : Final SELECT command returned by Entry Point and supplied to the Discover kernel by the payment application. This data will be analysed by the Discover kernel.
//!		- \ref TAG_EP_FINAL_SELECT_RESPONSE : Final SELECT response returned by Entry Point and supplied to the Discover kernel by the payment application. This data will be analysed by the Discover kernel.
//!		- \ref TAG_EP_FINAL_SELECT_STATUS_WORD : Final SELECT status words (SW1,SW2) returned by Entry Point and supplied to the Discover kernel by the payment application. This data will be analysed by the Discover kernel.
//!	   - The following tags are optional:
//!		- \ref TAG_KERNEL_PAYMENT_FLOW_STOP : Data field indicating steps where the transaction flow has to be stopped. It is strongly recommanded, for transaction performances purposes, not to interrupt the transaction flow using this tag (recommanded value 0).
//!		- \ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM : Data field indicating steps where customisation is necessary.
//!		- \ref TAG_KERNEL_PROPRIETARY_TAGS : Description of the proprietary tags to be handled by the Discover kernel (RFU as no additional proprietary tags required).
//!	- Output data returned by the Discover kernel
//!			- \ref TAG_DISCOVER_TRANSACTION_OUTCOME : Indicates the transaction outcome (online request or terminated). If terminated no other tag data is returned.
//!			- \ref TAG_EMV_TRACK_2_EQU_DATA : The seeded track 2 equivilant data (tag 57).
//!			- \ref TAG_DISCOVER_TRACK1_DATA : The seeded track 1 data (tag 56).
//!			- \ref TAG_EMV_DF_NAME : The card returned DF Name (tag 84).
//!			- \ref TAG_EMV_APPLICATION_LABEL : The card returned Application Label (tag 50).
//!			- \ref TAG_EMV_APPLI_PREFERED_NAME : The optionally card returned Application Preferred Name (tag 9F12).
//!			- \ref TAG_EMV_APPLI_PRIORITY_INDICATOR : The card returned Application Priority Indicator (tag 87).
//!			- \ref TAG_DISCOVER_APPLI_VERSION_NUMBER_ICC : The optionally card returned Application Version Number (tag 9F7D).
//!			- \ref TAG_DISCOVER_DCVV : The optionally card returned Dynamic CVV for card versions 0200 or higher (tag 9F7E).
//!			- \ref TAG_DISCOVER_V1_DCVV : The optionally card returned Dynamic CVV for older V1 cards (tag 9F8003). ++++ WARNING ++++ This tag does not TLV parse correctly
//!
//!		- If the transaction is cancelled or interrupted, the \ref TAG_KERNEL_LAST_EXECUTED_STEP_INTERRUPTION is returned to indicate the last executed step when the interruption / cancellation occured.
//!		Please refer to \ref DiscoverTransactionFlowSteps for more information about the existing transaction steps. It is recommended to avoid using feature as it will adversely impact the contactless transaction.
//!
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_ONLINE_AUTHORISATION : Transaction succeeded and must be sent online for authorisation.
//!	- \ref KERNEL_STATUS_CANCELLED : if transaction has been cancelled by the custom application (using \a Discover_Cancel() function).
//!	Take care that when tranasction is cancelled by the user, status code returned is \ref KERNEL_STATUS_CANCELLED | \ref KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK.
//!	- \ref KERNEL_STATUS_COMMUNICATION_ERROR : if a communication error occured with the card (no reponse to a command because card has been to early removed for example).
//!	- \ref KERNEL_STATUS_INVALID_INPUT_DATA : if provided data in \a pDataStruct are not correct.
//!	- \ref KERNEL_STATUS_ICC_MISSING_DATA : if mandatory ICC card is missing.
//!	- \ref KERNEL_STATUS_ICC_INVALID_DATA : if card returned an invalid data.
//!	- \ref KERNEL_STATUS_ICC_REDUNDANT_DATA : if card returned a redundant data.
//!	- \ref KERNEL_STATUS_ICC_DATA_FORMAT_ERROR : if card returned data with bad format.
//!	- \ref KERNEL_STATUS_CARD_BLOCKED : If the card is blocked (Final SELECT status word is 0x6A81).
//!	- \ref KERNEL_STATUS_APPLICATION_BLOCKED : If the card application is blocked (Final SELECT status word is 0x6283 or 0x6999).
//!	- \ref KERNEL_STATUS_DATABASE_ERROR : A database error occured.
//!	- \ref KERNEL_STATUS_UNKNOWN_SW : The card responded to a command with an unexpected status word.
//!	- \ref KERNEL_STATUS_COND_OF_USE_NOT_SATISFIED : Card responded to GPO with 0x6985 status word.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY : There is not enough memeory to perform the transaction.
//!	- \ref KERNEL_STATUS_INTERNAL_ERROR : An internal kernel error occured (would never occur).
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The Discover kernel is not loaded in the terminal (or an interface error occured).
//! \note If the transaction is cancelled or suspended by the application, the returned status code is \a status \a code | \ref KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK.
//!	If transaction is cancelled or interrupted by the user, the kernel database is not altered to allow to continue the transaction 
//!	anyway if requested (using \ref Discover_ResumeTransaction() function).

int Discover_DoTransaction (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows the application to resume the transaction when an interruption occured (requested interruption or cancellation).
//! The transaction will continue where it has been interrupted. It is recommended to only use this feature for debug purposes as it will
//! adversely impact the contactless transaction.
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//!	- Input data can be provided. It will replace each existing data within the kernel database.
//!	- Output data are the same as \ref Discover_DoTransaction() function (as it continues the transaction).
//! \return Kernel processing status code (identical than the \ref Discover_DoTransaction() function).
//! The returned value depends on the step where the transaction is resumed.
//!	For example, \ref KERNEL_STATUS_COND_OF_USE_NOT_SATISFIED cannot be returned if you resume the transaction after the \ref STEP_DISCOVER_INITIATE_APPLI_PROCESSING step.

int Discover_ResumeTransaction (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows the application to retrieve all the tags contained in the Discover kernel database.
//! All the tags present in the database are retrieved.
//! \param[out] pDataStruct Shared buffer filled with all the kernel data. 
//! Make sure the application supplied buffer size is sufficient to store all the tags.
//! Note the shared buffer is automatically cleared by the Discover kernel.
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if all the data are provided and no error occured.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occured.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The Discover kernel is not loaded in the terminal (or an interface error occured).
//! \note It is strongly recommanded to not call this function during the transaction flow, as it should impact the transaction performance.

int Discover_GetAllData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows the application to request specific tags from the Discover kernel (if present in its database).
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//! Make sure the application supplied buffer size is sufficient to store all the tags.
//! Note the shared buffer is automatically cleared by the Discover kernel.
//!	- Input data : Tag to be requested to the kernel. It is a concatenation of tags and length set to 0.
//! - Output data : list of retrieved data (coded in BER-TLV) that have been equested and that are present in the kernel database.
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if all the data are provided and no error occured.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occured.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The Discover kernel is not loaded in the terminal (or an interface error occured).
//! \note It is strongly recommanded to not call this function during the transaction flow, as it should impact the transaction performance.
//! \remarks Example to get the transaction date and the transaction time from the Discover kernel :
//! \code
//!	T_SHARED_DATA_STRUCT * pSharedDataStruct;
//!	
//!	// Initialise the shared buffer to be used (if not already done).
//!	// Make sure size is bigger enough.
//!	pSharedDataStruct = GTL_SharedExchange_InitShared (256);
//!
//!	if (pSharedDataStruct == NULL)
//!	{
//!		// An error occured when creating the shared data structure.
//!		...
//!	}
//!	
//!	// Add TAG_EP_FINAL_SELECT_COMMAND_SENT tag in pSharedDataStruct with a zero length.
//!	ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_EP_FINAL_SELECT_COMMAND_SENT, 0, NULL);
//!	// Check returned value ...
//!	
//!	// Add TAG_EP_FINAL_SELECT_STATUS_WORD tag in pSharedDataStruct with a zero length.
//!	ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_EP_FINAL_SELECT_STATUS_WORD, 0, NULL);
//!	// Check returned value ...
//!	
//!	// Call the Discover kernel to retrieve the requested tags.
//!	nResult = Discover_GetData (pSharedDataStruct);
//!	if (nResult != KERNEL_STATUS_OK)
//!	{
//!		// An error occured when requesting tags to the kernel.
//!		// ...
//!	}
//!	
//!	// Now, pSharedDataStruct contains the requested tags (only the ones that are present within the kernel database)
//!	// You can use GTL_SharedExchange_GetNext and GTL_SharedExchange_FindNext functions to retrievethe desired tags.
//!	// ...
//!	
//!	// If created, destroy the shared buffer if not used anymore
//!	if (pSharedDataStruct != NULL)
//!		GTL_SharedExchange_DestroyShare (pSharedDataStruct);
//! \endcode

int Discover_GetData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows the application to load the Discover kernel with specific tag data.
//! \param[in] pDataStruct Shared buffer filled with the data to be loaded into the kernel.
//!	- \a pDataStruct is filled using the \a GTL_SharedExchange_AddTag() function.
//!	- All the tags that are unknown by the kernel are ignored.
//!	- If a tag is added with a zero length, it removes this tag from the kernel database.
//!	- If a provided tag is already present in the database, this one will be replaced by the new value.
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if tags correctly added in the kernel database and no error occured.
//!	- \ref KERNEL_STATUS_INVALID_INPUT_DATA : if provided data in \a pDataStruct are not correct.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in the kernel database to store all the tags.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occured.
//!	- \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The Discover kernel is not loaded in the terminal (or an interface error occured).
//! \note It is strongly recommanded to not call this function during the transaction flow, as it should impact the transaction performance.
//! \remarks Example to get the transaction date and the transaction time from the Discover kernel (if previously passed in using \ref Discover_DoTransaction()) :
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
//!		// An error occured when creating the shared data structure.
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
//!	// Call the Discover kernel to load the tags.
//!	nResult = Discover_LoadData (pSharedDataStruct);
//!	if (nResult != KERNEL_STATUS_OK)
//!	{
//!		// An error occured when requesting tags to the kernel.
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

int Discover_LoadData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function can be used by the application to cancel the Discover transaction.
//! This could be used to cancel the transaction when the red key is pressed during the Discover transaction for example.
//! It is unlikely that the transaction will be running long enough to require cancelling but this interface is provided
//! for consistency with existing contactless kernels.
//! \return Always \ref KERNEL_STATUS_OK.
//! \note This is the responsibility of the custom application to correctly use this function. 
//! The Discover transaction can be cancelled at any step.
//! If called, the kernel will return \ref KERNEL_STATUS_CANCELLED on the following functions :
//!	- \ref Discover_DoTransaction().
//!	- \ref Discover_ResumeTransaction().

int Discover_Cancel (void);



//! \brief This function allows the application to manage the Discover kernel debug features.
//! This allows activation / dactivation of the following debug features :
//!	- Trace : it provides debug information in the \a Trace.exe tool provided in the TDS.
//!	- Time measurements : it manages in the database the \ref TAG_KERNEL_DEBUG_TIME tag that can be retrieved using \ref Discover_GetData() function).
//!	Note if Time debug feature is not activated, \ref TAG_KERNEL_DEBUG_TIME tag is not stored in the kernel database.
//!	- APDU storage : it stores all the APDU sent to the card and responses sent by the card in the database, using specific tags. 
//!	This concerns the commands GPO and READ RECORD.
//!	Each command is stored in a \ref TAG_DISCOVER_INT_SENT_APDU tag, each received card response is stored in a \ref TAG_DISCOVER_INT_CARD_RESPONSE tag.
//! \param[in] pDataStruct Shared buffer filled with the \ref TAG_KERNEL_DEBUG_ACTIVATION tag indicating the debug mode.
//!	If the tag is not present or set to 0, then all the debug features are deactivated.
//! \return \ref KERNEL_STATUS_OK is always returned.
//!	\note If debug features shall be activated, it is strongly recommanded to call this function before the transaction has started.
//!	This ensures that this function does not adversely impact the contactless transaction time.
//! \remarks Example to get the transaction date and the transaction time from the Discover kernel :
//! \code
//!	T_SHARED_DATA_STRUCT * pSharedDataStruct;
//!	unsigned char ucTraceOnly = KERNEL_DEBUG_MASK_TRACES;	// Trace only is activated
//!	unsigned char ucApduOnly = KERNEL_DEBUG_MASK_APDU; // APDU is activated
//!	unsigned char ucTracesAndApdu = KERNEL_DEBUG_MASK_TRACES | KERNEL_DEBUG_MASK_APDU; // Traces and APDU debug features are activated.
//!	
//!	// Initialise the shared buffer to be used (if not already done).
//!	// Make sure size is bigger enough.
//!	pSharedDataStruct = GTL_SharedExchange_InitShared (128);
//!
//!	if (pSharedDataStruct == NULL)
//!	{
//!		// An error occured when creating the shared data structure.
//!		...
//!	}
//!	
//!	// Indicate Traces Only has to be activated.
//!	ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_KERNEL_DEBUG_ACTIVATION, 1, &ucTraceOnly);
//!	// Check returned value ...
//!	
//!	// Call the Discover kernel to load the tags.
//!	nResult = Discover_DebugManagement (pSharedDataStruct);
//!	if (nResult != KERNEL_STATUS_OK)
//!	{
//!		// An error occured when requesting tags to the kernel.
//!		// ...
//!	}
//!	
//!	// Indicate Traces Only has to be activated.
//!	ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_KERNEL_DEBUG_ACTIVATION, 1, &ucApduOnly);
//!	// Check returned value ...
//!	
//!	// Call the Discover kernel to load the tags.
//!	nResult = Discover_DebugManagement (pSharedDataStruct);
//!	if (nResult != KERNEL_STATUS_OK)
//!	{
//!		// An error occured when requesting tags to the kernel.
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

int Discover_DebugManagement (T_SHARED_DATA_STRUCT * pDataStruct);



//!	\brief This function clears and initialise the Discover kernel.
//! It fully clear the database and restores the global data (reset cancel, deactivate debug features, etc). 
//! It is mandatory to call this function 
//! after each Discover transation has been completed (and the terminal is returning on idle state).
//! \return Kernel processing status code.
//!	- \ref KERNEL_STATUS_OK if Discover kernel correctly cleared and initialised.
//!	- \ref KERNEL_STATUS_DATABASE_ERROR if a database error occured.

int Discover_Clear (void);

//! \brief This function gets the kernel information.
//! \param[out] pDataStruct Shared buffer filled with the following tags (note this buffer is automatically cleared by the function) :
//!	- \ref TAG_KERNEL_APPLICATION_NAME that indicates the application name (ASCII format).
//!	- \ref TAG_KERNEL_APPLICATION_IDENT that indicates the kernel identifier (in ASCII format, \a 3349 followed by the Discover kernel version on 4 digits).
//!	- \ref TAG_KERNEL_APPLICATION_CRC that indicates the Discover kernel CRC.
//! \return
//!	- \ref KERNEL_STATUS_OK if kernel information correctly retrieved.
//!	- \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!	- \ref KERNEL_STATUS_INTERNAL_ERROR if an internal error occurred.

int Discover_GetInfos (T_SHARED_DATA_STRUCT * pDataStruct);

//! \brief This function allows to execute a specific transaction step when an interruption has been executed
//! (requested interruption or cancellation).
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//!    - Input data can be provided. It will replace each existing data within the kernel database.
//!    - Output data are the same as \ref Discover_DoTransaction() function.
//! \return Kernel processing status code (identical to the \ref Discover_DoTransaction() function).
//! The returned value depends on the step where the transaction is resumed.

//! \brief Function to execute the ProcessTransactionStep kernel service. 
//! \param[in,out] pDataStruct data exchange buffer.
//! \return Kernel processing status code.

//int Discover_ProcessTransactionStep (T_SHARED_DATA_STRUCT * pDataStruct);

//! @}


//! \addtogroup DiscoverTransactionFlow
//! @{
//! The following details the Discover kernel transaction flow. Each transaction step in the following flow diagram corresponds to a transaction step described in \ref DiscoverTransactionFlowSteps.
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
//!		nodeStart [label="Discover_DoTransaction",shape="ellipse",style=filled];
//!		node_STEP_DISCOVER_INITIAL [label="Initial",size="50,2",style=filled,fillcolor=plum,URL="\ref STEP_DISCOVER_INITIAL"];
//!		node_STEP_DISCOVER_FINAL_SELECTION [label="Final Application Selection",size="5,2",style=filled,fillcolor=plum,URL="\ref STEP_DISCOVER_FINAL_SELECTION"];
//!		node_STEP_DISCOVER_INITIATE_APPLI_PROCESSING	[label="Initiate Application Processing",size="5,2",style=filled,fillcolor=plum,URL="\ref STEP_DISCOVER_INITIATE_APPLI_PROCESSING"];
//!		node_STEP_DISCOVER_READ_APPLI_DATA [label="Read Application Data",style=filled,fillcolor=plum,URL="\ref STEP_DISCOVER_READ_APPLI_DATA"];
//!		node_STEP_DISCOVER_APPLI_VERSION_NB_CHECKING [label="AVN Checking",style=filled,fillcolor=plum,URL="\ref STEP_DISCOVER_APPLI_VERSION_NB_CHECKING"];
//!		node_STEP_DISCOVER_REMOVE_CARD [label="Remove Card",style=filled,fillcolor=plum,URL="\ref STEP_DISCOVER_REMOVE_CARD"];
//!		node_STEP_DISCOVER_COMPLETION [label="Completion",style=filled,fillcolor=plum,URL="\ref STEP_DISCOVER_COMPLETION"];
//!		nodeStop [label="Return transaction result",shape="ellipse",style=filled];
//! 
//!		nodeStart -> node_STEP_DISCOVER_INITIAL [weight=100];
//!		node_STEP_DISCOVER_INITIAL -> node_STEP_DISCOVER_FINAL_SELECTION [weight=100];
//!		node_STEP_DISCOVER_FINAL_SELECTION -> node_STEP_DISCOVER_INITIATE_APPLI_PROCESSING [weight=100];
//!		node_STEP_DISCOVER_INITIATE_APPLI_PROCESSING -> node_STEP_DISCOVER_READ_APPLI_DATA [weight=100];
//!		node_STEP_DISCOVER_READ_APPLI_DATA -> node_STEP_DISCOVER_APPLI_VERSION_NB_CHECKING [weight=100];
//!		node_STEP_DISCOVER_APPLI_VERSION_NB_CHECKING -> node_STEP_DISCOVER_REMOVE_CARD [weight=100];
//!		node_STEP_DISCOVER_REMOVE_CARD -> node_STEP_DISCOVER_COMPLETION [weight=1];
//!		node_STEP_DISCOVER_COMPLETION -> nodeStop [weight=100];
//!	}
//! \enddot
//! @}



//! \addtogroup DiscoverOverview
//! @{
//! <h2>Introduction</h2><br>
//! The Discover kernel provides the payment application with an interface to perform Discover contactless transactions. It is fully compliant 
//! with the <i>Discover Network RF Contactless Specification - Supplement Guide For Functional Portion, Version 2.10, 13th June 2008</i>.
//! The Discover contactless transactions are magnetic stripe based transactions.<br>
//!
//! The kernel supports the following features :
//!	- Full supports of Discover V1.0 and V2.0 contactless cards.
//!	- Track 1 and Track 2 seeding.
//! 
//! <h2>Performances requirements</h2><br>
//! There are currently no Discover transaction time requirements.
//! 
//! <h2>Additional information</h2><br>
//! The Discover kernel performs the transaction but it does not manage :
//!	- The graphical user interface : This is the role of your application to perform the GUI. It allows better customisation.
//!	- The Discover parameters : All the parameters (supported AID, etc) are exclusively managed by the custom application itself.
//!	When a transaction is to be performed, this is the role of your application to provide the correct data to the kernel to perform the transaction.
//!	There is no persistent data within the Discover kernel itself. After each transaction, the Discover kernel shall be completely cleared.
//!	- The exception file : The exception file checking is performed by the custom application after the contactless transaction is complete (it allows you to have your own exception file format).
//!	If the card PAN is found within the exception file, the custom application must process the transaction outcome accordingly.
//! 
//!	<br><br>
//! <table cellspacing="5" bgcolor="#FFCCCC" bordercolordark="green" bordercolorlight="yellow">
//! <tr><td>
//! It is <b>mandatory</b> to call the \ref Discover_Clear() function after each transaction has been completed. This will clear the current transaction data and ensure the subsequent transaction can be performed correctly.
//! </td></tr>
//! </table>
//! 
//! @}



//! \addtogroup DiscoverCustomisationProcess
//! @{
//! \details It is possible for an application to be called back during the transaction process to make some customisation and interact with the transaction flow.
//! For example, it might be necessary during the DISCOVER transaction to indicate card has been correctly read (GUI). 
//! The Discover customisation will allow you to perform any processing you need that is not specified by the Discover specification.
//! <br><br>
//! <table cellspacing="5" bgcolor="#FFCCCC" bordercolordark="green" bordercolorlight="yellow">
//! <tr><td>
//! <b>Warning</b> : Using this function during the contactless session will adversely impact contactless 
//! transaction time. It is therefore recommended that this function is not used during the contactless session 
//! unless mandated by local requirements. Note that using this function outside the contactless session (e.g. STEP_DISCOVER_REMOVE_CARD)
//! will not impact the contactless transaction time.
//! </td></tr>
//! </table>
//! 
//! <h2>How to be called to perform customisation on a transaction step</h2><br>
//! To call back an application for customisation, the Discover kernel shall have the following information :
//!	- The application identifier to call.
//!	- The application service to use.
//!	- A bit field indicating which step the application wishes to customise.
//!
//! All of this information is provided to the Discover kernel using the \ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM tag. 
//! This tag contains a \ref T_KERNEL_TRANSACTION_FLOW_CUSTOM structure.
//! The Discover kernel will call the application for customisation after the step to customise has been executed.
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
//! ADD_STEP_CUSTOM(STEP_DISCOVER_REMOVE_CARD, sTransactionFlowCustom.pucStepCustom); // To do GUI when card has been read
//! 
//! // Add the structure into the shared buffer to be sent to the Discover kernel to perform the transaction
//! cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
//! if (cr != STATUS_SHARED_EXCHANGE_OK)
//! {
//! 	// An error occurred when adding the tag in the shared buffer
//! 	// ...
//! }
//! 
//! // Other processing to prepare data for Discover transaction
//! // ...
//! 
//! // Call the Discover kernel to perform the transaction (Discover_DoTransaction() function) with the shared buffer containing all the necessary data 
//! // To perform the transaction, including TAG_KERNEL_PAYMENT_FLOW_CUSTOM tag.
//! // ...
//! \endcode
//! 
//! \note As described in the example before, it is strongly recommended to customise the following Discover transaction step :
//!	- \ref STEP_DISCOVER_REMOVE_CARD to indicate the card has been read and can be removed for a Discover transaction.
//! 
//! 
//! <b>How to perform the customisation ?</b><br>
//! When the \ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM tag is provided (with all the correct information and if the application type and service identifier are correct),
//! the DISCOVER kernel will call you back for customisation.
//! 
//! \note For every customised step :
//!	- It is mandatory to clear data provided by the kernel from the shared buffer (after having read the necessary data provided by the kernel of course).
//! - It is mandatory to return \ref KERNEL_STATUS_CONTINUE to the customisation service.
//!
//! The function to be called when the customisation service is called by the Discover kernel shall have the following format :
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
//! 		case (STEP_DISCOVER_REMOVE_CARD):
//! 			// Card can be remove, do GUI
//! 			// ...
//! 			// Clear the shared buffer before returning to the kernel
//! 			GTL_SharedExchange_ClearEx (pDataStuct, FALSE);
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
//! 
//! @}



//! \addtogroup DiscoverProprietaryTags
//! @{
//! At present there is no requirement for the custom application to define any Discover proprietary tags. If, in the future, there 
//! is a requirment for proprietary Discover tags the following interface can be used...
//!
//! The Discover kernel allows you to define a certain number of proprietary tags. It allows answering some specific field needs.
//! This section describes how to define these tags to make them known by the Discover kernel. 
//! 
//! The proprietary tags are defined using the \ref TAG_KERNEL_PROPRIETARY_TAGS tag. When this tag is sent to the Discover kernel, 
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
//! // We consider that pDataStruct is the shared buffer used to send data to the Discover kernel
//! cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_KERNEL_PROPRIETARY_TAGS, sizeof(pProprietaryTags), pProprietaryTags);
//! if (cr != STATUS_SHARED_EXCHANGE_OK)
//! {
//! 	// An error occurred
//! 	// ...
//! }
//!
//! // When performing the transaction, tags DF01, DF02 and DF03 will be known by the Discover kernel, and they will be stored ...
//! // ...
//! 
//! \endcode
//! 
//! \note This tag (if necessary) shall be sent to the Discover kernel in the \ref Discover_DoTransaction() function. As all other tags, this 
//! one is not persistent. It means it shall be sent on every transaction where the proprietary tags are necessary.

//! @}
