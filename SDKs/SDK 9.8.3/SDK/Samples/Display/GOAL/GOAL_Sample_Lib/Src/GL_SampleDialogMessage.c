#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog message
void GL_SampleDialogMessage1(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Open information message box with long text
	result = GL_Dialog_Message  (graphicLib, "Lorem ipsum", "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Nam liber tempor cum soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat facer possim assum.", GL_ICON_INFORMATION, GL_BUTTON_VALID, GL_TIME_INFINITE);
}


// Sample of dialog message
void GL_SampleDialogMessage2(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Open error message box (only the valid key is used)
	result = GL_Dialog_Message  (graphicLib, "Error title", "Error message", GL_ICON_ERROR, GL_BUTTON_VALID, GL_TIME_INFINITE);
}


// Sample of dialog message
void GL_SampleDialogMessage3(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Open question message box (the valid key and cancel are used)
	result = GL_Dialog_Message  (graphicLib, "Question title", "Question message", GL_ICON_QUESTION, GL_BUTTON_ALL, GL_TIME_INFINITE);
}


// Sample of dialog message
void GL_SampleDialogMessage4(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Open warning message box (only the valid key is used)
	result = GL_Dialog_Message  (graphicLib, "Warning title", "Warning message", GL_ICON_WARNING, GL_BUTTON_VALID, GL_TIME_INFINITE);
}


// Sample of dialog message
void GL_SampleDialogMessage5(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Open information message box (only the valid key is used)
	result = GL_Dialog_Message  (graphicLib, "Information title", "Information message", GL_ICON_INFORMATION, GL_BUTTON_VALID, GL_TIME_INFINITE);
}


// Sample of dialog message
void GL_SampleDialogMessage6(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Open information message box (only the valid key is used)
	result = GL_Dialog_Message  (graphicLib, NULL, "PLEASE WAIT", GL_ICON_INFORMATION, GL_BUTTON_VALID, GL_TIME_INFINITE);
}


// Sample of dialog message
void GL_SampleDialogMessage(T_GL_HGRAPHIC_LIB graphicLib)
{
	GL_SampleDialogMessage1(graphicLib);
	GL_SampleDialogMessage2(graphicLib);
	GL_SampleDialogMessage3(graphicLib);
	GL_SampleDialogMessage4(graphicLib);
	GL_SampleDialogMessage5(graphicLib);
	GL_SampleDialogMessage6(graphicLib);
}
