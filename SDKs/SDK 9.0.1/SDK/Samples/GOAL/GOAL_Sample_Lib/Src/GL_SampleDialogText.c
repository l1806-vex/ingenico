#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog text
void GL_SampleDialogText(T_GL_HGRAPHIC_LIB graphicLib)
{
	char text[100] = "330412345678";
	ulong result;

	// Example of entering a text
	result = GL_Dialog_Text (graphicLib, "Text input", "Telephone number :","(/d/d)/d/d./d/d./d/d./d/d./d/d", text, sizeof(text), GL_TIME_INFINITE);
}
