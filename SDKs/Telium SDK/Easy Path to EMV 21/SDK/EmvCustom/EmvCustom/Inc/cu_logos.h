/**
* \file cu_logos.h
* \brief This module contains the functions needed to print official logos on the receipt.
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


#ifndef CU_LOGOS_H
#define CU_LOGOS_H

//! \defgroup Group_cu_logo Official logos management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

#define VERTICAL_BAR					0xB3			//!< Default character definition for vertical bar.
#define HORIZONTAL_BAR					0xC4			//!< Default character definition for horizontal bar.
#define HORIZONTAL_BEGIN_BAR			0xA9			//!< Default character definition for horizontal begin bar.
#define HORIZONTAL_END_BAR				0xAA			//!< Default character definition for horizontal end bar.
#define HORIZONTAL_DOUBLE_BAR			0xCD			//!< Default character definition for horizontal double bar.
#define HORIZONTAL_BEGIN_DOUBLE_BAR		0xD5			//!< Default character definition for horizontal begin double bar.
#define HORIZONTAL_END_DOUBLE_BAR		0xB8			//!< Default character definition for horizontal end double bar.
#define LEFT_BOTTOM_ROUNDED_CORNER		0xC0			//!< Default character definition for left bottom rounded corner.
#define LEFT_TOP_ROUNDED_CORNER			0xDA			//!< Default character definition for left top rounded corner.
#define RIGHT_BOTTOM_ROUNDED_CORNER		0xD9			//!< Default character definition for right bottom rounded corner.
#define RIGHT_TOP_ROUNDED_CORNER		0xBF			//!< Default character definition for right top rounded corner.
#define EURO							0xEE			//!< Default character definition for euro.


/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function prints the Ingenico logo.
//===========================================================================
void	CULOGO_Print_Ingenico(void);

//===========================================================================
//! \brief This function prints a line. The max lenght of a line is 24 characters.
//! \param offset : number of empty char before the beginning of text.
//! \param length : length of the line.
//===========================================================================
void    CUPRINT_Boundary_Line(const short offset, const short length);

//===========================================================================
//! \brief This function prints many blanks lines. Used to feed paper.
//! \param lines_nb : number of blank lines to print.
//===========================================================================
void    CUPRINT_Blanks_Lines(const unsigned char lines_nb);

//===========================================================================
//! \brief This function redefines a list of characters by graphic patterns.
//===========================================================================
void	init_printer_extended_characters(void);

//===========================================================================
//! \brief This function desactivates previously defined patterns. The default
//! characters definitions are restored.
//===========================================================================
void	term_printer_extended_characters(void);

//===========================================================================
//! \brief This function closes the printer and redefines all default characters
//! necessary after use CUPRINT_XXXXXXXX functions.
//===========================================================================
void    CUPRINT_Close_Printer(void);

//===========================================================================
//! \brief This function opens the printer and defines extended characters
//! necessary before use all CUPRINT_XXXXXXXX functions.
//===========================================================================
void    CUPRINT_Open_Printer(void);

//! @}

#endif
