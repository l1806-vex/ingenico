#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog slider
void GL_SampleDialogSlider(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;
	T_GL_COORD value = 5;

	// Example of displaying slider dialog
	result = GL_Dialog_Slider (graphicLib, "Slider", "Select level", "file://flash/HOST/TU.TAR/wgusuite/image24.wgu", &value, 0, 100, 5, 0, GL_TIME_INFINITE);
}
