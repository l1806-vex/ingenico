#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog color
void GL_SampleDialogColor(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_COLOR color;
	ulong result;

	// Example of selecting color
	result = GL_Dialog_Color (graphicLib, "Color", "Select color", &color, GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}
