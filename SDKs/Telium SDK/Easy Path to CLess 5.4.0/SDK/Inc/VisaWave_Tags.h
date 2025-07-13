/**
 * \file    VisaWave_Tags.h
 * \brief   This describes all the specific VisaWave contactless kernel tags.
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

//! \addtogroup VisaWaveTagsDefinedBySpec
//! @{
#define TAG_VISAWAVE_TERMINAL_TRANSACTION_QUALIFIERS	0x9F66					/*!< VISAWAVE - Indicates reader capabilities, requirements, and preferences to the card.<br> - Format : b.<br>	- Length : 4 bytes.<br> - Source : Terminal. */
#define TAG_VISAWAVE_VLP_ISSUER_AUTHORIZATION_CODE		0x9F74					/*!< VISAWAVE - VLP issuer authorization code.<br> - Format : b.<br>	- Length : 6 bytes.<br> - Source : Card. */
#define TAG_VISAWAVE_VLP_AVAILABLE_FUNDS				0x9F79					/*!< VISAWAVE - VLP available funds.<br> - Format : n.<br>	- Length : 6 bytes.<br> - Source : Card. */
#define TAG_VISAWAVE_VLP_TERMINAL_SUPPORT_INDICATOR		0x9F7A					/*!< VISAWAVE - VLP terminal support indicator.<br> - Format : b.<br>	- Length : 1 byte.<br> - Source : Terminal. */

#define TAG_VISAWAVE_READER_CLESS_TR_LIMIT				0xDF00					/*!< VISAWAVE - Reader Contactless transaction limit.<br> - Format : n.<br>	- Length : 6 bytes.<br> - Source : Terminal. */
#define TAG_VISAWAVE_CVM_REQUIRED_LIMIT					0xDF01					/*!< VISAWAVE - CVM required limit.<br> - Format : n.<br>	- Length : 6 bytes.<br> - Source : Terminal. */
#define TAG_VISAWAVE_CLESS_FLOOR_LIMIT					0xDF02					/*!< VISAWAVE - Contactless floor limit.<br> - Format : n.<br>	- Length : 6 bytes.<br> - Source : Terminal. */
//! @}


//! \addtogroup VisaWaveTagsInternallyDefined
//! @{
#define TAG_VISAWAVE_SFI11_PRESENT_IN_AFL				0x9F918901				/*!< VISAWAVE - Indicates if the SFI 11 is present or not in the AFL (offline/online transaction).<br> - Format : b.<br>	- Length : 1 bytes.<br> - Source : Terminal. */
#define TAG_VISAWAVE_ONLINE_ONLY						0x9F918902				/*!< VISAWAVE - Indicates if an AID supports Online Transaction only (if this tag is present and different from 0x00).<br> - Format : b.<br>	- Length : 1 bytes.<br> - Source : Terminal. */
#define TAG_VISAWAVE_TRANSACTION_CVM					0x9F918903				/*!< VISAWAVE - Data object used to indicate to the terminal the outcome of the CVM Selection function. Possible values are "No CVM", "Signature", "Online PIN". The coding of the value is implementation specific. Refer to \ref VisaWavePossibleCvm for more information about the possible values.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */

#define TAG_VISAWAVE_INT_GENAC_REF_CTRL_PARAMETER		0x9F918905				/*!< VISAWAVE - Internal tag indicating the Generate AC Reference Control Parameter to be sent on the Generate AC command (Always ARQC for online transactions).<br> - Format : b.<br>	- Length : 1 bytes.<br> - Source : Terminal. */
#define TAG_VISAWAVE_INT_DATA_PART_OF_ODA				0x9F918906				/*!< VISAWAVE - Internal tag containing the concatenation of data that are part of authentication.<br>	- Format : b.<br>	- Length : up to 3072 bytes.<br>	- Source : Terminal. */
#define TAG_VISAWAVE_INT_IS_SFI_ERROR					0x9F918907				/*!< VISAWAVE - Internal tag indicating if a record that is part of ODA is incorrectly coded or not. If there is no error, this tag is not stored.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_VISAWAVE_INT_GENAC_RESPONSE_DATA			0x9F918908				/*!< VISAWAVE - Internal tag containing the Generate AC card response data (content of template 0x77). This tag will be used for CDA signature generation and verification.<br>	- Format : b.<br>	- Length : up to 257 bytes.<br>	- Source : Terminal. */
#define TAG_VISAWAVE_INT_DATA_PART_OF_DDA				0x9F918909				/*!< VISAWAVE - Internal tag containing the concatenation of data that are part of DDA authentication.<br>	- Format : b.<br>	- Length : up to 3072 bytes.<br>	- Source : Terminal. */
#define TAG_VISAWAVE_INT_SENT_APDU						0x9F91890A				/*!< VISAWAVE - Internal tag containing an APDU sent by the reader to the contactless card (several tags can be present).<br>	- Format : b.<br>	- Length : up to 261 bytes.<br>	- Source : Terminal. */
#define TAG_VISAWAVE_INT_CARD_RESPONSE					0x9F91890B				/*!< VISAWAVE - Internal tag containing a card response (several tags can be present).<br>	- Format : b.<br>	- Length : up to 257 bytes.<br>	- Source : Terminal. */

#define TAG_VISAWAVE_LAST_TRANSACTION_PAN				0x9F91890C				/*!< VISAWAVE - Primary Account Number (PAN) of the last transaction.<br>	- Format : cn var. up to 19 digits..<br>	- Length : var. up to 10 bytes.<br>	- Source : Terminal. */
//! @}


//! \addtogroup VisaWavePossibleCvm
//! @{
#define VISAWAVE_CVM_NO_CVM								0x01					/*!< VISAWAVE - "No CVM" method has been applied. */
#define VISAWAVE_CVM_SIGNATURE							0x02					/*!< VISAWAVE - "Signature" method has been applied. */
#define VISAWAVE_CVM_ONLINE_PIN							0x04					/*!< VISAWAVE - "Online PIN" method has been applied. */
//! @}


/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Glodal Data ////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////
