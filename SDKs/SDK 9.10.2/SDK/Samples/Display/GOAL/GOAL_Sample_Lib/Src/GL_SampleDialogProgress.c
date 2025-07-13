#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// This function is called periodically to update the progress bar of the dialog box. 
// The value received as parameter corresponds to the current value of the progress bar.
// When this value reaches the maximum, the dialog is automatically closed.
static T_GL_COORD update(T_GL_COORD value)
{
	return value+1;
}


// Sample of dialog progress
void GL_SampleDialogProgress1(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example with long text
	result = GL_Dialog_Progress(graphicLib, "Lorem ipsum", "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Nam liber tempor cum soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat facer possim assum.", "file://flash/HOST/TU.TAR/wgusuite/image24.wgu", 0, 0, 100, update, GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}


// Sample of dialog progress
void GL_SampleDialogProgress2(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of displaying progress dialog
	result = GL_Dialog_Progress(graphicLib, "Progress", "Please wait", "file://flash/HOST/TU.TAR/wgusuite/image24.wgu", 0, 0, 100, update, GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}


// Sample of dialog progress
void GL_SampleDialogProgress(T_GL_HGRAPHIC_LIB graphicLib)
{
	GL_SampleDialogProgress1(graphicLib);
	GL_SampleDialogProgress2(graphicLib);
}
