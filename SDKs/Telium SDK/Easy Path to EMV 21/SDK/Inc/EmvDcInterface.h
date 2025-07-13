/////////////////////////////////////////////////////////////////

//! \file
//! This file describes the interface of the EmvDcInterface.lib library.

//// Macros & preprocessor definitions //////////////////////////

#ifndef _SECDEL_
#error _SECDEL_ must be defined !
#endif

#define EMV_SEL_EMV_CARD				0	//!< An EMV card is detected.
#define EMV_SEL_NOT_EMV_CARD			1	//!< A non EMV card is detected.
#define EMV_SEL_CARD_ERROR				2	//!< A card error occurs. Typically, you should perform a fallback.
#define EMV_SEL_NO_CARD					3	//!< There is no card in the reader. Typically, you should cancel the transaction or wait again for the card.

//// Types //////////////////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

//! \brief Prepare EMV DC for a transaction and power on the card.
//! \param[in] pInputDel Parameters to give to EMV DC. It is usualy NULL (no parameter).
//! \param[in,out] pTempDel Pointer to a temporary that will be modified by this function. The result has no meaning. Give a DEL that you use for othoer tasks to minimise the memory usage.
//! \return It can return:
//! - \ref EMV_SEL_EMV_CARD,
//! - \ref EMV_SEL_NOT_EMV_CARD,
//! - \ref EMV_SEL_CARD_ERROR,
//! - \ref EMV_SEL_NO_CARD.
int EMV_SEL_PowerOn(DEL* pInputDel, DEL* pTempDel);

//! \brief Retreive the status of the power on and the historical bytes of the ATR.
//! \param[out] Status Status of the the power on.
//! \param[out] historic Historical bytes of the ATR.
void EMV_SEL_GetPowerOnStatus(unsigned char *Status, HISTORIC *historic);

/*! \brief Retreive the list of AIDs both managed by the terminal and the card.
\param[in] pAidList DEL that contain a \a TAG_AID_LIST_TERMINAL tag.
\return It returns a pointer to a DEL that contains the list of the mutually supported AIDs. The tags present in the DEL are:
- \a TAG_SERVICE_STATUS_CODE (9F8101) is the status of the operation.
- \a TAG_NUMBER_OF_MATCHING_APP (9F8117) is the number of mutually supported AIDs.
- \a TAG_CARDHOLDER_CONFIRMATION (9F8116) is equal to 1 if cardholder confirmation is necessary (at least one application request for it or at least one Application Priority Indicator is missing).
- For each supported AID:
	- \a TAG_AID_ICC (4F) Application Identifier - card.
	- \a TAG_APPLICATION_LABEL (50) Application Label,
	- \a TAG_APPLICATION_PREFFERRED_NAME (9F12) Application Preferred Name,
	- \a TAG_ISSUER_CODE_TABLE_INDEX (9F11) Issuer Code Table Index,
	- \a TAG_LANGUAGE_PREFERENCE (5F2D) Language Preference,
	- \a TAG_APPLI_PRIOR_IND (87) Application Priority Indicator.
\see \ref EMV_SEL_DoTransaction
\remarks See EMV 4.1 Book 1, chapter 12.4 (Final Selection), pages 148 and 149 on how to select the application to use, with or without cardholder confirmation depending on the Application Priority Indicator.
\remarks Example that prints all the mutually supported AIDs (do not perform any transaction).
\code
{
	static unsigned char ListAid[] = {
		0x05, 0xA0, 0x00, 0x00, 0x00, 0x04,		// Mastercard
		0x05, 0xA0, 0x00, 0x00, 0x00, 0x03,		// VISA
	};
	static DEL InDel;
	static DEL TmpDel;

	DEL* pOutDel;
	DataElement Elt;
	DataElement* pElt;
	FILE* hPrinter;
	int nResult;
	int i;
	int j;
	char String[256];

	hPrinter = fopen("PRINTER", "w");

	pprintf("EMV_SEL_PowerOn()\n");
	ttestall(PRINTER, 0);
	// Power on the card
	nResult = EMV_SEL_PowerOn(NULL, &TmpDel);
	pprintf(" => %d\n", nResult);
	ttestall(PRINTER, 0);
	if (nResult == EMV_SEL_EMV_CARD)
	{
		DEL_init(&InDel);

		// Add the list of the AIDs supported by the terminal
		Elt.tag = TAG_AID_LIST_TERMINAL;
		Elt.length = sizeof(ListAid);
		Elt.ptValue = ListAid;
		DEL_AddDataElement(&InDel, &Elt);

		pprintf("EMV_SEL_GetCandidateList()\n");
		ttestall(PRINTER, 0);
		// Get the list of mutually supported AIDs
		pOutDel = EMV_SEL_GetCandidateList(&InDel);
		if (pOutDel != NULL)
		{
			pprintf(" =>\n\n");
			ttestall(PRINTER, 0);

			// Print each AID information
			if (DEL_GetCount(pOutDel) > 0)
			{
				i = 1;
				pElt = DEL_GetDataElement(pOutDel, i);
				do
				{
					if (pElt->tag == TAG_AID_ICC)
					{
						pprintf("AID=");
						for(j = 0; j < (int)pElt->length; j++)
							pprintf("%02X", pElt->ptValue[j]);
						pprintf("\n");
						ttestall(PRINTER, 0);

						i++;
						if (i <= DEL_GetCount(pOutDel))
						{
							pElt = DEL_GetDataElement(pOutDel, i);
							while((pElt->tag != TAG_AID_ICC) && (i <= DEL_GetCount(pOutDel)))
							{
								switch(pElt->tag)
								{
								case TAG_APPLICATION_LABEL:
									memcpy(String, pElt->ptValue, pElt->length);
									String[pElt->length] = '\0';
									pprintf("Label=\"%s\"\n", String);
									break;
								case TAG_APPLICATION_PREFFERRED_NAME:
									memcpy(String, pElt->ptValue, pElt->length);
									String[pElt->length] = '\0';
									pprintf("Pref Name=\"%s\"\n", String);
									break;
								case TAG_ISSUER_CODE_TABLE_INDEX:
									pprintf("Issuer Code Table Index=%d\n", (int)pElt->ptValue[0]);
									break;
								case TAG_LANGUAGE_PREFERENCE:
									memcpy(String, pElt->ptValue, pElt->length);
									String[pElt->length] = '\0';
									pprintf("Lang Pref=%s\n", String);
									break;
								case TAG_APPLI_PRIOR_IND:
									pprintf("Appli Prio Ind=%d\n", (int)pElt->ptValue[0]);
									break;

								default:
									pprintf("%X=", pElt->tag);
									for(j = 0; j < (int)pElt->length; j++)
										pprintf("%02X", pElt->ptValue[j]);
									pprintf("\n");
									break;
								}
								ttestall(PRINTER, 0);

								i++;
								if (i <= DEL_GetCount(pOutDel))
									pElt = DEL_GetDataElement(pOutDel, i);
							}
						}

						pprintf("------------------------\n");
					}
					else
					{
						pprintf("***%X=", pElt->tag);
						for(j = 0; j < (int)pElt->length; j++)
							pprintf("%02X", pElt->ptValue[j]);
						pprintf("\n");
						ttestall(PRINTER, 0);

						i++;
						if (i <= DEL_GetCount(pOutDel))
							pElt = DEL_GetDataElement(pOutDel, i);
					}
				} while (i <= DEL_GetCount(pOutDel));
			}
		}
		else
		{
			pprintf(" => NULL\n");
			ttestall(PRINTER, 0);
		}

		pprintf("\n\n\n\n\x0c");
		ttestall(PRINTER, 0);

		fclose(hPrinter);

		// TODO: Choose the AID to use and perform the transaction by calling EMV_SEL_DoTransaction or call EMV_SEL_Stop
		EMV_SEL_Stop();
	}
	else
	{
		pprintf("\n\n\n\n\x0c");
		ttestall(PRINTER, 0);

		fclose(hPrinter);
	}
}\endcode
*/
DEL* EMV_SEL_GetCandidateList(DEL* pAidList);

//! \brief Stop the current EMV transaction.
//! \remarks You must call this function if \ref EMV_SEL_PowerOn returned \ref EMV_SEL_EMV_CARD but you didn't perform the transaction (\ref EMV_SEL_GetCandidateList returned an error, ...).
void EMV_SEL_Stop(void);

//! \brief Start a transaction after the application selection step (see \ref EMV_SEL_PowerOn and \ref EMV_SEL_GetCandidateList).
//! \param[in] nLenAid Length of the AID to use \a pAid.
//! \param[in] pAid AID to use.
//! \param[in] nLabelLength Length of the label \a pLabel of the AID. Set to 0 if there is no label.
//! \param[in] pLabel Label of the AID. Set to NULL if there is no label.
//! \param[in] pAppliPrioInd Application priority indicator of the AID (length is 1 byte). Set to NULL if there is no application priority indicator.
//! \param[in] nPrefLangLength Length of the language preference \a pPrefLang of the AID. Set to 0 if there is no language preference.
//! \param[in] pPrefLang Language preference of the AID. Set to NULL if there is no language preference.
//! \return It can return:
//! - \a PAY_OK The transaction is performed.
//! - \a PAY_KO The transaction is not performed.
//! - \a PAY_OTHER_AID The transaction is not performed and another AID can be tried.
int EMV_SEL_DoTransaction(int nLenAid, unsigned char* pAid, int nLabelLength, unsigned char* pLabel, unsigned char* pAppliPrioInd, int nPrefLangLength, unsigned char* pPrefLang);

//! \brief Define the values of one or several private tags.
//! \param[in] pInputDel DEL containing the tags to store.
//! \return It can return:
//! - \a TRUE The operation is successfull.
//! - \a FALSE An invalid tag is present in the input DEL \a pInputDel.
//! \remarks The allowed tags are:
//! - Payment system tags (9F50 to 9F7F).
//! - Tags of the private class (first byte is between C0 and FF).
int EMVDC_Ex_SetPrivateDataElements(const DEL* pInputDel);

//! \brief Define the values of tags.
//! \param[in] pInputDel DEL containing the tags to store.
//! \return It can return:
//! - \a TRUE The operation is successfull.
//! - \a FALSE An invalid tag is present in the input DEL \a pInputDel.
//! \remarks The allowed tags are:
//! - Transaction Type (9C).
//! - Authorisation Response Code (8A).
//! - Payment system tags (9F50 to 9F7F).
//! - Tags of the private class (first byte is between C0 and FF).
int EMVDC_Ex_SetDataElements(const DEL* pInputDel);

//! \brief Patch for REQ2 
//! \return none
//! \remarks : only valid for kernels 0405, 0406, 0407
void FixeTVR53(void);

