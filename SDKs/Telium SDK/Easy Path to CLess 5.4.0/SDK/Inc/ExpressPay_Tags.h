/**
 * \file    ExpressPay_Tags.h
 * \brief   This describes all the specific ExpressPay contactless kernel tags.
 *
 *
 * \author	Ingenico
 * \author  Copyright (c) 2008 Ingenico, rue claude Chappe,\n
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

//! \addtogroup ExpressPayTagsDefinedBySpec
//! @{
#define TAG_EXPRESSPAY_TERMINAL_CAPABILITIES				0x9F6D					/*!< EXPRESSPAY - Indicates the terminal's capability to support ExpressPay Magstripe or EMV Contactless. Bits 8, 7, and 4 only are used.<br> '00' = ExpressPay 1.0.<br> '40' = ExpressPay 2.0 Magstripe only.<br> '80' = ExpressPay 2.0 EMV and Magstripe.<br> 'C0' = ExpressPay Mobile.<br> Bit 4 will be set during \ref STEP_EXPRESSPAY_INITIATE_APPLI_PROCESSING step to indicate if CVM is required.<br> <br> - Format : n 2.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_TERMINAL_TRANSACTION_CAPABILITIES	0x9F6E					/*!< EXPRESSPAY - Data for managing Expresspay transactions, and includes Expresspay terminal capabilities (static data) and data around CVM (dynamic data).<br>Byte 1 Terminal Capabilities<br>	- Bit 8 : AEIPS contact mode supported<br>	- Bit 7 : Expresspay Magstripe Mode supported (Mandatory)<br>	- Bit 6 : Expresspay EMV full online mode supported<br>	- Bit 5 : Expresspay EMV partial online mode supported<br>	- Bit 4 : Expresspay Mobile supported<br>	- bits 3 to 1 : RFU<br>Byte 2 Terminal CVM Capabilities<br>	- Bit 8 : Mobile CVM<br>	- bit 7 : Online PIN<br>	- bit 6 : Signature<br>	- bit 5 : Plaintext Offline PIN<br>	- bit 4 to 1 : RFU<br>Byte 3 Transaction Capabilities<br>	- bit 8 : Terminal is offline only<br>	- bit 7 : CVM required<br>	- bit 6 to 1 : RFU<br>Byte 4 Transaction Capabilities<br>	- bit 8 to 1: RFU<br> <br> - Format : b.<br>	- Length : 4 bytes.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_CARD_INTERFACE_CAPABILITIES			0x9F70					/*!< EXPRESSPAY - Data element indicating which other interfaces are supported by the device.<br>Byte 1<br>	- Bit 8 : Keyed data entry supported<br>	- Bit 7 : Physical Magstripe supported<br>	- Bit 6 : Contact EMV interface supported<br>	- Bit 5 : Contactless interface supported<br>	- Bit 4 : Mobile interface supported<br>	- All other bits : RFU<br> <br> - Format : b.<br>	- Length : 2 bytes.<br>	- Source : Card. */
#define TAG_EXPRESSPAY_MOBILE_CVM_RESULTS					0x9F71					/*!< EXPRESSPAY - Data element returned from the Card in the GET PROCESSING OPTIONS response, indicating the status of Mobile CVM entry.<br>Byte 1 CVM Performed<br>	- '01' : Mobile CVM performed<br>	- '3F' : No CVM performed<br>Byte 2 CVM condition<br>	- '0' : Mobile CVM not required<br> - '03' : Terminal required CVM<br>Byte 3 CVM Results<br>	- '0' : Unknown<br>	- '1' : Failed<br>	- '2' : Successful<br> - '3' : Blocked<br> <br>- Format : n2.<br>	- Length : 3 bytes.<br>	- Source : Card. */
//! @}

//! \addtogroup ExpressPayTagsInternallyDefined
//! @{
#define TAG_EXPRESSPAY_UNPREDICTABLE_NUMBER_RANGE		0x9F918200				/*!< EXPRESSPAY - Allows to define the unpredictable number range (between 60 and 1200, default value is 60).<br> - Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_PSEUDO_MS_TRACK1					0x9F918201				/*!< EXPRESSPAY - Contains pseudo magnetic stripe Track 1 data generated by the kernel.
<table><tr><th>Field Name</th><th>Length</th></tr>
<tr><td>Start Sentinel</td><td><CENTER>1</CENTER></td></tr>
<tr><td>Format Code</td><td><CENTER>1</CENTER></td></tr>
<tr><td>Account Number (PAN)</td><td><CENTER>15</CENTER></td></tr>
<tr><td>Field Separator</td><td><CENTER>1</CENTER></td></tr>
<tr><td>Cardmember Name</td><td><CENTER>21</CENTER></td></tr>
<tr><td>ATC</td><td><CENTER>5</CENTER></td></tr>
<tr><td>Field Separator</td><td><CENTER>1</CENTER></td></tr>
<tr><td>Expiration Date (YYMM)</td><td><CENTER>4</CENTER></td></tr>
<tr><td>Service Code</td><td><CENTER>3</CENTER></td></tr>
<tr><td>Unpredictable Number</td><td><CENTER>4</CENTER></td></tr>
<tr><td>Discretionnary Data</td><td><CENTER>5</CENTER></td></tr>
<tr><td>End Sentinel</td><td><CENTER>1</CENTER></td></tr>
</table> */
#define TAG_EXPRESSPAY_PSEUDO_MS_TRACK2					0x9F918202				/*!< EXPRESSPAY - Contains pseudo magnetic stripe Track 2 data generated by the kernel.
<table><tr><th>Field Name</th><th>Length</th></tr>
<tr><td>Start Sentinel</td><td><CENTER>1</CENTER></td></tr>
<tr><td>Account Number (PAN)</td><td><CENTER>15</CENTER></td></tr>
<tr><td>Field Separator</td><td><CENTER>1</CENTER></td></tr>
<tr><td>Expiration Date (YYMM)</td><td><CENTER>4</CENTER></td></tr>
<tr><td>Service Code</td><td><CENTER>3</CENTER></td></tr>
<tr><td>Unpredictable Number</td><td><CENTER>4</CENTER></td></tr>
<tr><td>Discretionnary Data</td><td><CENTER>5</CENTER></td></tr>
<tr><td>ATC</td><td><CENTER>5</CENTER></td></tr>
<tr><td>End Sentinel</td><td><CENTER>1</CENTER></td></tr>
</table> */
#define TAG_EXPRESSPAY_INT_SENT_APDU					0x9F918203				/*!< EXPRESSPAY - Internal tag containing an APDU sent by the reader to the contactless card (several tags can be present).<br>	- Format : b.<br>	- Length : up to 261 bytes.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_INT_CARD_RESPONSE				0x9F918204				/*!< EXPRESSPAY - Internal tag containing a card response (several tags can be present).<br>	- Format : b.<br>	- Length : up to 257 bytes.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_INT_DATA_PART_OF_ODA				0x9F918205				/*!< EXPRESSPAY - Internal tag containing the concatenation of data that are part of authentication.<br>	- Format : b.<br>	- Length : up to 2048 bytes.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_INT_IS_SFI_ERROR					0x9F918206				/*!< EXPRESSPAY - Internal tag indicating if a record that is part of ODA is incorrectly coded or not. If there is no error, this tag is not stored.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */

#define TAG_EXPRESSPAY_INT_ODA_METHOD					0x9F918207				/*!< EXPRESSPAY - Internal tag indicating the ODA selected method.Refer to \ref ExpressPayPossibleOdaMethods for more information about the possible values.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */

#define TAG_EXPRESSPAY_INT_GENAC_REF_CTRL_PARAMETER		0x9F918208				/*!< EXPRESSPAY - Internal tag indicating the Generate AC Reference Control Parameter to be sent on the Generate AC command (result of the Terminal Action Analysis Step).Refer to \ref GenAcRefControlParameters for more information about the possible values. Note the \a EMVLIB_GENAC_RCP_CDA_MASK bit is not set in this value.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_INT_GENAC_RESPONSE_DATA			0x9F918209				/*!< EXPRESSPAY - Internal tag containing the Generate AC card response data (content of template 0x77). This tag will be used for CDA signature generation and verification.<br>	- Format : b.<br>	- Length : up to 257 bytes.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_INT_TERMINAL_AVN_LIST			0x9F91820A				/*!< EXPRESSPAY - Internal tag indicating the list of application version number supported by the terminal. This consists of a concatenation of AVN (each of them is coded on 2 bytes).<br>	- Format : b.<br>	- Length : up to 128 bytes (i.e. up to 64 application version numbers).<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_TRANSACTION_CVM					0x9F91820B				/*!< EXPRESSPAY - Data object used to indicate to the terminal the outcome of the CVM Selection function. Possible values are "No CVM", "Signature", "Online PIN". The coding of the value is implementation specific. Refer to \ref ExpressPayPossibleCvm for more information about the possible values.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_INT_TAC_IAC_DEFAULT_MATCHED		0x9F91820C				/*!< EXPRESSPAY - Internal tag indicating the TAC IAC default matched or not with the TVR (\a TRUE if it matched, \a FALSE else).<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_UNABLE_TO_GO_ONLINE				0x9F91820D				/*!< EXPRESSPAY - Tag indicating the Terminal is unable to connect to the Acquirer for online authorization (\a TRUE if unable to connect, \a FALSE else).<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_INT_OPTIMIZED_ODA				0x9F91820E				/*!< OBSOLETE WITH KERNEL ExpressPay 3 - Internal tag indicating the card has been optimized to allow a more efficient processing of ODA (\a TRUE if optimized card, \a FALSE else).<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_FULL_ONLINE_EMV_REMOVAL_TIMEOUT	0x9F91820F				/*!< EXPRESSPAY - Timeout value that indicates when the cardholder should remove the card during an ExpressPay Full Online EMV transaction if no authorization response is received from the Acquirer. Transaction is then completed as Partial Online. Time in milliseconds.<br> Terminal is not capable to process full online transactions if set to 0.<br>	- Format : b.<br>	- Length : 4 bytes.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_ARC_ONLINE_APPROVED				0x9F918210				/*!< EXPRESSPAY - Tag indicating the Terminal received an Authorization Response Code from the Acquirer indicating an approved transaction (\a TRUE if approved, \a FALSE else).<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_CONTACT_EMV_CAPABLE				0x9F918211				/*!< OBSOLETE WITH KERNEL ExpressPay 3 - Tag indicating the Terminal is capable to perform a contact EMV transaction (\a TRUE if capable, \a FALSE else).<br>If TRUE in EMV Mode, a partial Online transaction will result in a contact EMV transaction.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_INT_CV_NOT_SUCCESSFUL			0x9F918212				/*!< OBSOLETE WITH KERNEL ExpressPay 3 - Internal tag indicating the TVR/TAC/IAC Byte 3 bit 8 matched when checking Action Codes Denial. Transaction is declined (\a TRUE if it matched, \a FALSE else).<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_MOBILE_TRANSACTION_RESTARTED		0x9F918213				/*!< EXPRESSPAY - Tag indicating that the transaction has been restarted ('Try Again' processing used during Mobile CVM processing) (different from 0 if transaction has been restarted: second tap, 0 or absent else).<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_EXPRESSPAY_ISSUER_SCRIPT_71_LIST			0x9F918214				/*!< EXPRESSPAY - List of Scripts with tag '71' received from the Issuer. This scripts contain commands that must be sent to the card before the second Generate AC command.<br> - Format : b.<br> - Length : up to 512 bytes.<br> - Source : Terminal. */
#define TAG_EXPRESSPAY_ISSUER_SCRIPT_72_LIST			0x9F918215				/*!< EXPRESSPAY - List of Scripts with tag '72' received from the Issuer. This scripts contain commands that must be sent to the card after the second Generate AC command.<br> - Format : b.<br> - Length : up to 512 bytes.<br> - Source : Terminal. */
#define TAG_EXPRESSPAY_INT_SUPPORTED_CAPK_INDEX_LIST	0x9F918216				/*!< EXPRESSPAY - Internal tag containing the list of CA Public Key index list (concatenation of indexes (each one coded on one byte)). This tag can contain up to 64 supported key indexes.<br>	- Format : b.<br>	- Length : up to 64 bytes.<br>	- Source : Terminal. */
//! @}

//! \addtogroup ExpressPayPossibleCvm
//! @{
#define EXPRESSPAY_CVM_NO_CVM							0x01					/*!< EXPRESSPAY - "No CVM" method has been applied. */
#define EXPRESSPAY_CVM_SIGNATURE						0x02					/*!< EXPRESSPAY - "Signature" method has been applied. */
#define EXPRESSPAY_CVM_ONLINE_PIN						0x04					/*!< EXPRESSPAY - "Online PIN" method has been applied. */
//! @}


//! \addtogroup ExpressPayPossibleOdaMethods
//! @{
#define EXPRESSPAY_ODA_METHOD_NONE						0x00					/*!< EXPRESSPAY - Value for \a TAG_EXPRESSPAY_INT_ODA_METHOD indicating no ODA method has been selected. */
#define EXPRESSPAY_ODA_METHOD_SDA						0x01					/*!< EXPRESSPAY - Value for \a TAG_EXPRESSPAY_INT_ODA_METHOD indicating SDA method has been selected. */
#define EXPRESSPAY_ODA_METHOD_CDA						0x02					/*!< EXPRESSPAY - Value for \a TAG_EXPRESSPAY_INT_ODA_METHOD indicating CDA method has been selected. */
//! @}

//! \addtogroup ExpressPayPossibleCardTypes
//! @{
#define EXPRESSPAY_B1_CARD_ID								0x82					/*!< EXPRESSPAY 1 only - First byte of \a TAG_KERNEL_CARD_TYPE tag indicating this is an ExpressPay card. ExpressPay kernel always sets the first byte with this define. */
#define EXPRESSPAY_B2_CARD_TYPE_MSTRIPE_ONLY				0x01					/*!< EXPRESSPAY 1 only - Second byte of \a TAG_KERNEL_CARD_TYPE tag indicating the card supports ExpressPay Magstripe mode only. */
#define EXPRESSPAY_B2_CARD_TYPE_EMV_AND_MSTRIPE				0x02					/*!< EXPRESSPAY 1 only - Second byte of \a TAG_KERNEL_CARD_TYPE tag indicating the card supports ExpressPay EMV and Magstripe mode. */
//! @}

/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Glodal Data ////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////
