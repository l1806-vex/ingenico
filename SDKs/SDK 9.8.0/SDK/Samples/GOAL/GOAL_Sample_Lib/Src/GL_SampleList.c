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

// Sample of list
void GL_SampleList(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET list;
	T_GL_HWIDGET widget;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 80, 80, GL_UNIT_PERCENT);

	// Creating a list
	list = GL_List_Create(window);

		// Adds a label and an edit to enter the name
		widget = GL_Label_Create(list);
		GL_Widget_SetText(widget,"Name");

		widget = GL_Edit_Create(list);
		GL_Widget_SetMask(widget,"/a/a/a/a/a/a/a/a/a/a");

		// Adds a label and an edit to enter the age
		widget = GL_Label_Create(list);
		GL_Widget_SetText(widget,"Age");

		widget = GL_Edit_Create(list);
		GL_Widget_SetMask(widget,"/d/d/d years");

		// Adds two radio buttons to select the sex
		widget = GL_RadioButton_Create(list);
		GL_Widget_SetText(widget,"male");
		GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);

		widget = GL_RadioButton_Create(list);
		GL_Widget_SetText(widget,"female");
		GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);

		// Adds check button to select the marital status
		widget = GL_CheckButton_Create(list);
		GL_Widget_SetText(widget,"married");
		GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);

		// Adds quit button
		widget = GL_Button_Create(list);
		GL_Widget_SetText(widget,"quit");
		GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
		GL_Widget_SetShortcut(widget,  GL_KEY_VALID);

	// Registering a callback. This callback will be called every click on the button
	GL_Widget_RegisterCallback(widget, GL_EVENT_STYLUS_CLICK, OnClick);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
