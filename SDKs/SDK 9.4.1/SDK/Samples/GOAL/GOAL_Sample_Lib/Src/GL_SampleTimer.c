#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Callback for processing a timeout message.
// The "message" contains details of the message received by the window
static bool OnTimeout(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);

	// Stop the timer
	GL_Timer_Stop(GL_Message_GetWidget(message));

	// Here we force the value to 0 to release the application of the loop on GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	return true;
}


// Sample of timer
void GL_SampleTimer(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET timer;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

	// Creating a timer
	timer = GL_Timer_Create(window);

	// Set interval to 1s, timer is automatically started 
	GL_Timer_SetInterval(timer, 1000);

	// Registering a callback. This callback will be called every second
	GL_Widget_RegisterCallback(timer, GL_EVENT_TIMER_OUT, OnTimeout);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
