/**
 * \file	CST_Term.h
 * \brief 	Module for messages management.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __CST_TERM_H__INCLUDED__
#define __CST_TERM_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define YESCLEAR					TRUE
#define NOCLEAR						FALSE

#define LONGLINE					TRUE
#define SHORTLINE					FALSE

// Name of the messages file that can be loaded in the terminal for messages customisation
#define CST_MSG_FILE				"/SYSTEM/CSTMSG"	

// Terminal types (according to EMV)
#define CST_TERM_TYPE_FINANCIAL_ATT_ONLINE_ONLY			0x11	/*!< Terminal Type - Financial, Attended, Online only. */
#define CST_TERM_TYPE_FINANCIAL_UNATT_ONLINE_ONLY		0x14	/*!< Terminal Type - Financial, Unattended, Online only. */
#define CST_TERM_TYPE_MERCHANT_ATT_ONLINE_ONLY			0x21	/*!< Terminal Type - Merchant, Attended, Online only. */
#define CST_TERM_TYPE_MERCHANT_UNATT_ONLINE_ONLY		0x24	/*!< Terminal Type - Merchant, Unattended, Online only. */
#define CST_TERM_TYPE_CARDHOLDER_UNATT_ONLINE_ONLY		0x34	/*!< Terminal Type - Cardholder, Unattended, Online only. */


//// Types //////////////////////////////////////////////////////


//// Global variables ///////////////////////////////////////////


//// Functions //////////////////////////////////////////////////

//! \brief This function display a text line in graphic mode. 
//! \param[in] xp_line : line index.
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment : center, left, rigth, ....
//! \param[in] bmode : YESCLEAR to erase before display something, else nothing
//! \param[in] c_l_LongLine : TRUE for long line to display (little police will be used), FALSE else.

void CST_Term_DisplayGraphicLine(int xi_line, MSGinfos * ptrMSG, int nAlignment, unsigned char bmode, unsigned char bLongLine);



//! \brief This function initialise Messages menagement. 

void CST_Term_Initialise(void);



//! \brief Define the application language with the Manager language. 

void CST_Term_SetMerchantLanguage (void);



//! \brief Set the intelligent reader date and time with the date and time of the terminal.

void CST_Term_SetReaderDateAndTime(void);



//! \brief Get and save the money label that corresponds to the given currency code.
//! \param[in] pCurrencyLabel Currency code used for the current transaction.

void CST_Term_SetMoneyLabel(unsigned char *pCurrencyLabel);



//! \brief Gives the money label.
//! \return
//!		- \a money label.
//! \note This function shall be called after having loaded the parameters.

char *CST_Term_GiveMoneyLabel(void);



//! \brief Get a specific information in a shared buffer.
//! \param[in] pResultDataStruct Shared exchange buffer from which the tag shall be extracted.
//! \param[in] ulTag Tag that shall be extracted.
//! \param[out] pInfo pointer to the requested value
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

int CST_Term_RetreiveInfo (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned long ulTag, unsigned char ** pInfo);



//! \brief Get all the kernel data in a buffer.
//!	\param[in] pDataStruct Buffer to be filled witgh the kernel data.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

int CST_Term_GetAllData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Establishes the connection with the intelligent reader (try on USB port, and then try on serial port).

void CST_Term_ConnectAll(void);

#endif //__CST_TERM_H__INCLUDED__
