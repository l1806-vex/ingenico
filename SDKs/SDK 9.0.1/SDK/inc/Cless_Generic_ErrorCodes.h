/**
 * \file	Cless_Generic_ErrorCodes.h
 * \brief	This describes all the Error Codes that TPass DLL can return.
 *
 *
 * \author	Ingenico
 * \author	Copyright (c) 2008 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/


/////////////////////////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////////////////////////

#define ERR_CLESS_NO_TAG						(0xFFFFFFFF)	/*!< Indicates there is no concerned tag for the provided error. */

//! \addtogroup ClessErrorCodes
//! @{

#define ERR_CLESS_000001						(0x0A000001)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_SendAndStoreSelect, An error occured when adding the Command/Response element in the list. */
#define ERR_CLESS_000002						(0x0A000002)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_SendAndStoreSelect, An error occured when trying to build or to send the command to the card (bad parameter or no card answer). */ 
#define ERR_CLESS_000003						(0x0A000003)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ExtractAndParseFciTemplate, SELECT response is not correctly formatted (padding outside the template, or incorrect length). */
#define ERR_CLESS_000004						(0x0A000004)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ExtractAndParseFciTemplate, A mandatory icc data is missing : TAG_FCI_TEMPLATE. Tag found is not the expected one. */
#define ERR_CLESS_000005						(0x0A000005)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ExtractAndParseFciTemplate, FCI Template has bad format */
#define ERR_CLESS_000006						(0x0A000006)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ExtractAndParseFciTemplate, TAG_EMV_DF_NAME has a bad format (within 0x6F). */
#define ERR_CLESS_000007						(0x0A000007)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ExtractAndParseFciTemplate, TAG_EMV_FCI_PROPRIETARY_TEMPLATE has a bad format (within 0x6F). */
#define ERR_CLESS_000008						(0x0A000008)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ExtractAndParseFciTemplate, The terminal shall ignore tags that are not expected in the FCI (concerned tag is provided). */
#define ERR_CLESS_000009						(0x0A000009)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ExtractAndParseFciTemplate, A parsing error occured on the card response (extracting data from FCI template). */
#define ERR_CLESS_00000A						(0x0A00000A)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ExtractAndParseFciTemplate, Missing mandatory data in the SELECT response (in the 6F template) : TAG_EMV_DF_NAME. */
#define ERR_CLESS_00000B						(0x0A00000B)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ExtractAndParseFciTemplate, Missing mandatory data in the SELECT response (in the 6F template) : TAG_EMV_FCI_PROPRIETARY_TEMPLATE. */
#define ERR_CLESS_00000C						(0x0A00000C)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseFciProprietaryTemplate, TAG_EMV_APPLICATION_LABEL is redundant or has a bad format within the 0xA5 template, ignore it (as it is not a critical data, as specified in the specification). */
#define ERR_CLESS_00000D						(0x0A00000D)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseFciProprietaryTemplate, TAG_EMV_APPLI_PRIORITY_INDICATOR is redundant or has a bad format within the 0xA5 template, discard card response (as there is an error on a critical card data). */
#define ERR_CLESS_00000E						(0x0A00000E)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseFciProprietaryTemplate, TAG_EMV_PDOL is redundant or has a bad format within the 0xA5 template, discard card response (as there is an error on a critical card data). */
#define ERR_CLESS_00000F						(0x0A00000F)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseFciProprietaryTemplate, TAG_EMV_APPLICATION_LABEL is redundant or has a bad format within the 0xA5 template, ignore it (as it is not a critical data, as specified in the specification). */
#define ERR_CLESS_000010						(0x0A000010)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseFciProprietaryTemplate, TAG_EMV_ISSUER_CODE_TABLE_INDEX is redundant or has a bad format within the 0xA5 template, ignore it (as it is not a critical data, as specified in the specification). */
#define ERR_CLESS_000011						(0x0A000011)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseFciProprietaryTemplate, TAG_EMV_APPLI_PREFERED_NAME is redundant or has a bad format within the 0xA5 template, ignore it (as it is not a critical data, as specified in the specification). */
#define ERR_CLESS_000012						(0x0A000012)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseFciProprietaryTemplate, TAG_EMV_FCI_ISSUER_DISCRET_DATA is redundant or has a bad format within the 0xA5 template, discard card response (as there is an error on a critical card data). */
#define ERR_CLESS_000013						(0x0A000013)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseFciProprietaryTemplate, The terminal shall ignore tags that are not expected in the FCI (concerned tag is provided). */
#define ERR_CLESS_000014						(0x0A000014)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseFciProprietaryTemplate, A parsing error occured on the card response (extracting data from FCI template). */
#define ERR_CLESS_000015						(0x0A000015)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseFciIssuerDiscretionaryData, FCI Issuer Discretionnary Data parsing error. */
#define ERR_CLESS_000016						(0x0A000016)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_CheckAndStore, The concerned tag is redundant within the card. */
#define ERR_CLESS_000017						(0x0A000017)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_CheckAndStore, The concerned tag has a bad format. */
#define ERR_CLESS_000018						(0x0A000018)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseAndCheckCardResponse, Parsing FCI Issuer Discretionary Data, continue with next terminal supported AID. */
#define ERR_CLESS_000019						(0x0A000019)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseAndCheckCardResponse, Parsing FCI Proprietary Template failed, continue with next terminal supported AID. */
#define ERR_CLESS_00001A						(0x0A00001A)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_ParseAndCheckCardResponse, Parsing FCI Template failed, continue with next terminal supported AID. */
#define ERR_CLESS_00001B						(0x0A00001B)	/*!< Cless error, Cless_AS_ApplicationSelection.c, Cless_AS_ListOfAidMethod, The candidate element cannot be added to the candidate list because of either a lack of memory or either due to an internal error (bad parameter). */
#define ERR_CLESS_00001C						(0x0A00001C)	/*!< Cless error, Cless_AS_ApplicationSelection.c, Cless_AS_ListOfAidMethod, The card is blocked (card returned 0x6A81 to the SELECT command). */
#define ERR_CLESS_00001D						(0x0A00001D)	/*!< Cless error, Cless_AS_ApplicationSelection.c, Cless_AS_ListOfAidMethod, An error occured when Sending command to card. */
#define ERR_CLESS_00001E						(0x0A00001E)	/*!< Cless error, __Cless_LOA_ParseFciProprietaryTemplate, Tag has a zero length within the FCI Proprietary Template, it shall be ignored. */
#define ERR_CLESS_00001F						(0x0A00001F)	/*!< Cless error, __Cless_LOA_ExtractAndParseFciTemplate, Tag has a zero length within the FCI Template, it shall be ignored. */

//! \cond NOT_DOCUMENTED
#define ERR_CLESS_000020						(0x0A000020)	/*!< Cless error,  */
//! \endcond

#define ERR_CLESS_000021						(0x0A000021)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_RemoveAidFromCandidateList, Error when removing AID from the candidate list (one of the provided parameters to the functionis not correct : invalid candidate list pointer or invalid index). */
#define ERR_CLESS_000022						(0x0A000022)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_RemoveAidFromCandidateList, Error when removing first AID from the candidate list (one of the provided parameters to the functionis not correct : invalid candidate list pointer or invalid index). */
#define ERR_CLESS_000023						(0x0A000023)	/*!< Cless error, Cless_AS_ApplicationSelection.c, Cless_AS_RemoveAidFromCandidateList, Cannot remove any AID from the candidate list because this one is empty. */
#define ERR_CLESS_000024						(0x0A000024)	/*!< Cless error, Cless_AS_ApplicationSelection.c, Cless_AS_ListOfAidMethod, There is no matching AID in the candidate list (this one is empty). */

//! \cond NOT_DOCUMENTED
#define ERR_CLESS_000025						(0x0A000025)	/*!< Cless error,  */
#define ERR_CLESS_000026						(0x0A000026)	/*!< Cless error,  */
#define ERR_CLESS_000027						(0x0A000027)	/*!< Cless error,  */
#define ERR_CLESS_000028						(0x0A000028)	/*!< Cless error,  */
//! \endcond

#define ERR_CLESS_000029						(0x0A000029)	/*!< Cless error, Cless_Generic_Commands.c, Cless_Generic_Commands_SendSelectCommand, A communication error occured with the card (card removed for example) or contactless driver is not opened. */
#define ERR_CLESS_00002A						(0x0A00002A)	/*!< Cless error, Cless_Generic_Commands.c, Cless_Generic_Commands_SendSelectCommand, An error occured when building the SELECT command. */
#define ERR_CLESS_00002B						(0x0A00002B)	/*!< Cless error, Cless_AS_Commands.c, Cless_AS_Commands_SendGenericCommand, The card does not answer to the SELECT command (communication error, card removed for example). */
#define ERR_CLESS_00002C						(0x0A00002C)	/*!< Cless error, Cless_AS_Commands.c, Cless_AS_Commands_SendGenericCommand, Command cannot be sent because contactless driver is not opened. */
#define ERR_CLESS_00002D						(0x0A00002D)	/*!< Cless error, Cless_AS_ApplicationSelection.c, Cless_AS_ListOfAidMethod, An error occured during Final Application Selection of AID having the highest priority. */

//! \cond NOT_DOCUMENTED
#define ERR_CLESS_00002E						(0x0A00002E)	/*!< Cless error,  */ 
//! \endcond

#define ERR_CLESS_00002F						(0x0A00002F)	/*!< Cless error, Cless_AS_ApplicationSelection.c, __Cless_AS_FinalSelectionProcessing, An error occured during Final Application Selection. */
#define ERR_CLESS_000030						(0x0A000030)	/*!< Cless error, Cless_AS_ApplicationSelection.c, Cless_AS_RemoveAidFromCandidateList, An error occured during the final selection process (remove AID and then SELECT next). */
#define ERR_CLESS_000031						(0x0A000031)	/*!< Cless error, Cless_AS_ApplicationSelection.c, Cless_AS_RemoveAidFromCandidateList, An internal error occured when trying to remove an AID from the candidate list (status code already updated). */
#define ERR_CLESS_000032						(0x0A000032)	/*!< Cless error, Cless_APDU_ApduMethod, __Cless_APDU_Method_SendAndCheck, Error when sending the APDU to the card. */
#define ERR_CLESS_000033						(0x0A000033)	/*!< Cless error, Cless_APDU_ApduMethod, __Cless_APDU_Method_SendAndCheck, Error when adding response structure to the list */
#define ERR_CLESS_000034						(0x0A000034)	/*!< Cless error, Cless_APDU_ApduMethod, Cless_APDU_Method_Process, An error occured when trying to send command to the card response storage error). */
#define ERR_CLESS_000035						(0x0A000035)	/*!< Cless error, Cless_APDU_ApduMethod, Cless_APDU_Method_Process, No APDU crietria matched. */
#define ERR_CLESS_000036						(0x0A000036)	/*!< Cless error, Cless_APDU_ApduMethod, Cless_APDU_Method_Process, Method state indicates process is already completed. */
#define ERR_CLESS_000037						(0x0A000037)	/*!< Cless error, Cless_APDU_Data, APDU List structure init failed. */
#define ERR_CLESS_000038						(0x0A000038)	/*!< Cless error, Cless_APDU_Data, APDU Before Response List structure init failed. */
#define ERR_CLESS_000039						(0x0A000039)	/*!< Cless error, Cless_APDU_Data, APDU After Response List structure init failed. */

//! \cond NOT_DOCUMENTED
#define ERR_CLESS_00003A						(0x0A00003A)	/*!< Cless error,  */
#define ERR_CLESS_00003B						(0x0A00003B)	/*!< Cless error,  */
#define ERR_CLESS_00003C						(0x0A00003C)	/*!< Cless error,  */
#define ERR_CLESS_00003D						(0x0A00003D)	/*!< Cless error,  */
#define ERR_CLESS_00003E						(0x0A00003E)	/*!< Cless error,  */
#define ERR_CLESS_00003F						(0x0A00003F)	/*!< Cless error,  */
//! \endcond

#define ERR_CLESS_000040						(0x0A000040)	/*!< Cless error, Cless_ExplicitSelection_LoadData, Initialisation error */
#define ERR_CLESS_000041						(0x0A000041)	/*!< Cless error, Cless_ExplicitSelection_LoadData, Invalid tag length */
#define ERR_CLESS_000042						(0x0A000042)	/*!< Cless error, Cless_ExplicitSelection_LoadData, Invalid tag value */
#define ERR_CLESS_000043						(0x0A000043)	/*!< Cless error, Cless_ExplicitSelection_LoadData, Duplicated tag */
#define ERR_CLESS_000044						(0x0A000044)	/*!< Cless error, Cless_ExplicitSelection_LoadData, Missing tag */
#define ERR_CLESS_000045						(0x0A000045)	/*!< Cless error, Cless_Generic_GetPreProcessingResults, Invalid input TlvTree */
#define ERR_CLESS_000046						(0x0A000046)	/*!< Cless error, Cless_Generic_LoadData.c, __Cless_AS_AnalyseApdu(), at least, one of TAG_GENERIC_APDU_EXPECTED_STATUS_WORD or TAG_GENERIC_APDU_EXPECTED_CARD_RESPONSE must be present. */
#define ERR_CLESS_000047						(0x0A000047)	/*!< Cless error, Cless_Generic_LoadData.c, __Cless_AS_AnalyseApdu(), if TAG_GENERIC_APDU_EXPECTED_CARD_RESPONSE and TAG_GENERIC_APDU_RESPONSE_MASK are given, they must have the same length. */
#define ERR_CLESS_000048						(0x0A000048)	/*!< Cless error, Cless_Generic_Selection.c no method allows to select AID */

//! \cond NOT_DOCUMENTED
#define ERR_CLESS_000049						(0x0A000049)	/*!< Cless error,  */
#define ERR_CLESS_00004A						(0x0A00004A)	/*!< Cless error,  */
#define ERR_CLESS_00004B						(0x0A00004B)	/*!< Cless error,  */
#define ERR_CLESS_00004C						(0x0A00004C)	/*!< Cless error,  */
#define ERR_CLESS_00004D						(0x0A00004D)	/*!< Cless error,  */
#define ERR_CLESS_00004E						(0x0A00004E)	/*!< Cless error,  */
#define ERR_CLESS_00004F						(0x0A00004F)	/*!< Cless error,  */
#define ERR_CLESS_000050						(0x0A000050)	/*!< Cless error,  */
#define ERR_CLESS_000051						(0x0A000051)	/*!< Cless error,  */
#define ERR_CLESS_000052						(0x0A000052)	/*!< Cless error,  */
#define ERR_CLESS_000053						(0x0A000053)	/*!< Cless error,  */
#define ERR_CLESS_000054						(0x0A000054)	/*!< Cless error,  */
#define ERR_CLESS_000055						(0x0A000055)	/*!< Cless error,  */
//! \endcond

#define ERR_CLESS_000056						(0xA0000056)	/*!< Cless error, Cless_Internal_LoadData.c, __Cless_Internal_LoadData, Redundant transaction currency exponent. */
#define ERR_CLESS_000057						(0xA0000057)	/*!< Cless error, Cless_Internal_LoadData.c, __Cless_Internal_LoadData, Invalid transaction currency exponent. */
#define ERR_CLESS_000058						(0xA0000058)	/*!< Cless error, Cless_LOA_ListOfAidMethod.c, An error occurred when getting the pre processing results from EP. */
#define ERR_CLESS_000059						(0xA0000059)	/*!< Cless error, Cless_LOA_ListOfAidMethod.c, An error occurred when initialising the shared buffer to get the pre processing results. */
#define ERR_CLESS_00005A						(0xA000005A)	/*!< Cless error, Cless_LOA_ListOfAidMethod.c, There could have been some AID, but all of them was not allowed because of EP results. */

//! @}
