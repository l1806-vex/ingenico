#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// This function is called periodically to update the progress bar of the dialog box. 
// The value received as parameter corresponds to the current value of the progress bar.
// When this value reaches the maximum, the dialog is automatically closed.
static T_GL_COORD update(T_GL_COORD value)
{
	return value+1;
}

// Sample of dialog progress
void GL_SampleDialogProgress(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of displaying progress dialog
	result = GL_Dialog_Progress(graphicLib, "Progress", "Please wait", "file://flash/HOST/TU.TAR/wgusuite/image24.wgu", 0, 0, 100, update, GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
}
