/**
 * \file
 * \brief Header file for the kernel parameters initialisation.
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

#ifndef APCLESS_KERNEL_H_INCLUDED
#define APCLESS_KERNEL_H_INCLUDED

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


int APCLESS_Kernel_AddTransactionGenericData(T_SHARED_DATA_STRUCT* kernelSharedData);

int APCLESS_Kernel_AddAidRelatedData (T_SHARED_DATA_STRUCT* selectionSharedData, T_SHARED_DATA_STRUCT* kernelSharedData, int* kernelToUse);


#endif //APCLESS_KERNEL_H_INCLUDED
