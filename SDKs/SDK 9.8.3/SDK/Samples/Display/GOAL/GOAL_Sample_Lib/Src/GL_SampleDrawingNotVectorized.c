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


/** Context for the drawing */
typedef struct T_GL_SAMPLE_DRAWING_CONTEXT
{
	T_GL_COORD x;           ///< x coordinate of the image in drawing
	T_GL_COORD y;           ///< y coordinate of the image in drawing
	T_GL_WGU_HEADER header; ///< Image header
} T_GL_SAMPLE_DRAWING_CONTEXT;

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
	T_GL_SAMPLE_DRAWING_CONTEXT * ptContext;
	T_GL_HWIDGET drawing;

	// Gets the pointer to the data context
	GL_Message_GetUserData(message, &ptContext, sizeof(ptContext));

	// Gets the drawing handle
	drawing = GL_Message_GetWidgetById(message, 0);

	// Erase the drawing before to display the part of image
	GL_Drawing_Clear(drawing);

	// Draw an image part in a drawing
	// IMPORTANT : The GL_Drawing_DrawArea writes data directly in the drawing, 
	// the drawing widget is completly created after an initial call to GL_Window_Dispatch.
	// All data written before the first call to GL_Window_Dispatch will be lost.
	GL_Drawing_DrawArea(drawing, 
		(T_GL_COORD)ptContext->x,  (T_GL_COORD)ptContext->y,                    // Coordinates of the top left corner in the drawing
		(T_GL_DIM)ptContext->header.width, (T_GL_DIM)ptContext->header.height,  // Size of rectangle in the drawing
		GL_Image_Content,                                                       // Image pixmap data
		(T_GL_COORD)ptContext->x,  (T_GL_COORD)ptContext->y,                    // Coordinates of the rectangle in the image
		(T_GL_DIM)ptContext->header.width, (T_GL_DIM)ptContext->header.height); // Size of image
	ptContext->x += 2;
	ptContext->y += 2;

	// If the image is out of space
	if ((long)ptContext->x > (long)ptContext->header.width || (long)ptContext->y > (long)ptContext->header.height)
	{
		ptContext->x = -(T_GL_COORD)ptContext->header.width;
		ptContext->y = -(T_GL_COORD)ptContext->header.height;
	}
	return true;
}


// Sample of drawing with not vectorized mode
void GL_SampleDrawingNotVectorized(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET drawing;
	T_GL_HWIDGET timer;
	T_GL_SAMPLE_DRAWING_CONTEXT context;
	T_GL_SAMPLE_DRAWING_CONTEXT * ptContext;
	
	memset(&context, 0, sizeof(context));

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

		// Creating a timer to move image
		timer = GL_Timer_Create(window);

		// Set interval to 1s, timer is automatically started 
		GL_Timer_SetInterval(timer, 100);

		// Registering a callback. This callback will be called every second
		GL_Widget_RegisterCallback(timer, GL_EVENT_TIMER_OUT, OnTimeout);

		// Registering a callback. This callback will be called every keypress on the keyboard
		GL_Widget_RegisterCallback(window, GL_EVENT_KEY_DOWN, OnKeyPressed);

		// Reduces the size of window
		GL_Widget_SetSize(window, 100, 100, GL_UNIT_PERCENT);

		// Create a drawing surface
		drawing = GL_Drawing_Create(window);

			// Set the id to drawing
			GL_Widget_SetId(drawing, 0);

			// Set the background color of the drawing
			GL_Widget_SetBackColor(drawing, GL_COLOR_GRAY);

			// Read a raw image
			GL_Sample_GetImage(drawing, &context.header);


		// Attach the pointer of the context to the window
		ptContext = &context;
		GL_Widget_SetUserData(window, &ptContext, sizeof(ptContext));

	// Refreshments and message handling of the window
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
