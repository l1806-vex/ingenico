/**
 * \file
 * \brief Header file for the detection and selection step.
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

#ifndef APCLESS_SELECTION_H_INCLUDED
#define APCLESS_SELECTION_H_INCLUDED

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

// Selection method
#define APCLESS_SELECTION_UNKNOWN     0              ///< Application selection method is not defined.
#define APCLESS_SELECTION_IMPLICIT    1              ///< Application has been selected with the implicit selection method
#define APCLESS_SELECTION_EXPLICIT    2              ///< Application has been selected with the explicit selection method

/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

void APCLESS_Selection_SetMethod(int mode);

int APCLESS_Selection_GetMethod(void);

int APCLESS_Selection_GiveInfo(TLV_TREE_NODE * tlvTree, const int explicitSelection);

int APCLESS_Selection_GuiCustomisation(T_SHARED_DATA_STRUCT* dataStruct);


#endif //APCLESS_SELECTION_H_INCLUDED
