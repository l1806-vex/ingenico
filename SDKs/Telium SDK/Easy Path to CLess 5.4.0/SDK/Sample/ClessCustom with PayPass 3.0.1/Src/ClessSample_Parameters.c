/**
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
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

//! \brief 
const Struct_TagList CrcTagList[] = {
	{0x9F928210,			C_TAG_TYPE_BUF_BYTE,	NULL},
	{0x9F928212,			C_TAG_TYPE_BUF_BYTE,	NULL},
	{0x9F928214,			C_TAG_TYPE_BUF_BYTE,	NULL},
	{0x9F1A,				C_TAG_TYPE_BUF_BYTE,	NULL},
	{0x9F40,				C_TAG_TYPE_BUF_BYTE,	NULL},
	{0x9F35,				C_TAG_TYPE_BUF_BYTE,	NULL},
	{0x9F01,				C_TAG_TYPE_BUF_BYTE,	NULL},
	{0x9F15,				C_TAG_TYPE_BUF_BYTE,	NULL},
	{0x9F16,				C_TAG_TYPE_BUF_BYTE,	NULL},
	{0x9F1C,				C_TAG_TYPE_BUF_BYTE,	NULL},
};


//! \brief Default parameters (XML format)
const char gs_DefaultParam[] =
{
	"	<?xml version=\"1.0\" standalone=\"yes\" ?>"
	"	<!-- Fichier de parametres base kenels contacless -->"
	""
	"	<tlvtree ver=\"1.0\">"
	""
	"	<node tag=\"0x0\">"
	"		<node tag=\"0x9F918801\"> 44 65 66 61 75 6C 74 20 50 61 72 61 6d 65 74 65 72 73 </node>	<!-- TAG_SAMPLE_PARAMETERS_LABEL : Parameters identifier label -->"
	""
	"		<node tag=\"0xBF918800\">	<!-- TAG_SAMPLE_AID_PARAMETERS -->"
	""
	"			<node tag=\"0x1000\">"
	"				<!-- AID : MasterCard PayPass AID for debit -->"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 10 10 </node>					<!-- TAG_AID_TERMINAL : MasterCard PayPass AID -->"
	"				<node tag=\"0x9F918701\"> 00 </node>								<!-- TAG_EMV_INT_TRANSACTION_TYPE -->"
	"				<node tag=\"0x9F928100\"> 45 01 00 00 </node>						<!-- TAG_EP_AID_OPTIONS -->"
	"				<node tag=\"0x9F928101\"> 00 02 </node>								<!-- TAG_EP_KERNEL_TO_USE -->"
	"				<node tag=\"0x9F09\"> 00 02  </node>								<!-- TAG_EMV_APPLI_VERSION_NUMBER_TERM -->"
	"				<node tag=\"0x9F918523\"> 00 </node>								<!-- TAG_PAYPASS_CARD_DATA_INPUT_CAPABILITY -->"
	"				<node tag=\"0x9F918525\"> 60 </node>								<!-- TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_REQUIRED -->"
	"				<node tag=\"0x9F918526\"> 08 </node>								<!-- TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_NOT_REQUIRED -->"
	"				<node tag=\"0x9F918502\"> 9F 6A 04 </node>							<!-- TAG_PAYPASS_DEFAULT_UDOL -->"
	"				<node tag=\"0x9F918522\"> 20 </node>								<!-- TAG_PAYPASS_KERNEL_CONFIGURATION -->"
	"				<node tag=\"0x9F6D\"> 00 01 </node>									<!-- TAG_PAYPASS_MSTRIPE_APPLI_VERSION_NUMBER_TERM -->"
	"				<node tag=\"0x9F918527\"> 10 </node>								<!-- TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_REQUIRED -->"
	"				<node tag=\"0x9F918528\"> 00 </node>								<!-- TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_NOT_REQUIRED -->"
	"				<node tag=\"0x9F7C\"> 30 31 32 33 34 35 36 37 38 39 41 42 43 44 "
	"								45 46 47 48 49 4A </node>							<!-- TAG_PAYPASS_MERCHANT_CUSTOM_DATA -->"
	"				<node tag=\"0x9F15\"> 93 11 </node>									<!-- TAG_EMV_MERCHANT_CATEGORY_CODE -->"
	"				<node tag=\"0x9F92810F\"> 00 00 00 01 00 00 </node>					<!-- TAG_EP_CLESS_FLOOR_LIMIT -->"
	"				<node tag=\"0x9F91851C\"> 00 00 00 03 00 00 </node>					<!-- TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_NO_DCV -->"
	"				<node tag=\"0x9F91851D\"> 00 00 00 05 00 00 </node>					<!-- TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_DCV -->"
	"				<node tag=\"0x9F92810E\"> 00 00 00 00 10 00 </node>					<!-- TAG_EP_CLESS_CVM_REQUIRED_LIMIT -->"
	"				<node tag=\"0x9F918524\"> 08 </node>								<!-- TAG_PAYPASS_SECURITY_CAPABILITY -->"
	"				<node tag=\"0x9F918709\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_DEFAULT -->"
	"				<node tag=\"0x9F91870A\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_DENIAL -->"
	"				<node tag=\"0x9F91870B\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_ONLINE -->"
	"				<node tag=\"0x9F35\"> 22 </node>								    <!-- TAG_EMV_TERMINAL_TYPE	 -->"
	"				<node tag=\"0x9F91841D\"> 65 6E 66 72 </node>						<!-- TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES -->"
	"			</node>"
	""
	"			<node tag=\"0x1000\">"
	"				<!-- AID : Maestro PayPass AID for debit -->"
	"				<node tag=\"0x9F06\"> A0 00 00 00 04 30 60 </node>					<!-- TAG_AID_TERMINAL : Maestro PayPass AID -->"
	"				<node tag=\"0x9F918701\"> 00 </node>								<!-- TAG_EMV_INT_TRANSACTION_TYPE -->"
	"				<node tag=\"0x9F928100\"> 45 01 00 00 </node>						<!-- TAG_EP_AID_OPTIONS -->"
	"				<node tag=\"0x9F928101\"> 00 02 </node>								<!-- TAG_EP_KERNEL_TO_USE : MasterCard -->"
	"				<node tag=\"0x9F09\"> 00 02  </node>								<!-- TAG_EMV_APPLI_VERSION_NUMBER_TERM -->"
	"				<node tag=\"0x9F918523\"> 00 </node>								<!-- TAG_PAYPASS_CARD_DATA_INPUT_CAPABILITY -->"
	"				<node tag=\"0x9F918525\"> 60 </node>								<!-- TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_REQUIRED -->"
	"				<node tag=\"0x9F918526\"> 08 </node>								<!-- TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_NOT_REQUIRED -->"
	"				<node tag=\"0x9F918502\"> 9F 6A 04 </node>							<!-- TAG_PAYPASS_DEFAULT_UDOL -->"
	"				<node tag=\"0x9F918522\"> A0 </node>								<!-- TAG_PAYPASS_KERNEL_CONFIGURATION -->"
	"				<node tag=\"0x9F6D\"> 00 01 </node>									<!-- TAG_PAYPASS_MSTRIPE_APPLI_VERSION_NUMBER_TERM -->"
	"				<node tag=\"0x9F918527\"> 10 </node>								<!-- TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_REQUIRED -->"
	"				<node tag=\"0x9F918528\"> 00 </node>								<!-- TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_NOT_REQUIRED -->"
	"				<node tag=\"0x9F7C\"> 30 31 32 33 34 35 36 37 38 39 41 42 43 44 "
	"									45 46 47 48 49 4A </node>							<!-- TAG_PAYPASS_MERCHANT_CUSTOM_DATA -->"
	"				<node tag=\"0x9F15\"> 93 11 </node>									<!-- TAG_EMV_MERCHANT_CATEGORY_CODE -->"
	"				<node tag=\"0x9F92810F\"> 00 00 00 01 00 00 </node>					<!-- TAG_EP_CLESS_FLOOR_LIMIT -->"
	"				<node tag=\"0x9F91851C\"> 00 00 00 03 00 00 </node>					<!-- TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_NO_DCV -->"
	"				<node tag=\"0x9F91851D\"> 00 00 00 05 00 00 </node>					<!-- TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_DCV -->"
	"				<node tag=\"0x9F92810E\"> 00 00 00 03 00 00 </node>					<!-- TAG_EP_CLESS_CVM_REQUIRED_LIMIT -->"
	"				<node tag=\"0x9F918524\"> 08 </node>								<!-- TAG_PAYPASS_SECURITY_CAPABILITY -->"
	"				<node tag=\"0x9F918709\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_DEFAULT -->"
	"				<node tag=\"0x9F91870A\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_DENIAL -->"
	"				<node tag=\"0x9F91870B\"> 00 00 00 00 00 </node>					<!-- TAG_EMV_INT_TAC_ONLINE -->"
	"				<node tag=\"0x9F35\"> 22 </node>								    <!-- TAG_EMV_TERMINAL_TYPE	 -->"
	"				<node tag=\"0x9F91841D\"> 65 6E 66 72 </node>						<!-- TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES -->"
	"			</node>"
	""
	"		</node> <!-- End node 0xBF918800 : TAG_SAMPLE_AID_PARAMETERS -->"
	""
	""
	"		<node tag=\"0xBF918801\">	<!-- TAG_SAMPLE_CAKEYS_PARAMETERS -->"
	""
	"			<node tag=\"0x1000\">"
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
	"			<node tag=\"0x1000\">"
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
	"			<node tag=\"0x1000\">"
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
	"			<node tag=\"0x1000\">"
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
	"			<node tag=\"0x1000\">"
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
	"			<node tag=\"0x1000\">"
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
	"			<node tag=\"0x1000\">"
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
	"			<node tag=\"0x1000\">"
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
	"			<node tag=\"0x1000\">"
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
	"		</node> <!-- End node 0xBF918801 : TAG_SAMPLE_CAKEYS_PARAMETERS-->"
	""
	"		<node tag=\"0xBF918802\">	<!-- TAG_SAMPLE_CAREVOK_PARAMETERS -->"
	"		</node> <!-- End node 0xBF918802 : TAG_SAMPLE_CAREVOK_PARAMETERS -->"
	""
	""
	"		<node tag=\"0xBF918803\">	<!-- TAG_SAMPLE_ICS_PARAMETERS -->"
	""
	"			<node tag=\"0x1000\">"
	"				<!-- ICS0 values -->"
	"				<node tag=\"0x9F928210\"> 03 00 00 00 </node>				<!-- TAG_GENERIC_DETECTION_TYPE -->"
	"				<node tag=\"0x9F928212\"> 00 00 17 70 </node>				<!-- TAG_GENERIC_DETECTION_GLOBAL_TIMEOUT : 6000 -->"
	"				<node tag=\"0x9F928214\"> 01 </node>						<!-- TAG_GENERIC_DETECTION_NB_CARDS_TO_DETECT -->"
	"				<node tag=\"0x9F918804\"> 03 A9 80 </node>					<!-- TAG_SAMPLE_NO_CARD_TIMEOUT : 4 minutes (240000ms = 3A980) (Interac GUI mode) -->"
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
	"				<node tag=\"0x9F918565\"> 00 00 </node>						<!-- TAG_PAYPASS_MAX_LIFETIME_OF_TORN_TXN_LOG_RECORD -->"
    "  				<node tag=\"0x9F918561\"> 00 </node>						<!-- TAG_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS -->"
	""
	"			</node> <!-- End node 1000 -->"
	"		</node> <!-- End node 0xBF918803 : TAG_SAMPLE_ICS_PARAMETERS-->"
	""
	"		<node tag=\"0xBF918804\">	<!-- TAG_SAMPLE_SPECIFIC_PARAMETERS -->"
	""
	"			<!-- PAYPASS Specific parameters -->"
	"			<node tag=\"0x1000\">"
	"				<node tag=\"0x9F928101\"> 00 02 </node>				<!-- TAG_EP_KERNEL_TO_USE : PAYPASS -->"
	"			</node> <!-- End node 1000 -->"
	""
	"			<node tag=\"0x9F918802\" format=\"ascii\"> \"EUR9782,.1\" </node>		<!-- TAG_SAMPLE_GENERIC_MONEY_EXTENDED EUR9782,.1 -->"
	"			<node tag=\"0x9F918802\" format=\"ascii\"> \"MYR4582,.1\" </node>		<!-- TAG_SAMPLE_GENERIC_MONEY_EXTENDED MYR4582,.1 -->"
	"			<node tag=\"0x9F918802\" format=\"ascii\"> \"CAD1242,.1\" </node>		<!-- TAG_SAMPLE_GENERIC_MONEY_EXTENDED CAD1242,.1 -->"
	"			<node tag=\"0x9F918802\" format=\"ascii\"> \"USD8402,.1\" </node>		<!-- TAG_SAMPLE_GENERIC_MONEY_EXTENDED USD8402,.1 -->"
	"		</node> <!-- End node 0xBF918804 : TAG_SAMPLE_SPECIFIC_PARAMETERS-->"
	""
	"	</node>	 <!-- End node 0 -->"
	"</tlvtree>"
};


//! \brief Global TLV Tree used for parameters management.
TLV_TREE_NODE pTreeCurrentParam = NULL;							/*!< Node from param file parameters. */
TLV_TREE_NODE pTreeDefaultParam = NULL;							/*!< Node from default parameters. */

static char gs_Label_Disk_Name[DISK_NAME_SIZE];				/*!< To store the disk name. */

// Global variable declaration
static T_PARAMETER_AID gs_Parameter_AID[C_NUMBER_AID_MAX];	/*!< Static structure containing all the AID data prepared before card presentation. */
static int gs_nNbParameterSet; 								/*!< Static data containing the number of configured AID. */

static int nNbMoneyExtended = 0;
static S_MONEY_EXTENDED * ptr_money_extended = NULL;


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////

static void __ClessSample_Parameters_BuildListValue(TLV_TREE_NODE * pTree, char * pc_x_buffer, int * pi_x_Index, Struct_TagList * ps_x_ListPointer, int i_x_NbTag);
static void __ClessSample_Parameters_Get_Disk_Name(char* ptDiskName);
static void __ClessSample_Parameters_SetKRevokParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID);
static void __ClessSample_Parameters_SetKernelParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID);
static void __ClessSample_Parameters_SetGlobalParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID);
static int __ClessSample_Parameters_HexToAscii(char * ac_x_hexbuf, int i_x_hexbuflg, char * ac_x_asciibuf);

static int __ClessSample_Parameters_ReadParameter(TLV_TREE_NODE * pTree, unsigned int nIndex, unsigned long tag, ParameterElement *data);
static int __ClessSample_Parameters_SetBooleanValue (unsigned char *value, unsigned char *pBool);
static int __ClessSample_Parameters_FileRead(TLV_TREE_NODE * pTree, char *pc_x_DirFile, char *pc_x_fileName);
static int __ClessSample_Parameters_WriteBinFile(TLV_TREE_NODE pTree, char * ptr_OutBuf);
static int __ClessSample_Parameters_ReadParamFile(TLV_TREE_NODE * p_node, char *pc_x_DirFile, unsigned int i_x_ParamFileType);
static int __ClessSample_Parameters_CreateDisk (void);
static int __ClessSample_Parameters_IsTagAlreadyInTLVTree(TLV_TREE_NODE pTree, unsigned long ulTag, unsigned int nAction);;
static int __ClessSample_Parameters_CopyParameters( const TLV_TREE_NODE hDestTree, const TLV_TREE_NODE hSrcTree, int nParametersType);
static int __ClessSample_Parameters_SetAIDParametersInFinalStruct(TLV_TREE_NODE pnode);
static int __ClessSample_Parameters_EncodeTLVTreeInShareBuf(int nNbAID);
static int __ClessSample_Parameters_AddTLVTreeInShareBuf (int nNumAID);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief This function converts an hexa buffer given as input parameter 
//! to its ascii values.
//! \param[in] str buffer to convert (hexa format).
//! \param[out] dest buffer in ascii format.
//! \return
//! - 0 if successfull.
//! - -1 otherwise.

static int __ClessSample_Parameters_HexToAscii (char * ac_x_hexbuf, int i_x_hexbuflg, char * ac_x_asciibuf)
{
	unsigned int i_l_Index;
	unsigned char value;

	for (i_l_Index = 0; i_l_Index<(unsigned int)i_x_hexbuflg; i_l_Index++)
	{
		value = ac_x_hexbuf[i_l_Index] >> 4;
		value &= 0x0f;
		if (value <= 9)
			ac_x_asciibuf[2*i_l_Index] = value + 0x30;
		else
			ac_x_asciibuf[2*i_l_Index] = value + 0x37;

		value = ac_x_hexbuf[i_l_Index] & 0x0f;
		if (value <= 9)
			ac_x_asciibuf[2*i_l_Index+1] = value + 0x30;
		else
			ac_x_asciibuf[2*i_l_Index+1] = value + 0x37;
	}
	// String end
	ac_x_asciibuf[2*i_l_Index] = 0;
	return 1;
}



//! \brief This function builds a list of value with tags given as parameter.
//! \param[in] pTree TLVTree to go throw to find tag values.
//! \param[out] pc_x_buffer : buffer to update with tag value.
//! \param[in,out] pi_x_Index : index on pc_x_buffer.
//! \param[in] ps_x_ListPointer : tag list (Struct_TagList format).
//! \param[in] i_x_NbTag : number of tags in list.

static void __ClessSample_Parameters_BuildListValue(TLV_TREE_NODE * pTree, char * pc_x_buffer, int * pi_x_Index, Struct_TagList * ps_x_ListPointer, int i_x_NbTag)
{
	unsigned int    ListIndex;
	unsigned int    CarIndex;
	ParameterElement data;

	for (ListIndex=0; (unsigned int)ListIndex<(unsigned int)i_x_NbTag; ListIndex++)
	{
		if (__ClessSample_Parameters_ReadParameter(pTree, 0, ps_x_ListPointer[ListIndex].tag, &data))
			switch (ps_x_ListPointer[ListIndex].tagtype)
		{
			case C_TAG_TYPE_HEXA_BYTE:
				pc_x_buffer[(*pi_x_Index)++] = *(data.ptValue);
				break;

			case C_TAG_TYPE_BUF_BYTE:
				memcpy(&pc_x_buffer[(*pi_x_Index)], data.ptValue, data.length);
				(*pi_x_Index) += data.length;
				break;

			case C_TAG_TYPE_BUF_BYTE_WITH_MASQ:
				for (CarIndex = 0; CarIndex<data.length; CarIndex++)
				{
					pc_x_buffer[(*pi_x_Index) + CarIndex] = data.ptValue[CarIndex] & ps_x_ListPointer[ListIndex].Masq[CarIndex];
				}
				(*pi_x_Index) += data.length;
				break;

			case C_TAG_TYPE_BOOLEAN:
				pc_x_buffer[(*pi_x_Index)++] = *(data.ptValue);
				break;

			case C_TAG_TYPE_TXT:
			default:
				// Not managed
				break;
		}
	}
}



//! \brief This function reads tag informations in a TLVTree.
//! \param[in] pTree to go throw to found tag informations.
//! \param[in] nIndex for multi-value of a same tag.
//! \param[in] tag to look for.
//! \param[out] data informations on tag.
//! \return
//! - 0 if successfull.
//! - -1 otherwise.

static int __ClessSample_Parameters_ReadParameter(TLV_TREE_NODE * pTree, unsigned int nIndex, unsigned long tag, ParameterElement *data)
{
	int           Result = 0;
	TLV_TREE_NODE pNode;
	static unsigned char BoolValue;

	// Initialization
	data->tag=0;
	data->length=0;
	data->ptValue = NULL;

	// Look for the tag in the pTree TLVTree
	pNode = TlvTree_Find(*pTree, tag, nIndex);

	// If a tag was found
	if (pNode != NULL)
	{
		data->tag     = tag;
		data->length  = TlvTree_GetLength(pNode);
		data->ptValue = (unsigned char*)TlvTree_GetData(pNode);

		// If the parameter has the "YES" or "NO" value
		if (__ClessSample_Parameters_SetBooleanValue(data->ptValue, &BoolValue) == TRUE)
		{
			/*data->tag=tag; no modification */
			data->length = 1;
			data->ptValue = &BoolValue;
		}
		Result = 1;
	}

	return (Result);
}



//! \brief This function sets the boolean given as output parameter according 
//! to the value of input parameter 'value': 
//! - if value equals NO pBool is set to 0.
//! - if value equals YES pBool is set to 1.
//! - for other values of value pBool is set to 0.
//! \param[in] value : string to test.
//! \param[out] pBool : boolean to set.
//! \return
//! - \ref TRUE if value equals YES or NO.
//! - \ref FALSE otherwise.

static int __ClessSample_Parameters_SetBooleanValue (unsigned char *value, unsigned char *pBool)
{
	int iRet;

	iRet = TRUE;
	if (strcmp((char*)value, NO) == 0)
	{
		*pBool = 0;
	}
	else
	{
		// YES
		if (strcmp((char*)value, YES) == 0)
		{
			*pBool = 1;
		}
		// ERROR
		else
		{
			*pBool = 0;
			iRet = FALSE;
		}
	}
	return (iRet);
}



//! \brief This function reads an array (XML format) and extract tags and value to build a TLVTree. 
//! \param[in] ptr_ac_x_ParamTable array with parameters with XML format.
//! \param[in] i_x_ArraySize array number of elements.
//! \param[out] pBool : boolean to set.
//! \return TLVTree updated with parameters.

static TLV_TREE_NODE __ClessSample_Parameters_ReadArray(const unsigned char *ptr_ac_x_ParamTable, unsigned int i_x_ArraySize)
{
	TLV_TREE_NODE  pTree = 0;
	int s;

	s = TlvTree_Unserialize(&pTree, TLV_TREE_SERIALIZER_XML, ptr_ac_x_ParamTable, i_x_ArraySize );

	if (s != 0)
	{
		upload_diagnostic_txt((unsigned char *)"PB on xml parameters !!!\n");
		GTL_Traces_TraceDebug ("__ClessSample_Parameters_ReadArray : PB on xml parameters !!!");
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

static int __ClessSample_Parameters_FileRead(TLV_TREE_NODE * pTree, char *pc_x_DirFile, char *pc_x_fileName)
{
	char ac_l_OutBuf[80];
	char LabelDiskName[DISK_NAME_SIZE];
	int nResult = 0;

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__ClessSample_Parameters_Get_Disk_Name(LabelDiskName);

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

		if (__ClessSample_Parameters_ReadParamFile(pTree, pc_x_DirFile, FileTypeAccess) != 0)
		{
			GTL_Traces_TraceDebug ("__ClessSample_Parameters_ReadParamFile() error");
			nResult = 1;
		}
		//ClessSample_Parameters_TlvTree_Display(pTree, "Read param.par");
	}
	return (nResult);
}



//! \brief This function update a file with parameters given in a TLVTree.
//! File is updated in TLVTree serial binary format.
//! \param[in] pTree to go save in file.
//! \param[in] ptr_OutBuf file path and name to update.
//! \return
//! - 0 if ok, 1 else.

static int __ClessSample_Parameters_WriteBinFile(TLV_TREE_NODE pTree, char * ptr_OutBuf)
{
	unsigned char * ac_l_pucBuffer = NULL;
	unsigned int  result = 0;
	int           i_l_Size;
	S_FS_FILE     *ptr_file;

	// Input parameters checking
	if ((strlen(ptr_OutBuf) == 0) || (pTree == 0))
	{
		return 1;
	}

	// Check size
	i_l_Size = TlvTree_GetSerializationSize(pTree, TLV_TREE_SERIALIZER_DEFAULT);

	if (i_l_Size>C_PUC_MAX_BUFFER_SIZE) // If file size greater than max size
	{
		GTL_Traces_TraceDebug ("__ClessSample_Parameters_WriteBinFile : Parameter node size too important");
		result = 1;
	}
	else
	{
		ac_l_pucBuffer = (unsigned char *) umalloc(i_l_Size + 10);
		i_l_Size = TlvTree_Serialize( pTree, TLV_TREE_SERIALIZER_DEFAULT, ac_l_pucBuffer, i_l_Size + 10);

		// The buffer is saved in a file
		if ((i_l_Size < 0) || (i_l_Size > C_PUC_MAX_BUFFER_SIZE)) // If serialization pb
		{
			GTL_Traces_TraceDebug ("__ClessSample_Parameters_WriteBinFile : Parameter node serialisation pb");
			result = 1;
		}
	}

	if (result == 0)	// If ok
	{
		unsigned int Mode,rc;
		int ret;

		ret = __ClessSample_Parameters_CreateDisk();
		if (ret == FS_OK)
		{
			ret = FS_exist (ptr_OutBuf);

			if (ret == FS_OK)
			{
				GTL_Traces_TraceDebug ("__ClessSample_Parameters_WriteBinFile : FILE EXIST");
				// The former file is suppressed. 
				ret = FS_unlink (ptr_OutBuf);
			}
		}

		Mode = FS_WRTMOD;
		rc = FS_mount(ptr_OutBuf, &Mode);
		if (rc != FS_OK)
		{
			upload_diagnostic_txt((unsigned char *)"PB Mount COM File param\n");
			result = 1;
		} 

		ptr_file = FS_open (ptr_OutBuf, "a");
		if (ptr_file == NULL)
		{
			result = 1;
			upload_diagnostic_txt ((unsigned char*)"Error create file\n");
		}
	}

	if (result == 0)	// If ok
	{
		FS_write (ac_l_pucBuffer, 1, i_l_Size, ptr_file);
		FS_close(ptr_file);	// Close file
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

static int __ClessSample_Parameters_ReadParamFile(TLV_TREE_NODE * p_node, char *pc_x_DirFile, unsigned int i_x_ParamFileType)
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
		upload_diagnostic_txt((unsigned char *)"PB Mount COM Filen\n");
	}
	ptr_file = FS_open(pc_x_DirFile, "r");

	if (ptr_file != NULL)
	{
		int s;
		unsigned long ulFileLength;

		ulFileLength = FS_length (ptr_file);
		
		if (ulFileLength>C_PUC_MAX_BUFFER_SIZE) // If file size greater than max size
		{
			GTL_Traces_TraceDebug ("__ClessSample_Parameters_ReadParamFile : Parameter file size too important !!!");
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
				// Reset of this node, a problem occurred
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

static void __ClessSample_Parameters_Get_Disk_Name(char* ptDiskName)
{
	sprintf(gs_Label_Disk_Name,"%s%02x", LABEL_DISK, 0);
	memcpy(ptDiskName, gs_Label_Disk_Name, sizeof(gs_Label_Disk_Name));
}



//! \brief This function create give disk to store parameters. 
//! \return
//! FS_OK if disk created, other else.

static int __ClessSample_Parameters_CreateDisk (void)
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



//! \brief This function check if tag if allready in destination TLVTree.
//! If tag is allready present => no action or delete it 
//! \param[in] pTree TLVTree with parameters set 
//! \param[in] ulTag tag to check in structure
//! \param[in] nAction, C_PARAMS_NO_ACTION (no ation) or C_PARAMS_DELETE (suppress it)
//! \return 1 if Tag is already present, 0 else

static int __ClessSample_Parameters_IsTagAlreadyInTLVTree(TLV_TREE_NODE pTree, unsigned long ulTag, unsigned int nAction)
{
	int	nIndex, nFound;
	TLV_TREE_NODE pNode;

	if ((pTree == NULL) || (ulTag == 0))
		return (0); // A problem occurs, input parameters are empty ! Nothing could be made

	nIndex = 0;
	nFound = 0;

	pNode = TlvTree_Find(pTree, (unsigned int) ulTag, nIndex++);
	do{
		if (pNode) // If something found
		{
			nFound = 1; // Super we found it !!!
			if (nAction == C_PARAMS_NO_ACTION)	// If no action is asked on each tag found
				break;	// We can stop treatment

			if (nAction == C_PARAMS_DELETE)		// If a delete action has been asked
			{
				TlvTree_Release(pNode);			// Disapeared !
			}

			pNode = TlvTree_Find(pTree, (unsigned int) ulTag, nIndex++);
		}
	}while (pNode != 0);

	return (nFound);
}



//! \brief This function copies all parameters under hSrcTree TLVTree in the hDestTree TLVTree 
//! \param[in] hSrcTree TLVTree node with parameters to copies.
//! \param[in] hDescTree TLVTree node with parameters to update.
//! \param[in] nParametersType allows to specify if parameters to add are prioritary, exclusive or not. 
//! return 0 if copied has been correctly executed, 1 else.

static int __ClessSample_Parameters_CopyParameters (const TLV_TREE_NODE hDestTree, const TLV_TREE_NODE hSrcTree, int nParametersType)
{
	unsigned int nResult = 0;
	int nTLVResult;
	TLV_TREE_NODE pResearch;
	int nCopyCanBeMade;
	unsigned int nTag;
	TLV_TREE_NODE pTmpNode;
	
	if ((hDestTree == NULL) || (hSrcTree == NULL))
	{
		nResult = 1;
		return (nResult);
	}

	// Init local data
	pTmpNode = NULL;
	
	// For each tag found in Src TLVTree
	pResearch = TlvTree_GetFirstChild(hSrcTree);
	
	do
	{
		if (pResearch != 0)
		{
			// Node has been found
			nTag = TlvTree_GetTag(pResearch); // What tag is managed
			
			switch (nParametersType)
			{
			case C_PRIORITY_PARAMS:
				__ClessSample_Parameters_IsTagAlreadyInTLVTree(hDestTree, nTag, C_PARAMS_DELETE); // If tag is already present => delete it
				nCopyCanBeMade = 1; // Copy can be made ...
				break;
				
			case C_UNPRIORITY_PARAMS:
				if (__ClessSample_Parameters_IsTagAlreadyInTLVTree(hDestTree, nTag, C_PARAMS_NO_ACTION) != 0) // If tag is already present => we keep it
					nCopyCanBeMade = 0; // Copy cannot be made ...
				else
					nCopyCanBeMade = 1; // Tag isn't already present, we can copy it 
				break;
				
			case C_MULTI_PARAMS: // No action, just a copy is necessary
			default:
				nCopyCanBeMade = 1; // Copy can be made ...
				break;
			}
			
			if (nCopyCanBeMade) // If copy can be made (no problem of multi same tags)
			{
				// Copy it in destination pNode
				pTmpNode = TlvTree_Copy(pResearch);
				nTLVResult = TlvTree_Graft(hDestTree, pTmpNode);
			}
			else
			{
				nTLVResult = TLV_TREE_OK; // To allow to continue
			}

			if (nTLVResult == TLV_TREE_OK)
				pResearch = TlvTree_GetNext(pResearch);
			else
			{
				nResult = 1;// A problem occurs
				pResearch = NULL; // To stop process
				GTL_Traces_TraceDebug ("__ClessSample_Parameters_CopyParameters : Unable to add tag in dest TLVTree");
			}
		} // End (if pResearch != 0)
	}while (pResearch != 0);
	
	return (nResult);
}



//! \brief This function add AID parameters in global gs_Parameter_AID[] structure.
//! \param[in] pnode parameters node for the kernel.
//! \return number of AID found in input parameters.

static int __ClessSample_Parameters_SetAIDParametersInFinalStruct(TLV_TREE_NODE pnode)
{
	unsigned int nNbAID;
	int	nIndex;
	TLV_TREE_NODE pChild;
	TLV_TREE_NODE pAIDParams, pResearch;			// Node for AID parameters.


	// Found main AID nodes in TLVTree given in parameters
	nNbAID = 0;
	nIndex = 0;

	// Look for the main AID tag in the pTree TLVTree
	pAIDParams = TlvTree_Find(pnode, C_PARAM_AID_TAG, nIndex);

	if (pAIDParams == 0) // No AID information found
		return(nNbAID);
		
	// For each AID found in parameters
	pChild = TlvTree_GetFirstChild(pAIDParams);
	
	// Loop on each parameters set
	while ((pChild != 0) && (nNbAID < C_NUMBER_AID_MAX)) // Loop on each child
	{
		//nIndex = 0;
		
		// Create a tree containing the AID data
		gs_Parameter_AID[nNbAID].pTreeAID = TlvTree_New(C_TAG_MAIN);
		
		pResearch = TlvTree_Find (pChild, TAG_EMV_AID_TERMINAL, 0); // If AID informations have been found
		
		if (pResearch != 0) // If AID informations have been found
		{
			if (__ClessSample_Parameters_CopyParameters(gs_Parameter_AID[nNbAID].pTreeAID, pChild, C_MULTI_PARAMS) != 0)
			{
				GTL_Traces_TraceDebug ("__ClessSample_Parameters_SetAIDParametersInFinalStruct : Unable to add tag in AID parameters");
			}
			else
			{
				// Put index reference in AID informations structure
				gs_Parameter_AID[nNbAID].nAIDLength = TlvTree_GetLength(pResearch);
				memcpy (gs_Parameter_AID[nNbAID].ucAID, TlvTree_GetData(pResearch), TlvTree_GetLength(pResearch));
				
				// Store the index
				gs_Parameter_AID[nNbAID].ucAIDIndex = nNbAID;
				
				// Delete AID informations from destination TLVTree
				//nIndex = 0;
				pResearch = TlvTree_Find(gs_Parameter_AID[nNbAID].pTreeAID, TAG_EMV_AID_TERMINAL, 0);
				if (pResearch)
					TlvTree_Release(pResearch);
			}
		}
		
		nNbAID ++; // Increase the number of supported AID
		pChild = TlvTree_GetNext(pChild); // Next AID (next child)
	} // End loop on each AID parameters

	return (nNbAID);
}



//! \brief This function add Krevok parameters in global gs_Parameter_AID[] structure.
//! \param[in] nNbAID Number of available AID.
//! \param[in] pnode parameters node for the kernel.

static void __ClessSample_Parameters_SetKRevokParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID)
{
	unsigned int nIndex, nIndexAID;
	TLV_TREE_NODE pKRevokParams;		// Node for KRevok parameters.
	
	nIndex = 0;
	nIndexAID = 0;

	// Found global parameters
	pKRevokParams = TlvTree_Find (pnode, C_PARAM_KREVOK_TAG, nIndex);
	
	// Set global parameters in AID TLVTree
	if (pKRevokParams != NULL) // If KRevok parameters found
	{
		// Loop on each AID
		for (nIndexAID = 0; nIndexAID<(unsigned int)nNbAID; nIndexAID++)
		{
			if (__ClessSample_Parameters_CopyParameters(gs_Parameter_AID[nIndex].pTreeAID, pKRevokParams, C_MULTI_PARAMS) != 0)
			{
				GTL_Traces_TraceDebug ("__ClessSample_Parameters_SetKRevokParametersInFinalStruct: Pb copy Krevok parameters");
			}
		}
	}
}



//! \brief This function add kernel parameters in global gs_Parameter_AID[] structure.
//! \param[in] nNbAID Number of available AID.
//! \param[in] pnode parameters node for the kernel.

static void __ClessSample_Parameters_SetKernelParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID)
{
	unsigned char * pucTagPtr;
	int nTagLentgth;
	unsigned int nIndex, nIndexAID;
	TLV_TREE_NODE pKernelParams;		// Node for global parameters.
	TLV_TREE_NODE pResearch;			// Node for research.
	TLV_TREE_NODE pNode;

	nIndex = 0;
	nIndexAID = 0;

	// Found global parameters
	pKernelParams = TlvTree_Find (pnode, C_PARAM_KERNEL_TAG, nIndex);
	
	// Set global parameters in AID TLVTree
	if (pKernelParams != NULL) // If Kernel parameters found
	{
		// Loop on each AID
		for (nIndexAID = 0; nIndexAID<(unsigned int)nNbAID; nIndexAID++)
		{
			// Found kernel parameters to use
			//nIndex = 0;
			pResearch = TlvTree_Find(gs_Parameter_AID[nIndexAID].pTreeAID, TAG_EP_KERNEL_TO_USE, 0);
			
			if (pResearch) // If kernel to use has been found
			{
				// Store kernel parameters.
				if (ClessSample_Parameters_AddParametersInNode(gs_Parameter_AID[nIndexAID].pTreeAID, pnode, C_PARAM_KERNEL_TAG, TAG_EP_KERNEL_TO_USE, TlvTree_GetLength(pResearch), TlvTree_GetData(pResearch), C_UNPRIORITY_PARAMS) != 0)
				{
					GTL_Traces_TraceDebug ("__ClessSample_Parameters_SetKernelParametersInFinalStruct: Pb kernel parameters copy");
				}
			}
		}

		nIndex = 0;
		pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SAMPLE_GENERIC_MONEY_EXTENDED, nIndex++);

		if (pNode) // If something found
		{
			nNbMoneyExtended = 0; // Reset for update it
			if (ptr_money_extended)
				ufree(ptr_money_extended);
			ptr_money_extended = NULL;
		}
		
		do{
			if (pNode) // If something found
			{
				// Add informations in ptr_money_extended array
				nNbMoneyExtended++;

				pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SAMPLE_GENERIC_MONEY_EXTENDED, nIndex++);
			}
		}while (pNode != 0);
		
		nIndex = 0;
		if (nNbMoneyExtended)
		{
			ptr_money_extended = umalloc(nNbMoneyExtended * sizeof(S_MONEY_EXTENDED));
			pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SAMPLE_GENERIC_MONEY_EXTENDED, nIndex++);
	
			do{
				if (pNode) // If something found
				{
					nTagLentgth = TlvTree_GetLength(pNode);
					pucTagPtr = TlvTree_GetData(pNode);
				}
				
				if (pNode) // If something found
				{
					memset(&ptr_money_extended[nIndex-1], 0, sizeof(S_MONEY_EXTENDED)); 		// Reset structure
					if (nTagLentgth >= 10)														// If something found
					{
						memcpy(ptr_money_extended[nIndex-1].currency.nom, pucTagPtr, 3); 		// Nom copy, 3 bytes
						memcpy(ptr_money_extended[nIndex-1].currency.code, pucTagPtr + 3, 3); 	// Code copy, 3 bytes
						ptr_money_extended[nIndex-1].currency.posdec = pucTagPtr[6] - 0x30;		// Decimal position in the amount  
		
						ptr_money_extended[nIndex-1].infos.cents_separator = pucTagPtr[7];
						ptr_money_extended[nIndex-1].infos.thousands_separator = pucTagPtr[8];
						ptr_money_extended[nIndex-1].infos.currency_position = pucTagPtr[9] - 0x30;
					}
					pNode = TlvTree_Find(pKernelParams, (unsigned int) TAG_SAMPLE_GENERIC_MONEY_EXTENDED, nIndex++);
				}
			}while (pNode != 0);
		}
	}
}



//! \brief This function give Extended money structure initialized with parameters.
//! \param[in/out] n_x_NbMoney Number of money managed.
//! \param[in/out] ps_x_Money pnode parameters node for the kernel.

void ClessSample_Parameters_GetMoneyExtended(int * n_x_NbMoney, S_MONEY_EXTENDED ** ps_x_Money)
{
	*n_x_NbMoney = nNbMoneyExtended;
	*ps_x_Money  = ptr_money_extended;
}



//! \brief This function add global parameters in global gs_Parameter_AID[] structure.
//! \param[in] nNbAID.
//! \param[in] pnode parameters node for the kernel.

static void __ClessSample_Parameters_SetGlobalParametersInFinalStruct(TLV_TREE_NODE pnode, int nNbAID)
{
	TLV_TREE_NODE pGlobalParams;		// Node for global parameters.
	unsigned int nIndex;
	
	nIndex = 0;
	
	// Found global parameters
	nIndex = 0;
	pGlobalParams = TlvTree_Find(pnode, C_PARAM_GLOBAL_TAG, nIndex);
	
	// Set global parameters in AID TLVTree
	if (pGlobalParams) // If global parameters found
	{
		// Loop on each AID
		for (nIndex = 0; nIndex<(unsigned int)nNbAID; nIndex++)
		{
			// Store global parameters.
			if (ClessSample_Parameters_AddParametersInNode(gs_Parameter_AID[nIndex].pTreeAID, pnode, C_PARAM_GLOBAL_TAG, 0, 0, NULL, C_UNPRIORITY_PARAMS) != 0)
			{
				GTL_Traces_TraceDebug ("__ClessSample_Parameters_SetGlobalParametersInFinalStruct : ClessSample_Parameters_BuildAIDNodes : No global parameters found");
			}
		}
	}
}



//! \brief This function add global parameters in global gs_Parameter_AID[] structure.
//! \param[in] nNbAID Number of parametered AID.
//! \param[in] pnode parameters node for the kernel.
//! \return KERNEL_STATUS_OK if no problem, other else.

static int __ClessSample_Parameters_EncodeTLVTreeInShareBuf(int nNbAID)
{
	int nResult = 0;
	int nIndex;
	T_SHARED_DATA_STRUCT* pAidInfo;

	// Loop on each AID set of parameter to manage
	for (nIndex=0; nIndex<nNbAID; nIndex++)
	{
		pAidInfo = GTL_SharedExchange_Init(C_SHARE_BUFFER_SIZE, C_BUFFER_SHARED);
		if (pAidInfo == NULL)
		{
			nResult = 1; // Error
			goto End;
		}
		
		gs_Parameter_AID[nIndex].pSharedAIDParam = pAidInfo; 

		if (__ClessSample_Parameters_AddTLVTreeInShareBuf(nIndex) != 0)
			nResult = 1; // Error
	} // End Loop on each AID set of parameter to manage
	
End :
	return (nResult);
}



//! \brief This function add parameters in global g_Parameter_AID[] structure.
//! \param[in] nNumAID parameter set number.
//! \return
//!		- 0 if no problem
//!		- 1 else.

static int __ClessSample_Parameters_AddTLVTreeInShareBuf (int nNumAID)
{
	int nResult = 0;
	int nResultSharedExchange;
	TLV_TREE_NODE hRootNode, hNode; 
	T_SHARED_DATA_STRUCT* pAidInfo;

	hRootNode = gs_Parameter_AID[nNumAID].pTreeAID;
	pAidInfo = gs_Parameter_AID[nNumAID].pSharedAIDParam; 
	hNode = hRootNode;
			
	// Loop on each tag to add in Share exchange buffer
	do{
		hNode = TlvTree_Iterate(hNode, hRootNode );
		
		if (hNode != 0) // Tag may be added in Shared Buffer
		{
			// Get informations from tag found					
			
			nResultSharedExchange = GTL_SharedExchange_AddTag (pAidInfo, TlvTree_GetTag(hNode), TlvTree_GetLength(hNode), TlvTree_GetData(hNode));
			switch (nResultSharedExchange)
			{
				case STATUS_SHARED_EXCHANGE_OK:
					break;
				case STATUS_SHARED_EXCHANGE_NOT_ENOUGH_SPACE: 
					GTL_Traces_TraceDebug ("__ClessSample_Parameters_EncodeTLVTreeInShareBuf() not enought space");
					nResult = 1; // Error
					break;
				case STATUS_SHARED_EXCHANGE_ERROR:
				default:
					GTL_Traces_TraceDebug ("__ClessSample_Parameters_EncodeTLVTreeInShareBuf() exchange error");
					nResult = 1; // Error
					break;
			}
		}
	}while((hNode != 0) && (nResultSharedExchange == STATUS_SHARED_EXCHANGE_OK)); // End loop on tag to add in Share exchange buffer

	return (nResult);
}



//! \brief This function clear TLVTree used to store parameters. 

void ClessSample_Parameters_InitParameters(TLV_TREE_NODE * pTree)
{
	if (pTree)
		TlvTree_Release(*pTree);
}



//! \brief This function update TLVTree with defaut parameters (read in an array). 

void ClessSample_Parameters_ReadDefaultParameters(TLV_TREE_NODE * pTree)
{
	ClessSample_Parameters_InitParameters (pTree);

	// Default parameters initialisation => set in TLV tree
	*pTree = __ClessSample_Parameters_ReadArray((const unsigned char*)gs_DefaultParam, sizeof(gs_DefaultParam));
}



//! \brief This function update TLVTree with parameters read in a XML text file. 

int ClessSample_Parameters_ReadXMLParamFile (TLV_TREE_NODE * p_node, unsigned int i_x_tag, char *filePath, char *fileName)
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
		GTL_Traces_DiagnosticText("ClessSample_Parameters_ReadXMLParamFile : Cannot mount the file\n");
		result = 1;
		goto End;
	}

	// Open the file
	ptr_file = FS_open (fileName, "r");
	
	if (ptr_file == NULL)
	{
		// Problem with file
		GTL_Traces_DiagnosticText("ClessSample_Parameters_ReadXMLParamFile : FS_open(%s) ko\n", fileName);
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
			GTL_Traces_DiagnosticText("ClessSample_Parameters_ReadXMLParamFile : XML param file size too important\n");
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
			// Reset of this node, a problem occurred
			p_node = 0;
			result = 1;
			GTL_Traces_DiagnosticText("ClessSample_Parameters_ReadXMLParamFile : PB unserialize param file\n");
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



//! \brief This function set TLVTree parameters in a save file. 

int ClessSample_Parameters_SaveParam (TLV_TREE_NODE pTree)
{
	// Local variables déclaration
	// Function result
	int nResult;
	char ac_l_FilePath_L[80];
	char LabelDiskName[DISK_NAME_SIZE];

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__ClessSample_Parameters_Get_Disk_Name(LabelDiskName);

	// Update PARAM.PAR serial binary TLVTree format file
	sprintf(ac_l_FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM_SAV);
	nResult = __ClessSample_Parameters_WriteBinFile(pTree, ac_l_FilePath_L);

	return(nResult);
}



//! \brief This function update TLVTree with parameters read in a save file. 

int ClessSample_Parameters_RestoreParam (TLV_TREE_NODE * pTree)
{
	char FilePath_L[80];
	int ret = FS_OK;
	char LabelDiskName[DISK_NAME_SIZE];
	int nResult;
	unsigned int Mode,rc;

	memclr(FilePath_L,sizeof(FilePath_L));

	memclr(LabelDiskName, sizeof(LabelDiskName));
	__ClessSample_Parameters_Get_Disk_Name(LabelDiskName);

	Mode = FS_WRTMOD;
	sprintf(FilePath_L, "/%s", LabelDiskName);
	rc = FS_mount(FilePath_L, &Mode);
	if (rc != FS_OK)
	{
		upload_diagnostic_txt((unsigned char *)"PB Mount COM File param\n");
		nResult = 1;
	}
	else
	{
		
		sprintf(FilePath_L, "/%s/%s", LabelDiskName, C_FILE_PARAM_SAV);
		// Set path in input buffer for BuildParameters() call
		ret = FS_exist (FilePath_L);
		
		if (ret == FS_OK)
		{
			GTL_Traces_TraceDebug("ClessSample_Parameters_RestoreParam : Load %s file", C_FILE_PARAM_SAV);
			// Load parameter file in the terminal
			nResult = __ClessSample_Parameters_FileRead (pTree, FilePath_L, C_FILE_PARAM_SAV);
		}
		else
		{
			GTL_Traces_TraceDebug("ClessSample_Parameters_RestoreParam : %s file not existing", C_FILE_PARAM_SAV);
			nResult = 1;
		}
	}
	
	return (nResult);
}



//! \brief This function compute a CRC allowing to check parameters loaded.
//! The CRC is computed on a list of a fix list of tags.

int ClessSample_Parameters_Compute_Config_CRC(TLV_TREE_NODE * pTree, int * nCRCLength, unsigned char ** pSha)
{
	unsigned char   buffer[370];
	unsigned int    i;

	i = 0;
	memset (buffer, 0, sizeof (buffer));

	// Buffer build
	__ClessSample_Parameters_BuildListValue(pTree, (char*)buffer, (int*)&i, (Struct_TagList *)CrcTagList, sizeof(CrcTagList) / sizeof(Struct_TagList));

	*pSha = (unsigned char*)GTL_SHA_Sha1Compute ((unsigned char*)buffer, i);

	*nCRCLength = 20;

	return TRUE;
}



//! \brief This function allows to trace TLV tree given as parameter on trace tool

void ClessSample_Parameters_TlvTree_Display(TLV_TREE_NODE pTree , char * txt)
{
	// #define DETAIL

	// trace when simulating on target
	TLV_TREE_NODE pNode;
	char TmpBuf[100];
#ifdef DETAIL
	unsigned char * ptr_car;
	unsigned int index;
#endif // DETAIL


	pNode = pTree;

	GTL_Traces_TraceDebug("\nClessSample_Parameters_TlvTree_Display:\n %s", txt);

	while( pNode != NULL )
	{
		sprintf(TmpBuf, "- %08x [- %08x]: (%d/%d)   ", TlvTree_GetTag(pNode), (int)(TlvTree_GetParent(pNode) ? TlvTree_GetParent(pNode) : 0 ),
			(int)TlvTree_GetData(pNode), (int)TlvTree_GetLength(pNode)); 
		GTL_Traces_TraceDebug(TmpBuf);

#ifdef DETAIL
		ptr_car = (unsigned char*)TlvTree_GetData(pNode);
		for (index=0; ((index<(TlvTree_GetLength(pNode))) && (index<30)); index++)
		{
			sprintf(&TmpBuf[index*3], "%2x ", *ptr_car++);
		}
		GTL_Traces_TraceDebug(TmpBuf);
#endif // DETAIL

		pNode = TlvTree_Iterate( pNode,  pTree );
	} 
}



//! \brief This function trace parameters store in a TLVTree.
//! \brief Trace may be made on printer, USB, ... 

void ClessSample_Parameters_Trace_Param_Supported(TLV_TREE_NODE pnode, unsigned char ucOutputType, char *ptr_x_DataName, unsigned char c_x_tracetype, unsigned long ul_x_tag)
{
	unsigned long lLocalTag;
	unsigned int nLocalLen;
    char text[1024];
    char partialtext[130];
    char * PtrText;
	char * ptr_data;
	TLV_TREE_NODE hnode;
	TLV_TREE_NODE pNode;
	unsigned char ucSavedOutputDevice;

	// Save default output device
	ucSavedOutputDevice = ClessSample_DumpData_DumpGetOutputId ();

	ClessSample_DumpData_DumpSetOutputId(ucOutputType); 			// Output on printer/USB...

	if (ClessSample_DumpData_DumpOpenOutputDriver() == FALSE)	// Open Driver
	{
		// Restore default output device
		ClessSample_DumpData_DumpSetOutputId (ucSavedOutputDevice);
		return; // A problem occurs
	}
	
	hnode = pnode;

	ClessSample_DumpData("%s", ptr_x_DataName);

	// If main Mark has been found
	if (hnode == NULL)
		goto End; // A problem occurs, dump data driver shall be closed
	
	// Display all the nodes and children under the mark given
	pNode = hnode;

	pNode = TlvTree_Iterate(pNode, hnode);

	while( pNode != NULL )
	{   
		lLocalTag = TlvTree_GetTag(pNode);
		nLocalLen = TlvTree_GetLength(pNode);
		ptr_data = (char *)TlvTree_GetData(pNode);

		switch (c_x_tracetype)
		{
			case C_TRACE_ONE_TAG :
				if (TlvTree_GetTag(pNode) != ul_x_tag)
					break;

			case C_TRACE_ALL_CHILD:
			{
				ClessSample_DumpData("T:%lx L:%x V:", lLocalTag, nLocalLen);

				memset (text, '\0', sizeof(text));
				__ClessSample_Parameters_HexToAscii (ptr_data, nLocalLen, text);

				if (strlen (text) > 120)
				{
					PtrText = text;
					do{
						strncpy(partialtext, PtrText, 120); // warning, strncpy doesn't copy string end if maximun length is reached
						partialtext[120] = 0; // Protection against overflow
						PtrText += 120;
						ClessSample_DumpData("%s\n", partialtext);
					}while(strlen(partialtext) == 120);
				}
				else
					ClessSample_DumpData("%s", text);
					
				break;
			}

			default: // No treatment
				break;

		}
		pNode = TlvTree_Iterate(pNode, hnode);
	} // End while on Node

	ClessSample_DumpData_DumpNewLine();							// CR

End:
	ClessSample_DumpData_DumpCloseOutputDriver();				// close Output Driver

	// Restore default output device
	ClessSample_DumpData_DumpSetOutputId (ucSavedOutputDevice);
}



//! \brief This function trace CRC of a predefine list of tag of a TLVTree.

void ClessSample_Parameters_Trace_CRC(TLV_TREE_NODE pnode, unsigned char ucOutputType, char *ptr_x_DataName)
{
	int nCRCLength, nIndex;
	unsigned char * pSha;
	char ucStr[370];
	char ucTmpStr[10];
	unsigned char ucSavedOutputDevice;

	// Save default output device
	ucSavedOutputDevice = ClessSample_DumpData_DumpGetOutputId();

	ClessSample_DumpData_DumpSetOutputId(ucOutputType); 			// Output on printer/USB...
	if (ClessSample_DumpData_DumpOpenOutputDriver() == FALSE)	// Open Driver
	{
		// Restore default output device
		ClessSample_DumpData_DumpSetOutputId(ucSavedOutputDevice);
		return; // A problem occurs
	}

	ClessSample_DumpData("%s", ptr_x_DataName);
	
	ClessSample_Parameters_Compute_Config_CRC(&pnode, &nCRCLength, &pSha);
	sprintf(ucStr, "CRC loaded file : ");
	for (nIndex=0; nIndex<nCRCLength; nIndex++)
	{
		sprintf(ucTmpStr, "%02x", pSha[nIndex]);
		strcat(ucStr, ucTmpStr);
	}
	ClessSample_DumpData("%s", ucStr);
	
	ClessSample_DumpData_DumpNewLine();							// CR
	ClessSample_DumpData_DumpCloseOutputDriver();				// close Output Driver

	// Restore default output device
	ClessSample_DumpData_DumpSetOutputId(ucSavedOutputDevice);
}



//! \brief This function select TLVTree of parameters in relationchip with Index AID.

int ClessSample_Parameters_GiveAIDNumber(void)
{
	return (gs_nNbParameterSet);
}



//! \brief This function Send AID of parameters store.

unsigned char * ClessSample_Parameters_GiveAID(unsigned int n_x_AIDIndex, int * pAIDLength)
{
	unsigned char * pAID = NULL;
	
	*pAIDLength = 0;
	
	if (n_x_AIDIndex >= (unsigned int)gs_nNbParameterSet) // If index greater than number of parameter set
	{
		GTL_Traces_TraceDebug("ClessSample_Parameters_GiveAID : Bad index");
		goto End;
	}
	
	pAID = gs_Parameter_AID[n_x_AIDIndex].ucAID;
	*pAIDLength	= gs_Parameter_AID[n_x_AIDIndex].nAIDLength;
		
End:
	return (pAID);
}



//! \brief This function select TLVTree of parameters in relationchip with Index AID.

TLV_TREE_NODE ClessSample_Parameters_GiveAIDTLVTtree(unsigned int n_x_AIDIndex)
{
	if (n_x_AIDIndex >= (unsigned int)gs_nNbParameterSet) // If index greater than number of parameter set
	{
		GTL_Traces_TraceDebug("ClessSample_Parameters_GiveAIDTLVTtree : Bad index");
		return (NULL);
	}
	
	return (gs_Parameter_AID[n_x_AIDIndex].pTreeAID);
}



//! \brief This function select shared buffer of parameters to use with Index AID.

T_SHARED_DATA_STRUCT * ClessSample_Parameters_GiveAIDShareBuffer(unsigned int n_x_AIDIndex)
{
	if (n_x_AIDIndex >= (unsigned int)gs_nNbParameterSet) // If index greater than number of parameter set
	{
		GTL_Traces_TraceDebug("ClessSample_Parameters_GiveAIDShareBuffer : Bad index");
		return (NULL);
	}
	
	return (gs_Parameter_AID[n_x_AIDIndex].pSharedAIDParam);
}



//! \brief This function found subset parameters and select parameters set to store in MainNode.

int ClessSample_Parameters_AddParametersInNode(TLV_TREE_NODE pMainNode, TLV_TREE_NODE pParameterNode, unsigned long ulSubsetTag, unsigned long ulTag, int nTagLength, unsigned char * ucTagValue, int nParametersType)
{
	int nResult = 0; // No problem = Default result
	//  Find main tag in input parameters node
	int	nIndex = 0;
	int nFound = 0;
	TLV_TREE_NODE pNode, pChild, pResearch;

	if ((pMainNode == NULL) || (pParameterNode == NULL) || (ulSubsetTag == 0))
	{
		GTL_Traces_TraceDebug ("ClessSample_Parameters_AddParametersInNode : Invalid input parameter");
		nResult = 1; // A problem occurs, input parameters are empty !
		goto End;
	}

	// Look for the tag in the pTree TLVTree
	pNode = TlvTree_Find(pParameterNode, ulSubsetTag, 0);

	// If a tag was found
	if (pNode != NULL) // If subset has been found
	{
		pChild = TlvTree_GetFirstChild(pNode);
		
		// Loop on each parameters set
		while((pChild != 0) && (!nFound))
		{
			nIndex = 0;
			
			if (ulTag == 0) // If no tag is specified, first set of parameters will be taken.
			{
				nFound = TRUE;
			}
			else // A tag is specified : we have to look for the tag with appropriate value.
			{
				do{
					pResearch = TlvTree_Find(pChild, ulTag, nIndex++);
					
					if (pResearch != 0)
					{
						// Check if tag found is same as we want 					
						if (((unsigned long)TlvTree_GetTag(pResearch) == ulTag) && (TlvTree_GetLength(pResearch) == (unsigned long)nTagLength) && (memcmp(TlvTree_GetData(pResearch), ucTagValue, nTagLength) == 0))
							nFound = TRUE;					 
					}
				}while ((pResearch != NULL) && (!nFound));
			}
			
			if (!nFound)
			{
				pChild = TlvTree_GetNext(pChild); // Next Child
			}
		}
		
		if (nFound) // If specific tag has been found, all parameters in pChild set may be copied in pMainNode main Node parameter set
		{
			if (__ClessSample_Parameters_CopyParameters(pMainNode, pChild, nParametersType) != 0)
			{
				GTL_Traces_TraceDebug ("ClessSample_Parameters_AddParametersInNode : __ClessSample_Parameters_CopyParameters error");
				nResult = 1;// A problem occurs
				goto End;
			}
		}
	}
End:
	return (nResult);
}



//! \brief This function organises TLVTree nodes with parameters used for AID selection.

void ClessSample_Parameters_BuildAIDNodes(TLV_TREE_NODE pnode)
{
	int nIndex;

	// Init structures
	for (nIndex = 0; nIndex < gs_nNbParameterSet; nIndex++)
	{
		if (gs_Parameter_AID[nIndex].pTreeAID != NULL)
		{
			TlvTree_Release(gs_Parameter_AID[nIndex].pTreeAID);
			gs_Parameter_AID[nIndex].pTreeAID = NULL;
		}

		if (gs_Parameter_AID[nIndex].pSharedAIDParam != NULL)
			GTL_SharedExchange_DestroyShare (gs_Parameter_AID[nIndex].pSharedAIDParam);
	}

	// Init structures
	memset(gs_Parameter_AID, 0, sizeof(T_PARAMETER_AID) * C_NUMBER_AID_MAX);
	gs_nNbParameterSet = 0;

	// Add AID parameters in final global Structure
	gs_nNbParameterSet = __ClessSample_Parameters_SetAIDParametersInFinalStruct(pnode);

	if (gs_nNbParameterSet == 0)
	{
		GTL_Traces_TraceDebug("ClessSample_Parameters_BuildAIDNodes : No avaibale AID");
		return; // No AID found ...
	}

	// Here, gs_Parameter_AID[] is initialised with AID parameters, AID value (and length) and AID index    

	// Add kernel parameters in final global Structure
	__ClessSample_Parameters_SetKernelParametersInFinalStruct(pnode, gs_nNbParameterSet);

	// Add global parameters in final global Structure
	__ClessSample_Parameters_SetGlobalParametersInFinalStruct(pnode, gs_nNbParameterSet);

	// Add KRevok parameters in final global Structure
	__ClessSample_Parameters_SetKRevokParametersInFinalStruct(pnode, gs_nNbParameterSet);

	
	// Put set of parameters in ShareTLV (BERTLV) format (for kernel use when AID will be used).
	if (__ClessSample_Parameters_EncodeTLVTreeInShareBuf(gs_nNbParameterSet) != 0)
		GTL_Traces_TraceDebug ("ClessSample_Parameters_BuildAIDNodes : __ClessSample_Parameters_EncodeTLVTreeInShareBuf failed");
}



//! \brief Dump parameters set on trace link.

void ClessSample_Parameters_Trace_Parameter_AID_Structure(void)
{
	unsigned int nIndexAID;
	
	// Loop on each AID parameter set
	for (nIndexAID = 0; nIndexAID<(unsigned int)gs_nNbParameterSet; nIndexAID++)
	{
		GTL_Traces_TraceDebug("AID parameters set index : %d\n", gs_Parameter_AID[nIndexAID].ucAIDIndex);
		GTL_Traces_TraceDebugBuffer (gs_Parameter_AID[nIndexAID].nAIDLength, gs_Parameter_AID[nIndexAID].ucAID,	"AID :");
		ClessSample_Parameters_Trace_Param_Supported(gs_Parameter_AID[nIndexAID].pTreeAID, CUSTOM_OUTPUT_TRACE, "TLVTree:", C_TRACE_ALL_CHILD, 0);
	}
}



//! \brief Read the XML file and store it in a TLV Tree.

int ClessSample_Parameters_ReadXMLFile (char * VolumeName, char * FileName, TLV_TREE_NODE * pTree)
{
	int nResult;
	char FilePath_L[DISK_NAME_SIZE];
	char FileName_L[DISK_NAME_SIZE];
	
	if (strcmp(FileName, C_FILE_PARAM_XML) == 0)  // Does the file name is CLESSCUST.PAR ?
	{
		// Reset TLVTree
		ClessSample_Parameters_InitParameters(pTree);
		
		// Read XML file
		sprintf(FilePath_L, "/%s", VolumeName);
		sprintf(FileName_L, "/%s/%s", VolumeName, FileName);
		
		// Read the parameter file and stor ethe content in pTreeCurrentParam
		nResult = ClessSample_Parameters_ReadXMLParamFile (pTree, 0, FilePath_L, FileName_L);
		
    	//Trace parameters on printer
		if (nResult == 0) // If no problem
		{
			// Trace the supported parameters in the Trace tool
			ClessSample_Parameters_Trace_Param_Supported(*pTree, CUSTOM_OUTPUT_TRACE, "Read parameters", C_TRACE_ALL_CHILD, 0);
			
			// Save the parameters into a file (CLESSPARAM.PAR)
			nResult = ClessSample_Parameters_SaveParam (*pTree);
			
			if (nResult != 0) // If a problem occurs
			{
				GTL_Traces_TraceDebug("ClessSample_Parameters_ReadXMLFile : ClessSample_Parameters_SaveParam() error");				
			}
			else
			{
				ClessSample_Parameters_Trace_CRC(*pTree, CUSTOM_OUTPUT_TRACE, "CRC loaded file :");
			}
		}
		else
		{
			GTL_Traces_DiagnosticText ("ClessSample_Parameters_ReadXMLFile : CLESSCUST.PAR incorrect file received\n");
		}
		return (STOP); // File is ok for this application
	}
	return (FCT_OK);
}



//! \brief Get the CA Key data according to the RID and the CA Key index.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[in] ucCaKeyIndex CA Public Key index to find.
//! \param[in] pRid RID to be used to find the CA Public Key.
//! \param[out] pOutputDataStruct Shared buffer filled with the CA Public Key data.
//! \return
//!		- \ref TRUE if correctly performed (data found and \a pOutputDataStruct filled).
//!		- \ref FALSE if an error occurred.

int ClessSample_Parameters_GetCaKeyData (TLV_TREE_NODE ParameterTlvTree, const unsigned char ucCaKeyIndex, const unsigned char * pRid, T_SHARED_DATA_STRUCT * pOutputDataStruct)
{
	TLV_TREE_NODE pCaKeysParams;		// Node for CAKeys.
	TLV_TREE_NODE pChild;				// CA Key content
	TLV_TREE_NODE pResearch;			// Working Node
	unsigned char * pValue;
	int nResult = FALSE;
	int bFound = FALSE;
	int cr;
	
	pCaKeysParams = TlvTree_Find(ParameterTlvTree, C_PARAM_CAKEY_TAG, 0);
	
	if (pCaKeysParams != NULL)
	{
		// For each CA Key found in parameters
		pChild = TlvTree_GetFirstChild(pCaKeysParams);
		
		while (pChild != NULL)
		{
			pResearch = TlvTree_Find(pChild, TAG_EMV_AID_TERMINAL, 0); // If AID informations have been found
			
			if (pResearch != NULL)
			{
				if (memcmp(pRid, TlvTree_GetData(pResearch), 5) == 0)
				{
					// Same RID, check if CA Key index is identical
					pResearch = TlvTree_Find(pChild, TAG_EMV_CA_PUBLIC_KEY_INDEX_TERM, 0); // If AID informations have been found
					
					if (pResearch != NULL)
					{
						pValue = TlvTree_GetData(pResearch);
						if (ucCaKeyIndex == pValue[0])
						{
							// This is the correct CA Key, copy the necessary data in pOutputDataStruct (modulus and exponent)
							bFound = TRUE;							
							
							pResearch = TlvTree_Find(pChild, TAG_EMV_INT_CAPK_MODULUS, 0); // If AID informations have been found
							if (pResearch != NULL)
							{
								cr = GTL_SharedExchange_AddTag(pOutputDataStruct, TAG_EMV_INT_CAPK_MODULUS, TlvTree_GetLength(pResearch), TlvTree_GetData(pResearch));
								if (cr != STATUS_SHARED_EXCHANGE_OK)
								{
									GTL_Traces_TraceDebug("ClessSample_Parameters_GetCaKeyData An error occurred when adding TAG_EMV_INT_CAPK_MODULUS in the shared structure (cr = %02x)", cr);
									GTL_SharedExchange_ClearEx(pOutputDataStruct, FALSE);
									goto End;
								}
							}
							
							pResearch = TlvTree_Find(pChild, TAG_EMV_INT_CAPK_EXPONENT, 0); // If AID informations have been found
							if (pResearch != NULL)
							{
								cr = GTL_SharedExchange_AddTag(pOutputDataStruct, TAG_EMV_INT_CAPK_EXPONENT, TlvTree_GetLength(pResearch), TlvTree_GetData(pResearch));
								if (cr != STATUS_SHARED_EXCHANGE_OK)
								{
									GTL_Traces_TraceDebug("ClessSample_Parameters_GetCaKeyData An error occurred when adding TAG_EMV_INT_CAPK_EXPONENT in the shared structure (cr = %02x)", cr);
									GTL_SharedExchange_ClearEx(pOutputDataStruct, FALSE);
									goto End;
								}
							}
							
							nResult = TRUE;
							goto End;
						}
					}
				}
			}
			
			pChild = TlvTree_GetNext(pChild);
		}
	}
	
	if (!bFound)
	{
		GTL_Traces_TraceDebug("ClessSample_Parameters_GetCaKeyData : CA Public Key is not found");
	}
End:
	return (nResult);
}



//! \brief Create the certificate supported list for each AID.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[in] usKernelId Kernel identifier to determine which AID structure shall be updated with the supported certificate list.
//! \return
//!		- \ref TRUE if correctly performed.
//!		- \ref FALSE if an error occurred.

int ClessSample_Parameters_CreateSupportedCertificateListForKernel (TLV_TREE_NODE ParameterTlvTree, unsigned short usKernelId)
{
	unsigned char ucSupportedCaList[64];
	unsigned long ulSupportedListLength;
	unsigned char * pAid;
	int nResult = TRUE;
	TLV_TREE_NODE pAidParams; // AID structure content
	TLV_TREE_NODE pChild; // CA Key content
	TLV_TREE_NODE pResearch; // Working Node
	unsigned short usCurrentKernel;
	unsigned char * pKernelToUse;

	pAidParams = TlvTree_Find(ParameterTlvTree, C_PARAM_AID_TAG, 0);

	if (pAidParams != NULL)
	{
		pChild = TlvTree_GetFirstChild(pAidParams);

		while (pChild != NULL)
		{
			// Init kernel identifier
			usCurrentKernel = DEFAULT_EP_KERNEL_UNKNOWN;

			// Search the kernel to use for this AID
			pResearch = TlvTree_Find(pChild, TAG_EP_KERNEL_TO_USE, 0); // Get the kernel to use for this AID

			if (pResearch != NULL)
			{
				// Build the kernel to use for future use
				pKernelToUse = TlvTree_GetData(pResearch);
				usCurrentKernel = pKernelToUse[1] + (pKernelToUse[0] << 8);

				// If the AID kernel is the same as the requested one
				if (usCurrentKernel == usKernelId)
				{
					// Get the AID
					pResearch = TlvTree_Find(pChild, TAG_EMV_AID_TERMINAL, 0); // If AID informations have been found
					
					if (pResearch != NULL)
					{
						// Save the AID pointer
						pAid = TlvTree_GetData(pResearch);

						// Init output data (supported certificate list)
						ulSupportedListLength = sizeof (ucSupportedCaList);
						memset (ucSupportedCaList, 0, ulSupportedListLength);

						// Get the certificate list for this AID
						ClessSample_Parameters_GetSupportedCertificateList (ParameterTlvTree, ucSupportedCaList, &ulSupportedListLength, pAid);

						if (ulSupportedListLength > 0)
						{
							// Add the tag in the TLV Tree (for the current AID)
							if (usKernelId == DEFAULT_EP_KERNEL_PAYPASS)
							{
								if (TlvTree_AddChild (pChild, TAG_PAYPASS_INT_SUPPORTED_CAPK_INDEX_LIST, ucSupportedCaList, ulSupportedListLength) == NULL)
								{
									GTL_Traces_TraceDebug ("ClessSample_Parameters_CreateSupportedCertificateListForKernel : An error occurred when adding the supported certificate list to the PayPass AID structure");
									nResult = FALSE;
								}
							}
						}
					}
				}
			}

			// Get the next AID structure
			pChild = TlvTree_GetNext(pChild);
		}
	}

	return (nResult);
}



//! \brief Get the CA Key data according to the RID and the CA Key index.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \param[out] pCertificateList List of supported certificate indexes.
//! \param[in,out] Input : The length of \a pCertificate. Output : length of the certificate list.
//! \param[in] pRid RID to be used to find the CA Public Key.
//! \param[out] pOutputDataStruct Shared buffer filled with the CA Public Key data.

void ClessSample_Parameters_GetSupportedCertificateList (TLV_TREE_NODE ParameterTlvTree, unsigned char * pCertificateList, unsigned long * pCertificateListLength, const unsigned char * pRid)
{
	TLV_TREE_NODE pCaKeysParams;		// Node for CAKeys.
	TLV_TREE_NODE pChild;				// CA Key content
	TLV_TREE_NODE pResearch;			// Working Node
	unsigned char * pValue;
	unsigned long ulTempLength = 0;
	
	pCaKeysParams = TlvTree_Find(ParameterTlvTree, C_PARAM_CAKEY_TAG, 0);
	
	if (pCaKeysParams != NULL)
	{
		// For each CA Key found in parameters
		pChild = TlvTree_GetFirstChild(pCaKeysParams);
		
		while (pChild != NULL)
		{
			pResearch = TlvTree_Find(pChild, TAG_EMV_AID_TERMINAL, 0); // If AID informations have been found
			
			if (pResearch != NULL)
			{
				if (memcmp(pRid, TlvTree_GetData(pResearch), 5) == 0)
				{
					// Same RID, check if CA Key index is identical
					pResearch = TlvTree_Find(pChild, TAG_EMV_CA_PUBLIC_KEY_INDEX_TERM, 0); // If AID informations have been found
					
					if (pResearch != NULL)
					{
						pValue = TlvTree_GetData(pResearch);

						if (*pCertificateListLength > ulTempLength)
						{
							pCertificateList[ulTempLength] = pValue[0];
							ulTempLength ++; // One more supported CA
						}
					}
				}
			}
			
			pChild = TlvTree_GetNext(pChild);
		}
	}
	
	if (pCertificateListLength != NULL)
		*pCertificateListLength = ulTempLength;
}



//! \brief Check the CA keys coherence and verify the checksum.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_CheckCaKeysCrc (TLV_TREE_NODE ParameterTlvTree)
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
	MSGinfos tDisplayMsg;
	
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
			pResearch = TlvTree_Find(pChild, TAG_EMV_AID_TERMINAL, 0); // If AID informations have been found
				
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
			pResearch = TlvTree_Find(pChild, TAG_EMV_CA_PUBLIC_KEY_INDEX_TERM, 0); // If AID informations have been found

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
			pResearch = TlvTree_Find(pChild, TAG_EMV_INT_CAPK_EXPONENT, 0); // If AID informations have been found

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

				if ((nCapkCrcLength == 20) && (pShaResult != NULL))
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

			
			// If a checking error occurred, dump the incorrect CA structure information
			if (!bContinue)
			{
				if (ClessSample_DumpData_DumpOpenOutputDriver())
				{
					if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
						ClessSample_DumpData ("\x1b" "E");

					ClessSample_DumpData ("INVALID CERTIFICATE");

					if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
						ClessSample_DumpData ("\x1b" "@" "\x0F");

					ClessSample_DumpData_DumpNewLine();
					ClessSample_DumpData_DumpNewLine();
					ClessSample_DumpData ("RID = ");
					if (nRidLength != 0)
						if (nRidLength != 5)
							ClessSample_DumpData("Bad Length");
						else
							ClessSample_DumpData("%02x%02x%02x%02x%02x", pRid[0], pRid[1], pRid[2], pRid[3], pRid[4]);
					else
						ClessSample_DumpData("Missing");
					ClessSample_DumpData_DumpNewLine();

					ClessSample_DumpData ("Index = ");
					if (nCapkIndexLength != 0)
						if (nCapkIndexLength != 1)
							ClessSample_DumpData("Bad Length");
						else
							ClessSample_DumpData ("%02x", pCapkIndex[0]);
					else
						ClessSample_DumpData("Missing");
					ClessSample_DumpData_DumpNewLine();

					ClessSample_DumpData ("Modulus = ");
					if (nCapkModulusLength != 0)
						if (nCapkModulusLength > 248)
							ClessSample_DumpData("Bad Length");
						else
							ClessSample_DumpData ("%02x%02x...%02x%02x", pCapkModulus[0], pCapkModulus[1], pCapkModulus[nCapkModulusLength-2], pCapkModulus[nCapkModulusLength-1]);
					else
						ClessSample_DumpData("Missing");
					ClessSample_DumpData_DumpNewLine();

					ClessSample_DumpData ("Exponent = ");
					if (nCapkExponentLength != 0)
						if ((nCapkExponentLength != 1) && (nCapkExponentLength != 3))
							ClessSample_DumpData("Bad Length");
						else
							if (nCapkExponentLength == 1)
								ClessSample_DumpData ("%02x", pCapkExponent[0]);
							else
								ClessSample_DumpData ("%02x%02x%02x", pCapkExponent[0], pCapkExponent[1], pCapkExponent[2]);
					else
						ClessSample_DumpData("Missing");
					ClessSample_DumpData_DumpNewLine();

					ClessSample_DumpData ("CRC = ");
					if (nCapkCrcLength != 0)
						if (nCapkCrcLength != 20)
							ClessSample_DumpData("Bad Length");
						else
						{
							for (nIndex=0;nIndex<20;nIndex++)
								ClessSample_DumpData ("%02x", pCapkCrc[nIndex]);
						}
					else
						ClessSample_DumpData("Missing");
					ClessSample_DumpData_DumpNewLine();
					ClessSample_DumpData_DumpNewLine();

					if (pShaResult != NULL)
					{
						ClessSample_DumpData ("Expected Cks = ");
						for (nIndex=0;nIndex<20;nIndex++)
								ClessSample_DumpData ("%02x", ((unsigned char *)pShaResult)[nIndex]);
					}		
					ClessSample_DumpData_DumpNewLine();
					ClessSample_DumpData_DumpNewLine();
					ClessSample_DumpData_DumpNewLine();

					if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
						ClessSample_DumpData ("\x1b" "@");

					ClessSample_DumpData_DumpCloseOutputDriver();
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
		ClessSample_Term_Read_Message(STD_MESS_INVALID_CERTIFICATE, PSQ_Give_Language(), &tDisplayMsg);
		Helper_DisplayTextMerchant(ERASE, HELPERS_MERCHANT_LINE_2, &tDisplayMsg, LEDSOFF);
    	Helper_RefreshScreen(WAIT, HELPERS_MERCHANT_SCREEN);
	}
}



//! \brief Dump the CA keys configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_DumpCaKeys (TLV_TREE_NODE ParameterTlvTree)
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
			ClessSample_DumpData_DumpTlvTreeNodeWithTitle ("CERTIFICATE", pChild);

			// Get the next CA structure
			pChild = TlvTree_GetNext(pChild);
		}
	}
}



//! \brief Dumps the parameters identifier label.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_DumpIdentificationLabel (TLV_TREE_NODE ParameterTlvTree)
{
	TLV_TREE_NODE pParamIdLabel;		// Node for Parameter Identification Label.
	unsigned char * pValue;
	unsigned int nDataLength;
	unsigned char szString[32];
	
	pValue = NULL;
	nDataLength = 0;
	memset (szString, '\0', sizeof(szString));

	pParamIdLabel = TlvTree_Find(ParameterTlvTree, TAG_SAMPLE_PARAMETERS_LABEL, 0);
	
	if (pParamIdLabel != NULL)
	{
		pValue = TlvTree_GetData(pParamIdLabel);
		nDataLength = TlvTree_GetLength(pParamIdLabel);
	}
	
	// Dump the title
	if (ClessSample_DumpData_DumpOpenOutputDriver())
	{
		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
			ClessSample_DumpData ("\x1b" "E");

		if ((pValue != NULL) && (nDataLength != 0))
		{
			memcpy (szString, pValue, nDataLength);
			ClessSample_DumpData ("%s", szString);
		}
		else
		{
			ClessSample_DumpData ("UNKNOWN PARAM ID");
		}

		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();
		ClessSample_DumpData_DumpNewLine();

		if (ClessSample_DumpData_DumpGetOutputId() == CUSTOM_OUTPUT_PRINTER)
			ClessSample_DumpData ("\x1b" "@");

		// Close the output driver
		ClessSample_DumpData_DumpCloseOutputDriver();
	}
}



//! \brief Dump the AIDs configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_DumpAids (TLV_TREE_NODE ParameterTlvTree)
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
			ClessSample_DumpData_DumpTlvTreeNodeWithTitle ("AID STRUCTURE", pChild);

			// Get the next CA structure
			pChild = TlvTree_GetNext(pChild);
		}
	}
}



//! \brief Dump the global parameters configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_DumpGlobals (TLV_TREE_NODE ParameterTlvTree)
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
			ClessSample_DumpData_DumpTlvTreeNodeWithTitle ("GLOBAL DATA", pChild);

			// Get the next CA structure
			pChild = TlvTree_GetNext(pChild);
		}
	}
}



//! \brief Dump the kernel specific parameters configured in the parameter file.
//! \param[in] ParameterTlvTree TLV Tree containing all the parameters.
//! \note It dumps all the invalid data using the configured output device (cf "ClessSample_DumpData.h" functions).

void ClessSample_Parameters_DumpKernelSpecific (TLV_TREE_NODE ParameterTlvTree)
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
			ClessSample_DumpData_DumpTlvTreeNodeWithTitle ("KERNEL SPECIFIC", pChild);

			// Get the next CA structure
			pChild = TlvTree_GetNext(pChild);
		}
	}
}



//! \brief Get a specific information in the parameter file.
//! \param[in] ulTag Tag that shall be extracted.
//! \param[out] bTagPresent Boolean set to \ref SAMPLE_TAG_PRESENT if the tag is correctly retrieved, \ref SAMPLE_TAG_EMPTY if the tag is present but empty, \ref SAMPLE_TAG_ABSENT if the tag is not present in the parameter file.
//! \param[out] pInfo pointer to the requested value
//! \return
//!		- TRUE if data correctly get.
//!		- FALSE if an error occurred.

int ClessSample_Parameters_GetTagInParameterFile(unsigned long ulTag, unsigned char *bTagPresent, unsigned char ** pInfo)
{
	TLV_TREE_NODE pTlvTmp; 		// Temporary Node
	unsigned char *pValue;
	unsigned int nDataLength;

	pTlvTmp = TlvTree_Find(pTreeCurrentParam, ulTag, 0);
	if (pTlvTmp != NULL)
	{
		nDataLength = TlvTree_GetLength(pTlvTmp);
		pValue = TlvTree_GetData(pTlvTmp);
		
		// Get the requested tag value
		*pInfo = pValue;

		if(nDataLength == 0)
			*bTagPresent = SAMPLE_TAG_EMPTY;
		else
		{
			// Tag is present, check the length is correct
			switch (ulTag)
			{
			case (TAG_EMV_AMOUNT_AUTH_NUM):
				if (nDataLength != LENGTH_OF_TRANSACTION_AMOUNT_AUTH_NUM)
					return (FALSE);
				break;
			case (TAG_EMV_AMOUNT_OTHER_NUM):
				if (nDataLength != LENGTH_OF_TRANSACTION_AMOUNT_OTHER_NUM)
					return (FALSE);
				break;
			case (TAG_EMV_TRANSACTION_CURRENCY_CODE):
				if (nDataLength != LENGTH_OF_TRANSACTION_CURRENCY_CODE)
					return (FALSE);
				break;
			case (TAG_EMV_TRANSACTION_CURRENCY_EXPONENT):
				if (nDataLength != LENGTH_OF_TRANSACTION_CURRENCY_EXPONENT)
					return (FALSE);
				break;
			case (TAG_EMV_TRANSACTION_DATE):
				if (nDataLength != LENGTH_OF_TRANSACTION_DATE)
					return (FALSE);
				break;
			case (TAG_EMV_TRANSACTION_TIME):
				if (nDataLength != LENGTH_OF_TRANSACTION_TIME)
					return (FALSE);
				break;
			case (TAG_EMV_TRANSACTION_TYPE):
				if (nDataLength != LENGTH_OF_TRANSACTION_TYPE)
					return (FALSE);
				break;
			case (TAG_EMV_IFD_SERIAL_NUMBER):
				if (nDataLength != LENGTH_OF_IFD_SERIAL_NUMBER)
					return (FALSE);
				break;
			default:
				break;
			}

			// Tag length is correct
			*bTagPresent = SAMPLE_TAG_PRESENT;
		}
	}
	else
		*bTagPresent = SAMPLE_TAG_ABSENT;

	return (TRUE);
}


	
//! \brief This function get the currency label and exponent from the parameters.
//! \param[in] pCurrencyCode Currency code to find in the parameter file.
//! \param[out] pCurrencyLabel Currency label to get.
//!	\return
//!	- \a TRUE if currency is found.
//!	- \a FALSE indicate an invalid parameter as the currency code provided is unknown from the application.

int ClessSample_Parameters_GetCurrencyFromParameters(unsigned char *pCurrencyCode, char **pCurrencyLabel)
{
	int n_NbMoney;
	S_MONEY_EXTENDED * ps_x_Money;
	int i;
	static char *pEurLabel = "EUR";
	char ucCurrencyCode[3];

	GTL_Convert_DcbToAscii(pCurrencyCode, ucCurrencyCode, 1, 4);

	// Get the list of supported money
	ClessSample_Parameters_GetMoneyExtended(&n_NbMoney, &ps_x_Money);

	// Try to find the requested money 
	for(i=0; i<n_NbMoney; i++)
	{
		if(memcmp(ps_x_Money[i].currency.code, ucCurrencyCode, 3) == 0)
		{
			// Currency code found in the parameter file, get the currency label and exponent
			*pCurrencyLabel = (char*)ps_x_Money[i].currency.nom;
			return (TRUE);
		}
	}

	// Not found, check if it is the default currency Euro
	if(memcmp(ucCurrencyCode,"978", 3) == 0)
	{
		*pCurrencyLabel = pEurLabel;
		return (TRUE);
	}

	return (FALSE);
} 



//! \brief This function get the format and the currency position from the parameters to display the amount.
//! \param[in] pCurrencyLabel Currency label to find in the parameter file.
//! \param[out] pFormat Format of the displayed amount.
//! \param[out] pPosition Position of the currency (before or after the amount).
//!	\return
//!	- \a TRUE if format to display is found.
//!	- \a FALSE indicate an invalid parameter as the currency label provided is unknown from the application.

int ClessSample_Parameters_GetCurrencyFormatFromParameters(char *pCurrencyLabel, unsigned char *pFormat,unsigned char *pPosition)
{
	int n_NbMoney;
	S_MONEY_EXTENDED * ps_x_Money;
	int i;
	unsigned char ucExponent;
	unsigned char ucCents;			// character used to separate the cents
    unsigned char ucThousands;		// character used to separate the thousands

	// Set the default format
	*pFormat = 0;	// 0 ==> 1.000,00 
	*pPosition = CURRENCY_AFTER_AMOUNT;	// 0 ==> currency displayed after the amount

	// Get the list of supported money
	ClessSample_Parameters_GetMoneyExtended(&n_NbMoney, &ps_x_Money);

	// Try to find the requested money 
	for(i=0; i<n_NbMoney; i++)
	{
		if(memcmp(ps_x_Money[i].currency.nom, pCurrencyLabel, 3) == 0)
		{
			// Currency label found in the parameter file, get the format and the position
			
			if(ps_x_Money[i].infos.currency_position == CURRENCY_BEFORE_AMOUNT)
				*pPosition = CURRENCY_BEFORE_AMOUNT;
			else
				*pPosition = CURRENCY_AFTER_AMOUNT;
			
			ucCents = ps_x_Money[i].infos.cents_separator;
			ucThousands = ps_x_Money[i].infos.thousands_separator;
			ucExponent = ps_x_Money[i].currency.posdec;

			if ((ucCents == ',') && (ucThousands == '.') && (ucExponent == 2))
				*pFormat = 0;
			else if ((ucCents == '.') && (ucThousands == ',') && (ucExponent == 2))
				*pFormat = 1;
			else if ((ucCents == ',') && (ucThousands == ' ') && (ucExponent == 2))
				*pFormat = 2;
			else if ((ucCents == ' ') && (ucThousands == '.') && (ucExponent == 0))
				*pFormat = 3;
			else if ((ucCents == ' ') && (ucThousands == ',') && (ucExponent == 0))
				*pFormat = 4;
			else if ((ucCents == ' ') && (ucThousands == ' ') && (ucExponent == 0))
				*pFormat = 5;
			else if ((ucCents == ',') && (ucThousands == '.') && (ucExponent == 3))
				*pFormat = 6;
			else if ((ucCents == '.') && (ucThousands == ',') && (ucExponent == 3))
				*pFormat = 7;
			else if ((ucCents == ',') && (ucThousands == ' ') && (ucExponent == 3))
				*pFormat = 8;
			else
				*pFormat = 0;

			return (TRUE);
		}
	}

	return (FALSE);
}
