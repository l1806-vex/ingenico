#include "GL_GraphicLib.h"

void GL_TutorialStepGraphicLib(void)
{
	// Creates the graphic lib instance. The creation of the graphics library takes an important time, it is recommended to do creation once at application startup and use it for all windows created after.
	T_GL_HGRAPHIC_LIB gl = GL_GraphicLib_Create();

	// Destroy the graphic lib instance
	GL_GraphicLib_Destroy(gl);
}
