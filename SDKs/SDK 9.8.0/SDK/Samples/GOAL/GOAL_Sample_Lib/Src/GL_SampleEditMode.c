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

// Sample of edit mode
void GL_SampleEditMode(T_GL_HGRAPHIC_LIB graphicLib)
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

				button = GL_Button_Create     (layout);
					GL_Widget_SetItem         (button, 0, row++);
					GL_Widget_SetExpand       (button, GL_DIRECTION_WIDTH);
					GL_Widget_SetText         (button,"Quit");
					GL_Widget_SetShortcut     (button, GL_KEY_VALID);
					GL_Widget_RegisterCallback(button, GL_EVENT_STYLUS_CLICK,  OnClick);

				label = GL_Label_Create       (layout);
					GL_Widget_SetItem         (label, 0, row++);
					GL_Widget_SetText         (label, "Right align, replace");

				edit = GL_Edit_Create         (layout);
					GL_Widget_SetItem         (edit, 0, row++);
					GL_Widget_SetMask         (edit, "/x/x/x./x/x/x./x/x./x/x");
					GL_Widget_SetExpand       (edit, GL_DIRECTION_ALL);
					GL_Widget_SetMode         (edit, GL_MODE_REPLACE);
					GL_Widget_SetTextAlign    (edit, GL_ALIGN_RIGHT);

				label = GL_Label_Create       (layout);
					GL_Widget_SetItem         (label, 0, row++);
					GL_Widget_SetText         (label, "Right align, insert");

				edit = GL_Edit_Create         (layout);
					GL_Widget_SetItem         (edit, 0, row++);
					GL_Widget_SetMask         (edit, "/x/x/x./x/x/x./x/x./x/x");
					GL_Widget_SetExpand       (edit, GL_DIRECTION_ALL);
					GL_Widget_SetMode         (edit, GL_MODE_INSERT);
					GL_Widget_SetTextAlign    (edit, GL_ALIGN_RIGHT);

				label = GL_Label_Create       (layout);
					GL_Widget_SetItem         (label, 0, row++);
					GL_Widget_SetText         (label, "Left align, replace");

				edit = GL_Edit_Create         (layout);
					GL_Widget_SetItem         (edit, 0, row++);
					GL_Widget_SetMask         (edit, "/x/x/x./x/x/x./x/x./x/x");
					GL_Widget_SetExpand       (edit, GL_DIRECTION_ALL);
					GL_Widget_SetMode         (edit, GL_MODE_REPLACE);
					GL_Widget_SetTextAlign    (edit, GL_ALIGN_LEFT);

				label = GL_Label_Create       (layout);
					GL_Widget_SetItem         (label, 0, row++);
					GL_Widget_SetText         (label, "Left align, insert");

				edit = GL_Edit_Create         (layout);
					GL_Widget_SetItem         (edit, 0, row++);
					GL_Widget_SetMask         (edit, "/x/x/x./x/x/x./x/x./x/x");
					GL_Widget_SetExpand       (edit, GL_DIRECTION_ALL);
					GL_Widget_SetMode         (edit, GL_MODE_INSERT);
					GL_Widget_SetTextAlign    (edit, GL_ALIGN_LEFT);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	GL_Widget_Destroy(window);
}
