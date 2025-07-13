/**
 * \file    Interac_Tags.h
 * \brief   This describes all the specific Interac contactless kernel tags.
 *
 *
 * \author	Ingenico
 * \author  Copyright (c) 2009 Ingenico, rue claude Chappe,\n
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

//! \addtogroup InteracTagsDefinedBySpec
//! @{
#define TAG_INTERAC_MERCHANT_TYPE_INDICATOR				0x9F58					/*!< INTERAC - Merchant Type Indicator (MTI). This tag provides Merchant type Indicator that is used by the card for its card risk management 5 values are possible: 01, 02, 03 04 and 05.<br>	- Format : numeric.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_INTERAC_TERMINAL_TRANSACTION_INFORMATION	0x9F59					/*!< INTERAC - Terminal Transaction Information (TTI). TTI is a value set by the acquirer and is stored in the terminal. It reflects some terminal capabilities that will be used within the transaction. <br>	- Format : b.<br>	- Length : 3 byte.<br>	- Source : Terminal.<br><br> 
																				Here is a description of the TTI bits as described in the Interac specification:<br><br>
																				TTI Byte 1:
																				<table><tr><th>b8</th><th>b7</th><th>b6</th><th>b5</th><th>b4</th><th>b3</th><th>b2</th><th>b1</th><th>Meaning</th></tr>
																				<tr><td>1</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>Reader with display capability</td>
																				<tr><td> </td><td>1</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>Interac Contact application available</td>
																				<tr><td> </td><td> </td><td>1</td><td> </td><td> </td><td> </td><td> </td><td> </td><td>Interac Contact application at other terminal</td>
																				<tr><td> </td><td> </td><td> </td><td>1</td><td> </td><td> </td><td> </td><td> </td><td>CDA supported</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td>1</td><td> </td><td> </td><td> </td><td>Offline Capable terminal (value '0' means online only terminal)</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td> </td><td>1</td><td> </td><td> </td><td>Online PIN supported</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>0</td><td> </td><td>RFU</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>0</td><td>RFU</td>
																				</table>
																				TTI Byte 2:
																				<table><tr><th>b8</th><th>b7</th><th>b6</th><th>b5</th><th>b4</th><th>b3</th><th>b2</th><th>b1</th><th>Meaning</th></tr>
																				<tr><td>0</td><td>0</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>Contactless only capable</td>
																				<tr><td>0</td><td>1</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>Contactless and Mag Stripe capable</td>
																				<tr><td>1</td><td>0</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>Contactless, Contact Chip and Mag Stripe capable</td>
																				<tr><td>1</td><td>1</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>Contactless and Contact Chip capable</td>
																				<tr><td> </td><td> </td><td>0</td><td> </td><td> </td><td> </td><td> </td><td> </td><td>RFU</td>
																				<tr><td> </td><td> </td><td> </td><td>0</td><td> </td><td> </td><td> </td><td> </td><td>RFU</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td>0</td><td> </td><td> </td><td> </td><td>RFU</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td> </td><td>0</td><td> </td><td> </td><td>RFU</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>0</td><td> </td><td>RFU</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>0</td><td>RFU</td>
																				</table>
																				TTI Byte 3: All bits RFU
																				*/
#define TAG_INTERAC_TERMINAL_TRANSACTION_TYPE   		0x9F5A					/*!< INTERAC - Terminal Transaction Type (TTT). This tag is a dynamic value set by the terminal and reflects the type of transaction performed. For Refund or Reversals set to 0x01 otherwise set to 0x00. <br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_INTERAC_RECEIPT_LIMIT		        		0x9F5D					/*!< INTERAC - Terminal Contactless Receipt Required limit, the kernel checks this limit with the amount, authorised and indicates to the application if a receipt is required. Refer to \ref TAG_INTERAC_RECEIPT_STATUS for kernel indicatation if application need to print a receipt<br>	- Format : n.<br>	- Length : 6 bytes (12 numeric digits).<br>	- Source : Terminal. */
#define TAG_INTERAC_TERMINAL_OPTION_STATUS		        0x9F5E					/*!< INTERAC - Terminal supported options (TOS) defines the conditions when the payment application will perform revert to contact.<br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal. 
																				<br><br> 
																				Here is a description of the TOS bits as described in the Interac specification:<br><br>
																				TOS Byte 1:
																				<table><tr><th>b8</th><th>b7</th><th>b6</th><th>b5</th><th>b4</th><th>b3</th><th>b2</th><th>b1</th><th>Meaning</th></tr>
																				<tr><td>1</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>Use other Interface if different Currency</td>
																				<tr><td> </td><td>1</td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>Use other Interface if differnet Country Code</td>
																				<tr><td> </td><td> </td><td>1</td><td> </td><td> </td><td> </td><td> </td><td> </td><td>Use other Interface if Domestic txn with different Currency</td>
																				<tr><td> </td><td> </td><td> </td><td>0</td><td> </td><td> </td><td> </td><td> </td><td>RFU</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td>0</td><td> </td><td> </td><td> </td><td>RFU</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td> </td><td>0</td><td> </td><td> </td><td>RFU</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>0</td><td> </td><td>RFU</td>
																				<tr><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td> </td><td>0</td><td>RFU</td>
																				</table>
																				TOS Byte 2: All Bits RFU
																				<br><br> Note that a default value of E000 is recommended
																				*/
#define TAG_INTERAC_FLOOR_LIMIT							0x9F5F					/*!< INTERAC - Floor Limit Amount used to compare against Transaction amount.  Use \ref TAG_EP_CLESS_FLOOR_LIMIT instead of this tag since Entry Point is supported. <br>	- Format : n.<br>	- Length : 6 bytes (12 numeric digits).<br>	- Source : Terminal. */
#define TAG_INTERAC_CARD_PRODUCT_CODE           	    0x9F62					/*!< INTERAC - Indicates the type of card product supported by the selected Application Identifier (AID). [RFU]<br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Card. */
#define TAG_INTERAC_CARD_TRANSACTION_INFORMATION    	0x9F63					/*!< INTERAC - CTI provide information on card decision for a specific transaction. <br>	- Format : b.<br>	- Length : 4 bytes.<br>	- Source : Card. */
#define TAG_INTERAC_FORM_FACTOR_INDICATOR				0x9F70					/*!< INTERAC - Defines the device form factor (Dual Interface card, Contactless only card, Key Fob, Mobile phone, RFU). <br>	- Format : n.<br>	- Length : 1 byte (2 numeric digits).<br>	- Source : Card. */
//! @}

//! \addtogroup InteracTagsInternallyDefined
//! @{
//#define TAG_INTERAC_XXXXX				            0x9F918A00 to 0x9F918A7F  
#define TAG_INTERAC_TERMINAL_CAPABILITIES_CVM_REQ		0x9F918A04				/*!< INTERAC - Indicates the card data input, CVM, and security capabilities of the terminal and Interac reader when the transaction amount is greater than or equal to the Terminal CVM Required Limit.<br>	- Format : b.<br>	- Length : 3 bytes.<br>	- Source : Terminal. */
#define TAG_INTERAC_TERMINAL_CAPABILITIES_NO_CVM_REQ	0x9F918A05				/*!< INTERAC - Indicates the card data input, CVM, and security capabilities of the terminal and Interac reader when the transaction amount is below the Terminal CVM Required Limit.<br>	- Format : b.<br>	- Length : 3 bytes.<br>	- Source : Terminal. */
#define TAG_INTERAC_TRANSACTION_CVM						0x9F918A06				/*!< INTERAC - Data object used to indicate to the terminal the outcome of the CVM Selection function. Possible values are "No CVM", "Signature", "Online PIN". The coding of the value is implementation specific. Refer to \ref InteracPossibleCvm for more information about the possible values.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_INTERAC_TRANSACTION_OUTCOME					0x9F918A07				/*!< INTERAC - Data object used to indicate to the terminal the outcome of the transaction processing. Possible values are "Approved", "Online Request", "Declined", "Try Another Interface" or "End Application". The coding of the value is implementation specific. Refer to \ref InteracPossibleOutcomes for more information about the possible values.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_INTERAC_RECEIPT_STATUS						0x9F918A08				/*!< INTERAC - Receipt required based on amount being greater than receipt limit (\ref TAG_INTERAC_RECEIPT_LIMIT). Receipt required inf amount >= receipt limit and approved transaction. Values (\ref INTERAC_RECEIPT_REQUIRED or \ref INTERAC_RECEIPT_NOT_REQUIRED).<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_INTERAC_INT_ODA_METHOD				        0x9F918A0E				/*!< INTERAC - Internal tag indicating the ODA selected method. Refer to \ref InteracPossibleOdaMethods for more information about the possible values.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_INTERAC_INT_DATA_PART_OF_ODA    			0x9F918A0F				/*!< INTERAC - Internal tag containing the concatenation of data that are part of authentication.<br>	- Format : b.<br>	- Length : up to 3072 bytes.<br>	- Source : Terminal. */
#define TAG_INTERAC_INT_IS_SFI_ERROR		    		0x9F918A10				/*!< INTERAC - Internal tag indicating if a record that is part of ODA is incorrectly coded or not. If there is no error, this tag is not stored.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_INTERAC_INT_TERMINAL_AVN_LIST		    	0x9F918A11				/*!< INTERAC - Internal tag indicating the list of application version number supported by the terminal. This consists of a concatenation of AVN (each of them is coded on 2 bytes).<br>	- Format : b.<br>	- Length : up to 128 bytes (i.e. up to 64 application version numbers).<br>	- Source : Terminal. */
#define TAG_INTERAC_INT_GENAC_REF_CTRL_PARAMETER	    0x9F918A12				/*!< INTERAC - Internal tag indicating the Generate AC Reference Control Parameter to be sent on the Generate AC command (result of the Terminal Action Analysis Step). Refer to \ref GenAcRefControlParameters for more information about the possible values. Note the \a EMVLIB_GENAC_RCP_CDA_MASK bit is not set in this value.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_INTERAC_INT_TAC_IAC_DEFAULT_MATCHED     	0x9F918A13				/*!< INTERAC - Internal tag indicating the TAC IAC default matched or not with the TVR (\a TRUE if it matched, \a FALSE else).<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_INTERAC_INT_GENAC_RESPONSE_DATA     		0x9F918A14				/*!< INTERAC - Internal tag containing the Generate AC card response data (content of template 0x77). This tag will be used for CDA signature generation and verification.<br>	- Format : b.<br>	- Length : up to 257 bytes.<br>	- Source : Terminal. */

#define TAG_INTERAC_INT_SENT_APDU						0x9F918A15				/*!< INTERAC - Internal tag containing an APDU sent by the reader to the contactless card (several tags can be present).<br>	- Format : b.<br>	- Length : up to 261 bytes.<br>	- Source : Terminal. */
#define TAG_INTERAC_INT_CARD_RESPONSE					0x9F918A16				/*!< INTERAC - Internal tag containing a card response (several tags can be present).<br>	- Format : b.<br>	- Length : up to 257 bytes.<br>	- Source : Terminal. */
#define TAG_INTERAC_INT_SUPPORTED_CAPK_INDEX_LIST		0x9F918A17				/*!< INTERAC - Internal tag containing the list of CA Public Key index list (concatenation of indexes (each one coded on one byte)). This tag can contain up to 64 supported key indexes.<br>	- Format : b.<br>	- Length : up to 64 bytes.<br>	- Source : Terminal. */
#define TAG_INTERAC_INT_MERCHANT_FORCE_ONLINE			0x9F918A18				/*!< INTERAC - Internal tag that indicates if the merchant wants to force the tranasction online (coded on 1 byte). If set to 01, TVR Byte 4 bit 4 is set at the begining of the Terminal Action Analysis to indicate merchant has forced the transaction online (\a 1 if merchant wishes to force transaction online, \a not \a present or \a 0 if not forced online).<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
//! @}


//! \addtogroup InteracPossibleCvm
//! @{
#define INTERAC_CVM_NO_CVM								0x01					/*!< INTERAC - "No CVM" method has been applied. */
#define INTERAC_CVM_SIGNATURE							0x02					/*!< INTERAC - "Signature" method has been applied. */
#define INTERAC_CVM_ONLINE_PIN							0x04					/*!< INTERAC - "Online PIN" method has been applied. */
//! @}


//! \addtogroup InteracPossibleOutcomes
//! @{
#define INTERAC_OUTCOME_APPROVED								0x01					/*!< INTERAC - The Interac reader is satisfied that the transaction is acceptable with the selected card application and wants the transaction to be offline approved. */
#define INTERAC_OUTCOME_ONLINE_REQUEST							0x02					/*!< INTERAC - The Interac reader has found that the transaction requires an online authorization. */
#define INTERAC_OUTCOME_DECLINED								0x03					/*!< INTERAC - The Interac reader has found that the transaction is not acceptable with the selected card application and wants the transaction to be offline declined. */
#define INTERAC_OUTCOME_TRY_ANOTHER_INTERFACE					0x04					/*!< INTERAC - The Interac reader is unable to complete the transaction with the selected card application, but knows that another interface (e.g. contact or magnetic-stripe) may be available in the same terminal. */
#define INTERAC_OUTCOME_END_APPLICATION							0x05					/*!< INTERAC - The Interac reader experienced an application error (e.g. missing data) */
#define INTERAC_OUTCOME_TRY_ANOTHER_INTERFACE_SEE_ATTENDANT		0x06					/*!< INTERAC - Merchant location supports IDP Chip & PIN transactions. Cardholder needs to perform the transaction on another terminal, display message like “PIN Entry Required – Please see Attendant” or similar message is required that would direct Cardholders to the appropriate terminal to complete their transaction. */
#define INTERAC_OUTCOME_DECLINED_CONTACT_TRANSACTION_REQUIRED	0x07					/*!< INTERAC - Merchant location does not support IDP Chip & PIN transactions and cannot be performed on another terminal, display message like,“Cannot process contactless transaction - PIN Entry Required” or similar message is required. */
//! @}


//! \addtogroup InteracPossibleOdaMethods
//! @{
#define INTERAC_ODA_METHOD_NONE					0x00					/*!< INTERAC - Value for \a TAG_INTERAC_INT_ODA_METHOD indicating no ODA method has been selected. */
#define INTERAC_ODA_METHOD_CDA					0x02					/*!< INTERAC - Value for \a TAG_INTERAC_INT_ODA_METHOD indicating CDA method has been selected. */
//! @}

//! \addtogroup InteracPossibleReceiptMode
//! @{
#define INTERAC_RECEIPT_REQUIRED				0x00					/*!< INTERAC - Value for \a TAG_INTERAC_RECEIPT_STATUS indicating a transaction receipt is required. */
#define INTERAC_RECEIPT_NOT_REQUIRED			0x01					/*!< INTERAC - Value for \a TAG_INTERAC_RECEIPT_STATUS indicating a transaction receipt is not required. */
//! @}

/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Glodal Data ////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////
