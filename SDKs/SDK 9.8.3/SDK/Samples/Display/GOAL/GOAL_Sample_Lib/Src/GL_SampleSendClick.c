#include "GL_GraphicLib.h"
#include "GL_Samples.h"



// Callback for processing a timeout message.
// The "message" contains details of the message received by the window
static bool OnTimeout(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);

	// Here we force the value to 0 to release the application of the loop on GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	return true;
}


// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnClick(T_GL_HMESSAGE message)
{
	int counter = 0;

	// Gets the data user attached to the window
	GL_Message_GetUserData(message, &counter, sizeof(counter));

	// Increase the user counter
	counter ++;

	// Sets the data user attached to the window
	GL_Message_SetUserData(message, &counter, sizeof(counter));

	// Changes the text of the button
	GL_Widget_SetText(GL_Message_GetWidget(message), "Click count = %d", counter);
	return true;
}


// Sample of send click
void GL_SampleSendClick(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET button;
	T_GL_HWIDGET timer;
	int counter = 0;
	
	// Creating a blank window
	window = GL_Window_Create(graphicLib);

		// Reduces the size of window
		GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

		// Sets the position of window
		GL_Widget_SetPosition(window, 0, 0, GL_UNIT_PERCENT);

		// Attaches the user data "counter" to the window
		GL_Widget_SetUserData(window, &counter, sizeof(counter));

		// Creating a timer
		timer = GL_Timer_Create(window);

			// Set interval to 1s, timer is automatically started 
			GL_Timer_SetInterval(timer, 1000);

			// Registering a callback. This callback will be called every second
			GL_Widget_RegisterCallback(timer, GL_EVENT_TIMER_OUT, OnTimeout);

		// Creating a button 
		button = GL_Button_Create(window);

			// Sets the background color of the button
			GL_Widget_SetBackColor(button, GL_COLOR_AQUA);

			// Prohibits the extension of the button
			GL_Widget_SetGrow(button, GL_DIRECTION_NONE);

			// Registering a callback. This callback will be called every click on the button
			GL_Widget_RegisterCallback(window, GL_EVENT_STYLUS_CLICK, OnClick);

			// Simulates a key pres on a graphic lib
			GL_GraphicLib_SendClick(graphicLib, 50, 50, GL_UNIT_PERCENT);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

		// Simulates a key press on a window
		GL_Window_SendClick(window, 50, 50, GL_UNIT_PERCENT);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
