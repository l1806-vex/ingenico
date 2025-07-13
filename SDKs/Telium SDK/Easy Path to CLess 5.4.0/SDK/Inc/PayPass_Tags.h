/**
 * \file    PayPass_Tags.h
 * \brief   This describes all the specific PayPass contactless kernel tags.
 *
 *
 * \author	Ingenico
 * \author  Copyright (c) 2011 Ingenico, rue claude Chappe,\n
 *          07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author  Ingenico has intellectual property rights relating to the technology embodied \n
 *          in this software. In particular, and without limitation, these intellectual property rights may\n
 *          include one or more patents.\n
 *          This software is distributed under licenses restricting its use, copying, distribution, and\n
 *          and decompilation. No part of this software may be reproduced in any form by any means\n
 *          without prior written authorization of Ingenico.
 **/



/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup PayPassTagsDefinedBySpec
//! @{
#define TAG_PAYPASS_TRACK1_DATA										0x56					/*!< PAYPASS - Track 1 Data contains the data objects of the track 1 according to [ISO/IEC 7813] Structure B, excluding start sentinel, end sentinel and LRC.<br><br>	- Format : ans.<br>	- Length : var. up to 76 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_OFFLINE_ACCUMULATOR_BALANCE						0x9F50					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Represents the amount of offline spending available in the card. It can be retreived before and after the GenAC. It is stored in \ref TAG_PAYPASS_BALANCE_READ_BEFORE_GENAC and/or \ref TAG_PAYPASS_BALANCE_READ_AFTER_GENAC only (not stored as 9F50 in the kernel database).<br><br>	- Format : n.<br>	- Length : 6 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_DRDOL											0x9F51					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - A data object in the Card that provides the Kernel with a list of data objects that must be passed to the Card in the data field of the RECOVER AC command.<br><br>	- Format : b.<br>	- Length : var up to 256.<br>	- Source : Card. */
#define TAG_PAYPASS_TRANSACTION_CATEGORY_CODE						0x9F53					/*!< PAYPASS - This is a data object defined by MasterCard which indicates the type of transaction being performed, and which may be used in Card Risk Management.<br><br>	- Format : an.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_DS_ODS_CARD				    					0x9F54					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains the Card stored operator proprietary data obtained in the response to the GET PROCESSING OPTIONS command.<br><br>	- Format : b.<br>	- Length : var. up to 160 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_DSDOL							    			0x9F5B					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - A data object in the card that provides the kernel with a list of data objects that must be passed to the card in the data field of the Generate AC after the CDOL1 Related Data.<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Card. */
#define TAG_PAYPASS_DS_REQUESTED_OPERATOR_ID    					0x9F5C					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains the Terminal determined opertaor identifier for data storage. It is sent to the Card in the GET PROCESSING OPTIONS command.<br><br>	- Format : b.<br>	- Length : 8 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_APPLICATION_CAPABILITIES_INFORMATION			0x9F5D					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Lists a number of card features beyond regular payment.<br>Refer to \ref PayPass3ApplicationCapabilitiesInformation for more information about the possible values.<br><br>	- Format : b.<br>	- Length : 3 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_DS_ID							    			0x9F5E					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Data Storage Identifier constructed as follows : Application PAN (without any 'F' padding) || Application PAN Sequence Number (+ zero padding).<br><br>	- Format : n.<br>	- Length : 8 to 11 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_DS_SLOT_AVAILABILITY	    					0x9F5F					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains the Card indication, obtained in the response to the GET PROCESSING OPTIONS command, about the slot type(s) available for data storage.<br>	- Bit 8 : Permanent slot type.<br>	- Bit 7 : Volatile slot type.<br>	- Bits 6-1: RFU.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Card. */
#define TAG_PAYPASS_CVC3_TRACK1										0x9F60					/*!< PAYPASS - The CVC3TRACK1 is a 2-byte cryptogram returned by the card in the response to the COMPUTE CRYPTOGRAPHIC CHECKSUM command.<br><br>	- Format : b.<br>	- Length : 2 byte.<br>	- Source : Card. */
#define TAG_PAYPASS_CVC3_TRACK2										0x9F61					/*!< PAYPASS - The CVC3TRACK2 is a 2-byte cryptogram returned by the card in the response to the COMPUTE CRYPTOGRAPHIC CHECKSUM command.<br><br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_PCVC3_TRACK1									0x9F62					/*!< PAYPASS - PCVC3TRACK1 indicates to the PayPass reader the positions in the discretionary data field of the Track 1 Data where the qTRACK1 CVC3TRACK1 digits have to be copied.<br><br>	- Format : b.<br>	- Length : 6 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_PUNATC_TRACK1									0x9F63					/*!< PAYPASS - PUNATCTRACK1 indicates to the PayPass reader the positions in the discretionary data field of the Track 1 Data where the nUN UN (Numeric) digits and tTRACK1 ATC digits have to be copied.<br><br>	- Format : b.<br>	- Length : 6 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_NATC_TRACK1										0x9F64					/*!< PAYPASS - The value of NATCTRACK1 represents the number of digits of the ATC to be included in the discretionary data field of the Track 1 Data.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Card. */
#define TAG_PAYPASS_PCVC3_TRACK2									0x9F65					/*!< PAYPASS - PCVC3TRACK2 indicates to the PayPass reader the positions in the discretionary data field of the Track 2 Data where the qTRACK2 CVC3TRACK2 digits have to be copied.<br><br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_PUNATC_TRACK2									0x9F66					/*!< PAYPASS - PUNATCTRACK2 indicates to the PayPass reader the positions in the discretionary data field of the Track 2 Data where the nUN UN (Numeric) digits and tTRACK2 ATC digits have to be copied.<br><br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_NATC_TRACK2										0x9F67					/*!< PAYPASS - The value of NATCTRACK2 represents the number of digits of the ATC to be included in the discretionary data field of the Track 2 Data.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Card. */
#define TAG_PAYPASS_UDOL											0x9F69					/*!< PAYPASS - The UDOL is the DOL that specifies the data objects to be included in the data field of the COMPUTE CRYPTOGRAPHIC CHECKSUM command. The UDOL must at least include the UN (Numeric). The UDOL is not mandatory for the card. There will always be a Default UDOL, including as its only entry the tag and length of the UN (Numeric) (tag '9F6A').<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Card. */
#define TAG_PAYPASS_MSTRIPE_UNPREDICTABLE_NUMBER					0x9F6A					/*!< PAYPASS - Unpredictable number generated by the PayPass reader during a PayPass – Mag Stripe Transaction. The UN (Numeric) is passed to the card in the data field of the COMPUTE CRYPTOGRAPHIC CHECKSUM command. The (8-nUN) most significant digits must be set to zero.<br><br>	- Format : n.<br>	- Length : 8 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_TRACK2_DATA										0x9F6B					/*!< PAYPASS - Track 2 Data contains the data objects of the track 2 according to [ISO/IEC 7813], excluding start sentinel, end sentinel and LRC.<br><br>	- Format : b.<br>	- Length : var. up to 19 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_MSTRIPE_APPLI_VERSION_NUMBER_ICC				0x9F6C					/*!< PAYPASS - Version number assigned by the payment system for the specific PayPass – Mag Stripe functionality of the application (card value).<br><br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_MSTRIPE_APPLI_VERSION_NUMBER_TERM				0x9F6D					/*!< PAYPASS - Version number assigned by the payment system for the specific PayPass – Mag Stripe functionality of the application (terminal value).<br><br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_THIRD_PARTY_DATA								0x9F6E					/*!< PAYPASS - The PayPass Third Party Data contains proprietary information from a third party. If present, the PayPass Third Party Data must be present in a file read using the READ RECORD command.<br><br>	- Format : b.<br>	- Length : 5-32 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_DS_SLOT_MANAGEMENT_CONTROL	    				0x9F6F					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains the Card indication, obtained in the response to the GET PROCESSING OPTIONS command, about the status of the slot containing data associated to the DS Requested Operator ID.<br>Please refer to \ref PayPass3DsSlotManagementControl for existing flag masks.<br><br>	- Bit 8 : Permanent slot type.<br>	- Bit 7 : Volatile slot type.<br>	- Bit 6 : Low volatility.<br>	- Bit 5 : Locked slot.<br>	- Bits 4-2 : RFU.<br>	- Bit 1 : Deactivated slot.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Card. */
#define TAG_PAYPASS_PROTECTED_DATA_ENVELOPE_1						0x9F70					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The Protected Data Envelopes contain proprietary information from the issuer, payment system or third party. The Protected Data Envelope can be retrieved with the GET DATA command. Updating the Protected Data Envelope with the PUT DATA command requires secure messaging and is outside the scope of the specification. The length is specific to the card implementation and must have a value between 32 and 192 bytes.<br><br>	- Format : b.<br>	- Length : 32 - 192 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_PROTECTED_DATA_ENVELOPE_2						0x9F71					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The Protected Data Envelopes contain proprietary information from the issuer, payment system or third party. The Protected Data Envelope can be retrieved with the GET DATA command. Updating the Protected Data Envelope with the PUT DATA command requires secure messaging and is outside the scope of the specification. The length is specific to the card implementation and must have a value between 32 and 192 bytes.<br><br>	- Format : b.<br>	- Length : 32 - 192 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_PROTECTED_DATA_ENVELOPE_3						0x9F72					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The Protected Data Envelopes contain proprietary information from the issuer, payment system or third party. The Protected Data Envelope can be retrieved with the GET DATA command. Updating the Protected Data Envelope with the PUT DATA command requires secure messaging and is outside the scope of the specification. The length is specific to the card implementation and must have a value between 32 and 192 bytes.<br><br>	- Format : b.<br>	- Length : 32 - 192 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_PROTECTED_DATA_ENVELOPE_4						0x9F73					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The Protected Data Envelopes contain proprietary information from the issuer, payment system or third party. The Protected Data Envelope can be retrieved with the GET DATA command. Updating the Protected Data Envelope with the PUT DATA command requires secure messaging and is outside the scope of the specification. The length is specific to the card implementation and must have a value between 32 and 192 bytes.<br><br>	- Format : b.<br>	- Length : 32 - 192 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_PROTECTED_DATA_ENVELOPE_5						0x9F74					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The Protected Data Envelopes contain proprietary information from the issuer, payment system or third party. The Protected Data Envelope can be retrieved with the GET DATA command. Updating the Protected Data Envelope with the PUT DATA command requires secure messaging and is outside the scope of the specification. The length is specific to the card implementation and must have a value between 32 and 192 bytes.<br><br>	- Format : b.<br>	- Length : 32 - 192 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_UNPROTECTED_DATA_ENVELOPE_1						0x9F75					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The Unprotected Data Envelopes contain proprietary information from the issuer, payment system or third party. Unprotected Data Envelopes can be retrieved with the GET DATA command and can be updated with the PUT DATA (CLA='80') command without secure messaging. The length of Unprotected Data Envelopes is specific to the card implementation and must have a value between 32 and 192 bytes.<br><br>	- Format : b.<br>	- Length : 32 - 192 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_UNPROTECTED_DATA_ENVELOPE_2						0x9F76					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The Unprotected Data Envelopes contain proprietary information from the issuer, payment system or third party. Unprotected Data Envelopes can be retrieved with the GET DATA command and can be updated with the PUT DATA (CLA='80') command without secure messaging. The length of Unprotected Data Envelopes is specific to the card implementation and must have a value between 32 and 192 bytes.<br><br>	- Format : b.<br>	- Length : 32 - 192 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_UNPROTECTED_DATA_ENVELOPE_3						0x9F77					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The Unprotected Data Envelopes contain proprietary information from the issuer, payment system or third party. Unprotected Data Envelopes can be retrieved with the GET DATA command and can be updated with the PUT DATA (CLA='80') command without secure messaging. The length of Unprotected Data Envelopes is specific to the card implementation and must have a value between 32 and 192 bytes.<br><br>	- Format : b.<br>	- Length : 32 - 192 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_UNPROTECTED_DATA_ENVELOPE_4						0x9F78					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The Unprotected Data Envelopes contain proprietary information from the issuer, payment system or third party. Unprotected Data Envelopes can be retrieved with the GET DATA command and can be updated with the PUT DATA (CLA='80') command without secure messaging. The length of Unprotected Data Envelopes is specific to the card implementation and must have a value between 32 and 192 bytes.<br><br>	- Format : b.<br>	- Length : 32 - 192 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_UNPROTECTED_DATA_ENVELOPE_5						0x9F79					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The Unprotected Data Envelopes contain proprietary information from the issuer, payment system or third party. Unprotected Data Envelopes can be retrieved with the GET DATA command and can be updated with the PUT DATA (CLA='80') command without secure messaging. The length of Unprotected Data Envelopes is specific to the card implementation and must have a value between 32 and 192 bytes.<br><br>	- Format : b.<br>	- Length : 32 - 192 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_MERCHANT_CUSTOM_DATA							0x9F7C					/*!< PAYPASS - Proprietary merchant data that may be requested by the card.<br><br>	- Format : ans.<br>	- Length : 20 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_DS_SUMMARY_1					    			0x9F7D					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains the Card indication, obtained in the response to the GET PROCESSING OPTIONS command, about either the stored summary associated with DS ODS Card if present, or about the default zero-filled summary if DS ODS Card is not present and DS Unpredictable Number is present.<br><br>	- Format : b.<br>	- Length : 8 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_MOBILE_SUPPORT_INDICATOR						0x9F7E					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The Mobile Support Indicator informs the Card that the Kernel supports extensions for mobile and requires on-device cardholder verification. Note this tag shall not be provided by the application as it is set by the kernel automatically.<br>	- Bits 8-3 : RFU.<br>	- Bit 2 : Offline PIN required.<br>	- Bit 1 : Mobile supported.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_DS_UNPREDICTABLE_NUMBER				    		0x9F7F					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains the Card challenge (random), obtained in the response to the GET PROCESSING OPTIONS command, to be used by the Terminal in the summary calculation when providing DS ODS Term.<br><br>	- Format : b.<br>	- Length : 4 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_POS_CARDHOLDER_INTERACTION_INFO					0xDF4B					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The POS Cardholder Interaction Information informs the kernel about the indicators set in the mobile phone that may influence the action flow of the merchant and cardholder.<br>Refer to \ref PayPass3ApplicationCapabilitiesInformation for more information about the possible values.<br><br>	- Format : b.<br>	- Length : 3 bytes.<br>	- Source : Card. */
#define TAG_PAYPASS_DS_INPUT_CARD   								0xDF60					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains Terminal provided data if permanent data storage in the Card was applicable (DS Slot Management Control[8]=1b), remains applicable, or becomes applicable (DS ODS Info[8]=1b). Otherwise, this data item is a filler to be supplied by the Kernel. The data is forwarded to the Card with the GENERATE AC, as per DSDOL formatting.<br><br>	- Format : b.<br>	- Length : 8 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_DS_DIGEST_H		    							0xDF61					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains the result of OWHF2 (DS Input (Term)) or OWHF2AES (DS Input (Term)), if DS Input (Term) is provided by the Terminal.  The data object is to be supplied to the Card with the GENERATE AC command, as per DSDOL formatting.<br><br>	- Format : b.<br>	- Length : 8 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_DS_ODS_INFO			    						0xDF62					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains Terminal provided data to be forwarded to the Card with the GENERATE AC command, as per DSDOL formatting.<br>Please refer to \ref PayPass3DsOdsInfoFlags for more information about the flags.<br>	- Bit 8 : Permanent slot type.<br>	- Bit 7 : Volatile slot type.<br>	- Bit 6 : Low volatility.<br>	- Bit 5 : RFU.<br>	- Bit 4 : Decline payment transaction in case of data storage error.<br>	- Bits 3-1 : RFU.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_DS_ODS_TERM				    					0xDF63					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains Terminal provided data to be forwarded to the Card with the GENERATE AC command, as per DSDOL formatting.<br><br>	- Format : b.<br>	- Length : var. up to 160 bytes.<br>	- Source : Terminal. */
//! @}


//! \addtogroup PayPassTagsInternallyDefined
//! @{
#define TAG_PAYPASS_DD_CARD_TRACK1									0x9F918500				/*!< PAYPASS - If Track 1 Data is present, then DDCARD,TRACK1 contains a copy of the discretionary data field of Track 1 Data as returned by the card in the file read using the READ RECORD command during a PayPass – Mag Stripe transaction (i.e. without UN (Numeric), ATC, CVC3TRACK1 and nUN included).<br><br>	- Format : ans.<br>	- Length : var. up to 56 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF812A value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_DD_CARD_TRACK2									0x9F918501				/*!< PAYPASS - DDCARD,TRACK2 contains a copy of the discretionary data field of Track 2 Data as returned by the card in the file read using the READ RECORD command during a PayPass – Mag Stripe transaction (i.e. without UN (Numeric), ATC, CVC3TRACK2 and nUN included).<br><br>	- Format : ans.<br>	- Length : var. up to 8 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF812B value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_DEFAULT_UDOL									0x9F918502				/*!< PAYPASS - The Default UDOL is the UDOL to be used for constructing the value field of the COMPUTE CRYPTOGRAPHIC CHECKSUM command if the UDOL in the card is not present. The Default UDOL must always be present and must contain as its only entry the tag and length of the UN (Numeric). The value of the Default UDOL must be: '9F6A04'.<br><br>	- Format : b.<br>	- Length : 3 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF811A value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_MSTRIPE_INDICATOR								0x9F918503				/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - Indicates for each AID whether the PayPass – Mag Stripe profile is supported or not by the PayPass reader. Its value is implementation specific (\a 0 if not supported, \a 1 if supported). <br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_TERMINAL_CAPABILITIES_CVM_REQ					0x9F918504				/*!< <b>OBSOLETE WITH KERNEL C2</b><br><br>PAYPASS - Indicates the card data input, CVM, and security capabilities of the terminal and PayPass reader when the transaction amount is greater than or equal to the Terminal CVM Required Limit.<br><br>	- Format : b.<br>	- Length : 3 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_TERMINAL_CAPABILITIES_NO_CVM_REQ				0x9F918505				/*!< <b>OBSOLETE WITH KERNEL C2</b><br><br>PAYPASS - Indicates the card data input, CVM, and security capabilities of the terminal and PayPass reader when the transaction amount is below the Terminal CVM Required Limit.<br><br>	- Format : b.<br>	- Length : 3 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_TRANSACTION_CVM									0x9F918506				/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - Data object used to indicate to the terminal the outcome of the CVM Selection function. Possible values are "No CVM", "Signature", "Online PIN". The coding of the value is implementation specific. Refer to \ref PayPassPossibleCvm for more information about the possible values.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_TRANSACTION_OUTCOME								0x9F918507				/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - Data object used to indicate to the terminal the outcome of the transaction processing. Possible values are "Approved", "Online Request", "Declined", "Try Another Interface" or "End Application". The coding of the value is implementation specific. Refer to \ref PayPassPossibleOutcomes for more information about the possible values.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */

#define TAG_PAYPASS_INT_MSTRIPE_K_TRACK2							0x9F918508				/*!< PAYPASS - Internal tag indicating the number of non-zero bits in PUNATC Track 2 (k Track2).<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MSTRIPE_Q_TRACK2							0x9F918509				/*!< PAYPASS - Internal tag indicating the number of non-zero bits in PCVC3 Track 2 (q Track2).<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MSTRIPE_K_TRACK1							0x9F91850A				/*!< PAYPASS - Internal tag indicating the number of non-zero bits in PUNATC Track 1 (k Track1).<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MSTRIPE_Q_TRACK1							0x9F91850B				/*!< PAYPASS - Internal tag indicating the number of non-zero bits in PCVC3 Track 1 (q Track1).<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MSTRIPE_NUN									0x9F91850C				/*!< PAYPASS - Internal tag equal to ((k Track2) - (t Track2)).<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MSTRIPE_TERMINAL_AVN_LIST					0x9F91850D				/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - Internal tag indicating the list of MStripe application version number supported by the terminal. This consiste of a concatenation of AVN (each of them is coded on 2 bytes).<br><br>	- Format : b.<br>	- Length : up to 128 bytes (i.e. up to 64 application version numbers).<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MCHIP_ODA_METHOD							0x9F91850E				/*!< PAYPASS - Internal tag indicating the MChip ODA selected method. Refer to \ref PayPassPossibleOdaMethods for more information about the possible values.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MCHIP_DATA_PART_OF_ODA						0x9F91850F				/*!< PAYPASS - Internal tag containing the concatenation of data that are part of authentication.<br><br>	- Format : b.<br>	- Length : up to 2048 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MCHIP_IS_SFI_ERROR							0x9F918510				/*!< PAYPASS - Internal tag indicating if a record that is part of ODA is incorrectly coded or not. If there is no error, this tag is not stored.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MCHIP_TERMINAL_AVN_LIST						0x9F918511				/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - Internal tag indicating the list of MChip application version number supported by the terminal. This consists of a concatenation of AVN (each of them is coded on 2 bytes).<br><br>	- Format : b.<br>	- Length : up to 128 bytes (i.e. up to 64 application version numbers).<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MCHIP_GENAC_REF_CTRL_PARAMETER				0x9F918512				/*!< PAYPASS - Internal tag indicating the Generate AC Reference Control Parameter to be sent on the Generate AC command (result of the Terminal Action Analysis Step). Refer to \ref GenAcRefControlParameters for more information about the possible values. Note the \a EMVLIB_GENAC_RCP_CDA_MASK bit is not set in this value.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8114 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_MCHIP_TAC_IAC_DEFAULT_MATCHED				0x9F918513				/*!< PAYPASS - Internal tag indicating the TAC IAC default matched or not with the TVR (\a TRUE if it matched, \a FALSE else).<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MCHIP_GENAC_RESPONSE_DATA					0x9F918514				/*!< PAYPASS - Internal tag containing the Generate AC card response data (content of template 0x77). This tag will be used for CDA signature generation and verification.<br><br>	- Format : b.<br>	- Length : up to 258 bytes.<br>	- Source : Terminal. */

#define TAG_PAYPASS_INT_SENT_APDU									0x9F918515				/*!< PAYPASS - Internal tag containing an APDU sent by the reader to the contactless card (several tags can be present).<br><br>	- Format : b.<br>	- Length : up to 261 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_CARD_RESPONSE								0x9F918516				/*!< PAYPASS - Internal tag containing a card response (several tags can be present).<br><br>	- Format : b.<br>	- Length : up to 258 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_SUPPORTED_CAPK_INDEX_LIST					0x9F918517				/*!< PAYPASS - Internal tag containing the list of CA Public Key index list (concatenation of indexes (each one coded on one byte)). This tag can contain up to 64 supported key indexes.<br><br>	- Format : b.<br>	- Length : up to 64 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_MERCHANT_FORCE_ONLINE						0x9F918518				/*!< PAYPASS - Internal tag that indicates if the merchant wants to force the tranasction online (coded on 1 byte). If set to 01, TVR Byte 4 bit 4 is set at the begining of the Terminal Action Analysis to indicate merchant has forced the transaction online (\a 1 if merchant wishes to force transaction online, \a not \a present or \a 0 if not forced online). This is only applicable for the MChip transaction flow. It sets the TVR B4b4.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_USE_REFUND_FLOW								0x9F918519				/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - Internal tag that indicates if the refund transaction flow as descibed in the PayPass 2.1 specification shall be used (\a 1 if refund transaction is used, \a not \a present or \a 0 if not used, i.e standard transaction flow used).<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_ODA_FAILED_FLAG								0x9F91851A				/*!< PAYPASS - Internal tag that indicates ODA has failed. If ODA does not fail, this tag is not present in the database. If present, it indicates which ODA has failed  : \ref PAYPASS_MCHIP_ODA_METHOD_CDA if CDA failed.<br>Note \ref PAYPASS_MCHIP_ODA_METHOD_SDA cannot be used anymore as C2 Kernel does not support SDA anymore.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_FORCE_MSTRIPE_FLOW							0x9F91851B				/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - Internal tag that indicates if the MStripe transaction flow shall be forced, even if a MChip card is presented (\a 1 if MStripe flow is forced, \a not \a present or \a 0 if standard processing is used, i.e. both MChip and MStripe). If a M/Chip card is presented and MStripe flow is forced, then the card will be considered as a MStripe card.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */

#define TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_NO_DCV					0x9F91851C				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the transaction amount limit above which the transaction is not allowed, when on-device cardholder verification is not supported.<br><br>	- Format : n.<br>	- Length : 6 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8124 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_CLESS_TRANSACTION_LIMIT_DCV						0x9F91851D				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the transaction amount limit above which the transaction is not allowed, when on-device cardholder verification is supported.<br><br>	- Format : n.<br>	- Length : 6 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8125 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_ODA_STATUS										0x9F91851E				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates if CDA is to be performed for the transaction in progress.<br>Refer to \ref PayPass3OdaStatus for more information about the possible values.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_OUTCOME_PARAMETER_SET							0x9F91851F				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates to the Terminal the outcome of the transaction processing by the Kernel. Its value is an accumulation of results about applicable parts of the transaction.<br>Refer to \ref PayPass3OutcomeParameterSet for more information about the possible values.<br><br>	- Format : b.<br>	- Length : 8 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8129 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA						0x9F918520				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Combines all parameters for GUI.<br>Refer to \ref PayPass3UserInterfaceRequestData for more information about the possible values.<br><br>	- Format : b.<br>	- Length : 22 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8116 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_ERROR_INDICATION								0x9F918521				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains information regarding the nature of the error that has been encountered during the transaction processing. This data is part of the discretionary data.<br>Refer to \ref PayPass3ErrorIndication for more information about the possible values.<br><br>	- Format : b.<br>	- Length : 6 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8115 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_KERNEL_CONFIGURATION							0x9F918522				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the Kernel configuration options. Set this to 0 if you support both MChip and MStripe transaction flows.<br>Please refer to \ref PayPass3KernelConfiguration section for more information about the possible values.<br>	- bit 8 : Only EMV mode transactions supported.<br>	- bit 7 : Only Mag-stripe mode transactions supported.<br>	- bit 6 : On device cardholder verification supported.<br>	- bits 5 to 1 : RFU.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF811B value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_CARD_DATA_INPUT_CAPABILITY						0x9F918523				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the card data input capability of the Terminal and Reader. This tag is coded according to Annex A.2 of EMV Book 4.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8117 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_SECURITY_CAPABILITY								0x9F918524				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the security capability of the Kernel. This tag is coded according to Annex A.2 of EMV Book.<br>	- Bit 8 : SDA<br>	- Bit 7 : DDA<br>	- Bit 6 : Card Capture<br>	- Bit 5 : RFU<br>	- Bit 4 : CDA<br>	- bits 3 to 1 : RFU <br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF811F value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_REQUIRED				0x9F918525				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the MChip CVM Capability of the Terminal and Reader when transaction amount is greater than the Reader CVM Required Limit. The CVM Capability - CVM Required is coded according to Annex A.2 of EMV Book 4.<br>	- Bit 8 : Plaintext PIN for ICC verification.<br>	- Bit 7 : Enciphered PIN for online verification.<br>	- Bit 6 : Signature (paper).<br>	- Bit 5 : Enciphered PIN for offline verification.<br>	- Bit 4 : No CVM required.<br>	- Bits 3 to 1 : RFU.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8118 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_MCHIP_CVM_CAPABILITY_CVM_NOT_REQUIRED			0x9F918526				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the MChip CVM Capability of the Terminal and Reader when transaction amount is lesser than or equal to the Reader CVM Required Limit. The CVM Capability - CVM Required is coded according to Annex A.2 of EMV Book 4.<br>	- Bit 8 : Plaintext PIN for ICC verification.<br>	- Bit 7 : Enciphered PIN for online verification.<br>	- Bit 6 : Signature (paper).<br>	- Bit 5 : Enciphered PIN for offline verification.<br>	- Bit 4 : No CVM required.<br>	- Bits 3 to 1 : RFU.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8119 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_REQUIRED				0x9F918527				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the MStripe CVM Capability of the Terminal and Reader when transaction amount is greater than the Reader CVM Required Limit.<br>	- Bit 8-5 : 0000 means No CVM<br>	- Bit 8-5 : 0001 means OBTAIN SIGNATURE<br>	- Bit 8-5 : 0010 means ONLINE PIN<br>	- Bit 8-5 : 1111 means N/A<br>	- Bits 4 - 1 : RFU.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF811E value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_MSTRIPE_CVM_CAPABILITY_CVM_NOT_REQUIRED			0x9F918528				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the MStripe CVM Capability of the Terminal and Reader when transaction amount is lesser than or equal to the Reader CVM Required Limit.<br>	- Bit 8-5 : 0000 means No CVM<br>	- Bit 8-5 : 0001 means OBTAIN SIGNATURE<br>	- Bit 8-5 : 0010 means ONLINE PIN<br>	- Bit 8-5 : 1111 means N/A<br>	- Bits 4 - 1 : RFU.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF812C value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_MSTRIPE_NUN_PRIME							0x9F918529				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Internal tag equal indicating the nUn' necessary fro mobiles phones. It can be nUn or (nUn + 5) % 10 depending of the case.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_PROPRIETARY_RECORD_MANAGEMENT				0x9F91852A				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates what the kernel is supposed to do with the proprietary records.<br>	- Bit 8 : Indicates if the proprietary records are read (note the ones that are part of ODA are systematically read)<br>	- Bit 7 : Indicates if the proprietary recognised tag in the the proprietary records are stored<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_DEFAULT_HOLD_TIME								0x9F91852B				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the default delay for the processing of the next MSG signal. The Message Hold Time is an integer in units of 100ms.<br><br>	- Format : n.<br>	- Length : 3 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF812D value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_RID											0x9F91852C				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the RID to be used to retreive the CA public key. This tag is only provided in the STEP_PAYPASS_MCHIP_GET_CERTIFICATE step customisation in order to retreive the CA Public key.<br><br>	- Format : b.<br>	- Length : 5 to 16 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_DISABLE_LANGUAGE_SELECTION					0x9F91852D				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates if the language selection is activated (0 or not present) or is disabled (1).<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_PHONE_MESSAGE_TABLE							0x9F91852E				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the Phone Message Table to be used with the selected AID. This tag consists fo a list of entries. Each entry has the following format : PCII_MASK on 3 bytes, PCII_VALUE on 3 bytes, MESSAGE on 1 byte and STATUS on 1 byte.<br><br>	- Format : b.<br>	- Length : up to 128 bytes (i.e. 16 entries).<br>	- Source : Terminal. */
#define TAG_PAYPASS_BALANCE_READ_BEFORE_GENAC						0x9F91852F				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Stores the Card Balance read before the Generate AC. To read the card balance before the Generate AC, the card shall support it, and the payment application shall provide this tag as empty (to indicates it wants to read it).<br><br>	- Format : n.<br>	- Length : 6 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8104 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_BALANCE_READ_AFTER_GENAC						0x9F918530				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Stores the Card Balance read after the Generate AC. To read the card balance after the Generate AC, the card shall support it, and the payment application shall provide this tag as empty (to indicates it wants to read it).<br><br>	- Format : n.<br>	- Length : 6 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8105 value in the MasterCard Kernel C2 specification. */

#define TAG_PAYPASS_INT_DS_INPUT_TERM								0x9F918531				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains Terminal provided data if permanent data storage in the Card was applicable (DS Slot Management Control[8]=1b), stays or becomes (DS ODS Info[8]=1b) applicable. DS Input (Term) is used by the Kernel as input to calculate DS Digest H.<br><br>	- Format : b.<br>	- Length : 8 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8109 value in the MasterCard Kernel C2 specification.  */
#define TAG_PAYPASS_INT_DS_ODS_INFO_FOR_KERNEL						0x9F918532				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains instructions from the application on how to proceed with the transaction if :<br>	- The AC requested by the application does not match the AC proposed by the kernel.<br>	- The update of the slot data has failed.<br>Please refer to \ref PayPass3DsOdsInfoForReader for more information about the different masks.<br><br>	- Bit 8 : Usable for TC.<br>	- Bit 7 : Usable for ARQC.<br>	- Bit 6 : Usable for AAC.<br>	- Bits 5-4 : RFU.<br>	- Bit 3 : Stop if no DS ODS Term.<br>	- Bit 2 : Stop if write failed.<br>	- Bit 1 : RFU.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF810A value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_DS_SUMMARY_2								0x9F918533				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - This data allows the Kernel to check the consistency between DS_Summary_1 and DS_Summary_2, and so to ensure that DS ODS Card is provided by a genuine Card. It is located in the ICC Dynamic Data recovered from the SIgned Dynamic Application Data.<br><br>	- Format : b.<br>	- Length : 8 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8101 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_DS_SUMMARY_3								0x9F918534				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - This data allows the Kernel to check whether the Card has seen the same transaction data as were sent by the Terminal/Kernel. It is located in the ICC Dynamic Data recovered from the Signed Dynamic Application Data.<br><br>	- Format : b.<br>	- Length : 8 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8102 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_DS_SUMMARY_STATUS							0x9F918535				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Information reported by the Kernel to the Terminal about :<br>	- The inconsistency between DS_Summary_1 and DS_Summary_2 (successfull read)<br>	- difference between DS_Summary_2 and DS_Summary_3 (successfull write).<br>This data object is part of the Discretionary Data.<br><br>	- Bits 8-3 : RFU.<br>	- Bit 2 : Read.<br>	- bit 1 : Write.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF810B value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_DSVN_TERM									0x9F918536				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Integrated Data Storage support by the Kernel depends on the presence of this data object. If it is absent, data storage is not supported. Its value is '02' for this version of data storage functionality. This variable length data item has an initial byte that defines the maximum version number supported by the Terminal and a variable number of subsequent bytes that define how the Terminal supports earlier versions of the specification. As this is the first version, no legacy support is described and no additional bytes are present.<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF810D value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_POST_GENAC_PUT_DATA_STATUS						0x9F918537				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Information reported by the Kernel to the Terminal, about the processing of PUT DATA commands after processing the GENERATE AC command. Possible values are 'completed' or 'not completed'. In the latter case, this status is not specific about which of the PUT DATA commands failed, or about how many of these commands have failed or succeeded.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF810E value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_PRE_GENAC_PUT_DATA_STATUS						0x9F918538				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Information reported by the Kernel to the Terminal, about the processing of PUT DATA commands before processing the GENERATE AC command. Possible values are 'completed' or 'not completed'. In the latter case, this status is not specific about which of the PUT DATA commands failed, or about how many of these commands have failed or succeeded.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF810F value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_DS_AC_TYPE									0x9F918539				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains the AC type indicated by the Terminal fro which IDS data must be stored in the Card.<br>Bits8-7 : b00 (AAC), b01 (TC), b10 (ARQC), b11 (RFU).<br>	- Bits 6-1 : RFU.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8108 value in the MasterCard Kernel C2 specification. */

// Data Exchange
#define TAG_PAYPASS_DATA_STORAGE			    					0x9F918540				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indications Data storage mechanism supported by the application. Default is to support SDS and IDS.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_DATA_EXCHANGE				    				0x9F918541				/*!< <b>OBSOLETE TAG</b><br><b>Note this tag is now obsolete, as the Data Exchange is an implementation option and cannot be disabled.</b><br><br>PAYPASS - Indication that the terminal application supported Data Exchange mechanism as defined in Kernel C2.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_DS_IDS_STATUS								0x9F918545				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates if the transaction performs an IDS read and/or write.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8128 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_DS_PROCEED_TO_FIRST_WRITE						0x9F91854B				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates that the Terminal will send no more requests to read data other than as indicated in Tags To Read. This data item indicates the point at which the kernel shifts from the Card reading phase to the Card writing pahse. <br>	- If it is not present or is present with non zero length and value different from zero, then the kernel proceeds without waiting.<br>	- If it is present with zero length, then the kernel sends a DEK signal to the application and waits for the DET sinal.<br>	- If it is present with non zero length and value equal to zero, then the kernel waits for a DET signal from the application without sending a DEK signal.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8110 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_TIME_OUT_VALUE									0x9F91854C				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Defines the time in ms befaore the timer generates a TIMEOUT signal.<br><br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8127 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_DATA_EXCHANGE_CUSTOM					        0x9F91854D				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the how the kernel shall call the custom application for data exchange (value is a \ref T_PAYPASS_DATA_EXCHANGE_CUSTOM structure).<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_CANCEL_DE_TIME_OUT_VALUE				        0x9F91854E				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Defines the time in ms before the kernel times out waiting for the payment application to respond to a Data Exchange Service Call. Note that since the application has not responded to a kernel sub task call the kernel must reset the terminal after this timer expires.<br><br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal.<br> */

#define TAG_PAYPASS_CONSTRUCTED_DRDOL_VALUE							0x9F918560				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Value of the constructed DRDOL (using terminal data).<br><br>	- Format : b.<br>	- Length : up to 256 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8113 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS				0x9F918561				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Maximum number of records that can be contained in the torn transaction log.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF811D value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_NUMBER_OF_TORN_TXN_LOG_RECORDS					0x9F918562				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Number of records stored in the torn transaction log.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_IS_TORN_RECORD_TAG_LIST							0x9F918563				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - List of transaction data needed by the custom application to identify if the current transaction appears in the torn transaction log.<br><br>	- Format : b.<br>	- Length : var up to 32 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_TORN_RECORD_TAG_LIST							0x9F918564				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - List of transaction data that is stored in a torn record.<br><br>	- Format : b.<br>	- Length : var up to 256 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_MAX_LIFETIME_OF_TORN_TXN_LOG_RECORD				0x9F918565				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Maximum time, in seconds, that a record can remain in the Torn Transaction Log.<br><br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF811C value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_RECOVER_AC_SW_NOT_9000						0x9F918566				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Internal tag indicating if the card did not returned SW=9000 to the Recover AC. It is set to 1 if it is the case. If the tag is not present or set to 0, it means it is not the case.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_DO_NOT_REMOVE_TORN_RECORD					0x9F918567				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Internal tag indicating if the Torn Record shall not be removed from the Torn Log (1 if shall not be removed, 0 or absent indicates the record shall be removed).<br>Note that this tag is unknow from the kernel and is provided just as indication for Torn Management.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_PAYPASS_HOLD_TIME_VALUE									0x9F918568				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Indicates the time that the field is to be turned off after the transaction is completed if requested to do so by the cardholder device. The Hold Time Value is in units of 100ms.<br><br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8130 value in the MasterCard Kernel C2 specification. */

#define TAG_PAYPASS_DATA_RECORD										0xBF918501				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The data record is a list of TLV encoded data objects returned with the Outcome Parameter Set on the completion of transaction processing.<br><br>	- Format : b.<br>	- Length : var up to 512 bytes.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xFF8105 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_DISCRETIONARY_DATA								0xBF918502				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - The discretionary data is a list of Kernel-specific data objects sent to the Terminal as a separate field in the OUT signal.<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xFF8106 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_TORN_RECORD										0xBF918503				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - A torn record is a list of TLV encoded data objects. A torn record contains the transaction data to add in the torn transaction log.<br><br>	- Format : b.<br>	- Length : var up to 2048 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_OLD_TORN_RECORD									0xBF918504				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - An old torn record is a torn record that has been removed from the torn transaction log.<br><br>	- Format : b.<br>	- Length : var up to 2048 bytes .<br>	- Source : Terminal. */
#define TAG_PAYPASS_TORN_RECORD_IN_DISCRETIONARY_DATA				0xBF918505				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Torn record that has been added in the discretionnary data (contains the torn record or the old torn record).<br><br>	- Format : b.<br>	- Length : var up to 2048 bytes .<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xFF8101 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_DS_TAGS_TO_READ									0xBF918506				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - List of tags that the terminal requires to be read from the card.<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8112 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_DS_TAGS_TO_READ_YET							0xBF918507				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - List of tags that the terminal still needs to be read from the card. This cumulative list can be appended with tags from additional DET signals.<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Terminal. */
#define TAG_PAYPASS_DS_TAGS_TO_WRITE_AFTER_GENAC					0xBF918508				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Contains the Terminal data writing requests to be sent to the Card after processing the GENERATE AC command or the RECOVER AC command. The value of this data object is composed of a series of TLVs.<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xFF8103 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_DS_TAGS_TO_WRITE_YET_AFTER_GENAC				0xBF918509				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - List of data objects that contains the accumulated Terminal data writing requests received in Tags To Write After Gen AC.<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Terminal. */
#define TAG_PAYPASS_DS_TAGS_TO_WRITE_BEFORE_GENAC					0xBF91850A				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - List of data objects indicating the Terminal data writing requests to be sent to the Card before processing the GENERATE AC command or the RECOVER AC command.<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xFF8102 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_DS_TAGS_TO_WRITE_YET_BEFORE_GENAC				0xBF91850B				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - List of data objects that contains the accumulated Terminal data writing requests received in Tags To Write Before Gen AC.<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Terminal. */
#define TAG_PAYPASS_DS_DATA_TO_SEND									0xBF91850C				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - List of data objects that contains the accumulated data sent by the Kernel to the Terminal in a DEK signal. These data may correspond to Terminal reading requests, obtained from the Card by means of GET DATA or READ RECORD commands, or may correspond to data that the Kernel posts to the Terminal as part of its own processing.<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xFF8104 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_DS_DATA_NEEDED								0xBF91850D				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - List of tags included in the DEK signal to request information from the Terminal.<br><br>	- Format : b.<br>	- Length : var.<br>	- Source : Terminal.<br><br>Note this tag is defined with 0xDF8106 value in the MasterCard Kernel C2 specification. */
#define TAG_PAYPASS_INT_DEK_SIGNAL									0xBF91850E				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Internal tag containing a DEK Signal sent by the reader to the application. Only applicable if Data Exchange is supported. (several tags can be present).<br><br>	- Format : b.<br>	- Length : up to 261 bytes.<br>	- Source : Terminal. */
#define TAG_PAYPASS_INT_DET_SIGNAL									0xBF91850F				/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Internal tag containing a DET Signal sent by the application to the reader. Only applicable if Data Exchange is supported. (several tags can be present).<br><br>	- Format : b.<br>	- Length : up to 261 bytes.<br>	- Source : Terminal. */
//! @}


//! \addtogroup PayPassPossibleCvm
//! @{
#define PAYPASS_CVM_NO_CVM											0x01					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - "No CVM" method has been applied. */
#define PAYPASS_CVM_SIGNATURE										0x02					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - "Signature" method has been applied. */
#define PAYPASS_CVM_ONLINE_PIN										0x04					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - "Online PIN" method has been applied. */
//! @}


//! \addtogroup PayPassPossibleOutcomes
//! @{
#define PAYPASS_OUTCOME_APPROVED									0x01					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - The PayPass reader is satisfied that the transaction is acceptable with the selected card application and wants the transaction to be offline approved. */
#define PAYPASS_OUTCOME_ONLINE_REQUEST								0x02					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - The PayPass reader has found that the transaction requires an online authorization. */
#define PAYPASS_OUTCOME_DECLINED									0x03					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - The PayPass reader has found that the transaction is not acceptable with the selected card application and wants the transaction to be offline declined. */
#define PAYPASS_OUTCOME_TRY_ANOTHER_INTERFACE						0x04					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - The PayPass reader is unable to complete the transaction with the selected card application, but knows that another interface (e.g. contact or magnetic-stripe) may be available. */
#define PAYPASS_OUTCOME_END_APPLICATION								0x05					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - The PayPass reader experienced an application error (e.g. missing data) */
#define PAYPASS_OUTCOME_SELECT_NEXT									0x06					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - The PayPass reader expects the reader to select the next matching application in the candidate list. */
#define PAYPASS_OUTCOME_TRY_AGAIN									0x07					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - The PayPass reader indicates the transaction shall be restarted due to a communication error. */
//! @}


//! \addtogroup PayPassPossibleOdaMethods
//! @{
#define PAYPASS_MCHIP_ODA_METHOD_NONE								0x00					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - Value for \a TAG_PAYPASS_INT_MCHIP_ODA_METHOD indicating no ODA method has been selected. */
#define PAYPASS_MCHIP_ODA_METHOD_SDA								0x01					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - Value for \a TAG_PAYPASS_INT_MCHIP_ODA_METHOD indicating SDA method has been selected. */
#define PAYPASS_MCHIP_ODA_METHOD_CDA								0x02					/*!< <b>OBSOLETE WITH KERNEL C2</b><br>PAYPASS - Value for \a TAG_PAYPASS_INT_MCHIP_ODA_METHOD indicating CDA method has been selected. */
//! @}


//! \addtogroup PayPassPossibleCardTypes
//! @{
#define PAYPASS_B1_CARD_ID											0x85					/*!< PAYPASS - First byte of \a TAG_KERNEL_CARD_TYPE tag indicating this is a Paypass card. PayPass kernel always sets the first byte with this define. */
#define PAYPASS_B2_CARD_TYPE_MSTRIPE								0x01					/*!< PAYPASS - Second byte of \a TAG_KERNEL_CARD_TYPE tag indicating this is a Paypass MStripe card. */
#define PAYPASS_B2_CARD_TYPE_MCHIP									0x02					/*!< PAYPASS - Second byte of \a TAG_KERNEL_CARD_TYPE tag indicating this is a Paypass MChip card. */
#define PAYPASS_B2_MASK_ON_DEVICE_CVM_SUPPORTED						0x80					/*!< <b>NEW WITH KERNEL C2</b><br>PAYPASS - Mask on the second byte of \a TAG_KERNEL_CARD_TYPE tag, that indicates the presented device supports the CVM itself (mobile for example). */
//! @}


//! \addtogroup PayPass3OutcomeParameterSet
//! @{
#define PAYPASS_OPS_LENGTH											(8)						/*!< PAYPASS - Length of \ref TAG_PAYPASS_OUTCOME_PARAMETER_SET tag. */

#define PAYPASS_OPS_STATUS_BYTE										(0)						/*!< PAYPASS - Byte number in OPS for status (first byte). */
#define PAYPASS_OPS_STATUS_APPROVED									0x10					/*!< PAYPASS - Indicates the transaction is approved. */
#define PAYPASS_OPS_STATUS_DECLINED									0x20					/*!< PAYPASS - Indicates the transaction is declined. */
#define PAYPASS_OPS_STATUS_ONLINE_REQUEST							0x30					/*!< PAYPASS - Indicates the transaction is sent online for authorisation. */
#define PAYPASS_OPS_STATUS_END_APPLICATION							0x40					/*!< PAYPASS - Indicates the transaction is terminated. */
#define PAYPASS_OPS_STATUS_SELECT_NEXT								0x50					/*!< PAYPASS - Indicates the transaction need to select the next AID in the candidate list. */
#define PAYPASS_OPS_STATUS_TRY_ANOTHER_INTERFACE					0x60					/*!< PAYPASS - Indicates the transaction should be tried over another interface. */
#define PAYPASS_OPS_STATUS_TRY_AGAIN								0x70					/*!< PAYPASS - Indicates the transaction has to be restarted again. */
#define PAYPASS_OPS_STATUS_NA										0xF0					/*!< PAYPASS - Transaction status is not applicable. */

#define PAYPASS_OPS_START_BYTE										(1)						/*!< PAYPASS - Byte number in OPS for start (second byte). */
#define PAYPASS_OPS_START_A											0x00					/*!< PAYPASS - Transaction needs to start at A. Not returned by PayPass kernel. */
#define PAYPASS_OPS_START_B											0x10					/*!< PAYPASS - Transaction needs to start at B. It is required when the transaction needs to restart from the beginning (e.g. retry due to a communication error with the card, or restart for a second tap). */
#define PAYPASS_OPS_START_C											0x20					/*!< PAYPASS - Transaction needs to start at C. It is required when transaction needs to be restared using the next available AID (i.e. equivalent of SELECT NEXT). */
#define PAYPASS_OPS_START_D											0x30					/*!< PAYPASS - Transaction needs to start at D. Not returned by PayPass kernel. */
#define PAYPASS_OPS_START_NA										0xF0					/*!< PAYPASS - Transaction start is not applicable (i.e. transaction is completed or terminated, and does not need to be restarted). */

#define PAYPASS_OPS_ONLINE_RESPONSE_DATA_BYTE						(2)						/*!< PAYPASS - Byte number in OPS for online response data (third byte). */
#define PAYPASS_OPS_ONLINE_RESPONSE_DATA_NA							0xF0					/*!< PAYPASS - Online response data is not applicable. */

#define PAYPASS_OPS_CVM_BYTE										(3)						/*!< PAYPASS - Byte number in OPS for CVM result (fourth byte). */
#define PAYPASS_OPS_CVM_NO_CVM										0x00					/*!< PAYPASS - Transaction CVM indicates no CVM is required. */
#define PAYPASS_OPS_CVM_SIGNATURE									0x10					/*!< PAYPASS - Transaction CVM indicates signature is required. */
#define PAYPASS_OPS_CVM_ONLINE_PIN									0x20					/*!< PAYPASS - Transaction CVM indicates Online PIN is required. */
#define PAYPASS_OPS_CVM_CONFIRMATION_CODE_VERIFIED					0x30					/*!< PAYPASS - Transaction CVM indicates confirmation code has been veirified. */
#define PAYPASS_OPS_CVM_NA											0xF0					/*!< PAYPASS - Transaction CVM indicates is not applicable. */

#define PAYPASS_OPS_DATA_PRESENCE_BYTE								(4)						/*!< PAYPASS - Byte number in OPS for data presence (fifth byte). */
#define PAYPASS_OPS_DATA_PRESENCE_MASK_UIR_ON_OUTCOME				0x80					/*!< PAYPASS - A specific GUI is requested on outcome. */
#define PAYPASS_OPS_DATA_PRESENCE_MASK_UIR_ON_RESTART				0x40					/*!< PAYPASS - A specific GUI is requested on restart. */
#define PAYPASS_OPS_DATA_PRESENCE_MASK_DATA_RECORD					0x20					/*!< PAYPASS - Data record is present in the outcome data. */
#define PAYPASS_OPS_DATA_PRESENCE_MASK_DISCRET_DATA					0x10					/*!< PAYPASS - Discretionary Data is present in the outcome data. */
#define PAYPASS_OPS_DATA_PRESENCE_MASK_RECEIPT						0x08					/*!< PAYPASS - Receipt is required. */

#define PAYPASS_OPS_ALTERNATIVE_INTERFACE_PREF_BYTE					(5)						/*!< PAYPASS - Byte number in OPS for alternative interface preference (sixth byte). */
#define PAYPASS_OPS_ALTERNATIVE_INTERFACE_PREF_NA					0xF0					/*!< PAYPASS - The alternative interface preference is not applicable. */

#define PAYPASS_OPS_FIELD_OFF_REQUEST_BYTE							(6)						/*!< PAYPASS - Byte number in OPS for field off request (seventh byte). */
#define PAYPASS_OPS_FIELD_OFF_REQUEST_NA							0xFF					/*!< PAYPASS - The field off request is not applicable. */

#define PAYPASS_OPS_REMOVAL_TIMEOUT_BYTE							(7)						/*!< PAYPASS - Byte number in OPS for removal timeout (eighth byte). */
//! @}


//! \addtogroup PayPass3UserInterfaceRequestData
//! @{
#define PAYPASS_UIRD_LENGTH											(22)					/*!< PAYPASS - Length of \ref TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA tag. */

#define PAYPASS_UIRD_MESSAGE_ID_BYTE								(0)						/*!< PAYPASS - Byte number in UIRD for message identifier (first byte). */
#define PAYPASS_UIRD_MESSAGE_ID_CARD_READ_OK						0x17					/*!< PAYPASS - Indicates the card has been read. */
#define PAYPASS_UIRD_MESSAGE_ID_TRY_AGAIN							0x21					/*!< PAYPASS - Indicates the card has to be presented again. */
#define PAYPASS_UIRD_MESSAGE_ID_APPROVED							0x03					/*!< PAYPASS - Indicates the transaction is approved. */
#define PAYPASS_UIRD_MESSAGE_ID_APPROVED_SIGN						0x1A					/*!< PAYPASS - Indicates the transaction is approved but signature required. */
#define PAYPASS_UIRD_MESSAGE_ID_DECLINED							0x07					/*!< PAYPASS - Indicates the transaction is declined. */
#define PAYPASS_UIRD_MESSAGE_ID_ERROR_OTHER_CARD					0x1C					/*!< PAYPASS - Indicates the an error occured and the cardholder shall use another card. */
#define PAYPASS_UIRD_MESSAGE_ID_SEE_PHONE							0x20					/*!< PAYPASS - Indicates the cardholder shall see his phone for instructions. */
#define PAYPASS_UIRD_MESSAGE_ID_AUTHORISING_PLEASE_WAIT				0x1B					/*!< PAYPASS - Indicates the cardholder the transaction is sent online for authorisation. */
#define PAYPASS_UIRD_MESSAGE_ID_INSERT_CARD							0x1D					/*!< PAYPASS - Indicates the cardholder has to insert his card. */
#define PAYPASS_UIRD_MESSAGE_ID_CLEAR_DISPLAY						0x1E					/*!< PAYPASS - Indicates the display shall be cleared. */
#define PAYPASS_UIRD_MESSAGE_ID_NA									0xFF					/*!< PAYPASS - Message identifier is not applicable. */

#define PAYPASS_UIRD_STATUS_BYTE									(1)						/*!< PAYPASS - Byte number in UIRD for status (second byte). */
#define PAYPASS_UIRD_STATUS_NOT_READY								0x00					/*!< PAYPASS - Reader is ready. */
#define PAYPASS_UIRD_STATUS_IDLE									0x01					/*!< PAYPASS - Reader is idle. */
#define PAYPASS_UIRD_STATUS_READY_TO_READ							0x02					/*!< PAYPASS - Reader is ready to read the card. */
#define PAYPASS_UIRD_STATUS_PROCESSING								0x03					/*!< PAYPASS - Transaction is in progress. */
#define PAYPASS_UIRD_STATUS_CARD_READ_SUCCESSFULLY					0x04					/*!< PAYPASS - Card has been read successfully. */
#define PAYPASS_UIRD_STATUS_PROCESSING_ERROR						0x05					/*!< PAYPASS - An error occured. */
#define PAYPASS_UIRD_STATUS_NA										0xFF					/*!< PAYPASS - Status for UIRD is not applicable. */

#define PAYPASS_UIRD_HOLD_TIME_OFFSET								(2)						/*!< PAYPASS - Byte number in OPS for CVM result (third byte, on 3 bytes). */
#define PAYPASS_UIRD_HOLD_TIME_LENGTH								(3)						/*!< PAYPASS - Length of "Hold Time" field in the \ref TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA tag. */

#define PAYPASS_UIRD_LANGUAGE_PREFERENCE_OFFSET						(5)						/*!< PAYPASS - Byte number in OPS for CVM result (sixth byte, on 8 bytes). */
#define PAYPASS_UIRD_LANGUAGE_PREFERENCE_LENGTH						(8)						/*!< PAYPASS - Length of "Language Preference" field in the \ref TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA tag. */

#define PAYPASS_UIRD_VALUE_QUALIFIER_BYTE							(13)					/*!< PAYPASS - Byte number in OPS for online response data (forteenth byte). */
#define PAYPASS_UIRD_VALUE_QUALIFIER_NONE							0x00					/*!< PAYPASS - No data has to be displayed. */
#define PAYPASS_UIRD_VALUE_QUALIFIER_AMOUNT							0x10					/*!< PAYPASS - Amount has to be displayed. */
#define PAYPASS_UIRD_VALUE_QUALIFIER_BALANCE						0x20					/*!< PAYPASS - Card balance has to be displayed. */

#define PAYPASS_UIRD_VALUE_OFFSET									(14)					/*!< PAYPASS - Value of the qualifier, if applicable (fifteenth byte, on 6 bytes). */
#define PAYPASS_UIRD_VALUE_LENGTH									(6)						/*!< PAYPASS - Length of "Value" field in the \ref TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA tag. */

#define PAYPASS_UIRD_CURRENCY_CODE_OFFSET							(20)					/*!< PAYPASS - Value of the currency code, if applicable (twentyth byte, on 2 bytes). */
#define PAYPASS_UIRD_CURRENCY_CODE_LENGTH							(2)						/*!< PAYPASS - Length of "Curreny Code" field in the \ref TAG_PAYPASS_USER_INTERFACE_REQUEST_DATA tag. */
//! @}

//! \addtogroup PayPass3ErrorIndication
//! @{
#define PAYPASS_EI_LENGTH											(6)						/*!< PAYPASS - Length of \ref TAG_PAYPASS_ERROR_INDICATION tag. */

#define PAYPASS_EI_L1_BYTE											(0)						/*!< PAYPASS - Byte number in EI for status (first byte). It concerns the L1 error indication. */
#define PAYPASS_EI_L1_OK											0x00					/*!< PAYPASS - All is OK. */
#define PAYPASS_EI_L1_TIMEOUT_ERROR									0x01					/*!< PAYPASS - Indicates the timeout for card response reception has been elapsed. */
#define PAYPASS_EI_L1_TRANSMISSION_ERROR							0x02					/*!< PAYPASS - A transmission error occurred. */
#define PAYPASS_EI_L1_PROTOCOL_ERROR								0x03					/*!< PAYPASS - A protocol error occurred. */

#define PAYPASS_EI_L2_BYTE											(1)						/*!< PAYPASS - Byte number in EI for status (second byte). */
#define PAYPASS_EI_L2_OK											0x00					/*!< PAYPASS - Processing is OK. */
#define PAYPASS_EI_L2_CARD_DATA_MISSING								0x01					/*!< PAYPASS - A card data is missing. */
#define PAYPASS_EI_L2_CAM_FAILED									0x02					/*!< PAYPASS - An error occurred when doing the ODA. */
#define PAYPASS_EI_L2_STATUS_BYTES									0x03					/*!< PAYPASS - Card returned a bad SW. */
#define PAYPASS_EI_L2_PARSING_ERROR									0x04					/*!< PAYPASS - Card response does not correctly parse. */
#define PAYPASS_EI_L2_MAX_LIMIT_EXCEEDED							0x05					/*!< PAYPASS - Cless Transaction Limit is exceeded. */
#define PAYPASS_EI_L2_CARD_DATA_ERROR								0x06					/*!< PAYPASS - Card returned an invalid data. */
#define PAYPASS_EI_L2_MAGSTRIPE_NOT_SUPPORTED						0x07					/*!< PAYPASS - MStripe cannot be used for the transaction. */
#define PAYPASS_EI_L2_NO_PPSE										0x08					/*!< PAYPASS - NOT USED. */
#define PAYPASS_EI_L2_PPSE_FAULT									0x09					/*!< PAYPASS - NOT USED. */
#define PAYPASS_EI_L2_EMPTY_CANDIDATE_LIST							0x0A					/*!< PAYPASS - NOT USED. */
#define PAYPASS_EI_L2_IDS_READ_ERROR								0x0B					/*!< PAYPASS - NOT USED. */
#define PAYPASS_EI_L2_IDS_WRITE_ERROR								0x0C					/*!< PAYPASS - NOT USED. */
#define PAYPASS_EI_L2_IDS_DATA_ERROR								0x0D					/*!< PAYPASS - NOT USED. */
#define PAYPASS_EI_L2_IDS_NO_MATCHING_AC							0x0E					/*!< PAYPASS - NOT USED. */
#define PAYPASS_EI_L2_TERMINAL_DATA_ERROR							0x0F					/*!< PAYPASS - Terminal provided an invalid data. */

#define PAYPASS_EI_L3_BYTE											(2)						/*!< PAYPASS - Byte number in EI for status (third byte). */
#define PAYPASS_EI_L3_OK											0x00					/*!< PAYPASS - AProcessing is OK. */
#define PAYPASS_EI_L3_TIMEOUT										0x01					/*!< PAYPASS - NOT USED. */
#define PAYPASS_EI_L3_STOP											0x02					/*!< PAYPASS - NOT USED. */
#define PAYPASS_EI_L3_AMOUNT_NOT_PRESENT							0x03					/*!< PAYPASS - Transaction amount s not present. */

#define PAYPASS_EI_SW12_OFFSET										(3)						/*!< PAYPASS - Byte number in EI for status (fourth byte, on 2 bytes). */
#define PAYPASS_EI_SW12_LENGTH										(2)						/*!< PAYPASS - Length of the "SW12" field in EI. */

#define PAYPASS_EI_MSG_ON_ERROR_BYTE								(5)						/*!< PAYPASS - Byte number in EI for "Msg On Error" (sixth byte). */
//! @}


//! \addtogroup PayPass3KernelConfiguration
//! @{
#define PAYPASS_KERNEL_CONFIGURATION_SUPPORT_MCHIP_MSTRIPE			0x00					/*!< PAYPASS - Indicates both MChip and MStripe are supported. */
#define PAYPASS_KERNEL_CONFIGURATION_SUPPORT_MCHIP_ONLY				0x80					/*!< PAYPASS - Indicates MChip only is supported. */
#define PAYPASS_KERNEL_CONFIGURATION_SUPPORT_MSTRIPE_ONLY			0x40					/*!< PAYPASS - Indicates MStripe only is supported. */
#define PAYPASS_KERNEL_CONFIGURATION_SUPPORT_ON_DEVICE_CVM			0x20					/*!< PAYPASS - Indicates 'On device cardholder verification' is supported. */
//! @}


//! \addtogroup PayPass3OdaStatus
//! @{
#define PAYPASS_ODA_STATUS_NONE										0x00					/*!< PAYPASS - Indicates no ODA is to be performed during the transaction. */
#define PAYPASS_ODA_STATUS_CDA										0x80					/*!< PAYPASS - Indicates CDA is to be performed during the transaction. */
//! @}


//! \addtogroup PayPass3ApplicationCapabilitiesInformation
//! @{
#define PAYPASS_ACI_B1												0						/*!< PAYPASS : Application Capabilities Information - Byte 1. */
#define PAYPASS_ACI_B1_ACI_VERSION_NUMBER_MASK						0xF0					/*!< PAYPASS : Application Capabilities Information - Mask of the ACI version number. */
#define PAYPASS_ACI_B1_DS_VERSION_NUMBER_MASK						0x0F					/*!< PAYPASS : Application Capabilities Information - Mask of the Data Storage version number. */
#define PAYPASS_ACI_B1_DS_NOT_SUPPORTED								0x00					/*!< PAYPASS : Application Capabilities Information - Data Storage version number that indicates data storage is not supported. */
#define PAYPASS_ACI_B1_DS_VERSION_1_SUPPORTED						0x01					/*!< PAYPASS : Application Capabilities Information - Card supports Data Storage version 1. */
#define PAYPASS_ACI_B1_DS_VERSION_2_SUPPORTED						0x02					/*!< PAYPASS : Application Capabilities Information - Card supports Data Storage version 2. */

#define PAYPASS_ACI_B2												1						/*!< PAYPASS : Application Capabilities Information - Byte 2. */
#define PAYPASS_ACI_B2_SUPPORT_FIELD_OFF_DETECTION_MASK				0x04					/*!< PAYPASS : Application Capabilities Information - Supports for field off detection (b'1'). */
#define PAYPASS_ACI_B2_SUPPORT_BALANCE_READING_MASK					0x02					/*!< PAYPASS : Application Capabilities Information - Supports for balance reading (b'1'). */
#define PAYPASS_ACI_B2_CDA_SUPPORTED_OVER_TC_ARQC_AAC_MASK			0x01					/*!< PAYPASS : Application Capabilities Information - CDA indicator that indicates if card supports CDA over TC, ARQC and AAC (b'1'). If not, it supports CDA as in EMV (b'0'). */

#define PAYPASS_ACI_B3												2						/*!< PAYPASS : Application Capabilities Information - Byte 3 (SDS Scheme Indicator). */
#define PAYPASS_ACI_B3_UNDEFINED_SDS_CONFIGURATION					0x00					/*!< PAYPASS : Application Capabilities Information - Undefined SDS configuration */
#define PAYPASS_ACI_B3_ALL_10_TAGS_32_BYTES							0x01					/*!< PAYPASS : Application Capabilities Information - All 10 tags 32 bytes. */
#define PAYPASS_ACI_B3_ALL_10_TAGS_48_BYTES							0x02					/*!< PAYPASS : Application Capabilities Information - All 10 tags 48 bytes. */
#define PAYPASS_ACI_B3_ALL_10_TAGS_64_BYTES							0x03					/*!< PAYPASS : Application Capabilities Information - All 10 tags 64 bytes. */
#define PAYPASS_ACI_B3_ALL_10_TAGS_96_BYTES							0x04					/*!< PAYPASS : Application Capabilities Information - All 10 tags 96 bytes. */
#define PAYPASS_ACI_B3_ALL_10_TAGS_128_BYTES						0x05					/*!< PAYPASS : Application Capabilities Information - All 10 tags 128 bytes. */
#define PAYPASS_ACI_B3_ALL_10_TAGS_160_BYTES						0x06					/*!< PAYPASS : Application Capabilities Information - All 10 tags 160 bytes. */
#define PAYPASS_ACI_B3_ALL_10_TAGS_192_BYTES						0x07					/*!< PAYPASS : Application Capabilities Information - All 10 tags 192 bytes. */
#define PAYPASS_ACI_B3_ALL_SDS_TAGS_32_BYTES_EXCEPT_9F78			0x08					/*!< PAYPASS : Application Capabilities Information - All SDS tags 32 bytes except '9F78' which is 64 bytes. */
//! @}

//! \addtogroup PayPass3DataStorageTypes
//! @{
#define PAYPASS_DS_DISABLE_NONE										0x00					/*!< PAYPASS -  No Data Storage supported */
#define PAYPASS_DS_DISABLE_IDS										0x80					/*!< PAYPASS -  Integrated Data Storage */
//! @}

//! \addtogroup PayPass3IDSStatusModes
//! @{
#define PAYPASS_IDS_STATUS_NONE										0x00					/*!< PAYPASS -  IDS Status no Read or Write specified */
#define PAYPASS_IDS_STATUS_READ										0x80					/*!< PAYPASS -  IDS Status Read (bit 8 set) */
#define PAYPASS_IDS_STATUS_WRITE									0x40					/*!< PAYPASS -  IDS Status Write (bit 7 set) */
//! @}

//! \addtogroup PayPass3DSSummaryStatusModes
//! @{
#define PAYPASS_DS_SUMMARY_STATUS_NONE								0x00					/*!< PAYPASS -  DS Summary Status with no flag set. */
#define PAYPASS_DS_SUMMARY_SUCCESSFUL_READ							0x80					/*!< PAYPASS -  DS Summary Status indicating successful 'Read' (bit 8 set) */
#define PAYPASS_DS_SUMMARY_SUCCESSFUL_WRITE							0x40					/*!< PAYPASS -  DS Summary Status indicating successful 'Write' (bit 7 set) */
//! @}

//! \addtogroup PayPass3PostGENACPutDataStatusModes
//! @{
#define PAYPASS_POST_GEN_AC_PUT_DATA_STATUS_NONE					0x00					/*!< PAYPASS -  Post GENAC Put Data Status not specified */
#define PAYPASS_POST_GEN_AC_PUT_DATA_STATUS_COMPLETED				0x80					/*!< PAYPASS -  Post GENAC Put Data Status Completed (bit 8 set) */
//! @}

//! \addtogroup PayPass3PreGENACPutDataStatusModes
//! @{
#define PAYPASS_PRE_GEN_AC_PUT_DATA_STATUS_NONE						0x00					/*!< PAYPASS -  Pre GENAC Put Data Status not specified */
#define PAYPASS_PRE_GEN_AC_PUT_DATA_STATUS_COMPLETED				0x80					/*!< PAYPASS -  Pre GENAC Put Data Status Completed (bit 8 set) */
//! @}

//! \addtogroup PayPass3DsOdsInfoForReader
//! @{
#define PAYPASS_DS_ODS_INFO_KERNEL_FLAG_USABLE_FOR_TC				0x80					/*!< PAYPASS -  'Usable for TC' flag in \ref TAG_PAYPASS_INT_DS_ODS_INFO_FOR_KERNEL */
#define PAYPASS_DS_ODS_INFO_KERNEL_FLAG_USABLE_FOR_ARQC				0x40					/*!< PAYPASS -  'Usable for ARQC' flag in \ref TAG_PAYPASS_INT_DS_ODS_INFO_FOR_KERNEL */
#define PAYPASS_DS_ODS_INFO_KERNEL_FLAG_USABLE_FOR_AAC				0x20					/*!< PAYPASS -  'Usable for AAC' flag in \ref TAG_PAYPASS_INT_DS_ODS_INFO_FOR_KERNEL */
#define PAYPASS_DS_ODS_INFO_KERNEL_FLAG_STOP_IF_NO_DS_ODS_TERM		0x04					/*!< PAYPASS -  'Stop if no DS ODS Term' flag in \ref TAG_PAYPASS_INT_DS_ODS_INFO_FOR_KERNEL */
#define PAYPASS_DS_ODS_INFO_KERNEL_FLAG_STOP_IF_WRITE_FAILED		0x02					/*!< PAYPASS -  'Stop if write failed' flag in \ref TAG_PAYPASS_INT_DS_ODS_INFO_FOR_KERNEL */
//! @}

//! \addtogroup PayPass3DsSlotManagementControl
//! @{
#define PAYPASS_DS_SLOT_MNGT_CTRL_FLAG_PERMANENT_SLOT_TYPE			0x80					/*!< PAYPASS -  'Permanent Slot Type' flag in \ref TAG_PAYPASS_DS_SLOT_MANAGEMENT_CONTROL */
#define PAYPASS_DS_SLOT_MNGT_CTRL_FLAG_VOLATILE_SLOT_TYPE			0x40					/*!< PAYPASS -  'Volatile Slot Type' flag in \ref TAG_PAYPASS_DS_SLOT_MANAGEMENT_CONTROL */
#define PAYPASS_DS_SLOT_MNGT_CTRL_FLAG_LOW_VOLATILITY				0x20					/*!< PAYPASS -  'Low Volatility' flag in \ref TAG_PAYPASS_DS_SLOT_MANAGEMENT_CONTROL */
#define PAYPASS_DS_SLOT_MNGT_CTRL_FLAG_LOCKED_SLOT					0x10					/*!< PAYPASS -  'Locked Slot' flag in \ref TAG_PAYPASS_DS_SLOT_MANAGEMENT_CONTROL */
#define PAYPASS_DS_SLOT_MNGT_CTRL_FLAG_DEACTIVATED_SLOT				0x01					/*!< PAYPASS -  'Deactivated Slot' flag in \ref TAG_PAYPASS_DS_SLOT_MANAGEMENT_CONTROL */
//! @}

//! \addtogroup PayPass3DsOdsInfoFlags
//! @{
#define PAYPASS_DS_ODS_INFO_FLAG_PERMANENT_SLOT_TYPE				0x80					/*!< PAYPASS -  'Permanent Slot Type' flag in \ref TAG_PAYPASS_DS_ODS_INFO */
#define PAYPASS_DS_ODS_INFO_FLAG_VOLATILE_SLOT_TYPE					0x40					/*!< PAYPASS -  'Volatile Slot Type' flag in \ref TAG_PAYPASS_DS_ODS_INFO */
#define PAYPASS_DS_ODS_INFO_FLAG_LOW_VOLATILITY						0x20					/*!< PAYPASS -  'Low Volatility' flag in \ref TAG_PAYPASS_DS_ODS_INFO */
#define PAYPASS_DS_ODS_INFO_FLAG_DECLINE_IF_DS_ERROR				0x08					/*!< PAYPASS -  'Decline payment in case of data storage error' flag in \ref TAG_PAYPASS_DS_ODS_INFO */
//! @}

//! \addtogroup PayPass3DebugMaskSettings
//! @{
#define PAYPASS_DEBUG_MASK_DE_LOG									0x80					/*!< PAYPASS -  Corresponds to \ref KERNEL_DEBUG_KERNEL_SPECIFIC_2 used by PayPass kernel to indicate storage of Data Exchange Signals (DEK and DET) */
//! @}

//! \addtogroup PayPass3TagSource
//! @{
#define PAYPASS_SOURCE_DET	TAG_SOURCE_PROPRIETARY_1										/*!< PayPass specific Tag source to ensure that only DET Signal sourced tags are permitted to be stored in the database (as defined in Kernel C2 Annex A). */
//! @}


/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////

//! \addtogroup PayPass3PhoneMessageTableEntry
//!	@{

//!	\brief Defines a phone message table index
typedef struct
{
	unsigned char ucPciiMask[3];			/*!< PCII Mask */
	unsigned char ucPciiValue[3];			/*!< PCII Value */
	unsigned char ucMessage;				/*!< Message */
	unsigned char ucStatus;					/*!< Status */
} T_PAYPASS_PHONE_MESSAGE_TABLE_ENTRY;

//!	@}


/////////////////////////////////////////////////////////////////
//// Glodal Data ////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////
