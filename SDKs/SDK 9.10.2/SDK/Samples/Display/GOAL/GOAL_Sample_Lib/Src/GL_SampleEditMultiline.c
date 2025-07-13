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

// Sample of edit multiline
void GL_SampleEditMultiline(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET edit;
	T_GL_HWIDGET layout;
	T_GL_HWIDGET mainLayout;
	T_GL_HWIDGET label;

	window = GL_Window_Create(graphicLib);

	mainLayout = GL_Layout_Create(window);

		edit = GL_Edit_Create(mainLayout);
		GL_Widget_SetItem(edit, 0, 0);
		GL_Widget_SetShortcut(edit, GL_KEY_VALID);
		GL_Widget_RegisterCallback(edit, GL_EVENT_STYLUS_CLICK,  OnClick);

		layout = GL_Layout_Create(edit);
			GL_Widget_SetGrow  (layout, GL_DIRECTION_ALL);
			GL_Widget_SetShrink(layout, GL_DIRECTION_ALL);
			GL_Widget_SetExpand(layout, GL_DIRECTION_ALL);

			label = GL_Label_Create(layout);
				GL_Widget_SetGrow     (label, GL_DIRECTION_ALL);
				GL_Widget_SetShrink   (label, GL_DIRECTION_ALL);
				GL_Widget_SetExpand   (label, GL_DIRECTION_ALL);
				GL_Widget_SetBackColor(label, 0xFFDFDFDF);
				GL_Widget_SetForeColor(label, 0xFF007F00);
				GL_Widget_SetId       (label, 0xFF000001);
				GL_Widget_SetForeAlign(label, GL_ALIGN_TOP);

		GL_Widget_SetText     (edit,"Hello\nWorld world");
		GL_Widget_SetShrink   (edit, GL_DIRECTION_ALL);
		GL_Widget_SetGrow     (edit, GL_DIRECTION_ALL);
		GL_Widget_SetExpand   (edit, GL_DIRECTION_ALL);
		GL_Widget_SetMode     (edit, GL_MODE_REPLACE);
		GL_Widget_SetTextAlign(edit, GL_ALIGN_LEFT);


		edit = GL_Edit_Create(mainLayout);
		GL_Widget_SetItem(edit, 0, 1);
		GL_Widget_SetShortcut(edit, GL_KEY_VALID);
		GL_Widget_RegisterCallback(edit, GL_EVENT_STYLUS_CLICK,  OnClick);

		layout = GL_Layout_Create(edit);
			GL_Widget_SetGrow  (layout, GL_DIRECTION_ALL);
			GL_Widget_SetShrink(layout, GL_DIRECTION_ALL);
			GL_Widget_SetExpand(layout, GL_DIRECTION_ALL);

			label = GL_Label_Create(layout);
				GL_Widget_SetGrow     (label, GL_DIRECTION_ALL);
				GL_Widget_SetShrink   (label, GL_DIRECTION_ALL);
				GL_Widget_SetExpand   (label, GL_DIRECTION_ALL);
				GL_Widget_SetBackColor(label, 0xFFDFDFDF);
				GL_Widget_SetForeColor(label, 0xFF00007F);
				GL_Widget_SetId       (label, 0xFF000001);
				GL_Widget_SetForeAlign(label, GL_ALIGN_TOP);

		GL_Widget_SetText     (edit,"Bonjour\nMonde");
		GL_Widget_SetShrink   (edit, GL_DIRECTION_ALL);
		GL_Widget_SetGrow     (edit, GL_DIRECTION_ALL);
		GL_Widget_SetExpand   (edit, GL_DIRECTION_ALL);
		GL_Widget_SetMode     (edit, GL_MODE_INSERT);
		GL_Widget_SetTextAlign(edit, GL_ALIGN_LEFT);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	GL_Widget_Destroy(window);
}
