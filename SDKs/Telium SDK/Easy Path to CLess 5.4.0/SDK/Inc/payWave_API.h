/**
 * \file     payWave_API.h
 * \brief    This describes the payWave kernel API.
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


/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global definition //////////////////////////////////////////

//! \addtogroup payWaveTransactionFlowSteps
//! @{

#define STEP_PAYWAVE_INITIAL                            0x00                                 /*!< Step : initial process management. */
#define STEP_PAYWAVE_FINAL_APPLICATION_SELECTION        0x01                                 /*!< Final card selection. */
#define STEP_PAYWAVE_APPLICATION_BLOCKED                0x02                                 /*!< Step if application is blocked. */
#define STEP_PAYWAVE_CARD_BLOCKED                       0x03                                 /*!< Step if card is blocked. */
#define STEP_PAYWAVE_SELECT_ANOTHER_APPLICATION         0x04                                 /*!< Step if an another application must be selected. */
#define STEP_PAYWAVE_INITIATE_APPLICATION_PROCESSING    0x05                                 /*!< Initiate Application processing. */

#define STEP_PAYWAVE_MSD_READ_APPLICATION_DATA          0x06                                 /*!< Read card data. */
#define STEP_PAYWAVE_MSD_MANDATORY_DATA_CHECKING        0x07                                 /*!< Card MSD Mandatory Data Checking. */
#define STEP_PAYWAVE_MSD_COMPLETION                     0x08                                 /*!< Card MSD Completion. */
#define STEP_PAYWAVE_MSD_REMOVE_CARD                    0x09                                 /*!< Card MSD Remove Card. */

#define STEP_PAYWAVE_QVSDC_READ_APPLICATION_DATA        0x0A                                 /*!< Card QVSDC Read Application data. */
#define STEP_PAYWAVE_QVSDC_REMOVE_CARD                  0x0B                                 /*!< Card QVSDC Remove Card. */
#define STEP_PAYWAVE_QVSDC_MANDATORY_DATA_CHECKING      0x0C                                 /*!< Card QVSDC Check Mandatory Data. */
#define STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL           0x0D                                 /*!< Card QVSDC Black List control. */
#define STEP_PAYWAVE_QVSDC_POST_PROCESSING              0x0E                                 /*!< Card QVSDC Post Processing. */
#define STEP_PAYWAVE_QVSDC_GET_CERTIFICATE              0x0F                                 /*!< Card QVSDC Get Certificate. */
#define STEP_PAYWAVE_QVSDC_ODA_PROCESSING               0x10                                 /*!< Card QVSDC ODA Processing. */
#define STEP_PAYWAVE_QVSDC_FDDA_PROCESSING              0x11                                 /*!< Card QVSDC DDA Processing. */
#define STEP_PAYWAVE_QVSDC_SDA_PROCESSING               0x12                                 /*!< Card QVSDC SDA Processing. */
#define STEP_PAYWAVE_QVSDC_COMPLETION                   0x13                                 /*!< Card QVSDC Completion. */
#define STEP_PAYWAVE_QVSDC_COMPLETION_WITH_ERROR        0x14                                 /*!< Card Completion when an error occured. */

#define STEP_PAYWAVE_READ_TRANSACTION_LOG               0x15                                 /*!< Transaction Log Management. */
#define STEP_PAYWAVE_ISSUER_SCRIPT_PROCESSING           0x16                                 /*!< Issuer Script Processing. */

#define STEP_PAYWAVE_STOP                               0x1F                                 /*!< Last transaction step used for release memory, POFF, traces ... */

//! @}


//! \addtogroup payWaveStatusCodes
//! @{
#define PAYWAVE_STATUS_OK_MSD                           0x0301                               /*!< the function is correctly executed and MSD card has been found. */
#define PAYWAVE_STATUS_OK_QVSDC                         0x0302                               /*!< the function is correctly executed and QVSDC card has been found. */
#define PAYWAVE_STATUS_OK_FDDA                          0x0303                               /*!< the function is correctly executed and FDDA/DDA step must be executed. */
#define PAYWAVE_STATUS_OK_SDA                           0x0304                               /*!< the function is correctly executed and SDA step must be executed. */
//! @}

//! \addtogroup payWaveTimeMeasure
//! @{
#define PAYWAVE_TIME_TYPE_CARD                          0x80000000                           /*!< Time measure is relative to card access. */
#define PAYWAVE_TIME_TYPE_FUNCTION                      0x40000000                           /*!< Time measure is relative to code execution. */
#define PAYWAVE_TIME_TYPE_SYSTEM                        0x20000000                           /*!< Time measure is relative to system + manager + ... code execution. */

#define PAYWAVE_TIME_PRELIMINARY                        PAYWAVE_TIME_TYPE_FUNCTION+1         /*!< Time measure for Preliminary function execution */
#define PAYWAVE_TIME_PRELIMINARY_END                    PAYWAVE_TIME_TYPE_FUNCTION+2         /*!< Time measure end for Preliminary function execution */
#define PAYWAVE_TIME_TXN                                PAYWAVE_TIME_TYPE_FUNCTION+3         /*!< Time measure for transaction function execution */
#define PAYWAVE_TIME_TXN_END                            PAYWAVE_TIME_TYPE_FUNCTION+4         /*!< Time measure end for Transaction function execution */
#define PAYWAVE_TIME_TXN_STEP                           PAYWAVE_TIME_TYPE_FUNCTION+5         /*!< Time measure for transaction function execution */
#define PAYWAVE_TIME_TXN_STEP_END                       PAYWAVE_TIME_TYPE_FUNCTION+6         /*!< Time measure end for Transaction function execution */
#define PAYWAVE_TIME_DATA                               PAYWAVE_TIME_TYPE_FUNCTION+7         /*!< Time measure for LoadTag and LoadOneTag execution */
#define PAYWAVE_TIME_DATA_END                           PAYWAVE_TIME_TYPE_FUNCTION+8         /*!< Time measure for LoadTag and LoadOneTag execution */
#define PAYWAVE_TIME_GET_DATA                           PAYWAVE_TIME_TYPE_FUNCTION+9         /*!< Time measure for data obtention function execution */
#define PAYWAVE_TIME_GET_DATA_END                       PAYWAVE_TIME_TYPE_FUNCTION+10        /*!< Time measure end for data obtention function execution */
#define PAYWAVE_TIME_GET_ALL_DATA                       PAYWAVE_TIME_TYPE_FUNCTION+11        /*!< Time measure for obtain all data function execution */
#define PAYWAVE_TIME_GET_ALL_DATA_END                   PAYWAVE_TIME_TYPE_FUNCTION+12        /*!< Time measure for obtain all data function execution */
#define PAYWAVE_TIME_GPO_CMD                            PAYWAVE_TIME_TYPE_FUNCTION+13        /*!< Time measure for GetProcessingOption card command */
#define PAYWAVE_TIME_GPO_CMD_END                        PAYWAVE_TIME_TYPE_FUNCTION+14        /*!< Time measure for GetProcessingOption card command */
#define PAYWAVE_TIME_RAD_CMD                            PAYWAVE_TIME_TYPE_FUNCTION+15        /*!< Time measure for ReadApplicationData card command */
#define PAYWAVE_TIME_RAD_CMD_END                        PAYWAVE_TIME_TYPE_FUNCTION+16        /*!< Time measure for ReadApplicationData card command */
#define PAYWAVE_TIME_SERVICE_CALL                       PAYWAVE_TIME_TYPE_FUNCTION+17        /*!< Time measure for a service call to custom */
#define PAYWAVE_TIME_SERVICE_CALL_END                   PAYWAVE_TIME_TYPE_FUNCTION+18        /*!< Time measure for a service call to custom */
#define PAYWAVE_TIME_ISSUER_SCRIPT                      PAYWAVE_TIME_TYPE_FUNCTION+19        /*!< Time measure for a Issuer script update */
#define PAYWAVE_TIME_ISSUER_SCRIPT_END                  PAYWAVE_TIME_TYPE_FUNCTION+20        /*!< Time measure for a Issuer script update */
#define PAYWAVE_TIME_ISSUER_AUTHENTICATION              PAYWAVE_TIME_TYPE_FUNCTION+21        /*!< Time measure for a Issuer Authentication */
#define PAYWAVE_TIME_ISSUER_AUTHENTICATION_END          PAYWAVE_TIME_TYPE_FUNCTION+22        /*!< Time measure for a Issuer Authentication */
#define PAYWAVE_TIME_AFTER_TXN                          PAYWAVE_TIME_TYPE_FUNCTION+23        /*!< Time measure for after transaction function execution (Load Script)*/
#define PAYWAVE_TIME_AFTER_TXN_END                      PAYWAVE_TIME_TYPE_FUNCTION+24        /*!< Time measure end for after Transaction function execution (Load Script) */
#define PAYWAVE_TIME_SELECT_AID_ISP                     PAYWAVE_TIME_TYPE_FUNCTION+25        /*!< Time measure for select AID before an Issuer Script Processing */
#define PAYWAVE_TIME_SELECT_AID_ISP_END                 PAYWAVE_TIME_TYPE_FUNCTION+26        /*!< Time measure end for select AID before an Issuer Script Processing */
#define PAYWAVE_TIME_GET_DATA_TR_LOG                    PAYWAVE_TIME_TYPE_FUNCTION+27        /*!< Time measure for GetData card command used to obtain the Lof Format data element */
#define PAYWAVE_TIME_GET_DATA_TR_LOG_END                PAYWAVE_TIME_TYPE_FUNCTION+28        /*!< Time measure end for GetData card command used to obtain the Lof Format data element */
#define PAYWAVE_TIME_READ_TR_LOG	                    PAYWAVE_TIME_TYPE_FUNCTION+29        /*!< Time measure for Read transaction log Data */
#define PAYWAVE_TIME_READ_TR_LOG_END 	        	    PAYWAVE_TIME_TYPE_FUNCTION+30        /*!< Time measure end for for Read transaction log Data */
/*!< Time measure end for obtain all data function execution */
//! @}


//! \addtogroup payWaveErrorDefinition
//! @{
#define ERR_PAYWAVE_NO_TAG                              0xFFFFFFFF                           /*!< Indicates there is no concerned tag for the provided error. */

#define ERR_PAYWAVE_BASE                                0x13000000                           /*!< Error Code : warning, the first index of error code depend on each kernel... see documentation */
                                                                                             /*!< Error number        File                    Function */
#define ERR_PAYWAVE_000000                              ERR_PAYWAVE_BASE+0x000000            /*!< payWave error N 00, payWave_Entry.c         payWave_Entry_LoadTags(), a problem occurs on a service to load a tag */
#define ERR_PAYWAVE_000001                              ERR_PAYWAVE_BASE+0x000001            /*!< payWave error N 01, payWave_Entry.c         payWave_Entry_LoadTags(), a problem occurs on a service to reset a tag */
#define ERR_PAYWAVE_000002                              ERR_PAYWAVE_BASE+0x000002            /*!< payWave error N 02, payWave_Entry.c         payWave_Entry_LoadTags(), GTL_SharedExchange_GetNext() end with problem */
#define ERR_PAYWAVE_000003                              ERR_PAYWAVE_BASE+0x000003            /*!< payWave error N 03, payWave_Entry.c         __payWave_Entry_Store_One_Tag(), a problem occurs on a service to reset a tag */
#define ERR_PAYWAVE_000004                              ERR_PAYWAVE_BASE+0x000004            /*!< payWave error N 04, payWave_Entry.c         __payWave_Entry_Get_Kernel_Infos(), error on GTL_SharedExchange_AddTag for \ref TAG_KERNEL_APPLICATION_NAME */
#define ERR_PAYWAVE_000005                              ERR_PAYWAVE_BASE+0x000005            /*!< payWave error N 05, payWave_Entry.c         __payWave_Entry_Get_Kernel_Infos(), error on GTL_SharedExchange_AddTag for \ref TAG_KERNEL_APPLICATION_IDENT */
#define ERR_PAYWAVE_000006                              ERR_PAYWAVE_BASE+0x000006            /*!< payWave error N 06, payWave_Entry.c         __payWave_Entry_Get_Kernel_Infos(), error on GTL_SharedExchange_AddTag for \ref TAG_KERNEL_APPLICATION_CRC */
#define ERR_PAYWAVE_000007                              ERR_PAYWAVE_BASE+0x000007            /*!< payWave error N 07, payWave_Entry.c         __payWave_Entry_Get_Kernel_Infos(), error on GTL_SharedExchange_AddTag, not enougth space */
#define ERR_PAYWAVE_000008                              ERR_PAYWAVE_BASE+0x000008            /*!< payWave error N 08, payWave_Entry.c         __payWave_Entry_Get_Kernel_Infos(), unknown error on GTL_SharedExchange_AddTag */
#define ERR_PAYWAVE_000009                              ERR_PAYWAVE_BASE+0x000009            /*!< payWave error N 09, payWave_Entry.c         __payWave_Entry_Get_Data(), error on GTL_SharedExchange_AddTag */
#define ERR_PAYWAVE_00000A                              ERR_PAYWAVE_BASE+0x00000A            /*!< payWave error N 0A, payWave_Entry.c         __payWave_Entry_Get_Data(), not managed error on GTL_Database_GetTag */
#define ERR_PAYWAVE_00000B                              ERR_PAYWAVE_BASE+0x00000B            /*!< payWave error N 0B, payWave_Entry.c         __payWave_Entry_Get_All_Data(), error on GTL_SharedExchange_AddTag */
#define ERR_PAYWAVE_00000C                              ERR_PAYWAVE_BASE+0x00000C            /*!< payWave error N 0C, payWave_Time.c          payWave_Time_Init(), error on GTL_DataStorage_GetTagWithIndex for \ref TAG_KERNEL_DEBUG_TIME */
#define ERR_PAYWAVE_00000D                              ERR_PAYWAVE_BASE+0x00000D            /*!< payWave error N 0D, payWave_Time.c          payWave_Time_Init(), error on GTL_DataStorage_AddTagWithIndex for \ref TAG_KERNEL_DEBUG_TIME */
#define ERR_PAYWAVE_00000E                              ERR_PAYWAVE_BASE+0x00000E            /*!< payWave error N 0E, payWave_ttq.c           payWave_Is_TTQ_created(), error on GTL_DataStorage_GetTagWithIndex for \ref TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS */
#define ERR_PAYWAVE_00000F                              ERR_PAYWAVE_BASE+0x00000F            /*!< payWave error N 0F, payWave_TxnInitial.c    Function_TxnState_InitialStep(), if \ref TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS tag isn't created */
#define ERR_PAYWAVE_000010                              ERR_PAYWAVE_BASE+0x000010            /*!< payWave error N 10, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse(), error on GTL_DataStorage_GetTagWithIndex for \ref TAG_EP_FINAL_SELECT_STATUS_WORD  */
#define ERR_PAYWAVE_000011                              ERR_PAYWAVE_BASE+0x000011            /*!< payWave error N 11, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse(), error on GTL_DataStorage_GetTagWithIndex for \ref TAG_EP_FINAL_SELECT_RESPONSE */
#define ERR_PAYWAVE_000012                              ERR_PAYWAVE_BASE+0x000012            /*!< payWave error N 12, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_AnalyseAndParseFinalSelectResponse(), final status word is different from 0x90 0x00 */
#define ERR_PAYWAVE_000013                              ERR_PAYWAVE_BASE+0x000013            /*!< payWave error N 13, payWave_TxnFinalSel.c   __payWave_Common_CheckAndStore(), error on GTL_DataStorage_AddTagCtrltag tag is Redundant */
#define ERR_PAYWAVE_000014                              ERR_PAYWAVE_BASE+0x000014            /*!< payWave error N 14, payWave_TxnFinalSel.c   __payWave_Common_CheckAndStore(), unknown error on GTL_DataStorage_AddTagCtrl */
#define ERR_PAYWAVE_000015                              ERR_PAYWAVE_BASE+0x000015            /*!< payWave error N 15, payWave_TxnFinalSel.c   __payWave_Common_CheckAndStore(), error on GTL_DataStorage_AddTagCtrl not enought space */
#define ERR_PAYWAVE_000016                              ERR_PAYWAVE_BASE+0x000016            /*!< payWave error N 16, payWave_TxnFinalSel.c   __payWave_Common_CheckAndStore(), unknown error on GTL_DataStorage_AddTagCtrl */
#define ERR_PAYWAVE_000017                              ERR_PAYWAVE_BASE+0x000017            /*!< payWave error N 17, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ExtractAndParseFciTemplate(), error on GTL_BerTlvDecode_ParseTlv format error (bad FCI or padding outside template) */
#define ERR_PAYWAVE_000018                              ERR_PAYWAVE_BASE+0x000018            /*!< payWave error N 18, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ExtractAndParseFciTemplate(), error on GTL_BerTlvDecode_ParseTlv format error (Tag is not FCI Template) */
#define ERR_PAYWAVE_000019                              ERR_PAYWAVE_BASE+0x000019            /*!< payWave error N 19, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ExtractAndParseFciTemplate(), error on GTL_DataStorage_AddTagWithIndex format error (FCI Template has bad format) */
#define ERR_PAYWAVE_00001A                              ERR_PAYWAVE_BASE+0x00001A            /*!< payWave error N 1A, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ExtractAndParseFciTemplate(), tag is present but length is 0 */
#define ERR_PAYWAVE_00001B                              ERR_PAYWAVE_BASE+0x00001B            /*!< payWave error N 1B, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ExtractAndParseFciTemplate(), The terminal shall ignore tags that are not expected in the FCI */
#define ERR_PAYWAVE_00001C                              ERR_PAYWAVE_BASE+0x00001C            /*!< payWave error N 1C, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ExtractAndParseFciTemplate(), FCI Template parsing error */
#define ERR_PAYWAVE_00001D                              ERR_PAYWAVE_BASE+0x00001D            /*!< payWave error N 1D, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ExtractAndParseFciTemplate(), \ref TAG_EMV_DF_NAME not present */
#define ERR_PAYWAVE_00001E                              ERR_PAYWAVE_BASE+0x00001E            /*!< payWave error N 1E, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ExtractAndParseFciTemplate(), \ref TAG_EMV_FCI_PROPRIETARY_TEMPLATE not present */
#define ERR_PAYWAVE_00001F                              ERR_PAYWAVE_BASE+0x00001F            /*!< payWave error N 1F, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ParseFciProprietaryTemplate(), proprietary template is missing in base */
#define ERR_PAYWAVE_000020                              ERR_PAYWAVE_BASE+0x000020            /*!< payWave error N 20, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ParseFciProprietaryTemplate(), The terminal shall ignore tags that are not expected in the FCI Proprietary Template */
#define ERR_PAYWAVE_000021                              ERR_PAYWAVE_BASE+0x000021            /*!< payWave error N 21, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ParseFciProprietaryTemplate(), FCI Template parsing error */
#define ERR_PAYWAVE_000022                              ERR_PAYWAVE_BASE+0x000022            /*!< payWave error N 22, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ParseFciIssuerDiscretionaryData(), This function cannot be called if FCI Issuer Deiscretionary Data Template is not in database (shall be checked before calling this function) */
#define ERR_PAYWAVE_000023                              ERR_PAYWAVE_BASE+0x000023            /*!< payWave error N 23, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_ParseFciIssuerDiscretionaryData(), FCI Issuer Discretionnary Data parsing error */
#define ERR_PAYWAVE_000024                              ERR_PAYWAVE_BASE+0x000024            /*!< payWave error N 24, payWave_TxnFinalSel.c   __payWave_Txn_FinalSelect_LanguageSelection(), An error occured when adding tag \ref TAG_KERNEL_SELECTED_PREFERED_LANGUAGE in the database */
#define ERR_PAYWAVE_000025                              ERR_PAYWAVE_BASE+0x000025            /*!< payWave error N 25, payWave_TxnIniProc.c    __payWave_isTTQ_PresentInPDOL(), \ref TAG_EMV_PDOL tag error */
#define ERR_PAYWAVE_000026                              ERR_PAYWAVE_BASE+0x000026            /*!< payWave error N 26, payWave_TxnIniProc.c    __payWave_isTTQ_PresentInPDOL(), \ref TAG_EMV_PDOL tag not found */
#define ERR_PAYWAVE_000027                              ERR_PAYWAVE_BASE+0x000027            /*!< payWave error N 27, payWave_TxnIniProc.c    __payWave_isTTQ_PresentInPDOL(), If the PDOL is not present in the card response or if Tag '9F66' (Terminal Transaction Qualifiers) is not present in the PDOL, */
#define ERR_PAYWAVE_000028                              ERR_PAYWAVE_BASE+0x000028            /*!< payWave error N 28, payWave_TxnIniProc.c    __payWave_determine_card_type(), \ref TAG_EMV_AIP tag error */
#define ERR_PAYWAVE_000029                              ERR_PAYWAVE_BASE+0x000029            /*!< payWave error N 29, payWave_TxnIniProc.c    __payWave_determine_card_type(), \ref TAG_EMV_AIP tag not found */
#define ERR_PAYWAVE_00002A                              ERR_PAYWAVE_BASE+0x00002A            /*!< payWave error N 2A, payWave_TxnIniProc.c    __payWave_determine_card_type(), MSD and QVSDC are managed by terminal */
#define ERR_PAYWAVE_00002B                              ERR_PAYWAVE_BASE+0x00002B            /*!< payWave error N 2B, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), EmvLib_Dol_Build error  */
#define ERR_PAYWAVE_00002C                              ERR_PAYWAVE_BASE+0x00002C            /*!< payWave error N 2C, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), \ref TAG_EMV_PDOL tag not found */
#define ERR_PAYWAVE_00002D                              ERR_PAYWAVE_BASE+0x00002D            /*!< payWave error N 2D, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), error on \ref TAG_EMV_PDOL */
#define ERR_PAYWAVE_00002E                              ERR_PAYWAVE_BASE+0x00002E            /*!< payWave error N 2E, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), error on EmvLib_BuildCommand_GetProcessingOptions */
#define ERR_PAYWAVE_00002F                              ERR_PAYWAVE_BASE+0x00002F            /*!< payWave error N 2F, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), CLESS_Apdu error for GPO command */
#define ERR_PAYWAVE_000030                              ERR_PAYWAVE_BASE+0x000030            /*!< payWave error N 30, payWave_TxnIniProc.c    __payWave_TxnIniProc_Initiate_Application_Processing(), GTL_DataStorage_AddTagWithIndex error on \ref TAG_KERNEL_LAST_APDU_AND_SW */
#define ERR_PAYWAVE_000031                              ERR_PAYWAVE_BASE+0x000031            /*!< payWave error N 31, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), GTL_BerTlvDecode_Init error */
#define ERR_PAYWAVE_000032                              ERR_PAYWAVE_BASE+0x000032            /*!< payWave error N 32, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), GTL_BerTlvDecode_ParseTlv error on GPO card response */
#define ERR_PAYWAVE_000033                              ERR_PAYWAVE_BASE+0x000033            /*!< payWave error N 33, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), GTL_BerTlvDecode_Init error */
#define ERR_PAYWAVE_000034                              ERR_PAYWAVE_BASE+0x000034            /*!< payWave error N 34, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), GTL_Database_CheckTag error tag given in GPO card  */
#define ERR_PAYWAVE_000035                              ERR_PAYWAVE_BASE+0x000035            /*!< payWave error N 35, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), redundant tag between tag send by card in GPO response and Database */
#define ERR_PAYWAVE_000036                              ERR_PAYWAVE_BASE+0x000036            /*!< payWave error N 36, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), GTL_Database_AddTag error with tag send by card in GPO response */
#define ERR_PAYWAVE_000037                              ERR_PAYWAVE_BASE+0x000037            /*!< payWave error N 37, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), \ref TAG_EMV_AFL tag sent by card have length = 0 : AFL has no entrie */
#define ERR_PAYWAVE_000038                              ERR_PAYWAVE_BASE+0x000038            /*!< payWave error N 38, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), GTL_BerTlvDecode_ParseTlv error on GPO card response */
#define ERR_PAYWAVE_000039                              ERR_PAYWAVE_BASE+0x000039            /*!< payWave error N 39, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), GTL_Database_AddTagEx error on \ref TAG_EMV_AIP tag in format 1 GPO card response */
                                                                                             /*!< payWave error N 39, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), \ref TAG_EMV_AFL tag not correctly formatted */
#define ERR_PAYWAVE_00003A                              ERR_PAYWAVE_BASE+0x00003A            /*!< payWave error N 3A, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), GTL_Database_AddTagEx error on \ref TAG_EMV_AFL tag in format 1 GPO card response */
#define ERR_PAYWAVE_00003B                              ERR_PAYWAVE_BASE+0x00003B            /*!< payWave error N 3B, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), GTL_DataStorage_AddTagWithIndex error on \ref TAG_PAYWAVE_GPO_FORMAT_USED tag in format 1 GPO card response */
#define ERR_PAYWAVE_00003C                              ERR_PAYWAVE_BASE+0x00003C            /*!< payWave error N 3C, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), unknown format type in GPO card response */
#define ERR_PAYWAVE_00003D                              ERR_PAYWAVE_BASE+0x00003D            /*!< payWave error N 3D, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), CLESS_Apdu card response to the GPO command is 0x69 0x85 */
#define ERR_PAYWAVE_00003E                              ERR_PAYWAVE_BASE+0x00003E            /*!< payWave error N 3E, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), CLESS_Apdu card response to the GPO command is 0x69 0x84 */
#define ERR_PAYWAVE_00003F                              ERR_PAYWAVE_BASE+0x00003F            /*!< payWave error N 3F, payWave_TxnIniProc.c    __payWave_Initiate_Application_Processing(), CLESS_Apdu card response to the GPO command is not managed 0xXX 0xXX */
#define ERR_PAYWAVE_000040                              ERR_PAYWAVE_BASE+0x000040            /*!< payWave error N 40, payWave_TxnIniProc.c    Function_TxnState_IniProcessing(), \ref TAG_PAYWAVE_QVSDC_NOT_ALLOWED not managed by database */
#define ERR_PAYWAVE_000041                              ERR_PAYWAVE_BASE+0x000041            /*!< payWave error N 41, payWave_TxnIniProc.c    Function_TxnState_IniProcessing(), qVSDC is not allowed or MSD, qVSDC and Contactless VSDC are not available */
#define ERR_PAYWAVE_000042                              ERR_PAYWAVE_BASE+0x000042            /*!< payWave error N 42, payWave_TxnIniProc.c    __payWave_SetSfiError(), \ref TAG_PAYWAVE_ERROR_SFI_AUTH not managed by database */
#define ERR_PAYWAVE_000043                              ERR_PAYWAVE_BASE+0x000043            /*!< payWave error N 43, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), EmvLib_BuildCommand_ReadRecord error */
#define ERR_PAYWAVE_000044                              ERR_PAYWAVE_BASE+0x000044            /*!< payWave error N 44, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), ReadRecord card command error */
#define ERR_PAYWAVE_000045                              ERR_PAYWAVE_BASE+0x000045            /*!< payWave error N 45, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), GTL_DataStorage_AddTagWithIndex error for \ref TAG_KERNEL_LAST_APDU_AND_SW tag */
#define ERR_PAYWAVE_000046                              ERR_PAYWAVE_BASE+0x000046            /*!< payWave error N 46, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), ReadRecord card response different from 0x90 0x00 */
#define ERR_PAYWAVE_000047                              ERR_PAYWAVE_BASE+0x000047            /*!< payWave error N 47, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), GTL_BerTlvDecode_Init error on ReadRecord card response. */
#define ERR_PAYWAVE_000048                              ERR_PAYWAVE_BASE+0x000048            /*!< payWave error N 48, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), bad ReadRecord response tag or length. */
#define ERR_PAYWAVE_000049                              ERR_PAYWAVE_BASE+0x000049            /*!< payWave error N 49, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), GTL_BerTlvDecode_ParseTlv error on ReadRecord card response */
#define ERR_PAYWAVE_00004A                              ERR_PAYWAVE_BASE+0x00004A            /*!< payWave error N 4A, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), GTL_BerTlvDecode_Init error */
#define ERR_PAYWAVE_00004B                              ERR_PAYWAVE_BASE+0x00004B            /*!< payWave error N 4B, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), GTL_Database_CheckTag error on a tag in the ReadRecord card response */
#define ERR_PAYWAVE_00004C                              ERR_PAYWAVE_BASE+0x00004C            /*!< payWave error N 4C, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), redundant tag between tag in the ReadRecord card response and Database */
#define ERR_PAYWAVE_00004D                              ERR_PAYWAVE_BASE+0x00004D            /*!< payWave error N 4D, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), GTL_Database_AddTag error for tag comming from the ReadRecord card response */
#define ERR_PAYWAVE_00004E                              ERR_PAYWAVE_BASE+0x00004E            /*!< payWave error N 4E, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), GTL_BerTlvDecode_ParseTlv error on the ReadRecord card response */
#define ERR_PAYWAVE_00004F                              ERR_PAYWAVE_BASE+0x00004F            /*!< payWave error N 4F, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), GTL_BerTlvDecode_Init error */
#define ERR_PAYWAVE_000050                              ERR_PAYWAVE_BASE+0x000050            /*!< payWave error N 50, payWave_TxnReadData.c   __payWave_Read_Application_Data_with_AFL(), bad sfi in ReadRecord card response */
#define ERR_PAYWAVE_000051                              ERR_PAYWAVE_BASE+0x000051            /*!< payWave error N 51, payWave_TxnReadData.c   Function_TxnState_ReadAppliData(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_AFL tag */
#define ERR_PAYWAVE_000052                              ERR_PAYWAVE_BASE+0x000052            /*!< payWave error N 52, payWave_TxnIniProc.c    EmvLib_Dol_IsTagInDol return INVALID_DATA */
#define ERR_PAYWAVE_000053                              ERR_PAYWAVE_BASE+0x000053            /*!< payWave error N 53, payWave_TxnMSDCheck.c   __payWave_MSD_check_mandatory_data_presence(), Check Mandatory Tag fails */
#define ERR_PAYWAVE_000054                              ERR_PAYWAVE_BASE+0x000054            /*!< payWave error N 54, payWave_TxnMSDCheck.c   __payWave_MSD_check_mandatory_data_presence(), Check Optionnals Tag fails */
#define ERR_PAYWAVE_000055                              ERR_PAYWAVE_BASE+0x000055            /*!< payWave error N 55, payWave_TxnMSDCheck.c   payWave_checkTrack2Validity(), GTL_DataStorage_GetTagWithIndex for \ref TAG_EMV_TRACK_2_EQU_DATA error */
#define ERR_PAYWAVE_000056                              ERR_PAYWAVE_BASE+0x000056            /*!< payWave error N 56, payWave_TxnMSDCheck.c   payWave_checkTrack2Validity(), GTL_DataStorage_GetTagWithIndex not found for \ref TAG_EMV_TRACK_2_EQU_DATA */
#define ERR_PAYWAVE_000057                              ERR_PAYWAVE_BASE+0x000057            /*!< payWave error N 57, payWave_TxnMSDCheck.c   payWave_checkTrack2Validity(), The PAN is too long or there is no separator 'D' */
#define ERR_PAYWAVE_000058                              ERR_PAYWAVE_BASE+0x000058            /*!< payWave error N 58, payWave_TxnMSDCheck.c   payWave_checkTrack2Validity(), Missing country code or bad country code format */
#define ERR_PAYWAVE_000059                              ERR_PAYWAVE_BASE+0x000059            /*!< payWave error N 59, payWave_TxnMSDCheck.c   payWave_checkTrack2Validity(), Error with the expiration date format */
#define ERR_PAYWAVE_00005A                              ERR_PAYWAVE_BASE+0x00005A            /*!< payWave error N 5A, payWave_TxnMSDCheck.c   payWave_checkTrack2Validity(), Bad month format */
#define ERR_PAYWAVE_00005B                              ERR_PAYWAVE_BASE+0x00005B            /*!< payWave error N 5B, payWave_TxnMSDCheck.c   payWave_checkTrack2Validity(), Bad service code format */
#define ERR_PAYWAVE_00005C                              ERR_PAYWAVE_BASE+0x00005C            /*!< payWave error N 5C, payWave_TxnMSDCheck.c   payWave_checkTrack2Validity(), Error with discretionnary data */
#define ERR_PAYWAVE_00005D                              ERR_PAYWAVE_BASE+0x00005D            /*!< payWave error N 5D, payWave_TxnMSDCheck.c   payWave_checkTrack2Validity(), error on Padding to F (only one F should occur, but accept several F) */
#define ERR_PAYWAVE_00005E                              ERR_PAYWAVE_BASE+0x00005E            /*!< payWave error N 5E, payWave_TxnMSDCheck.c   __payWave_MSD_create_track_2_original(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_TRACK_2_EQU_DATA tag */
#define ERR_PAYWAVE_00005F                              ERR_PAYWAVE_BASE+0x00005F            /*!< payWave error N 5F, payWave_TxnMSDCheck.c   __payWave_MSD_create_track_2_original(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_PAYWAVE_MAGSTRIPE_TRACK_2 tag */
#define ERR_PAYWAVE_000060                              ERR_PAYWAVE_BASE+0x000060            /*!< payWave error N 60, payWave_TxnMSDCheck.c   Function_TxnState_MSDDataCheck(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_PAYWAVE_GPO_FORMAT_USED tag */
#define ERR_PAYWAVE_000061                              ERR_PAYWAVE_BASE+0x000061            /*!< payWave error N 61, payWave_TxnMSDCheck.c   Function_TxnState_MSDDataCheck(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_ISSUER_APPLI_DATA tag */
#define ERR_PAYWAVE_000062                              ERR_PAYWAVE_BASE+0x000062            /*!< payWave error N 62, payWave_TxnMSDCheck.c   free */
#define ERR_PAYWAVE_000063                              ERR_PAYWAVE_BASE+0x000063            /*!< payWave error N 63, payWave_TxnMSDCheck.c   free */
#define ERR_PAYWAVE_000064                              ERR_PAYWAVE_BASE+0x000064            /*!< payWave error N 64, payWave_TxnMSDCheck.c   free */
#define ERR_PAYWAVE_000065                              ERR_PAYWAVE_BASE+0x000065            /*!< payWave error N 65, payWave_TxnMSDCheck.c   free */
#define ERR_PAYWAVE_000066                              ERR_PAYWAVE_BASE+0x000066            /*!< payWave error N 66, payWave_TxnCompl.c      Function_TxnState_MSDCompletion(), GTL_DataStorage_GetTagWithIndex error on tag from tag list to send */
#define ERR_PAYWAVE_000067                              ERR_PAYWAVE_BASE+0x000067            /*!< payWave error N 67, payWave_TxnCompl.c      Function_TxnState_MSDCompletion(), GTL_SharedExchange_AddTag error on tag from tag list to send */
#define ERR_PAYWAVE_000068                              ERR_PAYWAVE_BASE+0x000068            /*!< payWave error N 68, payWave_TxnCompl.c      free */
#define ERR_PAYWAVE_000069                              ERR_PAYWAVE_BASE+0x000069            /*!< payWave error N 69, payWave_TxnCompl.c      free */
#define ERR_PAYWAVE_00006A                              ERR_PAYWAVE_BASE+0x00006A            /*!< payWave error N 6A, payWave_TxnQVSDCCheck.c __payWave_QVSDC_check_mandatory_data_presence(), unknown transaction status code */
#define ERR_PAYWAVE_00006B                              ERR_PAYWAVE_BASE+0x00006B            /*!< payWave error N 6B, payWave_TxnQVSDCCheck.c __payWave_QVSDC_check_mandatory_data_presence(), Check MandatoryTag fails */
#define ERR_PAYWAVE_00006C                              ERR_PAYWAVE_BASE+0x00006C            /*!< payWave error N 6C, payWave_TxnQVSDCCheck.c __payWave_QVSDC_check_mandatory_data_presence(), Check OptionnalTag fails */
#define ERR_PAYWAVE_00006D                              ERR_PAYWAVE_BASE+0x00006D            /*!< payWave error N 6D, payWave_TxnQVSDCCheck.c Function_TxnState_QVSDCDataCheck(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_ISSUER_APPLI_DATA tag */
#define ERR_PAYWAVE_00006E                              ERR_PAYWAVE_BASE+0x00006E            /*!< payWave error N 6E, payWave_TxnQVSDCCheck.c free */
#define ERR_PAYWAVE_00006F                              ERR_PAYWAVE_BASE+0x00006F            /*!< payWave error N 6F, payWave_TxnQVSDCCheck.c free */
#define ERR_PAYWAVE_000070                              ERR_PAYWAVE_BASE+0x000070            /*!< payWave error N 70, payWave_TxnQVSDCCheck.c free */
#define ERR_PAYWAVE_000071                              ERR_PAYWAVE_BASE+0x000071            /*!< payWave error N 71, payWave_TxnQVSDCPProc.c __payWave_get_Track2_information(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_APPLI_PAN tag */
#define ERR_PAYWAVE_000072                              ERR_PAYWAVE_BASE+0x000072            /*!< payWave error N 72, payWave_TxnQVSDCPProc.c __payWave_get_Track2_information(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_APPLI_EXPIRATION_DATE tag  */
#define ERR_PAYWAVE_000073                              ERR_PAYWAVE_BASE+0x000073            /*!< payWave error N 73, payWave_TxnQVSDCPProc.c __payWave_get_Track2_information(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_TRACK_2_EQU_DATA tag when expiration date or PAN must be extracted from TRACK2 */
#define ERR_PAYWAVE_000074                              ERR_PAYWAVE_BASE+0x000074            /*!< payWave error N 74, payWave_TxnQVSDCPProc.c __payWave_get_Track2_information(), GTL_DataStorage_GetTagWithIndex not found with \ref TAG_EMV_TRACK_2_EQU_DATA tag when expiration date or PAN must be extracted from TRACK2 */
#define ERR_PAYWAVE_000075                              ERR_PAYWAVE_BASE+0x000075            /*!< payWave error N 75, payWave_TxnQVSDCPProc.c __payWave_get_Track2_information(), invalid track 2 format : \ref TAG_EMV_TRACK_2_EQU_DATA tag when expiration date or PAN must be extracted from TRACK2 */
#define ERR_PAYWAVE_000076                              ERR_PAYWAVE_BASE+0x000076            /*!< payWave error N 76, payWave_TxnQVSDCPProc.c __payWave_get_Track2_information(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_EMV_APPLI_PAN tag */
#define ERR_PAYWAVE_000077                              ERR_PAYWAVE_BASE+0x000077            /*!< payWave error N 77, payWave_TxnQVSDCPProc.c __payWave_get_Track2_information(), invalid track 2 format : \ref TAG_EMV_TRACK_2_EQU_DATA tag when expiration date or PAN must be extracted from TRACK2 */
#define ERR_PAYWAVE_000078                              ERR_PAYWAVE_BASE+0x000078            /*!< payWave error N 78, payWave_TxnQVSDCPProc.c __payWave_get_Track2_information(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_EMV_APPLI_EXPIRATION_DATE tag */
#define ERR_PAYWAVE_000079                              ERR_PAYWAVE_BASE+0x000079            /*!< payWave error N 79, payWave_TxnQVSDCPProc.c __payWave_qVSDC_Execute_PIN_Online_CVM(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_KERNEL_ONLINE_PIN_REQUESTED tag */
#define ERR_PAYWAVE_00007A                              ERR_PAYWAVE_BASE+0x00007A            /*!< payWave error N 7A, payWave_TxnQVSDCPProc.c __payWave_qVSDC_Execute_Signature_CVM(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_KERNEL_SIGNATURE_REQUESTED tag */
#define ERR_PAYWAVE_00007B                              ERR_PAYWAVE_BASE+0x00007B            /*!< payWave error N 7B, payWave_TxnQVSDCPProc.c __payWave_qVSDC_CVM_processing(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_PAYWAVE_CARD_TRANSACTION_QUALIFIERS tag */
#define ERR_PAYWAVE_00007C                              ERR_PAYWAVE_BASE+0x00007C            /*!< payWave error N 7C, payWave_TxnQVSDCPProc.c free */
#define ERR_PAYWAVE_00007D                              ERR_PAYWAVE_BASE+0x00007D            /*!< payWave error N 7D, payWave_TxnQVSDCPProc.c __payWave_isExpirationDateLessThanCurrentDate(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_TRANSACTION_DATE tag */
#define ERR_PAYWAVE_00007E                              ERR_PAYWAVE_BASE+0x00007E            /*!< payWave error N 7E, payWave_TxnQVSDCPProc.c __payWave_isExpirationDateLessThanCurrentDate(), Card expired */
#define ERR_PAYWAVE_00007F                              ERR_PAYWAVE_BASE+0x00007F            /*!< payWave error N 7F, payWave_TxnQVSDCPProc.c __payWave_isNotPANinBlackList(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_KERNEL_PAN_IN_BLACK_LIST */
#define ERR_PAYWAVE_000080                              ERR_PAYWAVE_BASE+0x000080            /*!< payWave error N 80, payWave_TxnQVSDCPProc.c __payWave_isNotPANinBlackList(), Card in black list */
#define ERR_PAYWAVE_000081                              ERR_PAYWAVE_BASE+0x000081            /*!< payWave error N 81, payWave_TxnQVSDCPProc.c free */
#define ERR_PAYWAVE_000082                              ERR_PAYWAVE_BASE+0x000082            /*!< payWave error N 82, payWave_TxnQVSDCPProc.c Function_TxnState_QVSDCPostProc(), bad __payWave_qVSDC_offline_treatements state result for off-line-approuved treatment  */
#define ERR_PAYWAVE_000083                              ERR_PAYWAVE_BASE+0x000083            /*!< payWave error N 83, payWave_TxnQVSDCPProc.c Function_TxnState_QVSDCPostProc(), transaction state unknown */
#define ERR_PAYWAVE_000084                              ERR_PAYWAVE_BASE+0x000084            /*!< payWave error N 84, payWave_TxnQVSDCPProc.c free */
#define ERR_PAYWAVE_000085                              ERR_PAYWAVE_BASE+0x000085            /*!< payWave error N 85, payWave_TxnQVSDCBL.c    Function_TxnState_QVSDCBLControl(), */
#define ERR_PAYWAVE_000086                              ERR_PAYWAVE_BASE+0x000086            /*!< payWave error N 86, payWave_TxnQVSDCBL.c    Function_TxnState_QVSDCBLControl(), */
#define ERR_PAYWAVE_000087                              ERR_PAYWAVE_BASE+0x000087            /*!< payWave error N 87, payWave_TxnQVSDCBL.c    Function_TxnState_QVSDCBLControl(), */
#define ERR_PAYWAVE_000088                              ERR_PAYWAVE_BASE+0x000088            /*!< payWave error N 88, payWave_TxnQVSDCBL.c    Function_TxnState_QVSDCBLControl(), */
#define ERR_PAYWAVE_000089                              ERR_PAYWAVE_BASE+0x000089            /*!< payWave error N 89, payWave_TxnQVSDCCert.c  free */
#define ERR_PAYWAVE_00008A                              ERR_PAYWAVE_BASE+0x00008A            /*!< payWave error N 8A, payWave_TxnQVSDCCert.c  free */
#define ERR_PAYWAVE_00008B                              ERR_PAYWAVE_BASE+0x00008B            /*!< payWave error N 8B, payWave_TxnQVSDCCert.c  free */
#define ERR_PAYWAVE_00008C                              ERR_PAYWAVE_BASE+0x00008C            /*!< payWave error N 8C, payWave_TxnInitial.c    Function_TxnState_InitialStep(), GTL_DataStorage_AddTagWithIndex error with tag \ref TAG_KERNEL_CARD_TYPE. */
#define ERR_PAYWAVE_00008D                              ERR_PAYWAVE_BASE+0x00008D            /*!< payWave error N 8D, payWave_TxnQVSDCPProc.c payWave_qVSDC_ODA_OdaDataInit(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_PAYWAVE_ODA_INPUT_AUTHENTICATION_DATA tag. */
#define ERR_PAYWAVE_00008E                              ERR_PAYWAVE_BASE+0x00008E            /*!< payWave error N 8E, payWave_TxnQVSDCPProc.c payWave_qVSDC_ODA_OdaDataInit(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_EMV_CA_PUBLIC_KEY_INDEX_CARD tag. */
#define ERR_PAYWAVE_00008F                              ERR_PAYWAVE_BASE+0x00008F            /*!< payWave error N 8F, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_add_DDA_data_ddol(), GTL_Database_GetTag error for FDDA V00 mandatory tags. */
#define ERR_PAYWAVE_000090                              ERR_PAYWAVE_BASE+0x000090            /*!< payWave error N 90, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_add_DDA_data_ddol(), GTL_Database_GetTag error for FDDA V01 mandatory tags. */
#define ERR_PAYWAVE_000091                              ERR_PAYWAVE_BASE+0x000091            /*!< payWave error N 91, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_add_DDA_data_ddol(), FDDA version not managed. */
#define ERR_PAYWAVE_000092                              ERR_PAYWAVE_BASE+0x000092            /*!< payWave error N 92, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_way_if_fDDA_fails(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_PAYWAVE_CARD_TRANSACTION_QUALIFIERS tag. */
#define ERR_PAYWAVE_000093                              ERR_PAYWAVE_BASE+0x000093            /*!< payWave error N 93, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_is_fDDA_Supported(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_PAYWAVE_TERM_SUPPORTED_FDDA_VERSIONS tag. */
#define ERR_PAYWAVE_000094                              ERR_PAYWAVE_BASE+0x000094            /*!< payWave error N 94, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_Check_Mandatory_data_presence_fDDA(), Unknown fDDA version. */
#define ERR_PAYWAVE_000095                              ERR_PAYWAVE_BASE+0x000095            /*!< payWave error N 95, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_check_mandatory_data(), GTL_Database_GetTag error with ODA mandatory tags. */
#define ERR_PAYWAVE_000096                              ERR_PAYWAVE_BASE+0x000096            /*!< payWave error N 96, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_check_mandatory_data(), GTL_Database_GetTag not found with ODA mandatory tags. */
#define ERR_PAYWAVE_000097                              ERR_PAYWAVE_BASE+0x000097            /*!< payWave error N 97, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_check_mandatory_data(), mandatory tags not found for ODA process. */
#define ERR_PAYWAVE_000098                              ERR_PAYWAVE_BASE+0x000098            /*!< payWave error N 98, payWave_TxnQVSDCCert.c  __payWave_qVSDC_DDA_AddData(), oda_datas maximum buffer length has been reached. */
#define ERR_PAYWAVE_000099                              ERR_PAYWAVE_BASE+0x000099            /*!< payWave error N 99, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_sda_format_list(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_SDA_TAG_LIST tag. */
#define ERR_PAYWAVE_00009A                              ERR_PAYWAVE_BASE+0x00009A            /*!< payWave error N 9A, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_sda_format_list(), GTL_BerTlvDecode_Init error for SDA tag list. */
#define ERR_PAYWAVE_00009B                              ERR_PAYWAVE_BASE+0x00009B            /*!< payWave error N 9B, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_sda_format_list(), GTL_Database_GetTag error with tag supplied in \ref TAG_EMV_SDA_TAG_LIST list. */
#define ERR_PAYWAVE_00009C                              ERR_PAYWAVE_BASE+0x00009C            /*!< payWave error N 9C, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_sda_format_list(), GTL_BerTlv_IsTagConstructedObject said no about the tag supplied in \ref TAG_EMV_SDA_TAG_LIST list. */
#define ERR_PAYWAVE_00009D                              ERR_PAYWAVE_BASE+0x00009D            /*!< payWave error N 9D, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_sda_format_list(), if tag read in \ref TAG_EMV_SDA_TAG_LIST list is different from \ref TAG_EMV_AIP. */
#define ERR_PAYWAVE_00009E                              ERR_PAYWAVE_BASE+0x00009E            /*!< payWave error N 9E, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_sda_format_list(), GTL_BerTlvDecode_ParseTlv error on the \ref TAG_EMV_SDA_TAG_LIST.  */
#define ERR_PAYWAVE_00009F                              ERR_PAYWAVE_BASE+0x00009F            /*!< payWave error N 9F, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_retrieve_issuer_pub_key(), mandatory tag for retrieve issuer public key isn't stored. */
#define ERR_PAYWAVE_0000A0                              ERR_PAYWAVE_BASE+0x0000A0            /*!< payWave error N A0, payWave_TxnQVSDCCert.c  free. */
#define ERR_PAYWAVE_0000A1                              ERR_PAYWAVE_BASE+0x0000A1            /*!< payWave error N A1, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_retrieve_issuer_pub_key(), error on EmvLib_Oda_RetrieveIssuerPublicKey libEMV function. */
#define ERR_PAYWAVE_0000A2                              ERR_PAYWAVE_BASE+0x0000A2            /*!< payWave error N A2, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_retrieve_icc_pub_key(), mandatory tag for retrieve icc public key isn't stored. */
#define ERR_PAYWAVE_0000A3                              ERR_PAYWAVE_BASE+0x0000A3            /*!< payWave error N A3, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_retrieve_icc_pub_key(), error on EmvLib_Oda_RetrieveIccPublicKey libEMV function. */
#define ERR_PAYWAVE_0000A4                              ERR_PAYWAVE_BASE+0x0000A4            /*!< payWave error N A4, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_retrieve_icc_pub_key(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_KERNEL_ICC_RECOVERED_DATA tag. */
#define ERR_PAYWAVE_0000A5                              ERR_PAYWAVE_BASE+0x0000A5            /*!< payWave error N A5, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_retrieve_icc_pub_key(), Issuer algo indicator error. */
#define ERR_PAYWAVE_0000A6                              ERR_PAYWAVE_BASE+0x0000A6            /*!< payWave error N A6, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_dda_verif_signature(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_SIGNED_DYNAMIC_APPLI_DATA tag. */
#define ERR_PAYWAVE_0000A7                              ERR_PAYWAVE_BASE+0x0000A7            /*!< payWave error N A7, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_dda_verif_signature(), error on EmvLib_Oda_DdaSignatureVerification libEMV function. */
#define ERR_PAYWAVE_0000A8                              ERR_PAYWAVE_BASE+0x0000A8            /*!< payWave error N A8, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_dda_verif_signature(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_KERNEL_ICC_RECOVERED_DATA tag */
#define ERR_PAYWAVE_0000A9                              ERR_PAYWAVE_BASE+0x0000A9            /*!< payWave error N A9, payWave_TxnQVSDCCert.c  __payWave_qVSDC_oda_dda_verif_signature(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_EMV_ICC_DYNAMIC_NUMBER tag */
#define ERR_PAYWAVE_0000AA                              ERR_PAYWAVE_BASE+0x0000AA            /*!< payWave error N AA, payWave_TxnQVSDCCert.c  __payWave_sda_verif_signature(), \ref TAG_EMV_SIGNED_STATIC_APPLI_DATA data length and ICC public key length are different */
#define ERR_PAYWAVE_0000AB                              ERR_PAYWAVE_BASE+0x0000AB            /*!< payWave error N AB, payWave_TxnQVSDCCert.c  __payWave_sda_verif_signature(), mandatory tag for verif SDA signature is missing */
#define ERR_PAYWAVE_0000AC                              ERR_PAYWAVE_BASE+0x0000AC            /*!< payWave error N AC, payWave_TxnQVSDCCert.c  __payWave_sda_verif_signature(), error on EmvLib_Oda_SdaSignatureVerification libEMV function */
#define ERR_PAYWAVE_0000AD                              ERR_PAYWAVE_BASE+0x0000AD            /*!< payWave error N AD, payWave_TxnQVSDCCert.c  __payWave_sda_verif_signature(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_EMV_DATA_AUTHENTICATION_CODE tag */
#define ERR_PAYWAVE_0000AE                              ERR_PAYWAVE_BASE+0x0000AE            /*!< payWave error N AE, payWave_TxnQVSDCCert.c  payWave_qVSDC_ODA_AddData(), oda_datas max buffer length reached */
#define ERR_PAYWAVE_0000AF                              ERR_PAYWAVE_BASE+0x0000AF            /*!< payWave error N AF, payWave_TxnQVSDCCert.c  Function_TxnState_QVSDCGetCert(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_AID_CARD */
#define ERR_PAYWAVE_0000B0                              ERR_PAYWAVE_BASE+0x0000B0            /*!< payWave error N B0, payWave_TxnQVSDCCert.c  Function_TxnState_QVSDCGetCert(), GTL_SharedExchange_AddTag error */
#define ERR_PAYWAVE_0000B1                              ERR_PAYWAVE_BASE+0x0000B1            /*!< payWave error N B1, payWave_TxnQVSDCCert.c  Function_TxnState_QVSDCGetCert(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_CA_PUBLIC_KEY_INDEX_CARD tag */
#define ERR_PAYWAVE_0000B2                              ERR_PAYWAVE_BASE+0x0000B2            /*!< payWave error N B2, payWave_TxnQVSDCCert.c  Function_TxnState_QVSDCGetCert(), GTL_SharedExchange_AddTag error */
#define ERR_PAYWAVE_0000B3                              ERR_PAYWAVE_BASE+0x0000B3            /*!< payWave error N B3, payWave_TxnQVSDCCert.c  Function_TxnState_QVSDCODAProc(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_AIP tag */
#define ERR_PAYWAVE_0000B4                              ERR_PAYWAVE_BASE+0x0000B4            /*!< payWave error N B4, payWave_TxnQVSDCCert.c  GTL_DataStorage_GetTagWithIndex(), error with \ref TAG_EMV_TERMINAL_CAPABILITIES tag */
#define ERR_PAYWAVE_0000B5                              ERR_PAYWAVE_BASE+0x0000B5            /*!< payWave error N B5, payWave_TxnQVSDCCert.c  Function_TxnState_QVSDCODAProc(), FDDA and SDA could'nt be performed  */
#define ERR_PAYWAVE_0000B6                              ERR_PAYWAVE_BASE+0x0000B6            /*!< payWave error N B6, payWave_TxnQVSDCCert.c  Function_TxnState_QVSDCDDAProc(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_PAYWAVE_CARD_AUTHENTICATION_RELATED_DATA tag */
#define ERR_PAYWAVE_0000B7                              ERR_PAYWAVE_BASE+0x0000B7            /*!< payWave error N B7, payWave_TxnQVSDCCert.c  Function_TxnState_QVSDCDDAProc(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_PAYWAVE_FDDA_VERSION tag */
#define ERR_PAYWAVE_0000B8                              ERR_PAYWAVE_BASE+0x0000B8            /*!< payWave error N B8, payWave_TxnQVSDCCert.c  Function_TxnState_QVSDCDDAProc(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_INT_CAPK_MODULUS tag */
#define ERR_PAYWAVE_0000B9                              ERR_PAYWAVE_BASE+0x0000B9            /*!< payWave error N B9, payWave_TxnQVSDCCert.c  Function_TxnState_QVSDCDDAProc(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_EMV_INT_CAPK_EXPONENT tag */
#define ERR_PAYWAVE_0000BA                              ERR_PAYWAVE_BASE+0x0000BA            /*!< payWave error N BA, payWave_Debug.c         Function payWave_Debug_StoreCommandToBeSent(), GTL_DataStorage_AddTagUnIndexed error with \ref TAG_PAYWAVE_INT_SENT_APDU */
#define ERR_PAYWAVE_0000BB                              ERR_PAYWAVE_BASE+0x0000BB            /*!< payWave error N BB, payWave_Debug.c         Function payWave_Debug_StoreCommandToBeSent(), GTL_DataStorage_AddTagUnIndexed error with \ref TAG_PAYWAVE_INT_SENT_APDU */
#define ERR_PAYWAVE_0000BC                              ERR_PAYWAVE_BASE+0x0000BC            /*!< payWave error N BC, payWave_Debug.c         Function GTL_DataStorage_AddTagUnIndexed(), GTL_DataStorage_AddTagUnIndexed error with \ref TAG_PAYWAVE_INT_CARD_RESPONSE */
#define ERR_PAYWAVE_0000BD                              ERR_PAYWAVE_BASE+0x0000BD            /*!< payWave error N BD, payWave_Debug.c         Function payWave_Debug_TimeInit(), GTL_DataStorage_GetTagWithIndex error with \ref TAG_KERNEL_DEBUG_TIME */
#define ERR_PAYWAVE_0000BE                              ERR_PAYWAVE_BASE+0x0000BE            /*!< payWave error N BE, payWave_Debug.c         Function payWave_Debug_TimeInit(), GTL_DataStorage_AddTagWithIndex error with \ref TAG_KERNEL_DEBUG_TIME */
#define ERR_PAYWAVE_0000BF                              ERR_PAYWAVE_BASE+0x0000BF            /*!< payWave error N BF, payWave_Common.c        Function payWave_Common_GetAndStoreUnpredictableNumber(), An error occured when getting a random number (DLL). */
#define ERR_PAYWAVE_0000C0                              ERR_PAYWAVE_BASE+0x0000C0            /*!< payWave error N C0, payWave_Common.c        Function payWave_Common_GetAndStoreUnpredictableNumber(), Unable to add \ref TAG_EMV_UNPREDICTABLE_NUMBER tag in the database. */
#define ERR_PAYWAVE_0000C1                              ERR_PAYWAVE_BASE+0x0000C1            /*!< payWave error N C1, payWave_TxnFinalSel.c   Function __payWave_TxnFinalSel_AnalyseAndParseFinalSelectResponse(), Missing Terminal mandatory data : \ref TAG_EP_FINAL_SELECT_COMMAND_SENT from database. */
#define ERR_PAYWAVE_0000C2                              ERR_PAYWAVE_BASE+0x0000C2            /*!< payWave error N C2, payWave_TxnFinalSel.c   Function __payWave_TxnFinalSel_AnalyseAndParseFinalSelectResponse(), The sent ADF and the DF Name have the same length but are different. */
#define ERR_PAYWAVE_0000C3                              ERR_PAYWAVE_BASE+0x0000C3            /*!< payWave error N C3, payWave_TxnFinalSel.c   Function __payWave_TxnFinalSel_AnalyseAndParseFinalSelectResponse(), The sent ADF and the DF Name returned by the card has not the same length. */
#define ERR_PAYWAVE_0000C4                              ERR_PAYWAVE_BASE+0x0000C4            /*!< payWave error N C4, payWave_Isp.c           Function __payWave_Isp_ISO_Cmd(), database error for TAG_EMV_ISSUER_SCRIPT_COMMAND tag access. */
#define ERR_PAYWAVE_0000C5                              ERR_PAYWAVE_BASE+0x0000C5            /*!< payWave error N C5, payWave_Isp.c           Function __payWave_Isp_ISO_Cmd(), Contactless card command (script command) isn't a ISO format. */
#define ERR_PAYWAVE_0000C6                              ERR_PAYWAVE_BASE+0x0000C6            /*!< payWave error N C6, payWave_Isp.c           Function __payWave_Isp_SendToCard(), database error for TAG_EMV_ISSUER_SCRIPT_COMMAND tag access. */
#define ERR_PAYWAVE_0000C7                              ERR_PAYWAVE_BASE+0x0000C7            /*!< payWave error N C7, payWave_Isp.c           Function __payWave_Isp_SendToCard(), Contactless card command (script command) haven't goog length. */
#define ERR_PAYWAVE_0000C8                              ERR_PAYWAVE_BASE+0x0000C8            /*!< payWave error N C8, payWave_Isp.c           Function __payWave_Isp_SendToCard(), EmvLib_BuildCommand_Generic() call error for Contacless Issuer Script command build. */
#define ERR_PAYWAVE_0000C9                              ERR_PAYWAVE_BASE+0x0000C9            /*!< payWave error N C9, payWave_Isp.c           Function __payWave_Isp_SendToCard(), CLESS_Apdu error on an Issuer Script card command. */
#define ERR_PAYWAVE_0000CA                              ERR_PAYWAVE_BASE+0x0000CA            /*!< payWave error N CA, payWave_Isp.c           Function __payWave_Isp_SendToCard(), database error for TAG_KERNEL_LAST_APDU_AND_SW tag access. */
#define ERR_PAYWAVE_0000CB                              ERR_PAYWAVE_BASE+0x0000CB            /*!< payWave error N CB, payWave_Isp.c           Function __payWave_Isp_SendToCard(), bad card response to an Issuer Srcipt command. */
#define ERR_PAYWAVE_0000CC                              ERR_PAYWAVE_BASE+0x0000CC            /*!< payWave error N CC, payWave_Isp.c           Function __payWave_Isp_AddISR(), internal error, bad function call. */
#define ERR_PAYWAVE_0000CD                              ERR_PAYWAVE_BASE+0x0000CD            /*!< payWave error N CD, payWave_Isp.c           Function __payWave_Isp_AddISR(), database error for TAG_EMV_INT_ISSUER_SCRIPT_RESULTS tag access. */
#define ERR_PAYWAVE_0000CE                              ERR_PAYWAVE_BASE+0x0000CE            /*!< payWave error N CE, payWave_Isp.c           Function __payWave_Isp_AddISR(), database error for TAG_EMV_INT_ISSUER_SCRIPT_RESULTS tag access. */
#define ERR_PAYWAVE_0000CF                              ERR_PAYWAVE_BASE+0x0000CF            /*!< payWave error N CF, payWave_Isp.c           Function __payWave_Isp_ISP(), input 71 or 72 tag format check with error result. */
#define ERR_PAYWAVE_0000D0                              ERR_PAYWAVE_BASE+0x0000D0            /*!< payWave error N D0, payWave_Isp.c           Function __payWave_Isp_ISP(), unknown tag in 71 or 71 TLV buffer (different from ISSUER_SCRIPT_COMMAND or ISSUER_SCRIPT_IDENTIFIER. */
#define ERR_PAYWAVE_0000D1                              ERR_PAYWAVE_BASE+0x0000D1            /*!< payWave error N D1, payWave_Isp.c           Function __payWave_Isp_ISP(), TLV parsing error in input Issuer Script buffer (first step : check). */
#define ERR_PAYWAVE_0000D2                              ERR_PAYWAVE_BASE+0x0000D2            /*!< payWave error N D2, payWave_Isp.c           Function __payWave_Isp_ISP(), TLV parsing error in input Issuer Script buffer (second step : perform). */
#define ERR_PAYWAVE_0000D3                              ERR_PAYWAVE_BASE+0x0000D3            /*!< payWave error N D3, payWave_Isp.c           Function __payWave_Isp_ISP(), bad tag check in input Issuer Script buffer. */
#define ERR_PAYWAVE_0000D4                              ERR_PAYWAVE_BASE+0x0000D4            /*!< payWave error N D4, payWave_Isp.c           Function __payWave_Isp_ISP(), database error for TAG_EMV_ISSUER_SCRIPT_IDENTIFIER tag access. */
#define ERR_PAYWAVE_0000D5                              ERR_PAYWAVE_BASE+0x0000D5            /*!< payWave error N D5, payWave_Isp.c           Function __payWave_Isp_ISP(), database error for TAG_EMV_ISSUER_SCRIPT_COMMAND tag access. */
#define ERR_PAYWAVE_0000D6                              ERR_PAYWAVE_BASE+0x0000D6            /*!< payWave error N D6, payWave_Isp.c           Function __payWave_Isp_ISP(), database error for TAG_EMV_ISSUER_SCRIPT_COMMAND tag access. */
#define ERR_PAYWAVE_0000D7                              ERR_PAYWAVE_BASE+0x0000D7            /*!< payWave error N D7, payWave_Isp.c           Function __payWave_Isp_ISP(), pb of lentgh in Issuer Script commands. */
#define ERR_PAYWAVE_0000D8                              ERR_PAYWAVE_BASE+0x0000D8            /*!< payWave error N D8, payWave_Isp.c           Function __payWave_Isp_ISP(), BERTLV parsing error in input Issueur Script buffer. */
#define ERR_PAYWAVE_0000D9                              ERR_PAYWAVE_BASE+0x0000D9            /*!< payWave error N D9, payWave_Isp.c           Function Function_TxnState_ISP_ISP(), open contacless driver error. */
#define ERR_PAYWAVE_0000DA                              ERR_PAYWAVE_BASE+0x0000DA            /*!< payWave error N DA, payWave_Isp.c           Function Function_TxnState_ISP_ISP(), database error for TAG_EP_FINAL_SELECT_COMMAND_SENT tag access. */
#define ERR_PAYWAVE_0000DB                              ERR_PAYWAVE_BASE+0x0000DB            /*!< payWave error N DB, payWave_Isp.c           Function Function_TxnState_ISP_ISP(), card dialog error. */
#define ERR_PAYWAVE_0000DC                              ERR_PAYWAVE_BASE+0x0000DC            /*!< payWave error N DC, payWave_Isp.c           Function Function_TxnState_ISP_ISP(), bad card respons to a AID selection. */
#define ERR_PAYWAVE_0000DD                              ERR_PAYWAVE_BASE+0x0000DD            /*!< payWave error N DD, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CheckAUC(), database error for TAG_EMV_APPLI_USAGE_CONTROL tag access. */
#define ERR_PAYWAVE_0000DE                              ERR_PAYWAVE_BASE+0x0000DE            /*!< payWave error N DE, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CheckAUC(), database error for TAG_EMV_ISSUER_COUNTRY_CODE tag access. */
#define ERR_PAYWAVE_0000DF                              ERR_PAYWAVE_BASE+0x0000DF            /*!< payWave error N DF, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CheckAUC(), Domestic card and different countries. */
#define ERR_PAYWAVE_0000E0                              ERR_PAYWAVE_BASE+0x0000E0            /*!< payWave error N E0, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CheckAUC(), error on Application Usage Control code. */
#define ERR_PAYWAVE_0000E1                              ERR_PAYWAVE_BASE+0x0000E1            /*!< payWave error N E1, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CheckAUC(), database error for TAG_PAYWAVE_CARD_TRANSACTION_QUALIFIERS tag access. */
#define ERR_PAYWAVE_0000E2                              ERR_PAYWAVE_BASE+0x0000E2            /*!< payWave error N E2, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CVM_processing(), error in TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS => Consumer Device CVM not set. */
#define ERR_PAYWAVE_0000E3                              ERR_PAYWAVE_BASE+0x0000E3            /*!< payWave error N E3, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CVM_processing(), database error for TAG_PAYWAVE_CARD_TRANSACTION_QUALIFIERS tag access. */
#define ERR_PAYWAVE_0000E4                              ERR_PAYWAVE_BASE+0x0000E4            /*!< payWave error N E4, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CVM_processing(), error in TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS => a reader that support only the Consumer Device CVM, declines. */
#define ERR_PAYWAVE_0000E5                              ERR_PAYWAVE_BASE+0x0000E5            /*!< payWave error N E5, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CVM_processing(), database error for TAG_PAYWAVE_CARD_AUTHENTICATION_RELATED_DATA tag access. */
#define ERR_PAYWAVE_0000E6                              ERR_PAYWAVE_BASE+0x0000E6            /*!< payWave error N E6, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CVM_processing(), CVM control, Card Authentication Related Data bytes do not match with CTQ bytes => declines. */
#define ERR_PAYWAVE_0000E7                              ERR_PAYWAVE_BASE+0x0000E7            /*!< payWave error N E7, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CVM_processing(), database error for TAG_EMV_ISSUER_APPLI_DATA tag access. */
#define ERR_PAYWAVE_0000E8                              ERR_PAYWAVE_BASE+0x0000E8            /*!< payWave error N E8, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CVM_processing(), CVM control, if CTQ not returned by card, Online PIN not required or not supported, Consumer Device CVM Performed by card, Card Authentication Related Data was not returned during the transaction, the cryptogram type is not an ARQC. */
#define ERR_PAYWAVE_0000E9                              ERR_PAYWAVE_BASE+0x0000E9            /*!< payWave error N E9, payWave_TxnQVSDCPProc.c Function __payWave_TxnqVSDCPProc_CVM_processing(), CVM control : CVM Required and CVM Not Performed. */
#define ERR_PAYWAVE_0000EA                              ERR_PAYWAVE_BASE+0x0000EA            /*!< payWave error N EA, payWave_TxnReadTransactionLog.c Function __Function_TxnReadTransactionLogGetFormat(), EmvLib_BuildCommand_GetData or payWave_Debug_StoreCommandToBeSent command error . */
#define ERR_PAYWAVE_0000EB                              ERR_PAYWAVE_BASE+0x0000EB            /*!< payWave error N EB, payWave_TxnReadTransactionLog.c Function __Function_TxnReadTransactionLogGetFormat(), CLESS_Apdu command error for GetDataTransactionLog. */
#define ERR_PAYWAVE_0000EC                              ERR_PAYWAVE_BASE+0x0000EC            /*!< payWave error N EC, payWave_TxnReadTransactionLog.c Function __Function_TxnReadTransactionLogGetFormat(),  database error for TAG_EMV_LOG_FORMAT tag access or CLESS_Apdu card response differente from 90 00 for GetDataTransactionLog command. */
#define ERR_PAYWAVE_0000ED                              ERR_PAYWAVE_BASE+0x0000ED            /*!< payWave error N ED, payWave_TxnReadTransactionLog.c Function __Function_TxnReadTransactionLogGetRecords(), TAG_EMV_FCI_ISSUER_DISCRET_DATA tag parse error or EmvLib_BuildCommand_ReadRecord error for LogEntry or payWave_Debug_StoreCommandToBeSent error */
#define ERR_PAYWAVE_0000EE                              ERR_PAYWAVE_BASE+0x0000EE            /*!< payWave error N EE, payWave_TxnReadTransactionLog.c Function __Function_TxnReadTransactionLogGetFormat(), CLESS_Apdu command error for ReadTransactionLog or payWave_Debug_StoreCardResponse error or database error for TAG_KERNEL_LAST_APDU_AND_SW tag access or database error for TAG_PAYWAVE_TRANSACTION_LOG_RECORD tag access or CLESS_Apdu card response for ReadTransactionLog different from 9000 and 6A83. */
#define ERR_PAYWAVE_0000EF                              ERR_PAYWAVE_BASE+0x0000EF            /*!< payWave error N EF, payWave_TxnReadTransactionLog.c Function __payWave_TxnIsp_IssuerAuthentication(), database error for TAG_EMV_ISSUER_AUTHENTICATION_DATA tag access or EmvLib_BuildCommand_Generic() error. */
#define ERR_PAYWAVE_0000F0                              ERR_PAYWAVE_BASE+0x0000F0            /*!< payWave error N F0, payWave_TxnReadTransactionLog.c Function __payWave_TxnIsp_IssuerAuthentication(), CLESS_Apdu error for Issuer Authentication or database error for TAG_KERNEL_LAST_APDU_AND_SW tag access or Issuer Authentication error. */
// #define ERR_PAYWAVE_0000XX                           ERR_PAYWAVE_BASE+0x0000XX            /*!< payWave error N XX */

//! @}


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Glodal Data ///////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup payWaveInterfaceFunctions
//! @{

//! \brief This function performs the payWave transaction with the presented qVSDC or MSD card.
//!    All the necessary data to perform the transaction shall be provided.
//! This function shall be called after the application selection (PPSE performed and Final SELECT response and status word provided).
//!    It begins by analysing the provided Final SELECT response and Status word. The transaction is performed until completion.
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel. 
//!    This shared buffer shall be initialised using the \a GTL_SharedExchange_InitShared() function 
//! (please refer to GTL documentation for more information containing data exchange buffer).
//!    - Input data list (underline are mandatory or highly recommanded)
//!        - <i>\ref TAG_EMV_TRANSACTION_DATE</i> : Transaction date.
//!        - <i>\ref TAG_EMV_TRANSACTION_TIME</i> : Transaction time.
//!        - <i>\ref TAG_EMV_AMOUNT_AUTH_BIN</i> : Amount Authorised, Binary format.
//!        - <i>\ref TAG_EMV_AMOUNT_AUTH_NUM</i> : Amount Authorised, Numeric format.
//!        - \ref TAG_EMV_AMOUNT_OTHER_BIN : Amount Other, Binary format.
//!        - \ref TAG_EMV_AMOUNT_OTHER_NUM : Amount Other, Numeric format.
//!        - <i>\ref TAG_EMV_TRANSACTION_CURRENCY_CODE</i> : Transaction currency code.
//!        - \ref TAG_EMV_TRANSACTION_CURRENCY_EXPONENT : Transaction currency exponent.
//!        - <i>\ref TAG_EMV_TRANSACTION_TYPE</i> : Transaction type.
//!        - \ref TAG_EMV_IFD_SERIAL_NUMBER : Payment interface serial number.
//!        - \ref TAG_EMV_TRANSACTION_SEQUENCE_COUNTER :Transaction Sequence Counter
//!        - \ref TAG_EP_KERNEL_TO_USE : Kernel to be used (for payWave, it shall be set to \a DEFAULT_EP_KERNEL_VISA).
//!        - <i>\ref TAG_EP_AID_OPTIONS</i> : AID application selection options (please refer to \a EntryPoint_Tags.h for more information).
//!        - <i>\ref TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS</i> : reader data element indicating capabilities (e.g., MSD or qVSDC) and transaction-specific requirements of the reader.
//!        - \ref TAG_EP_CLESS_TRANSACTION_LIMIT : Contactless Transaction Limit for the choosen AID.
//!        - \ref TAG_EP_CLESS_FLOOR_LIMIT : Contactless Floor limit for the choosen AID.
//!        - \ref TAG_EP_CLESS_CVM_REQUIRED_LIMIT : Contactless CVM required limit for the choosen AID.
//!        - \ref TAG_EMV_TERMINAL_FLOOR_LIMIT : Terminal floor limit for the choosen AID.
//!        - <i>\ref TAG_PAYWAVE_TERM_SUPPORTED_FDDA_VERSIONS</i> : list of DDA version supported by the reader.
//!        - <i>\ref TAG_EMV_TERMINAL_CAPABILITIES</i> : Indicates the card data input, CVM, and security capabilities of the terminal.
//!        - \ref TAG_EMV_TERMINAL_COUNTRY_CODE : Terminal country code.
//!        - \ref TAG_EMV_ADD_TERMINAL_CAPABILITIES : Terminal Additional Capabilities.
//!        - \ref TAG_EMV_TERMINAL_TYPE : Terminal Type.
//!        - \ref TAG_EMV_ACQUIRER_IDENTIFIER : Acquirer identifier.
//!        - \ref TAG_EMV_MERCHANT_CATEGORY_CODE : Merchant category code.
//!        - \ref TAG_EMV_MERCHANT_IDENTIFIER : Merchant identifier.
//!        - \ref TAG_EMV_TERMINAL_IDENTIFICATION : Terminal identification.
//!        - \ref TAG_EMV_AID_TERMINAL : AID as configured in the terminal.
//!        - \ref TAG_EP_AID_ADDITIONAL_RESULTS : Application selection additional results for the choosen AID (indicates the Entry Point results, such as floor limits exceeded, etc).
//!            Please refer to \a EntryPoint_Tags.h documentation for more information about this tag.
//!        - <i>\ref TAG_EP_FINAL_SELECT_STATUS_WORD</i> : Final SELECT response status word provided by the application selection. It will be anlysed by the payWave kernel itself.
//!        - <i>\ref TAG_EP_FINAL_SELECT_RESPONSE</i> : Final SELECT response provided by the application selection. It will be anlysed by the payWave kernel itself.
//!        - \ref TAG_KERNEL_PAYMENT_FLOW_STOP : Data field indicating steps where the transaction flow has to be stopped. It is dstrongly recommanded, for transaction performances purposes, to not interrupt the transaction flow using this way (recommanded value is all set to 0).
//!        - \ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM : Data field indicating steps where customisation is necessary.
//!        - \ref TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES : Supported language for the choosen AID.
//!        - \ref TAG_EP_FINAL_SELECT_COMMAND_SENT : Final select sent to the card.
//!    - Output data returned by the payWave kernel
//!        - Whatever the transaction result (except if transaction is cancelled or interrupted), in case of MSD card treated :
//!            - \ref TAG_KERNEL_STATUS_CODE : Status code (Status code value. See Status Code values definition for more information).
//!            - \ref TAG_KERNEL_CARD_TYPE : Card type (if determined, 0x0001 for qVSDC cards, 0x0002 for MSD cards).
//!            - \ref TAG_EMV_AIP : Application Interchange Profile.
//!            - \ref TAG_EMV_ATC : Application Transaction Counter (ATC).
//!            - \ref TAG_EMV_APPLICATION_CRYPTOGRAM : Application Cryptogram.
//!            - \ref TAG_EMV_IFD_SERIAL_NUMBER : Payment interface serial number.
//!            - \ref TAG_EMV_ISSUER_APPLI_DATA : Issuer Application Data.
//!            - \ref TAG_EMV_TERMINAL_CAPABILITIES : Indicates the card data input, CVM, and security capabilities of the terminal.
//!            - \ref TAG_EMV_TERMINAL_TYPE : Terminal Type.
//!            - \ref TAG_EMV_UNPREDICTABLE_NUMBER : Unpredictable Number.
//!            - \ref TAG_EMV_AMOUNT_AUTH_BIN : Amount Authorised, Binary format.
//!            - \ref TAG_EMV_AMOUNT_AUTH_NUM : Amount Authorised, Numeric format.
//!            - \ref TAG_EMV_AMOUNT_OTHER_BIN : Amount Other, Binary format.
//!            - \ref TAG_EMV_AMOUNT_OTHER_NUM : Amount Other, Numeric format.
//!            - \ref TAG_EMV_APPLI_EFFECTIVE_DATE : Application Effective Date.
//!            - \ref TAG_EMV_APPLI_EXPIRATION_DATE : Application Expiration Date.
//!            - \ref TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER : Application Primary Account Number (PAN) Sequence Counter.
//!            - \ref TAG_EMV_TERMINAL_COUNTRY_CODE : Terminal country code.
//!            - \ref TAG_EMV_TRACK_2_DISCRET_DATA : Application Primary Account Number (PAN) Sequence Counter.
//!            - \ref TAG_EMV_TRACK_1_DISCRET_DATA : Track 1 Discretionary Data.
//!            - \ref TAG_EMV_TRANSACTION_CURRENCY_CODE : Transaction currency code.
//!            - \ref TAG_EMV_TRANSACTION_CURRENCY_EXPONENT : Transaction currency exponent.
//!            - \ref TAG_EMV_TRANSACTION_DATE : Transaction date.
//!            - \ref TAG_EMV_TRANSACTION_TIME : Transaction time.
//!            - \ref TAG_EMV_TRANSACTION_TYPE : Transaction type.
//!            - \ref TAG_EMV_DF_NAME : Dedicated File (DF) Name.
//!            - \ref TAG_EMV_SERVICE_CODE : Service Code.
//!            - \ref TAG_EMV_TRANSACTION_SEQUENCE_COUNTER :Transaction Sequence Counter.
//!            - \ref TAG_EMV_TRACK_2_EQU_DATA : Track 2 Equivalent Data.
//!            - \ref TAG_KERNEL_SIGNATURE_REQUESTED : Indicates whether a signature is required or not (TRUE if signature is required).
//!            - \ref TAG_KERNEL_LAST_APDU_AND_SW : Indicates the last command sent to the card (CLA/INS/P1/P2) and the status word (SW) provided by the card to this command.
//!            - \ref TAG_KERNEL_DEBUG_TIME : TAG debug time (active measures of steps, cards access, ...).
//!            - \ref TAG_PAYWAVE_INT_SENT_APDU : APDU buffer sent to card
//!            - \ref TAG_PAYWAVE_INT_CARD_RESPONSE : card response buffer
//!            - \ref TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS : reader data element indicating capabilities (e.g., MSD or qVSDC) and transaction-specific requirements of the reader.
//!            - \ref TAG_KERNEL_SELECTED_PREFERED_LANGUAGE : Language identifier matching between the card and the terminal (as determined by the language selection).
//!            - \ref TAG_EMV_APPLICATION_LABEL : Application label.
//!            - \ref TAG_PAYWAVE_TRACK_1 : Track 1 build by terminal.
//!            - \ref TAG_PAYWAVE_MAGSTRIPE_TRACK_2 : MagStripe track 2.
//!            - \ref TAG_PAYWAVE_FORM_FACTOR_INDICATOR : Indicates the form factor of the consumer payment device and the type of contactless interface over which the transaction was conducted.
//!            - \ref TAG_PAYWAVE_CUSTOMER_EXCLUSIVE_DATA : Contains data for transmission to the Issuer in MSD transactions with a cryptogram.
//!        - Whatever the transaction result (except if transaction is cancelled or interrupted), in case of qVSDC card treated :
//!            - \ref TAG_KERNEL_STATUS_CODE : Status code (Status code value. See Status Code values definition for more information).
//!            - \ref TAG_KERNEL_CARD_TYPE : Card type (if determined, 0x0001 for qVSDC cards, 0x0002 for MSD cards).
//!            - \ref TAG_EMV_TVR : Terminal Verification Results.
///            - \ref TAG_KERNEL_ONLINE_PIN_REQUESTED : Indicates if online PIN is requested by the kernel or not (TRUE if Online PIN is requested).
//!            - \ref TAG_KERNEL_SIGNATURE_REQUESTED : Indicates whether a signature is required or not (TRUE if signature is required).
//!            - \ref TAG_KERNEL_LAST_APDU_AND_SW : Indicates the last command sent to the card (CLA/INS/P1/P2) and the status word (SW) provided by the card to this command.
//!            - \ref TAG_KERNEL_DEBUG_TIME : TAG debug time (active measures of steps, cards access, ...).
//!            - \ref TAG_PAYWAVE_INT_SENT_APDU : APDU buffer sent to card.
//!            - \ref TAG_PAYWAVE_INT_CARD_RESPONSE : card response buffer.
//!            - \ref TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS : reader data element indicating capabilities (e.g., MSD or qVSDC) and transaction-specific requirements of the reader.
//!            - \ref TAG_EMV_AMOUNT_AUTH_NUM : Amount Authorised, Numeric format.
//!            - \ref TAG_PAYWAVE_AVAILABLE_OFFLINE_SPENDING_AMOUNT : Available Offline Spending Amount.
//!            - \ref TAG_EMV_TRACK_2_EQU_DATA : Track 2 Equivalent Data.
//!            - \ref TAG_EMV_APPLI_EXPIRATION_DATE : Application Expiration Date.
//!            - \ref TAG_EMV_APPLI_PAN : Application Primary Account Number (PAN).
//!            - \ref TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER : Application Primary Account Number (PAN) Sequence Counter.
//!            - \ref TAG_KERNEL_SELECTED_PREFERED_LANGUAGE : Language identifier matching between the card and the terminal (as determined by the language selection).
//!            - \ref TAG_EMV_DF_NAME : Dedicated File (DF) Name.
//!            - \ref TAG_EMV_APPLICATION_LABEL : Application label.
//!            - \ref TAG_EMV_IFD_SERIAL_NUMBER : Payment interface serial number.
//!            - \ref TAG_EMV_TERMINAL_CAPABILITIES : Indicates the card data input, CVM, and security capabilities of the terminal.
//!            - \ref TAG_EMV_TERMINAL_TYPE : Terminal Type.
//!            - \ref TAG_EMV_AMOUNT_AUTH_BIN : Amount Authorised, Binary format.
//!            - \ref TAG_EMV_AMOUNT_OTHER_BIN : Amount Other, Binary format.
//!            - \ref TAG_EMV_AMOUNT_OTHER_NUM : Amount Other, Numeric format.
//!            - \ref TAG_EMV_APPLI_EFFECTIVE_DATE : Application Effective Date.
//!            - \ref TAG_EMV_TERMINAL_COUNTRY_CODE : Terminal country code.
//!            - \ref TAG_EMV_TRACK_2_DISCRET_DATA : Application Primary Account Number (PAN) Sequence Counter.
//!            - \ref TAG_EMV_TRACK_1_DISCRET_DATA : Track 1 Discretionary Data
//!            - \ref TAG_EMV_TRANSACTION_CURRENCY_CODE : Transaction currency code.
//!            - \ref TAG_EMV_TRANSACTION_CURRENCY_EXPONENT : Transaction currency exponent.
//!            - \ref TAG_EMV_TRANSACTION_DATE : Transaction date.
//!            - \ref TAG_EMV_TRANSACTION_TIME : Transaction time.
//!            - \ref TAG_EMV_TRANSACTION_TYPE : Transaction type.
//!            - \ref TAG_EMV_SERVICE_CODE : Service Code
//!            - \ref TAG_EMV_TRANSACTION_SEQUENCE_COUNTER : Transaction Sequence Counter
//!            - \ref TAG_EMV_APPLICATION_CRYPTOGRAM : Application Cryptogram
//!            - \ref TAG_EMV_AIP : Application Interchange Profile
//!            - \ref TAG_EMV_ATC : Application Transaction Counter (ATC)
//!            - \ref TAG_EMV_UNPREDICTABLE_NUMBER : Unpredictable Number
//!            - \ref TAG_EMV_ISSUER_APPLI_DATA : Issuer Application Data
//!            - \ref TAG_PAYWAVE_FORM_FACTOR_INDICATOR : Indicates the form factor of the consumer payment device and the type of contactless interface over which the transaction was conducted.
//!            - \ref TAG_PAYWAVE_TERMINAL_ENTRY_CAPABILITY : Terminal entry cababilities.
//!            - \ref TAG_PAYWAVE_TRANSACTION_LOG_RECORD : payWave Transaction Log (from card) storage.
//!            - \ref TAG_PAYWAVE_ODA_FAIL :  payWave kernel parameter : error is due to an Fdda Fail.
//!            - \ref TAG_PAYWAVE_DECLINED_BY_CARD : error is due to a card AAC response.
//!        - error case transaction result
//!            - \ref TAG_KERNEL_STATUS_CODE : Status code (Status code value. See Status Code values definition for more information).
//!            - \ref TAG_KERNEL_TRACE_ERROR : TAG trace error (memorise error and associated tags).
//!            - \ref TAG_KERNEL_CARD_TYPE : Card type (if determined, 0x0001 for qVSDC cards, 0x0002 for MSD cards).
//!            - \ref TAG_KERNEL_LAST_APDU_AND_SW : Indicates the last command sent to the card (CLA/INS/P1/P2) and the status word (SW) provided by the card to this command.
//!            - \ref TAG_KERNEL_DEBUG_TIME : TAG debug time (active measures of steps, cards access, ...).
//!            - \ref TAG_PAYWAVE_INT_SENT_APDU : APDU buffer sent to card.
//!            - \ref TAG_PAYWAVE_INT_CARD_RESPONSE : card response buffer.
//!            - \ref TAG_KERNEL_IS_CA_REVOKED : Indicates if the Certificate Authority public key is revoked or not (TRUE if CA is revoked).
//!            - \ref TAG_KERNEL_SELECTED_PREFERED_LANGUAGE : Language identifier matching between the card and the terminal (as determined by the language selection).
//! \return Kernel processing status code.
//!        - \ref KERNEL_STATUS_OFFLINE_APPROVED : Transaction succeeded and is offline approved.
//!        - \ref KERNEL_STATUS_OFFLINE_DECLINED : Transaction is offline declined.
//!        - \ref KERNEL_STATUS_ONLINE_AUTHORISATION : Transaction succeded and has to be sent online for authorisation.
//!        - \ref KERNEL_STATUS_CANCELLED : if transaction has been cancelled by the custom application (using \a payWave_Cancel() function).
//!        Take care that when transaction is cancelled by the user, status code returned is \ref KERNEL_STATUS_CANCELLED | \ref KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK.
//!        - \ref KERNEL_STATUS_SERVICE_NOT_AVAILABLE : if payWave service is not available.
//!        - \ref KERNEL_STATUS_DATABASE_ERROR : A database error occured.
//!        - \ref KERNEL_STATUS_INVALID_INPUT_DATA : if provided data in \a pDataStruct are not correct.
//!        - \ref KERNEL_STATUS_LACK_OF_MEMORY : there is not enough memeory to perform the transaction.
//!        - \ref KERNEL_STATUS_COMMUNICATION_ERROR : if a communication error occured with the card (no reponse to a command because card has been to early removed for example).
//!        - \ref KERNEL_STATUS_MISSING_INPUT_DATA : mandatory input data has not been supplied.
//!        - \ref KERNEL_STATUS_ICC_MISSING_DATA : if mandatory ICC card is missing.
//!        - \ref KERNEL_STATUS_ICC_REDUNDANT_DATA : if card returned a redundant data.
//!        - \ref KERNEL_STATUS_ICC_DATA_FORMAT_ERROR : if card returned data with bad format.
//!        - \ref KERNEL_STATUS_TERM_MISSING_DATA : A mandatory terminal is missing to perform the transaction.
//!        - \ref KERNEL_STATUS_CARD_BLOCKED : If the card is blocked (Final SELECT status word is 0x6A81).
//!        - \ref KERNEL_STATUS_REMOVE_AID : application shall be removed from candidate list, please give the next AID.
//!        - \ref KERNEL_STATUS_UNKNOWN_SW : card responded to a command with an unexpected status word.
//!        - \ref KERNEL_STATUS_COND_OF_USE_NOT_SATISFIED : Card responded to GPO with 0x6985 status word.
//!        - \ref KERNEL_STATUS_USE_CONTACT_INTERFACE : if transaction shall be conducted over another interafce.
//!        - \ref KERNEL_STATUS_INTERNAL_ERROR : An internal kernel error occured (would never occur).
//!        - \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The payWave kernel is not loaded in the terminal (or an interface error occured).
//!        - \ref KERNEL_STATUS_EXPIRED_CERTIFICATE : The certificate is expired.
//!        - \ref KERNEL_STATUS_REVOKED_CERTIFICATE : The certificate is revoked.

int payWave_DoTransaction (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to resume the transaction when an interruption occured (requested interruption or cancellation).
//! The transaction will continue where it has been interrupted.
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//!    - Input data can be provided. It will replace each existing data within the kernel database.
//!    - Output data are the same as \ref payWave_DoTransaction() function (as it continues the transaction).
//! \return Kernel processing status code (identical than the \ref payWave_DoTransaction() function).
//! The returned value depends on the step executed.

int payWave_ResumeTransaction (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to execute a specific transaction step when an interruption has been executed
//! (requested interruption or cancellation).
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//!    - Input data can be provided. It will replace each existing data within the kernel database.
//!    - Output data are the same as \ref payWave_DoTransaction() function.
//! \return Kernel processing status code (identical to the \ref payWave_DoTransaction() function).
//! The returned value depends on the step where the transaction is resumed.

//! \brief Function to execute the ProcessTransactionStep kernel service. 
//! \param[in,out] pDataStruct data exchange buffer.
//! \return Kernel processing status code.

int payWave_ProcessTransactionStep (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to retrieve all the kernel database.
//! All the tags present in the database are retrieved.
//! \param[out] pDataStruct Shared buffer filled with all the kernel data. 
//! Make sure the buffer size you provide is bigger enough to store all the tags.
//! Note the shared buffer is automatically cleared by the payWave kernel.
//! \return Kernel processing status code.
//!    - \ref KERNEL_STATUS_OK if all the data are provided and no error occured.
//!    - \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!    - \ref KERNEL_STATUS_DATABASE_ERROR if a database error occured.
//!    - \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The payWave kernel is not loaded in the terminal (or an interface error occured).
//! \note It is strongly recommanded to not call this function during the transaction flow, as it should impact the transaction performance.

int payWave_GetAllData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to execute the After transaction step (Used for load Issuer Scripts).
//! The transaction will continue on a specific step.
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//!    This shared buffer shall be initialised using the \a GTL_SharedExchange_InitShared() function 
//! (please refer to GTL documentation for more information containing data exchange buffer).
//!    - Input data list (underline are mandatory or highly recommanded)
//!        - <i>\ref TAG_PAYWAVE_ISSUER_SCRIPT_LIST</i> : Scripts received from Issuer.
//!    - Output data are the same as \ref payWave_DoTransaction() function (as it continues the transaction).
//! - Whatever the transaction result (except if transaction is cancelled or interrupted) :
//!    - \ref TAG_KERNEL_STATUS_CODE : Status code (Status code value. See Status Code values definition for more information).
//!    - \ref TAG_PAYWAVE_ISSUER_SCRIPT_RESULT : Bits field that indicates the result of Issuer Script Processing.
//! \return Kernel processing status code :
//!    - \ref KERNEL_STATUS_OK if all the data are provided and no error occured.
//!    - \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!    - \ref KERNEL_STATUS_DATABASE_ERROR if a database error occured.
//!    - \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The payWave kernel is not loaded in the terminal (or an interface error occured).
//! The returned value depends on the step executed.
int payWave_AfterTransaction (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function allows to request kernel some tags (if present in its database).
//! \param[in,out] pDataStruct Shared buffer used to exchange data with the kernel.
//! Make sure the buffer size you provide is bigger enough to store all the tags.
//! Note the shared buffer is automatically cleared by the payWave kernel.
//! - Input data : Tag to be requested to the kernel. It is a concatenation of tags and length set to 0.
//! - Output data : list of retrieved data (coded in BER-TLV) that have been equested and that are present in the kernel database.
//! \return Kernel processing status code.
//!    - \ref KERNEL_STATUS_OK if all the data are provided and no error occured.
//!    - \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to store all the tags.
//!    - \ref KERNEL_STATUS_DATABASE_ERROR if a database error occured.
//!    - \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The payWave kernel is not loaded in the terminal (or an interface error occured).
//! \note It is strongly recommanded to not call this function during the transaction flow, as it should impact the transaction performance.
//! \remarks Example to get the transaction date and the transaction time from the payWave kernel :
//! \code
//!    T_SHARED_DATA_STRUCT * pSharedDataStruct;
//!    
//!    // Initialise the shared buffer to be used (if not already done).
//!    // Make sure size is bigger enough.
//!    pSharedDataStruct = GTL_SharedExchange_InitShared (256);
//!
//!    if (pSharedDataStruct == NULL)
//!    {
//!        // An error occured when creating the shared data structure.
//!        ...
//!    }
//!    
//!    // Add TAG_EMV_TRANSACTION_DATE tag in pSharedDataStruct with a zero length.
//!    ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_EMV_TRANSACTION_DATE, 0, NULL);
//!    // Check returned value ...
//!    
//!    // Add TAG_EMV_TRANSACTION_TIME tag in pSharedDataStruct with a zero length.
//!    ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_EMV_TRANSACTION_TIME, 0, NULL);
//!    // Check returned value ...
//!    
//!    // Call the payWave kernel to retrieve the requested tags.
//!    nResult = payWave_GetData (pSharedDataStruct);
//!    if (nResult != KERNEL_STATUS_OK)
//!    {
//!        // An error occured when requesting tags to the kernel.
//!        // ...
//!    }
//!    
//!    // Now, pSharedDataStruct contains the requested tags (only the ones that are present within the kernel database)
//!    // You can use GTL_SharedExchange_GetNext and GTL_SharedExchange_FindNext functions to retrievethe desired tags.
//!    // ...
//!    
//!    // If created, destroy the shared buffer if not used anymore
//!    if (pSharedDataStruct != NULL)
//!        GTL_SharedExchange_DestroyShare (pSharedDataStruct);
//! \endcode

int payWave_GetData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Function to be used to load some data within the kernel.
//! \param[in] pDataStruct Shared buffer filled with the data to be loaded into the kernel.
//!    - \a pDataStruct is filled using the \a GTL_SharedExchange_AddTag() function.
//!    - All the tags that are unknown by the kernel are ignored.
//!    - If a tag is added with a zero length, it removes this tag from the kernel database.
//!    - If a provided tag is already present in the database, this one will be replaced by the new value.
//! \return Kernel processing status code.
//!    - \ref KERNEL_STATUS_OK if tags correctly added in the kernel database and no error occured.
//!    - \ref KERNEL_STATUS_INVALID_INPUT_DATA : if provided data in \a pDataStruct are not correct.
//!    - \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in the kernel database to store all the tags.
//!    - \ref KERNEL_STATUS_DATABASE_ERROR if a database error occured.
//!    - \ref KERNEL_STATUS_LIB_INTERFACE_ERROR : The payWave kernel is not loaded in the terminal (or an interface error occured).
//! \note It is strongly recommanded to not call this function during the transaction flow, as it should impact the transaction performance.
//! \remarks Example to get the transaction date and the transaction time from the payWave kernel :
//! \code
//!    T_SHARED_DATA_STRUCT * pSharedDataStruct;
//!    unsigned char ucTransactionDate[] = {0x09,0x09,0x09}; // September 9th of 2009
//!    
//!    // Initialise the shared buffer to be used (if not already done).
//!    // Make sure size is bigger enough.
//!    pSharedDataStruct = GTL_SharedExchange_InitShared (256);
//!
//!    if (pSharedDataStruct == NULL)
//!    {
//!        // An error occured when creating the shared data structure.
//!        ...
//!    }
//!    
//!    // Add transaction date in pSharedDataStruct (if tag already present in the database, this one will be replaced by the one sent here).
//!    ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_EMV_TRANSACTION_DATE, 3, ucTransactionDate);
//!    // Check returned value ...
//!    
//!    // Add transaction time tag in pSharedDataStruct with a zero length (to indicate you want to remove it).
//!    ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_EMV_TRANSACTION_TIME, 0, NULL);
//!    // Check returned value ...
//!    
//!    // Call the payWave kernel to load the tags.
//!    nResult = payWave_LoadData (pSharedDataStruct);
//!    if (nResult != KERNEL_STATUS_OK)
//!    {
//!        // An error occured when requesting tags to the kernel.
//!        // ...
//!    }
//!    
//!    // Tags has been correctly loaded in the kernel database
//!    // ...
//!    
//!    // If created, destroy the shared buffer if not used anymore
//!    if (pSharedDataStruct != NULL)
//!        GTL_SharedExchange_DestroyShare (pSharedDataStruct);
//! \endcode

int payWave_LoadData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function can be used to cancel the payWave transaction.
//! We could imagine to use it to cancel the transaction when the red key is pressed during the payWave transaction for example.
//! \return Always \ref KERNEL_STATUS_OK.
//! \note This is the responsibility of the custom application to correctly use this function. 
//! The payWave transaction can be cancelled at any step.
//! If called, the kernel will return \ref KERNEL_STATUS_CANCELLED on the following functions :
//!    - \ref payWave_DoTransaction().
//!    - \ref payWave_ResumeTransaction().

int payWave_Cancel (void);



//! \brief This function allows to manage the payWave kernel debug features.
//! This allows to activate / dactivate the following debug features :
//!    - Trace : it provides debug information in the \a Trace.exe tool provided in the TDS.
//!    - Time measurements : it manages in the database the \ref TAG_KERNEL_DEBUG_TIME tag that can be retrieved using \ref payWave_GetData() function.
//!    Note if Time debug feature is not activated, \ref TAG_KERNEL_DEBUG_TIME tag is not stored in the kernel database.
//!    - APDU storage : it stores all the APDU sent to the card and responses sent by the card in the database, using specific tags. 
//!    Each command is stored in a \ref TAG_PAYWAVE_INT_SENT_APDU tag, each received card response is stored in a \ref TAG_PAYWAVE_INT_CARD_RESPONSE tag.
//! \param[in] pDataStruct Shared buffer filled with the \ref TAG_KERNEL_DEBUG_ACTIVATION tag indicating the debug mode.
//!    If the tag is not present or set to 0, then all the debug features are deactivated.
//! \return \ref KERNEL_STATUS_OK is always returned.
//!    \note If debug features shall be activated, it is strongly recommanded to call this function before the transaction has started.
//!    It allows to not waste time during the transaction (performances purposes).
//! \remarks Example to get the transaction date and the transaction time from the payWave kernel :
//! \code
//!    T_SHARED_DATA_STRUCT * pSharedDataStruct;
//!    unsigned char ucTraceOnly = KERNEL_DEBUG_MASK_TRACES; // Trace only is activated
//!    unsigned char ucApduOnly = KERNEL_DEBUG_MASK_APDU;    // APDU is activated
//!    unsigned char ucTracesAndApdu = KERNEL_DEBUG_MASK_TRACES | KERNEL_DEBUG_MASK_APDU; // Traces and APDU debug features are activated.
//!    
//!    // Initialise the shared buffer to be used (if not already done).
//!    // Make sure size is bigger enough.
//!    pSharedDataStruct = GTL_SharedExchange_InitShared (128);
//!
//!    if (pSharedDataStruct == NULL)
//!    {
//!        // An error occured when creating the shared data structure.
//!        ...
//!    }
//!    
//!    // Indicate Traces Only has to be activated.
//!    ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_KERNEL_DEBUG_ACTIVATION, 1, &ucTraceOnly);
//!    // Check returned value ...
//!    
//!    // Call the payWave kernel to load the tags.
//!    nResult = payWave_DebugManagement (pSharedDataStruct);
//!    if (nResult != KERNEL_STATUS_OK)
//!    {
//!        // An error occured when requesting tags to the kernel.
//!        // ...
//!    }
//!    
//!    // Indicate Traces Only has to be activated.
//!    ret = GTL_SharedExchange_AddTag (pSharedDataStruct, TAG_KERNEL_DEBUG_ACTIVATION, 1, &ucApduOnly);
//!    // Check returned value ...
//!    
//!    // Call the payWave kernel to load the tags.
//!    nResult = payWave_DebugManagement (pSharedDataStruct);
//!    if (nResult != KERNEL_STATUS_OK)
//!    {
//!        // An error occured when requesting tags to the kernel.
//!        // ...
//!    }
//!    
//!    // At this step, only APDU is activated (trace has been deactivated).
//!    // If you want to activate both Traces and APDU, send TAG_KERNEL_DEBUG_ACTIVATION = ucTracesAndApdu.
//!    // ...
//!    
//!    // If created, destroy the shared buffer if not used anymore
//!    if (pSharedDataStruct != NULL)
//!        GTL_SharedExchange_DestroyShare (pSharedDataStruct);
//! \endcode

int payWave_DebugManagement (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function clears and initialise the payWave kernel.
//! It fully clear the database and restores the global data (reset cancel, deactivate debug features, etc). 
//! It is mandatory to call this function 
//! after each payWave transation has been completed (and the terminal is returning on idle state).
//! \return Kernel processing status code.
//!    - \ref KERNEL_STATUS_OK if payWave kernel correctly cleared and initialised.
//!    - \ref KERNEL_STATUS_DATABASE_ERROR if a database error occured.

int payWave_Clear (void);



//! \brief This function gets the kernel information.
//! \param[out] pDataStruct Shared buffer filled with the following tags (note this buffer is automatically cleared by the function) :
//!    - \ref TAG_KERNEL_APPLICATION_NAME that indicates the application name (ASCII format).
//!    - \ref TAG_KERNEL_APPLICATION_IDENT that indicates the kernel identifier (in ASCII format, \a 813350 followed by the payWave kernel version on 4 digits).
//!    - \ref TAG_KERNEL_APPLICATION_CRC that indicates the payWave kernel CRC.
//! \return
//!    - \ref KERNEL_STATUS_OK if kernel information correctly retrieved.
//!    - \ref KERNEL_STATUS_LACK_OF_MEMORY if there is not enough memory in \a pDataStruct to stre al the tags.
//!    - \ref KERNEL_STATUS_INTERNAL_ERROR if an internal error occured.

int payWave_GetInfos (T_SHARED_DATA_STRUCT * pDataStruct);



//! @}


//! \addtogroup payWaveTransactionFlow
//! @{
//! Here is described the transaction flow as it is implemented in the payWave kernel. Each transaction step in the following graph corresponds to a transaction step described in \ref payWaveTransactionFlowSteps.
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
//!		nodeStart [label="payWave_DoTransaction",shape="ellipse",style=filled];
//!		node_STEP_PAYWAVE_INITIAL [label="Step : initial process management",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_INITIAL"];
//!		node_STEP_PAYWAVE_FINAL_APPLICATION_SELECTION [label="Final card selection",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_FINAL_APPLICATION_SELECTION"];
//!		node_STEP_PAYWAVE_APPLICATION_BLOCKED [label="Step if application is blocked",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_APPLICATION_BLOCKED"];
//!		node_STEP_PAYWAVE_CARD_BLOCKED [label="Step if card is blocked",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_CARD_BLOCKED"];
//!		node_STEP_PAYWAVE_SELECT_ANOTHER_APPLICATION [label="Step if an another application must be selected",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_SELECT_ANOTHER_APPLICATION"];
//!		node_STEP_PAYWAVE_INITIATE_APPLICATION_PROCESSING [label="Initiate Application processing",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_INITIATE_APPLICATION_PROCESSING"];
//!		node_STEP_PAYWAVE_MSD_READ_APPLICATION_DATA [label="Card MSD Read card data",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_MSD_READ_APPLICATION_DATA"];
//!		node_STEP_PAYWAVE_MSD_MANDATORY_DATA_CHECKING [label="Card MSD Mandatory Data Checking",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_MSD_MANDATORY_DATA_CHECKING"];
//!		node_STEP_PAYWAVE_MSD_COMPLETION [label="Card MSD Completion",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_MSD_COMPLETION"];
//!		node_STEP_PAYWAVE_MSD_REMOVE_CARD [label="Card MSD Remove Card",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_MSD_REMOVE_CARD"];
//!		node_STEP_PAYWAVE_QVSDC_READ_APPLICATION_DATA [label="Card QVSDC Read Application data",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_QVSDC_READ_APPLICATION_DATA"];
//!		node_STEP_PAYWAVE_QVSDC_REMOVE_CARD [label="Card QVSDC Remove Card",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_QVSDC_REMOVE_CARD"];
//!		node_STEP_PAYWAVE_QVSDC_MANDATORY_DATA_CHECKING [label="Card QVSDC Check Mandatory Data",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_QVSDC_MANDATORY_DATA_CHECKING"];
//!		node_STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL [label="Card QVSDC Black List control",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL"];
//!		node_STEP_PAYWAVE_QVSDC_POST_PROCESSING [label="Card QVSDC Post Processing",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_QVSDC_POST_PROCESSING"];
//!		node_STEP_PAYWAVE_QVSDC_GET_CERTIFICATE [label="Card QVSDC Get Certificate",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_QVSDC_GET_CERTIFICATE"];
//!		node_STEP_PAYWAVE_QVSDC_ODA_PROCESSING [label="Card QVSDC ODA Processing",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_QVSDC_ODA_PROCESSING"];
//!		node_STEP_PAYWAVE_QVSDC_FDDA_PROCESSING [label="Card QVSDC DDA Processing",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_QVSDC_FDDA_PROCESSING"];
//!		node_STEP_PAYWAVE_QVSDC_SDA_PROCESSING [label="Card QVSDC SDA Processing",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_QVSDC_SDA_PROCESSING"];
//!		node_STEP_PAYWAVE_QVSDC_COMPLETION [label="Card QVSDC Completion",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_QVSDC_COMPLETION"];
//!		node_STEP_PAYWAVE_QVSDC_COMPLETION_WITH_ERROR [label="Card Completion when an error occured",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_QVSDC_COMPLETION_WITH_ERROR"];
//!		node_STEP_PAYWAVE_STOP [label="Last transaction step used for release memory, POFF, traces",style=filled,fillcolor=plum,URL="\ref STEP_PAYWAVE_STOP"];
//!		nodeStop [label="Return transaction result",shape="ellipse",style=filled];
//! 
//!		nodeStart -> node_STEP_PAYWAVE_INITIAL [weight=100];
//!		node_STEP_PAYWAVE_INITIAL -> node_STEP_PAYWAVE_FINAL_APPLICATION_SELECTION [weight=100];
//!		node_STEP_PAYWAVE_FINAL_APPLICATION_SELECTION -> node_STEP_PAYWAVE_INITIATE_APPLICATION_PROCESSING [weight=100];
//!		node_STEP_PAYWAVE_FINAL_APPLICATION_SELECTION -> node_STEP_PAYWAVE_CARD_BLOCKED [weight=100];
//!		node_STEP_PAYWAVE_FINAL_APPLICATION_SELECTION -> node_STEP_PAYWAVE_APPLICATION_BLOCKED [weight=100];
//!		node_STEP_PAYWAVE_FINAL_APPLICATION_SELECTION -> node_STEP_PAYWAVE_SELECT_ANOTHER_APPLICATION [weight=100];
//!		node_STEP_PAYWAVE_INITIATE_APPLICATION_PROCESSING -> node_STEP_PAYWAVE_MSD_READ_APPLICATION_DATA [weight=100];
//!		node_STEP_PAYWAVE_INITIATE_APPLICATION_PROCESSING -> node_STEP_PAYWAVE_QVSDC_READ_APPLICATION_DATA [weight=100];
//!		node_STEP_PAYWAVE_MSD_READ_APPLICATION_DATA -> node_STEP_PAYWAVE_MSD_REMOVE_CARD [weight=100];
//!		node_STEP_PAYWAVE_MSD_REMOVE_CARD -> node_STEP_PAYWAVE_MSD_MANDATORY_DATA_CHECKING [weight=100];
//!		node_STEP_PAYWAVE_MSD_MANDATORY_DATA_CHECKING -> node_STEP_PAYWAVE_MSD_COMPLETION [weight=100];
//!		node_STEP_PAYWAVE_MSD_COMPLETION -> node_STEP_PAYWAVE_STOP [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_READ_APPLICATION_DATA -> node_STEP_PAYWAVE_QVSDC_REMOVE_CARD [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_REMOVE_CARD -> node_STEP_PAYWAVE_QVSDC_MANDATORY_DATA_CHECKING [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_MANDATORY_DATA_CHECKING -> node_STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_MANDATORY_DATA_CHECKING -> node_STEP_PAYWAVE_QVSDC_POST_PROCESSING [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_MANDATORY_DATA_CHECKING -> node_STEP_PAYWAVE_QVSDC_COMPLETION [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL -> node_STEP_PAYWAVE_QVSDC_POST_PROCESSING [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_POST_PROCESSING -> node_STEP_PAYWAVE_QVSDC_COMPLETION [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_POST_PROCESSING -> node_STEP_PAYWAVE_QVSDC_GET_CERTIFICATE [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_GET_CERTIFICATE -> node_STEP_PAYWAVE_QVSDC_ODA_PROCESSING [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_ODA_PROCESSING -> node_STEP_PAYWAVE_QVSDC_FDDA_PROCESSING [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_ODA_PROCESSING -> node_STEP_PAYWAVE_QVSDC_SDA_PROCESSING [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_ODA_PROCESSING -> node_STEP_PAYWAVE_QVSDC_COMPLETION [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_FDDA_PROCESSING -> node_STEP_PAYWAVE_QVSDC_COMPLETION [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_SDA_PROCESSING -> node_STEP_PAYWAVE_QVSDC_COMPLETION [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_COMPLETION -> nodeStop [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_COMPLETION_WITH_ERROR -> nodeStop [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_COMPLETION -> node_STEP_PAYWAVE_STOP [weight=100];
//!		node_STEP_PAYWAVE_QVSDC_COMPLETION_WITH_ERROR -> node_STEP_PAYWAVE_STOP [weight=100];
//!		node_STEP_PAYWAVE_STOP -> nodeStop [weight=100];
//!	}
//! \enddot
//! @}



//! \addtogroup payWaveOverview
//! @{
//! <h2>Presentation</h2><br>
//! The payWave kernel allows you to easily perform transactions using the Visa MSD or qVSDC contactless technology. It is fully compliant 
//! with the <i>Visa Contacless Payment Specification Version 2.1 (May 2009)</i>.<br>
//! The kernel supports the following features :
//!	- Full supports of payWave MSD and/or qVSDC contactless cards.
//!	- Following CVM are supported and configurable : No CVM, Signature and Online PIN.
//!	- Language selection management (multi language supported).
//!	- Offline Data Authentication supported methods : SDA.
//!	- Exception file and CA Revocation management.
//!	- Offline and online capabilities.
//! 
//! <table cellspacing="5" bgcolor="#FFCCCC" bordercolordark="green" bordercolorlight="yellow">
//! <tr><td>
//! <h2>Performances requirements</h2><br>
//! - Visa requires the terminal processing time during a transaction to not exceed :
//!	500 ms for a qVSDC and MSD transaction with 140 ms for the POS (Point Of Sale) terminal or Electronic Cash Register(ECR).
//!
//! These are huge constraints. That is why it is mandatory for you to optimise your application at the maximum to minimise 
//! the processing time when the transaction is in progress (i.e. when the interaction between the ICC and the terminal and 
//! in progress).<br>
//! It means :
//!	- The maximum of the data to be sent to the payWave kernel shall be prepared in advance.
//!	- The customisation shall be reduced at the minimum during the transaction.
//! </td></tr>
//! </table>
//! 
//! <h2>Additional information</h2><br>
//! The payWave kernel performs the transaction but it does not manage :
//!	- The graphical user interface : This is the role of your application to perform the GUI. It will allow a better customisation.
//!	- The payWave parameters : all the parameters (supported AID, supported CA Keys, etc) are exclusively managed by the custom application itself.
//!	When a transaction is to be performed, this is the role of your application to provide the correct data to the kernel to perform the transaction.
//!	There is no persistent data within the payWave kernel itself. After each transaction, the payWave kernel shall be completely cleared.
//!	- The exception file itself : in fact, the exception file checking is performed by the custom application (it allows you to have your own exception file format).
//!	If the PAN card (or PAN + PanSequence Number card) is found within the exception file, the custom application indicates it to the payWave kernel (using customisation).
//!	The kernel will continue transaction accordingly.
//! 
//!	<br><br>
//! <table cellspacing="5" bgcolor="#FFCCCC" bordercolordark="green" bordercolorlight="yellow">
//! <tr><td>
//! It is <b>mandatory</b> to call the \ref payWave_Clear() function after each transaction has been completed. Else, next transaction will not correctly work.
//! </td></tr>
//! </table>
//! 
//! @}



//! \addtogroup payWaveCustomisationProcess
//! @{
//! \details It is possible for an application to be called back during the transaction process to make some customisation and interact with the transaction flow.
//! For example, it would be necessary during the payWave transaction to indicate card has been correctly read (GUI), or to check if the card PAN is present or not
//! in the exception file, etc. The payWave customisation will allow you to perform any processing you need that is not specified by the payWave specification.
//! <br><br>
//! <table cellspacing="5" bgcolor="#FFCCCC" bordercolordark="green" bordercolorlight="yellow">
//! <tr><td>
//! <b>Warning</b> : The terminal processing time during the transaction (i.e. until the card and the card interact together) shall not exceed 140ms. That is why it 
//! is strongly recommended to avoid at the maximum the number of customisation calls during this period.
//! </td></tr>
//! </table>
//! 
//! <h2>How to be called to perform customisation on a transaction step</h2><br>
//! To call back an application for customisation, the payWave kernel shall have the following information :
//!	- The application identifier to call.
//!	- The application service to use.
//!	- A bit field indicating which step the application wishes to customise.
//!
//! All of this information is provided to the payWave kernel using the \ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM tag. 
//! This tag contains a \ref T_KERNEL_TRANSACTION_FLOW_CUSTOM structure.
//! The payWave kernel will call the application for customisation after the step to customise has been executed.
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
//! ADD_STEP_CUSTOM(STEP_PAYWAVE_MSD_REMOVE_CARD, sTransactionFlowCustom.pucStepCustom); // To do GUI when MStripe card has been read
//! ADD_STEP_CUSTOM(STEP_PAYWAVE_QVSDC_REMOVE_CARD, sTransactionFlowCustom.pucStepCustom); // To do GUI when MChip card has been read
//! ADD_STEP_CUSTOM(STEP_PAYWAVE_QVSDC_GET_CERTIFICATE, sTransactionFlowCustom.pucStepCustom); // To provide the CA key data for ODA
//! 
//! // For optimisation, request blacklist checking only if a black list has been loaded
//! if (ClessSample_IsBlackListPresent())	
//! 	ADD_STEP_CUSTOM(STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL, sTransactionFlowCustom.pucStepCustom); // To check if PAN is in the blacklist
//! 
//! // Add the structure into the shared buffer to be sent to the payWave kernel to perform the transaction
//! cr = GTL_SharedExchange_AddTag(pDataStruct, TAG_KERNEL_PAYMENT_FLOW_CUSTOM, sizeof(T_TRANSACTION_FLOW_CUSTOM), (const unsigned char *)&sTransactionFlowCustom);
//! if (cr != STATUS_SHARED_EXCHANGE_OK)
//! {
//! 	// An error occurred when adding the tag in the shared buffer
//! 	// ...
//! }
//! 
//! // Other processing to prepare data for payWave transaction
//! // ...
//! 
//! // Call the payWave kernel to perform the transaction (payWave_DoTransaction() function) with the shared buffer containing all the necessary data 
//! // To perform the transaction, including TAG_KERNEL_PAYMENT_FLOW_CUSTOM tag.
//! // ...
//! \endcode
//! 
//! \note As described in the example before, it is strongly recommended to customise the following payWave transaction steps :
//!	- \ref STEP_PAYWAVE_MSD_REMOVE_CARD to indicate a MSD payWave card has been read and can be removed for a transaction.
//!	- \ref STEP_PAYWAVE_QVSDC_REMOVE_CARD to indicate a qVSDC payWave card has been read and can be removed for a transaction.
//! - \ref STEP_PAYWAVE_QVSDC_GET_CERTIFICATE is mandatory for a payWave qVSDC transaction as it allows the custom application to provide to 
//!	the payWave kernel all the certificate data to perform Offline Data Authentication.
//! 
//! 
//! <b>How to perform the customisation ?</b><br>
//! When the \ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM tag is provided (with all the correct information and if the application type and service identifier are correct),
//! the payWave kernel will call you back for customisation.
//! 
//! \note For every customised step :
//!	- It is mandatory to clear data provided by the kernel from the shared buffer (after having read the necessary data provided by the kernel of course).
//! - It is mandatory to return \ref KERNEL_STATUS_CONTINUE to the customisation service.
//!
//! The function to be called when the customisation service is called by the payWave kernel shall have the following format :
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
//!		    case STEP_PAYWAVE_MSD_REMOVE_CARD:
//!			case STEP_PAYWAVE_QVSDC_REMOVE_CARD:
//! 			// Card can be remove, do GUI
//! 			// ...
//! 			// Clear the shared buffer before returning to the kernel
//! 			GTL_SharedExchange_ClearEx (pDataStuct, FALSE);
//! 			break;
//! 		case (STEP_PAYWAVE_QVSDC_GET_CERTIFICATE):
//! 			// Get the certificate depending on the other provided data
//! 			// Clear the shared buffer before returning to the kernel
//! 			GTL_SharedExchange_ClearEx (pDataStuct, FALSE);
//! 			// ... and add output data if necessary
//! 			break;
//! 		case (STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL):
//! 			// Check if the card is present in the exception file or not
//! 			// Clear the shared buffer before returning to the kernel
//! 			GTL_SharedExchange_ClearEx (pDataStuct, FALSE);
//! 			// ... and add output data if necessary
//! 			break;
//! 		default:
//! 			break;
//! 		}
//! 	}
//! 	return (nResult);
//! }
//! \endcode
//! 
//! <b>Which data are provided to custom for customisation ?</b><br>
//! By default, some data are provided to the custom on each step to be customised. By default, the following data are provided :
//!	- \ref TAG_KERNEL_CUSTOM_STEP indicating the step identifier.
//!	- \ref TAG_EMV_LANGUAGE_PREFERENCE indicating the list of supported language by the card (if present). It may help to correctly do GUI if necessary, with the correct language.
//!	- \ref TAG_KERNEL_SELECTED_PREFERED_LANGUAGE indicating the selected language during the language selection (if not present, default language shall be used). It may help to correctly do GUI if necessary, with the correct language.
//! 
//! Some specific additional data are sent depending on the customisation step :
//!	- \ref STEP_PAYWAVE_QVSDC_BLACK_LIST_CONTROL step :
//!		- Additional data provided by the payWave kernel :
//!			- \ref TAG_EMV_APPLI_PAN to indicate the card PAN.
//!			- \ref TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER to indicate the PAN Sequence number (if present).
//!		- Data that can be provided to the kernel (output) :
//!			- \ref TAG_KERNEL_PAN_IN_BLACK_LIST to indicate if PAN has been found in the exception file or not.
//!
//!	- \ref STEP_PAYWAVE_QVSDC_GET_CERTIFICATE step :
//!		- Additional data provided by the payWave kernel :
//!			- \ref TAG_EMV_DF_NAME to identify the RID to get the certificate.
//!			- \ref TAG_EMV_CA_PUBLIC_KEY_INDEX_CARD indicating the CA index (provided by the card).
//!		- Data to be provided to the kernel (output) :
//!			- \ref TAG_EMV_INT_CAPK_MODULUS containing the CA public key modulus.
//!			- \ref TAG_EMV_INT_CAPK_EXPONENT containing the CA public key exponent.
//! @}
//! 
//! \addtogroup payWaveProprietaryTags
//! @{
//! The payWave kernel allows you to define a several proprietary tags. It allows answering some specific field needs.
//! This section describes how to define these tags to make them known by the payWave kernel.
//! 
//! The proprietary tags are defined using the \ref TAG_KERNEL_PROPRIETARY_TAGS tag. When this tag is sent to the payWave kernel, 
//! this one create a proprietary database in which will be stored all the defined tags.
//! The \ref TAG_KERNEL_PROPRIETARY_TAGS tag is a list of T_TI_TAG_INFO structures (see GTL documentation for more information). 
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
//! // We consider that pDataStruct is the shared buffer used to send data to the payWave kernel
//! cr = GTL_SharedExchange_AddTag (pDataStruct, TAG_KERNEL_PROPRIETARY_TAGS, sizeof(pProprietaryTags), pProprietaryTags);
//! if (cr != STATUS_SHARED_EXCHANGE_OK)
//! {
//! 	// An error occurred
//! 	// ...
//! }
//!
//! // When performing the transaction, tags DF01, DF02 and DF03 will be known by the payWave kernel, and they will be stored ...
//! // ...
//! 
//! \endcode
//! 
//! \note This tag (if necessary) shall be sent to the payWave kernel on the \ref payWave_DoTransaction() function. As all other tags, this 
//! one is not persistent. It means it shall be sent on every transaction where the proprietary tags are necessary.
//! @}
