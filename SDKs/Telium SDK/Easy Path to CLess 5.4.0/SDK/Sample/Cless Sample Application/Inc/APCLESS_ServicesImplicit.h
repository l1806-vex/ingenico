/**
* \file
* \brief This module implements all the services used for implicit transaction.
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
*/

#ifndef APCLESS_SERVICES_IMPLICIT_H_INCLUDED
#define APCLESS_SERVICES_IMPLICIT_H_INCLUDED

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

int APCLESS_ServicesImplicit_ClessGiveInfo(NO_SEGMENT appliId, S_TRANSIN* paramIn, S_CLESS_GIVEINFO* paramOut);
int APCLESS_ServicesImplicit_ClessDebitAid(NO_SEGMENT appliId, unsigned int size, void* data);
int APCLESS_ServicesImplicit_ClessEnd(NO_SEGMENT appliId);
int APCLESS_ServicesImplicit_CustomSelectionGui(unsigned int size, void* data);


#endif // APCLESS_SERVICES_IMPLICIT_H_INCLUDED
