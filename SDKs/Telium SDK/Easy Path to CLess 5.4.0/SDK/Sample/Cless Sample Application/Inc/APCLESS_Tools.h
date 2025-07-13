/**
 * \file
 * \brief Header file for the tool functions of the Sample of Easy Path to Contactless.
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

#ifndef APCLESS_TOOLS_H_INCLUDED
#define APCLESS_TOOLS_H_INCLUDED

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////



/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

void APCLESS_Tools_ConvertAsciiToBcd(char* ascii, int asciiLen, unsigned char* pBcd, int iShift);

int APCLESS_Tools_SharedBufferRetrieveInfo (T_SHARED_DATA_STRUCT* sharedData, unsigned long tag, unsigned char ** info);

int APCLESS_Tools_NumberOfDaysBetweenTwoDates (DATE *date1, DATE *date2);

#endif //APCLESS_TOOLS_H_INCLUDED
