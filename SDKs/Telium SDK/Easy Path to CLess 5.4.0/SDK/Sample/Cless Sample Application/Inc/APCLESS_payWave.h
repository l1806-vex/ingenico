/**
 * \file
 * \brief Header file of the Visa payWave module.
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


#ifndef APCLESS_PAYWAVE_H_INCLUDED
#define APCLESS_PAYWAVE_H_INCLUDED


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

int APCLESS_payWave_PerformTransaction(T_SHARED_DATA_STRUCT* dataStruct);
int APCLESS_payWave_KernelCustomiseStep(T_SHARED_DATA_STRUCT* sharedData, const unsigned char ucCustomisationStep);

#endif  //APCLESS_PAYWAVE_H_INCLUDED

