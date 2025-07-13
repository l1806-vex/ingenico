#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog virtual keyboard
void GL_SampleDialogVirtualKeyboard(T_GL_HGRAPHIC_LIB graphicLib)
{
	char text[100] = "330412345678";
	ulong result;

	// Example of entering a text
	result = GL_Dialog_VirtualKeyboard (graphicLib, "Virtual keyboard input", "Telephone number :","(/d/d)/d/d./d/d./d/d./d/d./d/d", text, sizeof(text), GL_TIME_INFINITE);

	// Example of entering a text
	result = GL_Dialog_VirtualKeyboard (graphicLib, "Virtual keyboard input", "Text edition : ",0, text, sizeof(text), GL_TIME_INFINITE);
}
