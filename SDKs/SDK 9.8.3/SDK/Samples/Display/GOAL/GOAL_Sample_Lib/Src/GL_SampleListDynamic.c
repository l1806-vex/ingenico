#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Identifier to found the list
#define ID_LIST 0


// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnQuit(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}


// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnAdd(T_GL_HMESSAGE message)
{
	T_GL_HWIDGET list = GL_Message_GetWidgetById(message, ID_LIST);
	T_GL_HWIDGET label = GL_Label_Create(list);
	GL_Widget_SetText(label, "Hello");
	return true;
}


// Sample of list of dynamic items
void GL_SampleListDynamic(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET list;
	T_GL_HWIDGET button;
	T_GL_HWIDGET layout;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Create main layout
	layout = GL_Layout_Create(window);

		// Creating a list
		list = GL_List_Create(layout);

			// Set id of the list
			GL_Widget_SetId(list, ID_LIST);
			
			// Locate the list in the main layout
			GL_Widget_SetItem(list, 0, 0);

		// Add button
		button = GL_Button_Create(layout);

			// Set text of button
			GL_Widget_SetText(button, "Add");

			// Locate the list in the main layout
			GL_Widget_SetItem(button, 0, 1);

			// Registering a callback. This callback will be called every click on the button
			GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnAdd);

			// Expand button on width only
			GL_Widget_SetGrow(button, GL_DIRECTION_WIDTH);
			GL_Widget_SetExpand(button, GL_DIRECTION_WIDTH);


		// Quit button
		button = GL_Button_Create(layout);

			// Set text of button
			GL_Widget_SetText(button, "Quit");

			// Locate the list in the main layout
			GL_Widget_SetItem(button, 0, 2);

			// Registering a callback. This callback will be called every click on the button
			GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnQuit);

			// Valid to quit
			GL_Widget_SetShortcut(button,  GL_KEY_VALID);

			// Expand button on width only
			GL_Widget_SetGrow(button, GL_DIRECTION_WIDTH);
			GL_Widget_SetExpand(button, GL_DIRECTION_WIDTH);


	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
