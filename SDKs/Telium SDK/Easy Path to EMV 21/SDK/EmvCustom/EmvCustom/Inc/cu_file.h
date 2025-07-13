/**
* \file cu_file.h
* \brief This module contains the functions allowing the saving of global variables, in
* case of power failure. The maximum allowed size for saving is 8 Ko.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

#ifndef CU_FILE_H
#define CU_FILE_H

//! \defgroup Group_cu_file Global data saving in case of power failure.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

//! \brief This structure defines global data saved in RAM.
typedef struct
{
	// unsigned long LogPointer;						//!< Current position of pointer in record batch file.
	DATE DateNextTransf;							//!< date of the next automatic data batch capture.
	unsigned char ucMode2000;						//!< Boolean indicating if EMV 2000 is supported.
	unsigned char g_no_serial [9];					//!< Serial number.
	unsigned char g_terminal_id [ 9 ] ;				//!< Terminal ID.
	unsigned short usDefaultCurrency;				//!< Default currency.
	unsigned char  ucDelayAfterAtr;					//!< Delay after answer to reset.
#ifdef _TOOLWARE_
	unsigned char ucAdvancedMode;
#endif
} STRUCT_GLOBAL_RAM_DATA;


/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */

#ifdef FILE_H
STRUCT_GLOBAL_RAM_DATA S_GlobalRamData;

/* **************************************************** */
/* Noms du fichier pour la sauvegarde des donnees en RAM */
/* **************************************************** */
/* Label pour les données globales à l'application */

const unsigned char LABEL_GLOBAL_DATA [] = "F_EMVCUST_DGLOB";


#else
extern STRUCT_GLOBAL_RAM_DATA S_GlobalRamData;		//!< Global variable used to store data in Ram.


//===========================================================================
// This function saves and restore global RAM data.
//===========================================================================
void FILE_Save_Restore_global_RAM_data (void);


#endif


// #define LogPointer			S_GlobalRamData.LogPointer				//!< alias on field, current position of pointer in record batch file, of global variable.
#define DateNextTransf		S_GlobalRamData.DateNextTransf			//!< alias on field, date of the next automatic data batch capture, of global variable.
#define ucMode2000			S_GlobalRamData.ucMode2000				//!< alias on field, Boolean indicating if EMV 2000 is supported, of global variable.
#define g_no_serial			S_GlobalRamData.g_no_serial				//!< alias on field serial number of global variable.
#define g_terminal_id		S_GlobalRamData.g_terminal_id			//!< alias on field terminal ID of global variable. 
#define usDefaultCurrency	S_GlobalRamData.usDefaultCurrency		//!< alias on field default currency of global variable.
#define ucDelayAfterAtr		S_GlobalRamData.ucDelayAfterAtr			//!< alias on field delay after answer to reset of global variable.
#ifdef _TOOLWARE_
#define ucAdvancedMode		S_GlobalRamData.ucAdvancedMode			//!< alias on field 
#endif

//! @}

#endif

