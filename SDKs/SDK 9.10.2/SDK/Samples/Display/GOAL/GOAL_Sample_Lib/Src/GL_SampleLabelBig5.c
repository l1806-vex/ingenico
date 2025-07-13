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


// Create the document with differents characteres
static void GL_Sample_CreateDocument(T_GL_HWIDGET parent, bool print)
{
	T_GL_HWIDGET label;
	T_GL_HWIDGET layout;
	T_GL_DIM row = 0;

	// Creating the layout
	layout = GL_Layout_Create(parent);

		// Load in terminal the package FONT_GOAL_CHINESE.Mxx
		// Creating a chinese label 
		label = GL_Sample_CreateText(layout, print);
			
			// Set position in the layout
			GL_Widget_SetItem(label, 0, row++);
			GL_Widget_SetWrap(label, true);

			// WARNING : To avoid delays in the display it is important 
			// for Chinese characters to select a font size in the existing 
			// (12, 16, 24, 24, 32, 48, 36 and 72 pixels)
			GL_Widget_SetFontSize(label, 24, 24, GL_UNIT_PIXEL);

			// Sets a text encoded in big 5
			GL_Widget_SetText(label,"如何在  中使用既有的 C library?"
				"　在資訊科技快速發展的今天, 開發及測試軟體的速度是不容忽視的"
				"課題. 為加快開發及測試的速度, 我們便常希望能利用一些已開發好的"
				"library, 並有一個 fast prototyping 的 programming language 可"
				"供使用. 目前有許\許\多多的 library 是以 C 寫成, 而  是一個"
				"fast prototyping 的 programming language. 故我們希望能將既有的"
				"C library 拿到  的環境中測試及整合. 其中最主要也是我們所"
				"要討論的問題就是:");
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


// Sample of label big5
void GL_SampleLabelBig5(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_ENCODING_CHARSET charset = GL_GraphicLib_GetCharset(graphicLib);

	// IMPORTANT : You must select the charset big5
	GL_GraphicLib_SetCharset(graphicLib, GL_ENCODING_BIG_5);
	GL_Sample_CreateOnPrinter(graphicLib);
	GL_Sample_CreateOnScreen(graphicLib);

	// Restore previous charset
	GL_GraphicLib_SetCharset(graphicLib, charset);
}
