/**
* \file
* \brief This module implements all the Telium Manager services.
*
* \author Ingenico
* \author Copyright (c) 2012 Ingenico, 28-32, boulevard de Grenelle,\n
* 75015 Paris, France, All Rights Reserved.
*
* \author Ingenico has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorisation of Ingenico.
**/

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "APCLESS.h"


//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

static void __APCLESS_ServiceManager_GetAppName(NO_SEGMENT appliId, char *name, int nameBufferSize);


//// Global variables ///////////////////////////////////////////

static int __APCLESS_ServicesManager_isDllTpassLoaded = FALSE;     ///< Boolean to check if Tpass DLL has been loaded

static const char* __APCLESS_ServicesManager_MenuUser[] =
{
   "Explicit Trn",
   "Debug Trace On",
   "Debug Trace Off",
   0
};


//// Functions //////////////////////////////////////////////////

//! \brief Retrieves the name of the application.
//! \param[in] appliId The application ID.
//! \param[out] name Buffer of size \a nameBufferSize which will contain the application name.
//! \param[in] nameBufferSize The size of the \a name buffer.
static void __APCLESS_ServiceManager_GetAppName(NO_SEGMENT appliId, char *name, int nameBufferSize)
{
	// To avoid warnings because 'nameBufferSize' is not used
	(void)nameBufferSize;

	ASSERT(name != NULL);
	ASSERT(nameBufferSize >= 0);

	// Build the application value
	// TODO: Set your application name
	VERIFY(sprintf(name, "CLess") < nameBufferSize);
}

//! \brief The Telium Manager calls this service at startup.
//! \param[in] appliId The application ID.
//! \param[out] paramOut Output parameters that contains the application ID.
//! \return Always \a FCT_OK.
//! \sa Telium Manager reference documentation.
int APCLESS_ServiceManager_AfterReset(NO_SEGMENT appliId, S_TRANSOUT *paramOut)
{
	unsigned char changeFlag;
	unsigned char changeType;
	int isAppliUpdated;

	ASSERT(paramOut != NULL);

	// Clear the output parameter
	memclr(paramOut, sizeof(*paramOut));
	paramOut->noappli = appliId;

	// Check for first run
	isAppliUpdated = FALSE;
	if (first_init(appliId, &changeFlag, &changeType) != FSE_FAILED)
	{
		if (changeFlag == (unsigned char)-1)
		{
			// The application has been updated since the last execution
			isAppliUpdated = TRUE;
		}
	}

	//************************************************************************
	// Initialise the application
	//************************************************************************
	// TODO: Open the DLLs if any
   __APCLESS_ServicesManager_isDllTpassLoaded = (TPasslib_open() == 0);  // TPass DLL Library

	// TODO: Initialise generic components of the application
   APCLESS_Gui_Init();

	// TODO: Initialise the application (load files ...)
   if (__APCLESS_ServicesManager_isDllTpassLoaded)
   {
      // Set the LEDs into the idle state
      APCLESS_Gui_IndicatorIdle();
   }
   else
   {  // TPass Dll not found -> display error message
      APCLESS_Gui_Display_Error_No_TPass();
   }


	//************************************************************************

	//************************************************************************
	// TODO: Print a ticket to inform the merchant that the application has been loaded / updated
	//************************************************************************
	if (isAppliUpdated)
	{
		// TODO: Print the application version
	}
	//************************************************************************

	// Clear the first run flag
	if (isAppliUpdated)
	{
		raz_init(appliId);
	}

	return FCT_OK;
}

//! \brief The Telium Manager calls this service to get the name of the application.
//! \param[in] appliId The application ID.
//! \param[out] paramOut Output parameters that contains the application name amongst other things.
//! \return Always \a FCT_OK.
//! \sa Telium Manager reference documentation.
int APCLESS_ServiceManager_IsName(NO_SEGMENT appliId, S_ETATOUT *paramOut)
{
	ASSERT(paramOut != NULL);

	// Initialise the output parameter
	memclr(&paramOut->returned_state[paramOut->response_number],
		sizeof(paramOut->returned_state[paramOut->response_number]));

	// Get the name of the application
	__APCLESS_ServiceManager_GetAppName(appliId, paramOut->returned_state[paramOut->response_number].appname,
		sizeof(paramOut->returned_state[paramOut->response_number].appname));
	paramOut->returned_state[paramOut->response_number].no_appli = appliId;
	paramOut->returned_state[paramOut->response_number].state.response = REP_OK;
	paramOut->response_number++;

	return FCT_OK;
}

//! \brief The Telium Manager calls this service to let the application to customise the Telium Manager behaviour.
//! \param[in] appliId The application ID.
//! \param[out] paramOut Output parameters.
//! \return Always \a FCT_OK.
//! \sa Telium Manager reference documentation.
int APCLESS_ServiceManager_GiveYourDomain(NO_SEGMENT appliId, S_INITPARAMOUT *paramOut)
{
	// To avoid warnings because 'appliId' is not used
	(void)appliId;

	ASSERT(paramOut != NULL);

	// Initialise the output parameter
	memclr(&paramOut->returned_state[paramOut->response_number],
		sizeof(paramOut->returned_state[paramOut->response_number]));

	// Allow Telium Manager to modify all the parameters
	// TODO: Set the value to your needs
	paramOut->returned_state[paramOut->response_number].mask = MSK_ALL_PARAM;

	// It is a standard application
	paramOut->returned_state[paramOut->response_number].application_type = TYP_EXPORT;
	paramOut->response_number++;

	return FCT_OK;
}


//! \brief The Telium Manager calls this service to know the state of the application.
//! \param[in] appliId The application ID.
//! \param[out] paramOut Output parameters that contains the state of the application.
//! \return Always \a FCT_OK.
//! \sa Telium Manager reference documentation.
int APCLESS_ServiceManager_IsState(NO_SEGMENT appliId, S_ETATOUT *paramOut)
{
	ASSERT(paramOut != NULL);

	// Initialise the output parameter
	memclr(&paramOut->returned_state[paramOut->response_number],
		sizeof(paramOut->returned_state[paramOut->response_number]));

	// Get the name of the application
	__APCLESS_ServiceManager_GetAppName(appliId, paramOut->returned_state[paramOut->response_number].appname,
		sizeof(paramOut->returned_state[paramOut->response_number].appname));
	paramOut->returned_state[paramOut->response_number].no_appli = appliId;

	// TODO: Retrieve the state of the application
	paramOut->returned_state[paramOut->response_number].state.response = REP_OK;
	paramOut->response_number++;

#ifdef PAYPASS_TORN
   // Clean up the Torn Transaction log by removing torn records that were not recovered and that have been aged off the log.
   APCLESS_PayPassTorn_CleanLog();
#endif

	return FCT_OK;
}

//! \brief The Telium Manager calls this service each time it wants to delete an application.
//! \param[in] appliId The application ID.
//! \param[out] paramOut Output parameters that contains the application response:
//!      - DEL_YES : application authorises deletion process
//!      - DEL_NO :  application refuses any deletion process (Manager will display a message regarding the application which has refused the deletion)
//! \return Always \a FCT_OK.
//! \sa Telium Manager reference documentation.
int APCLESS_ServiceManager_IsDelete(NO_SEGMENT appliId, S_DELETE *paramOut)
{
   // To avoid warnings because 'appliId' is not used
   (void)appliId;

   // Initialise the output parameter
   memclr(paramOut, sizeof(*paramOut));

   // TODO: Check batch file status
   paramOut->deleting = DEL_YES;

   return FCT_OK;
}

//! \brief The Telium Manager calls this service each time the application is selected with the "F" menu.
//! \param[in] appliId The application ID.
//! \return Always \a FCT_OK.
//! \sa Telium Manager reference documentation.
int APCLESS_ServiceManager_MoreFunction(NO_SEGMENT appliId)
{
   int bContinue=1;
   char appName[12+1];

   // To avoid warnings because 'appliId' is not used
	(void)appliId;

   if (__APCLESS_ServicesManager_isDllTpassLoaded)
   {
      __APCLESS_ServiceManager_GetAppName(appliId, appName, sizeof(appName));

      // Menu management
      do
      {
         switch(APCLESS_Gui_Menu(appName, 0, __APCLESS_ServicesManager_MenuUser))
         {
            case 0: APCLESS_Explicit_DoTransaction(); break;         // Explicit do transaction
            case 1: APCLESS_ParamTrn_SetDebugTrace(TRUE); break;     // Debug trace on
            case 2: APCLESS_ParamTrn_SetDebugTrace(FALSE); break;    // Debug trace off
            default: bContinue=2; break;                             // Abort key pressed
         }
      } while(bContinue==1);
   }
   else
   {  // TPass Dll not found -> display error message
      APCLESS_Gui_Display_Error_No_TPass();
   }

   return FCT_OK;
}



