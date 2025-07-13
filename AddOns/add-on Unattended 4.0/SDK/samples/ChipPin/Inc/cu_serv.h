/**
* \file cu_serv.h
* \brief This module contains the the implementation of the services 
* provided by EMV CUSTOM.
*
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

#ifndef CU_SERV_H
#define CU_SERV_H

//! \defgroup Group_cu_serv Implementation of the services provided by EMV custom.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

// Status codes defined for the Service EMVCUST_LastTransaction_Status
/* #define CUSERV_record_not_found				0			//!< No data available.
#define CUSERV_last_trans_succeeded			1			//!< Last transaction succeeded.
#define CUSERV_PAN_OK_trans_failed			2			//!< PAN read, but transaction failed.
#define CUSERV_PAN_KO_trans_failed			3			//!< Unable to read PAN.
*/

// Transaction types, used for transactions other than debit
#define CUSERV_DEBIT_TRANSACTION			0			//!< Standard transaction.
#define CUSERV_REFUND_TRANSACTION			1			//!< Refund transaction.
#define CUSERV_CASH_TRANSACTION				2			//!< Cash transaction.
#define CUSERV_CASHBACK_TRANSACTION			3			//!< CashBack transaction.

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */

extern unsigned char ucComm_Message_reason_code;		//!< Global variable used to store the call reason code for a reversal message.
extern unsigned char Pos_8583_93 [];					//!< Global variable used to store point of service entry mode for the current transaction.
extern unsigned short CUSERV_New_Parameters;			//!< Boolean indicating if new manager parameters are present. Then it will be transmitted to engine.
extern unsigned char nb_time_select;					//!< Global variable indicating the time number that AID list has been displayed. (used for AID reselection).
extern StructListe   Menu;								//!< Global variable used to display menus.
extern unsigned long ulTransactionType;					//!< Global variable indicating the transaction type : CUSERV_DEBIT_TRANSACTION, CUSERV_REFUND_TRANSACTION, CUSERV_CASH_TRANSACTION, CUSERV_CASHBACK_TRANSACTION.
extern unsigned char signature_asked;					//!< Global variable set to TRUE or FALSE, indicating if the cardholder signature is requested.
extern unsigned char Aid[];								//!< Global variable used to store the AID.

/* ======================================================================= */
/* Global function declaration                                             */
/* ======================================================================= */

//===========================================================================
//! \brief This function initializes the TLV tree given as parameter.
//! \param[in,out] phOutputTLVTree : TLV tree initialized with status code set
//! to 0 :
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
void EMVCUST_Initialise_TlvTree(TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function initializes the TLV tree given as parameter with 
//! the global parameters of the terminal.
//! \param[out] phOutputTLVTree : TLV tree containing the global parameters of
//! the terminal : 
//! - \ref TAG_TERMINAL_CAPABILITIES,
//! - \ref TAG_ADD_TERMINAL_CAPABILITIES,
//! - \ref TAG_TERMINAL_COUNTRY_CODE, 
//! - \ref TAG_TERMINAL_IDENTIFICATION,	
//! - \ref TAG_TERMINAL_TYPE, 
//! - \ref TAG_SCHEMAS_KSU,
//! - \ref TAG_IFD_SERIAL_NUMBER,
//! - \ref TAG_COMPATIBILITY_2000,
//! - \ref TAG_USE_PSE,
//! - \ref TAG_CUST_IS_CARDHOLDER_CONFIRMATION,
//! - \ref TAG_PSE_ALGO,
//! - \ref TAG_CUST_IS_COMM_MANAGED_BY_CUSTOM,
//! - \ref TAG_WAIT_AFTER_ATR,
//! - \ref TAG_CUST_SUPPORTED_LANGUAGE_LIST,
//! - \ref TAG_CUST_IS_ONLINE_ADVICE, 
//! - \ref TAG_CUST_IS_BATCH_CAPTURE,
//! - \ref TAG_CUST_IS_ONLINE_CAPTURE,
//! - \ref TAG_POS_ENTRY_MODE_CODE,
//! - \ref TAG_CUST_TRM_OVERPASS_AIP,
//! - \ref TAG_CUST_IS_SKIP_DEFAULT,
//! - \ref TAG_CUST_IS_SKIP_ONLINE,
//! - \ref TAG_CUST_IS_ODA_PROCESSING,
//! - \ref TAG_CUST_DETECT_FAIL_PRIOR_TAA,
//! - \ref TAG_CUST_CDA_NEVER_REQUEST_ARQC_1GENAC,
//! - \ref TAG_CUST_CDA_NEVER_REQUEST_ONLINE_2GENAC,
//! - \ref TAG_CUST_IS_FLOOR_LIMIT_CHECKING,
//! - \ref TAG_CUST_IS_RANDOM_TRANSACTION_SELECT,
//! - \ref TAG_CUST_IS_VELOCITY_CHECKING,
//! - \ref TAG_CUST_IS_ACCOUNT_TYPE,
//! - \ref TAG_CUST_SUBSEQUENT_BYPASS_PIN,
//! - \ref TAG_CUST_IS_FORCED_ACCEPTANCE,
//! - \ref TAG_CUST_IS_FORCED_ONLINE,
//! - \ref TAG_CUST_APPLI_NAME,
//! - \ref TAG_CUST_IDLE_MESSAGE,
//! - \ref TAG_CUST_STATUS_CODE.
//===========================================================================
void EMVCUST_Get_Global_Param_TlvTree(TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function initializes the TLV tree given as parameter with 
//! the list of the AID managed by the application.
//! \param[out] phOutputTLVTree : TLV tree containing the list of the AID 
//! managed by the application : 
//! - \ref TAG_GIVE_AID_MANUAL_SELECTION,
//! - \ref TAG_GIVE_AID_NB_AID,
//! - Then for each AID : 
//! - \ref TAG_GIVE_AID_AID_VALUE,
//! - \ref TAG_GIVE_AID_ASI.
//===========================================================================
void EMVCUST_Get_AID_TlvTree(TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function manages the menus of the custom application.
//! \param[out] phOutputTLVTree : TLV tree containing the status code set
//! with the result, of the menu function.
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
void EMVCUST_More_Function_TLVTree(TLV_TREE_NODE *phOutputTLVTree); // TLV_TREE_NODE *phInputTLVTree

//===========================================================================
//! \brief This function allows to launch treatments associated with F key.
//! \param[in] Val_Key : Pressed key.
//! \param[out] OutKey : Pressed key.
//===========================================================================
void EMVCUST_KeyManagement_TLVTree(unsigned char Val_Key, unsigned char* OutKey);

//===========================================================================
//! \brief This function initializes the TLV tree given as parameter with 
//! the list of the AID managed by the application.
//! \param[out] phOutputTLVTree : TLV tree containing the list of the AID 
//! managed by the application : 
//! - \ref TAG_AID_LIST_TERMINAL,
//! - \ref TAG_NB_AID_TERMINAL,
//! - \ref TAG_CUST_STATUS_CODE.
//===========================================================================
void EMVCUST_Get_AID_List_TlvTree(TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function gets the AID data, provided by the acquirer.
//! \param[in] phInputTLVTree : input TLV tree containing the tag : 
//! - \ref TAG_AID_PROPRIETARY.
//! \param[out] phOutputTLVTree : output TLV tree containing the list of data 
//! of the AID : 
//! - \ref TAG_AID_PROPRIETARY,
//! - \ref TAG_VERSION_NUMBER_TERMINAL,
//! - \ref TAG_DEFAULT_DDOL,
//! - \ref TAG_DEFAULT_TDOL,
//! - \ref TAG_MAX_TARG_PERC_FOR_BIASED_RAND_SEL,
//! - \ref TAG_TARG_PERC_FOR_BIASED_RAND_SEL,
//! - \ref TAG_TERMINAL_ACTION_CODE_DEFAULT,
//! - \ref TAG_TERMINAL_ACTION_CODE_DENIAL,
//! - \ref TAG_TERMINAL_ACTION_CODE_ONLINE,
//! - \ref TAG_TERMINAL_FLOOR_LIMIT,
//! - \ref TAG_TRESH_VALUE_FOR_BIASED_RAND_SEL,
//! - \ref TAG_TRANSACTION_CURRENCY_CODE,
//! - \ref TAG_TRANSACTION_CURRENCY_EXP,
//! - \ref TAG_CUST_APPLICATION_SELECTION_ID,
//! - \ref TAG_SUPPORTED_PROPRIETARY_LIST,
//! - \ref TAG_CUST_STATUS_CODE.
//===========================================================================
void EMVCUST_Get_AID_DATA_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function gets the parameters linked to a specific AID.
//! \param[in] phInputTLVTree : input TLV tree containing the tag : 
//! - \ref TAG_AID_PROPRIETARY.
//! \param[out] phOutputTLVTree : output TLV tree containing the list of 
//! parameters of the AID : 
//! - \ref TAG_TIME_OUT_PIN_CODE,
//! - \ref TAG_TIME_OUT_INTER_CAR,
//! - \ref TAG_CUST_IS_KSU,
//! - \ref TAG_CUST_IS_BLACK_LIST,
//! - \ref TAG_CUST_COMM_TYPE_APPLI,
//! - \ref TAG_CUST_SERVICE_AUTHO_NUM,
//! - \ref TAG_TRANSACTION_TYPE,
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
void EMVCUST_Get_AID_Param_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function is called by EMV engine after each step of the EMV 
//! transaction. It enables EMV custom to make extra checks and treatments.
//! The data exchanged are specific for each step.
//! \param[in] function : step number. The different steps of the transaction
//! are : 
//! - \ref EMVDC_START,
//! - \ref EMVDC_APPLICATION_SELECTION,
//! - \ref EMVDC_INITIATE_APPLICATION_PROCESSING,
//! - \ref EMVDC_READ_APPLICATION_DATA,
//! - \ref EMVDC_OFFLINE_DATA_AUTHENTICATION,
//! - \ref EMVDC_PROCESSING_RESTRICTIONS,
//! - \ref EMVDC_CARDHOLDER_VERIFICATION,
//! - \ref EMVDC_TERMINAL_RISK_MANAGEMENT,
//! - \ref EMVDC_TERMINAL_ACTION_ANALYSIS,
//! - \ref EMVDC_CARD_ACTION_ANALYSIS,
//! - \ref EMVDC_ON_LINE_PROCESSING,
//! - \ref EMVDC_ISSUER_TO_CARD_SCRIPT_PROCESSING1,
//! - \ref EMVDC_COMPLETION,
//! - \ref EMVDC_ISSUER_TO_CARD_SCRIPT_PROCESSING2,
//! - \ref EMVDC_STOP,
//! - \ref EMVDC_CARDHOLDER_VERIFICATION_FIRST,
//! - \ref EMVDC_CARDHOLDER_VERIFICATION_OTHER,
//! - \ref EMVDC_INITIATE_TRLOG_PROCESSING,
//! - \ref EMVDC_READ_TRLOG_DATA.
//! \param[in] phInputTLVTree : input TLV tree containing specific data of 
//! the step : Output data returned by EMVDC to the previous call of 
//! EMVCUST_Process_Step_TlvTree, including function status code.
//! \param[out] phOutputTLVTree : output TLV tree containing specific data 
//! of the step.
//===========================================================================
void EMVCUST_Process_Step_TlvTree(int function, TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function builds an output TLV tree with data read in the 
//! database.
//! \param[in] phInputTLVTree : input TLV tree containing the tag : 
//! - \ref TAG_AID_PROPRIETARY.
//! \param[out] phOutputTLVTree : output TLV tree containing the data read 
//! in the database.
//===========================================================================
void EMVCUST_Get_AID_ICS_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function performs the referral request treatments. The voice 
//! referral is called by the card or by the host.
//! \param[in] phInputTLVTree : input TLV tree containing the tag : 
//! - \ref TAG_EG_REFERRAL_CARD.
//! \param[out] phOutputTLVTree : TLV tree containing the status code set
//! with the result, of the referral request.
//! - \ref TAG_CUST_STATUS_CODE set to : 
//! - \ref TAG_CUST_PROCESS_COMPLETED,
//! - \ref TAG_CUST_REFERRAL_DECLINED,
//! - \ref TAG_CUST_REFERRAL_ON_LINE,
//! - \ref TAG_CUST_REFERRAL_NOT_ACCEPTED.
//===========================================================================
void EMVCUST_Voice_Referral_TlvTree (TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function allows to EMV engine to display a standard message.
//! If the message is to be displayed to the cardholder, EMV ENGINE may add 
//! a code with Cardholder Language, corresponding to Cardholder Preferred 
//! Language read on the card.
//! \param[in] phInputTLVTree : input TLV tree containing the number of the 
//! message to display, and the cardholder language.
//! - \ref TAG_EG_MESSAGE_CODE_NUM.
//! - \ref TAG_EG_CARDHOLDER_LANGUAGE.
//! \param[out] phOutputTLVTree : TLV tree containing the status code set
//! to 0.
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
void EMVCUST_Display_Message_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function searches in the financial batch record, the last
//! transaction performed with the current card. 
//! - If the Primary Account Number of the current card is found in the 
//! batch record, the function builds an output TLV tree containing the last
//! transaction details.
//! - Otherwise, the output TLV tree built contains the status code set 
//! to TAG_CUST_PAN_NOT_FOUND.
//! \param[in] phInputTLVTree : input TLV tree containing the PAN of the 
//! current card to find :
//! - \ref TAG_APPLI_PRIM_ACCOUNT_NB.
//! \param[out] phOutputTLVTree : 
//! - \ref TAG_CUST_STATUS_CODE set to TAG_CUST_PAN_NOT_FOUND, if given PAN not found.
//! - TLV tree containing the last transaction details otherwise : 
//! - \ref TAG_AMOUNT_AUTH_BIN,
//! - \ref TAG_AMOUNT_OTHER_BIN,
//! - \ref TAG_LAST_TR_AMOUNT_BIN,
//! - \ref TAG_LAST_TR_CURRENCY_CODE,
//! - \ref TAG_TRANSACTION_DATE,
//! - \ref TAG_TRANSACTION_TIME,
//! - \ref TAG_TRANSACTION_TYPE.
//===========================================================================
void EMVCUST_Get_Last_Transaction_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function asks the cardholder to choose a language in the list
// of supported langages.
//! \param[out] phOutputTLVTree : TLV tree containing a list of language tags : 
//! - \ref TAG_CUST_IS_MULTILANG_SUPPORTED,
//! - \ref TAG_CUST_SUPPORTED_LANGUAGE_LIST,
//! - \ref TAG_EG_CARDHOLDER_LANGUAGE,
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
void EMVCUST_Choose_Language_Menu_TlvTree (TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function manages the choice of account type.
//! \param[out] phOutputTLVTree : TLV tree containing the tag TAG_ACCOUNT_TYPE
//! set to the value chosen by the cardholder.
//===========================================================================
void EMVCUST_Choose_Account_Type_Menu_TlvTree (TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function is called periodically by manager to know : 
//! - if some parameters have changed.
//! - if an automatic data batch capture must be performed.
//! \param[out] phOutputTLVTree : TLV tree containing the tag TAG_CUST_STATUS_CODE
//! set to :
//! - \ref TAG_CUST_NEW_PARAMETERS if some parameters have changed.
//! - 0 otherwise.
//===========================================================================
void EMVCUST_Periodic_Call_TLVTree(TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function performs the initialization of the global variable
//! used for menu display.
//! \param[in] flag : Set to _ON_ or _OFF_. It indicates if the correction key
//! has to be managed.
//! \param[in] offset : table index for selection.
//===========================================================================
void InitDefaut(int flag,int offset);

//===========================================================================
//! \brief This function manages an authorization request.
//! \param[out] phOutputTLVTree : output TLV tree containing the response from
//! the host : 
//! - TAG_AUTHORISATION_RESPONSE_CODE,
//! - TAG_CUST_STATUS_CODE.
//===========================================================================
void EMVCUST_Authorization_TlvTree (TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function searches an element in TLV tree given as parameter.
//! \param[in] phInTLVTree : input TLV tree in which to search the tag.
//! \param[in] Tag : tag to search in the input TLV tree.
//! \param[out] ptElt : DataElement structure containing the tag number, 
//! tag value, tag length. If tag found in input TLV tree.
//! \return
//! - TRUE if the tag is found in the input TLV tree.
//! - FALSE otherwise.
//===========================================================================
unsigned short CUSERV_Extract_Element_TLV_Tree(TLV_TREE_NODE *phInTLVTree, unsigned long Tag, DataElement *ptElt);

//===========================================================================
//! \brief This function calls the service that informs about protocol used.
//! \return
//! - \ref COMM_PROTOCOL_TYPE_YES.
//! - \ref COMM_PROTOCOL_TYPE_HYPERTERMINAL
//! - \ref COMM_PROTOCOL_TYPE_ISO8583_1987
//! - \ref COMM_PROTOCOL_TYPE_ISO8583_1993
//! - \ref COMM_PROTOCOL_TYPE_SPDH
//===========================================================================
int Host_Comm_Protocol(void);

//===========================================================================
//! \brief This function makes the configuration and the connection to a host 
//! according to protocol implemented.
//! \return
//! - TRUE if communication connection OK.
//! - FALSE otherwise.
//===========================================================================
int Host_Config_Connect(void);

//! @}

#endif
