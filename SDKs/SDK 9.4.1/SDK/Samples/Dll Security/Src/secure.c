/***
 * Copyright (c) 2001 Sagem Monetel SA, rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * Sagem Monetel SA has intellectual property rights relating
 * to the technology embodied in this software.  In particular, 
 * and without limitation, these intellectual property rights 
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting 
 * its use, copying, distribution, and decompilation.  
 * No part of this software may be reproduced in any form 
 * by any means without prior written authorization of 
 * Sagem Monetel.
 *
 * @Title:        SECURE.C
 * @Description:  Sample of schemes use
 * @Company:      Sagem Monetel
 * @Reference:    
 * @Comment:
 *       
 * @author        JLM
 * @version       1.0
 * @date          2006/12
 */ 

#include "sdk30.h"
#include "SEC_interface.h"
#include "schVar_def.h"
#include "tlvVar_def.h"


/******************************************************/
/*                VAR PARAMETERS TO SET               */
/******************************************************/
/* 
 FOR YOUR TESTS : INITIALIZE WITH YOUR CARD NUMBER !!!!
			CARD_NUMBER_SIGN  4bytes to define   
			VAR_NUMBER_SIGN   4bytes to define       
*/
#define CARD_NUMBER_SIGN	TO_BE_DEFINED
#define VAR_NUMBER_SIGN		TO_BE_DEFINED


/* SECRET AREA ID TO USE */
#define ID_SCR_XXX_BANK   0x0E012130

/* BANK ID TO USE */
#define ID_BANK_XXX		BK_SAGEM

/* ROOT KEY NUMBER */
#define ROOT_KEY_NO_XXX				1008

/* PIN MASTER KEY NUMBER */
#define PIN_MASTER_KEY_NO_XXX		72

/* MAC MASTER KEY NUMBER */
#define MAC_MASTER_KEY_NO_XXX		88

/* PIN KEY NUMBER */
#define PIN_KEY_NO_XXX		8

/* MAC KEY NUMBER */
#define MAC_KEY_NO_XXX		24

/*
 These constants are defined temporary, 
 */
const unsigned char ThePinKey          [DES_KEY_SIZE]  = {0xBE, 0x27, 0x2A, 0x9D, 0xB2, 0x27, 0x2F, 0xDB}; /* unciphered is "23456789" */
const unsigned char TheMacKey          [DES_KEY_SIZE]  = {0x87, 0x7D, 0xF2, 0x1F, 0xC0, 0xA5, 0x70, 0x0D}; /* unciphered is "76543210"} */
const unsigned char ThePinMasterKey    [DES_KEY_SIZE]  = {0x3B, 0x2C, 0x7C, 0x7E, 0x68, 0x29, 0xAE, 0xDA}; /* unciphered is "12345678" */
const unsigned char TheMacMasterKey    [DES_KEY_SIZE]  = {0xD1, 0x97, 0xED, 0x41, 0xE3, 0x18, 0x15, 0xA0}; /* unciphered is "87654321" */
const unsigned char TheRootKey         [TDES_KEY_SIZE+1] = {"9999999999999999"};

unsigned char G_ptResult[8];
int G_iLenResult;


void PrintPrn(const char * format,...)
{
	char newt[512];
	va_list liste;
	FILE *prn ;
	va_start(liste,format);
#ifdef __GNUC__
	vsprintf(newt,format,&liste);
#else
	vsprintf(newt,format,liste);
#endif
	prn = fopen("PRINTER","w-"); // or use printer
	fprintf(prn,"%s\n",newt);
	ttestall ( PRINTER , 300 );
	fclose(prn);
}


/** 
 * function: GetBoosterType 
 * @brief: Return booster type of terminal 
 * @author: JC. Pommaret 
 * @return: 1 for booster1, 2 for booster2, ... 
 */

static int GetBoosterType(void) 
{ 
	FILE * iapp;
	char data[3+1];

	iapp = fopen("IAPP","rw*");
	if((iapp != NULL) || (stdperif("IAPP",NULL) != NULL))
	{
		if(iapp != NULL) fclose(iapp);
		
		SystemFioctl(SYS_FIOCTL_GET_PRODUCT_CODE,data); 
		if(memcmp(data,"M35",3) > 0) 
		{ 
			return(2); 
		} 
		else          
		{ 
			return(1); 
		}
	}
	else
	{
		return(0);
	}
}

#define INTERN_BOOSTER_PRODUCT "TERMINAL"
#define EXTERN_BOOSTER_PRODUCT "PINPAD"


static int MenuSelectSecurePart (char * ptcTitle, int iNbChoice, char * tab_ptChoice[], int * pt_iIndex)
{
StructListe Menu;
int            maxx, maxy, iret, i; 
unsigned char  cr;
ENTRY_BUFFER   buf_entry;

	iret = KO;
	*pt_iIndex = 0;
	GetScreenSize (&maxy,&maxx);
	Menu.Fenetre.left = 0;
    Menu.Fenetre.top = 0;
    Menu.Fenetre.rigth = (maxx - 1);
    Menu.Fenetre.bottom = (maxy - 1);
    Menu.Fenetre.nblines = iNbChoice; 
    Menu.Fenetre.fontsize = _MEDIUM_;
    Menu.Fenetre.type = _PROPORTIONNEL_;
    Menu.Fenetre.police = 0;
    Menu.Fenetre.correct = _OFF_;
    Menu.Fenetre.offset = *pt_iIndex;
    Menu.Fenetre.shortcommand = _OFF_;   /* No Shortcut */
    Menu.Fenetre.selected = _ON_;        /* SELECT CHOICE */
    Menu.Fenetre.thickness = 2;
    Menu.Fenetre.border = _ON_;
    Menu.Fenetre.popup = _NOPOPUP_;
    Menu.Fenetre.first = *pt_iIndex;         
    Menu.Fenetre.current = *pt_iIndex;
    Menu.Fenetre.time_out = 0;
    Menu.Fenetre.titre = (unsigned char*)ptcTitle;
 
	for (i=0; i<iNbChoice; i++)
		Menu.tab[i] = (unsigned char*)tab_ptChoice [i];
    Menu.tab[iNbChoice] = NULL;
 
    G_List_Entry(&Menu);
    if ( ttestall (ENTRY, 0) == 0 )
    {
		Stop_Entry();
    }
    cr = Get_Entry(&buf_entry);
 
    if (cr == CR_ENTRY_OK)
	{
		*pt_iIndex = buf_entry.d_entry[0];
	}

	return (cr);
}

static int GetSelectSecurepart       (T_SEC_PARTTYPE * SecPart, int ibToPrint)
{
	int iret, iNbChoices, iind;
	char * tab_choice [3];

	iret = OK;
	iNbChoices = 3;
	tab_choice [0] = "PIN ENTRY";
	tab_choice [1] = "CARD READER";
	tab_choice [2] = "DATA CIPHERING";
	*SecPart = C_SEC_CIPHERING;
	if  (MenuSelectSecurePart ("SECURE PART?", iNbChoices, tab_choice, &iind) == CR_ENTRY_OK)
	{
		if (iind == 0)
			*SecPart = C_SEC_PINCODE;
		else if (iind == 1)
			*SecPart = C_SEC_CARD;
		if (ibToPrint == TRUE)
			PrintPrn (tab_choice [iind]);
	}
	else iret = KO;
	return (iret);
}

#define C_NB_PARTS		3
static T_SEC_PARTTYPE sctabtypeparts [C_NB_PARTS] = {C_SEC_PINCODE, C_SEC_CARD, C_SEC_CIPHERING};
int SetConfigSecurity     (void)
{
T_SEC_CONFIG tabConfParts[C_NB_PARTS];
	int i, iind, iret, iNbParts, ibPinpadBoost, icrChoice;
	char cBoosterType, cBoosterTypePinpad, * ptTitleSeclect;
	char * tab_choice[2];

	icrChoice = CR_ENTRY_OK;
	if (GetBoosterType () >= 2)
		cBoosterType = C_SEC_BL2;
	else
		cBoosterType = C_SEC_BL1;

	cBoosterTypePinpad = C_SEC_BL1;
	ibPinpadBoost = FALSE;
	iret = PSQ_Is_pinpad();
	if (iret != 0)
	{
		iret = PSQ_Pinpad_Value();
		switch (iret)
		{
			case PP30_PPAD:
			case PPC30_PPAD:
			case PPR30_PPAD:
			case P30_PPAD:			
				ibPinpadBoost = TRUE;
				cBoosterTypePinpad = C_SEC_BL1;
				if (iret == P30_PPAD)
					cBoosterTypePinpad = C_SEC_BL2;
				break;
			default :
			break;
		}
	}
	tab_choice [0] = EXTERN_BOOSTER_PRODUCT;
	tab_choice [1] = INTERN_BOOSTER_PRODUCT;
	for (i=0; i < C_NB_PARTS; i++)
	{
		tabConfParts [i].SecureType = sctabtypeparts [i];
		tabConfParts [i].cBoosterType = cBoosterType;
		tabConfParts [i].ptszBoosterPeripheral = IAPP_DEF_NAME;
		tabConfParts [i].cbGestResid = TRUE;
		if (ibPinpadBoost == TRUE)
		{
			switch (tabConfParts [i].SecureType)
			{
				case C_SEC_PINCODE :
					ptTitleSeclect = "PIN ENTRY KEYBOARD ?";
				break;
				case C_SEC_CARD :
					ptTitleSeclect = "CARD READER LOCATION ?";
				break;
				case C_SEC_CIPHERING :
					ptTitleSeclect = "KEY FOR DATA CIPHERING?";
				break;
				default :
					ptTitleSeclect = "SECURE TYPE ?";
				break;
			}
			switch (tabConfParts [i].SecureType)
			{
				case C_SEC_PINCODE :
				case C_SEC_CARD :
				case C_SEC_CIPHERING :
					icrChoice = MenuSelectSecurePart (ptTitleSeclect, 2, tab_choice, &iind);
					if ( (icrChoice == CR_ENTRY_OK) && (iind == 0) )
					{
						/* Using the Pinpad Booster as a secure part */
						tabConfParts [i].ptszBoosterPeripheral = IAPP_USB_NAME;
						tabConfParts [i].cBoosterType = cBoosterTypePinpad;
					}
				break;
				default :
				break;
			}
		}
		if (icrChoice != CR_ENTRY_OK)
			break; /* out of the For loop */
	}
	iNbParts = C_NB_PARTS;
	if (icrChoice == CR_ENTRY_OK)
		iret = SEC_SetConfig (iNbParts, tabConfParts);
	else
		iret = KO;
	return (iret);
}

int GetConfigSecurity	  (void)
{
	int iret, iNbParts, i;
	T_SEC_CONFIG tabConfParts[C_NB_PARTS];
	char szMess[100];

	iret = SEC_GetConfig (&iNbParts, tabConfParts);
	sprintf (szMess, "NbParts:%d", iNbParts);
	for (i=0; i < iNbParts; i++)
	{
		switch ( (int) tabConfParts[i].SecureType )
		{
				case C_SEC_PINCODE :
					strcat (szMess, "\n-PIN ENTRY: ");
					break;
				case C_SEC_CARD :
					strcat (szMess, "\n-CARD READER: ");
					break;
				case C_SEC_CIPHERING :
					strcat (szMess, "\n-CIPHERING: ");
					break;
				default:
					sprintf (szMess, "%s\n-SecurePart:%d ", szMess, tabConfParts[i].SecureType);
		}
		if ( memcmp (tabConfParts [i].ptszBoosterPeripheral, IAPP_USB_NAME, strlen(IAPP_USB_NAME)) == 0)
			strcat (szMess, EXTERN_BOOSTER_PRODUCT);
		else
			strcat (szMess, INTERN_BOOSTER_PRODUCT);
	}
	PrintPrn (szMess);

	return (iret);
}

/** 
 * function: IsPinEntryOnPinpad 
 * @brief: Return TRUE if PinEntry is Pinpad 
 * @return: TRUE PinEntry on Pinpad /FALSE PinEntry on terminal
 */
int IsPinEntryOnPinpad	  (void)
{
	int iret, i, iNbParts;
	T_SEC_CONFIG tabConfParts[C_NB_PARTS];

	iret = SEC_GetConfig (&iNbParts, tabConfParts);
	if (iret == OK)
	{
		iret = FALSE; /* No PinEntry on pinpad by default */
		for (i=0; i < iNbParts; i++)
		{
			if (tabConfParts[i].SecureType == C_SEC_PINCODE)
			{
				if ( memcmp (tabConfParts [i].ptszBoosterPeripheral, IAPP_USB_NAME, strlen(IAPP_USB_NAME)) == 0)
					iret = TRUE; /* Pinpad is secure part for PinEntry */
				break; /* to go out the for loop */
			}
		}
	}
	else
		iret = FALSE; /* No PinEntry on pinpad by default */

	return (iret);
}

int ListSecretAreas       (void)
{
	T_SEC_PARTTYPE SecPart;
	int iret, iNbId, tabList [10], i;
	char szMess[80], szTemp[10];

	iret = GetSelectSecurepart (&SecPart, TRUE);
	if  (iret == OK)
	{
		iret = SEC_listSecureId (SecPart, &iNbId, tabList);
		if (iret == OK)
		{
			strcpy (szMess, "Id:");
			for (i=0; i< iNbId; i++)
			{
				sprintf (szTemp, " %x", tabList[i]);
				strcat (szMess, szTemp);
			}
			PrintPrn (szMess);
		}
	}
	return (iret);
}

int CreateSecretAreas     (void)
{
	T_SEC_PARTTYPE SecPart;
	int iret;

	iret = GetSelectSecurepart (&SecPart, TRUE);
	if  (iret == OK)
	{
		iret = SEC_CreateSecretArea (SecPart, (SEG_ID) ID_SCR_XXX_BANK,  
							 CARD_NUMBER_SIGN, VAR_NUMBER_SIGN);
	}
	return (iret);
}


int FreeSecret         (void)
{
	char * tab_choice [2];
	int iNbChoices, iret, iind;
	T_SEC_PARTTYPE SecPart;
	T_SEC_DATAKEY_ID stKeyId;

	iret = GetSelectSecurepart (&SecPart, FALSE);
	iNbChoices = 2;
	tab_choice [0] = "YES";
	tab_choice [1] = "NO";
	if  ( (iret == OK) && 
		(MenuSelectSecurePart ("TO FREE WHOLE AREA?", iNbChoices, tab_choice, &iind) == CR_ENTRY_OK) )
	{
		if (iind == 0)
		{
			/* To free Whole secret area */
			stKeyId.iSecretArea = ID_SCR_XXX_BANK;
			stKeyId.cAlgoType = 0;
			stKeyId.usNumber = 0;
			stKeyId.uiBankId = 0;
			iret = SEC_FreeSecret (SecPart, &stKeyId);
		}
		else
		{
			if (SecPart == C_SEC_PINCODE)
			{
				/* To free PIN Master Key */
				stKeyId.iSecretArea = ID_SCR_XXX_BANK;
				stKeyId.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
				stKeyId.usNumber = PIN_MASTER_KEY_NO_XXX;
				stKeyId.uiBankId = ID_BANK_XXX;
				iret = SEC_FreeSecret (SecPart, &stKeyId);
				if (iret == OK)
				{
					/* To free PIN Key */
					stKeyId.iSecretArea = ID_SCR_XXX_BANK;
					stKeyId.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
					stKeyId.usNumber = PIN_KEY_NO_XXX;
					stKeyId.uiBankId = ID_BANK_XXX;
					iret = SEC_FreeSecret (SecPart, &stKeyId);
				}
			}
			else if (SecPart == C_SEC_CIPHERING)
			{
				/* To free MAC Master Key */
				stKeyId.iSecretArea = ID_SCR_XXX_BANK;
				stKeyId.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
				stKeyId.usNumber = MAC_MASTER_KEY_NO_XXX;
				stKeyId.uiBankId = ID_BANK_XXX;
				iret = SEC_FreeSecret (SecPart, &stKeyId);
				if (iret == OK)
				{
					/* To free MAC Key */
					stKeyId.iSecretArea = ID_SCR_XXX_BANK;
					stKeyId.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
					stKeyId.usNumber = MAC_KEY_NO_XXX;
					stKeyId.uiBankId = ID_BANK_XXX;
					iret = SEC_FreeSecret (SecPart, &stKeyId);
				}
			}
		}
	}

	return (iret);
}

static void SetRootKeyId (T_SEC_DATAKEY_ID * ptstRootKey)
{
		ptstRootKey->iSecretArea = ID_SCR_XXX_BANK;
		ptstRootKey->cAlgoType   = TLV_TYPE_KTDES; /* This ROOT key is a TDES Key */
		ptstRootKey->usNumber    = ROOT_KEY_NO_XXX;
		ptstRootKey->uiBankId    = ID_BANK_XXX;
}

int LoadRootKey			(void)
{
	T_SEC_PARTTYPE SecPart;
	int iret, iUsage;
	T_SEC_DATAKEY_ID stKey;

	iret = OK;
	iret = GetSelectSecurepart (&SecPart, FALSE);
	if  (iret == OK)
	{
		SetRootKeyId (&stKey);
		iUsage = CIPHERING_KEY; /* Key to cipher PIN keys and MAC keys */
		iret = SEC_LoadKey (SecPart,  
					       NULL, &stKey, (unsigned char*) &TheRootKey, iUsage);
		if (iret != OK)
			PrintPrn ("Use SKMT/SKMT2 tool to load the Root Key");
	}
	return (iret);
}

int LoadPinKeys			(void)
{
	T_SEC_PARTTYPE SecPart;
	int iret, iUsage;
	T_SEC_DATAKEY_ID stMasterKey, stKey, stRootKey;

	SecPart = C_SEC_PINCODE;
	iret = SEC_isSecretArea (SecPart, (SEG_ID) ID_SCR_XXX_BANK);
		if ( iret == OK )
		{
			/* Ciphering Key is the Root Key */
			SetRootKeyId (&stRootKey);

			/* PIN Master Key to load */
			stMasterKey.iSecretArea = ID_SCR_XXX_BANK;
			stMasterKey.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
			stMasterKey.usNumber = PIN_MASTER_KEY_NO_XXX;
			stMasterKey.uiBankId = ID_BANK_XXX;
			iUsage = CIPHERING_KEY; /* Key to cipher PIN keys */
			iret = SEC_LoadKey (SecPart,  
								&stRootKey, &stMasterKey, (unsigned char*) &ThePinMasterKey, iUsage);
			if (iret == OK)
			{
				/* PIN Key to load */
				stKey.iSecretArea = ID_SCR_XXX_BANK;
				stKey.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
				stKey.usNumber = PIN_KEY_NO_XXX;
				stKey.uiBankId = ID_BANK_XXX;
				iUsage = CIPHERING_PIN; /* Key to cipher PIN */
				iret = SEC_LoadKey (SecPart,  
									&stMasterKey, &stKey, (unsigned char*) &ThePinKey, iUsage);
			}
		}
		else
			PrintPrn ("Use SKMT/SKMT2 tool to load the Root Key");
	
	return (iret);
}

int LoadMACKeys			(void)
{
	T_SEC_PARTTYPE SecPart;
	int iret, iUsage;
	T_SEC_DATAKEY_ID stMasterKey, stKey, stRootKey;

	SecPart = C_SEC_CIPHERING;
	iret = SEC_isSecretArea (SecPart, (SEG_ID) ID_SCR_XXX_BANK);
	if  (iret == OK)
	{
			/* Ciphering Key is the Root Key */
			SetRootKeyId (&stRootKey);

			/* MAC Master Key to load */
			stMasterKey.iSecretArea = ID_SCR_XXX_BANK;
			stMasterKey.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
			stMasterKey.usNumber = MAC_MASTER_KEY_NO_XXX;
			stMasterKey.uiBankId = ID_BANK_XXX;
			iUsage = CIPHERING_KEY; /* Key to cipher MAC keys */
			iret = SEC_LoadKey (SecPart,  
								&stRootKey, &stMasterKey, (unsigned char*) &TheMacMasterKey, iUsage);
			if (iret == OK)
			{
				/* MAC Key to load */
				stKey.iSecretArea = ID_SCR_XXX_BANK;
				stKey.cAlgoType = TLV_TYPE_KDES; /* This key is a DES Key */
				stKey.usNumber = MAC_KEY_NO_XXX;
				stKey.uiBankId = ID_BANK_XXX;
				iUsage = CIPHERING_DATA; /* Key to cipher data CBC/ECB */
				iret = SEC_LoadKey (SecPart,  
									&stMasterKey, &stKey, (unsigned char*) &TheMacKey, iUsage);
			}
	}
	else
		PrintPrn ("Use SKMT/SKMT2 tool to load the Root Key");
	
	return (iret);
}

int PinEntry			(void)
{
	unsigned int Key;
	unsigned char EndEnterPIN=FALSE;
	unsigned int Indice, Column, Line;
	int ihid_key, ibToContinue;
	unsigned int uiEventToWait;
	int iret;
	unsigned char ucdataout;
	char 	szpinpad[20];
	T_SEC_ENTRYCONF stEntryConfig;
	int ibPinpadBoost;


	Column= 1; Line= 1;
	EndEnterPIN= FALSE;
	Indice= 0;
	szpinpad [0] = 0;
	

	ibPinpadBoost = IsPinEntryOnPinpad ();
	if (!ibPinpadBoost)
		printf("\x1b Input your code");
	else
	{
			PPS_firstline ();
			PPS_Display ("Enter your code?"); 
	}


	// timeOut first char: 6000 ms, other 60000 ms, HidKey : 0x2A
	// get Pin ( 4 to 10 digits)
	PrintPrn("TestGetPinCode: 4 to 10 digits, timeout: 6s, 60s");
	ihid_key = 0x2A;
	stEntryConfig.ucEchoChar = (unsigned char) ihid_key;
	stEntryConfig.ucMinDigits = 4;
	stEntryConfig.ucMaxDigits = 10;
	stEntryConfig.iFirstCharTimeOut = 6000;
	stEntryConfig.iInterCharTimeOut = 60000;
	iret = SEC_PinEntryInit (&stEntryConfig, C_SEC_PINCODE);
	ibToContinue = TRUE;
	if (!ibPinpadBoost)
		uiEventToWait = 0;
	else
		uiEventToWait = KEYBOARD; /* waiting event EFT keyboard while Pinpad Entry*/
	if (iret == OK)
	{
		while(EndEnterPIN != TRUE)
		{

			iret = SEC_PinEntry (&uiEventToWait,
						&ucdataout, &ibToContinue);
			if (iret == OK)
			{
				Key = ucdataout;
				if (!ibPinpadBoost)
					uiEventToWait = 0;
				else
					uiEventToWait = KEYBOARD; /* waiting event EFT keyboard */
				if (Key == (unsigned int) ihid_key)
				{
					if (Indice < MAX_PIN_CODE_SIZE) {
						if (Indice == 0) {
							if (!ibPinpadBoost)
							{
								gotoxy(Line, Column);
								printf("               ");
							}
							else
							{
								PPS_newline ();
								PPS_clearline ();
								PPS_Display ("               "); 
								szpinpad[0] =0;
							}
						}
						if (!ibPinpadBoost)
						{
							gotoxy(Line, Column+Indice); printf("%c", Key);
						}
						else
						{
							szpinpad[Indice] = Key;
							szpinpad[Indice+1] = 0;
							PPS_clearline ();
							PPS_Display (szpinpad); 
						}
						Indice++;
					} else {
						EndEnterPIN = TRUE; /* to stop */
					}
				}
				else
					switch (Key) {
					case 0x00: /* TimeOut */
					case 0x01: /* Response to stop the PinEntry */
					break;
					case T_VAL :
//						PrintDebug(" PIN valid(%d key)\n", Indice); 
					break;
					case T_ANN:
//						PrintDebug(" CANCEL Key for Pin Code\n"); 
					break;
					case T_CORR:
						if (Indice!=0) {
							Indice--;
							if (!ibPinpadBoost)
							{
								gotoxy(Line, Column+Indice); printf(" ");
							}
							else
							{
								PPS_clearline ();
								szpinpad[Indice] = 0;
								PPS_Display (szpinpad); 
							}
						}
					break;
					}
			}
			else if (iret == ERR_TIMEOUT)
			{
				EndEnterPIN = TRUE;
			}
			else
			{
					EndEnterPIN = TRUE;
			}

			if (ibToContinue  == FALSE)
				EndEnterPIN = TRUE; /* End of while */
			else if (EndEnterPIN == TRUE)
			{
					ibToContinue = FALSE; /* To stop the PIN Entry*/
					EndEnterPIN = FALSE; /* in the loop of while */
			}
		}
	}

	if (ibPinpadBoost)
		PPS_clear_display();

	return (iret);			
}

int EncipherPin			(void)
{
	int iret, iFormat;
static const unsigned char ThePanIso[8]            = {0x12, 0x34, 0x56, 0x78, 0x90, 0x98, 0x76, 0x54};
	unsigned int uiLengthOut;
	T_SEC_PARTTYPE SecPart;
	T_SEC_DATAKEY_ID stKey;

	/* Format 0 DES                              */
	/* Ciphered Result : DF 71 88 DB E9 02 4C 95 */
	/* With Input Pin  : 1234                    */
	/* ThePinKey  Hexa : 32 33 34 35 36 37 38 39 */
	/* Pan[8] Hexa     : 12 34 56 78 90 98 76 54 */
	/*********************************************/
	SecPart = C_SEC_PINCODE; /* Secure part used to store the PIN key */
	stKey.iSecretArea = ID_SCR_XXX_BANK;
	stKey.cAlgoType = TLV_TYPE_KDES; /* PIN key is a DES Key */
	stKey.usNumber = PIN_KEY_NO_XXX;
	stKey.uiBankId = ID_BANK_XXX;
	iFormat = ISO9564_F0_DES;
	iret = SEC_Iso9564 (SecPart, &stKey, iFormat, (unsigned char *) ThePanIso,
							 &G_ptResult[0], &uiLengthOut);
	if (iret == OK) 
		G_iLenResult = uiLengthOut;
	return (iret);
}


int MacCalculation		(void)
{
	int iret;
static const unsigned char tabICV[8]            = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char tabinput [8*8];
	T_SEC_DATAKEY_ID stKey;

	/* MAC DES                                   */
	/* Ciphered Result : D5 C2 92 14 61 C1 B1 39 */
	/* With Input data : 05 05 ... 05 (64 bytes) */
	/* ICV             : 00 00 00 00 00 00 00 00 */
	/*********************************************/
	stKey.iSecretArea = ID_SCR_XXX_BANK;
	stKey.cAlgoType = TLV_TYPE_KDES; /* MAC key is a DES Key */
	stKey.usNumber = MAC_KEY_NO_XXX;
	stKey.uiBankId = ID_BANK_XXX;
	memset (tabinput, 0x05, sizeof(tabinput));
	iret = SEC_ComputeMAC (&stKey, (unsigned char *) tabinput, sizeof(tabinput),
							(unsigned char *) tabICV, G_ptResult);
	if (iret == OK) 
		G_iLenResult = 8;

	return (iret);
}

