/**
 * \file	ClessSample_Customisation.h
 * \brief 	Manages the kernel customisation.
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


#ifndef __CLESS_SAMPLE_CUSTOMISATION_H__INCLUDED__
#define __CLESS_SAMPLE_CUSTOMISATION_H__INCLUDED__

/////////////////////////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////////////////////////

#define CLESS_SAMPLE_CUST_UNKNOWN			0x00		/*!< Indicates current transaction has an unknown type. */
#define CLESS_SAMPLE_CUST_PAYPASS			0x01		/*!< Indicates current transaction is PayPass. */
#define CLESS_SAMPLE_CUST_PAYWAVE			0x02		/*!< Indicates current transaction payWave. */
#define CLESS_SAMPLE_CUST_VISAWAVE			0x03		/*!< Indicates current transaction VisaWave. */
#define CLESS_SAMPLE_CUST_EXPRESSPAY		0x04		/*!< Indicates current transaction is ExpressPay. */
#define CLESS_SAMPLE_CUST_DISCOVER			0x05		/*!< Indicates current transaction is Discover. */
#define CLESS_SAMPLE_CUST_INTERAC			0x06		/*!< Indicates current transaction is Interac. */

/////////////////////////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Global data definitions ////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////////////////////////

//! \brief Set the used payment scheme.
//! \param[in] ucUsedScheme Indicates the used scheme.

void ClessSample_Customisation_SetUsedPaymentScheme (const unsigned char ucUsedScheme);



//! \brief Set the used payment scheme.
//! \return The used scheme.
//!		\a CLESS_SAMPLE_CUST_UNKNOWN Scheme is not yet known.
//!		\a CLESS_SAMPLE_CUST_PAYPASS Scheme is PayPass.
//!		\a CLESS_SAMPLE_CUST_PAYWAVE Scheme is payWave.
//!		\a CLESS_SAMPLE_CUST_DISCOVER Scheme is Discover.
//!		\a CLESS_SAMPLE_CUST_INTERAC Scheme is Interac.

unsigned char ClessSample_Customisation_GetUsedPaymentScheme (void);



//! \brief Perform the kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \return
//!		- \a CLESS_CUST_CONTINUE always.

int ClessSample_Customisation_Process (T_SHARED_DATA_STRUCT * pSharedData);



//! \brief Function called for application selection processing customisation.
//! \param[in] pDataStruct Shared exchange structure provided with customisation information.
//! \return
//! 	- CLESS_CUST_DEFAULT to use the default processing. 
//! 	- CLESS_CUST_RETRY_WITH_CLESS if the transaction shall be restarted.
//! 	- CLESS_CUST_RETRY_WITHOUT_CLESS if transaction shall be restarted without cless.
//! 	- CLESS_CUST_STOP if the transaction shall be stopped.
//! 	- CLESS_CUST_NEXT_METHOD if next application selection method shall be used (if present). 
//! 	- CLESS_CUST_CONTINUE_METHOD if next application selection criteria shall be used. 

int ClessSample_Customisation_CustAsProc (T_SHARED_DATA_STRUCT * pDataStruct);


//! \brief This function is called to customise the GUI during the DLL processing.
//! \param[in] pDataStruct Shared buffer containing data necessary to customise the step.
//! \return
//!	- \ref CLESS_CUST_DEFAULT if default DLL GUI shall be executed.
//!	- \ref CLESS_CUST_CONTINUE if application made customisation and default DLL GUI shall not be executed.

/*int ClessSample_Customisation_SelectionGui (T_SHARED_DATA_STRUCT * pDataStruct);*/

//! \brief This function is called to customise the GUI during the DLL processing for Interac.
//! \param[in] pDataStruct Shared buffer containing data necessary to customise the step.
//! \return
//!	- \ref CLESS_CUST_DEFAULT if default DLL GUI shall be executed.
//!	- \ref CLESS_CUST_CONTINUE if application made customisation and default DLL GUI shall not be executed.

int ClessSample_Customisation_Interac_SelectionGui (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Set the global data indicating double tap is in progress.
//! \param[in] bDoubleTapInProgress \ref TRUE if double tap is in progress, \ref FALSE else.

void ClessSample_Customisation_SetDoubleTapInProgress (const unsigned char bDoubleTapInProgress);

//! \brief Indicates if double tap is in progress or not.
//! \return
//!	- \ref TRUE if double tap is in progress.
//!	- \ref FALSE else.

unsigned char ClessSample_Customisation_GetDoubleTapInProgress (void);



//! \brief This function is called to customise the GUI during the DLL processing for Visa Asia.
//! \brief Customisation is different according to the GUI mode used (specific GUI for Visa Asia)
//! \brief Customisation is different according to the selection mode (implicit or explicit)
//! \param[in] pDataStruct Shared buffer containing data necessary to customise the step.
//! \return
//!	- \ref CLESS_CUST_DEFAULT if default DLL GUI shall be executed.
//!	- \ref CLESS_CUST_CONTINUE if application made customisation and default DLL GUI shall not be executed.

int ClessSample_Customisation_VisaAsia_SelectionGui (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief This function is called to customise the GUI during the DLL processing.
//! \brief Customisation is different according to the GUI mode used (specific GUI for Visa Asia)
//! \brief Customisation is different according to the selection mode (implicit or explicit)
//! \param[in] pDataStruct Shared buffer containing data necessary to customise the step.
//! \return
//!	- \ref CLESS_CUST_DEFAULT if default DLL GUI shall be executed.
//!	- \ref CLESS_CUST_CONTINUE if application made customisation and default DLL GUI shall not be executed.

int ClessSample_Customisation_Generic_SelectionGui (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Analyse the application selection result and set the transaction result.
//! \param[in] nApplicationSelectionResult Application selection result.
//! \return The transaction result.

int ClessSample_Customisation_AnalyseApplicationSelectionResult (int nApplicationSelectionResult);



//! \brief Perform the kernel data exchange.
//! \param[in,out] pSharedData Shared buffer used for data exchange (DET and DEK processing).
//! \return
//!		- \a CLESS_CUST_CONTINUE always.

int ClessSample_Customisation_Data_Exchange (T_SHARED_DATA_STRUCT * pSharedData);


#endif // __CLESS_SAMPLE_CUSTOMISATION_H__INCLUDED__
