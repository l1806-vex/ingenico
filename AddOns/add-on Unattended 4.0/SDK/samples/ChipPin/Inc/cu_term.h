/**
* \file cu_term.h
* \brief This module contains the functions that manages the interface with the terminal.
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

#ifndef CU_TERM_H
#define CU_TERM_H

//! \defgroup Group_cu_term Terminal interface management.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

// #define L_ATRMAX				(4 + 15)			//!< Maximum number of bytes in answer to reset. 15 corresponds to the size of historical bytes. 4 corresponds to the size of system bytes.

#define KEYS_IN_BUFFER			0x20				//!< State definition indicating that a key was pressed.

#define DISK_SIZE				0x19000				//!< Disk size definition. 100kb.

#define LABEL_DISK				"E_CUST"			//!< Const part of Label_Disk_Name.
#define LABEL_FILE_BATCH_REC	"BAT_REC"			//!< Partial name of batch record file.
#define LABEL_FILE_BATCH_MNG	"BAT_MNG"			//!< Partial name of batch management file.


/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

//! \brief This enumerator defines common boolean type.
typedef enum
{
	B_FALSE = FALSE,								//!< FALSE value.
	B_TRUE  = TRUE,									//!< TRUE value.
	B_NON_INIT  = 0xFF								//!< Not initialised value.
} T_Bool;



//! \brief This enumerator defines the positions for displaying text on the screen.
typedef enum
{
	CENTER,											//!< The text is centered.
	LEFT,											//!< The text is left justified.
	RIGHT,											//!< The text is right justified.
	LEFTBLINK										//!< The text is blinking.
} T_CUTERMjustify;



//! \brief This enumerator defines the different keys for controlling the keyboard.
typedef enum
{
	ZERO = T_NUM0,									//!< Zero numerical key.
	ONE = T_NUM1,									//!< One numerical key.
	TWO = T_NUM2,									//!< Two numerical key.
	THREE = T_NUM3,									//!< Three numerical key.
	FOUR = T_NUM4,									//!< Four numerical key.
	FIVE = T_NUM5,									//!< Five numerical key.
	SIX = T_NUM6,									//!< Six numerical key.
	SEVEN = T_NUM7,									//!< Seven numerical key.
	EIGHT = T_NUM8,									//!< Eight numerical key.
	NINE = T_NUM9,									//!< Nine numerical key.
	T_F1 = T_SK1,									//!< Function 1 key.
	T_F2 = T_SK2,									//!< Function 2 key.
	T_F3 = T_SK3,									//!< Function 3 key.
	T_F4 = T_SK4,									//!< Function 4 key.
	CU_T_POINT = T_POINT,							//!< Dot key.
	T_STAR = 0x07,									//!< Star key.
	CU_VALID = T_VAL,								//!< Green key.
	CORRECT = T_CORR,								//!< Yellow key.
	CANCEL = T_ANN									//!< Red key.
} T_CUTERMkey;


//! \brief This enumerator defines the different printing modes.
typedef enum
{
	PRINT_NORMAL,									//!< The font is normal.
	PRINT_CONDENSED,								//!< The font is condensed.
	PRINT_LARGE										//!< The font is large.
} T_CUTERMprintMode;


/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */
extern T_Bool isPinpad;								//!< Boolean to know if a pinpad can be used.

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function clears the terminal display.
//===========================================================================
extern void CUTERMclearDisplay(void);

//===========================================================================
//! \brief This function allows to redefine two characters of the _dPOLICE4x7_ font.
//! It allows to have the STD_MESS_PROTECT_ENTER_PIN msg on two lines 
//! (for french or english).
//===========================================================================
extern void CUTERM_DefineNewChar(void);

//===========================================================================
//! \brief This function allows to restore previously defined characters of 
//! the _dPOLICE4x7_ font.
//===========================================================================
extern void CUTERM_RestoreChar(void);

//===========================================================================
//! \brief This function displays one line on the terminal.
//! \param[in] xi_line : line number on the terminal display.
//! \param[in] xs_text : text to be displayed.
//! \param[in] xt_justify : text justification mode :
//! - left justified
//! - centered
//! - right justified
//! - blinking
//! \param[in] mode : defines the displaying mode : 
//! - "w" : the screen is cleared before display.
//! - "a" : the screen is not cleared before display.
//===========================================================================
extern void CUTERMdisplayLine(int xi_line,
							  char *xs_text,
							  T_CUTERMjustify xt_justify,
							  char *mode);

//===========================================================================
//! \brief This function displays one line on the terminal in small graphic mode.
//! \param[in] xi_line : line number on the terminal display.
//! \param[in] xs_text : text to be displayed.
//! \param[in] xt_justify : text justification mode :
//! - left justified
//! - centered
//! - right justified
//! - blinking
//! \param[in] mode : defines the displaying mode : 
//! - "w" : the screen is cleared before display.
//! - "a" : the screen is not cleared before display.
//! \param[in] LongLine : boolean. If set to TRUE, a proportional font and
//! background will be used.
//===========================================================================
extern void CUTERMdisplayGraphicLine(int xi_line,
									 char *xs_text,
									 T_CUTERMjustify xt_justify,
									 char *mode,
									 char LongLine);

//===========================================================================
//! \brief This function returns the line and the column number switch
//! of the terminal display.
//! \param[out] xp_line : line number on the terminal display.
//! \param[out] xp_column : column number on the terminal display.
//===========================================================================
extern void CUTERMgetDisplay(int *xp_line, int *xp_column);

//===========================================================================
//! \brief This function returns the key pressed on the terminal,during 
//! the time-out delay given as parameter.
//! \param[in] xi_timeout : timeout (in ms) to get the key. 0 means immediate.
//! \param[in] xp_key : The key pressed if present. The function returns TRUE
//! in this case. The key can be : '0'-'9', ',', 'F1'-'F4', VALID, CORRECT, 
//! CANCEL.
//! \return
//! - TRUE if a key is present.
//! - FALSE otherwise. (timeout expired, keyboard unavailable).
//===========================================================================
extern T_Bool CUTERMgetKey(int xi_timeout, T_CUTERMkey* xp_key);

//===========================================================================
//! \brief This function tests if a printer is present.
//! \return
//! - TRUE if a printer is present.
//! - FALSE otherwise.
//===========================================================================
extern T_Bool CUTERIsPrinterPresent(void);


//===========================================================================
//! \brief This function processes a paper feed, so that the last printed 
//! line is visible.
//===========================================================================
extern void CUTERMpaperFeed(void);


//===========================================================================
//! \brief This function prints the text and wait for the end of the job, 
//! up to 5 seconds.
//! \param[in] xs_text : text to be printed.
//===========================================================================
extern void CUTERMprintLine(char *xs_text);

//===========================================================================
//! \brief This function changes the printing mode on the printer.
//! \param[in] xt_mode : printing mode : 
//! - PRINT_NORMAL
//! - PRINT_CONDENSED
//! - PRINT_LARGE
//===========================================================================
extern void CUTERMsetPrinter(T_CUTERMprintMode xt_mode);

//===========================================================================
//! \brief This function sleeps for a time, given as parameter.
//! \param[in] xi_delay : sleep duration (in ms).
//===========================================================================
extern void CUTERMsleep(int xi_delay);



//===========================================================================
//! \brief This function is used to know the serial number of the terminal.
//! \param[out] no_serial : terminal serial number. Coded on 8 characters.
//===========================================================================
extern void CUTERMgetSerialNumber(char *no_serial);

//===========================================================================
//! \brief This function is used to init the serial number of the terminal.
//! \param[in] no_serial : new serial number.
//===========================================================================
extern void CUTERMsetSerialNumber(char *no_serial);

//===========================================================================
//! \brief This function returns the pin code.
//! \param[in] TO_first_car : first character timeout.
//! \param[in] TO_inter_car : inter character timeout.
//! \param[out] xp_pin : pointer on entry buffer.
//! \return The pinpad entry report : 
//! - 0 : pinpad entry is successfull.
//! - TO_INPUT : the pinpad timeout has expired.
//! - CANCEL_INPUT : the pinpad input is canceled.
//! - ERROR_INPUT : pinpad entry not ok.
//! - PP_HS : the pinpad is out of service.
//===========================================================================
extern unsigned char CUTERMgetPPpin (short TO_first_car, short TO_inter_car, ENTRY_BUFFER *xp_pin);

//===========================================================================
//! \brief This function tests if a pinpad is present.
//! \return 
//! - TRUE if a pinpad is present.
//! - FALSE otherwise.
//===========================================================================
extern T_Bool CUTERIsPinpadPresent(void);

//===========================================================================
//! \brief This function returns the line and the column number of the pinpad
//! display.
//! \param[out] xp_line : line number on the pinpad display.
//! \param[out] xp_column : column number on the pinpad display.
//! \note The function sets *xp_line, and *xp_column to 0 if no pinpad is present.
//===========================================================================
extern void CUTERMgetPPdisplay(int *xp_line, int *xp_column);

//===========================================================================
//! \brief This function displays one line on the pinpad.
//! \param[in] xi_line : line number on the pinpad display.
//! \param[in] xs_text : text to be displayed.
//! \param[in] xt_justify : text justification mode :
//! - left justified
//! - centered
//! - right justified
//! - blinking
//! \return
//! - 0 if the line display is successfull.
//! - 1 otherwise.
//===========================================================================
extern int CUTERMdisplayPPline(int xi_line, char *xs_text, T_CUTERMjustify xt_justify);

//===========================================================================
//! \brief This function tests if a declared pinpad is present. (PP30,PPC30,PPR30).
//! \param[in] xs_text : text to be displayed.
//! \return
//! - TRUE if there is no pinpad, or if declared pinpad is present.
//! - FALSE otherwise.
//===========================================================================
unsigned char CUTERIsDeclaredPPPresent(char *xs_text);
// unsigned char CUTERMisPPOk(char *xs_text);

//===========================================================================
//! \brief This function is used to know the the card acceptor terminal id.
//! \param[out] term_id : the card acceptor terminal Id.
//===========================================================================
extern void	CUTERMgetTerminalId(char *term_id);

//===========================================================================
//! \brief This function is used to set the the card acceptor terminal id.
//! \param[in] term_id : the card acceptor terminal Id.
//===========================================================================
extern void	CUTERMsetTerminalId(char *term_id);

//===========================================================================
//! \brief This function clears the pinpad display. If the pinpad is not present, 
//! the function has no effect.
//===========================================================================
extern void	CUTERMclearPPdisplay(void);

//===========================================================================
//! \brief This function waits for validation or correction key input.
//! This function may be used on ML30, EFT ... products.
//! \param[in] xi_timeout : key waiting time (in seconds).
//! \param[in] mask : mask to forbid keys.
//! \param[in] xp_key : entered key.
//! \return 
//! - TRUE if the entered key is validation or correction.
//! - FALSE otherwise.
//===========================================================================
extern T_Bool CUTERM_Wait_function_key(byte xi_timeout, word mask, T_CUTERMkey *xp_key);

//===========================================================================
//! \brief This function tests if graphical functions can be used on PPAD.
//! \return
//! - TRUE : graphical functions can be used on PPAD.
//! - FALSE : graphical functions cannot be used on PPAD.
//===========================================================================
extern char CUTERMIsGraphicPP(void);

//! @}

#endif

