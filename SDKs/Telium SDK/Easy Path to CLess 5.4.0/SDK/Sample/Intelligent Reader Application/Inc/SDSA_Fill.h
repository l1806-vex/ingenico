/**
 * \file	SDSA_Fill.h
 * \brief	This module is used to fill the structure with data necessary for transaction.
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

#ifndef __SDSA_FILL_H__INCLUDED__
#define __SDSA_FILL_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define C_SHARED_KERNEL_BUFFER_SIZE				16384		/*!< Maximum size of the shared buffer exchanged between this application and the kernels. */


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

typedef struct
{
	unsigned char ucTransactionType;				/*!< Generic transaction data : Transaction type. */
	unsigned char ucTransactionCurrencyCode[2];		/*!< Generic transaction data : Transaction Currency Code. */
	unsigned char ucTransactionCurrencyExponent;	/*!< Generic transaction data : Transaction Currency Exponent. */
	unsigned char ucTransactionCurrencyLabel[4];	/*!< Generic transaction data : Transaction Currency Label. */
	unsigned long ulTransactionAmountBin;			/*!< Generic transaction data : Transaction Amount (binary format). */
	unsigned long ulTransactionAmountOtherBin;		/*!< Generic transaction data : Transaction Amount Other (binary format). */
	unsigned char bIsAmountPresent;					/*!< Generic transaction data : Indicates if the transaction amount is present or not. */
	unsigned char ucIfdSerialNumber[8];				/*!< Generic transaction data : Payment Interface serial number. */
	unsigned char ucTransactionDate[3];				/*!< Generic transaction data : Transaction date. */
	unsigned char ucTransactionTime[3];				/*!< Generic transaction data : Transaction time. */
	unsigned char bIsAvailableAmountPresent;		/*!< Generic transaction data : Indicates if the transaction available amount is present or not. */
	unsigned long ulAvailableAmount;				/*!< Generic transaction data : Available Amount. */
} T_PAYMENT_DATA_STRUCT;


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

extern T_SHARED_DATA_STRUCT * g_pKernelSharedBuffer;		/*!< Share exchange buffer used with the payment kernels. */


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Gives the transaction data structure.
//! \return The transaction data structure.

const T_PAYMENT_DATA_STRUCT * SDSA_Fill_GetTransactionDataStructure (void);



//! \brief Gives transaction amount.
//! \return
//!		- \a transaction amount.

unsigned long SDSA_Fill_GiveAmount(void);



//! \brief Gives the money label.
//! \return
//!		- \a money label.
//! \note This function shall be called after having loaded the parameters.
unsigned char *SDSA_Fill_GiveMoneyLabel(void);



//! \brief Gives transaction type.
//! \return
//!		- \a transaction type.

unsigned char SDSA_Fill_GiveTransactionType(void);



//! \brief Indicates if there is at least one Visa AID in the parametres.
//! \return
//!		- \a TRUE if at least one Visa AID is present.
//!		- \a FALSE if not.
//! \note This function shall be called after having loaded the parameters.

int SDSA_Fill_IsThereVisaAid (void);



//! \brief Indicates if there is only Amex AIDs in the parameters.
//! \return
//!		- \a TRUE if only Amex AIDs are present.
//!		- \a FALSE if not.
//! \note This function shall be called after having loaded the parameters.

int SDSA_Fill_IsThereAmexAidOnly (void);



//! \brief Save some transaction data.
//! \param[in] bAmountPresent Indicates if the transaction amount is present or not.
//! \param[in] pTransactionType Indicates the transaction type to save.
//! \param[in] ucTransactionCashBack Indicates the specific transaction cashback type.
//! \param[in] pCurrencyCode Indicates the transaction currency code to save (shall be coded on 2 bytes).
//! \param[in] ucCurrencyExponent Indicates the transaction type to save.
//! \param[in] pCurrencylabel Indicates the currency label to save.
//! \param[in] pAmountAuthNum Indicates the transaction amount (numeric format) to save.
//! \param[in] pAmountOtherNum Indicates the transaction amount other (numeric format) to save.
//! \param[in] pIfdSerialNumber IFD serial number. If not provided, the Intelligent Reader one is used.
//! \param[in] pTransactionTime Transaction time.
//! \param[in] pTransactionDate Transaction date.
//! \param[in] pTransactionSeqCounter Transaction sequence counter.
//! \param[in] nLastPANLength Length of the PAN used for the last transaction (VisaWave need).
//! \param[in] pLastPAN PAN used for the last transaction (VisaWave need).

void SDSA_Fill_PrepareAndSaveClessGiveInfoTransactionData (const unsigned char bAmountPresent, const unsigned char * pTransactionType,  
																  const unsigned char * pTransactionCashBack, const unsigned char * pCurrencyCode,
																  const unsigned char ucCurrencyExponent, const unsigned char * pCurrencyLabel,
																  const unsigned char * pAmountAuthNum, const unsigned char * pAmountOtherNum,
																  const unsigned char * pIfdSerialNumber, const unsigned char * pTransactionTime,
																  const unsigned char * pTransactionDate, const unsigned char * pTransactionSeqCounter,
																  const unsigned int nLastPANLength, const unsigned char * pLastPAN);


//! \brief Save the available amount returned by the card (if available).
//! \brief This value could be used when displaying transaction result for example.
//! \param[in] nVisa Indicates if it is a payWave or a VisaWave transaction.
//! \param[in] pDataStruct share buffer with tags informations.

void SDSA_Fill_SaveAvailableAmount (int nVisa, T_SHARED_DATA_STRUCT * pDataStruct);


//! \brief Init the shared buffre exchanged with the contactless kernels.
//! \param[in] pKernelSharedBuffer Shared exchange to be initialised.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

int SDSA_Fill_InitSharedBufferWithKernels (T_SHARED_DATA_STRUCT ** pSharedBuffer);



//! \brief Fill output buffer with data for _give_info use.
//! \param[out] Output TLV Tree filled with all the necessary data for Application Selection and card detection.
//! \param[in] pParamTlvTree TLV Tree containing all the parameters (supported AIDs, etc).
//! \param[in] bExplicitSelection \a TRUE if Explicit Selection is used. \a FALSE if Implicit Selection is used.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

int SDSA_Fill_GetApplicationSelectionParameters (TLV_TREE_NODE * pOuputTlvTree, TLV_TREE_NODE * pParamTlvTree, const unsigned int bExplicitSelection);



//! \brief Initialise the shared exchange buffer to be used with the kernel.
//! \param[out] pDataStruct Shared exchange structure filled with the generic transaction data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

int SDSA_Fill_TransactionGenericData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Get the correct AID parameters (to perform the transaction) according to the application selection result.
//! \param[out] pKernelDataStruct Shared buffer to be filled with the correct AID parameters (depending on the Application Selection results).
//! \param[in] pSharedStruct Shared buffer containing the application selection results.
//! \param[out] pKernelToUse Indicates the kernel to be used for the transaction.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occured.

int SDSA_Fill_AidRelatedData (T_SHARED_DATA_STRUCT * pKernelDataStruct, T_SHARED_DATA_STRUCT * pSharedStruct, int * pKernelToUse);


#endif // __SDSA_FILL_H__INCLUDED__
