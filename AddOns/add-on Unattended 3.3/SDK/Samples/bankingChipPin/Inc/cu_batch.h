/**
* \file cu_batch.h
* \brief This module contains the functions that manages the transaction record file.
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

#ifndef CU_BATCH_H
#define CU_BATCH_H

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "def_tag.h"

//! \defgroup Group_cu_batch Transaction file management. High level functions.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

// #define CUBATCH_DEF_LOG_SIZE        100		//!< Definition of batch log size.

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

//! \brief This enumerator defines the type of batch message.
typedef enum
{
	FINANCIAL_RECORD,						//!< Financial record batch message.
	ADVICE									//!< advice record batch message.
} T_CUBATCH_MESS_TYPE ;


//! \brief This structure defines new batch data capture elements as 
//! described in EMV96 Term, table III-9.
/* typedef struct
{
	unsigned char AIP[2];					//!< Application Interchange Profile
	unsigned char ATC[2];					//!< Application Transaction Pointer
	unsigned char AUC[2];					//!< Application Usage Control
	unsigned char CID;						//!< Cryptogram Information Data
	unsigned char CVM_list[252];			//!< Card Verification Method List
	unsigned char CVM_result[3];			//!< Card Verification Method Result
	unsigned char IDF_serial_number [8];	//!< IFD serial number
	unsigned char IAC_default[5];			//!< Issuer Action Code Default
	unsigned char IAC_denial[5];			//!< Issuer Action Code Denial
	unsigned char IAC_online[5];			//!< Issuer Action Code Online
	// char IAD;							//!< Issuer Application Data
	unsigned char ISC_len;					//!< Issuer Script Results length
	unsigned char ISC[50];					//!< Issuer Script Results
	unsigned char TCap[5];					//!< Terminal Capabilities
	unsigned char TType;					//!< Terminal Type
	unsigned char TVR[5];					//!< Terminal Verification Results
	unsigned char AC[8];					//!< TC or AAC
	unsigned char UN[4];					//!< Unpredictable Number
	unsigned char IAD_len;					//!< IAD length
	unsigned char IAD[32];					//!< Issuer Application Data
	unsigned char AAN[6];					//!< TAG_AMOUNT_AUTH_NUM
	unsigned char AON[6];					//!< TAG_AMOUNT_OTHER_NUM
	unsigned char ICC_len;					//!< ICC length
	unsigned char ICC[LEN_AID];				//!< TAG_AID_ICC
	unsigned char SC[2];					//!< TAG_SERVICE_CODE
	unsigned char TSC[LEN_TRANSACTION_SEQ_COUNTER];		//!< TAG_TRANSACTION_SEQ_COUNTER
	unsigned char TRACK2_len;				//!< TRACK 2 EQU Data length
	unsigned char TRACK2_data[19];			//!< TAG_TRACK2_EQU_DATA
	unsigned char TCE[1];					//!< TAG_TRANSACTION_CURRENCY_EXP
	unsigned char TCC[1];					//!< TAG_TRANSACTION_CATEGORY_CODE (EPI Proprietary Data)
	unsigned char VNT[2];					//!< TAG_VERSION_NUMBER_TERMINAL
	unsigned char AID_len;					//!< AID length
	unsigned char AID[LEN_AID];				//!< TAG_AID_TERMINAL
	unsigned char TFAind[1];				//!< Transaction Forced-Acceptance indicator
	unsigned char Pos_8583_93 [LEN_CUST_POS_ISO8583_93];
	unsigned char TSI[2];					//!< Terminal Status Information
	unsigned char ICC_DYNA[8];				//!< ICC dynamic number
} T_CUBATCH_new_data ;


//! \brief This structure defines existing batch data capture elements as 
//! described in EMV96 Term, table III-10.
typedef struct
{
	unsigned char Acq_Id[15];				//!< Acquirer Identifier
	unsigned long AmAuth;					//!< Amount Authorised (binary)
	unsigned long AmOth;					//!< Amount Other (binary)
	unsigned char AppEffDdate[4];			//!< Application Effective Date
	unsigned char AppExpate[4];				//!< Application Expiration Date
	unsigned char PAN[10];					//!< Application Primary Account Number
	unsigned char PAN_len;					//!< Primary Account Number length
	unsigned char PAN_Seq;					//!< Application PAN Sequence Number
	unsigned char Auth_Code[6];				//!< Authorisation Code
	unsigned char Auth_Resp_Code[2];		//!< Authorisation Response Code
	unsigned char Iss_Country[2];			//!< Issuer Country Code
	unsigned char MCC[2];					//!< Merchant Category Code
	unsigned char POS_Ent_Mode;				//!< POS Entry Mode
	unsigned char Term_Country[2];			//!< Terminal Country Code
	unsigned char Term_Id[8];				//!< Terminal Identifier
	unsigned long TransAmount;				//!< Transaction Amount (binary)
	unsigned char TransCurr[2];				//!< Transaction Currency Code
	unsigned char TransDate[3];				//!< Transaction Date
	unsigned char TransTime[3];				//!< Transaction Time
	unsigned char TransType;				//!< Transaction Type
} T_CUBATCH_exist_data ;
*/

//! \brief This structure defines batch data capture elements.
/* typedef struct
{
	unsigned long log_max_size;				//!< maximum log size
	unsigned long next_record_nb;			 
	unsigned long nb_record;
} T_CUBATCH_management_data ;
*/

//! \brief This structure defines a financial record.
/* typedef struct
{
	T_CUBATCH_new_data      new_data;		//!< new batch data capture elements.
	T_CUBATCH_exist_data    exist_data;		//!< existing batch data capture elements.
} T_CUBATCH__financial_record ;
*/

/* Structure of data for offline advices                                   */

//! \brief This structure defines new advice elements as 
//! described in EMV4.1, Book 4, 12.1.7.
/* typedef struct
{
	unsigned char AIP[2];					//!< Application Interchange Profile
	unsigned char ATC[2];					//!< Application Transaction Pointer
	unsigned char AUC[2];					//!< Application Usage Control
	unsigned char CID;						//!< Cryptogram Information Data
	unsigned char CVM_list[252];			//!< Card Verification Method List
	unsigned char CVM_result[3];			//!< Card Verification Method Result
	unsigned char IDF_serial_number [8];	//!< IFD serial number
	unsigned char IAD_len;					//!< IAD length
	unsigned char IAD[32];					//!< Issuer Application Data
	unsigned char ISC_len;					//!< Issuer Script Results length
	unsigned char ISC[25];					//!< Issuer Script Results
	unsigned char TCap[5];					//!< Terminal Capabilities
	unsigned char TType;					//!< Terminal Type
	unsigned char TVR[5];					//!< Terminal Verification Results
	unsigned char AC[8];					//!< TC or AAC
	unsigned char UN[4];					//!< Unpredictable Number


} T_CUBATCH_advice_new_data ;


//! \brief This structure defines existing advice elements as 
//! described in EMV4.1, Book 4, 12.1.7.
typedef struct
{
	unsigned char Acq_Id[15];				//!< Acquirer Identifier
	unsigned long AmAuth;					//!< Amount Authorised (binary)
	unsigned long AmOth;					//!< Amount Other (binary)
	unsigned char AppEffDdate[4];			//!< Application Effective Date
	unsigned char AppExpate[4];				//!< Application Expiration Date
	unsigned char PAN[10];					//!< Application Primary Account Number
	unsigned char PAN_len;					//!< Primary Account Number length
	unsigned char PAN_Seq;					//!< Application PAN Sequence Number
	unsigned char Auth_Resp_Code[2];		//!< Authorisation Response Code
	unsigned char MCC[2];					//!< Merchant Category Code
	unsigned char POS_Ent_Mode;				//!< POS Entry Mode
	unsigned char Term_Country[2];			//!< Terminal Country Code
	unsigned char Term_Id[8];				//!< Terminal Identifier
	unsigned char TRACK2_len;				//!< TRACK 2 EQU Data length
	unsigned char TRACK2_data[19];			//!< TAG_TRACK2_EQU_DATA
	unsigned long TransAmount;				//!< Transaction Amount (binary)
	unsigned char TransCurr[2];				//!< Transaction Currency Code
	unsigned char TransDate[3];				//!< Transaction Date
	unsigned char TransTime[3];				//!< Transaction Time
	unsigned char TransType;				//!< Transaction Type

} T_CUBATCH_advice_exist_data ;

//! \brief This structure defines an advice record.
typedef struct
{
	T_CUBATCH_advice_new_data      adv_new_data;		//!< New advice elements.
	T_CUBATCH_advice_exist_data    adv_exist_data;		//!< Existing advice elements.
} T_CUBATCH_advice_record ;
*/

//! \brief This union defines the type of batch record.
/* typedef union
{
	T_CUBATCH__financial_record	   financial_record;	//!< Financial record.
	T_CUBATCH_advice_record		   advice_record;		//!< Advice record.
} T_CUBATCH_struct ;

//! \brief This structure defines a batch record.
typedef struct
{
	T_CUBATCH_struct      record;						//!< Record (financial or advice).
	T_CUBATCH_MESS_TYPE Mess_Type;						//!< Message Type.
} T_CUBATCH_record ;
*/

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function erases the log file.
//===========================================================================
// extern void CUBATCH_DeleteLog(void);


//===========================================================================
//! \brief This function gives the content of the last record in the log, 
//! according with the given PAN.
//! \param[in] PAN : Primary Account Number seeked.
//! \param[out] phOutputTLVTree : TLV tree containing the last record with 
//! the same primary account number, if found.
//! \return 
//! - TRUE if found.
//! - FALSE otherwise.
//===========================================================================
extern T_Bool CUBATCHReadLastPANRecord (unsigned char PAN[10], TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function calculates the total amount of financial records stored
//! in the batch. It also gives the number of records in the batch.
//! \param[out] nb_record : number of records in the batch.
//! \param[out] total_amount : total amount in the batch, assuming that there is
//! only one currency.
//! \return 
//! - TRUE if statistics are valid.
//! - FALSE otherwise.
//===========================================================================
extern T_Bool CUBATCH_GiveStatistics (unsigned long *nb_record,
									  unsigned long *total_amount);

//===========================================================================
//! \brief This function gives the number of records contained in the batch file.
//! It has to be called at the beginning of the batch data capture.
//! \param[out] nb_record : number of records in the batch.
//! \return always TRUE.
//===========================================================================
T_Bool CUBATCH_InitialiseBatchTransfer (unsigned long *nb_record);

//===========================================================================
//! \brief This function gets the date of the next auto data batch capture.
//! \param[out] date_time : date of the next auto data batch capture.
//===========================================================================
void CUBATCH_GetNextTransfDate (DATE *date_time);

//===========================================================================
//! \brief This function sets the date of the next auto data batch capture.
//! \param[in] date_time : date of the next auto data batch capture.
//===========================================================================
void CUBATCH_SetNextTransfDate (DATE *date_time);

//===========================================================================
//! \brief This function checks the consistency of the transaction file. 
//! If the file data are valid the ram data are updated with the file content.
//! If the file is found corrupted, the function tries to restore it.
//===========================================================================
void CUBATCH_RestoreLog (void);

//===========================================================================
//! \brief This function adds one financial record in the batch file.
//! Data are read from EMVDC database.
//! \param[out] phOutputTLVTree : TLV tree containing the financial record build.
//===========================================================================
extern void CUBATCH_Create_Financial_Record (TLV_TREE_NODE *phOutputTLVTree);

//===========================================================================
//! \brief This function adds one advice record in the batch file. 
//! Data are read from EMVDC database.
//===========================================================================
extern void CUBATCH_Create_Advice_Record (void);

//===========================================================================
//! \brief This function adds one magstripe financial record in the batch file.
//! Data are read from EMVDC database, and from input TLV tree.
//! \param[in] pInputTLVTree : input TLV tree containing transaction tags to record.
//! \param[in] Record_POS_EM : POS Entry Mode. 
//! \li if set, the value stored in the record is read in data base.
//! \li if not set, the value stored in the record is hard coded.
//===========================================================================
extern void CUBATCH_Create_MAGFinancial_Record (TLV_TREE_NODE *pInputTLVTree, int Record_POS_EM);

//! @}

#endif
