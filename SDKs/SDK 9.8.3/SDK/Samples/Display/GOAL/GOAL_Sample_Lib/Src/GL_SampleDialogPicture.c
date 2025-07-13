#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Sample of dialog picture
void GL_SampleDialogPicture1(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example with long text
	result = GL_Dialog_Picture (graphicLib, "Lorem ipsum", "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Nam liber tempor cum soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat facer possim assum.", "file://flash/HOST/TU.TAR/wgusuite/image24.wgu", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
}


// Sample of dialog picture
void GL_SampleDialogPicture2(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Wgu", "Wgu", "file://flash/HOST/TU.TAR/wgusuite/image24.wgu", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
}


// Sample of dialog picture
void GL_SampleDialogPicture3(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Jpeg", "Jpeg", "file://flash/HOST/TU.TAR/jpgsuite/image24.jpg", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
}


// Sample of dialog picture
void GL_SampleDialogPicture4(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Bitmap", "Bmp", "file://flash/HOST/TU.TAR/bmpsuite/image24.bmp", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
}


// Sample of dialog picture
void GL_SampleDialogPicture5(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Png", "Png", "file://flash/HOST/TU.TAR/pngsuite/image24.png", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
}


// Sample of dialog picture
void GL_SampleDialogPicture6(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Gif", "Gif", "file://flash/HOST/TU.TAR/gifsuite/image24.gif", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
}


// Sample of dialog picture
void GL_SampleDialogPicture7(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Animated gif", "Earth", "file://flash/HOST/TU.TAR/gifsuite/earth.gif", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
}


// Sample of dialog picture
void GL_SampleDialogPicture8(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of displaying picture
	result = GL_Dialog_Picture (graphicLib, "Animated gif", "Newton's cradle", "file://flash/HOST/TU.TAR/gifsuite/newtons.gif", GL_BUTTON_DEFAULT, GL_TIME_INFINITE);
}


// Sample of dialog picture
void GL_SampleDialogPicture(T_GL_HGRAPHIC_LIB graphicLib)
{
	GL_SampleDialogPicture1(graphicLib);
	GL_SampleDialogPicture2(graphicLib);
	GL_SampleDialogPicture3(graphicLib);
	GL_SampleDialogPicture4(graphicLib);
	GL_SampleDialogPicture5(graphicLib);
	GL_SampleDialogPicture6(graphicLib);
	GL_SampleDialogPicture7(graphicLib);
	GL_SampleDialogPicture8(graphicLib);
}
