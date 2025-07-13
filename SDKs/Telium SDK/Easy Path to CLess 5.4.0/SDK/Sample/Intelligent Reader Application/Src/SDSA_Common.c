/**
 * \file	SDSA_Common.c
 * \brief	Contains several common functions.
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
 */


/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDSA_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Global data definition /////////////////////////////////////

static int gs_bTransactionMode;						// Indicates if transaction is explicit, implicit or not launched.
static unsigned long gs_pulListOfOutputTags[256];	// List of output tags to be returned at the end of the transaction.
static int gs_nNumberOfOutputTags = 0;				// Number of output tags to be returned at the end of the transaction.


/////////////////////////////////////////////////////////////////
//// Static functions definition ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \brief Get a specific information in a shared buffer.
//! \param[in] pResultDataStruct Shared exchange buffer from which the tag shall be extracted.
//! \param[in] ulTag Tag that shall be extracted.
//! \param[out] pInfo pointer to the requested value
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

int SDSA_Common_RetreiveInfo (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned long ulTag, unsigned char ** pInfo)
{
	int nResult = TRUE;
	int nPosition, cr;
	unsigned long ulReadLength;
	const unsigned char * pReadValue;
	
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	*pInfo = NULL; // Default result : no information
	
	cr = GTL_SharedExchange_FindNext(pResultDataStruct, &nPosition, ulTag, &ulReadLength, &pReadValue);
	
	if (cr != STATUS_SHARED_EXCHANGE_OK)
	{
		GTL_Traces_TraceDebug("SDSA_Common_RetreiveInfo : Unable to get info from the kernel response (tag=%02lx, cr=%02x)", ulTag, cr);
		nResult = FALSE;
		goto End;
	}
	
	// Get the requested tag value
	*pInfo = (unsigned char *)pReadValue;
	
End:	
	return (nResult);
}


//! \brief Format the message that contains the amount, the currency according to ucFormat, ucPosition...  
//! \param[in] ucFormat : format of the displayed amount 
//!                         0 ==> 1.000,00                                   
//!                         1 ==> 1,000.00                                   
//!                         2 ==> 1 000,00                                   
//!                         3 ==> 1.000                                      
//!                         4 ==> 1,000                                      
//!                         5 ==> 1 000                                      
//!                         6 ==> 1.000,000                                  
//!                         7 ==> 1,000.000                                  
//!                         8 ==> 1 000,000    
//! \param[in] ucCurrency : transaction currency
//! \param[in] ucPosition : position of the currency
//!                         0 ==> after the amount                        
//!                         1 ==> before the amount 
//! \param[in] ulAmount : the transaction amount
//! \param[out] pFormattedAmountMessage : the formatted message to display
//! \return : none

void SDSA_Common_FormatAmount(unsigned char ucFormat,unsigned char *ucCurrency,unsigned char ucPosition,unsigned long ulAmount,char *pFormattedAmountMessage)
{
  char            currency[4];
  char            separator1[2];
  char            separator2[2];
  char            position;
  int             exponent;
  unsigned long   divider;
  unsigned long   i;
  char   amount_format[51];


  position=ucPosition;
  strcpy((char *)currency,(char *)ucCurrency);
  switch (ucFormat)
  {
    case 1 :
      strcpy(separator1,".");
      strcpy(separator2,",");
      exponent=2;
      break;
    case 2 :
      strcpy(separator1,",");
      strcpy(separator2," ");
      exponent=2;
      break;
    case 3 :
      strcpy(separator1," ");
      strcpy(separator2,".");
      exponent=0;
      break;
    case 4 :
      strcpy(separator1," ");
      strcpy(separator2,",");
      exponent=0;
      break;
    case 5 :
      strcpy(separator1," ");
      strcpy(separator2," ");
      exponent=0;
      break;
    case 6 :
      strcpy(separator1,",");
      strcpy(separator2,".");
      exponent=3;
      break;
    case 7 :
      strcpy(separator1,".");
      strcpy(separator2,",");
      exponent=3;
      break;
    case 8 :
      strcpy(separator1,",");
      strcpy(separator2," ");
      exponent=3;
      break;
    case 0 :
	default :
      strcpy(separator1,",");
      strcpy(separator2,".");
      exponent=2;
      break;
  }
  switch(exponent)
  {
    case 1 :
      for (divider=1L,i=0L;i<(unsigned)exponent;divider*=10L,i++);
      if ((ulAmount/divider)<1000L)
      {
        sprintf(amount_format,"%lu%s%0*lu",
                (ulAmount/divider),
                separator1,
                exponent,
                (ulAmount%divider));
      }
      else
	  {
        if ((ulAmount/divider)<1000000L)
        {
          sprintf(amount_format,"%lu%s%03lu%s%0*lu",
                  ((ulAmount/divider)/1000L),
                  separator2,
                  ((ulAmount/divider)%1000L),
                  separator1,
                  exponent,
                  (ulAmount%divider));
        }
        else
	    {
          sprintf(amount_format,"%lu%s%03lu%s%03lu%s%0*lu",
                  ((ulAmount/divider)/1000000L),
                  separator2,
                  (((ulAmount/divider)/1000L)%1000L),
                  separator2,
                  ((ulAmount/divider)%1000L),
                  separator1,
                  exponent,
                  (ulAmount%divider));
        }
      }
      break;  
    case 2 :
    case 3 :
    case 4 :
    case 5 :
    case 6 :
    case 7 :
      for (divider=1L,i=0L;i<(unsigned)exponent;divider*=10L,i++);
      if ((ulAmount/divider)<1000L)
      {
        sprintf(amount_format,"%lu%s%0*lu",
                (ulAmount/divider),
                separator1,
                exponent,
                (ulAmount%divider));
      }
      else
	  {
        sprintf(amount_format,"%lu%s%03lu%s%0*lu",
                ((ulAmount/divider)/1000L),
                separator2,
                ((ulAmount/divider)%1000L),
                separator1,
                exponent,
                (ulAmount%divider));
      }
      break;  
    case 0 :
    default :
      if ((ulAmount)<1000L)
	  {
        sprintf(amount_format,"%lu",(ulAmount));
      }
      else
      {
        if ((ulAmount)<1000000L)
        {
          sprintf(amount_format,"%lu%s%03lu",((ulAmount)/1000L),separator2,((ulAmount)%1000L));
        }
        else
        {
          sprintf(amount_format,"%lu%s%03lu%s%03lu",((ulAmount)/1000000L),separator2,(((ulAmount)/1000L)%1000L),separator2,((ulAmount)%1000L));
        }
      }
      break;
  }
  if (position==0)
  {
    sprintf(pFormattedAmountMessage,"%s %s",
            amount_format,
            currency);
  }
  else
  {
    sprintf(pFormattedAmountMessage,"%s %s",
            currency,
            amount_format);
  }
}


//! \brief Indicates in which mode the transaction is (None, Implicit or Explicit).
//! \return The transaction mode :
//!	- \ref SDSA_COMMON_MODE_NONE if no transaction is in progress.
//!	- \ref SDSA_COMMON_MODE_EXPLICIT if transaction is in explicit mode.
//!	- \ref SDSA_COMMON_MODE_IMPLICIT if transaction is in implicit mode.

int SDSA_Common_GetTransactionMode (void)
{
	return (gs_bTransactionMode);
}


//! \brief Set the transaction mode (None, Implicit or Explicit).
//! \param[in] bTransactionMode The transaction mode to be set :
//!	- \ref SDSA_COMMON_MODE_NONE if no transaction is in progress.
//!	- \ref SDSA_COMMON_MODE_EXPLICIT if transaction is in explicit mode.
//!	- \ref SDSA_COMMON_MODE_IMPLICIT if transaction is in implicit mode.

void SDSA_Common_SetTransactionMode (const int bTransactionMode)
{
	gs_bTransactionMode = bTransactionMode;
}



//! \brief Check that all mandatory data to perform a transaction are available.
//! \param[in] hInputTlvTree Contains the input data to perform the transaction.
//! \param[in] pListOfTags contains the list of mandatory tags.
//! \param[in] nNumberOfTags number of tags contained in pListOfTags
//! \return
//!	- \a TRUE if all the mandatory tags are present.
//!	- \a FALSE if a mandatory tag is not present.

int SDSA_Common_CheckMandatoryTagsPresenceTlvTree (const TLV_TREE_NODE hInputTlvTree, const unsigned long * pListOfTags, const int nNumberOfTags)
{
	int nResult = TRUE;
	int nIndex;
	TLV_TREE_NODE hTlvTreeNode;

	nIndex = 0;
	hTlvTreeNode = NULL;

	while ((nResult) && (nIndex < nNumberOfTags))
	{
		hTlvTreeNode = TlvTree_Find (hInputTlvTree, pListOfTags[nIndex], 0);

		if (hTlvTreeNode == NULL)
		{
			nResult = FALSE;
			GTL_Traces_TraceDebug ("Missing mandatory tag : %02lx", pListOfTags[nIndex]);
			nIndex = nNumberOfTags;
		}

		nIndex++;
	}

	return (nResult);
}


//! \brief Copy the data in a TLV Tree.
//! \param[in] pDataStruct Data buffer that contains data to add in the TLV Tree.
//! \param[out] hOutputTlvTree Output TLV Tree containing the data.

void SDSA_Common_CopyDataStructInTLVTree (T_SHARED_DATA_STRUCT * pDataStruct, TLV_TREE_NODE hOutputTlvTree)
{
	int cr, nResult;
	int nPosition;
	unsigned long ulReadTag, ulReadLength;
	const unsigned char * pValue;

	cr = STATUS_SHARED_EXCHANGE_OK;
	nPosition = SHARED_EXCHANGE_POSITION_NULL;
	nResult = FALSE;

	if (hOutputTlvTree != NULL)
	{
		do
		{
			cr = GTL_SharedExchange_GetNext (pDataStruct, &nPosition, &ulReadTag, &ulReadLength, &pValue);
			if (cr == STATUS_SHARED_EXCHANGE_OK)
			{
				TlvTree_AddChild (hOutputTlvTree, ulReadTag, pValue, ulReadLength);
			}
		} while (cr == STATUS_SHARED_EXCHANGE_OK);
			
		// If end of data has not been reached
		if (cr != STATUS_SHARED_EXCHANGE_END)
			GTL_Traces_TraceDebug ("SDSA_Common_CopyDataStructInTLVTree : Error occured when parsing the shared buffer.");
	}
	else
	{
		GTL_Traces_TraceDebug ("SDSA_Common_CopyDataStructInTLVTree : hOutputTlvTree is NULL");
	}
}


//! \brief Copy a TLV Tree in a data structure.
//! \param[in] hTlvTree TLV Tree that contains data to had to the data structure.
//! \param[out] pDataStruct Data buffer that will contain the copied data.

void SDSA_Common_CopyTlvTreeInDataStruct (TLV_TREE_NODE hTlvTree, T_SHARED_DATA_STRUCT * pDataStruct)
{
	TLV_TREE_NODE pResearch;
	
	pResearch = TlvTree_GetFirstChild (hTlvTree);
	
	while (pResearch != NULL)
	{
		GTL_SharedExchange_AddTag(pDataStruct, TlvTree_GetTag (pResearch), TlvTree_GetLength(pResearch),TlvTree_GetData(pResearch));
		pResearch = TlvTree_GetNext (pResearch);
	}
}


//! \brief Check if a card is present in the field.
//! \return TRUE if there is a card in the field, FALSE else.

int SDSA_Common_IsCardInFieldDeselection (void)
{
	int bCardInField = FALSE;
	int nIndex;

	if (ClessEmv_IsDriverOpened())
	{
		ClessEmv_FormatCommand (SETFIELD,FALSE,0,0,0);
		ttestall (0, 1);
		ClessEmv_FormatCommand (SETFIELD,TRUE,0,0,0);
		ttestall (0, 1);

		for (nIndex = 0; (nIndex < 3) && (!bCardInField); nIndex++)
		{
			bCardInField = (ClessEmv_FormatCommand (FCTREQ, CL_TYPE_A, TRUE, 0, 0) == CL_OK); // Type A

			if (!bCardInField)
				bCardInField = (ClessEmv_FormatCommand (FCTREQ, CL_TYPE_B, TRUE, 0, 0) == CL_OK); // Type B
		}
	}

	if (bCardInField)
		GTL_Traces_TraceDebug ("CARD IN FIELD");
	else
		GTL_Traces_TraceDebug ("NO CARD IN FIELD");

	return (bCardInField);
}


//! \brief Release the given TlvTree and then set the pointer to NULL

void TlvTree_ReleaseEx(TLV_TREE_NODE* pTlvTree)
{
	if (pTlvTree != NULL)
	{
		if (*pTlvTree != NULL)
		{
			TlvTree_Release(*pTlvTree);
			*pTlvTree = NULL;
		}
	}
}


//! \brief Save the list of output tags to be returned at the end of the transaction.
//! \param[in] pListOfTags Contains the list of tags
//! \param[in] nListOfTagsLength Length of the list of tags

void SDSA_Common_SetListOfOutputTags(const unsigned char *pListOfTags, const int nListOfTagsLength)
{
	if((pListOfTags != NULL) && (nListOfTagsLength != 0))
	{
		memcpy((unsigned char *) gs_pulListOfOutputTags, pListOfTags, nListOfTagsLength);
		gs_nNumberOfOutputTags = (nListOfTagsLength/(sizeof(long)));
	}
	else
		gs_nNumberOfOutputTags = 0;
}


//! \brief Get the requested tags if \ref TAG_SDSA_LIST_OF_OUTPUT_TAGS has been provided.
//! \param[out] hOutputTlvTree Output TLV Tree that will contain the requeted data.
//! \return TRUE if data had been get, FALSE else

int SDSA_Common_GetListOfOutputTags (TLV_TREE_NODE hOutputTlvTree)
{
	T_SHARED_DATA_STRUCT * pDataRequest;
	unsigned char ucKernel;
	int nReturn = FALSE;
	int nIndex;
	
	// If the length of the list of output tags to be returned is 0, no tag to get 
	if(gs_nNumberOfOutputTags == 0)
		return (FALSE);

	pDataRequest = GTL_SharedExchange_InitShared(32768);
	if (pDataRequest == NULL)
		return (FALSE);
		
	for (nIndex = 0; nIndex < gs_nNumberOfOutputTags; nIndex++)
	{
		// Add the requested tag in the list
		GTL_SharedExchange_AddTag (pDataRequest, gs_pulListOfOutputTags[nIndex], 0, NULL);

	}
	// Get the idenfier of the kernel that performed the transaction
	ucKernel = SDSA_Customisation_GetUsedPaymentScheme();

	switch (ucKernel)
	{
	case SDSA_KERNEL_IDENTIFIER_PAYPASS :
		nReturn = PayPass_GetData(pDataRequest);
		break;

	case SDSA_KERNEL_IDENTIFIER_PAYWAVE :
		nReturn = payWave_GetData(pDataRequest);
		break;

	case SDSA_KERNEL_IDENTIFIER_VISAWAVE :
		nReturn = VisaWave_GetData(pDataRequest);
		break;

	case SDSA_KERNEL_IDENTIFIER_EXPRESSPAY :
		nReturn = ExpressPay3_GetData(pDataRequest);
		break;

	case SDSA_KERNEL_IDENTIFIER_INTERAC:
		nReturn = Interac_GetData(pDataRequest);
		break;

	case SDSA_KERNEL_IDENTIFIER_DISCOVER:
		nReturn = Discover_GetData(pDataRequest);
		break;

	default:
		GTL_Traces_TraceDebug("SDSA_Common_GetListOfOutputTags : Unknown value for kernel identifier : %x", ucKernel);
		break;
	}

	
	if (nReturn == KERNEL_STATUS_OK)
	{
		// Retrieve the requested tags and add them in the output TlvTree
		SDSA_Common_CopyDataStructInTLVTree(pDataRequest, hOutputTlvTree);
		
		nReturn = TRUE;
	}

	GTL_SharedExchange_DestroyShare(pDataRequest);

	return (nReturn);
}
