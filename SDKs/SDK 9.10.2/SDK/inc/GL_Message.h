// $Id: GL_Message.h,v 1.1.2.28 2012/07/16 12:23:32 rbertholet Exp $
#ifndef GL_Message_h_INCLUDED
#define GL_Message_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_Message
@{
@addtogroup GL_MessageDoc Message
@{
	The messages correspond to user events (key pressed, stylus move, stylus click, time out...) 
	and the graphics library events (lost focus, get focus, ...)

	See also : @ref GL_Widget_CommonMessage and @ref GL_Widget_CallbackProperties

Below is a list of specific functions to this class :
	- @ref GL_Message_Create         : Create the message  (@ref GL_Widget_UserDataProperties)
	- @ref GL_Message_Destroy        : Releases a message and free its associated memory  (@ref GL_Widget_UserDataProperties)
	- @ref GL_Message_GetType        : Gets the type of an message
	- @ref GL_Message_GetPosition    : Returns the position of stylus in case of stylus message
	- @ref GL_Message_SetPosition    : Sets the position of stylus in case of STYLUS message
	- @ref GL_Message_GetMove        : Returns the move of stylus (only for the stylus scroll message)
	- @ref GL_Message_SetMove        : Sets the move of stylus in case of STYLUS message
	- @ref GL_Message_GetKey         : Gets the key code in case of KEY message
	- @ref GL_Message_SetKey         : Sets the key code in case of KEY message
	- @ref GL_Message_GetSize        : Return the size of area (PAINT event)
	- @ref GL_Message_GetRange       : Gets the range 
	- @ref GL_Message_SetRange       : Sets the range 
	- @ref GL_Message_SetResult      : Sets the execution result of the current window. The default value is GL_KEY_NONE. (@ref GL_Window_MainLoop)
	- @ref GL_Message_GetResult      : Gets the execution result of the current window. (@ref GL_Window_MainLoop)
	- @ref GL_Message_SetUserData    : Sets the contents of the user data attached to a window (@ref GL_Widget_UserDataProperties)
	- @ref GL_Message_GetUserData    : Gets the contents of the user data attached to a window (@ref GL_Widget_UserDataProperties)
	- @ref GL_Message_GetData        : Gets the data attached to this message (@ref GL_Widget_UserDataProperties)
	- @ref GL_Message_SetData        : Sets the data attached to this message (@ref GL_Widget_UserDataProperties)
	- @ref GL_Message_GetWidget      : Gets the widget handle associated with the message
	- @ref GL_Message_GetTimer       : Gets the timer handle attached to the timeout 
	- @ref GL_Message_GetWindow      : Gets the window handle associated with the message
	- @ref GL_Message_GetUserControl : Gets the user control handle associated to this message
	- @ref GL_Message_GetScreenOrientation : Gets the screen orientation

Example of using callbacks message :
	@include GL_SamplePlayer.c
@}

*/
/** Create the message, allows the application to create its own message
@param widget widget handle
@param type event type
@return handle on the message or NULL if none, message must be released with GL_Message_Release */
T_GL_HMESSAGE GL_Message_Create(T_GL_HWIDGET widget, T_GL_EVENT_TYPE type) GL_EXCEPTION;

/** Releases a message and free its associated memory.
Messages are normally automatically destroyed if they are sent by goal, 
the only use case for this function is when a message is created and must be destroyed before the sent
@param message message to release */
void GL_Message_Destroy(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Gets the type of an message
@param message message from which getting the type
@return type of the message found */
T_GL_EVENT_TYPE GL_Message_GetType(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Returns the position in widget of stylus in case of stylus message
@param message message from which getting the position
@return position structure found */
T_GL_POSITION GL_Message_GetPosition(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Sets the position of stylus in case of STYLUS message
@param message message from which getting the key code
@param x x coordinates
@param y y coordinates */
void GL_Message_SetPosition(T_GL_HMESSAGE message, T_GL_COORD x, T_GL_COORD y) GL_EXCEPTION;

/** Returns the move of stylus (only for the stylus scroll message)
@param message message from which getting the move
@return move structure found */
T_GL_MOVE GL_Message_GetMove(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Sets the move of stylus in case of STYLUS message
@param message message from which getting the key code
@param x x coordinates
@param y y coordinates */
void GL_Message_SetMove(T_GL_HMESSAGE message, T_GL_COORD x, T_GL_COORD y) GL_EXCEPTION;

/** Gets the key code in case of KEY message (@ref GL_TypesKeys)
@param message message from which getting the key code
@return key key code */
T_GL_WCHAR GL_Message_GetKey(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Sets the key code in case of KEY message
@param message message from which getting the key code
@param key key code */
void GL_Message_SetKey(T_GL_HMESSAGE message, T_GL_WCHAR key) GL_EXCEPTION;

/** Return the size of area (PAINT event)
@param message message from which getting the size
@return size structure found */
T_GL_SIZE GL_Message_GetSize(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Gets the widget handle associated with the message
@param message message from which getting the widget handle
@return the widget handle */
T_GL_HWIDGET GL_Message_GetWidget(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Gets a widget in a window according to its id
@param message message from which getting the widget handle
@param id the identifier 
@return the widget handle */
T_GL_HWIDGET GL_Message_GetWidgetById(T_GL_HMESSAGE message, T_GL_ID id) GL_EXCEPTION;

/** Gets the timer handle attached to the timeout 
@param message message handle
@return the timer handle */
T_GL_HWIDGET GL_Message_GetTimer(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Gets the number of timer epired in the event
@param message message handle
@return the count of timer expired */
ulong GL_Message_GetTimerCount(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Gets the window handle associated with the message
@param message message from which getting the widget handle
@return the window handle */
T_GL_HWIDGET GL_Message_GetWindow(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Gets the user control handle associated to this message (to get the closest usercontrol parent)
@param message message from which getting the user control handle
@return the first user control handle */
T_GL_HWIDGET GL_Message_GetUserControl(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Get the graphic librairy handle associated with the message 
@param message message handle
@return graphic library handle */
T_GL_HGRAPHIC_LIB GL_Message_GetGraphicLib(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Return the range 
@param message message from which getting the range
@return range structure found */
T_GL_RANGE GL_Message_GetRange(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Sets the range 
@param message message handle
@param range range to set */
void GL_Message_SetRange(T_GL_HMESSAGE message, T_GL_RANGE range) GL_EXCEPTION;

/** Gets the execution result of the current window. For predefined result value see @ref GL_TypesResults or @ref GL_TypesKeys
@param message message handle
@return result value */
ulong GL_Message_GetResult(T_GL_HMESSAGE message) GL_EXCEPTION;

/** Sets the execution result of the current window. The default value is GL_KEY_NONE.
This value set will be returned to each call of @ref GL_Window_Dispatch,
for predefined result value see @ref GL_TypesResults or @ref GL_TypesKeys
@param message message handle
@param result result value */
void GL_Message_SetResult(T_GL_HMESSAGE message, ulong result) GL_EXCEPTION;

/** Gets the contents of the user data attached to a window (@ref GL_Widget_UserDataProperties)
@param message message handle
@param data data buffer handle
@param dataSize maximal size of data buffer
@return size of data gets */
unsigned long GL_Message_GetUserData(T_GL_HMESSAGE message, void * data, unsigned long dataSize) GL_EXCEPTION;

/** Sets the contents of the user data attached to a window (@ref GL_Widget_UserDataProperties)
@param message message handle
@param data data buffer handle
@param dataSize maximal size of data buffer */
void GL_Message_SetUserData(T_GL_HMESSAGE message, const void * data, unsigned long dataSize) GL_EXCEPTION;

/** Gets the data attached to this message
@param message message handle
@param data data buffer handle (null accepted to get the data length)
@param dataSize maximal size of data buffer (zero accepted to get the data length)
@return size of data gets */
unsigned long GL_Message_GetData(T_GL_HMESSAGE message, void * data, unsigned long dataSize) GL_EXCEPTION;

/** Sets the data attached to this message
@param message message handle
@param data data buffer handle
@param dataSize maximal size of data buffer */
void GL_Message_SetData(T_GL_HMESSAGE message, const void * data, unsigned long dataSize) GL_EXCEPTION;

/** Gets the screen orientation
@param message message handle
@return return the screen orientation */
T_GL_SCREEN_ORIENTATION GL_Message_GetScreenOrientation(T_GL_HMESSAGE message) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif

#endif // GL_Message_h_INCLUDED
