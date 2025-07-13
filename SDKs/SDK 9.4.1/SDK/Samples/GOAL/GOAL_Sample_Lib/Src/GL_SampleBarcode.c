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


// Sample of barcode
void GL_SampleBarcode(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET barcode;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 100, 100, GL_UNIT_PERCENT);

	// Creating a barcode
	barcode = GL_Barcode_Create(window);

	// Set the mime type of barcode
	GL_Barcode_SetMimeType(barcode, GL_MIME_BARCODE_QR);

	// Set the value of barcode
	GL_Barcode_SetValue(barcode, "Hello world", strlen("Hello world") + 1);

	// Configure the margin of QR
	GL_Barcode_SetParamInteger(barcode, GL_BARCODE_QR_MARGIN, 2);

	// Fit the barcode to the screen
	GL_Widget_SetTransformation(barcode, GL_TRANSFORMATION_FIT_ALL);

	// Registering a callback. This callback will be called every keypress on the keyboard
	GL_Widget_RegisterCallback(window, GL_EVENT_KEY_DOWN, OnKeyPressed);

	// Display window and wait clic on button
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
