#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Sample of dialog date
void GL_SampleDialogDate1(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_DATE date;
	ulong result;

	// Example of entering a date
	date.day    = 7;
	date.month  = 2;
	date.year   = 2011;
	result = GL_Dialog_Date (graphicLib, "Date", "Current date", &date, "y/m/d", GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}


// Sample of dialog date
void GL_SampleDialogDate2(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_DATE date;
	ulong result;

	// Example of entering an hour
	date.hour   = 13;
	date.minute = 56;
	date.second = 38;
	result = GL_Dialog_Date (graphicLib, "Hour", "Current hour", &date, "H:M:S", GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}


// Sample of dialog date
void GL_SampleDialogDate(T_GL_HGRAPHIC_LIB graphicLib)
{
	GL_SampleDialogDate1(graphicLib);
	GL_SampleDialogDate2(graphicLib);
}
