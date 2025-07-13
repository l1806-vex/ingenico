#include "GL_GraphicLib.h"
#include "GL_Samples.h"
#include "GL_Wgu.h"

// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnKeyPressed(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}


// Sample of drawing with vectorized mode
void GL_SampleDrawingVectorized(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET drawing;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

		// Registering a callback. This callback will be called every keypress on the keyboard
		GL_Widget_RegisterCallback(window, GL_EVENT_KEY_DOWN, OnKeyPressed);

		// Reduces the size of window
		GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

		// Create a drawing surface
		drawing = GL_Drawing_Create(window);

			// Is used to switch to vectorized mode :
			// this mode provides automatic resizing of designs registered in the drawing, 
			// it allows particularly when orientation of the screen change to redisplay the data and
			// taking into account the new size of the area.
			// WARNING : in this mode all draw commands are kept, if commands are numerous they can saturate the memory.
			GL_Drawing_SetVectorized(drawing, true);

			// Set the background color of the drawing
			GL_Widget_SetBackColor(drawing, GL_COLOR_GRAY);

			// A action to draw an ellipse
			GL_Drawing_SetPen     (drawing, GL_COLOR_BLUE, 1,GL_UNIT_PERCENT);
			GL_Drawing_SetBrush   (drawing, GL_COLOR_YELLOW);
			GL_Drawing_DrawEllipse(drawing, 25, 25, 25, 25, GL_UNIT_PERCENT);

			// A action to draw a rectangle
			GL_Drawing_SetPen     (drawing, GL_COLOR_RED, 1,GL_UNIT_PERCENT);
			GL_Drawing_SetBrush   (drawing, GL_COLOR_ORANGE);
			GL_Drawing_DrawRect   (drawing, 50, 50, 50, 50, GL_UNIT_PERCENT);

			// A action to draw line
			GL_Drawing_SetPen     (drawing, GL_COLOR_BLACK, 1,GL_UNIT_PERCENT);
			GL_Drawing_DrawLine   (drawing, 25,25,75,75,GL_UNIT_PERCENT);

			// A action to draw a text "Hello world"
			GL_Drawing_SetPen     (drawing, GL_COLOR_BLUE, 1,GL_UNIT_PERCENT);
			GL_Drawing_SetFont    (drawing, "GOAL", GL_FONT_STYLE_NORMAL, 10, 10, GL_UNIT_PERCENT);
			GL_Drawing_DrawText   (drawing, 0,0,GL_UNIT_PERTHOUSAND, "Hello world");

			// A action to draw a text "Utf8"
			GL_Drawing_SetPen     (drawing, GL_COLOR_BLUE, 1,GL_UNIT_PERCENT);
			GL_Drawing_SetFont    (drawing, "GOAL", GL_FONT_STYLE_NORMAL, 10, 10, GL_UNIT_PERCENT);
			GL_Drawing_DrawText   (drawing, 0,200,GL_UNIT_PERTHOUSAND, "utf8 : éàßù");
 
	// Refreshments and message handling of the window
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}


