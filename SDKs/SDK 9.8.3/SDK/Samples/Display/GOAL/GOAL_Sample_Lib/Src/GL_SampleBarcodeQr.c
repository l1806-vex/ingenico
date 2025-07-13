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


// Create the barcode
static T_GL_HWIDGET CreateBarcode(T_GL_HWIDGET parent)
{
	T_GL_HWIDGET barcode;

	barcode = GL_Barcode_Create(parent);

	// Set the mime type of barcode
	GL_Barcode_SetMimeType(barcode, GL_MIME_BARCODE_QR);

	// Set the value of barcode
	GL_Barcode_SetValue(barcode, "Hello world from qr", strlen("Hello world from qr") + 1);

	// Configure the margin of QR
	GL_Barcode_SetParamInteger(barcode, GL_BARCODE_QR_MARGIN, 2);

	// Fit the barcode to the screen
	GL_Widget_SetTransformation(barcode, GL_TRANSFORMATION_FIT_ALL);

	return barcode;
}


// sample function to display a barcode ean 8
static void BarcodeOnScreen(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 100, 100, GL_UNIT_PERCENT);

	// Create a barcode on the screen
	CreateBarcode(window);

	// Registering a callback. This callback will be called every keypress on the keyboard
	GL_Widget_RegisterCallback(window, GL_EVENT_KEY_DOWN, OnKeyPressed);

	// Display window and wait clic on button
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory,
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}


// sample function to print a barcode ean 8
static void BarcodeOnPrinter(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET document;
	T_GL_HWIDGET layout;
	T_GL_HWIDGET barcode;

	// Creating a document intended for print
	document = GL_Document_Create(graphicLib);

	// Creating a layout in document is required to use the alignments to the right and left of the text
	layout = GL_Layout_Create(document);

	// Adds a barcode in the layout
	barcode = CreateBarcode(layout);

	// IMPORTANT : Sets the mininal size of the barcode
	GL_Widget_SetMinSize(barcode, 200, 200, GL_UNIT_PIXEL);

	// Receipt print
	GL_Document_Print(document, 0);

	// Destroy the document
	GL_Widget_Destroy(document);
}


// Sample of barcode
void GL_SampleBarcodeQr(T_GL_HGRAPHIC_LIB graphicLib)
{

	// Function to print a barcode
	BarcodeOnPrinter(graphicLib);

	// Function to display a barcode
	BarcodeOnScreen(graphicLib);

}
