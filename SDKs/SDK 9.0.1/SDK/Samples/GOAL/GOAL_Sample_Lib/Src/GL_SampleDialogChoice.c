#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog choice
void GL_SampleDialogChoice(T_GL_HGRAPHIC_LIB graphicLib)
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

		0 //<- DO NOT FORGET THIS TO STOP THE LIST
	};
	ulong result;
	int selectedItem = 3;

	// Display the menu and wait selection
	result = GL_Dialog_Choice (graphicLib, "Menu", menu, selectedItem, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
}
