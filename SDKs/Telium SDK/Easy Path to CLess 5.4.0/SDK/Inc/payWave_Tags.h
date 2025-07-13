/**
 * \file     payWave_Tags.h
 * \brief    This describes all the specific payWave contactless kernel tags.
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

//! \addtogroup payWavePossibleCardTypes
//! @{

#define C_PAYWAVE_CARD_TYPE_MSB_PAYWAVE        0x00          /*!< No card type predefined. */

#define C_PAYWAVE_CARD_TYPE_UNKNOWN            0x00          /*!< No card type predefined. */
#define C_PAYWAVE_CARD_TYPE_QVSDC              0x01          /*!< Card Type qVSDC. */
#define C_PAYWAVE_CARD_TYPE_MSD                0x02          /*!< Card Type MSD. */
#define C_PAYWAVE_CARD_TYPE_WAVE2              0x03          /*!< Card Type PayWave2. */

//! @}

//! \addtogroup payWaveTagsInternallyDefined
//! @{

#define TAG_PAYWAVE_APPLICATION_DEFAULT_ACTION             0x9F52                  /*!< Visa Proprietary data element indicating issuer specified action for the card to take for certain exception conditions.<br>	- Format : b.<br>	- Length : 4 bytes.<br> - Source : Icc. */
#define TAG_PAYWAVE_APPLICATION_PROGRAM_IDENTIFIER         0x9F5A                  /*!< Application Program Identifier.<br>	- Format : b.<br> - Length : 1 to 16 bytes.<br> - Source : Icc. */
#define TAG_PAYWAVE_AVAILABLE_OFFLINE_SPENDING_AMOUNT      0x9F5D                  /*!< Available Offline Spending Amount.<br>	- Format : N.<br> - Length : 6 bytes.<br> - Source : Icc. */
#define TAG_PAYWAVE_TERMINAL_TRANSACTION_QUALIFIERS        0x9F66                  /*!< Indicates reader capabilities, requirements, and preferences to the card.<br> - Format : B.<br>	- Length : 4 bytes.<br> - Source : Terminal. */
#define TAG_PAYWAVE_CARD_ADDITIONNAL_PROCESSES             0x9F68                  /*!< Indicates card processing requirements and preferences.<br> - Format : B.<br> - Length : 4 bytes.<br> - Source : Icc. */
#define TAG_PAYWAVE_CARD_AUTHENTICATION_RELATED_DATA       0x9F69                  /*!< Contains the fDDA Version Number and Card Unpredictable Number.<br> - Format : B.<br> - Length : 1 to 16 bytes.<br> - Source : Icc. */
#define TAG_PAYWAVE_CARD_CVM_LIMIT                         0x9F6B                  /*!< Indicates that when card and reader currencies match and a contactless transaction exceeds this value, a CVM is required by the Card.<br> - Format : N.<br> - Length : 6 bytes.<br> - Source : Icc. */
#define TAG_PAYWAVE_CARD_TRANSACTION_QUALIFIERS            0x9F6C                  /*!< Used to indicate to the device which CVMs are requested by the card.<br> - Format : B.<br> - Length : 2 bytes.<br> - Source : Icc. */
#define TAG_PAYWAVE_VLP_RESET_THRESHOLD                    0x9F6D                  /*!< If Amount, Authorised is greater than VLP Available Funds minus this threshold, the card requests online processing.<br> - Format : N.<br> - Length : 6 bytes.<br> - Source : Icc. */
#define TAG_PAYWAVE_FORM_FACTOR_INDICATOR                  0x9F6E                  /*!< Indicates the form factor of the consumer payment device and the type of contactless interface over which the transaction was conducted.<br> - Format : B.<br> - Length : 4 bytes.<br> - Source : Icc. */
#define TAG_PAYWAVE_VLP_FUNDS_LIMIT                        0x9F77                  /*!< Value to which VLP Available Funds is reset.<br> - Format : N.<br> - Length : 6 bytes.<br>	- Source : Icc. */
#define TAG_PAYWAVE_VLP_SINGLE_TRANSACTION_LIMIT           0x9F78                  /*!< VLP Single Transaction Limit.<br> - Format : N.<br> - Length : 6 bytes.<br>	- Source : Icc. */
#define TAG_PAYWAVE_VLP_AVAILABLE_FUNDS                    0x9F79                  /*!< A counter that may be decremented (for LV or CTTA the funds may be added to CTTA) by the Amount, Authorized when an offline low-value qVSDC transaction takes place.<br> - Format : N.<br> - Length : 6 bytes.<br> - Source : Icc. */
#define TAG_PAYWAVE_CUSTOMER_EXCLUSIVE_DATA                0x9F7C                  /*!< Contains data for transmission to the Issuer in MSD transactions with a cryptogram.<br> - Format : B.<br> - Length : 1 to 32 bytes.<br>	- Source : Icc. */

//! @}


//! \addtogroup payWaveTagsDefinedBySpec
//! @{

//#define TAG_PAYWAVE_XXXXX                                0x9f918300 to 0x9f91837F  
#define TAG_PAYWAVE_QVSDC_NOT_ALLOWED                      0x9F918300              /*!< payWave kernel parameter : Set to true, the qVSDC doesn't perform the transaction.<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */
#define TAG_PAYWAVE_GPO_FORMAT_USED                        0x9F918301              /*!< Set to 1 in DataBase if format 1 is used = Cryptogram 17 management.<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */
#define TAG_PAYWAVE_ERROR_SFI_AUTH                         0x9F918302              /*!< Set to 1 in Database is an sfi error has been detected in the 70 template record.<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */
#define TAG_PAYWAVE_MAGSTRIPE_TRACK_2                      0x9F918303              /*!< Original Track 2 converted from the track 2 equivalent data.<br> - Format : B.<br> - Length : 1 to 70 bytes.<br> - Source : Terminal. */
#define TAG_PAYWAVE_MSD_CRYPTOGRAM_TYPE                    0x9F918304              /*!< Set to cryptogram type value.<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */
//#define TAG_UNUSED                                       0x9F918305              /* TAG_UNUSED. */
#define TAG_PAYWAVE_IS_SDA_SUPPORTED                       0x9F918306              /*!< payWave kernel parameter : Set to true, SDA method is supported by terminal.<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */
#define TAG_PAYWAVE_TERM_SUPPORTED_FDDA_VERSIONS           0x9f918307              /*!< payWave kernel parameter : list of FDA version supported by terminal.<br> - Format : B.<br> - Length : 1 to 2 bytes.<br> - Source : Terminal. */
#define TAG_PAYWAVE_FDDA_VERSION                           0x9F918308              /*!< Set in DataBase with the fDDA version supported.<br> - Format : B.<br> - Length : 1 to 2 bytes.<br> - Source : Terminal. */

#define TAG_PAYWAVE_CARD_TYPE                              0x9F918309              /*!< Set to C_PAYWAVE_CARD_TYPE_MSB_PAYWAVE + C_PAYWAVE_CARD_TYPE_LSB_UNKNOWN or C_PAYWAVE_CARD_TYPE_LSB_MSD or C_PAYWAVE_CARD_TYPE_LSB_QVSDC.<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */
#define TAG_PAYWAVE_ODA_INPUT_AUTHENTICATION_DATA          0x9F91830A              /*!< Buffer containing all the data to be authenticated.<br> - Format : B.<br> - Length : 1 to 3072 bytes.<br> - Source : Terminal. */
#define TAG_PAYWAVE_ODA_INPUT_DDOL_DATA                    0x9F91830B              /*!< Buffer containing all the data to be authenticated.<br> - Format : B.<br> - Length : 1 to 256 bytes.<br> - Source : Terminal. */
#define TAG_PAYWAVE_INT_SENT_APDU                          0x9F91830C              /*!< Un-indexed multi-tag : command list sent to the card.<br> - Format : B.<br> - Length : 1 to 261 bytes.<br> - Source : Terminal. */
#define TAG_PAYWAVE_INT_CARD_RESPONSE                      0x9F91830D              /*!< Un-indexed multi-tag : response list from the card.PAYWAVE_COMMON_MAX_COMMAND_LENGTH.<br> - Format : B.<br> - Length : 1 to 257 bytes.<br> - Source : Terminal. */
#define TAG_PAYWAVE_PBOC_MODE                              0x9F91830E              /*!< Specific card management with PAN SEQ NB set 2 times in the read records.<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */
#define TAG_PAYWAVE_TRACK_1                                0x9F91830F              /*!< Track 1 build by terminal.<br> - Format : B.<br> - Length : 27 to 79 bytes.<br> - Source : Terminal. */

#define TAG_PAYWAVE_ISSUER_SCRIPT_RESULT                   0x9F5B                  /*!< Bits field that indicates the result of Issuer Script Processing.<br> - Format : B.<br> - Length : from 1 to 50 bytes.<br> - Source : Terminal. */
#define TAG_PAYWAVE_ISSUER_SCRIPT_LIST                     0x9F918316              /*!< Scripts received from Issuer.<br> - Format : B.<br> - Length : 256 bytes.<br> - Source : Issuer. */
#define TAG_PAYWAVE_TERMINAL_ENTRY_CAPABILITY              0x9F918317              /*!< Terminal entry cababilities.<br> - Format : B.<br> - Length : 1 bytes.<br> - Source : Terminal. */
#define TAG_PAYWAVE_IS_TRANSACTION_LOG_SUPPORTED           0x9F918318              /*!< payWave kernel parameter : Set to true, Transaction Log is supported by terminal.<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */
#define TAG_PAYWAVE_TRANSACTION_LOG_RECORD		           0x9F918319              /*!< payWave Transaction Log (from card) storage.<br> - Format : B.<br> - Length : 263 bytes.<br> - Source : Icc. */
#define TAG_PAYWAVE_MSD_TAGS_NOT_MANAGED                   0x9F91831A              /*!< payWave kernel parameter : MSD list of tag to not managed in completion output buffer.<br> - Format : B.<br> - Length : 1 to 50 bytes.<br> - Source : Terminal. */
#define TAG_PAYWAVE_QVSDC_TAGS_NOT_MANAGED                 0x9F91831B              /*!< payWave kernel parameter : qVSDC list of tag to not managed in completion output buffer.<br> - Format : B.<br> - Length : 1 to 50 bytes.<br> - Source : Terminal. */
#define TAG_PAYWAVE_ODA_FAIL                               0x9F91831C              /*!< payWave kernel parameter : error is due to an Fdda Fail.<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */
#define TAG_PAYWAVE_DECLINED_BY_CARD                       0x9F91831D              /*!< payWave kernel parameter : error is due to a card AAC response.<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */
#define TAG_PAYWAVE_MSD_DISABLE_CVN17                      0x9F91831E              /*!< payWave kernel parameter : Set to true, CVN17 is not supported by terminal by payWave (MSD) kernel .<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */
#define TAG_PAYWAVE_ENABLE_INTERRUPT_ON_READ               0x9F91831F              /*!< payWave kernel parameter : Set to true, payWave transaction flow may be terminated by external request during read record step.<br> - Format : B.<br> - Length : 1 byte.<br> - Source : Terminal. */

//! @}


/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Glodal Data ////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////
