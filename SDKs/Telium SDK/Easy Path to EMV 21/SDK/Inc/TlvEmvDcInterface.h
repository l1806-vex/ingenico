/////////////////////////////////////////////////////////////////

//! \file
//! This file describes the interface of the EmvDcInterface.lib library.

//// Macros & preprocessor definitions //////////////////////////


#define EMV_SEL_EMV_CARD				0	//!< An EMV card is detected.
#define EMV_SEL_NOT_EMV_CARD			1	//!< A non EMV card is detected.
#define EMV_SEL_CARD_ERROR				2	//!< A card error occurs. Typically, you should perform a fallback.
#define EMV_SEL_NO_CARD					3	//!< There is no card in the reader. Typically, you should cancel the transaction or wait again for the card.

//// Types //////////////////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

//! \brief Prepare EMV DC for a transaction and power on the card.
//! \param[in] pInputTree Parameters to give to EMV DC. It is usualy NULL (no parameter).
//! \return It can return:
//! - \ref EMV_SEL_EMV_CARD,
//! - \ref EMV_SEL_NOT_EMV_CARD,
//! - \ref EMV_SEL_CARD_ERROR,
//! - \ref EMV_SEL_NO_CARD.
int TLV_EMV_SEL_PowerOn(TLV_TREE_NODE pInputTree);


//! \brief Retreive the list of AIDs both managed by the terminal and the card.
//! \param[in] pAidListTlv Contain a \a TAG_AID_LIST_TERMINAL tag.
//! \return It returns a TlvTree that contains the list of the mutually supported AIDs.
//! \remarks See EMV 4.1 Book 1, chapter 12.4 (Final Selection), pages 148 and 149 on how to select the application to use, with or without cardholder confirmation depending on the Application Priority Indicator.
TLV_TREE_NODE TLV_EMV_SEL_GetCandidateList(TLV_TREE_NODE pAidListTlv);


//! \brief Define the values of one or several private tags.
//! \param[in] pInputTlv TlvTree containing the tags to store.
//! \return It can return:
//! - \a TRUE The operation is successfull.
//! - \a FALSE An invalid tag is present in the input TlvTree \a pInputTlv.
//! \remarks The allowed tags are:
//! - Payment system tags (9F50 to 9F7F).
//! - Tags of the private class (first byte is between C0 and FF).
int TLV_EMVDC_Ex_SetPrivateDataElements(const TLV_TREE_NODE pInputTlv);

//! \brief Define the values of tags.
//! \param[in] pInputTlv TlvTree containing the tags to store.
//! \return It can return:
//! - \a TRUE The operation is successfull.
//! - \a FALSE An invalid tag is present in the input TlvTree \a pInputTlv.
//! \remarks The allowed tags are:
//! - Transaction Type (9C).
//! - Authorisation Responce Code (8A).
//! - Payment system tags (9F50 to 9F7F).
//! - Tags of the private class (first byte is between C0 and FF).
int TLV_EMVDC_Ex_SetDataElements(const  TLV_TREE_NODE pInputTlv);

