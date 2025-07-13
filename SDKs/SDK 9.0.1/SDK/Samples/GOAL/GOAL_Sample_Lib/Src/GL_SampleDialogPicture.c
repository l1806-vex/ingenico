#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog picture
void GL_SampleDialogPicture(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Wgu", "Wgu", "file://flash/HOST/TU.TAR/wgusuite/image24.wgu", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Jpeg", "Jpeg", "file://flash/HOST/TU.TAR/jpgsuite/image24.jpg", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Bitmap", "Bmp", "file://flash/HOST/TU.TAR/bmpsuite/image24.bmp", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Png", "Png", "file://flash/HOST/TU.TAR/pngsuite/image24.png", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Gif", "Gif", "file://flash/HOST/TU.TAR/gifsuite/image24.gif", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Animated gif", "Earth", "file://flash/HOST/TU.TAR/gifsuite/earth.gif", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Animated gif", "Newton's cradle", "file://flash/HOST/TU.TAR/gifsuite/newtons.gif", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
}
