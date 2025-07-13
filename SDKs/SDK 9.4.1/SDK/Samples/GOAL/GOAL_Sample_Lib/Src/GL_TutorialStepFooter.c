#include "GL_GraphicLib.h"

void GL_TutorialStepFooter(void)
{
	// Creates the graphic lib instance. The creation of the graphics library takes an important time, it is recommended to do creation once at application startup and use it for all windows created after.
	T_GL_HGRAPHIC_LIB gl = GL_GraphicLib_Create();

	// Creates window
	T_GL_HWIDGET window = GL_Window_Create(gl);

	// Creates main layout
	T_GL_HWIDGET mainLayout = GL_Layout_Create(window);

	// Creates the title
	{
		T_GL_HWIDGET title = GL_Label_Create(mainLayout);
		GL_Widget_SetItem(title, 0, 0); 
		GL_Widget_SetText(title, "Information");
		GL_Widget_SetBackColor(title, GL_COLOR_PURPLE);
		GL_Widget_SetForeColor(title, GL_COLOR_WHITE);
		GL_Widget_SetExpand(title, GL_DIRECTION_WIDTH);
	}

	// Create the footer layout
	{
		T_GL_HWIDGET footerLayout;
		T_GL_HWIDGET buttonOk;
		T_GL_HWIDGET buttonCancel;

		footerLayout = GL_Layout_Create(mainLayout);
		GL_Widget_SetItem(footerLayout, 0, 2);

		buttonOk = GL_Button_Create(footerLayout);
		GL_Widget_SetText(buttonOk, "OK");
		buttonCancel = GL_Button_Create(footerLayout);
		GL_Widget_SetText(buttonCancel, "Cancel");
		GL_Widget_SetItem(buttonOk, 0, 0);
		GL_Widget_SetItem(buttonCancel, 1, 0);
	}

	// Shows the window 1 seconds
	GL_Window_Dispatch(window, 1000);

	// Destroy the window
	GL_Widget_Destroy(window);

	// Destroy the graphic lib instance
	GL_GraphicLib_Destroy(gl);
}
