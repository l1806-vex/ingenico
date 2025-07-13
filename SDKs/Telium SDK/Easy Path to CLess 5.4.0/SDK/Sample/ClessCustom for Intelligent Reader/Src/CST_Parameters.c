/**
 * \file	CST_Parameters.c
 * \brief	This module contains the functions needed for parameters management.
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
 **/

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "CST_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define MAX_FILE_LG						1024		/*!< max length buf for file. */
#define DISK_NAME_SIZE					33			/*!< Size of disk name. */


//! \brief TagAccess Tag reading access type
#define TAG_READING						1			/*!<  */
#define VALUE_READING					3			/*!<  */


//! \brief Action when a tag is allready found in destination TLVTree
#define C_PARAMS_NO_ACTION				0			/*!<  */
#define C_PARAMS_DELETE					1			/*!<  */


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////



//! \brief Default parameters (XML format)
const char gs_DefaultParam[] =
{
	"	<?xml version=\"1.0\" standalone=\"yes\" ?>"
	"	<!-- Fichier de parametres base kenels contacless -->"
	""
	"	<tlvtree ver=\"1.0\">"
	""
	"	<node tag=\"0xBF91884A\">"
	"		<node tag=\"0x9F91884A\"> 44 65 66 61 75 6C 74 20 50 61 72 61 6d 65 74 65 72 73 </node>		<!-- TAG_SDSA_PARAMETERS_LABEL : Default Parameters -->"
	""
	"		<node tag=\"0xBF918845\">	<!-- TAG_SDSA_AID_PARAMETERS -->"
	""
	"			<node tag=\"0xBF918840\">"
	"				<!-- AID : VISA: Visa Credit or Debit or Easy Entry -->"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 10 10 </node>					<!-- TAG_AID_TERMINAL -->"
	"                                                                                   <!-- Application Program Identifier not specified : default parameters set -->"
	"				<node tag=\"0x9F928101\"> 00 03 </node>								<!-- TAG_EP_KERNEL_TO_USE : VISA -->"
	"				<node tag=\"0x9F928100\"> 05 01 00 00 </node>						<!-- TAG_EP_AID_OPTIONS : TAG_EP_AID_OPTIONS : Partial AID & Zero amount + EP allowed -->"
	"				<node tag=\"0x9F66\"> B6 80 C0 00 </node>							<!-- TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS clss MSD + qVSDC & onlinePIN + sign supported + CVN17 + ISP-->"
	"				<node tag=\"0x9F92810D\"> 00 00 00 01 00 00 </node>					<!-- TAG_EP_CLESS_TRANSACTION_LIMIT : 100 euros -->"
	"				<node tag=\"0x9F92810F\"> 00 00 00 00 15 00 </node>					<!-- TAG_EP_CLESS_FLOOR_LIMIT : 15 euros -->"
	"				<node tag=\"0x9F92810E\"> 00 00 00 00 10 00 </node>					<!-- TAG_EP_CLESS_CVM_REQUIRED_LIMIT: 10 euros -->"
	"				<node tag=\"0x9F1B\"> 00 00 05 AA </node>							<!-- TAG_EMV_TERMINAL_FLOOR_LIMIT : 14,50 euros -->"
	"				<node tag=\"0x9F918705\"> 9F 37 04 </node>							<!-- TAG_EMV_INT_DEFAULT_DDOL (VisaWave specific) -->"
	"			</node>"
	""
	"			<node tag=\"0xBF918840\">"
	"				<!-- AID : VISA: Visa Electron -->"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 20 10 </node>					<!-- TAG_AID_TERMINAL -->"
	"                                                                                   <!-- Application Program Identifier not specified : default parameters set -->"
	"				<node tag=\"0x9F928101\"> 00 03 </node>								<!-- TAG_EP_KERNEL_TO_USE : VISA -->"
	"				<node tag=\"0x9F928100\"> 05 01 00 00 </node>						<!-- TAG_EP_AID_OPTIONS : TAG_EP_AID_OPTIONS : Partial AID & Zero amount + EP allowed -->"
	"				<node tag=\"0x9F66\"> B6 80 C0 00 </node>							<!-- TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS clss MSD + qVSDC & onlinePIN + sign supported + CVN17 + ISP -->"
	"				<node tag=\"0x9F92810D\"> 00 00 00 01 00 00 </node>					<!-- TAG_EP_CLESS_TRANSACTION_LIMIT : 100 euros -->"
	"				<node tag=\"0x9F92810F\"> 00 00 00 00 15 00 </node>					<!-- TAG_EP_CLESS_FLOOR_LIMIT : 15 euros -->"
	"				<node tag=\"0x9F92810E\"> 00 00 00 00 10 00 </node>					<!-- TAG_EP_CLESS_CVM_REQUIRED_LIMIT: 10 euros -->"
	"				<node tag=\"0x9F1B\"> 00 00 05 AA </node>							<!-- TAG_EMV_TERMINAL_FLOOR_LIMIT : 14,50 euros -->"
	"			</node>"
	""
	"			<node tag=\"0xBF918840\">"
	"				<!-- AID : VISA: V PAY -->"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 20 20 </node>					<!-- TAG_AID_TERMINAL -->"
	"                                                                                   <!-- Application Program Identifier not specified : default parameters set -->"
	"				<node tag=\"0x9F928101\"> 00 03 </node>								<!-- TAG_EP_KERNEL_TO_USE : VISA -->"
	"				<node tag=\"0x9F928100\"> 05 03 00 00 </node>						<!-- TAG_EP_AID_OPTIONS : Partial AID & Zero amount -->"
	"				<node tag=\"0x9F92810D\"> 00 00 00 01 00 00 </node>					<!-- TAG_EP_CLESS_TRANSACTION_LIMIT : 100 euros -->"
	"				<node tag=\"0x9F92810F\"> 00 00 00 00 15 00 </node>					<!-- TAG_EP_CLESS_FLOOR_LIMIT -->"
	"				<node tag=\"0x9F92810E\"> 00 00 00 00 10 00 </node>					<!-- TAG_EP_CLESS_CVM_REQUIRED_LIMIT -->"
	"				<node tag=\"0x9F66\"> B6 00 00 00 </node>							<!-- TAG_EP_TERMINAL_TRANSACTION_QUALIFIERS -->"
	"				<node tag=\"0x9F1B\"> 00 00 05 AA </node>							<!-- TAG_EMV_TERMINAL_FLOOR_LIMIT -->"
	""
	"			</node>"
	""
	"			<node tag=\"0xBF918840\">"
	"				<!-- AID : MasterCard PayPass AID for debit -->"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 10 10 </node>					<!-- TAG_AID_TERMINAL : MasterCard PayPass AID -->"
	"				<node tag=\"0x9F928101\"> 00 02 </node>								<!-- TAG_EP_KERNEL_TO_USE : MasterCard -->"
	"				<node tag=\"0x9F928100\"> 05 01 00 00 </node>						<!-- TAG_EP_AID_OPTIONS : Partial AID & Zero amount & PPSE -->"
	"				<node tag=\"0x9F92810D\"> 00 00 00 00 20 00 </node>					<!-- TAG_EP_CLESS_TRANSACTION_LIMIT : 20.00 -->"
	"				<node tag=\"0x9F92810E\"> 00 00 00 00 10 00 </node>					<!-- TAG_EP_CLESS_CVM_REQUIRED_LIMIT : 10.00 -->"
	"				<node tag=\"0x9F92810F\"> 00 00 00 00 15 00 </node>					<!-- TAG_EP_CLESS_FLOOR_LIMIT : 15.00 -->"
	"				<node tag=\"0x9F1B\"> 00 00 05 AA </node>							<!-- TAG_EMV_TERMINAL_FLOOR_LIMIT : 14.50 -->"
	"				<node tag=\"0x9F91850D\"> 01 06 02 01 02 06 </node>					<!-- TAG_PAYPASS_INT_MSTRIPE_TERMINAL_AVN_LIST : 0106, 0201, 0206 -->"
	"				<node tag=\"0x9F918511\"> 01 05 02 00 02 05 </node>					<!-- TAG_PAYPASS_INT_MCHIP_TERMINAL_AVN_LIST : 0105, 0200, 0205 -->"
	"				<node tag=\"0x9F918504\"> E0 68 C8 </node>							<!-- TAG_PAYPASS_TERMINAL_CAPABILITIES_CVM_REQ : E0 68 C8 (Online PIN, Signature and No CVM) -->"
	"				<node tag=\"0x9F918505\"> E0 08 C8 </node>							<!-- TAG_PAYPASS_TERMINAL_CAPABILITIES_NO_CVM_REQ : E0 08 C8 (No CVM only) -->"
	"				<node tag=\"0x9F918502\"> 9F 6A 04 </node>							<!-- TAG_PAYPASS_DEFAULT_UDOL : Value defined in the Paypass 2.0 specification -->"
	"				<node tag=\"0x9F918503\"> 01 </node>								<!-- TAG_PAYPASS_MSTRIPE_INDICATOR : MStripe profile is allowed for this AID -->"
	"				<node tag=\"0x9F918709\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_DEFAULT : 00 00 00 00 00 (no matching bit) -->"
	"				<node tag=\"0x9F91870A\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_DENIAL : 00 00 00 00 00 (no matching bit) -->"
	"				<node tag=\"0x9F91870B\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_ONLINE : 00 00 00 00 00 (no matching bit) -->"
	"				<node tag=\"0x9F53\"> 52 </node>									<!-- TAG_PAYPASS_TRANSACTION_CATEGORY_CODE : 52 -->"
	"				<node tag=\"0x9F918706\"> 9F 08 02 </node>							<!-- TAG_EMV_INT_DEFAULT_TDOL : 9F 08 02 -->"
	"				<node tag=\"0x9F91841D\"> 65 6E 66 72 </node>						<!-- TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES : en, fr -->"
	"			</node>"
	""
	"			<node tag=\"0xBF918840\">"
	"				<!-- AID : Maestro PayPass AID for debit -->"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 30 60 </node>					<!-- TAG_AID_TERMINAL : Maestro PayPass AID -->"
	"				<node tag=\"0x9F928101\"> 00 02 </node>								<!-- TAG_EP_KERNEL_TO_USE : MasterCard -->"
	"				<node tag=\"0x9F928100\"> 05 01 00 00 </node>						<!-- TAG_EP_AID_OPTIONS : Partial AID & Zero amount & PPSE -->"
	"				<node tag=\"0x9F92810D\"> 00 00 00 00 20 00 </node>					<!-- TAG_EP_CLESS_TRANSACTION_LIMIT : 20.00 -->"
	"				<node tag=\"0x9F92810E\"> 00 00 00 00 10 00 </node>					<!-- TAG_EP_CLESS_CVM_REQUIRED_LIMIT : 10.00 -->"
	"				<node tag=\"0x9F92810F\"> 00 00 00 00 15 00 </node>					<!-- TAG_EP_CLESS_FLOOR_LIMIT : 15.00 -->"
	"				<node tag=\"0x9F1B\"> 00 00 05 AA </node>							<!-- TAG_EMV_TERMINAL_FLOOR_LIMIT : 14.50 -->"
	"				<node tag=\"0x9F91850D\"> 01 06 02 01 02 06 </node>					<!-- TAG_PAYPASS_INT_MSTRIPE_TERMINAL_AVN_LIST : 0106, 0201, 0206 -->"
	"				<node tag=\"0x9F918511\"> 01 05 02 00 02 05 </node>					<!-- TAG_PAYPASS_INT_MCHIP_TERMINAL_AVN_LIST : 0105, 0200, 0205 -->"
	"				<node tag=\"0x9F918504\"> E0 68 C8 </node>							<!-- TAG_PAYPASS_TERMINAL_CAPABILITIES_CVM_REQ : E0 68 C8 (Online PIN, Signature and No CVM) -->"
	"				<node tag=\"0x9F918505\"> E0 08 C8 </node>							<!-- TAG_PAYPASS_TERMINAL_CAPABILITIES_NO_CVM_REQ : E0 08 C8 (No CVM only) -->"
	"				<node tag=\"0x9F918502\"> 9F 6A 04 </node>							<!-- TAG_PAYPASS_DEFAULT_UDOL : Value defined in the Paypass 2.0 specification -->"
	"				<node tag=\"0x9F918503\"> 00 </node>								<!-- TAG_PAYPASS_MSTRIPE_INDICATOR : MStripe profile is not allowed for this AID -->"
	"				<node tag=\"0x9F918709\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_DEFAULT : 00 00 00 00 00 (no matching bit) -->"
	"				<node tag=\"0x9F91870A\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_DENIAL : 00 00 00 00 00 (no matching bit) -->"
	"				<node tag=\"0x9F91870B\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_ONLINE : 00 00 00 00 00 (no matching bit) -->"
	"				<node tag=\"0x9F53\"> 52 </node>									<!-- TAG_PAYPASS_TRANSACTION_CATEGORY_CODE : 52 -->"
	"				<node tag=\"0x9F918706\"> 9F 08 02 </node>							<!-- TAG_EMV_INT_DEFAULT_TDOL : 9F 08 02 -->"
	"				<node tag=\"0x9F91841D\"> 65 6E </node>								<!-- TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES : en -->"
	"			</node>"
	""
	"			<node tag=\"0xBF918840\">"
	"				<!-- AID : American Express ExpressPay AID -->"
	"				<node tag=\"0x9F06\"> A0 00 00 00 25 01 </node>						<!-- TAG_AID_TERMINAL : American Express ExpressPay -->"
	"				<node tag=\"0x9F928101\"> 00 04 </node>								<!-- TAG_EP_KERNEL_TO_USE : ExpressPay -->"
	"				<node tag=\"0x9F928100\"> 25 03 00 00 </node>						<!-- TAG_EP_AID_OPTIONS : Partial AID & Zero amount & PPSE -->"
	"				<node tag=\"0x9F92810D\"> 00 00 00 00 20 00 </node>					<!-- TAG_EP_CLESS_TRANSACTION_LIMIT : 20.00 -->"
	"				<node tag=\"0x9F92810E\"> 00 00 00 00 20 00 </node>					<!-- TAG_EP_CLESS_CVM_REQUIRED_LIMIT : 20.00 -->"
	"				<node tag=\"0x9F92810F\"> 00 00 00 00 20 00 </node>					<!-- TAG_EP_CLESS_FLOOR_LIMIT : 20.00 -->"
	"				<node tag=\"0x9F1B\"> 00 00 27 10 </node>							<!-- TAG_EMV_TERMINAL_FLOOR_LIMIT : 100.00 -->"
	"				<node tag=\"0x9F918200\"> 00 3C </node>								<!-- TAG_EXPRESSPAY_UNPREDICTABLE_NUMBER_RANGE : 60 -->"
	"				<node tag=\"0x9F91820A\"> 00 01 </node>								<!-- TAG_EXPRESSPAY_INT_TERMINAL_AVN_LIST : 0001 -->"
	"				<node tag=\"0x9F918709\"> C4 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_DEFAULT -->"
	"				<node tag=\"0x9F91870A\"> C4 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_DENIAL -->"
	"				<node tag=\"0x9F91870B\"> C4 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_ONLINE -->"
	"				<node tag=\"0x9F918706\"> 9F 08 02 </node>							<!-- TAG_EMV_INT_DEFAULT_TDOL -->"
	"				<node tag=\"0x9F91841D\"> 65 6E 66 72 </node>						<!-- TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES : en, fr -->"
	"				<node tag=\"0x9F33\"> E0 68 88 </node>								<!-- TAG_EMV_TERMINAL_CAPABILITIES : E0 68 88 (PIN Online, Signature and No CVM, SDA and CDA) -->"
	"				<node tag=\"0x9F6D\"> C0 </node>									<!-- TAG_EXPRESSPAY_TERMINAL_CAPABILITIES : 00 (ExpressPay 1.0), 40 (ExpressPay 2.0 Magstripe Only), 80 (ExpressPay 2.0 EMV and Magstripe), C0 (ExpressPay Mobile - EMV) -->"
	"				<node tag=\"0x9F6E\"> F8 F0 00 00 </node>							<!-- TAG_EXPRESSPAY_TERMINAL_TRANSACTION_CAPABILITIES : -->"
	"				<node tag=\"0x9F91820F\"> 00 00 27 10 </node> 						<!-- TAG_EXPRESSPAY_FULL_ONLINE_EMV_REMOVAL_TIMEOUT : (4E20=20 sec) (2710=10 sec) (1388=5 sec) -->"
	"				<node tag=\"0x9F918850\"> 00 00 0B B8 </node> 						<!-- TAG_SDSA_EXPRESSPAY_DOUBLE_TAP_TIME : (BB8=3 sec) (7D0=2 sec) (3E8=1 sec) -->"
	"			</node>"
	""
	"		</node> <!-- End node 0xBF918845 : TAG_SDSA_AID_PARAMETERS -->"
	""
	""
	"		<node tag=\"0xBF918846\">	<!-- TAG_SDSA_CAKEYS_PARAMETERS -->"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 50 </node>"
	"				<node tag=\"0x9F918704\"> D1 11 97 59 00 57 B8 41 96 C2 F4 D1 1A 8F 3C 05"
	"										40 8F 42 2A 35 D7 02 F9 01 06 EA 5B 01 9B B2 8A"
	"										E6 07 AA 9C DE BC D0 D8 1A 38 D4 8C 7E BB 00 62"
	"										D2 87 36 9E C0 C4 21 24 24 6A C3 0D 80 CD 60 2A"
	"										B7 23 8D 51 08 4D ED 46 98 16 2C 59 D2 5E AC 1E"
	"										66 25 5B 4D B2 35 25 26 EF 09 82 C3 B8 AD 3D 1C"
	"										CE 85 B0 1D B5 78 8E 75 E0 9F 44 BE 73 61 36 6D"
	"										EF 9D 1E 13 17 B0 5E 5D 0F F5 29 0F 88 A0 DB 47 </node>"
	"				<node tag=\"0x9F918703\"> 01 00 01 </node>"
	"				<node tag=\"0x9F918702\"> B7 69 77 56 68 CA CB 5D 22 A6 47 D1 D9 93 14 1E DA B7 23 7B </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 51 </node>"
	"				<node tag=\"0x9F918704\"> DB 5F A2 9D 1F DA 8C 16 34 B0 4D CC FF 14 8A BE"
	"										E6 3C 77 20 35 C7 98 51 D3 51 21 07 58 6E 02 A9"
	"										17 F7 C7 E8 85 E7 C4 A7 D5 29 71 0A 14 53 34 CE"
	"										67 DC 41 2C B1 59 7B 77 AA 25 43 B9 8D 19 CF 2C"
	"										B8 0C 52 2B DB EA 0F 1B 11 3F A2 C8 62 16 C8 C6"
	"										10 A2 D5 8F 29 CF 33 55 CE B1 BD 3E F4 10 D1 ED"
	"										D1 F7 AE 0F 16 89 79 79 DE 28 C6 EF 29 3E 0A 19"
	"										28 2B D1 D7 93 F1 33 15 23 FC 71 A2 28 80 04 68"
	"										C0 1A 36 53 D1 4C 6B 48 51 A5 C0 29 47 8E 75 7F </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> B9 D2 48 07 5A 3F 23 B5 22 FE 45 57 3E 04 37 4D C4 99 5D 71 </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 53 </node>"
	"				<node tag=\"0x9F918704\"> BC D8 37 21 BE 52 CC CC 4B 64 57 32 1F 22 A7 DC"
	"										76 9F 54 EB 80 25 91 3B E8 04 D9 EA BB FA 19 B3"
	"										D7 C5 D3 CA 65 8D 76 8C AF 57 06 7E EC 83 C7 E6"
	"										E9 F8 1D 05 86 70 3E D9 DD DA DD 20 67 5D 63 42"
	"										49 80 B1 0E B3 64 E8 1E B3 7D B4 0E D1 00 34 4C"
	"										92 88 86 FF 4C CC 37 20 3E E6 10 6D 5B 59 D1 AC"
	"										10 2E 2C D2 D7 AC 17 F4 D9 6C 39 8E 5F D9 93 EC"
	"										B4 FF DF 79 B1 75 47 FF 9F A2 AA 8E EF D6 CB DA"
	"										12 4C BB 17 A0 F8 52 81 46 38 71 35 E2 26 B0 05"
	"										A4 74 B9 06 2F F2 64 D2 FF 8E FA 36 81 4A A2 95"
	"										00 65 B1 B0 4C 0A 1A E9 B2 F6 9D 4A 4A A9 79 D6"
	"										CE 95 FE E9 48 5E D0 A0 3A EE 9B D9 53 E8 1C FD"
	"										1E F6 E8 14 DF D3 C2 CE 37 AE FA 38 C1 F9 87 73"
	"										71 E9 1D 6A 5E B5 9F DE DF 75 D3 32 5F A3 CA 66"
	"										CD FB A0 E5 71 46 CC 78 98 18 FF 06 BE 5F CC 50"
	"										AB D3 62 AE 4B 80 99 6D </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> AC 21 3A 2E 0D 2C 0C A3 5A D0 20 13 23 53 6D 58 09 7E 4E 57 </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 92 </node>"
	"				<node tag=\"0x9F918704\"> 99 6A F5 6F 56 91 87 D0 92 93 C1 48 10 45 0E D8"
	"										EE 33 57 39 7B 18 A2 45 8E FA A9 2D A3 B6 DF 65"
	"										14 EC 06 01 95 31 8F D4 3B E9 B8 F0 CC 66 9E 3F"
	"										84 40 57 CB DD F8 BD A1 91 BB 64 47 3B C8 DC 9A"
	"										73 0D B8 F6 B4 ED E3 92 41 86 FF D9 B8 C7 73 57"
	"										89 C2 3A 36 BA 0B 8A F6 53 72 EB 57 EA 5D 89 E7"
	"										D1 4E 9C 7B 6B 55 74 60 F1 08 85 DA 16 AC 92 3F"
	"										15 AF 37 58 F0 F0 3E BD 3C 5C 2C 94 9C BA 30 6D"
	"										B4 4E 6A 2C 07 6C 5F 67 E2 81 D7 EF 56 78 5D C4"
	"										D7 59 45 E4 91 F0 19 18 80 0A 9E 2D C6 6F 60 08"
	"										05 66 CE 0D AF 8D 17 EA D4 6A D8 E3 0A 24 7C 9F </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> 42 9C 95 4A 38 59 CE F9 12 95 F6 63 C9 63 E5 82 ED 6E B2 53 </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 94 </node>"
	"				<node tag=\"0x9F918704\"> AC D2 B1 23 02 EE 64 4F 3F 83 5A BD 1F C7 A6 F6"
	"										2C CE 48 FF EC 62 2A A8 EF 06 2B EF 6F B8 BA 8B"
	"										C6 8B BF 6A B5 87 0E ED 57 9B C3 97 3E 12 13 03"
	"										D3 48 41 A7 96 D6 DC BC 41 DB F9 E5 2C 46 09 79"
	"										5C 0C CF 7E E8 6F A1 D5 CB 04 10 71 ED 2C 51 D2"
	"										20 2F 63 F1 15 6C 58 A9 2D 38 BC 60 BD F4 24 E1"
	"										77 6E 2B C9 64 80 78 A0 3B 36 FB 55 43 75 FC 53"
	"										D5 7C 73 F5 16 0E A5 9F 3A FC 53 98 EC 7B 67 75"
	"										8D 65 C9 BF F7 82 8B 6B 82 D4 BE 12 4A 41 6A B7"
	"										30 19 14 31 1E A4 62 C1 9F 77 1F 31 B3 B5 73 36"
	"										00 0D FF 73 2D 3B 83 DE 07 05 2D 73 03 54 D2 97"
	"										BE C7 28 71 DC CF 0E 19 3F 17 1A BA 27 EE 46 4C"
	"										6A 97 69 09 43 D5 9B DA BB 2A 27 EB 71 CE EB DA"
	"										FA 11 76 04 64 78 FD 62 FE C4 52 D5 CA 39 32 96"
	"										53 0A A3 F4 19 27 AD FE 43 4A 2D F2 AE 30 54 F8"
	"										84 06 57 A2 6E 0F C6 17 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> C4 A3 C4 3C CF 87 32 7D 13 6B 80 41 60 E4 7D 43 B6 0E 6E 0F </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 95 </node>"
	"				<node tag=\"0x9F918704\"> BE 9E 1F A5 E9 A8 03 85 29 99 C4 AB 43 2D B2 86"
	"										00 DC D9 DA B7 6D FA AA 47 35 5A 0F E3 7B 15 08"
	"										AC 6B F3 88 60 D3 C6 C2 E5 B1 2A 3C AA F2 A7 00"
	"										5A 72 41 EB AA 77 71 11 2C 74 CF 9A 06 34 65 2F"
	"										BC A0 E5 98 0C 54 A6 47 61 EA 10 1A 11 4E 0F 0B"
	"										55 72 AD D5 7D 01 0B 7C 9C 88 7E 10 4C A4 EE 12"
	"										72 DA 66 D9 97 B9 A9 0B 5A 6D 62 4A B6 C5 7E 73"
	"										C8 F9 19 00 0E B5 F6 84 89 8E F8 C3 DB EF B3 30"
	"										C6 26 60 BE D8 8E A7 8E 90 9A FF 05 F6 DA 62 7B </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> EE 15 11 CE C7 10 20 A9 B9 04 43 B3 7B 1D 5F 6E 70 30 30 F6 </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 96 </node>"
	"				<node tag=\"0x9F918704\"> B7 45 86 D1 9A 20 7B E6 62 7C 5B 0A AF BC 44 A2"
	"										EC F5 A2 94 2D 3A 26 CE 19 C4 FF AE EE 92 05 21"
	"										86 89 22 E8 93 E7 83 82 25 A3 94 7A 26 14 79 6F"
	"										B2 C0 62 8C E8 C1 1E 38 25 A5 6D 3B 1B BA EF 78"
	"										3A 5C 6A 81 F3 6F 86 25 39 51 26 FA 98 3C 52 16"
	"										D3 16 6D 48 AC DE 8A 43 12 12 FF 76 3A 7F 79 D9"
	"										ED B7 FE D7 6B 48 5D E4 5B EB 82 9A 3D 47 30 84"
	"										8A 36 6D 33 24 C3 02 70 32 FF 8D 16 A1 E4 4D 8D </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> 76 16 E9 AC 8B E0 14 AF 88 CA 11 A8 FB 17 96 7B 73 94 03 0E </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 97 </node>"
	"				<node tag=\"0x9F918704\"> AF 07 54 EA ED 97 70 43 AB 6F 41 D6 31 2A B1 E2"
	"										2A 68 09 17 5B EB 28 E7 0D 5F 99 B2 DF 18 CA E7"
	"										35 19 34 1B BB D3 27 D0 B8 BE 9D 4D 0E 15 F0 7D"
	"										36 EA 3E 3A 05 C8 92 F5 B1 9A 3E 9D 34 13 B0 D9"
	"										7E 7A D1 0A 5F 5D E8 E3 88 60 C0 AD 00 4B 1E 06"
	"										F4 04 0C 29 5A CB 45 7A 78 85 51 B6 12 7C 0B 29 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> 80 01 CA 76 C1 20 39 55 E2 C6 28 41 CD 6F 20 10 87 E5 64 BF </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 98 </node>"
	"				<node tag=\"0x9F918704\"> CA 02 6E 52 A6 95 E7 2B D3 0A F9 28 19 6E ED C9"
	"										FA F4 A6 19 F2 49 2E 3F B3 11 69 78 9C 27 6F FB"
	"										B7 D4 31 16 64 7B A9 E0 D1 06 A3 54 2E 39 65 29"
	"										2C F7 78 23 DD 34 CA 8E EC 7D E3 67 E0 80 70 89"
	"										50 77 C7 EF AD 93 99 24 CB 18 70 67 DB F9 2C B1"
	"										E7 85 91 7B D3 8B AC E0 C1 94 CA 12 DF 0C E5 B7"
	"										A5 02 75 AC 61 BE 7C 3B 43 68 87 CA 98 C9 FD 39 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> E7 AC 9A A8 EE D1 B5 FF 1B D5 32 CF 14 89 A3 E5 55 75 72 C1 </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 03 </node>"
	"				<node tag=\"0x9F22\"> 99 </node>"
	"				<node tag=\"0x9F918704\"> AB 79 FC C9 52 08 96 96 7E 77 6E 64 44 4E 5D CD"
	"										D6 E1 36 11 87 4F 39 85 72 25 20 42 52 95 EE A4"
	"										BD 0C 27 81 DE 7F 31 CD 3D 04 1F 56 5F 74 73 06"
	"										EE D6 29 54 B1 7E DA BA 3A 6C 5B 85 A1 DE 1B EB"
	"										9A 34 14 1A F3 8F CF 82 79 C9 DE A0 D5 A6 71 0D"
	"										08 DB 41 24 F0 41 94 55 87 E2 03 59 BA B4 7B 75"
	"										75 AD 94 26 2D 4B 25 F2 64 AF 33 DE DC F2 8E 09"
	"										61 5E 93 7D E3 2E DC 03 C5 44 45 FE 7E 38 27 77 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> 4A BF FD 6B 1C 51 21 2D 05 55 2E 43 1C 5B 17 00 7D 2F 5E 6D </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F0 </node>"
	"				<node tag=\"0x9F918704\"> 75 63 C5 1B 52 76 AA 63 70 AB 84 05 52 24 14 64"
	"										58 32 B6 BE F2 A9 89 C7 71 47 5B 2E 8D C6 54 DC"
	"										8A 5B FF 9E 28 E3 1F F1 A3 70 A4 0D C3 FF EB 06"
	"										BC 85 48 7D 5F 1C B6 1C 24 41 FD 71 CB CD 05 D8"
	"										83 F8 DE 41 3B 24 3A FC 9D CA 76 8B 06 1E 35 B8"
	"										84 B5 D2 1B 6B 01 6A A3 6B A1 2D AB CF E4 9F 8E"
	"										52 8C 89 3C 34 C7 D4 79 39 77 E4 CC 99 AB 09 64"
	"										0D 9C 7A AB 7E C5 FF 3F 40 E3 D4 D1 8D F7 E3 A7 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> AE 66 74 45 F8 DE 6F 82 C3 88 00 E5 EB AB A3 22 F0 3F 58 F2 </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F3 </node>"
	"				<node tag=\"0x9F918704\"> 98 F0 C7 70 F2 38 64 C2 E7 66 DF 02 D1 E8 33 DF"
	"										F4 FF E9 2D 69 6E 16 42 F0 A8 8C 56 94 C6 47 9D"
	"										16 DB 15 37 BF E2 9E 4F DC 6E 6E 8A FD 1B 0E B7"
	"										EA 01 24 72 3C 33 31 79 BF 19 E9 3F 10 65 8B 2F"
	"										77 6E 82 9E 87 DA ED A9 C9 4A 8B 33 82 19 9A 35"
	"										0C 07 79 77 C9 7A FF 08 FD 11 31 0A C9 50 A7 2C"
	"										3C A5 00 2E F5 13 FC CC 28 6E 64 6E 3C 53 87 53"
	"										5D 50 95 14 B3 B3 26 E1 23 4F 9C B4 8C 36 DD D4"
	"										4B 41 6D 23 65 40 34 A6 6F 40 3B A5 11 C5 EF A3 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> A6 9A C7 60 3D AF 56 6E 97 2D ED C2 CB 43 3E 07 E8 B0 1A 9A </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F5 </node>"
	"				<node tag=\"0x9F918704\"> A6 E6 FB 72 17 95 06 F8 60 CC CA 8C 27 F9 9C EC"
	"										D9 4C 7D 4F 31 91 D3 03 BB EE 37 48 1C 7A A1 5F"
	"										23 3B A7 55 E9 E4 37 63 45 A9 A6 7E 79 94 BD C1"
	"										C6 80 BB 35 22 D8 C9 3E B0 CC C9 1A D3 1A D4 50"
	"										DA 30 D3 37 66 2D 19 AC 03 E2 B4 EF 5F 6E C1 82"
	"										82 D4 91 E1 97 67 D7 B2 45 42 DF DE FF 6F 62 18"
	"										55 03 53 20 69 BB B3 69 E3 BB 9F B1 9A C6 F1 C3"
	"										0B 97 D2 49 EE E7 64 E0 BA C9 7F 25 C8 73 D9 73"
	"										95 3E 51 53 A4 20 64 BB FA BF D0 6A 4B B4 86 86"
	"										0B F6 63 74 06 C9 FC 36 81 3A 4A 75 F7 5C 31 CC"
	"										A9 F6 9F 8D E5 9A DE CE F6 BD E7 E0 78 00 FC BE"
	"										03 5D 31 76 AF 84 73 E2 3E 9A A3 DF EE 22 11 96"
	"										D1 14 83 02 67 7C 72 0C FE 25 44 A0 3D B5 53 E7"
	"										F1 B8 42 7B A1 CC 72 B0 F2 9B 12 DF EF 4C 08 1D"
	"										07 6D 35 3E 71 88 0A AD FF 38 63 52 AF 0A B7 B2"
	"										8E D4 9E 1E 67 2D 11 F9 </node>"
	"				<node tag=\"0x9F918703\"> 01 00 01 </node>"
	"				<node tag=\"0x9F918702\"> C2 23 98 04 C8 09 81 70 BE 52 D6 D5 D4 15 9E 81 CE 84 66 BF </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F6 </node>"
	"				<node tag=\"0x9F918704\"> A2 5A 6B D7 83 A5 EF 6B 8F B6 F8 30 55 C2 60 F5"
	"										F9 9E A1 66 78 F3 B9 05 3E 0F 64 98 E8 2C 3F 5D"
	"										1E 8C 38 F1 35 88 01 7E 2B 12 B3 D8 FF 6F 50 16"
	"										7F 46 44 29 10 72 9E 9E 4D 1B 37 39 E5 06 7C 0A"
	"										C7 A1 F4 48 7E 35 F6 75 BC 16 E2 33 31 51 65 CB"
	"										14 2B FD B2 5E 30 1A 63 2A 54 A3 37 1E BA B6 57"
	"										2D EE BA F3 70 F3 37 F0 57 EE 73 B4 AE 46 D1 A8"
	"										BC 4D A8 53 EC 3C C1 2C 8C BC 2D A1 83 22 D6 85"
	"										30 C7 0B 22 BD AC 35 1D D3 60 68 AE 32 1E 11 AB"
	"										F2 64 F4 D3 56 9B B7 12 14 54 50 05 55 8D E2 60"
	"										83 C7 35 DB 77 63 68 17 2F E8 C2 F5 C8 5E 8B 5B"
	"										89 0C C6 82 91 1D 2D E7 1F A6 26 B8 81 7F CC C0"
	"										89 22 B7 03 86 9F 3B AE AC 14 59 D7 7C D8 53 76"
	"										BC 36 18 2F 42 38 31 4D 6C 42 12 FB DD 7F 23 D3 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> 50 29 09 ED 54 5E 3C 8D BD 00 EA 58 2D 06 17 FE E9 F6 F6 84 </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F7 </node>"
	"				<node tag=\"0x9F918704\"> 94 EA 62 F6 D5 83 20 E3 54 C0 22 AD DC F0 55 9D"
	"										8C F2 06 CD 92 E8 69 56 49 05 CE 21 D7 20 F9 71"
	"										B7 AE A3 74 83 0E BE 17 57 11 5A 85 E0 88 D4 1C"
	"										6B 77 CF 5E C8 21 F3 0B 1D 89 04 17 BF 2F A3 1E"
	"										59 08 DE D5 FA 67 7F 8C 7B 18 4A D0 90 28 FD DE"
	"										96 B6 A6 10 98 50 AA 80 01 75 EA BC DB BB 68 4A"
	"										96 C2 EB 63 79 DF EA 08 D3 2F E2 33 1F E1 03 23"
	"										3A D5 8D CD B1 E6 E0 77 CB 9F 24 EA EC 5C 25 AF </node>"
	"				<node tag=\"0x9F918703\"> 01 00 01 </node>"
	"				<node tag=\"0x9F918702\"> EE B0 DD 9B 24 77 BE E3 20 9A 91 4C DB A9 4C 1C 4A 9B DE D9 </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F8 </node>"
	"				<node tag=\"0x9F918704\"> A1 F5 E1 C9 BD 86 50 BD 43 AB 6E E5 6B 89 1E F7"
	"										45 9C 0A 24 FA 84 F9 12 7D 1A 6C 79 D4 93 0F 6D"
	"										B1 85 2E 25 10 F1 8B 61 CD 35 4D B8 3A 35 6B D1"
	"										90 B8 8A B8 DF 04 28 4D 02 A4 20 4A 7B 6C B7 C5"
	"										55 19 77 A9 B3 63 79 CA 3D E1 A0 8E 69 F3 01 C9"
	"										5C C1 C2 05 06 95 92 75 F4 17 23 DD 5D 29 25 29"
	"										05 79 E5 A9 5B 0D F6 32 3F C8 E9 27 3D 6F 84 91"
	"										98 C4 99 62 09 16 6D 9B FC 97 3C 36 1C C8 26 E1 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> F0 6E CC 6D 2A AE BF 25 9B 7E 75 5A 38 D9 A9 B2 4E 2F F3 DD </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> F9 </node>"
	"				<node tag=\"0x9F918704\"> A9 9A 6D 3E 07 18 89 ED 9E 3A 0C 39 1C 69 B0 B8"
	"										04 FC 16 0B 2B 4B DD 57 0C 92 DD 5A 0F 45 F5 3E"
	"										86 21 F7 C9 6C 40 22 42 66 73 5E 1E E1 B3 C0 62"
	"										38 AE 35 04 63 20 FD 8E 81 F8 CE B3 F8 B4 C9 7B"
	"										94 09 30 A3 AC 5E 79 00 86 DA D4 1A 6A 4F 51 17"
	"										BA 1C E2 43 8A 51 AC 05 3E B0 02 AE D8 66 D2 C4"
	"										58 FD 73 35 90 21 A1 20 29 A0 C0 43 04 5C 11 66"
	"										4F E0 21 9E C6 3C 10 BF 21 55 BB 27 84 60 9A 10"
	"										64 21 D4 51 63 79 97 38 C1 C3 09 09 BB 6C 6F E5"
	"										2B BB 76 39 7B 97 40 CE 06 4A 61 3F F8 41 11 85"
	"										F0 88 42 A4 23 EA D2 0E DF FB FF 1C D6 C3 FE 0C"
	"										98 21 47 91 99 C2 6D 85 72 CC 8A FF F0 87 A9 C3 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> 33 67 12 DC C2 85 54 80 9C 6A A9 B0 23 58 DE 6F 75 51 64 DB </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> FA </node>"
	"				<node tag=\"0x9F918704\"> 9C 6B E5 AD B1 0B 4B E3 DC E2 09 9B 4B 21 06 72"
	"										B8 96 56 EB A0 91 20 4F 61 3E CC 62 3B ED C9 C6"
	"										D7 7B 66 0E 8B AE EA 7F 7C E3 0F 1B 15 38 79 A4"
	"										E3 64 59 34 3D 1F E4 7A CD BD 41 FC D7 10 03 0C"
	"										2B A1 D9 46 15 97 98 2C 6E 1B DD 08 55 4B 72 6F"
	"										5E FF 79 13 CE 59 E7 9E 35 72 95 C3 21 E2 6D 0B"
	"										8B E2 70 A9 44 23 45 C7 53 E2 AA 2A CF C9 D3 08"
	"										50 60 2F E6 CA C0 0C 6D DF 6B 8D 9D 9B 48 79 B2"
	"										82 6B 04 2A 07 F0 E5 AE 52 6A 3D 3C 4D 22 C7 2B"
	"										9E AA 52 EE D8 89 38 66 F8 66 38 7A C0 5A 13 99 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> 0A BC AD AD 2C 75 58 CA 9C 70 81 AE 55 DD DC 71 4F 8D 45 F8 </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 </node>"
	"				<node tag=\"0x9F22\"> FE </node>"
	"				<node tag=\"0x9F918704\"> A6 53 EA C1 C0 F7 86 C8 72 4F 73 7F 17 29 97 D6"
	"										3D 1C 32 51 C4 44 02 04 9B 86 5B AE 87 7D 0F 39"
	"										8C BF BE 8A 60 35 E2 4A FA 08 6B EF DE 93 51 E5"
	"										4B 95 70 8E E6 72 F0 96 8B CD 50 DC E4 0F 78 33"
	"										22 B2 AB A0 4E F1 37 EF 18 AB F0 3C 7D BC 58 13"
	"										AE AE F3 AA 77 97 BA 15 DF 7D 5B A1 CB AF 7F D5"
	"										20 B5 A4 82 D8 D3 FE E1 05 07 78 71 11 3E 23 A4"
	"										9A F3 92 65 54 A7 0F E1 0E D7 28 CF 79 3B 62 A1 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> 9A 29 5B 05 FB 39 0E F7 92 3F 57 61 8A 9F DA 29 41 FC 34 E0 </node>"
	"			</node>"
	""
	"			<node tag=\"0xBF918841\">"
	"				<node tag=\"0x9F06\"> A0 00 00 00 25 </node>"
	"				<node tag=\"0x9F22\"> 97 </node>"
	"				<node tag=\"0x9F918704\"> E1 78 FF E8 34 B4 B7 67 AF 3C 9A 51 1F 97 3D 8E"
	"										85 05 C5 FC B2 D3 76 80 75 AB 7C C9 46 A9 55 78"
	"										99 55 87 9A AF 73 74 07 15 15 21 99 6D FA 43 C5"
	"										8E 6B 13 0E B1 D8 63 B8 5D C9 FF B4 05 09 47 A2"
	"										67 6A A6 A0 61 A4 A7 AE 1E DB 0E 36 A6 97 E8 7E"
	"										03 75 17 EB 89 23 13 68 75 BA 2C A1 08 7C BA 7E"
	"										C7 65 3E 5E 28 A0 C2 61 A0 33 AF 27 E3 A6 7B 64"
	"										BB A2 69 56 30 7E C4 7E 67 4E 3F 8B 72 2B 3A E0"
	"										49 8D B1 6C 79 85 31 0D 9F 3D 11 73 00 D3 2B 09 </node>"
	"				<node tag=\"0x9F918703\"> 03 </node>"
	"				<node tag=\"0x9F918702\"> EB DA 52 2B 63 1B 3E B4 F4 CB FC 06 79 C4 50 13 9D 2B 69 CD </node>"
	"			</node>"
	""
	"		</node> <!-- End node 0xBF918846 : TAG_SDSA_CAKEYS_PARAMETERS-->"
	""
	""
	"		<node tag=\"0xBF918847\">	<!-- TAG_SDSA_CAREVOK_PARAMETERS -->"
	"		</node> <!-- End node 0xBF918847 : TAG_SDSA_CAREVOK_PARAMETERS -->"
	""
	""
	"		<node tag=\"0xBF918848\">	<!-- TAG_SDSA_ICS_PARAMETERS -->"
	""
	"			<node tag=\"0xBF918842\">"
	"				<!-- ICS0 values -->"
	"				<node tag=\"0x9F928210\"> 03 00 00 00 </node>				<!-- TAG_GENERIC_DETECTION_TYPE -->"
	"				<node tag=\"0x9F928212\"> 00 00 17 70 </node>				<!-- TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT : 6000 -->"
	"				<node tag=\"0x9F928214\"> 01 </node>						<!-- TAG_GENERIC_DETECTION_NB_CARDS_TO_DETECT -->"
	"				<node tag=\"0x9F91884D\"> 03 A9 80 </node>					<!-- TAG_SDSA_NO_CARD_TIMEOUT : 4 minutes (240000ms = 3A980) -->"
	""
	"			<!-- Application Independent Data -->"
	"				<node tag=\"0x9F1A\"> 00 56 </node>							<!-- TAG_EMV_TERMINAL_COUNTRY_CODE -->"
	"				<node tag=\"0x9F40\"> 60 00 F0 B0 01 </node>				<!-- TAG_EMV_ADD_TERMINAL_CAPABILITIES -->"
	"				<node tag=\"0x9F35\"> 22 </node>							<!-- TAG_EMV_TERMINAL_TYPE -->"
	""
	"				<!-- Application Dependent Data -->"
	"				<node tag=\"0x9F01\"> 01 23 45 67 89 01 </node>				<!-- TAG_EMV_ACQUIRER_IDENTIFIER -->"
	"				<node tag=\"0x9F15\"> 00 00 </node>							<!-- TAG_EMV_MERCHANT_CATEGORY_CODE -->"
	"				<node tag=\"0x9F16\"> 31 31 32 32 33 33 34 34 35 35 36 36 37 37 38 </node>	<!-- TAG_EMV_MERCHANT_IDENTIFIER -->"
	"				<node tag=\"0x9F1C\"> 31 32 33 34 35 36 37 38 </node> 		<!-- TAG_EMV_TERMINAL_IDENTIFICATION -->"
	""
	"			</node> <!-- End node 0xBF918842 -->"
	"		</node> <!-- End node 0xBF918803 : TAG_SDSA_ICS_PARAMETERS-->"
	""
	""
	""
	"		<node tag=\"0xBF918849\">	<!-- TAG_SDSA_SPECIFIC_PARAMETERS -->"
	""
	"			<!-- JCB Specific parameters -->"
	"			<node tag=\"0xBF918843\">"
	"				<node tag=\"0x9F928101\"> 00 01 </node>				<!-- TAG_EP_KERNEL_TO_USE : JCB -->"
	"			</node> <!-- End node -->"
	""
	"			<!-- PAYPASS Specific parameters -->"
	"			<node tag=\"0xBF918843\">"
	"				<node tag=\"0x9F928101\"> 00 02 </node>				<!-- TAG_EP_KERNEL_TO_USE : PAYPASS -->"
	"			</node> <!-- End node -->"
	""
	"			<!-- VISA Specific parameters -->"
	"			<node tag=\"0xBF918843\">"
	"				<node tag=\"0x9F928101\"> 00 03 </node>				<!-- TAG_EP_KERNEL_TO_USE : VISA -->"
	""
	"				<!-- Supported fDDA versions = 00 01 -->"
	"				<node tag=\"0x9f918307\"> 00 01 </node>				<!-- TAG_PAYWAVE_TERM_SUPPORTED_FDDA_VERSIONS -->"
	"				<node tag=\"0x9F33\"> E0 28 C8 </node>				<!-- TAG_EMV_TERMINAL_CAPABILITIES -->"
	""
	"				<!-- VisaWave specific tags -->"
	"				<node tag=\"0x9F918803\"> 00 00 4E 20 </node> 		<!-- TAG_SAMPLE_DOUBLE_DIP_TIMEOUT : (7530=30 sec) (4E20=20 sec) (2710=10 sec)-->"
	"				<node tag=\"0x9F918804\"> 00 00 3A 98 </node> 		<!-- TAG_SAMPLE_NO_CARD_TIMEOUT : (4E20=20 sec) (3A98=15 sec) (2710=10 sec)-->"
	"			</node> <!-- End node -->"
	""
	"			<!-- ExpressPay Specific parameters -->"
	"			<node tag=\"0xBF918843\">"
	"				<node tag=\"0x9F928101\"> 00 04 </node>				<!-- TAG_EP_KERNEL_TO_USE : American Express ExpressPay -->"
	"			</node> <!-- End node -->"
	""
	"			<!-- EMVCO Specific parameters -->"
	"			<node tag=\"0xBF918843\">"
	"				<node tag=\"0x9F928101\"> 01 01 </node>				<!-- TAG_EP_KERNEL_TO_USE : EMVCO -->"
	"			</node> <!-- End node -->"
	""
	"			<node tag=\"0x9F91884B\" format=\"ascii\"> \"EUR9782,.1\" </node>		<!-- TAG_SDSA_GENERIC_MONEY_EXTENDED EUR9782,.1 -->"
	"			<node tag=\"0x9F91884B\" format=\"ascii\"> \"MYR4582,.1\" </node>		<!-- TAG_SDSA_GENERIC_MONEY_EXTENDED MYR4582,.1 -->"
	"			<node tag=\"0x9F91884B\" format=\"ascii\"> \"CAD1242,.1\" </node>		<!-- TAG_SDSA_GENERIC_MONEY_EXTENDED CAD1242,.1 -->"
	"			<node tag=\"0x9F91884B\" format=\"ascii\"> \"USD8402,.1\" </node>		<!-- TAG_SDSA_GENERIC_MONEY_EXTENDED USD8402,.1 -->"
	"		</node> <!-- End node 0xBF918849 : TAG_SDSA_SPECIFIC_PARAMETERS-->"
	""
	"	</node>	 <!-- End node TAG_SDSA_PARAMETER_FILE_NODE -->"
	"</tlvtree>"
};


//! \brief Global TLV Tree used for parameters management.
TLV_TREE_NODE pTreeCurrentParam = NULL;							/*!< Node from param file parameters. */
TLV_TREE_NODE pTreeDefaultParam = NULL;							/*!< Node from default parameters. */

static unsigned char gs_ucTerminalSha[32];
static unsigned long gs_ulTerminalShaLength;

static char gs_Label_Disk_Name[DISK_NAME_SIZE];					/*!< To store the disk name. */

static int nNbMoneyExtended = 0;
static S_MONEY_EXTENDED * ptr_money_extended = NULL;


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static void __CST_Parameters_Get_Disk_Name(char* ptDiskName);
static int __CST_Parameters_FileRead(TLV_TREE_NODE * pTree, char *pc_x_DirFile, char *pc_x_fileName);
static int __CST_Parameters_ShaFileRead(unsigned char *pucSha, int nSize, unsigned long *pucShaLength, char *pc_x_DirFile, char *pc_x_fileName);
static int __CST_Parameters_WriteBinFile(TLV_TREE_NODE pTree, char * ptr_OutBuf, unsigned char *pucSha, int nShaLength, char * ptr_ShaBuf);
static int __CST_Parameters_ReadParamFile(TLV_TREE_NODE * p_node, char *pc_x_DirFile, unsigned int i_x_ParamFileType);
static int __CST_Parameters_CreateDisk (void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief This function reads an array (XML format) and extract tags and value to build a TLVTree. 
//! \param[in] ptr_ac_x_ParamTable array with parameters with XML format.
//! \param[in] i_x_ArraySize array number of elements.
//! \param[out] pBool : boolean to set.
//! \return TLVTree updated with parameters.

static TLV_TREE_NODE __CST_Parameters_ReadArray(char *ptr_ac_x_ParamTable, int i_x_ArraySize)
{
	TLV_TREE_NODE  pTree = 0;
	int s;

	s = TlvTree_Unserialize(&pTree, TLV_TREE_SERIALIZER_XML, (unsigned char*)ptr_ac_x_ParamTable, i_x_ArraySize );

	if (s != 0)
	{
		GTL_Traces_TraceDebug ("__CST_Parameters_ReadArray : PB on xml parameters !!!");
		// Reset of this node, a problem occur
		pTree = 0;
	}

	return (pTree);
}



//! \brief This function reads a file of parameters (XML format) and extract tags and value to build a TLVTree. 
//! \param[in] pTree to go throw to found tag informations.
//! \param[in] pc_x_DirFile file path of xml text file to read.
//! \param[in] pc_x_fileName file name of xml text file to read.
//! \return
//! - 0 if file read ok, 1 else.

static int __CST_Parameters_FileRead(TLV_TREE_NODE * pTree, char *pc_x_DirFile, char *pc_x_fileName)
{
	char ac_l_OutBuf[80];
	char LabelDiskName[DISK_NAME_SIZE];
	int nResult = 0;

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__CST_Parameters_Get_Disk_Name(LabelDiskName);

	sprintf(ac_l_OutBuf, "/%s/%s", LabelDiskName, C_FILE_PARAM_SAV);

	if ((strncmp(pc_x_fileName, C_FILE_NAME_XML, sizeof(C_FILE_NAME_XML)-1) == 0)	||
		(strncmp(pc_x_fileName, C_FILE_PARAM_SAV, sizeof(C_FILE_PARAM_SAV)-1) == 0) )
	{
		unsigned int FileTypeAccess = TLV_TREE_SERIALIZER_DEFAULT;

		if (strncmp(pc_x_fileName, C_FILE_NAME_XML, sizeof(C_FILE_NAME_XML)-1) == 0)
		{
			// XML format used to load parameter
			FileTypeAccess = TLV_TREE_SERIALIZER_XML;
		}

		if (__CST_Parameters_ReadParamFile(pTree, pc_x_DirFile, FileTypeAccess) != 0)
		{
			GTL_Traces_TraceDebug ("__CST_Parameters_ReadParamFile() error");
			nResult = 1;
		}
	}
	return (nResult);
}



//! \brief This function reads a file that contains the sha calculated on the saved parameters. 
//! \param[in] pucSha sha to get.
//! \param[in] nSize size of the pucSha buffer.
//! \param[in] pucShaLength length of the sha.
//! \param[in] pc_x_DirFile file path of text file to read.
//! \param[in] pc_x_fileName file name of text file to read.
//! \return
//! - 0 if file read ok, 1 else.

static int __CST_Parameters_ShaFileRead(unsigned char *pucSha, int nSize, unsigned long *pucShaLength, char *pc_x_DirFile, char *pc_x_fileName)
{
	char ac_l_OutBuf[80];
	char LabelDiskName[DISK_NAME_SIZE];
	int nResult = 0;

	unsigned int Mode, rc;
	S_FS_FILE * ptr_file;
	unsigned char * ac_l_pucBuffer = NULL;
	unsigned long ulFileLength;

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__CST_Parameters_Get_Disk_Name(LabelDiskName);

	sprintf(ac_l_OutBuf, "/%s/%s", LabelDiskName, C_FILE_SHAPARAM_SAV);

	if (strncmp(pc_x_fileName, C_FILE_SHAPARAM_SAV, sizeof(C_FILE_SHAPARAM_SAV)-1) == 0 )
	{
		// Read data from parameters file
		Mode = FS_READMOD;
		rc= FS_mount (pc_x_DirFile,&Mode);
		if (rc != FS_OK)
		{
			GTL_Traces_TraceDebug ("__CST_Parameters_ShaFileRead : FS_mount error");
		}

		ptr_file = FS_open(pc_x_DirFile, "r");

		if (ptr_file != NULL)
		{
			ulFileLength = FS_length (ptr_file);

			GTL_Traces_TraceDebug ("__CST_Parameters_ShaFileRead : file length %lx", ulFileLength);
				
			if (ulFileLength > C_PUC_MAX_SHABUFFER_SIZE) // If file size greater than max size
			{
				GTL_Traces_TraceDebug ("__CST_Parameters_ShaFileRead : Parameter file size too important !!!");
				nResult = 1;
			}
			else
			{
				ac_l_pucBuffer = (unsigned char *) umalloc(ulFileLength+10);
				FS_read (ac_l_pucBuffer, 1, ulFileLength+10, ptr_file);
				if(ulFileLength <= (unsigned int) nSize)
				{
					// Copy the sha value and the sha length
					memcpy(pucSha, ac_l_pucBuffer, ulFileLength);
					*pucShaLength = ulFileLength;
					GTL_Traces_TraceDebug ("__CST_Parameters_ShaFileRead : strlen %lx buf %s", *pucShaLength, pucSha);
				}
				else
					nResult = 1;
				ufree(ac_l_pucBuffer);
			}
			FS_close(ptr_file);
		}
		else // Pb on FS_open()
		{
			nResult = 1;
		}
	}
	return (nResult);
}



//! \brief This function update a file with parameters given in a TLVTree.
//! File is updated in TLVTree serial binary format.
//! \param[in] pTree to go save in file.
//! \param[in] ptr_OutBuf file path and name to update. File that contains the parameters.
//! \param[in] pucSha Sha to save (calculated with given parameters).
//! \param[in] nShaLength Length of the sha.
//! \param[in] ptr_ShaBuf file path and name to update. File that contains the Sha.
//! \return
//! - 0 if ok, 1 else.

static int __CST_Parameters_WriteBinFile(TLV_TREE_NODE pTree, char * ptr_OutBuf, unsigned char *pucSha, int nShaLength, char *ptr_ShaBuf)
{
	unsigned char * ac_l_pucBuffer = NULL;
	unsigned int  result = 0;
	int           i_l_Size = 0;
	S_FS_FILE     *ptr_file, *ptr_Shafile;

	// If the TlvTree that contains the parameters to save is null, suppress the saved file
	if(pTree == 0)
		goto SuppressFile;

	// Input parameters checking
	if ((strlen(ptr_OutBuf) == 0) || (strlen(ptr_ShaBuf) == 0))
	{
		return 1;
	}

	// Check size
	i_l_Size = TlvTree_GetSerializationSize(pTree, TLV_TREE_SERIALIZER_DEFAULT);

	if (i_l_Size>C_PUC_MAX_BUFFER_SIZE) // If file size greater than max size
	{
		GTL_Traces_TraceDebug ("__CST_Parameters_WriteBinFile : Parameter node size too important");
		result = 1;
	}
	else
	{
		ac_l_pucBuffer = (unsigned char *) umalloc(i_l_Size + 10);
		i_l_Size = TlvTree_Serialize( pTree, TLV_TREE_SERIALIZER_DEFAULT, ac_l_pucBuffer, i_l_Size + 10);

		// The buffer is saved in a file
		if ((i_l_Size < 0) || (i_l_Size > C_PUC_MAX_BUFFER_SIZE)) // If serialization pb
		{
			GTL_Traces_TraceDebug ("__CST_Parameters_WriteBinFile : Parameter node serialisation pb");
			result = 1;
		}
	}

SuppressFile:
	if (result == 0)	// If ok
	{
		unsigned int Mode,rc;
		int ret,ret2;

		ret = __CST_Parameters_CreateDisk();
		if (ret == FS_OK)
		{
			ret = FS_exist (ptr_OutBuf);
			ret2 = FS_exist (ptr_ShaBuf);

			if ((ret == FS_OK) || (ret2 == FS_OK))
			{
				if(ret == FS_OK)
				{
					// The former file is suppressed. 
					GTL_Traces_TraceDebug ("__CST_Parameters_WriteBinFile : %s FILE EXIST", ptr_OutBuf);
					FS_unlink (ptr_OutBuf);
				}
				if(ret2 == FS_OK)
				{
					// The former file is suppressed. 
					GTL_Traces_TraceDebug ("__CST_Parameters_WriteBinFile : %s FILE EXIST", ptr_ShaBuf);
					FS_unlink (ptr_ShaBuf);
				}
				
				// File is suppressed, terminate
				if(pTree == 0)
					return(result);
			}
			else
			{
				// File does not exist, terminate
				if(pTree == 0)
					return(result);
			}
		}

		Mode = FS_WRTMOD;
		rc = FS_mount(ptr_OutBuf, &Mode);
		if (rc != FS_OK)
		{
			GTL_Traces_TraceDebug ("__CST_Parameters_WriteBinFile : FS_mount param file error");
			result = 1;
		} 

		ptr_file = FS_open (ptr_OutBuf, "a");
		if (ptr_file == NULL)
		{
			result = 1;
			GTL_Traces_TraceDebug ("__CST_Parameters_WriteBinFile : Error create param file");
		}

		rc = FS_mount(ptr_ShaBuf, &Mode);
		if (rc != FS_OK)
		{
			GTL_Traces_TraceDebug ("__CST_Parameters_WriteBinFile : FS_mount sha file error");
			result = 1;
		} 

		ptr_Shafile = FS_open (ptr_ShaBuf, "a");
		if (ptr_Shafile == NULL)
		{
			result = 1;
			GTL_Traces_TraceDebug ("__CST_Parameters_WriteBinFile : Error create sha file");
		}
	}

	if (result == 0)	// If ok
	{
		// Save the parameters in the file
		FS_write (ac_l_pucBuffer, 1, i_l_Size, ptr_file);
		// Close file
		FS_close(ptr_file);

		// Save the sha in the file
		if(nShaLength != 0)
			FS_write (pucSha, 1, nShaLength, ptr_Shafile);
		else
			CST_Parameters_SetShaLength(nShaLength);

		// Close file
		FS_close(ptr_Shafile);
	}

	if (ac_l_pucBuffer != 0)
		ufree(ac_l_pucBuffer);
	return (result);
}



//! \brief This function reads a file of parameters (XML format) and extract tags and value to build a TLVTree. 
//! \param[in] pnode to store tags informations.
//! \param[in] pc_x_DirFile file path of xml text file to read.
//! \param[in] pc_x_fileName file name of xml text file to read.
//! \return
//! 0 if ok 1 else.

static int __CST_Parameters_ReadParamFile(TLV_TREE_NODE * p_node, char *pc_x_DirFile, unsigned int i_x_ParamFileType)
{
	int  result = 0;
	unsigned char * ac_l_pucBuffer = NULL;
	unsigned int Mode,rc;
	S_FS_FILE * ptr_file;

	// Read data from parameters file
	Mode = FS_READMOD;
	rc= FS_mount (pc_x_DirFile,&Mode);
	if (rc != FS_OK)
	{
		GTL_Traces_TraceDebug ("__CST_Parameters_ReadParamFile : FS_mount Error");
	}
	ptr_file = FS_open(pc_x_DirFile, "r");

	if (ptr_file != NULL)
	{
		int s;
		unsigned long ulFileLength;

		ulFileLength = FS_length (ptr_file);
		
		if (ulFileLength>C_PUC_MAX_BUFFER_SIZE) // If file size greater than max size
		{
			GTL_Traces_TraceDebug ("__CST_Parameters_ReadParamFile : Parameter file size too important !!!");
			result = 1;
		}
		else
		{
			ac_l_pucBuffer = (unsigned char *) umalloc(ulFileLength+10);
			FS_read (ac_l_pucBuffer, 1, ulFileLength+10, ptr_file);
			s = TlvTree_Unserialize(p_node, i_x_ParamFileType, ac_l_pucBuffer, ulFileLength+10);
			ufree(ac_l_pucBuffer);

			if (s != 0)
			{
				// Reset of this node, a problem occured
				p_node = 0;
				result = 1;
			}
		}
		FS_close(ptr_file);
	}
	else // Pb on FS_open()
	{
		result = 1;
	}

	return (result);
}



//! \brief This function give disk label used to store parameters. 
//! \param[in/out] Disk name to update.

static void __CST_Parameters_Get_Disk_Name(char* ptDiskName)
{
	sprintf(gs_Label_Disk_Name,"%s%02x", LABEL_DISK, 0);
	memcpy(ptDiskName, gs_Label_Disk_Name, sizeof(gs_Label_Disk_Name));
}



//! \brief This function create give disk to store parameters. 
//! \return
//! FS_OK if disk created, other else.

static int __CST_Parameters_CreateDisk (void)
{
	int               Retour;
	unsigned long     DiskSize;
	S_FS_PARAM_CREATE ParamCreat;
	char              FilePath_L[33];

	ParamCreat.Mode         = FS_WRITEONCE;
	ParamCreat.IdentZone    = FS_WO_ZONE_DATA;

	memclr(gs_Label_Disk_Name,sizeof(gs_Label_Disk_Name));
	sprintf(gs_Label_Disk_Name,"%s%02x", LABEL_DISK, 0);

	strcpy(ParamCreat.Label, gs_Label_Disk_Name);
	ParamCreat.AccessMode   = FS_WRTMOD;
	ParamCreat.NbFichierMax = 20;
	DiskSize              = DISK_SIZE;

	sprintf(FilePath_L,"/%s",gs_Label_Disk_Name);
	Retour = FS_mount (FilePath_L,&ParamCreat.Mode);
	if (Retour != FS_OK)
	{
		Retour=FS_dskcreate(&ParamCreat,&DiskSize);
	}
	return (Retour);
}



//! \brief This function clear TLVTree used to store parameters. 
//! \param[in] TLVTree to clear.

void CST_Parameters_InitParameters(TLV_TREE_NODE * pTree)
{
	TlvTree_ReleaseEx(pTree);
}



//! \brief This function update TLVTree with defaut parameters (read in an array). 
//! \param[in] TLVTree to update with default parameters.

void CST_Parameters_ReadDefaultParameters(TLV_TREE_NODE * pTree)
{
	CST_Parameters_InitParameters (pTree);

	// Default parameters initialisation => set in TLV tree
	*pTree = __CST_Parameters_ReadArray((char*)gs_DefaultParam, sizeof(gs_DefaultParam));
}



//! \brief This function update TLVTree with parameters read in a XML text file. 
//! \param[in] p_node to update with parameters read.
//! \param[in] i_x_tag main node to set in TLVRee.
//! \param[in] filePath file path of xml text file to read.
//! \param[in] fileName file name of xml text file to read.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int CST_Parameters_ReadXMLParamFile (TLV_TREE_NODE * p_node, unsigned int i_x_tag, char *filePath, char *fileName)
{
	int  result = 0;
	unsigned char * ac_l_pucBuffer = NULL;
	unsigned int Mode,rc;
	S_FS_FILE * ptr_file;
	unsigned int i_x_ParamFileType = TLV_TREE_SERIALIZER_XML;
	int s = 0;
	unsigned long ulFileLength = 0;

	(void)i_x_tag;
	ptr_file = NULL;

	// Open input file
	Mode = FS_READMOD;
	rc= FS_mount (filePath,&Mode);
	if (rc != FS_OK)
	{
		// Cannot mount the file
		GTL_Traces_TraceDebug("CST_Parameters_ReadXMLParamFile : Cannot mount the file\n");
		result = 1;
		goto End;
	}

	// Open the file
	ptr_file = FS_open (fileName, "r");
	
	if (ptr_file == NULL)
	{
		// Problem with file
		GTL_Traces_TraceDebug("CST_Parameters_ReadXMLParamFile : FS_open(%s) ko\n", fileName);
		result = 1;
		goto End;
	}
	else
	{
		// File correctly opened, allocate a buffer to store the file content
		ulFileLength = FS_length (ptr_file);
		
		if (ulFileLength>C_PUC_MAX_BUFFER_SIZE) // If file size greater than max size
		{
			result = 1;
			GTL_Traces_TraceDebug("CST_Parameters_ReadXMLParamFile : XML param file size too important\n");
			goto End;
		}
		else
		{
			ac_l_pucBuffer = (unsigned char *) umalloc(ulFileLength+10);
			// Read the file content, and store it in ac_l_pucBuffer
			FS_read (ac_l_pucBuffer, 1, ulFileLength+10, ptr_file);
			// Unserialise the file content (as it is a TLV Tree)
			s = TlvTree_Unserialize(p_node, i_x_ParamFileType, ac_l_pucBuffer, ulFileLength+10);
			// TLV Tree is unserialised, free the allocated buffer
			ufree(ac_l_pucBuffer);
		}

		if (s != 0)
		{
			// Reset of this node, a problem occured
			p_node = 0;
			result = 1;
			GTL_Traces_TraceDebug("CST_Parameters_ReadXMLParamFile : PB unserialize param file\n");
			goto End;
		}
	}

End:
	// If mount has been made, unmount the disk
	if (rc == FS_OK)
		FS_unmount(filePath);
	
	if (ptr_file != NULL)
		FS_close(ptr_file);

	return (result);
}



//! \brief This function set TLVTree parameters in a save file, and save the sha calculated in a second file. 
//! \param[in] pTree to save.
//! \param[in] pucSha Sha to save (calculated with given parameters).
//! \param[in] nShaLength Length of the sha.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int CST_Parameters_SaveParam (TLV_TREE_NODE pTree, unsigned char *pucSha, int nShaLength)
{
	// Local variables déclaration
	// Function result
	int nResult;
	char ac_l_FilePath_L[80];
	char ac_l_ShaFilePath_L[80];
	char LabelDiskName[DISK_NAME_SIZE];

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__CST_Parameters_Get_Disk_Name(LabelDiskName);

	// Update CLESSPARAM.PAR serial binary TLVTree format file
	sprintf(ac_l_FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM_SAV);
	sprintf(ac_l_ShaFilePath_L, "/%s/%s", LabelDiskName, C_FILE_SHAPARAM_SAV);
	nResult = __CST_Parameters_WriteBinFile(pTree, ac_l_FilePath_L, pucSha, nShaLength, ac_l_ShaFilePath_L);

	return(nResult);
}



//! \brief This function update TLVTree with parameters read in a save file. 
//! \param[in] pTree TLVTree to get.
//! \param[in] pucSha sha to get.
//! \param[in] nSize size of the pucSha buffer.
//! \param[in] pulShaLength length of the sha.
//! \return
//!		- 0 if no problem
//!		- 1 else.

int CST_Parameters_RestoreParam (TLV_TREE_NODE * pTree, unsigned char *pucSha, int nSize, unsigned long *pulShaLength)
{
	char FilePath_L[80];
	int ret = FS_OK;
	char LabelDiskName[DISK_NAME_SIZE];
	int nResult;
	unsigned int Mode,rc;

	memclr(FilePath_L,sizeof(FilePath_L));

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__CST_Parameters_Get_Disk_Name(LabelDiskName);

	Mode = FS_WRTMOD;
	sprintf(FilePath_L, "/%s", LabelDiskName);
	rc = FS_mount(FilePath_L, &Mode);
	if (rc != FS_OK)
	{
		GTL_Traces_TraceDebug ("CST_Parameters_RestoreParam : FS_mount Error");
		nResult = 1;
	}
	else
	{
		// Restore the parameters from saved file
		sprintf(FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM_SAV);
		// Set path in input buffer for BuildParameters() call
		ret = FS_exist (FilePath_L);
		
		if (ret == FS_OK)
		{
			GTL_Traces_TraceDebug("CST_Parameters_RestoreParam : Load %s file", C_FILE_PARAM_SAV);
			// Load parameter file in the terminal
			nResult = __CST_Parameters_FileRead (pTree, FilePath_L, C_FILE_PARAM_SAV);
		}
		else
		{
			GTL_Traces_TraceDebug("CST_Parameters_RestoreParam : %s file not existing", C_FILE_PARAM_SAV);
			nResult = 1;
		}

		if(nResult !=1)
		{
			// Parameters are restored, now try to restore the sha from saved file
			sprintf(FilePath_L, "/%s/%s", LabelDiskName, C_FILE_SHAPARAM_SAV);
			ret = FS_exist (FilePath_L);

			if (ret == FS_OK)
			{
				GTL_Traces_TraceDebug("CST_Parameters_RestoreParam : Load %s file", C_FILE_SHAPARAM_SAV);
				// Load sha file in the terminal
				nResult = __CST_Parameters_ShaFileRead (pucSha, nSize, pulShaLength, FilePath_L, C_FILE_SHAPARAM_SAV);
			}
			else
			{
				GTL_Traces_TraceDebug("CST_Parameters_RestoreParam : %s file not existing", C_FILE_SHAPARAM_SAV);
				nResult = 1;
			}
		}
	}
	
	return (nResult);
}



//! \brief Read the XML file and store it in a TLV Tree.
//! \param[in] VolumeName Volume name where the file is located.
//! \param[in] FileName File Name.
//! \param[out] pTree Store the XML file content in this TLV Tree.
//! \return
//!		- \a FCT_OK if file is not for the application.
//!		- \a STOP if the file is for the application.

int CST_Parameters_ReadXMLFile (char * VolumeName, char * FileName, TLV_TREE_NODE * pTree)
{
	int nResult;
	char FilePath_L[DISK_NAME_SIZE];
	char FileName_L[DISK_NAME_SIZE];
	
	if (strcmp(FileName, C_FILE_PARAM_XML) == 0)  // Does the file name is CLESSCUST.PAR ?
	{
		// Reset TLVTree
		CST_Parameters_InitParameters(pTree);
		
		// Read XML file
		sprintf(FilePath_L, "/%s", VolumeName);
		sprintf(FileName_L, "/%s/%s", VolumeName, FileName);
		
		// Read the parameter file and store the content in pTree
		nResult = CST_Parameters_ReadXMLParamFile (pTree, 0, FilePath_L, FileName_L);		
    	if (nResult != 0)
		{
			GTL_Traces_TraceDebug ("CST_Parameters_ReadXMLFile : CLESSCUST.PAR incorrect file received\n");
		}
		return (STOP); // File is ok for this application
	}
	return (FCT_OK);
}


//! \brief Check the CA keys coherence and verify the checksum.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "CST_DumpData.h" functions).

void CST_Parameters_CheckCaKeysCrc (TLV_TREE_NODE ParameterTlvTree)
{
	TLV_TREE_NODE pCaKeysParams;		// Node for CAKeys.
	TLV_TREE_NODE pChild, pChildTmp;	// CA Key content
	TLV_TREE_NODE pResearch;			// Working Node
	unsigned char ucTempBuffer[288];
	unsigned int nDataLength;
	int bContinue;
	unsigned long * pShaResult;
	unsigned char * pRid;
	unsigned char * pCapkIndex;
	unsigned char * pCapkModulus;
	unsigned char * pCapkExponent;
	unsigned char * pCapkCrc;
	unsigned int nRidLength;
	unsigned int nCapkIndexLength;
	unsigned int nCapkModulusLength;
	unsigned int nCapkExponentLength;
	unsigned int nCapkCrcLength;
	unsigned int nIndex;
	unsigned int bCertificateErrorDetected = FALSE;
	
	pCaKeysParams = TlvTree_Find(ParameterTlvTree, C_PARAM_CAKEY_TAG, 0);
	
	if (pCaKeysParams != NULL)
	{
		// For each CA Key found in parameters
		pChild = TlvTree_GetFirstChild(pCaKeysParams);
		
		while (pChild != NULL)
		{
			// Clear the temporary buffer
			memset (ucTempBuffer, 0x00, sizeof(ucTempBuffer));
			nDataLength = 0;
			bContinue = TRUE;
			pShaResult = NULL;
			pRid = NULL;
			pCapkIndex = NULL;
			pCapkModulus = NULL;
			pCapkExponent = NULL;
			pCapkCrc = NULL;
			nRidLength = 0;
			nCapkIndexLength = 0;
			nCapkModulusLength = 0;
			nCapkExponentLength = 0;
			nCapkCrcLength = 0;


			// First, check the RID is present with length equal to 5 bytes
			pResearch = TlvTree_Find(pChild, TAG_EMV_AID_TERMINAL, 0); // If AID informations have been founded
				
			if (pResearch != NULL)
			{
				pRid = TlvTree_GetData(pResearch);
				nRidLength = TlvTree_GetLength(pResearch);

				if (nRidLength == 5)
				{
					memcpy (&(ucTempBuffer[nDataLength]), pRid, nRidLength);
					nDataLength += nRidLength;
				}
				else
				{
					// RID has a bad length
					bContinue = FALSE;
				}
			}
			else
			{
				// RID is missing, check next 
				bContinue = FALSE;
			}


			// Check CA PK index is present with length set to 1
			pResearch = TlvTree_Find(pChild, TAG_EMV_CA_PUBLIC_KEY_INDEX_TERM, 0); // If AID informations have been founded

			if (pResearch != NULL)
			{
				pCapkIndex = TlvTree_GetData(pResearch);
				nCapkIndexLength = TlvTree_GetLength(pResearch);

				if (nCapkIndexLength == 1)
				{
					memcpy (&(ucTempBuffer[nDataLength]), pCapkIndex, nCapkIndexLength);
					nDataLength += nCapkIndexLength;
				}
				else
				{
					// CA Public Key Index has a bad length, check next
					bContinue = FALSE;
				}
			}
			else
			{
				// CA Public Key Index is missing, check next
				bContinue = FALSE;
			}


			// Check CA PK Modulus is present with length in [1;248]
			pResearch = TlvTree_Find(pChild, TAG_EMV_INT_CAPK_MODULUS, 0);

			if (pResearch != NULL)
			{
				pCapkModulus = TlvTree_GetData(pResearch);
				nCapkModulusLength = TlvTree_GetLength(pResearch);

				if ((nCapkModulusLength > 0) && (nCapkModulusLength <= 248))
				{
					memcpy (&(ucTempBuffer[nDataLength]), pCapkModulus, nCapkModulusLength);
					nDataLength += nCapkModulusLength;
				}
				else
				{
					// CA Public Key Modulus has a bad length, check next
					bContinue = FALSE;
				}
			}
			else
			{
				// CA Public Key Modulus is missing, check next
				bContinue = FALSE;
			}


			// Check CA PK Exponent is present and length is either 1 or 3.
			pResearch = TlvTree_Find(pChild, TAG_EMV_INT_CAPK_EXPONENT, 0); // If AID informations have been founded

			if (pResearch != NULL)
			{
				pCapkExponent = TlvTree_GetData(pResearch);
				nCapkExponentLength = TlvTree_GetLength(pResearch);

				if ((nCapkExponentLength == 1) || (nCapkExponentLength == 3))
				{
					memcpy (&(ucTempBuffer[nDataLength]), pCapkExponent, nCapkExponentLength);
					nDataLength += nCapkExponentLength;
				}
				else
				{
					// CA Public Key Exponent has a bad length, check next
					bContinue = FALSE;
				}
			}
			else
			{
				// CA Public Key Exponent is missing, check next
				bContinue = FALSE;
			}


			// Calculate the CRC
			if (bContinue)
			{
				pShaResult = GTL_SHA_Sha1Compute (ucTempBuffer, nDataLength);
			}



			// Check the CA PK Checksum is present with length 20, and check it matches the computed checksum
			pResearch = TlvTree_Find(pChild, TAG_EMV_INT_CAPK_CHECKSUM, 0);

			if (pResearch != NULL)
			{
				pCapkCrc = TlvTree_GetData(pResearch);
				nCapkCrcLength = TlvTree_GetLength(pResearch);

				if (nCapkCrcLength == 20)
				{
					if (memcmp ((unsigned char *)pShaResult, pCapkCrc, 20) != 0)
						bContinue = FALSE;
				}
				else
				{
					// CA Public Key CRC has a bad length, check next
					bContinue = FALSE;
				}
			}
			else
			{
				// CA Public Key CRC is missing, check next
				bContinue = FALSE;
			}

			
			// If a checking error occured, dump the incorrect CA structure information
			if (!bContinue)
			{
				if (CST_DumpData_OpenOutputDriver())
				{
					if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
						CST_DumpData ("\x1b" "E");

					CST_DumpData ("INVALID CERTIFICATE");

					if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
						CST_DumpData ("\x1b" "@" "\x0F");

					CST_DumpData_NewLine();
					CST_DumpData_NewLine();
					CST_DumpData ("RID = ");
					if (nRidLength != 0)
						if (nRidLength != 5)
							CST_DumpData("Bad Length");
						else
							CST_DumpData("%02x%02x%02x%02x%02x", pRid[0], pRid[1], pRid[2], pRid[3], pRid[4]);
					else
						CST_DumpData("Missing");
					CST_DumpData_NewLine();

					CST_DumpData ("Index = ");
					if (nCapkIndexLength != 0)
						if (nCapkIndexLength != 1)
							CST_DumpData("Bad Length");
						else
							CST_DumpData ("%02x", pCapkIndex[0]);
					else
						CST_DumpData("Missing");
					CST_DumpData_NewLine();

					CST_DumpData ("Modulus = ");
					if (nCapkModulusLength != 0)
						if (nCapkModulusLength > 248)
							CST_DumpData("Bad Length");
						else
							CST_DumpData ("%02x%02x...%02x%02x", pCapkModulus[0], pCapkModulus[1], pCapkModulus[nCapkModulusLength-2], pCapkModulus[nCapkModulusLength-1]);
					else
						CST_DumpData("Missing");
					CST_DumpData_NewLine();

					CST_DumpData ("Exponent = ");
					if (nCapkExponentLength != 0)
						if ((nCapkExponentLength != 1) && (nCapkExponentLength != 3))
							CST_DumpData("Bad Length");
						else
							if (nCapkExponentLength == 1)
								CST_DumpData ("%02x", pCapkExponent[0]);
							else
								CST_DumpData ("%02x%02x%02x", pCapkExponent[0], pCapkExponent[1], pCapkExponent[2]);
					else
						CST_DumpData("Missing");
					CST_DumpData_NewLine();

					CST_DumpData ("CRC = ");
					if (nCapkCrcLength != 0)
						if (nCapkCrcLength != 20)
							CST_DumpData("Bad Length");
						else
						{
							for (nIndex=0;nIndex<20;nIndex++)
								CST_DumpData ("%02x", pCapkCrc[nIndex]);
						}
					else
						CST_DumpData("Missing");
					CST_DumpData_NewLine();
					CST_DumpData_NewLine();

					if (pShaResult != NULL)
					{
						CST_DumpData ("Expected Cks = ");
						for (nIndex=0;nIndex<20;nIndex++)
								CST_DumpData ("%02x", ((unsigned char *)pShaResult)[nIndex]);
					}		
					CST_DumpData_NewLine();
					CST_DumpData_NewLine();
					CST_DumpData_NewLine();

					if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
						CST_DumpData ("\x1b" "@");

					CST_DumpData_CloseOutputDriver();
				}
			}

			// Get the next CA structure
			pChildTmp = pChild;
			pChild = TlvTree_GetNext(pChild);
			
			if (!bContinue)
			{
				bCertificateErrorDetected = TRUE;
				TlvTree_Release(pChildTmp);
			}
		}
	}

	// If a certificate error has been detected, display a message on th emerchant screen
	if (bCertificateErrorDetected)
	{
		Helper_DisplayMessage(STD_MESS_INVALID_CERTIFICATE, ERASE, HELPERS_MERCHANT_LINE_2);
    	Helper_RefreshScreen(WAIT);
	}
}


//! \brief Dump the CA keys configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.

void CST_Parameters_DumpCaKeys (TLV_TREE_NODE ParameterTlvTree)
{
	TLV_TREE_NODE pCaKeysParams;		// Node for CAKeys.
	TLV_TREE_NODE pChild;				// CA Key content
	
	pCaKeysParams = TlvTree_Find(ParameterTlvTree, C_PARAM_CAKEY_TAG, 0);
	
	if (pCaKeysParams != NULL)
	{
		// For each CA Key found in parameters
		pChild = TlvTree_GetFirstChild(pCaKeysParams);
		
		while (pChild != NULL)
		{
			// Dump the structure
			CST_DumpData_DumpTlvTreeNodeWithTitle ("CERTIFICATE", pChild);

			// Get the next CA structure
			pChild = TlvTree_GetNext(pChild);
		}
	}
}



//! \brief Dumps the parameters identifier label.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.

void CST_Parameters_DumpIdentificationLabel (TLV_TREE_NODE ParameterTlvTree)
{
	TLV_TREE_NODE pParamIdLabel;		// Node for Parameter Identification Label.
	unsigned char * pValue;
	unsigned int nDataLength;
	unsigned char szString[32];
	
	pValue = NULL;
	nDataLength = 0;
	memset (szString, '\0', sizeof(szString));

	pParamIdLabel = TlvTree_Find(ParameterTlvTree, TAG_SDSA_PARAMETERS_LABEL, 0);
	
	if (pParamIdLabel != NULL)
	{
		pValue = TlvTree_GetData(pParamIdLabel);
		nDataLength = TlvTree_GetLength(pParamIdLabel);
	}
	
	// Dump the title
	if (CST_DumpData_OpenOutputDriver())
	{
		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "E");

		if ((pValue != NULL) && (nDataLength != 0))
		{
			memcpy (szString, pValue, nDataLength);
			CST_DumpData ("%s", szString);
		}
		else
		{
			CST_DumpData ("UNKNOWN PARAM ID");
		}

		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();
		CST_DumpData_NewLine();

		if (CST_DumpData_GetOutputId() == CST_OUTPUT_PRINTER)
			CST_DumpData ("\x1b" "@");

		// Close the output driver
		CST_DumpData_CloseOutputDriver();
	}
}



//! \brief Dump the AIDs configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.

void CST_Parameters_DumpAids (TLV_TREE_NODE ParameterTlvTree)
{
	TLV_TREE_NODE pAidsParams;		// Node for CAKeys.
	TLV_TREE_NODE pChild;				// CA Key content
	
	pAidsParams = TlvTree_Find(ParameterTlvTree, C_PARAM_AID_TAG, 0);
	
	if (pAidsParams != NULL)
	{
		// For each CA Key found in parameters
		pChild = TlvTree_GetFirstChild(pAidsParams);
		
		while (pChild != NULL)
		{
			// Dump the title
			CST_DumpData_DumpTlvTreeNodeWithTitle ("AID STRUCTURE", pChild);

			// Get the next CA structure
			pChild = TlvTree_GetNext(pChild);
		}
	}
}



//! \brief Dump the global parameters configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.

void CST_Parameters_DumpGlobals (TLV_TREE_NODE ParameterTlvTree)
{
	TLV_TREE_NODE pGlobalParams;		// Node for Global data.
	TLV_TREE_NODE pChild;				// CA Key content
	
	pGlobalParams = TlvTree_Find(ParameterTlvTree, C_PARAM_GLOBAL_TAG, 0);
	
	if (pGlobalParams != NULL)
	{
		// For each CA Key found in parameters
		pChild = TlvTree_GetFirstChild(pGlobalParams);
		
		while (pChild != NULL)
		{
			// Dump the title
			CST_DumpData_DumpTlvTreeNodeWithTitle ("GLOBAL DATA", pChild);

			// Get the next CA structure
			pChild = TlvTree_GetNext(pChild);
		}
	}
}



//! \brief Dump the kernel specific parameters configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.

void CST_Parameters_DumpKernelSpecific (TLV_TREE_NODE ParameterTlvTree)
{
	TLV_TREE_NODE pKernelParams;		// Node for kernel specific data.
	TLV_TREE_NODE pChild;				// CA Key content
	
	pKernelParams = TlvTree_Find(ParameterTlvTree, C_PARAM_KERNEL_TAG, 0);
	
	if (pKernelParams != NULL)
	{
		// For each CA Key found in parameters
		pChild = TlvTree_GetFirstChild(pKernelParams);
		
		while (pChild != NULL)
		{
			// Dump the title
			CST_DumpData_DumpTlvTreeNodeWithTitle ("KERNEL SPECIFIC", pChild);

			// Get the next CA structure
			pChild = TlvTree_GetNext(pChild);
		}
	}
}


//! \brief This function returns the Sha of the current parameters.
//! \return Sha calculated on the current parameters.

unsigned char *CST_Parameters_GetSha(void)
{
	return(gs_ucTerminalSha);
}


//! \brief This function returns the size of the variable that contained the Sha of the current parameters.
//! \return The size of the variable that contained the Sha.

int CST_Parameters_GetShaSize(void)
{
	return(sizeof(gs_ucTerminalSha));
}


//! \brief This function returns the length of the Sha of the current parameters.
//! \return The sha length.

unsigned long *CST_Parameters_GetShaLength(void)
{
	return(&gs_ulTerminalShaLength);
}


//! \brief This function set the length of the Sha of the current parameters.
//! \param[in] ulLen Length of the Sha.

void CST_Parameters_SetShaLength(unsigned long ulLen)
{
	gs_ulTerminalShaLength = ulLen;
}


//! \brief This function checks the consistency between the terminal parameters and the intelligent reader parameters.
//! \brief If parameters are not consistent, parameters are loaded in the intelligent reader.

void CST_Parameters_CheckConsistency(void)
{
	TLV_TREE_NODE hTlvTreeParam = NULL;
	TLV_TREE_NODE pTlvTreeSha, hTlvTreeIn, hTlvTreeOut;
	unsigned long ulReaderCRCLength;
	unsigned char *pReaderSha;
	int nResult;
	int bUpdateNeeded;
	unsigned char ucGetShaOnly;
	
	bUpdateNeeded = TRUE;
	
	if(pTreeCurrentParam == NULL)
	{
		GTL_Traces_TraceDebug("CST_Parameters_CheckConsistency, pTreeCurrentParam is null");

		// No parameters in the terminal, erase reader parameters.
		nResult = SDI_Payment_EraseParams(nSDSAAppliId);
	}
	else
	{
		// Get the SHA calculated on the reader parameters
		hTlvTreeIn = TlvTree_New(0);
		if (hTlvTreeIn != NULL)
		{
			ucGetShaOnly = TRUE;

			TlvTree_AddChild (hTlvTreeIn, TAG_SDSA_GET_PARAMETERS_SHA_ONLY, &ucGetShaOnly, sizeof (ucGetShaOnly));

			nResult = SDI_Payment_GetParams (nSDSAAppliId, hTlvTreeIn, &hTlvTreeParam);

			if ((nResult == SDI_STATUS_OK) && (hTlvTreeParam != NULL))
			{
				pTlvTreeSha = TlvTree_Find(hTlvTreeParam, TAG_SDSA_LOADED_PARAMETERS_SHA, 0);
				if(pTlvTreeSha != NULL)
				{
					pReaderSha = TlvTree_GetData(pTlvTreeSha);
					ulReaderCRCLength = TlvTree_GetLength(pTlvTreeSha);
				
					// Check if loaded parameters are the same in the terminal and in the reader
					if(gs_ulTerminalShaLength == ulReaderCRCLength)
					{
						if(memcmp(gs_ucTerminalSha, pReaderSha, gs_ulTerminalShaLength) == 0)
						{
							GTL_Traces_TraceDebug("CST_Parameters_CheckConsistency, PARAM OK");
							bUpdateNeeded = FALSE;
						}
					}
				}

				TlvTree_ReleaseEx (&hTlvTreeParam);
			}
			TlvTree_ReleaseEx (&hTlvTreeIn);

			if(nResult == SDI_STATUS_DISCONNECTED)
				goto End;
		}

		// Parameters are not consistent, parameters are loaded in the intelligent reader.
		if(bUpdateNeeded)
		{
			// Load the terminal parameters in the reader
			nResult = SDI_Payment_LoadParams (nSDSAAppliId, pTreeCurrentParam, &hTlvTreeOut);

			// Save the calculated SHA
			if ((nResult == SDI_STATUS_OK) && (hTlvTreeOut != NULL))
			{				
				pTlvTreeSha = TlvTree_Find(hTlvTreeOut, TAG_SDSA_LOADED_PARAMETERS_SHA, 0);
				if(pTlvTreeSha != NULL)
				{
					gs_ulTerminalShaLength = TlvTree_GetLength(pTlvTreeSha);
					memcpy(gs_ucTerminalSha, TlvTree_GetData(pTlvTreeSha), gs_ulTerminalShaLength);

					// Save parameters in a file.
					CST_Parameters_SaveParam (pTreeCurrentParam, gs_ucTerminalSha, gs_ulTerminalShaLength);
				}

				TlvTree_ReleaseEx (&hTlvTreeOut);
			}

			if(nResult == SDI_STATUS_DISCONNECTED)
				goto End;

			// New parameters, update some values
			CST_VisaWave_SetVisaAsiaGuiMode();
			CST_Interac_SetInteracGuiMode();
			CST_Parameters_GetMoneyExtendedFromParameters();
		}
	}

End:
	if(nResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();
}



//! \brief This function get the moneys defined in the parameter file.

void CST_Parameters_GetMoneyExtendedFromParameters(void)
{
	unsigned char * pucTagPtr;
	int nTagLentgth;
	unsigned int nIndex;
	TLV_TREE_NODE pKernelParams;		// Node for global parameters.
	TLV_TREE_NODE pNode;

	nIndex = 0;

	// Found specific parameters
	pKernelParams = TlvTree_Find (pTreeCurrentParam, C_PARAM_KERNEL_TAG, nIndex);
	
	if (pKernelParams != NULL) // If Kernel parameters founded
	{
		nIndex = 0;
		pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SDSA_GENERIC_MONEY_EXTENDED, nIndex++);

		if (pNode) // If something founded
		{
			nNbMoneyExtended = 0; // Reset for update it
			if (ptr_money_extended)
				ufree(ptr_money_extended);
			ptr_money_extended = NULL;
		}
		
		do{
			if (pNode) // If something founded
			{
				// Add informations in ptr_money_extended array
				nNbMoneyExtended++;

				pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SDSA_GENERIC_MONEY_EXTENDED, nIndex++);
			}
		}while (pNode != 0);
		
		nIndex = 0;
		if (nNbMoneyExtended)
		{
			ptr_money_extended = umalloc(nNbMoneyExtended * sizeof(S_MONEY_EXTENDED));
			pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SDSA_GENERIC_MONEY_EXTENDED, nIndex++);
	
			do{
				if (pNode) // If something founded
				{
					nTagLentgth = TlvTree_GetLength(pNode);
					pucTagPtr = TlvTree_GetData(pNode);
				}
				
				if (pNode) // If something founded
				{
					memset(&ptr_money_extended[nIndex-1], 0, sizeof(S_MONEY_EXTENDED)); 		// Reset structure
					if (nTagLentgth >= 10)														// If something founded
					{
						memcpy(ptr_money_extended[nIndex-1].currency.nom, pucTagPtr, 3); 		// Name copy, 3 bytes
						memcpy(ptr_money_extended[nIndex-1].currency.code, pucTagPtr + 3, 3); 	// Code copy, 3 bytes
						ptr_money_extended[nIndex-1].currency.posdec = pucTagPtr[6] - 0x30;		// Decimal position in the amount  
		
						ptr_money_extended[nIndex-1].infos.cents_separator = pucTagPtr[7];
						ptr_money_extended[nIndex-1].infos.thousands_separator = pucTagPtr[8];
						ptr_money_extended[nIndex-1].infos.currency_position = pucTagPtr[9] - 0x30;
					}
					pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SDSA_GENERIC_MONEY_EXTENDED, nIndex++);
				}
			}while (pNode != 0);
		}
	}
}

//! \brief This function give Extended money structure initialized with parameters.
//! \param[in/out] n_x_NbMoney Number of money managed.
//! \param[in/out] ps_x_Money pnode parameters node for the kernel.

void CST_Parameters_GetMoneyExtended(int * n_x_NbMoney, S_MONEY_EXTENDED ** ps_x_Money)
{
	*n_x_NbMoney = nNbMoneyExtended;
	*ps_x_Money  = ptr_money_extended;
}
