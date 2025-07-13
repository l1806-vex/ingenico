/*
* $Id: WGUI_Deprecated.h,v 1.1.2.8 2013/01/14 08:03:20 nthibert Exp $
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

#if !defined(MACRO_DEPRECATED)
#if defined(__GNUC__)
#define MACRO_DEPRECATED __attribute__ ((deprecated))
#else
#define MACRO_DEPRECATED
#endif
#endif


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
@defgroup WGUI_DLL			DLL
@defgroup WGUI_Display		Display
@defgroup WGUI_Canvas		Canvas
@defgroup WGUI_Browser		Browser
@defgroup WGUI_HtmlEvent	HTML events
@defgroup WGUI_PrintJob		Printer
@defgroup WGUI_Template		Template
@defgroup WGUI_JSON			JSON
@defgroup WGUI_Keymap		Keymap
@defgroup WGUI_Resource		Resource
@defgroup WGUI_Tool			Tools
@defgroup WGUI_Proxy		Proxy
@defgroup WGUI_Plugin		Plugin
@defgroup WGUI_Type			Types
@defgroup WGUI_Errors		Errors
*/

// *************************************************************************************
// *************************************************************************************
/**
@addtogroup WGUI_Type
@{
*/
// *************************************************************************************
// *************************************************************************************

/** Canvasa data structure declaration */
struct WGUI_CANVAS;

/** Canvas handle declaration */
typedef struct WGUI_CANVAS * WGUI_CANVAS_HANDLE;


/** Browser data structure declaration */
struct WGUI_BROWSER;

/** Browser handle declaration */
typedef struct WGUI_BROWSER * WGUI_BROWSER_HANDLE;

/** Html event data structure declaration */
struct WGUI_HTML_EVENT;

/** Html event handle definition */
typedef struct WGUI_HTML_EVENT * WGUI_HTML_EVENT_HANDLE;

/** Print job */
struct WGUI_PRINT_JOB;

/** Print job handle */
typedef struct WGUI_PRINT_JOB * WGUI_PRINT_JOB_HANDLE;

/** JSON data structure declaration */
struct WGUI_JSON;

/** JSON handle declaration */
typedef struct WGUI_JSON * WGUI_JSON_NODE;

/** Wide char declaration */
typedef unsigned short WGUI_WCHAR;

/** Boolean definition */
typedef enum WGUI_BOOL
{
	WGUI_FALSE = 0,
	WGUI_TRUE  = 1
} WGUI_BOOL;


// *************************************************************************************
// *************************************************************************************
/**
@}
@addtogroup WGUI_Browser
@{
*/
// *************************************************************************************
// *************************************************************************************

/** Options that can be set by @ref WGUI_Browser_SetOption function */
typedef enum WGUI_BROWSER_OPTION
{
	WGUI_BROWSER_LOADING_BAR_DELAY,         ///< set the delay before displaying the loading bar in ms, @ref WGUI_INFINITE to deactivate
	WGUI_BROWSER_TEMPLATE_MODE,             ///< set the mode of the template parser value to be taken in @ref WGUI_TEMPLATE_MODE
	WGUI_BROWSER_TEXT_CURSOR_WIDTH,			///< set the width of the text editing cursor value to be taken in @ref WGUI_TEXT_CURSOR_WIDTH
	WGUI_BROWSER_SCROLLBAR_WIDTH,			///< set the scrollbar width value in px or -1 for default (must be set before displaying a page and not in a dispatch loop)
	WGUI_BROWSER_SCROLLBAR_BUTTON_HEIGHT,	///< set the scrollbar button height value in px or -1 for default (must be set before displaying a page and not in a dispatch loop)
	WGUI_BROWSER_TEXTAREA_OLD_STYLE_FOCUS	///< set the textarea focus style. true for old style : got to the end of the textarea on focus. false (default) don't change position when focus
}WGUI_BROWSER_OPTION;

/** Values of the option in case of @ref WGUI_BROWSER_TEMPLATE_MODE */
typedef enum WGUI_TEMPLATE_MODE
{
	WGUI_TEMPLATE_NONE,     ///< deactivate the template parser
	WGUI_TEMPLATE_ACTIVATE 	///< activate template parser
}WGUI_TEMPLATE_MODE;

/** Values of the @ref WGUI_BROWSER_TEXT_CURSOR_WIDTH option */
typedef enum WGUI_TEXT_CURSOR_WIDTH
{
	WGUI_TEXT_CURSOR_NORMAL = 1,	///< Normal cursor size (1px large)
	WGUI_TEXT_CURSOR_MEDIUM,		///< Medium cursor size (2px large)
	WGUI_TEXT_CURSOR_LARGE			///< Large cursor size (3px large)
}WGUI_TEXT_CURSOR_WIDTH;


// *************************************************************************************
// *************************************************************************************
/**
@}
@addtogroup WGUI_Errors
@{
	This part define all error codes returned by the WGUI functions.
*/
// *************************************************************************************
// *************************************************************************************

/** Errors codes */
typedef enum WGUI_ERROR
{
	//keep the comment under it's for doxygen presentation

	WGUI_OK                          =  0,      ///< Execution is successful
	WGUI_FAILED                      = -1,      //!< Execution has failed
	WGUI_INVALID_HANDLE              = -2,      //!< The handle is not valid
	WGUI_INVALID_PARAMETER           = -3,      //!< Invalid parameter or null pointer detected
	WGUI_NOT_YET_IMPLEMENTED         = -4,      //!< A feature used is not yet available
	WGUI_MEMORY_ERROR				 = -5,		//!< Memory allocation error

	///< <b> Element errors codes</b>
	WGUI_ELEMENT_INVALID_ERROR       = -100,    //!< Element is not valid
	WGUI_ELEMENT_INVALID_HANDLE,                //!< The handle is not valid
	WGUI_ELEMENT_NOT_FOUND,                     //!< Element not found in the document

	///< <b> @ref WGUI_Resource errors codes</b>
	WGUI_RESOURCE_READ_FAILED        = -200,    //!< The resource file cannot be read
	WGUI_RESOURCE_TOO_MANY,                     //!< Too many resources have been defined

	///< <b> Document errors codes </b>
	WGUI_DOCUMENT_INVALID_HANDLE     = -300,    //!< Document handle is not valid
	WGUI_DOCUMENT_CANNOT_OPEN,                  //!< Cannot open document url

	///< <b> @ref WGUI_Browser errors codes </b>
	WGUI_BROWSER_BAD_URL             = -400,	//!< URL can't be resolved by WGUI
	WGUI_BROWSER_OPTION_UNSUPPORTED,            //!< trying to set an unknown option
	WGUI_BROWSER_NO_EVENT_RECEIVED,             //!< indicates that no html event was received

	///< <b> @cond FULL_DOC @ref @endcond WGUI_JS errors codes </b>
	WGUI_JS_VALUE_NULL               = -500,    //!< Value pointer is null
	WGUI_JS_INVALID_CONTEXT,                    //!< Context pointer is null or some data corrupted
	WGUI_JS_PARAM_NOT_FOUND,                    //!< The parameter is not found

	///< <b> @ref WGUI_Proxy errors codes </b>
	WGUI_PROXY_TOO_MANY_ERROR        = -600,    //!< Too many proxies registered
	WGUI_PROXY_ALREADY_EXISTING,                //!< The proxy cannot be registered, previous proxy existing with the same name
	WGUI_PROXY_NOT_FOUND,                       //!< The proxy registered cannot be found
	WGUI_PROXY_LOADING_ERROR,                   //!< Can't load the proxy or initialise the DLL
	WGUI_PROXY_MEMORY_ERROR,                    //!< No more memory available

	///< <b> @ref WGUI_Template error codes </b>
	WGUI_TEMPLATE_MEMORY_ERROR       = -700,    //!< No more memory available
	WGUI_TEMPLATE_ALREADY_DEFINED,              //!< tag is already defined
	WGUI_TEMPLATE_NOT_FOUND,                    //!< tag not found

	///< <b> @ref WGUI_HtmlEvent errors codes</b>
	WGUI_HTML_EVENT_VAR_NOT_FOUND     = -800,    //!< Event name not found in variables list
	WGUI_HTML_EVENT_BUFFER_TOO_SMALL,            //!< Buffer passed in parameters is too small
	WGUI_HTML_EVENT_NO_URL,                      //!< No url available (this is normal with html event type reset)
	WGUI_HTML_EVENT_RESPONSE_UNSUPPORTED,        //!< Can't set the response in the event (normal with all event but XHR)
	WGUI_HTML_EVENT_INVALID,					 //!< Invalid event handle

	///< <b> @ref WGUI_Canvas error codes </b>
	WGUI_CANVAS_OUTPUT_NOT_SUPPORTED = -900,      //!< Canvas output type not supported

	///< <b> @ref WGUI_Display error codes </b>
	WGUI_DISPLAY_LOCKED_ERR          = -1000,     //!< The display cannot be destroyed it is locked by other application
	WGUI_DISPLAY_ALREADY_CREATE_ERR,              //!< The display has been already initialized by another application and cannot be modified
	WGUI_DISPLAY_ALREADY_DESTROY_ERR,             //!< The display has been already destroyed
	WGUI_DISPLAY_WINDOW_MANAGER_ERR,              //!< The windows manager cannot be opened

	///< <b> @ref WGUI_PrintJob error codes </b>
	WGUI_PRINT_JOB_PRINTING          = -1100,     //!< The print is not ended
	WGUI_PRINT_JOB_PAPER_OUT,                     //!< Paper is needed
	WGUI_PRINT_JOB_PENDING,                       //!< Previous job not yet terminated
	WGUI_PRINT_JOB_PROBLEM,                       //!< Print failed for any reason

	///< <b> @ref WGUI_Plugin error codes </b>
	WGUI_PLUGIN_NOT_FOUND_ERROR     = -1200,      //!< The plugin DLL cannot be loaded (Dll file is not present)
	WGUI_PLUGIN_GET_PROC_ADDRESS_ERROR,           //!< The DLL getprocaddress cannot be found in DLL
	WGUI_PLUGIN_NO_ENTRY_POINT_ERROR,             //!< Plugin entry point (WGUI_Plugin_Init function) not found in the DLL
	WGUI_PLUGIN_ALREADY_REGISTERED_ERROR,         //!< A plugin with the same mime type selected has already been registered
	WGUI_PLUGIN_MISSING_FUNCTION_ERROR,           //!< The plugin cannot be registered : mandatory callback function not defined in the plugin (See MANDATORY FUNCTION)
	WGUI_PLUGIN_UNREGISTER_ERROR,                 //!< The plugin unregister failed for any reason (unable to unload DLL)

	///< <b> @ref WGUI_JSON error codes </b>
	WGUI_JSON_JS_OBJECT_DESTROYED   = -1300,      //!< The JavaScript object used is already destroyed
	WGUI_JSON_JS_OBJECT_NO_CALLBACK,			  //!< The JavaScript object used has no callback function to call (onreadystatechange)
	WGUI_JSON_JS_OBJECT_CALLBACK_FAILED,		  //!< The JavaScript object callback failed to be called
	WGUI_JSON_CREATION_FAILED,					  //!< JSON object creation failed
	WGUI_JSON_NOT_AN_ARRAY,						  //!< JSON node is not an array
	WGUI_JSON_NOT_AN_OBJECT						  //!< JSON node is not an object

} WGUI_ERROR;

/**
@}
*/

// *************************************************************************************
// *************************************************************************************
/**
@addtogroup WGUI_DLL            
@{
This API is used to initialize the DLL and connect all applications functions to the DLL. 
Cgui browser must be always initialized before the first use. 
*/
// *************************************************************************************
// *************************************************************************************

#ifndef SWIG
/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
This function must be called before any other API calls are made.
Load WGUI_ DLL and initialize WGUI library */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_DLL_Init ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/** This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_DLL_Init(void) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
This function should be called when then application exits, UnLoad WGUI_ DLL */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_DLL_Terminate ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_DLL_Terminate(void) MACRO_DEPRECATED;
#endif


#endif

/** */
typedef struct DLL_Version
{
	/** DLL version number */
	unsigned int version;

	/** DLL revision number */
	unsigned int revision;
} DLL_Version;

/**  @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
Get the DLL version information
@return Version revision info */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_DLL_GetVersion ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT DLL_Version WGUI_DLL_GetVersion(void) MACRO_DEPRECATED;
#endif


// *************************************************************************************
// *************************************************************************************
/**
@}
@addtogroup WGUI_Display 
@{
	@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.

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

/** All display type */
typedef enum WGUI_DISPLAY_TYPE
{
	WGUI_DISPLAY_BLACK_WHITE,    //<! <b> deprecated </b> black and white display selected (Not yet available)
	WGUI_DISPLAY_COLORS          //<! <b> deprecated </b> color display selected
#ifdef WIN32
	,WGUI_DISPLAY_12BPP_COLORS   //<! <b> deprecated </b> color display selected (only for windows display)
#endif
	,WGUI_DISPLAY_HADWARE		 //<! for creating display, mode is the screen capabilities
} WGUI_DISPLAY_TYPE;

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
Get display informations, size in pixels and type
@param width pointer to physical screen width in pixels
@param height pointer to physical screen height in pixels
@param type pointer to type of screen */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Display_GetInfo ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Display_GetInfo(unsigned int * width, unsigned int * height, WGUI_DISPLAY_TYPE * type) MACRO_DEPRECATED;
#endif

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
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Display_Create ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Display_Create(unsigned int x, unsigned int y, unsigned int width, unsigned int height, WGUI_DISPLAY_TYPE type) MACRO_DEPRECATED;
#endif

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
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Display_Resize ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Display_Resize(unsigned int x, unsigned int y, unsigned int width, unsigned int height) MACRO_DEPRECATED;
#endif

/** <b> Deprecated </b>
@cond FULL_DOC
Destroy the display allocated
@endcond
@return error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Display_Destroy ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Display_Destroy(void) MACRO_DEPRECATED;
#endif

// *************************************************************************************
// *************************************************************************************
/** 
@}
@addtogroup WGUI_Canvas             
@{
	The canvas can be seen like a window (without menu and scroll bar). 
	A canvas is used to delimit the browser display. 
	Many canvases can be created on the display. 
*/
// *************************************************************************************
// *************************************************************************************

/** Canvas type */
typedef enum WGUI_CANVAS_OUTPUT
{
	WGUI_CANVAS_SCREEN, //!< Canvas output to screen
	WGUI_CANVAS_PRINTER //!< Canvas output to printer
} WGUI_CANVAS_OUTPUT;


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
Create new canvas on screen
@param output canvas output
@param x x canvas position on the userarea (area between led/header/footer) (not supported for printer)
@param y y canvas position on the userarea (area between led/header/footer) (not supported for printer)
@param width canvas width 
@param height canvas height 
@return canvas pointer if successfully creater else return null */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Canvas_Create ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_CANVAS_HANDLE WGUI_Canvas_Create(WGUI_CANVAS_OUTPUT output, int x, int y, unsigned int width, unsigned int height) MACRO_DEPRECATED;
#endif


/** @deprecated This function must not be used.
Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application. Destroy canvas
@param canvas canvas handle pointer */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Canvas_Destroy ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Canvas_Destroy(WGUI_CANVAS_HANDLE canvas) MACRO_DEPRECATED;
#endif


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 All browser display refresh are done with this function.
Wait keyboard, timer, mouse events and dispatch to browser 
@param canvas canvas handle pointer */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Canvas_DispatchEvent ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Canvas_DispatchEvent(WGUI_CANVAS_HANDLE canvas) MACRO_DEPRECATED;
#endif


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Set the focus to the selected canvas (only canvas with focus can get keyboard events)
@param canvas canvas handle pointer */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Canvas_SetFocus ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Canvas_SetFocus(WGUI_CANVAS_HANDLE canvas) MACRO_DEPRECATED;
#endif


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Move canvas on screen
@param canvas canvas handle pointer 
@param x x canvas position on the userarea (area between led/header/footer) (not supported for printer)
@param y y canvas position on the userarea (area between led/header/footer) (not supported for printer) */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Canvas_Move ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Canvas_Move(WGUI_CANVAS_HANDLE canvas, int x, int y) MACRO_DEPRECATED;
#endif


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Resize canvas on screen
@param canvas canvas handle pointer 
@param width canvas width 
@param height canvas height */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Canvas_Resize ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Canvas_Resize(WGUI_CANVAS_HANDLE canvas, int width, int height) MACRO_DEPRECATED;
#endif

/** Mouse cursor type */
typedef enum WGUI_CURSOR 
{
	WGUI_CURSOR_NONE,   // No cursor displayed
	WGUI_CURSOR_ARROW,  // Mouse arrow cursor displayed
	WGUI_CURSOR_DOT,    // Mouse dot cursor displayed
	WGUI_CURSOR_CROSS   // Mouse cross cursor displayed
} WGUI_CURSOR;

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Set the mouse cursor displayed on the canvas
@param canvas canvas handle pointer
@param cursor cursor type */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Canvas_SetCursor ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Canvas_SetCursor(WGUI_CANVAS_HANDLE canvas, WGUI_CURSOR cursor) MACRO_DEPRECATED;
#endif


/** Canvas info */
typedef struct WGUI_CANVAS_INFO
{
	/** the x position in pixels on root screen */
	int x;

	/** the y position in pixels on root screen */
	int y;

	/** the window width in pixels */
	int width;

	/** the window height in pixels */
	int height;
} WGUI_CANVAS_INFO;


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Get canvas information
@param canvas canvas handle pointer 
@param info pointer to canvas information */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Canvas_GetInfo ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Canvas_GetInfo (WGUI_CANVAS_HANDLE canvas, WGUI_CANVAS_INFO * info) MACRO_DEPRECATED;
#endif


// *************************************************************************************
// *************************************************************************************
/** 
@}
@addtogroup WGUI_Keymap            
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.

	The Keymap API is used to configure the browser keyboard.
	It is possible to change the browser key behaviour. 
	The browser uses specific keys, these keys are not equal to the terminal keyboard key; 
	you can bind any terminal key to these browser keys.
*/
// *************************************************************************************
// *************************************************************************************

// *************************************************************************************
/** Definition of virtual Key Code that can be used by the browser to manage some events */
// *************************************************************************************
/**
@defgroup WGUI_KeymapBrowser Browser key
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
*/

#define WGUI_KEY_NONE            ((WGUI_WCHAR)0x0000) //!< No key 
#define WGUI_KEY_TAB             ((WGUI_WCHAR)0x0009) //!< Tabulation
#define WGUI_KEY_BACKSPACE       ((WGUI_WCHAR)0x0008) //!< Delete previous charactere before cursor
#define WGUI_KEY_CR              ((WGUI_WCHAR)0x000D) //!< Carriage return
#define WGUI_KEY_ESC             ((WGUI_WCHAR)0x001B) //!< Escape

/* Following key are mapped to private use portion of Unicode-16 */
#define WGUI_KEY_PAGE_UP         ((WGUI_WCHAR)0xF808) //!< Scroll page displayed to the previous page
#define WGUI_KEY_PAGE_DOWN       ((WGUI_WCHAR)0xF809) //!< Scroll page displayed to the next page
#define WGUI_KEY_LINE_UP         ((WGUI_WCHAR)0xF802) //!< Scroll page displayed to the previous line
#define WGUI_KEY_LINE_DOWN       ((WGUI_WCHAR)0xF803) //!< Scroll page displayed to the next line
#define WGUI_KEY_ALT             ((WGUI_WCHAR)0xF82F) //!< alt modifier
#define WGUI_KEY_CTRL            ((WGUI_WCHAR)0xF82D) //!< ctrl modifier
#define WGUI_KEY_SHIFT           ((WGUI_WCHAR)0xF82B) //!< shift modifier
#define WGUI_KEY_CAPS            ((WGUI_WCHAR)0xF829) //!< caps lock
#define WGUI_KEY_FOCUS_PREVIOUS  ((WGUI_WCHAR)0xF81B) //!< Set the focus to the previous field
#define WGUI_KEY_FOCUS_NEXT      ((WGUI_WCHAR)0xF81C) //!< Set the focus to the next field
#define WGUI_KEY_FORWARD_HISTORY ((WGUI_WCHAR)0xF81D) //!< Forward page in history
#define WGUI_KEY_BACK_HISTORY    ((WGUI_WCHAR)0xF81E) //!< Back page in history
#define WGUI_KEY_RELOAD_PAGE     ((WGUI_WCHAR)0xF81F) //!< Reload html page displayed
#define WGUI_KEY_HOME_PAGE       ((WGUI_WCHAR)0xF820) //!< Load home page
#define WGUI_KEY_STOP_BROWSING   ((WGUI_WCHAR)0xF821) //!< Stop the current browsing
#define WGUI_KEY_INSERT          ((WGUI_WCHAR)0xF804) //!< Toogle replace insertion mode
#define WGUI_KEY_PREVIOUS_ITEM   ((WGUI_WCHAR)0xF83B) //!< Move cursor to the left or select previous item in the field 
#define WGUI_KEY_NEXT_ITEM       ((WGUI_WCHAR)0xF83C) //!< Move cursor to the right or select next item in the field 
#define WGUI_KEY_DELETE          ((WGUI_WCHAR)0xF805) //!< Delete next charactere after cursor
#define WGUI_KEY_LEFT            ((WGUI_WCHAR)0xF800) //!< Scroll page displayed to the left
#define WGUI_KEY_RIGHT           ((WGUI_WCHAR)0xF801) //!< Scroll page displayed to the right
#define WGUI_KEY_HOME            ((WGUI_WCHAR)0xF806) //!< Start of string edition
#define WGUI_KEY_END             ((WGUI_WCHAR)0xF807) //!< End of string edition <br><br>

#define WGUI_KEY_IGNORE			 ((WGUI_WCHAR)0xF8FF) //!< The binded key will be ignored if pressed

/**
@}
*/

// *************************************************************************************
/** Definition of physical key of the telium terminal */
// *************************************************************************************
/**
@defgroup WGUI_KeymapTelium Terminal key
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
*/
#define WGUI_TELIUM_KEY_0             ((WGUI_WCHAR)0x0030) //!< Telium numeric 0 key
#define WGUI_TELIUM_KEY_1             ((WGUI_WCHAR)0x0031) //!< Telium numeric 1 key
#define WGUI_TELIUM_KEY_2             ((WGUI_WCHAR)0x0032) //!< Telium numeric 2 key
#define WGUI_TELIUM_KEY_3             ((WGUI_WCHAR)0x0033) //!< Telium numeric 3 key
#define WGUI_TELIUM_KEY_4             ((WGUI_WCHAR)0x0034) //!< Telium numeric 4 key
#define WGUI_TELIUM_KEY_5             ((WGUI_WCHAR)0x0035) //!< Telium numeric 5 key
#define WGUI_TELIUM_KEY_6             ((WGUI_WCHAR)0x0036) //!< Telium numeric 6 key
#define WGUI_TELIUM_KEY_7             ((WGUI_WCHAR)0x0037) //!< Telium numeric 7 key
#define WGUI_TELIUM_KEY_8             ((WGUI_WCHAR)0x0038) //!< Telium numeric 8 key
#define WGUI_TELIUM_KEY_9             ((WGUI_WCHAR)0x0039) //!< Telium numeric 9 key
#define WGUI_TELIUM_KEY_DOT           ((WGUI_WCHAR)0x002E) //!< Telium numeric dot key

#define WGUI_TELIUM_KEY_VALIDATION    ((WGUI_WCHAR)0xF850) //!< Telium green key
#define WGUI_TELIUM_KEY_CANCEL        ((WGUI_WCHAR)0xF851) //!< Telium red key
#define WGUI_TELIUM_KEY_CORRECTION    ((WGUI_WCHAR)0xF852) //!< Telium yellow key
#define WGUI_TELIUM_KEY_PAPER         ((WGUI_WCHAR)0xF853) //!< Telium paper feed key
#define WGUI_TELIUM_KEY_F             ((WGUI_WCHAR)0xF854) //!< Telium function key
#define WGUI_TELIUM_KEY_F1            ((WGUI_WCHAR)0xF855) //!< Telium function 1 key
#define WGUI_TELIUM_KEY_F2            ((WGUI_WCHAR)0xF856) //!< Telium function 2 key
#define WGUI_TELIUM_KEY_F3            ((WGUI_WCHAR)0xF857) //!< Telium function 3 key
#define WGUI_TELIUM_KEY_F4            ((WGUI_WCHAR)0xF858) //!< Telium function 4 key
#define WGUI_TELIUM_KEY_UP            ((WGUI_WCHAR)0xF859) //!< Telium up arrow key
#define WGUI_TELIUM_KEY_DOWN          ((WGUI_WCHAR)0xF85A) //!< Telium down arrow key
#define WGUI_TELIUM_KEY_OK            ((WGUI_WCHAR)0xF86B) //!< Telium ok key
#define WGUI_TELIUM_KEY_CLEAR         ((WGUI_WCHAR)0xF86C) //!< Telium clear key
/**
@}
*/

// *************************************************************************************
// *************************************************************************************

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Bind telium key to a list of keys list, this function is used to configure virtual map keyboard,
to unbind key set count to 0 and keys to null pointer.
@param browser The HTML Browser handle 
@param teliumKey keyboard telium key
@param keys wgui keys list 
@param count number of keys in list
@return Keymap error code

The default configuration is the following : 

	@li \ref WGUI_TELIUM_KEY_0           => '0',' ','+','"','_','\''
	@li \ref WGUI_TELIUM_KEY_1           => '1', 'q', 'z', 'Q', 'Z'
	@li \ref WGUI_TELIUM_KEY_2           => '2', 'a', 'b', 'c', 'A', 'B', 'C'
	@li \ref WGUI_TELIUM_KEY_3           => '3', 'd', 'e', 'f', 'D', 'E', 'F'
	@li \ref WGUI_TELIUM_KEY_4           => '4', 'g', 'h', 'i', 'G', 'H', 'I'
	@li \ref WGUI_TELIUM_KEY_5           => '5', 'j', 'k', 'l', 'J', 'K', 'L'
	@li \ref WGUI_TELIUM_KEY_6           => '6', 'm', 'n', 'o', 'M', 'N', 'O'
	@li \ref WGUI_TELIUM_KEY_7           => '7', 'p', 'r', 's', 'P', 'R', 'S'
	@li \ref WGUI_TELIUM_KEY_8           => '8', 't', 'u', 'v', 'T', 'U', 'V'
	@li \ref WGUI_TELIUM_KEY_9           => '9', 'w', 'x', 'y', 'W', 'X', 'Y'
	@li \ref WGUI_TELIUM_KEY_DOT         => '.',';','-',':','?'

*/
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Keymap_BindManyKey ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Keymap_BindManyKey(WGUI_BROWSER_HANDLE browser, WGUI_WCHAR teliumKey, const WGUI_WCHAR * keys, unsigned long count) MACRO_DEPRECATED;
#endif


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Bind telium key to a wgui key, to unbind key set key to 0
@param browser The HTML Browser handle 
@param teliumKey keyboard telium key
@param key wgui key 
@return Keymap error code 

The default configuration is the following : 

	@li \ref WGUI_TELIUM_KEY_VALIDATION  => \ref WGUI_KEY_CR
	@li \ref WGUI_TELIUM_KEY_CANCEL      => \ref WGUI_KEY_ESC
	@li \ref WGUI_TELIUM_KEY_CORRECTION  => \ref WGUI_KEY_BACKSPACE
	@li \ref WGUI_TELIUM_KEY_F1          => \ref WGUI_KEY_PREVIOUS_ITEM 
	@li \ref WGUI_TELIUM_KEY_F4          => \ref WGUI_KEY_NEXT_ITEM
	@li \ref WGUI_TELIUM_KEY_UP          => \ref WGUI_KEY_FOCUS_PREVIOUS
	@li \ref WGUI_TELIUM_KEY_DOWN        => \ref WGUI_KEY_FOCUS_NEXT

	All other keys are affected to \ref WGUI_KEY_IGNORE

<br><b>Example:</b><br>
	bind the next field navigation with F1 :<br>
	WGUI_Keymap_BindOneKey(WGUI_KEY_FOCUS_NEXT, WGUI_TELIUM_KEY_F1);

<br><b>Default layout for ICT250:</b><br>
	@image html Key_250.png
<br><b>Default layout for EFT930:</b><br>
	@image html Key_930.png
<br><b>Default layout for ISC350:</b><br>
	@image html Key_350.png

	<i>Nota : for the 350 (screen wider than 320px) samples add the following binding : </i>
	- WGUI_Keymap_BindOneKey(browser, WGUI_TELIUM_KEY_F, WGUI_KEY_FOCUS_PREVIOUS);
	- WGUI_Keymap_BindOneKey(browser, WGUI_TELIUM_KEY_DOT, WGUI_KEY_FOCUS_NEXT);
	<i><br>This map '-' key with "Set the focus to the next field" action key code 63516 (0xF81C)
	<br>And '+' key with "Set the focus to the previous field" action  key code 63515 (0xF81B)</i>


*/
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Keymap_BindOneKey ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Keymap_BindOneKey(WGUI_BROWSER_HANDLE browser, WGUI_WCHAR teliumKey, WGUI_WCHAR key) MACRO_DEPRECATED;
#endif


// *************************************************************************************
// *************************************************************************************
/**
@}
@defgroup WGUI_Browser       Browser
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
	The Browser API is used to create browser, load html page and configure the browser.
*/
// *************************************************************************************
// *************************************************************************************
/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Browser constructor
@param canvas handle of the canvas previously created with CreateCanvas
@return browser instance created or null if creation has failed */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_Create ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_BROWSER_HANDLE WGUI_Browser_Create(WGUI_CANVAS_HANDLE canvas) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Browser destructor
@param browser The HTML Browser handle 
@return browser error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_Destroy ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_Destroy (WGUI_BROWSER_HANDLE browser) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * This function is functionally identical to entering a string in the URL bar of an HTML Browser window.
@param browser  The handle of the HTML Browser
@param url  The URL to load
@param refresh : 1 to refresh screen, 0 otherwise
@return browser error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_LoadUrl ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_LoadUrl(WGUI_BROWSER_HANDLE browser, const char* url, int refresh ) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * This function refreshs the browser's screen. It displays its main document.
@param browser  The handle of the HTML Browser
@return browser error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_Refresh ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_Refresh(WGUI_BROWSER_HANDLE browser ) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * This function flush browser's content.
@param browser  The handle of the HTML Browser
@return browser error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_Flush ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_Flush(WGUI_BROWSER_HANDLE browser ) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Set an option of the browser
@param browser The HTML Browser handle
@param option type of option to set 
@param value value of the option
@return browser error code*/
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_SetOption ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_SetOption(WGUI_BROWSER_HANDLE browser,enum WGUI_BROWSER_OPTION option, long value) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Receive next unread html event data, the event contains the url posted and all variables contained in url. The event data
is destroyed with the next call of WGUI_Browser_GetHtmlEvent.
@param browser  The handle of the HTML Browser
@param evt event data pointer or null pointer if no event 
@return browser error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_GetHtmlEvent ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_GetHtmlEvent(WGUI_BROWSER_HANDLE browser, WGUI_HTML_EVENT_HANDLE * evt) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Receive next unread html event data, the event contains the url posted and all variables contained in url. The event data
must be released by WGUI_Browser_ReleaseHtmlEvent or WGUI_JSON_SendResponse.
@param browser  The handle of the HTML Browser
@param evt event data pointer or null pointer if no event 
@return browser error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_PeekHtmlEvent ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_PeekHtmlEvent(WGUI_BROWSER_HANDLE browser, WGUI_HTML_EVENT_HANDLE * evt) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Release an event previously get by WGUI_Browser_PeekHtmlEvent
@param browser  The handle of the HTML Browser
@param evt event data to be released
@return browser error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_ReleaseHtmlEvent ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_ReleaseHtmlEvent(WGUI_BROWSER_HANDLE browser, WGUI_HTML_EVENT_HANDLE evt) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * This function load page from ascii data pointer
@param browser  The handle of the HTML Browser
@param html_src Pointer to a null-terminated buffer of html source.
@param refresh : 1 to refresh screen, 0 otherwise
@return document error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_WriteHtmlAscii ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_WriteHtmlAscii (WGUI_BROWSER_HANDLE browser, const char* html_src, int refresh ) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * This function load page from unicode data pointer
@param browser  The handle of the HTML Browser
@param html_src Pointer to a null-terminated buffer of html source.
@param refresh : 1 to refresh screen, 0 otherwise
@return document error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_WriteHtmlUnicode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_WriteHtmlUnicode (WGUI_BROWSER_HANDLE browser, const WGUI_WCHAR * html_src, int refresh ) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * This function configure the default error message, this message is displayed when an error occured while
trying to load page 
@param browser  The handle of the HTML Browser
@param errorMessage Pointer to a null-terminated buffer of html error message (ascii format).
@return document error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_SetErrorAscii ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_SetErrorAscii (WGUI_BROWSER_HANDLE browser, const char* errorMessage) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * This function configure the default error message, this message is displayed when an error occured while
trying to load page 
@param browser  The handle of the HTML Browser
@param errorMessage Pointer to a null-terminated buffer of html error message (unicode format).
@return document error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Browser_SetErrorUnicode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Browser_SetErrorUnicode (WGUI_BROWSER_HANDLE browser, const WGUI_WCHAR * errorMessage) MACRO_DEPRECATED;
#endif


// *************************************************************************************
// *************************************************************************************
/** 
@}
@addtogroup WGUI_PrintJob                 
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
	The PrintJob API is used to print html page to the printer.
*/
// *************************************************************************************
// *************************************************************************************

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Start the page print in ascii, if the printer is buzy the job is appended to printer queue
@param html_src Pointer to a null-terminated buffer of html source.
@param reverse WGUI_TRUE indicates that black is inversed with white, WGUI_FALSE no color inversion
@return print job handle */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_PrintJob_PrintHtmlAscii ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_PRINT_JOB_HANDLE WGUI_PrintJob_PrintHtmlAscii(const char* html_src, WGUI_BOOL reverse) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Start the page print in unicode, if printer is buzy the job is appended to printer queue
@param html_src Pointer to a null-terminated buffer of html source.
@param reverse WGUI_TRUE indicates that black is inversed with white, WGUI_FALSE no color inversion
@return print job handle */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_PrintJob_PrintHtmlUnicode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_PRINT_JOB_HANDLE WGUI_PrintJob_PrintHtmlUnicode(const WGUI_WCHAR* html_src, WGUI_BOOL reverse) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Start the page print with an url, if printer is buzy the job is appended to printer queue
@param url  The URL to print
@param reverse WGUI_TRUE indicates that black is inversed with white, WGUI_FALSE no color inversion
@return print job handle */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_PrintJob_PrintUrl ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_PRINT_JOB_HANDLE WGUI_PrintJob_PrintUrl(const char* url, WGUI_BOOL reverse) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Cancel print job and remove from printer queue
@param job print job handle */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_PrintJob_Cancel ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_PrintJob_Cancel(WGUI_PRINT_JOB_HANDLE job) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Restart print job from the beginning. Useful to restart print after a paper out
@param job print job handle */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_PrintJob_Restart ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_PrintJob_Restart(WGUI_PRINT_JOB_HANDLE job) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Indicates the job status
@param job print job handle 
@return print job status (WGUI_OK job terminated) */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_PrintJob_GetStatus ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_PrintJob_GetStatus(WGUI_PRINT_JOB_HANDLE job) MACRO_DEPRECATED;
#endif


// *************************************************************************************
// *************************************************************************************
/** 
@}
@addtogroup WGUI_HtmlEvent                 
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
	The HtmlElement API is used to extract data embedded in the url returned by @ref WGUI_Browser_GetHtmlEvent.
*/
// *************************************************************************************
// *************************************************************************************

/** Infinit duration */
#define WGUI_INFINITE 0xFFFFFFFF

/** HTML Event mask */
typedef enum WGUI_HTML_EVENT_TYPE
{
	WGUI_HTML_EVENT_NONE,
	WGUI_HTML_EVENT_RESET, //!< Detect html reset event
	WGUI_HTML_EVENT_POST,  //!< Detect html applicative GET event (protocol app://)
	WGUI_HTML_EVENT_GET,   //!< Detect html applicative POST event (protocol app://)	
	WGUI_HTML_EVENT_XHR_GET,    //!< Detect html applicative GET event (protocol app://) sent by javascript through XMLHttpRequest object (not yet implemented)
	WGUI_HTML_EVENT_XHR_POST	//!< Detect html applicative POST event (protocol app://) sent by javascript through XMLHttpRequest object (not yet implemented)
} WGUI_HTML_EVENT_TYPE;

/**
 * @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Get event type from html event data
@param evt event handle
@param type event type pointer 
@return Html event error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_HtmlEvent_GetType ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_HtmlEvent_GetType(WGUI_HTML_EVENT_HANDLE evt, WGUI_HTML_EVENT_TYPE * type) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Get URL from html event data
@param evt event handle
@param url url data pointer
@param count number of characters to get from 
@return Html event error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_HtmlEvent_GetUrl ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_HtmlEvent_GetUrl(WGUI_HTML_EVENT_HANDLE evt, WGUI_WCHAR * url, unsigned long count) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Get variable stored in the event, according to its variable name, returns it in ascii
@param evt event received handle 
@param name ascii name string
@param value ascii value buffer
@param nSize size of value buffer 
@return Html event error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_HtmlEvent_GetVariableAscii ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_HtmlEvent_GetVariableAscii(WGUI_HTML_EVENT_HANDLE evt, const char* name, char* value, unsigned int nSize) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Get variable stored in the event, according to its variable name, returns it in unicode
@param evt event received handle 
@param name unicode name string
@param value unicode value buffer
@param count number of characters to get from 
@return Html event error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_HtmlEvent_GetVariableUnicode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_HtmlEvent_GetVariableUnicode(WGUI_HTML_EVENT_HANDLE evt, const WGUI_WCHAR* name, WGUI_WCHAR* value, unsigned int count) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Get the variable length in ascii
@param evt event received handle 
@param name ascii name string
@return number of characters of variable value, 0 if variable is not found */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_HtmlEvent_GetVariableAsciiLen ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT unsigned int WGUI_HtmlEvent_GetVariableAsciiLen(WGUI_HTML_EVENT_HANDLE evt, const char* name) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Get the variable length in unicode
@param evt event received handle 
@param name unicode name string
@return number of characters of variable value, 0 if variable is not found */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_HtmlEvent_GetVariableUnicodeLen ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT unsigned int WGUI_HtmlEvent_GetVariableUnicodeLen(WGUI_HTML_EVENT_HANDLE evt, const WGUI_WCHAR* name) MACRO_DEPRECATED;
#endif


// *************************************************************************************
// *************************************************************************************
/**
@}
@addtogroup WGUI_JSON             
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
	The JSON API is used to communicate between the browser and application via the javascript language. 
	JSON (JavaScript Object Notation) is a lightweight data-interchange format http://www.json.org/.
	JSON is built on two structures:

		- A collection of name/value pairs. In various languages, this is realized as an object, record, struct, dictionary, hash table, keyed list, or associative array.
		- An ordered list of values. In most languages, this is realized as an array, vector, list, or sequence.

	In JSON, they take on these forms:
		- An <b>object</b> is an unordered set of name/value pairs. An object begins with { (left brace) and ends with } (right brace). Each name is followed by : (colon) and the name/value pairs are separated by , (comma).
		- An <b>array</b> is an ordered collection of values. An array begins with [ (left bracket) and ends with ] (right bracket). Values are separated by , (comma).
		- A <b>value</b> can be a string in double quotes, or a number, or true or false or null, or an object or an array. These structures can be nested.
		- A <b>string</b> is a collection of zero or more Unicode characters, wrapped in double quotes, using backslash escapes. A character is represented as a single character string. A string is very much like a C or Java string.
		- A <b>number</b> is very much like a C or Java number, except that the octal and hexadecimal formats are not used.
*/
// *************************************************************************************
// *************************************************************************************

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Create an empty JSON object and return its handle
@return JSON object handle or NULL if failed */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_CreateObject ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_JSON_NODE WGUI_JSON_CreateObject(void) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Destroy JSON object and associated memory
@param object : JSON object handle to destroy
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_DestroyObject ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_DestroyObject(WGUI_JSON_NODE object) MACRO_DEPRECATED;
#endif


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an array item in an object
@param parent : parent object in which add a new array
@param name : name of the child object to add
@return the WGUI_JSON_NODE of the array in which value can be put*/
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddItemArray ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_JSON_NODE WGUI_JSON_AddItemArray(WGUI_JSON_NODE parent, const char* name) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an object item in an object
@param parent : parent object in which add a new object
@param name : name of the child object to add
@return the WGUI_JSON_NODE of the array in which value can be put*/
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddItemObject ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_JSON_NODE WGUI_JSON_AddItemObject(WGUI_JSON_NODE parent, const char* name) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an existing Node to an object
	The node is added by reference if node is modified after being inserted
	the modifications will be reflected in the parent
@param parent : parent object in which add a the node
@param name : name of the child object to add
@param node : existing node to add
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddItemNode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddItemNode(WGUI_JSON_NODE parent, const char* name, WGUI_JSON_NODE node) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an Int item in an object
@param parent : parent object in which add a new int
@param name : name of the child object to add
@param value : int value to add
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddItemInt ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddItemInt(WGUI_JSON_NODE parent, const char* name, int value) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add a boolean item in an object
@param parent : parent object in which add a new boolean
@param name : name of the child object to add
@param value : boolean value to add (0 is false other is true)
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddItemBoolean ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddItemBoolean(WGUI_JSON_NODE parent, const char* name, int value) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add a double item in an object
@param parent : parent object in which add a new double
@param name : name of the child object to add
@param value : double value to add
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddItemDouble ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddItemDouble(WGUI_JSON_NODE parent, const char* name, double value) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an ascii string item in an object
@param parent : parent object in which add a new ascii string
@param name : name of the child object to add
@param value : ascii string value to add
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddItemStringAscii ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddItemStringAscii(WGUI_JSON_NODE parent, const char* name, char * value) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add a unicode string item in an object
@param parent : parent object in which add a new unicode string
@param name : name of the child object to add
@param value : unicode string value to add
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddItemStringUnicode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddItemStringUnicode(WGUI_JSON_NODE parent, const char* name, WGUI_WCHAR * value) MACRO_DEPRECATED;
#endif


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an array item in an array
@param parent : parent object in which add a new array
@return the WGUI_JSON_NODE of the array in which value can be put*/
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddArray ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_JSON_NODE WGUI_JSON_AddArray(WGUI_JSON_NODE parent) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an object item in an array
@param parent : parent object in which add a new object
@return the WGUI_JSON_NODE of the object in which value can be put*/
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddObject ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_JSON_NODE WGUI_JSON_AddObject(WGUI_JSON_NODE parent) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an existing Node to an array
	The node is added by reference if node is modified after being inserted
	the modifications will be reflected in the parent
@param parent : parent object in which add a the node
@param node : existing node to add
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddNode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddNode(WGUI_JSON_NODE parent, WGUI_JSON_NODE node) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an Int in an array
@param parent : parent array in which add a new int
@param value : int value to add
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddInt ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddInt(WGUI_JSON_NODE parent, int value) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add a boolean in an array
@param parent : parent array in which add a new boolean
@param value : boolean value to add (0 is false other is true)
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddBoolean ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddBoolean(WGUI_JSON_NODE parent, int value) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add a double in an array
@param parent : parent array in which add a new double
@param value : double value to add
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddDouble ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddDouble(WGUI_JSON_NODE parent, double value) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an ascii string in an array
@param parent : parent array in which add a new ascii string
@param value : ascii string value to add
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddStringAscii ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddStringAscii(WGUI_JSON_NODE parent, char * value) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add a unicode string in an array
@param parent : parent array in which add a new unicode string
@param value : unicode string value to add
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_AddStringUnicode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_AddStringUnicode(WGUI_JSON_NODE parent, WGUI_WCHAR * value) MACRO_DEPRECATED;
#endif


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Send JSON response to the caller and destroy the event
@param browser  The handle of the HTML Browser
@param response : JSON response handle previously built to be send
@param evt : event to respond to
@return Error code from WGUI_ERROR */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_SendResponse ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_JSON_SendResponse(WGUI_BROWSER_HANDLE browser, WGUI_JSON_NODE response, WGUI_HTML_EVENT_HANDLE evt) MACRO_DEPRECATED;
#endif


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Create a json object from an ascii string
@param value : ascii string to parse
@return WGUI_JSON_NODE the new created object*/
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_FromStringAscii ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_JSON_NODE WGUI_JSON_FromStringAscii(char * value) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Create a json object from an unicode string
@param value : unicode string to parse
@return WGUI_JSON_NODE the new created object*/
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_FromStringUnicode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_JSON_NODE WGUI_JSON_FromStringUnicode(WGUI_WCHAR * value) MACRO_DEPRECATED;
#endif


/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Dump the json object into an unicode string
@param object json object
@return string converted */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_ToStringUnicode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT const WGUI_WCHAR * WGUI_JSON_ToStringUnicode(WGUI_JSON_NODE object) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Dump the json object into an ascii string
@param object json object
@return string converted */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_JSON_ToStringAscii ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT const char * WGUI_JSON_ToStringAscii(WGUI_JSON_NODE object) MACRO_DEPRECATED;
#endif


// *************************************************************************************
// *************************************************************************************
/**
@}
@addtogroup WGUI_Resource                 
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
	The Resource API is used to load in memory a zipped file which contains pages and images, 
	to access to the pages and images you must used the "wgui://" protocol.
*/
// *************************************************************************************
// *************************************************************************************

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Load resource filename. The resource filename is a zip file.
For use a resource in an html page you must prefix the url by "wgui://" followed
with the correct path.
@param filename resource filename (zip file) 
@return true if load is a success else return false */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Resource_Load ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Resource_Load(const char* filename) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Unload resource filename
@param filename resource filename (zip file) 
@return true if load is a success else return false */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Resource_Unload ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Resource_Unload(const char* filename) MACRO_DEPRECATED;
#endif


// *************************************************************************************
// *************************************************************************************
/** 
@}
@addtogroup WGUI_Tool                 
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
	The Tools API is composed of functions useful to manipulate unicode string. 
*/
// *************************************************************************************
// *************************************************************************************

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Convert unicode string into ASCII string
@param unicode input string to convert
@param ascii output string converted
@param count number of characters to get from */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Tool_UnicodeToAscii ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Tool_UnicodeToAscii(const WGUI_WCHAR * unicode, char* ascii, unsigned int count) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Convert ASCII string into unicode string
@param ascii input string to convert
@param unicode output string converted
@param count number of characters to get from */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Tool_AsciiToUnicode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Tool_AsciiToUnicode(const char* ascii, WGUI_WCHAR * unicode, unsigned int count) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Sleep in ms
@param duration in milliseconds */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Tool_Sleep ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT void WGUI_Tool_Sleep(unsigned long duration) MACRO_DEPRECATED;
#endif
                     
/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Appends src to string dst of size siz (unlike strncat, siz is the
full size of dst, not space left).  At most siz-1 characters
will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
@param dst destination string
@param src source string
@param count size characters in destination string
@return strlen(src) + MIN(siz, strlen(initial dst)). If retval >= siz, truncation occurred. */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Tool_Strcat ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT unsigned int WGUI_Tool_Strcat(WGUI_WCHAR *dst, const WGUI_WCHAR *src, unsigned int count) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Calculates the length of the string s, not including the terminating '\\0' character.
@param str source string
@return the number of characters in s. */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Tool_Strlen ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT unsigned int WGUI_Tool_Strlen   (const WGUI_WCHAR* str) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Copy src to string dst of size siz.  At most siz-1 characters will be copied. Always NUL terminates (unless siz == 0).
@param dest destination string
@param src source string
@param count size characters in destination string
@return strlen(src); if retval >= siz, truncation occurred. */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Tool_Strcpy ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT unsigned int WGUI_Tool_Strcpy   (WGUI_WCHAR* dest, const WGUI_WCHAR* src, unsigned int count) MACRO_DEPRECATED;
#endif

/**  @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * locates the first occurrence of the null-terminated string s2 in the null-terminated string s1.
@param s1 srce string
@param s2 substring to find into s1
@return a pointer to the beginning of the substring, or NULL if the substring is not found.*/
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Tool_Strstr ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_WCHAR*  WGUI_Tool_Strstr   (const WGUI_WCHAR* s1, const WGUI_WCHAR* s2) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Compares the two strings s1 and s2.
It returns an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2. 
@param s1 string 1
@param s2 string 2
@return an integer less than, equal to, or greater than zero if s1 (or the first n bytes thereof) is found, respectively, to be less than, to match, or be greater than s2. */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Tool_Strcmp ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT int  WGUI_Tool_Strcmp   (const WGUI_WCHAR* s1, const WGUI_WCHAR* s2) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Compares the two strings s1 and s2.
It returns an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2, except it only compares the first (at most) n characters of s1 and s2. 
@param s1 string 1
@param s2 string 2
@param count number of characters 
@return an integer less than, equal to, or greater than zero if s1 (or the first n bytes thereof) is found, respectively, to be less than, to match, or be greater than s2. */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Tool_Strncmp ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT int  WGUI_Tool_Strncmp  (const WGUI_WCHAR* s1, const WGUI_WCHAR* s2, unsigned int count) MACRO_DEPRECATED;
#endif


// *************************************************************************************
// *************************************************************************************
/**
@}
@addtogroup WGUI_Template           
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
	function managing tag / template replacement : 
	call an url prefixed with an '@' use a stream replacement mechanism : each word
	found between tag \<?tpl and ?> in the source are replaced by their corresponding
	   text if found. If a word is not defined, it is replaced by empty string "" 
*/
// *************************************************************************************
// *************************************************************************************

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an Ascii replacement tag in the template replacement list
@param browser The HTML Browser handle
@param tagName name of the tag to match for (in ascii)
@param tagReplacement replacement text  of the tag (in ascii)
@param overWrite : true : replace tag if already exist, 0 return an error in this case
@return WGUI_OK, or WGUI_TEMPLATE_ error */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Template_AddTagAscii ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Template_AddTagAscii(WGUI_BROWSER_HANDLE browser, const char*tagName, const char*tagReplacement, WGUI_BOOL overWrite) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Add an Unicode replacement tag in the template replacement list
@param browser The HTML Browser handle
@param tagName name of the tag to match for (in Unicode)
@param tagReplacement replacement text  of the tag (in Unicode)
@param overWrite : true : replace tag if already exist, 0 return an error in this case
@return WGUI_OK, or WGUI_TEMPLATE_ error */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Template_AddTagUnicode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Template_AddTagUnicode(WGUI_BROWSER_HANDLE browser, const WGUI_WCHAR *tagName, const WGUI_WCHAR *tagReplacement, WGUI_BOOL overWrite) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Remove an Ascii tag from the template replacement list
@param browser The HTML Browser handle
@param tagName name of the tag to remove (ascii)
@return WGUI_OK, or WGUI_TEMPLATE_ error */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Template_RemoveTagAscii ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Template_RemoveTagAscii(WGUI_BROWSER_HANDLE browser, const char*tagName) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Remove an Unicode tag from the template replacement list
@param browser The HTML Browser handle
@param tagName name of the tag to remove (ascii)
@return WGUI_OK, or WGUI_TEMPLATE_ error */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Template_RemoveTagUnicode ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Template_RemoveTagUnicode(WGUI_BROWSER_HANDLE browser, const WGUI_WCHAR *tagName) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Remove all defined tags from the template replacement list
@param browser The HTML Browser handle
@return WGUI_OK, or WGUI_TEMPLATE_ error */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Template_FlushTags ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Template_FlushTags(WGUI_BROWSER_HANDLE browser) MACRO_DEPRECATED;
#endif


// *************************************************************************************
// *************************************************************************************
/**
@}
@addtogroup WGUI_Plugin           
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
	This API is used to extend the browser with additionnal plugins, (for example signature capture plugin, video plugin).

	The plugin DLL must be registered with @ref WGUI_Plugin_Register function, and unregistered with @ref WGUI_Plugin_Unregister function.

	To add a plugin in the html page you must use the <b>object</b> tag :

	&lt;object <b>type</b>='music' <b>width</b>='100' <b>height</b>='30' data='hello.html' border=1 &gt; <br>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&lt;param name='param1' value='value1' type='type1'&gt;&lt;/param&gt; <br>
		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&lt;param name='param2' value='value2' type='type1'&gt;&lt;/param&gt;<br>
	&lt;/object&gt;<br>

		- type : define the mime type (this type must be equal to the value returned by the function Plugin_GetType.
		- width : define the plugin width in pixels
		- height : define the plugin height in pixels
		- param : define a parameter
			@cond FULL_DOC
			the parameter is passed to plugin via an event @ref WGUI_EVENT_SET_PARAM, 
			the parameter name, value and the type are stored in the WGUI_PLUGIN_PARAM of the @ref WGUI_PLUGIN_EVENT structure .
			@endcond 
*/
// *************************************************************************************
// *************************************************************************************

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Register plugin tag plugin
@param browser browser handle
@param dllName name of the dll containing the plugin plugin
@return plugin error */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Plugin_Register ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Plugin_Register(WGUI_BROWSER_HANDLE browser, const char * dllName) MACRO_DEPRECATED;
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Unregister plugin tag plugin
@param browser browser handle
@param dllName name of the dll containing the object plugin
@return plugin error */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_Plugin_Unregister ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_Plugin_Unregister(WGUI_BROWSER_HANDLE browser, const char * dllName) MACRO_DEPRECATED;
#endif


// *************************************************************************************
// *************************************************************************************
/**
@}
@addtogroup WGUI_Proxy 
@{
@deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
	The WGUI Proxy API define a way of defining its own proxy (ie urlbase)
	External transport proxy libraries can be dynamically registered to the WGUI
	Engine. It allows to add new protocols implemented in separated libraries (DLL)
	without recompiling the WGUI Engine and the browsers.

	Existing proxy are : 
		- name : "HTTP" proxyname "HTTP" : register http protocol only in mockup mode
		- name : "HTTP" proxyname "HTTPS" : register https protocol only in mockup mode
*/
// *************************************************************************************
// *************************************************************************************

#ifdef _WIN32
/** Register new proxy 
@cond
@param browser The HTML Browser handle
@param Init : Init function of the proxy
@param proxyname : name of the proxy to register
@return execution error code */
EXPORT WGUI_ERROR WGUI_ProxyRegister(WGUI_BROWSER_HANDLE browser, void *(*Init)(const char* proxyname),int (*Configure)(void * conf), const char* proxyname);
/** 
@endcond */
#else
/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Register new proxy
@param browser The HTML Browser handle
@param name : name of the dll containing the proxy
@param proxyname : name of the proxy to register
@return execution error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_ProxyRegister ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_ProxyRegister(WGUI_BROWSER_HANDLE browser, const char* name, const char* proxyname) MACRO_DEPRECATED;
#endif
#endif

/** @deprecated This function must not be used. Use GOAL instead of cGUI 
 To continue to use this function, define _DEPRECATED_WGUI_SDK090800_ in your application.
 * Unregister proxy
@param browser The HTML Browser handle
@param proxyname urlbase to unregister
@return execution error code */
#ifndef _DEPRECATED_WGUI_SDK090800_
#define WGUI_ProxyUnregister ERROR_Deprecation_For_ModuleWGUI_Migrate_Your_Application_To_GOAL;
/* This error is generated to warn you about the deprecation for WGUI. You can remove this error by adding _DEPRECATED_WGUI_SDK090800_
 * Please do the necessary to clean your code.*/
#else
EXPORT WGUI_ERROR WGUI_ProxyUnregister(WGUI_BROWSER_HANDLE browser, const char* proxyname) MACRO_DEPRECATED;
#endif


/**
@}
@}
*/


#ifdef __cplusplus
}
#endif

#endif // WGUI_Deprecated_h_INCLUDED
