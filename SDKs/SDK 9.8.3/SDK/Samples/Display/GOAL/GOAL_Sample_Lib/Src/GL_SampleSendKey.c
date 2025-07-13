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

// Sample of send key
void GL_SampleSendKey(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET edit;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

	// Creating a edit 
	edit = GL_Edit_Create(window);

	// Enlarged the size of the edit field (If the field is created empty it is sized very small)
	GL_Widget_SetExpand(edit, GL_DIRECTION_WIDTH);

	// Registering a callback. This callback will be called every click on the button
	GL_Widget_RegisterCallback(window, GL_EVENT_STYLUS_CLICK, OnClick);

	// Simulates a key pres on a graphic lib (ATTENTION: Only one window receives key press events, it is always the window that has focus.)
	GL_GraphicLib_SendKey(graphicLib, '4');
	GL_GraphicLib_SendKey(graphicLib, '5');
	GL_GraphicLib_SendKey(graphicLib, '6');
	GL_GraphicLib_SendKey(graphicLib, '7');

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	// Simulates a key press on a window
	// IMPORTANT: this function should always be called after a first call to GL_Window_Dispatch, 
	// because the creation of the window is effective only after the first dispatch or a mainloop.
	GL_Window_SendKey(window, '0');
	GL_Window_SendKey(window, '1');
	GL_Window_SendKey(window, '2');
	GL_Window_SendKey(window, '3');

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}


