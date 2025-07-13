/**
 * \file	EntryPoint_ErrorCodes.h
 * \brief	This describes all the Error Codes that Entry Point can return.
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

#define ERR_EP_NO_TAG						(0xFFFFFFFF)	/*!< Indicates there is no concerned tag fo rthe provided error. */

//! \addtogroup EntryPointErrorCodes
//! @{

#define ERR_EP_000001						(0x07000001)	/*!< Entry Point error, __EntryPoint_PreConditions_UnpredictableNumberGeneration, An error occured when generating an unpredictable number. */
#define ERR_EP_000002						(0x07000002)	/*!< Entry Point error, __EntryPoint_PreConditions_ExtractNecessaryData, During the data extraction for pre condition, the tag check failed (bad length, or bad coding). */
#define ERR_EP_000003						(0x07000003)	/*!< Entry Point error, __EntryPoint_PreConditions_ExtractNecessaryData, During the data extraction for pre condition, the tag is unknown by Entry Point. */
#define ERR_EP_000004						(0x07000004)	/*!< Entry Point error, __EntryPoint_PreConditions_ExtractNecessaryData, During the data extraction for pre condition, a parsing error occured with the input provided data. */
#define ERR_EP_000005						(0x07000005)	/*!< Entry Point error, EntryPoint_PreConditions_CheckMandatoryDataPresence, a mandatory data is missing (transaction amount). */
#define ERR_EP_000006						(0x07000006)	/*!< Entry Point error, EntryPoint_PreConditions_CheckMandatoryDataPresence, a mandatory data is missing (unpredictable number). */
#define ERR_EP_000007						(0x07000007)	/*!< Entry Point error, EntryPoint_PreConditions_OutputDataSet, There is not enough memory to fill the output structure with all the data. */
#define ERR_EP_000008						(0x07000008)	/*!< Entry Point error, __EntryPoint_PreConditions_ExtractNecessaryData, During the data extraction for pre condition, a tag is not expected (it is ignored). */
#define ERR_EP_000009						(0x07000009)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, An unexpected tag in the TAG_EP_AID_INFORMATION is present. This one is ignored. */
#define ERR_EP_00000A						(0x0700000A)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, A tag provided in the TAG_EP_AID_INFORMATION is incorrect. */
#define ERR_EP_00000B						(0x0700000B)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, A tag provided in the TAG_EP_AID_INFORMATION is unknown (this one is ignored). */
#define ERR_EP_00000C						(0x0700000C)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, A tag provided in the TAG_EP_AID_INFORMATION is incorrect. Current pre processing structure is cleared. */
#define ERR_EP_00000D						(0x0700000D)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, TTQ is missing as the AID is configured for Visa kernel (TTQ is mandatory for Visa kernel). */
#define ERR_EP_00000E						(0x0700000E)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, A mandatory data in TAG_EP_AID_INFORMATION is missing : TAG_EP_AID_OPTIONS. Current pre processing structure element is cleared. */
#define ERR_EP_00000F						(0x0700000F)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, A mandatory data in TAG_EP_AID_INFORMATION is missing : TAG_EMV_AID_TERMINAL. Current pre processing structure element is cleared. */
#define ERR_EP_000010						(0x07000010)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, A mandatory data in TAG_EP_AID_INFORMATION is missing : TAG_EP_KERNEL_TO_USE. Current pre processing structure element is cleared. */
#define ERR_EP_000011						(0x07000011)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, An error occured when parsing the TAG_EP_AID_INFORMATION content. */
#define ERR_EP_000012						(0x07000012)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, Pre processing structure size needs to be increase, there is not enough memory to create new element. */
#define ERR_EP_000013						(0x07000013)	/*!< Entry Point error, EntryPoint_PreProcessing_Manage, Pre procssing provided data (in the input data structure) do not correctly parse. */
#define ERR_EP_000014						(0x07000014)	/*!< Entry Point error, EntryPoint_PreProcessing_Manage, Pre processing is requested but pre conditions data is missing (not performed ?). */
#define ERR_EP_000015						(0x07000015)	/*!< Entry Point error, EntryPoint_PreProcessing_Manage, an error occured when parsing TAG_EP_AID_INFORMATION content. */
#define ERR_EP_000016						(0x07000016)	/*!< Entry Point error, EntryPoint_PreProcessing_Manage, There is no allowed AID after pre processing step. */
#define ERR_EP_000017						(0x07000017)	/*!< Entry Point error, EntryPoint_PreProcessing_GetResults, There is no available pre processing element. */
#define ERR_EP_000018						(0x07000018)	/*!< Entry Point error, EntryPoint_PreProcessing_GetResults, There is not enough memory to create the temporary memory structure. */
#define ERR_EP_000019						(0x07000019)	/*!< Entry Point error, EntryPoint_PreProcessing_GetResults, There is not enough memory to create the output structure to store all the pre processing results. */
#define ERR_EP_00001A						(0x0700001A)	/*!< Entry Point error, EntryPoint_PreProcessing_OutputDataSet, There is no enough memory to add the TAG_EP_NUMBER_OF_ALLOWED_AID in the output data structure. */
#define ERR_EP_00001B						(0x0700001B)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_AddElementToCandidateList, Cannot allocate a new candidate list element due to lack of memory. */
#define ERR_EP_00001C						(0x0700001C)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_CheckAndStore, The concerned tag is redundant within the card response. */
#define ERR_EP_00001D						(0x0700001D)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_CheckAndStore, The concerned tag is not valid (incorrect length or value encoding). */
#define ERR_EP_00001E						(0x0700001E)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_CandidateListInit, An error occured when trying to init the candidate list. */
#define ERR_EP_00001F						(0x0700001F)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciTemplateChecking, Parsing error during FCI template analysis. */
#define ERR_EP_000020						(0x07000020)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciTemplateChecking, Tag is not 0x6F (impossible as it shall be 0x6F). */
#define ERR_EP_000021						(0x07000021)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciTemplateChecking, The tag check failed during the FCI template analysis. */
#define ERR_EP_000022						(0x07000022)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciTemplateChecking, The DF Name provided in the FCI template is not correct. */
#define ERR_EP_000023						(0x07000023)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciTemplateChecking, The FCI proprietary tempplate provided in the FCI template is not correct. */
#define ERR_EP_000024						(0x07000024)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciTemplateChecking, The tag is not expected in the FCI template, ignore it. */
#define ERR_EP_000025						(0x07000025)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciTemplateChecking, A parsing error occured on the card response (extracting data from FCI template). */
#define ERR_EP_000026						(0x07000026)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciProprietaryTemplateChecking, The TAG_EMV_FCI_PROPRIETARY_TEMPLATE is missing. */
#define ERR_EP_000027						(0x07000027)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciProprietaryTemplateChecking, The TAG_EMV_FCI_ISSUER_DISCRET_DATA returned in the FCI proprietary template is not crrectly formatted. */
#define ERR_EP_000028						(0x07000028)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciProprietaryTemplateChecking, The tag is not expected in the FCI proprietary template, ignore it. */
#define ERR_EP_000029						(0x07000029)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciProprietaryTemplateChecking, A parsing error occured on the card response (extracting data from FCI proprietary template). */
#define ERR_EP_00002A						(0x0700002A)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_ParsePPSERecordElt, ADF has an incorrect format, ignore the Directory Entry (as specified in EP 5.4.3.7). */
#define ERR_EP_00002B						(0x0700002B)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_ParsePPSERecordElt, ADF is redundant in the Directory Entry. */
#define ERR_EP_00002C						(0x0700002C)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_ParsePPSERecordElt, API check failed (format error or redundant). */
#define ERR_EP_00002D						(0x0700002D)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_ParsePPSERecordElt, Application Label check failed (format error or redundant). */
#define ERR_EP_00002E						(0x0700002E)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_ParsePPSERecordElt, CACT check failed (format error or redundant). */
#define ERR_EP_00002F						(0x0700002F)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_ParsePPSERecordElt, Unexpected tag in the Directory Entry, this one is ignored. */
#define ERR_EP_000030						(0x07000030)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_ParsePPSERecordElt, Parsing error of the template 0x61 */
#define ERR_EP_000031						(0x07000031)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_AddToCandidateListLegacy, Unable to add new element in the candidate list. */
#define ERR_EP_000032						(0x07000032)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_AddToCandidateListEmvco, Unable to add new element in the candidate list. */
#define ERR_EP_000033						(0x07000033)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_StateSelectWithPPSE, An error occured during the extraction of the FCI template or FCI proprietary template and the data located into. */
#define ERR_EP_000034						(0x07000034)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_StateSelectWithPPSE, A mandatory icc data is missing (0xBF0C or 0x84). */
#define ERR_EP_000035						(0x07000035)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_StateSelectWithPPSE, The DF name (2SYS.PAY.DDF31) is not the same on the card. */
#define ERR_EP_000036						(0x07000036)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_StateSelectWithPPSE, Several applications are supported by the card and API is absent for previous application, so PPSE is failed. */
#define ERR_EP_000037						(0x07000037)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_StateSelectWithPPSE, Cannot add element in the candidate list because no enough memory */
#define ERR_EP_000038						(0x07000038)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_StateSelectWithPPSE, The ADF is not present, or is present but has not a correct format, so ignore it and check next directory entry. */
#define ERR_EP_000039						(0x07000039)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_StateSelectWithPPSE, An error occured in the template. */
#define ERR_EP_00003A						(0x0700003A)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_StateSelectWithPPSE, Discretionary Data empty (no application template (0x61)). */
#define ERR_EP_00003B						(0x0700003B)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_StateSelectWithPPSE, Error during FCI Discretionary template parsing. */
#define ERR_EP_00003C						(0x0700003C)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_StateSelectWithPPSE, Unknown PPSE step (internal automator). */
#define ERR_EP_00003D						(0x0700003D)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseResponseAnalysis, PPSE response is not correctly formatted (padding outside the template, or incorrect length). */
#define ERR_EP_00003E						(0x0700003E)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseResponseAnalysis, An error occured during the PPSE processing. */
#define ERR_EP_00003F						(0x0700003F)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_Ppse, Card response analysis failed. */
#define ERR_EP_000040						(0x07000040)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_Ppse, Card is blocked (SW = 0x6A81). */
#define ERR_EP_000041						(0x07000041)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_Ppse, Application is blocked (SW = 0x6283). */
#define ERR_EP_000042						(0x07000042)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_Ppse, Card does not support PPSE (SW = 0x6A82). */
#define ERR_EP_000043						(0x07000043)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_Ppse, Unexpected Status Word. */
#define ERR_EP_000044						(0x07000044)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_Ppse, No card answer from the card. */
#define ERR_EP_000045						(0x07000045)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_Ppse, Cannot initialise the candidate list. */
#define ERR_EP_000046						(0x07000046)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_Ppse, There is no matching AID in the candidate list. */
#define ERR_EP_000047						(0x07000047)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_FinalSelect, No card answer from the card to final SELECT. */
#define ERR_EP_000048						(0x07000048)	/*!< Entry Point error, EntryPoint_ApplicationSelection_Manage, Final SELECT fails. */
#define ERR_EP_000049						(0x07000049)	/*!< Entry Point error, EntryPoint_ApplicationSelection_Manage, PPSE fails. */
#define ERR_EP_00004A						(0x0700004A)	/*!< Entry Point error, EntryPoint_ApplicationSelection_GetPpseResponse, Not enough memory to store the PPSE response in the structure. */
#define ERR_EP_00004B						(0x0700004B)	/*!< Entry Point error, EntryPoint_ApplicationSelection_GetPpseResponse, No available PPSE response. */
#define ERR_EP_00004C						(0x0700004C)	/*!< Entry Point error, EntryPoint_ApplicationSelection_GetFinalSelectResponse, Not enough memory to store the pre processing result in the structure. */
#define ERR_EP_00004D						(0x0700004D)	/*!< Entry Point error, EntryPoint_ApplicationSelection_GetFinalSelectResponse, No available Final SELECT response. */
#define ERR_EP_00004E						(0x0700004E)	/*!< Entry Point error, EntryPoint_ApplicationSelection_GetCandidateListElements, There is not enough memory to add element in the local structure. */
#define ERR_EP_00004F						(0x0700004F)	/*!< Entry Point error, EntryPoint_ApplicationSelection_GetCandidateListElements, There is not enough memory to store TAG_EP_CANDIDATE_LIST_ELEMENT tag in the output structure. */
#define ERR_EP_000050						(0x07000050)	/*!< Entry Point error, EntryPoint_ApplicationSelection_GetCandidateListElements, There is not enough memory to create the temporary element. */
#define ERR_EP_000051						(0x07000051)	/*!< Entry Point error, EntryPoint_ApplicationSelection_GetCandidateListElements, No available element in the candidate list. */
#define ERR_EP_000052						(0x07000052)	/*!< Entry Point error, EntryPoint_ApplicationSelection_ExternalFinalSelect, Missing mandatory data (TAG_EMV_AID_TERMINAL). */
#define ERR_EP_000053						(0x07000053)	/*!< Entry Point error, EntryPoint_ApplicationSelection_RemoveAndSelect, Final SELECT fails. */
#define ERR_EP_000054						(0x07000054)	/*!< Entry Point error, EntryPoint_ApplicationSelection_RemoveAndSelect, No more available AID. */
#define ERR_EP_000055						(0x07000055)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, A mandatory data in TAG_EP_AID_INFORMATION is missing : TAG_TERMINAL_APPLICATION_TYPE. Current pre processing structure element is cleared. */
#define ERR_EP_000056						(0x07000056)	/*!< Entry Point error, EntryPoint_ApplicationSelection_GetCandidateListElements, An error occured when adding the number of candidate AID in the shared exchange buffer. */
#define ERR_EP_000057						(0x07000057)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_Ppse, Contactless application selection is not allowed as the is no available AID for Entry Point. */
#define ERR_EP_000058						(0x07000058)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_ParsePPSERecordElt, There is a missing mandatory parameter within the Directory Entry : ADF Name (AID). */
#define ERR_EP_000059						(0x07000059)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_ParsePPSERecordElt, Tag that has a zero length shall be considered as not present (in Directory Entry 0x61)(tag is provided). */
#define ERR_EP_00005A						(0x0700005A)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciTemplateChecking, Tag that has a zero length shall be considered as not present (in FCI template 0x6F)(tag is provided). */
#define ERR_EP_00005B						(0x0700005B)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_PpseFciProprietaryTemplateChecking, Tag that has a zero length shall be considered as not present (in FCI proprietary template 0xA5)(tag is provided). */
#define ERR_EP_00005C						(0x0700005C)	/*!< Entry Point error, EntryPoint_Version_Get, An error occured when adding the TAG_EP_APPLICATION_NAME tag in the shared exchange buffer. */
#define ERR_EP_00005D						(0x0700005D)	/*!< Entry Point error, EntryPoint_Version_Get, An error occured when adding the TAG_EP_APPLICATION_IDENTIFIER tag in the shared exchange buffer. */
#define ERR_EP_00005E						(0x0700005E)	/*!< Entry Point error, EntryPoint_Version_Get, An error occured when adding the TAG_EP_APPLICATION_CRC tag in the shared exchange buffer. */
#define ERR_EP_00005F						(0x0700005F)	/*!< Entry Point error, EntryPoint_Version_Get, There is not enough memory to add the Entry Point information. */
#define ERR_EP_000060						(0x07000060)	/*!< Entry Point error, EntryPoint_Version_Get, An internal error occured. */
#define ERR_EP_000061						(0x07000061)	/*!< Entry Point error, __EntryPoint_ApplicationSelection_ParsePPSERecordElt, Card Kernel ID check failed (format error or redundant). */
#define ERR_EP_000062						(0x07000062)	/*!< Entry Point error, __EntryPoint_PreProcessing_ParseAidInformation, If the B1b7 of AID OPTION is set and both "Associated kernel" and "Kernel To Use" are not present, then at leat one of them is missing. */

//! @}
