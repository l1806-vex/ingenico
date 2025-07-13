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

// Sample of scroll view
void GL_SampleScrollView(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET scrollviewLayout;
	T_GL_HWIDGET button;
	T_GL_HWIDGET hscrollbar;
	T_GL_HWIDGET vscrollbar;
	T_GL_HWIDGET scrollview;
	T_GL_HWIDGET windowLayout;
	T_GL_DIM     row;
	T_GL_DIM     column;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

	// Creating the layout for the window
	windowLayout = GL_Layout_Create(window);

	// Creation of the horizontal scroll bar
	hscrollbar = GL_HScrollBar_Create(windowLayout);

	// Positioning the scroll bar in the window layout
	GL_Widget_SetItem(hscrollbar, 0, 1);

	// Creation of the vertical scroll bar
	vscrollbar = GL_VScrollBar_Create(windowLayout);

	// Positioning the scroll bar the window layout 
	GL_Widget_SetItem(vscrollbar, 1, 0);

	// Create view scrolled
	scrollview = GL_ScrollView_Create(windowLayout);

	// Positioning the scroll view in the window layout
	GL_Widget_SetItem(scrollview, 0, 0);

	// Attachs the view scrolled with scrollbars
	GL_ScrollView_AttachScrollbar(scrollview,hscrollbar,vscrollbar);

	// Registering a callback. This callback will be called every click on the button
	GL_Widget_RegisterCallback(window, GL_EVENT_STYLUS_CLICK, OnClick);

	// CONTENT OF SCROLL VIEW
	// Creating a layout with 5 columns and 5 rows
	scrollviewLayout = GL_Layout_Create(scrollview);

	// For all rows of the layout
	for (row = 0; row < 8; row++)
	{
		// For all columns of the layout
		for (column = 0; column < 5; column++)
		{
			char text[256];

			// Creates and attaches a label to the layout
			button = GL_Button_Create(scrollviewLayout);

			// Sets the label location in the layout
			GL_Widget_SetItem(button, column, row);

			// Sets the label text
			sprintf(text, " %d : %d ", column, row);
			GL_Widget_SetText(button, text);
		}
	}

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);
	
	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
