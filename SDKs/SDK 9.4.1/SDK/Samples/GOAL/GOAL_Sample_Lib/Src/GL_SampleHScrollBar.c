#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnClick(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}


// Sample of horizontal scroll bar
void GL_SampleHScrollBar(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET bar;
	T_GL_COORD   value;
	ulong result = GL_RESULT_NONE;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

	// Creating a scroll bar
	bar = GL_HScrollBar_Create(window);

	// Configure scroll bar
	GL_Widget_SetMin  (bar, 0);
	GL_Widget_SetMax  (bar, 100);
	GL_Widget_SetValue(bar, 0);
	GL_Widget_SetPage (bar, 1);

	// Registering a callback. This callback will be called every click on the button
	GL_Widget_RegisterCallback(window, GL_EVENT_STYLUS_CLICK, OnClick);

	for (value = 0; value <= 100 && result == GL_RESULT_NONE; value ++)
	{
		// Set the current value
		GL_Widget_SetValue(bar, value);

		// Refreshments and message handling of the window
		result = GL_Window_Dispatch(window, 1);
	}

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
