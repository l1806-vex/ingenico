/**
 * \file	CST_Scan.c
 * \brief	This module manages contact transactions.
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


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

typedef struct
{
    unsigned short type_code;
	unsigned short service;
	unsigned long m_ulAmount;
	int m_nCurrencyCode;
} T_PERFORM_PAYMENT;


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

FILE* hSwipe2;
FILE* hCam0;
int bSwipe2DriverOpened;
int bCam0DriverOpened;

int g_ListOfEvent;											// Global variable used by the scanning task to provide the event.

static S_TRANSIN trans_in;
static StructPt  EntryPoint;

static TRACK2_BUFFER bufIso2;
LG_REF_CLI lgIso2;

/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////



/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Memorise ISO2 track.
//! \param[in] lgParamIso2 : lg track Iso 2.
//! \param[in] pParambufIso2 pointer on ISO2 track data. 
void CST_Scan_MemoriseISO2Track(LG_REF_CLI lgParamIso2, TRACK2_BUFFER pParambufIso2)
{
    if (lgParamIso2 <= sizeof(TRACK2_BUFFER))
    {
        lgIso2 = lgParamIso2;
        memcpy(bufIso2, pParambufIso2, lgParamIso2);
    }
    else
        lgIso2 = 0;
}


//! \brief Opens the drivers for contact transactions.

void CST_Scan_TransacOpenDrivers(void)
{	
	hSwipe2 = stdperif("SWIPE2",NULL);
	if (hSwipe2 == NULL)
	{
		bSwipe2DriverOpened = TRUE;
		hSwipe2 = fopen("SWIPE2", "r");
		GTL_Traces_TraceDebug("Swipe 2 opened");
	}
	else
	{
		bSwipe2DriverOpened = FALSE;
		GTL_Traces_TraceDebug("Swipe 2 already opened");
	}

	hCam0 = stdperif("CAM0",NULL);
	if (hCam0 == NULL)
	{
		bCam0DriverOpened = TRUE;
		hCam0 = fopen("CAM0", "rw");
		GTL_Traces_TraceDebug("Cam0 opened");
	}
	else
	{
		bCam0DriverOpened = FALSE;
		GTL_Traces_TraceDebug("Cam0 already opened");
	}
}


//! \brief Close the Cam0 contact driver.

void CST_Scan_TransacCloseDriversExceptSwipe(void)
{
    if (hCam0 != NULL)
    {
        fclose(hCam0);
        hCam0 = NULL;
    }
}


//! \brief Close the contact drivers.

void CST_Scan_TransacCloseDrivers(void)
{
	if (bSwipe2DriverOpened)
	{
		if (hSwipe2 != NULL)
		{
			fclose(hSwipe2);
			hSwipe2 = NULL;
		}
	}
	if (bCam0DriverOpened)
	{
		if (hCam0 != NULL)
		{
			fclose(hCam0);
			hCam0 = NULL;
		}
	}
}



//! \brief Perform a contact transaction on Cam0.
//! \param[in] ulAmount Transaction amount. 
//! \param[in] nCurrencyCode Transaction currency code.
//! \return :
//!		- TRUE if the contact transaction is performed
//!		- FALSE else

int CST_Scan_TransacCam0(unsigned long ulAmount, int nCurrencyCode)
{
	int bResult;
	unsigned char priority;
	int  ret_code;
	T_PERFORM_PAYMENT Data;

	bResult = FALSE;

	CST_Scan_TransacCloseDrivers();

	if (ServiceGet(0x5D,120,&priority)==0)
	{
		Data.type_code = 0x5D;
		Data.service = 120;
		Data.m_ulAmount = ulAmount;
		Data.m_nCurrencyCode = nCurrencyCode;
		USR_ServiceCall(0x5D,120,sizeof(Data),&Data,&ret_code);

		bResult = TRUE;
	}
	else if (ServiceGet(0x51,120,&priority)==0)
	{
		Data.type_code = 0x51;
		Data.service = 120;
		Data.m_ulAmount = ulAmount;
		Data.m_nCurrencyCode = nCurrencyCode;
		USR_ServiceCall(0x51,120,sizeof(Data),&Data,&ret_code);

		bResult = TRUE;
	}

	return bResult;
}



//! \brief Perform a swipe transaction.
//! \param[in] ulAmount Transaction amount. 
//! \return :
//!		- TRUE if the swipe transaction is performed
//!		- FALSE else

int CST_Scan_TransacSwipe2(unsigned long ulAmount)
{
	int bResult;
	unsigned char priority;
	int  ret_code;

	bResult = FALSE;

    CST_Scan_TransacCloseDriversExceptSwipe(); // Close just the CAM0

	if (ServiceGet (0x68, DEBIT_NON_EMV, &priority) == 0)
	{
		EntryPoint.type_code = 0x68;
		EntryPoint.service = DEBIT_NON_EMV;

		// Fill in trans_in structure
		trans_in.del.count = 0;
		trans_in.support = TRACK2_SUPPORT;
		trans_in.entry = MANUAL_ENTRY;
		trans_in.payment = CARD_PAYMENT;
		trans_in.transaction = DEBIT_TR;
		// No initial amount
		trans_in.amount = ulAmount;
		trans_in.peri = 0;
		trans_in.report_piste = TRUE;
		memset (trans_in.track1, 0, sizeof(TRACK1_BUFFER));
		memcpy (trans_in.track2, bufIso2, lgIso2);
		memset (trans_in.track3, 0, sizeof(TRACK3_BUFFER));
		memcpy(&EntryPoint.Param.DebitNonEmv.param_in, &trans_in, sizeof(S_TRANSIN));

		ServiceCall(0x68, DEBIT_NON_EMV, sizeof(StructPt), &EntryPoint, &ret_code);

		bResult = TRUE;
    }

	CST_Scan_TransacCloseDrivers();

	return bResult;
}


//! \brief Perform a contact transaction.
//! If a contact card has already been detected, the transaction is directly performed, else a message is displayed and contact interfaces are scanned to detect the card.
//! \param[in] ulAmount Transaction amount. 
//! \param[in] nCurrencyCode Transaction currency code.
//! \param[in] pFormattedAmountMessage Message to display that contains the transaction amount. 
//! \param[in] bScanInterfaces Boolean (TRUE if contact interfaces must be scanned). 

void CST_Scan_PerformContactTransaction (unsigned long ulAmount, int nCurrencyCode, char *pFormattedAmountMessage, int bScanInterfaces)
{
	FILE * hKeyboard;
	FILE * hCam0Task;
	FILE * hSwipeTask;
	unsigned char StatusSwipe,StatusCam0;
	int nEvent;
	MSGinfos tMsg;
	int nTime;
	int bStopScanning;

	if(bScanInterfaces)
	{
		// Display insert/swipe message
		GetMessageInfos(STD_MESS_INSERT_OR_SWIPE, &tMsg);
		Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_3, &tMsg);

		// Display the amount with the same font
		tMsg.message = pFormattedAmountMessage;
		Helper_DisplayTextMerchant(NO_ERASE, HELPERS_MERCHANT_LINE_2, &tMsg);

		Helper_RefreshScreen(NOWAIT);

		CST_Scan_TransacOpenDrivers();

		hKeyboard = fopen("KEYBOARD", "r");

		bStopScanning = FALSE;
		nTime = 0;

		while ((!bStopScanning) && (nTime < 6000)) // Wait for event during 60 seconds
		{
			StatusSwipe = 0;
			StatusCam0 = 0;
			nEvent = 0;

			// Check if there is an event on the CAM0 (if opened)
			hCam0Task = stdperif ("CAM0", NULL);
			if (hCam0Task != NULL)
			{
				status(hCam0Task, &StatusCam0);
				if ((StatusCam0 & CAM_PRESENT) != 0)
					nEvent = CAM0;
			}

			// Check if there is an event on the SWIPE2 (if opened)
			hSwipeTask = stdperif ("SWIPE2", NULL);
			if (hSwipeTask != NULL)
			{
				status(hSwipeTask, &StatusSwipe);
				if ((StatusSwipe & TRACK_READ) != 0)
				{
					nEvent = SWIPE2;
					
                    { // Iso2 Track memorisation
                        int iCrIso2;
                        unsigned char ucgIso2 = 0;
                        static TRACK2_BUFFER bufIso2;
                    	
                        iCrIso2 = is_iso2 (hSwipeTask, &ucgIso2, bufIso2);
                        if (iCrIso2 == ISO_OK)
                            CST_Scan_MemoriseISO2Track(sizeof(TRACK2_BUFFER), bufIso2);
                        else
                            CST_Scan_MemoriseISO2Track(0, bufIso2);
                    }
                }
			}

			// No previous events (SWIPE2 or CAM0), make a ttestall during 10ms
			if (nEvent == 0)
				nEvent = ttestall (KEYBOARD, 1);

			// According to the event that may have occured
			switch(nEvent)
			{
			case (0): // Timeout, no event, continue scanning
				break;

			case KEYBOARD: // Keyboard event
				if (getchar() == T_ANN) // Cancel only if red key pressed
				{
					bStopScanning = TRUE;
				}
				break;

			case CAM0:
				g_ListOfEvent = nEvent;
				bStopScanning = TRUE;
				break;

			case SWIPE2:
				g_ListOfEvent = nEvent;
				bStopScanning = TRUE;
				break;

			default:
				break;
			}

			nTime++;
		}

		// Close the keyboard
		fclose (hKeyboard);

		CST_Scan_TransacCloseDrivers();
	}

	// Perform a contact transaction if a card has been detected
	if(g_ListOfEvent & CAM0)
	{
		if (CST_Scan_TransacCam0(ulAmount, nCurrencyCode) == FALSE)
			GTL_Traces_TraceDebug ("CST_Scan_PerformContactTransaction Pb Transac Cam 0");
	}
	else if(g_ListOfEvent & SWIPE2)
	{
		if (CST_Scan_TransacSwipe2(ulAmount) == FALSE)
			GTL_Traces_TraceDebug ("CST_Scan_PerformContactTransaction Pb Transac Swipe 2");
	}

	// Clear the list of event
	g_ListOfEvent = 0;
}
