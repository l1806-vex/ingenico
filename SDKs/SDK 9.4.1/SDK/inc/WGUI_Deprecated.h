/*
* $Id: WGUI_Deprecated.h,v 1.1.2.4 2012/01/31 10:47:24 nthibert Exp $
*
* Copyright (c) 2008 SAGEM Monetel, rue claude Chappe,
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* SAGEM Monetel SA has intellectual property rights relating
* to the technology embodied in this software.  In particular,
* and without limitation, these intellectual property rights
* may include one or more patents.
*
* This software is distributed under licenses restricting
* its use, copying, distribution, and decompilation.
* No part of this software may be reproduced in any form
* by any means without prior written authorization of
* SAGEM Monetel.
*
* Description:  Web browser and graphical user interface
*
*/
#ifndef WGUI_Deprecated_h_INCLUDED
#define WGUI_Deprecated_h_INCLUDED



#ifdef __cplusplus
extern "C"
{
#endif

	

/** @cond NO_DOC*/
#ifndef EXPORT
	#ifdef WIN32
		#define EXPORT __declspec (dllexport)
	#else
		#define EXPORT 
	#endif
#endif
/** @endcond */
	
/**
@addtogroup WGUI_Api
@{
*/

// *************************************************************************************
// *************************************************************************************
/**
@addtogroup WGUI_Display 
@{
	This module is used to manage the physical display.
	Cgui can manage the full display, but to avoid some compatibility problems with existing applications 
	like the manager, CGui can reduce the refresh area onto the display. 
	In all case Cgui manage entirely the display, a window coordinates is positionned according to the top left corner 
	of the physical display. The refresh area can be smaller or equal to the physical display; it cannot be
	greater than the physical display. 
	All pixels located out of the refreshed area will be never displayed.
*/
// *************************************************************************************
// *************************************************************************************

/** <b> Deprecated 
This function will now only mark the calling application as compatible. The compatible application have the font size adjusted 
to be GOAL compliant and their canvas are created in absolute position of the screen like before</b>
@cond FULL_DOC
Create and initialize display. 
The WGUI rendering can be shared with other application on the same physical display.
This function initialize position of the WGUI rendering display. Only one display can be initialized for all
applications. If the display has been previously initialized, this function returns the error 
@ref WGUI_DISPLAY_ALREADY_CREATE_ERR, this error is not blocking, 
you can display a browser, but you cannot destroy the display with @ref WGUI_Display_Destroy.
@endcond
@param x x coordinates in pixels of the rendering in the physical display (0 right corner)
@param y y coordinates in pixels of the rendering in the physical display (0 top corner)
@param width width in pixels of the rendering in the physical display (0xFFFFFFFF full width)
@param height height in pixels of the rendering in the physical display (0xFFFFFFFF full height)
@param type display type 
@return error */
EXPORT WGUI_ERROR WGUI_Display_Create(unsigned int x, unsigned int y, unsigned int width, unsigned int height, WGUI_DISPLAY_TYPE type);

/** <b> Deprecated 
This function will now only mark the calling application as compatible. The compatible application have the font size adjusted 
to be GOAL compliant and their canvas are created in absolute position of the screen like before</b>

@cond FULL_DOC
Resize and move the refreshed area
@endcond
@param x x position in pixels on screen 
@param y y position in pixels on screen
@param width screen width in pixels (-1 full screen)
@param height screen height in pixels (-1 full screen) */
EXPORT void WGUI_Display_Resize(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

/** <b> Deprecated </b>
@cond FULL_DOC
Destroy the display allocated
@endcond
@return error code */
EXPORT WGUI_ERROR WGUI_Display_Destroy(void);

/**
@}
@}
*/

#ifdef __cplusplus
}
#endif

#endif // WGUI_Deprecated_h_INCLUDED
