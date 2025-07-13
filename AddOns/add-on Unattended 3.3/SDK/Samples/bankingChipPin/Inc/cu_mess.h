/**
* \file cu_mess.h
* \brief This module contains the functions used for message management.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

#ifndef CU_MESS_H
#define CU_MESS_H

//! \defgroup Group_cu_mess Message management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define C_NBLANGHOLDER			3				//!< Number of managed languages for card holder.
#define C_NBLANGMERCH			4				//!< Number of managed languages for merchant.

#define C_LG_FRENCH				1				//!< French language definition.
/* #define C_LG_ENGLISH			0				// English language definition.
#define C_LG_SPANISH			2				// Spanish language definition.
#define C_LG_LOCAL				3*/				// Local language definition.

#define L_NBCURCY				34				//!< Number of managed currencies.

/* Currency identifier definition */
#define C_IEP_CURCY_BEF    0x0056				//!< Belgian franc currency.
#define C_IEP_CURCY_NLG    0x0528				//!< Netherlands guilder currency.
#define C_IEP_CURCY_CHF    0x0756				//!< Swiss franc currency.
#define C_IEP_CURCY_USD    0x0840				//!< US dollar currency.
#define C_IEP_CURCY_BRL    0x0076				//!< Brazilian real currency.
#define C_IEP_CURCY_CAD    0x0124				//!< Canadian dollar currency.
#define C_IEP_CURCY_AUD    0x0036				//!< Australian dollar currency.
#define C_IEP_CURCY_HKD    0x0344				//!< Hong Kong dollar currency.
#define C_IEP_CURCY_NZD    0x0554				//!< New Zealand dollar currency.
#define C_IEP_CURCY_ESP    0x0724				//!< Spanish peseta currency.
#define C_IEP_CURCY_FRF    0x0250				//!< French franc currency.
#define C_IEP_CURCY_ARS    0x0032				//!< Argentine peso currency.
#define C_IEP_CURCY_ATS    0x0040				//!< Austrian Schilling currency.
#define C_IEP_CURCY_CLP    0x0152				//!< Chilean peso currency.
#define C_IEP_CURCY_CLF    0x0990				//!< Chilean unidad de Fomento currency.
#define C_IEP_CURCY_CRC    0x0188				//!< Costa Rican colon currency.
#define C_IEP_CURCY_HRD    0x0191				//!< Croatian kuna currency.
#define C_IEP_CURCY_HNL    0x0340				//!< Lempira currency.
#define C_IEP_CURCY_INR    0x0356				//!< Indian rupee currency.
#define C_IEP_CURCY_IDR    0x0360				//!< Rupiah currency.
#define C_IEP_CURCY_ILS    0x0376				//!< Israeli new sheqel currency.
#define C_IEP_CURCY_LUF    0x0442				//!< Luxembourg franc currency.
#define C_IEP_CURCY_MYR    0x0458				//!< Malaysian ringgit currency.
#define C_IEP_CURCY_MXN    0x0484				//!< Mexican peso currency.
#define C_IEP_CURCY_NOK    0x0578				//!< Norwegian krone currency.
#define C_IEP_CURCY_PHP    0x0608				//!< Philippine peso currency.
#define C_IEP_CURCY_SEK    0x0752				//!< Swedish krona currency.
#define C_IEP_CURCY_THB    0x0764				//!< Thai Baht currency.
#define C_IEP_CURCY_TRL    0x0792				//!< Turkish lira currency.
#define C_IEP_CURCY_AED    0x0784				//!< United arab emirates dirham currency.
#define C_IEP_CURCY_XEU    0x0954				//!< European currency unit.
#define C_IEP_CURCY_EURO   0x0978				//!< European euro currency.
#define C_IEP_CURCY_HUF    0x0348				//!< Hungarian forint currency.
#define C_IEP_CURCY_POUND  0x0826				//!< Pound sterling currency.

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

//! \brief This structure defines the data used for currency configuration.
typedef struct
{
	unsigned short  currency;					//!< Currency identifier.
	char            label[4];					//!< Currency label to display.
	int             unit;						//!< Number of decimal to display. ( = 10 power unit)
} T_AppConfCurcy;

//! \brief Definition of the application configuration structure.
typedef struct
{
	int            i_MsgNumber;					//!< ID of the message associated to the tag.
	unsigned long  tag;							//!< Tag of the parameter.
}
S_TAB_ICS_CONFIG;

//! \brief This enumerator defines the different message tables.
typedef enum
{
	TERMINAL_TABLE = 0,							//!< ID of the table containing the terminal messages.
	RECEIPT_TABLE,								//!< ID of the table containing the receipt messages.
	STANDARD_TABLE,								//!< ID of the table containing the standard messages.
	DEFAULT_TABLE,								//!< ID of the table containing the default messages.
	ICS_TABLE,									//!< ID of the table containing the ICS messages.
	BATCH_STAT_TABLE,							//!< ID of the table containing the batch stat messages.
	BATCH_INIT_TABLE,							//!< ID of the table containing the batch init messages.
	CALL_RECEIPT_TABLE,							//!< ID of the table containing the call receipt messages.
	CONSULT_RECEIPT_TABLE,						//!< ID of the table containing the consult receipt messages.
	MAG_STRIPE_TABLE							//!< ID of the table containing the mag stripe messages.
#ifdef _TOOLWARE_
	,DEMO_MODE_TABLE							//!< ID of the table containing the demo mode messages.
#endif
}
CUMESS_TABLE_MESSAGE;

//! \brief Definition of the structure containing the language information. 
//! This structure is used for multilanguage management.
typedef struct
{
	unsigned char    iso639_code [3];			//!< 2 digits coding the language. ex : "en".
	unsigned char    lang_name [25];			//!< Name to be displayed on the menu. ex : "ENGLISH".
	unsigned char    table_id;					//!< Id in the messages tables. ex : 0.
}
t_lang_code;


/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */

extern const t_lang_code lang_table[C_NBLANGHOLDER];		//!< Table for multilangage management.

extern const S_TAB_ICS_CONFIG table_ics_config[];			//!< Table of messages.

extern unsigned long ul_InputAmount;						//!< Entered amount.

extern const T_AppConfCurcy ct_confCurrency[L_NBCURCY];		//!< Currency table.

/* ----------------------------------------------------------------------- */
/* To use those variables you have to use the function CUMESS_Read_Message */
/* The first param determine the variable which contains the messages      */
/* for example:                                                            */
/* use CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_TRY_AGAIN, lg_code)    */
/* ----------------------------------------------------------------------- */

extern const unsigned char TimeOutPINCode[];				//!< Definition of pin code timeout.

extern const unsigned char TimeOutInterCar[];				//!< Definition inter character timeout.

// All those following datas are reserved for a future use
// so they are useless for the moment
extern unsigned char ct_KernelSupportToolWare;				//!< If set to TRUE this variable indicates That the kernel is compiled with the Toolware.
extern unsigned char ct_SystemSupportToolWare;				//!< If set to TRUE this variable indicates That the system is compiled with the Toolware.
extern unsigned long ct_KernelVersion;						//!< Kernel version.
extern unsigned long ct_KernelCRC;							//!< Kernel CRC.
extern unsigned long ct_SystemVersion;						//!< System version.
extern unsigned long ct_SystemCRC;							//!< System CRC.

extern MSGinfos CurrentMSG;									//!< This global variable is used to store message informations.

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function initialises the messages management.
//===========================================================================
void CUMESS_Initialise(void);

//===========================================================================
//! \brief This function manages the amount entry.
//! \param[in] currency_code : ISO currency code.
//! \param[out] entered_amount : amount entered.
//! \return
//! - TRUE if amount is valid.
//! - FALSE otherwise.
//===========================================================================
int CUMESS_GetAmount (unsigned short currency_code, unsigned long *entered_amount);

//===========================================================================
//! \brief This function converts a binary value (a long), into a BCD value, 
//! on 6 characters.
//! \param[in] BinaryValue : binary value to convert.
//! \param[out] NumValue : converted value in BCD.
//===========================================================================
void CUMESS_ConvertBinNUM (unsigned long BinaryValue, unsigned char *NumValue);

//===========================================================================
//! \brief This function displays a standard message.
//! \param[in] xi_line : line number where to display the message.
//! \param[in] mess_code : number of the message to display.
//! \param[in] who : where to display message : 
//! - on the pinpad (DISPLAY_CARDHOLDER).
//! - on the merchant terminal (DISPLAY_MERCHANT_CARDHOLDER).
//===========================================================================
void CUMESS_Display_Message (int xi_line, unsigned char mess_code, unsigned char who);

//===========================================================================
//! \brief This function returns one message of the table CONSULT_RECEIPT_TABLE.
//! The message is defined by input parameters (number, language).
//! This function may be used only for printer messages.
//! \param[in] number : the index of the message in the table.
//! \param[in] language : language of the message.
//! \return
//! - The message, if it exists in the table.
//! - no_mess_found, if the message doesn't exist in the table.
//! - NULL if the language_table is NULL.
//===========================================================================
char *CUMESS_ReadMessageReceipt(int number, int language);

//===========================================================================
//! \brief This function returns the iso639 id in relation with the iso639 code.
//! \param[in] pc_x_IsoCode : iso639 code on two bytes.
//! \param[out] ps_x_IdCode : iso639 id code. Warning, this id code is not 
//! updated if iso code isn't found.
//===========================================================================
void CUMESS_GiveIso639Code(unsigned char * pc_x_IsoCode, unsigned short *ps_x_IdCode);


//===========================================================================
//! \brief This function returns one message from the message table given 
//! as parameter.
//! The message is defined by input parameters (num, language).
//! \param[in] table : table in which message is searched.
//! \param[in] num : the index of the message in the table.
//! \param[in] language : message language.
//! \return
//! - The message, if it exists in the table.
//! - no_mess_found, if the message doesn't exist in the table.
//! - NULL if the language_table is NULL.
//===========================================================================
// char *CUMESS_Read_Message(int num, int language);
char *CUMESS_Read_Message(CUMESS_TABLE_MESSAGE table, int num, int language);


//===========================================================================
//! \brief This function returns the message informations.
//! \param[in,out] ptr_MSGtest : pointer on the MSGinfos struct to update.
//! \param[in] num : the index of the message in the table.
//! \param[in] language : language of the message.
//===========================================================================
void CUMESS_Read_MsgInfos(MSGinfos * ptr_MSGtest, int num, int language);

//! @}

#endif

