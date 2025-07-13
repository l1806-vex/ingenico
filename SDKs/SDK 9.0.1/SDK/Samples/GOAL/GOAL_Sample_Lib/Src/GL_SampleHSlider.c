#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Callback for processing a slider changed
static bool OnSliderChange(T_GL_HMESSAGE message)
{
	(void)(message);
	return true;
}

// Sample of horizontal slider
void GL_SampleHSlider(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET slider;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

	// Creating a slider
	slider = GL_HSlider_Create(window);

	// Configure slider
	GL_Widget_SetMin  (slider, 0);
	GL_Widget_SetMax  (slider, 100);
	GL_Widget_SetValue(slider, 0);
	GL_Widget_SetStep (slider, 10);

	// Registering a callback on uncheck
	GL_Widget_RegisterCallback(slider, GL_EVENT_HORIZONTAL_SCROLL, OnSliderChange);


	// When the maximum value is reached it exit of the loop
	while(GL_Widget_GetValue(slider) < 50)
	{
		// Refreshments and message handling of the window
		GL_Window_Dispatch(window, 1);
	}

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);

}
