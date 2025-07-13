#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnClick(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}

// Sample of edit mask
void GL_SampleEditMask(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET button;
	T_GL_HWIDGET edit;
	T_GL_HWIDGET label;
	T_GL_HWIDGET layout;
	T_GL_HWIDGET scrollview;
	T_GL_DIM row = 0;

	window = GL_Window_Create(graphicLib);

		scrollview = GL_ScrollView_Create(window);

			layout = GL_Layout_Create(scrollview);

				button = GL_Button_Create (layout);
					GL_Widget_SetItem     (button, 0, row++);
					GL_Widget_SetExpand   (button, GL_DIRECTION_WIDTH);
					GL_Widget_SetText     (button,"Quit");
					GL_Widget_SetShortcut (button, GL_KEY_VALID);
					GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK,  OnClick);

				// Input Mask character decimal
				label = GL_Label_Create   (layout);
					GL_Widget_SetItem     (label, 0, row++);
					GL_Widget_SetText     (label, "Decimal");

				edit = GL_Edit_Create     (layout);
					GL_Widget_SetItem     (edit, 0, row++);
					GL_Widget_SetMask     (edit, "/d/d/d/d/d/d/d/d/d/d/D./D/D Eur");
					GL_Widget_SetExpand   (edit, GL_DIRECTION_WIDTH);
					GL_Widget_SetTextAlign(edit, GL_ALIGN_RIGHT);
					GL_Widget_SetMode     (edit, GL_MODE_0_NOT_SIGNIFICANT);


				// Input mask character octal
				label = GL_Label_Create   (layout);
					GL_Widget_SetItem     (label, 0, row++);
					GL_Widget_SetText     (label, "Octal");

				edit = GL_Edit_Create     (layout);
					GL_Widget_SetItem     (edit, 0, row++);
					GL_Widget_SetExpand   (edit, GL_DIRECTION_WIDTH);
					GL_Widget_SetMask     (edit, "0o/o/o/o/o/o/o/o/o");


				// Input mask character hexadecimal
				label = GL_Label_Create   (layout);
					GL_Widget_SetItem     (label, 0, row++);
					GL_Widget_SetText     (label, "Hexa");

				edit = GL_Edit_Create     (layout);
					GL_Widget_SetItem     (edit, 0, row++);
					GL_Widget_SetExpand   (edit, GL_DIRECTION_WIDTH);
					GL_Widget_SetMask     (edit, "0x/x/x/x/x/x/x/x/x");


				// Input mask character binary
				label = GL_Label_Create   (layout);
					GL_Widget_SetItem     (label, 0, row++);
					GL_Widget_SetText     (label, "Binary");

				edit = GL_Edit_Create     (layout);
					GL_Widget_SetItem     (edit, 0, row++);
					GL_Widget_SetExpand   (edit, GL_DIRECTION_WIDTH);
					GL_Widget_SetMask     (edit, "0b/b/b/b/b/b/b/b/b");


				// Input mask with any characters
				label = GL_Label_Create   (layout);
					GL_Widget_SetItem     (label, 0, row++);
					GL_Widget_SetText     (label, "Password");

				edit = GL_Edit_Create     (layout);
					GL_Widget_SetItem     (edit, 0, row++);
					GL_Widget_SetExpand   (edit, GL_DIRECTION_WIDTH);
					GL_Widget_SetMask     (edit, "/c/c/c/c/c/c/c/c");
					GL_Widget_SetMode     (edit, GL_MODE_PASSWORD);


				// Input mask with decimal
				label = GL_Label_Create   (layout);
					GL_Widget_SetItem     (label, 0, row++);
					GL_Widget_SetText     (label, "Date");

				edit = GL_Edit_Create     (layout);
					GL_Widget_SetItem     (edit, 0, row++);
					GL_Widget_SetExpand   (edit, GL_DIRECTION_WIDTH);
					GL_Widget_SetMask     (edit, "/d/d///d/d///d/d");


				// Input mask with decimal
				label = GL_Label_Create   (layout);
					GL_Widget_SetItem     (label, 0, row++);
					GL_Widget_SetText     (label, "Hour");

				edit = GL_Edit_Create     (layout);
					GL_Widget_SetItem     (edit, 0, row++);
					GL_Widget_SetExpand   (edit, GL_DIRECTION_WIDTH);
					GL_Widget_SetMask     (edit, "/d/d:/d/d:/d/d");


				// Input mask with alphanumeric
				label = GL_Label_Create   (layout);
					GL_Widget_SetItem     (label, 0, row++);
					GL_Widget_SetText     (label, "Alphanumeric");

				edit = GL_Edit_Create     (layout);
					GL_Widget_SetItem     (edit, 0, row++);
					GL_Widget_SetExpand   (edit, GL_DIRECTION_WIDTH);
					GL_Widget_SetMask     (edit, "/a/a/a/a/a/a/a/a/a/a/a");


				// Input mask with any char
				label = GL_Label_Create   (layout);
					GL_Widget_SetItem     (label, 0, row++);
					GL_Widget_SetText     (label, "Any char");

				edit = GL_Edit_Create     (layout);
					GL_Widget_SetItem     (edit, 0, row++);
					GL_Widget_SetExpand   (edit, GL_DIRECTION_WIDTH);
					GL_Widget_SetMask     (edit, "/c/c/c/c/c/c/c/c/c/c/c");


				// Input mask with user character mask
				label = GL_Label_Create   (layout);
					GL_Widget_SetItem     (label, 0, row++);
					GL_Widget_SetText     (label, "User char mask");

				edit = GL_Edit_Create     (layout);
					GL_Widget_SetItem     (edit, 0, row++);
					GL_Widget_SetExpand   (edit, GL_DIRECTION_WIDTH);

					// Set the mask with user character mask
					GL_Widget_SetMask     (edit, "/u/u/u/u/u/u/u/u/u/u/u");

					// Configure the user character
					GL_Widget_SetUserChar (edit, "123456789.");


				// Input with no mask defined
				label = GL_Label_Create   (layout);
					GL_Widget_SetItem     (label, 0, row++);
					GL_Widget_SetText     (label, "No mask");

				edit = GL_Edit_Create     (layout);
					GL_Widget_SetItem     (edit, 0, row++);
					GL_Widget_SetExpand   (edit, GL_DIRECTION_WIDTH);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	GL_Widget_Destroy(window);
}
