/**
 * \file
 * \brief Header file for the PayPass module.
 *
 * \author  Ingenico
 *
 * \author  Ingenico has intellectual property rights relating to the technology embodied \n
 *       in this software. In particular, and without limitation, these intellectual property rights may\n
 *       include one or more patents.\n
 *       This software is distributed under licenses restricting its use, copying, distribution, and\n
 *       and decompilation. No part of this software may be reproduced in any form by any means\n
 *       without prior written authorization of Ingenico.
 */


#ifndef APCLESS_PAYPASS_H_INCLUDED
#define APCLESS_PAYPASS_H_INCLUDED



/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define APCLESS_PAYPASS_MAX_NUMBER_OF_TORN_TXN_LOG_RECORDS            3       ///< Max number of Torn Transaction Log Records.


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

int APCLESS_PayPass_PerformTransaction(T_SHARED_DATA_STRUCT* dataStruct);
int APCLESS_PayPass_KernelCustomiseStep(T_SHARED_DATA_STRUCT* sharedData, const unsigned char ucCustomisationStep);


#ifdef PAYPASS_TORN
   unsigned int APCLESS_PayPassTorn_GetNumberOfTornTxnLogRecords(void);
   void APCLESS_PayPassTorn_CleanLog(void);
   int APCLESS_PayPassTorn_IsTornTxn(T_SHARED_DATA_STRUCT* sharedDataStruct);
   int APCLESS_PayPassTorn_AddRecord(T_SHARED_DATA_STRUCT* sharedDataStruct);
   int APCLESS_PayPassTorn_RemoveRecord(void);
#endif


#endif  //APCLESS_PAYPASS_H_INCLUDED

