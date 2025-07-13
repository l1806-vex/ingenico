#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Sample of dialog virtual keyboard
void GL_SampleDialogVirtualKeyboard1(T_GL_HGRAPHIC_LIB graphicLib)
{
	char text[100] = "330412345678";
	ulong result;

	// Example of entering a text by defining a mask user
	result = GL_Dialog_VirtualKeyboard (graphicLib, 0, "Enter your mail : ","/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u/u|0123456789abcdefghijklmnopqrstuvwxyz@_.", text, sizeof(text), GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}


// Sample of dialog virtual keyboard
void GL_SampleDialogVirtualKeyboard2(T_GL_HGRAPHIC_LIB graphicLib)
{
	char text[100] = "330412345678";
	ulong result;

	// Example of entering a text
	result = GL_Dialog_VirtualKeyboard (graphicLib, "Virtual keyboard input", "Telephone number :","(/d/d)/d/d./d/d./d/d./d/d./d/d", text, sizeof(text), GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}


// Sample of dialog virtual keyboard
void GL_SampleDialogVirtualKeyboard3(T_GL_HGRAPHIC_LIB graphicLib)
{
	char text[100] = "330412345678";
	ulong result;

	// Example of entering a text
	result = GL_Dialog_VirtualKeyboard (graphicLib, "Virtual keyboard input", "Text edition : ",0, text, sizeof(text), GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}


// Sample of dialog virtual keyboard
void GL_SampleDialogVirtualKeyboard(T_GL_HGRAPHIC_LIB graphicLib)
{
	GL_SampleDialogVirtualKeyboard1(graphicLib);
	GL_SampleDialogVirtualKeyboard2(graphicLib);
	GL_SampleDialogVirtualKeyboard3(graphicLib);
}
