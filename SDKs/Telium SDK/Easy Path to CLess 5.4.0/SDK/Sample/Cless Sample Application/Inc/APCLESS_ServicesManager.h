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

#ifndef APCLESS_SERVICES_MANAGER_H_INCLUDED
#define APCLESS_SERVICES_MANAGER_H_INCLUDED

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

//// Global variables ///////////////////////////////////////////


//// Functions //////////////////////////////////////////////////

int APCLESS_ServiceManager_AfterReset(NO_SEGMENT appliId, S_TRANSOUT *paramOut);
int APCLESS_ServiceManager_IsName(NO_SEGMENT appliId, S_ETATOUT *paramOut);
int APCLESS_ServiceManager_GiveYourDomain(NO_SEGMENT appliId, S_INITPARAMOUT *paramOut);
int APCLESS_ServiceManager_IsState(NO_SEGMENT appliId, S_ETATOUT *paramOut);
int APCLESS_ServiceManager_IsDelete(NO_SEGMENT appliId, S_DELETE *paramOut);
int APCLESS_ServiceManager_MoreFunction(NO_SEGMENT appliId);

#endif // APCLESS_SERVICES_MANAGER_H_INCLUDED
