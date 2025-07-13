/**
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
 */


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

static int ng_TransactionSuccesful = FALSE;
static int gs_nDeviceType = CLESS_SAMPLE_DEVICE_UNDETERMINED;						/*!< Indicates the type of device. */


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Extract the status code (TAG_KERNEL_STATUS_CODE) from a shared exchange buffer.
//! \param[in] pSharedStruct Shared exchange buffer from which the status code shall be extracted.
//! \return The exctracted status code.

int ClessSample_Common_GetStatusCode (T_SHARED_DATA_STRUCT * pSharedStruct)
{
	int nResult;
	int nStatusCode = -1;
	unsigned long ulTag, ulReadLength;
	const unsigned char * pReadValue;
	int nPosition;

	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	ulTag = TAG_KERNEL_STATUS_CODE;
	nResult = GTL_SharedExchange_FindNext (pSharedStruct, &nPosition, ulTag, &ulReadLength, &pReadValue);

	if (nResult == STATUS_SHARED_EXCHANGE_OK)  // If tag found
	{
		memcpy(&nStatusCode, pReadValue, ulReadLength); 
	}

	return (nStatusCode);
}

//! \brief Get a specific information in a shared buffer.
//! \param[out] pSpendingAmount pointer
//! \return
//!		- \ref TRUE if correctly retrieved.
//!		- \ref FALSE if an error occurred.

int ClessSample_Common_RetrieveInfo (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned long ulTag, unsigned char ** pInfo)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	if ((pResultDataStruct == NULL) || (ulTag == 0) || (pInfo == NULL))
	{
		GTL_Traces_TraceDebug("ClessSample_Common_RetrieveInfo : parameter error");
		nResult = FALSE;
		goto End;
	}

	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	*pInfo = NULL; // Default result : no information
	
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, ulTag, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("ClessSample_Common_RetrieveInfo : Unable to getinfo from the kernel response (tag=%02lx, cr=%02x)", ulTag, cr);
		nResult = FALSE;
		goto End;
	}
	
	// Get the transaction outcome
	*pInfo = (unsigned char *)pReadValue;
	
End:	
	return (nResult);
}


//! \brief Get a specific information in a TlvTree.
//! \param[in] pTlvTree Tree node.
//! \param[in] ulTag Tag to be found.
//! \param[out] pReadLength Read length in relation with tag asked.
//! \param[out] pReadValue Read value in relation with tag asked.
//! \return
//!		- \ref TRUE if correctly retrieved.
//!		- \ref FALSE if an error occurred.

int ClessSample_Common_GetTagInTlvTree (TLV_TREE_NODE pTlvTree, unsigned long ulTag, unsigned int *pReadLength, unsigned char ** pReadValue)
{
	TLV_TREE_NODE pTlvTmp; 		// Temporary Node

	if(pTlvTree == NULL)
		return (FALSE);

	pTlvTmp = TlvTree_Find(pTlvTree, ulTag, 0);
	if (pTlvTmp != NULL)
	{
		*pReadLength = TlvTree_GetLength(pTlvTmp);
		*pReadValue = TlvTree_GetData(pTlvTmp);
		
		return (TRUE);
	}

	return (FALSE);
}


//! \brief Allows to set transaction state : successfulled or not.
//! \param[in] : TRUE if transaction has been successfulled, FALSE else.
//! \return nothing
void ClessSample_Common_SetTransactionState (int n_Succesful)
{
	ng_TransactionSuccesful = n_Succesful;
}



//! \brief Allows to known is transaction has been successfulled.
//! \return
//!		- \ref TRUE if transaction has been successfulled.
//!		- \ref FALSE.
int ClessSample_Common_IsTransactionSuccesful (void)
{
	return (ng_TransactionSuccesful);
}

//! \brief Allows to manage transaction state and update output share buffer with data.
//! \param[in] pSharedStruct : share buffer to update
//! \return
//!		- \ref TRUE if transaction has been successfulled.
//!		- \ref FALSE.
void ClessSample_Common_ManageTransactionState (T_SHARED_DATA_STRUCT * pSharedStruct)
{
	// Allows to initialise output buffer with data used for cashbox.
	NO_PORTEUR no_porteur;
	NO_SEGMENT AppliNum;

	AppliNum = (NO_SEGMENT)ApplicationGetCurrent();
	memset(no_porteur, 0, sizeof(NO_PORTEUR));

	// If transaction has been succeffulled
	if (ClessSample_Common_IsTransactionSuccesful())
		ClessSample_Common_cr_caisse(pSharedStruct, PAY_OK, AppliNum, no_porteur);
	else
		ClessSample_Common_cr_caisse(pSharedStruct, PAY_KO, AppliNum, no_porteur);
}


//! \brief Allows to initialise output buffer with data used for cashbox.
//! \param[in] pIn : Share buffer to exchange.
//! \param[in] cr_cxce : result for cash register.
//! \param[in] no_appli : application number.
//! \param[in] no_porteur : cardholder number.
//! \return nothing
void ClessSample_Common_cr_caisse(T_SHARED_DATA_STRUCT *pIn, unsigned char cr_cxce, NO_SEGMENT no_appli, NO_PORTEUR no_porteur)
{
	// Clear de la struture
	GTL_SharedExchange_ClearEx (pIn, FALSE);
	GTL_SharedExchange_AddTag(pIn, TAG_GENERIC_MANAGER_STRANSOUT_NOAPPLI, 1, &no_appli);         // TAG_GENERIC_MANAGER_STRANSOUT_NOAPPLI       : 0x9F928244
	GTL_SharedExchange_AddTag(pIn, TAG_GENERIC_MANAGER_STRANSOUT_RC_PAYMENT, 1, &cr_cxce);       // TAG_GENERIC_MANAGER_STRANSOUT_RC_PAYMENT    : 0x9F928245
	GTL_SharedExchange_AddTag(pIn, TAG_GENERIC_MANAGER_STRANSOUT_CARDHOLDER_NB, 19, no_porteur); // TAG_GENERIC_MANAGER_STRANSOUT_CARDHOLDER_NB : 0x9F928246
}


//! \brief Format the message that contains the amount, the currency according to ucFormat, ucPosition...  
//! \param[in] ucFormat : the display format
//! \param[in] ucCurrency : transaction currency
//! \param[in] ucPosition : the position of the currency
//! \param[in] ulAmount : the transaction amount
//! \param[out] pFormattedAmountMessage : the formatted message to display

void ClessSample_Common_FormatAmount (unsigned char ucFormat, char *ucCurrency, unsigned char ucPosition, unsigned long ulAmount, char *pFormattedAmountMessage)
{
	char            currency[4];
	char            separator1[2];
	char            separator2[2];
	char            position;
	int             exponent;
	unsigned long   divider;
	unsigned long   i;
	char   amount_format[51];



	// Determine the separators and the exponent
	position=ucPosition;
	strcpy((char *)currency,(char *)ucCurrency);

	switch (ucFormat)
	{
	case 1 :
		strcpy(separator1,".");
		strcpy(separator2,",");
		exponent=2;
		break;
	
	case 2 :
		strcpy(separator1,",");
		strcpy(separator2," ");
		exponent=2;
		break;

	case 3 :
		strcpy(separator1," ");
		strcpy(separator2,".");
		exponent=0;
		break;

	case 4 :
		strcpy(separator1," ");
		strcpy(separator2,",");
		exponent=0;
		break;

	case 5 :
		strcpy(separator1," ");
		strcpy(separator2," ");
		exponent=0;
		break;

	case 6 :
		strcpy(separator1,",");
		strcpy(separator2,".");
		exponent=3;
		break;

	case 7 :
		strcpy(separator1,".");
		strcpy(separator2,",");
		exponent=3;
		break;

	case 8 :
		strcpy(separator1,",");
		strcpy(separator2," ");
		exponent=3;
		break;

	case 0 :
	default :
		strcpy(separator1,",");
		strcpy(separator2,".");
		exponent=2;
		break;
	}

	// Format the amount
	switch(exponent)
	{
	case 1 :
		for (divider=1L,i=0L;i<(unsigned)exponent;divider*=10L,i++);

		if ((ulAmount/divider)<1000L)
		{
			sprintf(amount_format,"%lu%s%0*lu", (ulAmount/divider), separator2, exponent, (ulAmount%divider));
		}
		else
		{
			if ((ulAmount/divider)<1000000L)
			{
				sprintf(amount_format,"%lu%s%03lu%s%0*lu", ((ulAmount/divider)/1000L), separator1, ((ulAmount/divider)%1000L), separator2, exponent, (ulAmount%divider));
			}
			else
			{
				sprintf(amount_format,"%lu%s%03lu%s%03lu%s%0*lu", ((ulAmount/divider)/1000000L), separator1, (((ulAmount/divider)/1000L)%1000L), separator1, ((ulAmount/divider)%1000L), separator2, exponent, (ulAmount%divider));
			}
		}
		break;  
	case 2 :
	case 3 :
	case 4 :
	case 5 :
	case 6 :
	case 7 :
		for (divider=1L,i=0L;i<(unsigned)exponent;divider*=10L,i++);

		if ((ulAmount/divider)<1000L)
		{
			sprintf(amount_format,"%lu%s%0*lu", (ulAmount/divider), separator2, exponent, (ulAmount%divider));
		}
		else
		{
			sprintf(amount_format,"%lu%s%03lu%s%0*lu", ((ulAmount/divider)/1000L), separator1, ((ulAmount/divider)%1000L), separator2, exponent, (ulAmount%divider));
		}
		break;  
	case 0 :
	default :
		if ((ulAmount)<1000L)
		{
			sprintf(amount_format,"%lu",(ulAmount));
		}
		else
		{
			if ((ulAmount)<1000000L)
			{
				sprintf(amount_format,"%lu%s%03lu",((ulAmount)/1000L),separator1,((ulAmount)%1000L));
			}
			else
			{
				sprintf(amount_format,"%lu%s%03lu%s%03lu",((ulAmount)/1000000L),separator1,(((ulAmount)/1000L)%1000L),separator1,((ulAmount)%1000L));
			}
		}
		break;
	}

	if (position == 0)
	{
		sprintf(pFormattedAmountMessage,"%s %s", amount_format, currency);
	}
	else
	{
		sprintf(pFormattedAmountMessage,"%s %s", currency, amount_format);
	}
}



//! \brief Requests amount entry, prepare frame for Entry Point (fill shared memory)
//! \param[in] bEnterAmountOther \a TRUE if amount other shall be enetered (change the label).
//! \param[in] pCurrencyLabel : the currency label
//! \param[out] pAmountBin : the entered transaction amount
//! \return 
//!		- TRUE if amount has been entered.
//!		- FALSE if amount entry has been cancelled.

int ClessSample_Common_AmountEntry (const int bEnterAmountOther, const unsigned char *pCurrencyLabel, unsigned long * pAmountBin)
{
	TAB_ENTRY_FCT TabEntry;
	unsigned long ulAmount;
	int nResult;
	unsigned char ucFormat, ucPosition;
	unsigned char CurrencyLabel[4];
	

	// Init amount entry structure
	TabEntry.mask = 0;
	TabEntry.time_out = 60;
	*pAmountBin = 0;
	memset (CurrencyLabel, 0, sizeof(CurrencyLabel));

	///////////////////////////////////////////////////
	//unsigned char  ucFormat: format of the displayed amount                         
	//                         0 ==> 1.000,00                                   
	//                         1 ==> 1,000.00                                   
	//                         2 ==> 1 000,00                                   
	//                         3 ==> 1.000                                      
	//                         4 ==> 1,000                                      
	//                         5 ==> 1 000                                      
	//                         6 ==> 1.000,000                                  
	//                         7 ==> 1,000.000                                  
	//                         8 ==> 1 000,000                                  
	//unsigned char ucPosition: position of the currency     
	//                         0 ==> after the amount                        
	//                         1 ==> before the amount 
	////////////////////////////////////////////////////
	
	ucFormat = 0;
	ucPosition = 0;
	memcpy (CurrencyLabel, pCurrencyLabel, 3);

	// Get transaction amount
	if (!bEnterAmountOther)
		nResult = GetAmount(ucFormat, CurrencyLabel, ucPosition, &ulAmount, (unsigned char*)"Amount", &TabEntry);
	else
		nResult = GetAmount(ucFormat, CurrencyLabel, ucPosition, &ulAmount, (unsigned char*)"Amount Other", &TabEntry);

	// If amount is validated
	if (nResult == T_VAL)
	{
		/// Format the message that contains the amount, the currency according to ucFormat, ucPosition...  
		///ClessSample_Common_FormatAmount(ucFormat,CurrencyLabel,ucPosition,ulAmount,pFormattedAmountMessage);
		
		// Return the transaction amount
		*pAmountBin = ulAmount;
	}

	// Return amount entry result
	return (nResult == T_VAL);
}


//! \brief Calculate the day number in the year, based on the date.
//! \param[in] date Date.
//! \return The day number in the year.

static int __ClessSample_Common_DayOfYear (DATE *date)
{
	unsigned long year;
	unsigned long month;
	unsigned long day;
	unsigned int i;
	int leap_year;

	const unsigned char day_per_month[2][13] = {
		{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};

	Ascbin (&year, date->year, 2);
	Ascbin (&month, date->month, 2);
	Ascbin (&day, date->day, 2);

	// Determine if it is a leap year or not
	leap_year = (year % 4) == 0;

	// Calculate the days
	for (i=1; i<month; i++)
		day = day + day_per_month[leap_year][i];

	return (day);
}



//! \brief This function returns the number of days bewteen two dates.
//! \param[in] date1 First date
//! \param[in] date2 Second date
//! \returns the number of days between date1 and date2.
//! \note No date check is done, so the provided dates shall be valid !

int ClessSample_Common_NumberOfDaysBetweenTwoDates (DATE *date1, DATE *date2)
{
	int  day1, day2;
	unsigned long  year1, year2, year;
	DATE temp;
	int result;

	// Prepare temporary data set to 31/12, allowing to calculate the number of days or a given year
	Binasc(temp.day, 31, 2);
	Binasc(temp.month, 12, 2);

	// Calculate the delta in days
	day1 = __ClessSample_Common_DayOfYear(date1);
	day2 = __ClessSample_Common_DayOfYear(date2);
	result = day2 - day1;

	// Add the delat in years, if necessary
	Ascbin (&year1, date1->year, 2);
	Ascbin (&year2, date2->year, 2);

	// Management of year 2000
	if (year1 <= 50)
		year1 = year1 + 2000;
	else
		year1 = year1 + 1900;
	if (year2 <= 50)
		year2 = year2 + 2000;
	else
		year2 = year2 + 1900;

	// Determine the most recent year to determine the loop
	if (year2  <= year1 )
	{
		for (year=year2; year<year1; year++)
		{
			Binasc(temp.year, year % 100, 2);
			result = result - __ClessSample_Common_DayOfYear(&temp); // Negative delta
		}
	}
	else
	{
		for (year=year1; year<year2; year++)
		{
			Binasc(temp.year, year % 100, 2);
			result = result + __ClessSample_Common_DayOfYear(&temp); // Positive delta
		}
	}

	return (result);
}


//! \brief Determine the type of terminal.
//! \return The type of terminal.
int ClessSample_Common_GetTerminalType (void)
{
	// Device type already determined
	if (gs_nDeviceType == CLESS_SAMPLE_DEVICE_UNDETERMINED)
	{
		// Device type not yet determined, so, do it
		if (IsICT220())
			gs_nDeviceType = TERM_ICT220;
		else if (IsICT250())
			gs_nDeviceType = TERM_ICT250;
		else if (IsISC350())
			gs_nDeviceType = TERM_ISC350;
		else if (IsISC250())
			gs_nDeviceType = TERM_ISC250;
		else if (IsIWL220())
			gs_nDeviceType = TERM_IWL220;
		else if (IsIWL250())
			gs_nDeviceType = TERM_IWL250;
		else if (IsIWL280())
			gs_nDeviceType = TERM_IWL280;
		else if (IsIPP320())
			gs_nDeviceType = TERM_IPP320;
		else if (IsIPP350())
			gs_nDeviceType = TERM_IPP350;
		else if (IsIMP350())
			gs_nDeviceType = TERM_IMP350;
		else if (IsIMP3xxCompanion())
			gs_nDeviceType = TERM_IMP320;
		else if (IsML30())
			gs_nDeviceType = TERM_P300;
		else if (IsEFT30())
			gs_nDeviceType = TERM_EFT930; //TERM_EFT930BT, TERM_EFT930G, TERM_EFT930SGEM, TERM_EFT930W, TERM_EFT930S
		else if (IsSPM())
			gs_nDeviceType = TERM_SPM;
		else if (IsIWL350())
			gs_nDeviceType = TERM_IWL350;
		else if (IsISC480())
			gs_nDeviceType = TERM_ISC480;
		else if (IsIPP480())
			gs_nDeviceType = TERM_IPP480;
		else if (IsIUC150())
			gs_nDeviceType = TERM_IUN150;
		else if (IsIUC180() || IsIUC180B())
			gs_nDeviceType = TERM_IUN180;
		else if (IsIST150())
			gs_nDeviceType = TERM_IST150;
		else if (IsIUP250())
			gs_nDeviceType = TERM_IUN230;
		else if (IsIWB220())
			gs_nDeviceType = TERM_IWB220;
		else if (IsIWB250())
			gs_nDeviceType = TERM_IWB250;
		else if (GetTerminalType() == TYPE_TERMINAL_MR40)
			gs_nDeviceType = TERM_MR40;
		else
			gs_nDeviceType = CLESS_SAMPLE_DEVICE_UNKNOWN;
	}

	return (gs_nDeviceType);
}


