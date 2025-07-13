/**
 * \file	ClessSample_Fill.h
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

#ifndef __CLESS_SAMPLE_FILL_H__INCLUDED__
#define __CLESS_SAMPLE_FILL_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define C_SHARED_KERNEL_BUFFER_SIZE				18432		/*!< Maximum size of the shared buffer exchanged between this application and the kernels. */

#define LENGTH_OF_TRANSACTION_AMOUNT_AUTH_NUM			6
#define LENGTH_OF_TRANSACTION_AMOUNT_OTHER_NUM			6
#define LENGTH_OF_TRANSACTION_TYPE						1
#define LENGTH_OF_TRANSACTION_DATE						3
#define LENGTH_OF_TRANSACTION_TIME						3
#define LENGTH_OF_TRANSACTION_CURRENCY_CODE				2
#define LENGTH_OF_TRANSACTION_CURRENCY_EXPONENT			1
#define LENGTH_OF_IFD_SERIAL_NUMBER						8


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

typedef struct
{
	unsigned char bIsTransacTypePresent;			/*!< Generic transaction data : Indicates if the transaction type is present, empty or absent. */
	unsigned char ucTransactionType;				/*!< Generic transaction data : Transaction type. */
	unsigned char bIsCurrencyCodePresent;			/*!< Generic transaction data : Indicates if the currency code is present, empty or absent. */
	unsigned char ucTransactionCurrencyCode[2];		/*!< Generic transaction data : Transaction Currency Code. */
	unsigned char bIsCurrencyExpPresent;			/*!< Generic transaction data : Indicates if the currency exponent is present, empty or absent. */
	unsigned char ucTransactionCurrencyExponent;	/*!< Generic transaction data : Transaction Currency Exponent. */
	char ucTransactionCurrencyLabel[4];				/*!< Generic transaction data : Transaction Currency Label. */
	unsigned char bIsAmountAuthPresent;				/*!< Generic transaction data : Indicates if the transaction Amount Authorized is present, empty or absent. */
	unsigned long ulTransactionAmount;				/*!< Generic transaction data : Transaction Amount. */
	unsigned char bIsAmountOtherPresent;			/*!< Generic transaction data : Indicates if the transaction Amount Other is present, empty or absent. */
	unsigned long ulTransactionAmountOther;			/*!< Generic transaction data : Transaction Amount Other. */
	unsigned char bIsSerialNumberPresent;			/*!< Generic transaction data : Indicates if the interface serial number is present, empty or absent. */
	unsigned char ucIfdSerialNumber[8];				/*!< Generic transaction data : Payment Interface serial number. */
	unsigned char bIsDatePresent;					/*!< Generic transaction data : Indicates if the transaction date is present, empty or absent. */
	unsigned char ucTransactionDate[3];				/*!< Generic transaction data : Transaction date. */
	unsigned char bIsTimePresent;					/*!< Generic transaction data : Indicates if the transaction time is present, empty or absent. */
	unsigned char ucTransactionTime[3];				/*!< Generic transaction data : Transaction time. */
	unsigned char bIsTxnCategoryCodePresent;		/*!< Generic transaction data : Indicates if the Transaction Category Code is present, empty or absent. */
	unsigned char ucTxnCategoryCode;				/*!< Generic transaction data : Transaction Category Code. */
} T_PAYMENT_DATA_STRUCT;


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

extern T_SHARED_DATA_STRUCT * g_pKernelSharedBuffer;		/*!< Share exchange buffer used with the payment kernels. */


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Gives the transaction data structure.
//! \return The transaction data structure.

const T_PAYMENT_DATA_STRUCT * ClessSample_Fill_GetTransactionDataStructure (void);



//! \brief Gives transaction amount.
//! \return
//!		- \a transaction amount.
//! \note This function shall be called after having loaded the parameters.

unsigned long ClessSample_Fill_GiveAmount(void);



//! \brief Gives the money label.
//! \return
//!		- \a money label.
//! \note This function shall be called after having loaded the parameters.

char *ClessSample_Fill_GiveMoneyLabel(void);



//! \brief Gives the transaction type.
//! \return
//!		- \a transaction type.
//! \note This function shall be called after the transaction type has been populated.

unsigned char ClessSample_Fill_GiveTransactionType(void);



//! \brief Indicates if there is at least one AID in the parametres related to the specified kernel.
//! \param[in] nKernelIdentifier Kernel identifier.
//! \return
//!		- \a TRUE if at least one AID is present.
//!		- \a FALSE if not.
//! \note This function shall be called after having loaded the parameters.

int ClessSample_Fill_IsThereAidWithKernel (const int nKernelIdentifier);



//! \brief Save the some transaction only provided on CLESS_GIVE_INFO service.
//! \param[in] bIsAmountAuthPresent Indicates if the transaction amount authorised is present or not.
//! \param[in] ulAmountAuthBin Indicates the transaction amount (binary format) to save.
//! \param[in] bIsAmountOtherPresent Indicates if the transaction amount other is present or not.
//! \param[in] ulAmountOtherBin Indicates the transaction amount other (binary format) to save.
//! \param[in] bIsCurrencyCodePresent Indicates if the transaction currency code is present or not.
//! \param[in] pCurrencyCode Indicates the transaction currency code to save (shall be coded on 2 bytes).
//! \param[in] bIsCurrencyExpPresent Indicates if the transaction currency exponent is present or not.
//! \param[in] pCurrencyExponent Indicates the transaction type to save.
//! \param[in] bIsTransacTypePresent Indicates if the transaction type is present or not.
//! \param[in] pTransactionType Indicates the transaction type to save.
//! \param[in] bUseCurrentSn \a TRUE if the current SN shall be used, \a FALSE if \a bIsSerialNumberPresent and \a pIfdSerialNumber have to be used.
//! \param[in] bIsSerialNumberPresent Indicates if the interface serial number is present or not.
//! \param[in] pCurrencyLabel Indicates the currency label to save.
//!	\param[in] bIsTxnCategoryCodePresent Indicates if the Transaction Category Code is present or not.
//!	\param[in] pTxnCategoryCode Indicates the Transaction Category Code to save.

void ClessSample_Fill_PrepareAndSaveClessGiveInfoTransactionStaticData (const unsigned char bIsAmountAuthPresent, const unsigned long ulAmountAuthBin,
															const unsigned char bIsAmountOtherPresent, const unsigned long ulAmountOtherBin,
															const unsigned char bIsCurrencyCodePresent, const unsigned char * pCurrencyCode,
															const unsigned char bIsCurrencyExpPresent, const unsigned char * pCurrencyExponent,
															const unsigned char bIsTransacTypePresent, const unsigned char * pTransactionType,
															const unsigned char bUseCurrentSn, const unsigned char bIsSerialNumPresent,
															const char * pCurrencyLabel,
															const unsigned char bIsTxnCategoryCodePresent, const unsigned char * pTxnCategoryCode);



//! \brief Save the some transaction only provided on CLESS_GIVE_INFO service.
//! \param[in] bUseCurrentDate if \a TRUE, the function reads the current date and set the structure. Else (\a FALSE), the function uses the provided parameters.
//! \param[in] bIsDatePresent Indicates if the transaction date is present or not.
//! \param[in] bUseCurrentTime if \a TRUE, the function reads the current time and set the structure. Else (\a FALSE), the function uses the provided parameters.
//! \param[in] bIsTimePresent Indicates if the transaction time is present or not.

void ClessSample_Fill_PrepareAndSaveClessGiveInfoTransactionDynamicData (const unsigned char bUseCurrentDate, const unsigned char bIsDatePresent,
																		 const unsigned char bUseCurrentTime, const unsigned char bIsTimePresent);




//! \brief Init the shared buffre exchanged with the contactless kernels.
//! \param[in] pKernelSharedBuffer Shared exchange to be initialised.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int ClessSample_Fill_InitSharedBufferWithKernels (T_SHARED_DATA_STRUCT ** pSharedBuffer);



//! \brief Fill output buffer with data for _give_info use.
//! \param[out] Output TLV Tree filled with all the necessary data for Application Selection and card detection.
//! \param[in] pParamTlvTree TLV Tree containing all the parameters (supported AIDs, etc).
//! \param[in] bExplicitSelection \a TRUE if Explicit Selection is used. \a FALSE if Implicit Selection is used.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int ClessSample_Fill_GetApplicationSelectionParameters (TLV_TREE_NODE * pOuputTlvTree, TLV_TREE_NODE * pParamTlvTree, const unsigned int bExplicitSelection);



//! \brief Initialise the shared exchange buffer to be used with the kernel.
//! \param[out] pDataStruct Shared exchange structure filled with the generic transaction data.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int ClessSample_Fill_TransactionGenericData (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Get the correct AID parameters (to perform the transaction) according to the application selection result.
//! \param[out] pKernelDataStruct Shared buffer to be filled with the correct AID parameters (depending on the Application Selection results).
//! \param[in] pSharedStruct Shared buffer containing the application selection results.
//! \param[out] pKernelToUse Indicates the kernel to be used for the transaction.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int ClessSample_Fill_AidRelatedData (T_SHARED_DATA_STRUCT * pKernelDataStruct, T_SHARED_DATA_STRUCT * pSharedStruct, int * pKernelToUse);


//T_SHARED_DATA_STRUCT * ClessSample_Fill_CommonTransaction (T_SHARED_DATA_STRUCT * pDataStruct, int * pKernelToUse);




#endif // __CLESS_SAMPLE_FILL_H__INCLUDED__
