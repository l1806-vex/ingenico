/**
 *!\file GTL_SHA.h
 * \brief This file describes all the SHA cryptography features.
 *
 *
 * \author Ingenico
 * \author Copyright (c) 2009 Ingenico, 1 rue claude Chappe,\n
 *		   07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __GTL_SHA_H__INCLUDED__
#define __GTL_SHA_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Compute SHA.
//! \param[in] pInputData Data to be computed.
//! \param[in] nInputLength Length of \a pInputData.
//! \return Pointer on the SHA result.

unsigned long * GTL_SHA_Sha1Compute (const unsigned char *pInputData, const int nInputLength);



#endif // __GTL_SHA_H__INCLUDED__
