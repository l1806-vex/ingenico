/**
 * \file	SDSA_Defines.h
 * \brief	SDSA defines.
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

#ifndef __SDSA_DEFINES_H__INCLUDED__
#define __SDSA_DEFINES_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup TransactionType
//! @{

#define SDSA_TRANSACTION_TYPE_DEBIT					0x00		/*!< Definition of debit transaction type. */
#define SDSA_TRANSACTION_TYPE_CASH					0x01		/*!< Definition of cash transaction type. */
#define SDSA_TRANSACTION_TYPE_PURCH_WITH_CASHBACK   0x09        /*!< Definition of purchase with cashback transaction type. */
#define SDSA_TRANSACTION_TYPE_REFUND				0x20		/*!< Definition of refund transaction type. */

//! @}

//! \addtogroup KernelIdentifier
//! @{

#define SDSA_KERNEL_IDENTIFIER_UNKNOWN				0x00		/*!< Unknown kernel. */
#define SDSA_KERNEL_IDENTIFIER_PAYPASS				0x01		/*!< Indicates that PayPass Kernel was used to perform the transaction. */
#define SDSA_KERNEL_IDENTIFIER_PAYWAVE				0x02		/*!< Indicates that payWave Kernel was used to perform the transaction. */
#define SDSA_KERNEL_IDENTIFIER_VISAWAVE				0x03		/*!< Indicates that VisaWave Kernel was used to perform the transaction. */
#define SDSA_KERNEL_IDENTIFIER_EXPRESSPAY			0x04		/*!< Indicates that ExpressPay Kernel was used to perform the transaction. */
#define SDSA_KERNEL_IDENTIFIER_INTERAC  			0x05		/*!< Indicates that Interac Kernel was used to perform the transaction. */
#define SDSA_KERNEL_IDENTIFIER_DISCOVER				0x06		/*!< Indicates that Discover Kernel was used to perform the transaction. */
//! @}

//! \addtogroup PaymentStatus
//! @{

#define SDSA_PAYMENT_STATUS_NOT_STARTED				0x00000001	/*!< Mask indicating no payment is in progress.*/
#define SDSA_PAYMENT_STATUS_DETECT_CARD				0x00000002	/*!< Mask indicating card detection has been started.*/
#define SDSA_PAYMENT_STATUS_IN_PROGRESS				0x00000004	/*!< Mask indicating a card has been detected and transaction is in progress.*/
#define SDSA_PAYMENT_STATUS_COLLISION				0x00000008	/*!< Mask indicating if too many cards have been presented.*/
#define SDSA_PAYMENT_STATUS_RETRY					0x00000010	/*!< Mask indicating transaction is restarted due to communication error.*/
#define SDSA_PAYMENT_STATUS_DOUBLE_TAP				0x00000020	/*!< Mask indicating if a double tap is required.*/
#define SDSA_PAYMENT_STATUS_CARD_READ				0x00000040	/*!< Mask indicating if the interaction with the card is completed.*/

//! @}


//! \addtogroup PossibleScreens
//! @{

//! \addtogroup GenericScreens
//! @{

#define SDSA_SCREEN_IDLE							(1)				/*!< GUI state used for idle state. */
#define SDSA_SCREEN_PRESENT_CARD					(2)				/*!< GUI state used to ask the user to present the card. */
#define SDSA_SCREEN_RETRY							(3)				/*!< GUI state indicating transaction is restarted due to communication error. */
#define SDSA_SCREEN_USE_CONTACT						(4)				/*!< GUI state indicating that the transaction shall be conducted over another interface. */
#define SDSA_SCREEN_REMOVE_CARD						(5)				/*!< GUI state indicating that the interaction with the card is completed and card can be removed. */
#define SDSA_SCREEN_TIMEOUT_ELAPSED					(6)				/*!< GUI state indicating that no card has been presented and timeout is elapsed. */
#define SDSA_SCREEN_CANCELLED						(7)				/*!< GUI state indicating that the process has been cancelled. */
#define SDSA_SCREEN_PROCESSING						(8)				/*!< GUI state indicating that a card has been detected and transaction is in progress. */
#define SDSA_SCREEN_COLLISION						(9)				/*!< GUI state indicating that too many cards have been presented. */
#define SDSA_SCREEN_OFFLINE_APPROVED				(10)			/*!< GUI state indicating that transaction is offline approved. */
#define SDSA_SCREEN_ONLINE_APPROVED					(11)			/*!< GUI state indicating that transaction is online approved. */
#define SDSA_SCREEN_OFFLINE_DECLINED				(12)			/*!< GUI state indicating that transaction is offline declined. */
#define SDSA_SCREEN_ONLINE_DECLINED					(13)			/*!< GUI state indicating that transaction is online declined. */
#define SDSA_SCREEN_ONLINE_PIN_REQUIRED				(14)			/*!< GUI state indicating that Online PIN is required to perform the transaction. */
#define SDSA_SCREEN_SIGNATURE_REQUIRED				(15)			/*!< GUI state indicating that signature is required to perform the transaction. */
#define SDSA_SCREEN_CARD_NOT_SUPPORTED				(16)			/*!< GUI state indicating that the contactless card is not supported by the intelligent reader (there is no matching AID). */
#define SDSA_SCREEN_DISCONNECTED					(17)			/*!< GUI state indicating that the intelligent reader is disconnected. */
#define SDSA_SCREEN_CONNECTED						(18)			/*!< GUI state indicating that the intelligent reader disconnected. */

//! @}


//! \addtogroup payWaveScreens
//! @{

#define SDSA_PAYWAVE_SCREEN_STATUS_ERROR					(20)			/*!< GUI state indicating that the transaction status in invalid. */
#define SDSA_PAYWAVE_SCREEN_OFFLINE_APPROVED				(21)			/*!< GUI state indicating that the payWave transaction is offline approved. */
#define SDSA_PAYWAVE_SCREEN_OFFLINE_DECLINED				(22)			/*!< GUI state indicating that the payWave transaction is offline declined. */
#define SDSA_PAYWAVE_SCREEN_SIGNATURE_REQUIRED				(23)			/*!< GUI state indicating that signature is required to perform the payWave transaction. */
#define SDSA_PAYWAVE_SCREEN_SIGNATURE_OK					(24)			/*!< GUI state indicating that the signature is valid. */
#define SDSA_PAYWAVE_SCREEN_SIGNATURE_KO					(25)			/*!< GUI state indicating that the signature is not valid. */
#define SDSA_PAYWAVE_SCREEN_ONLINE_APPROVED_WITH_AOSA		(26)			/*!< GUI state indicating that the payWave transaction is online approved (Available Offline Spending Amount is displayed). */
#define SDSA_PAYWAVE_SCREEN_ONLINE_APPROVED_WITHOUT_AOSA	(27)			/*!< GUI state indicating that the payWave transaction is online approved (Available Offline Spending Amount is not displayed). */
#define SDSA_PAYWAVE_SCREEN_ONLINE_DECLINED					(28)			/*!< GUI state indicating that the payWave transaction is online declined. */
#define SDSA_PAYWAVE_SCREEN_ONLINE_PROCESSING				(29)			/*!< GUI state indicating that the payWave transaction is sent online for authorization. */
#define SDSA_PAYWAVE_SCREEN_PIN_KO							(30)			/*!< GUI state indicating that the entered PIN is invalid. */
#define SDSA_PAYWAVE_SCREEN_PIN_CANCELED					(31)			/*!< GUI state indicating PIN entry has been cancelled. */
#define SDSA_PAYWAVE_SCREEN_PHONE_INSTRUCTIONS				(32)			/*!< GUI state indicating that the user has to follow the instructions given on his contactless phone to continue the transaction. */
#define SDSA_PAYWAVE_SCREEN_ERROR							(33)			/*!< GUI state indicating that an error occurred. */

//! @}

//! \addtogroup VisaWaveScreens
//! @{

#define SDSA_VISAWAVE_SCREEN_STATUS_ERROR			(40)			/*!< GUI state indicating that the transaction status in invalid. */
#define SDSA_VISAWAVE_SCREEN_OFFLINE_APPROVED		(41)			/*!< GUI state indicating that the VisaWave transaction is offline approved. */
#define SDSA_VISAWAVE_SCREEN_OFFLINE_DECLINED		(42)			/*!< GUI state indicating that the VisaWave transaction is offline declined. */
#define SDSA_VISAWAVE_SCREEN_SIGNATURE_REQUIRED		(43)			/*!< GUI state indicating that signature is required to perform the VisaWave transaction. */
#define SDSA_VISAWAVE_SCREEN_SIGNATURE_OK			(44)			/*!< GUI state indicating that the signature is valid. */
#define SDSA_VISAWAVE_SCREEN_SIGNATURE_KO			(45)			/*!< GUI state indicating that the signature is not valid. */
#define SDSA_VISAWAVE_SCREEN_ONLINE_APPROVED		(46)			/*!< GUI state indicating that the VisaWave transaction is online approved. */
#define SDSA_VISAWAVE_SCREEN_ONLINE_DECLINED		(47)			/*!< GUI state indicating that the VisaWave transaction is online declined. */
#define SDSA_VISAWAVE_SCREEN_ONLINE_PROCESSING		(48)			/*!< GUI state indicating that the VisaWave transaction is sent online for authorization. */
#define SDSA_VISAWAVE_SCREEN_PIN_KO					(49)			/*!< GUI state indicating that the entered PIN is invalid. */
#define SDSA_VISAWAVE_SCREEN_ERROR					(50)			/*!< GUI state indicating that an error occurred. */
#define SDSA_VISAWAVE_SCREEN_RETRY					(51)			/*!< GUI state indicating transaction is restarted due to communication error. */
#define SDSA_VISAWAVE_SCREEN_COLLISION				(52)			/*!< GUI state indicating that too many cards have been presented. */
#define SDSA_VISAWAVE_SCREEN_USE_CONTACT			(53)			/*!< GUI state indicating that the transaction shall be conducted over another interface. */

//! @}

//! \addtogroup PayPassScreens
//! @{

#define SDSA_PAYPASS_SCREEN_APPROVED				(60)			/*!< GUI state indicating that the PayPass transaction is approved. */
#define SDSA_PAYPASS_SCREEN_OFFLINE_APPROVED		(61)			/*!< GUI state indicating that the PayPass transaction is offline approved. */
#define SDSA_PAYPASS_SCREEN_OFFLINE_DECLINED		(62)			/*!< GUI state indicating that the PayPass transaction is offline declined. */
#define SDSA_PAYPASS_SCREEN_ONLINE_PROCESSING		(63)			/*!< GUI state indicating that the PayPass transaction is sent online for authorization. */
#define SDSA_PAYPASS_SCREEN_ONLINE_APPROVED			(64)			/*!< GUI state indicating that the PayPass transaction is online approved. */
#define SDSA_PAYPASS_SCREEN_ONLINE_DECLINED			(65)			/*!< GUI state indicating that the PayPass transaction is online declined. */
#define SDSA_PAYPASS_SCREEN_SIGNATURE_REQUIRED		(66)			/*!< GUI state indicating that signature is required to perform the PayPass transaction. */
#define SDSA_PAYPASS_SCREEN_CARD_BLOCKED			(67)			/*!< GUI state indicating that the card is blocked and the PayPass transaction cannot be performed. */
#define SDSA_PAYPASS_SCREEN_APPLICATION_BLOCKED		(68)			/*!< GUI state indicating that the application in the card is blocked. */
#define SDSA_PAYPASS_SCREEN_OFFLINE_APPROVED_REFUND	(69)			/*!< GUI state indicating that the PayPass refund transaction is offline approved. */
#define SDSA_PAYPASS_SCREEN_ERROR_REFUND			(70)			/*!< GUI state indicating an error occured during the PayPass refund transaction. */
#define SDSA_PAYPASS_SCREEN_ERROR					(71)			/*!< GUI state indicating that an error occurred. */

//! @}

//! \addtogroup ExpressPayScreens
//! @{

#define SDSA_EXPRESSPAY_SCREEN_OFFLINE_APPROVED				(80)			/*!< GUI state indicating that the ExpressPay transaction is offline approved. */
#define SDSA_EXPRESSPAY_SCREEN_OFFLINE_DECLINED				(81)			/*!< GUI state indicating that the ExpressPay transaction is offline declined. */
#define SDSA_EXPRESSPAY_SCREEN_ONLINE_PROCESSING			(82)			/*!< GUI state indicating that the ExpressPay transaction is sent online for authorization. */
#define SDSA_EXPRESSPAY_SCREEN_ONLINE_APPROVED				(83)			/*!< GUI state indicating that the ExpressPay transaction is online approved. */
#define SDSA_EXPRESSPAY_SCREEN_ONLINE_DECLINED				(84)			/*!< GUI state indicating that the ExpressPay transaction is online declined. */
#define SDSA_EXPRESSPAY_SCREEN_ERROR						(85)			/*!< GUI state indicating that an error occurred. */
#define SDSA_EXPRESSPAY_SCREEN_SIGNATURE_REQUIRED			(86)			/*!< GUI state indicating that signature is required to perform the ExpressPay transaction. */
#define SDSA_EXPRESSPAY_SCREEN_APPROVED						(87)			/*!< GUI state indicating that the current processing is approved. */
#define SDSA_EXPRESSPAY_SCREEN_TRANSACTION_NOT_PERMITTED	(88)			/*!< OBSOLETE WITH KERNEL ExpressPay 3 - GUI state indicating that the contactless transaction is not permitted (Cardholder Verification is not successful and transaction is declined). */
#define SDSA_EXPRESSPAY_SCREEN_PROCESSING					(89)			/*!< GUI state indicating that a card has been detected and EMV Full Online transaction is in progress. */
#define SDSA_EXPRESSPAY_SCREEN_REMOVE_CARD					(90)			/*!< GUI state indicating that the interaction with the card is completed and card can be removed (EMV Full Online Authorization timer expires before a response is received from the Acquirer). */

//! @}

//! \addtogroup InteracScreens
//! @{

#define SDSA_INTERAC_SCREEN_IDLE							(100)			/*!< GUI state indicating that the Interac Reader is Idle. */
#define SDSA_INTERAC_SCREEN_PRESENT_CARD					(101)			/*!< GUI state indicating that the Interac transaction Requesting card presentation. */
#define SDSA_INTERAC_SCREEN_COLLISION						(102)			/*!< GUI state indicating that the Interac transacaction has been presented with more than one card. */
#define SDSA_INTERAC_SCREEN_NOT_SUPPORTED					(103)			/*!< GUI state indicating that the card is not supported. */
#define SDSA_INTERAC_SCREEN_USE_CONTACT						(104)			/*!< GUI state indicating that the Interac transaction is requesting card insertion. */
#define SDSA_INTERAC_SCREEN_TIMEOUT_ELAPSED					(105)			/*!< GUI state indicating that a card has not been presented . */

//! @}

//! @}

/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////



#endif // __SDSA_DEFINES_H__INCLUDED__
