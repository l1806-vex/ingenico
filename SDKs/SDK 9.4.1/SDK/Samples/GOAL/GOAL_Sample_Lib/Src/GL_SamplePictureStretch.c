#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnKeyPressed(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}


// Sample of stretch picture
void GL_SamplePictureStretch(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET picture;
	T_GL_HWIDGET layout;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Create main layout
	layout = GL_Layout_Create(window);
		
		// Create top left image of frame
		picture = GL_Picture_Create(layout);

			// Sets the position in layout on the top left corner
			GL_Widget_SetItem(picture, 0, 0);

			// Sets source filename
			GL_Widget_SetSource(picture, "file://flash/HOST/TU.TAR/bmpsuite/FrameTopLeft.BMP");

			// Disable the grow of layout cell
			GL_Widget_SetGrow(picture, GL_DIRECTION_NONE);

		// Create top image of frame
		picture = GL_Picture_Create(layout);

			// Sets the position in layout on the top border
			GL_Widget_SetItem(picture, 1, 0);

			// Sets source filename
			GL_Widget_SetSource(picture, "file://flash/HOST/TU.TAR/bmpsuite/FrameTop.BMP");

			// Enable the grow of cell in width
			GL_Widget_SetGrow(picture, GL_DIRECTION_WIDTH);

			// Enable the expansion of widget in width
			GL_Widget_SetExpand(picture, GL_DIRECTION_WIDTH);

			// Repeat this image according to x coordinate and stretch according to y coordinate
			GL_Widget_SetTransformation(picture, GL_TRANSFORMATION_REPEAT_X_STRETCH_Y);

		// Create top right image of frame
		picture = GL_Picture_Create(layout);

			// Sets the position in layout on the top right corner
			GL_Widget_SetItem(picture, 2, 0);

			// Sets source filename
			GL_Widget_SetSource(picture, "file://flash/HOST/TU.TAR/bmpsuite/FrameTopRight.BMP");

			// Disable the grow of layout cell
			GL_Widget_SetGrow(picture, GL_DIRECTION_NONE);

		// Create left border image of frame
		picture = GL_Picture_Create(layout);

			// Sets the position in layout on the left border
			GL_Widget_SetItem(picture, 0, 1);

			// Sets source filename
			GL_Widget_SetSource(picture, "file://flash/HOST/TU.TAR/bmpsuite/FrameLeft.BMP");

			// Enable the grow of cell in height
			GL_Widget_SetGrow(picture, GL_DIRECTION_HEIGHT);

			// Enable the expansion of widget in height
			GL_Widget_SetExpand(picture, GL_DIRECTION_HEIGHT);

			// Repeat this image according to y coordinate and stretch according to x coordinate
			GL_Widget_SetTransformation(picture, GL_TRANSFORMATION_REPEAT_Y_STRETCH_X);

		// Create the central image
		picture = GL_Picture_Create(layout);

			// Sets the position in layout in the middle
			GL_Widget_SetItem(picture, 1, 1);

			// Sets source filename
			GL_Widget_SetSource(picture, "file://flash/HOST/TU.TAR/jpgsuite/fruit.jpg");

			// Enable the grow of cell in all direction
			GL_Widget_SetGrow(picture, GL_DIRECTION_ALL);

			// Enable the expansion of widget in all direction
			GL_Widget_SetExpand(picture, GL_DIRECTION_ALL);

			// Repeat this image according to x and y coordinates
			GL_Widget_SetTransformation(picture, GL_TRANSFORMATION_REPEAT_ALL);

		// Create right border image of frame
		picture = GL_Picture_Create(layout);

			// Sets the position in layout in the left
			GL_Widget_SetItem(picture, 2, 1);

			// Sets source filename
			GL_Widget_SetSource(picture, "file://flash/HOST/TU.TAR/bmpsuite/FrameRight.BMP");

			// Enable the grow of cell in height
			GL_Widget_SetGrow(picture, GL_DIRECTION_HEIGHT);

			// Enable the expansion of widget in height
			GL_Widget_SetExpand(picture, GL_DIRECTION_HEIGHT);

			// Repeat this image according to y coordinate and stretch according to x coordinate
			GL_Widget_SetTransformation(picture, GL_TRANSFORMATION_REPEAT_Y_STRETCH_X);


		// Create bottom left corner image of frame
		picture = GL_Picture_Create(layout);

			// Sets the position in layout in the bottom left 
			GL_Widget_SetItem(picture, 0, 2);

			// Sets source filename
			GL_Widget_SetSource(picture, "file://flash/HOST/TU.TAR/bmpsuite/FrameBottomLeft.BMP");

			// Disable the grow of layout cell
			GL_Widget_SetGrow(picture, GL_DIRECTION_NONE);


		// Create bottom image of frame
		picture = GL_Picture_Create(layout);

			// Sets the position in layout on the bottom border
			GL_Widget_SetItem(picture, 1, 2);

			// Sets source filename
			GL_Widget_SetSource(picture, "file://flash/HOST/TU.TAR/bmpsuite/FrameBottom.BMP");

			// Enable the grow of cell in width
			GL_Widget_SetGrow(picture, GL_DIRECTION_WIDTH);

			// Enable the expansion of widget in width
			GL_Widget_SetExpand(picture, GL_DIRECTION_WIDTH);

			// Repeat this image according to x coordinate and stretch according to y coordinate
			GL_Widget_SetTransformation(picture, GL_TRANSFORMATION_REPEAT_X_STRETCH_Y);


		// Create bottom right image of frame
		picture = GL_Picture_Create(layout);

			// Sets the position in layout on the bottom right corner
			GL_Widget_SetItem(picture, 2, 2);

			// Sets source filename
			GL_Widget_SetSource(picture, "file://flash/HOST/TU.TAR/bmpsuite/FrameBottomRight.BMP");

			// Disable the grow of layout cell
			GL_Widget_SetGrow(picture, GL_DIRECTION_NONE);

	// Registering a callback. This callback will be called every keypress on the keyboard
	GL_Widget_RegisterCallback(window, GL_EVENT_KEY_DOWN, OnKeyPressed);

	// Display window and wait clic on button
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
