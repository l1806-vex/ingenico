/**
* \file cu_more.c
* \brief This module contains the functions activated by the navigation menus.
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
#include "del_lib.h"
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
#include "cu_entry.h"
#include "convert.h"
#include "cu_param.h"
#include "gestion_param.h"
#include "cu_comm.h"
#include "servcomm.h"
#include "servcomm_TlvTree.h"
#include "convert.h"
#include "cu_file.h"
#include "LinkLayer.h"
#include "serveng.h"
#include "cu_disk.h"
#include "EngineInterfaceLib.h"
#include "TlvTreeDel.h"
#include "EngineInterface.h"
#include "cu_trfile.h"
#include "WGUI.h"
#include "cu_wgui.h"

//! \addtogroup Group_cu_more
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define TO_PARAM    120								//!< Time-out for parameter entry

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

static void CUMORE_Cash          (void);
static void CUMORE_CashBack      (void);
static void CUMORE_BatchStat     (void);
static int  CUMORE_BatchCaptRaz  (void);
static void CUMORE_BatchRAZ      (void);
static void CUMORE_Enter_Terminal_ID (void);
static void CUMORE_Reset         (void);
static void CUMORE_Default       (void);
static void CUMORE_Administrative(void);
static void CUMORE_Inquiry       (void);


static void CUMORE_Dump_GParam   (void);
static void CUMORE_Bypass_PIN (void);

static void CUMORE_ForcedOnline  (void);
static void CUMORE_TransactionLog(void);

static int merchant(void);
static int ParamManagement(void);

#ifdef _TOOLWARE_
static void CUMORE_Demo_Mode(void);
#endif /* _TOOLWARE_ */

static void CUMORE_Dump_ICS(void);
static int CUMORE_Send_Financial_Record (TLV_TREE_NODE hInputTree);
static int CUMORE_Send_Advice_Record (TLV_TREE_NODE hInputTree);
static void CUMORE_Dump_AID(void);

/* ========================================================================*/
/* Constant declarations                                                   */
/* ========================================================================*/

const NavigationListe NavigationEmvdc[] =
{
	{CMN_MESS_DEBIT,                    (PFONCNAVI) CUMORE_Debit},
	{CMN_MESS_REFUND,                   (PFONCNAVI) CUMORE_Refund},
	{CMN_MESS_EMV_CASH,                 (PFONCNAVI) CUMORE_Cash},
	{CMN_MESS_EMV_CASHBACK,             (PFONCNAVI) CUMORE_CashBack},
	{CMN_MESS_EMV_ADMINISTRATIVE,       (PFONCNAVI) CUMORE_Administrative},
	{CMN_MESS_EMV_INQUIRY		,       (PFONCNAVI) CUMORE_Inquiry},
	{CMN_MESS_MERCHANT,                 (PFONCNAVI) merchant}
#ifdef _TOOLWARE_
	,{CMN_MESS_MERCHANT_TOOLWARE, (PFONCNAVI) CUMORE_Demo_Mode}
#endif /* _TOOLWARE_ */
};

static const NavigationListe NavigationMerchant[] =
{
	{CMN_MESS_MERCHANT_BYPASSPIN,       (PFONCNAVI) CUMORE_Bypass_PIN},
	{CMN_MESS_MERCHANT_BATCH_STAT,      (PFONCNAVI) CUMORE_BatchStat},
	{CMN_MESS_MERCHANT_RUN_BATCH,       (PFONCNAVI) CUMORE_BatchCaptRaz},
	{CMN_MESS_MERCHANT_PARAM_MNGT,      (PFONCNAVI) ParamManagement},
	{CMN_MESS_MERCHANT_FORCE_ONLINE,    (PFONCNAVI) CUMORE_ForcedOnline},
	{CMN_MESS_MERCHANT_TRANSACTIONLOG,  (PFONCNAVI) CUMORE_TransactionLog}
};

static const NavigationListe NavigationBatchCapt[] =
{
	{CMN_MESS_MERCHANT_RUN_BATCH_RAZ,   (PFONCNAVI) CUMORE_BatchCapt},
	{CMN_MESS_MERCHANT_BATCH_RAZ,       (PFONCNAVI) CUMORE_BatchRAZ}
};

static const NavigationListe NavigationParamMngt[] =
{
	{CMN_MESS_MERCHANT_RESET_ALL,       (PFONCNAVI) CUMORE_Reset},
	{CMN_MESS_MERCHANT_DEFAUT_CONF,     (PFONCNAVI) CUMORE_Default},
	{CMN_MESS_MERCHANT_TERMINAL_ID,		(PFONCNAVI) CUMORE_Enter_Terminal_ID},
	{CMN_MESS_MERCHANT_DUMP_ICS,		(PFONCNAVI) CUMORE_Dump_ICS},
	{CMN_MESS_MERCHANT_DUMP_AID,		(PFONCNAVI) CUMORE_Dump_AID},
	{CMN_MESS_MERCHANT_GLOBAL_PARAM,	(PFONCNAVI) CUMORE_Dump_GParam},
};


const unsigned char CUMORE_TRUE []   = {0x00, 0x01};
const unsigned char CUMORE_FALSE []  = {0x00, 0x00};

// static const TAB_ENTRY_STRING t_term_id={0x0000,TO_PARAM,1,0,1,8,1};


/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

unsigned short Bypass_Required;

unsigned short TransactionForcedOnline;

//extern unsigned char ucMode2000;

unsigned char RetransmitIndicator;

TLV_TREE_NODE CUMORE_Tree;

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
//! \brief This function manages the application Merchant menu.
//! \return The Get_Entry return value.
//! - CR_ENTRY_OK : Successful entry.
//! \li the field d_entry[0] of Entry_buffer contains the index of the selected
//! item in the list for G_List_Entry.
//! \li the field d_len of Entry_buffer contains the entry length.
//! \li the field d_entry [50]  of Entry_buffer contains the entry for G_Numerical_Entry.
//! - CR_ENTRY_NOK : Correction (if authorised)
//! - CR_ENTRY_TIME_OUT : Timeout elapsed
//! - CR_ENTRY_CANCEL : Entry Cancelled
//! - CR_ENTRY_VAL : Green key (confirmation)
//! - CR_ENTRY_FCT : F key pushed (if authorised)
//! - CR_ENTRY_SK1 : SK1 ('1' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK2 : SK2 ('2' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK3 : SK3 ('3' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK4 : SK4 ('4' on EFT930M or ML30) key pushed (if authorised)
//===========================================================================
static int merchant(void)
{
	unsigned char	cr;
	unsigned char	i;
	ENTRY_BUFFER	Entry_buffer;
	unsigned short	lg_code;
	wIconList		IconLst;

	memclr(&IconLst, sizeof(IconLst));

	// Init table from const
	InitDefaut(_ON_,1);

	lg_code = PSQ_Give_Language();

	if(Get_StateWGUI())
	{

		// Init icon list structure
		CUWGUI_InitIconList(&IconLst);
		InitMSGinfos(&IconLst.title);
		IconLst.title.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT, lg_code);

		for (i=0 ; i < ELVEC(NavigationMerchant) ; i++ )
		{
			InitMSGinfos(&IconLst.tab[i]);
			IconLst.tab[i].message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, NavigationMerchant[i].itemlabel, lg_code);
			CUWGUI_load_icon(NavigationMerchant[i].itemlabel, &IconLst.List[i].name_icon);
			IconLst.List[i].file_directory = (char *)file_dir;

		}

		// Last item
		IconLst.List[i].name_icon = NULL;
		IconLst.tab[i].message = NULL;

		cGUI_Icon_List(&IconLst);

	}
	else
	{
		Menu.Fenetre.titre = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT, lg_code);

		for (i=0 ; i < ELVEC(NavigationMerchant) ; i++ )
		{
			Menu.tab[i] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, NavigationMerchant[i].itemlabel, lg_code);
		}

		// Call navigation time-out 30 secs
		Menu.tab[i] = NULL;

		G_List_Entry(&Menu);

	}

	ttestall(ENTRY,0);
	cr=Get_Entry(&Entry_buffer);

	switch(cr)
	{
		case CR_ENTRY_OK :
			ACCES_FCT0 (NavigationMerchant[Entry_buffer.d_entry[0]].function);
			break;
	}

	return(cr);
}

//===========================================================================
//! \brief This function manages the application ParamManagement menu.
//! \return The Get_Entry return value.
//! - CR_ENTRY_OK : Successful entry.
//! \li the field d_entry[0] of Entry_buffer contains the index of the selected
//! item in the list for G_List_Entry.
//! \li the field d_len of Entry_buffer contains the entry length.
//! \li the field d_entry [50]  of Entry_buffer contains the entry for G_Numerical_Entry.
//! - CR_ENTRY_NOK : Correction (if authorised)
//! - CR_ENTRY_TIME_OUT : Timeout elapsed
//! - CR_ENTRY_CANCEL : Entry Cancelled
//! - CR_ENTRY_VAL : Green key (confirmation)
//! - CR_ENTRY_FCT : F key pushed (if authorised)
//! - CR_ENTRY_SK1 : SK1 ('1' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK2 : SK2 ('2' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK3 : SK3 ('3' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK4 : SK4 ('4' on EFT930M or ML30) key pushed (if authorised)
//===========================================================================
static int ParamManagement(void)
{
	unsigned char	cr;
	unsigned char	i;
	ENTRY_BUFFER	Entry_buffer;
	unsigned short	lg_code;
	wIconList		IconLst;

	memclr(&IconLst, sizeof(IconLst));

	// Init table from const
	InitDefaut(_ON_,1);

	lg_code = PSQ_Give_Language();

	if(Get_StateWGUI())
	{
		// Init icon list structure
		CUWGUI_InitIconList(&IconLst);
		IconLst.title.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_PARAM_MNGT, lg_code);

		for (i=0 ; i < ELVEC(NavigationParamMngt) ; i++ )
		{
			InitMSGinfos(&IconLst.tab[i]);
			IconLst.tab[i].message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, NavigationParamMngt[i].itemlabel, lg_code);
			CUWGUI_load_icon(NavigationParamMngt[i].itemlabel, &IconLst.List[i].name_icon);
			IconLst.List[i].file_directory = (char *)file_dir;

		}

		// Last item
		IconLst.List[i].name_icon = NULL;
		IconLst.tab[i].message = NULL;

		cGUI_Icon_List(&IconLst);
	}
	else
	{
		Menu.Fenetre.titre = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_PARAM_MNGT, lg_code);

		for (i=0 ; i < ELVEC(NavigationParamMngt) ; i++ )
		{
			Menu.tab[i] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, NavigationParamMngt[i].itemlabel, lg_code);
		}

		// Call navigation time-out 30 secs
		Menu.tab[i] = NULL;

		G_List_Entry(&Menu);
	}

	ttestall(ENTRY,0);
	cr=Get_Entry(&Entry_buffer);

	switch(cr)
	{
		case CR_ENTRY_OK :
			ACCES_FCT0 (NavigationParamMngt[Entry_buffer.d_entry[0]].function);
			break;
	}
	return(cr);
}

//===========================================================================
//! \brief This function performs a transaction according to transaction type
//! given as parameter.
//! \param[in] TransactionType : type of the transaction.
//! \param ucParameters  : TRUE if ulAmount and nCurrencyCode parameters must be used.
//! \param ulAmount      : amount entered.
//! \param nCurrencyCode : ISO currency code.
//! \ref CUSERV_DEBIT_TRANSACTION
//! \ref CUSERV_REFUND_TRANSACTION
//! \ref CUSERV_CASH_TRANSACTION
//! \ref CUSERV_CASHBACK_TRANSACTION
//===========================================================================
static void CUMORE_PaiementFct(unsigned long TransactionType, unsigned char ucParameters, unsigned long ulAmount, int nCurrencyCode)
{
#ifdef _ENABLE_CAM2_
	static const unsigned long ulChipReaders = CAM0 | CAM2;
#else
	static const unsigned long ulChipReaders = CAM0;
#endif
	int result;
	int found;
	unsigned short currency_code = 0;
	unsigned char  TabAmount [4];
	unsigned char  TabAmountC [4];
	unsigned char  NumAmount [6];
	unsigned char  NumAmountC [6];
	unsigned long  entered_amount;
	DataElement eltCurrency,eltCurrencyExp;
	unsigned char TypeAppli[2];
	unsigned char EngAppliSel;
	TLV_TREE_NODE hInputTree;
	TLV_TREE_NODE hOutputTree;

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	// -----------------------------------------------------------------
	// Amount Entry
	// -----------------------------------------------------------------

    if (ucParameters == TRUE) // If parameters given in interface must be used
    {
        result = T_VAL;
        entered_amount = ulAmount;
        currency_code = nCurrencyCode;
    }
    else // Parameters : amount and currency code must be inputed or found ...
    {
	    // No card is present at this moment. The currency used is the Terminal currency
	    found = PAR_ReadParameter(TAG_TRANSACTION_CURRENCY_CODE, (DataElementExt *)&eltCurrency);
	    if (found)
		    currency_code = (eltCurrency.ptValue[0] << 8) + eltCurrency.ptValue[1];

	    // Read the amount, using the good currency code
	    result = CUMESS_GetAmount (currency_code, &entered_amount);
    }

	if ((result == T_VAL) && (entered_amount!=0))
	{
		// Amount is valid. Convert in num
		CUMESS_ConvertBinNUM (entered_amount, NumAmount);

		LongToChar (entered_amount, TabAmount);

		// Store amounts in current database

		CUTERMclearDisplay();

		hInputTree = TlvTree_New(0);

		if(hInputTree != NULL)
		{
			ShortToChar(CustApplicationNumber,TypeAppli);
			TlvTree_AddChild(hInputTree, TAG_ENG_CUSTOM_APPLI_TYPE, (unsigned char*) &TypeAppli, 2);

			EngAppliSel =0;
			TlvTree_AddChild(hInputTree, TAG_ENG_APPLI_SEL_ALREADY_DONE, (unsigned char*) & EngAppliSel, 1);

			TlvTree_AddChild(hInputTree, TAG_TRANSACTION_CURRENCY_CODE, (unsigned char*) &eltCurrency.ptValue[0], 2);

			found = PAR_ReadParameter(TAG_TRANSACTION_CURRENCY_CODE, (DataElementExt *)&eltCurrencyExp);
			if (found)
			{
				TlvTree_AddChild(hInputTree, TAG_TRANSACTION_CURRENCY_EXP, (unsigned char*) &eltCurrencyExp.ptValue[0], 1);
			}

			if (TransactionType == CUSERV_CASHBACK_TRANSACTION)
			{
				ulTransactionType = CUSERV_CASHBACK_TRANSACTION;

				// Read the amount, using the good currency code
				result = CUMESS_GetAmount (currency_code, &entered_amount);
				LongToChar (0, TabAmountC);
				memset (NumAmountC,sizeof(NumAmountC),0);
				if ( (result == T_VAL) && (entered_amount!=0) )
				{
					CUMESS_ConvertBinNUM (entered_amount, NumAmountC);

					LongToChar (entered_amount, TabAmountC);
				}
			}
			else
			{
				memclr  ( TabAmountC,sizeof(TabAmountC));
			}
			TlvTree_AddChild(hInputTree, TAG_AMOUNT_OTHER_BIN, TabAmountC, 4);
			TlvTree_AddChild(hInputTree, TAG_AMOUNT_OTHER_NUM, NumAmountC, 6);
			TlvTree_AddChild(hInputTree, TAG_AMOUNT_AUTH_BIN, TabAmount, 4);

			TlvTree_AddChild(hInputTree, TAG_ENG_WAIT_CHIP_READERS, &ulChipReaders, sizeof(ulChipReaders));
			TlvTree_AddChild(hInputTree, TAG_ENG_REMOVE_CHIP_READERS, &ulChipReaders, sizeof(ulChipReaders));

			// Copy the TLV tree to a local _DEL_ object.
			// Convert local _DEL_ object to local DEL object
			// These conversions will be suppressed when Engine_DoTransaction will be implemented in TLV tree mode.
			hOutputTree = TlvTree_New(0);
			if(hOutputTree != NULL)
			{
				Engine_DoTransaction(hInputTree,&hOutputTree);

				// release local TLV tree
				TlvTree_ReleaseEx(&hOutputTree);
			}
		}
	}
}

//===========================================================================
void CUMORE_Debit(void)
{
	ulTransactionType = CUSERV_DEBIT_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_DEBIT_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}

//===========================================================================
void CUMORE_Administrative(void)
{
	ulTransactionType = CUSERV_DEBIT_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_DEBIT_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}
//===========================================================================
void CUMORE_Inquiry(void)
{
	ulTransactionType = CUSERV_DEBIT_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_DEBIT_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}

void CUMORE_DebitEx(unsigned long ulAmount, int nCurrencyCode)
{
	ulTransactionType = CUSERV_DEBIT_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_DEBIT_TRANSACTION, TRUE, ulAmount, nCurrencyCode);
}

//===========================================================================
void CUMORE_Refund (void)
{
	ulTransactionType = CUSERV_REFUND_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_REFUND_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}

//===========================================================================
//! \brief This function performs a cash transaction.
//===========================================================================
static void CUMORE_Cash (void)
{
	/* Memorize the transaction type                                       */
	ulTransactionType = CUSERV_CASH_TRANSACTION;
	CUMORE_PaiementFct(CUSERV_CASH_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}

//===========================================================================
//! \brief This function performs a cash back transaction.
//===========================================================================
static void CUMORE_CashBack(void)
{
	CUMORE_PaiementFct(CUSERV_CASHBACK_TRANSACTION, FALSE, (unsigned long)0, (int)0);
}

//===========================================================================
//! \brief This function gives statistics on the batch data file.
//===========================================================================
static void CUMORE_BatchStat(void)
{
	unsigned long nb_record;
	unsigned long total_amount;
	unsigned long result;
	int merchLang;
	char line[80];
	unsigned char *pcline1;
	unsigned char msg[100];

	// Get manager language
	merchLang = PSQ_Give_Language();
	if (merchLang >= C_NBLANGMERCH)
	{
		merchLang = 0;
	}

	// Display please wait
	pcline1 = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_PLEASE_WAIT, merchLang);
	sprintf(msg, "\n%s", pcline1);
	CUTERMdisplayLine(0, msg, CENTER, (char *)"w");

	// Read statistics
	result = CUBATCH_GiveStatistics (&nb_record, &total_amount);

	if (result)
	{
		// Read language
		// merchLang = PSQ_Give_Language();

		// Print statistics ticket
		CUTERMsetPrinter(PRINT_LARGE);
		CUTERMprintLine("");
		CUTERMprintLine(CUMESS_Read_Message(BATCH_STAT_TABLE, STAT_MESS_BATCH_STATISTICS, merchLang));
		CUTERMprintLine("");
		CUTERMsetPrinter(PRINT_NORMAL);
		sprintf(line,
				"%s   : %ld\n",
				CUMESS_Read_Message(BATCH_STAT_TABLE, STAT_MESS_NB_RECORDS, merchLang),
				nb_record);
		CUTERMprintLine(line);
		sprintf(line,
				"%s   : %ld\n",
				CUMESS_Read_Message(BATCH_STAT_TABLE, STAT_MESS_TOTAL_AMOUNT, merchLang),
				total_amount);
		CUTERMprintLine(line);
		CUTERMprintLine("");
		CUTERMpaperFeed();
	}
}

//===========================================================================
//! \brief This function manages the Bypass PIN function.
//===========================================================================
static void CUMORE_Bypass_PIN (void)
{
	unsigned short		lg_code;
	unsigned char		msg[100];
	unsigned char		*pcline1, *pcline2;

	// Short message to display the BYPASS PIN function is activated for next transaction
	CUDB_Get_cardholder_language (&lg_code);
	if (lg_code >= C_NBLANGMERCH)
	{
		lg_code = 0;
	}

	CUTERMclearDisplay();

	pcline1 = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_BYPASS_PIN_1, lg_code);
	pcline2 = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_BYPASS_PIN_2, lg_code);
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "%s\n%s", pcline1, pcline2);
	CUTERMdisplayLine(0, msg, CENTER, (char *)"w");

	CUTERMsleep (1500);

	// Set the bypass required flag
	Bypass_Required = (CUMORE_TRUE[0] << 8) + CUMORE_TRUE[1];

}

//===========================================================================
//! \brief This function forces the next transaction to go online.
//===========================================================================
static void CUMORE_ForcedOnline (void)
{
	unsigned short		lg_code;
	unsigned char		msg[100];
	unsigned char		*pcline1, *pcline2;

	// Short message to display that next transaction will go online
	CUDB_Get_cardholder_language (&lg_code);
	if (lg_code >= C_NBLANGMERCH)
	{
		lg_code = 0;
	}

	CUTERMclearDisplay();

	pcline1 = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_FORCED_ONLINE_1, lg_code);
	pcline2 = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_FORCED_ONLINE_2, lg_code);
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "%s\n%s", pcline1, pcline2);
	CUTERMdisplayLine(0, msg, CENTER, (char *)"w");

	CUTERMsleep (1500);

	// Set the Transaction forced online flag
	TransactionForcedOnline = (CUMORE_TRUE[0] << 8) + CUMORE_TRUE[1];

}

//===========================================================================
//! \brief This function sends the batch data file to the host thru ISO8583 protocol.
//===========================================================================
static void CUMORE_BatchCapt_Iso8583 (void)
{
	int cr;
	unsigned long nb_record;
	DataElement elt;
	unsigned short found;  // transfer_ok
	int transfer_ok;
	unsigned short NeedBlackList;
	int merchLang;
	unsigned char text [255];
	DATE date;
	unsigned char raz_no_serial [ 9 ]  ;
	int bConnected;
	char *pc_l_DisplayTxt;
	TLV_TREE_NODE hTree, hOutTree,hTreeDis;
	unsigned int Trans_pos = 0;
	unsigned short Trans_index = 0;
	unsigned char *pcline1;
	unsigned char msg[100];

	hTreeDis = NULL;

	// Read number of records
	CUBATCH_InitialiseBatchTransfer (&nb_record);

	merchLang = PSQ_Give_Language();

	// Put on base only X930
	if (( powered() !=1)&&(CUTERMgetTerminalType()==T_CUTERM_X930))
	{
		pc_l_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_REPLACE_BASE, merchLang);
		CUTERMdisplayLine(0, pc_l_DisplayTxt, CENTER, (char *)"w");
		do
		{
			cr = powered();
		} while (cr != 1);

		CUMESS_Display_Message (0, STD_MESS_PLEASE_WAIT, DISPLAY_MERCHANT_CARDHOLDER);
	}

	// Display please wait
	pcline1 = CUMESS_Read_Message(STANDARD_TABLE, STD_MESS_PLEASE_WAIT, merchLang);
	sprintf(msg, "\n%s", pcline1);
	CUTERMdisplayLine(0, msg, CENTER, (char *)"w");

	/*-----------------------------------------------------------------------*/
	/* Batch transfer initialisation                                         */
	/*-----------------------------------------------------------------------*/
	found = FALSE;

	bConnected = Host_Config_Connect();

	if (bConnected)
	{
		// Sequence Counter : 9F41
		hTree = Engine_GetDataElement(TAG_TRANSACTION_SEQ_COUNTER);

		hOutTree = TlvTree_New(0);

		if(hOutTree != NULL)
		{

			found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_TRANSACTION_SEQ_COUNTER, &elt);
			if (found)
			{
				TlvTree_AddChild(hOutTree, elt.tag, elt.ptValue, elt.length);
			}

			// release local TLV tree
			TlvTree_ReleaseEx(&hTree);

			// Improvement of IFD_serial number and terminal id management
			CUTERMgetSerialNumber((char*)raz_no_serial);
			TlvTree_AddChild(hOutTree, TAG_IFD_SERIAL_NUMBER, raz_no_serial, 8);

			TlvTree_AddChild(hOutTree, TAG_CUST_NB_RECORD_IN_BATCH, ( unsigned char *) &nb_record, 4);

			// Check Black-list validity
			NeedBlackList = !(CUBLACKL_IsValid ());
			TlvTree_AddChild(hOutTree, TAG_CUST_NEW_BLACK_LIST_NEEDED, ( unsigned char *) &NeedBlackList, 2);

			// Batch transfer initialisation
			found = FALSE;

			// Generate batch TLV tree in the same way than for authorisation
			hOutTree = EMVCUST_Build_start_transac_download_TLVTree(&hOutTree);

			hOutTree = COMM_Send_And_Receive_Message_TlvTree(hOutTree);

			found = CUSERV_Extract_Element_TLV_Tree(&hOutTree, TAG_COMM_STATUS_CODE, &elt);
		}
	}
	else
	{
		found = FALSE;
	}

	transfer_ok = (found && (*(elt.ptValue) == 0));
	if (transfer_ok)
	{
		/*-----------------------------------------------------------------------*/
		/* Batch transfer loop                                                   */
		/*-----------------------------------------------------------------------*/

		cr = CUDISK_CreateDisk();
		if (cr == FS_OK)
		{
			do
			{
				cr = Get_Next_Transaction(&Transac_File, &hTree, &Trans_pos);

				if (cr == TRANS_FILE_OK)
				{
					// Get TAG_CUST_BATCH_RECORD_TYPE
					found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_CUST_BATCH_RECORD_TYPE, &elt);
					if (found)
					{
						// Check if record read is a financial record
						if (elt.ptValue[0] == FINANCIAL_RECORD)
						{
							transfer_ok = CUMORE_Send_Financial_Record(hTree);
						}
						else
						{
							transfer_ok = CUMORE_Send_Advice_Record(hTree);
						}

						Trans_index++;

						if (transfer_ok)
						{
							// Erase the record
							RetransmitIndicator = FALSE;
						}
						else
						{
							// Mark the record has been transmitted
							RetransmitIndicator = TRUE;
						}
					}
				}

				TlvTree_ReleaseEx(&hTree);
			}
			while ((Trans_index < nb_record) && (transfer_ok));
			// End of batch transfer loop
			// while (cr == TRANS_FILE_OK);

			if ((Trans_index == nb_record) && transfer_ok)
			{
				// All the transaction records are sent. The file can be deleted
				Del_Transaction_File(&Transac_File);
			}

			// Unmount the volume
			CUDISK_UnmountDisk();
		}

		/*-----------------------------------------------------------------------*/
		/* Batch transfer termination                                            */
		/*-----------------------------------------------------------------------*/

		// Sequence Counter : 9F41
		hTree = Engine_GetDataElement(TAG_TRANSACTION_SEQ_COUNTER);

		// release local TLV tree
		TlvTree_ReleaseEx(&hOutTree);

		hOutTree = TlvTree_New(0);

		if(hOutTree != NULL)
		{
			found = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_TRANSACTION_SEQ_COUNTER, &elt);
			if (found)
			{
				TlvTree_AddChild(hOutTree, elt.tag, elt.ptValue, elt.length);
			}

			// release local TLV tree
			TlvTree_ReleaseEx(&hTree);

			// Improvement of IFD_serial number and terminal id management
			// CUTERMgetTerminalId ( (char *) card_acceptor_terminal_id ) ;
			CUTERMgetSerialNumber((char*)raz_no_serial);
			TlvTree_AddChild(hOutTree, TAG_IFD_SERIAL_NUMBER, ( unsigned char * ) raz_no_serial, 8);

			// Mixed Communication with ISO8583 and SPDH
			// Send record
			hOutTree = EMVCUST_Build_terminate_transac_download_TLVTree(&hOutTree);

			hOutTree = COMM_Send_And_Receive_Message_TlvTree(hOutTree);

			found = CUSERV_Extract_Element_TLV_Tree(&hOutTree, TAG_COMM_STATUS_CODE, &elt);

			transfer_ok = (found && transfer_ok && (*(elt.ptValue) == 0));

		}
	}
	else
	{
		// else communication KO

		// Mixed Communication with ISO8583 and SPDH
		hOutTree = EMVCUST_Build_terminate_transac_download_TLVTree(&hOutTree);

		hOutTree = COMM_Send_And_Receive_Message_TlvTree(hOutTree);
	}

	// release local TLV tree
	TlvTree_ReleaseEx(&hOutTree);

	// Generate batch TLV tree in the same way than for authorisation
	if (bConnected)
	{
		hTreeDis=COMM_Disconnect_TlvTree (NULL);
		bConnected = FALSE;
		TlvTree_ReleaseEx(&hTreeDis);
	}

	/*-----------------------------------------------------------------------*/
	/* ticket                                                                */
	/*-----------------------------------------------------------------------*/
	sprintf ((char *) text, "\x1b""E%s""\x1b""F", CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_APPLI_NAME, merchLang));
	CUTERMprintLine((char *)text);

	read_date(&date);
	sprintf ((char *) text, "%.2s/%.2s/%.2s  %.2s:%.2s", date.day, date.month, date.year, date.hour, date.minute);
	CUTERMprintLine((char *)text);

	pc_l_DisplayTxt = CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CNS_MESS_CAPTURE, merchLang);
	CUTERMprintLine(pc_l_DisplayTxt);
	if (transfer_ok)
	{
		// DATA CAPTURE SUCCESFUL
		pc_l_DisplayTxt = CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CNS_MESS_SUCCESFUL, merchLang);
		CUTERMprintLine(pc_l_DisplayTxt);
	}
	else
	{
		// DATA CAPTURE ERROR
		pc_l_DisplayTxt = CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CNS_MESS_ERROR, merchLang);
		CUTERMprintLine(pc_l_DisplayTxt);
	}

	CUTERMpaperFeed();
}

//===========================================================================
//! \brief This function erases the batch data file without data capture.
//! \return The Get_Entry return value.
//! - CR_ENTRY_OK : Successful entry.
//! \li the field d_entry[0] of Entry_buffer contains the index of the selected
//! item in the list for G_List_Entry.
//! \li the field d_len of Entry_buffer contains the entry length.
//! \li the field d_entry [50]  of Entry_buffer contains the entry for G_Numerical_Entry.
//! - CR_ENTRY_NOK : Correction (if authorised)
//! - CR_ENTRY_TIME_OUT : Timeout elapsed
//! - CR_ENTRY_CANCEL : Entry Cancelled
//! - CR_ENTRY_VAL : Green key (confirmation)
//! - CR_ENTRY_FCT : F key pushed (if authorised)
//! - CR_ENTRY_SK1 : SK1 ('1' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK2 : SK2 ('2' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK3 : SK3 ('3' on EFT930M or ML30) key pushed (if authorised)
//! - CR_ENTRY_SK4 : SK4 ('4' on EFT930M or ML30) key pushed (if authorised)
//===========================================================================
static int CUMORE_BatchCaptRaz(void)
{
	unsigned char	cr;
	unsigned char	i;
	ENTRY_BUFFER	Entry_buffer;
	unsigned short	lg_code;
	wIconList		IconLst;

	memclr(&IconLst, sizeof(IconLst));

	// Init table from const
	InitDefaut(_ON_,1);

	lg_code = PSQ_Give_Language();

	if(Get_StateWGUI())
	{
		// Init icon list structure
		CUWGUI_InitIconList(&IconLst);
		IconLst.title.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_RUN_BATCH, lg_code);

		for (i=0 ; i < ELVEC(NavigationBatchCapt) ; i++ )
		{
			InitMSGinfos(&IconLst.tab[i]);
			IconLst.tab[i].message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, NavigationBatchCapt[i].itemlabel, lg_code);
			CUWGUI_load_icon(NavigationBatchCapt[i].itemlabel, &IconLst.List[i].name_icon);
			IconLst.List[i].file_directory = (char *)file_dir;

		}

		// Last item
		IconLst.List[i].name_icon = NULL;
		IconLst.tab[i].message = NULL;

		cGUI_Icon_List(&IconLst);

	}
	else
	{
		Menu.Fenetre.titre = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_RUN_BATCH, lg_code);

		for (i=0 ; i < ELVEC(NavigationBatchCapt) ; i++ )
		{
			Menu.tab[i] = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, NavigationBatchCapt[i].itemlabel, lg_code);
		}

		// Call navigation time-out 30 secs
		Menu.tab[i] = NULL;

		G_List_Entry(&Menu);
	}

	ttestall(ENTRY,0);
	cr=Get_Entry(&Entry_buffer);

	switch(cr)
	{
		case CR_ENTRY_OK :
			ACCES_FCT0 (NavigationBatchCapt[Entry_buffer.d_entry[0]].function);
			break;
	}
	return(cr);
}

//===========================================================================
void CUMORE_BatchCapt()
{
	int Protocol_Type;

	// Mixed Communication with ISO8583 and SPDH
	Protocol_Type = Host_Comm_Protocol();
	if (Protocol_Type != COMM_PROTOCOL_TYPE_SPDH )
	{
		CUMORE_BatchCapt_Iso8583();
	}
	else
	{
		// CUMORE_BatchCapt_Spdh();
	}
}



//===========================================================================
//! \brief This function erases the batch data file.
//===========================================================================
static void CUMORE_BatchRAZ(void)
{
	int  retour;

	retour = CUDISK_CreateDisk();
	if (retour == FS_OK)
	{
		// Erase transaction file
		Del_Transaction_File(&Transac_File);

		// Unmount the volume
		CUDISK_UnmountDisk();

	}
}


//===========================================================================
//! \brief This function initialise the serial number of the terminal.
//===========================================================================
static void CUMORE_Enter_Terminal_ID (void)
{
	// int cr;
	unsigned char cr;
	int	i;
	TLV_TREE_NODE hTree;
	unsigned char card_acceptor_terminal_id [ 9 ];
	int lg_code;
	wStructListe Menu;
	ENTRY_BUFFER buf_entry;
	TAB_ENTRY_STRING t_term_id;
	cGuiStructEntry WGuiEntry;

	// CUSERV_New_Parameters = TRUE;

	lg_code = PSQ_Give_Language();

	memclr( card_acceptor_terminal_id, 9);

	// Get current terminal ID
	CUTERMgetTerminalId(card_acceptor_terminal_id);

	// 3 Trials to get card_acceptor_terminal_id
	i=3;
	while (i>0)
	{
		InitwStructList(&Menu, _ON_, 1);
		Menu.Fenetre.nblines = 1;

		InitMSGinfos(&(Menu.Fenetre.titre));
		CUWGUI_InitStructEntry(&WGuiEntry);

		// Title
		Menu.Fenetre.titre.message = (unsigned char *) CUMESS_Read_Message(TERMINAL_TABLE, CMN_MESS_MERCHANT_TERMINAL_ID2, lg_code);
		WGuiEntry.title.message = Menu.Fenetre.titre.message;

		// Label
		InitMSGinfos_message(&(Menu.tab[0]), NULL);

		// Default value
		InitMSGinfos_message(&(Menu.tab[1]), card_acceptor_terminal_id);
		WGuiEntry.current_value.message = card_acceptor_terminal_id;
		// InitMSGinfos_message(&(Menu.tab[1]), " ");

		// Help
		InitMSGinfos_message(&(Menu.tab[2]), NULL);

		t_term_id.mask = 0x0000;
		t_term_id.time_out = TO_PARAM;
		t_term_id.line = 18;
		t_term_id.column = 20;
		t_term_id.echo = 1;
		t_term_id.nb_max = 8;
		t_term_id.nb_min = 0;

		// wG_Saisie_Numerique(&Menu, (TAB_ENTRY_STRING *)&t_term_id);
		cGUI_Numerical_Entry(&Menu, (TAB_ENTRY_STRING *)&t_term_id, &WGuiEntry);

		ttestall(ENTRY,0);

		cr=Get_Entry(&buf_entry);

		switch (cr)
		{
			case CR_ENTRY_OK :
				memclr(card_acceptor_terminal_id, 9);
				memcpy(card_acceptor_terminal_id, buf_entry.d_entry, buf_entry.d_len);
				CUTERMsetTerminalId ( (char *) card_acceptor_terminal_id );
				CUSERV_New_Parameters = TRUE;
				i=0;
				break;

			case CR_ENTRY_TIME_OUT :
				Stop_Entry();
				i=0;
				break;

			case CR_ENTRY_CANCEL :
				i=0;
				break;

			default :
				memclr(card_acceptor_terminal_id, 9);
				i-- ;
				break;

		}
	}

	/*&BEGIN  FT/07/1692/MA   improvement of IFD_serial number and terminal id management  */
	hTree = TlvTree_New(0);

	if (hTree != NULL)
	{
		TlvTree_AddChild(hTree, TAG_TERMINAL_IDENTIFICATION, (unsigned char *) &card_acceptor_terminal_id, LEN_TERMINAL_IDENTIFICATION);

		CUDB_StoreTLVTree (&hTree);

		// release local TLV tree
		TlvTree_ReleaseEx(&hTree);
	}
	/*&END  FT/07/1692/MA   improvement of IFD_serial number and terminal id management  */


	Bypass_Required = (CUMORE_FALSE[0] << 8) + CUMORE_FALSE[1];

	TransactionForcedOnline = (CUMORE_FALSE[0] << 8) + CUMORE_FALSE[1];

}

//===========================================================================
//! \brief This function resets the database and the keys.
//===========================================================================
static void CUMORE_Reset(void)
{
	char *ptrDummy = 0;

	PAR_InitParam(C_PARAM_INIT_APLI, ptrDummy);
	PAR_InitParam(C_PARAM_INIT_DEFAULT, ptrDummy);

	PAR_ResetMarkList();
	CUPAR_ResetAdditionnalICS();
	CUPAR_ResetAdditionnalAID();
	CUPAR_ResetAdditionnalKRevok();

	CUPAR_InitDefFiles (FALSE);
}

//===========================================================================
//! \brief This function dumps the database from the AID parameters.
//===========================================================================
static void CUMORE_Dump_AID (void)
{
	unsigned int  i_l_NumMark = C_TAG_AID;

	CUTERMprintLine("AID params :\n");
	CUPAR_Tag_Dump(i_l_NumMark);
}

//===========================================================================
//! \brief This function dumps the database from the general parameters.
//===========================================================================
static void CUMORE_Dump_GParam     (void)
{
	CUTERMprintLine("General params :\n");
	CUPAR_TLVTree_Dump(C_TREE_APPLI);
}

//===========================================================================
//! \brief This function reload the parameters with the default values.
//===========================================================================
static void CUMORE_Default(void)
{
	int found;
	char *ptrDummy = 0;
	DataElement elt;

	CUMORE_Reset();

	PAR_InitParam(C_PARAM_DEFAULT, ptrDummy);

	CUPAR_InitDefFiles (TRUE);

	// Reset the selected mark list
	PAR_ResetMarkList();

	// Select Main ICS + ICSx (Maybe unused)
	CUPAR_SelectAdditionnalICS();

	found = PAR_ReadParameter(TAG_TRANSACTION_CURRENCY_CODE, (DataElementExt *)&elt);
	if (found)
		usDefaultCurrency  = (elt.ptValue[0] << 8) + elt.ptValue[1];

	// For real card : No delay
	ucDelayAfterAtr = FALSE;
}

#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function manages the demo mode selection menu.
//===========================================================================
static void CUMORE_Demo_Mode(void)
{
	T_CUTERMkey		key;
	int				merchLang;
	unsigned short	mask = 0;
	byte			b_l_TimeOut;
	unsigned char	msg[100];
	unsigned char	*pc_line1, *pc_line2;
	wStructListe	Menu;
	ENTRY_BUFFER	entry_buffer;
	unsigned char	cr_entry;
	cGuiStructList	MenuWgui;
	int				index;

	CUTERMclearDisplay();
	merchLang = PSQ_Give_Language();
	key = CU_VALID; /* init =/= CANCEL */

	if (ct_SystemSupportToolWare == FALSE)
	{
		ucAdvancedMode = FALSE;
		pc_line1 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_NOT_SUPPORTED, merchLang);
		pc_line2 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_YOUR_SYSTEM, merchLang);
		memset(msg, 0, sizeof(msg));
		sprintf(msg, "%s\n%s", pc_line1, pc_line2);
		CUTERMdisplayLine(0, msg, LEFT, (char *)"w");

		CUTERM_Wait_function_key(2, mask, &key);

		return;
	}
	if(!Get_StateWGUI())
	{

		// Enter type of ticket required
		pc_line1 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_USE_DEMO_MODE, merchLang);
		pc_line2 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_POS_ADVANCED, merchLang);
		memset(msg, 0, sizeof(msg));
		sprintf(msg, "%s\n%s", pc_line1, pc_line2);
		CUTERMdisplayLine(0, msg, LEFT, (char *)"w");


		key = CU_VALID; /* init =/= CANCEL */
		// Init timeout to 10s
		b_l_TimeOut = 10;
		mask = MASK_ANNULATION | MASK_SKCORR | MASK_SK2 | MASK_VALIDATION | MASK_SKVAL |MASK_SK3;

		// Waits 10s with mask
		if (CUTERM_Wait_function_key(b_l_TimeOut, mask, &key) == TRUE)
		{
			//char * PtrMsg;
			unsigned short mask = 0;

			if ((key == T_ANN) ||
				(key == T_CORR) ||
				(key == T_SK2))
			{
				ucAdvancedMode = FALSE;
				CUTERMclearDisplay();
				pc_line1 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_POS_DEMO, merchLang);
				pc_line2 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_SELECTED, merchLang);
				memset(msg, 0, sizeof(msg));
				sprintf(msg, "%s\n%s", pc_line1, pc_line2);
				CUTERMdisplayLine(0, msg, LEFT, (char *)"w");
				CUTERM_Wait_function_key(2, mask, &key);
			}
			else if ((key == T_VAL) ||
				(key == T_SK3))
			{
				ucAdvancedMode = TRUE;
				CUTERMclearDisplay();
				pc_line1 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_ADVANCED_DEMO, merchLang);
				pc_line2 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_SELECTED, merchLang);
				memset(msg, 0, sizeof(msg));
				sprintf(msg, "%s\n%s", pc_line1, pc_line2);
				CUTERMdisplayLine(0, msg, LEFT, (char *)"w");
				CUTERM_Wait_function_key(2, mask, &key);
			}
		}
		// else time-out

		CUTERMclearDisplay();
	}
	else
	{
		InitwStructList(&Menu, _ON_, 1);
		CUWGUI_InitStructList(&MenuWgui);

		InitMSGinfos(&(Menu.Fenetre.titre));
		Menu.Fenetre.titre.message = (unsigned char *) CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_USE_DEMO_MODE, merchLang);
		MenuWgui.title.message = Menu.Fenetre.titre.message;

		// Optional icon not managed
		MenuWgui.full_screen = 1;


		for (index = 0; index < 3; index++)
		{
			InitMSGinfos(&(Menu.tab[index]));
		}

		Menu.tab[0].message = (unsigned char *) CUMESS_Read_Message(DEFAULT_TABLE, DEMO_MESS_POS_DEMO, merchLang);
		Menu.tab[1].message = (unsigned char *) CUMESS_Read_Message(DEFAULT_TABLE, DEMO_MESS_ADVANCED_DEMO, merchLang);
		Menu.tab[2].message = NULL;

		for (index = 0; index < 3; index++)
		{
			InitMSGinfos(&(MenuWgui.tab[index]));
			MenuWgui.tab[index].message = Menu.tab[index].message;

			// Optional icon
			MenuWgui.Icon[index].file_directory = (char *)file_dir;
			MenuWgui.Icon[index].name_icon = " ";
			// CUWGUI_load_icon(STD_MESS_UNDEFINED, &MenuWgui.Icon[index].name_icon);

		}


		cGUI_List_Entry(&Menu, &MenuWgui);
		ttestall(ENTRY,0);
		cr_entry=Get_Entry(&entry_buffer);

		if(cr_entry == CR_ENTRY_OK)
		{
			if (entry_buffer.d_entry[0] == 0)
			{
				ucAdvancedMode = FALSE;
				pc_line1 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_POS_DEMO, merchLang);
				pc_line2 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_SELECTED, merchLang);
				memset(msg, 0, sizeof(msg));
				sprintf(msg, "%s\n%s", pc_line1, pc_line2);
				CUTERMdisplayLine(0, msg, LEFT, (char *)"w");

			}
			else
			{
				ucAdvancedMode = TRUE;
				pc_line1 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_ADVANCED_DEMO, merchLang);
				pc_line2 = CUMESS_Read_Message(DEMO_MODE_TABLE, DEMO_MESS_SELECTED, merchLang);
				memset(msg, 0, sizeof(msg));
				sprintf(msg, "%s\n%s", pc_line1, pc_line2);
				CUTERMdisplayLine(0, msg, LEFT, (char *)"w");
			}
			CUTERMsleep (3000);
		}
	}
}
#endif /* _TOOLWARE_ */

//===========================================================================
//! \brief This function manages the printing of the receipt of the current ICS.
//===========================================================================
static void CUMORE_Dump_ICS(void)
{
	unsigned short lg_code;
	unsigned char msg[100];
	unsigned char *pc_line1, *pc_line2;

	// Retreive language code
	CUDB_Get_cardholder_language (&lg_code);
	if (lg_code > C_NBLANGHOLDER)
	{
		lg_code = 0;
	}

	CUTERMclearDisplay();

	pc_line1 = CUMESS_Read_Message(ICS_TABLE, ICS_MESS_PRINTING_1, lg_code);
	pc_line2 = CUMESS_Read_Message(ICS_TABLE, ICS_MESS_IN_PROGRESS, lg_code);
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "%s\n%s", pc_line1, pc_line2);
	CUTERMdisplayLine(0, msg, LEFT, (char *)"w");


	{
		CUPAR_Print_ICS_Config();
	}

	CUTERMclearDisplay();
}

//===========================================================================
//! \brief This function sends one financial record.
//! \param[in] hInputTree : Input TLV tree containing the financial transaction
//! read in the batch file.
//! \return
//! - TRUE : The transmission is successful.
//! - FALSE : in case of error.
//===========================================================================
static int CUMORE_Send_Financial_Record (TLV_TREE_NODE hInputTree)
{
	DataElement elt;
	unsigned short transfer_ok, found;
	TLV_TREE_NODE hTree,hTreeSR;
	unsigned char ISC_len;

	transfer_ok = 0;
	hTreeSR = NULL;
	hTree = TlvTree_New(0);

	if ((hTree != NULL) && (hInputTree != NULL))
	{
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AIP, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ATC, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_USAGE_CONTROL, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CRYPTOGRAM_INFORMATION_DATA, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CVM_LIST, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CVR_RESULT, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_IFD_SERIAL_NUMBER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_DEFAULT, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/

		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_DENIAL, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		} */

		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_ONLINE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_SCRIPT_RESULT_LIST_LEN, &elt);
		if (found)
		{
			ISC_len = elt.ptValue[0];
			// Bad storage of Issuer Script results
			if (ISC_len > 0)
			{
				/* elt.tag     = TAG_ISSUER_SCRIPT_RESULT_LIST_LEN;
				elt.length  = 1;
				elt.ptValue = &(batch_record.record.financial_record.new_data.ISC_len);*/
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);

				/* elt.tag     = TAG_ISSUER_SCRIPT_RESULT_LIST;
				elt.length  = batch_record.record.financial_record.new_data.ISC_len;
				elt.ptValue = batch_record.record.financial_record.new_data.ISC;*/
				found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_SCRIPT_RESULT_LIST, &elt);
				if (found)
				{
					elt.length = ISC_len;
					TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
				}
			}
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_CAPABILITIES, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_TYPE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TVR, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Add TSI to transaction file
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TSI, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_CRYPTOGRAMME_AC, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_UNPREDICTABLE_NUMBER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ACQUIRER_IDENTIFIER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/* elt.tag     = TAG_AMOUNT_AUTH_BIN;
		elt.length  = 4;
		LongToChar (batch_record.record.financial_record.exist_data.AmAuth, TabAmount);
		elt.ptValue = TabAmount; */
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_AUTH_BIN, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/* elt.tag     = TAG_AMOUNT_OTHER_BIN;
		elt.length  = 4;
		LongToChar (batch_record.record.financial_record.exist_data.AmOth, TabAmount1);
		elt.ptValue = TabAmount1;*/
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_OTHER_BIN, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_EFFECTIVE_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_EXPIRATION_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_PRIM_ACCOUNT_NB, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_PRIM_ACCOUNT_NB_SEQ_NB, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AUTHORISATION_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AUTHORISATION_RESPONSE_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_COUNTRY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_MERCHANT_CATEGORY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_POS_ENTRY_MODE_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Point of Service Entry Mode
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CUST_POS_ISO8583_93, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_COUNTRY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_IDENTIFICATION, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		} */
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_CURRENCY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_TIME, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_TYPE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Issuer Application Data 0x9F10
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_APPLICATION_DATA, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}

		// Amount, Authorised 0x9F02 (numeric)
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_AUTH_NUM, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Amount, Other 0x9F03 (numeric)
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_OTHER_NUM, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// AID : 4F
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AID_ICC, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}

		// Service Code : 5F30
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_SERVICE_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Sequence Counter : 9F41
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_SEQ_COUNTER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Track 2 : 57
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRACK2_EQU_DATA, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}

		// Transaction Currency Exponent : 5F36
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_CURRENCY_EXP, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Application Version Number : 9F09
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_VERSION_NUMBER_TERMINAL, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/*
		// Add Application Identifier : 9F06
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AID_TERMINAL, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}*/
		/*& END SMO/ETU/05/20028/MA */

		// TAG_TRANSACTION_FORCED_ACCEPTANCE is tested in Script CM.082
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_FORCED_ACCEPTANCE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* elt.tag     = TAG_COMM_MESSAGE_RETRANSMISSION;
		elt.length  = 1;
		elt.ptValue = &RetransmitIndicator;
		TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length); */
		/*& END SMO/ETU/05/20028/MA */

		// Add ICC dynamic number in batch file
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ICC_DYNAMIC_NUMBER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Mixed Communication with ISO8583 and SPDH
		// Send record
		hTree = EMVCUST_Build_transac_download_TLVTree(&hTree);

		hTreeSR = COMM_Send_And_Receive_Message_TlvTree(hTree);

		found = CUSERV_Extract_Element_TLV_Tree(&hTreeSR, TAG_COMM_STATUS_CODE, &elt);

		transfer_ok = (found && (*(elt.ptValue) == 0));

		// release local TLV tree
		TlvTree_ReleaseEx(&hTree);
		TlvTree_ReleaseEx(&hTreeSR);

	}

	return (transfer_ok);

}

//===========================================================================
//! \brief This function sends one advice record.
//! \param[in] hInputTree : Input TLV tree containing the advice transaction
//! read in the batch file.
//! \return
//! - TRUE : The transmission is successful.
//! - FALSE : in case of error.
//===========================================================================
static int CUMORE_Send_Advice_Record (TLV_TREE_NODE hInputTree)
{
	DataElement elt;
	unsigned short transfer_ok, found;
	TLV_TREE_NODE hTree,hTreeSR;
	unsigned char ISC_len;

	transfer_ok = 0;
	hTree = TlvTree_New(0);
	hTreeSR = NULL;

	if ((hTree != NULL) && (hInputTree != NULL))
	{
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AIP, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ATC, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_USAGE_CONTROL, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CRYPTOGRAM_INFORMATION_DATA, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CVM_LIST, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_CVR_RESULT, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_IFD_SERIAL_NUMBER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_DEFAULT, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/

		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_DENIAL, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/

		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_ACTION_CODE_ONLINE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_SCRIPT_RESULT_LIST_LEN, &elt);
		if (found)
		{
			ISC_len = elt.ptValue[0];
			// Bad storage of Issuer Script results
			if (ISC_len > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);

				found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_SCRIPT_RESULT_LIST, &elt);
				if (found)
				{
					elt.length = ISC_len;
					TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
				}
			}
		}

		/* if (batch_record.record.advice_record.adv_new_data.ISC_len > 0)
		{
			elt.tag     = TAG_ISSUER_SCRIPT_RESULT_LIST_LEN;
			elt.length  = 1;
			elt.ptValue = &(batch_record.record.advice_record.adv_new_data.ISC_len);
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);

			elt.tag     = TAG_ISSUER_SCRIPT_RESULT_LIST;
			elt.length  = batch_record.record.advice_record.adv_new_data.ISC_len;
			elt.ptValue = batch_record.record.advice_record.adv_new_data.ISC;
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		} */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_CAPABILITIES, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_TYPE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TVR, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_CRYPTOGRAMME_AC, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_UNPREDICTABLE_NUMBER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ACQUIRER_IDENTIFIER, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/* elt.tag     = TAG_AMOUNT_AUTH_BIN;
		elt.length  = 4;
		LongToChar (batch_record.record.advice_record.adv_exist_data.AmAuth, TabAmount);
		elt.ptValue = TabAmount; */
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_AUTH_BIN, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/* elt.tag     = TAG_AMOUNT_OTHER_BIN;
		elt.length  = 4;
		LongToChar (batch_record.record.advice_record.adv_exist_data.AmOth, TabAmount1);
		elt.ptValue = TabAmount1; */
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AMOUNT_OTHER_BIN, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_EFFECTIVE_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_EXPIRATION_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_PRIM_ACCOUNT_NB, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_APPLI_PRIM_ACCOUNT_NB_SEQ_NB, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_AUTHORISATION_RESPONSE_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_MERCHANT_CATEGORY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_POS_ENTRY_MODE_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_COUNTRY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TERMINAL_IDENTIFICATION, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_CURRENCY_CODE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_DATE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_TIME, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_TYPE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}

		// Issuer Application Data 0x9F10
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_ISSUER_APPLICATION_DATA, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}

		// Track 2 : 57
		found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRACK2_EQU_DATA, &elt);
		if (found)
		{
			if (elt.length > 0)
			{
				TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
			}
		}

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* found = CUSERV_Extract_Element_TLV_Tree(&hInputTree, TAG_TRANSACTION_FORCED_ACCEPTANCE, &elt);
		if (found)
		{
			TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);
		}*/
		/*& END SMO/ETU/05/20028/MA */

		/*& BEGIN SMO/ETU/05/20028/MA : Remove unused tags because DEL is too small ! */
		/* elt.tag = TAG_COMM_MESSAGE_RETRANSMISSION;
		elt.length  = 1;
		elt.ptValue = &RetransmitIndicator;
		TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length); */
		/*& END SMO/ETU/05/20028/MA */

		// Mixed Communication with ISO8583 and SPDH
		// Send record
		hTree = EMVCUST_Build_transac_advice_TLVTree(&hTree);

		hTreeSR = COMM_Send_And_Receive_Message_TlvTree(hTree);

		found = CUSERV_Extract_Element_TLV_Tree(&hTreeSR, TAG_COMM_STATUS_CODE, &elt);

		transfer_ok = (found && (*(elt.ptValue) == 0));

		// release local TLV tree
		TlvTree_ReleaseEx(&hTree);
		TlvTree_ReleaseEx(&hTreeSR);
	}

	return (transfer_ok);

}

//===========================================================================
//! \brief This function manages the printing of the transaction log of the ICC.
//===========================================================================
static void CUMORE_TransactionLog(void)
{
	unsigned short TransactionLogAsked;
	unsigned char    buf[11];
	TLV_TREE_NODE hInputTree;
	TLV_TREE_NODE hOutputTree;
	unsigned char TypeAppli[2];
	unsigned char EngAppliSel;

	// release global TLV tree
	TlvTree_ReleaseEx(&CUMORE_Tree);

	CUMORE_Tree = TlvTree_New(0);

	if(CUMORE_Tree != NULL)
	{
		TransactionLogAsked = TRUE;
		ShortToChar(TransactionLogAsked,buf);
		TlvTree_AddChild(CUMORE_Tree, TAG_CUST_TRLOG_IS_ASKED, (unsigned char *)buf, 2);
		hOutputTree = TlvTree_New(0);
		if(hOutputTree != NULL)
		{

			hInputTree = TlvTree_New(0);

			if(hInputTree != NULL)
			{
			ShortToChar(CustApplicationNumber,TypeAppli);
			TlvTree_AddChild(hInputTree, TAG_ENG_CUSTOM_APPLI_TYPE, (unsigned char*) &TypeAppli, 2);

			EngAppliSel =0;
			TlvTree_AddChild(hInputTree, TAG_ENG_APPLI_SEL_ALREADY_DONE, (unsigned char*) & EngAppliSel, 1);

			Engine_DoReadTransactionLog(hInputTree,&hOutputTree);

			// release local TLV tree
			TlvTree_ReleaseEx(&hOutputTree);
			}
		}
	}
}

//! @}

