/**
 * \file	CLESS_SAMPLE_GuiState.h
 * \brief 	Gui state management functions.
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


/////////////////////////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////////////////////////

// Screen definitions
#define CLESS_SAMPLE_SCREEN_IDLE								(1)				/*!<  */
#define CLESS_SAMPLE_SCREEN_PRESENT_CARD						(2)				/*!<  */
#define CLESS_SAMPLE_SCREEN_RETRY								(3)				/*!<  */
#define CLESS_SAMPLE_SCREEN_USE_CONTACT							(4)				/*!<  */
#define CLESS_SAMPLE_SCREEN_REMOVE_CARD							(5)				/*!<  */
#define CLESS_SAMPLE_SCREEN_WAIT_CARD_REMOVAL					(6)				/*!<  */
#define CLESS_SAMPLE_SCREEN_TIMEOUT_ELAPSED						(7)				/*!<  */
#define CLESS_SAMPLE_SCREEN_CANCELLED							(8)				/*!<  */
#define CLESS_SAMPLE_SCREEN_PROCESSING							(9)				/*!<  */
#define CLESS_SAMPLE_SCREEN_COLLISION							(10)			/*!<  */
#define CLESS_SAMPLE_SCREEN_ONLINE_APPROVED						(11)			/*!<  */
#define CLESS_SAMPLE_SCREEN_ONLINE_PIN_REQUIRED					(12)			/*!<  */
#define CLESS_SAMPLE_SCREEN_SIGNATURE_REQUIRED					(13)			/*!<  */
#define CLESS_SAMPLE_SCREEN_ERROR           					(14)			/*!<  */
#define CLESS_SAMPLE_SCREEN_CARD_BLOCKED				        (15)			/*!<  */
#define CLESS_SAMPLE_SCREEN_APPLICATION_BLOCKED                 (16)            /*!<  */
#define CLESS_SAMPLE_SCREEN_OFFLINE_APPROVED			        (17)			/*!<  */
#define CLESS_SAMPLE_SCREEN_OFFLINE_DECLINED			        (18)			/*!<  */
#define CLESS_SAMPLE_SCREEN_ONLINE_PROCESSING			        (19)			/*!<  */
#define CLESS_SAMPLE_SCREEN_ONLINE_DECLINED				        (20)			/*!<  */
#define CLESS_SAMPLE_SCREEN_PIN_CANCEL					        (21)			/*!<  */
#define CLESS_SAMPLE_SCREEN_PIN_ERROR					        (22)			/*!<  */
#define CLESS_SAMPLE_SCREEN_ERASE_CUSTOMER				        (23)			/*!<  */
#define CLESS_SAMPLE_SCREEN_USER                		        (24)			/*!<  */
#define CLESS_SAMPLE_SCREEN_KEYBOARD                            (25)			/*!<  */
#define CLESS_SAMPLE_SCREEN_ERROR_STATUS				        (26)			/*!<  */
#define CLESS_SAMPLE_SCREEN_BATCH_ERROR        		            (27)			/*!<  */
#define CLESS_SAMPLE_SCREEN_REPRESENT_CARD						(28)			/*!<  */
#define CLESS_SAMPLE_SCREEN_ONLINE_UNABLE				        (29)			/*!<  */
#define CLESS_SAMPLE_SCREEN_REMOVE_CARD_TWO_LINES				(30)			/*!<  */
#define CLESS_SAMPLE_SCREEN_TRY_ANOTHER_CARD					(31)			/*!<  */
#define CLESS_SAMPLE_SCREEN_PHONE_INSTRUCTIONS					(32)			/*!<  */
#define CLESS_SAMPLE_SCREEN_PHONE_INSTRUCTIONS_RETRY			(33)			/*!<  */

#define CLESS_SAMPLE_PAYPASS_SCREEN_SIGNATURE_REQUIRED			(63)			/*!<  */
#define CLESS_SAMPLE_PAYPASS_SCREEN_OFFLINE_APPROVED_REFUND		(66)			/*!<  */
#define CLESS_SAMPLE_PAYPASS_SCREEN_ERROR_REFUND				(67)			/*!<  */
#define CLESS_SAMPLE_PAYPASS_SCREEN_APPROVED					(68)			/*!<  */
#define CLESS_SAMPLE_PAYPASS_SCREEN_SIGNATURE_OK				(69)			/*!<  */
#define CLESS_SAMPLE_PAYPASS_SCREEN_SIGNATURE_KO				(70)			/*!<  */
#define CLESS_SAMPLE_PAYPASS_SCREEN_AUTHORISING					(71)			/*!<  */
#define CLESS_SAMPLE_PAYPASS_SCREEN_DECLINED					(72)			/*!<  */
#define CLESS_SAMPLE_PAYPASS_SCREEN_REMOVE						(73)			/*!<  */
#define CLESS_SAMPLE_PAYPASS_SCREEN_REMOVE_CARD_DS_OPERATION	(74)			/*!<  */
#define CLESS_SAMPLE_PAYPASS_SCREEN_WAIT_CARD_REMOVAL			(75)			/*!<  */

#define CLESS_SAMPLE_SCREEN_CARD_NOT_SUPPORTED					(131)           /*!<  */
#define CLESS_SAMPLE_SCREEN_EMPTY_UPP							(132)			/*!<  */


/////////////////////////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////////////////////////

typedef struct
{
	int nMerchantLanguage;			/*!< Merchant language. */
	int nCardholderLanguage;		/*!< Cardholder language. */
	int bCardholderLanguageDefined;	/*!< Indicates if the cardholder language had been defined. */
} T_SAMPLE_TRANSACTION_LANGUAGE;


/////////////////////////////////////////////////////////////////////////////////////
//// Global data definitions ////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////////////////////////

//! \brief Initialise the language structure.

void ClessSample_GuiState_InitLanguageStructure (void);



//! \brief Get the merchant language.
//! \return The merchant language.

int ClessSample_GuiState_GetMerchantLanguage (void);



//! \brief Get the cardholder language.
//! \return The cardholder language.

int ClessSample_GuiState_GetCardholderLanguage (void);



//! \brief Set the application language with the cardholder language if present, else with the merchant language.
//! \param[in] pPreferredLanguage Indicates the preferred language if already extracted.

void ClessSample_GuiState_SetCardholderLanguage (unsigned char * pPreferredLanguage);



//! \brief This function displays a screen on the display.
//! \param[in] ulScreenIdentifier Screen identifier.

void ClessSample_GuiState_DisplayScreen (unsigned long ulScreenIdentifier, int nMerchantLang, int nCardholderLang);



//! \brief This function displays a screen on the display.
//! \param[in] ulScreenIdentifier Screen identifier.
//! \param[in] nMerchantLang Merchant language. \a -1 if unknown.
//! \param[in] nCardholderLang Cardholder language. \a -1 if unknown.

void ClessSample_GuiState_DisplayScreenText (unsigned long ulScreenIdentifier, int nMerchantLang, int nCardholderLang);
