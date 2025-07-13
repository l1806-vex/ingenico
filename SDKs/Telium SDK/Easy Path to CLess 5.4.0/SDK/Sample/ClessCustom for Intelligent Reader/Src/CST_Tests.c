/**
 * \file	CST_Test.c
 * \brief 	This file allows to test each functions available in the SDI DLL Interface (System functions and Payment functions).
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#include "CST_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


static unsigned char gs_ucTransactionType;				/*!< Generic transaction data : Transaction type. */
static char gs_ucFormattedAmountMessage[32];			/*!< Global data : message that contains the amount, currency... */

//! \brief Main menu.
static const T_CST_HELPER_MENU_ITEM MenuMain[] = {
	{STD_MESS_MENU_SYSTEM_TESTS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PAYMENT_TESTS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_MAINTENANCE_TESTS, "CU_DEFAULT.WGU"}
};

static const T_CST_HELPER_MENU_ITEM MenuSystemTests[] = {
	{STD_MESS_MENU_SYSTEM_GET_DATE_AND_TIME, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SYSTEM_SET_DATE_AND_TIME, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SYSTEM_GET_LANGUAGE, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SYSTEM_SET_LANGUAGE, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SYSTEM_GET_SUPPORTED_LANG, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SYSTEM_GET_SW_CONF, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SYSTEM_GET_SERIAL_NUMBER, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SYSTEM_GET_STATE, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SYSTEM_RESET, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SYSTEM_IS_CONNECTED, "CU_DEFAULT.WGU"}
};

static const T_CST_HELPER_MENU_ITEM MenuPaymentTests[] = {
	{STD_MESS_MENU_PAYMENT_GET_PARAMETERS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PAYMENT_ERASE_PARAMETERS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PAYMENT_WAIT_REMOVAL, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_PAYMENT_GENERIC_COMMAND, "CU_DEFAULT.WGU"}
};

static const T_CST_HELPER_MENU_ITEM MenuSwConfiguration[] = {
	{STD_MESS_MENU_SW_APPLICATIONS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SW_SYSTEM, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SW_MANAGER, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SW_DRIVERS, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SW_DLL, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_SW_ALL, "CU_DEFAULT.WGU"}
};

static const T_CST_HELPER_MENU_ITEM MenuTransactionType[] = {
	{STD_MESS_MENU_TR_TYPE_DEBIT, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TR_TYPE_CASH, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TR_TYPE_REFUND, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_TR_TYPE_CASHBACK, "CU_DEFAULT.WGU"}
};

static const T_CST_HELPER_MENU_ITEM MenuMaintenanceTests[] = {
	{STD_MESS_MENU_MAINTENANCE_LOCAL_LOADING, "CU_DEFAULT.WGU"},
	{STD_MESS_MENU_MAINTENANCE_START, "CU_DEFAULT.WGU"}
};


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


static int __Menu_SystemTests(void);
static int __Menu_PaymentTests(void);
static int __Menu_MaintenanceTests(void);

static int __Menu_GetSwConfiguration(void);

static void __CST_Tests_GetDateAndTime(void);
static void __CST_Tests_SetDateAndTime(void);
static void __CST_Tests_GetCurrentLanguage(void);
static void __CST_Tests_SetLanguage(void);
static void __CST_Tests_GetSupportedLanguages(void);
static void __CST_Tests_GetDeviceSerialNumber(void);
static void __CST_Tests_GetState(void);
static void __CST_Tests_Reset(void);
static void __CST_Tests_IsConnected(void);
static void __CST_Tests_GetParams(void);
static void __CST_Tests_WaitCardRemoval (void);
static void __CST_Tests_Generic_UserCommand (void);
static void __CST_Tests_LocalLoading(void);
static void __CST_Tests_StartMaintenance(void);

static void __CST_Tests_FormatAmount(unsigned char ucFormat,unsigned char *ucCurrency,unsigned char ucPosition,unsigned long ulAmount,char *pFormattedAmountMessage);
static int __CST_Tests_AmountEntry (const unsigned char *pCurrencyLabel, unsigned long * pAmountBin, char *pFormattedAmountMessage);
static void __CST_Tests_TransactionTypeMenuDisplay(const unsigned char *pCurrencyLabel, unsigned long * pulAmount, unsigned long * pulAmountOther, unsigned char * pucTransactionType, int * pnTransactionCashBack);
static void __CST_Tests_GetSoftwareConfiguration (const char * pTitle, const int nMask);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Gives transaction type.
//! \return The transaction type.
//! \note This function can be called after transaction type has been populated.

unsigned char CST_Tests_GiveTransactionType(void)
{
	return (gs_ucTransactionType);
}


//! \brief Gives the message to display the amount value.

char *CST_Tests_GiveAmountMessage(void)
{
	return (gs_ucFormattedAmountMessage);
}


//! \brief Main menu that allows to test each System and Payment functions of the intelligent reader

int CST_Tests_ManageMenu(void)
{
	int nChoice = 0;

	do
	{
		nChoice = HelperDisplayMenu(STD_MESS_MENU_TEST_EACH_FCT, nChoice, NUMBER_OF_ITEMS(MenuMain), MenuMain, FALSE);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:
				__Menu_SystemTests();
				nChoice = -1;
				break;

			case 1:
				__Menu_PaymentTests();
				nChoice = -1;
				break;

			case 2:
				__Menu_MaintenanceTests();
				nChoice = -1;
				break;

			default:
				break;
			}
		} 
	}while(nChoice >= 0);

	return nChoice;
}


//! \brief Menu that allows to test each System functions of the intelligent reader

static int __Menu_SystemTests(void)
{
	FILE *hPrinter;
	int nChoice;
	
	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu(STD_MESS_MENU_SYSTEM_TESTS, nChoice, NUMBER_OF_ITEMS(MenuSystemTests), MenuSystemTests, FALSE);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:
				hPrinter = fopen("PRINTER", "w-*");
				if (hPrinter != NULL)
					__CST_Tests_GetDateAndTime ();
				fclose(hPrinter);
				nChoice = -1;
				break;
			case 1:
				hPrinter = fopen("PRINTER", "w-*");
				if (hPrinter != NULL)
					__CST_Tests_SetDateAndTime ();
				fclose(hPrinter);
				nChoice = -1;
				break;
			case 2:
				hPrinter = fopen("PRINTER", "w-*");
				if (hPrinter != NULL)
					__CST_Tests_GetCurrentLanguage ();
				fclose(hPrinter);
				nChoice = -1;
				break;
			case 3:
				hPrinter = fopen("PRINTER", "w-*");
				if (hPrinter != NULL)
					__CST_Tests_SetLanguage ();
				fclose(hPrinter);
				nChoice = -1;
				break;
			case 4:
				hPrinter = fopen("PRINTER", "w-*");
				if (hPrinter != NULL)
					__CST_Tests_GetSupportedLanguages ();
				fclose(hPrinter);
				nChoice = -1;
				break;
			case 5:
				__Menu_GetSwConfiguration();
				nChoice = -1;
				break;
			case 6:
				hPrinter = fopen("PRINTER", "w-*");
				if (hPrinter != NULL)
					__CST_Tests_GetDeviceSerialNumber ();
				fclose(hPrinter);
				nChoice = -1;
				break;
			case 7:
				hPrinter = fopen("PRINTER", "w-*");
				if (hPrinter != NULL)
					__CST_Tests_GetState ();
				fclose(hPrinter);
				nChoice = -1;
				break;
			case 8: // Reset
				hPrinter = fopen("PRINTER", "w-*");
				if (hPrinter != NULL)
					__CST_Tests_Reset();
				fclose(hPrinter);
				nChoice = -1;
				break;
			case 9: // Is connected
				hPrinter = fopen("PRINTER", "w-*");
				if (hPrinter != NULL)
					__CST_Tests_IsConnected ();
				fclose(hPrinter);
				nChoice = -1;
				break;
			
			default:
				break;
			}
		}
	} while(nChoice >= 0);

	return nChoice;
}


//! \brief Menu that allows to test each Payment functions of the intelligent reader.

static int __Menu_PaymentTests(void)
{
	int nChoice;
	
	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu(STD_MESS_MENU_PAYMENT_TESTS, nChoice, NUMBER_OF_ITEMS(MenuPaymentTests), MenuPaymentTests, FALSE);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:
				__CST_Tests_GetParams();
				nChoice = -1;
				break;
			case 1:
				CST_Tests_EraseParameters();
				nChoice = -1;
				break;
			case 2:
				__CST_Tests_WaitCardRemoval();
				nChoice = -1;
				break;
			case 3:
				__CST_Tests_Generic_UserCommand ();
				nChoice = -1;
				break;
			
			default:
				break;
			}
		}
	} while(nChoice >= 0);

	return nChoice;
}


//! \brief Menu that allows to test each Maintenance functions of the intelligent reader.

static int __Menu_MaintenanceTests(void)
{
	int nChoice;
	
	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu(STD_MESS_MENU_MAINTENANCE_TESTS, nChoice, NUMBER_OF_ITEMS(MenuMaintenanceTests), MenuMaintenanceTests, FALSE);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0:
				__CST_Tests_LocalLoading();
				nChoice = -1;
				break;
			case 1:
				__CST_Tests_StartMaintenance();
				nChoice = -1;
				break;
			
			default:
				break;
			}
		}
	} while(nChoice >= 0);

	return nChoice;
}


//! \brief Allows to test SDI_System_GetSoftwareConfiguration() function.

static int __Menu_GetSwConfiguration(void)
{
	int nChoice;
	
	nChoice = 0;
	do
	{
		nChoice = HelperDisplayMenu(STD_MESS_MENU_SYSTEM_GET_SW_CONF, nChoice, NUMBER_OF_ITEMS(MenuSwConfiguration), MenuSwConfiguration, FALSE);
		if (nChoice >= 0)
		{
			switch(nChoice)
			{
			case 0: // Applications
				__CST_Tests_GetSoftwareConfiguration ("APPLICATIONS", SDI_SOFT_APPLICATIONS);
				break;
			case 1: // System
				__CST_Tests_GetSoftwareConfiguration ("OS PACK", SDI_SOFT_SYSTEM);
				break;
			case 2: // Manager
				__CST_Tests_GetSoftwareConfiguration ("MANAGER PACK", SDI_SOFT_MANAGER);
				break;
			case 3: // Drivers
				__CST_Tests_GetSoftwareConfiguration ("DRIVERS", SDI_SOFT_DRIVERS);
				break;
			case 4: // DLL
				__CST_Tests_GetSoftwareConfiguration ("DLL", SDI_SOFT_DLL);
				break;
			case 5: // ALL
				__CST_Tests_GetSoftwareConfiguration ("OS PACK", SDI_SOFT_SYSTEM);
				__CST_Tests_GetSoftwareConfiguration ("MANAGER PACK", SDI_SOFT_MANAGER);
				__CST_Tests_GetSoftwareConfiguration ("APPLICATIONS", SDI_SOFT_APPLICATIONS);
				__CST_Tests_GetSoftwareConfiguration ("DRIVERS", SDI_SOFT_DRIVERS);
				__CST_Tests_GetSoftwareConfiguration ("DLL", SDI_SOFT_DLL);
				break;
			default:
				break;
			}
		}
	} while(nChoice >= 0);

	return nChoice;
}


//
// System tests
//

//! \brief Allows to test SDI_System_GetDateAndTime() function.

static void __CST_Tests_GetDateAndTime(void)
{
	int nResult;
	unsigned char ucDate [7], ucTime [7];

	// Init variables
	memset(ucDate, 0, sizeof(ucDate));
	memset(ucTime, 0, sizeof(ucTime));

	nResult = SDI_System_GetDateAndTime(ucDate, ucTime);

	pprintf("SDI_System_GetDateAndTime:\n Return: 0x%x\n Date: %s\n Time: %s\n", nResult, ucDate, ucTime);
	ttestall(PRINTER, 0);

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}


//! \brief Allows to test SDI_System_SetDateAndTime() function.

static void __CST_Tests_SetDateAndTime(void)
{
	int nResult;
	unsigned char ucDate[]="140410", ucTime[]= "080000";

	nResult = SDI_System_SetDateAndTime(ucDate, ucTime);

	pprintf("SDI_System_SetDateAndTime:\n Return: 0x%x\n", nResult);
	ttestall(PRINTER, 0);

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}


//! \brief Allows to test SDI_System_GetCurrentLanguage() function.

static void __CST_Tests_GetCurrentLanguage(void)
{
	int nResult;
	unsigned char ucLanguage [3];

	// Init variables
	memset(ucLanguage, 0, sizeof(ucLanguage));

	nResult = SDI_System_GetCurrentLanguage(ucLanguage);

	pprintf("SDI_System_GetCurrentLanguage:\n Return: 0x%x\n Language: %s\n", nResult, ucLanguage);
	ttestall(PRINTER, 0);

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}


//! \brief Allows to test SDI_System_SetLanguage() function.

static void __CST_Tests_SetLanguage(void)
{
	int nResult;
	unsigned char ucLanguage[]="fr";

	nResult = SDI_System_SetLanguage(ucLanguage);

	pprintf("SDI_System_SetLanguage:\n Return: 0x%x\n", nResult);
	ttestall(PRINTER, 0);

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}


//! \brief Allows to test SDI_System_GetSupportedLanguages() function.

static void __CST_Tests_GetSupportedLanguages(void)
{
	int nResult;
	unsigned char ucSupportedLang[32];
	unsigned long ulNbLang;

	// Init variable
	memset(ucSupportedLang, 0, sizeof(ucSupportedLang));

	nResult = SDI_System_GetSupportedLanguages(ucSupportedLang, sizeof(ucSupportedLang), &ulNbLang);

	pprintf("SDI_System_GetSupportedLanguages:\n Return: 0x%x\n Nb: %d\n Languages: %s\n", nResult, ulNbLang, ucSupportedLang);
	ttestall(PRINTER, 0);

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//! \brief Dump the software configuration.
//! \param[in] pTitle Title of the components to be dumped.
//! \param[in] nMask Mask of thecomponent to retreive.
//!		- \ref SDI_SOFT_SYSTEM OS pack information.
//!		- \ref SDI_SOFT_MANAGER Manager pack information.
//!		- \ref SDI_SOFT_APPLICATIONS Applications information.
//!		- \ref SDI_SOFT_DRIVERS Drivers information.
//!		- \ref SDI_SOFT_DLL DLL Information.

static void __CST_Tests_GetSoftwareConfiguration (const char * pTitle, const int nMask)
{
	int nResult = SDI_STATUS_UNKNOWN;
	TLV_TREE_NODE pSoftwareInfoTree = NULL;
	TLV_TREE_NODE pComponentStructure;
	TLV_TREE_NODE pComponentInfo;
	char ucString[21];

	// Dump title
	CST_DumpData_Title (pTitle);

	// Open driver
	if (CST_DumpData_OpenOutputDriver())
	{
		// Get the software configuration
		nResult = SDI_System_GetSoftwareConfiguration(nMask, &pSoftwareInfoTree);
		
		if ((nResult == SDI_STATUS_OK) && (pSoftwareInfoTree != NULL))
		{
			// Get the first child
			pComponentStructure = TlvTree_GetFirstChild(pSoftwareInfoTree);

			while (pComponentStructure != NULL)
			{
				// Print the structure content
				pComponentInfo = TlvTree_Find(pComponentStructure, TAG_SDI_COMPONENT_NAME, 0); // Get the component name (not mandatory if M2OS or OS packs)
				if (pComponentInfo != NULL)
				{
					memcpy (ucString, TlvTree_GetData(pComponentInfo), TlvTree_GetLength(pComponentInfo));
					ucString[TlvTree_GetLength(pComponentInfo)] = '\0';
					CST_DumpData ("Name: %s", ucString);
					CST_DumpData_NewLine();
				}

				pComponentInfo = TlvTree_Find(pComponentStructure, TAG_SDI_COMPONENT_IDENTIFIER, 0); // Get the component name (not mandatory if M2OS or OS packs)
				if (pComponentInfo != NULL)
				{
					memcpy (ucString, TlvTree_GetData(pComponentInfo), TlvTree_GetLength(pComponentInfo));
					ucString[TlvTree_GetLength(pComponentInfo)] = '\0';
					CST_DumpData ("Vers: %s", ucString);
					CST_DumpData_NewLine();
				}

				pComponentInfo = TlvTree_Find(pComponentStructure, TAG_SDI_COMPONENT_CRC, 0); // Get the component name (not mandatory if M2OS or OS packs)
				if (pComponentInfo != NULL)
				{
					memcpy (ucString, TlvTree_GetData(pComponentInfo), TlvTree_GetLength(pComponentInfo));
					ucString[TlvTree_GetLength(pComponentInfo)] = '\0';
					CST_DumpData ("CRC : %s", ucString);
					CST_DumpData_NewLine();
				}

				CST_DumpData_NewLine();

				// Get the next component
				pComponentStructure = TlvTree_GetNext(pComponentStructure);
			}

			CST_DumpData_NewLine();
			CST_DumpData_NewLine();
		}
		else
		{
			// Software configuration retreival failed
			CST_DumpData ("FAILED (%02x)", nResult);
			CST_DumpData_NewLine();
		}

		CST_DumpData_CloseOutputDriver();
	}

	// If allocated, release the TLV Tree
	TlvTree_ReleaseEx (&pSoftwareInfoTree);

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////


//! \brief Allows to test SDI_System_GetDeviceSerialNumber() function.

static void __CST_Tests_GetDeviceSerialNumber(void)
{
	int nResult;
	unsigned char ucSerialNumber[9];

	// Init variable
	memset(ucSerialNumber, 0, sizeof(ucSerialNumber));

	nResult = SDI_System_GetDeviceSerialNumber(ucSerialNumber);

	pprintf("SDI_System_GetDeviceSerialNumber:\n Return: 0x%x\n Serial nb: %s\n", nResult, ucSerialNumber);
	ttestall(PRINTER, 0);

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}			


//! \brief Allows to test SDI_System_GetState() function.

static void __CST_Tests_GetState(void)
{
	int nResult;
	unsigned int nState;

	nResult = SDI_System_GetState(&nState);

	pprintf("SDI_System_GetState:\n Return: 0x%x\n State : 0x%x\n", nResult, nState);
	ttestall(PRINTER, 0);

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}


//! \brief Allows to test SDI_System_Reset() function.

static void __CST_Tests_Reset(void)
{
	int nResult;
	
	nResult = SDI_System_Reset();
	
	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}


//! \brief Allows to test SDI_System_IsConnected() function.

static void __CST_Tests_IsConnected(void)
{
	int nResult;

	nResult = SDI_System_IsConnected();

	pprintf("__CST_Tests_IsConnected:\n Return: 0x%x\n", nResult);

	if(nResult == SDI_STATUS_DISCONNECTED)
		pprintf("   DISCONNECTED\n");
	else
		pprintf("   CONNECTED\n");

	ttestall(PRINTER, 0);
}


			
//
// Tests the payment functionnalities
//


//! \brief Allows to test SDI_Payment_GetParams() function.

static void __CST_Tests_GetParams(void)
{
	TLV_TREE_NODE hTlvTreeIn;
	TLV_TREE_NODE hTlvTreeOut = NULL;
	unsigned char ucGetShaOnly;
	int nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;

	hTlvTreeIn = TlvTree_New(0);

	if (hTlvTreeIn != NULL)
	{
		ucGetShaOnly = FALSE;

		TlvTree_AddChild (hTlvTreeIn, TAG_SDSA_GET_PARAMETERS_SHA_ONLY, &ucGetShaOnly, sizeof (ucGetShaOnly));
		
		nResult = SDI_Payment_GetParams (nSDSAAppliId, hTlvTreeIn, &hTlvTreeOut);

		if (hTlvTreeOut != NULL)
		{
			CST_Parameters_DumpIdentificationLabel(hTlvTreeOut);
			CST_DumpData_DumpTlvTreeNodeWithTitle ("Get Parameters", hTlvTreeOut);
			TlvTree_ReleaseEx (&hTlvTreeOut);
		}
		
		TlvTree_ReleaseEx (&hTlvTreeIn);
	}
	else
	{
		GTL_Traces_TraceDebug ("__CST_Tests_GetParams : error when creating the TLV-Tree");
	}

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}


//! \brief Allows to test SDI_Payment_EraseParams() function.

int CST_Tests_EraseParameters (void)
{
	int nResult;

	nResult = SDI_Payment_EraseParams(nSDSAAppliId);

	//pprintf("SDI_Payment_EraseParams:\n Return: 0x%x\n", nResult);

	if(nResult == SDI_STATUS_OK)
	{
		// Reset TLVTree parameters
		CST_Parameters_InitParameters(&pTreeCurrentParam);

		if (CST_Parameters_SaveParam (pTreeCurrentParam, NULL, 0) != 0) // Save dummy TLVTree parameters in file
		{
			GTL_Traces_TraceDebug ("Erase Term save error");
			nResult = SDI_STATUS_KO;
		}
	}

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();

	return (nResult);
}


//! \brief Allows to test SDI_Payment_WaitCardRemoval() function.

static void __CST_Tests_WaitCardRemoval (void)
{
	int nResult = SDI_STATUS_UNKNOWN;
	unsigned char bTrue = 0x01;
	TLV_TREE_NODE hTlvTreeIn;
	int nEvent;
	FILE * hKeyboard;

	hTlvTreeIn = TlvTree_New(0);

	if (hTlvTreeIn != NULL)
	{
		TlvTree_AddChild(hTlvTreeIn, TAG_SDSA_WAIT_CARD_REMOVAL, &bTrue, 1);

		// Open the keyboard driver
		hKeyboard = fopen("KEYBOARD", "r");

		nResult = SDI_Payment_WaitCardRemoval (nSDSAAppliId, hTlvTreeIn, E_USER_EVENT);
		
		if(nResult == SDI_STATUS_OK)
		{
			// Scan the keyboard, check for cancel
			nResult = SDI_STATUS_ANSWER_NOT_YET_RECEIVED;
			do
			{
				// Wait for a notification or for cancel
				nEvent = ttestall(USER_EVENT | KEYBOARD, 1);
				
				if(nEvent & USER_EVENT)
				{
					nResult = SDI_Payment_GetCardRemovalResult();
				}
				if((nEvent & KEYBOARD))
				{
					if (getchar() == T_ANN) // Cancel only if red key pressed
					{
						SDI_Payment_CancelTransaction(nSDSAAppliId);
					}
				}
			}while( nResult == SDI_STATUS_ANSWER_NOT_YET_RECEIVED );
		}

		// Close the keyboard driver
		fclose (hKeyboard);

		GTL_Traces_TraceDebug ("SDI_Payment_WaitCardRemoval result = %d", nResult);

		TlvTree_ReleaseEx (&hTlvTreeIn);
	}
	else
	{
		GTL_Traces_TraceDebug ("SDI_Payment_WaitCardRemoval : error when creating the TLV-Tree");
		nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
	}

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
	else
		CST_DisplayScreen(SDSA_SCREEN_IDLE);
}


//! \brief Format the message that contains the amount, the currency according to ucFormat, ucPosition...  
//! \param[in] ucFormat : the display format
//! \param[in] ucCurrency : transaction currency
//! \param[in] ucPosition : the position of the currency
//! \param[in] ulAmount : the transaction amount
//! \param[out] pFormattedAmountMessage : the formatted message to display

static void __CST_Tests_FormatAmount(unsigned char ucFormat,unsigned char *ucCurrency,unsigned char ucPosition,unsigned long ulAmount, char *pFormattedAmountMessage)
{
  char            currency[4];
  char            separator1[2];
  char            separator2[2];
  char            position;
  int             exponent;
  unsigned long   divider;
  unsigned long   i;
  char   amount_format[51];


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
  switch(exponent)
  {
    case 1 :
      for (divider=1L,i=0L;i<(unsigned)exponent;divider*=10L,i++);
      if ((ulAmount/divider)<1000L)
      {
        sprintf(amount_format,"%lu%s%0*lu",
                (ulAmount/divider),
                separator2,
                exponent,
                (ulAmount%divider));
      }
      else
	  {
        if ((ulAmount/divider)<1000000L)
        {
          sprintf(amount_format,"%lu%s%03lu%s%0*lu",
                  ((ulAmount/divider)/1000L),
                  separator1,
                  ((ulAmount/divider)%1000L),
                  separator2,
                  exponent,
                  (ulAmount%divider));
        }
        else
	    {
          sprintf(amount_format,"%lu%s%03lu%s%03lu%s%0*lu",
                  ((ulAmount/divider)/1000000L),
                  separator1,
                  (((ulAmount/divider)/1000L)%1000L),
                  separator1,
                  ((ulAmount/divider)%1000L),
                  separator2,
                  exponent,
                  (ulAmount%divider));
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
        sprintf(amount_format,"%lu%s%0*lu",
                (ulAmount/divider),
                separator2,
                exponent,
                (ulAmount%divider));
      }
      else
	  {
        sprintf(amount_format,"%lu%s%03lu%s%0*lu",
                ((ulAmount/divider)/1000L),
                separator1,
                ((ulAmount/divider)%1000L),
                separator2,
                exponent,
                (ulAmount%divider));
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
  if (position==0)
  {
    sprintf(pFormattedAmountMessage,"%s %s",
            amount_format,
            currency);
  }
  else
  {
    sprintf(pFormattedAmountMessage,"%s %s",
            currency,
            amount_format);
  }
}


//! \brief Requests amount entry
//! \param[in] pCurrencyLabel : the currency label
//! \param[out] pAmountBin : the entered transaction amount
//! \param[out] pFormattedAmountMessage : the formatted message to display
//! \return 
//!		- TRUE if amount has been entered.
//!		- FALSE if amount entry has been cancelled.

static int __CST_Tests_AmountEntry (const unsigned char *pCurrencyLabel, unsigned long * pAmountBin, char *pFormattedAmountMessage)
{
	TAB_ENTRY_FCT TabEntry;
	unsigned long ulAmount;
	int nResult;
	unsigned char ucFormat, ucPosition;
	unsigned char CurrencyLabel[4];
	MSGinfos tMsg;
	
	// Amount entry
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
	ucPosition = 1;
	memcpy (CurrencyLabel, pCurrencyLabel, 3);

	GetMessageInfos(STD_MESS_ENTER_AMOUNT, &tMsg);
	nResult = GetAmount(ucFormat, CurrencyLabel, ucPosition, &ulAmount, (unsigned char*)tMsg.message, &TabEntry);

	if (nResult == T_VAL)
	{
		// Format the message that contains the amount, the currency according to ucFormat, ucPosition...  
		__CST_Tests_FormatAmount(ucFormat,CurrencyLabel,ucPosition,ulAmount,pFormattedAmountMessage);
		
		*pAmountBin = ulAmount;
	}

	return (nResult == T_VAL);
}

//! \brief Allows to test SDI_Payment_DoTransaction() function.

void CST_Tests_DoTransaction (void)
{
	TLV_TREE_NODE hTlvTreeIn;
	TLV_TREE_NODE hTlvTreeOut = NULL;
	T_SHARED_DATA_STRUCT *pTempStruct;

	int nPosition, cr;
	int nKernelUsed;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	unsigned char bLoopMode = FALSE;

	int nEvent = 0;
	FILE * hKeyboard;
	FILE * hCam0Task;
	FILE * hSwipeTask;
	unsigned char StatusSwipe,StatusCam0;

	int nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
	int nTransactionResult = SDI_STATUS_UNKNOWN;

	// unsigned long tListOfOuputTags[] = {TAG_EMV_AMOUNT_AUTH_NUM, TAG_EMV_TRANSACTION_CURRENCY_CODE, TAG_EMV_TRANSACTION_TYPE};
	int nTransactionCashBack;
	S_MONEY money;
	unsigned char ucTransactionCurrencyCode[2];
	int nCurrencyCode;
	unsigned long ulAmount, ulAmountOther;
	unsigned char ucBuffer[6];
	DATE Date;
	unsigned char ucTransactionDate[3];
	unsigned char ucTransactionTime[3];
	unsigned char ucTrue = 0x01;
	unsigned char ucFalse = 0x00;


	nTransactionCashBack = 0;
	ulAmountOther = 0;

	// Get the currency configured in the manager
	memset (&money, 0x00, sizeof(S_MONEY));
	PSQ_Est_money (&money);

	// Convert the transaction currency code from the manager to 2 byte numeric
	memset (ucTransactionCurrencyCode, 0x00, sizeof(ucTransactionCurrencyCode));
	ucTransactionCurrencyCode[0] = (unsigned char)(money.code[0] - '0');
	ucTransactionCurrencyCode[1] = (unsigned char)(((money.code[1] - '0') << 4) | (money.code[2] - '0'));
	
	// Convert currency code
	nCurrencyCode = ((ucTransactionCurrencyCode[0] << 8) + ucTransactionCurrencyCode[1]);

	// Save the money label (used for receipt, PIN entry...)
	CST_Term_SetMoneyLabel(money.nom);

	// Ask for amount entry
	if (!__CST_Tests_AmountEntry(money.nom, &ulAmount, gs_ucFormattedAmountMessage))
	{
		nResult = SDI_STATUS_KO;
		goto End;
	}

	if (CST_Menu_IsEnableInputTransactionType()) // If transactionType must be selected
	{
		__CST_Tests_TransactionTypeMenuDisplay(money.nom, &ulAmount, &ulAmountOther, &gs_ucTransactionType, &nTransactionCashBack);

		// Anti-bug:
		if (ulAmountOther > ulAmount)
		{			
			Helper_DisplayMessage(STD_MESS_ERROR, ERASE, HELPERS_MERCHANT_LINE_2);
			Helper_RefreshScreen(WAIT);

			gs_ucTransactionType = 0xFF; // Error
		}
	}
	else
	{
		gs_ucTransactionType = SDSA_TRANSACTION_TYPE_DEBIT;
	}

	// Error management
	if (gs_ucTransactionType == 0xFF)
		goto End;

	// Loop mode information
	bLoopMode = CST_Menu_IsTransactionLoopOn();

	do{ // bLoopMode
		hTlvTreeIn = TlvTree_New(0);

		if (hTlvTreeIn != NULL)
		{
			//////
			// Add the payment data in the input data
			//////

			// Add the transaction amount
			GTL_Convert_UlToDcbNumber(ulAmount, ucBuffer, sizeof(ucBuffer));
			TlvTree_AddChild(hTlvTreeIn, TAG_EMV_AMOUNT_AUTH_NUM, ucBuffer, sizeof(ucBuffer));
			GTL_Convert_UlToDcbNumber(ulAmountOther, ucBuffer, sizeof(ucBuffer));
			TlvTree_AddChild(hTlvTreeIn, TAG_EMV_AMOUNT_OTHER_NUM, ucBuffer, sizeof(ucBuffer));

			// Add the transaction type
			TlvTree_AddChild(hTlvTreeIn, TAG_EMV_TRANSACTION_TYPE, &gs_ucTransactionType, sizeof(gs_ucTransactionType));

			// Add the current date & time
			if (read_date(&Date) == OK)
			{
				ucTransactionDate[0] = (unsigned char)(((Date.year[0] - '0') << 4) | (Date.year[1] - '0'));
				ucTransactionDate[1] = (unsigned char)(((Date.month[0] - '0') << 4) | (Date.month[1] - '0'));
				ucTransactionDate[2] = (unsigned char)(((Date.day[0] - '0') << 4) | (Date.day[1] - '0'));

				ucTransactionTime[0] = (unsigned char)(((Date.hour[0] - '0') << 4) | (Date.hour[1] - '0'));
				ucTransactionTime[1] = (unsigned char)(((Date.minute[0] - '0') << 4) | (Date.minute[1] - '0'));
				ucTransactionTime[2] = (unsigned char)(((Date.second[0] - '0') << 4) | (Date.second[1] - '0'));

				TlvTree_AddChild(hTlvTreeIn, TAG_EMV_TRANSACTION_DATE, ucTransactionDate, sizeof(ucTransactionDate));
				TlvTree_AddChild(hTlvTreeIn, TAG_EMV_TRANSACTION_TIME, ucTransactionTime, sizeof(ucTransactionTime));
			}
			else
			{
				GTL_Traces_TraceDebug("CST_Tests_DoTransaction : Unable to read date and time");
			}

			// Add the transaction currency code
			TlvTree_AddChild(hTlvTreeIn, TAG_EMV_TRANSACTION_CURRENCY_CODE, ucTransactionCurrencyCode, sizeof(ucTransactionCurrencyCode));

			// Add the cashback information
			if(nTransactionCashBack)
				TlvTree_AddChild(hTlvTreeIn, TAG_SDSA_TRANSACTION_CASHBACK, &ucTrue, 1);
			else
				TlvTree_AddChild(hTlvTreeIn, TAG_SDSA_TRANSACTION_CASHBACK, &ucFalse, 1);

			// Add the transaction sequence counter
			CST_Batch_AddTscToTlvTree(hTlvTreeIn);

			// Add the list of tags to be returned at the end of the transaction (If not provided, default tag list will be returned).
			// TlvTree_AddChild(hTlvTreeIn, TAG_SDSA_LIST_OF_OUTPUT_TAGS, tListOfOuputTags, sizeof(tListOfOuputTags));
			
			// Specific Visa Asia: get last transaction data (date, PAN, ...)
			if(CST_VisaWave_IsVisaAsiaGuiMode())
				CST_VisaWave_GetLastTransactionData(hTlvTreeIn);

			// Open contact drivers to detect card insertion/swipe
			CST_Scan_TransacOpenDrivers();

			// Launch task to be notified when the transaction status has changed (in progress, retry, collision...)
			CST_TaskStatus_LaunchTask ();
				
			// Open the keyboard driver
			hKeyboard = fopen("KEYBOARD", "r");

			// Perform the transaction
			nResult = SDI_Payment_DoTransaction (nSDSAAppliId, hTlvTreeIn, E_USER_EVENT);

			if(nResult == SDI_STATUS_OK)
			{
				nResult = SDI_STATUS_ANSWER_NOT_YET_RECEIVED;
				// Scan the peripherals, check for cancel (keyboard, chip, swipe)
				g_ListOfEvent = 0;
				do
				{
					StatusSwipe = 0;
					StatusCam0 = 0;
					nEvent = 0;

					if(g_ListOfEvent == 0)
					{
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
					}

					// No previous events (SWIPE2 or CAM0), make a ttestall during 10ms
					if (nEvent == 0)
						nEvent = ttestall(USER_EVENT | KEYBOARD, 1);

					if(nEvent & USER_EVENT)
					{
						// A notification has been received
						nResult = SDI_Payment_GetTransactionResult(&hTlvTreeOut);
						// Save the transaction result
						nTransactionResult = nResult;
					}
					
					if((nEvent & KEYBOARD))
					{
						if (getchar() == T_ANN) // Cancel only if red key pressed
						{
							g_ListOfEvent = nEvent; // Update the event
							SDI_Payment_CancelTransaction(nSDSAAppliId);
						}
					}
					if((nEvent & CAM0) || (nEvent & SWIPE2))
					{
						g_ListOfEvent = nEvent; // Update the event
						SDI_Payment_CancelTransaction(nSDSAAppliId);
					}
				}while(nResult == SDI_STATUS_ANSWER_NOT_YET_RECEIVED);
			}

			// Close the keyboard driver
			fclose (hKeyboard);

			// Close the contact drivers
			CST_Scan_TransacCloseDrivers();

			GTL_Traces_TraceDebug ("CST_DoTransaction result = %d", nResult);

			if (hTlvTreeOut != NULL)
			{
				// Copy the transaction output data (TLV Tree) in a buffer
				pTempStruct = GTL_SharedExchange_InitLocal(32768);
				if(pTempStruct == NULL)
					goto End;

				CopyTlvTreeToDataStruct(hTlvTreeOut, pTempStruct);

				nPosition = SHARED_EXCHANGE_POSITION_NULL;

				// Get the kernel identifier that performed the transaction
				cr = GTL_SharedExchange_FindNext(pTempStruct, &nPosition, TAG_SDSA_KERNEL_IDENTIFIER, &ulReadLength, &pReadValue);
				if (cr != STATUS_SHARED_EXCHANGE_OK)
				{
					GTL_Traces_TraceDebug("CST_DoTransaction : Unable to get TAG_SDSA_KERNEL_IDENTIFIER from the kernel response (cr = %02x)", cr);
				}
				else
				{
					nKernelUsed = pReadValue[1] + (pReadValue[0] << 8);
					// Call custom section in relationship with the kernel that performed the transaction
					switch (nKernelUsed)
					{
					case SDSA_KERNEL_IDENTIFIER_PAYPASS :
						nTransactionResult = CST_PayPass_Transaction(pTempStruct, nResult);
						break;

					case SDSA_KERNEL_IDENTIFIER_PAYWAVE :
						nTransactionResult = CST_payWave_Transaction(pTempStruct, nResult);
						break;

					case SDSA_KERNEL_IDENTIFIER_VISAWAVE :
						nTransactionResult = CST_VisaWave_Transaction(pTempStruct, nResult);
						break;

					case SDSA_KERNEL_IDENTIFIER_EXPRESSPAY :
						nTransactionResult = CST_ExpressPay_Transaction(pTempStruct, nResult);
						__CST_Tests_WaitCardRemoval();
						break;

					case SDSA_KERNEL_IDENTIFIER_INTERAC :
						nTransactionResult = CST_Interac_Transaction(pTempStruct, nResult);
						break;

					case SDSA_KERNEL_IDENTIFIER_DISCOVER :
						nTransactionResult = CST_Discover_Transaction(pTempStruct, nResult);
						break;

					default:
						GTL_Traces_TraceDebug("CST_DoTransaction : Unknown value for TAG_SDSA_KERNEL_IDENTIFIER tag : %x", nKernelUsed);
						break;
					}
				}

				GTL_SharedExchange_DestroyLocal(pTempStruct);
				TlvTree_ReleaseEx (&hTlvTreeOut);
			}

			TlvTree_ReleaseEx (&hTlvTreeIn);
		}
		else
		{
			GTL_Traces_TraceDebug ("CST_Tests_DoTransaction : error when creating the TLV-Tree");
			nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
		}

		// Kill the get status task
		CST_TaskStatus_KillTask();

		// Clear the payment data
		SDI_Payment_ClearData(nSDSAAppliId);

		if(nResult == SDI_STATUS_DISCONNECTED)
			CST_ReconnectionProcess();

		// Specific post processing result (transaction cancelled by a contact event, contactless not allowed...)
		switch (nTransactionResult)
		{
		case SDI_STATUS_CONTACTLESS_NOT_ALLOWED:
			CST_DisplayScreen(SDSA_SCREEN_IDLE);
			// No AID allowed for the cless transaction (amount is greater than floor limit)
			CST_Scan_PerformContactTransaction(ulAmount, nCurrencyCode, gs_ucFormattedAmountMessage, TRUE);
			break;

		case SDI_STATUS_USE_OTHER_INTERFACE:
			// Ask to use a contact interface (contact peripherals are scanned)
			CST_DisplayScreen(SDSA_SCREEN_USE_CONTACT);
			CST_Scan_PerformContactTransaction(ulAmount, nCurrencyCode, gs_ucFormattedAmountMessage, TRUE);
			break;

		case SDI_STATUS_CANCELLED:
			CST_DisplayScreen(SDSA_SCREEN_IDLE);
			// If a contact interface was used to cancel the transaction and perform the transaction
			CST_Scan_PerformContactTransaction(ulAmount, nCurrencyCode, gs_ucFormattedAmountMessage, FALSE);
			break;

		case SDI_STATUS_CARD_NOT_SUPPORTED:
			Helper_DisplayMessage(STD_MESS_CARD_NOT_SUPPORTED, ERASE, HELPERS_MERCHANT_LINE_2);
			Helper_RefreshScreen(NOWAIT);
			CST_DisplayScreen(SDSA_SCREEN_CARD_NOT_SUPPORTED);
			break;

		default:
			// No specific processing for other transaction result
			CST_DisplayScreen(SDSA_SCREEN_IDLE);
			break;
		}

	}while (bLoopMode && (nResult != SDI_STATUS_CANCELLED) && (nResult != SDI_STATUS_NO_PARAMETER) && (nResult != SDI_STATUS_DISCONNECTED) );

End:

	// Clear the list of event
	g_ListOfEvent = 0;
}


//! \brief Allows to test SDI_Generic_UserCommand() function.

static void __CST_Tests_Generic_UserCommand (void)
{
	TLV_TREE_NODE hTlvTreeIn, hTlvTreeOut;
	unsigned char uc_Date[] = {0x10,0x04,0x23};
	int nResult;

	hTlvTreeIn = TlvTree_New(0);

	if (hTlvTreeIn != NULL)
	{
		// Add the date
		TlvTree_AddChild(hTlvTreeIn, TAG_EMV_TRANSACTION_DATE, uc_Date, sizeof(uc_Date));
		
		nResult = SDI_Generic_UserCommand(nSDSAAppliId, 1, hTlvTreeIn, &hTlvTreeOut);

		CST_DumpData_DumpTlvTreeNodeWithTitle ("__CST_Tests_Generic_UserCommand output", hTlvTreeOut);

		TlvTree_ReleaseEx (&hTlvTreeIn);
		TlvTree_ReleaseEx (&hTlvTreeOut);

		if(nResult == SDI_STATUS_DISCONNECTED)
			CST_ReconnectionProcess();
	} 
}


//
// Tests the Maintenance functionnalities
//

static void __CST_Tests_LocalLoading(void)
{
	int nResult;

	nResult = SDI_Maintenance_LocalLoading();

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}


static void __CST_Tests_StartMaintenance(void)
{
	int nResult;

	// The default application maintenance is called.
	nResult = SDI_Maintenance_Start(0, 0, NULL);

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}


//! \brief Copy a TLV Tree in a data structure.
//! \param[in] hTlvTree TLV Tree that contains data to had to the data structure.
//! \param[out] pDataStruct Data buffer that will contain the copied data.

void CopyTlvTreeToDataStruct (TLV_TREE_NODE hTlvTree, T_SHARED_DATA_STRUCT * pDataStruct)
{
	TLV_TREE_NODE pResearch;
	
	pResearch = TlvTree_GetFirstChild (hTlvTree);
	
	while (pResearch != NULL)
	{
		GTL_SharedExchange_AddTag(pDataStruct, TlvTree_GetTag (pResearch), TlvTree_GetLength(pResearch),TlvTree_GetData(pResearch));
		pResearch = TlvTree_GetNext (pResearch);
	}
}


//! \brief Copy the data in a TLV Tree.
//! \param[in] pDataStruct Data buffer that contains data to add in the TLV Tree.
//! \param[out] hOutputTlvTree Output TLV Tree containing the data.

void CopyDataStructInTLVTree (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree)
{
	int cr, nResult;
	int nPosition;
	unsigned long ulReadTag, ulReadLength;
	const unsigned char * pValue;

	cr = STATUS_SHARED_EXCHANGE_OK;
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	nResult = FALSE;

	if (hOutputTlvTree != NULL)
	{
		do
		{
			cr = GTL_SharedExchange_GetNext (pDataStruct, &nPosition, &ulReadTag, &ulReadLength, &pValue);
			if (cr == STATUS_SHARED_EXCHANGE_OK)
			{
				TlvTree_AddChild (hOutputTlvTree, ulReadTag, pValue, ulReadLength);
			}
		} while (cr == STATUS_SHARED_EXCHANGE_OK);
			
		// If end of data has not been reached
		if (cr != STATUS_SHARED_EXCHANGE_END)
			GTL_Traces_TraceDebug ("CopyDataStructInTLVTree : Error occured when parsing the shared buffer.");
	}
	else
	{
		GTL_Traces_TraceDebug ("CopyDataStructInTLVTree : hOutputTlvTree is NULL");
	}
}



//! \brief Allows to test SDI_Payment_SetGuiState() function.
//! \param[in] ulScreenToDisplay Screen identifier.

int CST_DisplayScreen (const unsigned long ulScreenToDisplay)
{
	TLV_TREE_NODE hTlvTreeIn;
	int nResult = SDI_STATUS_OK;
	unsigned char ucScreenIdentifier[4];

	// Convert the screen identifier
	GTL_Convert_UlToBinNumber (ulScreenToDisplay, ucScreenIdentifier, sizeof (ucScreenIdentifier));

	// Create a TLV-Tree
	hTlvTreeIn = TlvTree_New(0);

	if (hTlvTreeIn != NULL)
	{
		// Add the screen to display in the TLV-Tree
		TlvTree_AddChild (hTlvTreeIn, TAG_SDSA_GUI_STATE_TO_SET, ucScreenIdentifier, 4);
		
		// Call the remote application
		nResult = SDI_Payment_SetGuiState (nSDSAAppliId, hTlvTreeIn);

		if (nResult != SDI_STATUS_OK)
			GTL_Traces_TraceDebug ("CST_DisplayScreen result = %d", nResult);

		TlvTree_ReleaseEx (&hTlvTreeIn);
	}
	else
	{
		GTL_Traces_TraceDebug ("CST_DisplayScreen : error when creating the TLV-Tree");
		nResult = SDI_STATUS_NOT_ENOUGH_MEMORY;
	}

	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();

	return (nResult);
}


//! \brief Transaction Type menu management

static void __CST_Tests_TransactionTypeMenuDisplay(const unsigned char *pCurrencyLabel, unsigned long * pulAmount, unsigned long * pulAmountOther, unsigned char * pucTransactionType, int * pnTransactionCashBack)
{
	int nChoice;
	int nInputAmountOther = 0;

    *pucTransactionType = 0xFF;
    *pnTransactionCashBack = 0;

	nChoice = 0;

    do {
    	nChoice = HelperDisplayMenu(STD_MESS_MENU_TR_TYPE_TITLE, nChoice, NUMBER_OF_ITEMS(MenuTransactionType), MenuTransactionType, FALSE);

	    if (nChoice >= 0)
	    {
		    switch(nChoice)
		    {
		    case 0:
		        *pucTransactionType = SDSA_TRANSACTION_TYPE_DEBIT;
			    break;
		    case 1:
			    *pucTransactionType = SDSA_TRANSACTION_TYPE_CASH;
			    break;
		    case 2:
			    *pucTransactionType = SDSA_TRANSACTION_TYPE_REFUND;
			    break;
		    case 3:
				// For payWave, cashback transactions use the DEBIT transaction type 
				if(CST_Menu_IsVisaCashback())
					*pucTransactionType = SDSA_TRANSACTION_TYPE_DEBIT;
				else
					*pucTransactionType = SDSA_TRANSACTION_TYPE_PURCH_WITH_CASHBACK;
			    nInputAmountOther = TRUE;
			    *pnTransactionCashBack = TRUE;
			    break;
		    default:
			    *pucTransactionType = 0xFF;
			    break;
    	    }
   	    }
    } while (*pucTransactionType == 0xFF);

    if (nInputAmountOther)
    {
      // If Amount = 0
      if (*pulAmount == 0)
      {
    	  *pulAmountOther = 0; // No Amount other entry possible or must be set to 0 (Initial amount inputed must be egal to amount + amount other)
      }
      else
      {
	    char ucFormattedAmountMessage[32];

        // => amount other must inputed
		if (!__CST_Tests_AmountEntry(pCurrencyLabel, pulAmountOther, ucFormattedAmountMessage))
	    {
		    *pucTransactionType = 0xFF;
        }
      }
	}
}


//! \brief Try to reconnect when a connection error occurs.

void CST_ReconnectionProcess (void)
{
	int nResult;
	int nTime = 0;

	// Kill the get status task (if running)
	CST_TaskStatus_KillTask();
	
	GTL_Traces_TraceDebug ("CST_ReconnectionProcess, Try to connect...\n");
	
	CST_Term_ConnectAll();

	while ((nResult = SDI_System_IsConnected()) != SDI_STATUS_OK)
	{
		GTL_Traces_TraceDebug ("CST_ReconnectionProcess, connection failed!\n");
		ttestall(0,100); nTime++;
		if( nResult == SDI_STATUS_DISCONNECTED)
		{
			CST_Term_ConnectAll();
		}

		// If disconnected during more than 2 tries, display a message
		if(nTime == 2)
		{
			Helper_DisplayMessage(STD_MESS_READER, ERASE, HELPERS_MERCHANT_LINE_3);
			Helper_DisplayMessage(STD_MESS_READER_DISCONNECTED, NO_ERASE, HELPERS_MERCHANT_LINE_4);
			Helper_RefreshScreen(NOWAIT);
		}
	}

	// If disconnected during more than 2 tries, display a message
	if(nTime >= 2)
	{
		Helper_DisplayMessage(STD_MESS_READER, ERASE, HELPERS_MERCHANT_LINE_3);
		Helper_DisplayMessage(STD_MESS_READER_CONNECTED, NO_ERASE, HELPERS_MERCHANT_LINE_4);
		Helper_RefreshScreen(NOWAIT);
	}

	// Reader is connected. Set the reader date and time.
	CST_Term_SetReaderDateAndTime();

	GTL_Traces_TraceDebug ("CST_ReconnectionProcess, CONNECTED!\n");
}
