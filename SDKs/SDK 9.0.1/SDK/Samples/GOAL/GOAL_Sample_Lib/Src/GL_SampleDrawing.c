#include "GL_GraphicLib.h"
#include "GL_Samples.h"
#include "GL_Wgu.h"

// Buffer that will receive data from the image (it is better to dynamically allocate)
static char GL_Image_Content[32767];

// Gets an image
static void GL_Sample_GetImage(T_GL_HWIDGET drawing, T_GL_WGU_HEADER * header)
{
	// Depending on the format of pixels supported by the screen then the images files will be different
	const char * filenames[] =
	{
		"file://flash/HOST/TU.TAR/wgusuite/punaise8.wgu",
		"file://flash/HOST/TU.TAR/wgusuite/punaise16.wgu",
		"file://flash/HOST/TU.TAR/wgusuite/punaise32.wgu",
	};

	// Gets the encoding format of pixels
	T_GL_PIXEL_TYPE pixelType = GL_Drawing_GetPixelType(drawing);

	// If the format is supported
	if (pixelType <= GL_PIXEL_TYPE_ARGB8888)
	{
		// Gets the size of the image
		long imageSize = GL_File_GetSizeFilename(filenames[pixelType]);

		// If the reserved buffer size is sufficient
		if (imageSize > sizeof(T_GL_WGU_HEADER) && imageSize <= (sizeof(T_GL_WGU_HEADER) + sizeof(GL_Image_Content)))
		{
			T_GL_HFILE file;

			// Calculates the data size of the image (without the header)
			imageSize -= sizeof(T_GL_WGU_HEADER);

			// Open the image file
			file = GL_File_Open(filenames[pixelType], GL_FILE_OPEN_EXISTING, GL_FILE_ACCESS_READ);

			// If the file is opened
			if (file)
			{
				// Read the header data
				GL_File_Read(file, header, sizeof(*header));

				// Read the image content
				GL_File_Read(file, &GL_Image_Content, imageSize);

				// Close the image file
				GL_File_Close(file);
			}
		}
	}
}


// Callback for processing a timeout message.
// The "message" contains details of the message received by the window
static bool OnTimeout(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);

	// Stop the timer
	GL_Timer_Stop(GL_Message_GetWidget(message));

	// Here we force the value to 0 to release the application of the loop on GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	return true;
}


// Sample of drawing
void GL_SampleDrawing(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET drawing;
	T_GL_WGU_HEADER imageHeader;
	T_GL_HWIDGET timer;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Creating a timer (To exit the window automatically after a period)
	timer = GL_Timer_Create(window);

	// Set interval to 1s, timer is automatically started 
	GL_Timer_SetInterval(timer, 1000);

	// Registering a callback. This callback will be called every second
	GL_Widget_RegisterCallback(timer, GL_EVENT_TIMER_OUT, OnTimeout);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

	// Create a drawing surface
	drawing = GL_Drawing_Create(window);

	// Set the background color of the drawing
	GL_Widget_SetBackColor(drawing, GL_COLOR_GRAY);

	// A action to draw an ellipse
	GL_Drawing_SetPen(drawing, GL_COLOR_BLUE, 1,GL_UNIT_PERCENT);
	GL_Drawing_SetBrush(drawing, GL_COLOR_YELLOW);
	GL_Drawing_DrawEllipse(drawing, 25, 25, 25, 25, GL_UNIT_PERCENT);

	// A action to draw a rectangle
	GL_Drawing_SetPen(drawing, GL_COLOR_RED, 1,GL_UNIT_PERCENT);
	GL_Drawing_SetBrush(drawing, GL_COLOR_ORANGE);
	GL_Drawing_DrawRect(drawing, 50, 50, 50, 50, GL_UNIT_PERCENT);

	// A action to draw line
	GL_Drawing_SetPen(drawing, GL_COLOR_BLACK, 1,GL_UNIT_PERCENT);
	GL_Drawing_DrawLine(drawing, 25,25,75,75,GL_UNIT_PERCENT);

	// A action to draw a text "Hello world"
	GL_Drawing_SetPen(drawing, GL_COLOR_BLUE, 1,GL_UNIT_PERCENT);
	GL_Drawing_SetFont(drawing, "arial", GL_FONT_STYLE_NORMAL, 30, 30, GL_UNIT_PERCENT);
	GL_Drawing_DrawText(drawing, 0,200,GL_UNIT_PERTHOUSAND, "Hello world");

	// Read a raw image
	GL_Sample_GetImage(drawing, &imageHeader);

	// Refreshments and message handling of the window (this call is IMPORTANT before to use GL_Drawing_DrawArea)
	GL_Window_Dispatch(window, 0);

	// Draw an image part in a drawing
	// IMPORTANT : The GL_Drawing_DrawArea writes data directly in the drawing, 
	// the drawing widget is completly created after an initial call to GL_Window_Dispatch.
	// All data written before the first call to GL_Window_Dispatch will be lost.
	GL_Drawing_DrawArea(drawing, 
		5,  55,           // Coordinates of the top left corner in the drawing
		60, 60,           // Size of rectangle in the drawing
		GL_Image_Content, // Image pixmap data
		10, 10,           // Coordinates of the rectangle in the image
		(T_GL_DIM)imageHeader.width, (T_GL_DIM)imageHeader.height); // Size of image

	// Refreshments and message handling of the window
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);

}
