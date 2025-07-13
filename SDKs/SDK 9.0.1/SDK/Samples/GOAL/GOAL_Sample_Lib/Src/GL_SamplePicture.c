#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Sample of picture
void GL_SamplePicture(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET picture;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

	// Creating a picture
	picture = GL_Picture_Create(window);

	// Set the image source
	GL_Widget_SetSource(picture, "file://flash/HOST/TU.TAR/icones/11.png");

	// Refreshments and message handling of the window
	GL_Window_Dispatch(window, 1000);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
