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


/** Escapes sequences */
#define ESC_UNDERLINE "\x1B-"
#define ESC_BOLD      "\x1B*"
#define ESC_ITALIC    "\x1B/"
#define ESC_XXSMALL   "\x1B""0"
#define ESC_XSMALL    "\x1B""1"
#define ESC_SMALL     "\x1B""2"
#define ESC_MEDIUM    "\x1B""3"
#define ESC_LARGE     "\x1B""4"
#define ESC_XLARGE    "\x1B""5"
#define ESC_XXLARGE   "\x1B""6"
#define ESC_REVERSE   "\x1B#"
#define ESC_RESTORE   "\x1B."
#define ESC 0x1B
#define ESC_BACKCOLOR 0x60
#define ESC_FORECOLOR 0x40


/** Set all escape sequences with fore colors */
static void GL_Sample_SetEscapeForeColors(char * text)
{
	int position = 0;
	unsigned char color;
	int line, column;
	color = 0;

	for (line = 0; line < 4; line ++)
	{
		for (column = 0; column < 8; column ++)
		{
			// If the forecolor must be highlighted 
			if (color <= 0x07)
			{
				text[position++] = ESC;
				text[position++] = ESC_BACKCOLOR + 0x1F;
			}
			else
			{
				text[position++] = ESC;
				text[position++] = ESC_BACKCOLOR + 0x07;
			}

			// Add the fore color 
			text[position++] = GL_KEY_ESCAPE;
			text[position++] = ESC_FORECOLOR + color;

			// Add its hexadecimal value
			sprintf(&text[position], "%02X ", (int)(ESC_FORECOLOR + color));
			position += 3;
			color ++;
		}
		text[position++] = '\n';
	}
	text[position++] = '\0';
}


/** Set all escape sequence with back colors */
static void GL_Sample_SetEscapeBackColor(char * text)
{
	int position = 0;
	unsigned char color;
	int line, column;
	color = 0;
	for (line = 0; line < 4; line ++)
	{
		for (column = 0; column < 8; column ++)
		{
			// If the backcolor must be highlighted 
			if (color >= 0x18)
			{
				text[position++] = ESC;
				text[position++] = 0x47;
			}

			// Add the back color 
			text[position++] = GL_KEY_ESCAPE;
			text[position++] = ESC_BACKCOLOR + color;

			// Add its hexadecimal value
			sprintf(&text[position], "%02X ", (int)(ESC_BACKCOLOR + color));
			position += 3;
			color ++;
		}
		text[position++] = '\n';
	}
	text[position++] = '\0';
}


// Create the document with differents characteres
static void GL_Sample_CreateDocument(T_GL_HWIDGET parent, bool print)
{
	T_GL_HWIDGET label;
	T_GL_HWIDGET layout;
	T_GL_DIM row = 0;
	char message[256];

	// Creating the layout
	layout = GL_Layout_Create(parent);

		// Creating a style label 
		label = GL_Sample_CreateText(layout, print);

			// Set position in the layout
			GL_Widget_SetItem(label, 0, row++);

			// Wrap the text
			GL_Widget_SetWrap(label, true);

			// Sets the text 
			GL_Widget_SetText(label, 
				ESC_UNDERLINE "Underline " ESC_UNDERLINE 
				ESC_BOLD      "Bold "      ESC_BOLD
				ESC_ITALIC    "Italic "    ESC_ITALIC
				ESC_XXSMALL   "XXSmall "   ESC_XXSMALL
				ESC_XSMALL    "XSmall "    ESC_XSMALL
				ESC_SMALL     "Small "     ESC_SMALL
				ESC_MEDIUM    "Medium "    ESC_MEDIUM
				ESC_LARGE     "Large "     ESC_LARGE
				ESC_XLARGE    "XLarge "    ESC_XLARGE
				ESC_XXLARGE   "XXLarge "   ESC_XXLARGE ESC_RESTORE  
				ESC_REVERSE   "Reverse\n"   ESC_REVERSE);


		// Creating a label with back color
		label = GL_Sample_CreateText(layout, print);

			// Set position in the layout
			GL_Widget_SetItem(label, 0, row++);

			// Sets the text 
			GL_Widget_SetText(label, "Fore colors :");


		// Creating a label with back color
		label = GL_Sample_CreateText(layout, print);

			// Wrap the text
			GL_Widget_SetWrap(label, true);

			// Add escape sequences with all fore colors
			GL_Sample_SetEscapeForeColors(message);

			// Set position in the layout
			GL_Widget_SetItem(label, 0, row++);

			// Sets the text 
			GL_Widget_SetText(label, message);


		// Creating a label with back color
		label = GL_Sample_CreateText(layout, print);

			// Set position in the layout
			GL_Widget_SetItem(label, 0, row++);

			// Sets the text 
			GL_Widget_SetText(label, "Back colors : ");


		// Creating a label with back color
		label = GL_Sample_CreateText(layout, print);

			// Wrap the text
			GL_Widget_SetWrap(label, true);

			// Add escape sequences with all back colors
			GL_Sample_SetEscapeBackColor(message);

			// Set position in the layout
			GL_Widget_SetItem(label, 0, row++);

			// Sets the text 
			GL_Widget_SetText(label, message);
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


// Sample of label escape sequences
void GL_SampleLabelEscapeSequence(T_GL_HGRAPHIC_LIB graphicLib)
{
	GL_Sample_CreateOnPrinter(graphicLib);
	GL_Sample_CreateOnScreen(graphicLib);
}
