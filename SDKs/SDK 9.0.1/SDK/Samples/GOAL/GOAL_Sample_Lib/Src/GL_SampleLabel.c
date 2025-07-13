#include "GL_GraphicLib.h"
#include "GL_Samples.h"

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

	// Refreshments and message handling of the window
	GL_Window_Dispatch(window, 1000);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
