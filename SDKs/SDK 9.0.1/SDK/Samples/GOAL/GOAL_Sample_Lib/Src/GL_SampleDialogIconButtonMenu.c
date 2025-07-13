#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog icon button menu
void GL_SampleDialogIconButtonMenu(T_GL_HGRAPHIC_LIB graphicLib)
{
	const char * menu [] =
	{
		"Zero",   "file://flash/HOST/TU.TAR/icones/0.png",
		"One",    "file://flash/HOST/TU.TAR/icones/1.png",
		"Two",    "file://flash/HOST/TU.TAR/icones/2.png",
		"Three",  "file://flash/HOST/TU.TAR/icones/3.png",
		"Four",   "file://flash/HOST/TU.TAR/icones/4.png",
		"Five",   "file://flash/HOST/TU.TAR/icones/5.png",
		"Six",    "file://flash/HOST/TU.TAR/icones/6.png",
		"Seven",  "file://flash/HOST/TU.TAR/icones/7.png",
		"Height", "file://flash/HOST/TU.TAR/icones/8.png",
		"Nine",   "file://flash/HOST/TU.TAR/icones/9.png",
		"Ten",    "file://flash/HOST/TU.TAR/icones/0.png",
		"Eleven", "file://flash/HOST/TU.TAR/icones/1.png",
		"Twelve", "file://flash/HOST/TU.TAR/icones/2.png",

		0 //<- DO NOT FORGET THIS TO STOP THE LIST
	};

	ulong result;

	// Display the menu and wait selection
	result = GL_Dialog_IconButtonMenu (graphicLib, "Menu", menu, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
}
