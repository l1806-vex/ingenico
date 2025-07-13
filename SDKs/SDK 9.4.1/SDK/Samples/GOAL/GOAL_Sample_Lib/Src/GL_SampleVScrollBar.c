#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of vertical scroll bar
void GL_SampleVScrollBar(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET bar;
	T_GL_COORD   value;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

	// Creating a scroll bar
	bar = GL_VScrollBar_Create(window);

	// Configure scroll bar
	GL_Widget_SetMin  (bar, 0);
	GL_Widget_SetMax  (bar, 100);
	GL_Widget_SetValue(bar, 0);
	GL_Widget_SetPage (bar, 1);

	for (value = 0; value <= 100; value ++)
	{
		// Set the current value
		GL_Widget_SetValue(bar, value);

		// Refreshments and message handling of the window
		GL_Window_Dispatch(window, 1);
	}

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
