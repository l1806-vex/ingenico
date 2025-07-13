#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnClick(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}

// Sample of font
void GL_SampleFont(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET button;
	T_GL_HWIDGET label;
	T_GL_HWIDGET layout;
	T_GL_HWIDGET scrollview;
	T_GL_DIM row = 0;

	window = GL_Window_Create(graphicLib);

		scrollview = GL_ScrollView_Create(window);
		layout = GL_Layout_Create(scrollview);

		button = GL_Button_Create(layout);
			GL_Widget_SetItem             (button, 0, row++);
			GL_Widget_SetText             (button, "GL_SCALE_XXSMALL");

		label = GL_Label_Create(layout);
			GL_Widget_SetItem             (label, 0, row++);
			GL_Widget_SetText             (label, "012345678901234567890123456");
			GL_Widget_SetFontScale        (label, GL_SCALE_XXSMALL);
			GL_Widget_SetBackColor        (label, GL_COLOR_BLACK);
			GL_Widget_SetForeColor        (label, GL_COLOR_WHITE);

		button = GL_Button_Create(layout);
			GL_Widget_SetItem             (button, 0, row++);
			GL_Widget_SetText             (button, "GL_SCALE_XSMALL");

		label = GL_Label_Create(layout);
			GL_Widget_SetItem             (label, 0, row++);
			GL_Widget_SetText             (label, "012345678901234567890123");
			GL_Widget_SetFontScale        (label, GL_SCALE_XSMALL);
			GL_Widget_SetBackColor        (label, GL_COLOR_BLACK);
			GL_Widget_SetForeColor        (label, GL_COLOR_WHITE);

		button = GL_Button_Create(layout);
			GL_Widget_SetItem             (button, 0, row++);
			GL_Widget_SetText             (button, "GL_SCALE_SMALL");

		label = GL_Label_Create(layout);
			GL_Widget_SetItem             (label, 0, row++);
			GL_Widget_SetText             (label, "0123456789012345678901");
			GL_Widget_SetFontScale        (label, GL_SCALE_SMALL);
			GL_Widget_SetBackColor        (label, GL_COLOR_BLACK);
			GL_Widget_SetForeColor        (label, GL_COLOR_WHITE);

		button = GL_Button_Create(layout);
			GL_Widget_SetItem             (button, 0, row++);
			GL_Widget_SetText             (button, "GL_SCALE_MEDIUM");

		label = GL_Label_Create(layout);
			GL_Widget_SetItem             (label, 0, row++);
			GL_Widget_SetText             (label, "01234567890123456789");
			GL_Widget_SetFontScale        (label, GL_SCALE_MEDIUM);
			GL_Widget_SetBackColor        (label, GL_COLOR_BLACK);
			GL_Widget_SetForeColor        (label, GL_COLOR_WHITE);

		button = GL_Button_Create(layout);
			GL_Widget_SetItem             (button, 0, row++);
			GL_Widget_SetText             (button, "GL_SCALE_LARGE");

		label = GL_Label_Create(layout);
			GL_Widget_SetItem             (label, 0, row++);
			GL_Widget_SetText             (label, "0123456789012345");
			GL_Widget_SetFontScale        (label, GL_SCALE_LARGE);
			GL_Widget_SetBackColor        (label, GL_COLOR_BLACK);
			GL_Widget_SetForeColor        (label, GL_COLOR_WHITE);

		button = GL_Button_Create(layout);
			GL_Widget_SetItem             (button, 0, row++);
			GL_Widget_SetText             (button, "GL_SCALE_XLARGE");

		label = GL_Label_Create(layout);
			GL_Widget_SetItem             (label, 0, row++);
			GL_Widget_SetText             (label, "0123456789012");
			GL_Widget_SetFontScale        (label, GL_SCALE_XLARGE);
			GL_Widget_SetBackColor        (label, GL_COLOR_BLACK);
			GL_Widget_SetForeColor        (label, GL_COLOR_WHITE);

		button = GL_Button_Create(layout);
			GL_Widget_SetItem             (button, 0, row++);
			GL_Widget_SetText             (button, "GL_SCALE_XXLARGE");

		label = GL_Label_Create(layout);
			GL_Widget_SetItem             (label, 0, row++);
			GL_Widget_SetText             (label, "0123456789");
			GL_Widget_SetFontScale        (label, GL_SCALE_XXLARGE);
			GL_Widget_SetBackColor        (label, GL_COLOR_BLACK);
			GL_Widget_SetForeColor        (label, GL_COLOR_WHITE);

		label = GL_Label_Create(layout);
			GL_Widget_SetItem             (label, 0, row++);
			GL_Widget_SetText             (label, "UTF8 chars : éçèàêùß");
			GL_Widget_SetFontScale        (label, GL_SCALE_LARGE);
			GL_Widget_SetBackColor        (label, GL_COLOR_BLACK);
			GL_Widget_SetForeColor        (label, GL_COLOR_WHITE);

		button = GL_Button_Create(layout);
			GL_Widget_SetItem             (button, 0, row++);
			GL_Widget_SetText             (button, "Quit");
			GL_Widget_SetForeAlign        (button, GL_ALIGN_BOTTOM);
			GL_Widget_SetShortcut         (button, GL_KEY_VALID);
			GL_Widget_RegisterCallback    (button, GL_EVENT_STYLUS_CLICK,  OnClick);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);
	
	GL_Widget_Destroy(window);
}
