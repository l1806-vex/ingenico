#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog media
void GL_SampleDialogMedia(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of displaying video
	result = GL_Dialog_Media (graphicLib, "Video", "Hello world", "file://flash/HOST/CLESS.MP4", 50, GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
}
