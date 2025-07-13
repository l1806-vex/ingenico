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
#include "ClessSample_Logos.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Define the transaction card provider type //////////////////


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static void __ClessSample_Receipt_FormatAmount(unsigned long ulAmount, int bNegative, int nCurrencyExponent, int nWidth, char* pString);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Format the amount for printing purpose.
//! \param[in] ulAmount Amount to be formatted.
//! \param[in] bNegative Indicates if a minus character shall be displayed or not. 
//! \param[in] nCurrencyExponent Currency exponent (for decimal separator location).
//! \param[in] nWidth 
//! \param[out] pString Formatted string for receipt printing.

static void __ClessSample_Receipt_FormatAmount(unsigned long ulAmount, int bNegative, int nCurrencyExponent, int nWidth, char* pString)
{
	char Amount[10 + 1];
	char String[20];
	int nSrcIndex;
	int nDestIndex;
	int bDigitDetected;
	char* pPtr;

	sprintf(Amount, "%010lu", ulAmount);

	bDigitDetected = FALSE;
	nDestIndex = 0;

	memset(String, 0, sizeof(String));

	for(nSrcIndex = 0; nSrcIndex < 10; nSrcIndex++)
	{
		if (!bDigitDetected)
		{
			if (Amount[nSrcIndex] != '0')
				bDigitDetected = TRUE;
			else if (nSrcIndex == 10 - 1 - nCurrencyExponent)
				bDigitDetected = TRUE;
		}

		if (bDigitDetected)
		{
			String[nDestIndex++] = Amount[nSrcIndex];

			if (nSrcIndex < 10 - 1 - nCurrencyExponent)
			{
				if (((10 - 1 - nCurrencyExponent - nSrcIndex) % 3) == 0)
					String[nDestIndex++] = ' ';
			}
			else if (nSrcIndex == 10 - 1 - nCurrencyExponent)
			{
				// If exponent = 0, do not print a decimal separator
				if (nCurrencyExponent != 0)
					String[nDestIndex++] = '.';
			}
		}
	}

	String[nDestIndex] = '\0';

	nDestIndex = strlen(String);
	if (bNegative)
		nDestIndex++;

	pPtr = pString;
	while(nDestIndex < nWidth)
	{
		*(pPtr++) = ' ';
		nDestIndex++;
	}

	if (bNegative)
		*(pPtr++) = '-';

	strcpy(pPtr, String);
}

void ClessSampleFormatSpendingAmount(const unsigned char * pAvailableOfflineSpendingAmount, unsigned int nLengthSpendingAmount, char * szSpendingAmount)
{
    char str[13];
    char * ptr;
    int index;
    int nLgStr;
    
	if (szSpendingAmount == NULL)
		return;
	
	if ((pAvailableOfflineSpendingAmount == NULL) || (nLengthSpendingAmount == 0))
	{
		*szSpendingAmount = 0; // String end...
		return;
	}
	
    ptr = str; 
    GTL_Convert_DcbNumberToAscii((const unsigned char*)pAvailableOfflineSpendingAmount, ptr, nLengthSpendingAmount, 12);

    index = 0;
    while ((ptr[index] == '0') && (index < 10))
    	index++;
    ptr+=index;
    	
    nLgStr = strlen(ptr);
    strcpy (szSpendingAmount, ClessSample_Fill_GiveMoneyLabel());
    if (nLgStr > 2)
    {
	    strcat ((char*)szSpendingAmount, " ");
	    strncat ((char*)szSpendingAmount, ptr, nLgStr - 2);
	    szSpendingAmount[strlen(ClessSample_Fill_GiveMoneyLabel()) + nLgStr-1] = 0;
	    strcat ((char*)szSpendingAmount, ",");
	    strncat ((char*)szSpendingAmount, &ptr[nLgStr-2], 2);
	}
	else
	{
	    strcat ((char*)szSpendingAmount, " 0,");
	    strcat ((char*)szSpendingAmount, ptr);
    }
}



//! \brief Prints the receipt for C2 kernel transactions.
//! \param[in] pTransaction Structure containing the data returned by the C2 kernel.
//! \param[in] bMobileTransaction Indicates if the transaction has bee performed with a mobile or not.
//! \param[in] nRequiredCvm Indicates the required CVM.
//! \param[in] nCardHolderLang Indicates the cardholder language.

void ClessSample_Receipt_PrintPayPass (T_SHARED_DATA_STRUCT * pTransaction, const int bMobileTransaction, const int nRequiredCvm, int nCardHolderLang)
{
	int nResult, nPosition;
	unsigned long ulTag;
	unsigned long ulReadLength;
	const unsigned char * pValue;
	const unsigned char* pValueAid;
	unsigned int LengthAid;
	const unsigned char* pValueTvr;
	const unsigned char* pValueAmountNum;
	const unsigned char* pValueAmountOtherNum;
	const unsigned char* pValueExpirationDate;
	const unsigned char* pValuePan;
	unsigned int LengthPan;
	const unsigned char* pValuePanSeq;
	const unsigned char* pValueCurrencyCode;
	const unsigned char* pValueCurrencyExp;
	const unsigned char* pValueDate;
	const unsigned char* pValueType;
	const unsigned char* pValueCardType;
	const unsigned char* pValueApplicationLabel;
	unsigned int length_application_label;
	const unsigned char* pValueAppliPreferedName;
	unsigned int length_appli_prefered_name;

	unsigned char Aid[20];
	unsigned char Tvr[5];
	unsigned long ulAmount;
	unsigned long ulAmountOther;
	char ExpirationDate[6 + 1];
	char Pan[19 + 1];
	unsigned long ulPanSeq;
	unsigned long ulCurrencyCode;
	unsigned long ulCurrencyExp;
	char Date[6 + 1];
	unsigned long ulType;
	char szAmount[20];
	unsigned short usCardType;
	unsigned char ApplicationLabel [16 + 1]; // Application label + '\0'
	unsigned char AppliPreferedName [16 + 1]; // Application prefered name + '\0'
	int temp;
	MSGinfos tDisplayMsg;
	

	// Open output device
	if (!ClessSample_DumpData_DumpOpenOutputDriver())
		return;

	pValueAid = NULL;
	LengthAid = 0;
	pValueTvr = NULL;
	pValueAmountNum = NULL;
	pValueAmountOtherNum = NULL;
	pValueExpirationDate = NULL;
	pValuePan = NULL;
	LengthPan = 0;
	pValuePanSeq = NULL;
	pValueCurrencyCode = NULL;
	pValueCurrencyExp = NULL;
	pValueDate = NULL;
	pValueType = NULL;
	pValueCardType = NULL;
	usCardType = 0;
	pValueApplicationLabel = NULL;
	length_application_label = 0;
	pValueAppliPreferedName = NULL;
	length_appli_prefered_name = 0;

	defprinterpatternHR (0, 0, 0xF1, (char *) Line_part_1);
	defprinterpatternHR (0, 0, 0xF2, (char *) Line_part_2);
	defprinterpatternHR (0, 0, 0xF9, (char *) Signature_part_1);
	defprinterpatternHR (0, 0, 0xFA, (char *) Signature_part_2);
	defprinterpatternHR (0, 0, 0xE8, (char *) MasterCardPayPass_Part1);
	defprinterpatternHR (0, 0, 0xE9, (char *) MasterCardPayPass_Part2);

	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	
	do{
    	// Try to following tag.
    	nResult = GTL_SharedExchange_GetNext (pTransaction, &nPosition, &ulTag, &ulReadLength, &pValue);

        if (nResult == STATUS_SHARED_EXCHANGE_OK)  // If tag found
        {
			switch(ulTag)
			{
    		case TAG_EMV_DF_NAME:							pValueAid = pValue;	LengthAid = ulReadLength; break;
    		case TAG_EMV_TVR:								pValueTvr = pValue; break;
    		case TAG_EMV_AMOUNT_AUTH_NUM:					pValueAmountNum = pValue; break;
    		case TAG_EMV_AMOUNT_OTHER_NUM:					pValueAmountOtherNum = pValue; break;
    		case TAG_EMV_APPLI_EXPIRATION_DATE:				pValueExpirationDate = pValue; break;
    		case TAG_EMV_APPLI_PAN:							pValuePan = pValue;	LengthPan = ulReadLength; break;
    		case TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER:			pValuePanSeq = pValue; break;
    		case TAG_EMV_TRANSACTION_CURRENCY_CODE:			pValueCurrencyCode = pValue; break;
    		case TAG_EMV_TRANSACTION_CURRENCY_EXPONENT:		pValueCurrencyExp = pValue; break;
    		case TAG_EMV_TRANSACTION_DATE:					pValueDate = pValue; break;
    		case TAG_EMV_TRANSACTION_TYPE:					pValueType = pValue; break;
    		case TAG_KERNEL_CARD_TYPE:						pValueCardType=pValue; break;
    		case TAG_EMV_APPLICATION_LABEL:					pValueApplicationLabel=pValue; length_application_label = ulReadLength; break;
    		case TAG_EMV_APPLI_PREFERED_NAME:				pValueAppliPreferedName=pValue; length_appli_prefered_name = ulReadLength; break;
			default:
				break;
			}
        }
        else if (nResult != STATUS_SHARED_EXCHANGE_END)  // Error
        {
        	GTL_Traces_TraceDebug("Display tags error:%x\n", nResult);
        }
    }while (nResult == STATUS_SHARED_EXCHANGE_OK);


	memset(Aid, 0, sizeof(Aid));
	memset(Tvr, 0, sizeof(Tvr));
	ulAmount = 0;
	ulAmountOther = 0;
	memset(ExpirationDate, '?', sizeof(ExpirationDate));
	memset(Pan, '?', sizeof(Pan));
	ulPanSeq = 0;
	ulCurrencyCode = 0;
	ulCurrencyExp = 0;
	memset(Date, '?', sizeof(Date));
	ulType = 0;
	memset (ApplicationLabel, '\0', sizeof(ApplicationLabel));
	memset (AppliPreferedName, '\0', sizeof(AppliPreferedName));

	if (pValueAid != NULL)
		memcpy(Aid, pValueAid, LengthAid);
	if (pValueTvr != NULL)
		memcpy(Tvr, pValueTvr, sizeof(Tvr));
	if (pValueAmountNum != NULL)
		GTL_Convert_DcbNumberToUl(pValueAmountNum, &ulAmount, 6);
	if (pValueAmountOtherNum != NULL)
		GTL_Convert_DcbNumberToUl(pValueAmountOtherNum, &ulAmountOther, 6);
	if (pValueExpirationDate != NULL)
		GTL_Convert_DcbNumberToAscii(pValueExpirationDate, ExpirationDate, 3, 6);
	if (pValuePan != NULL)
		GTL_Convert_DcbPaddedToAscii(pValuePan, Pan, LengthPan);
	if (pValuePanSeq != NULL)
		GTL_Convert_DcbNumberToUl(pValuePanSeq, &ulPanSeq, 1);
	if (pValueCurrencyCode != NULL)
		GTL_Convert_DcbNumberToUl(pValueCurrencyCode, &ulCurrencyCode, 2);
	if (pValueCurrencyExp != NULL)
		GTL_Convert_DcbNumberToUl(pValueCurrencyExp, &ulCurrencyExp, 1);
	if (pValueDate != NULL)
		GTL_Convert_DcbNumberToAscii(pValueDate, Date, 3, 6);
	if (pValueType != NULL)
		ulType = pValueType[0];
	if (pValueCardType != NULL)
		usCardType = (pValueCardType[0] << 8) + pValueCardType[1];
	if (pValueApplicationLabel != NULL)
		memcpy (ApplicationLabel, pValueApplicationLabel, length_application_label);
	if (pValueAppliPreferedName != NULL)
		memcpy (AppliPreferedName, pValueAppliPreferedName, length_appli_prefered_name);

	// Print the receipt
	__ClessSample_Receipt_FormatAmount(ulAmount, FALSE, ulCurrencyExp, 0, szAmount);

	// Format the PAN
	{
		int nLen;

		nLen = strlen(Pan);
		if (nLen)
		{
			Pan[nLen - 1] = '-';
			if (nLen > 6)
				memset(Pan, '-', 6);
			else
				memset(Pan, '-', nLen-1);
		}
	}

	// Print the logo
	if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER) // Bitmaps only works with a printer
	{
		ClessSample_DumpData("\xE8\xE9");
	}
	else
	{
		ClessSample_DumpData(" ####            #### ");ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData(" #   #           #   #");ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData(" ####  ### #   # ####  ###   ###  ###");ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData(" #    #  #  # #  #    #  #  #### ####");ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData(" #     ####  #   #     #### ###  ###");ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData("            #");ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData("           #");ClessSample_DumpData_DumpNewLine();
	}
			
	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();

	// Print separator line
	ClessSample_DumpData_DumpNewLine();
	if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER) // Bitmaps only works with a printer
		ClessSample_DumpData ("\xF1\xF2");
	else
		ClessSample_DumpData ("-------------------------");
	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();

	// Print receipt depending on the action
	ClessSample_DumpData ("\x1b" "@\x1b" "E");

	// Display the application label if available
	if (pValueApplicationLabel != NULL)
	{
		for (temp=0;temp<(unsigned char)length_application_label;temp++)
		{
			if (!(((ApplicationLabel[temp] >= 0x30) && (ApplicationLabel[temp] <= 0x39))
				|| ((ApplicationLabel[temp] >= 0x41) && (ApplicationLabel[temp] <= 0x5A))
				|| ((ApplicationLabel[temp] >= 0x61) && (ApplicationLabel[temp] <= 0x7A))))
			{
				ApplicationLabel[temp] = 0x20;
			}
		}

		ClessSample_DumpData("\x1b" "@");
		ClessSample_DumpData("%s", ApplicationLabel);
		ClessSample_DumpData_DumpNewLine();
	}

	// Display the application preferred name if available
	if (pValueAppliPreferedName != NULL)
	{
		for (temp=0;temp<(unsigned char)length_appli_prefered_name;temp++)
		{
			if (!(((AppliPreferedName[temp] >= 0x30) && (AppliPreferedName[temp] <= 0x39))
				|| ((AppliPreferedName[temp] >= 0x41) && (AppliPreferedName[temp] <= 0x5A))
				|| ((AppliPreferedName[temp] >= 0x61) && (AppliPreferedName[temp] <= 0x7A))))
			{
				AppliPreferedName[temp] = 0x20;
			}
		}

		ClessSample_DumpData("\x1b" "@");
		ClessSample_DumpData("%s", AppliPreferedName);
		ClessSample_DumpData_DumpNewLine();
	}

	ClessSample_DumpData_DumpNewLine();

	ClessSample_DumpData("\x1b" "@\x1b" "E");

	if (ulType == CLESS_SAMPLE_TRANSACTION_TYPE_DEBIT)
	{
		ClessSample_Term_Read_Message(STD_MESS_DEBIT, nCardHolderLang, &tDisplayMsg);
		ClessSample_DumpData(tDisplayMsg.message);
	}
	else if (ulType == CLESS_SAMPLE_TRANSACTION_TYPE_REFUND)
	{
		ClessSample_Term_Read_Message(STD_MESS_REFUND, nCardHolderLang, &tDisplayMsg);
		ClessSample_DumpData(tDisplayMsg.message);
	}
	else
	{
		ClessSample_Term_Read_Message(STD_MESS_TRANSAC_TYPE, nCardHolderLang, &tDisplayMsg);
		ClessSample_DumpData("%s %lX", tDisplayMsg.message, ulType);
	}

	ClessSample_DumpData_DumpNewLine();
	ClessSample_Term_Read_Message(STD_MESS_APPROVED_TICKET, nCardHolderLang, &tDisplayMsg);
	ClessSample_DumpData (tDisplayMsg.message);
	ClessSample_DumpData ("\x1b" "@");

	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();

	ClessSample_DumpData ("%c%c/%c%c/%c%c", Date[4], Date[5], Date[2], Date[3], Date[0], Date[1]);
	ClessSample_DumpData_DumpNewLine();

	// If the PAN is present, print it (with hidden parts)
	if (pValuePan != NULL)
	{
		ClessSample_DumpData ("%s", Pan);
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
	}
		
	ClessSample_Term_Read_Message(STD_MESS_AMOUNT, nCardHolderLang, &tDisplayMsg);
	ClessSample_DumpData (tDisplayMsg.message);
		
	if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
		ClessSample_DumpData ("\x1b" "E");

	ClessSample_DumpData ("%s %s", ClessSample_Fill_GiveMoneyLabel(), szAmount);
	ClessSample_DumpData ("\x1b" "@");
	ClessSample_DumpData_DumpNewLine();

	// Check if signature is required
	if (nRequiredCvm == PAYPASS_OPS_CVM_SIGNATURE)
	{
		ClessSample_DumpData_DumpNewLine();

		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER) // Bitmaps only works with a printer
		{
			ClessSample_DumpData ("\xF9\xFA");
			ClessSample_DumpData_DumpNewLine();
		}
		else
		{
			ClessSample_DumpData (" *** Signature ******************* ");ClessSample_DumpData_DumpNewLine();
			ClessSample_DumpData ("*                                 *");ClessSample_DumpData_DumpNewLine();
			ClessSample_DumpData ("*                                 *");ClessSample_DumpData_DumpNewLine();
			ClessSample_DumpData ("*                                 *");ClessSample_DumpData_DumpNewLine();
			ClessSample_DumpData (" ********************************* ");ClessSample_DumpData_DumpNewLine();
		}
	}

	ClessSample_DumpData_DumpNewLine();

	if (bMobileTransaction)
	{
		ClessSample_Term_Read_Message(STD_MESS_RECEIPT_TXN_WITH_MOBILE, nCardHolderLang, &tDisplayMsg);
		ClessSample_DumpData (tDisplayMsg.message);

		ClessSample_DumpData("\x0F");

		if (nRequiredCvm == PAYPASS_OPS_CVM_CONFIRMATION_CODE_VERIFIED)
			ClessSample_Term_Read_Message(STD_MESS_RECEIPT_PIN_VERIFIED, nCardHolderLang, &tDisplayMsg);
		else
			ClessSample_Term_Read_Message(STD_MESS_RECEIPT_NO_CARDHOLDER_VERIFICATION, nCardHolderLang, &tDisplayMsg);

		ClessSample_DumpData (tDisplayMsg.message);

		ClessSample_DumpData("\x1b" "@");
	}
	else
	{
		ClessSample_Term_Read_Message(STD_MESS_RECEIPT_TXN_WITH_CARD, nCardHolderLang, &tDisplayMsg);
		ClessSample_DumpData (tDisplayMsg.message);
	}


	// Print separator line
	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();
	if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER) // Bitmaps only works with a printer
		ClessSample_DumpData ("\xF1\xF2");
	else
		ClessSample_DumpData ("-------------------------");
	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();

	ClessSample_DumpData("  Let's keep in touch !");

	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();

	if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER) // Different presentation if on a printer or in text mode
	{
		ClessSample_DumpData("       INGENICO");
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData("\x0F");
		ClessSample_DumpData("      190-192, avenue Charles de Gaulle");
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData("\x0F");
		ClessSample_DumpData("       92000 Neuilly-sur-Seine - FRANCE");
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData("\x0F");
		ClessSample_DumpData("Tel:+33 146 25 82 00        Fax:+33 147 72 56 95");
		ClessSample_DumpData("\x1b" "@");
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData ("\xF1\xF2");
	}
	else
	{
		ClessSample_DumpData("       INGENICO");ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData("190-192, avenue Charles de Gaulle");ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData(" 92000 Neuilly-sur-Seine");ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData("   Tel:+33 146 25 82 00");ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData("   Fax:+33 147 72 56 95");ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData("---------------------------");
		ttestall (0,5);
	}

	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();
	ClessSample_DumpData_DumpNewLine();

	ClessSample_DumpData_DumpCloseOutputDriver();
}
