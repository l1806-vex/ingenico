#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Identifier to retrieve the scroll view
#define GL_SAMPLE_SCROLLVIEW_ID 1


// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnKeyDown(T_GL_HMESSAGE message)
{
	T_GL_HWIDGET scrollview;

	// According the key pressed
	switch (GL_Message_GetKey(message))
	{
	// Previous key pressed
	case GL_VIRTUAL_KEY_PREVIOUS:
		// Search for the scrolled in the window
		scrollview = GL_Message_GetWidgetById(message, GL_SAMPLE_SCROLLVIEW_ID);

		// Moves to the text of the previous page
		GL_ScrollView_Move(scrollview, 0, GL_ScrollView_GetVerticalRange(scrollview).value-GL_ScrollView_GetVerticalRange(scrollview).page);
		break;

	// Next key pressed
	case GL_VIRTUAL_KEY_NEXT:
		// Search for the scrolled in the window
		scrollview = GL_Message_GetWidgetById(message, GL_SAMPLE_SCROLLVIEW_ID);

		// Moves to the text of the next page
		GL_ScrollView_Move(scrollview, 0, GL_ScrollView_GetVerticalRange(scrollview).value+GL_ScrollView_GetVerticalRange(scrollview).page);
		break;

	// Other keys : exit the window
	default:
		// Here we force the value to 0 to release the application of the loop on @ref GL_Window_MainLoop,
		// this assignment is an example and may be replaced by a more complete treatment 
		GL_Message_SetResult(message, 0);
		break;
	}
	
	return true;
}


// Sample of scroll text
void GL_SampleScrollText(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET scrollviewLayout;
	T_GL_HWIDGET label;
	T_GL_HWIDGET vscrollbar;
	T_GL_HWIDGET scrollview;
	T_GL_HWIDGET windowLayout;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 100, 100, GL_UNIT_PERCENT);

	// Creating the layout for the window
	windowLayout = GL_Layout_Create(window);

	// Creation of the vertical scroll bar
	vscrollbar = GL_VScrollBar_Create(windowLayout);

	// Positioning the scroll bar the window layout 
	GL_Widget_SetItem(vscrollbar, 1, 0);

	// Create view scrolled
	scrollview = GL_ScrollView_Create(windowLayout);

	// Positioning the scroll view in the window layout
	GL_Widget_SetItem(scrollview, 0, 0);

	// Indicates the identifier of the view scrolled
	GL_Widget_SetId(scrollview, GL_SAMPLE_SCROLLVIEW_ID);

	// Attachs the view scrolled with scrollbars
	GL_ScrollView_AttachScrollbar(scrollview,0,vscrollbar);

	// Registering a callback. This callback will be called every key pressed
	GL_Widget_RegisterCallback(window, GL_EVENT_KEY_DOWN, OnKeyDown);

	// Creating a layout with 5 columns and 5 rows
	scrollviewLayout = GL_Layout_Create(scrollview);

	// Add a label in a scroll view
	label = GL_Label_Create(scrollviewLayout);

	// Load the label with a long text
	GL_Widget_SetText(label, 
			"Lorem ipsum dolor sit amet, consectetuer adipiscing elit. "
			"Pellentesque suscipit accumsan massa. "
			"Nullam sapien mauris, venenatis at, fermentum at, tempus eu, urna. "
			"Sed a lorem ut est tincidunt consectetuer. Aliquam vel nibh. "
			"Suspendisse fermentum. Donec nonummy lacinia leo. "
			"Aenean scelerisque metus eget sem. Nam malesuada sapien eu nibh. Curabitur accumsan felis in erat. "
			"Pellentesque sit amet dui vel justo gravida auctor. Suspendisse potenti. "
			"Phasellus nisi metus, tempus sit amet, ultrices ac, porta nec, felis. Integer accumsan. "
			"Curabitur risus urna, placerat et, luctus pulvinar, auctor vel, orci. Fusce venenatis ligula in pede");

	// Align the text to the left side
	GL_Widget_SetTextAlign(label, GL_ALIGN_LEFT);

	// The wrap allows text to automatically return to the line if it does not fit in width in the space allocated to it.
	GL_Widget_SetWrap(label, true);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnKeyDown
	GL_Window_MainLoop(window);
	
	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
