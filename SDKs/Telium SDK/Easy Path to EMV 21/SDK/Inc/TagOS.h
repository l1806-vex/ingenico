
/**
* \file TagOS.h
* \brief This module contains Transaction Steps Definition
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

#define EMVDC_APPLI_TYPE		(0x60)


//! \def TAG_GIVE_AID_NB_AID
//! \brief - Tag belonging to Output DEL filled up for Give_Aid Interface : Number of Aid supported
//! See Manager User's Guide 
//! Length : 1 byte
#define TAG_GIVE_AID_NB_AID			   0x9F8D00

//! \def TAG_GIVE_AID_AID_VALUE
//! \brief - Tag belonging to Output DEL filled up for Give_Aid Interface :List of AIDs managed by the application 
//! See Manager User's Guide 
//! Length : 1 byte
#define TAG_GIVE_AID_AID_VALUE	   	   0x9F8D01

#define TAG_GIVE_AID_APP_NAME		   0x9F8D02
#define TAG_GIVE_AID_APP_PRIO		   0x9F8D03
#define TAG_GIVE_AID_PREF_LANGUAGE	   0x9F8D04
#define TAG_TERM_APP_NUMBER			   0x9F8D05
#define TAG_GIVE_AID_MANUAL_SELECTION  0x9F8D06
#define TAG_GIVE_AID_ALREADY_SELECTED  0x9F8D07
#define TAG_GIVE_AID_ASI               0x9F8D08
#define TAG_GIVE_AID_EXTENDED          0x9F8D09


#define _OK_  0
#define _KO_ !_OK_

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

//! \brief Structure used for calls to all the EMVDC services.
typedef struct
{
	unsigned short type_code;			//!< Code type associated with EMVDC Component (96).
	unsigned short service;				//!< Service to be called.
	int    function;					//!< Step to be called, in case of call to EMVDC_process_step service.
	_DEL_  DEL;							//!< Input / Output DEL.
} StructProcessStep;

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/


//! \defgroup Step Transaction Steps Definition.
//! @{
#define	EMVDC_START								0		//!< Power on the card.
#define	EMVDC_APPLICATION_SELECTION				1		//!< Build Candidate List.
#define EMVDC_INITIATE_APPLICATION_PROCESSING	2		//!< Initiate Transaction (Get Processing Option command).
#define EMVDC_READ_APPLICATION_DATA				3		//!< Read Application Data.
#define EMVDC_OFFLINE_DATA_AUTHENTICATION		4		//!< Offline Data Authentication (SDA or DDA).
#define EMVDC_PROCESSING_RESTRICTIONS			5		//!< Processing Restrictions.
#define EMVDC_CARDHOLDER_VERIFICATION			6		//!< Obsolete !! DO NOT USE.
#define EMVDC_TERMINAL_RISK_MANAGEMENT			7		//!< Terminal Risk Management.
#define EMVDC_TERMINAL_ACTION_ANALYSIS			8		//!< Terminal Action Analysis.
#define EMVDC_CARD_ACTION_ANALYSIS				9		//!< Card Action Analysis (First Generate_AC).
#define EMVDC_ON_LINE_PROCESSING				10		//!< Online Processing.
#define EMVDC_ISSUER_TO_CARD_SCRIPT_PROCESSING1	11		//!< Issuer Script Processing phase 1 (scripts 71).
#define EMVDC_COMPLETION						12		//!< Transaction Completion.
#define EMVDC_ISSUER_TO_CARD_SCRIPT_PROCESSING2	13		//!< Issuer Script Processing phase 2 (scripts 72).
#define EMVDC_STOP								14		//!< Power off the ICC.
#define EMVDC_CARDHOLDER_VERIFICATION_FIRST		15		//!< Beginning of CVM step.
#define EMVDC_CARDHOLDER_VERIFICATION_OTHER		16		//!< CVM Step Continuation.
#define EMVDC_ODA_EXTERN_INIT					17		//!< Beginning of External ODA. Do not use if not explicitly needed.
#define EMVDC_ODA_EXTERN_INTERNAL_AUTHENTICATE	18		//!< Extern DDA. Do not use if not explicitly needed.
#define EMVDC_ODA_EXTERN_RESULT					19		//!< End of  of External ODA. Do not use if not explicitly needed.
#define EMVDC_FINAL_SELECTION					20		//!< Final Application Selection Step.
/*& BEGIN FT/937/06/MA : Get transaction Log from ICC for PBOC			   */
#define EMVDC_INITIATE_TRLOG_PROCESSING			21		//!< Read Log Entry for Transaction Log.
#define EMVDC_READ_TRLOG_DATA					22		//!< Read Transaction Log.
/*& END FT/937/06/MA : Get transaction Log from ICC for PBOC			   */

//! @}	// end of Step
