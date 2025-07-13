
#ifndef _EMVDC_H
#define _EMVDC_H
/**
 *
 *! \file        _emvdc_.h
 * \brief This module contains definitions for access to EMVDC component
 *
	EMVDC is the EMV Level 2 kernel dedicated to Telium Platform.
	It is developped upon the M2OS architecture.
	It offers a set of services to applications, using the IAC communication mechanism.
 *
 * \author        SMO
 * \author Copyright (c) 2001 Sagem Monetel SA, rue claude Chappe,
 * \author 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author Sagem Monetel SA has intellectual property rights relating
 * \author to the technology embodied in this software.  In particular,
 * \author and without limitation, these intellectual property rights
 * \author may include one or more patents.
 *
 * \author This software is distributed under licenses restricting
 * \author its use, copying, distribution, and decompilation.
 * \author No part of this software may be reproduced in any form
 * \author by any means without prior written authorization of
 * \author Sagem Monetel.

 * \see    EMV 2000 - Level 2 requirements
 * \see    SDK EFT 30 Documentation
 *
 */
#ifndef TAG_GIVE_AID_NB_AID
#define TAG_GIVE_AID_NB_AID			   0x9F8D00
#define TAG_GIVE_AID_AID_VALUE	   	   0x9F8D01
#define TAG_GIVE_AID_APP_NAME		   0x9F8D02
#define TAG_GIVE_AID_APP_PRIO		   0x9F8D03
#define TAG_GIVE_AID_PREF_LANGUAGE	   0x9F8D04
#define TAG_TERM_APP_NUMBER			   0x9F8D05
#define TAG_GIVE_AID_MANUAL_SELECTION  0x9F8D06
#define TAG_GIVE_AID_ALREADY_SELECTED  0x9F8D07
#define TAG_GIVE_AID_ASI               0x9F8D08
#define TAG_GIVE_AID_EXTENDED          0x9F8D09
#endif

/** @defgroup Serv EMVDC Services definition
 *  @{											*/
#define SERVICE_EMVDC_INITIATE_TRANSACTION        101
#define SERVICE_EMVDC_PROCESS_TRANSACTION         102
#define SERVICE_EMVDC_COMPLETE_TRANSACTION        103
#define SERVICE_EMVDC_GET_DATA_ELEMENTS           104
#define SERVICE_EMVDC_SET_DEFAULT_DATA_ELEMENTS   105
#define SERVICE_EMVDC_DUMP_DATA_ELEMENTS          106
#define SERVICE_EMVDC_CLEAR_DEFAULT_DATA_ELEMENTS 107
#define SERVICE_EMVDC_GET_DEFAULT_DATA_ELEMENTS   108
#define SERVICE_EMVDC_APPLICATION_SELECTION       109
#define SERVICE_EMVDC_PROCESS_STEP                110
#define SERVICE_EMVDC_APP_SEL                     111
#define SERVICE_EMVDC_READ                        112
/* BEGIN TEDT/Z3/02/1314/PBE */
#define SERVICE_EMVDC_GET_CHALLENGE               113
/* END TEDT/Z3/02/1314/PBE */
/*& BEGIN SMO/ETU/04/20017/LB                                              */
#define SERVICE_EMVDC_SET_DATA_ELEMENTS           114
/*& END  SMO/ETU/04/20017/LB                                               */
/*& BEGIN SMO/ETU/04/20160/MA                                              */
#define SERVICE_EMVDC_GET_COMMAND		          115
/*& END  SMO/ETU/04/20160/MA                                              */
/*&BEGIN FT/08/3207/WM      Ajout du temps de calcul RSA dans les traces TOOLWARE  */
#define SERVICE_EMVDC_GET_ODA   		          116
/*&END FT/08/3207/WM      Ajout du temps de calcul RSA dans les traces TOOLWARE  */
/*&BEGIN FT/08/4160/MG */
#define EMVDC_REVOKE_ISSUER_CERTIFICATE			  117
/*&END FT/08/4160/MG */
#define SERVICE_EMVDC_CLEAR_TRANSACTION_DATA      118 
/* data storage*/
#define  SERVICE_EMVDC_AS_PROP_DATA_ELEMENTS      119
/** @} */

/** @defgroup Step Transaction Steps Definition
 *  @{											*/
#define	EMVDC_START								0	/*!< Power on the card    */
#define	EMVDC_APPLICATION_SELECTION				1	/*!< Build Candidate List */
#define EMVDC_INITIATE_APPLICATION_PROCESSING	2	/*!< Initiate Transaction (Get Processing Option command) */
#define EMVDC_READ_APPLICATION_DATA				3	/*!< Read Application Data */
#define EMVDC_OFFLINE_DATA_AUTHENTICATION		4	/*!< Offline Data Authentication (SDA or DDA) */
#define EMVDC_PROCESSING_RESTRICTIONS			5	/*!< Processing Restrictions */
#define EMVDC_CARDHOLDER_VERIFICATION			6	/*!< Obsolete !! DO NOT USE */
#define EMVDC_TERMINAL_RISK_MANAGEMENT			7	/*!< Terminal Risk Management */
#define EMVDC_TERMINAL_ACTION_ANALYSIS			8	/*!< Terminal Action Analysis */
#define EMVDC_CARD_ACTION_ANALYSIS				9	/*!< Card Action Analysis (First Generate_AC) */
#define EMVDC_ON_LINE_PROCESSING				10	/*!< Online Processing */
#define EMVDC_ISSUER_TO_CARD_SCRIPT_PROCESSING1	11	/*!< Issuer Script Processing phase 1 (scripts 71) */
#define EMVDC_COMPLETION						12	/*!< Transaction Completion */
#define EMVDC_ISSUER_TO_CARD_SCRIPT_PROCESSING2	13	/*!< Issuer Script Processing phase 2 (scripts 72) */
#define EMVDC_STOP								14	/*!< Power off the ICC */
#define EMVDC_CARDHOLDER_VERIFICATION_FIRST		15	/*!< Beginning of CVM step */
#define EMVDC_CARDHOLDER_VERIFICATION_OTHER		16	/*!< CVM Step Continuation */
/*& BEGIN Externalisation ODA 									*/
#define EMVDC_ODA_EXTERN_INIT		             17	/*!< Beginning of External ODA. Do not use if not explicitly needed */
#define EMVDC_ODA_EXTERN_INTERNAL_AUTHENTICATE		18	/*!< Extern DDA. Do not use if not explicitly needed */
#define EMVDC_ODA_EXTERN_RESULT		         19	/*!< End of  of External ODA. Do not use if not explicitly needed */
#define EMVDC_FINAL_SELECTION				    20	/*!< Final Application Selection Step */
/*& END															*/
/** @} */ // end of Step
#define _OK_  0
#define _KO_ !_OK_

/*& BEGIN FT/937/06/MA : Get transaction Log from ICC for PBOC			   */
#define EMVDC_INITIATE_TRLOG_PROCESSING			21  /*!< Read Log Entry for Transaction Log  */
#define EMVDC_READ_TRLOG_DATA					22	/*!< Read Transaction Log */
/*& END FT/937/06/MA : Get transaction Log from ICC for PBOC			   */

/**
 * Structure used for calls to all the EMVDC services
 */
typedef struct
{
    unsigned short type_code;	/**< Code type associated with EMVDC Component (96) */
	unsigned short service;		/**< Service to be called */
	int    function;			/**< Step to be called, in case of call to EMVDC_process_step service */
	_DEL_  DEL;					/**< Input / Output DEL.	*/
} StructProcessStep;

/** @defgroup Serv EMVDC Services definition
 *  @{											*/
/**
 * function:    EMVDC_initiate_transaction
 * @brief: Obsolete Service. DO NOT CALL ANY MORE !!
 * @author: SMO
 *-----------------------------------------------------------------------------
 * @param
 * @return:
 * @
 * @exception
 *-----------------------------------------------------------------------------
 */
DEL* EMVDC_initiate_transaction        ( const DEL *aDEL);

/**
 * function:    EMVDC_process_transaction
 * @brief: Obsolete Service. DO NOT CALL ANY MORE !!
 * @author: SMO
 *-----------------------------------------------------------------------------
 * @param
 * @return:
 * @
 * @exception
 *-----------------------------------------------------------------------------
 */
DEL* EMVDC_process_transaction         ( const DEL *aDEL);

/**
 * function:    EMVDC_complete_transaction
 * @brief: Obsolete Service. DO NOT CALL ANY MORE !!
 * @author: SMO
 */
DEL* EMVDC_complete_transaction        ( const DEL *aDEL);

/**
 * function:    EMVDC_get_data_elements
 * @brief: Read a list of element in the transaction Database.
 * @author: SMO
 * @param aDEL contains the list of elements to be read.
 * @return: Output DEL with the value of all requested elements.
 * @return: Elements not found are not returned in the output DEL.
 */
DEL* EMVDC_get_data_elements           ( const DEL *aDEL);

/**
 * function:    EMVDC_set_default_data_elements
 * @brief: Writes a list of elements in the parameter Database.
 * @author: SMO
 * @param aDEL : contains the list of elements to be written.
 * @return: Void DEL.
 */
DEL* EMVDC_set_default_data_elements   ( const DEL *aDEL);

/**
 * function:    EMVDC_dump_data_elements
 * @brief: Print the transaction Database. Use for debug purpose only.
	Prefer the use of EMV Tool now.
 * @author: SMO
 * @param None
 * @return OK if dump successful, else KO
  */
int  EMVDC_dump_data_elements          (void);

/**
 * function:    EMVDC_clear_default_data_elements
 * @brief: Clear the  Parameter Database.
 * @author: SMO
 * @param None.
 * @return: Void DEL
 * @exception
 */
DEL* EMVDC_clear_default_data_elements (void);

/**
 * @function:    EMVDC_clear_transaction_data
 * @brief: Clear the  Parameter Database, the Transaction Database, random, used keys

 * @author: SMO

 *-----------------------------------------------------------------------------
 * @param: None.
 * @return: Void DEL
 * @exception:

 *-----------------------------------------------------------------------------
 */
DEL *EMVDC_clear_transaction_data(void);

/**
 * function:    EMVDC_get_default_data_elements
 * @brief: Read a list of element in the Parameter Database.

 * @author: SMO

 *-----------------------------------------------------------------------------
 * @param
 * @param Input DEL containing the list of elements to be read.
 * @return: Output DEL with the value of all requested elements.
 * @return: Elements not found are not returned in the output DEL.
 * @exception

 *-----------------------------------------------------------------------------
 */
DEL* EMVDC_get_default_data_elements   ( const DEL *aDEL);

/**
 * function:    EMVDC_application_selection
 * @brief: Build EMV candidate List

 * @detailed: This Service builds the candidate List, According to EMV 2000, Book 1, chapter 8
 * @detailed: The Payment Systems Directories method will be used if the tag "PSE usage" has been set previously,
 * @detailed: the List of AID method will be used otherwise.
 * @detailed: CAUTION : the PSE method is not available for French application.
 * @author: SMO

 *-----------------------------------------------------------------------------
 * @param
 * @param aDEL : Input Candidate AID List[len AIDi][val AIDi] x number of AIDlen is 1 byte val is maximum 16 bytes
 * @param	The most significant bit of len is used as Application Selection Indicator,
 * @param	with an opposite logic : bit = 0 : partial AID length enabled for this AID.
 * @param		                        bit = 1 : partial AID length disabled.
 * @return DEL Containing the following tags :
 		- Service Status Code	9F8101 with values
 			- 00 00 Process completed successfully
 			- 00 1x Transaction Terminated
 			- 01 xx Service execution error
 		- Number of matching applications	9F8117
 		- Cardholder Confirmation		9F8116	1	0: No, 1:Yes
 * @exception

 *-----------------------------------------------------------------------------
 */
DEL* EMVDC_application_selection       ( const DEL* aDEL);

/**
 * function:    EMVDC_process_step
 * @brief: Asks EMVDC to perform one transaction step

 * @detailed: This Service copies the entry DEL into the transaction database.
 * @detailed: Then it performs the treatments related with the step.
 * @detailed: This may result into commands sent to the card.
 * @detailed: It updates the tag TAG_SERVICE_STATUS_CODE with the result of
 * @detailed: the step
 * @author: SMO

 *-----------------------------------------------------------------------------
 * @param function : Step to be performed
 * @param aDEL : List of elements given in entry of the step.
 * @return: DEL Containing the following the tag TAG_SERVICE_STATUS_CODE
 * @exception

 *-----------------------------------------------------------------------------
 */
DEL* EMVDC_process_step                ( int function, const DEL *aDEL);

DEL* EMVDC_app_sel_pinbio              ( const  DEL* aDEL);

DEL* EMVDC_read_pinbio                 ( const  DEL* aDEL);

 /* BEGIN TEDT/Z3/02/1314/PBE */
/*& BEGIN SMO/ETU/04/20017/LB                                              */
/**
 * function:    EMVDC_Get_Challenge
 * @brief Asks EMVDC to send a GET_CHALLENGE command to the ICC

 * @author SMO

 *-----------------------------------------------------------------------------
 * @param
 * @param Void DEL
 * @return DEL containing the tag TAG_UNPREDICTABLE_ICC_NUMBER
 * @warning This function shall be called only in case of Externalisation of PIN
 * @warning encipherement.
 * @exception

 *-----------------------------------------------------------------------------
 */
DEL * EMVDC_Get_Challenge( const DEL* aDEL);
 /* END TEDT/Z3/02/1314/PBE */

/*& BEGIN SMO/ETU/04/20017/LB                                              */
/**
 * function:    EMVDC_set_data_elements
 * @brief Writes a list of elements in the transaction Database.

 * @author: SMO

 *-----------------------------------------------------------------------------
 * @param
 * @param Input DEL containing the list of elements to be written.
 * @return Void DEL.
 * @warning This function should not be called unless for very special reasons.
 * @warning Misuse of this function may result of bad EMV treatments.
 * @exception

 *-----------------------------------------------------------------------------
 */
DEL* EMVDC_set_data_elements   (const DEL *aDEL);
/*& END  SMO/ETU/04/20017/LB                                               */

/*& BEGIN  SMO/ETU/04/20160/MA                                              */
/**
 * function:    EMVDC_get_commands
 * @brief This service replies with the information on a command sent to the card

 * @author: SMO

 *-----------------------------------------------------------------------------
 * @param
 * @param cmd_number Command number to be read (first one is command 0)
 * @return Output DEL containing
 * @return  - #TAG_APDU_CMD
 * @return  - #TAG_APDU_RESPONSE
 * @return  - #TAG_BEGIN_TIMER
 * @return  - #TAG_END_TIMER
 * @exception

 *-----------------------------------------------------------------------------
 */
DEL * EMVDC_get_commands(int cmd_number);
/*& END  SMO/ETU/04/20160/MA                                              */


DEL* EMVDC_get_AS_Proprietary_elements           ( const DEL *aDEL);

/** @} */


/*&BEGIN FT/08/3207/WM      Ajout du temps de calcul RSA dans les traces TOOLWARE  */
/**
 * function:    EMVDC_get_ODA_Time
 * @brief This service replies with time spent in ODA

 * @author: SMO

 *-----------------------------------------------------------------------------
 * @param
 * @param void
 * @return Output DEL containing
 * @return  - #TAG_ODA_TIME
 * @exception

 *-----------------------------------------------------------------------------
 */
DEL *EMVDC_get_ODA_Time(void);
/*&END FT/08/3207/WM      Ajout du temps de calcul RSA dans les traces TOOLWARE  */
/** @} */

#ifndef __DEL_DEFINED__

#ifdef _SECDEL_
#define CopyEntree	SecCopyEntree
#define CopySortie	SecCopySortie
void SecCopyEntree                        (DEL *aDEL, _DEL_ *_vDEL);
void SecCopySortie                        (_DEL_ *_vDEL,DEL *aDEL);
void SecDEL_CleanTags						(DEL* aDEL);
void SecDEL_FlushTags						(DEL* aDEL);
#define DEL_CleanTags SecDEL_CleanTags
#define DEL_FlushTags SecDEL_FlushTags
#else
void CopyEntree                        (DEL *aDEL, _DEL_ *_vDEL);
void CopySortie                        (_DEL_ *_vDEL,DEL *aDEL);
void DEL_CleanTags(DEL* aDEL);
void DEL_FlushTags(DEL* aDEL);
#endif


//-------------------------------------------------------------------------
/**
 * function:    _DEL_init
 * @brief Initiate external DEL mechanism
 * @author: SMO
 * @param aDEL : External DEL to be initialised
 * @return NONE
 * @warning Use this service only for IAPP services.
 * @warning Do not use in internal services
 * @exception
 */
//-------------------------------------------------------------------------
void           _DEL_init(_DEL_ *aDEL);

//-------------------------------------------------------------------------
/**
 * function:    _DEL_AddDataElement
 * @brief Add one element to an external DEL
 * @author: SMO
 * @param aDEL : External DEL where the element shall be added
 * @param AnElement : Element to be added
 * @return
 * @warning Use this service only for IAPP services.
 * @warning Do not use in internal services
 * @exception
 */
//-------------------------------------------------------------------------
int            _DEL_AddDataElement(_DEL_ *aDEL,const DataElement *AnElement);

//-------------------------------------------------------------------------
/**
 * function:    _DEL_GetDataElement
 * @brief Read one element into an external DEL
 * @author: SMO
 * @param
 * @param aDEL : External DEL
 * @param index : Index of the element in the DEL.
 * @return element read in the DEL.
 * @warning Use this service only for IAPP services.
 * @warning Do not use in internal services
 * @exception
 */
//-------------------------------------------------------------------------
_DataElement_ *_DEL_GetDataElement(_DEL_ *aDEL, int index);

//-------------------------------------------------------------------------
/**
 * function:    _DEL_GetCount
 * @brief Return the number of elements contained by an external DEL
 * @author: SMO
 * @param
 * @param aDEL : External DEL
 * @return Number of element
 * @warning Use this service only for IAPP services.
 * @warning Do not use in internal services
 * @exception
 */
//-------------------------------------------------------------------------
int            _DEL_GetCount(_DEL_ *aDEL);
/** @} */
#endif

#endif
