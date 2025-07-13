#include "GL_GraphicLib.h"
#include "GL_Samples.h"

#define GL_SCROLLVIEW_ID 0

// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnKeyPressed(T_GL_HMESSAGE message)
{
	T_GL_HWIDGET scrollview;
	T_GL_RANGE verticalRange;
	T_GL_RANGE horizontalRange;

	// Gets the handle of the scrollview
	scrollview = GL_Message_GetWidgetById(message, GL_SCROLLVIEW_ID);

	// Gets the vertical area of scroll view
	verticalRange   = GL_ScrollView_GetVerticalRange(scrollview);

	// Gets the horizontal area of scroll view
	horizontalRange = GL_ScrollView_GetHorizontalRange(scrollview);

	// According to the key pressed
	switch (GL_Message_GetKey(message))
	{
	// Go up in the text
	case GL_VIRTUAL_KEY_PREVIOUS:
		GL_ScrollView_Move(scrollview, horizontalRange.value, verticalRange.value - 10);
		break;

	// Go down in the text
	case GL_VIRTUAL_KEY_NEXT:
		GL_ScrollView_Move(scrollview, horizontalRange.value, verticalRange.value + 10);
		break;

	// Go left in the text
	case GL_VIRTUAL_KEY_LEFT:
		GL_ScrollView_Move(scrollview, horizontalRange.value - 10, verticalRange.value);
		break;

	// Go right in the text
	case GL_VIRTUAL_KEY_RIGHT:
		GL_ScrollView_Move(scrollview, horizontalRange.value + 10, verticalRange.value);
		break;

	case GL_KEY_CANCEL:
	case GL_KEY_VALID:
		// Here we force the value to 0 to release the application of the loop on GL_Window_Dispatch,
		// this assignment is an example and may be replaced by a more complete treatment 
		GL_Message_SetResult(message, 0);
		break;
	default:
		break;
	}
	return true;
}


// Selects the correct line creator according to display context
static T_GL_HWIDGET GL_Sample_CreateText(T_GL_HWIDGET parent, bool print)
{
	T_GL_HWIDGET result;

	// If the line will be printed
	if (print)
	{
		result = GL_Print_Create(parent);
	}
	else
	{
		result = GL_Label_Create(parent);
	}

	return result;
}


// Create the document with ttf font files in differents languages
static void GL_Sample_CreateDocument(T_GL_HWIDGET parent, bool print)
{
	T_GL_HWIDGET label;
	T_GL_HWIDGET layout;
	T_GL_DIM row = 0;

	// Creating the layout
	layout = GL_Layout_Create(parent);

		// Sign ANGSANA.TTF and load in terminal
		// Creating a thai label 
		label = GL_Sample_CreateText(layout, print);

			// Set position in the layout
			GL_Widget_SetItem(label, 0, row++);

			// Selects ttf file Angsana.TTF
			GL_Widget_SetFontName(label, "Angsana");
			
			// Sets the text in greek
			GL_Widget_SetText(label,"สวัสดีครับทุกคน ลองสะกดนี้");

		// Sign AKSHAR.TTF and load in terminal
		// Creating a hindi label 
		label = GL_Sample_CreateText(layout, print);

			// Set position in the layout
			GL_Widget_SetItem(label, 0, row++);

			// Selects ttf file Akshar.TTF
			GL_Widget_SetFontName(label, "Akshar");
			
			// Sets the text in greek
			GL_Widget_SetText(label,"सभी को नमस्कार.इस वर्तनी की कोशिश करो.");

		// Sign TIRESIA.TTF and load in terminal
		// Creating a french label 
		label = GL_Sample_CreateText(layout, print);

			// Set position in the layout
			GL_Widget_SetItem(label, 0, row++);

			// Selects ttf file Tiresias.TTF
			GL_Widget_SetFontName(label, "Tiresias");
			
			// Sets the text in greek
			GL_Widget_SetText(label,"Hé !! çà va ?");

}


// Display texts on screen
static void GL_Sample_CreateOnScreen(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET scrollview;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

		// Reduces the size of window
		GL_Widget_SetSize(window, 100, 100, GL_UNIT_PERCENT);

		// Creating the scroll view
		scrollview = GL_ScrollView_Create(window);

		// Sets the id to found later the scroll view
		GL_Widget_SetId(scrollview, GL_SCROLLVIEW_ID);

		// Fill the window
		GL_Sample_CreateDocument(scrollview, false);

	// Registering a callback. This callback will be called every keypress on the keyboard
	GL_Widget_RegisterCallback(window, GL_EVENT_KEY_DOWN, OnKeyPressed);

	// Display window and wait clic on button
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}


// Print texts on printer
static void GL_Sample_CreateOnPrinter(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET document;

	// Creating a blank document
	document = GL_Document_Create(graphicLib);

	// Create the document
	GL_Sample_CreateDocument(document, true);

	// Receipt print
	GL_Document_Print(document, 0);

	// Destruction of the document. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(document);
}


// Sample of label TTF
void GL_SampleLabelTtf(T_GL_HGRAPHIC_LIB graphicLib)
{
	GL_Sample_CreateOnPrinter(graphicLib);
	GL_Sample_CreateOnScreen(graphicLib);
}
