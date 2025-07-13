/**
 * \file	SDSA_Tags.h
 * \brief	Defines the SDSA application tags.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2010 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __SDSA_TAGS_H__INCLUDED__
#define __SDSA_TAGS_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup SDSA_Tags
//! @{

// Simple tags
#define TAG_SDSA_LIST_OF_OUTPUT_TAGS				0x9F918840		/*!< SDSA tag : list of tags to be returned at the end of the transaction (up to 256 bytes). If not provided, default tag list is returned. */
#define TAG_SDSA_LOADED_PARAMETERS_SHA				0x9F918841		/*!< SDSA tag : a SHA calculated on the loaded parameters. This SHA allows the terminal to be able to check if the parameters loaded in the device are coherent with its ones. */
#define TAG_SDSA_GET_PARAMETERS_SHA_ONLY			0x9F918842		/*!< SDSA tag : indicates if only the parameter SHA shall be retrieved or not (Boolean). If not present, all the parameters as well as the SHA are returned. */
#define TAG_SDSA_KERNEL_IDENTIFIER					0x9F918843		/*!< SDSA tag : idenfier of the kernel used to perform the transaction. */
#define TAG_SDSA_GET_ALL_DATA						0x9F918844		/*!< SDSA tag : indicates that all the kernel data is required. */
#define TAG_SDSA_STATUS_TO_NOTIFY					0x9F918845		/*!< SDSA tag : bit field (binary on 4 bytes), containing the status on which the caller wish to be notified. */
#define TAG_SDSA_CURRENT_TXN_STATUS					0x9F918846		/*!< SDSA tag : containing the value of the current transaction status. */
#define TAG_SDSA_GUI_STATE_TO_SET					0x9F918847		/*!< SDSA tag : indicating the GUI state to be set. */
#define TAG_SDSA_WAIT_CARD_REMOVAL					0x9F918848		/*!< SDSA tag : indicating if the reader shall wait the card removal or not (Boolean). */
#define TAG_SDSA_QUICK_GUI_MODE						0x9F918849		/*!< SDSA tag : indicates if the quick GUI mode must be used or not (if yes the GUI time will be minimized). */
#define TAG_SDSA_PARAMETERS_LABEL					0x9F91884A		/*!< SDSA tag : Indicates the parameter label. */
#define TAG_SDSA_GENERIC_MONEY_EXTENDED				0x9F91884B		/*!< SDSA tag : Defines a money. nom:3car, code:3car, decimal pos:1car, centseparator:1car, thousandseparator:1car, currencyposition:0after1before. - Format : t - Length : 10 bytes - Source : Terminal. */
#define TAG_SDSA_DOUBLE_DIP_TIMEOUT					0x9F91884C		/*!< SDSA tag : Indicates how soon the reader can accept the same card to perform the next transaction having the same amount. Time in milliseconds. (VisaWave requirement)*/
#define TAG_SDSA_NO_CARD_TIMEOUT					0x9F91884D		/*!< SDSA tag : Timout value for card detection process. Time in milliseconds. (VisaWave requirement)*/
#define TAG_SDSA_ZERO_CHECK_DEACTIVATED				0x9F91884E		/*!< SDSA tag : Set to true, payWave kernel doesn't realize the zero check with the Online cryptogram */
#define TAG_SDSA_TRANSACTION_CASHBACK				0x9F91884F		/*!< SDSA tag : Internal transaction cashback : kernel subset. */
#define TAG_SDSA_EXPRESSPAY_DOUBLE_TAP_TIME			0x9F918850		/*!< SDSA tag : To configure the period of time the contactless reader field is deactivated between the two taps of the Mobile CVM. Time in milliseconds. Range: one to three seconds (default 1.5 seconds). (Expresspay 3 requirement). */


// Constructed tags
#define TAG_SDSA_PARAM_AID_STRUCTURE				0xBF918840		/*!< SDSA tag : AID structure, node that contains each AID data. */
#define TAG_SDSA_PARAM_CA_KEY_STRUCTURE				0xBF918841		/*!< SDSA tag : CA key structure, node that contains each CA data. */
#define TAG_SDSA_PARAM_ICS_DATA_STRUCTURE			0xBF918842		/*!< SDSA tag : ICS data structure, tag that contains ICS related data . */
#define TAG_SDSA_PARAM_KERNEL_SPECIFIC_STRUCTURE	0xBF918843		/*!< SDSA tag : kernel specific data structure, node that contains each kernel specific data . */

#define TAG_SDSA_AID_PARAMETERS						0xBF918845		/*!< SDSA tag : AID subset. */
#define TAG_SDSA_CAKEYS_PARAMETERS					0xBF918846		/*!< SDSA tag : CAKEYS subset. */
#define TAG_SDSA_CAREVOK_PARAMETERS					0xBF918847		/*!< SDSA tag : CAREVOK subset. */
#define TAG_SDSA_ICS_PARAMETERS						0xBF918848		/*!< SDSA tag : global parameters (ICS) subset. */
#define TAG_SDSA_SPECIFIC_PARAMETERS				0xBF918849		/*!< SDSA tag : kernel subset. */

#define TAG_SDSA_PARAMETER_FILE_NODE				0xBF91884A		/*!< SDSA tag : node that contains a parameter file. */
#define TAG_SDSA_BLACKLIST_FILE_NODE				0xBF91884B		/*!< SDSA tag : node that contains a blacklist file. */

//! @}


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////



#endif // __SDSA_TAGS_H__INCLUDED__
