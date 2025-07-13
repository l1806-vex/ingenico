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


// Sample of label utf8
void GL_SampleLabelUtf8(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET label;
	T_GL_HWIDGET layout;
	T_GL_HWIDGET scrollview;
	T_GL_DIM row = 0;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

		// Reduces the size of window
		GL_Widget_SetSize(window, 100, 100, GL_UNIT_PERCENT);

		// Creating the scroll view
		scrollview = GL_ScrollView_Create(window);

		// Sets the id to found later the scroll view
		GL_Widget_SetId(scrollview, GL_SCROLLVIEW_ID);

		// Creating the layout
		layout = GL_Layout_Create(scrollview);


			// Default GOAL fonts supports all latin characters
			// Creating a latin label 
			label = GL_Label_Create(layout);

				// Set position in the layout
				GL_Widget_SetItem(label, 0, row++);

				// Wrap the text
				GL_Widget_SetWrap(label, true);

				// Sets the text 
				GL_Widget_SetText(label,"Hé !! çà va ?");


			// Load in terminal the package FONT_GOAL_ORIENTAL.Mxx
			// Creating an arabic label 
			label = GL_Label_Create(layout);

				// Set position in the layout
				GL_Widget_SetItem(label, 0, row++);

				// Wrap the text
				GL_Widget_SetWrap(label, true);

				// Sets the text 
				GL_Widget_SetText(label,"فإن الجمعية العامة تنادي بهذا الإعلان");


			// Load in terminal the package FONT_GOAL_ORIENTAL.Mxx
			// Creating an hebrew label 
			label = GL_Label_Create(layout);

				// Set position in the layout
				GL_Widget_SetItem(label, 0, row++);

				// Wrap the text
				GL_Widget_SetWrap(label, true);

				// Sets the text 
				GL_Widget_SetText(label,"שלום לכולם תרגום מבחן");


			// Load in terminal the package FONT_GOAL_TRADITIONAL_CHINESE.Mxx
			// Creating a chinese label 
			label = GL_Label_Create(layout);
			
				// Set position in the layout
				GL_Widget_SetItem(label, 0, row++);
				GL_Widget_SetFontSize(label, 24,24, GL_UNIT_PIXEL); // WARNING : only one size defined

				// Sets the text in traditional chinese
				GL_Widget_SetText(label,"電買開東車紅無鳥熱時語");


			// Load in terminal the package FONT_GOAL_SIMPLIFIED_CHINESE.Mxx
			// Creating a chinese label 
			label = GL_Label_Create(layout);

				// Set position in the layout
				GL_Widget_SetItem(label, 0, row++);
				GL_Widget_SetFontSize(label, 16,16, GL_UNIT_PIXEL);

				// Sets the text in simplified chinese
				GL_Widget_SetText(label,"电买开东车红无鸟热时语");


			// Load in terminal the package FONT_GOAL_CYRILLIC_GREEK.Mxx
			// Creating a russian label 
			label = GL_Label_Create(layout);

				// Set position in the layout
				GL_Widget_SetItem(label, 0, row++);

				// Sets the text in russian
				GL_Widget_SetText(label,"Привет всем, перевод испытаний");

				// Wrap the text
				GL_Widget_SetWrap(label, true);


			// Load in terminal the package FONT_GOAL_CYRILLIC_GREEK.Mxx
			// Creating a greek label 
			label = GL_Label_Create(layout);

				// Set position in the layout
				GL_Widget_SetItem(label, 0, row++);

				// Sets the text in greek
				GL_Widget_SetText(label,"Γεια σε όλους, δοκιμασία της μετάφρασης");

				// Wrap the text
				GL_Widget_SetWrap(label, true);


	// Registering a callback. This callback will be called every keypress on the keyboard
	GL_Widget_RegisterCallback(window, GL_EVENT_KEY_DOWN, OnKeyPressed);

	// Display window and wait clic on button
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
