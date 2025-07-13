#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Callback for processing a click on valid button message.
// The "message" contains details of the message received by the window
static bool OnValid(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}

// Callback for processing a click on cancel message.
// The "message" contains details of the message received by the window
static bool OnCancel(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 1);
	return true;
}

// Sample of virtual keyboard
void GL_SampleCustomVirtualKeyboard(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET virtualKeyboard;
	ulong result;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 100, 100, GL_UNIT_PERCENT);

	// Creating a virtual keyboard
	virtualKeyboard = GL_VirtualKeyboard_Create(window);

	// Sets the default text
	GL_Widget_SetText(virtualKeyboard, "Hello");

	// Registering a callback. This callback will be called every click on the button valid
	GL_Widget_RegisterCallback(virtualKeyboard, GL_EVENT_VALID, OnValid);

	// Registering a callback. This callback will be called every click on the button cancel
	GL_Widget_RegisterCallback(virtualKeyboard, GL_EVENT_CANCEL, OnCancel);

	// Clear all characters pages existing by default in the virtual keyboard
	GL_VirtualKeyboard_ClearPages(virtualKeyboard);

	// Define the next keyboard, The keyboard is split into two pages of characters.
	//  First page :
	//   1 | 2 | 3 | Page 2
	//  ---+---+---+-----------
	//   4 | 5 | 6 | Cancel
	//  ---+---+---+-----------
	//   7 | 8 | 9 | Correction
	//  ---+---+---+-----------
	//   * | 0 | # | Validation
	// 
	//  Second page :
	//   A | B | C | Page 1
	//  ---+---+---+-----------
	//   D | E | F | Cancel
	//  ---+---+---+-----------
	//   G | H | I | Correction
	//  ---+---+---+-----------
	//   J | K | L | Validation

	// According to the charset used the constants are not the same.
	// If you always use the same charset please choose the appropriate constants to the charset (@ref GL_TypesKeysUtf8 or @ref GL_TypesKeysIso)
	if (GL_GraphicLib_GetCharset(graphicLib) == GL_ENCODING_UTF8)
	{
		GL_VirtualKeyboard_AddPage(virtualKeyboard, "Page 1", 
			// Note : I do not put a comma in the definition of the chain then the compiler will automatically join all the strings into a single
			"123" GL_KEY_UTF8_PAGE_UP    "\n" // To move to the next line on a keyboard just place a carriage return
			"456" GL_KEY_UTF8_CANCEL     "\n"
			"567" GL_KEY_UTF8_CORRECTION "\n"
			"*0#" GL_KEY_UTF8_VALID);

		GL_VirtualKeyboard_AddPage(virtualKeyboard, "Page 2",
			// Note : I do not put a comma in the definition of the chain then the compiler will automatically join all the strings into a single
			"ABC" GL_KEY_UTF8_PAGE_UP    "\n" // To move to the next line on a keyboard just place a carriage return
			"DEF" GL_KEY_UTF8_CANCEL     "\n" 
			"GHI" GL_KEY_UTF8_CORRECTION "\n"
			"JKL" GL_KEY_UTF8_VALID);

		// If you must place your own specific characters to please the utf8 encoding here.
		// example for 0xF808 occur in the utf8 string following "\xEF\xA0\x88" 
	}
	else
	{
		GL_VirtualKeyboard_AddPage(virtualKeyboard, "Page 1", 
			// Note : I do not put a comma in the definition of the chain then the compiler will automatically join all the strings into a single
			"123" GL_KEY_ISO_PAGE_UP    "\n" // To move to the next line on a keyboard just place a carriage return
			"456" GL_KEY_ISO_CANCEL     "\n"
			"567" GL_KEY_ISO_CORRECTION "\n"
			"*0#" GL_KEY_ISO_VALID);

		GL_VirtualKeyboard_AddPage(virtualKeyboard, "Page 2",
			// Note : I do not put a comma in the definition of the chain then the compiler will automatically join all the strings into a single
			"ABC" GL_KEY_ISO_PAGE_UP    "\n" // To move to the next line on a keyboard just place a carriage return
			"DEF" GL_KEY_ISO_CANCEL     "\n"
			"GHI" GL_KEY_ISO_CORRECTION "\n"
			"JKL" GL_KEY_ISO_VALID);

		// For characters value greater than 0xFF you must be preceded by \x1B (escape character)
		// example for 0xF808 occur in the iso string following "\x1B\xF8\x08" 
	}

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	result = GL_Window_MainLoop(window);

	// If the valid button pressed
	if (result == 0)
	{
		const char * text;

		// Gets the text entered
		text = GL_Widget_GetText(virtualKeyboard);

		(void)text; // <- Avoid a compilation warning
	}

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
