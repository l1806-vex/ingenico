/**
 * \file	SDSA_Term.c
 * \brief 	Module for messages management.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
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

#include "SDSA_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


// Default messages table (in SDSA_Messages.c)
// generated from SDSA_msgEnglish.h and SDSA_msgFrench.f files
extern const unsigned char SDSA_Messages[];


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


#ifdef _SIMULPC_
// This function is used ONLY IN SIMULATION
// TransfertData copies the local messages from the PC.
// to the terminal (char *LocalMessages variable) to avoid MMU errors.
extern char * TransfertData(char * msg);
#endif



/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////



//! \brief This function initialise Messages management. 

void SDSA_Term_Initialise(void)
{
	static int bInitialised = FALSE;
	char *NewMessages;					 // Address of the loaded message file (if exists)
	const unsigned char* pLocalMessages; // Address of the default local messages
	char ucFileName[20];


	if (bInitialised)
		return;

	bInitialised = TRUE;

	// Get the default messages
#ifdef _SIMULPC_
	pLocalMessages = TransfertData((char *)SDSA_Messages);
#else
	pLocalMessages = SDSA_Messages;
#endif // _SIMULPC_

	
	// Try to load the message file in memory (SDSA_MSG_FILE file can be loaded in the terminal for message customisation)
	sprintf(ucFileName, "%s.SGN",SDSA_MSG_FILE);
	NewMessages = LoadMSG(ucFileName);    
	if(NewMessages == NULL )
	{	
		sprintf(ucFileName, "%s.PGN",SDSA_MSG_FILE);
		NewMessages = LoadMSG(ucFileName);    
	}

	if(NewMessages == NULL )
	{
		GTL_Traces_TraceDebug("SDSA_Term_Initialise : MSG file not found :\n %s", ucFileName); 
		// Local messages are used
		DefCurrentMSG((char *)pLocalMessages);
	}
	else
	{
		GTL_Traces_TraceDebug("SDSA_Term_Initialise : MSG file loaded :\n %s", ucFileName); 
		// New messages are used in priority
		DefCurrentMSG(NewMessages);
	}

	// If a message is not found in higher priority messages file, default messages will be used
	// Local messages (file SDSA_Messages.c) contain english and french messages
	DefDefaultMSG((char *)pLocalMessages);

	// Set the current application language with the manager language
	SDSA_UserInterface_SetMerchantLanguage();
	// Set the default language (English)
	DefDefaultLang("en");
}



//! \brief Get the languages supported by the application.
//! \param[in] ulBufferSize Size in bytes of pSupportedLanguages.
//! \param[out] pSupportedLanguages Contains the supported languages code according to ISO 639-1 (up to 24 bytes, we consider the device can support 12 different languages at maximum).
//! \param[out] pNumberOfSupportedLanguages Number of supported languages.
//! \return
//!	- TRUE if supported languages correctly got.
//!	- FALSE if an error occurred.

int SDSA_Term_GetSupportedLanguages (char * pSupportedLanguages, const unsigned long ulBufferSize, unsigned long * pNumberOfSupportedLanguages)
{
	char ucFileName[20];
	char ucSupportedLanguages[32], ucTemp[32];
	unsigned long ulNumberOfSupportedLanguages;
	char *pApplicationMSG;
	int nNumberOfLanguages, i;


	if((pSupportedLanguages == NULL) || (pNumberOfSupportedLanguages == NULL))
		return (FALSE);

	// English and french are always available in the SDSA application.
	ulNumberOfSupportedLanguages = 2;
	strcpy(ucSupportedLanguages, "enfr");

	// Check if the cutomisation file for SDSA application messages exists (SDSA_MSG_FILE file can be loaded in the reader for message customisation)
	sprintf(ucFileName, "%s.SGN",SDSA_MSG_FILE);
	pApplicationMSG = LoadMSG(ucFileName);    
	if(pApplicationMSG == NULL )
	{	sprintf(ucFileName, "%s.PGN",SDSA_MSG_FILE);
		pApplicationMSG = LoadMSG(ucFileName);    
	}

	if(pApplicationMSG != NULL)
	{
		// Customisation file exists. Add the supported languages.

		nNumberOfLanguages = GetSupportedLanguages(ucTemp, pApplicationMSG);
		for (i=0; i<nNumberOfLanguages; i++)
		{
			// English and French are already added
			if((strncmp(&ucTemp[i*2],"en",2)!=0) && (strncmp(&ucTemp[i*2],"fr",2)!=0) &&
			   (strncmp(&ucTemp[i*2],"EN",2)!=0) && (strncmp(&ucTemp[i*2],"FR",2)!=0))
			{
				strncat(ucSupportedLanguages, &ucTemp[i*2], 2);
				ulNumberOfSupportedLanguages++;
			}
		}
	}

	// Copy information in the output parameters
	if(2*ulNumberOfSupportedLanguages <= ulBufferSize)
		strncpy(pSupportedLanguages, ucSupportedLanguages, 2*ulNumberOfSupportedLanguages);
	else
		strncpy(pSupportedLanguages, ucSupportedLanguages, ulBufferSize);

	*pNumberOfSupportedLanguages = ulNumberOfSupportedLanguages;

	return (TRUE);
}
