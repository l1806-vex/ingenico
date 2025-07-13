/**
* \file cu_receipt.c
* \brief This module contains the functions needed to print a receipt.
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

#define _NEW_DESIGN_								// new design for POS ticket

/* ======================================================================== */
/* Include files                                                            */
/* ======================================================================== */

#include "SDK30.H"
#include "_emvdctag_.h"
#include "del_lib.h"
#include "MyTlvTree.h"
#include "cu_base.h"								// to use CUDB_Get_cardholder_language
#include "cu_term.h"								// to use many types and many functions
#include "cu_batch.h"								// to use the type T_CUBATCH_record
#include "cu_mess.h"								// to use messages
#include "cu_serv.h"
#include "cu_entry.h"
#include "MessagesDefinitions.h"
#include "convert.h"								// to use CharToShort
#include "cu_logos.h"								// to print logos
#include "_emvdctag_.h"
#include "cu_receipt.h"
#include "cu_entry.h"
#include "EngineInterfaceLib.h"
#include "cu_param.h"
#include "gestion_param.h"

#ifdef _USE_UCM_
#include "ucmtelium.h"
#include "ucmhostdll.h"
#include "ucmclib.h"
#endif

//! \addtogroup Group_cu_receipt
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define LOST_TIME_IN_BOOSTER								97			// the time lost into the booster
																		// For security reasons, we can't have any informations about the command
																		// send from the booster to the card in order to present the encipherd PIN
																		// This time was evaluated by a spy hardware. An average is 970 ms.


// All transaction's steps
#define APPLICATION_SELECTION								0x01
#define INITIATE_APPLICATION_PROCESSING						0x02
#define OFFLINE_DATA_AUTHENTICATION							0x03
#define PROCESSING_RESTRICTIONS								0x04
#define CARDHOLDER_VERIFICATION								0x05
#define TERMINAL_RISK_MANAGEMENT							0x06
#define ACTION_ANALYSIS										0x07
#define ONLINE_PROCESSING									0x08
#define ISSUER_TO_CARD_SCRIPT_PROCESSING					0x09
#define COMPLETION											0x0A
#define TRANSACTION_RECEIPT									0x10
#define ERROR_COMMAND_UNKNOWN								0xFF

// Masks for Transaction Flag Status
#define INIT_TFS											0x00000000

#define APPLICATION_SELECTION_IS_PERFORMED					0x00000001
#define SELECTION_METHOD_IS_DSM								0x00000002
#define SELECTION_METHOD_IS_ESM								0x00000004
#define FIRST_SELECT_IS_PERFORMED							0x00000008
#define FINAL_SELECT_IS_PERFORMED							0x00000010
#define INITIATE_APPLICATION_IS_PERFORMED					0x00000020

#define OFFLINE_DATA_AUTHENTICATION_IS_TO_BE_PERFORMED		0x00000100
#define OFFLINE_DATA_AUTHENTICATION_IS_PERFORMED			0x00000200
#define OFFLINE_DATA_AUTHENTICATION_IS_SDA					0x00000400
#define OFFLINE_DATA_AUTHENTICATION_IS_DDA					0x00000800
#define OFFLINE_DATA_AUTHENTICATION_IS_CDA					0x00001000

#define CARDHOLDER_VERIFICATION_IS_TO_BE_PERFORMED			0x00010000
#define CARDHOLDER_VERIFICATION_IS_PERFORMED				0x00020000
#define PLAINTEXT_PIN_IS_TO_BE_PERFORMED					0x00040000
#define ENCIPHERED_PIN_IS_TO_BE_PERFORMED					0x00080000
#define ONLINE_PIN_IS_TO_BE_PERFORMED						0x00100000

#define ACTION_ANALISYS_IS_PERFORMED						0x00010000
#define TERMINAL_RISK_MANAGEMENT_IS_TO_BE_PERFORMED			0x00020000
#define TERMINAL_RISK_MANAGEMENT_IS_PERFORMED				0x00040000
#define ONLINE_PROCESSING_IS_PERFORMED						0x00080000

// Cryptogram Generated
#define MASK_CRYPTOGRAM										0xC0

// Keys
#define CERTIFICATE_AUTHORITY								0x00
#define ISSUER_PUBLIC_KEY									0x01
#define ICC_PUBLIC_KEY										0x02

// AIP
#define OFFLINE_SDA_IS_SUPPORTED							0x40
#define OFFLINE_DDA_IS_SUPPORTED							0x20
#define COMBINED_DDA_GENERATE_AC_SUPPORTED					0x02

#define STATUS_TR_APPROVED									0
#define STATUS_TR_DECLINED									1
#define STATUS_TR_CANCELLED									2
#define STATUS_TR_CARD_ERROR								3
#define STATUS_TR_PROCESSING_ERROR							4
#define STATUS_TR_REFUND_APPROVED							5


/* Missing font addition */
#define _pHEIGHT_ "_pHEIGHT_";


/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

//! \brief This enumerator defines the states when reading APDU commands stored in EMVDC data base.
typedef enum {
	IS_DONE,												//!< All the APDU command have been read.
	IS_IN_PROGRESS,											//!< The reading of an APDU command is in progress.
	IS_NOT_AVAILABLE										//!< No APDU command is stored.
} t_process;

//! \brief This enumerator defines the alignement for the text to print.
typedef enum {
	ALIGN_LEFT =    0,										//!< Text alignement on the left.
	ALIGN_CENTER =  1,										//!< Text alignement on the center.
	ALIGN_RIGHT =   2										//!< Text alignement on the right.
} t_align;

//! \brief This enumerator defines the printing levels.
typedef enum {
	L0 =    0,												//!< Level 0 of printing. (condensed mode).
	L1 =    1,												//!< Level 1 of printing. (normal mode).
	L2 =    2,												//!< Level 2 of printing. (double height mode).
	L3 =    3,												//!< Level 3 of printing. (double width mode).
	L4 =    4												//!< Level 4 of printing. (bold mode).
} t_level;

//! \brief This enumerator defines the application selection method.
typedef enum {
	DIRECTORY_SELECTION_METHOD               = 0x01,		//!< The method is directory selection.
	EXPLICIT_SELECTION_METHOD                = 0x02,		//!< The method is explicit selection.
	CARD_IS_BLOCKED_OR_COMMAND_NOT_SUPPORTED = 0x04,		//!< The card is blocked or the command is not supported.
	APPLICATION_IS_BLOCKED                   = 0x08,		//!< The application is blocked.
	ERROR_RESPONSE_UNKNOWN                   = 0xFF			//!< Unknown response of the card.
} Selection_Method;

//! \brief This enumerator defines the offline data authentication modes.
typedef enum {
	IS_NOT_SUPPORTED =    0,		//!< The offline data authentication is not supported.
	IS_SDA,							//!< The mode is static data authentication.
	IS_DDA,							//!< The mode is dynamic data authentication. This mode offers fraud protection. The card generates a RSA signature using transaction-specific data for validation by the terminal.
	IS_CDA							//!< The mode is combined dynamic data authentication / application cryptogram generation.
} t_oda;

//! \brief This enumerator defines the different cryptograms.
typedef enum {
	CRYPTO_AAC  = 0x00,				//!< Application authentication cryptogram. An application cryptogram generated when declining a transaction.
	CRYPTO_TC   = 0x40,				//!< Transaction certificate. An application cryptogram generated when accepting a transaction.
	CRYPTO_ARQC = 0x80				//!< Application request cryptogram. An application cryptogram generated when requesting online authorization.
} t_cryptogram;

//! \brief This enumerator defines the different presentation modes of pin code.
typedef enum {
	P_PLAINTEXT_PIN,				//!< The pin code is presented in plain text.
	P_ENCIPHERED_PIN,				//!< The pin code is presented enciphered.
	P_ONLINE_PIN,					//!< The pin code is presented online.
	P_NO_PIN						//!< No method is used.
} t_pin;

//! \brief Definition of transaction flag status.
typedef unsigned int    TFS;

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

/* ======================================================================== */
/* Extern variable declarations                                             */
/* ======================================================================== */

#ifdef _TOOLWARE_
extern unsigned long        ulMMI_amount;
extern unsigned long        ulMMI_account_type;
extern unsigned long        ulMMI_langue;
extern unsigned long        ulMMI_selappli;
extern unsigned long        ulMMI_force_OLP;
extern unsigned long        ulMMI_force_CAA;
extern unsigned long        ulMMI_force_COMP;
extern unsigned long        ulMMI_pin_on_line;
extern unsigned long        ulMMI_pin_off_line;
extern unsigned long        ulHOST_comm;
extern unsigned long        ulMMI_ticket;
extern unsigned long        ulBegin_transaction;
extern unsigned long        ulEnd_transaction;
#endif /* _TOOLWARE_ */

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

#ifdef _TOOLWARE_
static unsigned long    ulBegin_computation;
/* static */ unsigned long    ulEnd_computation;
static unsigned long    ulCard;
static unsigned long    ulTerminal;
#endif /* _TOOLWARE_ */

char * ptr_PrinterMode;

int    g_language;
FILE   *g_pPrinter;
TFS    g_TFS;

/* ======================================================================== */
/* Static function definitions                                              */
/* ======================================================================== */
static void print_tail(void);
static void CUPRINT_String_XT(const unsigned char *string, const t_align align, const t_level level);
static void CUPRINT_Double_String(const unsigned char *left_string, const unsigned char *right_string, const t_level level);
static void CUPRINT_Top_Frame(const short offset, const short lenght);
static void CUPRINT_Bottom_Frame(const short offset, const short lenght);
static void CUPRINT_Top_Frame_String(const short offset, const short lenght, const unsigned char *string, const t_align align);
static void CUPRINT_String_Frame(const short offset, const short lenght, const unsigned char *string, const t_align align);
static void CUPRINT_Double_String_Frame(const short offset, const short lenght, const unsigned char *left_string, const unsigned char *right_string);
static void CUPRINT_Paper_Feed(void);

#ifdef _TOOLWARE_
//   Functions for toolware
static void CUPRINT_Data(const unsigned char *label, const unsigned char *value, const t_level level);
static void print_header(void);
static void card_features(void);
static void transaction_features(void);
static void transaction_flow_analysis(void);
static void define_step(const DataElement *request, unsigned char *step);
static void print_statistics(const unsigned char step, const unsigned long terminal_time, const unsigned long card_time, const unsigned long extra_time, const unsigned char nb_commands, const unsigned char * AdditionnalText, const unsigned long Additionnaltime);
static Selection_Method get_selection_method(const DataElement *response);
#endif /* _TOOLWARE_ */

/* ======================================================================== */
/* Local function implementation (Private)                                  */
/* ======================================================================== */

#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function converts a tick number, given as input parameter, in time.
//! \param[in] ulTicks : tick number to convert.
//! \param[in] ulBase : time base.
//! \return the time corresponding to the tick number, in time base unit.
//===========================================================================
static unsigned long TimeCounter_ConvertTicksToTime(unsigned long ulTicks, unsigned long ulBase)
{
	unsigned long long ullTime;

	ullTime = ((((unsigned long long)ulTicks) * ulBase) + 16384) / 32768;
	if (ullTime > 0xffffffff)
	{
		// Overflow
		ullTime = 0xffffffff;
	}

	return (unsigned long)ullTime;
}
#endif

//===========================================================================
void CUPRINT_Open_Printer(void)
{
	// Bad value
	g_pPrinter = (FILE*)NULL;

	// Call UCM service
#ifdef _USE_UCM_
	if(UCM_Present)
	{
		if (iLIBUCM_Print_Open(UCMC_PRINT,"w-") == FCT_OK)
			g_pPrinter = (FILE*)1;	// This value may be tested as ok (different from NULL)
	}
	else
#endif
		g_pPrinter = fopen("PRINTER", "w-");

	init_printer_extended_characters();
}

//===========================================================================
void CUPRINT_Close_Printer(void)
{
	term_printer_extended_characters();

#ifdef _USE_UCM_
	//call UCM service
	if(UCM_Present)
		iLIBUCM_Print_Close(UCMC_PRINT);
	else
#endif
		fclose(g_pPrinter);
}

//===========================================================================
//! \brief This function prints three empty lines to eject the ticket.
//===========================================================================
static void CUPRINT_Paper_Feed(void)
{
	pprintf("\n\n\n""\xC""\n");
	ttestall(PRINTER, 50);
}

//===========================================================================
//! \brief This function sets the printer level.
//! \param[in] level : the printing level. It can take the following values : 
//! - L0 = 0 for _pCONDENSED_ font.
//! - L1 = 1 for _pNORMAL_ font.
//! - L2 = 2 for _pHEIGHT_ font. This font is not in the default local /LOCAL/MANAGER.SGN file.
//! - L3 = 3 for _dSMALL_ font.
//! - L4 = 4 for _pBOLD_ font.
//! - default case : _dMEDIUM_ font.
//! \return ticket width.
//===========================================================================
static int CUPRINT_SetPrintLevel(const t_level level)
{
	int ticket_width;

	switch (level)
	{
	case L0 :
		pprintf("%c", 0x0F);			// condensed mode
		ticket_width = 48;
		ptr_PrinterMode = _pCONDENSED_;
		break;
	case L1 :
		ticket_width = 24;
		ptr_PrinterMode = _pNORMAL_;
		break;
	case L2 :
		pprintf("%cF", 0x1B);			// double height mode
		ticket_width = 24;
		ptr_PrinterMode = _pHEIGHT_;	// warning, this font isn't in the default /LOCAL/MANAGER.SGN file ...
		break;
	case L3 :
		pprintf("%c", 0x0E);			// double width mode
		ticket_width = 12;
		ptr_PrinterMode = _dSMALL_;
		break;
	case L4 :
		pprintf("%cE", 0x1B);			// bold mode
		ticket_width = 23;				// it's just a an average
		ptr_PrinterMode = _pBOLD_;
		break;
	default :
		ticket_width = 24;
		ptr_PrinterMode = _dMEDIUM_;
		break;
	}

	return (ticket_width);
}


//===========================================================================
//! \brief This function sets the current printer level to off. Recovers _pNORMAL_ font.
//! \param[in] level : the printing level. It can take the following values : 
//! - L0 = 0 for uncondensed mode.
//! - L1 = 1 
//! - L2 = 2 
//! - L3 = 3 for undoublewidht mode.
//! - L4 = 4 for unbold mode.
//! - default for other modes.
//===========================================================================
static void CUPRINT_UnsetPrintLevel(const t_level level)
{
	switch (level)
	{
	case L0 :
		pprintf("%c", 0x12);    // uncondensed mode
		break;
	case L1 :
		break;
	case L2 :
		break;
	case L3 :
		pprintf("%c", 0x14);    // undoublewidht mode
		break;
	case L4 :
		pprintf("%cF", 0x1B);   // unbold mode
		break;
	default :
		break;
	}

	ptr_PrinterMode = _pNORMAL_;
}

//===========================================================================
//! \brief This function prints a string in a line. If the string is too long 
//! to be printed in a line, the string will be printed in several lines.
//! \param[in] string : the string to be printed.
//! \param[in] align : the string alignment.
//! \param[in] level : the printing level (condensed, bold, normal, ...).
//===========================================================================
static void CUPRINT_String_XT(const unsigned char *string, const t_align align, const t_level level)
{
	int lenght;
	int i, j, k;
	int spaces_nb;
	int ticket_width; 

	ticket_width = CUPRINT_SetPrintLevel(level);

	switch (align)
	{
	default :
	case ALIGN_LEFT :
		lenght = strlen(string);
		if (lenght <= ticket_width)
		{
			// Print the string
			//            pprintf("%s", string);
			CurrentMSG.message = (char*)string;
			PrintMSGInfos(&CurrentMSG, _OFF_, ptr_PrinterMode, _FIXED_WIDTH_);
		}
		// The string is too long to be printed on one line
		else
		{
			i = ticket_width - 1;
			j = 0;
			do
			{
				while (string[i] != ' ')
					i --;

				for (; j < i; j ++)
				{
					pprintf("%c", string[j]);
				}

				pprintf("\n");

				lenght = strlen(&string[i]);
				j = i + 1;
				i = i + ticket_width;
				if (level == L2)
				{
					//                    pprintf("%cH", 0x1B);    // double height mode
					ticket_width = CUPRINT_SetPrintLevel(L2);
				}
			}
			while (lenght > ticket_width);

			pprintf("%s", &string[j]);
		}
		break;

	case ALIGN_RIGHT :
		lenght = strlen(string);
		if (lenght <= ticket_width)
		{
			spaces_nb = ticket_width - lenght;

			if (spaces_nb >= 0)
			{
				// Print blanks spaces before the string
				for (i = 0; i < spaces_nb; i++)
					pprintf(" ");

			}

			// Print the string
			pprintf("%s", string);
		}
		// The string is too long to be printed on one line
		else
		{
			i = ticket_width - 1;
			j = 0;
			do
			{
				while (string[i] != ' ')
					i --;

				spaces_nb = ticket_width - (i - j);
				for (k = 0; k < spaces_nb; k++)
				{
					pprintf(" ");
				}
				for (; j < i; j ++)
				{
					pprintf("%c", string[j]);
				}

				pprintf("\n");

				j = i + 1;
				i = i + ticket_width;
				lenght = strlen(&string[j]);
				if (level == L2)
				{
					//                    pprintf("%cH", 0x1B);    // double height mode
					ticket_width = CUPRINT_SetPrintLevel(L2);
				}
			}
			while (lenght > ticket_width);

			spaces_nb = ticket_width - lenght;

			for (k = 0; k < spaces_nb; k++)
			{
				pprintf(" ");
			}

			pprintf("%s", &string[j]);

		}
		break;

	case ALIGN_CENTER :
		lenght = strlen(string);
		if (lenght <= ticket_width)
		{
			spaces_nb = ticket_width - lenght;

			spaces_nb = spaces_nb / 2;

			// Print blanks spaces before the string
			for (i = 0; i < spaces_nb; i++)
			{
				pprintf(" ");
			}

			// Print the string
			pprintf("%s", string);
		}
		// The string is too long to be printed on one line
		else
		{
			i = ticket_width - 1;
			j = 0;
			do
			{
				while (string[i] != ' ')
					i --;

				spaces_nb = ticket_width - (i - j);
				spaces_nb = spaces_nb / 2;

				for (k = 0; k < spaces_nb; k++)
				{
					pprintf(" ");
				}
				for (; j < i; j ++)
				{
					pprintf("%c", string[j]);

				}

				pprintf("\n");

				j = i + 1;
				i = i + ticket_width;
				lenght = strlen(&string[j]);
				if (level == L2)
				{
					//                    pprintf("%cH", 0x1B);    // double height mode
					ticket_width = CUPRINT_SetPrintLevel(L2);
				}
			}
			while (lenght > ticket_width);

			spaces_nb = ticket_width - lenght;
			spaces_nb = spaces_nb / 2;

			for (k = 0; k < spaces_nb; k++)
			{
				pprintf(" ");
			}

			pprintf("%s", &string[j]);
		}
		break;
	}

	pprintf("\n");

	CUPRINT_UnsetPrintLevel(level);

	ttestall(PRINTER, 50);
}

//===========================================================================
//! \brief This function prints two strings in a line :
//! - the first with a left alignment.
//! - the second with a right alignement.
//! \param[in] left_string : the left string to be printed.
//! \param[in] right_string : the right string to be printed.
//! \param[in] level : the printing level (condensed, bold, normal, ...).
//===========================================================================
static void CUPRINT_Double_String(const unsigned char *left_string, const unsigned char *right_string, const t_level level)
{
	unsigned int i;
	unsigned int lenght;
	unsigned int spaces_nb;
	unsigned int ticket_width;

	ticket_width = CUPRINT_SetPrintLevel(level);

	spaces_nb = ticket_width - strlen(left_string) - strlen(right_string);

	// Print left string
	lenght = strlen(left_string);
	pprintf("%s", left_string);

	// Print blanks spaces between the two strings
	for (i = 0; i < spaces_nb; i++)
	{
		pprintf(" ");
	}

	// Print the right string
	lenght = strlen(right_string);
	pprintf("%s", right_string);

	pprintf("\n");

	CUPRINT_UnsetPrintLevel(level);

	ttestall(PRINTER, 50);
}

#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function prints a data and its value in a line :
//! - the label is printed with a left alignment.
//! - the value is print with a right alignement.
//! \param[in] label : a string containing the label.
//! \param[in] value : a string containing the value.
//! \param[in] level : the printing level (condensed, bold, normal, ...).
//===========================================================================
static void CUPRINT_Data(const unsigned char *label, const unsigned char *value, const t_level level)
{
	unsigned int lg_libele;
	unsigned int lg_valeur;
	unsigned int spaces_nb;
	unsigned int i;
	unsigned int ticket_width;

	ticket_width = CUPRINT_SetPrintLevel(level);

	lg_libele = strlen(label);
	lg_valeur = strlen(value);

	spaces_nb = ticket_width - (lg_libele + lg_valeur);

	if ((lg_libele + lg_valeur) <= ticket_width)
	{
		for (i = 0; i < lg_libele; i++)
		{
			pprintf("%c", label[i]);
		}

		for (i = 0; i < spaces_nb; i++)
		{
			pprintf(" ");
		}

		for (i = 0; i < lg_valeur; i++)
		{
			pprintf("%c", value[i]);
		}

		pprintf("\n");
	}
	else
	{
		pprintf("Too many characters.");
	}

	CUPRINT_UnsetPrintLevel(level);

	ttestall(PRINTER, 50);
}
#endif /* _TOOLWARE_ */

//===========================================================================
void CUPRINT_Blanks_Lines(const unsigned char lines_nb)
{
	unsigned char i;

	for (i = 0; i < lines_nb; i++)
		pprintf("\n");

	ttestall(PRINTER, 50);
}

//===========================================================================
//! \brief This function prints the top of a frame. The max lenght of a line 
//! is 24 characters. Use this function to open a frame. See also those functions :
//! - \ref CUPRINT_Top_Frame
//! - \ref CUPRINT_Top_Frame_String
//! - \ref CUPRINT_Bottom_Frame
//! - \ref CUPRINT_Double_String_Frame
//! - \ref CUPRINT_String_Frame
//! \param[in] offset : number of white spaces before beginning of printing.
//! \param[in] lenght : the lenght of the line.
//===========================================================================
static void CUPRINT_Top_Frame(const short offset, const short lenght)
{
	unsigned short i;
	unsigned short border_nb;

	// Print the offset
	for (i = 0; i < offset; i++)
	{
		pprintf(" ");
	}

	border_nb = lenght - 2;

	// Print the right top corner
	pprintf("%c", LEFT_TOP_ROUNDED_CORNER);

	// Print the border
	for (i = 0; i < border_nb; i++)
	{
		pprintf("%c", HORIZONTAL_BAR);
	}
	
	// Print the left top corner
	pprintf("%c\n", RIGHT_TOP_ROUNDED_CORNER);
	ttestall(PRINTER, 50);
}

//===========================================================================
//! \brief This function prints the top of a frame containing a string. 
//! The max lenght of a line is 24 characters. 
//! Use this function to open a frame. See also those functions :
//! - \ref CUPRINT_Top_Frame
//! - \ref CUPRINT_Top_Frame_String
//! - \ref CUPRINT_Bottom_Frame
//! - \ref CUPRINT_Double_String_Frame
//! - \ref CUPRINT_String_Frame
//! \param[in] offset : number of white spaces before beginning of printing.
//! \param[in] lenght : the lenght of the line.
//! \param[in] string : the string to print into the frame.
//! \param[in] align : the aligment of the string.
//===========================================================================
static void CUPRINT_Top_Frame_String(const short offset, const short lenght, const unsigned char *string, const t_align align)
{
	unsigned short    i;
	unsigned short    spaces_nb;
	unsigned short    _spaces_nb;


	// Print the offset
	for (i = 0; i < offset; i++)
	{
		pprintf(" ");
	}

	// Substract the two sides bars
	spaces_nb = lenght - 2;

    // Substract the string lenght and its two spaces around
	spaces_nb = spaces_nb - (strlen(string) + 2);

	// Print the right top corner
	pprintf("%c", LEFT_TOP_ROUNDED_CORNER);

	switch (align)
	{
	default :
	case ALIGN_LEFT :
		// Print the string with his two spaces
		pprintf("%c%s%c", HORIZONTAL_END_BAR, string, HORIZONTAL_BEGIN_BAR);

		// Print the blanks
		for (i = 0; i < spaces_nb; i ++)
		{
			pprintf("%c", HORIZONTAL_BAR);
		}
		break;

	case ALIGN_CENTER :
		// spaces number before the string
		_spaces_nb = spaces_nb / 2;

		// spaces number after the string
		spaces_nb = spaces_nb - _spaces_nb;

		// Print the blanks before the string
		for (i = 0; i < _spaces_nb; i ++)
		{
			pprintf("%c", HORIZONTAL_BAR);
		}

		// Print the string with his two spaces
		pprintf("%c%s%c", HORIZONTAL_END_BAR, string, HORIZONTAL_BEGIN_BAR);

		// Print the blansk after the string
		for (i = 0; i < spaces_nb; i ++)
		{
			pprintf("%c", HORIZONTAL_BAR);
		}
		break;

	case ALIGN_RIGHT :
		// Print the blanks
		for (i = 0; i < spaces_nb; i ++)
		{
			pprintf("%c", HORIZONTAL_BAR);
		}
		// Print the string with his two spaces
		pprintf("%c%s%c", HORIZONTAL_END_BAR, string, HORIZONTAL_BEGIN_BAR);
		break;
	}

	// Print the left side bar
	pprintf("%c\n", RIGHT_TOP_ROUNDED_CORNER);
	ttestall(PRINTER, 50);
}

//===========================================================================
//! \brief This function prints a string into a frame with a specific alignment.
//! The max lenght of a line is 24 characters. 
//! If the string is too long to be printed on one line, it will be printed 
//! on several lines. Use this function to fill a frame. See also those functions :
//! - \ref CUPRINT_Top_Frame
//! - \ref CUPRINT_Top_Frame_String
//! - \ref CUPRINT_Bottom_Frame
//! - \ref CUPRINT_Double_String_Frame
//! - \ref CUPRINT_String_Frame
//! \param[in] offset : number of white spaces before beginning of printing.
//! \param[in] lenght : the lenght of the line.
//! \param[in] string : the string to print into the frame.
//! \param[in] align : the aligment of the string.
//===========================================================================
static void CUPRINT_String_Frame(const short offset, const short lenght, const unsigned char *string, const t_align align)
{
	unsigned short i;
	unsigned short spaces_nb_after;
	unsigned short spaces_nb_before;

	unsigned short ind_begin;
	unsigned short ind_end;
	unsigned short max;
	unsigned short string_lenght;

	if ((lenght) > (24 - offset))
	{
		max = 24 - offset;
	}
	else
	{
		// Substract the two sides bars
		max = lenght - 2;
	}

	switch (align)
	{
	default :
	case ALIGN_LEFT :
		string_lenght = strlen(string);

		// The string could be print on one line
		if (string_lenght <= max)
		{
			// Print the offset
			for (i = 0; i < offset; i++)
			{
				pprintf(" ");

			}

			// Print the left border
			pprintf("%c", VERTICAL_BAR);

			// Print the string
			for (i = 0; i < string_lenght; i ++)
			{
				pprintf("%c", string[i]);

			}

			// Print the blanks between the string and the right border
			spaces_nb_after = max - string_lenght;
			for (i = 0; i < spaces_nb_after; i ++)
			{
				pprintf(" ");

			}

			// Print the right border
			pprintf("%c\n", VERTICAL_BAR);
			ttestall(PRINTER, 50);
		}
		// The string is too long to be printed on one line
		else
		{
			ind_begin = 0;
			ind_end = ind_begin + max;
			do
			{
				// Print the offset
				for (i = 0; i < offset; i ++)
				{
					pprintf(" ");
				}

				// Print the right side bar
				pprintf("%c", VERTICAL_BAR);

				// Looking for a ' '
				while ((string[ind_end] != ' ') && (ind_end > ind_begin))
				{
					ind_end --;
				}

				// No space found: return to max
				if (ind_end <= ind_begin)
				{
					ind_end = ind_begin + max;
				}

				// Print the piece of string
				for (i = ind_begin; i < ind_end; i ++)
				{
					pprintf("%c", string[i]);
				}

				// Print the blanks between the piece of string and the right border
				spaces_nb_after = max - (ind_end - ind_begin);
				for (i = 0; i < spaces_nb_after; i ++)
				{
					pprintf(" ");
				}

				// Print the right border
				pprintf("%c\n", VERTICAL_BAR);
				ttestall(PRINTER, 50);

				if (string[ind_end] != ' ')
				{
					ind_begin = ind_end;
					ind_end = ind_end + max;
				}
				else
				{
					ind_begin = ind_end + 1;
					ind_end = ind_end + max + 1;
				}
				string_lenght = strlen(&string[ind_begin]);
			}
			while (string_lenght > max);

			// Print the offset
			for (i = 0; i < offset; i ++)
			{
				pprintf(" ");

			}

			// Print the right side bar
			pprintf("%c", VERTICAL_BAR);

			// Print the last piece of string
			ind_end = ind_begin + string_lenght;
			for (i = ind_begin; i < ind_end; i ++)
			{
				pprintf("%c", string[i]);
			}

			// Print the blanks between the last piece of string and the right border
			spaces_nb_after = max - (string_lenght);
			for (i = 0; i < spaces_nb_after; i ++)
			{
				pprintf(" ");
			}

			// Print the right border
			pprintf("%c\n", VERTICAL_BAR);
			ttestall(PRINTER, 50);
		}
		break;

	case ALIGN_CENTER :
		string_lenght = strlen(string);

		// The string could be print on one line
		if (string_lenght <= max)
		{
			// Print the offset
			for (i = 0; i < offset; i++)
			{
				pprintf(" ");
			}

			// Print the left border
			pprintf("%c", VERTICAL_BAR);

			// Print the blanks between the string and the left border
			spaces_nb_before = (max - string_lenght) / 2;
			for (i = 0; i < spaces_nb_before ; i ++)
			{
				pprintf(" ");
			}

			// Print the string
			for (i = 0; i < string_lenght; i ++)
			{
				pprintf("%c", string[i]);
			}

			// Print the blanks between the string and the right border
			spaces_nb_after = (max - string_lenght) - spaces_nb_before;
			for (i = 0; i < spaces_nb_after; i ++)
			{
				pprintf(" ");
			}

			// Print the right border
			pprintf("%c\n", VERTICAL_BAR);
			ttestall(PRINTER, 50);
		}
		// The string is too long to be printed on one line
		else
		{
			ind_begin = 0;
			ind_end = ind_begin + max;
			do
			{
				// Print the offset
				for (i = 0; i < offset; i ++)
				{
					pprintf(" ");
				}

				// Print the right side bar
				pprintf("%c", VERTICAL_BAR);

				// Looking for a ' '
				while ((string[ind_end] != ' ') && (ind_end > ind_begin))
				{
					ind_end --;
				}

				// No space found: return to max
				if (ind_end <= ind_begin)
				{
					ind_end = ind_begin + max;
				}

				// Print the blanks between the piece of string and the left border
				spaces_nb_before = (max - (ind_end - ind_begin)) / 2;
				for (i = 0; i < spaces_nb_before; i ++)
				{
					pprintf(" ");
				}

				// Print the piece of string
				for (i = ind_begin; i < ind_end; i ++)
				{
					pprintf("%c", string[i]);
				}

				// Print the blanks between the piece of string and the right border
				spaces_nb_after = (max - (ind_end - ind_begin)) - spaces_nb_before;
				for (i = 0; i < spaces_nb_after; i ++)
				{
					pprintf(" ");
				}

				// Print the right border
				pprintf("%c\n", VERTICAL_BAR);
				ttestall(PRINTER, 50);


				if (string[ind_end] != ' ')
				{
					ind_begin = ind_end;
					ind_end = ind_end + max;
				}
				else
				{
					ind_begin = ind_end + 1;
					ind_end = ind_end + max + 1;
				}
				string_lenght = strlen(&string[ind_begin]);
			}
			while (string_lenght > max);

			// Print the offset
			for (i = 0; i < offset; i ++)
			{
				pprintf(" ");
			}

			// Print the right side bar
			pprintf("%c", VERTICAL_BAR);

			// Print the blanks between the lase piece of string and the left border
			spaces_nb_before = (max - string_lenght) / 2;
			for (i = 0; i < spaces_nb_before ; i ++)
			{
				pprintf(" ");
			}

			// Print the last piece of string
			ind_end = ind_begin + string_lenght;
			for (i = ind_begin; i < ind_end; i ++)
			{
				pprintf("%c", string[i]);
			}

			// Print the blanks between the last piece of string and the right border
			spaces_nb_after = (max - string_lenght) - spaces_nb_before;
			for (i = 0; i < spaces_nb_after; i ++)
			{
				pprintf(" ");
			}

			// Print the right border
			pprintf("%c\n", VERTICAL_BAR);
			ttestall(PRINTER, 50);
		}
		break;

	case ALIGN_RIGHT :
		string_lenght = strlen(string);

		// The string could be print on one line
		if (string_lenght <= max)
		{
			// Print the offset
			for (i = 0; i < offset; i++)
			{
				pprintf(" ");
			}

			// Print the left border
			pprintf("%c", VERTICAL_BAR);

			// Print the blanks between the string and the left border
			spaces_nb_before = max - string_lenght;
			for (i = 0; i < spaces_nb_before; i ++)
			{
				pprintf(" ");
			}

			// Print the string
			for (i = 0; i < string_lenght; i ++)
			{
				pprintf("%c", string[i]);
			}

			// Print the right border
			pprintf("%c\n", VERTICAL_BAR);
			ttestall(PRINTER, 50);

		}
		// The string is too long to be printed on one line
		else
		{
			ind_begin = 0;
			ind_end = ind_begin + max;
			do
			{
				// Print the offset
				for (i = 0; i < offset; i ++)
				{
					pprintf(" ");
				}

				// Print the right side bar
				pprintf("%c", VERTICAL_BAR);

				// Looking for a ' '
				while ((string[ind_end] != ' ') && (ind_end > ind_begin))
				{
					ind_end --;
				}

				// No space found: return to max
				if (ind_end <= ind_begin)
				{
					ind_end = ind_begin + max;
				}

				// Print the blanks between the piece of string and the left border
				spaces_nb_before = max - (ind_end - ind_begin);
				for (i = 0; i < spaces_nb_before; i ++)
				{
					pprintf(" ");
				}

				// Print the piece of string
				for (i = ind_begin; i < ind_end; i ++)
				{
					pprintf("%c", string[i]);
				}

				// Print the right border
				pprintf("%c\n", VERTICAL_BAR);
				ttestall(PRINTER, 50);

				if (string[ind_end] != ' ')
				{
					ind_begin = ind_end;
					ind_end = ind_end + max;
				}
				else
				{
					ind_begin = ind_end + 1;
					ind_end = ind_end + max + 1;
				}
				string_lenght = strlen(&string[ind_begin]);
			}
			while (string_lenght > max);

			// Print the offset
			for (i = 0; i < offset; i ++)
			{
				pprintf(" ");
			}

			// Print the right side bar
			pprintf("%c", VERTICAL_BAR);

			// Print the blanks between the last piece of string and the left border
			spaces_nb_before = max - (string_lenght);
			for (i = 0; i < spaces_nb_before; i ++)
			{
				pprintf(" ");
			}

			// Print the last piece of string
			ind_end = ind_begin + string_lenght;
			for (i = ind_begin; i < ind_end; i ++)
			{
				pprintf("%c", string[i]);
			}

			// Print the right border
			pprintf("%c\n", VERTICAL_BAR);
			ttestall(PRINTER, 50);
		}
		break;
	}
}

//===========================================================================
//! \brief This function prints two strings into a frame. The first one is printed, 
//! followed by blank spaces, and then the second one. This sequence is centered.
//! The max lenght of a line is 24 characters. 
//! If the sequence is too long to be printed on one line, it will be printed 
//! on several lines. Use this function to fill a frame. See also those functions :
//! - \ref CUPRINT_Top_Frame
//! - \ref CUPRINT_Top_Frame_String
//! - \ref CUPRINT_Bottom_Frame
//! - \ref CUPRINT_Double_String_Frame
//! - \ref CUPRINT_String_Frame
//! \param[in] offset : number of white spaces before beginning of printing.
//! \param[in] lenght : the lenght of the line.
//! \param[in] left_string : the string to print on the left.
//! \param[in] right_string : the string to print on the right.
//===========================================================================
static void CUPRINT_Double_String_Frame(const short offset, const short lenght, const unsigned char *left_string, const unsigned char *right_string)
{
	unsigned short    i;
	unsigned short    max;
	unsigned short    spaces_nb;

	// The two strings are too long to be printed on the same line
	if ( (short) ((strlen(left_string) + strlen(right_string) + offset + 2)) > (lenght - 2))
	{
		CUPRINT_String_Frame(offset, lenght, left_string, ALIGN_LEFT);
		CUPRINT_String_Frame(offset, lenght, right_string, ALIGN_RIGHT);
	}
	// The two strings can be printed on the same line
	else
	{
		// Max number of characters to be printed on one line
		if ((lenght) > (24 - offset))
		{
			max = 24 - offset;
		}
		else
		{
			// Substract the two sides bars
			max = lenght - 2;
		}

		// Print the offset
		for (i = 0; i < offset; i++)
		{
			pprintf(" ");

		}
		// Number of free spaces
		spaces_nb = max - (strlen(left_string) + strlen(right_string));    // Substract the two strings lenght

		// Print the right side bar and the left string
		pprintf("%c%s", VERTICAL_BAR, left_string);

		// Print the blanks between the two strings
		for (i = 0; i < spaces_nb; i ++)
		{
			pprintf(" ");

		}

		// Print the left side bar and the right string
		pprintf("%s%c\n", right_string, VERTICAL_BAR);
		ttestall(PRINTER, 50);
	}
}

//===========================================================================
//! \brief This function prints the bottom of a frame.
//! The max lenght of a line is 24 characters. 
//! Use this function to fill a frame. See also those functions :
//! - \ref CUPRINT_Top_Frame
//! - \ref CUPRINT_Top_Frame_String
//! - \ref CUPRINT_Bottom_Frame
//! - \ref CUPRINT_Double_String_Frame
//! - \ref CUPRINT_String_Frame
//! \param[in] offset : number of white spaces before beginning of printing.
//! \param[in] lenght : the lenght of the line.
//===========================================================================
static void CUPRINT_Bottom_Frame(const short offset, const short lenght)
{
	unsigned short    i;
	unsigned short    border_nb;

	if ((lenght) > (24 - offset))
	{
		border_nb = 24 - offset;
	}
	else
	{
		border_nb = lenght - 2;
	}

	// Print the offset
	for (i = 0; i < offset; i++)
	{
		pprintf(" ");
	}

	// Print the left bottom corner
	pprintf("%c", LEFT_BOTTOM_ROUNDED_CORNER);

	// Print the border
	for (i = 0; i < border_nb; i++)
	{
		pprintf("%c", HORIZONTAL_BAR);
	}
	// Print the right bottom corner

	pprintf("%c\n", RIGHT_BOTTOM_ROUNDED_CORNER);
	ttestall(PRINTER, 50);
}

//===========================================================================
//! \brief This function prints a line.
//! The max lenght of a line is 24 characters.
//! \param[in] offset : number of white spaces before beginning of printing.
//! \param[in] length : the length of the line.
//===========================================================================
void CUPRINT_Boundary_Line(const short offset, const short length)
{
	unsigned short    i;
	unsigned short    border_nb;


	if ((length) > (24 - offset))
	{
		border_nb = 24 - offset;
	}
	else
	{
		border_nb = length - 2;
	}

	// Print the offset
	for (i = 0; i < offset; i++)
	{
		pprintf(" ");
	}

	// Print the begin border
	pprintf("%c", HORIZONTAL_BEGIN_BAR);

	// Print the borders
	for (i = 0; i < border_nb; i++)
	{
		pprintf("%c", HORIZONTAL_BAR);
	}

	// Print the end border
	pprintf("%c\n", HORIZONTAL_END_BAR);
	ttestall(PRINTER, 50);
}


#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function prints the card features.
//===========================================================================
static void card_features(void)
{
	static unsigned char    buffer[50];
	static unsigned char offset[40];

	DataElement                elt;
	DataElement                Elt; // *ptElt;

	unsigned short            i;
	unsigned short            usFound;
	unsigned char           select;
	int                     found;

	Selection_Method        selection;
	t_oda                    oda;
	t_pin                    pin;

	unsigned long            ulKey_exponent[3];
	unsigned short            usKey_lenght[3];

	static const unsigned long RequiredTags[] = {TAG_AIP, TAG_ICC_PUB_KEY_EXP, TAG_ICC_PUB_KEY_REM, 
		TAG_ISSUER_PUBLIC_KEY_EXP, TAG_ISSUER_PUBLIC_KEY_REM, TAG_CERT_AUTH_PUB_KEY_EXPONENT,
		TAG_CERT_AUTH_PUB_KEY_MODULUS, TAG_CERT_AUTH_PUB_KEY_MODULUS, TAG_CERT_AUTH_PUB_KEY_MODULUS,
		TAG_IPK_DATA, TAG_ICC_DATA };
	TLV_TREE_NODE hTree;

	// Print header
	CUPRINT_Boundary_Line(0, 24);
	CUPRINT_Blanks_Lines(1);

	sprintf(buffer, "1 - %s", CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_CARD_FEATURES, g_language));
	CUPRINT_String_XT(buffer, ALIGN_LEFT, L4);
	CUPRINT_Blanks_Lines(1);

	CUPRINT_Top_Frame(0, 24);

	found = PAR_ReadParameter(TAG_USE_PSE, (DataElementExt *)&elt);

	// Selection Method
	if (found)
		select = elt.ptValue[0];
	else 
		select = 0; /* Default value ??? */

	if (select == FALSE)
	{
		sprintf(buffer, "%s%c ", CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CU_MESS_PSE, g_language), VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_Read_Message(CONSULT_RECEIPT_TABLE, CU_MESS_SELECTION_METHOD, g_language));
		CUPRINT_Data(offset, buffer, L0);
		g_TFS = g_TFS | SELECTION_METHOD_IS_DSM;
	}
	else
	{
		hTree = Engine_GetCommand(0);    // the first command (Select with PSE directory)

		usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APDU_RESPONSE, &Elt);

		// Release local TLV tree
		TlvTree_ReleaseEx(&hTree);

		if (usFound)
		{
			// selection = get_selection_method(ptElt);
			selection = get_selection_method(&Elt);
			switch (selection)
			{
			case DIRECTORY_SELECTION_METHOD :
				sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_PSE, g_language), VERTICAL_BAR);
				sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_SELECTION_METHOD, g_language));
				CUPRINT_Data(offset, buffer, L0);
				g_TFS = g_TFS | SELECTION_METHOD_IS_DSM;
				break;
			case EXPLICIT_SELECTION_METHOD :
				sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_NO_PSE, g_language), VERTICAL_BAR);
				sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_SELECTION_METHOD, g_language));
				CUPRINT_Data(offset, buffer, L0);
				g_TFS = g_TFS | SELECTION_METHOD_IS_ESM;
				break;
			case CARD_IS_BLOCKED_OR_COMMAND_NOT_SUPPORTED :
				sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_ERROR, g_language), VERTICAL_BAR);
				sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_SELECTION_METHOD, g_language));
				CUPRINT_Data(offset, buffer, L0);
				sprintf(buffer, "%s%c", CUMESS_ReadMessageReceipt(CU_MESS_APP_IS_BLOCKED_OR_CMD_NOT_SUPPORTED, g_language), VERTICAL_BAR);
				sprintf(offset, "%c", VERTICAL_BAR);
				CUPRINT_Data(offset, buffer, L0);
				break;
			case APPLICATION_IS_BLOCKED :
				sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_ERROR, g_language), VERTICAL_BAR);
				sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_SELECTION_METHOD, g_language));
				CUPRINT_Data(offset, buffer, L0);
				sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_APP_IS_BLOCKED, g_language), VERTICAL_BAR);
				sprintf(offset, "%c", VERTICAL_BAR);
				CUPRINT_Data(offset, buffer, L0);
				break;
			default :
			case ERROR_RESPONSE_UNKNOWN :
				sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_ERROR, g_language), VERTICAL_BAR);
				sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_SELECTION_METHOD, g_language));
				CUPRINT_Data(offset, buffer, L0);
				sprintf(buffer, "Respond unknown %c ", VERTICAL_BAR);
				sprintf(offset, "%c", VERTICAL_BAR);
				CUPRINT_Data(offset, buffer, L0);
				break;
			}
		}
	}

	// PIN Verification
	// check if there is a Get Challenge command in the command list
	i = 0;
	pin = P_PLAINTEXT_PIN;
	if ((ulMMI_pin_on_line == 0) && (ulMMI_pin_off_line == 0))
		pin = P_NO_PIN;
	hTree = Engine_GetCommand(i);
	usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APDU_CMD, &Elt);
	// Release local TLV tree
	TlvTree_ReleaseEx(&hTree);
	while (usFound)
	{
		hTree = Engine_GetCommand(i);
		usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APDU_CMD, &Elt);

		if ((Elt.ptValue[0] == 0x00) &
			(Elt.ptValue[1] == 0x84))    // Get Challenge
			pin = P_ENCIPHERED_PIN;

		i ++;

		// Release local TLV tree
		TlvTree_ReleaseEx(&hTree);

	}
	/* Online management */
	if (ulMMI_pin_on_line)   /* If time have been used for input on line pin */
		pin = P_ONLINE_PIN;  /* It's an on-line key verification             */

	switch (pin)
	{
	case P_ONLINE_PIN :
		sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_ONLINE_PIN, g_language), VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_PIN_VERIFICATION, g_language));
		CUPRINT_Data(offset, buffer, L0);
		g_TFS = g_TFS | ONLINE_PIN_IS_TO_BE_PERFORMED;
		break;
	case P_ENCIPHERED_PIN :
		sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_ENCIPHERED_PIN, g_language), VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_PIN_VERIFICATION, g_language));
		CUPRINT_Data(offset, buffer, L0);
		g_TFS = g_TFS | ENCIPHERED_PIN_IS_TO_BE_PERFORMED;
		break;
	case P_PLAINTEXT_PIN :
		sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_PLAINTEXT_PIN, g_language), VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_PIN_VERIFICATION, g_language));
		CUPRINT_Data(offset, buffer, L0);
		g_TFS = g_TFS | PLAINTEXT_PIN_IS_TO_BE_PERFORMED;
		break;
	case P_NO_PIN :
		sprintf(buffer, "%s%c ", " ", VERTICAL_BAR); /* No method used => no text */
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_PIN_VERIFICATION, g_language));
		CUPRINT_Data(offset, buffer, L0);
		/* g_TFS */ /* No change on this */
		break;
	default :
		sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_ERROR, g_language), VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_PIN_VERIFICATION, g_language));
		CUPRINT_Data(offset, buffer, L0);
		/* g_TFS */ /* No change on this */
		break;
	}

	// Get the RequiredTags from from EMVDC Data base.
	hTree = Engine_GetDataElements(sizeof(RequiredTags) / sizeof(RequiredTags[0]), RequiredTags);

	// Offline Authentication Method

	oda = IS_NOT_SUPPORTED;
	usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_AIP, &Elt);

	if (usFound)
	{
		g_TFS = g_TFS | OFFLINE_DATA_AUTHENTICATION_IS_TO_BE_PERFORMED;
		// Is DDA ?
		if ((Elt.ptValue [0] & OFFLINE_DDA_IS_SUPPORTED) == OFFLINE_DDA_IS_SUPPORTED)
		{
			if ((Elt.ptValue [0] & COMBINED_DDA_GENERATE_AC_SUPPORTED) == COMBINED_DDA_GENERATE_AC_SUPPORTED)
				oda = IS_CDA;
			else
				oda = IS_DDA;
		}
		else
		{
			// Is SDA ?
			if ((Elt.ptValue [0] & OFFLINE_SDA_IS_SUPPORTED) == OFFLINE_SDA_IS_SUPPORTED)
				oda = IS_SDA;
		}
	}

	switch (oda)
	{
	case IS_SDA :
		sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_SDA, g_language), VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_AUTHENTICATION_METHOD, g_language));
		CUPRINT_Data(offset, buffer, L0);
		g_TFS = g_TFS | OFFLINE_DATA_AUTHENTICATION_IS_SDA;
		break;
	case IS_DDA :
		sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_DDA, g_language), VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_AUTHENTICATION_METHOD, g_language));
		CUPRINT_Data(offset, buffer, L0);
		g_TFS = g_TFS | OFFLINE_DATA_AUTHENTICATION_IS_DDA;
		break;
	case IS_CDA :
		sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_CDA, g_language), VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_AUTHENTICATION_METHOD, g_language));
		CUPRINT_Data(offset, buffer, L0);
		g_TFS = g_TFS | OFFLINE_DATA_AUTHENTICATION_IS_CDA;
		break;
	default :
	case IS_NOT_SUPPORTED :
		sprintf(buffer, "%s%c ", CUMESS_ReadMessageReceipt(CU_MESS_NOT_SUPPORTED, g_language), VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_AUTHENTICATION_METHOD, g_language));
		CUPRINT_Data(offset, buffer, L0);
		break;
	}

	// Print keys
	// Certificate Authority
	if (oda != IS_NOT_SUPPORTED)
	{
		usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_CERT_AUTH_PUB_KEY_MODULUS, &Elt);
		if (usFound)
		{
			usKey_lenght[CERTIFICATE_AUTHORITY] = Elt.length * 8;

			usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_CERT_AUTH_PUB_KEY_EXPONENT, &Elt);

			if (usFound)
			{
				if (Elt.length == 1)
					ulKey_exponent[CERTIFICATE_AUTHORITY] = 3;
				else
					ulKey_exponent[CERTIFICATE_AUTHORITY] = 65537;
			}
			else
			{
				ulKey_exponent[CERTIFICATE_AUTHORITY]    = 0;
			}
		}
		else
		{
			usKey_lenght[CERTIFICATE_AUTHORITY]        = 0;
			ulKey_exponent[CERTIFICATE_AUTHORITY]         = 0;
		}

		// Issuer Public Key
		usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_IPK_DATA, &Elt);
		if (usFound)
		{
			usKey_lenght[ISSUER_PUBLIC_KEY] = Elt.ptValue[13] * 8;
			if (Elt.ptValue[14] == 1)
				ulKey_exponent[ISSUER_PUBLIC_KEY]    = 3;
			else
				ulKey_exponent[ISSUER_PUBLIC_KEY]    = 65537;
		}
		else
		{
			usKey_lenght[ISSUER_PUBLIC_KEY]        = 0;
			ulKey_exponent[ISSUER_PUBLIC_KEY]    = 0;
		}

		// ICC Public Key
		usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_ICC_DATA, &Elt);
		if (usFound)
		{
			usKey_lenght[ICC_PUBLIC_KEY]    = Elt.ptValue[19] * 8;
			if (Elt.ptValue[20] == 1)
				ulKey_exponent[ICC_PUBLIC_KEY]    = 3;
			else
				ulKey_exponent[ICC_PUBLIC_KEY]    = 65537;
		}
		else
		{
			usKey_lenght[ICC_PUBLIC_KEY]    = 0;
			ulKey_exponent[ICC_PUBLIC_KEY]    = 0;
		}

		// Print CA informations
		if ((usKey_lenght[CERTIFICATE_AUTHORITY] != 0) |
			(ulKey_exponent[CERTIFICATE_AUTHORITY] != 0))
		{
			sprintf(buffer, "%c ", VERTICAL_BAR);
			sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_KEY_CERTIFICATE_AUTHORITY, g_language));
			CUPRINT_Data(offset, buffer, L0);
			if (usKey_lenght[CERTIFICATE_AUTHORITY] != 0)
			{
				sprintf(buffer, "%d bits%c ", usKey_lenght[CERTIFICATE_AUTHORITY], VERTICAL_BAR);
				sprintf(offset, "%c - %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_KEY_LENGHT, g_language));
				CUPRINT_Data(offset, buffer, L0);
			}
			if (ulKey_exponent[CERTIFICATE_AUTHORITY] != 0)
			{
				sprintf(buffer, "%ld     %c ", ulKey_exponent[CERTIFICATE_AUTHORITY], VERTICAL_BAR);
				sprintf(offset, "%c - %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_KEY_EXPONENT, g_language));
				CUPRINT_Data(offset, buffer, L0);
			}
		}

		// Print Issuer Public Key informations
		if ((usKey_lenght[ISSUER_PUBLIC_KEY] != 0) |
			(ulKey_exponent[ISSUER_PUBLIC_KEY] != 0))
		{
			sprintf(buffer, "%c ", VERTICAL_BAR);
			sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_KEY_ISSUER_PUBLIC_KEY, g_language));
			CUPRINT_Data(offset, buffer, L0);
			if (usKey_lenght[ISSUER_PUBLIC_KEY] != 0)
			{
				sprintf(buffer, "%d bits%c ", usKey_lenght[ISSUER_PUBLIC_KEY], VERTICAL_BAR);
				sprintf(offset, "%c - %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_KEY_LENGHT, g_language));
				CUPRINT_Data(offset, buffer, L0);
			}
			if (ulKey_exponent[ISSUER_PUBLIC_KEY] != 0)
			{
				sprintf(buffer, "%ld     %c ", ulKey_exponent[ISSUER_PUBLIC_KEY], VERTICAL_BAR);
				sprintf(offset, "%c - %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_KEY_EXPONENT, g_language));
				CUPRINT_Data(offset, buffer, L0);
			}
		}

		// Print ICC Public Key informations
		if ((usKey_lenght[ICC_PUBLIC_KEY] != 0) |
			(ulKey_exponent[ICC_PUBLIC_KEY] != 0))
		{
			sprintf(buffer, "%c ", VERTICAL_BAR);
			sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_KEY_ICC_PUBLIC_KEY, g_language));
			CUPRINT_Data(offset, buffer, L0);
			if (usKey_lenght[ICC_PUBLIC_KEY] != 0)
			{
				sprintf(buffer, "%d bits%c ", usKey_lenght[ICC_PUBLIC_KEY], VERTICAL_BAR);
				sprintf(offset, "%c - %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_KEY_LENGHT, g_language));
				CUPRINT_Data(offset, buffer, L0);
			}
			if (ulKey_exponent[ICC_PUBLIC_KEY] != 0)
			{
				sprintf(buffer, "%ld     %c ", ulKey_exponent[ICC_PUBLIC_KEY], VERTICAL_BAR);
				sprintf(offset, "%c - %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_KEY_EXPONENT, g_language));
				CUPRINT_Data(offset, buffer, L0);
			}
		}
	}

	// Release local TLV tree
	TlvTree_ReleaseEx(&hTree);

	CUPRINT_Bottom_Frame(0, 24);
	CUPRINT_Blanks_Lines(1);
}
#endif /* _TOOLWARE_ */

#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function prints the the transaction features.
//===========================================================================
static void transaction_features(void)
{
	static unsigned char    buffer[50];
	static unsigned char    offset[50];

	DataElement        EltCmd;
	DataElement        EltRsp;
	DataElement        EltBegin;
	DataElement        EltEnd;

	unsigned long      ulBegin_command_time =    0;
	unsigned long      ulEnd_command_time =    0;
	unsigned long      ulPrevious_command =    0;
	unsigned short     usFound;
	unsigned short     i = 0;

	t_process          process = IS_IN_PROGRESS;
	TLV_TREE_NODE      hTree;


	// Print header
	CUPRINT_Boundary_Line(0, 24);
	CUPRINT_Blanks_Lines(1);

	sprintf(buffer, "2 - %s", CUMESS_ReadMessageReceipt(CU_MESS_TRANSACTION_FEATURES, g_language));
	CUPRINT_String_XT(buffer, ALIGN_LEFT, L4);
	CUPRINT_Blanks_Lines(1);

	while ((process != IS_DONE) && (process != IS_NOT_AVAILABLE))
	{
		hTree = Engine_GetCommand(i);
		usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APDU_CMD, &EltCmd);

		if (!usFound)
		{
			// there is no commands
			if (i == 0)
				process = IS_NOT_AVAILABLE;
			// process is done
			else
				process = IS_DONE;
		}
		else
		{
			// retreive other informations
			usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APDU_RESPONSE, &EltRsp);
			usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_BEGIN_TIMER, &EltBegin);
			usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_END_TIMER, &EltEnd);

			ulBegin_command_time    = CharToLong (EltBegin.ptValue);
			ulEnd_command_time        = CharToLong (EltEnd.ptValue);

			// first command
			if (i == 0)
			{
				// Init datas
				ulBegin_transaction = ulBegin_command_time;
				ulBegin_computation = ulBegin_command_time;
				ulPrevious_command = ulEnd_command_time;
				ulCard = ulEnd_command_time - ulBegin_command_time;
				ulTerminal = 0;
			}
			else
			{
				ulCard    = ulCard + (ulEnd_command_time - ulBegin_command_time);
				ulTerminal = ulTerminal + (ulBegin_command_time - ulPrevious_command);
				ulPrevious_command = ulEnd_command_time;
			}
		}
		i++;

		// Release local TLV tree
		TlvTree_ReleaseEx(&hTree);

	}

	if (process != IS_NOT_AVAILABLE)
	{
		// sub extra time
		ulTerminal = ulTerminal + (ulEnd_computation - ulPrevious_command) - ulMMI_pin_off_line - ulMMI_pin_on_line - ulMMI_amount - ulMMI_account_type - ulMMI_langue - ulMMI_selappli - ulMMI_force_OLP - ulMMI_force_CAA - ulMMI_force_COMP - ulHOST_comm ;

		// sub lost time in booster if PIN is enciphered
		if((g_TFS & ENCIPHERED_PIN_IS_TO_BE_PERFORMED) == ENCIPHERED_PIN_IS_TO_BE_PERFORMED)
		{
			ulTerminal = ulTerminal - LOST_TIME_IN_BOOSTER;
			ulCard = ulCard + LOST_TIME_IN_BOOSTER;
		}

		// Print transaction time
		CUPRINT_String_XT(CUMESS_ReadMessageReceipt(CU_MESS_TRANSACTION_TIME, g_language), ALIGN_LEFT, L1);
		sprintf(buffer, "%ld ms", (ulEnd_transaction - ulBegin_transaction) * 10);
		CUPRINT_Top_Frame_String(0, 24, buffer, ALIGN_RIGHT);

		// Print ratios
		sprintf(buffer, "%ld.%02ld %%%c ", (ulTerminal * 100) / (ulEnd_transaction - ulBegin_transaction), ((ulTerminal * 100 * 100) / (ulEnd_transaction - ulBegin_transaction)) % 100, VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_TERMINAL, g_language));
		CUPRINT_Data(offset, buffer, L0);

		sprintf(buffer, "%ld.%02ld %%%c ", (ulCard * 100) / (ulEnd_transaction - ulBegin_transaction), ((ulCard * 100 * 100) / (ulEnd_transaction - ulBegin_transaction)) % 100, VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_CARD, g_language));
		CUPRINT_Data(offset, buffer, L0);

		sprintf(buffer, "%ld.%02ld %%%c ", ((ulMMI_pin_off_line + ulMMI_pin_on_line + ulMMI_amount + ulMMI_account_type + ulMMI_langue + ulMMI_selappli + ulMMI_force_OLP + ulMMI_force_CAA + ulMMI_force_COMP + ulMMI_ticket) * 100) / (ulEnd_transaction - ulBegin_transaction), (((ulMMI_pin_off_line + ulMMI_pin_on_line + ulMMI_amount + ulMMI_account_type + ulMMI_langue + ulMMI_selappli + ulMMI_force_OLP + ulMMI_force_CAA + ulMMI_force_COMP + ulMMI_ticket) * 100 * 100) / (ulEnd_transaction - ulBegin_transaction)) % 100, VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_MMI, g_language));
		CUPRINT_Data(offset, buffer, L0);

		sprintf(buffer, "%ld.%02ld %%%c ", (ulHOST_comm * 100) / (ulEnd_transaction - ulBegin_transaction), ((ulHOST_comm * 100 * 100) / (ulEnd_transaction - ulBegin_transaction)) % 100, VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_HOST_COMMUNICATION, g_language));
		CUPRINT_Data(offset, buffer, L0);

		CUPRINT_Bottom_Frame(0, 24);
		CUPRINT_Blanks_Lines(1);

		// Print computation time
		CUPRINT_String_XT(CUMESS_ReadMessageReceipt(CU_MESS_COMPUTATION_TIME, g_language), ALIGN_LEFT, L1);
		sprintf(buffer, "%ld ms", ((ulEnd_computation - ulBegin_computation) - ulMMI_amount - ulMMI_account_type - ulMMI_langue - ulMMI_selappli - ulMMI_force_OLP - ulMMI_force_CAA - ulMMI_force_COMP - ulMMI_pin_off_line - ulMMI_pin_on_line - ulHOST_comm) * 10);
		CUPRINT_Top_Frame_String(0, 24, buffer, ALIGN_RIGHT);


		// Print terminal and card times
		sprintf(buffer, "%ld ms%c ", ulTerminal * 10, VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_TERMINAL, g_language));
		CUPRINT_Data(offset, buffer, L0);

		sprintf(buffer, "%ld ms%c ", ulCard * 10, VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_CARD, g_language));
		CUPRINT_Data(offset, buffer, L0);

		sprintf(buffer, "%ld.%02ld  %%%c ", (ulTerminal * 100) / (ulTerminal + ulCard), ((ulTerminal * 100 * 100) / (ulTerminal + ulCard)) % 100, VERTICAL_BAR);
		sprintf(offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_TERMINAL_COMPUTATION, g_language));
		CUPRINT_Data(offset, buffer, L0);

		CUPRINT_Bottom_Frame(0, 24);

		// Print the comment
		CUPRINT_String_XT(CUMESS_ReadMessageReceipt(CU_MESS_COMMENT, g_language), ALIGN_LEFT, L0);
	}
	else
	{
		CUPRINT_String_XT("Not available", ALIGN_CENTER, L1);
	}

	CUPRINT_Blanks_Lines(1);
}
#endif /* _TOOLWARE_ */

#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function analyses the transaction flow.
//===========================================================================
static void transaction_flow_analysis(void)
{
	static unsigned char    buffer[30];
	unsigned char   ac_AdditionnalText[30];

	unsigned char    ucCurrent_step            = 0;
	unsigned char    ucPrevious_step           = 0;

	unsigned char    ucNb_commandes            = 0;
	unsigned char    ucNb_tt_commandes         = 0;
	unsigned long    ulExtra_time              = 0;
	unsigned long    ulCard_time               = 0;
	unsigned long    ulTerminal_time           = 0;
	unsigned long    ulTotal_extra_time        = 0;
	unsigned long    ulTotal_card_time         = 0;
	unsigned long    ulTotal_terminal_time     = 0;
	unsigned long    ulAdditionnal_time        = 0;
	unsigned short   usFound;
	unsigned short   i = 0;

	TLV_TREE_NODE    hTree;
	t_process        process = IS_IN_PROGRESS;

	DataElement      EltCmd;
	DataElement      EltRsp;
	DataElement      EltBegin;
	DataElement      EltEnd;
	DataElement      AddTime;
	unsigned long    ulBegin_command_time;
	unsigned long    ulEnd_command_time;
	unsigned long    ulPrevious_command_time   = 0;

	// Print header
	CUPRINT_Boundary_Line(0, 24);
	CUPRINT_Blanks_Lines(1);

	sprintf(buffer, "3 - %s", CUMESS_ReadMessageReceipt(CU_MESS_TRANSACTION_FLOW_ANALYSIS, g_language));
	CUPRINT_String_XT(buffer, ALIGN_LEFT, L4);
	CUPRINT_Blanks_Lines(1);

	while (process != IS_DONE)
	{
		hTree = Engine_GetCommand(i);
		usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APDU_CMD, &EltCmd);

		// no more commands or no commands
		if (!usFound)
		{
			// there is no commands
			if (i == 0)
				process = IS_NOT_AVAILABLE;
			// process is done
			else
				process = IS_DONE;
		}
		else
		{
			// Retreive other information
			usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APDU_RESPONSE, &EltRsp);
			usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_BEGIN_TIMER, &EltBegin);
			usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_END_TIMER, &EltEnd);

			// Convert into long format
			ulBegin_command_time = CharToLong (EltBegin.ptValue);
			ulEnd_command_time =   CharToLong (EltEnd.ptValue);

			// First command
			if (i == 0)
			{
				define_step(&EltCmd, &ucCurrent_step);


				// Init datas
				ucPrevious_step         = ucCurrent_step;
				ucNb_commandes          = 1;
				ulExtra_time            = 0;
				ulCard_time             = ulEnd_command_time - ulBegin_command_time;
				ulTerminal_time         = 0;                // time would be calculated during the process of the next command
				ulPrevious_command_time = ulEnd_command_time;
				// terminal time = time between two commads
				// be carefull, this time may contain extra time like MMI or Host
			}
			else
			{
				define_step(&EltCmd, &ucCurrent_step);

				// same step that previous command
				if (ucCurrent_step == ucPrevious_step)
				{
					ulCard_time = ulCard_time + (ulEnd_command_time - ulBegin_command_time);
					ulTerminal_time = ulTerminal_time + (ulBegin_command_time - ulPrevious_command_time);
					ulPrevious_command_time = ulEnd_command_time;
					ucNb_commandes ++;
				}
				// new step
				else
				{
					// Print previous step statistics
					// only if it is not the first command
					if (ucPrevious_step != 0)    // + check if it is necessary yet
					{
						// ODA is SDA
						// Specific process if it is ODA step and it is a SDA
						// because there is no command : terminal time begin at the end of the previous command
						if (((g_TFS & OFFLINE_DATA_AUTHENTICATION_IS_SDA)       ==    OFFLINE_DATA_AUTHENTICATION_IS_SDA) &
							((g_TFS & OFFLINE_DATA_AUTHENTICATION_IS_PERFORMED) !=    OFFLINE_DATA_AUTHENTICATION_IS_PERFORMED) &
							((g_TFS & INITIATE_APPLICATION_IS_PERFORMED)        ==    INITIATE_APPLICATION_IS_PERFORMED))
						{
							ulExtra_time = 0;

							// Print INITIATE_APPLICATION_PROCESSING step
							print_statistics(INITIATE_APPLICATION_PROCESSING, ulTerminal_time, ulCard_time, ulExtra_time, ucNb_commandes, 0, 0);

							// Update total time
							ulTotal_card_time = ulTotal_card_time + ulCard_time;
							ulTotal_terminal_time = ulTotal_terminal_time + ulTerminal_time;
							ucNb_tt_commandes = ucNb_tt_commandes + ucNb_commandes;

							// reInit staticstics
							ulTerminal_time = 0;
							ulCard_time = 0;        // no command in SDA
							ulExtra_time = 0;
							ucNb_commandes = 0;

							/* If Pin was on-line verified, ulExtra_Time must be added with Pin code input time (No CARDHOLDER_VERIFICATION step in this case) */
							if ((g_TFS & ONLINE_PIN_IS_TO_BE_PERFORMED) == ONLINE_PIN_IS_TO_BE_PERFORMED)
							{
								// Warning : in case of only on-line Pin-code verification, "Cardholder Verification" step isn't existing so the ulMMI_pin_on_line must be deducted here
								ulExtra_time += ulMMI_pin_on_line;
							}

							// Process to the calculation of OFFLINE_DATA_AUTHENTICATION times
							ulTerminal_time = ulBegin_command_time - ulPrevious_command_time - ulExtra_time;

							hTree = Engine_GetODATime();
							usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_ODA_TIME, &AddTime);
							if (usFound)
							{
								long l_l_TicksTime;
								strcpy(ac_AdditionnalText, CUMESS_ReadMessageReceipt(CU_MESS_RSA_TIME, g_language));
								l_l_TicksTime = ((unsigned long)(AddTime.ptValue[3] << 24)) + ((unsigned long)(AddTime.ptValue[2] <<16)) + ((unsigned long)(AddTime.ptValue[1] <<8)) + ((unsigned long)AddTime.ptValue[0]);
								ulAdditionnal_time = TimeCounter_ConvertTicksToTime(l_l_TicksTime, 1000);
							}
							else
							{
								ac_AdditionnalText[0] = 0;
								ulAdditionnal_time = 0;
							}

							// Print the OFFLINE_DATA_AUTHENTICATION step
							print_statistics(OFFLINE_DATA_AUTHENTICATION, ulTerminal_time, ulCard_time, ulExtra_time, ucNb_commandes, ac_AdditionnalText, ulAdditionnal_time);

							// Update total time
							ulTotal_terminal_time = ulTotal_terminal_time + ulTerminal_time;    // the only which has been modify

							// ReInit statistics
							ulExtra_time = 0;
							ulTerminal_time = 0;
							ulCard_time = ulEnd_command_time - ulBegin_command_time;
							ulPrevious_command_time = ulEnd_command_time;
							ucNb_commandes = 1;                // the current command which is the command of the next step

							// on a effectue le l'authentification statique
							g_TFS = g_TFS | OFFLINE_DATA_AUTHENTICATION_IS_PERFORMED;
						}
						else
							// ODA is a DDA
						{
							if (((g_TFS & OFFLINE_DATA_AUTHENTICATION_IS_DDA)       ==    OFFLINE_DATA_AUTHENTICATION_IS_DDA) &
								((g_TFS & OFFLINE_DATA_AUTHENTICATION_IS_PERFORMED) !=    OFFLINE_DATA_AUTHENTICATION_IS_PERFORMED) &
								((g_TFS & INITIATE_APPLICATION_IS_PERFORMED)        ==    INITIATE_APPLICATION_IS_PERFORMED))
							{
								ulExtra_time = 0;

								// Print INITIATE_APPLICATION_PROCESSING
								print_statistics(INITIATE_APPLICATION_PROCESSING, ulTerminal_time, ulCard_time, ulExtra_time, ucNb_commandes, 0, 0);

								// Update total times
								ulTotal_card_time = ulTotal_card_time + ulCard_time;
								ulTotal_terminal_time = ulTotal_terminal_time + ulTerminal_time;
								ucNb_tt_commandes = ucNb_tt_commandes + ucNb_commandes;

								// ReInit statistics
								ulTerminal_time = 0;
								ulCard_time = 0;
								ulExtra_time = 0;
								ucNb_commandes = 1;

								/* If Pin was on-line verified, ulExtra_Time must be added with Pin code input time (No CARDHOLDER_VERIFICATION step in this case) */
								if ((g_TFS & ONLINE_PIN_IS_TO_BE_PERFORMED) == ONLINE_PIN_IS_TO_BE_PERFORMED)
								{
									// Warning : in case of only on-line Pin-code verification, "Cardholder Verification" step isn't existing so the ulMMI_pin_on_line must be deducted here
									ulExtra_time += ulMMI_pin_on_line;
								}

								// Process to the calculation of OFFLINE_DATA_AUTHENTICATION times
								ulTerminal_time = ulBegin_command_time - ulPrevious_command_time - ulExtra_time;

								// ReInit statistics
								//                                ulTerminal_time = 0;
								ulCard_time = ulEnd_command_time - ulBegin_command_time;
								ulPrevious_command_time = ulEnd_command_time;
								ucNb_commandes = 1;

								// on a effectue le l'authentification statique
								g_TFS = g_TFS | OFFLINE_DATA_AUTHENTICATION_IS_PERFORMED;
							}
							else
							{
								// MMI processing
								switch (ucPrevious_step)
								{
								case APPLICATION_SELECTION :
									ulExtra_time = ulMMI_amount + ulMMI_account_type + ulMMI_langue + ulMMI_selappli;
									ulTerminal_time += (ulBegin_command_time - ulPrevious_command_time) - ulExtra_time;
									//                                    if (ulTerminal_time > ulExtra_time)
									//                                        ulTerminal_time -= ulExtra_time;
									//                                    /* else */
									//                                        /* We are in a multi-application selection, musn't be add several times */
									break;

								case CARDHOLDER_VERIFICATION : // Warning : this step is present only with an off-line pin verification
									// In case of only on-line pin verification this step isn't present
									ulExtra_time = ulMMI_pin_off_line;

									if ((g_TFS & ENCIPHERED_PIN_IS_TO_BE_PERFORMED) == ENCIPHERED_PIN_IS_TO_BE_PERFORMED)
									{
										ulTerminal_time = ulTerminal_time + (ulBegin_command_time - ulPrevious_command_time) - ulExtra_time - LOST_TIME_IN_BOOSTER;
										ulCard_time = ulCard_time + LOST_TIME_IN_BOOSTER;
									}
									else
									{
										ulTerminal_time = ulTerminal_time + (ulBegin_command_time - ulPrevious_command_time) - ulExtra_time;
									}
									break;

								case ACTION_ANALYSIS :
									ulExtra_time = 0;

									/* Host time management */
									ulTerminal_time = ulTerminal_time + (ulBegin_command_time - ulPrevious_command_time);
									if (ulTerminal_time > ulHOST_comm)
									{
										ulExtra_time += ulHOST_comm;
										ulTerminal_time -= ulHOST_comm;
									}
									break;

								case OFFLINE_DATA_AUTHENTICATION :
									// ulExtra_time = ulMMI_force_OLP;
									ulExtra_time = 0;
									ulTerminal_time = ulTerminal_time + (ulBegin_command_time - ulPrevious_command_time) - ulExtra_time;

									hTree = Engine_GetODATime();
									usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_ODA_TIME, &AddTime);
									if (usFound)
									{
										long l_l_TicksTime;
										strcpy(ac_AdditionnalText, CUMESS_ReadMessageReceipt(CU_MESS_RSA_TIME, g_language));
										l_l_TicksTime = ((unsigned long)(AddTime.ptValue[3] << 24)) + ((unsigned long)(AddTime.ptValue[2] <<16)) + ((unsigned long)(AddTime.ptValue[1] <<8)) + ((unsigned long)AddTime.ptValue[0]);
										ulAdditionnal_time = TimeCounter_ConvertTicksToTime(l_l_TicksTime, 1000);
									}
									else
									{
										ac_AdditionnalText[0] = 0;
										ulAdditionnal_time = 0;
									}
									break;

								case COMPLETION :
									/* Warning : COMPLETION WILL BE MADE AT THE END OF THIS FUNCTION NOT HERE ! */
									break;

								case INITIATE_APPLICATION_PROCESSING :
								case PROCESSING_RESTRICTIONS :
								case TERMINAL_RISK_MANAGEMENT :
								case ONLINE_PROCESSING :
								case ISSUER_TO_CARD_SCRIPT_PROCESSING :
								case TRANSACTION_RECEIPT :
								default : /* case : INITIATE_APPLICATION_PROCESSING */
									ulExtra_time = 0;
									ulTerminal_time += (ulBegin_command_time - ulPrevious_command_time) - ulExtra_time;
									break;
								}
								ulTotal_extra_time = ulTotal_extra_time + ulExtra_time;
								ulTotal_card_time = ulTotal_card_time + ulCard_time;
								ulTotal_terminal_time = ulTotal_terminal_time + ulTerminal_time;
								ucNb_tt_commandes = ucNb_tt_commandes + ucNb_commandes;

								// Print previous step
								if (ucPrevious_step == OFFLINE_DATA_AUTHENTICATION)
									print_statistics(ucPrevious_step, ulTerminal_time, ulCard_time, ulExtra_time, ucNb_commandes, ac_AdditionnalText, (const unsigned long)ulAdditionnal_time);
								else
									print_statistics(ucPrevious_step, ulTerminal_time, ulCard_time, ulExtra_time, ucNb_commandes, 0, 0);
								ulExtra_time = 0; /* For next use */
								// ReInit statistics
								ulTerminal_time = 0;
								ulCard_time = ulEnd_command_time - ulBegin_command_time;
								ulPrevious_command_time = ulEnd_command_time;
								ucNb_commandes = 1;
							}
						}
					}
					ucPrevious_step = ucCurrent_step;
				}
			}

			i ++;
		}
		// Release local TLV tree
		TlvTree_ReleaseEx(&hTree);

	}

	if (process != IS_NOT_AVAILABLE)
	{
		// Print the last step
		// Warning : the last step is specific because in this case, lasts times has host, or force_comp must be added
		switch (ucPrevious_step)
		{
		case COMPLETION :
			if ((ulTerminal_time + ulEnd_computation - ulPrevious_command_time) > ulHOST_comm)
				ulExtra_time = ulHOST_comm + ulMMI_force_COMP;
			break;

		case ACTION_ANALYSIS :
			ulExtra_time = ulMMI_force_OLP + ulMMI_force_CAA + ulMMI_force_COMP;
			break;

		case CARDHOLDER_VERIFICATION :
			ulExtra_time = ulMMI_force_OLP + ulMMI_force_CAA + ulMMI_force_COMP;
			break;

		default :
			break;
		}

		// Update total time
		ulTerminal_time = ulTerminal_time + (ulEnd_computation - ulPrevious_command_time) - ulExtra_time;
		ulTotal_card_time = ulTotal_card_time + ulCard_time;
		ucNb_tt_commandes = ucNb_tt_commandes + ucNb_commandes;

		print_statistics(ucPrevious_step, ulTerminal_time, ulCard_time, ulExtra_time, ucNb_commandes, 0, 0);

		// Print the receipt step
		print_statistics(TRANSACTION_RECEIPT, 0, 0, ulMMI_ticket, 0, 0, 0);
	}
	else
	{
		CUPRINT_String_XT("Not available", ALIGN_CENTER, L1);
	}

	CUPRINT_Blanks_Lines(1);
}
#endif /* _TOOLWARE_ */

#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function defines the current step with a command contained into
//! a DataElement. This function works only if you call it for eachprevious 
//! command. (it stored information in the g_TFS).
//! \param[in] request : the DataElement request containing the command sent.
//! \param[out] step : the number of the step (ex: APPLICATION_SELECTION).
//===========================================================================
static void define_step(const DataElement *request, unsigned char *step)
{
	switch (request->ptValue[0])
	{
	case 0x00 :
		switch (request->ptValue[1])
		{
			// VERIFY
		case 0x20 :
			*step = CARDHOLDER_VERIFICATION;
			break;

			// EXTERNAL AUTHENTICATE
		case 0x82 :
			*step = ONLINE_PROCESSING;
			break;

			// GET CHALLENGE
		case 0x84 :
			*step = CARDHOLDER_VERIFICATION;
			break;

			// INTERNAL AUTHENTICATE
		case 0x88 :
			// Initiatiate application is completed => print the authentication step
			if ((g_TFS & INITIATE_APPLICATION_IS_PERFORMED) != INITIATE_APPLICATION_IS_PERFORMED)
				g_TFS = g_TFS | INITIATE_APPLICATION_IS_PERFORMED;

			*step = OFFLINE_DATA_AUTHENTICATION;
			break;

			// SELECT
		case 0xA4 :
			// PSE
			if ((g_TFS & SELECTION_METHOD_IS_DSM) == SELECTION_METHOD_IS_DSM)
			{
				// First select
				if ((g_TFS & FIRST_SELECT_IS_PERFORMED) != FIRST_SELECT_IS_PERFORMED)
				{
					*step = APPLICATION_SELECTION;
					g_TFS = g_TFS | FIRST_SELECT_IS_PERFORMED;
				}
				// Final Select
				else
				{
					*step = APPLICATION_SELECTION;
					g_TFS = g_TFS | FINAL_SELECT_IS_PERFORMED;
				}
			}
			// no PSE
			else
			{
				*step = APPLICATION_SELECTION;
			}
			break;

			// READ_RECORD
		case 0xB2 :
			if ((g_TFS & SELECTION_METHOD_IS_DSM) == SELECTION_METHOD_IS_DSM)
			{
				if ((g_TFS & FINAL_SELECT_IS_PERFORMED) != FINAL_SELECT_IS_PERFORMED)
					*step = APPLICATION_SELECTION;
				else
					*step = INITIATE_APPLICATION_PROCESSING;
			}
			else
			{
				*step = INITIATE_APPLICATION_PROCESSING;
			}
			break;

			// ERROR
		default :
			*step = ERROR_COMMAND_UNKNOWN;
			break;
		}
		break;

	case 0x80 :
		switch (request->ptValue[1])
		{
			// CARD BLOCK
		case 0x16 :
			*step = ISSUER_TO_CARD_SCRIPT_PROCESSING;
			break;

			// APPLICATION BLOCK
		case 0x18 :
			*step = ISSUER_TO_CARD_SCRIPT_PROCESSING;
			break;

			// APPLICATION UNBLOCK
		case 0x1E :
			*step = ISSUER_TO_CARD_SCRIPT_PROCESSING;
			break;

			// GET PROCESSING OPTIONS
		case 0xa8 :
			*step = INITIATE_APPLICATION_PROCESSING;
			break;

			// GENERATE APPLICATION CRYPTOGRAM
		case 0xAE :
			// l'initialisation de l'appli est terminee : pour afficher l'authentification
			if ((g_TFS & INITIATE_APPLICATION_IS_PERFORMED) != INITIATE_APPLICATION_IS_PERFORMED)
				g_TFS = g_TFS | INITIATE_APPLICATION_IS_PERFORMED;

			if ((g_TFS & ACTION_ANALISYS_IS_PERFORMED) != ACTION_ANALISYS_IS_PERFORMED)
			{
				g_TFS = g_TFS | ACTION_ANALISYS_IS_PERFORMED;
				*step = ACTION_ANALYSIS;
			}
			else
			{
				g_TFS = g_TFS | ONLINE_PROCESSING_IS_PERFORMED;
				*step = COMPLETION;
			}
			break;

			// GET DATA
		case 0xCA :
			// l'initialisation de l'appli est terminee
			if ((g_TFS & INITIATE_APPLICATION_IS_PERFORMED) != INITIATE_APPLICATION_IS_PERFORMED)
				g_TFS = g_TFS | INITIATE_APPLICATION_IS_PERFORMED;

			switch (request->ptValue[3])
			{
				// Last Online Application Transaction Counter Register
				// seulement si cette donnee n'est pas deja presente dans le terminal
			case 0x13 :
				*step = TERMINAL_RISK_MANAGEMENT;
				break;
				// PIN Try Counter
				// si le CVM necessite une verification du code PIN
			case 0x17 :
				*step = CARDHOLDER_VERIFICATION;
				break;
				// Application Transaction Counter
				// seulement si cette donnee n'est pas deja presente dans le terminal
			case 0x36 :
				*step = TERMINAL_RISK_MANAGEMENT;
				break;
			}
			break;

			// ERROR
		default :
			*step = ERROR_COMMAND_UNKNOWN;
			break;
		}
		break;

		// ERROR
	default :
		*step = ERROR_COMMAND_UNKNOWN;
		break;
	}
}
#endif /* _TOOLWARE_ */

#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function prints some informations : 
//! - label
//! - terminal_time
//! - card_time
//! - extra_time
//! - terminal ratio
//! - nb_commands
//! - AdditionnalTime
//===========================================================================
static void print_statistics(const unsigned char step,
							 const unsigned long terminal_time,
							 const unsigned long card_time,
							 const unsigned long extra_time,
							 const unsigned char nb_commands,
							 const unsigned char * ptr_AdditionnalText,
							 const unsigned long AdditionnalTime)
{
	unsigned char buffer[48];
	unsigned char offset[48];
	unsigned char *label = NULL;
	int           step_number;

	switch (step)
	{
	case APPLICATION_SELECTION :
		step_number = CU_MESS_STEP_APPLICATION_SELECTION;
		break;
	case INITIATE_APPLICATION_PROCESSING :
		step_number = CU_MESS_STEP_INITIATE_PROCESSING_AND_READ_DATA;
		break;
	case OFFLINE_DATA_AUTHENTICATION :
		step_number = CU_MESS_STEP_OFFLINE_DATA_AUTHENTICATION;
		break;
	case PROCESSING_RESTRICTIONS :
		step_number = CU_MESS_STEP_PROCESSING_RESTRICTIONS;
		break;
	case CARDHOLDER_VERIFICATION :
		step_number = CU_MESS_STEP_CARDHOLDER_VERIFICATION;
		break;
	case TERMINAL_RISK_MANAGEMENT :
		step_number = CU_MESS_STEP_TERMINAL_RISK_MANAGEMENT;
		break;
	case ACTION_ANALYSIS :
		step_number = CU_MESS_STEP_TERMINAL_AND_CARD_ACTION_ANALYSIS;
		break;
	case ONLINE_PROCESSING :
		step_number = CU_MESS_STEP_ONLINE_PROCESSING;
		break;
	case ISSUER_TO_CARD_SCRIPT_PROCESSING :
		step_number = CU_MESS_STEP_ISSUER_TO_CARD_SCRIPT_PROCESSING;
		break;
	case COMPLETION :
		step_number = CU_MESS_STEP_COMPLETION;
		break;
	case TRANSACTION_RECEIPT :
		step_number = CU_MESS_STEP_TRANSACTION_RECEIPT;
		break;
	case ERROR_COMMAND_UNKNOWN:
		step_number = CU_MESS_STEP_COMMAND_UNKNOWN;
		break;
	default :
		step_number = CU_MESS_STEP_UNRECOGNIZED;
		break;
	}

	label = (unsigned char *) CUMESS_ReadMessageReceipt(step_number, g_language);
	sprintf((char *) buffer, "%ld ms", (terminal_time + card_time + extra_time) * 10);

	// Print title
	CUPRINT_String_XT(label, ALIGN_LEFT, L1);
	CUPRINT_Top_Frame_String(0, 24, buffer, ALIGN_RIGHT);

	// Print terminal time
	sprintf((char *) buffer, "%ld ms%c ", terminal_time * 10, VERTICAL_BAR);
	sprintf((char *) offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_TERMINAL, g_language));
	CUPRINT_Data(offset, buffer, L0);

	// Print card time
	sprintf((char *) buffer, "%ld ms%c ", card_time * 10, VERTICAL_BAR);
	sprintf((char *) offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_CARD, g_language));
	CUPRINT_Data(offset, buffer, L0);

	// Print extra time (MMI of Host)
	sprintf((char *) buffer, "%ld ms%c ", extra_time * 10, VERTICAL_BAR);
	sprintf((char *) offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_EXTRA, g_language));
	CUPRINT_Data(offset, buffer, L0);

	// Print terminal ratio
	sprintf((char *) buffer, "%ld  %%%c ", ((terminal_time * 10) * 100) / ((terminal_time * 10) + (card_time * 10) + (extra_time * 10)), VERTICAL_BAR);
	sprintf((char *) offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_TERMINAL_STEP, g_language));
	CUPRINT_Data(offset, buffer, L0);

	// Print the number of commands
	sprintf((char *) buffer, "%d   %c ", nb_commands, VERTICAL_BAR);
	sprintf((char *) offset, "%c %s", VERTICAL_BAR, CUMESS_ReadMessageReceipt(CU_MESS_COMMANDS, g_language));
	CUPRINT_Data(offset, buffer, L0);

	// Print the additionnal line
	if (ptr_AdditionnalText)
		if (strlen(ptr_AdditionnalText) > 0)
		{
			sprintf((char *) buffer, "%ld ms%c ", AdditionnalTime, VERTICAL_BAR);
			sprintf((char *) offset, "%c %s", VERTICAL_BAR, ptr_AdditionnalText);
			CUPRINT_Data(offset, buffer, L0);
		}

		CUPRINT_Bottom_Frame(0, 24);
		CUPRINT_Blanks_Lines(1);
}
#endif /* _TOOLWARE_ */

#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function returns the application selection method.
//! \param[in] response : DataElement containing the selection method.
//! \return the coded application selection method : 
//! - \ref DIRECTORY_SELECTION_METHOD
//! - \ref EXPLICIT_SELECTION_METHOD
//! - \ref CARD_IS_BLOCKED_OR_COMMAND_NOT_SUPPORTED
//! - \ref APPLICATION_IS_BLOCKED
//! - \ref ERROR_RESPONSE_UNKNOWN
//===========================================================================
static Selection_Method get_selection_method(const DataElement *response)
{
	if ((response->ptValue[response->length -2] == 0x90) &
		(response->ptValue[response->length - 1] == 0x00))
		return DIRECTORY_SELECTION_METHOD;
	else
		if ((response->ptValue[response->length -2] == 0x6A) &
			(response->ptValue[response->length - 1] == 0x82))
			return EXPLICIT_SELECTION_METHOD;
		else
			if ((response->ptValue[response->length -2] == 0x6A) &
				(response->ptValue[response->length - 1] == 0x81))
				return CARD_IS_BLOCKED_OR_COMMAND_NOT_SUPPORTED;
			else
				if ((response->ptValue[response->length -2] == 0x62) &
					(response->ptValue[response->length - 1] == 0x83))
					return APPLICATION_IS_BLOCKED;
				else
					return ERROR_RESPONSE_UNKNOWN;

}
#endif /* _TOOLWARE_ */

#ifdef _TOOLWARE_
//===========================================================================
//! \brief This function prints the the Ingenico Logo and "designed for EMV".
//===========================================================================
static void print_header(void)
{
	CULOGO_Print_Ingenico();
	CUPRINT_String_XT("designed for EMV", ALIGN_CENTER, L1);
}
#endif /* _TOOLWARE_ */

//===========================================================================
//! \brief This function prints informations about Ingenico : Adress, Fax, Tel.
//===========================================================================
static void print_tail(void)
{
	CUPRINT_Boundary_Line(0, 24);
	CUPRINT_Blanks_Lines(1);
	/*&BEGIN FT/08/3956/MA trailer Ingenico */
	CUPRINT_String_XT(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_SMO_INFO_0, g_language), ALIGN_CENTER, L1);
	CUPRINT_String_XT(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_SAGEM_MONETEL, g_language), ALIGN_CENTER, L1);
	CUPRINT_Blanks_Lines(1);
	/*&END FT/08/3956/MA trailer Ingenico */

	CUPRINT_String_XT(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_SMO_INFO_1, g_language), ALIGN_CENTER, L0);
	CUPRINT_String_XT(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_SMO_INFO_2, g_language), ALIGN_CENTER, L0);
	CUPRINT_Double_String(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_SMO_INFO_3, g_language), CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_SMO_INFO_4, g_language), L0);

	CUPRINT_Blanks_Lines(1);
	CUPRINT_Boundary_Line(0, 24);
}

/* ======================================================================== */
/* Global function implementation (Public)                                  */
/* ======================================================================== */

//===========================================================================
void CURECEIPT_Print_Ticket_POS_Demo(TLV_TREE_NODE hInputTLVTree, unsigned char status_tr)
{
	int                unit;

	unsigned short   i;
	unsigned short   usFound;
	unsigned short   lg_code;
	unsigned short   currency_code;

	unsigned char    currency[4];
	unsigned char    tvr_ascii[11];
	unsigned char    aid_ascii[LEN_AID*2];
	unsigned char    pan_ascii[40 + 1];
	unsigned char    buffer[30], tmp[30];

	TLV_TREE_NODE    hTree;
	DataElement      elt;
	unsigned char	 TransDate[3];
	unsigned char	 TransTime[3];
	unsigned long    AmAuth = 0;
	static const unsigned long RequiredTags[] = { TAG_APPLICATION_LABEL, TAG_APPLICATION_PREFFERRED_NAME, 
		TAG_APPLI_PRIM_ACCOUNT_NB };
	int len;


	g_language = PSQ_Give_Language();

	CUPRINT_Open_Printer();

#ifdef _USE_UCM_
	// If printer haven't been opened
	if (g_pPrinter == NULL)
	{
		// We cannot continue to print something
		return;
	}
#endif


	CUDB_Get_cardholder_language(&lg_code);

	usFound = CUSERV_Extract_Element_TLV_Tree(&hInputTLVTree, TAG_TRANSACTION_CURRENCY_CODE, &elt);
	if(usFound)
	{
		currency_code = CharToShort(elt.ptValue);
	}
	else
	{
		currency_code = 0;
	}

	i = 0;
	usFound = FALSE;
    // unit initialisation
	unit = 0;
	while ((!usFound) && (i < L_NBCURCY))
	{
		usFound = (ct_confCurrency[i].currency == currency_code);
		if (!usFound)
		{
			i++;
		}
		else
		{
			if (strcmp("EUR", ct_confCurrency[i].label) == 0)
				strcpy((char *) currency, "\xEE");
			else
				strcpy((char *) currency, ct_confCurrency[i].label);
			unit = ct_confCurrency[i].unit;
		}
	}


	// ***** NEW_DESIGN *****
	// Print header
	// &BEGIN FT/08/3956/MA trailer Ingenico
	CULOGO_Print_Ingenico();
	CUPRINT_Boundary_Line(0, 24);
	CUPRINT_Blanks_Lines(1);
	// &END FT/08/3956/MA trailer Ingenico

	Hexascii(aid_ascii, &Aid[1], Aid[0] * 2);    // Aid[0] = lg
	aid_ascii[Aid[0] * 2] = 0x00;

	if (status_tr == STATUS_TR_REFUND_APPROVED)
	{
		strcpy((char *) tmp, CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_REFUND_TRANS, lg_code));
		sprintf((char *) buffer, "\x1b""E%s""\x1b""F", tmp);
		CUPRINT_String_XT(buffer, ALIGN_LEFT, L1);
	}

	// Get the RequiredTags from from EMVDC Data base.
	hTree = Engine_GetDataElements(sizeof(RequiredTags) / sizeof(RequiredTags[0]), RequiredTags);

	usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APPLICATION_LABEL, &elt);

	// Name and label
	if (usFound)
	{
		// strcpy((char *) tmp, CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_APPLI_NAME, lg_code));
		memset(tmp, 0, sizeof(tmp));
		memcpy(tmp, elt.ptValue, elt.length);
		sprintf((char *) buffer, "\x1b""E%s""\x1b""F", tmp);
		CUPRINT_String_XT(buffer, ALIGN_LEFT, L1);
	}
	else
	{
		usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APPLICATION_PREFFERRED_NAME, &elt);
		if (usFound)
		{
			// strcpy((char *) tmp, CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_APPLI_NAME, lg_code));
			memset(tmp, 0, sizeof(tmp));
			memcpy(tmp, elt.ptValue, elt.length);
			sprintf((char *) buffer, "\x1b""E%s""\x1b""F", tmp);
			CUPRINT_String_XT(buffer, ALIGN_LEFT, L1);
		}
	}

	// Date & Hour
	usFound = CUSERV_Extract_Element_TLV_Tree(&hInputTLVTree, TAG_TRANSACTION_DATE, &elt);
	if (usFound)
	{
		memcpy(TransDate, elt.ptValue, elt.length);
	}

	usFound = CUSERV_Extract_Element_TLV_Tree(&hInputTLVTree, TAG_TRANSACTION_TIME, &elt);
	if (usFound)
	{
		memcpy(TransTime, elt.ptValue, elt.length);
	}

	sprintf ((char *) buffer, "%.2x/%.2x/%.2x  %.2x:%.2x",
		TransDate[2],
		TransDate[1],
		TransDate[0],
		TransTime[0],
		TransTime[1]
	);
	CUPRINT_String_XT(buffer, ALIGN_LEFT, L1);

	// AID
	sprintf((char *) buffer, "%.20s\n",aid_ascii);
	CUPRINT_String_XT(buffer, ALIGN_LEFT, L1);

	// PAN
	usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_APPLI_PRIM_ACCOUNT_NB, &elt);
	if (usFound)
	{
		// &BEGIN FT/7706/PADSS: Hide the PAN
		memset (pan_ascii, 0, sizeof(pan_ascii) );
		len = 2 * elt.length;
		if (Hexascii((unsigned char *) pan_ascii, (unsigned char *) elt.ptValue, len) == OK)
		{
			if (pan_ascii[len - 1] == 'F')
			{
				len--;
				pan_ascii[len] = '\0';
			}

			memset (&pan_ascii[6], '*', len - 6 - 4);
		}
		// &END FT/7706/PADSS: Hide the PAN

		sprintf ((char *) buffer, "%.30s\n",pan_ascii);
		CUPRINT_String_XT(buffer, ALIGN_LEFT, L1);
	}

	// Release local TLV tree
	TlvTree_ReleaseEx(&hTree);

	// State
	if ((status_tr == STATUS_TR_APPROVED) ||
		(status_tr == STATUS_TR_REFUND_APPROVED))
	{
		CUPRINT_Top_Frame_String(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_APPROVED, g_language), ALIGN_CENTER);
	}
	else
	{
		CUPRINT_Top_Frame_String(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_DECLINED, g_language), ALIGN_CENTER);
	}
	CUPRINT_String_Frame(0, 24, "\0", ALIGN_CENTER);

	// Amount
	usFound = CUSERV_Extract_Element_TLV_Tree(&hInputTLVTree, TAG_AMOUNT_AUTH_BIN, &elt);
	if (usFound)
	{
		AmAuth = CharToLong (elt.ptValue);
	}

	if (unit == 0)
	{
		sprintf((char *) buffer, "%8lu %s", AmAuth, currency);
	}
	else
	{
		sprintf((char *) buffer, "%6lu.%02lu %s", AmAuth/100, AmAuth%100, currency);
	}
	CUPRINT_Double_String_Frame(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_AMOUNT, g_language), buffer);
	CUPRINT_String_Frame(0, 24, " ", ALIGN_LEFT);

	// TVR
	usFound = CUSERV_Extract_Element_TLV_Tree(&hInputTLVTree, TAG_TVR, &elt);
	if (usFound)
	{
		Hexascii(tvr_ascii, elt.ptValue, 10);
		tvr_ascii[10] = 0x00;
	}
	CUPRINT_Double_String_Frame(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_TRANSACTION_VERIFICATION_STATUS, g_language), tvr_ascii);
	CUPRINT_Bottom_Frame(0, 24);

	// Signature ?
	if (signature_asked == TRUE)
	{
		CUPRINT_String_Frame(0, 24, " ", ALIGN_LEFT);
		CUPRINT_String_Frame(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_SIGNATURE, g_language), ALIGN_LEFT);
		CUPRINT_String_Frame(0, 24, " ", ALIGN_LEFT);
		CUPRINT_String_Frame(0, 24, " ", ALIGN_LEFT);
		CUPRINT_String_Frame(0, 24, " ", ALIGN_LEFT);
	}


	CUPRINT_Blanks_Lines(1);
	print_tail();

	CUPRINT_Paper_Feed();
	CUPRINT_Close_Printer();

}


#ifdef _TOOLWARE_

//===========================================================================
void CURECEIPT_Print_Ticket_Advance_Demo(void)
{
	DataElement    Elt;
	unsigned short usFound;
	unsigned char  buffer[25];
	TLV_TREE_NODE  hTree;


	// Get data from EMVDC

	// Check if the TOOLWARE TAG is present in the KERNEL and
	// Retreive his value
	hTree = Engine_GetDataElement(TAG_IS_TOOLWARE);

	usFound = CUSERV_Extract_Element_TLV_Tree(&hTree, TAG_IS_TOOLWARE, &Elt);

	if ((! usFound) || ((usFound) && (Elt.ptValue[0] == 0)))
	{
		ct_KernelSupportToolWare = FALSE;
	}
	else
	{
		ct_KernelSupportToolWare = TRUE;
	}

	CUPRINT_Open_Printer();

#ifdef _USE_UCM_
	// If printer haven't been opened
	if (g_pPrinter == NULL)
	{
		// We cannot continue to print something
		return;
	}
#endif

	g_language = PSQ_Give_Language();

	if (ct_KernelSupportToolWare == FALSE)
	{
		CUPRINT_Boundary_Line(0, 24);
		CUPRINT_String_XT(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_ERROR, g_language), ALIGN_LEFT, L4);
		CUPRINT_String_XT(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_KERNEL_NOT_SUPPORT_TOOLWARE, g_language), ALIGN_LEFT, L1);
		CUPRINT_Blanks_Lines(1);

		CUPRINT_String_XT(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_EMV_KERNEL, g_language), ALIGN_LEFT, L4);
		sprintf(buffer, "%ld", ct_KernelVersion);
		CUPRINT_Double_String(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_VERSION, g_language), buffer, L1);
		sprintf(buffer, "%lx", ct_KernelCRC);
		CUPRINT_Double_String(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_CHECKSUM, g_language), buffer, L1);
		CUPRINT_Boundary_Line(0, 24);
	}
	else
	{
		g_TFS = INIT_TFS;

		print_header();

		CUPRINT_Blanks_Lines(2);
		CUPRINT_String_XT(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_ADVANCED_DEMO, g_language), ALIGN_CENTER, L2);
		CUPRINT_Blanks_Lines(2);

		card_features();
		transaction_features();
		transaction_flow_analysis();
		// Just for debug : Print the command list and their timings
		//db_print_commands();
		//db_print_IHM();

		print_tail();
	}

	// Release local TLV tree
	TlvTree_ReleaseEx(&hTree);

	CUPRINT_Paper_Feed();
	CUPRINT_Close_Printer();
}
#endif /* _TOOLWARE_ */


//===========================================================================
void CURECEIPT_Print_EMV_Config(void)
{
	unsigned char  ucValue[256];
	unsigned char  buffer[256];
	int            i;
	int            select_result;
	// Config name
	DataElementExt data;
	int cr;
#ifdef _USE_UCM_
	unsigned char  buffer_imp[256];
#endif

	g_language = PSQ_Give_Language();

	CUPRINT_Open_Printer();


#ifdef _USE_UCM_
	// If printer haven't been opened
	if (g_pPrinter == NULL)
	{
		// We cannot continue to print something
		return;
	}
#endif

#ifdef _USE_UCM_
	// Print the header
	if(UCM_Present)
	{
		sprintf (buffer_imp, "%s\n",CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_EMV_CONFIG_IDENT, g_language));
		pprintf (buffer_imp);
	}
	else
#endif
		CUPRINT_String_XT(CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_EMV_CONFIG_IDENT, g_language), ALIGN_CENTER, L2);
	CUPRINT_Blanks_Lines(1);

	// ICS
	// Reset mark manager
	PAR_ResetMarkList();
	select_result = PAR_SelectMark(C_TAG_ICS0, C_TREE_ALL);

	CUPRINT_Top_Frame(0, 24);
	CUPRINT_String_Frame(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_ICS, g_language), ALIGN_CENTER);

	cr = PAR_ReadParameter(TAG_CUST_IS_CONFIG_FILE, &data);
	if (cr)
		CUPRINT_Double_String_Frame(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_NAME, g_language), data.elt.ptValue );
	// Checksums
	cr = PAR_ReadParameter(TAG_CUST_CRC_CONFIG_FILE, &data);
	if (cr)
		CUPRINT_Double_String_Frame(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_CHECKSUM, g_language), data.elt.ptValue);
	cr = PAR_ReadParameter(TAG_CUST_FULL_CRC_CONFIG_FILE, &data);
	if (cr)
		CUPRINT_Double_String_Frame(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_FULL_CHECKSUM, g_language), data.elt.ptValue);

	// Skip line
	CUPRINT_Double_String_Frame(0, 24, "", "");

	// EMV Kernel Informations
	CUPRINT_String_Frame(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_EMV_KERNEL, g_language), ALIGN_CENTER);

	// Kernel Version
	sprintf(buffer, "%ld", ct_KernelVersion);
	CUPRINT_Double_String_Frame(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_VERSION, g_language), buffer);
	// Kernel CRC
	/*&BEGIN FT/08/4075/MA print of EMVDC CRC*/
	sprintf(buffer, "%04lx", ct_KernelCRC);
	/*&END FT/08/4075/MA print of EMVDC CRC*/
	CUPRINT_Double_String_Frame(0, 24, CUMESS_Read_Message(RECEIPT_TABLE, CU_MESS_CHECKSUM, g_language), buffer);

	CUPRINT_Bottom_Frame(0, 24);


	CUPRINT_Blanks_Lines(1);
	// Print parameters
	i = 0;

	if (select_result == 0) /* if no problem */
		while (table_ics_config[i].i_MsgNumber != (int)NULL)
		{
			unsigned char * pc_l_Msg;

			pc_l_Msg = CUMESS_Read_Message(RECEIPT_TABLE, table_ics_config[i].i_MsgNumber, g_language); /* Table number not used */
			sprintf(buffer, "%s:", pc_l_Msg);

			CUPAR_Get_Param(table_ics_config[i].tag, ucValue);
			CUPRINT_Double_String(buffer, ucValue, L0);
			i ++;
		}

	CUPRINT_Paper_Feed();
	CUPRINT_Close_Printer();
}

//! @}

