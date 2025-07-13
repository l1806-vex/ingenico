#include "GL_GraphicLib.h"
#include "GL_Samples.h"

#define GL_ID_UP 0
#define GL_ID_DOWN 1
#define GL_ID_LEFT 2
#define GL_ID_RIGHT 3
#define GL_ID_UNLOCK 4

// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnQuit(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}

// Callback for processing a screen orientation unlock
static bool OnUnlock(T_GL_HMESSAGE message)
{
	// Unlock the screen orientation
	GL_GraphicLib_UnlockScreenOrientation(GL_Message_GetGraphicLib(message));
	return true;
}
// Callback for processing a screen orientation lock on up
static bool OnLockUp(T_GL_HMESSAGE message)
{
	// Lock the screen orientation on up
	GL_GraphicLib_SetScreenOrientation(GL_Message_GetGraphicLib(message), GL_SCREEN_ORIENTATION_UP);
	return true;
}
// Callback for processing a screen orientation lock on down
static bool OnLockDown(T_GL_HMESSAGE message)
{
	// Lock the screen orientation on down
	GL_GraphicLib_SetScreenOrientation(GL_Message_GetGraphicLib(message), GL_SCREEN_ORIENTATION_DOWN);
	return true;
}

// Callback for processing a screen orientation lock on left
static bool OnLockLeft(T_GL_HMESSAGE message)
{
	// Lock the screen orientation on left
	GL_GraphicLib_SetScreenOrientation(GL_Message_GetGraphicLib(message), GL_SCREEN_ORIENTATION_LEFT);
	return true;
}

// Callback for processing a screen orientation lock on right
static bool OnLockRight(T_GL_HMESSAGE message)
{
	// Lock the screen orientation on right
	GL_GraphicLib_SetScreenOrientation(GL_Message_GetGraphicLib(message), GL_SCREEN_ORIENTATION_RIGHT);
	return true;
}

// Callback for processing a screen orientation lock on right
static bool OnUserAreaChanged(T_GL_HMESSAGE message)
{
	// According to the screen orientation colors the text of button
	switch(GL_Message_GetScreenOrientation(message))
	{
	case GL_SCREEN_ORIENTATION_UP:
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_UP   ), GL_COLOR_RED);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_DOWN ), GL_COLOR_LABEL_TEXT);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_LEFT ), GL_COLOR_LABEL_TEXT);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_RIGHT), GL_COLOR_LABEL_TEXT);
		break;

	case GL_SCREEN_ORIENTATION_DOWN:
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_UP   ), GL_COLOR_LABEL_TEXT);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_DOWN ), GL_COLOR_RED);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_LEFT ), GL_COLOR_LABEL_TEXT);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_RIGHT), GL_COLOR_LABEL_TEXT);
		break;

	case GL_SCREEN_ORIENTATION_LEFT:
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_UP   ), GL_COLOR_LABEL_TEXT);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_DOWN ), GL_COLOR_LABEL_TEXT);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_LEFT ), GL_COLOR_RED);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_RIGHT), GL_COLOR_LABEL_TEXT);
		break;

	case GL_SCREEN_ORIENTATION_RIGHT:
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_UP   ), GL_COLOR_LABEL_TEXT);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_DOWN ), GL_COLOR_LABEL_TEXT);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_LEFT ), GL_COLOR_LABEL_TEXT);
		GL_Widget_SetForeColor(GL_Message_GetWidgetById(message, GL_ID_RIGHT), GL_COLOR_RED);
		break;

	default:
		break;
	}
	return true;
}

// Sample of screen orientation
void GL_SampleOrientation(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET button;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Creating quit button
	button = GL_Button_Create(window);

		// Set text button
		GL_Widget_SetText(button,"quit");
	
		// Place in the left
		GL_Widget_SetBackAlign(button, GL_ALIGN_BOTTOM_RIGHT);

		// Registering a callback. This callback will be called every click on the button
		GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnQuit);

	// Creating a button 
	button = GL_Button_Create(window);
		// Set text button
		GL_Widget_SetText(button,"up");

		// Set the id
		GL_Widget_SetId(button, GL_ID_UP);

		// Place in the up
		GL_Widget_SetBackAlign(button, GL_ALIGN_TOP);

		// Registering a callback. This callback will be called every click on the button
		GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnLockUp);

	// Creating button
	button = GL_Button_Create(window);
		// Set text button
		GL_Widget_SetText(button,"down");
	
		// Set the id
		GL_Widget_SetId(button, GL_ID_DOWN);

		// Place in the down
		GL_Widget_SetBackAlign(button, GL_ALIGN_BOTTOM);

		// Registering a callback. This callback will be called every click on the button
		GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnLockDown);

	// Creating button
	button = GL_Button_Create(window);
		// Set text button
		GL_Widget_SetText(button,"left");
	
		// Set the id
		GL_Widget_SetId(button, GL_ID_LEFT);

		// Place in the left
		GL_Widget_SetBackAlign(button, GL_ALIGN_LEFT);

		// Registering a callback. This callback will be called every click on the button
		GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnLockLeft);

	// Creating right
	button = GL_Button_Create(window);
		// Set text button
		GL_Widget_SetText(button,"right");
	
		// Set the id
		GL_Widget_SetId(button, GL_ID_RIGHT);

		// Place in the left
		GL_Widget_SetBackAlign(button, GL_ALIGN_RIGHT);

		// Registering a callback. This callback will be called every click on the button
		GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnLockRight);

	// Creating right
	button = GL_Button_Create(window);
		// Set text button
		GL_Widget_SetText(button,"unlock");
	
		// Registering a callback. This callback will be called every click on the button
		GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnUnlock);

	// Registering a callback. This callback will be called every orientation changed
	GL_Widget_RegisterCallback(window, GL_EVENT_USERAREA_CHANGED, OnUserAreaChanged);

	// Prevent screen from changing its orientation
	GL_GraphicLib_LockScreenOrientation(graphicLib);

	// Display window and wait clic on button
	GL_Window_MainLoop(window);

	// Restore screen orientation to the up
	GL_GraphicLib_SetScreenOrientation(graphicLib, GL_SCREEN_ORIENTATION_UP);

	// Allow screen to change its orientation
	GL_GraphicLib_UnlockScreenOrientation(graphicLib);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
