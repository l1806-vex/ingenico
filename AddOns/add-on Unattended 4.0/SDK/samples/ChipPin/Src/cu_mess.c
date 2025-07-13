/**
* \file cu_mess.c
* \brief This module contains the functions used for message management.
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
#include "TlvTree.h"
#include "cu_base.h"
#include "cu_term.h"
#include "cu_mess.h"
#include "MSGlib.h"
#include "MessagesDefinitions.h"
#include "cu_serv.h"
#include "def_tag.h"

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/
#ifdef OUTPUT_MSG_ON_COM
void CUMESS_SendMsg(char * Msg);
#endif

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

// Multilanguage management
const t_lang_code lang_table[C_NBLANGHOLDER]=
{
	{"en"    ,"ENGLISH"    ,0       },
	{"fr"    ,"FRANCAIS"   ,1       },
	{"es"    ,"ESPANOL"    ,0xFF    }    // Not supported : english messages
};

/* Messages 01 to 13 are defined in EMV96, spec for payment systems         */
/* PART III, 1.2                                                            */
//!
//! \todo User's Interface implementation :
//! Modify the tables of messages to fit your needs.
//! You may need also to create new characters.
//!

const S_TAB_ICS_CONFIG table_ics_config[] =
{
	{ICS_MESS_TERMINAL_TYPE                         ,TAG_TERMINAL_TYPE                          },
	{ICS_MESS_TERMINAL_COUNTRY_CODE                 ,TAG_TERMINAL_COUNTRY_CODE                  },
	{ICS_MESS_TERMINAL_CURRENCY                     ,TAG_TRANSACTION_CURRENCY_CODE              },
	{ICS_MESS_TERMINAL_CAPABILITY                   ,TAG_TERMINAL_CAPABILITIES                  },
	{ICS_MESS_ADD_TERMINAL_CAPABILITY               ,TAG_ADD_TERMINAL_CAPABILITIES              },
	{ICS_MESS_PSE                                   ,TAG_USE_PSE                                },
	{ICS_MESS_CARDHOLDER_CONFIRMATION               ,TAG_CUST_IS_CARDHOLDER_CONFIRMATION        },
	{ICS_MESS_PREFERRED_ORDER_OF_DISPLAY            ,TAG_CUST_IS_PREFERRED_DISPLAY_ORDER        },
	{ICS_MESS_MULTI_LANGUAGE                        ,TAG_CUST_IS_MULTILANG_SUPPORTED            },
	{ICS_MESS_REVOCATION_OF_IPK_CERT                ,TAG_CUST_IS_REVOK_SUPPORTED                },
	{ICS_MESS_DEFAULT_DDOL                          ,TAG_CUST_IS_DEFAULT_DDOL                   },
	{ICS_MESS_BYPASS_PIN_ENTRY                      ,TAG_CUST_IS_PIN_BYPASS                     },
	{ICS_MESS_GETDATA_FOR_PIN_TRY_COUNTER           ,TAG_CUST_IS_GETDATA_PIN_TRY_COUNTER        },
	{ICS_MESS_FLOOR_LIMIT_CHECKING                  ,TAG_CUST_IS_FLOOR_LIMIT_CHECKING           },
	{ICS_MESS_RANDOM_TRANSACTION_SELECTION          ,TAG_CUST_IS_RANDOM_TRANSACTION_SELECT      },
	{ICS_MESS_VELOCITY_CHECKING                     ,TAG_CUST_IS_VELOCITY_CHECKING              },
	{ICS_MESS_TRANSACTION_LOG                       ,TAG_CUST_IS_TRANSACTION_LOG                },
	{ICS_MESS_EXCEPTION_FILE                        ,TAG_CUST_IS_EXCEPTION_FILE                 },
	{ICS_MESS_FORCE_ONLINE                          ,TAG_CUST_IS_FORCED_ONLINE                  },
	{ICS_MESS_FOERCE_ACCEPTANCE                     ,TAG_CUST_IS_FORCED_ACCEPTANCE              },
	{ICS_MESS_ADVICES                               ,TAG_CUST_IS_ONLINE_ADVICE                  },
	{ICS_MESS_ISSUER_REFFERALS                      ,TAG_CUST_IS_ISSUER_REFERRAL                },
	{ICS_MESS_CARD_REFFERALS                        ,TAG_CUST_IS_CARD_REFERRAL                  },
	{ICS_MESS_BATCH_DATA_CAPTURE                    ,TAG_CUST_IS_BATCH_CAPTURE                  },
	{ICS_MESS_ONLINE_DATA_CAPTURE                   ,TAG_CUST_IS_ONLINE_CAPTURE                 },
	{ICS_MESS_DEFAULT_TDOL                          ,TAG_CUST_IS_DEFAULT_TDOL                   },
	{ICS_MESS_POS_ENTRY_MODE                        ,TAG_CUST_IS_POS_ENTRY_MODE                 },
	{ICS_MESS_POS_ENTRY_VALUE                       ,TAG_POS_ENTRY_MODE_CODE                    },
	{ICS_MESS_PINPAD                                ,TAG_CUST_IS_PINPAD                         },
	{ICS_MESS_AMOUNT_AND_PIN_ENTERED_ON_SAME_KEYPAD ,TAG_CUST_IS_AMOUNT_PIN_SAME                },
	{ICS_MESS_TRM_OVERPASS_AIP                      ,TAG_CUST_TRM_OVERPASS_AIP                  },
	{ICS_MESS_SKIP_TAC_IAC_DAFAULT                  ,TAG_CUST_IS_SKIP_DEFAULT                   },
	{ICS_MESS_SKIP_TAC_IAC_ONLINE                   ,TAG_CUST_IS_SKIP_ONLINE                    },
	{ICS_MESS_ODA                                   ,TAG_CUST_IS_ODA_PROCESSING                 },
	{ICS_MESS_ACCOUNT_TYPE                          ,TAG_CUST_IS_ACCOUNT_TYPE                   },
	{ICS_MESS_PSEALGO                               ,TAG_PSE_ALGO                               },
	{ICS_MESS_PRIOR_TAA                             ,TAG_CUST_DETECT_FAIL_PRIOR_TAA             },
	{ICS_MESS_NEVER_GENAC1                          ,TAG_CUST_CDA_NEVER_REQUEST_ARQC_1GENAC     },
	{ICS_MESS_NEVER_GENAC2                          ,TAG_CUST_CDA_NEVER_REQUEST_ONLINE_2GENAC   },
	{ICS_MESS_SUBSEQUENT_PIN_BYPASS                 ,TAG_CUST_SUBSEQUENT_BYPASS_PIN             },
	{ICS_MESS_AMOUNT_UNKNOWN_BEF_CVM                ,TAG_CUST_IS_AMOUNT_UNKNOWN_BEFORE_CVM      },
	{ICS_MESS_SELECTABLE_KERNEL                     ,TAG_CUST_IS_SELECTABLE_KERNEL				},
	{ICS_MESS_DELETABLE_TAC                         ,TAG_CUST_IS_DELETABLE_TAC					},
	{(int)NULL                                      ,0                                          }
};


const unsigned char TimeOutPINCode[] =
{
	0x17,			// 60 seconds
	0x70
};

const unsigned char TimeOutInterCar[] =
{
	0x07,			// 20 seconds
	0xd0
};

/*-------------------------------------------------------------------------*/
/* Specific constants for currency management                              */
/*-------------------------------------------------------------------------*/

/* Definition of currency configuration                                    */

const T_AppConfCurcy ct_confCurrency [L_NBCURCY] =
{
	{C_IEP_CURCY_BEF , "BEF", 2},
	{C_IEP_CURCY_NLG , "NLG", 2},
	{C_IEP_CURCY_CHF , "CHF", 2},
	{C_IEP_CURCY_USD , "USD", 2},
	{C_IEP_CURCY_BRL , "BRL", 2},
	{C_IEP_CURCY_CAD , "CAD", 2},
	{C_IEP_CURCY_AUD , "AUD", 2},
	{C_IEP_CURCY_HKD , "HKD", 2},
	{C_IEP_CURCY_NZD , "NZD", 2},
	{C_IEP_CURCY_ESP , "ESP", 0},
	{C_IEP_CURCY_FRF , "FRF", 2},
	{C_IEP_CURCY_ARS , "ARS", 2},
	{C_IEP_CURCY_ATS , "ATS", 2},
	{C_IEP_CURCY_CLP , "CLP", 2},
	{C_IEP_CURCY_CLF , "CLF", 2},
	{C_IEP_CURCY_CRC , "CRC", 2},
	{C_IEP_CURCY_HRD , "HRK", 2},
	{C_IEP_CURCY_HNL , "HNL", 2},
	{C_IEP_CURCY_INR , "INR", 2},
	{C_IEP_CURCY_IDR , "IDR", 2},
	{C_IEP_CURCY_ILS , "ILS", 2},
	{C_IEP_CURCY_LUF , "LUF", 0},
	{C_IEP_CURCY_MYR , "MYR", 2},
	{C_IEP_CURCY_MXN , "MXN", 2},
	{C_IEP_CURCY_NOK , "NOK", 2},
	{C_IEP_CURCY_PHP , "PHP", 2},
	{C_IEP_CURCY_SEK , "SEK", 2},
	{C_IEP_CURCY_THB , "THB", 2},
	{C_IEP_CURCY_TRL , "TRL", 2},
	{C_IEP_CURCY_AED , "AED", 2},
	{C_IEP_CURCY_XEU , "XEU", 2},
	{C_IEP_CURCY_EURO, "EUR", 2},
	{C_IEP_CURCY_HUF,  "HUF", 0},
	{C_IEP_CURCY_POUND,"GBP", 2},
};

/*-------------------------------------------------------------------------*/
/* Constant definitions for global parameters                              */
/*-------------------------------------------------------------------------*/

/* Terminal Capabilities :                                                 */
/* IC with contacts                                                        */
/* Plaintext PIN for ICC verification                                      */
/* Enciphered PIN for online verification                                  */
/* Static Data Authentification                                            */
/* Dynamic Data Authentification                                           */

/* Additional Terminal Capabilities :                                      */
/* goods                                                                   */
/* Numeric Keys                                                            */
/* Function Keys                                                           */
/* Print Attendant                                                         */
/* Display, attendant                                                      */


/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

MSGinfos CurrentMSG;
extern const unsigned char cu_lang[];				// Default messages in LANG


// All those following datas are reserved for a future use
// so they are useless for the moment
unsigned char ct_KernelSupportToolWare;
unsigned char ct_SystemSupportToolWare;
unsigned long ct_KernelVersion;
unsigned long ct_KernelCRC;
unsigned long ct_SystemVersion;
unsigned long ct_SystemCRC;

unsigned long ul_InputAmount;

extern int UCM_Present;

/* ========================================================================*/
/* External functions                                                      */
/* ========================================================================*/

#ifdef _SIMULPC_
// This function is used ONLY IN SIMULATION
// TransfertData copies the local messages from the PC.
// to the terminal (char *LocalMessages variable) to avoid MMU errors.
extern char * TransfertData(char * msg);
#endif

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
void CUMESS_Initialise(void)
{
	static int bInitialised = FALSE;
	char *NewMessages;     // Address of the loaded message file
	const unsigned char* pLocalMessages;

	if (bInitialised)
		return;

	bInitialised = TRUE;

#ifdef _SIMULPC_
	pLocalMessages = TransfertData((char *)cu_lang);
#else
	pLocalMessages = (const unsigned char*)cu_lang;
#endif

	trace(0, strlen("CUMESS_Initialise()\n"), "CUMESS_Initialise()\n");

	// Load the message file in memory
	NewMessages=LoadMSG("/SYSTEM/LANG.SGN");    
	if(NewMessages == NULL )
	{
		trace(0, strlen("MSG file not found :\n /SYSTEM/LANG.SGN"), "MSG file not found :\n /SYSTEM/LANG.SGN"); 
		// Local messages are used
		DefCurrentMSG((char *)pLocalMessages); // Higher priority table
	}
	else
	{
		trace(0, strlen("MSG file loaded :\n /SYSTEM/LANG.SGN"), "MSG file loaded :\n /SYSTEM/LANG.SGN"); 
		// New messages are used
		DefCurrentMSG(NewMessages);     // Higher priority table
	}

	DefDefaultMSG((char *)pLocalMessages); // If msg not found in higher priority table, this one will be used
	// Define current and default languages (English)
	DefCurrentLang(EN);
	DefDefaultLang(EN);
}

//===========================================================================
int CUMESS_GetAmount (unsigned short currency_code,
					  unsigned long *entered_amount)

{
	// Internal data declaration
	unsigned short i;
	unsigned short found;
	int            merchLang;
	TAB_ENTRY_FCT  Tab;
	unsigned char  fmtAmt;
	int            retgetamt;
	int            i_l_numMsg;

	// Retreive Terminal merchant language
	merchLang = PSQ_Give_Language();

	// Search currency in currency definition table
	i= 0;
	found = FALSE;
	while ((!found) && (i < L_NBCURCY))
	{
		found = (ct_confCurrency[i].currency == currency_code);
		if (!found)
		{
			i++;
		}
	}

	if (ct_confCurrency[i].unit == 0)
	{
		if (merchLang == C_LG_FRENCH)
		{
			fmtAmt = 3;
		}
		else
		{
			fmtAmt = 4;
		}
	}
	else
	{
		if (merchLang == C_LG_FRENCH)
		{
			fmtAmt = 0;
		}
		else
		{
			fmtAmt = 1;
		}
	};

	// Time out = 30sec.
	Tab.time_out = 30;
	// numerics, green, red, yellow keys enabled
	Tab.mask = 0;

	switch (ulTransactionType)
	{
	case CUSERV_REFUND_TRANSACTION :
		i_l_numMsg = DFT_MESS_NB_REFUND_TRANS;
		break;

	case CUSERV_CASH_TRANSACTION :
		i_l_numMsg = DFT_MESS_NB_CASH_TRANS;
		break;

	case CUSERV_CASHBACK_TRANSACTION :
		i_l_numMsg = DFT_MESS_NB_CASHBACK_TRANS;
		break;

	default :
		i_l_numMsg = STD_MESS_AMOUNT;
		break;
	}

	retgetamt = GetAmount(	fmtAmt,
								(unsigned char *)&ct_confCurrency[i].label,
								1,
								entered_amount, 
								(unsigned char *) CUMESS_Read_Message(DEFAULT_TABLE, i_l_numMsg, merchLang),
								&Tab);
                   
	if (retgetamt == T_VAL)
		ul_InputAmount = *entered_amount;
	else
		ul_InputAmount = 0;

	return (retgetamt);
}

//===========================================================================
void CUMESS_ConvertBinNUM (unsigned long BinaryValue, unsigned char *NumValue)
{
	// Internal data declaration
	unsigned long Bin;
	unsigned long rest;
	unsigned long i;

	Bin = BinaryValue;

	for (i = 0; i < 6; i++)
	{
		// first nibble
		rest = Bin - ((Bin / 10) * 10);
		NumValue [5 - i] = (unsigned char) rest;
		Bin = (Bin / 10);

		// Second nibble
		rest = Bin - ((Bin / 10) * 10);
		NumValue [5 - i] += (unsigned char) (rest << 4);
		Bin = (Bin / 10);
	}
}

#ifdef OUTPUT_MSG_ON_COM
void CUMESS_SendMsg(char * Msg)
{
    unsigned short sender;
    unsigned short receiver;
    unsigned short type;
	static   S_MESSAGE_IAM message;

    receiver = (TaskIam1*256) + MANAGER_TYPE; /* To TaskIam1           */
                                              /* Application Type M2OS */

    sender   = (TaskApplication*256) + 0x00;  /* 03 ==> M2OS task      */
                                              /* Application Type all  */
    type = 0x0;                               /* For Exemple           */

    /* envoie du message */
    message.receiver = receiver; 
    message.sender = sender;
    message.type = type;
    message.length = strlen(Msg);
    memcpy(message.value,(unsigned char *)Msg,message.length); 
    Send_Message( &message );
    
    ttestall(0,200);
}
#endif


//===========================================================================
void CUMESS_Display_Message (int xi_line, unsigned char mess_code, unsigned char who)
{
	unsigned short lg_code;
	int            merchLang;
	char *         pc_l_DisplayTxt = NULL;
	T_Bool NoMerchant_Display;
	char  msg[100];

	/*&BEGIN FT/08/4207/MA multi language display */
#ifdef _USE_UCM_
	if(UCM_Present)
		NoMerchant_Display = B_TRUE;
	else
#endif
		NoMerchant_Display = B_FALSE;
	/*&END FT/08/4207/MA multi language display */


	// if ((mess_code >= 1) && (mess_code <= C_MAX_EMV_BASIC_MESS)) Become unused with new msg management
	{
		// Display message on the cardholder display (PinPad or terminal)
		if ((who == DISPLAY_CARDHOLDER) || (who == DISPLAY_MERCHANT_CARDHOLDER))
		{
			// Display message on the cardholder's display, with the cardholder language
			CUDB_Get_cardholder_language (&lg_code);

			pc_l_DisplayTxt = CUMESS_Read_Message(STANDARD_TABLE, (int)mess_code, lg_code);
			if (CUTERIsPinpadPresent() == TRUE)
				CUTERMdisplayPPline(xi_line, pc_l_DisplayTxt, CENTER);
			else
			{
				memset(msg, 0, sizeof(msg));
				
				switch(xi_line)
				{
				case 0:
				default:
					sprintf(msg, "%s", pc_l_DisplayTxt);
					break;

				case 1:
					sprintf(msg, "\n%s", pc_l_DisplayTxt);
					break;

				case 2:
					sprintf(msg, "\n\n%s", pc_l_DisplayTxt);
					break;

				case 3:
					sprintf(msg, "\n\n\n%s", pc_l_DisplayTxt);
					break;

				}

				CUTERMdisplayLine(0, msg , CENTER, (char *)"w");
			}
		}
		
		// Display message on the merchant's display, if it's not the cardholder's one
		/*&BEGIN FT/08/4207/MA multi language display */
		if ((who == DISPLAY_MERCHANT) ||
			((who == DISPLAY_MERCHANT_CARDHOLDER) && (CUTERIsPinpadPresent() == TRUE)&& (NoMerchant_Display==B_FALSE)))
		/*&END FT/08/4207/MA multi language display */

		{
			// Display message on the merchant display, with the merchant language
			merchLang = PSQ_Give_Language();
			if (merchLang > C_NBLANGMERCH)
			{
				merchLang = 0;
			}
			pc_l_DisplayTxt = CUMESS_Read_Message(STANDARD_TABLE, mess_code, merchLang);

			memset(msg, 0, sizeof(msg));
			
			switch(xi_line)
			{
			case 0:
			default:
				sprintf(msg, "%s", pc_l_DisplayTxt);
				break;

			case 1:
				sprintf(msg, "\n%s", pc_l_DisplayTxt);
				break;

			case 2:
				sprintf(msg, "\n\n%s", pc_l_DisplayTxt);
				break;

			case 3:
				sprintf(msg, "\n\n\n%s", pc_l_DisplayTxt);
				break;

			}

			CUTERMdisplayLine(0, msg , CENTER, (char *)"w");
		}
	}

#ifdef OUTPUT_MSG_ON_COM
  // Send display information for com0 output          
  if (pc_l_DisplayTxt)
    CUMESS_SendMsg(pc_l_DisplayTxt);
#endif
}

//===========================================================================
char *CUMESS_ReadMessageReceipt(int number, int language)
{
	char * Msgptr;

	// Table number not used
	Msgptr = CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, number, language);

	return(Msgptr);
}


//===========================================================================
void CUMESS_GiveIso639Code(unsigned char * pc_x_IsoCode, unsigned short *ps_x_IdCode)
{
	int j;

	// Extract the language code associated with the ISO code
	for (j = 0; j < C_NBLANGHOLDER; j++)
	{
		if ((pc_x_IsoCode[0] == lang_table [j].iso639_code [0]) &&
			(pc_x_IsoCode[1] == lang_table [j].iso639_code [1]))
		{
			*ps_x_IdCode = (unsigned short) lang_table [j].table_id;
			break; 
			// Language is found. Process can be stopped.
		}
	}
}


//===========================================================================
char *CUMESS_Read_Message(CUMESS_TABLE_MESSAGE table, int num, int language)
// char *CUMESS_Read_Message(int num, int language)
{
	int index;
	char ac_l_iso[] = "xx";		// Unused value

	// if language code is not valid: DefDefaultLang(EN) = English will be used
	for(index=0; index<C_NBLANGHOLDER; index++)
	{
		if (lang_table[index].table_id == (unsigned char)language)
		{
			strcpy(ac_l_iso, (char*)lang_table[index].iso639_code);
			break;
		}
	}

	DefCurrentLang(ac_l_iso);

	// Test GetMessageInfos function
	GetMessageInfos(num,&CurrentMSG);

	return(CurrentMSG.message);
}


//===========================================================================
void CUMESS_Read_MsgInfos(MSGinfos * ptr_MSGtest, int num, int language)
{
	int index;
	char ac_l_iso[] = "xx"; /* Unused value */

	// if language code is not valid: DefDefaultLang(EN) = English will be used
	for(index=0; index<C_NBLANGHOLDER; index++)
	{
		if (lang_table[index].table_id == (unsigned char)language)
		{
			strcpy(ac_l_iso, (char*)lang_table[index].iso639_code);
			break;
		}
	}

	DefCurrentLang(ac_l_iso);

	// Test GetMessageInfos function
	GetMessageInfos(num, ptr_MSGtest);
}

