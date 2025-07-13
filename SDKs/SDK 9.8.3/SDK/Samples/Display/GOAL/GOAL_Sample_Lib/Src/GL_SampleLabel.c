#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnKeyPressed(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}


// Sample of label
void GL_SampleLabel(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET label;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

	// Creating a label 
	label = GL_Label_Create(window);

	// Sets the text "Hello world"
	GL_Widget_SetText(label,"Hello\nworld");

	// Sets the background color
	GL_Widget_SetBackColor(label, GL_COLOR_BLUE);

	// Sets the foreground color
	GL_Widget_SetForeColor(label, GL_COLOR_YELLOW);

	// Registering a callback. This callback will be called every keypress on the keyboard
	GL_Widget_RegisterCallback(window, GL_EVENT_KEY_DOWN, OnKeyPressed);

	// Display window and wait clic on button
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
