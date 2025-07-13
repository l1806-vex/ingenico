#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog menu
void GL_SampleDialogMenu(T_GL_HGRAPHIC_LIB graphicLib)
{
	const char * menu [] =
	{
		"Zero",
		"One",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Height",
		"Nine",
		"Ten",
		"Eleven",
		"Twelve",
		"Utf8 : éèàù",

		0 //<- DO NOT FORGET THIS TO STOP THE LIST
	};
	ulong result;

	// Display the menu and wait selection
	result = GL_Dialog_Menu (graphicLib, "Menu", menu, 3, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
}
