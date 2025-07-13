#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Sample of dialog text
void GL_SampleDialogText1(T_GL_HGRAPHIC_LIB graphicLib)
{
	char text[100] = "330412345678";
	ulong result;

	// Example of entering a text with long text
	result = GL_Dialog_Text (graphicLib, "Lorem ipsum", "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Nam liber tempor cum soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat facer possim assum.","(/d/d)/d/d./d/d./d/d./d/d./d/d", text, sizeof(text), GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}


// Sample of dialog text
void GL_SampleDialogText2(T_GL_HGRAPHIC_LIB graphicLib)
{
	char text[100] = "330412345678";
	ulong result;

	// Example of entering a text
	result = GL_Dialog_Text (graphicLib, "Text input", "Telephone number :","(/d/d)/d/d./d/d./d/d./d/d./d/d", text, sizeof(text), GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}


// Sample of dialog text
void GL_SampleDialogText(T_GL_HGRAPHIC_LIB graphicLib)
{
	GL_SampleDialogText1(graphicLib);
	GL_SampleDialogText2(graphicLib);
}
