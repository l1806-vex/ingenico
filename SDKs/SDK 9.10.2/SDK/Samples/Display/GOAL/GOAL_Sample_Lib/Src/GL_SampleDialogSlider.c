#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Sample of dialog slider
void GL_SampleDialogSlider1(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;
	T_GL_COORD value = 5;

	// Example of displaying slider dialog
	result = GL_Dialog_Slider (graphicLib, "Lorem ipsum", "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Nam liber tempor cum soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat facer possim assum.", "file://flash/HOST/TU.TAR/wgusuite/image24.wgu", &value, 0, 100, 5, 0, GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}


// Sample of dialog slider
void GL_SampleDialogSlider2(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;
	T_GL_COORD value = 5;

	// Example of displaying slider dialog
	result = GL_Dialog_Slider (graphicLib, "Slider", "Select level", "file://flash/HOST/TU.TAR/wgusuite/image24.wgu", &value, 0, 100, 5, 0, GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}


// Sample of dialog slider
void GL_SampleDialogSlider(T_GL_HGRAPHIC_LIB graphicLib)
{
	GL_SampleDialogSlider1(graphicLib);
	GL_SampleDialogSlider2(graphicLib);
}
