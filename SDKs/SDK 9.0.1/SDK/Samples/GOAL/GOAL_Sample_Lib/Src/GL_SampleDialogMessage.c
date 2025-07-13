#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog message
void GL_SampleDialogMessage(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Open error message box (only the valid key is used)
	result = GL_Dialog_Message  (graphicLib, "Error title", "Error message", GL_ICON_ERROR, GL_BUTTON_VALID, GL_TIME_INFINITE);

	// Open question message box (the valid key and cancel are used)
	result = GL_Dialog_Message  (graphicLib, "Question title", "Question message", GL_ICON_QUESTION, GL_BUTTON_ALL, GL_TIME_INFINITE);

	// Open warning message box (only the valid key is used)
	result = GL_Dialog_Message  (graphicLib, "Warning title", "Warning message", GL_ICON_WARNING, GL_BUTTON_VALID, GL_TIME_INFINITE);

	// Open information message box (only the valid key is used)
	result = GL_Dialog_Message  (graphicLib, "Information title", "Information message", GL_ICON_INFORMATION, GL_BUTTON_VALID, GL_TIME_INFINITE);
}
