/**
* \file cu_wgui.h
* \brief This module contains the functions needed color management.
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

#ifndef CU_WGUI_H
#define CU_WGUI_H

//! \defgroup Group_cu_wgui Web graphical user interface.
//! @{

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/
/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////
#define E_USER_EVENT_PIN    29							// User event offset
#define USER_EVENT_PIN     	1 << E_USER_EVENT_PIN  		// User event	
#define E_USER_EVENT		30							// User event offset
#define USER_EVENT			1 << E_USER_EVENT			// User event	

#define E_USER_EVENT_START	31							// User event offset
#define USER_EVENT_START	1 << E_USER_EVENT_START		// User event	

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

/* ======================================================================== */
/* Global variables                                                         */
/* ======================================================================== */

extern const char file_dir[];				//!< Path for icons in resources file.

/* ======================================================================== */
/* Global function declarations                                             */
/* ======================================================================== */

//===========================================================================
//! \brief This function gets the icon name of the icon given as number.
//! \param[in] num_icon : icon number.
//! \param[out] icon_name : icon name.
//===========================================================================
void CUWGUI_load_icon(int num_icon, char **icon_name);

//===========================================================================
//! \brief This function gets the icon name of the language icon given as number.
//! \param[in] num_lang : language number.
//! \param[out] icon_name : icon name.
//===========================================================================
void CUWGUI_load_flag_icon(char num_lang, char **icon_name);

//===========================================================================
//! \brief This function gets the icon name for the list item given by the 
//! parameter index.
//! \param[in] index : list index.
//! \param[out] icon_name : icon name.
//===========================================================================
void CUWGUI_load_yesno_icon(int index, char **icon_name);

//===========================================================================
//! \brief This function gets the icon name for the list item given by the 
//! parameter index.
//! \param[in] index : list index.
//! \param[out] icon_name : icon name.
//===========================================================================
void CUWGUI_load_trans_icon(int index, char **icon_name);

//===========================================================================
//! \brief This function inits the icon list structure : footer messages... 
//! \param[in,out] pIconList : pointer to structure wIconList.
//===========================================================================
void CUWGUI_InitIconList(wIconList *pIconList);

//===========================================================================
//! \brief This function inits the WGUI list structure : footer messages... 
//! \param[in,out] pWguiList : pointer to structure wGuiStructList.
//===========================================================================
void CUWGUI_InitStructList(cGuiStructList *pWguiList);

//===========================================================================
//! \brief This function inits the WGUI entry structure : footer messages... 
//! \param[in,out] pWguiEntry : pointer to structure wGuiStructEntry.
//===========================================================================
void CUWGUI_InitStructEntry(cGuiStructEntry *pWguiEntry);

//===========================================================================
//! \brief This function displays the html page used for pin code entry.
//! \param[in] pcline1 : pointer to message of line 1.
//! \param[in] pcline2 : pointer to message of line 2.
//! \param[in] pcline3 : pointer to message of line 3.
//! \param[in] pcline4 : pointer to message of line 4.
//! \param[in] WGUI_Browser : Browser used to display html page.
//===========================================================================
void CUWGUI_DisplayEnterPin(char *pcline1, char *pcline2, char *pcline3, char *pcline4, WGUI_BROWSER_HANDLE WGUI_Browser);

//===========================================================================
//! \brief This function sends the key given by security scheme to the html page 
//! used for pin code entry.
//! \param[in] inputkey : key given by scheme.
//! \param[in] WGUI_Canvas : Browser used to display html page.
//===========================================================================
void CUWGUI_DisplayPinLine(char inputkey, WGUI_CANVAS_HANDLE WGUI_Canvas);


//===========================================================================
//! \brief This function desactivates the leds, the header, get the current 
//! canvas used by manager, resizes and moves it.
//===========================================================================
void CUWGUI_InitBrowser(void);

//===========================================================================
//! \brief This function activates the header, the leds, resizes and moves 
//! the given canvas.
//===========================================================================
void CUWGUI_RestoreBrowser(void);

//! @}

#endif

