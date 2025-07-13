/**
 * \file	SDSA_Customisation.h
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


#ifndef __SDSA_CUSTOMISATION_H__INCLUDED__
#define __SDSA_CUSTOMISATION_H__INCLUDED__

/////////////////////////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Global data definitions ////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////////////////////////

//! \brief Set the used payment scheme.
//! \param[in] ucUsedScheme Indicates the used scheme.

void SDSA_Customisation_SetUsedPaymentScheme (const unsigned char ucUsedScheme);



//! \brief Get the used payment scheme.
//! \return The used scheme.
//!		\a SDSA_KERNEL_IDENTIFIER_UNKNOWN Scheme is not yet known.
//!		\a SDSA_KERNEL_IDENTIFIER_PAYPASS Scheme is PayPass.
//!		\a SDSA_KERNEL_IDENTIFIER_PAYWAVE Scheme is payWave.
//!		\a SDSA_KERNEL_IDENTIFIER_VISAWAVE Scheme is VisaWave.
//!		\a SDSA_KERNEL_IDENTIFIER_EXPRESSPAY Scheme is ExpressPay.

unsigned char SDSA_Customisation_GetUsedPaymentScheme (void);



//! \brief Perform the kernel customisation.
//! \param[in,out] pSharedData Shared buffer used for customisation.
//! \return
//!		- \a CLESS_CUST_CONTINUE always.

int SDSA_Customisation_Process (T_SHARED_DATA_STRUCT * pSharedData);



//! \brief This function is called to customise the GUI during the DLL processing.
//! \brief Customisation is different according to the GUI mode used (specific GUI for Visa Asia)
//! \brief Customisation is different according to the selection mode (implicit or explicit)
//! \param[in] pDataStruct Shared buffer containing data necessary to customise the step.
//! \return
//!	- \ref CLESS_CUST_DEFAULT if default DLL GUI shall be executed.
//!	- \ref CLESS_CUST_CONTINUE if application made customisation and default DLL GUI shall not be executed.

int SDSA_Customisation_SelectionGui (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Function called for explicit application selection processing customisation.
//! \param[in] pDataStruct Shared exchange structure provided with customisation information.
//! \return
//! 	- CLESS_CUST_DEFAULT to use the default processing. 
//! 	- CLESS_CUST_RETRY_WITH_CLESS if the transaction shall be restarted.
//! 	- CLESS_CUST_RETRY_WITHOUT_CLESS if transaction shall be restarted without cless.
//! 	- CLESS_CUST_STOP if the transaction shall be stopped.
//! 	- CLESS_CUST_NEXT_METHOD if next application selection method shall be used (if present). 
//! 	- CLESS_CUST_CONTINUE_METHOD if next application selection criteria shall be used. 

int SDSA_Customisation_CustAsProc (T_SHARED_DATA_STRUCT * pDataStruct);



//! \brief Analyse the application selection result and set the transaction result.
//! \param[in] nApplicationSelectionResult Application selection result.
//! \return The transaction result.

int SDSA_Customisation_AnalyseApplicationSelectionResult(int nApplicationSelectionResult);


#endif // __SDSA_CUSTOMISATION_H__INCLUDED__
