#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnClick(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}


// Sample of stretching buttons
void GL_SampleButtonStretch(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET button;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Creating a button that expands in a layout cell
	button = GL_Button_Create(window);
		// Set text button
		GL_Widget_SetText(button,"Expand");
	
		// Expands in all direction
		GL_Widget_SetExpand(button, GL_DIRECTION_ALL);
	
		// Sets margins arround button
		GL_Widget_SetMargins(button, 5, 5, 5, 5, GL_UNIT_PIXEL);

	// Extension of a button using a minimum size
	button = GL_Button_Create(window);
		// Set text button
		GL_Widget_SetText(button,"Minsize");
	
		// Sets margins arround button
		GL_Widget_SetMinSize(button, 100, 100, GL_UNIT_PIXEL);

		// Place in the bottom right corner
		GL_Widget_SetBackAlign(button, GL_ALIGN_BOTTOM_RIGHT);

	// Extension of a button by placing content on multiple lines
	button = GL_Button_Create(window);
		// Set text button
		GL_Widget_SetText(button,"Multi\nLines\nButton");
	
		// Place in the top left corner
		GL_Widget_SetBackAlign(button, GL_ALIGN_TOP_LEFT);

	// Size reduction of a button by decreasing the font size
	button = GL_Button_Create(window);
		// Set text button
		GL_Widget_SetText(button,"Small font");
	
		// Place in the top left corner
		GL_Widget_SetBackAlign(button, GL_ALIGN_TOP_RIGHT);

		// Change the font size
		GL_Widget_SetFontScale(button, GL_SCALE_XXSMALL);
	
	// Registering a callback. This callback will be called every click on the button
	GL_Widget_RegisterCallback(window, GL_EVENT_STYLUS_CLICK, OnClick);

	// Display window and wait clic on button
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
