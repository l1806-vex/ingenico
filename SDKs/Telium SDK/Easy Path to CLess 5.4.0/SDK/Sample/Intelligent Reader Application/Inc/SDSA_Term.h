/**
 * \file	SDSA_Term.h
 * \brief 	Module for messages management.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __SDSA_TERM_H__INCLUDED__
#define __SDSA_TERM_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

// Name of the messages file that can be loaded in the terminal for messages customisation
#define SDSA_MSG_FILE				"/SYSTEM/SDSAMSG"	


//// Types //////////////////////////////////////////////////////


//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////


//! \brief This function initialise Messages menagement. 

void SDSA_Term_Initialise(void);



//! \brief Get the languages supported by the application.
//! \param[in] ulBufferSize Size in bytes of pSupportedLanguages.
//! \param[out] pSupportedLanguages Contains the supported languages code according to ISO 639-1 (up to 24 bytes, we consider the device can support 12 different languages at maximum).
//! \param[out] pNumberOfSupportedLanguages Number of supported languages.
//! \return
//!	- TRUE if supported languages correctly got.
//!	- FALSE if an error occurred.

int SDSA_Term_GetSupportedLanguages (char * pSupportedLanguages, const unsigned long ulBufferSize, unsigned long * pNumberOfSupportedLanguages);


#endif //__SDSA_TERM_H__INCLUDED__
