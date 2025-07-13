/**
* \brief This module implements the services provided by the application.
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

#define __APCLESS_SERVICES_PRIORITY_DEFAULT           30       //!< Default priority for services.
#define __APCLESS_SERVICES_PRIORITY_IDLE_MSG          70       //!< Priority of the idle message service.

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

static int __APCLESS_ServicesManager(unsigned int size, StructPt *data);
static int __APCLESS_ServicesCless(unsigned int size, StructPt *data);
static void __APCLESS_GiveInterface(unsigned short appliId);

void entry(void);

//// Global variables ///////////////////////////////////////////

//! \brief Array used to declare all the supported services to the system.
static service_desc_t __APCLESS_theServices[] = {
   { 0, AFTER_RESET, (SAP)__APCLESS_ServicesManager, __APCLESS_SERVICES_PRIORITY_DEFAULT },
   { 0, IS_NAME , (SAP)__APCLESS_ServicesManager, __APCLESS_SERVICES_PRIORITY_DEFAULT },
   { 0, GIVE_YOUR_DOMAIN, (SAP)__APCLESS_ServicesManager, __APCLESS_SERVICES_PRIORITY_DEFAULT },
   { 0, IS_STATE, (SAP)__APCLESS_ServicesManager, __APCLESS_SERVICES_PRIORITY_DEFAULT },
   { 0, IS_DELETE, (SAP)__APCLESS_ServicesManager, __APCLESS_SERVICES_PRIORITY_DEFAULT },
   { 0, MORE_FUNCTION, (SAP)__APCLESS_ServicesManager, __APCLESS_SERVICES_PRIORITY_DEFAULT },

   { 0, CLESS_GIVE_INFO, (SAP)__APCLESS_ServicesCless, __APCLESS_SERVICES_PRIORITY_DEFAULT },
   { 0, CLESS_DEBIT_AID, (SAP)__APCLESS_ServicesCless, __APCLESS_SERVICES_PRIORITY_DEFAULT },
   { 0, CLESS_END, (SAP)__APCLESS_ServicesCless, __APCLESS_SERVICES_PRIORITY_DEFAULT },

   { 0, CLESS_SERVICE_CUST_IMPSEL_GUI, (SAP)__APCLESS_ServicesCless, __APCLESS_SERVICES_PRIORITY_DEFAULT },
   { 0, SERVICE_CUSTOM_KERNEL, (SAP)__APCLESS_ServicesCless, __APCLESS_SERVICES_PRIORITY_DEFAULT },

};

//// Functions //////////////////////////////////////////////////

//! \brief The entry point for all the Telium Manager services.
//! \param[in] size Size of the data \a data.
//! \param[in,out] data Data related to the called service.
static int __APCLESS_ServicesManager(unsigned int size, StructPt *data)
{
   NO_SEGMENT appliId;
   int result;

   // To avoid warnings because 'size' is not used
   (void)size;

   // Get the application number
   appliId = (NO_SEGMENT)ApplicationGetCurrent();
   // Execute the requested service
   switch(data->service)
   {
      case AFTER_RESET:
         result = APCLESS_ServiceManager_AfterReset(appliId, &data->Param.AfterReset.param_out);
         break;
      case IS_NAME:
         result = APCLESS_ServiceManager_IsName(appliId, &data->Param.IsName.param_out);
         break;
      case GIVE_YOUR_DOMAIN:
         result = APCLESS_ServiceManager_GiveYourDomain(appliId, &data->Param.GiveYourType.param_out);
         break;

      case IS_STATE:
         result = APCLESS_ServiceManager_IsState(appliId, &data->Param.IsState.param_out);
         break;

      case IS_DELETE:
         result = APCLESS_ServiceManager_IsDelete(appliId, &data->Param.IsDelete.param_out);
         break;

      case MORE_FUNCTION:
         result = APCLESS_ServiceManager_MoreFunction(appliId);
         break;

      default:
         result = FCT_OK;
         ASSERT(FALSE);
         break;
   }

   return result;
}


//! \brief The entry point for all the Contactless services.
//! \param[in] size Size of the data \a data.
//! \param[in,out] data Data related to the called service.
static int __APCLESS_ServicesCless(unsigned int size, StructPt *data)
{
   NO_SEGMENT appliId;
   int result;

   // To avoid warnings because 'size' is not used
   (void)size;

   // Get the application number
   appliId = (NO_SEGMENT)ApplicationGetCurrent();
   // Execute the requested service
   switch(data->service)
   {
      // Implicit Selection Services
      case CLESS_GIVE_INFO:
         result = APCLESS_ServicesImplicit_ClessGiveInfo(appliId, &data->Param.ClessGiveInfo.param_in, &data->Param.ClessGiveInfo.param_out);
         break;

      case CLESS_DEBIT_AID:
         result = APCLESS_ServicesImplicit_ClessDebitAid(appliId, size, data);
         break;

      case CLESS_END:
         result = APCLESS_ServicesImplicit_ClessEnd(appliId);
         break;

      case CLESS_SERVICE_CUST_IMPSEL_GUI:
         result = APCLESS_ServicesImplicit_CustomSelectionGui(size, data);
         break;

      // Kernel services   APCLESS_ServicesKernel_Custom
      case SERVICE_CUSTOM_KERNEL:
         result = APCLESS_ServicesKernel_Custom(size, data);
         break;


      default:
         result = FCT_OK;
         ASSERT(FALSE);
         break;
   }

   return result;
}



//! \brief This function registers all the services of the application to the system.
//! \param[in] appliId Application system identifier.
static void __APCLESS_GiveInterface(unsigned short appliId)
{
   int index;

   // Initialise the application type in the table of supported services
   for(index = 0; index < (int)(sizeof(__APCLESS_theServices) / sizeof(__APCLESS_theServices[0])); index++)
      __APCLESS_theServices[index].appli_id = appliId;

   // Register services
   ServiceRegister((sizeof(__APCLESS_theServices) / sizeof(__APCLESS_theServices[0])), __APCLESS_theServices);
}

//! \brief This function is the main function of the application.
//! The objective of this function is to declare the supported services.
void entry(void)
{
   object_info_t info;

   // TODO: Initialise the global variables
   // Do It here to ensure that global variables are initialised before any service call
   // Be careful to only INITIALISE the global variables and not doing treatments (loading files, use display, ...)

   ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &info);
   __APCLESS_GiveInterface(info.application_type);
}

