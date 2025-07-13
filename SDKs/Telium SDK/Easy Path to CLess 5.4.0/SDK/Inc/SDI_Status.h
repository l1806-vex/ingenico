/**
 * \file	SDI_Status.h
 * \brief	Describes the different status returned by the SDI DLL when a function is called.
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

#ifndef __SDI_STATUS_H__INCLUDED__
#define __SDI_STATUS_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup SDI_Status
//! @{
#define SDI_STATUS_OK							0x0101			/*!< The function is correctly executed. */
#define SDI_STATUS_KO							0x0102			/*!< An error occurred. */
#define SDI_STATUS_BUSY							0x0103			/*!< The command cannot be executed because the device is busy. */
#define SDI_STATUS_DISCONNECTED					0x0104			/*!< The intelligent reader is not connected. */
#define SDI_STATUS_NOT_ALLOWED					0x0105			/*!< The function called cannot be processed. */
#define SDI_STATUS_APPROVED						0x0106			/*!< Transaction is approved. */
#define SDI_STATUS_DECLINED						0x0107			/*!< Transaction is offline declined. */
#define SDI_STATUS_ONLINE_REQUEST				0x0108			/*!< Transaction has to be sent online for authorization. */
#define SDI_STATUS_TERMINATED					0x0109			/*!< Transaction is terminated. */
#define SDI_STATUS_USE_OTHER_INTERFACE			0x010A			/*!< Transaction shall be conducted over another interface. */
#define SDI_STATUS_INVALID_DATA					0x010B			/*!< The provided data are not correct. */
#define SDI_STATUS_CANCELLED					0x010C			/*!< The process has been cancelled. */
#define SDI_STATUS_IN_PROGRESS					0x010D			/*!< An operation is already in progress (connection, transaction...). */
#define SDI_STATUS_NO_PARAMETER					0x010E			/*!< There is no loaded parameter in the intelligent reader. */
#define SDI_STATUS_NO_OPERATION_IN_PROGRESS		0x010F			/*!< There is no operation (transaction, status check...) in progress. */
#define SDI_STATUS_UNKNOWN_SERVICE				0x0110			/*!< The application identifier is not valid or the application in the intelligent reader does not implement the related service. */
#define SDI_STATUS_MISSING_DATA					0x0111			/*!< Mandatory data are missing. */
#define SDI_STATUS_NOT_ENOUGH_MEMORY			0x0112			/*!< There is not enough memory in the intelligent reader. */
#define SDI_STATUS_OUTPUT_BUFFER_TOO_SMALL		0x0113			/*!< The given ouput TlvTree is too small. */
#define SDI_STATUS_NO_CARD						0x0114			/*!< No card has been presented and timeout is elapsed. */
#define SDI_STATUS_CARD_BLOCKED					0x0115			/*!< Card is blocked and transaction cannot be performed. */
#define SDI_STATUS_APPLICATION_BLOCKED			0x0116			/*!< The application in the card is blocked. */
#define SDI_STATUS_NOT_SUPPORTED				0x0117			/*!< The provided value to be used is not supported (ie: language given in \ref SDI_System_SetLanguage() function parameter is not supported). */
#define SDI_STATUS_ANSWER_NOT_YET_RECEIVED		0x0118			/*!< The result is not yet received (transaction result, transaction status or card removal result). */
#define SDI_STATUS_CARD_NOT_SUPPORTED			0x0119			/*!< The contactless card is not supported by the intelligent reader (there is no matching AID). */
#define SDI_STATUS_CONTACTLESS_NOT_ALLOWED		0x0120			/*!< There is no AID allowed for the cless transaction is the intelligent reader (amount is greater than floor limit). */
#define SDI_STATUS_INVALID_PARAMETER            0x0121          /*!< A parameter is not correct */
#define SDI_STATUS_DLL_NOT_LOADED				0x01FF			/*!< The SDI DLL is not loaded. */
#define SDI_STATUS_UNKNOWN						0x0FFF			/*!< The status is unknown. */
//! @}

/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


#endif // __SDI_STATUS_H__INCLUDED__
