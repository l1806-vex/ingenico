#include "GL_GraphicLib.h"
#include "GL_Samples.h"
#define SIGNATURE_ID 1


// Callback to clear signature
static bool OnClear(T_GL_HMESSAGE message)
{
	// Search widget signature on the window
	T_GL_HWIDGET signature = GL_Message_GetWidgetById(message, SIGNATURE_ID);

	// Clears the signature
	GL_Signature_Clear(signature);
	return true;
}


// Callback to print signature
static bool OnPrint(T_GL_HMESSAGE message)
{
	T_GL_HWIDGET document;
	T_GL_HWIDGET signature;

	// Search widget signature on the window
	signature = GL_Message_GetWidgetById(message, SIGNATURE_ID);

	// Saves the signature in a temporary file
	GL_Signature_Save(signature, "file://flash/HOST/TEMP.SIG");

	// Creating a document to print
	document = GL_Document_Create(GL_Message_GetGraphicLib(message));

	// Adding a signature area on the document
	signature = GL_Signature_Create(document);

	// Load the temporary file signature
	GL_Signature_Load(signature, "file://flash/HOST/TEMP.SIG");

	// Print the document with the signature
	GL_Document_Print(document, 3 * GL_TIME_SECOND);

	// Destroys the open document
	GL_Widget_Destroy(document);
	return true;
}


// Callback to save signature
static bool OnSave(T_GL_HMESSAGE message)
{
	// Search widget signature on the window
	T_GL_HWIDGET signature = GL_Message_GetWidgetById(message, SIGNATURE_ID);

	// Save the signature
	GL_Signature_Save(signature, "file://flash/HOST/SIGNATUR.SIG");
	return true;
}


// Callback to load signature
static bool OnLoad(T_GL_HMESSAGE message)
{
	// Search widget signature on the window
	T_GL_HWIDGET signature = GL_Message_GetWidgetById(message, SIGNATURE_ID);

	// Load the signature
	GL_Signature_Load(signature, "file://flash/HOST/SIGNATUR.SIG");
	return true;
}


// Callback for processing a click message.
static bool OnQuit(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}


// Sample of signature capture
void GL_SampleSignature(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET mainLayout;
	T_GL_HWIDGET buttonLayout;
	T_GL_HWIDGET signature;
	T_GL_HWIDGET button;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);
	GL_Widget_SetSize(window, 90, 90, GL_UNIT_PERCENT);

	// Creating the main layout
	mainLayout = GL_Layout_Create(window);

		// Creation of the signature area
		signature = GL_Signature_Create(mainLayout);
			// Positioning of the signature area on the main layout
			GL_Widget_SetItem(signature, 0, 0);

			GL_Widget_SetMargins(signature, 5, 5, 5, 5, GL_UNIT_PIXEL);

			// Configuring Pen
			GL_Signature_SetPenWidth(signature, 2);

			// Registering an identifier to find the widget signature area during the callback event processing
			GL_Widget_SetId(signature, SIGNATURE_ID);

		// Creation of the button layout
		buttonLayout = GL_Layout_Create(mainLayout);

		// Positioning of the button layout on the main layout
		GL_Widget_SetItem(buttonLayout, 0, 1);

			// Prohibits the extension in height of the button area
			GL_Widget_SetGrow(buttonLayout, GL_DIRECTION_WIDTH);

			// Creation of the quit button
			button = GL_Button_Create(buttonLayout);
				GL_Widget_SetText(button, "Quit");

				// Positioning of the button on the button layout
				GL_Widget_SetItem(button, 0, 0);

				// Registers a callback on a button click
				GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnQuit);

				// Adds a keyboard shortcut to button
				GL_Widget_SetShortcut(button, GL_KEY_VALID);

				// Prohibits the extension in height of the button
				GL_Widget_SetGrow(button, GL_DIRECTION_WIDTH);

			// Creation of the clear button
			button = GL_Button_Create(buttonLayout);
				GL_Widget_SetText(button, "Clear");

				// Positioning of the button on the button layout
				GL_Widget_SetItem(button, 1, 0);

				// Registers a callback on a button click
				GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnClear);

				// Adds a keyboard shortcut to button
				GL_Widget_SetShortcut(button, GL_KEY_CORRECTION);

				// Prohibits the extension in height of the button
				GL_Widget_SetGrow(button, GL_DIRECTION_WIDTH);

			// Creation of the print button
			button = GL_Button_Create(buttonLayout);
				GL_Widget_SetText(button, "Print");

				// Positioning of the button on the button layout
				GL_Widget_SetItem(button, 2, 0);

				// Registers a callback on a button click
				GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnPrint);

				// Adds a keyboard shortcut to button
				GL_Widget_SetShortcut(button, GL_KEY_2);

				// Prohibits the extension in height of the button
				GL_Widget_SetGrow(button, GL_DIRECTION_WIDTH);

			// Creation of the save button
			button = GL_Button_Create(buttonLayout);
				GL_Widget_SetText(button, "0)Save");

				// Positioning of the button on the button layout
				GL_Widget_SetItem(button, 0, 1);

				// Registers a callback on a button click
				GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnSave);

				// Adds a keyboard shortcut to button
				GL_Widget_SetShortcut(button, GL_KEY_0);

				// Prohibits the extension in height of the button
				GL_Widget_SetGrow(button, GL_DIRECTION_WIDTH);

			// Creation of the load button
			button = GL_Button_Create(buttonLayout);
				GL_Widget_SetText(button, "1)Load");

				// Positioning of the button on the button layout
				GL_Widget_SetItem(button, 2, 1);

				// Registers a callback on a button click
				GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK, OnLoad);

				// Adds a keyboard shortcut to button
				GL_Widget_SetShortcut(button, GL_KEY_1);

				// Prohibits the extension in height of the button
				GL_Widget_SetGrow(button, GL_DIRECTION_WIDTH);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnQuit
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
