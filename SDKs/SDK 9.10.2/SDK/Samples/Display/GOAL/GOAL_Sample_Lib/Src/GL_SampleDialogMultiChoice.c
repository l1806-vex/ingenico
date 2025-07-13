#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog multi choice
void GL_SampleDialogMultiChoice(T_GL_HGRAPHIC_LIB graphicLib)
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

	// Initial state of checkboxes
	bool checked [] =
	{
		true, //"Zero",
		false,//"One",
		false,//"Two",
		true, //"Three",
		true, //"Four",
		false,//"Five",
		true, //"Six",
		false,//"Seven",
		false,//"Height",
		false,//"Nine",
		false,//"Ten",
		true, //"Eleven",
		true, //"Twelve",
		true, // utf8
	};
	ulong result;

	// Display the multi choice and wait selection
	result = GL_Dialog_MultiChoice (graphicLib, "Menu", menu, 3, checked, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}
