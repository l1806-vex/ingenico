#include "GL_GraphicLib.h"

void GL_TutorialStepLayout(void)
{
	// Creates the graphic lib instance. The creation of the graphics library takes an important time, it is recommended to do creation once at application startup and use it for all windows created after.
	T_GL_HGRAPHIC_LIB gl = GL_GraphicLib_Create();

	// Creates window
	T_GL_HWIDGET window = GL_Window_Create(gl);

	// Creates main layout
	T_GL_HWIDGET mainLayout = GL_Layout_Create(window);

	T_GL_HWIDGET title = GL_Label_Create(mainLayout);
	GL_Widget_SetItem(title, 0, 0); 
	GL_Widget_SetText(title, "Information");
	GL_Widget_SetBackColor(title, GL_COLOR_PURPLE);
	GL_Widget_SetForeColor(title, GL_COLOR_WHITE);
	GL_Widget_SetExpand(title, GL_DIRECTION_WIDTH);

	// Shows the window 1 seconds
	GL_Window_Dispatch(window, 1000);

	// Destroy the window
	GL_Widget_Destroy(window);

	// Destroy the graphic lib instance
	GL_GraphicLib_Destroy(gl);
}
