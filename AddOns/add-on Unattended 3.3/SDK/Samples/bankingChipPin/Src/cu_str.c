/**
* \file cu_str.c
* \brief This module contains the functions needed for magnetic stripe management.
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
#include "cu_term.h"
#include "MyTlvTree.h"
#include "cu_batch.h"
#include "cu_base.h"
#include "convert.h"
#include "gestion_param.h"
#include "cu_serv.h"
#include "cu_param.h"
#include "cu_mess.h"
#include "MessagesDefinitions.h"
#include "cu_term.h"
#include "cu_entry.h"
#include "convert.h"
#include "cu_mess.h"
#include "cu_pinen.h"
#include "cu_more.h"
#include "cu_logos.h"
#include "TlvTreeDel.h"
#include "EngineInterfaceLib.h"

//! \addtogroup Group_cu_str
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

static unsigned long entered_amount;

/* ======================================================================== */
/* Static function definitions                                              */
/* ======================================================================== */

static int Input_Amount(int bAmount, unsigned long amount, TLV_TREE_NODE *phOutputTLVTree);

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
int CUSTR_Mag_Stripe_Debit (int bValidAmount, unsigned long amount, int isFallbackAllowed,
							char *track2_buffer)
{
	// Internal data declaration
	unsigned char pan[19 + 1];
	unsigned char pan_dcb[10];
	unsigned int i,j;
	int        endPAN;
	char       ExpirationDate [5];
	char       ExpirationDate_dcb [3];
	char       ServiceCode [4];
	unsigned short lg_code;
	int rejection;
	int ICCPresent;
	int resdeb;
	unsigned char chaine [40];
	DataElement elt;
	int record_POSEM;
	unsigned short usFound;
	unsigned short currency_code = 0;
	int            g_language;
	int            unit = 0;
	int            found;

	unsigned char  currency[4];
	unsigned char  buffer[30];

	TLV_TREE_NODE  hTree;

	CUDB_Get_cardholder_language (&lg_code);
	resdeb = FALSE;
	hTree = NULL;


	// Begin

	// Extract PAN
	i= 0;
	endPAN = FALSE;
	rejection = FALSE;

	memset (pan , 0, 19 + 1);
	memset (ExpirationDate , 0, 5);
	memset (ServiceCode , 0, 4);
	memset (currency , 0, 4);

	// Get the PAN (skip the first char that is the start flag of the track)
	do
	{
		if (track2_buffer [i + 1] == 'D')
		{
			endPAN = TRUE;
		}
		else
		{
			pan [i] = track2_buffer [i + 1];
			i++;
		}
	}
	while (!endPAN && ( i < 20));

	if (endPAN)
	{
		pan [i] = 0;
		i += 2;

		// Hide the PAN
		memset (&pan[6], '*', strlen(pan) - 6 - 4);

		// Extract DATE and Service Code
		ExpirationDate [0] = track2_buffer [i++];
		ExpirationDate [1] = track2_buffer [i++];
		ExpirationDate [2] = track2_buffer [i++];
		ExpirationDate [3] = track2_buffer [i++];

		ServiceCode [0] = track2_buffer [i++];
		ServiceCode [1] = track2_buffer [i++];
		ServiceCode [2] = track2_buffer [i++];

		// Is it an ISO2 card (Service Code begins with a 2 or a 6)
		ICCPresent = FALSE;
		
		// Fallback receipt and data capture POS entry mode
		if ((ServiceCode [0] == '2') || (ServiceCode [0] == '6'))
		{
			ICCPresent = TRUE;

			if (!isFallbackAllowed)
			{
				// More than ...., between last IC introduction and magnetic stripe : reject the magnetic introduction.
				CUTERMdisplayLine(0, CUMESS_Read_Message(MAG_STRIPE_TABLE, MAGS_MESS_USE_ICC, lg_code), CENTER, (char *)"w");
				CUTERMsleep (1000);
				rejection = TRUE;
			}
			else
			{
				resdeb = TRUE;
			}
		}

		PAR_SelectMark(C_TAG_ICS0, C_TREE_ALL);

		// Fallback receipt and data capture POS entry mode
		if (rejection == FALSE)
		{
			hTree = TlvTree_New(0); 
			if (hTree != NULL)
			{
				if (Input_Amount(bValidAmount, amount, &hTree))
				{
#ifdef _USE_UCM_
					if(!UCM_Present)
#endif
					{
						j = strlen(pan);
						Aschex(&pan_dcb[0],pan,j);
						if     ((j & 0x01) == 0x01)
						{
							// pad an F at the right of data
							pan_dcb[j/2]=pan_dcb[j/2]|0x0F;
							j++;
						}
						TlvTree_AddChild(hTree, TAG_APPLI_PRIM_ACCOUNT_NB, ( unsigned char *) pan_dcb, j / 2);

						Aschex(&ExpirationDate_dcb[0],&ExpirationDate[0],4);
						ExpirationDate_dcb[2]=0x30;
						TlvTree_AddChild(hTree, TAG_APPLI_EXPIRATION_DATE, ( unsigned char *) ExpirationDate_dcb, 3);

						PAR_ReadParameter(TAG_TRANSACTION_CURRENCY_CODE, (DataElementExt *)&elt);
						TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);

						PAR_ReadParameter(TAG_TERMINAL_COUNTRY_CODE, (DataElementExt *)&elt);
						TlvTree_AddChild(hTree, elt.tag, elt.ptValue, elt.length);

						/*&BEGIN FT/06/1188/MA : improvement magstripe management      */
						// DEL_ConcatDEL (&CUMORE_outDEL, &Common_outputDEL);
						/*&END FT/06/1188/MA : improvement magstripe management        */
					}
				}
				else rejection = TRUE;
			}
			else rejection = TRUE;
		}

		// Fallback receipt and data capture POS entry mode
		if (rejection == FALSE)
		{
			// Print ticket with PAN, Expiration Date, and Service Code status
			// Trailer Ingenico
			CUPRINT_Open_Printer();
			CULOGO_Print_Ingenico();
			CUPRINT_Boundary_Line(0, 24);
			CUPRINT_Blanks_Lines(1);
			CUPRINT_Close_Printer();

			CUTERMprintLine (CUMESS_Read_Message(MAG_STRIPE_TABLE, MAGS_MESS_MAG_STRIPE_READ, lg_code));
			CUTERMprintLine (" ");
			CUTERMprintLine ((char *) pan);
			CUTERMprintLine (CUMESS_Read_Message(MAG_STRIPE_TABLE, MAGS_MESS_EXP_DATE, lg_code));
			CUTERMprintLine ((char*) ExpirationDate);
			CUTERMprintLine (CUMESS_Read_Message(MAG_STRIPE_TABLE, MAGS_MESS_SERV_CODE, lg_code));
			CUTERMprintLine ((char*) ServiceCode);

			found = PAR_ReadParameter(TAG_TRANSACTION_CURRENCY_CODE, (DataElementExt *)&elt);
			if (found)
			{
				currency_code = (elt.ptValue[0] << 8) + elt.ptValue[1];

				i = 0;
				usFound = FALSE;
				while ((!usFound) && (i < L_NBCURCY))
				{
					usFound = (ct_confCurrency[i].currency == currency_code);
					if (!usFound)
					{
						i++;
					}
					else
					{
						strcpy((char *) currency, ct_confCurrency[i].label);
						unit = ct_confCurrency[i].unit;
					}
				}
			}

			g_language = PSQ_Give_Language();

			sprintf (buffer, "%s\n", CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_AMOUNT, g_language));
			CUTERMprintLine ((char*) buffer);

			if (unit == 0)
			{
				sprintf((char *) buffer, "%8lu %s",entered_amount,currency);
			}
			else
			{
				sprintf((char *) buffer, "%6lu.%02lu %s",entered_amount/100,entered_amount%100,currency);
			}

			CUTERMprintLine ((char*) buffer);

			if (ICCPresent)
			{
				CUTERMprintLine (CUMESS_Read_Message(MAG_STRIPE_TABLE, MAGS_MESS_CHIP_PRESENT, lg_code));

				if ((!rejection))
				{
					CUTERMprintLine (CUMESS_Read_Message(MAG_STRIPE_TABLE, MAGS_MESS_LAST_CHIP_1, lg_code));
					CUTERMprintLine (CUMESS_Read_Message(MAG_STRIPE_TABLE, MAGS_MESS_LAST_CHIP_2, lg_code));
				}
				else
				{
					CUTERMprintLine(" ");
					CUTERMprintLine(" ");
				}
			}
			else
			{
				CUTERMprintLine (CUMESS_Read_Message(MAG_STRIPE_TABLE, MAGS_MESS_CHIP_ABSENT, lg_code));
			}

			// add calls to EMV Tool functionnalities
#ifdef _USE_UCM_
			// reimplementation of Dumptags and traces
			if(UCM_Present)
			{
				SetOutputCom0();
				DumpTags();
			}
			else
#endif
			{
				// Fallback receipt and data capture POS entry mode
				// Magstripe transaction shall not set POS_entry_mode
				if ((!rejection) && (isFallbackAllowed))
				{
					int found;
					int PEMValue;

					found = PAR_ReadParameter(TAG_POS_ENTRY_MODE_CODE, (DataElementExt *)&elt);

					if (found)
					{
						PEMValue = (elt.ptValue[1] << 8) + elt.ptValue[0];
						sprintf ((char* ) chaine, "POS EM %x\n", PEMValue);
					}
					else
						sprintf ((char* ) chaine, "POS EM %s\n", NONE);

					CUTERMprintLine ((char*) chaine);
				}

				CUTERMpaperFeed();

				record_POSEM = FALSE;
				if ((!rejection) && (isFallbackAllowed))
				{
					record_POSEM = TRUE;
				}
				CUBATCH_Create_MAGFinancial_Record (&hTree, record_POSEM);

				// Release local TLV tree
				TlvTree_ReleaseEx(&hTree);
			}
		}
	}

	return (resdeb);
}

//===========================================================================
int CUSTR_CheckFallback()
{
	DataElement Elt;
	int iFound, iEnded;
	int isFallbackAllowed;
	int i;
	unsigned char PSE_CMD[] = {0x00, 0xA4, 0x04, 0x00, 0x0E, 0x31, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31, 0x00};
	static const unsigned long RequiredTags[] = { TAG_NUMBER_OF_MATCHING_APP, TAG_LAST_APDU_CMD_RESPONSE }; 
	TLV_TREE_NODE hTree,hTreeCom;

	hTreeCom=NULL;
	isFallbackAllowed = TRUE;

	// Retrieve RequiredTags from EMVDC Data base
	hTree = Engine_GetDataElements(sizeof(RequiredTags) / sizeof(RequiredTags[0]), RequiredTags);

	if (hTree != NULL)
	{
		// --------------------------------------------------------------------
		// Is the card blocked ?
		iFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_LAST_APDU_CMD_RESPONSE, &Elt);
		if (iFound)
		{
			if ((Elt.ptValue [4] == 0x6A) &&
				(Elt.ptValue [5] == 0x81))
			{
				// The card is blocked, fallback not allowed
				isFallbackAllowed = FALSE;
			}
		}

		// --------------------------------------------------------------------
		// Read the number of matching application from EMVDC
		iFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_NUMBER_OF_MATCHING_APP, &Elt);
		if ((iFound) && isFallbackAllowed)
		{
			isFallbackAllowed = FALSE;
			if (Elt.ptValue[0] == 0)
			{
				// No matching application

				// Parse all the SELECT commands sent
				i = 0;
				iEnded = FALSE;
				while (!iEnded)
				{
					hTreeCom = Engine_GetCommand(i);
					iFound = CUSERV_Extract_Element_TLV_Tree(&hTreeCom, TAG_APDU_CMD, &Elt);
					if (iFound)
					{
						// Is it a select command, and not PSE ?
						if ((Elt.ptValue[0] == 0x00) &&
							(Elt.ptValue[1] == 0xA4) &&
							memcmp (Elt.ptValue, PSE_CMD, 20) != 0)
						{
							// It is a select AID command
							// Is the AID blocked ?
							iFound = CUSERV_Extract_Element_TLV_Tree(&hTreeCom, TAG_APDU_RESPONSE, &Elt);
							if (iFound)
							{
								if ((Elt.ptValue[Elt.length-2] == 0x62) &&
									(Elt.ptValue[Elt.length-1] == 0x83))
								{
									// Application blocked, magstripe can not be used
									isFallbackAllowed = FALSE;
									// !! We don't check if the card is a MasterCard
									// A specific test on the AID could be added.
								}
								else
								{
									// Application not blocked, magstripe allowed
									isFallbackAllowed = TRUE;
								}
							}
						}
					}
					else
					{
						iEnded = TRUE;
					}

					i ++;
				}
			}
			else
			{
				// One AID is selected : NO fallback
				isFallbackAllowed = FALSE;
			}
		}
		// release local TLV tree
		TlvTree_ReleaseEx(&hTree);
		TlvTree_ReleaseEx(&hTreeCom);
	}

	return isFallbackAllowed;

}

//===========================================================================
//! \brief This function returns amount tags and transaction date and time.
//! \param[in] bAmount : TRUE if the amount is already available
//! \param[in] amount : the amount if bAmount is TRUE
//! \param[out] phOutputTLVTree : output TLV tree containing amount tags and
//! transaction date and time.
//! \return 
//! - TRUE if output TLV tree built.
//! - FALSE otherwise.
//===========================================================================
static int Input_Amount(int bAmount, unsigned long amount, TLV_TREE_NODE *phOutputTLVTree)
{
	unsigned char NumAmount [6];
	// unsigned long entered_amount;
	int result;
	DataElement elt;
	unsigned char TabAmount [4];
	unsigned char heure_dcb [3];
	unsigned char date_dcb [3];
	DATE date;


	entered_amount =0;

	if (bAmount)
	{
		result = T_VAL;
		entered_amount = amount;
	}
	else
	{
		result = CUMESS_GetAmount (0x978, &entered_amount);
	}


	if ((result) && (result!=T_ANN) && (entered_amount!=0))
	{
		// Amount is valid
		// Convert in num
		CUMESS_ConvertBinNUM (entered_amount, NumAmount);

		// Store amounts in current database
		LongToChar (entered_amount, TabAmount);
		TlvTree_AddChild(*phOutputTLVTree, TAG_AMOUNT_AUTH_BIN, TabAmount, 4);

		TlvTree_AddChild(*phOutputTLVTree, TAG_AMOUNT_AUTH_NUM, NumAmount, 6);

		LongToChar (0, TabAmount);
		TlvTree_AddChild(*phOutputTLVTree, TAG_AMOUNT_OTHER_BIN, TabAmount, 4);

		// Convert in num
		CUMESS_ConvertBinNUM (entered_amount, NumAmount);

		TlvTree_AddChild(*phOutputTLVTree, TAG_AMOUNT_OTHER_NUM, NumAmount, 6);

		PAR_ReadParameter(TAG_TRANSACTION_TYPE, (DataElementExt *)&elt);
		TlvTree_AddChild(*phOutputTLVTree, elt.tag, elt.ptValue, elt.length);

		read_date(&date);
		// Date of the transaction
		Aschex(&date_dcb[0],date.year,2);
		Aschex(&date_dcb[1],date.month,2);
		Aschex(&date_dcb[2],date.day,2);

		// Time of the transaction
		Aschex(&heure_dcb[0],date.hour,2);
		Aschex(&heure_dcb[1],date.minute,2);
		Aschex(&heure_dcb[2],date.second,2);

		TlvTree_AddChild(*phOutputTLVTree, TAG_TRANSACTION_DATE, ( unsigned char *) date_dcb, 3);

		TlvTree_AddChild(*phOutputTLVTree, TAG_TRANSACTION_TIME, ( unsigned char *) heure_dcb, 3);

		return TRUE;
	}
	else
	{ 
		// amount = 0 or CANCEL
		return FALSE;
	}

	return FALSE;
}

//! @}

