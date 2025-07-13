/**
 * \file    Discover_Tags.h
 * \brief   This describes all the specific Discover contactless kernel tags.
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


//! \defgroup DiscoverSpecificTags Specific Discover contactless kernel tags
//! @{
//! \defgroup DiscoverTagsDefinedBySpec Discover tags which value is defined by the Discover specification.
//! \defgroup DiscoverTagsInternallyDefined Discover tags described in the specification but value is defined using the internal Ingenico range (0x9F818500 to 0x9F85817F).
//! @}
//! \defgroup DiscoverPossibleOutcomes Different possible values for \a TAG_DISCOVER_TRANSACTION_OUTCOME tag.

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup DiscoverTagsDefinedBySpec
//! @{
#define TAG_DISCOVER_TRACK1_DATA						0x56					/*!< DISCOVER - Track 1 Data contains the data objects of the track 1 according to [ISO/IEC 7813] Structure B, excluding start sentinel, end sentinel and LRC. */
#define TAG_DISCOVER_APPLI_VERSION_NUMBER_ICC			0x9F7D					/*!< DISCOVER - Card Application Version number */
#define TAG_DISCOVER_DCVV								0x9F7E					/*!< DISCOVER - Card Dynamic Card Verification Value. Used during track data seeding. */
#define TAG_DISCOVER_V1_DCVV							0x9F8003				/*!< DISCOVER - Card Dynamic Card Verification Value from V1 cards. Used during track data seeding. WARNING this card tag does not parse correctly */
//! @}


//! \addtogroup DiscoverTagsInternallyDefined
//! @{
//#define TAG_DISCOVER_XXXXX				            0x9F918600 to 0x9f91867F  
#define TAG_DISCOVER_TRANSACTION_OUTCOME				0x9F918601				/*!< DISCOVER - Data object used to indicate to the terminal the outcome of the transaction processing. Possible values are "Approved", "Online Request", "Declined", "Try Another Interface" or "End Application". The coding of the value is implementation specific. */
#define TAG_DISCOVER_INT_SENT_APDU						0x9F918602				/*!< DISCOVER - Internal tag containing an APDU sent by the reader to the contactless card (several tags can be present). */
#define TAG_DISCOVER_INT_CARD_RESPONSE					0x9F918603				/*!< DISCOVER - Internal tag containing a card response (several tags can be present). */
//! @}

//! \addtogroup DiscoverPossibleOutcomes
//! @{
#define DISCOVER_OUTCOME_ONLINE_REQUEST					0x01					/*!< DISCOVER - The Discover reader has found that the transaction requires an online authorization. */
#define DISCOVER_OUTCOME_END_APPLICATION				0x02					/*!< DISCOVER - The Discover reader experienced an application error (e.g. missing data) */
//! @}

/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Glodal Data ////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////
