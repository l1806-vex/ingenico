#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of layout
void GL_SampleLayout(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET layout;
	T_GL_HWIDGET label;
	T_GL_DIM     row;
	T_GL_DIM     column;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

	// Creating a layout
	layout = GL_Layout_Create(window);

	// For all rows of the layout
	for (row = 0; row < 4; row++)
	{
		// For all columns of the layout
		for (column = 0; column < 5; column++)
		{
			char text[256];

			// Creates and attaches a label to the layout
			label = GL_Label_Create(layout);

			// Sets the label location in the layout
			GL_Widget_SetItem(label, column, row);

			// Sets the label text
			sprintf(text, "%d:%d", column, row);
			GL_Widget_SetText(label, text);
		}
	}

	// Refreshments and message handling of the window
	GL_Window_Dispatch(window, 1000);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}

