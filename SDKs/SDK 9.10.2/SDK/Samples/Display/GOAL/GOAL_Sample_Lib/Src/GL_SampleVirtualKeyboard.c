#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Callback for processing a click on valid button message.
// The "message" contains details of the message received by the window
static bool OnValid(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}

// Callback for processing a click on cancel message.
// The "message" contains details of the message received by the window
static bool OnCancel(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 1);
	return true;
}

// Sample of virtual keyboard
void GL_SampleVirtualKeyboard(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET virtualKeyboard;
	const char * text;
	ulong result;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 100, 100, GL_UNIT_PERCENT);

	// Creating a virtual keyboard
	virtualKeyboard = GL_VirtualKeyboard_Create(window);

	// Sets the default text
	GL_Widget_SetText(virtualKeyboard, "Hello");

	// Registering a callback. This callback will be called every click on the button valid
	GL_Widget_RegisterCallback(virtualKeyboard, GL_EVENT_VALID, OnValid);

	// Registering a callback. This callback will be called every click on the button cancel
	GL_Widget_RegisterCallback(virtualKeyboard, GL_EVENT_CANCEL, OnCancel);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	result = GL_Window_MainLoop(window);

	// If the valid button pressed
	if (result == 0)
	{
		// Gets the text entered
		text = GL_Widget_GetText(virtualKeyboard);
		(void)text; // <- Avoid a compilation warning
	}

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
