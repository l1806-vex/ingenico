/**
* \file cu_serv.c
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

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "SDK30.H"
#include "_emvdctag_.h"
#include "TagOS.h"
#include "del_lib.h"

#define PILOTE

#include "def_tag.h"
#include "cu_term.h"
#include "cu_black.h"
#include "MyTlvTree.h"
#include "cu_batch.h"
#include "cu_base.h"
#include "cu_serv.h"
#include "cu_mess.h"
#include "MessagesDefinitions.h"
#include "cu_more.h"
#include "convert.h"
#include "cu_entry.h"
#include "cu_param.h"
#include "gestion_param.h"
#include "cu_pin.h"
#include "cu_str.h"
#include "cu_comm.h"
#include "cu_pinen.h"
#include "cu_file.h"
#include "cu_receipt.h"
#include "servcomm.h"
#include "servcomm_TlvTree.h"
#include "EmvEngineInterface.h"
#include "LinkLayer.h"
#include "services.h"
#include "EngineInterfaceLib.h"

#include "EngineInterface.h"

#ifdef _USE_UCM_
#include "ucmtelium.h"
#include "ucmhostdll.h"
#include "ucmclib.h"
#endif


//! \addtogroup Group_cu_serv
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#ifdef _DONT_USE_F_KEYS_
#undef _DONT_USE_F1_KEY_
#define _DONT_USE_F1_KEY_

#undef _DONT_USE_F2_KEY_
#define _DONT_USE_F2_KEY_

#undef _DONT_USE_F3_KEY_
#define _DONT_USE_F3_KEY_

#undef _DONT_USE_F4_KEY_
#define _DONT_USE_F4_KEY_
#endif

#define STATUS_TR_APPROVED					0					//!< Definition of an approved transaction.
#define STATUS_TR_DECLINED					1					//!< Definition of a declined transaction.
#define STATUS_TR_CANCELLED					2					//!< Definition of a canceled transaction.
#define STATUS_TR_CARD_ERROR				3					//!< Definition of a card error during the transaction.
#define STATUS_TR_PROCESSING_ERROR			4					//!< Definition of a processing error during the transaction.
#define STATUS_TR_REFUND_APPROVED			5					//!< Definition of an approved refund transaction.

#define CUSERV_COMM_MAX_RETRIES				1					//!< Definition of maximum number of communication retries.

// Definition of Transaction Type, according with ISO8583
#define CUSERV_CREDIT_TYPE					0x20				//!< Definition of a credit type transaction.
#define CUSERV_CASH_TYPE					0x01				//!< Definition of a cash type transaction.

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

const unsigned char CUSERV_TRUE []   = {0x00, 0x01};			//!< Definition of TRUE value.
const unsigned char CUSERV_FALSE []  = {0x00, 0x00};			//!< Definition of FALSE value.

const unsigned char ARC_REFERRAL_APPROVED []={
	0x59,
	0x32
};																//!< Definition of an approved after card-initiated Referral : Y2.

const unsigned char ARC_REFERRAL_DECLINED []={
	0x5A,
	0x32
};																//!< Declined after card-initiated Referral : Z2.


/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

static unsigned short CUSERV_IsInBlackList;						//!< boolean indicating if the PAN number of the inserted card is in the black list.

unsigned char ucComm_Message_reason_code;
unsigned char Pos_8583_93 [LEN_CUST_POS_ISO8583_93];
unsigned short CUSERV_New_Parameters;
unsigned char nb_time_select;
StructListe       Menu;
unsigned long ulTransactionType;
unsigned char signature_asked;
unsigned char Aid [LEN_AID];
static unsigned char lg_Aid;									//!< AID length.
S_STATE_PARAM param;
int active_beep;

int TransactionLoopMode;
unsigned long loop_amount;

extern int giKeyboardType;
extern int giDisplayType;

#ifdef _TOOLWARE_
unsigned long        ulMMI_pin_on_line;
unsigned long        ulMMI_pin_off_line;
unsigned long        ulMMI_amount;
unsigned long        ulMMI_account_type;
unsigned long        ulHOST_comm;
unsigned long        ulMMI_ticket;
unsigned long        ulMMI_langue;
unsigned long        ulMMI_selappli;
unsigned long        ulMMI_force_OLP;
unsigned long        ulMMI_force_CAA;
unsigned long        ulMMI_force_COMP;
unsigned long        ulEnd_transaction =0;
extern unsigned long ulEnd_computation ;
extern void CURECEIPT_Print_Ticket_Advance_Demo(void);
#endif

static unsigned char status_tr;									//!< This variable stores the transaction status.
static unsigned char buffer_result;								//!< This variable stores the proprietary method entry.
static unsigned short ProprietaryMethodFirst;					//!< This variable is a boolean set to TRUE if the proprietary method is selected.
static int Protocol_Type;										//!< This variable stores the communication protocol type.

static unsigned short TransacOk;								//!< Boolean indicating if the transaction is authorized by the host.

static unsigned short CommProblem;								//!< Boolean indicating if a communication problem occured.

static unsigned short CUSERV_CommRetries;						//!< Communication trial number.
static unsigned char nb_try_pin_offline, nb_try_pin_online;		//!< number of trials of online / offline pin entry.

static int isConnected;											//!< Boolean indicating if the host is connected.

/*& BEGIN FT/937/06/MA : Get transaction Log from ICC for PBOC             */
static int isTrlog;												//!< Boolean indicating.
/*& END FT/937/06/MA : Get transaction Log from ICC for PBOC               */

static unsigned char reversal_requested;						//!< Boolean indicating if a reversal communication is requested.


/* ======================================================================== */
/* Static function definitions                                              */
/* ======================================================================== */

static void Forced_Acceptance(int function, unsigned char *is_forced_acceptance);
static void Add_Batch (unsigned char status_tr);
static void DisplayCancel(unsigned short merchLang);
static int Is_COMM_COMPONENT_Loaded (unsigned char type_appli);
static unsigned char CU_EnterProprietaryMethod(void);
static int Is_Offline_Only (void);
static unsigned char CallEnterPinOnLine(unsigned char nb_try, ENTRY_BUFFER *buffer);

// Specific functions for Process_step execution
static void EMVDC_START_Function(unsigned short * error_code, TLV_TREE_NODE *phOutTLVTree);
static void EMVDC_APPLICATION_SELECTION_Function_TlvTree(unsigned short * error_code, unsigned short *ptr_usMerchantLang, TLV_TREE_NODE *phInTLVTree, TLV_TREE_NODE *phOutTLVTree);
static void EMVDC_READ_APPLICATION_DATA_Function_TlvTree(unsigned short *error_code, TLV_TREE_NODE *phOutTLVTree);
static void EMVDC_OFFLINE_DATA_AUTHENTICATION_Function_TlvTree(unsigned short *error_code, TLV_TREE_NODE *phOutTLVTree);
static void EMVDC_CARDHOLDER_VERIFICATION_FIRST_Function_Tlvtree(unsigned short * error_code, TLV_TREE_NODE *phInTLVTree, TLV_TREE_NODE *phOutTLVTree);
static void EMVDC_CARDHOLDER_VERIFICATION_OTHER_Function_Tlvtree(unsigned short * error_code, TLV_TREE_NODE *phInTLVTree, TLV_TREE_NODE *phOutTLVTree);
static void EMVDC_TERMINAL_RISK_MANAGEMENT_Function_Tlvtree(unsigned short * error_code, TLV_TREE_NODE *phOutTLVTree);
static void EMVDC_CARD_ACTION_ANALYSIS_Function_Tlvtree(unsigned short *error_code, TLV_TREE_NODE *phOutTLVTree);
static void EMVDC_ON_LINE_PROCESSING_Function_Tlvtree(unsigned short * error_code, unsigned short *ptr_usMerchantLang, TLV_TREE_NODE *phInTLVTree, TLV_TREE_NODE *phOutTLVTree);
static void EMVDC_COMPLETION_Function_Tlvtree(unsigned short * error_code, TLV_TREE_NODE *phOutTLVTree);
static void EMVDC_STOP_Function_Tlvtree(unsigned short *error_code, unsigned short *ptr_usMerchantLang);
static void EMVDC_READ_TRLOG_DATA_Function_Tlvtree(unsigned short *error_code, TLV_TREE_NODE *phInTLVTree);

/*&BEGIN FT/08/3081/MA : advice online implementation */
static void Send_Advice_Message_TLVTree(unsigned short * error_code, unsigned short *ptr_usMerchantLang);
static T_Bool Online_Advice_Conditions(void);
/*&END FT/08/3081/MA : advice online implementation */

static void StopBeep(void);
static void ReStartBeep(void);
extern	unsigned short TransactionReactivateAsked;

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
//! \brief This function tests if the terminal allows only offline transactions.
//! \return
//! - FCT_OK if the terminal is offline only.
//! - KO otherwise.
//===========================================================================
static int Is_Offline_Only (void)
{
	int found;
	DataElement elt;

	// Reset the selected mark list
	PAR_ResetMarkList();
	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	// Get data from TLVTree
	found = PAR_ReadParameter(TAG_TERMINAL_TYPE, (DataElementExt *)&elt);

	// Search the database number associated with this AID
	if (found)
	{
		if ( (elt.ptValue[0]==0x13) || (elt.ptValue[0]==0x23) || (elt.ptValue[0]==0x16) || (elt.ptValue[0]==0x26))
			return FCT_OK;
		else
			return KO;
	}
	return KO;
}

//===========================================================================
void EMVCUST_Initialise_TlvTree(TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned char StatusCode[2];

	// if (*phOutputTLVTree != NULL)
	if (phOutputTLVTree != NULL)
	{
		// Add status code
		ShortToChar(TAG_CUST_PROCESS_COMPLETED, StatusCode);
		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &StatusCode, 2);
	}

	TransactionForcedOnline = (CUSERV_FALSE[0] << 8) + CUSERV_FALSE[1];
}


//===========================================================================
void EMVCUST_Get_Global_Param_TlvTree(TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned short error_code;
	int merchLang;
	char chaine [40];
	int select_result;
	unsigned char    buf[11];
	const unsigned long cst_tag_list[] = { TAG_TERMINAL_CAPABILITIES, TAG_ADD_TERMINAL_CAPABILITIES,
		TAG_TERMINAL_COUNTRY_CODE, TAG_TERMINAL_IDENTIFICATION,	TAG_TERMINAL_TYPE, TAG_SCHEMAS_KSU,
		TAG_IFD_SERIAL_NUMBER, TAG_COMPATIBILITY_2000, TAG_USE_PSE,	TAG_CUST_IS_CARDHOLDER_CONFIRMATION,
		TAG_PSE_ALGO, TAG_CUST_IS_COMM_MANAGED_BY_CUSTOM, TAG_WAIT_AFTER_ATR, TAG_CUST_SUPPORTED_LANGUAGE_LIST,
		TAG_CUST_IS_ONLINE_ADVICE, TAG_CUST_IS_BATCH_CAPTURE, TAG_CUST_IS_ONLINE_CAPTURE, TAG_POS_ENTRY_MODE_CODE,
		TAG_CUST_TRM_OVERPASS_AIP, TAG_CUST_IS_SKIP_DEFAULT, TAG_CUST_IS_SKIP_ONLINE, TAG_CUST_IS_ODA_PROCESSING,
		TAG_CUST_DETECT_FAIL_PRIOR_TAA, TAG_CUST_CDA_NEVER_REQUEST_ARQC_1GENAC,	TAG_CUST_CDA_NEVER_REQUEST_ONLINE_2GENAC,
		TAG_CUST_IS_FLOOR_LIMIT_CHECKING, TAG_CUST_IS_RANDOM_TRANSACTION_SELECT, TAG_CUST_IS_VELOCITY_CHECKING,
		TAG_CUST_IS_ACCOUNT_TYPE, TAG_CUST_SUBSEQUENT_BYPASS_PIN, TAG_CUST_IS_FORCED_ACCEPTANCE,
		TAG_CUST_IS_FORCED_ONLINE, TAG_CUST_IS_AMOUNT_UNKNOWN_BEFORE_CVM,TAG_CUST_IS_SELECTABLE_KERNEL,TAG_CUST_IS_DELETABLE_TAC,TAG_CUST_LOG_DURING_TR };
		//TAG_TRANSACTION_CATEGORY_CODE,


	PAR_InitParam(C_PARAM_INIT_APLI, NULL);

	// Get data from CUDB Global

	// Retreive Terminal merchant language
	merchLang = PSQ_Give_Language();
	if (merchLang > C_NBLANGMERCH)
	{
		merchLang = 0;
	}

	//----------------------------------------------------------------------
	// Extract global parameters from TLVTree
	//----------------------------------------------------------------------
	{
		// Reset mark manager
		PAR_ResetMarkList();
		select_result = PAR_SelectMark(C_TAG_ICS0, C_TREE_ALL);

		// Get data from TLVTree
		if (select_result == 0)
			// if no problem
			PAR_ReadParameterListTLVTree(cst_tag_list, sizeof (cst_tag_list) / sizeof(unsigned long), phOutputTLVTree);
	}

	//----------------------------------------------------------------------
	// Following tags are reconstructed at each call because their value may have changed
	//----------------------------------------------------------------------

	strcpy (chaine, CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_APPLI_NAME, merchLang));
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_APPLI_NAME, (unsigned char *) chaine, strlen ((char *) chaine));

	strcpy (chaine, CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_IDLE_MESS, merchLang));
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_IDLE_MESSAGE, (unsigned char *) chaine, strlen ((char *) chaine));

	chaine[0] = 1;
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_FINAL_SELECT_CALL, chaine, 1);

	error_code = 0;
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &error_code, 2);
	if (TransactionReactivateAsked == TRUE)
		ShortToChar(TransactionReactivateAsked,buf);
	else
		memclr(buf,2);
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_TRREACTIVATE_IS_ASKED, (unsigned char *) buf, 2);
}

//===========================================================================
void EMVCUST_Get_AID_TlvTree(TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned short  i;
	T_CUDB_AID_Elt tab_AID[NB_AID_MAX];
	unsigned char nb_aid;
	const unsigned char ct_DispList = 1;

	// Build an output TLV tree

	// Read the list of AID in TLV tree structure
	CUPAR_GiveAIDList(&nb_aid, tab_AID);

	TlvTree_AddChild(*phOutputTLVTree, TAG_GIVE_AID_MANUAL_SELECTION, (unsigned char*) &ct_DispList, 1);

	// Number of AID
	TlvTree_AddChild(*phOutputTLVTree, TAG_GIVE_AID_NB_AID, (unsigned char *) &nb_aid, 1);

	// Construct AID List
	for (i = 0; i < nb_aid; i++)
	{
		TlvTree_AddChild(*phOutputTLVTree, TAG_GIVE_AID_AID_VALUE, (unsigned char *) (&tab_AID[i].AID[1]), tab_AID[i].AID[0]);

		// Retrieve the Application Selection Indicator
		TlvTree_AddChild(*phOutputTLVTree, TAG_GIVE_AID_ASI, (unsigned char *) (&tab_AID[i].ASI ), 1);
	}

	CUDB_StoreTLVTree(phOutputTLVTree);
}


//===========================================================================
void EMVCUST_Get_AID_List_TlvTree(TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned char  nb_aid;
	unsigned short i;
	unsigned short error_code;
	static char AIDList [NB_AID_MAX * (LEN_AID + 2)];
	T_CUDB_AID_Elt tab_AID[NB_AID_MAX];
	DataElement elt;

	// Build an output TLV tree

	memset (AIDList, 0, NB_AID_MAX * (LEN_AID + 2));

	// Read the list of AID in TLVTree structure
	CUPAR_GiveAIDList(&nb_aid, tab_AID);

	// Construct AID List
	elt.tag = TAG_AID_LIST_TERMINAL;
	elt.length  = 0;
	for (i = 0; i < nb_aid; i++)
	{
		// Retrieve the Application Selection Indicator
		if (tab_AID [i].ASI != 0)
		{
			// Value of Application Selection Indicator set in leftmost
			// length bit of AID (Recall, AID Value contains in fact
			// the AID length on one byte, followed by the AID itself
			(tab_AID[i]).AID [0] |= 0x80;
		}

		// Copy AID in the list
		memcpy (&(AIDList [elt.length]), (char *) &(tab_AID[i].AID), tab_AID[i].len_Aid);
		elt.length += tab_AID[i].len_Aid;
	}
	elt.ptValue = (unsigned char *) AIDList;
	TlvTree_AddChild(*phOutputTLVTree, elt.tag, elt.ptValue, elt.length);

	// Number of AID
	TlvTree_AddChild(*phOutputTLVTree, TAG_NB_AID_TERMINAL, (unsigned char *) &nb_aid, 1);

	// Add status code
	error_code = 0;
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &error_code, 2);

	CUDB_StoreTLVTree(phOutputTLVTree);
}


//===========================================================================
void EMVCUST_Get_AID_DATA_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned short found;
	short          select_result = DB_KO;
	unsigned short error_code;
	DataElement    Data_Elt;
	const unsigned long cst_tag_list[] = { TAG_TERMINAL_CAPABILITIES, TAG_ADD_TERMINAL_CAPABILITIES,
		TAG_POS_ENTRY_MODE_CODE, TAG_CUST_IS_CARDHOLDER_CONFIRMATION, TAG_CUST_IS_DEFAULT_DDOL,
		TAG_CUST_IS_FLOOR_LIMIT_CHECKING, TAG_CUST_IS_RANDOM_TRANSACTION_SELECT, TAG_CUST_IS_VELOCITY_CHECKING,
		TAG_CUST_IS_DEFAULT_TDOL, TAG_CUST_IS_ODA_PROCESSING, TAG_CUST_IS_ACCOUNT_TYPE,	TAG_CUST_IS_SKIP_DEFAULT,
		TAG_CUST_IS_SKIP_ONLINE, TAG_CUST_DETECT_FAIL_PRIOR_TAA, TAG_CUST_CDA_NEVER_REQUEST_ARQC_1GENAC,
		TAG_CUST_CDA_NEVER_REQUEST_ONLINE_2GENAC, TAG_ACQUIRER_IDENTIFIER, TAG_AID_PROPRIETARY,
		TAG_VERSION_NUMBER_TERMINAL, TAG_CERT_AUTH_PUB_KEY_CHECKSUM, TAG_CERT_AUTH_PUB_KEY_INDEX_TERM,
		TAG_DEFAULT_DDOL, TAG_DEFAULT_TDOL,	TAG_MAX_TARG_PERC_FOR_BIASED_RAND_SEL, TAG_MERCHANT_CATEGORY_CODE,
		TAG_MERCHANT_IDENTIFIER, TAG_TARG_PERC_FOR_BIASED_RAND_SEL, TAG_TERMINAL_ACTION_CODE_DEFAULT,
		TAG_TERMINAL_ACTION_CODE_DENIAL, TAG_TERMINAL_ACTION_CODE_ONLINE, TAG_TERMINAL_FLOOR_LIMIT,
		TAG_TRESH_VALUE_FOR_BIASED_RAND_SEL, TAG_TRANSACTION_CURRENCY_CODE, TAG_TRANSACTION_CURRENCY_EXP,
		TAG_TRANSACTION_REF_CURRENCY_CODE, TAG_TRANSACTION_REF_CURRENCY_CONV, TAG_TRANSACTION_REF_CURRENCY_EXP,
		TAG_CUST_APPLICATION_SELECTION_ID, TAG_SUPPORTED_PROPRIETARY_LIST, TAG_TSC_NOT_MANAGED,
		TAG_PROPRIETARY_TAGS_EX, TAG_CUST_SUBSEQUENT_BYPASS_PIN, TAG_CUST_IS_FORCED_ACCEPTANCE,
		TAG_CUST_IS_FORCED_ONLINE, TAG_CUST_IS_AMOUNT_UNKNOWN_BEFORE_CVM ,TAG_CUST_IS_SELECTABLE_KERNEL,TAG_CUST_IS_DELETABLE_TAC,TAG_CUST_LOG_DURING_TR,TAG_CUST_TRREACTIVATE_IS_ASKED};
	unsigned char StatusCode[2];


	error_code = 0;

	// Extract the AID from the input TLV Tree
	found = CUSERV_Extract_Element_TLV_Tree(phInputTLVTree, TAG_AID_PROPRIETARY, &Data_Elt);

	// search the database number associated with this AID
	if (found)
	{
		// Reset mark manager
		PAR_ResetMarkList();
		select_result = DB_OK;

		memcpy (Aid, Data_Elt.ptValue, Data_Elt.length);
		lg_Aid = Data_Elt.length;
		if (select_result == DB_OK)
			select_result = CUDB_Select_AID_Parameters (lg_Aid, Data_Elt.ptValue);

		if (select_result == DB_KO)
		{
			error_code = TAG_CUST_SERVICE_NOT_AVAILABLE;
		}
	}
	else
	{
		error_code = TAG_CUST_WRONG_TLV_TREE_INPUT_PARAMETER;
	}

	if (select_result == DB_OK)
	{
		//----------------------------------------------------------------------
		// Build a TLV tree with the data given by the acquirer
		// See SDE141 for the list
		//----------------------------------------------------------------------
		{
			// Add TAG_AID_PROPRIETARY tag
			TlvTree_AddChild(*phOutputTLVTree, Data_Elt.tag, Data_Elt.ptValue, Data_Elt.length);

			// Get data from TLVTree
			if (select_result == 0)
				// if no problem
				PAR_ReadParameterListTLVTree(cst_tag_list, sizeof (cst_tag_list) / sizeof(unsigned long), phOutputTLVTree);
		}
	}

	// Add tag status code
	ShortToChar(error_code, StatusCode);
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &StatusCode, 2);

}

//===========================================================================
void EMVCUST_Get_AID_Param_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned char  ucTransactionType;
#ifdef INT_TTYPE
	unsigned char  ucIntTransactionType;
#endif
	unsigned short found;
	short select_result = DB_KO;
	unsigned short error_code;
	DataElement Data_Elt;
	unsigned char StatusCode[2];

	error_code = 0;

	// Extract the AID from the input TLV Tree
	found = CUSERV_Extract_Element_TLV_Tree(phInputTLVTree, TAG_AID_PROPRIETARY, &Data_Elt);

	// Search the database number associated with this AID
	if (found)
	{
		// Reset mark manager
		PAR_ResetMarkList();
		select_result = CUDB_Select_AID_Parameters (Data_Elt.length, Data_Elt.ptValue);

		if (select_result == DB_KO)
		{
			error_code = TAG_CUST_SERVICE_NOT_AVAILABLE;
		}
	}
	else
	{
		error_code = TAG_CUST_WRONG_TLV_TREE_INPUT_PARAMETER;
	}


	// Build the output TLV tree

	if (select_result == DB_OK)
	{
		//----------------------------------------------------------------------
		// Build a TLV tree with the data given by the acquirer
		// See SES1967 for the list
		//----------------------------------------------------------------------

		TlvTree_AddChild(*phOutputTLVTree, TAG_TIME_OUT_PIN_CODE, (unsigned char *) TimeOutPINCode, 2);

		TlvTree_AddChild(*phOutputTLVTree, TAG_TIME_OUT_INTER_CAR, (unsigned char *) TimeOutInterCar, 2);

		// No KSU for the moment
		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_IS_KSU, (unsigned char *) CUSERV_FALSE, 2);

		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_IS_BLACK_LIST, (unsigned char *) CUSERV_FALSE, 2);

		/*&BEGIN FT/4209/MA  Force acceptance parameter is correctly managed */
		/*
		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_IS_PIN_BYPASS, (unsigned char *) CUSERV_TRUE, 2);

		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_IS_OFFLINE_ADVICE, (unsigned char *) CUSERV_FALSE, 2);

		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_IS_VOICE_REFERRAL, (unsigned char *) CUSERV_TRUE, 2);

		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_IS_FORCED_ONLINE, (unsigned char *) CUSERV_TRUE, 2);

		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_IS_FORCED_ACCEPTANCE, (unsigned char *) CUSERV_FALSE, 2);

		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_IS_ONLINE_ADVICE_IF_FORCED_ACCEPTANCE, (unsigned char *) CUSERV_FALSE, 2);
		*/
		/*&END FT/4209/MA  Force acceptance parameter is correctly managed */

		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_COMM_TYPE_APPLI, (unsigned char *) CUSERV_FALSE, 2);

		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_SERVICE_AUTHO_NUM, (unsigned char *) CUSERV_FALSE, 2);

		switch (ulTransactionType)
		{
		case CUSERV_REFUND_TRANSACTION :
			ucTransactionType = CUSERV_CREDIT_TYPE;
#ifdef INT_TTYPE
			ucIntTransactionType = TYPE_GOODS_SERVICES;
#endif
			break;

		case CUSERV_CASH_TRANSACTION :
			ucTransactionType = CUSERV_CASH_TYPE;
#ifdef INT_TTYPE
			ucIntTransactionType = TYPE_CASH;
#endif
			break;

#ifdef INT_TTYPE
		case CUSERV_CASHBACK_TRANSACTION :
			ucTransactionType = CUSERV_CASHBACK_TRANSACTION;
			ucIntTransactionType = TYPE_CASHBACK;
			break;
#endif

		default :
			// Default transaction is debit
			ucTransactionType = (unsigned char)ulTransactionType;
#ifdef INT_TTYPE
			ucIntTransactionType = TYPE_GOODS_SERVICES;
#endif
			break;
		}
		TlvTree_AddChild(*phOutputTLVTree, TAG_TRANSACTION_TYPE, &ucTransactionType, 1);
#ifdef INT_TTYPE
		TlvTree_AddChild(*phOutputTLVTree, TAG_INT_TRANSACTION_TYPE, &ucIntTransactionType, 1);
#endif
	}

	// Add tag status code
	ShortToChar(error_code, StatusCode);
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &StatusCode, 2);


	// Store data into CUDB
	CUDB_StoreTLVTree(phOutputTLVTree);
}

//===========================================================================
void EMVCUST_Get_AID_ICS_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned short found;
	short select_rsp;
	unsigned short error_code;
	DataElement Data_Elt;
	const unsigned long RequiredTags[] = {TAG_TERMINAL_TYPE, TAG_TERMINAL_COUNTRY_CODE,
		TAG_TRANSACTION_CURRENCY_CODE, TAG_TERMINAL_CAPABILITIES, TAG_ADD_TERMINAL_CAPABILITIES,
		TAG_CUST_IS_MULTILANG_SUPPORTED, TAG_CUST_IS_REVOK_SUPPORTED, TAG_CUST_IS_DEFAULT_DDOL,
		TAG_CUST_IS_PIN_BYPASS, TAG_CUST_IS_GETDATA_PIN_TRY_COUNTER,
		TAG_CUST_IS_POS_ENTRY_MODE, TAG_CUST_POS_ENTRY_VALUE, TAG_CUST_IS_DEFAULT_DDOL,
		TAG_CUST_IS_FLOOR_LIMIT_CHECKING, TAG_CUST_IS_RANDOM_TRANSACTION_SELECT,
		TAG_CUST_IS_VELOCITY_CHECKING, TAG_CUST_IS_EXCEPTION_FILE, TAG_CUST_IS_TRANSACTION_LOG,
		TAG_CUST_IS_FORCED_ONLINE, TAG_CUST_IS_FORCED_ACCEPTANCE, TAG_CUST_IS_ONLINE_ADVICE,
		TAG_CUST_IS_ISSUER_REFERRAL, TAG_CUST_IS_CARD_REFERRAL, TAG_CUST_IS_BATCH_CAPTURE,
		TAG_CUST_IS_ONLINE_CAPTURE, TAG_CUST_IS_DEFAULT_TDOL, TAG_POS_ENTRY_MODE_CODE,
		TAG_CUST_IS_PINPAD, TAG_CUST_IS_AMOUNT_PIN_SAME, TAG_CUST_TRM_OVERPASS_AIP,
		TAG_CUST_IS_SKIP_DEFAULT, TAG_CUST_IS_SKIP_ONLINE, TAG_CUST_IS_ODA_PROCESSING,
		TAG_CUST_IS_ACCOUNT_TYPE, TAG_CUST_DETECT_FAIL_PRIOR_TAA, TAG_CUST_CDA_NEVER_REQUEST_ARQC_1GENAC,
		TAG_CUST_CDA_NEVER_REQUEST_ONLINE_2GENAC, TAG_CUST_SUBSEQUENT_BYPASS_PIN,
		TAG_CUST_IS_CARDHOLDER_CONFIRMATION,TAG_CUST_IS_AMOUNT_UNKNOWN_BEFORE_CVM,TAG_CUST_IS_SELECTABLE_KERNEL,TAG_CUST_IS_DELETABLE_TAC,TAG_CUST_LOG_DURING_TR,TAG_CUST_TRREACTIVATE_IS_ASKED };
	unsigned char StatusCode[2];



	// Local variables initialisation
	error_code = 0;

	// Extract the AID from the input TLV Tree
	found = CUSERV_Extract_Element_TLV_Tree(phInputTLVTree, TAG_AID_PROPRIETARY, &Data_Elt);

	// search the database number associated with this AID
	if (found)
	{
		// Reset mark manager
		PAR_ResetMarkList();

		memcpy (Aid, Data_Elt.ptValue, Data_Elt.length);
		lg_Aid = Data_Elt.length;
		select_rsp = CUDB_Select_AID_Parameters (lg_Aid, Data_Elt.ptValue);
		if (select_rsp == DB_KO)
		{
			found = 0;
			error_code = TAG_CUST_SERVICE_NOT_AVAILABLE;
		}
	}
	else
	{
		error_code = TAG_CUST_WRONG_TLV_TREE_INPUT_PARAMETER;
	}

	if (found)
	{
		//----------------------------------------------------------------------
		// Build a TLV tree with the data given by the acquirer
		// See SDE141 for the list
		//----------------------------------------------------------------------

		// Read the list of tags in the database
		// Main mark activation made by CUDB_Select_AID_Parameters()
		PAR_ReadParameterListTLVTree(RequiredTags, sizeof (RequiredTags) / sizeof(unsigned long), phOutputTLVTree);

	}

	// Add tag status code
	ShortToChar(error_code, StatusCode);
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &StatusCode, 2);

}


//===========================================================================
void InitDefaut(int flag,int offset)
{
	int MAXX, MAXY;

	// large display
	GetScreenSize(&MAXY,&MAXX);
	if (MAXY==128)
		Menu.Fenetre.nblines        = 8;
	else
		Menu.Fenetre.nblines        = 4;

	Menu.Fenetre.left           = 0;
	Menu.Fenetre.top            = 0;
	Menu.Fenetre.rigth          = (MAXX-1);
	Menu.Fenetre.bottom         = (MAXY-1);
	Menu.Fenetre.fontsize       = _MEDIUM_;
	Menu.Fenetre.type           = _PROPORTIONNEL_;
	Menu.Fenetre.police         = 0;
	Menu.Fenetre.correct        = flag;
	Menu.Fenetre.offset         = offset;
	Menu.Fenetre.shortcommand   = _ON_;
	Menu.Fenetre.selected       = _OFF_;
	Menu.Fenetre.thickness      = 2;
	Menu.Fenetre.border         = _ON_;
	Menu.Fenetre.popup          = _NOPOPUP_;
	Menu.Fenetre.first          = 0;
	Menu.Fenetre.current        = 0;
	Menu.Fenetre.time_out       = 120;
}

//===========================================================================
void InitStructList(StructListe *pMenu, int flag, int offset)
{
	int MAXX, MAXY;
	GetScreenSize(&MAXY,&MAXX);
	if (MAXY==128)
		pMenu->Fenetre.nblines        = 8;
	else
		pMenu->Fenetre.nblines        = 4;
	pMenu->Fenetre.left           = 0;
	pMenu->Fenetre.top            = 0;
	pMenu->Fenetre.rigth          = (MAXX-1);
	pMenu->Fenetre.bottom         = (MAXY-1);
	pMenu->Fenetre.fontsize       = _MEDIUM_;
	pMenu->Fenetre.type           = _PROPORTIONNEL_;
	pMenu->Fenetre.police         = 0;
	pMenu->Fenetre.correct        = flag;
	pMenu->Fenetre.offset         = offset;
	pMenu->Fenetre.shortcommand   = _ON_;
	pMenu->Fenetre.selected       = _OFF_;
	pMenu->Fenetre.thickness      = 2;
	pMenu->Fenetre.border         = _ON_;
	pMenu->Fenetre.popup          = _NOPOPUP_;
	pMenu->Fenetre.first          = 0;
	pMenu->Fenetre.current        = 0;
	pMenu->Fenetre.time_out       = 120;
}

#define ACCES_FCT0(a)                       (a)()

void EMVCUST_More_Function_TLVTree(TLV_TREE_NODE *phOutputTLVTree) // TLV_TREE_NODE *phInputTLVTree
{
	unsigned char  cr;
	unsigned char  index;
	unsigned short error_code;
	// unsigned short found;
	int            merchLang;
	// DataElement elt;
	ENTRY_BUFFER  buffer;
	StructListe Menu;

	// Retreive Terminal merchant language
	merchLang = PSQ_Give_Language();

	// release global TLV tree
	TlvTree_ReleaseEx(&CUMORE_Tree);

	CUMORE_Tree = TlvTree_New(0);

	// Extract ENGINE application number from the input TLV tree
//_	found = CUSERV_Extract_Element_TLV_Tree(phInputTLVTree, TAG_EG_NUM_APPLI, &elt);

	// search the database number associated with this AID
//_	if (found)
//_	{

	InitStructList(&Menu, _ON_, 1);

	//InitDefaut(_ON_,1);

	// table init from const
	Menu.Fenetre.titre = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_EMV_APP, merchLang);

#ifdef _USE_UCM_
	if(UCM_Present)
	{
		Menu.tab[0] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, NavigationEmvdc[4].itemlabel, merchLang);
		Menu.tab[1] = NULL;
	}
	else
#endif
	{
		for (index=0 ; index < ELVEC(NavigationEmvdc) ; index++ )
		{
			Menu.tab[index] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, NavigationEmvdc[index].itemlabel, merchLang);
		}

		// Last item

		Menu.tab[index] = NULL;
	}

	G_List_Entry(&Menu);


	ttestall(ENTRY,0);
	cr=Get_Entry(&buffer);

	switch(cr)
	{
	case CR_ENTRY_OK :
#ifdef _USE_UCM_
		if(UCM_Present)
			ACCES_FCT0 (NavigationEmvdc[4].function);
		else
#endif
		 ACCES_FCT0 (NavigationEmvdc[buffer.d_entry[0]].function);
		break;
	}


//_	}


	// Build an output TLV tree

	// Copy result TLV tree in phOutputTLVTree
	*phOutputTLVTree = TlvTree_Copy(CUMORE_Tree);

	error_code = 0;
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &error_code, 2);
}

//===========================================================================
void EMVCUST_KeyManagement_TLVTree(unsigned char Val_Key, unsigned char* OutKey)
{

	*OutKey = Val_Key;

	// release global TLV tree
	TlvTree_ReleaseEx(&CUMORE_Tree);

	CUMORE_Tree = TlvTree_New(0);

	switch (Val_Key)
	{
		case T_F1 :		// Debit
#ifndef _DONT_USE_F1_KEY_
			CUMORE_Debit();
			*OutKey = T_ANN;
#endif
			break;

		case T_F2 :		// Refund
#ifndef _DONT_USE_F2_KEY_
			CUMORE_Refund();
			*OutKey = T_ANN;
#endif
			break;

		case T_F4 :		// Refund


			break;

		case T_NUM0:
		case T_NUM1:
		case T_NUM2:
		case T_NUM3:
		case T_NUM4:
		case T_NUM5:
		case T_NUM6:
		case T_NUM7:
		case T_NUM8:
		case T_NUM9:
		case T_VAL :
		case T_POINT :
			break;

		default :
			break;
	}
}

//===========================================================================
void EMVCUST_Periodic_Call_TLVTree(TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned char text[26];
	unsigned short error_code;
	int cmpdate;
	int is_time_batch_capture;
	int merchLang;
	DATE date;
	char * pc_l_DisplayTxt;
	unsigned char StatusCode[2];

      
	// Retreive Terminal merchant language
	merchLang = PSQ_Give_Language();

	error_code = 0;

	// Check If new parameters are present
	if (CUSERV_New_Parameters)
	{
		error_code = TAG_CUST_NEW_PARAMETERS;
		CUSERV_New_Parameters = FALSE;
	}
	else
	{
		error_code = 0;
	}

	// Check If it's time to make a data batch capture

	// Read current date
	is_time_batch_capture = FALSE;
	read_date(&date);
	CUBATCH_GetNextTransfDate (&DateNextTransf);

	// Is it time to run the next periodic call ?
	cmpdate = SLSQ_TimeGapInSeconds (&DateNextTransf, &date);
	if (cmpdate == 0)
	{
			is_time_batch_capture = TRUE;
	}
	else if (cmpdate > 0)
	{
		is_time_batch_capture = TRUE;
	}

	if (is_time_batch_capture == TRUE)
	{
		// Perform periodic call
		CUMORE_BatchCapt ();
		// Update the date to the next periodic call = tomorrow
		USQ_Ajouterjour(1, &date);
		// change just the date and not the hour
		memcpy(&DateNextTransf, &date, 6);
		CUBATCH_SetNextTransfDate (&DateNextTransf);

		CUTERMprintLine(" ");

		pc_l_DisplayTxt = CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CNS_MESS_NEXT_DATA_CAPTURE, merchLang);

		CUTERMprintLine(pc_l_DisplayTxt);

		sprintf ((char *) text, "%.2s/%.2s/%.2s  %.2s:%.2s", date.day, date.month, date.year, date.hour, date.minute);
		CUTERMprintLine((char *)text);

		CUTERMpaperFeed();
	}

	ShortToChar(error_code, StatusCode);
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &StatusCode, 2);


   
}

//===========================================================================
void EMVCUST_Process_Step_TlvTree(int function, TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned char  buf[11];
	unsigned short usCardholderLang, usMerchantLang;
	unsigned short found;
	unsigned short error_code;

	DataElement Data_Elt;

	CUDB_Get_cardholder_language (&usCardholderLang);
	usMerchantLang = PSQ_Give_Language();
	if (usMerchantLang > C_NBLANGMERCH)
	{
		usMerchantLang = 0;
	}

	found = CUSERV_Extract_Element_TLV_Tree(phInputTLVTree, TAG_SERVICE_STATUS_CODE, &Data_Elt);

	if (found)
	{
		// Modification for EFT30
		error_code = CharToShort(Data_Elt.ptValue);
	}
	else
	{
		error_code = 0;
	}

	switch (function)
	{
		case EMVDC_START:
			// step only called if the debit is asked by the menu
			EMVDC_START_Function(&error_code, phOutputTLVTree);
			break;

		case EMVDC_APPLICATION_SELECTION:
			EMVDC_APPLICATION_SELECTION_Function_TlvTree(&error_code, &usMerchantLang, phInputTLVTree, phOutputTLVTree);
			break;

		case EMVDC_INITIATE_APPLICATION_PROCESSING:
			// No function
			break;

		case EMVDC_READ_APPLICATION_DATA:
			EMVDC_READ_APPLICATION_DATA_Function_TlvTree(&error_code, phOutputTLVTree);
			break;

		case EMVDC_OFFLINE_DATA_AUTHENTICATION:
			EMVDC_OFFLINE_DATA_AUTHENTICATION_Function_TlvTree(&error_code, phOutputTLVTree);
			break;

		case EMVDC_PROCESSING_RESTRICTIONS:
			// No function
			break;

		case EMVDC_CARDHOLDER_VERIFICATION:
			// No function
			break;

		case EMVDC_CARDHOLDER_VERIFICATION_FIRST:
			EMVDC_CARDHOLDER_VERIFICATION_FIRST_Function_Tlvtree(&error_code, phInputTLVTree, phOutputTLVTree);
			break;

		case EMVDC_CARDHOLDER_VERIFICATION_OTHER:
			EMVDC_CARDHOLDER_VERIFICATION_OTHER_Function_Tlvtree(&error_code, phInputTLVTree, phOutputTLVTree);
			break;

		case EMVDC_TERMINAL_RISK_MANAGEMENT:
			EMVDC_TERMINAL_RISK_MANAGEMENT_Function_Tlvtree(&error_code, phOutputTLVTree);
			break;

		case EMVDC_TERMINAL_ACTION_ANALYSIS:
			// No function
			break;

		case EMVDC_CARD_ACTION_ANALYSIS:
			EMVDC_CARD_ACTION_ANALYSIS_Function_Tlvtree(&error_code, phOutputTLVTree);
			break;

		case EMVDC_ON_LINE_PROCESSING:
			EMVDC_ON_LINE_PROCESSING_Function_Tlvtree(&error_code, &usMerchantLang, phInputTLVTree, phOutputTLVTree);
			break;

		case EMVDC_ISSUER_TO_CARD_SCRIPT_PROCESSING1:
			// No function
			break;

		case EMVDC_COMPLETION:
			EMVDC_COMPLETION_Function_Tlvtree(&error_code, phOutputTLVTree);
			break;

		case EMVDC_ISSUER_TO_CARD_SCRIPT_PROCESSING2:
			// No function
			break;

		case EMVDC_STOP:
			EMVDC_STOP_Function_Tlvtree(&error_code, &usMerchantLang);
			break;

		case EMVDC_INITIATE_TRLOG_PROCESSING:
			isTrlog = TRUE;
			break;

		case EMVDC_READ_TRLOG_DATA:
			EMVDC_READ_TRLOG_DATA_Function_Tlvtree(&error_code, phInputTLVTree);
			break;

		default :
			break;
	}	// End switch (function)


	ShortToChar(error_code,buf);
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, (unsigned char *) buf, 2);

}

//**************************
// PROCESS_STEP FUNCTIONS
//**************************

//===========================================================================
//! \brief This function manages the START Process_step state. Several variables
//! are initialized in this step.
//! \param[out] error_code : function result (not modified by this function).
//===========================================================================
static void EMVDC_START_Function(unsigned short * error_code, TLV_TREE_NODE *phOutTLVTree)
{
	unsigned char buf[2];
	CUTERMclearDisplay();
	CUTERMclearPPdisplay();
	status_tr = STATUS_TR_PROCESSING_ERROR;
	signature_asked = FALSE;
	nb_try_pin_offline = 1;
	nb_try_pin_online = 1;

	reversal_requested = FALSE;

	// P30 management
	isPinpad = B_NON_INIT;

	// Proprietary method for CVM list
	ProprietaryMethodFirst= FALSE;

	// Get transaction Log from ICC for PBOC
	isTrlog = FALSE;

	CUPAR_ResetAdditionnalICS();
	CUPAR_ResetAdditionnalAID();
	CUPAR_ResetAdditionnalKRevok();
	if (TransactionReactivateAsked == TRUE)
		ShortToChar(TransactionReactivateAsked,buf);
	else
		memclr(buf,2);
	TlvTree_AddChild(*phOutTLVTree, TAG_CUST_TRREACTIVATE_IS_ASKED, (unsigned char *) buf, 2);
}

//===========================================================================
//! \brief This function manages manages the APPLICATION_SELECTION
//! Process_step state.
//! \param[out] error_code : function result.
//! \param[in] ptr_usMerchantLang : language information used by the Merchant.
//! \param[in] phInTLVTree : input TLV tree containing the following tags :
//! - \ref TAG_SERVICE_STATUS_CODE
//! - \ref TAG_NUMBER_OF_MATCHING_APP
//! - \ref TAG_CARDHOLDER_CONFIRMATION
//! - \ref TAG_AID_ICC
//! - \ref TAG_APPLICATION_LABEL
//! - \ref TAG_APPLICATION_PREFFERRED_NAME
//! - \ref TAG_LANGUAGE_PREFERENCE
//! - \ref TAG_ISSUER_CODE_TABLE_INDEX
//! - \ref TAG_APPLI_PRIOR_IND
//! - \ref TAG_SERVICE_STATUS_CODE
//! - \ref TAG_AID_PROPRIETARY
//! - \ref TAG_TRANSACTION_CURRENCY_CODE
//! - \ref TAG_TRANSACTION_CURRENCY_EXP
//! - \ref TAG_EG_IS_AMOUNT_NEEDED
//! \param[out] phOutTLVTree : output TLV tree containing the following tags :
//! - \ref TAG_AMOUNT_AUTH_BIN
//! - \ref TAG_AMOUNT_AUTH_NUM
//! - \ref TAG_AMOUNT_OTHER_BIN
//! - \ref TAG_AMOUNT_OTHER_NUM
//! - \ref TAG_TRANSACTION_DATE
//! - \ref TAG_TRANSACTION_TIME
//! - \ref TAG_PP_OK
//! - \ref TAG_CUST_CA_REVOK_1
//! - \ref TAG_CUST_POS_ISO8583_93
//! - \ref TAG_CUST_FORCED_ONLINE_REQUEST
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
static void EMVDC_APPLICATION_SELECTION_Function_TlvTree(unsigned short * error_code, unsigned short *ptr_usMerchantLang, TLV_TREE_NODE *phInTLVTree, TLV_TREE_NODE *phOutTLVTree)
{
	unsigned char pinpadok;
	unsigned char TabAmount [4];
	unsigned char buf[11];
	unsigned short usCardholderLang;
	unsigned short found;
	short base_number;
	unsigned short currency_code;
	unsigned long entered_amount;
	int result;
	DataElement Data_Elt;
	DataElement elt;
#ifdef _TOOLWARE_
	unsigned long ulFin_ihm   = 0;
	unsigned long ulDebut_ihm = 0;
#endif
	char * pc_l_DisplayTxt;

	result        = 0;
	base_number   = 0;
	currency_code = 0;

	// IHM time calculation
#ifdef _TOOLWARE_
	if (ucAdvancedMode == TRUE)
	{
		ulHOST_comm  = 0;
		ulMMI_pin_on_line  = 0;
		ulMMI_pin_off_line = 0;
		ulMMI_amount = 0;
		ulMMI_account_type = 0;
		ulMMI_force_OLP  = 0;
		ulMMI_force_CAA  = 0;
		ulMMI_force_COMP = 0;
	}
#endif

	CUDB_Get_cardholder_language (&usCardholderLang);
	*ptr_usMerchantLang = PSQ_Give_Language();
	if (*ptr_usMerchantLang > C_NBLANGMERCH)
	{
		*ptr_usMerchantLang = 0;
	}

	isConnected = FALSE;

	TransacOk = FALSE;

	CommProblem = FALSE;

	signature_asked = FALSE;
	status_tr = STATUS_TR_PROCESSING_ERROR;

	// Initialise the data base for the current transaction
	memclr(Aid, LEN_AID);
	lg_Aid = 0;
	CUSERV_CommRetries = 0;

	pc_l_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_WELCOME, usCardholderLang);
	CUTERMclearPPdisplay();

	pinpadok = CUTERIsDeclaredPPPresent(pc_l_DisplayTxt);

	//----------------------------------------------------------------------
	// Amount Entry
	//----------------------------------------------------------------------

	// Amount is already entered ?
	found = CUSERV_Extract_Element_TLV_Tree(phInTLVTree, TAG_EG_IS_AMOUNT_NEEDED, &Data_Elt);

	if (found)
	{
		if ( (Data_Elt.ptValue[0] == 0x00) && (Data_Elt.ptValue[1] == 0x01) )
		{
			// Default case : only debit transaction
			ulTransactionType = CUSERV_DEBIT_TRANSACTION;

			// Extract the AID from the input TLV tree
			found = CUSERV_Extract_Element_TLV_Tree(phInTLVTree, TAG_AID_PROPRIETARY, &Data_Elt);

			if (found)
			{
				// AID found. Retrieve the database associated with this AID
				base_number = CUDB_Select_AID_Parameters (Data_Elt.length, Data_Elt.ptValue);
				if (base_number == DB_KO)
					found = 0;
			}

			if (found)
			{
				// Get data from TLVTree
				found = PAR_ReadParameter(TAG_TRANSACTION_CURRENCY_CODE, (DataElementExt *)&elt);
				if (found)
					currency_code = CharToShort(elt.ptValue);
			}

			if (found)
			{
				// IHM calculation time
#ifdef _TOOLWARE_
				if (ucAdvancedMode == TRUE)
				{
					ulDebut_ihm = get_tick_counter();
				}
#endif
				// Read the amount, using the good currency code
#ifdef _USE_UCM_
				if(UCM_Present)
				{
					found = CUSERV_Extract_Element_TLV_Tree(phInTLVTree, TAG_AMOUNT_AUTH_BIN, &Data_Elt);
					if(found)
					{
						entered_amount = CharToLong(Data_Elt.ptValue);
						result = 1;
					}
				}
				else
#endif
				{
					if (TransactionLoopMode == TRUE)
					{
						if (loop_amount == 0)
						{
							result = CUMESS_GetAmount (currency_code, &entered_amount);
							if ((result) && (result!=T_ANN) && (entered_amount!=0))
							{
								loop_amount = entered_amount;
							}
						}
						else
						{
							entered_amount = loop_amount;
							result = T_VAL;
						}
					}
					else
					result = CUMESS_GetAmount (currency_code, &entered_amount);
				}

				// IHM calculation time
#ifdef _TOOLWARE_
				if (ucAdvancedMode == TRUE)
				{
					ulFin_ihm = get_tick_counter();
					ulMMI_amount = ulFin_ihm - ulDebut_ihm;
				}
#endif

				// Build an output TLV tree

				if ((result) && (result!=T_ANN) && (entered_amount!=0))
				{
					unsigned char NumAmount [6];
					// Store informations into CUDB Current
					// Store amounts in current database

					// Amount is valid, Convert in num
					CUMESS_ConvertBinNUM (entered_amount, NumAmount);

					LongToChar (entered_amount, TabAmount);
					TlvTree_AddChild(*phOutTLVTree, TAG_AMOUNT_AUTH_BIN, TabAmount, 4);

					TlvTree_AddChild(*phOutTLVTree, TAG_AMOUNT_AUTH_NUM, NumAmount, 6);

					LongToChar (0, TabAmount);
					TlvTree_AddChild(*phOutTLVTree, TAG_AMOUNT_OTHER_BIN, TabAmount, 4);

					// Convert in num
					// TAG_AMOUNT_OTHER_NUM is faultly set in a debit Transaction
					CUMESS_ConvertBinNUM (0, NumAmount);

					TlvTree_AddChild(*phOutTLVTree, TAG_AMOUNT_OTHER_NUM, NumAmount, 6);

				}
				else
				{
					// amount = 0 or CANCEL
					*error_code = TAG_CUST_TRANSACTION_CANCELLED;
					status_tr = STATUS_TR_CANCELLED;
				}
			}
		}
	}

	CUTERMclearDisplay();

	{
		// Date and time management
		DATE date;
		unsigned char heure_dcb [3];
		unsigned char date_dcb [3];
		read_date(&date);

		// Date of the transaction
		Aschex(&date_dcb[0],date.year,2);
		Aschex(&date_dcb[1],date.month,2);
		Aschex(&date_dcb[2],date.day,2);

		// Time of the transaction
		Aschex(&heure_dcb[0],date.hour,2);
		Aschex(&heure_dcb[1],date.minute,2);
		Aschex(&heure_dcb[2],date.second,2);

		TlvTree_AddChild(*phOutTLVTree, TAG_TRANSACTION_DATE, (unsigned char *) date_dcb, 3);

		TlvTree_AddChild(*phOutTLVTree, TAG_TRANSACTION_TIME, (unsigned char *) heure_dcb, 3);
	}

	TlvTree_AddChild(*phOutTLVTree, TAG_PP_OK, (unsigned char *) &pinpadok, 1);

	// Extract the AID from the input TLV tree
	found = CUSERV_Extract_Element_TLV_Tree(phInTLVTree, TAG_AID_PROPRIETARY, &Data_Elt);

	// Searches the database number associated with this AID
	if (found)
	{
		T_CUSERV_lst_tagCArevok CA_revok;
		memcpy (Aid, Data_Elt.ptValue, Data_Elt.length);

		// Searches the list of revoked certificates with this AID
		found = CUPAR_GiveRevokedCA  (Aid, &CA_revok);
		if (found)
		{
			int i;

			// Revoked CA found, copy in the outpout TLV tree
			for (i=0; i<MAX_NB_TAG_FOR_REVOKED_CA; i++)
			{
				if (CA_revok.Taglength[i] != 0)
				{
					TlvTree_AddChild(*phOutTLVTree, TAG_CUST_CA_REVOK_1+i, CA_revok.revoked_CA[i], CA_revok.Taglength[i]);
				}
			}
		}
	}

	if (Bypass_Required == ((CUSERV_TRUE[0] << 8) + CUSERV_TRUE[1]))
	{
		unsigned char BypassPIN;

		BypassPIN = 0x01;
		TlvTree_AddChild(*phOutTLVTree, TAG_BYPASS_PIN, (unsigned char *) &BypassPIN, 1);
	}

	// Initialization of Point of Service Entry Mode
	//            Pos_8583_93 [0]  = '5';    // Nominal Entry Mode : ICC
	//            Pos_8583_93 [1]  = '1';    // Nominal CVM : PIN
	//            Pos_8583_93 [2]  = '0';    // No card capture capability
	//            Pos_8583_93 [3]  = '1';    // Attended terminal
	//            Pos_8583_93 [4]  = '0';    // Cardholder present
	//            Pos_8583_93 [5]  = '1';    // Card present
	//            Pos_8583_93 [6]  = '5';    // Entry Mode : ICC
	//            Pos_8583_93 [7]  = '1';    // CVM : PIN
	//            Pos_8583_93 [8]  = '1';    // Cardholder authentified by ICC
	//            Pos_8583_93 [9]  = '3';    // Card Data output capability : ICC
	//            Pos_8583_93 [10] = '4';    // Print and receipt capable
	//            Pos_8583_93 [11] = 'C';    // up to 12 characters.
	memcpy((void *) Pos_8583_93, (void *) "51010151134C", LEN_CUST_POS_ISO8583_93);

	TlvTree_AddChild(*phOutTLVTree, TAG_CUST_POS_ISO8583_93, (unsigned char *) Pos_8583_93, LEN_CUST_POS_ISO8583_93);

	ShortToChar(TransactionForcedOnline,buf);
	TlvTree_AddChild(*phOutTLVTree, TAG_CUST_FORCED_ONLINE_REQUEST, (unsigned char *) buf, 2);
	if (TransactionReactivateAsked == TRUE)
		ShortToChar(TransactionReactivateAsked,buf);
	else
		memclr(buf,2);
	TlvTree_AddChild(*phOutTLVTree, TAG_CUST_TRREACTIVATE_IS_ASKED, (unsigned char *) buf, 2);
}

//===========================================================================
//! \brief This function manages the READ_APPLICATION_DATA Process_step state.
//! \param[out] error_code : function result.
//! \param[out] phOutTLVTree : output TLV tree built :
//! - \ref TAG_CUST_PAN_IN_BLACK_LIST
//! - \ref TAG_CERT_AUTH_PUB_KEY_MODULUS
//! - \ref TAG_CERT_AUTH_PUB_KEY_EXPONENT
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
static void EMVDC_READ_APPLICATION_DATA_Function_TlvTree(unsigned short *error_code, TLV_TREE_NODE *phOutTLVTree)
{
	unsigned short found,found2;
	unsigned char buf1[11];
	DataElement  Data_Elt, Data_Elt2;
	TLV_TREE_NODE hTree;
	static const unsigned long RequiredTags[] = { TAG_APPLI_PRIM_ACCOUNT_NB, TAG_CERT_AUTH_PUB_KEY_INDEX_ICC,
		TAG_AID_PROPRIETARY, TAG_APPLI_PRIM_ACCOUNT_NB_SEQ_NB };

#ifdef AMT_UNKNOWN
	const unsigned char cst_Unknown={0x01};
#endif
	// Get data from EMVDC

	// Retrieve Last APDU Command Response
	hTree = Engine_GetDataElement(TAG_LAST_APDU_CMD_RESPONSE);

	found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_LAST_APDU_CMD_RESPONSE, &Data_Elt);

	// release local TLV tree
	TlvTree_ReleaseEx(&hTree);

	if (found)
	{
		// Check if it was a Read Record
		if ((Data_Elt.ptValue [0] == 0x00)  &&    // CLA command
			(Data_Elt.ptValue [1] == 0xB2))       // INS command
		{
			unsigned char cmd_ok;

			// Check Response bytes SW1 SW2 for Exception handling
			cmd_ok = ((Data_Elt.ptValue [4] == 0x90) && (Data_Elt.ptValue [5] == 0x00))  ||
				((Data_Elt.ptValue [4] == 0x62) && (Data_Elt.ptValue [5] == 0x83))  ||
				((Data_Elt.ptValue [4] == 0x63) && (Data_Elt.ptValue [5] == 0x00))  ||
				((Data_Elt.ptValue [4] == 0x63) && ((Data_Elt.ptValue [5] & 0xF0) == 0xC0));
			if (!cmd_ok)
			{
				*error_code = TAG_CUST_CARD_ERROR;
				status_tr = STATUS_TR_CARD_ERROR;
			}
			// else we don't change error_code
		}
	}

	if (ulTransactionType == CUSERV_REFUND_TRANSACTION)
	{
		// This is a refund transaction, as defined in EPI document
		// Terminal Requirtments v4.0, chapter 14
		// Stop the transaction now
		*error_code = TAG_CUST_TRANSACTION_CANCELLED;
		status_tr = STATUS_TR_REFUND_APPROVED;
	}

	if ((*error_code != TAG_CUST_TRANSACTION_CANCELLED) && (*error_code != TAG_CUST_PROCESSING_ERROR))
	{
		unsigned char Modulus [255];
		unsigned short ModulusLength;
		unsigned char Exponent [3];
		unsigned short ExponentLength;

		//-----------------------------------------------------------------
		// Exception file Control
		//-----------------------------------------------------------------

		// Get data from EMVDC

		// Retreive PAN, Key Index, AID proprietary, PAN sequence number, from EMVDC
		hTree = Engine_GetDataElements(sizeof(RequiredTags) / sizeof(RequiredTags[0]), RequiredTags);

		found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APPLI_PRIM_ACCOUNT_NB, &Data_Elt);

		// PAN sequence number shall be controlled in exception file
		found2= CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APPLI_PRIM_ACCOUNT_NB_SEQ_NB, &Data_Elt2);

		if (found )
		{
			if (found2 )
			{
				CUSERV_IsInBlackList = CUBLACKL_IsInBlackList  (Data_Elt.ptValue, (unsigned short) Data_Elt.length,B_TRUE,Data_Elt2.ptValue[0]);
			}
			else
			{
				CUSERV_IsInBlackList = CUBLACKL_IsInBlackList  (Data_Elt.ptValue, (unsigned short) Data_Elt.length,B_FALSE,0);
			}
		}


		// Build an output TLV tree

		ShortToChar(CUSERV_IsInBlackList,buf1);
		TlvTree_AddChild(*phOutTLVTree, TAG_CUST_PAN_IN_BLACK_LIST, (unsigned char *)buf1, 2);

		// Extract the AID from the TLV tree read in EMVDC
		found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_AID_PROPRIETARY, &Data_Elt);

		// Search the database number associated with this AID
		if (found)
		{
			memcpy (Aid, Data_Elt.ptValue, Data_Elt.length);
			lg_Aid = Data_Elt.length;
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_CERT_AUTH_PUB_KEY_INDEX_ICC, &Data_Elt);

		if (found)
		{
			// Search the key linked with the AID and the index
			found = CUPAR_GiveKey  (Aid,
				(unsigned char) *(Data_Elt.ptValue),
				Modulus,
				&ModulusLength,
				Exponent,
				&ExponentLength);
			if (found)
			{
				// Key found, copy in the outpout TLV tree
				TlvTree_AddChild(*phOutTLVTree, TAG_CERT_AUTH_PUB_KEY_MODULUS, Modulus, ModulusLength);

				TlvTree_AddChild(*phOutTLVTree, TAG_CERT_AUTH_PUB_KEY_EXPONENT, Exponent, ExponentLength);
			}
		}

#ifdef AMT_UNKNOWN
		TlvTree_AddChild(*phOutTLVTree, TAG_CUST_IS_AMOUNT_UNKNOWN_BEFORE_CVM, &cst_Unknown, 1);
#endif
		// release local TLV tree
		TlvTree_ReleaseEx(&hTree);

	}

}

//===========================================================================
//! \brief This function manages the OFFLINE_DATA_AUTHENTICATION Process_step
//! state.
//! \param[out] error_code : function result.
//! \param[out] phOutTLVTree : output TLV tree built :
//! - \ref TAG_LAST_APDU_CMD_RESPONSE
//===========================================================================
static void EMVDC_OFFLINE_DATA_AUTHENTICATION_Function_TlvTree(unsigned short *error_code, TLV_TREE_NODE *phOutTLVTree)
{
	unsigned short found;
	DataElement Data_Elt;
	TLV_TREE_NODE hTree;

	// Retreive Last APDU Command Response
	hTree = Engine_GetDataElement(TAG_LAST_APDU_CMD_RESPONSE);

	found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_LAST_APDU_CMD_RESPONSE, &Data_Elt);

	if (found)
	{
		// Check if it was ans Internal Authenticate
		if ((Data_Elt.ptValue [0] == 0x00)  &&    // CLA command
			(Data_Elt.ptValue [1] == 0x88)  &&    // INS command
			(Data_Elt.ptValue [2] == 0x00)  &&    // P1 command
			(Data_Elt.ptValue [3] == 0x00))       // P2 command
		{
			unsigned char cmd_ok;

			// Check Response bytes SW1 SW2 for Exception handling
			cmd_ok = ((Data_Elt.ptValue [4] == 0x90) && (Data_Elt.ptValue [5] == 0x00))  ||
				((Data_Elt.ptValue [4] == 0x62) && (Data_Elt.ptValue [5] == 0x83))  ||
				((Data_Elt.ptValue [4] == 0x63) && ((Data_Elt.ptValue [5] & 0xF0) == 0xC0));
			if (!cmd_ok)
			{
				*error_code = TAG_CUST_CARD_ERROR;
				status_tr = STATUS_TR_CARD_ERROR;
			}
			// else we don't change error_code
		}
	}

	// Build an output TLV tree

	if (hTree != *phOutTLVTree)
	{
		TlvTree_AddChild(*phOutTLVTree, Data_Elt.tag, Data_Elt.ptValue, Data_Elt.length);
	}

	// release local TLV tree
	TlvTree_ReleaseEx(&hTree);
}

//===========================================================================
//! \brief This function manages the CARDHOLDER_VERIFICATION_FIRST Process_step
//! state.
//! \param[out] error_code : function result.
//! \param[out] phInTLVTree : input TLV tree containing the following tags :
//! - \ref TAG_SUPPORTED_PROPRIETARY_LIST
//! - \ref TAG_TIME_OUT_INTER_CAR
//! - \ref TAG_TIME_OUT_PIN_CODE
//! - \ref TAG_TRANSACTION_TYPE
//! - \ref TAG_AMOUNT_AUTH_BIN
//! - \ref TAG_AMOUNT_AUTH_NUM
//! - \ref TAG_AMOUNT_OTHER_BIN
//! - \ref TAG_AMOUNT_OTHER_NUM
//! - \ref TAG_TRANSACTION_CURRENCY_CODE
//! - \ref TAG_TRANSACTION_CURRENCY_EXP
//! - \ref TAG_SUBSEQUENT_BYPASS_PIN
//! - \ref TAG_SERVICE_STATUS_CODE
//! - \ref TAG_REMAINING_PIN
//! - \ref TAG_STATUS_CVP
//! - \ref TAG_EG_CARDHOLDER_LANGUAGE
//! \param[out] phOutTLVTree : output TLV tree built :
//! - \ref TAG_AUTOMATE
//! - \ref TAG_PIN_CODE
//! - \ref TAG_RESULT_PROPRIETARY_METHOD
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
static void EMVDC_CARDHOLDER_VERIFICATION_FIRST_Function_Tlvtree(unsigned short * error_code, TLV_TREE_NODE *phInTLVTree, TLV_TREE_NODE *phOutTLVTree)
{
	unsigned char RepCVF, dummy;
	unsigned short found;
#ifdef _TOOLWARE_
	unsigned long ulDebut_ihm = 0;
	unsigned long ulFin_ihm   = 0;
#endif
	ENTRY_BUFFER buffer_pin;
	DataElement Data_Elt;

	buffer_pin.d_len = 12;
	memclr(buffer_pin.d_entry, 12);

	// Signature ?
	found = CUSERV_Extract_Element_TLV_Tree(phInTLVTree, TAG_SIGNATURE, &Data_Elt);

	if (found)
	{
		signature_asked = Data_Elt.ptValue[0];
	}

	// Enter pin or not ?
	found = CUSERV_Extract_Element_TLV_Tree(phInTLVTree, TAG_STATUS_CVP, &Data_Elt);

	if (found)
	{
		switch (*(Data_Elt.ptValue))
		{
		case INPUT_PIN_ON :
			// IHM time calculation
#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_ihm = get_tick_counter();
			}
#endif

      	StopBeep();
      		
			// Refashion of Pin Pad management file
			RepCVF = CallEnterPinOnLine(nb_try_pin_online, &buffer_pin);

         ReStartBeep();


			// IHM time calculation
#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulFin_ihm = get_tick_counter();
				ulMMI_pin_on_line += (ulFin_ihm - ulDebut_ihm);
			}
#endif

			nb_try_pin_online ++;
			break;

		case INPUT_PIN_OFF :
			// IHM time calculation
#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_ihm = get_tick_counter();
			}
#endif
			StopBeep();
			// Refashion of Pin Pad management file
			RepCVF = CUPIN_EnterPinOffLine(nb_try_pin_offline, TRUE, &buffer_pin, &dummy, &Bypass_Required);
			ReStartBeep();

			// IHM time calculation
#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulFin_ihm = get_tick_counter();
				ulMMI_pin_off_line += (ulFin_ihm - ulDebut_ihm);
			}
#endif
			nb_try_pin_offline ++;
			break;

		case NO_INPUT :
			RepCVF = NO_INPUT;			// END_OF_CV
			break;

		case NO_REMAINING_PIN :
			RepCVF = NO_REMAINING_PIN;	//END_OF_CV
			break;

		default :
			// Proprietary method for CVM list
			if (*(Data_Elt.ptValue)==PROPRIETARY_METHOD)
			{
				ProprietaryMethodFirst= TRUE;
				RepCVF = CU_EnterProprietaryMethod();
			}
			else
				RepCVF = 0;				// END_OF_CV
			break;
		}
	}

	// IHM time calculation
#ifdef _TOOLWARE_
	else
	{
		if (ucAdvancedMode == TRUE)
		{
			ulMMI_pin_off_line = 0;
			ulMMI_pin_on_line = 0;
		}
	}
#endif

	// Build an output TLV tree

	TlvTree_AddChild(*phOutTLVTree, TAG_AUTOMATE, (unsigned char *) &RepCVF, 1);

	if (Bypass_Required == ((CUSERV_TRUE[0] << 8) + CUSERV_TRUE[1]))
	{
		unsigned char BypassPIN;

		BypassPIN = 0x01;
		TlvTree_AddChild(*phOutTLVTree, TAG_BYPASS_PIN, (unsigned char *) &BypassPIN, 1);
	}

	TlvTree_AddChild(*phOutTLVTree, TAG_PIN_CODE, (unsigned char *) buffer_pin.d_entry, buffer_pin.d_len);

	// Proprietary method for CVM list
	TlvTree_AddChild(*phOutTLVTree, TAG_RESULT_PROPRIETARY_METHOD, (unsigned char *) &buffer_result, 1);
}

//===========================================================================
//! \brief This function manages the CARDHOLDER_VERIFICATION_OTHER Process_step
//! state.
//! \param[out] error_code : function result.
//! \param[out] phInTLVTree : input TLV tree containing the following tags :
//! - \ref TAG_AUTOMATE
//! - \ref TAG_PIN_CODE
//! - \ref TAG_RESULT_PROPRIETARY_METHOD
//! - \ref TAG_SERVICE_STATUS_CODE
//! - \ref TAG_REMAINING_PIN
//! - \ref TAG_STATUS_CVP
//! - \ref TAG_EG_CARDHOLDER_LANGUAGE L:02 (2) V: 66 72
//! \param[out] phOutTLVTree : output TLV tree built :
//! - \ref TAG_AUTOMATE
//! - \ref TAG_PIN_CODE
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
static void EMVDC_CARDHOLDER_VERIFICATION_OTHER_Function_Tlvtree(unsigned short * error_code, TLV_TREE_NODE *phInTLVTree, TLV_TREE_NODE *phOutTLVTree)
{
	unsigned char RepCVF, dummy;
	unsigned short found;
	DataElement Data_Elt;
	ENTRY_BUFFER buffer_pin;

	// Variables needed for IHM time calculation
#ifdef _TOOLWARE_
	unsigned long ulDebut_ihm = 0;
	unsigned long ulFin_ihm   = 0;
#endif

	buffer_pin.d_len = 12;
	memclr(buffer_pin.d_entry, 12);

	// Signature ?
	found = CUSERV_Extract_Element_TLV_Tree(phInTLVTree, TAG_SIGNATURE, &Data_Elt);

	if (found)
	{
		signature_asked = Data_Elt.ptValue[0];
	}

	// Enter pin or not ?
	found = CUSERV_Extract_Element_TLV_Tree(phInTLVTree, TAG_STATUS_CVP, &Data_Elt);

	if (found)
	{
		switch (*(Data_Elt.ptValue))
		{
		case INPUT_PIN_ON :
			// IHM time calculation
#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_ihm = get_tick_counter();
			}
#endif


      		StopBeep();
 
			// Refashion of Pin Pad management file
			RepCVF = CallEnterPinOnLine(nb_try_pin_online, &buffer_pin);

      		ReStartBeep();
 
			// IHM time calculation
#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulFin_ihm = get_tick_counter();
				ulMMI_pin_on_line += (ulFin_ihm - ulDebut_ihm);
			}
#endif

			nb_try_pin_online ++;

			CUTERMclearDisplay();
			CUTERMclearPPdisplay();
			break;

		case INPUT_PIN_OFF :
			if (ProprietaryMethodFirst == FALSE)
			{
				CUTERMclearDisplay();
				CUTERMclearPPdisplay();
				CUMESS_Display_Message(0,STD_MESS_INCORRECT_PIN, DISPLAY_MERCHANT_CARDHOLDER);
				CUTERMsleep (1000);
			}

			// IHM time calculation
#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_ihm = get_tick_counter() - 100;
			}
#endif
			// Refashion of Pin Pad management file

		StopBeep();

			RepCVF = CUPIN_EnterPinOffLine(nb_try_pin_offline, TRUE, &buffer_pin, &dummy, &Bypass_Required);

		ReStartBeep();
 
			// Header management / displaying on X07
			CUTERMclearDisplay();

			// IHM time calculation
#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulFin_ihm = get_tick_counter();
				ulMMI_pin_off_line += (ulFin_ihm - ulDebut_ihm);
			}
#endif

			nb_try_pin_offline ++;
			break;

		case NO_INPUT :
			RepCVF = NO_INPUT;				// END_OF_CV
			break;

		case NO_REMAINING_PIN :
			RepCVF = NO_REMAINING_PIN;		// END_OF_CV
			break;

		case INPUT_PIN_OK :
			CUTERMclearDisplay();
			CUTERMclearPPdisplay();
			CUMESS_Display_Message(0,STD_MESS_PIN_OK, DISPLAY_MERCHANT_CARDHOLDER);
			// Header management / displaying on X07
			ttestall(0,100);

			RepCVF = 0;						// END_OF_CV
			break;

		default :
			RepCVF = 0;						// END_OF_CV
			break;
		}
	}

	// IHM time calculation
#ifdef _TOOLWARE_
	else
	{
		if (ucAdvancedMode == TRUE)
		{
			ulMMI_pin_off_line = 0;
			ulMMI_pin_on_line = 0;
		}
	}
#endif


	// Build an output TLV tree

	TlvTree_AddChild(*phOutTLVTree, TAG_AUTOMATE, (unsigned char *) &RepCVF, 1);

	if (Bypass_Required == ((CUSERV_TRUE[0] << 8) + CUSERV_TRUE[1]))
	{
		unsigned char BypassPIN;

		BypassPIN = 0x01;
		TlvTree_AddChild(*phOutTLVTree, TAG_BYPASS_PIN, (unsigned char *) &BypassPIN, 1);
	}

	TlvTree_AddChild(*phOutTLVTree, TAG_PIN_CODE, (unsigned char *) buffer_pin.d_entry, buffer_pin.d_len);
}

//===========================================================================
//! \brief This function manages the TERMINAL_RISK_MANAGEMENT Process_step
//! state.
//! \param[out] error_code : function result.
//! \param[out] phOutTLVTree : output TLV tree built :
//! - \ref TAG_PIN_CODE
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
static void EMVDC_TERMINAL_RISK_MANAGEMENT_Function_Tlvtree(unsigned short * error_code, TLV_TREE_NODE *phOutTLVTree)
{
	ENTRY_BUFFER buffer_pin;

	// Build an output TLV tree

	// Clear PIN CODE of the memory !
	buffer_pin.d_len = 12;
	memclr(buffer_pin.d_entry, 12);

	TlvTree_AddChild(*phOutTLVTree, TAG_PIN_CODE, (unsigned char *) buffer_pin.d_entry, buffer_pin.d_len);

	CUTERMclearPPdisplay();
	CUMESS_Display_Message(1,STD_MESS_PLEASE_WAIT, DISPLAY_MERCHANT_CARDHOLDER);

}

//===========================================================================
//! \brief This function manages the CARD_ACTION_ANALYSIS Process_step
//! state.
//! \param[out] error_code : function result.
//! \param[out] phOutTLVTree : output TLV tree built :
//! - optionnaly \ref TAG_TRANSACTION_FORCED_ACCEPTANCE
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
static void EMVDC_CARD_ACTION_ANALYSIS_Function_Tlvtree(unsigned short *error_code, TLV_TREE_NODE *phOutTLVTree)
{
	unsigned char is_forced_acceptance[2];
	unsigned char ucFA;

	switch (*error_code)
	{
	case TAG_CUST_TRANSACTION_ACCEPTED:
		status_tr = STATUS_TR_APPROVED;
		break;

	case TAG_CUST_SERVICE_NOT_ALLOWED:
		// Service not allowed in GENAC, shall terminate transaction
		CUMESS_Display_Message (0, STD_MESS_NOT_ACCEPTED, DISPLAY_MERCHANT_CARDHOLDER);
		CUTERMsleep (1000);
		status_tr = STATUS_TR_PROCESSING_ERROR;
		break;

		// AAR terminates transaction
	case TAG_CUST_NOT_ACCEPTED:
		status_tr = STATUS_TR_PROCESSING_ERROR;
		break;

	case TAG_CUST_TRANSACTION_DECLINED:
		// Propose Forced acceptance in this case
		// Display a message telling the transaction is declined
		CUMESS_Display_Message (0, STD_MESS_DECLINED, DISPLAY_MERCHANT_CARDHOLDER);
		CUTERMsleep (1000);

		Forced_Acceptance(EMVDC_CARD_ACTION_ANALYSIS, is_forced_acceptance);

		if (is_forced_acceptance[1] == 0x01)
		{
			status_tr = STATUS_TR_APPROVED;
		}
		else
		{
			status_tr = STATUS_TR_DECLINED;
		}

		// Build an output TLV tree
		ucFA = is_forced_acceptance[1];
		TlvTree_AddChild(*phOutTLVTree, TAG_TRANSACTION_FORCED_ACCEPTANCE, (unsigned char *) &ucFA, 1);
		break;

	default:
		break;
	}

}

//===========================================================================
//! \brief This function manages the ON_LINE_PROCESSING Process_step state.
//! \param[out] error_code : function result.
//! \param[in] ptr_usMerchantLang : language information used by the merchant.
//! \param[in] phInTLVTree : input TLV tree containing the following tags :
//! - \ref TAG_AUTHORISATION_RESPONSE_CODE
//! - \ref TAG_AUTHORISATION_RESULT
//! - \ref TAG_CUST_IS_COMMUNICATION_OK
//! - \ref TAG_SERVICE_STATUS_CODE
//! \param[out] phOutTLVTree : output TLV tree built :
//! - optionnaly \ref TAG_CUST_FORCED_ACCEPTANCE_REQUEST
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
static void EMVDC_ON_LINE_PROCESSING_Function_Tlvtree(unsigned short * error_code, unsigned short *ptr_usMerchantLang, TLV_TREE_NODE *phInTLVTree, TLV_TREE_NODE *phOutTLVTree)
{
	unsigned char  is_forced_acceptance[2];
	unsigned short found;
	char *         pc_l_DisplayTxt;
	DataElement    Data_Elt;
	TLV_TREE_NODE  hTree;


	// EMVDC_ON_LINE_PROCESSING

	//---------------------------------------------------------------
	// Check the result of the communication
	//---------------------------------------------------------------

	CommProblem = FALSE;

	// Read Communication Status
	found = CUSERV_Extract_Element_TLV_Tree(phInTLVTree, TAG_CUST_IS_COMMUNICATION_OK, &Data_Elt);

	if (found)
	{
		if (Data_Elt.ptValue[1] == 0x00)
		{
			CommProblem = TRUE;
			CUSERV_CommRetries++;
		}
		else if (Data_Elt.ptValue[1] == 0x02)
		{
			CommProblem = TRUE;

			// Correct bug when CUSERV_COMM_MAX_RETRIES is not 1
			CUSERV_CommRetries = CUSERV_CommRetries + CUSERV_COMM_MAX_RETRIES + 1;	// Not retry
		}
	}

	if (!CommProblem)
	{
		// Send a reversal message
		found = CUSERV_Extract_Element_TLV_Tree(phInTLVTree, TAG_AUTHORISATION_RESPONSE_CODE, &Data_Elt);

		// Check Authorisation Response Code
		if (found)
		{
			if ((Data_Elt.ptValue [0] < 0x30) ||	// '0'
				(Data_Elt.ptValue [0] > 0x39) ||	// '9'
				(Data_Elt.ptValue [1] < 0x30) ||	// '0'
				(Data_Elt.ptValue [1] > 0x39))		// '9'
			{
				// Y2, Z2 acceptance
				if ((memcmp (Data_Elt.ptValue, ARC_REFERRAL_APPROVED, 2) != 0) &&
					(memcmp (Data_Elt.ptValue, ARC_REFERRAL_DECLINED, 2) != 0))
				{
					CommProblem = TRUE;
					CUSERV_CommRetries++;
				}
			}

			else if ((Data_Elt.ptValue [0] == 0x30) &&
				(Data_Elt.ptValue [1] == 0x30))
			{
				if(Is_Offline_Only()==FCT_OK)
					TransacOk = FALSE;
				else
					TransacOk = TRUE;
			}
		}
		else
		{
			CommProblem = TRUE;
			CUSERV_CommRetries++;
		}
	}

	if (CommProblem)
	{
		if (CUSERV_CommRetries > CUSERV_COMM_MAX_RETRIES)
		{
			ucComm_Message_reason_code = TAG_COMM_TIME_OUT_WAITING_FOR_RESPONSE;

			// Reversal after 2nd generate AC
			// Reversal requested not for Offline Only terminals
			if(Is_Offline_Only()!=FCT_OK)
				reversal_requested = TRUE;

			TransacOk= TRUE;

			pc_l_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_COMM_PROBLEM, *ptr_usMerchantLang);
			CUTERMdisplayLine(0, pc_l_DisplayTxt, CENTER, (char *)"w");
			CUTERMsleep (1000);
#ifdef _TOOLWARE_
			ulMMI_force_OLP = 100; /* This value will be updated by Forced_Acceptance() if this function will be called */
#endif

			// Force only if TACs indicate Reject

			// Retreive Result Analisys tac default
			hTree = Engine_GetDataElement(TAG_RESULT_ANALISYS_TAC_DEFAULT);

			found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_RESULT_ANALISYS_TAC_DEFAULT, &Data_Elt);

			if (found)
			{
				if (Data_Elt.ptValue [0] == TAC_DEFAULT_REJECT)
				{

					Forced_Acceptance(EMVDC_ON_LINE_PROCESSING, is_forced_acceptance);

					// Build an output TLV tree

					TlvTree_AddChild(*phOutTLVTree, TAG_CUST_FORCED_ACCEPTANCE_REQUEST, (unsigned char *) is_forced_acceptance, 2);
				}
			}

			// release local TLV tree
			TlvTree_ReleaseEx(&hTree);
		}
		else
		{
			// Build an empty output TLV Tree

			*error_code = TAG_CUST_RETRY_COMMUNICATION;
		}
	}


	// Advice online implementation
	if ( Online_Advice_Conditions())
	{
		if (CommProblem == TRUE)
			if (CUSERV_CommRetries > CUSERV_COMM_MAX_RETRIES)
			{
				status_tr =STATUS_TR_PROCESSING_ERROR;
				*error_code = TAG_CUST_PROCESSING_ERROR;
			}
	}
}

//===========================================================================
//! \brief This function manages the EMVDC_COMPLETION Process_step state.
//! \param[out] error_code : function result.
//! \param[out] phOutTLVTree : output TLV tree built :
//! - optionnaly \ref TAG_CUST_FORCED_ACCEPTANCE_REQUEST
//! - \ref TAG_CUST_STATUS_CODE
//===========================================================================
static void EMVDC_COMPLETION_Function_Tlvtree(unsigned short * error_code, TLV_TREE_NODE *phOutTLVTree)
{
	DataElement Data_Elt;
	unsigned short  found;
	TLV_TREE_NODE  hTree;

	unsigned char is_forced_acceptance[2];


	if (*error_code == TAG_CUST_TRANSACTION_ACCEPTED)
	{
		status_tr = STATUS_TR_APPROVED;
	}
	else if (*error_code == TAG_CUST_SERVICE_NOT_ALLOWED)
	{
		// Service not allowed in GENAC shall terminate transaction
		CUMESS_Display_Message (0, STD_MESS_NOT_ACCEPTED, DISPLAY_MERCHANT_CARDHOLDER);
		CUTERMsleep (1000);

		status_tr = STATUS_TR_PROCESSING_ERROR;
	}

	// If crypto > requested display "declined"
	// AAR terminates transaction and higer level of CID on GENAC1 terminates transac
	// ( aar is tag_not_accepted the same as not expected cid )
	else if ((*error_code == TAG_CUST_TRANSACTION_DECLINED) || (*error_code == TAG_CUST_NOT_ACCEPTED))
	{
		unsigned char ucFA;

		status_tr = STATUS_TR_DECLINED;


		// if AAR stop
		hTree = Engine_GetDataElement(TAG_CRYPTOGRAM_INFORMATION_DATA);

		found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_CRYPTOGRAM_INFORMATION_DATA, &Data_Elt);

		if (found)
		{
			if ((*Data_Elt.ptValue == AAR ) &&(*error_code == TAG_CUST_NOT_ACCEPTED))
			{
				status_tr = STATUS_TR_PROCESSING_ERROR;
			}
		}

		if (status_tr != STATUS_TR_PROCESSING_ERROR)
		{
			// Display a message telling the transaction is declined
			CUTERMclearDisplay();
			CUTERMclearPPdisplay();
			CUMESS_Display_Message (0, STD_MESS_DECLINED, DISPLAY_MERCHANT_CARDHOLDER);
			// For TOOLWARE, time will be taken by Force_Aceptance()
			CUTERMsleep (1000);

			Forced_Acceptance(EMVDC_COMPLETION, is_forced_acceptance);

			CUTERMclearDisplay();
			CUTERMclearPPdisplay();
			CUMESS_Display_Message(1,STD_MESS_PLEASE_WAIT, DISPLAY_MERCHANT_CARDHOLDER);

			if (is_forced_acceptance[1] == 0x01)
			{
				status_tr = STATUS_TR_APPROVED;
			}
			else
			{
				status_tr = STATUS_TR_DECLINED;
			}


			// Build an output TLV tree
			ucFA = is_forced_acceptance[1];
			TlvTree_AddChild(*phOutTLVTree, TAG_TRANSACTION_FORCED_ACCEPTANCE, (unsigned char *) &ucFA, 1);
		}

		// release local TLV tree
		TlvTree_ReleaseEx(&hTree);

	}

	Bypass_Required = (CUSERV_FALSE[0] << 8) + CUSERV_FALSE[1];

	TransactionForcedOnline = (CUSERV_FALSE[0] << 8) + CUSERV_FALSE[1];

}

//===========================================================================
//! \brief This function manages the EMVDC_STOP Process_step state.
//! \param[out] error_code : function result.
//! \param[in] ptr_usMerchantLang : language information used by the merchant.
//===========================================================================
static void EMVDC_STOP_Function_Tlvtree(unsigned short *error_code, unsigned short *ptr_usMerchantLang)
{
	TLV_TREE_NODE hTree,hTreeSR,hTreeDis;

#ifdef _TOOLWARE_
	unsigned long ulDebut_online=0;
#endif

	hTree = TlvTree_New(0);
	hTreeSR = NULL;

	// Display TRY AGAIN for Aids reselection
	nb_time_select =0;

	if ((status_tr == STATUS_TR_APPROVED) ||
		(status_tr == STATUS_TR_REFUND_APPROVED))
	{
		if ( reversal_requested == TRUE )
		{
			Protocol_Type = Host_Comm_Protocol();
			if (Protocol_Type != COMM_PROTOCOL_TYPE_SPDH )
			{
				EMVCUST_Build_reversal_TLVTree_Iso8583(&hTree);
			}
			else
			{
				// EMVCUST_Build_reversal_TLVTree_Spdh(&hTree);
			}

#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_online = get_tick_counter();
			}
#endif

			hTreeSR = COMM_Send_And_Receive_Message_TlvTree(hTree);

#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				unsigned long ulFin_online;
				ulFin_online = get_tick_counter();
				ulHOST_comm += ulFin_online - ulDebut_online;
			}
#endif
		}

		CUTERMclearDisplay();
		CUTERMclearPPdisplay();
		CUMESS_Display_Message(0,STD_MESS_APPROVED, DISPLAY_MERCHANT_CARDHOLDER);
	}
	else if (status_tr == STATUS_TR_DECLINED)
	{
		if (TransacOk == TRUE)
		{
			ucComm_Message_reason_code = TAG_COMM_SUSPECTED_MALFUNCTION;

			// Mixed Communication with ISO8583 and SPDH
			Protocol_Type = Host_Comm_Protocol();
			if (Protocol_Type != COMM_PROTOCOL_TYPE_SPDH )
			{
				EMVCUST_Build_reversal_TLVTree_Iso8583(&hTree);
			}
			else
			{
				// EMVCUST_Build_reversal_TLVTree_Spdh(&hTree);
			}
#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_online = get_tick_counter();
			}
#endif
			// Real SPDH Interface

			hTreeSR = COMM_Send_And_Receive_Message_TlvTree(hTree);

#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				unsigned long ulFin_online;
				ulFin_online = get_tick_counter();
				ulHOST_comm += ulFin_online - ulDebut_online;
			}
#endif
		}
		else
		{
			// Advice online implementation
			if ( Online_Advice_Conditions())
			{
				Send_Advice_Message_TLVTree(error_code, ptr_usMerchantLang);
				if (CommProblem == TRUE)
				{
					status_tr =STATUS_TR_PROCESSING_ERROR;
				}
			}
		}


		CUTERMclearDisplay();
		CUTERMclearPPdisplay();
		CUMESS_Display_Message(0, STD_MESS_DECLINED, DISPLAY_MERCHANT_CARDHOLDER);
		CUTERMsleep (1500);
	}
	else if (status_tr == STATUS_TR_CANCELLED)
	{
		if (TransacOk == TRUE)
		{
			ucComm_Message_reason_code = TAG_COMM_CUSTOMER_CANCELLATION;

			// Mixed Communication with ISO8583 and SPDH
			Protocol_Type = Host_Comm_Protocol();
			if (Protocol_Type != COMM_PROTOCOL_TYPE_SPDH )
			{
				EMVCUST_Build_reversal_TLVTree_Iso8583(&hTree);
			}
			else
			{
				// EMVCUST_Build_reversal_TLVTree_Spdh(&hTree);
			}

#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_online = get_tick_counter();
			}
#endif
			// Real SPDH Interface

			hTreeSR = COMM_Send_And_Receive_Message_TlvTree(hTree);

#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				unsigned long ulFin_online;
				ulFin_online = get_tick_counter();
				ulHOST_comm += ulFin_online - ulDebut_online;
			}
#endif
		}
		else
		{
			// Advice online implementation
			if ( Online_Advice_Conditions())
			{
				Send_Advice_Message_TLVTree(error_code, ptr_usMerchantLang);
				if (CommProblem == TRUE)
				{
					status_tr =STATUS_TR_PROCESSING_ERROR;
				}
			}
		}


		CUTERMclearDisplay();
		CUTERMclearPPdisplay();
		DisplayCancel (*ptr_usMerchantLang);
		CUTERMsleep (1000);
	}
	else if (status_tr == STATUS_TR_CARD_ERROR)
	{
		if (TransacOk == TRUE)
		{
			ucComm_Message_reason_code = TAG_COMM_SUSPECTED_MALFUNCTION;

			// Mixed Communication with ISO8583 and SPDH
			Protocol_Type = Host_Comm_Protocol();
			if (Protocol_Type != COMM_PROTOCOL_TYPE_SPDH )
			{
				EMVCUST_Build_reversal_TLVTree_Iso8583(&hTree);
			}
			else
			{
				// EMVCUST_Build_reversal_TLVTree_Spdh(&hTree);
			}

#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_online = get_tick_counter();
			}
#endif
			// Real SPDH Interface

			hTreeSR = COMM_Send_And_Receive_Message_TlvTree(hTree);

#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				unsigned long ulFin_online;
				ulFin_online = get_tick_counter();
				ulHOST_comm += ulFin_online - ulDebut_online;
			}
#endif
		}
		else
		{
			// Advice online implementation
			if ( Online_Advice_Conditions())
			{
				Send_Advice_Message_TLVTree(error_code, ptr_usMerchantLang);
				if (CommProblem == TRUE)
				{
					status_tr =STATUS_TR_PROCESSING_ERROR;
				}
			}
		}

		CUTERMclearDisplay();
		CUTERMclearPPdisplay();
		CUMESS_Display_Message(0, STD_MESS_CARD_ERROR, DISPLAY_MERCHANT_CARDHOLDER);
		CUTERMsleep (1000);
	}
	else if (status_tr == STATUS_TR_PROCESSING_ERROR)
	{
		if (TransacOk == TRUE)
		{
			ucComm_Message_reason_code = TAG_COMM_SUSPECTED_MALFUNCTION;

			// Mixed Communication with ISO8583 and SPDH
			Protocol_Type = Host_Comm_Protocol();
			if (Protocol_Type != COMM_PROTOCOL_TYPE_SPDH )
			{
				EMVCUST_Build_reversal_TLVTree_Iso8583(&hTree);
			}
			else
			{
				// EMVCUST_Build_reversal_TLVTree_Spdh(&hTree);
			}

#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_online = get_tick_counter();
			}
#endif
			// Real SPDH Interface

			hTreeSR = COMM_Send_And_Receive_Message_TlvTree(hTree);

#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				unsigned long ulFin_online;
				ulFin_online = get_tick_counter();
				ulHOST_comm += ulFin_online - ulDebut_online;
			}
#endif
		}
		else
		{
			// Advice online implementation
			if ( Online_Advice_Conditions())
			{
				Send_Advice_Message_TLVTree(error_code, ptr_usMerchantLang);
				if (CommProblem == TRUE)
				{
					status_tr =STATUS_TR_PROCESSING_ERROR;
				}
			}
		}


		CUTERMclearDisplay();
		CUTERMclearPPdisplay();
		CUMESS_Display_Message(0, STD_MESS_PROCESSING_ERROR, DISPLAY_MERCHANT_CARDHOLDER);
		CUTERMsleep (1000);
	}

	// Release the local TlvTree
	TlvTree_ReleaseEx(&hTree);


	/*& BEGIN SMO/ETU/04/20449/LB                                                   */
	if (isConnected)
	{
		// Real SPDH Interface
		hTreeDis = COMM_Disconnect_TlvTree (NULL);

		isConnected = FALSE;
		TlvTree_ReleaseEx(&hTreeDis);
	}

	// Get transaction Log from ICC for PBOC
	if (isTrlog != TRUE)
	{
		//--------------------------------------------------------------
		// Batch Data Capture
		//--------------------------------------------------------------

		Add_Batch (status_tr);

		// Reset to Default case : debit transaction
		ulTransactionType = CUSERV_DEBIT_TRANSACTION;

		Bypass_Required = (CUSERV_FALSE[0] << 8) + CUSERV_FALSE[1];

		TransactionForcedOnline = (CUSERV_FALSE[0] << 8) + CUSERV_FALSE[1];

		// Error card during the transaction => Allow fall-back
		//!
		//! \todo FALL-BACK implementation :
		//! Check the local rules for fall-back, in the case an error
		//! is detected during the transaction.
		//! Adapt the algorithm hereafter to your local need.
		//!
		if ((*error_code == TAG_CUST_CARD_ERROR) ||
			(*error_code == TAG_CUST_ICC_DATA_FORMAT_ERROR) ||
			(*error_code == TAG_CUST_MISSING_MANDATORY_ICC_DATA) ||
			(*error_code == TAG_CUST_ICC_REDUNDANT_DATA) )
		{
			int i;
			NO_SEGMENT seg_number;
			seg_number = (NO_SEGMENT)num_seg();
			for (i = 0; i < seg_number; i++)
			{
				if (ApplicationGetCurrentAppliType() == I_EMVCUST_Type_Appli)
      				{
      				
#ifdef _USE_UCM_
      					if(!UCM_Present)
#endif
      						cu_fall_back(seg_number, NO_ENTRY, 0);
      				}
				
   			

			}
		}
	}


	// add calls to EMV Tool functionnalities
#ifdef _USE_UCM_
	// Reimplementation of Dumptags and traces
	if(UCM_Present)
	{
		SetOutputCom0();
		DumpTags();
	}
#endif
	TlvTree_ReleaseEx(&hTree);
	TlvTree_ReleaseEx(&hTreeSR);

}


//===========================================================================
//! \brief This function manages the EMVDC_READ_TRLOG_DATA Process_step state.
//! \param[out] error_code : function result.
//! \param[in] phInTLVTree : input TLV tree containing the transaction log :
//! - \ref TAG_TRLOG_RECORD.
//===========================================================================
static void EMVDC_READ_TRLOG_DATA_Function_Tlvtree(unsigned short *error_code, TLV_TREE_NODE *phInTLVTree)
{
	DataElement    Data_Elt;
	TLV_TREE_NODE  hTree;

	isTrlog = TRUE;
	if (*error_code == TAG_CUST_PROCESS_COMPLETED)
	{
		status_tr = STATUS_TR_APPROVED;

		hTree = TlvTree_GetFirstChild(*phInTLVTree);

		while  (hTree != NULL)
		{
			// Get the tag
			Data_Elt.tag = TlvTree_GetTag(hTree);

			// Get the length
			Data_Elt.length = TlvTree_GetLength(hTree);

			// Get the value
			Data_Elt.ptValue = TlvTree_GetData(hTree);

			if ( Data_Elt.tag == TAG_TRLOG_RECORD )
			{
				/* WRITE here the way you want to print the Transaction Log */
				/* hee is a sample to be madified */
				unsigned char debug[100];

				sprintf ((char *)debug, "LOG  %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
					Data_Elt.ptValue[0],Data_Elt.ptValue[1],Data_Elt.ptValue[2],Data_Elt.ptValue[3],Data_Elt.ptValue[4],
					Data_Elt.ptValue[5],Data_Elt.ptValue[6],Data_Elt.ptValue[7],Data_Elt.ptValue[8],Data_Elt.ptValue[9],
					Data_Elt.ptValue[10],Data_Elt.ptValue[11],Data_Elt.ptValue[12],Data_Elt.ptValue[13],Data_Elt.ptValue[14]);
				upload_diagnostic_txt ((unsigned char*)debug);
			}

			// Get the next node
			hTree = TlvTree_GetNext(hTree);

		}

	}
	else
	{
		status_tr = STATUS_TR_DECLINED;
	}
}

//===========================================================================
void EMVCUST_Voice_Referral_TlvTree (TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned short lg_code, found;
	unsigned char text[40];
	unsigned char pan_ascii[38];
	DataElement elt;
	T_CUTERMkey key;
	T_Bool cr;
	unsigned short error_code;
	char * pc_l_DisplayTxt;
	unsigned char StatusCode[2];

	unsigned short mask;
	byte b_l_TimeOut;
	TLV_TREE_NODE hTree;

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	error_code = TAG_CUST_REFERRAL_DECLINED;

	// The referral request treatements have to be done only if parameter allows or if it is not a card referral.
	// else terminal terminates transaction
	found = PAR_ReadParameter(TAG_CUST_IS_ISSUER_REFERRAL, (DataElementExt *)&elt);

	if (elt.ptValue[0] == 1)
	{
		lg_code = PSQ_Give_Language();
		if (lg_code > C_NBLANGMERCH)
		{
			lg_code = 0;
		}

		// Display a message, asking the merchant to call his bank
		CUMESS_Display_Message (0, STD_MESS_CALL_YOUR_BANK, DISPLAY_MERCHANT);

		// Get data from EMVDC

		// Retrieve PAN
		hTree = Engine_GetDataElement(TAG_APPLI_PRIM_ACCOUNT_NB);

		found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APPLI_PRIM_ACCOUNT_NB, &elt);

		if (found)
		{
			// Display informations for the referral

			memset (pan_ascii, 0, sizeof(pan_ascii));
			Hexascii((unsigned char *) pan_ascii,
					(unsigned char *) elt.ptValue,
					(int) 2 * elt.length);

			CUTERMsleep (5000);
			// sprintf ((char *) text, "PAN : %10s\n", pan_ascii);
			// CUTERMdisplayLine (0, (char *)text, LEFT, (char *)"w");
			// sprintf ((char *) text, "%16s\n", (char *) &(pan_ascii[10]));
			// CUTERMdisplayLine (1, (char *)text, LEFT, (char *)"a");
			sprintf ((char *) text, "PAN : %.10s\n%16s\n", pan_ascii, &(pan_ascii[10]));
			CUTERMdisplayLine (0, (char *)text, LEFT, (char *)"w");

			// Wait for a key entry, before displaying the following message
			cr = CUTERMgetKey(120000, &key);		// 2 minutes
		}

		// release local TLV tree
		TlvTree_ReleaseEx(&hTree);

		// Ask for referral result
         pc_l_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_APPROVED, lg_code);
         CUTERMdisplayLine(0, pc_l_DisplayTxt, CENTER, (char *)"w");

         key = CU_VALID;		// init =/= CANCEL
         b_l_TimeOut = 120;	// 120s

         mask = MASK_ANNULATION | MASK_CORRECTION | MASK_VALIDATION | MASK_SKVAL | MASK_SKCORR | MASK_SK1 | MASK_SK4;

         if (CUTERM_Wait_function_key(b_l_TimeOut, mask, &key) == TRUE)		// 10s with mask
         {

            if ((key == T_VAL) ||
            	(key == T_SK1))
            {
               	// Approved
               	error_code = 0;
            }
         }
         // else time-out
         // error_code = TAG_CUST_REFERRAL_DECLINED; same as default value
		

	}
	else
	{
		error_code = TAG_CUST_REFERRAL_NOT_ACCEPTED;
		status_tr = STATUS_TR_DECLINED;
	}

	// Build an output TLV tree

	// Add tag status code
	ShortToChar(error_code, StatusCode);
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &StatusCode, 2);

}

//===========================================================================
void EMVCUST_Display_Message_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned short found;
	unsigned short error_code;
	unsigned short lg_code;
	unsigned char  mess_code;
	unsigned char  ucDisplayDestination;
	DataElement    Data_Elt;
	DataElementExt ext_elt;

	ucDisplayDestination = DISPLAY_MERCHANT;
	mess_code = 0;

	// Extract the message destination from the input TLV tree
	found = CUSERV_Extract_Element_TLV_Tree(phInputTLVTree, TAG_EG_DISPLAY_DESTINATION, &Data_Elt);

	if (found)
	{
		ucDisplayDestination = Data_Elt.ptValue [0];
	}

	// Extract the number of the message to display from the input TLV tree
	found = CUSERV_Extract_Element_TLV_Tree(phInputTLVTree, TAG_EG_MESSAGE_CODE_NUM, &Data_Elt);

	if (found)
	{
		mess_code = Data_Elt.ptValue[0];
	}


	// Extract the cardholder language from the input TLV tree
	found = CUSERV_Extract_Element_TLV_Tree(phInputTLVTree, TAG_EG_CARDHOLDER_LANGUAGE, &(ext_elt.elt));

	if (found)
	{
		// Store data into pTreeAppli TLV tree
		PAR_SetParameter(TAG_EG_CARDHOLDER_LANGUAGE, ext_elt);
	}

	CUDB_Get_cardholder_language (&lg_code);


	if ((ucDisplayDestination == DISPLAY_CARDHOLDER) ||
		(ucDisplayDestination == DISPLAY_MERCHANT_CARDHOLDER))
	{
		CUTERMclearPPdisplay();
	}

	// Display message
	CUMESS_Display_Message (1, mess_code, ucDisplayDestination);

	error_code = 0;


	// Build output TLV tree

	// Add tag status code
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &error_code, 2);

}

//===========================================================================
void EMVCUST_Get_Last_Transaction_TlvTree(TLV_TREE_NODE *phInputTLVTree, TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned short found;
	unsigned short error_code;
	DataElement elt, Data_Elt;
	unsigned char TabAmount [4];
	unsigned long Tr_Amount;
	unsigned char PAN_Number[10];
	TLV_TREE_NODE hTransactionTree;
	unsigned char StatusCode[2];

	// Extract the PAN from the input TLV tree
	found = CUSERV_Extract_Element_TLV_Tree(phInputTLVTree, TAG_APPLI_PRIM_ACCOUNT_NB, &Data_Elt);

	if (found)
	{
		// Copy PAN Number
		memset(PAN_Number, 0, sizeof(PAN_Number));
		memcpy(PAN_Number, Data_Elt.ptValue, Data_Elt.length);

		// Search the last record with this PAN in the batch file
		found = CUBATCHReadLastPANRecord (PAN_Number, &hTransactionTree);

		if (found)
		{
			//-------------------------------------------------------------------
			// Copy the record fields from transaction TLV tree to the output TLV tree
			//-------------------------------------------------------------------

			found = CUSERV_Extract_Element_TLV_Tree(&hTransactionTree, TAG_AMOUNT_AUTH_BIN, &elt);
			if (found)
			{
				TlvTree_AddChild(*phOutputTLVTree, elt.tag, elt.ptValue, elt.length);
			}

			found = CUSERV_Extract_Element_TLV_Tree(&hTransactionTree, TAG_AMOUNT_OTHER_BIN, &elt);
			if (found)
			{
				TlvTree_AddChild(*phOutputTLVTree, elt.tag, elt.ptValue, elt.length);
			}

			/* elt.tag     = TAG_LAST_TR_AMOUNT_BIN;
			elt.length  = 4;
			LongToChar (batch_record.exist_data.TransAmount, TabAmount);
			elt.ptValue = TabAmount;*/
			found = CUSERV_Extract_Element_TLV_Tree(&hTransactionTree, TAG_AMOUNT_AUTH_BIN, &elt);
			if (found)
			{
				Tr_Amount = CharToLong (elt.ptValue);
				found = CUSERV_Extract_Element_TLV_Tree(&hTransactionTree, TAG_AMOUNT_OTHER_BIN, &elt);
				if (found)
				{
					Tr_Amount = Tr_Amount + CharToLong (elt.ptValue);
					LongToChar (Tr_Amount, TabAmount);
					TlvTree_AddChild(*phOutputTLVTree, TAG_LAST_TR_AMOUNT_BIN, TabAmount, 4);
				}
			}

			found = CUSERV_Extract_Element_TLV_Tree(&hTransactionTree, TAG_TRANSACTION_CURRENCY_CODE, &elt);
			if (found)
			{
				elt.tag = TAG_LAST_TR_CURRENCY_CODE;
				TlvTree_AddChild(*phOutputTLVTree, elt.tag, elt.ptValue, elt.length);
			}

			found = CUSERV_Extract_Element_TLV_Tree(&hTransactionTree, TAG_TRANSACTION_DATE, &elt);
			if (found)
			{
				TlvTree_AddChild(*phOutputTLVTree, elt.tag, elt.ptValue, elt.length);
			}

			found = CUSERV_Extract_Element_TLV_Tree(&hTransactionTree, TAG_TRANSACTION_TIME, &elt);
			if (found)
			{
				TlvTree_AddChild(*phOutputTLVTree, elt.tag, elt.ptValue, elt.length);
			}

			found = CUSERV_Extract_Element_TLV_Tree(&hTransactionTree, TAG_TRANSACTION_TYPE, &elt);
			if (found)
			{
				TlvTree_AddChild(*phOutputTLVTree, elt.tag, elt.ptValue, elt.length);
			}

			error_code = 0;
		}
		else
		{
			// PAN not found in the data base
			error_code = TAG_CUST_PAN_NOT_FOUND;

			// Build an empty output TLV tree
		}

		// release local TLV tree
		TlvTree_ReleaseEx(&hTransactionTree);
	}
	else
	{
		error_code = TAG_CUST_WRONG_TLV_TREE_INPUT_PARAMETER;

		// Build an empty output TLV tree
	}

	// Add tag status code
	ShortToChar(error_code, StatusCode);
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &StatusCode, 2);
}

//===========================================================================
void EMVCUST_Authorization_TlvTree (TLV_TREE_NODE *phOutputTLVTree)
{
#ifdef _TOOLWARE_
	unsigned long    ulDebut_online=0;
	unsigned long    ulFin_online=0;
#endif
	int cr, merchLang;
	unsigned short code;
	unsigned char code_result[2];
	char *pc_l1_DisplayTxt;
	char *pc_l2_DisplayTxt;
	char *pc_l_DisplayTxt;
	int	Comm_Protocol;
	unsigned char msg[100];
	TLV_TREE_NODE phOutputTLVTreeBuild;


	if(Is_Offline_Only()==FCT_OK)
	{
		// Build an output TLV tree

		code = 0;
		TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, (unsigned char *) &code, 2);

		code = 0;
		TlvTree_AddChild(*phOutputTLVTree, TAG_COMM_STATUS_CODE, (unsigned char *) &code, 2);

		code_result[0] = 1;
		TlvTree_AddChild(*phOutputTLVTree, TAG_AUTHORISATION_RESULT, (unsigned char *) &code_result, 1);

	}
	else
	{

		merchLang = PSQ_Give_Language();
		if (merchLang > C_NBLANGMERCH)
		{
			merchLang = 0;
		}

		// Check if the terminal is on its base
		cr = powered();

		// IHM time calculation
#ifdef _TOOLWARE_
		if (ucAdvancedMode == TRUE)
		{
			ulDebut_online = get_tick_counter();
		}
#endif

		// It is not useful to put the terminal on its base if the yes protocol is used.
		Comm_Protocol = Host_Comm_Protocol();

		// Put on base only X930
		if ((cr !=1)&&(IsPortable()==1) && (Comm_Protocol != COMM_PROTOCOL_TYPE_YES ))
		{
			pc_l_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_REPLACE_BASE, merchLang);
			CUTERMdisplayLine(0, pc_l_DisplayTxt, CENTER, (char *)"w");
			do
			{
				cr = powered();
			} while (cr != 1);

			CUMESS_Display_Message (0, STD_MESS_PLEASE_WAIT, DISPLAY_MERCHANT);
		}

		// IHM time calculation
#ifdef _TOOLWARE_
		if (ucAdvancedMode == TRUE)
		{
			ulFin_online = get_tick_counter();
			ulHOST_comm = ulHOST_comm + (ulFin_online - ulDebut_online);
		}
#endif

		// Build an output TLV tree

		// Connect with the acquirer host
		if (!isConnected)
		{
			isConnected = Host_Config_Connect();
		}

		if (isConnected)
		{
			// Prepare the input TLV tree for authorization request
			if (Comm_Protocol != COMM_PROTOCOL_TYPE_SPDH )
			{
				EMVCUST_BuildISO8583_autho_TLVTree (&phOutputTLVTreeBuild);
			}
			else
			{
				// EMVCUST_Build_autho_TLVTree_Spdh (phOutputTLVTree);
			}
			// Ask for an authorisation

			// Server time calculation, for online checking.
#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_online = get_tick_counter();
			}
#endif

			// Display 2 lines on UCM

			pc_l1_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_AUTHOR_MESS_1, merchLang);
			pc_l2_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_AUTHOR_MESS_2, merchLang);

#ifdef _USE_UCM_
			if(UCM_Present)
			{
				iLIBUCM_Display_Option( UCMC_DISPLAY, pc_l1_DisplayTxt, UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_APPEND, 0 ) ;
				iLIBUCM_Display_Option( UCMC_DISPLAY, "\n", UCMDISPLAY_APPEND , 0 ) ;
				iLIBUCM_Display_Option( UCMC_DISPLAY, pc_l2_DisplayTxt, UCMDISPLAY_APPEND|UCMDISPLAY_CLOSE_AT_END , 0 ) ;
			}
			else
#endif
			{
				memset(msg, 0, sizeof(msg));
				sprintf((char*)msg, " %s\n  %s", pc_l1_DisplayTxt, pc_l2_DisplayTxt);
				CUTERMdisplayLine(0, (char*)msg , CENTER, (char *)"w");
			}

			// Real SPDH Interface

				TlvTree_ReleaseEx(&*phOutputTLVTree);
				*phOutputTLVTree = COMM_Send_And_Receive_Message_TlvTree(phOutputTLVTreeBuild);

			// Server time calculation, for online checking.
#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulFin_online = get_tick_counter();
				ulHOST_comm = ulHOST_comm + (ulFin_online - ulDebut_online);
			}
#endif
		}
					// Release the local TlvTree
			TlvTree_ReleaseEx(&phOutputTLVTreeBuild);
	}
}

//===========================================================================
void EMVCUST_Choose_Language_Menu_TlvTree (TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned short error_code;
	unsigned char  cr;
	unsigned char  ucLangCode [3];
	int merchLang;
	int foundM, foundS;
	int i, j, index, iKey;
	int iIsSupported;
	DataElement eltM, eltS;
	ENTRY_BUFFER buffer;
	StructListe   Menu;
#ifdef _USE_UCM_
	unsigned char nonfin;
	char ctMessage[ 200 ];
#endif

#ifdef _TOOLWARE_
	unsigned long ulFin_ihm   = 0;
	unsigned long ulDebut_ihm = 0;
#endif

	cr = (unsigned char)-1;
	index = 0;

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	// Retreive Terminal merchant language
	merchLang = PSQ_Give_Language();

	iIsSupported = FALSE;


	// Get data from TLV tree
	foundM = PAR_ReadParameter(TAG_CUST_IS_MULTILANG_SUPPORTED, (DataElementExt *)&eltM);
	if (foundM)
	{
		TlvTree_AddChild(*phOutputTLVTree, eltM.tag, eltM.ptValue, eltM.length);
		iIsSupported = eltM.ptValue [0];
	}

	// Get data from TLV tree
	foundS = PAR_ReadParameter(TAG_CUST_SUPPORTED_LANGUAGE_LIST, (DataElementExt *)&eltS);
	if (foundS)
		TlvTree_AddChild(*phOutputTLVTree, eltS.tag, eltS.ptValue, eltS.length);

	// Search the database number associated with this AID
	if (foundM && foundS && iIsSupported)
	{
		// Remove state header if needed

		// InitDefaut(_ON_,1);
		InitStructList(&Menu, _ON_, 1);

		InitMSGinfos((MSGinfos *)&(Menu.Fenetre.titre));
        Menu.Fenetre.titre = (unsigned char *) CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_SELECT_LANG, merchLang);

		// Optional icon managed

#ifdef _TOOLWARE_
		if (ucAdvancedMode == TRUE)
		{
			ulDebut_ihm = get_tick_counter();
		}
#endif

		for (i=0 ; (i * 2) < (int) eltS.length ; i++ )
		{
			// Extract ISO 639-1 code
			ucLangCode [0] = eltS.ptValue [2 * i];
			ucLangCode [1] = eltS.ptValue [2 * i + 1];
			ucLangCode [2] = 0;

			Menu.tab[i] = (unsigned char*)"UNKNOWN";

			// Extract the associated name
			for (j = 0; j < C_NBLANGHOLDER; j++)
			{
				if ((ucLangCode [0] == lang_table [j].iso639_code [0]) &&
					(ucLangCode [1] == lang_table [j].iso639_code [1]))
				{
					InitMSGinfos((MSGinfos *)&(Menu.tab[i]));
                    Menu.tab[i] = (unsigned char *) lang_table [j].lang_name;


					// Optional icon
				}
			}
		}
		// Display the language selection menu
		InitMSGinfos((MSGinfos *)&(Menu.tab[i]));
        Menu.tab[i] = NULL;

		// MenuWgui.Icon[i].name_icon = NULL;

#ifdef _USE_UCM_
		if(UCM_Present)
		{
			unsigned short lg_code;
			char * ptrMsg;

			index = 0;
			nonfin = 0;
			lg_code = PSQ_Give_Language();
			ptrMsg = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_YESV_NOA, lg_code);

			do
			{
				sprintf(ctMessage, "%.16s\n%s",Menu.tab[index], ptrMsg);

				iLIBUCM_Display_Message( UCMC_DISPLAY, ctMessage,0) ;

				iLIBUCM_Pinpad_Ttestall( UCMC_PPAD, 300 );

            iKey = iLIBUCM_Pinpad_GetChar( UCMC_PPAD );
            
				/* Key simulation for IUC180B */
				if( giKeyboardType == PARAM_TYPE_IUC180B )
				{
				   switch( iKey )
				   {
				      case T_SKHAUT:
				         iKey = T_ANN;
				      break;

				      case T_SKBAS:
				         iKey = T_VAL ;
				      break;
				   }
				}

				switch( iKey  )
				{
				case T_VAL:
					nonfin = 1;
					cr = CR_ENTRY_OK;
					break;

				case T_CORR:
					index--;
					if(index==0)
						index = C_NBLANGHOLDER-1;
					break;

				case T_ANN:
					index++;
					if(index==C_NBLANGHOLDER)
						index = 0;
					break;

				default:
					break;
				}
			}
			while(nonfin==0);
		}
		else
#endif
		{
			if ((TransactionLoopMode == TRUE)&&(loop_amount != 0))
			{
				cr = CR_ENTRY_OK;
				buffer.d_entry[0] = 00;
			}
			else
			{
	            G_List_Entry (&Menu);
	            ttestall (ENTRY, 0);
	            cr = Get_Entry (&buffer);
			}
		}

		switch(cr)
		{
		case CR_ENTRY_OK :
			// Extract the ISO code associated with the name
			for (j = 0; j < C_NBLANGHOLDER; j++)
			{
#ifdef _USE_UCM_
				if(UCM_Present)
					buffer.d_entry[0] = index;
#endif
				if (strcmp ((char*)lang_table [j].lang_name, (char*)Menu.tab[buffer.d_entry[0]]) == 0)
				{
					DataElementExt data;
					data.elt.length = 2;
					data.elt.ptValue = (unsigned char *) lang_table [j].iso639_code;
					data.elt.tag = TAG_EG_CARDHOLDER_LANGUAGE;
					PAR_SetParameter(TAG_EG_CARDHOLDER_LANGUAGE, data);
					TlvTree_AddChild(*phOutputTLVTree, data.elt.tag, data.elt.ptValue, data.elt.length);
				}
			}
			break;
		}

#ifdef _TOOLWARE_
		if (ucAdvancedMode == TRUE)
		{
			ulFin_ihm = get_tick_counter();
			ulMMI_langue = ulFin_ihm - ulDebut_ihm;
		}
#endif


	}

	error_code = 0;

	// Add tag status code
	TlvTree_AddChild(*phOutputTLVTree, TAG_CUST_STATUS_CODE, &error_code, 2);
}

//===========================================================================
void EMVCUST_Choose_Account_Type_Menu_TlvTree (TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned char   cr,account_type;
	unsigned short  lg_code;
	int             index, iKey;
	ENTRY_BUFFER   buffer;
	StructListe	Menu;


#ifdef _USE_UCM_
	unsigned char   nonfin;
	char            ctMessage[ 200 ];
#endif

#ifdef _TOOLWARE_
	unsigned long ulDebut_ihm = 0;
#endif

	cr = (unsigned char)-1;
	index = 0;

	trace(0,strlen("EMVCUST_Choose_Account_Type_Menu"), "EMVCUST_Choose_Account_Type_Menu");

	// InitDefaut(_ON_,1);
	InitStructList(&Menu, _ON_, 1);

	// Init table from const
	// lg_code = PSQ_Give_Language();
	CUDB_Get_cardholder_language(&lg_code);
	InitMSGinfos((MSGinfos *)&(Menu.Fenetre.titre));
	Menu.Fenetre.titre = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_ACCOUNT_TYPE, lg_code);

	// Optional icon managed

	Menu.tab[0] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_AT_SAVING ,lg_code);
	Menu.tab[1] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_AT_DEBIT ,lg_code);
	Menu.tab[2] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_AT_CREDIT ,lg_code);
	Menu.tab[3] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_AT_default ,lg_code);
	Menu.tab[4] = NULL;


		// Optional icon

#ifdef _TOOLWARE_
	if (ucAdvancedMode == TRUE)
	{
		ulDebut_ihm = get_tick_counter();
	}
#endif

#ifdef _USE_UCM_
	if(UCM_Present)
	{
		char * ptrMsg;

		index = 0;
		nonfin = 0;
		ptrMsg = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_YESV_NOA, lg_code);

		do
		{
			sprintf(ctMessage, "%.16s\n%s",Menu.tab[index], ptrMsg);

			iLIBUCM_Display_Message( UCMC_DISPLAY, ctMessage,0) ;

			iLIBUCM_Pinpad_Ttestall( UCMC_PPAD, 300 );

         iKey = iLIBUCM_Pinpad_GetChar( UCMC_PPAD );
			/* Key simulation for IUC180B */
			if( giKeyboardType == PARAM_TYPE_IUC180B )
			{
			   switch( iKey )
			   {
			      case T_SKHAUT:
			         iKey = T_ANN;
			      break;

			      case T_SKBAS:
			         iKey = T_VAL ;
			      break;
			   }
			}

			switch( iKey )
			{
			case T_VAL:
				nonfin = 1;
				cr = CR_ENTRY_OK;
				break;

			case T_CORR:
				index--;
				if(index==0)
					index = C_NBLANGHOLDER-1;
				break;

			case T_ANN:
				index++;
				if(index==C_NBLANGHOLDER)
					index = 0;
				break;

			default:
				break;
			}

		}
		while(nonfin==0);

	}
	else
#endif
	{
		if ((TransactionLoopMode == TRUE)&&(loop_amount != 0))
		{
			cr = CR_ENTRY_OK;
			buffer.d_entry[0] = 00;
		}
		else
		{
			G_List_Entry(&Menu);
			ttestall(ENTRY,0);
			cr=Get_Entry(&buffer);
		}
	}

#ifdef _TOOLWARE_
	if (ucAdvancedMode == TRUE)
	{
		unsigned long ulFin_ihm   = 0;
		ulFin_ihm = get_tick_counter();
		ulMMI_account_type = ulFin_ihm - ulDebut_ihm;
	}
#endif

	account_type = ACCOUNT_TYPE_DEFAULT;
	if (cr == CR_ENTRY_OK )
	{

#ifdef _USE_UCM_
		if(UCM_Present)
			buffer.d_entry[0] = index;
#endif

		switch (buffer.d_entry[0])
		{
		case 0x00:
			account_type = ACCOUNT_TYPE_SAVINGS;
			break;
		case 0x01:
			account_type = ACCOUNT_TYPE_CHEQUE_DEBIT;
			break;
		case 0x02:
			account_type = ACCOUNT_TYPE_CREDIT;
			break;
		default:
			break;
		}
	}

	CUMESS_Display_Message (0, STD_MESS_PLEASE_WAIT, DISPLAY_MERCHANT_CARDHOLDER);

	// Build an output TLV tree

	TlvTree_AddChild(*phOutputTLVTree, TAG_ACCOUNT_TYPE, (unsigned char *) &account_type, 1);

}

//===========================================================================
unsigned short CUSERV_Extract_Element_TLV_Tree(TLV_TREE_NODE *phInTLVTree, unsigned long Tag, DataElement *ptElt)
{
	unsigned short found;
	TLV_TREE_NODE hFoundNode=NULL;

	found = FALSE;

	if(*phInTLVTree != NULL)
	{
		hFoundNode = TlvTree_Find(*phInTLVTree, Tag, 0);
		if(hFoundNode != NULL)
		{
			// Node found, get the tag
			ptElt->tag = TlvTree_GetTag(hFoundNode);

			// Get the length
			ptElt->length = TlvTree_GetLength(hFoundNode);

			// Get the value
			ptElt->ptValue = TlvTree_GetData(hFoundNode);

			found = TRUE;
		}
	}
	return (found);
}


/* ======================================================================== */
/* Local function declaration                                               */
/* ======================================================================== */

//===========================================================================
//! \brief This function creates a new batch record.
//! \param[in] status_tr : status of the transaction :
//! - \ref STATUS_TR_APPROVED
//! - \ref STATUS_TR_DECLINED
//! - \ref STATUS_TR_CANCELLED
//! - \ref STATUS_TR_CARD_ERROR
//! - \ref STATUS_TR_PROCESSING_ERROR
//! - \ref STATUS_TR_REFUND_APPROVED
//===========================================================================
static void Add_Batch (unsigned char status_tr)
{
	unsigned short found;
	int iIsAdviceSupported;
	DataElement elt;
	TLV_TREE_NODE hTree,hTreeGD;

	hTreeGD=NULL;
	hTree=NULL;
	if ((status_tr == STATUS_TR_APPROVED) || (status_tr == STATUS_TR_REFUND_APPROVED))
	{
		CUBATCH_Create_Financial_Record (&hTree);

		//----------------------------------------------------------------------
		// Ticket
		//----------------------------------------------------------------------

		// Printing time of the transaction ticket.
#ifdef _TOOLWARE_
		if (ucAdvancedMode == TRUE)
		{
			ulEnd_computation = get_tick_counter();
		}
#endif

		CURECEIPT_Print_Ticket_POS_Demo(hTree, status_tr);

		// Release the local TlvTree
		TlvTree_ReleaseEx(&hTree);

#ifdef _TOOLWARE_
		if (ucAdvancedMode == TRUE)
		{
			ulEnd_transaction = get_tick_counter();
			ulMMI_ticket = ulEnd_transaction - ulEnd_computation;

			CURECEIPT_Print_Ticket_Advance_Demo();
		}
#endif
	}
	else
	{
		// Get data from TLV tree
		// The transaction has been declined. Create an advice record if needed
		found = PAR_ReadParameter(TAG_CUST_IS_ONLINE_ADVICE, (DataElementExt *)&elt);

		iIsAdviceSupported = FALSE;
		if (found)
		{
			iIsAdviceSupported = (elt.ptValue[0] == 0x01);
		}

		if (iIsAdviceSupported)
		{
			// Get TAG_IS_ADVICE_REQUIRED from EMVDC
			hTreeGD = Engine_GetDataElement(TAG_IS_ADVICE_REQUIRED);

			found = CUSERV_Extract_Element_TLV_Tree(&hTreeGD, TAG_IS_ADVICE_REQUIRED, &elt);

			if (found)
			{
				if ( elt.ptValue[0] == 0x01 )
				{
					CUBATCH_Create_Advice_Record ();
				}
			}

			// Release the local TlvTree
			TlvTree_ReleaseEx(&hTreeGD);

		}
	}
	// Release the local TlvTree
	TlvTree_ReleaseEx(&hTree);

}

//===========================================================================
//! \brief This function asks to the cardholder if he wants to force the
//! acceptance of the transaction.
//! \param[in] function : transaction step.
//! \param[out] is_forced_acceptance : boolean indicating if the cardholder
//! wants to force the acceptance of the transaction.
//===========================================================================
static void Forced_Acceptance(int function, unsigned char *is_forced_acceptance)
{
	T_CUTERMkey key;
	unsigned short lg_code;
	unsigned short mask;
	byte b_l_TimeOut = 60; /* 60s */
	char * pc_l1_DisplayTxt;
	char * pc_l2_DisplayTxt;
	unsigned short found;
	DataElement elt;
#ifdef _USE_UCM_
	T_Bool cr = FALSE;
#endif
	unsigned char msg[100];
	ENTRY_BUFFER entry_buffer;
	unsigned char cr_entry = CR_ENTRY_NOK;

#ifdef _TOOLWARE_
	unsigned long ulDebut_ihm = 0;
#endif

	// Management of forced acceptance parameter
	memclr(is_forced_acceptance, 2);

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	found = PAR_ReadParameter(TAG_CUST_IS_FORCED_ACCEPTANCE, (DataElementExt *)&elt);

	if (found)
		if (elt.ptValue[0] == 1)
		{
			lg_code = PSQ_Give_Language();
			if (lg_code > C_NBLANGMERCH)
			{
				lg_code = 0;
			}

			// Display 2 lines on UCM
			pc_l1_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_FORCED, lg_code);
			pc_l2_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_YES_NO, lg_code);

		#ifdef _USE_UCM_
			if(UCM_Present)
			{
             if( (giDisplayType  == PARAM_TYPE_IUP250 ) || (giDisplayType  == PARAM_TYPE_IUC180B ) )
             {
               pc_l2_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_YES_NO, lg_code);
             }
                     
				iLIBUCM_Display_Option( UCMC_DISPLAY, pc_l1_DisplayTxt, UCMDISPLAY_CLEAR | UCMDISPLAY_OPEN_IF_NOT | UCMDISPLAY_APPEND, 0 ) ;
				iLIBUCM_Display_Option( UCMC_DISPLAY, "\n", UCMDISPLAY_APPEND , 0 ) ;
				iLIBUCM_Display_Option( UCMC_DISPLAY, pc_l2_DisplayTxt, UCMDISPLAY_APPEND|UCMDISPLAY_CLOSE_AT_END , 0 ) ;
			}
			else
		#endif
			{
				memset(msg, 0, sizeof(msg));
				sprintf((char*)msg, "%s\n%s", pc_l1_DisplayTxt, pc_l2_DisplayTxt);
				CUTERMdisplayLine(0, (char*)msg , CENTER, (char *)"w");
	
			}

		#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_ihm = get_tick_counter();
			}
		#endif

		#ifdef _USE_UCM_
			if(UCM_Present)
			{
				cr = CUTERMgetKey(6000, &key);		// 1 minute

				if ( cr == TRUE)
				{
					if (key == T_VAL)
						is_forced_acceptance[1] = 0x01;

					if (key == T_F2)
						is_forced_acceptance[1] = 0x01;
				}
			}
			else
		#endif
			{
				if ((TransactionLoopMode == TRUE)&&(loop_amount != 0))
				{
					key = T_ANN;
					cr_entry = CR_ENTRY_OK;
					entry_buffer.d_entry[0] = 1 ;
				}
				else
				{
				mask = MASK_ANNULATION | MASK_SKCORR | MASK_SK2 | MASK_VALIDATION | MASK_SKVAL |MASK_SK3;
				CUTERM_Wait_function_key(b_l_TimeOut, mask, &key);			// Wait 10s with mask
				}
			}

		#ifdef _TOOLWARE_
			// Warning : +10 id added for display (+1000ms)
			if (ucAdvancedMode == TRUE)
			{
				unsigned long ulFin_ihm;
				ulFin_ihm = get_tick_counter();

				switch (function)
				{
				case EMVDC_CARD_ACTION_ANALYSIS:
					ulMMI_force_CAA = ulFin_ihm - ulDebut_ihm + 100;
					break;

				case EMVDC_ON_LINE_PROCESSING:
					ulMMI_force_OLP = ulFin_ihm - ulDebut_ihm + 100;
					break;

				case EMVDC_COMPLETION:
				default:
					ulMMI_force_COMP = ulFin_ihm - ulDebut_ihm + 100;
					break;
				}
			}
		#endif
				switch (key)
				{
				case (T_SK2):
				case (T_VAL):
					is_forced_acceptance[1] = 0x01;		// Force acceptance = TRUE
					break;

				case (T_SK3):
				case (T_ANN):
				case (T_CORR):
				case (TIMEOUT):
				default:
					// is_forced_acceptance[1] = 0x00;	// Force acceptance = FALSE = default value
					break;
				}

		}
}

//===========================================================================
//! \brief This function displays the "CANCEL" message.
//! \param[in] merchLang : used language.
//===========================================================================
static void DisplayCancel(unsigned short merchLang)
{
	CUTERMdisplayLine(0, CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_CANCEL, merchLang), CENTER, (char *)"w");
}

//===========================================================================
//! \brief This function tests the presence of communication component.
//! \param[in] type_appli : application type of communication component.
//! \return
//! - TRUE if communication component loaded.
//! - FALSE otherwise.
//===========================================================================
static int Is_COMM_COMPONENT_Loaded (unsigned char type_appli)
{
	int comm_exist;
	unsigned char priority;

	comm_exist = FALSE;

	if (ServiceGet(type_appli,I_COMM_CONNECT,&priority)==0)
	{
      // Spdh  segment not found
      comm_exist= TRUE;
   }

	return (comm_exist);
}

//===========================================================================
//! \brief This function calls the service that initializes the communication
//! parameters.
//! \param[in] hInputTLVTree : input TLV tree containing the communication
//! configuration.
//! \return
//! - B_TRUE if communication configuration OK.
//! - 0xFFFF otherwise.
//===========================================================================
static int Host_Comm_Configure (TLV_TREE_NODE hInputTLVTree)
{
	int ret;
	unsigned short found;
	TLV_TREE_NODE hTree;
	DataElement Data_Elt;


	ret = 0xFFFF;
	hTree = COMM_Configure_TlvTree(hInputTLVTree);
	if(hTree != NULL)
	{

		found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_COMM_STATUS_CODE, &Data_Elt);
		if (found == B_TRUE)
		{
			if ( CharToShort(Data_Elt.ptValue) == TAG_COMM_PROCESS_COMPLETED )
			{
				ret = B_TRUE;
			}
		}

		// Release local TLV tree
		TlvTree_ReleaseEx(&hTree);
	}

	return ret;
}


//===========================================================================
//! \brief This function begins the connection with the host.
//! \return
//! - B_TRUE if communication connexion is OK.
//! - B_FALSE otherwise.
//===========================================================================
static int Host_Comm_Connect (void)
{
	int ret;
	unsigned short found;
	unsigned short CommOK;
	unsigned char  buf[11];
	TLV_TREE_NODE  hTree;
	DataElement    Data_Elt;
	DataElementExt  eltExt;

	ret = B_FALSE;


	// Get data from COMM

	hTree = COMM_Connect_TlvTree(NULL);

	if(hTree != NULL)
	{
		found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_COMM_STATUS_CODE, &Data_Elt);
		if (found == B_TRUE)
		{
			if ( CharToShort(Data_Elt.ptValue) == TAG_COMM_PROCESS_COMPLETED )
			{
				// Store data to CUDB Current

				CommOK = TRUE;
				ShortToChar(CommOK,buf);
				eltExt.elt.tag      = TAG_CUST_IS_COMMUNICATION_OK;
				eltExt.elt.length   = 2;
				eltExt.elt.ptValue  = (unsigned char *)buf;

				// Store data into pTreeAppli TLV tree
				PAR_SetParameter(TAG_CUST_IS_COMMUNICATION_OK, eltExt);

				ret = B_TRUE;
			}
		}

		// Release local TLV tree
		TlvTree_ReleaseEx(&hTree);
	}

	return ret;
}

//===========================================================================
int Host_Comm_Protocol (void)
{
	int ret;
	TLV_TREE_NODE hOutputTlvTree;
	TLV_TREE_NODE hNode;
	const unsigned char* pValue;

	ret = COMM_PROTOCOL_TYPE_YES;

	hOutputTlvTree = COMM_Get_Protocol_Info_TlvTree(NULL);

	if (hOutputTlvTree != NULL)
	{
		hNode = TlvTree_Find(hOutputTlvTree, TAG_COMM_PROTOCOL_TYPE, 0);

		if (hNode != NULL)
		{
			pValue = TlvTree_GetData(hNode);

			if (pValue != NULL)
				ret = *pValue;
		}
	}

	TlvTree_ReleaseEx(&hOutputTlvTree);

	return ret;
}

//===========================================================================
int Host_Config_Connect(void)
{
	int isConnected;
	TLV_TREE_NODE hTree;

	isConnected = FALSE;

	// TLV tree creation
	hTree = TlvTree_New(0);

	if(hTree != NULL)
	{
		if (Is_COMM_COMPONENT_Loaded(I_COMM_DEFAULT_TYPE_APPLI))
		{
			// Mixed Communication with ISO8583 and SPDH
			Protocol_Type = Host_Comm_Protocol();
			if (Protocol_Type != COMM_PROTOCOL_TYPE_SPDH )
			{
				EMVCUST_BuildCommConfig_ISO8583(3000, 0, &hTree);
			}
			else
			{
				// EMVCUST_BuildCommConfig_Spdh(&hTree);
			}

			if (Host_Comm_Configure(hTree) == B_TRUE)
			{
				if (Host_Comm_Connect () == B_TRUE)
				{
					isConnected = TRUE;
				}
			}
		}

		// Release the local TlvTree
		// TlvTree_ReleaseEx(&hTree);
	}

	return isConnected;
}

//===========================================================================
//! \brief This function manages the proprietary input by keyboard.
//! \return \ref PROPRIETARY_METHOD.
//===========================================================================
static unsigned char CU_EnterProprietaryMethod(void)
{
	char carac;
	FILE *keyb,*display;

	buffer_result = 00;
#ifdef _USE_UCM_
	if(UCM_Present)
	{
		iLIBUCM_Display_Open(UCMC_DISPLAY,"w");
		iLIBUCM_Display_Message(UCMC_DISPLAY,"PROPRIETARY\n METHOD\n",0);
		iLIBUCM_Pinpad_Open(UCMC_PPAD,"r");
		carac = iLIBUCM_Pinpad_GetChar(UCMC_PPAD);

		/* Key simulation for IUC180B */
		if( giKeyboardType == PARAM_TYPE_IUC180B )
		{
		   switch( carac )
		   {
		      case T_SKHAUT:
		         carac = T_ANN;
		      break;

		      case T_SKBAS:
		         carac = T_VAL ;
		      break;
		   }
		}
		
		iLIBUCM_Pinpad_Close(UCMC_PPAD);
		iLIBUCM_Display_Close(UCMC_DISPLAY);
	}
	else
#endif
	{
		unsigned short mask;
		byte b_l_TimeOut;

		display=fopen("DISPLAY","w");
		fprintf(display,"PROPRIETARY\n METHOD\n");
		keyb = fopen("KEYBOARD","r");

		carac = (T_CUTERMkey)CU_VALID; /* init =/= CANCEL */
		b_l_TimeOut = 120; /* 120s */
		mask = MASK_ANNULATION | MASK_CORRECTION | MASK_VALIDATION | MASK_SKVAL | MASK_SKCORR | MASK_SK1 | MASK_SK2 | MASK_SK3 | MASK_SK4;

		CUTERM_Wait_function_key(b_l_TimeOut, mask, (T_CUTERMkey*)&carac); /* 10s with mask */

		fclose(keyb);
		fclose(display);
	}

	switch(carac)
	{
	case T_VAL:
		buffer_result = 01;
		break;
	case T_CORR:
	case T_ANN:
	case TIMEOUT:
	default:
		buffer_result = 00;
		break;
	}

	return (PROPRIETARY_METHOD);
}


// Refashion of Pin Pad management file
//===========================================================================
//! \brief This function performs the online pin code entry : it tests the
//! tag TAG_APPLI_PRIM_ACCOUNT_NB and calls the function CUPIN_EnterPinOnLine().
//! \param[in] nb_try : number of PIN entry attempts.
//! \param[out] buffer : buffer to store enciphered PIN.
//! \return
//! - PP_HS : Problem with the PINPAD, or with the booster.
//! - INPUT_PIN_ON : PIN entry and encipherement was successfull.
//! - CANCEL_INPUT : PIN entry was canceled.
//! - TO_INPUT : Time-out during PIN entry.
//===========================================================================
static unsigned char CallEnterPinOnLine(unsigned char nb_try, ENTRY_BUFFER *buffer)
{
	unsigned char  cr_enter_pin;
	unsigned short found;
	DataElement    elt;
	TLV_TREE_NODE  hTree;

	// Retreive TAG_APPLI_PRIM_ACCOUNT_NB from EMVDC
	hTree = Engine_GetDataElement(TAG_APPLI_PRIM_ACCOUNT_NB);

	found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APPLI_PRIM_ACCOUNT_NB, &elt);

	if (found)
	{
		cr_enter_pin = CUPIN_EnterPinOnLine(nb_try, TRUE, buffer, elt.ptValue,&Bypass_Required);
	}
	else
	{
		cr_enter_pin = PP_HS;
	}

	// Release the local TlvTree
	TlvTree_ReleaseEx(&hTree);

	return(cr_enter_pin);
}

//===========================================================================
//! \brief This function tests if the terminal is configured to perform an
//! online advice.
//! \return
//! - B_TRUE if the terminal can perform an online advice.
//! - B_FALSE otherwise.
//===========================================================================
static T_Bool Online_Advice_Conditions(void)
{
	T_Bool  ret;
	int found;
	DataElement elt;
	TLV_TREE_NODE hTree;

	ret = B_FALSE;

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	// Get TAG_IS_ADVICE_REQUIRED from EMVDC
	hTree = Engine_GetDataElement(TAG_IS_ADVICE_REQUIRED);

	found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_IS_ADVICE_REQUIRED, &elt);
	if (found)
	{
		if ( elt.ptValue[0] == 0x01 )
		{
			// Get data from TLV tree
			found = PAR_ReadParameter(TAG_CUST_IS_BATCH_CAPTURE, (DataElementExt *)&elt);
			if (found)
			{
				if ( elt.ptValue[0] == 0x00 )
				{
					found = PAR_ReadParameter(TAG_CUST_IS_ONLINE_CAPTURE, (DataElementExt *)&elt);
					if (found)
					{
						if ( elt.ptValue[0] == 0x01 )
						{
							if (Is_Offline_Only()!=FCT_OK)
								ret = B_TRUE;
						}
					}
				}
			}
		}
	}

	// Release the local TlvTree
	TlvTree_ReleaseEx(&hTree);

	return (ret);
}

//===========================================================================
//! \brief This function sends an advice message.
//! \param[out] error_code : set to TAG_CUST_PROCESSING_ERROR in case of
//! communication error.
//! \param[in] ptr_usMerchantLang : current language.
//===========================================================================
static void Send_Advice_Message_TLVTree(unsigned short * error_code, unsigned short *ptr_usMerchantLang)
{
	unsigned short found;
	DataElement   elt;
	unsigned char text[26];
	TLV_TREE_NODE hTree,hTreeSR;

#ifdef _TOOLWARE_
	unsigned long ulDebut_online=0;
#endif
	hTreeSR = NULL;
	if (!CommProblem)
	{

		// Connect with the acquirer host
		if (!isConnected)
		{
			isConnected = Host_Config_Connect();
		}

		if (isConnected)
		{

			Protocol_Type = Host_Comm_Protocol();
			if (Protocol_Type != COMM_PROTOCOL_TYPE_SPDH )
			{
				EMVCUST_Build_advice_TLVTree_Iso8583(&hTree);
			}
			else
			{
				// EMVCUST_Build_advice_TLVTree_Spdh(&hTree);
			}

#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				ulDebut_online = get_tick_counter();
			}
#endif

			hTreeSR = COMM_Send_And_Receive_Message_TlvTree(hTree);

#ifdef _TOOLWARE_
			if (ucAdvancedMode == TRUE)
			{
				unsigned long ulFin_online;
				ulFin_online = get_tick_counter();
				ulHOST_comm += ulFin_online - ulDebut_online;
			}
#endif
		}


		// Read Communication Status
		found = CUSERV_Extract_Element_TLV_Tree(&hTreeSR, TAG_COMM_STATUS_CODE, &elt);
		if (found)
		{
			if ((elt.ptValue[0] == 0x01)&&(elt.ptValue[1] == 0x04))
			{
				CommProblem = TRUE;
				CUSERV_CommRetries = CUSERV_COMM_MAX_RETRIES+1;
			}
		}

		if (!CommProblem)
		{
			found = CUSERV_Extract_Element_TLV_Tree(&hTreeSR, TAG_AUTHORISATION_RESPONSE_CODE, &elt);

			// Check Authorisation Response Code
			if (found)
			{
				if ((elt.ptValue [0] < 0x30) || /* '0'   */
					(elt.ptValue [0] > 0x39) || /* '9'   */
					(elt.ptValue [1] < 0x30) || /* '0'   */
					(elt.ptValue [1] > 0x39))   /* '9'   */
				{
					// Y2, Z2 acceptance
					if ((memcmp (elt.ptValue, ARC_REFERRAL_APPROVED, 2) != 0) &&
						(memcmp (elt.ptValue, ARC_REFERRAL_DECLINED, 2) != 0))
					{
						CommProblem = TRUE;
						CUSERV_CommRetries = CUSERV_COMM_MAX_RETRIES+1;
					}
				}
				else if ((elt.ptValue [0] == 0x30) &&
					(elt.ptValue [1] == 0x30))
				{
					if(Is_Offline_Only()==FCT_OK)
						TransacOk = FALSE;
					else
						TransacOk = TRUE;
				}
			}
			else
			{
				CommProblem = TRUE;
				CUSERV_CommRetries = CUSERV_COMM_MAX_RETRIES+1;
			}
		}

		if (CommProblem)
		{
			if (CUSERV_CommRetries > CUSERV_COMM_MAX_RETRIES)
			{
				strcpy ((char* ) text, CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_COMM_PROBLEM, *ptr_usMerchantLang));
				CUTERMdisplayLine(0, (char *)text, CENTER, (char *)"w");
				CUTERMsleep (1000);
				*error_code = TAG_CUST_PROCESSING_ERROR;
			}
		}
	}

	TlvTree_ReleaseEx(&hTreeSR);

}



//! @}

static void StopBeep(void)
{
#ifdef _USE_UCM_

#else
	active_beep=FALSE;

	PSQ_read_state_param(&param);
	if (param.BeepOn == 1)
	{
		active_beep=TRUE;
		param.BeepOn = 0;
		PSQ_write_state_param(&param);
	}

 #endif       
}

static void ReStartBeep(void)
{		
#ifdef _USE_UCM_

#else
	if (active_beep==TRUE)
	{
		param.BeepOn = 1;
		PSQ_write_state_param(&param);
	}
#endif
}
void EMVCUST_ParamFile_Upload_TlvTree (TLV_TREE_NODE *phOutputTLVTree)
{
	int cr, merchLang;
	char *pc_l1_DisplayTxt;
	char *pc_l2_DisplayTxt;
	char *pc_l_DisplayTxt;
	int	Comm_Protocol;
	unsigned char msg[100];
	TLV_TREE_NODE phOutputTLVTreeBuild;
	TLV_TREE_NODE hTreeDis;
		merchLang = PSQ_Give_Language();
		if (merchLang > C_NBLANGMERCH)
		{
			merchLang = 0;
		}
		cr = powered();
		Comm_Protocol = Host_Comm_Protocol();
		if ((cr !=1)&&(IsPortable()==1) && (Comm_Protocol != COMM_PROTOCOL_TYPE_YES ))
		{
			pc_l_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_REPLACE_BASE, merchLang);
			CUTERMdisplayLine(0, pc_l_DisplayTxt, CENTER, (char *)"w");
			do
			{
				cr = powered();
			} while (cr != 1);
			CUMESS_Display_Message (0, STD_MESS_PLEASE_WAIT, DISPLAY_MERCHANT);
		}
		if (!isConnected)
		{
			isConnected = Host_Config_Connect();
		}
		if (isConnected)
		{
			phOutputTLVTreeBuild = TlvTree_New(0);
			phOutputTLVTreeBuild = EMVCUST_Build_LoadParam_TLVTree (&phOutputTLVTreeBuild);
			pc_l1_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, IAID_MESS_LOAD_MESS_1, merchLang);
			pc_l2_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, IAID_MESS_LOAD_MESS_2, merchLang);
			memset(msg, 0, sizeof(msg));
			sprintf((char*)msg, " %s\n  %s", pc_l1_DisplayTxt, pc_l2_DisplayTxt);
			CUTERMdisplayLine(0, (char*)msg , CENTER, (char *)"w");
			*phOutputTLVTree = COMM_Receive_File_TlvTree(phOutputTLVTreeBuild);
			hTreeDis = COMM_Disconnect_TlvTree (NULL);
			isConnected = FALSE;
			TlvTree_ReleaseEx(&hTreeDis);
			TlvTree_ReleaseEx(&*phOutputTLVTree);
	}
	TlvTree_ReleaseEx(&phOutputTLVTreeBuild);
}



