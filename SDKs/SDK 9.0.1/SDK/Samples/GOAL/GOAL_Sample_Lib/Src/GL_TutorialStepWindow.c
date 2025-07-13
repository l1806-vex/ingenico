#include "GL_GraphicLib.h"

void GL_TutorialStepWindow(void)
{
	// Creates the graphic lib instance. The creation of the graphics library takes an important time, it is recommended to do creation once at application startup and use it for all windows created after.
	T_GL_HGRAPHIC_LIB gl = GL_GraphicLib_Create();

	// Creates window
	T_GL_HWIDGET window = GL_Window_Create(gl);

	// Shows the window 1 seconds
	GL_Window_Dispatch(window, 1000);

	// Destroy the window
	GL_Widget_Destroy(window);

	// Destroy the graphic lib instance
	GL_GraphicLib_Destroy(gl);
}
