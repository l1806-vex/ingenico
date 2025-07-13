/**
 * \file	CST_Term.c
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

#include "CST_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define C_FIRSTCOL						0						//!< Definition of the first comlumn.
#define BACKGROUNDPIXELS				1						//!< Number of pixels added on the top and under the message to form the background.


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

extern const unsigned char CST_Messages[];				// Default messages

static char gs_ucCurrencyLabel[4];


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

//! \brief This function display a text line in graphic mode. 
//! \param[in] nline : line index.
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment : center, left, rigth, ....
//! \param[in] bmode : TRUE to erase before display something, else nothing
//! \param[in] bLongLine : TRUE for long line to display (little police will be used), FALSE else.

void CST_Term_DisplayGraphicLine(int nline, MSGinfos * ptrMSG, int nAlignment, unsigned char bmode, unsigned char bLongLine)
{
	int lg, x, y;
	int nScreenHeight, nScreenWidth;
	char * police;
	int nType; // _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_
	int nNbLineInScreen = 5;
	int nFontHeight;

	if (bLongLine)
		police = _dMEDIUM_;
	else
		police = _dLARGE_;
	
	nType = _PROP_WIDTH_;

	// In order to get back the width/heigth of the screen
	GetScreenSize(&nScreenHeight, &nScreenWidth);
	
	if(ptrMSG->file ==NULL)
		ptrMSG->file = GetDefaultFONaddress();  // Use the default manager font

	DefCurrentFont(ptrMSG->file);

	nFontHeight = GetExtendedPoliceSize(police); // Get the height of the police 
	if (nFontHeight < 0)
        GTL_Traces_TraceDebug("Police not found : %s", police);
    else
        nNbLineInScreen = nScreenHeight / nFontHeight;
	
	// Get the length of the input text
	if(ptrMSG->coding == _UNICODE_)
		lg = SizeOfUnicodeString((unsigned char*)(ptrMSG->message), police, nType);
	else
		lg = SizeOfISO8859String((unsigned char*)(ptrMSG->message), police, nType);

	// Calculate the position of the text to be displayed
	y = nFontHeight * nline;
	x = C_FIRSTCOL;
			
	switch (nAlignment)
	{
		case (HELPERS_ALIGN_CENTER):
			x = (nScreenWidth - lg) / 2;
			break;
		case (HELPERS_ALIGN_LEFT):
			x = C_FIRSTCOL;
			break;
		case (HELPERS_ALIGN_RIGHT):
			x = nScreenWidth - lg;
			break;
		default:
			x = C_FIRSTCOL;
			break;
	}

	// If the text lenght is superior to column it will be automatically truncated
	if (x < 0)
		x = C_FIRSTCOL;

	if (bmode == YESCLEAR)
	{
		// Clear the screen
		_clrscr();
	}
	else
	{	
		// Clear only the used line
		if(!bLongLine)
			DrawRect(0, y, nScreenWidth, y + nFontHeight, 0, _OFF_, _OFF_);
	}

	if (bLongLine)
	{
	    int nRectPosition;
        nRectPosition = nScreenHeight - (nNbLineInScreen - nline - 1) * nFontHeight;
        
		DrawRect(0, nRectPosition - 2*BACKGROUNDPIXELS, nScreenWidth, nRectPosition + nFontHeight + BACKGROUNDPIXELS, 0, _OFF_, _ON_);
		DisplayMSGinfos(x, nRectPosition - BACKGROUNDPIXELS, ptrMSG, _ON_, police, nType);
	}
	else    
	{
		DisplayMSGinfos(x, y, ptrMSG, _OFF_, police, nType);
	}
}


//! \brief This function initialise Messages menagement. 

void CST_Term_Initialise(void)
{
	static int bInitialised = FALSE;
	char *NewMessages;     // Address of the loaded message file
	const char* pLocalMessages;
	char ucFileName[20];

	if (bInitialised)
		return;

	bInitialised = TRUE;

#ifdef _SIMULPC_
	pLocalMessages = TransfertData((char *)CST_Messages);
#else
	pLocalMessages = (char*)CST_Messages;
#endif // _SIMULPC_


	// Load the message file in memory
	sprintf(ucFileName, "%s.SGN",CST_MSG_FILE);
	NewMessages=LoadMSG(ucFileName);   
	if(NewMessages == NULL )
	{
		sprintf(ucFileName, "%s.PGN",CST_MSG_FILE);
		NewMessages=LoadMSG(ucFileName);
	}
	if(NewMessages == NULL )
	{
		GTL_Traces_TraceDebug("CST_Term_Initialise : MSG file not found :\n %s", ucFileName); 
		// Local messages are used
		DefCurrentMSG((char *)pLocalMessages); // Higher priority table
	}
	else
	{
		GTL_Traces_TraceDebug("CST_Term_Initialise : MSG file loaded :\n %s", ucFileName); 
		// New messages are used
		DefCurrentMSG(NewMessages);     // Higher priority table
	}

	DefDefaultMSG((char *)pLocalMessages); // If msg not found in higher priority table, this one will be used
	
	// Define current and default languages
	CST_Term_SetMerchantLanguage();
	DefDefaultLang("en");

	CST_Term_SetReaderDateAndTime();
}



//! \brief Define the application language with the Manager language. 

void CST_Term_SetMerchantLanguage (void)
{
	char *ucManagerLanguage;
	char ucLanguage[3];

	ucManagerLanguage = GetManagerLanguage();
	
	memset(ucLanguage, 0, sizeof(ucLanguage));
	ucLanguage[0] = GTL_Convert_LowerCase(ucManagerLanguage[0]);
	ucLanguage[1] = GTL_Convert_LowerCase(ucManagerLanguage[1]);
	
	// Set the CST application language
	DefCurrentLang(ucLanguage);

	// Set the intelligent reader application language
	SDI_System_SetLanguage((unsigned char*)ucLanguage);
}


//! \brief Set the intelligent reader date and time with the date and time of the terminal.

void CST_Term_SetReaderDateAndTime(void)
{
	DATE date;
	unsigned char ucDate[7], ucTime[7];

	memset(ucDate, 0x00, sizeof(ucDate));
	memset(ucTime, 0x00, sizeof(ucTime));
	
	if(read_date(&date) == OK)
	{
		memcpy(ucDate, date.year, 2);
		memcpy(&ucDate[2], date.month, 2);
		memcpy(&ucDate[4], date.day, 2);

		memcpy(ucTime,date.hour,2);
		memcpy(&ucTime[2],date.minute,2);
		memcpy(&ucTime[4],date.second,2);

		SDI_System_SetDateAndTime(ucDate, ucTime);
	}
}


//! \brief Get and save the money label that corresponds to the given currency code.
//! \param[in] pCurrencyLabel Currency code used for the current transaction.

void CST_Term_SetMoneyLabel(unsigned char *pCurrencyLabel)
{
	memset(gs_ucCurrencyLabel, 0, sizeof(gs_ucCurrencyLabel));
	memcpy(gs_ucCurrencyLabel, pCurrencyLabel, 3);
}


//! \brief Gives the money label.
//! \return
//!		- \a money label.
//! \note This function shall be called after having loaded the parameters.

char *CST_Term_GiveMoneyLabel(void)
{
	return (gs_ucCurrencyLabel);
}



//! \brief Get a specific information in a shared buffer.
//! \param[in] pResultDataStruct Shared exchange buffer from which the tag shall be extracted.
//! \param[in] ulTag Tag that shall be extracted.
//! \param[out] pInfo pointer to the requested value
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

int CST_Term_RetreiveInfo (T_SHARED_DATA_STRUCT * pResultDataStruct, unsigned long ulTag, unsigned char ** pInfo)
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
		GTL_Traces_TraceDebug("CST_Term_RetreiveInfo : Unable to get info from the kernel response (tag=%02lx, cr=%02x)", ulTag, cr);
		nResult = FALSE;
		goto End;
	}
	
	// Get the requested tag value
	*pInfo = (unsigned char *)pReadValue;
	
End:	
	return (nResult);
}



//! \brief Get all the kernel data in a buffer.
//!	\param[in] pDataStruct Buffer to be filled witgh the kernel data.
//! \return
//!		- \ref TRUE if correctly retreived.
//!		- \ref FALSE if an error occured.

int CST_Term_GetAllData (T_SHARED_DATA_STRUCT * pDataStruct)
{
	int nSdiResult = SDI_STATUS_UNKNOWN, nResult = FALSE;
	TLV_TREE_NODE hTlvTreeIn;
	TLV_TREE_NODE hTlvTreeOut = NULL;

	hTlvTreeIn = TlvTree_New(0);
	if (hTlvTreeIn == NULL)
	{				
		GTL_Traces_TraceDebug ("CST_Term_GetAllData : error when creating the TLV-Tree");
	}
	else
	{
		TlvTree_AddChild (hTlvTreeIn, TAG_SDSA_GET_ALL_DATA, NULL, 0);
		nSdiResult = SDI_Payment_GetData(nSDSAAppliId, hTlvTreeIn, &hTlvTreeOut);
		if((nSdiResult == SDI_STATUS_OK) && (hTlvTreeOut != NULL))
		{
			// Clear the buffer and copy the data
			GTL_SharedExchange_ClearEx (pDataStruct, FALSE);
			CopyTlvTreeToDataStruct(hTlvTreeOut, pDataStruct);
			nResult = TRUE;
		}
		TlvTree_ReleaseEx (&hTlvTreeIn);
		TlvTree_ReleaseEx (&hTlvTreeOut);
	}

	if(nSdiResult == SDI_STATUS_DISCONNECTED)
		CST_ReconnectionProcess();

	return (nResult);
}



//! \brief Establishes the connection with the intelligent reader (try on USB port, and then try on serial port).

void CST_Term_ConnectAll(void)
{
	SDI_System_Disconnect();
	SDI_System_Connect("USB");
	if(SDI_System_IsConnected() == SDI_STATUS_DISCONNECTED)
	{
		SDI_System_Disconnect();
		SDI_System_Connect("COM0");
	}
}
