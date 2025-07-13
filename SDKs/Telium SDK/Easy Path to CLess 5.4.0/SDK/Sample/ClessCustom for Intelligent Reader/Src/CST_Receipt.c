/**
 * \file	CST_Receipt.c
 * \brief	Manages the receipt printing.
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
 */

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "CST_Implementation.h"
#include "CST_Logos.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Define the transaction card provider type //////////////////


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static void __CST_Receipt_FormatAmount(unsigned long ulAmount, int bNegative, int nCurrencyExponent, int nWidth, char* pString);
static void __CST_Receipt_GetSelectedPreferedLanguage (void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Format the amount for printing purpose.
//! \param[in] ulAmount Amount to be formatted.
//! \param[in] bNegative Indicates if a minus character shall be displayed or not. 
//! \param[in] nCurrencyExponent Currency exponent (for decimal separator location).
//! \param[in] nWidth 
//! \param[out] pString Formatted string for receipt printing.

static void __CST_Receipt_FormatAmount(unsigned long ulAmount, int bNegative, int nCurrencyExponent, int nWidth, char* pString)
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


//! \brief Format the spending amount for printer or display.
//! \param[in] pAvailableOfflineSpendingAmount in DCB format.
//! \param[in] nLengthSpendingAmount data length.
//! \param[in/out] buffer updated with amount formated.
//! \return
//! 	nothing.

void CST_FormatSpendingAmount(const unsigned char * pAvailableOfflineSpendingAmount, unsigned int nLengthSpendingAmount, char * szSpendingAmount)
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
    strcpy (szSpendingAmount, CST_Term_GiveMoneyLabel());
    if (nLgStr > 2)
    {
	    strcat ((char*)szSpendingAmount, " ");
	    strncat ((char*)szSpendingAmount, ptr, nLgStr - 2);
	    szSpendingAmount[strlen(CST_Term_GiveMoneyLabel()) + nLgStr-1] = 0;
	    strcat ((char*)szSpendingAmount, ",");
	    strncat ((char*)szSpendingAmount, &ptr[nLgStr-2], 2);
	}
	else
	{
	    strcat ((char*)szSpendingAmount, " 0,");
	    strcat ((char*)szSpendingAmount, ptr);
    }
}


//! \brief Create a shared buffer, and requests the selected language to the kernel that performed the transaction.

static void __CST_Receipt_GetSelectedPreferedLanguage (void)
{
	int cr = SDI_STATUS_UNKNOWN;
	TLV_TREE_NODE hTlvTreeIn;
	TLV_TREE_NODE hTlvTreeOut = NULL;
	T_SHARED_DATA_STRUCT * pDataRequest;
	unsigned char * pLanguage;

	hTlvTreeIn = TlvTree_New(0);

	pDataRequest = GTL_SharedExchange_InitLocal (128);

	if ((hTlvTreeIn != NULL) && (pDataRequest != NULL))
	{
		// Indicate tag to be requested
		TlvTree_AddChild(hTlvTreeIn, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, NULL, 0);

		cr = SDI_Payment_GetData(nSDSAAppliId, hTlvTreeIn, &hTlvTreeOut);

		if ((cr == SDI_STATUS_OK) && (hTlvTreeOut != NULL)) // If a data has been obtained
		{
			// Copy data in the buffer
			CopyTlvTreeToDataStruct(hTlvTreeOut, pDataRequest);

			if(pDataRequest->ulDataLength)
			{
				// Search the tag in the kernel response structure
				if (CST_Term_RetreiveInfo (pDataRequest, TAG_KERNEL_SELECTED_PREFERED_LANGUAGE, &pLanguage))
				{
					DefCurrentLang((char*)pLanguage);
				}
			}
		}
	}

	// Destroy the buffer
	if (pDataRequest)
		GTL_SharedExchange_DestroyLocal(pDataRequest);

	TlvTree_ReleaseEx (&hTlvTreeIn);
	TlvTree_ReleaseEx (&hTlvTreeOut);

	if(cr == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}

//! \brief Print a transaction ticket (for cardholder or merchant) at the end of a transaction or print transaction batch data, according to input parameter (nTicketType).
//! \param[in] pTransaction Shared exchange buffer containing all the transaction data.
//! \param[in] nTicketType Ticket type.
//! \param[in] nTransactionResult APPROVED_TICKED or DECLINED_TICKED
//! \param[in] bSignatureRequested Indicates if signature is requested or not (\a TRUE if requested, \a FALSE else).
//! \param[in] nAOSA : with Available Offline Spending Amount : WITH_AOSA or WITHOUT_AOSA
//! \note Make sure the output driver is already opened before calling this function.

void CST_Receipt_PrintTransaction (T_SHARED_DATA_STRUCT * pTransaction, int nTicketType, int nTransactionResult, const int bSignatureRequested, int nAOSA)
{
	int nResult, nPosition;
	unsigned long ulTag;
	unsigned long ulReadLength;
	const unsigned char * pValue;
	const unsigned char* pValueStatusCode;
	const unsigned char* pValueTsc;
	unsigned int LengthTsc;
	const unsigned char* pValueAid;
	unsigned int LengthAid;
	const unsigned char* pValueCid;
	const unsigned char* pValueCvrResult;
	const unsigned char* pValueTvr;
	const unsigned char* pValueAmountBin;
	const unsigned char* pValueAmountNum;
	const unsigned char* pValueAmountOtherBin;
	const unsigned char* pValueAmountOtherNum;
	const unsigned char* pValueExpirationDate;
	const unsigned char* pValuePan;
	unsigned int LengthPan;
	const unsigned char* pValuePanSeq;
	const unsigned char* pValueAuthorCode;
	const unsigned char* pValueAuthorRespCode;
	const unsigned char* pValueCurrencyCode;
	const unsigned char* pValueCurrencyExp;
	const unsigned char* pValueDate;
	const unsigned char* pValueTime;
	const unsigned char* pValueType;
	const unsigned char* pValueForcedOnline;
	const unsigned char* pAvailableOfflineSpendingAmount;
	unsigned int length_spending_amount;
	const unsigned char* pVisaWaveAvailableOfflineSpendingAmount;
	unsigned int length_VisaWave_spending_amount;
	const unsigned char* pValueCardType;
	unsigned char temp;
	const unsigned char* pValueApplicationLabel;
	unsigned int length_application_label;
	const unsigned char* pValueAppliPreferedName;
	unsigned int length_appli_prefered_name;
	unsigned long ulStatusCode;
	unsigned long ulTsc;
	unsigned char Aid[20];
	unsigned char Cid;
	unsigned char CvrResult[3];
	unsigned char Tvr[5];
	unsigned long ulAmount;
	unsigned long ulAmountOther;
	char ExpirationDate[6 + 1];
	char Pan[19 + 1];
	unsigned long ulPanSeq;
	char AuthorCode[6 + 1];
	char AuthorRespCode[2 + 1];
	unsigned long ulCurrencyCode;
	unsigned long ulCurrencyExp;
	char Date[6 + 1];
	char Time[6 + 1];
	unsigned long ulType;
	int bForcedOnline;
	char szAmount[20];
	char szSpendingAmount[20];
	char szVisaWaveSpendingAmount[20];
	char transactionKind;
	unsigned long ulAvailableOfflineSpendingAmount;
	unsigned short usCardType;
	unsigned char ApplicationLabel [16 + 1]; // Application label + '\0'
	unsigned char AppliPreferedName [16 + 1]; // Application prefered name + '\0'
	MSGinfos tDisplayMsg;

	
	if (!CST_DumpData_OpenOutputDriver())
		return;

	pValueStatusCode = NULL;
	pValueTsc = NULL;
	LengthTsc = 0;
	pValueAid = NULL;
	LengthAid = 0;
	pValueCid = NULL;
	pValueCvrResult = NULL;
	pValueTvr = NULL;
	pValueAmountBin = NULL;
	pValueAmountNum = NULL;
	pValueAmountOtherBin = NULL;
	pValueAmountOtherNum = NULL;
	pValueExpirationDate = NULL;
	pValuePan = NULL;
	LengthPan = 0;
	pValuePanSeq = NULL;
	pValueAuthorCode = NULL;
	pValueAuthorRespCode = NULL;
	pValueCurrencyCode = NULL;
	pValueCurrencyExp = NULL;
	pValueDate = NULL;
	pValueTime = NULL;
	pValueType = NULL;
	pValueForcedOnline = NULL;
	pAvailableOfflineSpendingAmount = NULL;
	length_spending_amount = 0;
	pVisaWaveAvailableOfflineSpendingAmount = NULL;
	length_VisaWave_spending_amount = 0;
	transactionKind =0;
	pValueCardType = NULL;
	usCardType = 0;
	pValueApplicationLabel = NULL;
	length_application_label = 0;
	pValueAppliPreferedName = NULL;
	length_appli_prefered_name = 0;


	defprinterpatternHR (0, 0, 0xF1, (char *) Line_part_1);
	defprinterpatternHR (0, 0, 0xF2, (char *) Line_part_2);
	defprinterpatternHR (0, 0, 0xF3, (char *) Visa_payWave_part_1);
	defprinterpatternHR (0, 0, 0xF4, (char *) Visa_payWave_part_2);
	defprinterpatternHR (0, 0, 0xF7, (char *) Ingenico_part_1);
	defprinterpatternHR (0, 0, 0xF8, (char *) Ingenico_part_2);
	defprinterpatternHR (0, 0, 0xF9, (char *) Signature_part_1);
	defprinterpatternHR (0, 0, 0xFA, (char *) Signature_part_2);
	defprinterpatternHR (0, 0, 0xFD, (char *) Paypass_only_part_1);
	defprinterpatternHR (0, 0, 0xFE, (char *) Paypass_only_part_2);
	defprinterpatternHR (0, 0, 0xEE, (char *) AmericanExpress_part_1);
	defprinterpatternHR (0, 0, 0xEF, (char *) AmericanExpress_part_2);
	defprinterpatternHR (0, 0, 0xEC, (char *) Discover_part_1);
	defprinterpatternHR (0, 0, 0xED, (char *) Discover_part_2);
	defprinterpatternHR (0, 0, 0xEA, (char *) Interac_only_part_1);
	defprinterpatternHR (0, 0, 0xEB, (char *) Interac_only_part_2);

	nPosition = SHARED_EXCHANGE_POSITION_NULL;

	// Set the current language to cardholder value
	__CST_Receipt_GetSelectedPreferedLanguage();
	
	do{
    	// Try to following tag.
    	nResult = GTL_SharedExchange_GetNext (pTransaction, &nPosition, &ulTag, &ulReadLength, &pValue);

        if (nResult == STATUS_SHARED_EXCHANGE_OK)  // If tag found
        {
//			GTL_Traces_TraceDebug("Receipt tag:%x\n", ulTag);

			switch(ulTag)
			{
			case TAG_KERNEL_STATUS_CODE:					pValueStatusCode = pValue; break;
    		case TAG_EMV_TRANSACTION_SEQUENCE_COUNTER:		pValueTsc = pValue;	LengthTsc = ulReadLength; break;
    		case TAG_EMV_AID_CARD:							pValueAid = pValue;	LengthAid = ulReadLength; break;
    		case TAG_EMV_DF_NAME:							pValueAid = pValue;	LengthAid = ulReadLength; break;
    		case TAG_EMV_CRYPTOGRAM_INFO_DATA:				pValueCid = pValue; break;
    		case TAG_EMV_CVM_RESULTS:						pValueCvrResult = pValue; break;
    		case TAG_EMV_TVR:								pValueTvr = pValue; break;
    		case TAG_EMV_AMOUNT_AUTH_BIN:					pValueAmountBin = pValue; break;
    		case TAG_EMV_AMOUNT_AUTH_NUM:					pValueAmountNum = pValue; break;
    		case TAG_EMV_AMOUNT_OTHER_BIN:					pValueAmountOtherBin = pValue; break;
    		case TAG_EMV_AMOUNT_OTHER_NUM:					pValueAmountOtherNum = pValue; break;
    		case TAG_EMV_APPLI_EXPIRATION_DATE:				pValueExpirationDate = pValue; break;
    		case TAG_EMV_APPLI_PAN:							pValuePan = pValue;	LengthPan = ulReadLength; break;
    		case TAG_EMV_APPLI_PAN_SEQUENCE_NUMBER:			pValuePanSeq = pValue; break;
    		case TAG_EMV_AUTHORISATION_CODE:				pValueAuthorCode = pValue; break;
    		case TAG_EMV_AUTHORISATION_RESPONSE_CODE:		pValueAuthorRespCode = pValue; break;
    		case TAG_EMV_TRANSACTION_CURRENCY_CODE:			pValueCurrencyCode = pValue; break;
    		case TAG_EMV_TRANSACTION_CURRENCY_EXPONENT:		pValueCurrencyExp = pValue; break;
    		case TAG_EMV_TRANSACTION_DATE:					pValueDate = pValue; break;
    		case TAG_EMV_TRANSACTION_TIME:					pValueTime = pValue; break;
    		case TAG_EMV_TRANSACTION_TYPE:					pValueType = pValue; break;
    		case TAG_KERNEL_CARD_TYPE:						pValueCardType=pValue; break;
    		case TAG_EMV_APPLICATION_LABEL:					pValueApplicationLabel=pValue; length_application_label = ulReadLength; break;
			case TAG_EMV_APPLI_PREFERED_NAME:				pValueAppliPreferedName=pValue; length_appli_prefered_name = ulReadLength; break;
    		case TAG_PAYWAVE_AVAILABLE_OFFLINE_SPENDING_AMOUNT: pAvailableOfflineSpendingAmount=pValue; length_spending_amount = ulReadLength; break;
			case TAG_VISAWAVE_VLP_AVAILABLE_FUNDS:			pVisaWaveAvailableOfflineSpendingAmount=pValue; length_VisaWave_spending_amount = ulReadLength; break;
			default:
				break;
			}
        }
        else if (nResult == STATUS_SHARED_EXCHANGE_END)  // Buffer end reached
        {
        }
        else // error or end or ...
        {
        	GTL_Traces_TraceDebug("Display tags error:%x\n", nResult);
        }
    }while (nResult == STATUS_SHARED_EXCHANGE_OK);



	ulStatusCode = 0;
	ulTsc = 0;
	memset(Aid, 0, sizeof(Aid));
	Cid = 0;
	memset(CvrResult, 0, sizeof(CvrResult));
	memset(Tvr, 0, sizeof(Tvr));
	ulAmount = 0;
	ulAmountOther = 0;
	memset(ExpirationDate, '?', sizeof(ExpirationDate));
	memset(Pan, '?', sizeof(Pan));
	ulPanSeq = 0;
	memset(AuthorCode, 0, sizeof(AuthorCode));
	memset(AuthorRespCode, 0, sizeof(AuthorRespCode));
	ulCurrencyCode = 0;
	ulCurrencyExp = 0;
	memset(Date, '?', sizeof(Date));
	memset(Time, '?', sizeof(Time));
	ulType = 0;
	bForcedOnline = FALSE;
	ulAvailableOfflineSpendingAmount = 0;
	memset (szSpendingAmount, '\0', sizeof(szSpendingAmount));
	memset (szVisaWaveSpendingAmount, '\0', sizeof(szVisaWaveSpendingAmount));
	memset (ApplicationLabel, '\0', sizeof(ApplicationLabel));

	if (pValueStatusCode != NULL)
		GTL_Convert_BinNumberToUl(pValueStatusCode, &ulStatusCode, 2);
	if (pValueTsc != NULL)
		GTL_Convert_DcbNumberToUl(pValueTsc, &ulTsc, LengthTsc);
	if (pValueAid != NULL)
		memcpy(Aid, pValueAid, LengthAid);
	if (pValueCid != NULL)
		Cid = *pValueCid;
	if (pValueCvrResult != NULL)
		memcpy(CvrResult, pValueCvrResult, sizeof(CvrResult));
	if (pValueTvr != NULL)
		memcpy(Tvr, pValueTvr, sizeof(Tvr));
	if (pValueAmountBin != NULL)
		GTL_Convert_BinNumberToUl(pValueAmountBin, &ulAmount, 4);
	if (pValueAmountOtherBin != NULL)
		GTL_Convert_BinNumberToUl(pValueAmountOtherBin, &ulAmountOther, 4);
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
	if (pValueAuthorCode != NULL)
		memcpy(AuthorCode, pValueAuthorCode, 6);
	if (pValueAuthorRespCode != NULL)
		memcpy(AuthorRespCode, pValueAuthorRespCode, 2);
	if (pValueCurrencyCode != NULL)
		GTL_Convert_DcbNumberToUl(pValueCurrencyCode, &ulCurrencyCode, 2);
	if (pValueCurrencyExp != NULL)
		GTL_Convert_DcbNumberToUl(pValueCurrencyExp, &ulCurrencyExp, 1);
	if (pValueDate != NULL)
		GTL_Convert_DcbNumberToAscii(pValueDate, Date, 3, 6);
	if (pValueTime != NULL)
		GTL_Convert_DcbNumberToAscii(pValueTime, Time, 3, 6);
	if (pValueType != NULL)
		GTL_Convert_DcbNumberToUl(pValueType, &ulType, 1);
	if (pValueForcedOnline != NULL)
	{
		if (*pValueForcedOnline)
			bForcedOnline = TRUE;
	}
	
	if (pAvailableOfflineSpendingAmount != NULL)
	{
		CST_FormatSpendingAmount(pAvailableOfflineSpendingAmount, length_spending_amount, szSpendingAmount);
	}

	if (pVisaWaveAvailableOfflineSpendingAmount != NULL)
	{
		CST_FormatSpendingAmount(pVisaWaveAvailableOfflineSpendingAmount, length_VisaWave_spending_amount, szVisaWaveSpendingAmount);
	}
	
	//transactionKind = UNKNOWN_TRANSACTION;
	if (pValueCardType != NULL)
		usCardType = (pValueCardType[0] << 8) + pValueCardType[1];

	if (pValueApplicationLabel != NULL)
		memcpy (ApplicationLabel, pValueApplicationLabel, length_application_label);

	if (pValueAppliPreferedName != NULL)
		memcpy (AppliPreferedName, pValueAppliPreferedName, length_appli_prefered_name);

	// Print a VISA ticket
	if ((nTicketType == BATCH_TICKET_VISA) || (nTicketType == BATCH_TICKET_VISAWAVE))
	{
		__CST_Receipt_FormatAmount(ulAmount, FALSE, ulCurrencyExp, 0, szAmount);

		memset(Pan, '-', 6);
		Pan[strlen(Pan) - 1] = '-';


		if(nTicketType == BATCH_TICKET_VISAWAVE)
		{
			if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			{
				CST_DumpData("\xF7\xF8");
			}
			else
			{
				CST_DumpData("#       #           #         #                    )");CST_DumpData_NewLine();
				CST_DumpData(" #     #   ###       #   #   #                   )  )");CST_DumpData_NewLine();
				CST_DumpData("  #   #  # #     ###  # # # # ### #   # ##     )  )  )");CST_DumpData_NewLine();
				CST_DumpData("   # #   #   #  #  #   #   # #  #  # # ## #  )  )  ) )");CST_DumpData_NewLine();
				CST_DumpData("    #    # ###   ####  #   #  ####  #   ##     )  )  )");CST_DumpData_NewLine();
				CST_DumpData("                                                 )  )");CST_DumpData_NewLine();
				CST_DumpData("                                                   ) ");CST_DumpData_NewLine();
			}
		}
		else
		{
			if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			{
				CST_DumpData("\xF3\xF4");
			}
			else
			{
				CST_DumpData("               #         #                    )");CST_DumpData_NewLine();
				CST_DumpData("                #   #   #                   )  )");CST_DumpData_NewLine();
				CST_DumpData(" ###   ### #   # # # # # ### #   # ##     )  )  )");CST_DumpData_NewLine();
				CST_DumpData(" #  # #  #  # #   #   # #  #  # # ## #  )  )  ) )");CST_DumpData_NewLine();
				CST_DumpData(" ###   ####  #    #   #  ####  #   ##     )  )  )");CST_DumpData_NewLine();
				CST_DumpData(" #          #                               )  )");CST_DumpData_NewLine();
				CST_DumpData(" #         #                                  ) ");CST_DumpData_NewLine();
			}
		}
		
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			CST_DumpData ("\xF1\xF2");
		else
			CST_DumpData ("---------------------------");

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

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

			CST_DumpData("\x1b" "@");
			CST_DumpData("%s", ApplicationLabel);
			CST_DumpData_NewLine();
		}

		for (temp=0;temp<(unsigned char)LengthAid;temp++)
			CST_DumpData("%02x", Aid[temp]);

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		CST_DumpData("\x1b" "@\x1b" "E");

		
		if (ulType == 0)
		{
			GetMessageInfos(STD_MESS_DEBIT, &tDisplayMsg);
			CST_DumpData(tDisplayMsg.message);
		}
		else
		{
			GetMessageInfos(STD_MESS_TRANSAC_TYPE, &tDisplayMsg);
			CST_DumpData("%s %lu", tDisplayMsg.message, ulType);
		}

		CST_DumpData("\x1b" "@");
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData ("%c%c/%c%c/%c%c %c%c:%c%c:%c%c", Date[4], Date[5], Date[2], Date[3], Date[0], Date[1], Time[0], Time[1], Time[2], Time[3], Time[4], Time[5]);
		CST_DumpData_NewLine();

		if (pValuePan != NULL)
		{
			CST_DumpData ("\x1b" "@");
			CST_DumpData ("%s", Pan);
			CST_DumpData_NewLine();
		}
		else
		{
			CST_DumpData_NewLine();
		}

		if (pValueExpirationDate != NULL)
		{
			CST_DumpData ("\x1b" "@");
			CST_DumpData ("%c%c/%c%c", ExpirationDate[2], ExpirationDate[3], ExpirationDate[0], ExpirationDate[1]);
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
		}
		else
		{
			CST_DumpData_NewLine();
		}

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "@" "\x1b" "E");
		
		if (nTransactionResult == APPROVED_TICKED)
			GetMessageInfos(STD_MESS_APPROVED_TICKET, &tDisplayMsg);
		else // (nTransactionResult == DECLINED_TICKED)
			GetMessageInfos(STD_MESS_DECLINED_TICKET, &tDisplayMsg);
		CST_DumpData (tDisplayMsg.message);
		
		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		GetMessageInfos(STD_MESS_AMOUNT, &tDisplayMsg);
		CST_DumpData (tDisplayMsg.message);
		
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "E");

		CST_DumpData ("%s %s", CST_Term_GiveMoneyLabel(), szAmount);
		
		
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();

		if (nAOSA == WITH_AOSA)
		{
			if(nTicketType == BATCH_TICKET_VISAWAVE)
			{
				if (pVisaWaveAvailableOfflineSpendingAmount != NULL)
				{
					if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
						CST_DumpData ("\x0F");

					GetMessageInfos(STD_MESS_AVAILABLE, &tDisplayMsg);
					CST_DumpData (tDisplayMsg.message);
					if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
						CST_DumpData ("\x1b" "@");

					CST_DumpData ("%s", szVisaWaveSpendingAmount);

					if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
						CST_DumpData ("\x1b" "@");
					CST_DumpData_NewLine();
				}
			}
			else
			{
				if (pAvailableOfflineSpendingAmount != NULL)
				{
					if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
						CST_DumpData ("\x0F");

					GetMessageInfos(STD_MESS_AVAILABLE, &tDisplayMsg);
					CST_DumpData (tDisplayMsg.message);
					if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
						CST_DumpData ("\x1b" "@");

					CST_DumpData ("%s", szSpendingAmount);

					if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
						CST_DumpData ("\x1b" "@");
					CST_DumpData_NewLine();
				}
			}
		}// else (nAOSA == WITHOUT_AOSA) => no action

		if (bSignatureRequested)
		{
			CST_DumpData_NewLine();

			if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			{
				CST_DumpData ("\xF9\xFA");
			}
			else
			{
				CST_DumpData (" *** Signature ******************* ");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData (" ********************************* ");
			}
		}
		
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData("Love Every Quick Payment");
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			CST_DumpData ("\xF1\xF2");
		else
			CST_DumpData ("-------------------------");

		CST_DumpData_NewLine();
		CST_DumpData("  And keep in touch !");
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Different presentation if on a printer or in text mode
		{
			CST_DumpData("      Ingenico");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("           1, rue Claude Chappe BP 346");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("      07 503  Guilherand-Granges - FRANCE");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("Tel:+33 475 81 40 40        Fax:+33 475 81 43 00");
			CST_DumpData("\x1b" "@");
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData ("\xF1\xF2");
		}
		else
		{
			CST_DumpData("      Ingenico");CST_DumpData_NewLine();
			CST_DumpData("1, rue Claude Chappe BP 346");CST_DumpData_NewLine();
			CST_DumpData(" 07 503 Guilherand-Granges");CST_DumpData_NewLine();
			CST_DumpData("    Tel:+33 475 81 40 40");CST_DumpData_NewLine();
			CST_DumpData("    Fax:+33 475 81 43 00");
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData ("-------------------------");
			ttestall (0,5);
		}

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
	}

	// Print a Mastercard ticket
	else if (nTicketType == BATCH_TICKET_MASTERCARD)
	{
		__CST_Receipt_FormatAmount(ulAmount, FALSE, ulCurrencyExp, 0, szAmount);

		memset(Pan, '-', 6);
		Pan[strlen(Pan) - 1] = '-';

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
		{
			CST_DumpData("\xFD\xFE");
		}
		else
		{
			CST_DumpData(" ####            #### ");CST_DumpData_NewLine();
			CST_DumpData(" #   #           #   #");CST_DumpData_NewLine();
			CST_DumpData(" ####  ### #   # ####  ###   ###  ###");CST_DumpData_NewLine();
			CST_DumpData(" #    #  #  # #  #    #  #  #### ####");CST_DumpData_NewLine();
			CST_DumpData(" #     ####  #   #     #### ###  ###");CST_DumpData_NewLine();
			CST_DumpData("            #");CST_DumpData_NewLine();
			CST_DumpData("           #");CST_DumpData_NewLine();
		}
			
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			CST_DumpData ("\xF1\xF2");
		else
			CST_DumpData ("-------------------------");

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		CST_DumpData ("\x1b" "@\x1b" "E");

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

			CST_DumpData("\x1b" "@");
			CST_DumpData("%s", ApplicationLabel);
			CST_DumpData_NewLine();
		}

		for (temp=0;temp<(unsigned char)LengthAid;temp++)
			CST_DumpData("%02x", Aid[temp]);

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		CST_DumpData("\x1b" "@\x1b" "E");

		if (ulType == 0) // Debit
		{
			GetMessageInfos(STD_MESS_DEBIT, &tDisplayMsg);
			CST_DumpData(tDisplayMsg.message);
		}
		else if (ulType == 20) // Refund
		{
			GetMessageInfos(STD_MESS_MENU_MAIN_REFUND, &tDisplayMsg);
			CST_DumpData(tDisplayMsg.message);
		}
		else
		{
			GetMessageInfos(STD_MESS_TRANSAC_TYPE, &tDisplayMsg);
			CST_DumpData("%s %lu", tDisplayMsg.message, ulType);
		}

		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData ("%c%c/%c%c/%c%c %c%c:%c%c:%c%c", Date[4], Date[5], Date[2], Date[3], Date[0], Date[1], Time[0], Time[1], Time[2], Time[3], Time[4], Time[5]);
		CST_DumpData_NewLine();
		CST_DumpData ("%s", Pan);
		CST_DumpData_NewLine();
		CST_DumpData ("%c%c/%c%c", ExpirationDate[2], ExpirationDate[3], ExpirationDate[0], ExpirationDate[1]);
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData ("\x1b" "E");

		GetMessageInfos(STD_MESS_APPROVED_TICKET, &tDisplayMsg);
		CST_DumpData (tDisplayMsg.message);
		
		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		
		GetMessageInfos(STD_MESS_AMOUNT, &tDisplayMsg);
		CST_DumpData (tDisplayMsg.message);
		
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "E");

		CST_DumpData ("%s %s", CST_Term_GiveMoneyLabel(), szAmount);
		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();


		if (bSignatureRequested)
		{
			CST_DumpData_NewLine();

			if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			{
				CST_DumpData ("\xF9\xFA");
			}
			else
			{
				CST_DumpData (" *** Signature ******************* ");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData (" ********************************* ");
			}
		}

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData("  Let's keep in touch !");
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			CST_DumpData ("\xF1\xF2");
		else
			CST_DumpData ("---------------------------");

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Different presentation if on a printer or in text mode
		{
			CST_DumpData("      Ingenico");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("           1, rue Claude Chappe BP 346");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("      07 503  Guilherand-Granges - FRANCE");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("Tel:+33 475 81 40 40        Fax:+33 475 81 43 00");
			CST_DumpData("\x1b" "@");
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData ("\xF1\xF2");
		}
		else
		{
			CST_DumpData("       Ingenico");CST_DumpData_NewLine();
			CST_DumpData("1, rue Claude Chappe BP 346");CST_DumpData_NewLine();
			CST_DumpData(" 07 503 Guilherand-Granges");CST_DumpData_NewLine();
			CST_DumpData("   Tel:+33 475 81 40 40");CST_DumpData_NewLine();
			CST_DumpData("   Fax:+33 475 81 43 00");CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData("---------------------------");
			ttestall (0,5);
		}

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
	}
		// Print an ExpressPay ticket
	else if (nTicketType == BATCH_TICKET_AMEX)
	{
		__CST_Receipt_FormatAmount(ulAmount, FALSE, ulCurrencyExp, 0, szAmount);

		memset(Pan, '-', 6);
		Pan[strlen(Pan) - 1] = '-';

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
		{
			CST_DumpData("\xEE\xEF");
		}
		else
		{
			CST_DumpData("  ###             ");CST_DumpData_NewLine();
			CST_DumpData(" #   #              ");CST_DumpData_NewLine();
			CST_DumpData(" #####  ### ### ###  # # ");CST_DumpData_NewLine();
			CST_DumpData(" #   # #  ##  # # #   # ");CST_DumpData_NewLine();
			CST_DumpData(" #   # #  #   #  ### # #");CST_DumpData_NewLine();
		}
			
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			CST_DumpData ("\xF1\xF2");
		else
			CST_DumpData ("-------------------------");

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		CST_DumpData ("\x1b" "@\x1b" "E");

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

			CST_DumpData("\x1b" "@");
			CST_DumpData("%s", ApplicationLabel);
			CST_DumpData_NewLine();
		}

		for (temp=0;temp<(unsigned char)LengthAid;temp++)
			CST_DumpData("%02x", Aid[temp]);

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		CST_DumpData("\x1b" "@\x1b" "E");

		if (ulType == 0)
		{
			GetMessageInfos(STD_MESS_DEBIT, &tDisplayMsg);
			CST_DumpData(tDisplayMsg.message);
		}
		else
		{
			GetMessageInfos(STD_MESS_TRANSAC_TYPE, &tDisplayMsg);
			CST_DumpData("%s %lu", tDisplayMsg.message, ulType);
		}

		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData ("%c%c/%c%c/%c%c %c%c:%c%c:%c%c", Date[4], Date[5], Date[2], Date[3], Date[0], Date[1], Time[0], Time[1], Time[2], Time[3], Time[4], Time[5]);
		CST_DumpData_NewLine();
		CST_DumpData ("%s", Pan);
		CST_DumpData_NewLine();
		CST_DumpData ("%c%c/%c%c", ExpirationDate[2], ExpirationDate[3], ExpirationDate[0], ExpirationDate[1]);
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData ("\x1b" "E");

		GetMessageInfos(STD_MESS_APPROVED_TICKET, &tDisplayMsg);
		CST_DumpData (tDisplayMsg.message);
		
		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		
		GetMessageInfos(STD_MESS_AMOUNT, &tDisplayMsg);
		CST_DumpData (tDisplayMsg.message);
		
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "E");

		CST_DumpData ("%s %s", CST_Term_GiveMoneyLabel(), szAmount);
		
		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();


		if (bSignatureRequested)
		{
			CST_DumpData_NewLine();

			if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			{
				CST_DumpData ("\xF9\xFA");
			}
			else
			{
				CST_DumpData (" *** Signature ******************* ");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData (" ********************************* ");
			}
		}

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData("  Let's keep in touch !");
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			CST_DumpData ("\xF1\xF2");
		else
			CST_DumpData ("---------------------------");

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Different presentation if on a printer or in text mode
		{
			CST_DumpData("      Ingenico");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("           1, rue Claude Chappe BP 346");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("      07 503  Guilherand-Granges - FRANCE");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("Tel:+33 475 81 40 40        Fax:+33 475 81 43 00");
			CST_DumpData("\x1b" "@");
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData ("\xF1\xF2");
		}
		else
		{
			CST_DumpData("       Ingenico");CST_DumpData_NewLine();
			CST_DumpData("1, rue Claude Chappe BP 346");CST_DumpData_NewLine();
			CST_DumpData(" 07 503 Guilherand-Granges");CST_DumpData_NewLine();
			CST_DumpData("   Tel:+33 475 81 40 40");CST_DumpData_NewLine();
			CST_DumpData("   Fax:+33 475 81 43 00");CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData("---------------------------");
			ttestall (0,5);
		}

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
	}

	// Print a Discover ticket
	else if (nTicketType == BATCH_TICKET_DISCOVER)
	{
		__CST_Receipt_FormatAmount(ulAmount, FALSE, ulCurrencyExp, 0, szAmount);

		memset(Pan, '-', 6);
		Pan[strlen(Pan) - 1] = '-';

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
		{
			CST_DumpData("\xEC\xED");
		}
		else
		{
			CST_DumpData(" #### ");CST_DumpData_NewLine();
			CST_DumpData(" #   #  #");CST_DumpData_NewLine();
			CST_DumpData(" #    #     ##  ##  ##  #  #  ##   ##");CST_DumpData_NewLine();
			CST_DumpData(" #    # #  #   #   #  # #  # #  # #");CST_DumpData_NewLine();
			CST_DumpData(" #    # #  ##  #   #  # #  # ###  #");CST_DumpData_NewLine();
			CST_DumpData(" #   #  #    # #   #  #  ##  #    #");CST_DumpData_NewLine();
			CST_DumpData(" ####   #  ##   ##  ##   ##   ##  #");CST_DumpData_NewLine();
		}
			
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			CST_DumpData ("\xF1\xF2");
		else
			CST_DumpData ("-------------------------");

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		CST_DumpData ("\x1b" "@\x1b" "E");

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

			CST_DumpData("\x1b" "@");
			CST_DumpData("%s", ApplicationLabel);
			CST_DumpData_NewLine();
		}

		// Print the Application Prefered Name
		CST_DumpData("\x1b" "@");
		CST_DumpData("%s", AppliPreferedName);
		CST_DumpData_NewLine();

		for (temp=0;temp<(unsigned char)LengthAid;temp++)
			CST_DumpData("%02x", Aid[temp]);

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		CST_DumpData("\x1b" "@\x1b" "E");

		if (ulType == 0)
		{
			GetMessageInfos(STD_MESS_DEBIT, &tDisplayMsg);
			CST_DumpData(tDisplayMsg.message);
		}
		else
		{
			GetMessageInfos(STD_MESS_TRANSAC_TYPE, &tDisplayMsg);
			CST_DumpData("%s %lu", tDisplayMsg.message, ulType);
		}

		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData ("%c%c/%c%c/%c%c %c%c:%c%c:%c%c", Date[4], Date[5], Date[2], Date[3], Date[0], Date[1], Time[0], Time[1], Time[2], Time[3], Time[4], Time[5]);
		CST_DumpData_NewLine();
		CST_DumpData ("%s", Pan);
		CST_DumpData_NewLine();
		CST_DumpData ("%c%c/%c%c", ExpirationDate[2], ExpirationDate[3], ExpirationDate[0], ExpirationDate[1]);
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData ("\x1b" "E");

		GetMessageInfos(STD_MESS_APPROVED_TICKET, &tDisplayMsg);
		CST_DumpData (tDisplayMsg.message);
		
		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		
		GetMessageInfos(STD_MESS_AMOUNT, &tDisplayMsg);
		CST_DumpData (tDisplayMsg.message);
		
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "E");

		CST_DumpData ("%s %s", CST_Term_GiveMoneyLabel(), szAmount);
		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();


		if (bSignatureRequested)
		{
			CST_DumpData_NewLine();

			if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			{
				CST_DumpData ("\xF9\xFA");
			}
			else
			{
				CST_DumpData (" *** Signature ******************* ");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData (" ********************************* ");
			}
		}

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData("    Have a nice day !");
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			CST_DumpData ("\xF1\xF2");
		else
			CST_DumpData ("---------------------------");

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Different presentation if on a printer or in text mode
		{
			CST_DumpData("      Ingenico");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("           1, rue Claude Chappe BP 346");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("      07 503  Guilherand-Granges - FRANCE");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("Tel:+33 475 81 40 40        Fax:+33 475 81 43 00");
			CST_DumpData("\x1b" "@");
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData ("\xF1\xF2");
		}
		else
		{
			CST_DumpData("       Ingenico");CST_DumpData_NewLine();
			CST_DumpData("1, rue Claude Chappe BP 346");CST_DumpData_NewLine();
			CST_DumpData(" 07 503 Guilherand-Granges");CST_DumpData_NewLine();
			CST_DumpData("   Tel:+33 475 81 40 40");CST_DumpData_NewLine();
			CST_DumpData("   Fax:+33 475 81 43 00");CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData("---------------------------");
			ttestall (0,5);
		}

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
	}

	// Print a Interac ticket
	else if (nTicketType == BATCH_TICKET_INTERAC)
	{
		__CST_Receipt_FormatAmount(ulAmount, FALSE, ulCurrencyExp, 0, szAmount);

		memset(Pan, '-', 6);
		Pan[strlen(Pan) - 1] = '-';

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
		{
			CST_DumpData("       \xEA\xEB");
		}
		else
		{
			CST_DumpData(" #                            ");CST_DumpData_NewLine();
			CST_DumpData(" #       #                    ");CST_DumpData_NewLine();
			CST_DumpData(" #      ###                   ");CST_DumpData_NewLine();
			CST_DumpData(" # ###   #    ##  ##  ##   ## ");CST_DumpData_NewLine();
			CST_DumpData(" # #  #  #   # # #   #  # #   ");CST_DumpData_NewLine();
			CST_DumpData(" # #  #  # # ##  #   #  # #   ");CST_DumpData_NewLine();
			CST_DumpData(" # #  #  ##   ## #    ###  ## ");CST_DumpData_NewLine();
		}
			
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			CST_DumpData ("\xF1\xF2");
		else
			CST_DumpData ("-------------------------");

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		CST_DumpData ("\x1b" "@\x1b" "E");

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

			CST_DumpData("\x1b" "@");
			CST_DumpData("%s", ApplicationLabel);
			CST_DumpData_NewLine();
		}

		// Print the Application Prefered Name
		CST_DumpData("\x1b" "@");
		CST_DumpData("%s", AppliPreferedName);
		CST_DumpData_NewLine();

		for (temp=0;temp<(unsigned char)LengthAid;temp++)
			CST_DumpData("%02x", Aid[temp]);

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		CST_DumpData("\x1b" "@\x1b" "E");

		if (*pValueType == 0) //Debit
		{
			GetMessageInfos(STD_MESS_DEBIT, &tDisplayMsg);
			CST_DumpData(tDisplayMsg.message);
		}
		else if (*pValueType == 0x20) // Refund
		{
			GetMessageInfos(INTERAC_MESS_REFUND, &tDisplayMsg);
			CST_DumpData(tDisplayMsg.message);
		}
		else
		{
			GetMessageInfos(STD_MESS_TRANSAC_TYPE, &tDisplayMsg);
			CST_DumpData("%s %lu", tDisplayMsg.message, ulType);
		}

		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData ("%c%c/%c%c/%c%c %c%c:%c%c:%c%c", Date[4], Date[5], Date[2], Date[3], Date[0], Date[1], Time[0], Time[1], Time[2], Time[3], Time[4], Time[5]);
		CST_DumpData_NewLine();
		CST_DumpData ("%s", Pan);
		CST_DumpData_NewLine();
		CST_DumpData ("%c%c/%c%c", ExpirationDate[2], ExpirationDate[3], ExpirationDate[0], ExpirationDate[1]);
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData ("\x1b" "E");

		GetMessageInfos(STD_MESS_APPROVED_TICKET, &tDisplayMsg);
		CST_DumpData (tDisplayMsg.message);
		
		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		
		GetMessageInfos(STD_MESS_AMOUNT, &tDisplayMsg);
		CST_DumpData (tDisplayMsg.message);
		
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "E");

		CST_DumpData ("%s %s", CST_Term_GiveMoneyLabel(), szAmount);
		CST_DumpData ("\x1b" "@");
		CST_DumpData_NewLine();


		if (bSignatureRequested)
		{
			CST_DumpData_NewLine();

			if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			{
				CST_DumpData ("\xF9\xFA");
			}
			else
			{
				CST_DumpData (" *** Signature ******************* ");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData ("*                                 *");CST_DumpData_NewLine();
				CST_DumpData (" ********************************* ");
			}
		}

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData("Contactless in a Flash !");
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Bitmaps only works with a printer
			CST_DumpData ("\xF1\xF2");
		else
			CST_DumpData ("---------------------------");

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER) // Different presentation if on a printer or in text mode
		{
			CST_DumpData("      Ingenico");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("           1, rue Claude Chappe BP 346");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("      07 503  Guilherand-Granges - FRANCE");
			CST_DumpData_NewLine();
			CST_DumpData("\x0F");
			CST_DumpData("Tel:+33 475 81 40 40        Fax:+33 475 81 43 00");
			CST_DumpData("\x1b" "@");
			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData ("\xF1\xF2");
		}
		else
		{
			CST_DumpData("       Ingenico");CST_DumpData_NewLine();
			CST_DumpData("1, rue Claude Chappe BP 346");CST_DumpData_NewLine();
			CST_DumpData(" 07 503 Guilherand-Granges");CST_DumpData_NewLine();
			CST_DumpData("   Tel:+33 475 81 40 40");CST_DumpData_NewLine();
			CST_DumpData("   Fax:+33 475 81 43 00");CST_DumpData_NewLine();
			CST_DumpData_NewLine();
			CST_DumpData("---------------------------");
			ttestall (0,5);
		}

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		// output the TVR
		CST_DumpData("TVR: ");

		for (temp=0;temp<5;temp++)
			CST_DumpData("%02x", Tvr[temp]);

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
	}
	
	CST_DumpData_CloseOutputDriver();

	// Set the current language
	CST_Term_SetMerchantLanguage();
}
