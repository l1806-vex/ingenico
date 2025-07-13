#ifndef GL_Window_h_INCLUDED
#define GL_Window_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_Window
@{
@addtogroup GL_WindowDoc Window
@{
This widget allows management of a window on the screen, it is the highest level widget used for receiving all the other widgets.
By default the window is positioned at 0.0 and occupies the entire screen.


The window creation is done by the function @ref GL_Window_Create.

The destruction of the window is done by the function @ref GL_Widget_Destroy.

<h2>Geometry</h2>
	To change the geometry of the window you must use the following functions:
	 - @ref GL_Widget_GetSize, @ref GL_Widget_SetSize : Force the window size (In this case the minimum and maximum sizes are ignored)
	 - @ref GL_Widget_GetPosition, @ref GL_Widget_SetPosition : Absolute position on the screen (In this case the alignement and margins are ignored)
	 - @ref GL_Widget_GetMinSize, @ref GL_Widget_SetMinSize : Minimum size occupied
	 - @ref GL_Widget_GetMaxSize, @ref GL_Widget_SetMaxSize : Maximum size occupied
	 - @ref GL_Widget_GetMargins, @ref GL_Widget_SetMargins : Margin placement on the screen to use with the alignment
	 - @ref GL_Widget_GetBackAlign, @ref GL_Widget_SetBackAlign : Alignment on the screen
 
<h2>Windows management</h2>
	You can show or hide a window screen without destroying it, using the following functions :
	- @ref GL_Window_Show : show the window
	- @ref GL_Window_Hide : hide the window
	
<h2>Messages management</h2>
	The window to work properly and to handle messages needs a periodic call to the function @ref GL_Window_Dispatch.

	Each message received by the window can be intercepted by registering a callback (type @ref GL_Widget_RegisterCallback)
	using the function @ref T_GL_MESSAGE_CALLBACK. See also @ref GL_Widget_CallbackProperties.

<h2>Results</h2>
	Fonctions to manage the execution result : 
	- @ref GL_Window_SetResult : Sets the execution result of the current window. The default value is GL_KEY_NONE.
	- @ref GL_Window_GetResult : Gets the execution result of the current window. 
	
	For predefined result value see @ref GL_TypesResults or @ref GL_TypesKeys.

<h2>Simulation of messages</h2>
	Sometimes it is necessary to simulate a key press or a click pen. It is possible using the following functions:
	- @ref GL_Window_SendKey simulates pressing a key on the keyboard.
	- @ref GL_Window_SendClick simulates a press on the screen with your finger, stylus or a stylus click.


<h2>Focus</h2>
	The focus is set by default on the first widget found in the window, when the focus is positioned on an element, 
	it can receive keyboard messages.
	- @ref GL_Window_NextFocus : Sets the focus to the next widget
	- @ref GL_Window_PreviousFocus : Sets the focus to the previous widget
	- @ref GL_Window_GetFocus : Gets the handle of the widget that has focus
	- @ref GL_Widget_SetFocus : Sets the focus state on the widget if the widget is focusable (only a single widget on a window can receive focus)

<h2>Miscellaneous</h2>
	The stylus cursor can be made visible by using the function @ref GL_Window_SetCursor.
	To saves the content of the window into an image file use @ref GL_Window_SaveImage.

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_ShortcutProperties
	- @ref GL_Widget_UserDataProperties

Methods inherited from class widget :
	- @ref GL_Widget_GetSize
	- @ref GL_Widget_SetSize
	- @ref GL_Widget_GetMinSize
	- @ref GL_Widget_SetMinSize
	- @ref GL_Widget_GetMaxSize
	- @ref GL_Widget_SetMaxSize
	- @ref GL_Widget_GetPosition
	- @ref GL_Widget_SetPosition
	- @ref GL_Widget_GetVisible
	- @ref GL_Widget_SetVisible
	- @ref GL_Widget_GetBackAlign
	- @ref GL_Widget_SetBackAlign
	- @ref GL_Widget_Destroy
	- @ref GL_Widget_SetMargins
	- @ref GL_Widget_GetMargins
	- @ref GL_Widget_SetBorders
	- @ref GL_Widget_GetBorders
	- @ref GL_Widget_GetBackColor
	- @ref GL_Widget_SetBackColor
	- @ref GL_Widget_GetUserData
	- @ref GL_Widget_SetUserData
	- @ref GL_Widget_ReadResource
	- @ref GL_Widget_InstanciateResource

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>
	Below is an example of creating a blank window. We leave this window by pressing a button.

	@include GL_SampleWindow.c

	Below is an example of send key

	@include GL_SampleSendKey.c

	Below is an example of send click

	@include GL_SampleSendClick.c
	
@}
*/

/*<ALL>
	Extension("WINDOW",            "WIDGET",     "This widget allows management of a window on the screen",
		RefOne("children",         "CHILDREN",   "Children items attached to this widget"),
	),
</ALL>*/

/** Creating a window in the user area 
@param graphicLib handle on the graphical client
@return returns the window handle created or null if creation failed */
T_GL_HWIDGET GL_Window_Create(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Makes the window visible
@param window the window handle */
void GL_Window_Show (T_GL_HWIDGET window) GL_EXCEPTION;

/** Makes invisible window
@param window the window handle */
void GL_Window_Hide (T_GL_HWIDGET window) GL_EXCEPTION;

/** Sets the focus to the next widget
@param window window handle */
void GL_Window_NextFocus(T_GL_HWIDGET window) GL_EXCEPTION;

/** Sets the focus to the previous widget
@param window window handle */
void GL_Window_PreviousFocus(T_GL_HWIDGET window) GL_EXCEPTION;

/** Gets the handle of the widget that has focus
@param window window handle 
@return widget handle or null if if no widget has focus */
T_GL_HWIDGET GL_Window_GetFocus(T_GL_HWIDGET window) GL_EXCEPTION;

/** Sets the stylus cursor displayed on window
@param window window handle
@param cursor cursor type */
void GL_Window_SetCursor(T_GL_HWIDGET window, T_GL_CURSOR cursor) GL_EXCEPTION;

/** Refresh the window displayed and dispatch all messages received
@param window window handle
@param duration duration in milliseconds 
(WARNING this is the maximum wait time of an event. If you need a precise duration you must use @ref GL_TimerDoc)
@return returns the result previously set by the function @ref GL_Window_SetResult or @ref GL_Message_SetResult */
ulong GL_Window_Dispatch(T_GL_HWIDGET window, unsigned int duration) GL_EXCEPTION;

/** Send key pressed message (simulates a key press on the keyboard) 
WARNING: this function should always be called after a first call to GL_Window_Dispatch,
To take into account the key message you must call the function GL_Window_Dispatch after this function.
@param window window handle
@param key key value */
void GL_Window_SendKey(T_GL_HWIDGET window, T_GL_WCHAR key) GL_EXCEPTION;

/** Send click message (simulates a stylus down and stylus up)
WARNING: this function should always be called after a first call to GL_Window_Dispatch,
To take into account the key message you must call the function GL_Window_Dispatch after this function.
@param window window handle
@param x new X coordinates relatives to the window coded according to the chosen unit  
@param y new Y coordinates relatives to the window coded according to the chosen unit  
@param unit unit of coordinates */
void GL_Window_SendClick(T_GL_HWIDGET window, T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit) GL_EXCEPTION;

/** Sets the execution result of the current window. The default value is GL_KEY_NONE.
This value set will be returned to each call of @ref GL_Window_Dispatch.
For predefined result value see @ref GL_TypesResults or @ref GL_TypesKeys
@param window window handle
@param result result value */
void GL_Window_SetResult(T_GL_HWIDGET window, ulong result) GL_EXCEPTION;

/** Gets the execution result of the current window. For predefined result value see @ref GL_TypesResults or @ref GL_TypesKeys
@param window window handle
@return result value */
ulong GL_Window_GetResult(T_GL_HWIDGET window) GL_EXCEPTION;

/** Displays the window until the execution result is positioned
@param window window handle
@return returns the result previously set by the function @ref GL_Window_SetResult or @ref GL_Message_SetResult */
ulong GL_Window_MainLoop(T_GL_HWIDGET window) GL_EXCEPTION;

/** Sets the inactivity timer (@ref GL_EVENT_INACTIVITY, @ref GL_RESULT_INACTIVITY)
@param window window handle
@param duration duration in millisecondes (@ref GL_TIME_INFINITE for the infinite) */
void GL_Window_SetInactivityDuration(T_GL_HWIDGET window, T_GL_DURATION duration) GL_EXCEPTION;

/** Gets the inactivity timer (@ref GL_EVENT_INACTIVITY)
@param window window handle
@return  duration in millisecondes */
ulong GL_Window_GetInactivityDuration(T_GL_HWIDGET window) GL_EXCEPTION;

/** Gets the widget at a given position
@param window window handle 
@param x X coordinate relative to window, coded according to the chosen unit 
@param y Y coordinate relative to window, coded according to the chosen unit 
@param unit unit of coordinates
@return widget handle or null if if no widget found */
T_GL_HWIDGET GL_Window_GetWidgetAtPosition(T_GL_HWIDGET window, T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit) GL_EXCEPTION;

/** Saves the contents of the window into an image file
@param window window handle
@param filename filename (See @ref GL_Widget_Url for the url coding)
@param mimeType mime type to encode the image file, only @ref GL_MIME_IMAGE_WGU and @ref GL_MIME_IMAGE_BMP are supported. 
WARNING : If you use the BMP format you must have previously loaded this image decoder in the terminal.*/
void GL_Window_SaveImage(T_GL_HWIDGET window, const char * filename, const char * mimeType) GL_EXCEPTION;

/** Gets the rectangle of the useful area of the window
WARNING : This function returns the correct values only after a call of function @ref GL_Window_Dispatch.
WARNING : The active area does not include the border of the window
@param window window handle
@return Rectangle occupied by the ar on the window. The coordinates and sizes are expressed in pixels. */
T_GL_RECT GL_Window_GetArea(T_GL_HWIDGET window) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif

#endif // GL_Window_h_INCLUDED
