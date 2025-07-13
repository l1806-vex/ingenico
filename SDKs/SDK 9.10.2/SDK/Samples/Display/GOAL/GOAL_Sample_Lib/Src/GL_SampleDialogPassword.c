#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog password
void GL_SampleDialogPassword(T_GL_HGRAPHIC_LIB graphicLib)
{
	char text[100] = "1234";
	ulong result;

	// Example of entering a text
	result = GL_Dialog_Password (graphicLib, "Password input", "Enter password :","/d/d/d/d/d/d", text, sizeof(text), GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}
