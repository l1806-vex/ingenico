/**
 * \file	SDM_Services.h
 * \brief	Describes the services available for applications in the Intelligent Reader.
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

#ifndef __SDM_SERVICES_H__INCLUDED__
#define __SDM_SERVICES_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


//! \addtogroup PaymentServices
//! @{

#define SERVICE_PAYMENT_DO_TXN						0x1E10		/*!< Perform the transaction. */
#define SERVICE_PAYMENT_CANCEL_TXN					0x1E11		/*!< Cancel the transaction initiated with the \ref SERVICE_PAYMENT_DO_TXN or the \ref SERVICE_PAYMENT_TXN_POST_PROCESSING service. */
#define SERVICE_PAYMENT_LOAD_PARAMS					0x1E12		/*!< Load all the parameters. */
#define SERVICE_PAYMENT_GET_PARAMS					0x1E13		/*!< Get the loaded parameters. */
#define SERVICE_PAYMENT_ERASE_PARAMS				0x1E14		/*!< Erase the parameters. */
#define SERVICE_PAYMENT_GET_DATA					0x1E15		/*!< Get transaction data. */
#define SERVICE_PAYMENT_CLEAR_DATA					0x1E16		/*!< Clear the transaction data. */
#define SERVICE_PAYMENT_SET_GUI_STATE				0x1E17		/*!< Sets the GUI into the required state. */
#define SERVICE_PAYMENT_CARD_REMOVAL				0x1E18		/*!< Perform the card removal. */
#define SERVICE_PAYMENT_TXN_POST_PROCESSING			0x1E19		/*!< Perform the transaction post processing (if applicable, and depending on the payment scheme). */
#define SERVICE_PAYMENT_GET_STATUS					0x1E1A		/*!< Get the transaction status. */
#define SERVICE_PAYMENT_GET_STATUS_CANCEL			0x1E1B		/*!< Cancel the retrieval started with the \ref SERVICE_PAYMENT_GET_STATUS service. */

//! @}


//! \addtogroup GenericServices
//! @{

#define SERVICE_GENERIC_USER_CMD_01					0x1E20		/*!< Generic User Command number 1. */
#define SERVICE_GENERIC_USER_CMD_02					0x1E21		/*!< Generic User Command number 2. */
#define SERVICE_GENERIC_USER_CMD_03					0x1E22		/*!< Generic User Command number 3. */
#define SERVICE_GENERIC_USER_CMD_04					0x1E23		/*!< Generic User Command number 4. */
#define SERVICE_GENERIC_USER_CMD_05					0x1E24		/*!< Generic User Command number 5. */
#define SERVICE_GENERIC_USER_CMD_06					0x1E25		/*!< Generic User Command number 6. */
#define SERVICE_GENERIC_USER_CMD_07					0x1E26		/*!< Generic User Command number 7. */
#define SERVICE_GENERIC_USER_CMD_08					0x1E27		/*!< Generic User Command number 8. */

//! @}


//! \addtogroup StateServices
//! @{

#define SERVICE_STATE_READER_CONNECTED				0x1E30		/*!< Perform GUI when reader is connected. If not defined, a default GUI is performed by the intelligent reader. */
#define SERVICE_STATE_READER_DISCONNECTED			0x1E31		/*!< Perform GUI when reader is disconnected. If not defined, a default GUI is performed by the intelligent reader. */

//! @}



//! \addtogroup DataExchangeServices
//! @{

#define SERVICE_DATA_EXCHANGE_GET_DEK_START			0x1E40		/*!< Get the DEK signals. */
#define SERVICE_DATA_EXCHANGE_GET_DEK_STOP			0x1E41		/*!< Stop the retrieval of DEK signals. */
#define SERVICE_DATA_EXCHANGE_IS_CANCEL_START		0x1E42		/*!< Check if the Data Exchange processing must be cancelled. */
#define SERVICE_DATA_EXCHANGE_IS_CANCEL_STOP		0x1E43		/*!< Stop the Cancel processing. */
#define SERVICE_DATA_EXCHANGE_SEND_DET				0x1E44		/*!< Send a DET signal. */

//! @}


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

//! \brief Structure describing the header for service call between application and protocol
typedef struct
{
	unsigned short m_usAppliType;	/*!< Application type to be called. */
	unsigned short m_usService;		/*!< Service to be called. */
	unsigned long m_ulRuf1;			/*!< RUF1. */
	unsigned long m_ulRuf2;			/*!< RUF2. */
	unsigned long m_ulRuf3;			/*!< RUF3. */
} SDM_SERVICE_HEADER;


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


#endif // __CLESS_SDM_SERVICES_H__INCLUDED__
