// $Id: GL_GraphicLib.h,v 1.1.2.84 2013/01/18 16:06:05 rbertholet Exp $  
// Management's main library of graphic objects.
#ifndef GL_GraphicLib_h_INCLUDED
#define GL_GraphicLib_h_INCLUDED

#ifndef GL_EXCEPTION
	#define GL_EXCEPTION
#endif

#ifdef __cplusplus
extern "C"
{
#endif



#include "GL_Types.h"
#include "GL_CommonTypes.h"
#include <stdarg.h>

/**
@addtogroup GL_Resource Resource management
@{ 
@addtogroup GL_ResourceDoc Resource management
@{

	This section presents the functions allows access to a widget based on its identifier :
		- @ref GL_GraphicLib_ReadResource : Reads a resource file and instantiates all widgets
		- @ref GL_GraphicLib_InstanciateResource : Instanciates a resource from Json string
		- @ref GL_Widget_ReadResource : Reads a resource file and instantiates all objects in the read file
		- @ref GL_Widget_InstanciateResource : Instanciates a resource from a string
		- @ref GL_Widget_SetTextById : Changes the text of the widget @ref GL_Widget_FormatProperties
		- @ref GL_Widget_GetTextById : Return the text of the widget
		- @ref GL_Widget_SetSourceById : Changes the image source of the widget @ref GL_Widget_Url
		- @ref GL_Widget_GetSourceById : Return the image source of the widget @ref GL_Widget_Url
		- @ref GL_Widget_SetMaskById : Sets the input mask 
		- @ref GL_Widget_SetUserDataById : Sets the contents of the user data attached to a widget
		- @ref GL_Widget_GetUserDataById : Sets the contents of the user data attached to a widget
		- @ref GL_Widget_GetCheckById : Gets the check state 
		- @ref GL_Widget_SetCheckById : Sets the check state 
		- @ref GL_Widget_RegisterCallbackById : Adds a callback to a widget of treatment for a given message type
		- @ref GL_Widget_UnregisterCallbackById : Removes a callback to a widget of treatment for a given message type

@}
@}

@addtogroup GL_GraphicLib
@{
@addtogroup GL_GraphicLibDoc Graphic library
@{
	The graphic library is a C framework providing GUI (Graphical User Interface) and other facilities 
	for black and white terminal or color terminal.
	
	First you must create an instance of the graphics library. 
	This instance must necessarily remain open throughout the lifetime of the application to avoid delays : 
	the creation of an instance load different skins and it takes time.
	
	The creation of an instance of the graphics library is done using the function @ref GL_GraphicLib_Create.
	
	The destruction of this instance is using the function @ref GL_GraphicLib_Destroy (All windows and their contents will be destroyed during this call).
	
	These functions allow to create and destroy the graphics library, and instantiate the widget from the resource file
		- @ref GL_IsPresent : Check if DLL is present
		- @ref GL_GraphicLib_Create : Creating a new instance of the graphics object library
		- @ref GL_GraphicLib_CreateWithParam :  Creating a new instance of the graphics object library with a specific parameter (remote server or particular skin)
		- @ref GL_GraphicLib_Destroy : Destroying an instance of the graphics object library
		- @ref GL_GraphicLib_ReadResource : Reads a resource file and instantiates all widgets
		- @ref GL_GraphicLib_InstanciateResource : Instanciates a resource from Json string

	These functions allow to know the errors produced when running the application : 
		- @ref GL_GraphicLib_GetErrorCode : Gets the last error code
		- @ref GL_GraphicLib_GetErrorMessages : Gets the error message

	These functions allow to obtain various information :
		- @ref GL_GraphicLib_GetTerminalType : Returns the terminal type name
		- @ref GL_GraphicLib_GetScreenSize : Gets the size in pixels of the terminal screen 
		- @ref GL_GraphicLib_GetVersion : Gets the DLL version and revision 
		- @ref GL_GraphicLib_GetWidgetAtPosition : Gets the widget at a given position
		- @ref GL_GraphicLib_IsTouchPresent : Indicates if the screen is a touch screen or not

	These functions allow the configuration of the graphics library :
		- @ref GL_GraphicLib_GetScreenOrientation : Gets the terminal screen orientation
		- @ref GL_GraphicLib_SetScreenOrientation : Sets the terminal screen orientation
		- @ref GL_GraphicLib_LockScreenOrientation : Prevents the screen to change its orientation. 
		- @ref GL_GraphicLib_UnlockScreenOrientation : Releases the screen orientation only if it has already been locked by the same graphiclib
		- @ref GL_GraphicLib_SetDefaultPath : Sets the default path
		- @ref GL_GraphicLib_GetDefaultPath : Gets the default path
		- @ref GL_GraphicLib_SetFontName : Sets the default font name
		- @ref GL_GraphicLib_GetFontName : Gets the default font name
		- @ref GL_GraphicLib_SetCharset : Changes the encoding charset of the graphic library
		- @ref GL_GraphicLib_GetCharset : Gets the encoding charset of the graphic library
		- @ref GL_GraphicLib_BindManyKey : Binds telium key to many virtual key
		- @ref GL_GraphicLib_BindSingleKey : Binds telium key to virtual key
		- @ref GL_GraphicLib_UnbindKey : Unbinds telium key 
		- @ref GL_GraphicLib_SetWindowSize : Sets the default size that must occupy the windows when they have no dimensions defined
		- @ref GL_GraphicLib_SetWindowPosition : Sets the default position to be taken by the windows when they have no defined position
		- @ref GL_GraphicLib_GetUserArea : Gets the user area rect

	These functions are used to simulate events such as mouse clicks or key pressed :
		- @ref GL_GraphicLib_SendKey : Simulates sending a key pressed message 
		- @ref GL_GraphicLib_SendClick : Simulates sending a click message 
		- @ref GL_GraphicLib_SendBreak : Sends a break, the messages are popped before stacking other 
@}

*/

/*<ALL>
	Top("goal",                      "GOAL",         "Top element", 
		ItemSingle("window",   "WINDOW", ""),
		ItemSingle("document", "DOCUMENT", ""),
		ItemSingle("usercontrol", "USERCONTROL", "")
	),
</ALL>*/

/** Widget context handle */
typedef struct T_GL_WIDGET * T_GL_HWIDGET;

/** local Screen location */
#define GL_SCREEN_LOCAL (NULL)

/** Graphic library context handle */
typedef struct T_GL_GRAPHIC_LIB * T_GL_HGRAPHIC_LIB;

/** Widget constructor */
typedef T_GL_HWIDGET (*T_GL_HWIDGET_CREATE)(T_GL_HWIDGET parent);

/** 
@addtogroup GL_GraphicLibCreation Creation and destruction
@{
*/

/** Viewer handle definition */
typedef struct T_GL_VIEWER * T_GL_HVIEWER;

#ifndef SWIG
/** Check if DLL is present
@return 1 if DLL is present 0 otherwise */
int GL_IsPresent(void);
#endif

/** Creating an instance of the graphics object library. The creation of the graphics library takes an important time, it is recommended to do creation once at application startup and use it for all windows created after.
@return Graphic library context handle  */
T_GL_HGRAPHIC_LIB GL_GraphicLib_Create(void) GL_EXCEPTION;

/** Creating an instance of the graphics object library. The creation of the graphics library takes an important time, it is recommended to do creation once at application startup and use it for all windows created after.
@param viewer set this value to NULL
@param skinName name of the skin. Default name is "GOAL".

The name of a skin is composed of the following pattern "[Name]_SK[Width]_[Height]" :
   - Name : name of skin
   - Width : screen width in pixels
   - Height : screen height in pixels

You can use wild card to select a particular skin ('?' For a ignore one character, '*' to ignore more characters), example :
   - GOAL_SK640_480 : Select the skin for a screen 640 x 480
   - GOAL_SK320_* : Select the first skin compatible with the width 320 pixels
   - GOAL : In this particular case the skin adapted to the screen will be automatically selected

@return Graphic library context handle  */
T_GL_HGRAPHIC_LIB GL_GraphicLib_CreateWithParam(T_GL_HVIEWER viewer, const char * skinName) GL_EXCEPTION;


/** Destroying an instance of the graphics object library
@param graphicLib Graphic library context handle */
void GL_GraphicLib_Destroy(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Reads a resource file and instantiates all widgets 
@param graphicLib Graphic library context handle 
@param filename name and file path configuration (See @ref GL_Widget_Url for the url coding)
@return returns the instantiated resource or null if an error is detected */
T_GL_HWIDGET GL_GraphicLib_ReadResource(T_GL_HGRAPHIC_LIB graphicLib, const char * filename) GL_EXCEPTION;

/** Instanciate a resource from json string
@param graphicLib Graphic library context handle 
@param content JSON string content the resource 
(The JSON string can be encoded in UTF-8, UTF-16 or UTF-32. If the string is encoded in UTF-32 or UTF-16 it is 
imperative to add a BOM at the begin of the string, to know the BOM supported see @ref T_GL_ENCODING_BOM)
@param size total size in bytes of the JSON string
@return returns the instantiated resource or null if an error is detected */
T_GL_HWIDGET GL_GraphicLib_InstanciateResource(T_GL_HGRAPHIC_LIB graphicLib, const char * content, unsigned long size);

/** 
@}
@addtogroup GL_GraphicLibError Error management
@{
*/

/** Gets the last error code (clear error code after this call)
@param graphicLib Graphic library context handle 
@return returns error code */
T_GL_ERROR_CODE GL_GraphicLib_GetErrorCode(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Gets the error message (Clear the error message after this call)
@param graphicLib Graphic library context handle 
@return returns message error (Never keep the pointer, it is deallocated automatically at the next call to this function) */
const char * GL_GraphicLib_GetErrorMessages(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** 
@}
@addtogroup GL_GraphicLibConfiguration Configuration
@{
@section GL_GraphicLibConfiguration_Introduction Display configuration
This section presents the configuration of the GOAL Library.

Configuration of the screen rotation :
	- @ref GL_GraphicLib_GetScreenOrientation
	- @ref GL_GraphicLib_SetScreenOrientation
	- @ref GL_GraphicLib_LockScreenOrientation
	- @ref GL_GraphicLib_UnlockScreenOrientation

Configuration of the default path :
	- @ref GL_GraphicLib_SetDefaultPath
	- @ref GL_GraphicLib_GetDefaultPath

Configuration of the text :
	- @ref GL_GraphicLib_SetFontName
	- @ref GL_GraphicLib_GetFontName
	- @ref GL_GraphicLib_SetCharset
	- @ref GL_GraphicLib_GetCharset

Configuration of the keypad :
	- @ref GL_GraphicLib_BindManyKey
	- @ref GL_GraphicLib_BindSingleKey
	- @ref GL_GraphicLib_UnbindKey

Configuration of the windows manager :
	- @ref GL_GraphicLib_SetWindowSize
	- @ref GL_GraphicLib_SetWindowPosition
	- @ref GL_GraphicLib_GetUserArea
	
<hr>@section GL_GraphicLib_ScreenOrientation Screen rotation

Starting with SDK 9.6.0, the screen rotation is one of the features of the Telium platform.
The screen rotation is the ability of the platform to go from portrait into landscape mode in the four directions (0, 90, 180 or 270 degrees).

The availability of the feature is depending on :
	- iWL280 or iWL350 hardware platform
	- HW Accelerometer detection
	- Orientation parameter in the Manager set to "On" 
	- non ZKA terminal (limitation to be studied later)

<b> WARNING: The feature will be limited when the running application use full screen display.</b> Especially, it means that when the footer, the header or the leds are enabled, the feature will not activate.

Remarks : for iWL350 terminal, the keypad in Idle screen is considered as footer and so de-activates the feature.

Remarks : Some screens will be locked by the Telium Platform :
	- The setup menu of the Manager for iWL280 for a better usability,
	- The PIN request screen for security reasons,
	- The ContactLess screen because of EMVCo constrains.

The screen rotation is available for full screen video and signature screen.

Using this feature can be done in 3 ways :
	- Lock the screen in one precise orientation with @ref GL_GraphicLib_LockScreenOrientation and @ref GL_GraphicLib_SetScreenOrientation,
	- Register the @ref GL_EVENT_ORIENTATION_CHANGE event with @ref GL_Widget_RegisterCallback to manage the screen rotation manually using event reception and @ref GL_GraphicLib_SetScreenOrientation,
	- Let the platform manage the screen rotation automatically using @ref GL_GraphicLib_UnlockScreenOrientation.

An example si available : @ref GL_SampleOrientation.c
*/

/** @brief Gets the current terminal screen orientation.
@sa @ref GL_GraphicLib_ScreenOrientation.
@param graphicLib Graphic library context handle 
@return the screen orientation @ref T_GL_SCREEN_ORIENTATION */
T_GL_SCREEN_ORIENTATION GL_GraphicLib_GetScreenOrientation(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** @brief Changes the screen orientation. 

This can be done only when the screen isn't already locked by another screen (i.e. graphiclib context).
@sa @ref GL_GraphicLib_ScreenOrientation.
@param graphicLib Graphic library context handle 
@param orientation Next orientation to set to the screen
@return @ref GL_SUCCESS if the screen has been correctly locked else returns @ref GL_ERROR_SCREEN_ALREADY_LOCKED if the screen is already locked 
or @ref GL_ERROR_SCREEN_IN_ROTATION if the screen is currently changing its orientation*/
T_GL_ERROR_CODE GL_GraphicLib_SetScreenOrientation(T_GL_HGRAPHIC_LIB graphicLib, T_GL_SCREEN_ORIENTATION orientation) GL_EXCEPTION;

/** @brief Prevents the screen from changing its orientation either automaticaly or by another screen (i.e. graphiclib context).
@sa @ref GL_GraphicLib_ScreenOrientation.
@param graphicLib Graphic library context handle 
@return @ref GL_SUCCESS if the screen has been correctly locked else returns @ref GL_ERROR_SCREEN_ALREADY_LOCKED if the screen is already locked 
or @ref GL_ERROR_SCREEN_IN_ROTATION if the screen is currently changing its orientation*/
T_GL_ERROR_CODE GL_GraphicLib_LockScreenOrientation(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** @brief Releases the screen orientation only if it has been locked by the same screen (i.e. graphiclib context).

The screen orientation is therefore automatically managed by the GOAL librairy.
The events indicating rotation of the screen will be received only if screen has registered to @ref GL_EVENT_ORIENTATION_CHANGE event with @ref GL_Widget_RegisterCallback.<br>
@sa @ref GL_GraphicLib_ScreenOrientation.
@param graphicLib Graphic library context handle */
void GL_GraphicLib_UnlockScreenOrientation(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Sets the default path
@param graphicLib Graphic library context handle 
@param path default path */
void GL_GraphicLib_SetDefaultPath(T_GL_HGRAPHIC_LIB graphicLib, const char * path) GL_EXCEPTION;

/** Gets the default path
@param graphicLib Graphic library context handle 
@return default path */
const char * GL_GraphicLib_GetDefaultPath(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Sets the default font name
WARNING : the font change must be done before any widget creation. To avoid this problem make the change just after the @ref GL_GraphicLib_Create.
@param graphicLib Graphic library context handle
@param name font name */
void GL_GraphicLib_SetFontName(T_GL_HGRAPHIC_LIB graphicLib, const char * name) GL_EXCEPTION;

/** Gets the default font name
@param graphicLib Graphic library context handle 
@return name font name */
const char * GL_GraphicLib_GetFontName(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Changes the encoding charset of the graphic library (default encoding is utf8).
The charset modification affects only the widgets created thereafter
@param graphicLib Graphic library context handle 
@param charset encoding charset*/
void GL_GraphicLib_SetCharset(T_GL_HGRAPHIC_LIB graphicLib, T_GL_ENCODING_CHARSET charset) GL_EXCEPTION;

/** Gets the encoding charset of the graphic library
@param graphicLib Graphic library context handle 
@return charset encoding charset */
T_GL_ENCODING_CHARSET GL_GraphicLib_GetCharset(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Binds telium key to many virtual key
@param graphicLib Graphic library context handle 
@param teliumKey telium keyboard key (see @ref GL_TypesKeys)
@param keys virtual keys list 
@param count number of keys in list */
void GL_GraphicLib_BindManyKey(T_GL_HGRAPHIC_LIB graphicLib, T_GL_WCHAR teliumKey, const T_GL_WCHAR * keys, unsigned long count) GL_EXCEPTION;

/** Binds telium key to virtual key
@param graphicLib Graphic library context handle 
@param teliumKey telium keyboard key (see @ref GL_TypesKeys)
@param key virtual key */
void GL_GraphicLib_BindSingleKey(T_GL_HGRAPHIC_LIB graphicLib, T_GL_WCHAR teliumKey, T_GL_WCHAR key) GL_EXCEPTION;

/** Unbinds telium key 
@param graphicLib Graphic library context handle 
@param teliumKey telium keyboard key */
void GL_GraphicLib_UnbindKey(T_GL_HGRAPHIC_LIB graphicLib, T_GL_WCHAR teliumKey) GL_EXCEPTION;

/** Sets the default size that must occupy the windows when they have no dimensions defined
@param graphicLib Graphic library context handle 
@param width new width coded according to the chosen unit
@param height new height coded according to the chosen unit 
@param unit unit of size */
void GL_GraphicLib_SetWindowSize(T_GL_HGRAPHIC_LIB graphicLib, T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit) GL_EXCEPTION;

/** Sets the default position to be taken by the windows when they have no defined position
@param graphicLib Graphic library context handle 
@param x new X coordinates coded according to the chosen unit 
@param y new Y coordinates coded according to the chosen unit
@param unit unit size */
void GL_GraphicLib_SetWindowPosition(T_GL_HGRAPHIC_LIB graphicLib, T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit) GL_EXCEPTION;

/** Gets the user area 
@param graphicLib Graphic library context handle 
@return the rectangle of the user area on the screen */
T_GL_RECT GL_GraphicLib_GetUserArea(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;


/** 
@}
@addtogroup GL_GraphicLibInformation Information
@{
*/


/** @return the terminal type name (@ref GL_TypesTerminal)
@param graphicLib Graphic library context handle */
const char *GL_GraphicLib_GetTerminalType(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Gets the size in pixels of the terminal screen 
@param graphicLib Graphic library context handle
@return the size */
T_GL_SIZE GL_GraphicLib_GetScreenSize(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Indicates if the screen is a touch screen or not
@param graphicLib Graphic library context handle
@return the touch screen state */
bool GL_GraphicLib_IsTouchPresent(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Gets the widget at a given position
@param graphicLib Graphic library context handle
@param x X coordinate in pixels absolute to screen
@param y Y coordinate in pixels absolute to screen
@return widget handle or null if if no widget found */
T_GL_HWIDGET GL_GraphicLib_GetWidgetAtPosition(T_GL_HGRAPHIC_LIB graphicLib, T_GL_COORD x, T_GL_COORD y) GL_EXCEPTION;

/** Saves the contents of the screen into an image file
@param graphicLib Graphic library context handle
@param filename filename (See @ref GL_Widget_Url for the url coding)
@param mimeType mime type to encode the image file, only @ref GL_MIME_IMAGE_WGU and @ref GL_MIME_IMAGE_BMP are supported. 
WARNING : If you use the BMP format you must have previously loaded this image decoder in the terminal.*/
void GL_GraphicLib_SaveImage(T_GL_HGRAPHIC_LIB graphicLib, const char * filename, const char * mimeType) GL_EXCEPTION;

/** Version and revision of DLL */
typedef struct T_GL_VERSION
{
	/** Version value */
	ulong version;

	/** Revision value */
	ulong revision;
} T_GL_VERSION;

/** Gets the DLL version and revision 
@return version and revision */
T_GL_VERSION GL_GraphicLib_GetVersion(void) GL_EXCEPTION;

/** Resize the internal size of cache
<b>CAUTION: The maximum size is limited to 32 MB, 
if you resize to this value you can receive an out of memory if you use the dllmalloc.</b>
<b>CAUTION : if several applications change the size only the last request is taken into account.</b>
@param graphicLib Graphic library context handle
@param size new size of cache in bytes (maximum 32 mo) */
void GL_GraphicLib_ResizeCache(T_GL_HGRAPHIC_LIB graphicLib, ulong size);

/** 
@}
@addtogroup GL_GraphicLibSimulation Simulation
@{
*/

/** Simulates sending a key pressed message to the first window that calls the function @ref GL_Window_Dispatch (simulates a key press on the keyboard).
ATTENTION: Only one window receives key press events, it is always the window that has focus.
@param graphicLib Graphic library context handle 
@param key key value */
void GL_GraphicLib_SendKey(T_GL_HGRAPHIC_LIB graphicLib, T_GL_WCHAR key) GL_EXCEPTION;

/** Simulates sending a click message to the first window that calls the function GL_Window_Dispatch (simulates a stylus down and stylus up)
@param graphicLib Graphic library context handle 
@param x X coordinates relatives to the focused window coded according to the chosen unit  
@param y Y coordinates relatives to the focused window coded according to the chosen unit  
@param unit unit of coordinates */
void GL_GraphicLib_SendClick(T_GL_HGRAPHIC_LIB graphicLib, T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit) GL_EXCEPTION;

/** Sends a break, the messages are popped before stacking other 
@param graphicLib Graphic library context handle */
void GL_GraphicLib_SendBreak(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Gets the size of a text in pixels according to the selected font name, font size and font style.
ATTENTION : this function returns raw data, It does not handle the wrapped texts and/or texts on multiple lines with carriage returns, 
if you want to know the size of a widget it is preferable to use the function @ref GL_Widget_GetRect.
@param graphicLib Graphic library context handle 
@param text one line of text (Formatting characters should not be present in the chain)
@param fontName name of font or null for default font
@param fontStyle font stype to select 
@param fontHeight height in pixels of the font to select 
@return the size of the text in pixels */
T_GL_SIZE GL_GraphicLib_GetTextSize(T_GL_HGRAPHIC_LIB graphicLib, const char * text, const char * fontName, T_GL_FONT_STYLE fontStyle, T_GL_DIM fontHeight) GL_EXCEPTION;

/** 
@}
@}

*/

/**
@}
*/


#include "GL_Widget.h"
#include "GL_SignatureFile.h"
#include "GL_StringList.h"
#include "GL_File.h"
#include "GL_Dir.h"
#include "GL_Timer.h"
#include "GL_Message.h"
#include "GL_Window.h"
#include "GL_Button.h"
#include "GL_Icon.h"
#include "GL_CheckButton.h"
#include "GL_RadioButton.h"
#include "GL_Layout.h"
#include "GL_Label.h"
#include "GL_Picture.h"
#include "GL_Edit.h"
#include "GL_VScrollBar.h"
#include "GL_HScrollBar.h"
#include "GL_Drawing.h"
#include "GL_ProgressBar.h"
#include "GL_ScrollView.h"
#include "GL_List.h"
#include "GL_Dialog.h"
#include "GL_Palette.h"
#include "GL_VirtualKeyboard.h"
#include "GL_Media.h"
#include "GL_HSlider.h"
#include "GL_Plugin.h"
#include "GL_Document.h"
#include "GL_Print.h"
#include "GL_Signature.h"
#include "GL_Viewer.h"
#include "GL_IconButton.h"
#include "GL_Barcode.h"
#include "GL_UserControl.h"
#include "GL_ArrowButton.h"

#ifdef WIN32
#undef  _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

/* __NEWTYPE__ */
#ifdef __cplusplus
}
#endif
#endif // GL_GraphicLib_h_INCLUDED
