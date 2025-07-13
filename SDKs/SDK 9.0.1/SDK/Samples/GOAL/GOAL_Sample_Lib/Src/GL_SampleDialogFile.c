#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog file
void GL_SampleDialogFile(T_GL_HGRAPHIC_LIB graphicLib)
{
	char filename[256];

	// Example of choose of file
	if (GL_Dialog_File(graphicLib, "Select file", "dir://flash/HOST", "*.*",  filename, sizeof(filename), 0, GL_TIME_INFINITE) == GL_KEY_VALID)
	{
		// Here treat the file selected...
	}
}
