#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnCancel(T_GL_HMESSAGE message)
{
	// Here we force the result to cancel key value
	GL_Message_SetResult(message, GL_KEY_CANCEL);
	return true;
}

// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnValid(T_GL_HMESSAGE message)
{
	// Here we force the result to valid key value
	GL_Message_SetResult(message, GL_KEY_VALID);
	return true;
}

// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnCorrection(T_GL_HMESSAGE message)
{
	// Here we force the result to correction key value
	GL_Message_SetResult(message, GL_KEY_CORRECTION);
	return true;
}

// Sample of button with a skin icon on top
void GL_SampleButtonWithSkinedIcon(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET button;
	T_GL_HWIDGET layout;
	ulong result;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);
	
	// Create main layout
	layout = GL_Layout_Create(window);

	// Creating a button with icon cancel
	button = GL_Button_Create(layout);
	
		// Sets the cancel skined image
		GL_Widget_SetSource(button, "skin://images/cancel.wgu");
		
		// Locates the button in the layout
		GL_Widget_SetItem(button, 0, 0);

		// Register shortcut to cancel key
		GL_Widget_SetShortcut(button, GL_KEY_CANCEL);

		// Registering a callback. This callback will be called every click on the button
		GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnCancel);

	// Creating a button with icon correction
	button = GL_Button_Create(layout);
	
		// Sets the correction skined image
		GL_Widget_SetSource(button, "skin://images/correction.wgu");
		
		// Locates the button in the layout
		GL_Widget_SetItem(button, 0, 1);

		// Register shortcut to correction key
		GL_Widget_SetShortcut(button, GL_KEY_CORRECTION);

		// Registering a callback. This callback will be called every click on the button
		GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnCorrection);
		
	// Creating a button with icon correction
	button = GL_Button_Create(layout);
	
		// Sets the correction skined image
		GL_Widget_SetSource(button, "skin://images/validation.wgu");
		
		// Locates the button in the layout
		GL_Widget_SetItem(button, 0, 2);

		// Register shortcut to valid key
		GL_Widget_SetShortcut(button, GL_KEY_VALID);

		// Registering a callback. This callback will be called every click on the button
		GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnValid);
	
	// Display window and wait clic on any button
	result = GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
